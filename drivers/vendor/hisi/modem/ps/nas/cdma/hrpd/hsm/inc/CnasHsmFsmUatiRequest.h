

#ifndef __CNAS_HSM_FSM_UATI_REQUEST_H__
#define __CNAS_HSM_FSM_UATI_REQUEST_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmSndInternalMsg.h"
#include "nas_cttf_hrpd_rsnp_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
#define CNAS_HSM_MSG_PRIORITY_UATI_REQ                  (10)
#define CNAS_HSM_MSG_PRIORITY_UATI_COMP                 (10)
#define CNAS_HSM_UAIT_REQ_FAILED_MAX_CNT                (5)
#define CNAS_HSM_UATI_ASSIGN_TIMEOUT_MAX_CNT            (5)

/* 发送Uati Complete后，收到Snp Data Cnf指示失败时，Uati Complete的重试次数*/
#define CNAS_HSM_UAIT_COMPLETE_MAX_RETRY_CNT            (3)

/*****************************************************************************
  3 The Enumeration Define
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

typedef struct
{
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpFailReason;
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enUatiFailReason;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_SCP_FAIL_REASON_MAP_UATI_FAIL_REASON_STRU;


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
VOS_UINT32 CNAS_HSM_RcvInterUatiReq_UATIRequest_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitUATIAssignTimerExpire_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if 0
VOS_UINT32 CNAS_HSM_RcvCttfSnpDataCnf_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if 0
VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if 0
VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdOverHeadMsgInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_HSM_SndUatiReqMsg_UatiReq(VOS_VOID);

#if 0
VOS_VOID CNAS_HSM_SndUatiCmplMsg_UatiReq(VOS_VOID);
#endif

VOS_VOID CNAS_HSM_QuitFsmUatiReq(
    CNAS_HSM_UATI_REQUEST_RESULT_ENUM_UINT8                 enRslt,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enFailReason
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if 0
VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvApsDiscReq_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT8 CNAS_HSM_ProcAmpMsg_UATIRequest_WaitUATIAssign(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd
);



VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if 0
VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if 0
VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_UatiReq_WaitUatiCmplSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfHrpdSnpDataInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvApsDiscReq_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_UatiReq_WaitUatiAssign(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_UatiReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvApsDiscReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_WaitUatiReqSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_HSM_HandleUatiAssignMsg_SetupState(
     CNAS_HSM_UATI_ASSIGN_MSG_STRU                         *pstUatiAssignMsg
);

VOS_VOID CNAS_HSM_HandleUatiAssignMsg_OpenState(
     CNAS_HSM_UATI_ASSIGN_MSG_STRU                         *pstUatiAssignMsg
);

CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8
CNAS_HSM_ConvertScpFailReasonToUatiFailReason(
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpFailReason
);

VOS_UINT32 CNAS_HSM_GetWaitUatiAssignTimerLen_UatiReq(VOS_VOID);

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









