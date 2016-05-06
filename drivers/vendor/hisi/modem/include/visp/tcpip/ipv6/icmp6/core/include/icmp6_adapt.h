/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : icmp6_adapt.h
  Version       : Initial Draft
  Author        : Sandeep71635
  Created       : 2007/12/4
  Last Modified :
  Description   : Header file for adaptations like global semaphore
  Function List :
  History       :
  1.Date        : 2007/12/4
    Author      : Sandeep71635
    Modification: Created file

******************************************************************************/
#ifndef __ICMP6_ADAPT_H__
#define __ICMP6_ADAPT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef _IPB_IR_IPV6BASIC_TAILOR_H
#error("you must include  ipbir_ipv6basic_tailor.h before including this file")
#endif


#if (VRP_NO == TCPIP_IN_VRP) /*In VISP*/
#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)

#define IP6_ICMP6_NOTIFY_NP(ulOper, pvInfo) \
        ((g_pfIP6_ICMP6_PPIOperation)?(IP6_ICMP6_Notify_PPI(ulOper, \
                                pvInfo)): (VOS_OK))

#define IP6_ICMP6_IS_NP()         (g_pfIP6_ICMP6_PPIOperation != NULL)


#define IP6_ICMP6_NP_ADDSTATS(stNPICMP6Stat, stCPStats, stSum_DP_CP)               \
{                                                                                  \
    int i;                                                                         \
    (stSum_DP_CP).ulIcps_totaloutput                                               \
                = (stNPICMP6Stat).ulIcps_totaloutput                               \
                        + (stCPStats).ulIcps_totaloutput;                          \
    (stSum_DP_CP).ulIcp6s_error                                                    \
                = (stNPICMP6Stat).ulIcp6s_error                                    \
                    + (stCPStats).ulIcp6s_error;                                   \
    (stSum_DP_CP).ulIcp6s_canterror                                                \
                = (stNPICMP6Stat).ulIcp6s_canterror                                \
                    + (stCPStats).ulIcp6s_canterror;                               \
    for (i=0; i<256; ++i)                                                          \
    {                                                                              \
        (stSum_DP_CP).ulIcp6s_outhist[i]                                           \
                = (stNPICMP6Stat).ulIcp6s_outhist[i]                               \
                    + (stCPStats).ulIcp6s_outhist[i];                              \
    }                                                                              \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_noroute                \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_noroute        \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_noroute;       \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_admin                  \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_admin          \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_admin;         \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_beyondscope            \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_beyondscope    \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_beyondscope;   \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_addr                   \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_addr           \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_addr;          \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_reject_route           \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_reject_route   \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_dst_unreach_reject_route;  \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_packet_too_big                     \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_packet_too_big             \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_packet_too_big;            \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_time_exceed_transit                \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_time_exceed_transit        \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_time_exceed_transit;       \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_paramprob_header                   \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_paramprob_header           \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_paramprob_header;          \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_time_exceed_reassembly             \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_time_exceed_reassembly     \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_time_exceed_reassembly;    \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_paramprob_nextheader               \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_paramprob_nextheader       \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_paramprob_nextheader;      \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_paramprob_option                   \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_paramprob_option           \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_paramprob_option;          \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_redirect                           \
        = (stNPICMP6Stat).stIcp6s_outerrhist.ulIcp6errs_redirect                   \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_redirect;                  \
    (stSum_DP_CP).stIcp6s_outerrhist.ulIcp6errs_unknown                            \
        = stNPICMP6Stat.stIcp6s_outerrhist.ulIcp6errs_unknown                      \
            + (stCPStats).stIcp6s_outerrhist.ulIcp6errs_unknown;                   \
}

#else
#define IP6_ICMP6_NOTIFY_NP(ulOper, pvInfo) VOS_OK
#define IP6_ICMP6_IS_NP()         0
#define IP6_ICMP6_NP_ADDSTATS(stNPICMP6Stat, stCPStats, stSum_DP_CP)
#endif
#endif /*end of #if (VRP_NO == TCPIP_IN_VRP)*/

/* Internal Function API - Input Param - Check and Return */
#define IP6_ICMP6_FUN_CHECK_AND_RETURN(m_condition, m_ulResult)         \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        return (m_ulResult);                                            \
    }                                                                   \
}

#define IP6_ICMP6_INTFUN_CHECK_AND_RETURN(m_condition, m_ulResult)      \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        VOS_DBGASSERT(0);                                               \
        return (m_ulResult);                                            \
    }                                                                   \
}

#define IP6_ICMP6_NOTIFY_TOOBIG_INCOMING(m_pstMBuf, m_ulIfIndex) \
{ \
    if ((NULL != g_pstIP6_ICMP6_Flow_Callback) \
        && (NULL != g_pstIP6_ICMP6_Flow_Callback->pfICMP6_TooBigNotify)) \
    { \
        (VOID)g_pstIP6_ICMP6_Flow_Callback->pfICMP6_TooBigNotify(m_pstMBuf, m_ulIfIndex); \
    } \
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ICMP6_ADAPT_H__ */
