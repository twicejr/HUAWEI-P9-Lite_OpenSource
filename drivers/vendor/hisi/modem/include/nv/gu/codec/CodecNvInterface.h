

#ifndef __CODECNVINTERFACE_H__
#define __CODECNVINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 语音声学处理NV参数数组单个ID数组长度 单位:int16 */
#define CODEC_PP_NV_ARRAY_ID_LEN  (200)

/* 语音声学处理NV参数数组ID个数  */
#define CODEC_PP_NV_ARRAY_ID_NUM  (3)

/* 音频声学处理NV参数数组单个ID数组长度 单位:int16 */
#define AUDIO_PP_NV_ARRAY_ID_LEN  (200)

/* 音频声学处理NV参数数组ID个数  */
#define AUDIO_PP_NV_ARRAY_ID_NUM  (3)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 实体名称  : PP_AUDIO_PCM_OMP_NV_STRU
 功能描述  : 频响补偿NV项维护结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          enPcmCompEnable;                        /* 配置项 使能标志 */
    VOS_INT16                           shwCompGain;                            /* 配置项 施加增益（左移） */
    VOS_INT16                           shwM;                                   /* 配置项 滤波器的长度 */
    VOS_INT16                           shwReserved;
    VOS_INT16                           ashwCoef[128];                          /* 补偿滤波参数 */
} PP_AUDIO_PCM_COMP_NV_STRU;

/*****************************************************************************
 结构名    : NB_MAXVOLLEVEL_NV_STRU
 结构说明  : NB_MaxVolLevel NV结构体,ID en_NV_Item_MaxVolLevel 12298
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwNBMaxVolLevel;/*Range:[1,20]*/
}NB_MAXVOLLEVEL_NV_STRU;

/*****************************************************************************
 结构名    : HEADSETPARA_AUDIO_NV_STRU
 结构说明  : HeadSetPara_Audio NV结构体,ID en_NV_HeadSetPara_Audio 12299
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   uwDownLrOutvol;
    VOS_UINT32                   uwUpRinl2vol;
    VOS_UINT32                   uwUpRl2mnbst;
    VOS_UINT32                   uwFilter;
}HEADSETPARA_AUDIO_NV_STRU;

/*****************************************************************************
 结构名    : HANDSETPARA_AUDIO_NV_STRU
 结构说明  : HandSetPara_Audio NV结构体,ID en_NV_HandSetPara_Audio 12300
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   uwDownROutvol;
    VOS_UINT32                   uwDownROpgavol;
    VOS_UINT32                   uwDownOut4attn;
    VOS_UINT32                   uwUpLinl2vol;
    VOS_UINT32                   uwUpLl2mnbst;
    VOS_UINT32                   uwFilter;
}HANDSETPARA_AUDIO_NV_STRU;

/*****************************************************************************
 结构名    : HANDFREEPARA_AUDIO_NV_STRU
 结构说明  : HandFreePara_Audio NV结构体,ID en_NV_HandFreePara_Audio 12301
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   uwDownLrOpgavol;
    VOS_UINT32                   uwDownSpkattn;
    VOS_UINT32                   uwDownSpkvol;
    VOS_UINT32                   uwDownDcgain;
    VOS_UINT32                   uwDownAcgain;
    VOS_UINT32                   uwUpLinl2vol;
    VOS_UINT32                   uwUpLl2mnbst;
    VOS_UINT32                   uwFilter;
}HANDFREEPARA_AUDIO_NV_STRU;

/*****************************************************************************
 结构名    : PCVOICE_AUDIO_NV_STRU
 结构说明  : PCVoice_Audio NV结构体,ID en_NV_PCVoice_Audio 12302
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   uwDownLrOutvol;
    VOS_UINT32                   uwUpRinl2vol;
    VOS_UINT32                   uwUpRl2mnbst;
    VOS_UINT32                   uwFilter;
}PCVOICE_AUDIO_NV_STRU;

/*****************************************************************************
 结构名    : ERRLOGENABLE_NV_STRU
 结构说明  : ErrLogEnable NV结构体,ID en_NV_Item_ErrLog_Enable 12304
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwErrLogEnable;
}ERRLOGENABLE_NV_STRU;

/*****************************************************************************
 结构名    : NV_MED_PARA_ERRLOG_STRU
 结构说明  : NV_MED_Para_ErrLog NV结构体,ID en_NV_Item_ErrLog_DataStru 12305
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwMaxDmaMicReset;
    VOS_UINT16                   uhwMaxDmaSpkReset;
    VOS_UINT16                   uhwMaxDecIntLost;
    VOS_UINT16                   uhwMaxBbpDataNone;
    VOS_UINT16                   uhwMaxBbpDataBad;
    VOS_UINT16                   uhwMaxDecipherLost;
    VOS_UINT16                   uhwMaxBfiFrames;
    VOS_UINT16                   uhwMaxSidFrames;
    VOS_UINT16                   uhwMaxInterpolate;
    VOS_UINT16                   uhwMaxRingBufFull;
}NV_MED_PARA_ERRLOG_STRU;

/*****************************************************************************
 结构名    : HOOKNV_STRU
 结构说明  : HookNv NV结构体,ID en_NV_Item_Hook_Enable_Target 12306
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwHookEnable;
    VOS_UINT16                   uhwHookTarget;
}HOOKNV_STRU;

/*****************************************************************************
 结构名    : WB_MAXVOLLEVEL_STRU
 结构说明  : WB_MaxVolLevel NV结构体,ID en_NV_WB_MaxVolLevel 12317
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwWBMaxVolLevel;/*Range:[1,20]*/
}WB_MAXVOLLEVEL_STRU;

