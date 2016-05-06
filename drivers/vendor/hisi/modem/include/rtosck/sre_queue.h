/**
 * @file sre_queue.h
 *
 * Copyright(C), 2011-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：队列模块的对外头文件。 \n
 */

/**@defgroup SRE_queue 队列
  *@ingroup SRE_comm
  */

#ifndef _SRE_QUEUE_H
#define _SRE_QUEUE_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//支持功能宏裁剪,sre_buildef.h文件中支持的功能宏
#if (OS_OPTION_QUEUE == YES) 
/**
 * @ingroup SRE_queue
 * 队列错误码：队列最大资源数配置成0。
 *
 * 值: 0x02002701
 *
 * 解决方案: 队列最大资源数配置大于0，如果不用队列模块，可以配置裁剪开关为NO。
 */
#define OS_ERRNO_QUEUE_MAXNUM_ZERO                     SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x01)

/**
 * @ingroup SRE_queue
 * 队列错误码：初始化队列内存不足。
 *
 * 值: 0x02002702
 *
 * 解决方案: 分配更大的内存分区。
 */
#define OS_ERRNO_QUEUE_NO_MEMORY                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x02)

/**
 * @ingroup SRE_queue
 * 队列错误码：队列创建时内存不足。
 *
 * 值: 0x02002703
 *
 * 解决方案: 可以将内存空间配大。或将创建队列的节点长度和节点个数减少。
 */
#define OS_ERRNO_QUEUE_CREATE_NO_MEMORY                SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x03)

/**
 * @ingroup SRE_queue
 * 队列错误码：没有空闲的队列资源，已经达到配置的最大队列数。
 *
 * 值: 0x02002704
 *
 * 解决方案: 增加配置项中队列资源数配置。
 */
#define OS_ERRNO_QUEUE_CB_UNAVAILABLE                  SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x04)

/**
 * @ingroup SRE_queue
 * 队列错误码：任务切换锁定时，禁止任务阻塞于队列。
 *
 * 值: 0x02002705
 *
 * 解决方案: 使用前，任务先解锁。
 */
#define OS_ERRNO_QUEUE_PEND_IN_LOCK                    SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x05)

/**
 * @ingroup SRE_queue
 * 队列错误码：队列等待超时。
 *
 * 值: 0x02002706
 *
 * 解决方案: 请查看超时时间设置是否合适。
 */
#define OS_ERRNO_QUEUE_TIMEOUT                         SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x06)

/**
 * @ingroup SRE_queue
 * 队列错误码：不能删除被任务阻塞的队列。
 *
 * 值: 0x02002707
 *
 * 解决方案: 让阻塞的任务获得资源，不阻塞在此队列上。
 */
#define OS_ERRNO_QUEUE_IN_TSKUSE                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x07)

/**
 * @ingroup SRE_queue
 * 队列错误码：有超时情况下写队列不能在中断中使用。
 *
 * 值: 0x02002708
 *
 * 解决方案: 同步队列超时时间配置为无等待或者使用异步队列。
 */
#define OS_ERRNO_QUEUE_IN_INTERRUPT                    SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x08)

/**
 * @ingroup SRE_queue
 * 队列错误码：队列未创建。
 *
 * 值: 0x02002709
 *
 * 解决方案: 输入正确的入参。
 */
#define OS_ERRNO_QUEUE_NOT_CREATE                      SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x09)

/**
 * @ingroup SRE_queue
 * 队列错误码：阻塞在任务上的队列被激活，但没有得到调度，不能删除
 *
 * 值: 0x0200270a
 *
 * 解决方案: 等待任务被调度后，就可以删除。
 */
#define OS_ERRNO_QUEUE_BUSY                            SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0a)

/**
 * @ingroup SRE_queue
 * 队列错误码：队列创建时输入的指针为空。
 *
 * 值: 0x0200270b
 *
 * 解决方案: 查看队列创建时输入的指针是否为空。
 */
#define OS_ERRNO_QUEUE_CREAT_PTR_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0b)

/**
 * @ingroup SRE_queue
 * 队列错误码：队列创建时入参队列长度或者队列消息结点大小为0。
 *
 * 值: 0x0200270c
 *
 * 解决方案: 输入正确的入参。
 */
#define OS_ERRNO_QUEUE_PARA_ZERO                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0c)

/**
 * @ingroup SRE_queue
 * 队列错误码：队列句柄非法，错误或超出队列句柄范围。
 *
 * 值: 0x0200270d
 *
 * 解决方案: 查看输入的队列句柄值是否有效。
 */
