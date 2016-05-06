/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_sh_init.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-23
*        Author: LY(57500)
*   Description: DHCP4R模块Shell部分的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-23  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP4R_SH_INIT_H_
#define _DHCP4R_SH_INIT_H_

#ifdef __cplusplus
extern "C"{
#endif

ULONG DHCP4R_SH_Init();
VOID DHCP4R_SH_DeInit(VOID);
VOID DHCP4R_Debug_Info(CHAR* szString);

#ifdef __cplusplus
extern }
#endif      /* end of __cplusplus  */

#endif      /* end of _DHCP4R_SH_INIT_H_ */

