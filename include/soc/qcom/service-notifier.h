/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2017, 2021, The Linux Foundation. All rights reserved.
 */

#ifndef _SERVICE_NOTIFIER_H
#define _SERVICE_NOTIFIER_H

#include <linux/types.h>
#include <linux/notifier.h>
#include <linux/err.h>

#define SERVREG_NOTIF_SERVICE_STATE_DOWN_V01   0x0FFFFFFF
#define SERVREG_NOTIF_SERVICE_STATE_UP_V01     0x11111111
#define SERVREG_NOTIF_SERVICE_STATE_UNINIT_V01 0x7FFFFFFF

static inline void *service_notif_register_notifier(const char *service_name,
						    uint32_t instance_id,
						    struct notifier_block *nb,
						    int *curr_state)
{
	if (curr_state)
		*curr_state = SERVREG_NOTIF_SERVICE_STATE_DOWN_V01;
	return ERR_PTR(-ENODEV);
}

static inline int service_notif_unregister_notifier(void *service_notif_handle,
						    struct notifier_block *nb)
{
	return 0;
}

#endif /* _SERVICE_NOTIFIER_H */
