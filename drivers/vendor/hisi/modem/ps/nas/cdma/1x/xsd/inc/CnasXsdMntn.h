/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdMntn.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2014年8月18日
  最近修改   :
  功能描述   : CnasXsdMntn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年8月18日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XSD_MNTN_H__
#define __CNAS_XSD_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "PsLogdef.h"
#include  "CnasXsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasPrlApi.h"
#include  "CnasCcb.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_XSD_MAX_LOG_CHANNEL_NUM_IN_SCAN_LIST           (512)

#define CNAS_XSD_MAX_LOG_SYSTEM_NUM_IN_ACQ_LIST             (256)




/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_XSD_PRL_SOURCE_TYPE_ENUM_UINT8
 结构说明  : PRL源类型，即PRL是来源与EPRL文件，PRL文件，NVRAM或HARD CODE
  1.日    期   : 2014年10月28日
    作    者   : y00245242
    修改内容   : 新建
*****************************************************************************/
enum CNAS_XSD_PRL_SOURCE_TYPE_ENUM
{
    CNAS_XSD_PRL_TYPE_EPRL_FILE,
    CNAS_XSD_PRL_TYPE_PRL_FILE,
    CNAS_XSD_PRL_TYPE_NVRAM,
    CNAS_XSD_PRL_TYPE_HARD_CODE,

    CNAS_XSD_PRL_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_XSD_PRL_SOURCE_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_XSD_MNTN_MSG_ID_ENUM
 结构说明  : CNAS XSD模块发送给OM的可维可测消息
  1.日    期   : 2014年08月18日
    作    者   : W00176964
    修改内容   : CNAS XSD模块发送给OM的可维可测消息
*****************************************************************************/
enum CNAS_XSD_MNTN_MSG_ID_ENUM
{
    ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND                 = ID_CNAS_MNTN_XSD_MSG_BASE,    /*_H2ASN_MsgChoice  CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_ACQ_SYS_LIST_IND,                                                  /*_H2ASN_MsgChoice  CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_AVAIL_SYS_LIST_IND,                                                /*_H2ASN_MsgChoice  CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_MRU_LIST_IND,                                                      /*_H2ASN_MsgChoice  CNAS_XSD_LOG_MRU_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_AVOID_FREQ_LIST_IND,                                               /*_H2ASN_MsgChoice  CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_PRL_SOURCE_TYPE_IND,                                               /*_H2ASN_MsgChoice  CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_BUFFER_MSG_INFO_IND,                                               /*_H2ASN_MsgChoice  CNAS_XSD_LOG_BUffER_MSG_INFO_STRU */

    ID_CNAS_XSD_MNTN_LOG_CALL_REDIAL_SCAN_CHAN_LIST_IND,                                    /*_H2ASN_MsgChoice  CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_BANDClASS_LIST_IND,                                                /*_H2ASN_MsgChoice  CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_REDIR_SCAN_CHAN_LIST_IND,                                          /*_H2ASN_MsgChoice  CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_CFREQLOCK_SCAN_CHAN_LIST_IND,                                      /*_H2ASN_MsgChoice  CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_HOME_SID_NID_LIST_IND,                                             /*_H2ASN_MsgChoice  CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_OOC_TIMER_SCHEDULE_IND,                                            /*_H2ASN_MsgChoice  CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_OOC_CTX_INFO_IND,                                                  /*_H2ASN_MsgChoice  CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_HOME_SID_NID_PRI_FLG,                                              /*_H2ASN_MsgChoice  CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU */

    ID_CNAS_XSD_MNTN_LOG_OPER_LOCK_WHITE_SID_LIST_IND,                                      /*_H2ASN_MsgChoice  CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU */

    ID_CNAS_XSD_MNTN_LOG_CTCC_CUSTOMIZE_FREQ_LIST_IND,                                      /*_H2ASN_MsgChoice  CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU */

    ID_CNAS_XSD_MNTN_LOG_EMC_CALL_REDIAL_SCAN_CHAN_LIST_IND,                                /*_H2ASN_MsgChoice  CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU */

    ID_CNAS_XSD_MNTN_LOG_GEO_LIST_SRCH_STATUS_IND,                                          /*_H2ASN_MsgChoice  CNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU */

    ID_CNAS_XSD_MNTN_LOG_CDMA_STANDARD_CHANNELS_IND,                                        /*_H2ASN_MsgChoice  CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU */

    ID_CNAS_XSD_MNTN_LOG_CALLBACK_CFG_IND,                                                  /*_H2ASN_MsgChoice  CNAS_XSD_LOG_CALLBACK_CFG_STRU */

    ID_CNAS_XSD_MNTN_LOG_ENTER_CALLBACK_IND,                                                /*_H2ASN_MsgChoice  CNAS_XSD_LOG_CALLBACK_STATUS_STRU */

