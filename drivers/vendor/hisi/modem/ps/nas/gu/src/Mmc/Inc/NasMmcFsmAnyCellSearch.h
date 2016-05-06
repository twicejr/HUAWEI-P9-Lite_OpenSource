/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmAnyCellSearch.h
  版 本 号   : 初稿
  作    者   : W00167002
  生成日期   : 2011年4月29日
  最近修改   :
  功能描述   : NasMmcFsmAnyCellSearch.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年4月29日
    作    者   : W00167002
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef _NAS_MMC_FSM_ANYCELL_SEARCH_H_
#define _NAS_MMC_FSM_ANYCELL_SEARCH_H_

#include  "vos.h"
#include  "NasMmlCtx.h"
#include  "NasMmcSndInternalMsg.h"


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
VOS_UINT32 NAS_MMC_RcvTafPlmnSrchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcMmcSrchPlmnReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmcInterAnycellSearchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_SndSearchRslt_AnyCellSearch(
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32               enResult
);


VOS_UINT32  NAS_MMC_RcvMmcInterPlmnSearchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitWasPlmnSrchCnfExpired_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitGasPlmnSrchCnfExpired_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitWasStopCnfExpired_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitGasStopCnfExpired_AnyCellSearch_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_RcvLmmPlmnSrchCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSrchCnfExpired_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_AnyCellSearch_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchStopCnf_AnyCellSearch_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_AnyCellSearch_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvLSysInfoInd_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

VOS_VOID NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID NAS_MMC_SndSuspendReq_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID NAS_MMC_GetCoverageRatPrioList_Anycell(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU     *pstInterPlmnSrchReq,
    NAS_MML_PLMN_RAT_PRIO_STRU             *pstRatPrioList
);

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_MMC_IsNeedSndAsSuitableCellSelReq_AnyCellSearch(VOS_VOID);

/* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_IsNeedSndLmmSuitableCellSelReq_AnyCellSearch(VOS_VOID);
#endif
/* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

VOS_UINT32 NAS_MMC_IsNeedRejectAnycellSerach_AnyCellSearch(VOS_VOID);

VOS_VOID NAS_MMC_ProcNoRf_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
);

VOS_VOID NAS_MMC_UpdateRfAvailFlg_AnyCellSearch(VOS_VOID);


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

#endif /* end of NasMmcAnyCellSearch.h */
