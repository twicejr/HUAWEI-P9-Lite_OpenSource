/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_var.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: PPPMUX组件私有全局变量的引用说明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/

#ifndef _PPPMUX_VAR_H_
#define _PPPMUX_VAR_H_

#ifdef  __cplusplus
extern "C"{
#endif


extern PPPMUX_MOD_INFO_S        g_stPPPMUXModInfo;
extern PPPMUX_SHELL_CALLBACK_S  g_stPPPMUXShellApi; 

extern struct IIF_IFNET_ComIntFUNVtbl       *g_pstPppMuxIfnetFunTable;
extern struct IIF_COMP_PPP_ComIntFUNVtbl    *g_pstPppMuxPppFunTable;

extern DLL_S g_stPPPMUXPppInfoList; 

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _PPPMUX_VAR_H_ */
