/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CodecInterface.h
  版 本 号   : 初稿
  作    者   : 苏庄銮 59026
  生成日期   : 2011年6月16日
  最近修改   :
  功能描述   : CODEC子系统公共头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年6月16日
    作    者   : 苏庄銮 59026
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CODECINTERFACE_H__
#define __CODECINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "VcCodecInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define HIFI_TASK_NUM                   (4)                                     /* HiFi操作系统支持任务个数 */
#define HIFI_INTR_NUM                   (32)                                    /* HiFi系统中断个数         */
#define VOICE_MAX_HOOK_LEN              (640)                                   /* 语音最大钩取数据长度，单位2 Byte */
#define AUDIO_MAX_HOOK_LEN              (3840)                                  /* 音频最大钩取数据长度，单位2 Byte，暂定 */
#define WPHY_VOICE_AMR_SUBFRAME_NUM     (3)                                     /* W物理层与CODEC交互的语音数据子帧个数 */
#define WPHY_VOICE_AMR_FRAME_LEN        (16)                                    /* W物理层与CODEC交互的语音数据长度,单位32Bit,上下行长度一致 */

/*WPHY_CODEC_DATA_STRU结构含义如下
uhwQualityIdx   --AMR帧质量标志, 0表示
auhwLen         --依次存放A/B/C子流的长度，以BIT为单位
auwData         --依次存放A/B/C子流数据，ABC子流分别32BIT对齐*/
#define WPHY_VOICE_DATA_STRU                                                      \
    CODEC_AMR_FQI_QUALITY_ENUM_UINT16       enQualityIdx;                         \
    VOS_UINT16                              auhwLen[WPHY_VOICE_AMR_SUBFRAME_NUM]; \
    VOS_UINT32                              auwData[WPHY_VOICE_AMR_FRAME_LEN];

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum VOICE_VOICE_MSG_ID_ENUM
{
    ID_VOICE_VOICE_TX_PP_REQ          = 0xDD30,           /* 单板测试使用, 用于触发上行PP处理 */
    ID_VOICE_VOICE_RX_PP_REQ          = 0xDD31,           /* 单板测试使用, 用于触发下行PP处理 */
    VOICE_VOICE_MSG_ID_BUTT
};
typedef VOS_UINT16 VOICE_VOICE_MSG_ID_ENUM_UINT16;

/*****************************************************************************
 枚举名    : UCOM_RET_ENUM
 枚举说明  : 消息及函数执行结果
*****************************************************************************/
enum UCOM_RET_ENUM
{
    UCOM_RET_SUCC                       = VOS_OK,                               /*成功*/
    UCOM_RET_FAIL                       = VOS_ERR,                              /*失败*/
    UCOM_RET_NUL_PTR                    = 2,                                    /*空指针*/
    UCOM_RET_ERR_PARA                   = 3,                                    /*参数错误*/
    UCOM_RET_ERR_STATE                  = 4,                                    /*状态错误*/
    UCOM_RET_ERR_MSG                    = 5,                                    /*未知消息*/
    UCOM_RET_ERR_NOMEM                  = 6,                                    /*空间不足*/
    UCOM_RET_FUNC_DISABLE               = 7,                                    /*功能不支持*/
    UCOM_RET_SEND_FAIL                  = 8,                                    /*消息发送失败*/
    UCOM_RET_MSG_DELAY                  = 9,                                    /*消息延时超时*/
    UCOM_RET_BUTT
};
typedef VOS_UINT16 UCOM_RET_ENUM_UINT16;

/* 开关量枚举 */
enum CODEC_SWITCH_ENUM
{
    CODEC_SWITCH_OFF                      = 0,
    CODEC_SWITCH_ON,
    CODEC_SWITCH_BUTT
};
typedef VOS_UINT16  CODEC_SWITCH_ENUM_UINT16;

/* 输入输出枚举 */
enum CODEC_INOUT_ENUM
{
    CODEC_INOUT_DEFAULT                   = 0,                                    /* default:TxIn=SIO;TxOut=UL;RxIn=DL;RxOut=SIO */
    CODEC_INOUT_SOUND,                                                            /* SOUND合成, reserve */
    CODEC_INOUT_DATA,                                                             /* 数据接口, reserve  */
    CODEC_INOUT_BUTT
};
typedef VOS_UINT16  CODEC_INOUT_ENUM_UINT16;

