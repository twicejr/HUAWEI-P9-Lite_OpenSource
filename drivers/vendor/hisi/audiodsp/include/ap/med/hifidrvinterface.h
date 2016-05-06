/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : HifiDrvInterface.h
  版 本 号   : 初稿
  作    者   : C00137131
  生成日期   : 2012年8月16日
  最近修改   :
  功能描述   : Hifi与DRV之间的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月16日
    作    者   : C00137131
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含

  notice:  不要包含任何其他头文件!!!
           请同时修改\device\hisi\hi6620\common\audio\hifidrvinterface.h，保持两份文件一致!!!
*****************************************************************************/


#ifndef __HIFIDRVINTERFACE_H__
#define __HIFIDRVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* AP侧Kernel音频驱动发送数据给hifi时的buff描述，bufAddr为总线地址，bufSize和dataSize单位byte */
#if 0                                                                            /*_H2ASN_Skip */
#define DRV_SEND_DATA_STRU                                                      \
    VOS_UINT32                              uwBufAddr;                          \
    VOS_UINT32                              uwBufSize;                          \
    VOS_UINT32                              uwDataSize;
#else
#define DRV_SEND_DATA_STRU                                                      \
    unsigned int                           uwBufAddr;                          \
    unsigned int                           uwBufSize;                          \
    unsigned int                           uwDataSize;
#endif

#define MSG_HEADER  unsigned int uwSenderCpuId;  \
                    unsigned int uwSenderPid;    \
                    unsigned int uwReceiverCpuId;\
                    unsigned int uwReceiverPid;  \
                    unsigned int uwLength;

#define AUDIO_HIFIMISC_MSG_SN_DEFAULT       (0xffffffff)                        /* Hifi主动上报的SN号 */
#define HIFI_AUDIO_PCM_COMP_COEF_LEN_MAX    (128)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* 音频输入输出模式，播放/录音 */
enum AUDIO_PCM_MODE_ENUM
{
    AUDIO_PCM_MODE_PLAYBACK = 0,
    AUDIO_PCM_MODE_CAPTURE,
/*    AUDIO_PCM_MODE_HDMI,
    AUDIO_PCM_MODE_WIFIDISPLAY,*/
    AUDIO_PCM_MODE_BUT
};
typedef unsigned short  AUDIO_PCM_MODE_ENUM_UINT16;              /*_H2ASN_Replace typedef VOS_UINT16 AUDIO_PCM_MODE_ENUM_UINT16; */

/* 音频输入输出对象枚举 */
enum AUDIO_PCM_OBJ_ENUM
{
    AUDIO_PCM_OBJ_AP = 0,
    AUDIO_PCM_OBJ_HIFI,
    AUDIO_PCM_OBJ_BUT
};
typedef unsigned short  AUDIO_PCM_OBJ_ENUM_UINT16;    /*_H2ASN_Replace typedef VOS_UINT16 AUDIO_PCM_OBJ_ENUM_UINT16; */

/* 音频数据搬运触发命令枚举，该枚举与AP侧宏定义SNDRV_PCM_TRIGGER_XXXX一一对应 */
enum AUDIO_PCM_TRIGGER_CMD_ENUM
{
    AUDIO_PCM_TRIGGER_STOP          = 0,            /* 音频通路停止 */
    AUDIO_PCM_TRIGGER_START         = 1,            /* 音频通路开启 */
    AUDIO_PCM_TRIGGER_PAUSE_PUSH    = 3,            /* 音频通路暂停 */
    AUDIO_PCM_TRIGGER_PAUSE_RELEASE = 4,            /* 音频通路释放暂停 */
    AUDIO_PCM_TRIGGER_SUSPEND       = 5,            /* 音频通路暂停 */
    AUDIO_PCM_TRIGGER_RESUME        = 6,            /* 音频通路继续 */
    AUDIO_PCM_TRIGGER_BUT
};
typedef unsigned short  AUDIO_PCM_TRIGGER_CMD_ENUM_UINT16;  /*_H2ASN_Replace typedef VOS_UINT16 AUDIO_PCM_TRIGGER_CMD_ENUM_UINT16; */

/* AUDIO PLAYER音频播放数据格式状态枚举 */
enum AUDIO_FILE_FORMAT_ENUM
{
    AUDIO_FILE_FORMAT_MP3 = 0,
    AUDIO_FILE_FORMAT_AAC,
    AUDIO_FILE_FORMAT_WAV,
    AUDIO_FILE_FORMAT_BUT
};
typedef unsigned short  AUDIO_FILE_FORMAT_ENUM_UINT16; /*_H2ASN_Replace typedef VOS_UINT16 AUDIO_FILE_FORMAT_ENUM_UINT16; */


/* AUDIO PLAYER音频数据播放完毕状态枚举 */
enum AUDIO_PLAY_DONE_IND_ENUM
{
    AUDIO_PLAY_DONE_NORMAL   = 0,                           /* 一块音频数据正常播放完成 */
    AUDIO_PLAY_DONE_COMPLETE,                               /* 一个完整音频文件正常播放完成 */
    AUDIO_PLAY_DONE_ABNORMAL,                               /* 播放过程出错，播放中断 */
    AUDIO_PLAY_DONE_RESET,                                     /*ap command : listen thread exit*/
    AUDIO_PLAY_DONE_BUTT
};

typedef unsigned short  AUDIO_PLAY_DONE_IND_ENUM_UINT16;/*_H2ASN_Replace typedef VOS_UINT16 AUDIO_PLAY_DONE_IND_ENUM_UINT16; */

/* AUDIO PLAYER执行过程中成功失败枚举 */
enum AUDIO_PLAY_RESULT_CNF_ENUM
{
    AUDIO_PLAY_RESULT_OK = 0,                               /* 成功 */
    AUDIO_PLAY_RESULT_FAIL,                                 /* 失败 */
    AUDIO_PLAY_RESULT_BUT
};

typedef unsigned short  AUDIO_PLAY_RESULT_CNF_ENUM_UINT16;/*_H2ASN_Replace typedef VOS_UINT16 AUDIO_PLAY_RESULT_CNF_ENUM_UINT16; */

/*****************************************************************************
 实体名称  : AUDIO_EFFECT_ENABLE_ENUM
 功能描述  : 音效使能枚举
*****************************************************************************/
enum AUDIO_EFFECT_ENABLE_ENUM
{
    AUDIO_EFFECT_NONE        = 0,   /* 音效关闭 */
    AUDIO_EFFECT_DTS_ENABLE,        /* DTS音效使能 */
    AUDIO_EFFECT_DTS_DISABLE,
    AUDIO_EFFECT_DM3_ENABLE,        /* dobly音效使能 */
    AUDIO_EFFECT_DM3_DISABLE,
    AUDIO_EFFECT_ENABLE_BUT
};
typedef unsigned short AUDIO_EFFECT_ENABLE_UINT16;       /*_H2ASN_Replace typedef VOS_UINT16 AUDIO_EFFECT_ENABLE_UINT16; */

/*****************************************************************************
 实体名称  : AUDIO_EFFECT_DEVICE_ENUM
 功能描述  : 当前设备
*****************************************************************************/
enum AUDIO_EFFECT_DEVICE_ENUM
{
    AUDIO_EFFECT_DEVICE_HEADPHONE = 0,
    AUDIO_EFFECT_DEVICE_SPK,
    AUDIO_EFFECT_DEVICE_BUT
};
typedef unsigned short AUDIO_EFFECT_DEVICE_UINT16;/*_H2ASN_Replace typedef VOS_UINT16 AUDIO_EFFECT_DEVICE_UINT16; */

/* 音效类型 */
enum AUDIO_EFFECT_TYPE_ENUM
{
    AUDIO_EFFECT_DTS = 0, /* DTS音效 */
    AUDIO_EFFECT_DM3,     /* dolby音效 */
    AUDIO_EFFECT_TYPE_BUT
};
typedef unsigned short AUDIO_EFFECT_TYPE_UINT16;/*_H2ASN_Replace typedef VOS_UINT16 AUDIO_EFFECT_TYPE_UINT16; */

