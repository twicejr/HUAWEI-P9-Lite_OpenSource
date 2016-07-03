

#ifndef _CC_MM_INTERFACE_H_
#define _CC_MM_INTERFACE_H_

#include "MmCmInterface.h"
#include "NasMncc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
#pragma pack(4)
/* CC发给MM的消息 */
#define MMCC_EST_REQ                                        0
#define MMCC_REL_REQ                                        2
#define MMCC_ABORT_REQ                                      4
#define MMCC_DATA_REQ                                       6
#define MMCC_UNIT_DATA_REQ                                  8
#define MMCC_REEST_REQ                                      10
#define MMCC_PROMPT_REJ                                     12
#define MMCC_START_CC                                       14
#define MMCC_SRVCC_CALL_INFO_NOTIFY                         16

#define MMCC_BEGIN_SESSION_NOTIFY                           (18)
#define MMCC_END_SESSION_NOTIFY                             (20)

#define MMCC_CALL_STATUS_NTY                                (22)

#define MMCC_GET_CALL_INFO_CNF                              (24)

/* CC接收MM的原语 */
#define MMCC_EST_CNF                                        1
#define MMCC_EST_IND                                        3
#define MMCC_REL_IND                                        5
#define MMCC_DATA_IND                                       7
#define MMCC_UNIT_DATA_IND                                  9
#define MMCC_SYNC_IND                                       13
#define MMCC_REEST_CNF                                      11
#define MMCC_ERR_IND                                        15
#define MMCC_PROMPT_IND                                     17
#define MMCC_EMC_NUM_LST_IND                                19
#define MMCC_SRVCC_STATUS_IND                               21

#define MMCC_GET_CALL_INFO_REQ                              23

#define MMCC_RRC_CONN_REL_IND                               25                  /* 当收到接入层的释放消息后，通知CC清除缓存 */

/* 原语MMCC_EST_REQ的结构体 */
#define                     MMCC_MO_NORMAL_CALL             1                   /* Mobile originating call establishment    */
#define                     MMCC_EMERGENCY_CALL             2                   /* Emergency call establishment             */

#define                     MMCC_NO_CALL_PRIORITY           0
#define                     MMCC_CALL_PRIORITY_4            1
#define                     MMCC_CALL_PRIORITY_3            2
#define                     MMCC_CALL_PRIORITY_2            3
#define                     MMCC_CALL_PRIORITY_1            4
#define                     MMCC_CALL_PRIORITY_0            5
#define                     MMCC_CALL_PRIORITY_B            6
#define                     MMCC_CALL_PRIORITY_A            7

#define                     MMCC_CALL_MODE_SPEECH           (0)
#define                     MMCC_CALL_MODE_VIDEO            (1)
#define                     MMCC_CALL_MODE_OTHER            (2)

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头*/
    VOS_UINT32                          ulTransactionId;                        /* TI */
    VOS_UINT32                          ulCallType;                             /* 呼叫类型 */
    VOS_UINT32                          ulCallMode;                             /* 呼叫模式,speech或video或其他的 */
    VOS_UINT32                          ulCallPri ;                             /* 呼叫优先级 */
    VOS_UINT8                           ucRedialFlg;                           /* 呼叫重拨标志 */
    VOS_UINT8                           aucReserve[3];
}MMCC_EST_REQ_STRU;

/* 原语MMCC_EST_CNF的结构体 */
#define                 MMCC_EST_ESTING                     0                   /* 该MM连接正在建立                          */
#define                 MMCC_EST_SUCCESS                    1                   /* 该MM连接建立成功                          */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */
    VOS_UINT32                          ulTransactionId;                        /* TI                                       */
    VOS_UINT32                          ulResult;                               /* 该MM连接建立结果                          */
}MMCC_EST_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头                                   */
    VOS_UINT8                           aucReserve[4];
}MMCC_GET_CALL_INFO_REQ_STRU;


