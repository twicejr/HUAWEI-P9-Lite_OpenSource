/*
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2013 Hisilicon Limited.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */
#include <linux/cpu.h>
#include <linux/io.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <asm/cacheflush.h>
#include <asm/smp_plat.h>
#include "core.h"

enum {
	HI3620_CTRL,
	HI3716_CTRL,
};

static void __iomem *ctrl_base;
static int id;

void hs_set_cpu(int cpu, bool enable)
{
	u32 val = 0;

	if (!ctrl_base)
		return;

	if (id == HI3620_CTRL) {
		if (enable) {
			/* MTCMOS */
			writel_relaxed((0x01 << (cpu + 3)), ctrl_base + 0xD0);
			writel_relaxed((0x1011 << cpu), ctrl_base + 0x414);
			writel_relaxed((0x401011 << cpu), ctrl_base + 0x410);

			/* ISO disable */
			writel((0x01 << (cpu + 3)), ctrl_base + 0x0C4);

			/* WFI Mask */
			val = readl(ctrl_base + 0x200);
			val &= ~(0x1 << (cpu+28));
			writel(val, ctrl_base + 0x200);

			/* Enable core */
			writel_relaxed((0x01 << cpu), ctrl_base + 0xf4);
			/* Unreset */
			writel_relaxed((0x401011 << cpu), ctrl_base + 0x414);
		} else {
			/* iso enable */
			writel_relaxed((0x01 << (cpu + 3)), ctrl_base + 0xC0);

			/* MTCMOS */
			writel_relaxed((0x01 << (cpu + 3)), ctrl_base + 0xD4);

			/* wfi mask */
			val = readl_relaxed(ctrl_base + 0x200);
			val |= (0x1 << (cpu+28));
			writel_relaxed(val, ctrl_base + 0x200);

			/* disable core*/
			writel_relaxed((0x01 << cpu), ctrl_base + 0xf8);
			/* Reset */
			writel_relaxed((0x401011 << cpu), ctrl_base + 0x410);
		}
	} else if (id == HI3716_CTRL) {
		if (enable) {
			/* power on cpu1 */
			val = readl_relaxed(ctrl_base + 0x1000);
			val &=  ~(0x1 << 8);
			val |= (0x1 << 7);
			val &= ~(0x1 << 3);
			writel_relaxed(val, ctrl_base + 0x1000);

			/* unreset */
			val = readl_relaxed(ctrl_base + 0x50);
			val &= ~(0x1 << 17);
			writel_relaxed(val, ctrl_base + 0x50);
		} else {
			/* power down cpu1 */
			val = readl_relaxed(ctrl_base + 0x1000);
			val &=  ~(0x1 << 8);
			val |= (0x1 << 7);
			val |= (0x1 << 3);
			writel_relaxed(val, ctrl_base + 0x1000);

			/* reset */
			val = readl_relaxed(ctrl_base + 0x50);
			val |= (0x1 << 17);
			writel_relaxed(val, ctrl_base + 0x50);
		}
	}
}

void __init hs_hotplug_init(void)
{
	struct device_node *node;

	node = of_find_compatible_node(NULL, NULL, "hisilicon,cpuctrl");
	if (node) {
		ctrl_base = of_iomap(node, 0);
		id = HI3716_CTRL;
		return;
	}
	node = of_find_compatible_node(NULL, NULL, "hisilicon,sctrl");
	if (node) {
		ctrl_base = of_iomap(node, 0);
		id = HI3620_CTRL;
		return;
	}
}

static inline void cpu_enter_lowpower(void)
{
	unsigned int v;

	flush_cache_all();
	asm volatile(
	/*
	 * Turn off coherency and L1 D-cache
	 */
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, #0x40\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	"	mrc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, #0x04\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	  : "=&r" (v)
	  : "r" (0)
	  : "cc");
}

void hs_cpu_die(unsigned int cpu)
{
	cpu_enter_lowpower();
	hs_set_cpu_jump(cpu, phys_to_virt(0));
	cpu_do_idle();

	/* We should have never returned from idle */
	panic("cpu %d unexpectedly exit from shutdown\n", cpu);
}

int hs_cpu_kill(unsigned int cpu)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(50);

	while (hs_get_cpu_jump(cpu))
		if (time_after(jiffies, timeout))
			return 0;
	hs_set_cpu(cpu, false);
	return 1;
}
