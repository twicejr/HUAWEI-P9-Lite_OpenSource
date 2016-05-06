/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VcCodecInterface.h
  版 本 号   : 初稿
  作    者   : zhoujun /z40661
  生成日期   : 2010年3月24日
  最近修改   :
  功能描述   : VC和CODEC模块间的接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年3月24日
    作    者   : zhoujun /z40661
    修改内容   : 创建文件

******************************************************************************/

#ifndef __VCCODECINTERFACE_H__
#define __VCCODECINTERFACE_H__

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
#define VC_VOICE_MAX_MSD_LEN (140)                                              /* ECALL最小数据集(MSD)的最大长度 单位:byte */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum VC_VOICE_MSG_ID_ENUM
{
    /*  ARM->HIFI */
    ID_VC_VOICE_BASE            = 0x9400,
    ID_VC_VOICE_START_REQ       = 0x9402,       /*启动语音处理*/                /* _H2ASN_MsgChoice VCVOICE_START_REQ_STRU */
    ID_VC_VOICE_STOP_REQ        = 0x9403,       /*语音软件停止运行*/            /* _H2ASN_MsgChoice VCVOICE_STOP_REQ_STRU */
    ID_VC_VOICE_SET_DEVICE_REQ  = 0x9404,       /*语音软件参数设置*/            /* _H2ASN_MsgChoice VCVOICE_SET_DEVICE_REQ_STRU */
    ID_VC_VOICE_SET_VOLUME_REQ  = 0x9405,       /*语音软件更新音量*/            /* _H2ASN_MsgChoice VCVOICE_SET_VOLUME_REQ_STRU */
    ID_VC_VOICE_SET_CODEC_REQ   = 0x9407,       /*更新信源编解码参数*/          /* _H2ASN_MsgChoice VCVOICE_SET_CODEC_REQ_STRU */
    ID_VC_VOICE_FOREGROUND_REQ  = 0x940A,       /*设置为前台通路*/              /* _H2ASN_MsgChoice VCVOICE_FOREGROUND_REQ_STRU */
    ID_VC_VOICE_BACKGROUND_REQ  = 0x940B,       /*设置为后台通路*/              /* _H2ASN_MsgChoice VCVOICE_BACKGROUND_REQ_STRU */
    ID_VC_VOICE_GROUND_QRY      = 0x940C,       /*查询通路状态 */               /* _H2ASN_MsgChoice VCVOICE_GROUND_QRY_STRU */
    ID_VC_VOICE_LOOP_REQ        = 0x940D,       /* 设置环回 */                  /* _H2ASN_MsgChoice VCVOICE_LOOP_REQ_STRU */
    ID_VC_VOICE_SET_MSD_REQ             = 0x940E,       /*ECAL数据参数设置*/            /* _H2ASN_MsgChoice VCVOICE_SET_MSD_REQ_STRU */
    ID_VC_VOICE_SET_ECALLCFG_REQ        = 0x940F,       /*ECAL配置参数设置*/            /* _H2ASN_MsgChoice VCVOICE_SET_ECALLCFG_REQ_STRU */
    ID_VC_VOICE_SO_CTRL_ORDER_IND   = 0x9415,       /*CDMA下控制SO的状态和速率*/    /* _H2ASN_MsgChoice VCVOICE_SO_CTRL_ORDER_IND_STRU */
    ID_VC_VOICE_SO_CTRL_MSG_IND     = 0x9416,       /*CDMA下控制SO的状态和速率*/    /* _H2ASN_MsgChoice VCVOICE_SO_CTRL_MSG_IND_STRU */
//    ID_VC_VOICE_SO_CTRL_SEND_SPECIAL_PACKETS = 0x9417,  /*VC不在conversation状态，需要声码器发特殊码流，该接口待与网侧交流后确定*/

    /*  HIFI->ARM */
    ID_VOICE_VC_BASE            = 0x4900,
    ID_VOICE_VC_START_CNF       = 0x4902,       /*响应VC_VOICE_START_REQ*/      /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_STOP_CNF        = 0x4903,       /*响应VC_VOICE_STOP_REQ*/       /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_DEVICE_CNF  = 0x4904,       /*响应VC_VOICE_SET_DEVICE_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_VOLUME_CNF  = 0x4905,       /*响应VC_VOICE_SET_VOLUME_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_CODEC_CNF   = 0x4907,       /*响应VC_VOICE_SET_CODEC_REQ*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_FOREGROUND_CNF  = 0x490A,       /*响应VC_VOICE_FOREGROUND_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_BACKGROUND_CNF  = 0x490B,       /*响应VC_VOICE_BACKGROUND_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_GROUND_RSP      = 0x490C,       /*响应VC_VOICE_GROUND_QRY*/     /* _H2ASN_MsgChoice VCVOICE_GROUND_RSP_STRU */
    ID_VOICE_VC_LOOP_CNF        = 0x490D,       /* 设置环回响应 */              /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_ECALLCFG_CNF        = 0x490F,      /*响应ID_VC_VOICE_SET_ECALLCFG_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_ECALL_TRANS_STATUS_NTF  = 0x4910,      /*回复ECALL传送状态*/           /* _H2ASN_MsgChoice VCVOICE_ECALL_TRANS_STATUS_NTF_STRU */
    ID_VOICE_VC_START_SEND_MSD_IND      = 0x4930,      /*要求NAS重新发送MSD数据*/           /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */

    ID_VOICE_VC_DTMF_IND                = 0x4911,       /* 主动上报DTMF号码检测结果 */              /* _H2ASN_MsgChoice VOICEVC_DTMF_IND_STRU */
    ID_VOICE_VC_AL_ACK_REPORT_IND       = 0x4914,

    /* CODEC->CODEC */
    ID_VOICE_VOICE_ECALL_UPDATE_IND     = 0xDD0A,      /*Ecall数据更新*/                     /* _H2ASN_MsgChoice VOICE_VOICE_ECALL_UPDATE_IND_STRU */
    ID_VOICE_VOICE_ECALL_PULLSTART_IND  = 0xDD0B,      /*Ecall使用旧的Ecall数据启动MSD流程*/ /* _H2ASN_MsgChoice VOICE_VOICE_ECALL_PULLSTART_IND_STRU */

    VC_VOICE_MSG_ID_BUTT
};
typedef VOS_UINT16 VC_VOICE_MSG_ID_ENUM_UINT16;


