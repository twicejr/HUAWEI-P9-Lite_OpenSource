

#ifndef __TCRABMINTERFACE_H__
#define __TCRABMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
/*RABM->TC Command消息前3个字节宏定义 RABM->TC*/
#define ERABM_ETC_MSG_ID_HEADER            PS_MSG_ID_RABM_TO_TC_BASE

/*TC ->RABM Command消息前3个字节宏定义 TC->RABM*/
#define ETC_ERABM_MSG_ID_HEADER            PS_MSG_ID_TC_TO_RABM_BASE

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : ETC_ERABM_MSG_TYPE_ENUM
 枚举说明  : TC与RABM消息类型
*****************************************************************************/
enum ETC_ERABM_MSG_TYPE_ENUM
{
    /*消息原语*/
    /*TC发送给RABM的消息原语*/
    ID_ETC_ERABM_ACTIVATE_TEST_MODE             = (0x01+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_ACTIVATE_TEST_MODE_STRU */
    ID_ETC_ERABM_DEACTIVATE_TEST_MODE           = (0x02+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_DEACTIVATE_TEST_MODE_STRU */
    ID_ETC_ERABM_REL_REQ                        = (0x03+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_REL_REQ_STRU */
    ID_ETC_ERABM_SUSPEND_RSP                    = (0x04+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_SUSPEND_RSP_STRU */
    ID_ETC_ERABM_RESUME_RSP                     = (0x05+ETC_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_RESUME_RSP_STRU */

    /*RABM发送给TC的消息原语*/
    ID_ETC_ERABM_REL_IND                        = (0x01+ERABM_ETC_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_REL_IND_STRU */
    ID_ETC_ERABM_SUSPEND_IND                    = (0x02+ERABM_ETC_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_SUSPEND_IND_STRU */
    ID_ETC_ERABM_RESUME_IND                     = (0x03+ERABM_ETC_MSG_ID_HEADER),/* _H2ASN_MsgChoice ETC_ERABM_RESUME_IND_STRU */

    ID_ETC_ERABM_BUTT
};
typedef VOS_UINT32 ETC_ERABM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : ETC_ERABM_RSLT_TYPE_ENUM
 枚举说明  : TC回复RABM消息结果枚举
*****************************************************************************/
enum ETC_ERABM_RSLT_TYPE_ENUM
{
    ETC_ERABM_RSLT_TYPE_SUCC             = 0x00, /*成功*/
    ETC_ERABM_RSLT_TYPE_FAIL             = 0x01, /*失败*/

    ETC_ERABM_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 ETC_ERABM_RSLT_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : ETC_ERABM_ACTIVATE_TEST_MODE_STRU
 结构说明  : ETC_ERABM_ACTIVATE_TEST_MODE_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
} ETC_ERABM_ACTIVATE_TEST_MODE_STRU;

/*****************************************************************************
 结构名    : ETC_ERABM_DEACTIVATE_TEST_MODE_STRU
 结构说明  : ETC_ERABM_DEACTIVATE_TEST_MODE_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
} ETC_ERABM_DEACTIVATE_TEST_MODE_STRU;

/*****************************************************************************
 结构名    : ETC_ERABM_REL_REQ_STRU
 结构说明  : ETC_ERABM_REL_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/            /* 消息头*/
    VOS_UINT32                           ulReserved;         /* 保留字*/
}ETC_ERABM_REL_REQ_STRU;

/*****************************************************************************
 结构名    : ETC_ERABM_REL_IND_STRU
 结构说明  : ETC_ERABM_REL_IND_STRU数据结构
*****************************************************************************/
typedef ETC_ERABM_REL_REQ_STRU ETC_ERABM_REL_IND_STRU;

/*****************************************************************************
 结构名称: ETC_ERABM_SUSPEND_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:RABM->TC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} ETC_ERABM_SUSPEND_IND_STRU;

/*****************************************************************************
 结构名称: ETC_ERABM_SUSPEND_RSP_STRU
 协议表格:
 ASN.1 描述:
 结构说明:TC->RABM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt;
} ETC_ERABM_SUSPEND_RSP_STRU;

/*****************************************************************************
 结构名称: ETC_ERABM_RESUME_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:RABM->TC
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} ETC_ERABM_RESUME_IND_STRU;


/*****************************************************************************
 结构名称: ETC_ERABM_RESUME_RSP_STRU
 协议表格:
 ASN.1 描述:
 结构说明:TC->RABM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt;
} ETC_ERABM_RESUME_RSP_STRU;


typedef struct
{
    ETC_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export ETC_ERABM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          ETC_ERABM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}ETC_ERABM_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    ETC_ERABM_MSG_DATA                    stMsgData;
}TcRabmInterface_MSG;

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

#endif /* end of TcRabmInterface.h */
