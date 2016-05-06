/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcApp.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年9月3日
  最近修改   :
  功能描述   : TafXCallProcApp.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_X_CALL_PROC_APP_H__
#define __TAF_X_CALL_PROC_APP_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "TafXCallCtx.h"
#include "xcc_xcall_pif.h"
#include "hi_list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_XCALL_ECC_RANDOM_LEN                            (16)

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
VOS_VOID TAF_XCALL_RcvAppCallOrigReq(VOS_VOID *pMsg);

VOS_VOID TAF_XCALL_RcvAppSupsCmdReq(VOS_VOID *pMsg);

#if 0
VOS_VOID TAF_XCALL_RcvAppSendFlashReq(VOS_VOID *pMsg);
#endif

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelHoldOrUdubReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelCallXReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdRelAllCallReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);

VOS_VOID TAF_XCALL_ProcCallSupsCmdHoldActAcptOthReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppCallSupsReq
);


extern VOS_VOID TAF_XCALL_RcvAppSendBurstDTMFReq(VOS_VOID *pMsg);

extern VOS_VOID TAF_XCALL_RcvAppSendFlashReq(VOS_VOID *pMsg);

/* Buffer操作函数从XCallProcApp挪到XCallCtx.c中 */


VOS_VOID TAF_XCALL_RcvAgentGetCallInfoReq(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvAppGetCallInfoReq(VOS_VOID *pMsg);
VOS_VOID TAF_XCALL_RcvAppXlemaReq(VOS_VOID *pMsg);


VOS_VOID TAF_XCALL_RcvAppCustomDialReq(VOS_VOID *pMsg);

VOS_UINT32 TAF_XCALL_GetRedialPeriodTimerLen(
    VOS_UINT8                           ucCallId
);


VOS_VOID TAF_XCALL_RcvAppSendContDTMFReq(VOS_VOID *pMsg);


VOS_VOID TAF_XCALL_ReplaceFlashPlusWithDigit(
    VOS_UINT8                           ucSrcDigitNum,
    VOS_UINT8                          *pucSrcDigit,
    VOS_UINT8                          *pucDstDigitNum,
    VOS_UINT8                          *pucDstDigit
);

VOS_VOID TAF_XCALL_RcvAtCclprGetReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccNumSetReq(
    VOS_VOID                           *pMsg
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_RcvAppEncryptVoiceReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppRemoteCtrlAnswerReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccSrvCapCfgReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccSrvCapQryReq(VOS_VOID *pstMsg);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
VOS_VOID TAF_XCALL_RcvAppEccTestModeCfgReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccTestModeQryReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccKmcKeyCfgReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccKmcKeyQryReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppEccRandomQryReq(VOS_VOID *pstMsg);
#endif
#endif

VOS_VOID TAF_XCALL_RcvAppPrivacyModeSetReq(VOS_VOID *pstMsg);

VOS_VOID TAF_XCALL_RcvAppPrivacyModeQryReq(VOS_VOID *pstMsg);
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

#endif /* end of TafXCallProcApp.h */

