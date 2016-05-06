

#ifndef __CDSADSINTERFACE_H__
#define __CDSADSINTERFACE_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* !!!!!!!!!!!暂时定义，最终的值由北京确定 */
#define ADS_CDS_MSG_HDR                (0x00)
#define CDS_ADS_MSG_HDR                (0x10)

#define CDS_ADS_ALL_RABID               (0xFF)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
枚举名    : CDS_ADS_MSG_ID_ENUM
结构说明  : CDS和ADS的之间的消息

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义CDS和ADS之间的消息
*****************************************************************************/
enum CDS_ADS_MSG_ID_ENUM
{
    ID_CDS_ADS_STOP_SENDDATA_IND     = CDS_ADS_MSG_HDR + 0x01,                  /* CDS->ADS STOP SENDDATA IND */
    ID_CDS_ADS_STOP_SENDDATA_RSP     = ADS_CDS_MSG_HDR + 0x01,                  /* ADS->CDS STOP SENDDATA RSP */
    ID_CDS_ADS_START_SENDDATA_IND    = CDS_ADS_MSG_HDR + 0x02,                  /* CDS->ADS START SENDDATA IND */
    ID_CDS_ADS_START_SENDDATA_RSP    = ADS_CDS_MSG_HDR + 0x02,                  /* ADS->CDS START SENDDATA RSP */
    ID_CDS_ADS_CLEAR_DATA_IND        = CDS_ADS_MSG_HDR + 0x03,                  /* CDS->ADS CLEAR DATA IND */
    ID_CDS_ADS_CLEAR_DATA_RSP        = ADS_CDS_MSG_HDR + 0x03,                  /* ADS->CDS CLEAR DATA RSP */
    ID_CDS_ADS_IP_PACKET_IND         = CDS_ADS_MSG_HDR + 0x04,                  /* CDS->ADS IP PACKET IND */
    ID_CDS_ADS_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  CDS_ADS_MSG_ID_ENUM_UINT32;

/*****************************************************************************
枚举名    : CDS_ADS_IP_PACKET_TYPE_ENUM_UINT8
结构说明  : CDS与ADS的IP消息包类型定义

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义CDS与ADS的消息包类型
*****************************************************************************/
enum CDS_ADS_IP_PACKET_TYPE_ENUM
{
    CDS_ADS_IP_PACKET_TYPE_DHCP_SERVERV4   = 0x00,
    CDS_ADS_IP_PACKET_TYPE_ND_SERVERDHCPV6 = 0x01,
    CDS_ADS_IP_PACKET_TYPE_ICMPV6          = 0x02,
    CDS_ADS_IP_PACKET_TYPE_LINK_FE80       = 0x03,
    CDS_ADS_IP_PACKET_TYPE_LINK_FF         = 0x04,
    CDS_ADS_IP_PACKET_TYPE_BUTT
};
typedef VOS_UINT8 CDS_ADS_IP_PACKET_TYPE_ENUM_UINT8;

/*****************************************************************************
枚举名    : CDS_ADS_DL_IPF_BEARER_ID_ENUM
结构说明  : CDS与ADS下行的IPF Bearer Id定义

  1.日    期   : 2011年12月16日
    作    者   : 鲁琳/l60609
    修改内容   : CDS与ADS下行的IPF Bearer Id定义
*****************************************************************************/
enum CDS_ADS_DL_IPF_BEARER_ID_ENUM
{
    CDS_ADS_DL_IPF_BEARER_ID_RSV0     = 0,                                      /* 0~4保留 */
    CDS_ADS_DL_IPF_BEARER_ID_EPSBID5  = 5,                                      /* 5~15 EPS Bearer ID*/
    CDS_ADS_DL_IPF_BEARER_ID_EPSBID15 = 15,
    CDS_ADS_DL_IPF_BEARER_ID_DHCPV4   = 16,                                     /* 下行DHCP */
    CDS_ADS_DL_IPF_BEARER_ID_DHCPV6   = 17,                                     /* 下行DHCPv6*/
    CDS_ADS_DL_IPF_BEARER_ID_ICMPV4   = 18,                                     /* 下行ICMP */
    CDS_ADS_DL_IPF_BEARER_ID_ICMPV6   = 19,                                     /* 下行ICMPv6 */
    CDS_ADS_DL_IPF_BEARER_ID_LL_FE80  = 20,
    CDS_ADS_DL_IPF_BEARER_ID_LL_FF    = 21,
    CDS_ADS_DL_IPF_BEARER_ID_INVALID  = 63                                      /* 不匹配任何Filter，0x3F*/
};
typedef VOS_UINT32 CDS_ADS_DL_IPF_BEARER_ID_ENUM_UINT32;

/*****************************************************************************
枚举名    : ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8
结构说明  : ADS给CDS的数据包类型

  1.日    期   : 2013年05月22日
    作    者   : 范晶/00179208
    修改内容   : 定义ADS与CDS的数据包类型
*****************************************************************************/
enum ADS_CDS_PKT_TYPE_ENUM
{
    ADS_CDS_IPF_PKT_TYPE_IP   = 0x00,                                           /* IP类型 */
    ADS_CDS_IPF_PKT_TYPE_PPP  = 0x01,                                           /* PPP类型 */
    ADS_CDS_IPF_PKT_TYPE_BUTT
};
typedef VOS_UINT8 ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8;

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
结构名    : CDS_ADS_STOP_SENDDATA_IND_STRU
结构说明  : CDS指示ADS停止数据发送结构

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义CDS指示ADS停止数据发送的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* 消息ID */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucReserved[1];

} CDS_ADS_STOP_SENDDATA_IND_STRU;

