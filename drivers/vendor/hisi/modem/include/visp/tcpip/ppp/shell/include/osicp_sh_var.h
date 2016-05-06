/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              osicp_sh_var.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description:  OSICP Shell 的全局变量声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/

#ifndef _OSICP_SH_VAR_H_
#define _OSICP_SH_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

extern struct IIF_OSICP_ComIntFUNVtbl          *g_pstOSICPComFUNTable;
extern struct IIF_OSICP_ComIntCFGVtbl          *g_pstOSICPComCFGTable;
extern struct IIF_OSICP_ComIntSSAVtbl          *g_pstOSICPComSSATable;

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif/* end of _OSICP_SH_VAR_H_ */
