/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ifib6c_inc.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2003-07-22
*       Author: Zhang Hongyan
*  Description: contain the core head file,when a file include this 
*               head file and contain all of file in core.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-22   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00645
*  2006-04-21   Jiangtao                Adjust for D00858 
*
*******************************************************************************/
 
#include "tcpip/public/tcpip_config.h"

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _IFIB6C_INC_H
#define _IFIB6C_INC_H

/* Note that we include fibagent header also since we have used, those types 
   in ifib6c.h, this wont be a problem, since fibagent is a compulsory 
   componentto be integrated in VRP, where as FibContainer is an option. */
#include "tcpip/ipv6/sfib6/core_fib6c/include/fib6c_def.h"
#include "tcpip/ipv6/sfib6/core_fib6c/include/fib6c_type.h"
#include "tcpip/ipv6/sfib6/core_fib6c/include/fib6c_frmwork.h"
#include "tcpip/ipv6/sfib6/core_fib6c/include/fib6c_implement.h"
#include "tcpip/ipv6/sfib6/core_fib6c/include/ifib6c.h"
#include "tcpip/ipv6/sfib6/core_fib6c/include/ifib6c_api.h"
#include "tcpip/ipv6/sfib6/core_fib6c/include/fib6c_core_api.h"

extern ComponentInfo *g_pCompFib6ContainerInfo;


#endif /*_IFIB6C_INC_H */

#ifdef  __cplusplus
}
#endif

