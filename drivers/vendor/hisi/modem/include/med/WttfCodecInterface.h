/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : WttfcodecInterface.h
  版 本 号   : V1.00
  作    者   : 黄飞
  生成日期   : 2010年4月9日
  最近修改   :
  功能描述   : WttfCodecInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年4月9日
    作    者   : 黄飞
    修改内容   : 创建文件
******************************************************************************/

#ifndef __WTTFCODECINTERFACE_H__
#define __WTTFCODECINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WTTFVOICE_AMR_CODEC_MODE_NUM    (11)             /* AMR-NB和AMR-WB复用，取最大值，CODEC_MODE 个数共有11种，不包括SID */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum WTTFVOICE_AMR_CODECMODE_TYPE_ENUM
{
    WTTFVOICE_AMR_CODECMODE_TYPE_475K          = 0,                             /* 4.75K数据格式: class a 42bit, b 53bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_515K          = 1,                             /* 5.15K数据格式: class a 49bit, b 54bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_590K          = 2,                             /* 5.9 K数据格式: class a 55bit, b 63bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_670K          = 3,                             /* 6.7 K数据格式: class a 58bit, b 76bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_740K          = 4,                             /* 7.4 K数据格式: class a 61bit, b 87bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_795K          = 5,                             /* 7.95K数据格式: class a 75bit, b 84bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_102K          = 6,                             /* 10.2K数据格式: class a 65bit, b 99bit , c 40bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_122K          = 7,                             /* 12.2K数据格式: class a 81bit, b 103bit, c 60bit */
    WTTFVOICE_AMR_CODECMODE_TYPE_BUTT
};
typedef  VOS_UINT16 WTTFVOICE_AMR_CODECMODE_TYPE_ENUM_UINT16; 

enum WTTFVOICE_AMRWB_CODECMODE_TYPE_ENUM
{
    WTTFVOICE_AMRWB_CODECMODE_TYPE_660K        = 0,                             /* 6.60K数据格式:   class a 54bit, b 78bit , c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_885K        = 1,                             /* 8.85K数据格式:   class a 64bit, b 113bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1265K       = 2,                             /* 12.65 K数据格式: class a 72bit, b 181bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1425K       = 3,                             /* 14.25 K数据格式: class a 72bit, b 213bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1585K       = 4,                             /* 15.85 K数据格式: class a 72bit, b 245bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1825K       = 5,                             /* 18.25K数据格式:  class a 72bit, b 293bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1985K       = 6,                             /* 19.85K数据格式:  class a 72bit, b 325bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_2305K       = 7,                             /* 23.05K数据格式:  class a 72bit, b 389bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_2385K       = 8,                             /* 23.85K数据格式:  class a 72bit, b 405bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_1585K_B     = 9,                             /* 15.85 K数据格式: class a 72bit, b 245bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_2385K_B     = 10,                             /* 23.85K数据格式:  class a 72bit, b 405bit, c 0bit */
    WTTFVOICE_AMRWB_CODECMODE_TYPE_BUTT
};
typedef  VOS_UINT16 WTTFVOICE_AMRWB_CODECMODE_TYPE_ENUM_UINT16;

enum WTTFVOICE_AMR_FRAME_TYPE_ENUM
{
    WTTFVOICE_AMR_FRAME_TYPE_475K         = 0,    /* 4.75K数据格式: class a 42bit, b 53bit */
    WTTFVOICE_AMR_FRAME_TYPE_515K         = 1,    /* 5.15K数据格式: class a 49bit, b 54bit */
    WTTFVOICE_AMR_FRAME_TYPE_590K         = 2,    /* 5.9 K数据格式: class a 55bit, b 63bit */
    WTTFVOICE_AMR_FRAME_TYPE_670K         = 3,    /* 6.7 K数据格式: class a 58bit, b 76bit */
    WTTFVOICE_AMR_FRAME_TYPE_740K         = 4,    /* 7.4 K数据格式: class a 61bit, b 87bit */
    WTTFVOICE_AMR_FRAME_TYPE_795K         = 5,    /* 7.95K数据格式: class a 75bit, b 84bit */
    WTTFVOICE_AMR_FRAME_TYPE_102K         = 6,    /* 10.2K数据格式: class a 65bit, b 99bit , c 40bit */
    WTTFVOICE_AMR_FRAME_TYPE_122K         = 7,    /* 12.2K数据格式: class a 81bit, b 103bit, c 60bit */
    WTTFVOICE_AMR_FRAME_TYPE_SID          = 8,    /* SID帧数据格式: class a 39bit */

    WTTFVOICE_AMR_FRAME_TYPE_BUTT
};
typedef  VOS_UINT8    WTTFVOICE_AMR_FRAME_TYPE_ENUM_UINT8;

