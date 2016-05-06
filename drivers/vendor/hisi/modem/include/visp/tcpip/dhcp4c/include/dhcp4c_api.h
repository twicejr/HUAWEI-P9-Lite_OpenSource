/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_api.h
*
*  Project Code: VISPV1R7
*   Module Name: dhcpc
*  Date Created: 2008-03-07
*        Author: wuhailan
*   Description: dhcpc用户API接口文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-07   wuhailan                Create
*
*******************************************************************************/
#ifndef _DHCP4C_API_H_
#define _DHCP4C_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef DNS_DOMAIN_LIST_NAME_LENGTH
#define DNS_DOMAIN_LIST_NAME_LENGTH 20
#endif

#define DHCP4C_DOMAINNAME_SIZE DNS_DOMAIN_LIST_NAME_LENGTH
#define DHCP4C_DNSIP_NUM       6 /* dns server 地址个数 */
#define DHCP4C_ROUTER_NUM      8 /* router list number */

#define DHCP4C_MINCIDLEN       2
#define DHCP4C_MAXCIDLEN       256
#define DHCP4C_MINVSILEN       1
#define DHCP4C_MAXVSILEN       256

/* DHCP数据包中option的选项代码,其他暂时不考虑 */
#define DHCP4C_OPTION_PAD                                 0
#define DHCP4C_OPTION_END                                 255
#define DHCP4C_OPTION_CLIENTID                            61
#define DHCP4C_OPTION_SERVERID                            54
#define DHCP4C_OPTION_SUBNET_MASK                         1
#define DHCP4C_OPTION_ROUTER                              3
#define DHCP4C_OPTION_DNS                                 6
#define DHCP4C_OPTION_DOMAIN_NAME                         15
#define DHCP4C_OPTION_REQUESTED_IP                        50
#define DHCP4C_OPTION_OVERLOAD                            52
#define DHCP4C_OPTION_MESSAGE_TYPE                        53
#define DHCP4C_OPTION_LEASE_TIME                          51
#define DHCP4C_OPTION_RENEWAL_TIME                        58
#define DHCP4C_OPTION_REBINDING_TIME                      59
#define DHCP4C_OPTION_PARAMETEREQLIST                     55
#define DHCP4C_OPTION_MAXMSG_SIZE                         57
#define DHCP4C_OPTION_VSI                                 43

#define DHCP4C_FSM_MAX               11

/* FSM 状态*/
#define DHCP4C_FSM_IFDOWN         0
#define DHCP4C_FSM_INIT           1
#define DHCP4C_FSM_INIT_REBOOT    2
#define DHCP4C_FSM_REBOOTING      3
#define DHCP4C_FSM_SELECTING      4
#define DHCP4C_FSM_REQUESTING     5
#define DHCP4C_FSM_BOUND          6
#define DHCP4C_FSM_REBINDING      7
#define DHCP4C_FSM_RENEWING       8
#define DHCP4C_FSM_HALFBOUND      9
#define DHCP4C_FSM_WAIT_CONFCHECK   10  /*用户配置检查状态*/

/*dhcp数据包的类型*/
#define DHCP4C_DHCPDISCOVER          1
#define DHCP4C_DHCPOFFER             2
#define DHCP4C_DHCPREQUEST           3
#define DHCP4C_DHCPDECLINE           4
#define DHCP4C_DHCPACK               5
#define DHCP4C_DHCPNAK               6
#define DHCP4C_DHCPRELEASE           7
#define DHCP4C_DHCPINFORM            8


/* DEBUG 宏开关定义 */
#define DHCP4C_DEBUG_FLAG_PACKET        0x01
#define DHCP4C_DEBUG_FLAG_EVENT         0x02
#define DHCP4C_DEBUG_FLAG_ERROR         0x04
#define DHCP4C_DEBUG_FLAG_ALL           0x07

#define DHCP4C_CHADDR_LEN   16

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* 最大接口名长度 */
#endif

/* 增加/刷新DHCP租期记录 */
#define DHCP4C_ADD_LEASE  0
/* 删除DHCP租期记录 */
#define DHCP4C_DEL_LEASE  1

/*Add by x57575 for Nodeb CR BC3D02026*/
#define DHCP4C_PKTHOOK_SUCCESS_MODIFY       0
#define DHCP4C_PKTHOOK_NOT_MODIFY           1
#define DHCP4C_PKTHOOK_FAIL_MODIFY          2

/* 去使能DHCP VLAN Scaning功能 */
#define DHCP4C_VLAN_SCANNING_DISABLE        0
/* 使能DHCP VLAN Scaning功能 */
#define DHCP4C_VLAN_SCANNING_ENABLE         1
/* DHCP VLAN Scaning功能延迟时间最大值1h=3600*1000ms */
#define DHCP4C_VLAN_SCANNING_MAX_DELAYTIME  3600000

typedef struct tagDhcp4cStatistic
{
    /* 协商统计信息  接收*/
    ULONG ulInDhcpOffer;        /* DHCP4C_DHCPOFFER 2 */
    ULONG ulInDhcpAck;          /* DHCP4C_DHCPACK 5 */
    ULONG ulInDhcpNak;          /* DHCP4C_DHCPNAK 6 */
    ULONG ulInDhcpInform;       /* DHCP4C_DHCPINFORM 8 */
    ULONG ulInErr;              /* DHCP4C 错误统计*/

    /* 协商统计信息  发送*/
    ULONG ulOutDhcpDiscover;    /* DHCP4C_DHCPDISCOVER 1 */
    ULONG ulOutDhcpReqest;      /* DHCP4C_DHCPREQUEST 3 */
    ULONG ulOutDhcpDecline;     /* DHCP4C_DHCPDECLINE 4 */
    ULONG ulOutDhcpRelease;     /* DHCP4C_DHCPRELEASE 7 */
} DHCP4CSTATISTIC_S;

