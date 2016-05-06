/*
 *  linux/arch/arm/mach-k3v2/cpu-k3v2.c
 *
 *  CPU frequency scaling for K3V2
 *
 *  Copyright (C) 2005 Nokia Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cpu.h>
#include <linux/cpufreq.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <asm/system.h>
#include <linux/pm_qos_params.h>
#include <linux/ipps.h>
#include <linux/cpufreq-k3v2.h>
#include <mach/boardid.h>
#include <linux/switch.h>
#include "pwrctrl_multi_memcfg.h"
#include "pwrctrl_multi_dfs_asm.h"
#include <linux/interrupt.h>
#include "soc_irqs.h"

#if defined(CHIP_BB_HI6210)
#define SOC_SRAM_ON_BASE_ADDR         (TEEOS_SRAM_ADDR)
#endif

struct switch_dev policy_switch;

static struct ipps_device *gpipps_device;
static struct ipps_client ipps_client;

/*cpufreq table must be sorted by asc*/
struct cpufreq_frequency_table *cpufreq_table;

/*gpufreq table must be sorted by asc*/
struct cpufreq_frequency_table *gpufreq_table;

/*ddrfreq table must be sorted by asc*/
struct cpufreq_frequency_table *ddrfreq_table;

/*busfreq table must be sorted by asc*/
struct cpufreq_frequency_table *busfreq_table;

static struct pm_qos_request_list g_ippspolicy;

struct ipps_param gipps_param;
struct ipps_param_stru gipps_param_stru;

#ifdef CONFIG_LOWPM_DEBUG
	#undef CONFIG_LOWPM_DEBUG
#endif

#if 0
#ifdef CONFIG_LOWPM_DEBUG
extern struct ipps_param_stru gdbgipps_param_stru;
#endif
#endif

struct cpu_num_limit gcpu_num_limit = {
        .max = NR_CPUS,
        .min = 1,
        .block = 0,
};


struct ipps_param gdbgipps_param;
struct ipps_param_stru gdbgipps_param_stru;

#define CPU_FREQ_MIN (200000)

/********************Qos notifier begin*********************/
static int cpumaxprofile_notify(struct notifier_block *b,
		unsigned long l, void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       PARAM_MAX_TYPE(ipps_param_stru);
	PARAM_MAX(cpu) = l;

	pr_debug("[%s] in=%lu, profile=%d\n", __func__, l, PARAM_MAX(cpu));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->cpu.max_freq != 0) {
	    PARAM_MAX_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
#endif

	return 0;
}

static struct notifier_block cpumaxprofile_notifier = {
	.notifier_call = cpumaxprofile_notify,
};

static int cpuminprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       PARAM_MIN_TYPE(ipps_param_stru);
	PARAM_MIN(cpu) = l;

	pr_debug("[%s] cpu_min=%d\n", __func__, PARAM_MIN(cpu));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->cpu.min_freq != 0) {
	    PARAM_MIN_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
#endif

	return 0;
}

static struct notifier_block cpuminprofile_notifier = {
	.notifier_call = cpuminprofile_notify,
};

static int cpublockprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       PARAM_BLOCK_TYPE(ipps_param_stru);
	PARAM_BLOCK(cpu) = l;

	pr_debug("[%s] cpu_block=%d.\n", __func__, PARAM_BLOCK(cpu));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->cpu.max_freq != 0 || gdbgipps_param_stru.ipps_param->cpu.min_freq != 0) {
	    PARAM_BLOCK_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
#endif

	return 0;
}

static struct notifier_block cpublockprofile_notifier = {
	.notifier_call = cpublockprofile_notify,
};

static int cpusafeprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);

       PARAM_SAFE_TYPE(ipps_param_stru);
	PARAM_SAFE(cpu) = l;

	pr_debug("[%s] cpu_safe=%d.\n", __func__, PARAM_SAFE(cpu));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->cpu.safe_freq != 0){
	    PARAM_SAFE_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
#endif


	return 0;
}

static struct notifier_block cpusafeprofile_notifier = {
	.notifier_call = cpusafeprofile_notify,
};

/*bus dfs*/

static int busmax_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	PARAM_MAX_TYPE(ipps_param_stru);
	PARAM_MAX(bus) = l;

	pr_debug("[%s] in=%lu, profile=%d\n", __func__, l, PARAM_MAX(bus));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->cpu.max_freq != 0) {
	    PARAM_MAX_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_BUS, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_BUS, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_BUS, &ipps_param_stru);
#endif

	return 0;
}

static struct notifier_block busmaxprofile_notifier = {
	.notifier_call = busmax_notify,
};

static int busmin_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	PARAM_MIN_TYPE(ipps_param_stru);
	PARAM_MIN(bus) = l;

	pr_debug("[%s] bus_min=%d\n", __func__, PARAM_MIN(bus));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->bus.min_freq != 0) {
	    PARAM_MIN_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_BUS, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_BUS, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_BUS, &ipps_param_stru);
#endif

	return 0;
}

static struct notifier_block busminprofile_notifier = {
	.notifier_call = busmin_notify,
};
/*bus dfs end*/

/*Int vote*/
static int cpuidle_int_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
	int int_value = 0;

	pr_debug("[%s] in=%lu\n", __func__, l);

	int_value = (int)l;

    /*don't need implement now*/
	/*调用cpuidle投票接口，将总线投票值传给总线投票模块*/

	return 0;
}

static struct notifier_block cpuilde_int_notifier = {
	.notifier_call = cpuidle_int_notify,
};
/*Int vote end*/
/**
*  cpu max number lock handle.
*/
static inline void cpumax_handle(void)
{
	int cpu_online_num = num_online_cpus();

	if (gcpu_num_limit.block != 0)
		return;

	while (gcpu_num_limit.max < cpu_online_num) {
		cpu_down(cpu_online_num-1);
		cpu_online_num = num_online_cpus();
	}
}

static int cpunumbermax_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
	int cpumax = 0;

	pr_debug("[%s] in=%lu\n", __func__, l);

	cpumax = (int)l;

	if (cpumax > num_possible_cpus())
		cpumax = num_possible_cpus();

	if (cpumax < 1)
		cpumax = 1;

	if (gcpu_num_limit.max != cpumax) {
		gcpu_num_limit.max = cpumax;
		/*check if we need to hotplug out cpu*/
		cpumax_handle();
	}

	return 0;
}

static struct notifier_block cpunumbermax_notifier = {
	.notifier_call = cpunumbermax_notify,
};

/***
* cpu min lock handle
*/
static inline void cpumin_handle(void)
{
	int cpu_online_num = num_online_cpus();

	if (gcpu_num_limit.block != 0)
		return;

	while (gcpu_num_limit.min > cpu_online_num) {
		cpu_up(cpu_online_num);
		cpu_online_num = num_online_cpus();
	}
}

