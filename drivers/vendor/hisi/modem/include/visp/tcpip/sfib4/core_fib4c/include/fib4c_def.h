/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib4c_def.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: Definitions of  macro and component interfaces
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIB4C_DEF_H
#define _FIB4C_DEF_H

#include "sfib4/include/sfib4_api.h"

#define FIB4C_TYPE_RPC_OPENROUTE        0x00000200
#define FIB4C_TYPE_RPC_GETROUTE         0x00000201
#define FIB4C_TYPE_RPC_CLOSEROUTE       0x00000202
#define FIB4C_TYPE_RPC_TOTALROUTE       0x00000203

#define FIB4C_MAX_DISP_SIZE             10
#define IP4_ADDR_SIZE                   32
#define FIB4C_DEF_PREFIX_LEN            32

#define FIB4_REFRESHED                  FIB4_ERR + 30
#define FIB4_BALRT_ADDED                FIB4_ERR + 31

#define FIB4C_DEBUG_MAIN                0
#define FIB4C_DEBUG_IO                  1


/* module id definitions for Systrace */
#define SYSTRC_IPV4_FIBCONTR_BASE       00
#define IP4_FIBC_IMPL                   ((SYSTRC_IPV4_FIBCONTR_BASE << 8) + 010) 
#define IP4_FIBC_FRMWRK                 ((SYSTRC_IPV4_FIBCONTR_BASE << 8) + 011) 
#define IP4_FIBC_SH_CFG                 ((SYSTRC_IPV4_FIBCONTR_BASE << 8) + 012) 
#define IP4_FIBC_SH_INIT                ((SYSTRC_IPV4_FIBCONTR_BASE << 8) + 013) 

#define FIB4_RT_SUCCESS                 0
/* Note FIB4_ERR is 1 */

#endif

#ifdef  __cplusplus
}
#endif
