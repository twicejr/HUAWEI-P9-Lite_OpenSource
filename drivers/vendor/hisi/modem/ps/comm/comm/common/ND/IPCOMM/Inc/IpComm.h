


#ifndef __IPCOMM_H__
#define __IPCOMM_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "IpIpmGlobal.h"
#include "TTFComm.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define          ND_TASK_PID                  UEPS_PID_NDCLIENT
#elif (OSA_CPU_ACPU == VOS_OSA_CPU)
#define          ND_TASK_PID                  UEPS_PID_NDSERVER
#endif

/*通过ModemId和EpsId组合成exEpsId，高2bit为ModemId,第6bit为EpsId*/
#define ND_FORM_EXEPSID(ModemId,EpsId)          (VOS_UINT8)((VOS_UINT8)(((ModemId) << 6) | (EpsId)))

/*从ExEpsId中获得ModemId*/
#define ND_GET_MODEMID_FROM_EXEPSID(ExEpsId)    (VOS_UINT16)(((ExEpsId) & 0xC0) >> 6)

/*从ExEpsId中获得EpsId*/
#define ND_GET_EPSID_FROM_EXEPSID(ExEpsId)      (VOS_UINT8)((ExEpsId) & 0x3F)
#define IP_DHCPV4SERVER_OFF                                 (0)
#define IP_DHCPV4SERVER_ON                                  (1)

#define IP_IPV6_LINK_LOCAL_PREFIX                           (0xfe80)
#define IP_IPV6_LINK_LOCAL_MASK                             (0xffc0)
#define IP_IPV6_ND_HOP_LIMIT                                (0xff)
#define IP_IPV6_ND_VALID_CODE                               (0)

#define ND_MAX_EPSB_ID             (15)                /*最大的承载号*/
#define ND_MIN_EPSB_ID             (5)                 /*最小的承载号*/

#define ND_IP_MAX_PREFIX_NUM_IN_RA      (6)
#define ND_IPV6_IF_OFFSET               (8)
#define ND_IPV6_IF_LEN                  (8)
#define ND_IP_IPV6_PREFIX_LENGTH        (8)

#define ND_IP_IPV6_IFID_LENGTH          (8)
#define ND_IP_IPV6_ADDR_LENGTH          (16)

#define IP_MAX_PREFIX_NUM_IN_RA         ND_IP_MAX_PREFIX_NUM_IN_RA


/*huibo DHCPV6 maro begin*/
#define IP_IPV6_OP_TRUE                   (1)
#define IP_IPV6_DHCP6_TYPE                (55)
#define IP_IPV6_DHCP6_PC_PORT             (546)
#define IP_IPV6_DHCP6_UE_PORT             (547)
#define IP_IPV6_DHCP6_INFOR_REQ           (11)
#define IP_IPV6_DHCP6_TYPE_REPLY          (7)
#define IP_IPV6_DHCP6_TRANS_ID_LEN        (3)
#define IP_IPV6_DHCP6_OPT_DNS_SERVERS     (23)
#define IP_IPV6_DHCP6_REPLY_HDR_LEN       (8) /*DHCP REPLY 头四字节 + Option头四字节*/

#define IP_IPV6_HW_TYPE                     (1)
#define IP_IPV6_MAX_DNS_NUM                 (2)
#define IP_IPV6_DHCP_OPT_LINKADDR_SIZE      (6)
#define IP_IPV6_DHCP_OPT_CLIEND_ID          (1)
#define IP_IPV6_DHCP_OPT_SERVER_ID          (2)
#define IP_IPV6_DHCP_OPT_REQUEST            (6)
#define IP_IPV6_DHCP_DUID_LL_OPT_TYPE       (3)
#define IP_IPV6_DHCP_OPT_CLIENT_ID_LEN      (10 + 4)
#define IP_IPV6_DHCP_DUID_LL_OPT_LEN        (10)

/*huibo DHCPV6 maro end*/

