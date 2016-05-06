/******************************************************************************

                  版权所有 (C), 2013-2023, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Cttf_ppp_trace_info_pif.h
  版 本 号   : 初稿
  作    者   : d00314740
  生成日期   : 2015年06月19日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2015年06月19日
    作    者   : d00314740
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CTTF_PPP_TRACE_INFO_PIF_H__
#define __CTTF_PPP_TRACE_INFO_PIF_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : PS_DATA_FLOW_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : Data flow type
*****************************************************************************/
enum PS_DATA_FLOW_TYPE_ENUM
{
    PS_DATA_FLOW_TYPE_PPP_FRAME     = 0,
    PS_DATA_FLOW_TYPE_IPV4_PACKET,
    PS_DATA_FLOW_TYPE_IPV6_PACKET,
    PS_DATA_FLOW_TYPE_BUTT
};
typedef VOS_UINT8 PS_DATA_FLOW_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : HIGH_LAYER_PROTOCOL_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : High layer protocol type, 按照EVDO协议high layer定义
*****************************************************************************/
enum HIGH_LAYER_PROTOCOL_TYPE_ENUM
{
    HIGH_LAYER_TCP_TYPE                 = 0,
    HIGH_LAYER_UDP_TYPE,
    HIGH_LAYER_ICMP_TYPE,
    HIGH_LAYER_ICMPV6_TYPE,
    HIGH_LAYER_IPV4_OTHER_PROTOCOL_TYPE,
    HIGH_LAYER_IPV6_OTHER_PROTOCOL_TYPE,
    HIGH_LAYER_PROTOCOL_TYPE_BUTT
};
typedef VOS_UINT8 HIGH_LAYER_PROTOCOL_TYPE_ENUM_UINT8;

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
 结构名    : PS_DATA_HTTP_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 待详细定义，缓解低速率和拥塞下打不开网页
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[4];
} PS_DATA_HTTP_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_DNS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 待详细定义，缓解低速率和拥塞下打不开网页
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve1[4];
    /* flag类型: 请求 or 应答 */
} PS_DATA_DNS_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_TCP_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TCP_TYPE的扩展信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpId;   /* ip header identification */
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usDstPort;
    VOS_UINT32                          ulAckSeq;
    PS_BOOL_ENUM_UINT8                  enIncludeHttp;
    VOS_UINT8                           aucReserve1[3];
    PS_DATA_HTTP_INFO_STRU              stHttp;
} PS_DATA_TCP_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_UDP_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : UDP_TYPE的扩展信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpId;   /* ip header identification */
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usDstPort;
    PS_BOOL_ENUM_UINT8                  enIncludeDns;
    VOS_UINT8                           aucReserve1[3];
    PS_DATA_DNS_INFO_STRU               stDns;
} PS_DATA_UDP_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_ICMPV4_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ICMPV4_TYPE的扩展信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpId;     /* ip header identification */
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT8                           ucType;     /* icmp header type */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usIcmpId;   /* icmp header identification */
    VOS_UINT16                          usIcmpSn;   /* icmp header sequence number */
} PS_DATA_ICMPV4_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_ICMPV6_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ICMPV6_TYPE的扩展信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT8                           ucType;   /* icmp header type */
    VOS_UINT8                           aucReserve1[1];
} PS_DATA_ICMPV6_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_IPV4_OTHER_PROTOCOL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4其他类型的扩展信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usIpId;   /* ip header identification */
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
} PS_DATA_IPV4_OTHER_PROTOCOL_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_IPV6_OTHER_PROTOCOL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6其他类型的扩展信息
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDataLen;  /* ip packet byte len */
    VOS_UINT8                           aucReserve1[2];
} PS_DATA_IPV6_OTHER_PROTOCOL_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_HIGH_LAYER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上层各类别数据的详细信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulChoice;

#define PS_DATA_HIGH_LAYER_TCP_TYPE                    (6)
#define PS_DATA_HIGH_LAYER_UDP_TYPE                    (17)
#define PS_DATA_HIGH_LAYER_ICMP_TYPE                   (1)
#define PS_DATA_HIGH_LAYER_ICMPV6_TYPE                 (58)
#define PS_DATA_HIGH_LAYER_IPV4_OTHER_PROTOCOL_TYPE    (254)
#define PS_DATA_HIGH_LAYER_IPV6_OTHER_PROTOCOL_TYPE    (255)

    union
    {
         PS_DATA_TCP_INFO_STRU                  stTcpInfo;
         PS_DATA_UDP_INFO_STRU                  stUdpInfo;
         PS_DATA_ICMPV4_INFO_STRU               stIcmpv4Info;
         PS_DATA_ICMPV6_INFO_STRU               stIcmpv6Info;
         PS_DATA_IPV4_OTHER_PROTOCOL_INFO_STRU  stIpv4OtherTypeInfo;
         PS_DATA_IPV6_OTHER_PROTOCOL_INFO_STRU  stIpv6OtherTypeInfo;
    } u;
} PS_DATA_HIGH_LAYER_INFO_STRU;

/*****************************************************************************
 结构名    : PS_DATA_EXT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上层各类别数据的扩展信息
*****************************************************************************/
typedef struct
{
    PS_DATA_FLOW_TYPE_ENUM_UINT8        enDataType;         /* 为方便工具进行解析，同时跟EVDO协议对接 */
    VOS_UINT8                           ucPri;              /* 优先级 */
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT32                          ulBirthTime;        /* 生命起始tick */
    PS_DATA_HIGH_LAYER_INFO_STRU        stHighLayerInfo;    /* 不论是PPP帧，还是IP报文，都带有这个结构信息 */
    VOS_UINT8                           aucUserDef[4];      /* 用户自定义扩展空间 */
    VOS_UINT16                          usStartSN;
    VOS_UINT16                          usEndSN;
} PS_DATA_EXT_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/



/*****************************************************************************
  9 全局变量声明
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

#endif /* end of Cttf_ppp_trace_info_pif.h */






