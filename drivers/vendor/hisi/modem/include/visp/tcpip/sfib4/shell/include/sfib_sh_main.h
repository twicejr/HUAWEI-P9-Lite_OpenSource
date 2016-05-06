/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib_sh_main.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB4
* Date Created: 2003-07-08
*       Author: Zhang Hongyan
*  Description: SFIBÄ£¿éshellº¯ÊýÉùÃ÷
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2003-07-08   Zhang Hongyan           Create
*  2006-03-30   Jiangtao                Adjust for D00646
*  2006-04-21   Jiangtao                Adjust for D00859 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _SFIB_SH_MAIN_H
#define _SFIB_SH_MAIN_H

extern ULONG getMainboardId ();

ULONG SFIB_RegApp ();
ULONG SFIB_FIBAgent_Init ();
ULONG SFIB_FIB4C_Init ();
ULONG SFIB_FIB6C_Init ();
ULONG SFIB_FIBA_WriteQueue(IP6_FIB_MSGHDR_S *pstRtMsgHead);
ULONG SFIB_FIBA_WriteEvent(ULONG ulEvType);
ULONG SFIB_FIBA_ReadQueue(IP6_FIB_MSGHDR_S *pstMsg);
VOID SFIB_FIBA_ShellDebugOut0(ULONG ulBoardId, FIB6A_DBG_INFO_E enState, ULONG ulMsgFmt);
VOID SFIB_FIB4C_ShellDebugOut0(FIB4C_DEBUG_INFO_E enState, char *pBuf, ULONG ulLen);
VOID SFIB_FIB6C_ShellDebugOut0(FIB6C_DEBUG_INFO_E enState, char *pBuf, ULONG ulLen);
ULONG SFIB_RM_Init();
extern ULONG TCPIP_IC_SendMsg(ULONG ulMid, ULONG ulInfoId, char *pBuf);

VOID SFIB4_SetDebugSwitch(ULONG ulDbg);
ULONG SFIB4_GetDebugSwitch(ULONG *pulDbg);
#endif
#ifdef __cplusplus
}
#endif

