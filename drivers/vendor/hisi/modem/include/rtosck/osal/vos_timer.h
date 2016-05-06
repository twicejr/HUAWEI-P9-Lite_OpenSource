/**
 * @file vos_timer.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL定时器头文件。 \n
 */

/**@defgroup vos_timer 定时器
 *@ingroup OSAL
*/

#ifndef __VOS_TIMER_H__
#define __VOS_TIMER_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if((YES == OS_OPTION_EVENT) && (YES == OS_OPTION_QUEUE))

#define VOS_TIMER_LOOP                          1
#define VOS_TIMER_NOLOOP                        0
#define VOS_TIMER_DEL_ON_TIMEOUTMSG             4
#define VOS_TIMER_EVENT                         (1 << 15)

/**
 * @ingroup vos_timer
 * 定时器状态：空闲态。
 */
#define VOS_TM_IS_IDLE                          0x5A

/**
 * @ingroup vos_timer
 * 定时器状态：等待超时态。
 */
#define VOS_TM_IS_TICKING                       0xA5

/**
 * @ingroup vos_timer
 * 定时器状态：超时态。
 */
#define VOS_TM_IS_OUT                           0xAA

/**
 * @ingroup vos_timer
 * 定时器状态：被删除态。
 */
#define VOS_TM_IS_DELETED                       0x55

/**
 * @ingroup vos_timer
 * OSAL定时器超时处理函数类型定义。
 */
typedef VOS_VOID(*P_TIMER_FUNC)(VOS_VOID *);

/**
 * @ingroup vos_timer
 * OSAL定时器超时消息类型。
 */
typedef struct tagTIMERMSG
{
    VOS_UINT32      ulSourceID;             /**< 源ID */
    VOS_UINT32      ulTimerID;              /**< 定时器ID */
    P_TIMER_FUNC    pfFunc;                 /**< 超时回调函数 */
    VOS_VOID        *pArg;                  /**< 超时回调函数的参数 */
} VOS_TIMERMSG_S;

/**
 * @ingroup vos_timer
 * OSAL定时器运行信息类型。
 */
typedef struct tagTIMERINFO
{
    VOS_UINT32      ulTaskID;               /**< 超时后向任务ID发送事件 */
    VOS_UINT32      ulMsgQueID;             /**< 队列ID */
    VOS_UINT32      ulFlag;                 /**< 定时器的类型VOS_TIMER_LOOP或VOS_TIMER_NOLOOP */
    VOS_UINT32      ulTimerStatus;          /**< 定时器的状态 */
    VOS_UINT32      ulMillSec;              /**< 定时器的超时时长 */
    P_TIMER_FUNC    pfFunc;                 /**< 定时器的回调函数 */
    VOS_VOID        *pArg;                  /**< 定时器的参数 */
} VOS_TIMERINFO_S;

/**
 * @ingroup  vos_timer
 * @brief 创建并启动一个定时器。
 *
 * @par 描述:
 * 创建并启动一个定时器。
 *
 * @attention
 * <ul>
 * <li>中断处理函数pfnHandler的第一个参数是创建的定时器的逻辑编号。</li>
 * <li>对于周期定时模式的定时器，建议用户不要把定时间隔设置的过低，避免一直触发定时器的处理函数。</li>
 * </ul>
 *
 * @param  ulTaskID [IN] 类型#VOS_UINT32，任务ID，取值范围为有效的任务ID。
 * @param  ulMsgQueID  [IN] 类型#VOS_UINT32，队列ID。取值范围为有效的队列ID。该参数为NULL时，表示使用的是回调方式的定时器。
 * @param  ulMillSec  [IN] 类型#VOS_UINT32，定时器时长，单位ms。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 * @param  pfFunc  [IN] 类型#P_TIMER_FUNC，超时回调函数。取值范围为非空。
 * @param  pArg  [IN] 类型#VOS_VOID *，超时回调函数的参数，定时器超时后将会向超时回调函数传递这个参数，取值范围为非空。
 * @param  pulTimerID  [OUT] 类型#VOS_UINT32 *，创建的定时器ID。取值范围为非空。
 * @param  ulFlag  [IN] 类型#VOS_UINT32，定时器类型。取值范围为{VOS_TIMER_NOLOOP，VOS_TIMER_LOOP}，二者只能取其一。如果没有输入它们两者中的任何一个，默认采用VOS_TIMER_NOLOOP。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，定时器创建成功。
 * @par 依赖:
 * <ul><li>vos_timer.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Timer_Delete
 */