/*****************************************************************************
 结构名    : NV_CLVL_VOLUM_STRU
 结构说明  : NV_CLVL_VOLUM NV结构体,ID en_NV_CLVL_VOLUM 12323
*****************************************************************************/
typedef struct
{
    VOS_INT16                   shwHandSetVolValue;
    VOS_INT16                   shwHandFreeVolValue;
    VOS_INT16                   shwCarFreeVolValue;
    VOS_INT16                   shwEarphoneVolValue;
    VOS_INT16                   shwBlueToothVolValue;
    VOS_INT16                   shwPcVoiceVolValue;
    VOS_INT16                   shwRsv[10];
}NV_CLVL_VOLUM_STRU;

/*****************************************************************************
 结构名    : CODEC_VOICE_HOOK_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音数据勾取控制结构体,ID en_NV_VoiceTraceCfg 12324 相关
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* 使能项 */
    VOS_UINT16                          uhwTarget;/*Range:[0,2047]*/            /* 语音数据上报勾取点，低0-10位有效，有效值为0-2047 */
}CODEC_VOICE_HOOK_CONFIG_STRU;

/*****************************************************************************
 结构名    : CODEC_LOOP_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 编码环回控制结构体,ID en_NV_VoiceTraceCfg 12324 相关
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* 使能项 */
    VOS_UINT16                          uhwType;/*Range:[0,2]*/                 /* 环回类型: 1. DMA环回，2. 编码前环回，3. 编码后环回 */
}CODEC_LOOP_CONFIG_STRU;

/*****************************************************************************
 结构名    : CODEC_ERRLOG_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Errlog控制结构体,ID en_NV_VoiceTraceCfg 12324 相关
             注意，如增删该结构体里各门限的个数或者内容，必须同步更新:
             1. 枚举CODEC_ERRLOG_EVENTS_ENUM
             2. 门限结构体CODEC_ERRLOG_THD_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* 使能项 */
    VOS_INT16                           shwReserved;                            /* 保留位 */
    VOS_UINT16                          uhwMaxDmaMicReset;/*Range:[1,65535]*/   /* Mic DMA 连续重启的上限 */
    VOS_UINT16                          uhwMaxDmaSpkReset;/*Range:[1,65535]*/   /* Spk DMA 连续重启的上限 */
    VOS_UINT16                          uhwMaxDecIntLost;/*Range:[1,65535]*/    /* WCDMA 译码中断丢失上限 */
    VOS_UINT16                          uhwMaxBBPDataNone;/*Range:[1,65535]*/   /* WCDMA BBP 上报数据为空的上限 */
    VOS_UINT16                          uhwMaxBBPDataBad;/*Range:[1,65535]*/    /* WCDMA BBP 上报数据为坏帧 */
    VOS_UINT16                          uhwMaxDecipherLost;/*Range:[1,65535]*/  /* WCDMA 解码序列丢失上限 */
    VOS_UINT16                          uhwMaxBFIFrames;/*Range:[1,65535]*/     /* GSM 收到 BFI 帧上限 */
    VOS_UINT16                          uhwMaxSIDFrames;/*Range:[1,65535]*/     /* 数据帧为SID 的上限 */
    VOS_UINT16                          uhwMaxInterpolate;/*Range:[1,65535]*/   /* PC Voice 插帧数目上限 */
    VOS_UINT16                          uhwMaxRingBufFull;/*Range:[1,65535]*/   /* PC Voice Ring Buffer 满的次数上限 */
}CODEC_ERRLOG_CONFIG_STRU;

