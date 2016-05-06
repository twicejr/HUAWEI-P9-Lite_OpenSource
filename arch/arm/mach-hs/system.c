/*
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2013 Hisilicon Limited.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */
#include <linux/io.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>

#include <asm/proc-fns.h>
#include <asm/smp_plat.h>

#include "core.h"

void __iomem *hs_sctrl_base;
static int hs_smp_reg;
static int hs_resume_reg;
static int hs_reboot_reg;

void hs_map_io(void)
{
	struct device_node *np;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sctrl");
	if (np) {
		hs_sctrl_base = of_iomap(np, 0);
		if (!hs_sctrl_base)
			pr_err("of_iomap(sctrl_base) failed\n");
		of_property_read_u32(np, "smp_reg", &hs_smp_reg);
		of_property_read_u32(np, "resume_reg", &hs_resume_reg);
		of_property_read_u32(np, "reboot_reg", &hs_reboot_reg);
	}
}

void hs_set_cpu_jump(int cpu, void *jump_addr)
{
	int offset = hs_smp_reg;

	cpu = cpu_logical_map(cpu);
	if (cpu > 0)
		offset +=  0x04 * (cpu - 1);
	writel_relaxed(virt_to_phys(jump_addr), hs_sctrl_base + offset);
}

int hs_get_cpu_jump(int cpu)
{
	int offset = hs_smp_reg;

	cpu = cpu_logical_map(cpu);
	if (cpu > 0)
		offset +=  0x04 * (cpu - 1);
	return readl_relaxed(hs_sctrl_base + offset);
}

void hs_restart(char mode, const char *cmd)
{
	writel_relaxed(0xdeadbeef, hs_sctrl_base + hs_reboot_reg);

	while (1)
		cpu_do_idle();
}

