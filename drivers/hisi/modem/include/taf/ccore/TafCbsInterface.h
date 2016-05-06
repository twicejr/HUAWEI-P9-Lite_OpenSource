/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafCbsInterface.h
  版 本 号   : 初稿
  作    者   : 查鸣峰
  生成日期   : 2007年4月3日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2007年4月3日
    作    者   : 查鸣峰
    修改内容   : 创建文件

  2.日    期   : 2012年3月1日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR 命名调整将NAS调整为TAF 

******************************************************************************/

#ifndef __TAFCBSINTERFACE_H__
#define __TAFCBSINTERFACE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define  CBS_MAX_MSG_LEN                (1246)
#define  CBS_MIN_MSG_LEN                (1)
#define  CBS_MAX_MSG_ID_NUM             (100)

#define  GAS_CBS_MAX_CBPAGE_LEN         (88)                                    /*广播短消息一页的最大长度*/

#define  CBS_MSGID_RANGE_MAX            (20)                                    /*激活消息类型列表分段容量*/

#define  RR_CBS_ETWS_SECURITY_INFO_LEN  (50) 

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名: TAF_CBS_MSG_TYPE_ENUM
 协议格式:
 ASN.1描述:
 枚举说明: CBS模块和接入层之间的消息ID
*****************************************************************************/
enum TAF_CBS_MSG_TYPE_ENUM
{
    ID_BMC_CBS_DATA_IND                 =  0x0001,                              /* _H2ASN_MsgChoice BMC_CBS_DATA_IND_STRU */
    ID_GAS_CBS_DATA_IND                 =  0x0003,                              /* _H2ASN_MsgChoice GAS_CBS_DATA_IND_STRU */
    ID_BMC_CBS_CFG_CNF                  =  0x0005,                              /* _H2ASN_MsgChoice BMC_CBS_CFG_CNF_STRU */
    ID_GAS_CBS_CFG_CNF                  =  0x0007,                              /* _H2ASN_MsgChoice GAS_CBS_CFG_CNF_STRU */
    ID_RR_CBS_ETWS_PRIMARY_NOTIFY_IND   =  0x0009,                              /* _H2ASN_MsgChoice RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU */
    ID_LRRC_CBS_DATA_IND                =  0x000B,                              /* _H2ASN_MsgChoice LRRC_CBS_DATA_IND_STRU */
    ID_RR_CBS_GS_STATUS_CHANGE_IND      =  0x000D,                              /* _H2ASN_MsgChoice RR_CBS_GS_STATUS_CHANGE_IND_STRU */
    ID_CBS_BMC_CFG_REQ                  =  0x0002,                              /* _H2ASN_MsgChoice CBS_BMC_CFG_REQ_STRU */
    ID_CBS_GAS_CFG_REQ                  =  0x0004,                              /* _H2ASN_MsgChoice CBS_GAS_CFG_REQ_STRU */
    ID_TAF_CBS_MSG_TYPE_BUTT            =  0xFFFF
};
typedef VOS_UINT16 TAF_CBS_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名: TAF_CBS_CFG_RSLT_ENUM
 协议格式:
 ASN.1描述:
 枚举说明: 激活接入层的CBS功能的结果
*****************************************************************************/
enum TAF_CBS_CFG_RSLT_ENUM
{
    TAF_CBS_CFG_RSLT_SUCC               = 0,
    TAF_CBS_CFG_RSLT_FAIL,
    TAF_CBS_CFG_RSLT_BUTT
};
typedef VOS_UINT32   TAF_CBS_CFG_RSLT_ENUM_UINT32;

/*****************************************************************************
 枚举名: TAF_CBS_GS_CHG_TYPE_ENUM
 协议格式:
 ASN.1描述:
 枚举说明: 地理区域变更类型
*****************************************************************************/
enum TAF_CBS_GS_CHG_TYPE_ENUM
{
    TAF_CBS_GS_CHG_TYPE_CHG_PLMN        = 0,                                    /* UE的PLMN改变*/
    TAF_CBS_GS_CHG_TYPE_CHG_SA          = 1,                                    /* UE的服务区改变*/
    TAF_CBS_GS_CHG_TYPE_CHG_CELL        = 2,                                    /* UE的小区变更*/
    TAF_CBS_GS_CHG_TYPE_CHG_RAT         = 3,                                    /* UE的系统变更(双模切换)*/
    TAF_CBS_GS_CHG_TYPE_NO_CHG          = 4,                                    /* UE的小区状态未改变*/
    TAF_CBS_GS_CHG_TYPE_CHG_BUTT
};
typedef  VOS_UINT8 TAF_CBS_GS_CHG_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名: TAF_CBS_CFG_ENUM
 协议格式:
 ASN.1描述:
 枚举说明: 配置接入层的CBS功能激活/去激活
*****************************************************************************/
enum TAF_CBS_CFG_ENUM
{
    TAF_CBS_CFG_ACTIVE                  = 0,
    TAF_CBS_CFG_DEACTIVE,
    TAF_CBS_CFG_BUTT
};
typedef  VOS_UINT32   TAF_CBS_CFG_ENUM_UINT32;



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
 结构名称: TAF_CBS_PLMN_ID_STRU
 协议表格:
 ASN.1 描述:
 结构说明: PLMN ID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}TAF_CBS_PLMN_ID_STRU;

