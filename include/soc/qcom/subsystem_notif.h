/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2018, The Linux Foundation. All rights reserved.
 */

#ifndef __SUBSYSTEM_NOTIF_H__
#define __SUBSYSTEM_NOTIF_H__

#include <linux/notifier.h>
#include <linux/remoteproc/qcom_rproc.h>

enum subsys_notif_type {
	SUBSYS_BEFORE_SHUTDOWN,
	SUBSYS_AFTER_SHUTDOWN,
	SUBSYS_BEFORE_POWERUP,
	SUBSYS_AFTER_POWERUP,
	SUBSYS_RAMDUMP_NOTIFICATION,
	SUBSYS_POWERUP_FAILURE,
	SUBSYS_PROXY_VOTE,
	SUBSYS_PROXY_UNVOTE,
	SUBSYS_SOC_RESET,
	SUBSYS_PREPARE_FOR_FATAL_SHUTDOWN,
	SUBSYS_NOTIF_TYPE_COUNT
};

#define SUBSYS_MODEM "modem"
#define SUBSYS_LOCAL_MODEM "modem"
#define SUBSYS_REMOTE_MODEM "esoc0"

struct notif_data {
	void *pdev;
	bool enable_ramdump;
	bool enable_mini_ramdump;
	bool no_auth;
	const char *subsys_name;
};

#if IS_ENABLED(CONFIG_QCOM_RPROC_COMMON)
static inline void *subsys_notif_register_notifier(const char *subsys_name,
						   struct notifier_block *nb)
{
	return qcom_register_ssr_notifier(subsys_name, nb);
}

static inline int subsys_notif_unregister_notifier(void *subsys_handle,
						   struct notifier_block *nb)
{
	return qcom_unregister_ssr_notifier(subsys_handle, nb);
}
#else
static inline void *subsys_notif_register_notifier(const char *subsys_name,
						   struct notifier_block *nb)
{
	return NULL;
}

static inline int subsys_notif_unregister_notifier(void *subsys_handle,
						   struct notifier_block *nb)
{
	return 0;
}
#endif

static inline int subsys_notif_queue_notification(void *subsys_handle,
						  enum subsys_notif_type notif_type,
						  void *data)
{
	return 0;
}

static inline void *subsys_notif_add_subsys(const char *subsys_name)
{
	return NULL;
}

#endif /* __SUBSYSTEM_NOTIF_H__ */
