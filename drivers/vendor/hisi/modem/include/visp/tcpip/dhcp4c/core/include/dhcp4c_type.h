/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_type.h
*
*  Project Code: VISP1.5
*   Module Name: DHCP client Module
*  Date Created: 2004-05-19
*        Author: tangcongfeng(36956)
*   Description: 定义了DHCP中所用的数据结构
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-05-19 tangcongfeng(36956)     Creat the first version.
*  2006-05-10  lu yao(60000758)       为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

#ifndef _DHCP4C_TYPE_H_
#define _DHCP4C_TYPE_H_



#ifdef  __cplusplus
extern "C"{
#endif

/* Header of DHCP packet */
typedef struct tagDHCP4C_PACKET_HEAD
{
    UCHAR               ucOp;                /* Message opcode/type */
    UCHAR               ucHtype;             /* Hardware addr type  */
    UCHAR               ucHlen;              /* Hardware addr length */
    UCHAR               ucHops;              /* Number of relay agent hops from client */
    ULONG               ulXid;               /* Transaction ID */
    USHORT              usSecs;              /* Seconds since clien t started looking */
    USHORT              usFlags;             /* Flag bits */
    ULONG               ulCiaddr;            /* Client address (if already in use) */
    ULONG               ulYiaddr;            /* 'your' (client) address */
    ULONG               ulSiaddr;            /* address of next server to use in DHCP */
    ULONG               ulGiaddr;            /* DHCP relay agent address */
    UCHAR               pucChaddr [DHCP4C_CHADDR_LEN];   /* Client hardware address */
    UCHAR               pcSname [DHCP4C_SNAME_LEN];      /* Optional server host name */
    UCHAR               pcFile [DHCP4C_FILE_LEN];        /* Boot filename */
} DHCP4C_PACKET_HEAD_S;



/*dhcp网络包物理结构DHCP4C_PACKET_S*/
typedef struct tagDHCP4C_PACKET
{
    DHCP4C_PACKET_HEAD_S * pstHead; /*DHCP报文头*/
    UCHAR *pucOptions; /* DHCP 选项*/
}DHCP4C_PACKET_S;

/* 存放解析报文信息结构 */
typedef struct tagDHCP4C_PACKETINFO
{

    ULONG       ulXid;            /* Transaction ID */
    ULONG       ulCiaddr;         /* Client address (if already in use) */
    ULONG       ulYiaddr;         /* 'your' (client) address */
    ULONG       ulSiaddr;         /* address of next server to use in DHCP */
    ULONG       ulGiaddr;         /* DHCP relay agent address */
    UCHAR       pucChaddr [DHCP4C_CHADDR_LEN];         /* Client hardware address */
    ULONG       ulOptionOverload;                       /* options overload option */
    ULONG       ulMsgType;                              /* message type */
    ULONG       ulServerId;                             /* server identifier */
    ULONG       ulSubnetMask;                           /* subnet mask  */
    ULONG       ulRouter[DHCP4C_ROUTER_NUM];            /* router address */
    ULONG       ulDNSAddr[DHCP4C_DNSIP_NUM];            /* dns sever address */
    CHAR        pcDomain[DHCP4C_DOMAINNAME_SIZE];       /* domain name */
    ULONG       ulLeaseTime;                            /* address lease time */
    ULONG       ulRenewalTime;                          /* renewal time value */
    ULONG       ulRebingdingTime;                       /* Rebinding time value */
    UCHAR       ucOptionExistFlg[DHCP4C_MAX_OPTIONCODE]; /*标志选项存在 */
    UCHAR       ucPadding;
}DHCP4C_PACKETINFO_S;

/* SESSION 控制块 */
typedef struct tagDHCP4C_SESSION
{
    DLL_NODE_S          stDLLNode; /* list node pointer,must be in first  position in this struct */
    ULONG               ulXID;              /* Transaction ID */
    ULONG               ulInterfaceIndexID; /* Interface Index ID */
    ULONG               ulInterfaceIPAddr;  /* interface address  */
    ULONG               ulInterfaceSubnetMask;    /* the interface's subnetmask  */
    ULONG               ulGatewayIPAddr[DHCP4C_ROUTER_NUM];      /* the Gatewey address */
    ULONG               ulDNSIPAddr[DHCP4C_DNSIP_NUM];           /* the Domain Nane Server's address */
    CHAR                pcDomainName[DHCP4C_DOMAINNAME_SIZE];   /* the Domain Name */
    ULONG               ulServerIdentifier;                      /* the DHCP server identifier */
    UCHAR               pucChaddr [DHCP4C_CHADDR_LEN];           /* client hardware address */
    ULONG               ulLeaseTime;      /* address lease time */
    ULONG               ulRenewTime;      /* renewal time value  */
    ULONG               ulRebindTime;     /* rebinding time value */
    ULONG               ulFSMState;       /* FSM state */
    ULONG               ulArpReqTimerID;         /* ARP REQ timer ID */
    ULONG               ulDiscoverTimerID;       /* Discover timer ID */
    ULONG               ulRequestTimerID;        /* Request timer ID */
    ULONG               ulRenewTimerID;          /* Renew timer ID */
    ULONG               ulRebindTimerID;         /* rebinding timer ID */
    ULONG               ulLeaseTimerID;          /* Lease timer ID */
    ULONG               ulLeaseTimeSince1970;    /* lease time in seconde since 1970/1/1 00:00:00*/
    ULONG               ulDebugFlag;             /* 调试开关 */
    UCHAR               *pucSendBuf;             /* 发送DHCP报文缓存 */
    UCHAR               *pucOptionItem;          /* 用户配置DHCP选内容 */
    ULONG               ulMsgType;               /* message type */
    ULONG               ulSendBufLen;            /* DHCP 报文长度 */
    ULONG               ulMaxReSent;             /* 记录报文重发次数 */
    LONG                lSocketId;               /* SOCKET id */
    ULONG               ulRenewInterfaceFlag;    /* 标识三种状态: DHCP4C_ISRENEWING, DHCP4C_RENEW_TIMOUT, DHCP4C_ISRELEASEING_BAK */                                                 
    ULONG               ulSmooth;                /* 1－未平滑，0－已经平滑*/
    UCHAR               aucSeverMac[MACADDRLEN];  /* Sever的physical地址 */
    UCHAR               ucReserved[2];
    ULONG               ulCfgCheckTimerID;       /* 用户配置检查 timer ID */
    UCHAR               *pucRecvBuf;             /*保存接收DHCP报文缓存 */
    ULONG               ulRecvLen;               /*接收的DHCP报文长度*/
    ULONG               ulCfgCheckResult;        /*保存用户配置检查结果*/
    ULONG               ulOutIfIndex;            /* 在LoopBack接口上使能DHCP时指定的出接口,用于支持DHCP over IPSEC 功能,
                                                    0:表示没有指定出接口, 非0表示指定的出接口索引.正常的DHCP该字段都为0,
                                                    只有在指定出接口使能LoopBack接口的DHCP时该字段才非0. */
    DHCP4CSTATISTIC_S   stDhcp4cStatistic;       /* DHCP报文统计 */
}DHCP4C_SESSION_S;


typedef struct tagDHCP4C_DEBUGINFO
{
    DLL_NODE_S      stDLLNode;  /* list node pointer,must be in first  position in this struct */
    ULONG ulIfIndex;            /*Interface Index*/
    ULONG ulDebugFlag;          /* Debug flag */
}DHCP4C_DEBUGINFO_S;

typedef struct tagDHCP4C_CONFIGINFO
{
    DLL_NODE_S      stDLLNode;  /* list node pointer,must be in first  position in this struct */
    ULONG  ulIfIndex;           /* Interface Index */
    ULONG  ulConfigFlag;        /* Config flag */
    ULONG  ulCiaddr;            /* Ciaddr option,网络序 */
    ULONG  ulCIDLen;            /* the length of configuration CID */
    ULONG  ulVSILen;            /* the length of configuration VSI */
    UCHAR  ucCID[DHCP4C_MAXCIDLEN];           /* CID option */
    UCHAR  ucVSI[DHCP4C_MAXVSILEN];           /* VSI option */
    /*added by l61496 2007-7-26 添加DHCP默认地址*/
    ULONG ulDHCPDefaultIP;     /* Default address*/
    ULONG ulDHCPDefaultSubMask; /* Default sub mask */
    ULONG ulEnable;
    ULONG ulDelayTime;
}DHCP4C_CONFIGINFO_S;


#define     DLLNODE(x)      ((DHCP4C_SESSION_S *)(x))
#define     DLLNODEDEBUG(x)    ((DHCP4C_DEBUGINFO_S *)(x))
#define     DLLNODECONFIG(x)   ((DHCP4C_CONFIGINFO_S *)(x))

/* 单个接口的DHCP租期节点 */
typedef struct tagDHCP4C_LEASE_NODE
{
    DLL_NODE_S stDLLNode;  /* list node pointer, must be in first position in this struct */
    DHCP4C_LEASE_S stLease; /* DHCP4C 租期记录 */
}DHCP4C_LEASE_NODE_S;

#pragma    pack( 1 )

typedef struct  tagDHCP_ETHERHDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*目的physical地址*/
    UCHAR                   ucHdrSrcMacAddr[6];     /*源physical地址  */
    USHORT                  usHdrType;              /*协议类型   */
}DHCP_ETHERHDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP4C_TYPE_H_ */


