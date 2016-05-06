

#ifndef __CNAS_HSM_CTX_H__
#define __CNAS_HSM_CTX_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
#include "hsm_hsd_pif.h"
#include "cas_hrpd_overheadmsg_nas_pif.h"

#include "ehsm_hsm_pif.h"
#include "hsm_aps_pif.h"
#include "CnasHsmFsmCachedMsgPriMnmt.h"
#include "CnasHsmFsmTbl.h"
#include "CnasCcb.h"

#include  "NasNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
/* buffer message max length */
#define CNAS_HSM_MAX_MSG_BUFFER_LEN                         (1600)

/* cache message queue max size number */
#define CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM                    (8)

#define CNAS_HSM_INVAILD_CACHE_INDEX                        (0xFF)

/* MEID byte number */
#define CNAS_HSM_MEID_OCTET_NUM                             (7)

/* ESN byte number */
#define CNAS_HSM_ESN_OCTET_NUM                              (4)

#define CNAS_HSM_ICCID_OCTET_NUM                            (10)

/* UATI104 bit length */
#define CNAS_HSM_UATI104_BIT_LENGTH                         (104)

/* UATI024 bit length */
#define CNAS_HSM_UATI024_BIT_LENGTH                         (24)

#define CNAS_HSM_UATI_OCTET_LENGTH                          (16)

#define CNAS_HSM_MAX_UATI_REC_NUM                           (5)

#define CNAS_HSM_MAX_UPPER_OLD_UATI_OCTETS                  (13)

#define CNAS_HSM_RAND_A_VAL                                 (16807)

#define CNAS_HSM_RAND_M_VAL                                 (2147483647)

/* max internal message queue size number */
#define CNAS_HSM_MAX_INT_MSG_QUEUE_NUM                      (8)

/* invalid ATI value */
#define CNAS_HSM_INVALID_ATI_VALUE                          (0xFF)

#define CNAS_HSM_MSG_PRIORITY_SESSION_CLOSE                 (40)

/* 8 bits per 1 byte */
#define CNAS_HSM_BIT_LEN_PER_BYTE                           (8)

#define CNAS_HSM_MSG_PRIORITY_HARDWARE_ID_RESP              (40)

#define CNAS_HSM_ATI_VALUE_LENGTH                           (4)


/* -2592000 =< RANGE <= 2592000 (-180degree to 180 degree)*/
#define CNAS_HSM_INVALIDE_LONGITUDE                         (0x7FFFFFFF)
/* -1296000 =< RANGE <= 1296000 (-90degree to 90 degree)*/
#define CNAS_HSM_INVALIDE_LATITUDE                          (0x7FFFFFFF)

#define CNAS_HSM_180DEGREE                                  (0x278D00)
#define CNAS_HSM_360DEGREE                                  (0x4F1A00)

#define CNAS_HSM_SUBNET_ID_MAX_LENGTH                       (16)
#define CNAS_HSM_SECOND_COLORCODE_MAX_LENGTH                (7)


#define CNAS_HSM_DEFAULT_SESSION_ACT_MAX_CNT_CONN_FAIL      (5) /* Session激活时，连接失败原因导致session激活失败时的默认最大尝试次数     */
                                                                /* 连接失败的原因值: CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_FAIL  */
                                                                /*                   CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_FDENY */
#define CNAS_HSM_DEFAULT_SESSION_ACT_MAX_CNT_OTHER_FAIL     (3) /* Session激活时，其它失败原因导致session激活失败时的默认最大尝试次数 */

#define CNAS_HSM_AN_AUTH_MAX_REJECT_CNT                     (3) /* AN鉴权被网侧连续拒绝的最大次数，CDG143建议3次 */

#define CNAS_HSM_UATI_ASSIGN_MSG_SEQ_NUM_INIT_VALUE         ( 255 )


#define CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME                 (2)

#define CNAS_HSM_MSG_PRIORITY_KEEP_ALVIE_REQ            (40)
#define CNAS_HSM_MSG_PRIORITY_KEEP_ALVIE_RSP            (40)

#define CNAS_HSM_MIN_WAIT_UATI_ASSIGN_TIMER_LEN         (5)     /* 单位:秒 */
#define CNAS_HSM_MAX_WAIT_UATI_ASSIGN_TIMER_LEN         (120)   /* 单位:秒 */

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

/*****************************************************************************
 Enumeration Name    : CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM
 Description         : The Close Reason of SessionClose message
                       C.S0024-A_v3.0_060912.pdf [Section:7.2.6.2.1]
 1.DATE              : 02/02/2015
   AUTHOR            : s00250401
   Modification      : Create
 2.DATE              : 2015-05-30
   AUTHOR            : y00174758
   Modification      : Lint时文件重复包含错误，从CnasHsmEncode.h移过来
*****************************************************************************/
enum CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM
{
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_NORMAL                       = 0x00,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_REPLY                        = 0x01,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR                     = 0x02,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL               = 0x03,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_NEG_ERR                 = 0x04,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_SESS_CONF_FAIL               = 0x05,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_SESS_LOST                    = 0x06,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_SESS_UNREACHABLE             = 0x07,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_SESS_RES_BUSY                = 0x08,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_BUTT
};
typedef VOS_UINT8 CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM_UINT8;


enum CNAS_HSM_SESSION_DEACT_REASON_ENUM
{
    CNAS_HSM_SESSION_DEACT_REASON_SCP_NEG_FAIL,                         /*  0: CAS_CNAS_HRPD_SCP_NEG_RSLT_FAILURE */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_EXP,                           /*  1: CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_EXPIRED */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_FAIL,                   /*  2: CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ, /*  3: CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ, /*  4: CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_PERS_INVALID,                     /*  5: CAS_CNAS_HRPD_SCP_NEG_RSLT_PERSONALITY_INVALID */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_RSP_EXP,                      /*  6: CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_RSP_EXPIRED */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_MSG_FAIL,                     /*  7: CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_MSG_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_GAUP_FAIL,                     /*  8: CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_GAUP_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_IRAT_TO_LTE,                      /*  9: CAS_CNAS_HRPD_SCP_NEG_RSLT_IRAT_TO_LTE */
    CNAS_HSM_SESSION_DEACT_REASON_SCP_NO_RF,                            /*  10: CAS_CNAS_HRPD_SCP_NEG_RSLT_NO_RF */

    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_NEG_FAIL,        /* 11: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason FAILURE */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_AN_EXP,          /* 12: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason AN_EXPIRED */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CONN_OPEN_FAIL,  /* 13: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason CONN_OPEN_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_CONN_OPEN_DENY,      /* 14: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason CONN_OPEN_DENY */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_PERS_INVALID,        /* 15: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason PERSONALITY_INVALID */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CFG_RSP_EXP,     /* 16: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason CFG_RSP_EXPIRED */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CFG_MSG_FAIL,    /* 17: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason CFG_MSG_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_AN_GAUP_FAIL,    /* 18: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason AN_GAUP_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_IRAT_TO_LTE,     /* 19: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RAT_TO_LTE */
    CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_NO_RF,           /* 20: ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason NO_RF */

    CNAS_HSM_SESSION_DEACT_REASON_NETWORK_LOST_IN_SESSION_ACT,          /* 21: ID_CAS_CNAS_HRPD_NETWORK_LOST_IND */
    CNAS_HSM_SESSION_DEACT_REASON_WAIT_SCP_CNF_EXP,                     /* 22: Protect timer expire when wait ID_CAS_CNAS_HRPD_SCP_ACTIVE_CNF */

    CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_UATI_REACH_MAX_CNT,          /* 23: AMP FAIL: UATI fail after 5 times try */
    CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_SYS_ACQ_SUBNET_CHANGE,       /* 24: AMP FAIL: Subnet change after acq system */
    CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_OTHER_SCENE,                 /* 25: AMP FAIL: Other scene  */

    CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD,                        /* 26: Previous session is EHRPD, change to HRPD */
    CNAS_HSM_SESSION_DEACT_REASON_HRPD_TO_EHRPD,                        /* 27: Previous session is HRPD, change to EHRPD */

    CNAS_HSM_SESSION_DEACT_REASON_AN_CLOSE_SESSION_IN_VACANT,           /* 28: Receive SessionClose in VACANT state*/

    CNAS_HSM_SESSION_DEACT_REASON_INTERNAL_SESSION_CLOSE_IN_CONN_MNMT,  /* 29: Receive ID_CNAS_HSM_HSM_SESSION_CLOSE_IND in Substate CONN_MNMT */

