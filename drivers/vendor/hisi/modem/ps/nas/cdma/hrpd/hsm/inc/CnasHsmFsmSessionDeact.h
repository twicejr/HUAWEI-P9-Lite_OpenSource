

#ifndef __CNAS_HSM_FSM_SESSION_DEACT_H__
#define __CNAS_HSM_FSM_SESSION_DEACT_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmSndInternalMsg.h"

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
VOS_VOID CNAS_HSM_QuitFsmScpDeactiveReq(VOS_VOID);

VOS_UINT8 CNAS_HSM_IsNeedSendSessionClose_SessionDeact(
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM_UINT8       enCloseReasonSendAn
);

VOS_UINT32 CNAS_HSM_RcvInterSessionDeactReq_SessionDeact_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitSnpDataCnfTimerExpire_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfSnpDataCnf_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_SessionDeact_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasConnCloseInd_SessionDeact_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitHrpdConnCloseIndTimerExpire_SessionDeact_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitScpDeactiveCnfTimerExpire_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasScpDeactiveCnf_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdResumeInd_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvRrmStatusInd_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvCasNetworkLostIndProc_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_SessionDeact_WaitSessionCloseSnpDataCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_SessionDeact_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_SessionDeact_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvRrmStatusInd_SessionDeact_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_SessionDeact_WaitConnCloseInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvRrmStatusInd_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSystemAcquiredInd_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdResumeInd_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdIratFromLteInd_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPilotSrchFailNtf_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_SessionDeact_WaitScpDeactiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_GetSessionCloseWaitSnpDataCnfTimerLen_SessionDeact(VOS_VOID);

VOS_UINT32 CNAS_HSM_GetConnCloseWaitConnCloseIndTimerLen_SessionDeact(VOS_VOID);

VOS_UINT32 CNAS_HSM_GetScpDeactiveWaitScpDeactiveCnfTimerLen_SessionDeact(VOS_VOID);

CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM_UINT8 CNAS_HSM_GetStartReviseTimerSceneBySessionDeactReason_SessionDeact(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
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

#endif /* end of CnasHsmMain.h */








