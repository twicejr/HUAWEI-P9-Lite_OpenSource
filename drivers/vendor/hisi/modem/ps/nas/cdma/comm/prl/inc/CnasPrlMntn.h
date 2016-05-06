/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasPrlMntn.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年8月2日
  最近修改   :
  功能描述   : PRL参数定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年8月2日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_PRL_MNTN_H__
#define __CNAS_PRL_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasMntn.h"
#include  "CnasPrlParse.h"
#include  "CnasPrlApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     CNAS_PRL_MNTN_MAX_SYS_REC_NUM                   (10)

#define     CNAS_PRL_MNTN_MAX_ACQ_REC_NUM                   (10)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : CNAS_PRL_MNTN_MSG_ID_ENUM
 结构说明  : CNAS PRL可维可测消息ID
  1.日    期   : 2014年08月18日
    作    者   : y00245242
    修改内容   : 新增
*****************************************************************************/
enum CNAS_PRL_MNTN_MSG_ID_ENUM
{
    ID_CNAS_PRL_MNTN_HEADER_INFO_IND    = ID_CNAS_MNTN_PRL_MSG_BASE, /*_H2ASN_MsgChoice  CNAS_PRL_MNTN_HEADER_INFO_IND_STRU */

    ID_CNAS_PRL_MNTN_ACQ_RECORD_INFO_IND,                            /*_H2ASN_MsgChoice  CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU */

    ID_CNAS_PRL_MNTN_SYS_RECORD_INFO_IND,                            /*_H2ASN_MsgChoice  CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU */

    ID_CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_IND,                     /*_H2ASN_MsgChoice  CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU */

    ID_CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_IND,                /*_H2ASN_MsgChoice  CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU */

    ID_CNAS_PRL_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32;

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
 结构名    : CNAS_PRL_CDMA_SYS_ACQ_CHANNEL_RECORD_STRU
 结构说明  : PRL捕获记录channel数据结构

  1.日    期   : 2014年08月18日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfChans;   /* channel个数 */
    VOS_UINT8                           aucResvered[3];

    VOS_UINT16                          ausChan[CNAS_PRL_ACQ_CUSTOM_CHAN_RECORD_MAX_NUM];        /* 存放channel首地址 */
}CNAS_PRL_CDMA_SYS_ACQ_CHANNEL_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_TRACE_STRU
 结构说明  : PCS CDMA System Acquisition (Using Blocks) Record数据结构
             (见3GPP2 C.S0016-D 3.5.5.2.1.5)，用于TRACE使用

  1.日    期   : 2014年08月18日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfBlocks;   /* block数目 */
    VOS_UINT8                                               aucResvered[3];

    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM_UINT8            aenBlock[CNAS_PRL_ACQ_BLOCK_RECORD_MAX_NUM];        /* block指针 */

}CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_TRACE_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_GENERIC_ACQ_FOR_1X_AND_IS95_TRACE_STRU
 结构说明  : Generic Acquisition Record for cdma2000 1x and IS-95
             Record数据结构(见3GPP2 C.S0016-D 3.5.5.2.2.10), 为trace使用
  1.日    期   : 2014年08月18日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfChans;
    VOS_UINT8                                               aucReseved[3];

    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreq[CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM];        /* band + channel */

}CNAS_PRL_GENERIC_ACQ_FOR_1X_AND_IS95_TRACE_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_GENERIC_ACQ_FOR_HRPD_TRACE_STRU
 结构说明  : Generic Acquisition Record for HRPD

  1.日    期   : 2015年06月08日
    作    者   : z00316370
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfChans;
    VOS_UINT8                                               aucReseved[3];
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreq[CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM];        /* band + channel */
}CNAS_PRL_GENERIC_ACQ_FOR_HRPD_TRACE_STRU;


