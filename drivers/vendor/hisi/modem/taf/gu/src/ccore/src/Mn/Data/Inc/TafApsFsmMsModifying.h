/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmMsModifying.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : TafApsFsmMsModifying.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSFSMMSMODIFYING_H__
#define __TAFAPSFSMMSMODIFYING_H__

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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode(VOS_VOID);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvSmPdpModifyInd_MsModifying_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvAtPsCallModifyReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvAtPsCallAnswerReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvAtPsCallHangupReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_Suspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRsp(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRspSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnf(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnfSuspend(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_VOID TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode(VOS_VOID);

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

#endif /* end of TafApsFsmMsModifying.h */
