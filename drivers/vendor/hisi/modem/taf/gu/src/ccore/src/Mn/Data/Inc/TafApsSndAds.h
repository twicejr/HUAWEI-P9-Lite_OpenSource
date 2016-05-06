/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndAds.h
  版 本 号   : 初稿
  作    者   : m00217266
  生成日期   : 2014年1月27日
  最近修改   :
  功能描述   : TafApsSndAds.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月27日
    作    者   : m00217266
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_APS_SNDADS_H__
#define __TAF_APS_SNDADS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "Ps.h"
#include "AdsInterface.h"
#include "Taf_Aps.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* Added by m00217266 for L-C互操作项目, 2014-1-26, begin */
/* APP QOS: */
#define TAF_APS_APP_QOS_TRAFFIC_CLASS_CONVERSATIONAL        (0)
#define TAF_APS_APP_QOS_TRAFFIC_CLASS_STREAMING             (1)
#define TAF_APS_APP_QOS_TRAFFIC_CLASS_INTERACTIVE           (2)
#define TAF_APS_APP_QOS_TRAFFIC_CLASS_BACKGROUND            (3)

/* APP QOS: Traffic Handling */
#define TAF_APS_APP_QOS_TRAFFIC_HANDLING_PRIORITY_1         (1)
#define TAF_APS_APP_QOS_TRAFFIC_HANDLING_PRIORITY_2         (2)
#define TAF_APS_APP_QOS_TRAFFIC_HANDLING_PRIORITY_3         (3)

/* APP QOS: Source Statistic Descriptor */
#define TAF_APS_APP_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN        (0)
#define TAF_APS_APP_QOS_SRC_STATS_DESCRIPTOR_SPEECH         (1)

/* APP QOS: Transfer Delay */
#define TAF_APS_APP_QOS_TRANSFER_DELAY_150MS                (150)

/* APP QOS: Signal Ind */
#define TAF_APS_APP_QOS_SIGNAL_IND_NOT_OPTIMISE             (0)
#define TAF_APS_APP_QOS_SIGNAL_IND_OPTIMISE                 (1)
/* Added by m00217266 for L-C互操作项目, 2014-1-26, end */

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

/* Added by m00217266 for L-C互操作项目, 2014-1-26, begin */
ADS_QCI_TYPE_ENUM_UINT8 TAF_APS_QosParaTransferToQci(
    TAF_UMTS_QOS_STRU                   *pQos
);

VOS_VOID TAF_APS_SendAdsPdpStatusInd(
    VOS_UINT32                          ulPid,
    ADS_PDP_STATUS_IND_STRU            *pstAdsInd
);

VOS_VOID TAF_APS_NotifyAdsWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
);

VOS_VOID TAF_APS_NotifyAdsWhenPdpDeactivated(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU    *pstEvent
);

VOS_VOID TAF_APS_NotifyAdsWhenPdpAvtivated(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);
/* Added by m00217266 for L-C互操作项目, 2014-1-26, end */


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

#endif /* end of TafApsSndAds.h */