enum WTTFVOICE_AMRWB_FRAME_TYPE_ENUM
{
    WTTFVOICE_AMRWB_FRAME_TYPE_660K         = 0,    /* 6.60K数据格式: class a 54bit, b 78bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_885K         = 1,    /* 8.85K数据格式: class a 64bit, b 113bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1265K        = 2,    /* 12.65K数据格式: class a 72bit, b 181bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1425K        = 3,    /* 14.25K数据格式: class a 72bit, b 213bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1585K        = 4,    /* 15.85K数据格式: class a 72bit, b 245bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1825K        = 5,    /* 18.25K数据格式: class a 72bit, b 293bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1985K        = 6,    /* 19.85K数据格式: class a 72bit, b 325bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_2305K        = 7,    /* 23.05K数据格式: class a 72bit, b 389bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_2385K        = 8,    /* 23.85K数据格式: class a 72bit, b 405bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_SID          = 9,    /* SID帧1.75K数据格式: class a 40bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_1585K_B      = 10,   /* 15.85K数据格式: class a 73bit, b 244bit */
    WTTFVOICE_AMRWB_FRAME_TYPE_2385K_B      = 11,   /* 23.85K数据格式: class a 74bit, b 403bit */

    WTTFVOICE_AMRWB_FRAME_TYPE_BUTT
};
typedef  VOS_UINT16    WTTFVOICE_AMRWB_FRAME_TYPE_ENUM_UINT16;


enum WTTFVOICE_AMR_TYPE_ENUM
{
    WTTFVOICE_AMR_TYPE_AMR2               = 0,
    WTTFVOICE_AMR_TYPE_AMR                = 1,
    WTTFVOICE_AMR_TYPE_AMRWB              = 2,
    WTTFVOICE_AMR_TYPE_BUTT
};
typedef VOS_UINT16 WTTFVOICE_AMR_TYPE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMR_FORMAT_ENUM
 功能描述  : AMR窄带和宽带定义, 参见3GPP TS 26.101
*****************************************************************************/
enum WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM
{
    WTTFVOICE_AMR_BANDWIDTH_TYPE_NB             = 0,
    WTTFVOICE_AMR_BANDWIDTH_TYPE_WB             = 1,
    WTTFVOICE_AMR_BANDWIDTH_TYPE_BUTT
};
typedef VOS_UINT16 WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : WTTFVOICE_RSLT_ENUM
 功能描述  : WTTF与CODEC之间返回值定义
*****************************************************************************/
enum WTTFVOICE_RSLT_ENUM
{
    WTTFVOICE_RSLT_SUCC             = 0,                                    /* 返回给MAC, 成功 */
    WTTFVOICE_RSLT_FAIL             = 1,                                    /* 返回给MAC, 失败 */
    WTTFVOICE_RSLT_BUTT
};
typedef VOS_UINT16 WTTFVOICE_RSLT_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
enum WTTFVOICE_MSG_TYPE_ENUM
{
    ID_MAC_VOICE_MODE_SET_IND           = 0x9450,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_VOICE_MODE_SET_IND_STRU */
    ID_VOICE_MAC_MODE_SET_RSP           = 0x3050,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_MODE_SET_RSP_STRU */

    ID_MAC_VOICE_MODE_CHANGE_IND        = 0x9451,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_VOICE_MODE_CHANGE_IND_STRU */
    ID_VOICE_MAC_MODE_CHANGE_RSP        = 0x3051,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_MODE_CHANGE_RSP_STRU */

    ID_VOICE_MAC_AMR_TYPE_REQ           = 0x3052,           /* _H2ASN_MsgChoice WTTFVOICE_MAC_AMR_TYPE_REQ_STRU */

    ID_MAC_VOICE_AMR_DATA_IND           = 0x1101,           /* 未使用 */ /*_H2ASN_Skip */ 
    ID_VOICE_MAC_AMR_DATA_REQ           = 0x3101,           /*_H2ASN_Skip */

    WTTFVOICE_MSG_TYPE_BUTT                                 /*_H2ASN_Skip */
} ;
typedef VOS_UINT16  WTTFVOICE_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 实体名称  : WTTFVOICE_MAC_CODEC_MODE_SET_IND_STRU
 功能描述  : WTTF MAC发消息通知Codec其支持的CodecMode集
           目前应用场景是当发生ID_RRC_MAC_D_CONFIG_REQ 和 ID_RRC_MAC_TFC_CONTROL_REQ时
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16           enMsgName;             /* 消息ID */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;                /*操作标识*/
    VOS_UINT16                               usSidEnable;           /*是否使用SID帧[0,1] 0:不使用, 1:使用*/
    WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16 enCodecType;           /*0: NB;   1:WB*/ /*_H2ASN_Replace VOS_UINT16 enCodecType;*/
    VOS_UINT16                               usCodecModeCnt;        /* AMR 语音速率集合包含的语音速率个数，enCodecType =NB时范围[1..8]，enCodecType =WB时范围[1..9]*/
    VOS_UINT16                               aenCodecModes[WTTFVOICE_AMR_CODEC_MODE_NUM]; /* AMR 语音速率集合, enCodecType =NB时包含速率范围[0..7] 0: 4.75kbps, 7: 12.2kbps，enCodecType =WB时包含速率范围[0..8] 0: 6.60kbps, 8: 23.85kbps */
} WTTFVOICE_MAC_VOICE_MODE_SET_IND_STRU;