#define IP_IPV6_BASIC_HEAD_NEXT_HEAD_OFFSET                 (6)
#define IP_IPV6_BASIC_HEAD_PAYLOAD_OFFSET                   (4)
#define IP_IPV6_BASIC_HOP_LIMIT_OFFSET                      (7)
#define IP_IPV6_SRC_ADDR_OFFSET                             (8)
#define IP_IPV6_DST_ADDR_OFFSET                             (24)
#define IP_IPV6_EXT_HEAD_NEXT_HEAD_OFFSET                   (0)
#define IP_IPV6_EXT_HEAD_LEN_OFFSET                         (1)
#define IP_IPV6_FRA_EXT_HEAD_FRGOFFSET_OFFSET               (2)
#define IP_IPV6_FRA_EXT_HEAD_ID_OFFSET                      (4)
#define IP_IPV6_FRAMENT_EXT_HEAD_LEN                        (8)
#define IP_IPV6_AH_EXT_HEAD_SPI_OFFSET                      (4)
#define IP_IPV6_AH_EXT_HEAD_SQN_OFFSET                      (8)
#define IP_IPV6_ESP_EXT_HEAD_SQN_OFFSET                     (4)

#define IP_ICMPV6_TYPE_OFFSET                               (0)
#define IP_ICMPV6_CODE_OFFSET                               (1)
#define IP_ICMPV6_CHECKSUM_OFFSET                           (2)
#define IP_ICMPV6_HOP_LIMIT_OFFSET                          (4)

#define IP_ICMPV6_INIT_CHECKSUM                             (0)

#define IP_PACKAGE_HEADER_RESERVE                           (2)

#define IP_ICMPV6_RS_MAX_LENGTH                             (200)

#define IP_ND_STAT_INC(x)           (x) = ((x) + (1))

#define IP_ICMPV6_NA_FLAG_OFFSET                            (4)


#define IP_ICMPV6_TARGET_ADDR_OFFSET                        (8)

#define IP_ICMPV6_RS_HEADER_LEN                             (8)
#define IP_ICMPV6_RA_HEADER_LEN                             (16)
#define IP_ICMPV6_NS_HEADER_LEN                             (24)
#define IP_ICMPV6_NA_HEADER_LEN                             (24)

#define IP_ND_OPT_UNIT_LEN                                  (8)

/*内存操作*/
#define IP_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulBufferLen) \
             (VOS_VOID)VOS_MemCpy( pucDestBuffer, pucSrcBuffer, ulBufferLen )

#define IP_MEM_SET(pucBuffer, ucData, ulBufferLen) \
             (VOS_VOID)VOS_MemSet( pucBuffer, ucData, ulBufferLen )

#define IP_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen) \
             VOS_MemCmp(pucDestBuffer,pucSrcBuffer,ulBufferLen)


#define IP_GetNdOptionLen(ucNdOptionLen)                    ((ucNdOptionLen) * IP_ND_OPT_UNIT_LEN)

#define IP_GetFragOffset(usFrgOffset, usInputData)          ((usFrgOffset) = (((usInputData) & 0xfff8) >> 3))
#define IP_GetFragM(ucFrgM, usInputData)                    ((ucFrgM) = ((usInputData) & 0x0001))

#define IP_GetExtensionLen(ucExtHeaderLen)                  (((ucExtHeaderLen) + 1) * 8)

#define IP_IPV6_64BITPREFIX_EQUAL_ZERO(pucIpv6Addr)\
            (((*(pucIpv6Addr)) == 0)\
            && ((*(pucIpv6Addr+1)) == 0)\
            && ((*(pucIpv6Addr+2)) == 0)\
            && ((*(pucIpv6Addr+3)) == 0)\
            && ((*(pucIpv6Addr+4)) == 0)\
            && ((*(pucIpv6Addr+5)) == 0)\
            && ((*(pucIpv6Addr+6)) == 0)\
            && ((*(pucIpv6Addr+7)) == 0))

#define IP_IPV6_IS_LINKLOCAL_ADDR(pucIpv6Addr)\
            (((*(pucIpv6Addr)) == 0xfe)\
            && (((*(pucIpv6Addr+1)) & 0xc0) == 0x80))

#define IP_IPV6_IS_MULTICAST_ADDR(pucIpV6Addr)              (0xff == (*(pucIpV6Addr)))

