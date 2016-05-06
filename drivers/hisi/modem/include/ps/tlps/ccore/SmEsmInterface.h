/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SmEsmInterface.h
  版 本 号   : 初稿
  作    者   : lihong 00150010, anhuiqing 00165503
  生成日期   : 2011-04-02
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2011-04-02
    作    者   : lihong 00150010, anhuiqing 00165503
    修改内容   : 创建文件

******************************************************************************/

#ifndef _SM_ESM_INTERFACE_H_
#define _SM_ESM_INTERFACE_H_

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

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define SM_ESM_MAX_LENGTH_OF_APN            (100)
#define SM_ESM_MAX_TFT_PF_NUM               (16)

#define SM_ESM_IPV4_ADDR_LEN                (4)
#define SM_ESM_IPV6_ADDR_LEN                (16)



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 结构名称   : SM_ESM_MSG_ID_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : SM和ESM之间的原语
*****************************************************************************/
enum SM_ESM_MSG_ID_ENUM
{
    /* SM->ESM的消息原语 */
    ID_SM_ESM_PDP_CONTEXT_INFO_IND       = (0x01+PS_MSG_ID_SM_TO_ESM_BASE),     /* _H2ASN_MsgChoice SM_ESM_PDP_CONTEXT_INFO_IND_STRU */

    /* ESM->SM的消息原语 */
    ID_ESM_SM_EPS_BEARER_INFO_IND        = (0x01+PS_MSG_ID_ESM_TO_SM_BASE),     /* _H2ASN_MsgChoice SM_ESM_EPS_BEARER_INFO_IND_STRU */
    ID_ESM_APS_ESM_NOTIFICATION_IND      = (0x02+PS_MSG_ID_ESM_TO_SM_BASE),     /* _H2ASN_MsgChoice ESM_APS_NOTIFICATION_IND_STRU */

    ID_SM_ESM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 SM_ESM_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 结构名称   : SM_ESM_PDP_OPTION_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : PDP或EPS BEARER状态枚举
*****************************************************************************/
enum SM_ESM_PDP_OPTION_ENUM
{
    SM_ESM_PDP_OPT_ACTIVATE             = 0,
    SM_ESM_PDP_OPT_MODIFY                  ,
    SM_ESM_PDP_OPT_DEACTIVATE              ,

    SM_ESM_PDP_OPT_BUTT
};
typedef VOS_UINT32 SM_ESM_PDP_OPTION_ENUM_UINT32;

/*****************************************************************************
 结构名称   : SM_ESM_PDP_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : PDP地址类型枚举
*****************************************************************************/
enum SM_ESM_PDP_TYPE_ENUM
{
    SM_ESM_PDP_PPP                      = 0,
    SM_ESM_PDP_IPV4                        ,
    SM_ESM_PDP_IPV6                        ,
    SM_ESM_PDP_IPV4V6                      ,

    SM_ESM_PDP_TYPE_BUTT
};
typedef VOS_UINT8 SM_ESM_PDP_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名称   : SM_ESM_TRANSFER_DIRECTION_ENUM_UINT8
 协议表格   :
 ASN.1 描述 :
 结构说明   : PACKET FILTER方向枚举
*****************************************************************************/
enum SM_ESM_TRANSFER_DIRECTION_ENUM
{
    SM_ESM_TRANSFER_DIRECTION_PRE_REL7_TFT_FILTER           = 0x00,
    SM_ESM_TRANSFER_DIRECTION_DOWNLINK                      = 0x01,
    SM_ESM_TRANSFER_DIRECTION_UPLINK                        = 0x02,
    SM_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK               = 0x03,

    SM_ESM_TRANSFER_DIRECTION_BUTT
};
typedef VOS_UINT8 SM_ESM_TRANSFER_DIRECTION_ENUM_UINT8;

/*****************************************************************************
 结构名称   : SM_ESM_BCM_ENUM_UINT8
 协议表格   :
 ASN.1 描述 :
 结构说明   : BEARER CONTROL MODE枚举
*****************************************************************************/
enum SM_ESM_BCM_ENUM
{
    SM_ESM_BCM_MS_ONLY                  = 0x01,
    SM_ESM_BCM_MS_NW                    = 0x02,

    SM_ESM_BCM_BUTT
};
typedef VOS_UINT8 SM_ESM_BCM_ENUM_UINT8;

/*****************************************************************************
 枚举名称: SM_ESM_PDP_EMC_IND_ENUM
 枚举说明: PDP上下文是否紧急类型
*****************************************************************************/
enum SM_ESM_PDP_EMC_IND_ENUM
{
    SM_ESM_PDP_NOT_FOR_EMC                 = 0x00,
    SM_ESM_PDP_FOR_EMC                     = 0x01,

