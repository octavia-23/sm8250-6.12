/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2020, The Linux Foundation. All rights reserved.
 */

#ifndef __SOC_QCOM_PM_H
#define __SOC_QCOM_PM_H

#include <linux/types.h>
#include <linux/pm.h>

static inline uint32_t msm_cpuidle_get_deep_idle_latency(void)
{
	return 0;
}

#endif /* __SOC_QCOM_PM_H */
