/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : AtNdisInterface.h header file
  History           :
******************************************************************************/

#ifndef __ATNDISINTERFACE_H__
#define __ATNDISINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "mdrv.h"
#include "msp_at.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#ifndef IPV4_ADDR_LEN
#define   IPV4_ADDR_LEN      4       /*IPV4地址长度*/
#endif

#ifndef	IPV6_ADDR_LEN
#define   IPV6_ADDR_LEN      16      /*IPV6地址长度*/
#endif

#define   MIN_VAL_EPSID      5
#define   MAX_VAL_EPSID      15

#define   NDIS_MSG_ID_BASE                  0x3000
#define   NDIS_MSG_ID_END                   0x3100


#define   MIN_VAL_HANDLE                  (0x5A0000)
#define   MAX_VAL_HANDLE                  (0x5A003F)

#define NDIS_INVALID_HANDLEINDEX          (0x7F)
#define NDIS_INVALID_HANDLE               (0x7FFFFFFF)
#define NDIS_INVALID_RABID                (0x7F)

#define NDIS_INVALID_SPEPORT              (0)

#define   AT_NDIS_IPV4_ADDR_LENGTH          (4)
#define   AT_NDIS_IPV6_ADDR_LENGTH          (16)
#define   AT_NDIS_MAX_PREFIX_NUM_IN_RA      (6)
#define   AT_NDIS_IPV6_IFID_LENGTH          (8)
/*****************************************************************************
 结构名    : NDIS_MSG_ID_SECTION_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MSP和NDIS模块间的接口消息
*****************************************************************************/
enum NDIS_MSG_ID_SECTION_ENUM
{
    NDIS_MSG_ID_AT_TO_NDIS_BASE   = NDIS_MSG_ID_BASE,                         /*从MSP AT发往NDIS的消息ID的起始值*/

    NDIS_MSG_ID_NDIS_TO_AT_BASE   = NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x20        /*从NDIS发往MSP AT的消息ID的起始值*/
};
/*****************************************************************************
 结构名    : AT_NDIS_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MSP和NDIS模块间的接口消息
*****************************************************************************/
enum AT_NDIS_MSG_TYPE_ENUM
{
    ID_AT_NDIS_PDNINFO_CFG_REQ               = (NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x01), /*0x3001*/    /* _H2ASN_MsgChoice AT_NDIS_PDNINFO_CFG_REQ_STRU*/      /* MSP配置PDN信息 */
    ID_AT_NDIS_PDNINFO_CFG_CNF               = (NDIS_MSG_ID_NDIS_TO_AT_BASE + 0x01), /*0x3021*/    /* _H2ASN_MsgChoice AT_NDIS_PDNINFO_CFG_CNF_STRU*/      /* 上述消息确认消息 */

    ID_AT_NDIS_PDNINFO_REL_REQ               = (NDIS_MSG_ID_AT_TO_NDIS_BASE + 0x02),  /*0x3002*/   /* _H2ASN_MsgChoice  AT_NDIS_PDNINFO_REL_REQ_STRU*/      /* MSP配置PDN信息释放消息 */
    ID_AT_NDIS_PDNINFO_REL_CNF               = (NDIS_MSG_ID_NDIS_TO_AT_BASE + 0x02),  /*0x3022*/   /* _H2ASN_MsgChoice  AT_NDIS_PDNINFO_REL_CNF_STRU*/      /* 上述消息确认消息 */

    ID_AT_NDIS_MSG_TYPE_END
};
typedef VOS_UINT32 AT_NDIS_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : OM_NDIS_KEY_EVENT_ENUM
 结构说明  : 关键事件的取值的定义
*****************************************************************************/
enum OM_NDIS_KEY_EVENT_ENUM
{

    NDIS_OM_PDN_INFO_CFG       = 1,
    NDIS_OM_PDN_INFO_REL
};
typedef VOS_UINT32 OM_NDIS_KEY_EVENT_ENUM_UINT32;


