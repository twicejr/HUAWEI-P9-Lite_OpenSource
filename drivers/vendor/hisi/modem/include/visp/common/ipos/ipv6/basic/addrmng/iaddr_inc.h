/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

*******************************************************************************
*                              iaddr_inc.h
*
*    Module Name :  ADDR
*    Version     :  IPBIRV100R003.IPv6.E001
*    Create Date :  2006/09/23
*    Author      :  Yinyuanbin
*    Description :  To define and expose ADDR Component and interface
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-10-01  yinyuanbin    Created for including all public definitions in
*                             this file, for IPB IR V1R2
*  2008-05-02  Wanlu           Updated for VISPV1R7 integration
******************************************************************************/

#ifndef _ADDR_INC_H
#define _ADDR_INC_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "addr_public.h"

/* Component ID declaration */
#define CID_IPV6_ADDRMNG                         (CID_IPV6_BASE + 8)

/* Interface IDs declaration for ADDR Router Interfaces */
#define IID_IPV6_ADDRMNG_INTF_INIT      (IID_IPV6_BASE + 80)
#define IID_IPV6_ADDRMNG_INTF_CFG       (IID_IPV6_BASE + 81)
#define IID_IPV6_ADDRMNG_INTF_FUN       (IID_IPV6_BASE + 82)

#define IID_IP6_ADDR_INIT IID_IPV6_ADDRMNG_INTF_INIT
#define IID_IP6_ADDR_CFG  IID_IPV6_ADDRMNG_INTF_CFG
#define IID_IP6_ADDR_FUN  IID_IPV6_ADDRMNG_INTF_FUN

/* Interface IDs declaration for ADDR ND HOST Interfaces */
#define IID_IP6_ADDR_HOST_INIT               (IID_IPV6_BASE + 83)
#define IID_IP6_ADDR_HOST_CFG                (IID_IPV6_BASE + 84)
#define IID_IP6_ADDR_HOST_FUN                (IID_IPV6_BASE + 85)

/*******************************************************************************
                                ADDR Router LEVEL 1 V-tables
*******************************************************************************/

/* Level 1 Init Interface */
DECLARE_INTERFACE(IIF_IP6_ADDR_ComIntINIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_SGSN_RegCallbackFunc)
                        (IP6_ADDR_SGSN_CALLBACK_FUNC_S  *pstCallbackFunc);
    METHOD_(ULONG, pfIP6_Addr_Srm_RegCallbackFunc)
                        (IP6_ADDR_SRM_CALLBACK_FUNC_S *pstCallbackFunc);
    METHOD_(ULONG, pfIP6_Addr_Reg_Platform_Hook)
                        (IP6_ADDR_DADRESULT_NOTIFY_FUNC_S *pstCallbackFunc);
};

/*Map to new interface names*/
#define IIF_IP6_ADDR_INIT     IIF_IP6_ADDR_ComIntINIT
#define IIF_IP6_ADDR_INITVtbl IIF_IP6_ADDR_ComIntINITVtbl