/* 设置音效参数 */
enum AUDIO_EFFECT_SETPARAMS_ENUM
{
    AUDIO_EFFECT_DM3_BYPASS = 1,
    AUDIO_EFFECT_DM3_SINGLE_DEVICE_VALUE = 2,
    AUDIO_EFFECT_DM3_ALL_VALUES = 3,
    AUDIO_EFFECT_DM3_BUT
};
typedef unsigned short AUDIO_EFFECT_SETPARAMS_UINT16;/*_H2ASN_Replace typedef VOS_UINT16 AUDIO_EFFECT_SETPARAMS_UINT16; */

/* 设置setLoop */
enum AUDIO_PLAYER_SET_LOOP_ENUM
{
    AUDIO_PLAYER_SET_LOOP_FLASE = 0,
    AUDIO_PLAYER_SET_LOOP_TRUE  = 1,
    AUDIO_PLAYER_SET_LOOP_BUTT
};
typedef unsigned int AUDIO_PLAYER_SET_LOOP_ENUM_UINT32;/*_H2ASN_Replace typedef VOS_UINT32 AUDIO_PLAYER_SET_LOOP_ENUM_UINT32; */

/* 通话中上报的音频业务错误码 */
enum VOICE_AUDIO_ERR_IND_ENUM
{
    VOICE_AUDIO_NO_ERR          = 0,
    VOICE_AUDIO_ERR_IND         = 1,
    VOICE_AUDIO_FATAL_ERR_IND   = 2,
    VOICE_AUDIO_ERR_BUTT
};
typedef unsigned int VOICE_AUDIO_ERR_IND_ENUM_UINT32;/*_H2ASN_Replace typedef VOS_UINT32 VOICE_AUDIO_ERR_IND_ENUM_UINT32; */

/* 通话中上报的音频业务类型枚举 */
enum VOICE_AUDIO_MODE_ENUM
{
    VOICE_AUDIO_MODE_PLAY       = 0,
    VOICE_AUDIO_MODE_RECORD     = 1,
    VOICE_AUDIO_MODE_BUT
};
typedef unsigned int VOICE_AUDIO_MODE_ENUM_UINT32;/*_H2ASN_Replace typedef VOS_UINT32 VOICE_AUDIO_MODE_ENUM_UINT32; */

enum AUDIO_MSG_ENUM
{
    ID_AP_VOICEPP_START_REQ             = 0xDD42,           /* 启动VOICEPP通话 *//* _H2ASN_MsgChoice VOICEPP_MC_START_REQ_STRU */
    ID_VOICEPP_MSG_START                = ID_AP_VOICEPP_START_REQ,   /*_H2ASN_Skip */
    ID_VOICEPP_AP_START_CNF             = 0xDD43,           /*_H2ASN_Skip */
    ID_AP_VOICEPP_STOP_REQ              = 0xDD44,           /* 终止VOICEPP通话 *//* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_VOICEPP_AP_STOP_CNF              = 0xDD45,           /* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_AP_VOICEPP_SET_DEVICE_REQ        = 0xDD46,           /* 配置输入输出设备 *//* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_VOICEPP_AP_SET_DEVICE_CNF        = 0xDD47,          /* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_AP_VOICEPP_SET_WB_REQ            = 0xDD48,           /* 设置宽窄带 *//* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_VOICEPP_AP_SET_WB_CNF            = 0xDD49,           /* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_VOICEPP_MSG_END                  = 0xDD4A,          /* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */

    /* AP音频驱动与HIFI audio player模块交互消息ID */
    ID_AP_AUDIO_PLAY_START_REQ          = 0xDD51,           /* AP启动Hifi audio player request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_AUDIO_AP_PLAY_START_CNF          = 0xDD52,           /* Hifi启动audio player后回复AP confirm命令 */ /*_H2ASN_Skip */
    ID_AP_AUDIO_PLAY_PAUSE_REQ          = 0xDD53,           /* AP停止Hifi audio player request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_PAUSE_REQ_STRU */
    ID_AUDIO_AP_PLAY_PAUSE_CNF          = 0xDD54,           /* Hifi停止audio player后回复AP confirm命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_PAUSE_CNF_STRU */
    ID_AUDIO_AP_PLAY_DONE_IND           = 0xDD56,           /* Hifi通知AP audio player一块数据播放完毕或者播放中断indication */ /* _H2ASN_MsgChoice AUDIO_PLAYER_DONE_IND_STRU */
    ID_AP_AUDIO_PLAY_UPDATE_BUF_CMD     = 0xDD57,           /* AP通知Hifi新数据块更新command */ /* _H2ASN_MsgChoice AUDIO_PLAYER_UPDATE_BUF_CMD_STRU */
    ID_AP_AUDIO_PLAY_QUERY_TIME_REQ     = 0xDD59,           /* AP查询Hifi audio player播放进度request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_TIME_REQ_STRU */
    ID_AP_AUDIO_PLAY_WAKEUPTHREAD_REQ   = 0xDD5A,           /* AP主动结束播放 */ /*_H2ASN_Skip */
    ID_AUDIO_AP_PLAY_QUERY_TIME_CNF     = 0xDD60,           /* Hifi回复AP audio player播放进度confirm命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_TIME_CNF_STRU */
    ID_AP_AUDIO_PLAY_QUERY_STATUS_REQ   = 0xDD61,           /* AP查询Hifi audio player播放状态request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_STATUS_REQ_STRU */
    ID_AUDIO_AP_PLAY_QUERY_STATUS_CNF   = 0xDD62,           /* Hifi回复AP audio player播放状态confirm命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_STATUS_CNF_STRU */
    ID_AP_AUDIO_PLAY_SEEK_REQ           = 0xDD63,           /* AP seek Hifi audio player到某一位置request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SEEK_REQ_STRU */
    ID_AUDIO_AP_PLAY_SEEK_CNF           = 0xDD64,           /* Hifi回复AP seek结果confirm命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SEEK_CNF_STRU */

    /* AP音频驱动与audio loop环回交互消息ID */
    ID_AP_AUDIO_LOOP_BEGIN_REQ          = 0xDD65,           /* AP启动Hifi begin audio loop request命令 */ /*_H2ASN_Skip */
    ID_AUDIO_AP_LOOP_BEGIN_CNF          = 0xDD66,           /* Hifi回复AP begin audio loop结果confirm命令 */ /* _H2ASN_MsgChoice AUDIO_LOOP_CNF_STRU */
    ID_AP_AUDIO_LOOP_END_REQ            = 0xDD67,           /* AP启动Hifi end audio loop request命令 */ /* _H2ASN_MsgChoice AUDIO_PCM_OPEN_REQ_STRU */
    ID_AUDIO_AP_LOOP_END_CNF            = 0xDD68,           /* Hifi回复AP end audio loop结果confirm命令 */ /* _H2ASN_MsgChoice AUDIO_LOOP_CNF_STRU */
    ID_AP_AUDIO_PLAY_SET_VOL_CMD        = 0xDD70,           /* AP设置超低功耗播放音量命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SET_VOL_REQ_STRU */

    ID_AUDIO_PLAYER_START_REQ           = 0xDD71,           /* _H2ASN_MsgChoice AUDIO_PCM_OPEN_REQ_STRU */
    ID_AUDIO_PLAYER_STOP_REQ            = 0xDD73,           /* _H2ASN_MsgChoice AUDIO_PCM_CLOSE_REQ_STRU */

    /* AP音频驱动与录音模块交互消息 */
    ID_AP_AUDIO_RECORD_START_CMD        = 0xDD40,           /* _H2ASN_MsgChoice AUDIO_RECORD_START_STRU */
    ID_AP_AUDIO_RECORD_STOP_CMD         = 0xDD41,           /* _H2ASN_MsgChoice AUDIO_RECORD_STOP_STRU */

    /* AP音频驱动与命令模块交互消息 */
    ID_AP_AUDIO_CMD_SET_SOURCE_CMD      = 0xDD95,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_SET_DEVICE_CMD      = 0xDD96,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_SET_MODE_CMD        = 0xDD97,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_SET_MMI_MODE_CMD    = 0xDD98,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_MLIB_SET_PARA_CMD   = 0xDD92,           /*_H2ASN_Skip */ /*modify*/////////////////////
    ID_AP_AUDIO_CMD_SET_ANGLE_CMD       = 0xDD99,

