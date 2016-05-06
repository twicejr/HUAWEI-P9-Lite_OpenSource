/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmMain.h
  版 本 号   : 初稿
  作    者   : h44270
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : TafApsFsmMain.C 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : h44270
    修改内容   : 创建文件

******************************************************************************/

#ifndef _TAF_APS_FSM_MAIN_H
#define _TAF_APS_FSM_MAIN_H

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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvEsmPdpManageInd_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpSetupInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEsmPdpModifyInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
#endif
VOS_UINT32 TAF_APS_RcvApsInternalPdpDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvRabmSysChgToGprs_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvRabmLocalPdpDeactivateReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSetPdpContextStateReq_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpActivateInd_Inactive(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSmPdpModifyInd_Active(
   VOS_UINT32                          ulEventType,
   struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 TAF_APS_RcvPppDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvCdsServiceInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvCdsServiceInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvPsCallOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallEndReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiDormantTimerExpired_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvXccResumeInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmCalConnectInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvTiHrpdLostExpired_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 TAF_APS_RcvPppModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppReConnInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPppDeactInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvHsmDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvPsPppDialOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEHsmPdnDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



VOS_UINT32 TAF_APS_RcvPsInterEnd1xService_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_RcvEhsmPdnInfoChgInd_Active(
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

#endif /* end of _NAS_MMC_FSM_MAIN.h */

