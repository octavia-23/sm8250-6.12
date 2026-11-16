// SPDX-License-Identifier: GPL-2.0-only
/*
 * Xiaomi Alioth Smoke Test & Hardware Watchdog Reboot Driver
 *
 * Provides early bringup verification by restarting the system
 * after a specified timeout via cmdline:
 *   alioth.smoke_reboot=<seconds>
 *   alioth.smoke_reboot_cmd=<command_string>
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/workqueue.h>
#include <linux/reboot.h>

#define ALIOTH_SMOKE_CMD_MAX 32

static unsigned int alioth_smoke_secs;
static char alioth_smoke_cmd[ALIOTH_SMOKE_CMD_MAX];
static struct delayed_work alioth_smoke_reboot_work;

static int __init alioth_smoke_reboot_setup(char *str)
{
	int ret;

	ret = kstrtouint(str, 0, &alioth_smoke_secs);
	return (ret == 0);
}
__setup("alioth.smoke_reboot=", alioth_smoke_reboot_setup);

static int __init alioth_smoke_cmd_setup(char *str)
{
	strscpy(alioth_smoke_cmd, str, sizeof(alioth_smoke_cmd));
	return 1;
}
__setup("alioth.smoke_reboot_cmd=", alioth_smoke_cmd_setup);

static void alioth_smoke_reboot_fn(struct work_struct *work)
{
	char *cmd = (alioth_smoke_cmd[0] != '\0') ? alioth_smoke_cmd : NULL;

	pr_emerg("alioth: smoke_reboot: %u s elapsed, restarting %s\n",
		 alioth_smoke_secs, cmd ? cmd : "system");
	kernel_restart(cmd);
}

static int __init alioth_smoke_reboot_init(void)
{
	if (alioth_smoke_secs != 0) {
		pr_info("alioth: smoke_reboot: restarting in %u s\n", alioth_smoke_secs);
		INIT_DELAYED_WORK(&alioth_smoke_reboot_work, alioth_smoke_reboot_fn);
		schedule_delayed_work(&alioth_smoke_reboot_work,
				      msecs_to_jiffies(alioth_smoke_secs * 1000));
	}
	return 0;
}
late_initcall(alioth_smoke_reboot_init);

MODULE_DESCRIPTION("Xiaomi Alioth Smoke Test & Hardware Watchdog Reboot Driver");
MODULE_LICENSE("GPL");
