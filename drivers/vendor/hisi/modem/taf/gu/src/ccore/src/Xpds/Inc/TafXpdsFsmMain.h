/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmMain.h
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2015年8月24日
  功能描述   : TafXpdsFsmMain.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月26日
    作    者   : g0025631
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XPDS_FSM_MAIN_H_
#define _TAF_XPDS_FSM_MAIN_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafXpdsCtx.h"

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
VOS_UINT32 TAF_XPDS_RcvAtGpsStartReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsCfgMpcAddrReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPdeAddrReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPositionModeReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsReplyNiReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsQryTimeInfoReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsBindServerCnf_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsMpcProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsPdeProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsPosInfoRsp_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsAbnormalAbortAgpsSessionInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiPosReportExpired_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvCasPdeDataInd_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXccIncomingInd_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvCasPdeDataInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvCpXpdsPdeProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvCpXpdsLinkProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiDataIndWaitExpired_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_XPDS_ProcNiCancelPos(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enProcRslt
);

VOS_VOID TAF_XPDS_ProcAtGpsStopReq(VOS_VOID);

VOS_VOID TAF_XPDS_ProcServerBindRsltSucc_NoLink(VOS_VOID);

VOS_VOID TAF_XPDS_ProcServerBindRsltSucc(VOS_VOID);

VOS_UINT32 TAF_XPDS_ProcTrackingMpcConnectFail(VOS_VOID);

VOS_VOID TAF_XPDS_RestartPosProc(VOS_VOID);

VOS_VOID TAF_XPDS_ProcMpcRsltSucc(VOS_VOID);

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
