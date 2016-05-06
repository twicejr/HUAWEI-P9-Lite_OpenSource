/**
 * @file sre_event.h
 *
 * Copyright(C), 2011-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：事件模块的对外头文件。 \n
 */

/**@defgroup SRE_event 事件
  *@ingroup SRE_comm
  */

#ifndef _SRE_EVENT_H
#define _SRE_EVENT_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//支持功能宏裁剪,sre_buildef.h文件中支持的功能宏
#if (YES == OS_OPTION_EVENT)
/**
 * @ingroup SRE_event
 * 事件等待时间设定：事件最大等待超时值设置。
 */
#define OS_EVENT_WAIT_FOREVER   0xFFFFFFFF

/**
 * @ingroup SRE_event
 * 事件读取模式：表示期望uwEventMask中的任何一个事件。
 */
#define OS_EVENT_ANY            0x00000001

/**
 * @ingroup SRE_event
 * 事件读取模式：表示期望接收uwEventMask中的所有事件。
 */
#define OS_EVENT_ALL            0x00000010

/**
 * @ingroup SRE_event
 * 事件读取模式：表示等待接收事件。
 */
#define OS_EVENT_WAIT           0x00010000

/**
 * @ingroup SRE_event
 * 事件读取模式：表示不等待接收事件。
 */
#define OS_EVENT_NOWAIT         0x00100000

/**
 * @ingroup SRE_event
 * 事件错误码：事件读取失败，期望事件没有发生。
 *
 * 值: 0x02002600
 *
 * 解决方案：可使用等待读取事件。
 */
#define OS_ERRNO_EVENT_READ_FAILED                          SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x00)

/**
 * @ingroup SRE_event
 * 事件错误码：读取事件超时。
 *
 * 值: 0x02002601
 *
 * 解决方案：增大事件读取等待时间，或其他任务给该任务写事件操作。
 */
#define OS_ERRNO_EVENT_READ_TIMEOUT                         SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x01)

/**
 * @ingroup SRE_event
 * 事件错误码：写事件时入参任务ID非法。
 *
 * 值: 0x02002602
 *
 * 解决方案: 请输入合法任务ID。
 */
#define OS_ERRNO_EVENT_TASKID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x02)

/**
 * @ingroup SRE_event
 * 事件错误码：写事件时入参任务未创建。
 *
 * 值: 0x02002603
 *
 * 解决方案: 请输入合法任务ID，或先创建任务再对其写事件操作。
 */
#define OS_ERRNO_EVENT_TSK_NOT_CREATED                      SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x03)

/**
 * @ingroup SRE_event
 * 事件错误码：读事件时EVENTMASK入参非法，入参不能为0。
 *
 * 值: 0x02002604
 *
 * 解决方案: 请输入合法值。
 */
#define OS_ERRNO_EVENT_EVENTMASK_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x04)

/**
 * @ingroup SRE_event
 * 事件错误码：只能在任务中进行读事件操作。
 *
 * 值: 0x02002605
 *
 * 解决方案: 请在任务中进行读事件操作。
 */
#define OS_ERRNO_EVENT_READ_NOT_IN_TASK                     SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x05)

/**
 * @ingroup SRE_event
 * 事件错误码：读事件接口中uwFlags入参非法，该入参为（OS_EVENT_ANY，OS_EVENT_ALL）中一个和（OS_EVENT_WAIT，OS_EVENT_NOWAIT）中的一个标识或的结果。OS_EVENT_WAIT模式下，等待时间必须非零。
 *
 * 值: 0x02002606
 *
 * 解决方案: 请输入合法的入参。
 */
#define OS_ERRNO_EVENT_FLAGS_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x06)

/**
 * @ingroup SRE_event
 * 事件错误码：在锁任务调度状态下，禁止任务阻塞于读事件。
 *
 * 值: 0x02002607
 *
 * 解决方案: 请解锁任务调度后，再进行读事件。
 */
#define OS_ERRNO_EVENT_READ_IN_LOCK                         SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x07)

/**
 * @ingroup SRE_event
 * 事件错误码：写事件时EVENT入参非法，入参不能为0。
 *
 * 值: 0x02002608
 *
 * 解决方案: 请输入合法值。
 */
#define OS_ERRNO_EVENT_INVALID                              SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x08)

