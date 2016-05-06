/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : phyCodecInterface.h
  版 本 号   : 初稿
  作    者   : 陈超群 00137131
  生成日期   : 2011年5月6日
  最近修改   :
  功能描述   : PHY和CODEC模块间的接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月6日
    作    者   : 陈超群 00137131
    修改内容   : 创建文件

******************************************************************************/
#ifndef __PHYCODECINTERFACE_H__
#define __PHYCODECINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CodecInterface.h"

/* _H2ASN_Include CODEC_ctrl_mc.h */
/* _H2ASN_Include codec_typedefine.h */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define GPHY_VOICE_DATA_LEN                                   (17)                /* G物理层与CODEC交互的语音数据长度,单位16Bit */
#define WPHY_VOICE_WCDMA_MAX_CELL_NUM                         (6)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum DSP_VOICE_MSG_ID_ENUM
{
    /*====== WPHY->CODEC ======*/
    ID_WPHY_VOICE_RX_DATA_IND                         = 0xBD01,                 /* W 语音解码指示 */             /* _H2ASN_MsgChoice WPHY_VOICE_RX_DATA_IND_STRU */
    ID_WPHY_VOICE_SYNC_IND                            = 0xBD02,                 /* W 同步指示 */                 /* _H2ASN_MsgChoice WPHY_VOICE_SYNC_IND_STRU */
    ID_WPHY_VOICE_BACKGROUND_CNF                      = 0xBD03,                 /* W 物理层回复已进入静默模式 *//* _H2ASN_MsgChoice GUPHY_VOICE_BACKGROUND_CNF_STRU */
    ID_WPHY_VOICE_FOREGROUND_CNF                      = 0xBD04,                 /* W 物理层回复已退出静默模式 *//* _H2ASN_MsgChoice GUPHY_VOICE_FOREGROUND_CNF_STRU */
    ID_WPHY_VOICE_CHANNEL_QUALITY_IND                 = 0xBD05,                 /* W 物理层上报信道质量，用于后台可维可测 *//* _H2ASN_MsgChoice WPHY_VOICE_CHANNEL_QUALITY_IND_STRU */
    ID_WPHY_VOICE_BSD_CS_IND                          = 0xBD06,                 /* W 物理层维测信息，作为BSD3.0算法的输入 */ /* _H2ASN_MsgChoice WPHY_VOICE_BSD_CS_IND_STRU */

    /*====== CODEC->WPHY ======*/
    ID_VOICE_WPHY_TX_DATA_IND                         = 0xDB01,                 /* W 语音编码结果 */             /* _H2ASN_MsgChoice VOICE_WPHY_TX_DATA_IND_STRU */
    ID_VOICE_WPHY_BACKGROUND_REQ                      = 0xDB03,                 /* W 通知PHY进入静默工作模式 */  /* _H2ASN_MsgChoice VOICE_GUPHY_BACKGROUND_REQ_STRU */
    ID_VOICE_WPHY_FOREGROUND_REQ                      = 0xDB04,                 /* W 通知PHY退出静默工作模式 */  /* _H2ASN_MsgChoice VOICE_GUPHY_FOREGROUND_REQ_STRU */

    /*====== GPHY->CODEC ======*/
    ID_GPHY_VOICE_RX_DATA_IND                         = 0xCD01,                 /* GSM 语音解码指示 */           /* _H2ASN_MsgChoice GPHY_VOICE_RX_DATA_IND_STRU */
    ID_GPHY_VOICE_UPDATE_PARA_CMD                     = 0xCD02,                 /* GSM 语音编码参数更新 */       /* _H2ASN_MsgChoice GPHY_VOICE_UPDATE_PARA_CMD_STRU */
    ID_GPHY_VOICE_PLAY_IND                            = 0xCD04,                 /* GSM 下行语音播放启动指示 */   /* _H2ASN_MsgChoice GPHY_VOICE_PLAY_IND_STRU */
    ID_GPHY_VOICE_RECORD_IND                          = 0xCD05,                 /* GSM 上行语音采集启动指示 */   /* _H2ASN_MsgChoice GPHY_VOICE_RECORD_IND_STRU */
    ID_GPHY_VOICE_BACKGROUND_CNF                      = 0xCD07,                 /* G 物理层回复已进入静默模式 *//* _H2ASN_MsgChoice GUPHY_VOICE_BACKGROUND_CNF_STRU */
    ID_GPHY_VOICE_FOREGROUND_CNF                      = 0xCD08,                 /* G 物理层回复已退出静默模式 *//* _H2ASN_MsgChoice GUPHY_VOICE_FOREGROUND_CNF_STRU */
    ID_GPHY_VOICE_SYNC_IND                            = 0xCD10,                 /* G 同步指示 */                /* _H2ASN_MsgChoice GPHY_VOICE_SYNC_IND_STRU */
    ID_GPHY_VOICE_CHANNEL_QUALITY_IND                 = 0xCD11,                 /* G 物理层信道质量可维可测 */ /* _H2ASN_MsgChoice GPHY_VOICE_CHANNEL_QUALITY_IND_STRU */
    ID_GPHY_VOICE_BSD_CS_IND                          = 0xCD12,                 /* G 物理层维测信息，作为BSD3.0算法的输入 */ /* _H2ASN_MsgChoice GPHY_VOICE_BSD_CS_IND_STRU */
    ID_GPHY_VOICE_HO_START_REQ                        = 0xCD13,                 /* Ho切换开始，向MED下发开始消息 */ /* _H2ASN_MsgChoice GPHY_VOICE_HO_START_REQ_STRU */
    ID_GPHY_VOICE_HO_COMPLETE_REQ                     = 0xCD14,                 /* Ho切换完成，向MED下发完成消息 */ /* _H2ASN_MsgChoice GPHY_VOICE_HO_Complete_REQ_STRU */

    /*====== CODEC->GPHY ======*/
    ID_VOICE_GPHY_TX_DATA_IND                         = 0xDC02,                 /* GSM 语音编码结果 */           /* _H2ASN_MsgChoice VOICE_GPHY_TX_DATA_IND_STRU */
    ID_VOICE_GPHY_SYNC_REQ                            = 0xDC03,                 /* GSM 语音时序同步请求，GPHY收到后重新指示语音开始上下行语音采集、播放 */ /* _H2ASN_MsgChoice VOICE_GPHY_SYNC_REQ_STRU */
    ID_VOICE_GPHY_PLAY_CNF                            = 0xDC04,                 /* GSM 下行语音播放启动确认 */   /* _H2ASN_MsgChoice VOICE_GPHY_PLAY_CNF_STRU */
    ID_VOICE_GPHY_RECORD_CNF                          = 0xDC05,                 /* GSM 上行语音播放启动确认 */   /* _H2ASN_MsgChoice VOICE_GPHY_RECORD_CNF_STRU */
    ID_VOICE_GPHY_SET_CODEC_IND                       = 0xDC06,                 /* GSM 声码器切换指示 */         /* _H2ASN_MsgChoice VOICE_GPHY_SET_CODEC_IND_STRU */
    ID_VOICE_GPHY_BACKGROUND_REQ                      = 0xDC07,                 /* GSM 通知PHY进入静默工作模式 *//* _H2ASN_MsgChoice VOICE_GUPHY_BACKGROUND_REQ_STRU */
    ID_VOICE_GPHY_FOREGROUND_REQ                      = 0xDC08,                 /* GSM 通知PHY退出静默工作模式 *//* _H2ASN_MsgChoice VOICE_GUPHY_FOREGROUND_REQ_STRU */

    /*====== CODEC->CODEC ======*/
    ID_VOICE_VOICE_ENC_REQ                            = 0xDD03,                   /* G/U编码消息,在上行DMA搬运完成时发送 */
    ID_VOICE_VOICE_RECORD_IND                         = 0xDD04,                   /* UMTS 上行DMA搬运启动消息,在3ms定时器中断中发送 */        /* _H2ASN_MsgChoice GPHY_VOICE_RECORD_IND_STRU */
    ID_VOICE_VOICE_PLAY_IND                           = 0xDD05,                   /* UMTS 下行语音播放,在6ms定时器中断中发送 */               /* _H2ASN_MsgChoice GPHY_VOICE_PLAY_IND_STRU */
    ID_VOICE_VOICE_UPDATE_REQ                         = 0xDD07,                   /* 声码器类型变化时,重新配置上下行处理 */                   /* _H2ASN_Skip */
    ID_VOICE_VOICE_DEC_REQ                            = 0xDD08,                   /* G/U解码消息,在下行DMA搬运完成时发送 */                   /* _H2ASN_Skip */
    ID_VOICE_VOICE_REMAP_IND                          = 0xDD0C,                   /* mmbuf搬运完成，通知voice remap */                       /* _H2ASN_Skip */
    ID_VOICE_VOICE_REQUEST_MMBUF_IND                  = 0xDD0D,                   /* voice remap完成，再次申请mmbuf */                       /* _H2ASN_Skip */

    /*lwx26324 add @20140327 for external modem，begin*/
    ID_VOICEPP_VOICEPP_MICIN_IND                      = 0xDD10,                 /* micin loop dma start msg */  /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_LINEIN_IND                     = 0xDD11,                 /* linein loop dma start msg */ /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_SPKOUT_IND                     = 0xDD12,                 /* spkout loop dma start msg */  /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_LINEOUT_IND                    = 0xDD13,                 /* lineout loop dma start msg */ /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_PROC_IND                       = 0xDD14,                 /* 启动上行数据搬运 */ /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_RXPROC_IND                     = 0xDD15,                 /* 下行数据算法处理 */ /* _H2ASN_Skip */
    ID_VOICEPP_VOICEPP_TXPROC_IND                     = 0xDD16,                 /* 上行数据算法处理 */ /* _H2ASN_Skip */
    /*lwx26324 add @20140327 for external modem，end*/ 

    /*====== UCOM->CODEC ======*/
    ID_UCOM_VOICE_SUSPEND_CMD                         = 0xCD09,                 /* 语音软件暂停、恢复消息，在G/U进行异系统切换过程中发送 */ /* _H2ASN_MsgChoice GUPHY_VOICE_SUSPEND_CMD_STRU */

    MSG_ID_BUTT                                                                  /* _H2ASN_Skip */
};
typedef VOS_UINT16 DSP_VOICE_MSG_ID_ENUM_UINT16;