/*****************************************************************************
 结构名    : CODEC_NV_PARA_VOICE_TRACE_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音TRACE配置NV项结构体,ID en_NV_VoiceTraceCfg 12324
*****************************************************************************/
typedef struct
{
    CODEC_VOICE_HOOK_CONFIG_STRU          stVoiceHookCfg;                       /* 语音数据勾取控制结构体 */
    CODEC_LOOP_CONFIG_STRU                stLoopCfg;                            /* 编码环回控制结构体 */
    CODEC_ERRLOG_CONFIG_STRU              stErrlogCfg;                          /* Errlog控制结构体 */
}CODEC_NV_PARA_VOICE_TRACE_CFG_STRU;

/*****************************************************************************
 结构名    : CODEC_LOG_HOOK_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 日志勾取配置,ID en_NV_HifiTraceCfg 12325 相关
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* 使能项 */
    VOS_UINT16                          uhwLevel;/*Range:[0,2]*/                /* LOG上报级别，0. INFO级别，1. WARNING级别，2. ERROR级别 */
}CODEC_LOG_HOOK_CONFIG_STRU;

/*****************************************************************************
 结构名    : CODEC_MSG_HOOK_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息勾取配置,ID en_NV_HifiTraceCfg 12325 相关
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;/*Range:[0,1]*/               /* 使能项 */
    VOS_INT16                           shwReserved;                            /* 保留位 */
}CODEC_MSG_HOOK_CONFIG_STRU;

/*****************************************************************************
 结构名    : CODEC_NV_PARA_HIFI_TRACE_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HIFI TRACE配置NV项结构体,ID en_NV_HifiTraceCfg 12325
*****************************************************************************/
typedef struct
{
    CODEC_LOG_HOOK_CONFIG_STRU            stLogHookCfg;                         /* 语音数据勾取控制结构体 */
    CODEC_MSG_HOOK_CONFIG_STRU            stMsgHookCfg;                         /* 编码环回控制结构体 */
}CODEC_NV_PARA_HIFI_TRACE_CFG_STRU;

/*****************************************************************************
 结构名    : CODEC_NV_PARA_SIO_VOICE_MASTER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : voice SIO主从配置NV项结构体,ID en_NV_Item_SIO_Voice_Master 12326
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwIsPcmMaster;/*Range:[0,1]*/         /* voice SIO是否为master模式 */
}CODEC_NV_PARA_SIO_VOICE_MASTER_STRU;

/*****************************************************************************
 结构名    : CODEC_AUDIO_HOOK_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 音频数据勾取控制结构体，ID en_NV_AudioTraceCfg 12327相关
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;                              /* 使能项 */
    VOS_UINT16                          uhwTarget;                              /* 音频数据上报勾取点，低0-10位有效，有效值为0-2047 */
}CODEC_AUDIO_HOOK_CONFIG_STRU;

/*****************************************************************************
 结构名    : CODEC_NV_PARA_AUDIO_TRACE_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 音频TRACE配置NV项结构体，ID ID en_NV_AudioTraceCfg 12327
*****************************************************************************/
typedef struct
{
    CODEC_AUDIO_HOOK_CONFIG_STRU          stAudioHookCfg;                         /* 音频数据勾取控制结构体 */
}CODEC_NV_PARA_AUDIO_TRACE_CFG_STRU;

/*****************************************************************************
 结构名    : CODEC_NV_PARA_SIO_AUDIO_MASTER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : audio SIO主从配置NV项结构体,ID en_NV_Item_SIO_Audio_Master 12328
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           uhwIsPcmMaster;/*Range:[0,1]*/         /* audio SIO是否为master模式 */
}CODEC_NV_PARA_SIO_AUDIO_MASTER_STRU;

/*****************************************************************************
 结构名    : CODEC_NV_PARA_HIFI_POWEROFF_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HIFI下电使能/关闭配置NV项结构体,ID en_NV_HifiPowerOffCfg 12333
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwPowerOffEnable;/*Range:[0,1]*/              /* HIFI下电是否使能 */
    VOS_UINT16                   uhwRsv;
    VOS_UINT32                   uwWITimeThd;                                   /* 进入低功耗模式最大空闲时长 */
    VOS_UINT32                   uwPDTimeThd;                                   /* 下电最大空闲时长 */
}CODEC_NV_PARA_HIFI_POWEROFF_CFG_STRU;

