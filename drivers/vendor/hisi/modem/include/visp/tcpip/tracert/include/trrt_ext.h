/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trrt_ext.h
*
*  Project Code: VISP1.5
*   Module Name: Traceroute Module 
*  Date Created: 2003-07-14
*        Author: Suraj( )
*   Description: This file contatins the declarations of the external interfaces used.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-07-14  Suraj( )         Creat the first version.
*
*******************************************************************************/

#ifndef _TRACERT_EXT_H_
#define _TRACERT_EXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_basefun.h"

/**************************************************************\
* 外部模块提供的接口函数声明
\**************************************************************/
extern struct hostent *gethostbyname6(CHAR *pName, ULONG ulPolicy);

#ifdef __cplusplus
}
#endif

#endif
