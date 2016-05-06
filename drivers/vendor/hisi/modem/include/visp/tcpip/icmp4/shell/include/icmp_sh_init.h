/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_sh_init.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: shell初始化相关的宏定义和变量声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
 
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ICMP_SH_INIT_H_
#define _ICMP_SH_INIT_H_

#define IP_ICMP_SH_INIT         ((SYSTRC_IP_ICMP_BASE << 8) + 40) 
#define IP_ICMP_SH_IC           ((SYSTRC_IP_ICMP_BASE << 8) + 41) 


extern struct IIF_IPV4_IP_ICMP_ComIntCFGVtbl *g_pstShIcmpCfgVtbl;


#endif  /* end of _ICMP_SH_INIT_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

