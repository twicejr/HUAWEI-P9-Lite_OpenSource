/******************************************************************************
  Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
  File name:      PSAgentInterface.h
  Author:          liutao
  Version:         V10
  Date:             2004-12-25
  Description:  the interface of Agent
  History:
  1. 日    期  : 2006年12月4日
     作    者  : luojian id:60022475
     修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
  2. 日    期   : 2007年06月08日
     作    者   : luojian 60022475
     修改内容   : 根据问题单号A32D11576
******************************************************************************/
#ifndef    _PS_AGENT_INTERFACE_H
#define    _PS_AGENT_INTERFACE_H

#include "pscfg.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif    /* __cpluscplus   */
#endif    /* __cpluscplus   */

#pragma  pack(4)
/****************Data Define Begin**************/
#define     RRC_DL_MAX_MESSAGE_NUM                  26
#define     RRC_UL_MAX_MESSAGE_NUM                  30
#define     RRC_CBG_MAX_INTRA_FREQ_CELL             32
#define     RRC_CBG_MAX_EACH_FREQ_CELL              16
#define     RRC_CBG_MAX_ADDITIONAL_CARRIER          2
#define     RLC_AM_RB_NUM                           10
/* #define     LEN_MOBILE_ID                           9 */
#define     LEN_PTMSI_SIGNATURE                     3
#define     LEN_PTMSI                               4
#define     LEN_RAI                                 6
#define     LEN_LA                                  5
#define     LEN_CK                                  16
#define     LEN_IK                                  16
#define     LEN_DRX                                 2
#define     LEN_NETWORK_CAPABILITY                  9
#define     LEN_RADIO_ACCESS_CAPABILITY             52
#define     INTEGRITY_KEY_LENGTH                    16
#define     CIPHERIGN_KEY_LENGTH                    16
#define     MM_TMSI_LENGTH                          0x04
#define     MM_LAI_LENGTH                           0x05
#define     LEN_MOBILE_ID                           9
#define     MAX_PDP_NUM                             11
/****************Data Define End*****************************************/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/****************the Interface of AGENT and RRC Define Begin ************/
/*CBG_REPORT_CONFIG_REQ*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMsgID;
    VOS_UINT32    ulRcvNum;
    struct
    {
        VOS_UINT32    ulRcvMsgID;
        VOS_UINT32    ulRcvMsgFlg;
    }rcv_msg[RRC_DL_MAX_MESSAGE_NUM];
    VOS_UINT32        ulSndNum;
    struct
    {
        VOS_UINT32    ulSndMsgID;
        VOS_UINT32    ulSndMsgFlg;
    }snd_msg[RRC_UL_MAX_MESSAGE_NUM];
} CBG_REPORT_CONFIG_REQ_STRU;

/*CBG_REPORT_IND*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMsgID;
    VOS_UINT32	 ulLchType;
    VOS_UINT32    ulUpDown;
    VOS_UINT32    ulAirMsgID;
    VOS_UINT32    ulLengthASN;
    VOS_INT8     ucData[4];
} CBG_REPORT_IND_STRU;

/*CBG_RRC_ACT_IND*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMsgID;
    VOS_UINT32    ulActInd;
} CBG_RRC_ACT_IND_STRU;

/*CBG_RRC_CELL_RESEL_IND*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMsgID;
    VOS_UINT32    ulQua;
    VOS_UINT32    ulCellNum;
    struct
    {
        VOS_UINT32    ulFreqInfo;
        VOS_UINT32    ulPriScramCode;
        VOS_INT32     lResult;
    }aCellResult[RRC_CBG_MAX_INTRA_FREQ_CELL +  RRC_CBG_MAX_EACH_FREQ_CELL*RRC_CBG_MAX_ADDITIONAL_CARRIER+1];
} CBG_RRC_CELLRESEL_IND_STRU;
/**************the Interface of AGENT and RRC Define End******************/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/****************the Interface of AGENT and RLC Define Begin**************/
/*BG_RLC_SET_DATA_RATE_DISPLAY*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32   ulMessageId;
    VOS_UINT32   ulRbId;
    VOS_UINT32   ulOpenOrShut;
    VOS_UINT32   ulGapOfTime;
} IF_BG_RLC_SET_DATA_RATE_DISPLAY_STRU;

/*RLC_BG_LINK_RATE_IND*/
typedef struct
{
    VOS_UINT32    ulRbId;
    VOS_UINT32    ulRlcUpLinkBitWithAck;
    VOS_UINT32    ulRlcUpLinkRetranPduNum;
    VOS_UINT32    ulRlcUpLinkAllDataPduNum;
    VOS_UINT32    ulRlcUpLinkStatusPduNum;
    VOS_UINT32    ulRlcUpLinkResetNum;
    VOS_UINT32    ulRlcUpLinkDataLinkLossNum;
    VOS_UINT32    ulRlcUpLinkFullWinNum;
    VOS_UINT32    ulRlcUpLinkAverWinRate;
    VOS_UINT32    ulRlcUpLinkMaxWinRate;
    VOS_UINT32    ulRlcDownLinkReassBit;
    VOS_UINT32    ulRlcDownLinkRetranPduNum;
    VOS_UINT32    ulRlcDownLinkAllDataPduNum;
    VOS_UINT32    ulRlcDownLinkStatusPduNum;
    VOS_UINT32    ulRlcDownLinkResetNum;
} RB_LINK_RATE_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT32    ulGapOfTime;
    VOS_UINT32    ulRbNum;
    RB_LINK_RATE_IND_STRU  struRbLinkRateInfo[RLC_AM_RB_NUM];
} IF_RLC_BG_LINK_RATE_IND_STRU;
/**************the Interface of AGENT and RLC Define End******************/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/**************the Interface of AGENT and MAC Define Begin ***************/
/*CMD_MAC_START_FTP_REQ*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32   ulMessageId;
    VOS_UINT32   ulServerIp;
    VOS_UINT8   ucFileName[12];
    VOS_UINT32   ulDataNum;
}MAC_START_FTP_REQ_STRU;

/*CMD_MAC_STOP_FTP_REQ*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT32    ulReserved;
}MAC_STOP_FTP_REQ_STRU;

/*CMD_MAC_START_FTP_CNF*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT32    ulResult;
}MAC_START_FTP_CNF_STRU;

/*MAC_BG_AMR_REQ*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMsgID;
    VOS_UINT32    ulSetupFlag;
    VOS_UINT32    ulServiceType;
} MAC_AMR_REQ_STRU;

/*MAC_SET_DATA_RATE_DISPLAY*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT16   usMessageId;
    VOS_UINT16   usOpenOrShut;
    VOS_UINT32    ulGapOfTime;
} AGENT_MAC_SET_DATA_RATE_DISPLAY_STR;

/*MAC_BG_DATA_RATE_DISPLAY_IND*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT16   usMessageId;
    VOS_UINT16   usDownLinkBit;
    VOS_UINT16   usUpLinkBit;
    VOS_UINT16   usUpLinkMaxConfigRate;
    VOS_UINT16   usDownLinkMaxConfigRate;
    VOS_UINT16   usReserved;
}IF_MAC_AG_MAC_DATA_RATE_DISPLAY_REP_STRU;
/***************the Interface of AGENT and MAC Define End*****************/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/***********the Interface of AGENT and PMM/MM Define Begin ***************/
/*AGENT_PMM_INQUIRE*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
} AGENT_PMM_INQUIRE_STRU;

/*PMM_AGENT_INFO*/
typedef struct
{
    VOS_UINT8    ucLength;
    VOS_UINT8    ucMobileIDValue[LEN_MOBILE_ID];
} MOBILE_ID_STRUCT;

