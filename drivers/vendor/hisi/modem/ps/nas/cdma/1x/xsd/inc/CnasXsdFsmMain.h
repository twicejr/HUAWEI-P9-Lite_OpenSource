/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdFsmMain.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年7月3日
  最近修改   :
  功能描述   : CnasXsdFsmMain.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月3日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_FSM_MAIN_H__
#define __CNAS_XSD_FSM_MAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include "cas_1x_control_initialstate_nas_pif.h"

#include "CnasXsdCtx.h"
#include  "CnasXsdSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_MAX_TRY_TIMES    (10)

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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 CNAS_XSD_RcvStartReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvPowerOffReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvPowerOffRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_XSD_RcvPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 CNAS_XSD_RcvSwitchOnRsltCnf_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvSysAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvInternalSysAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvSysAcqRsltCnf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvInternalSysAcqReq_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvSysDeterminInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvCasOhmInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiAvailTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvInternalRedirectionInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvRedirectionRsltCnf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithRedirectionReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithProtoMismatchReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithReleaseReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithNdssOffReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithSysLostReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithRescanReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithLockReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithUnlockReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithAccessDeniedReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithAcctBlockReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithErrReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithRegistRejReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithReselectionReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithSystemReselectionReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithNewSystemReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithMaxAccessFailureReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithAbnormalReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_UINT32 CNAS_XSD_RcvTiAvailMru0TimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvPowerOffReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT16 CNAS_XSD_GetNextOocScheduleTimerLen(
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
);

VOS_VOID CNAS_XSD_ProcOocSchedule(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
);

VOS_VOID CNAS_XSD_SetOocSearchScene(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
);
VOS_VOID CNAS_XSD_ProcSearchNetworkRslt_Fail(
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
);

VOS_VOID CNAS_XSD_ProcSearchNetworkRslt_Abort(
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU     *pstSysAcqRslt
);

VOS_VOID CNAS_XSD_ProcSearchNetworkRslt_Succ(
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU     *pstSysAcqRslt
);
VOS_VOID CNAS_XSD_UpdateOocSearchPhaseAndCurrentTimes(
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
);

CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_XSD_GetOocSearchScene(VOS_VOID);

VOS_UINT32 CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithNoRfReason_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccMoCallEndNtf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackNtf_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackSrchBreakTimerExpired_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackNtf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccMoCallEndNtf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccMoCallEndNtf_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackNtf_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_XSD_IsCurSystemValid( VOS_VOID );

VOS_VOID CNAS_XSD_ProcRedirectionRsltCnf_Fail( VOS_VOID );

VOS_VOID CNAS_XSD_ProcEmcRedialSysAcq_Idle(VOS_VOID);
VOS_UINT32 CNAS_XSD_IsNeedReportNoService(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *pstSysDeterminInd
);
VOS_UINT32 CNAS_XSD_ProcEmcSysAcqFlow_Idle(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32      enEmcAcqScene,
    VOS_UINT32                              ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU         *pstFreq,
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU   *pstSysDeterminInd
);

VOS_VOID CNAS_XSD_ProcNormalCallRedialSysAcqFailScene(VOS_VOID);

VOS_VOID CNAS_XSD_ProcEmergencyCallSysAcqFailScene(VOS_VOID);

VOS_VOID CNAS_XSD_ProcEmcCallReleaseSysAcqFailScene(VOS_VOID);

VOS_VOID CNAS_XSD_ProcEmcCallBackSystemLostSysAcqFailScene(VOS_VOID);

VOS_VOID CNAS_XSD_ProcCallReleaseWithRedirSysAcqFailScene(
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU     *pstSysAcqRslt
);

VOS_UINT32 CNAS_XSD_RcvMsccXsdSysAcq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_VOID CNAS_XSD_ProcCasSystemDetermineIndWithAcquisitionFail_Idle(
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd
);

extern CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCasOhmHrpdSysAddr(VOS_VOID);


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

#endif /* end of CnasXsdFsmMain.h */
