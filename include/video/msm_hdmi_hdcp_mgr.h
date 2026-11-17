/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#ifndef _MSM_HDMI_HDCP_MGR_H_
#define _MSM_HDMI_HDCP_MGR_H_

#include <linux/types.h>

enum {
	DS_UNKNOWN,
	DS_RECEIVER,
	DS_REPEATER,
};

struct HDCP_V2V1_MSG_TOPOLOGY {
	u32 ds_type;
	u8 bksv[5];
	u32 dev_count;
	u32 depth;
	bool max_cascade_exceeded;
	bool max_dev_exceeded;
	u8 ksv_list[640];
};

#endif /* _MSM_HDMI_HDCP_MGR_H_ */
