/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasPrlApi.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年8月2日
  最近修改   :
  功能描述   : CnasPrlApi.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年8月2日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_PRL_API_H__
#define __CNAS_PRL_API_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasPrlParse.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CNAS_PRL_PUBLIC_NETWORK_NID                         (0)

#define CNAS_PRL_SID_OPER_0                                 (15904)
#define CNAS_PRL_SID_OPER_1                                 (15905)

#define CNAS_PRL_MAX_MATCHING_GEO_NUM                       (32)                /* 同时匹配GEO列表的最大处理个数 */

#define CNAS_HSD_MAX_MATCHED_GEO_NUM                        (8)

#define CNAS_HSD_MAX_MATCH_LVL_SYS_REC_INDEX_NUM            (4)

#define CNAS_PRL_CDMA_CHANNEL_RANGE_1                       (1)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_239                     (239)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_359                     (359)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_400                     (400)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_539                     (539)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_599                     (599)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_699                     (699)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_799                     (799)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_801                     (801)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_871                     (871)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_899                     (899)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_919                     (919)   
#define CNAS_PRL_CDMA_CHANNEL_RANGE_991                     (991)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1000                    (1000)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1039                    (1039)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1041                    (1041)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1199                    (1199)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1201                    (1201)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1299                    (1299)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1323                    (1323)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1329                    (1329)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1399                    (1399)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1473                    (1473)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1499                    (1499)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1536                    (1536) 
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1600                    (1600)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1715                    (1715)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_1792                    (1792)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_2016                    (2016)
#define CNAS_PRL_CDMA_CHANNEL_RANGE_2047                    (2047)

#define CNAS_PRL_BAND_CLASS_TYPE_MAX                        (16)


#define CNAS_PRL_MAX_MATCHED_SYSTEM_NUM                     (10)

#define CNAS_PRL_MAX_MATCHED_HRPD_SYSTEM_NUM                (16)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM
 结构说明  : 用于标记在一条ACQ REC里面，是否已经转换过一次的标记
 1.日    期   : 2014年8月14日
   作    者   : h00246512
   修改内容   : 新建

