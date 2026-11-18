/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __ASM_ARM64_DMA_IOMMU_H
#define __ASM_ARM64_DMA_IOMMU_H

#include <linux/dma-mapping.h>
#include <linux/iommu.h>

struct dma_iommu_mapping {
	struct iommu_domain *domain;
	dma_addr_t base;
};

#endif /* __ASM_ARM64_DMA_IOMMU_H */
