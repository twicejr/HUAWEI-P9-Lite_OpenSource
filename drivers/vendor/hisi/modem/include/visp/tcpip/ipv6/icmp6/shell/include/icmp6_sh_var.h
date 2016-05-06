/********************************************************************
*                          icmp6_sh_var.h
*  Project Code    : VRP3.0
*  Author          : Mayun  / Mahaveer Jain
*  Create Date     : 2002-8-20
*  Version         :
*  Description     : 本文件是icmp6.c文件
*  Others          :
*---------------------------------------------------------------------
*  Modification History
*  DATE        NAME       DESCRIPTION
*---------------------------------------------------------------------
* 2006-09-14   Alok       Updated for 14 Fly-Check rules adherence
*                         for IPBIRV1R2.IPv6
*---------------------------------------------------------------------
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.
*                      ALL RIGHTS RESERVED
*********************************************************************/
#ifndef _ICMP6_SH_VAR_H_
#define _ICMP6_SH_VAR_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "ipv6/icmp6/include/iicmp6_int_inc.h"


extern ULONG g_ulIP6ICMP6DebugFlag;
extern ULONG g_ulICMP6CliState;
extern IP6_ICMP6_MOD_INFO_S g_stMInfo;

extern struct IIF_IP6_ICMP6_INITVtbl        *g_pstICMP6InitTable;
extern struct IIF_IP6_ICMP6_CFGVtbl         *g_pstICMP6CfgTable;
extern struct IIF_IP6_ICMP6_FUNVtbl         *g_pstICMP6FunTable;
extern struct IIF_IP6_ICMP6_INT_INITVtbl    *g_pstICMP6INTInitTable;
extern struct IIF_IP6_ICMP6_INT_SSAVtbl     *g_pstICMP6INTSSATable;

extern ULONG ulSOCKTmrQueID;
extern ULONG ulVRPTID_SOCK;

//extern void vos_printf(char *fmt, ...);

#if (VRP_CENTERALIZATION == VRP_YES)
    extern void SNMP_Add_MIB_ipv6icmp_tree(void);
#endif

/* Added by Anand - V1R7 Workspace Integration */
#define ICMP6_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ICMP6_VAR_H_ */