/* 网络制式枚举 */
enum CODEC_NET_MODE_ENUM
{
    CODEC_NET_MODE_G                      = VCVOICE_NET_MODE_GSM,               /* G网络制式 */
    CODEC_NET_MODE_W                      = VCVOICE_NET_MODE_WCDMA,             /* W网络制式 */
    CODEC_NET_MODE_TD                     = VCVOICE_NET_MODE_TDSCDMA,           /* TD网络制式 */
    CODEC_NET_MODE_L                      = VCVOICE_NET_MODE_IMS_EUTRAN,        /* Lte网络制式 */
    CODEC_NET_MODE_C                      = VCVOICE_NET_MODE_CDMA,              /* CDMA网络制式 */
    CODEC_NET_MODE_BUTT                   = VCVOICE_NET_MODE_BUTT
};
typedef VOS_UINT16  CODEC_NET_MODE_ENUM_UINT16;

/* 声码器类型枚举 */
enum CODEC_ENUM
{
    CODEC_AMR                       = VCVOICE_TYPE_AMR,
    CODEC_EFR                       = VCVOICE_TYPE_EFR,
    CODEC_FR                        = VCVOICE_TYPE_FR,
    CODEC_HR                        = VCVOICE_TYPE_HR,
    CODEC_AMR2                      = VCVOICE_TYPE_AMR2,
    CODEC_AMRWB                     = VCVOICE_TYPE_AMRWB,
    CODEC_G711                      = VCVOICE_TYPE_G711,
    CODEC_EVRC                      = VCVOICE_TYPE_EVRC,
    CODEC_EVRCB                     = VCVOICE_TYPE_EVRCB,
    CODEC_BUTT                      = VCVOICE_TYPE_BUTT
};
typedef VOS_UINT16  CODEC_ENUM_UINT16;

/* AMR速率模式 */
enum CODEC_AMR_RATE_MODE_ENUM
{
    CODEC_AMR_RATE_MODE_475K              = 0,
    CODEC_AMR_RATE_MODE_515K,
    CODEC_AMR_RATE_MODE_590K,
    CODEC_AMR_RATE_MODE_670K,
    CODEC_AMR_RATE_MODE_740K,
    CODEC_AMR_RATE_MODE_795K,
    CODEC_AMR_RATE_MODE_102K,
    CODEC_AMR_RATE_MODE_122K,
    CODEC_AMR_RATE_MODE_BUTT
};
typedef VOS_UINT16  CODEC_AMR_RATE_MODE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_DTX_ENUM
 功能描述  : DTX取值定义
*****************************************************************************/
enum CODEC_DTX_ENUM
{
    CODEC_DTX_DISABLE               = 0,                                    /* DTX不使能 */
    CODEC_DTX_ENABLE                = 1,                                    /* DTX使能   */
    CODEC_DTX_BUTT
};
typedef VOS_UINT16 CODEC_DTX_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_VAD_ENUM
 功能描述  : EFR,HR,FR VAD flag取值定义, 参见3GPP TS 46.081
*****************************************************************************/
enum CODEC_VAD_ENUM
{
    CODEC_VAD_SILENCE               = 0,                                    /* 检测为静音 */
    CODEC_VAD_SPEECH                = 1,                                    /* 检测为语音 */
    CODEC_VAD_BUTT
};
typedef VOS_UINT16 CODEC_VAD_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_SP_ENUM
 功能描述  : EFR,HR,FR SP flag取值定义, 参见3GPP TS 46.081
*****************************************************************************/
enum CODEC_SP_ENUM
{
    CODEC_SP_SID                    = 0,                                    /* 输出SID帧    */
    CODEC_SP_SPEECH                 = 1,                                    /* 输出SPEECH帧 */
    CODEC_SP_BUTT
};
typedef VOS_UINT16 CODEC_SP_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_BFI_ENUM
 功能描述  : EFR,HR,FR 坏帧标志bfi,ufi取值定义, 参见3GPP TS 46.081, 46.041
*****************************************************************************/
enum CODEC_BFI_ENUM
{
    CODEC_BFI_NO                    = 0,                                    /* 好帧 */
    CODEC_BFI_YES                   = 1,                                    /* 坏帧 */
    CODEC_BFI_BUTT
};
typedef VOS_UINT16 CODEC_BFI_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_SID_ENUM
 功能描述  : EFR,HR,FR SID flag取值定义, 参见3GPP TS 46.041
