/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmRedial.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2013年12月12日
  最近修改   :
  功能描述   : TafSpmRedial.h的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月12日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SPM_Redial_H_
#define _TAF_SPM_REDIAL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "TafTypeDef.h"
#include "MnCallApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_SPM_IS_VIDEO_CALL(CallType)                 \
            ((MN_CALL_TYPE_VIDEO_TX    == CallType)     \
          || (MN_CALL_TYPE_VIDEO_RX    == CallType)     \
          || (MN_CALL_TYPE_VIDEO       == CallType))    \


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
VOS_UINT8 TAF_SPM_IsCallRedialCauseValueFromImsDomain(TAF_CS_CAUSE_ENUM_UINT32 enCause);

VOS_UINT8 TAF_SPM_IsCsCallRedialAllowed(MN_CALL_INFO_STRU *pstCallInfo);

VOS_VOID TAF_SPM_FreeCallRedialBufferWithClientId(MN_CLIENT_ID_T usClientId);

VOS_VOID TAF_SPM_FreeCallRedialBufferWithCallId(MN_CALL_ID_T ucCallId);

TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetCallRedialBufferWithCallId(MN_CALL_ID_T ucCallId);

TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSmsRedialBufferWithClientId(
    VOS_UINT8                          *pucIndex,
    MN_CLIENT_ID_T                      usClientId
);

VOS_VOID TAF_SPM_UpdateCallRedialBufferMsgWithCallId(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_ID_T                        ucCallId
);

VOS_VOID TAF_SPM_UpdateCallRedialBufferMsgWithCallType(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_TYPE_ENUM_U8                enDestCallType,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmcCat
);


VOS_UINT8 TAF_SPM_StoreMsgIntoCallRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 TAF_SPM_StoreMsgIntoSmsRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 TAF_MSG_IsSmsRedialCauseValueFromImsDomain(SMR_SMT_ERROR_ENUM_UINT32 enCause);

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

#endif /* _TAF_SPM_REDIAL_H_ end */

