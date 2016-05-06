/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : VcMain.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2012年03月03日
  最近修改   :
  功能描述   : VcMain.c 的头文件
  函数列表   :
  修改历史   :
   1. 日    期   : 2012年03月03日
      作    者   : s62952
      修改内容   : 创建文件

******************************************************************************/
#ifndef _VC_MAIN_H_
#define _VC_MAIN_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include "AppVcApi.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-31, begin */
#include "VcComm.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "VcImsaInterface.h"
#endif
#include "VcCallInterface.h"
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-31, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define VC_MAX_BUFF_MSG_NUM                 (8)

/*内部宏定义*/
#define APP_VC_GetState()                   (g_stVcStateMgmt.enState)

#define APP_VC_GetRadioMode()               (g_stVcStateMgmt.enRadioMode)
#define APP_VC_GetDevHandle()               (g_stVcStateMgmt.iDevHandle)


#define APP_VC_GetPcVoiceSupportFlg()       (g_stVcStateMgmt.ucPcVoiceSupportFlag)
#define APP_VC_GetPcVoicePort()             (g_stVcStateMgmt.ucVoicePort)
#define APP_VC_GetPreMuteStatus()           (g_stVcStateMgmt.enPreMuteStatus)
#define APP_VC_GetCurrMuteStatus()          (g_stVcStateMgmt.enCurrMuteStatus)

#define APP_VC_MUTED_VOLUME                 (-80)
#define APP_VC_UNMUTED_VOLUME               (0)

#define APP_VC_GetCallStatus()              (g_stVcStateMgmt.bInCall)

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, begin */
#define APP_VC_GetStartHifiOrig()           (g_stVcStateMgmt.enStartHifiOrig)
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-11, end */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum APP_VC_STATE_ENUM
{
    APP_VC_S_NULL,                                                              /* 空状态 */
    APP_VC_S_WAIT_INTERNAL_SET_DEV_RSLT,                                        /* 等待DEVICE设置结果状态 */
    APP_VC_S_WAIT_INTERNAL_SET_START_RSLT,                                      /* 等待START设置结果状态 */
    APP_VC_S_WAIT_INTERNAL_SET_CLOSE_RSLT,                                      /* 等待CLOSE设置结果状态 */
    APP_VC_S_WAIT_INTERNAL_SET_CODEC_RSLT,                                      /* 等待CODEC设置结果状态 */
    APP_VC_S_WAIT_AT_SET_DEV_RSLT,                                              /* 等待AT设置DEVICE结果状态 */
    APP_VC_S_WAIT_AT_SET_VOLUME_RSLT,                                           /* 等待AT设置VOLUME结果状态 */
    APP_VC_S_WAIT_AT_SET_MUTE_STATUS_RSLT,                                      /* 等待AT设置静音结果状态 */

    /* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
    APP_VC_S_WAIT_SET_ECALL_CFG_RSLT,                                           /* 等待设置ECALL配置结果状态 */
    /* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

    APP_VC_S_WAIT_SET_FOREGROUND_RSLT,                                          /* 等待设置前台模式结果状态 */
    APP_VC_S_WAIT_SET_BACKGROUND_RSLT,                                          /* 等待设置后台模式结果状态 */
    APP_VC_S_WAIT_QRY_GROUND_RSLT,                                              /* 等待查询前后台模式结果状态 */

    APP_VC_S_BUTT
};
typedef VOS_UINT16  APP_VC_GLOBAL_STATE_ENUM_U16;

enum APP_VC_MSG_ORIGIN_ENUM
{
    APP_VC_MSG_ORIGIN_AT,                                                       /* 来自AT设置的消息 */
    APP_VC_MSG_ORIGIN_TAF,                                                      /* 来自内部消息 */
    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-16, begin */
    APP_VC_MSG_ORIGIN_IMSA,                                                     /* 来自IMSA的消息 */
    /* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-16, end */
    APP_VC_MSG_ORIGIN_BUTT
};
typedef VOS_UINT16  APP_VC_MSG_ORIGIN_ENUM_U16;

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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID APP_VC_BufferMsgProc(VOS_VOID);
VOS_VOID APP_VC_AddBufferMsg(MsgBlock* pMsg);

VOS_VOID APP_VC_SaveClvlVolume(
    APP_VC_NV_CLVL_VOLUME_STRU         *pstClvlVolume
);
VOS_VOID APP_VC_GetClvlVolume(
    APP_VC_NV_CLVL_VOLUME_STRU         *pstClvlVolume
);
VOS_INT16 APP_VC_GetCurrVolume(
    APP_VC_NV_CLVL_VOLUME_STRU         *pstClvlVolume
);
VOS_VOID APP_VC_SetCurrVolume(
    APP_VC_NV_CLVL_VOLUME_STRU         *pstClvlVolume,
    VOS_INT16                           sCurrVolume
);
VC_PHY_DEVICE_MODE_ENUM_U16 APP_VC_GetCurrDevMode(VOS_VOID);