    CNAS_HSM_SESSION_DEACT_REASON_KEEP_ALIVE_EXP_OPEN,                  /* 30: Keep alive timer expire in open state */
    CNAS_HSM_SESSION_DEACT_REASON_INTERNAL_SESSION_CLOSE_SLAVE,         /* 31: Receive ID_CNAS_HSM_HSM_SESSION_CLOSE_IND in slave state */

    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SUSPEND,                /* 32: UATI is aborted by ID_HSD_HSM_SUSPEND_IND */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_POWER_SAVE,             /* 33: UATI is aborted by ID_HSD_HSM_POWER_SAVE_REQ */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_POWER_OFF,              /* 34: UATI is aborted by ID_HSD_HSM_POWEROFF_REQ */

    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_NETWORK_LOST,           /* 35: UATI is aborted by ID_CAS_CNAS_HRPD_NETWORK_LOST_IND */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_AN_CLOSE_SESSION,       /* 36: UATI is aborted by AN send session close */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_EHRPD_NOT_AVAILABLE,    /* 37: UATI is aborted by ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND，该场景不存在，保留该原因 */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_PA_MODE_NTF,            /* 38: UATI is aborted by ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF */

    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_KEEP_ALIVE_EXP,         /* 39: UATI is aborted by keep alive timer expire */

    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_NEG_FAIL,           /* 40: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_FAILURE */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_AN_EXP,             /* 41: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_AN_EXPIRED */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CONN_OPEN_FAIL,     /* 42: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_CONN_OPEN_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CONN_OPEN_DENY,     /* 43: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_CONN_OPEN_DENY */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_PERS_INVALID,       /* 44: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_PERSONALITY_INVALID */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_RSP_EXP,        /* 45: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_CFG_RSP_EXPIRED */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_MSG_FAIL,       /* 46: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_CFG_MSG_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_AN_GAUP_FAIL,   /* 47: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_AN_GAUP_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_IRAT_TO_LTE,        /* 48: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_IRAT_TO_LTE */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_NO_RF,              /* 49: UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_NO_RF */

    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_SUSPEND,             /* 50: Session active is aborted by ID_HSD_HSM_SUSPEND_IND */
    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_POWER_SAVE,          /* 51: Session active is aborted by ID_HSD_HSM_POWER_SAVE_REQ */
    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_POWER_OFF,           /* 52: Session active is aborted by ID_HSD_HSM_POWEROFF_REQ */
    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_AN_CLOSE_SESSION,    /* 53: Session active is aborted by AN send session close */
    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_OHM,                 /* 54: Session active is aborted by OHM */

    CNAS_HSM_SESSION_DEACT_REASON_SESSION_DEACT_ABORT,                      /* 55: Session deactive is aborted */

    CNAS_HSM_SESSION_DEACT_REASON_BUTT = 0xFF
};
typedef VOS_UINT8 CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8;

/*****************************************************************************
 Enumeration Name    : CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM
 Description         : session deactive需要启动修正定时器的场景,数值越小，优先级越高
 1.DATE              : 12/11/15
   AUTHOR            : y00307564
   Modification      : Create
*****************************************************************************/
enum CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM
{
    CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_POWER_OFF,
    CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_POWER_SAVE,

    CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_BUTT              = 0xFF
};
typedef VOS_UINT8 CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM_UINT8;


enum CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_ENUM
{
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_SETUP,
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_SESSION_ACT,
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_NOT_SESSION_ACT,
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_RCV_CAS_NEG_RSLD_IND,
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_KEEP_ALIVE_EXP_OPEN,
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_KEEP_ALIVE_EXP_SLAVE,
    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_IN_CONN_MNMT_SENT_SESSION_CLOSE,

    CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_BUTT = 0xFF
};
typedef VOS_UINT8 CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_ENUM_UINT8;


enum CNAS_HSM_SESSION_ACTIVE_REASON_ENUM
{
    CNAS_HSM_SESSION_ACTIVE_REASON_NEG,             /* CNAS_CAS_HRPD_SCP_ACTIVE_TYPE_NEG */

    CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY,        /* CNAS_CAS_HRPD_SCP_ACTIVE_TYPE_RECOVERY */

    CNAS_HSM_SESSION_ACTIVE_REASON_BUTT = 0xFF
};
typedef VOS_UINT8 CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8;


enum CNAS_HSM_PROTOCOL_TYPE_ENUM
{
    CNAS_HSM_SESSION_MANAGEMENT_PROTOCOL               = 0x0010,
    CNAS_HSM_ADDRESS_MANAGEMENT_PROTOCOL               = 0x0011,
    CNAS_HSM_PROTOCOL_TYPE_BUTT
};

typedef VOS_UINT16 CNAS_HSM_PROTOCOL_TYPE_ENUM_UINT16;


enum CNAS_HSM_INIT_CTX_TYPE_ENUM
{
    CNAS_HSM_INIT_CTX_STARTUP                    = 0,
    CNAS_HSM_INIT_CTX_POWEROFF                   = 1,
    CNAS_HSM_INIT_CTX_BUTT
};
typedef VOS_UINT8 CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8;



enum CNAS_HSM_HARDWARE_ID_TYPE_ENUM
{
    CNAS_HSM_HARDWARE_ID_TYPE_MEID                    = 0x0000FFFF,
    CNAS_HSM_HARDWARE_ID_TYPE_ESN                     = 0x00010000,
    CNAS_HSM_HARDWARE_ID_TYPE_NULL                    = 0x00FFFFFF,
    CNAS_HSM_HARDWARE_ID_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_HSM_HARDWARE_ID_TYPE_ENUM_UINT32;


enum CNAS_HSM_HARDWARE_ID_SRC_TYPE_ENUM
{
    CNAS_HSM_HARDWARE_ID_SRC_TYPE_NVIM,
    CNAS_HSM_HARDWARE_ID_SRC_TYPE_RAND,
    CNAS_HSM_HARDWARE_ID_SRC_TYPE_UIM,
    CNAS_HSM_HARDWARE_ID_SRC_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_HSM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32;


enum CNAS_HSM_RCV_OHM_SCENE_ENUM
{
    CNAS_HSM_RCV_OHM_SCENE_FOLLOW_OHM,          /* AT receive OverheadMessages.Updated indication follow OverheadMessages.Updated */
    CNAS_HSM_RCV_OHM_SCENE_FOLLOW_SYS_ACQ,      /* AT receive OverheadMessages.Updated indication follow InitializationState.NetworkAcquire indication */
    CNAS_HSM_RCV_OHM_SCENE_FOLLOW_CONN_CLOSE,   /* AT receive OverheadMessages.Updated indication follow ConnectedState.ConnectionClosed indication */
    CNAS_HSM_RCV_OHM_SCENE_FOLLOW_IDLE_HO,      /* AT receive OverheadMessages.Updated indication follow RouteUpdate.IdleHO indication */

    CNAS_HSM_RCV_OHM_SCENE_BUTT
};
typedef VOS_UINT8 CNAS_HSM_RCV_OHM_SCENE_ENUM_UINT8;



enum CNAS_HSM_ATI_TYPE_ENUM
{
    CNAS_HSM_ATI_TYPE_BATI                    = 0,                          /* Broadcast ATI */
    CNAS_HSM_ATI_TYPE_MATI                    = 1,                          /* Multicast ATI */
    CNAS_HSM_ATI_TYPE_UATI                    = 2,                          /* Unicast ATI */
    CNAS_HSM_ATI_TYPE_RATI                    = 3,                          /* Random ATI */
    CNAS_HSM_ATI_TYPE_INACTIVE                = 4,                          /* ATI not active */

    CNAS_HSM_ATI_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_HSM_ATI_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : CNAS_HSM_HRPD_COVERTED_CAS_STATUS_ENUM
 *
 * Description :
 *******************************************************************************/
enum CNAS_HSM_HRPD_CAS_STATUS_ENUM
{
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT                      = 0x0000,
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_IDLE                      = 0x0001,
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_CONN                      = 0x0002,

    CNAS_HSM_HRPD_CAS_STATUS_ENUM_BUTT
};
typedef VOS_UINT16 CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum  CNAS_HSM_CONN_MNMT_TRIGGER_ENUM
{
    CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN         = 0x00,
    CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_CLOSE_CONN,
    CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN,
    CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_CLOSE_CONN,
    CNAS_HSM_CONN_MNMT_TRIGGER_BY_POWER_SAVE,
    CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND,

    CNAS_HSM_CONN_MNMT_TRIGGER_BUTT
};
typedef VOS_UINT8 CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8;

/** ****************************************************************************
 * Name        : CNAS_HSM_CONN_STATUS_ENUM
 *
 * Description :
 *******************************************************************************/
enum CNAS_HSM_CONN_STATUS_ENUM
{
    CNAS_HSM_HRPD_CONN_STATUS_CLOSE,
    CNAS_HSM_HRPD_CONN_STATUS_OPEN,

    CNAS_HSM_CONN_STATUS_BUTT
};
typedef VOS_UINT8 CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8;

/** ****************************************************************************
 * Name        : CNAS_HSM_UATI_REQ_TRIGGER_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum  CNAS_HSM_UATI_REQ_TRIGGER_ENUM
{
    CNAS_HSM_UATI_REQ_TRIGGER_BY_AT                   = 0x00,     /* AT send uati req, AN send uati assign, AT send uati complete */
    CNAS_HSM_UATI_REQ_TRIGGER_BY_AN,                              /* AN directly send uati assign, AT send uati complete */

