/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * OF helpers for the GPIO API
 *
 * Copyright (c) 2007-2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#ifndef __LINUX_OF_GPIO_H
#define __LINUX_OF_GPIO_H

#include <linux/compiler.h>
#include <linux/gpio/driver.h>
#include <linux/gpio.h>		/* FIXME: Shouldn't be here */
#include <linux/of.h>

struct device_node;

enum of_gpio_flags {
	OF_GPIO_ACTIVE_LOW = 0x1,
	OF_GPIO_SINGLE_ENDED = 0x2,
};

#ifdef CONFIG_OF_GPIO

extern int of_get_named_gpio(const struct device_node *np,
			     const char *list_name, int index);

static inline int of_get_named_gpio_flags(const struct device_node *np,
		const char *list_name, int index, enum of_gpio_flags *flags)
{
	if (flags) {
		struct of_phandle_args out_args;
		int ret = of_parse_phandle_with_args(np, list_name, "#gpio-cells", index, &out_args);
		if (!ret && out_args.args_count > 1)
			*flags = (enum of_gpio_flags)out_args.args[1];
		else
			*flags = 0;
	}
	return of_get_named_gpio(np, list_name, index);
}

#else /* CONFIG_OF_GPIO */

#include <linux/errno.h>

/* Drivers may not strictly depend on the GPIO support, so let them link. */
static inline int of_get_named_gpio(const struct device_node *np,
                                   const char *propname, int index)
{
	return -ENOSYS;
}

static inline int of_get_named_gpio_flags(const struct device_node *np,
		const char *list_name, int index, enum of_gpio_flags *flags)
{
	if (flags)
		*flags = 0;
	return -ENOSYS;
}

#endif /* CONFIG_OF_GPIO */

#endif /* __LINUX_OF_GPIO_H */
