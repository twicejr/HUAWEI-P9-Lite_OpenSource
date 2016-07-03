
#ifndef  MSG_IMSA_INTERFACE_H
#define  MSG_IMSA_INTERFACE_H

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafClientApi.h"
#include "NasSms.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 枚举定义
*****************************************************************************/


enum MSG_IMSA_MSG_TYPE_ENUM
{
    ID_MSG_IMSA_RP_DATA_REQ   =TAF_MSG_IMSA_MSG_BASE,       /* _H2ASN_MsgChoice MSG_IMSA_RP_DATA_REQ_STRU */
    ID_MSG_IMSA_REPORT_REQ,                                 /* _H2ASN_MsgChoice MSG_IMSA_REPORT_REQ_STRU */
    ID_MSG_IMSA_SMMA_REQ,                                   /* _H2ASN_MsgChoice MSG_IMSA_SMMA_REQ_STRU */

    ID_IMSA_MSG_DATA_IND      =TAF_MSG_IMSA_MSG_BASE+0x100,  /* _H2ASN_MsgChoice IMSA_MSG_DATA_IND_STRU */
    ID_IMSA_MSG_REPORT_IND,                                 /* _H2ASN_MsgChoice IMSA_MSG_REPORT_IND_STRU */
    ID_IMSA_MSG_MT_ERR_IND,                                 /* _H2ASN_MsgChoice IMSA_MSG_MT_ERR_IND_STRU */

    ID_IMSA_MSG_TYPE_BUTT
};
typedef  VOS_UINT32  MSG_IMSA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  3 类型定义
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

typedef SMT_SMR_DATA_STRU MSG_IMSA_RP_DATA_REQ_STRU;


typedef SMT_SMR_DATA_STRU MSG_IMSA_REPORT_REQ_STRU;


typedef SMT_SMR_SMMA_STRU MSG_IMSA_SMMA_REQ_STRU;


typedef SMR_SMT_EST_IND_STRU IMSA_MSG_DATA_IND_STRU;


typedef SMR_SMT_MO_REPORT_STRU IMSA_MSG_REPORT_IND_STRU;


typedef SMR_SMT_MT_ERR_STRU IMSA_MSG_MT_ERR_IND_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    MSG_IMSA_MSG_TYPE_ENUM_UINT32       enMsgId;
    
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MSG_IMSA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}MSG_IMSA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MSG_IMSA_MSG_DATA                   stMsgData;
}MsgImsaInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MSG_IMSA_INTERFACE_H */
