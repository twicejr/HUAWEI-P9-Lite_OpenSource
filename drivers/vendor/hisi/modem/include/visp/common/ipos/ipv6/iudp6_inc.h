/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              iudp6_inc.h
*
*    Project Code:  VRP5.0
*    Module Name: IP6 TCP6
*    Create Date:   2003/06/23
*    Author:           Sunil Dutt
*    Description:    To define UDP6 component interfaces
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2003-06-30    Sunil Dutt    Create
*  2006-04-11    Aparna        Updated for rearraning of public definitions for
*                              IPOSV1R1
*  2006-08-29    Prabhu H      Updated for RFC 4113 MIB implmentation
*  2008-05-02  Wanlu           Updated for VISPV1R7 integration
************************************************************************/

#ifndef _IUDP6_INC_H
#define _IUDP6_INC_H

#ifdef  __cplusplus
extern "C"{
#endif 

#include "udp6_public.h"

/* Component ID declaration */
#define CID_IPV6_UDP6                        (CID_IPV6_BASE + 3)

/* Interface IDs declaration */
#define IID_IPV6_UDP6_INTF_CFG     (IID_IPV6_BASE + 30)
#define IID_IPV6_UDP6_INTF_FUN     (IID_IPV6_BASE + 31)

/*Map old IIDs*/
#define IID_IP6_UDP6_CFG IID_IPV6_UDP6_INTF_CFG
#define IID_IP6_UDP6_FUN IID_IPV6_UDP6_INTF_FUN

DECLARE_INTERFACE (IIF_IP6_UDP6_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(IP6_UDP6_MIB_CONN_S *, pfIP6_UDP6_ConnTableGetFirst)();
    METHOD_(IP6_UDP6_MIB_CONN_S *, pfIP6_UDP6_ConnTableGetNext)(
        IN6ADDR_S  stLAddr, ULONG ulLPort, ULONG ulIfIndx);
    METHOD_(IP6_UDP6_MIB_CONN_S  *, pfIP6_UDP6_ConnTableMatch)
        (IN6ADDR_S  *pstLAddr, ULONG ulLPort, ULONG ulIfIndx);
    METHOD_(VOID, pfIP6_UDP6_ClearStatist)(VOID);
    METHOD_(VOID, pfIP6_UDP6_DisplayStatist)(ULONG ulLanMode, CHAR *szOut);
    METHOD_(VOID,  pfIP6_UDP6_SetFilterZero)();
    METHOD_(ULONG,  pfIP6_UDP6_ProDbugFilter)(ULONG ulFlag, ULONG ulTaskId,
        ULONG ulSockId);
    METHOD_(ULONG,  pfIP6_UDP6_GetStats)(UDP6STAT_S *pstUDP6Stats);
    METHOD_(ULONG,  pfIP6_UDP6_GetDebugFilter)(
        UDP6_SOCKDBUGFILTRD_S *pstSockDbgFilter);
    METHOD_(UDP6_MIB_RETURN_S *, pfIP6_UDP6_EndpointTableGetOp)
        (IN6ADDR_S  stLAddr, ULONG ulLPort, IN6ADDR_S stRAddr, ULONG ulRPort,
        ULONG ulInstance);
    METHOD_(UDP6_MIB_RETURN_S *, pfIP6_UDP6_EndpointTableGetFirstOp)(VOID);
    METHOD_(UDP6_MIB_RETURN_S *, pfIP6_UDP6_EndpointTableGetNextOp)
        (IN6ADDR_S  stLAddr, ULONG ulLPort, IN6ADDR_S stRAddr, ULONG ulRPort,
        ULONG ulInstance);
    METHOD_(ULONG, pfUDP6_EndpointTableShellInterface) (VOID* pMsgRcv,
        VOID** ppMsgSnd);
    METHOD_(UDP6_MibScalarStc *, pfUDP6_GetMibScalars)(VOID);
};

#define IIF_IP6_UDP6_CFG     IIF_IP6_UDP6_ComIntCFG
#define IIF_IP6_UDP6_CFGVtbl IIF_IP6_UDP6_ComIntCFGVtbl

DECLARE_INTERFACE (IIF_IP6_UDP6_ComIntFun)
{
    IUNKNOWN_METHODS

    METHOD_(VOID, pfIP6_UDP6_Reg_SockAPI) (SOSB6_CALLBACUP_SET_S *
        pfSocketTL6CallBack);
    METHOD_(VOID, pfIP6_UDP6_Reg_IN6PCBAPI) (IN6PCB_CALLBACUP_SET_S *
        pfIn6PCBTL6CallBack);

};

#define IIF_IP6_UDP6_FUN     IIF_IP6_UDP6_ComIntFun
#define IIF_IP6_UDP6_FUNVtbl IIF_IP6_UDP6_ComIntFunVtbl

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* #ifndef _IUDP6_INC_H */
