/*
 * big.LITTLE CPU idle driver.
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/arm-cci.h>
#include <linux/bitmap.h>
#include <linux/cpuidle.h>
#include <linux/cpu_pm.h>
#include <linux/clockchips.h>
#include <linux/debugfs.h>
#include <linux/hrtimer.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/tick.h>
#include <linux/vexpress.h>
#include <asm/mcpm.h>
#include <asm/cpuidle.h>
#include <asm/cputype.h>
#include <asm/idmap.h>
#include <asm/proc-fns.h>
#include <asm/suspend.h>
#include <linux/of.h>
#include <asm/smp_plat.h>
#include <asm/cputype.h>
#include <linux/hisi/pm/pwrctrl_multi_def.h>
#include <linux/hisi/pm/hi6xxx-power-common.h>
/*#include "drv_ipcm.h"*/
#include <linux/hisi/pm/pwrctrl_multi_memcfg.h>



/*#define CPUIDLE_DEBUG*/
#define MAX_CPU_NR		8

#define RUNNING_STATE_IDX	-1
#define CLUSTER_DOWN_IDX	2

#define CLUSTER_DOWN_ENABLE 1
static int bl_cpuidle_cpu_desired_state[MAX_CPU_NR];


/* extern functions */
extern void get_resource_lock(unsigned int cluster, unsigned int core);
extern void put_resource_lock(unsigned int cluster, unsigned int core);
extern void set_cluster_idle_bit(unsigned int cluster);
extern int is_hi6210(void);
extern void hisi_pm_cci_enable(unsigned int id);
static int bl_cpuidle_simple_enter(struct cpuidle_device *dev, struct cpuidle_driver *drv, int index);

int bl_cpuidle_simple_enter(struct cpuidle_device *dev,
		struct cpuidle_driver *drv, int index)
{
#if defined(CPUIDLE_DEBUG)
    int cpuid = smp_processor_id();
    printk(KERN_DEBUG"%s cpu:%d enter\n",__FUNCTION__ , cpuid);
#endif
	cpu_do_idle();
	return index;
}

static int bl_enter_powerdown(struct cpuidle_device *dev,
				struct cpuidle_driver *drv, int idx);

#ifdef CLUSTER_DOWN_ENABLE
static int bl_enter_cluster_powerdown(struct cpuidle_device *dev,
				struct cpuidle_driver *drv, int idx);
#endif

static struct cpuidle_state bl_cpuidle_set[] __initdata = {
	[0] = {
		.enter                  = bl_cpuidle_simple_enter,
		.exit_latency           = 1,
		.target_residency       = 1,
		.power_usage		= UINT_MAX,
		.flags                  = CPUIDLE_FLAG_TIME_VALID,
		.name                   = "WFI",
		.desc                   = "ARM WFI",
	},
	[1] = {
		.enter			= bl_enter_powerdown,
		.exit_latency		= 500,
		.target_residency	= 1000,
		.flags			= CPUIDLE_FLAG_TIME_VALID |
					  CPUIDLE_FLAG_TIMER_STOP,
		.name			= "C1",
		.desc			= "ARM power down",
	},
#ifdef CLUSTER_DOWN_ENABLE
	/* the exit_latency & target_residency is test value. */
	[2] = {
		.enter			= bl_enter_cluster_powerdown,
		.exit_latency		= 5000,/*10*/
		.target_residency	= 15000,/*100*/
		.flags			= CPUIDLE_FLAG_TIME_VALID |
					  CPUIDLE_FLAG_TIMER_STOP,
		.name			= "C2",
		.desc			= "cluster power down",
	},
#endif
#ifdef CLUSTER_SLEEP_ENABLE
	/* the exit_latency & target_residency is test value. */
	[3] = {
		.enter			= bl_enter_cluster_powerdown,
		.exit_latency		= 10000,
		.target_residency	= 400000,
		.flags			= CPUIDLE_FLAG_TIME_VALID |
					  CPUIDLE_FLAG_TIMER_STOP,
		.name			= "C3",
		.desc			= "cluster sleep",
	},
#endif
};

static struct cpuidle_driver bl_idle_driver = {
	.name = "bl_idle",
	.owner = THIS_MODULE,
	.safe_state_index = 0
};

static DEFINE_PER_CPU(struct cpuidle_device, bl_idle_dev);

#ifdef CLUSTER_DOWN_ENABLE
static int notrace bl_finisher(unsigned long arg)
{
	unsigned int mpidr = read_cpuid_mpidr();
	unsigned int cluster = (mpidr >> 8) & 0xf;
	unsigned int cpu = mpidr & 0xf;

	mcpm_set_entry_vector(cpu, cluster, cpu_resume);
	/*BSP_IPC_SpinLock(IPC_SEM_CPUIDLE);*/
	set_cluster_idle_bit(cluster);
	/*BSP_IPC_SpinUnLock(IPC_SEM_CPUIDLE);*/
	mcpm_cpu_suspend(arg);

	return 1;
}

#define CLUSTER_MASK		0xff00

extern ktime_t menu_state_ok_until(int cpuid);

