/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_ssa.h
*
* Project Code: VISPV100R005
*  Module Name: AM4  
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: 定义了AM4中SHELL的函数
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理 
*
*******************************************************************************/
 
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_SSA_H_
#define _AM4_SSA_H_

/* declare of callback set variable */
extern AM4_SHELL_HA_CALLBACK_FUNC_SET_S g_stAm4ShHACallback;
extern IP_AM4_IC_CALLBACK_SET_S g_stAm4ICCallbacks;

ULONG IP_AM4_RegisterShHACallback(AM4_SHELL_HA_CALLBACK_FUNC_SET_S *pstCallback);
ULONG IP_AM4_RegisterICCallbacks(IP_AM4_IC_CALLBACK_SET_S *pstICCallback);

ULONG IP_PlugIn(IFNET_S *pstIf);
ULONG IP_PlugOut(IFNET_S *pstIf);


#endif  /* end of _AM4_SSA_H_ */ 

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

