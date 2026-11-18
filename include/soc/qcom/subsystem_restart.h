/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2018, The Linux Foundation. All rights reserved.
 */

#ifndef __SUBSYS_RESTART_H
#define __SUBSYS_RESTART_H

#include <linux/types.h>
#include <linux/notifier.h>

struct subsys_desc;
struct subsys_device;

static inline void *subsystem_get(const char *name)
{
	return NULL;
}

static inline void *subsystem_get_with_fwname(const char *name, const char *fw_name)
{
	return NULL;
}

static inline void subsystem_put(void *subsystem)
{
}

static inline int subsystem_restart(const char *name)
{
	return 0;
}

static inline int subsystem_restart_dev(struct subsys_device *dev)
{
	return 0;
}

static inline int subsystem_crashed(const char *name)
{
	return 0;
}

static inline int get_subsys_ssr_failure(const char *name)
{
	return 0;
}

#endif /* __SUBSYS_RESTART_H */
