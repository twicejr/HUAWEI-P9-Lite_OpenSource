

#ifndef __CNAS_HSM_FSM_MAIN_H__
#define __CNAS_HSM_FSM_MAIN_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmSndInternalMsg.h"
#include "nas_cttf_hrpd_rsnp_pif.h"
#include "CnasHsmCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/

/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/




/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSystemAcqInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvUatiRequestResultInd_Setup(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvUatiRequestResultInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Setup(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmHrpdPaRatModeNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSystemAcqInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_GetNoMonitorDistance_Open(
    VOS_INT32       lLongitude,
    VOS_INT32       lLatitude
);

VOS_UINT8 CNAS_HSM_IsNeedStartDeactProcedure(VOS_VOID);

VOS_VOID CNAS_HSM_HandleMonitorDistance_Open(
    VOS_UINT8                          *pucIsNeedStartDeactProc
);


VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_ProcAmpMsg_Open(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstSnpDataInd
);


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmConnMnmtResultInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 CNAS_HSM_RcvHsmSessionActiveResultInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionDeactiveResultInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionDeactiveResultInd_Setup(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_HSM_EnterInactiveStateProc_L1Main(VOS_VOID);

VOS_VOID CNAS_HSM_EnterSetupStateProc_L1Main(VOS_VOID);

VOS_VOID CNAS_HSM_EnterSlaveStateProc_L1Main(VOS_VOID);

VOS_VOID CNAS_HSM_StartUATIRequestProcedure_L1Main(
    CNAS_HSM_UATI_REQ_TRIGGER_ENUM_UINT8                    enTriggerReason
);

/* Added session active reason as input parameter */
VOS_VOID CNAS_HSM_StartSessionActiveProcedure_L1Main(
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason
);


/* Change session deacitve reason to session close reason */
VOS_VOID CNAS_HSM_StartSessionDeactiveProcedure_L1Main(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
);

VOS_VOID CNAS_HSM_StartSwitchOnProcedure_L1Main(VOS_VOID);

VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT8 CNAS_HSM_IsNeedSndUatiReq(VOS_VOID);

VOS_UINT8 CNAS_HSM_IsSubnetChanged(VOS_VOID);

VOS_UINT32 CNAS_HSM_RcvRrmStatusInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdIratFromLteNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionActiveResultInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSystemAcqInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdResumeInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdIratFromLteNtf_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionActiveResultInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionDeactiveResultInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 CNAS_HSM_IsNeedReNegEhrpdSession(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8    enCurrSessionType
);

VOS_UINT32 CNAS_HSM_RcvHsmSwitchOnResultInd_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8  CNAS_HSM_IsCardChanged(VOS_VOID);

VOS_UINT32 CNAS_HSM_RcvApsOrigReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvApsDiscReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmConnEstReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_HSM_ProcSessionRetryAfterSessionDeact_L1Main(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpNegFail(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpAnExp(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenFail(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenDenyExplicitlyRej(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenDenyImplicitlyRej(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpPersInvalid(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpCfgRspExp(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpCfgMsgFail(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpAnGaupFail(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpIratToLte(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpNoRf(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonNetworkLostInSessionAct(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonWaitScpCnfExp(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonSessionActAbortByAnCloseSession(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonAmpFailUatiReachMaxCnt(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonAmpFailSysAcqSubnetChange(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonAmpFailOtherScene(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonKeepAliveExpOpen(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonInternalSessionCloseSalve(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonEhrpdToHrpd(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonHrpdToEhrpd(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonPowerSaveStup(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonPowerSaveOpen(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonPowerOff(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonSessionActAbortByOhm(VOS_VOID);

VOS_VOID CNAS_HSM_ResetSessionRetryParameters(VOS_VOID);

CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8
CNAS_HSM_ConvertUaitFailReasonToSessionDeactReason(
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enUatiFailReason
);

CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8
CNAS_HSM_ConvertSessionActFailReasonToSessionDeactReason(
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enSessionActFailReason
);

VOS_UINT8 CNAS_HSM_IsSessionDeactReasonAbort(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
);

VOS_VOID CNAS_HSM_StartConnMnmtProcedure_L1Main(
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8           enTriggerScene
);

VOS_VOID CNAS_HSM_ProcMsgForFirstSysAcq_L1Main(VOS_VOID);

VOS_VOID CNAS_HSM_ProcSessionRecoverySucc_L1Main(VOS_VOID);



#endif


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasHsmMain.h */






