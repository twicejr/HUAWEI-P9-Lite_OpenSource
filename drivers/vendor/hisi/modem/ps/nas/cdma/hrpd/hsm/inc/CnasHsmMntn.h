

#ifndef __CNAS_HSM_MNTN_H__
#define __CNAS_HSM_MNTN_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "CnasHsmCtx.h"
#include  "CnasMntn.h"
#include  "CnasCcb.h"
#include  "PsTypeDef.h"
#include  "CnasHsmEncode.h"
#include  "CnasHsmKeepAlive.h"
#include  "CnasHsmFsmTbl.h"
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


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/
enum CNAS_HSM_MNTN_MSG_ID_ENUM
{
    ID_CNAS_HSM_MNTN_LOG_HARDWARE_ID_INFO               = ID_CNAS_MNTN_HSM_MSG_BASE,
    ID_CNAS_HSM_MNTN_LOG_BUFFER_MSG_INFO_IND,
    ID_CNAS_HSM_MNTN_LOG_FSM_MAIN_STATE_INFO_IND,
    ID_CNAS_HSM_MNTN_LOG_FSM_SUB_STATE_INFO_IND,
    ID_CNAS_HSM_MNTN_LOG_ENCODE_RESULT_IND,
    ID_CNAS_HSM_MNTN_LOG_DECODE_RESULT_IND,
    /*Air link mssage begin*/
    ID_CNAS_HSM_MNTN_MSG_TYPE_UATI_REQ,
    ID_CNAS_HSM_MNTN_MSG_TYPE_UATI_ASSIGN,
    ID_CNAS_HSM_MNTN_MSG_TYPE_UATI_COMPLETE,
    ID_CNAS_HSM_MNTN_MSG_TYPE_HARDWAREID_REQ,
    ID_CNAS_HSM_MNTN_MSG_TYPE_HARDWAREID_RESP,
    ID_CNAS_HSM_MNTN_MSG_TYPE_SESSION_CLOSE,
    ID_CNAS_HSM_MNTN_MSG_TYPE_KEEP_ALIVE_REQ,               /*_H2ASN_MsgChoice  CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU */
    ID_CNAS_HSM_MNTN_MSG_TYPE_KEEP_ALIVE_RESP,              /*_H2ASN_MsgChoice  CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU */
    /*Air link message end*/

    ID_CNAS_HSM_MNTN_LOG_AMP_SMP_NEG_ATTRS_INFO_IND,        /*_H2ASN_MsgChoice  CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_IND,            /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU */

    ID_CNAS_HSM_MNTN_LOG_RCV_ATI_LIST_INFO_IND,             /*_H2ASN_MsgChoice  CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU */

    ID_CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND,       /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND,                /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND,         /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND,           /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND,   /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND,     /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND,         /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND,              /*_H2ASN_MsgChoice  CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU */

    ID_CNAS_HSM_MNTN_LOG_BUTT
};
typedef VOS_UINT32 CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32;


enum CNAS_HSM_UATI_ASSIGN_CATE_ENUM
{
    CNAS_HSM_UATI_ASSIGN_CATE_NORMAL,
    CNAS_HSM_UATI_ASSIGN_CATE_NOT_FRESH,
    CNAS_HSM_UATI_ASSIGN_CATE_INVALID,
    CNAS_HSM_UATI_ASSIGN_BUTT
};
typedef VOS_UINT32 CNAS_HSM_UATI_ASSIGN_CATE_ENUM_UINT32;


enum CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ENUM
{
    CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ADD,                       /* add message to buffer queue */
    CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_REPLACE,                   /* replace exist message in buffer queue */
    CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_DEL,                       /* delete message from buffer queue */
    CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_BUTT
};
typedef VOS_UINT32 CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 The Declaration Of The Global Variable
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
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    CNAS_HSM_HARDWARE_ID_TYPE_ENUM_UINT32                   enHwidType;
    CNAS_HSM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32               enHwidSrcType;
    VOS_UINT32                                              ulEsn;                              /* 32-bit */
    VOS_UINT8                                               aucMeId[CNAS_HSM_MEID_OCTET_NUM];    /* 56-bit */
    VOS_UINT8                                               aucRsv[1];
}CNAS_HSM_LOG_HWID_INFO_STRU;