enum PMM_MAIN_STATE_ENUM
{
    PMM_MAIN_STATE_NULL                          = 0,
    PMM_MAIN_STATE_DEREGISTERED                  = 1,
    PMM_MAIN_STATE_DEREGISTERED_INIT             = 2,
    PMM_MAIN_STATE_REGISTERED_INIT               = 3,
    PMM_MAIN_STATE_REGISTERED                    = 4,
    PMM_MAIN_STATE_ROUTING_AREA_UPDATING_INIT    = 5,
    PMM_MAIN_STATE_SERVICE_REQUEST_INIT          = 6
};

enum PMM_SUB_STATE_ENUM
{
    PMM_SUB_STATE_NULL                           = 0,
    PMM_SUB_STATE_NORMAL_SERVICE                 = 1,
    PMM_SUB_STATE_ATTACH_NEEDED                  = 2,
    PMM_SUB_STATE_ATTEMPTING_TO_ATTACH           = 3,
    PMM_SUB_STATE_NO_IMSI                        = 4,
    PMM_SUB_STATE_NO_CELL_AVAILABLE              = 5,
    PMM_SUB_STATE_LIMITED_SERVICE                = 6,
    PMM_SUB_STATE_PLMN_SEARCH                    = 7,
    PMM_SUB_STATE_ATTEMPTING_TO_UPDATE           = 8,
    PMM_SUB_STATE_ATTEMPTING_TO_UPDATE_MM        = 9,
    PMM_SUB_STATE_IMSI_DETACH_INIT               = 10,
    PMM_SUB_STATE_SUSPEND_GSM_ONLY               = 11,
    PMM_SUB_STATE_UPDATE_NEEDED                  = 12
};

