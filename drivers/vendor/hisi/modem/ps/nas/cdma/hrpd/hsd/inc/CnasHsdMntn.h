/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdMntn.h
  版 本 号   : 初稿
  作    者   : d00212987
  生成日期   : 2014年12月16日
  最近修改   :
  功能描述   : CnasHsdMntn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月16日
    作    者   : d00212987
    修改内容   : 创建文件

******************************************************************************/

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
/*****************************************************************************
 枚举名    : CNAS_HSD_MNTN_MSG_ID_ENUM
 结构说明  : CNAS HSD模块发送给OM的可维可测消息
  1.日    期   : 2014年12月16日
    作    者   : d00212987
    修改内容   : CNAS XSD模块发送给OM的可维可测消息
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

/*****************************************************************************
 枚举名    : CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM
 结构说明  : CNAS HSD模块发送给OM的可维可测消息
  1.日    期   : 2014年12月16日
    作    者   : d00212987
    修改内容   : CNAS XSD模块发送给OM的可维可测消息
*****************************************************************************/
enum CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM
{
    ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_READ_NV =0,

    ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_STAY_SUCC ,

    ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_HSD_PRL_SOURCE_TYPE_ENUM_UINT8
 结构说明  : PRL源类型，即PRL是来源与EPRL文件，PRL文件，NVRAM或HARD CODE
  1.日    期   : 2015年08月18日
    作    者   : x00306642
    修改内容   : 新建
*****************************************************************************/
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
/*****************************************************************************
 结构名    : CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU
 结构说明  : 输出到SDT的扫描频点列表消息结构体
 1.日    期   : 2014年12月18日
   作    者   : d00212987
   修改内容   : 新增
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


/*****************************************************************************
 结构名    : CNAS_HSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU
 结构说明  : 输出到SDT的捕获系统列表消息结构体
 1.日    期   : 2014年12月18日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enMsgLogType;
    VOS_UINT16                                              usSysNum;
    VOS_UINT8                                               aucRsv[2];
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU                         astSysRecList[CNAS_HSD_MAX_LOG_HRPD_SYS_NUM];       /* 系统捕获列表 */
}CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU;


/*****************************************************************************
 结构名    : CNAS_HSD_LOG_MRU_LIST_MSG_STRU
 结构说明  : 输出到SDT的MRU列表消息结构体
 1.日    期   : 2014年12月18日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM_UINT8                   enMruLogType;
    VOS_UINT8                                               ucSysNum;
    VOS_UINT8                                               aucReserve[2];
    CNAS_PRL_HRPD_SYSTEM_STRU                               astSystem[CNAS_HSD_MAX_MRU_SYS_NUM];
}CNAS_HSD_LOG_MRU_LIST_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU
 结构说明  : 输出到SDT的OOC timer调度消息结构体
 1.日    期   : 2015年01月13日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                                               ucMru0SearchTimerLen;
    VOS_UINT8                                               ucPhaseNum;
    VOS_UINT8                                               aucReserved[2];
    CNAS_HSD_OOC_TIMER_INFO_STRU                            astOocTimerInfo[CNAS_HSD_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU
 结构说明  : 输出到SDT的OOC上下文消息结构体
 1.日    期   : 2015年02月05日
   作    者   : z00316370
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucWaitSearchFlag;
    VOS_UINT8                           ucCurrentPhase;
    VOS_UINT16                          usCurrentTimes;
    VOS_UINT8                           ucSceneSetFlag;
    VOS_UINT8                           aucReserved[3];
}CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU
 结构说明  : 输出到SDT的avoid频点列表消息结构体
 1.日    期   : 2015年01月07日
   作    者   : x00306642
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                                               ucAvoidItemUsedNum;
    VOS_UINT8                                               aucReserve[3];
    VOS_UINT8                                               aucCounter[CNAS_HSD_AVOID_REASON_MAX];
    CNAS_HSD_AVOID_FREQ_INFO_STRU                           astAvoidFreqInfo[CNAS_HSD_MAX_AVOID_FREQ_NUM];
}CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_LOG_REDIRCT_MSG_STRU
 结构说明  : 将收到的重定向频点法向LOG工具中
 1.日    期   : 2015年1月18s日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/
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

/*****************************************************************************
 结构名    : CNAS_HSD_LOG_OPER_LOCK_WHITE_SID_LIST_STRU
 结构说明  : 输出到SDT的OPER LOCK WHITE SID LIST
 1.日    期   : 2015年8月1日
   作    者   : x00306642
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucEnable;                          /* 白名单是否使能 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;
    CNAS_CCB_SYS_INFO_STRU              astSysInfo[CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM];
}CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU
 结构说明  : 输出到SDT的CTCC自定义频点列表
 1.日    期   : 2015年8月1日
   作    者   : x00306642
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_CCB_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CCB_MAX_FREQ_NUM];
}CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU
 结构说明  : 输出到SDT的prl源类型
 1.日    期   : 2015年08月18日
   作    者   : x00306642
   修改内容   : 新增
*****************************************************************************/
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

