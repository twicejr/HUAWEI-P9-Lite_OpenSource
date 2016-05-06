/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_sh_init.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG适配初始化头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_SHINIT_H
#define _1AG_SHINIT_H

#ifdef  __cplusplus
    extern "C"{
#endif

extern VOID OAM_1AG_DebugInfo(CHAR* pcString);
extern ULONG OAM_1AG_Init(VOID);
extern ULONG OAM_1AG_RegApp(VOID);

#ifdef  __cplusplus
}
#endif

#endif

