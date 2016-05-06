/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasIpInterface.h
  Description     : IP与NAS的接口文件
  History         :
      1.lihong 00150010 2010-11-20   Draft Enact

******************************************************************************/




#ifndef __NASIPINTERFACE_H__
#define __NASIPINTERFACE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "PsTypeDef.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


#if (VOS_OS_VER != VOS_WIN32)
 #pragma pack(4)
#else
 #pragma pack(push, 4)
#endif


/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_IP_IPV6_IFID_LENGTH         (8)
#define NAS_IP_IPV6_ADDR_LENGTH         (16)
#define NAS_IP_IPV4_ADDR_LENGTH         (4)
#define NAS_IP_MAX_DNS_SERVER_NUM       (2)




#define ESM_IP_MSG_HDR                  (PS_MSG_ID_NAS_TO_IP_BASE)
#define IP_ESM_MSG_HDR                  (PS_MSG_ID_IP_TO_NAS_BASE)
#define RABM_IP_MSG_HDR                 (PS_MSG_ID_NAS_TO_IP_BASE + 0x08)
#define IP_RABM_MSG_HDR                 (PS_MSG_ID_IP_TO_NAS_BASE + 0x08)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_IP_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS与IP的消息原语类型
*****************************************************************************/
enum NAS_IP_MSG_ID_ENUM
{
    /* ESM发给IP的原语 */
    ID_ESM_IP_START_REQ                 = (ESM_IP_MSG_HDR + 0x00),  /* _H2ASN_MsgChoice ESM_IP_START_REQ_STRU */
    ID_ESM_IP_STOP_REQ                  = (ESM_IP_MSG_HDR + 0x01),  /* _H2ASN_MsgChoice ESM_IP_STOP_REQ_STRU */
    ID_ESM_IP_CONFIG_PARA_REQ           = (ESM_IP_MSG_HDR + 0x02),  /* _H2ASN_MsgChoice ESM_IP_CONFIG_PARA_REQ_STRU */
    ID_ESM_IP_PDP_RELEASE_IND           = (ESM_IP_MSG_HDR + 0x03),  /* _H2ASN_MsgChoice ESM_IP_PDP_RELEASE_IND_STRU */
    ID_ESM_IP_REL_IND                   = (ESM_IP_MSG_HDR + 0x04),  /* _H2ASN_MsgChoice ESM_IP_REL_IND_STRU */
    ID_ESM_IP_NW_PARA_IND               = (ESM_IP_MSG_HDR + 0x05),  /* _H2ASN_MsgChoice ESM_IP_NW_PARA_IND_STRU */

    /* IP发给ESM的原语 */
    ID_ESM_IP_START_CNF                 = (IP_ESM_MSG_HDR + 0x00),  /* _H2ASN_MsgChoice ESM_IP_START_CNF_STRU */
    ID_ESM_IP_STOP_CNF                  = (IP_ESM_MSG_HDR + 0x01),  /* _H2ASN_MsgChoice ESM_IP_STOP_CNF_STRU */
    ID_ESM_IP_STATE_IND                 = (IP_ESM_MSG_HDR + 0x02),  /* _H2ASN_MsgChoice ESM_IP_STATE_IND_STRU */
    ID_ESM_IP_CONFIG_PARA_IND           = (IP_ESM_MSG_HDR + 0x03),  /* _H2ASN_MsgChoice ESM_IP_CONFIG_PARA_IND_STRU */

    /* RABM发给IP的原语 */
    ID_IP_RABM_START_FILTER_CNF         = (RABM_IP_MSG_HDR + 0x00), /* _H2ASN_MsgChoice IP_RABM_START_FILTER_CNF_STRU */
    ID_IP_RABM_STOP_FILTER_CNF          = (RABM_IP_MSG_HDR + 0x01), /* _H2ASN_MsgChoice IP_RABM_STOP_FILTER_CNF_STRU */
    ID_IP_RABM_DATA_IND                 = (RABM_IP_MSG_HDR + 0x02), /* _H2ASN_MsgChoice IP_RABM_DATA_IND_STRU */

