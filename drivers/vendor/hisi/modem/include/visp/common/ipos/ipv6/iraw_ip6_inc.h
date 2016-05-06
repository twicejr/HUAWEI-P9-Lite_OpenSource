/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              iraw_ip6_inc.h
*
*    Project Code: VRP5.0
*    Module Name : IP6 RawIp6
*    Create Date : 2003/06/23
*    Author      : Sunil Dutt
*    Description : To define RawIp6 component interfaces
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2003-06-23  Sunil Dutt       Create
*  2006-04-11  Arun V           Updated for rearranging of public definitions  for or IPOSV1R1
*  2008-05-02  Wanlu           Updated for VISPV1R7 integration
*************************************************************************/

#ifndef _IRAWIP6_INC_H
#define _IRAWIP6_INC_H

#ifdef  __cplusplus
extern "C"{
#endif 

#include "raw_ip6_public.h"

/* Component ID declaration */
#define CID_IPV6_RIP6                     (CID_IPV6_BASE + 4)

/* Interface IDs declaration */
#define IID_IPV6_RIP6_INTF_CFG    (IID_IPV6_BASE + 40)
#define IID_IPV6_RIP6_INTF_FUN    (IID_IPV6_BASE + 41)

/*Mapping to old IDs*/
#define IID_IP6_RIP6_CFG IID_IPV6_RIP6_INTF_CFG
#define IID_IP6_RIP6_FUN IID_IPV6_RIP6_INTF_FUN


/* the configuration interfaces provided by the component. */
DECLARE_INTERFACE (IIF_IP6_RIP6_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_RIP6_ResetStatistics) (VOID);
    METHOD_(ULONG, pfIP6_RIP6_GetStatistics) (RIP6STAT_S *pstRip6Stats);
};

#define IIF_IP6_RIP6_CFG     IIF_IP6_RIP6_ComIntCFG
#define IIF_IP6_RIP6_CFGVtbl IIF_IP6_RIP6_ComIntCFGVtbl

/* the functional interfaces provided by the component. */
DECLARE_INTERFACE (IIF_IP6_RIP6_ComIntFun)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIP6_RIP6_Input) (MBUF_S **ppstMBuf, ULONG *pulOff,
        ULONG ulProto);
    METHOD_(VOID, pfIP6_RIP6_Reg_SockAPI)
        (SOSB6_CALLBACUP_SET_S *pfSocketTL6CallBack);
    METHOD_(VOID, pfIP6_RIP6_Reg_IN6PCBAPI)
        (IN6PCB_CALLBACUP_SET_S *pfIn6PCBTL6CallBack);

    METHOD_(LONG, pfIP6_RIP6_Output)(MBUF_S *pstMBuf,
        UINTPTR  ulSock, SOCKADDR_IN6_S *pstDstAddr,MBUF_S *pstMCtl);

    METHOD_(LONG, pfIP6_RIP6_CtlOutput)(LONG lOper, UINTPTR ulSock,LONG lLevel,
        LONG lOptName, MBUF_S **ppMBuf);

    METHOD_(LONG, pfIP6_RIP6_Usrreq)(UINTPTR ulSock, LONG lReq,VOID *pstMBuf,
        VOID *pstMName, VOID *pstMCtl);

};

#define IIF_IP6_RIP6_FUN     IIF_IP6_RIP6_ComIntFun
#define IIF_IP6_RIP6_FUNVtbl IIF_IP6_RIP6_ComIntFunVtbl


#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */
#endif /* End of _IRAWIP6_INC_H */