#define IP_IPV6_EQUAL_ALL_ZERO(pucIpv6Addr)\
            (((*(pucIpv6Addr)) == 0)\
            && ((*(pucIpv6Addr+1)) == 0)\
            && ((*(pucIpv6Addr+2)) == 0)\
            && ((*(pucIpv6Addr+3)) == 0)\
            && ((*(pucIpv6Addr+4)) == 0)\
            && ((*(pucIpv6Addr+5)) == 0)\
            && ((*(pucIpv6Addr+6)) == 0)\
            && ((*(pucIpv6Addr+7)) == 0)\
            && ((*(pucIpv6Addr+8)) == 0)\
            && ((*(pucIpv6Addr+9)) == 0)\
            && ((*(pucIpv6Addr+10)) == 0)\
            && ((*(pucIpv6Addr+11)) == 0)\
            && ((*(pucIpv6Addr+12)) == 0)\
            && ((*(pucIpv6Addr+13)) == 0)\
            && ((*(pucIpv6Addr+14)) == 0)\
            && ((*(pucIpv6Addr+15)) == 0))

#define IP_ProduceSolicitedNodeMulticastIPAddr(pucDstIpv6Addr, pucSrcIpv6Addr)\
    {\
        (*(pucDstIpv6Addr))      = (0xff);\
        (*(pucDstIpv6Addr + 1))  = (0x02);\
        (*(pucDstIpv6Addr + 11)) = (0x01);\
        (*(pucDstIpv6Addr + 12)) = (0xff);\
        (*(pucDstIpv6Addr + 13)) = (*(pucSrcIpv6Addr + 13));\
        (*(pucDstIpv6Addr + 14)) = (*(pucSrcIpv6Addr + 14));\
        (*(pucDstIpv6Addr + 15)) = (*(pucSrcIpv6Addr + 15));\
    }

#define IP_ProduceSolicitedNodeMulticastMacAddr(pucDstMacAddr, pucSrcIpv6Addr)\
    {\
        (*(pucDstMacAddr))     = (0x33);\
        (*(pucDstMacAddr + 1)) = (0x33);\
        (*(pucDstMacAddr + 2)) = (0xff);\
        (*(pucDstMacAddr + 3)) = (*(pucSrcIpv6Addr + 13));\
        (*(pucDstMacAddr + 4)) = (*(pucSrcIpv6Addr + 14));\
        (*(pucDstMacAddr + 5)) = (*(pucSrcIpv6Addr + 15));\
    }

#define IP_ProduceIfaceIdFromMacAddr(pucIpv6Addr, pucMacAddr)\
            {\
                (*(pucIpv6Addr + 8)) = ((*(pucMacAddr)) ^ 0x2);\
                (*(pucIpv6Addr + 9)) = (*(pucMacAddr + 1));\
                (*(pucIpv6Addr + 10)) = (*(pucMacAddr + 2));\
                (*(pucIpv6Addr + 11)) = (0xff);\
                (*(pucIpv6Addr + 12)) = (0xfe);\
                (*(pucIpv6Addr + 13)) = (*(pucMacAddr + 3));\
                (*(pucIpv6Addr + 14)) = (*(pucMacAddr + 4));\
                (*(pucIpv6Addr + 15)) = (*(pucMacAddr + 5));\
            }

#define IP_GetUint16Data(usUint16Data, pucFirstByte)\
            {\
                (usUint16Data) = (*(pucFirstByte)) << IP_BITMOVE_8;\
                (usUint16Data) |= (*((pucFirstByte) + 1));\
            }
/*lint -emacro({701}, IP_GetUint32Data)*/
#define IP_GetUint32Data(ulUint32Data, pucFirstByte)\
            {\
                (ulUint32Data) = (*(pucFirstByte)) << IP_BITMOVE_24;\
                (ulUint32Data) |= (*((pucFirstByte) + 1)) << IP_BITMOVE_16;\
                (ulUint32Data) |= (*((pucFirstByte) + 2)) << IP_BITMOVE_8;\
                (ulUint32Data) |= (*((pucFirstByte) + 3));\
            }

#define IP_SetUint16Data(pucFirstByte, usUint16Data)\
            {\
                (*(pucFirstByte)) = ((usUint16Data) >> IP_BITMOVE_8) & 0xff;\
                (*((pucFirstByte) + 1)) = (usUint16Data) & 0xff;\
            }

#define IP_SetUint32Data(pucFirstByte, ulUint32Data)\
            {\
                (*(pucFirstByte)) = ((ulUint32Data) >> IP_BITMOVE_24) & 0xff;\
                (*((pucFirstByte) + 1)) = ((ulUint32Data) >> IP_BITMOVE_16) & 0xff;\
                (*((pucFirstByte) + 2)) = ((ulUint32Data) >> IP_BITMOVE_8) & 0xff;\
                (*((pucFirstByte) + 3)) = (ulUint32Data) & 0xff;\
            }

/*封装写IP消息头的宏*/
#define ND_IP_WRITE_MSG_HEAD(pstMsg, ulRabmMsgID, ulSendPid, ulReceivePid)\
                    (pstMsg)->ulMsgId   = (ulRabmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = ulSendPid;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = ulReceivePid;


#ifndef IP_RELEASE
#if (VOS_OS_VER != VOS_WIN32)
#define IP_ASSERT(exp) \
    if(!(exp))\
    {\
        vos_assert((VOS_UINT32)THIS_FILE_ID, __LINE__);\
        return;\
    }

#define IP_ASSERT_RTN(exp,ret) \
    if (!(exp)) \
    {\
        vos_assert((VOS_UINT32)THIS_FILE_ID,__LINE__); \
        return (ret); \
    }
#else
/*
#define IP_ASSERT(exp) \
    if(!(exp))\
    {\
        vos_assert(__FILE__, __LINE__);\
        return;\
    }

#define IP_ASSERT_RTN(exp,ret) \
    if (!(exp)) \
    {\
        vos_assert(__FILE__,__LINE__); \
        return (ret); \
    }
*/
#define IP_ASSERT(exp) \
    if(!(exp))\
    {\
        vos_printf("Assert, File: %s, Line:%d\n", __FILE__,__LINE__);\
        return;\
    }

#define IP_ASSERT_RTN(exp,ret) \
    if (!(exp)) \
    {\
        vos_printf("Assert, File: %s, Line:%d\n", __FILE__,__LINE__); \
        return (ret); \
    }

#endif

#else
#define IP_ASSERT(exp)                ((VOS_VOID)0)
#define IP_ASSERT_RTN(exp,ret)        ((VOS_VOID)0)
#endif

#if    VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define    VOS_NTOHL(x)    (x)
#define    VOS_HTONL(x)    (x)
#define    VOS_NTOHS(x)    (x)
#define    VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#endif    /* _BYTE_ORDER==_LITTLE_ENDIAN */

#define IPND_LOG(ModulePID, SubMod, Level, pcString)
#define IPND_LOG1(ModulePID, SubMod, Level, pcString, lPara1)
#define IPND_LOG2(ModulePID, SubMod, Level, pcString, lPara1,lPara2)
#define IPND_LOG3(ModulePID, SubMod, Level, pcString, lPara1,lPara2,lPara3)
#define IPND_LOG4(ModulePID, SubMod, Level, pcString, lPara1,lPara2,lPara3,lPara4)

#define IPND_INFO_LOG(ModuleId, String)
#define IPND_INFO_LOG1(ModuleId, String,Para1)
#define IPND_INFO_LOG2(ModuleId, String,Para1,Para2)
#define IPND_INFO_LOG3(ModuleId, String,Para1,Para2,Para3)
#define IPND_INFO_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

#define IPND_WARNING_LOG(ModuleId, String)
#define IPND_WARNING_LOG1(ModuleId, String,Para1)
#define IPND_WARNING_LOG2(ModuleId, String,Para1,Para2)
#define IPND_WARNING_LOG3(ModuleId, String,Para1,Para2,Para3)
#define IPND_WARNING_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)

#define IPND_ERROR_LOG(ModuleId, String)
#define IPND_ERROR_LOG1(ModuleId, String,Para1)
#define IPND_ERROR_LOG2(ModuleId, String,Para1,Para2)
#define IPND_ERROR_LOG3(ModuleId, String,Para1,Para2,Para3)
#define IPND_ERROR_LOG4(ModuleId, String,Para1,Para2,Para3,Para4)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 结构名    : IP_ERR_ENUM
 结构说明  : IP模块错误码
 *****************************************************************************/
enum    IP_ERR_ENUM
{
    IP_SUCC                         = 0x00000000,
    IP_FAIL                                     ,

    IP_MSG_DISCARD                              ,       /* 丢弃该消息，即该消息不被该当前状态处理 */
    IP_MSG_HANDLED                              ,       /* 该消息已被当前状态处理 */

    IP_ERR_BUTT
};
typedef VOS_UINT32  IP_ERR_ENUM_UINT32;

/*****************************************************************************
 枚举名    : IP_BOOL_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : PS统一布尔类型枚举定义
*****************************************************************************/
enum IP_BOOL_ENUM
{
    IP_FALSE                            = 0,
    IP_TRUE                             = 1,
    IP_BOOL_BUTT
};
typedef VOS_UINT8   IP_BOOL_ENUM_UINT8;

/*****************************************************************************
 枚举名    : IP_ICMPV6_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 扩展头类型枚举
*****************************************************************************/
enum IP_ICMPV6_TYPE_ENUM
{
    IP_ICMPV6_PACKET_TOO_BIG            = 2,
    IP_ICMPV6_TYPE_ECHOREQUEST          = 128,
    IP_ICMPV6_TYPE_ECHOREPLY            = 129,
    IP_ICMPV6_TYPE_RS                   = 133,
    IP_ICMPV6_TYPE_RA                   = 134,
    IP_ICMPV6_TYPE_NS                   = 135,
    IP_ICMPV6_TYPE_NA                   = 136,
    IP_ICMPV6_TYPE_REDIRECT             = 137,

    IP_ICMPV6_TYPE_BUTT
};
typedef VOS_UINT32 IP_ICMPV6_TYPE_ENUM_UINT32;

enum IP_ICMPV6_OPT_TYPE_ENUM
{
    IP_ICMPV6_OPT_SRC_LINK_LAYER_ADDR                   = 1,
    IP_ICMPV6_OPT_TGT_LINK_LAYER_ADDR                   = 2,
    IP_ICMPV6_OPT_PREFIX_INFO                           = 3,
    IP_ICMPV6_OPT_REDIRECT_HEADER                       = 4,
    IP_ICMPV6_OPT_MTU                                   = 5,

    IP_ICMPV6_OPT_TYPE_BUTT
};
typedef VOS_UINT32 IP_ICMPV6_OPT_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : IP_EXTENSION_HEADER_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 扩展头类型枚举
*****************************************************************************/
enum IP_EXTENSION_HEADER_TYPE_ENUM
{
   IP_EXTENSION_HEADER_TYPE_HOPBYHOP    = 0x0,
   IP_EXTENSION_HEADER_TYPE_ROUTING     = 0x2b,
   IP_EXTENSION_HEADER_TYPE_FRAGMENT    = 0x2c,
   IP_EXTENSION_HEADER_TYPE_ESP         = 0x32,
   IP_EXTENSION_HEADER_TYPE_AH          = 0x33,
   IP_EXTENSION_HEADER_TYPE_DESTINATION = 0x3c,

   IP_EXTENSION_HEADER_TYPE_BUTT
};
typedef VOS_UINT32 IP_EXTENSION_HEADER_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : ND_IP_IPV6_PREFIX_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ND_IP_IPV6_PREFIX_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitL          :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ulBitA          :1;
    VOS_UINT32                          ulBitPrefixLen  :8;
    VOS_UINT32                          ulBitRsv        :22;

    VOS_UINT32                          ulValidLifeTime;
    VOS_UINT32                          ulPreferredLifeTime;
    VOS_UINT8                           aucPrefix[IP_IPV6_ADDR_LEN];
}ND_IP_IPV6_PREFIX_STRU;

