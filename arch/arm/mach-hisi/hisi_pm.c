/*
  * arch/arm/mach-hisi/hisi_pm.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License version 2 as
  * published by the Free Software Foundation.
  */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/arm-cci.h>
#include <asm/mcpm.h>
#include <asm/proc-fns.h>
#include <asm/cacheflush.h>
#include <linux/irqchip/arm-gic.h>
#include <asm/psci.h>
#include <asm/cputype.h>
#include <asm/cp15.h>
#include <linux/of_gpio.h>
#include <linux/delay.h>
#include <asm/tlbflush.h>
#if defined(CONFIG_HI3630_LPM3_IPC)
#include "hisi_ipc.h"
#endif

#define RES0_LOCK_OFFSET		(0x400)
#define RES0_UNLOCK_OFFSET	(0x404)
#define RES0_STATUS_OFFSET		(0x408)
#define REG_SCBAKDATA2_OFFSET (0x31C)
#define CLUSTER_OFF_RESIDENCY	(1000)/*this will be fixed*/
#define HISI_MAX_CPUS		4
#define HISI_MAX_CLUSTERS	2

struct hisi_pm_data {
	void __iomem *sctrl_base_addr;
	void __iomem *crg_base_addr;
	void __iomem *pctrl_base_addr;
};

static arch_spinlock_t hisi_pm_lock = __ARCH_SPIN_LOCK_UNLOCKED;
static int hisi_pm_use_count[HISI_MAX_CPUS][HISI_MAX_CLUSTERS];
struct hisi_pm_data g_pm_data;

static int hisi_pm_power_up(u32 cpu, u32 cluster)
{
	struct hisi_pm_data *pm_data_temp = &g_pm_data;

	local_irq_disable();
	arch_spin_lock(&hisi_pm_lock);

	hisi_pm_use_count[cpu][cluster]++;
	if (hisi_pm_use_count[cpu][cluster] == 1) {
		writel(virt_to_phys(mcpm_entry_point), pm_data_temp->sctrl_base_addr + REG_SCBAKDATA2_OFFSET);
	} else if (hisi_pm_use_count[cpu][cluster] == 2) {
		arch_spin_unlock(&hisi_pm_lock);
		local_irq_enable();
		return 0;
	} else {
		BUG();
	}

#if defined(CONFIG_HI3630_LPM3_IPC)
	hisi_ipc_pm_on_off(cpu, cluster, PM_ON);
#endif

	arch_spin_unlock(&hisi_pm_lock);
	local_irq_enable();

	return 0;
}

static void hisi_pm_down(u64 residency)
{
	unsigned int mpidr, cpu, cluster;
	bool last_man = false, skip_wfi = false;

	mpidr = read_cpuid_mpidr();
	cpu = mpidr & 0xff;
	cluster = (mpidr >> 8) & 0xff;

	__mcpm_cpu_going_down(cpu, cluster);
	arch_spin_lock(&hisi_pm_lock);
	hisi_pm_use_count[cpu][cluster]--;
	if (hisi_pm_use_count[cpu][cluster] == 0) {
		if (!hisi_pm_use_count[0][cluster] &&
		    !hisi_pm_use_count[1][cluster] &&
		    !hisi_pm_use_count[2][cluster] &&
		    !hisi_pm_use_count[3][cluster] &&
		    (!residency || residency > CLUSTER_OFF_RESIDENCY)) {
			if (__mcpm_cluster_state(cluster) != CLUSTER_UP) {
				pr_crit("%s: last man but __mcpm_cluster_state(%d) returned %d\n",
					__func__, cluster, __mcpm_cluster_state(cluster));
				BUG();
			}
			last_man = true;
		}
	} else if (hisi_pm_use_count[cpu][cluster] == 1) {
		/*
		 * A power_up request went ahead of us.
		 * Even if we do not want to shut this CPU down,
		 * the caller expects a certain state as if the WFI
		 * was aborted.  So let's continue with cache cleaning.
		 */
		skip_wfi = true;
	} else {
		BUG();
	}

	gic_cpu_if_down();

	if (last_man && __mcpm_outbound_enter_critical(cpu, cluster)) {
		arch_spin_unlock(&hisi_pm_lock);

		set_cr(get_cr() & ~CR_C);
		flush_cache_all();
		asm volatile ("clrex");
		set_auxcr(get_auxcr() & ~(1 << 6));
		local_flush_tlb_all();

		cci_disable_port_by_cpu(mpidr);
		hisi_cci_enable_detect(cluster);

		/*
		 * Ensure that both C & I bits are disabled in the SCTLR
		 * before disabling ACE snoops. This ensures that no
		 * coherency traffic will originate from this cpu after
		 * ACE snoops are turned off.
		 */
		cpu_proc_fin();
		__mcpm_outbound_leave_critical(cluster, CLUSTER_DOWN);
	} else {
		arch_spin_unlock(&hisi_pm_lock);
		set_cr(get_cr() & ~CR_C);
		flush_cache_louis();
		asm volatile ("clrex");
		set_auxcr(get_auxcr() & ~(1 << 6));
		local_flush_tlb_all();
	}
	__mcpm_cpu_down(cpu, cluster);

	if (!skip_wfi) {
#if defined(CONFIG_HI3630_LPM3_IPC)
		hisi_ipc_pm_on_off(cpu, cluster, PM_OFF);
#endif
		if(last_man)
			hisi_cci_enable_detect(cluster);

		dsb();
		while(1)
			wfi();
	}
}

static void hisi_pm_power_down(void)
{
	hisi_pm_down(0);
}

static void hisi_pm_powered_up(void)
{
	unsigned int mpidr, cpu, cluster;
	unsigned long flags;

	mpidr = read_cpuid_mpidr();
	cpu = mpidr & 0xff;
	cluster = (mpidr >> 8) & 0xff;

	local_irq_save(flags);
	arch_spin_lock(&hisi_pm_lock);

	if (!hisi_pm_use_count[cpu][cluster])
		hisi_pm_use_count[cpu][cluster] = 1;

	arch_spin_unlock(&hisi_pm_lock);
	local_irq_restore(flags);
}

static const struct mcpm_platform_ops hisi_pm_power_ops = {
	.power_up	= hisi_pm_power_up,
	.power_down	= hisi_pm_power_down,
	.powered_up	= hisi_pm_powered_up,
};

static void __init hisi_pm_usage_count_init(void)
{
	unsigned int mpidr, cpu, cluster;

	mpidr = read_cpuid_mpidr();
	cpu = mpidr & 0xff;
	cluster = (mpidr >> 8) & 0xff;

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	BUG_ON(cpu >= 4 || cluster >= 2);
	hisi_pm_use_count[cpu][cluster] = 1;
}

extern void hisi_pm_power_up_setup(unsigned int affinity_level);

static int __init hisi_pm_init(void)
{
	int ret = 0;
	struct device_node *np = NULL;
	struct hisi_pm_data *pm_data_temp = &g_pm_data;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np) {
		pr_err("%s: hisilicon,sysctrl No compatible node found\n", __func__);
		return -ENODEV;
	}
	pm_data_temp->sctrl_base_addr = of_iomap(np, 0);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (!np) {
		pr_err("%s: hisilicon,crgctrl No compatible node found\n", __func__);
		ret = -ENODEV;
		goto unmap_sctrl;
	}
	pm_data_temp->crg_base_addr = of_iomap(np, 0);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	if (!np) {
		pr_err("%s: hisilicon,pctrl No compatible node found\n", __func__);
		ret = -ENODEV;
		goto unmap_crg;
	}
	pm_data_temp->pctrl_base_addr = of_iomap(np, 0);

	hisi_pm_usage_count_init();

	ret = mcpm_platform_register(&hisi_pm_power_ops);
	if (ret) {
		pr_err("HISI PM:platform_ops has been registered.\n");
		goto unmap_pctrl;
	}

	ret = mcpm_sync_init(hisi_pm_power_up_setup);
	if (ret)
		goto unmap_pctrl;
	pr_info("HISI power management initialized\n");

	return ret;
unmap_pctrl:
	iounmap(pm_data_temp->pctrl_base_addr);
unmap_crg:
	iounmap(pm_data_temp->crg_base_addr);
unmap_sctrl:
	iounmap(pm_data_temp->sctrl_base_addr);
	return ret;
}

early_initcall(hisi_pm_init);
MODULE_DESCRIPTION("Hisilicon power management driver");
MODULE_AUTHOR("zhanjun 00183814");
MODULE_LICENSE("GPL");
