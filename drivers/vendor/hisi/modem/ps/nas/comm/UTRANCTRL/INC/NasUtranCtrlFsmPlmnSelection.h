/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUtranCtrlFsmPlmnSelection.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2012年7月14日
  最近修改   :
  功能描述   : NasUtranCtrlFsmPlmnSelection.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月4日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_UTRANCTRL_FSM_PLMN_SELECTION_H_
#define _NAS_UTRANCTRL_FSM_PLMN_SELECTION_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"


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
VOS_UINT32 NAS_UTRANCTRL_RcvWasPlmnSrchCnf_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvWasRrMmRelInd_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_UTRANCTRL_RcvTdPlmnSrchCnf_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf(VOS_VOID);
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf(
	VOS_UINT32                          ulEventType,
	struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32  NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnfBackTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnfBackW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32 NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW(
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

#endif /* end of NasUtranCtrlFsmPlmnSelection.h */