typedef struct tagDHCP4C_FSM_SELECT
{
    ULONG ulPacketLen;
    UCHAR  *pOfferPacket;     /* 选择的Server的Offer报文*/
}DHCP4C_FSM_SELECT_S;

typedef struct tagDHCP4C_PROC_HOOK
{
    UCHAR *pucUdpBuf;   /* 存放报文的缓冲区指针 */
    ULONG ulRecvLen;    /* 接收的报文长度 */
    USHORT usVlanInfo;  /* vlan信息 */
    USHORT usRes;       /* 保留字段 */
}DHCP4C_PROC_HOOK_S;

typedef struct tagDHCP4C_DISPLAYINFO
{
    ULONG            ulIfIndex;               /* 接口索引*/
    ULONG            ulIpAddr;                /* 地址 */
    ULONG            ulInterfaceSubnetMask;   /* 子网掩码 */
    CHAR             szDnsSuffix[DHCP4C_DOMAINNAME_SIZE];   /* domain name */
    ULONG            ulDNSIPAddr[DHCP4C_DNSIP_NUM];          /* 名字解析服务器地址 */
    ULONG            ulGatewayIPAddr[DHCP4C_ROUTER_NUM];     /* 网关地址 */
    ULONG            ulLeaseTime;                            /* address lease time */
    ULONG            ulOutIfIndex;            /* 使能DHCP时指定的出接口索引, 0表示没有指定出接口 */
}DHCP4C_DISPLAYINFO_S;

/*DHCP4c 配置的信息，主要是供外部接口获取DHCP 的信息*/
typedef struct tagDHCP4C_OPTIONINFO
{
    ULONG  ulCiaddr;                          /* Ciaddr option */
    ULONG  ulCIDLen;                          /* the length of configuration CID */
    ULONG  ulVSILen;                          /* the length of configuration VSI */
    UCHAR  ucCID[DHCP4C_MAXCIDLEN];           /* CID option */
    UCHAR  ucVSI[DHCP4C_MAXVSILEN];           /* VSI option */
}DHCP4C_OPTIONINFO_S;

/* 单个接口的DHCP租期文件内容定义 */
typedef struct tagDHCP4C_LEASE
{
    CHAR  if_szIfName[IF_MAX_INTERFACE_NAME_LEN+1]; /*接口名，关键字段*/
    UCHAR pucChaddr[DHCP4C_CHADDR_LEN];   /* physical地址 */
    UCHAR ucEnableFlag;      /* DHCP使能标志 */
    UCHAR ucPriority;        /* 地址优先级 */
    UCHAR ucPadding[2];
    ULONG ulInterfaceIPAddr; /* 接口地址，主机序 */
    ULONG ulSecond1970;      /* 租期结束时间离1970/1/1-00:00:00以来的秒数*/
}DHCP4C_LEASE_S;

/* DHCP4C统计信息 */
typedef struct tagDHCP4C_Statistic
{
    /* 协商统计信息  接收*/
    ULONG ulInDhcpOffer;        /* DHCP4C_DHCPOFFER     */
    ULONG ulInDhcpAck;          /* DHCP4C_DHCPACK       */
    ULONG ulInDhcpNak;          /* DHCP4C_DHCPNAK       */
    ULONG ulInErr;              /* DHCP4C 错误统计      */

    /* 协商统计信息  发送*/
    ULONG ulOutDhcpDiscover;    /* DHCP4C_DHCPDISCOVER  */
    ULONG ulOutDhcpReqest;      /* DHCP4C_DHCPREQUEST   */
    ULONG ulOutDhcpDecline;     /* DHCP4C_DHCPDECLINE   */
    ULONG ulOutDhcpRelease;     /* DHCP4C_DHCPRELEASE   */
} DHCP4C_STATISTIC_S;

/*DHCP4c模块错误码*/
enum tagDHCP_ErrCode
{
    DHCP4C_SUCCESS = 0,
    DHCP4C_FAILURE,

    DHCP4C_CONFIGERR_INDEX,     /*2 无效的接口索引(无对应接口) */
    DHCP4C_CONFIGERR_MEMORY,    /*3 内存分配失败(内存不足) */
    DHCP4C_CONFIGERR_LEN,       /*4 配置项长度错误  */
    DHCP4C_CONFIGERR_VAL,       /*5 配置项值错误    */
    DHCP4C_CONFIGERR_CODE,      /*6 配置项code错误  */
    DHCP4C_CONFIGERR_INTER,     /*7 指定的接口类型错误 */
    DHCP4C_CONFIGERR_DBGTYPE,   /*8 指定的Debug类型错误 */
    DHCP4C_CONFIGERR_DISABLE,   /*9 指定的接口没有使能DHCP */

    DHCP4C_WRONGFLAG_PPP,       /*10 在PPP上使能DHCP, 没有使用DHCP地址的优先级低于接口地址优先级的标志 */
    DHCP4C_REQFLAG_WRONG,       /*11 使能DHCP的标志位错误 */
    DHCP4C_REENABLEFLAG_WRONG,  /*12 重复使能DHCP标志位错误,只允许使用同样的标志位使能DHCP */