enum NET_MODE_ENUM
{
    NET_MODE_1    = 0x00,
    NET_MODE_2    = 0x01
};

enum PMM_CAUSE_ENUM
{
    PMM_CAUSE_IMSI_UNKNOWN_IN_HLR                                   = 0x02,
    PMM_CAUSE_ILLEGAL_MS                                            = 0x03,
    PMM_CAUSE_IMSI_UNKNOWN_IN_VLR                                   = 0x04,

    PMM_CAUSE_ILLEGAL_ME                                            = 0x06,
    PMM_CAUSE_GPRS_SERVICE_NOT_ALLOWED                              = 0x07,
    PMM_CAUSE_GPRS_SERVICE_AND_NONGPRS_SERVICE_NOT_ALLOWED          = 0x08,
    PMM_CAUSE_MS_IDENTITY_CANNOT_BE_DERIVED_BY_THE_NETWORK          = 0x09,
    PMM_CAUSE_IMPLICITLY_DETACHED                                   = 0x0A,
    PMM_CAUSE_PLMN_NOT_ALLOWED                                      = 0x0B,
    PMM_CAUSE_LOCATION_AREA_NOT_ALLOWED                             = 0x0C,
    PMM_CAUSE_ROAMING_NOT_ALLOWED                                   = 0x0D,
    PMM_CAUSE_GPRS_SERVICES_NOT_ALLOWED_IN_THIS_PLMN                = 0x0E,
    PMM_CAUSE_NO_SUITABLE_CELLS_IN_LOCATION_AREA                    = 0x0F,

    PMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE                         = 0x10,
    PMM_CAUSE_NETWORK_FAILURE                                       = 0x11,

    PMM_CAUSE_MAC_FAILURE                                           = 0x14,
    PMM_CAUSE_SYNC_FAILURE                                          = 0x15,
    PMM_CAUSE_CONGESTION                                            = 0x16,
    PMM_CAUSE_GSM_AUTHENTICATION_UNACCEPTABLE                       = 0x17,

    PMM_CAUSE_NO_PDP_CONTEXT_ACTIVATED                              = 0x28,

    PMM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE                        = 0x5f,
    PMM_CAUSE_INVALID_MANDATORY_INFORMATION                         = 0x60,
    PMM_CAUSE_MESSAGE_TYPE_NONEXISTENT_OR_NOT_IMPLEMENTED           = 0x61,
    PMM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE   = 0x62,
    PMM_CAUSE_IE_NOT_EXISTENT_OR_NOT_IMPLEMENTED                    = 0x63,
    PMM_CAUSE_CONDITIONAL_IE_ERROR                                  = 0x64,
    PMM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE            = 0x65,

    PMM_CAUSE_UNSPECIFIC                                            = 0x6f,
    PMM_CAUSE_NULL                                                  = 0xff
};

