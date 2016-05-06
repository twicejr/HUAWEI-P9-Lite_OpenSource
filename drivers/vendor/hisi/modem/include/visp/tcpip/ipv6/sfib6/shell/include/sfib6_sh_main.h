/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib6_sh_main.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2006-11-25
*       Author: zhoutong
*  Description: SFIB模块shell 函数原型声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-11-25   zhoutong                Create
*
*******************************************************************************/
#ifndef _SFIB6_SH_MAIN_H_
#define _SFIB6_SH_MAIN_H_

#ifdef    __cplusplus
extern "C"{
#endif

VOID SFIB6_SetDebugSwitch(ULONG ulDbg);
ULONG SFIB6_GetDebugSwitch(ULONG *pulDbg);

#ifdef __cplusplus
}
#endif

#endif /*_SFIB6_SH_MAIN_H_*/

