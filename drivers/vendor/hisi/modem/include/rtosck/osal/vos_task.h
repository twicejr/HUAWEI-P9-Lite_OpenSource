/**
 * @file vos_task.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL任务头文件。 \n
 */

/**@defgroup vos_task 任务
 *@ingroup OSAL
*/

#ifndef __VOS_TASK_H__
#define __VOS_TASK_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define VOS_TSK_MIN_STACK_SIZE          0x130
#define VOS_T_PRIORITY_NORMAL           64
#define VOS_TASK_DEFAULT_STACKSIZE      0x1000

typedef VOS_VOID (* TaskStartAddress_PF)
(
    VOS_UINTPTR ulArg0,                 /* 任务处理函数的第一个参数 */
    VOS_UINTPTR ulArg1,                 /* 任务处理函数的第二个参数 */
    VOS_UINTPTR ulArg2,                 /* 任务处理函数的第三个参数 */
    VOS_UINTPTR ulArg3                  /* 任务处理函数的第四个参数 */
);

typedef TaskStartAddress_PF VOS_TASK_ENTRY_TYPE;

/**
 * @ingroup  vos_task
 * @brief 创建任务。
 *
 * @par 描述:
 * 创建一个任务。在系统OS初始化前创建的任务只是简单地加入就绪队列。
 * 系统初始化后创建的任务，如果优先级高于当前任务且未锁任务，则立即发生任务调度并被运行，否则加入就绪队列。
 *
 * @attention
 * <ul>
 * <li>任务名的最大长度为15字节，不含结束符。</li>
 * <li>acTaskName，pfTaskStartAddress，aulTaskArg，pulTaskID都不能为空，否则创建失败。ulTaskPriority不能大于255，否则创建失败。</li>
 * <li>若指定的任务栈大小为0，则使用配置项#VOS_TASK_DEFAULT_STACKSIZE指定的默认的任务栈大小。</li>
 * <li>任务栈的大小必须按16字节大小对齐。确定任务栈大小的原则是，够用就行：多了浪费，少了任务栈溢出。具体多少取决于需要消耗多少的栈内存，视情况而定：函数调用层次越深，栈内存开销越大，局部数组越大，局部变量越多，栈内存开销也越大。</li>
 * <li>任务创建时，任务创建参数中的任务栈大小配置建议不要使用最小任务栈大小VOS_TSK_MIN_STACK_SIZE(大小为0x130)，该项只是包含任务上下文预留的栈空间，任务调度时额外的任务开销需要由用户自行保证足够的任务栈空间配置。</li>
 * <li>每个任务名字只能对应单个任务。</li>
 * </ul>
 *
 * @param  acTaskName[15] [IN] 类型#VOS_CHAR，任务的名字，长度不超过15（不包含结束符'\0'），取值范围为非空。
 * @param  ulTaskPriority [IN] 类型#VOS_UINT32，要创建任务的优先级。取值范围是0～255，数值越大，优先级越高。取值范围为默认值为VOS_T_PRIORITY_NORMAL。
 * @param  ulTaskMode [IN] 类型#VOS_UINT32，该参数忽略，取值范围为任意值。
 * @param  ulTaskStackSize [IN] 类型#VOS_UINT32，要创建任务的任务栈大小，单位为字节。当传入0时，将使用默认值0x1000字节。取值范围不小于VOS_TSK_MIN_STACK_SIZE字节。
 * @param  aulTaskArg[4] [IN] 类型#VOS_UINT32，要传给任务入口函数的VOS_UINPTR类型的参数的首地址。取值范围为任意值。
 * @param  pfTaskStartAddress [IN] 类型#TaskStartAddress_PF，要创建任务的入口函数地址。取值范围为非空。
 * @param  pulTaskID [OUT] 类型#VOS_UINT32 *，保存新创建任务的ID。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_ERRNO_NOMEM                     0x0000000C，内存申请失败。
 * @retval #VOS_OK                              0x00000000，任务创建成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Delete
 */
extern VOS_UINT32 VOS_T_Create(VOS_CHAR acTaskName[15], VOS_UINT32 ulTaskPriority, VOS_UINT32 ulTaskMode, VOS_SIZE_T ulTaskStackSize, VOS_UINTPTR aulTaskArg[4], TaskStartAddress_PF pfTaskStartAddress, VOS_UINT32 *pulTaskID);

