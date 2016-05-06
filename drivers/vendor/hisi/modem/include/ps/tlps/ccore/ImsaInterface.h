/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaInterface.h
    Description : IMSA对外提供的公共功能接口头文件
    History     :
      1.lihong 00150010    2013-07-10  Draft Enact


******************************************************************************/

#ifndef __IMSAINTERFACE_H__
#define __IMSAINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "TafClientApi.h"


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
 枚举名    : IMSA_INTER_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 对外消息ID定义
*****************************************************************************/
enum    IMSA_INTER_MSG_ID_ENUM
{
    /* CONTROL发给REG的消息原语 */
    ID_IMSA_NORMAL_REG_STATUS_NOTIFY        = TAF_IMSA_COMM_MSG_BASE,           /* _H2ASN_MsgChoice IMSA_NORMAL_REG_STATUS_NOTIFY_STRU */

    ID_IMSA_INTER_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 IMSA_INTER_MSG_ID_ENUM_UINT32;



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    枚举名    : IMSA_SUBCRIBE_TYPE_ENUM
    枚举说明  : 订阅类型
*****************************************************************************/
enum IMSA_SUBCRIBE_TYPE_ENUM
{
    IMSA_SUBCRIBE_TYPE_NORMAL_REG       = 0x00,

    IMSA_SUBCRIBE_TYPE_BUTT             = 0xFF
};
typedef VOS_UINT8 IMSA_SUBCRIBE_TYPE_ENUM_UINT8;

/*****************************************************************************
    枚举名    : IMSA_NORMAL_REG_STATUS_ENUM
    枚举说明  : 普通注册状态
*****************************************************************************/
enum IMSA_NORMAL_REG_STATUS_ENUM
{
    IMSA_NORMAL_REG_STATUS_DEREG        = 0x00,
    IMSA_NORMAL_REG_STATUS_DEREGING     = 0x01,
    IMSA_NORMAL_REG_STATUS_REGING       = 0x02,
    IMSA_NORMAL_REG_STATUS_REG          = 0x03,

    IMSA_NORMAL_REG_STATUS_BUTT             = 0xFF
};
typedef VOS_UINT32 IMSA_NORMAL_REG_STATUS_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : IMSA_NORMAL_REG_STATUS_NOTIFY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMSA_NORMAL_REG_STATUS_NOTIFY_STRU消息结构定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                    /*_H2ASN_Skip*/
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNormalRegStatus;
    VOS_UINT32                          ulPara;
    VOS_UINT32                          ulSubscriptionId;
} IMSA_NORMAL_REG_STATUS_NOTIFY_STRU;


/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    IMSA_INTER_MSG_ID_ENUM_UINT32       ulMsgId;            /* _H2ASN_MsgChoice_Export IMSA_INTER_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_INTER_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} IMSA_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    IMSA_INTERFACE_MSG_DATA             stMsgData;
} ImsaInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32  IMSA_AddSubscription
(
    VOS_UINT32                          ulPid,
    IMSA_SUBCRIBE_TYPE_ENUM_UINT8       enType,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulSubscriptionId
);

extern VOS_UINT32  IMSA_DeleteSubscription(VOS_UINT32 ulSubscriptionId);

/*****************************************************************************
 函数名称: IMSA_IsExitImsService
 协议表格:
 ASN.1 描述:
 函数说明:IMSA提供给其他模块，判断当前是否存在IMS业务
*****************************************************************************/
extern VOS_UINT32  IMSA_IsExitImsService
(
    VOS_VOID
);



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

#endif /* end of ImsaInterface.h */

