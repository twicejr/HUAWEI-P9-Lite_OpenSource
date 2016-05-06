
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallEncKmcMsg.h
  版 本 号   : 初稿
  作    者   : l00359089
  生成日期   : 2015年10月20日
  功能描述   : TafXCallEncKmcMsg.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月20日
    作    者   : l00359089
    修改内容   : 创建文件 for CDMA 1X Iteration 19
******************************************************************************/

#ifndef __TAF_X_CALL_ENC_KMC_MSG_H__
#define __TAF_X_CALL_ENC_KMC_MSG_H__

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

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_XCALL_KMC_ENC_TBL_ITEM(enMsgType, pProcMsgFunc)\
            {\
                (VOS_UINT32)((enMsgType) & 0x000000FF), (pProcMsgFunc)\
            }

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
typedef TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 (*TAF_XCALL_ENC_KMC_MSG_PROC_FUNC)(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);
/*****************************************************************************
结构名    : TAF_XCALL_ENC_KMC_MSG_PROC_STRU
结构说明  : TAF XCALL模块编码KMC消息处理函数的结构
1.日    期  : 2015年10月26日
  作    者  : l00359089
  修改内容  : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulMsgType;          /* TAF XCALL KMC 消息类型*/
    TAF_XCALL_ENC_KMC_MSG_PROC_FUNC                         pProcMsgFunc;
}TAF_XCALL_ENC_KMC_MSG_PROC_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID TAF_XCALL_FillReservedFld(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncKeyReqMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncRemoteCtrlCmdRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);
#ifdef VOS_WIN32
TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncKeyRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncMtEncryptIndMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncErrIndMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateAckMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncRemoteCtrlCmdMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData ,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
);
#endif

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncodeKmcMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
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

#endif /* end of TafXCallEncKmcMsg.h */