/**
 * @ingroup  vos_task
 * @brief 删除任务。
 *
 * @par 描述:
 * 删除指定的任务。
 *
 * @attention
 * <ul>
 * <li>若为自删除，则任务控制块和任务栈在下一次创建任务时才回收。</li>
 * <li>对于任务自删除，RTOSck处理该任务相关的信号量和接收到的消息会强制删除。</li>
 * <li>任务自删除时，任务删除钩子不允许进行pend信号量、挂起等操作。</li>
 * </ul>
 *
 * @param  ulTaskID [IN] 类型#VOS_UINT32，要删除任务ID。取值范围为有效的任务ID。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，删除任务成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Create
 */
extern VOS_UINT32 VOS_T_Delete(VOS_UINT32 ulTaskID);

/**
 * @ingroup  vos_task
 * @brief 锁任务调度。
 *
 * @par 描述:
 * 锁任务调度。任务调度被锁后不再发生任务切换直至真正解锁。
 *
 * @attention
 * <ul>
 * <li>该接口只锁任务调度，并不关中断，因此任务仍可被中断打断。</li>
 * <li>执行该接口则锁计数值加1，解锁则锁计数值减1。因此，必须与#VOS_TaskUnlock配对使用。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval #VOS_OK                              0x00000000，锁任务调度成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_TaskUnlock
 */
extern VOS_UINT32 VOS_TaskLock(VOS_VOID);

/**
 * @ingroup  vos_task
 * @brief 解锁任务调度。
 *
 * @par 描述:
 * 任务锁计数值减1。若嵌套加锁，则只有锁计数值减为0才真正的解锁了任务调度。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>执行该接口则锁计数值加1，解锁则锁计数值减1。因此，必须与#VOS_TaskLock配对使用。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval #VOS_OK                              0x00000000，解锁任务调度成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_TaskUnlock
 */
extern VOS_UINT32 VOS_TaskUnlock(VOS_VOID);

/**
 * @ingroup  vos_task
 * @brief 当前任务释放CPU控制权。
 *
 * @par 描述:
 * 当前任务释放CPU控制权。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>不在任务中，或已锁任务调度时调用该接口，则释放CPU控制权失败。</li>
 * <li>未锁任务调度时，顺取同优先级队列中的下一个任务执行。如没有同级的就绪任务，则不发生任务调度，继续执行原任务。</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Delay | VOS_T_RunDelay
 */
extern VOS_VOID VOS_T_FreeCPU(VOS_VOID);

/**
 * @ingroup  vos_task
 * @brief 任务延迟。
 *
 * @par 描述:
 * 延迟当前运行任务的执行。任务延时等待指定的毫秒数后，重新参与调度。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>硬中断或软中断处理中，或已锁任务，则延时操作失败。</li>
 * <li>若传入参数0，且未锁任务调度，则顺取同优先级队列中的下一个任务执行。如没有同级的就绪任务，则不发生任务调度，继续执行原任务。</li>
 * </ul>
 *
 * @param  ulMillisecond [IN] 类型#VOS_UINT32，要延时的毫秒数，即休眠的时间。单位是毫秒（千分之一秒）。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_FreeCPU | VOS_T_RunDelay
 */
extern VOS_VOID VOS_T_Delay(VOS_UINT32 ulMillisecond);

/**
 * @ingroup  vos_task
 * @brief 让当前任务运行一段时间后延时指定时长。
 *
 * @par 描述:
 * 当前任务运行ulRunMillisecs时长后延时ulDelayMillisecs。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>硬中断或软中断处理中，或已锁任务，则延时操作失败。</li>
 * <li>ulDelayMillisecs如果为0，且未锁任务调度，则顺取同优先级队列中的下一个任务执行。如没有同级的就绪任务，则不发生任务调度，继续执行原任务。</li>
 * </ul>
 *
 * @param  ulRunMillisecs [IN] 类型#VOS_UINT32，任务运行的毫秒数。单位是毫秒（千分之一秒）。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 * @param  ulDelayMillisecs [IN] 类型#VOS_UINT32，要延时的毫秒数，即休眠的时间。单位是毫秒（千分之一秒）。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Delay | VOS_T_FreeCPU
 */
