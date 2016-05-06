/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaImsInterface.h
    Description : IMSA与IMS消息接口头文件
    History     :
      1.sunbing 00049683    2013-07-5  Draft Enact


******************************************************************************/

#ifndef __IMSAIMSINTERFACE_H__
#define __IMSAIMSINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "ImsaImsEvent.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 枚举名    : IMSA_IMS_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :
*****************************************************************************/
enum    IMSA_IMS_MSG_ID_ENUM
{
    ID_IMSA_IMS_INPUT_CALL_MSG           = 0x0000,                /* _H2ASN_MsgChoice IMSA_IMS_INPUT_CALL_MSG_STRU */
    ID_IMSA_IMS_INPUT_SMS_MSG            = 0x0001,                /* _H2ASN_MsgChoice IMSA_IMS_INPUT_SMS_MSG_STRU */
    ID_IMSA_IMS_INPUT_SERVICE_MSG        = 0x0002,                /* _H2ASN_MsgChoice IMSA_IMS_INPUT_SERVICE_MSG_STRU */
    ID_IMSA_IMS_INPUT_SYSTEM_MSG         = 0x0003,                /* _H2ASN_MsgChoice IMSA_IMS_INPUT_SYSTEM_MSG_STRU */
    ID_IMSA_IMS_INPUT_PARA_MSG           = 0x0004,                /* _H2ASN_MsgChoice IMSA_IMS_INPUT_PARA_MSG_STRU */
    ID_IMSA_IMS_INPUT_USSD_MSG           = 0x0005,                /* _H2ASN_MsgChoice IMSA_IMS_INPUT_USSD_MSG_STRU */
    ID_IMSA_IMS_INPUT_NV_INFO_MSG        = 0x0006,                /* _H2ASN_MsgChoice IMSA_IMS_INPUT_NV_INFO_MSG_STRU */

    ID_IMS_IMSA_OUTPUT_CALL_MSG          = 0x0081,                /* _H2ASN_MsgChoice IMS_IMSA_OUTPUT_CALL_MSG_STRU */
    ID_IMS_IMSA_OUTPUT_SMS_MSG           = 0x0082,                /* _H2ASN_MsgChoice IMS_IMSA_OUTPUT_SMS_MSG_STRU */
    ID_IMS_IMSA_OUTPUT_SERVICE_MSG       = 0x0083,                /* _H2ASN_MsgChoice IMS_IMSA_OUTPUT_SERVICE_MSG_STRU */
    ID_IMS_IMSA_OUTPUT_SYSTEM_MSG        = 0x0084,                /* _H2ASN_MsgChoice IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU */
    ID_IMS_IMSA_OUTPUT_PARA_MSG          = 0x0085,                /* _H2ASN_MsgChoice IMS_IMSA_OUTPUT_PARA_MSG_STRU */
    ID_IMS_IMSA_OUTPUT_USSD_MSG          = 0x0086,                /* _H2ASN_MsgChoice IMS_IMSA_OUTPUT_USSD_MSG_STRU */
    ID_IMS_IMSA_OUTPUT_NV_INFO_MSG       = 0x0087,                /* _H2ASN_MsgChoice IMS_IMSA_OUTPUT_NV_INFO_MSG_STRU */

    ID_IMSA_IMS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 IMSA_IMS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/




/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
 结构名    : IMSA_IMS_INPUT_CALL_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_IMS_INPUT_CALL_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_INPUT_CALL_EVENT_STRU                  stInputCall;
} IMSA_IMS_INPUT_CALL_MSG_STRU;

/*****************************************************************************
 结构名    : IMS_IMSA_OUTPUT_CALL_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS_IMSA_OUTPUT_CALL_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_OUTPUT_CALL_EVENT_STRU                 stOutputCall;
} IMS_IMSA_OUTPUT_CALL_MSG_STRU;


/*****************************************************************************
 结构名    : IMSA_IMS_INPUT_SMS_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_IMS_INPUT_SMS_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_INPUT_SMS_EVENT_STRU                   stInputSms;
} IMSA_IMS_INPUT_SMS_MSG_STRU;

/*****************************************************************************
 结构名    : IMS_IMSA_OUTPUT_SMS_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS_IMSA_OUTPUT_SMS_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_OUTPUT_SMS_EVENT_STRU                  stOutputSms;
} IMS_IMSA_OUTPUT_SMS_MSG_STRU;

/*****************************************************************************
 结构名    : IMSA_IMS_INPUT_SERVICE_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_IMS_INPUT_SERVICE_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_INPUT_SERVICE_EVENT_STRU               stInputService;
} IMSA_IMS_INPUT_SERVICE_MSG_STRU;

/*****************************************************************************
 结构名    : IMS_IMSA_OUTPUT_SERVICE_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS_IMSA_OUTPUT_SERVICE_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU              stOutputService;
} IMS_IMSA_OUTPUT_SERVICE_MSG_STRU;


/*****************************************************************************
 结构名    : IMSA_IMS_INPUT_SYSTEM_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_IMS_INPUT_SYSTEM_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_INPUT_SYSTEM_EVENT_STRU                stInputSystem;
} IMSA_IMS_INPUT_SYSTEM_MSG_STRU;

/*****************************************************************************
 结构名    : IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU               stOutputSystem;
} IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU;

/*****************************************************************************
 结构名    : IMSA_IMS_INPUT_PARA_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_IMS_INPUT_PARA_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_INPUT_PARA_EVENT_STRU                  stInputPara;
} IMSA_IMS_INPUT_PARA_MSG_STRU;

/*****************************************************************************
 结构名    : IMS_IMSA_OUTPUT_PARA_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS_IMSA_OUTPUT_PARA_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_OUTPUT_PARA_EVENT_STRU                 stOutputPara;
} IMS_IMSA_OUTPUT_PARA_MSG_STRU;

/*****************************************************************************
 结构名    : IMSA_IMS_INPUT_USSD_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_IMS_INPUT_USSD_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_INPUT_USSD_EVENT_STRU                  stInputUssd;
} IMSA_IMS_INPUT_USSD_MSG_STRU;

/*****************************************************************************
 结构名    : IMS_IMSA_OUTPUT_USSD_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS_IMSA_OUTPUT_USSD_MSG_STRU消息结构定义
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_OUTPUT_USSD_EVENT_STRU                 stOutputUssd;
} IMS_IMSA_OUTPUT_USSD_MSG_STRU;

/*****************************************************************************
 结构名    : IMSA_IMS_INPUT_PARA_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_IMS_INPUT_PARA_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_INPUT_NV_INFO_EVENT_STRU               stInputNvInfo;
} IMSA_IMS_INPUT_NV_INFO_MSG_STRU;

/*****************************************************************************
 结构名    : IMS_IMSA_OUTPUT_NV_INFO_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS_IMSA_OUTPUT_PARA_MSG_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_ID_ENUM_UINT32                     ulMsgId;
    IMSA_IMS_OUTPUT_NV_INFO_EVENT_STRU              stOutputNvInfo;
} IMS_IMSA_OUTPUT_NV_INFO_MSG_STRU;

typedef struct
{
    IMSA_IMS_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_MsgChoice_Export IMSA_IMS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_IMS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}IMSA_IMS_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    IMSA_IMS_MSG_DATA                    stMsgData;
} ImsaImsInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaImsInterface.h */




