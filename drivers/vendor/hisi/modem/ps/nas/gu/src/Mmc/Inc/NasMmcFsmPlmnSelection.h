/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmPlmnSelection.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年4月27日
  最近修改   :
  功能描述   : NasMmcPlmnSelection.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年4月27日
    作    者   : w00176964
    修改内容   : 创建文件
  2.日    期   : 2011年7月04日
    作    者   : s46746
    修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __NASMMCFSMPLMNSELECTION_H__
#define __NASMMCFSMPLMNSELECTION_H__

#include "NasMmcCtx.h"
#include "NasMmcSndInternalMsg.h"
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"


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
VOS_UINT32 NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
VOS_UINT32 NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvInterAbortUtranCtrlPlmnSearchCnf_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(VOS_VOID);

VOS_UINT32  NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_UINT32 NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
);
VOS_VOID NAS_MMC_BuildSearchedPlmnInfoByLteSearchedPlmnInfoInd(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstLteSearchedPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo
);

VOS_UINT32 NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstInterPlmnSearchInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat
);

VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU   *pstSearchedExistPlmnInfo
);

VOS_UINT32 NAS_MMC_IsNeedSkipFddRcvRrcSearchedPlmnInfoInd_PlmnSelection(
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
);

VOS_VOID NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    VOS_UINT8                                               ucIsPowerOn
);
VOS_VOID NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedExistPlmnInfo,
    VOS_UINT8                                               ucIsPowerOn
);

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitPs(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmConnInfoInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvGmmSignalingStatusInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmRrConnInfoInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
VOS_UINT32 NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchStopCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmPlmnStopCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif
#endif

VOS_UINT32 NAS_MMC_GetNextHistorySearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);

VOS_UINT32 NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);

VOS_UINT32 NAS_MMC_GetNextPrefBandSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);

VOS_UINT32 NAS_MMC_GetNextSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);

VOS_VOID NAS_MMC_GetNextSearchPlmnFail_PlmnSelection(VOS_VOID);

VOS_VOID NAS_MMC_ProcNoRf_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
);

VOS_VOID NAS_MMC_ProcNoRfAreaLost_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
);

VOS_UINT32 NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);
VOS_VOID NAS_MMC_GetNoSearchedEhplmn_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat,    
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstDestEHPlmnInfo
);

/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
VOS_UINT32 NAS_MMC_IsNeedAddEhplmnWhenSeachDplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);
VOS_VOID NAS_MMC_BuildDestPlmnListWhenSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     *pstDestPlmnList,
    NAS_MML_PLMN_WITH_RAT_STRU          *pstDestPlmn
);
/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

VOS_VOID NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);

VOS_VOID NAS_MMC_SndSuspendReq_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID NAS_MMC_SndRelReq_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg
);

VOS_UINT32 NAS_MMC_IsReCampLtePlmnValid_PlmnSelection(VOS_VOID);

VOS_VOID NAS_MMC_ReCampLte_PlmnSelection(VOS_VOID);


VOS_UINT32 NAS_MMC_IsNeedEnableLte_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 enPlmnSearchScene
);

VOS_UINT32 NAS_MMC_IsDisableLteNeedWaitEpsConnRel_PlmnSelection(VOS_VOID);

#endif

VOS_VOID NAS_MMC_UpdateOosAreaLostPlmnSearchInfo_PlmnSelection(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstPlmnSearchReq,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_UpdatePlmnSearchInfo_PlmnSelection(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstPlmnSearchReq,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_UpdatePlmnSearchList_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstInterPlmnSearchInfo,
    VOS_UINT32                                               ulIsNeedSortAvailPlmnList,
    VOS_UINT8                                                ucIsAllBandSearch
);


VOS_VOID NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction
);

VOS_VOID NAS_MMC_SearchNextPlmn_PlmnSelection(VOS_VOID);

VOS_VOID NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection(VOS_VOID);

VOS_VOID NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection(VOS_VOID);


