/**
 * @file vos_event.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL事件头文件。 \n
 */

/**@defgroup vos_event 事件
 *@ingroup OSAL
*/

#ifndef __VOS_EVENT_H__
#define __VOS_EVENT_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (YES == OS_OPTION_EVENT)

/**
 * @ingroup vos_event
 * 事件读取模式：表示期望接收ulEvents中的任何一个事件。
 */
#define VOS_EV_ANY                          ((VOS_UINT32)1 << 26)

/**
 * @ingroup vos_event
 * 事件读取模式：表示期望接收ulEvents中的所有事件。
 */
#define VOS_EV_ALL                          ((VOS_UINT32)1 << 27)

/**
 * @ingroup vos_event
 * 事件错误码：读取事件超时。
 *
 * 值: 0x00000040
 *
 * 解决方案: 增大事件读取等待时间，或其他任务给该任务写事件操作。
 */
#define VOS_ERRNO_EVENT_TIMEOUT             0x00000040

/**
 * @ingroup vos_event
 * 事件错误码：事件读取失败，期望事件没有发生。
 *
 * 值: 0x00000041
 *
 * 解决方案: 可使用等待读取事件。
 */
#define VOS_ERRNO_EVENT_READ_UNAVAI         0x00000041

/**
 * @ingroup  vos_event
 * @brief 读事件。
 *
 * @par 描述:
 * 读取当前任务的指定掩码为ulEvents的事件，可以一次性读取多个事件。事件读取成功后，被读取的事件将被清除。
 *
 * @attention
 * <ul>
 * <li>读取模式可以选择读取任意事件和读取所有事件。</li>
 * <li>等待模式可以选择等待和不等待，可等待指定时间、永久等待。</li>
 * <li>当读取事件没有发生且为等待模式时，会发生任务调度，锁任务状态除外。</li>
 * <li>不能在IDLE任务中读事件，需要用户自行保证。</li>
 * <li>不能在系统初始化之前调用读事件接口。</li>
 * </ul>
 *
 * @param  ulEvents [IN] 类型#VOS_UINT32，要读取的事件，此处的事件是按位存储的，每一位代表一个事件。取值范围为非零。
 * @param  pulEvents [OUT] 类型#VOS_UINT32 *，用于保存接收到的事件的指针。取值范围为非空，如果为空会报错。
 * @param  ulFlags [IN] 类型#VOS_UINT32，读取事件所采取的策略,为（VOS_EV_ALL，VOS_EV_ANY）中一个和（VOS_WAIT，VOS_NO_WAIT）中的一个标识或的结果。
 * @param  ulTimerOut [IN] 类型为#VOS_UINT32，等待超时时间，单位为毫秒。0表示永远等待。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_ERRNO_EVENT_TIMEOUT             0x00000040，读事件超时，用户增大事件读取等待时间，或用户在其他任务中给该任务写事件操作。
 * @retval #VOS_ERRNO_EVENT_READ_UNAVAI         0x00000041，期望事件没有发生，用户可使用等待读取事件。
 * @retval #VOS_ERROR                           0xFFFFFFFF，读事件，用户检查是否不在任务中读事件或锁任务调度时读事件。
 * @retval #VOS_OK                              0x00000000，读事件成功。
 * @par 依赖:
 * <ul><li>vos_event.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Ev_Write
 */
extern VOS_UINT32 VOS_Ev_Read(VOS_UINT32 ulEvents, VOS_UINT32 *pulEvents, VOS_UINT32 ulFlags, VOS_UINT32 ulTimerOut);

/**
 * @ingroup  vos_event
 * @brief 写事件。
 *
 * @par 描述:
 * 写任务ID为uwTaskID的指定事件，可以一次性写多个事件，可以在中断中调用。
 *
 * @attention
 * <ul>
 * <li>若指定任务正在等待读取写入的事件，则会激活指定任务，并发生任务调度。</li>
 * <li>不能向IDLE任务写事件，需要用户自行保证。</li>
 * </ul>
 *
 * @param  ulTaskID [IN] 类型#VOS_UINT32，任务ID，表示要对该指定任务进行写事件操作。取值范围为有效的任务ID。
 * @param  ulEvents [IN] 类型#VOS_UINT32，写入的事件号，每一位代表一个事件。取值范围为非零。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，写事件成功。
 * @par 依赖:
 * <ul><li>vos_event.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Ev_Read
 */
extern VOS_UINT32 VOS_Ev_Write(VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
#endif //__VOS_EVENT_H__

