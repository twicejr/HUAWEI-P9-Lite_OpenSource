/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaCdsInterface.h
    Description : 内部模块间接口头文件
    History     :
      1.lihong 00150010    2013-07-02  Draft Enact


******************************************************************************/

#ifndef __IMSACDSINTERFACE_H__
#define __IMSACDSINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"


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


#define IMSA_CDS_MSG_ID_HEADER        0
#define CDS_IMSA_MSG_ID_HEADER        10

#define IMSA_CDS_MAX_IMS_BEARER_NUM     (8)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 枚举名    : IMSA_CDS_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : IMSA与CDS之间的消息
*****************************************************************************/
enum    IMSA_CDS_MSG_ID_ENUM
{
    /* IMSA发给CDS的消息原语 */
    ID_IMSA_CDS_SET_IMS_BEARER_REQ          = 0x00 + IMSA_CDS_MSG_ID_HEADER,    /* _H2ASN_MsgChoice IMSA_CDS_SET_IMS_BEARER_REQ_STRU */

    /* CDS发给IMSA的消息原语 */
    ID_IMSA_CDS_SET_IMS_BEARER_CNF          = 0x00 + CDS_IMSA_MSG_ID_HEADER,    /* _H2ASN_MsgChoice IMSA_CDS_SET_IMS_BEARER_CNF_STRU */

    ID_IMSA_CDS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 IMSA_CDS_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : IMSA_CDS_IMS_BEARER_TYPE_ENUM
 枚举说明  : 承载类型枚举
*****************************************************************************/
enum IMSA_CDS_IMS_BEARER_TYPE_ENUM
{
    IMSA_CDS_IMS_BEARER_TYPE_SIGNAL     = 0x00,
    IMSA_CDS_IMS_BEARER_TYPE_MEDIA      = 0x01,

    IMSA_CDS_IMS_BEARER_TYPE_BUTT       = 0xFF
};
typedef VOS_UINT8 IMSA_CDS_IMS_BEARER_TYPE_ENUM_UINT8;





/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : IMSA_CDS_IMS_BEARER_STRU
 结构说明  : IMS承载结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEpsbId;
    IMSA_CDS_IMS_BEARER_TYPE_ENUM_UINT8 enBearerType;
    VOS_UINT8                           aucReserved[2];
} IMSA_CDS_IMS_BEARER_STRU;

/* Add by lihong 2013-12-23 Ut和ims共用APN begin */
/*****************************************************************************
 结构名    : IMSA_CDS_IMS_PORT_INFO_STRU
 结构说明  : IMS使用的端口信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMinImsPort;       /* 小端 */
    VOS_UINT16                          usMaxImsPort;       /* 小端 */
} IMSA_CDS_IMS_PORT_INFO_STRU;
/* Add by lihong 2013-12-23 Ut和ims共用APN end */

/*****************************************************************************
 结构名    : IMSA_CDS_SET_IMS_BEARER_REQ_STRU
 结构说明  : IMSA设置CDS下行过滤承载请求消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulImsBearerNum;
    IMSA_CDS_IMS_BEARER_STRU            astImsBearerArray[IMSA_CDS_MAX_IMS_BEARER_NUM];

    /* Add by lihong 2013-12-23 Ut和ims共用APN begin */
    IMSA_CDS_IMS_PORT_INFO_STRU         stImsPortInfo;
    /* Add by lihong 2013-12-23 Ut和ims共用APN end */
} IMSA_CDS_SET_IMS_BEARER_REQ_STRU;

/*****************************************************************************
 结构名    : IMSA_CDS_SET_IMS_BEARER_REQ_STRU
 结构说明  : IMSA设置CDS下行过滤承载回复消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulResult;
} IMSA_CDS_SET_IMS_BEARER_CNF_STRU;

typedef struct
{
    IMSA_CDS_MSG_ID_ENUM_UINT32         enMsgId;            /*_H2ASN_MsgChoice_Export IMSA_CDS_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_CDS_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}IMSA_CDS_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    IMSA_CDS_INTERFACE_MSG_DATA         stMsgData;
} ImsaCdsInterface_MSG;



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

#endif /* end of ImsaCdsInterface.h */

