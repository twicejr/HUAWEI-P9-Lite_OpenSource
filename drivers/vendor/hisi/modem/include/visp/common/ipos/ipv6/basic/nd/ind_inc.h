/******************************************************************************
*             Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ind_inc.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  IPBIRV100R003.IPv6.E001
*    Module Name :  ND
*    Create Date :  2006/09/23
*    Author      :  Yinyuanbin
*    Description :  To define and expose ND Component and interface
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-10-01  yinyuanbin    Created for including all public definitions in
*                             this file, for IPOS IR V1R2
*  2008-05-02  Wanlu           Updated for VISPV1R7 integration
************************************************************************/

#ifndef _ND_INC_H
#define _ND_INC_H

#ifdef  __cplusplus
extern "C"{
#endif

#include "common/ipos/ipv6/basic/nd/nd_public.h"


/* Component ID declaration */
#define CID_IPV6_ND                                   (CID_IPV6_BASE + 6)

/* Interface IDs declaration for Common Vtable */
#define IID_IP6_ND_COMMON                    (IID_IPV6_BASE + 60)

/* Interface IDs declaration for Router*/
#define IID_IPV6_ND_INTF_INIT                (IID_IPV6_BASE + 61)
#define IID_IPV6_ND_INTF_CFG                 (IID_IPV6_BASE + 62)
#define IID_IPV6_ND_INTF_FUN                 (IID_IPV6_BASE + 63)

/*Mapp to new IIDs*/
#define IID_IP6_ND_INIT IID_IPV6_ND_INTF_INIT
#define IID_IP6_ND_CFG  IID_IPV6_ND_INTF_CFG
#define IID_IP6_ND_FUN  IID_IPV6_ND_INTF_FUN


/* Interface IDs declaration for Host*/
#define IID_IP6_ND_HOST_INIT                 (IID_IPV6_BASE + 64)
#define IID_IP6_ND_HOST_CFG                  (IID_IPV6_BASE + 65)
#define IID_IP6_ND_HOST_FUN                  (IID_IPV6_BASE + 66)
#define IID_IP6_ND_HOST_DHCP6CAdapt  (IID_IPV6_BASE + 67)


/* ND Common VTable Structure - Level 1 */
DECLARE_INTERFACE (IIF_IP6_ND_COMMON)
{
    IUNKNOWN_METHODS
    METHOD_(BOOL_T, pfIP6_ND_IsNodeHost)(VOID);
};

/******************************************************************************/
/*                      Router VTable Start Here                              */
/******************************************************************************/

/***************
   INIT VTable
***************/

/* ND Init VTable strcture Level - 1 */
DECLARE_INTERFACE (IIF_IP6_ND_ComIntINIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_SGSN_RegCallbackFunc)(
        IP6_ND_SGSN_CALLBACK_FUNC_S *pstNDSgsnCallback);
    METHOD_(ULONG, pfIP6_ND_SOCK_RegCallbackFunc)(
        IP6_ND_SOCK_CALLBACK_SET_S *pstNDSocketCallback);
    METHOD_(ULONG, pfIP6_ND_Flow_RegCallbackFunc)(
        IP6_ND_FLOW_CALLBACK_SET_S *pstFlowCallback);
};

#define IIF_IP6_ND_INIT         IIF_IP6_ND_ComIntINIT
#define IIF_IP6_ND_INITVtbl     IIF_IP6_ND_ComIntINITVtbl

/******************************************************************************/

/**********************
   Configuration VTable
***********************/

