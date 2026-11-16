// SPDX-License-Identifier: GPL-2.0-only
/*
 * Xiaomi Alioth ADSP/CDSP/Modem Subsystem Boot & SSR Driver
 *
 * Boots Qualcomm remoteprocs upon userspace request or early boot,
 * monitors subsystem crashes, and manages crash-loop backoff.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/remoteproc.h>
#include <linux/remoteproc/qcom_rproc.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/mutex.h>
#include <linux/notifier.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

#define ALIOTH_DSP_COUNT 4

struct alioth_dsp {
	const char *name;
	const char *ssr_name;
	struct device_node *node;
	struct rproc *rproc;
	struct miscdevice misc;
	struct notifier_block nb;
	void *ssr_handle;
	struct delayed_work work;
	struct mutex lock;
	struct kobject *kobj;
	bool booted;
	int retry_count;
	unsigned long last_crash_jiffies;
	int crash_count;
};

static unsigned int alioth_dsp_max_crashes = 5;
static unsigned int alioth_dsp_crash_window = 60;
module_param_named(max_crashes, alioth_dsp_max_crashes, uint, 0644);
module_param_named(crash_window, alioth_dsp_crash_window, uint, 0644);

static struct alioth_dsp alioth_dsps[ALIOTH_DSP_COUNT] = {
	{ .name = "adsp",  .ssr_name = "adsp" },
	{ .name = "cdsp",  .ssr_name = "cdsp" },
	{ .name = "slpi",  .ssr_name = "slpi" },
	{ .name = "modem", .ssr_name = "modem" },
};

static int alioth_subsys_open(struct inode *inode, struct file *file)
{
	struct miscdevice *m = file->private_data;
	struct alioth_dsp *dsp = container_of(m, struct alioth_dsp, misc);

	mutex_lock(&dsp->lock);
	if (!dsp->booted && dsp->node) {
		dsp->retry_count = 0;
		schedule_delayed_work(&dsp->work, 0);
	}
	mutex_unlock(&dsp->lock);

	return 0;
}

static const struct file_operations alioth_subsys_fops = {
	.owner = THIS_MODULE,
	.open  = alioth_subsys_open,
};

static void alioth_dsp_work(struct work_struct *work)
{
	struct alioth_dsp *dsp = container_of(work, struct alioth_dsp, work.work);
	int ret;

	mutex_lock(&dsp->lock);
	if (dsp->booted) {
		mutex_unlock(&dsp->lock);
		return;
	}

	if (!dsp->rproc)
		dsp->rproc = rproc_get_by_phandle(dsp->node->phandle);

	if (!dsp->rproc) {
		dsp->retry_count++;
		if (dsp->retry_count >= 60) {
			pr_warn("alioth-dsp-boot: %s: remoteproc never appeared\n", dsp->name);
			mutex_unlock(&dsp->lock);
			return;
		}
		schedule_delayed_work(&dsp->work, msecs_to_jiffies(500));
		mutex_unlock(&dsp->lock);
		return;
	}

	ret = rproc_boot(dsp->rproc);
	if (ret == 0) {
		dsp->booted = true;
		pr_info("alioth-dsp-boot: %s booted\n", dsp->name);
	} else {
		pr_err("alioth-dsp-boot: %s: boot failed: %d\n", dsp->name, ret);
		rproc_put(dsp->rproc);
		dsp->rproc = NULL;
		dsp->retry_count++;
		if (dsp->retry_count < 60)
			schedule_delayed_work(&dsp->work, msecs_to_jiffies(500));
	}

	mutex_unlock(&dsp->lock);
}

static int alioth_dsp_ssr_notify(struct notifier_block *nb,
				  unsigned long action, void *data)
{
	struct alioth_dsp *dsp = container_of(nb, struct alioth_dsp, nb);
	unsigned long now = jiffies;

	if (action == 2) { /* QCOM_SSR_BEFORE_SHUTDOWN */
		if (time_after(now, dsp->last_crash_jiffies + msecs_to_jiffies(alioth_dsp_crash_window * 1000)))
			dsp->crash_count = 0;

		dsp->last_crash_jiffies = now;
		dsp->crash_count++;

		pr_warn("alioth-dsp-boot: %s crashed (%u in %u s)\n",
			dsp->name, dsp->crash_count, alioth_dsp_crash_window);

		if (dsp->crash_count >= alioth_dsp_max_crashes) {
			pr_emerg("alioth-dsp-boot: %s crashed %u times within %u s, recovery disabled\n",
				 dsp->name, dsp->crash_count, alioth_dsp_crash_window);
			if (dsp->rproc)
				dsp->rproc->recovery_disabled = true;
		}
	}
	return NOTIFY_DONE;
}

