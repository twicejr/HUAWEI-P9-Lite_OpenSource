/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ImsCodecInterface.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2013年7月15日
  最近修改   :
  功能描述   : IMSA和CODEC模块间的接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月15日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __IMSACODECINTERFACE_H__
#define __IMSACODECINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
/* _H2ASN_Include v_typedef.h */
/* _H2ASN_Include ImsaCodecInterface.h */
#include "vos.h"
#include "CodecInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define IMSA_CODEC_MAX_DATA_LEN                     (32)           /* 单位，16 bit */

/*
IMSA_TX_DATA_STRU结构含义如下
usFrameType     --上行本帧的FrameType
ausData         --IF1协议中的A、B、C子流，ABC紧密排列，Byte对齐
*/
#define IMSA_TX_DATA_STRU                                                       \
    VOS_UINT16                      usMsgId;    /* 原语类型 */ /*_H2ASN_Skip*/\
    VOS_UINT16                      usReserve;  /* 保留字   */                            \
    CODEC_AMR_TYPE_TX_ENUM_UINT16   usStatus;   /* AMR声码器类型  */                            \
    VOS_UINT16                      usFrameType; /* 帧类型   */                           \
    VOS_UINT16                      ausData[IMSA_CODEC_MAX_DATA_LEN];

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum IMSA_VOICE_MSG_ID_ENUM
{
    /*====== VOICE->IMSA ======*/
    ID_VOICE_IMSA_TX_DATA_IND                       = 0x49A8,                   /* IMS上行语音编码结果 */           /* _H2ASN_MsgChoice VOICE_IMSA_TX_DATA_IND_STRU */
    ID_VOICE_IMSA_CFG_CNF                           = 0x49A9,                   /* 设置HIFI上行的交互周期结果 */    /* _H2ASN_MsgChoice VOICE_IMSA_CFG_CNF_STRU */
    ID_VOICE_IMSA_RX_DATA_ACK                       = 0x49AA,                   /* 回复RX_DATA处理结果 */           /* _H2ASN_MsgChoice VOICE_IMSA_RX_DATA_ACK_STRU */

    /*====== IMSA->VOICE ======*/
    ID_IMSA_VOICE_RX_DATA_IND                       = 0x94A8,                   /* IMS下行语音数据 */               /* _H2ASN_MsgChoice IMSA_VOICE_RX_DATA_IND_STRU */
    ID_IMSA_VOICE_CFG_REQ                           = 0x94A9,                   /* 设置HIFI上行的交互周期 */        /* _H2ASN_MsgChoice IMSA_VOICE_CFG_REQ_STRU */

    IMSA_VOICE_MSG_ID_BUTT
};
typedef VOS_UINT16 IMSA_VOICE_MSG_ID_ENUM_UINT16;

enum IMSA_VOICE_ERRORFLAG_ENUM
{
    IMSA_VOICE_NO_ERROR = 0,                                                    /* Jitter Buffer有数据 */
    IMSA_VOICE_ERROR,                                                           /* Jitter Buffer没有数据 */
    IMSA_VOICE_ERRORFLAG_BUTT
};
typedef VOS_UINT16 IMSA_VOICE_ERRORFLAG_ENUM_UINT16;

enum IMSA_VOICE_CFG_ENUM
{
    IMSA_VOICE_CFG_SUCC         = 0,                /* 设置成功 */
    IMSA_VOICE_CFG_FAIL,                            /* 设置失败 */
    IMSA_VOICE_CFG_BUTT
};
typedef VOS_UINT32 IMSA_VOICE_CFG_ENUM_UINT32;



/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/

/*****************************************************************************
 实体名称  : IMSA_VOICE_RX_DATA_IND_STRU
 功能描述  : IMS获取IP包并完成RTP解包后通过IMSA发送该消息给VOICE将数据发送过去
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* 0x94A8*/ /*_H2ASN_Skip*/
    VOS_UINT16                          usSN;                                   /* 包序列号 */
    VOS_UINT32                          ulTS;                                   /* 包时间戳 */
    CODEC_ENUM_UINT16                   usCodecType;                            /* 声码器类型 */
    CODEC_DTX_ENUM_UINT16               usDtxEnable;                            /* 上行编码的DTX */
    VOS_UINT16                          usRateMode;                             /* 上行编码的RateMode */
    IMSA_VOICE_ERRORFLAG_ENUM_UINT16    usErrorFlag;                            /* Buffer没数据时的ErrorFlag */
    VOS_UINT16                          usFrameType;                            /* 下行本帧的FrameType */
    VOS_UINT16                          usQualityIdx;                           /* Quality indification */
    VOS_UINT16                          ausData[IMSA_CODEC_MAX_DATA_LEN];       /* IF1协议中的A、B、C子流，ABC紧密排列，Byte对齐 */
    VOS_UINT32                          ulSSRC;                                 /* SSRC信息 */
    VOS_UINT32                          ulNeedAckFlag;                          /* 是否需要HIFI回复标志 */
    VOS_UINT32                          ulOpid;                                 /* Opid号，用来同步消息 */
}IMSA_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_IMSA_RX_DATA_ACK_STRU
 功能描述  : 需要HIFI回复ack,HIFI的回复结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* 0x94AA*/ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserved;
    VOS_UINT32                          ulOpid;                                 /* Opid号，用来同步消息 */
}VOICE_IMSA_RX_DATA_ACK_STRU;

/*****************************************************************************
 实体名称  : VOICE_IMSA_TX_DATA_IND_STRU
 功能描述  : VOICE在上行数据处理和编码OK后，通过该消息将数据发送给IMSA
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER																/*_H2ASN_Skip*/
    IMSA_TX_DATA_STRU
}VOICE_IMSA_TX_DATA_IND_STRU;

/*****************************************************************************
 实体名称  : IMSA_VOICE_CFG_REQ_STRU
 功能描述  : 设置HIFI上行的交互周期
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER																/*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* 0x94a9 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulTransTime;                            /* 上行和IMSA的交互周期 */
    VOS_UINT32                          ulSendBitrate;                          /* Ims发包的码率 */
}IMSA_VOICE_CFG_REQ_STRU;

/*****************************************************************************
 实体名称  : IMSA_VOICE_CFG_CNF_STRU
 功能描述  : IMSA_VOICE_CFG_REQ的回复
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER																/*_H2ASN_Skip*/
    VOS_UINT16                              usMsgId;                            /* 0x49a9 */ /*_H2ASN_Skip*/
    VOS_UINT16                              usReserve;
    IMSA_VOICE_CFG_ENUM_UINT32              ulResult;                           /* 执行结果 */
}VOICE_IMSA_CFG_CNF_STRU;



/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
#if 0                                                                           /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
/* 需要更改相应的ASN编码,去掉L方式,仅保留V方式 */
typedef struct
{
    IMSA_VOICE_MSG_ID_ENUM_UINT16          enMsgID;                              /* _H2ASN_MsgChoice_Export IMSA_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_IMSA_TRACE_MSG_DATA;

/* 协议消息结构*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_IMSA_TRACE_MSG_DATA              stMsgData;
}VoiceImsaTrace_MSG;

#endif    																		/* _H2ASN_Skip */
/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of imsacodecinterface.h */

