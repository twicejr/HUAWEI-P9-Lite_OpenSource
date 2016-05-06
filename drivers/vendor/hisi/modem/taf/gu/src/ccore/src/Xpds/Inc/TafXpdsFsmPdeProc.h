/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmPdeProc.h
  版 本 号   : 初稿
  作    者   : y00174758
  生成日期   : 2015年8月24日
  功能描述   : TafXpdsFsmPdeProc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年8月24日
    作    者   : y00174758
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XPDS_FSM_PDE_PROC_H_
#define _TAF_XPDS_FSM_PDE_PROC_H_

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
VOS_UINT32 TAF_XPDS_RcvXpdsPdeProcStartReq_L2Pde_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeAssistInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitPdeAssistInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvAtGpsPrmInfoRsp_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiPrmInfoRspExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitGpsPrecisionPseudoRangeExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitGpsPseudoRangeCnfExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeLocRespInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsbWaitPdeData(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvTiWaitPdeMsbDataExpired_L2Pde_MsbWaitPdeData(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_XPDS_RcvXpdsAbnormalAbortSessionInd_L2Pde(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_XPDS_ProcEphData_L2Pde_MsbWaitPdeData(VOS_VOID);

VOS_VOID TAF_XPDS_ProcAlmData_L2Pde_MsbWaitPdeData(VOS_VOID);

VOS_VOID TAF_XPDS_ProcQuitL2Pde_L2Pde(VOS_VOID);

VOS_VOID TAF_XPDS_StopAllL2PdeTimer_L2Pde(VOS_VOID);

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