/******************************************************************************************************
结构名    : WTTFVOICE_MAC_MODE_SET_RSP_STRU
结构说明  : Codec发消息响应MAC的 WTTFVOICE_MAC_CODEC_MODE_SET_IND_STRU 消息
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16           enMsgName;             /* 消息ID */ /*_H2ASN_Skip*/
    VOS_UINT16                               usOpId;                /*操作标识*/
    WTTFVOICE_RSLT_ENUM_UINT16               enResult;              /*返回结果[0,1] 0:= PS_SUCC , 1:= PS_FAIL */ /*_H2ASN_Replace VOS_UINT16 enResult;*/
    VOS_UINT16                               enCurrMode;            /*当前AMR 语音速率，enCodecType=NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps，enCodecType=WB时，包含速率范围[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    WTTFVOICE_AMR_TYPE_ENUM_UINT16           enAmrType;             /*enCodecType=NB时，AMR 语音类型[0,1] 0: AMR2, 1: AMR；enCodecType=WB时此参数无意义 *//*_H2ASN_Replace VOS_UINT16 enAmrType;*/
    VOS_UINT16                               ausRsv[1];
} WTTFVOICE_MAC_MODE_SET_RSP_STRU;

/******************************************************************************************************
结构名    : WTTFVOICE_MAC_CODEC_MODE_CHANGE_IND_STRU
结构说明  : WTTF MAC发消息通知Codec语言编码速率改变为目标速率
          目前应用场景是当MAC因TFC状态变化而发生速率改变时
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16              enMsgName;          /* 消息ID */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOpId;             /*操作标识*/
    WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16    enCodecType;        /*0: NB; 1:WB*/ /*_H2ASN_Replace VOS_UINT16 enCodecType;*/
    VOS_UINT16                                  enCurrMode;         /*当前AMR 语音速率；enCodecType=NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps；enCodecType=WB时范围[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    VOS_UINT16                                  enTargetMode;       /*目标AMR 语音速率；enCodecType=NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps；enCodecType=WB时范围[0..8] 0: 6.60kbps, 8: 23.85kbps */
    VOS_UINT16                                  ausRsv[1];          /*保留*/
} WTTFVOICE_MAC_VOICE_MODE_CHANGE_IND_STRU;

/******************************************************************************************************
结构名    : WTTFVOICE_MAC_MODE_CHANGE_RSP_STRU
结构说明  : Codec发消息响应MAC的 WTTFVOICE_MAC_CODEC_MODE_CHANGE_IND_STRU 消息
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16              enMsgName;          /* 消息ID */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usOpId;             /*操作标识*/
    WTTFVOICE_RSLT_ENUM_UINT16                  enResult;           /*返回结果[0,1] 0:= PS_SUCC , 1:= PS_FAIL *//*_H2ASN_Replace VOS_UINT16 enResult;*/
    VOS_UINT16                                  enCurrMode;         /*当前AMR 语音速率； enCodecType =NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps；enCodecType=WB时范围[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    VOS_UINT16                                  enTargetMode;       /*目标AMR 语音速率； enCodecType =NB时范围[0..7] 0: 4.75kbps, 7: 12.2kbps；enCodecType=WB时范围[0..8] 0: 6.60kbps, 8: 23.85kbps*/
    VOS_UINT16                                  ausRsv[1];
} WTTFVOICE_MAC_MODE_CHANGE_RSP_STRU;

/******************************************************************************************************
结构名    : WTTFVOICE_MAC_AMR_TYPE_REQ_STRU
结构说明  : Codec发消息通知MAC消息当前的AMR类型
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16              enMsgName;          /* 消息ID */ /*_H2ASN_Skip*/
    WTTFVOICE_AMR_TYPE_ENUM_UINT16              enAmrType;          /*AMR 语音类型[0,1,2] 0: AMR2, 1: AMR, 2: AMRWB */ /*_H2ASN_Replace VOS_UINT16 enAmrType;*/
    VOS_UINT16                                  ausRsv[2];
}WTTFVOICE_MAC_AMR_TYPE_REQ_STRU;

/******************************************************************************************************
结构名    : WTTFVOICE_MAC_AMR_DATA_STRU
结构说明  : Codec给MAC AMR消息的数据结构
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    WTTFVOICE_MSG_TYPE_ENUM_UINT16              enMsgName;          /* 消息ID */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usMuteFlag;         /* 1表示已写入，0表示已读走 */
    WTTFVOICE_AMR_BANDWIDTH_TYPE_ENUM_UINT16    enCodecType;        /* 0: NB;  1: WB */ /*_H2ASN_Replace VOS_UINT16 enCodecType;*/
    VOS_UINT16                                  enFrameType;        /* AMR编码帧类型 */
}WTTFVOICE_MAC_AMR_DATA_STRU;

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
    WTTFVOICE_MSG_TYPE_ENUM_UINT16      enMsgID;            /* _H2ASN_MsgChoice_Export WTTFVOICE_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          WTTFVOICE_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}VOICE_WTTF_TRACE_MSG_DATA;

/* 协议消息结构*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_WTTF_TRACE_MSG_DATA             stMsgData;
}VoiceWttfTrace_MSG;

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

#endif /* end of WttfCodecInterface.h */



