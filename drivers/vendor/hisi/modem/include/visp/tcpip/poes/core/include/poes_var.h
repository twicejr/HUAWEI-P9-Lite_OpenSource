/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_var.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POES模块的全局变量声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef  _POES_VAR_H_
#define  _POES_VAR_H_

#if __cplusplus
extern "C"{
#endif

/* POES模块信息 */
extern POES_MOD_INFO_S g_stPoesModInfo;

/* Core中使用的回调函数集 */
extern POES_SHELL_CALLBACK_SET_S g_stPoesShellApi; 

/* POES模块物理定时器ID */
extern ULONG g_ulPoesGlobalTimerId;

/* POES模块的IFNET组件功能虚表指针 */
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstPoesIfnetFunTable;

/* ACName */
extern UCHAR g_szACName[POES_ACNAME_MAX_LEN];

/* 全局session数 */
extern USHORT g_usSessionNum;

/* 全局session数限制 */
extern USHORT g_usMaxSession;

/* 本端MAC session数限制 */
extern USHORT g_usMaxSessionPerOurMac;

/* 对端MAC session数限制 */
extern USHORT g_usMaxSessionPerHisMac;

/* 全局调试信息开关 */
extern POES_DEBUG_INFO_S g_stPoesDbgInfo;

/* PPPoE连接LCP/IPCP UP/DOWN告警开关 */
extern ULONG g_ulPoesWarningSw;

/* POES控制块链表首节点 */
extern DLL_S g_stPoesCbList;

/* POES对端MAC控制块链表首节点 */
extern DLL_S g_stPoesHisMacList;

/* 获取ACName的钩子函数指针 */
extern GetACName_HOOK_FUNC g_pfGetACName_HOOK_FUNC;

#if __cplusplus
}
#endif

#endif 

