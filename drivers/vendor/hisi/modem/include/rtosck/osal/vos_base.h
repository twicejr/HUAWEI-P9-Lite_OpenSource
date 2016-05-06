/**
* @file vos_base.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：OSAL基础头文件。 \n
*/

#ifndef _VOS_BASE_H
#define _VOS_BASE_H

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
#include "vos_typedef.h"
#include "vos_redef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup vos_base
 * 等待资源模式：等待。
 */
#define VOS_WAIT                            ((VOS_UINT32)1 << 30)

/**
 * @ingroup vos_base
 * 等待资源模式：不等待。
 */
#define VOS_NO_WAIT                         ((VOS_UINT32)1 << 31)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
#endif //_VOS_BASE_H

