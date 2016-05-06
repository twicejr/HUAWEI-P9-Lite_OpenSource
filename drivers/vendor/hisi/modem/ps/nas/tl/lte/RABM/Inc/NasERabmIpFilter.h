/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasERabmIpFilter.h
  版 本 号   : 初稿
  作    者   : L62099
  生成日期   : 2011年2月26日
  最近修改   :
  功能描述   : RABM TFT功能在IP 过滤硬件上的适配文件，包含外部接口的引用，内
               部使用参数和消息结构的定义
  函数列表   :
  修改历史   :
  1.日    期   : 2011年2月26日
    作    者   : L62099
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NASRABMIPF_H__
#define __NASRABMIPF_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "TlPsDrv.h"
#include  "NasERabmAppMsgProc.h"
#include  "CdsInterface.h"

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
  2 macro
*****************************************************************************/
/* 上行最多Filter数目为128 */
#define NAS_ERABM_IPF_MAX_UL_FILTER          128

/* 下行Filter目前使用8个 */
#define NAS_ERABM_IPF_MAX_DL_FILTER          8

/* 上行NIDS Filter最大数目 */
#define NAS_ERABM_IPF_MAX_UL_NDIS_FILTER     (12)

/* 当前上行NDIS Filter数目 */
#define NAS_ERABM_IPF_CUR_UL_NDIS_FILTER_NUM (10)

/* IPF 使用的Filter类型 */
#define NAS_ERABM_IPF_IPTYPE_IPV4            0
#define NAS_ERABM_IPF_IPTYPE_IPV6            1
#define NAS_ERABM_IPF_IPTYPE_IPV4V6          2
#define NAS_ERABM_IPF_IPTYPE_INVALID         3

#define NAS_ERABM_NO_UPPERLAYER             (0)
/* 给NDIS所需数据包的过滤器预留的优先级个数，0-5 */
#define NAS_ERABM_IPF_UL_NDIS_PRIORITY_NUM  (6)

#define NAS_ERABM_MIN_AIR_TFT_PRIORITY      (255)
/* 上行最多Filter数目为128 */
#define NAS_ERABM_CDS_MAX_UL_FILTER          128

/* 为默认承载设置的优先级 ,低于其它所有TFT Filter的优先级 */
#define NAS_ERABM_CDS_LOWEST_PRI            (NAS_ERABM_MIN_AIR_TFT_PRIORITY+1)


/* 为默认承载设置的优先级 ,低于其它所有TFT Filter的优先级 */
#define NAS_ERABM_IPF_LOWEST_PRI            (NAS_ERABM_IPF_UL_NDIS_PRIORITY_NUM+\
                                             NAS_ERABM_MIN_AIR_TFT_PRIORITY+1)

/* IPF过滤不匹配所有Filter */
#define NAS_ERABM_IPF_INVALID_BEARER_ID      0x3F

/* 上行提供给驱动的FilterID = EPSBID | TFT Filter ID */
#define NAS_ERABM_IPF_UL_IPV4_FILTER_ID(epsbid, filterid)\
    ((((VOS_UINT32)epsbid)<<16)|((VOS_UINT32)(filterid)))

#define NAS_ERABM_IPF_UL_IPV6_FILTER_ID(epsbid, filterid)\
    ((((VOS_UINT32)epsbid)<<24)|((VOS_UINT32)(filterid)))

/* 以下宏定义为NAS IPF Filter 队列操作集 */
/*#define NAS_ERABM_IPF_CONFIG_INFO_PTR()                     &g_stNasERabmIpfConfigInfo*/
#define NAS_ERABM_IPF_FILTER_LIST_PTR()                     &g_stNasERabmIpfFilterArray