static int check_other_cpus(ktime_t when, struct cpuidle_driver *drv, int idx)
{
	unsigned int cpu = smp_processor_id();
	unsigned long mpidr = cpu_logical_map(cpu);
	unsigned int cluster = mpidr & CLUSTER_MASK;
	unsigned int i;

	for_each_cpu(i, cpu_online_mask) {
		if ( (cpu_logical_map(i) & CLUSTER_MASK) != cluster)
			continue;

		if (cpu_logical_map(i) == mpidr)
			continue;

		/* if not cpudown, bail out */
		if (bl_cpuidle_cpu_desired_state[i] < CLUSTER_DOWN_IDX)
			return -EPERM;
	}

	return 0;
}

int bl_enter_cluster_powerdown(struct cpuidle_device *dev,
				struct cpuidle_driver *drv, int idx)
{
	int ret;

#if defined(CPUIDLE_DEBUG)
    int cpuid = smp_processor_id();

    if(cpuid == 9)
    {
        cpu_do_idle();
        return idx;
    }
    printk(KERN_ERR"%s cpu:%d enter\n",__FUNCTION__ , cpuid);
#endif
	BUG_ON(!irqs_disabled());

	/* if cluster powerdown conditions is not statified,
	 * then power down the cpu instead.
	 */

	bl_cpuidle_cpu_desired_state[smp_processor_id()] = CLUSTER_DOWN_IDX;

	if (check_other_cpus(ktime_get(), drv, idx))
		return drv->states[idx - 1].enter(dev, drv, idx - 1);

	cpu_pm_enter();

	ret = cpu_suspend(idx - 1, bl_finisher);
	if (ret)
		BUG();

    /*hisi_pm_cci_enable((smp_processor_id()>=4)?1:0);*/
    /*printk(KERN_ERR"%s cpu:%d cci en 2.\n",__FUNCTION__ , cpuid);*/
	bl_cpuidle_cpu_desired_state[smp_processor_id()] = RUNNING_STATE_IDX;

	mcpm_cpu_powered_up();

	cpu_pm_exit();

	return idx;
}
#endif

static int notrace bl_powerdown_finisher(unsigned long arg)
{
	unsigned int mpidr = read_cpuid_mpidr();
	unsigned int cluster = (mpidr >> 8) & 0xf;
	unsigned int cpu = mpidr & 0xf;

	mcpm_set_entry_vector(cpu, cluster, cpu_resume);
	mcpm_cpu_suspend(0);  /* 0 AFFINITY0 */
	return 1;
}

/*
 * bl_enter_powerdown - Programs CPU to enter the specified state
 * @dev: cpuidle device
 * @drv: The target state to be programmed
 * @idx: state index
 *
 * Called from the CPUidle framework to program the device to the
 * specified target state selected by the governor.
 */
int bl_enter_powerdown(struct cpuidle_device *dev,
				struct cpuidle_driver *drv, int idx)
{
	int ret;
	int cpuid = smp_processor_id();

#if defined(CPUIDLE_DEBUG)
    if(cpuid == 9)
    {
        cpu_do_idle();
        return idx;
    }
    printk(KERN_DEBUG"%s cpu:%d enter\n",__FUNCTION__ , cpuid);
#endif

	BUG_ON(!irqs_disabled());

	cpu_pm_enter();

	ret = cpu_suspend((unsigned long) dev, bl_powerdown_finisher);
	if (ret)
		BUG();

    /*hisi_pm_cci_enable((smp_processor_id()>=4)?1:0);*/
    /*printk(KERN_ERR"%s cpu:%d cci en 1.\n",__FUNCTION__ , cpuid);*/
	bl_cpuidle_cpu_desired_state[cpuid] = RUNNING_STATE_IDX;

	mcpm_cpu_powered_up();

	cpu_pm_exit();

	return idx;
}

/*
 * bl_idle_init
 *
 * Registers the bl specific cpuidle driver with the cpuidle
 * framework with the valid set of states.
 */

static int __init bl_idle_init(void)
{
	struct cpuidle_device *dev;
	int i, cpu_id;
	struct cpuidle_driver *drv = &bl_idle_driver;

    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_CPUIDLE))
    {
		pr_err("%s: cpuidle switch is not on\n", __func__);
        return -ENODEV;
    }

	if (!of_find_compatible_node(NULL, NULL, "arm,generic")) {
		pr_info("%s: No compatible node found\n", __func__);
		return -ENODEV;
	}
	drv->state_count = (sizeof(bl_cpuidle_set) /
				       sizeof(struct cpuidle_state));

	for (i = 0; i < MAX_CPU_NR; i++)
		bl_cpuidle_cpu_desired_state[i] = RUNNING_STATE_IDX;

	for (i = 0; i < drv->state_count; i++) {
		memcpy(&drv->states[i], &bl_cpuidle_set[i],
				sizeof(struct cpuidle_state));
	}

	cpuidle_register_driver(drv);

	for_each_cpu(cpu_id, cpu_online_mask) {
		pr_err("CPUidle for CPU%d registered\n", cpu_id);
		dev = &per_cpu(bl_idle_dev, cpu_id);
		dev->cpu = cpu_id;

		dev->state_count = drv->state_count;

		if (cpuidle_register_device(dev)) {
			printk(KERN_ERR "%s: Cpuidle register device failed\n",
			       __func__);
			return -EIO;
		}
	}

	return 0;
}

device_initcall(bl_idle_init);