    /* AP音频驱动与HIFI音频通道模块交互消息ID */
    ID_AP_AUDIO_PCM_OPEN_REQ            = 0xDD25,           /* _H2ASN_MsgChoice AUDIO_PCM_OPEN_REQ_STRU */
    ID_AP_AUDIO_PCM_CLOSE_REQ           = 0xDD26,           /* _H2ASN_MsgChoice AUDIO_PCM_CLOSE_REQ_STRU */
    ID_AP_AUDIO_PCM_HW_PARA_REQ         = 0xDD27,           /* _H2ASN_MsgChoice AUDIO_PCM_HW_PARAMS_REQ_STRU */
    ID_AP_AUDIO_PCM_HW_FREE_REQ         = 0xDD28,           /* 暂未使用，保留 */ /*_H2ASN_Skip */
    ID_AP_AUDIO_PCM_PREPARE_REQ         = 0xDD29,           /* 暂未使用，保留 */ /*_H2ASN_Skip */
    ID_AP_AUDIO_PCM_TRIGGER_REQ         = 0xDD2A,           /* _H2ASN_MsgChoice AUDIO_PCM_TRIGGER_REQ_STRU */
    ID_AP_AUDIO_PCM_POINTER_REQ         = 0xDD2B,           /* 暂未使用，保留 */ /*_H2ASN_Skip */
    ID_AP_AUDIO_PCM_SET_BUF_CMD         = 0xDD2C,           /* _H2ASN_MsgChoice AUDIO_PCM_SET_BUF_CMD_STRU */
    ID_AUDIO_AP_PCM_PERIOD_ELAPSED_CMD  = 0xDD2D,           /* _H2ASN_MsgChoice AUDIO_PCM_PERIOD_ELAPSED_CMD_STRU */

    /* HIFI音频通道模块内部交互消息ID */
    ID_AUDIO_UPDATE_PLAY_BUFF_CMD       = 0xDD2E,           /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */
    ID_AUDIO_UPDATE_CAPTURE_BUFF_CMD    = 0xDD2F,           /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */
    ID_AUDIO_AP_PCM_TRIGGER_CNF         = 0xDDA0,           /* _H2ASN_MsgChoice AUDIO_PCM_TRIGGER_CNF_STRU */

    /* HIFI PCM模块与audio player模块内部交互消息ID */
    ID_AUDIO_UPDATE_PLAYER_BUFF_CMD     = 0xDD31,           /* audio PCM通知player更新播放buff数据 */ /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */

    /* AP和HIFI关于音效的交互消息 */
    ID_AP_AUDIO_EFFECT_ENABLE_REQ       = 0xDD34,           /* 待定 */  /* _H2ASN_MsgChoice AUDIO_EFFECT_ENABLE_REQ_STRU */
    ID_AP_AUDIO_EFFECT_PARA_REQ         = 0xDD33,           /* 待定 */  /* _H2ASN_MsgChoice AUDIO_EFFECT_SET_PARAMS_REQ_STRU */

    /* AP和HIFI的DTS交互消息 */
    ID_AP_AUDIO_SET_DTS_ENABLE_CMD       = 0xDD36,           /* AP通知Hifi使能DTS */  /* _H2ASN_MsgChoice AUDIO_EFFECT_DTS_SET_ENABLE_REQ_STRU */
    /* ID_AUDIO_PLAYER_SET_DTS_ENABLE_IND  0xDD37               内部消息占用 */
    ID_AP_AUDIO_SET_DTS_DEV_CMD          = 0xDD38,           /* AP通知Hifi DTS 输出设备模式 */  /* _H2ASN_MsgChoice AUDIO_EFFECT_DTS_SET_DEV_REQ_STRU */
    ID_AP_AUDIO_SET_DTS_GEQ_TYPE_CMD     = 0xDD39,           /* AP通知Hifi DTS GEQ音效类型*/  /* _H2ASN_MsgChoice AUDIO_EFFECT_DTS_SET_GEQ_TYPE_REQ_STRU */
    ID_AP_AUDIO_SET_DTS_GEQ_ENABLE_CMD   = 0xDD3B,           /* AP通知Hifi DTS GEQ使能*/ /*_H2ASN_Skip */

    /* A核通知HIFI C 核复位消息ID */
    ID_AP_HIFI_CCPU_RESET_REQ           = 0xDDE1,           /* _H2ASN_MsgChoice AP_HIFI_CCPU_RESET_REQ_STRU */

    /* hifi回复ID_AP_HIFI_CCPU_RESET_REQ */
    ID_HIFI_AP_CCPU_RESET_CNF           = 0xDDE2,           /* _H2ASN_MsgChoice HIFI_AP_CCPU_RESET_CNF_STRU */

    ID_AP_HIFI_REMOTE_SET_BUF_CMD       = 0xDDE3,           /* _H2ASN_MsgChoice AP_VOICE_SET_BUF_CMD_STRU */
    ID_HIFI_AP_REMOTE_PERIOD_ELAPSED_CMD= 0xDDE4,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_PERIOD_ELAPSED_IND_STRU */

    ID_AP_HIFI_REMOTE_RECORD_START_REQ  = 0xDDE5,           /* _H2ASN_MsgChoice AP_VOICE_REMOTE_AUDIO_REQ_STRU */
    ID_HIFI_AP_REMOTE_RECORD_START_CNF  = 0xDDE6,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    ID_HIFI_AP_REMOTE_RECORD_DATA_ERR_IND = 0xDDE7,         /* _H2ASN_MsgChoice VOICE_AP_REMOTE_DATA_ERR_IND_STRU */

    ID_AP_HIFI_REMOTE_RECORD_STOP_REQ   = 0xDDE8,           /* _H2ASN_MsgChoice AP_VOICE_REMOTE_AUDIO_REQ_STRU */
    ID_HIFI_AP_REMOTE_RECORD_STOP_CNF   = 0xDDE9,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    ID_AP_HIFI_REMOTE_PLAY_START_REQ    = 0xDDEA,           /* _H2ASN_MsgChoice AP_VOICE_REMOTE_AUDIO_REQ_STRU */
    ID_HIFI_AP_REMOTE_PLAY_START_CNF    = 0xDDEB,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    ID_AP_HIFI_REMOTE_PLAY_DATA_ERR_IND = 0xDDEC,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_DATA_ERR_IND_STRU */

    ID_AP_HIFI_REMOTE_PLAY_STOP_REQ     = 0xDDED,           /* _H2ASN_MsgChoice AP_VOICE_REMOTE_AUDIO_REQ_STRU */
    ID_HIFI_AP_REMOTE_PLAY_STOP_CNF     = 0xDDEE,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    ID_HIFI_AP_REMOTE_VOICE_STOP_CMD    = 0xDDEF,           /* _H2ASN_MsgChoice VOICE_AP_REMOTE_AUDIO_CNF_STRU */

    /* for 3mic */
    ID_AP_AUDIO_ROUTING_COMPLETE_REQ    = 0xDDC0,/*AP 通知HIFI 3Mic/4Mic 通路已建立*/ /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AUDIO_AP_DP_CLK_EN_IND           = 0xDDC1,/* HIFI 通知A核打开或关闭Codec DP时钟 */ /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU*/
    ID_AP_AUDIO_DP_CLK_STATE_IND        = 0xDDC2,/* A核通知HIFI ，Codec DP时钟状态( 打开或关闭) */ /* _H2ASN_MsgChoiceAUDIO_CMD_COMMON_SET_STRU */
    ID_AUDIO_AP_FADE_OUT_REQ            = 0xDDC4,/* HIFI通知AP做淡出处理 */ /* _H2ASN_MsgChoiceAUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_FADE_OUT_CNF            = 0xDDC5,/* AP通知HIFI淡出完毕 */ /* _H2ASN_MsgChoiceAUDIO_CMD_COMMON_SET_STRU */

    /* for voice BSD */
    ID_AP_AUDIO_BSD_CONTROL_REQ         = 0xDDC6,           /* hal层通知HIFI，BSD语音检测开始or停止 */ /*_H2ASN_Skip */
    ID_AUDIO_AP_OM_CMD                  = 0xDDC9,            /*_H2ASN_Skip */

    /* 测试用: hal层通知HIFI, 通过特定危险操作触发对应的HIFI单独复位 */
    ID_AP_HIFI_MOCKER_HIFI_RESET_CMD    = 0xDDCA,           /* _H2ASN_MsgChoice AP_HIFI_MOCKER_HIFI_RESET_CMD_STRU */
    ID_AP_AUDIO_STR_CMD                 = 0xDDCB,           /* AP给HIFI发送一个字符串，具体含义hifi中解析 */
    ID_AUDIO_AP_VOICE_BSD_PARAM_CMD     = 0xDDCC,           /* VOICE BSD 参数上报  */
};