/* 增加上行Filter数目 */
#define NAS_ERABM_IPF_ADD_UL_FILTER_NUM()                   (((NAS_ERABM_IPF_FILTER_LIST_PTR())->ulUpLinkUsedNum)++)
/* 设置上行Filter数目 */
#define NAS_ERABM_IPF_SET_UL_FILTER_NUM(num)                (NAS_ERABM_IPF_FILTER_LIST_PTR())->ulUpLinkUsedNum = (num)
/* 读取上行已有Filter数目 */
#define NAS_ERABM_IPF_GET_UL_FILTER_NUM()                   (NAS_ERABM_IPF_FILTER_LIST_PTR())->ulUpLinkUsedNum
/* 读取上行指定位置的Filter */
#define NAS_ERABM_IPF_GET_UL_FILTER_PTR(num)                (&((NAS_ERABM_IPF_FILTER_LIST_PTR())->astUlFilter[num]))
/* 判断上行FIlter队列是否满 */
#define NAS_ERABM_IPF_IS_UL_FILTER_FULL()                   (NAS_ERABM_IPF_GET_UL_FILTER_NUM() >= NAS_ERABM_IPF_MAX_UL_FILTER)

/* 增加下行Filter数目 */
#define NAS_ERABM_IPF_ADD_DL_FILTER_NUM()                   (((NAS_ERABM_IPF_FILTER_LIST_PTR())->ulDownLinkUsedNum)++)
/* 设置下行Filter数目 */
#define NAS_ERABM_IPF_SET_DL_FILTER_NUM(num)                (NAS_ERABM_IPF_FILTER_LIST_PTR())->ulDownLinkUsedNum = (num)
/* 读取下行已有Filter数目 */
#define NAS_ERABM_IPF_GET_DL_FILTER_NUM()                   (NAS_ERABM_IPF_FILTER_LIST_PTR())->ulDownLinkUsedNum
/* 读取下行指定位置的Filter */
#define NAS_ERABM_IPF_GET_DL_FILTER_PTR(num)                (&((NAS_ERABM_IPF_FILTER_LIST_PTR())->astDlFilter[num]))
/* 判断下行FIlter队列是否满 */
#define NAS_ERABM_IPF_IS_DL_FILTER_FULL()                   (NAS_ERABM_IPF_GET_DL_FILTER_NUM() >= NAS_ERABM_IPF_MAX_DL_FILTER)

/* IPF优先级比较函数定义 */
typedef VOS_INT (*NAS_IPF_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);
typedef VOS_INT (*NAS_CDS_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);

/* IPF上行NDIS Filter定义 */
#define NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(filter_id)\
    pstFilter = &g_astNasERabmUlNdisFilter[filter_id];\
    NAS_ERABM_MEM_SET_S(pstFilter, sizeof(NAS_ERABM_IPF_UL_NDIS_FILTER_INFO),   \
                            0x0, sizeof(NAS_ERABM_IPF_UL_NDIS_FILTER_INFO))     \

#define NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(iptype)\
    pstFilter->ucIpType = (iptype)

#define NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(priority)\
    pstFilter->usPriority = (priority)

#define NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(protocol)\
    pstFilter->ucProtocolId = (protocol);\
    pstFilter->bitOpProtocolId = NAS_ERABM_OP_TRUE

#define NAS_ERABM_IPF_UL_NDIS_FILTER_PORT_HI(port_hi)\
    pstFilter->usPortHi = (port_hi);\
    pstFilter->bitOpPort = NAS_ERABM_OP_TRUE

#define NAS_ERABM_IPF_UL_NDIS_FILTER_PORT_LO(port_lo)\
    pstFilter->usPortLo = (port_lo);\
    pstFilter->bitOpPort = NAS_ERABM_OP_TRUE

#define NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPTYPE(type)\
    pstFilter->usIcmpType = (type);\
    pstFilter->bitOpType = NAS_ERABM_OP_TRUE

#define NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPCODE(code)\
    pstFilter->usIcmpCode = (code);\
    pstFilter->bitOpCode = NAS_ERABM_OP_TRUE

#define NAS_ERABM_IPF_UL_NDIS_FILTER_DSTADDR_FE80()\
    pstFilter->aucDstAdrr[0] = 0xfe;\
    pstFilter->aucDstAdrr[1] = 0x80;\
    pstFilter->aucDstMask[0] = 0xff;\
    pstFilter->aucDstMask[1] = 0xc0;\
    pstFilter->bitOpDstAdrr = NAS_ERABM_OP_TRUE