enum VC_VOICE_DTMF_MSG_ID_ENUM
{
    ID_VC_VOICE_DTMF_BASE               = 0x9420,
    ID_VC_VOICE_START_DTMF_REQ          = 0x9421,       /* VC通知VOICE开始DTMF发送和播放 */ /* _H2ASN_MsgChoice VCVOICE_START_DTMF_REQ_STRU */
    ID_VOICE_VC_START_DTMF_CNF          = 0x4921,       /* 响应VC_VOICE_START_DTMF_REQ*/      /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_DTMF_OVER_IND           = 0x4922,       /* VOICE通知VC已完成DTMF号码发送*/    /* _H2ASN_MsgChoice VOICEVC_DTMF_OVER_IND_STRU */
    ID_VC_VOICE_STOP_DTMF_REQ           = 0x9423,       /* VC通知VOICE中断DTMF发送和播放*/    /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_STOP_DTMF_CNF           = 0x4923,       /* 响应ID_VC_VOICE_STOP_DTMF_REQ*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VC_VOICE_SET_DTMF_DETECT_REQ     = 0x9424,       /* 响应ID_VC_VOICE_SET_DTMF_DETECT_REQ*/  /* _H2ASN_MsgChoice VC_VOICE_DTMF_DETECT_REQ_STRU */
    ID_VOICE_VC_SET_DTMF_DETECT_CNF     = 0x4924,       /* 响应ID_VOICE_VC_SET_DTMF_DETECT_CNF*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VC_VOICE_DTMF_MSG_ID_MAX,
};
typedef VOS_UINT16 VC_VOICE_DTMF_MSG_ID_ENUM_UINT16;


enum VCVOICE_NET_MODE_ENUM
{
    VCVOICE_NET_MODE_GSM         = 0,
    VCVOICE_NET_MODE_WCDMA,
    VCVOICE_NET_MODE_TDSCDMA,
    VCVOICE_NET_MODE_IMS_EUTRAN,
    VCVOICE_NET_MODE_CDMA,
    VCVOICE_NET_MODE_BUTT
};
typedef VOS_UINT16 VCVOICE_NET_MODE_ENUM_UINT16;

enum VCVOICE_TYPE_ENUM
{
    VCVOICE_TYPE_AMR      = 0,                                                  /* amr */
    VCVOICE_TYPE_EFR,                                                           /* enhanced full rate */
    VCVOICE_TYPE_FR,                                                            /* full rate */
    VCVOICE_TYPE_HR,                                                            /* half rate */
    VCVOICE_TYPE_AMR2,                                                          /* amr2 */
    VCVOICE_TYPE_AMRWB,                                                         /* AMR-WB */
    VCVOICE_TYPE_G711,                                                          /* G711 */
    VCVOICE_TYPE_EVRC,                                                          /* EVRC */
    VCVOICE_TYPE_EVRCB,                                                         /* EVRCB */
    VCVOICE_TYPE_BUTT                                                           /* invalid value */
};
typedef VOS_UINT16  VCVOICE_TYPE_ENUM_UINT16;

