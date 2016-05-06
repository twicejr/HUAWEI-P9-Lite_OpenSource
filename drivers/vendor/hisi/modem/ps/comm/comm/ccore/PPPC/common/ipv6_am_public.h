/******************************************************************************

                  版权所有 (C), 2012-2020, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ipv6_am_public.h
  版 本 号   : 初稿
  作         者   :  zhaichao
  生成日期   : 2012年10月10日
  最近修改   :
  功能描述   : IPV6组件模块提供给AM子系统的公共头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月10日
    作    者   : zhaichao
    修改内容   : 创建文件

******************************************************************************/
#ifndef _IPV6_AM_PUBLIC_H
#define _IPV6_AM_PUBLIC_H

/**************宏定义***************/
#define IPV6_V6_USER       1   
#define IPV6_V4V6_USER     2 

#define IPV6_ADD   0
#define IPV6_SUB   1

#define IPV6_IPV6CP_ATTEMPT  1   
#define IPV6_IPV6CP_SUCC     2 
/**************函数声明***************/

/*IPV6 FIXED HEADER */
typedef struct tagIpv6hdr {
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    VOS_UINT32        traffic_class_1:4,
                 version:4,
                 flow_lbl_1:4,
                 traffic_class_2:4,
                 flow_lbl_2:16;
#else
    VOS_UINT32        version:4,
                 traffic_class:8,
                 flow_lbl:20;
#endif    

    VOS_UINT16       payload_len;
    UCHAR        nexthdr;
    UCHAR        hop_limit;

    in6_addr    saddr;
    in6_addr    daddr;
}VOS_PACKED IPV6HDR_S;


VOS_VOID IPV6_PerfActUserStatistic(VOS_UINT32 ulPerfType,VOS_UINT32 ulOper,VOS_UINT32 ulDomainIndex);
VOS_UINT16 IPV6_CalcCheckSum(VOS_UINT8 *ptr, in6_addr *pSrcAddr, in6_addr *pDesAddr, const VOS_UINT8 *msg, 
                                       VOS_UINT32 ulLen, VOS_UINT8 ucPro);
VOS_UINT16 IPV6_CalcCheckSumExten(in6_addr *pSrcAddr, in6_addr *pDesAddr, const VOS_UINT8 *msg, 
                                                    VOS_UINT32 ulLen, VOS_UINT8 ucPro);
VOS_UINT32  IPV6_StopTimer(VOS_UINT32 ulTimerId);
extern VOS_UINT32 Ipv6_A11NotifySendRa(VOS_UINT32 ulPdnIndex);

#endif
