/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_sh_init.h
*
* Project Code: VISPV100R005
*  Module Name: PP4
* Date Created: 2002-06-18
*       Author: chenshuanglong(28510)
*  Description: PP4模块shell初始化相关的宏定义，结构体，变量和函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-07   zhoutong(43740)         规范性整改
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _PP4_SH_INIT_H_
#define _PP4_SH_INIT_H_


/* define the max cli notify counts */
#define MAX_IP_PP4_COMPONENTS       10


/* SYSTRACE id */
#define IP_PP4_SH_CONFIG    ((SYSTRC_IP_PP4_BASE << 8) + 40) 
#define IP_PP4_SH_IC        ((SYSTRC_IP_PP4_BASE << 8) + 42)
#define IP_PP4_SH_INIT      ((SYSTRC_IP_PP4_BASE << 8) + 43) 
#define IP_PP4_SH_LCS       ((SYSTRC_IP_PP4_BASE << 8) + 44) 
#define IP_PP4_SH_SSA       ((SYSTRC_IP_PP4_BASE << 8) + 45) 

/* Global CLI state flag */
extern ULONG g_ulIPPp4CliState;

/* vtables of pp4 component */
extern struct IIF_IPV4_IP_PP4_ComIntSSAVtbl  *g_pstShPp4SSAVtbl;
extern struct IIF_IPV4_IP_PP4_ComIntCFGVtbl  *g_pstShPp4CfgVtbl;
extern struct IIF_IPV4_IP_PP4_ComIntFUNVtbl  *g_pstShPp4FunVtbl;


#endif  /* end of _PP4_SH_INIT_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */


