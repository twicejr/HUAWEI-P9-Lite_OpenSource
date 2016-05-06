/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AdmInterface.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2008年3月27日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2008年3月27日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __ADMINTERFACE_H__
#define __ADMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/* error code in ADM*/
#define ADM_SUCCESS                                         0
#define ADM_ERR_ERROR                                       1
#define ADM_ERR_DEV_OCCUPIED                                2
#define ADM_ERR_WRONG_SOURCE                                3
#define ADM_ERR_DEV_ID_ERROR                                4
#define ADM_ERR_WRITE_FORBIDDEN                             5
#define ADM_ERR_VOL_EXCEED                                  6
#define ADM_ERR_SEND_MSG_FAILURE                            7
#define ADM_ERR_MUTE_VALUE_ERROR                            8
#define ADM_ERR_MALLOC_FAILURE                              9

#define ADM_VOL_TYPE_RX                                     0
#define ADM_VOL_TYPE_TX                                     1
#define ADM_VOL_TYPE_SIDE                                   2
#define ADM_SERVICE_TYPE_VOICE                              0


#define ADM_SOURCE_VOICE                                    0
#define ADM_SOURCE_MEDIA                                    1
#define ADM_SOURCE_TONE                                     2
#define ADM_DEVICE_VOICE_ACTIVE                             2
#define ADM_DEVICE_MEDIA_ACTIVE                             1
#define ADM_DEVICE_INACTIVE                                 0

#define ADM_TRUE                                            1
#define ADM_FALSE                                           0

#define ADM_PRIORITY_VOICE                                  0
#define ADM_PRIORITY_RING                                   1
#define ADM_PRIORITY_RESERV                                 2
#define ADM_PRIORITY_MEDIA                                  3

#define ADM_RSV_PID                                         0
#define ADM_AMR_RATE                                        1
#define ADM_DTX_MODE                                        2
#define ADM_RADIO_MODE                                      3

#define ADM_MODE_GSM                                        0
#define ADM_MODE_WCDMA                                      1


/*****************************************************************************
  3 类型定义
*****************************************************************************/
/* 播放短音时的三个回调函数类型 */
typedef VOS_VOID PauseCallBack();
typedef VOS_VOID PlayCallBack(VOS_UINT8* buf, VOS_UINT32 length, VOS_INT32 loop);
typedef VOS_VOID ResumeCallBack();

typedef VOS_INT32 AudioDevID;

typedef struct PlayToneCallbackStru
{
    PauseCallBack  *pPause;
    PlayCallBack   *pPlay;
    ResumeCallBack *pResume;
}PlayToneCallback;

typedef enum
{
    RING_SID                                                = 0,                /* 电话告警音   loop */
    PWRUP_SID,                                                                  /* 唤醒上电提示音1000ms */
    DIAL_TONE_SID,                                                              /* 拨号提示音loop */
    CALL_SID,                                                                   /* 回铃音loop */
    INT_SID,                                                                    /* 拦截音1   loop */
    ABRV_INT_SID,                                                               /* 拦截音2   4000ms */
    REORD_SID,                                                                  /* 网络拥塞音loop  */
    BUSY_SID,                                                                   /* 忙音loop */
    CONFIRM_TONE_SID,                                                           /* 证实音 600ms */
    CALL_WAITING_SID,                                                           /* 呼叫等待音200ms */
    OFF_HOOK_SID,                                                               /* Off-Hook 警告音loop */
    FADE_TONE_SID,                                                              /* 衰落音1180ms */
    SVC_CHANGE_SID,                                                             /* 业务改变音290ms */
    ALTERNATE_REORDER_SID,                                                      /* 呼叫失败或重配音1790ms */
    MESSAGE_WAITING_SID,                                                        /* 消息等待音1400ms */
    PIP_TONE_SID,                                                               /* Pip音800ms */
    SND_SVC_ACQ_SID,                                                            /* 进入业务提示音 320ms */
    SND_SVC_LOST_SID,                                                           /* 业务LOST提示音 320ms */
    SND_SVC_CHNG_MORE_PREF_SID,                                                 /* 更换到较多首选业务提示音 200ms */
    SND_SVC_CHNG_LESS_PREF_SID,                                                 /* 更换到较少首选业务提示音 200ms */
    SND_EXT_PWR_ON_SID,                                                         /* 外接电源ON音     150ms       */
    SND_EXT_PWR_OFF_SID,                                                        /* 外接电源OFF音   150ms       */
    USER_RING1_SID,                                                             /* 自带铃声1                    */
    USER_RING2_SID,                                                             /* 自带铃声2                    */
    USER_RING3_SID,                                                             /* 自带铃声3                    */
    USER_RING4_SID,                                                             /* 自带铃声4                    */
    USER_RING5_SID,                                                             /* 自带铃声5                    */
    USER_RING6_SID,                                                             /* 自带铃声6                    */
    USER_RING7_SID,                                                             /* 自带铃声7                    */
    USER_RING8_SID,                                                             /* 自带铃声8                    */
    USER_RING9_SID,                                                             /* 自带铃声9                    */
    USER_RING10_SID,                                                            /* 自带铃声10                   */
    SPECIAL_INFO_CADENCE_SID,                                                   /* 特殊信息音     1990ms  */
    SUBSCRIBER_BUSY_SID,                                                        /* Subscriber忙音           loop      */
    CONGESTION_SID,                                                             /* 阻塞音         loop             */
    ERROR_INFORMATION_SID,                                                      /* 错误信息音    2660ms        */
    NUMBER_UNOBTAINABLE_SID,                                                    /* 错误号码音   2660ms         */
    AUTH_FAILURE_SID,                                                           /* 鉴定失效音      2660ms    */
    DTMFTest_SID,                                                               /* DTMF测试音   loop */
    KEY_TONE0_SID,                                                              /* 按键0 tone音  loop */
    KEY_TONE1_SID,                                                              /* 按键1 tone音  loop */
    KEY_TONE2_SID,                                                              /* 按键2 tone音  loop */
    KEY_TONE3_SID,                                                              /* 按键3 tone音  loop */
    KEY_TONE4_SID,                                                              /* 按键4 tone音  loop */
    KEY_TONE5_SID,                                                              /* 按键5 tone音  loop */
    KEY_TONE6_SID,                                                              /* 按键6 tone音  loop */
    KEY_TONE7_SID,                                                              /* 按键7 tone音  loop */
    KEY_TONE8_SID,                                                              /* 按键8 tone音  loop */
    KEY_TONE9_SID,                                                              /* 按键9 tone音  loop */
    KEY_TONEA_SID,                                                              /* 按键A tone音  loop */
    KEY_TONEB_SID,                                                              /* 按键B tone音  loop */
    KEY_TONEC_SID,                                                              /* 按键C tone音  loop */
    KEY_TONED_SID,                                                              /* 按键D tone音  loop */
    KEY_TONEE_SID,                                                              /* 按键E tone音  loop */
    KEY_TONEF_SID                                                               /* 按键F tone音  loop */
}SoundId;