/*****************************************************************************
 结构名    : ND_IP_IPV6_DNS_SER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS_IP_IPV6_DNS_SER_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDnsSerNum;        /*DNS服务器个数*/
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucPriDnsServer[IP_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDnsServer[IP_IPV6_ADDR_LEN];
}ND_IP_IPV6_DNS_SER_STRU;

/*****************************************************************************
 结构名    : ND_IP_IPV6_SIP_SER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : NAS_IP_IPV6_SIP_SER_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSipSerNum;        /*SIP服务器个数*/
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           aucPriSipServer[IP_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecSipServer[IP_IPV6_ADDR_LEN];
}ND_IP_IPV6_SIP_SER_STRU;

/*****************************************************************************
 结构名    : ESM_IP_IPV6_NW_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ESM_IP_IPV6_NW_PARA_STRU的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBitOpMtu              :1;
    VOS_UINT32                          ulBitRsv                :31;

    VOS_UINT8                           ucCurHopLimit;
    VOS_UINT8                           ucReserved[3];

    VOS_UINT8                           aucInterfaceId[ND_IP_IPV6_IFID_LENGTH];

    VOS_UINT32                          ulMtu;
    VOS_UINT32                          ulPrefixNum;
    ND_IP_IPV6_PREFIX_STRU              astPrefixList[ND_IP_MAX_PREFIX_NUM_IN_RA];

    ND_IP_IPV6_DNS_SER_STRU            stDnsSer;
    ND_IP_IPV6_SIP_SER_STRU            stSipSer;                               /* SIP服务器 */
}ESM_IP_IPV6_NW_PARA_STRU;

