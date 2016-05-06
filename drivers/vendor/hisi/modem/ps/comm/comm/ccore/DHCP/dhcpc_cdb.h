/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : dhcpc_cdb.h
  Version       : Initial Draft
  Author        : l00103336
  Created       : 2012/4/19
  Last Modified :
  Description   : DHCPC模块配置数据结构
  Function List :
  History       :
  1.Date        : 2012/4/19
    Author      : l00103336
    Modification: Created file

******************************************************************************/
#ifndef __DHCPC_CDB_H__
#define __DHCPC_CDB_H__

#ifdef   __WIN32_PLATFORM__
#pragma pack(push, 1)
#endif

#define DHCP_SERVER_GROUP_MAX_NUM   1000

/*congjing DHCPC*//*****************************/
#define DHCP_PRISRV_TIMER_ON    1   /* 定时器开启 */
#define DHCP_PRISRV_TIMER_DOWN  0   /* 定时器关闭 */
#define DHCP_PRISRV_TEST_ON     1   /* 主用服务器探测打开 */
#define DHCP_PRISRV_TEST_DOWN   0   /* 主用服务器探测关闭 */

#define DHCP_NO_ALARM                      0               /* DHCP 没有发布链路断告警 */
#define DHCP_ALARMED                       1               /* DHCP 已经发布链路断告警 */

#define DHCP_SEVER_NORMAL                         0 /*服务器状态正常*/
#define DHCP_SEVER_ABNORMAL                       1 /*服务器无响应*/      
#define DHCP_SEVER_TRY                            2 /*服务器探测开启*/
#define DHCP_SEVER_GROUP_IS_IPV6                  1 /*dhcp服务器类型*/
#define DHCP_SEVER_GROUP_IS_IPV4                  2 /*dhcp服务器类型*/
#define DHCP_SEVER_RETRANSMIT_NUM_NORMAL          1 /*向服务器发送消息次数*/
#define DHCP_SEVER_RETRANSMIT_NUM_INI             0 /*向服务器发送消息初始次数*/
#define DHCP_SEVER_INVALID_IP                              0 /*无效ip*/
#define DHCPC_V_INTERFACE_NAME_MAX_LEN  19

/* 增加DHCP信令V接口跟踪 */
typedef struct
{
    UCHAR       aucIfName[DHCPC_V_INTERFACE_NAME_MAX_LEN+1];     /* V接口名称 */
    ULONG       ulPeerIp;       /* 对端IP地址 */
    UCHAR       aulPeerIPv6[40];       /*对端IPv6地址 */
    ULONG       ulMsgType;       /* 消息类型 */
    ULONG       ulPeerIpTypeOp;       /* 对端地址类型选项 */
}VOS_PACKED DHCPC_IFTRC_V_FILTER; 

#define VOS_ERR_GTPC_ERR_BASE    20000
#define VOS_ERR_GTPC_ERR_LOGIC_INTERFACE             (VOS_ERR_GTPC_ERR_BASE+31)    /* 逻辑接口输入不合法或者接口不存在 */
#define VOS_ERR_GTPC_ERR_PEER_IP                     (VOS_ERR_GTPC_ERR_BASE+33)    /* 对端IP错误 */


#define LAP_DHCP_SERVER_GROUP_NAME_MAX_LENGTH    32
#define LAP_VPN_INSTANCE_NAME_MAX_LENGTH         31

/* zhangjinquan 00175135 DHCPv6特性 2012-07-02 start */
typedef struct tagLAPDHCPCFG
{
     ULONG aulPrimaryServerIp[4];        /*  主服务器的IP 地址*/
     ULONG aulSecondaryServerIp[4];        /*  备服务器的IP 地址*/
     ULONG ulVpnIndex;                /*  DHCP 服务器组所属的VPN 实例索引*/  
     UCHAR aucDhcpServerGrpName[LAP_DHCP_SERVER_GROUP_NAME_MAX_LENGTH + 1];        /*  DHCP服务器组的名称 */
     UCHAR  ucLeaseTime;            /* 地址租期 */
     USHORT usDhcpServerGrpIndex;    /* DHCP服务器组的index */
     UCHAR aucVpnName[LAP_VPN_INSTANCE_NAME_MAX_LENGTH+1]; /*  DHCP 服务器组所属的VPN 实例名字*/ 
     UCHAR ucIsDHCPv6;             /* 是否DHPCv6标记: 1--是ipv6 ,2 -- 是ipv4 ，0--默认group*/
     UCHAR ucRetransmitNum;        /* 配置的最大重发次数，范围0-5，默认3 */
     UCHAR ucRetransmitTimeOut;    /* 配置的重发间隔，范围1-10，默认3 */
     UCHAR ucReserve;              /* 保留字段 */
}LAP_DHCP_CFG_S;
/* zhangjinquan 00175135 DHCPv6特性 2012-07-02 end   */

#ifdef   __WIN32_PLATFORM__
#pragma pack(pop, 1)
#endif

#endif /* end of __DHCPC_CDB_H__ */