/*****************************************************************************
 结构名    : AT_NDIS_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MSP配置的结果:成功还是失败
*****************************************************************************/
enum AT_NDIS_ENUM
{
    AT_NDIS_SUCC                            = 0,
    AT_NDIS_FAIL                            = 1,
    AT_NDIS_BUTT
};
typedef VOS_UINT8   AT_NDIS_RSLT_ENUM_UINT8;

/*****************************************************************************
 结构名    : AT_NDIS_PDNCFG_CNF_TYPE
 协议表格  :
 ASN.1描述 :
 结构说明  : NDIS向AT返回PDN配置结果类型
*****************************************************************************/
enum AT_NDIS_PDNCFG_CNF_TYPE
{
    AT_NDIS_PDNCFG_CNF_SUCC                       = 0,   /*配置成功*/
    AT_NDIS_PDNCFG_CNF_FAIL                       = 1,   /*配置失败*/
    AT_NDIS_PDNCFG_CNF_IPV4ONLY_SUCC              = 2,   /*IPV4和IPV6参数同时有效时，只有IPV4参数配置成功*/
    AT_NDIS_PDNCFG_CNF_IPV6ONLY_SUCC              = 3,   /*IPV4和IPV6参数同时有效时，只有IPV6参数配置成功*/
    AT_NDIS_PDNCFG_CNF_BUUT
};
typedef VOS_UINT8   AT_NDIS_PDNCFG_CNF_UINT8;

/*****************************************************************************
 结构名    : AT_NDIS_DHCP_INFO_TYPE
 协议表格  :
 ASN.1描述 :
 结构说明  : AT向NDIS请求上报PDN信息类型
*****************************************************************************/
enum AT_NDIS_DHCP_INFO_TYPE_ENUM
{
    AT_NDIS_DHCP_INFO_TYPE_IPV4         = 0,     /*只查询IPV4信息*/
    AT_NDIS_DHCP_INFO_TYPE_IPV6         = 1,     /*只查询IPV6信息*/

