/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              filevar.h
*
*  Project Code: VISP1.5
*   Module Name: socket4   
*  Date Created: 2006-4-28
*        Author: l(48769)
*   Description: kenel functions to operate file or socket 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _FILEVAR_H
#define        _FILEVAR_H

#ifdef    __cplusplus
extern    "C"{
#endif

LONG SOO_Close(FILE_S *);
LONG SOO_Read(FILE_S *, UIO_S * );    
LONG SOO_Write(FILE_S *, UIO_S * );
LONG SOO_Select(TCB_S *, FILE_S *, LONG ); /*Modified by x36317 for SWFD07933*/
LONG SOO_Ioctl(FILE_S *,  ULONG , CHAR * );

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */


#endif