*****************************************************************************/
enum CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM
{
    CNAS_PRL_MAP_PCS_BLOCK_NULL_FLG                         = 0x0,
    CNAS_PRL_MAP_PCS_BLOCK_A_FLG                            = 0x1,
    CNAS_PRL_MAP_PCS_BLOCK_B_FLG                            = 0x2,
    CNAS_PRL_MAP_PCS_BLOCK_C_FLG                            = 0x4,
    CNAS_PRL_MAP_PCS_BLOCK_D_FLG                            = 0x8,
    CNAS_PRL_MAP_PCS_BLOCK_E_FLG                            = 0x10,
    CNAS_PRL_MAP_PCS_BLOCK_F_FLG                            = 0x20,
    CNAS_PRL_MAP_PCS_BLOCK_ANY_FLG                          = 0xFF,
    CNAS_PRL_MAP_PCS_BLOCK_BUTT
};
typedef VOS_UINT32 CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CNAS_PRL_SID_NID_MATCH_ENUM
 结构说明  : 做SID和NID匹配时，匹配的程度

 1.日    期   : 2014年08月06日
   作    者   : h00246512
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SID_NID_MATCH_ENUM
{
  CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH,                                         /* 不匹配 */
  CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_SID,                                      /* 被匹配的SID是通配SID，值为0 */
  CNAS_PRL_SID_NID_MATCH_LVL_WILDCARD_NID,                                      /* 被匹配的NID是通配NID，值为65535 */
  CNAS_PRL_SID_NID_MATCH_LVL_SID_NID,                                           /* SID和NID是整个匹配的 */
  CNAS_PRL_SID_NID_MATCH_LVL_BUTT
} ;
typedef VOS_UINT16 CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CNAS_PRL_BAND_CHANNEL_MATCH_ENUM
 结构说明  : Band与channel match类型

 1.日    期   : 2014年12月31日
   作    者   : y00245242
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM
{
  CNAS_PRL_BAND_CHANNEL_NOT_MATCH,                                              /* 不匹配 */
  CNAS_PRL_BAND_MATCH,                                                          /* 仅BAND匹配 */
  CNAS_PRL_BAND_CHANNEL_MATCH,                                                  /* BAND与channel都匹配 */

  CNAS_PRL_BAND_CHANNEL_MATCH_BUTT
} ;
typedef VOS_UINT8 CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM
 结构说明  : 1X系统在GEO中的匹配优先级枚举

 1.日    期   : 2015年4月08日
   作    者   : w00176964
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM
{
    CNAS_PRL_1X_MATCH_PRIO_LEVLE_NULL = 0,                                                 /* not in current GEO */
    CNAS_PRL_1X_MATCH_PRIO_LEVLE_0,                                                        /* most prefered system in current GEO */
    CNAS_PRL_1X_MATCH_PRIO_LEVLE_1,                                                        /* second prefered system in current GEO */
    CNAS_PRL_1X_MATCH_PRIO_LEVLE_OTHER,                                                    /* third or next prefered system in current GEO */

    /* 后边的Level不一一列举 */

    CNAS_PRL_1X_MATCH_PRIO_LEVLE_BUTT = 100
} ;
typedef VOS_UINT8 CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_PRL_PRIO_LVL_ENUM
 结构说明  : SubNet匹配的程度枚举

 1.日    期   : 2014年12月09日
   作    者   : d00212987
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_PRIO_LVL_ENUM
{
    CNAS_PRL_PRIO_LEVEL_0 = 0,                                                    /* Level 0 MRU */
    CNAS_PRL_PRIO_LEVEL_1,                                                        /* Level 1  */
    CNAS_PRL_PRIO_LEVEL_2,                                                        /* Level 2  */
    CNAS_PRL_PRIO_LEVEL_3,                                                        /* Level 3  */
    CNAS_PRL_PRIO_LEVEL_4,                                                        /* Level 4  */
    CNAS_PRL_PRIO_LEVEL_5,                                                        /* Level 5  */

    /* 后边的Level不一一列举 */

    CNAS_PRL_PRIO_LEVEL_BUTT = 100
} ;
typedef VOS_UINT8 CNAS_PRL_PRIO_LVL_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_CHECK_ASSN_INCL_ENUM
 结构说明  : 检查ASSN INCL枚举

 1.日    期   : 2014年12月09日
   作    者   : d00212987
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_CHECK_ASSN_INCL_ENUM
{
    CNAS_PRL_CHECK_ASSN_INCL = 0,                                       /* 需检查ASSN INCL */
    CNAS_PRL_NO_CHECK_ASSN_INCL,                                        /* 不需检查ASSN INCL */

    CNAS_PRL_CHECK_ASSN_INCL_BUTT
} ;
typedef VOS_UINT16 CNAS_PRL_CHECK_ASSN_INCL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CNAS_PRL_SORT_ENUM
 结构说明  : 排序枚举

 1.日    期   : 2014年12月09日
   作    者   : d00212987
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SORT_ENUM
{
    CNAS_PRL_SORT_NEEDED     = 0,                                            /* 需要排序 */
    CNAS_PRL_SORT_NOT_NEEDED,                                            /* 不需要排序*/

    CNAS_PRL_SORT_BUTT
} ;
typedef VOS_UINT16 CNAS_PRL_SORT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CNAS_PRL_SUBNET_MATCH_LVL_ENUM
 结构说明  : SubNet匹配的程度枚举

 1.日    期   : 2014年12月09日
   作    者   : d00212987
   修改内容   : 新增
 2.日    期   : 2015年12月30日
   作    者   : z00316370
   修改内容   : 增加通配情况下频点匹配等级

*****************************************************************************/
enum CNAS_PRL_SUBNET_MATCH_LVL_ENUM
{
    CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH = 0,                                      /* 不匹配 */
    CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD,                                           /* SUBNET通配 */
    CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND,                                      /* SUBNET通配band匹配 */
    CNAS_PRL_SUBNET_MATCH_LVL_WILDCARD_BAND_CHANNEL,                              /* SUBNET通配band匹配channel匹配 */
    CNAS_PRL_SUBNET_MATCH_LVL_SUBNET,                                             /* SUBNET匹配 */
    CNAS_PRL_SUBNET_MATCH_LVL_BUTT
} ;
typedef VOS_UINT16 CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CNAS_HSD_FREQ_TYPE_INDICATION_ENUM
 结构说明  : 频点是否是MRU

 1.日    期   : 2014年12月10日
   作    者   : j00304117
   修改内容   : 新增

