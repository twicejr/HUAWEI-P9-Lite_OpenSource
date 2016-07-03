
#ifndef __DHCPC_VAR_H__
#define __DHCPC_VAR_H__


extern ULONG   g_ulCtrlblkXaxis;
extern ULONG   g_ulCtrlblkYaxis;

extern VOID    *g_pulSDDhcpMCQueID        ;
extern VOID    *g_pulSDDhcpv6cMcQueId;
extern VOID    *g_pulDHCP_LAP2_RSPQueID   ;
extern VOID    *g_pulDHCP_LAP2_REQQueID   ;

extern ULONG   g_ulDhcpcTaskId            ;
extern RELTMR_T   g_ulDhcpcRenewTimerID      ;
extern RELTMR_T   g_ulDhcpcRetransTimerID    ;
extern RELTMR_T   g_ulDhcpcCtrlBlockAgingTimerID;
extern RELTMR_T g_ulDhcpcSeqnumAgingTimerID;
extern ULONG   g_ulDhcpcTimerQid          ;
extern ULONG   g_ulDhcpcServerQid         ;
extern ULONG   g_ulCurrDHCPCCtlIndex      ;    /*重用定时器目前处理的用户DHCP控制块索引*/
extern ULONG   g_ulTimerRenewType         ;    /*重用定时器类型*/
extern ULONG   g_ulCurrProcIndex          ;    /*重发定时器当前处理的链表的index*/
extern ULONG   g_ulTimerRetransType       ;    /*重发定时器类型*/
extern ULONG   g_ulDHCPCTransId           ;    /*Xid的起始值*/
extern ULONG   g_ulDhcpcGlbLeaseTime      ;    /*全局配置的IP有效时间全局变量*/
extern ULONG   g_ulDHCPCDbgPkt            ;
extern ULONG   g_ulDhcpcInnerQid;
/*dft发送控制块定时器ID*/
extern ULONG   g_uldftDhcpcSendCBTimerID;

extern ULONG *g_DFT_pulDHCPSendCBNum;      /* DFT上报DHCP发送控制块数目 */

/*APN配置的DHCP服务器UDPS服务号链表*/
//extern AM_SLL_S                       g_stDhcpcUdpsSrvNumList;  

/*  重发定时器链表结构*/
extern DLL_S                       g_astTimerLink[DHCPC_TMR_CIRCLE_TIME]; 

/*全局UDPS服务号变量*/
extern DHCPC_GLOBAL_UDPS_SRVNO_S   g_stDhcpcGlobalUdpsSrvNo;

/*临时控制块数组*/
extern DHCPC_CTRLBLK_NODE          *g_pstDhcpCtrlBlkNodeArr;

/*DHCP 控制块索引数组*/
extern DHCPC_CTRLBLK               **g_pstDhcpcCtrlBlkRec;

//extern DHCPC_HASH_S    g_DHCPC_stHashTable;         /*IP HASH 表*/

extern UCHAR           *g_pucDpeRightValAddr;       /*dpe 负荷分担的权重值首地址*/
extern UCHAR           *g_pucDpeRightCountAddr;     /*SD 用于负荷分担选择dpe的计算值首地址*/

extern RELTMR_T g_aulDhcpcSrvTimerId[DHCPGRP_MAX_NUM];
extern ULONG g_ulDhcpDebug;
extern ULONG g_aulDHCPDbgCnt[DHCP_MAX_FAILURE_COUNTER];
extern VOS_SIZE_T  g_PGWtoServer_ulDHCPV4DiscoveryNumAddr ; /*用于统计PGW发送给DHCP Server的DHCPV4 Discovery消息包数*/
extern VOS_SIZE_T  g_PGWtoServer_ulDHCPV4RequestNumAddr ;   /*用于统计PGW发送给DHCP Server的DHCPV4 Request消息包数*/
extern VOS_SIZE_T  g_PGWtoServer_ulDHCPV4DeclineNumAddr ;   /*用于统计PGW发送给DHCP Server的DHCPV4 Decline消息包数*/
extern VOS_SIZE_T  g_PGWtoServer_ulDHCPV4ReleaseNumAddr ;   /*用于统计PGW发送给DHCP Server的DHCPV4 Releases消息包数*/
extern VOS_SIZE_T  g_ServertoPGW_ulDHCPV4OfferNumAddr ;     /*用于统计PGW接收的DHCP Server始发的DHCPV4 Offer消息包数*/
extern VOS_SIZE_T  g_ServertoPGW_ulDHCPV4AckNumAddr ;       /*用于统计PGW接收的DHCP Server始发的DHCPV4 Ack消息包数*/
extern VOS_SIZE_T  g_ServertoPGW_ulDHCPV4akNumAddr ;        /*用于统计PGW接收的DHCP Server始发的DHCPV4 Nak消息包数*/

extern UCHAR g_ucSoftParaDHCPKPN;

extern ULONG g_ulDhcpCtrlBlockAgingFlag;

extern ULONG g_ulDhcpcCurrentScanPdpIndex;

extern ULONG g_ulDhcpcCurrentScanHashKey;

extern ULONG g_ulDhcpcLogRecordRegId;

/* 告警计数 */

 /*告警扫描定时器ID */
extern ULONG g_ulDhcpcAlarmTimerID;

extern UCHAR *g_pucDhcpPktBuf;

extern DHCPC_CTRLBLK **g_pstDhcpcIpv6CtrlBlkRec;

extern ULONG g_ulDhcpcSpuType;

extern ULONG g_ulDhcpcBoardType;
extern ULONG g_ulResendTimeout;

#endif /* __DHCPC_VAR_H__ */
