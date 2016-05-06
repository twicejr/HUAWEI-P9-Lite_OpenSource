/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TdmacCodecInterface.h
  版 本 号   : V1.00
  作    者   : 00187560
  生成日期   : 2012年7月28日
  最近修改   :
  功能描述   : TdmacCodecInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月28日
    作    者   : 00187560
    修改内容   : 创建文件
******************************************************************************/

#ifndef __TDMACCODECINTERFACE_H__
#define __TDMACCODECINTERFACE_H__

#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TDMACVOICE_AMR_CODEC_MODE_NUM    (8)             /* AMR-NB，取最大值，CODEC_MODE 个数共有8种，不包括SID */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum TDMACVOICE_AMR_CODECMODE_TYPE_ENUM
{
    TDMACVOICE_AMR_CODECMODE_TYPE_475K          = 0,     /* 4.75K数据格式: class a 42bit, b 53bit */
    TDMACVOICE_AMR_CODECMODE_TYPE_515K          = 1,     /* 5.15K数据格式: class a 49bit, b 54bit */
    TDMACVOICE_AMR_CODECMODE_TYPE_590K          = 2,     /* 5.9 K数据格式: class a 55bit, b 63bit */
    TDMACVOICE_AMR_CODECMODE_TYPE_670K          = 3,     /* 6.7 K数据格式: class a 58bit, b 76bit */
    TDMACVOICE_AMR_CODECMODE_TYPE_740K          = 4,     /* 7.4 K数据格式: class a 61bit, b 87bit */
    TDMACVOICE_AMR_CODECMODE_TYPE_795K          = 5,     /* 7.95K数据格式: class a 75bit, b 84bit */
    TDMACVOICE_AMR_CODECMODE_TYPE_102K          = 6,     /* 10.2K数据格式: class a 65bit, b 99bit , c 40bit */
    TDMACVOICE_AMR_CODECMODE_TYPE_122K          = 7,     /* 12.2K数据格式: class a 81bit, b 103bit, c 60bit */
    TDMACVOICE_AMR_CODECMODE_TYPE_BUTT
};
typedef  VOS_UINT16 TDMACVOICE_AMR_CODECMODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : TDMACVOICE_AMR_TYPE_ENUM
 功能描述  : AMR声码器定义, 参见3GPP TS 26.101
*****************************************************************************/
enum TDMACVOICE_AMR_TYPE_ENUM
{
    TDMACVOICE_AMR_TYPE_AMR2               = 0,
    TDMACVOICE_AMR_TYPE_AMR                = 1,
    TDMACVOICE_AMR_TYPE_BUTT
};
typedef VOS_UINT16 TDMACVOICE_AMR_TYPE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : TDMACVOICE_AMR_BANDWIDTH_TYPE_ENUM
 功能描述  : AMR窄带定义, 参见3GPP TS 26.101
*****************************************************************************/
enum TDMACVOICE_AMR_BANDWIDTH_TYPE_ENUM
{
    TDMACVOICE_AMR_BANDWIDTH_TYPE_NB       = 0,
    TDMACVOICE_AMR_BANDWIDTH_TYPE_BUTT
};
typedef VOS_UINT16 TDMACVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : TDMACVOICE_RSLT_ENUM
 功能描述  : TDMAC与CODEC之间结果返回值定义
*****************************************************************************/
enum TDMACVOICE_RSLT_ENUM
{
    TDMACVOICE_RSLT_SUCC             = 0,                                    /* 返回给MAC, 成功 */
    TDMACVOICE_RSLT_FAIL             = 1,                                    /* 返回给MAC, 失败 */
    TDMACVOICE_RSLT_BUTT
};
typedef VOS_UINT16 TDMACVOICE_RSLT_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
enum TDMACVOICE_MSG_TYPE_ENUM
{
    ID_TDMAC_VOICE_MODE_SET_IND         = 0x9460,           /* _H2ASN_MsgChoice TDMACVOICE_MAC_VOICE_MODE_SET_IND_STRU */
    ID_VOICE_TDMAC_MODE_SET_RSP         = 0x3060,           /* _H2ASN_MsgChoice TDMACVOICE_VOICE_MAC_MODE_SET_RSP_STRU */

    ID_TDMAC_VOICE_MODE_CHANGE_IND      = 0x9461,           /* _H2ASN_MsgChoice TDMACVOICE_MAC_VOICE_MODE_CHANGE_IND_STRU */
    ID_VOICE_TDMAC_MODE_CHANGE_RSP      = 0x3061,           /* _H2ASN_MsgChoice TDMACVOICE_VOICE_MAC_MODE_CHANGE_RSP_STRU */

    ID_VOICE_TDMAC_AMR_TYPE_REQ         = 0x3062,           /* _H2ASN_MsgChoice TDMACVOICE_VOICE_MAC_AMR_TYPE_REQ_STRU */

    TDMACVOICE_MSG_TYPE_BUTT
} ;
typedef VOS_UINT16 TDMACVOICE_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 实体名称  : TDMACVOICE_MAC_VOICE_MODE_SET_IND_STRU
 功能描述  : WTTF MAC发消息通知Codec其支持的CodecMode集
           目前应用场景是当发生ID_RRC_MAC_D_CONFIG_REQ 和 ID_RRC_MAC_TFC_CONTROL_REQ时
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* 消息头 */        /*_H2ASN_Skip*/
    TDMACVOICE_MSG_TYPE_ENUM_UINT16           enMsgName;             /*消息类型*/ /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;                /*操作标识*/
    VOS_UINT16                                usSidEnable;           /*是否使用SID帧[0,1] 0:不使用, 1:使用*/
    TDMACVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16 enCodecType;           /*0: NB*/
    VOS_UINT16                                usCodecModeCnt;        /* AMR 语音速率集合包含的语音速率个数，enCodecType =NB时范围[1..8]*/
    VOS_UINT16                                aenCodecModes[TDMACVOICE_AMR_CODEC_MODE_NUM]; /* AMR 语音速率集合, enCodecType =NB时包含速率范围[0..7] 0: 4.75kbps, 7: 12.2kbps，enCodecType =WB时包含速率范围[0..8] 0: 6.60kbps, 8: 23.85kbps */
    VOS_UINT16                                usReserved;
} TDMACVOICE_MAC_VOICE_MODE_SET_IND_STRU;

