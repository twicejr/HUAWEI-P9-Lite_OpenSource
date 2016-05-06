/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              udp_sh_init_api.h
*
*  Project Code: VISP1.5
*   Module Name: UDP4
*  Date Created: 2004-06-22
*        Author: WeiYongDong
*   Description: Initialize the shell and main loop process funtion apis
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-06-22  WeiYongDong      Create the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/


#ifndef _UDP_SH_INIT_API_H
#define _UDP_SH_INIT_API_H
         
#ifdef __cplusplus
extern "C"{
#endif


ULONG IP6_UDP6_SH_Init();
ULONG IP6_UDP6_SH_DeInit();

#ifdef __cplusplus
}
#endif

#endif
