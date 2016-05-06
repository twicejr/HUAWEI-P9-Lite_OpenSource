/*******************************************************************************
*                                                                              *
*        Copyright 2003-2006  Huawei Technologies India Private Limited        *
*                          All Rights Reserved                                 *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*                              udp6_sh_ic.h                                    *
*                                                                              *
*    Project Code: VRP5.0                                                      *
*    Module Name:  IP6 BASIC UDP6                                              *
*    Version    :  Initial Draft                                               *
*    Create Date:  2003/04/29                                                  *
*         Author:  Sunil Dutt                                                  *
*     Description: Shell IC implement header file for UDP6 Component           *
*                                                                              *
*------------------------------------------------------------------------------*
*  Modification History                                                        *
*  DATE        NAME             DESCRIPTION                                    *
*  --------------------------------------------------------------------------  *
*  2003-06-10  Sunil Dutt    Create                                            *
*  2006-06-08          Alok          Updated for 14 Fly-Check rules adherence  *
*                                    for IPOSIR-V1R1-IPv6                      *
*******************************************************************************/

#ifndef UDP6_SH_IC_H
#define UDP6_SH_IC_H

#define UDP6_DBGID_PACKET            IC_INFOID_DEF(MID_UDP6,IC_INFO_DEBUG,0)
#define UDP6_DBGID_GENERAL           IC_INFOID_DEF(MID_UDP6,IC_INFO_DEBUG,1)

VOID IP6_UDP6_SH_DbugPkt(CHAR *pcPreStr, MBUF_S *pstMbuf, int ioff);
ULONG IP6_UDP6_SH_DebugPkt(ULONG ulflag);
LONG IP6_UDP6_SH_DebugAll();
LONG IP6_UDP6_SH_NoDebugAll();
ULONG IP6_UDP6_SH_Reg2IC(VOID);
VOID IP6_UDP6_SH_DebugToIC (CHAR *pszString);
ULONG IP6_UDP6_SH_DebugPktEnable(VOID);

#endif
