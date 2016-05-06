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

#ifndef _TAF_XPDS_CP_FSM_PDE_PROC_H_
#define _TAF_XPDS_CP_FSM_PDE_PROC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafXpdsCommFunc.h"

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
#define TAF_XPDS_PPM_TIMER_FRACTION 2

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

extern VOS_VOID TAF_XPDS_SendSessionEndAndQuitL2Fsm(VOS_VOID);
extern VOS_VOID TAF_XPDS_HandleXpdsCpMsaModePdeOperationNI(VOS_VOID);
extern VOS_VOID TAF_XPDS_HandleXpdsCpMsaModePdeOperationSI(VOS_VOID);
extern VOS_VOID TAF_XPDS_HandleXpdsCpMsbModePdeOperation(VOS_VOID);
extern VOS_UINT32 TAF_XPDS_RcvAtGpsPrmInfoRsp_CpL2Pde_MsaWaitGpsPseudoInfo(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvAtGpsStopReq_L2Pde(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpGeneralTimerTimeout(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterReqLocRsp(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecieveCasCnf(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecieveGpsLocResp(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecievePdeResp(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsCpPdeProcStart_CpL2Pde_Init(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeAssistInfo(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeLocRespInfo(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterMsInfo(
   VOS_UINT32                           ulEventType,
   struct MsgCB                        *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterAquiAssis_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecievePrmReq_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModePPMComplete_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID TAF_XPDS_SendPilotPhaseMeasurement(VOS_VOID);

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


