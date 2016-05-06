/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock6_deb.h
*
*  Project Code: VISP1.5
*   Module Name: Socket6
*  Date Created: 2006-4-29
*        Author: luyao(60000758)
*   Description: socket6调试信息
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-29   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef  _SOCK6_DEB_H
#define  _SOCK6_DEB_H

#ifdef __cplusplus
extern    "C"{
#endif



extern SOCKDBUGFILTRD_S  g_stDbugSock6Filter;  /* socket6过滤条件 */
extern ULONG             g_ulSock6DbugFlag ;   /* socket6调试信息开关 */

extern CHAR *SOCK6_SprintSockPair(IN6PCB_S *pIN6PCB, CHAR *pRet);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif

