

#ifndef __CNAS_HSM_SND_INTERNAL_MSG_H__
#define __CNAS_HSM_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmEncode.h"
#include "cas_hrpd_sessioncfg_nas_pif.h"

#include "cas_hrpd_sessioncfg_session_layer_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/


enum CNAS_HSM_INTERNAL_MSG_TYPE_ENUM
{
    ID_CNAS_HSM_HSM_UATI_REQ                        = 0x0000,       /* _H2ASN_MsgChoice CNAS_HSM_HSM_UATI_REQ_STRU*/
    ID_CNAS_HSM_HSM_SESSION_ACTIVE_REQ,                             /* _H2ASN_MsgChoice CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU*/
    ID_CNAS_HSM_HSM_SESSION_DEACTIVE_REQ,                           /* _H2ASN_MsgChoice CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU*/
    ID_CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND,                        /* _H2ASN_MsgChoice CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU*/
    ID_CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND,                      /* _H2ASN_MsgChoice CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU*/
    ID_CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND,                    /* _H2ASN_MsgChoice CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU*/

    ID_CNAS_HSM_HSM_SWITCH_ON_REQ,                                  /* _H2ASN_MsgChoice CNAS_HSM_HSM_READ_SWITCH_ON_STRU*/
    ID_CNAS_HSM_HSM_SWITCH_ON_RESULT_IND,                           /* _H2ASN_MsgChoice CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU*/
    ID_CNAS_HSM_HSM_SESSION_CLOSE_IND,                              /* _H2ASN_MsgChoice CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU*/

    ID_CNAS_HSM_HSM_CONN_MNMT_REQ,                                  /* _H2ASN_MsgChoice CNAS_HSM_HSM_CONN_MNMT_REQ_STRU*/
    ID_CNAS_HSM_HSM_CONN_MNMT_RESULT_IND,                           /* _H2ASN_MsgChoice CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU*/

    ID_CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF,                           /* _H2ASN_MsgChoice CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU*/

#ifdef DMT
    ID_CNAS_HSM_HSM_MODIFY_SESSION_SEED_REQ,                        /* _H2ASN_MsgChoice CNAS_HSM_HSM_MODIFY_SESSION_SEED_REQ_STRU*/
    ID_CNAS_HSM_HSM_MODIFY_CUR_SYS_TICK_REQ,                        /* _H2ASN_MsgChoice CNAS_HSM_HSM_MODIFY_CUR_SYS_TICK_REQ_STRU*/
    ID_CNAS_HSM_HSM_RCV_FWD_TRAF_CHAN_DATA_IND,                     /* _H2ASN_MsgChoice CNAS_HSM_HSM_RCV_FWD_TRAF_CHAN_DATA_IND_STRU*/
    ID_CNAS_HSM_HSM_MODIFY_SMP_AMP_ATTR_REQ,                        /* _H2ASN_MsgChoice CNAS_HSM_HSM_MODIFY_SMP_AMP_ATTR_REQ_STRU*/
#endif

    ID_CNAS_HSM_HSM_PIF_MSG_TYPE_ENUM_BUTT
};
typedef VOS_UINT16 CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 Enumeration Name    : CNAS_HSM_UATI_REQUEST_RESULT_ENUM
 Description         : The HSM module UATI REQEUST result type enum
 1.DATE              : 26/1/2015
   AUTHOR            : w00176964
   Modification      : Create
 2.DATE              : 26/11/2015
   AUTHOR            : m00312079
   Modification      : DTS2015111102189:添加Cancel原因值
*****************************************************************************/

enum CNAS_HSM_UATI_REQUEST_RESULT_ENUM
{
    CNAS_HSM_UATI_REQUEST_RESULT_SUCC,
    CNAS_HSM_UATI_REQUEST_RESULT_FAIL,
    CNAS_HSM_UATI_REQUEST_RESULT_CANCEL,

    CNAS_HSM_UATI_REQUEST_RESULT_BUTT
};
typedef VOS_UINT8 CNAS_HSM_UATI_REQUEST_RESULT_ENUM_UINT8;


enum CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM
{
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_REACH_MAX_CNT,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SUSPEND,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_SAVE,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_OFF,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_EHRPD_NOT_AVAILABLE,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_PA_MODE_NTF,

    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_KEEP_ALIVE_EXP,

    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_NEG_FAIL,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_AN_EXP,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_FAIL,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_DENY,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_PERS_INVALID,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_RSP_EXP,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_MSG_FAIL,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_AN_GAUP_FAIL,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_IRAT_TO_LTE,
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_NO_RF,

    CNAS_HSM_UATI_REQUEST_FAIL_REASON_BUTT
};

typedef VOS_UINT8 CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8;



enum CNAS_HSM_SESSION_ACTIVE_RESULT_ENUM
{
    CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL,
    CNAS_HSM_SESSION_ACTIVE_RESULT_SUCC,

    CNAS_HSM_SESSION_ACTIVE_RESULT_BUTT
};
typedef VOS_UINT8 CNAS_HSM_SESSION_ACTIVE_RESULT_ENUM_UINT8;


enum CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM
{
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_NEG_FAIL,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_AN_EXP,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_FAIL,

    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ,

    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_PERS_INVALID,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_RSP_EXP,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_MSG_FAIL,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_AN_GAUP_FAIL,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_IRAT_TO_LTE,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_NO_RF,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_WAIT_SCP_CNF_EXP,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_POWER_OFF,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_POWER_SAVE,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_SUSPEND,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_NETWORK_LOST,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION,
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_OHM,

