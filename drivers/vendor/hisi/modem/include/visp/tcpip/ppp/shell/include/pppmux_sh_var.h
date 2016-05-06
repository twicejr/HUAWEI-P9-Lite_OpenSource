/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_sh_var.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: PPPMUX Shell 的全局变量声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/

#ifndef _PPPMUX_SH_VAR_H_
#define _PPPMUX_SH_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

extern struct IIF_PPPMUX_ComIntFUNVtbl          *g_pstPPPMUXComFUNTable;
extern struct IIF_PPPMUX_ComIntCFGVtbl          *g_pstPPPMUXComCFGTable;
extern struct IIF_PPPMUX_ComIntSSAVtbl          *g_pstPPPMUXComSSATable;

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif/* end of _PPPMUX_SH_VAR_H_ */
