/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : Initial Draft
*    File Name      : ND_SH_SSA.H
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : the SSP interface module of ND
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef _ND_SH_SSA_H
#define _ND_SH_SSA_H

#ifdef    __cplusplus
extern "C"{
#endif

#define    ulVRPTID_ND  g_stNdAppInfo.ulTaskId

/* Invalid Queue-Id */
#define IP6_ND_INVALID_QUEUE_ID       0xFFFFFFFF

/* General Assert */
#define IP6_ND_ASSERT(m_exception)  VOS_DBGASSERT((m_exception))


VOID  IP6_ND_SH_ProcTimerEvents(ND_TIMER_S *pstTimerMsg);

/* Added By Ahmed for Defect ID: AC4D05729 */
VOID  IP6_ND_SH_ProcEvents(IP6_ND_EVENTMSG_S *pstMsg);

/* VOID IP6_ND_SH_AsynEnQue(ND_TIMER_S *pstRcvMsg);*/
VOID IP6_ND_SH_AsynEnQue(IP6_ND_EVENTMSG_S *pstRcvMsg);


ULONG IP6_ND_SH_TimerCreate(ULONG ulMillSec, VOID  (*pfTimerFunc)(VOID *),
                   VOID  *pArgTimerMessage, ULONG *pulRetTimerID, ULONG ulFlag);
ULONG IP6_ND_SH_TimerDelete(ULONG ulTimerID);
ULONG IP6_ND_SH_Tm_Now(ULONG *pulRetTimeInMillSecHigh,
                                                ULONG *pulRetTimeInMillSecLow);
ULONG IP6_ND_SH_Timer_GetInfo(ULONG ulTimerID, VOS_TIMERINFO_S *pRetTimerInfo);
ULONG IP6_ND_SH_Tm_BootInSec(ULONG *pulSecond, ULONG *pulUSecond);
VOID IP6_ND_SH_T_Delay(ULONG ulMillisecond);
ULONG IP6_ND_SH_TimerCreateWin(ULONG ulMillSec,
                                           VOID  (*pfTimerFunc)(VOID *),
                                           VOID *pArgTimerMessage,
                                           ULONG *pulRetTimerID, ULONG ulFlag);
ULONG IP6ND_SH_LogToIPOSIC(ULONG ulLogID, ...);
ULONG IP6_ND_SH_Addr6ToStr(const IN6ADDR_S *pstIp6Addr, char *szAddr);
extern VOS_VOID VOS_T_Delay(ULONG ulMillSecs);  /*Changed by wan for VISPV1R7 integration*/

#if (VRP_YES == IP6_NDHOST)

ULONG IP6_ND_SH_TWL_RegCallbackFunc(VOID);

ULONG IP6_ND_SH_DHCP6_Adapt_RegCallbackFunc(VOID);

ULONG IP6_ND_SH_CreateTWLInstance (TWL_HANDLE *phNDTWLHandle);

ULONG IP6_ND_SH_DeleteTWLInstance(VOID);

ULONG IP6_ND_SH_StartTimer(ULONG ulTimeValue,VOID *pvTimerMsg,
                           ULONG *pulTimerid);

ULONG IP6_ND_SH_CreateNonPeriodTimer(ULONG ulTimeValue,
                    ULONG (*pfIP6_TimeOutHandler)(UINTPTR aulPara[]),
                    UINTPTR aulPara[TWL_MAX_USE_PARA_LEN], ULONG *pulTimerid);

ULONG IP6_ND_SH_StopTimer(ULONG ulTimerID);

ULONG IP6_ND_SH_RefreshTimer(ULONG ulTimerID,ULONG ulNewTimeValue);

ULONG IP6_ND_SH_TickProc(VOID);

ULONG IP6_ND_SH_GetRestTimeValue(ULONG ulTimerID,ULONG *pulRestTimeValue);

ULONG IP6_ND_SH_GetTimerPara(ULONG ulTimerID,VOID *pstTimerMsg);

ULONG IP6_ND_SH_TWL_Timeout_Handler(UINTPTR aulPara[TWL_MAX_USE_PARA_LEN]);

ULONG IP6_ND_SH_CreateCtrlMsgQueue(VOID);

ULONG IP6_ND_SH_CtrlMsgQue_Write(UINTPTR ulMsg[4],
                          ULONG ulFlags, ULONG ulTimeOutInMillSec);

ULONG IP6_ND_SH_Ev_Write_ToNDTask(ULONG ulEvent);

/* BEGIN : NDHOST SDV Defect AC4D05450, Anand */
ULONG IP6_ND_SH_Is_CtrMsg_Queue_Full(VOID);

VOID IP6_ND_SH_ScheduleCtrlMsgQueue(IP6_ND_CFG_OPT_E *penDelayFlag);

ULONG IP6_ND_SH_GetTimerMsg(ULONG ulTimerID,
                            UINTPTR aulPara[TWL_MAX_USE_PARA_LEN]);


/* DHCP Adapter Function declarations */
ULONG IP6_ND_NotifyServerAvailability(ULONG ulIfnetIndex,
                                      IP6_ND_DHCPV6SERVER_AVAIL_E eNotifyType);
ULONG IP6_ND_DHCP6CAdaptAddrNotUsable(IP6_ND_IADESC_S *pstIADesc,
                                        IP6_ND_IN6ADDRWITHTIME_S *pstAddress,
                                        IP6_ND_NOTUSABLE_REASON_E eType);

#endif /* (VRP_YES == IP6_NDHOST) */

VOID IP6_ND_SH_ScheduleTmrQueue(VOID);

/* Added By Ahmed for Defect ID: AC4D05729 */
VOID IP6_ND_SH_ScheduleEventQueue(VOID);

#ifdef        __cplusplus
}
#endif        /* end of __cplusplus */

#endif        /* end of _ND_SH_SSA_H_ */
