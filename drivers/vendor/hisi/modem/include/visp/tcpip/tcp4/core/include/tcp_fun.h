/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_fun.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4
*  Date Created: 2000-03-25
*        Author: Chen Bin
*   Description: TCP功能函数原型申明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2000-03-25  Chen Bin         Create the first version.
*
*******************************************************************************/

#ifndef _tcp_fun_h_
#define _tcp_fun_h_

#ifdef __cplusplus
extern "C"{
#endif

TCPMd5Pwd_S *TCPCreateMD5Node(SOCKMD5Pwd_EX_S *pSockPwd);

ULONG TCPDelAllPwdNode(TCPCB_S *pTCPCB);
ULONG TCPDelPwdNode(TCPCB_S *pTCPCB, ULONG ulIpAddr);

#define ISN_CHANGE_LIMIT   1000
#define ISN_SEC_SIZE       16

extern VOID TCPRandIsnSec();

/* Macros used for MD5 config. notify */
#define TCP_MD5_PASS_DEL 0
#define TCP_MD5_PASS_ADD 1
#define TCP_MD5_PASS_DEL_ALL 2

#define TCP_SOCK_CLOSE 3

VOID TCPIPMd5CfgNotify(TCPCB_S *pNwTCPCB, MBUF_S *p, UINT32 ulOperation);

ULONG TCPAddorModifyPwd(TCPCB_S *pTCPCB, SOCKMD5Pwd_EX_S *pSockPwd, ULONG ulFlag);
CHAR * TCPGetMd5PwdByIP(TCPCB_S *pTCPCB, ULONG ulIpAddr, ULONG *pulMask);

CHAR * TCPGetMd5PwdByIPAndMask(TCPCB_S *pTCPCB, ULONG ulIpAddr, ULONG ulMask);

ULONG IP4_TCP4_QueryInterface(IUnknown * This, COMP_IID iid, LPVOID *ppvObj);
ULONG TCP_Init_Com(const COM_ID_INFO_S * pstComInfo, ULONG  ulComLen);
ULONG TCP_Activate_Com ();
ULONG TCP_SetModuleInfo (TCP4_MOD_INFO_S *pstMInfo);
ULONG TCP_RegShellApi ( IP4_TCP4_SH_CALLBACUP_SET_S *pfCallBackSet);
ULONG TCP_ConnTableGetFirst(TCPMIBCONN_S *pMibEntry);
ULONG TCP_ConnTableGetNext(TCPMIBCONN_S *pMibEntry);
ULONG TCP_ConnTableMatch(TCPMIBCONN_S *pMibEntry);
VOID TCP_GetStatist(TCPSTAT_S *pstTCPStat);
VOID TCP_ClearStatist(VOID);
VOID TCP_SetFilterZero(VOID);
VOID TCP_SetFilterAll(VOID);
ULONG TCP_ProDbugFilter(ULONG ulFlag, ULONG ulFilterType,ULONG ulTaskId, ULONG ulSockId);
ULONG TCP_FindTCPCB(VOID *pAddress, TCPCB_INFO_S *pInfo);
VOID TCP_Get_Param(ULONG ulType, ULONG * pulValue);
ULONG TCP_Set_Param(ULONG ulType ,ULONG ulValue);
ULONG TCP_OpenObject(ULONG ulMainType, UINTPTR * pulHandle);
ULONG TCP_CloseObject(UINTPTR  ulHandle);
ULONG TCP_Get_Object_First(UINTPTR ulHandle, INPCB_INFO_S *pPCBInfo);
ULONG TCP_Get_Object_Next(UINTPTR ulHandle, INPCB_INFO_S *pPCBInfo);
VOID TCP_GetFilter(ULONG *pulDebugFlag,TCPDBUGFILTRD_S *pstPacketFilter, TCPDBUGFILTRD_S*pstEventFilter,TCPDBUGFILTRD_S *pstMD5Filter);

ULONG ImplTcpFactoryQueryInterface (IUnknown* This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplTcpFactoryCreateInstance (IComponentFactory * This,  COMP_IID iid, VOID ** ppvObj );

VOID  TCP_StateChangeOutput(TCPCB_S *pTCPCB, SHORT sNewState);
VOID TCP_TransaOutput(TCPCB_S *pTCPCB, const CHAR *szInfo, ULONG ulFlag);

CHAR * TCP_MD5Generate(CHAR * pszData1,ULONG ulLen1,CHAR * pszData2,ULONG ulLen2,
                               CHAR * pszData3,ULONG ulLen3,CHAR *pszData4,ULONG ulLen4,
                               CHAR * pszDigest);

struct tagQUEUE;
VOID TCP_RemQueue(struct tagQUEUE *pstFrag);
VOID TCP_InsQueue(struct tagQUEUE *pstFrag, struct tagQUEUE *pHead);

ULONG TCP_ClearTcbCache();
LONG TCP_SetRespondQuench(ULONG ulValue);

ULONG TCP_GetTcpHash(VOID **pstTcpHash);

VOID TCP_MD5Output(TCPCB_S *pTCPCB, const CHAR *szInfo);

extern ULONG TCP_GetPerTcp4ConnStats(TCP4CONN_S *pstConnInfo, TCP4PERSTAT_S *pstRetStats);
extern ULONG TCP_ResetPerTcp4ConnStats(TCP4CONN_S *pstConnInfo);

ULONG TCP_OpenTcpNetInfo(UINTPTR *pulHandle);
ULONG TCP_GetTcpNetInfo(UINTPTR ulWaitlist, TCPIP_TCPNETINFO_S *pstNetInfo);
ULONG TCP_CloseTcpNetInfo(UINTPTR ulWaitlist);

/*Added by wangtong207740, 基于socket id 获取对应的tcp报文统计, 2012/9/5 */
extern ULONG TCP_GetInfoBySocket(ULONG ulSocketId ,TCP_SOCK_INFO_S *pstTcpInfo);

/* Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */
extern ULONG TCP_GetTcpInfoBySocketNum(TCP_SOCK_INFO_S *pstTcpConStat, ULONG ulRetSize);
/* End of Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */
extern UINT32 TCPCOOKIE_CalcCookie(TCPCB_S *pTCPCB, TCPIPHDR_S *pRcvHeader, UINT16 *pu16MSS, UINT32 *pu32TimeStamp);
extern UINT32 TCPCOOKIE_ChkCookie(TCPCB_S *pTCPCB, TCPIPHDR_S *pRcvHeader, UINT16 *u16MSS);

extern ULONG TCPGetKeepIdle(VOID *pSocket);

/* Added by dutianyi00217007 for DTS2013121909156, 修改时延计算方式 */
VOID TCP_StatDelay(TCPCB_S *pTCPCB);
/* End of adding by dutianyi00217007 for DTS2013121909156, 修改时延计算方式 */

ULONG TCPNeedClose(VOID *pSocket);

#ifdef __cplusplus
}
#endif

#endif