enum VCVOICE_EXECUTE_RSLT_ENUM
{
    VCVOICE_EXECUTE_RSLT_SUCC = 0,                                              /* 0 成功 */
    VCVOICE_EXECUTE_RSLT_FAIL,                                                  /* 1 失败 */
    VCVOICE_EXECUTE_RSLT_NULL_PTR,                                              /* 2 空指针 */
    VCVOICE_EXECUTE_RSLT_PARA_ERR,                                              /* 3 参数错误 */
    VCVOICE_EXECUTE_RSLT_STATE_ERR,                                             /* 4 状态错误 */
    VCVOICE_EXECUTE_RSLT_UNKNOWN_MSG,                                           /* 5 未知消息 */

    VCVOICE_EXECUTE_RSLT_BUTT
};
typedef VOS_UINT16  VCVOICE_EXECUTE_RSLT_ENUM_UINT16;

enum VCVOICE_VOLUME_TARGET_ENUM
{
    VCVOICE_VOLUME_TARGET_UP = 0,                                               /* 0 上行 */
    VCVOICE_VOLUME_TARGET_DOWN,                                                 /* 1 下行 */

    VCVOICE_VOLUME_TARGET_BUTT
};
typedef VOS_UINT16  VCVOICE_VOLUME_TARGET_ENUM_UINT16;

enum VCVOICE_WORK_TYPE_ENUM
{
    VCVOICE_WORK_TYPE_NORMAL = 0,                                               /* 0 正常工作模式 */
    VCVOICE_WORK_TYPE_TEST,                                                     /* 1 测试模式 */
    VCVOICE_WORK_TYPE_ECALL,                                                    /* 2 ECALL模式 */
    VCVOICE_WORK_TYPE_TTY_FULL,                                                 /* 3 TTY FULL模式 */
    VCVOICE_WORK_TYPE_TTY_VCO,                                                  /* 4 TTY VCO模式 */
    VCVOICE_WORK_TYPE_TTY_HCO,                                                  /* 5 TTY HCO模式 */
    VCVOICE_WORK_TYPE_BUTT
};
typedef VOS_UINT16  VCVOICE_WORK_TYPE_ENUM_UINT16;

