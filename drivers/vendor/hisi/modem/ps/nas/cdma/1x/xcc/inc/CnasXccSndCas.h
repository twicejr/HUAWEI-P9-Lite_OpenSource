/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccSndCas.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年9月15日
  最近修改   :
  功能描述   : CnasXccSndCas.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月15日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CNASXCCSNDCAS_H__
#define __CNASXCCSNDCAS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "cas_1x_access_ctrl_proc_nas_pif.h"
#include  "CnasXccCtx.h"
#include  "cas_1x_control_main_nas_pif.h"


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
VOS_VOID CNAS_XCC_SndCasCallRelReq(
    VOS_UINT8                           ucConnectId,
    VOS_UINT8                           ucConRef,
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason,
    VOS_UINT8                           ucIsRelAll
);

VOS_VOID CNAS_XCC_SndCasEstReq(
    CAS_CNAS_1X_EST_TYPE_ENUM_UINT8     enEstType,
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

VOS_VOID CNAS_XCC_SndCasDschDataReq(
    CAS_CNAS_1X_TX_TCH_MSG_TYPE_ENUM_UINT8                  enTxcDschMsgType,
    CNAS_XCC_TX_ORDER_TYPE_ENUM_UINT8                       enOrderType,
    VOS_UINT8                                               ucMsgSeqNum,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucMsgData
);

VOS_VOID CNAS_XCC_NotifyCasEnterTchSubstate(VOS_VOID);

VOS_VOID CNAS_XCC_SndCasCschDataReq(
    CAS_CNAS_1X_TX_COMMON_MSG_TYPE_ENUM_UINT8               enTxCschMsgType,
    PS_BOOL_ENUM_UINT8                                      enAckReqFlag,
    VOS_UINT8                                              *pucAckPara,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucMsgData
);

VOS_VOID CNAS_XCC_SndCasBeginSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
);

VOS_VOID CNAS_XCC_SndCasEndSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

VOS_VOID CNAS_XCC_SndCasEccServiceReq(VOS_VOID);
#endif

VOS_VOID CNAS_XCC_SndCasLongCodeTransitionNtf(VOS_UINT8 ucUsePrivateLongCodeFlag);
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

#endif /* end of CnasXccSndCas.h */
