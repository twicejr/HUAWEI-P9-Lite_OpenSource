
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallDecKmcMsg.h
  版 本 号   : 初稿
  作    者   : l00359089
  生成日期   : 2015年10月20日
  功能描述   : TafXCallDecKmcMsg.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月20日
    作    者   : l00359089
    修改内容   : 创建文件 for CDMA 1X Iteration 19
******************************************************************************/

#ifndef __TAF_X_CALL_DEC_KMC_MSG_H__
#define __TAF_X_CALL_DEC_KMC_MSG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "TafXCallKmcCommType.h"

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

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_UINT32 TAF_XCALL_ConvertBcdToDecimal(
    VOS_UINT8                                              *pucSrcData,
    VOS_UINT16                                             *pusDestData
);

VOS_UINT32 TAF_XCALL_ConvertBcdTimeStampToDecimalTimeStamp(
    VOS_UINT8                                              *pucSrcData,
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeStamp
);

VOS_VOID TAF_XCALL_DecKeyRspMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecMtEncryptIndMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecPubKeyUpdateMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecErrIndMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecPubKeyUpdateAckMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecRemoteCtrlCmdMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
);

VOS_VOID TAF_XCALL_DecodeKmcMsg(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                          usMsgDataLen,
    TAF_XCALL_KMC_MSG_STRU             *pstDecodedData
);

#endif

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

#endif /* end of TafXCallDecKmcMsg.h */