static int cpunumbermin_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
	int cpumin = 0;

	pr_debug("[%s] in=%lu\n", __func__, l);

	cpumin = (int)l;

	if (cpumin > num_possible_cpus())
		cpumin = num_possible_cpus();

	if (cpumin < 1)
		cpumin = 1;

	if (gcpu_num_limit.min != cpumin) {
		gcpu_num_limit.min = cpumin;

		/*check if we need to hotplug cpu*/
		cpumin_handle();
	}

	return 0;
}

static struct notifier_block cpunumbermin_notifier = {
	.notifier_call = cpunumbermin_notify,
};

/**
*  cpu lock number handler.
**/
static inline void cpu_lock_handle(void)
{
	int cpu_online_num = num_online_cpus();

	if (gcpu_num_limit.block == 0) {
		cpumax_handle();
		cpumin_handle();
		return;
	}

	while (gcpu_num_limit.block != cpu_online_num) {

		if (gcpu_num_limit.block < cpu_online_num)
			cpu_down(cpu_online_num - 1);
		else if (gcpu_num_limit.block > cpu_online_num)
			cpu_up(cpu_online_num);

		cpu_online_num = num_online_cpus();
	}
}

static int cpunumberlock_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
	int cpulock = 0;

	pr_debug("[%s] in=%lu\n", __func__, l);

	cpulock = (int)l;

	/*if the cpu number is larger than possible number,
	* we use the possible number.*/
	if (cpulock > num_possible_cpus())
		cpulock = num_possible_cpus();

	if (gcpu_num_limit.block != cpulock) {

		gcpu_num_limit.block = cpulock;

		/*check if we need to hotplug cpu*/
		cpu_lock_handle();
	}

	return 0;
}

static struct notifier_block cpunumberlock_notifier = {
	.notifier_call = cpunumberlock_notify,
};

static int cpunumbersafe_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
	int isafe = 0;

	pr_debug("[%s] in=%lu\n", __func__, l);

	isafe = (int)l;

	if (isafe > num_possible_cpus())
		isafe = num_possible_cpus();

	if (isafe <= 1)
		isafe = 1;

	if (gcpu_num_limit.safe != isafe)
		gcpu_num_limit.safe = isafe;

	return 0;
}


static struct notifier_block cpunumbersafe_notifier = {
	.notifier_call = cpunumbersafe_notify,
};

static int gpumaxprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);

       PARAM_MAX_TYPE(ipps_param_stru);
	PARAM_MAX(gpu) = l;

	pr_debug("[%s] gpu_max=%d\n", __func__, PARAM_MAX(gpu));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->gpu.max_freq != 0){
	    PARAM_MAX_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &ipps_param_stru);
#endif

	return 0;
}

static struct notifier_block gpumaxprofile_notifier = {
	.notifier_call = gpumaxprofile_notify,
};

static int gpuminprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);
       PARAM_MIN_TYPE(ipps_param_stru);
	PARAM_MIN(gpu) = l;

	pr_debug("[%s] gpu_min=%d\n", __func__, PARAM_MIN(gpu));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->gpu.min_freq != 0){
	    PARAM_MIN_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &ipps_param_stru);
#endif
	return 0;
}

static struct notifier_block gpuminprofile_notifier = {
	.notifier_call = gpuminprofile_notify,
};

static int gpublockprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);
       PARAM_BLOCK_TYPE(ipps_param_stru);
	PARAM_BLOCK(gpu) = l;

	pr_debug("[%s] gpu_block=%d\n", __func__, PARAM_BLOCK(gpu));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->gpu.max_freq != 0 || gdbgipps_param_stru.ipps_param->gpu.min_freq != 0) {
	    PARAM_BLOCK_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &ipps_param_stru);
#endif
	return 0;
}

static struct notifier_block gpublockprofile_notifier = {
	.notifier_call = gpublockprofile_notify,
};

static int gpusafeprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);

       PARAM_SAFE_TYPE(ipps_param_stru);
	PARAM_SAFE(gpu) = l;

	pr_debug("[%s] gpu_safe=%d\n", __func__, PARAM_SAFE(gpu));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->gpu.safe_freq != 0) {
	    PARAM_SAFE_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &ipps_param_stru);
#endif
	return 0;
}

static struct notifier_block gpusafeprofile_notifier = {
	.notifier_call = gpusafeprofile_notify,
};

static int ddrmaxprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);

       PARAM_MAX_TYPE(ipps_param_stru);
	PARAM_MAX(ddr) = l;

	pr_debug("[%s] ddr_max=%d\n", __func__, PARAM_MAX(ddr));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->ddr.max_freq != 0) {
	    PARAM_MAX_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &ipps_param_stru);
#endif

	return 0;
}

static struct notifier_block ddrmaxprofile_notifier = {
	.notifier_call = ddrmaxprofile_notify,
};

static int ddrminprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);

       PARAM_MIN_TYPE(ipps_param_stru);
	PARAM_MIN(ddr) = l;

	pr_debug("[%s] ddr_min=%d\n", __func__, PARAM_MIN(ddr));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->ddr.min_freq != 0) {
	    PARAM_MIN_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &ipps_param_stru);
#endif

	return 0;
}

static struct notifier_block ddrminprofile_notifier = {
	.notifier_call = ddrminprofile_notify,
};

static int ddrblockprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);

       PARAM_BLOCK_TYPE(ipps_param_stru);
	PARAM_BLOCK(ddr) = l;

	pr_debug("[%s] ddr_block=%d\n", __func__, PARAM_BLOCK(ddr));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->ddr.max_freq != 0 || gdbgipps_param_stru.ipps_param->ddr.min_freq != 0) {
	    PARAM_BLOCK_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &ipps_param_stru);
#endif
	return 0;
}

static struct notifier_block ddrblockprofile_notifier = {
	.notifier_call = ddrblockprofile_notify,
};

static int ddrsafeprofile_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
       struct ipps_param_stru ipps_param_stru;
        
       ipps_param_stru.ipps_param = &gipps_param;
       
	pr_debug("[%s] in=%lu\n", __func__, l);

       PARAM_SAFE_TYPE(ipps_param_stru);
	PARAM_SAFE(ddr) = l;

	pr_debug("[%s] ddr_safe=%d\n", __func__, PARAM_SAFE(ddr));

#ifdef CONFIG_LOWPM_DEBUG
	if (gdbgipps_param_stru.ipps_param->ddr.safe_freq != 0) {
	    PARAM_SAFE_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &gdbgipps_param_stru);
	}else {
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &ipps_param_stru);
	}
#else
	ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &ipps_param_stru);
#endif
	return 0;
}

static struct notifier_block ddrsafeprofile_notifier = {
	.notifier_call = ddrsafeprofile_notify,
};

static int ippspolicy_notify(struct notifier_block *b, unsigned long l,
	void *v)
{
	unsigned int upolicy = 0;

	upolicy = l;

	if (PM_QOS_IPPS_POLICY_MAX <  upolicy) {
		upolicy = PM_QOS_IPPS_POLICY_SPECIAL0B;
		WARN(1, "Policy overflow =%lx\n", l);
	}

	pr_info("%s l=%d, upolicy=%x\n", __func__, __LINE__, upolicy);

	switch_set_state(&policy_switch, upolicy);

	//upolicy = (upolicy&0xF) << 4;

	ipps_set_current_policy(&ipps_client, IPPS_OBJ_CPU|IPPS_OBJ_GPU|IPPS_OBJ_DDR, &upolicy);
       ipps_set_current_policy(&ipps_client, IPPS_OBJ_DDR, &upolicy);
	return 0;
}

