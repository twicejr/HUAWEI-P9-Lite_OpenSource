/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_def.h
*
*  Project Code: VISP1.5
*   Module Name: DHCP client Module
*  Date Created: 2004-05-19
*        Author: tangcongfeng(36956)
*   Description: 定义了DHCP模块所用的宏
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-05-19 tangcongfeng(36956)      Creat the first version.
*
*******************************************************************************/

#ifndef _DHCP4C_DEF_H_
#define _DHCP4C_DEF_H_


#ifdef  __cplusplus
extern "C"{
#endif


#define DHCP4C_SNAME_LEN    64
#define DHCP4C_FILE_LEN     128
#define DHCP4C_CHADDR_LEN   16


/* FSM UP/DOWN 状态*/
#define DHCP4C_FSM_UP   0
#define DHCP4C_FSM_DOWN 1

#define DHCP4C_BOUND    0
#define DHCP4C_UNBOUND  1

#define DHCP4C_SESSION_SMOOTHED   0
#define DHCP4C_SESSION_UNSMOOTHED 1

/* FSM 事件类型 */
#define DHCP4C_FSM_EV_IPCNFLCT          1
#define DHCP4C_FSM_EV_IFPHYCHANGE       2
#define DHCP4C_FSM_EV_START             3
#define DHCP4C_FSM_EV_RENEW             4
#define DHCP4C_FSM_EV_RELEASE           5
#define DHCP4C_FSM_EV_STOP              6
#define DHCP4C_FSM_EV_IFDELETE          7

/* 事件 位 */
#define EV_DHCP4C_CMD   ((ULONG)1)
#define EV_DHCP4C_CNTRL ((ULONG)1<<1)


#define DHCP4C_INTERFAC_LOW    0    /* 通过DHCP获取的地址优先级高于接口原有的地址优先级 */
#define DHCP4C_INTERFAC_HIG    1    /* 通过DHCP获取的地址优先级低于接口原有的地址优先级 */

#define DHCP4C_MAX_RESENT      4

#define DHCP4C_HEAD_LEN        236

/* DHCP消息类型 */
#define DHCP4C_BOOTREQUEST    1
#define DHCP4C_BOOTREPLY      2

/* 以太网硬件类型 */
#define DHCP4C_HARDTYPE_ETH   1

/* RFC3456 DHCP over IPSEC规定DHCP使用的硬件类型 */
#define DHCP4C_HARDTYPE_DHCP_OVER_IPSEC   31

/* 以太网硬件地址长度 */
#define DHCP4C_HARDLEN_ETH    6

/* 广播标志 */
#define DHCP4C_BROADCAST_FLAGS 0x8000

/* 单播标志 */
#define DHCP4C_UNICAST_FLAGS      0

#define DHCP4C_MAGIC_COOKIE   "\143\202\123\143" /* 8进制。运行时连续四个字节的内存上的存储值为0x63,0x82,0x053,0x63 */
#define MAGIC_COOKIE_LEN      4


/* DHCP的 Option的 overload 标志位 */
#define DHCP4C_OVERLOAD_FILE_FLAG   1
#define DHCP4C_OVERLOAD_SNAME_FLAG  2

/* 选项代码最大为255 */
#define DHCP4C_MAX_OPTIONCODE       255
#define DHCP_OPTIONMAXLEN           512      /*DHCP 选项最大长度*/

/* 各选项在DHCP报文中状态 */
#define DHCP4C_OPTION_MUSTNOT        0
#define DHCP4C_OPTION_MUST           1
#define DHCP4C_OPTION_MAY            2
#define DHCP4C_OPTION_CONDITIONAL    3


/* UDP数据包发送缓冲区大小 */
#define DHCP4C_UDPBUF_MAXLEN         2048

#define DHCP4C_SERVER_PORT           0x43            /* dhcp server port */
#define DHCP4C_CLIENT_PORT           0x44            /* dhcp client port */

/* 增强DHCP Client兼容性. */
#define  DHCP4C_MAXHDR_LEN   80     /* 构造DHCP Client报文MBUF时预留的首部长度 */
#define  DHCP4C_UDPIPHDR_LEN      28   /* DHCP Client报文的UDP, IP层首部长度 */
#define  DHCP4C_TTL   255           /* DHCP Client报文的TTL值  */
#define  DHCP4C_TOS   0             /* DHCP Client报文的TOS值  */

/* 重发定时器时延初值 */
#define DHCP4C_TIMER_INITAL    4000
/* Discover报文连续无响应时，重新开始Discover报文发送的间隔，参考Windows设置为5分钟 */
#define DHCP4C_TIMER_INTERVAL    5*60*1000


#define DHCP4C_TIMER_LOOP      1
#define DHCP4C_TIMER_NOLOOP    0

/* ARPREQUEST 报文0.5秒发送一次检测IP是否冲突*/
#define DHCP4C_ARPECHO_TIMEOUT_VALUE        500

/*用户配置5s 检查定时器*/
#define DHCP4C_CFGCHECK_TIMEOUT_VALUE        5000

/* 配置项标志定义 */
#define DHCP4C_CONFIGCIADDR  0x01
#define DHCP4C_CONFIGCID     0x02
#define DHCP4C_CONFIGVSI     0x04
#define DHCP4C_CONFIGDEFAULTIP 0x08
#define DHCP4C_CONFIGVLANSCANNING 0x10

/* 广播地址 */
#define DHCP4C_BROADCAST_IPADDR        0xffffffffL
#define DHCP4C_MAC_LEN                 6

#if (VRP_OS_WINDOWS == VRP_YES)
#define DHCP4C_DEFAULT_FILE_LEASE      "c:/lease.bak"
#endif

#define DHCP4C_DELETE_DNSIP  1
#define DHCP4C_ADD_DNSIP     0


#define DHCP4C_ISRENEWING    0x01 /* renewing interface flag */
#define DHCP4C_RENEW_TIMOUT  0x02 /* renew timer time out */

#define VOS_TIMER_DEL_ON_TIMEOUTMSG  4

#define DHCP4C_MAX_SESSION   64 /* 最大session 数*/

/* DHCP4C模块使用的SID统一在此定义 */

#define SID_COMP_DHCP4C_DLL_S             1  /* DLL_S */
#define SID_COMP_DHCP4C_SESSION_S         2  /* DHCP4C_SESSION_S */
#define SID_COMP_DHCP4C_CONFIGINFO_S      3  /* DHCP4C_CONFIGINFO_S */
#define SID_COMP_DHCP4C_SNDBUF            4  /* DHCP4C会话报文缓存 */
#define SID_COMP_DHCP4C_DEBUGINFO_S       5  /* DHCP4C_DEBUGINFO_S */
#define SID_COMP_DHCP4C_VIRTUAL_S         6  /* DHCP4C虚接口上配置信息 */
#define SID_COMP_DHCP4C_LEASE_S           7  /* DHCP4C租期节点DHCP4C_LEASE_NODE_S */

/* end of SID */

#ifndef MACADDRLEN
#define MACADDRLEN                6
#endif

#define DHCP_ETHERTYPE_IP         0x0800  /* IP协议报文 */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP4C_DEF_H_ */


