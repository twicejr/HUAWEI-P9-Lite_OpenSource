

#ifndef __CNAS_EHSM_FSM_ACTIVATING_H__
#define __CNAS_EHSM_FSM_ACTIVATING_H__

    /*****************************************************************************
      1 The Include of the header file
    *****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
#include "ehsm_aps_pif.h"
#include "CnasEhsmCtx.h"

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

VOS_UINT32 CNAS_EHSM_RcvEhsmAttachReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);


VOS_UINT32 CNAS_EHSM_RcvApsReConnReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvApsPdnActivateReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmConnEstCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitHsmConnEstCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitConnRetryEst_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdReconnInd_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnConnCnf_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvCttfEhrpdPdnAttachCnf_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnfExpired_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitCttfPdnSetupCnf_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvTiWaitRetryPdnSetup_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);
VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_Activating_WaitPdnRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvEhsmAbortReq_Activating_WaitCttfPdnSetupCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);
VOS_UINT32 CNAS_EHSM_RcvAbortReq_Activating_WaitHsmConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);
VOS_UINT32 CNAS_EHSM_RcvEhsmPdnSetupReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_VOID CNAS_EHSM_IncreConntRetryTimes_Activating(VOS_VOID);

VOS_VOID CNAS_EHSM_ResetConntRetryTimes_Activating(VOS_VOID);

VOS_VOID CNAS_EHSM_EstPdnFailureHandler_Activating(
    EHSM_APS_CAUSE_ENUM_UINT32          enCause,
    VOS_UINT32                          ulEventType
);
EHSM_APS_CAUSE_ENUM_UINT32 CNAS_EHSM_GetAbortCauseByEventType_Activating(
    VOS_UINT32                          ulEventType
);

VOS_VOID CNAS_EHSM_ProcAbortProcedure_Activating(
    VOS_UINT32                          ulAbortEventType
);

VOS_UINT8 CNAS_EHSM_IsRejectByNetworkErrorCode_Activating(
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode
);

VOS_VOID CNAS_EHSM_PdnSetupFailureHandler_Activating(
    VOS_UINT8                                               ucPdnId,
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode,
    CNAS_EHSM_APN_STRU                                     *pstApn
);

VOS_VOID CNAS_EHSM_AttachFailureHandler_Activating(
    VOS_UINT8                                               ucPdnId,
    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16                  enErrorCode,
    CNAS_EHSM_APN_STRU                                     *pstApn
);

VOS_VOID CNAS_EHSM_AttachFailureCommHandlerForHrpdFallback_Activating
(
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
);

VOS_VOID CNAS_EHSM_PdnActivateFailureCommHandlerForHrpdFallback_Activating
(
    VOS_UINT8                           ucCid,
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
);

VOS_UINT32 CNAS_EHSM_RcvApsPdnAttachReq_Activating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_RcvHsmSessionInfoInd_Activating_WaitConnEstRetry(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_EHSM_SaveEhrpdLocalPdnInfo_Activating(
    VOS_UINT8                           ucPdnId
);

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

#endif /* end of CnasEhsmActivating.h */