    DHCP4C_HA_IS_SMOOTHING,     /*13 HA正在平滑处理或手动倒换处理时，用户若操作接口，则返回此错误码 */
    DHCP4C_CONFIGERR_SUBTRUNK,  /*14 TRUNK子接口进行操作*/
    DHCP4C_CONFIGERR_CFGDHCPIP, /*15 配置DHCP 地址失败*/
    DHCP4C_CONFIGERR_WRITEQUE,  /*16 写队列失败*/
    DHCP4C_PARA_ERR,            /*17 参数错误*/
    DHCP4C_STOP_FAILURE,        /*18 dhcp4c_stop failure        */
    DHCP4C_AM4_CFG_ERR,         /*19 IP_AM4_CfgProcIpAddrDhcp return err  */
    DHCP4C_ALREADY_ENABLE_DHCP, /*20 已经使能了DHCP*/
    DHCP4C_CONFIGERR_IPIFNET,   /*21 接口获取到不正确的IP控制块*/
    DHCP4C_CONFIGERR_NULLPOINTER,/*22输入指针为空*/
    DHCP4C_CONFIGERR_DBGNO,     /*23 指定的debug开关值不正确*/
    DHCP4C_INVALID_IPADDRESS,   /*24 返回的地址无效*/
    DHCP4C_CONFIGNODE_NOTEXIST, /*25 不存在此配置结点*/

    DHCP4C_API_COM_NULL,        /*26 dhcp4c组件为空*/
    DHCP4C_API_PARA_WRONG,      /*27 存入参数有误*/
    DHCP4C_API_GET_INFO_FAIL,   /*28 获取显示信息失败*/
    DHCP4C_NOT_3D_MODE,         /*29 非三维接口模式*/
    DHCP4C_NULLPOINTER,         /*30 参数指针为空*/
    DHCP4C_IP_ADDR_WRONG,       /*31 地址非法*/
    DHCP4C_VIRTUAL_IFNET,       /*32 非本板接口*/
    DHCP4C_TASKRAP_NULL_IFNET,  /*33 任务抢占导致接口为空*/
    DHCP4C_WRITE_LEASE_NULL,    /*34 写DHCP租期文件的钩子函数为空*/
    DHCP4C_READ_LEASE_NULL,     /*35 读DHCP租期文件的钩子函数为空*/
    DHCP4C_INT_NOTL3ETH,        /*36 二层端口不支持Dhcp*/
    DHCP4C_ISVLANIF,            /*37 接口是VLANIF */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    DHCP4C_VRF_NOT_SUPPORT,     /*38 该接口所在的VRF实例不支持DHCP*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    DHCP4C_REG_UNREG_FAIL,      /*39 DHCP注册或去注册失败*/
    DHCP4C_CONFIGERR_LOOPBACKIF_INDEX,  /* 40 支持DHCP OVER IPSEC时,使能DHCP时传入的LoopBack接口索引参数不合法 */
    DHCP4C_CONFIGERR_NOT_LOOPBACK,      /* 41 支持DHCP OVER IPSEC时,使能DHCP时传入的LoopBack接口索引参数不是LoopBack类型 */
    DHCP4C_CONFIGERR_OUTIF_INDEX,       /* 42 支持DHCP OVER IPSEC时,使能DHCP时传入的出接口索引参数不合法 */
    DHCP4C_VIRTUAL_OUTIFNET,            /* 43 支持DHCP OVER IPSEC时,使能DHCP时传入的出接口索引不合法,不是本板接口 */
    DHCP4C_OUTIFNET_NOTL3ETH,           /* 44 支持DHCP OVER IPSEC时,使能DHCP时传入的出接口索引不合法,不是三层接口 */
    DHCP4C_OUTIFNET_ISVLANIF,           /* 45 支持DHCP OVER IPSEC时,使能DHCP时传入的出接口索引不合法,是VLAN接口 */
    DHCP4C_CONFIGERR_SUBTRUNK_OUTIFNET, /* 46 支持DHCP OVER IPSEC时,使能DHCP时传入的出接口索引不合法,是TRUNK成员接口 */
    DHCP4C_CONFIGERR_INTER_OUTIFNET,    /* 47 支持DHCP OVER IPSEC时,使能DHCP时传入的出接口索引不合法,不是ETH,TRUNK接口 */
    DHCP4C_CONFIGERR_VLANSCANNING_NOTENABLE,/* 48 去使能DHCP VLAN Scaning功能时,DHCP VLAN Scaning功能未使能 */
    DHCP4C_CONFIGERR_VLANSCANNING_DELAYTIME_OVERFLOW,/* 49 使能DHCP VLAN Scaning功能时,设置延时时间超过设定的最大值(1h) */
    DHCP4C_CONFIGERR_IP_ALREADY,  /* 50 添加/删除IP重复操作 */
    DHCP4C_ERR_MAX
};

/*Modified by zhongyu206043, 修改参数为结构体DHCP4C_PROC_HOOK_S  for S.DHCP.1.1, 2012/8/18 */
typedef ULONG (*TCPIP_PROCDHCP_HOOK_FUNC)(DHCP4C_PROC_HOOK_S *pInfo);

/* 注册获取DHCP信息钩子函数 */
typedef ULONG ( * GET_DHCP_CLIENT_IP_HOOK_FUN) ( ULONG ulIfIndex,
                                                        ULONG ulDHCPClientIP,
                                                        ULONG ulDHCPClientIPMask,
                                                        ULONG aulDNSIP[DHCP4C_DNSIP_NUM],
                                                        ULONG aulGatewayIP[DHCP4C_ROUTER_NUM],
                                                        CHAR pcDomainName[DHCP4C_DOMAINNAME_SIZE],
                                                        ULONG ulFlag
                                                        );

