
#ifndef __IMSA_RNIC_INTERFACE_H__
#define __IMSA_RNIC_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "RnicInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*================================================*/
/* 数值宏定义 */
/*================================================*/
#define   IMSA_RNIC_IPV4_ADDR_LENGTH          (4)     /* IPV4地址长度，单位字节 */
#define   IMSA_RNIC_IPV6_ADDR_LENGTH          (16)    /* IPV6地址长度, 单位字节 */

#define   IMSA_RNIC_MAX_DNS_SERVER_NUM        (4)     /* 最多可设置4个DNS服务器，一主三辅 */

/*================================================*/
/* 功能函数宏定义 */
/*================================================*/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

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
 枚举名    : IMSA_RNIC_MSG_ID_ENUM
 枚举说明  : IMSA与RNIC的消息定义
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 创建
*****************************************************************************/
enum IMSA_RNIC_MSG_ID_ENUM
{
    /* IMSA发给RNIC的消息枚举 */
    ID_IMSA_RNIC_PDN_ACT_IND        = 0x0001,   /* PDN激活指示 */               /* _H2ASN_MsgChoice IMSA_RNIC_PDN_ACT_IND_STRU */
    ID_IMSA_RNIC_PDN_DEACT_IND      = 0x0002,   /* PDN去激活指示 */             /* _H2ASN_MsgChoice IMSA_RNIC_PDN_DEACT_IND_STRU */

    /* RNIC发给IMSA的消息枚举 */


    ID_IMSA_RNIC_MSG_ID_ENUM_BUTT

};
typedef VOS_UINT32 IMSA_RNIC_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : IMSA_RNIC_IPV4_PDN_INFO_STRU
 结构说明  : IPV4 配置信息结构
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDnsPrim         :1;                     /* 外部模块填写，指示aucDnsPrimAddr是否需要配置 */
    VOS_UINT32                          bitOpDnsSec          :1;                     /* 外部模块填写，指示aucDnsSecAddr是否需要配置 */
    VOS_UINT32                          bitOpSpare           :30;

    VOS_UINT8                           aucIpV4Addr[IMSA_RNIC_IPV4_ADDR_LENGTH];       /* IP地址 */
    VOS_UINT8                           aucDnsPrimAddr[IMSA_RNIC_IPV4_ADDR_LENGTH];    /* 主DNS服务器IP */
    VOS_UINT8                           aucDnsSecAddr[IMSA_RNIC_IPV4_ADDR_LENGTH];     /* 辅DNS服务器IP */
}IMSA_RNIC_IPV4_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : IMSA_RNIC_IPV6_PDN_INFO_STRU
 结构说明  : IPV6 配置信息结构
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDnsPrim         :1;                     /* 外部模块填写，指示aucDnsPrimAddr是否需要配置 */
    VOS_UINT32                          bitOpDnsSec          :1;                     /* 外部模块填写，指示aucDnsSecAddr是否需要配置 */
    VOS_UINT32                          bitOpSpare           :30;

    VOS_UINT32                          ulBitPrefixLen;                              /* IPV6前缀长度,单位为bit */
    VOS_UINT8                           aucIpV6Addr[IMSA_RNIC_IPV6_ADDR_LENGTH];       /* IP地址 */
    VOS_UINT8                           aucDnsPrimAddr[IMSA_RNIC_IPV6_ADDR_LENGTH];    /* 主DNS服务器IP */
    VOS_UINT8                           aucDnsSecAddr[IMSA_RNIC_IPV6_ADDR_LENGTH];     /* 辅DNS服务器IP */
}IMSA_RNIC_IPV6_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : IMSA_RNIC_SOCK_PORT_INFO_STRU
 结构说明  : 端口范围配置信息结构
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSockMinPort;      /* socket 端口范围下限 */
    VOS_UINT16                          usSockMaxPort;      /* socket 端口范围上限 */
}IMSA_RNIC_SOCK_PORT_INFO_STRU;


/*****************************************************************************
 结构名    : IMSA_RNIC_PDN_INFO_CONFIG_STRU
 结构说明  : IMSA给RNIC虚拟网卡的PDN配置信息
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo : 1;
    VOS_UINT32                          bitOpIpv6PdnInfo : 1;
    VOS_UINT32                          bitOpSockPortInfo: 1;
    VOS_UINT32                          bitOpSpare       : 29;

    MODEM_ID_ENUM_UINT16                enModemId;                  /* 当前Modem号 */
    VOS_UINT8                           ucRabId;                    /* 承载号，取值范围[5,15] */
    VOS_UINT8                           ucReserved[1];              /* 消息结构体对齐*/

    IMSA_RNIC_IPV4_PDN_INFO_STRU        stIpv4PdnInfo;
    IMSA_RNIC_IPV6_PDN_INFO_STRU        stIpv6PdnInfo;
    IMSA_RNIC_SOCK_PORT_INFO_STRU       stSockPortInfo;
}IMSA_RNIC_PDN_INFO_CONFIG_STRU;

/*****************************************************************************
 结构名    : IMSA_RNIC_PDN_ACT_IND_STRU
 结构说明  : IMSA给RNIC的PDN激活指示
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* 消息头 */    /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                    /* 消息类型 */  /* _H2ASN_Skip */
    IMSA_RNIC_PDN_INFO_CONFIG_STRU      stPdnInfo;
}IMSA_RNIC_PDN_ACT_IND_STRU;

/*****************************************************************************
 结构名    : IMSA_RNIC_PDN_DEACT_IND_STRU
 结构说明  : IMSA给RNIC的PDN去激活指示
 1.日    期   : 2014年07月31日
   作    者   : f00179208
   修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /* 消息头 */    /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                    /* 消息类型 */  /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;                  /* 当前Modem号 */
    VOS_UINT8                           ucRabId;                    /* RAB标识，取值范围:[5,15] */
    VOS_UINT8                           ucReserved[1];              /* 消息结构体对齐*/
}IMSA_RNIC_PDN_DEACT_IND_STRU;

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
    IMSA_RNIC_MSG_ID_ENUM_UINT32        enMsgId;            /* _H2ASN_MsgChoice_Export IMSA_RNIC_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_RNIC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} IMSA_RNIC_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    IMSA_RNIC_INTERFACE_MSG_DATA          stMsgData;
} ImsaRnicInterface_MSG;

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

#endif /* ImsaRnicInterface.h */

