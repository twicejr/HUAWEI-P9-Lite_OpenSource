/*
 * (Hisilicon's Hi36xx/Hi37xx SoC based) flattened device tree enabled machine
 *
 * Copyright (c) 2012-2013 Linaro Ltd.
 *
 * Haojian Zhuang <haojian.zhuang@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/irqchip.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>

#include <asm/hardware/arm_timer.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/hardware/timer-sp.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>

#include <linux/clocksource.h>
#include "core.h"

static struct of_device_id hs_l2cache_match[] __initdata = {
	{ .compatible = "arm,pl310-cache", },
	{}
};

static void __init hi3xxx_timer_init(void)
{
	struct device_node *node = NULL;
	int ret;
	u32 data[2];

	hs_map_io();
	hs_hotplug_init();
	of_clk_init(NULL);
	clocksource_of_init();

	node = of_find_matching_node(NULL, hs_l2cache_match);
	WARN_ON(!node);
	if (!node) {
		pr_err("Failed to find l2cache\n");
		return;
	}
	ret = of_property_read_u32_array(node, "hisilicon,l2cache-aux",
					 &data[0], 2);
	if (ret < 0) {
		data[0] = 0;
		data[1] = ~0UL;
	}
	l2x0_of_init(data[0], data[1]);
}

static void __init hs_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

static const char *hs_compat[] __initdata = {
	"hisilicon,hi3620-hi4511",
	"hisilicon,hi3716",
	NULL,
};

DT_MACHINE_START(HS_DT, "Hisilicon Hi36xx/Hi37xx (Flattened Device Tree)")
	/* Maintainer: Haojian Zhuang <haojian.zhuang@linaro.org> */
	.map_io		= debug_ll_io_init,
	.init_irq	= irqchip_init,
	.init_time	= hi3xxx_timer_init,
	.init_machine	= hs_init,
	.dt_compat	= hs_compat,
	.smp		= smp_ops(hs_smp_ops),
	.restart	= hs_restart,
MACHINE_END
