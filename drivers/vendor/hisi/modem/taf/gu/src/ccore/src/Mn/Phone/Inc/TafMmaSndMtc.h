/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndMtc.h
  版 本 号   : 初稿
  作    者   : h00313353
  生成日期   : 2015年11月05日
  最近修改   :
  功能描述   : TafMmaSndMtc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月05日
    作    者   : h00313353
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_MMA_SND_MTC_H_
#define _TAF_MMA_SND_MTC_H_
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MmaMsccInterface.h"
#include "TafSdcCtx.h"
#include "NasUtranCtrlInterface.h"
#include "MtcMmaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)
/*****************************************************************************
  2 宏定义
*****************************************************************************/

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
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_VOID TAF_MMA_SndMtcSysInfo(
    VOS_UINT8                           ucIsFobbiddenPlmnFlag,
    VOS_UINT8                           ucPsSupportFlg
);

VOS_VOID TAF_MMA_SndMtcEplmnInfoInd(
    MSCC_MMA_EPLMN_INFO_IND_STRU        *pstEplmnInfoIndMsg
);

VOS_VOID TAF_MMA_SndMtcRatModeInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
);

VOS_VOID TAF_MMA_SndMtcPowerStateInd(
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState
);

VOS_VOID TAF_MMA_SndMtcCurrCampPlmnInfoInd(
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU   *pstPlmnInfo
);

VOS_VOID TAF_MMA_SndMtcRegStatusInd(
    VOS_UINT8                          ucIsUsimValidFlag
);

VOS_VOID TAF_MMA_SndMtcRatCfgInd(
    TAF_MMA_RAT_ORDER_STRU            *pstNewRatOrder
);

VOS_VOID TAF_MMA_SndMtcImsaStateInd(
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState
);
#endif

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_MMA_SndMtcImsVoiceCapInd(
    VOS_UINT8                           ucAvail
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

#endif /* end of TafMmaSndMtc.h */

