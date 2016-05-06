/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              eth_sh_main_cen.h
*
*  Project Code: VISPV100R005
*   Module Name: Etharp 
*  Date Created: 2004-7-7
*        Author: Zhang Hongyan(19316)
*   Description: 以太ARP模块的SHELL的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-7-7  Zhang Hongyan(19316)  Create the first version.
*  2006-4-27 wang xin(03278)       根据编程规范，对文件进行规范化整理
*******************************************************************************/

#ifdef    __cplusplus
extern    "C"{
#endif

#ifndef _ETH_SH_MAIN_CEN_H
#define _ETH_SH_MAIN_CEN_H

ULONG ETHARP_Init();
VOID ETHARP_CreateArpTimer(VOID * timerList, VOID  (*pfTimerFunc)(VOID *), ULONG *pulTimerId);
VOID ETHARP_DebugOutbut(CHAR *pBuf, ULONG ulLen);
ULONG ETHARP_DropQueue(MBUF_S *pMBuf);
extern ULONG TCPIP_IC_SendMsg(ULONG ulMId, ULONG ulInfoId, char *pBuf);
#endif


#ifdef    __cplusplus
}
#endif