/* 通话模式枚举 */
enum VCVOICE_DEV_MODE_ENUM
{
    VCVOICE_DEV_MODE_HANDSET                = 0,                                /* 手持模式 */
    VCVOICE_DEV_MODE_HANDFREE,                                                  /* 免提模式 */
    VCVOICE_DEV_MODE_CARFREE,                                                   /* 车载免提模式 */
    VCVOICE_DEV_MODE_HEADSET,                                                   /* 耳机模式 */
    VCVOICE_DEV_MODE_BLUETOOTH,                                                 /* 蓝牙模式 */
    VCVOICE_DEV_MODE_PCVOICE,                                                   /* PC-VOICE模式 */
    VCVOICE_DEV_MODE_HEADPHONE,                                                 /* 不带耳机MIC的耳机通话 */
    VCVOICE_DEV_MODE_SUPER_HANDFREE,                                            /* 超级免提 */
    VCVOICE_DEV_MODE_SMART_TALK,                                                /* 智音通话 */
    VCVOICE_DEV_MODE_BUTT
};
typedef VOS_UINT16  VCVOICE_DEV_MODE_ENUM_UINT16;

/* 通路状态 */
enum VCVOICE_GROUND_ENUM
{
    VCVOICE_GROUND_FOREGROUND               = 0,                                /* 前台模式 */
    VCVOICE_GROUND_BACKGROUND,                                                  /* 后台模式 */
    VCVOICE_GROUND_INVALID,                                                     /* 非法 */
    VCVOICE_GROUND_BUTT
};
typedef VOS_UINT16  VCVOICE_GROUND_ENUM_UINT16;

/* 环回状态 */
enum VCVOICE_LOOP_ENUM
{
    VCVOICE_LOOP_STOP                       = 0,                                /* 退出环回模式 */
    VCVOICE_LOOP_START,                                                         /* 进入环回模式 */
    VCVOICE_LOOP_BUTT
};
typedef VOS_UINT16  VCVOICE_LOOP_ENUM_UINT16;

enum VCVOICE_ECALL_TRANS_STATUS_ENUM
{
    VCVOICE_ECALL_MSD_TRANSMITTING_START,                                      /* 当前MSD数据已经开始发送 */
    VCVOICE_ECALL_MSD_TRANSMITTING_SUCCESS,                                    /* 当前MSD数据已经发送成功 */
    VCVOICE_ECALL_MSD_TRANSMITTING_FAIL,                                       /* 当前MSD数据已经发送失败 */
    VCVOICE_ECALL_PSAP_MSD_REQUIRETRANSMITTING,                                /* PSAP要求更新MSD数据 */
    VCVOICE_ECALL_MSD_TRANSMITTING_STOP,                                       /* 当前MSD数据已经停止发送 */
    VCVOICE_ECALL_TRANS_STATUS_BUTT
};
typedef VOS_UINT8  VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8;

enum VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM
{
    VCVOICE_ECALL_CAUSE_WAIT_PSAP_TIME_OUT,                                    /* 等待PSAP的传输指示超时 */
    VCVOICE_ECALL_CAUSE_MSD_TRANSMITTING_TIME_OUT,                             /* MSD数据传输超时 */
    VCVOICE_ECALL_CAUSE_WAIT_AL_ACK_TIME_OUT,                                  /* 等待应用层的确认超时 */
    VCVOICE_ECALL_CAUSE_UNSPECIFIC_ERROR,                                      /* 其他异常错误 */
    VCVOICE_ECALL_CAUSE_BUTT
};
typedef VOS_UINT8  VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8;

enum VCVOICE_ECALL_MSD_MODE_ENUM
{
    VCVOICE_ECALL_MSD_MODE_TRANSPARENT,                                         /* MSD数据为透传模式*/
    VCVOICE_ECALL_MSD_MODE_BUTT
};
typedef VOS_UINT16  VCVOICE_ECALL_MSD_MODE_ENUM_UINT16;

