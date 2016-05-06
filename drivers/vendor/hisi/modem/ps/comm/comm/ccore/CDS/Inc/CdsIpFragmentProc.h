/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsIpFragmentProc.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2012年05月07日
  最近修改   :
  功能描述   : 定义IP分片相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年05月07日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_IPFRAGMENT_PROC_H__
#define __CDS_IPFRAGMENT_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "CdsDepend.h"
#include "CdsIpfCtrl.h"
#include "TcpIpTypeDef.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define CDS_IPV4_FRAGMENT_BUFF_SIZE               (30)                  /**/
#define CDS_IPV6_FRAGMENT_BUFF_SIZE               (20)                  /**/
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
 结构名    : CDS_IPV4_FRAGMENT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IPV4分段信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8        ucEpsbID;
    VOS_UINT8        aucRev[1];

    VOS_UINT16       usIpIdentity;
    IPV4_ADDR_UN     unSrcAddr;
    IPV4_ADDR_UN     unDstAddr;
}CDS_IPV4_FRAGMENT_INFO_STRU;

/*****************************************************************************
 结构名    : CDS_IPV4_FRAGMENT_BUFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IPV4分片缓存
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulIndex;
    CDS_IPV4_FRAGMENT_INFO_STRU        astSegBuff[CDS_IPV4_FRAGMENT_BUFF_SIZE];
}CDS_IPV4_FRAGMENT_BUFF_STRU;

/*****************************************************************************
 结构名    : CDS_IPV6_FRAGMENT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IPV6分片信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8        ucEpsbID;
    VOS_UINT8        aucRev[3];
    IPV6_ADDR_UN     unSrcAddr;
    IPV6_ADDR_UN     unDstAddr;
    VOS_UINT32       ulIdentity;
}CDS_IPV6_FRAGMENT_INFO_STRU;


/*****************************************************************************
 结构名    : CDS_IPV6_FRAGMENT_BUFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IPV6分片缓存
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulIndex;
    CDS_IPV6_FRAGMENT_INFO_STRU        astSegBuff[CDS_IPV6_FRAGMENT_BUFF_SIZE];
}CDS_IPV6_FRAGMENT_BUFF_STRU;

/*****************************************************************************
 结构名    : CDS_IP_FRAGMENT_STATS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IP分片统计量
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulRxIpv4Frag;               /*接收IPV4分片的个数*/
    VOS_UINT32                  ulRxIpv4IpfSucc;            /*接收IPV4 IPF过滤成功的个数*/
    VOS_UINT32                  ulRxIpv4IpfFail;            /*接收IPV4 IPF过滤失败个数*/
    VOS_UINT32                  ulRxIpv6Frag;               /*接收IPV6分片个数*/
    VOS_UINT32                  ulRxIpv6IpfSucc;            /*接收IPV6 IPF过滤成功的个数*/
    VOS_UINT32                  ulRxIpv6IpfFail;            /*接收IPV6 IPF过滤失败的个数*/
    VOS_UINT32                  ulLocalProcSucc;            /*接收本地处理成功的个数*/
    VOS_UINT32                  ulLocalProcFail;            /*接收本地处理失败的个数*/
}CDS_IP_FRAGMENT_STATS_STRU;

/*****************************************************************************
 结构名    : CDS_IPV6_SEGMENT_BUFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS IPV6分片缓存
*****************************************************************************/
typedef struct
{
    CDS_IPV4_FRAGMENT_BUFF_STRU        stIpV4Buff;
    CDS_IPV6_FRAGMENT_BUFF_STRU        stIpV6Buff;
    CDS_IP_FRAGMENT_STATS_STRU         stStats;
}CDS_IP_FRAGMENT_BUFF_STRU;


/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
extern     CDS_IP_FRAGMENT_BUFF_STRU       g_stCdsIpFragBuff;

/*获取IPV4分片处理BUFF*/
#define CDS_GET_IPV4_FRAGMENT_BUFF()            (&(g_stCdsIpFragBuff.stIpV4Buff))

/*获取IPV6分片处理BUFF*/
#define CDS_GET_IPV6_FRAGMENT_BUFF()            (&(g_stCdsIpFragBuff.stIpV6Buff))

/*获取IP分片处理统计量*/
#define CDS_GET_IP_FRAGMENT_STATS_STRU()        (&(g_stCdsIpFragBuff.stStats))


/*统计信息*/
#define CDS_IPFRAG_RX_IPV4_PKT(n)                (g_stCdsIpFragBuff.stStats.ulRxIpv4Frag += (n))
#define CDS_IPFRAG_RX_IPV4_IPF_SUCC(n)           (g_stCdsIpFragBuff.stStats.ulRxIpv4IpfSucc += (n))
#define CDS_IPFRAG_RX_IPV4_IPF_FAIL(n)           (g_stCdsIpFragBuff.stStats.ulRxIpv4IpfFail += (n))
#define CDS_IPFRAG_RX_IPV6_PKT(n)                (g_stCdsIpFragBuff.stStats.ulRxIpv6Frag    += (n))
#define CDS_IPFRAG_RX_IPV6_IPF_SUCC(n)           (g_stCdsIpFragBuff.stStats.ulRxIpv6IpfSucc += (n))
#define CDS_IPFRAG_RX_IPV6_IPF_FAIL(n)           (g_stCdsIpFragBuff.stStats.ulRxIpv6IpfFail += (n))
#define CDS_IPFRAG_LOCAL_PROC_SUCC(n)            (g_stCdsIpFragBuff.stStats.ulLocalProcSucc += (n))
#define CDS_IPFRAG_LOCAL_PROC_FAIL(n)            (g_stCdsIpFragBuff.stStats.ulLocalProcFail += (n))


/*****************************************************************************
  8 函数声明
*****************************************************************************/



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