static struct notifier_block ippspolicy_notifier = {
	.notifier_call = ippspolicy_notify,
};

static void k3v2_qos_remove_notifier(void)
{
	int ret = 0;

	QOS_REMOVE_NOTIFY(PM_QOS_CPU_MAX_PROFILE, cpumaxprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_CPU_MIN_PROFILE, cpuminprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_CPU_PROFILE_BLOCK, cpublockprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_CPU_PROFILE_SAFE, cpusafeprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_CPU_NUMBER_LOCK, cpunumberlock_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_CPU_NUMBER_MAX, cpunumbermax_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_CPU_NUMBER_MIN, cpunumbermin_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_CPU_NUMBER_SAFE, cpunumbersafe_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_GPU_MAX_PROFILE, gpumaxprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_GPU_MIN_PROFILE, gpuminprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_GPU_PROFILE_BLOCK, gpublockprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_GPU_PROFILE_SAFE, gpusafeprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_DDR_MAX_PROFILE, ddrmaxprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_DDR_MIN_PROFILE, ddrminprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_DDR_PROFILE_BLOCK, ddrblockprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_DDR_PROFILE_SAFE, ddrsafeprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_IPPS_POLICY, ippspolicy_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_BUS_MAX_PROFILE, busmaxprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_BUS_MIN_PROFILE, busminprofile_notifier);

	QOS_REMOVE_NOTIFY(PM_QOS_CPUIDLE_INT_DEFAULT_VALUE, cpuilde_int_notifier);

}


static void k3v2_qos_add_notifier(void)
{
	int ret = 0;

	QOS_ADD_NOTIFY(PM_QOS_CPU_MAX_PROFILE, cpumaxprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_CPU_MIN_PROFILE, cpuminprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_CPU_PROFILE_BLOCK, cpublockprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_CPU_PROFILE_SAFE, cpusafeprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_CPU_NUMBER_LOCK, cpunumberlock_notifier);

	QOS_ADD_NOTIFY(PM_QOS_CPU_NUMBER_MAX, cpunumbermax_notifier);

	QOS_ADD_NOTIFY(PM_QOS_CPU_NUMBER_MIN, cpunumbermin_notifier);

	QOS_ADD_NOTIFY(PM_QOS_CPU_NUMBER_SAFE, cpunumbersafe_notifier);

	QOS_ADD_NOTIFY(PM_QOS_GPU_MAX_PROFILE, gpumaxprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_GPU_MIN_PROFILE, gpuminprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_GPU_PROFILE_BLOCK, gpublockprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_GPU_PROFILE_SAFE, gpusafeprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_DDR_MAX_PROFILE, ddrmaxprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_DDR_MIN_PROFILE, ddrminprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_DDR_PROFILE_BLOCK, ddrblockprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_DDR_PROFILE_SAFE, ddrsafeprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_IPPS_POLICY, ippspolicy_notifier);

	QOS_ADD_NOTIFY(PM_QOS_BUS_MAX_PROFILE, busmaxprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_BUS_MIN_PROFILE, busminprofile_notifier);

	QOS_ADD_NOTIFY(PM_QOS_CPU_INT_LATENCY, cpuilde_int_notifier);

	return;

ERROR:
	k3v2_qos_remove_notifier();

}

/******************** PM QOS NOTIFY***************************/
/* pm_qos interface global val*/
struct pm_qos_lst {
	struct pm_qos_request_list *lst;
	int qos_class;
	s32 dvalue;
};

static struct pm_qos_request_list g_cpumaxlimits;
static struct pm_qos_request_list g_cpuminlimits;
static struct pm_qos_request_list g_cpublocklimits;
static struct pm_qos_request_list g_cpusafelimits;
static struct pm_qos_request_list g_gpumaxlimits;
static struct pm_qos_request_list g_gpuminlimits;
static struct pm_qos_request_list g_gpublocklimits;
static struct pm_qos_request_list g_gpusafelimits;
static struct pm_qos_request_list g_ddrmaxlimits;
static struct pm_qos_request_list g_ddrminlimits;
static struct pm_qos_request_list g_ddrblocklimits;
static struct pm_qos_request_list g_ddrsafelimits;
static struct pm_qos_request_list g_qoscpulock;
static struct pm_qos_request_list g_qoscpumax;
static struct pm_qos_request_list g_qoscpumin;
static struct pm_qos_request_list g_qoscpusafe;
static struct pm_qos_request_list g_busmaxlimits;
static struct pm_qos_request_list g_busminlimits;

static struct pm_qos_lst pm_qos_list[] = {
{&g_cpumaxlimits, PM_QOS_CPU_MAX_PROFILE, PM_QOS_CPU_MAXPROFILE_DEFAULT_VALUE},
{&g_cpuminlimits, PM_QOS_CPU_MIN_PROFILE, PM_QOS_CPU_MINPROFILE_DEFAULT_VALUE},
{&g_cpublocklimits, PM_QOS_CPU_PROFILE_BLOCK, PM_QOS_CPU_BLKPROFILE_DEFAULT_VALUE},
{&g_cpusafelimits, PM_QOS_CPU_PROFILE_SAFE, PM_QOS_CPU_SAFEPROFILE_DEFAULT_VALUE},
{&g_gpumaxlimits, PM_QOS_GPU_MAX_PROFILE, PM_QOS_GPU_MAXPROFILE_DEFAULT_VALUE},
{&g_gpuminlimits, PM_QOS_GPU_MIN_PROFILE, PM_QOS_GPU_MINPROFILE_DEFAULT_VALUE},
{&g_gpublocklimits, PM_QOS_GPU_PROFILE_BLOCK, PM_QOS_GPU_BLKPROFILE_DEFAULT_VALUE},
{&g_gpusafelimits, PM_QOS_GPU_PROFILE_SAFE, PM_QOS_GPU_SAFEPROFILE_DEFAULT_VALUE},
{&g_ddrmaxlimits, PM_QOS_DDR_MAX_PROFILE, PM_QOS_DDR_MAXPROFILE_DEFAULT_VALUE},
{&g_ddrminlimits, PM_QOS_DDR_MIN_PROFILE, PM_QOS_DDR_MINPROFILE_DEFAULT_VALUE},
{&g_ddrblocklimits, PM_QOS_DDR_PROFILE_BLOCK, PM_QOS_DDR_BLKPROFILE_DEFAULT_VALUE},
{&g_ddrsafelimits, PM_QOS_DDR_PROFILE_SAFE, PM_QOS_DDR_SAFEPROFILE_DEFAULT_VALUE},
{&g_qoscpulock, PM_QOS_CPU_NUMBER_LOCK, PM_QOS_CPU_NUMBER_LOCK_DEFAULT_VALUE},
{&g_qoscpumax, PM_QOS_CPU_NUMBER_MAX, PM_QOS_CPU_NUMBER_MAX_DEFAULT_VALUE},
{&g_qoscpumin, PM_QOS_CPU_NUMBER_MIN, PM_QOS_CPU_NUMBER_MIN_DEFAULT_VALUE},
{&g_qoscpusafe, PM_QOS_CPU_NUMBER_SAFE, PM_QOS_CPU_NUMBER_SAFE_DEFAULT_VALUE},
{&g_busmaxlimits, PM_QOS_BUS_MAX_PROFILE, PM_QOS_BUS_MAXPROFILE_DEFAULT_VALUE},
{&g_busminlimits, PM_QOS_BUS_MIN_PROFILE, PM_QOS_BUS_MINPROFILE_DEFAULT_VALUE},
};

