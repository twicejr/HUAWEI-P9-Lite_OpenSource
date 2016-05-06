/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib6c_frmwork.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2004-07-08
*       Author: Zhang Hongyan
*  Description: This file contains the prototype declarations of the
*               functions in frmwork of FIB container    
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

#ifndef _FIB6C_FRMWORK_H
#define _FIB6C_FRMWORK_H

ULONG IP6_FIB_FrmWork_Init ();
ULONG IP6_FIB_Request (RTMSG6_S *pstRtMsg);
ULONG IP6_FIB_Request_PT(RTMSG6_S *pstRtMsg);
ULONG IP6_AllocValid (ROUTE6_S* stRoute6, BOOL_T bEnableRouteBal);            

ULONG IP6_FIBContainer_Init_Com (COM_ID_INFO_S *pstComInfo, ULONG  ulComLen);
ULONG IP6_FIBContainer_Activate_Com ();
ULONG IP6_FIBContainer_SetModuleInfo (IP6_FIBContainer_MOD_INFO_S *pstMInfo);
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
ULONG IP6_FIBContainer_RegShellApi ( IP6_FIBContainer_SHELL_EV_CALLBACUP_SET_S *pfCallBackSet);

#endif

#ifdef  __cplusplus
}
#endif

