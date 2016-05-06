/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iicmp.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: 声明icmp提供的的三个组件虚表
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理 
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_PP4_H_
#define _I_PP4_H_

/* icmp组件提供的组件虚表 */
extern IIF_IPV4_IP_ICMP_ComIntCFG g_IComInt_ICMP_CFG;
extern IIF_IPV4_IP_ICMP_ComIntFUN g_IComInt_ICMP_FUN;
extern IIF_IPV4_IP_ICMP_ComIntSSA g_IComInt_ICMP_SSA;

/* icmp模块信息 */
extern ComponentInfo m_CompIcmpInfo;

#endif  /*  _I_PP4_H_  */

#ifdef  __cplusplus
}
#endif