typedef struct{
    unsigned int iRxVol;
    unsigned int iTxVol;
    unsigned int iSideVol;
}ExtraArg;


/*****************************************************************************
  4 接口函数声明
*****************************************************************************/
/******************************************************************************
函数名  ：   Adm_SendDTMF
功能描述：   播放DTMF音
输入参数：   usSoundId    DTMF音id
             pArg         参数指针，用于扩展
输出参数：   无
返回值  ：   成功返回0， 错误返回错误码
*******************************************************************************/
int Adm_SendDTMF(SoundId usSoundId, ExtraArg *pArg);
/******************************************************************************
函数名  ：   Adm_StopDTMF
功能描述：   播放DTMF音
输入参数：   无
输出参数：   无
返回值  ：   成功返回0， 错误返回错误码
*******************************************************************************/
int Adm_StopDTMF(VOS_VOID);


/******************************************************************************
函数名  ：   Adm_SetParam
功能描述：   模块间接口，提供给PS或媒体设置相应参数
输入参数：   ucParamId 参数ID
             uiValue   参数值
输出参数：   无
返回值  ：   无
*******************************************************************************/
VOS_INT32 Adm_SetParam(VOS_UINT8 ucParamId, VOS_UINT32 uiValue);

/******************************************************************************
函数名  ：   Adm_Open
功能描述：   打开音频设备的对外接口
输入参数：   ucPriority 音频业务优先级, 取值范围[0~4], 0:语音 1:来电铃声 2:预留 3:媒体
             cbPlayTone 播放短音的回调结构
输出参数：   无
返回值  ：   成功返回0，失败返回错误码
*******************************************************************************/
VOS_INT32 Adm_Open(VOS_UINT8 ucPriority, PlayToneCallback *cbPlayTone);


/******************************************************************************
函数名  ：   Adm_Close
功能描述：   关闭音频设备的对外接口
输入参数：   audioDevId   音频设备ID
输出参数：   无
返回值  ：   成功返回0，失败返回错误码
*******************************************************************************/
VOS_INT32 Adm_Close(AudioDevID audioDevId);


/******************************************************************************
函数名  ：   Adm_SetVolume
功能描述：   设置本地输出音量
输入参数：   ucServiceType   音频业务类型，分为语音、短音、按键音、来电铃声
             ucVol           音量值
输出参数：   无
返回值  ：   成功返回0，错误返回错误码
*******************************************************************************/
VOS_INT32 Adm_SetVolume(VOS_UINT8 ucServiceType, VOS_UINT8 ucVolType, VOS_UINT32 iVol);

/******************************************************************************
函数名  ：   Adm_SetMute
功能描述：   设置本地输出音量的静音状态
输入参数：   ucServiceType   音频业务类型，分为语音、短音、按键音、来电铃声
             ucMute          是否静音的标识
输出参数：   无
返回值  ：   成功返回0，错误返回错误码
*******************************************************************************/
VOS_INT32 Adm_SetMute(VOS_UINT8 ucServiceType, VOS_UINT8 ucVolType, VOS_UINT8 ucMute);


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

#endif /* __ADMINTERFACE_H__ */

