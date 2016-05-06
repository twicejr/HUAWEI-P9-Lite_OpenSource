/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcEccSrv.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年10月21日
  最近修改   :
  功能描述   : TafXCallProcEccSrv.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月21日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_X_CALL_PROC_ECC_SRV_H__
#define __TAF_X_CALL_PROC_ECC_SRV_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include <time.h>                               /* mktime */
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
#define TAF_XCALL_TIME_STAMP_ORIG_YEAR      (1900)
#define TAF_XCALL_TIME_MONTHS_OF_ONE_YEAR   (12)
#define TAF_XCALL_MKTIME_MONTH_OFFSET       (1)
#define TAF_XCALL_STIME_INVALID_VALUE       (0xffffffffffffffffULL)
#define TAF_XCALL_STIME_MAX_INTERVAL_VALUE  (0x1fffffffffffffffULL)
#define TAF_XCALL_TIME_INTERVAL_ONEDAY      (86400)
#define TAF_XCALL_TIME_INTERVAL_5MINUTS     (300)
#define TAF_XCALL_SYSTIME_ORIGINAL_YEAR     (1980)
#define TAF_XCALL_SYSTIME_ORIGINAL_MONTH    (1)
#define TAF_XCALL_SYSTIME_ORIGINAL_DAY      (6)
#define TAF_XCALL_INVALID_HARDWARE_ID       (0xFF)
#define TAF_XCALL_HARDWARE_TYPE_MEID_LEN    (7)
#define TAF_XCALL_HARDWARE_TYPE_ESN_LEN     (4)
#define TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN  (7)
#define TAF_XCALL_IMSI_INFO_LEN             (8)
#define TAF_XCALL_CALLEDNUM_INFO_MAX_LEN    (6)
#define TAF_XCALL_IDENTITY_COMBINE_MAX_LEN  (25)
#define TAF_XCALL_STIME_CONVERT_80MS_TO_1S(n)   (n * 8 / 100)

#define TAF_XCALL_ADDITIONAL_INFO_LENGTH    (6)
#define TAF_XCALL_MAX_ENCRYPT_VOICE_NUM     (11)
#define TAF_XCALL_MAX_ASCII_NUM_LEN         (64)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
结构名      : TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32
结构说明    : 语音加密流程消息事件类型
  1.日    期   : 2015年10月26日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM
{
    /* APP消息事件类型 */
    TAF_XCALL_APP_MSG_EVENT_ENC_VOICE_REQ,
    TAF_XCALL_APP_MSG_EVENT_ORIG_REQ,
    TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,

    /* KMC消息事件 */
    TAF_XCALL_KMC_MSG_EVENT_MO_KEY_RSP,
    TAF_XCALL_KMC_MSG_EVENT_MT_ENCRYPT_IND,
    TAF_XCALL_KMC_MSG_EVENT_MT_KEY_RSP,
    TAF_XCALL_KMC_MSG_EVENT_ERR_IND,

    /* XCC消息事件类型 */
    TAF_XCALL_XCC_MSG_EVENT_INCOMING_CALL_IND,
    TAF_XCALL_XCC_MSG_EVENT_DISC_IND,
    TAF_XCALL_XCC_MSG_EVENT_TCH_ASSIGN_CMPL_IND,
    TAF_XCALL_XCC_MSG_EVENT_ECC_SERVICE_CNF,
    TAF_XCALL_XCC_MSG_EVENT_ANSWER_CALL_CNF,

    /* XSMS消息事件 */
    TAF_XCALL_XSMS_MSG_EVENT_ENC_VOICE_XSMS_SEND_CNF,

    /* 定时器事件 */
    TAF_XCALL_TIMER_MSG_EVENT_WAIT_ORIG_REQ,
    TAF_XCALL_TIMER_MSG_EVENT_DELAY_SEND_ENCRYPT_REQ,
    TAF_XCALL_TIMER_MSG_EVENT_TX01,
    TAF_XCALL_TIMER_MSG_EVENT_TX02,

    /* XCALL内部事件类型: 如冲突场景导致的呼叫释放 */
    TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,

    TAF_XCALL_VOICE_ENC_MSG_EVENT_MAX
};
typedef VOS_UINT32 TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32
结构说明    : 公钥更新消息事件类型
  1.日    期   : 2015年10月26日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM
{
    /* KMC消息事件 */
    TAF_XCALL_KMC_MSG_EVENT_PUB_KEY_UPDATE_IND,                                                     /* KMC公钥更新 */
    TAF_XCALL_KMC_MSG_EVENT_PUB_KEY_UPDATE_ACK,                                                     /* KMC公钥更新确认 */

    /* XSMS消息事件 */
    TAF_XCALL_XCC_MSG_EVENT_PUB_KEY_UPDATE_XSMS_SEND_CNF,

    /* 定时器事件 */
    TAF_XCALL_TIMER_MSG_EVENT_PUB_KEY_UPDATE_WAIT_ACK,

    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_MAX
};
typedef VOS_UINT32 TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32
结构说明    : KMC远程控制操作消息事件类型
  1.日    期   : 2015年10月26日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM
{
    /* APP消息事件类型 */
    TAF_XCALL_APP_MSG_EVENT_REMOTE_CTRL_ANSWER_REQ,                                                 /* KMC远程控制指令用户应答 */

    /* KMC远程控制状态机相关事件 */
    TAF_XCALL_KMC_MSG_EVENT_ROMOTE_CTRL_CMD_IND,                                                    /* KMC远程控制指令 */

    /* XSMS消息事件 */
    TAF_XCALL_XCC_MSG_EVENT_ROMOTE_CTRL_XSMS_SEND_CNF,                                              /* KMC远程控制指令响应发送确认 */

    /* 定时器事件 */
    TAF_XCALL_TIMER_MSG_EVENT_REMOTE_CTRL_WAIT_AP_ANSWER,                                           /* KMC远程控制指令用户应答定时器超时 */

    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_MAX
};
typedef VOS_UINT32 TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32;