typedef struct
{
    CNAS_HSM_MSG_PRI_ENUM_UINT8         enMsgPri;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                           aucMsgBuffer[CNAS_HSM_MAX_MSG_BUFFER_LEN];
}CNAS_HSM_MNTN_CACHE_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                      /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;                    /* _H2ASN_Skip */
    CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ENUM_UINT32            enOperateType;
    VOS_UINT8                                               ucCurOperateMsgBuffIndex;   /* 增加或者删除的消息在缓存队列中的索引 */
    VOS_UINT8                                               ucCacheMsgNum;
    VOS_UINT8                                               aucRsv[2];
    VOS_UINT32                                              ulCurOperateMsgSenderPid;
    VOS_UINT32                                              ulCurOperateMsgId;
    CNAS_HSM_MNTN_CACHE_MSG_STRU                            astCacheMsg[CNAS_HSM_MAX_CACHE_MSG_QUEUE_NUM];
}CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                     /* _H2ASN_Skip */
    VOS_UINT32                          ulOldState;
    VOS_UINT32                          ulNewState;
}CNAS_HSM_LOG_FSM_STATE_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                     /* _H2ASN_Skip */
    VOS_UINT32                          ulErrCode;
}CNAS_HSM_LOG_CODEC_RESULT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                  stHardwareIdRsp;
}CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    CNAS_HSM_UATI_COMP_MSG_STRU                             stUatiComp;
}CNAS_HSM_LOG_MNTN_UATI_COMP_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    CNAS_HSM_SESSION_CLOSE_MSG_STRU                         stSessionClose;
}CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    CNAS_HSM_UATI_ASSIGN_CATE_ENUM_UINT32                   enUatiAssignCate;
    CNAS_HSM_UATI_ASSIGN_MSG_STRU                           stUatiAssign;
}CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    CNAS_HSM_UATI_REQ_MSG_STRU                              stUatiReq;
}CNAS_HSM_LOG_MNTN_UATI_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    CNAS_HSM_HARDWARE_ID_REQ_MSG                            stHardWareIdReq;
}CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU;


typedef struct
{
    VOS_UINT16                                              usTsmpClose;
    VOS_UINT8                                               ucResv[2];
}CNAS_HSM_SMP_NEG_ATTRIB_STRU;


typedef struct
{
    VOS_UINT16                                              usMaxNoMonitorDistance;
    VOS_UINT16                                              usHardwareSeparableFromSession;
    VOS_UINT16                                              usSupportGAUPMaxNoMonitorDistance;
    VOS_UINT16                                              usReducedSubnetMaskOffset;
    VOS_UINT16                                              usSupportSecondaryColorCodes;
    VOS_UINT8                                               ucResv[2];
}CNAS_HSM_AMP_NEG_ATTRIB_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    CNAS_HSM_SMP_NEG_ATTRIB_STRU                            stSmpNegAttrib;
    CNAS_HSM_AMP_NEG_ATTRIB_STRU                            stAmpNegAttrib;
}CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    VOS_UINT32                                              ulATIRecordNum;
    CNAS_HSM_ATI_RECORD_STRU                                astATIEntry[CNAS_HSM_MAX_UATI_REC_NUM];
}CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU;

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CNAS_HSM_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    CNAS_HSM_MNTN_MSG_DATA              stMsgData;
}CNAS_HSM_MNTN_MSG;


typedef struct
{
    VOS_MSG_HEADER                               /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;
    CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU    stKeepAliveReq;
}CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                               /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;
    CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU   stKeepAliveResp;
}CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU;



typedef struct
{
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;
    VOS_UINT8                                               ucSessionActTriedCntConnFail;
    VOS_UINT8                                               ucSessionActTriedCntOtherFail;
    VOS_UINT8                                               ucIsSessionActTimerRun;
    VOS_UINT8                                               ucSessionActMaxCntConnFail;
    VOS_UINT8                                               ucSessionActMaxCntOtherFail;
    VOS_UINT8                                               ucRsv[2];
    VOS_UINT32                                              ulSessionActTimerLen;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;
    VOS_UINT8                                               ucRsv1[2];
    CNAS_HSM_L1_STA_ENUM_UINT32                             enCurrMainState;
}CNAS_HSM_SESSION_DEACT_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;
    CNAS_HSM_SESSION_DEACT_INFO_STRU                        stSessionDeactInfo;
}CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                      /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;

    VOS_UINT32                                              ulIsKeepAliveAfterProc;

    CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM_UINT32             enKeepAliveTimerScene;
    VOS_UINT32                                              ulSysTickFwdTrafChan;
    VOS_UINT32                                              ulOldSysTickFwdTrafChan;
    VOS_UINT32                                              ulKeepAliveTimerLen;
    VOS_UINT32                                              ulTotalTimerRunCount;
    VOS_UINT32                                              ulTimerExpiredCount;
    VOS_UINT32                                              ulReferenceSysTick;
    VOS_UINT8                                               ucKeepAliveReqSndCount;
    VOS_UINT8                                               ucIsKeepAliveInfoValid;
    VOS_UINT8                                               ucKeepAliveReqTransId;
    VOS_UINT8                                               ucRsv;
    VOS_UINT16                                              usTsmpClose;
    VOS_UINT8                                               aucReserved[2];
    VOS_UINT32                                              ulTsmpCloseRemainTime;

}CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                              /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                /* _H2ASN_Skip */
    VOS_UINT32                          ulWaitReadCardCnfFlag;  /* wait read card cnf flag */
}CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_Skip */
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enCurSessionStatus;
    VOS_UINT8                           ucIsFirstSysAcq;
    VOS_UINT8                           aucRsv[2];
}CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;
}CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU;