    CNAS_HSM_UATI_REQ_TRIGGER_BUTT
};
typedef VOS_UINT8 CNAS_HSM_UATI_REQ_TRIGGER_ENUM_UINT8;


/*****************************************************************************
 Name    : CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM
 Description  : Enum definition for wait card cnf flag
 History     :
  1.Date     : 2015-05-30
    Author   : y00307564
    Modify   : create
  2.Date     : 2015-09-30
    Author   : y00307564
    Modify   : DTS2015082403731 增加读取增加读取ESNMEIDME和PPP AN鉴权用户名卡文件
*****************************************************************************/
enum CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM
{
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_NULL                       = 0x00,
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ICCID                      = 0x01, /* 卡文件ID: 2fe2 */
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_UIMID                      = 0x02, /* 卡文件ID: 6f31 */
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ESNMEIDME                  = 0x04, /* 卡文件ID: 6f38 */
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_HRPD_ACCESS_AUTH_USERNAME  = 0x08, /* 卡文件ID: 6f57 */
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_BUTT
};
typedef VOS_UINT32 CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32;


enum CNAS_HSM_SESSION_RELEASE_TYPE_ENUM
{
    CNAS_HSM_SESSION_RELEASE_TYPE_0     = 0x00,
    CNAS_HSM_SESSION_RELEASE_TYPE_A     = 0x01,
    CNAS_HSM_SESSION_RELEASE_TYPE_BUTT  = 0x02
};
typedef VOS_UINT8 CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8;


enum CNAS_HSM_SESSION_STATUS_ENUM
{
    CNAS_HSM_SESSION_STATUS_CLOSE              = 0x00,
    CNAS_HSM_SESSION_STATUS_OPEN               = 0x01,
    CNAS_HSM_SESSION_STATUS_BUTT               = 0x02
};
typedef VOS_UINT8 CNAS_HSM_SESSION_STATUS_ENUM_UINT8;



enum CNAS_HRPD_SESSION_TYPE_ENUM
{
    CNAS_HSM_SESSION_TYPE_HRPD          = 0x00,
    CNAS_HSM_SESSION_TYPE_EHRPD         = 0x01,
    CNAS_HSM_SESSION_TYPE_BUTT          = 0x02
};
typedef VOS_UINT8 CNAS_HSM_SESSION_TYPE_ENUM_UINT8;


enum CNAS_HSM_SLOT_VOTE_TYPE_ENUM
{
    CNAS_HSM_SLOT_VOTE_TYPE_KEEP_ALIVE_PROCEDURE            = 0x01,
    CNAS_HSM_SLOT_VOTE_TYPE_UATI_REQ_PROCEDURE              = 0x02,
    CNAS_HSM_SLOT_VOTE_TYPE_BUTT                            = 0xFF
};

typedef VOS_UINT8 CNAS_HSM_SLOT_VOTE_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/
#ifdef DMT
    extern VOS_UINT32                       g_ulCurSessionSeed;
#endif

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
    VOS_UINT32                          ulEventType;
    CNAS_HSM_MSG_PRI_ENUM_UINT8         enMsgPri;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                           aucMsgBuffer[CNAS_HSM_MAX_MSG_BUFFER_LEN];
}CNAS_HSM_MSG_STRU;


typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* internal message number */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[CNAS_HSM_MAX_INT_MSG_QUEUE_NUM]; /* HSM module internal message,store the message pointer here */
}CNAS_HSM_INT_MSG_QUEUE_STRU;

/*****************************************************************************
 Structure Name    : CNAS_HSM_CACHE_MSG_INFO_STRU
 Description       : The structure of HSM buffer message
 1.Date            : 26/1/2015
   Author          : w00176964
   Modification    : Create
 2.Date            : 8/9/2015
   Author          : w00176964
   Modification    : CNAS内存裁剪调整
*****************************************************************************/

typedef struct
{
    CNAS_HSM_MSG_PRI_ENUM_UINT8         enMsgPri;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pucMsgBuffer;/* 存放消息头指针 */
}CNAS_HSM_CACHE_MSG_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_HSM_CACHE_MSG_INFO_STRU        astCacheMsg[CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM];
}CNAS_HSM_CACHE_MSG_QUEUE_STRU;



typedef struct
{
    CNAS_HSM_ATI_TYPE_ENUM_UINT8        enATIType;
    VOS_UINT8                           aucRsv[3];
    /* access terminal identifier.The filed is valid only if the ATI type is not equal to INACTIVE */
    VOS_UINT8                           aucATIValue[CNAS_HSM_ATI_VALUE_LENGTH];
    VOS_UINT32                          ulAddrTimerLen;
}CNAS_HSM_ATI_RECORD_STRU;



typedef struct
{
    VOS_UINT32                          ulATIRecordNum;
    CNAS_HSM_ATI_RECORD_STRU            astATIEntry[CNAS_HSM_MAX_UATI_REC_NUM];
}CNAS_HSM_ATI_LIST_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucUATIReqFailedCnt;                 /* UATI request failed count */
    VOS_UINT8                           ucUATIAssignTimerExpiredCnt;        /* UATI ASSIGN TIMER expired count */
    VOS_UINT8                           ucAbortFlg;                         /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    VOS_UINT8                           aucRsv[1];
}CNAS_HSM_FSM_UATI_REQUEST_CTX_STRU;


typedef struct
{
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;    /* Session deactive reason */
    VOS_UINT8                                               ucAbortFlg;              /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM_UINT8    enReviseTimerScene;      /* 需要启动修正定时器的场景 */
    VOS_UINT8                                               aucRsv[1];
}CNAS_HSM_FSM_SESSION_DEACTIVE_CTX_STRU;


typedef struct
{
    VOS_UINT8                                               ucAbortFlg;                         /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason;              /* session active 的请求原因值 */
    VOS_UINT8                                               ucIsGetPaNtf;
    VOS_UINT8                                               aucRsv[1];
}CNAS_HSM_FSM_SESSION_ACTIVE_CTX_STRU;


typedef struct
{
    VOS_UINT8                                               ucAbortFlg;        /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene;    /* 链接管理请求场景 */
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_FSM_CONN_MNMT_CTX_STRU;



typedef struct
{
    VOS_UINT32                          ulSessionSeed;
    CNAS_HSM_ATI_RECORD_STRU            stTransmitATI;
    CNAS_HSM_ATI_LIST_INFO_STRU         stReceiveATIList;
}CNAS_HSM_PUBLIC_DATA_CTX_STRU;



typedef struct
{
    VOS_UINT8                           aucCurUATI[CNAS_HSM_UATI_OCTET_LENGTH];
    VOS_UINT8                           aucOldUATI[CNAS_HSM_UATI_OCTET_LENGTH];
    VOS_UINT8                           ucSubnetInc;                        /* 1 bits */
    VOS_UINT8                           ucUATIColorCode;
    VOS_UINT8                           ucUATISubnetMask;                   /* 0 or 8 bits */
    VOS_UINT8                           ucOldUATILen;                       /* 4 bits */
}CNAS_HSM_UATI_INFO_STRU;


typedef struct
{
    VOS_INT32                           lLongitude;
    VOS_INT32                           lLatitude;
}CNAS_HSM_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucSessionActTriedCntConnFail;   /* Session act tried count of connection fail */
    VOS_UINT8                           ucSessionActTriedCntOtherFail;  /* Session act tried count of other fail */
    VOS_UINT8                           ucSessionActMaxCntConnFail;     /* Session act max count of connection fail */
    VOS_UINT8                           ucSessionActMaxCntOtherFail;    /* Session act max count of other fail */
    VOS_UINT32                          ulSessionActTimerLen;           /* Session act timer length, unit is millisecond */
    VOS_UINT16                          usScpActFailProtType;           /* Protocol type in ID_CAS_CNAS_HRPD_SCP_ACTIVE_CNF and ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND */
    VOS_UINT16                          usScpActFailProtSubtype;        /* Protocol subtype in ID_CAS_CNAS_HRPD_SCP_ACTIVE_CNF and ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND */
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8    enReqSessionTypeForRetry;       /* Request session type(HRPD/EHRPD) for retry */
    VOS_UINT8                           ucIsExplicitlyConnDenyFlg;
    VOS_UINT8                           aucRsv[2];
}CNAS_HSM_SESSION_ACTIVE_CTRL_CTX_STRU;



