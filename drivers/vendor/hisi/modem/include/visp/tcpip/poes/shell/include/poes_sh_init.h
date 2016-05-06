/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_sh_init.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POES组件Shell部分头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/


#ifndef  _POES_SH_INIT_H_
#define  _POES_SH_INIT_H_

#ifdef __cplusplus
extern "C"{
#endif

/* poes_sh_init.c */
ULONG POES_Init(VOID);
VOID POES_DeInit();
ULONG POES_RegApp(VOID);
VOID POES_Debug_Info(CHAR* pcString);
ULONG POES_DropQueue(MBUF_S *pMBuf);
/* end of poes_sh_init.c */

#if __cplusplus
}
#endif

#endif