/*****************************************************************************
结构名      : TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32
结构说明    : ECC状态机ID
  1.日    期   : 2015年10月26日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
enum TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM
{
    TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC,

    TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE,

    TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL,

    TAF_XCALL_ECC_STATE_MACHINE_ID_BUTT
};
typedef VOS_UINT32 TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32;

/*****************************************************************************
结构名      : TAF_XCALL_HARDWARE_ID_TYPE_ENUM_UINT8
结构说明    : Hard Ware Id对应的存储类型
  1.日    期   : 2015年10月26日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
enum TAF_XCALL_HARDWARE_ID_TYPE_ENUM
{
    TAF_XCALL_HARDWARE_ID_TYPE_ESN      = 0x01,
    TAF_XCALL_HARDWARE_ID_TYPE_MEID     = 0x10,

    TAF_XCALL_HARDWARE_ID_TYPE_BUTT
};
typedef VOS_UINT8 TAF_XCALL_HARDWARE_ID_TYPE_ENUM_UINT8;



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
/* 动作处理函数的类型定义 */
typedef VOS_VOID (*TAF_XCALL_ECC_EVENT_PROC_FUNC)(VOS_VOID *pMsg, VOS_VOID *pKmcDecMsg);

/*****************************************************************************
 结构名    : TAF_XCALL_ECC_EVENT_PROC_STRU
 结构说明  : ECC事件处理函数处理结构

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;                            /* 事件类型 */
    TAF_XCALL_ECC_EVENT_PROC_FUNC       pfEventProcFun;                         /* 事件处理函数 */
}TAF_XCALL_ECC_EVENT_PROC_STRU;
/*****************************************************************************
 结构名    : TAF_XCALL_MKTIME_TM_STRU
 结构说明  : TimeZone类型的时间结构

 修改记录  :
  1.日    期   : 2015年10月24日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
typedef struct tm TAF_XCALL_MKTIME_TM_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_STD_TIME_ZONE_STRU
 结构说明  : TimeZone类型的时间结构

 修改记录  :
  1.日    期   : 2015年10月24日
    作    者   : h00313353
    修改内容   : Iteration 19

*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSecond;   /* 秒[0,59] */
    VOS_UINT32                          ulMinute;   /* 分[0,59] */
    VOS_UINT32                          ulHour;     /* 小时[0,23] */
    VOS_UINT32                          ulDay;      /* 一月中的第几天[1,31] */
    VOS_UINT32                          ulMonth;    /* 月[0,11] */
    VOS_UINT32                          ulYear;     /* 从1900年起的年数 */
    VOS_UINT32                          ulWday;     /* 一周中的第几天[0,6] */
    VOS_UINT32                          ulYday;     /* 一年中的第几天[0,365] */
    VOS_UINT32                          ulIsdst;    /* 夏令时 */
} TAF_XCALL_STD_TIME_ZONE_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_HARDWARE_ID_INFO_STRU
 结构说明  : HARDWARE ID信息结构体

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucHardWareIdLen;
    TAF_XCALL_HARDWARE_ID_TYPE_ENUM_UINT8   enHardWareType;
    VOS_UINT8                               aucHardWareIdInfo[TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN];
    VOS_UINT8                               aucReserved[3];
} TAF_XCALL_HARDWARE_ID_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_XCALL_PLAIN_TEXT_INFO_STRU
 结构说明  : ID信息明文信息组合结构体

 修改历史      :
  1.日    期   : 2015年10月27日
    作    者   : h00313353
    修改内容   : Iteration 19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumLen;
    VOS_UINT8                           aucContent[TAF_XCALL_IDENTITY_COMBINE_MAX_LEN];
    VOS_UINT8                           aucReserved[2];
} TAF_XCALL_PLAIN_TEXT_INFO_STRU;
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
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_UINT16 TAF_XCALL_GetSendXsmsReqOpId(VOS_VOID);
VOS_VOID TAF_XCALL_ProcEccEvent(
    VOS_UINT32                                              ulEventType,
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32          enStateMachine,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcKmcKsNegotiateProcedure(
    TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32          enEvent,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcKmcPublicKeyUpdateProcedure(
    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32     enEvent,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcKmcRemoteControlProcedure(
    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32        enEvent,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ExitVoiceEncriptProcedure(VOS_VOID);

VOS_VOID TAF_XCALL_ExitPubKeyUpdateProcedure(VOS_VOID);

VOS_VOID TAF_XCALL_ExitRemoteCtrlOpertionProcedure(VOS_VOID);

VOS_UINT32 TAF_XCALL_VerifySignature(
    VOS_UINT8                           ucPubKeyLen,
    VOS_UINT8                          *pucPubKey,
    VOS_UINT8                           ucSignInfoLen,
    VOS_UINT8                          *pucSignInfo,
    VOS_UINT8                           ucSignDataLen,
    VOS_UINT8                          *pucSignData
);

VOS_UINT32 TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(
    VOS_UINT8                                               ucCallNumLen,
    VOS_UINT8                                              *pucCallNum,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstEccRemoteNum
);
VOS_VOID TAF_XCALL_ProcMoAutoModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
);

VOS_VOID TAF_XCALL_ProcMtAutoModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
);

VOS_VOID TAF_XCALL_ProcMoManualModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
);

VOS_VOID TAF_XCALL_ProcMtManualModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventAppEncVoiceReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventAppOrigReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventAppHangUpReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMoKeyRsp(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMtEncryptInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMtKeyRsp(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcErrInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventIncomingCallInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventXccDiscInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventXccTchAssignCmplInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventXccEccServiceCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventXccAnswerCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerWaitOrigReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerDelaySendEncReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerTx01(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerTx02(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcVoiceEncEventIntCallRelInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcPubKeyEventKmcUpdateInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcPubKeyEventKmcUpdateAck(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcPubKeyEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcRemoteCtrlEventAppRemoteCtrlAnswerReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcRemoteCtrlEventKmcRemoteCtrlCmdInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcRemoteCtrlEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_ProcRemoteCtrlEventTimerWaitApAnswer(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_UINT32 TAF_XCALL_IsMkTimeParaValid(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone
);

VOS_UINT32 TAF_XCALL_GetTimeIntervalSince1970(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone,
    VOS_UINT64                         *pullTimeInterval
);

VOS_UINT32 TAF_XCALL_ConvertCurSysTime80msToStdTimeIntervalSince1970(
    VOS_UINT64                          ullCurSysTime,
    VOS_UINT64                         *pullStdSysTime
);

VOS_UINT32 TAF_XCALL_IsTimeZoneEmpty(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone
);

VOS_UINT32 TAF_XCALL_IsTimeStampValid(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeStamp,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstLastSysTimeZone
);

VOS_UINT32 TAF_XCALL_GenerateEncVoicePlainText(
    VOS_UINT8                                              *pucImsiInfo,
    TAF_XCALL_HARDWARE_ID_INFO_STRU                        *pstHardWareId,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstCalledNum,
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                         *pstPlainTextInfo
);

VOS_UINT32 TAF_XCALL_SendRemoteCtrlEventRsltToKmc(
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlCmdType,
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enRemoteCtrlRsltType,
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx
);

VOS_UINT32 TAF_XCALL_GetHardWareInfo(
    TAF_XCALL_HARDWARE_ID_INFO_STRU                        *pstHardWareIdInfo
);

VOS_UINT32 TAF_XCALL_FillKmcUpdateRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
);

VOS_UINT32 TAF_XCALL_SendKmcUpdateRspMsg(
    VOS_UINT16                          usOpId,
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
);

VOS_UINT32 TAF_XCALL_IsCallingNumExist(
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity
);

VOS_UINT32 TAF_XCALL_FillKmcReqMsgCipherText(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
);

VOS_UINT32 TAF_XCALL_ConvertRemoteNumFromStdBcdToKmcBcd(
    VOS_UINT8                          *pucStdBcdContent,
    VOS_UINT8                           ucStdBcdLen,
    VOS_UINT8                          *pucEncVoiceMsgContent,
    VOS_UINT8                           ucEncVoiceMsgLen
);

VOS_UINT32 TAF_XCALL_ConvertImsiFromStdBcdToKmcBcd(
    VOS_UINT8                          *pucStdImsiContent,
    VOS_UINT8                          *pucEncVoiceImsiContent,
    VOS_UINT8                           ucEncVoiceImsiLen
);

VOS_UINT8 TAF_XCALL_ConvertRemoteNumFromKmcBcdToStdBcd(
    VOS_UINT8                          *pucKmcBcdNum,
    VOS_UINT8                           ucKmcBcdNumLen,
    VOS_UINT8                          *pucStdBcdNum,
    VOS_UINT8                           ucStdBcdNumLen
);

VOS_VOID TAF_XCALL_ProcPubKeyEventTimerWaitAck(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
);

VOS_VOID TAF_XCALL_FillAdditionalInfo(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
);


TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32 TAF_XCALL_SendKmcKeyReqMsg(
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
);
VOS_VOID TAF_XCALL_FillKmcKeyReqMsgTypeAndMode(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
);
#endif
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

#endif /* end of TafXCallProcXsms.h */