typedef struct
{
    VOS_UINT32                          ulSendMsgSize;         /* 消息的总长度 */
    VOS_UINT32                          ulResv;                /*为了同64位操作系统兼容，指针放在在8字节对齐位置*/
    VOS_UINT8                          *pucSendMsg;            /* 消息的首地址 */
}IP_SND_MSG_STRU;

typedef struct
{
    VOS_UINT32                          ucBitOpSrcLinkLayerAddr :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitRsv                :31;

    VOS_UINT8                           aucSrcLinkLayerAddr[IP_MAC_ADDR_LEN];
    VOS_UINT8                           aucReserve1[2];
}IP_ND_MSG_RS_STRU;

typedef ND_IP_IPV6_PREFIX_STRU IP_IPV6_PREFIX_STRU;

typedef struct
{
    VOS_UINT32                          ulBitOpSrcLinkLayerAddr :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ulBitOpMtu              :1;
    VOS_UINT32                          ulBitRsv1               :30;

    VOS_UINT32                          ulBitCurHopLimit        :8;
    VOS_UINT32                          ulBitM                  :1;
    VOS_UINT32                          ulBitO                  :1;
    VOS_UINT32                          ulBitRsv2               :6;
    VOS_UINT32                          ulBitRouterLifeTime     :16;
    VOS_UINT32                          ulReachableTimer;
    VOS_UINT32                          ulReTransTime;

    VOS_UINT8                           aucSrcLinkLayerAddr[IP_MAC_ADDR_LEN];
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulMtu;
    VOS_UINT32                          ulPrefixNum;
    IP_IPV6_PREFIX_STRU                 astPrefixList[IP_MAX_PREFIX_NUM_IN_RA];
}IP_ND_MSG_RA_STRU;

typedef struct
{
    VOS_UINT32                          ucBitOpSrcLinkLayerAddr :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitRsv                :31;

    VOS_UINT8                           aucTargetAddr[IP_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSrcLinkLayerAddr[IP_MAC_ADDR_LEN];
    VOS_UINT8                           aucReserve1[2];
}IP_ND_MSG_NS_STRU;

typedef struct
{
    VOS_UINT32                          ucBitOpTargetLinkLayerAddr :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          ucBitRsv1               :31;

    VOS_UINT32                          ucBitR                  :1;
    VOS_UINT32                          ucBitS                  :1;
    VOS_UINT32                          ucBitO                  :1;
    VOS_UINT32                          ucBitRsv2               :29;
    VOS_UINT8                           aucTargetAddr[IP_IPV6_ADDR_LEN];
    VOS_UINT8                           aucTargetLinkLayerAddr[IP_MAC_ADDR_LEN];
    VOS_UINT8                           aucReserve1[2];
}IP_ND_MSG_NA_STRU;

typedef union
{
    IP_ND_MSG_RS_STRU                   stRs;
    IP_ND_MSG_RA_STRU                   stRa;
    IP_ND_MSG_NS_STRU                   stNs;
    IP_ND_MSG_NA_STRU                   stNa;
}IP_ND_MSG_STRU_UNION;

typedef struct
{
    VOS_UINT8                           ucType;
    VOS_UINT8                           ucCode;
    VOS_UINT8                           ucReserved1[2];

    VOS_UINT8                           aucSrcIp[IP_IPV6_ADDR_LEN];
    VOS_UINT8                           aucDesIp[IP_IPV6_ADDR_LEN];

    IP_ND_MSG_STRU_UNION                uNdMsgStru;
}IP_ND_MSG_STRU;

/*Moved by huibo begin*/
/*****************************************************************************
 结构名    : IPv6_PSEDUOHEADER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6伪首部
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucIPSrc[IP_IPV6_ADDR_LEN];             /*源IP地址*/
    VOS_UINT8                           aucIPDes[IP_IPV6_ADDR_LEN];             /*目的IP地址*/
    VOS_UINT32                          ulUpperLength;                          /*整个UPPER-LAYER长度，不包括伪首部长度*/
    VOS_UINT8                           ucZero[3];                              /*全部为0*/
    VOS_UINT8                           ucNextHead;
}IPV6_PSEDUOHEADER_STRU;

