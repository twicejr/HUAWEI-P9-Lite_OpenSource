
#ifndef        _SOCK_VAR_H
#define        _SOCK_VAR_H

#ifdef    __cplusplus
extern    "C"{
#endif


#include "tcpip/tcp4/core/include/tcp.h"
#ifndef MIN
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#endif  /* MIN */
#ifndef MAX
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#endif


extern TCB_S        *pTcbHead;        /* the task control block head    */
extern FILEOPS_S    *pFileOps;        /* pFileOps = &stFileOps */
extern FILEOPS_S     stFileOps;       /* file function */
extern ULONG         ulSbMax;         /* maximum size of socket recv and write buffer */
extern LONG          iselcoll;        /* select collection, the number of a socket being select */

/*********************************************************
*  for socket command line
*********************************************************/
/* Commented by x43050 2006-5-27 Defect ID: A82D01677 */
/* extern CHAR           stRemoteHostName[MAXHOSTNUM][HOSTINFOSTRLEN];*/
extern LONG        iRemoteHostTotal;
extern SOCKHOST_S  stHost[MAXHOSTNUM];

/********************************************************
*   used by TCPCtlInput and UDP_CtlInput()
********************************************************/
extern CHAR chInetCtlErrMap_a[];
extern INPCB_S         pcbTCPConnections; /* head of queue of active tcpcb's */
extern PCBHASH_S  g_stTcpHash;  /* tcp hash table structure */

/*********************************************************
*  for udp
*********************************************************/
/* extern long iUDPDebugFlags; hided by mayun */
extern INPCB_S   stUdb;
extern PCBHASH_S g_stUdpHash;

/*********************************************************
*  for rawip
*********************************************************/
extern INPCB_S stRawInPcb;

extern INADDR_S    stSockZeroInAddr;

extern SOCKDBUGFILTRD_S  g_stDbugSockFilter;

extern ULONG g_ulSockDbugFlag;
extern UCHAR g_aucSockLogSwitch[IPPROTO_MAX];

extern SOCKET_S stHeadCacheSocket ;

extern IP_SOCK_SH_CALLBACUP_SET_S g_stSOCK4CallBack;
extern SOCK_MOD_INFO_S g_stSOCK4ModInfo;

/*  VISP V100R005   2006-4-25   x43050  支持IPv6单独测试 */
extern ULONG  g_ulIsSOCKET4Enable;    /* 默认打开1   关闭0  */
extern ULONG  g_ulIsSOCKET6Enable;    /* 默认打开1   关闭0  */


extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl *g_pstSOCKAddr4Vtbl;
extern struct IIF_IPV4_IP_PP4_ComIntFUNVtbl *g_pstSOCKPP4Vtbl;
extern struct IIF_COMP_DNSC_ComIntFUNVtbl   *g_pstSOCKDNSCVtbl;

extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl *g_pstSOCKFIB4Vtbl;
extern struct IIF_COMP_PPP_ComIntFUNVtbl      *g_pstSOCKPPPVtbl;
extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl *g_pstSOCKETHARPVtbl;
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern struct IIF_VRF_ComIntFUNVtbl * g_pstSockVrfVtbl;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/* Begin:VISPV2R3C00 VRF6 abhishekmishraa , 2013-11-20 */
extern struct IIF_VRF6_ComIntFUNVtbl * g_pstSockVrf6Vtbl;
/* End:VISPV2R3C00 VRF6 abhishekmishraa , 2013-11-20 */

#define SOCK_ADDR_LEN 36

extern UCHAR g_aucSockAddr[SOCK_ADDR_LEN];

extern TCB_S *g_pstGlobalTcb;

extern TCP_SEQ ulISNOldOffset;
extern TCP_SEQ ulISNOffset;
extern struct IIF_IP6_SOCK_ComIntFUNVtbl        *g_pstSOCKET6Vtbl;
extern struct IIF_IP6_PMTU_ComIntFunVtbl        *g_pstSock4PmtuVtbl;
extern struct IIF_IP6_TCP6_ComIntFunVtbl        *g_pstSock4TCP6Vtbl;

extern struct IIF_IP4_TCP4_ComIntFunVtbl *g_pstSOCKTCP4FunVtbl; /* Added for SOCKET HA */

extern ULONG g_ulSockTcpAsyncComplSwitch;

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
