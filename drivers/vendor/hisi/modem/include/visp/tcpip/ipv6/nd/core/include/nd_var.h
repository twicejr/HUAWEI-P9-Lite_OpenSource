/******************************************************************************
*
*            Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : IPBIRV100R003.IPv6.E001
*    File Name      : ND_VAR.H
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : contais ND core related variables definations
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef    _ND_VAR_H_
#define    _ND_VAR_H_

#ifdef    __cplusplus
extern "C"{
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/* The following structures are to be defined by other modules */
extern struct IIF_IP6_ICMP6_ComIntCFGVtbl  * g_pstNDICMPCfgVtbl;
extern struct IIF_IP6_ICMP6_ComIntFunVtbl  * g_pstNDICMPFUNVtbl;
extern struct IIF_IP6_ADDR_GENERIC_FUNVtbl * g_pstNDADDRVtbl;
extern struct IIF_IP6_PP_ComIntFunVtbl     * g_pstNDPPVtbl;

/* Level 2 Function VTable of ADDR module */
extern struct IIF_IP6_ADDR_GENERIC_IR_FUNVtbl * g_pstNDADDRIRVtbl;

extern UCHAR   g_ucNDCurHopLimit;
extern ULONG  g_ulNDVlinkEnabled;

extern ULONG g_ulNDDADNum;
extern ULONG g_ulNDDADTimerID;
extern ND_TIMER_S g_stNDDadTimerMsg;
extern ULONG g_ulNDOtherSet;
extern IN6ADDR_S g_stNDIn6Addr_any;
extern IN6ADDR_S g_stNDIn6Addr_allNode;

extern IP6_ND_SH_CALLBACK_FUNC_S g_stNDCallBack;
extern IP6_ND_SGSN_CALLBACK_FUNC_S g_stNDSGSNCallBack;

#if (TCPIP_IN_VRP == VRP_NO)

extern IP6_ND_SOCK_CALLBACK_SET_S g_stNDSocketCallBack;

#endif /* (TCPIP_IN_VRP == VRP_NO)*/

extern IP6_ND_FLOW_CALLBACK_SET_S g_stNDFlowCallback;

extern IP6_ND_MOD_INFO_S g_stNDModInfo;
extern DAD_S *g_pstNDDAD;
extern ULONG g_ulNDEntryToDelete;

extern ULONG g_ulNDTotalNBEntries;

/* PAF variables for NB entries */
extern SPECS_RES_VALUE_S g_stIP6_ND_PAFTotalNBEntries;
extern SPECS_RES_VALUE_S g_stIP6_ND_PAFTotalStatNBEntries;
extern SPECS_RES_VALUE_S g_stIP6_ND_PAFInfNBEntries;
extern SPECS_RES_VALUE_S g_stIP6_ND_PAFInfStatNBEntries;

extern SPECS_RES_VALUE_S g_stIP6_ND_PAFTotalNBEntriesExact;
extern SPECS_RES_VALUE_S g_stIP6_ND_PAFTotalStatNBEntriesExact;
extern SPECS_RES_VALUE_S g_stIP6_ND_PAFInfNBEntriesExact;
extern SPECS_RES_VALUE_S g_stIP6_ND_PAFInfStatNBEntriesExact;

/* PAF variable for Prefix entries */
extern SPECS_RES_VALUE_S g_stIP6_ND_PAFPrefixNum;
extern ULONG g_ulND_MIISupport;

extern ULONG g_ucNDIP6FwdFlag;
extern IComponentFactory m_NDFactory;

/* ND debug flag */
extern ULONG g_ulNDDebugFlag;

extern IIF_IP6_ND_COMMON m_IP6_ND_COMMON;

extern IIF_IP6_ND_INIT m_IP6_ND_INIT;
extern IIF_IP6_ND_CFG  m_IP6_ND_CFG;
extern IIF_IP6_ND_FUN  m_IP6_ND_FUN;

extern IIF_IP6_ND_IR_FUN m_IP6_ND_IR_FUN;

extern IIF_IP6_ND_INT_INIT m_IP6_ND_INT_INIT;
extern IIF_IP6_ND_INT_FUN m_IP6_ND_INT_FUN;
extern IIF_IP6_ND_INT_SSA m_IP6_ND_INT_SSA;

extern IIF_IP6_ND_HOST_INIT m_IP6_ND_HOST_INIT;
extern IIF_IP6_ND_HOST_CFG  m_IP6_ND_HOST_CFG;
extern IIF_IP6_ND_HOST_FUN  m_IP6_ND_HOST_FUN;
extern IIF_IP6_ND_HOST_DHCP6ADAPT m_IP6_ND_HOST_DHCP6CADAPT;

extern IIF_IP6_ND_HOST_IR_FUN m_IP6_ND_HOST_IR_FUN;

extern IIF_IP6_ND_HOST_INT_INIT m_IP6_ND_HOST_INT_INIT;
extern IIF_IP6_ND_HOST_INT_FUN m_IP6_ND_HOST_INT_FUN;
extern IIF_IP6_ND_HOST_INT_SSA m_IP6_ND_HOST_INT_SSA;

extern ULONG g_ulND_Cr_IsIAS;


/* Total number of Static NB entries */
/* Begin :Changes for AC4D05067 by Anand on 20-02-2008*/
extern ULONG g_ulNDTotalStatNBEntries;