enum VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM
{
    VCVOICE_ECALL_MSD_VOICE_NOT_ABANDON,                                        /* MSD数据传输过程带提示音*/
    VCVOICE_ECALL_MSD_VOICE_ABANDON,                                            /* MSD数据传输过程不带提示音*/
    VCVOICE_ECALL_MSD_VOICE_BUTT
};
typedef VOS_UINT16  VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM_UINT16;

/* CDMA下平均速率控制枚举，ORDQ值的前3个bit */
enum VCVOICE_ORDQ_3MSBS_ENUM
{
    VCVOICE_ORDQ_ZERO = 0,                              /* 不做降速率处理 */
    VCVOICE_ORDQ_FOURTH,                                /* 紧接着的4个语音包中，最后一个包降为半速率 */
    VCVOICE_ORDQ_HALF,                                  /* 紧接着的2个语音包中，后一个包降为半速率 */
    VCVOICE_ORDQ_THREE_FOURTHS,                         /* 紧接着的4个语音包中，后3个包降为半速率 */
    VCVOICE_ORDQ_FULL,                                  /* 紧接着的一个语音包降为半速率*/
    VCVOICE_ORDQ_BUTT
};
typedef VOS_UINT8 VCVOICE_ORDQ_3MSBS_ENUM_UINT8;

/* CDMA下平均速率控制枚举 */
enum VCVOICE_EVRC_RATE_REDUC_ENUM
{
    VCVOICE_EVRC_RATE_REDUC_ZERO = 0,                   /* 不做降速率处理 */
    VCVOICE_EVRC_RATE_REDUC_FOURTH,                     /* 紧接着的4个语音包中，最后一个包降为半速率 */
    VCVOICE_EVRC_RATE_REDUC_HALF,                       /* 紧接着的2个语音包中，后一个包降为半速率 */
    VCVOICE_EVRC_RATE_REDUC_THREE_FOURTHS,              /* 紧接着的4个语音包中，后3个包降为半速率 */
    VCVOICE_EVRC_RATE_REDUC_FULL,                       /* 紧接着的一个语音包降为半速率*/
    VCVOICE_EVRC_RATE_REDUC_BUTT
};
typedef VOS_UINT8 VCVOICE_EVRC_RATE_REDUC_ENUM_UINT8;

/* CDMA下平均速率控制枚举 */
enum VCVOICE_EVRCB_RATE_REDUC_ENUM
{
    VCVOICE_EVRCB_RATE_REDUC_830K = 0,                  /* 降速率为8.3kbps */
    VCVOICE_EVRCB_RATE_REDUC_757K = 1,
    VCVOICE_EVRCB_RATE_REDUC_664K = 2,
    VCVOICE_EVRCB_RATE_REDUC_618K = 3,
    VCVOICE_EVRCB_RATE_REDUC_582K = 4,
    VCVOICE_EVRCB_RATE_REDUC_545K = 5,
    VCVOICE_EVRCB_RATE_REDUC_508K = 6,
    VCVOICE_EVRCB_RATE_REDUC_400K = 7,
    VCVOICE_EVRCB_RATE_REDUC_BUTT
};
typedef VOS_UINT8 VCVOICE_EVRCB_RATE_REDUC_ENUM_UINT8;

enum VCVOICE_MOBILE_TO_MOBILE_ENUM
{
    VCVOICE_MOBILE_TO_MOBILE_OFF = 0,
    VCVOICE_MOBILE_TO_MOBILE_ON  = 1,                   /* 值为1，需要将声码器输出暂停1s */
    VCVOICE_MOBILE_TO_MOBILE_BUTT
};
typedef VOS_UINT8 VCVOICE_MOBILE_TO_MOBILE_ENUM_UINT8;