extern VOS_VOID VOS_T_RunDelay(VOS_UINT32 ulRunMillisecs, VOS_UINT32 ulDelayMillisecs);

/**
 * @ingroup  vos_task
 * @brief 挂起任务。
 *
 * @par 描述:
 * 挂起指定的任务，任务将从就绪队列中被删除。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>若为当前任务且已锁任务，则不能被挂起。</li>
 * <li>IDLE任务不能被挂起。</li>
 * <li>任务ID值为0，表示挂起ID为0的任务。</li>
 * </ul>
 *
 * @param  ulTaskID [IN] 类型#VOS_UINT32，要挂起的任务ID。取值范围为有效的任务ID。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，执行底层OS层函数出错。
 * @retval #VOS_OK                              0x00000000，挂起任务成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_T_Suspend(VOS_UINT32 ulTaskID);

/**
 * @ingroup  vos_task
 * @brief 查询指定任务的任务名字。
 *
 * @par 描述:
 * 根据指定的任务ID，查询该任务ID对应的任务名字。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>不能查询ID不合法的任务名。</li>
 * <li>若查询没有创建的任务名，查询失败。</li>
 * <li>任务ID值为0，表示查询ID为0的任务名字。</li>
 * </ul>
 *
 * @param  uwTaskID [IN] 类型#VOS_UINT32，任务ID。取值范围为有效的任务ID。
 *
 * @retval #VOS_NULL_PTR                        0x00000000，查询失败。
 * @retval #任意值                              长度不超过15个字符的任务名字的地址。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_T_GetName
 */
extern VOS_CHAR * VOS_GetTaskName(VOS_UINT32 ulTaskID);

/**
 * @ingroup  vos_task
 * @brief 查询任务名。
 *
 * @par 描述:
 * 根据任务ID，将查询到任务名。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>不能查询ID不合法的任务名。</li>
 * <li>若查询没有创建的任务名，查询失败。</li>
 * <li>任务ID值为0，表示查询ID为0的任务名字。</li>
 * </ul>
 *
 * @param  uwTaskID [IN] 类型#VOS_UINT32，任务ID。取值范围为有效的任务ID。
 * @param  acTaskName[15] [OUT] 类型#VOS_CHAR，长度为不超过15个字符的任务名的地址。取值范围为非空。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，参数错误，查询失败。
 * @retval #VOS_OK                              0x00000000，查询成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_GetTaskName
 */
extern VOS_UINT32 VOS_T_GetName(VOS_UINT32 ulTaskID, VOS_CHAR acTaskName[15]);

/**
 * @ingroup  vos_task
 * @brief 获取当前任务ID。
 *
 * @par 描述:
 * 获取处于运行态的任务ID。
 *
 * @attention
 * <ul>
 * <li>硬中断或软中断处理中，也可获取当前任务ID，即被中断打断的任务。</li>
 * <li>在任务切换钩子处理中调用时，获取的是切入任务的ID。</li>
 * </ul>
 *
 * @param  pulTaskID [OUT] 类型#VOS_UINT32 *，保存任务ID。取值范围为非空。
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF，参数错误，获取任务ID失败。
 * @retval #VOS_OK                              0x00000000，获取任务ID成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_GetTaskName
 */
extern VOS_UINT32 VOS_T_GetSelfID(VOS_UINT32 *pulTaskID);

/**
 * @ingroup  vos_task
 * @brief 判断任务是否有效。
 *
 * @par 描述:
 * 根据任务ID，判断任务是否有效。
 *
 * @attention
 * <ul>
 * <li>任务ID是从0开始编号的。</li>
 * </ul>
 *
 * @param  ulTaskId [IN] 类型#VOS_UINT32，任务ID。取值范围为为任意值。
 *
 * @retval #VOS_TRUE                            0x00000001，任务ID合法。
 * @retval #VOS_FALSE                           0x00000000，任务ID不合法。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_GetTaskName
 */
