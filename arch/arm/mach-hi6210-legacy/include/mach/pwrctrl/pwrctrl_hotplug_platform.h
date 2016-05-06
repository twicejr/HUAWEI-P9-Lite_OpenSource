
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
  文 件 名   : pwrctrl_hotplug_platform.h
  版 本 号   : 初稿
  作    者   : 石连传 61250
  生成日期   : 2012年9月2日
  最近修改   :
  功能描述   : pwrctrl_hotplug_platform.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月2日
    作    者   : 石连传 61250
    修改内容   : 创建文件

******************************************************************************/

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
