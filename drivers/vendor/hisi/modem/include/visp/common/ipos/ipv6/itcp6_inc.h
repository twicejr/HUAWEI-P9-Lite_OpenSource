/*******************************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-------------------------------------------------------------------------------
*                              itcp6_inc.h
*
*    Project Code:  VRP5.0
*    Module Name: IP6 TCP6
*    Create Date:   2003/06/23
*    Author:           Naina Gupta
*    Description:    To define TCP6 component interfaces
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-06-30    Naina Gupta    Create
*  2006-06-06    Alok           Updated for 14 Fly-Check rules adherence
*                               for IPOSIR-V1R1-IPv6
*  2007-12-10    Sandeep71635   Updated Vtable rearrangement as part of V1R3
*  2008-05-02  Wanlu           Updated for VISPV1R7 integration
*******************************************************************************/

#ifndef _ITCP6_INC_H
#define _ITCP6_INC_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcp6_public.h"

/* Component ID declaration */
#define CID_IPV6_TCP6                      (CID_IPV6_BASE + 2)

/* Interface IDs declaration */
#define IID_IPV6_TCP6_INTF_CFG    (IID_IPV6_BASE + 20)
#define IID_IPV6_TCP6_INTF_FUN    (IID_IPV6_BASE + 21)

/*Map the old IIDs*/
#define IID_IP6_TCP6_CFG IID_IPV6_TCP6_INTF_CFG
#define IID_IP6_TCP6_FUN IID_IPV6_TCP6_INTF_FUN


DECLARE_INTERFACE (IIF_IP6_TCP6_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(TCP6MIBCONN_S *, pfTCP6_ConnTableGetFirst)(VOID);
    METHOD_(VOID, pfTCP6_GetStatistics)(TCP6STAT_S *pstTCP6Stat);
    METHOD_(TCP6MIBCONN_S *, pfTCP6_ConnTableGetNext)(IN6ADDR_S stLAddr,
        ULONG ulLPort, IN6ADDR_S stFAddr, ULONG ulFPort, ULONG ulIfIndx);
    METHOD_(TCP6MIBCONN_S *, pfTCP6_ConnTableMatch)(IN6ADDR_S stLAddr,
        ULONG ulLPort, IN6ADDR_S stFAddr, ULONG ulFPort, ULONG ulIfIndx);
    METHOD_(VOID, pfTCP6_SetFilterZero) (VOID);
    METHOD_(LONG, pfTCP6_SetDebugAll)(VOID);
    METHOD_(VOID, pfTCP6_ClearDebugFlag)(VOID);
    METHOD_(USHORT, pfTCP6_TCP6CBFound)(TCP6CB_S * pstTCP6CB);
    METHOD_(ULONG, pfTCP6_Set_Syn_TimeOut)(ULONG ulTCP6KeepIntvl,ULONG ulFlag);
    METHOD_(ULONG, pfTCP6_Set_Fin_TimeOut)(ULONG ulTCP6KeepIntvl,ULONG ulFlag);
    METHOD_(ULONG, pfTCP6_Set_Window)(ULONG ulValue,ULONG ulFlag);
    METHOD_(ULONG, pfTCP6_Get_TCPCBParam)(IN6ADDR_S stLAddr,
        ULONG ulLPort, IN6ADDR_S stFAddr, ULONG ulFPort, ULONG ulUserVrfIndex,
        TCP6CBPARAM_S *pstMatchNode);
    METHOD_(ULONG, pfTCP6_ResetConnectionStats) (TCP6CONNINFO_S *pstTCP6ConnInfo);
    METHOD_(ULONG, pfTCP6_GetConnectionStats) (TCP6CONNINFO_S *pstTCP6ConnInfo,
                                                      TCP6PERCONNSTAT_S *pstPerTCP6Stat);
};

#define IIF_IP6_TCP6_CFG     IIF_IP6_TCP6_ComIntCFG
#define IIF_IP6_TCP6_CFGVtbl IIF_IP6_TCP6_ComIntCFGVtbl



DECLARE_INTERFACE (IIF_IP6_TCP6_ComIntFun)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfTCP6_Get_Param)(ULONG ulType, ULONG * pulValue);
    METHOD_(VOID, pfTCP6_SetStatisticsZero) (VOID);
    METHOD_(VOID, pfTCP6_GetIn6PCBFromConnections)(UINTPTR *pulIn6PCB);
    METHOD_(ULONG, pfTCP6_OpenObject_TCP6Conn) (ULONG ulMainType,
        UINTPTR *pulHandle);
    METHOD_(ULONG, pfTCP6_CloseObject_TCP6Conn) (UINTPTR  ulHandle);
    METHOD_(ULONG, pfTCP6_Get_Object_NextTCP6Conn)(UINTPTR ulHandle,
        TCP6CONNPARAM_S *pstIn6PCB);
    METHOD_(VOID, pfIP6_TCP6_SOSB6_Socket_RegisterCallBack)
        (SOSB6_CALLBACUP_SET_S * pfSocketTL6CallBack);
    METHOD_(VOID, pfIP6_TCP6_IN6PCB_Socket_RegisterCallBack)
        (IN6PCB_CALLBACUP_SET_S * pfIn6PCBTL6CallBack);
    METHOD_(VOID, pfTCP6_PMTU_Notify)
        (UINTPTR ulTCP6CB, ULONG ulMtuVal, UCHAR ucEvokingFlag);
    METHOD_(ULONG, pfIP6_TCP6_GetDebugFilter) (ULONG *pulDebugFlag,
        TCP6DBUGFILTRD_S *pstSockDbgPktFilter,
        TCP6DBUGFILTRD_S *pstSockDbgTraFilter);
    METHOD_(ULONG, pfTCP6_ProDbugFilter)(ULONG ulFlag,
        ULONG ulDbgFilterId, ULONG ulTaskId, ULONG ulSockId);
    METHOD_(VOID, pfTCP6_Get_ulCurrEstablished) (ULONG *pulCurrentEstablished);
    METHOD_(ULONG,pfTCP6_GetTCP6Now)(VOID);
    METHOD_(VOID, pfTCP6_SetTCP6Now)(ULONG ulNow);
    METHOD_(ULONG, pfTCP6_GetMatchTCP6CB) (IN6ADDR_S stLAddr, ULONG ulLPort,
    IN6ADDR_S stFAddr, ULONG ulFPort, TCP6CB_S *pstTCP6CB,
        TCP6CONNPARAM_S *pstTcp6CBConn);
    METHOD_(ULONG, pfTCP6_ClearTcbCache) (VOID);
};

#define IIF_IP6_TCP6_FUN     IIF_IP6_TCP6_ComIntFun
#define IIF_IP6_TCP6_FUNVtbl IIF_IP6_TCP6_ComIntFunVtbl


#ifdef  __cplusplus
}
#endif

#endif  /* _ITCP6_INC_H */
