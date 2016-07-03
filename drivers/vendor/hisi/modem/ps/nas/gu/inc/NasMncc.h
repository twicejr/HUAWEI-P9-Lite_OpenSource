
#ifndef  NAS_MNCC_H
#define  NAS_MNCC_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "NasCcAirMsg.h"
#include "msp_diag_comm.h"

#define MNCC_EMERGENCY_MAX_LIST                       (16)
#define MNCC_EMERGENCY_NUMBER_MAX_LENGTH              (46)                      /* Emergency Number information的最大字节数 */


/* MNCC Primitives defination */
typedef enum
{
    /* MN --> CC */
    MNCC_SETUP_REQ,                                                             /* parameter: SETUP message */
    MNCC_EMERG_SETUP_REQ,                                                       /* parameter: EMERGENCY SETUP message */
    MNCC_SETUP_RES,                                                             /* parameter: CONNECT message */
    MNCC_CALL_CONF_REQ,                                                         /* parameter: CALL CONFIRM message */
    MNCC_ALERT_REQ,                                                             /* parameter: ALERTING message */
    MNCC_DISC_REQ,                                                              /* parameter: DISCONNECT message */
    MNCC_REL_REQ,                                                               /* parameter: RELEASE message */
    MNCC_REJ_REQ,                                                               /* parameter: RELEASE COMPLETE message */
    MNCC_FACILITY_REQ,                                                          /* parameter: FACILITY message */
    MNCC_HOLD_REQ,                                                              /* parameter: HOLD message */
    MNCC_RETRIEVE_REQ,                                                          /* parameter: RETRIEVE message */
    MNCC_START_DTMF_REQ,                                                        /* parameter: START DTMF message */
    MNCC_STOP_DTMF_REQ,                                                         /* parameter: None */
    MNCC_MODIFY_REQ,                                                            /* parameter: MODIFY message */
    MNCC_MODIFY_RES,                                                            /* parameter: MODIFY COMPLETE message */
    MNCC_MODIFY_REJ_REQ,                                                        /* parameter: MODIFY REJECT message */
    MNCC_EST_CNF_REQ,                                                           /* parameter: Establishment Cnf message */
    MNCC_SRVCC_CALL_INFO_NOTIFY,                                                /* parameter:srvcc call info notify message */
    MNCC_CALL_STATUS_NTY,                                                       /* parameter:call status notify message */

    /* CC --> MN */
    MNCC_SETUP_IND = 0x0100,                                                    /* parameter: SETUP message */
    MNCC_SETUP_CNF,                                                             /* parameter: CONNECT message */
    MNCC_SETUP_COMPL_IND,                                                       /* parameter: None */
    MNCC_CALL_PROC_IND,                                                         /* parameter: CALL PROCEEDING message */
    MNCC_ALERT_IND,                                                             /* parameter: ALERTING message */
    MNCC_DISC_IND,                                                              /* parameter: DISCONNECT message */
    MNCC_REL_IND,                                                               /* parameter: RELEASE message */
    MNCC_REL_CNF,                                                               /* parameter: RELEASE COMPLETE message */
    MNCC_REJ_IND,                                                               /* parameter: Cause or none */
    MNCC_FACILITY_IND,                                                          /* parameter: FACILITY message */
    MNCC_FACILITY_LOCAL_REJ,                                                    /* parameter: Invoke ID */
    MNCC_HOLD_CNF,                                                              /* parameter: None */
    MNCC_HOLD_REJ,                                                              /* parameter: HOLD REJ message */
    MNCC_RETRIEVE_CNF,                                                          /* parameter: None */
    MNCC_RETRIEVE_REJ,                                                          /* parameter: RETRIEVE REJ message */
    MNCC_START_DTMF_CNF,                                                        /* parameter: None */
    MNCC_START_DTMF_REJ,                                                        /* parameter: Cause */
    MNCC_STOP_DTMF_CNF,                                                         /* parameter: None */
    MNCC_MODIFY_IND,                                                            /* parameter: Modify message */
    MNCC_MODIFY_CNF,                                                            /* parameter: Modify Complete message */
    MNCC_MODIFY_REJ_IND,                                                        /* parameter: MODIFY REJECT message */
    MNCC_SYNC_IND,                                                              /* parameter: sync message */
    MNCC_PROGRESS_IND,                                                          /* parameter: Process message */
    MNCC_CC_EST_IND,                                                            /* parameter:CC ESTABLISHMENT message*/
    MNCC_RECALL_IND,                                                            /* parameter:recall message*/
    MNCC_UUSINFO_IND,                                                           /* parameter:Uus message*/

    MNCC_EMERGENCY_LIST_IND,
    MNCC_SRVCC_STATUS_IND,                                                      /* parameter:srvcc status notify message */

    MNCC_PRIM_NAME_MAX

} MNCC_PRIM_NAME_ENUM;
typedef VOS_UINT16  MNCC_PRIM_NAME_ENUM_U16;