void k3v2_pm_qos_add(void)
{
	int i = 0;
	int ilength = sizeof(pm_qos_list)/sizeof(struct pm_qos_lst);

	for (i = 0; i < ilength; i++) {
		pm_qos_add_request(pm_qos_list[i].lst, pm_qos_list[i].qos_class,
			pm_qos_list[i].dvalue);
	}
}

void k3v2_pm_qos_remove(void)
{
	int i = 0;
	int ilength = sizeof(pm_qos_list)/sizeof(struct pm_qos_lst);

	for (i = 0; i < ilength; i++)
		pm_qos_remove_request(pm_qos_list[i].lst);
}

/*******************Qos notifier end    ******************/


/*******************freq attr setting begin*****************************/
/**
 * show_available_freqs - show available frequencies for the specified GPU
 */
 #define SHOW_AVAILABLE_FREQS(obj)	\
static ssize_t show_##obj##_available_freqs(struct cpufreq_policy *policy,\
	char *buf)\
{\
	unsigned int i = 0;\
	ssize_t count = 0;\
	for (i = 0; (obj##freq_table[i].frequency != CPUFREQ_TABLE_END); i++) {\
		if (obj##freq_table[i].frequency == CPUFREQ_ENTRY_INVALID)\
			continue;\
		count += sprintf(&buf[count], "%d ", obj##freq_table[i].frequency);\
	}\
	count += sprintf(&buf[count], "\n");\
	return count;\
}

#define DEFINE_FREQ_ATTR(obj, _name)	\
static struct freq_attr scaling_##obj = {\
	.attr = { .name = _name,\
		  .mode = 0444,\
		},\
	.show = show_##obj,\
};

SHOW_AVAILABLE_FREQS(gpu)
SHOW_AVAILABLE_FREQS(ddr)
SHOW_AVAILABLE_FREQS(bus)
DEFINE_FREQ_ATTR(gpu_available_freqs, "scaling_available_gpufrequencies")
DEFINE_FREQ_ATTR(ddr_available_freqs, "scaling_available_ddrfrequencies")
DEFINE_FREQ_ATTR(bus_available_freqs, "scaling_available_busfrequencies")

/**
 * show_available_policy - show available policy
 */
static ssize_t show_available_policies(struct cpufreq_policy *policy,
	char *buf)
{
	ssize_t count = 0;

	count += sprintf(&buf[count], "powersave normal performance\n");

	return count;
}

DEFINE_FREQ_ATTR(available_policies, "scaling_available_policies")

static ssize_t show_scaling_cur_policy(struct cpufreq_policy *policy, char *buf)
{
	/*first read current policy from mcu*/
	unsigned int upolicy = 0;
	ipps_get_current_policy(&ipps_client, IPPS_OBJ_CPU, &upolicy);

	/*then return to user*/
	switch (upolicy) {
	case 0x0:
		return sprintf(buf, "powersave\n");
	case 0x1:
		return sprintf(buf, "normal\n");
	case 0x2:
		return sprintf(buf, "performance\n");
	default:
		return sprintf(buf, "powersave\n");
	}
}

static ssize_t store_scaling_cur_policy(struct cpufreq_policy *policy,
					const char *buf, size_t count)
{
	char	str_policy[16];
	unsigned int ret = -EINVAL;
	unsigned int upolicy = 0;

	ret = sscanf(buf, "%15s", str_policy);
	if (ret != 1)
		return -EINVAL;

	printk("%s %d %s\n", __func__, __LINE__, str_policy);

	if (!strnicmp(str_policy, "powersave",	CPUFREQ_NAME_LEN)) {
		/*powersave mode*/
		printk("powersave called.\n");
		upolicy = 0x0;
	} else if (!strnicmp(str_policy, "performance",	CPUFREQ_NAME_LEN)) {
		/*performance mode*/
		printk("performance called.\n");
		upolicy = 0x2;
	} else if (!strnicmp(str_policy, "normal", CPUFREQ_NAME_LEN)) {
		/*normal mode*/
		printk("normal called.\n");
		upolicy = 0x1;
	} else if (!strnicmp(str_policy, "special01", CPUFREQ_NAME_LEN)) {
		/*special01 mode*/
		printk("special01 called.\n");
		upolicy = 0x3;
	} else if (!strnicmp(str_policy, "special02", CPUFREQ_NAME_LEN)) {
		/*special02 mode*/
		printk("special02 called.\n");
		upolicy = 0x4;
	} else if (!strnicmp(str_policy, "special03", CPUFREQ_NAME_LEN)) {
		/*special03 mode*/
		printk("special03 called.\n");
		upolicy = 0x5;
	} else {
		/*powersave mode*/
		printk("powersave called.\n");
		upolicy = 0x0;
	}

	pm_qos_update_request(&g_ippspolicy, upolicy);
	return count;
}
cpufreq_freq_attr_rw(scaling_cur_policy);

/**
 * show_available_profile - show available profile
 */
static ssize_t show_available_profiles(struct cpufreq_policy *policy,
	char *buf)
{
	ssize_t count = 0;

	count += sprintf(&buf[count], "profile range:0~1\n");

	return count;
}

DEFINE_FREQ_ATTR(available_profiles, "scaling_available_profiles")

static ssize_t show_scaling_cur_profile(struct cpufreq_policy *policy, char *buf)
{
	/*first read current policy from mcu*/
	unsigned int uprofile = 0;
	ipps_get_current_profile(&ipps_client, IPPS_OBJ_CPU, &uprofile);

    return sprintf(buf, "%d\n", uprofile);
}

static ssize_t store_scaling_cur_profile(struct cpufreq_policy *policy,
					const char *buf, size_t count)
{
	unsigned int ret = -EINVAL;
	unsigned int uprofile = 0;

	ret = sscanf(buf, "%u", &uprofile);
	if (ret != 1)
		return -EINVAL;

	printk("%s %d profile:%d\n", __func__, __LINE__, uprofile);

    ipps_set_current_profile(&ipps_client, IPPS_OBJ_CPU, &uprofile);

	return count;
}
cpufreq_freq_attr_rw(scaling_cur_profile);

#define DEFINE_ATTR_CUR_FREQ(_obj, _OBJ)	\
static ssize_t show_scaling_##_obj##_cur_freq(struct cpufreq_policy *policy, char *buf)\
{\
		int ret = 0;\
		unsigned int freq = 0;\
		ret = ipps_get_current_freq(&ipps_client, _OBJ, &freq);\
		if (ret) {\
			pr_debug("Failed to get frequency.\n");\
			return ret;\
		}\
		return sprintf(buf, "%d\n", freq);\
}\
static ssize_t store_scaling_##_obj##_cur_freq(struct cpufreq_policy *policy,\
						const char *buf, size_t count)\
{\
		unsigned int freq = 0;\
		int ret = 0;\
		if (!sscanf(buf, "%d", &freq))\
			return -EINVAL;\
		ret = ipps_set_current_freq(&ipps_client, _OBJ, &freq);\
		if (ret) {\
			pr_debug("Failed to set frequency.\n");\
			return ret;\
		}\
		return count;\
}

DEFINE_ATTR_CUR_FREQ(gpu, IPPS_OBJ_GPU)
DEFINE_ATTR_CUR_FREQ(ddr, IPPS_OBJ_DDR)
cpufreq_freq_attr_rw(scaling_gpu_cur_freq);
cpufreq_freq_attr_rw(scaling_ddr_cur_freq);

#define DEFINE_ATTR_CUR_MODE(_obj, _OBJ)		\
static ssize_t show_scaling_##_obj##_mode(struct cpufreq_policy *policy, char *buf)\
{\
	int ret = 0;\
	unsigned int mode = IPPS_ENABLE;\
	ret = ipps_get_mode(&ipps_client, _OBJ, &mode);\
	if (ret) {\
		pr_debug("Failed to get mode.\n");\
		return ret;\
	}\
	return sprintf(buf, "%s\n",\
				(mode == IPPS_ENABLE) ? "ENABLED":"DISABLED");\
}\
static ssize_t store_scaling_##_obj##_mode(struct cpufreq_policy *policy,\
					const char *buf, size_t count)\
{\
	unsigned int mode;\
	int ret = 0;\
	if (!sscanf(buf, "%d", &mode))\
		return -EINVAL;\
	ret = ipps_set_mode(&ipps_client, _OBJ, &mode);\
	if (ret) {\
		pr_debug("Failed to set mode.\n");\
		return ret;\
	}\
	return count;\
}

