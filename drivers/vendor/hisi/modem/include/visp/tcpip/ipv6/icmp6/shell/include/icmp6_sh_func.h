/******************************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*------------------------------------------------------------------------------
*                              icmp6_sh_func.h
*
*   Project Code : VRP5.0
*    Module Name : IP6  ICMP6
*    Create Date : 2003/06/22
*         Author : Mahaveer Jain
*        Version :
*    Description : Shell SSA implement header file for ICMP6 module
*        Remarks : The following function declarations has their
*                  corresponding comments on its function definition headers.
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
* 2006-09-14   Alok       Updated for 14 Fly-Check rules adherence
*                         for IPBIRV1R2.IPv6
*******************************************************************************
*/
#ifndef _ICMP6_SH_FUNC_H
#define _ICMP6_SH_FUNC_H

#ifdef _cplusplus
extern "C"{
#endif

ULONG IP6_ICMP6_SH_Init(VOID);

ULONG IP6_ICMP6_SH_DeInit(VOID);

extern ULONG IP6_ICMP6_SH_LogToIPOSIC(ULONG ulLogID, ...);

ULONG IP6_ICMP6_SH_TimerDelete(ULONG ulTimerID);

ULONG IP6_ICMP6_SH_TimerCreate (ULONG ulMillSec,
                                VOID (*pfTimerFunc)(VOID *),
                                VOID  *pArg,
                                ULONG *pulTimerID,
                                ULONG ulFlag);

/* Start: RFC4443 compliance changes */
ULONG IP6_ICMP6_SH_TimerRefresh (ULONG ulTimerID, ULONG ulNewMillSec);

/* End: RFC4443 compliance changes */

#define IP6_ICMP6_SH_LOG        (VOID) IP6_ICMP6_SH_LogToIPOSIC

#ifdef _cplusplus
}
#endif /* _cplusplus */

#endif  /* _ICMP6_SH_FUNC_H */


