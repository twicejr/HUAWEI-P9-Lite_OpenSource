/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pmtu_adapt.h
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
#ifndef __PMTU_ADAPT_H__
#define __PMTU_ADAPT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef _IPB_IR_IPV6BASIC_TAILOR_H
#error("you must include  ipbir_ipv6basic_tailor.h before including this file")
#endif


#define IP6_PMTU_INTFUN_CHECK_AND_RETURN(m_condition, m_ulResult)       \
{                                                                       \
    if ((m_condition))                                                  \
    {                                                                   \
        VOS_DBGASSERT(0);                                               \
        return (m_ulResult);                                            \
    }                                                                   \
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __PMTU_ADAPT_H__ */