/*****************************************************************************
 结构名    : CODEC_NV_PARA_HIFI_WATCHDOG_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HIFI Watchdog配置NV项结构体,ID en_NV_HifiWatchDogCfg 12334
*****************************************************************************/
typedef struct
{
    VOS_UINT16                   uhwWDEnable;/*Range:[0,1]*/                    /* HIFI watchdog是否使能 */
    VOS_UINT16                   uhwRsv;
    VOS_UINT32                   uwWDTimeoutLen;                                /* HIFI watchdog timeout length */
}CODEC_NV_PARA_HIFI_WATCHDOG_CFG_STRU;

/*****************************************************************************
 结构名    : CODEC_PP_NV_STRU
 结构说明  : PP模块各模式ID结构体,ID 12335 - 12376
*****************************************************************************/
typedef struct
{
    VOS_INT16                      ashwNv[CODEC_PP_NV_ARRAY_ID_LEN];
}CODEC_PP_NV_STRU;

/*****************************************************************************
 结构名    : PHY_MIC_NUM_NV_STRU
 结构说明  : en_NV_PHY_MIC_NUM NV结构体,ID en_NV_PHY_MIC_NUM 12349
*****************************************************************************/
typedef struct
{
    VOS_INT16                         hwPhyMicNum;
    VOS_INT16                         hwReserv;
}PHY_MIC_NUM_NV_STRU;

/*****************************************************************************
 实体名称  : VOICE_SMART_PA_CFG_STRU
 功能描述  : Smart PA控制模块，参数由NV读取,ID en_NV_SmartPACfg 12350
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          enEnable;
    VOS_UINT16                          uhwIsMaster;
    VOS_UINT16                          uhwValidChannel;/*Range:[0,1]*/         /* 0表示左声道有效，1表示右声道有效 */
    VOS_UINT16                          auhwReserve[3];
} VOICE_SMART_PA_CFG_NV_STRU;

/*****************************************************************************
 实体名称  : PP_AUDIO_PCM_TxCOMP_NV_STRU
 功能描述  : 上行频响补偿NV项维护结构体,ID en_NV_AudioTxCompCfg 12351
*****************************************************************************/
typedef struct
{
    PP_AUDIO_PCM_COMP_NV_STRU           stTxCompCfg;
} PP_AUDIO_PCM_TxCOMP_NV_STRU;

/*****************************************************************************
 实体名称  : PP_AUDIO_PCM_RxCOMP_NV_STRU
 功能描述  : 下行频响补偿NV项维护结构体,ID en_NV_AudioRxCompCfg 12352
*****************************************************************************/
typedef struct
{
    PP_AUDIO_PCM_COMP_NV_STRU           stRxCompCfg;
} PP_AUDIO_PCM_RxCOMP_NV_STRU;

/*****************************************************************************
 结构名    : AUDIO_PP_NV_STRU
 结构说明  : PP模块各模式ID结构体,ID 12379 - 12384
*****************************************************************************/
typedef struct
{
    VOS_INT16                           ashwNv[AUDIO_PP_NV_ARRAY_ID_LEN];       /* 音频NV项 */
}AUDIO_PP_NV_STRU;

/*****************************************************************************
 结构名    : EN_FORTE_DATA_STRU
 结构说明  : Forte使用的NV项
*****************************************************************************/
typedef struct
{
    VOS_INT16                           usData[256];
} EN_FORTE_DATA_STRU;

/*****************************************************************************
 结构名    : EN_OPENDSP_CONFIG_STRU
 结构说明  : OpenDSP配置项
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucProfile;                              /* 配置选择 */
    VOS_UINT8                           ucReserve[3];
} EN_OPENDSP_CONFIG_STRU;