/**
 *@ingroup SRE_event
 *@brief 读事件。
 *
 *@par 描述:
 *读取当前任务的指定掩码为uwEventMask的事件，可以一次性读取多个事件。事件读取成功后，被读取的事件将被清除。
 *@attention
 * <ul>
 * <li>读取模式可以选择读取任意事件和读取所有事件。</li>
 * <li>等待模式可以选择等待和不等待，可等待指定时间、永久等待。</li>
 * <li>当读取事件没有发生且为等待模式时，会发生任务调度，锁任务状态除外。</li>
 * <li>不能在IDLE任务中读事件，需要用户自行保证。</li>
 * <li>不能在系统初始化之前调用读事件接口。</li>
 * </ul>
 *
 *@param uwEventMask [IN] 类型为#UINT32，设置要读取的事件掩码，每个bit位对应一个事件，1表示要读取。该入参不能为0。
 *@param uwFlags     [IN] 类型为#UINT32，读取事件所采取的策略,为（OS_EVENT_ANY，OS_EVENT_ALL）中一个和（OS_EVENT_WAIT，OS_EVENT_NOWAIT）中的一个标识或的结果。
 *#OS_EVENT_ALL表示期望接收uwEventMask中的所有事件，#OS_EVENT_ANY表示等待uwEventMask中的任何一个事件。
 *#OS_EVENT_WAIT表示若期望事件没有发生，等待接收，#OS_EVENT_NOWAIT表示若期望事件没有发生，将不会等待接收。
 *@param uwTimeOut   [IN] 类型为#UINT32，等待超时时间，单位为tick，取值(0~0xFFFFFFFF]。当uwFlags标志为OS_EVENT_WAIT，这个参数才有效。若值为#OS_EVENT_WAIT_FOREVER，则表示永久等待。
 *@param puwEvents   [OUT] 类型为#UINT32 *，用于保存接收到的事件的指针。如果不需要输出，可以填写NULL。
 *
 *@retval #OS_ERRNO_EVENT_READ_FAILED        0x02002600，事件读取失败，期望事件没有发生。
 *@retval #OS_ERRNO_EVENT_READ_TIMEOUT       0x02002601，读取事件超时。
 *@retval #OS_ERRNO_EVENT_EVENTMASK_INVALID  0x02002604，读事件时EVENTMASK入参非法，入参不能为0。
 *@retval #OS_ERRNO_EVENT_READ_NOT_IN_TASK   0x02002605，只能在任务中进行读事件操作。
 *@retval #OS_ERRNO_EVENT_FLAGS_INVALID      0x02002606，读事件接口中uwFlags入参非法。
 *@retval #OS_ERRNO_EVENT_READ_IN_LOCK       0x02002607，在锁任务调度状态下，禁止任务阻塞于读事件。
 *@retval #SRE_OK                            0x00000000，操作成功。

 *@par 依赖:
 * <ul>
 *@li sre_event.h：该接口声明所在的头文件。
 *@since RTOSck V100R001C00
 * </ul>
 *@see SRE_EventWrite
*/
extern UINT32 SRE_EventRead( UINT32 uwEventMask,
                             UINT32 uwFlags,
                             UINT32 uwTimeOut,
                             UINT32 *puwEvents );

/**
 *@ingroup SRE_event
 *@brief 写事件。
 *
 *@par 描述:
 *写任务ID为uwTaskID的指定事件，可以一次性写多个事件，可以在RTOSck接管的中断中调用。
 *@attention
 * <ul>
 * <li>若指定任务正在等待读取写入的事件，则会激活指定任务，并发生任务调度。</li>
 * <li>不能向IDLE任务写事件，需要用户自行保证。</li>
 * </ul>
 *
 *@param uwTaskID [IN] 类型为#UINT32，任务ID，表示要对某个任务进行写事件操作。
 *@param uwEvents [IN] 类型为#UINT32，事件号，每个bit对应一个事件。
 *
 *@retval #OS_ERRNO_EVENT_TSK_NOT_CREATED     0x02002603，写事件时入参任务未创建。
 *@retval #OS_ERRNO_EVENT_TASKID_INVALID      0x02002602，写事件时入参任务ID非法。
 *@retval #OS_ERRNO_EVENT_INVALID             0x02002608，写事件时入参事件类型非法，不能为零。
 *@retval #SRE_OK                             0x00000000，操作成功。
 *@par 依赖:
 * <ul>
 *@li sre_event.h：该接口声明所在的头文件。
 * </ul>
 *@since RTOSck V100R001C00
 *@see SRE_EventRead
*/
extern UINT32 SRE_EventWrite(UINT32 uwTaskID, UINT32 uwEvents);

#endif //#if (YES == OS_OPTION_EVENT)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_EVENT_H */