    ID_CNAS_XSD_MNTN_LOG_QUIT_CALLBACK_IND,                                                 /*_H2ASN_MsgChoice  CNAS_XSD_LOG_CALLBACK_STATUS_STRU */

    ID_CNAS_XSD_MNTN_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_IND,                                  /*_H2ASN_MsgChoice  CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU */

    ID_CNAS_XSD_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32;


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
 结构名    : CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU
 结构说明  : 输出到SDT的扫描频点列表消息结构体
 1.日    期   : 2014年8月18日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usChanNum;
    VOS_UINT16                          usCurScanIndex;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     astScanChanList[CNAS_XSD_MAX_LOG_CHANNEL_NUM_IN_SCAN_LIST];/* 频点扫描列表 */
}CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU
 结构说明  : 输出到SDT的捕获系统列表消息结构体
 1.日    期   : 2014年8月18日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT16                          usSysNum;
    VOS_UINT8                           aucRsv[2];
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU   astAcqSysList[CNAS_XSD_MAX_LOG_SYSTEM_NUM_IN_ACQ_LIST];   /* 系统捕获列表 */
}CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU
 结构说明  : 输出到SDT的AVIALABLE系统列表消息结构体
 1.日    期   : 2014年8月18日
   作    者   : w00176964
   修改内容   : 新增

 2.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucAvailSysNum;
    VOS_UINT8                           ucNextSrchIndex;
    VOS_UINT8                           aucRsved[2];
    CNAS_XSD_AVAIL_SYSTEM_INFO_STRU     astAvailSystem[CNAS_XSD_MAX_AVAILABLE_SYS_NUM];
}CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_MRU_LIST_MSG_STRU
 结构说明  : 输出到SDT的MRU列表消息结构体
 1.日    期   : 2014年8月18日
   作    者   : w00176964
   修改内容   : 新增
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_PRL_1X_SYSTEM_STRU             astSystem[CNAS_XSD_MAX_MRU_SYS_NUM];
}CNAS_XSD_LOG_MRU_LIST_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                          ulBandClass;
}CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU
 结构说明  : 输出到SDT的HOME_SID_NID列表消息结构体
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucSysNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_CCB_1X_HOME_SID_NID_STRU       astHomeSidNid[CNAS_CCB_MAX_HOME_SID_NID_LIST];
}CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU
 结构说明  : 输出到SDT的OOC timer调度消息结构体
 1.日    期   : 2014年12月31日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT8                           ucPhaseNum;
    VOS_UINT8                           uc1xOocDoTchPhase1TimerLen;                         /* Do TCH，前4次尝试 Ooc Timer 最短时长 */
    VOS_UINT8                           uc1xOocDoTchPhase2TimerLen;                         /* Do TCH，4次以上尝试 Ooc Timer 最短时长 */
    CNAS_XSD_OOC_TIMER_INFO_STRU        astOocTimerInfo[CNAS_XSD_MAX_OOC_SCHEDULE_PHASE_NUM];
}CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU
 结构说明  : 输出到SDT的avoid频点列表消息结构体
 1.日    期   : 2014年10月22日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucAvoidFreqNum;
    VOS_UINT8                           aucReserve[3];
    CNAS_XSD_AVOID_FREQ_INFO_STRU       astAvoidFreqInfo[CNAS_XSD_MAX_AVOID_FREQ_NUM];
}CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU
 结构说明  : 输出到SDT的prl源类型
 1.日    期   : 2014年10月22日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    CNAS_XSD_PRL_SOURCE_TYPE_ENUM_UINT8 enPrlSrcType;
    VOS_UINT8                           aucReserve[3];
}CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_BUffER_MSG_INFO_STRU
 结构说明  : 输出到SDT的缓存队列信息
 1.日    期   : 2014年11月5日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                          ulFullFlg;
    CNAS_XSD_CACHE_MSG_QUEUE_STRU       stMsgQueue;
}CNAS_XSD_LOG_BUffER_MSG_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU
 结构说明  : 输出到SDT的OOC上下文消息结构体
 1.日    期   : 2015年1月14日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucWaitSearchFlag;
    VOS_UINT8                           ucCurrentPhase;
    VOS_UINT16                          usCurrentTimes;
    VOS_UINT8                           ucDoTrafficFlag;
    VOS_UINT8                           ucFirstFourAcqArrivedFlag;
    VOS_UINT8                           ucAttemptTimesInDoTraffic;
    VOS_UINT8                           ucSceneSetFlag;
}CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_CFG_STRU
 结构说明  : 输出到SDT的ucHomeSidNidMostPriFlg
 1.日    期   : 2015年7月3日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucHomeSidNidMostPriFlg;
    VOS_UINT8                           aucReserved[3];
}CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_OPER_LOCK_WHITE_SID_LIST_STRU
 结构说明  : 输出到SDT的OPER LOCK WHITE SID LIST
 1.日    期   : 2015年7月3日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucEnable;                          /* 白名单是否使能 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usWhiteSysNum;
    CNAS_CCB_SYS_INFO_STRU              astSysInfo[CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM];
}CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU
 结构说明  : 输出到SDT的CTCC自定义频点列表
 1.日    期   : 2015年7月3日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT8                           ucEnableFlg;
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usFreqNum;
    CNAS_CCB_FREQENCY_CHANNEL_STRU      astFreqList[CNAS_CCB_MAX_FREQ_NUM];
}CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU
 结构说明  : 输出到SDT的GEO list搜索状态信息
 1.日    期   : 2015年7月10日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;            /* _H2ASN_Skip */
    VOS_UINT16                                              usGeoNum;       /* GEO数目 */
    VOS_UINT16                                              usReserved;
    CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU                      astGeoSrchInfo[CNAS_XSD_MAX_LOG_SYSTEM_NUM_IN_ACQ_LIST]; /* 指向GEO搜索信息首地址 */
}CNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU
 结构说明  : 输出到SDT的CDMA标准频段信息
 1.日    期   : 2015年7月10日
   作    者   : y00245242
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    					enMsgId;            /* _H2ASN_Skip */
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                    stCdmaStandardChan; /* cdma标准频段信息 */
}CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_CALLBACK_CFG_STRU
 结构说明  : 输出到SDT紧急呼CallBack模式Nv配置信息
 1.日    期   : 2015年7月10日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    					enMsgId;            /* _H2ASN_Skip */
    CNAS_XSD_CALLBACK_CFG_STRU                              stCallBackCfg;      /* 紧急呼CallBack相关配置信息 */
} CNAS_XSD_LOG_CALLBACK_CFG_STRU;