typedef struct
{
    VOS_UINT8                           IsExist;
    VOS_UINT8                           LastOctOffset;
    NAS_CC_MSG_SETUP_MO_STRU            stSetup;
}MNCC_IE_SETUP_CONTAINER_STRU;

typedef struct
{
    NAS_AIR_MSG_HDR_STRU                stHeader;
    MNCC_IE_SETUP_CONTAINER_STRU        stSetupContainer;
}MNCC_MSG_EST_STRU;


enum NAS_MNCC_SRVCC_STATUS_ENUM
{
    NAS_MNCC_SRVCC_STATUS_START        = 0,     /* SRVCC开始 */
    NAS_MNCC_SRVCC_STATUS_SUCCESS      = 1,     /* SRVCC成功 */
    NAS_MNCC_SRVCC_STATUS_FAIL         = 2,     /* SRVCC失败 */
    NAS_MNCC_SRVCC_STATUS_BUTT
};
typedef VOS_UINT32  NAS_MNCC_SRVCC_STATUS_ENUM_UINT32;



enum MNCC_CALL_STATUS_ENUM
{
    MNCC_CALL_STATUS_SETUP_SUCC         = 0,                                    /* 呼叫建立成功 */
    MNCC_CALL_STATUS_SETUP_FAIL         = 1,                                    /* 呼叫建立失败 */
    MNCC_CALL_STATUS_BUTT
};
typedef VOS_UINT8  MNCC_CALL_STATUS_ENUM_UINT8;



typedef struct
{
    NAS_MNCC_SRVCC_STATUS_ENUM_UINT32   enSrvccStatus;
    VOS_UINT8                           aucReserve1[4];    /*预留*/
}MNCC_SRVCC_STATUS_IND_STRU;


typedef struct
{
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           aucReserve1[2] ;
    NAS_CC_IE_BC_STRU                   stBC1;
    NAS_CC_IE_BC_STRU                   stBC2;
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldAuxState;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyAuxState;
    VOS_UINT8                           aucReserve2[1] ;
}MNCC_ENTITY_STATUS_STRU;

#define   MNCC_MAX_ENTITY_NUM      7


typedef struct
{
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           ucTchAvail;
    VOS_UINT8                           aucReserve[2];
    MNCC_ENTITY_STATUS_STRU             astEntityStatus[MNCC_MAX_ENTITY_NUM];
}MNCC_SRVCC_CALL_INFO_NOTIFY_STRU;


typedef struct
{
    MNCC_CALL_STATUS_ENUM_UINT8         enCallStatus;
    VOS_UINT8                           aucReserve1[3];    /*预留*/
}MNCC_CALL_STATUS_NTY_STRU;

