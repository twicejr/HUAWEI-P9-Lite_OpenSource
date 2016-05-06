

#ifndef __OMESMINTERFACE_H__
#define __OMESMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "LPSCommon.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
/*OM->ESM Command消息前3个字节宏定义 OM->ESM*/
#define OM_ESM_MSG_ID_HEADER                               PS_MSG_ID_OM_TO_ESM_BASE

/*ESM->OM Command消息前3个字节宏定义 ESM->OM*/
#define ESM_OM_MSG_ID_HEADER                               PS_MSG_ID_ESM_TO_OM_BASE


#define OM_ESM_REPORT_INFO_OPEN                       1
#define OM_ESM_REPORT_INFO_CLOSE                      0

#define OM_MAX_IPV4_ADDR_LEN                               4
#define OM_MAX_IPV6_ADDR_LEN                               16

#define OM_MAX_APN_LEN                                     99

#define OM_ESM_MAX_EPSB_NUM                                (11)                /*最大承载数*/




/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : OM_ESM_MSG_TYPE_ENUM
 枚举说明  : OM与SM消息取值
*****************************************************************************/
enum OM_ESM_MSG_TYPE_ENUM
{
    ID_OM_ESM_INFO_REPORT_REQ              = 0x01+OM_ESM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  OM_ESM_INFO_REPORT_REQ_STRU*/
    ID_OM_ESM_INFO_REPORT_CNF              = 0x01+ESM_OM_MSG_ID_HEADER,/*_H2ASN_MsgChoice  OM_ESM_INFO_REPORT_CNF_STRU*/


    ID_OM_ESM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 OM_ESM_MSG_TYPE_ENUM_UINT32;



/*****************************************************************************
 枚举名    : OM_ESM_INFO_REPORT_ENUM
 枚举说明  : ESM上报协议状态的开关状态
*****************************************************************************/
enum OM_ESM_INFO_REPORT_ENUM
{
    OM_ESM_INFO_REPORT_CLOSE,        /* 不需要上报 */
    OM_ESM_INFO_REPORT_OPEN,         /* 需要上报 */
    OM_ESM_INFO_REPORT_BUTT
};
typedef VOS_UINT32 OM_ESM_INFO_REPORT_UINT32;

/*****************************************************************************
 枚举名    : OM_ESM_BEARER_STATE_ENUM
 枚举说明  : 承载状态取值
*****************************************************************************/
enum ESM_BEARER_CONTEXT_STATE_ENUM
{
    BEARER_CONTEXT_INACTIVE       = 0x00,
    BEARER_CONTEXT_ACTIVE      = 0x01,
    BEARER_CONTEXT_BUTT
};
typedef VOS_UINT32 ESM_BEARER_CONTEXT_STATE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : OM_ESM_BEARER_TYPE_ENUM
 枚举说明  : 承载类型取值
*****************************************************************************/
enum ESM_BEARER_TYPE_ENUM
{
    BEARER_TYPE_DEFAULT         = 0x00,
    BEARER_TYPE_DEDICATED       = 0x01,
    BEARER_TYPE_EMERGENCY       = 0x02,
    BEARER_TYPE_BUTT
};
typedef VOS_UINT32 ESM_BEARER_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : OM_ESM_APN_INFO_STRU
 结构说明  : APN  参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           aucApnName[OM_MAX_APN_LEN];
}OM_ESM_APN_INFO_STRU;

/*****************************************************************************
 结构名    : OM_ESM_EPS_QOS_INFO_STRU
 结构说明  : EPS_QOS  参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucQCI;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulULMaxRate;    /* 单位为kbps */
    VOS_UINT32                          ulDLMaxRate;    /* 单位为kbps */
    VOS_UINT32                          ulULGMaxRate;   /* 单位为kbps */
    VOS_UINT32                          ulDLGMaxRate;   /* 单位为kbps */
}OM_ESM_EPS_QOS_INFO_STRU;

/*****************************************************************************
 结构名    : OM_ESM_CONTEXT_APN_AMBR_STRU
 结构说明  : APN AMBR 参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulDLApnAmbr;
    VOS_UINT32                           ulULApnAmbr;

}OM_ESM_CONTEXT_APN_AMBR_STRU;

/*****************************************************************************
 结构名    : OM_ESM_IP_ADDR_STRU
 结构说明  : IP地址的结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[OM_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[OM_MAX_IPV6_ADDR_LEN];
}OM_ESM_IP_ADDR_STRU;


/*****************************************************************************
 结构名    : OM_ESM_STATE_INFO_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulCid;
    ESM_BEARER_CONTEXT_STATE_ENUM_UINT32     enBearerCntxtState;
    ESM_BEARER_TYPE_ENUM_UINT32         enBearerCntxtType;
    VOS_UINT32                          ulLinkBearId;
    OM_ESM_APN_INFO_STRU                stApn;
    OM_ESM_CONTEXT_APN_AMBR_STRU        stApnAmbrInfo;
    OM_ESM_EPS_QOS_INFO_STRU            stSdfQosInfo;
    OM_ESM_IP_ADDR_STRU                 stIpAddr;
} OM_ESM_STATE_INFO_STRU;

/* 用于HSO SG窗口显示 */
typedef struct
{
    OM_ESM_STATE_INFO_STRU              stEsmInfo[OM_ESM_MAX_EPSB_NUM];//最大承载数
} DIAG_ESM_INFO_IND_STRU;



/* 用于HSO SG窗口显示 */

/*****************************************************************************
 结构名    :  OM_ESM_INFO_REPORT_REQ_STRU
 结构说明  : ID_ OM_ESM_INFO_REPORT_REQ 消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER

    VOS_UINT32                          ulOpId;
    OM_ESM_INFO_REPORT_UINT32          enRptCtrl;
} OM_ESM_INFO_REPORT_REQ_STRU;
/*****************************************************************************
 结构名    :  APP_ESM_INFO_REPORT_CNF_STRU
 结构说明  : ID_ APP_ESM_INFO_REPORT_CNF 消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;    /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulRslt;
} OM_ESM_INFO_REPORT_CNF_STRU;



typedef struct
{
    OM_ESM_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export OM_ESM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          OM_ESM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}OM_ESM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    OM_ESM_INTERFACE_MSG_DATA           stMsgData;
} OMEsmInterface_MSG;






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

#endif /* end of AppEsmInterface.h */

