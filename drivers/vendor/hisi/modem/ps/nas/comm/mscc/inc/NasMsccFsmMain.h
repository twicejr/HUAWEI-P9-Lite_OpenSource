


#ifndef __NAS_MSCC_FSM_MAIN_H__
#define __NAS_MSCC_FSM_MAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasMsccCtx.h"
#include  "NasMsccSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifdef DMT
extern VOS_UINT32 g_ulDisableAutoSysAcq;
#endif


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


/* State: NAS_MSCC_MAIN_STA_NULL act table */

VOS_UINT32 NAS_MSCC_RcvMmaStartReq_Main_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MSCC_RcvMsccStartCnf_Main_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


/* NAS_MSCC_MAIN_STA_DEACTIVE act table */
VOS_UINT32 NAS_MSCC_RcvMmaStartReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MSCC_RcvMmaSysAcquireReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccPowerOffCnf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


/* NAS_MSCC_MAIN_STA_ACTIVE act table */
VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcPlmnSelectionRsltInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccPowerOffCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32 NAS_MSCC_GetSystemAcquireFinalResult(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32                enAcqRslt
);

VOS_VOID NAS_MSCC_ProcPowerOffResult_Main(
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32  enRslt
);

VOS_UINT32 NAS_MSCC_RcvMmaSysCfgReq_Main_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccSysCfgCnf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccSysCfgCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* 删除此函数 */


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvHsdSysAcqInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvInterSysAcqRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MSCC_RcvInternalSysAcqReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcMmssLteUnavailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MSCC_ProcBsrFailureRslt_Main_Active(
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU    *pstBsrSearchRsltCnf
);

VOS_UINT32 NAS_MSCC_RcvInternalBsrRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiBsrTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiSleepTimerExpired_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiAvailableTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTiScanTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MSCC_PerformSystemAcquireUponSleepTimerExpired_Main(VOS_VOID);


VOS_UINT32 NAS_MSCC_RcvMmcMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvXsdMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvHsdRfAvailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MSCC_RcvMmcRfAvailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmaSrvAcqReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallStartNtf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MSCC_RcvHsdInterSysStartInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmcInterSysStartInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMsccCLInterSysRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallSusccessNtf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvXsdEmcCallBackInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvTi1xSrvClSysAcqPhaseOneTotalTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredOosSrch_L1Main(VOS_VOID);

VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main(VOS_VOID);

VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredLteHistorySrchWith1xSrvExist_L1Main(VOS_VOID);

NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32 NAS_MSCC_GetSysAcqLteSrchType_L1Main(
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
);



#endif

VOS_VOID NAS_MSCC_PerformSystemAcquireUponPowerOn_Main(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MSCC_PerformSystemAcquireUponSysCfg_Main(VOS_VOID);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
VOS_VOID NAS_MSCC_ProcDynamicLoadAfterStartCnf_Main(VOS_VOID);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Active(
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

#endif /* end of CnasXsdFsmRedir.h */