/****************************************************************************/
/* ND Host related changes done here */
/****************************************************************************/

/* Global Prefix list radix root node */
extern IP6_ND_PREFIXNODE_S *g_pstNDGblPfx;

/* Global variable for ND Destination Cache */
extern IP6_ND_DESTCACHEGBLPARAM_S *g_pstNDDestCacheGbl;
extern USHORT  g_usMaxNDVrf;

/* Global list contains the interfaces which as Default Router(s) */
extern DLL_S *g_pstNDIntfDefRtrAvail;

/* All Routers multicast address */
extern IN6ADDR_S g_stNDIn6Addr_allRouter;

/* DHCP6 Client Adaptor Call back funtions */
extern IP6_ND_DHCP6CADAPT_CALLBACK_S g_stND_DHCP6CAdaptCallBack;

/* Timer Wheel Call back function */
extern IP6_ND_SH_TWLCALLBACK_FUNC_S g_stND_TWLCallBack;

/* PAF structure */
/* Description: During Client Initialization, PAF structure will be updated
from the PAF file.*/

/* Maximum number of Default Router list entries supported in an interface */
extern SPECS_RES_VALUE_S g_stIP6NDPAF_MaxDefRtrInIntf;

/* Maximum number of Prefix List entries supported in an interface */
extern SPECS_RES_VALUE_S g_stIP6NDPAF_MaxPrefListInf;

/* Maximum number of Destination Cache entries */
extern SPECS_RES_VALUE_S g_stIP6NDPAF_MaxDestCache;

extern ULONG  g_ulNDQueueFullDropRA;

/* Begin :Changes for AC4D05067 by Arvind's Review comment */
/* This Global variable is used to control the Sequence of PAF loading for
NB Cache */
extern ULONG g_ulNDNBPAFLoadSequence;

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
extern ULONG (*g_pfIP6_ND_PPIOperation)(ULONG ulOperType, VOID * pData);
#endif

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

#define MINCONFIGVALUE 3

/* Set MIN-RA more than 0.75*MAX-RA */
/*Change for defect AC4D00938 Desc: Warning message logged is incorrect
 Reason: The macro with 3/4 was giving zero*/
#define MINFACTOR_FOR_MINRA (0.75)

#define IP6_ND_CB_SH_TIMER_CREATE \
            g_stND_TWLCallBack.pfIP6_ND_SH_StartTimer

#define IP6_ND_CB_SH_TIMER_DELETE  \
            g_stND_TWLCallBack.pfIP6_ND_SH_StopTimer

#define IP6_ND_CB_SH_TIMER_GETPARAMS \
            g_stND_TWLCallBack.pfIP6_ND_SH_GetTimerPara

#define IP6_ND_CB_SH_TIMER_GETRESTVAL \
            g_stND_TWLCallBack.pfIP6_ND_SH_GetRestTimeValue

/* Client Adaptor Call back funtion for notifying DHCP6 server availablity */
#define IP6_ND_CB_DHCP6C_ADAPT_NOTIFY_SERVERAVAIL   \
            g_stND_DHCP6CAdaptCallBack.pfIP6_ND_NotifyServerAvailability

/* Client Adaptor Call back funtion for notifying DHCP6 server about the
Non Usability of the address(es) given configuration */
#define IP6_ND_CB_DHCP6C_ADAPT_NOTIFY_ADDR_NOTUSABLE   \
            g_stND_DHCP6CAdaptCallBack.pfIP6_ND_DHCP6CAdaptAddrNotUsable

/* Address Mgmt Event Notification function for Stateless/Stateful Address */
#define IP6_ND_ADDR_HANDLE_HOSTEVENTS    \
            g_pstNDADDRIRVtbl->pfIP6_Addr_HandleHostEvents

/* PAF - Avail Value Macros */
#define IP6ND_PAF_MAX_DEFRTR_PER_INTF       \
            (g_stIP6NDPAF_MaxDefRtrInIntf.ulAvail_Value)

#define IP6ND_PAF_MAX_PREFLIST_PER_INTF     \
            (g_stIP6NDPAF_MaxPrefListInf.ulAvail_Value)

#define IP6ND_PAF_MAX_DESTCACHE_ENTRY       \
            (g_stIP6NDPAF_MaxDestCache.ulAvail_Value)

#define IP6_ND_GET_TIME_BOOTINSEC           \
            g_stNDCallBack.pfIP6_ND_SH_Tm_BootInSec

extern gpfIP6NDSpecialNDProxy g_pfIP6NDSpecialProxy;
extern gpfIP6GetDADProxyIfIndex g_pfIP6GetDADProxyIfIndex;

/*add by wuling 00201943 for IPv6协议DOWN不下发邻居删除PPI 2014-03-25 :S-IP-003-IPv6-008--start*/
extern ULONG g_ulNDNPDelNBSwitch;
/*add by wuling 00201943 for IPv6协议DOWN不下发邻居删除PPI 2014-03-25 :S-IP-003-IPv6-008--end*/

/* Added by fengjing209023 for DTS2014061301920 BALONG DAD优化需求，打开后不做DAD和initial delay */
extern ULONG g_ulNDNODADSwitch;

/* 复用地址模块的OPEN,CLOSE函数 */
#define IP6_IFND_OPEN IP6_Addr_OpenTable
#define IP6_IFND_CLOSE IP6_Addr_CloseTable
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _ND_VAR_H_ */

