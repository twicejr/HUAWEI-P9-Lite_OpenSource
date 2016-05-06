/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallSendApp.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年04月18日
  最近修改   : 2014年04月18日
  功能描述   : CALL模块发送消息给APP，即AT或STK
  函数列表   :
  修改历史   :
  1.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/
#ifndef  MN_CALL_SEND_APP_H
#define  MN_CALL_SEND_APP_H


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "NasMncc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3类型定义
*****************************************************************************/


/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-09, begin */
VOS_VOID TAF_CALL_SendCallOrigCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            ulErrorCode
);
VOS_VOID TAF_CALL_SendSupsCmdCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            ulErrorCode
);
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-09, end */

VOS_VOID TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    TAF_CS_CAUSE_ENUM_UINT32            ulErrorCode
);

VOS_VOID TAF_CALL_SendDtmfCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_EVENT_ENUM_U32              enEventType,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID MN_CALL_SndStkMtCallEvent(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi
);

VOS_VOID MN_CALL_SndStkCallDiscEvent(
    const VOS_VOID                     *pMsg,
    MNCC_PRIM_NAME_ENUM_U16             enMsgName,
    VOS_BOOL                            bNetMsg
);

VOS_VOID MN_CALL_SndStkCallConnEvent(
    VOS_UINT8                           ucTi,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_SendQueryEcallInfoCnf(
    MN_CLIENT_ID_T                       usClientId,
    MN_OPERATION_ID_T                    ucOpId,
    MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU *pstEcallInfo
);
#endif

VOS_VOID TAF_CALL_SendTafRelCallCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MN_CALL_SEND_CC_H */