/*****************************************************************************
 结构名    : NDIS_IP6_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6地址
*****************************************************************************/
typedef struct
{
    union
    {
        VOS_UINT8                       aucAddr[16];
        VOS_UINT16                      ausAddr[8];
        VOS_UINT32                      aulAddr[4];
    } in6;
}NDIS_IP6_ADDR_STRU;

/*****************************************************************************
 结构名    : NDIS_IP6_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6首部
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulVerClassFlow;     /* 4 bit version, 8 bit class, 20 bit flow. */
    VOS_UINT16                          usPayLoadlen;       /* Payload length. */
    VOS_UINT8                           ucNextHeader;       /* Next Header. */
    VOS_UINT8                           ucHLim;             /* Hop limit. */
    NDIS_IP6_ADDR_STRU                  stSrc;              /* IPv6 source address. */
    NDIS_IP6_ADDR_STRU                  stDst;              /* IPv6 destination address. */
}NDIS_IP6_HDR_STRU;

/*****************************************************************************
 结构名    : UDP_HEAD_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : UDP头部结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16  usSrcPort;              /*源端口*/
    VOS_UINT16  usDstPort;              /*目的端口*/
    VOS_UINT16  usLen;                  /*UDP包长度*/
    VOS_UINT16  usCheck;                /*UDP校验和*/
}UDP_HEAD_ST;

/*****************************************************************************
 结构名    : UDP_HEAD_ST
 协议表格  :
 ASN.1描述 :
 结构说明  : UDP头部结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usOptionCode;   /* OPTION_DNS_SERVERS (23) */
    VOS_UINT16                          usOptionLen;    /* Length of the list of DNS recursive name
                                                        servers in octets; must be a multiple of 16 */
    NDIS_IP6_ADDR_STRU                  astIpv6DNS[IP_IPV6_MAX_DNS_NUM];  /* DNS-recursive-name-server (IPv6 address) */
}IPV6_DHCP_DNS_OPTION_STRU;

/*****************************************************************************
 结构名    : IPV6_PKT_DHCP_OPT_HDR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UDP头部结构
*****************************************************************************/
/* DHCP Options */
typedef struct
{
    VOS_UINT16                          usDhcpOptCode;
    VOS_UINT16                          usDhcpOptLen;
    VOS_UINT8                           aucDhcpOptData[4];
}IPV6_PKT_DHCP_OPT_HDR_STRU;

/* DHCP DUID-LL Options */
typedef struct
{
    VOS_UINT16                          usDhcpDuidType;
    VOS_UINT16                          usDhcpDuidHWType;
    VOS_UINT8                           aucLinkLayerAddr[IP_IPV6_DHCP_OPT_LINKADDR_SIZE];
}IPV6_PKT_DHCP_DUID_LL_OPT_STRU;

typedef struct
{
    VOS_UINT8                           ucNdOptType;
    VOS_UINT8                           ucNdOptLen;
    VOS_UINT8                           aucNdOptData[1];
}NDIS_PKT_ND_OPT_HDR_STRU;

