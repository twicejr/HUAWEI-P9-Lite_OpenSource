/**
* @file sre_sync.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述： 核间同步的对外头文件。 \n
*/

/** @defgroup SRE_sync 核间同步互斥
 *@ingroup SRE_comm
 */

#ifndef _SRE_SYNC_H
#define _SRE_SYNC_H

#include "sre_base.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup  SRE_sync
 * 核间同步信息的模式----计数模式。
 */
#define OS_SYNC_BARRIER_MODE_COUNT                          0

/**
 * @ingroup  SRE_sync
 * 核间同步信息的模式----核模式。
 */
#define OS_SYNC_BARRIER_MODE_CHNID                          1

/**
 * @ingroup  SRE_sync
 * 系统核间同步信息的结构体定义。
 */
typedef struct tagSyncBarrier
{
    volatile UINT32 vuwLock;        /**< 锁资源：核间互斥锁。         */
    volatile UINT16 vusMode;        /**< 同步模式：核模式或计数模式。 */
    volatile UINT16 vusGateValue;   /**< 同步阈值：用以检测是否所有的核都已经同步。     */
    volatile UINT32 vuwRealValue;   /**< 实时值：每个核同步时，会修改该值，所有核同步后，该值重置为初始值。  */
    volatile UINT32 vuwInitValue;   /**< 初始值：初始和所有核同步后，该值被赋给实时值。 */
} OS_SYNC_BARRIER_S;

#if(OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup  SRE_sync
 * @brief spinlock操作。
 *
 * @par 描述:
 * 使用spinlock功能对临界资源进行加锁。
 *
 * @attention
 * <ul>
 * <li>只支持SD6183平台。</li>
 * <li>输入的地址对应的物理地址必须是32字节对齐的GLOBAL LL2地址，并且该地址不可Cache，另外，该地址的内容必须被清零，否则会不生效。</li>
 * <li>若输入的物理地址为NULL，则直接返回。</li>
 * </ul>
 *
 * @param  pvuwAddress [INT] 类型#volatile UINT32 *，执行加锁操作的地址。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_sync.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_SplIrqLock
 */
extern VOID SRE_SplLock(volatile UINT32 *pvuwAddress);

/**
 * @ingroup  SRE_sync
 * @brief spinunlock操作。
 *
 * @par 描述:
 * 使用spinunlock功能对临界资源进行解锁。
 *
 * @attention
 * <ul>
 * <li>只支持SD6183平台。</li>
 * <li>输入的地址对应的物理地址必须是32字节对齐的GLOBAL LL2地址，并且该地址不可Cache，另外，该地址的内容必须被清零，否则会不生效。</li>
 * <li>若输入的物理地址为NULL，则直接返回。</li>
 * </ul>
 *
 * @param  pvuwAddress [INT] 类型#volatile UINT32 *，执行加锁操作的地址。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_sync.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_SplIrqUnlock
 */
extern VOID SRE_SplUnlock(volatile UINT32 *pvuwAddress);

/**
 * @ingroup  SRE_sync
 * @brief 关中断条件下进行spinlock操作。
 *
 * @par 描述:
 * 使用spinlock功能在关中断条件下对临界资源进行加锁。
 *
 * @attention
 * <ul>
 * <li>只支持SD6183平台。</li>
 * <li>输入的地址对应的物理地址必须是32字节对齐的GLOBAL LL2地址，并且该地址不可Cache，另外，该地址的内容必须被清零，否则会不生效。</li>
 * <li>若输入的物理地址为NULL，则直接返回。</li>
 * </ul>
 *
 * @param  pvuwAddress [INT] 类型#volatile UINT32 *，执行加锁操作的地址。
 *
 * @retval 关闭全局中断前的中断状态值
 * @par 依赖:
 * <ul><li>sre_sync.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_SplLock
 */
extern UINT32 SRE_SplIrqLock(volatile UINT32 *pvuwAddress);

/**
 * @ingroup  SRE_sync
 * @brief 开中断条件进行spinunlock操作。
 *
 * @par 描述:
 * 使用spinunlock功能在开中断条件下对临界资源进行解锁。
 *
 * @attention
 * <ul>
 * <li>只支持SD6183平台。</li>
 * <li>输入的地址对应的物理地址必须是32字节对齐的GLOBAL LL2地址，并且该地址不可Cache，另外，该地址的内容必须被清零，否则会不生效。</li>
 * <li>若输入的物理地址为NULL，则直接返回。</li>
 * </ul>
 *
 * @param  pvuwAddress [INT] 类型#volatile UINT32 *，执行加锁操作的地址。
 * @param  uwIntSave   [INT] 类型#UINT32，执行关中断条件下加锁操作的返回值。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_sync.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_SplUnlock
 */
extern VOID SRE_SplIrqUnlock(volatile UINT32 *pvuwAddress, UINT32 uwIntSave);

#endif


#if (OS_OPTION_KERNEL_PROCESS == NO)

/**
 * @ingroup  SRE_sync
 * @brief 指定的方式等待多核同步。
 *
 * @par 描述:
 * 多核操作，以指定的模式进行多核同步。
 *
 * @attention
 * <ul>
 *<li>全局变量入参pstBarrier请保存在不可cache的共享内存中。</li>
 *<li>对多进程下的内核进程不支持该接口</li>
 *<li>实时值需与初始值取值相同。</li>
 *<li>锁资源取值不限，仅用其地址值。</li>
 *<li>同步阈值取值不限，仅用在同步前后进行对比。</li>
 *<li>两种核间同步模式:OS_SYNC_BARRIER_MODE_COUNT表示计数模式和OS_SYNC_BARRIER_MODE_CHNID表示核模式。</li>
 *<li>对于核数超过32个的平台(如SD6183)，不支持核模式的同步</li>
 *<li>计数模式(#OS_SYNC_BARRIER_MODE_COUNT)下:初始值为总共需要同步的核数。</li>
 *<li>指定核模式(#OS_SYNC_BARRIER_MODE_CHNID)下:32位的初始值可最大容纳32个核进行同步，每一位代表一个核，例如:初始值为0x03，表示核0和核1之间的核间同步。</li>
 * </ul>

 * @param  pstBarrier   [IN] 类型#volatile OS_SYNC_BARRIER_S *，核间同步结构体信息。
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_sync.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_WaitForAllCores
 */
extern VOID SRE_SyncBarrierWait(volatile OS_SYNC_BARRIER_S *pstBarrier);

/**
 * @ingroup  SRE_sync
 * @brief 等待所有核同步，若为多实例场景，则等待的核数为该实例内的所有核。
 *
 * @par 描述:
 * 多核操作，一个核等待所有其他核在此同步。
 *
 * @attention
 * <ul>
 * <li>系统中所运行的核均在此同步。</li>
 * <li>对多进程下的内核进程不支持该接口</li>
 * </ul>
 *
 * @param  无
 *
 * @retval 无
 * @par 依赖:
 * <ul><li>sre_sync.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SyncBarrierWait
 */
extern VOID SRE_WaitForAllCores(VOID);

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif // _SRE_SYNC_H




