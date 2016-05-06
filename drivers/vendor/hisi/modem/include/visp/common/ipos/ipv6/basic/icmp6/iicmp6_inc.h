/*-----------------------------------------------------------------------
*                              iicmp6_inc.h
*
*    Project Code:  IPOS IR V1R2
*    Module Name :  ICMP6
*    Create Date :  2006/09/23
*    Author      :  Yinyuanbin
*    Description :  To define and expose ICMP6 Component and interface
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-10-01  yinyuanbin    Created for including all public definitions in
*                             this file, for IPOS IR V1R2
*  2008-05-02  Wanlu           Updated for VISPV1R7 integration
************************************************************************/

#ifndef _ICMP6_INC_H
#define _ICMP6_INC_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"

/* Component ID declaration for ICMP6 */
#define CID_IPV6_ICMP6                         (CID_IPV6_BASE + 1)

/* Interface IDs declaration */
#define IID_IPV6_ICMP6_INTF_CFG       (IID_IPV6_BASE + 10)
#define IID_IPV6_ICMP6_INTF_FUN       (IID_IPV6_BASE + 11)
#define IID_IPV6_ICMP6_INTF_INIT       (IID_IPV6_BASE + 12)

/*Map to old IIDs*/
#define  IID_IP6_ICMP6_CFG  IID_IPV6_ICMP6_INTF_CFG
#define  IID_IP6_ICMP6_FUN  IID_IPV6_ICMP6_INTF_FUN
#define  IID_IP6_ICMP6_INIT IID_IPV6_ICMP6_INTF_INIT

DECLARE_INTERFACE(IIF_IP6_ICMP6_ComIntINIT)
{
    IUNKNOWN_METHODS
    METHOD_ (ULONG, pfIP6_ICMP6_SOSB6_Socket_RegisterCallBack)
        (SOSB6_CALLBACUP_SET_S *pstSOSB6CallBack);
    METHOD_ (ULONG, pfIP6_ICMP6_IN6PCB_Socket_RegisterCallBack)
        (IN6PCB_CALLBACUP_SET_S *pstIN6PCBCallBack);
    METHOD_ (ULONG, pfIP6_ICMP6_Reg_Flow_Callback)
        (ICMP6_EXT_CALLBACK_S *pstCallBack);
};

#define IIF_IP6_ICMP6_INIT     IIF_IP6_ICMP6_ComIntINIT
#define IIF_IP6_ICMP6_INITVtbl IIF_IP6_ICMP6_ComIntINITVtbl

DECLARE_INTERFACE (IIF_IP6_ICMP6_ComIntFun)
{
    IUNKNOWN_METHODS
    METHOD_ (VOID, pfIP6_ICMP6_Error) (MBUF_S *pstMBuf, UCHAR ucType,
        UCHAR ucCode, LONG lParam);
    METHOD_ (ULONG, pfIP6_ICMP6_Input) (MBUF_S **ppstMBuf, ULONG *pulOff,
        ULONG ulProto);
    METHOD_ (LONG, pfIP6_ICMP6_CtlOutput) (LONG lOper, UINTPTR ulSockId,
        LONG lLevel, LONG lOptName, MBUF_S **ppMPtr);
    METHOD_ (VOID, pfIP6_ICMP6_RedirectOutput) (MBUF_S *pstMBuf,
        const ICMP6_ROUTE_S * pstRt);
    METHOD_ (IN6ADDR_S *, pfIP6_ICMP6_SelectSrcAddr) (const IN6ADDR_S
        *pstDstAddr, IN6ADDR_S *pstSrcAddr, USHORT usVrfIndex);
};


#define  IIF_IP6_ICMP6_FUN     IIF_IP6_ICMP6_ComIntFun
#define  IIF_IP6_ICMP6_FUNVtbl IIF_IP6_ICMP6_ComIntFunVtbl

DECLARE_INTERFACE (IIF_IP6_ICMP6_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_ (ULONG, pfIP6_ICMP6_ErrorRateLimitUpdate)
        (const ICMP6_ERRRATE_MSG_S *pstBuf);
    METHOD_ (ULONG, pfIP6_ICMP6_ErrorRateLimitGetValue) (ULONG *pulInterval,
        ULONG *pulTockens);
    METHOD_ (ULONG, pfIP6_ICMP6_SetTooBigErrorRateLimit) (ULONG ulRateStatus);
    METHOD_ (ULONG, pfIP6_ICMP6_GetAllStatistics) (ICMP6STAT_S *pstIcmp6Stat);
    METHOD_ (ULONG, pfIP6_ICMP6_ResetAllStatistics) (VOID);
    METHOD_ (ULONG, pfIP6_ICMP6_IncrementStatistics) (ULONG ulIfIndex,
        ICMP6STATFIELD efield, UCHAR ucType);
    METHOD_ (ULONG, pfIP6_ICMP6_ResetStatisticsByType)(ICMP6STATFIELD efield,
        UCHAR ucType);
    METHOD_ (ULONG, pfIP6_ICMP6_GetStatisticsByType)(ICMP6STATFIELD efield,
        UCHAR ucType, ULONG *ulVal);
    METHOD_(ULONG, pfIP6_ICMP6_GetIntfStatistics)
                                (ULONG ulIfIndex, ICMP6STAT_S *psticmp6stat);
    METHOD_(ULONG, pfIP6_ICMP6_ResetIntfStatistics)(ULONG ulIfIndex);
    
    /* Start: RFC4443 compliance changes */
    METHOD_(ULONG, pfIP6_ICMP6_EnableDisableIntfDestUnReachError)(ULONG ulIfindex, 
                                                             ULONG ulOperation);
    /* End: RFC4443 compliance changes */
};

#define  IIF_IP6_ICMP6_CFG     IIF_IP6_ICMP6_ComIntCFG
#define  IIF_IP6_ICMP6_CFGVtbl IIF_IP6_ICMP6_ComIntCFGVtbl

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /*_ICMP6_INC_H */

