/**
 * @file vos_queue.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL队列头文件。 \n
 */

/**@defgroup vos_queue 队列
 *@ingroup OSAL
*/

#ifndef __VOS_QUEUE_H__
#define __VOS_QUEUE_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (YES == OS_OPTION_QUEUE)

#define VOS_URGENT                  ((VOS_UINT32)1 << 28)
#define VOS_NORMAL                  ((VOS_UINT32)1 << 29)
#define VOS_QUE_NODE_SIZE           (sizeof(VOS_UINTPTR) * 4)
#define VOS_DEFAULT_QUEUE_SIZE      64
#define VOS_Q_PRIOR                 ((VOS_UINT32)1)
#define VOS_Q_FIFO                  ((VOS_UINT32)1 << 1)
#define VOS_Q_ASYN                  ((VOS_UINT32)1 << 2)
#define VOS_Q_SYN                   ((VOS_UINT32)1 << 3)

/**
 * @ingroup vos_queue
 * 队列错误码：异步读队列时，队列为空。
 *
 * 值: 0x00000030
 *
 * 解决方案: 读队列时需保证队列里有消息。
 */
#define VOS_ERRNO_QUEUE_READ_NOMSG          0x00000030

/**
 * @ingroup vos_queue
 * 队列错误码：同步读队列时，发生超时。
 *
 * 值: 0x00000031
 *
 * 解决方案: 请查看超时时间设置是否合适。
 */
#define VOS_ERRNO_QUEUE_READ_TIMEOUT        0x00000031

/**
 * @ingroup vos_queue
 * 队列错误码：异步写队列时，队列已满。
 *
 * 值: 0x00000032
 *
 * 解决方案: 写队列前需保证要有空闲的节点。
 */
#define VOS_ERRNO_QUEUE_WRITE_MSGFULL       0x00000032

/**
 * @ingroup vos_queue
 * 队列错误码：同步写队列时，发生超时。
 *
 * 值: 0x00000033
 *
 * 解决方案: 请查看超时时间设置是否合适。
 */
#define VOS_ERRNO_QUEUE_WRITE_TIMEOUT       0x00000033

/**
 * @ingroup vos_queue
 * 队列错误码：同步读写队列时，队列已经被删除。
 *
 * 值: 0x00000034
 *
 * 解决方案: 输入正确的入参。
 */
#define VOS_ERRNO_QUEUE_QUEUEDELETED        0x00000034

/**
 * @ingroup  vos_queue
 * @brief 创建一个消息队列。
 *
 * @description
 * 创建一个消息队列，该消息队列名称为chQueName、长度为ulQueDepth。创建成功后，把创建好的队列ID保存在输出参数指针pulQueueID中。
 *
 * @attention
 * <ul>
 * <li>每个队列节点的大小的单位是BYTE。</li>
 * <li>每个队列节点的长度自动做2字节对齐。</li>
 * <li>每个队列节点的长度为VOS_QUE_NODE_SIZE字节，消息的最大长度为VOS_QUE_NODE_SIZE字节</li>
 * </ul>
 *
 * @param chQueName[4] [IN] 类型为#VOS_CHAR，要创建的队列名称，长度为4字节。队列名称可以为空字符串，可以重名。建议传入不为空字符串，且命名规范。
 * @param ulQueDepth [IN] 类型为#VOS_UINT32，要创建队列的消息个数，即能够容纳多少个消息。若取值为0，表示使用缺省的队列长度，为64。
 * @param ulFlags [IN] 类型为#VOS_UINT32，消息队列的阻塞模式，该参数忽略，取值范围为任意值。
 * @param pulQueueID [OUT] 类型为#VOS_UINT32 *，用于保存创建的队列ID的指针。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，chQueName或者pulQueueID为空，请输入有效的队列名称或队列ID的指针。
 * @retval #VOS_ERRNO_NOMEM                     0x0000000c，内存不足，请先释放一部分内存。
 * @retval #VOS_ERROR                           0xFFFFFFFF，没有空闲的队列资源，增加配置项中队列资源数配置。
 * @retval #VOS_OK                              0x00000000，创建消息队列成功。
 * @par 依赖:
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Delete
 */
extern VOS_UINT32 VOS_Que_Create(VOS_CHAR chQueName[4], VOS_UINT32 ulQueDepth, VOS_UINT32 ulFlags, VOS_UINT32 *pulQueueID);

