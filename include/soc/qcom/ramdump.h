/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2014, 2017-2018, The Linux Foundation. All rights reserved.
 */

#ifndef _RAMDUMP_H
#define _RAMDUMP_H

#include <linux/types.h>
#include <linux/device.h>

struct ramdump_segment {
	unsigned long address;
	unsigned long size;
	void *v_address;
};

static inline void *create_ramdump_device(const char *name, struct device *dev)
{
	return NULL;
}

static inline void destroy_ramdump_device(void *rd_dev)
{
}

static inline int do_ramdump(void *rd_dev, struct ramdump_segment *segments, int count)
{
	return 0;
}

#endif
