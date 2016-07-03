
/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PWRCTRL_HOTPLUG_PLATFORM_H__
#define __PWRCTRL_HOTPLUG_PLATFORM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MAILBOX_TARGET_CPU_MCU 6

#define CPU_POWER_DOWN         1
#define CPU_POWER_UP           2
#define IPC_SEM_CPU_BASE       12
#define IPC_SEM_CPU_PW(cpuindex)  (IPC_SEM_SMP_CPU0 + cpuindex)


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
