/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_sh_init.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk  
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunk模块Shell部分的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_SH_INIT_H_
#define _TRUNK_SH_INIT_H_

#ifdef __cplusplus
extern "C"{
#endif

/* trunk_sh_init.c */
ULONG TRUNK_Init(VOID);
ULONG TRUNK_RegApp(VOID);
VOID TRUNK_Debug_Info(CHAR* pcString);
ULONG TRUNK_DropQueue(MBUF_S *pMBuf);
ULONG TRUNK_DoNothing(MBUF_S *pMBuf);

/* end of trunk_sh_init.c */

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_SH_INIT_H_ */

