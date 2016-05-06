

#ifndef __CNAS_HSM_PRE_PROC_ACT_H__
#define __CNAS_HSM_PRE_PROC_ACT_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmCtx.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "nas_cttf_hrpd_rsnp_pif.h"
#include "cas_hrpd_sessioncfg_session_layer_pif.h"
#include "CnasCcb.h"
#include "CnasHsmSndRrm.h"
#include "cnas_cttf_hrpd_pa_pif.h"

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
CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16 CNAS_HSM_ConvertCasStatusToHsm_PreProc(
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enPreHrpdOrigCasStatus,
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enCurHrpdCasStatus
);

HSM_HSD_HRPD_CAS_STATUS_ENUM_UINT16 CNAS_HSM_ConvertCasStatusToHsd_PreProc(
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enCasStatus);

VOS_UINT32 CNAS_HSM_RcvCasHrpdCasStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdSessionNegStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdSessionNegRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_ProcAmpMsg_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd
);

VOS_UINT32 CNAS_HSM_ProcSmpMsg_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd
);

VOS_UINT32 CNAS_HSM_RcvCttfHrpdSnpDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_HSM_RcvApsOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvApsDiscReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmConnEstReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasSysTimeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);




VOS_UINT32 CNAS_HSM_RcvApsConnRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvAps1xToHrpdHandOffReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHlu1xToHrpdHandOffCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHluLocChngdInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_HSM_RcvCasHrpdConnOpenInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdConnCloseInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasDataServiceAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_HSM_RcvCasIdleHoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_HSM_RcvTiKeepAliveTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_ProcKeepAliveReqFromAN_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstKeepAliveReq
);

VOS_UINT32 CNAS_HSM_ProcKeepAliveRspFromAN_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstKeepAliveRsp
);

VOS_UINT32 CNAS_HSM_ProcHardWareIdReqFromAN_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstHardWareIdReq
);

VOS_UINT32 CNAS_HSM_RcvTiMoKeepAliveWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiWaitKeepAliveRspExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiMtKeepAliveWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiHardWareIdRspWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 CNAS_HSM_RcvTiSessionCloseRspWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#ifdef DMT
VOS_UINT32 CNAS_HSM_RcvHsmModifySessionSeedReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmModifyCurSysTickReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmFwdTrafChanDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsmModifyAmpSmpAttrReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_VOID CNAS_HSM_StoreAmpNegAttrib_PreProc(
    CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU   *pstAmpNegAttribs
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdCommitInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvEhsmLteRegSuccessInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvRrmStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfSnpDataCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvTiAddressTimerExp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasSessionChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCasHrpdNetworkLostInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvHsdOhmNotCurrentInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_ProcSessionClose_PreProc(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU   *pstSessionClose
);

VOS_UINT32 CNAS_HSM_IsNeedDiscardSessionClose_PreProc(VOS_VOID);

VOS_UINT32 CNAS_HSM_IsCurCsimUimCardPresent(
    USIMM_CARD_STATUS_STRU             *pstCsimUimInfo
);

VOS_UINT32 CNAS_HSM_RcvPihUsimStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvUsimStoreEsnMeidRsltCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSM_RcvCttfHprdPaAccAuthStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_HSM_ClearRelativeCtx_PreProc(VOS_VOID);

VOS_UINT32 CNAS_HSM_RcvTiUatiCmplWaitSnpDataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pMsg
);

VOS_VOID CNAS_HSM_RcvUatiCmplSnpDataCnf_PreProc(
    CTTF_HRPD_SNP_RSLT_ENUM_UINT32                          enSnpDataCnfRslt,
    CTTF_HRPD_SNP_DATA_FAIL_REASON_ENUM_UINT32              enSnpDataCnfFailReason
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

#endif /* end of CnasHsmMainCtrl.h */


