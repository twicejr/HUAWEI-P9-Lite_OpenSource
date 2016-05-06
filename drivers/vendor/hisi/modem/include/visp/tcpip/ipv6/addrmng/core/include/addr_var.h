
#ifndef _ADDR_VAR_H_
#define _ADDR_VAR_H_


#ifdef __cplusplus
extern "C" {
#endif

/* AC4D01223 - Added by Prabhu H (71185) */
#include "ipbircommon/ipbirmap/ipbir_others.h"
#include "ipv6/addrmng/core/include/addr_ha.h"

/* Contains set of required pointer to functions of ND module, which will be
   accessed by ADDR */
extern struct IIF_IP6_ND_GENERIC_FUNVtbl       *g_pstADDRNDVtbl;
extern struct IIF_IP6_ND_GENERIC_IR_FUNVtbl    *g_pstADDRNDIRVtbl;

/* Start: RFC4443 compliance changes */
/* Vtable to access ICMP functions by ADDR */
extern struct IIF_IP6_ICMP6_IR_FUNVtbl   *g_pstADDRICMPVtbl;

/* End: RFC4443 compliance changes */

/* Contains set of callback pointer to functions of SRM module, which will be
   accessed by ADDR */
extern IP6_ADDR_SRM_CALLBACK_FUNC_S g_stIP6ADDR_SRM_CallBack;

/*  ADDR module information global structure */
extern IP6_ADDR_MOD_INFO_S    g_stADDRModInfo;

extern IP6_Addr_VPN *g_pstAddrVpn;
extern USHORT  g_usMaxAddrVrf;

/* Global pointer to Link local Ipv6 Interface address */
extern IP6IFADDR_S      *g_pstLinkLocalIpIfAddr;

#define IP6_ADDR_RPC_SEND     0
#define IP6_ADDR_RPC_NOSEND   1

/* Global variable to notify link layer interface ID change */
extern ULONG g_ulNotifyLinkLayerFlag;

/* Global variable to ON/OFF logging mechanism in IPv6 module */
extern ULONG g_ulIP6LoggerSwitch;

/* This parameter will be set Software debug command
   to control the output text at IP6 level */
extern ULONG g_ulIP6LogLevel;
extern ULONG g_ulAddrHACoreState;

/* Set of callback pointer to functions provided by ADDR Shell */
extern IP6_ADDR_SH_CALLBACK_FUNC_S  g_stIP6ADDR_SH_CallBack;

/* Begin   : Defect ID: D01006, Modifier:Rajesh, Date:2004/9/13
   Reason  : Initial, Max Mtu change for Pos, GE interfaces*/
/* Global variables store MTU change for POS and GE interfaces */
extern SPECS_RES_VALUE_S  g_stIP6ADDR_PAF_MtuPosVal;
extern SPECS_RES_VALUE_S  g_stIP6ADDR_PAF_MtuGEVal;


extern SPECS_RES_VALUE_S  g_stIP6ADDR_PAF_AddrNum;


extern SPECS_FUN_VALUE_S  g_stIP6ADDR_PAF_Fun_AutoConfigSwitch;

extern IComponentFactory m_ADDRFactory;

extern IIF_IP6_ADDR_INIT            m_IP6_ADDR_INIT;
extern IIF_IP6_ADDR_CFG             m_IP6_ADDR_CFG;
extern IIF_IP6_ADDR_FUN             m_IP6_ADDR_FUN;
extern IIF_IP6_ADDR_IR_FUN          m_IP6_ADDR_IR_FUN;
extern IIF_IP6_ADDR_INT_INIT        m_IP6_ADDR_INT_INIT;
extern IIF_IP6_ADDR_INT_FUN         m_IP6_ADDR_INT_FUN;
extern IIF_IP6_ADDR_INT_HSB         m_IP6_ADDR_INT_HSB;
extern IIF_IP6_ADDR_INT_SSA         m_IP6_ADDR_INT_SSA;

extern IIF_IP6_ADDR_HOST_INIT       m_IP6_ADDR_HOST_INIT;
extern IIF_IP6_ADDR_HOST_CFG        m_IP6_ADDR_HOST_CFG;
extern IIF_IP6_ADDR_HOST_FUN        m_IP6_ADDR_HOST_FUN;
extern IIF_IP6_ADDR_HOST_IR_FUN     m_IP6_ADDR_HOST_IR_FUN;
extern IIF_IP6_ADDR_HOST_INT_INIT   m_IP6_ADDR_HOST_INT_INIT;
extern IIF_IP6_ADDR_HOST_INT_FUN    m_IP6_ADDR_HOST_INT_FUN;
extern IIF_IP6_ADDR_HOST_INT_SSA    m_IP6_ADDR_HOST_INT_SSA;

/*   Get API provided to PMTU to fetch MAX MTU value from ADDR */
extern ULONG g_ulIP6ADDR_MaxMtu;

extern ULONG VOS_WaitListDelFromList(ULONG ulMainType, VOID *pDataToDel);



extern IP6_ADDR_TIMER_CALLBACK_FUNC_S g_stIP6ADDR_Timer_CallBack;

extern IP6_ADDR_REGISTERED_APP_INFO_S g_stRegIpv6AppInfo;



extern ULONG g_ulADDR_Cr_IsIAS;


#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
extern ULONG (*g_pfIP6_ADDR_PPIOperation)(ULONG ulOperType, VOID * pData);
extern IP6_ADDR_DADRESULT_NOTIFY_FUNC_S g_stDADNotifyCallback;
#endif


extern IP6_ADDR_DADRESULT_NOTIFY_FUNC_S *g_pstDADNotifyCallback;

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _ADDR_VAR_H_ */

