/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbaMntn.h
  版 本 号   : 初稿
  作    者   : l00171473
  生成日期   : 2012年3月19日
  最近修改   :
  功能描述   : TafCbaMntn.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年3月19日
    作    者   : l00171473
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFCBAMNTN_H__
#define __TAFCBAMNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "TafCbaCtx.h"
#include  "TafCbaProcNvim.h"
#include  "TafMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 宏定义
*****************************************************************************/


#define TAF_CBA_MNTN_INFO_HEADER_LEN                        (24)                /* 可维可测结构的头部长度,
                                                                                   TAF_CBA_MNTN_INFO_STRU结构中不含UNION部分的长度 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_CBA_OM_MSG_ID_ENUM
 结构说明  : CBA模块可维可测消息ID枚举
 1.日    期   : 2012年3月19日
   作    者   : l00171473
   修改内容   : 新增
 2.日    期   : 2012年3月27日
   作    者   : w00176964
   修改内容   : 新增
 3.日    期   : 2012年12月07日
   作    者   : l00171473
   修改内容   : For DTS2012120600056, 添加CBS相关NV项的可维可测
 4.日    期   : 2013年8月29日
   作    者   : f62575
   修改内容   : VSIM FEATURE
*****************************************************************************/
enum TAF_CBA_OM_MSG_ID_ENUM
{
    TAF_CBA_OM_MSG_LOG_INFO                                 = ID_TAF_MNTN_MSG_CBA_BASE,            /* _H2ASN_MsgChoice TAF_CBA_LOG_INFO_STRU */ /* CBA 模块LOG INFO */

    TAF_CBA_OM_MSG_DUP_ETWS_PRIM_NTF_RECORD,                                    /* _H2ASN_MsgChoice TAF_CBA_LOG_DUP_RECORD_STRU */ /* 重复ETWS主通知记录 */
    TAF_CBA_OM_MSG_DUP_CBS_RECORD,                                              /* _H2ASN_MsgChoice TAF_CBA_LOG_DUP_RECORD_STRU */ /* 重复CBS记录 */

    TAF_CBA_OM_MSG_SAVE_ETWS_PRIM_NTF_RECORD,                                   /* _H2ASN_MsgChoice TAF_CBA_LOG_SAVE_RECORD_STRU */ /* 保存ETWS主通知记录 */
    TAF_CBA_OM_MSG_SAVE_CBS_RECORD,                                             /* _H2ASN_MsgChoice TAF_CBA_LOG_SAVE_RECORD_STRU */ /* 保存CBS记录 */

    TAF_CBA_OM_MSG_DEL_ETWS_PRIM_RECORD,                                        /* _H2ASN_MsgChoice TAF_CBA_LOG_DEL_RECORD_STRU */ /* 删除ETWS主通知记录 */
    TAF_CBA_OM_MSG_DEL_DEL_CBS_RECORD,                                          /* _H2ASN_MsgChoice TAF_CBA_LOG_DEL_RECORD_STRU */ /* 删除CBS记录 */

    TAF_CBA_OM_MSG_CBMI_DOWNLOAD_LIST,                                          /* _H2ASN_MsgChoice TAF_CBA_LOG_CBMI_DOWNLOAD_LIST_STRU */ /* CBMI DOWNLOAD list的内容 */
    TAF_CBA_OM_MSG_CBMI_RANGE_LIST,                                             /* _H2ASN_MsgChoice TAF_CBA_LOG_CBMI_RANGE_LIST_STRU */ /* CBMI RANGE List的内容 */

    TAF_CBA_OM_MSG_NVIM_INFO,                                                   /* _H2ASN_MsgChoice TAF_CBA_LOG_NVIM_INFO_STRU */ /* CBS相关NV信息 */

    TAF_CBA_OM_MSG_BUTT
};
typedef VOS_UINT32  TAF_CBA_OM_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_CBA_OM_LOG_ID_ENUM
 结构说明  : CBA模块可维可测的LOG消息枚举
 1.日    期   : 2012年3月19日
   作    者   : l00171473
   修改内容   : 新增
*****************************************************************************/
enum TAF_CBA_OM_LOG_ID_ENUM
{
    TAF_CBA_OM_LOG_RCV_PRIM_NTF_WHEN_ETWS_DISABLE,                              /* 收到ETWS主通知时 ETWS 特性关闭 */
    TAF_CBA_OM_LOG_ETWS_PRIM_NTF_MSGID_INVALID,                                 /* 主通知消息ID无效 */
    TAF_CBA_OM_LOG_CBS_MSGID_INVALID,                                           /* CBS消息ID无效 */
    TAF_CBA_OM_LOG_TICK_ERROR,                                                  /* VOS TICK不正确 */
    TAF_CBA_OM_LOG_PAGEINDEX_INVALID,                                           /* PAGEINDEX无效 */
    TAF_CBA_OM_LOG_PAGELEN_INVALID,                                             /* PAGELEN无效 */

