/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2020, The Linux Foundation. All rights reserved.
 */

#ifndef _LINUX_MSM_BUS_H
#define _LINUX_MSM_BUS_H

#include <linux/types.h>
#include <linux/device.h>
#include <linux/platform_device.h>

struct msm_bus_vectors {
	u64 src;
	u64 dst;
	u64 ab;
	u64 ib;
};

struct msm_bus_paths {
	int num_paths;
	struct msm_bus_vectors *vectors;
};

struct msm_bus_scale_pdata {
	struct msm_bus_paths *use_cases;
	int num_usecases;
	const char *name;
	int active_only;
};

static inline uint32_t msm_bus_scale_register_client(
		struct msm_bus_scale_pdata *pdata)
{
	return 1;
}

static inline int msm_bus_scale_client_update_request(
		uint32_t cl, unsigned int index)
{
	return 0;
}

static inline void msm_bus_scale_unregister_client(uint32_t cl)
{
}

static inline struct msm_bus_scale_pdata *msm_bus_pdata_from_node(
		struct platform_device *pdev, struct device_node *of_node)
{
	return NULL;
}

static inline struct msm_bus_scale_pdata *msm_bus_cl_get_pdata(
		struct platform_device *pdev)
{
	return NULL;
}

static inline void msm_bus_cl_clear_pdata(struct msm_bus_scale_pdata *pdata)
{
}

#endif /* _LINUX_MSM_BUS_H */