/**
 * @ingroup  vos_queue
 * @brief 删除指定的消息队列。
 *
 * @description
 * 根据传入的ulQueueID，删除相应的消息队列。删除后队列资源被回收。
 *
 * @attention
 * <ul>
 * <li>不能删除未创建的队列。</li>
 * <li>删除同步队列时，必须确保无任务阻塞于该队列，且无被激活后还没及时操作队列的任务，否则删除队列失败。</li>
 * </ul>
 *
 * @param ulQueueID [IN] 类型为#VOS_UINT32，要删除的队列ID，取值范围为合法的队列ID。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，输入参数ulQueueID非法。用户需要检查自己的输入参数。
 * @retval #VOS_ERROR                           0xFFFFFFFF，删除队列失败，可能的原因为释放队列内存失败。
 * @retval #VOS_OK                              0x00000000，删除队列成功。
 * @par 依赖:
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Create
 */
extern VOS_UINT32 VOS_Que_Delete(VOS_UINT32 ulQueueID);

/**
 * @ingroup  vos_queue
 * @brief 写消息队列。
 *
 * @description
 * 根据传入的ulFlags，同步或者异步写一个消息到队列ulQueueID中，将消息写到队列尾部，待写入消息地址在aulQueMsg，长度为VOS_QUE_NODE_SIZE。
 * 同步写队列时，如果消息队列满，则写队列的任务将被阻塞，并等待写入直到超时（即uiTimeOut毫秒）或者队列消息被读出。
 *
 * @attention
 * <ul>
 * <li>阻塞模式不能在idle钩子使用，需用户保证。</li>
 * <li>在osStart之前不能调用该接口，需用户保证。</li>
 * </ul>
 *
 * @param ulQueueID [IN] 类型为#VOS_UINT32，要写的队列ID，取值范围为合法的队列ID。
 * @param aulQueMsg[4] [IN] 类型为#VOS_UINTPTR，待发送消息的地址。取值范围为非空。
 * @param ulFlags [IN] 类型为#VOS_UINT32，写队列的模式，同步或异步，取值范围为{VOS_WAIT|VOS_URGENT，VOS_NO_WAIT|VOS_URGENT，VOS_WAIT|VOS_NORMAL，VOS_NO_WAIT|VOS_NORMAL}。
 * @param ulTimeOut [IN] 类型为#VOS_UINT32，同步写队列时，写阻塞超时等待时间。单位为毫秒。为0表示永远等待。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，输入参数ulQueueID非法或aulQueMsg为空指针。用户需要检查自己的输入参数。
 * @retval #VOS_ERRNO_QUEUE_WRITE_MSGFULL       0x00000032，异步写队列时，队列已满。
 * @retval #VOS_ERRNO_QUEUE_WRITE_TIMEOUT       0x00000033，同步写队列时，发生超时。
 * @retval #VOS_ERRNO_QUEUE_QUEUEDELETED        0x00000034，同步读队列时，队列已经被删除。
 * @retval #VOS_ERROR                           0xFFFFFFFF，写队列失败，可能的原因是任务切换锁定时或不在任务中写队列。
 * @retval #VOS_OK                              0x00000000，写队列成功。
 * @par 依赖:
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Read
 */
extern VOS_UINT32 VOS_Que_Write(VOS_UINT32 ulQueueID, VOS_UINTPTR aulQueMsg[4], VOS_UINT32 ulFlags, VOS_UINT32 ulTimeOut);

/**
 * @ingroup  vos_queue
 * @brief 读消息队列。
 *
 * @description
 * 根据传入的ulFlags，同步或者异步读取队列 ulQueueID 中的一个消息。将读取到的消息保存到地址为 aulQueMsg， 大小为VOS_QUE_NODE_SIZE的缓冲区。
 * 同步读队列时，如果队列为空，读取队列的任务将被阻塞，并等待读取直到超时（即ulTimeOut毫秒）或者有消息写入。
 *
 * @attention
 * <ul>
 * <li>队列读取才采用FIFO模式，即先入先出，读取队列中最早写入的数据(相对于队列节点是先后顺序)。</li>
 * <li>阻塞模式不能在idle钩子使用，需用户保证。</li>
 * <li>在osStart之前不能调用该接口，需用户保证。</li>
 * </ul>
 *
 * @param ulQueueID [IN] 类型为#VOS_UINT32，要读取的队列ID，取值范围为合法的队列ID。
 * @param aulQueMsg[4] [OUT] 类型为#VOS_UINTPTR，存放读取出来的消息的Buffer，长度为VOS_QUE_NODE_SIZE。读取成功后，消息将拷贝到此缓冲区中。取值范围为非空。
 * @param ulFlags [IN] 类型为#VOS_UINT32，读队列的模式，同步或异步，取值范围为{VOS_WAIT，VOS_NO_WAIT}。
 * @param ulTimeOut [IN] 类型为#VOS_UINT32，同步读队列时，队列阻塞超时等待时间，以毫秒为单位。为0表示永远等待。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，输入参数ulQueueID非法或aulQueMsg为空指针。用户需要检查自己的输入参数。
 * @retval #VOS_ERRNO_QUEUE_READ_NOMSG          0x00000030，异步读队列时，队列为空。
 * @retval #VOS_ERRNO_QUEUE_READ_TIMEOUT        0x00000031，同步读队列时，发生超时。
 * @retval #VOS_ERRNO_QUEUE_QUEUEDELETED        0x00000034，同步读队列时，队列已经被删除。
 * @retval #VOS_ERROR                           0xFFFFFFFF，读队列失败，可能的原因是任务切换锁定时或不在任务中读队列。
 * @retval #VOS_OK                              0x00000000，读队列成功。
 * @par 依赖:
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Write
 */
