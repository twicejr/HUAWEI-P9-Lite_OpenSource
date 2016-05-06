/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code:  VRP5.0
*    Module Name:  IP6 Addr Mgmt
*    File Name: ADDR_SH_FUNC.H
     Version       : IPBIRV100R003.IPv6.E001
*    Create Date:  2003/07/16
*         Author:  Vikas Goel
*     Description: Functions used in shell
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-07-16  VikasG    Create
   Problem Number: AC4D01246     Author:KLSrini,   Date:2006/12/4
   Description   :  Exception with router restart when change Controller
                    interface mode with IPv6 debug
*******************************************************************************/

#ifndef _ADDR_SH_FUNC_H
#define _ADDR_SH_FUNC_H

#ifdef    __cplusplus
extern "C"{
#endif


/* The function is available to both IPOS and VISP Environment */
ULONG IP6_Addr_Reg2IC(VOID);


ULONG IP6_Addr_SH_Tm_BootInSec(ULONG *pulSecond, ULONG *pulUSecond);

ULONG IP6_Addr_SH_CreateNonPeriodicTimer(VOID *pvTimerMsg, 
                                                              ULONG ulTimeMilliSec,
                                                              IP6_ADDR_TIMERTYPE_E enTimerType, 
                                                              ULONG *pulTimerId);
ULONG IP6_Addr_SH_DeleteTimer(ULONG ulTimerID);


ULONG IP6_Addr_SH_GetTimerInfo(ULONG ulTimerID, UINTPTR aulTimerMsgInfo[IP6_ADDR_MAX_TM_PARA_LEN]);

ULONG IP6_Addr_SH_GetLeftoverTime(ULONG ulTimerID, ULONG *pulRestTimeValue);

ULONG IP6_Addr_SH_RefreshTimer(ULONG ulTimerID, ULONG ulNewTimeValue);

ULONG IP6_Addr_SH_Timer_RegCallback();





#ifdef        __cplusplus
}
#endif        /* end of __cplusplus */

#endif        /* end of _ADDR_SH_FUNC_H_ */


