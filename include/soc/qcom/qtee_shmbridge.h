/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _SOC_QCOM_QTEE_SHMBRIDGE_H_
#define _SOC_QCOM_QTEE_SHMBRIDGE_H_

#include <linux/types.h>
#include <linux/errno.h>

struct qtee_shm {
	phys_addr_t paddr;
	void *vaddr;
	size_t size;
};

static inline bool qtee_shmbridge_is_enabled(void)
{
	return false;
}

static inline int32_t qtee_shmbridge_allocate_shm(size_t size, struct qtee_shm *shm)
{
	return -EINVAL;
}

static inline void qtee_shmbridge_free_shm(struct qtee_shm *shm)
{
}

#endif /* _SOC_QCOM_QTEE_SHMBRIDGE_H_ */