*****************************************************************************/
enum CNAS_HSD_FREQ_TYPE_INDICATION_ENUM
{
    CNAS_HSD_FREQ_TYPE_MRU,
    CNAS_HSD_FREQ_TYPE_OTHER,
    CNAS_HSD_FREQ_TYPE_REDIRECTION,
    CNAS_HSD_FREQ_TYPE_BUTT
};
typedef VOS_UINT8 CNAS_HSD_FREQ_TYPE_INDICATION_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_SPREADING_RATE_ENUM
 结构说明  : 做SID和NID匹配时，匹配的程度

 1.日    期   : 2014年08月06日
   作    者   : h00246512
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SPREADING_RATE_ENUM
{
    CNAS_SPREADING_RATE_1,
    CNAS_SPREADING_RATE_3,
    CNAS_SPREADING_RATE_BUTT
};
typedef VOS_UINT8 CNAS_PRL_SPREADING_RATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_WILDCARD_TYPE_ENUM
 结构说明  : 通配符类型

 1.日    期   : 2014年08月15日
   作    者   : h00246512
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_WILDCARD_TYPE_ENUM
{
  CNAS_PRL_WILDCARD_TYPE_NOT_WILDCARD,          /* 非通配符 */
  CNAS_PRL_WILDCARD_TYPE_SID,                   /* SID是通配符 */
  CNAS_PRL_WILDCARD_TYPE_NID,                   /* NID是通配符 */
  CNAS_PRL_WILDCARD_TYPE_UNKNOWN,               /* 未知的通配符 */
  CNAS_PRL_WILDCARD_TYPE_BUTT
} ;
typedef VOS_UINT8 CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CNAS_PRL_SYS_PRI_TYPE_ENUM
 结构说明  : 系统优先级类型

 1.日    期   : 2014年11月28日
   作    者   : c00299063
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_SYS_PRI_TYPE_ENUM
{
    CNAS_PRL_SYS_PRI_HIGH,
    CNAS_PRL_SYS_PRI_SAME,
    CNAS_PRL_SYS_PRI_LOW,
    CNAS_PRL_SYS_PRI_UNKNOWN,
    CNAS_PRL_SYS_PRI_BUTT
};

typedef VOS_UINT32 CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : CNAS_PRL_BAND_CHANNEL_MATCH_CMP_ENUM
 结构说明  : 系统优先级类型

 1.日    期   : 2015年6月8日
   作    者   : c00299063
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_BAND_CHANNEL_MATCH_CMP_ENUM
{
    CNAS_PRL_BAND_CHANNEL_MATCH_CMP_FIR_RECORD_HIGH,
    CNAS_PRL_BAND_CHANNEL_MATCH_CMP_SEC_RECORD_HIGH,
    CNAS_PRL_BAND_CHANNEL_MATCH_CMP_TWO_RECORD_SAME,
    CNAS_PRL_BAND_CHANNEL_MATCH_CMP_UNKNOWN,
    CNAS_PRL_BAND_CHANNEL_MATCH_CMP_BUTT
};

typedef VOS_UINT8 CNAS_PRL_BAND_CHANNEL_MATCH_CMP_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_PRL_INCLUDE_RELATION_ENUM
 结构说明  : 系统优先级类型

 1.日    期   : 2015年6月8日
   作    者   : c00299063
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_ENUM
{
    CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_FIR_INCLUDE_SEC,
    CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SEC_INCLUDE_FIR,
    CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_SAME,
    CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_NOT_INCLUDE,
    CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_BUTT
};

typedef VOS_UINT8 CNAS_PRL_ACQ_RECORD_INCLUDE_RELATION_ENUM_UINT8;


