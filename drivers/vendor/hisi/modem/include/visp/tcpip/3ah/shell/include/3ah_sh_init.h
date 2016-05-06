/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_sh_init.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH 
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AH模块SHELL部分的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_SH_INIT_H_
#define _3AH_SH_INIT_H_

#ifdef __cplusplus
extern "C"{
#endif


ULONG OAM_3AH_SH_Init(VOID);
VOID OAM_3AH_RegApp(VOID);
VOID OAM_3AH_DeInit(VOID);
VOID OAM_3AH_DebugOutString(CHAR* szString);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus       */

#endif      /* end of _3AH_SH_INIT_H_   */

