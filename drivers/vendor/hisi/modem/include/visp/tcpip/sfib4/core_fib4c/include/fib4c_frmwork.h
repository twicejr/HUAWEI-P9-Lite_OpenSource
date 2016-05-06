/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              fib4c_frmwork.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: This file contains the prototype declarations of the
*               functions in frmwork of FIB container
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

#ifndef _FIB4C_FRMWORK_H
#define _FIB4C_FRMWORK_H

ULONG IP4_FIB_FrmWork_Init ();
ULONG IP4_FIB_Request (RTMSG4_S *pstRtMsg);
ULONG IP4_AllocValid (ROUTE4_S* stRoute4);            
ULONG IP4_AllocValid_ForInternal (ROUTE4_S* stRoute4);  


ULONG IP4_FIBContainer_Init_Com (COM_ID_INFO_S *pstComInfo, ULONG  ulComLen);
ULONG IP4_FIBContainer_Activate_Com ();
ULONG IP4_FIBContainer_SetModuleInfo (IP4_FIBContainer_MOD_INFO_S *pstMInfo);
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
ULONG IP4_FIBContainer_RegShellApi (IP4_FIBContainer_SHELL_EV_CALLBACUP_SET_S *pfCallBackSet);


#endif

#ifdef  __cplusplus
}
#endif