typedef unsigned short  AUDIO_MSG_ENUM_UINT16;/*_H2ASN_Replace typedef VOS_UINT16 AUDIO_MSG_ENUM_UINT16; */

/* misc设备commad字段枚举 */
enum AUDIO_MISC_CMD_ENUM
{
    AUDIO_MISC_CMD_SYNC = 0,
    AUDIO_MISC_CMD_NOTIFY,
    AUDIO_MISC_CMD_ASYNC,
    AUDIO_MISC_CMD_BUTT,
};
typedef unsigned int  AUDIO_MISC_CMD_ENUM_UINT32;/*_H2ASN_Replace typedef VOS_UINT32 AUDIO_MISC_CMD_ENUM_UINT32; */

/* VOIP通话模式枚举 */
enum AUDIO_VOIP_DEVICE_ENUM
{
    AUDIO_VOIP_DEVICE_HANDSET           = 0,                /* 手持模式 */
    AUDIO_VOIP_DEVICE_HANDFREE,                             /* 免提模式 */
    AUDIO_VOIP_DEVICE_CARFREE,                              /* 车载免提模式 */
    AUDIO_VOIP_DEVICE_HEADSET,                              /* 耳机模式 */
    AUDIO_VOIP_DEVICE_BLUETOOTH,                            /* 蓝牙模式 */
    AUDIO_VOIP_DEVICE_PCVOICE,                              /* PC-VOICE模式 */
    AUDIO_VOIP_DEVICE_HEADPHONE,                            /* 不带耳机MIC的耳机通话 */
    AUDIO_VOIP_DEVICE_BUTT
};
typedef unsigned int  AUDIO_VOIP_DEVICE_ENUM_UINT32;/*_H2ASN_Replace typedef VOS_UINT32 AUDIO_VOIP_DEVICE_ENUM_UINT32; */

/* 声学增强模式枚举 */
enum AUDIO_ENHANCE_DEVICE_ENUM
{
    AUDIO_ENHANCE_DEVICE_HANDSET        = 0,                /* 手持模式 */
    AUDIO_ENHANCE_DEVICE_HANDFREE       = 1,                /* 免提模式 */
    AUDIO_ENHANCE_DEVICE_CARFREE        = 2,                /* 车载免提模式 */
    AUDIO_ENHANCE_DEVICE_HEADSET        = 3,                /* 耳机模式 */
    AUDIO_ENHANCE_DEVICE_BLUETOOTH      = 4,                /* 蓝牙模式 */
    AUDIO_ENHANCE_DEVICE_PCVOICE        = 5,                /* PC-VOICE模式 */
    AUDIO_ENHANCE_DEVICE_HEADPHONE      = 6,                /* 不带耳机MIC的耳机通话 */
    AUDIO_ENHANCE_DEVICE_SUPER_HANDFREE = 7,
    AUDIO_ENHANCE_DEVICE_HANDSET_AVE    = 8,
    AUDIO_ENHANCE_DEVICE_BUTT
};
typedef unsigned int  AUDIO_ENHANCE_DEVICE_ENUM_UINT32;/*_H2ASN_Replace typedef VOS_UINT32 AUDIO_ENHANCE_DEVICE_ENUM_UINT32; */

/* 声学增强模块枚举 */
enum AUDIO_ENHANCE_MODULE_ENUM
{
    AUDIO_ENHANCE_MODULE_DEFAULT        = 0,                /* 普通音频处理 */
    AUDIO_ENHANCE_MODULE_VOIP,                              /* VOIP音频处理 */
    AUDIO_ENHANCE_MODULE_SIRI,                              /* 语音识别音频处理 */
    AUDIO_ENHANCE_MODULE_INCALL,                         /* 进入通话场景 */
    AUDIO_ENHANCE_MODULE_OUTCALL,                         /* 退出通话场景 */
    AUDIO_ENHANCE_MODULE_BUTT,

};
typedef unsigned int   AUDIO_ENHANCE_MODULE_ENUM_UINT32;/*_H2ASN_Replace typedef VOS_UINT32 AUDIO_ENHANCE_MODULE_ENUM_UINT32; */

enum
{
    VOICE_BSD_DETECT_STOP = 0,
    VOICE_BSD_DETECT_START,
    VOICE_BSD_DETECT_RESET,
    VOICE_BSD_DETECT_BUT
};
typedef unsigned int VOICE_BSD_CONTROL_REQ_ENUM_UINT32;/*_H2ASN_Replace typedef VOS_UINT32 VOICE_BSD_CONTROL_REQ_ENUM_UINT32; */

/*****************************************************************************
 枚举名    : HIFI_RESET_CASE_ENUM
 枚举说明  : HIFI复位方式
*****************************************************************************/
enum HIFI_RESET_CASE_ENUM
{
    HIFI_RESET_CASE_SOFTINT       = 0,   /* 模拟主动触发软中断 */
    HIFI_RESET_CASE_PANIC         = 1,   /* 模拟触发HIFI PANIC */
    HIFI_RESET_CASE_WTD_TIMEOUT   = 2,   /* 模拟触发看门狗超时复位 */
    HIFI_RESET_CASE_BUTT
};
typedef unsigned short HIFI_RESET_CASE_ENUM_UINT16;   /*_H2ASN_Replace typedef VOS_UINT16 HIFI_RESET_CASE_ENUM_UINT16; */

enum audio_player_set_angle_enum{
    SCREEN_ANGLE_PORTRAIT_0 = 0,
    SCREEN_ANGLE_LANDSCAPE_90 = 90,
    SCREEN_ANGLE_PORTRAIT_180 = 180,
    SCREEN_ANGLE_LANDSCAPE_270 = 270,
    SCREEN_ANGLE_MAX,
};

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/