/* Union of parameters in MNCC primitives (MN -> CC) */
typedef union
{
    NAS_CC_MSG_SETUP_MO_STRU            stSetup;
    NAS_CC_MSG_EMERGENCY_STEUP_STRU     stEmerg;
    NAS_CC_MSG_ALERTING_MO_STRU         stAlert;
    NAS_CC_MSG_CONNECT_MO_STRU          stConn;
    NAS_CC_MSG_CALL_CNF_STRU            stCallCnf;
    NAS_CC_MSG_MODIFY_STRU              stModify;
    NAS_CC_MSG_MODIFY_COMPLETE_STRU     stModifyRes;
    NAS_CC_MSG_MODIFY_REJ_STRU          stModifyRej;
    NAS_CC_MSG_DISCONNECT_MO_STRU       stDisc;
    NAS_CC_MSG_RELEASE_MO_STRU          stRel;
    NAS_CC_MSG_FACILITY_MO_STRU         stFac;
    NAS_CC_MSG_START_DTMF_STRU          stStartDtmf;
    NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU stRelComp;
    NAS_CC_MSG_CC_EST_CNF_STRU          stCcEstCnf;

    MNCC_SRVCC_CALL_INFO_NOTIFY_STRU    stSrvccCallInfoNtf;
    MNCC_CALL_STATUS_NTY_STRU           stCallStatusNtf;
} MNCC_REQ_PARAM_UNION;

/* MNCC_SYNC_IND */
enum NAS_CC_RADIO_ACCESS_MODE_ENUM
{
    NAS_CC_RA_MODE_GSM,
    NAS_CC_RA_MODE_WCDMA
};
typedef VOS_UINT32  NAS_CC_RADIO_MODE_ENUM_U32;

/* 和nasrrcinterface.h中的定义保持一致 */

enum NAS_CC_CHANNEL_TYPE_ENUM
{
    NAS_CC_TCH_SINGAL_MOD,                                                      /* 仅信令模式*/
    NAS_CC_TCH_TYPE_FR,                                                         /* full rate */
    NAS_CC_TCH_TYPE_HR,                                                         /* half rate */
    NAS_CC_TCH_TYPE_EFR,                                                        /* enhanced full rate */
    NAS_CC_TCH_TYPE_AHR,                                                        /* a half rate */
    NAS_CC_TCH_TYPE_AMR,                                                        /* amr */
    NAS_CC_TCH_TYPE_AMR2,                                                       /* amr2 */
    NAS_CC_TCH_TYPE_AMRWB = 0x08,

    NAS_CC_TCH_CSD_9600,                                                        /* CSD */
    NAS_CC_TCH_CSD_4800,                                                        /* CSD */
    NAS_CC_TCH_CSD_2400,                                                        /* CSD */
    NAS_CC_TCH_CSD_14400,                                                       /* CSD */


    NAS_CC_TCH_TYPE_BUFF                                                        /* invalid value */
};
typedef VOS_UINT32  NAS_CC_TCH_TYPE_ENUM_U32;

/* 和nasrrcinterface.h中的定义保持一致 */
enum NAS_CC_SUB_CHANNEL_TYPE_ENUM
{
    NAS_CC_CHANNEL_RATE_NULL   = 0x00,                                          /* rate 0kbps/s */
    NAS_CC_CHANNEL_RATE_475    = 0x01,                                          /* rate 4.75kbps/s */
    NAS_CC_CHANNEL_RATE_515    = 0x02,                                          /* rate 5.15kbps/s */
    NAS_CC_CHANNEL_RATE_59     = 0x04,                                          /* rate 5.9kbps/s */
    NAS_CC_CHANNEL_RATE_67     = 0x08,                                          /* rate 6.7kbps/s */
    NAS_CC_CHANNEL_RATE_74     = 0x10,                                          /* rate 7.4kbps/s */
    NAS_CC_CHANNEL_RATE_795    = 0x20,                                          /* rate 7.95kbps/s */
    NAS_CC_CHANNEL_RATE_102    = 0x40,                                          /* rate 10.2kbps/s */
    NAS_CC_CHANNEL_RATE_122    = 0x80,                                          /* rate 12.2kbps/s */
    NAS_CC_CHANNEL_RATE_BUFF                                                    /* invalid value */
};
typedef VOS_UINT32  NAS_CC_RATE_TYPE_ENUM_U32;

enum NAS_CC_ALERT_IND_ENUM
{
    NAS_CC_ALERT_START,
    NAS_CC_ALERT_STOP,
    NAS_CC_ALERT_IND_BUFF
};
typedef VOS_UINT32  NAS_CC_ALERT_IND_ENUM_U32;