/* Level 1 CFG Interface */
DECLARE_INTERFACE(IIF_IP6_ADDR_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_Add_GlobalUniAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S  stIn6Addr, ULONG ulPrefixLen);
    METHOD_(ULONG, pfIP6_Addr_Add_LinkLocalAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S  stIn6Addr);
    METHOD_(ULONG, pfIP6_Addr_Add_EuiAddr)(ULONG ulIfIndex,
        IN6ADDR_S stIn6Addr, ULONG ulPrefixLen);
    METHOD_(ULONG, pfIP6_Addr_Del_GlobalUniAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S stIn6Addr, ULONG ulPrefixLen);
    METHOD_(ULONG, pfIP6_Addr_Del_LinkLocalAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S  stIn6Addr);
    METHOD_(ULONG, pfIP6_Addr_Del_EuiAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S  stIn6Addr, ULONG ulPrefixLen);
    METHOD_(ULONG, pfIP6_Addr_Del_AllAddr)(ULONG ulIfNetIndex);
    METHOD_(ULONG, pfIP6_Addr_AutoCfg)(ULONG ulIfNetIndex);
    METHOD_(ULONG, pfIP6_Addr_UndoAutoCfg)(ULONG ulIfNetIndex);
    METHOD_(ULONG, pfIP6_Addr_SetMTU)(ULONG ulIfnetIndex,
        ULONG ulIsNoCmd, ULONG ulMtu);
    METHOD_(ULONG, pfIP6_Addr_GetMTU)(ULONG ulIfnetIndex,
        ULONG ulIsCmd, ULONG *pulMtu);
    METHOD_(ULONG, pfIP6_Addr_OpenTable)(ULONG ulMainType,
        UINTPTR *pulWaitListHandle, UCHAR ucWaitlistType);
    METHOD_(ULONG, pfIP6_Addr_CloseTable)(UINTPTR ulWaitListHandle);
    METHOD_(ULONG, pfIP6_Addr_GetFirstExt)(UINTPTR ulWaitListHandle,
        VOID *pstAddrNode, VOID **ppstCurrentNode);
    METHOD_(ULONG, pfIP6_Addr_GetNextExt)(UINTPTR ulWaitListHandle,
        ULONG ulMainType, VOID ** ppCurrentObject);
    METHOD_(ULONG, pfIP6_Addr_GetFirstAddrTbl)(IP6_ADDR_ADDRTBL_S
        *pstInOutMIBAddrTbl);
    METHOD_(ULONG, pfIP6_Addr_GetAddrTbl)(ULONG ulIfIndex,
        IP6_ADDR_ADDRTBL_S *pstInOutMIBAddrTbl);
    METHOD_(ULONG, pfIP6_Addr_GetNextAddrTbl)(ULONG ulIfIndex,
        IP6_ADDR_ADDRTBL_S *pstInOutMIBAddrTbl);
    METHOD_(ULONG, pfIP6_Addr_GetFirstIfTbl)(ULONG *pulIpv6IfIndex);
    METHOD_(ULONG, pfIP6_Addr_GetNextIfTbl)(ULONG *pulIpv6IfIndex);
    METHOD_(ULONG, pfIP6_Addr_IfTblGetValueByIndex)(ULONG ulIpv6IfIndex,
        IP6_ADDR_IFENTRY_S *);
    METHOD_(ULONG, pfIP6_Addr_IfTblIndexExist)(ULONG ulIfIndex);
    METHOD_(ULONG, pfIP6_Addr_SetMaxMtu)(ULONG ulMaxMtu);
    METHOD_(ULONG, pfIP6_Addr_GetMaxMtu)(ULONG *pulMaxMtu);
    METHOD_(VOID, pfIP6_Addr_SetDebug)(ULONG ulSwitch, ULONG ulLevel);
    METHOD_(VOID, pfIP6_Addr_GetDebug)(ULONG* ulSwitch, ULONG* ulLevel);
    METHOD_(VOID, pfIP6_Addr_DisplayIntAddDebug)(IP6IFADDR_S *pIp6IfAddr);

    /* New API's added for SGSN by karthik */
    METHOD_(ULONG, pfIP6_Addr_Disp_Open) (UINTPTR *pulSessionId,
         IP6_ADDR_DISP_FILTER_S *pstDispAddrFilter);

    METHOD_(ULONG, pfIP6_Addr_Display_GetFirst) (UINTPTR ulSessionId,
         IP6_ADDR_GET_INFO_S *pstRetAddr);

    METHOD_(ULONG, pfIP6_Addr_Display_GetNext) (UINTPTR ulSessionId,
          IP6_ADDR_GET_INFO_S *pstRetAddr);

    METHOD_(ULONG, pfIP6_Addr_Disp_Close) (UINTPTR ulSessionId);
    METHOD_(ULONG, pfIP6_Addr_Del_All_EuiAddr)(ULONG ulIfNetIndex);

    METHOD_(ULONG, pfIP6_Addr_UniAddr_GetFirst)(UINTPTR ulSessionId, ULONG ulAddrScope,
                        ULONG ulIfIndex, IP6_ADDR_INFO_S *pstDispUniAddr);

    METHOD_(ULONG, pfIP6_Addr_UniAddr_GetNext)(UINTPTR ulSessionId, ULONG ulAddrScope,
                        ULONG ulIfIndex, IP6_ADDR_INFO_S *pstDispUniAddr);

    METHOD_(ULONG, pfIP6_Addr_MultiAddr_GetFirst)(UINTPTR ulSessionId, ULONG ulAddrScope,
            ULONG ulIfIndex, IP6_NDHOST_MULTIADDR_INFO_S *pstDispMultiAddr);

    METHOD_(ULONG, pfIP6_Addr_MultiAddr_GetNext)(UINTPTR ulSessionId,
                            IP6_NDHOST_MULTIADDR_INFO_S *pstDispMultiAddr);

    METHOD_(ULONG, pfIP6_Addr_GetDADState)(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr, ULONG *pulDadState);
    METHOD_(ULONG, pfIP6_Addr_RestartDADForAddr)(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr);
};