enum RCM_VOICE_MSG_ID_ENUM
{
    /*====== CODEC->RCM ======*/
    ID_VOICE_RCM_CALL_STATE_IND         = 0xEF01,                               /* CODEC通知RCM进入静默工作模式的mode和modem */  /* _H2ASN_MsgChoice VOICE_RCM_CALL_STATE_IND_STRU */

    /*====== RCM->CODEC ======*/
    ID_RCM_VOICE_CALL_STATE_CNF         = 0xEF02,                               /* RCM回复CODEC */ /* _H2ASN_MsgChoice RCM_VOICE_CALL_STATE_CNF_STRU */

    ID_RCM_VOICE_MSG_ID_ENUM_BUTT                                               /* _H2ASN_Skip */                                           
};
typedef VOS_UINT16 RCM_VOICE_MSG_ID_ENUM_UINT16;



/* PHY向MED发送确认中成功或失败指示枚举 */
enum DSP_VOICE_RESULT_ENUM
{
    DSP_VOICE_RESULT_SUCC,
    DSP_VOICE_RESULT_FAIL,

    DSP_VOICE_RESULT_BUTT,
};
typedef VOS_UINT16 DSP_VOICE_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_VOICE_MODEM_ID_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : MODEM ID
*****************************************************************************/
enum RCM_VOICE_MODEM_ID_ENUM
{
    RCM_VOICE_MODEM_1                         = 0,                              /* MODEM0 */
    RCM_VOICE_MODEM_2                         = 1,                              /* MODEM1 */
    RCM_VOICE_MODEM_3                         = 2,                              /* MODEM2 */
    RCM_VOICE_MODEM_ID_BUTT
};
typedef VOS_UINT16  RCM_VOICE_MODEM_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : RCM_VOICE_CALL_STATE_ENUM_UINT16
 枚举说明  : modem Background or Active Call状态
             0:Active Call状态
             1:Background Call状态