enum RR_REL_CAUSE_ENUM
{
    RR_REL_CAUSE_NORMAL_EVENT,
    RR_REL_CASUE_UNSPECIFIED,
    RR_REL_CASUE_PRE_EMPTIVE_RELEASE,
    RR_REL_CAUSE_CONGESTION,
    RR_REL_CAUSE_RE_ESTABLISH_REJ,
    RR_REL_CAUSE_USER_INACTIVITY,
    RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT,
    RR_REL_CAUSE_RANDOM_ACCESS_FAILURE,
    RR_REL_CAUSE_RR_CONNECTION_FAILURE,
    RR_REL_CAUSE_ACCESS_BARRED_CAUSE_ACCESS_CLASS_CONTROL,
    RR_REL_CAUSE_COVERAGE_LOST,
    RR_REL_CAUSE_ABORT_RR_NORMAL,
    RR_REL_CAUSE_ABORT_RR_UNEXIST_CONNECTION,
    RR_REL_CAUSE_RRC_IS_ESTABLISHING,
    RR_REL_CAUSE_RRC_SNW
};

enum PMM_INTERNAL_CAUSE_ENUM
{
    PMM_INTERNAL_CAUSE_GPRS_NOT_SUPPORTED              = 0x80,
    PMM_INTERNAL_CAUSE_T3310_EXPIRED                   = 0x81,
    PMM_INTERNAL_CAUSE_T3321_EXPIRED                   = 0x82,
    PMM_INTERNAL_CAUSE_T3330_EXPIRED                   = 0x83,
    PMM_INTERNAL_CAUSE_T3317_EXPIRED                   = 0x84,
    PMM_INTERNAL_CAUSE_RR_EST_FAILURE                  = 0x85,
    PMM_INTERNAL_CAUSE_ACCESS_BARRED                   = 0x86,
    PMM_INTERNAL_CAUSE_LOWER_LAYER_FAILURE             = 0x87,
    PMM_INTERNAL_CAUSE_MM_AUTHENTICATION_FAILURE       = 0x88,
    PMM_INTERNAL_CAUSE_COVERAGE_LOST                   = 0x89,
    PMM_INTERNAL_CAUSE_USER_DETACH                     = 0x8A,
    PMM_INTERNAL_CAUSE_NULL                            = 0xFF
};


typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT32    ulT3312Value;
    VOS_UINT32    ulT3302Value;
    VOS_UINT8    aucPTmsi[LEN_PTMSI];
    VOS_UINT32    ulUserMode;
    enum     NET_MODE_ENUM           enNetMode;
    enum     PMM_MAIN_STATE_ENUM     enPMMMainState;
    enum     PMM_SUB_STATE_ENUM      enPMMSubState;
    enum     PMM_CAUSE_ENUM          enPMMCause;
    enum     RR_REL_CAUSE_ENUM       enRRReleaseCause;
    enum     PMM_INTERNAL_CAUSE_ENUM enPMMInternalCause;
    MOBILE_ID_STRUCT          IMSI;
    MOBILE_ID_STRUCT          IMEI;
    MOBILE_ID_STRUCT          IMEISV;
    VOS_UINT8    ucPTMSISignature[LEN_PTMSI_SIGNATURE];
    VOS_UINT8    ucRAI[LEN_RAI];
    VOS_UINT8    ucCKSN;
    VOS_UINT8    ucCipheringAlgorithm;
    VOS_UINT8    ucCK[LEN_CK];
    VOS_UINT8    ucIK[LEN_IK];
    VOS_UINT8    ucDRXPara[LEN_DRX];
    VOS_UINT8    ucNetworkCapability[LEN_NETWORK_CAPABILITY];
    VOS_UINT8    ucRACapability[LEN_RADIO_ACCESS_CAPABILITY];
} PMM_AGENT_INFO_STRU;

/*AGENT_MM_INQUIRE*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
} AGENT_MM_INQUIRE_STRU;

/*MM_AGENT_INFO*/
enum MM_STATE_ENUM
{
    MM_NULL                                        = 0x00,
    MM_IDLE                                        = 0x01,
    MM_WAITFOR_RR_CONNECT_LA_UPDATE                = 0x02,
    MM_WAITFOR_RR_CONNECT_MM_CONNECT               = 0x03,
    MM_WAITFOR_RR_CONNECT_IMSI_DETACH              = 0x04,
    MM_LA_UPDATE_PENDING                           = 0x05,
    MM_LA_UPDATE_INITIATED                         = 0x06,
    MM_WAITFOR_OUTGOING_MM_CONNECT                 = 0x07,
    MM_WAITFOR_ADDITIONAL_MM_CONNECT               = 0x08,
    MM_CONNECT_ACTIVE                              = 0x09,
    MM_IMSI_DETACH_INITIATED                       = 0x0a,
    MM_IMSI_DETACH_PENDING                         = 0x0b,
    MM_WAITFOR_NETWORK_COMMAND                     = 0x0c,
    MM_LOCATION_UPDATE_REJECTED                    = 0x0d,
    MM_PROCESS_CM_SERVICE_PROMPT,
    MM_WAIT_FOR_REESTABLISH,
    MM_WAIT_FOR_RR_ACTIVE,
    MM_CONNECTION_ACTIVE_GROUP_MODE,
    MM_WAIT_FOR_RR_CONNECTION_GROUP_MODE,
    MM_RR_CONNECTION_RELEASE_NOT_ALLOWED,
    MM_WAITFOR_ATTACH                             /*<==A32D11576*/
};