typedef struct
{
    VOS_UINT32                   ulCcMsgSize;                                        /* [1,MMCC_MAX_SIZE_CC_MSG],Byte            */
    VOS_UINT8                   aucCcMsg[4];                                        /* 消息的前四个字节内容                        */
}CC_MSG_STRU;

typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
    VOS_UINT32                   ulTransactionId;                                    /* TI，此参数可以不需要                       */
    CC_MSG_STRU             FisrtCcMsg;                                         /* 第一条CC消息                              */
}MMCC_EST_IND_STRU;

/* 原语MMCC_REL_REQ的结构体 */
#define     MMCC_RELEASE_ALL        0                                       /* 释放所有的MM连接                           */
#define     MMCC_RELEASE_SPECIFIC   1                                       /* 释放指定的MM连接                           */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                    */
    VOS_UINT32                   ulReleaseType;                                      /* 释放类型                                  */
    VOS_UINT32                   ulTransactionId;                                    /* TI                                       */
}MMCC_REL_REQ_STRU;

/* 原语MMCC_REL_IND的结构体 */
#define             MMCC_REL_CAUSE_EST_OR_REEST_FAIL    0
#define             MMCC_REL_CAUSE_REL_OR_ABSENT        1




typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                    */
    VOS_UINT32                   ulTransactionId;                                    /* TI                                       */
    VOS_UINT32                   ulRelCause;                                         /* 释放原因                                  */
}MMCC_REL_IND_STRU;

/* 原语MMCC_ABORT_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                    */
    VOS_UINT32              ulTransactionId;                                    /* TI                                       */
}MMCC_ABORT_REQ_STRU;

/* 原语MMCC_DATA_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
    VOS_UINT32              ulTransactionId;                                    /* TI                                       */
    CC_MSG_STRU             SendCcMsg;                                          /* 需要发送的CC消息                           */
}MMCC_DATA_REQ_STRU;


/* 原语MMCC_DATA_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                    */
    VOS_UINT32                   ulTransactionId;                                    /* TI                                       */
    CC_MSG_STRU             RcvCcMsg;                                           /* MM收到的CC消息                            */
}MMCC_DATA_IND_STRU;

/* 原语MMCC_SYNC_IND的结构体 */

typedef enum
{
    MMCC_CHAN_MOD_SIG_ONLY,
    MMCC_CHAN_MOD_FR,
    MMCC_CHAN_MOD_HR,
    MMCC_CHAN_MOD_EFR,
    MMCC_CHAN_MOD_AHR,
    MMCC_CHAN_MOD_AMR,
    MMCC_CHAN_MOD_AMR2,
    MMCC_CHAN_MOD_AMRWB = 0x08,
    MMCC_CHAN_MOD_DATA_9600,
    MMCC_CHAN_MOD_DATA_4800,
    MMCC_CHAN_MOD_DATA_2400,
    MMCC_CHAN_MOD_DATA_14400,
    MMCC_CHAN_MOD_WFS,


    MMCC_CHAN_MOD_BUTT
} MMCC_SYNC_CHANNAL_MODE_ENUM;
typedef VOS_UINT32 MMCC_CHANNEL_MODE_ENUM_U32;

/*MMCC接口的定义，需要与RRMM接口定义一致*/
typedef enum
{
    MM_CC_AMR_RATE_NULL               = 0x00,             /* 用于ASN.1解码，代码不使用 */
    MM_CC_AMR_RATE_4P75               = 0x01,             /* 4.75k */
    MM_CC_AMR_RATE_5P15               = 0x02,             /* 5.15k */
    MM_CC_AMR_RATE_5P9                = 0x04,             /* 5.90k */
    MM_CC_AMR_RATE_6P7                = 0x08,             /* 6.70k */
    MM_CC_AMR_RATE_7P4                = 0x10,             /* 7.40k */
    MM_CC_AMR_RATE_7P95               = 0x20,             /* 7.95k */
    MM_CC_AMR_RATE_10P2               = 0x40,             /* 10.2k */
    MM_CC_AMR_RATE_12P2               = 0x80,             /* 12.2k */
    MM_CC_AMR_RATE_BUTT
} MMCC_TCH_RATE_ENUM;
typedef VOS_UINT32 MMCC_TCH_RATE_ENUM_U32;


