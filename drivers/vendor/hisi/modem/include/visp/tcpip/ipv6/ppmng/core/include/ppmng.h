/**********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited        
*                          All Rights Reserved                                 
*----------------------------------------------------------------------
*                              ppmng.h                                            
*    Project Code:  VRP5.0                                                     
*    Module Name:  IP6 PP                                                     
*    Create Date:  2003/06/09                                               
*    Author:       Arun H S
*    Description:  To define data structure for PP component     
*-----------------------------------------------------------------------
*  Modification History                                                        
*  DATE        NAME             DESCRIPTION                                    
*  ----------------------------------------------------------------------
*  2003-06-09  Arun H S         Create                                         
*************************************************************************/
#ifndef _IP6_PPMNG_H
#define _IP6_PPMNG_H

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/ipv6/ppmng/include/ppmng_api.h"

typedef struct tagIP6_SH_TIMEOUT_CALLBACUP_SET_S
{
    VOID (*IP6_PP_TimerProcess) (VOID);
} IP6_SH_TIMEOUT_CALLBACUP_SET_S;


typedef enum tagIP6MIBObjects
{
    IP6_PP_MIB_IN_RCVS = 1,
    IP6_PP_MIB_IN_HDR_ERRS,
    IP6_PP_MIB_IN_TOOBIG_ERR,
    IP6_PP_MIB_IN_NOROUTES,
    IP6_PP_MIB_IN_ADDR_ERRS,
    IP6_PP_MIB_IN_UNKNOWN_PROTOS,
    IP6_PP_MIB_IN_TRUNC_PKTS,
    IP6_PP_MIB_IN_DISCARDS,
    IP6_PP_MIB_IN_DELIVER,
    IP6_PP_MIB_IN_MCAST_PKTS,
    IP6_PP_MIB_OUT_FORW_DGMS,
    IP6_PP_MIB_OUT_REQS,
    IP6_PP_MIB_OUT_DISCARDS,
    IP6_PP_MIB_OUT_FRAG_OKS,
    IP6_PP_MIB_OUT_FRAG_FAILS,
    IP6_PP_MIB_OUT_FRAG_CREATS,
    IP6_PP_MIB_OUT_MCAST_PKTS,
    IP6_PP_MIB_REASM_REQDS,
    IP6_PP_MIB_REASM_OKS,
    IP6_PP_MIB_REASM_FAILS
} IP6_PP_MIB_OBJECTS;

ULONG IP6_PP_UnicastRouting_GetStatus ();
ULONG IP6_PP_TimerProcess (IP6_PP_Timer_MSG_S *pstMsg);
ULONG IP6_PP_GetStatistics (IP6_ICMP6_STATS_S *pstIp6Icmp6Stat);
ULONG IP6_PP_SetStatistics ();
ULONG IP6_PP_MIB_GetGlobalStatistics (IP6STAT_S *pstIp6Stat);
ULONG IP6_PP_MIB_SetGlobalStatistics (IP6_PP_MIB_OBJECTS etmpMIBObjects, ULONG ulData);
ULONG IP6_PP_MIB_Set_Statistics (ULONG ulIpv6IfIndex, ULONG ulenumMib, ULONG ulIpv6IfStats);
ULONG IP6_PP_MIB_Get_Statistics (ULONG ulIpv6IfIndex, IP6STAT_S *pstIp6Stat);
VOID IP6_PP_SOSB6_Socket_RegisterCallBack(SOSB6_CALLBACUP_SET_S *pstSOSB6CallBack);
VOID IP6_PP_IN6PCB_Socket_RegisterCallBack(IN6PCB_CALLBACUP_SET_S *pstIN6PCBCallBack);
VOID IP6_PP_Incr_Decr_Statistics (IP6_PP_STATISTICS etmpIp6Stats, LONG lData);
ULONG IP6_PP_PktTypeStat_Register(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);
ULONG IP6_PP_PktTypeStat_UnRegister(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);
ULONG IP6_PP_GetPP6PktTypeStat(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey, 
                                          TCPIP_PP6_PKTTYPE_STAT_S *pstFlowStat);
ULONG IP6_PP_ClrPP6PktTypeStat(TCPIP_PP6_PKTTYPE_STAT_KEY_S  *pKey);
VOID IP6_PP_IncrPP6PktStat(ULONG ulPro, USHORT usPort, ULONG ulOff, ULONG ulPktType, MBUF_S *pstMBuf);
    
#ifdef __cplusplus
}
#endif

#endif

