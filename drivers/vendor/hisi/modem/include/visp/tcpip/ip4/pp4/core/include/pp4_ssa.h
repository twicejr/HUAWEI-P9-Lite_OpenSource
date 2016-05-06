/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_ssa.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: pp4_ssa.c头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-01   zhoutong(43740)         规范性整改
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_SSA_H_
#define _PP4_SSA_H_


/* 回调函数 */
extern IP_PP4_IC_CALLBACK_SET_S g_stPp4ICCallbacks;
/* 注册回调函数 */
extern ULONG IP_PP4_RegisterICCallbacks(IP_PP4_IC_CALLBACK_SET_S *pstICCallback);



#endif  /* _PP4_SSA_H_  */

#ifdef  __cplusplus
}
#endif


