/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2020, The Linux Foundation. All rights reserved.
 */

#ifndef _LINUX_MSM_ION_H
#define _LINUX_MSM_ION_H

#include <linux/types.h>

#define ION_BIT(nr)			(1UL << (nr))
#define ION_FLAG_CACHED			1
#define ION_FLAG_CACHED_NEEDS_SYNC	2
#define ION_FLAG_SECURE			(1UL << 31)
#define ION_FLAG_CP_PIXEL		ION_BIT(19)
#define ION_FLAG_CP_CAMERA_PREVIEW	ION_BIT(20)
#define ION_FLAG_CP_SEC_DISPLAY		ION_BIT(25)

#endif /* _LINUX_MSM_ION_H */
