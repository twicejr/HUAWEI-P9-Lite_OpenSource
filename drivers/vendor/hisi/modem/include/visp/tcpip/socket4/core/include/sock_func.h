/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_func.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket functions
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _SOCK_FUNC_H
#define        _SOCK_FUNC_H

#ifdef    __cplusplus
extern    "C"{
#endif

LONG    CheckTcb(ULONG ,struct tagTCB ** );
LONG    CreateTcb(ULONG ,struct tagTCB ** );
LONG    CreateGlobalTcb();

LONG    DeleteTcb(ULONG);
LONG    WaitEvent(ULONG,SHORT);
LONG    WakeUp(ULONG, ULONG );
LONG    TSleep(ULONG, ULONG );
/*LONG     TSleepConnect(ULONG,SHORT);*/
LONG    TSleepConnect(SHORT);

VOID    SelWakeUp(SOCKBUF_S *,LONG);
VOID    SoWakeUp(SOCKET_S *, LONG );
LONG    SB_Wait(SOCKET_S *,LONG);


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

