/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsEncode.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日s
  功能描述   : TafXsmsEncode.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XSMS_ENCODE_H_
#define _TAF_XSMS_ENCODE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafXsmsDecode.h"
#include  "TafAppXsmsInterface.h"
#include  "TafXsmsInterMsg.h"


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
extern VOS_VOID TAF_XSMS_ReplaceMessageID(
    TAF_XSMS_MESSAGE_STRU              *pucBDStru,
    VOS_UINT16                          usMessageId
);

extern VOS_VOID TAF_XSMS_FillTeleserviceID(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
);

extern VOS_VOID TAF_XSMS_FillServiceCategory(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
);

extern VOS_VOID TAF_XSMS_FillAddress(
    TAF_XSMS_ADDR_STRU                 *pstAddr,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucLen
);

extern VOS_VOID TAF_XSMS_FillSubAddress(
    TAF_XSMS_SUB_ADDR_STRU             *pstSubAddr,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos,
    VOS_UINT8                           enStates
);

extern VOS_VOID TAF_XSMS_FillBearerReplyOpiton(
    VOS_UINT8                           ucBearReplySeqNum,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
);

extern VOS_VOID TAF_XSMS_FillBearerData(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
);

extern VOS_UINT32 TAF_XSMS_GetP2PDBMStru(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT16                          usMessageIdentifier,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT8                           enStates,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDBMStru,
    VOS_UINT32                          ulIsReplySeqNeed
);


extern VOS_UINT32 TAF_XSMS_GetAckDBMStru(
    TAF_XSMS_ADDR_STRU                 *pstAddrStru,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCodeStru,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDBMStru
);

extern VOS_UINT32 TAF_XSMS_EncodeBearDataStruToP2PRaw(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucEncodedLen,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT16                          usMessageIdentifier,
    VOS_UINT8                           enStates,
    VOS_UINT32                          ulIsReplySeqNeeded
);

extern VOS_UINT32 TAF_XSMS_EncodeBearDataStruToSimRaw(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT8                          *pucEncodedLen,
    VOS_UINT8                           enStates,
    VOS_UINT32                          ulIsReplySeqNeeded
);

extern VOS_UINT32 TAF_XSMS_EncodeAckMsg(
    TAF_XSMS_ADDR_STRU                 *pstDestAddr,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCode,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucCodedLen
);

extern VOS_VOID TAF_XSMS_EncodeAuth(
    TAF_XSMS_ADDR_STRU                 *pstDestinationAddr,
    VOS_UINT8                          *pucAuthData
);

VOS_VOID TAF_XSMS_EncodeRelativeValidPeriod
(
    VOS_UINT8                           ucTimeValue, /* timeLen = (ucTimeValue+1)*5 */
    VOS_UINT8                          *pucEncodeLen,
    VOS_UINT8                          *pucData
);

VOS_VOID TAF_XSMS_EncodePrioIndicator
(
    TAF_XSMS_BD_SMS_PRIO_ENUM_UINT8     enPrio,
    VOS_UINT8                          *pucEncodeLen,
    VOS_UINT8                          *pucData
);

VOS_UINT32 TAF_XSMS_EncodeXcallMsgBearDataByContext
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
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