    AT_NDIS_DHCP_INFO_TYPE_BUTT
};
typedef VOS_UINT8 AT_NDIS_DHCP_INFO_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : AT_NDIS_IPV4_ADDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4地址结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucIpV4Addr[AT_NDIS_IPV4_ADDR_LENGTH];
}AT_NDIS_IPV4_ADDR_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_IPV4_PDN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4 配置信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPdnAddr         :1;
    VOS_UINT32                          bitOpDnsPrim         :1;
    VOS_UINT32                          bitOpDnsSec          :1;
    VOS_UINT32                          bitOpWinsPrim        :1;
    VOS_UINT32                          bitOpWinsSec         :1;
    VOS_UINT32                          bitOpPcscfPrim       :1;
    VOS_UINT32                          bitOpPcscfSec        :1;
    VOS_UINT32                          bitOpSpare           :25;

    AT_NDIS_IPV4_ADDR_STRU              stPDNAddrInfo;
    AT_NDIS_IPV4_ADDR_STRU              stSubnetMask;         /*子网掩码*/
    AT_NDIS_IPV4_ADDR_STRU              stGateWayAddrInfo;    /*网关*/
    AT_NDIS_IPV4_ADDR_STRU              stDnsPrimAddrInfo;    /*主DNS信息 */
    AT_NDIS_IPV4_ADDR_STRU              stDnsSecAddrInfo;     /*辅DNS信息 */
    AT_NDIS_IPV4_ADDR_STRU              stWinsPrimAddrInfo;   /*主DNS信息 */
    AT_NDIS_IPV4_ADDR_STRU              stWinsSecAddrInfo;    /*辅DNS信息 */
    AT_NDIS_IPV4_ADDR_STRU              stPcscfPrimAddrInfo;  /*主PCSCF信息 */
    AT_NDIS_IPV4_ADDR_STRU              stPcscfSecAddrInfo;   /*辅PCSCF信息 */
}AT_NDIS_IPV4_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_IPV6_DNS_SER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6 DNS信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSerNum;           /*服务器个数*/
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucPriServer[AT_NDIS_IPV6_ADDR_LENGTH];
    VOS_UINT8                           aucSecServer[AT_NDIS_IPV6_ADDR_LENGTH];
}AT_NDIS_IPV6_DNS_SER_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_IPV6_PCSCF_SER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6 PCSCF信息结构
*****************************************************************************/
typedef AT_NDIS_IPV6_DNS_SER_STRU AT_NDIS_IPV6_PCSCF_SER_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_IPV6_PREFIX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6 前缀信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitL          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ulBitA          :1;
    VOS_UINT32                          ulBitPrefixLen  :8;
    VOS_UINT32                          ulBitRsv        :22;

    VOS_UINT32                          ulValidLifeTime;
    VOS_UINT32                          ulPreferredLifeTime;
    VOS_UINT8                           aucPrefix[AT_NDIS_IPV6_ADDR_LENGTH];
}AT_NDIS_IPV6_PREFIX_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_IPV6_PDN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6 配置信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitOpMtu              :1;
    VOS_UINT32                          ulBitRsv1               :31;

    VOS_UINT32                          ulBitCurHopLimit        :8;
    VOS_UINT32                          ulBitM                  :1;
    VOS_UINT32                          ulBitO                  :1;
    VOS_UINT32                          ulBitRsv2               :22;

    VOS_UINT8                           aucInterfaceId[AT_NDIS_IPV6_IFID_LENGTH];
    VOS_UINT32                          ulMtu;
    VOS_UINT32                          ulPrefixNum;
    AT_NDIS_IPV6_PREFIX_STRU            astPrefixList[AT_NDIS_MAX_PREFIX_NUM_IN_RA];

    AT_NDIS_IPV6_DNS_SER_STRU           stDnsSer;
    AT_NDIS_IPV6_PCSCF_SER_STRU         stPcscfSer;
} AT_NDIS_IPV6_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_PDNINFO_CFG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDN配置消息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo : 1;
    VOS_UINT32                          bitOpIpv6PdnInfo : 1;
    VOS_UINT32                          bitOpSpare       : 30;

    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;            /* 承载号 */
    VOS_UINT8                           aucRev[1];          /* 消息结构体对齐*/

    UDI_HANDLE                          ulHandle;           /* 设备ID，标识网卡 */

    AT_NDIS_IPV4_PDN_INFO_STRU          stIpv4PdnInfo;
    AT_NDIS_IPV6_PDN_INFO_STRU          stIpv6PdnInfo;

    VOS_UINT32                          ulMaxRxbps;         /*最大接收bps*/
    VOS_UINT32                          ulMaxTxbps;         /*最大发送bps*/

    VOS_INT32                           lSpePort;           /*SPE端口*/
    VOS_UINT32                          ulIpfFlag;          
}AT_NDIS_PDNINFO_CFG_REQ_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_PDNINFO_CFG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDN配置的回复信息
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                  enModemId;
    VOS_UINT8                             ucRabId;
    AT_NDIS_PDNCFG_CNF_UINT8              enResult;
    VOS_UINT8                             ucRabType;
    VOS_UINT8                             aucRsv[3];
}AT_NDIS_PDNINFO_CFG_CNF_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_PDNINFO_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDN释放消息
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                  enModemId;
    VOS_UINT8                             ucRabId;          /*范围5-15*/
    VOS_UINT8                             ucRcv[1];
}AT_NDIS_PDNINFO_REL_REQ_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_PDNINFO_REL_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDN释放回复消息
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                             ucRabId;      /*范围5-15*/
    AT_NDIS_RSLT_ENUM_UINT8               enResult;
    VOS_UINT8                             ucRabType;
    VOS_UINT8                           aucRsv[3];
}AT_NDIS_PDNINFO_REL_CNF_STRU;

/*****************************************************************************
 结构名    : AT_NDIS_USBABNORMAL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : USB异常时通知MSP
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             aucRev[4];
}AT_NDIS_USBABNORMAL_IND_STRU;



/*

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucSysMode;
    VOS_UINT16 usMsgSize;
    VOS_UINT32 ulMsgId;
    VOS_UINT8  pMsg[0];
} AT_FW_CMD_BINARY_MSG_STRU;
*/




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