*****************************************************************************/
enum RCM_VOICE_CALL_STATE_ENUM
{
    RCM_VOICE_CALL_ACTIVE           = 0,
    RCM_VOICE_CALL_BACKGROUND       = 1,
    RCM_VOICE_CALL_BUTT
};
typedef VOS_UINT16 RCM_VOICE_CALL_STATE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : GPHY_VOICE_CHANNEL_TYPE_ENUM_UINT16
 枚举说明  : TCH业务信道类型
*****************************************************************************/
enum GPHY_VOICE_CHANNEL_TYPE_ENUM
{
    GPHY_VOICE_CHANNEL_TYPE_TCH_FS          = 0,
    GPHY_VOICE_CHANNEL_TYPE_TCH_EFS         = 1,
    GPHY_VOICE_CHANNEL_TYPE_TCH_HS          = 2,
    GPHY_VOICE_CHANNEL_TYPE_TCH_AFS         = 3,
    GPHY_VOICE_CHANNEL_TYPE_TCH_AHS         = 4,

    GPHY_VOICE_CHANNEL_TYPE_BUTT
};
typedef VOS_UINT16 GPHY_VOICE_CHANNEL_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : GPHY_VOICE_TCHHS_SUB_CHANNEL_ENUM_UINT16
 枚举说明  : 半速率子信道