enum VCVOICE_INTI_CODEC_ENUM
{
    VCVOICE_INTI_CODEC_DISABLE = 0,
    VCVOICE_INTI_CODEC_ENABLE  = 1,                     /* 值为1，重新初始化声码器 */
    VCVOICE_INTI_CODEC_BUTT
};
typedef VOS_UINT8 VCVOICE_INTI_CODEC_ENUM_UINT8;

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
 结构名    : VCCODEC_START_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 启动语音处理消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 */
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;                                 /* 通讯服务制式：0 G；1 W */
    VCVOICE_TYPE_ENUM_UINT16            enCodecType;                            /* 声码器类别：0 AMR；1 EFR；2 FR；3 HR；4 AMR2； 5 AMRWB */
    VCVOICE_WORK_TYPE_ENUM_UINT16       enWorkType;                             /* 工作模式:0 正常工作模式 1: 测试模式 */
    VOS_UINT16                          usReserve2;                             /* 保留 */
}VCVOICE_START_REQ_STRU;


/*****************************************************************************
 结构名    : VCCODEC_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止语音处理消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
}VCVOICE_STOP_REQ_STRU;


/*****************************************************************************
 结构名    : VCVOICE_SET_DEVICE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音设备参数结构体
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
    VCVOICE_DEV_MODE_ENUM_UINT16        usDeviceMode;                           /* 语音设备：0 手持；1 手持免提；2 车载免提；3 耳机；4 蓝牙； 5 PC-VOICE  */
    VOS_UINT16                          usReserve2;                             /* 保留 */
}VCVOICE_SET_DEVICE_REQ_STRU;

/*****************************************************************************
 结构名    : VCCODEC_SET_VOLUME_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求语音软件更新音量参数消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
    VCVOICE_VOLUME_TARGET_ENUM_UINT16   enVolTarget;
    VOS_INT16                           sVolValue;
}VCVOICE_SET_VOLUME_REQ_STRU;

/*****************************************************************************
 结构名    : VCCODEC_SET_CODEC_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 请求更新信源编解码参数参数消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;                                 /* 通讯服务制式：0 G；1 W */
    VCVOICE_TYPE_ENUM_UINT16            enCodecType;                            /* 声码器类别：0 AMR；1 EFR；2 FR；3 HR; 4 AMR2; 5 AMRWB */
}VCVOICE_SET_CODEC_REQ_STRU;

/*****************************************************************************
 结构名    : VCVOICE_FOREGROUND_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : VC模块请求MED将该路电话激活, 上下行语音输入输出恢复
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
} VCVOICE_FOREGROUND_REQ_STRU;

/*****************************************************************************
 结构名    : VCVOICE_BACKGROUND_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : VC模块请求MED将该路电话去激活，上行进入了静音状态，下行的语音输出通路断开
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
} VCVOICE_BACKGROUND_REQ_STRU;

/*****************************************************************************
 结构名    : VCVOICE_GROUND_QRY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : VC模块查询当前通路状态(前台/后台)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
} VCVOICE_GROUND_QRY_STRU;

/*****************************************************************************
 结构名    : VCVOICE_GROUND_RSP_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音软件回复当前通路状态
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* 保留 */
    VCVOICE_GROUND_ENUM_UINT16          enState;                                /* 当前状态 */
    VOS_UINT16                          usReserve2;                             /* 保留 */
} VCVOICE_GROUND_RSP_STRU;

/*****************************************************************************
 结构名    : VCCODEC_OP_RSLT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 对VC消息操作响应的消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 */
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt;                              /* 执行结果 */
    VOS_UINT16                          usReserve2;
}VCVOICE_OP_RSLT_STRU;

/*****************************************************************************
 结构名    : VCVOICE_LOOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 环回模式请求
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 */
    VCVOICE_LOOP_ENUM_UINT16            enMode;                                 /* 当前状态 */
    VOS_UINT16                          usReserve2;
}VCVOICE_LOOP_REQ_STRU;

/*****************************************************************************
 结构名    : VOICEVC_DTMF_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音软件主动上报DTMF检测结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usDtmfCode;                             /* DTMF号码值 */
} VOICEVC_DTMF_IND_STRU;

