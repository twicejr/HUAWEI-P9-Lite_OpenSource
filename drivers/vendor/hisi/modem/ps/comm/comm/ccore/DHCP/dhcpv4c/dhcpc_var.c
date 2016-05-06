/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpc_var.c
  版 本 号   : 初稿
  作    者   : c57548
  生成日期   : 2007年11月3日
  最近修改   :
  功能描述   : dhcpc模块的全局变量定义
  函数列表   :
  修改历史   :
  1.日    期   : 2007年11月3日
    作    者   : c57548
    修改内容   : 创建文件

******************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpv6c_pkt.h"
#include "dhcpc_var.h"

/*跟sd之间的共享队列id*/
VOID    *g_pulSDDhcpMCQueID         = 0;

/* 在sd上接受dhcpv6 server消息的共享队列 */
VOID    *g_pulSDDhcpv6cMcQueId      = 0;

/*dhcpc向lap发送消息的队列id*/
VOID    *g_pulDHCP_LAP2_RSPQueID    = 0;

/*dhcpc接收lap消息的队列id*/
VOID    *g_pulDHCP_LAP2_REQQueID    = 0;

/*遍历dhcpc hash链表时的hash节点的标记*/
ULONG   g_ulCtrlblkXaxis = 0; /*代表HASH链的X轴,长度为65535*/

/*遍历dhcpc hash链表时每个hash节点下的控制块节点数*/
ULONG   g_ulCtrlblkYaxis = 0; /*代表HASH链的Y轴,所有HASHKEY相同的节点*/

/*dhcpc模块的任务id*/
ULONG   g_ulDhcpcTaskId             = 0;

/*发送续租消息的定时器id*/
RELTMR_T   g_ulDhcpcRenewTimerID       = 0;

/*控制重发消息的定时器id*/
RELTMR_T   g_ulDhcpcRetransTimerID     = 0;

/*控制块老化定时器ID*/
RELTMR_T g_ulDhcpcCtrlBlockAgingTimerID = 0;

/*dft发送控制块定时器ID*/
ULONG   g_uldftDhcpcSendCBTimerID = 0;

/*SEQNUM老化定时器ID*/
RELTMR_T g_ulDhcpcSeqnumAgingTimerID = 0;

/*定时器队列id*/
ULONG   g_ulDhcpcTimerQid           = 0;

ULONG   g_ulDhcpcInnerQid           = 0;


/*dhcpc接收sd上送消息的队列id*/
ULONG   g_ulDhcpcServerQid          = 0;

/*重用定时器目前处理的用户DHCP控制块索引*/
ULONG   g_ulCurrDHCPCCtlIndex       = 1;

/*重用定时器类型*/
ULONG   g_ulTimerRenewType          = 0;

/*重发定时器当前处理的链表的index*/
ULONG   g_ulCurrProcIndex           = 0;

/*重发定时器类型*/
ULONG   g_ulTimerRetransType        = 0;

/*Xid的起始值*/
ULONG   g_ulDHCPCTransId            = 0;

/*全局配置的IP有效时间全局变量*/
ULONG   g_ulDhcpcGlbLeaseTime       = 0;

/*DHCPC模块调试打印开关*/
ULONG   g_ulDHCPCDbgPkt             = 0;

/*dhcpc模块的调试计数集合*/
ULONG   g_aulDHCPDbgCnt[DHCP_MAX_FAILURE_COUNTER];

/*APN配置的DHCP服务器UDPS服务号链表*/
//AM_SLL_S                       g_stDhcpcUdpsSrvNumList;

/*  重发定时器链表结构*/
DLL_S                       g_astTimerLink[DHCPC_TMR_CIRCLE_TIME];

/*全局UDPS服务号变量*/
DHCPC_GLOBAL_UDPS_SRVNO_S   g_stDhcpcGlobalUdpsSrvNo;

/*临时控制块数组*/
DHCPC_CTRLBLK_NODE          *g_pstDhcpCtrlBlkNodeArr;