*****************************************************************************/
enum GPHY_VOICE_TCHHS_SUB_CHANNEL_ENUM
{
    GPHY_VOICE_TCHHS_SUB_CHANNEL_0          = 0,
    GPHY_VOICE_TCHHS_SUB_CHANNEL_1          = 1,

    GPHY_VOICE_TCH_SUB_CHANNEL_BUTT
};
typedef VOS_UINT16 GPHY_VOICE_TCHHS_SUB_CHANNEL_ENUM_UINT16;


/*****************************************************************************
 枚举名    : GPHY_VOICE_CRC_RESULT_ENUM_UINT16
 枚举说明  : CRC 校验结果
*****************************************************************************/
enum GPHY_VOICE_CRC_RESULT_ENUM
{
    GPHY_VOICE_CRC_RESULT_ERROR             = 0,
    GPHY_VOICE_CRC_RESULT_CORRECT           = 1,

    GPHY_VOICE_CRC_BUTT
};
typedef VOS_UINT16 GPHY_VOICE_CRC_RESULT_ENUM_UINT16;


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/
/*****************************************************************************
 实体名称  : WPHY_VOICE_SYNC_IND_STRU
 功能描述  : 语音业务启动后，WPHY在9ms中断发送该消息给CODEC进行时序同步指示消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD02*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* 保留*/
    VOS_UINT16                          uhwCfn;                                 /* 当前CFN */
    VOS_UINT16                          uhwSlotOffset;                          /* 同步消息偏移帧头位置的slot值 */
    VOS_UINT16                          uhwChipOffset;                          /* 同步消息偏移帧头位置的chip值 */
    VOS_UINT16                          uhwReserve2;
    VOS_UINT32                          uwTimeSlice;                            /* 发送时刻时戳 */
}WPHY_VOICE_SYNC_IND_STRU;

/*****************************************************************************
 实体名称  : WPHY_VOICE_RX_DATA_IND_STRU
 功能描述  : WPHY取出AMR码流后，进行解密，解密完后发送该消息给CODEC将数据发送过去
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwCfn;
    WPHY_VOICE_DATA_STRU                                                         /*_H2ASN_Skip*/
}WPHY_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_WPHY_TX_DATA_IND_STRU
 功能描述  : CODEC在上行数据OK后，发送该消息给WPHY将数据发送过去
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDB01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    WPHY_VOICE_DATA_STRU
}VOICE_WPHY_TX_DATA_IND_STRU;