extern VOS_UINT32 VOS_Que_Read(VOS_UINT32 ulQueueID, VOS_UINTPTR aulQueMsg[4], VOS_UINT32 ulFlags, VOS_UINT32 ulTimeOut);

/**
 * @ingroup  vos_queue
 * @brief 获取一个消息队列中的消息数目。
 *
 * @description
 * 获取队列ulQueueID的消息数目，存储于pulMsgNum中。
 *
 * @attention 无
 *
 * @param ulQueueID [IN] 类型为#VOS_UINT32，要获取消息数目的队列ID。取值范围为合法的队列ID。
 * @param pulMsgNum [OUT] 类型为#VOS_UINT32 *，存储获取到的消息数目，取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，输入参数ulQueueID非法或pulMsgNum为空指针。用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取队列ulQueueID的消息数目成功。
 * @par 依赖:
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_Que_GetMsgNum(VOS_UINT32 ulQueueID, VOS_UINT32 *pulMsgNum);

/**
 * @ingroup  vos_queue
 * @brief 获取一个消息队列中最大消息个数。
 *
 * @description
 * 获取指定队列ulQueueID的最大消息个数，即该队列能够容纳的最多的消息个数。获取成功后，最大的消息个数存在输出参数指针pulMaxNum中。
 *
 * @attention 无
 *
 * @param ulQueueID [IN] 类型为#VOS_UINT32，要获取消息数目的队列ID。取值范围为合法的队列ID。
 * @param pulMaxNum [OUT] 类型为#VOS_UINT32 *，保存获取到的消息队列的最大消息个数。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，输入参数ulQueueID非法或输入参数pulMaxNum是空指针。用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取消息队列中最大消息个数成功。
 * @par 依赖:
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_Que_GetMaxNum(VOS_UINT32 ulQueueID, VOS_UINT32 *pulMaxNum);

/**
 * @ingroup  vos_queue
 * @brief 获取队列的名字。
 *
 * @description
 *
 * 获取ulQueueID对应队列的名字，存储于chQueName。
 *
 * @attention 无
 *
 * @param ulQueueID [IN] 类型为#VOS_UINT32，要获取名字的消息队列ID。取值范围为合法的队列ID。
 * @param chQueName[4] [OUT] 类型为#VOS_CHAR，用于存储获取到的队列的名字，长度为4字节。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，队列名字获取失败，输入参数ulQueueID非法或输入参数chQueName是空指针。用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，获取队列名成功。
 * @par 依赖:
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see 无
 */
extern VOS_UINT32 VOS_Que_GetName(VOS_UINT32 ulQueueID, VOS_CHAR chQueName[4]);

/**
 * @ingroup  vos_queue
 * @brief 删除指定的消息队列。
 *
 * @description
 * 根据传入的ulQueueID，删除相应的消息队列。删除后队列资源被回收。
 *
 * @attention
 * <ul>
 * <li>不能删除未创建的队列。</li>
 * <li>删除同步队列时，必须确保无任务阻塞于该队列，且无被激活后还没及时操作队列的任务，否则删除队列失败。</li>
 * </ul>
 *
 * @param ulQueueID [IN] 类型为#VOS_UINT32，要删除的队列ID，取值范围为合法的队列ID。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，输入参数ulQueueID非法。用户需要检查自己的输入参数。
 * @retval #VOS_ERROR                           0xFFFFFFFF，删除队列失败，可能的原因为释放队列内存失败。
 * @retval #VOS_OK                              0x00000000，删除队列成功。
 * @par 依赖:
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Create
 */
extern VOS_UINT32 VOS_QueueDelete(VOS_UINT32 ulQueueID);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_QUEUE_H__

