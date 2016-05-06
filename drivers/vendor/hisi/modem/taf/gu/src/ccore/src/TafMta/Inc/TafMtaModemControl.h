/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaModemControl.h
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2013年10月21日
  最近修改   :
  功能描述   : TafMtaModemControl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年03月11日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFMTAMODEMCONTROL_H__
#define __TAFMTAMODEMCONTROL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#if (FEATURE_ON == FEATURE_DSDS)
#include "PsRrmInterface.h"
#endif

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
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
VOS_VOID TAF_MTA_RcvMtcPsTransferInd(
    VOS_VOID                           *pMsg
);
#endif


VOS_VOID TAF_MTA_RcvAtQryMipiClkReq(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiMipiClkExpired(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvMtcMipiClkInfoInd(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_SndMipiClkInfoToAt(VOS_UINT16 usMipiClk);

#if (FEATURE_ON == FEATURE_DSDS)
VOS_UINT32 TAF_MTA_SndRrmProtectPsInd(VOS_VOID);

VOS_UINT32 TAF_MTA_SndRrmDeProtectPsInd(VOS_VOID);

VOS_UINT32 TAF_MTA_SndRrmPsProtectType(
    PS_BOOL_ENUM_UINT8                  usRrmPsProtectType
);

VOS_UINT32 TAF_MTA_SndAsPsProtectIndMsg(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT8                           ucProtectFlg
);

VOS_VOID TAF_MTA_SndAtSetPsProtectCnf(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    AT_MTA_MSG_TYPE_ENUM_UINT32         enErr
);

VOS_VOID TAF_MTA_RcvAtPsProtectSetReq(
    VOS_VOID                           *pMsg
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

#endif /* end of TafMtaModemControl.h */