typedef struct
{
    VOS_UINT8                                               ucColorCode;
    VOS_UINT8                                               ucSubNetMask;
    VOS_UINT8                                               ucOhmParameterUpToDate;
    VOS_UINT8                                               ucSecondaryColorCodeCount;
    VOS_UINT8                                               aucSectorId[CNAS_HSM_SUBNET_ID_MAX_LENGTH];
    VOS_UINT8                                               aucSecondaryColorCode[CNAS_HSM_SECOND_COLORCODE_MAX_LENGTH];
    VOS_UINT8                                               aucRsv[1];
    VOS_INT32                                               lLongitude;
    VOS_INT32                                               lLatitude;
}CNAS_HSM_HRPD_SYS_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucIsStored;  /* VOS_TRUE:做了store/VOS_FALSE:未做store */
    VOS_UINT8                           ucIsChanged; /* VOS_TRUE:ESN_MEID改变了/VOS_FALSE: ESN_MEID未改变 */
    VOS_UINT8                           aucRsv[2];
}CNAS_HSM_STORE_ESN_MEID_RSLT_STRU;


typedef struct
{
    VOS_UINT8                                               ucIsPreCardPresent;  /* 先前一次卡是否存在 */
    VOS_UINT8                                               ucIsCurCardPresent;  /* 目前卡是否存在 */
    VOS_UINT8                                               aucReserve[2];
}CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucWaitUatiAssignTimerLenInAmpSetup; /* Setup态时，成功发送UATI req后等网侧UATI assign的保护时长，默认5s */
    VOS_UINT8                                               ucWaitUatiAssignTimerLenInAmpOpen;  /* Open态时，成功发送UATI req后等网侧UATI assign的保护时长，默认120s */
    VOS_UINT8                                               aucReserve[2];
} CNAS_HSM_WAIT_UATI_ASSIGN_TIMER_LEN_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               aucSubnet[CNAS_HSM_SUBNET_ID_MAX_LENGTH];
    VOS_UINT8                                               ucCount;
    VOS_UINT8                                               aucReserve[3];
} CNAS_HSM_SESSION_CLOSE_INFO_STRU;



typedef struct
{
    CNAS_HSM_PUBLIC_DATA_CTX_STRU                           stPublicData;                   /* HSM public data for other module */
    CNAS_HSM_UATI_INFO_STRU                                 stUATIInfo;                     /* UATI info */
    CNAS_HSM_LOC_INFO_STRU                                  stLocInfo;                      /* Location info */
    CNAS_HSM_SESSION_ACTIVE_CTRL_CTX_STRU                   stSessionActiveCtrlCtx;         /* Session active control ctx */
    CNAS_HSM_HRPD_SYS_INFO_STRU                             stHrpdSysInfo;

    VOS_UINT8                                               ucUATIAssignMsgSeq;             /* UATI Assignment message sequence number */
    VOS_UINT8                                               ucUATIReqTransId;               /* UATI Request transection ID,each new UATI request should increase this value modulo 256 */

    VOS_UINT8                                               ucIsFirstSysAcq;                /* If TRUE, then HSM receives System acquire Ind for the first time after Switch On*/
    CNAS_HSM_RCV_OHM_SCENE_ENUM_UINT8                       enRcvOhmScene;                  /* The scene of receive OHM */

    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;                /* session status: OPEN or CLOSE */
    VOS_UINT8                                               ucIsSessionNegOngoing;          /* VOS_TRUE: session is ongoing. VOS_FALSE:session is not ongoing */
    VOS_UINT8                                               ucIsScpActive;                  /* VOS_TRUE: scp is in active state; VOS_FALSE: scp is in deactive State */
    VOS_UINT8                                               ucStartUatiReqAfterSectorIdChgFlg;   /* 为了通过RF测试和CCF2.2.2.8用例，增加NV控制
                                                                                                                 NV打开(默认):参照标杆只要sector ID发生变化就启动UATI申请流程
                                                                                                                 NV关闭:      严格按照协议C.S0024 7.3.7.1.6.1处理，即只有在HO或者
                                                                                                                              Conn Close后，sector ID发生变化才启动UATI申请流程 */

    CNAS_HSM_WAIT_UATI_ASSIGN_TIMER_LEN_INFO_STRU           stWaitUatiAssignTimerLenInfo;

    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enLatestSessionDeactReason;     /* Latest session deactive reason */

    VOS_UINT8                                               aucPrevUatiForSessionRestore[CNAS_HSM_UATI_OCTET_LENGTH];   /* Previous UATI128 for session restore  */

    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enNegoSessionType;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enReqSessionType;               /* the session type used in activation req  msg */
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType;

    CNAS_HSM_STORE_ESN_MEID_RSLT_STRU                       stStoreEsnMeidRslt;             /* 获取的store ESN_MEID_ME的结果 */
    CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU                   stCardStatusChgInfo;            /* hsm卡状态变化信息 */

    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                         stLastHrpdUERevInfo;

    VOS_UINT8                                               ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen;/* 在open态时当UATI req发送成功后等网侧UATI assign超时
                                                                                                                                   后的重试次数,默认不重试，最大重试4次 */

    VOS_UINT8                                               ucUatiCompleteRetryTimes;       /* 发送Uati Complete后，收到Snp Data Cnf指示失败时的重试次数，最大重试3次*/

    VOS_UINT8                                               aucRsv[2];

    CNAS_HSM_SESSION_CLOSE_INFO_STRU                        stSessionCloseInfo;
}CNAS_HSM_SESSION_CTRL_STRU;



typedef struct
{
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enHrpdConvertedCasStatus;
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enHrpdOriginalCasStatus;
    VOS_UINT8                                               ucHsmCallId;
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_HRPD_CONN_CTRL_STRU;


typedef struct
{
    VOS_UINT32                          ulWaitCardReadFlag; /* 每个文件占一个标记，该bit位为"1"表示该文件未读取 */
}CNAS_HSM_FSM_SWITCH_ON_CTX_STRU;



typedef struct
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubState;

    CNAS_HSM_FSM_UATI_REQUEST_CTX_STRU                      stUatiReqFsmCtx;

    CNAS_HSM_FSM_SESSION_DEACTIVE_CTX_STRU                  stSessionDeactiveFsmCtx;
    CNAS_HSM_FSM_SWITCH_ON_CTX_STRU                         stCardReadInfo;

    CNAS_HSM_FSM_SESSION_ACTIVE_CTX_STRU                    stSessionActiceFsmCtx;
    CNAS_HSM_FSM_CONN_MNMT_CTX_STRU                         stConnMnmtFsmCtx;

}CNAS_HSM_FSM_CTX_STRU;


typedef struct
{
    VOS_UINT8                           aucReserve[4];
}CNAS_HSM_MAINTAIN_CTX_STRU;


typedef struct
{
    CNAS_HSM_HARDWARE_ID_TYPE_ENUM_UINT32                   enHwidType;
    CNAS_HSM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32               enHwidSrcType;
    VOS_UINT32                                              ulEsn;                              /* 32-bit */
    VOS_UINT8                                               aucMeId[CNAS_HSM_MEID_OCTET_NUM];    /* 56-bit */
    VOS_UINT8                                               aucRsv[1];
}CNAS_HSM_HARDWARE_ID_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU
 结构说明  : AMP协商参数
 1.日    期   : 2015年05月30日
   作    者   : y00307564
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMaxNoMonitorDistance;
    VOS_UINT16                          usHardwareSeparableFromSession;
    VOS_UINT16                          usSupportGAUPMaxNoMonitorDistance;
    VOS_UINT16                          usReducedSubnetMaskOffset;
    VOS_UINT16                          usSupportSecondaryColorCodes;
    VOS_UINT8                           aucRsv[2];
}CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU;

/*****************************************************************************
 结构名    : CNAS_HSM_LAST_HRPD_SESSION_INFO_STRU
 结构说明  : 与hrpd session相关的NV上下文
 1.日    期   : 2015年05月30日
   作    者   : y00307564
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enSessionStatus;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8    enSessionType;
    VOS_UINT8                           aucRsv[2];
    CNAS_HSM_HARDWARE_ID_INFO_STRU      stHwid;             /* 最后一次session中保存的hardware id */
}CNAS_HSM_LAST_HRPD_SESSION_INFO_STRU;

/****************************************************************************
Structure name  :   CNAS_HSM_CUSTOM_CONFIG_STRU
Description     :   Structure definition containing the Containing the NV Values
Modify History:
    1)  Date    :   2015-06-08
        Author  :   y00307564
        Modify content :    Create
    2)  Date    :   2015-10-15
        Author  :   y00307564
        Modify content :    DTS2015082403731修改，增加hrpd ppp an鉴权用户名
    3)  Date    :   2015-12-21
        Author  :   m00312079
        Modify content :    DTS2015120208895修改，增加UE的版本信息
****************************************************************************/
typedef struct
{
    VOS_UINT8                                               aucHrpdNvimIccId[CNAS_CCB_ICCID_OCTET_LEN]; /* 最后一次session中保存的ICCID*/
    VOS_UINT8                                               aucRsv[2];
    CNAS_HSM_LAST_HRPD_SESSION_INFO_STRU                    stHrpdNvimSessInfo;                         /* hrpd session info from nv */
    CNAS_HSM_HARDWARE_ID_INFO_STRU                          stNvimHwid;                                 /* NV中保存的hardwareID */
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                     stHrpdNvimAccessAuthInfo;                   /* NV中保存的hrpd an鉴权用户信息 */
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                         stHrpdUERevInfo;
}CNAS_HSM_CUSTOM_CONFIG_STRU;