*****************************************************************************/
enum CODEC_SID_ENUM
{
    CODEC_SID_SPEECH                = 0,                                    /* 语音帧        */
    CODEC_SID_ACCEPT                = 1,                                    /* 可接受的SID帧 */
    CODEC_SID_VALID                 = 2,                                    /* 合法的SID帧   */
    CODEC_SID_BUTT
};
typedef VOS_UINT16 CODEC_SID_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_TAF_ENUM
 功能描述  : EFR,HR,FR TAF取值定义, 参见3GPP TS 46.081, 46.041
*****************************************************************************/
enum CODEC_TAF_ENUM
{
    CODEC_TAF_NONE                  = 0,                                    /* 非时间对齐 */
    CODEC_TAF_ALIGNED               = 1,                                    /* 时间对齐, 应该接收到SID */
    CODEC_TAF_BUTT
};
typedef VOS_UINT16 CODEC_TAF_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_HR_UFI_ENUM
 功能描述  : HR UFI取值定义, 0-信道稳定, 1-信道不好
*****************************************************************************/
enum CODEC_HR_UFI_ENUM
{
    CODEC_HR_UFI_GOOD               = 0,                                    /* 信道稳定 */
    CODEC_HR_UFI_BAD                = 1,                                    /* 信道不好 */
    CODEC_HR_UFI_BUTT
};
typedef VOS_UINT16 CODEC_HR_UFI_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMR_FORMAT_ENUM
 功能描述  : AMR码流格式定义, 参见3GPP TS 26.101
*****************************************************************************/
enum CODEC_AMR_FORMAT_ENUM
{
    CODEC_AMR_FORMAT_IF1              = 0,                                      /* IF1码流格式,UMTS下使用 */
    CODEC_AMR_FORMAT_BITS             = 1,                                      /* GSM-AMR码流格式 */
    CODEC_AMR_FORMAT_IMS              = 2,                                      /* IMS码流格式 */
    CODEC_AMR_FORMAT_BUTT
};
typedef VOS_UINT16 CODEC_AMR_FORMAT_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMR_FRM_TYPE_ENUM
 功能描述  : AMR IF帧类型, 参见3GPP TS 26.101 Table 1a
*****************************************************************************/
enum CODEC_AMR_FRM_TYPE_ENUM
{
    CODEC_AMR_FRM_TYPE_475K         = 0,
    CODEC_AMR_FRM_TYPE_515K         = 1,
    CODEC_AMR_FRM_TYPE_590K         = 2,
    CODEC_AMR_FRM_TYPE_670K         = 3,
    CODEC_AMR_FRM_TYPE_740K         = 4,
    CODEC_AMR_FRM_TYPE_795K         = 5,
    CODEC_AMR_FRM_TYPE_102K         = 6,
    CODEC_AMR_FRM_TYPE_122K         = 7,
    CODEC_AMR_FRM_TYPE_AMR_SID      = 8,
    CODEC_AMR_FRM_TYPE_GSM_EFR_SID  = 9,
    CODEC_AMR_FRM_TYPE_TDMA_EFR_SID = 10,
    CODEC_AMR_FRM_TYPE_PDC_EFR_SID  = 11,
    CODEC_AMR_FRM_TYPE_NO_DATA      = 15,
    CODEC_AMR_FRM_TYPE_BUTT
};
typedef VOS_UINT16 CODEC_AMR_FRM_TYPE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMR_TYPE_RX_ENUM
 功能描述  : AMR接收帧类型定义, 参见3GPP TS 26.093及26.073 frame.h
*****************************************************************************/
enum CODEC_AMR_TYPE_RX_ENUM
{
    CODEC_AMR_TYPE_RX_SPEECH_GOOD   = 0,
    CODEC_AMR_TYPE_RX_SPEECH_DEGRADED,
    CODEC_AMR_TYPE_RX_ONSET,
    CODEC_AMR_TYPE_RX_SPEECH_BAD,
    CODEC_AMR_TYPE_RX_SID_FIRST,
    CODEC_AMR_TYPE_RX_SID_UPDATE,
    CODEC_AMR_TYPE_RX_SID_BAD,
    CODEC_AMR_TYPE_RX_NO_DATA,
    CODEC_AMR_TYPE_RX_BUTT
};
typedef VOS_UINT16 CODEC_AMR_TYPE_RX_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMR_TYPE_TX_ENUM
 功能描述  : AMR发送帧类型定义, 参见3GPP TS 26.093及26.073 frame.h
