/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_sh_var.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-08
 *        Author: YaoChengLiang
 *   Description: MP Shell 的全局变量声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-08      YaoChengLiang   Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *
 *************************************************************************/

#ifndef _MP_SH_VAR_H_
#define _MP_SH_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif


/* component fun & cfg & ssa interface vtbl of MP used by shell */
extern struct IIF_MP_ComIntFUNVtbl          *g_pstMPComFUNTable;
extern struct IIF_MP_ComIntCFGVtbl          *g_pstMPComCFGTable;
extern struct IIF_MP_ComIntSSAVtbl          *g_pstMPComSSATable;

/* component fun interface vtbl of PPPoE Client used by MP shell */
extern struct IIF_PPPOE_CLIENT_ComIntFUNVtbl*g_pstMpPoecComFunTable;

/* MP 错误码的英文信息 */
extern CHAR *Inf_MP_Err_En[];


#ifdef __cplusplus
}
#endif

#endif