/*****************************************************************************
 Structure Name    : CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU
 Description       : structure of log session recovery judge related info
 1.Date            : 2015-09-22
   Author          : t00323010
   Modification    : HSM MNTN(DTS2015092201636): Create
2. Date            : 2015-10-10
   Author          : w00351686
   Modification    : HSM MNTN(DTS2015092201636): Modified the structure name
3. Date            : 2015-10-13
   Author          : y00307564
   Modification    : DTS2015082403731: 增加换卡逻辑新增的ESN_MEID_ME和ppp an鉴权信息
4. Date            : 2015-12-22
   Author          : m00312079
   Modification    : DTS2015120208895: 增加UE支持的版本信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    VOS_UINT32                                              ulIsSessionExpired;
    VOS_UINT8                                               ucCardChangedFlg;
    VOS_UINT8                                               ucIsKeepAliveInfoValid;
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enLastSessionStatus;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enLastSessionType;
    VOS_UINT32                                              ulIsSupportEhrpd;
    VOS_UINT8                                               aucLastIccid[CNAS_HSM_ICCID_OCTET_NUM];
    VOS_UINT8                                               aucCurIccid[CNAS_HSM_ICCID_OCTET_NUM];
    CNAS_HSM_HARDWARE_ID_INFO_STRU                          stLastHwid;
    CNAS_HSM_HARDWARE_ID_INFO_STRU                          stCurHwid;
    VOS_UINT32                                              ulTsmpCloseRemainTime;
    VOS_UINT32                                              aulLastPowerOffSysTime[CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME];
    VOS_UINT32                                              aulReceivedSysTime[CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME];
    CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU                   stCardStatus;
    CNAS_HSM_STORE_ESN_MEID_RSLT_STRU                       stStoreEsnMeidRslt;
    CNAS_CCB_ESNMEIDME_INFO_STRU                            stCurEsnMeidMe;
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                     stlastAccessAuthInfo;
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                     stCurAccessAuthInfo;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                         stLastUERevInfo;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                         stCurUERevInfo;
}CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                              /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                /* _H2ASN_Skip */
    CNAS_HSM_SESSION_CTRL_STRU          stSessionCtrlInfo;
    CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU   stHrpdAmpNegAttibInfo;


    CNAS_HSM_MULTI_MODE_CTRL_INFO_STRU  stMultiModeCtrlInfo;
}CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubState;
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8                      enSessionStatus;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enCovertedCasStatus;
    CAS_CNAS_HRPD_CAS_STATUS_ENUM_UINT16                    enOriginalCasStatus;
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;
    VOS_UINT8                                               aucRsv[1];
}CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU;


enum CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ENUM
{
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ERROR_SNP_DATA_CNF          = 0x00,
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_BUFF_MSG_PROC               = 0x01,
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_BUTT
};
typedef VOS_UINT8 CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ENUM_UINT8;


typedef struct
{
    VOS_UINT16                          usSndOpId;
    VOS_UINT16                          usRcvOpId;
    CNAS_HSM_L1_STA_ENUM_UINT32         enMainState;
    CNAS_HSM_SS_ID_ENUM_UINT32          enSubState;
}CNAS_HSM_MNTN_LOG_DISCARD_SNP_DATA_CNF_REASON_STRU;


typedef union
{
    CNAS_HSM_MNTN_LOG_DISCARD_SNP_DATA_CNF_REASON_STRU      stDiscardSnpDataCnfReason;
}CNAS_HSM_MNTN_LOG_DISCARD_MSG_REASON_UNION;