/*****************************************************************************
结构名    : CDS_ADS_STOP_SENDDATA_RSP_STRU
结构说明  : ADS回复CDS停止数据发送结构

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS回复CDS停止数据发送的结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* 消息ID */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucReserved[1];
} CDS_ADS_STOP_SENDDATA_RSP_STRU;

/*****************************************************************************
结构名    : CDS_ADS_START_SENDDATA_IND_STRU
结构说明  : CDS指示ADS继续数据发送结构

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义CDS指示ADS继续数据发送结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* 消息ID */
    MODEM_ID_ENUM_UINT16                enModemId ;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucReserved[1];
} CDS_ADS_START_SENDDATA_IND_STRU;

/*****************************************************************************
结构名    : CDS_ADS_START_SENDDATA_RSP_STRU
结构说明  : ADS回复CDS恢复数据发送结构

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS回复CDS恢复数据发送结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* 消息ID */
    MODEM_ID_ENUM_UINT16                enModemId ;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucReserved[1];
} CDS_ADS_START_SENDDATA_RSP_STRU;

/*****************************************************************************
结构名    : CDS_ADS_CLEAR_DATA_IND_STRU
结构说明  : CDS指示ADS清空缓存数据结构

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义CDS指示ADS清空缓存数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* 消息ID */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucRsv[1];                              /* 保留*/
} CDS_ADS_CLEAR_DATA_IND_STRU;

/*****************************************************************************
结构名    : CDS_ADS_CLEAR_DATA_RSP_STRU
结构说明  : ADS回复CDS清空缓存数据结构

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义ADS回复CDS清空缓存数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* 消息ID */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* Rab Id*/
    VOS_UINT8                           aucRsv[1];                              /* 保留*/
} CDS_ADS_CLEAR_DATA_RSP_STRU;

/*****************************************************************************
 结构名    : CDS_ADS_DATA_IND_STRU
 结构说明  : CDS与ADS之间的数据包消息结构

  1.日    期   : 2011年12月6日
    作    者   : 鲁琳/l60609
    修改内容   : 定义CDS与ADS之间的数据包消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    CDS_ADS_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           ucRabId;                                /* RAB标识，取值范围:[5,15] */
    CDS_ADS_IP_PACKET_TYPE_ENUM_UINT8   enIpPacketType;                         /* IP PACKET TYPE*/
    VOS_UINT16                          usLen;                                  /* Zc Len*/
    VOS_UINT8                           aucRsv[2];                              /* 保留*/
    VOS_UINT8                           aucData[4];                             /* 数据包 */
} CDS_ADS_DATA_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/






#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