/* ND Configuration VTable Structure Level 1 */
DECLARE_INTERFACE(IIF_IP6_ND_ComIntCFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_SetManageFlag) (ULONG ulIfNetIndex,
        IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetManageFlag) (ULONG ulIfNetIndex,
        UCHAR *pucRetVal);
    METHOD_(ULONG, pfIP6_ND_SetOtherFlag) (ULONG ulIfNetIndex,
        IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetOtherFlag) (ULONG ulIfNetIndex,
        UCHAR *pucRetVal);
    METHOD_(ULONG, pfIP6_ND_SetReachableTime) (ULONG ulIfNetIndex,
        ULONG ulValue, IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetReachableTime) (ULONG ulIfNetIndex,
        ULONG *pulRetVal);
    METHOD_(ULONG, pfIP6_ND_SetRAInterval) (ULONG ulIfnetIndex,
        ULONG ulValue, IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetRAInterval) (ULONG ulIfnetIndex,
        ULONG *pulRetVal);
    METHOD_(ULONG, pfIP6_ND_SetRAMinInterval) (ULONG ulIfnetIndex,
        ULONG ulValue, IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetRAMinInterval) (ULONG ulIfnetIndex,
        ULONG *pulRetVal);
    METHOD_(ULONG, pfIP6_ND_SetDefaultTime) (ULONG ulIfnetIndex,
        ULONG ulValue, IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetDefaultTime) (ULONG ulIfnetIndex,
        ULONG *pulRetVal);
    METHOD_(ULONG, pfIP6_ND_SetHopLimit) (UCHAR ucValue,
        IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_SuppressRAFlag) (ULONG ulIfNetIndex,
        IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG,pfIP6_ND_GetRAFlag) (ULONG ulIfnetIndex,UCHAR *pucRetVal);
    METHOD_(ULONG, pfIP6_ND_SetNSInterval) (ULONG ulIfNetIndex, ULONG ulValue,
        IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetNSInterval) (ULONG ulIfNetIndex,
        ULONG *pulRetVal);
    METHOD_(ULONG, pfIP6_ND_SetDADAttempt) (ULONG ulIfNetIndex, ULONG ulValue,
        IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetDADAttempt) (ULONG ulIfNetIndex,
        ULONG *pulRetVal);

    /* Description: API signature is changed by combining all arguments in one
       structure for IAS support */
    METHOD_(ULONG, pfIP6_ND_AddStaticNBEntry)
        (ND_STATIC_NBENTRY_S *pstStaticNBEntry);


    METHOD_(ULONG, pfIP6_ND_DelStaticNBEntry) (ULONG ulIfNetIndex,
        IN6ADDR_S stIn6Addr);
    METHOD_(ULONG, pfIP6_ND_ProcPrefixInfo) (ULONG ulIfIndex,
        ULONG ulNo, ULONG ulValidTime, UCHAR ucAutoConfFlag,
        ULONG ulPreferredTime, ULONG ulPrefixLength, IN6ADDR_S stAddrPrefix,
        UCHAR ucOnLinkFlag);
    METHOD_(ULONG, pfIP6_ND_ResetStaticNBEntries) (VOID);
    METHOD_(ULONG, pfIP6_ND_ResetDynamicNBEntries) (VOID);
    METHOD_(ULONG, pfIP6_ND_ResetIfAllNBEntries) (VOID *pvIfNet);
    METHOD_(ULONG, pfIP6_ND_ResetAllNBEntries) (VOID);
    METHOD_(ULONG, pfIP6_ND_GetFirstExt) (VOID *pvIfNet,
         ND_NBENTRY_INFO_S *pNBEntryOut, UINTPTR ulNBWaitListHandle);
    METHOD_(ULONG, pfIP6_ND_OpenTable) (UINTPTR *pulWaitListHandle);
    METHOD_(ULONG, pfIP6_ND_OpenIOTable) (UINTPTR *pulWaitListHandle,
         VOID *pvIfNet);
    METHOD_(VOID, pfIP6_ND_CloseTable) (UINTPTR ulNBWaitListHandle);
    METHOD_(ULONG, pfIP6_ND_GetNextExt) (UINTPTR ulNBWaitListHandle,
        ND_NBENTRY_INFO_S *pstNextNBInfo);
    METHOD_(ULONG, pfIP6_ND_IsNBEntryStatic) (VOID *pvCurrentNode);
    METHOD_(ND_GETFROMCORE_S *, pfIP6_ND_GetNDInfoFromCore) (VOID *pvIfnet);
    METHOD_(ULONG, pfIP6_ND_GetStaticEntryCount)(ULONG ulIfNetIndex,
        ULONG *pulStaticNBCount);
    METHOD_(ULONG, pfIP6_ND_AddrPrefixTbl_GetFirst) (
        IP6_ND_PrefixTbl_S *pstOutPfxTblEntry);
    METHOD_(ULONG, pfIP6_ND_AddrPrefixTbl_GetEntry) (ULONG ulIfIndex,
        IP6_ND_PrefixTbl_S *pstOutPfxTblEntry);
    METHOD_(ULONG, pfIP6_ND_AddrPrefixTbl_GetNextEntry) (ULONG ulIfIndex,
        IP6_ND_PrefixTbl_S *pstOutPfxTblEntry);
    METHOD_(VOID, pfIP6_ND_SetVlink) (ULONG ulFlag);
    METHOD_(ULONG, pfIP6_ND_SetDeleteEntryLimit) (ULONG ulEntryToDelete);
    METHOD_(ULONG, pfIP6_ND_GetDeleteEntryLimit) (ULONG *pulRetVal);
    METHOD_(VOID, pfIP6_ND_SetGlobalValue) (ULONG ulValue);
    METHOD_(VOID, pfIP6_ND_Reboot) (VOID);
    METHOD_(VOID, pfIP6_ND_SetTimerQueueID)(ULONG ulTimerQueueID);
    METHOD_(ULONG, pfIP6_ND_NBValidate_Address) (IN6ADDR_S  stIn6Addr,
        UCHAR *pucLLAddr, UCHAR ucFlag, ULONG ulIfIndex);
    METHOD_(ULONG, pfIP6_ND_GetNode) (UINTPTR ulNBWaitListHandle,
                                     ND_NBENTRY_INFO_S *pstNBInfo);
    METHOD_(ULONG, pfIP6_ND_SetDebug) (IP6_ND_CFG_OPT_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetDebug) (ULONG *pulRetVal);

    /* Added by Rajat Phull, Moved from Init V-Table(Level 3) */
    METHOD_(ULONG, pfIP6_ND_ResetIfAllNBEntriesPerVLAN)(ULONG ulIfIndex,
                                                ULONG ulVlanId, UCHAR ucType);
    METHOD_(ULONG, pfIP6_ND_DelDynamicNBEntriesByAddr)(ULONG ulIfIndex, 
                                              IN6ADDR_S *pstIn6Addr);
    METHOD_(ULONG, pfIP6_ND_NS_Output_Ext)(ULONG ulIfIndex,
                                            ULONG  ucOptionFlag,
                                            IN6ADDR_S *pstDstAddr,
                                            IN6ADDR_S *pstSrcAddr,
                                            IN6ADDR_S *pstTgtAddr);
    METHOD_(ULONG, pfIP6_ND_SetNDSpecialProxyFlag)(ULONG ulIfIndex,
                                                   UCHAR ucFalg);
    /* Modified by guojianjun178934, 接口状态变化或MAC地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    METHOD_(ULONG, pfIP6_ND_SetNAAttempt) (ULONG ulIfNetIndex, ULONG ulValue, IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetNAAttempt) (ULONG ulIfNetIndex, ULONG *pulRetVal);
    METHOD_(ULONG, pfIP6_ND_SetNAInterval) (ULONG ulIfNetIndex, ULONG ulValue, IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetNAInterval) (ULONG ulIfNetIndex, ULONG *pulRetVal);
    /*End of Modified by guojianjun178934, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
};

#define IIF_IP6_ND_CFG              IIF_IP6_ND_ComIntCFG
#define IIF_IP6_ND_CFGVtbl          IIF_IP6_ND_ComIntCFGVtbl

/******************************************************************************/

