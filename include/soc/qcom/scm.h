/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _SOC_QCOM_SCM_H_
#define _SOC_QCOM_SCM_H_

#include <linux/types.h>
#include <linux/firmware/qcom/qcom_scm.h>
#include <asm/cacheflush.h>

#ifndef dmac_flush_range
#define dmac_flush_range(start, end) \
	dcache_clean_inval_poc((unsigned long)(start), (unsigned long)(end))
#endif

#define SCM_SVC_BOOT			0x01
#define SCM_SVC_PIL			0x02
#define SCM_SVC_UTIL			0x03
#define SCM_SVC_TZ			0x04
#define SCM_SVC_IO			0x05
#define SCM_SVC_INFO			0x06
#define SCM_SVC_SSD			0x07
#define SCM_SVC_FUSE			0x08
#define SCM_SVC_PWR			0x09
#define SCM_SVC_MP			0x0C
#define SCM_SVC_DCVS			0x0D
#define SCM_SVC_ES			0x10
#define SCM_SVC_HDCP			0x11
#define SCM_SVC_MDTP			0x12
#define SCM_SVC_LMH			0x13
#define SCM_SVC_SMMU_PROGRAM		0x15
#define SCM_SVC_QDSS			0x16
#define SCM_SVC_TZSCHEDULER		0xFC

#define SCM_SIP_FNID(s, c) (((((s) & 0xFF) << 8) | ((c) & 0xFF)) | 0x02000000)

#define SCM_VAL		0x0
#define SCM_RO		0x1
#define SCM_RW		0x2
#define SCM_BUFVAL	0x3

#define SCM_ARGS_MASK	0xF
#define SCM_ARGS_SHIFT	4
#define SCM_MAX_ARGS	10

#define __SCM_ARGS(n, a, b, c, d, ...) \
	((((n) & 0xF) | \
	 (((a) & 0x3) << 4) | \
	 (((b) & 0x3) << 6) | \
	 (((c) & 0x3) << 8) | \
	 (((d) & 0x3) << 10)))
#define SCM_ARGS(...) __SCM_ARGS(__VA_ARGS__, 0, 0, 0, 0)

#define SCM_BUFFER_PHYS(b) virt_to_phys(b)

struct scm_desc {
	u32 arginfo;
	u64 args[SCM_MAX_ARGS];
	u64 ret[3];
};

static inline int scm_call2(u32 fn_id, struct scm_desc *desc)
{
	return 0;
}

static inline u32 scm_io_read(phys_addr_t addr)
{
	unsigned int val = 0;
	qcom_scm_io_readl(addr, &val);
	return val;
}

static inline int scm_io_write(phys_addr_t addr, u32 val)
{
	return qcom_scm_io_writel(addr, val);
}

#endif /* _SOC_QCOM_SCM_H_ */