extern VOS_BOOL VOS_TaskIdValidate(VOS_UINT32 ulTaskId);

/**
 * @ingroup  vos_task
 * @brief 创建任务。
 *
 * @par 描述:
 * 创建一个任务。在系统OS初始化前创建的任务只是简单地加入就绪队列。
 * 系统初始化后创建的任务，如果优先级高于当前任务且未锁任务，则立即发生任务调度并被运行，否则加入就绪队列。
 *
 * @attention
 * <ul>
 * <li>任务名的最大长度为15字节，不含结束符。</li>
 * <li>acTaskName，pfTaskStartAddress，aulTaskArg，pulTaskID都不能为空，否则创建失败。ulTaskPriority不能大于255，否则创建失败。</li>
 * <li>若指定的任务栈大小为0，则使用配置项#VOS_TASK_DEFAULT_STACKSIZE指定的默认的任务栈大小。</li>
 * <li>任务栈的大小必须按16字节大小对齐。确定任务栈大小的原则是，够用就行：多了浪费，少了任务栈溢出。具体多少取决于需要消耗多少的栈内存，视情况而定：函数调用层次越深，栈内存开销越大，局部数组越大，局部变量越多，栈内存开销也越大。</li>
 * <li>任务创建时，任务创建参数中的任务栈大小配置建议不要使用最小任务栈大小OS_TSK_MIN_STACK_SIZE(大小为0x130)，该项只是包含任务上下文预留的栈空间，任务调度时额外的任务开销需要由用户自行保证足够的任务栈空间配置。</li>
 * <li>每个任务名字只能对应单个任务。</li>
 * </ul>
 *
 * @param  puchName [IN] 类型#VOS_CHAR *，任务的名字，长度不超过15（不包含结束符''），取值范围为非空。
 * @param  pulTaskID [OUT] 类型#VOS_UINT32 *，保存新创建任务的ID。取值范围为非空。
 * @param  pfnFunc [IN] 类型#VOS_TASK_ENTRY_TYPE，要创建任务的入口函数地址。取值范围为非空。
 * @param  ulPriority [IN] 类型#VOS_UINT32，要创建任务的优先级。取值范围是0～255，数值越大，优先级越高。取值范围为默认值为VOS_T_PRIORITY_NORMAL。
 * @param  ulStackSize [IN] 类型#VOS_UINT32，要创建任务的任务栈大小。当传入0时，将使用RTOSck系统DOPRA适配层默认值。取值范围为默认值：0x1000字节。
 * @param  ulTaskMode [IN] 类型#VOS_SIZE_T，该参数忽略，取值范围为任意值。
 * @param  aulArgs[4] [IN] 类型#VOS_UINTPTR ，要传给任务入口函数的VOS_UINPTR类型的参数的首地址。取值范围为任意值。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_ERRNO_NOMEM                     0x0000000C，内存申请失败。
 * @retval #VOS_OK                              0x00000000，任务创建成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_DeleteTask
 */
extern VOS_UINT32 VOS_CreateTask(VOS_CHAR *puchName, VOS_UINT32 *pulTaskID, VOS_TASK_ENTRY_TYPE pfnFunc, VOS_UINT32 ulPriority, VOS_SIZE_T ulStackSize, VOS_UINTPTR aulArgs[4]);

/**
 * @ingroup  vos_task
 * @brief 删除任务。
 *
 * @par 描述:
 * 删除指定的任务。
 *
 * @attention
 * <ul>
 * <li>若为自删除，则任务控制块和任务栈在下一次创建任务时才回收。</li>
 * <li>对于任务自删除，RTOSck处理该任务相关的信号量和接收到的消息会强制删除。</li>
 * <li>任务自删除时，任务删除钩子不允许进行pend信号量、挂起等操作。</li>
 * </ul>
 *
 * @param  ulTaskID [IN] 类型#VOS_UINT32，要删除任务ID。取值范围为有效的任务ID。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，删除任务失败。
 * @retval #VOS_OK                              0x00000000，删除任务成功。
 * @par 依赖:
 * <ul><li>vos_task.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Create
 */
extern VOS_UINT32 VOS_DeleteTask(VOS_UINT32 ulTaskID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_TASK_H__