    /* IP发给RABM的原语 */
    ID_IP_RABM_START_FILTER_REQ         = (IP_RABM_MSG_HDR + 0x00), /* _H2ASN_MsgChoice IP_RABM_START_FILTER_REQ_STRU */
    ID_IP_RABM_STOP_FILTER_REQ          = (IP_RABM_MSG_HDR + 0x01), /* _H2ASN_MsgChoice IP_RABM_STOP_FILTER_REQ_STRU */

    ID_NAS_IP_MSG_ID_BUTT
};
typedef VOS_UINT32   NAS_IP_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_IP_DHCPV4_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : DHCPV4使用标识
*****************************************************************************/
enum NAS_IP_DHCPV4_FLAG_ENUM
{
    NAS_IP_DHCPV4_NOT_USED              = 0x00,
    NAS_IP_DHCPV4_USED                  = 0x01,
    NAS_IP_DHCPV4_BUTT
};
typedef VOS_UINT32 NAS_IP_DHCPV4_FLAG_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_IP_ICMPV6_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : ICMPV6使用标识
*****************************************************************************/
enum NAS_IP_ICMPV6_FLAG_ENUM
{
    NAS_IP_ICMPV6_NOT_USED              = 0x00,
    NAS_IP_ICMPV6_USED                  = 0x01,
    NAS_IP_ICMPV6_BUTT
};
typedef VOS_UINT32 NAS_IP_ICMPV6_FLAG_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_IP_STATE_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : IP状态枚举
*****************************************************************************/
enum NAS_IP_STATE_TYPE_ENUM
{
    NAS_IP_STATE_TYPE_FOURTH_DISCOVER_EXPIRE    = 1,
    NAS_IP_STATE_TYPE_FOURTH_REQUEST_EXPIRE     = 2,
    NAS_IP_STATE_TYPE_T1_EXPIRE                 = 3,
    NAS_IP_STATE_TYPE_T2_EXPIRE                 = 4,
    NAS_IP_STATE_TYPE_T_EXPIRE                  = 5,
    NAS_IP_STATE_TYPE_BUTT
};
typedef VOS_UINT32  NAS_IP_STATE_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_IP_FILTER_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 数据包过滤类型枚举
*****************************************************************************/
enum NAS_IP_FILTER_TYPE_ENUM
{
    NAS_IP_FILTER_TYPE_DHCPV4          = 0x00,
    NAS_IP_FILTER_TYPE_ICMPV6          = 0x01,
    NAS_IP_FILTER_TYPE_BUTT
};
typedef VOS_UINT32 NAS_IP_FILTER_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_IP_FILTER_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : NAS给IP返回的结果枚举
*****************************************************************************/
enum NAS_IP_RESULT_ENUM
{
    NAS_IP_RESULT_SUCCESS              = 0x00,
    NAS_IP_RESULT_FAIL                 = 0x01,
    NAS_IP_RESULT_BUTT
};
typedef VOS_UINT32 NAS_IP_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_IP_IP_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : IP类型枚举
*****************************************************************************/
enum NAS_IP_IP_TYPE_ENUM
{
    NAS_IP_IP_TYPE_IPV4                 = 0x01,
    NAS_IP_IP_TYPE_IPV6                 = 0x02,
    NAS_IP_IP_TYPE_IPV4_IPV6            = 0x03,