VOS_VOID  APP_VC_AppQryModeReqProc(APP_VC_REQ_MSG_STRU  *pstAppMsg);
VOS_VOID  APP_VC_AppSetPortReqProc(APP_VC_REQ_MSG_STRU *pstAppMsg);
VOS_VOID  APP_VC_AppQryPortReqProc(APP_VC_REQ_MSG_STRU *pstAppMsg);
VOS_UINT32 APP_VC_GetVoiceTestFlag(VOS_UINT32 *pVoiceTestFlag);

/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-31, begin */
#if (FEATURE_ON == FEATURE_IMS)
VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32  APP_VC_ConvertVcOpenChannelFailCauseToImsaExceptionCause(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32              enVcCause
);
CALL_VC_CODEC_TYPE_ENUM_U8  APP_VC_ConvertImsaCodeTypeToCallCodeType(
    IMSA_VC_CODEC_TYPE_ENUM_UINT8       enImsaCodeType
);
VOS_VOID  APP_VC_ImsaStartHifiNtfProc(IMSA_VC_START_HIFI_NTF_STRU* pstMsg);
VOS_VOID  APP_VC_ImsaStopHifiNtfProc(IMSA_VC_STOP_HIFI_NTF_STRU* pstMsg);
VOS_VOID  APP_VC_ImsaHifiParaChangeNtfProc(IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU* pstMsg);
VOS_VOID  APP_VC_ImsaMsgProc(VOS_VOID *pMsg);

#endif
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-07-31, end */
 #if (FEATURE_ON == FEATURE_PTM)
VOS_VOID APP_VC_AppVCFailErrRecord(
    VOS_UINT16                          usName,
    VOS_UINT16                          usCause
);
 #endif

 VOS_VOID  APP_VC_AppQryTTYModeProc(
     APP_VC_REQ_MSG_STRU                *pstAppMsg
 );
 VOS_VOID  APP_VC_AppSetTTYModeProc(
     APP_VC_REQ_MSG_STRU                *pstAppMsg
 );
 TAF_VC_TTYMODE_ENUM_UINT8 APP_VC_GetTTYMode(VOS_VOID);
 VOS_UINT32 APP_VC_SetTTYMode(
    TAF_VC_TTYMODE_ENUM_UINT8           enTTYMode
 );
 VOS_VOID APP_VC_InitTTYMode(VOS_VOID);


/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, begin */
VOS_VOID  APP_VC_CallChannelCloseProc(VOS_VOID);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID  APP_VC_SetMsdProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
);

VOS_VOID  APP_VC_QryMsdProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
);

VOS_VOID  APP_VC_SetEcallCfgProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
);

VOS_VOID  APP_VC_QryEcallCfgProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
);

VOS_VOID APP_VC_MapAppEcallTransStatus(
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8  enVcTransStatus,
    APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8  *penAppStatus
);

VOS_VOID APP_VC_MapAppEcallTransFailCause(
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  enVcFailCause,
    APP_VC_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  *penAppFailCause
);

VOS_VOID APP_VC_MapCallEcallTransStatus(
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8   enVcTransStatus,
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8  *penCallStatus
);

VOS_VOID APP_VC_MapCallEcallTransFailCause(
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enVcFailCause,
    VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  *penCallFailCause
);

VOS_VOID  APP_VC_ReportEcallState(VOS_VOID *pMsg);
VOS_VOID  APP_VC_StartSendMsdData(VOS_VOID *pMsg);

VOS_VOID  APP_VC_CallChannelConnectProc(VOS_VOID);

 VOS_VOID  APP_VC_MedSetMsdCnfProc(VOS_VOID *pMsg);

VOS_VOID APP_VC_MapMedMsdMode(
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16   enAppMode,
    VCVOICE_ECALL_MSD_MODE_ENUM_UINT16 *penVoiceMode
);

VOS_VOID APP_VC_MapMedVocConfig(
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16           enAppMode,
    VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM_UINT16  *penVoiceMode
);

VOS_VOID  APP_VC_SetEcallCfgCnfProc
(
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
);

VOS_VOID APP_VC_RecordAlAckInfo(
    VOS_UINT32                          ulTimesTamp,
    VOS_UINT8                           ucAkAckValue
);

VOS_VOID  APP_VC_ReportAlAckProc(VOS_VOID *pMsg);
#endif

VOS_VOID  APP_VC_InitGlobeVariable(VOS_VOID);

VOS_UINT32 APP_VC_IsVcVoiceWorkTypeTest();

VCVOICE_WORK_TYPE_ENUM_UINT16 APP_VC_GetWorkType(VOS_VOID);

/* Added by j00174725 for V3R3C60_eCall项目, 2014-3-29, end */

VOS_VOID APP_VC_ProcDtmfInd(
    VOICEVC_DTMF_IND_STRU             *pstDtmfInd
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID APP_VC_CallChannelSoCtrlOrderInd(
    MsgBlock                           *pstMsg
);

VOS_VOID APP_VC_CallChannelSoCtrlMsgInd(
    MsgBlock                           *pstMsg
);

#endif

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

#endif /* end of VcMain.h */