/*****************************************************************************
 实体名称  : AUDIO_HIFIMISC_MSG_TAIL_STRU
 功能描述  : AP HifiMisc设备的消息标识结构体，包括消息类型、消息编号，要求紧跟着
             原消息内容写在消息末尾
*****************************************************************************/
 typedef struct
{
    unsigned int                           uwCmdId;            /*_H2ASN_Replace VOS_UINT32 uwCmdId;*/
    unsigned int                           uwSn;               /*_H2ASN_Replace VOS_UINT32 uwSn;*/
} AUDIO_HIFIMISC_MSG_TAIL_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PCM_OPEN_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_PCM_OPEN_REQ给DSP_PID_AUDIO，通知Hifi启动
             输入输出通道任务
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD25*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Skip */
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* 启动数据输入/数据输出 */ /*_H2ASN_Replace VOS_UINT16 enPcmMode;*/
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
} AUDIO_PCM_OPEN_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PCM_CLOSE_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_PCM_CLOSE_REQ给DSP_PID_AUDIO，通知Hifi停止
             输入输出通道任务
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD26*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Skip */
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* 停止数据输入/数据输出 */ /*_H2ASN_Replace VOS_UINT16 enPcmMode;*/
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
} AUDIO_PCM_CLOSE_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PCM_HW_PARAMS_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_PCM_HW_PARAMS_REQ给DSP_PID_AUDIO，通知Hifi
             进行资源相关初始化
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD27*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Skip */
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* 需初始化相关资源的通道 */ /*_H2ASN_Replace VOS_UINT16 enPcmMode;*/
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
    unsigned int                            uwChannelNum;       /* 通道的声道数 */ /*_H2ASN_Replace VOS_UINT32 uwChannelNum;*/
    unsigned int                            uwSampleRate;       /* 当前通道采样率 */ /*_H2ASN_Replace VOS_UINT32 uwSampleRate;*/
} AUDIO_PCM_HW_PARAMS_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PCM_TRIGGER_REQ_STRU
 功能描述  : AP或Hifi发送该消息ID_AP_AUDIO_PCM_TRIGGER_REQ给DSP_PID_AUDIO，触发
             Hifi的某数据通道进行状态更新
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD2A*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* 数据通道模式 */ /*_H2ASN_Replace VOS_UINT16 enPcmMode;*/
    AUDIO_PCM_TRIGGER_CMD_ENUM_UINT16       enCmd;              /* 触发命令字 */ /*_H2ASN_Replace VOS_UINT16 enCmd;*/
    AUDIO_PCM_OBJ_ENUM_UINT16               enPcmObj;           /* 交互的对象，为AP或者Hifi */ /*_H2ASN_Replace VOS_UINT16 enPcmObj;*/
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
    //void                                   *pSubStream;         /* 当前Buff对应的音频子流编号,仅AP侧有效 */
    unsigned int                            uwSubStream_l;      /*_H2ASN_Replace VOS_UINT32 uwSubStream_l;*/
    unsigned int                            uwSubStream_h;      /*_H2ASN_Replace VOS_UINT32 uwSubStream_h;*/
    unsigned int                            uwBufAddr;          /* 缓冲区首地址 */ /*_H2ASN_Replace VOS_UINT32 uwBufAddr;*/
    unsigned int                            uwBufSize;          /* 缓冲区的大小，单位byte */ /*_H2ASN_Replace VOS_UINT32 uwBufSize;*/
} AUDIO_PCM_TRIGGER_REQ_STRU;
/*****************************************************************************
 实体名称  : AUDIO_PCM_TRIGGER_CNF_STRU
 功能描述  : Hifi发送消息ID_AUDIO_AP_PCM_TRIGGER_CNF通知AP
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* 数据通道模式 */ /*_H2ASN_Replace VOS_UINT16 enPcmMode;*/
    AUDIO_PCM_TRIGGER_CMD_ENUM_UINT16       enCmd;              /*_H2ASN_Replace VOS_UINT16 enCmd;*/
    //void                                   *pSubStream;         /* 当前Buff对应的音频子流编号,仅AP侧有效 */
    unsigned int                            uwSubStream_l;      /*_H2ASN_Replace VOS_UINT32 uwSubStream_l;*/
    unsigned int                            uwSubStream_h;      /*_H2ASN_Replace VOS_UINT32 uwSubStream_h;*/
} AUDIO_PCM_TRIGGER_CNF_STRU;
/*****************************************************************************
 实体名称  : AUDIO_PCM_SET_BUF_CMD_STRU
 功能描述  : AP或Hifi发送消息ID_AP_AUDIO_PCM_SET_BUF_CMD给DSP_PID_AUDIO，设置某
             数据通道的输入输出Buffer地址
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD2C*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* 数据通道模式 */ /*_H2ASN_Replace VOS_UINT16 enPcmMode;*/
    AUDIO_PCM_OBJ_ENUM_UINT16               enPcmObj;           /* 交互的对象，为AP或者Hifi */ /*_H2ASN_Replace VOS_UINT16 enPcmObj;*/
    unsigned int                            uwBufOffset;          /* 缓冲区首地址 */ /*_H2ASN_Replace VOS_UINT32 uwBufAddr;*/
    unsigned int                            uwBufSize;          /* 缓冲区的大小，单位byte */ /*_H2ASN_Replace VOS_UINT32 uwBufSize;*/
} AUDIO_PCM_SET_BUF_CMD_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PCM_PERIOD_ELAPSED_CMD_STRU
 功能描述  : Hifi发送消息ID_AUDIO_AP_PCM_PERIOD_ELAPSED_CMD通知AP或Hifi一个PERIOD
             的数据已消费完或填充完毕
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD2D*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_PCM_MODE_ENUM_UINT16              enPcmMode;          /* 数据通道模式 */ /*_H2ASN_Replace VOS_UINT16 enPcmMode;*/
    unsigned short                          uhwReserve1;        /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
    // void                                   *pSubStream;         /* 当前Buff对应的音频子流编号,仅AP侧有效 */
    unsigned int                             uwSubStream_l;     /*_H2ASN_Replace VOS_UINT32 uwSubStream_l;*/
    unsigned int                             uwSubStream_h;     /*_H2ASN_Replace VOS_UINT32 uwSubStream_h;*/
} AUDIO_PCM_PERIOD_ELAPSED_CMD_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_DECODE_REQ_STRU
 功能描述  : AP侧HAL层通过DSP驱动发送消息ID_AP_AUDIO_PLAY_DECODE_REQ，请求Hifi
             对一帧数据进行解码并回写至指定地址
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    AUDIO_FILE_FORMAT_ENUM_UINT16           enFormat;           /* 音频格式 */ /*_H2ASN_Replace VOS_UINT16 enFormat;*/
    unsigned int                            uwSampleRate;       /* 音频数据采样率 */ /*_H2ASN_Replace VOS_UINT32 uwSampleRate;*/
    unsigned int                            uwChannels;         /* 音频数据声道数 */ /*_H2ASN_Replace VOS_UINT32 uwChannels;*/
    unsigned int                            uwDataAddr;         /* 未解码数据缓存 */ /*_H2ASN_Replace VOS_UINT32 uwDataAddr;*/
    unsigned int                            uwDataLen;          /* 缓冲数据长度 */ /*_H2ASN_Replace VOS_UINT32 uwDataLen;*/
    unsigned int                            uwPcmAddr;          /* 待填入解码后数据的缓存 */ /*_H2ASN_Replace VOS_UINT32 uwPcmAddr;*/
    unsigned int                            uwPcmLen;           /* 缓冲数据长度 */ /*_H2ASN_Replace VOS_UINT32 uwPcmLen;*/
} AUDIO_PLAYER_DECODE_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_DECODE_RSP_STRU
 功能描述  : HIFI发送消息ID_AUDIO_AP_PLAY_DECODE_RSP，回复AP解码已完成
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned short                          uhwRet;             /* 处理返回结果 */ /*_H2ASN_Replace VOS_UINT16 uhwRet;*/
    unsigned short                          uhwReserved1;       /*_H2ASN_Replace VOS_UINT16 uhwReserve1;*/
} AUDIO_PLAYER_DECODE_RSP_STRU;


/*****************************************************************************
 实体名称  : AUDIO_PLAYER_START_REQ_STRU
 功能描述  : 该消息请求Hifi启动超低功耗播放
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD51*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                            uwStartPos;         /* 开始解码位置，含文件头 */ /*_H2ASN_Replace VOS_UINT32 uwStartPos;*/
    unsigned short                          uhwWithHeader;      /* AP侧更新的Buff中是否存在512K的文件头，0表示不存在，1表示存在 */ /*_H2ASN_Replace VOS_UINT16 uhwWithHeader;*/
    AUDIO_FILE_FORMAT_ENUM_UINT16           enFormat;           /* 音频文件格式 */ /*_H2ASN_Replace VOS_UINT16 enFormat;*/
    unsigned int                            uwSampleRate;       /* 音频数据采样率 */ /*_H2ASN_Replace VOS_UINT32 uwSampleRate;*/
    unsigned int                            uwOutputDevice;     /* 声音输出设备(耳机或者speaker) */ /*_H2ASN_Replace VOS_UINT32 uwOutputDevice;*/
    unsigned int                            uwTotalFileSize;    /* 整首MP3/AAC音乐的大小，含文件头信息，单位byte */ /*_H2ASN_Replace VOS_UINT32 uwTotalFileSize;*/
    unsigned int                            wavDataSize;        /* 整首wav文件数据大小,不包括文件头 *//*_H2ASN_Replace VOS_UINT32 wavDataSize;*/
} AUDIO_PLAYER_START_REQ_STRU;
/*****************************************************************************
 实体名称  : audio_player_set_vol_req_stru
 功能描述  : 该消息请求设置Hifi超低功耗播放
*****************************************************************************/
 typedef struct
{
    unsigned short                          msg_id;           /*0xDD70*/ /*_H2ASN_Skip */
    unsigned short                          reserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                            left_volume;            /* 左声道音量值，Q15  */ /*_H2ASN_Replace VOS_UINT32 uwValue;*/
    unsigned int                            right_volume;            /* 右声道音量值，Q15  */ /*_H2ASN_Replace VOS_UINT32 uwValue;*/
} audio_player_set_vol_req_stru;

/*****************************************************************************
 实体名称  : AP_HIFI_CCPU_RESET_REQ_STRU
 功能描述  : AP通知HIFI C核复位的消息结构体
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDDE1*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
} AP_HIFI_CCPU_RESET_REQ_STRU;

/*****************************************************************************
 实体名称  : HIFI_AP_CCPU_RESET_CNF_STRU
 功能描述  : 响应ID_AP_HIFI_CCPU_RESET_REQ，如果hifi有语音业务时，停止语音业务，回复AP
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;          /*0xDDE2*/ /*_H2ASN_Skip */
    unsigned short                          uhwResult;         /* 0表示succ， 1表示fail*/ /*_H2ASN_Replace VOS_UINT16 uhwResult;*/
} HIFI_AP_CCPU_RESET_CNF_STRU;