    CNAS_HSM_SESSION_ACT_FAIL_REASON_BUTT
};

typedef VOS_UINT8 CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8;



enum CNAS_HSM_CONN_MNMT_RESULT_ENUM
{
    CNAS_HSM_CONN_MNMT_RESULT_FAIL,
    CNAS_HSM_CONN_MNMT_RESULT_SUCC,

    CNAS_HSM_CONN_MNMT_RESULT_BUTT
};
typedef VOS_UINT8 CNAS_HSM_CONN_MNMT_RESULT_ENUM_UINT8;

/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_UATI_REQ_TRIGGER_ENUM_UINT8                    enTriggerReason;
    VOS_UINT8                                               aucRsv[3];
}CNAS_HSM_HSM_UATI_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason;
    VOS_UINT8                                               aucRsv[3];
}CNAS_HSM_HSM_SESSION_ACTIVE_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;
    VOS_UINT8                                               aucRsv[3];
}CNAS_HSM_HSM_SESSION_DEACTIVE_REQ_STRU;




typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_UATI_REQUEST_RESULT_ENUM_UINT8                 enRslt;
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enFailReason;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_SESSION_ACTIVE_RESULT_ENUM_UINT8               enRslt;
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enFailReason;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;
    VOS_UINT8                                               aucRsv[3];
}CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
}CNAS_HSM_HSM_READ_SWITCH_ON_STRU;


typedef struct
{
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enResult;
    PS_BOOL_ENUM_UINT8                                      enProtocolTypeVaildFlag;
    VOS_UINT16                                              usProtocolType;
    VOS_UINT16                                              usProtocolSubType;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_HSM_SESSION_NEG_RSLT_INFO;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_ENUM_UINT8    enScene;                /* 发送ID_CNAS_HSM_HSM_SESSION_CLOSE_IND消息的场景 */
    VOS_UINT8                                               aucRsv[3];
    CNAS_HSM_HSM_SESSION_NEG_RSLT_INFO                      stSessionNegRsltInfo;   /* 仅在enScene是RCV_CAS_NEG_RSLD_IND有含义 */
}CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
}CNAS_HSM_HSM_SWITCH_ON_RESULT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    VOS_UINT8                                               aucReserve[3];
}CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU;

#ifdef DMT

typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT32                                              ulSessionSeed;
}CNAS_HSM_HSM_MODIFY_SESSION_SEED_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT32                                              ulCurSysTick;
}CNAS_HSM_HSM_MODIFY_CUR_SYS_TICK_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
}CNAS_HSM_HSM_RCV_FWD_TRAF_CHAN_DATA_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU                        stHsmAmpNegAttribs;
    CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU                        stHsmSmpNegAttribs;
}CNAS_HSM_HSM_MODIFY_SMP_AMP_ATTR_REQ_STRU;
#endif


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    VOS_UINT8                                               aucRsv[3];
}CNAS_HSM_HSM_CONN_MNMT_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    CNAS_HSM_CONN_MNMT_RESULT_ENUM_UINT8                    enRslt;
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU;



typedef struct
{
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enUatiFailReason;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_UATI_FAIL_REASON_MAP_SESSION_DEACTVE_REASON_STRU;


typedef struct
{
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enSessionActFailReason;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_SESSION_ACT_FAIL_REASON_MAP_SESSION_DEACT_REASON_STRU;

/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_HSM_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}CNAS_HSM_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT16*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_HSM_INTERNAL_MSG_DATA          stMsgData;
}CNAS_HSM_INTERNAL_MSG;

/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_VOID CNAS_HSM_SndInternalUATIReq(
    CNAS_HSM_UATI_REQ_TRIGGER_ENUM_UINT8                    enTriggerReason
);

/* Added Session Active Reason input argument */
VOS_VOID CNAS_HSM_SndInternalSessionActiveReq(
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason
);

extern VOS_VOID CNAS_HSM_SndInternalSessionDeactiveReq(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
);
extern VOS_VOID CNAS_HSM_SndInternalUATIRequestResultInd(
    CNAS_HSM_UATI_REQUEST_RESULT_ENUM_UINT8                 enRslt,
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
);
extern VOS_VOID CNAS_HSM_SndInternalSessionActiveResultInd(
    CNAS_HSM_SESSION_ACTIVE_RESULT_ENUM_UINT8               enRslt,
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
);

extern VOS_VOID CNAS_HSM_SndInternalSessionDeactiveResultInd(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
);

extern VOS_VOID CNAS_HSM_SndInternalSwitchOnReq(VOS_VOID);
extern VOS_VOID CNAS_HSM_SndInternalSwitchOnResultInd(VOS_VOID);
extern VOS_VOID CNAS_HSM_SndInternalSessionCloseInd(
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_ENUM_UINT8    enScene,
    CNAS_HSM_HSM_SESSION_NEG_RSLT_INFO                     *pstSessionNegRsltInfo
);

extern VOS_VOID CNAS_HSM_SndInternalConnMnmtReq(
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8           enTriggerScene
);

extern VOS_VOID CNAS_HSM_SndInternalConnMnmtResultInd(
    CNAS_HSM_CONN_MNMT_RESULT_ENUM_UINT8                    enRslt,
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene
);

VOS_VOID CNAS_HSM_BuildHsmHrpdPaRatModeNtfMsg(
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstCasHrpdPaRatModeNtf,
    CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF_STRU                 *pstHsmHrpdPaRatModeNtf
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

#endif /* end of CnasHsmSndInternalMsg.h */