/*****************************************************************************
 枚举名    : CNAS_PRL_CUSTOM_MATCH_LVL_ENUM
 结构说明  : 自定义匹配模式

 1.日    期   : 2015年12月3日
   作    者   : w00242748
   修改内容   : 新增

*****************************************************************************/
enum CNAS_PRL_CUSTOM_MATCH_LVL_ENUM
{
    CNAS_PRL_CUSTOM_MATCH_LVL_NOT_MATCH,                                         /* 不匹配 */
    CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_SID_EXCEPT_CHANNEL,
    CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_SID,                                      /* 被匹配的SID是通配SID，值为0 */
    CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_NID,                                      /* 被匹配的NID是通配NID，值为65535 */
    CNAS_PRL_CUSTOM_MATCH_LVL_SID_NID,                                           /* SID和NID是整个匹配的 */
    CNAS_PRL_CUSTOM_MATCH_LVL_BUTT
} ;
typedef VOS_UINT16 CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16;

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
 结构名    : CNAS_MAP_BAND_CHANNEL_INFO_STRU
 结构说明  : 根据捕获表获取的频段和频点信息
   1.日    期   : 2013年8月6日
    作    者   : h00246512
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqInfo[CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM];
}CNAS_PRL_ACQ_REC_FREQ_INFO_STRU;


/*****************************************************************************
 结构名    : CNAS_SUITED_GEO_INFO_STRU
 结构说明  : 系统表中匹配的GEO信息
 1.日    期   : 2014年8月08日
   作    者   : h00246512
   修改内容   : 新增
 2.日    期   : 2015年7月7日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;             /* SID和NID的匹配等级 */
    VOS_UINT16                                              usGeoFirstSysRecIndex;  /* 相匹配的GEO中的第一个系统记录在系统表中的位置 */
    VOS_UINT16                                              usGeoSysRecNum;         /* 相匹配的GEO中的系统记录个数 */
    VOS_UINT16                                              usMostMatchedIndex;
}CNAS_PRL_MATCHED_GEO_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_MATCHING_GEO_LIST_STRU
 结构说明  : 系统表中匹配的GEO列表信息
 1.日    期   : 2014年8月08日
   作    者   : h00246512
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;                                        /* 待匹配的SID */
    VOS_UINT16                                              usNid;                                        /* 待匹配的SID */
    VOS_UINT8                                               ucGeoNum;                                     /* 匹配的GEO列表个数 */
    VOS_UINT8                                               aucReserved[3];
    CNAS_PRL_MATCHED_GEO_INFO_STRU                          astGeoInfoList[CNAS_PRL_MAX_MATCHING_GEO_NUM];    /* 匹配的GEO信息 */
}CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_HSD_DRPD_MOST_MATCHED_GEO_INFO
 结构说明  : 在所有匹配1x系统GEO中查找最匹配的GEO
   1.日    期   : 2013年12月11日
    作    者   : j00304117
    修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8               ucNumOfMostMatchGeo;
    VOS_UINT8               aucIndexInGeoList[CNAS_HSD_MAX_MATCHED_GEO_NUM];
}CNAS_HSD_DRPD_MOST_MATCHED_GEO_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_MATCHED_1X_GEO_INFO_EX_STRU
 结构说明  : 系统表中匹配的GEO信息
 1.日    期   : 2014年12月09日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;             /* SID和NID的匹配等级 */
    VOS_UINT16                                              usGeoFirstSysRecIndex;  /* 相匹配的GEO中的第一个系统记录在系统表中的位置 */
    VOS_UINT16                                              usGeoSysRecNum;         /* 相匹配的GEO中的系统记录个数 */
    VOS_UINT16                                              us1xSysIndexNum;        /* 相匹配的1x index个数 */
    VOS_UINT16                                              aus1xSysIndex[CNAS_HSD_MAX_MATCH_LVL_SYS_REC_INDEX_NUM];
}CNAS_PRL_MATCHED_1X_GEO_INFO_EX_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_MATCHED_1X_GEO_LIST_INFO_EX_STRU
 结构说明  : 系统表中匹配的GEO列表信息
 1.日    期   : 2014年12月09日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;                                        /* 待匹配的SID */
    VOS_UINT16                                              usNid;                                        /* 待匹配的SID */
    VOS_UINT8                                               ucGeoNum;                                     /* 匹配的GEO列表个数 */
    VOS_UINT8                                               aucReserved[3];
    CNAS_PRL_MATCHED_1X_GEO_INFO_EX_STRU                    ast1xGeoInfoListEx[CNAS_PRL_MAX_MATCHING_GEO_NUM];/* 匹配的GEO信息 */
}CNAS_PRL_MATCHED_1X_GEO_LIST_INFO_EX_STRU;