typedef struct
{
    VOS_MSG_HEADER                                                          /* _H2ASN_Skip */
    CNAS_HSM_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;        /* _H2ASN_Skip */
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ENUM_UINT8          enDiscardMsgScene;
    VOS_UINT8                                               aucRsv[3];
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_REASON_UNION              unDiscardMsgReason;
}CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU;


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

VOS_VOID CNAS_HSM_LogHwIdInfo(
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstHwIdInfo
);

VOS_VOID  CNAS_HSM_LogBufferMsgInfo(
    MSG_HEADER_STRU                                        *pstCurOperateMsgHead,
    VOS_UINT8                                               ucMsgBuffIndex,
    CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ENUM_UINT32            enOperateType
);

VOS_VOID  CNAS_HSM_LogFsmStateInfoInd(
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulOldState,
    VOS_UINT32                          ulNewState
);

VOS_VOID  CNAS_HSM_LogCodecResultInd(
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulErrCode
);

VOS_VOID  CNAS_HSM_LogUatiReqMsg(
    CNAS_HSM_UATI_REQ_MSG_STRU                             *pstUatiReq
);

VOS_VOID  CNAS_HSM_LogUatiCompMsg(
    CNAS_HSM_UATI_COMP_MSG_STRU                            *pstUatiCmp
);

VOS_VOID  CNAS_HSM_LogHardWareIdRespMsg(
    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                 *pstHardwareIdInfo
);

VOS_VOID  CNAS_HSM_LogSessionCloseMsg(
    CNAS_HSM_SESSION_CLOSE_MSG_STRU                        *pstSessionCloseInput
);

VOS_VOID  CNAS_HSM_LogHardWareIdReqMsg(
    CNAS_HSM_HARDWARE_ID_REQ_MSG                              *pstHardWareIdReq
);

VOS_VOID  CNAS_HSM_LogUatiAssignMsg(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU                          *pstUatiAssign,
    CNAS_HSM_UATI_ASSIGN_CATE_ENUM_UINT32                   enUatiAssignCate
);

VOS_VOID CNAS_HSM_LogAmpSmpNegAttribInfoInd(
    CNAS_HSM_AMP_NEG_ATTRIB_STRU                           *pstAmpNegAttrib,
    CNAS_HSM_SMP_NEG_ATTRIB_STRU                           *pstSmpNegAttrib
);

VOS_VOID  CNAS_HSM_LogKeepAliveReq(
    CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU                       *pstKeepAliveReq
);

VOS_VOID  CNAS_HSM_LogKeepAliveResp(
    CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU                      *pstKeepAliveResp
);


VOS_VOID  CNAS_HSM_LogSessionDeactInfo(
    CNAS_HSM_SESSION_DEACT_INFO_STRU                       *pstSessionDeactInfo
);

VOS_VOID  CNAS_HSM_LogReceiveATIListInfo(
    CNAS_HSM_ATI_LIST_INFO_STRU                            *pstCurrRcvATIList
);

VOS_VOID  CNAS_HSM_LogSessionKeepAliveInfo(
    CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM_UINT32             enKeepAliveTimerScene,
    VOS_UINT32                                              ulIsKeepAliveAfterProc,
    CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU                      *pstKeepAliveCtrlCtxInfo
);

VOS_VOID CNAS_HSM_LogReadCardInfo(
    VOS_UINT32                          ulWaitCardReadCnfFlag
);

VOS_VOID CNAS_HSM_LogQuitSlaveStateInfo(
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enCurSessionStatus,
    VOS_UINT8                           ucIsFirstSysAcq
);

VOS_VOID CNAS_HSM_LogSessionRecoveryJudgeInfo(
    VOS_UINT8                           ucCardChangedFlg,
    VOS_UINT32                          ulIsSessionExpired
);

VOS_VOID CNAS_HSM_LogSessionOperateCtrlInfo(VOS_VOID);

VOS_VOID CNAS_HSM_LogConnMnmtStatusInfo(VOS_VOID);

VOS_VOID CNAS_HSM_LogDiscardMsgInfo(
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ENUM_UINT8          enDiscardMsgScene,
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_REASON_UNION             *punDiscardMsgReason
);

VOS_VOID CNAS_HSM_LogBuffQueueFullInd(VOS_VOID);
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

#endif /* end of CnasHsmDecode.h */