    TAF_CBA_OM_LOG_BUTT
};
typedef VOS_UINT32  TAF_CBA_OM_LOG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_CBA_OM_DEL_REASON_ENUM
 结构说明  : CBA模块可维可测删除记录原因枚举
 1.日    期   : 2012年3月19日
   作    者   : l00171473
   修改内容   : 新增
*****************************************************************************/
enum TAF_CBA_OM_DEL_REASON_ENUM
{
    TAF_CBA_OM_DEL_REASON_LIST_FULL,                                            /* 记录表满删除记录 */
    TAF_CBA_OM_DEL_REASON_TIMEOUT,                                              /* 记录超时删除记录 */
    TAF_CBA_OM_DEL_REASON_GS_CHG,                                               /* GS变化删除记录 */
    TAF_CBA_OM_DEL_REASON_USER,                                                 /* 用户操作导致删除记录 */

    TAF_CBA_OM_DEL_REASON_BUTT
};
typedef VOS_UINT8  TAF_CBA_OM_DEL_REASON_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_CBA_OM_SAVE_TYPE_ENUM
 结构说明  : CBA模块可维可测保存记录类型
 1.日    期   : 2012年3月19日
   作    者   : l00171473
   修改内容   : 新增
*****************************************************************************/
enum TAF_CBA_OM_SAVE_TYPE_ENUM
{
    TAF_CBA_OM_SAVE_TYPE_RECORD_FULL,                                           /* CBS记录表满 */
    TAF_CBA_OM_SAVE_TYPE_APPEND_RECORD,                                         /* 追加一个CBS记录 */
    TAF_CBA_OM_SAVE_TYPE_UPDATE_RECORD_BITMAP,                                  /* 更新接收页的BITMAP */
    TAF_CBA_OM_SAVE_TYPE_REPLACE_RECORD,                                        /* 覆盖原CBS记录 */
    TAF_CBA_OM_SAVE_TYPE_BUTT
};
typedef VOS_UINT8  TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8;

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
 结构名    : TAF_CBA_LOG_INFO_STRU
 结构说明  : CBA可维可测LOG结构
 1.日    期   : 2012年3月10日
   作    者   : l00171473
   修改内容   : 新建 for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    TAF_CBA_OM_LOG_ID_ENUM_UINT32       enLogId;
}TAF_CBA_LOG_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_LOG_DUP_RECORD_STRU
 结构说明  : 重复记录项的可维可测信息
 1.日    期   : 2012年3月10日
   作    者   : l00171473
   修改内容   : 新建 for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPageBitmap;                           /* 已接收页的BitMap(G的CBS消息包含此信息) */
    VOS_UINT16                          usMsgID;                                /* 主从通知/CBS消息ID */
    VOS_UINT16                          usSN;                                   /* 主从通知/CBS序列号 */
    VOS_UINT8                           aucRsv[2];
}TAF_CBA_LOG_DUP_RECORD_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_LOG_DEL_RECORD_STRU
 结构说明  : 删除记录项的可维可测信息
 1.日    期   : 2012年3月10日
   作    者   : l00171473
   修改内容   : 新建 for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    TAF_CBA_OM_DEL_REASON_ENUM_UINT8    enDelReason;
    VOS_UINT8                           aucRsv[3];

    VOS_UINT16                          usMsgID;                                /* 主从通知/CBS消息ID */
    VOS_UINT16                          usSN;                                   /* 主从通知/CBS序列号 */
    VOS_UINT32                          ulDupDetcTimeLen;                       /* 有效时长N,单位: 秒, 为0表示一直有效 */
    VOS_UINT32                          ulRcvTimeTick;                          /* 收到消息时的时间戳, 取自 VOS_GetTick, 单位: 10 ms */
    VOS_UINT32                          ulCurrTick;
}TAF_CBA_LOG_DEL_RECORD_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_LOG_SAVE_RECORD_STRU
 结构说明  : 保存记录项的可维可测信息
 1.日    期   : 2012年3月10日
   作    者   : l00171473
   修改内容   : 新建 for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType;                             /* 保存类型 */
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          usRecordNum;                            /* 新的记录个数 */

    VOS_UINT32                          ulDupDetcTimeLen;                       /* 有效时长N,单位: 秒, 为0表示一直有效 */
}TAF_CBA_LOG_SAVE_RECORD_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_LOG_CBMI_DOWNLOAD_LIST_STRU
 结构说明  : 当前CBS CBMID List的可维可测信息
 1.日    期   : 2012年3月10日
   作    者   : l00171473
   修改内容   : 新建 for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCbmidNum;                             /* 所包含的广播id的总数量 */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT16                          ausMsgId[TAF_CBA_MAX_CBMID_NUM];        /* 具体的广播消息id */
}TAF_CBA_LOG_CBMI_DOWNLOAD_LIST_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_LOG_CBMI_RANGE_STRU
 结构说明  : CBMID RANG 信息
 1.日    期   : 2012年3月10日
   作    者   : l00171473
   修改内容   : 新建 for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /* 小区广播消息ID的开始序号  */
    VOS_UINT16                          usMsgIdTo;                              /* 小区广播消息ID的结束序号 */
}TAF_CBA_LOG_CBMI_RANGE_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_LOG_CBMI_RANGE_LIST_STRU
 结构说明  : 当前CBS CBMIR List的可维可测信息
 1.日    期   : 2012年3月10日
   作    者   : l00171473
   修改内容   : 新建 for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCbmirNum;                             /* 小区广播消息的ID个数 */
    VOS_UINT8                           aucRsv[2];
    TAF_CBA_LOG_CBMI_RANGE_STRU         astCbmiRange[TAF_CBA_MAX_CBMID_RANGE_NUM]; /* 小区广播消息的范围信息 */
}TAF_CBA_LOG_CBMI_RANGE_LIST_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_LOG_NVIM_INFO_STRU
 结构说明  : 当前CBS相关的NV项的可维可测信息
 1.日    期   : 2012年12月04日
   作    者   : l00171473
   修改内容   : 新建 for DTS2012120600056