enum MM_SUBSTATE_ENUM
{
    MM_SUBSTATE_NULL                              = 0x00,
    MM_SUBSTATE_NORMAL_SERVICE                    = 0x01,
    MM_SUBSTATE_ATTEMPTING_TO_UPDATE              = 0x02,
    MM_SUBSTATE_LIMITED_SERVICE                   = 0x03,
    MM_SUBSTATE_NO_IMSI                           = 0x04,
    MM_SUBSTATE_NO_CELL_AVAILABLE                 = 0x05,
    MM_SUBSTATE_LA_UPDATE_NEEDED                  = 0x06,
    MM_SUBSTATE_PLMN_SEARCH                       = 0x07,
    MM_SUBSTATE_PLMN_SEARCH_NORMALSERVICE         = 0x08,
    MM_SUBSTATE_RCV_GROUP_CALL_NORMAL_SERVICE     = 0x09,
    MM_SUBSTATE_RCV_GROUP_CALL_LIMITED_SERVICE    = 0x0a
};

enum MM_LAUPDATE_STATUS_ENUM
{
    MM_UPDATE_STATUS_UPDATED                                        = 0,
    MM_UPDATE_STATUS_NOT_UPDATED                                    = 1,
    MM_UPDATE_STATUS_PLMN_NOT_ALLOW                                 = 2,
    MM_UPDATE_STATUS_LA_NOT_ALLOW                                   = 3,
    MM_UPDATE_STATUS_ROAM_NOT_ALLOW                                 = 4,
    MM_UPDATE_STATUS_NULL                                           = 7
};

typedef struct
{
    VOS_UINT8                          aucTmsi[MM_TMSI_LENGTH];
    VOS_UINT8                          aucLai[MM_LAI_LENGTH];
    enum MM_LAUPDATE_STATUS_ENUM   enLaUpdateStatus;
    VOS_UINT8                          ucTmsiValidFlag;
} LA_INFO_STRU;

enum MM_CAUSE_ENUM
{
    MM_CAUSE_NO_CAUSE                              = 0,
    MM_CAUSE_IMSI_UNKNOW_IN_HLR                    = 2,
    MM_CAUSE_ILLEGAL_MS                            = 3,
    MM_CAUSE_IMSI_UNKNOW_IN_VLR                    = 4,
    MM_CAUSE_IMEI_NOT_ACCEPT                       = 5,
    MM_CAUSE_ILLEGAL_ME                            = 6,
    MM_CAUSE_GPRS_SERVICES_NOT_ALLOWED             = 7,
    MM_CAUSE_GPRS_NONGPRS_SERVICE_NOT_ALLOWED      = 8,
    MM_CAUSE_MS_ID_CANOT_BE_DERIVED_BY_NETWORK     = 9,
    MM_CAUSE_IMPLICITLY_DETACHED                   = 10,
    MM_CAUSE_PLMN_NOT_ALLOWED                      = 11,
    MM_CAUSE_LA_NOT_ALLOWED                        = 12,
    MM_CAUSE_ROAM_NOT_ALLOWED                      = 13,
    MM_CAUSE_GPRS_SERVICE_NOT_ALLOW_IN_THIS_PLMN   = 14,
    MM_CAUSE_NO_SUITABLE_CELL_IN_THIS_LA           = 15,
    MM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE         = 16,
    MM_CAUSE_NETWORK_FAILURE                       = 17,
    MM_CAUSE_MAC_FAILURE                           = 20,
    MM_CAUSE_SYNC_FAILURE                          = 21,
    MM_CAUSE_CONGESTION                            = 22,
    MM_CAUSE_GSM_AUTH_UNACCEPTABLE                 = 23,
    MM_CAUSE_SERVICE_NOT_SUPPORT                   = 32,
    MM_CAUSE_SERVICE_NOT_SUBSCRIBED                = 33,
    MM_CAUSE_SERVICE_TEMP_OUTOF_ORDER              = 34,
    MM_CAUSE_CALL_CAN_NOT_IDENTIFIED               = 38,
    MM_CAUSE_SEMANTICALLY_INCORRECT                = 95,
    MM_CAUSE_INVALID_MANDATORY_INFORMATION         = 96,
    MM_CAUSE_MSG_TYPE_NO_EXIST                     = 97,
    MM_CAUSE_MSG_TYPE_NOT_COMPATIBLE               = 98,
    MM_CAUSE_IE_NO_EXIST                           = 99,
    MM_CAUSE_CONDITIONAL_IE_ERROR                  = 100,
    MM_CAUSE_MSG_NOT_COMPATIBLE_STATE              = 101,
    MM_CAUSE_PROTOCOL_ERROR                        = 111
};

