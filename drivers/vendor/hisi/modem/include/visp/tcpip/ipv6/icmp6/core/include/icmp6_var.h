/*******************************************************************************
*                          icmp6_var.h
*  Project Code    : VRP3.0
*  Author          : Mayun  / Mahaveer Jain
*  Create Date     : 2002-8-20
*  Version         :
*  Description     : 本文件是icmp6.c文件
*  Others          :
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
* 2006-09-14   Alok             Updated for 14 Fly-Check rules adherence
*                               for IPBIRV1R2.IPv6
*-------------------------------------------------------------------------------
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.
*                      ALL RIGHTS RESERVED
*******************************************************************************/
#ifndef _ICMP6_VAR_H_
#define _ICMP6_VAR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* Added by Anand - V1R7 Workspace Integration */
#define ICMP6_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))


extern ULONG g_ulMidIcmp6;
extern ULONG g_ulICMP6MaxLinkHdr;

/* Currently configured interval value */
extern ULONG g_ulIcmp6_ErrorRate_Interval;

extern ULONG g_ulIcmp6_TooBigErrorRate_Interval;

/* Currently configured tokens count value */
extern ULONG g_ulIcmp6_CurErrorRate_Tockens;
extern ULONG g_ulIcmp6_TooBigErrorRate_Tockens;

/* Current counter for tokens */
extern ULONG g_ulIcmp6_TooBigErrorRate_CurrentCnt;

/* Start: RFC4443 compliance changes */
/* Global rate at which tokens are released */
extern ULONG g_ulIcmp6_FillErrorRate;

/* Global to store total configured tokens */
extern ULONG g_ulIcmp6_ErrorRate_TotalTokens;

/* End: RFC4443 compliance changes */

extern ICMP6STAT_S g_stIcmp6Stat;

extern IP6_ICMP6_SH_CALLBACK_FUNC_S     g_stICMP6CallbackFun;
extern IP6_ICMP6_MOD_INFO_S             g_stICMP6ModInfo;
extern SOSB6_CALLBACUP_SET_S            g_stSOSB6Callback;
extern IN6PCB_CALLBACUP_SET_S           g_stIN6PCBCallBack;

extern struct IIF_IP6_ADDR_GENERIC_FUNVtbl          *g_pstICMP6ADDRVtbl;
extern struct IIF_IP6_RIP6_FUNVtbl            *g_pstICMP6RIPVtbl;
extern struct IIF_IP6_PMTU_IR_FUNVtbl               *g_pstICMP6_PMTU_IR_FUNVtbl;
extern struct IIF_IP6_ND_GENERIC_FUNVtbl            *g_pstICMP6NDVtbl;
extern struct IIF_IP6_ND_GENERIC_IR_FUNVtbl         *g_pstICMP6NDIRVtbl;

extern IIF_IP6_ICMP6_INIT           g_IP6_ICMP6_INIT;
extern IIF_IP6_ICMP6_CFG            g_IP6_ICMP6_CFG;
extern IIF_IP6_ICMP6_FUN            g_IP6_ICMP6_FUN;
extern IIF_IP6_ICMP6_INT_INIT       g_IP6_ICMP6_INT_INIT;
extern IIF_IP6_ICMP6_INT_SSA        g_IP6_ICMP6_INT_SSA;
extern IIF_IP6_ICMP6_IR_FUN         g_IP6_ICMP6_IR_FUN;

extern IComponentFactory m_ICMP6Factory;
extern UCHAR *g_aszIP6Icmp6DbgStrInfo[];
extern ULONG g_ulIcmp6_TooBigTimerID;
extern ULONG g_ulIcmp6_ErrorRateLimitTmrID;

#if (IPBIR_IPV6_NP_SUPPORT  == VRP_YES)
extern ULONG (*g_pfIP6_ICMP6_PPIOperation)(ULONG ulOperType, VOID * pData);
#endif

extern ICMP6_EXT_CALLBACK_S g_stIP6_ICMP6_Flow_Callback;
extern ICMP6_EXT_CALLBACK_S *g_pstIP6_ICMP6_Flow_Callback;

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ICMP6_VAR_H_ */
