/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and 
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may 
* *    be used to endorse or promote products derived from this software 
* *    without specific prior written permission.
* 
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef __TAF_APP_ADM_H__
#define __TAF_APP_ADM_H__


#include "TafTypeDef.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif


#pragma pack(4)

/* 标志无语音业务的编译开关，问题单A32D12736 */
#define  TAF_FEATURE_NO_VOICE_SERVICE


#ifndef TAF_FEATURE_NO_VOICE_SERVICE

/* error code in ADM*/
#define ADM_SUCCESS                 0
#define ADM_ERR_ERROR               1
#define ADM_ERR_DEV_OCCUPIED        2
#define ADM_ERR_WRONG_SOURCE        3
#define ADM_ERR_DEV_ID_ERROR        4
#define ADM_ERR_WRITE_FORBIDDEN     5
#define ADM_ERR_VOL_EXCEED          6
#define ADM_ERR_SEND_MSG_FAILURE    7
#define ADM_ERR_MUTE_VALUE_ERROR    8
#define ADM_ERR_MALLOC_FAILURE      9


#define ADM_VOL_TYPE_RX             0
#define ADM_VOL_TYPE_TX             1
#define ADM_VOL_TYPE_SIDE           2
#define ADM_SERVICE_TYPE_VOICE      0


#define ADM_SOURCE_VOICE  0
#define ADM_SOURCE_MEDIA  1
#define ADM_SOURCE_TONE   2
#define ADM_DEVICE_VOICE_ACTIVE 2
#define ADM_DEVICE_MEDIA_ACTIVE 1
#define ADM_DEVICE_INACTIVE 0


#define ADM_TRUE    1
#define ADM_FALSE   0

#define ADM_PRIORITY_VOICE          0
#define ADM_PRIORITY_RING           1
#define ADM_PRIORITY_RESERV         2
#define ADM_PRIORITY_MEDIA          3

#define ADM_RSV_PID         0
#define ADM_AMR_RATE        1
#define ADM_DTX_MODE        2
#define ADM_RADIO_MODE  3

/*播放短音时的三个回调函数类型 */
typedef TAF_VOID PauseCallBack();
typedef TAF_VOID PlayCallBack(TAF_UINT8* buf, TAF_UINT32 length, TAF_INT32 loop);
typedef TAF_VOID ResumeCallBack();

typedef TAF_INT32 AudioDevID;

typedef struct PlayToneCallbackStru
{
    PauseCallBack  *pPause;
    PlayCallBack   *pPlay;
    ResumeCallBack *pResume;
}PlayToneCallback;



typedef enum
{
    RING_SID = 0,               /* 电话告警音   loop */
    PWRUP_SID,                  /* 唤醒上电提示音1000ms */
    DIAL_TONE_SID,              /* 拨号提示音loop */
    CALL_SID,                   /* 回铃音loop */
    INT_SID,                    /* 拦截音1   loop */
    ABRV_INT_SID,               /* 拦截音2   4000ms */
    REORD_SID,                  /* 网络拥塞音loop  */
    BUSY_SID,                   /* 忙音loop */
    CONFIRM_TONE_SID,           /* 证实音 600ms */
    CALL_WAITING_SID,           /* 呼叫等待音200ms */
    OFF_HOOK_SID,               /* Off-Hook 警告音loop */
    FADE_TONE_SID,              /* 衰落音1180ms */
    SVC_CHANGE_SID,             /* 业务改变音290ms */
    ALTERNATE_REORDER_SID,      /* 呼叫失败或重配音1790ms */
    MESSAGE_WAITING_SID,        /* 消息等待音1400ms */
    PIP_TONE_SID,               /* Pip音800ms */
    SND_SVC_ACQ_SID,             /* 进入业务提示音 320ms */
    SND_SVC_LOST_SID,            /* 业务LOST提示音 320ms */
    SND_SVC_CHNG_MORE_PREF_SID,  /* 更换到较多首选业务提示音 200ms */
    SND_SVC_CHNG_LESS_PREF_SID,  /* 更换到较少首选业务提示音 200ms */
    SND_EXT_PWR_ON_SID,          /* 外接电源ON音     150ms       */
    SND_EXT_PWR_OFF_SID,         /* 外接电源OFF音   150ms       */
    USER_RING1_SID,              /* 自带铃声1                    */
    USER_RING2_SID,              /* 自带铃声2                    */
    USER_RING3_SID,              /* 自带铃声3                    */
    USER_RING4_SID,              /* 自带铃声4                    */
    USER_RING5_SID,              /* 自带铃声5                    */
    USER_RING6_SID,              /* 自带铃声6                    */
    USER_RING7_SID,              /* 自带铃声7                    */
    USER_RING8_SID,              /* 自带铃声8                    */
    USER_RING9_SID,              /* 自带铃声9                    */
    USER_RING10_SID,             /* 自带铃声10                   */
    SPECIAL_INFO_CADENCE_SID,    /* 特殊信息音     1990ms  */
    SUBSCRIBER_BUSY_SID,         /* Subscriber忙音           loop      */
    CONGESTION_SID,              /* 阻塞音         loop             */
    ERROR_INFORMATION_SID,       /* 错误信息音    2660ms        */
    NUMBER_UNOBTAINABLE_SID,     /* 错误号码音   2660ms         */
    AUTH_FAILURE_SID,            /* 鉴定失效音      2660ms    */
    DTMFTest_SID,                  /* DTMF测试音   loop */
    KEY_TONE0_SID,               /* 按键0 tone音  loop */
    KEY_TONE1_SID,               /* 按键1 tone音  loop */
    KEY_TONE2_SID,               /* 按键2 tone音  loop */
    KEY_TONE3_SID,               /* 按键3 tone音  loop */
    KEY_TONE4_SID,               /* 按键4 tone音  loop */
    KEY_TONE5_SID,               /* 按键5 tone音  loop */
    KEY_TONE6_SID,               /* 按键6 tone音  loop */
    KEY_TONE7_SID,               /* 按键7 tone音  loop */
    KEY_TONE8_SID,               /* 按键8 tone音  loop */
    KEY_TONE9_SID,               /* 按键9 tone音  loop */
    KEY_TONEA_SID,               /* 按键A tone音  loop */
    KEY_TONEB_SID,               /* 按键B tone音  loop */
    KEY_TONEC_SID,               /* 按键C tone音  loop */
    KEY_TONED_SID,               /* 按键D tone音  loop */
    KEY_TONEE_SID,               /* 按键E tone音  loop */
    KEY_TONEF_SID                /* 按键F tone音  loop */
    /*NULL */
}SoundId;

typedef struct{
    unsigned int iRxVol;
    unsigned int iTxVol;
    unsigned int iSideVol;
}ExtraArg;

TAF_INT32 Adm_SendDTMF(SoundId usSoundId, ExtraArg *pArg);
TAF_INT32 Adm_StopDTMF();
TAF_INT32 Adm_SetParam(TAF_UINT8 ucParamId, TAF_UINT32 uiValue);
TAF_INT32 Adm_Open(TAF_UINT8 ucPriority, PlayToneCallback *cbPlayTone);
TAF_INT32 Adm_Close(AudioDevID audioDevId);
TAF_INT32 Adm_SetVolume(TAF_UINT8 ucServiceType, TAF_UINT8 ucVolType, TAF_UINT32 iVol);
TAF_INT32 Adm_SetMute(TAF_UINT8 ucServiceType, TAF_UINT8 ucVolType, TAF_UINT8 ucMute);
#endif /* TAF_FEATURE_NO_VOICE_SERVICE */

#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafAppAdm.h */
