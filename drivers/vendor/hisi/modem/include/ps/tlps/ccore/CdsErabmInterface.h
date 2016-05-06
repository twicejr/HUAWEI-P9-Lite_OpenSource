/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsErabmInterface.h
  版 本 号   : 初稿
  作    者   : lihong 00150010
  生成日期   : 2011-12-05
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2011-12-05
    作    者   : lihong 00150010
    修改内容   : 创建文件

******************************************************************************/

#ifndef _CDS_ERABM_INTERFACE_H_
#define _CDS_ERABM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "TTFMemInterface.h"
#include "CdsRabmInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/



/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 结构名称   : CDS_ERABM_MSG_ID_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : CDS和ERABM之间的原语
*****************************************************************************/
enum CDS_ERABM_MSG_ID_ENUM
{
    /* CDS->ERABM的消息原语 */
    ID_CDS_ERABM_SERVICE_NOTIFY         = (0x01+PS_MSG_ID_CDS_TO_ERABM_BASE),   /* _H2ASN_MsgChoice CDS_ERABM_SERVICE_NOTIFY_STRU */

    /* ERABM->CDS的消息原语 */
    ID_ERABM_CDS_SEND_BUFF_DATA_IND     = (0x01+PS_MSG_ID_ERABM_TO_CDS_BASE),   /* _H2ASN_MsgChoice ERABM_CDS_SEND_BUFF_DATA_IND_STRU */
    ID_ERABM_CDS_FREE_BUFF_DATA_IND     = (0x02+PS_MSG_ID_ERABM_TO_CDS_BASE),   /* _H2ASN_MsgChoice ERABM_CDS_FREE_BUFF_DATA_IND_STRU */

    ID_QOS_FC_ERABM_RAB_CREATE_IND      = (0x03+PS_MSG_ID_ERABM_TO_CDS_BASE),     /* _H2ASN_MsgChoice CDS_ERABM_RAB_CREATE_IND_STRU */
    ID_QOS_FC_ERABM_RAB_RELEASE_IND     = (0x04+PS_MSG_ID_ERABM_TO_CDS_BASE),     /* _H2ASN_MsgChoice CDS_ERABM_RAB_RELEASE_IND_STRU */

    ID_CDS_ERABM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 CDS_ERABM_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 结构名称   : CDS_ERABM_TRANSFER_RESULT_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : 获取DRB结果枚举
*****************************************************************************/
enum CDS_ERABM_TRANSFER_RESULT_ENUM
{
    CDS_ERABM_TRANSFER_RESULT_SUCC       	= 0x00,
    CDS_ERABM_TRANSFER_RESULT_FAIL          = 0x01,
    CDS_ERABM_TRANSFER_RESULT_IDLE          = 0x02,
    CDS_ERABM_TRANSFER_RESULT_DRB_SUSPEND   = 0x03,
    CDS_ERABM_TRANSFER_RESULT_DRB_NOT_EXIST = 0x04,
    CDS_ERABM_TRANSFER_RESULT_BUTT
};
typedef VOS_UINT32 CDS_ERABM_TRANSFER_RESULT_ENUM_UINT32;

/*****************************************************************************
 结构名称   : CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : 触发CDS处理缓存数据的枚举类型
*****************************************************************************/
enum CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM
{
    CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC    = 0,
    CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_DRB_CONN        = 1,
    CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_BUTT
};
typedef VOS_UINT32 CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32;



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
 结构名称: CDS_ERABM_SERVICE_NOTIFY_STRU
 协议表格:
 ASN.1 描述:
 结构说明: CDS请求ERABM建链消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                    /*_H2ASN_Skip*/
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucReserved[3];
} CDS_ERABM_SERVICE_NOTIFY_STRU;

/*****************************************************************************
 结构名称: ERABM_CDS_SEND_BUFF_DATA_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: ERABM通知CDS处理缓存数据消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                                          ulMsgId;    /*_H2ASN_Skip*/

    CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32   enSndBuffDataAllowedType;
} ERABM_CDS_SEND_BUFF_DATA_IND_STRU;

/*****************************************************************************
 结构名称: ERABM_CDS_SEND_BUFF_DATA_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: ERABM通知CDS清除缓存数据消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                    /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];
} ERABM_CDS_FREE_BUFF_DATA_IND_STRU;

/*****************************************************************************
 结构名称: CDS_ERABM_RAB_CREATE_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: ERABM通知CDS建立EPSB承载结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    QCI_TYPE_ENUM_UINT8                 enQci;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucLinkRabId;
    VOS_UINT8                           ucRev;
} CDS_ERABM_RAB_CREATE_IND_STRU;
/*****************************************************************************
 结构名称: CDS_ERABM_RAB_RELEASE_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: ERABM通知CDS释放EPSB承载结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           ucRev[3];
} CDS_ERABM_RAB_RELEASE_IND_STRU;

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
    CDS_ERABM_MSG_ID_ENUM_UINT32        ulMsgId;            /* _H2ASN_MsgChoice_Export CDS_ERABM_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CDS_ERABM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} CDS_ERABM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    CDS_ERABM_INTERFACE_MSG_DATA        stMsgData;
} CdsErabmInterface_MSG;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 CDS_ERABM_GetIpFragEpsbId
(
    VOS_UINT8                           *pucEpsbId,
    TTF_MEM_ST                          *pstIpFrag,
    VOS_UINT32                           ulIpFragLen
);

extern CDS_ERABM_TRANSFER_RESULT_ENUM_UINT32 CDS_ERABM_GetDrbId
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                          *pucDrbId
);

extern VOS_UINT32 CDS_ERABM_GetDefaultEpsbId
(
    VOS_UINT8                           ucDrbId,
    VOS_UINT8                          *pucDeftEpsbId
);

extern VOS_UINT32 CDS_ERABM_GetEpsbId
(
    VOS_UINT8                           ucDrbId,
    VOS_UINT8                          *pucEpsbId
);



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

#endif /* end of CdsErabmInterface.h */