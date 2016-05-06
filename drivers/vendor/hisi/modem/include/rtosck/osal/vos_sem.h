/**
 * @file vos_sem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL信号量头文件。 \n
 */

/**@defgroup vos_sem 信号量
 *@ingroup OSAL
*/

#ifndef __VOS_SEM_H__
#define __VOS_SEM_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define VOS_SM_NAME_LENGTH                      16
#define VOS_SEMA4_FIFO                          0x00000001
#define VOS_SEMA4_PRIOR                         0x00000002
#define VOS_SEMA4_DELETE_SAFE                   0x00000004
#define VOS_SEMA4_INVERSION_SAFE                0x00000008
#define VOS_SM_PRIOR                            ((VOS_UINT32)1)

/**
 * @ingroup  vos_sem
 * @brief 创建一个互斥信号量。
 *
 * @par 描述:
 * 创建一个互斥信号量。
 *
 * @attention
 * <ul><li>创建是否成功会受到"最大支持信号量"配置项的限制。</li></ul>
 *
 * @param  acSmName[VOS_SM_NAME_LENGTH] [IN] 类型#VOS_CHAR，该参数忽略，取值范围为任意值。
 * @param  ulFlags [IN] 类型#VOS_UINT32，互斥信号量类型。互斥信号量的调度方式只支持优先级，取值只能为VOS_SEMA4_PRIOR，其他类型会报错。
 * @param  pulSmID [OUT] 类型#VOS_UINT32 *，保存互斥信号量ID。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，互斥信号量创建成功。
 * @par 依赖:
 * <ul><li>vos_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmB_Create | VOS_SmCCreate | VOS_SmDelete
 */
extern VOS_UINT32 VOS_SmMCreate(VOS_CHAR acSmName[VOS_SM_NAME_LENGTH], VOS_UINT32 ulFlags, VOS_UINT32 *pulSmID);

/**
 * @ingroup  vos_sem
 * @brief 创建一个二进制信号量。
 *
 * @par 描述:
 * 创建一个二进制信号量。
 *
 * @attention
 * <ul><li>创建是否成功会受到"最大支持信号量"配置项的限制。</li></ul>
 *
 * @param  acSmName[4] [IN] 类型#VOS_CHAR，该参数忽略，取值范围为任意值。
 * @param  ulSmInit [IN] 类型#VOS_UINT32，二进制信号量的初值。二进制信号量最多可以被锁一次，即P操作只能作一次。初始值为0表示信号量开始时不能被锁，为1表示可以锁一次。取值范围为{0，1}。如果没有输入它们两者中的任何一个会报错。
 * @param  ulFlags [IN] 类型#VOS_UINT32，二进制信号量类型。取值范围为{VOS_SM_FIFO，VOS_SM_PRIOR}。如果没有输入它们两者中的任何一个会报错。
 * @param  pulSmID [OUT] 类型#VOS_UINT32 *，保存二进制信号量ID。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，二进制信号量创建成功。
 * @par 依赖:
 * <ul><li>vos_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmMCreate | VOS_SmCCreate | VOS_SmDelete
 */
extern VOS_UINT32 VOS_SmB_Create(VOS_CHAR acSmName[4], VOS_UINT32 ulSmInit, VOS_UINT32 ulFlags, VOS_UINT32 *pulSmID);

/**
 * @ingroup  vos_sem
 * @brief 创建一个计数型信号量。
 *
 * @par 描述:
 * 创建一个计数型信号量。
 *
 * @attention
 * <ul><li>创建是否成功会受到"最大支持信号量"配置项的限制。</li></ul>
 *
 * @param  acSmName[VOS_SM_NAME_LENGTH] [IN] 类型#VOS_CHAR，该参数忽略，取值范围为任意值。
 * @param  ulSmInit [IN] 类型#VOS_UINT32，计数型信号量的初值。取值范围为0～0xFFFFFFFE。
 * @param  ulFlags [IN] 类型#VOS_UINT32，计数型信号量类型。等待该计数型信号量的任务的调度方式：VOS_SEMA4_FIFO或VOS_SEMA4_PRIOR，二者只能取其一。如果没有输入它们两者中的任何一个，默认采用VOS_SEMA4_FIFO。则取值范围为:{VOS_SEMA4_FIFO，VOS_SEMA4_PRIOR}。
 * @param  pulSmID [OUT] 类型#VOS_UINT32 *，保存二进制信号量ID。取值范围为非空。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，二进制信号量创建成功。
 * @par 依赖:
 * <ul><li>vos_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmMCreate | VOS_SmB_Create | VOS_SmDelete
 */
