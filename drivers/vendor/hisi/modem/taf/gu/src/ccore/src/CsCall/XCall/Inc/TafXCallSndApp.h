/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallSndApp.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年9月3日
  最近修改   :
  功能描述   : TafXCallSndApp.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_X_CALL_SND_APP_H__
#define __TAF_X_CALL_SND_APP_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "xcc_xcall_pif.h"
#include "TafAppCall.h"
#include "TafXCallCtx.h"

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

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_SndCsEvtToAt(
    VOS_UINT32                          ulEvtId,
    VOS_UINT16                          usClientId,
    VOS_UINT16                          usLength,
    VOS_VOID                           *pData
);

VOS_VOID TAF_XCALL_SndCsEvtToStk(
    VOS_UINT32                          ulEvtId,
    VOS_UINT32                          ulModuleId,
    MN_CALL_INFO_STRU                  *pstCallInfo
);

VOS_VOID TAF_XCALL_SndCallOrigCnf(
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientid,
    MN_CALL_TYPE_ENUM_U8                enCallType
);


VOS_VOID TAF_XCALL_SndSupsCmdCnf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_XCALL_SndSupsResult(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);

VOS_VOID TAF_XCALL_SndCallIncomingInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndCallOrigInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndCallConnectInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndCallReleaseInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndCallAllReleaseInd(
    VOS_UINT32                          ulModuleId
);

extern VOS_VOID TAF_XCALL_SndCalledNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndCallingPratNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndConnNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndRedirNumInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndDisplayInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndExtDisplayInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndLineCtrlInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndSignalInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndCCWACInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndCallingNumSignalInfoInd(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
);

extern VOS_VOID TAF_XCALL_SndFlashRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
);

extern VOS_VOID TAF_XCALL_SndBurstDTMFRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
);

extern VOS_VOID TAF_XCALL_SndBurstDTMFCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult,
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndXlemaCnf(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
);

extern VOS_VOID TAF_XCALL_SndContDTMFCnf(
    VOS_UINT16                                  usClientId,
    VOS_UINT8                                   ucOpId,
    TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8  enResult,
    VOS_UINT8                                   ucCallId
);

extern VOS_VOID TAF_XCALL_SndContDTMFRslt(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucResult
);



VOS_VOID TAF_XCALL_SndBurstDTMFInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    XCC_XCALL_BURST_DTMF_IND_STRU      *pstBurstDtmfInd
);
VOS_VOID TAF_XCALL_SndContDTMFInd(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    XCC_XCALL_CONT_DTMF_IND_STRU       *pstContDtmfInd
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_SndAppEncryptVoiceCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceStatus
);

VOS_VOID TAF_XCALL_SndAppEncryptVoiceInd(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceStatus,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstCallingNumber
);

VOS_VOID TAF_XCALL_SndAppRemoteCtrlInd(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_REMOTE_CTRL_APP_TYPE_ENUM_UINT32               enRemoteCtrlType
);

VOS_VOID TAF_XCALL_SndAppRemoteCtrlAnswerCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_REMOTE_CTRL_OPER_RESULT_ENUM_UINT32            enResult
);

VOS_VOID TAF_XCALL_SndAppEccSrvCapCfgCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_ECC_SRV_CAP_CFG_RESULT_ENUM_UINT32         enResult
);

VOS_VOID TAF_XCALL_SndAppEccSrvCapQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_ECC_SRV_CAP_ENUM_UINT32                    enEccSrvCap,
    TAF_CALL_APP_ECC_SRV_STATUS_ENUM_UINT32                 enEccSrvStatus
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
VOS_VOID TAF_XCALL_SndTestModeCfgCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    VOS_UINT32                                              ulResult
);

VOS_VOID TAF_XCALL_SndTestModeQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_SET_EC_TEST_MODE_ENUM_UINT32               enTestMode,
    VOS_UINT32                                              ulResult
);

VOS_VOID TAF_XCALL_SndKmcKeyCfgCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    VOS_UINT32                                              ulResult
);

VOS_VOID TAF_XCALL_SndKmcKeyQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstEccPubKeyInfo,
    VOS_UINT32                                              ulResult
);

VOS_VOID TAF_XCALL_SndRandomQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    VOS_UINT8                                               ucEccRandomSize,
    TAF_CALL_APP_EC_RANDOM_DATA_STRU                       *pstEccRandom,
    VOS_UINT32                                              ulResult
);

VOS_VOID TAF_XCALL_SndEncryptedVoiceDataInd(
    VOS_INT8                                               *pscData,
    VOS_UINT32                                              ulDataLen
);

#endif
#endif

VOS_VOID TAF_XCALL_SndAppPrivacyModeSetCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_APP_RESULT_TYPE_ENUM_UINT32                    enResult
);

VOS_VOID TAF_XCALL_SndAppPrivacyModeQryCnf(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyMode,
    VOS_UINT8                                               ucCallNums,
    TAF_CALL_CALL_PRIVACY_MODE_INFO_STRU                   *pstCallPrivacyModeInfo
);

VOS_VOID TAF_XCALL_SndAppPrivacyModeInd(
    TAF_CCA_CTRL_STRU                                      *pstCtrl,
    VOS_UINT8                                               ucCallId,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enCallPrivacyMode,
    TAF_CALL_PRIVACY_MODE_ENUM_UINT8                        enPrivacyModeSetting
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

#endif /* end of TafXCallSndApp.h */

