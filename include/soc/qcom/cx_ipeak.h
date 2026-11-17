/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 */

#ifndef __SOC_QCOM_CX_IPEAK_H
#define __SOC_QCOM_CX_IPEAK_H

#include <linux/types.h>
#include <linux/device.h>

struct cx_ipeak_client;

static inline struct cx_ipeak_client *cx_ipeak_register(
		struct device_node *dev_node, const char *client_name)
{
	return NULL;
}

static inline void cx_ipeak_unregister(struct cx_ipeak_client *client)
{
}

static inline int cx_ipeak_update(struct cx_ipeak_client *client, bool vote)
{
	return 0;
}

#endif /* __SOC_QCOM_CX_IPEAK_H */