#define OS_ERRNO_QUEUE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0d)

/**
 * @ingroup SRE_queue
 * 队列错误码：指针为空。
 *
 * 值: 0x0200270e
 *
 * 解决方案: 查看输入的指针是否输入为空。
 */
#define OS_ERRNO_QUEUE_PTR_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0e)

/**
 * @ingroup SRE_queue
 * 队列错误码：读写队列时buffer长度为0。
 *
 * 值: 0x0200270f
 *
 * 解决方案: 输入正确的入参。
 */
#define OS_ERRNO_QUEUE_SIZE_ZERO                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0f)

/**
 * @ingroup SRE_queue
 * 队列错误码：写队列时，输入buffer的大小大于队列结点大小。
 *
 * 值: 0x02002710
 *
 * 解决方案: 减少buffer的大小，或者使用更大结点大小的队列。
 */
#define OS_ERRNO_QUEUE_SIZE_TOO_BIG                    SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x10)

/**
 * @ingroup SRE_queue
 * 队列错误码：读写队列时，没有资源。
 *
 * 值: 0x02002711
 *
 * 解决方案: 写队列前需保证要有空闲的节点，读队列时需保证队列里有消息。
 */
#define OS_ERRNO_QUEUE_NO_SOURCE                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x11)

/**
 * @ingroup SRE_queue
 * 队列错误码：队列优先级参数有误
 *
 * 值: 0x02002712
 *
 * 解决方案: 请检查参数，参数只能是0或1
 */
#define OS_ERRNO_QUEUE_PRIO_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x12)

/**
 * @ingroup SRE_queue
 * 队列错误码：节点长度超过最大值
 *
 * 值: 0x02002713
 *
 * 解决方案: 队列节点长度不能大于0XFFFA
 */
#define OS_ERRNO_QUEUE_NSIZE_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x13)


/**
 * @ingroup SRE_queue
 * 队列优先级类型
 */
typedef enum
{
    OS_QUEUE_NORMAL = 0,      /**< 普通消息队列*/
    OS_QUEUE_URGENT,          /**< 紧急消息队列*/
    OS_QUEUE_BUTT
}OS_QUEUE_PRIO_E;

/**
 * @ingroup SRE_queue
 * 队列等待时间设定：表示永久等待。
 */
#define OS_QUEUE_WAIT_FOREVER     0xFFFFFFFF

/**
 * @ingroup SRE_queue
 * 队列等待时间设定：表示不等待。
 */
#define OS_QUEUE_NO_WAIT          0

/**
 * @ingroup SRE_queue
 * 所有PID。
 */
#define OS_QUEUE_PID_ALL          0xFFFFFFFF

/**
 * @ingroup SRE_queue
 * @brief 创建队列。
 *
 * @par 描述:
 * 创建一个队列，创建时可以设定队列长度和队列结点大小。
 * @attention
 * <ul>
 * <li>每个队列节点的大小的单位是BYTE。</li>
 * <li>每个队列节点的长度自动做2字节对齐。</li>
 * <li>每个队列节点的长度不能大于0xFFFA。</li>
 * </ul>
 * @param usNodeNum      [IN] 类型为#UINT16    ，队列节点个数，不能为0。
 * @param usMaxNodeSize  [IN] 类型为#UINT16    ，每个队列结点的大小。
 * @param puwQueueID     [OUT] 类型为#UINT32 * ，存储队列ID，ID从1开始。
 *
 * @retval #SRE_OK                           0x00000000，操作成功。
 * @retval #OS_ERRNO_QUEUE_CREAT_PTR_NULL    0x0200270b，队列创建时输入的指针为空。
 * @retval #OS_ERRNO_QUEUE_PARA_ZERO         0x0200270c，入参队列长度或者队列消息结点大小为0。
 * @retval #OS_ERRNO_QUEUE_CB_UNAVAILABLE    0x02002704，没有空闲的队列资源数，已经达到配置的最大队列数。
 * @retval #OS_ERRNO_QUEUE_CREATE_NO_MEMORY  0x02002703，队列创建时内存不足。
 * @retval #OS_ERRNO_QUEUE_NSIZE_INVALID     0x02002713,节点长度超过最大值。
 * @par 依赖:
 * @li SRE_queue.h：该接口声明所在的头文件。
 * @since RTOSck V100R001C00
 * @see SRE_QueueDelete
*/
extern UINT32 SRE_QueueCreate(   UINT16 usNodeNum,
                                 UINT16 usMaxNodeSize,
                                 UINT32 *puwQueueID);