extern VOS_UINT32 VOS_SmCCreate(VOS_CHAR acSmName[VOS_SM_NAME_LENGTH], VOS_UINT32 ulSmInit, VOS_UINT32 ulFlags, VOS_UINT32 *pulSmID);

/**
 * @ingroup  vos_sem
 * @brief 删除一个信号量。
 *
 * @par 描述:
 * 删除用户传入的信号量句柄指定的信号量，如果有任务阻塞于该信号量，则删除失败。
 *
 * @attention 无
 *
 * @param ulSmID [IN] 类型为#VOS_UINT32，信号量ID，取值范围为有效的信号量ID。
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查自己的输入参数。
 * @retval #VOS_OK                              0x00000000，信号量删除成功。
 * @par 依赖:
 * <ul><li>vos_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmMCreate | VOS_SmB_Create | VOS_SmCCreate
 */
extern VOS_UINT32 VOS_SmDelete(VOS_UINT32 ulSmID);

/**
 * @ingroup  vos_sem
 * @brief 等待一个信号量。
 *
 * @par 描述:
 * 等待用户传入指定的信号量，若其计数器值大于0，则直接减1返回成功，否则任务阻塞。
 * 等待其他线程发布该信号量，可设置等待超时时间。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>等待时间可以选择零等待、等待特定时间、永久等待。</li>
 * <li>该接口只能被任务调用。</li>
 * <li>在锁任务情况下，用户要PEND信号量，要保证当前有可用信号量资源。</li>
 * </ul>
 *
 * @param ulSmID [IN] 类型为#VOS_UINT32，信号量ID，取值范围为有效的信号量ID。
 * @param ulTimeOutInMillSec [IN] 类型为#VOS_UINT32，同步超时等待时间，单位为毫秒。0表示永远等待。取值范围为不超过（0xFFFFFFFF/每秒所包含的Tick数）。

 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查信号量ID是否合法。
 * @retval #VOS_ERROR                           0xFFFFFFFF，等待信号量发生错误，用户检查是否存在如下情形:1.不在任务中或锁任务调度时等待信号量；2.等待信号量超时。
 * @retval #VOS_OK                              0x00000000，等待信号量成功。
 * @par 依赖:
 * <ul><li>vos_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmV
 */
extern VOS_UINT32 VOS_SmP(VOS_UINT32 ulSmID, VOS_UINT32 ulTimeOutInMillSec);

/**
 * @ingroup  vos_sem
 * @brief 异步等待信号量。
 *
 * @par 描述:
 * 异步等待信号量，如果信号量的计数值不为0，将会使得信号量的计数器值减1。如果信号量的计数值为0，则返回失败，而不会阻塞。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>该接口只能被任务调用。</li>
 * </ul>
 *
 * @param ulSmID [IN] 类型为#VOS_UINT32，信号量ID，取值范围为有效的信号量ID。

 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查信号量ID是否合法。
 * @retval #VOS_ERROR                           0xFFFFFFFF，异步等待信号量失败。
 * @retval #VOS_OK                              0x00000000，异步等待信号量成功。
 * @par 依赖:
 * <ul><li>vos_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmV
 */
extern VOS_UINT32 VOS_Sm_AsyP(VOS_UINT32 ulSmID);

/**
 * @ingroup  vos_sem
 * @brief 发布指定的信号量。
 *
 * @par 描述:
 * 发布指定的信号量，若没有任务等待该信号量，则直接将计数器加1返回。
 * 否则根据唤醒方式唤醒相应的阻塞任务，FIFO方式唤醒最早阻塞的任务，优先级方式唤醒阻塞在此信号量的最高优先级任务。
 *
 * @attention
 * <ul>
 * <li>在osStart之前不能调用该接口。</li>
 * <li>在未锁任务的情况下，如果唤醒的任务优先级高于当前任务，则会立刻发生任务切换。</li>
 * <li>发生任务切换时，如果支持优先级唤醒方式，且创建信号量时指定唤醒方式为优先级，则唤醒阻塞在该信号量上的最高优先级任务。</li>
 * </ul>
 *
 * @param ulSmID [IN] 类型为#VOS_UINT32，信号量ID，取值范围为有效的信号量ID。

 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016，参数错误，用户需要检查信号量ID是否合法。
 * @retval #VOS_ERROR                           0xFFFFFFFF，发布信号量发生错误，用户检查是否存在如下情形:1.信号量加操作后溢出；2.中断中释放互斥型信号量；3.非互斥信号量的持有者在释放此互斥信号量。
 * @retval #VOS_OK                              0x00000000，发布信号量成功。
 * @par 依赖:
 * <ul><li>vos_sem.h：该接口声明所在的头文件。</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmP
 */
extern VOS_UINT32 VOS_SmV(VOS_UINT32 ulSmID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_SEM_H__

