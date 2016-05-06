/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ImsNicInterface.h
  版 本 号   : 初稿
  作    者   : caikai
  生成日期   : 2013年7月16日
  最近修改   :
  功能描述   : IMS虚拟网卡提供的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月16日
    作    者   : caikai
    修改内容   : 创建文件

******************************************************************************/

#ifndef __IMSNICINTERFACE_H__
#define __IMSNICINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"

#if( FEATURE_ON == FEATURE_IMS )
#include  "PsTypeDef.h"


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define   IMS_NIC_IPV4_ADDR_LENGTH          (4)     /* IPV4地址长度，单位字节 */
#define   IMS_NIC_IPV6_ADDR_LENGTH          (16)    /* IPV6地址长度, 单位字节 */

#if ((VOS_OS_VER == VOS_RTOSCK) || ((VOS_OS_VER == VOS_WIN32) && (VOS_PC_TEST == VOS_RTOSCK)))
#define   IMS_NIC_MAX_DNS_SERVER_NUM        (6)     /* VISP中最多可设置6个DNS服务器，一主三辅 */
#else
#define   IMS_NIC_MAX_DNS_SERVER_NUM        (4)     /* Interpeak中最多可设置4个DNS服务器，一主三辅 */
#endif

//#define   IMS_NIC_DEBUG

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 返回值编号 */
enum IMS_NIC_ERROR_CODE_ENUM
{
     IMS_NIC_SUCC                                   = 0,    /* 成功 */
     IMS_NIC_FAIL,                                          /* 失败 */

     IMS_NIC_CONFIG_PTR_NULL,                               /* 传入的配置结构指针为空 */
     IMS_NIC_MODEM_ID_INVALID,                              /* ModemId无效 */
     IMS_NIC_RABID_INVALID,                                 /* 输入的承载号无效 */
     IMS_NIC_DNS_SERVER_FULL,                               /* DNS服务器已配满，最大设置四个，一主三辅 */
     IMS_NIC_PREFIXLEN_INVALID,                             /* IPV6前缀长度无效 */
     IMS_NIC_RABID_IDLE,                                    /* 输入的承载号上没有对应的配置，删除接口中使用 */
     IMS_NIC_MTU_INVALID,                                   /* 输入的MTU值无效 */
     IMS_NIC_ALREADY_INITED,                                /* 虚拟网卡已经初始化 */
     IMS_NIC_NOT_INITED,                                    /* 虚拟网卡没有初始化 */
     IMS_NIC_SYSCALLFAIL,                                   /* 系统调用失败 */
     IMS_NIC_NO_CFG_PDN,                                    /* 没有任何配置 */

     IMS_NIC_ERR_BUTT
};
typedef VOS_UINT32 IMS_NIC_ERROR_CODE_ENUM_UINT32;

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
 结构名    : IMS_NIC_IPV4_PDN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV4 配置信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDnsPrim         :1;                     /* 外部模块填写，指示aucDnsPrimAddr是否需要配置 */
    VOS_UINT32                          bitOpDnsSec          :1;                     /* 外部模块填写，指示aucDnsSecAddr是否需要配置 */
    VOS_UINT32                          bitOpSpare           :30;

    VOS_UINT8                           aucIpV4Addr[IMS_NIC_IPV4_ADDR_LENGTH];       /* IP地址 */
    VOS_UINT8                           aucDnsPrimAddr[IMS_NIC_IPV4_ADDR_LENGTH];    /* 主DNS服务器IP */
    VOS_UINT8                           aucDnsSecAddr[IMS_NIC_IPV4_ADDR_LENGTH];     /* 辅DNS服务器IP */
}IMS_NIC_IPV4_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_IPV6_PDN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IPV6 配置信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDnsPrim         :1;                     /* 外部模块填写，指示aucDnsPrimAddr是否需要配置 */
    VOS_UINT32                          bitOpDnsSec          :1;                     /* 外部模块填写，指示aucDnsSecAddr是否需要配置 */
    VOS_UINT32                          bitOpSpare           :30;

    VOS_UINT32                          ulBitPrefixLen;                              /* IPV6前缀长度,单位为bit */
    VOS_UINT8                           aucIpV6Addr[IMS_NIC_IPV6_ADDR_LENGTH];       /* IP地址 */
    VOS_UINT8                           aucDnsPrimAddr[IMS_NIC_IPV6_ADDR_LENGTH];    /* 主DNS服务器IP */
    VOS_UINT8                           aucDnsSecAddr[IMS_NIC_IPV6_ADDR_LENGTH];     /* 辅DNS服务器IP */
} IMS_NIC_IPV6_PDN_INFO_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_SOCK_PORT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 端口范围配置信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSockMinPort;      /* socket 端口范围下限 */
    VOS_UINT16                          usSockMaxPort;      /* socket 端口范围上限 */
} IMS_NIC_SOCK_PORT_INFO_STRU;

