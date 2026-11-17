/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2020, Xiaomi Corporation. All rights reserved.
 */

#ifndef _DRM_NOTIFIER_MI_H_
#define _DRM_NOTIFIER_MI_H_

#include <linux/notifier.h>

enum {
	MI_DRM_PRE_EVENT_BLANK = 0x01,
	MI_DRM_EARLY_EVENT_BLANK = 0x02,
	MI_DRM_EVENT_BLANK = 0x03,
};

enum {
	MI_DRM_BLANK_UNBLANK = 0,
	MI_DRM_BLANK_POWERDOWN = 1,
};

struct mi_drm_notifier {
	int id;
	void *data;
};

static inline int mi_drm_register_client(struct notifier_block *nb)
{
	return 0;
}

static inline int mi_drm_unregister_client(struct notifier_block *nb)
{
	return 0;
}

static inline int mi_drm_notifier_call_chain(unsigned long val, void *v)
{
	return 0;
}

#endif /* _DRM_NOTIFIER_MI_H_ */