#define NAS_CC_MAX_UUIE_MSG_NUM         (7)
typedef struct
{
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType;
    VOS_UINT8                           aucReserved3[3];
    NAS_CC_IE_USER_USER_STRU            stUuieInfo;
}NAS_CC_UUS1_INFO_STRU;

typedef struct
{
    NAS_CC_ALERT_IND_ENUM_U32           enAlertInd;
    VOS_UINT32                          ulTchAvail;                             /*TCH available, VOS_TRUE:存在; VOS_FALSE:不存在*/
    NAS_CC_RADIO_MODE_ENUM_U32          enRaMode;
    NAS_CC_TCH_TYPE_ENUM_U32            enTchType;
}NAS_CC_SYNC_IND_STRU;

typedef struct
{
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgtype;
    VOS_UINT8                           aucReserved3[3];
    NAS_CC_MSG_USER_INFO_STRU           stUserInfo;
}NAS_CC_UUS_INFO_IND_STRU;


typedef struct
{
    VOS_UINT8                           ucCategoryValue;                        /* Emergency Service Category Value         */
    VOS_UINT8                           ucEmcNumLen;                            /*紧急呼号码长度，即aucEmcNum的有效长度*/
    VOS_UINT8                           aucEmergencyNum[MNCC_EMERGENCY_NUMBER_MAX_LENGTH];
}MNCC_EMERGENCY_CONTENT_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT8                           ucEmergencyNumber;
    VOS_UINT8                           aucReserved[3];
    MNCC_EMERGENCY_CONTENT_STRU         astEmergencyLists[MNCC_EMERGENCY_MAX_LIST];
}MNCC_EMERGENCY_LIST_IND_STRU;

/* Union of parameters in MNCC primitives (CC -> MN) */
typedef union
{
    NAS_CC_MSG_SETUP_MT_STRU            stSetup;
    NAS_CC_MSG_ALERTING_MT_STRU         stAlert;
    NAS_CC_MSG_CONNECT_MT_STRU          stConn;
    NAS_CC_MSG_CALL_PROC_STRU           stCallProc;
    NAS_CC_MSG_MODIFY_STRU              stModify;
    NAS_CC_MSG_DISCONNECT_MT_STRU       stDisc;
    NAS_CC_MSG_RELEASE_MT_STRU          stRel;
    NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU stRelComp;
    NAS_CC_MSG_FACILITY_MT_STRU         stFac;
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause;
    VOS_UINT8                           ucInvokeId;
    NAS_CC_SYNC_IND_STRU                stSyncInd;
    MNCC_MSG_EST_STRU                   stEstInd;
    NAS_CC_MSG_RECALL_STRU              stRecall;
    NAS_CC_MSG_PROGRESS_STRU            stProgressInd;
    NAS_CC_UUS_INFO_IND_STRU            stUusInfo;

    MNCC_EMERGENCY_LIST_IND_STRU        stEmcListInd;

    MNCC_SRVCC_STATUS_IND_STRU          stSrvccStaInd;
} MNCC_IND_PARAM_UNION;


/* Structure of the MNCC primitive message (MN -> CC) */
typedef struct
{
    VOS_MSG_HEADER
    MNCC_PRIM_NAME_ENUM_U16             enPrimName;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulParamLen;
    MNCC_REQ_PARAM_UNION                unParam;
    VOS_UINT8                           ucRedialFlg;
    VOS_UINT8                           aucReserve[3];
} MNCC_REQ_PRIM_MSG_STRU;

/* Structure of the MNCC primitive message (CC -> MN) */
typedef struct
{
    VOS_MSG_HEADER
    MNCC_PRIM_NAME_ENUM_U16             enPrimName;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulParamLen;
    MNCC_IND_PARAM_UNION                unParam;
} MNCC_IND_PRIM_MSG_STRU;


VOS_UINT32 NAS_CC_ActUus1Info(
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
);


VOS_VOID NAS_CC_GetAllUus1Info(
    VOS_UINT32                          *pulActNum,
    NAS_CC_UUS1_INFO_STRU               *pstUus1Info
);


VOS_UINT32 NAS_CC_DeactUus1Info(
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType
);

VOS_VOID NAS_CC_InitUus1Info( VOS_VOID );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* NAS_MNCC_H */