*****************************************************************************/
enum CODEC_AMR_TYPE_TX_ENUM
{
    CODEC_AMR_TYPE_TX_SPEECH_GOOD   = 0,
    CODEC_AMR_TYPE_TX_SID_FIRST,
    CODEC_AMR_TYPE_TX_SID_UPDATE,
    CODEC_AMR_TYPE_TX_NO_DATA,
    CODEC_AMR_TYPE_TX_SPEECH_DEGRADED,
    CODEC_AMR_TYPE_TX_SPEECH_BAD,
    CODEC_AMR_TYPE_TX_SID_BAD,
    CODEC_AMR_TYPE_TX_ONSET,
    CODEC_AMR_TYPE_TX_BUTT
};
typedef VOS_UINT16 CODEC_AMR_TYPE_TX_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMR_NSYNC_ENUM
 功能描述  : AMR NSYNC参数定义, 该参数DTX使能时使用, 参见3GPP TS 26.093 A5.1
*****************************************************************************/
enum CODEC_AMR_NSYNC_ENUM
{
    CODEC_AMR_NSYNC_INIT            = 0,                                    /* 初始化值 */
    CODEC_AMR_NSYNC_HANDOVER        = 12,                                   /* 当发生小区切换时Tx RSS发送给Tx DTX handler */
    CODEC_AMR_NSYNC_BUTT
};
typedef VOS_UINT16 CODEC_AMR_NSYNC_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMR_FQI_QUALITY_ENUM
 功能描述  : 与W物理层约定的AMR帧类型的好坏
*****************************************************************************/
enum CODEC_AMR_FQI_QUALITY_ENUM
{
    CODEC_AMR_FQI_QUALITY_BAD   = 0,
    CODEC_AMR_FQI_QUALITY_GOOD,
    CODEC_AMR_FQI_QUALITY_BUTT
};
typedef VOS_UINT16 CODEC_AMR_FQI_QUALITY_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMR_STI_SID_ENUM
 功能描述  : SID标志，0表示SID_FIRST，1表示SID_UPDATE
*****************************************************************************/
enum CODEC_AMR_STI_SID_ENUM
{
    CODEC_AMR_STI_SID_FIRST   = 0,
    CODEC_AMR_STI_SID_UPDATE,
    CODEC_AMR_STI_SID_BUTT
};
typedef VOS_UINT16 CODEC_AMR_STI_SID_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMRWB_RATE_MODE_ENUM_UINT16
 功能描述  : AMR-WB速率模式
*****************************************************************************/
enum CODEC_AMRWB_RATE_MODE_ENUM
{
    CODEC_AMRWB_RATE_MODE_660K              = 0,
    CODEC_AMRWB_RATE_MODE_885K,
    CODEC_AMRWB_RATE_MODE_1265K,
    CODEC_AMRWB_RATE_MODE_1425K,
    CODEC_AMRWB_RATE_MODE_1585K,
    CODEC_AMRWB_RATE_MODE_1825K,
    CODEC_AMRWB_RATE_MODE_1985K,
    CODEC_AMRWB_RATE_MODE_2305K,
    CODEC_AMRWB_RATE_MODE_2385K,
    CODEC_AMRWB_RATE_MODE_BUTT
};
typedef VOS_UINT16  CODEC_AMRWB_RATE_MODE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMRWB_FRM_TYPE_ENUM
 功能描述  : AMR-WB IF帧类型, 参见3GPP TS 26.201 Table 1a
*****************************************************************************/
enum CODEC_AMRWB_FRM_TYPE_ENUM
{
    CODEC_AMRWB_FRM_TYPE_660K         = 0,
    CODEC_AMRWB_FRM_TYPE_885K         = 1,
    CODEC_AMRWB_FRM_TYPE_1265K        = 2,
    CODEC_AMRWB_FRM_TYPE_1425K        = 3,
    CODEC_AMRWB_FRM_TYPE_1585K        = 4,
    CODEC_AMRWB_FRM_TYPE_1825K        = 5,
    CODEC_AMRWB_FRM_TYPE_1985K        = 6,
    CODEC_AMRWB_FRM_TYPE_2305K        = 7,
    CODEC_AMRWB_FRM_TYPE_2385K        = 8,
    CODEC_AMRWB_FRM_TYPE_SID          = 9,
    CODEC_AMRWB_FRM_TYPE_NO_DATA      = 15,
    CODEC_AMRWB_FRM_TYPE_BUTT
};
typedef VOS_UINT16 CODEC_AMRWB_FRM_TYPE_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMRWB_TYPE_RX_ENUM
 功能描述  : AMR-WB接收帧类型定义, 参见3GPP TS 26.193及26.173 frame.h
