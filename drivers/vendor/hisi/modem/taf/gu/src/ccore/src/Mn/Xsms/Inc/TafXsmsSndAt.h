/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsSndAt.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : TafXsmsSndAt.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XSMS_SND_AT_H_
#define _TAF_XSMS_SND_AT_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafAppXsmsInterface.h"
#include "TafXsmsDecode.h"
#include "TafXsmsStkInterface.h"

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
extern VOS_UINT32 TAF_XSMS_MsgInitInd(VOS_UINT32 ulTotalNum);

extern VOS_UINT32 TAF_XSMS_MsgSubmitCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulRslt
);
extern VOS_UINT32 TAF_XSMS_MsgWriteCnf(VOS_UINT16 usClientId,  VOS_UINT8 ucOpId, VOS_UINT32 ulRslt, VOS_UINT32 ulIndex);

extern VOS_UINT32 TAF_XSMS_MsgDeleteCnf(VOS_UINT16 usClientId, VOS_UINT8 ucOpId, VOS_UINT32 ulRslt);

extern VOS_UINT32 TAF_XSMS_MsgSubmitSuccInd(VOS_UINT32 ulMr);

extern VOS_UINT32 TAF_XSMS_MsgDeliveryInd(TAF_XSMS_MESSAGE_STRU *pstDeliveryMsg);

extern VOS_UINT32 TAF_XSMS_MsgUimFullInd(VOS_VOID);

extern VOS_UINT32 TAF_XSMS_SmsEventCallBack(
    TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32  enEventType,
    TAF_XSMS_APP_AT_EVENT_INFO_STRU   *pstEvent);
extern VOS_UINT32 TAF_XSMS_MsgSubmitFailInd(VOS_UINT32 ulCourceCode);
extern VOS_UINT32 TAF_XSMS_SetAPFullCnf(VOS_UINT16 usClientId, VOS_UINT8 ucOpId, VOS_UINT32 ulRslt);
extern VOS_UINT32 TAF_XSMS_SendStkRsltInd(
            VOS_UINT32                          ulSendRslt,
            VOS_UINT32                          ulCauseCode
);

extern VOS_VOID TAF_XSMS_StkMsgSubmitCnf(VOS_UINT32 ulRet);
extern VOS_VOID TAF_XSMS_SendStkCATPTMsg(VOS_UINT32 ulLen,
                                                    VOS_UINT8 *pucTpdu,
                                                    TAF_XSMS_MESSAGE_STRU *pst1XSms);

extern VOS_VOID TAF_XSMS_SendXpdsGpsSms(
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucData
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
