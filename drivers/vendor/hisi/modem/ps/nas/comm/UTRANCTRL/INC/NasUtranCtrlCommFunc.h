/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlCommFunc.h
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : NasUtranCtrlCommFunc.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_UTRANCTRL_COMM_FUNC_H_
#define _NAS_UTRANCTRL_COMM_FUNC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"

#include  "NasUtranCtrlCtx.h"

#include  "Nasrrcinterface.h"
#include  "MmcLmmInterface.h"
#include "NasMmcTimerMgmt.h"

#include "NasMmcSndInternalMsg.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


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
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)


VOS_UINT32 NAS_UTRANCTRL_BuildEventType (
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulMsgName
);

VOS_UINT32 NAS_UTRANCTRL_GetMsgEventType(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_SndGuAsUtranModeReq(
    VOS_UINT32                          ulRcvPid,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enMode
);

VOS_VOID  NAS_UTRANCTRL_ConvertSimPlmnToNasPlmn(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_UTRANCTRL_SndLmmUtranModeReq(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enMode
);
#endif  /* end of #if (FEATURE_ON == FEATURE_LTE) */

VOS_VOID  NAS_UTRANCTRL_StartTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  NAS_UTRANCTRL_StopTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);

NAS_MMC_TIMER_STATUS_ENUM_U8  NAS_UTRANCTRL_GetTimerStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
);
VOS_VOID NAS_UTRANCTRL_SndGuAsSuspendReq(
    VOS_UINT32                          ulRcvPid
);

VOS_VOID NAS_UTRANCTRL_SndAsSuspendRsp(
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt,
    VOS_UINT32                          ulRcvPid
);

VOS_VOID NAS_UTRANCTRL_SndGuAsPlmnStopReq(
    VOS_UINT32                          ulRcvPid
);

VOS_VOID NAS_UTRANCTRL_SndGuAsSyscfgReq(
    VOS_UINT32                          ulRcvPid
);

VOS_VOID NAS_UTRANCTRL_SndGuAsPowerOffReq(
    VOS_UINT32                          ulRcvPid
);

VOS_VOID NAS_UTRANCTRL_SndGuAsStartReq(
    VOS_UINT32                          ulRcvPid
);

VOS_VOID NAS_UTRANCTRL_UpdateCurUtranSwitchMode(
    VOS_UINT8                                              *pucImsi,
    VOS_UINT8                                               ucSimPresentStatus,
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU              *pstUtranModeAutoSwitch
);
VOS_VOID NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(
    VOS_UINT32                          ulRcvPid
);

VOS_UINT32 NAS_UTRANCTRL_IsSndOmPcRecurMsgValid(VOS_VOID);

VOS_UINT32 NAS_UTRANCTRL_IsNeedUtranCtrlFsmProcMsg(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_IsNeedSndAnotherUtranModeMsg(
    struct MsgCB                      *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_IsNeedSkipSearchUtranFddMode(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_IsNeedSkipSearchUtranTddMode(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_StartUtranTddModeMsgTimer(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_StartUtranFddModeMsgTimer(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_StartUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_StopUtranTddModeMsgTimer(
    VOS_UINT32                          ulMsgName
);

VOS_VOID NAS_UTRANCTRL_StopUtranFddModeMsgTimer(
    VOS_UINT32                          ulMsgName
);

VOS_VOID NAS_UTRANCTRL_StopUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 NAS_UTRANCTRL_IsSpecPlmnMccInGuRrcPlmnIdList(
    VOS_UINT32                          ulSpecPlmnMcc,
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList
);



VOS_VOID NAS_UTRANCTRL_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_UTRANCTRL_BuildRrMmStartCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    MMC_START_RESULT_ENUM_UINT32        ulResult,
    RRMM_START_CNF_STRU                *pstMsg
);
VOS_VOID NAS_UTRANCTRL_BuildRrMmPowerOffCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRMM_POWER_OFF_CNF_STRU            *pstMsg
);

VOS_VOID NAS_UTRANCTRL_BuildRrMmSysCfgCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRMM_SYS_CFG_RESULT_ENUM_UINT32     ulResult,
    RRMM_SYS_CFG_CNF_STRU              *pstMsg
);

VOS_VOID NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enPlmnSearchType,
    RRMM_PLMN_SEARCH_CNF_STRU          *pstMsg
);

VOS_VOID NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg(
    NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU            *pstMsg
);


RRC_PLMN_SEARCH_RLT_ENUM_UINT32 NAS_UTRANCTRL_BuildRrMmPlmnSearchFailRslt(
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enPlmnSearchType
);
VOS_VOID NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(
    VOS_UINT32                          ulTdMccNum,
    VOS_UINT32                         *pulTdMccList,
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList
);

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

RRC_NAS_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enNasUtranMode
);

#if (FEATURE_ON == FEATURE_LTE)
MMC_LMM_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enNasUtranMode
);
#endif

VOS_UINT32 NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
);
VOS_UINT32 NAS_UTRANCTRL_IsNeedProcLmmPlmnSearchCnf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstPlmnSrchCnf
);
VOS_VOID NAS_UTRANCTRL_ProcPlmnSearchReq_GetGeo(
    VOS_UINT32                          ulSndPid,
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSrchReq
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

#endif /* end of NasUtranCtrCommFunc.h */
