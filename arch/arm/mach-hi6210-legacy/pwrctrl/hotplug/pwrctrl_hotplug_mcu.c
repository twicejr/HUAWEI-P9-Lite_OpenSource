
/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/******************************************************************************

 ******************************************************************************
  文 件 名   : pwrctrl_hotplug_log.c
  版 本 号   : 初稿
  作    者   : 石连传61250
  生成日期   : 2012年9月2日
  最近修改   :
  功能描述   : CPU 上下电底层代码
  函数列表   :
              platform_cpu_die
              platform_cpu_kill
              platform_cpu_disable
              pwrctrl_hotplug_notify_mcu
              pwrctrl_cpu_change_notify
              pwrctrl_hotplug_hard_init
              pwrctrl_hotplug_hard_exit


  修改历史   :
  1.日    期   : 2012年9月2日
    作    者   :  石连传61250
    修改内容   : 创建文件

******************************************************************************/
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
#include <drv_ipcm.h>
 
static int notify_mcu_cpu_up (unsigned int cpu)
{
    ppwrctrl_hotplug_exc_log->hotplug_cpu_info[cpu].up_notemcu_time = pwrctrl_get_slice_time();

    BSP_IPC_SemGive(IPC_SEM_CPU_PW(cpu));

    return 0;
}

static int notify_mcu_cpu_down (unsigned int cpu)
{
    ppwrctrl_hotplug_exc_log->hotplug_cpu_info[cpu].down_notemcu_time = pwrctrl_get_slice_time();

    if (0 != BSP_IPC_SemTake(IPC_SEM_CPU_PW(cpu),50)) {
        printk(KERN_ERR"%s BSP_IPC_SemTake fail cpu:%d\n",__FUNCTION__, cpu);
        return -1;
    }

    return 0;
}

static int hotplug_cpu_up_notify (struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;

    switch(status){
        case CPU_ONLINE:
            /*notify_mcu_cpu_up(cpu);*/
            break;
        default:
            /*just pass other event*/
            break;
    }
    return NOTIFY_DONE;
}

static int hotplug_cpu_down_notify (struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;

    switch(status){
        case CPU_DEAD:
            /*notify_mcu_cpu_down(cpu);*/
            break;
        default:
            /*just pass other event*/
            break;

    }
    return NOTIFY_DONE;
}

static struct notifier_block __refdata hotplug_cpu_up_notifier = {
    .notifier_call = hotplug_cpu_up_notify,
    .priority = CPU_PRI_CPUSET_ACTIVE,
};

static struct notifier_block __refdata hotplug_cpu_down_notifier = {
    .notifier_call = hotplug_cpu_down_notify,
    .priority = CPU_PRI_CPUSET_INACTIVE,
};

static int __init hotplug_mcu_notify_init(void)
{
    register_hotcpu_notifier(&hotplug_cpu_up_notifier);
    register_hotcpu_notifier(&hotplug_cpu_down_notifier);

    return 0;
}

static void __exit hotplug_mcu_notify_exit(void)
{
    unregister_hotcpu_notifier(&hotplug_cpu_down_notifier);
    unregister_hotcpu_notifier(&hotplug_cpu_up_notifier);

    return;
}

module_init(hotplug_mcu_notify_init);
module_exit(hotplug_mcu_notify_exit);


