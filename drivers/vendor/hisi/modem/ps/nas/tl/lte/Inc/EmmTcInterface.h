

#ifndef __EMMTCINTERFACE_H__
#define __EMMTCINTERFACE_H__

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
/*EMM->TC Command消息前3个字节宏定义 EMM->TC*/
#define EMM_ETC_MSG_ID_HEADER            PS_MSG_ID_EMM_TO_TC_BASE

/*TC ->EMM Command消息前3个字节宏定义 TC->EMM*/
#define ETC_EMM_MSG_ID_HEADER            PS_MSG_ID_TC_TO_EMM_BASE



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : EMM_ETC_MSG_TYPE_ENUM
 枚举说明  : EMM与TC消息类型
*****************************************************************************/
enum EMM_ETC_MSG_TYPE_ENUM
{
    /*消息原语*/
    /*TC发送给EMM的消息原语*/
    ID_EMM_ETC_DATA_REQ                  = (0x01+ETC_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ETC_DATA_REQ_STRU */
    ID_EMM_ETC_REL_REQ                   = (0x02+ETC_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ETC_REL_REQ_STRU */

    /*EMM发送给TC的消息原语*/
    ID_EMM_ETC_DATA_IND                  = (0x01+EMM_ETC_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ETC_DATA_IND_STRU */
    ID_EMM_ETC_REL_IND                   = (0x02+EMM_ETC_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ETC_REL_IND_STRU */

    ID_EMM_ETC_BUTT
};
typedef VOS_UINT32 EMM_ETC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : EMM_ETC_MSG_STRU
 结构说明  : EMM_ETC_MSG_STRU空口消息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulTcMsgSize;
    VOS_UINT8                          aucTcMsg[4];       /* 消息的前四个字节内容             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}EMM_ETC_MSG_STRU;

/*****************************************************************************
 结构名    : EMM_ETC_DATA_REQ_STRU
 结构说明  : EMM_ETC_DATA_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    EMM_ETC_MSG_STRU                     stTcMsg;            /* TC MSG :TC模块向SAE携带参数消息*/
}EMM_ETC_DATA_REQ_STRU;

typedef EMM_ETC_DATA_REQ_STRU EMM_ETC_DATA_IND_STRU;

/*****************************************************************************
 结构名    : EMM_ETC_REL_REQ_STRU
 结构说明  : EMM_ETC_REL_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/            /* 消息头*/
    VOS_UINT32                           ulReserved;         /* 保留字*/
}EMM_ETC_REL_REQ_STRU;

/*****************************************************************************
 结构名    : EMM_ETC_REL_IND_STRU
 结构说明  : EMM_ETC_REL_IND_STRU数据结构
*****************************************************************************/
typedef EMM_ETC_REL_REQ_STRU EMM_ETC_REL_IND_STRU;

typedef struct
{
    EMM_ETC_MSG_TYPE_ENUM_UINT32         enMsgID;            /*_H2ASN_MsgChoice_Export EMM_ETC_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          EMM_ETC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}EMM_ETC_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    EMM_ETC_MSG_DATA                     stMsgData;
}EmmTcInterface_MSG;

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

#endif /* end of EmmTcInterface.h */