extern VOS_UINT32 VOS_Timer_Create(VOS_UINT32 ulTaskID, VOS_UINT32 ulMsgQueID, VOS_UINT32 ulMillSec, P_TIMER_FUNC pfFunc, VOS_VOID *pArg, VOS_UINT32 *pulTimerID, VOS_UINT32 ulFlag);

/**
 * @ingroup  vos_timer
 * @brief 停止并删除定时器。
 *
 * @par 描述:
 * 停止并删除定时器。
 *
 * @attention
 * <ul>
 * <li>不能删除正在超时处理的定时器。</li>
 * </ul>
 *
 * @param  ulTimerID [IN] 类型#VOS_UINT32，定时器ID，取值范围为有效的定时器ID。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，定时器删除成功。
 * @par 依赖:
 * <ul><li>vos_timer.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Timer_Create
 */
extern VOS_UINT32 VOS_Timer_Delete(VOS_UINT32 ulTimerID);

/**
 * @ingroup  vos_timer
 * @brief 修改定时器的定时时长。
 *
 * @par 描述:
 * 修改定时器的定时时长。
 *
 * @attention
 * <ul>
 * <li>不能修改正在超时处理的定时器时长。</li>
 * </ul>
 *
 * @param  ulTimerID [IN] 类型#VOS_UINT32，定时器ID，取值范围为有效的定时器ID。
 * @param  ulNewMillSec [IN] 类型#VOS_UINT32，新的定时器时长，单位ms。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，修改定时器的定时时长成功。
 * @par 依赖:
 * <ul><li>vos_timer.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_Timer_Resize(VOS_UINT32 ulTimerID, VOS_UINT32 ulNewMillSec);

/**
 * @ingroup  vos_timer
 * @brief 获取定时器的运行信息。
 *
 * @par 描述:
 * 获取定时器的运行信息。
 *
 * @attention 无
 *
 * @param  ulTimerID [IN] 类型#VOS_UINT32，定时器ID，取值范围为有效的定时器ID。
 * @param  pTimerInfo [OUT] 类型#VOS_TIMERINFO_S *，保存定时器信息的内存指针。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取定时器运行信息成功。
 * @par 依赖:
 * <ul><li>vos_timer.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_Timer_GetInfo(VOS_UINT32 ulTimerID, VOS_TIMERINFO_S *pTimerInfo);

/**
 * @ingroup  vos_timer
 * @brief 查询定时器是否停止。
 *
 * @par 描述:
 * 查询定时器是否停止。
 *
 * @attention 无
 *
 * @param  ulTimerID [IN] 类型#VOS_UINT32，定时器ID，取值范围为有效的定时器ID。
 *
 * @retval #VOS_FALSE                           0x00000000，定时器ID非法，或定时器未停止。
 * @retval #VOS_TRUE                            0x00000001，定时器已停止。
 * @par 依赖:
 * <ul><li>vos_timer.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT16 VOS_Timer_IsStoped(VOS_UINT32 ulTimerID);

/**
 * @ingroup  vos_timer
 * @brief 判断定时器的合法性。
 *
 * @par 描述:
 * 判断定时器的合法性。
 *
 * @attention 无
 *
 * @param  ulTimerID [IN] 类型#VOS_UINT32，定时器ID，取值范围为任意值。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，定时器ID非法。
 * @retval #VOS_OK                              0x00000000，定时器ID合法。
 * @par 依赖:
 * <ul><li>vos_timer.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_Timer_IsValid(VOS_UINT32 ulTimerID);

/**
 * @ingroup  vos_timer
 * @brief 暂停一个定时器。
 *
 * @par 描述:
 * 暂停一个定时器。
 *
 * @attention 无
 *
 * @param  ulTimerID [IN] 类型#VOS_UINT32，定时器ID，取值范围为有效的定时器ID。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，定时器暂停成功。
 * @par 依赖:
 * <ul><li>vos_timer.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Timer_Resume
 */
extern VOS_UINT32 VOS_Timer_Pause(VOS_UINT32 ulTimerID);

/**
 * @ingroup  vos_timer
 * @brief 恢复一个定时器。
 *
 * @par 描述:
 * 恢复一个定时器。
 *
 * @attention 无
 *
 * @param  ulTimerID [IN] 类型#VOS_UINT32，定时器ID，取值范围为有效的定时器ID。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，定时器恢复成功。
 * @par 依赖:
 * <ul><li>vos_timer.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Timer_Pause
 */
extern VOS_UINT32 VOS_Timer_Resume(VOS_UINT32 ulTimerID);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#endif

#endif //__VOS_TIMER_H__

