/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2020, The Linux Foundation. All rights reserved.
 */

#ifndef _LINUX_HDCP_QSEECOM_H_
#define _LINUX_HDCP_QSEECOM_H_

#include <linux/types.h>
#include <linux/errno.h>

enum hdcp2_app_cmd {
	HDCP2_CMD_INVALID,
	HDCP2_CMD_START,
	HDCP2_CMD_START_AUTH,
	HDCP2_CMD_STOP,
	HDCP2_CMD_TIMEOUT,
	HDCP2_CMD_PROCESS_MSG,
	HDCP2_CMD_QUERY_STREAM,
	HDCP2_CMD_EN_ENCRYPTION,
};

struct hdcp2_app_data {
	struct {
		u8 *data;
		u32 length;
	} request, response;
	u32 timeout;
	bool repeater_flag;
};

static inline void *hdcp1_init(void)
{
	return (void *)1;
}

static inline void hdcp1_deinit(void *data)
{
}

static inline bool hdcp1_feature_supported(void *data)
{
	return false;
}

static inline int hdcp1_start(void *data, u32 *aksv_msb, u32 *aksv_lsb)
{
	return -EINVAL;
}

static inline int hdcp1_stop(void *data)
{
	return 0;
}

static inline int hdcp1_set_enc(void *data, bool enable)
{
	return 0;
}

static inline void *hdcp2_init(u32 device_type)
{
	return NULL;
}

static inline void hdcp2_deinit(void *ctx)
{
}

static inline bool hdcp2_feature_supported(void *ctx)
{
	return false;
}

static inline int hdcp2_app_comm(void *ctx, enum hdcp2_app_cmd cmd,
				 struct hdcp2_app_data *app_data)
{
	return -EINVAL;
}

static inline int hdcp2_force_encryption(void *ctx, u32 enable)
{
	return -EINVAL;
}

static inline int hdcp2_open_stream(void *ctx, u8 vc_payload_id,
				    u8 stream_number, u8 *stream_type)
{
	return -EINVAL;
}

static inline int hdcp2_close_stream(void *ctx, u8 vc_payload_id,
				     u8 stream_number)
{
	return -EINVAL;
}

#endif /* _LINUX_HDCP_QSEECOM_H_ */
