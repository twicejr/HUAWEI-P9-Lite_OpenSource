/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              udp_cmd.h
*
*  Project Code: VISP1.5
*   Module Name: udp4
*  Date Created: 2004-04-25
*        Author: WeiYongDong
*   Description: UDP4配置接口需要的数据结构和宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-04-25  WeiYongDong      Create the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*  2006-05-11  luyao            为支持ARM CPU字节对齐特性，修改结构。
*  2008-01-16  w60786           Modify for A82D22576 增加UDP用户接口的函数原型声明
*
*******************************************************************************/

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

