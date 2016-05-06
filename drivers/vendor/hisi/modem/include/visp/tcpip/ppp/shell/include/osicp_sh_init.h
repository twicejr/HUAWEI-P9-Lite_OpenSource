/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              osicp_sh_init.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description: OSICP组件shell函数声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/

#ifndef _OSICP_SH_INIT_H_
#define _OSICP_SH_INIT_H_

#ifdef  __cplusplus
extern  "C"{
#endif

ULONG OSICP_SH_Init();
ULONG OSICP_SH_DeInit();
ULONG OSICP_RegApp();

extern struct ComponentInfo m_CompOsicpInfo;

#ifdef  __cplusplus
}
#endif

#endif
