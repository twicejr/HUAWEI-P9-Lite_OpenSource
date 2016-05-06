/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code  : VRP5.0
*    Module Name   : PMTU
*    Version       : Initial Draft
*    File Name     : pmtu_sh_func.h
*    Create Date   : 2003/09/02
*         Author   : Vikas Goel
*     Description  : Functions used in shell
*------------------------------------------------------------------------------
*  Modification History
*  DATE          NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003/09/02  VikasG    Create
*******************************************************************************/
#ifndef _PMTU_SH_FUNC_H
#define _PMTU_SH_FUNC_H

VOID  IP6_PMTU_SH_Cachetimeout_handler (VOID);
VOID  IP6_PMTU_SH_Agetimeout_handler (VOID);
ULONG IP6_PMTU_SH_Reg2IC(VOID);
ULONG IP6_PMTU_SH_Init (VOID);


ULONG IP6_PMTU_SH_Timer_Create(ULONG ulMillSec, VOID(*pfTimerFunc)(VOID *),
                            VOID *pArg, ULONG *pulRetTimerID, ULONG ulFlag);
ULONG IP6_PMTU_SH_Timer_Delete(ULONG ulTimerID);
ULONG IP6_PMTU_SH_Que_Write(UINTPTR ulMsg[4], ULONG ulFlags,
                                            ULONG ulTimeOutInMillSec);
ULONG IP6_PMTU_SH_Ev_Write(ULONG ulEvents);

ULONG IP6_Pmtu_SH_LogToIPOSIC(ULONG ulLogID, ...);
ULONG IP6_Pmtu_SH_DbgToIPOSIC(ULONG ulLogID, ...);
ULONG IP6_Pmtu_SH_AddrStToStr(const IN6ADDR_S *pstAddress,
                                      char *szAddr);

#if(TCPIP_IN_VRP == VRP_NO)
extern ULONG TCPIP_Get_PAF_ResValue (SPECS_RES_VALUE_S *pstResValue);
#endif

#ifdef    __cplusplus
extern "C"{
#endif

#ifdef        __cplusplus
}
#endif        /* end of __cplusplus */

#endif        /* end of _PMTU_SH_FUNC_H_ */



