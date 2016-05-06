/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Iping_inc.h
*
*  Project Code: VISP1.5
*   Module Name: ping  
*  Date Created: 2006-4-28
*        Author: luyao(60000758)
*   Description: Declare interface of PING 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _PING_INC_H_
#define _PING_INC_H_

#ifdef __cplusplus
extern "C" {
#endif
DECLARE_INTERFACE(IIF_PING_ComIntFUN) 
{

    IUNKNOWN_METHODS
    METHOD_(LONG, pfPING_DoPing)(ULONG ulExecID,Ping_Comm_S  *pPing6Param);  
    METHOD_(ULONG,pfPING_RegShellApi)(PING_CALLBACK_SET_S *pstPingCallBcakFun);    
    METHOD_(CHAR*, pfPIN_NToA)(ULONG ulAddr,CHAR szStrAddr[LEN_128]);    
};

DECLARE_INTERFACE( IIF_PING_ComIntCFG )
{
    IUNKNOWN_METHODS
    /* Methods provided to shell for com init, activate, and module info registration */
    METHOD_(ULONG, pfPING_InitCom)(COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
    METHOD_(ULONG, pfPING_ActivateCom)();
    METHOD_(ULONG, pfPING_SetModuleInfo)(PING_MOD_INFO_S  *pstMInfo);

    METHOD_(ULONG, pfPING_SetTos)(UCHAR ucTos);
    METHOD_(ULONG, pfPING_GetTos)(UCHAR *pucTos);
};


#ifdef __cplusplus
}
#endif

#endif


