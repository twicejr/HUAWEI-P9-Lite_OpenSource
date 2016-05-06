/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallSndXcc.h
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年9月3日
  最近修改   :
  功能描述   : TafXCallSndXcc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_X_CALL_SND_XCC_H__
#define __TAF_X_CALL_SND_XCC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
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
#define TAF_XCALL_CALL_NUM_TYPE_VALID_BIT         (0x70)
#define TAF_XCALL_CALL_PLAN_TYPE_VALID_BIT        (0x0F)


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
VOS_VOID TAF_XCALL_SndXccOrigCallReq(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndXccAnswerCallReq(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndXccHangUpCallReq(
    VOS_UINT8                           ucCallId,
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
);

VOS_VOID TAF_XCALL_SndXccIncomingCallRsp(
    XCC_XCALL_RESULT_ENUM_UINT32        enRslt,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
);

VOS_VOID TAF_XCALL_BuildOrigCallPara(
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigPara,
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_BuildCallingNum(
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU  *pstCallingNum,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
);

VOS_VOID TAF_XCALL_BuildCallingSubAddr(
    XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity
);

VOS_VOID TAF_XCALL_BuildCalledNum(
    XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU   *pstCalledNum,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
);

VOS_VOID TAF_XCALL_BuildCalledSubAddr(
    XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity
);

extern VOS_UINT32 TAF_XCALL_SndXccFlashReq(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucDigitNum,
    VOS_UINT8                          *pucDigits,
    VOS_UINT8                           ucIsEmcCall
);

extern TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SndXccBurstDTMFReq(
    TAF_CALL_BURST_DTMF_PARA_STRU      *pstBurstDtmfInfo
);


extern TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SndXccContDTMFReq(
    TAF_CALL_CONT_DTMF_PARA_STRU      *pstContDtmfInfo
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_SendEccServiceReq(VOS_VOID);
#endif

VOS_VOID TAF_XCALL_SendPrivacyModeSetReq(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8   enPrivacyMode,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_VOID TAF_XCALL_SendPrivacyModeQryReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
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

#endif /* end of TafXCallSndXcc.h */

