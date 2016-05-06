/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcXcc.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年9月3日
  最近修改   :
  功能描述   : TafXCallProcXcc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_X_CALL_PROC_XCC_H__
#define __TAF_X_CALL_PROC_XCC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "VcCallInterface.h"
#include "TafXCallCtx.h"
#include "xcc_xcall_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define TAF_XCALL_MAX_ORIG_REDIAL_COUNT     (0xff)
#endif

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

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_RcvXccCallOrigCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallHangUpCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallDiscInd(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallIncomingInd(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallAnswerCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccCallConnectInd(VOS_VOID *pMsg);
#if 0
VOS_VOID TAF_XCALL_RcvXccSendFlashCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccInfoRecInd(VOS_VOID *pMsg);
#endif

VOS_VOID TAF_XCALL_RcvXccCodecOpenInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccCodecCloseInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccCodecChangedInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccSoCtrlMsgInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccSoCtrlOrderInd(VOS_VOID *pMsg);

VOS_UINT32 TAF_XCALL_MapSoToCodecType(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo,
    CALL_VC_CODEC_TYPE_ENUM_U8         *penCodecType
);

TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_ConvertXccSoToXcallSo(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enXccSo
);

extern VOS_VOID TAF_XCALL_RcvXccSendBurstDTMFCnf(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RcvXccSendFlashCnf(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RscvXccInfoRecInd(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RcvXccInfoRecInd(VOS_VOID *pMsg);

VOS_UINT32 TAF_XCALL_IsNeedSilentRedial(
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);

VOS_UINT32 TAF_XCALL_IsNeedRedialSystemAcquire(
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_INT32                           lRssi
);

VOS_VOID TAF_XCALL_VoiceOrigRedialCount(
    VOS_UINT8                           ucPdpId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer
);


VOS_VOID TAF_XCALL_RcvXccNdssResultInd(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccSendContDTMFCnf(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccBurstDtmfInd(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvXccContDtmfInd(VOS_VOID *pMsg);


VOS_VOID TAF_XCALL_RcvXccTchAssignCmplInd(VOS_VOID *pMsg);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_RcvXccEccServiceCnf(VOS_VOID *pMsg);
#endif

VOS_VOID TAF_XCALL_RcvXccPrivacyModeSetCnf(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccPrivacyModeQryCnf(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvXccPrivacyModeInd(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_ProcPrivacyModeInd(
    VOS_UINT8                           ucCallId,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8    enPrivacyModeSetting
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

#endif /* end of TafXCallProcXcc.h */