    SM_ESM_PDP_EMC_IND_BUTT                = 0xFF
};
typedef VOS_UINT8 SM_ESM_PDP_EMC_IND_ENUM_UINT8;

/*****************************************************************************
 枚举名  : SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM
 枚举说明:
*****************************************************************************/
enum SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM
{
    SM_ESM_PDP_NOT_FOR_IMS_CN_SIG_ONLY     = 0x00,
    SM_ESM_PDP_FOR_IM_CN_SIG_ONLY          = 0x01,

    SM_ESM_PDP_IM_CN_SIG_FLAG_BUTT         = 0xFF
};
typedef VOS_UINT8 SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM_UINT8;


/*sunbing 49683 2013-10-14 VoLTE begin*/
enum ESM_APS_NOTIFICATION_IND_ENUM
{
    ESM_APS_NOTIFICATION_IND_SRVCC_HO_CANCELLED         = 0,

    ESM_APS_NOTIFICATION_IND_BUTT
};
typedef VOS_UINT32 ESM_APS_NOTIFICATION_IND_ENUM_UINT32;
/*sunbing 49683 2013-10-14 VoLTE end*/

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
 结构名称   : SM_ESM_APN_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 详见TS 24.008 section 10.5.6.1 APN为码流字节(未译码)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;           /* APN长度    */
    VOS_UINT8                           aucReserved[3];     /* 四字节对齐 */
    VOS_UINT8                           aucValue[SM_ESM_MAX_LENGTH_OF_APN];

} SM_ESM_APN_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_PDP_ADDR_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 详见TS 24.008 section 10.5.6.4 PDP address
              aucIpV4Addr[0]为地址高字节位，aucIpV4Addr[3]为地址低字节位
              aucIpV6Addr[0]为地址高字节位，aucIpV6Addr[15]为地址低字节位
