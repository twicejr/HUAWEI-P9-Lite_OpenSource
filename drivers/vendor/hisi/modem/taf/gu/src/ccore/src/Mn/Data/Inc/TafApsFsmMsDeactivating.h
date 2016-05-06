/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmDeactivating.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : TafApsFsmDeactivating.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_APS_FSM_MSDEACTIVATING_H__
#define __TAF_APS_FSM_MSDEACTIVATING_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafSmInterface.h"


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
VOS_VOID TAF_APS_RcvAtPsCallEndReq_MsDeactivating_GuMode(
    SM_TAF_CAUSE_ENUM_UINT16            enCause
);
VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_GuMode(
    SM_TAF_CAUSE_ENUM_UINT16            enCause
);
VOS_VOID TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_GuMode(
    SM_TAF_CAUSE_ENUM_UINT16            enCause
);

VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Init(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Init(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmAbortCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_Suspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvInterServiceStaChangeInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpAbortCnf_MsDeactivating_WaitSmAbortCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmAbortCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);

VOS_VOID TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_GuMode(VOS_VOID);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitEsmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitEsmDeactivateCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_LteMode(VOS_VOID);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpReleaseCnf_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateCnf_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateRej_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitL4aDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitL4aDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpReleaseCnf_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateCnf_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateRej_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitEsmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_LteMode(VOS_VOID);
VOS_VOID TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode(VOS_VOID);
VOS_VOID TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_LteMode(VOS_VOID);
VOS_VOID TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_LteMode( VOS_VOID );
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_APS_RcvAtPsCallEndReq_MsDeactivating_LteMode_ReserveDef(VOS_VOID);

VOS_VOID TAF_APS_ProcLocDeactBear_MsDeactivating_LteMode(VOS_VOID);

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

#endif /* end of TafApsFsmDeactivating.h */