/******************************************************************************************************
结构名    : TCODEC_MAC_MODE_SET_RSP_STRU
结构说明  : Codec发消息响应MAC的 TMAC_VOICE_MODE_SET_IND_STRU 消息
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* 消息头 */        /*_H2ASN_Skip*/
    TDMACVOICE_MSG_TYPE_ENUM_UINT16          enMsgName;             /*消息类型*/ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;                /*操作标识*/
    TDMACVOICE_RSLT_ENUM_UINT16              enResult;              /*返回结果[0,1] 0:= PS_SUCC , 1:= PS_FAIL */
    VOS_UINT16                               enCurrMode;            /*当前AMR 语音速率，enCodecType=NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps，enCodecType=WB时，包含速率范围[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    TDMACVOICE_AMR_TYPE_ENUM_UINT16          enAmrType;             /*enCodecType=NB时，AMR 语音类型[0,1] 0: AMR2, 1: AMR */
    VOS_UINT16                               ausRsv[1];
} TDMACVOICE_VOICE_MAC_MODE_SET_RSP_STRU;

/******************************************************************************************************
结构名    : TDMACVOICE_MAC_VOICE_MODE_CHANGE_IND_STRU
结构说明  : WTTF MAC发消息通知Codec语言编码速率改变为目标速率
          目前应用场景是当MAC因TFC状态变化而发生速率改变时
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* 消息头 */        /*_H2ASN_Skip*/
    TDMACVOICE_MSG_TYPE_ENUM_UINT16             enMsgName;          /*消息类型*/ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOpId;             /*操作标识*/
    TDMACVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16   enCodecType;        /*0: NB*/
    VOS_UINT16                                  enCurrMode;         /*当前AMR 语音速率；enCodecType=NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps；*/
    VOS_UINT16                                  enTargetMode;       /*目标AMR 语音速率；enCodecType=NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps；*/
    VOS_UINT16                                  ausRsv[1];          /*保留*/
} TDMACVOICE_MAC_VOICE_MODE_CHANGE_IND_STRU;

/******************************************************************************************************
结构名    : TDMACVOICE_VOICE_MAC_MODE_CHANGE_RSP_STRU
结构说明  : Codec发消息响应MAC的 TDMACVOICE_MAC_VOICE_MODE_CHANGE_IND_STRU 消息
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TDMACVOICE_MSG_TYPE_ENUM_UINT16             enMsgName;          /*消息类型*/ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOpId;             /*操作标识*/
    TDMACVOICE_RSLT_ENUM_UINT16                 enResult;           /*返回结果[0,1] 0:= PS_SUCC , 1:= PS_FAIL */
    VOS_UINT16                                  enCurrMode;         /*当前AMR 语音速率； enCodecType =NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps；*/
    VOS_UINT16                                  enTargetMode;       /*目标AMR 语音速率； enCodecType =NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps；*/
    VOS_UINT16                                  ausRsv[1];
} TDMACVOICE_VOICE_MAC_MODE_CHANGE_RSP_STRU;

/******************************************************************************************************
结构名    : TDMACVOICE_VOICE_MAC_AMR_TYPE_REQ_STRU
结构说明  : Codec发消息通知MAC消息当前的AMR类型
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* 消息头 */        /*_H2ASN_Skip*/
    TDMACVOICE_MSG_TYPE_ENUM_UINT16             enMsgName;          /*消息类型*/ /*_H2ASN_Skip*/
    TDMACVOICE_AMR_TYPE_ENUM_UINT16             enAmrType;          /*AMR 语音类型[0,1] 0: AMR2, 1: AMR */
    VOS_UINT16                                  ausRsv[2];
}TDMACVOICE_VOICE_MAC_AMR_TYPE_REQ_STRU;

/******************************************************************************************************
结构名    : TDMACVOICE_VOICE_MAC_AMR_DATA_STRU
结构说明  : Codec给MAC AMR消息的数据结构
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* 消息头 */        /*_H2ASN_Skip*/
    TDMACVOICE_MSG_TYPE_ENUM_UINT16             enMsgName;          /*消息类型*/
    VOS_UINT16                                  usMuteFlag;         /*标志数据是否已被取走*/
    TDMACVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16   enCodecType;        /* 0: NB */
    VOS_UINT16                                  enFrameType;        /* AMR编码帧类型 */
}TDMACVOICE_VOICE_MAC_AMR_DATA_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */
/*****************************************************************************
  H2ASN生成的ASN文件需要添加
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
/* 需要更改相应的ASN编码,去掉L方式,仅保留V方式 */
typedef struct
{
    TDMACVOICE_MSG_TYPE_ENUM_UINT16     enMsgID;            /* _H2ASN_MsgChoice_Export TDMACVOICE_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TDMACVOICE_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}VOICE_TDMACVOICE_TRACE_MSG_DATA;

/* 协议消息结构*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_TDMACVOICE_TRACE_MSG_DATA       stMsgData;
}VoiceTdmacTrace_MSG;

#endif                                                     /* _H2ASN_Skip */

/*****************************************************************************
  10 函数声明
*****************************************************************************/







#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TdmacCodecInterface.h */



