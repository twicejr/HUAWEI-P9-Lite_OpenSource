/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib6c_def.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: Definitions of  macro and component interfaces
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00645
*  2006-04-21   Jiangtao                Adjust for D00858 
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _FIB6C_DEF_H
#define _FIB6C_DEF_H

#define FIB6C_TYPE_RPC_OPENROUTE        0x00000200
#define FIB6C_TYPE_RPC_GETROUTE         0x00000201
#define FIB6C_TYPE_RPC_CLOSEROUTE       0x00000202
#define FIB6C_TYPE_RPC_TOTALROUTE       0x00000203

#define FIB6C_MAX_DISP_SIZE             1000
#define IP6_ADDR_SIZE                   128
#define FIB6C_DEF_PREFIX_LEN            128

#define FIB6_REFRESHED                  FIB6_ERR + 30
#define FIB6_BALRT_ADDED                FIB6_ERR + 31

#define FIB6C_DEBUG_MAIN                0
#define FIB6C_DEBUG_IO                  1


/* module id definitions for Systrace */
#define SYSTRC_IPV6_FIBCONTR_BASE       00
#define IP6_FIBC_IMPL                   ((SYSTRC_IPV6_FIBCONTR_BASE << 8) + 010) 
#define IP6_FIBC_FRMWRK                 ((SYSTRC_IPV6_FIBCONTR_BASE << 8) + 011) 
#define IP6_FIBC_SH_CFG                 ((SYSTRC_IPV6_FIBCONTR_BASE << 8) + 012) 
#define IP6_FIBC_SH_INIT                ((SYSTRC_IPV6_FIBCONTR_BASE << 8) + 013) 

#define FIB6_RT_SUCCESS                 0
/* Note FIB6_ERR is 1 */

#define FIB6_NO_NEED_DELETE             0
#define FIB6_NEED_DELETE                1

#endif

#ifdef  __cplusplus
}
#endif