*****************************************************************************/
typedef struct
{
    SM_ESM_PDP_TYPE_ENUM_UINT8          enPdpType;          /* PDP地址类型 */
    VOS_UINT8                           aucReserved[3];     /* 四字节对齐  */
    VOS_UINT8                           aucIpV4Addr[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[SM_ESM_IPV6_ADDR_LEN];

} SM_ESM_PDP_ADDR_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_PDN_ADDR_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 详见TS 24.301 section 9.9.4.9 PDN address
              aucIpV4Addr[0]为地址高字节位，aucIpV4Addr[3]为地址低字节位
              aucIpV6Addr[0]为地址高字节位，aucIpV6Addr[15]为地址低字节位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;           /* PDN地址类型 */
    VOS_UINT8                           aucReserved[3];     /* 四字节对齐  */
    VOS_UINT8                           aucIpV4Addr[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[SM_ESM_IPV6_ADDR_LEN ];

} SM_ESM_PDN_ADDR_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_PCO_IPV4_ITEM_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : aucPriDns   - Primary DNS server Address
              aucSecDns   - Secondary DNS server Address
              aucGateWay  - Peer IP address
              aucPriNbns  - Primary WINS DNS address
              aucSecNbns  - Seocndary WINS DNS address
              aucPriPcscf - Primary P-CSCF address
              aucSecPcscf - Seocndary P-CSCF address

              aucGateWay[0]为地址高字节位，aucGateWay[3]为地址低字节位
              aucPriNbns[0]为地址高字节位，aucPriNbns[3]为地址低字节位
              aucSecNbns[0]为地址高字节位，aucSecNbns[3]为地址低字节位
              aucPriPcscf[0]为地址高字节位，aucPriPcscf[3]为地址低字节位
              aucSecPcscf[0]为地址高字节位，aucSecPcscf[3]为地址低字节位
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpGateWay    : 1;
    VOS_UINT32                          bitOpPriNbns    : 1;
    VOS_UINT32                          bitOpSecNbns    : 1;
    VOS_UINT32                          bitOpPriPcscf   : 1;
    VOS_UINT32                          bitOpSecPcscf   : 1;
    VOS_UINT32                          bitOpThiPcscf   : 1;
    VOS_UINT32                          bitOpSpare      : 24;

    VOS_UINT8                           aucPriDns[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucGateWay[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPriNbns[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbns[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPriPcscf[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscf[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucThiPcscf[SM_ESM_IPV4_ADDR_LEN];

} SM_ESM_PCO_IPV4_ITEM_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_PCO_IPV6_ITEM_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : aucPriDns   - Primary DNS server Address
              aucSecDns   - Secondary DNS server Address
              aucPriPcscf - Primary P-CSCF address
              aucSecPcscf - Seocndary P-CSCF address

              aucPriDns[0]为地址高字节位，aucPriDns[15]为地址低字节位
              aucSecDns[0]为地址高字节位，aucSecDns[15]为地址低字节位
              aucPriPcscf[0]为地址高字节位，aucPriPcscf[15]为地址低字节位
              aucSecPcscf[0]为地址高字节位，aucSecPcscf[15]为地址低字节位
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpPriPcscf   : 1;
    VOS_UINT32                          bitOpSecPcscf   : 1;
    VOS_UINT32                          bitOpThiPcscf   : 1;
    VOS_UINT32                          bitOpSpare      : 27;

    VOS_UINT8                           aucPriDns[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDns[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           aucPriPcscf[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscf[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           aucThiPcscf[SM_ESM_IPV6_ADDR_LEN];

} SM_ESM_PCO_IPV6_ITEM_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_PDP_QOS_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 详见TS 24.008 section 10.5.6.5 Quality of service
              GU NAS提供的是QOS各个参数的值，未译码
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDelayClass;
    VOS_UINT8                           ucReliabClass;
    VOS_UINT8                           ucPeakThrough;
    VOS_UINT8                           ucPrecedenceClass;
    VOS_UINT8                           ucMeanThrough;
    VOS_UINT8                           ucTrafficClass;
    VOS_UINT8                           ucDeliverOrder;
    VOS_UINT8                           ucDeliverOfErrSdu;
    VOS_UINT8                           ucMaximSduSize;
    VOS_UINT8                           ucMaxBitRateForUp;
    VOS_UINT8                           ucMaxBitRateForDown;
    VOS_UINT8                           ucResidualBer;
    VOS_UINT8                           ucSduErrRatio;
    VOS_UINT8                           ucTransDelay;
    VOS_UINT8                           ucTraffHandlPrior;
    VOS_UINT8                           ucGuarantBitRateForUp;
    VOS_UINT8                           ucGuarantBitRateForDown;
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;
    VOS_UINT8                           ucMaxBitRateForDownExt;
    VOS_UINT8                           ucGuarantBitRateForDownExt;
    VOS_UINT8                           ucMaxBitRateForUpExt;
    VOS_UINT8                           ucGuarantBitRateForUpExt;
    VOS_UINT8                           ucMaxBitRateForDownExt_2;
    VOS_UINT8                           ucGuarantBitRateForDownExt_2;
    VOS_UINT8                           ucMaxBitRateForUpExt_2;
    VOS_UINT8                           ucGuarantBitRateForUpExt_2;

    VOS_UINT8                           aucReserved[1];

} SM_ESM_PDP_QOS_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_EPS_QOS_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 详见TS 24.301 section 9.9.4.3 EPS Quality of service
              L NAS提供的QOS各参数，已译码
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucQCI;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulULMaxRate ;       /* 单位为kbps */
    VOS_UINT32                          ulDLMaxRate;        /* 单位为kbps */
    VOS_UINT32                          ulULGMaxRate;       /* 单位为kbps */
    VOS_UINT32                          ulDLGMaxRate;       /* 单位为kbps */

} SM_ESM_EPS_QOS_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_PF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 详见TS 24.008 section 10.5.6.12 Traffic Flow Template，已译码
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask : 1;
    VOS_UINT32                          bitOpProtocolId         : 1;
    VOS_UINT32                          bitOpSingleLocalPort    : 1;
    VOS_UINT32                          bitOpLocalPortRange     : 1;
    VOS_UINT32                          bitOpSingleRemotePort   : 1;
    VOS_UINT32                          bitOpRemotePortRange    : 1;
    VOS_UINT32                          bitOpSecuParaIndex      : 1;
    VOS_UINT32                          bitOpTypeOfService      : 1;
    VOS_UINT32                          bitOpFlowLabelType      : 1;
    VOS_UINT32                          bitOpLocalIpv4AddrAndMask : 1;
    VOS_UINT32                          bitOpLocalIpv6AddrAndMask : 1;
    VOS_UINT32                          bitOpSpare              : 20;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    SM_ESM_TRANSFER_DIRECTION_ENUM_UINT8 enDirection;
    VOS_UINT8                           ucPrecedence;             /*packet filter evaluation precedence*/

    VOS_UINT32                          ulSecuParaIndex;          /*SPI*/
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;             /*协议号*/
    VOS_UINT8                           ucTypeOfService;          /*TOS*/

    VOS_UINT8                           ucTypeOfServiceMask;      /*TOS Mask*/
    VOS_UINT8                           aucReserved[1];

    VOS_UINT8                           aucRmtIpv4Address[SM_ESM_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpAddress[0]为IP地址高字节位
                                                                    ucSourceIpAddress[3]为低字节位*/
    VOS_UINT8                           aucRmtIpv4Mask[SM_ESM_IPV4_ADDR_LEN];
                                                                  /*ucSourceIpMask[0]为IP地址高字节位 ,
                                                                    ucSourceIpMask[3]为低字节位 */
    VOS_UINT8                           aucRmtIpv6Address[SM_ESM_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Address[0]为IPv6接口标识高字节位
                                                                    ucRmtIpv6Address[15]为IPv6接口标识低字节位*/
    VOS_UINT8                           aucRmtIpv6Mask[SM_ESM_IPV6_ADDR_LEN];
                                                                  /*ucRmtIpv6Mask[0]为高字节位
                                                                    ucRmtIpv6Mask[15]为低字节位*/

    VOS_UINT32                          ulFlowLabelType;          /*FlowLabelType*/
    VOS_UINT8                           aucLocalIpv4Addr[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv4Mask[SM_ESM_IPV4_ADDR_LEN];
    VOS_UINT8                           aucLocalIpv6Addr[SM_ESM_IPV6_ADDR_LEN];
    VOS_UINT8                           ucLocalIpv6Prefix;
    VOS_UINT8                           aucReserved2[3];

} SM_ESM_PF_STRU;

/*****************************************************************************
 结构名称   : SM_ESM_CID_PF_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : CID联合PF的结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCid;
    SM_ESM_PF_STRU                      stPf;

} SM_ESM_CID_PF_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_TFT_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : TFT结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPfNum;
    SM_ESM_CID_PF_STRU                  astCidPf[SM_ESM_MAX_TFT_PF_NUM];

} SM_ESM_TFT_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_EPS_APN_AMBR_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : 见TS 24.008 section 9.9.4.2 APN aggregate maximum bit rate，未译码
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDLApnAmbrExt   : 1;
    VOS_UINT32                          bitOpULApnAmbrExt   : 1;
    VOS_UINT32                          bitOpDLApnAmbrExt2  : 1;
    VOS_UINT32                          bitOpULApnAmbrExt2  : 1;
    VOS_UINT32                          bitOpSpare          : 28;

    VOS_UINT8                           ucDLApnAmbr;
    VOS_UINT8                           ucULApnAmbr;
    VOS_UINT8                           ucDLApnAmbrExt;
    VOS_UINT8                           ucULApnAmbrExt;
    VOS_UINT8                           ucDLApnAmbrExt2;
    VOS_UINT8                           ucULApnAmbrExt2;

    VOS_UINT8                           aucReserved[2];

} SM_ESM_EPS_APN_AMBR_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_TRANSACTION_ID_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : Transaction ID 参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTiFlag;
    VOS_UINT8                           ucTiValue;

    VOS_UINT8                           aucReserved[2];

} SM_ESM_TRANSACTION_ID_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_PDP_CONTEXT_INFO_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : SM -> ESM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                    /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpLinkedNsapi    : 1;
    VOS_UINT32                          bitOpPdpQos         : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpTft            : 1;
    VOS_UINT32                          bitOpPcoIpv4Item    : 1;
    VOS_UINT32                          bitOpPcoIpv6Item    : 1;
    VOS_UINT32                          bitOpEmcInd         : 1;
    VOS_UINT32                          bitOpImCnSigalFlag  : 1;
    VOS_UINT32                          bitSpare            : 24;
    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption;

    SM_ESM_TRANSACTION_ID_STRU          stTransId;

    VOS_UINT32                          ulNsapi;

    /* 此承载对应的CID，一个BIT对应一个CID，由低到高,例如：BIT1代表CID 1，BIT32代表CID 32 */
    VOS_UINT32                          ulBitCid;

    /* 二次激活,则此成员有效 */
    VOS_UINT32                          ulLinkedNsapi;

    SM_ESM_PDP_ADDR_STRU                stPdpAddr;
    SM_ESM_PDP_QOS_STRU                 stPdpQos;
    SM_ESM_APN_STRU                     stApn;
    SM_ESM_TFT_STRU                     stTft;
    SM_ESM_PCO_IPV4_ITEM_STRU           stPcoIpv4Item;
    SM_ESM_PCO_IPV6_ITEM_STRU           stPcoIpv6Item;

    SM_ESM_PDP_EMC_IND_ENUM_UINT8           enEmergencyInd;
    SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM_UINT8    enImCnSignalFlag;
    VOS_UINT8                           aucReserved[2];

} SM_ESM_PDP_CONTEXT_INFO_IND_STRU;


/*****************************************************************************
 结构名称   : SM_ESM_EPS_BEARER_INFO_IND_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : ESM -> SM
              EPS Bearer的任何操作(Activate, Modify, Deactivate), 如果EPS的承载信息
              中包含TI, 则在次消息中必须填写. 如果消息中不携带TI, SM直接丢弃该消息
              linked EPS bearer identity (if available) 映射为 linked TI;
              PDN address and APN of the default EPS bearer context映射为PDP address and APN of the default PDP context;
              TFT of the default EPS bearer context映射为 the TFT of the default PDP context;
              TFTs of the dedicated EPS bearer contexts 映射为TFTs of the secondary PDP contexts;
              当操作类型为SM_ESM_PDP_OPT_MODIFY时，OP域为0，则表示不更新此项；OP域为1，则表示更新此项；
              当需要删除TFT信息时，将bitOpPf设为1，ulPfNum设为0；
              当要删除DNS，NBNS,P-CSCF等项时，需要将相应OP域设为1，相应项内容填为全0；
              ucLlcSapi，ucRadioPriority，ucPacketFlowId这三项的合法性由GU模的SM来做
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;            /* _H2ASN_Skip */

    VOS_UINT32                          bitOpLinkedEpsbId   : 1;
    VOS_UINT32                          bitOpEpsQos         : 1;
    VOS_UINT32                          bitOpTft            : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpApnAmbr        : 1;
    VOS_UINT32                          bitOpTransId        : 1;
    VOS_UINT32                          bitOpNegQos         : 1;
    VOS_UINT32                          bitOpLlcSapi        : 1;
    VOS_UINT32                          bitOpRadioPriority  : 1;
    VOS_UINT32                          bitOpPacketFlowId   : 1;
    VOS_UINT32                          bitOpPcoIpv4Item    : 1;
    VOS_UINT32                          bitOpPcoIpv6Item    : 1;
    VOS_UINT32                          bitOpBcm            : 1;
    VOS_UINT32                          bitOpEmcInd         : 1;
    VOS_UINT32                          bitOpImCnSigalFlag  : 1;
    VOS_UINT32                          bitOpErrorCode      : 1;
    VOS_UINT32                          bitOpSpare          : 16;

    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption;

    /* EPS bearer identity映射为NSAPI */
    VOS_UINT32                          ulEpsbId;

    /* 此承载对应的CID，一个BIT对应一个CID，由低到高,例如：BIT1代表CID 1，BIT32代表CID 32 */
    VOS_UINT32                          ulBitCid;

    /* 与此承载关联的EPS承载ID */
    VOS_UINT32                          ulLinkedEpsbId;

    SM_ESM_PDN_ADDR_STRU                stPdnAddr;
    SM_ESM_EPS_APN_AMBR_STRU            stEpsApnAmbr;
    SM_ESM_EPS_QOS_STRU                 stEpsQos;
    SM_ESM_TFT_STRU                     stTft;
    SM_ESM_APN_STRU                     stApn;
    SM_ESM_PDP_QOS_STRU                 stNegQos;
    SM_ESM_PCO_IPV4_ITEM_STRU           stPcoIpv4Item;
    SM_ESM_PCO_IPV6_ITEM_STRU           stPcoIpv6Item;

    SM_ESM_TRANSACTION_ID_STRU          stTransId;
    VOS_UINT8                           ucLlcSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
    SM_ESM_BCM_ENUM_UINT8               enBcm;

    SM_ESM_PDP_EMC_IND_ENUM_UINT8           enEmergencyInd;
    SM_ESM_PDP_IM_CN_SIG_FLAG_ENUM_UINT8    enImCnSignalFlag;
    VOS_UINT8                           aucReserved[2];
    
    VOS_UINT32                          ulErrorCode;   /* 收到网侧原因值后通知SM的错误码 */
} SM_ESM_EPS_BEARER_INFO_IND_STRU;

/*sunbing 49683 2013-10-14 VoLTE begin*/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    VOS_UINT32                              ulMsgId;        /* _H2ASN_Skip */
    ESM_APS_NOTIFICATION_IND_ENUM_UINT32    enNotificationIndicator;
}ESM_APS_NOTIFICATION_IND_STRU;
/*sunbing 49683 2013-10-14 VoLTE end*/

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
    SM_ESM_MSG_ID_ENUM_UINT32           ulMsgId;            /* _H2ASN_MsgChoice_Export SM_ESM_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          SM_ESM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} SM_ESM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    SM_ESM_INTERFACE_MSG_DATA           stMsgData;
} SmEsmInterface_MSG;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
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

#endif
