/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmNwActivating.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : TafApsFsmNwActivating.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSFSMNWACTIVATING_H__
#define __TAFAPSFSMNWACTIVATING_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


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

VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsCallAnswerReq_NwActivating_GuMode(struct MsgCB *pstMsg);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvEsmPdpManageInd_NwActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvEsmPdpManageInd_NwActivating_LteMode(VOS_VOID);
VOS_VOID TAF_APS_RcvAtPsCallAnswerReq_NwActivating_LteMode(struct MsgCB *pstMsg);
#endif
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSetPdpContextStateReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSmPdpActRej_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSmPdpActSecRej_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvSmPdpActCnf_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode(VOS_VOID);
VOS_VOID TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode_AutoAns(
    VOS_UINT8                           ucAnswerType,
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmPdpActivateInd
);
VOS_VOID TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode_ManualAns(
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmPdpActivateInd
);
VOS_UINT32 TAF_APS_RcvSmPdpActivateInd_NwActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSmActivateCnf(
           VOS_UINT32                          ulEventType,
           struct MsgCB                       *pstMsg
       );
VOS_UINT32 TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsCallHangUpReq_NwActivating_GuMode(struct MsgCB *pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvL4aSetCgansCnf_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsCallHangUpReq_NwActivating_LteMode(struct MsgCB *pstMsg);

#endif
VOS_UINT32 TAF_APS_RcvSmPdpActSecCnf_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_SndPdpDisconnectInd(VOS_UINT8 ucPdpId);

VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer_GuMode(struct MsgCB *pstMsg);

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

#endif /* end of TafApsFsmNwActivating.h */