/* 注册获取DHCP Server IP信息钩子函数 */
typedef ULONG (* GET_DHCP_SERVER_IP_HOOK_FUN) (ULONG ulIfIndex,
                                                      ULONG ulDHCPServerIP,
                                                      ULONG ulFlag
                                                     );

/* 注册添加DHCP选项钩子函数 */
typedef ULONG (*gpfDHCPADDOPTION_HOOK_FUNC)(ULONG ulIfIndex ,ULONG ulMessageType,
                                            ULONG ulFSMState,ULONG  ulMaxLen,
                                            UCHAR *pucOptionItem,ULONG *pulLen);
/* 读取DHCP租期文件的钩子函数原型
   DHCP4C_LEASE_S **ppstLease: 调用者返回的存放租期记录的内存首地址指针, 内存由调用者申请, VISP释放
   ULONG *pulLeaseNum: 调用者返回的租期记录个数 */
typedef ULONG (*LEASE_READ_HOOK)(DHCP4C_LEASE_S **ppstLease, ULONG *pulLeaseNum);

/* 写DHCP租期文件的钩子函数原型
   ULONG ulDelFlag: 为0表示写入记录, 如果存在接口名相同的记录则将其覆盖; 为1表示删除接口名相同的记录
   DHCP4C_LEASE_S *pstLease: 租期记录指针, 指向的内存由VISP申请与释放 */
typedef ULONG (*LEASE_WRITE_HOOK)(ULONG ulDelFlag, DHCP4C_LEASE_S *pstLease);

/*VISP新增配置检查回调函数注册钩子
（产品在该配置检查回调函数钩子中实现配置检查或者异步配置检查的通知)*/
typedef ULONG (*TCPIP_PROCDHCP_CONF_CHECK_HOOK_FUNC) (
                                                        UCHAR *pucUdpBuf,
                                                        ULONG ulRecvLen,
                                                        ULONG ulIfIndex,
                                                        ULONG ulCorrelator);
/*配置检查注册链表结构*/
typedef struct tagDHCP4C_CONF_CHECK_HOOK
{
    ULONG ulIfIndex;    /*需要做配置检查的接口*/
    ULONG ulCorrelator; /*配置检查关联器,VISP调用产品配置检查回调函数时交给产品的。*/
    ULONG ulCheckResult;    /*产品反馈的配置结果。VISP会在DHCPDECLINE报文中将该结果作为选项带给DHCP服务器。*/
    TCPIP_PROCDHCP_CONF_CHECK_HOOK_FUNC pfCfgCheckHookFunc; /*配置检测函数*/
    struct tagDHCP4C_CONF_CHECK_HOOK *pstNext;
}DHCP4C_CONF_CHECK_HOOK_S;


/*Add by x57575 for Nodeb CR BC3D02026*/
/* Modified by y00176567/z00171897, at 2011-07-06. 修改原因: 支持UTRP自启动 */
/* 单播处理钩子函数增加源IP参数 */
typedef struct tagTCPIP_PROCDHCP_UNICAST_HOOK_FUNC
{
    ULONG (*pfTCPIP_ProcdhcpcUnicastOut)(ULONG ulIfIndex,
                                ULONG *pulDhcpServerAddr,
                                   ULONG *pulDhcpSrcAddr,
                                        UCHAR *pucUdpBuf,
                                        ULONG ulSendLen);

    ULONG (*pfTCPIP_ProcdhcpcUnicastIn)(ULONG ulIfIndex,
                                       UCHAR *pucUdpBuf,
                                       ULONG ulRecvLen);
}TCPIP_PROCDHCP_UNICAST_HOOK_FUNC;

/* DHCP offer报文vlan信息对外通知回调函数原型
*  ULONG ulIfIndex: 接口索引
*  USHORT usVlanInfo: VLAN信息,包括tag,优先级,VLANID.(主机序)
*/
typedef VOID (*DHCP_VLAN_NOTIFY_HOOK)(ULONG ulIfIndex, USHORT usVlanInfo);

typedef struct tagDHCP4C_PROC_VALID_HOOK
{
    UCHAR *pucUdpBuf;   /* DHCP报文，含UDP首部 */
    ULONG ulRecvLen;    /* 报文长度 */
    ULONG ulMsgType;    /* 报文类型(当前版本仅支持Offer和ACK)
                            #define DHCP4C_DHCPDISCOVER          1
                            #define DHCP4C_DHCPOFFER             2
                            #define DHCP4C_DHCPREQUEST           3
                            #define DHCP4C_DHCPDECLINE           4
                            #define DHCP4C_DHCPACK               5
                            #define DHCP4C_DHCPNAK               6
                            #define DHCP4C_DHCPRELEASE           7
                            #define DHCP4C_DHCPINFORM            8*/
    USHORT usVlanInfo;  /* vlan 信息*/
    USHORT usRes;       /* 保留字段 */
}DHCP4C_PROC_VALID_HOOK_S;
typedef ULONG (*TCPIP_PROC_VALID_DHCP_HOOK_FUNC)(DHCP4C_PROC_VALID_HOOK_S *pInfo);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcp4cStatics
* Date Created: 2012-08-17
*       Author: zhongyu206043
*  Description: 获取DHCP的协商统计信息。
*        Input: ULONG ulIfIndex:
*               DHCP4CSTATISTIC_S * pstStat:启动DHCP的接口索引
*       Output: pstStat：指向结构体DHCP4CSTATISTIC_S
*                        的指针。其所指向的内存由用户负责申请和释放。
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhongyu206043           Create for S.DHCP.1.1
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcp4cStatics(ULONG ulIfIndex,DHCP4CSTATISTIC_S * pstStat);

