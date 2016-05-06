/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_fsm.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP
*  Date Created: 2008-06-02
*        Author: Yaochengliang
*   Description: PTP状态机模块的h文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME               DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-06-02    Yaochengliang        Create
*
*******************************************************************************/
#ifndef _PTP_FSM_H_
#define _PTP_FSM_H_

#ifdef __cplusplus
extern "C" {
#endif

ULONG PTP_DoFsm(PTP_PORT_S *pstPtpPort, ULONG ulPtpFsmEvent);
ULONG PTP_DoSlaveOnlyFsm(PTP_PORT_S *pstPtpPort, ULONG ulPtpFsmEvent);
ULONG PTP_DoMasterOnlyFsm(PTP_PORT_S *pstPtpPort, ULONG ulPtpFsmEvent);
ULONG PTP_FsmToDisableState(PTP_PORT_S *pstPtpPort);
ULONG PTP_FsmToFaultyState(PTP_PORT_S *pstPtpPort);
ULONG PTP_FsmToInitializingState(PTP_PORT_S *pstPtpPort);
ULONG PTP_FsmToListeningState(PTP_PORT_S *pstPtpPort);
ULONG PTP_FsmToUncalibratedState(PTP_PORT_S *pstPtpPort);
ULONG PTP_FsmToSlaveState(PTP_PORT_S *pstPtpPort);
ULONG PTP_FsmToMasterState(PTP_PORT_S *pstPtpPort);
ULONG PTP_FsmInitPtpPort(PTP_PORT_S *pstPtpPort);
ULONG PTP_FsmInitPtpClock();
ULONG PTP_UpdateParentDS(PTP_PORT_S *pstPtpPort);

#ifdef __cplusplus
}
#endif

#endif