/**
 * @ingroup SRE_queue
 * @brief 读队列。
 *
 * @par 描述:
 * 读取指定队列中的数据。将读取到的数据存入pBufferAddr地址，pBufferAddr地址和读取数据大小由用户传入。
 * @attention
 * <ul>
 * <li>队列读取才采用FIFO模式，即先入先出，读取队列中最早写入的数据(相对于队列节点是先后顺序)。</li>
 * <li>如果uwBufferSize大于队列中实际消息的大小，则只返回实际大小的数据，否则只读取uwBufferSize大小的数据。</li>
 * <li>uwBufferSize大小的单位是BYTE。</li>
 * <li>阻塞模式不能在idle钩子使用，需用户保证。</li>
 * <li>在osStart之前不能调用该接口，需用户保证。</li>
 * </ul>
 * @param uwQueueID      [IN]      类型为#UINT32 ，队列ID。
 * @param pBufferAddr    [OUT]     类型为#VOID*  ，读取存放队列中数据的起始地址。
 * @param puwLen         [IN/OUT]  类型为#UINT32 ，传入BUF的大小，输出实际消息的大小。
 * @param uwTimeOut      [IN]      类型为#UINT32 ，超时时间。
 *
 * @retval #SRE_OK                       0x00000000，操作成功。
 * @retval #OS_ERRNO_QUEUE_PTR_NULL      0x0200270e，读队列时输入指针为空。
 * @retval #OS_ERRNO_QUEUE_INVALID       0x0200270d，读队列句柄非法。
 * @retval #OS_ERRNO_QUEUE_SIZE_ZERO     0x0200270f，读队列时输入存放读取的数据buffer大小为0。
 * @retval #OS_ERRNO_QUEUE_NO_SOURCE     0x02002711, 读队列时队列为空。
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE    0x02002709，要读取的队列还未创建。
 * @retval #OS_ERRNO_QUEUE_IN_INTERRUPT  0x02002708, 中断不能被阻塞。
 * @retval #OS_ERRNO_QUEUE_PEND_IN_LOCK  0x02002705，锁任务下不能被阻塞。
 * @retval #OS_ERRNO_QUEUE_TIMEOUT       0x02002706，队列超时。

 * @par 依赖:
 * @li SRE_queue.h：该接口声明所在的头文件。
 * @since RTOSck V100R001C00
 * @see SRE_QueueWrite
*/
extern UINT32 SRE_QueueRead(UINT32  uwQueueID,
                            VOID *  pBufferAddr,
                            UINT32* puwLen,
                            UINT32  uwTimeOut);

/**
 * @ingroup SRE_queue
 * @brief 写队列。
 *
 * @par 描述:
 * 向指定队列写数据。将pBufferAddr地址中uwBufferSize大小的数据写入到队列中。
 * @attention
 * <ul>
 * <li>需保证uwBufferSize大小小于或等于队列结点大小。</li>
 * <li>uwBufferSize大小的单位是BYTE。                </li>
 * <li>阻塞模式不能在idle钩子使用，需用户保证。      </li>
 * <li>在osStart之前不能调用该接口，需用户保证。     </li>
 * </ul>
 * @param uwQueueID      [IN]  类型为#UINT32 ，队列ID。
 * @param pBufferAddr    [IN]  类型为#VOID*  ，写到队列中数据的起始地址。
 * @param uwBufferSize   [IN]  类型为#UINT32 ，写到队列中数据的大小。
 * @param uwTimeOut      [IN]  类型为#UINT32 ，超时时间。
 * @param uwPrio         [IN]  类型为#UINT32 ，优先级, 取值OS_QUEUE_NORMAL或OS_QUEUE_URGENT。
 *
 * @retval #SRE_OK                               0x00000000，操作成功。
 * @retval #OS_ERRNO_QUEUE_PTR_NULL              0x0200270e，写队列时输入指针为空。
 * @retval #OS_ERRNO_QUEUE_INVALID               0x0200270d，写队列句柄非法。
 * @retval #OS_ERRNO_QUEUE_SIZE_TOO_BIG          0x02002710，写队列时，输入buffer的大小大于队列结点大小。
 * @retval #OS_ERRNO_QUEUE_SIZE_ZERO             0x0200270f，写队列时输入要写的数据大小为0。
 * @retval #OS_ERRNO_QUEUE_PRIO_INVALID          0x02002712，队列优先级错误。
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE            0x02002709，队列没有创建。
 * @retval #OS_ERRNO_QUEUE_NO_SOURCE             0x02002711，队列满，没有可写的资源。
 * @retval #OS_ERRNO_QUEUE_IN_INTERRUPT          0x02002708，在中断被阻塞。
 * @retval #OS_ERRNO_QUEUE_PEND_IN_LOCK          0x02002705，锁任务下被阻塞。
 * @retval #OS_ERRNO_QUEUE_TIMEOUT               0x02002706，队列超时。

 * @par 依赖:
 * @li SRE_queue.h：该接口声明所在的头文件。
 * @since RTOSck V100R001C00
 * @see SRE_QueueRead
*/
extern UINT32 SRE_QueueWrite( UINT32 uwQueueID,
                              VOID * pBufferAddr,
                              UINT32 uwBufferSize,
                              UINT32 uwTimeOut,
                              UINT32 uwPrio);

