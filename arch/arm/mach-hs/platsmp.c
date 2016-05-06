/*
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2013 Hisilicon Limited.
 * Based on platsmp.c, Copyright (C) 2002 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */
#include <linux/smp.h>
#include <linux/io.h>
#include <asm/smp_scu.h>

#include "core.h"

static void __init hs_smp_prepare_cpus(unsigned int max_cpus)
{
	unsigned long base;
	void __iomem *scu_base;

	if (scu_a9_has_base()) {
		base = scu_a9_get_base();
		scu_base = ioremap(base, SZ_4K);
		if (!scu_base) {
			pr_err("ioremap(scu_base) failed\n");
			return;
		}
		scu_enable(scu_base);
		iounmap(scu_base);
	}
}

static int hs_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	hs_set_cpu(cpu, true);
	hs_set_cpu_jump(cpu, secondary_startup);
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));
	return 0;
}

struct smp_operations hs_smp_ops __initdata = {
	.smp_prepare_cpus	= hs_smp_prepare_cpus,
	.smp_boot_secondary	= hs_boot_secondary,
#ifdef CONFIG_HOTPLUG_CPU
	.cpu_die		= hs_cpu_die,
	.cpu_kill		= hs_cpu_kill,
#endif
};
