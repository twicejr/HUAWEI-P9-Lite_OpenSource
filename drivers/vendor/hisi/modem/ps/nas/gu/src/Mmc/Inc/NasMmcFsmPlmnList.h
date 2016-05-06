/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmPlmnList.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年7月02日
  最近修改   :
  功能描述   : NasMmcFsmPlmnList.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月02日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NAS_MMC_FSM_PLMN_LIST_H__
#define __NAS_MMC_FSM_PLMN_LIST_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasMmcSndInternalMsg.h"
#include  "MmcMmInterface.h"
#include  "MmcGmmInterface.h"

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
VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvInterPlmnListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PlmnList_NonInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MMC_SndRslt_PlmnList(
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt,
    VOS_UINT8                                               ulNeedPlmnSearch,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstListInfo,
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                    *pstRegRsltInfo
);
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmSignalingStatusInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmRrConnInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmTbfRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmAbortInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmServiceRequestResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvAreaLostInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitWasPlmnListCnfExpired_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasPlmnListCnfExpired_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmDetachInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcTafPlmnListAbortReq_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitLmmPlmnListCnfExpired_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSuspendCnf_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

#endif

VOS_VOID NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList(VOS_VOID);
VOS_VOID NAS_MMC_SndMsccListSearchCnfMsg_PlmnList(VOS_VOID);
VOS_VOID NAS_MMC_SndMsccPlmnListRejMsg_PlmnList(VOS_VOID);
VOS_VOID NAS_MMC_ProcFsmAbort_PlmnList(VOS_VOID);


VOS_UINT32  NAS_MMC_IsNeedAnyCellSrch_PlmnList(VOS_VOID);

VOS_UINT32  NAS_MMC_IsUserPlmnList_PlmnList(VOS_VOID);

VOS_VOID    NAS_MMC_ProcCsRegRslt_PlmnList(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
);

VOS_VOID    NAS_MMC_ProcPsRegRslt_PlmnList(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
);

VOS_UINT32  NAS_MMC_IsNeedPlmnSearch_PlmnList(VOS_VOID);

VOS_VOID    NAS_MMC_SndMsccPlmnListCnf_PlmnList(VOS_VOID);

VOS_VOID    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList(VOS_VOID);

VOS_VOID    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);
#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvMsccCsgListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_BuildReportCsgIdList_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
);
VOS_VOID NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
);
VOS_VOID NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
);


VOS_VOID NAS_MMC_ProcUserCsgListReq_PlmnList(VOS_VOID);
VOS_VOID NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);
VOS_VOID NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
);

VOS_VOID NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU       *pstPlmnSrchCnf
);
NAS_MML_CSG_ID_TYPE_ENUM_UINT8 NAS_MMC_GetCsgIdType_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
);
VOS_UINT32 NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId,
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8      ucCsgIdType
);
VOS_UINT8 NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
);
VOS_VOID NAS_MMC_AddCsgIdToListCnf_PlmnList(
    VOS_UINT32                                              ulIndex,
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          enCsgIdType,
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
);

NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8 NAS_MMC_ConvertMmlCsgIdTypeToMsccCsgIdType_PlmnList(
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8      enCsgIdType
);


VOS_VOID NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf
);

VOS_VOID NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSrchCnf
);

VOS_VOID NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);
VOS_VOID NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU       *pstPlmnSrchCnf
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitWasCsgListCnfExpired_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasCsgListCnfExpired_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvCsgListAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_IsCsgList_PlmnList(VOS_VOID);
VOS_VOID NAS_MMC_SndMsccCsgListSearchCnf_PlmnList(VOS_VOID);
VOS_VOID NAS_MMC_SndMsccCsgListAbortCnf_PlmnList(VOS_VOID);
VOS_VOID    NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);
#if (FEATURE_LTE == FEATURE_ON)
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
);

VOS_VOID NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
);

VOS_VOID NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
);

VOS_UINT32  NAS_MMC_RcvTiWaitLmmCsgListSrchCnfExpired_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID    NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList(VOS_VOID);

#endif
#endif

VOS_VOID    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID    NAS_MMC_SndSpecRatSuspendReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID    NAS_MMC_ProcRrmmSearchCnf_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
);

VOS_VOID    NAS_MMC_ProcPlmnListSucc_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
);

VOS_VOID    NAS_MMC_ProcRrmmSuspendCnf_PlmnList(
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf
);

#if (FEATURE_LTE == FEATURE_ON)
VOS_VOID    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(
    MMC_LMM_PLMN_ID_LIST_STRU          *pstSrcPlmnIdList,
    RRC_PLMN_ID_LIST_STRU              *pstDestPlmnIdList
);
#endif


VOS_VOID    NAS_MMC_GetPlmnStatus_PlmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                          *pucStatus,
    VOS_UINT16                          usRaMode
);

VOS_VOID NAS_MMC_ProcRrcConnRelInd_PlmnList(VOS_VOID);

VOS_VOID NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
);

VOS_VOID NAS_MMC_ProcUserPlmnListReq_PlmnList(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedWaitRrcRel_PlmnList( VOS_VOID );

VOS_VOID    NAS_MMC_ProcInterPlmnListReq_PlmnList(VOS_VOID);

VOS_VOID    NAS_MMC_ProcWasSysInfo_PlmnList(
    struct MsgCB                       *pstWSysInfoInd
);

VOS_VOID    NAS_MMC_ProcGasSysInfo_PlmnList(
    struct MsgCB                       *pstGSysInfoInd
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID    NAS_MMC_ProcLmmSearchCnf_PlmnList(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf
);

VOS_VOID    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList(VOS_VOID);

VOS_VOID NAS_MMC_ProcLteSysInfo_PlmnList(
    struct MsgCB                       *pstLSysInfoInd
);


VOS_VOID    NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
);

VOS_VOID    NAS_MMC_ProcLmmTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
);

VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
);

VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
);

VOS_VOID    NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
);

VOS_VOID    NAS_MMC_ProcLmmAttachInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
);

#endif

VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitRrcConnRelInd(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitCsPsRegRsltInd(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
);


/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

VOS_VOID NAS_MMC_ProcNoRf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat
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

#endif /* end of NasMmcFsmPlmnList.h */


