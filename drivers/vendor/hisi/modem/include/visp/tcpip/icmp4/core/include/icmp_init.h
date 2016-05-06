/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_init.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: 声明了Icmp中的初始化函数和全局变量
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理 
*  2006-11-08   zhoutong(43740)         规范性整改
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _ICMP_INIT_H_
#define _ICMP_INIT_H_

/* ICMP4模块信息 */
extern IP_ICMP_MOD_INFO_S g_stIPIcmpModInfo;

/* ICMP4模块调试开关*/ 
extern ULONG   ulDebugIcmpFlag;

/* add by z62531,禁ping功能开关 */
extern ULONG g_ulPingForbidFlag;

/* 允许响应地址掩码请求报文开关 */
extern UCHAR   g_ucbIcmpMaskNotReply;

/* 源地址，目的地址 */
extern SOCKADDRIN_S g_stIcmpSrc;
extern SOCKADDRIN_S g_stIcmpDst;

/* ICMP依赖的组件虚表指针变量 */
extern struct IIF_IPV4_IP_PP4_ComIntFUNVtbl *g_pstIcmpPp4Vtbl;
extern struct IIF_IP4_RIP4_ComIntFunVtbl    *g_pstIcmpRip4Vtbl;
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl *g_pstIcmpAm4Vtbl;

#define ICMP_VRF_MID 0x00000003

/* 组件初始化函数 */
ULONG IP_ICMP_Init_Com(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen) ;
ULONG IP_ICMP_Activate_Com();
ULONG IP_ICMP_SetModuleInfo(IP_ICMP_MOD_INFO_S *pstModInfo );

#endif  /*  _ICMP_INIT_H_  */

#ifdef  __cplusplus
}
#endif

