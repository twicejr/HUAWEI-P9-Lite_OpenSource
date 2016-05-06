
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
  文 件 名   : pwrctrl_hotplug_platform.c
  版 本 号   : 初稿
  作    者   : 石连传61250
  生成日期   : 2012年9月2日
  最近修改   :
  功能描述   : CPU 上下电底层代码
  函数列表   :
              pwrctrl_hotplug_qosdev_register
              pwrctrl_hotplug_qosdev_unregister
              pwrctrl_cpunumbermin_notify
              pwrctrl_cpunumbermax_notify
              pwrctrl_cpunumberlock_notify

  修改历史   :
  1.日    期   : 2012年9月2日
    作    者   :  石连传61250
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/notifier.h>
#include <linux/pm_qos_params.h>
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_hotplug_mgr.h>
#include <drv_ipcm.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/



/*****************************************************************************
  3 函数实现
*****************************************************************************/




/*************************************************************************
 函 数 名  : pwrctrl_cpunumbermin_notify
 功能描述  : qos cpunumbermin回调处理函数
 输入参数  : 设定的CPU个数
 输出参数  : 无
 返 回 值  : 无
修改记录   ：
************************************************************************/
void pwrctrl_cpunumbermin_notify (struct notifier_block *b, unsigned long cpumin,
    void *v)
{

    /*读SC判断qos特性是否打开，没有打开return ERROR */
    if((cpumin<= num_possible_cpus())&&(cpumin>=1))
    {
        pwrctrl_cpunumbermin_handle((u32_t)cpumin);
    }
    else
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_cpunumbermin fail:%d\n",cpumin,0,0,0,0,0);

    }
}


/*************************************************************************
 函 数 名  : pwrctrl_cpunumbermax_notify
 功能描述  : qos cpunumbermax回调处理函数
 输入参数  : 设定的CPU个数
 输出参数  : 无
 返 回 值  : 无
修改记录   ：
************************************************************************/
void pwrctrl_cpunumbermax_notify (struct notifier_block *b, unsigned long cpumax,
    void *v)
{
     int cpu = num_possible_cpus();

     PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_cpunumbermax_notify %d,%d\n",cpumax,cpu,0,0,0,0);

    /*读SC判断qos特性是否打开，没有打开return ERROR */
    if((cpumax<= num_possible_cpus())&&(cpumax>=1))
    {

        pwrctrl_cpunumbermax_handle((u32_t)cpumax);
    }
    else
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_cpunumbermax erro fail:%d\n",cpumax,0,0,0,0,0);

    }
}


/*************************************************************************
 函 数 名  : pwrctrl_cpunumberlock_notify
 功能描述  : qos cpunumberlock回调处理函数
 输入参数  : 设定的CPU个数
 输出参数  : 无
 返 回 值  : 无
修改记录   ：
************************************************************************/
void pwrctrl_cpunumberlock_notify (struct notifier_block *b, unsigned long cpulock,
    void *v)
{

    /*读SC判断qos特性是否打开，没有打开return ERROR */
    if(cpulock<= num_possible_cpus())
    {
        pwrctrl_cpunumberlock_handle((u32_t)cpulock);
    }
    else
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_cpunumberlock erro fail:%d\n",cpulock,0,0,0,0,0);

    }
}

local_t struct notifier_block cpu_numberlock_notifier = {
    .notifier_call = pwrctrl_cpunumberlock_notify,
    .next = NULL,
    .priority = 0,
};

local_t struct notifier_block cpu_maxnumber_notifier = {
    .notifier_call = pwrctrl_cpunumbermax_notify,
    .next = NULL,
    .priority = 0,
};
local_t struct notifier_block cpu_minnumber_notifier = {
    .notifier_call = pwrctrl_cpunumbermin_notify,
    .next = NULL,
    .priority = 0,
};
/*************************************************************************
 函 数 名  : pwrctrl_hotplug_qosdev_register
 功能描述  : cpu qos设备创建及回调notify函数注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OK/ERROR，设备注册成功或者失败
修改记录   ：
************************************************************************/
 int pwrctrl_hotplug_qosdev_register ( void )
{
    /*注册cpu_number_lock qos notify 回调函数*/
    /*注册cpu_number_min qos notify 回调函数*/
    /*注册cpu_number_max qos notify 回调函数*/
/*
#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
*/
    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_CPU_NUMBER_LOCK, &cpu_numberlock_notifier) < 0);

    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_CPU_NUMBER_MAX, &cpu_maxnumber_notifier) < 0);

    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_CPU_NUMBER_MIN, &cpu_minnumber_notifier) < 0);
/*
#endif
*/
    PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_hotplug_qosdev_register sucess\n",0,0,0,0,0,0);

    return 0;
}

/*************************************************************************
 函 数 名  : pwrctrl_hotplug_qosdev_unregister
 功能描述  : A
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
修改记录   ：
************************************************************************/
 s32_t pwrctrl_hotplug_qosdev_unregister ( void )
{
    /*去注册cpu_number_lock qos notify 回调函数*/
/*
#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
*/
    RET_ERR_IF(pm_qos_remove_notifier(PM_QOS_CPU_NUMBER_LOCK, &cpu_numberlock_notifier) < 0);

    RET_ERR_IF(pm_qos_remove_notifier(PM_QOS_CPU_NUMBER_MAX, &cpu_maxnumber_notifier) < 0);

    RET_ERR_IF(pm_qos_remove_notifier(PM_QOS_CPU_NUMBER_MIN, &cpu_minnumber_notifier) < 0);
/*
#endif
*/
    PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_hotplug_qosdev_unregister sucess\n",0,0,0,0,0,0);


    return 0;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

