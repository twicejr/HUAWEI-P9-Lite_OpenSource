/**
 * @file vos_safedef.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：VISP安全函数转定义 \n
 */

/**@defgroup vos_safedef VISP安全函数转定义
 *@ingroup OSAL
*/

#ifndef __VOS_SAFEDEF_H__
#define __VOS_SAFEDEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define TCPIP_Mem_Copy(pDstPtr, dst_size, pSrcPtr, copy_size)   TCPIP_Safe_Mem_Copy(pDstPtr, dst_size, pSrcPtr, copy_size)
#define TCPIP_strncpy(pDstPtr, dst_size, pSrcPtr, copy_size)    TCPIP_Safe_Strncpy(pDstPtr, dst_size, pSrcPtr, copy_size)
#define TCPIP_StrNCat(pDstPtr, dst_size, pSrcPtr, copy_size)    TCPIP_Safe_StrNCat(pDstPtr, dst_size, pSrcPtr, copy_size)
#define TCPIP_Mem_Move(pDest, dest_max, pSrc, count)            TCPIP_Safe_Mem_Move(pDest, dest_max, pSrc, count)
#define TCPIP_Mem_Set(pDstPtr, uChar, ulSetLen)                 TCPIP_Safe_Mem_Set(pDstPtr, ulSetLen, uChar, ulSetLen)

#if (TCPIP_VOS_FUNC_TYPE == VOS_FUNC_TYPE_SAFE)
#define TCPIP_SNPRINTF0(STR, LEN, PAPAM)                        VOS_snprintf_s(STR, LEN, LEN-1, PAPAM)
#define TCPIP_SNPRINTF(STR, LEN, PAPAM)                         (((LEN) > 0) ? VOS_snprintf_s(STR, LEN, LEN-1, PAPAM) : 0)
#define TCPIP_Vsprintf                                          VOS_vsprintf_s
#define TCPIP_Sscanf                                            VOS_sscanf_s
#define TCPIP_Scanf                                             VOS_scanf_s
#else
/*Added by yanlei00216869, 支持控制器安全函数适配, 2015/1/6   问题单号:DTS2015010508058 */
#if (TCPIP_VOS_FUNC_TYPE == VOS_FUNC_TYPE_SAFE_MBSC)
#define TCPIP_SNPRINTF0(STR, LEN, PAPAM)                        VOS_snprintf_S(STR, LEN, LEN-1, PAPAM)
#define TCPIP_SNPRINTF(STR, LEN, PAPAM)                         (((LEN) > 0) ? VOS_snprintf_S(STR, LEN, LEN-1, PAPAM) : 0)
#define TCPIP_Vsprintf                                          vsprintf_s
#define TCPIP_Sscanf                                            VOS_sscanf_S
#define TCPIP_Scanf                                             scanf_s
#else
#define TCPIP_SNPRINTF0(STR, LEN, PAPAM)                        VOS_nsprintf(STR,LEN,PAPAM)
#define TCPIP_SNPRINTF(STR, LEN, PAPAM)                         (((LEN) > 0) ? VOS_nsprintf(STR, LEN, PAPAM) : 0)
#define TCPIP_Vsprintf                                          VOS_nvsprintf
#define TCPIP_Sscanf                                            VOS_sscanf
#define TCPIP_Scanf                                             scanf
#endif
/* End of Added by yanlei00216869, 2015/1/6   问题单号:DTS2015010508058 */
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif //__VOS_SAFEDEF_H__