typedef struct
{
    VOS_UINT8    ucClassmark2Length;
    VOS_UINT8    ucClassmark2[3];
} CLASSMARK2;

typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT32    ulT3212Length;
    VOS_UINT32    ulUserMode;
    enum     MM_STATE_ENUM      enMmState;
    enum     MM_SUBSTATE_ENUM   enSubState;
    enum     MM_CAUSE_ENUM      enRejectCause ;
    LA_INFO_STRU       LaInfo;
    MOBILE_ID_STRUCT   IMSI;
    MOBILE_ID_STRUCT   IMEI;
    MOBILE_ID_STRUCT   IMEISV;
    CLASSMARK2         Classmark2;
    VOS_UINT8    ucCipherSequenceNum;
    VOS_UINT8    ucCipheringAlgorithm;
    VOS_UINT8    ucCipheringKey[CIPHERIGN_KEY_LENGTH];
    VOS_UINT8    ucIntegrityKey[INTEGRITY_KEY_LENGTH];
    VOS_UINT8    ucClassmark1;
    VOS_UINT8    ucAttFlag;
} MM_AGENT_INFO_STRU;

/*PMM_AGENT_PROCEDURE_IND*/

#if 0
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT16                      usMsgType;      /* 调试消息，从0x5001～0x5FFF，各模块划分规则待定 */
    VOS_UINT16                      usTransId;      /* 子进程标识,用于定位子进程 */
    OM_APP_HEADER_WITHSN                            /* 该消息头填充PS的PID和TOOL_ID,保证消息能转发给相应的PC模块*/

    VOS_UINT32    ulT3212Length;
    VOS_UINT32    ulUserMode;
    enum     MM_STATE_ENUM      enMmState;
    enum     MM_SUBSTATE_ENUM   enSubState;
    enum     MM_CAUSE_ENUM      enRejectCause ;
    LA_INFO_STRU       LaInfo;
    MOBILE_ID_STRUCT   IMSI;
    MOBILE_ID_STRUCT   IMEI;
    MOBILE_ID_STRUCT   IMEISV;
    CLASSMARK2         Classmark2;
    VOS_UINT8    ucCipherSequenceNum;
    VOS_UINT8    ucCipheringAlgorithm;
    VOS_UINT8    ucCipheringKey[CIPHERIGN_KEY_LENGTH];
    VOS_UINT8    ucIntegrityKey[INTEGRITY_KEY_LENGTH];
    VOS_UINT8    ucClassmark1;
    VOS_UINT8    ucAttFlag;
} MM_TRANS_AGENT_INFO_STRU;
#endif

/*PMM_AGENT_PROCEDURE_IND*/
typedef struct
{
      VOS_MSG_HEADER_IT
      VOS_UINT32   ulMessageId;
      VOS_UINT32   ulProcInfo;
} PMM_AGENT_PROCEDURE_IND_STRU;

