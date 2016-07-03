/*
 * ARM64 generic CPU idle driver.
 *
 * Copyright (C) 2014 ARM Ltd.
 * Author: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "CPUidle arm64: " fmt

#include <linux/cpuidle.h>
#include <linux/cpumask.h>
#include <linux/cpu_pm.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/slab.h>

#include <asm/cpuidle.h>
#include <asm/suspend.h>
#include <linux/sched.h>

#include "dt_idle_states.h"
#ifdef CONFIG_HISI_CORESIGHT_TRACE
#include <linux/coresight.h>
#endif

enum {
	LITTLE_CLUSTER_ID = 0,
	BIG_CLUSTER_ID,
	MAX_CLUSTER_ID,
};

/*
 * hisi_enter_idle_state - Programs CPU to enter the specified state
 *
 * dev: cpuidle device
 * drv: cpuidle driver
 * idx: state index
 *
 * Called from the CPUidle framework to program the device to the
 * specified target state selected by the governor.
 */
static int hisi_enter_idle_state(struct cpuidle_device *dev,
				  struct cpuidle_driver *drv, int idx)
{
	int ret;

	if (need_resched()) {
		return idx;
	}

	if (!idx) {
		cpu_do_idle();
		return idx;
	}

	ret = cpu_pm_enter();
	if (!ret) {
#ifdef CONFIG_ARCH_HISI
		local_fiq_disable();
#endif
		/*
		 * Pass idle state index to cpu_suspend which in turn will
		 * call the CPU ops suspend protocol with idle index as a
		 * parameter.
		 */
		ret = cpu_suspend(idx);
#ifdef CONFIG_HISI_CORESIGHT_TRACE
		/*Restore ETM registers */
		_etm4_cpuilde_restore();
#endif
#ifdef CONFIG_ARCH_HISI
		local_fiq_enable();
#endif
		cpu_pm_exit();
	}

	return ret ? -1 : idx;
}

static struct cpuidle_driver hisi_little_cluster_idle_driver = {
	.name = "hisi_little_cluster_idle",
	.owner = THIS_MODULE,
	/*
	 * State at index 0 is standby wfi and considered standard
	 * on all ARM platforms. If in some platforms simple wfi
	 * can't be used as "state 0", DT bindings must be implemented
	 * to work around this issue and allow installing a special
	 * handler for idle state index 0.
	 */
	.states[0] = {
		.enter                  = hisi_enter_idle_state,
		.exit_latency           = 1,
		.target_residency       = 1,
		.power_usage		= UINT_MAX,
		.flags                  = CPUIDLE_FLAG_TIME_VALID,
		.name                   = "WFI",
		.desc                   = "ARM64 WFI",
	}
};
static struct cpuidle_driver hisi_big_cluster_idle_driver = {
	.name = "hisi_big_cluster_idle",
	.owner = THIS_MODULE,
	/*
	 * State at index 0 is standby wfi and considered standard
	 * on all ARM platforms. If in some platforms simple wfi
	 * can't be used as "state 0", DT bindings must be implemented
	 * to work around this issue and allow installing a special
	 * handler for idle state index 0.
	 */
	.states[0] = {
		.enter                  = hisi_enter_idle_state,
		.exit_latency           = 1,
		.target_residency       = 1,
		.power_usage		= UINT_MAX,
		.flags                  = CPUIDLE_FLAG_TIME_VALID,
		.name                   = "WFI",
		.desc                   = "ARM64 WFI",
	}
};

static const struct of_device_id arm64_idle_state_match[] __initconst = {
	{ .compatible = "arm,idle-state",
	  .data = hisi_enter_idle_state },
	{ },
};

static int __init hisi_idle_drv_cpumask_init(struct cpuidle_driver *drv, int cluster_id)
{
	struct cpumask *cpumask;
	int cpu;

	cpumask = kzalloc(cpumask_size(), GFP_KERNEL);
	if (!cpumask)
		return -ENOMEM;

	for_each_possible_cpu(cpu) {
		if (cpu_topology[cpu].cluster_id == cluster_id)
			cpumask_set_cpu(cpu, cpumask);
	}

	drv->cpumask = cpumask;

	return 0;
}

static void __init hisi_idle_drv_cpumask_uninit(struct cpuidle_driver *drv)
{
	kfree(drv->cpumask);
}

static int __init hisi_idle_drv_init(struct cpuidle_driver *drv)
{
	int cpu, ret;

	/*
	 * Initialize idle states data, starting at index 1.
	 * This driver is DT only, if no DT idle states are detected (ret == 0)
	 * let the driver initialization fail accordingly since there is no
	 * reason to initialize the idle driver if only wfi is supported.
	 */
	ret = dt_init_idle_driver(drv, arm64_idle_state_match, 1);
	if (ret <= 0) {
		if (ret)
			pr_err("failed to initialize idle states\n");
		return ret ? : -ENODEV;
	}

	/*
	 * Call arch CPU operations in order to initialize
	 * idle states suspend back-end specific data
	 */
	for_each_possible_cpu(cpu) {
		ret = cpu_init_idle(cpu);
		if (ret) {
			pr_err("CPU %d failed to init idle CPU ops\n", cpu);
			return ret;
		}
	}

	ret = cpuidle_register(drv, NULL);
	if (ret) {
		pr_err("failed to register cpuidle driver\n");
		return ret;
	}

	return 0;
}

static int __init hisi_multidrv_idle_init(struct cpuidle_driver *drv, int cluster_id)
{
	int ret;
	if (cluster_id >= MAX_CLUSTER_ID) {
		pr_err("cluster id is out of range.\n");
		return -ENODEV;
	}

	ret = hisi_idle_drv_cpumask_init(drv, cluster_id);
	if (ret) {
		pr_err("fail to init idle driver!\n");
		return ret;
	}

	ret = hisi_idle_drv_init(drv);
	if (ret) {
		hisi_idle_drv_cpumask_uninit(drv);
		pr_err("fail to register cluster%d cpuidle drv.\n", cluster_id);
		return ret;
	}

	return 0;
}



/*
 * hisi_idle_init
 *
 * Registers the hisi multi cpuidle driver with the cpuidle
 * framework. It relies on core code to parse the idle states
 * and initialize them using driver data structures accordingly.
 */
static int __init hisi_idle_init(void)
{
	int ret;

	ret = hisi_multidrv_idle_init(&hisi_little_cluster_idle_driver, LITTLE_CLUSTER_ID);
	if (ret) {
		pr_err("fail to register little cluster cpuidle drv.\n");
		return ret;
	}

	ret = hisi_multidrv_idle_init(&hisi_big_cluster_idle_driver, BIG_CLUSTER_ID);
	if (ret) {
		pr_err("fail to register little cluster cpuidle drv.\n");
		return ret;
	}

	return 0;
}
device_initcall(hisi_idle_init);