*****************************************************************************/
typedef struct
{
    TAF_CBA_CBS_SERVICE_PARM_STRU       stCbsServiceParam;
    TAF_CBA_MS_CFG_ETWS_INFO_STRU       stEtwsMsCfg;                            /* 用户配置的ETWS的信息 */
}TAF_CBA_LOG_NVIM_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_CBA_MNTN_INFO_STRU
 结构说明  : CBA模块的可维可测信息
 1.日    期   : 2012年3月10日
   作    者   : l00171473
   修改内容   : 新建 for V7R1C50 CSFB&PPAC&ETWS&ISR
 2.日    期   : 2012年12月07日
   作    者   : l00171473
   修改内容   : For DTS2012120600056, 添加CBS相关NV项的可维可测
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_CBA_OM_MSG_ID_ENUM_UINT32                           enMsgId;            /* 消息类型 */      /* _H2ASN_Skip */

    union
    {
        TAF_CBA_LOG_INFO_STRU                               stLogInfo;          /* 可维可测LOG信息 */
        TAF_CBA_LOG_DUP_RECORD_STRU                         stDupRecordInfo;    /* 可维可测重复记录信息 */
        TAF_CBA_LOG_DEL_RECORD_STRU                         stDelRecordInfo;    /* 可维可测删除记录信息 */
        TAF_CBA_LOG_SAVE_RECORD_STRU                        stSaveRecordInfo;   /* 可维可测保存记录信息 */
        TAF_CBA_LOG_CBMI_DOWNLOAD_LIST_STRU                 stCbmiDownloadList; /* 可维可测CBMID LIST信息 */
        TAF_CBA_LOG_CBMI_RANGE_LIST_STRU                    stCbmiRangeList;    /* 可维可测CBMIR LIST信息 */
        TAF_CBA_LOG_NVIM_INFO_STRU                          stCbsNvimInfo;      /* CBS相关NV信息 */
    }u;
}TAF_CBA_MNTN_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_CBA_MNTN_DCS_DECODE_HOOK_STRU
 协议表格  :
 ASN.1描述 :
            ucDcs         输入的DCS
            stDcsInfo     解码函数返回的结果，是否7bit编码
 结构说明  : CBS的DCS解码结果勾包结构
 1.日    期   : 2013年6月26日
   作    者   : f62575
   修改内容   : V9R1 STK升级
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT8                           ucDcs;
    VOS_UINT8                           aucReserved1[3];
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;
 }TAF_CBA_MNTN_DCS_DECODE_HOOK_STRU;

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
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enMsgId;

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_CBA_OM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_CBA_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_CBA_OM_MSG_DATA                 stMsgData;
}TafCbaMntn_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/

/* Deleted by wx270776 for OM融合, 2015-6-28, begin */
/* Deleted by wx270776 for OM融合, 2015-6-28, end */

VOS_VOID TAF_CBA_SndOmLogInfo(
    TAF_CBA_OM_LOG_ID_ENUM_UINT32       enLogId
);

VOS_VOID TAF_CBA_SndOmDeledRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enType,
    TAF_CBA_OM_DEL_REASON_ENUM_UINT8    enDelReason,
    TAF_CBA_RECORD_STRU                *pstDelRecord
);


VOS_VOID TAF_CBS_SndOmSavedRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enMsgType,
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType,
    TAF_CBA_RECORD_STRU                *pstNewRecord,
    VOS_UINT16                          usRecordNum
);

VOS_VOID TAF_CBA_SndOmDupRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enType,
    TAF_CBA_RECORD_STRU                *pstOldRecord
);

VOS_VOID TAF_CBA_SndOmCbmiDownloadListInfo(VOS_VOID);

VOS_VOID TAF_CBA_SndOmCbmiRangeList(VOS_VOID);

VOS_VOID TAF_CBA_SndOmNvimInfo(VOS_VOID);


#endif

/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, begin */
/* Deleted TAF_CBA_SndOmDcsInfo */
/* Deleted by f62575 for V9R1 STK升级, 2013-6-26, end */

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

#endif /* end of TafCbaMntn.h */
