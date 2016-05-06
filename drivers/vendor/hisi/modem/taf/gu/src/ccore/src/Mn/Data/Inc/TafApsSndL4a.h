/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndL4a.h
  版 本 号   : 初稿
  作    者   : s62952
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : TafApsSndL4a.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : s62952
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSSNDL4A_H__
#define __TAFAPSSNDL4A_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnApsMultiMode.h"
#include "TafApsDecode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_LTE)

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

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : TAF_APS_SndL4aIpv6InfoNotifyInd
 功能描述  : 发送ID_APS_L4A_IPV6_INFO_NOTIFY_IND消息
 输入参数  : ucRabId                    - RAB ID
             pstIpv6RaInfo              - IPv6 RA参数
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 TAF_APS_SndL4aIpv6InfoNotifyInd(
    VOS_UINT8                           ucRabId,
    TAF_PDP_IPV6_RA_INFO_STRU          *pstIpv6RaInfo
);
#endif

VOS_VOID TAF_APS_SndL4aSetCgdcontReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgdscontReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgtftReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgautoReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgcontrdpReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgscontrdpReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgtftrdpReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgeqosReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetCgeqosrdpReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetAuthdataReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aAbortReq(
    VOS_UINT8                           ucCid
);
/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
VOS_VOID TAF_APS_SndL4aGetLteCsReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aGetCemodeReq(
    VOS_VOID                           *pMsgData
);

VOS_VOID TAF_APS_SndL4aSetPdprofReq(
    VOS_VOID                           *pMsgData
);
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */

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

#endif /* end of TafApsSndL4a.h */