#define NAS_ERABM_IPF_UL_NDIS_FILTER_DSTADDR_FF()\
    pstFilter->aucDstAdrr[0] = 0xff;\
    pstFilter->aucDstMask[0] = 0xff;\
    pstFilter->bitOpDstAdrr = NAS_ERABM_OP_TRUE

#define NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(filter_id)

/* 上行NDIS DHCPv4 Filter定义, UDP 目的端口为67(DHCPV4 SERVER) */
#define NAS_ERABM_IPF_DEF_UL_NDIS_DHCPV4_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_DHCP4);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(17);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PORT_HI(67);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PORT_LO(67);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_DHCP4)

/* 上行NDIS Filter定义, UDP目的端口547(DHCPV6 SERVER) */
#define NAS_ERABM_IPF_DEF_UL_NDIS_DHCPV6_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_DHCP6);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(17);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PORT_HI(547);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PORT_LO(547);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_DHCP6)

/*上行NDIS ICMP Router Solicitation Filter定义, 协议号58，Type 133， code 0 */
#define NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_RS_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_RS);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPTYPE(133);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_RS)

/*上行NDIS ICMP Router Advertisement Filter定义, 协议号58，Type 134， code 0 */
#define NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_RA_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_RA);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPTYPE(134);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_RA)

/*上行NDIS ICMP Neighbor Solicitation Filter定义, 协议号58，Type 135， code 0 */
#define NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_NS_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_NS);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPTYPE(135);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_NS)

/*上行NDIS ICMP Neighbor Advertisement Filter定义, 协议号58，Type 136， code 0 */
#define NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_NA_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_NA);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPTYPE(136);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_NA)

/*上行NDIS ICMP REDIRECT Filter定义, 协议号58，Type 137， code 0 */
#define NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_REDIRECT_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_REDIRECT);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPTYPE(137);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_REDIRECT)

/*上行NDIS ICMP ECHO REQUEST定义, 协议号58，Type 128， code 0，目的地址为FE80打头 */
#define NAS_ERABM_IPF_DEF_UL_NDIS_LOC_PING6_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_PING6);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PROTOCOL(58);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DSTADDR_FE80();\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPTYPE(128);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_ICMPCODE(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(0);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_PING6)

/*上行NDIS 目的地址FE80打头定义 */
#define NAS_ERABM_IPF_DEF_UL_NDIS_LOC_FE80_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_FE80);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DSTADDR_FE80();\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_FE80)

/*上行NDIS 目的地址FF打头定义 */
#define NAS_ERABM_IPF_DEF_UL_NDIS_LOC_FF_FILTER()\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_BEGIN(NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_FF);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_IP_TYPE(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DSTADDR_FF();\
    NAS_ERABM_IPF_UL_NDIS_FILTER_PRIORITY(1);\
    NAS_ERABM_IPF_UL_NDIS_FILTER_DEFINE_END(NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_FF)

/* 获取上行NDIS用户定义的Filter */
#define NAS_ERABM_IPF_GET_UL_NDIS_USER_FILTER(filter_id)\
    (&g_astNasERabmUlNdisFilter[filter_id])

/* 查表找到Filter ID对应的应配置给驱动的Bid */
#define NAS_ERABM_IPF_CONV_ULNDISFILTER_TO_BID(filter_id)\
    (g_aulNasERabmUlNdisFilterTypeTable[filter_id][1])

#define NAS_ERABM_IPF_GET_UL_NDIS_FILTER_FLAG()     (g_enUlNdisFilterValidFlag)
#define NAS_ERABM_IPF_SET_UL_NDIS_FILTER_FLAG(flag) (g_enUlNdisFilterValidFlag = (flag))


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_ERABM_IPF_DL_FILTER_TYPE
 协议表格  :
 ASN.1描述 :
 枚举说明  :  下行IP过滤类型
