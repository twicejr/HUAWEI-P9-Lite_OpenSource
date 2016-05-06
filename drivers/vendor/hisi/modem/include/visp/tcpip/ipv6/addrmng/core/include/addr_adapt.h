/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : addr_adapt.h
  Version       : IPBIRv1r3.IPV6.E001-ND-Host
  Author        : Sandeep71635
  Created       : 2007/10/30
  Last Modified :
  Description   : The file defines the types and macros for semaphore
                  protection in ADDR Component.
  Function List :
  History       :
  1.Date        : 2007/10/30
    Author      : Sandeep71635
    Modification: Created file

******************************************************************************/

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

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifndef __ADDR_ADAPT_H__
#define __ADDR_ADAPT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef _IPB_IR_IPV6BASIC_TAILOR_H
#error("you must include  ipbir_ipv6basic_tailor.h before including this file")
#endif


/* Internal Function API - Input Param - Check and Return */
#define IP6_ADDR_FUN_CHECK_AND_RETURN(m_condition, m_ulResult)          \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        return (m_ulResult);                                            \
    }                                                                   \
}

#define IP6_ADDR_FUN_CHECK_AND_RETURN_SEMFREE(m_condition, m_ulResult) \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        TCPIP_END_PT(g_ulSemForTightMods);                                 \
        return (m_ulResult);                                            \
    }                                                                   \
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __ADDR_ADAPT_H__ */

