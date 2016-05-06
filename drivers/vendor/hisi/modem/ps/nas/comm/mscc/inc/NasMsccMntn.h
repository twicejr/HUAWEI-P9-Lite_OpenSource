

#ifndef __NAS_MSCC_MNTN_H__
#define __NAS_MSCC_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "NasOmInterface.h"
#include "NasOmTrans.h"
#include "NasMsccCtx.h"
#include "NasMsccMlplMsplParse.h"
#include "NasNvInterface.h"
#include "NasMsccMlplMsplApi.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "omerrorlog.h"
#include "NasErrorLog.h"
#endif

#include "NasMntn.h"

#include "msp_diag_comm.h"
/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* #if __cplusplus */
#endif /* #ifdef __cplusplus */

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MSCC_MNTN_MSPL_MAX_NUM_MSPL_REC                 (10)
#define NAS_MSCC_MNTN_MLPL_MAX_NUM_SYS_LOC_TAG              (10)
#define NAS_MSCC_MNTN_MAX_NUM_MSPL_ID                       (10)
#define NAS_MSCC_MNTN_MAX_NUM_MLPL_REC                      (10)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum NAS_MSCC_MNTN_MSG_ID_BASE_ENUM
{
    /* 0x6000 ~ 0x6FFF为LOG保留 */
    ID_NAS_MSCC_MNTN_LOG_MSG_BASE           = 0x6000,                                   /* LOG模块间可维可测消息起始 */

    /* 0x7000 ~ 0x7FFF为internal message保留 */
    ID_NAS_MSCC_MNTN_INTERNAL_MSG_BASE      = 0x7000,                                   /* MSCC内部消息间可维可测消息起始 */

    /* 0x8000 ~ 0x8FFF为hook message保留 */
    ID_NAS_MSCC_MNTN_HOOK_MSG_BASE          = 0x8000,                                   /* MSCC HOOK消息可维可测消息起始 */

    /* 0x9000 ~ 0x9FFF为dynload message保留 */
    ID_NAS_MSCC_MNTN_DYNLOAD_MSG_BASE       = 0x9000,       /* MSCC DYNLOAD消息可维可测消息起始 */

    ID_NAS_MSCC_MNTN_MSG_BUTT
};
typedef VOS_UINT32 NAS_MSCC_MNTN_MSG_ID_BASE_ENUM_UINT32;





enum NAS_MSCC_MNTN_MSG_ID_ENUM
{
    ID_NAS_MSCC_MNTN_LOG_FSM_INFO_IND = ID_NAS_MSCC_MNTN_HOOK_MSG_BASE,  /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_FSM_INFO_STRU */

    ID_NAS_MSCC_MNTN_LOG_TIMER_INFO_IND,                                 /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_TIMER_INFO_IND_STRU */

    ID_NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_IND,                            /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU */

    ID_NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_IND,                            /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU */

    ID_NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_IND,                            /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU */

    ID_NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_IND,                       /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU */

    ID_NAS_MSCC_MNTN_LOG_MSPL_MSPL_HDR_INFO_IND,                         /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_MSPL_HEADER_STRU */

    ID_NAS_MSCC_MNTN_LOG_MSPL_MSPL_ID_INFO_IND,                          /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_MSPL_ID_LIST_STRU */

    ID_NAS_MSCC_MNTN_LOG_MSPL_CRC_CHK_RSLT_IND,                          /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU */

    ID_NAS_MSCC_MNTN_LOG_MLPL_MLPL_HDR_INFO_IND,                         /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_MLPL_HEADER_STRU */

    ID_NAS_MSCC_MNTN_LOG_MLPL_MLPL_REC_INFO_IND,                         /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU */

    ID_NAS_MSCC_MNTN_LOG_MLPL_CRC_CHK_RSLT_IND,                          /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU */

    ID_NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_IND,                           /*_H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU */

    ID_NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_IND,                              /* _H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU */

    ID_NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_IND,                              /* _H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU */

    ID_NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_IND,

    ID_NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND,                              /* _H2ASN_MsgChoice  NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND_STRU */

    ID_NAS_MSCC_MNTN_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_IND,    /* _H2ASN_MsgChoice  NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU */

    ID_NAS_MSCC_MNTN_LOG_FSM_L1_MAIN_CTX_RELATED_INFO,                   /* _H2ASN_MsgChoice  NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU */

#ifdef DMT
    ID_NAS_MSCC_MODIFY_MLPL_RECORD_REQ,

