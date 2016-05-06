/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              raw_ip6_var.h
*
*    Project Code: VRP5.0
*    Module Name : IP6 RawIp6
*    Version     : Initial Draft
*    Create Date : 2003/06/23
*    Author      : Sunil Dutt
*    Description : Contains the extern declaration for globals and definition
*                  of macros related to other components that are needed by
*                  RawIP6 Component.
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2003-06-23  Sunil Dutt       Create
*************************************************************************/
#ifndef _RAW_IP6_VAR_H
#define _RAW_IP6_VAR_H

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * SID of RAWIP6.
 */
#define SID_RIP6_INPUT                           57
#define SID_RIP6_OUTPUT_PREPEND                  58
#define SID_RIP6_OUTPUT_COPY                    59
#define SID_RIP6_CTLOUTPUT                       60
#define SID_RIP6_USRREQ_ICMP6_FILTER             61
#define SID_RIP6_INPUT_NEAT                      62

extern UINTPTR   g_ulRawIn6pcb;

extern ULONG   g_ulRip6_sendspace;
extern ULONG   g_ulRip6_recvspace;

#define  RAW_IP6_OK           0
#define  RAW_IP6_MEMNOTFREED  1
#define  RAW_IP6_MEMFREED     2

#define RAWIP6_INVALID_CHKSUM -1

/* Appln. specified Hop Limit Value specifying use of Kernel Default Value */
#define RAWIP6_DEFHOPLIMIT  -1

/* Added by Anand - V1R7 Workspace Integration */
#define RAWIP6_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

#ifndef NO_USE
#define     NO_USE(var)     (VOID)(var)
#endif


extern RIP6STAT_S        g_stRip6Stat;
extern RIP6_INT_OBJ_S    g_stRIP6_INT_OBJ;

extern IP6_RIP6_MOD_INFO_S    g_stRIP6ModInfo;
extern const IN6ADDR_S        g_stZeroRIP6In6Addr;

extern SOSB6_CALLBACUP_SET_S  *g_pfRIP6SocketAPI;
extern IN6PCB_CALLBACUP_SET_S *g_pfRIP6In6PCBCallBack;
extern const IN6ADDR_S         g_stZeroRIP6In6Addr;

/* Added in IR V1R3 by Arvind for Hop Limit Issue */
extern ULONG g_ulRawIP6IsHostNode; /* Node Type (Host/Router) */


#ifdef  __cplusplus
}
#endif

#endif

