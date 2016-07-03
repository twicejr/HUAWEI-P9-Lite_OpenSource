

#ifndef _UDP_CMD_H_
#define _UDP_CMD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define UDP_FILT_PERMIT     0
#define UDP_FILT_DENY       1

typedef struct tagUDPMIBCONN
{
    ULONG  ulLAddr;
    USHORT usLPort;
    UCHAR  ucPadding[2];
} UDPMIBCONN_S;


ULONG  UDP_ClassifyDbugFilt(UDP_DEBUGFILTER_S *pstDbugFiltRd, ULONG ulTaskId, ULONG ulSockId);
VOID UDP_SetFilterZero(VOID);
VOID UDP_SetFilterAll(VOID);
ULONG UDP_SetFilter(ULONG ulFlag, ULONG ulTaskId, ULONG ulSockId);
VOID UDP_GetFilter(ULONG *pulDebugFlag,UDP_DEBUGFILTER_S *pstUdpFilter);
VOID UDP_GetStatistics(UDPSTAT_S *pstUDPStat);
VOID UDP_ClearStatistics(VOID);
ULONG UDP_ClearSFIBCache(VOID);
VOID UDP_Input( MBUF_S *pMBuf, LONG nIpHLen);
ULONG UDP4_Process_For_InterMediate(MBUF_S *pMBuf, LONG nIpHLen);
ULONG OPTIM_UdpInput(MBUF_S * pstMbuf, LONG iFd);
ULONG UDP_GetPerUdp4ConnStats(UDP4CONN_S *pstConnInfo, UDP4PERSTAT_S  *pstRetStats);
ULONG UDP_ResetPerUdp4ConnStats(UDP4CONN_S *pstConnInfo);

ULONG UDP_OpenUdpNetInfo(UINTPTR *pulWaitlist);
ULONG UDP_GetUdpNetInfo(UINTPTR ulWaitlist , TCPIP_UDPNETINFO_S *pstNetInfo);
ULONG UDP_GetBFDNetInfo(TCPIP_UDPNETINFO_S *pstNetInfo);
ULONG UDP_CloseUdpNetInfo(UINTPTR ulWaitlist);


#ifdef __cplusplus
}
#endif

#endif /* _UDP_CMD_H_ */