*****************************************************************************/
enum NAS_ERABM_IPF_DL_FILTER_TYPE
{
    NAS_ERABM_IPF_DL_FITLER_DHCP4 = 0,
    NAS_ERABM_IPF_DL_FITLER_DHCP6,
    NAS_ERABM_IPF_DL_FITLER_RS,
    NAS_ERABM_IPF_DL_FITLER_RA,
    NAS_ERABM_IPF_DL_FITLER_NS,
    NAS_ERABM_IPF_DL_FITLER_NA,
    NAS_ERABM_IPF_DL_FITLER_REDIRECT,
    NAS_ERABM_IPF_DL_FITLER_BUTT
};
typedef VOS_UINT32  NAS_ERABM_IPF_DL_FILTER_TYPE_UINT32;
/*****************************************************************************
 枚举名    : NAS_ERABM_IPF_UL_NDIS_FILTER_TYPE
 协议表格  :
 ASN.1描述 :
 枚举说明  : 上行NDIS过滤类型
*****************************************************************************/
enum NAS_ERABM_IPF_UL_NDIS_FILTER_TYPE
{
    NAS_ERABM_IPF_UL_NDIS_FILTER_DHCP4              = 0,
    NAS_ERABM_IPF_UL_NDIS_FILTER_DHCP6,
    NAS_ERABM_IPF_UL_NDIS_FILTER_RS,
    NAS_ERABM_IPF_UL_NDIS_FILTER_RA,
    NAS_ERABM_IPF_UL_NDIS_FILTER_NS,
    NAS_ERABM_IPF_UL_NDIS_FILTER_NA,
    NAS_ERABM_IPF_UL_NDIS_FILTER_REDIRECT,
    NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_PING6,
    NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_FE80,
    NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_FF,
    NAS_ERABM_IPF_UL_NDIS_FILTER_BUTT
};
typedef VOS_UINT32  NAS_ERABM_IPF_UL_NDIS_FILTER_TYPE_UINT32;

/*****************************************************************************
 枚举名    : NAS_ERABM_IPF_IPSEG_INFO
 协议表格  :
 ASN.1描述 :
 枚举说明  :  下行IP分段信息
*****************************************************************************/
enum NAS_ERABM_IPF_IPSEG_INFO
{
    NAS_ERABM_IPF_IPF_NO_FRAGMENT = 0,
    NAS_ERABM_IPF_IPF_FRAGMENT_HEAD,
    NAS_ERABM_IPF_IPF_FRAGMENT_MID,
    NAS_ERABM_IPF_IPF_FRAGMENT_TAIL,

    NAS_ERABM_IPF_IPF_FRAGMENT_BUTT
};
typedef VOS_UINT16   NAS_ERABM_IPF_IPSEG_INFO_UINT16;

/*****************************************************************************
 枚举名    : NAS_ERABM_IPF_DIRECTION
 协议表格  :
 ASN.1描述 :
 枚举说明  :  IPF Filter方向
*****************************************************************************/
enum NAS_ERABM_IPF_DIRECTION
{
    NAS_ERABM_IPF_DIRECTION_UL = 0,
    NAS_ERABM_IPF_DIRECTION_DL,
    NAS_ERABM_IPF_DIRECTION_BUTT
};
typedef VOS_UINT32  NAS_ERABM_IPF_DIRECTION_UINT32;

/*****************************************************************************
 枚举名    : NAS_ERABM_UL_NDIS_FILTER_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 上行NDIS所需数据包的FILTER配置是否有效枚举
               0        有效
               1        无效

*****************************************************************************/
enum NAS_ERABM_UL_NDIS_FILTER_FLAG_ENUM
{
    NAS_ERABM_UL_NDIS_FILTER_VALID      =      0,        /*有效*/
    NAS_ERABM_UL_NDIS_FILTER_INVALID    =      1,        /*无效*/