*****************************************************************************/
enum CODEC_AMRWB_TYPE_RX_ENUM
{
    CODEC_AMRWB_TYPE_RX_SPEECH_GOOD   = 0,
    CODEC_AMRWB_TYPE_RX_SPEECH_DEGRADED,
    CODEC_AMRWB_TYPE_RX_ONSET,
    CODEC_AMRWB_TYPE_RX_SPEECH_BAD,
    CODEC_AMRWB_TYPE_RX_SID_FIRST,
    CODEC_AMRWB_TYPE_RX_SID_UPDATE,
    CODEC_AMRWB_TYPE_RX_SID_BAD,
    CODEC_AMRWB_TYPE_RX_NO_DATA,
    CODEC_AMRWB_TYPE_RX_SPEECH_LOST,
    CODEC_AMRWB_TYPE_RX_BUTT
};
typedef VOS_UINT16 CODEC_AMRWB_TYPE_RX_ENUM_UINT16;

/*****************************************************************************
 实体名称  : CODEC_AMRWB_TYPE_TX_ENUM
 功能描述  : AMR-WB发送帧类型定义, 参见3GPP TS 26.193及26.173 frame.h
*****************************************************************************/
enum CODEC_AMRWB_TYPE_TX_ENUM
{
    CODEC_AMRWB_TYPE_TX_SPEECH_GOOD   = 0,
    CODEC_AMRWB_TYPE_TX_SID_FIRST,
    CODEC_AMRWB_TYPE_TX_SID_UPDATE,
    CODEC_AMRWB_TYPE_TX_NO_DATA,
    CODEC_AMRWB_TYPE_TX_SPEECH_DEGRADED,
    CODEC_AMRWB_TYPE_TX_SPEECH_BAD,
    CODEC_AMRWB_TYPE_TX_SID_BAD,
    CODEC_AMRWB_TYPE_TX_ONSET,
    CODEC_AMRWB_TYPE_TX_SPEECH_LOST,
    CODEC_AMRWB_TYPE_TX_BUTT
};
typedef VOS_UINT16 CODEC_AMRWB_TYPE_TX_ENUM_UINT16;


/*****************************************************************************
 实体名称  : MED_CODEC_FRAME_FACCH_ENUM
 功能描述  : 下行是否偷帧标志
*****************************************************************************/
enum CODEC_FRAME_FACCH_ENUM
{
    CODEC_FRAME_FACCH_NO              = 0,
    CODEC_FRAME_FACCH_YES,
    CODEC_FRAME_FACCH_BUTT
};
typedef VOS_UINT16 CODEC_FRAME_FACCH_ENUM_UINT16;

/*音频录音模式*/
enum AUDIO_CAPTURE_MODE_ENUM
{
    AUDIO_CAPTURE_MODE_DISABLE = 0,                              /*录音禁止*/
    AUDIO_CAPTURE_MODE_CALL    = 1,                              /*普通CS通话录音*/
    AUDIO_CAPTURE_MODE_CAMCORD = 2,                              /*通话时摄像*/
    AUDIO_CAPTURE_MODE_EXT_CALL= 3,                              /*第三方Modem通话录音*/
    AUDIO_CAPTURE_MODE_AUDIO   = 4,                              /*普通音频录音*/
    AUDIO_CAPTURE_MODE_FM      = 5,                              /*普通FM录音*/
    AUDIO_CAPTURE_MODE_VQM     = 6,                              /*在线语音质量检测*/
    AUDIO_CAPTURE_MODE_BUT
};
typedef VOS_UINT16  AUDIO_CAPTURE_MODE_ENUM_UINT16;

/* 音频数据通路状态枚举 */
enum AUDIO_PCM_STATUS_ENUM
{
    AUDIO_PCM_STATUS_DEACTIVE= 0,
    AUDIO_PCM_STATUS_ACTIVE,
    AUDIO_PCM_STATUS_BUT
};
typedef VOS_UINT16  AUDIO_PCM_STATUS_ENUM_UINT16;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : MSG_CODEC_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 命令执行response通用结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 */
    UCOM_RET_ENUM_UINT16                enExeRslt;                              /* 执行结果 */
    VOS_UINT16                          usReserve2;
}MSG_CODEC_CNF_STRU;

/*****************************************************************************
 实体名称  : VOICE_WPHY_AMR_SERIAL_STRU
 功能描述  : 与W物理层之间约定的AMR上下行码流格式结构体
*****************************************************************************/
typedef struct
{
    WPHY_VOICE_DATA_STRU
}VOICE_WPHY_AMR_SERIAL_STRU;

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


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

#endif /* end of CodecInterface.h */