/*****************************************************************************
 实体名称  : APAUDIO_OP_RSLT_STRU
 功能描述  : 该消息向AP回复请求执行执行结果
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwResult;          /* 是否执行成功 */ /*_H2ASN_Replace VOS_UINT16 uhwResult;*/
} APAUDIO_OP_RSLT_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_DONE_IND_STRU
 功能描述  : 该消息通知AP当前音频文件播放结果
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD56*/ /*_H2ASN_Skip */
    AUDIO_PLAY_DONE_IND_ENUM_UINT16         enPlayDone;         /* 播放结果枚举 */ /*_H2ASN_Replace VOS_UINT16 enPlayDone;*/
} AUDIO_PLAYER_DONE_IND_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_PAUSE_REQ_STRU
 功能描述  : 该消息请求Hifi暂停或停止超低功耗解码
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD53*/ /*_H2ASN_Skip */
    unsigned short                          uhwPlayPending;     /* 暂停还是停止播放 */ /*_H2ASN_Replace VOS_UINT16 uhwPlayPending;*/
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned short                          uhwIsChangeDev;     /*_H2ASN_Replace VOS_UINT16 uhwIsChangeDev;*/
} AUDIO_PLAYER_PAUSE_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_PAUSE_CNF_STRU
 功能描述  : 该消息返回Hifi暂停时播放的数据量和结果
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwResult;          /* 是否执行成功 */ /*_H2ASN_Replace VOS_UINT16 uhwResult;*/
    unsigned int                            uwPlayedBytes;      /* 当前已播放的数据量 */ /*_H2ASN_Replace VOS_UINT32 uwPlayedBytes;*/
} AUDIO_PLAYER_PAUSE_CNF_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_PLAYDONE_SIGNAL_REQ_STRU
 功能描述  : AP发到HIFI的播放结束信号请求消息结构
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*_H2ASN_Skip */
    unsigned short                          uhwPlayDone;        /* AP主动结束播放 */ /*_H2ASN_Replace VOS_UINT16 uhwPlayDone;*/
} AUDIO_PLAYER_PLAYDONE_SIGNAL_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_SEEK_REQ_STRU
 功能描述  : AP发到HIFI的seek req消息结构
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD63*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                           uwSeekPos;          /* seek位置 */ /*_H2ASN_Replace VOS_UINT32 uwSeekPos;*/
    AUDIO_PLAYER_SET_LOOP_ENUM_UINT32       enSetLoop;          /* 单曲循环标志位 */ /*_H2ASN_Replace VOS_UINT32 enSetLoop;*/
} AUDIO_PLAYER_SEEK_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_SEEK_CNF_STRU
 功能描述  : 该消息通知AP seek result
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD64*/ /*_H2ASN_Skip */
    AUDIO_PLAY_RESULT_CNF_ENUM_UINT16       enSeekResult;       /* seek结果 */ /*_H2ASN_Replace VOS_UINT16 enSeekResult;*/
} AUDIO_PLAYER_SEEK_CNF_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_UPDATE_BUF_CMD_STRU
 功能描述  : 该消息通知Hifi更新播放BUFFER
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD57*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    DRV_SEND_DATA_STRU                                          /*_H2ASN_Skip */
} AUDIO_PLAYER_UPDATE_BUF_CMD_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_QUERY_TIME_REQ_STRU
 功能描述  : 该消息查询Hifi播放进度状态信息
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD59*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
} AUDIO_PLAYER_QUERY_TIME_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_QUERY_TIME_CNF_STRU
 功能描述  : 该消息Hifi上报播放进度状态信息
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD60*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                            uwPlayedBytes;      /* 当前已播放的音乐文件大小，单位byte，含文件头 */ /*_H2ASN_Replace VOS_UINT32 uwPlayedBytes;*/
} AUDIO_PLAYER_QUERY_TIME_CNF_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PLAYER_QUERY_STATUS_REQ_STRU
 功能描述  : 该消息查询Hifi播放状态信息
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD61*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
} AUDIO_PLAYER_QUERY_STATUS_REQ_STRU;


/*****************************************************************************
 实体名称  : AUDIO_PLAYER_QUERY_STATUS_CNF_STRU
 功能描述  : 该消息Hifi上报播放状态信息
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;           /*0xDD62*/ /*_H2ASN_Skip */
    AUDIO_PLAY_DONE_IND_ENUM_UINT16         enPlayStatus;       /* 播放结果枚举 */ /*_H2ASN_Replace VOS_UINT16 enPlayStatus;*/
} AUDIO_PLAYER_QUERY_STATUS_CNF_STRU;

/*****************************************************************************
 实体名称  : AUDIO_EFFECT_ENABLE_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_EFFECT_ENABLE_REQ给DSP_PID_AUDIO，通知Hifi
      使能音效
*****************************************************************************/
typedef struct{
    unsigned short                          uhwMsgId;           /*0xDD34*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_EFFECT_TYPE_UINT16                enEffectType;       /*_H2ASN_Replace VOS_UINT16 enEffectType;*/
    AUDIO_EFFECT_ENABLE_UINT16              enEffectEnable;     /*_H2ASN_Replace VOS_UINT16 enEffectEnable;*/
}AUDIO_EFFECT_ENABLE_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_EFFECT_SET_PARAMS_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_EFFECT_PARAM_REQ给DSP_PID_AUDIO，通知Hifi
             设置音效参数
*****************************************************************************/
typedef struct{
    unsigned short                          uhwMsgId;           /*0xDD33*/ /*_H2ASN_Skip */
    unsigned short                          uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_EFFECT_TYPE_UINT16                enEffectType;       /* 音效类型 */ /*_H2ASN_Replace VOS_UINT16 enEffectType;*/
    AUDIO_EFFECT_SETPARAMS_UINT16           enEffectSetParam;   /* 设置类型 */ /*_H2ASN_Replace VOS_UINT16 enEffectSetParam;*/
    DRV_SEND_DATA_STRU                                            /*_H2ASN_Skip */
}AUDIO_EFFECT_SET_PARAMS_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_COMP_FILT_SET_PARAMS_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_EFFECT_PARAM_REQ给DSP_PID_AUDIO，通知Hifi
             设置音效参数
*****************************************************************************/
typedef struct{
    unsigned short            uhwMsgId;                         /*_H2ASN_Skip */
    unsigned short            uhwReserve;                       /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned short            uhwPcmCompEnable;                 /* 配置项 使能标志 */ /*_H2ASN_Replace VOS_UINT16 uhwPcmCompEnable;*/
    short                     shwCompGain;                      /* 配置项 施加增益（左移） */ /*_H2ASN_Replace VOS_INT16 shwCompGain;*/
    short                     shwM;                             /* 配置项 滤波器的长度 */ /*_H2ASN_Replace VOS_INT16 shwM; */
    short                     shwReserved;                      /*_H2ASN_Replace VOS_INT16 shwReserved;*/
    short                     ashwCoef[HIFI_AUDIO_PCM_COMP_COEF_LEN_MAX];  /* 补偿滤波参数 */ /*_H2ASN_Replace VOS_INT16 ashwCoef[HIFI_AUDIO_PCM_COMP_COEF_LEN_MAX];*/
}AUDIO_COMP_FILT_SET_PARAMS_REQ_STRU;

/*****************************************************************************
 结构名    : AP_AUDIO_ENHANCE_START_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 启动模块处理消息结构
*****************************************************************************/
typedef struct
{
    unsigned short                      uhwMsgId;           /*0xDD81*/ /*_H2ASN_Skip */
    unsigned short                      uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    unsigned int                        uwSampleRate;       /*_H2ASN_Replace VOS_UINT32 uwSampleRate;*/
    AUDIO_ENHANCE_MODULE_ENUM_UINT32    enModule;           /* 需要启动的模块 */ /*_H2ASN_Replace VOS_UINT32 enModule;*/
}AP_AUDIO_ENHANCE_START_REQ_STRU;