/*Map to new interface names*/
#define  IIF_IP6_ADDR_CFG     IIF_IP6_ADDR_ComIntCFG
#define  IIF_IP6_ADDR_CFGVtbl IIF_IP6_ADDR_ComIntCFGVtbl

/* Level 1 Functional Interface */
DECLARE_INTERFACE(IIF_IP6_ADDR_ComIntFun)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_PlugOut)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_IF_Attach)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_IF_Detach)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_LLC_Notify) (VOID *pstIf,
                                            ULONG ulCmd, CHAR *pcData);
    METHOD_(ULONG, pfIP6_Addr_PhyUpDownNotify)(VOID *pstIf,
                                            ULONG ulCmd, CHAR *pcData);
    METHOD_(IP6IFADDR_S *, pfIP6_GetLinkLocalAddrOnIf)(VOID *pstIfNet);
    METHOD_(VOID, pfIP6_Addr_NotifyLinkLayer)(VOID *pstIf, ULONG ulCmd);
    METHOD_(ULONG, pfIP6_Addr_IFA_IfWithBestPrefix)
                                            (SOCKADDR_IN6_S *pstSockIn6Addr,
                                            VOID *pstIfnet,
                                            IN6ADDR_S **pstAddrOut);
    METHOD_(ULONG, pfIP6_Addr_GetLinkMtu)(VOID *pstIfnet,
                                            ULONG *pulMtu);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_IfWithDstAddr)
                                (SOCKADDR_IN6_S *pstSockAddr, USHORT usVrfIndex);
    METHOD_(ULONG, pfIP6_Addr_IfWithAddr)(SOCKADDR_IN6_S *pstSockIn6Addr,
                                                USHORT usVrfIndex);
    METHOD_(IP6MULTI_S *, pfIP6_Addr_IF_AddMulti)(IN6ADDR_S *pstMultiAddr,
                                                    VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_IF_DelMulti)(IN6ADDR_S *pstIn6Addr, VOID *pstIf);
    METHOD_(IN6ADDR_S, pfIP6_Addr_Get_MainIp6Addr)(IP6IFNET_S *pstIp6If);
    METHOD_(ULONG, pfIP6_Addr_GetIfnetIndex)(IN6ADDR_S stAddr,
                                                        USHORT usVrfIndex);
    METHOD_(ULONG, pfIP6_IF_IsAddrOnIpIf)(VOID *pstIfNet, IN6ADDR_S stIn6Addr, BOOL_T bCheckIFStatus);
    METHOD_(ULONG, pfIP6_Addr_IF_HaveIp6Addr)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_IsAnycastAddress)(IN6ADDR_S  stIn6Addr,
                                                        ULONG ulPrefixLen);
    METHOD_(ULONG, pfIP6_Addr_IsInvalidIP4Address)(ULONG ulAddr);
    METHOD_(ULONG, pfIP6_Addr_GetInterfaceId)(VOID *pstIf,
                                IP6_INTERFACEID_S *pstInterfaceId);
    METHOD_(ULONG, pfIP6_Addr_IFA_IfWithNextBestPrefix)(VOID *pstIf,
        IN6ADDR_S stAddrIn, IN6ADDR_S **ppstAddrOut, USHORT usVrfIndex);
    METHOD_(VOID, pfIP6_Addr_UnLoopBack)(VOID *pstIf);
    METHOD_(IN6ADDR_S *, pfIP6_Addr_GetValidUnicastAddrOnIf)(VOID *pstIfNet);
    METHOD_(ULONG, pfIP6_Addr_SerialLinkChange)(VOID* pstIfNet, ULONG ulCmd);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_ValidIPAddr)(VOID);
    METHOD_(ULONG, pfIP6_Addr_Get_MainIp6AddrByType)(IP6IFNET_S *pstIp6If,
        ULONG ulType, IN6ADDR_S *pstAddr);
    METHOD_(ULONG, pfIP6_Addr_GetIfState)(IP6_ADDR_IFSTATUS_S * pstUpDownInfo);
    METHOD_(ULONG, pfIP6_Addr_SendGetIfStatusMsg)
            (IP6_ADDR_IFSTATUS_S * pstUpDownInfo);
    METHOD_(ULONG, pfIP6_Addr_SelectSourceAddr)(
                                                const IN6ADDR_S *pstIp6DestAddr,
                                                IN6ADDR_S *pstSrcAddr,
                                                ULONG ulIfIndex,
                                                ULONG ulVrfIndex);
    METHOD_(IP6MULTI_S *, pfIP6_FindMultiOnIpIf) (IN6ADDR_S *pstAddr,
                                                    IP6IFNET_S *pstIp6IfNet);
    METHOD_(ULONG, pfIP6_IsInvalidIP6Address)(VOID *pstIfNet,
                                                IN6ADDR_S  stIn6Addr);

    /* Added for VISP LTE Requirements */
    METHOD_(ULONG, pfIP6_Addr_RestartDAD)(ULONG ulIfIndex);
    /*Added for VISP LTE Requirement 29 Dec 2009 */
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_IF_FindSameIpAddr)(IN6ADDR_S stIn6Addr,
                                                        IP6IFNET_S *pstIp6IfNet);
    METHOD_(ULONG, pfIP6_Addr_L3VPN6_Notify)(ULONG ulEvent, VOID *pData);
    METHOD_(ULONG, pfIP6_Addr_MTU_Notify)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_IsLocalAddr)(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);
    METHOD_(ULONG, pfIP6_Addr_GetIfIndexByAddr)(ULONG ulVrfIndex, IN6ADDR_S *pstIn6Addr, ULONG *pulIfIndex);
    METHOD_(ULONG, pfIP6_Addr_NotifyRmForIpcIf)(ULONG ulVrfIndex, VOID *pvIf);    
    METHOD_(ULONG, pfIP6_IsLocalIfAddr)(IN6ADDR_S  *pstAddr, ULONG ulIfIndex);
};

