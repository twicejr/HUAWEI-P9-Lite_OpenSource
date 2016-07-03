
/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/smp.h>
#include <linux/notifier.h>
#include <linux/cpu.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <mach/io.h>
#include <mach/platform.h>
#include <soc_baseaddr_interface.h>
#if defined(CHIP_BB_HI6210)
#else
#include <soc_sctrl_interface.h>
#endif
#include <soc_ao_sctrl_interface.h>
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_hotplug_mgr.h>
#include <mach/pwrctrl/pwrctrl_hotplug_platform.h>
#include <mach/pwrctrl/pwrctrl_hotplug_qos.h>


static int hotplug_log_cpu_up_notify (struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;

    switch(status){
        case CPU_UP_PREPARE:
            ppwrctrl_hotplug_exc_log->hotplug_cpu_info[cpu].up_power_time = pwrctrl_get_slice_time();
            break;
        default:
            /*just pass other event*/
            break;
    }
    return NOTIFY_DONE;
}

static int hotplug_log_cpu_down_notify (struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;

    switch(status){
        case CPU_DEAD:
            ppwrctrl_hotplug_exc_log->hotplug_cpu_info[cpu].down_power_time = pwrctrl_get_slice_time();
            break;
        default:
            /*just pass other event*/
            break;

    }
    return NOTIFY_DONE;
}


static struct notifier_block __refdata hotplug_log_cpu_up_notifier = {
    .notifier_call = hotplug_log_cpu_up_notify,
    .priority = CPU_PRI_SCHED_ACTIVE,
};

static struct notifier_block __refdata hotplug_log_cpu_down_notifier = {
    .notifier_call = hotplug_log_cpu_down_notify,
    .priority = CPU_PRI_CPUSET_INACTIVE,
};

static int __init hotplug_log_init(void)
{
    register_hotcpu_notifier(&hotplug_log_cpu_up_notifier);
    register_hotcpu_notifier(&hotplug_log_cpu_down_notifier);

    return 0;
}

static void __exit hotplug_log_exit(void)
{
    unregister_hotcpu_notifier(&hotplug_log_cpu_down_notifier);
    unregister_hotcpu_notifier(&hotplug_log_cpu_up_notifier);

    return;
}

module_init(hotplug_log_init);
module_exit(hotplug_log_exit);



