/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 */

#ifndef _FSA4480_I2C_H
#define _FSA4480_I2C_H

#include <linux/notifier.h>
#include <linux/of.h>

enum fsa_function {
	FSA_USBC_ORIENTATION_CC1,
	FSA_USBC_ORIENTATION_CC2,
	FSA_USBC_DISPLAYPORT_DISCONNECTED,
	FSA_MIC_GND_SWAP,
	FSA_USBC_AUDIO_DISCONNECTED,
};

#if IS_ENABLED(CONFIG_TYPEC_MUX_FSA4480)
int fsa4480_switch_event(struct device_node *node, enum fsa_function mode);
int fsa4480_reg_notifier(struct notifier_block *nb, struct device_node *node);
int fsa4480_unreg_notifier(struct notifier_block *nb, struct device_node *node);
#else
static inline int fsa4480_switch_event(struct device_node *node,
				       enum fsa_function mode)
{
	return 0;
}

static inline int fsa4480_reg_notifier(struct notifier_block *nb,
				       struct device_node *node)
{
	return 0;
}

static inline int fsa4480_unreg_notifier(struct notifier_block *nb,
					 struct device_node *node)
{
	return 0;
}
#endif

#endif /* _FSA4480_I2C_H */