/*Map to new interface names*/
#define  IIF_IP6_ADDR_FUN     IIF_IP6_ADDR_ComIntFun
#define  IIF_IP6_ADDR_FUNVtbl IIF_IP6_ADDR_ComIntFunVtbl


/*******************************************************************************
                                ADDR ND-HOST LEVEL 1 V-tables
*******************************************************************************/

/* Level 1 Host Init Interface */
DECLARE_INTERFACE (IIF_IP6_ADDR_HOST_INIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_Srm_RegCallbackFunc)
                        (IP6_ADDR_SRM_CALLBACK_FUNC_S *pstCallbackFunc);
    METHOD_(ULONG, pfIP6_Addr_Reg_Platform_Hook)
                    (IP6_ADDR_DADRESULT_NOTIFY_FUNC_S *pstCallbackFunc);
};

/* Level 1 Host CFG Interface */
DECLARE_INTERFACE(IIF_IP6_ADDR_HOST_CFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_Add_GlobalUniAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S  stIn6Addr, ULONG ulPrefixLen);
    METHOD_(ULONG, pfIP6_Addr_Add_LinkLocalAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S  stIn6Addr);
    METHOD_(ULONG, pfIP6_Addr_Del_GlobalUniAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S stIn6Addr, ULONG ulPrefixLen);
    METHOD_(ULONG, pfIP6_Addr_Del_LinkLocalAddr)(ULONG ulIfNetIndex,
        IN6ADDR_S  stIn6Addr);
    METHOD_(ULONG, pfIP6_Addr_OpenTable)(ULONG ulMainType,
        UINTPTR *pulWaitListHandle, UCHAR ucWaitlistType);
    METHOD_(ULONG, pfIP6_Addr_CloseTable)(UINTPTR ulNBWaitListHandle);
    METHOD_(ULONG, pfIP6_Addr_GetFirstExt)(UINTPTR ulNBWaitListHandle,
        VOID *pstNBNode, VOID **ppstCurrentNode);
    METHOD_(ULONG, pfIP6_Addr_GetNextExt)(UINTPTR ulNBWaitListHandle,
        ULONG ulMainType, VOID ** ppCurrentObject);
    METHOD_(ULONG, pfIP6_Addr_SetMaxMtu)(ULONG ulMaxMtu);
    METHOD_(ULONG, pfIP6_Addr_GetMaxMtu)(ULONG *pulMaxMtu);

    /* Added by Rakesh for New Adapter API 12-07-2011 */
    METHOD_(ULONG, pfIP6_Addr_SetMTU)(ULONG ulIfnetIndex,
            ULONG ulIsNoCmd, ULONG ulMtu);
    METHOD_(ULONG, pfIP6_Addr_GetMTU)(ULONG ulIfnetIndex,
            ULONG ulIsCmd, ULONG *pulMtu);
    METHOD_(VOID, pfIP6_Addr_SetDebug)(ULONG ulSwitch, ULONG ulLevel);
    METHOD_(VOID, pfIP6_Addr_GetDebug)(ULONG* ulSwitch, ULONG* ulLevel);
    METHOD_(VOID, pfIP6_Addr_DisplayIntAddDebug)(IP6IFADDR_S *pIp6IfAddr);

    METHOD_(ULONG, pfIP6_Addr_Disp_Open) (UINTPTR *pulSessionId,
         IP6_ADDR_DISP_FILTER_S *pstDispAddrFilter);

    METHOD_(ULONG, pfIP6_Addr_Display_GetFirst) (UINTPTR ulSessionId,
         IP6_ADDR_GET_INFO_S *pstRetAddr);

    METHOD_(ULONG, pfIP6_Addr_Display_GetNext) (UINTPTR ulSessionId,
          IP6_ADDR_GET_INFO_S *pstRetAddr);

    METHOD_(ULONG, pfIP6_Addr_Disp_Close) (UINTPTR ulSessionId);
    METHOD_(ULONG, pfIP6_Addr_UniAddr_GetFirst)(UINTPTR ulSessionId, ULONG ulAddrScope,
                        ULONG ulIfIndex, IP6_ADDR_INFO_S *pstDispUniAddr);

    METHOD_(ULONG, pfIP6_Addr_UniAddr_GetNext)(UINTPTR ulSessionId, ULONG ulAddrScope,
                        ULONG ulIfIndex, IP6_ADDR_INFO_S *pstDispUniAddr);

    METHOD_(ULONG, pfIP6_Addr_MultiAddr_GetFirst)(UINTPTR ulSessionId, ULONG ulAddrScope,
            ULONG ulIfIndex, IP6_NDHOST_MULTIADDR_INFO_S *pstDispMultiAddr);

    METHOD_(ULONG, pfIP6_Addr_MultiAddr_GetNext)(UINTPTR ulSessionId,
                            IP6_NDHOST_MULTIADDR_INFO_S *pstDispMultiAddr);

    METHOD_(ULONG, pfIP6_Addr_SetIpv6FuncOnIntf)
                            (ULONG ulIntfIndex, BOOL_T bIpv6FuncStatus);

    METHOD_(ULONG, pfIP6_Addr_GetIpv6FuncStatusOnIntf)(ULONG ulIfIndex,
                                                    BOOL_T *pbIpv6FuncStatus);

    METHOD_(ULONG, pfIP6_Addr_Del_AllManualAddr)(ULONG ulIfIndex);

    METHOD_(ULONG, pfIP6_Addr_Del_AllStatelessAddr)(ULONG ulIfIndex);

    METHOD_(ULONG, pfIP6_Addr_Register_IntfIPV6StatusNotify)(const
                IP6_ADDR_APPLICATION_CALLBACK_FUNC_S *pstApplicationCallBack);

    METHOD_(ULONG, pfIP6_Addr_UnRegister_IntfIPV6Notify)(ULONG ulModuleId);

    /* Added by Suraj_R for VISP */
    METHOD_(ULONG, pfIP6_Addr_EnableDisableIntfAutoconfig)(ULONG ulIfIndex,
                                                    ULONG ulOperation);
    METHOD_(ULONG, pfIP6_Addr_GetDADState)(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr, ULONG *pulDadState);
    METHOD_(ULONG, pfIP6_Addr_RestartDADForAddr)(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr);
};

