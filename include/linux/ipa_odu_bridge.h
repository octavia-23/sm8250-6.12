/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2019, The Linux Foundation. All rights reserved.
 */

#ifndef _IPA_ODU_BRIDGE_H_
#define _IPA_ODU_BRIDGE_H_

#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/ipa.h>

#define ODU_BRIDGE_IOC_MAGIC 0xCD

enum odu_bridge_ioctl_cmds {
	ODU_BRIDGE_IOCTL_SET_MODE = 0,
	ODU_BRIDGE_IOCTL_SET_LLV6_ADDR,
	ODU_BRIDGE_IOCTL_MAX,
};

enum odu_bridge_mode {
	ODU_BRIDGE_MODE_ROUTER = 0,
	ODU_BRIDGE_MODE_BRIDGE,
	ODU_BRIDGE_MODE_MAX,
};

#define ODU_BRIDGE_IOC_SET_MODE \
	_IOW(ODU_BRIDGE_IOC_MAGIC, ODU_BRIDGE_IOCTL_SET_MODE, uint32_t)

#define ODU_BRIDGE_IOC_SET_LLV6_ADDR \
	_IOW(ODU_BRIDGE_IOC_MAGIC, ODU_BRIDGE_IOCTL_SET_LLV6_ADDR, struct in6_addr)

struct odu_bridge_params {
	const char *netdev_name;
	void *priv;
	ipa_notify_cb tx_dp_notify;
	int (*send_dl_skb)(void *priv, struct sk_buff *skb);
	u8 device_ethaddr[ETH_ALEN];
	u32 ipa_desc_size;
};

#if IS_ENABLED(CONFIG_IPA) || IS_ENABLED(CONFIG_IPA3)
int odu_bridge_init(struct odu_bridge_params *params);
int odu_bridge_connect(void);
int odu_bridge_disconnect(void);
int odu_bridge_tx_dp(struct sk_buff *skb, struct ipa_tx_meta *metadata);
int odu_bridge_cleanup(void);
#else
static inline int odu_bridge_init(struct odu_bridge_params *params)
{
	return -ENODEV;
}
static inline int odu_bridge_connect(void)
{
	return -ENODEV;
}
static inline int odu_bridge_disconnect(void)
{
	return -ENODEV;
}
static inline int odu_bridge_tx_dp(struct sk_buff *skb, struct ipa_tx_meta *metadata)
{
	return -ENODEV;
}
static inline int odu_bridge_cleanup(void)
{
	return 0;
}
#endif

#endif /* _IPA_ODU_BRIDGE_H_ */