/*****************************************************************************
 实体名称  : WPHY_VOICE_CELL_INFO_STRU
 功能描述  : W小区能量信息结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwCpichRscp;                           /* CPICH RSCP测量值 */
    VOS_INT16                           shwCpichEcN0;                           /* CPICH EcN0测量值 */
}WPHY_VOICE_CELL_INFO_STRU;

/*****************************************************************************
 实体名称  : WPHY_VOICE_CHANNEL_QUALITY_IND_STRU
 功能描述  : W物理层可维可测，上报小区信道质量
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDB01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwCellNum;                             /* 上报小区个数 */
    VOS_UINT16                          uhwServCellId;                          /* 服务小区对应的ID */
    VOS_UINT16                          uhwReserved;                            /* 保留字段，保证4字节对齐 */
    WPHY_VOICE_CELL_INFO_STRU           astCellInfo[WPHY_VOICE_WCDMA_MAX_CELL_NUM];
}WPHY_VOICE_CHANNEL_QUALITY_IND_STRU;

/*****************************************************************************
 实体名称  : WPHY_VOICE_BSD_CS_IND_STRU
 功能描述  : WPHY给CODEC发送W信道质量，用于BSD特性
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          uhwReserved;
    VOS_INT16                           shwCpichEcN0;                           /* CPICH Ec/N0，1/8dBm精度 */
    VOS_INT16                           shwCpichRscp;                           /* CPICH RSCP */
    VOS_UINT16                          uhwSIR;                                 /* 语音信道SIR平均值 */
    VOS_UINT16                          uhwCRCErrBlkNum;                        /* CRC错误的语音block数量 */
    VOS_UINT16                          uhwTotalCRCBlkNum;                      /* 语音block统计总量 */
    VOS_UINT16                          uhwErrPilotBitNum;                      /* Pilot bit错误数量 */
    VOS_UINT16                          uhwTotalPilotBitNum;                    /* Pilot bit统计总量 */
    VOS_UINT16                          uhwDCHOutOfSyncInd;                     /* DCH out of sync 指示*/
}WPHY_VOICE_BSD_CS_IND_STRU;


/*****************************************************************************
 实体名称  : GPHY_VOICE_UPDATE_PARA_CMD_STRU
 功能描述  : GPHY在初始情况和编码参数发生变化时发送该消息告诉CODEC进行编码参数更新
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD02*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    CODEC_ENUM_UINT16                   enCodecType;                            /*声码器类型: 0 AMR-NB, 1 EFR, 2 FR, 3 HR , 4 AMR-NB 5 AMR-WB*/
    CODEC_DTX_ENUM_UINT16               enDtxMode;                              /* DTX使能标志：0 不使能，1 使能*/
    VOS_UINT16                          enAmrMode;                              /* AMR编码速率模式, 如果是AMR-NB，取值从7-0分别对应8种不同的速率模式12.2-4.75；如果是AMR-WB，取值2、1、0，分别对应12.65、8.85、6.60*/
    CODEC_AMR_NSYNC_ENUM_UINT16         enAmrNsync;                             /*一般为0，切换到新的基站时，取12*/
}GPHY_VOICE_UPDATE_PARA_CMD_STRU;

/*****************************************************************************
 实体名称  : GPHY_VOICE_PLAY_IND_STRU
 功能描述  : GPHY发送该消息告诉CODEC启动下行语音播放
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD04*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwTimeSlice;                            /* 发送时刻时戳 */
}GPHY_VOICE_PLAY_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_GPHY_PLAY_CNF_STRU
 功能描述  : CODEC发送该消息回复GPHY的原语ID_VOICE_GPHY_PLAY_CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC04*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwRslt;                                 /*执行结果,0成功/1失败*/
}VOICE_GPHY_PLAY_CNF_STRU;

