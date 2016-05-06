/**
 * @file sre_stkmon.h
 *
 * Copyright(C), 2012-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：栈越界模块的对外头文件。 \n
 */

/**@defgroup SRE_stkmon 栈越界检测
  *@ingroup SRE_inspect
 */

#ifndef _SRE_STKMON_H
#define _SRE_STKMON_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//KOS不支持任务栈监控功能   
#if (OS_OPTION_STACK_MON == YES)

/**
 * @ingroup SRE_stkmon
 * 栈越界检测错误码: 异常模块或栈越界检测模块未开启，或者设定异常栈空间区域过小。
 *
 * 值：0x02002a00
 *
 * 解决方案：栈越界检测依赖异常模块，请检查是否同时打开异常模块和栈越界检测模块开关以及异常栈空间大小。
 */
#define OS_ERRNO_STKMON_INIT_FAIL                       SRE_ERRNO_OS_ERROR(OS_MID_STKMON, 0x00)

/**
 * @ingroup SRE_stkmon
 * 栈越界检测错误码: 独占0号数据断点失败。
 *
 * 值：0x02002a02
 *
 * 解决方案：检测数据断点0是否在使用。
 */
#define OS_ERRNO_STKMON_GETWP_FAIL                      SRE_ERRNO_OS_ERROR(OS_MID_STKMON, 0x02)

/**
 * @ingroup SRE_stkmon
 * 栈越界检测错误码: 释放数据断点0失败。
 *
 * 值：0x02002a03
 *
 * 解决方案：检测该数据断点0是否被独占。
 */
#define OS_ERRNO_STKMON_FREEWP_FAIL                     SRE_ERRNO_OS_ERROR(OS_MID_STKMON, 0x03)

/**
 * @ingroup SRE_stkmon
 * 栈越界检测错误码: 任务栈越界。
 *
 * 值: 0x03002a04
 *
 * 解决方案: 创建任务时增大任务栈或者检查是否存在内存操作溢出。
 *
 */
#define OS_ERRNO_STKMON_OVER_FLOW                       SRE_ERRNO_OS_FATAL(OS_MID_STKMON, 0x04)

/**
 * @ingroup  SRE_stkmon
 * @brief 去使能栈越界检测。
 *
 * @par 描述:
 * 去使能栈越界检测功能。
 *
 * @attention 无。
 *
 * @param 无。
 *
 * @retval  #OS_ERRNO_STKMON_INIT_FAIL   0x02002a00，异常模块或栈越界检测模块未开启，或者设定异常栈空间区域过小。
 * @retval  #OS_ERRNO_HOOK_NOT_EXISTED   0x02001605，栈越界检测的任务切换钩子不存在。
 * @retval  #OS_ERRNO_STKMON_FREEWP_FAIL 0x02002a03，释放独占数据断点失败。
 * @retval  #SRE_OK                      0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_stkmon.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_StkMonRestore
 */
extern UINT32 SRE_StkMonDisable(VOID);

/**
 * @ingroup  SRE_stkmon
 * @brief 恢复栈越界检测状态。
 *
 * @par 描述:
 * 恢复栈越界检查功能。
 *
 * @attention 无。
 *
 * @param 无。
 *
 * @retval  #OS_ERRNO_STKMON_INIT_FAIL   0x02002a00，异常模块或栈越界检测模块未开启，或者设定异常栈空间区域过小。
 * @retval  #OS_ERRNO_HOOK_EXISTED       0x02001603，栈越界检测的任务切换钩子已存在。
 * @retval  #OS_ERRNO_HOOK_FULL          0x02001604，HOOK已满或配置个数为0。
 * @retval  #OS_ERRNO_STKMON_GETWP_FAIL  0x02002a02，独占数据断点0失败。
 * @retval  #SRE_OK                      0x00000000，成功。
 * @par 依赖:
 * <ul><li>sre_stkmon.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_StkMonDisable
 */
extern UINT32 SRE_StkMonRestore(VOID);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_STKMON_H */



