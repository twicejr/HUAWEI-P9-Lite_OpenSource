/********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*---------------------------------------------------------------------
*                              icmp6_sh_ic.h
*
*   Project Code : VRP5.0
*    Module Name : IP6 BASIC ICMP6
*    Create Date : 2003/06/30
*         Author : Mahaveer Jain
*        Version :
*    Description : Shell IC implement header file for ICMP6 module
*---------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  --------------------------------------------------------------------
* 2006-09-14   Alok       Updated for 14 Fly-Check rules adherence
*                         for IPBIRV1R2.IPv6
**********************************************************************
*/
#ifndef _ICMP6_SH_IC_H
#define _ICMP6_SH_IC_H

#ifdef _cplusplus
extern "C"{
#endif

#define ICMP6_DBGID_INFO  IC_INFOID_DEF(MID_ICMP6, IC_INFO_DEBUG, 0)

#define ICMP6_DBGID_INFO2  IC_INFOID_DEF(MID_ICMP6, IC_INFO_DEBUG, 1)

#define IP6_ICMP6_LOGID_DEF(macro_LogId)   \
    IPOS_IC_INFOID_DEF(MID_ICMP6, IC_INFO_LOG, macro_LogId)
#define IP6_ICMP6_DBGID_DEF(macro_DbgId)   \
    IPOS_IC_INFOID_DEF(MID_ICMP6, IC_INFO_DEBUG, macro_DbgId)

extern CHAR * inet_ntop(USHORT usFamily, const CHAR *pSrcAddr,
                            CHAR *szDstAddr, ULONG ulAddrLen);

/* Log and Debug related functions */
LONG IP6_ICMP6_SH_DebugAll(VOID);
LONG IP6_ICMP6_SH_NoDebugAll(VOID);
ULONG IP6_ICMP6_SH_Reg2IC(VOID);

ULONG IP6_ICMP6_SH_LogToIPOSIC(ULONG ulLogID, ...);
ULONG IP6_ICMP6_SH_DbgToIPOSIC(ULONG ulDbgID, ...);
ULONG IP6_ICMP6_SH_AddrStToStr(const IN6ADDR_S *pstAddress,
                                  char *szAddr);

extern VOID IP6_ICMP6_SH_SendInfo2IC (const ICMP6_S *pstIcmp6,
                                        const IN6ADDR_S *pstSrcaddr,
                                        const IN6ADDR_S *pstDstaddr,
                                        ULONG ulFlag);

#ifdef _cplusplus
}
#endif

#endif
