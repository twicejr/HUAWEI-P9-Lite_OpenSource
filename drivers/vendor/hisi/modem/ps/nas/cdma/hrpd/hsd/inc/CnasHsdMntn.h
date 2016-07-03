

#ifndef __CNAS_HSD_MNTN_H__
#define __CNAS_HSD_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "CnasHsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasPrlApi.h"
#include  "CnasCcb.h"
#include  "NasNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_HSD_MAX_LOG_FREQ_NUM_IN_SCAN_LIST              (128)

#define CNAS_HSD_MAX_LOG_SYSTEM_NUM_IN_ACQ_LIST             (256)

#define CNAS_HSD_MAX_LOG_HRPD_SYS_NUM                       (128)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum CNAS_HSD_MNTN_MSG_ID_ENUM
{
    ID_CNAS_HSD_MNTN_LOG_SCAN_FREQ_LIST_IND                 = ID_CNAS_MNTN_HSD_MSG_BASE,    /*_H2ASN_MsgChoice  CNAS_HSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU */

    ID_CNAS_HSD_MNTN_LOG_HRPD_SYS_LIST_IND,                                                 /*_H2ASN_MsgChoice  CNAS_HSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU */

    ID_CNAS_HSD_MNTN_LOG_MRU_LIST_IND,                                                      /*_H2ASN_MsgChoice  CNAS_HSD_LOG_MRU_LIST_MSG_STRU */

    ID_CNAS_HSD_MNTN_LOG_OOC_TIMER_SCHEDULE_IND,                                            /*_H2ASN_MsgChoice  CNAS_HSD_MNTN_LOG_OOC_TIMER_SCHEDULE_IND */

    ID_CNAS_HSD_MNTN_LOG_OOC_CTX_INFO_IND,                                                  /*_H2ASN_MsgChoice  CNAS_HSD_MNTN_LOG_OOC_CTX_INFO_IND */

    ID_CNAS_HSD_MNTN_LOG_AVOID_FREQ_LIST_IND,                                               /*_H2ASN_MsgChoice  CNAS_HSD_MNTN_LOG_AVOID_FREQ_LIST_IND */

    ID_CNAS_HSD_MNTN_LOG_REDIRECT_FREQ_LIST_IND,                                            /*_H2ASN_MsgChoice  CNAS_HSD_MNTN_LOG_REDIRECT_FREQ_LIST_IND */

    ID_CNAS_HSD_MNTN_LOG_PRL_SOURCE_TYPE_IND,                                               /*_H2ASN_MsgChoice  CNAS_HSD_MNTN_LOG_PRL_SOURCE_TYPE_IND */

    ID_CNAS_HSD_MNTN_LOG_OPER_LOCK_WHITE_SID_LIST_IND,                                      /*_H2ASN_MsgChoice  CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU */

    ID_CNAS_HSD_MNTN_LOG_CTCC_CUSTOMIZE_FREQ_LIST_IND,                                      /*_H2ASN_MsgChoice  CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU */

    ID_CNAS_HSD_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 CNAS_HSD_MNTN_MSG_ID_ENUM_UINT32;


enum CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM
{
    ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_READ_NV =0,

    ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_STAY_SUCC ,

    ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM_UINT8;


enum CNAS_HSD_PRL_SOURCE_TYPE_ENUM
{
    CNAS_HSD_PRL_TYPE_EPRL_FILE,
    CNAS_HSD_PRL_TYPE_PRL_FILE,
    CNAS_HSD_PRL_TYPE_NVRAM,
    CNAS_HSD_PRL_TYPE_HARD_CODE,

    CNAS_HSD_PRL_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_HSD_PRL_SOURCE_TYPE_ENUM_UINT8;

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
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enMsgLogType;
    VOS_UINT8                                               ucLowPrioLevel;
    VOS_UINT8                                               ucRsv[3];
    VOS_UINT16                                              usTotalItemNum;
    VOS_UINT16                                              usCurScanIndex;
    CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU                       astScanFreqList[CNAS_HSD_MAX_LOG_FREQ_NUM_IN_SCAN_LIST];/* 频点扫描列表 */
}CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU;



typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enMsgLogType;
    VOS_UINT16                                              usSysNum;
    VOS_UINT8                                               aucRsv[2];
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU                         astSysRecList[CNAS_HSD_MAX_LOG_HRPD_SYS_NUM];       /* 系统捕获列表 */
}CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU;




typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM_UINT8                   enMruLogType;
    VOS_UINT8                                               ucSysNum;
    VOS_UINT8                                               aucReserve[2];
    CNAS_PRL_HRPD_SYSTEM_STRU                               astSystem[CNAS_HSD_MAX_MRU_SYS_NUM];
}CNAS_HSD_LOG_MRU_LIST_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                                               ucMru0SearchTimerLen;
    VOS_UINT8                                               ucPhaseNum;
    VOS_UINT8                                               aucReserved[2];
    CNAS_HSD_OOC_TIMER_INFO_STRU                            astOocTimerInfo[CNAS_HSD_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucWaitSearchFlag;
    VOS_UINT8                           ucCurrentPhase;
    VOS_UINT16                          usCurrentTimes;
    VOS_UINT8                           ucSceneSetFlag;
    VOS_UINT8                           aucReserved[3];
}CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                                               ucAvoidItemUsedNum;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT8                                               aucCounter[CNAS_HSD_AVOID_REASON_MAX];
    CNAS_HSD_AVOID_FREQ_INFO_STRU                           astAvoidFreqInfo[CNAS_HSD_MAX_AVOID_FREQ_NUM];
}CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER
    CAS_HRPD_AIRLINKMGMT_NAS_PIF_MSG_TYPE_ENUM_UINT16       enMsgId;
    VOS_UINT16                                              usOpId;
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason;
    VOS_UINT8                                               ucChanNum;
    VOS_UINT8                                               aucRev[1];
    CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU                    aulChannel[CAS_CNAS_HRPD_MAX_REDIRECT_CH_NUM];
} CNAS_HSD_LOG_REDIRCT_MSG_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucEnable;                          /* 白名单是否使能 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;
    CNAS_CCB_SYS_INFO_STRU              astSysInfo[CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM];
}CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_CCB_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CCB_MAX_FREQ_NUM];
}CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    CNAS_HSD_PRL_SOURCE_TYPE_ENUM_UINT8 enPrlSrcType;
    VOS_UINT8                           aucReserve[3];
}CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU;

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
    CNAS_HSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_HSD_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_HSD_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CNAS_HSD_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    CNAS_HSD_MNTN_MSG_DATA              stMsgData;
}CNAS_HSD_MNTN_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CNAS_HSD_LogScanFreqList(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU           *pstScanFreqList,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32           enMsgLogType
);

VOS_VOID CNAS_HSD_LogSysRecList(
    CNAS_HSD_HRPD_SYS_LIST_STRU                  *pstSysRecList,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32            enMsgLogType
);

VOS_VOID CNAS_HSD_LogMruList(
    CNAS_HSD_HRPD_MRU_LIST_STRU                  *pstMruList,
    CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM_UINT8         enMruLogType
);

VOS_VOID CNAS_HSD_LogOocScheduleInfo(
    CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU            *pstOocTimerScheduleInfo
);

VOS_VOID CNAS_HSD_LogOocCtxInfo(
    CNAS_HSD_OOC_CTX_INFO_STRU         *pstOocCtxInfo
);

VOS_VOID CNAS_HSD_LogAvoidFreqList(
    CNAS_HSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList
);

VOS_VOID CNAS_HSD_LogRedirectionFreqList(
    CNAS_HSD_REDIRECTION_STRU           *pstRedirection
);

VOS_VOID CNAS_HSD_LogOperLockSysWhiteList(
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstMsg
);

VOS_VOID CNAS_HSD_LogCTCCCustomizeFreqList(
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstMsg
);

VOS_VOID CNAS_HSD_LogPrlSourceType(
    CNAS_HSD_PRL_SOURCE_TYPE_ENUM_UINT8 enPrlSrcType
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

#endif /* end of CnasHsdMntn.h */

