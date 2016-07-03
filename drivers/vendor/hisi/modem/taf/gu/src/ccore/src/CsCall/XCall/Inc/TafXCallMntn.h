

#ifndef __TAF_X_CALL_MNTN_H__
#define __TAF_X_CALL_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"


#include "TafMntn.h"
#include "TafXCallCtx.h"
#include "TafXCallKmcCommType.h"
#include "TafXCallProcEccSrv.h"
#include "TafSdcCtx.h"
#include "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_XCALL_MNTN_LOG_KMC_MSG_MAX_KMC_PUB_KEY_LEN    (48)
#define TAF_XCALL_MNTN_LOG_MEID_LEN                       (7)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


enum TAF_XCALL_MNTN_MSG_ID_ENUM
{
    ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND   = ID_TAF_MNTN_XCALL_BASE,             /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_CALL_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT,                                        /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU*/
    ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD,
    ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL,                    /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU*/

    ID_TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION,                                /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_INFO,                        /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_INFO,                           /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME,                        /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME,                      /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO,                              /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ,                                   /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU */
    ID_TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP,                                   /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND,                               /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU */
    ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ,                                   /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU */
    ID_TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP,                                   /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND,                                      /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND,                           /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP,                           /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK,                           /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND,                          /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU */
    ID_TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP,                          /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO,                      /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO,                       /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO,                    /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO,                                      /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU */

    ID_TAF_XCALL_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32;


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

typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_CALL_ENTITY_STRU          astCallEntity[TAF_XCALL_CALL_ENTITY_MAX_NUM];
}TAF_XCALL_MNTN_LOG_CALL_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_SUPS_CMD_MGMT_STRU        stSupsCmdMgmt;
}TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulEmcRedialPeriod;                      /* 紧急呼重拨定时器时长 */
} TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulStartAndStopContDtmfInterval;         /* Stop Cont DTMF 和Start Cont DTMF消息发送间隔定时器时长 */
} TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU;

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_STD_TIME_ZONE_TYPE_STRU         stMsgTimeZone;                          /* 消息中带的时间类型结构体 */
    TAF_STD_TIME_ZONE_TYPE_STRU         stLastTimeZone;                         /* 系统记录的操作时间结构体 */
    VOS_UINT64                          ullStdSysTimeInterval;                  /* 当前系统时间间隔 */
    VOS_UINT64                          ullStdLastTimeInterval;                 /* 当前系统记录的时间间隔 */
    VOS_UINT64                          ullStdMsgTimeInterval;                  /* 消息中带的时间间隔 */
} TAF_XCALL_MNTN_LOG_TIME_STAMP_VALIDATION_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT8                           ucVerNum;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucPubKey[TAF_XCALL_MNTN_LOG_KMC_MSG_MAX_KMC_PUB_KEY_LEN];
} TAF_XCALL_MNTN_LOG_VOICEENC_PUB_KEY_AND_VER_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT8                           ucEccSrvCap;        /* ECC服务能力: TRUE -- 支持ECC服务，FALSE -- 不支持ECC服务 */
    VOS_UINT8                           ucEccSrvStatus;     /* ECC服务状态: TRUE -- ECC服务打开，FALSE -- ECC服务关闭 */
    VOS_UINT8                           aucReserved[2];
} TAF_XCALL_MNTN_LOG_VOICEENC_CAP_CFG_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_XCALL_MNTN_LOG_VOICEENC_LAST_INFO_ERASE_TIME_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT16                          usYear;     /* Year [1980..2100) */
    VOS_UINT16                          usMonth;    /* Month of year [1..12] */
    VOS_UINT16                          usDay;      /* Day of month [1..31] */
    VOS_UINT16                          usHour;     /* Hour of day [0..23] */
    VOS_UINT16                          usMinute;   /* Minute of hour [0..59] */
    VOS_UINT16                          usSecond;   /* Second of minute [0..59] */
} TAF_XCALL_MNTN_LOG_VOICEENC_LAST_PASSWD_RESET_TIME_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT16                          usDelayEncVoiceReqTimerlen;             /* 延迟时长 */
    VOS_UINT16                          usRemoteCtrlAnswerTimerLen;             /* 远程控制应答时长 */
} TAF_XCALL_MNTN_LOG_VOICEENC_TIMER_CFG_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU              stMoKeyReq;                     /* 主叫密钥请求 */
} TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* 处理结果 */
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU              stMoKeyRsp;                     /* 主叫密钥响应 */
} TAF_XCALL_MNTN_LOG_MO_KMC_MSG_KEY_RSP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* 处理结果 */
    TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU       stMtEncryptInd;                 /* 被叫加密通知消息 */
} TAF_XCALL_MNTN_LOG_KMC_MSG_MT_ENCRYPT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU              stMtKeyReq;                     /* 被叫密钥请求 */
} TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* 处理结果 */
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU              stMtKeyRsp;                     /* 被叫密钥响应 */
} TAF_XCALL_MNTN_LOG_MT_KMC_MSG_KEY_RSP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* 处理结果 */
    TAF_XCALL_KMC_MSG_ERR_IND_STRU              stErrInd;                       /* 错误通知 */
} TAF_XCALL_MNTN_LOG_KMC_MSG_ERR_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* 处理结果 */
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU   stPubKeyUpdateInd;              /* KMC公钥更新 */
} TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU   stPubKeyUpdateRsp;              /* KMC公钥更新响应 */
} TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* 处理结果 */
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU   stPubKeyUpdateAck;              /* KMC公钥更新确认 */
} TAF_XCALL_MNTN_LOG_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32  enRslt;                         /* 处理结果 */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU  stRemoteCtrlInd;                /* 远程控制指令 */
} TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32           enMsgId;                        /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU  stRemoteCtrlRsp;                /* 远程控制指令响应 */
} TAF_XCALL_MNTN_LOG_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32      enStateMachine;             /* 状态机名称 */
    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32    enEventType;
    TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32               enState;
} TAF_XCALL_MNTN_LOG_VOICEENC_REMOTE_CTRL_STATE_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32      enStateMachine;             /* 状态机名称 */
    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32 enEventType;
    TAF_XCALL_K0_UPATE_STA_ENUM_UINT32                  enState;
} TAF_XCALL_MNTN_LOG_VOICEENC_KEY_UPDATE_STATE_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32      enStateMachine;             /* 状态机名称 */
    TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32      enEventType;
    TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32             enState;
} TAF_XCALL_MNTN_LOG_VOICEENC_VOICE_ENCRYPT_STATE_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32       enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT8                               aucImsi[TAF_SDC_MAX_IMSI_LEN];
    VOS_UINT8                               aucMeId[TAF_XCALL_MNTN_LOG_MEID_LEN];
    VOS_UINT32                              ulEsn;
    TAF_ECC_CALL_BCD_NUM_STRU               stCalledNum;
    TAF_XCALL_PLAIN_TEXT_INFO_STRU          stPlainTextInfo;
} TAF_XCALL_MNTN_LOG_CIPHERTEXT_INFO_STRU;