DEFINE_ATTR_CUR_MODE(cpu, IPPS_OBJ_CPU)
DEFINE_ATTR_CUR_MODE(gpu, IPPS_OBJ_GPU)
DEFINE_ATTR_CUR_MODE(ddr, IPPS_OBJ_DDR)
DEFINE_ATTR_CUR_MODE(tmp, IPPS_OBJ_TEMP)
cpufreq_freq_attr_rw(scaling_cpu_mode);
cpufreq_freq_attr_rw(scaling_gpu_mode);
cpufreq_freq_attr_rw(scaling_ddr_mode);
cpufreq_freq_attr_rw(scaling_tmp_mode);

#define DEFINE_ATTR_CUR_FUNC(_obj, _OBJ)		\
static ssize_t show_scaling_##_obj##_func(struct cpufreq_policy *policy, char *buf)\
{\
	int ret = 0;\
	unsigned int func = IPPS_DVFS_AVS_ENABLE;\
	ret = ipps_get_func(&ipps_client, _OBJ, &func);\
	if (ret) {\
		pr_debug("Failed to get func.\n");\
		return ret;\
	}\
	switch (func) {\
	case IPPS_DVFS_AVS_ENABLE:\
		ret = sprintf(buf, "%s\n", "dvfs avs enabled");\
		break;\
	case IPPS_DVFS_ENABLE:\
		ret = sprintf(buf, "%s\n", "dvfs enabled");\
		break;\
	case IPPS_AVS_ENABLE:\
		ret = sprintf(buf, "%s\n", "avs enabled");\
		break;\
	case IPPS_DVFS_AVS_DISABLE:\
		ret = sprintf(buf, "%s\n", "dvfs avs disabled");\
		break;\
	}\
	return ret;\
}\
static ssize_t store_scaling_##_obj##_func(struct cpufreq_policy *policy,\
					const char *buf, size_t count)\
{\
	unsigned int func;\
	int ret = 0;\
	if (!sscanf(buf, "%d", &func))\
		return -EINVAL;\
	ret = ipps_set_func(&ipps_client, _OBJ, &func);\
	if (ret) {\
		pr_debug("Failed to set func.\n");\
		return ret;\
	}\
	return count;\
}

DEFINE_ATTR_CUR_FUNC(cpu, IPPS_OBJ_CPU)
DEFINE_ATTR_CUR_FUNC(gpu, IPPS_OBJ_GPU)
DEFINE_ATTR_CUR_FUNC(ddr, IPPS_OBJ_DDR)
DEFINE_ATTR_CUR_FUNC(bus, IPPS_OBJ_BUS)
cpufreq_freq_attr_rw(scaling_cpu_func);
cpufreq_freq_attr_rw(scaling_gpu_func);
cpufreq_freq_attr_rw(scaling_ddr_func);
cpufreq_freq_attr_rw(scaling_bus_func);

/* cpufreq_hotplug Governor Tunables */
#define show_one(file_name, obj, object)					\
static ssize_t show_##file_name(struct cpufreq_policy *policy,\
	char *buf)		\
{									\
	unsigned freq =	PARAM_VAL(obj, object);		\
	pr_info("[%s] %d\n", __func__, PARAM_VAL(obj, object));	\
	return sprintf(buf, "%u\n", freq);		\
}

#define show_cpu_one(file_name, object)					\
static ssize_t show_##file_name(struct cpufreq_policy *policy,\
	char *buf)		\
{									\
	return sprintf(buf, "%u\n", gcpu_num_limit.object);		\
}

show_one(scaling_gpu_max_freq, gpu, max_freq);
show_one(scaling_gpu_min_freq, gpu, min_freq);
show_one(scaling_gpu_block_freq, gpu, block_freq);
show_one(scaling_gpu_safe_freq, gpu, safe_freq);
show_one(scaling_ddr_max_freq, ddr, max_freq);
show_one(scaling_ddr_min_freq, ddr, min_freq);
show_one(scaling_ddr_block_freq, ddr, block_freq);
show_one(scaling_ddr_safe_freq, ddr, safe_freq);
show_one(cpuinfo_block_freq, cpu, block_freq);
show_one(cpuinfo_safe_freq, cpu, safe_freq);
show_cpu_one(scaling_cpu_lock_num, block);
show_cpu_one(scaling_cpu_max_num, max);
show_cpu_one(scaling_cpu_min_num, min);
show_cpu_one(scaling_cpu_safe_num, safe);
show_one(scaling_bus_max_freq, bus, max_freq);
show_one(scaling_bus_min_freq, bus, min_freq);