/*****************************************************************************
 结构名    : VC_VOICE_DTMF_DETECT_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 语音软件主动上报DTMF检测使能设置
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16 usMessageId;
    VOS_UINT16 usReserve;
    VOS_UINT32 ulDtmfDetectOn;  /*0 off, 1 on */
}VC_VOICE_DTMF_DETECT_REQ_STRU;

/*****************************************************************************
 结构名    : VCVOICE_ECALL_TRANS_STATUS_NTF_STRU
 结构说明  : MED模块通知VC，当前的传输状态
 1.日    期   : 2014年3月23日
   作    者   : y00241934
   修改内容   : 新增，为支持eCall功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* 保留 */
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8       enEcallTransStatus ;            /* 当前的传输状态 */
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enEcallTransFailCause ;         /* ECALL的传输失败原因 */
    VOS_UINT16                                  usReserve2;                     /* 保留 */
    VOS_UINT32                                  ulTimeWindow;                   /* 可配置时间窗 */
}VCVOICE_ECALL_TRANS_STATUS_NTF_STRU;

/*****************************************************************************
 结构名    : VCVOICE_SET_MSD_REQ_STRU
 结构说明  : VC模块通过该消息，将MSD数据发送到MED
 1.日    期   : 2014年3月23日
   作    者   : y00241934
   修改内容   : 新增，为支持eCall功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* 保留 */
    VOS_UINT32                                  ulMsdLen ;                      /* MSD数据的长度 */
    VOS_UINT8                                   aucMsd[VC_VOICE_MAX_MSD_LEN];   /* MSD数据内容 */
} VCVOICE_SET_MSD_REQ_STRU;

/*****************************************************************************
 结构名    : VCVOICE_SET_ECALLCFG_REQ_STRU
 结构说明  : VC模块通过该消息，将ECALL配置发送到MED
 1.日    期   : 2014年3月24日
   作    者   : y00241934
   修改内容   : 新增，为支持eCall功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* 保留 */
    VCVOICE_ECALL_MSD_MODE_ENUM_UINT16          enMsdMode;                      /* 单板获取MSD数据模式 0:透传 */
    VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM_UINT16 enNoVoice;                      /* MSD数据传输过程中是否有语音数据 0:有语音 1:无语音 */
} VCVOICE_SET_ECALLCFG_REQ_STRU;

/*****************************************************************************
 结构名    : VOICE_VOICE_ECALL_UPDATE_IND_STRU
 结构说明  : ECALL状态更新
 1.日    期   : 2014年3月23日
   作    者   : y00241934
   修改内容   : 新增，为支持eCall功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* 保留 */
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8       enEcallTransStatus ;            /* 当前的传输状态 */
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enEcallTransFailCause ;         /* ECALL的传输失败原因 */
    VOS_UINT8                                   aucReserve2[2];                 /* 保留 */
}VOICE_VOICE_ECALL_UPDATE_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_VOICE_ECALL_PULLSTART_IND_STRU
 功能描述  : 使用原有MSD数据启动eCall
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved;
}VOICE_VOICE_ECALL_PULLSTART_IND_STRU;

/*****************************************************************************
 结构名    : VOICEVC_AL_ACK_REPORT_IND_STRU
 结构说明  : ECALL AL ACK上报
 1.日    期   : 2014年3月23日
   作    者   : y00241934
   修改内容   : 新增，为支持eCall功能
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgName;                      /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserve1;                     /* 保留 */
    VOS_UINT32                                  ulTimeStamp;
    VOS_UINT8                                   ucAlAckValue;
    VOS_UINT8                                   aucReserve2[3];
} VOICEVC_AL_ACK_REPORT_IND_STRU;


/*****************************************************************************
 结构名    : VCVOICE_SO_CTRL_ORDER_IND_STRU
 协议表格  : 协议C.S0014-D_v3.0_EVRC   2.2.2.1 小节
 ASN.1描述 :
 结构说明  : VC收到空口消息Service Option Control Orders,
             需要通知VOICE初始化声码器或调整速率
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgName;                                  /* 原语类型 */ /*_H2ASN_Skip*/
    VCVOICE_TYPE_ENUM_UINT16        enCodecType;
    VOS_UINT8                       ucORDQ;
    VOS_UINT8                       ucReserve[3];                               /* 保留 */
}VCVOICE_SO_CTRL_ORDER_IND_STRU;

