/*
  * arch/arm/mach-hisi/hisi_pm_psci.c
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
#include <linux/platform_device.h>
#include <linux/irqchip/arm-gic.h>
#include <asm/mcpm.h>
#include <asm/proc-fns.h>
#include <asm/cacheflush.h>
#include <asm/psci.h>
#include <asm/atomic.h>
#include <asm/cputype.h>
#include <asm/cp15.h>
#include <linux/arm-cci.h>
#include <linux/of_address.h>

#define PSCI_POWER_STATE_ID     (0)
#define HISI_MAX_CPUS		(4)
#define HISI_MAX_CLUSTERS	(2)
#define CLUTER_OFF_RESIDENCY (3000)
#define SLEEP_OFF_RESIDENCY (5000)

static atomic_t hisi_pm_use_count[HISI_MAX_CPUS][HISI_MAX_CLUSTERS];
static arch_spinlock_t hisi_pm_lock = __ARCH_SPIN_LOCK_UNLOCKED;

/* sysctrl and pctrl base  */
static void __iomem *sysctrl_base;
static void __iomem *pctrl_base;


#define RES0_LOCK_OFF	0x400
#define RES0_UNLOCK_OFF	0x404
#define RES0_LOCK_STAT_OFF	0x408

#define RES1_LOCK_OFF	0x40c
#define RES1_UNLOCK_OFF	0x410
#define RES1_LOCK_STAT_OFF	0x414

#define RES_LOCK_OFF(cluster)  (cluster == 0 ? RES0_LOCK_OFF : RES1_LOCK_OFF)
#define RES_UNLOCK_OFF(cluster)  (cluster == 0 ? RES0_UNLOCK_OFF : RES1_UNLOCK_OFF)
#define RES_LOCK_STAT_OFF(cluster)  (cluster == 0 ? RES0_LOCK_STAT_OFF : RES1_LOCK_STAT_OFF)

#define LOCK_BIT		(0x1 << 28)
#define LOCK_ID_MASK	(0x7 << 29)
#define LOCK_ID(core)	((0x6 - core)  << 29)
#define	LOCK_VAL(core)		(LOCK_ID(core) | LOCK_BIT)


#define SCBAKDATA8_OFFSET	0x334
#define SCBAKDATA9_OFFSET	0x338
/* scbakdata8 and scbakdata9  are used for cluster 0 and 1 */
#define CLUSTER_IDLE_STAT(cluster)  (cluster == 0 ? SCBAKDATA8_OFFSET : SCBAKDATA9_OFFSET)

/* core idle bit */
#define	CORE_IDLE_BIT(core)		(0x1 << core)
/* cluster idle bit */
#define CLUSTER_IDLE_BIT		 (0x1 << 8)
#define CLUSTER_IDLE_MASK	((0xf) | CLUSTER_IDLE_BIT)

void get_resource_lock(unsigned int cluster, unsigned int core)
{
	do {
		writel(LOCK_VAL(core), pctrl_base + RES_LOCK_OFF(cluster));
	} while((readl(pctrl_base + RES_LOCK_STAT_OFF(cluster)) & LOCK_ID_MASK) != LOCK_ID(core));
}
EXPORT_SYMBOL(get_resource_lock);

void put_resource_lock(unsigned int cluster, unsigned int core)
{
	writel(LOCK_VAL(core), pctrl_base + RES_UNLOCK_OFF(cluster));
}
EXPORT_SYMBOL(put_resource_lock);

void set_cluster_idle_bit(unsigned int cluster)
{
	unsigned long cluster_state;

	cluster_state = readl(sysctrl_base + CLUSTER_IDLE_STAT(cluster));
	cluster_state |= CLUSTER_IDLE_BIT;
	writel(cluster_state, sysctrl_base + CLUSTER_IDLE_STAT(cluster));
}
EXPORT_SYMBOL(set_cluster_idle_bit);


static void hisi_core_exit_coherence(void)
{
	set_cr(get_cr() & ~CR_C);
	flush_cache_louis();
}

static void hisi_cluster_exit_coherence(u32 cluster)
{
	set_cr(get_cr() & ~CR_C);

	if (cluster == 0) {
		asm volatile (
			"mov    ip, #0x400 \n\t"
			"mcr    p15, 1, ip, c15, c0, 3 \n\t"
			"dsb \n\t"
			"isb"
			: : : "ip");
	}
	flush_cache_all();
	asm volatile ("clrex");
	/*
	 * Ensure that both C & I bits are disabled in the SCTLR
	 * before disabling ACE snoops. This ensures that no
	 * coherency traffic will originate from this cpu after
	 * ACE snoops are turned off.
	 */
	//cpu_proc_fin();
}

static void hisi_pm_psci_system_off(void)
{
	BUG_ON(!psci_ops.system_off);

	psci_ops.system_off();

	while(1)
		asm volatile ("wfi");

	return ;
}

static int hisi_pm_psci_power_up(unsigned int cpu, unsigned int cluster)
{
	unsigned int mpidr = (cluster << 8) | cpu;
	int ret = 0;

	BUG_ON(!psci_ops.cpu_on);

	local_irq_disable();
	arch_spin_lock(&hisi_pm_lock);
	switch (atomic_inc_return(&hisi_pm_use_count[cpu][cluster])) {
	case 1:
		/*
		 * This is a request to power up a cpu that linux thinks has
		 * been powered down. Retries are needed if the firmware has
		 * seen the power down request as yet.
		 */
		local_irq_enable();
		arch_spin_unlock(&hisi_pm_lock);
		do {
			ret = psci_ops.cpu_on(mpidr,
					      virt_to_phys(mcpm_entry_point));
		} while (ret == -EAGAIN);

		return ret;
	case 2:
		/* This power up request has overtaken a power down request */
		local_irq_enable();
		arch_spin_unlock(&hisi_pm_lock);
		return ret;
	default:
		/* Any other value is a bug */
		BUG();
	}
}

