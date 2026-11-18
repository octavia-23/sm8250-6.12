/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2011-2019, The Linux Foundation. All rights reserved.
 */

#ifndef _MSM_SPS_H_
#define _MSM_SPS_H_

#include <linux/types.h>

struct sps_mem_buffer {
	void *base;
	phys_addr_t phys_base;
	u32 size;
	u32 min_size;
	dma_addr_t iova;
};

struct sps_iovec {
	u32 addr;
	u32 size:16;
	u32 flags:16;
};

#endif /* _MSM_SPS_H_ */