/*MMCC接口的定义，需要与RRMM接口定义一致*/
typedef enum
{
    /* reasons for GSM */
    MMCC_GSM_RES_ASSIGNED,
    MMCC_GSM_CHANNEL_MODE_MODIFIED,
    MMCC_GSM_GSM_HANDOVER,
    MMCC_WCDMA_GSM_HANDOVER,

    /* reasons for WCDMA */
    MMCC_WCDMA_RAB_ESTABLISHED,
    MMCC_WCDMA_RAB_RECONFIGURED,
    MMCC_GSM_WCDMA_INTER_HANDOVER,
    MMCC_WCDMA_NO_CHANGE,
    MMCC_WCDMA_RAB_RELEASED
} MMCC_SYNC_REASON_ENUM;
typedef VOS_UINT32 MMCC_SYNC_REASON_ENUM_U32;

#define NAS_MM_CC_MAX_RAB_NUM           16                                      /* RAB的最大个数 */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */
    MMCC_CHANNEL_MODE_ENUM_U32          enChannelMode;                          /* 信道模式，仅GSM */

    VOS_UINT32                          ulRabNum;                               /* 需要同步的RAB数量 */
    MMCC_SYNC_REASON_ENUM_U32           enSyncReason;

    struct
    {
        VOS_UINT32                      ulRabId;                                /* RAB ID */
        VOS_UINT32                      ulRabSyncInfo;                          /* 该RAB的同步信息 */
    }syncInfo[NAS_MM_CC_MAX_RAB_NUM];

} MMCC_SYNC_IND_STRU;

/* 原语MMCC_REEST_REQ的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                    */
    VOS_UINT32                   ulTransactionId;                                    /* TI                                       */
}MMCC_REEST_REQ_STRU;

/* 原语MMCC_REEST_CNF的结构体 */
#define     MMCC_REEST_ESTING       0                                       /* 该MM连接正在重建                          */
#define     MMCC_REEST_SUCCESS      1                                       /* 该MM连接重建成功                          */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                    */
    VOS_UINT32                   ulTransactionId;                                    /* TI                                       */
    VOS_UINT32                   ulResult;                                           /* 该MM连接重建结果                          */
}MMCC_REEST_CNF_STRU;

/* 原语MMCC_ERR_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* 消息头 */
    VOS_UINT32                          ulTransactionId;                        /* TI */
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enCause;                                /* 原因值 */
}MMCC_ERR_IND_STRU;

/* 原语MMCC_PROMPT_IND的结构体 */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                   */
}MMCC_PROMPT_IND_STRU;

/* 原语MMCC_PROMPT_REJ的结构体 */
#define     MMCC_CAUSE_SERV_OPT_TEMP_OUT_OF_ORDER      0                    /* Service option temporarily out of order  */
#define     MMCC_CAUSE_SERV_OPT_NOT_SUPP               1                    /* Service option not supported             */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* 消息头                                    */
    VOS_UINT32                   ulRefuseCause;                                      /* 拒绝原因                                  */
}MMCC_PROMPT_REJ_STRU;

/* 原语MMCC_EMC_NUM_LST_IND的结构体 */
#define MMCC_EMERGENCY_NUMBER_MAX_LENGTH              46                        /* Emergency Number information的最大字节数 */
#define MMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER        16                        /* Emergency Number Lists的最多个数         */
typedef struct
{
    VOS_UINT8                           ucCategoryValue;                        /* Emergency Service Category Value         */

    VOS_UINT8                           ucEmcNumLen;                            /*紧急呼号码长度，即aucEmcNum的有效长度*/
    VOS_UINT8                           aucEmergencyList[MMCC_EMERGENCY_NUMBER_MAX_LENGTH];
}MMCC_EMERGENCY_CONTENT_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT32                          ulMcc;
    VOS_UINT8                           ucEmergencyNumber;
    VOS_UINT8                           aucReserved[3];
    MMCC_EMERGENCY_CONTENT_STRU         astEmergencyLists[MMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER];
}MMCC_EMERGENCY_LIST_STRU;


