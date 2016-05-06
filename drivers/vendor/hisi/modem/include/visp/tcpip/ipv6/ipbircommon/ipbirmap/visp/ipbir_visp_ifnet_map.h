/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_ifnet_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To define VISP specific IFNET macros
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for defining VISP related IFNET macros
************************************************************************/

#ifndef _IPB_IR_VISP_IFNET_MAPP_H_
#define _IPB_IR_VISP_IFNET_MAPP_H_

#ifdef    __cplusplus
extern "C"{
#endif



#include "common/visp/VISP_IR_IFNET.h"  /*Common headfile visp provided*/

const CHAR* VRPAdapt_IF_GetIfNamebyIf(VOID *pstIfNet);
ULONG VRPAdapt_IF_GetIndexByIf(VOID* pstIfNet);
ULONG VRPAdapt_IF_GetFlagsbyIf(VOID *pstIfNet);
ULONG VRPAdapt_IF_GetLineProtocolbyIf(VOID *pstIf);
ULONG VRPAdapt_IF_GetIfBaud(VOID *pstIfNet);

/* Added by Saravanya For ND-Host,20-11-2007, to remove L4 Warning */
ULONG  VRPAdapt_IF_GetPhyTypebyIf(VOID *pstIf);
ULONG VRPAdapt_IF_IsTrunkPort(VOID* pIf);
ULONG VRPAdapt_IF_IsPhyStatusUpbyIf(VOID *pstIfNet);
ULONG  VRPAdapt_IF_GetPortTypebyIf(VOID *pstIf);
ULONG VRPAdapt_IF_IsShutdown(VOID *pstIfNet);
ULONG VRPAdapt_IF_GetIfBaudHigh(VOID *pstIfNet);
ULONG VRPAdapt_IF_IsIfLine6StatusUpbyIf(VOID *pstIfNet);
ULONG VRPAdapt_IF_GetSubIndexbyIf(VOID *pstIfNet);
ULONG VRPAdapt_IF_IsInvisible(VOID *pstIfNet);
ULONG VRPAdapt_IF_IsSpoofing(VOID *pstIfNet);
ULONG VRPAdapt_IF_GetLoopBackFlagbyIf(VOID *pstIfNet);
ULONG VRPAdapt_IF_GetSlotByIndex(ULONG ulIfIndex);
VOID * VRPAdapt_IF_WaitListGet ( VOID *pParam, VOID **pNewParam );
VOID * VRPAdapt_IF_GetIfByIndex(ULONG ulIfIndex);
VOID* VRPAdapt_IF_GetConfigHead(VOID);
VOID* VRPAdapt_IF_SearchIfFromChain( VOID * pstIfNet, ULONG ulSearch );
ULONG VRPAdapt_IF_BoardIsUp ( ULONG ulSlot );
ULONG VRPAdapt_PRODUCT_GetMainboardId(VOID);
ULONG VRPAdapt_PRODUCT_GetSelfBoardId(VOID);
VOID* VRPAdapt_IF_GetIfbyFullName (CHAR * pszFullName);
ULONG  VRPAdapt_VLINK6_IoCtl(VOID *pVLinkStatus, VOID *pCB);
VOID* VRPAdapt_VLINK6_GetCB(ULONG ulVlinkIndex);
ULONG VRPAdapt_IF_GetFirstIfIndex(ULONG * pIndex);
ULONG VRPAdapt_IF_LinkDownIOCtl ( VOID * , ULONG  ,CHAR * );
ULONG VRPAdapt_IF_PhyIoctl(VOID * , UINTPTR , ULONG , CHAR * );
UINTPTR VRPAdapt_IF_GetPhyLink(VOID *pstIf);
CHAR * VRPAdapt_IF_GetIfDescripbyIf(VOID *pstIfNet);
VOID* VRPAdapt_IF_GetIPv6CtlBLK(VOID *pstIfNet);
ULONG VRPAdapt_IF_SetIPv6CtlBLK(VOID *pstIfNet, VOID *pstIpv6CtlBlk);
ULONG VRPAdapt_IF_IsInNULL(VOID *pstIfNet);
ULONG VRPAdapt_IF_IfNetIsInloopback(VOID *pstIfNet);
ULONG VRPAdapt_IF_ISLOOPBACK(ULONG ulIfIndex);
ULONG VRPAdapt_IF_GETSLOTBYPTR(ULONG ulIfIndex);
CHAR * VRPAdapt_IF_Get_Msg_Router_En(ULONG ulType);

/* Begin : Changes for AC4D05168 by Ahmed on 20-02-2008*/
/* support Ethernet and P2P for NDHost VISP */
ULONG VRPAdapt_IF_IsIPv6Support(VOID* pvIf);
/* End : Changes for AC4D05168 by Ahmed on 20-02-2008*/

BOOL_T VRPAdapt_IF_IsValidIfIndex(ULONG ulIfIndex);
ULONG VRPAdapt_IF_GetPortTypebyIndex(ULONG ulIfIndex);
ULONG VRPAdapt_IF_GetIPSecSaEntryHead(ULONG ulIfIndex, VOID * * ppstHeadTemp);
ULONG VRPAdapt_IF_SetIPSecSaEntryHead(ULONG ulIfIndex, ULONG ulTdbEntryHead);
CHAR* VRPAdapt_IF_GetIfNamebyIndex(ULONG ulIfIndex);
ULONG VRPAdapt_IF_GetMTUbyIndex(ULONG ulIfIndex);
ULONG VRPAdapt_IF_RegisterNotifyFn(ULONG ulType, ULONG ulPriority,
                                                            VOID *pfNotifyFn);
ULONG VRPAdapt_IF_UnRegisterNotifyFn(ULONG ulType, VOID* pfNotifyFn);

ULONG VRPAdapt_IF_GetIfIndexbyName(CHAR *pszFullName);
ULONG VRPAdapt_IF_GetPhyTypebyIndex(ULONG ulIfIndex);

ULONG VRPAdapt_IF_MtuNotifyRouter6(VOID *pvIf);

ULONG VRPAdapt_IF_GetVrf6ByIfIndex(ULONG ulIfIndex);
ULONG VRPAdapt_IF_GetFirstSubIfIndexbyMainIndex(ULONG ulMainIndex,ULONG* ulFirstSubIndex);
ULONG  VRPAdapt_IF_GetNextSubIfIndexbyPreSubIndex(ULONG ulPreIndex,ULONG* ulNextIndex);
ULONG VRPAdapt_IF_GetLinkMtu(ULONG ulIfIndex, ULONG *pulMtu);
ULONG VRPAdapt_IF_IslocalAddr(VOID *pstAddr6,ULONG ulIfIndex);
ULONG VRPAdapt_IF_GetMatchIndex(ULONG *pulIndex);
ULONG VRPAdapt_IF_SelectSourceAddr(VOID *pstIp6DestAddr,VOID *pstSrcAddr,ULONG ulIndex);


/********************************************************************
 *
 *                        IFNET Adapter Function Mapping (2006-12-05)
 *
 ********************************************************************/
#define IPB_IR_IF_SELECTSRCARRD(pstIp6DestAddr,pstSrcAddr,pulIndex) \
                VRPAdapt_IF_SelectSourceAddr(pstIp6DestAddr,pstSrcAddr,pulIndex)

#define IPB_IR_IF_GETMATCHINDEX(pulIndex) \
                VRPAdapt_IF_GetMatchIndex(pulIndex)
            
#define IPB_IR_IF_ISLOCALADDR(pstAddr6Local,ulIfIndex) \
                VRPAdapt_IF_IslocalAddr(pstAddr6Local,ulIfIndex)
        
#define IPB_IR_IF_GETLINKMTU(ulIfIndex,pulMtu) \
            VRPAdapt_IF_GetLinkMtu(ulIfIndex,pulMtu)

#define IPB_IR_IF_GETIFNAMEBYIF(pstIf) \
    VRPAdapt_IF_GetIfNamebyIf(pstIf)

#define IPB_IR_IF_GETINDEXBYIF(pstIf) \
    VRPAdapt_IF_GetIndexByIf(pstIf)

#define IPB_IR_IF_GETFLAGSBYIF(pstIf) \
    VRPAdapt_IF_GetFlagsbyIf(pstIf)

#define IPB_IR_IF_GETLINEPROTOCOLBYIF(pstIf) \
    VRPAdapt_IF_GetLineProtocolbyIf(pstIf)

#define IPB_IR_IF_GETIFBAUD(pstIf) \
    VRPAdapt_IF_GetIfBaud(pstIf)

#define IPB_IR_IF_GETPHYTYPEBYIF(pstIf) \
    VRPAdapt_IF_GetPhyTypebyIf(pstIf)

#define IPB_IR_IF_ISPHYSTATUSUP(pstIf) \
    VRPAdapt_IF_IsPhyStatusUpbyIf(pstIf)

#define IPB_IR_IF_GETPORTTYPE(pstIf) \
    VRPAdapt_IF_GetPortTypebyIf(pstIf)

/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_IF_ISSHUTDOWN(pstIf) \
    VRPAdapt_IF_IsShutdown(pstIf)

#define IPB_IR_IF_GETIFBAUDHIGH(pstIf) \
    VRPAdapt_IF_GetIfBaudHigh(pstIf)

#define IPB_IR_IF_ISLINE6STATUSUP(pstIf) \
    VRPAdapt_IF_IsIfLine6StatusUpbyIf(pstIf)

#define IPB_IR_IF_GETSUBINDEXBYIF(pstIf) \
    VRPAdapt_IF_GetSubIndexbyIf(pstIf)

/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_IF_ISINVISIBLESET(pstIf) \
    VRPAdapt_IF_IsInvisible(pstIf)

/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_IF_ISSPOOFINGSET(pstIf) \
    VRPAdapt_IF_IsSpoofing(pstIf)

#define IPB_IR_IF_GETLOOPBACKFLAG(pstIf) \
    VRPAdapt_IF_GetLoopBackFlagbyIf(pstIf)


#define IPB_IR_IF_GETSLOTBYINDEX(ulIfIndex) \
    VRPAdapt_IF_GetSlotByIndex(ulIfIndex)

/* Prabhu add */
#define IPB_IR_IF_WAITLISTGET_FUNC_PTR \
    VRPAdapt_IF_WaitListGet
/* Prabhu end */

#define IPB_IR_IF_GETIFBYINDEX(ulIfIndex) \
    VRPAdapt_IF_GetIfByIndex(ulIfIndex)

/* Merge By Bharath */
#define IPB_IR_IF_GETCONFIGHEAD() \
    VRPAdapt_IF_GetConfigHead()

#define IPB_IR_IF_SEARCHIFFROMCHAIN(pstIfnet, ulFlag)\
    VRPAdapt_IF_SearchIfFromChain( pstIfnet, ulFlag )

#define IPB_IR_IF_BOARDISUP(ulSlot) \
    VRPAdapt_IF_BoardIsUp(ulSlot)

/* Merge By Bharath */
#define IPB_IR_IF_GETMAINBOARDID() \
    VRPAdapt_PRODUCT_GetMainboardId()

// Not used in ADDR
/* Merge By Bharath */
#define IPB_IR_IF_GETSELFBOARDID() \
    VRPAdapt_PRODUCT_GetSelfBoardId()

#define IPB_IR_IF_GETIFBYFULLNAME(pszSectionName) \
    VRPAdapt_IF_GetIfbyFullName(pszSectionName)

// Left Over To Discuss
/*#define IPB_IR_IF_HOOKFORQUERY(ulIposIfSupportFlag, ulIposIfFlagIndex, ulIposFuncFlag, pHelpVec, szType, szInput ) \
    IF_HOOKFORQUERY( ulIposIfSupportFlag,  ulIposIfFlagIndex, ulIposFuncFlag, pHelpVec, szType , szInput)
*/

/* Merge By Bharath */
#define IPB_IR_VLINK6_IOCTL(pVLinkStatus, pCB) \
    VRPAdapt_VLINK6_IoCtl(pVLinkStatus, pCB)

#define IPB_IR_VLINK6_GETCB(ulVlinkIndex) \
    VRPAdapt_VLINK6_GetCB(ulVlinkIndex)
/* Merge By Bharath */

/*#define IPB_IR_IF_GETLINKTYPE(ulIpv6IfEntry) \
    VRPAdapt_IF_GETLINKTYPE(ulIpv6IfEntry)*/

#define IPB_IR_IF_GETFIRSTIFINDEX(ulIfIndex) \
    VRPAdapt_IF_GetFirstIfIndex(ulIfIndex)

/****************************************************************************
IFNET structure's function pointer members
*********************************************************************/

#define IPB_IR_IF_PFLINKDOWNIOCtl(pstIf,ulIsChange,pszChar) \
    VRPAdapt_IF_LinkDownIOCtl( pstIf, ulIsChange , pszChar)

#define IPB_IR_IF_PHYIOCTL(pstif, ulPhyLink, enMulti, szDstEn) \
    VRPAdapt_IF_PhyIoctl(pstif, ulPhyLink, enMulti, szDstEn)

#define IPB_IR_IF_GETPHYLINK(pstIf) \
    VRPAdapt_IF_GetPhyLink(pstIf)

#define IPB_IR_IF_DESCRIPTION(pstIfNet) \
    VRPAdapt_IF_GetIfDescripbyIf(pstIfNet)


/****************************************************************************
IFNET macros and enums
*********************************************************************/
#define IPB_IR_IF_GETIPV6CTLBLK(pstIfNet) \
    VRPAdapt_IF_GetIPv6CtlBLK(pstIfNet)

#define IPB_IR_IF_SETIPv6CTLBLK(pstIf , pstIpv6CtlBlk)  \
    VRPAdapt_IF_SetIPv6CtlBLK(pstIf, pstIpv6CtlBlk)

#define IPB_IR_IF_ISNULL(pstLoopIf) \
    VRPAdapt_IF_IsInNULL(pstLoopIf)

#define IPB_IR_IF_IS_INLOOPBACK(pstIfNet) \
    VRPAdapt_IF_IfNetIsInloopback(pstIfNet)

#define IPB_IR_IF_IS_LOOPBACK(uIfIndex) \
    VRPAdapt_IF_ISLOOPBACK(uIfIndex)

/* Trunk interface AT defect VISP */
#define IPB_IR_IF_IS_ETHER_TRUNK(pstIf) \
    VRPAdapt_IF_IsTrunkPort(pstIf)
/* Trunk interface AT defect VISP */

/* Begin : Changes for AC4D05168 by Ahmed on 20-02-2008*/
/* Only to support Ethernet and P2P for NDHost VISP */
#define IPB_IR_IF_IS_IPv6_SUPPORT(pstIf) \
    VRPAdapt_IF_IsIPv6Support(pstIf)
/* End : Changes for AC4D05168 by Ahmed on 20-02-2008*/

#define IPB_IR_IF_GETSLOTBYPTR(pstIfNet) \
    VRPAdapt_IF_GETSLOTBYPTR(IPB_IR_IF_GETINDEXBYIF(pstIfNet))

/*VISP will provide self-solution headfiles so we no need to
   translate enum between ipos and visp, directly use the
   defination in those headfiles visp provided, 2005-12-02*/
#define IPB_IR_IF_MAP_CMD(enumCmd)  enumCmd
#define IPB_IR_IF_GET_HELPMSG_EN(enHelp)  \
    VRPAdapt_IF_Get_Msg_Router_En(enHelp)

/*End of modification by wan for VISP headfile adapt*/


#if 1 /* Commented by Arvind for V1R3 VISP WorkSpace Unification */
#define IPB_IR_IF_ISVALIDIFINDEX(ulIfIndex) \
    VRPAdapt_IF_IsValidIfIndex(ulIfIndex)

#define IPB_IR_IF_GETIFNAMEBYINDEX(ulIfIndex)    \
    VRPAdapt_IF_GetIfNamebyIndex(ulIfIndex)

#define IPB_IR_IF_GETIFINDEXBYNAME(pszFullName) \
    VRPAdapt_IF_GetIfIndexbyName(pszFullName)
#endif

#define IPB_IR_IF_REGISTER_NOTIFY_FUNC(ulType, ulPriority, pfNotifyFn) \
    VRPAdapt_IF_RegisterNotifyFn(ulType, ulPriority, pfNotifyFn)

#define IPB_IR_IF_UNREGISTER_NOTIFY_FUNC(ulType, pfNotifyFn) \
    VRPAdapt_IF_UnRegisterNotifyFn(ulType, pfNotifyFn)




/********************************************************************
 *
 *                        IFNET Type and Struture Mapping (2006-12-05)
 *
 ********************************************************************/
#define IPB_IR_IF_SEARCH_ALL \
    IF_SEARCH_ALL

#define IPB_IR_IF_RTATTR_BROADCAST  \
    IF_RTATTR_BROADCAST

// Not used in ADDR
#define IPB_IR_IF_RTATTR_POINT2POINT \
    IF_RTATTR_POINT2POINT

//Not used in ADDR
#define IPB_IR_IF_RTATTR_LOOPBACK \
    IF_RTATTR_LOOPBACK

#define IPB_IR_IF_RTATTR_NBMA \
    IF_RTATTR_NBMA

#define IPB_IR_SIOCIFDOWN \
    SIOCIFDOWN

#define IPB_IR_SIOCIFUP \
    SIOCIFUP


#define IPB_IR_ISLUP \
    ISLUP

#define IPB_IR_ISLDOWN \
    ISLDOWN

 #define IPB_IR_IF_STATUS_PROT_UP \
    IF_STATUS_PROT_UP

 #define  IPB_IR_IF_STATUS_LOW_DOWN \
    IF_STATUS_LOW_DOWN


#define IPB_IR_IF_STATUS_PROT_DOWN \
    IF_STATUS_PROT_DOWN

 #define IPB_IR_SIOCLINKSTATE \
    SIOCLINKSTATE

#define IPB_IR_SIOC6LINKSTATE \
    SIOC6LINKSTATE

#define IPB_IR_MAX_IF_NAME_LENGTH \
    MAX_IF_NAME_LENGTH


/* Following should have their eqivalents in IPOS common Adapter */



#define IPB_IR_RTM_DEL RTM_DEL

/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_IF_DOWN IF_DOWN

#define IPB_IR_RTM_CREATE RTM_CREATE

#define IPB_IR_RTM_DELADDRESS RTM_DELADDRESS

/*  Rajat Add*/
/*#define IPB_IR_RTM_INOUTLOOPBACK IPOS_RTM_INOUTLOOPBACK
#define IPB_IR_IF_SETLOOP IF_SETLOOP*/
#define IPB_IR_IF_DOWN IF_DOWN
#define IPB_IR_PHY_JOINMULTI PHY_JOINMULTI
#define IPB_IR_PHY_LEAVEMULTI PHY_LEAVEMULTI

/*  Rajat End*/


/* Prabhu add */
#define IPB_IR_SIOCNDDAD SIOCNDDAD
#define IPB_IR_SIOCLINKSTATE SIOCLINKSTATE
#define IPB_IR_SIOCDIP6LINKLOCALADDR SIOCDIP6LINKLOCALADDR
#define IPB_IR_SIOCGIP6LINKLOCALADDR SIOCGIP6LINKLOCALADDR
#define IPB_IR_SIOCSIP6INTERFACEID SIOCSIP6INTERFACEID
#define IPB_IR_SIOC6GETINTERFACEID SIOC6GETINTERFACEID
#define IPB_IR_SIOCGETMAC SIOCGETMAC
#define IPB_IR_SIOCAIP6LINKLOCALADDR SIOCAIP6LINKLOCALADDR


#define IPB_IR_HELP_LINESPOOFING Help_LineSpoofing
#define IPB_IR_HELP_LINEUP Help_LineUp
#define IPB_IR_HELP_LINEDOWN Help_LineDown
#define IPB_IR_HELP_INTERFACEADMINDOWN Help_InterfaceAdminDown
#define IPB_IR_HELP_INTERFACEDOWN Help_InterfaceDown
#define IPB_IR_HELP_INTERFACEUP Help_InterfaceUp


#define IPB_IR_IFNET_HOT_MSG_SLOT_INSERT IFNET_HOT_MSG_SLOT_INSERT
#define IPB_IR_IFNET_HOT_MSG_SLOT_REMOVE IFNET_HOT_MSG_SLOT_REMOVE
#define IPB_IR_IFNET_HOT_MSG_INTF_INSERT IFNET_HOT_MSG_INTF_INSERT
#define IPB_IR_IFNET_HOT_MSG_INTF_REMOVE IFNET_HOT_MSG_INTF_REMOVE
/*  Prabhu end */

/*#define IPB_IR_IF_LINKLINK(pstIf)   \
    VRPAdapt_IF_GetLinkLink(pstIf)*/
//(This is for  pstIf->if_ulLinkLink )

/*#define IPB_IR_IF_ANALYSENAME( stVTIfName , szIfName ) */
//(This is for (VOID)IF_AnalyseIfName(&stVTIfName,pIf->if_szIfName);)


/* #define IPB_IR_IF_MAX_MPCHANNEL \ */
/* Modified by Saravanya71677 for ND-Host */
#define IPB_IR_IF_SEARCH_CONFIG_CHAIN IF_SEARCH_CONFIG_CHAIN


/* Reason : Compilation change   Mod:Bharath */

#define IPB_IR_MAX_INTERFACE_NAME_LEN \
    IF_MAX_INTERFACE_NAME_LEN

#define IPB_IR_PORT_GE  \
    PORT_GE
/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_PORT_POS \
    PORT_POS
/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_PORT_TUNNEL \
    PORT_TUNNEL
/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_PORT_DPT \
    PORT_DPT

#define IPB_IR_PORT_TEMPLATE \
    PORT_TEMPLATE

#define IPB_IR_PORT_ATM \
    PORT_ATM

/* Added for VLAN & VLANIF framework by karthik 70713 in Nov 2009 */

#define IPB_IR_PORT_VLAN \
    PORT_VLAN


/* Karthik Change Reason: If Inloopback interface should not do replace
build run Incorrect FLAG was being mapped*/
#define IPB_IR_PHY_LOOP \
    PHY_LOOP

#define IPB_IR_PHY_POS \
    PHY_POS

#define IPB_IR_PHY_GE \
    PHY_GE

#define IPB_IR_PHY_TUNNEL \
    PHY_TUNNEL

#define IPB_IR_PHY_LOOPBACK \
    PHY_LOOPBACK

#define IPB_IR_PHY_ETHERNET \
    PHY_ETHERNET

#define IPB_IR_PHY_SYNC \
    PHY_SYNC

/* Merge By Bharath */
#define IPB_IR_LINE_ETHERNET \
    LINE_ETHERNET

#define IPB_IR_LINE_GE \
    LINE_GE
#define IPB_IR_IF_FUNC_FULLNAME \
    IF_FUNC_FULLNAME

#define IPB_IR_IF_FUNC_NUMBER_CHECK \
    IF_FUNC_NUMBER_CHECK

#define IPB_IR_IF_FUNC_TYPE_HELP \
    IF_FUNC_TYPE_HELP

#define IPB_IR_LINE_FR \
    LINE_FR

#define IPB_IR_LINE_ATM \
    LINE_ATM

/* Reason : ADDIPOS        Mod:Bharath */
#define IPB_IR_IFVLINKENTRY6_S \
    IFVLINKENTRY6_S

/*#define IPB_IR_IF_GETNEXTIFINDEX(ulIfIndex,pulIpv6IfEntry) \
    IF_GETNEXTIFINDEX(ulIfIndex,pulIpv6IfEntry)*/


/* Modified by Saravanya71677 for ND-Host */
/* #define IPB_IR_IF_WAITLIST_PARAM IPOS_IF_WAITLIST_PARAM */
#define IPB_IR_IF_WAITLIST_PARAM IF_WAITLIST_PARAM

typedef struct tagIp6AdpFilter
{
    ULONG ulIfIndex;
}IP6ADP_FILTER_S;

typedef struct tagIpAddr6WaitlistPara
{
    IPB_IR_IF_WAITLIST_PARAM stIfWaitlstPara;
    IP6ADP_FILTER_S stFilter;
    UINT32 u32GetNextFlag;
}IPADDR6_WAITLIST_PARA_S;

typedef struct tagIfNDWaitlistPara
{
    IPB_IR_IF_WAITLIST_PARAM stIfWaitlstPara;
    IP6ADP_FILTER_S stFilter;
    UINT32 u32GetNextFlag;
}IFND_WAITLIST_PARA_S;

/* Rajat Add */
#define IPB_IR_IF_ISDELETEOVER(pstIf) \
    VOS_OK

/*  Changed for IPSec as reuired 1 board to represent main board*/
#define IPB_IR_GET_MAX_BOARD_NUM()\
    VOS_ERR

#define IPB_IR_IF_GETSLOTBYIDX(ulIfIndex)       \
        VRPAdapt_IF_GETSLOTBYPTR(ulIfIndex)

#define IPB_IR_IF_GET_PORTTYPEBYIDX(ulIfIndex)   \
        VRPAdapt_IF_GetPortTypebyIndex(ulIfIndex)

#define IPB_IR_IF_GET_IPSECSAENTRYHEAD(ulIfIndex,ppstHeadTemp) \
        VRPAdapt_IF_GetIPSecSaEntryHead(ulIfIndex,ppstHeadTemp)

#define IPB_IR_IF_SET_IPSECSAENTRYHEAD(ulIfIndex,ulTdbEntryHead) \
        VRPAdapt_IF_SetIPSecSaEntryHead(ulIfIndex,ulTdbEntryHead)


#define IPB_IR_IF_GETMTUBYINDEX(ulIfIndex) \
        VRPAdapt_IF_GetMTUbyIndex(ulIfIndex)


/* Added by Suraj for Notification of MTU to IFnet for VISP only */
#define IPB_IR_IF_NOTIFYMTU(pvIf) \
        VRPAdapt_IF_MtuNotifyRouter6(pvIf)


#define IPB_IR_IF_GETVRF6BYINDEX(ulIfIndex) \
    VRPAdapt_IF_GetVrf6ByIfIndex(ulIfIndex)

#define IPB_IR_IF_GETFIRSTSUBIFINDEXBYMAININDEX(ulMainIndex, ulFirstSubIndex) \
    VRPAdapt_IF_GetFirstSubIfIndexbyMainIndex(ulMainIndex, ulFirstSubIndex)

#define IPB_IR_IF_GETNEXTSUBIFINDEXBYPRESUBINDEX(ulPreIndex, ulNextIndex) \
    VRPAdapt_IF_GetNextSubIfIndexbyPreSubIndex(ulPreIndex, ulNextIndex)
    

#ifdef __cplusplus
}
#endif        /* end of __cplusplus */


#endif  /* end of _IPB_IR_VISP_IFNET_MAPP_H_ */


