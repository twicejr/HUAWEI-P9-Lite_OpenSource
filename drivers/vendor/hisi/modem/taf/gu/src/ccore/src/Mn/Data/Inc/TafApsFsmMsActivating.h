/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmMsActivating.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : TafApsFsmMsActivating.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_APS_FSM_MSACTIVATING_H__
#define __TAF_APS_FSM_MSACTIVATING_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


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

VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsCallOrigReq_MsActivating_GuMode(VOS_VOID);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_GuMode(VOS_VOID);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_GuMode(VOS_VOID);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpActSecCnf_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpActSecRej_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReqMsgType_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsActivating_GuMode(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpSetupCnf_MsActivate_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmNdisconnCnf_MsActivate_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpActivateCnf_MsActivate_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    APP_ESM_PDP_SETUP_CNF_STRU         *pstEsmPdpSetupCnf
);
VOS_UINT32 TAF_APS_RcvEsmPdpActivateRej_MsActivate_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    APP_ESM_PDP_SETUP_CNF_STRU         *pstEsmPdpActivateRej
);
VOS_UINT32 TAF_APS_RcvEsmPdpSetupCnfRej_MsActivate_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmNdisconnCnfRej_MsActivate_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode(VOS_VOID);
VOS_VOID TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode(VOS_VOID);
VOS_VOID TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode(VOS_VOID);
#endif

VOS_UINT32 TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitSmActivateCnfSuspend(
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

#endif /* end of TafApsFsmMsActivating.h */
