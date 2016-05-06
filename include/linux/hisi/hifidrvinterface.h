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

/*****************************************************************************
 实体名称  : AP_HIFI_CCPU_RESET_REQ_STRU
 功能描述  : AP通知HIFI C核复位的消息结构体
 补充说明  ：需要与vendor\hisi\modem\include\med\hifidrvinterface.h文件中的数据结构保持绝对一致
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

enum AUDIO_MSG_ENUM
{
    ID_AP_VOICEPP_START_REQ             = 0xDD42,                       /* 启动VOICEPP通话 */
    ID_VOICEPP_MSG_START                = ID_AP_VOICEPP_START_REQ,
    ID_VOICEPP_AP_START_CNF             = 0xDD43,
    ID_AP_VOICEPP_STOP_REQ              = 0xDD44,                        /* 终止VOICEPP通话 */
    ID_VOICEPP_AP_STOP_CNF              = 0xDD45,
    ID_AP_VOICEPP_SET_DEVICE_REQ        = 0xDD46,                  /* 配置输入输出设备 */
    ID_VOICEPP_AP_SET_DEVICE_CNF        = 0xDD47,
    ID_AP_VOICEPP_SET_WB_REQ            = 0xDD48,                      /* 设置宽窄带 */
    ID_VOICEPP_AP_SET_WB_CNF            = 0xDD49,
    ID_VOICEPP_MSG_END                  = 0xDD4A,
    /* AP音频驱动与HIFI audio player模块交互消息ID */
    ID_AP_AUDIO_PLAY_START_REQ          = 0xDD51,           /* AP启动Hifi audio player request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_START_REQ_STRU */
    ID_AUDIO_AP_PLAY_START_CNF          = 0xDD52,           /* Hifi启动audio player后回复AP confirm命令 */ /* _H2ASN_MsgChoice APAUDIO_OP_RSLT_STRU */
    ID_AP_AUDIO_PLAY_PAUSE_REQ          = 0xDD53,           /* AP停止Hifi audio player request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_PAUSE_REQ_STRU */
    ID_AUDIO_AP_PLAY_PAUSE_CNF          = 0xDD54,           /* Hifi停止audio player后回复AP confirm命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_PAUSE_CNF_STRU */
    ID_AUDIO_AP_PLAY_DONE_IND           = 0xDD56,           /* Hifi通知AP audio player一块数据播放完毕或者播放中断indication */ /* _H2ASN_MsgChoice AUDIO_PLAYER_DONE_IND_STRU */
    ID_AP_AUDIO_PLAY_UPDATE_BUF_CMD     = 0xDD57,           /* AP通知Hifi新数据块更新command */ /* _H2ASN_MsgChoice AUDIO_PLAYER_UPDATE_BUF_CMD_STRU */
    ID_AP_AUDIO_PLAY_QUERY_TIME_REQ     = 0xDD59,           /* AP查询Hifi audio player播放进度request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_TIME_REQ_STRU */
    ID_AP_AUDIO_PLAY_WAKEUPTHREAD_REQ   = 0xDD5A,           /* AP主动结束播放 */
    ID_AUDIO_AP_PLAY_QUERY_TIME_CNF     = 0xDD60,           /* Hifi回复AP audio player播放进度confirm命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_TIME_CNF_STRU */
    ID_AP_AUDIO_PLAY_QUERY_STATUS_REQ   = 0xDD61,           /* AP查询Hifi audio player播放状态request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_STATUS_REQ_STRU */
    ID_AUDIO_AP_PLAY_QUERY_STATUS_CNF   = 0xDD62,           /* Hifi回复AP audio player播放状态confirm命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_QUERY_STATUS_CNF_STRU */
    ID_AP_AUDIO_PLAY_SEEK_REQ           = 0xDD63,           /* AP seek Hifi audio player到某一位置request命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SEEK_REQ_STRU */
    ID_AUDIO_AP_PLAY_SEEK_CNF           = 0xDD64,           /* Hifi回复AP seek结果confirm命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SEEK_CNF_STRU */

    /* AP音频驱动与audio loop环回交互消息ID */
    ID_AP_AUDIO_LOOP_BEGIN_REQ          = 0xDD65,           /* AP启动Hifi begin audio loop request命令 */
    ID_AUDIO_AP_LOOP_BEGIN_CNF          = 0xDD66,           /* Hifi回复AP begin audio loop结果confirm命令 */ /* _H2ASN_MsgChoice AUDIO_LOOP_CNF_STRU */
    ID_AP_AUDIO_LOOP_END_REQ            = 0xDD67,           /* AP启动Hifi end audio loop request命令 */ /* _H2ASN_MsgChoice AUDIO_PCM_OPEN_REQ_STRU */
    ID_AUDIO_AP_LOOP_END_CNF            = 0xDD68,           /* Hifi回复AP end audio loop结果confirm命令 */ /* _H2ASN_MsgChoice AUDIO_LOOP_CNF_STRU */
    ID_AP_AUDIO_PLAY_SET_VOL_CMD        = 0xDD70,           /* AP设置超低功耗播放音量命令 */ /* _H2ASN_MsgChoice AUDIO_PLAYER_SET_VOL_REQ_STRU */

    /* AP音频驱动与录音模块交互消息 */
    ID_AP_AUDIO_RECORD_START_CMD        = 0xDD40,           /* _H2ASN_MsgChoice AUDIO_RECORD_START_STRU */
    ID_AP_AUDIO_RECORD_STOP_CMD         = 0xDD41,           /* _H2ASN_MsgChoice AUDIO_RECORD_STOP_STRU */

    /* AP音频驱动与ENHANCE模块交互消息 */
    ID_AP_AUDIO_ENHANCE_START_REQ       = 0xDD81,           /* _H2ASN_MsgChoice AP_AUDIO_ENHANCE_START_REQ_STRU */
    ID_AUDIO_AP_ENHANCE_START_CNF       = 0xDD82,           /* _H2ASN_MsgChoice APAUDIO_OP_RSLT_STRU */
    ID_AP_AUDIO_ENHANCE_STOP_REQ        = 0xDD83,           /* _H2ASN_MsgChoice AP_AUDIO_ENHANCE_STOP_REQ_STRU */
    ID_AUDIO_AP_ENHANCE_STOP_CNF        = 0xDD84,           /* _H2ASN_MsgChoice APAUDIO_OP_RSLT_STRU */
    ID_AP_AUDIO_ENHANCE_SET_DEVICE_REQ  = 0xDD85,           /* _H2ASN_MsgChoice AP_AUDIO_ENHANCE_SET_DEVICE_REQ_STRU */
    ID_AUDIO_AP_ENHANCE_SET_DEVICE_CNF  = 0xDD86,           /* _H2ASN_MsgChoice APAUDIO_OP_RSLT_STRU */

    ID_AUDIO_PCM_ENHANCE_SET_DEVICE_IND = 0xDD91,           /* _H2ASN_MsgChoice AUDIO_PCM_ENHANCE_SET_DEVICE_IND_STRU */
    ID_AP_AUDIO_MLIB_SET_PARA_IND       = 0xDD92,           /* _H2ASN_MsgChoice AP_AUDIO_MLIB_SET_PARA_IND_STRU */
    ID_AUDIO_PCM_ENHANCE_START_IND      = 0xDD93,           /* _H2ASN_MsgChoice AUDIO_PCM_ENHANCE_START_IND_STRU */
    ID_AUDIO_PCM_ENHANCE_STOP_IND       = 0xDD94,           /* _H2ASN_MsgChoice AUDIO_PCM_ENHANCE_STOP_IND_STRU */

	/* AP音频驱动与命令模块交互消息 */
    ID_AP_AUDIO_CMD_SET_SOURCE_CMD      = 0xDD95,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_SET_DEVICE_CMD      = 0xDD96,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_SET_MODE_CMD        = 0xDD97,           /* _H2ASN_MsgChoice AUDIO_CMD_COMMON_SET_STRU */
    ID_AP_AUDIO_CMD_MLIB_SET_PARA_CMD   = 0xDD92,           /* _H2ASN_MsgChoice AP_AUDIO_MLIB_SET_PARA_IND_STRU */

    /* AP音频驱动与HIFI音频通道模块交互消息ID */
    ID_AP_AUDIO_PCM_OPEN_REQ            = 0xDD25,           /* _H2ASN_MsgChoice AUDIO_PCM_OPEN_REQ_STRU */
    ID_AP_AUDIO_PCM_CLOSE_REQ           = 0xDD26,           /* _H2ASN_MsgChoice AUDIO_PCM_CLOSE_REQ_STRU */
    ID_AP_AUDIO_PCM_HW_PARA_REQ         = 0xDD27,           /* _H2ASN_MsgChoice AUDIO_PCM_HW_PARAMS_REQ_STRU */
    ID_AP_AUDIO_PCM_HW_FREE_REQ         = 0xDD28,           /* 暂未使用，保留 */
    ID_AP_AUDIO_PCM_PREPARE_REQ         = 0xDD29,           /* 暂未使用，保留 */
    ID_AP_AUDIO_PCM_TRIGGER_REQ         = 0xDD2A,           /* _H2ASN_MsgChoice AUDIO_PCM_TRIGGER_REQ_STRU */
    ID_AP_AUDIO_PCM_POINTER_REQ         = 0xDD2B,           /* 暂未使用，保留 */
    ID_AP_AUDIO_PCM_SET_BUF_CMD         = 0xDD2C,           /* _H2ASN_MsgChoice AUDIO_PCM_SET_BUF_CMD_STRU */
    ID_AUDIO_AP_PCM_PERIOD_ELAPSED_CMD  = 0xDD2D,           /* _H2ASN_MsgChoice AUDIO_PCM_PERIOD_ELAPSED_CMD_STRU */

    /* HIFI音频通道模块内部交互消息ID */
    ID_AUDIO_UPDATE_PLAY_BUFF_CMD       = 0xDD2E,           /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */
    ID_AUDIO_UPDATE_CAPTURE_BUFF_CMD    = 0xDD2F,           /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */
    ID_AUDIO_AP_PCM_TRIGGER_CNF         = 0xDDA0,           /* _H2ASN_MsgChoice AUDIO_PCM_TRIGGER_CNF_STRU */

    ID_AP_HIFI_TEST_CMD                 = 0xDD32,           /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */

    /* HIFI PCM模块与audio player模块内部交互消息ID */
    ID_AUDIO_UPDATE_PLAYER_BUFF_CMD     = 0xDD31,           /* audio PCM通知player更新播放buff数据 */ /* _H2ASN_MsgChoice AUDIO_PCM_UPDATE_PLAY_BUFF_CMD_STRU */

    /* AP和HIFI关于音效的交互消息 */
    ID_AP_AUDIO_EFFECT_ENABLE_REQ       = 0xDD34,           /* 待定 */  /* _H2ASN_MsgChoice AUDIO_EFFECT_ENABLE_REQ_STRU */
    ID_AP_AUDIO_EFFECT_PARA_REQ         = 0xDD33,           /* 待定 */  /* _H2ASN_MsgChoice AUDIO_EFFECT_SET_PARAMS_REQ_STRU */

    /* AP和HIFI的DTS交互消息 */
    ID_AP_AUDIO_SET_DTS_ENABLE_CMD       = 0xDD36,           /* AP通知Hifi使能DTS */  /* _H2ASN_MsgChoice AUDIO_EFFECT_DTS_SET_ENABLE_REQ_STRU */
    /* ID_AUDIO_PLAYER_SET_DTS_ENABLE_IND  0xDD37               内部消息占用 */
    ID_AP_AUDIO_SET_DTS_DEV_CMD          = 0xDD38,           /* AP通知Hifi DTS 输出设备模式 */  /* _H2ASN_MsgChoice AUDIO_EFFECT_DTS_SET_DEV_REQ_STRU */

    /* A核通知HIFI C 核复位消息ID */
    ID_AP_HIFI_CCPU_RESET_REQ           = 0xDDE1,           /* _H2ASN_MsgChoice AP_HIFI_CCPU_RESET_REQ_STRU */

    /* hifi回复ID_AP_HIFI_CCPU_RESET_REQ */
    ID_HIFI_AP_CCPU_RESET_CNF           = 0xDDE2,           /* _H2ASN_MsgChoice HIFI_AP_CCPU_RESET_CNF_STRU */

    /* for 3mic: A核通知HIFI 3Mic/4Mic 通路已建立，允许启动DMA */
    ID_AP_AUDIO_ROUTING_COMPLETE_REQ    = 0xDDC0,
    ID_AUDIO_AP_ROUTING_COMPLETE_CNF    = 0xDDC6,
    /* HIFI 通知A核DMA配置完成，可以打开Codec DP时钟 */
    ID_AUDIO_AP_DMA_CONFIG_IND          = 0xDDC7,
    /* A核通知HIFI ，Codec DP时钟已打开 */
    ID_AP_AUDIO_DP_OPEN_IND             = 0xDDC8,
};

//for 3mic: struct for ioctl cmd to notify hifi 3Mic/4Mic routing complete
typedef struct {
    unsigned short    msgID;
    unsigned short    reserve;
}AUDIO_COMM_NOTIFY_REQ_STRU;

typedef struct {
    unsigned short    msgID;
    unsigned short    result;       //0表示成功，1表示失败
}AUDIO_COMM_NOTIFY_CNF_STRU;

typedef struct
{
    unsigned short    uhwMsgId;
    unsigned short    reserve;
} AUDIO_COMM_DMA_CONFIG_DONE_IND_STRU;

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
