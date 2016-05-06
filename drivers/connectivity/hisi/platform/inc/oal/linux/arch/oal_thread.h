/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : oal_thread.h
  版 本 号   : 初稿
  作    者   : z00237171
  生成日期   : 2014年1月29日
  最近修改   :
  功能描述   : oal_thread.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月13日
    作    者   : z00274374
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LINUX_THREAD_H__
#define __OAL_LINUX_THREAD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <asm/atomic.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/jiffies.h>
#include <linux/time.h>
#include <asm/param.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/kthread.h>

/*****************************************************************************
  2 STRUCT定义
*****************************************************************************/
typedef struct task_struct          oal_task_stru;

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 宏定义
*****************************************************************************/
#define oal_kthread_create        kthread_create
#define oal_kthread_bind          kthread_bind
#define oal_kthread_stop          kthread_stop
#define oal_kthread_run           kthread_run
#define oal_kthread_should_stop   kthread_should_stop
#define oal_schedule              schedule
#define oal_wake_up_process       wake_up_process
#define oal_set_current_state     set_current_state
#define oal_cond_resched          cond_resched

#if ((_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_5610EVB)\
    ||(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_5610DMB)\
    ||(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_VSPM310DMB)\
    ||(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_WS835DMB))
#define oal_sched_setscheduler sched_setscheduler_export
#elif(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_1102COMMON)
#define oal_sched_setscheduler sched_setscheduler
#endif
#define oal_set_user_nice          set_user_nice

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
