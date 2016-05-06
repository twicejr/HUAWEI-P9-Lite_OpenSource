/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_sh_cfg.h
*
*  Project Code: VISP1.5
*   Module Name: socket4   
*  Date Created: 2006-4-28
*        Author: l(48769)
*   Description: socket shell 相关信息
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28  l(48769)         Creat the first version.
*
*******************************************************************************/

#ifndef SOCK_SH_CFG
#define SOCK_SH_CFG

#ifdef __cplusplus
extern "C"{
#endif

#define CMOTABID_SOCK    0x03

enum enum_SOCK 
{
    SOCK_CMDELEMENT_TCPCFG, 
    SOCK_CMDELEMENT_TIMER,    
    SOCK_CMDELEMENT_SYNTIME, 
    SOCK_CMDELEMENT_INTEGER2_600, 
    SOCK_CMDELEMENT_FINWAIT, 
    SOCK_CMDELEMENT_INTEGER76_3600, 
    SOCK_CMDELEMENT_WINSIZE, 
    SOCK_CMDELEMENT_INTEGER1_32, 
    SOCK_CMDELEMENT_TCPDBUG, 
    SOCK_CMDELEMENT_TCPPKT, 
    SOCK_CMDELEMENT_TCPTSC, 
    SOCK_CMDELEMENT_TCPMD5, 
    SOCK_CMDELEMENT_TCPSHOW, 
    SOCK_CMDELEMENT_TCPBRIEF, 
    SOCK_CMDELEMENT_UDP, 
    SOCK_CMDELEMENT_IP, 
    SOCK_CMDELEMENT_HOST, 
    SOCK_CMDELEMENT_WORD1_20, 
    SOCK_CMDELEMENT_IPADDR, 
    SOCK_CMDELEMENT_HOSTS,
    SOCK_CMDELEMENT_TASKID,    
    SOCK_CMDELEMENT_SOCKID,
    SOCK_CMDELEMENT_TCPSTAT,
    SOCK_CMDELEMENT_TCPCB,
    SOCK_CMDELEMENT_TCPCBADDR,
    SOCK_CMDELEMENT_UDPPKT,
    SOCK_CMDELEMENT_IPDBUG,
    SOCK_CMDELEMENT_SOCKET,
    SOCK_CMDELEMENT_SOCKETSHOW,
    SOCK_CMDELEMENT_SOCKTYPE,
    SOCK_CMDELEMENT_SOCKTYPE_INTEGER1_3,
    SOCK_CMDELEMENT_SHOWIP,
    SOCK_CMDELEMENT_UDPSHOW,
    SOCK_CMDELEMENT_UDPSTAT
    
};

/**********************************************************************/
/* for socket command line : the value of byWitch in function ShowHost*/
/**********************************************************************/
#define SOCK_SHOWHOST_ALL          0


VOID SOCK6_SH_RegToIC( VOID );
VOID SOCK_RegToCmdLine();
VOID SOCK_SH_RegToIC( VOID );

ULONG SOCK_RegBuildRun();

VOID SOCK_ShowIpSocket(ULONG ulSockType, ULONG ulTaskId, ULONG ulSockId,ULONG ulExecID_SOCK);

ULONG SOCK_SH_GetHostName(CHAR *pName, LONG iNameLen);
VOID  SOCK_ShowTCB(ULONG ulTaskId);
VOID  SOCK_ShowSockInfo(ULONG ulTaskId, ULONG iFd);
VOID  SOCK_ShowSockBufInfo(ULONG ulTaskId, ULONG iFd, ULONG ulBufType);
VOID SOCK_ShowMGInfoBySock(ULONG ulTaskId, LONG lSockId);
/* Add for DTS2011041801697, by z00166124, at 2011-04-22. 修改原因: 增加显示接口 */
VOID  SOCK_ShowISISInfoBySock(ULONG ulTaskId, LONG lSockId);

VOID *SOCK_GetNextQ0Socket(VOID *pParam, VOID **pNewParam);
VOID *SOCK_GetNextQSocket(VOID *pParam, VOID **pNewParam);
ULONG SOCK_GetPQ0Info(LONG lFd , SOCKPQINFO_S *pstSockPQInfo);
ULONG SOCK_OpenPQ0Entry (LONG lFd ,UINTPTR *pulWaitListHandle);
ULONG SOCK_GetPQ0Entry(UINTPTR ulWaitListHandle, SOCKPQNODEINFO_S *pstSockPQNodeInfo);
ULONG SOCK_ClosePQ0Entry(UINTPTR ulWaitListHandle);
ULONG SOCK_GetPQInfo(LONG lFd , SOCKPQINFO_S *pstSockPQInfo);
ULONG SOCK_OpenPQEntry (LONG lFd ,UINTPTR *pulWaitListHandle);
ULONG SOCK_GetPQEntry(UINTPTR ulWaitListHandle, SOCKPQNODEINFO_S *pstSockPQNodeInfo);
ULONG SOCK_ClosePQEntry(UINTPTR ulWaitListHandle);
ULONG SOCK_GetSockResourceStatus(ULONG *pulTotalNum, ULONG *pulUsedNum);

#ifdef __cplusplus
}
#endif

#endif