/*****************************************************************************
 结构名    : CNAS_SUITED_GEO_INFO_STRU
 结构说明  : 系统表中的GEO信息
 1.日    期   : 2015年7月7日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usGeoFirstSysRecIndex;  /* 相匹配的GEO中的第一个系统记录在系统表中的位置 */
    VOS_UINT8                                               aucReserved[2];
}CNAS_PRL_GEO_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_MATCHING_GEO_LIST_STRU
 结构说明  : 系统表中的GEO列表信息
 1.日    期   : 2015年7月7日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usGeoNum;  /* GEO列表个数 */
    VOS_UINT8                                               aucReserved[2];
    CNAS_PRL_GEO_INFO_STRU                                 *pstGeoInfoList;    /* GEO信息仅包含GEO的第一条记录索引 */
}CNAS_PRL_GEO_LIST_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_PRL_MATCHED_INDEX_LIST_STRU
 结构说明  : 匹配的索引列表
 2.日    期   : 2015年12月4日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usMatchedIndexNum;
    VOS_UINT16                                              usReserved;
    VOS_UINT16                                              ausMostMatchedIndex[CNAS_PRL_MAX_MATCHED_SYSTEM_NUM];
}CNAS_PRL_MATCHED_INDEX_LIST_STRU;

/*****************************************************************************
 结构名    : CNAS_SUITED_GEO_INFO_STRU
 结构说明  : 系统表中匹配的GEO信息
 2.日    期   : 2015年7月7日
   作    者   : w00242748
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enGeoMostMatchLvl;          /* SID和NID的匹配等级 */
    VOS_UINT16                                              usReserved;
    VOS_UINT16                                              usGeoFirstSysRecIndex;  /* 相匹配的GEO中的第一个系统记录在系统表中的位置 */
    VOS_UINT16                                              usGeoSysRecNum;         /* 相匹配的GEO中的系统记录个数 */
    CNAS_PRL_MATCHED_INDEX_LIST_STRU                        astIndexList[CNAS_PRL_CUSTOM_MATCH_LVL_BUTT];
}CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU;

/*****************************************************************************
 结构名    : CNAS_MATCHING_GEO_LIST_STRU
 结构说明  : 系统表中匹配的GEO列表信息
 1.日    期   : 2014年8月08日
   作    者   : h00246512
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usSid;                                        /* 待匹配的SID */
    VOS_UINT16                                              usNid;                                        /* 待匹配的SID */
    VOS_UINT8                                               ucGeoNum;                                     /* 匹配的GEO列表个数 */
    VOS_UINT8                                               aucReserved[3];
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU                    astGeoInfoList[CNAS_PRL_MAX_MATCHING_GEO_NUM];    /* 匹配的GEO信息 */
}CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 CNAS_PRL_GetPrlInfoValidFlag(VOS_VOID);

VOS_UINT8 *CNAS_PRL_GetDefaultPrl(VOS_VOID);

VOS_UINT16 CNAS_PRL_GetDefaultPrlSize(VOS_VOID);

CNAS_PRL_ACQ_RECORD_INFO_STRU* CNAS_PRL_GetPrlAcqInfoAddr(VOS_VOID);

CNAS_PRL_SYS_RECORD_INFO_STRU* CNAS_PRL_GetPrlSysInfoAddr(VOS_VOID);

VOS_UINT16 CNAS_PRL_GetPrlAcqRecordNum(VOS_VOID);

CNAS_PRL_HEADER_INFO_STRU* CNAS_PRL_GetPrlHeaderInfoAddr(VOS_VOID);

CNAS_PRL_SSPR_P_REV_ENUM_UINT8 CNAS_PRL_GetPrlRevInfo(VOS_VOID);
VOS_VOID CNAS_PRL_SetPrlRevInfo(
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev
);

VOS_UINT16 CNAS_PRL_GetPrlSysRecordNum(VOS_VOID);

CNAS_PRL_ACQ_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlAcqRecord(VOS_UINT16 usIndex);

CNAS_PRL_EXT_SYS_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlSysRecord(VOS_UINT16 usIndex);

VOS_VOID CNAS_PRL_InitPrlAcqInfo(
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstPrlAcqInfo
);

VOS_VOID CNAS_PRL_InitPrlHeaderInfo(
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeader
);

VOS_VOID CNAS_PRL_InitPrlInfo(VOS_UINT32 ulTaskInitFlag);

VOS_VOID CNAS_PRL_InitPrlSysInfo(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo,
    VOS_UINT32                          ulTaskInitFlag
);