enum MMCC_SESSION_TYPE_ENUM
{
    MMCC_SESSION_TYPE_MO_NORMAL_CALL,
    MMCC_SESSION_TYPE_MO_EMERGENCY_CALL,
    MMCC_SESSION_TYPE_MT_NORMAL_CALL,
    MMCC_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 MMCC_SESSION_TYPE_ENUM_UINT8;


typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMCC_SESSION_TYPE_ENUM_UINT8                    enSessionType;
    VOS_UINT8                                       aucReserved[3];
} MMCC_BEGIN_SESSION_NOTIFY_STRU;




typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;                /*_H2ASN_Skip*/
    MMCC_SESSION_TYPE_ENUM_UINT8                    enSessionType;
    VOS_UINT8                                       aucReserved[3];
} MMCC_END_SESSION_NOTIFY_STRU;




enum NAS_MMCC_SRVCC_STATUS_ENUM
{
    NAS_MMCC_SRVCC_STATUS_START        = 0,     /* SRVCC开始 */
    NAS_MMCC_SRVCC_STATUS_SUCCESS      = 1,     /* SRVCC成功 */
    NAS_MMCC_SRVCC_STATUS_FAIL         = 2,     /* SRVCC失败 */
    NAS_MMCC_SRVCC_STATUS_BUTT
};
typedef VOS_UINT32  NAS_MMCC_SRVCC_STATUS_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* _H2ASN_Skip */
    NAS_MMCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus;
    VOS_UINT8                           aucReserve1[4];    /*预留*/
}MMCC_SRVCC_STATUS_IND_STRU;

typedef MNCC_CALL_STATUS_ENUM_UINT8 MMCC_CALL_STATUS_ENUM_UINT8;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* _H2ASN_Skip */
    MMCC_CALL_STATUS_ENUM_UINT8         enCallStatus;
    VOS_UINT8                           aucReserve[3];
}MMCC_CALL_STATUS_NTF_STRU;


enum NAS_CC_CALL_TYPE
{
    NAS_CC_CALL_TYPE_MO_NORMAL_CALL,                    /* 主叫正常呼 */
    NAS_CC_CALL_TYPE_EMERGENCY_CALL,                    /* 主叫紧急呼 */
    NAS_CC_CALL_TYPE_MT_NORMAL_CALL,                    /* 被叫普通呼 */
    NAS_CC_CALL_TYPE_BUTT
};
typedef VOS_UINT8  NAS_CC_CALL_TYPE_ENUM_U8;


typedef struct
{
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucTi;
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType;
}MMCC_CALL_INFO_STRU;

#define  NAS_CC_MAX_ENTITY_NUM          (7)

/* 无效的TI值 */
#define  NAS_CC_INVALID_TI_VALUE        (0xf)

/* 无效的CALL ID */
#define NAS_CC_INVALID_CALL_ID          (0xff)


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    MMCC_CALL_INFO_STRU                 astCallInfo[NAS_CC_MAX_ENTITY_NUM];
}MMCC_GET_CALL_INFO_CNF_STRU;

#define   NAS_MM_MAX_CC_CONNECTION_NUM      7


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* _H2ASN_Skip */
    VOS_UINT8                           ucTiNum;
    VOS_UINT8                           aucTransactionId[NAS_MM_MAX_CC_CONNECTION_NUM];
}MMCC_SRVCC_CALL_INFO_NOTIFY_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /* _H2ASN_Skip */
    VOS_UINT8                           aucRcv[4];
}MMCC_RRC_CONN_REL_IND_STRU;


VOS_VOID NAS_CC_GetCallInfo(
    MMCC_CALL_INFO_STRU                *pstCallInfo
);



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