/*****************************************************************************
 实体名称  : GPHY_VOICE_RECORD_IND_STRU
 功能描述  : GPHY发送该消息告诉CODEC启动上行语音采集
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD05*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwTimeSlice;                            /* 发送时刻时戳 */
}GPHY_VOICE_RECORD_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_GPHY_RECORD_CNF_STRU
 功能描述  : CODEC发送该消息回复GPHY的原语ID_VOICE_GPHY_RECORD_CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC05*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwRslt;                                 /*执行结果,0成功/1失败*/
}VOICE_GPHY_RECORD_CNF_STRU;

/*****************************************************************************
 实体名称  : GPHY_VOICE_RX_DATA_IND_STRU
 功能描述  : GPHY将语音码流通过该消息发送给CODEC进行下行解码
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD01 */ /*_H2ASN_Skip*/
    CODEC_ENUM_UINT16                   enCodecType;                            /* 声码器类型: 0-AMR, 1-EFR, 2-FR, 3-HR */
    CODEC_BFI_ENUM_UINT16               enBfi;                                  /* 坏帧标志,HR/FR/EFR使用 0 dis 1 enable,bad*/
    CODEC_SID_ENUM_UINT16               enSid;                                  /* HR/FR/EFR使用 */
    CODEC_TAF_ENUM_UINT16               enTaf;                                  /* 同步标志,HR/FR/EFR使用 */
    CODEC_HR_UFI_ENUM_UINT16            enUfi;                                  /* 0-信道稳定, 1-信道不好, HR使用 */
    VOS_UINT16                          enAmrMode;                              /* AMR编码速率模式*/
    CODEC_AMR_TYPE_RX_ENUM_UINT16       enAmrFrameType;                         /* AMR帧类型, TX_SPEECH_GOOD/TX_SID_FIRST/TX_SID_UPDATA/TX_NO_DATA */
    VOS_UINT16                          puhwData[GPHY_VOICE_DATA_LEN];            /* AMR为重排前，其它为重排后的码流数据，按16bit紧凑排列（数据有效位最长为FR：260/16） */
    CODEC_FRAME_FACCH_ENUM_UINT16       enIsFrameFacch;
    VOS_UINT16                          uhwDtxSpeechState;                      /* 0代表speech,1代表DTX */
    GPHY_VOICE_CRC_RESULT_ENUM_UINT16   enCrcFlag;                              /* CRC标识, 0: crc_error, 1: crc_correct */
    VOS_UINT16                          uhwPber;                                /* Pber */
    VOS_UINT16                          uhwReserve;                             /* rsv项 */
} GPHY_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_GPHY_TX_DATA_IND_STRU
 功能描述  : CODEC完成语音编码后，发送该消息给GPHY将编码后码流数据发送过去
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC02 */ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* 保留 */
    CODEC_VAD_ENUM_UINT16               enVadFlag;                              /* VAD标志, 0-语音帧, 1-非语音帧, HR/FR/EFR时使用*/
    CODEC_SP_ENUM_UINT16                enSpFlag;                               /* Speech标志: 0为非语音帧，1为语音帧, HR/FR/EFR时使用*/
    CODEC_AMR_TYPE_TX_ENUM_UINT16       enAmrFrameType;                         /*上行AMR帧类型,TX_SPEECH_GOOD,TX_SPEECH_FIRST,TX_SID_UPDATA,TX_NODATA */
    VOS_UINT16                          enAmrMode;                              /* AMR编码速率 */
    VOS_UINT16                          auhwData[GPHY_VOICE_DATA_LEN];          /* AMR为重排后，其它为重排前的码流数据，按16bit紧凑排列（数据有效位最长为FR：260/16）*/
    CODEC_ENUM_UINT16                   enCodecType;                            /* 声码器类型: 0-AMR, 1-EFR, 2-FR, 3-HR, 5-AMRWB */
}VOICE_GPHY_TX_DATA_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_GPHY_SYNC_REQ_STRU
 功能描述  : CODEC发送该消息给GPHY进行时序同步请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC03*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
} VOICE_GPHY_SYNC_REQ_STRU;