/*MM_AGENT_PROCEDURE_IND*/
typedef struct
{
      VOS_MSG_HEADER_IT
      VOS_UINT32   ulMessageId;
      VOS_UINT32   ulProcInfo;
} MM_AGENT_PROCEDURE_IND_STRU;
/****************the Interface of AGENT and PMM/MM Define End**************/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/****************the Interface of AGENT and SM Define Begin **************/
/*AGENT_SM_PDPNUM_INQUIRE*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
} AGENT_SM_PDPNUM_INQUIRE_STRU;

/*AGENT_SM_PDPNUM_IND*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT8    ucPDPNum;
    VOS_UINT8    ucNSAPI[MAX_PDP_NUM];
} AGENT_SM_PDPNUM_IND_STRU;

/*AGENT_SM_INQUIRE*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT8    ucNSAPI;
} AGENT_SM_INQUIRE_STRU;

/*SM_AGENT_INFO*/
enum  PDP_STATE
{
    PDP_INACTIVE,
    PDP_ACTIVE_PENDING,
    PDP_MODIFY_PENDING,
    PDP_INACTIVE_PENDING,
    PDP_ACTIVE
};

enum  PMM_CONNECTION
{
    PMM_DISCONNECTED,
    PMM_CONNECTED,
    PMM_CONNECTING
};

enum  TI_STATE
{
    TI_IDLE,
    TI_ALLOCATED,
    TI_EXTENSION
};

enum  NSAPI_STATE
{
    NSAPI_IDLE,
    NSAPI_ALLOCATED,
    NSAPI_RESERVED
};

enum  TIMER_STATE
{
    TIMER_ACTIVE,
    TIMER_INVALID
};

enum REACTIVATE_FLAG
{
    PDP_NORMAL,
    PDP_REACTIVATE
};

typedef struct
{
    VOS_UINT8 ucValidityFlag;
    VOS_UINT8 ucb3DelayClass ;
    VOS_UINT8 ucb3ReliabClass;
    VOS_UINT8 ucb4PeakThrough;
    VOS_UINT8 ucb3PrecedenceClass;
    VOS_UINT8 ucb5MeanThrough;
    VOS_UINT8 ucb3TraffClass;
    VOS_UINT8 ucb2DeliverOrder;
    VOS_UINT8 ucb3DeliverOfErrSdu;
    VOS_UINT8 ucMaximSduSize;
    VOS_UINT8 ucMaxBitRateForUp;
    VOS_UINT8 ucMaxBitRateForDown;
    VOS_UINT8 ucb4ResidualBer;
    VOS_UINT8 ucb4SduErrRatio;
    VOS_UINT8 ucb6TransDelay;
    VOS_UINT8 ucb2TraffHandlPrior;
    VOS_UINT8 ucGuarantBitRateForUp;
    VOS_UINT8 ucGuarantBitRateForDown;
} SMQOS;

/* Record some public state in SM process */
typedef struct
{
    enum    PDP_STATE       enCurrentPdpState;
    enum    TI_STATE        enTiState;
    enum    TIMER_STATE     enTimerState;
    enum    REACTIVATE_FLAG enReactivateFlag;
    VOS_UINT32   ulResendCounter;
    VOS_UINT32   ulNsapi;
    VOS_UINT32   ulLinkedTi;
} SM_INFO_TO_BG;

typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT32    ulTi;
    VOS_UINT8    ucNSAPI;
    enum     NSAPI_STATE      enNsapiStateToBG;
    enum     PMM_CONNECTION   enPmmConnectionToBG;
    SM_INFO_TO_BG    SmInfoToBG;
    SMQOS             QosToBg;
} SM_AGENT_INFO_STRU;