static void hisi_pm_psci_power_down(void)
{
	struct psci_power_state power_state;
	unsigned int mpidr, cpu, cluster;

	mpidr = read_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	BUG_ON(!psci_ops.cpu_off);
	arch_spin_lock(&hisi_pm_lock);
	switch (atomic_dec_return(&hisi_pm_use_count[cpu][cluster])) {
	case 1:
		/*
		 * Overtaken by a power up. Flush caches, exit coherency,
		 * return & fake a reset
		 */
		arch_spin_unlock(&hisi_pm_lock);
		hisi_core_exit_coherence();
		set_auxcr(get_auxcr() & ~(1 << 6));
		return;
	case 0:
		/* A normal request to possibly power down the cluster */
		power_state.id = PSCI_POWER_STATE_ID;
		power_state.type = PSCI_POWER_STATE_TYPE_POWER_DOWN;
		power_state.affinity_level = PSCI_POWER_STATE_AFFINITY_LEVEL1;
		gic_cpu_if_down();
		if (!atomic_read(&hisi_pm_use_count[0][cluster])&&
			!atomic_read(&hisi_pm_use_count[1][cluster]) &&
			!atomic_read(&hisi_pm_use_count[2][cluster]) &&
			!atomic_read(&hisi_pm_use_count[3][cluster])) {
				arch_spin_unlock(&hisi_pm_lock);
				hisi_cluster_exit_coherence(cluster);
			} else {
				arch_spin_unlock(&hisi_pm_lock);
				hisi_core_exit_coherence();
		}
		psci_ops.cpu_off(power_state);
		return;
	default:
		/* Any other value is a bug */
		BUG();
	}
}

static void hisi_pm_psci_suspend(u64 unused)
{
	struct psci_power_state power_state;
	unsigned int mpidr, cluster, core;
	unsigned long cluster_state = 0;

	mpidr = read_cpuid_mpidr();
	core = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	BUG_ON(!psci_ops.cpu_suspend);

	gic_cpu_if_down();

	pr_debug("[%s] mpidr = 0x%x, affinity_level = %d\n", __func__, mpidr, (u32)unused);

	if (unused != PSCI_POWER_STATE_AFFINITY_LEVEL3) {
		/* sync with lpm3 */
		get_resource_lock(cluster, core);

		/* set the core down bit */
		cluster_state = readl(sysctrl_base + CLUSTER_IDLE_STAT(cluster));
		cluster_state |= CORE_IDLE_BIT(core);
		writel(cluster_state, sysctrl_base + CLUSTER_IDLE_STAT(cluster));

		cluster_state = readl(sysctrl_base + CLUSTER_IDLE_STAT(cluster));
		if ((cluster_state & CLUSTER_IDLE_MASK) == CLUSTER_IDLE_MASK) {
			hisi_cluster_exit_coherence(cluster);
		} else {
			unused = PSCI_POWER_STATE_AFFINITY_LEVEL0;
		}

		put_resource_lock(cluster, core);
	} else {
		hisi_cluster_exit_coherence(cluster);
	}

	if (unused == PSCI_POWER_STATE_AFFINITY_LEVEL0)
		hisi_core_exit_coherence();

	/* construct idle power state */
	power_state.id = PSCI_POWER_STATE_ID;
	power_state.type = PSCI_POWER_STATE_TYPE_POWER_DOWN;
	power_state.affinity_level = (u8)unused;

	psci_ops.cpu_suspend(power_state, virt_to_phys(mcpm_entry_point));

	/* On success this function never returns */
	BUG();
}

static const struct mcpm_platform_ops hisi_pm_power_ops = {
	.power_up      = hisi_pm_psci_power_up,
	.power_down    = hisi_pm_psci_power_down,
	.suspend       = hisi_pm_psci_suspend,
};

static void __init hisi_pm_usage_count_init(void)
{
	unsigned int mpidr, cpu, cluster;

	mpidr = read_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);

	atomic_set(&hisi_pm_use_count[cpu][cluster], 1);
}

static int __init hisi_pm_psci_init(void)
{
	struct device_node *np;
	int ret;

	ret = psci_probe();
	if (ret) {
		pr_err("psci not found. Aborting psci init\n");
		return -ENODEV;
	}

	pm_power_off = hisi_pm_psci_system_off;

	hisi_pm_usage_count_init();

	if (sysctrl_base == NULL) {
		np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
		if (!np) {
			pr_err("get sysctrl node error !\n");
			BUG_ON(1);
			return -ENODEV;
		}
		sysctrl_base = of_iomap(np, 0);
		BUG_ON(!sysctrl_base);
	}

	if (pctrl_base == NULL) {
		np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
		if (!np) {
			pr_err("get pctrl node error !\n");
			BUG_ON(1);
			return -ENODEV;
		}
		pctrl_base = of_iomap(np, 0);
		BUG_ON(!pctrl_base);
	}

	ret = mcpm_platform_register(&hisi_pm_power_ops);
	if (!ret)
		ret = mcpm_sync_init(NULL);
	if (!ret)
		pr_info("Hisilicon psci power management initialized\n");

	return ret;
}

early_initcall(hisi_pm_psci_init);
MODULE_DESCRIPTION("Hisilicon psci power management driver");
MODULE_AUTHOR("zhanjun 00183814");
MODULE_LICENSE("GPL");
