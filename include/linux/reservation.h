/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_RESERVATION_COMPAT_H
#define _LINUX_RESERVATION_COMPAT_H

#include <linux/dma-resv.h>

#define reservation_object dma_resv
#define reservation_object_list dma_resv_list
#define reservation_object_init(obj) dma_resv_init(obj)
#define reservation_object_fini(obj) dma_resv_fini(obj)
#define reservation_object_lock(obj, ctx) dma_resv_lock(obj, ctx)
#define reservation_object_unlock(obj) dma_resv_unlock(obj)
#define reservation_object_trylock(obj) dma_resv_trylock(obj)
#define reservation_object_get_excl_rcu(obj) dma_resv_get_excl_unlocked(obj)
#define reservation_object_wait_timeout_rcu(obj, write, intr, timeout) \
	dma_resv_wait_timeout(obj, dma_resv_usage_rw(write), intr, timeout)

#endif /* _LINUX_RESERVATION_COMPAT_H */
