/**
* @file sre_mchwi.h
*
* Copyright(C), 2008-2008, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：多核硬中断对外头文件。 \n
*/

/** @defgroup SRE_mchwi 核间硬中断
   *@ingroup SRE_interrupt
*/

#ifndef _SRE_MCHWI_H
#define _SRE_MCHWI_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_mchwi
 * 核间中断错误码：核间中断触发的目的核号无效
 *
 * 值: 0x02001480
 *
 * 解决方案：目的核号非本核，且在有效范围内
 */
#define OS_ERRNO_MCHWI_DST_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x80)

/**
 * @ingroup SRE_mchwi
 * 核间中断错误码：6181和6108平台下，发送核间中断时，共享队列已满。
 *
 * 值: 0x02001486
 *
 * 解决方案: 等到邮箱队列中可存储核间中断时再发送。
 *
 */
#define OS_ERRNO_IPC_SHQ_FULL                              SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x86)

/**
 * @ingroup SRE_mchwi
 * 核间中断错误码：6181和6108平台下，初始化阶段，申请不到足够的消息缓冲队列空间。
 *
 * 值: 0x02001487
 *
 * 解决方案: 为共享静态分区配置更大内存空间。
 *
 */
#define OS_ERRNO_MCDDR_NO_MEMORY                              SRE_ERRNO_OS_ERROR(OS_MID_HWI, 0x87)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

