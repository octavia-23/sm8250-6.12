/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2013-2018, 2021 The Linux Foundation. All rights reserved.
 */

#ifndef _NET_RMNET_CONFIG_H_
#define _NET_RMNET_CONFIG_H_

#include <linux/skbuff.h>
#include <linux/time.h>
#include <linux/netdevice.h>
#include <linux/if_rmnet.h>
#include "../../drivers/net/ethernet/qualcomm/rmnet/rmnet_config.h"

#ifndef RMNET_MAP_GET_CD_BIT
#define RMNET_MAP_GET_CD_BIT(skb) \
	(((struct rmnet_map_header *)((skb)->data))->flags & MAP_CMD_FLAG)
#endif

#endif /* _NET_RMNET_CONFIG_H_ */
