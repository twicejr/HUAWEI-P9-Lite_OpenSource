/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipbir_ipv6_environ.h
  Version       : Initial Draft
  Author        : Prabhu H 71185
  Project Code  : IPB IR V1R2
  Created       : 2007/3/16
  Last Modified :
  Description   : Contains common macros and definitions used by all modules of
                  IPv6 IR version (ADDR, ND, ICMP6, PMTU, TCP, UDP6, RAWIP6)
  Function List :
  History       :
  1.Date        : 2007/3/16
    Author      : Prabhu H 71185
    Modification: Created file for IPBIRV100R002.IP.E001

******************************************************************************/

#ifndef _IPB_IR_IPV6_ENVIRON_H
#define _IPB_IR_IPV6_ENVIRON_H

#ifdef _cplusplus
extern "C"{
#endif

/* IPBIR_IP6_INTER_MALLOC will be used if the memory is allocated and freed
 * inside any of IPv6 IR modules.  Similarly, IPBIR_IP6_INTER_FREE will be used,
 * only when the corresponding memory is allocated by any of IPv6 IR modules
 */
#if (IPBIR_IPV6_BASIC_MODULES_PURIFY_TEST == VRP_YES)
extern VOID* malloc(ULONG);
extern VOID free(VOID* ptr);
#define IPBIR_IP6_INTERNAL_MALLOC(ulInfo, ulSize) malloc(ulSize)
#define IPBIR_IP6_INTERNAL_FREE(ptr)  free(ptr)
#else
#define IPBIR_IP6_INTERNAL_MALLOC(ulInfo, ulSize) VOS_Malloc((ulInfo), (ulSize))
#define IPBIR_IP6_INTERNAL_FREE(ptr)\
{\
    if (NULL != (ptr))\
    {\
        (VOID)VOS_Free(ptr);\
        (ptr) = NULL;\
    }\
    else\
    {\
        VOS_DBGASSERT(0);\
    }\
}
#endif

/* IPBIR_IP6_EXTER_MALLOC will be used if the memory is allocated inside
 * IPv6 IR modules and freed in any external module
 */
#define IPBIR_IP6_EXTERNAL_MALLOC(ulInfo, ulSize) VOS_Malloc((ulInfo), (ulSize))


/* IPBIR_IP6_EXTER_FREE will be used, only when the corresponding memory
 * is allocated by any of external modules other than IPv6 IR modules
 */
#define IPBIR_IP6_EXTERNAL_FREE(ptr)  \
{ \
    if (NULL != (ptr)) \
    { \
        (VOID)VOS_Free(ptr); \
        (ptr) = NULL; \
    } \
    else \
    { \
        VOS_DBGASSERT(0); \
    } \
}

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* _IPB_IR_IPV6_ENVIRON_H */