/*****************************************************************************
 结构名    : EN_MBDRC_DATA_STRU
 结构说明  : 该结构用于第三方算法的MBDRC使用的NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           usData[2048];
} EN_MBDRC_DATA_STRU;

/*****************************************************************************
 结构名    : DIAG_CHANNEL_QUALITY_STRU
 结构说明  : 该结构用于语音故障检测模块中判断当前小区信号好坏的NV项
*****************************************************************************/
typedef struct
{
    VOS_INT16               shwIsIgnoreChanQa;                                  /* 检测时是否忽略信号好坏状况。0表示考虑，1表示忽略 */
    VOS_INT16               shwGsmChanQaThd;                                    /* GSM下判断小区信号好坏的阈值 */
    VOS_INT16               shwUmtsChanQaThd;                                   /* W下判断小区信号好坏的阈值 */
    VOS_INT16               shwTdChanQaThd;                                     /* Td下判断小区信号好坏的阈值 */
    VOS_INT16               shwImsChanQaThd;                                    /* IMS下判断小区信号好坏的阈值 */
}DIAG_CHANNEL_QUALITY_STRU;

/*****************************************************************************
 结构名    : DIAG_LINEIN_STRU
 结构说明  : 该结构用于检测LineIn处语音故障的NV项
*****************************************************************************/
typedef struct
{
    VOS_INT16               shwDiagTime ;                                       /* 统计时间，单位(s) */
    VOS_INT16               shwGoodFrmPercentThd;                               /* Q15 (0.8*32767) */
    VOS_INT16               ahwReserve[8];
}DIAG_LINEIN_STRU;

/*****************************************************************************
 结构名    : VOICE_DIAG_NV_STRU
 结构说明  : 该结构用于语音故障检测模块的NV项
*****************************************************************************/
typedef struct
{
    VOS_INT16                 shwEnable;                                        /* 每一个bit位控制一个监测点 */
    DIAG_CHANNEL_QUALITY_STRU stChanQaPara;
    DIAG_LINEIN_STRU          stLineInPara;
    VOS_INT16                 ashwLineOut[10];
    VOS_INT16                 ashwCodecIn[10];
    VOS_INT16                 ashwCodecOut[10];
    VOS_INT16                 ashwMicIn[10];
    VOS_INT16                 ashwSpeakOut[10];
    VOS_INT16                 ashwAecIn[10];
    VOS_INT16                 ashwAecRef[10];
    VOS_INT16                 ashwReserve[170];
} VOICE_DIAG_NV_STRU;

/*****************************************************************************
 结构名    : VOICE_JB_NV_STRU
 结构说明  : 该结构用于控制JB的设置，当前主要用第一个参数，控制是否使能AJB
*****************************************************************************/
typedef struct
{
    VOS_UINT16                 uhwAjbEnable;                                     /* 是否使能AJB,0/1:否/是 */
    VOS_UINT16                 uhwInitBuf;                                       /* 初始深度,单位ms	*/
    VOS_UINT16                 uhwAjbMinBuf;                                     /* 最小深度,单位ms */
    VOS_UINT16                 uhwAjbMaxBuf;                                     /* 最大深度,单位ms */
    VOS_UINT16                 auhwReserve[12];
} VOICE_JB_NV_STRU;

/*****************************************************************************
 结构名    : DTMF_GEN_CHAN_PARAM_STRU
 结构说明  : DTMF发送算法模块的初始化输入参数值结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                uhwTimeOn;        /* 号码有效发送时长 */
    VOS_UINT16                usTimeOff;        /* 号码静音间隔时长 */
    VOS_INT16                 shwHFreqLvl;      /* 高频电平（单位：dBm）*/
    VOS_INT16                 shwLFreqLvl;      /* 低频电平（单位：dBm）*/
    VOS_UINT16                uhwFrmLen;        /* 主调度帧时长 */
    VOS_UINT16                uhwReserve;
    VOS_UINT32                uwReserve;
}DTMF_GEN_CHAN_PARAM_STRU;

/*****************************************************************************
 结构名    : DTMF_GEN_PARAM_STRU
 结构说明  : DTMF发送模块使用的NV项
*****************************************************************************/
typedef struct
{
    VOS_UINT16                uhwEnable;         /* DTMF发送模块使能开关 */
    VOS_UINT16                uhwReserve;
    DTMF_GEN_CHAN_PARAM_STRU  stGenChanPara;
}DTMF_GEN_PARAM_STRU;

/****************************************************************************
 结构名    : DTMF_GEN_PARAM_STRU
 结构说明  : DTMF发送模块标准类配置参数结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                uhwStandard;       /*(0:国标 / 非0:典型ITU-T Q.24)*/
    VOS_UINT16                uhwTlkOffLvl;      /*(抗语音等级:0~3, 大于等于4取缺省等级0)*/
}DTMF_DET_STD_CFG_STRU;