/*DHCP 控制块索引数组*/
DHCPC_CTRLBLK               **g_pstDhcpcCtrlBlkRec = 0;
/* BEGIN: Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/9 */
/*DHCP 控制块索引数组for DHCPv6*/
DHCPC_CTRLBLK               **g_pstDhcpcIpv6CtrlBlkRec = NULL;
/* END:   Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/9 */

/*m00551573 全文件pclint 2012-10-11 start*/
//DHCPC_HASH_S    g_DHCPC_stHashTable;            /*IP HASH 表*/
/*m00551573 全文件pclint 2012-10-11 end*/

UCHAR           *g_pucDpeRightValAddr = NULL;   /*dpe 负荷分担的权重值首地址*/
UCHAR           *g_pucDpeRightCountAddr = NULL;     /*SD 用于负荷分担选择dpe的计算值首地址*/

/*用于主服务器是否正常的探测定时器id*/
RELTMR_T g_aulDhcpcSrvTimerId[DHCPGRP_MAX_NUM] = {0};

/* 告警计数 */


 /*告警扫描定时器ID */
ULONG g_ulDhcpcAlarmTimerID = 0;

/*dhcpc模块的调试打印开关*/
VOS_UINT32 g_ulDhcpDebug = 0;

/* Added start by ZhangYang  z00142225 at 2009-04-09 UGWV900R001C001 for 性能统计 */
VOS_SIZE_T  g_PGWtoServer_ulDHCPV4DiscoveryNumAddr =  VOS_NULL_PTR ; /*用于统计PGW发送给DHCP Server的DHCPV4 Discovery消息包数*/
VOS_SIZE_T  g_PGWtoServer_ulDHCPV4RequestNumAddr =  VOS_NULL_PTR ;   /*用于统计PGW发送给DHCP Server的DHCPV4 Request消息包数*/
VOS_SIZE_T  g_PGWtoServer_ulDHCPV4DeclineNumAddr =  VOS_NULL_PTR ;   /*用于统计PGW发送给DHCP Server的DHCPV4 Decline消息包数*/
VOS_SIZE_T  g_PGWtoServer_ulDHCPV4ReleaseNumAddr =  VOS_NULL_PTR ;   /*用于统计PGW发送给DHCP Server的DHCPV4 Releases消息包数*/
VOS_SIZE_T  g_ServertoPGW_ulDHCPV4OfferNumAddr =  VOS_NULL_PTR ;     /*用于统计PGW接收的DHCP Server始发的DHCPV4 Offer消息包数*/
VOS_SIZE_T  g_ServertoPGW_ulDHCPV4AckNumAddr =  VOS_NULL_PTR ;       /*用于统计PGW接收的DHCP Server始发的DHCPV4 Ack消息包数*/
VOS_SIZE_T  g_ServertoPGW_ulDHCPV4akNumAddr =  VOS_NULL_PTR ;        /*用于统计PGW接收的DHCP Server始发的DHCPV4 Nak消息包数*/

/* Added end by ZhangYang  z00142225 at 2009-04-09 UGWV900R001C001 for 性能统计 */

/*控制块老化标记*/
ULONG  g_ulDhcpCtrlBlockAgingFlag = 0;

/*遍历上下文时记录当前遍历的上下文索引*/
ULONG  g_ulDhcpcCurrentScanPdpIndex = 0;

/*遍历dhcp控制块时记录当前的hashkey*/
ULONG g_ulDhcpcCurrentScanHashKey = 0;

ULONG *g_DFT_pulDHCPSendCBNum = NULL;      /* DFT上报DHCP发送控制块数目 */

/**********Dhcpc 日志注册id***********/
ULONG g_ulDhcpcLogRecordRegId = 0;

UCHAR *g_pucDhcpPktBuf = VOS_NULL;

ULONG g_ulDhcpcSpuType = 0;

/* Added start by y00170683 at 2012-07-10 UGW10.0 for DHCPV6特性 */
ULONG g_ulDhcpcBoardType = CRM_BOARD_TYPE_SPUD;
ULONG g_ulResendTimeout = 0;
/* Added end by y00170683 at 2012-07-10 UGW10.0 for DHCPV6特性 */

