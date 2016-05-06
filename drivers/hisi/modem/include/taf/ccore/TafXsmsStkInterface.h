/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsSTkInterface.h
  版 本 号   : 初稿
  作    者   : c00299064
  生成日期   : 2015年6月11日
  最近修改   :
  功能描述   : XSMS模块与STK模块相关的定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年06月11日
    作    者   : c00299064
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_XSMS_STK_INTERFACE_H__
#define __TAF_XSMS_STK_INTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "TafAppXsmsInterface.h"


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
enum TAF_XSMS_STK_MSG_TYPE_ENUM
{
    ID_STK_XSMS_SEND_SMS_REQ            = 0,        /* _H2ASN_MsgChoice STK_XSMS_SEND_SMS_REQ_STRU*/ /***< @sa STK_XSMS_SEND_SMS_REQ_STRU */
    ID_XSMS_STK_SEND_SMS_CNF            = 1,        /* _H2ASN_MsgChoice XSMS_STK_SEND_SMS_CNF_STRU*/ /***< @sa XSMS_STK_SEND_SMS_CNF_STRU */
    ID_XSMS_STK_SEND_SMS_RSLT_IND       = 2,        /* _H2ASN_MsgChoice XSMS_STK_SEND_SMS_RSLT_IND_STRU*/ /***< @sa XSMS_STK_SEND_SMS_RSLT_IND_STRU */
    ID_XSMS_STK_RCV_SMS_IND             = 3,        /* _H2ASN_MsgChoice XSMS_STK_RCV_SMS_IND_STRU*/ /***< @sa XSMS_STK_RCV_SMS_IND_STRU */
    ID_XSMS_STK_MSG_TYPE_BUTT
};

typedef VOS_UINT32 TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32;


enum TAF_XSMS_STK_PP_DOWNLOAD_ERR_ENUM
{
    TAF_XSMS_STK_PP_DOWNLOAD_ERR_NONE           = 0,
    TAF_XSMS_STK_PP_DOWNLOAD_ERR_DEST_BUSY      = 33,
    TAF_XSMS_STK_PP_DOWNLOAD_ERR_OTHER_PROBLEM  = 39
};

typedef VOS_UINT16 TAF_XSMS_STK_PP_DOWNLOAD_ERR_ENUM16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/

/** ****************************************************************************
 * Name        : STK_XSMS_SEND_SMS_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32   enMsgId;              /* _H2ASN_Skip */
    VOS_UINT32                          ulIsUserAck;          /* FALSE: NOT USER ACK, TRUE: USER ACK */
    TAF_XSMS_MESSAGE_STRU               st1XSms;
}STK_XSMS_SEND_SMS_REQ_STRU;

/** ****************************************************************************
 * Name        : XSMS_STK_SEND_SMS_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32   enMsgId;              /* _H2ASN_Skip */
    VOS_UINT32                          ulIsUserAck;          /* FALSE: NOT USER ACK, TRUE: USER ACK */
    VOS_UINT32                          ulRet;                /* FALSE:Xsms正在被占用 TRUE可以正常处理 */
}XSMS_STK_SEND_SMS_CNF_STRU;


/** ****************************************************************************
 * Name        : XSMS_STK_SEND_SMS_RSLT_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32   enMsgId;              /* _H2ASN_Skip */
    VOS_UINT32                          ulIsUserAck;          /* FALSE: NOT USER ACK, TRUE: USER ACK */
    VOS_UINT32                          ulSendSucc;           /* FALSE:发送失败， TRUE:发送成功 */
    VOS_UINT32                          ulCauseCode;          /* 失败原因值，成功时忽略此字段 */
}XSMS_STK_SEND_SMS_RSLT_IND_STRU;

/** ****************************************************************************
 * Name        : XSMS_STK_RCV_SMS_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    TAF_XSMS_STK_MSG_TYPE_ENUM_UINT32   enMsgId;              /* _H2ASN_Skip */
    VOS_UINT32                          ulTpduLen;
    TAF_XSMS_MESSAGE_STRU               st1XSms;
    VOS_UINT8                           aucTpduData[4];
}XSMS_STK_RCV_SMS_IND_STRU;


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

#endif /* End of TafXsmsSTkInterface.h */