typedef struct
{
    CNAS_HSM_CUSTOM_CONFIG_STRU         stCustomCfgInfo;
}CNAS_HSM_MS_CFG_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucKeepAliveReqSndCount;  /* Indicates the number of times HSM has sent keep alive Req to AN */
    VOS_UINT8                           aucReserved[3];          /* For padding */
    VOS_UINT32                          ulSysTickFwdTrafChan;    /* Stores the System tick at the moment when AT receives Fwd Traf Chan Data */
    VOS_UINT32                          ulOldSysTickFwdTrafChan; /* Stores the ulSysTickFwdTrafChan, at the time of starting the keep alive timer */
    VOS_UINT32                          ulKeepAliveTimerLen;     /* stores the keep alive timer length. Unit is millisec */
    VOS_UINT32                          ulTotalTimerRunCount;    /* Stores the total number of times the keep alive timer must be run to get the
                                                                    required time interval of ulKeepAliveTimerLen */
    VOS_UINT32                          ulTimerExpiredCount;     /* Stores the number of times the keep alive timer has expired.
                                                                    Used to judge if the required time interaval of ulKeepAliveTimerLen is complete */
}CNAS_HSM_KEEP_ALIVE_TIMER_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucIsKeepAliveInfoValid;     /* IF TRUE, then the Keep Alive parameters are valid */
    VOS_UINT8                           aucRsv;
    VOS_UINT16                          usTsmpClose;                /* Stores the Tsmpclose value in minutes */
    VOS_UINT32                          ulTsmpCloseRemainTime;      /* Stores the TsmpClose_Remain_time in Seconds */
    VOS_UINT32                          aulPowerOffSysTime[CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME]; /* Stores the CDMA Sys Time.
                                                                                                    at last power off. Unit is ms */
}CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU;



typedef struct
{
    VOS_UINT32                                              ulReferenceSysTick;     /* Stores the system tick at the time of receiving Sys time from HSD */
    VOS_UINT8                                               ucKeepAliveReqTransId;  /* should increase while each new keep alive request sent */
    VOS_UINT8                                               aucRsv[3];
    VOS_UINT32                                              aulReceivedSysTime[CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME]; /* Stores the CDMA Sys time received in Sys Acq Ind message or Sys Time Ind message from CAS */
    CNAS_HSM_KEEP_ALIVE_TIMER_INFO_STRU                     stKeepAliveTimerInfo;
    CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU                   stSessionKeepAliveInfo;
}CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU;


/*****************************************************************************
 结构名    : CNAS_HSM_MULTI_MODE_CTRL_INFO_STRU
 结构说明  : 与多模控制相关的CTX变量
 1.日    期   : 2015年06月03日
   作    者   : t00323010
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLteRegSuccFlg;                /* LTE reg succ while HRPD in slave mode */
    VOS_UINT8                           aucRsv[3];
}CNAS_HSM_MULTI_MODE_CTRL_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSM_SNP_DATA_REQ_OPID_INFO_STRU
 结构说明  : OpId for HSM Send Snp Data Requset message
 1.日    期   : 2015年06月11日
   作    者   : t00323010
   修改内容   : Iteration 12: create
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSessionCloseOpId;         /* Save OpId for Session Close msg,AT init or AN init, only one session close send at same time */
    VOS_UINT16                          usUatiReqOpId;              /* save OpId for Uati Request msg */
    VOS_UINT16                          usUatiCmplOpId;             /* Save OpId for UATI Complete msg */
    VOS_UINT16                          usKeepAliveReqOpId;         /* Save OpId for Keep Alive Request msg */
    VOS_UINT16                          usKeepALiveRspOpId;         /* Save OpId for Keep Alive Response msg */
    VOS_UINT16                          usHardWareIdRspOpId;        /* Save OpId for HardWareId Response msg */
}CNAS_HSM_SNP_DATA_REQ_OPID_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSM_SNP_DATA_REQ_OPID_CTRL_STRU
 结构说明  : Snp Data Req OpId Ctrl Stru for HSM module
 1.日    期   : 2015年06月11日
   作    者   : t00323010
   修改内容   : Iteration 12: create
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usHsmSnpDataReqOpId;            /* Hsm module current OpId, +1 each timer after used,[0~65535] */
    VOS_UINT8                                               aucRsv[2];
    CNAS_HSM_SNP_DATA_REQ_OPID_INFO_STRU                    stSaveSnpDataReqOpId;
}CNAS_HSM_SNP_DATA_REQ_OPID_CTRL_STRU;


/*****************************************************************************
 结构名    : CNAS_HSM_LOW_POWER_CTRL_STRU
 结构说明  : Low power Ctrl Stru for HSM module
 1.日    期   : 2015年12月07日
   作    者   : m00312079
   修改内容   : Create
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucSlotVoteBox;
    VOS_UINT8                                               aucRsv[3];
}CNAS_HSM_LOW_POWER_CTRL_STRU;


typedef struct
{
    CNAS_HSM_FSM_CTX_STRU                                   stCurFsmCtx;                    /* the current state machine contex info */

    CNAS_HSM_CACHE_MSG_QUEUE_STRU                           stCacheMsgQueue;                /* cacnhe message queue */

    CNAS_HSM_INT_MSG_QUEUE_STRU                             stIntMsgQueue;                  /* internal message queue */

    CNAS_HSM_MS_CFG_INFO_STRU                               stMsCfgInfo;                    /* the mobile sation config info */

    CNAS_HSM_MAINTAIN_CTX_STRU                              stMntnInfo;                     /* maintence info */

    CNAS_HSM_HRPD_CONN_CTRL_STRU                            stHrpdConnCtrlInfo;             /* hrpd connection ctrl info */

    CNAS_HSM_SESSION_CTRL_STRU                              stSessionCtrlInfo;
    CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU                       stHrpdAmpNegAttibInfo;          /* HRPD AMP协商参数 */

    CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU                       stKeepAliveCtrlCtx;             /* Keep Alive ctrl ctx Info */

    CNAS_HSM_MULTI_MODE_CTRL_INFO_STRU                      stMultiModeCtrlInfo;
    CNAS_HSM_SNP_DATA_REQ_OPID_CTRL_STRU                    stSnpDataReqCtrlInfo;

    CNAS_HSM_LOW_POWER_CTRL_STRU                            stLowPowerCtrlInfo;
}CNAS_HSM_CTX_STRU;


typedef struct
{
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;   /* Session deactive reason */
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM_UINT8       enCloseReasonSendToAn;  /* Reason in SessionClose send to AN */
    VOS_UINT8                                               aucRsv[2];
}CNAS_HSM_DEACT_REASON_MAP_REASON_SEND_AN_STRU;

typedef VOS_VOID (*pCnasHsmSessionDeactReasonHdlrFunc)(VOS_VOID);


typedef struct
{
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;           /* Session deactive reason */
    VOS_UINT8                                               aucRsv[3];
    pCnasHsmSessionDeactReasonHdlrFunc                      pfuncSessionDeactReasonHdlr;    /* Session deactive reason handle function */
}CNAS_HSM_SESSION_DEACT_REASON_PROC_TBL_STRU;


typedef struct
{
    CAS_CNAS_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                 enCasRslt;
    VOS_UINT8                                               aucRsv[3];
    HSM_APS_CAUSE_ENUM_UINT32                               enApsRslt;

} CNAS_HSM_APS_ERR_CODE_MAP_STRU;


typedef struct
{
    CAS_CNAS_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                 enCasRslt;
    VOS_UINT8                                               aucRsv[3];
    EHSM_HSM_RSLT_ENUM_UINT32                               enEhsmRslt;
} CNAS_HSM_EHSM_ERR_CODE_MAP_STRU;
/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*******************************************************************/
/* the init function placed here */

VOS_VOID CNAS_HSM_InitCtx(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8   enInitType
);

/* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
VOS_VOID CNAS_HSM_InitCacheMsgQueue(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
);
/* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */

VOS_VOID CNAS_HSM_InitIntMsgQueue(
    CNAS_HSM_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
);

VOS_VOID CNAS_HSM_InitPublicData(
    CNAS_HSM_PUBLIC_DATA_CTX_STRU      *pstPublicData
);

VOS_VOID CNAS_HSM_InitATIRecord(
    CNAS_HSM_ATI_RECORD_STRU           *pstATIRecord
);

CNAS_HSM_ATI_RECORD_STRU* CNAS_HSM_GetTransmitATIAddr(VOS_VOID);

VOS_VOID CNAS_HSM_InitATIList(
    CNAS_HSM_ATI_LIST_INFO_STRU        *pstATIListInfo
);

VOS_VOID CNAS_HSM_InitMsCfgInfo(
    CNAS_HSM_MS_CFG_INFO_STRU          *pstMsCfgInfo
);

