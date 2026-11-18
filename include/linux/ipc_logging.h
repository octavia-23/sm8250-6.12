/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2021, The Linux Foundation. All rights reserved.
 */

#ifndef _LINUX_IPC_LOGGING_H
#define _LINUX_IPC_LOGGING_H

#include <linux/types.h>

#if IS_ENABLED(CONFIG_IPC_LOGGING)
void *ipc_log_context_create(int max_num_pages, const char *mod_name, uint16_t user_version);
void ipc_log_context_destroy(void *ctxt);
int ipc_log_string(void *ilctxt, const char *fmt, ...) __printf(2, 3);
#else
static inline void *ipc_log_context_create(int max_num_pages,
					   const char *mod_name,
					   uint16_t user_version)
{
	return NULL;
}

static inline void ipc_log_context_destroy(void *ctxt)
{
}

static inline __printf(2, 3) int ipc_log_string(void *ilctxt, const char *fmt, ...)
{
	return 0;
}
#endif

#endif /* _LINUX_IPC_LOGGING_H */
