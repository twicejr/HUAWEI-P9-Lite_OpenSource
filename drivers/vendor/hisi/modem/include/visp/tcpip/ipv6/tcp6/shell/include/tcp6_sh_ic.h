/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              Tcp6_sh_ic.h
*
*    Project Code: VRP5.0
*    Module Name : IP6 BASIC PP
*    Version     : Initial Draft
*    Create Date : 2003/04/29
*    Author      : Naina Gupta
*    Description : Shell ic implement header file for PP module
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2003-06-10  Naina Gupta      Create
*  2006-06-02  Alok             Updated for 14 Fly-Check rules adherence
*                               for IPOSIR-V1R1-IPv6
*************************************************************************/


#ifndef _TCP6_SH_IC_H
#define _TCP6_SH_IC_H

#ifdef  __cplusplus
extern "C"{
#endif

LONG IP6_TCP6_SH_DebugAll(VOID);
LONG IP6_TCP6_SH_NoDebugAll(VOID);
LONG IP6_TCP6_SH_ShowDebugging(CHAR *pszStatusStr,
                                ULONG ulMaxLen,  ULONG ulDebugIndx,
                                ULONG *pulWaitlistHandle,  ULONG ulInterface);
ULONG IP6_TCP6_SH_Reg2IC(VOID);

VOID  IP6_TCP6_SH_SendInfo2IC (ULONG ulInfo,CHAR *pszInfo);
VOID  IP6_TCP6_DbugPkt(CHAR *pszPreStr,SHORT sTcpState,
                               TCP6IP6HDR_S *pstHeader);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* #ifndef _TCP6_SH_IC_H */