VOS_VOID CNAS_HSM_InitHrpdConnCtrlInfo(
    CNAS_HSM_HRPD_CONN_CTRL_STRU       *pstCallCtrlInfo
);

VOS_VOID CNAS_HSM_InitUATIInfo(
    CNAS_HSM_UATI_INFO_STRU            *pstUATIInfo
);

VOS_VOID CNAS_HSM_InitSessionActiveCtx(
    CNAS_HSM_SESSION_ACTIVE_CTRL_CTX_STRU                  *pstSessionActiveCtrlCtx
);

VOS_VOID CNAS_HSM_InitSessionCtrlInfo(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSM_SESSION_CTRL_STRU         *pstSessionCtrlInfo
);

VOS_VOID CNAS_HSM_InitMntnInfo(
    CNAS_HSM_MAINTAIN_CTX_STRU         *pstMntnInfo
);

VOS_VOID CNAS_HSM_InitCurFsmCtx(
    CNAS_HSM_FSM_CTX_STRU              *pstCurFsmCtx
);

VOS_VOID CNAS_HSM_InitUATIReqFsmCtx(
    CNAS_HSM_FSM_UATI_REQUEST_CTX_STRU *pstUATIReqFsmCtx
);

VOS_VOID CNAS_HSM_InitSessionDeactiveFsmCtx(
    CNAS_HSM_FSM_SESSION_DEACTIVE_CTX_STRU                 *pstSessionDeactiveFsmCtx
);

VOS_VOID CNAS_HSM_InitReadCardInfo(
    CNAS_HSM_FSM_SWITCH_ON_CTX_STRU    *pstCardReadInfo
);

VOS_VOID CNAS_HSM_InitKeepAliveCtrlCtx(
    CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU       *pstKeepAliveCtrlCtx
);

VOS_VOID CNAS_HSM_InitMultiModeCtrlInfo(
    CNAS_HSM_MULTI_MODE_CTRL_INFO_STRU         *pstMultiModeCtrlInfo
);

VOS_VOID CNAS_HSM_InitLastHrpdSessionInfo(
    CNAS_HSM_LAST_HRPD_SESSION_INFO_STRU                   *pstHrpdNvimSessInfo
);

VOS_VOID CNAS_HSM_InitUERevInfo(
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU*                        pstHrpdUERevInfo
);

VOS_VOID CNAS_HSM_InitHrpdAmpNegAttrib(
    CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU  *pstHrpdAmpNegAttibInfo
);

VOS_VOID CNAS_HSM_InitSnpDataReqCtrlInfo(
    CNAS_HSM_SNP_DATA_REQ_OPID_CTRL_STRU                   *pstSnpDataReqCtrlInfo
);

VOS_VOID CNAS_HSM_InitLastHrpdNvimAccessAuthInfo(
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstLastHrpdNvimAccessAuthInfo
);

VOS_VOID CNAS_HSM_InitHsmCardStatusInfo(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8                       enInitType,
    CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU                  *pstCardStatusChangeInfo
);

VOS_VOID CNAS_HSM_InitStoreEsnMeidRsltInfo(
    CNAS_HSM_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSM_STORE_ESN_MEID_RSLT_STRU  *pstStoreEsnMeidRslt
);
/*******************************************************************/


/*******************************************************************/
/* the access the structure address function placed here */

CNAS_HSM_CTX_STRU* CNAS_HSM_GetHsmCtxAddr(VOS_VOID);

CNAS_HSM_CACHE_MSG_QUEUE_STRU* CNAS_HSM_GetCacheMsgAddr(VOS_VOID);

CNAS_HSM_INT_MSG_QUEUE_STRU* CNAS_HSM_GetIntMsgQueueAddr(VOS_VOID);

CNAS_HSM_HRPD_CONN_CTRL_STRU* CNAS_HSM_GetHrpdConnCtrlInfoAddr(VOS_VOID);

CNAS_HSM_MS_CFG_INFO_STRU* CNAS_HSM_GetMsCfgInfoAddr(VOS_VOID);

CNAS_HSM_ATI_LIST_INFO_STRU* CNAS_HSM_GetReceivedATIListAddr(VOS_VOID);

CNAS_HSM_PUBLIC_DATA_CTX_STRU* CNAS_HSM_GetPublicDataAddr(VOS_VOID);

CNAS_HSM_SESSION_CTRL_STRU*    CNAS_HSM_GetSessionCtrlInfoAddr(VOS_VOID);

CNAS_HSM_FSM_CTX_STRU* CNAS_HSM_GetCurFsmCtxAddr(VOS_VOID);

CNAS_HSM_FSM_UATI_REQUEST_CTX_STRU* CNAS_HSM_GetUATIRequestFsmCtxAddr(VOS_VOID);

CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU* CNAS_HSM_GetKeepAliveCtrlCtxAddr(VOS_VOID);

CNAS_HSM_LOC_INFO_STRU* CNAS_HSM_GetLocInfoAddr(VOS_VOID);
CNAS_HSM_UATI_INFO_STRU* CNAS_HSM_GetUatiInfoAddr(VOS_VOID);

/* the set/get interface for each global value place here */
VOS_VOID  CNAS_HSM_SetCurrMainState(
    CNAS_HSM_L1_STA_ENUM_UINT32         enMainState
);

VOS_VOID  CNAS_HSM_SetCurrSubState(
    CNAS_HSM_SS_ID_ENUM_UINT32          enSubState
);

CNAS_HSM_L1_STA_ENUM_UINT32 CNAS_HSM_GetCurrMainState(VOS_VOID);

CNAS_HSM_SS_ID_ENUM_UINT32 CNAS_HSM_GetCurrSubState(VOS_VOID);

/* cache message interface */
VOS_UINT8 CNAS_HSM_GetCacheMsgNum(VOS_VOID);

VOS_UINT32  CNAS_HSM_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID CNAS_HSM_ClearCacheMsgByIndex(
    VOS_UINT8                           ucIndex
);
VOS_VOID CNAS_HSM_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_UINT8 CNAS_HSM_GetHighestPriCachedMsg(
     CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstMsgQueue
);

VOS_UINT8 CNAS_HSM_GetCacheIndexByEventType(
     VOS_UINT32                          ulEventType
);

VOS_UINT32 CNAS_HSM_GetNextCachedMsg(
    CNAS_HSM_MSG_STRU                  *pstCachedMsg
);

/* internal message queu interface */
VOS_VOID CNAS_HSM_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
);

VOS_UINT8 *CNAS_HSM_GetNextIntMsg(VOS_VOID);

VOS_UINT32 CNAS_HSM_GetIntMsgNum(VOS_VOID);

/* Deleted by w00176964 for CNAS内存裁剪, 2015-9-18, begin */

/* Deleted by w00176964 for CNAS内存裁剪, 2015-9-18, end */

/* public data interface */

VOS_VOID  CNAS_HSM_SetSessionSeed(
    VOS_UINT32                          ulSessionSeed
);
VOS_UINT32  CNAS_HSM_GetSessionSeed(VOS_VOID);

VOS_VOID  CNAS_HSM_SetStartUatiReqAfterSectorIdChgFlg(
    VOS_UINT8                           ucStartUatiReqAfterSectorIdChgFlg
);
VOS_UINT8  CNAS_HSM_GetStartUatiReqAfterSectorIdChgFlg(VOS_VOID);

/* call ctrl info interface */
CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16 CNAS_HSM_GetHrpdConvertedCasStatus(VOS_VOID);

VOS_VOID CNAS_HSM_SaveHrpdConvertedCasStatus(
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enHrpdConvertedCasStatus
);

CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16 CNAS_HSM_GetHrpdOriginalCasStatus(VOS_VOID);

VOS_VOID CNAS_HSM_SaveHrpdOriginalCasStatus(
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                   enHrpdOriginalCasStatus
);

VOS_VOID CNAS_HSM_SetSessionNegOngoingFlag(
    VOS_UINT8                           ucIsSessionNegOngoing
);


VOS_UINT8 CNAS_HSM_GetSessionNegOngoingFlag(VOS_VOID);

VOS_VOID CNAS_HSM_SetScpActiveFlag(
    VOS_UINT8                           ucIsScpActive
);

VOS_UINT8 CNAS_HSM_GetScpActiveFlag(VOS_VOID);

CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8 CNAS_HSM_GetConnStatus(VOS_VOID);

VOS_VOID CNAS_HSM_SetConnStatus(
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus
);


/* UATI rqeust context interface */

VOS_UINT8 CNAS_HSM_GetUATIReqFailedCnt(VOS_VOID);
VOS_VOID CNAS_HSM_IncreaseUATIReqFailedCnt(VOS_VOID);
VOS_VOID CNAS_HSM_ResetUATIReqFailedCnt(VOS_VOID);

VOS_UINT8 CNAS_HSM_GetUATIAssignTimerExpiredCnt(VOS_VOID);
VOS_VOID CNAS_HSM_IncreaseUATIAssignTimerExpiredCnt(VOS_VOID);