    NAS_ERABM_UL_NDIS_FILTER_FLAG_BUTT
};
typedef VOS_UINT32 NAS_ERABM_UL_NDIS_FILTER_FLAG_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_ERABM_IPF_FILTER_ARRAY
 协议表格  :
 ASN.1描述 :
 结构说明  : IPF FILTER队列结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulUpLinkUsedNum;
    VOS_UINT32                      ulDownLinkUsedNum;
    IPF_FILTER_CONFIG_S             astUlFilter[NAS_ERABM_IPF_MAX_UL_FILTER];
    IPF_FILTER_CONFIG_S             astDlFilter[NAS_ERABM_IPF_MAX_DL_FILTER];
}NAS_ERABM_IPF_FILTER_ARRAY;

/*****************************************************************************
 结构名    : NAS_ERABM_CDS_FILTER_ARRAY
 协议表格  :
 ASN.1描述 :
 结构说明  : IPF FILTER队列结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulUpLinkUsedNum;
    CDS_SOFTFILTER_INFO_STRU        astUlFilter[NAS_ERABM_CDS_MAX_UL_FILTER];
}NAS_ERABM_CDS_FILTER_ARRAY;
/*****************************************************************************
 结构名    : NAS_ERABM_IPF_IP4FRAG_CONTEXT
 协议表格  :
 ASN.1描述 :
 结构说明  : IPv4 分片上下文结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8           ucSrcAddr[4];         /*源地址
 */
    VOS_UINT8           ucDstAddr[4];         /*目的地址
 */
    VOS_UINT8           ucIpId[4];            /* IP IDentification
 */
}NAS_ERABM_IPF_IP4FRAG_CONTEXT;

/*****************************************************************************
 结构名    : NAS_ERABM_IPF_IP6FRAG_CONTEXT
 协议表格  :
 ASN.1描述 :
 结构说明  : IPv6 分片上下文结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8           ucSrcAddr[16];         /*源地址
 */
    VOS_UINT8           ucDstAddr[16];         /*目的地址
 */
    VOS_UINT8           ucIpId[4];             /*IP IDentification
 */
}NAS_ERABM_IPF_IP6FRAG_CONTEXT;


/*****************************************************************************
 结构名    : NAS_ERABM_IPF_UL_NDIS_FILTER_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行NDIS Filter使用的简易结构，用于配置上行NDIS所需数据包的FILTER
*****************************************************************************/
typedef struct
{
    VOS_UINT16          bitOpProtocolId:1;
    VOS_UINT16          bitOpPort:1;
    VOS_UINT16          bitOpType:1;
    VOS_UINT16          bitOpCode:1;
    VOS_UINT16          bitOpDstAdrr:1;
    VOS_UINT16          bitRsv:11;

    VOS_UINT8           ucIpType;       /*ip type, v4 or v6
 */
    VOS_UINT8           ucProtocolId;
    VOS_UINT16          usPortHi;       /*dest port
 */
    VOS_UINT16          usPortLo;       /*dest port
 */
    VOS_UINT16          usIcmpType;
    VOS_UINT16          usIcmpCode;
    VOS_UINT8           aucDstAdrr[16];
    VOS_UINT8           aucDstMask[16];
    VOS_UINT16          usPriority;
    VOS_UINT8           aucReserved[2];
}NAS_ERABM_IPF_UL_NDIS_FILTER_INFO;

#define NAS_ERABM_OM_LOG_MAX_FILTER 16

/*****************************************************************************
 结构名    : NAS_ERABM_OM_LOG_IPF_FILTER_INFO_STRU
 结构说明  : 上行TFT配置信息可维可测
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    VOS_UINT32                           ulFilterNum;
    IPF_FILTER_CONFIG_S                  astUlFilter[NAS_ERABM_OM_LOG_MAX_FILTER];
}NAS_ERABM_OM_LOG_IPF_FILTER_INFO_STRU;
/*****************************************************************************
 结构名    : NAS_ERABM_OM_LOG_CDS_FILTER_INFO_STRU
 结构说明  : 上行TFT配置信息可维可测
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      stMsgHeader;     /*_H2ASN_Skip*/
    VOS_UINT32                           ulUpLinkUsedNum;
    CDS_SOFTFILTER_INFO_STRU             astUlFilter[NAS_ERABM_OM_LOG_MAX_FILTER];
}NAS_ERABM_OM_LOG_CDS_FILTER_INFO_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_ERABM_IPF_FILTER_ARRAY g_stNasERabmIpfFilterArray;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_UINT32  NAS_ERABM_IpfConfigFilter(VOS_VOID);