    ID_NAS_MSCC_MODIFY_MSPL_ID_REQ,

    ID_NAS_MSCC_SET_CARD_READ_STUB_TYPE_REQ,

#endif

    ID_NAS_MSCC_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32;



enum NAS_MSCC_DISCARD_SERV_STA_ENUM
{
    NAS_MSCC_DISCARD_HSD_SERVICE_STATUS_IND                = 0,    /* 屏蔽HSD service status 状态上报*/
    NAS_MSCC_DISCARD_MMC_SERVICE_STATUS_IND,                       /* 屏蔽MMC service status 状态上报*/

    NAS_MSCC_DISCARD_SERV_STA_BUTT
};
typedef VOS_UINT8 NAS_MSCC_DISCARD_SERV_STA_ENUM_UINT8;


enum NAS_MSCC_CARD_READ_STUB_TYPE_ENUM
{
    NAS_MSCC_CARD_READ_STUB_TYPE_NO_STUB,
    NAS_MSCC_CARD_READ_STUB_TYPE_MLPL_NO_REPLY,
    NAS_MSCC_CARD_READ_STUB_TYPE_MSPL_NO_REPLY,
    NAS_MSCC_CARD_READ_STUB_TYPE_MLPL_MSPL_NO_REPLY,

    NAS_MSCC_CARD_READ_STUB_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_CARD_READ_STUB_TYPE_ENUM_UINT8;


enum NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ENUM
{
    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS,
    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ALL_SYS_OF_1X,
    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN,
    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_MSPL_INDEX_OF_1X,
    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_HIGH_PRI_SYS_THAN_HRPD_BY_1X_LOC,
    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BSR_TIMER_LEN_OF_HRPD_BY_1X_LOC,

    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ENUM_UINT32;


enum NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_ENUM
{
    NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_3GPP,
    NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_1X,
    NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_HRPD,

    NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_ENUM_UINT32;

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
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    VOS_UINT32                                              ulCurFsmId;
    VOS_UINT32                                              ulCurFsmState;
}NAS_MSCC_MNTN_LOG_FSM_INFO_STRU;




typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*//* 消息头 */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32    enMsgId;
    VOS_UINT32                          ulFullFlg;
    NAS_MSCC_CACHE_MSG_QUEUE_STRU       stMsgQueue;
}NAS_MSCC_MNTN_LOG_BUFFER_MSG_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_MLPL_MSPL_SOURCE_ENUM_UINT32                   enSource;
    NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32                    enRslt;
}NAS_MSCC_MNTN_LOG_MLPL_PARSE_RSLT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_MLPL_MSPL_SOURCE_ENUM_UINT32                   enSource;
    NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32                    enRslt;
}NAS_MSCC_MNTN_LOG_MSPL_PARSE_RSLT_STRU;


typedef union
{
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                st3gppInfo;
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                  st1xInfo;
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU                stHrpdInfo;
}NAS_MSCC_MMSS_MATCH_INPUT_INFO_UNION;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ENUM_UINT32            enMatchPurpose;
    NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_ENUM_UINT32      enSysRat;
    NAS_MSCC_MMSS_MATCH_INPUT_INFO_UNION                    unInputSysInfo;
    VOS_UINT8                                               ucMlplMatchRslt;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlpLRec;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMsplMatchRslt;
    VOS_UINT8                                               ucMatchedMsplRecId;
    VOS_UINT8                                               ucCurSysTypeNotExistInMspl;/* 当前系统类型的记录是否在MSPL表中存在 */
    VOS_UINT8                                               aucRsv[1];
    VOS_UINT32                                              ulBsrTimerLen;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                        stMsplSysList;
}NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_STRU;



typedef struct
{
    NAS_MSCC_MLPL_MSPL_MATCH_PURPOSE_ENUM_UINT32            enMatchPurpose;
    NAS_MSCC_MLPL_MSPL_MATCH_INPUT_SYS_RAT_ENUM_UINT32      enSysRat;
    VOS_VOID                                               *pvSysInfo;
    VOS_UINT8                                               ucMlplMatchRslt;
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                      enMlplMatchLvl;
    VOS_UINT8                                               ucIsUseDfltMlpLRec;
    VOS_UINT8                                               ucMatchedMsplIndex;
    VOS_UINT8                                               ucMsplMatchRslt;
    VOS_UINT8                                               ucMatchedMsplRecId;
    VOS_UINT8                                               ucCurSysTypeNotExistInMspl;/* 当前系统类型的记录是否在MSPL表中存在 */
    VOS_UINT8                                               aucRsv[1];
    VOS_UINT32                                              ulBsrTimerLen;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstMsplSysList;
}NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU;



typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_MSPL_HEADER_STRU           stMsplHdrInfo;
}NAS_MSCC_MNTN_MSPL_HEADER_STRU;


typedef struct
{
    /* To indicate if current MSPL_ID is valid or not */
    VOS_UINT8                           ucIsMsplIdValid;

    /* MSPL_ID is the unique identifier of an MSPL table assigned by the base station */
    VOS_UINT8                           ucMsplId;

    /* This field is set to the number of MMSS system priority records
       contained in the MSPL block */
    VOS_UINT8                           ucNumMsplRec;
    VOS_UINT8                           ucReserved;

    /* ucNumMsplRec instances of MSPL record structure */
    NAS_MSCC_MSPL_REC_STRU              astMsplRec[NAS_MSCC_MNTN_MSPL_MAX_NUM_MSPL_REC];
}NAS_MSCC_MNTN_MSPL_ID_STRU;



typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_Skip */
    VOS_UINT32                          ulNumMsplId;
    NAS_MSCC_MNTN_MSPL_ID_STRU          astMsplIdList[NAS_MSCC_MNTN_MAX_NUM_MSPL_ID];
}NAS_MSCC_MNTN_MSPL_ID_LIST_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_MLPL_HEADER_STRU           stMlplHdrInfo;
}NAS_MSCC_MNTN_MLPL_HEADER_STRU;


typedef struct
{
    /* Mobile Country Code */
    VOS_UINT16                          usMcc;

    /* Mobile Network Code */
    VOS_UINT16                          usMnc;

    /* Number of System Location Tags */
    VOS_UINT8                           ucNumSysLocTag;
    VOS_UINT8                           aucReserve[3];

    /* ucNumSysLocTag instances of System Location Tags */
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU      astSysLocTag[NAS_MSCC_MNTN_MLPL_MAX_NUM_SYS_LOC_TAG];
}NAS_MSCC_MNTN_MLPL_LOC_PARAM_STRU;


typedef struct
{
    /* To indicate if current MLPL record is valid or not. */
    VOS_UINT8                           ucIsRecValid;

    /* This field identifies the parameter used for Location grouping */
    VOS_UINT8                           ucLocParamType;
    VOS_UINT8                           aucReserved1[2];

    /* LOC_PARAM_VAL is the value of the Location Parameter used.
       The length of this field is variable in length and depends on the
       LOC_PARAM_TYPE used for location grouping */
    NAS_MSCC_MNTN_MLPL_LOC_PARAM_STRU   stLocParamVal;

    /* This field is set to the MSPL_ID of the MMSS System Priority List
       scorresponding to an MLPL entry */
    VOS_UINT8                           ucMsplIndex;
    VOS_UINT8                           aucReserved2[3];
}NAS_MSCC_MNTN_MLPL_RECORD_STRU;



typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_Skip */
    VOS_UINT32                          ulNumMlplRec;
    NAS_MSCC_MNTN_MLPL_RECORD_STRU      astMlplRecList[NAS_MSCC_MNTN_MAX_NUM_MLPL_REC];
}NAS_MSCC_MNTN_MLPL_RECORD_LIST_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32 enCrcRslt;
}NAS_MSCC_MNTN_MLPL_MSPL_CRC_RSLT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_DISCARD_SERV_STA_ENUM_UINT8                    enDiscardServSta;   /* 被屏蔽的场景 */
    VOS_UINT8                                               aucRsv[3];
}NAS_MSCC_MNTN_LOG_DISCARD_SERV_STA_INFO_STRU;



typedef struct
{
    VOS_UINT32                                              ulIsHrpdLteBothSupported;
    NAS_MSCC_FSM_ID_ENUM_UINT32                             enCurrFsmId;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8                      en3gppPsServiceStatus;
    VOS_UINT8                                               ucSimPsRegStatus;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8                      enHrpdPsServiceStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimCardStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimCardStatus;
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8                        enMsccSleepTimerStatus;
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8                        enMsccAvailTimerStatus;
    VOS_UINT8                                               ucHrpdConnExistFlg;
    VOS_UINT8                                               ucLteEpsConnExistFlg;
    VOS_UINT8                                               ucMlplMsplValidFlag;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_MNTN_BSR_CTRL_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_MNTN_BSR_CTRL_INFO_STRU                        stBsrCtrlInfo;
}NAS_MSCC_MNTN_LOG_BSR_CTRL_INFO_STRU ;