#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;            /* _H2ASN_MsgChoice_Export TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_XCALL_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_XCALL_MNTN_MSG_DATA             stMsgData;
}TAF_XCALL_MNTN_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_MNTN_LogCallInfo(VOS_VOID);
VOS_VOID TAF_XCALL_MNTN_LogSupsCmdMgmt(VOS_VOID);

VOS_VOID TAF_XCALL_MNTN_LogEmcCallRedialPeriod(VOS_VOID);

VOS_VOID TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval(VOS_VOID);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_MNTN_LogTimeStampValidation(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstMsgTimeZone,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstLastTimeZone,
    VOS_UINT64                          ullStdSysTimeInterval,
    VOS_UINT64                          ullStdLastTimeInterval,
    VOS_UINT64                          ullStdMsgTimeInterval
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncPubKeyAndVerInfo(
    VOS_UINT8                           ucVerNum,
    VOS_UINT8                          *pucPubKey
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptCapCfgPara(
    VOS_UINT8                           ucEccSrvCap,
    VOS_UINT8                           ucEccSrvStatus
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptLastInfoEraseTime(
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptLastPassworResetTime(
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeZoneInfo
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptTimerCfgInfo(
    VOS_UINT16                                              usDelayEncVoiceReqTimerLen,
    VOS_UINT16                                              usRemoteCtrlAnswerTimerLen
);

VOS_VOID TAF_XCALL_MNTN_LogMoKmcMsgKeyReq(
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU                         *pstMoKeyReq
);

VOS_VOID TAF_XCALL_MNTN_LogMoKmcMsgKeyRsp(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU                         *pstMoKeyRsp
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgMtEncryptInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_MT_ENCRYPT_IND_STRU                  *pstMtEncryptInd
);

VOS_VOID TAF_XCALL_MNTN_LogMtKmcMsgKeyReq(
    TAF_XCALL_KMC_MSG_KEY_REQ_STRU                         *pstMtKeyReq
);

VOS_VOID TAF_XCALL_MNTN_LogMtKmcMsgKeyRsp(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU                         *pstMtKeyRsp
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgErrInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_ERR_IND_STRU                         *pstErrInd
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_IND_STRU              *pstPubKeyUpdateInd
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateRsp(
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_RSP_STRU              *pstPubKeyUpdateRsp
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgPubKeyUpdateAck(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_ACK_STRU              *pstPubKeyUpdateAck
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdInd(
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRslt,
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU             *pstRemoteCtrlInd
);

VOS_VOID TAF_XCALL_MNTN_LogKmcMsgRemoteCtrlCmdRsp(
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSP_STRU             *pstRemoteCtrlRsp
);

VOS_VOID TAF_XCALL_MNTN_LogEncVoiceRemoteCtrlState(
    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32        enEventType,
    TAF_XCALL_REMOTE_CTRL_STA_ENUM_UINT32                   enState
);

VOS_VOID TAF_XCALL_MNTN_LogEncVoiceKeyUpdateState(
    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32     enEventType,
    TAF_XCALL_K0_UPATE_STA_ENUM_UINT32                      enState
);

VOS_VOID TAF_XCALL_MNTN_LogVoiceEncryptState(
    TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32          enEventType,
    TAF_XCALL_VOICE_ENCRYPT_STA_ENUM_UINT32                 enState
);

VOS_VOID TAF_XCALL_MNTN_LogCipherText(
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                         *pstCipherInfo,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstCalledNum
);

VOS_VOID TAF_XCALL_MNTN_LogKmcDecMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
);

VOS_VOID TAF_XCALL_MNTN_LogKmcEncMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
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

#endif /* end of TafXCallMntn.h */