/*****************************************************************************
 实体名称  : VOICE_GPHY_SET_CODEC_IND_STRU
 功能描述  : CODEC收到NAS配置声码器时发送该消息通知GPHY声码器配置事件
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC06*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* 保留字 */
} VOICE_GPHY_SET_CODEC_IND_STRU;

/*****************************************************************************
 实体名称  : GUPHY_VOICE_SUSPEND_CMD_STRU
 功能描述  : GU-PHY在2G3或3G2时发送该消息告诉CODEC暂停语音处理
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD08*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
} GUPHY_VOICE_SUSPEND_CMD_STRU;

/*****************************************************************************
 实体名称  : VOICE_GUPHY_BACKGROUND_REQ_STRU
 结构说明  : VOICE模块通知PHY进入静默工作模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserved;
} VOICE_GUPHY_BACKGROUND_REQ_STRU;

/*****************************************************************************
 实体名称  : PHY_CODEC_BACKGROUND_CNF_STRU
 结构说明  : PHY回复CODEC已进入静默工作模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserved[2];
} GUPHY_VOICE_BACKGROUND_CNF_STRU;

/*****************************************************************************
 实体名称  : VOICE_GUPHY_FOREGROUND_REQ_STRU
 结构说明  : VOICE模块通知PHY进入正常工作模式(退出静默模式)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserved;
} VOICE_GUPHY_FOREGROUND_REQ_STRU;

/*****************************************************************************
 实体名称  : GUPHY_VOICE_FOREGROUND_CNF_STRU
 结构说明  : PHY回复CODEC已进入正常工作模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserved[2];
} GUPHY_VOICE_FOREGROUND_CNF_STRU;

/*****************************************************************************
 实体名称  : GPHY_VOICE_SYNC_IND_STRU
 功能描述  : 语音业务启动后，GPHY在第12帧的0时隙送该消息给CODEC进行时序同步指示消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD10*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved1;                           /* 保留 */
    VOS_UINT32                          uwFn;                                   /* 帧号 */
    VOS_UINT32                          uwQb;                                   /* QB 0~4999 */
    VOS_UINT32                          uwTimeSlice;                            /* 发送时刻时戳 */
    VOS_UINT16                          uhwTsn;                                 /* 时隙号 0~7 */
    VOS_UINT16                          uhwChanCodeTime;                        /* 上行编码时间, 单位:0.1 ms */
    VOS_UINT16                          uhwChanDecodeTime;                      /* 下行译码时间, 单位:0.1 ms */

    GPHY_VOICE_CHANNEL_TYPE_ENUM_UINT16                     enChanType;         /* 信道类型 */
    GPHY_VOICE_TCHHS_SUB_CHANNEL_ENUM_UINT16                enSubChanNum;       /* 子信道号,半速率时有效 */

    VOS_UINT16                          uhwReserved2;                           /* 保留 */
}GPHY_VOICE_SYNC_IND_STRU;

/*****************************************************************************
 实体名称  : GPHY_VOICE_CHANNEL_QUALITY_IND_STRU
 功能描述  : GPHY给CODEC发送G信道质量，用于可维可测
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          uhwDTX;
    VOS_UINT16                          uhwRxlevFull;                            /* 信号强度+偏置(316) */
    VOS_UINT16                          uhwRxlevSub;                             /* 信号强度+偏置(316) */
    VOS_UINT16                          uhwFrmNumFull;                           /* FULL集的电平统计帧数 */
    VOS_UINT16                          uhwFrmNumSub;                            /* SUB集的电平统计帧数 */
    VOS_UINT16                          uhwErrBitsFull;                          /* FULL集的误码BIT数 */
    VOS_UINT16                          uhwErrBitsSub;                           /* SUB集的误码BIT数 */
    VOS_UINT16                          uhwTotalBitsFull;                        /* FULL集总的比特数 */
    VOS_UINT16                          uhwTotalBitsSub;                         /* SUB集总的比特数 */
    VOS_UINT16                          uhwRxLevVal;
    VOS_UINT16                          uhwMeanBep;
    VOS_UINT16                          uhwCvBep;
    VOS_UINT16                          uhwReserved;
}GPHY_VOICE_CHANNEL_QUALITY_IND_STRU;