/*****************************************************************************
 结构名    : CNAS_PRL_ACQ_RECORD_TRACE_STRU
 结构说明  : PRL捕获记录(acquire record)数据结构, 该结构用于trace捕获记录使用
  1.日    期   : 2014年08月18日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8                                enAcqType;
    VOS_UINT8                                                   ucAcqValid;      /* 标识该条acq记录是否有效。
                                                                                    ucAcqValid = 1 有效
                                                                                    ucAcqValid = 0 无效 */
    VOS_UINT8                                                   aucResvered[2];

    union
    {
        CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU     stCellularStandardSys;
        CNAS_PRL_CDMA_SYS_ACQ_CHANNEL_RECORD_STRU               stCelluarCustomSys;
        CNAS_PRL_JTACS_CDMA_SYS_ACQ_STANDARD_RECORD_STRU        stJtacsStandardSys;
        CNAS_PRL_CDMA_SYS_ACQ_CHANNEL_RECORD_STRU               stJtacsCustomSys;
        CNAS_PRL_CELLUAR_CDMA_PREFERRED_SYS_ACQ_RECORD_STRU     stCellularPreSys;
        CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_TRACE_STRU      stPcsBlocksSys;
        CNAS_PRL_CDMA_SYS_ACQ_CHANNEL_RECORD_STRU               stPcsChannelsSys;
        CNAS_PRL_CDMA_SYS_ACQ_CHANNEL_RECORD_STRU               st2GhzChannelSys;
        CNAS_PRL_GENERIC_ACQ_FOR_1X_AND_IS95_TRACE_STRU         st1xAndIs95Sys;
        CNAS_PRL_GENERIC_ACQ_FOR_HRPD_TRACE_STRU                stHrpdSys;
    }u;

}CNAS_PRL_MNTN_ACQ_RECORD_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_MNTN_HEADER_INFO_IND_STRU
 结构说明  : PRL可维可测头消息数据结构
  1.日    期   : 2014年08月18日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    CNAS_PRL_HEADER_INFO_STRU           stHeaderInfo;
}CNAS_PRL_MNTN_HEADER_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU
 结构说明  : PRL可维可测捕获记录数据结构
  1.日    期   : 2014年08月18日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                   /* 消息头 */    /* _H2ASN_Skip */
    CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                     /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                                  /* Module Id */
    VOS_UINT8                           ucRecNum;                                    /* 系统记录数目 */
    VOS_UINT8                           aucReserved[3];                              /* 保留位 */
    CNAS_PRL_MNTN_ACQ_RECORD_STRU       astAcqRec[CNAS_PRL_MNTN_MAX_ACQ_REC_NUM]; /* 捕获记录数据结构 */
}CNAS_PRL_MNTN_ACQ_REC_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU
 结构说明  : PRL可维可测捕获记录数据结构
  1.日    期   : 2014年08月18日
    作    者   : y00245242
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                   /* 消息头 */    /* _H2ASN_Skip */
    CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                     /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                                  /* Module Id */
    VOS_UINT8                           ucRecNum;                                    /* 系统记录数目 */
    VOS_UINT8                           aucReserved[3];                              /* 保留位 */
    CNAS_PRL_EXT_SYS_RECORD_STRU        astSysRec[CNAS_PRL_MNTN_MAX_SYS_REC_NUM]; /* 系统记录数据结构 */
}CNAS_PRL_MNTN_SYS_REC_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU
 结构说明  : 多匹配GEO信息结构
  1.日    期   : 2015年12月7日
    作    者   : w00242748
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                   /* 消息头 */    /* _H2ASN_Skip */
    CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;                                     /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                                              ulModuleId;                                  /* Module Id */
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU                    stMultiMatchedGeoInfo;
}CNAS_PRL_MNTN_MULTI_MATCHED_GEO_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU
 结构说明  : 多匹配GEO列表信息接口
  1.日    期   : 2015年12月7日
    作    者   : w00242748
    修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                   /* 消息头 */    /* _H2ASN_Skip */
    CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;                                     /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                                              ulModuleId;                                  /* Module Id */
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU               stMultiMatchedGeoListInfo;
}CNAS_PRL_MNTN_MULTI_MATCHED_GEO_LIST_INFO_STRU;


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
    CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32    enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_PRL_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CNAS_PRL_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CNAS_PRL_MNTN_MSG_DATA              stMsgData;
}CNAS_PRL_MNTN_MSG;



/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_PRL_MntnConvertAcqRecInfo(
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord,
    CNAS_PRL_MNTN_ACQ_RECORD_STRU      *pstMntnAcqRec
);
VOS_VOID CNAS_PRL_LogHeaderInfo(
    CNAS_PRL_HEADER_INFO_STRU           *pstPrlHeader
);

VOS_VOID CNAS_PRL_LogAcqRecInfo(
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqRecordInfo
);

VOS_VOID CNAS_PRL_LogSysRecInfo(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstSysRecordInfo
);

VOS_VOID CNAS_PRL_LogMultiMatchedGeoInfo(
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU                   *pstMultiMatchedGeoInfo
);

VOS_VOID CNAS_PRL_LogMultiMatchedGeoListInfo(
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstMultiMatchedGeoListInfo
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

#endif /* end of __CNAS_PRL_MNTN_H__ */