VOS_UINT32 NAS_MMC_ProcUserSearchCsRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);

VOS_UINT32 NAS_MMC_ProcUserSearchPsRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);

VOS_UINT32 NAS_MMC_ProcUserSearchRegCause15_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
);

VOS_UINT32 NAS_MMC_ProcUserSearchRegOtherCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
);

VOS_UINT32 NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
);

VOS_VOID NAS_MMC_LoadInterSysFsm_PlmnSelection(
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
);

VOS_VOID NAS_MMC_ProcUserSpecPlmnSrchForbGprsInfo_PlmnSelection( VOS_VOID );
VOS_VOID NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection( VOS_VOID );

VOS_VOID  NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucAccessMode
);


VOS_VOID NAS_MMC_ProcPsRegRslt_PlmnSelection(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
);

VOS_VOID NAS_MMC_ProcCsRegRslt_PlmnSelection(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
);

VOS_VOID  NAS_MMC_SndRslt_PlmnSelection(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt
);

#if   (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
);

VOS_VOID  NAS_MMC_ProcLmmMmcEpsOnlyAttachInd_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
);

VOS_VOID  NAS_MMC_ProcLmmAttachInd_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
);

VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
);

VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
);

VOS_VOID  NAS_MMC_ProcLmmTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif


VOS_UINT32  NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection(
     VOS_UINT32                         ulEventType,
     struct MsgCB                      *pstMsg
);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchScene_PlmnSelection(VOS_VOID);
VOS_UINT32  NAS_MMC_IsInterPlmnSearch_PlmnSelection(VOS_VOID);


VOS_UINT32 NAS_MMC_IsNeedSndEplmn_PlmnSelection( VOS_VOID );

VOS_UINT32 NAS_MMC_RcvSuspendFailCauseArealost_WaitCsPsRegRsltInd(VOS_VOID
);

VOS_VOID NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection(
    NAS_MML_EQUPLMN_INFO_STRU          *pstOutEplmnInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
);


VOS_UINT32 NAS_MMC_IsNeedHistoryPlmnSearch_PlmnSelection(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedPrefBandPlmnSearch_PlmnSelection(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedSpecPlmnSearch_PlmnSelection(VOS_VOID);

VOS_UINT8 NAS_MMC_GetSpecSceneSrchRplmnCarryEplmnFlag_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 enPlmnSearchScene,
    VOS_UINT8                             ucIsRoam
);

VOS_UINT8 NAS_MMC_IsSpecRatSearched_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enSpecRat
);

VOS_UINT32 NAS_MMC_IsNeedAddEplmnWhenSearchRplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);

VOS_UINT8 NAS_MMC_IsNeedUpdateSpecRatPlmnSearchInfo_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
);
VOS_UINT32  NAS_MMC_IsNeedAddDplmnOfSameCountryWhenSearchDPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
);

VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);




/* Added by s00246516 for L-C互操作项目, 2014-01-28, Begin */
#if   (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_DisableLteForSimReason_PlmnSelection(VOS_VOID);
#endif

VOS_VOID NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
);

VOS_UINT32 NAS_MMC_IsAllowedRegAfterAcqSucc_PlmnSelection(VOS_VOID);

VOS_UINT32 NAS_MMC_IsMsccRegReq_PlmnSelection(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection(VOS_VOID);

/* Added by s00246516 for L-C互操作项目, 2014-01-28, End */

VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection(VOS_VOID);
VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection(VOS_VOID);
VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection(VOS_VOID);

VOS_UINT32 NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_SaveGeoPlmn_PlmnSelection(
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSearchReq
);

extern VOS_VOID NAS_MMC_SndMsccSrchedGuPlmnInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_MMC_SndMsccSrchedLtePlmnInfo(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstSearchedPlmnInfoInd
);
#endif


VOS_UINT32 NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MMC_RcvTiWaitHistoryPlmnSrchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClRegStatusFromLmm
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

#endif

