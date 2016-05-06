#ifndef __DHCPM_INTERFACE_H__
#define __DHCPM_INTERFACE_H__

#if 0
typedef struct tagDHCP_SERVER_STATUS_S
{
    PGP_SPINLOCK_ID stSpinLockId;

    UCHAR   ucPrimarySrvStatus:3;
    UCHAR   ucPrimarySrvTest:1;
    UCHAR   ucSecondarySrvStatus:3;
    UCHAR   ucSecondarySrvTest:1;
    UCHAR   ucPrimSrvTimerStatus;       /* 主用服务器状态扫描定时器状态 */
    UCHAR   ucPrimTimeoutNum;           /* 主服务器闪断告警计数 */
    UCHAR   ucSecTimeoutNum;            /* 备服务器闪断告警计数 */

    USHORT  usPrimTryTimeInterval;      /* 主服务器变为Try的剩余时间 */
    USHORT  usSecTryTimeInterval;       /* 备服务器变为Try的剩余时间 */

    UCHAR   ucPrimRequestTimeout;
    UCHAR   ucSecRequestTimeout;
    UCHAR   ucPrimaryAlarmFlag:1;       /* 主服务器已经发送过链路断告警的标志 */
    UCHAR   ucSecondaryAlarmFlag:1;     /* 已经发送过链路断告警的标志 */
    UCHAR   ucResBit:6;               /* 保留字段 */
    UCHAR   ucReserve;            /* 保留字段 */
}DHCP_SERVER_STATUS_S;
#endif

#define DHCPM_MAX_REQUEST_TIMEOUT_NUM 5

extern DHCP_SERVER_STATUS_S *g_pstDhcpServerStatus;

ULONG DHCPM_GetDhcpSrvCfgByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer);
ULONG DHCPM_GetDhcpSrvCfgStatusByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer,
                                       DHCP_SERVER_STATUS_S *pstDhcpServerStatus);
ULONG inline DHCPM_SetPrimarySrvStatusByIndex(ULONG ulDhcpIndex, ULONG ulValue);
ULONG inline DHCPM_SetPrimarySrvTestByIndex(ULONG ulDhcpIndex, ULONG ulValue);
ULONG inline DHCPM_SetSecondarySrvStatusByIndex(ULONG ulDhcpIndex, ULONG ulValue);
ULONG inline DHCPM_SetPrimSrvTimerStatusByIndex(ULONG ulDhcpIndex, UCHAR ucValue);
ULONG inline DHCPM_SetPrimTimeoutNumByIndex(ULONG ulDhcpIndex, UCHAR ucValue);
ULONG inline DHCPM_SetSecTimeoutNumByIndex(ULONG ulDhcpIndex, UCHAR ucValue);
extern ULONG DHCPM_RegDhcpServer();
extern ULONG inline DHCPM_GetRetransmitCfgByIndex(ULONG ulDhcpIndex, UCHAR *pucRetransmitNum, UCHAR *pucRetransmitTimeOut);
extern ULONG inline DHCPM_TrySetPrimStatusAbnormalByIndex(ULONG ulDhcpIndex);
extern ULONG inline DHCPM_TrySetSecStatusAbnormalByIndex(ULONG ulDhcpIndex);
/*m00221573 全文件pclint 2012-10-15 start*/
extern ULONG DHCPM_GetDhcpSrvStatusByIndex(ULONG ulDhcpIndex, DHCP_SERVER_STATUS_S *pstDhcpServerStatus);
/*m00221573 全文件pclint 2012-10-15 end*/
#endif /* end of __DHCP_INC_H__ */
