/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmSysAcq.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年7月29日
  最近修改   :
  功能描述   : CnasXsdFsmSysAcq.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月29日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_FSM_SYS_ACQ_H__
#define __CNAS_XSD_FSM_SYS_ACQ_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasXsdCtx.h"
#include  "cas_1x_control_initialstate_nas_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_XSD_INVAILD_SCAN_LIST_FREQ_INDEX               (0xFFFF)

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

VOS_UINT32  CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvXsdSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_IsSidInOperLockSysWhiteList(
    VOS_UINT16                          usSid
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XSD_ProcScanListSyncComplete_SysAcq(VOS_VOID);

VOS_VOID CNAS_XSD_ContinueSyncScanList_SysAcq(
    VOS_UINT16                          usDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan
);

VOS_VOID CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    VOS_UINT32                                              ulIsNegSys
);

VOS_VOID CNAS_XSD_ProcCasSyncCnfSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);

VOS_VOID CNAS_XSD_ProcCasSyncCnfFail_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);

VOS_VOID CNAS_XSD_ProcCasSyncCnfNoRf_SysAcq(VOS_VOID);

VOS_VOID CNAS_XSD_ContinueSysSync_SysAcq(VOS_VOID);

CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_XSD_GetCurSysAcqScene_SysAcq(VOS_VOID);

VOS_UINT8 CNAS_XSD_IsImmediateSysAcq_SysAcq(VOS_VOID);

VOS_UINT32 CNAS_XSD_IsEmergencySysAcq_SysAcq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);
VOS_UINT32 CNAS_XSD_IsEmcSDSysAcq_SysAcq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);
VOS_VOID CNAS_XSD_GetNextAvailSysAcqList_SysAcq(
    VOS_UINT16                                             *pusFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqList
);


VOS_VOID CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq(
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList
);

VOS_VOID CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq(
    CNAS_CAS_1X_FREQENCY_CHANNEL_STRU                      *pstFreq,
    CNAS_CAS_1X_SYSTEM_IDENTITY_STRU                       *pstSyncedSysId
);

VOS_VOID CNAS_XSD_QuitFsmSysAcq_SysAcq(VOS_VOID);

VOS_VOID CNAS_XSD_ProcFreqAvoidedInCasSyncCnf(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);


VOS_VOID CNAS_XSD_PerformAbortProcedure_SysAcq(VOS_VOID);


VOS_UINT32 CNAS_XSD_PerformNormalCallRedialSystemSeletion_SysAcq(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
);

VOS_VOID CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);

VOS_VOID CNAS_XSD_PerformNotLessPrefSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU                       *pstSyncCnf
);

VOS_VOID CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU                       *pstSyncCnf
);

VOS_UINT32 CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_SysAcq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU                       *pstSyncCnf
);

VOS_VOID CNAS_XSD_PerformAllowedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU                       *pstSyncCnf
);

VOS_VOID CNAS_XSD_PerformSpecificSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU                       *pstSyncCnf
);

VOS_VOID CNAS_XSD_PerformPreferedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU                       *pstSyncCnf
);

VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_VOID CNAS_XSD_GetNextScanChanList_SysAcq(
    VOS_UINT16                          usCurScanChanIndex,
    VOS_UINT16                         *pusDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XSD_GetMostMatched1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMostMatchGeoListInfo
);

VOS_VOID CNAS_XSD_UpdateScanListChanStatusUponReceivedDeterminInd(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

VOS_VOID CNAS_XSD_UpdateGeoSysRecordStatusUponReceivedDeterminInd(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
);

VOS_UINT32 CNAS_XSD_IsCurGeoListSrchedInGeoListSrchInfo(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
);

VOS_VOID CNAS_XSD_ConstructGeoSysRecordSrchList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_ContinueGeoSysRecordSrch(VOS_VOID);

VOS_VOID CNAS_XSD_ContinueAvailSysListSrch(VOS_VOID);

VOS_UINT32 CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_UINT32 CNAS_XSD_IsCurSysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_UINT32 CNAS_XSD_IsCurSysGeoListSameAsCurSyncGeoInfo(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);

VOS_VOID CNAS_XSD_PreformBestPreferedSystemSelectionAndGeoSysRecordSearchListExist_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);

VOS_VOID CNAS_XSD_ProcSyncFailAndNoGeoSysRecorSearchList_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);

VOS_VOID CNAS_XSD_ReportSrvAvailableInd_SysAcq(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo
);

VOS_UINT32 CNAS_XSD_IsCallRelAnyCampOnFreq_SysAcq(
    CNAS_CAS_1X_FREQENCY_CHANNEL_STRU                      *pstFreq
);

VOS_UINT16 CNAS_XSD_UpdateSyncSuccChanStatus_SysAcq(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstChannel,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_UINT16 CNAS_XSD_UpdateSyncFailChanStatus_SysAcq(
    VOS_UINT16                                              usBeginScanListIndex,
    VOS_UINT16                                              usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU                        *pstSyncFailChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);

VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfFail_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
);

VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasDeterminInd_SysAcq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstTempFreq
);

VOS_VOID CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

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

#endif /* end of CnasXsdFsmSysAcq.h */