/*****************************************************************************
 结构名    : DTMF_DET_BASIC_STRU
 结构说明  : DTMF检测模块基本国标指标NV项
*****************************************************************************/
typedef struct
{
    /* 基本国标指标类 */
    VOS_INT16                 shwThrshLevlH;              /* 高频电平门限 */
    VOS_INT16                 shwThrshLevlL;              /* 低频电平门限 */
    VOS_UINT16                uhwONTime;                  /* 可靠接收ON时长 */
    VOS_UINT16                uhwOFFTime;                 /* 可靠接收OFF时长 */
    VOS_UINT16                uhwIntvlTime;               /* 容许的信号间断时长 */
    VOS_INT16                 shwTwistLevl;               /* 电平差门限 */
    VOS_UINT16                uhwdeltaMust;               /* 可靠接收频偏门限 */
    VOS_UINT16                uhwdeltaReject;             /* 拒绝接收频偏门限 */
    VOS_UINT16                uhwdeltaFactor;             /* 频偏判决点的位置 */
    VOS_UINT16                uhwReserve;
}DTMF_DET_BASIC_STRU;

/*****************************************************************************
 结构名    : DTMF_DET_TALKOFF_STRU
 结构说明  : DTMF检测模块抗语音特性使能开关类NV项
*****************************************************************************/
typedef struct
{
    /* 抗语音特性使能开关类 */
    VOS_UINT16                uhwTalkoffSwitch;         /* 抗语音总开关 */
    VOS_UINT16                uhwTDSwitch;              /* 时域稳定性开关 */
    VOS_UINT16                uhwTwistDEVSwitch;        /* 电平差稳定性开关 */
    VOS_UINT16                uhwSNRSwitch;             /* 信噪比开关 */
    VOS_UINT16                uhwIntvlSwitch;           /* 信号间断状态识别开关 */
    VOS_UINT16                uhwECSwitch;              /* EC状态识别开关 */
    VOS_UINT16                uhwLongTimSwitch;         /* 长时信号判决开关 */

    /* 信噪比参数类 */
    VOS_UINT16                uhwSnrBotmK;              /* 随信号幅度变化的信噪比门限比例因子 */
    VOS_UINT16                uhwFreqSeg[5];            /* 信噪比划分频率段 */
    VOS_UINT16                uhwSNRSeg[6];             /*不同频率段的信噪比门限 */

    /* 松弛的国标指标类 */
    VOS_UINT16                uhwdeltaDialTone;         /* 拨号音识别频偏容许范围 */
    VOS_UINT16                uhwdeltaRelax;            /* 再松弛的频偏 */
    VOS_UINT16                uhwLevlRelax;             /* 再松弛的电平门限 */
    VOS_UINT16                uhwTwistRelax;            /* 再松弛的电平差门限 */

    VOS_INT16                 shwECTimConv;              /* EC连续收敛的帧数 */
    VOS_INT16                 shwlgONTime;               /* 长时状态时长门限 */
    VOS_INT16                 shwTwistDEV;               /* 电平差稳定性参数 */
}DTMF_DET_TALKOFF_STRU;

/*****************************************************************************
 结构名    : DTMF_DET_PARAM_STRU
 结构说明  : DTMF检测模块配置参数
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          uhwEnable;                              /* DTMF检测模块使能开关 */
    VOS_UINT16                          uhwParamFlag;                           /* 配置参数类型，0为标准，1为自定义 */
    DTMF_DET_STD_CFG_STRU               stDetStdCfg;                            /* 国标参数配置项 */
    DTMF_DET_BASIC_STRU                 stDetBasic;
    DTMF_DET_TALKOFF_STRU               stDetTalkOff;
}DTMF_DET_PARAM_STRU;

/*****************************************************************************
 结构名    : VOICE_DTMF_CFG_NV_STRU
 结构说明  : DTMF模块使用的NV项
*****************************************************************************/
typedef struct
{
    DTMF_DET_PARAM_STRU                 stDetCfgPara;                           /* DTMF检测模块配置参数 */
    DTMF_GEN_PARAM_STRU                 stGenCfgPara;                           /* DTMF发送模块配置参数 */
    VOS_UINT16                          uhwReserve[4];
}VOICE_DTMF_CFG_NV_STRU;

/*****************************************************************************
  7 消息定义
*****************************************************************************/



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

#endif /* end of CodecNvInterface.h */

