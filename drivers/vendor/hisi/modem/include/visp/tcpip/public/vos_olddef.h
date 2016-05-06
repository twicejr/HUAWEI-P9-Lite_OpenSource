/**
 * @file vos_olddef.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：VISP原始安全函数转定义 \n
 */

/**@defgroup vos_safedef VISP原始的安全函数转定义
 *@ingroup OSAL
*/

#ifndef __VOS_OLDDEF_H__
#define __VOS_OLDDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define TCPIP_Mem_Copy(pDstPtr, dst_size, pSrcPtr, copy_size)   VOS_Mem_Copy(pDstPtr, pSrcPtr, copy_size)
#define TCPIP_Mem_Set(pDstPtr, uChar, ulSetLen )                VOS_Mem_Set(pDstPtr, uChar, ulSetLen )
#define TCPIP_strncpy(pDstPtr, dst_size, pSrcPtr, copy_size)    VOS_strncpy(pDstPtr, pSrcPtr, copy_size)
#define TCPIP_StrNCat(pDstPtr, dst_size, pSrcPtr, copy_size)    VOS_StrNCat(pDstPtr, pSrcPtr, copy_size)
#define TCPIP_nsprintf   VOS_nsprintf
#define TCPIP_nvsprintf  VOS_nvsprintf

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif //__VOS_OLDDEF_H__



