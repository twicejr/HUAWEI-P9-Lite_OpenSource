/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.
               All Rights Reserved

 ******************************************************************************
  File Name     : nd_adapt.h
  Version       : IPBIRV100R003.IPv6.E001
  Author        : Sandeep71635
  Created       : 2007/10/30
  Last Modified :
  Description   : The file defines the types and macros for semaphore
                  protection in ND Component.
  Function List :
  History       :
  1.Date        : 2007/10/30
    Author      : Sandeep71635
    Modification: Created file

******************************************************************************/

#ifndef __ND_ADAPT_H__
#define __ND_ADAPT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef _IPB_IR_IPV6BASIC_TAILOR_H
#error("you must include  ipbir_ipv6basic_tailor.h before including this file")
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/* General Assert */
#define IP6_ND_ASSERT(m_exception)  VOS_DBGASSERT((m_exception))

/* Internal Function API - Input Param - Check and Return */
#define IP6_ND_INTFUN_CHECK_AND_RETURN(m_condition, m_ulResult)         \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        VOS_DBGASSERT(0);                                               \
        return (m_ulResult);                                            \
    }                                                                   \
}

#define IP6_ND_FUN_CHECK_AND_BREAK(m_condition)                         \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        break;                                                          \
    }                                                                   \
}

/* Internal Function API - Input Param - Check and Return */
#define IP6_ND_FUN_CHECK_AND_RETURN(m_condition, m_ulResult)            \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        return (m_ulResult);                                            \
    }                                                                   \
}

#define IP6_ND_FUN_CHECK_AND_RETURNVOID(m_condition)                    \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        return;                                            \
    }                                                                   \
}


#define IP6_ND_FUN_CHECK_AND_RETURN_SEMFREE(m_condition, m_ulResult) \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        TCPIP_END_PT(g_ulSemForTightMods);                                \
        return (m_ulResult);                                            \
    }                                                                   \
}



/****************************************************************************/
/* ND Host parameter pointer in ND_INFO Malloc and free Macros */
#define IP6_ND_HOSTPARAMS_MALLOC(m_pstHostParams)                     \
    (m_pstHostParams) = (IP6_ND_HOSTPARAMS_S *)IP6_ND_MALLOC          \
                (g_stNDModInfo.ulModID | SID_ND_HOSTPARAMS,         \
                sizeof(IP6_ND_HOSTPARAMS_S))

#define IP6_ND_HOSTPARAMS_FREE(m_pstHostParams)                       \
                IP6_ND_FREE((m_pstHostParams))

/****************************************************************************/
/* Destination Cache Node Malloc and free Macros */
#define IP6_ND_DESTINATIONCACHE_MALLOC(m_pstDestCache)                    \
    (m_pstDestCache) = (IP6_ND_DESTCACHE_ENTRY_S*) IP6_ND_MALLOC(         \
                (g_stNDModInfo.ulModID) | (SID_HOST_DEST_CACHE_NODE),     \
                sizeof (IP6_ND_DESTCACHE_ENTRY_S))

#define IP6_ND_DESTCACHE_FREE(m_pstDestCache)                             \
                IP6_ND_FREE((m_pstDestCache))

/****************************************************************************/
/* Interface Default Router Node malloc and Free macro */
#define IP6_ND_DEF_ROUTER_ENTRY_MALLOC(m_pstDefRtrNode)                   \
    (m_pstDefRtrNode) = (IP6_ND_DEFROUTER_LIST_S *)IP6_ND_MALLOC(         \
                (g_stNDModInfo.ulModID) | (SID_HOST_DEFROUTER_LIST),    \
                sizeof(IP6_ND_DEFROUTER_LIST_S))

#define IP6_ND_DEF_ROUTER_ENTRY_FREE(m_pstDefRtrNode)                     \
                IP6_ND_FREE((m_pstDefRtrNode))

/****************************************************************************/
/* Timer message Malloc and free Macros */
#define IP6_ND_HOST_TIMER_MSG_MALLOC(m_pstTmrMsg)                         \
    (m_pstTmrMsg) = (IP6_ND_HOST_TMRMSG_S *)IP6_ND_MALLOC(                \
                (g_stNDModInfo.ulModID) | (SID_HOST_TMRMSG),            \
                sizeof(IP6_ND_HOST_TMRMSG_S))

#define IP6_ND_HOST_TIMER_MSG_FREE(m_pstTmrMsg)                           \
                IP6_ND_FREE((m_pstTmrMsg))

/****************************************************************************/
/* Interface Prefix List node Malloc and Free Macros */
#define IP6_ND_PREFIX_ENTRY_MALLOC(m_pstPrefixNode)                       \
    (m_pstPrefixNode) = (IP6_ND_INTFPREFIX_LIST_S *)IP6_ND_MALLOC(        \
                (g_stNDModInfo.ulModID) | (SID_HOST_INTFPREFIX_LIST),   \
                sizeof(IP6_ND_INTFPREFIX_LIST_S))

#define IP6_ND_PREFIX_ENTRY_FREE(m_pstPrefixNode)                         \
                IP6_ND_FREE((m_pstPrefixNode))

/****************************************************************************/
/* Global Prefix List node Malloc and Free Macros */
#define IP6_ND_GBL_PREFIX_MALLOC(m_pstGblPrefix)                          \
    m_pstGblPrefix = (IP6_ND_GLOBALPREFIX_LIST_S *)IP6_ND_MALLOC(         \
                (g_stNDModInfo.ulModID) | (SID_HOST_GBLPREFIX_LIST),    \
                sizeof(IP6_ND_GLOBALPREFIX_LIST_S))

#define IP6_ND_GBL_PREFIX_FREE(m_pstGblPrefix)                            \
                IP6_ND_FREE((m_pstGblPrefix))

/****************************************************************************/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ND_ADAPT_H__ */

