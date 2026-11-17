/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2021, The Linux Foundation. All rights reserved.
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef __SOC_QCOM_OF_COMMON_H
#define __SOC_QCOM_OF_COMMON_H

#include <linux/types.h>
#include <linux/of.h>

#ifndef LP_DDR4_TYPE
#define LP_DDR4_TYPE 0x7
#endif

static inline int of_fdt_get_ddrrank(int channel)
{
	return 0;
}

static inline int of_fdt_get_ddrhbb(int channel, int rank)
{
	return 0;
}

#ifndef of_fdt_get_ddrtype
static inline int of_fdt_get_ddrtype(void)
{
	return -EINVAL;
}
#define of_fdt_get_ddrtype of_fdt_get_ddrtype
#endif

#endif /* __SOC_QCOM_OF_COMMON_H */