/*****************************************************************************
 结构名    : AP_AUDIO_ENHANCE_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止模块处理消息结构
*****************************************************************************/
typedef struct
{
    unsigned short                      uhwMsgId;           /*0xDD83*/ /*_H2ASN_Skip */
    unsigned short                      uhwReserve;         /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_ENHANCE_MODULE_ENUM_UINT32    enModule;           /* 需要停止的模块 */ /*_H2ASN_Replace VOS_UINT32 enModule;*/
}AP_AUDIO_ENHANCE_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : AP_AUDIO_ENHANCE_SET_DEVICE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 设置设备模式
*****************************************************************************/
typedef struct
{
    unsigned short                      uhwMsgId;               /*0xDD85*/ /*_H2ASN_Skip */
    unsigned short                      uhwReserve;             /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    AUDIO_ENHANCE_DEVICE_ENUM_UINT32    uwDevice;                /*_H2ASN_Replace VOS_UINT32 uwDevice;*/
}AP_AUDIO_ENHANCE_SET_DEVICE_REQ_STRU;


/* 参数设置结构体 */
typedef struct
{
    unsigned short                      usMsgName;              /* 原语类型 */  /*0xDD92*/ /*_H2ASN_Skip*/
    unsigned short                      usReserve;              /* 保留 */      /*_H2ASN_Replace VOS_UINT16 usReserve;*/
    unsigned int                        uwPathID;               /* 路径ID */    /*_H2ASN_Replace VOS_UINT32 uwPathID;*/
    unsigned int                        uwModuleID;             /* 模块ID */    /*_H2ASN_Replace VOS_UINT32 uwModuleID;*/
    unsigned int                        uwSize;                 /* 数据大小 */  /*_H2ASN_Replace VOS_UINT32 uwSize;*/
    unsigned char                       aucData[4];             /* 数据起始 */  /*_H2ASN_Replace VOS_UINT8 aucData;*/

}AP_AUDIO_MLIB_SET_PARA_IND_STRU;

/*****************************************************************************
 实体名称  : AUDIO_EFFECT_DTS_SET_ENABLE_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_SET_DTS_ENABLE_REQ给DSP_PID_AUDIO，通知Hifi设置DTS音效使能与否
*****************************************************************************/
typedef struct{
    unsigned short                      uhwMsgId;               /*0xDD36*/ /*_H2ASN_Skip */ /* 设置DTS音效使能与否ID */
    unsigned short                      uhwEnableFlag;          /* DTS音效是否使能 */ /*_H2ASN_Replace VOS_UINT16 uhwEnableFlag;*/
}AUDIO_EFFECT_DTS_SET_ENABLE_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_EFFECT_DTS_SET_GEQ_TYPE_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_SET_DTS_GEQ_TYPE__REQ给DSP_PID_AUDIO，通知Hifi设置DTS音效类型
*****************************************************************************/
typedef struct{
    unsigned short                      uhwMsgId;               /*0xDD39*/ /*_H2ASN_Skip */ /* 设置DTS音效音效类型ID */
    unsigned short                      uhwGEQTypeIndex;        /* DTS音效类型索引 *//*_H2ASN_Replace VOS_UINT16 uhwGEQTypeIndex;*/
}AUDIO_EFFECT_DTS_SET_GEQ_TYPE_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_EFFECT_DTS_SET_GEQ_ENABLE_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_SET_DTS_GEQ_ENABLE_REQ给DSP_PID_AUDIO，通知Hifi设置DTS GEQ使能
*****************************************************************************/
typedef struct{
    unsigned short                      uhwMsgId;               /*0xDD3B*/ /*_H2ASN_Skip *//* 设置DTS音效 GEQ使能ID */
    unsigned short                      uhwGEQEnableFlag;       /* DTS音效GEQ 是否使能 *//*_H2ASN_Replace VOS_UINT16 uhwGEQEnableFlag;*/
}AUDIO_EFFECT_DTS_SET_GEQ_ENABLE_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_EFFECT_DTS_SET_DEV_REQ_STRU
 功能描述  : AP发送该消息ID_AP_AUDIO_SET_DTS_DEV_REQ给DSP_PID_AUDIO，通知Hifi设置DTS设备模式
*****************************************************************************/
 typedef struct
{
    unsigned short                      uhwMsgId;              /*0xDD38*/ /*_H2ASN_Skip */ /* 设置DTS音效设备模式ID */
    unsigned short                      uhwDevMode;           /* DTS音效设备模式 */ /*_H2ASN_Replace VOS_UINT16 uhwDevMode;*/
} AUDIO_EFFECT_DTS_SET_DEV_REQ_STRU;

/*****************************************************************************
 实体名称  : AUDIO_CMD_COMMON_SET_STRU
 功能描述  : 通用设置
*****************************************************************************/
typedef struct {
    unsigned short                      uhwMsgId;             /*_H2ASN_Skip */
    unsigned short                      uhwReserve;           /*_H2ASN_Skip */
    unsigned int                        uwValue;              /*_H2ASN_Replace VOS_UINT32 uwValue;*/
} AUDIO_CMD_COMMON_SET_STRU;

/*****************************************************************************
 实体名称  : AP_VOICE_REMOTE_AUDIO_REQ_STRU
 功能描述  : 远端播放、录音开始
*****************************************************************************/
typedef struct {
    MSG_HEADER                                      /*_H2ASN_Skip */
    unsigned short              uhwMessageId;       /*_H2ASN_Skip */
    unsigned short              uhwReserve;         /*_H2ASN_Skip */
    unsigned int                uwSampeRate;        /*_H2ASN_Replace VOS_UINT32 uwSampeRate;*/
    unsigned int                uwBufAddr;          /* 缓冲区首地址 */ /*_H2ASN_Replace VOS_UINT32 uwBufAddr;*/
    unsigned int                uwBufSize;          /* 缓冲区的大小，单位byte */ /*_H2ASN_Replace VOS_UINT32 uwBufSize;*/
}AP_VOICE_REMOTE_AUDIO_REQ_STRU;

/*****************************************************************************
 实体名称  : VOICE_AP_REMOTE_AUDIO_CNF_STRU
 功能描述  : 远端播放、录音回复
*****************************************************************************/
typedef struct {
    MSG_HEADER                                      /*_H2ASN_Skip */
    unsigned short                  uhwMessageId;   /*_H2ASN_Skip */
    unsigned short                  uhwReserve;     /*_H2ASN_Skip */
    unsigned int                    uwResult;       /*_H2ASN_Replace VOS_UINT32 uwResult;*/
    VOICE_AUDIO_MODE_ENUM_UINT32    uwMode;          /*_H2ASN_Replace VOS_UINT32 uwMode;*/
}VOICE_AP_REMOTE_AUDIO_CNF_STRU;

/*****************************************************************************
 实体名称  : AP_VOICE_SET_BUF_CMD_STRU
 功能描述  : 设置远端录音、播放数据地址
*****************************************************************************/
typedef struct {
    MSG_HEADER                                          /*_H2ASN_Skip */
    unsigned short                  uhwMessageId;       /*_H2ASN_Skip */
    unsigned short                  uhwReserve;         /*_H2ASN_Skip */
    VOICE_AUDIO_MODE_ENUM_UINT32    uwMode;              /*_H2ASN_Replace VOS_UINT32 uwMode;*/
    unsigned int                    uwBufAddr;          /* 缓冲区首地址 */ /*_H2ASN_Replace VOS_UINT32 uwBufAddr;*/
    unsigned int                    uwBufSize;          /* 缓冲区的大小，单位byte */ /*_H2ASN_Replace VOS_UINT32 uwBufSize;*/
}AP_VOICE_SET_BUF_CMD_STRU;

/*****************************************************************************
 实体名称  : VOICE_AP_REMOTE_PERIOD_ELAPSED_IND_STRU
 功能描述  : 远端录音、播放HIFI侧处理完毕的消息
*****************************************************************************/
typedef struct {
    MSG_HEADER                                          /*_H2ASN_Skip */
    unsigned short                  uhwMessageId;       /*_H2ASN_Skip */
    unsigned short                  uhwReserve;         /*_H2ASN_Skip */
    VOICE_AUDIO_MODE_ENUM_UINT32    uwMode;              /*_H2ASN_Replace VOS_UINT32 uwMode;*/
}VOICE_AP_REMOTE_PERIOD_ELAPSED_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_AP_REMOTE_DATA_ERR_IND_STRU
 功能描述  : 临时性错误或是不可恢复的错误主动上报结构体定义