VOS_VOID CNAS_PRL_InitPrlCtx(VOS_UINT32 ulTaskInitFlag);

VOS_UINT32 CNAS_PRL_ProcPrlInfo(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
);

VOS_VOID CNAS_PRL_BuildGeoSysRecList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    VOS_UINT8                                               ucIgnoreNegSys,
    VOS_UINT16                                             *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord
);


VOS_UINT16 CNAS_PRL_CalcPrlAcqRecTotalFreqNum(VOS_VOID);
VOS_UINT16 CNAS_PRL_CalcPrlSysRecListTotalFreqNum(
    VOS_UINT16                          usSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_OnlySidNidBandMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);
CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_OnlySidNidMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);
CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetMatchLvl_SidNidBandChannelMatch(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

VOS_UINT8 CNAS_PRL_GetPrefOnlyFlg(VOS_VOID);
CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8 CNAS_PRL_GetPrl1xIs95SysRecordWildCardType(
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);
VOS_VOID CNAS_PRL_GetPrlAcqRecFreqListInfo(
    CNAS_PRL_ACQ_RECORD_STRU                               *pstPrlAcqRec,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);

CNAS_PRL_WILDCARD_TYPE_ENUM_UINT8 CNAS_PRL_GetPrlSysRecordWildCardType(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

VOS_VOID CNAS_PRL_Get1xSysGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
);

VOS_UINT32 CNAS_PRL_Is1xSysNegativeInPrl(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
);

VOS_UINT32 CNAS_PRL_IsSidNidMatch_1XIS95(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);


CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_Get1xSysMatchSysRecordLvl(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);
VOS_VOID CNAS_PRL_MapCellularCdmaCustomToBandChannel(
    CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_CUSTOM_RECORD_STRU      *pstCelluarCustomSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapCellularCdmaPreferToBandChannel(
    CNAS_PRL_CELLUAR_CDMA_PREFERRED_SYS_ACQ_RECORD_STRU    *pstCellularPreSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapCellularCdmaStandardSysAToBandChannel(
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanSelType,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapCellularCdmaStandardSysBToBandChannel(
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enChanSelType,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapCellularCdmaStandardToBandChannel(
    CNAS_PRL_CELLULAR_CDMA_SYS_ACQ_STANDARD_RECORD_STRU    *pstCellularStandardSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsBlockAnyToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsBlockAToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsBlockBToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsBlockCToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsBlockDToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsBlockEToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsBlockFToBandChannel(
    CNAS_PRL_SPREADING_RATE_ENUM_UINT8                      enSpreadingRate,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsCdmaBlockToBandChannel(
    CNAS_PRL_PCS_CDMA_SYS_ACQ_BLOCKS_RECORD_STRU           *pstPcsBlocksSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapPcsCdmaChannelToBandChannel(
    CNAS_PRL_PCS_CDMA_SYS_ACQ_CHANNELS_STRU                *pstPcsChannelsSys,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                        *pstFreqInfo
);
VOS_VOID CNAS_PRL_MapStandardBand0SubClassToChannel(
    CNAS_PRL_BAND_SUBCLASS_TYPE_ENUM_UINT8                  enBandSubClass,
    CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8                        enSysSelType,
    CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8              enStandChanSelType,
    VOS_UINT16                                             *pusChannel
);

VOS_UINT32 CNAS_PRL_IsMostPref1xSysInGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
);

VOS_UINT32 CNAS_PRL_Is1xSysIdMatched(
    VOS_UINT16                          usSrcSid,
    VOS_UINT16                          usSrcNid,
    VOS_UINT16                          usDstSid,
    VOS_UINT16                          usDstNid
);

VOS_UINT32 CNAS_PRL_Is1xSysIdInSysIdList(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstSrcSysId,
    VOS_UINT16                          usDtsSysIdNum,
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstDstSysIdInfo
);


VOS_UINT32 CNAS_PRL_Is1xSysMatched(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSrcSys,
    CNAS_PRL_1X_SYSTEM_STRU            *pstDstSys
);

CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32  CNAS_PRL_CmpSysPriorityofTwoSystemsInSameGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMatchedGeoInfo
);

CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 CNAS_PRL_GetRoamingIndInMatchedGeolist(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
);

CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16 CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeoInfo,
    VOS_UINT16                         *pusIndex
);

#if 0
VOS_UINT16 CNAS_PRL_GetAcqRecIndexAccordingToSysRecIndex(
    VOS_UINT16                          usSysRecIndex
);
#endif

VOS_UINT32 CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                    *penRoamingInd
);

CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareRoamingIndicatorPreferenceOfTwoSystems(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstCurSysGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstOrigSysGeoListInfo
);

CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareChannelPreferenceOfTwoSystems(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU            *pstOrigSysInfo
);

CNAS_PRL_MATCHED_GEO_INFO_STRU *CNAS_PRL_GetTheSameGeoInfoOfTwoGeoList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstCurSysGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstOrigSysGeoListInfo
);

CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32 CNAS_PRL_CompareSystemPreference(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    CNAS_PRL_1X_SYSTEM_STRU            *pstOrigSysInfo
);

CNAS_PRL_MAP_PCS_BLOCK_FLG_ENUM_UINT32 CNAS_PRL_TransBlockTypeToBlockTypeFlag(
    CNAS_PRL_PCS_CDMA_FREQUENCY_BLOCK_ENUM_UINT8           enBlockType
);

VOS_UINT16 CNAS_PRL_CalcMatchedGeoListTotalFreqNum(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
);


CNAS_PRL_MATCHED_GEO_INFO_STRU *CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
);

VOS_VOID CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMostMatchGeoListInfo
);

CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_GetCurSysBandChannelMatchTypeInAcqRecord(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord
);


VOS_UINT8 CNAS_PRL_IsCurrentSystemInHomeSidNidList(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
);


CNAS_PRL_ACQ_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlValidAcqRecord(VOS_UINT16 usIndex);

CNAS_PRL_EXT_SYS_RECORD_STRU *CNAS_PRL_GetSpecifiedPrlValidSysRecord(VOS_UINT16 usIndex);

CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_IsHrpdFreqMatched(
    VOS_UINT16                          usAcqIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

VOS_UINT32 CNAS_PRL_CmpFreqValue(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSrcFreq,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstFreq
);

VOS_UINT32 CNAS_PRL_CmpSubnetValue(
    VOS_UINT8                          *pucSrcSubnet,
    VOS_UINT8                          *pucDstSubnet,
    VOS_UINT32                          ulCmpLen
);

CNAS_PRL_EXT_SYS_RECORD_STRU* CNAS_PRL_GetHrpdSysRecByIndex(VOS_UINT16 usIndex);

CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_IsHrpdSubnetMatched(
    VOS_UINT8                          *pucOTASubnetid,
    VOS_UINT8                           ucOTASubnetidBitSize,
    VOS_UINT8                          *pucSysRecSubnetid,
    VOS_UINT8                           ucSysRecSubnetidBitSize
);

CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

VOS_VOID CNAS_PRL_Get1xSysGeoListEx(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_1X_GEO_LIST_INFO_EX_STRU              *pst1xGeoListEx
);

CNAS_PRL_BAND_CHANNEL_MATCH_TYPE_ENUM_UINT8 CNAS_PRL_GetBandChanMatchInfoOfGeoSys(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstGeoInfo
);

VOS_UINT32 CNAS_PRL_IsSidNidMatch_MccMncBased(
    CNAS_PRL_1X_SYSTEM_STRU            *pstSysInfo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);
CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU const *CNAS_PRL_GetBand0PrefChanTab(VOS_VOID);

CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU const *CNAS_PRL_GetBand10PrefChanTab(VOS_VOID);

VOS_UINT32 CNAS_PRL_GetBand0PrefChanTabSize(VOS_VOID);

VOS_UINT32 CNAS_PRL_GetBand10PrefChanTabSize(VOS_VOID);


VOS_UINT8 CNAS_PRL_Is1xSysRecord(
    CNAS_PRL_EXT_SYS_RECORD_STRU                            *pstSysRecord
);
VOS_UINT32 CNAS_PRL_IsHrpdSysRec(
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl_IS856(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16 CNAS_PRL_GetHrpdSysRecMatchLvl_MccMncBased(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
);

VOS_VOID CNAS_PRL_FreeMccRec(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo
);

VOS_VOID CNAS_PRL_GetMostMultiMatched1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstMostMatchGeoListInfo
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

#endif /* end of __CNAS_PRL_API_H__ */