#define store_one(file_name, object, pm_qos) \
static ssize_t store_##file_name	\
	(struct cpufreq_policy *policy, const char *buf, size_t count)	\
{	\
	unsigned int input;	\
	int ret = sscanf(buf, "%u", &input);	\
	if (ret != 1)		\
		return -EINVAL;	\
    printk(KERN_NOTICE "%s value:%d\n", __FUNCTION__, input);           \
						\
	pm_qos_update_request(&pm_qos, input);	\
						\
	return count;	\
}					\

store_one(cpuinfo_block_freq, block_limit, g_cpublocklimits);
store_one(cpuinfo_safe_freq, safe_limit, g_cpusafelimits);
store_one(scaling_gpu_max_freq, max_limit, g_gpumaxlimits);
store_one(scaling_gpu_min_freq, min_limit, g_gpuminlimits);
store_one(scaling_gpu_block_freq, block_limit, g_gpublocklimits);
store_one(scaling_gpu_safe_freq, safe_limit, g_gpusafelimits);
store_one(scaling_ddr_max_freq, max_limit, g_ddrmaxlimits);
store_one(scaling_ddr_min_freq, min_limit, g_ddrminlimits);
store_one(scaling_ddr_block_freq, block_limit, g_ddrblocklimits);
store_one(scaling_ddr_safe_freq, safe_limit, g_ddrsafelimits);
store_one(scaling_cpu_lock_num, cpu_lock, g_qoscpulock);
store_one(scaling_cpu_max_num, max_limit, g_qoscpumax);
store_one(scaling_cpu_min_num, min_limit, g_qoscpumin);
store_one(scaling_cpu_safe_num, safe_limit, g_qoscpusafe);
store_one(scaling_bus_max_freq, max_limit, g_busmaxlimits);
store_one(scaling_bus_min_freq, min_limit, g_busminlimits);

cpufreq_freq_attr_rw(cpuinfo_block_freq);
cpufreq_freq_attr_rw(cpuinfo_safe_freq);
cpufreq_freq_attr_rw(scaling_gpu_max_freq);
cpufreq_freq_attr_rw(scaling_gpu_min_freq);
cpufreq_freq_attr_rw(scaling_gpu_block_freq);
cpufreq_freq_attr_rw(scaling_gpu_safe_freq);
cpufreq_freq_attr_rw(scaling_ddr_max_freq);
cpufreq_freq_attr_rw(scaling_ddr_min_freq);
cpufreq_freq_attr_rw(scaling_ddr_block_freq);
cpufreq_freq_attr_rw(scaling_ddr_safe_freq);
cpufreq_freq_attr_rw(scaling_cpu_lock_num);
cpufreq_freq_attr_rw(scaling_cpu_max_num);
cpufreq_freq_attr_rw(scaling_cpu_min_num);
cpufreq_freq_attr_rw(scaling_cpu_safe_num);
cpufreq_freq_attr_rw(scaling_bus_max_freq);
cpufreq_freq_attr_rw(scaling_bus_min_freq);

static struct freq_attr *k3v2_cpufreq_attr[] = {
	&cpufreq_freq_attr_scaling_available_freqs,
	&scaling_gpu_available_freqs,
	&scaling_ddr_available_freqs,
	&scaling_available_policies,
	&scaling_cur_policy,
	&scaling_available_profiles,
	&scaling_cur_profile,
	&scaling_gpu_cur_freq,
	&scaling_ddr_cur_freq,
	&cpuinfo_block_freq,
	&cpuinfo_safe_freq,
	&scaling_gpu_max_freq,
	&scaling_gpu_min_freq,
	&scaling_gpu_block_freq,
	&scaling_gpu_safe_freq,
	&scaling_ddr_max_freq,
	&scaling_ddr_min_freq,
	&scaling_ddr_block_freq,
	&scaling_ddr_safe_freq,
	&scaling_cpu_lock_num,
	&scaling_cpu_max_num,
	&scaling_cpu_min_num,
	&scaling_cpu_safe_num,
    &scaling_bus_max_freq,
	&scaling_bus_min_freq,
	&scaling_cpu_mode,
	&scaling_gpu_mode,
	&scaling_ddr_mode,
	&scaling_tmp_mode,
	&scaling_cpu_func,
	&scaling_gpu_func,
	&scaling_ddr_func,
	&scaling_bus_func,
	NULL,
};
/*******************freq attr setting end *****************************/

/*******************hotplug cpu operation ****************************/

static inline void wait_cpu_idle(unsigned int cpu)
{
	 unsigned int cnt = 0;
	 unsigned int tmp = 0;

	 tmp = readl(IO_ADDRESS(0xFC8020FC));
	 while ((1<<(8+cpu)) != (tmp & (1<<(8+cpu)))) {
		msleep(1);
		cnt++;
		tmp = readl(IO_ADDRESS(0xFC8020FC));

		/*wait 1s*/
		if (cnt > 1000) {
			WARN(1, "cpu %d wfi state is error, please check!\r\n", cpu);
			break;
		}
	}
}

static int __cpuinit hotcpu_k3_prepare(struct notifier_block *nfb,
					unsigned long action, void *hcpu)
{
	unsigned int umode = 0;
	unsigned int cpu = (unsigned long)hcpu;

	switch (action & 0xF) {
	case CPU_UP_PREPARE:

		umode = IPPS_DISABLE;
		ipps_set_mode(&ipps_client, IPPS_OBJ_CPU, &umode);

		/* MTCMOS */
		if (cpu > 1)
			writel((0x01 << (cpu + 3)), IO_ADDRESS(0xFC8020D0));
		udelay(100);

		/* Enable core */
		writel((0x01 << cpu), IO_ADDRESS(0xFC8020F4));

		/* Unreset */
		if (cpu > 1)
			writel((0x1011 << cpu), IO_ADDRESS(0xfc802414));

		/* reset */
		if (cpu > 1)
			writel((0x401011 << cpu), IO_ADDRESS(0xfc802410));

		/* ISO disable */
		if (cpu > 1)
			writel((0x01 << (cpu + 3)), IO_ADDRESS(0xFC8020C4));
		udelay(1);

		/* WFI Mask */
		writel(((~(0x1 << (cpu+28)))&readl(IO_ADDRESS(0xFC802200))), IO_ADDRESS(0xfc802200));

		/* Unreset */
		writel((0x401011 << cpu), IO_ADDRESS(0xfc802414));

		break;

	case CPU_DOWN_PREPARE:
		umode = IPPS_DISABLE;
		ipps_set_mode(&ipps_client, IPPS_OBJ_CPU, &umode);
		break;

	default:
		break;
	}

	return NOTIFY_OK;
}