/*****************************************************************************
 结构名    : SO_CTRL_MSG_CODEC_STRU
 协议表格  : 协议C.S0014-D_v3.0_EVRC   2.2.2.2小节和2.4.1.2小节
 ASN.1描述 :
 结构说明  :  空口消息Service Option Control Messages对语音的控制结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                  ucRateReduc;          /* 速率控制，EVRC:值为0~4    EVRCB:值为0~7 */
    VOS_UINT8                                  ucReserved;           /**/
    VCVOICE_MOBILE_TO_MOBILE_ENUM_UINT8        ucMobileToMobile;     /* 值为1时，需要在声码器初始化后将下行语音暂停1s*/
    VCVOICE_INTI_CODEC_ENUM_UINT8              ucInitCodec;          /* 初始化声码器标志位 */
}SO_CTRL_MSG_CODEC_STRU;

/*****************************************************************************
 结构名    : VCVOICE_SO_CTRL_MSG_IND_STRU
 协议表格  : 协议C.S0014-D_v3.0_EVRC   2.2.2.2小节和2.4.1.2小节
 ASN.1描述 :
 结构说明  :  VC收到空口消息Service Option Control Messages, 需要通知
              VOICE初始化声码器或调整速率
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                      usMsgName;                                  /* 原语类型 */ /*_H2ASN_Skip*/
    VCVOICE_TYPE_ENUM_UINT16        enCodecType;
    SO_CTRL_MSG_CODEC_STRU          stSoCtrlMsg;
}VCVOICE_SO_CTRL_MSG_IND_STRU;

/*****************************************************************************
 结构名    : VC_VOICE_START_DTMF_REQ_STRU
 ASN.1描述 :
 结构说明  : VC通知VOICE开始DTMF发送和播放
*****************************************************************************/
typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usDtmfCode;                     /*发送的码字*/
    VOS_UINT16                      usLocalPlayOn;                  /*是否同时进行本地播放*/
    VOS_UINT16                      usInBand;                       /*是否带内发送*/
    VOS_UINT16                      usDtmfTimeOn;                   /*发送时长，单位:ms*/
    VOS_UINT16                      usDtmfTimeOff;                  /*间隔时长，单位:ms*/
}VCVOICE_START_DTMF_REQ_STRU;

/*****************************************************************************
 结构名    : VOICEVC_STOP_DTMF_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : VOICE通知VC DTMF号码发送和播放完成
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
    VOS_UINT32                      ulResult;  /*0 success, others error code */
}VOICEVC_STOP_DTMF_IND_STRU;

/*****************************************************************************
 结构名    : VCVOICE_STOP_DTMF_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : VC通知VOICE中断DTMF发送和播放
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
}VCVOICE_STOP_DTMF_REQ_STRU;

/*****************************************************************************
 结构名    : VOICEVC_DTMF_OVER_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : VOICE通知VC已完成DTMF发送和播放
*****************************************************************************/
typedef struct {
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgName;
    VOS_UINT16                      usReserve;
    VOS_UINT32                      ulResult;  /*0 success, others error code */
}VOICEVC_DTMF_OVER_IND_STRU;




/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
/* 需要更改相应的ASN编码,去掉L方式,仅保留V方式 */
typedef struct
{
    VC_VOICE_MSG_ID_ENUM_UINT16         enMsgID;            /* _H2ASN_MsgChoice_Export VC_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          VC_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_VC_TRACE_MSG_DATA;

/* 协议消息结构*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_VC_TRACE_MSG_DATA               stMsgData;
}VoiceVcTrace_MSG;

#endif                                                     /* _H2ASN_Skip */

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

#endif /* end of VcCodecInterface.h */