    NAS_IP_IP_TYPE_BUTT
};
typedef VOS_UINT8 NAS_IP_IP_TYPE_ENUM_8;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : ESM_IP_CONFIG_PARA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_CONFIG_PARA_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRev[3];

    /*指示是否用DHCPv4来获取IPv4参数，0表示不用DHCPv4来获取IPv4参数，1表示用DHCPv4来获取IPv4参数*/
    NAS_IP_DHCPV4_FLAG_ENUM_UINT32      enDhcpv4Flag;

    /*IPV4格式的IP地址，aucIpv4Addr[0]为IP地址高字节位，aucIpv4Addr[3]为低字节位*/
    VOS_UINT8                           aucIpv4Addr[NAS_IP_IPV4_ADDR_LENGTH];

    /*指示是否用ICMPv6来获取IPv6参数，0表示不用ICMPv6来获取IPv6参数，1表示用ICMPv6来获取IPv6参数*/
    NAS_IP_ICMPV6_FLAG_ENUM_UINT32      enIcmpv6Flag;

    /*IPv6接口标示符，由网络分配，用于UE IPv6 Link local 地址的生成,aucIpv6InterfacId[0]为接口标示符高字节,aucIpv6InterfacId[7]为接口标示符低字节，0,0,0,0,0,0,0,0为无效接口标示符*/
    VOS_UINT8                           aucIpv6InterfacId[NAS_IP_IPV6_IFID_LENGTH];
} ESM_IP_CONFIG_PARA_REQ_STRU;

/*****************************************************************************
 结构名    : NAS_IP_IP_ADDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IP地址数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[NAS_IP_IPV4_ADDR_LENGTH];
    VOS_UINT8                           aucIpV6Addr[NAS_IP_IPV6_ADDR_LENGTH];
}NAS_IP_IP_ADDR_STRU;

/*****************************************************************************
 结构名    : NAS_IP_DNS_SER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DNS服务器数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDnsSerNum;        /*DNS服务器个数*/
    VOS_UINT8                           aucReserved[3];
    NAS_IP_IP_ADDR_STRU                 astDnsServer[NAS_IP_MAX_DNS_SERVER_NUM];
}NAS_IP_DNS_SER_STRU;

/*****************************************************************************
 结构名    : NAS_IP_IPV6_PREFIX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6前缀数据结构
*****************************************************************************/
typedef struct
{
    /*Global地址前缀有效bit位的长度*/
    VOS_UINT32                          ulGlobalPrefixLength;

    /*Global地址前缀，aucIpv6AddrPrefix[0]为前缀的高字节位，无效位补零*/
    VOS_UINT8                            aucIpv6AddrPrefix[NAS_IP_IPV6_IFID_LENGTH];
}NAS_IP_IPV6_PREFIX_STRU;

/*****************************************************************************
 结构名    : ESM_IP_CONFIG_PARA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_CONFIG_PARA_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpIpv4Addr                     : 1;
    VOS_UINT32                          bitOpDnsServer                    : 1;
    VOS_UINT32                          bitOpIpv6Prefix                   : 1;
    VOS_UINT32                          bitOpSpare                        : 29;

    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRev[3];

    /*通过DHCP获得的IPV4格式的IP地址，aucIpv4Addr[0]为IP地址高字节位，aucIpv4Addr[3]为低字节位*/
    VOS_UINT8                           aucIpv4Addr[NAS_IP_IPV4_ADDR_LENGTH];

    /* DNS服务器 */
    NAS_IP_DNS_SER_STRU                 stDnsServer;

    /* 全局IPv6地址前缀 */
    NAS_IP_IPV6_PREFIX_STRU             stIpv6Prefix;
} ESM_IP_CONFIG_PARA_IND_STRU;

/*****************************************************************************
 结构名    : ESM_IP_PDP_RELEASE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_PDP_RELEASE_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
   VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/
   VOS_UINT8                            ucEpsbId;
   VOS_UINT8                            aucRev[3];
} ESM_IP_PDP_RELEASE_IND_STRU;

/*****************************************************************************
 结构名    : ESM_IP_STATE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_STATE_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRev[3];

    /* IP模块状态 */
    NAS_IP_STATE_TYPE_ENUM_UINT32       enIpState;
} ESM_IP_STATE_IND_STRU;