/*****************************************************************************
 结构名    : CNAS_XSD_LOG_CALLBACK_STATUS_STRU
 结构说明  : 输出到SDT紧急呼CallBack模式进入和退出的消息
 1.日    期   : 2015年7月10日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_Skip */
} CNAS_XSD_LOG_CALLBACK_STATUS_STRU;

/*****************************************************************************
 结构名    : CNAS_XSD_LOG_CDMA_1X_PREF_CHANNELS_STRU
 结构说明  : 输出到SDT CDMA优选频点信息
 1.日    期   : 2015年7月10日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    					enMsgId;            /* _H2ASN_Skip */
    CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU              stCdma1XPrefChannels;
} CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU;

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
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CNAS_XSD_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_XSD_MNTN_MSG_DATA              stMsgData;
}CNAS_XSD_MNTN_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CNAS_XSD_LogScanChannelList(
    VOS_UINT32                          ulMsgName,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_LogAcqSystemList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_LogAvailSystemList(
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList
);

VOS_VOID CNAS_XSD_LogMruList(
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
);

VOS_VOID CNAS_XSD_LogAvoidFreqList(
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList
);

VOS_VOID CNAS_XSD_LogPrlSourceType(
    CNAS_XSD_PRL_SOURCE_TYPE_ENUM_UINT8 enPrlSrcType
);

VOS_VOID  CNAS_XSD_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

VOS_VOID CNAS_XSD_LogUeSupportedBandClass(
    VOS_UINT32                          ulBandClass
);


VOS_VOID CNAS_XSD_LogHomeSidNidList(
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList
);

VOS_VOID CNAS_XSD_LogOocScheduleInfo(
    CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU                 *pstOocTimerScheduleInfo
);

VOS_VOID CNAS_XSD_LogOocCtxInfo(
    CNAS_XSD_OOC_CTX_INFO_STRU         *pstOocCtxInfo
);

VOS_VOID CNAS_XSD_LogHomeSidNidDependOnPrlFlg(
    VOS_UINT8                           ucFlg
);

VOS_VOID CNAS_XSD_LogOperLockSysWhiteList(
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstMsg
);

VOS_VOID CNAS_XSD_LogCTCCCustomizeFreqList(
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstMsg
);

VOS_VOID CNAS_XSD_LogGeoListSrchStatus(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU    *pstGeoSrchStatus
);

VOS_VOID CNAS_XSD_LogCdmaStandardChannels(
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan
);

VOS_VOID CNAS_XSD_LogCallBackConfig(
    CNAS_XSD_CALLBACK_CFG_STRU                             *pstCallBackCfg
);

VOS_VOID CNAS_XSD_LogCallBackStatusInd(
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32                        enMsgId
);

VOS_VOID CNAS_XSD_LogCdma1XCustomPrefChannels(
    CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU             *pstCdma1XPrefChannels
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

#endif /* end of CnasXsdMntn.h */