VOS_VOID CNAS_HSM_SetCurrUATIAssignMsgSeqNum(
    VOS_UINT8                           ucSeqNum
);
VOS_UINT8 CNAS_HSM_GetCurrUATIAssignMsgSeqNum(VOS_VOID);

VOS_VOID CNAS_HSM_IncreaseUATITransId(VOS_VOID);
VOS_UINT8 CNAS_HSM_GetUATITransId(VOS_VOID);

CNAS_HSM_RCV_OHM_SCENE_ENUM_UINT8 CNAS_HSM_GetRcvOhmScene(VOS_VOID);

VOS_VOID CNAS_HSM_SetRcvOhmScene(
    CNAS_HSM_RCV_OHM_SCENE_ENUM_UINT8   enRcvOhmScene
);

CNAS_HSM_HARDWARE_ID_INFO_STRU* CNAS_HSM_GetHardwareIdInfo(VOS_VOID);


VOS_UINT8 CNAS_HSM_GetHsmCallId(VOS_VOID);

VOS_VOID CNAS_HSM_SaveHsmCallId(
    VOS_UINT8                           ucHsmCallId
);

VOS_UINT8 CNAS_HSM_GetRegLteSuccFlag(VOS_VOID);

VOS_VOID CNAS_HSM_SetRegLteSuccFlag(
    VOS_UINT8                           ucRegLteSucc
);


CNAS_HSM_SESSION_ACTIVE_CTRL_CTX_STRU* CNAS_HSM_GetSessionActiveCtrlCtx(VOS_VOID);

VOS_UINT8 CNAS_HSM_GetSessionActTriedCntConnFail(VOS_VOID);

VOS_UINT8 CNAS_HSM_GetSessionActTriedCntOtherFail(VOS_VOID);

VOS_VOID CNAS_HSM_IncreaseSessionActTriedCntConnFail(VOS_VOID);

VOS_VOID CNAS_HSM_IncreaseSessionActTriedCntOtherFail(VOS_VOID);

VOS_VOID CNAS_HSM_ResetSessionActTriedCntConnFail(VOS_VOID);

VOS_VOID CNAS_HSM_ResetSessionActTriedCntOtherFail(VOS_VOID);

VOS_UINT8 CNAS_HSM_GetSessionActMaxCntConnFail(VOS_VOID);

VOS_VOID CNAS_HSM_SetSessionActMaxCntConnFail(VOS_UINT8 ucMaxCnt);

VOS_UINT8 CNAS_HSM_GetSessionActMaxCntOtherFail(VOS_VOID);

VOS_VOID CNAS_HSM_SetSessionActMaxCntOtherFail(VOS_UINT8 ucMaxCnt);

VOS_UINT32 CNAS_HSM_GetSessionActTimerLen(VOS_VOID);

VOS_VOID CNAS_HSM_SetSessionActTimerLen(VOS_UINT32 ulTimerLen);

VOS_UINT8 CNAS_HSM_GetExplicitlyConnDenyFlg(VOS_VOID);

VOS_VOID CNAS_HSM_SetExplicitlyConnDenyFlg(VOS_UINT8 ucIsExplicitlyConnDenyFlg);


CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8
CNAS_HSM_GetSessionDeactReason_SessionDeact(VOS_VOID);

VOS_VOID CNAS_HSM_SetSessionDeactReason_SessionDeact(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enDeactiveReason
);

CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8 CNAS_HSM_GetLatestSessionDeactReason(VOS_VOID);

VOS_VOID CNAS_HSM_SetLatestSessionDeactReason(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enDeactiveReason
);

VOS_UINT8 CNAS_HSM_GetUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen(VOS_VOID);

VOS_VOID CNAS_HSM_SetUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen(
    VOS_UINT8                                               ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen
);

VOS_UINT8 CNAS_HSM_GetUatiCompleteRetryTimes(VOS_VOID);

VOS_VOID CNAS_HSM_ResetUatiCompleteRetryTimes(VOS_VOID);

VOS_VOID CNAS_HSM_IncreaseUatiCompleteRetryTimes(VOS_VOID);

VOS_UINT16 CNAS_HSM_GetScpActFailProcType(VOS_VOID);

VOS_VOID CNAS_HSM_SetScpActFailProcType(VOS_UINT16 usProcType);

VOS_UINT16 CNAS_HSM_GetScpActFailProcSubtype(VOS_VOID);

VOS_VOID CNAS_HSM_SetScpActFailProcSubtype(VOS_UINT16 usProcSubtype);

CNAS_HSM_FSM_SESSION_DEACTIVE_CTX_STRU* CNAS_HSM_GetSessionDeactiveFsmCtxAddr(VOS_VOID);

CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_GetReqSessionTypeForRetry(VOS_VOID);

VOS_VOID CNAS_HSM_SetReqSessionTypeForRetry(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8    enReqSessionType
);

CNAS_HSM_HRPD_SYS_INFO_STRU* CNAS_HSM_GetHrpdSysInfoAddr(VOS_VOID);

CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU* CNAS_HSM_GetSessionKeepAliveInfoAddr(VOS_VOID);

CNAS_HSM_LAST_HRPD_SESSION_INFO_STRU* CNAS_HSM_GetLastHrpdSessionInfoCtxAddr(VOS_VOID);

CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU* CNAS_HSM_GetLastHrpdAccessAuthInfoCtxAddr(VOS_VOID);

CNAS_NVIM_HRPD_UE_REV_INFO_STRU* CNAS_HSM_GetHrpdUERevInfoCtxAddr(VOS_VOID);
CNAS_NVIM_HRPD_UE_REV_INFO_STRU* CNAS_HSM_GetLastHrpdUERevInfoCtxAddr(VOS_VOID);

CNAS_HSM_SESSION_CLOSE_INFO_STRU* CNAS_HSM_GetSessionCloseInfoCtxAddr(VOS_VOID);

CNAS_HSM_HARDWARE_ID_INFO_STRU* CNAS_HSM_GetLastSessionHwidCtxAddr(VOS_VOID);

VOS_VOID CNAS_HSM_SetLastHardwareId(
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstHwid
);

VOS_VOID CNAS_HSM_SetLastHrpdSysInfo(
    CNAS_HSM_HRPD_SYS_INFO_STRU        *pstHrpdSysInfo
);

VOS_VOID CNAS_HSM_SetLastUatiInfo(
    CNAS_HSM_UATI_INFO_STRU        *stUATIInfo
);

CNAS_HSM_SESSION_STATUS_ENUM_UINT8 CNAS_HSM_GetLastHrpdSessionStatus(VOS_VOID);

VOS_VOID CNAS_HSM_SetLastHrpdSessionStatus(
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enSessionStatus
);

VOS_VOID CNAS_HSM_SetFirstSysAcqFlag(
    VOS_UINT8                           ucFirstSysAcqFlg
);

VOS_UINT8 CNAS_HSM_GetFirstSysAcqFlag(VOS_VOID);



/*******************************************************************/

VOS_VOID CNAS_HSM_SetReqSessionType(
CNAS_HSM_SESSION_TYPE_ENUM_UINT8 enSessionType
);

CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_GetReqSessionType(VOS_VOID);

VOS_VOID CNAS_HSM_SetLastSessionType(CNAS_HSM_SESSION_TYPE_ENUM_UINT8 enSessionType);

CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_GetNegoSessionType(VOS_VOID);

VOS_VOID CNAS_HSM_SetNegoSessionType(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8 enCurSessionType
);

CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_GetLastSessionType(VOS_VOID);

VOS_VOID CNAS_HSM_ClearNegoSessionType(VOS_VOID);

VOS_UINT32 CNAS_HSM_IsCurrentCapSupportEhrpd(VOS_VOID);


VOS_UINT8 CNAS_HSM_GetOhmParameterUpToDate(VOS_VOID);

VOS_VOID CNAS_HSM_SetOhmParameterUpToDate(
    VOS_UINT8                           ucOhmParameterUpToDate
);


VOS_UINT8 CNAS_HSM_GetKeepAliveReqSndCount(VOS_VOID);

VOS_VOID CNAS_HSM_SetKeepAliveReqSndCount(
    VOS_UINT8                           ucKeepAliveReqSndCount
);

VOS_UINT8 CNAS_HSM_GetKeepAliveReqTransId(VOS_VOID);

VOS_VOID CNAS_HSM_SetKeepAliveReqTransId(
    VOS_UINT8                           ucKeepAliveReqTransId
);

VOS_VOID CNAS_HSM_IncreaseKeepAliveReqTransId(VOS_VOID);

VOS_UINT32 CNAS_HSM_GetSysTickFwdTrafficChan(VOS_VOID);

VOS_VOID CNAS_HSM_SetSysTickFwdTrafficChan(
    VOS_UINT32                          ulSysTick
);

VOS_UINT32 CNAS_HSM_GetOldSysTickFwdTrafChan(VOS_VOID);

VOS_VOID CNAS_HSM_SetOldSysTickFwdTrafChan(
    VOS_UINT32                          ulOldSysTickFwdTrafChan
);