#ifdef DMT

typedef struct
{
    VOS_UINT8                           ucIsRecValid;
    VOS_UINT8                           ucLocParamType;
    VOS_UINT8                           ucMsplIndex;
    VOS_UINT8                           ucSysLocTagIndex;
    VOS_UINT16                          usMcc;
    VOS_UINT16                          usMnc;
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU      stSysLocTag;
}NAS_MSCC_MODIFIED_MLPL_RECORD_STRU;


typedef struct
{
    VOS_UINT8                           ucMlplRecIndex;
    VOS_UINT8                           aucRsv[3];
    NAS_MSCC_MODIFIED_MLPL_RECORD_STRU  stMlplRec;
}NAS_MSCC_MODIFIED_MLPL_RECORD_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucRecNum;/* how many mlpl records u have to modify */
    VOS_UINT8                                               ucIsContainDefRec;
    VOS_UINT8                                               aucReserved[2];
    NAS_MSCC_MODIFIED_MLPL_RECORD_INFO_STRU                 astMlplRecord[NAS_MSCC_MAX_NUM_MLPL_REC];
}NAS_MSCC_MSCC_MODIFY_MLPL_RECORD_REQ_STRU;


typedef struct
{
    VOS_UINT8                           ucIsMsplIdValid;
    VOS_UINT8                           ucMsplId;
    VOS_UINT8                           ucMsplRecIndex;
    VOS_UINT8                           ucReserved;
    NAS_MSCC_MSPL_REC_STRU              stMsplRec;
}NAS_MSCC_MODIFIED_MSPL_ID_STRU;


typedef struct
{
    VOS_UINT8                           ucMlplIdIndex;
    VOS_UINT8                           aucRsv[3];
    NAS_MSCC_MODIFIED_MSPL_ID_STRU      stMsplId;
}NAS_MSCC_MODIFIED_MSPL_ID_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucRecNum;/* how many mspl id u have to modify */
    VOS_UINT8                                               aucReserved[3];
    NAS_MSCC_MODIFIED_MSPL_ID_INFO_STRU                     astMsplId[NAS_MSCC_MAX_NUM_MSPL_ID];
}NAS_MSCC_MSCC_MODIFY_MSPL_ID_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_CARD_READ_STUB_TYPE_ENUM_UINT8                 enStubType;
    VOS_UINT8                                               aucRsv[1];
}NAS_MSCC_SET_CARD_READ_STUB_TYPE_REQ_STRU;


#endif


/** ****************************************************************************
 * Name        : NasMsccMntn_DATA
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_MsgChoice_Export NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsgBlock[4];

    /* _H2ASN_MsgChoice_When_Comment NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32 */

}NasMsccMntn_DATA;

/* _H2ASN_Length UINT32*/
/** ****************************************************************************
 * Name        : NasMsccMntn_MSG
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    NasMsccMntn_DATA                    stMsgData;
}NasMsccMntn_MSG;



typedef struct
{
    VOS_MSG_HEADER
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;
    NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU                   stNvimMmssCfg;
}NAS_MSCC_MNTN_LOG_MMSS_NVIM_CFG_STRU;



typedef struct
{
    VOS_MSG_HEADER
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;
    NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU                   stNvimLastLocInfo;
}NAS_MSCC_MNTN_LOG_MMSS_NVIM_LAST_LOC_INFO_STRU;



typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT16                              enNvItem;
    VOS_UINT16                              usNvDataLength;
    VOS_UINT32                              ulPid;
    VOS_UINT8                               aucNvInfo[4];/* NV内容 */
}NAS_MSCC_MNTN_LOG_READ_NV_INFO_IND_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU
 结构说明  : 输出CL系统捕获策略相关的可维可测信息结构体
 1.日    期   : 2015年12月15日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseOnePatternCfg;
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU  stPhaseTwoPatternCfg;
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8  enCur1xServiceSysAcqPhaseNum;
    VOS_UINT8                                               aucRsv[3];
}NAS_MSCC_LOG_CL_SYSTEM_ACQUIRE_STRATEGY_RELATED_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU
 结构说明  : 输出L1状态机上下文相关的可维可测信息结构体
 1.日    期   : 2015年12月15日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    NAS_MSCC_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    VOS_UINT32                                              ulOosAvailableTimerCount;
    VOS_UINT8                                               ucCur1xSrvHistorySrchCount;
    VOS_UINT8                                               ucCur1xSrvFullBandSrchCount;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MSCC_MNTN_DISCARD_MSG_STRU
 结构说明  : 复位分析要忽略的消息的结构体
 1.日    期   : 2016年01月23日
   作    者   : l00324781
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_PID                             ulSenderPid;        /* 消息发送方PID */
    VOS_PID                             ulReceiverPid;      /* 消息发送方PID */
    VOS_UINT32                          ulMsgName;          /* 发送消息ID */
}NAS_MSCC_MNTN_DISCARD_MSG_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID NAS_MSCC_MNTN_LogFsmInfo(
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState
);