*****************************************************************************/
typedef struct {
    MSG_HEADER                                          /*_H2ASN_Skip */
    unsigned short  uhwMessageId;                       /*_H2ASN_Skip */
    unsigned short  uhwReserve;                         /*_H2ASN_Skip */
    unsigned int    uwErrorCode;                        /*_H2ASN_Replace VOS_UINT32 uwErrorCode;*/
    VOICE_AUDIO_MODE_ENUM_UINT32    uwMode;               /*_H2ASN_Replace VOS_UINT32 uwMode;*/
}VOICE_AP_REMOTE_DATA_ERR_IND_STRU;

/*****************************************************************************
 实体名称  : VOICE_NO_PARAM_MSG_STRU
 功能描述  : 其他的消息只有消息ID，没有附加的消息参数。
*****************************************************************************/
typedef struct {
    MSG_HEADER                                         /*_H2ASN_Skip */
    unsigned short   usMessageId;                      /*_H2ASN_Skip */
    unsigned short   usReserve;                        /*_H2ASN_Skip */
}VOICE_AP_NO_PARAM_MSG_STRU;

/*****************************************************************************
 实体名称  : AUDIO_COMM_NOTIFY_MSG_STRU
 功能描述  : AP通知HIFI DP时钟开关状态
*****************************************************************************/
typedef struct {
    unsigned short    uhwMsgID;                         /*_H2ASN_Replace VOS_UINT16 uhwMsgID; */
    unsigned short    uwDpClkStatus;                    /*_H2ASN_Replace VOS_UINT16 uwDpClkStatus; */
    unsigned int      uwModule;                         /*_H2ASN_Replace VOS_UINT32 uwModule;*/
}AUDIO_COMM_NOTIFY_MSG_STRU;

/*****************************************************************************
 实体名称  : AP_AUDIO_BSD_CONTROL_REQ_STRU
 功能描述  : AP侧HAL层通过DSP驱动发送消息，通知HIFI BSD语音检测开始or停止
*****************************************************************************/
typedef struct {
    unsigned short                                              uhwMsgId;     /*_H2ASN_Replace VOS_UINT16 uhwMsgId;*/
    unsigned short                                              uhwReserve;   /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    VOICE_BSD_CONTROL_REQ_ENUM_UINT32                           uwValue;      /*_H2ASN_Replace VOS_UINT32 uwValue;*/
} AP_AUDIO_BSD_CONTROL_REQ_STRU;

/*****************************************************************************
 实体名称  : AP_HIFI_MOCKER_HIFI_RESET_CMD_STRU
 功能描述  : 测试用: hal层通知HIFI, 通过特定危险操作触发对应的HIFI单独复位
*****************************************************************************/
typedef struct {
    unsigned short                                              uhwMsgId;       /*_H2ASN_Replace VOS_UINT16 uhwMsgId;*/
    unsigned short                                              uhwReserve;     /*_H2ASN_Replace VOS_UINT16 uhwReserve;*/
    HIFI_RESET_CASE_ENUM_UINT16                                 enResetCase;
    unsigned short                                              uhwReserve2;    /*_H2ASN_Replace VOS_UINT16 uhwReserve2;*/
} AP_HIFI_MOCKER_HIFI_RESET_CMD_STRU;

struct set_angle_cmd{
	unsigned short                  msg_id;
	unsigned short                  reverse;
	unsigned int                    value;
};

#if 0                                                        /* _H2ASN_Skip */
/*****************************************************************************
 实体名称  : AUDIO_LOOP_CNF_STRU
 功能描述  : 该消息通知AP音频环回打开或关闭是否成功
*****************************************************************************/
 typedef struct
{
    unsigned short                          uhwMsgId;                           /*_H2ASN_Skip */
    AUDIO_PLAY_RESULT_CNF_ENUM_UINT16       enAudioLoopCnf;                    /*_H2ASN_Replace VOS_UINT16 enAudioLoopCnf;*/
} AUDIO_LOOP_CNF_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU
 功能描述  : 该消息更新Hifi的播放Buff信息，表示一帧数据已经消费完毕
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*0xDD31*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;           /*_H2ASN_Skip*/
} AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU;

/*****************************************************************************
 实体名称  : AUDIO_PCM_UPDATE_CAPTURE_BUFF_CMD_STRU
 功能描述  : 该消息更新Hifi的录音Buff信息，表示一帧数据已经录制完毕
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;           /*0xDD2F*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;            /*_H2ASN_Skip*/
} AUDIO_PCM_UPDATE_CAPTURE_BUFF_CMD_STRU;

/*****************************************************************************
 结构名    : AUDIO_PCM_ENHANCE_START_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 启动音频增强处理消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;            /*_H2ASN_Skip*/
    VOS_UINT32                          uwSampleRate;
    AUDIO_ENHANCE_MODULE_ENUM_UINT32    enModule;           /* 需要启动的模块 */ /*_H2ASN_Replace VOS_UINT32 enModule;*/
}AUDIO_PCM_ENHANCE_START_IND_STRU;

/*****************************************************************************
 结构名    : AUDIO_PCM_ENHANCE_STOP_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 停止音频增强处理消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    AUDIO_ENHANCE_MODULE_ENUM_UINT32    enModule;           /* 需要启动的模块 */ /*_H2ASN_Replace VOS_UINT32 enModule;*/
}AUDIO_PCM_ENHANCE_STOP_IND_STRU;

/*****************************************************************************
 结构名    : AUDIO_PCM_ENHANCE_SET_DEVICE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 设置设备模式
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip */
    VOS_UINT16                          uhwMsgId;           /*_H2ASN_Skip */
    VOS_UINT16                          uhwReserve;
    AUDIO_ENHANCE_DEVICE_ENUM_UINT32    uwDevice;               /*_H2ASN_Replace VOS_UINT32 uwDevice;*/
}AUDIO_PCM_ENHANCE_SET_DEVICE_IND_STRU;


typedef struct
{
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOICEPP_RSLT_ENUM_UINT16            enExeRslt;                              /* 执行结果 */  /*_H2ASN_Replace VOS_UINT16 enExeRslt;*/
}VOICEPP_OP_RSLT_STRU;

typedef struct
{
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 *//*_H2ASN_Skip*/
    VOS_UINT32                          ulWB;                                   /* 宽窄带信息 */
    VOS_UINT32                          ulBypassFlag;                           /* 是否bypass语音算法 */
    VOICEPP_MODEM_SIO_CLK_ENUM_UINT32   enModemSioClkMaster;                    /* ModemSio时钟主从配置 */ /*_H2ASN_Replace VOS_UINT32 enModemSioClkMaster;*/
}VOICEPP_MC_START_REQ_STRU;

typedef struct
{
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 *//*_H2ASN_Skip*/
}VOICEPP_MC_STOP_REQ_STRU;

typedef struct
{
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulDevice;
}VOICEPP_MC_DEV_REQ_STRU;

typedef struct
{
    VOS_UINT16                          usMsgName;                              /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 *//*_H2ASN_Skip*/
    VOS_UINT32                          ulWB;
}VOICEPP_MC_WB_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 *//*_H2ASN_Skip*/
}VOICEPP_MC_PROC_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 *//*_H2ASN_Skip*/
}VOICEPP_MC_LOOP_DMA_START_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* 保留 */
}VOICEPP_MC_PROC_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /*0xDDB0*/ /*_H2ASN_Skip*/
    AUDIO_HIFIMISC_MSG_TAIL_STRU        stStartMsgTail;                         /*_H2ASN_Replace VOS_UINT32 stStartMsgTail;*/
    VOS_UINT16                          uhwReserved;
}VOICEPP_VOICE_RESET_VOICE_STRU;
#endif                                                      /* _H2ASN_Skip */

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
    AUDIO_MSG_ENUM_UINT16               enMsgID;            /* _H2ASN_MsgChoice_Export AUDIO_MSG_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AUDIO_MSG_ENUM_UINT16
    ****************************************************************************/
}AUDIO_TRACE_MSG_DATA;

/* 协议消息结构*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    AUDIO_TRACE_MSG_DATA                 stMsgData;
}AudioTrace_MSG;

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

#endif /* end of hifidrvinterface.h */
