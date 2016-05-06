/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsSndCas.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : TafXsmsSndCas.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XSMS_SND_CAS_H_
#define _TAF_XSMS_SND_CAS_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "TafXsmsDecode.h"
#include "TafXsmsEncode.h"
#include "TafXsmsCtx.h"
#include "cas_1x_control_main_nas_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
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
extern VOS_UINT32 TAF_XSMS_TransDbmToDSCHData(TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm, CNAS_CAS_1X_DSCH_DATA_REQ_STRU *pstDschData);

extern VOS_UINT32 TAF_XSMS_TransDbmToCSCHData(TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm, CNAS_CAS_1X_CSCH_DATA_REQ_STRU *pstCschData);

extern VOS_UINT32 TAF_XSMS_SndCasDschDataReq(VOS_UINT8 ucMsgSeqNum, TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm);

extern VOS_UINT32 TAF_XSMS_SndCasCschDataReq(VOS_UINT8 ucMsgSeqNum, VOS_UINT8 *paucData, TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm);
extern VOS_UINT32 TAF_XSMS_SndCasCschOrderMsg
(
    VOS_UINT8                           ucMsgSeqNum,
    PS_BOOL_ENUM_UINT8                  enIsCasAckFlag,
    VOS_UINT8                          *paucCasAckData
);


VOS_VOID TAF_XSMS_SndCasBeginSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                        enSessionType
);

VOS_VOID TAF_XSMS_SndCasEndSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
);


#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
