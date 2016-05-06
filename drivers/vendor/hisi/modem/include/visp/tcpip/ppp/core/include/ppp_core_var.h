/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              ppp_core_var.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2004-07-01
 *        Author: YiAn
 *   Description: PPP全局及外部变量的声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004-07-01      YiAn            Create
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *
 *************************************************************************/ 

#ifndef _PPP_CORE_VAR_H_
#define _PPP_CORE_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

/*全局及外部变量的声明*/

/*ppp模块对外告警功能定时器*/
extern ULONG g_ulPPPNegTimerId;
/*用户指定的协商时间*/
extern ULONG g_ulPPPNegTime;
/*物理定时器超时时间*/
extern ULONG g_ulOutTime;

extern ULONG g_ulPPPLoopBackTime;

extern struct IIF_IFNET_ComIntFUNVtbl  *g_pstCoreIFNETFUNTable;
extern struct IIF_IFNET_ComIntCFGVtbl  *g_pstCoreIFNETCFGTable;
extern struct IIF_IP4_SOCK_ComIntFunVtbl *g_pstPppSockFunTable;

extern struct  IIF_COMP_PPP_ComIntCFGVtbl  *g_pstPPPCFGTable;  
extern struct  IIF_COMP_PPP_ComIntSSAVtbl  *g_pstPPPSSATable;
extern struct  IIF_COMP_PPP_ComIntFUNVtbl  *g_pstPPPFUNTable;

extern struct IIF_MP_ComIntFUNVtbl *g_pstPppMpFunTable;/*MP fun接口*/
extern struct IIF_MP_ComIntCFGVtbl *g_pstPppMPComCFGTable;

extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl *g_pstPppAM4FunTable ;

extern PPP_MOD_INFO_S g_stPPPModInfo;
extern PPP_SHELL_CALLBACK_SET_S g_stPPPShellFun;

extern struct IIF_COMP_IPHC_ComIntFUNVtbl *g_pstCoreIPHCFUNTable;
extern struct IIF_COMP_IPHC_ComIntCFGVtbl *g_pstCoreIPHCCFGTable;

extern struct IIF_PPPMUX_ComIntFUNVtbl *g_pstPppMuxFunTable;
extern struct IIF_OSICP_ComIntFUNVtbl *g_pstOsicpFunTable;

/* 控制块链表指针 */
extern DLL_S g_stPppInfoDLL ;

/* debug开关使用的变量 */
extern struct tagPppDebugInfo g_stPppDebugInfo ;
extern PPP_SUBMOD_CALLBACK_S g_stPppSubModCallBack;

extern ULONG g_ulPPPRestanmitDelay;

#ifdef __cplusplus
}
#endif

#endif