VOS_VOID  NAS_MSCC_MNTN_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

VOS_VOID  NAS_MSCC_MNTN_TraceIntMsg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulLength,
    VOS_VOID                           *pMsg
);

VOS_VOID NAS_MSCC_MNTN_LogMlplParseRslt(
    NAS_MSCC_MLPL_MSPL_SOURCE_ENUM_UINT32                   enSource,
    NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32                    enRslt
);

VOS_VOID NAS_MSCC_MNTN_LogMsplParseRslt(
    NAS_MSCC_MLPL_MSPL_SOURCE_ENUM_UINT32                   enSource,
    NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32                    enRslt
);

VOS_VOID NAS_MSCC_MNTN_LogMlplMsplMatchRslt(
    NAS_MSCC_MNTN_LOG_MLPL_MSPL_MATCH_RSLT_INPUT_STRU      *pstLogMatchRsltInput
);

VOS_VOID NAS_MSCC_MNTN_LogMsplHeaderInfo(
    NAS_MSCC_MSPL_HEADER_STRU          *pstMsplHeaderInfo
);

VOS_VOID NAS_MSCC_MNTN_GetMsplRec(
    NAS_MSCC_MSPL_REC_STRU             *pDesMsplRecList,
    NAS_MSCC_MSPL_REC_STRU             *pSrcMsplRecList
);

VOS_VOID NAS_MSCC_MNTN_LogMlplHeaderInfo(
    NAS_MSCC_MLPL_HEADER_STRU          *pstMlplHeaderInfo
);

VOS_VOID NAS_MSCC_MNTN_GetMlplSysLocTag(
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pDesSysLocTag,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pSrcSysLocTag
);

VOS_VOID NAS_MSCC_MNTN_LogMsplInfo(
    NAS_MSCC_MSPL_STRU                 *pstMsplInfo
);

VOS_VOID NAS_MSCC_MNTN_LogMlplInfo(
    NAS_MSCC_MLPL_STRU                 *pstMlplInfo
);

VOS_VOID NAS_MSCC_MNTN_LogMlplMsplCrcChkRslt(
    NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32                     enCrcCause,
    NAS_MSCC_MLPL_MSPL_PARSE_TYPE_ENUM_UINT8                enType
);

VOS_VOID NAS_MSCC_MNTN_LogDiscardServStaInfo(
    NAS_MSCC_DISCARD_SERV_STA_ENUM_UINT8              enDisacrdServSta
);

VOS_VOID NAS_MSCC_MNTN_LogBsrCtrlInfo(
    NAS_MSCC_MNTN_BSR_CTRL_INFO_STRU   *pstInStateInfo
);

VOS_VOID NAS_MSCC_MNTN_LogNvimMmssCfgInfo(
    NAS_NVIM_MMSS_SYSTEM_ACQUIRE_CFG_STRU                 *pstMmssNvimCfgInfo
);

VOS_VOID NAS_MSCC_MNTN_LogNvimMmssLastLocInfo(
    NAS_NVIM_MMSS_LAST_LOCATION_INFO_STRU                 *pstMmssNvimLastLocInfo
);

/* Deleted by wx270776 for OM融合, 2015-08-21, Begin */
/* Deleted by wx270776 for OM融合, 2012-08-21, End */

VOS_VOID NAS_MSCC_LogReadNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
);

VOS_VOID NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo(VOS_VOID);

VOS_VOID NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo(VOS_VOID);

VOS_UINT32 NAS_MSCC_MNTN_IsNeedDiscardForRcvMsg(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName
);
VOS_UINT32 NAS_MSCC_MNTN_IsNeedDiscardForSndMsg(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName
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
#endif                                                                                 /* __cpluscplus                              */

#endif

