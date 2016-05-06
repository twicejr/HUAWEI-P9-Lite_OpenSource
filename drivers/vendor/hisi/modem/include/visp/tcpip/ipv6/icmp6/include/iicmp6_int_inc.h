/*******************************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-------------------------------------------------------------------------------
*                              iicmp6_int_inc.h
*
*    Project Code:  IPB IR V1R2
*    Module Name :  ADDR
*        Version :
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define and expose ICMP Component,interface used by shell
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik    Created for including all public definitions in
*                             this file, for IPB IR V1R2 - COMMOM re-arrange
************************************************************************/
#ifndef _IICMP6_INT_INC_H
#define _IICMP6_INT_INC_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "common/ipos/ipv6/basic/icmp6/iicmp6_inc.h"
#include "ipv6/icmp6/include/icmp6_int_pub.h"
#include "ipv6/ircommon/icmp6/iicmp6_ir_inc.h"
#include "ipv6/ipv6_ppi.h"

/* Component Information */
extern const struct ComponentInfo m_CompICMP6Info;

/*Begin: Changed for VISPV1R7 integration by wan, 2008-05-02*/
#define IID_IP6_ICMP6_INT_SSA          (IID_IPV6_BASE + 13)
#define IID_IP6_ICMP6_INT_TEST         (IID_IPV6_BASE + 14)
#define IID_IP6_ICMP6_INT_INIT          (IID_IPV6_BASE + 15)
/*End of change for VISPV1R7 integration, 2008-05-02*/

DECLARE_INTERFACE(IIF_IP6_ICMP6_INT_INIT)
{
    IUNKNOWN_METHODS
    METHOD_ (ULONG, pfIP6_ICMP6_Init_Com_New)(const IPB_IR_ICMP6_COM_ID_INFO_S
                                                    *pComInfo, ULONG ulComLen);
    METHOD_ (ULONG, pfIP6_ICMP6_Activate_Com) ();
    METHOD_ (ULONG, pfIP6_ICMP6_SetModuleInfo) (IP6_ICMP6_MOD_INFO_S *pMInfo);
    METHOD_ (ULONG, pfIP6_ICMP6_RegShellCallBackFunc)(
                                IP6_ICMP6_SH_CALLBACK_FUNC_S *pstICMP6Callback);
    METHOD_(ULONG, pfIP6_ICMP6_RegNPCallback)(IPV6_PPI_HOOK_S *pstCallbackFunc);
};

DECLARE_INTERFACE (IIF_IP6_ICMP6_INT_SSA)
{
    IUNKNOWN_METHODS
    METHOD_ (VOID, pfIP6_ICMP6_NotifyInput)(MBUF_S *pstMBuf);
    METHOD_ (ULONG, pfIP6_ICMP6_ErrorRateLimitTimeout)(VOID *pTemp);
    METHOD_ (ULONG, pfIP6_ICMP6_TooBigErrorRateLimitTimeout)(VOID *pTemp);
};

typedef struct tagICMP6_INT_OBJ_S
{
    IIF_IP6_ICMP6_INIT      *pICMP6INIT;
    IIF_IP6_ICMP6_CFG       *pICMP6CFG;
    IIF_IP6_ICMP6_FUN       *pICMP6FUN;
    IIF_IP6_ICMP6_INT_INIT  *pICMP6INTINIT;
    IIF_IP6_ICMP6_INT_SSA   *pICMP6INTSSA;
    IIF_IP6_ICMP6_IR_FUN    *pICMP6IRFUN;
}ICMP6_INT_OBJ_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /*_IICMP6_INT_INC_H */