/*******************************************************************************
*    Func Name: TCPIP_DhcpcDoFsmSelecting
* Date Created: 2012-08-17
*       Author: zhongyu206043
*  Description: 触发DHCP Client模块完成Selecting状态处理。
*               只有当DHCP模块处于Selecting时才能使用。
*        Input: DHCP4C_FSM_SELECT_S *pstOfferInfo:所选择的DHCP Server的Offer报文
*       Output: 
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhongyu206043           Create for S.DHCP.1.1
*
*******************************************************************************/
extern ULONG TCPIP_DhcpcDoFsmSelecting(DHCP4C_FSM_SELECT_S *pstOfferInfo);


/*******************************************************************************
*    Func Name: TCPIP_DhcpRmtClient
* Date Created: 2009-11-18
*       Author: w60786
*  Description: 在LoopBack口上指定出接口使能DHCP，以支持DHCP over IPsec 功能
*        Input: ULONG ulLoopbackIfIndex: 使能DHCP功能的LoopBack口索引
*               ULONG ulOutIfIndex: 发送DHCP报文的出接口索引
*       Output: 
*       Return: 成功:VOS_OK;  其他:返回失败
*      Caution: 1. 该功能不支持备份.
*               2. 该API用于满足符合RFC3456的远程DHCP地址获取.ulOutIfIndex接口上需要使能IPSEC功能。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-18   w60786           Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_DhcpRmtClient(ULONG ulLoopbackIfIndex, ULONG ulOutIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_DhcpClient
*  Description: 使能/去使能DHCP Client
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:使能标记  0-去使能;  1-使能NodeB特殊DHCP; 2-使能普通DHCP
*       Output: 
*       Return: 成功:VOS_OK;  其他:返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-07   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_DhcpClient(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_ReleaseDhcp
*  Description: 释放DHCPC地址信息
*        Input: ULONG ulIfIndex:接口索引,若为零释放所有使用DHCP配置地址的接口的地址
*       Output: 无
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_ReleaseDhcp(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_RenewDhcp
*  Description: 发送更新某接口租期的消息
*        Input: ULONG ulIfIndex-接口索引值,若为零更新所有使用DHCP配置地址的接口的地址
*       Output: 无
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RenewDhcp(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcCiaddr
*  Description: 配置Ciaddr值信息:
*               ulCiaddr为0 时，清除对应的pConfigNode节点
*               ulCiaddr不为0时，增加对应的pConfigNode节点，配置 ulCiaddr的值
*               ulCiaddr为网络序,用户在传入时需要做一层主机序到网络序的转换
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulCiaddr:要配置的Ciaddr值
*       Output: 无
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcCiaddr(ULONG ulIfIndex, ULONG ulCiaddr);

/*******************************************************************************
*    Func Name: TCPIP_AddDhcpcOptionsInfo
*  Description: 配置Client ID项或VSI项或60选项值
*        Input: ULONG ulIfIndex: 接口索引值；
*               UCHAR ucCode:    子项的CODE域
*                                目前只支持子项域   43----VSI选项
*                                                   61----CID选项
*               UCHAR ucLen:     子项的长度域
*               UCHAR *pucValue: 子项的值域
*       Output: 无
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_AddDhcpcOptionsInfo(ULONG ulIfIndex, UCHAR ucCode, UCHAR ucLen, UCHAR *pucValue);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcOptionsInfo
*  Description: 获取 DHCP的配置信息，主要包括Ciaddr,VSI,CID.
*        Input: ULONG ulIfIndex: 接口索引
*               DHCP4C_OPTIONINFO_S *pstDhcpOptions: 获取信息指针
*       Output: 无
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcOptionsInfo(ULONG ulIfIndex, DHCP4C_OPTIONINFO_S *pstDhcpOptions);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcpcOptionsInfo
*  Description: 显示DHCPC的选项信息
*        Input: CHAR *pstIfName:接口名称
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-05-14   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcpcOptionsInfo(CHAR *pstIfName);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcInfo
*  Description: 获取DHCP租约相关信息
*        Input: ULONG ulIfIndex:接口索引
*               DHCP4C_DISPLAYINFO_S *pstDhcp4cInfo:DHCP租约相关信息指针
*       Output: 无
*       Return: VOS_OK成功,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcInfo(ULONG ulIfIndex, DHCP4C_DISPLAYINFO_S *pstDhcp4cInfo);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcpcInfo
*  Description: 显示指定接口DHCP Client租约信息
*        Input: CHAR *pstIfName:接口名称
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcpcInfo(CHAR *pstIfName);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcHADbg
*  Description: 设置调试开关的接口函数
*        Input: ULONG ulDbg:设置的调试开关值
*       Output: 无
*       Return: VOS_OK成功;VOS_ERR失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcHADbg
*  Description: 获取调试开关的接口函数
*        Input: 无
*       Output: ULONG *pulDbg:获取的调试开关值
*       Return: VOS_OK成功;VOS_ERR失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcHADbg(ULONG *pulDbg);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcDebug
*  Description: 设置接口dhcp配置调试开关，某类型的调试
*                开关不管全局的还是局部的，只要使能了该类型调试信息就会输出
*        Input: ULONG ulIfIndex:接口索引值为零对所有接口有效
*               ULONG ulSetYes:为真打开调试开关,为0关闭调试开关
*               ULONG ulDHCP4CDebugType:调试开关类型,类型值如下
*               DHCP4C_DEBUG_FLAG_PACKET        0x01
*               DHCP4C_DEBUG_FLAG_EVENT         0x02
*               DHCP4C_DEBUG_FLAG_ERROR         0x04
*               DHCP4C_DEBUG_FLAG_ALL           0x07
*       Output:
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcDebug(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulDHCP4CDebugType);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcpcDebug
*  Description: 显示DHCPC的调试开关信息.注:不包括HA开关
*        Input: VOID
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-05-14   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcpcDebug(VOID);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncProcDhcpcPacketHook
*  Description: DHCP4C接收处理的钩子函数注册接口
*        Input: TCPIP_PRODHCP_HOOK_FUNC pfHookFuc:提供给用户注册的DHCP4C接收处理的函数指针
*       Output: 无
*       Return: VOS_OK成功,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncProcDhcpcPacketHook(TCPIP_PROCDHCP_HOOK_FUNC pfHookFuc);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcDefaultAddr
*  Description: 配置DHCP的默认地址和子网掩码
*        Input: ULONG ulIfIndex: 接口索引号
*               ULONG ulIpAddr: 所添加的地址（主机序）
*               ULONG ulSubnetMask: 所添加的地址的子网掩码（主机序）
*       Output: 无
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcDefaultAddr(ULONG ulIfIndex, ULONG ulIpAddr, ULONG ulSubnetMask);
/*******************************************************************************
*    Func Name: TCPIP_DelDhcpcDefaultAddr
*  Description: 清除DHCP的默认地址和子网掩码
*        Input: ULONG ulIfIndex: 接口索引号
*       Output: 
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_DelDhcpcDefaultAddr(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcDefaultAddr
*  Description: 获取DHCP的默认地址和子网掩码
*        Input: ULONG ulIfIndex: 接口索引
*       Output: ULONG *pulIpAddr: 默认地址（主机序）
*               ULONG *pulSubnetMask: 默认子网掩码（主机序）
*       Return: 成功返回DHCP4C_SUCCESS,其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcDefaultAddr(ULONG ulIfIndex, ULONG *pulIpAddr,ULONG *pulSubnetMask);
/*******************************************************************************
*    Func Name: TCPIP_ShowDhcpcDefaultAddr
*  Description: 显示DHCP的默认地址和子网掩码
*        Input: CHAR *pstIfName:接口名称
*       Output: 无
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-24   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcpcDefaultAddr(CHAR *pstIfName);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetDhcpcIP
*  Description: 注册DHCP Client信息上报钩子处理函数
*        Input: GET_DHCP_CLIENT_IP_HOOK_FUN pfGetDHCPClientIP
*
*       Output: 
*       Return: VOS_ERR
                VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetDhcpcIP (GET_DHCP_CLIENT_IP_HOOK_FUN pfGetDHCPClientIP);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetDhcpsIP
* Date Created: 2009-02-05
*       Author: mafeng(59090)
*  Description: 注册DHCP Server IP信息上报钩子处理函数
*        Input: GET_DHCP_SERVER_IP_HOOK_FUN pfGetDHCPServerIP:
*       Output: 
*       Return: DHCP4C_FAILURE
*               DHCP4C_SUCCESS
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-05   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetDhcpsIP (GET_DHCP_SERVER_IP_HOOK_FUN pfGetDHCPServerIP);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcIP
*  Description: DHCP Client获取信息进行配置下发
*        Input: ULONG ulIfIndex,
                ULONG ulDHCPClientIP
*               ULONG ulDHCPClientIPMask,
                ULONG aulDNSIP[DHCP4C_DNSIP_NUM],
                ULONG aulGatewayIP[DHCP4C_ROUTER_NUM]
                CHAR pcDomainName[DHCP4C_DOMAINNAME_SIZE],
                ULONG ulFlag
*       Output: 
*       Return: DHCP4C_HA_IS_SMOOTHING:系统处于平滑或手动倒换阶段
                DHCP4C_NOT_3D_MODE:         非三维模式下
                DHCP4C_API_COM_NULL:        组件为空
                DHCP4C_PARA_ERR:            参数错误
                DHCP4C_CONFIGERR_INDEX:     无效接口索引
                DHCP4C_CONFIGERR_CFGDHCPIP: 配置DHCP 地址失败
                DHCP4C_CONFIGERR_INDEX:     接口索引无效
                DHCP4C_SUCCESS:             处理成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcIP(ULONG ulIfIndex,
                                          ULONG ulDHCPClientIP,
                                          ULONG ulDHCPClientIPMask,
                                          ULONG aulDNSIP[DHCP4C_DNSIP_NUM],
                                          ULONG aulGatewayIP[DHCP4C_ROUTER_NUM],
                                          CHAR pcDomainName[DHCP4C_DOMAINNAME_SIZE],
                                          ULONG ulFlag
                                          );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDhcpcAddOptionHook
*  Description: 用户注册添加DHCP Client选项的钩子函数
*        Input: gpfDHCPADDOPTION_HOOK_FUNC pfHookFunc:钩子函数指针
*       Output:
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-16   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDhcpcAddOptionHook(gpfDHCPADDOPTION_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcTos
*  Description: 设置DHCP4C模块的tos值
*        Input: UCHAR ucTos: 设置的tos值，值域有效
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcTos(UCHAR ucTos);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcTos
*  Description: 获取dhcp4c模块配置的tos值
*        Input: UCHAR *pucTos: 保存获取的tos值
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcTos(UCHAR *pucTos);
/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcIgnoreOption
*  Description: 设置是否可以接收server发送的携带50/55/57选项的报文
*        Input: ULONG ulSetYes: 要设置的值;0/1
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-20    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcIgnoreOption(ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcIgnoreOption
*  Description: 获取忽略50/55/57选项标记值
*        Input: ULONG *pulSetYes: 保存输出的值
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-20    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcIgnoreOption(ULONG *pulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDhcpLeaseHook
*  Description: 注册DHCP租期文件读写函数
*        Input: LEASE_WRITE_HOOK pfWriteHook: 写DHCP租期文件的钩子函数
*               LEASE_READ_HOOK pfReadHook: 读取DHCP租期文件的钩子函数
*       Output: 
*       Return: DHCP4C_SUCCESS
*               DHCP4C_WRITE_LEASE_NULL
*               DHCP4C_READ_LEASE_NULL
*      Caution: 必须在初始化VISP协议栈之前注册，且两个钩子函数必须同时注册
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-17  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDhcpLeaseHook(LEASE_WRITE_HOOK pfWriteHook, LEASE_READ_HOOK pfReadHook);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncProcDhcpcConfCheckHook
*  Description: 注册接口的配置检测函数
*        Input: ulIfIndex :接口索引
*               pfCfgCheckHook 配置检测钩子函数
*       Output: 
*       Return: DHCP4C_SUCCESS
*               DHCP4C_FAILURE
*               DHCP4C_CONFIGERR_MEMORY
*               DHCP4C_REG_UNREG_FAIL
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-13  r62469     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncProcDhcpcConfCheckHook(ULONG ulIfIndex,
                                    TCPIP_PROCDHCP_CONF_CHECK_HOOK_FUNC pfCfgCheckHook);

/*******************************************************************************
*    Func Name: TCPIP_UnRegFuncProcDhcpcConfCheckHook
*  Description: 去注册接口的配置检测函数
*        Input: ulIfindex :接口索引
*       Output: 
*       Return: DHCP4C_SUCCESS
*               DHCP4C_REG_UNREG_FAIL
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-13  r62469     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_UnRegFuncProcDhcpcConfCheckHook(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetDhcpcUserCheckResult
*  Description: 用户通知检查结果
*        Input: ulIfIndex :接口索引
*               ulCorrelator:配置检查关联器。VISP调用产品配置检查回调函数时交给产品的。
*               ulCheckResult: DHCP4C_CHECKOK(0)其它错误码为用户错误码，由用户定义和解析
*       Output: 
*       Return: DHCP4C_SUCCESS
*               DHCP4C_FAILURE
*      Caution: 产品在检查到配置冲突后，需要先调用TCPIP_RegFuncDhcpcCfgCheckOptionHook注册，
注册的选项由产品自定义，选项内容是错误码。再执行该函数。
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-13  r62469     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDhcpcUserCheckResult(ULONG ulIfIndex, ULONG ulCorrelator, ULONG ulCheckResult);

/*Add by x57575 for Nodeb CR BC3D02026*/
/*******************************************************************************
*    Func Name: TCPIP_RegFuncProcDhcpcUnicastHook
* Date Created: 2009-09-09
*       Author: xujun57575
*  Description: 提供产品注册DHCPC报文处理的钩子
*        Input: TCPIP_PROCDHCP_UNICAST_HOOK_FUNC pfProcDhcpcHookFunc:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-09   xujun57575              Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncProcDhcpcUnicastHook(TCPIP_PROCDHCP_UNICAST_HOOK_FUNC *pfProcDhcpcHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcpcSessionIfIndexByPkt
* Date Created: 2009-11-28
*       Author: mafeng(59090)
*  Description: 根据DHCPClient报文获取DHCPC会话的接口索引值(只对DHCPServer
*               发送到本基站发送的DHCPC报文进行处理,非本基站报文不处理返回非0)
*        Input: UCHAR *pucPktBuf:完整的DHCPClient报文,为DHCPC报文字符串首地址
*               ULONG usPktLen:DHCPClient报文的长度，长度应大于240
*       Output: ULONG *pulIfIndex:该DHCPC报文对应的使能DHCPC功能的接口索引值
*                                 要求输入非空指针
*       Return: 0(VOS_OK)该报文为本基站(协议栈)的报文
*               非0(错误码)该报文不是本基站(协议栈)的报文
*      Caution: 返回非0即说明该报文不是本基站的报文，返回0表示该报文是本基站的
*               DHCPC报文，但是在把从该DHCPC报文获取到的地址配置到接口前需要
*               判断一下接口的接口索引值是否与该API返回的接口索引值相等，如果
*               不相等则不能配置到接口上。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-28   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcpcSessionIfIndexByPkt(UCHAR *pucPktBuf, ULONG usPktLen, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncDHCPVlanNotifyHook
* Date Created: 2010-11-03
*       Author: y171195(z171897)
*  Description: DHCP VLAN Scaning功能中,提供产品注册通知OFFER报文中携带的VLAN信息的钩子
*        Input: DHCP_VLAN_NOTIFY_HOOK pfDhcpVlanNotifyHook:产品提供的处理OFFER报文
*               中携带的VLAN信息的函数
*       Output: 
*       Return: VOS_OK: 成功
*               其他: 失败
*      Caution: 1.该钩子函数支持动态注册和解注册,所以产品必须在协议栈启动之后才能
*                 调用该接口注册和解注册.
*               2.该回调钩子函数中不能使用产品的信号量，否则可能会和VISP的信号量产生死锁。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-03   y171195(z171897)              Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDHCPVlanNotifyHook(DHCP_VLAN_NOTIFY_HOOK pfDhcpVlanNotifyHook);

/*******************************************************************************
*    Func Name: TCPIP_SetDHCPVlanScanning
* Date Created: 2010-11-03
*       Author: y171195(z171897)
*  Description: 使能/去使能DHCP VLAN Scaning功能
*        Input: ulIfIndex: 接口索引
*               ulEnable: 使能标记: 1:使能; 0:去使能
*               ulDelayTime: Discovery报文重传超时延迟时间,单位毫秒,取值范围[0,3600*1000]
*       Output: 
*       Return: VOS_OK: 成功
*               其他: 失败
*      Caution:
*      1.DHCP Vlan Scanning功能要求产品必须在接口上使能DHCP之前先使能DHCP Vlan Scanning功能,
*        否则DHCP Vlan Scanning功能可能无法正常运作。
*      2.DHCP Vlan Scanning功能指定的延时时间的有效性合理性由产品自行保证。
*        要求产品指定的延时时间要足够产品对DHCP discovery报文进行VLAN Scanning发送处理。
*        即要求产品指定的延迟时间要保证协议栈重传的discovery报文在VLAN Scanning发送处理完成后发出。
*      3.DHCP Vlan Scanning功能要求产品必须在以太接口上使能VLAN功能。并且不能设置只接收某一特定VLAN的报文.
*      4.DHCP VLAN Scaning功能不支持HA备份.
*      5.只有以太接口支持DHCP VLAN Scaning功能.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-03   y171195(z171897)              Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetDHCPVlanScanning(ULONG ulIfIndex, ULONG ulEnable, ULONG ulDelayTime);

/*******************************************************************************
*    Func Name: TCPIP_GetDHCPVlanScanning
* Date Created: 2010-11-03
*       Author: y171195(z171897)
*  Description: 使能/去使能DHCP VLAN Scaning功能状态查询
*        Input: ulIfIndex: 接口索引
*       Output: pulEnable: 使能标记: 1:使能; 0:去使能
*               pulDelayTime: Discovery报文重传超时延迟时间,单位毫秒,取值范围[0,3600*1000]
*       Return: VOS_OK: 成功
*               其他: 失败
*      Caution:
*      1.DHCP Vlan Scanning功能要求产品必须在接口上使能DHCP之前先使能DHCP Vlan Scanning功能,
*        否则DHCP Vlan Scanning功能可能无法正常运作。
*      2.DHCP Vlan Scanning功能指定的延时时间的有效性合理性由产品自行保证。
*        要求产品指定的延时时间要足够产品对DHCP discovery报文进行VLAN Scanning发送处理。
*        即要求产品指定的延迟时间要保证协议栈重传的discovery报文在VLAN Scanning发送处理完成后发出。
*      3.DHCP Vlan Scanning功能要求产品必须在以太接口上使能VLAN功能。并且不能设置只接收某一特定VLAN的报文.
*      4.DHCP VLAN Scaning功能不支持HA备份.
*      5.只有以太接口支持DHCP VLAN Scaning功能.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-03   y171195(z171897)              Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDHCPVlanScanning(ULONG ulIfIndex, ULONG *pulEnable, ULONG *pulDelayTime);

/*******************************************************************************
*    Func Name: TCPIP_GetDhcp4cStatistic
* Date Created: 2012-09-04
*       Author: heyijun 00218462
*  Description: 获取DHCP4C报文统计
*        Input: None
*       Output: DHCP4C_STATISTIC_S * pstStat:
*       Return: DHCP4C_SUCCESS or 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-04   heyijun 00218462        Create for DTS2012092900232
*
*******************************************************************************/
extern ULONG TCPIP_GetDhcp4cStatistic(DHCP4C_STATISTIC_S * pstStat);

