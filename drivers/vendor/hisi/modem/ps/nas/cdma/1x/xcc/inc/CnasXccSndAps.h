/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccSndAps.h
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2014年9月6日
  最近修改   :
  功能描述   : CnasXccSndAps.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月6日
    作    者   : w00242748
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNAS_XCC_SND_APS_H__
#define __CNAS_XCC_SND_APS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CnasXccCtx.h"


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_XCC_SndApsDataCallSuspendInd(
    VOS_UINT8                                   ucConnectId,
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType
);

VOS_VOID CNAS_XCC_SndApsDataCallResumeInd(
    VOS_UINT8                                   ucConnectId,
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType
);

VOS_VOID CNAS_XCC_SndApsOrigDataCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_UINT8                           ucConRef,
    VOS_UINT8                           ucConnectId,
    VOS_INT16                           sRssi
);

VOS_VOID CNAS_XCC_SndApsHangupDataCallCnf(
    VOS_UINT8                           ucCallId
);

VOS_VOID CNAS_XCC_SndApsAnswerDataCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enRslt
);

VOS_VOID CNAS_XCC_SndApsIncomingCallInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

VOS_VOID CNAS_XCC_SndApsDataCallConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

VOS_VOID CNAS_XCC_SndApsDataServiceConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

VOS_VOID CNAS_XCC_SndApsDataCallDiscInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);


VOS_VOID CNAS_XCC_SndApsSoCtrlMsgInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    CNAS_XCC_SOCM_STRU                 *pstSOCM
);

VOS_VOID CNAS_XCC_SndApsUpdateDataCallInfoInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
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

#endif /* end of CnasXsdSndInternalMsg.h */
