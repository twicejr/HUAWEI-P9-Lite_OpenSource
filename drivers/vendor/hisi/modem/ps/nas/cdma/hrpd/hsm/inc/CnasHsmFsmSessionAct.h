

#ifndef __CNAS_HSM_FSM_SESSION_ACT_H__
#define __CNAS_HSM_FSM_SESSION_ACT_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmSndInternalMsg.h"
#include "cas_hrpd_sessioncfg_nas_pif.h"
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
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enSessionActFailReason;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_SCP_FAIL_REASON_MAP_SESSION_ACT_FAIL_REASON_STRU;


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
VOS_VOID CNAS_HSM_QuitFsmScpActReq(
    CNAS_HSM_SESSION_ACTIVE_RESULT_ENUM_UINT8               enRslt,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enFailReason
);

VOS_UINT32 CNAS_HSM_RcvInterSessionActiveReq_SessionAct_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitScpActiveCnfTimerExpire_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasScpActiveCnf_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

PS_BOOL_ENUM_UINT8 CNAS_HSM_GetEhrpdFlag(
    CNAS_CAS_HRPD_SCP_ACT_TYPE_ENUM_UINT8                   enScpActType
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitPaRatModeNtfTimerExpire_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_SessionAct_WaitScpActiveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_SessionAct_WaitPaRatModeNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8
CNAS_HSM_ConvertScpFailReasonToSessionActFailReason(
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpFailReason
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