/**********************
   Function VTable
***********************/

/* ND Function VTable Structure - Level 1 */
DECLARE_INTERFACE (IIF_IP6_ND_ComIntFun)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_Lookup)(MBUF_S *pstMbuf);
    METHOD_(ULONG, pfIP6_ND_EnableRouterFlag)(VOID);
    METHOD_(ULONG, pfIP6_ND_DisableRouterFlag)(VOID);
    METHOD_(VOID, pfIP6_ND_UpDownNotify) (VOID *pvIf, ULONG ulCmd,
        CHAR *pcData);
    METHOD_(VOID, pfIP6_ND_PhyUpDownNotify)(VOID *pvIf,ULONG ulCmd,
        CHAR *pcData);
    METHOD_(VOID, pfIP6_ND_LLAddrNotify)(VOID *pvIf, CHAR *pcData);
    METHOD_(VOID, pfIP6_ND_ShutDownNotify)(VOID *pvIf);
    METHOD_(ULONG, pfIP6_ND_GetVlinkStatus)(VOID);
    METHOD_(ND_PREFIX_S *, pfIP6_ND_FindPrefix)(ULONG ulIfnetIndex,
        IN6ADDR_S stPrefix);
    METHOD_(UCHAR, pfIP6_ND_GetHopLimit)(VOID);

    METHOD_(ULONG, pfIP6_ND_FetchNBEntry)(ULONG ulIfnetIndex,
        IN6ADDR_S *pstIPv6Addr, ND_NBENTRY_INFO_S *pstNBInfo);

    METHOD_(ULONG, pfIP6_ND_Start_NUD)(ULONG ulIfnetIndex,
                                            IN6ADDR_S *pstIPv6Addr);
    METHOD_(ULONG, pfIP6_ND_SendAdvertiseNA)(CHAR *szIfName, 
             IN6ADDR_S *pstDstAddr, UCHAR *pucMac);
};

