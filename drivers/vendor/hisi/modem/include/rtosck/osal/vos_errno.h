/**
 * @file vos_errno.h
 *
 * Copyright(C), 2012-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：OSAL错误码头文件。 \n
 */

/**@defgroup vos_errno 错误码
 *@ingroup OSAL
*/

#ifndef _VOS_ERRNO_H
#define _VOS_ERRNO_H

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define VOS_OK                  (0)
#define VOS_ERROR               ((VOS_UINT32)(-1))

/**
 * @ingroup vos_errno
 * OSAL错误码：参数错误。
 *
 * 值: 0x00000016
 *
 * 解决方案: 用户检查入参，保证入参合法。
 */
#define VOS_ERRNO_INVAL                 0x00000016

/**
 * @ingroup vos_errno
 * OSAL错误码：内存不足。
 *
 * 值: 0x0000000C
 *
 * 解决方案: 释放其他未使用的内存空间或者分配更大的私有FSC内存分区。
 */
#define VOS_ERRNO_NOMEM                 0x0000000C

/**
 * @ingroup vos_errno
 * OSAL错误码：OSAL初始化失败。
 *
 * 值: 0x00000080
 *
 * 解决方案: 请检查任务、信号量、队列、定时器模块是否开启并完成初始化。
 */
#define VOS_ERRNO_OSAL_INIT_FAILED      0x00000080

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif /* _VOS_ERRNO_H */

