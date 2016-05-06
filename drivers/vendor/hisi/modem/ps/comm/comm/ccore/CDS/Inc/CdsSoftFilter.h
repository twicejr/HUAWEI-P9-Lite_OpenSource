/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsSoftFilter.h
  版 本 号   : 初稿s
  作    者   : y00151394
  生成日期   : 2013年07月30日
  最近修改   :
  功能描述   : CDS软过滤功能头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年07月30日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_SOFT_FILTER_H__
#define __CDS_SOFT_FILTER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TcpIpTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*IPSec*/
#define IPSEC_NAT_TRAVERSAL_UDP_PORT          (4500)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/


/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : CDS_IP_DATA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS软过滤IPV4关键信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucNextHdr;                  /*协议号*/
    VOS_UINT8                       ucServiceType;              /*服务类型*/
    VOS_UINT8                       ucIpSegType;                /*分片类型信息*/
    VOS_UINT8                       ucTrafficClass;             /*传输流分类*/

    VOS_UINT32                      ulIpIdentity;               /*IP包的ID*/


    VOS_UINT32                      ulHdrLen;
    VOS_UINT32                      ulFlowLable;

    VOS_UINT32                      ulAhSpi;                    /*AH SPI*/
    VOS_UINT32                      ulEspSpi;                   /*ESP SPI*/
    VOS_UINT16                      usSrcPort;                  /*源端口号*/
    VOS_UINT16                      usDestPort;                 /*目的端口号*/

    IPV4_ADDR_UN                    unIpv4SrcAddr;              /*源IPv4地址*/
    IPV4_ADDR_UN                    unIpv4DestAddr;             /*目的IPv4地址*/

    IPV6_ADDR_UN                    unIpv6SrcAddr;              /*源IPv6地址*/
    IPV6_ADDR_UN                    unIpv6DestAddr;             /*目的IPv6地址*/
    VOS_UINT8                       ucIpVersion;                /*IP版本号*/
    VOS_UINT8                       aucRsv[3];

}CDS_IP_DATA_INFO_STRU;


/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/
extern VOS_VOID     CDS_DecodeIpv6Packet(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpv6Info);
extern VOS_UINT32   CDS_IpSoftFilter(TTF_MEM_ST *pstIpPkt, VOS_UINT16 *pusResult, const CDS_ENTITY_STRU *pstCdsEntity);
extern VOS_UINT32   CDS_Ipv6ExtHdr(VOS_UINT8 ucNextHdr);
extern VOS_UINT32   CDS_Ipv6AddrEqual(const IPV6_ADDR_UN *a1, const IPV6_ADDR_UN *a2);
extern VOS_VOID     CDS_DecodeIpv4Packet(const TTF_MEM_ST *pstIpPkt, CDS_IP_DATA_INFO_STRU *pstIpInfo);
extern VOS_VOID     CDS_DecodeIpv6Packet(const TTF_MEM_ST * pstIpPkt, CDS_IP_DATA_INFO_STRU * pstIpInfo);
extern VOS_UINT32   CDS_IsIpv4FragInfoEq(const CDS_IP_DATA_INFO_STRU *pstSrc,const CDS_IP_DATA_INFO_STRU *pstTarget);
extern VOS_UINT32   CDS_IsIpv6FragInfoEq(const CDS_IP_DATA_INFO_STRU *pstSrc,const CDS_IP_DATA_INFO_STRU *pstTarget);




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