/*SM_AGENT_STATUS_IND*/
enum SM_CAUSE_ENUM
{
    SM_NETWORK_CAUSE_LLC_OR_SNDCP_FAILURE,
    SM_NETWORK_CAUSE_INSUFFICIENT_RESOURCES,
    SM_NETWORK_CAUSE_MISS_OR_UNKNOWN_APN,
    SM_NETWORK_CAUSE_UNKNOWN_PDP_ADDRESS_OR_PDP_TYPE,
    SM_NETWORK_CAUSE_USER_AUTHENTICATION_FAILED,
    SM_NETWORK_CAUSE_ACTIVATION_REJECTED_BY_GGSN,
    SM_NETWORK_CAUSE_ACTIVATION_REJECTED_UNSPECIFIED,
    SM_NETWORK_CAUSE_SERVICE_OPTION_NOT_SUPPORTED,
    SM_NETWORK_CAUSE_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED,
    SM_NETWORK_CAUSE_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER,
    SM_NETWORK_CAUSE_NSAPI_ALREADY_USED,
    SM_NETWORK_CAUSE_REGULAR_DEACTIVATION,
    SM_NETWORK_CAUSE_QOS_NOT_ACCEPTED,
    SM_NETWORK_CAUSE_NETWORK_FAILURE,
    SM_NETWORK_CAUSE_REACTIVATION_REQUIRED,
    SM_NETWORK_CAUSE_SEMANTIC_ERROR_IN_THE_TFT_OPERATION,
    SM_NETWORK_CAUSE_SYNTACTICAL_ERROR_IN_THE_TFT_OPERATION,
    SM_NETWORK_CAUSE_UNKNOWN_PDP_CONTEXT,
    SM_NETWORK_CAUSE_SEMANTIC_ERRORS_IN_PACKET_FILTER,
    SM_NETWORK_CAUSE_SYNTACTICAL_ERRORS_IN_PACKET_FILTER,
    SM_NETWORK_CAUSE_PDP_CONTEXT_WITHOUT_TFT_ALREADY_ACTIVATED,
    SM_NETWORK_CAUSE_INVALID_TI_VALUE,
    SM_NETWORK_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE,
    SM_NETWORK_CAUSE_INVALID_MANDATORY_INFORMATION,
    SM_NETWORK_CAUSE_MESSAGE_TYPE_NON_EXISTENT,
    SM_NETWORK_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE,
    SM_NETWORK_CAUSE_NETWORK_CAUSE_IE_NON_EXISTENT,
    SM_NETWORK_CAUSE_CONDITIONAL_IE_ERROR,
    SM_NETWORK_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE,
    SM_NETWORK_CAUSE_PROTOCOL_ERROR_UNSPECIFIED,
    SM_INTERNAL_NO_TI_RELATED_TO_NSAPI,
    SM_INTERNAL_NSAPI_HAS_BEEN_OCCUPIED,
    SM_INTERNAL_PMM_RELEASED,
    SM_INTERNAL_T3380_EXPIRE,
    SM_INTERNAL_T3381_EXPIRE,
    SM_INTERNAL_REACTIVATION_RUNNING,
    SM_INTERNAL_REACTIVATION_FAILURE,
    SM_INTERNAL_MS_NETWORK_COLLISION,
    SM_INTERNAL_LINKED_TI_NOT_ACTIVE,
    SM_INTERNAL_NO_IDLE_NSAPI
};

typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    enum     SM_CAUSE_ENUM    enSmCause;
    VOS_UINT8    ucTi;
    VOS_UINT8    ucDirection;
} UUI_AGENT_SM_STATUS_IND_STRU;
/****************the Interface of AGENT and SM Define End****************/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/****************the Interface of AGENT and USIM Define Begin ***********/
/*AGENT_USIM_SET_MOBILEID*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
    VOS_UINT8    ucMobileId;
    VOS_UINT8    ucMobileIdLength;
    VOS_UINT8    ucMobileIdValue[LEN_MOBILE_ID];
} AGENT_USIM_SET_MOBILEID_STRU;

/*AGENT_USIM_SET_DEFAULT_DATA*/
typedef struct
{
    VOS_MSG_HEADER_IT
    VOS_UINT32    ulMessageId;
} AGENT_USIM_SET_DEFAULT_DATA_STRU;
/****************the Interface of AGENT and USIM Define End*********************/

#define RLC_SETDATARATEDISPLAY_STOP   0         /* 停止上报                    */
#define RLC_SETDATARATEDISPLAY_START  1         /* 开始上报                    */

#define MAC_DATA_RATE_DISPLAY_OPEN    1
#define MAC_DATA_RATE_DISPLAY_SHUT    0

#define MAC_FTP_START                 1         /* MAC下行译码数据收集功能已启动 */
#define MAC_FTP_STOP                  0         /* MAC下行译码数据收集功能未启动 */

#define AMR_LOOP_STOP                 0         /* 停止AMR自环操作               */
#define AMR_LOOP_START                1         /* 开始AMR自环操作               */

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

#endif

