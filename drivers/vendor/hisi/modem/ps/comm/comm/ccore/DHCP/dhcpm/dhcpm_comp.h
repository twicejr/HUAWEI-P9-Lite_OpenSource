#ifndef __DHCPM_COMP_H__
#define __DHCPM_COMP_H__

#ifdef PC_LINT
#define inline
#endif

extern PTM_COMPONENT_INFO_S g_stDhcpMCompInfo;
#define DHCPM_SELF_CSI       g_stDhcpMCompInfo.ullSelfCsi
#define DHCPM_SELF_CMPIDX    g_stDhcpMCompInfo.ulSelfCmpIdx
#define DHCPM_HANDLE         g_stDhcpMCompInfo.ulHandle

#define DHCPM_DHCPSERVER_LOCK_NAME "L_DHCP_SERVER"

#define DHCPM_ALARM_TIMER_LENGTH         1000            /*DHCP告警扫描定时器时长1s*/

#define DHCPM_SPINLOCK(SpinLockId)      PGP_SpinLockNoSchedule(SpinLockId);
#define DHCPM_SPINUNLOCK(SpinLockId)    PGP_SpinUnlockNoSchedule(SpinLockId);

#define DHCPM_ALARM_IPADDR_IPV4         4   /*上报告警地址类型为IPV4*/
#define DHCPM_ALARM_IPADDR_IPV6        6  /*上报告警地址类型为IPV6*/

typedef struct tagDHCP_SERVER_STATUS_MANAGER_S
{    
    DHCP_SERVER_STATUS_S *pstDhcpServerStatus;
    PGP_SPINLOCK_ID *pstlockSpinLockID;
}DHCP_SERVER_STATUS_MANAGER_S;

typedef struct tagDHCP_SERVER_CFG_MANAGER_S
{    
    LAP_DHCP_CFG_S *pstDhcpServer;
    MC_RWLOCK_ID RWLockId;
}DHCP_SERVER_CFG_MANAGER_S;


VOID DHCPM_AlarmTimerProc(VOID);
VOID DHCPM_CDBRegCallBack(VOID);
ULONG DHCPM_ModDhcpServerGroupNode(LAP_DHCP_CFG_S * pstDhcpServerGrpInfo);
ULONG DHCPM_RemoveDhcpServerByIndex(ULONG ulDhcpIndex);
/*m00221573  全文件pclint 2012-10-16 start*/
extern ULONG DHCPM_GetDhcpSrvCfgByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer);
extern inline ULONG DHCPM_GetRetransmitTimeOutByIndex(ULONG ulDhcpIndex, UCHAR *pucRetransmitTimeOut);
extern ULONG DHCPM_DbgInit(VOID);
extern VOID DHCPM_AlarmProcByDhcpServerIndex(ULONG ulDhcpIndex, ULONG ulAlarmDownFlg);
extern ULONG DHCPM_CommInit1(VOID);
extern ULONG DHCPM_CommInit3(VOID);
extern ULONG DHCPM_StartWorkProc(VOID);
/*m00221573  全文件pclint 2012-10-16 end*/
extern VOS_BOOL PSM_Inf_IsOnlySGRestarted(VOID);


#endif /* end of __DHCP_INC_H__ */