/*******************************************************************************
*    Func Name: TCPIP_ClrDhcp4cStatistic
* Date Created: 2012-09-05
*       Author: heyijun 00218462
*  Description: DHCP4C统计清零
*        Input: NONE
*       Output: NONE
*       Return: DHCP4C_SUCCESS or 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-05   heyijun 00218462        Create for DTS2012092900232
*
*******************************************************************************/
extern ULONG TCPIP_ClrDhcp4cStatistic(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowDhcp4cStat
* Date Created: 2012-09-06
*       Author: heyijun 00218462
*  Description: 显示DHCP4C报文统计
*        Input: NONE
*       Output: NONE
*       Return: NONE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-06   heyijun 00218462        Create for DTS2012092900232
*
*******************************************************************************/
extern VOID TCPIP_ShowDhcp4cStat(VOID);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncProcDhcpcValidPacketHook
* Date Created: 2014-02-11
*       Author: likaikun213099
*  Description: 用户注册校验DHCP报文的钩子函数
*        Input: TCPIP_PROC_VALID_DHCP_HOOK_FUNC pfHookFuc:钩子函数
*       Output: NONE
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-11   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncProcDhcpcValidPacketHook (TCPIP_PROC_VALID_DHCP_HOOK_FUNC pfHookFuc);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _DHCP4C_API_H_ */

