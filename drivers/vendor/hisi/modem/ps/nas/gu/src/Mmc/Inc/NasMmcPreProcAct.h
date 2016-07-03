
#ifndef _NAS_MMC_PREPROCACT_H_
#define _NAS_MMC_PREPROCACT_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"

#include "MsccMmcInterface.h"

#include  "Nasrrcinterface.h"
#include  "NasMmlCtx.h"

#include "MsccMmcInterface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include   "MmcMmInterface.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_MMC_REPORT_TIMER_OTA_EVENT_START  (1)
#define NAS_MMC_REPORT_TIMER_OTA_EVENT_STOP   (0)


#define NAS_MMC_RSSI_INVALID            (99)                                    /*无效值*/
#define NAS_MMC_RSRP_UNVALID            (99)                                    /*无效值*/
#define NAS_MMC_RSRQ_UNVALID            (99)                                    /*无效值*/
#define NAS_MMC_SIGNAL_DIVISOR          (8)                                     /*无效值*/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32  NAS_MMC_RcvMsccModeChange_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32  NAS_MMC_RcvGmmInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32  NAS_MMC_RcvGmmPdpStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);





VOS_UINT32  NAS_MMC_RcvMmInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);





VOS_UINT32  NAS_MMC_RcvGasScellRxInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasAtMsgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);
VOS_UINT32  NAS_MMC_RcvWasAtMsgCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnQryReqPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32  NAS_MMC_RcvRrMmNotCampOn_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);


VOS_UINT32  NAS_MMC_RcvRrMmLimitServiceCamp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmEquplmnQuery_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvUsimRefreshFileInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccUpdateUplmnNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID  NAS_MMC_ProcAgentUsimReadFileCnf_PreProc(
    VOS_UINT16                          usEfId,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);


VOS_UINT32 NAS_MMC_RcvGmmNetworkCapabilityInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvGmmTinInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcNotCampOnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmDetachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmTinInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmErrInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmCellSignReportInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvLmmCellSignReportInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

VOS_UINT32 NAS_MMC_RcvOmInquireReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvOmConfigTimerReportReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_IsMsccAttachTypeValid(
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enAttachType
);

VOS_UINT32  NAS_MMC_RcvMsccAttachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmGprsServiceInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvMsccSignReportReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_UINT32  NAS_MMC_RcvMsccOtherModemInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccOtherModemDplmnNplmnInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvMsccNcellInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccPsTransferInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#endif

VOS_UINT32 NAS_MMC_ProcMsccAttachReqInForbLa_PreProc(
    MSCC_MMC_ATTACH_REQ_STRU            *pstTafAttachReq,
    VOS_UINT32                          ulForbType
);

VOS_UINT32  NAS_MMC_RcvMsccDetachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvLmmAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmServiceRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_VOID  NAS_MMC_ProcAttachCnfAuthRej_PreProc(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
);
VOS_VOID  NAS_MMC_ProcEpsOnlyAttachCnf_PreProc(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
);
VOS_VOID  NAS_MMC_ProcCsOnlyAttachCnf_PreProc(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
);
VOS_VOID  NAS_MMC_ProcCsPsAttachCnf_PreProc(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
);
#endif

VOS_UINT32  NAS_MMC_RcvMmAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmDetachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32  NAS_MMC_IsNeedStartAvailableTimer_PsDetachCnf(VOS_VOID);

VOS_UINT32  NAS_MMC_RcvMmDetachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32 NAS_MMC_RestoreFixedContextData_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RestoreContextData_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafSysCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafRegReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_VOID NAS_MMC_RcvWasCellRssi_PreProc(
    RRC_NAS_CELL_RSCP_STRU_LIST         *pstWasCellRscp
);

VOS_VOID NAS_MMC_RcvWasCellBler_PreProc(
    RRC_NAS_CELL_TRCH_BLER_STRU_LIST    *pstWasCellBler
);

VOS_VOID NAS_MMC_RcvWasCellId_PreProc(
    RRC_NAS_CELL_ID_ST                  *pstWasCellId
);

VOS_UINT32  NAS_MMC_RcvOmOtaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvMsccUserSpecPlmnSearch_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvUserReselReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiAvailTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiPlmnSearchPhaseOneTotalTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_IsNeedAddPhaseNumRcvPhaseTotalTimerExpired_PreProc(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedRestartAvailableTimer( VOS_VOID );

VOS_VOID    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PreProc(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucAccessMode
);

VOS_UINT32  NAS_MMC_CheckUserSpecPlmnSearchParamMsg_PreProc(
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_ProcDetachCnfSucc_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
);

VOS_UINT32  NAS_MMC_ProcDetachCnfAuthRej_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
);

VOS_UINT32  NAS_MMC_ProcEpsOnlyDetachCnf_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
);

VOS_UINT32  NAS_MMC_ProcCsOnlyDetachCnf_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
);

VOS_UINT32  NAS_MMC_ProcCsPsDetachCnf_PreProc(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccCLInterSysStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif
#endif

#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32  NAS_MMC_RcvMsccCsgListSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcInterPlmnListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccStopGetGeoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccDplmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_UpdateDplmnNplmnList_PreProc(
    MSCC_MMC_DPLMN_SET_REQ_STRU        *pstRcvMsg,
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU  *pstDPlmnNPlmnCfgInfo
);

VOS_UINT32 NAS_MMC_IsEnableBgPlmnSearch_PreProc( VOS_VOID );

VOS_UINT32 NAS_MMC_RcvTiTryingHighPrioPlmnSearchExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiHplmnTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvStkSteerRoamingInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);


VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmGetTransactionReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvGmmLocalDetachInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32   NAS_MMC_RcvLmmSuspendCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32   NAS_MMC_RcvLmmMmcDetachInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmTimerStateNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32   NAS_MMC_RcvLmmRegStatusChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32   NAS_MMC_RcvLmmServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PreProc(
	VOS_UINT32                          ulEventType,
	struct MsgCB                        *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmRrConnInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasAcInfoChange_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSimAuthFailInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

VOS_UINT32  NAS_MMC_RcvRrMmCipherInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmCipherInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafOmMaintainInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_ProcUserReselReqUnNormalSrv_PreProc(
    MSCC_MMC_PLMN_USER_RESEL_REQ_STRU      *pUserReselReq
);
VOS_UINT32  NAS_MMC_ProcUserReselReqNormalService_PreProc(
    MSCC_MMC_PLMN_USER_RESEL_REQ_STRU      *pUserReselReq
);

 VOS_UINT32 NAS_MMC_ProcUserReselReqNormalServiceFun(VOS_VOID);

VOS_VOID NAS_MMC_DelayBgSearch(VOS_VOID);

VOS_UINT32  NAS_MMC_IsHighPrioPlmnFileRefreshed(
    VOS_UINT32                          ulFileId
);

VOS_UINT32  NAS_MMC_ProHighPrioPlmnRefreshInd_PreProc(VOS_VOID);

VOS_VOID NAS_MMC_ProcActingHplmnRefresh_PreProc(
    VOS_UINT8                               *pulBufferRefresh
);


VOS_VOID NAS_MMC_ProcScanCtrl_PreProc(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);

VOS_UINT32  NAS_MMC_RcvCmServiceRejectInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32  NAS_MMC_RcvPeriodDeleteDisabledPlmnWithRatExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmT3402LenNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvCustomizedForbLaTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvForbidLaTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmEutranNotAllowNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#if   (FEATURE_ON == FEATURE_LTE)

VOS_UINT32  NAS_MMC_RcvMmAbortInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);



VOS_UINT32  NAS_MMC_RcvLmmEmmInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvEnableLteExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmCsfbAbortInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmEmcPdpStatusNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif


VOS_UINT32 NAS_MMC_IsNeedPlmnSearch_UserReselReq(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedPlmnSearch_Oos(
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU        *pstRrmmLimitCampOnMsg
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32 NAS_MMC_RcvAcpuOmErrLogRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAcpuOmErrLogCtrlInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAcpuOmFtmCtrlInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32  NAS_MMC_RcvMsccEOPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcInterNvimOPlmnRefreshInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvMmSimAuthFail_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmSimAuthFail_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmCmServiceInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvMsccNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvPeriodicNetScanExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmNetScanCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccAbortNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmNetScanStopCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);





VOS_UINT32  NAS_MMC_RcvGasNcellMonitorInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasAreaLostInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasAreaLostInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrmPsStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvTiHighPrioRatHplmnSrchTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmServiceRequestResultInd_PreProc(
    VOS_UINT32                        ulEventType,
    struct MsgCB                      *pstMsg
);


VOS_UINT32 NAS_MMC_RcvRrmmSuspendInd_PreProc(
    VOS_UINT32                        ulEventType,
    struct MsgCB                      *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrmmResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_DSDS)
VOS_UINT32  NAS_MMC_RcvMsccBeginSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccEndSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccSrvAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#endif
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PreProc(
    VOS_UINT32                        ulEventType,
    struct MsgCB                      *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmInfoChangeNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_VOID NAS_MMC_ProcNoRfAreaLost_PreProc(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
);

VOS_UINT32 NAS_MMC_RcvGmmSigStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 NAS_MMC_RcvMsccImsSrvInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 NAS_MMC_RcvMsccImsSwitchStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_MMC_RcvMsccVoiceDomainChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MMC_ProcVoiceDomainDisableLte_PreProc(VOS_VOID);

extern VOS_UINT32  NAS_MMC_RcvMsccCFPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32  NAS_MMC_RcvTafSDTConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
extern VOS_UINT32  NAS_MMC_RcvMsccCFPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_FillPrefPlmnFile(
    VOS_UINT16                          usUpdateFile,
    VOS_UINT8                          *pucEfFile,
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU   *pstUPlmnInfo
);

VOS_UINT32 NAS_MMC_UpdateUsimPrefPlmn(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU   *pstUPlmnInfo,
    VOS_UINT16                          usUpdateFile
);

VOS_UINT32 NAS_MMC_ModPrefPlmnInfo(
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
);

VOS_UINT32 NAS_MMC_DelPrefPlmnInfo(
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
);

VOS_UINT32 NAS_MMC_AddPrefPlmnInfo(
    MSCC_MMC_PREF_PLMN_SET_REQ_STRU    *pstPrefPlmnSetReq
);

VOS_UINT32 NAS_MMC_RcvUsimSetFileCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_WaitUsimSetFileExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccPrefPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccPrefPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvMsccPlmnPriClassQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvMsccBgSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvLmmBgSearchHrpdCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvLmmStopBgSearchHrpdCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccStopBgSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_WaitLmmBgSearchHrpdExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32  NAS_MMC_RcvMmPlmnSearchInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_IsDplmnSetSeqValid(
    MSCC_MMC_DPLMN_SET_REQ_STRU                           *pstDPlmnSetReq
);

VOS_UINT32 NAS_MMC_RcvMsccAutoReselSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32  NAS_MMC_RcvMtaGetNasChrInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of NasMmcPreProcAct */