static int __cpuinit hotcpu_k3_later(struct notifier_block *nfb,
					unsigned long action, void *hcpu)
{
	unsigned int umode = 0;
	unsigned int cpu = (unsigned long)hcpu;

	switch (action & 0xF) {
	case CPU_ONLINE:
	case CPU_DOWN_FAILED:
		umode = IPPS_ENABLE;
		ipps_set_mode(&ipps_client, IPPS_OBJ_CPU, &umode);
		break;

	case CPU_UP_CANCELED:
	case CPU_DEAD:

		/*wait cpu wfi*/
		wait_cpu_idle(cpu);

		/* WFI Mask */
		writel(((0x1 << (cpu+28))|readl(IO_ADDRESS(0xFC802200))), IO_ADDRESS(0xfc802200));

		/* Disable core */
		writel((0x01 << cpu), IO_ADDRESS(0xFC8020F8));

		/* ISO enable */
		if (cpu > 1)
			writel((0x01 << (cpu + 3)), IO_ADDRESS(0xFC8020C0));
		udelay(1);

		/* Reset */
		writel((0x401011 << cpu), IO_ADDRESS(0xfc802410));

		/* MTCMOS */
		if (cpu > 1)
			writel((0x01 << (cpu + 3)), IO_ADDRESS(0xFC8020D4));
		udelay(100);

		umode = IPPS_ENABLE;
		ipps_set_mode(&ipps_client, IPPS_OBJ_CPU, &umode);
		break;

	default:
		break;
	}

	return NOTIFY_OK;
}

static struct notifier_block __refdata hotcpu_prepare_notifier = {
	.notifier_call = hotcpu_k3_prepare,
	.priority      = INT_MAX,
};

static struct notifier_block __refdata hotcpu_later_notifier = {
	.notifier_call = hotcpu_k3_later,
	.priority      = INT_MIN,
};

/*******************hotplug cpu operation ****************************/


/*******************Cpufreq_driver interface *************/
static int k3v2_verify_freq(struct cpufreq_policy *policy)
{
	if (cpufreq_table)
		return cpufreq_frequency_table_verify(policy, cpufreq_table);

	if (policy->cpu)
		return -EINVAL;

	cpufreq_verify_within_limits(policy, policy->cpuinfo.min_freq,
				     policy->cpuinfo.max_freq);
	return 0;
}

static unsigned int k3v2_getfreq(unsigned int cpu)
{
	unsigned int rate = CPU_FREQ_MIN;

	pr_debug("[%s] %d cpu\n", __func__, __LINE__);

	if (cpu)
		return 0;

	ipps_get_current_freq(&ipps_client, IPPS_OBJ_CPU, &rate);

	pr_debug("[%s] %d cur=%d.\n", __func__, __LINE__, rate);

	return rate;
}

static int k3v2_target(struct cpufreq_policy *policy,
		       unsigned int target_freq,
		       unsigned int relation)
{
	struct cpufreq_freqs freqs;
	int ret = 0;
	unsigned int dest_freq = target_freq;

    printk(KERN_ERR "%s target_freq:%d relation:%d\n",__func__, target_freq, relation);

#if 0
	/*check if we have limits on the cpufreqs*/
	if (target_freq > PARAM_MAX(cpu))
		target_freq = PARAM_MAX(cpu);

	if (target_freq < PARAM_MIN(cpu))
		target_freq = PARAM_MIN(cpu);
#endif

	freqs.old = k3v2_getfreq(0);
	freqs.new = target_freq;
	freqs.cpu = 0;

    printk(KERN_ERR "%s old:%d new:%d\n",__func__, freqs.old, freqs.new);

#if 0
	if (freqs.old == freqs.new)
		return ret;
#endif

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	/*set cpu freq.*/
	pm_qos_update_request(&g_cpuminlimits, dest_freq);
	//ipps_set_current_freq(&ipps_client, IPPS_OBJ_CPU, &dest_freq);
	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	return ret;
}

extern int BSP_DRV_PRIVATE_IPCIntInit(void);
extern int BSP_PRIVATE_IPC_IntEnable (unsigned int ulLvl);
extern void clear_private_ipc_int(unsigned int  enTarget, unsigned int enIntSrc);

#include <asm/hardware/gic.h>
extern void __iomem *gic_dist_base_addr;
void __iomem *g_sram_on_base_addr;

static irqreturn_t Ipc2IntHandler(int irq, void *dev_id)
{
    unsigned int cpu_online = 0;
    unsigned int value = 0;
    
    printk(KERN_ERR "hehe just do it!!! irq=%d.\n", irq);
    cpu_online = readl(g_sram_on_base_addr + (MEMORY_AXI_ACPU_FIQ_TEST_ADDR - SOC_SRAM_ON_BASE_ADDR));
    cpu_online += readl(g_sram_on_base_addr + (MEMORY_AXI_ACPU_FIQ_TEST_ADDR - SOC_SRAM_ON_BASE_ADDR) + 0x4);
    cpu_online += readl(g_sram_on_base_addr + (MEMORY_AXI_ACPU_FIQ_TEST_ADDR - SOC_SRAM_ON_BASE_ADDR) + 0x8);

    writel((cpu_online + SLAVE_CORE_FIQ_NUM), (gic_dist_base_addr + GIC_DIST_SOFTINT));
    writel((cpu_online + SLAVE_CORE_FIQ_NUM), (g_sram_on_base_addr + (MEMORY_AXI_ACPU_FIQ_CPU_INFO_ADDR - SOC_SRAM_ON_BASE_ADDR)));

    clear_private_ipc_int(IPC2_NOSEC_INT_ACPU, IPC2_NOSEC_DVFS_INT_NUM);
    writel(ACPU_IDLE_READY_FLAG, (g_sram_on_base_addr + (MEMORY_AXI_ACPU_FIQ_CPU_INFO_ADDR - SOC_SRAM_ON_BASE_ADDR + 0x4)));
    
    value = readl(g_sram_on_base_addr + (MEMORY_AXI_ACPU_FIQ_DEBUG_INFO_ADDR - SOC_SRAM_ON_BASE_ADDR));
    writel((value + 0x1), (g_sram_on_base_addr + (MEMORY_AXI_ACPU_FIQ_DEBUG_INFO_ADDR - SOC_SRAM_ON_BASE_ADDR + 0x4)));
    
    while(ACPU_DVFS_COMPLETE_FLAG != readl(g_sram_on_base_addr + (MEMORY_AXI_ACPU_FIQ_CPU_INFO_ADDR - SOC_SRAM_ON_BASE_ADDR + 0x14)));
    
    return IRQ_HANDLED;
}