/*****************************************************************************
 结构名    : IMS_NIC_PDN_INFO_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : IMS虚拟网卡PDN配置消息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo : 1;
    VOS_UINT32                          bitOpIpv6PdnInfo : 1;
    VOS_UINT32                          bitOpSockPortInfo: 1;
    VOS_UINT32                          bitOpSpare       : 29;

    MODEM_ID_ENUM_UINT16                enModemId;          /* 当前Modem号 */
    VOS_UINT8                           ucRabId;            /* 承载号，取值范围[5,15] */
    VOS_UINT8                           ucReserved[1];      /* 消息结构体对齐*/

    IMS_NIC_IPV4_PDN_INFO_STRU          stIpv4PdnInfo;
    IMS_NIC_IPV6_PDN_INFO_STRU          stIpv6PdnInfo;
    IMS_NIC_SOCK_PORT_INFO_STRU         stSockPortInfo;
}IMS_NIC_PDN_INFO_CONFIG_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/* IMS虚拟网卡上行数据发送回调定义 */
typedef VOS_UINT32 (*IMS_NIC_SEND_UL_DATA_FUNC)(VOS_UINT8 *pData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId);

/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : IMS_NIC_PdnInfoConfig
 功能描述  : IMS虚拟网卡配置接口,由IMSA模块调用
 输入参数  : pstConigInfo   IMS虚拟网卡配置信息
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_PdnInfoConfig (IMS_NIC_PDN_INFO_CONFIG_STRU *pstConigInfo);

/*****************************************************************************
 函 数 名  : IMS_NIC_PdnInfoDel
 功能描述  : IMS虚拟网卡PDN配置信息删除，由IMSA模块在PDN去激活后调用
 输入参数  : ucRabId        承载号
             enModemId      当前modemID
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_PdnInfoDel(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId);

/*****************************************************************************
 函 数 名  : IMS_NIC_MtuSet
 功能描述  : IMS虚拟网卡MTU设置
 输入参数  : ulMtu        最大发送单元
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败为对应的错误码

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_MtuSet(VOS_UINT32 ulMtu);

/*****************************************************************************
 函 数 名  : IMS_NIC_RegUlDataSendCb
 功能描述  : 注册IMS虚拟网卡上行数据发送回调函数，由CDS模块调用
 输入参数  : pFunc        上行数据发送回调接口
             enModemId    当前modemID
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_RegUlDataSendCb(IMS_NIC_SEND_UL_DATA_FUNC pFunc, MODEM_ID_ENUM_UINT16 enModemId);

/*****************************************************************************
 函 数 名  : IMS_NIC_RegUlDataSendCb
 功能描述  : IMS虚拟网卡下行数据接收接口，提供给CDS调用
 输入参数  : pucData      IP包数据
             usLen        IP包长度，单位:字节
             enModemId    当前modemID
 输出参数  : 无
 返 回 值  : 成功:IMS_NIC_SUCC，失败:IMS_NIC_FAIL

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_DlDataRcv(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId);

extern VOS_UINT32 IMS_NIC_InitAll(VOS_VOID);

extern VOS_UINT32 IMS_NIC_GetMntnInfo
(
    VOS_UINT8                       *pucData,
    VOS_UINT32                      *pulLen,
    VOS_UINT16                       usType
);

#endif  /*FEATURE_ON == FEATURE_IMS*/

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

#endif /* end of ImsNicInterface.h */