#define IIF_IP6_ND_FUN              IIF_IP6_ND_ComIntFun
#define IIF_IP6_ND_FUNVtbl          IIF_IP6_ND_ComIntFunVtbl

/******************************************************************************/
/*                      ND Host VTable Starts Here                            */
/******************************************************************************/

/***************
   INIT VTable
***************/

/* ND Host Init VTable strcture Level - 1 */
DECLARE_INTERFACE (IIF_IP6_ND_HOST_INIT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_SOCK_RegCallbackFunc)
        (IP6_ND_SOCK_CALLBACK_SET_S *pstNDSocketCallback);
    METHOD_(ULONG, pfIP6_ND_Flow_RegCallbackFunc)(
        IP6_ND_FLOW_CALLBACK_SET_S *pstFlowCallback);
};

/******************************************************************************/

/**********************
   Configuration VTable
***********************/

/* ND Configuration VTable Structure */
DECLARE_INTERFACE(IIF_IP6_ND_HOST_CFG)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_SetDADAttempt) (ULONG ulIfNetIndex, ULONG ulValue,
        IP6_ND_SETFLAG_E enFlag);

    METHOD_(ULONG, pfIP6_ND_GetDADAttempt) (ULONG ulIfNetIndex,
        ULONG *pulRetVal);

    /* Description: API signature is changed by combining all arguments in one
       structure for IAS support */
    METHOD_(ULONG, pfIP6_ND_AddStaticNBEntry)
        (ND_STATIC_NBENTRY_S *pstStaticNBEntry);


    METHOD_(ULONG, pfIP6_ND_DelStaticNBEntry) (ULONG ulIfNetIndex,
        IN6ADDR_S stIn6Addr);

    METHOD_(ULONG, pfIP6_ND_ResetStaticNBEntries) (VOID);
    METHOD_(ULONG, pfIP6_ND_ResetDynamicNBEntries) (VOID);
    METHOD_(ULONG, pfIP6_ND_ResetIfAllNBEntries) (VOID *pvIfNet);
    METHOD_(ULONG, pfIP6_ND_ResetAllNBEntries) (VOID);

    METHOD_(ULONG, pfIP6_ND_GetFirstExt) (VOID *pvIfNet,
         ND_NBENTRY_INFO_S *pNBEntryOut, UINTPTR ulNBWaitListHandle);
    METHOD_(ULONG, pfIP6_ND_OpenTable) (UINTPTR *pulWaitListHandle);
    METHOD_(VOID, pfIP6_ND_CloseTable) (UINTPTR ulNBWaitListHandle);
    METHOD_(ULONG, pfIP6_ND_GetNextExt) (UINTPTR ulNBWaitListHandle,
        ND_NBENTRY_INFO_S *pstNextNBInfo);
    METHOD_(ULONG, pfIP6_ND_IsNBEntryStatic) (VOID *pstCurrentNode);
    METHOD_(ULONG, pfIP6_ND_GetStaticEntryCount)(ULONG ulIfNetIndex,
        ULONG *pulStaticNBCount);
    METHOD_(ULONG, pfIP6_ND_SetDeleteEntryLimit) (ULONG ulEntryToDelete);
    METHOD_(ULONG, pfIP6_ND_GetDeleteEntryLimit) (ULONG *pulRetVal);
    METHOD_(VOID, pfIP6_ND_SetTimerQueueID)(ULONG ulTimerQueueID);
    METHOD_(ULONG, pfIP6_ND_NBValidate_Address) (IN6ADDR_S  stIn6Addr,
        UCHAR *pucLLAddr, UCHAR ucFlag, ULONG ulIfIndex);
    METHOD_(ULONG, pfIP6_ND_GetNode) (UINTPTR ulNBWaitListHandle,
         ND_NBENTRY_INFO_S* pstNBInfo);

    METHOD_(ULONG, pfIP6_ND_GetNDHostParams)(
        ULONG ulIfIndex, IP6_ND_GETHOSTPARAMS_S *pstHostParams);

    METHOD_(ULONG, pfIP6_ND_GetDefRouterEntryCount)(
        ULONG ulIfIndex, ULONG*pulDefRouterCnt);
    METHOD_(ULONG, pfIP6_ND_DefRouterOpenTable)(ULONG ulIfIndex,
        UINTPTR *pulHandle);
    METHOD_(ULONG, pfIP6_ND_DefRouterGetFirst)(
        UINTPTR ulWaitListHandle, IP6_ND_DEFROUTER_INFO_S *pstDefRouterEntryOut);
    METHOD_(ULONG, pfIP6_ND_DefRouterGetNext)(UINTPTR ulWaitListHandle,
        IP6_ND_DEFROUTER_INFO_S *pstDefRouterEntryOut);
    METHOD_(ULONG, pfIP6_ND_DefRouterCloseTable)(UINTPTR ulWaitListHandle);

    METHOD_(ULONG, pfIP6_ND_GetPrefixListEntryCount)(
        ULONG ulIfIndex, ULONG *pulPrefixListEntryCnt);
    METHOD_(ULONG, pfIP6_ND_PrefixListOpenTable)(ULONG ulIfIndex,
        UINTPTR *pulHandle);
    METHOD_(ULONG, pfIP6_ND_PrefixListGetFirst)(UINTPTR ulWaitListHandle,
        IP6_ND_INTFPREFIX_INFO_S *pstPrefixEntryOut);
    METHOD_(ULONG, pfIP6_ND_PrefixListGetNext)(UINTPTR ulWaitListHandle,
        IP6_ND_INTFPREFIX_INFO_S *pstPrefixEntryOut);
    METHOD_(ULONG, pfIP6_ND_PrefixListCloseTable)(UINTPTR ulWaitListHandle);

    METHOD_(ULONG, pfIP6_ND_GetDestCacheEntryCount)(ULONG ulVrfIndex, ULONG *pulDestCacheEntryCnt);
    METHOD_(ULONG, pfIP6_ND_DestinationCacheOpenTable)(UINTPTR *pulHandle);
    METHOD_(ULONG, pfIP6_ND_DestCacheGetFirst)(UINTPTR ulWtLstHandle, ULONG ulVrfIndex,
        IP6_ND_DESTCACHE_INFO_S  *pstDestEntryOut);
    METHOD_(ULONG, pfIP6_ND_DestCacheGetNext)(UINTPTR ulWtLstHandle,
        IP6_ND_DESTCACHE_INFO_S *pstDestEntryOut);
    METHOD_(ULONG, pfIP6_ND_DestinationCacheCloseTable)(UINTPTR ulWaitListHandle);

    METHOD_(ULONG, pfIP6_ND_DeleteAllDefRouterEntries)(ULONG ulIfIndex);
    METHOD_(ULONG, pfIP6_ND_DeleteAllIntfPrefixEntries)(ULONG ulIfIndex);
    METHOD_(ULONG, pfIP6_ND_DeleteAllDestCacheEntries)(ULONG ulVrfIndex);
    METHOD_(ULONG, pfIP6_ND_SetDebug) (IP6_ND_CFG_OPT_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetDebug) (ULONG *pulRetVal);

    /* Added by Rajat Phull, Moved from Init V-Table(Level 3) */
    METHOD_(ULONG, pfIP6_ND_ResetIfAllNBEntriesPerVLAN)(ULONG ulIfIndex,
                                                ULONG ulVlanId, UCHAR ucType);

    METHOD_(ULONG, pfIP6_ND_Find_NH_OG_Interface)(IN6ADDR_S *pstDestAddress,
                                                 ULONG *pulIfIndex, IN6ADDR_S *pstNexthopAddr);
    METHOD_(ULONG, pfIP6_ND_DelDynamicNBEntriesByAddr)(ULONG ulIfIndex, 
                                              IN6ADDR_S *pstIn6Addr);
    METHOD_(ULONG, pfIP6_ND_NS_Output_Ext)(ULONG ulIfIndex,
                                            ULONG  ucOptionFlag,
                                            IN6ADDR_S *pstDstAddr,
                                            IN6ADDR_S *pstSrcAddr,
                                            IN6ADDR_S *pstTgtAddr);
    METHOD_(ULONG, pfIP6_ND_SetNDSpecialProxyFlag)(ULONG ulIfIndex,
                                                   UCHAR ucFalg);
    /* Modified by guojianjun178934, 接口状态变化或MAC地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    METHOD_(ULONG, pfIP6_ND_SetNAAttempt) (ULONG ulIfNetIndex, ULONG ulValue, IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetNAAttempt) (ULONG ulIfNetIndex, ULONG *pulRetVal);
    METHOD_(ULONG, pfIP6_ND_SetNAInterval) (ULONG ulIfNetIndex, ULONG ulValue, IP6_ND_SETFLAG_E enFlag);
    METHOD_(ULONG, pfIP6_ND_GetNAInterval) (ULONG ulIfNetIndex, ULONG *pulRetVal);
    /*End of Modified by guojianjun178934, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */

};