/*****************************************************************************
 结构名    : ESM_IP_START_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_START_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
   VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/
} ESM_IP_START_REQ_STRU;

/*****************************************************************************
 结构名    : ESM_IP_START_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_START_CNF_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
} ESM_IP_START_CNF_STRU;

/*****************************************************************************
 结构名    : ESM_IP_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_STOP_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
   VOS_MSG_HEADER                                           /*_H2ASN_Skip*/
   VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/
} ESM_IP_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : ESM_IP_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_STOP_CNF_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulRslt;
} ESM_IP_STOP_CNF_STRU;

/*****************************************************************************
 结构名    : ESM_IP_REL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_REL_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
} ESM_IP_REL_IND_STRU;

/*****************************************************************************
 结构名    : IP_RABM_START_FILTER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IP_RABM_START_FILTER_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    NAS_IP_FILTER_TYPE_ENUM_UINT32      enFilterType;
} IP_RABM_START_FILTER_REQ_STRU;

/*****************************************************************************
 结构名    : IP_RABM_START_FILTER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IP_RABM_START_FILTER_CNF_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    NAS_IP_RESULT_ENUM_UINT32           enRslt;
} IP_RABM_START_FILTER_CNF_STRU;

/*****************************************************************************
 结构名    : IP_RABM_STOP_FILTER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IP_RABM_STOP_FILTER_REQ_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    NAS_IP_FILTER_TYPE_ENUM_UINT32      enFilterType;
} IP_RABM_STOP_FILTER_REQ_STRU;

/*****************************************************************************
 结构名    : IP_RABM_STOP_FILTER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IP_RABM_STOP_FILTER_CNF_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    NAS_IP_RESULT_ENUM_UINT32           enRslt;
} IP_RABM_STOP_FILTER_CNF_STRU;

/*****************************************************************************
 结构名    : ESM_IP_NW_PARA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_NW_PARA_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          bitOpIpAddr         : 1;
    VOS_UINT32                          bitOpSubnetMask     : 1;
    VOS_UINT32                          bitOpGateWay        : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           ucEpsbId;           /* 承载号*/
    VOS_UINT8                           aucRev[3];          /* 消息结构体对齐*/

    NAS_IP_IP_ADDR_STRU                 stIpAddr;           /* IP地址 */
    NAS_IP_IP_ADDR_STRU                 stSubnetMask;       /* 子网掩码 */
    NAS_IP_IP_ADDR_STRU                 stGateWay;          /* 默认网关 */
    NAS_IP_DNS_SER_STRU                 stDnsServer;        /* DNS服务器列表 */
} ESM_IP_NW_PARA_IND_STRU;


/*****************************************************************************
 结构名    : NAS_IP_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS_IP_MSG_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIpMsgSize;
    VOS_UINT8                           aucIpMsg[4];
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}NAS_IP_MSG_STRU;

/*****************************************************************************
 结构名    : IP_RABM_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IP_RABM_DATA_IND_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucRev[3];

    /* DHCPv4包 */
    NAS_IP_MSG_STRU                     stIpMsg;
} IP_RABM_DATA_IND_STRU;


typedef struct
{
    NAS_IP_MSG_ID_ENUM_UINT32           enMsgID;            /*_H2ASN_MsgChoice_Export NAS_IP_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_IP_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}NAS_IP_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    NAS_IP_MSG_DATA                     stMsgData;
} NasIpInterface_MSG;


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
 Function Name   : IP_IsDhcpv4ServerPacket
 Description     : 判定是否为DHCPV4 SERVER包
 Input           : pucIpMsg---------------------IP数据包首地址
                   ulIpMsgLen-------------------IP数据包长度
 Output          : VOS_VOID
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-11-29  Draft Enact

*****************************************************************************/
extern VOS_UINT32 IP_IsDhcpv4ServerPacket
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen
);
extern VOS_INT32  IP_PrintEsmIpMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);
extern VOS_INT32  IP_PrintRabmIpMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
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

#endif /* end of NasIpInterface.h */
