/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2017, The Linux Foundation. All rights reserved.
 */

#ifndef _SERVICE_LOCATOR_H
#define _SERVICE_LOCATOR_H

#include <linux/types.h>
#include <linux/notifier.h>

#define LOCATOR_DOWN 0
#define LOCATOR_UP   1
#define QMI_SERVREG_LOC_NAME_LENGTH_V01 64

struct pd_qmi_domain_list {
	char name[QMI_SERVREG_LOC_NAME_LENGTH_V01];
	uint32_t instance_id;
};

struct pd_qmi_client_data {
	char client_name[QMI_SERVREG_LOC_NAME_LENGTH_V01];
	char service_name[QMI_SERVREG_LOC_NAME_LENGTH_V01];
	int total_domains;
	struct pd_qmi_domain_list domain_list[1];
};

static inline int get_service_location(const char *client_name,
				       const char *service_name,
				       struct notifier_block *locator_nb)
{
	return -ENODEV;
}

#endif /* _SERVICE_LOCATOR_H */
