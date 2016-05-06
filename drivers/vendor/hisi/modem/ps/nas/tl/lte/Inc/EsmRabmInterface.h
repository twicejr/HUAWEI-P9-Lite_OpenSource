

#ifndef __ESMRABMINTERFACE_H__
#define __ESMRABMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "AppEsmInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define ESM_ERABM_INVALID_BEARER_ID       0xFFFFFFFF   /* 非法承载ID */

#define ESM_ERABM_MAX_EPSB_NUM            11           /*最大承载数*/

#define ESM_ERABM_MAX_PF_NUM_IN_BEARER    16
#define ESM_ERABM_MAX_PF_NUM              32

/*ESM ->RABM Command消息前3个字节宏定义 SM->RABM*/
#define ESM_ERABM_MSG_ID_HEADER           PS_MSG_ID_ESM_TO_RABM_BASE

/*RABM->SM Command消息前3个字节宏定义 RABM->SM*/
#define ERABM_ESM_MSG_ID_HEADER           PS_MSG_ID_RABM_TO_ESM_BASE


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : ESM_ERABM_MSG_TYPE_ENUM
 枚举说明  : SM与RABM的消息类型
*****************************************************************************/
enum ESM_ERABM_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /*消息ID*/
    /* RABM发给SM的原语 */
    ID_ESM_ERABM_REL_REQ                 = (0x02+ERABM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_REL_REQ_STRU */
    ID_ESM_ERABM_BEARER_STATUS_REQ       = (0x04+ERABM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_BEARER_STATUS_REQ_STRU */

    /* SM发给RABM的原语 */
    ID_ESM_ERABM_ACT_IND                 = (0x01+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_ACT_IND_STRU */
    ID_ESM_ERABM_MDF_IND                 = (0x03+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_MDF_IND_STRU */
    ID_ESM_ERABM_DEACT_IND               = (0x05+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_DEACT_IND_STRU */
    ID_ESM_ERABM_REL_IND                 = (0x07+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_REL_IND_STRU */

    ID_ESM_ERABM_CLEAR_CL_BEARER_NOTIFY  = (0x09+ESM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice ESM_ERABM_CLEAR_CL_BEARER_NOTIFY_STRU */

    ID_ESM_ERABM_BUTT
};
typedef VOS_UINT32 ESM_ERABM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : ESM_ERABM_PDN_TYPE_ENUM
 枚举说明  : SM与RABM支持的PDN类型
*****************************************************************************/
enum ESM_ERABM_PDN_TYPE_ENUM
{

    ESM_ERABM_PDN_TYPE_IPV4              = (0x01),    /* 支持IPV4地址*/
    ESM_ERABM_PDN_TYPE_IPV6              = (0x02),    /* 支持IPV6地址*/
    ESM_ERABM_PDN_TYPE_IPV4_IPV6         = (0x03),    /* 支持IPV4和IPV6地址*/

    ESM_ERABM_PDN_TYPE_BUTT
};
typedef VOS_UINT8 ESM_ERABM_PDN_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : ESM_ERABM_BEARER_TYPE_ENUM
 枚举说明  : SM与RABM支持的承载类型
*****************************************************************************/
enum ESM_ERABM_BEARER_TYPE_ENUM
{
    ESM_ERABM_BEARER_TYPE_DEFAULT        = 0,                /*缺省承载*/
    ESM_ERABM_BEARER_TYPE_DEDICATED      ,                   /*专有承载*/
    ESM_ERABM_BEARER_TYPE_EMERGENCY      ,                   /*紧急承载*/

    ESM_ERABM_BEARER_TYPE_BUTT
};
typedef VOS_UINT32  ESM_ERABM_BEARER_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : ESM_ERABM_BEARER_RAT_ENUM
 枚举说明  : 承载对应的接入技术类型
*****************************************************************************/
enum ESM_ERABM_BEARER_RAT_ENUM
{
    ESM_ERABM_BEARER_RAT_LTE        = 0,                /* 接入技术为LTE，GUL情况下都用这个，CL的情况L主模激活也用这个 */
    ESM_ERABM_BEARER_RAT_EHRPD      = 1  ,              /* EHRPD，如果是CL多模的情况下，EHRPD同步过来的承载用这个      */

    ESM_ERABM_BEARER_RAT_BUTT
};
typedef VOS_UINT8  ESM_ERABM_BEARER_RAT_ENUM_UINT8;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : ESM_ERABM_TFT_PF_STRU
 结构说明  : ESM_ERABM_TFT_STRU数据结构
*****************************************************************************/
typedef APP_ESM_TFT_INFO_STRU ESM_ERABM_TFT_PF_STRU;

/*****************************************************************************
 结构名    : ESM_ERABM_QOS_STRU
 结构说明  : ESM_ERABM_QOS_STRU数据结构
*****************************************************************************/
typedef APP_ESM_QOS_INFO_STRU ESM_ERABM_QOS_STRU;


/*****************************************************************************
 结构名    : ESM_ERABM_REL_REQ_STRU
 结构说明  : ESM_ERABM_REL_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/   /* 消息头 */
    VOS_UINT32                          ulReserved;         /* 保留字 */
}ESM_ERABM_REL_REQ_STRU;

/*****************************************************************************
 结构名    : ESM_ERABM_REL_IND_STRU
 结构说明  : ESM_ERABM_REL_IND_STRU数据结构
*****************************************************************************/
typedef ESM_ERABM_REL_REQ_STRU ESM_ERABM_REL_IND_STRU;

/*****************************************************************************
 结构名    : ESM_ERABM_ACT_IND_STRU
 结构说明  : ESM_ERABM_ACT_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulEpsId;
    VOS_UINT32                          ulTftPfNum;
    ESM_ERABM_TFT_PF_STRU               astTftPf[ESM_ERABM_MAX_PF_NUM_IN_BEARER];
    APP_ESM_IP_ADDR_STRU                stPdnAddr;
    ESM_ERABM_BEARER_TYPE_ENUM_UINT32   enBearerCntxtType;  /* 上下文对应承载的类型 */
    VOS_UINT32                          ulLinkedEpsbId;     /*与此承载关联的EPS承载ID*/
    VOS_UINT8                           ucQCI;              /*承载QCI */
    VOS_UINT8                           ucSessionId;        /* 消息OPID匹配*/

    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat;   /* 承载的接入技术类型 */
    VOS_UINT8                           ucHandoverFlag;     /* CL恢复承载场景标识，VOS_TRUE是L下恢复EHRPD的承载激活，VOS_FALSE不是恢复承载的场景 */
    VOS_UINT32                          ulEhrpdBearerId;    /* EHRPD承载ID        */

} ESM_ERABM_ACT_IND_STRU;

/*****************************************************************************
 结构名    : ESM_ERABM_MDF_IND_STRU
 结构说明  : ESM_ERABM_MDF_IND_STRU数据结构
*****************************************************************************/
typedef ESM_ERABM_ACT_IND_STRU ESM_ERABM_MDF_IND_STRU;


/*****************************************************************************
 结构名    : ESM_ERABM_DEACT_IND_STRU
 结构说明  : ESM_ERABM_DEACT_IND_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    VOS_UINT32                          ulEpsIdNum;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat;   /* 承载的接入技术类型 */
    VOS_UINT8                           ucRsv[3];           /* 保留 */

} ESM_ERABM_DEACT_IND_STRU;

/*****************************************************************************
 结构名    : ESM_ERABM_CLEAR_CL_BEARER_NOTIFY_STRU
 结构说明  : ESM_ERABM_CLEAR_CL_BEARER_NOTIFY_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    VOS_UINT8                           ucRsv[4];       /* 保留 */

} ESM_ERABM_CLEAR_CL_BEARER_NOTIFY_STRU;

/*****************************************************************************
 结构名    : ESM_ERABM_BEARER_STATUS_REQ_STRU
 结构说明  : ESM_ERABM_BEARER_STATUS_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* 消息头 */
    VOS_UINT32                          ulEpsIdNum;         /* 当前对应rb已激活的EPSID个数 */
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];     /*存贮已激活rb的EPS BID  */
    VOS_UINT8                           ucSessionId;
    VOS_UINT8                           aucRsv[3];
} ESM_ERABM_BEARER_STATUS_REQ_STRU;

typedef struct
{
    ESM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export ESM_ERABM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                            aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          ESM_ERABM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}ESM_ERABM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    ESM_ERABM_INTERFACE_MSG_DATA         stMsgData;
}EsmRabmInterface_MSG;

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

#endif /* end of RabmEsmInterface.h */