extern IPF_FILTER_CONFIG_S * NAS_ERABM_IpfGetFreeFilter
(
    NAS_ERABM_IPF_DIRECTION_UINT32 enDir
);

extern VOS_INT32  NAS_ERABM_IpfCompare
(
    const VOS_VOID *arg1,
    const VOS_VOID *arg2
);

extern VOS_UINT32 NAS_ERABM_IpfGenerateBaseIpv4Filter
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT8 ucEpsbId
);

extern VOS_UINT32 NAS_ERABM_IpfGenerateBaseIpv6Filter
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT8 ucEpsbId
);
extern VOS_UINT32 NAS_ERABM_IpfGenerateFilterWithoutTFT
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT8 ucEpsbId
);
extern VOS_VOID NAS_ERABM_IpfConvertOtherPartToFilter
(
    const ESM_ERABM_TFT_PF_STRU *pstTftPf,
    IPF_MATCH_INFO_S     *pstIpFilter
);

extern VOS_UINT32 NAS_ERABM_IpfCheckFilterType
(
    const ESM_ERABM_TFT_PF_STRU *pstTftPf,
    VOS_UINT8 ucIpType
);

extern VOS_UINT32 NAS_ERABM_IpfConvertTftToFilter
(
    const APP_ESM_IP_ADDR_STRU   *pstPdnAddr,
    const ESM_ERABM_TFT_PF_STRU   *pstTftPf,
    VOS_UINT8              ucEpsbId
);

extern VOS_UINT32 NAS_ERABM_IpfGenerateFilterWithTFT
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT8 ucEpsbId
);

extern VOS_UINT32 NAS_ERABM_IpfGenerateFilters(VOS_VOID);

extern VOS_UINT32 NAS_ERABM_IpfConfigUlFilter(VOS_VOID);

extern VOS_UINT8 NAS_ERABM_IpfIpFragmentProcess
(
    VOS_UINT8                          *pstDataAddr,
    VOS_UINT16                          usIpVer,
    VOS_UINT16                          usSegType,
    VOS_UINT8                           ucBearerId,
    VOS_UINT8                           ucUpperLayerFlag
);
extern VOS_VOID NAS_ERABM_SetUlNdisFilterValidFlag
(
    NAS_ERABM_UL_NDIS_FILTER_FLAG_ENUM_UINT32   enUlNdisFilterFlag
);
extern VOS_UINT32 NAS_ERABM_IpfAddUlNdisFilter(VOS_UINT32 ulFilterId);
extern VOS_UINT32 NAS_ERABM_IpfRmvUlNdisFilter(VOS_UINT32 ulFilterId);
extern VOS_VOID NAS_ERABM_IpfUlNdisFilterInit( VOS_VOID );
extern VOS_UINT8 NAS_ERABM_GetSrcIpv4MatchedDeftBearerId
(
    const NAS_ERABM_IPV4_HEADER_STRU   *pstIpv4HeaderInfo,
    VOS_UINT8                          *pucBearerId
);
extern VOS_UINT8 NAS_ERABM_GetSrcIpv6MatchedDeftBearerId
(
    const NAS_ERABM_IPV6_HEADER_STRU   *pstIpv6HeaderInfo,
    VOS_UINT8                          *pucBearerId
);
extern VOS_UINT32 NAS_ERABM_CdsConfigUlFilter( VOS_VOID );
extern VOS_VOID NAS_ERABM_SndOmLogIpfUlFilterInfo(IPF_FILTER_CONFIG_S  *pstFilterList, VOS_UINT32  ulIpFilterNum);
extern VOS_VOID NAS_ERABM_SndOmLogCdsUlFilterInfo(CDS_SOFTFILTER_INFO_STRU  *pstFilterList, VOS_UINT32  ulUpLinkUsedNum);

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

#endif


/*end of file.
 */