/*****************************************************************************
 结构名称: TAF_CBS_NETWORK_INFO_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 当前驻留的网络信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPlmnId     : 1;
    VOS_UINT32                          bitOpSa         : 1;
    VOS_UINT32                          bitOpCellId     : 1;
    VOS_UINT32                          bitSpare        : 29;

    TAF_CBS_PLMN_ID_STRU                stCurPlmn;                              /* 当前 Plmn */
    VOS_UINT16                          usSa;                                   /* 当前服务区信息  */
    VOS_UINT8                           aucRsv[2];                              /* 字节对齐保留 */
    VOS_UINT32                          ulCellId;                               /* 当前小区ID  */
}TAF_CBS_NETWORK_INFO_STRU;

/*****************************************************************************
 结构名称: BMC_CBS_DATA_IND_STRU,LRRC_CBS_DATA_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: W模CBS消息/ETWS消息内容, L模ETWS消息内容
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* 子进程标识,用于定位子进程，保留*/

    TAF_CBS_NETWORK_INFO_STRU           stCurrNetworkInfo;                      /* 当前网络信息 */

    VOS_UINT16                          usCBMID;                                /* CBS消息ID */

    /*aabbbbbb bbbbcccc, indicate Serial Number
    aa          GS
    bbbbbb      Message Code
    cccc        Update Number
    */
    VOS_UINT16                          usSerialNum;                            /* CBS消息序列号 */

    /*aaaa bbbb,indicate Data-Coding-Scheme
    aaaa        Coding Group Bits
    bbbb        Use of bits 3..0
    */
    VOS_UINT8                           ucDataCodeScheme;                       /* 数据编码方式 */
    VOS_UINT8                           aucRsv[1];

    VOS_UINT16                          usCBDataLen;                            /* [CBS_MIN_MSG_LEN,CBS_MAX_MSG_LEN],CBS消息长度,单位：字节*/
    VOS_UINT8                           aucCBData[4];                           /* CBS消息体，REF:3GPP TS 23.041: CHAPTER 9.4.2.2.5 CBS Data*/
}BMC_CBS_DATA_IND_STRU,LRRC_CBS_DATA_IND_STRU;

/*****************************************************************************
 结构名称: GAS_CBS_PAGE_DATA_STRU
 协议表格:
 ASN.1 描述:
 结构说明: G模CBS消息页内容
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLength;
    VOS_UINT8                           aucData[GAS_CBS_MAX_CBPAGE_LEN];
}GAS_CBS_PAGE_DATA_STRU;

/*****************************************************************************
 结构名称: GAS_CBS_DATA_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: G模CBS消息内容
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* 子进程标识,用于定位子进程，保留*/

    TAF_CBS_NETWORK_INFO_STRU           stCurrNetworkInfo;                      /* 当前网络信息 */

    VOS_UINT8                           ucPageNum;                              /* 当前CBS消息包含消息页总数*/
    VOS_UINT8                           aucRsv[3];

    GAS_CBS_PAGE_DATA_STRU              astPageData[1];                         /* 当前CBS消息页内容列表, Refer to 23041 9.4.1.2 Message Parameter*/
}GAS_CBS_DATA_IND_STRU;

/*****************************************************************************
 结构名称: CBS_MSGID_RANGE_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /* Cell broadcast message id value range from  */
    VOS_UINT16                          usMsgIdTo;                              /* Cell broadcast message id value range to    */
}CBS_MSGID_RANGE_STRU;

/*****************************************************************************
 结构名称: CBS_BMC_CFG_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 通知接入层CBS功能激活/去激活
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* 子进程标识,用于定位子进程，保留 */

    TAF_CBS_CFG_ENUM_UINT32             enCbsActive;                            /* CBS激活开关 */
}CBS_BMC_CFG_REQ_STRU;

typedef CBS_BMC_CFG_REQ_STRU CBS_GAS_CFG_REQ_STRU;

/*****************************************************************************
 结构名称: BMC_CBS_CFG_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 激活/去激活CBS功能的结果
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* 子进程标识,用于定位子进程，保留 */

    TAF_CBS_CFG_RSLT_ENUM_UINT32        enRslt;                                 /* 上层 原语证实结果 */
}BMC_CBS_CFG_CNF_STRU;

typedef BMC_CBS_CFG_CNF_STRU GAS_CBS_CFG_CNF_STRU;


/*****************************************************************************
 结构名    :    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :    上报主通知
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* 子进程标识,用于定位子进程，保留 */

    TAF_CBS_NETWORK_INFO_STRU           stCurrNetworkInfo;                      /* 当前网络信息 */

    VOS_UINT16                          usWarnType;                             /* 告警类型 */
    VOS_UINT16                          usMessageId;                            /* 消息ID */
    VOS_UINT16                          usSerialNumber;                         /* 序列号 */
    
    VOS_UINT8                           ucSecurityInfoPresent;                  /* 安全信息是否存在, VOS_TRUE:存在, VOS_FALSE:不存在 */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucSecurityInfo[RR_CBS_ETWS_SECURITY_INFO_LEN];
}RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU;

/*****************************************************************************
 结构名称: RR_CBS_GS_STATUS_CHANGE_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: 地理位置变更信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usTransId;                              /* 子进程标识,用于定位子进程，保留 */
    
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enGsChgType;                            /* 地理区域变更类型 */
    VOS_UINT8                           aucRsv[3];                              /* 字节对齐保留 */

    TAF_CBS_NETWORK_INFO_STRU           stCurrNetworkInfo;                      /* 当前网络信息 */
}RR_CBS_GS_STATUS_CHANGE_IND_STRU;


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
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    TAF_CBS_MSG_TYPE_ENUM_UINT16        enMsgID;                                /*_H2ASN_MsgChoice_Export TAF_CBS_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsg[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_CBS_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}TAF_CBS_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_CBS_MSG_DATA                    stMsgData;
} TafCbsInterface_MSG;

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

#endif /* end of TafCbsInterface.h */