static void alioth_dsp_teardown(void)
{
	int i;

	for (i = 0; i < ALIOTH_DSP_COUNT; i++) {
		struct alioth_dsp *dsp = &alioth_dsps[i];

		if (dsp->ssr_handle) {
			qcom_unregister_ssr_notifier(dsp->ssr_handle, &dsp->nb);
			dsp->ssr_handle = NULL;
		}
		if (dsp->misc.minor != 0)
			misc_deregister(&dsp->misc);
		if (dsp->kobj) {
			kobject_put(dsp->kobj);
			dsp->kobj = NULL;
		}
		cancel_delayed_work_sync(&dsp->work);
		if (dsp->rproc) {
			rproc_put(dsp->rproc);
			dsp->rproc = NULL;
		}
	}
}

static int alioth_dsp_boot_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int i, ret;

	if (!np)
		return -ENODEV;

	for (i = 0; i < ALIOTH_DSP_COUNT; i++) {
		struct alioth_dsp *dsp = &alioth_dsps[i];
		char prop_name[32];

		mutex_init(&dsp->lock);
		INIT_DELAYED_WORK(&dsp->work, alioth_dsp_work);

		snprintf(prop_name, sizeof(prop_name), "qcom,%s", dsp->name);
		dsp->node = of_parse_phandle(np, prop_name, 0);
		if (!dsp->node)
			continue;

		dsp->misc.minor = MISC_DYNAMIC_MINOR;
		dsp->misc.name = devm_kasprintf(dev, GFP_KERNEL, "subsys_%s", dsp->name);
		dsp->misc.fops = &alioth_subsys_fops;

		ret = misc_register(&dsp->misc);
		if (ret) {
			dev_warn(dev, "failed to register misc device for %s\n", dsp->name);
			continue;
		}

		dsp->nb.notifier_call = alioth_dsp_ssr_notify;
		dsp->ssr_handle = qcom_register_ssr_notifier(dsp->ssr_name, &dsp->nb);
		if (IS_ERR_OR_NULL(dsp->ssr_handle))
			dev_warn(dev, "failed to register SSR notifier for %s\n", dsp->ssr_name);

		schedule_delayed_work(&dsp->work, 0);
	}

	return 0;
}

static void alioth_dsp_boot_remove(struct platform_device *pdev)
{
	alioth_dsp_teardown();
}

static const struct of_device_id alioth_dsp_boot_of_match[] = {
	{ .compatible = "xiaomi,alioth-dsp-boot" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, alioth_dsp_boot_of_match);

static struct platform_driver alioth_dsp_boot_driver = {
	.probe = alioth_dsp_boot_probe,
	.remove = alioth_dsp_boot_remove,
	.driver = {
		.name = "alioth-dsp-boot",
		.of_match_table = alioth_dsp_boot_of_match,
	},
};
module_platform_driver(alioth_dsp_boot_driver);

MODULE_DESCRIPTION("Xiaomi Alioth ADSP/CDSP/Modem Subsystem Boot & SSR Driver");
MODULE_LICENSE("GPL");