static int __cpuinit k3v2_cpu_init(struct cpufreq_policy *policy)
{
	int result = 0;

	if (policy->cpu != 0) {
		pr_err("[%s] %d cpu=%d\n", __func__, __LINE__, policy->cpu);
	}

	policy->cpuinfo.transition_latency = 1 * 1000;

	if (!cpufreq_table) {
		cpufreq_table = kmalloc(sizeof(struct cpufreq_frequency_table) * 16 , GFP_KERNEL);

		if (!cpufreq_table) {
			pr_err("[%s] %d cpufreq_table kmalloc err\n", __func__, __LINE__);
			goto ERROR;
		}
	}

	if (!gpufreq_table) {
		gpufreq_table = kmalloc(sizeof(struct cpufreq_frequency_table) * 16 , GFP_KERNEL);

		if (!gpufreq_table) {
			pr_err("[%s] %d gpufreq_table kmalloc err\n", __func__, __LINE__);
			goto ERROR;
		}
	}

	if (!ddrfreq_table) {
		ddrfreq_table = kmalloc(sizeof(struct cpufreq_frequency_table) * 16 , GFP_KERNEL);

		if (!ddrfreq_table) {
			pr_err("[%s] %d ddrfreq_table kmalloc err\n", __func__, __LINE__);
			goto ERROR;
		}
	}

    if (!busfreq_table) {
		busfreq_table = kmalloc(sizeof(struct cpufreq_frequency_table) * 16 , GFP_KERNEL);

		if (!busfreq_table) {
			pr_err("[%s] %d busfreq_table kmalloc err\n", __func__, __LINE__);
			goto ERROR;
		}
	}

	gdbgipps_param_stru.ipps_param = &gdbgipps_param;
	gipps_param_stru.ipps_param = &gipps_param;

	if (policy->cpu == 0) {
              int ret = 0;
              g_sram_on_base_addr = (void __iomem *)IO_ADDRESS(SOC_SRAM_ON_BASE_ADDR);
              WARN_ON(g_sram_on_base_addr == NULL);
              
              ret = request_irq(IRQ_IPC2, Ipc2IntHandler, 0, "ipc2_irq", NULL);
        	if (ret ) {
        		printk(KERN_ERR "Ipc2IntHandler: Unable to register ipc2 irq ret=%d.\n", ret);
        	}
            
              BSP_DRV_PRIVATE_IPCIntInit();
              BSP_PRIVATE_IPC_IntEnable(IPC2_NOSEC_DVFS_INT_NUM);
		/*get freq_table*/
		ipps_get_freqs_table(&ipps_client, IPPS_OBJ_CPU, cpufreq_table);
		ipps_get_freqs_table(&ipps_client, IPPS_OBJ_DDR, ddrfreq_table);
		ipps_get_freqs_table(&ipps_client, IPPS_OBJ_GPU, gpufreq_table);
		ipps_get_freqs_table(&ipps_client, IPPS_OBJ_BUS, busfreq_table);

		/*get freq limits*/
		ipps_get_parameter(&ipps_client, IPPS_OBJ_DDR|IPPS_OBJ_GPU|IPPS_OBJ_CPU|IPPS_OBJ_BUS, &gipps_param_stru);

		policy_switch.name = "ippspolicy";
		result = switch_dev_register(&policy_switch);
		if (0 != result) {
			pr_err("%s line=%d, switch_dev_register err=%x\n", __func__, __LINE__, result);
			goto ERROR;
		}
	}

	/*get current profile*/
	policy->cur = k3v2_getfreq(0);
	if (cpufreq_table) {
		result = cpufreq_frequency_table_cpuinfo(policy, cpufreq_table);
		if (!result)
			cpufreq_frequency_table_get_attr(cpufreq_table,
							policy->cpu);
	} else {
		pr_err("freq_table does not exist.\n");
	}

	policy->min = PARAM_MIN(cpu);
	policy->max = PARAM_MAX(cpu);

	if (policy->cpu == 0) {
		/*add qos notifier*/
		k3v2_qos_add_notifier();
		k3v2_pm_qos_add();
		pm_qos_add_request(&g_ippspolicy, PM_QOS_IPPS_POLICY,
			PM_QOS_IPPS_POLICY_POWERSAVE);
	}

	return 0;

ERROR:

	if (cpufreq_table) {
		kfree(cpufreq_table);
		cpufreq_table = NULL;
	}

	if (ddrfreq_table) {
		kfree(ddrfreq_table);
		ddrfreq_table = NULL;
	}

	if (gpufreq_table) {
		kfree(gpufreq_table);
		gpufreq_table = NULL;
	}

    if (busfreq_table) {
		kfree(busfreq_table);
		busfreq_table = NULL;
	}

	printk("[%s] %d leave %x\n", __func__, __LINE__, EINVAL);

	return -EINVAL;
}

static int k3v2_cpu_exit(struct cpufreq_policy *policy)
{
	if (policy->cpu != 0) {
		pr_err("[%s] %d cpu=%d\n", __func__, __LINE__, policy->cpu);
		return -EINVAL;
	}

	pm_qos_remove_request(&g_ippspolicy);

	/*remove notifier*/
	k3v2_pm_qos_remove();
	k3v2_qos_remove_notifier();

	if (cpufreq_table) {
		kfree(cpufreq_table);
		cpufreq_table = NULL;
	}

	if (ddrfreq_table) {
		kfree(ddrfreq_table);
		ddrfreq_table = NULL;
	}

	if (gpufreq_table) {
		kfree(gpufreq_table);
		gpufreq_table = NULL;
	}

	if (busfreq_table) {
		kfree(busfreq_table);
		busfreq_table = NULL;
	}

	switch_dev_unregister(&policy_switch);

	return 0;
}

static struct cpufreq_driver k3v2_driver = {
	.flags		= CPUFREQ_STICKY,
	.verify		= k3v2_verify_freq,
	.target		= k3v2_target,
	.get		= k3v2_getfreq,
	.init		= k3v2_cpu_init,
	.exit		= k3v2_cpu_exit,
	.name		= "k3v2cpufreq",
	.attr		= k3v2_cpufreq_attr,
};

/******************cpufreq_driver interface end*****************************/


/******************ipps driver interface begin*****************************/

static void ippsclient_add(struct ipps_device *device)
{
	int ret = 0;

	gpipps_device = device;

	ret = cpufreq_register_driver(&k3v2_driver);
	if (0 != ret)
		pr_err("[%s] cpufreq_register_driver err=%x\n", __func__, ret);

#if 0
	register_hotcpu_notifier(&hotcpu_prepare_notifier);
	register_hotcpu_notifier(&hotcpu_later_notifier);
#endif
}

static void ippsclient_remove(struct ipps_device *device)
{
	int ret = 0;

	ret = cpufreq_unregister_driver(&k3v2_driver);
	if (ret != 0)
		pr_err("cpufreq_unregister_driver err=%x\n", ret);
#if 0
	unregister_hotcpu_notifier(&hotcpu_later_notifier);
	unregister_hotcpu_notifier(&hotcpu_prepare_notifier);
#endif
	gpipps_device = NULL;
}

static struct ipps_client ipps_client = {
	.name   = "k3v2cpufreq",
	.add    = ippsclient_add,
	.remove = ippsclient_remove
};

/*****************ipps driver interface end ****************************/

static int __init k3v2_cpufreq_init(void)
{
	int ret = 0;

	ret = ipps_register_client(&ipps_client);
	if (ret != 0)
		pr_err("%s ipps_register_client err=%x\n",
			__func__, ret);

	return ret;
}

static void __exit k3v2_cpufreq_exit(void)
{
	ipps_unregister_client(&ipps_client);
}

MODULE_AUTHOR("s00107748");
MODULE_DESCRIPTION("Cpufreq driver for k3v2 processors.");
MODULE_LICENSE("GPL");
arch_initcall(k3v2_cpufreq_init);
module_exit(k3v2_cpufreq_exit);
