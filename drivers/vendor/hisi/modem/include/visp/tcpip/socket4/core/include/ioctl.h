/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ioctl.h
*
*  Project Code: VISP1.5
*   Module Name: socket4 
*  Date Created: 2006-4-28
*        Author: l(48769)
*   Description: IO control functions
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _IOCTL_H
#define        _IOCTL_H

#ifdef    __cplusplus
extern    "C"{
#endif

LONG RT_IoCtl(SOCKET_S *,ULONG,CHAR *);
LONG MG_IoCtl(SOCKET_S *,ULONG,CHAR *);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