/******************************************************************************/

/**********************
   Function VTable
***********************/

/* ND Host Function VTable Structure - Level 1 */
DECLARE_INTERFACE (IIF_IP6_ND_HOST_FUN)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_Lookup) (MBUF_S *pMbuf);
    METHOD_(VOID, pfIP6_ND_UpDownNotify) (VOID *pvIf, ULONG ulCmd,
        CHAR *pcData);
    METHOD_(VOID, pfIP6_ND_PhyUpDownNotify) (VOID *pvIf,ULONG ulCmd,
        CHAR *pcData);
    METHOD_(VOID, pfIP6_ND_LLAddrNotify)(VOID *pvIf, CHAR *pcData);
    METHOD_(VOID, pfIP6_ND_ShutDownNotify)(VOID *pvIf);
    METHOD_(ULONG, pfIP6_ND_GetVlinkStatus)(VOID);
    METHOD_(UCHAR, pfIP6_ND_GetHopLimit) (VOID);
    METHOD_(ULONG, pfIP6_ND_FindNHAndOGIntf)(MBUF_S *pstMBuf,
        const IP6_PKTOPTS_S *pstOpt, ULONG ulZoneId, LONG lFlags);
    METHOD_(VOID, pfIP6_ND_NotifyRouteChange)
        (SFIB6_ROUTEINFO_S *pstRtInfo, ULONG ulEvent);
    METHOD_(ULONG, pfIP6_ND_GetIntfHopLimit)(ULONG ulIfIndex,
        ULONG *pulHopLimit);

    METHOD_(ULONG, pfIP6_ND_FetchNBEntry)(ULONG ulIfnetIndex,
        IN6ADDR_S *pstIPv6Addr, ND_NBENTRY_INFO_S *pstNBInfo);

    METHOD_(ULONG, pfIP6_ND_Start_NUD)(ULONG ulIfnetIndex,
                                            IN6ADDR_S *pstIPv6Addr);
   METHOD_(ULONG, pfIP6_ND_SendAdvertiseNA)(CHAR *szIfName, 
            IN6ADDR_S *pstDstAddr, UCHAR *pucMac);
};


/******************************************************************************/
/************************
   DHCP6C Adatptor VTable
*************************/

/* ND Host DHCP6C Adatpor VTable strucutre */
DECLARE_INTERFACE (IIF_IP6_ND_HOST_DHCP6ADAPT)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIP6_ND_DHCPC6_Adapt_RegCallbackFunc)(
        IP6_ND_DHCP6CADAPT_CALLBACK_S *pstDHCP6AdaptCallBackFunc);
    METHOD_(ULONG, pfIP6_ND_ConfigureStatefulAddress)(
        const IP6_ND_IADESC_S * pstIADesc,
        const IP6_ND_IN6ADDRWITHTIME_S *pstAddrWithTime, ULONG ulAddrCnt,
        IP6_ND_STATEFULCFG_OPTTYPE_E eAddUpdateFlag);
    METHOD_(ULONG, pfIP6_ND_SetOtherConfigParam)(
        IP6_ND_OTHERCFGPARAMS_S * pstOtherCfgParam);
};

/******************************************************************************/

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /*_ND_INC_H */