VOS_UINT32 CNAS_HSM_GetKeepAliveTimerLen(VOS_VOID);

VOS_VOID CNAS_HSM_SetKeepAliveTimerLen(
    VOS_UINT32                          ulKeepAliveTimerLen
);

VOS_UINT32 CNAS_HSM_GetKeepAliveTimerTotalRunCount(VOS_VOID);

VOS_VOID CNAS_HSM_SetKeepAliveTimerTotalRunCount(
    VOS_UINT32                          ulTotalTimerRunCount
);

VOS_UINT32 CNAS_HSM_GetKeepAliveTimerExpiredCount(VOS_VOID);

VOS_VOID CNAS_HSM_SetKeepAliveTimerExpiredCount(
    VOS_UINT32                          ulTimerExpiredCount
);

VOS_UINT16 CNAS_HSM_GetTsmpClose(VOS_VOID);

VOS_VOID CNAS_HSM_SetTsmpClose(
    VOS_UINT16                          usTsmpClose
);

VOS_UINT32 CNAS_HSM_GetTsmpCloseRemainTime(VOS_VOID);

VOS_VOID CNAS_HSM_SetTsmpCloseRemainTime(
    VOS_UINT32                          ulTsmpCloseRemainTime
);

VOS_UINT32* CNAS_HSM_GetLastPowerOffSysTime(VOS_VOID);

VOS_VOID CNAS_HSM_SetLastPowerOffSysTime(
    VOS_UINT32                         *pulSysTime
);

VOS_UINT32* CNAS_HSM_GetLastReceivedSysTime(VOS_VOID);

VOS_VOID CNAS_HSM_SetLastReceivedSysTime(
    VOS_UINT32                         *pulSysTime
);

VOS_UINT32 CNAS_HSM_GetReferenceSysTick(VOS_VOID);

VOS_VOID CNAS_HSM_SetReferenceSysTick(
    VOS_UINT32                          ulSysTick
);

VOS_UINT8 CNAS_HSM_GetKeepAliveInfoValidFlag(VOS_VOID);

VOS_VOID CNAS_HSM_SetKeepAliveInfoValidFlag(
    VOS_UINT8                           ucIsKeepAliveInfoValid
);


/*******************************************************************/

CNAS_HSM_FSM_SWITCH_ON_CTX_STRU* CNAS_HSM_GetCardReadInfoAddr(VOS_VOID);

CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 CNAS_HSM_GetWaitCardReadCnfFlag(VOS_VOID);

VOS_VOID CNAS_HSM_SetWaitCardReadCnfFlag(
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32            enFlag
);

VOS_VOID CNAS_HSM_ClearWaitCardReadCnfFlag(
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32            enFlag
);

VOS_VOID CNAS_HSM_ResetWaitCardReadCnfFlag(VOS_VOID);

CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU*  CNAS_HSM_GetHrpdAmpNegAttribAddr(VOS_VOID);

VOS_VOID CNAS_HSM_SetCurrSessionRelType(
     CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType
);

CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8 CNAS_HSM_GetCurrSessionRelType(VOS_VOID);

VOS_VOID CNAS_HSM_SetSessionStatus(
     CNAS_HSM_SESSION_STATUS_ENUM_UINT8                enSessionStatus
);

CNAS_HSM_SESSION_STATUS_ENUM_UINT8 CNAS_HSM_GetSessionStatus(VOS_VOID);


CNAS_HSM_FSM_SESSION_ACTIVE_CTX_STRU* CNAS_HSM_GetSessionActiveFsmCtxAddr(VOS_VOID);

CNAS_HSM_FSM_CONN_MNMT_CTX_STRU* CNAS_HSM_GetConnMnmtFsmCtxAddr(VOS_VOID);

VOS_VOID CNAS_HSM_InitSessionActiveFsmCtx(
    CNAS_HSM_FSM_SESSION_ACTIVE_CTX_STRU *pstSessionActFsmCtx
);

VOS_VOID CNAS_HSM_InitConnMnmtFsmCtx(
    CNAS_HSM_FSM_CONN_MNMT_CTX_STRU *pstConnMnmtFsmCtx
);

VOS_VOID CNAS_HSM_SetAbortFlag_UatiReq(
    VOS_UINT8                           ucAbortFlg
);

VOS_UINT8 CNAS_HSM_GetAbortFlag_UatiReq(VOS_VOID);

VOS_VOID CNAS_HSM_SetAbortFlag_SessionDeact(
    VOS_UINT8                           ucAbortFlg
);

VOS_UINT8 CNAS_HSM_GetAbortFlag_SessionDeact(VOS_VOID);

VOS_VOID CNAS_HSM_SetAbortFlag_SessionActive(
    VOS_UINT8                           ucAbortFlg
);

VOS_VOID CNAS_HSM_SetReviseTimerScene_SessionDeact(
    CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM_UINT8    enReviseTimerScene
);

VOS_VOID CNAS_HSM_CleanReviseTimerScene_SessionDeact(VOS_VOID);

CNAS_HSM_SESSION_DEACT_REVISE_TIMER_SCENE_ENUM_UINT8 CNAS_HSM_GetReviseTimerScene_SessionDeact(VOS_VOID);

VOS_UINT8 CNAS_HSM_GetAbortFlag_SessionActive(VOS_VOID);

VOS_VOID CNAS_HSM_SetSessionActiveReason_SessionActive(
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason
);

VOS_UINT8 CNAS_HSM_GetSessionActiveReason_SessionActive(VOS_VOID);

VOS_UINT8 CNAS_HSM_GetPaNtfFlag_SessionActive(VOS_VOID);

VOS_VOID CNAS_HSM_SetPaNtfFlag_SessionActive(
    VOS_UINT8                           ucIsGetPaNtf
);

VOS_VOID CNAS_HSM_SetAbortFlag_ConnMnmt(
    VOS_UINT8                           ucAbortFlg
);

VOS_UINT8 CNAS_HSM_GetAbortFlag_ConnMnmt(VOS_VOID);




VOS_VOID CNAS_HSM_SetConnMnmtTriggerScene_ConnMnmt(
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8                   enTriggerScene
);

CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8 CNAS_HSM_GetConnMnmtTriggerScene_ConnMnmt(VOS_VOID);

VOS_UINT16 CNAS_HSM_GetSnpDataReqOpId(VOS_VOID);

VOS_VOID CNAS_HSM_IncreaseSnpDataReqOpId(VOS_VOID);

VOS_VOID CNAS_HSM_SaveHardWareIdRspSnpDataReqOpId(VOS_UINT16 usOpId);

VOS_UINT16 CNAS_HSM_GetHardWareIdRspSnpDataReqOpId(VOS_VOID);

VOS_VOID CNAS_HSM_SaveUatiReqSnpDataReqOpId(VOS_UINT16 usOpId);

VOS_UINT16 CNAS_HSM_GetUatiReqSnpDataReqOpId(VOS_VOID);

VOS_VOID CNAS_HSM_SaveUatiCmplSnpDataReqOpId(VOS_UINT16 usOpId);

VOS_UINT16 CNAS_HSM_GetUatiCmplSnpDataReqOpId(VOS_VOID);

VOS_VOID CNAS_HSM_SaveSessionCloseSnpDataReqOpId(VOS_UINT16 usOpId);

VOS_UINT16 CNAS_HSM_GetSessionCloseSnpDataReqOpId(VOS_VOID);

VOS_VOID CNAS_HSM_SaveKeepAliveReqSnpDataReqOpId(VOS_UINT16 usOpId);

VOS_UINT16 CNAS_HSM_GetKeepAliveReqSnpDataReqOpId(VOS_VOID);

VOS_VOID CNAS_HSM_SaveKeepAliveRspSnpDataReqOpId(VOS_UINT16 usOpId);

VOS_UINT16 CNAS_HSM_GetKeepAliveRspSnpDataReqOpId(VOS_VOID);

CNAS_HSM_STORE_ESN_MEID_RSLT_STRU* CNAS_HSM_GetStoreEsnMeidRsltAddr(VOS_VOID);

CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU* CNAS_HSM_GetCardStatusChangeInfoAddr(VOS_VOID);

VOS_UINT8* CNAS_HSM_GetLastIccIdAddr(VOS_VOID);

VOS_VOID CNAS_CCB_SetLastIccId(
    VOS_UINT8                          *pucIccId
);

VOS_UINT8 CNAS_HSM_GetSlotVoteBox(VOS_VOID);

VOS_VOID CNAS_HSM_SetSlotVoteBox(VOS_UINT8 ucSlotVoteBox);

VOS_VOID  CNAS_HSM_InitWaitUatiAssignTimerLenInfo(VOS_VOID);

CNAS_HSM_WAIT_UATI_ASSIGN_TIMER_LEN_INFO_STRU*  CNAS_HSM_GetWaitUatiAssignTimerLenInfoAddr(VOS_VOID);


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

#endif /* end of CnasHsmCtx.h */