/**
 * @ingroup SRE_queue
 * @brief 删除队列。
 *
 * @par 描述:
 * 删除一个消息队列。删除后队列资源被回收。
 * @attention
 * <ul>
 * <li>不能删除未创建的队列。</li>
 * <li>删除同步队列时，必须确保任务阻塞于该队列，且无被激活后还没及时操作队列的任务，否则删除队列失败。</li>
 * </ul>
 * @param uwQueueID   [IN] 类型为#UINT32  ，队列ID。
 *
 * @retval #SRE_OK                       0x00000000，操作成功。
 * @retval #OS_ERRNO_QUEUE_INVALID       0x0200270d，未找到要删除的队列。
 * @retval #OS_ERRNO_QUEUE_IN_TSKUSE     0x02002707，有任务阻塞于该队列，队列不能删除。
 * @retval #OS_ERRNO_QUEUE_BUSY          0x0200270a，任务被激活但没有及时写队列。
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE    0x02002709，要删除的队列未创建。

 * @par 依赖:
 * @li SRE_queue.h：该接口声明所在的头文件。
 * @since RTOSck V100R001C00
 * @see SRE_QueueCreate | SRE_QueueCreateSyn
 */
extern UINT32 SRE_QueueDelete(UINT32  uwQueueID);

/**
 * @ingroup SRE_queue
 * @brief 获取队列的历史最大使用长度。
 *
 * @par 描述:
 * 获取从队列创建到删除前的历史最大使用长度。
 * @attention
 * <ul>
 * <li>峰值在队列删除前，不会被清零。</li>
 * </ul>
 * @param uwQueueID          [IN]  类型为#UINT32  ，队列ID
 * @param puwQueueUsedNum    [OUT] 类型为#UINT32*  ，队列节点使用峰值
 *
 * @retval #SRE_OK                         0x00000000，操作成功。
 * @retval #OS_ERRNO_QUEUE_INVALID         0x0200270d，未找到要删除的队列。
 * @retval #OS_ERRNO_QUEUE_PTR_NULL        0x0200270e，指针为空。
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE      0x02002709，队列未创建。

 * @par 依赖:
 * @li SRE_queue.h：该接口声明所在的头文件。
 * @since RTOSck V100R002C00
 * @see SRE_QueueNodeNumGet
 */
extern UINT32 SRE_QueueUsedPeak(UINT32 uwQueueID, UINT32 *puwQueueUsedNum);

/**
 * @ingroup SRE_queue
 * @brief 获取指定源PID的待处理消息个数。
 *
 * @par 描述:
 * 从指定队列中，获取指定源PID的待处理消息个数。
 * @attention
 * <ul>
 * <li>PID为OS_QUEUE_PID_ALL时，表示获取所有待处理的消息个数 </li>
 * <li>PID的合法性不做判断，不合法的PID获取的消息个数为0     </li>
 * </ul>
 * @param uwQueueID   [IN] 类型为#UINT32  ，队列ID。
 * @param uwTaskPID   [IN] 类型为#UINT32  ，线程PID。
 * @param puwNum      [OUT]类型为#UINT32*  ，待处理的消息个数。
 *
 * @retval #SRE_OK                         0x00000000，操作成功。
 * @retval #OS_ERRNO_QUEUE_INVALID         0x0200270d，未找到要删除的队列。
 * @retval #OS_ERRNO_QUEUE_PTR_NULL        0x0200270e，指针为空。
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE      0x02002709，队列未创建。

 * @par 依赖:
 * @li SRE_queue.h：该接口声明所在的头文件。
 * @since RTOSck V100R002C00
 * @see SRE_QueueUsedPeak
 */
extern UINT32 SRE_QueueNodeNumGet(UINT32 uwQueueID, UINT32 uwTaskPID, UINT32 *puwNum);
#endif //if (OS_OPTION_QUEUE == YES) 

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _sre_queue_h */