/*Moved by huibo end*/

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT8 g_aucNdAllNodesMulticaseAddr[];
extern VOS_UINT8 g_aucNdAllRoutersMulticaseAddr[];
extern VOS_UINT8 g_aucNdAllNodesMacAddr[];
extern VOS_UINT8 g_aucNdAllRoutersMacAddr[];


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/*Moved by huibo begin*/
extern VOS_VOID IP_BuildLinkLocalAddr
(
    VOS_UINT8 *pucLinkLocalAddr,
    const VOS_UINT8 *pucIfId
);

extern IP_BOOL_ENUM_UINT8 IP_IsValidRAPacket
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                         ulTypeOffset
);

extern VOS_VOID IP_BuildIPv6Header
(
    VOS_UINT8               *pucIpv6,
    IPV6_PSEDUOHEADER_STRU  *pstPseduoHeader,
    const VOS_UINT8         *pucInterfaceId,
    VOS_UINT32               ulUpperLength
);
extern VOS_VOID IP_ND_FormIPv6HeaderMsg
(
    const VOS_UINT8                    *aucSrcIPAddr,
    const VOS_UINT8                    *aucDstIPAddr,
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                          *pucData,
    VOS_UINT8                           ucType
);
extern VOS_UINT16 IPv6_Checksum
(
    const VOS_VOID          *pucPseduoHeader,
    const VOS_UINT8         *pucData,
    VOS_UINT32              ulLen
);

extern IP_BOOL_ENUM_UINT8 IP_IsValidNdMsg
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen,
    VOS_UINT32                         *pulTypeOffset
);

extern IP_ERR_ENUM_UINT32 IP_BuildIcmpv6Checksum
(
    VOS_UINT8                          *pucIpMsg,
    VOS_UINT32                          ulTypeOffset
);
/*Moved by huibo end*/
extern VOS_UINT32 ND_CheckEpsIdValid(VOS_UINT8 ucExEpsId);
extern IP_ERR_ENUM_UINT32 IP_GetIpv6UpLayerProtocol
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT16                          usPayLoad,
    VOS_UINT8                          *pucNextHeader,
    VOS_UINT32                         *pulDecodedLen
);
extern IP_ERR_ENUM_UINT32 IP_AffirmNdParam
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulTypeOffset
);

extern IP_BOOL_ENUM_UINT8 IP_IsIcmpv6Packet
(
    const VOS_UINT8                    *pucIpMsg,
    VOS_UINT32                          ulIpMsgLen,
    VOS_UINT32                         *pulDecodedLen
);
extern VOS_UINT32 IP_ConstructICMPv6PseudoHeader
(
    const VOS_UINT8                   *pucMsgData,
    VOS_UINT32                  ulTypeOffset,
    IPV6_PSEDUOHEADER_STRU      *pstPseduoHeader
);
extern VOS_UINT32  IP_Unit16Sum(const VOS_UINT8 *pucData, VOS_UINT32 ulLen);

extern IP_ERR_ENUM_UINT32 IP_VerifyICMPv6
(
    const VOS_UINT8        *pucIpMsg,
    VOS_UINT32             ulTypeOffset
);
extern VOS_UINT16 TTF_NDIS_Ipv6_CalcCheckSum
(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen,
    const NDIS_IP6_ADDR_STRU           *pstIp6SrcAddr,
    const NDIS_IP6_ADDR_STRU           *pstIp6DstAddr,
    VOS_UINT32                          ulProto
);
extern VOS_UINT32 TTF_NDIS_Ipv6GetDhcpOption
(
    IPV6_PKT_DHCP_OPT_HDR_STRU             *pFirstOpt,
    VOS_UINT16                              usTotOptLen,
    VOS_UINT16                              usNdOptCode,
    IPV6_PKT_DHCP_OPT_HDR_STRU            **pOpt,
    VOS_INT32                               lNumber
);
extern VOS_UINT32 TTF_NDIS_InputUDPHead
(
    VOS_UINT8                          *pBuf,
    VOS_UINT16                          usSrcPort,
    VOS_UINT16                          usDstPort,
    VOS_UINT16                          usUdpDataLen
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


#endif /* end of IpComm.h */