/*****************************************************************************
 结构名    : VOICE_RCM_CALL_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CODEC通知RCM Voice 是否背景Call 状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_VOICE_MSG_ID_ENUM_UINT16                enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    CODEC_NET_MODE_ENUM_UINT16                  enModeID;                       /* 模式ID */
    RCM_VOICE_MODEM_ID_ENUM_UINT16              enModemID;                      /* modem ID */
    RCM_VOICE_CALL_STATE_ENUM_UINT16            enVoiceCallState;               /* voice state */
    VOS_UINT16                                  usRsv2;                         /* 保留字段 */
}VOICE_RCM_CALL_STATE_IND_STRU;

/*****************************************************************************
 结构名    : RCM_VOICE_CALL_STATE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RCM回CODEC Voice Call 消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    RCM_VOICE_MSG_ID_ENUM_UINT16                enMsgID;                        /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usRsv;                          /* 保留字段 */
    VOS_UINT16                                  usOPID;                         /* 操作标识 */
    VOS_UINT16                                  usRsv1;                         /* 保留字段 */
    CODEC_NET_MODE_ENUM_UINT16                  enModeID;                       /* 模式ID */
    RCM_VOICE_MODEM_ID_ENUM_UINT16              enModemID;                      /* modem ID */
    RCM_VOICE_CALL_STATE_ENUM_UINT16            enVoiceCallState;               /* voice state */
    VOS_UINT16                                  usRsv2;                         /* 保留字段 */
}RCM_VOICE_CALL_STATE_CNF_STRU;


/*****************************************************************************
 实体名称  : GPHY_VOICE_CHANNEL_QUALITY_IND_STRU
 功能描述  : GPHY给CODEC发送G信道质量，用于可维可测
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                          uhwChannelType;                         /* 信道类型 */
    VOS_UINT16                          uhwAssignRxTs;                          /* 业务时隙 */
    VOS_UINT16                          uhwRxlev;                               /* 信号强度 */
    VOS_UINT16                          uhwCIAverage;                           /* CI平均值 */
    VOS_UINT16                          uhwErrBitSub;                           /* SUB误bit数量 */
    VOS_UINT16                          uhwTotalBitSub;                         /* SUB bit统计总量 */
    VOS_UINT16                          uhwReserved;
}GPHY_VOICE_BSD_CS_IND_STRU;

/*****************************************************************************
 实体名称  : GPHY_VOICE_HO_START_REQ_STRU
 功能描述  : Handover切换的时候，需要给MED下发该消息告诉MED开始切换
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD10*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved1;                           /* 保留 */
    VOS_UINT32                          uwFn;                                   /* 帧号 */
    VOS_UINT32                          uwQb;                                   /* QB 0~4999 */
    VOS_UINT32                          uwTimeSlice;                            /* 发送时刻时戳 */
}GPHY_VOICE_HO_START_REQ_STRU;

/*****************************************************************************
 实体名称  : GPHY_VOICE_HO_Complete_REQ_STRU
 功能描述  : Handover切换结束，需要向MED下发该消息告诉MED切换结束
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD10*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved1;                           /* 保留 */
    VOS_UINT32                          uwFn;                                   /* 帧号 */
    VOS_UINT32                          uwQb;                                   /* QB 0~4999 */
    VOS_UINT32                          uwTimeSlice;                            /* 发送时刻时戳 */
}GPHY_VOICE_HO_Complete_REQ_STRU;

/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
/* 需要更改相应的ASN编码,去掉L方式,仅保留V方式 */
typedef struct
{
    DSP_VOICE_MSG_ID_ENUM_UINT16          enMsgID;            /* _H2ASN_MsgChoice_Export DSP_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          DSP_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_PHY_TRACE_MSG_DATA;

/* 协议消息结构*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_PHY_TRACE_MSG_DATA              stMsgData;
}VoicePhyTrace_MSG;

#endif                                                     /* _H2ASN_Skip */


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

#endif /* end of phycodecinterface.h */
