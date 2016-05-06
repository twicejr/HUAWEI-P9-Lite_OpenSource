/**
  * @file sre_hunt.h
  *
  * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
  *
  * 描述：PID获取的对外头文件。\n
  */

#ifndef _SRE_HUNT_H
#define _SRE_HUNT_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**@defgroup sre_hunt Hunt处理
  *@ingroup SRE_comm
  */

/**
 * @ingroup sre_hunt
 * HUNT错误码：HUNT模块初始化失败。
 *
 * 值: 0x02001f00
 *
 * 解决方案：确保内存空间足够大，SD6183:从实例间共享UNCACHE空间申请，其他平台:从共享静态fsc内存或者私有fsc内存分区申请。
 */
#define OS_ERRNO_HUNT_INIT_ERROR            SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x00)

/**
 * @ingroup sre_hunt
 * HUNT错误码：创建任务或软中断时，线程名重名。
 *
 * 值: 0x02001f01
 *
 * 解决方案：创建任务或软中断时，确保线程名本核内唯一。
 */
#define OS_ERRNO_HUNT_THREAD_NAME_REPEAT    SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x01)

/**
 * @ingroup sre_hunt
 * HUNT错误码：通过进程ID及线程名获取线程TID时，该线程未创建或已删除。
 *
 * 值: 0x02001f02
 *
 * 解决方案：确保线程已创建且未被删除。
 */
#define OS_ERRNO_HUNT_THREAD_NOT_CREAT      SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x02)

/**
 * @ingroup sre_hunt
 * HUNT错误码：通过线程ID获取线程名时入参指针为空； 或通过名获取进程PID时入参非法；通过进程ID获取进程名时入参指针为空。
 *
 * 值: 0x02001f03
 *
 * 解决方案：确保入参指针非空、入参线程ID及进程ID等的合法性。
 */
#define OS_ERRNO_HUNT_ILLEGAL_INPUT         SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x03)

/**
 * @ingroup sre_hunt
 * HUNT错误码：通过线程名或进程名获取ID时，Hunt还表没有初始化。
 *
 * 值: 0x02001f04
 *
 * 解决方案：确保进程所在核的hunt表已初始化。
 */
#define OS_ERRNO_HUNT_NOT_INIT              SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x04)

/**
 * @ingroup sre_hunt
 * HUNT错误码：创建用户进程，进程名重名。
 *
 * 值: 0x02001f05
 *
 * 解决方案：创建用户进程时，确保进程名本核内唯一。
 */
#define OS_ERRNO_HUNT_PROCESS_NAME_REPEAT   SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x05)

/**
 * @ingroup sre_hunt
 * HUNT错误码：通过进程名获取进程PID时，该进程名没有找到。
 *
 * 值: 0x02001f06
 *
 * 解决方案：确保该进程的核已经运行起来而且该进程已注册创建且未被删除。
 */
#define OS_ERRNO_HUNT_PROCESS_NOT_FOUND     SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x06)

/**
 * @ingroup sre_hunt
 * HUNT错误码：hunt 模块名字申请失败。
 *
 * 值: 0x02001f07
 *
 * 解决方案：扩大共享名字空间大小。
 */
#define OS_ERRNO_HUNT_NAME_ALLOC_FAILED              SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x07)

/**
* @ingroup sre_hunt
* @brief 通过进程ID及线程名获取线程ID。
*
* @par 描述:
* 通过进程ID及线程名(软中断或任务)获取线程ID。
* @attention
* <ul>
* <li>本核调用#SRE_HuntMature后调用该接口，会检查目的核是否调用#SRE_HuntMature，如果调用了，则继续进行查询操作，否则一直等待。</li>
* <li>本核调用#SRE_HuntMature之前调用该接口，不关注目的核是否调用#SRE_HuntMature，直接进行查询操作。</li>
* </ul>
*
* @param uwProcessID  [IN] 类型为#UINT32，对于裸核来说为核号(SD6183为硬线程号)，对于多进程(KOS或者UOS进程)来说为查询线程所在的进程ID(COREID | INDEX): bit0~bit7: 进程索引Index; bit8~bit15:核号；其他位保留。
* @param pcThreadName [IN] 类型为#CHAR*，线程名长度范围[1,15]。
* @param puwTID [OUT] 类型为#UINT32*，线程TID。
*
* @retval #OS_ERRNO_HUNT_THREAD_NOT_CREAT 0x02001f02，该线程未创建或已删除。
* @retval #OS_ERRNO_HUNT_ILLEGAL_INPUT    0x02001f03，入参非法。
* @retval #OS_ERRNO_HUNT_NOT_INIT         0x02001f04，hunt还表没有初始化。
* @retval #SRE_OK                         0x00000000，获取PID成功。
* @par 依赖:
* <ul><li>sre_hunt.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R003C00
* @see SRE_HuntPidByName
*/
extern UINT32 SRE_HuntByName(UINT32 uwProcessID, CHAR *pcThreadName, UINT32 *puwTID);


#if ((OS_OPTION_KERNEL_PROCESS == YES)||(OS_OPTION_USR_PROCESS == YES))
/**
* @ingroup sre_hunt
* @brief 通过进程名获取进程PID。
*
* @par 描述:
* 通过进程名获取进程PID。
* @attention
* <ul>
* <li>本核调用#SRE_HuntMature后调用该接口，会检查目的核是否调用#SRE_HuntMature，如果调用了，则继续进行查询操作，否则一直等待。</li>
* <li>本核调用#SRE_HuntMature之前调用该接口，不关注目的核是否调用#SRE_HuntMature，直接进行查询操作。</li>
* <li>调用该接口需要保证查询的进程已经创建。</li>
* </ul>
*
* @param ucCoreID  [IN] 类型为#UINT8，线程所在核号[0,OS_MAX_CORE_NUM-1]。
* @param pcProcessName [IN] 类型为#CHAR*，进程名长度范围[1,15]。
* @param puwPID [OUT] 类型为#UINT32*，进程ID。
*
* @retval #OS_ERRNO_HUNT_ILLEGAL_INPUT     0x02001f03，入参非法。
* @retval #OS_ERRNO_HUNT_PROCESS_NOT_FOUND 0x02001f06，通过进程名获取进程PID时，该进程名没有找到。
* @retval #SRE_OK                          0x00000000，获取PID成功。
* @par 依赖:
* <ul><li>sre_hunt.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R003C00
* @see SRE_ProcessNameSet
*/
extern UINT32 SRE_HuntPidByName( CHAR *pcProcessName, UINT32 *puwProcessID);
#endif

/**
* @ingroup sre_hunt
* @brief 标记本核所有的任务和软中断已创建完成（OS的IDLE除外），其它核可以成功查询本核的PID。
*
* @par 描述:
* 置上本核mature标志。同时置标志：使得本核在调用#SRE_HuntByName时，如果目的核没有启动，则一直等待，直到目的核置上了mature标志才返回查询结果。
* @attention
* <ul>
* <li>必须在本核所有的任务和软中断（OS的IDLE除外）创建完成之后调用。</li>
* </ul>
*
* @param 无。
*
* @retval 无。
* @par 依赖:
* <ul><li>sre_hunt.h：该接口声明所在的头文件。</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HuntByName
*/
extern VOID SRE_HuntMature(VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_HUNT_H */

 

