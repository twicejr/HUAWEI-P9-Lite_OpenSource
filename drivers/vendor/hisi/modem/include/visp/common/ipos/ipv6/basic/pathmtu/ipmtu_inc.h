/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipmtu_inc.h
*
*    Project Code:  IPOS IR V1R2
*    Module Name :  PMTU
*    Create Date :  2006/09/23
*    Author      :  Yinyuanbin
*    Description :  To define and expose PMTU Component and interface
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-10-01  yinyuanbin    Created for including all public definitions in
*                             this file, for IPOS IR V1R2
*  2008-05-02  Wanlu           Updated for VISPV1R7 integration
************************************************************************/

#ifndef _PMTU_INC_H
#define _PMTU_INC_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "common/ipos/ipv6/basic/pathmtu/pmtu_public.h"

/*Component ID declaration */
#define CID_IPV6_PMTU                       (CID_IPV6_BASE + 5)

/*Interface IDs declration */
#define IID_IPV6_PMTU_INTF_INIT     (IID_IPV6_BASE + 50)
#define IID_IPV6_PMTU_INTF_CFG      (IID_IPV6_BASE + 51)
#define IID_IPV6_PMTU_INTF_FUN      (IID_IPV6_BASE + 52)

/*Map new IIDs to old IIDs*/
#define IID_IP6_PMTU_INIT IID_IPV6_PMTU_INTF_INIT
#define IID_IP6_PMTU_CFG  IID_IPV6_PMTU_INTF_CFG
#define IID_IP6_PMTU_FUN  IID_IPV6_PMTU_INTF_FUN

/*init interface declartaion*/
DECLARE_INTERFACE(IIF_IP6_PMTU_ComIntINIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_PMTU_RegSocketCallBack)
                        (PMTU_CALLBACKUP_SET_S *pstCallBackSet);
};

/*Map new interface name to old interface name*/
#define IIF_IP6_PMTU_INIT     IIF_IP6_PMTU_ComIntINIT
#define IIF_IP6_PMTU_INITVtbl IIF_IP6_PMTU_ComIntINITVtbl

/*FUN interface declartaion*/
DECLARE_INTERFACE(IIF_IP6_PMTU_ComIntFun)
{
    IUNKNOWN_METHODS
    METHOD_(VOID, pfIP6_PMTU_NotifyMTU)(IN6ADDR_S *pstDA, ULONG ulZoneid,
        ULONG ulMtu);
    METHOD_(ULONG, pfIP6_PMTU_Notification_Register) (SOCKADDR_IN6_S *pstsAD,
        LONG ulSockid, ULONG ulTaskId, ULONG ulIfindex);
    METHOD_(ULONG, pfIP6_PMTU_Notification_Unregister)\
        (LONG ulSockid, ULONG ulTaskId);
};

/*Map new interface name to old interface name*/
#define IIF_IP6_PMTU_FUN     IIF_IP6_PMTU_ComIntFun
#define IIF_IP6_PMTU_FUNVtbl IIF_IP6_PMTU_ComIntFunVtbl

/*CFG interface declartaion*/
DECLARE_INTERFACE(IIF_IP6_PMTU_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_PMTU_SetResSpecs)(SPECS_RES_VALUE_S  *pstResSpecs);
    METHOD_(ULONG, pfIP6_PMTU_GetResSpecs)(SPECS_RES_VALUE_S  *pstResSpecs);

    METHOD_(ULONG, pfIP6_PMTU_SetDefAgetime)(USHORT usAgetime);
    METHOD_(ULONG, pfIP6_PMTU_SetPmtu)(IN6ADDR_S *pstDA,
        ULONG ulZoneid, ULONG ulPmtu);
    METHOD_(ULONG, pfIP6_PMTU_DeleteMatchingEntry)(IN6ADDR_S stDA,
        ULONG ulZoneid, ULONG ulFlag);
    METHOD_(ULONG, pfIP6_PMTU_DeleteAllEntries)(VOID);
    METHOD_(ULONG, pfIP6_PMTU_OpenTable)(UINTPTR *pulUserHandle);
    METHOD_(ULONG, pfIP6_PMTU_GetFirst)(UINTPTR ulHandle,
        PMTU_CLI_DISPLAY_S *pstCLIDisplay, ULONG *pulMultiIndex);
    METHOD_(ULONG, pfIP6_PMTU_GetNext)(ULONG *pulMultiIndex,
        PMTU_CLI_DISPLAY_S *pstCLIDisplay, UINTPTR ulWaitListHandle);
    METHOD_(ULONG, pfIP6_PMTU_SearchObj)(IN6ADDR_S *pstDA, ULONG ulZoneid,
        PMTU_CLI_DISPLAY_S *pstCLIDisplay);
    METHOD_(ULONG, pfIP6_PMTU_CloseTable)(UINTPTR *pulUserHandle);
    METHOD_(ULONG, pfIP6_PMTU_ModifyGlobalAgeTime)(USHORT usAgetime);
    METHOD_(ULONG, pfIP6_PMTU_ClearPMTUEntries)(ULONG ulType);
    METHOD_(ULONG, pfIP6_PMTU_GetPathMTU)(IN6ADDR_S *pstDA, ULONG ulZoneid,
        ULONG *pulPmtu);
    METHOD_(ULONG, pfIP6_PMTU_SetMaxMtu)(ULONG ulMaxMtu);
    METHOD_(ULONG, pfIP6_PMTU_GetDefAgetime)(USHORT *pusAge);
    METHOD_(ULONG, pfIP6_PMTU_GetTotalEntries)
        (ULONG ulFlag, ULONG * pulTotalEntries);
};

/*Map new interface name to old interface name*/
#define IIF_IP6_PMTU_CFG     IIF_IP6_PMTU_ComIntCFG
#define IIF_IP6_PMTU_CFGVtbl IIF_IP6_PMTU_ComIntCFGVtbl

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _PMTU_INC_H */
