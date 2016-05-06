/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsInterface.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月24日
  最近修改   :
  功能描述   : 定义CDS提供给外部组件使用的公共接口文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_INTERFACE_H__
#define __CDS_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CdsMmcInterface.h"
#include "TcpIpTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*最大软过滤器个数*/
#define CDS_MAX_SOFT_FILTER_NUM                 (128)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : CDS_UL_IPF_BEARER_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :  上行IPF过滤结果中Bearer ID内容定义
              IPF Filter ID:
               0~4      保留
               5~15     EPS Bearer ID
               16       上行DHCP
               17       上行DHCPv6
               18       上行ICMP
               19       上行ICMPv6
               20       上行Link Local Address FE80
               21       上行Link Local Address FF
               22~62    暂时保留，可扩展
               63       不匹配任何Filter

*****************************************************************************/
typedef enum CDS_UL_IPF_BEARER_ID_ENUM
{
    CDS_UL_IPF_BEARER_ID_RSV0         = 0,
    CDS_UL_IPF_BEARER_ID_EPSBID5      = 5,
    CDS_UL_IPF_BEARER_ID_EPSBID15     = 15,
    CDS_UL_IPF_BEARER_ID_DHCPV4       = 16,
    CDS_UL_IPF_BEARER_ID_DHCPV6       = 17,
    CDS_UL_IPF_BEARER_ID_ICMPV4       = 18,
    CDS_UL_IPF_BEARER_ID_ICMPV6       = 19,
    CDS_UL_IPF_BEARER_ID_LL_FE80      = 20,
    CDS_UL_IPF_BEARER_ID_LL_FF        = 21,
    CDS_UL_IPF_BEARER_ID_INVALID      = 63 /*0x3F */
}CDS_UL_IPF_BEARER_ID_ENUM;

typedef VOS_UINT32  CDS_UL_IPF_BEARER_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : CDS_SOFTFILTER_DIRECTION_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CDS软过滤器方向
*****************************************************************************/
enum CDS_SOFTFILTER_DIRECTION_ENUM
{
    CDS_SOFTFILTER_DIRECTION_PRE_REL7_TFT_FILTER          = 0x00,
    CDS_SOFTFILTER_DIRECTION_DOWNLINK                     = 0x01,
    CDS_SOFTFILTER_DIRECTION_UPLINK                       = 0x02,
    CDS_SOFTFILTER_DIRECTION_UPLINK_DOWNLINK              = 0x03,
    CDS_SOFTFILTER_DIRECTION_BUTT
};
typedef VOS_UINT8 CDS_SOFTFILTER_DIRECTION_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CDS_SOFTFILTER_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CDS软过滤器类型定义
*****************************************************************************/
enum CDS_SOFTFILTER_TYPE_ENUM
{
    CDS_SOFTFILTER_TYPE_IPV4       = 0x00,
    CDS_SOFTFILTER_TYPE_IPV6       = 0x01,
    CDS_SOFTFILTER_TYPE_BUTT
};
typedef VOS_UINT8 CDS_SOFTFILTER_TYPE_ENUM_UINT8;


/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : CDS_SOFTFILTER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS过滤器信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask        : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask        : 1;
    VOS_UINT32                          bitOpLcIpv4AddrAndMask         : 1;
    VOS_UINT32                          bitOpLcIpv6AddrAndMask         : 1;
    VOS_UINT32                          bitOpProtocolId                : 1;
    VOS_UINT32                          bitOpSingleLocalPort           : 1;
    VOS_UINT32                          bitOpLocalPortRange            : 1;
    VOS_UINT32                          bitOpSingleRemotePort          : 1;
    VOS_UINT32                          bitOpRemotePortRange           : 1;
    VOS_UINT32                          bitOpSecuParaIndex             : 1;
    VOS_UINT32                          bitOpTypeOfService             : 1;
    VOS_UINT32                          bitOpFlowLabelType             : 1;
    VOS_UINT32                          bitOpSpare                     : 20;

    VOS_UINT32                              ulPacketFilterId;
    CDS_SOFTFILTER_DIRECTION_ENUM_UINT8     enDirection;
    CDS_SOFTFILTER_TYPE_ENUM_UINT8          enFilterType;
    VOS_UINT16                              usPrecedence;             /*packet filter evaluation precedence*/

    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved1[3];

    VOS_UINT32                          ulSecuParaIndex;          /*SPI*/
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;

    VOS_UINT8                           ucProtocolId;
    VOS_UINT8                           ucTypeOfService;          /*TOS*/
    VOS_UINT8                           ucTypeOfServiceMask;      /*TOS Mask*/
    VOS_UINT8                           aucReserved2[1];

    IPV4_ADDR_UN                        unLocalIpv4Addr;
    IPV4_ADDR_UN                        unLocalIpv4Mask;
    IPV4_ADDR_UN                        unRmtIpv4Addr;
    IPV4_ADDR_UN                        unRmtIpv4Mask;
    IPV6_ADDR_UN                        unLocalIpv6Addr;
    IPV6_ADDR_UN                        unLocalIpv6Mask;
    IPV6_ADDR_UN                        unRmtIpv6Addr;
    IPV6_ADDR_UN                        unRmtIpv6Mask;
    VOS_UINT32                          ulFlowLabelType;          /*FlowLabelType*/
}CDS_SOFTFILTER_INFO_STRU;


/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/
extern VOS_UINT32  CDS_GetRanMode(VOS_VOID);
extern VOS_UINT32  CDS_SetUlSoftFilter(const CDS_SOFTFILTER_INFO_STRU *pstUlFilterInfo, VOS_UINT32 ulFilterNum);
extern VOS_UINT32  CDS_IsPsDataAvail(VOS_VOID);



/*****************************************************************************
  9 OTHERS定义
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