/* Level 1 Host Functional Interface */
DECLARE_INTERFACE(IIF_IP6_ADDR_HOST_FUN)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_Addr_PlugOut)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_IF_Attach)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_IF_Detach)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_LLC_Notify) (VOID *pstIf,
                                            ULONG ulCmd, CHAR *pcData);
    METHOD_(ULONG, pfIP6_Addr_PhyUpDownNotify)(VOID *pstIf,
                                            ULONG ulCmd, CHAR *pcData);
    METHOD_(IP6IFADDR_S *, pfIP6_GetLinkLocalAddrOnIf)(VOID *pstIfNet);
    METHOD_(VOID, pfIP6_Addr_NotifyLinkLayer)(VOID *pstIf, ULONG ulCmd);

   /* METHOD_(ULONG, pfIP6_Addr_IFA_IfWithBestPrefix)
                                            (SOCKADDR_IN6_S *pstSockIn6Addr,
                                            VOID *pstIfnet,
                                            IN6ADDR_S **pstAddrOut); */
    METHOD_(ULONG, pfIP6_Addr_GetLinkMtu)(VOID *pstIfnet,
                                            ULONG *pulMtu);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_IfWithDstAddr)
                            (SOCKADDR_IN6_S *pstSockAddr, USHORT usVrfIndex);
    METHOD_(ULONG, pfIP6_Addr_IfWithAddr)(SOCKADDR_IN6_S *pstSockIn6Addr,
                                                USHORT usVrfIndex);
    METHOD_(IP6MULTI_S *, pfIP6_Addr_IF_AddMulti)(IN6ADDR_S *pstMultiAddr,
                                                    VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_IF_DelMulti)(IN6ADDR_S *pstIn6Addr, VOID *pstIf);
    METHOD_(IN6ADDR_S, pfIP6_Addr_Get_MainIp6Addr)(IP6IFNET_S *pstIp6If);
    METHOD_(ULONG, pfIP6_Addr_GetIfnetIndex)(IN6ADDR_S stAddr,
                                                        USHORT usVrfIndex);
    METHOD_(ULONG, pfIP6_IF_IsAddrOnIpIf)(VOID *pstIfNet, IN6ADDR_S stIn6Addr, BOOL_T bCheckIFStatus);
    METHOD_(ULONG, pfIP6_Addr_IF_HaveIp6Addr)(VOID *pstIf);
    METHOD_(ULONG, pfIP6_Addr_IsAnycastAddress)(IN6ADDR_S  stIn6Addr,
                                                        ULONG ulPrefixLen);
    METHOD_(ULONG, pfIP6_Addr_IsInvalidIP4Address)(ULONG ulAddr);
    METHOD_(ULONG, pfIP6_Addr_GetInterfaceId)(VOID *pstIf,
                                IP6_INTERFACEID_S *pstInterfaceId);

    /* METHOD_(ULONG, pfIP6_Addr_IFA_IfWithNextBestPrefix)(VOID *pstIf,
        IN6ADDR_S stAddrIn, IN6ADDR_S **ppstAddrOut, USHORT usVrfIndex); */
    METHOD_(VOID, pfIP6_Addr_UnLoopBack)(VOID *pstIf);
    METHOD_(IN6ADDR_S *, pfIP6_Addr_GetValidUnicastAddrOnIf)(VOID *pstIfNet);
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_Get_ValidIPAddr)(VOID);
    METHOD_(ULONG, pfIP6_Addr_Get_MainIp6AddrByType)(IP6IFNET_S *pstIp6If,
        ULONG ulType, IN6ADDR_S *pstAddr);
    METHOD_(ULONG, pfIP6_Addr_GetIfState)(IP6_ADDR_IFSTATUS_S * pstUpDownInfo);

    /* METHOD_(ULONG, pfIP6_Addr_SendGetIfStatusMsg)
        (IP6_ADDR_IFSTATUS_S * pstUpDownInfo); */
    METHOD_(ULONG, pfIP6_Addr_SelectSourceAddr)(
                                                const IN6ADDR_S *pstIp6DestAddr,
                                                IN6ADDR_S *pstSrcAddr,
                                                ULONG ulIfIndex,
                                                ULONG ulVrfIndex);
    METHOD_(IP6MULTI_S *, pfIP6_FindMultiOnIpIf) (IN6ADDR_S *pstAddr,
                                                    IP6IFNET_S *pstIp6IfNet);
    METHOD_(ULONG, pfIP6_IsInvalidIP6Address)(VOID *pstIfNet,
                                                IN6ADDR_S  stIn6Addr);

    /* Added for VISP LTE Requirements */
    METHOD_(ULONG, pfIP6_Addr_RestartDAD)(ULONG ulIfIndex);
    /*Added for VISP LTE Requirement 29 Dec 2009 */
    METHOD_(IP6IFADDR_S *, pfIP6_Addr_IF_FindSameIpAddr)(IN6ADDR_S stIn6Addr,
                                                    IP6IFNET_S *pstIp6IfNet);
    METHOD_(ULONG, pfIP6_Addr_L3VPN6_Notify)(ULONG ulEvent, VOID *pData);
    METHOD_(ULONG, pfIP6_IsLocalAddr)(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);
    METHOD_(ULONG, pfIP6_Addr_GetIfIndexByAddr)(ULONG ulVrfIndex, IN6ADDR_S *pstIn6Addr, ULONG *pulIfIndex);
    METHOD_(ULONG, pfIP6_Addr_NotifyRmForIpcIf)(ULONG ulVrfIndex, VOID *pvIf);
};

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _ADDR_INC_H */

