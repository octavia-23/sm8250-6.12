/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2019, The Linux Foundation. All rights reserved.
 */

#ifndef _IPA_ODU_BRIDGE_H_
#define _IPA_ODU_BRIDGE_H_

#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/msm_ipa.h>
#include <linux/ipa.h>

struct odu_bridge_params {
	const char *netdev_name;
	void *priv;
	ipa_notify_cb tx_dp_notify;
	int (*send_dl_skb)(void *priv, struct sk_buff *skb);
	u8 device_ethaddr[ETH_ALEN];
	u32 ipa_desc_size;
};

struct ipa_bridge_init_params {
	struct odu_bridge_params info;
	void (*wakeup_request)(void *cl_priv);
};

#if IS_ENABLED(CONFIG_IPA) || IS_ENABLED(CONFIG_IPA3)
int odu_bridge_init(struct odu_bridge_params *params);
int odu_bridge_connect(void);
int odu_bridge_disconnect(void);
int odu_bridge_tx_dp(struct sk_buff *skb, struct ipa_tx_meta *metadata);
int odu_bridge_cleanup(void);

int ipa_bridge_init(struct ipa_bridge_init_params *params, u32 *hdl);
int ipa_bridge_cleanup(u32 hdl);
int ipa_bridge_connect(u32 hdl);
int ipa_bridge_disconnect(u32 hdl);
int ipa_bridge_resume(u32 hdl);
int ipa_bridge_suspend(u32 hdl);
int ipa_bridge_set_perf_profile(u32 hdl, u32 bandwidth);
int ipa_bridge_tx_dp(u32 hdl, struct sk_buff *skb, struct ipa_tx_meta *metadata);
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
static inline int ipa_bridge_init(struct ipa_bridge_init_params *params, u32 *hdl)
{
	return -ENODEV;
}
static inline int ipa_bridge_cleanup(u32 hdl)
{
	return -ENODEV;
}
static inline int ipa_bridge_connect(u32 hdl)
{
	return -ENODEV;
}
static inline int ipa_bridge_disconnect(u32 hdl)
{
	return -ENODEV;
}
static inline int ipa_bridge_resume(u32 hdl)
{
	return -ENODEV;
}
static inline int ipa_bridge_suspend(u32 hdl)
{
	return -ENODEV;
}
static inline int ipa_bridge_set_perf_profile(u32 hdl, u32 bandwidth)
{
	return -ENODEV;
}
static inline int ipa_bridge_tx_dp(u32 hdl, struct sk_buff *skb, struct ipa_tx_meta *metadata)
{
	return -ENODEV;
}
#endif

#endif /* _IPA_ODU_BRIDGE_H_ */
