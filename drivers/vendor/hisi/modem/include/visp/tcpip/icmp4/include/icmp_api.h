/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_api.h
*
*  Project Code: VISPV100R007
*   Module Name: 用户API头文件
*  Date Created: 2008-04-08
*        Author: zengshaoyang62531
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _ICMP4_API_H_
#define _ICMP4_API_H_

#ifdef __cplusplus
extern  "C"{
#endif /* __cplusplus */

#define     ICMP_MAXTYPE              19

/*设置ping allow list时的操作类型*/
#define ICMP_PINGALLOWLIST_ADD          0
#define ICMP_PINGALLOWLIST_DELSINGLE    1
#define ICMP_PINGALLOWLIST_DELALL       2

#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH            47              /* 接口名长度 */
#endif

#define     ICMP_ECHOREPLY            0     /* echo reply */

#define     ICMP_UNREACH              3     /* 目的不可达 dest unreachable, codes: */
#define     ICMP_UNREACH_NET          0     /* 网络不可达 bad net */
#define     ICMP_UNREACH_HOST         1     /* 主机不可达 bad host */
#define     ICMP_UNREACH_PROTOCOL     2     /* 协议不可达 bad protocol */
#define     ICMP_UNREACH_PORT         3     /* 端口不可达 bad port */
#define     ICMP_UNREACH_NEEDFRAG     4     /* 需要进行分片但设置了不分片比特 IP_DF caused drop */
#define     ICMP_UNREACH_SRCFAIL      5     /* 源站选路失败 src route failed */
#define     ICMP_UNREACH_NET_UNKNOWN  6     /* 目的网络不认识 unknown net */
#define     ICMP_UNREACH_HOST_UNKNOWN 7     /* 目的主机不认识 unknown host */
#define     ICMP_UNREACH_ISOLATED     8     /* 源主机被隔离 src host isolated */
#define     ICMP_UNREACH_NET_PROHIB   9     /* 目的网络被强制禁止 prohibited access */
#define     ICMP_UNREACH_HOST_PROHIB  10    /* 目的主机被强制禁止 ditto */
#define     ICMP_UNREACH_TOSNET       11    /* 由于服务器类型tos，网络不可达 bad tos for net */
#define     ICMP_UNREACH_TOSHOST      12    /* 由于服务器类型tos，主机不可达 bad tos for host */

#define     ICMP_SOURCEQUENCH         4     /* 源端被关闭，报文丢失 packet lost, slow down */

#define     ICMP_REDIRECT             5     /* 重定向 shorter route, codes: */
#define     ICMP_REDIRECT_NET         0     /* 对网络重定向 for network */
#define     ICMP_REDIRECT_HOST        1     /* 对主机重定向 for host */
#define     ICMP_REDIRECT_TOSNET      2     /* 对服务类型和网络重定向 for tos and net */
#define     ICMP_REDIRECT_TOSHOST     3     /* 对服务类型和主机重定向 for tos and host */

#define     ICMP_ECHO                 8     /* 请求回显 echo service */
#define     ICMP_ROUTERADVERT         9     /* 路由器通告 router advertisement */
#define     ICMP_ROUTERSOLICIT        10    /* 路由器请求 router solicitation */

#define     ICMP_TIMXCEED             11    /* 超时 time exceeded, code: */
#define     ICMP_TIMXCEED_INTRANS     0     /* 传输期间生存时间为零 ttl==0 in transit */
#define     ICMP_TIMXCEED_REASS       1     /* 在数据报组装期间生存时间为零 ttl==0 in reass */

#define     ICMP_PARAMPROB            12    /* 坏的IP首部 ip header bad */
#define     ICMP_PARAMPROB_OPTABSENT  1     /* 缺少必需的选项 req. opt. absent */
#define     ICMP_BAD_IPHEAD           0     /* 坏的IP首部 bad ip head */

#define     ICMP_TSTAMP               13    /* 时间戳请求 timestamp request */
#define     ICMP_TSTAMPREPLY          14    /* 时间戳应答 timestamp reply */
#define     ICMP_IREQ                 15    /* 信息请求 information request */
#define     ICMP_IREQREPLY            16    /* 信息应答 information reply */
#define     ICMP_MASKREQ              17    /* 地址掩码请求 address mask request */
#define     ICMP_MASKREPLY            18    /* 地址掩码应答 address mask reply */
#define     ICMP_TOTALMSGS            19    /* 所有ICMP报文 total icmp messages,added by 8011 maye BYDD06214 */


#define     ICMP_MAXCODE              15


/* ICMP差错报文的防范开关值宏定义 */
#define ICMP_ATTACKGUARD_SWITCH_ALL            0xffffffff
#define ICMP_ATTACKGUARD_SWITCH_UNREACH        0x01
#define ICMP_ATTACKGUARD_SWITCH_REDIRECT       0x02
#define ICMP_ATTACKGUARD_SWITCH_TIMXCEED       0x04
#define ICMP_ATTACKGUARD_SWITCH_MASKREP        0x08
#define ICMP_ATTACKGUARD_SWITCH_TSREP          0x10    /* 2010-9-6, z00142640 modified for 同步BC3D03521 */
#define ICMP_ATTACKGUARD_SWITCH_PARAMPROB      0x20    /* 2010-10-20, pKF34550 modified for VISP183SZ-76:控制面DFNS,支持IP选项错误攻击防范 */
#define ICMP_ATTACKGUARD_SWITCH_SRCADDRANY     0x40    /* 2010-10-21, cKF34558 modified for VISPDEVSZ-88:控制面DFNS,支持ICMP仿冒攻击请求报文源地址为 0.0.0.0 防范 */
/*Added by wangbin, 当ping请求的目的IP地址为广播或者为本机已经加入的组播地址时，防攻击开关值, 2015/10/21   问题单号:DTS2015102607862 */
#define ICMP_ATTACKGUARD_SWITCH_DSTBCASTORMCAST   0x80
/* End of Added by wangbin, 2015/10/21   问题单号:DTS2015102607862 */

typedef enum tagICMP_ERR
{
    ICMP_PINGALLOWLIST_OK = 0,
    ICMP_PINGALLOWLIST_LISTEMPTY,       /*ping allow list为空*/
    ICMP_PINGALLOWLIST_LISTFULL,        /*ping allow list已满*/
    ICMP_DEBUGFLAG_ERR,                 /*icmp模块调试开关输入值非法*/
    ICMP_NULL_POINTER,                  /*指针为空*/
    ICMP_COMP_NULL,                     /*ICMP组件为空*/
    IFNET_COMP_NULL,                    /*ifnet组件虚表为空*/
    ICMP_IFNET_NULL,                    /*ifnet指针为空*/
    ICMP_PINGALLOWLIST_INVALIDPARAM,    /*参数无效*/
    ICMP_PINGALLOWLIST_ADDREXIST,       /*地址已经存在*/
    ICMP_PINGALLOWLIST_ADDRNOTEXIST,    /*地址不存在*/
    ICMP_PINGALLOWLIST_MEMERR,          /*内存错误*/
    ICMP_HA_IS_SMOOTHING,               /*正在平滑处理*/
    ICMP_IS_L2PORT,                     /* 输入的目标接口是一个二层端口 */
    ICMP_FLOWSTAT_WRONG_INPUT,
    ICMP_FLOWSTAT_EXIST,
    ICMP_FLOWSTAT_NOT_EXIST,
    ICMP_FLOWSTAT_WRONG_VRF,
    ICMP_FLOWSTAT_MALLOC_FAIL,
    ICMP_FLOWSTAT_VRF_REG_FAIL,
    ICMP_STAT_NOT_EXIST,
    ICMP_STAT_NOT_ENABLE,
    
}ICMP_ERR_E;
/*
 * Variables related to this implementation
 * of the internet control message protocol.
 */
typedef struct  tagICMPSTAT
{
    /* statistics related to icmp packets generated */
    /* commented by chenxia for D23636, 2003/06/26 */
    /* icps_ulError含义改为产生的ICMP报文因为种种原因未能发出去的数目, 用于对应mib中的icmpOutErrors */
    ULONG   icps_ulError;       /* # of calls to icmp_error */ 
    ULONG   icps_ulOldShort;    /* no error 'cuz old ip too short */
    ULONG   icps_ulOldIcmp;     /* no error 'cuz old was icmp */
    ULONG   icps_ulOutHist_a[ICMP_MAXTYPE + 1];
    ULONG   icps_ulOutTtlExceed;
    /* statistics related to input messages processed */
    ULONG   icps_ulBadCode;     /* icmp_code out of range */
    ULONG   icps_ulTooShort;    /* packet < ICMP_MINLEN */
    ULONG   icps_ulChecksum;    /* bad checksum */
    ULONG   icps_ulBadLen;      /* calculated bound mismatch */
    ULONG   icps_ulReflect;     /* number of responses */
    ULONG   icps_ulInHist_a[ICMP_MAXTYPE + 1];
    ULONG   icps_ulInTtlExceed;
}ICMPSTAT_S;

typedef struct tagICMPMSG
{    
    MBUF_S*   pstMbuf; 
    LONG      lType;  
    LONG      lCode;
    ULONG     ulDest;
    UCHAR     szIfName[MAX_IF_NAME_LENGTH+1];
} ICMP_MSG_S;

typedef struct  tagICMPFlowStat_Echo
{
    ULONG ulLocalIPAddr;        /* Local IP Addres, host order */
    ULONG ulRemoteIPAddr;       /* Peer address, host order */
    ULONG ulEchoRequest;        /* Echo Request number of packets */
    ULONG ulEchoReplay;         /* Echo Replay number of packets */
    ULONG ulSendErr;            /* The client sends the number of failures, 
                                    (unable to send ICMP packet outside) */
}ICMPFLOWSTAT_ECHO_S;

typedef struct  tagICMPFlowStat_PortUnReach
{
    ULONG ulLocalIPAddr;        /* The end of the address, host sequence */
    ULONG ulRemoteIPAddr;       /* peer address, host sequence */
    ULONG ulCount;              /* Count of the statistics */
    ULONG ulSendErr;            /* The client sends the number of failures,
                                    (unable to send ICMP packet outside) */
}ICMPFLOWSTAT_PORTUNREACH_S;

typedef enum tagTcpipICMPFlowStatType
{
    ICMP_LOCAL_ECHO_FLOW_STAT = 0,      /* 0. Local Echo Flow stats */
    ICMP_REMOTE_ECHO_FLOW_STAT,         /* 1. Remote Echo Flow stats */
    ICMP_LOCAL_PORT_UNREACH_FLOW_STAT,  /* 2. Local Port unreachable flow stats */
    ICMP_REMOTE_PORT_UNREACH_FLOW_STAT, /* 3. Remote Port unreachable flow stats */

    ICMP_FLOW_STAT_TYPE_ALL  = 0xff     /* 255. Used to select all flow stat types*/
} TCPIP_ICMP_FLOW_STAT_TYPE_E;

typedef struct tagICMPFlowStat_Cfg
{
    UCHAR ucFlowStatType;       /* Flow statistics type */
    UCHAR ucNumber;             /* Number of statistics */
    UCHAR ucRes[2];
}ICMPFLOWSTAT_CFG_S;

/* Each element of array hold the count for currepsonding icmp type */
typedef struct tagICMPSTATVRF
{
    ULONG   icps_ulOutHist_a[ICMP_MAXTYPE + 1][ICMP_MAXCODE + 1]; /* Stores count of icmp output packets */
    ULONG   icps_ulInHist_a[ICMP_MAXTYPE + 1][ICMP_MAXCODE + 1];  /* Stores count of icmp input packets */
}ICMPSTATVRF_S;


extern ULONG TCPIP_ICMP_Error( ICMP_MSG_S* pstIcmpErrSend );
/*******************************************************************************
*    Func Name: TCPIP_ClrIcmpIfSta
*  Description: 清除接口的icmp统计信息(部分)
*        Input: ULONG ulIfIndex:接口索引
*       Output: VOS_OK
*               ICMP_COMP_NULL:icmp组件虚表为空
*               ICMP_IFNET_NULL:ifnet指针为空
*               ICMP_NULL_POINTER:指针为空
*       Return: 
*      Caution: IP控制块指针在组件接口中已有判断，外层不再判断
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrIcmpIfSta(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ClrIcmpStat
*  Description: 清除所有接口上的icmp统计信息，清除全局icmp统计信息
*        Input: 
*       Output: 
*       Return: VOS_OK
*               ICMP_COMP_NULL:组件虚表为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrIcmpStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_DisablePing
*  Description: 设置禁PING功能使能/去使能
*        Input: ULONG ulSetYes:1 --- 使能，0 --- 去使能
*       Output: 
*       Return: VOS_OK
*               PUBLIC_HA_IS_SMOOTHING:public模块在手动倒换或平滑处理过程中
*               ICMP_COMP_NULL:icmp组件虚表为空
*               VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_DisablePing (ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_GetDisablePingSwitch
*  Description: 获取禁PING功能使能/去使能标志
*        Input: ULONG * pulSwitch:禁PING使能/去使能标志
*       Output: 
*       Return: VOS_OK
*               ICMP_NULL_POINTER:指针为空
*               ICMP_COMP_NULL:ICMP组件虚表为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDisablePingSwitch(ULONG *pulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_GetIcmpDebugFlag
*  Description: 获取icmp模块的调试开关
*        Input: 
*       Output: ULONG *pulDebugFlag:icmp模块的调试开关
*       Return: VOS_OK
*               ICMP_COMP_NULL:组件虚表为空
*               ICMP_NULL_POINTER:指针为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIcmpDebugFlag(ULONG *pulDebugFlag);
/*******************************************************************************
*    Func Name: TCPIP_GetIcmpStat
*  Description: 
*        Input: 
*       Output: ICMPSTAT_S* pstStat:
*       Return: VOS_OK
*               ICMP_COMP_NULL:组件虚表为空
*               ICMP_NULL_POINTER:指针为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIcmpStat (ICMPSTAT_S* pstStat);
/*******************************************************************************
*    Func Name: TCPIP_SetIcmpDebugFlag
*  Description: 设置icmp模块调试开关
*        Input: ULONG ulDebugFlag:调试开关，0 --- 关闭，1 --- 打开
*       Output: VOS_OK
*               ICMP_COMP_NULL:组件虚表为空
*               ICMP_DEBUGFLAG_ERR:调试开关值错误
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIcmpDebugFlag(ULONG ulDebugFlag);
/*******************************************************************************
*    Func Name: TCPIP_ShowIcmp4Statistic
*  Description: 显示icmp模块统计信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIcmp4Statistic(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetPingAllowList
*  Description: 设置ping allow list，0-新增地址;1-删除指定的地址;2-删除所有地址，
*               此时不判断地址和掩码
*        Input: ULONG ulOperation:操作类型 0-新增地址;1-删除指定的地址;2-删除所有地址
*               ULONG ulIpAddr:地址(主机序)
*               ULONG ulMask:子网掩码(主机序)
*       Output: 
*       Return: 成功 ICMP_PINGALLOWLIST_OK
*               失败
*                    ICMP_HA_IS_SMOOTHING:              处于平滑处理或手动倒换
*                    ICMP_PINGALLOWLIST_LISTEMPTY:      ping allow list为空
*                    ICMP_PINGALLOWLIST_INVALIDPARAM:   参数无效
*                    ICMP_PINGALLOWLIST_ADDREXIST:      地址已经存在
*                    ICMP_PINGALLOWLIST_LISTFULL:       ping allow list已满
*                    ICMP_PINGALLOWLIST_MEMERR:         内存错误
*                    ICMP_PINGALLOWLIST_ADDRNOTEXIST:   地址不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-14   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPingAllowList (ULONG ulOperation, ULONG ulIpAddr, ULONG ulMask);
/*******************************************************************************
*    Func Name: TCPIP_ShowPingAllowList
*  Description: 显示ping allow list
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-14   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPingAllowList (VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetIcmpAttackGuardSwitch
* Date Created: 2009-09-15
*       Author: wuhailan103194
*  Description: 设置ICMP差错类型及信息类型攻击防范开关
*        Input: ULONG ulSwitch:开关
*                              0 关闭, 默认关闭
*                              ICMP_ATTACKGUARD_SWITCH_ALL 0xffffffff 打开全部差错类型防攻击开关
*                              ICMP_ATTACKGUARD_SWITCH_UNREACH 0x01 不可达差错类型防攻击开关
*                              ICMP_ATTACKGUARD_SWITCH_REDIRECT 0x02 重定向差错类型防攻击开关
*                              ICMP_ATTACKGUARD_SWITCH_TIMXCEED 0x04 TTL声明周期类差错类型防攻击开关
*                              ICMP_ATTACKGUARD_SWITCH_MASKREP  0x08 响应地址掩码请求的开关
*                              ICMP_ATTACKGUARD_SWITCH_TSREP    0x10 响应时间戳请求的开关
*                              ICMP_ATTACKGUARD_SWITCH_PARAMPROB 0x20 IP首部选项错误回应的差错报文开关
*                              ICMP_ATTACKGUARD_SWITCH_SRCADDRANY 0x40 ICMP仿冒攻击请求报文源地址为0.0.0.0防范开关
*       Output: 
*       Return: 成功VOS_OK,其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIcmpAttackGuardSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIcmpAttackGuardSwitch
* Date Created: 2009-09-22
*       Author: wuhailan103194
*  Description: 获取ICMP差错类型及信息类型攻击防范开关
*        Input: 
*       Output: ULONG *pulSwitch:返回的开关值
*                              0 关闭, 默认关闭
*                              ICMP_ATTACKGUARD_SWITCH_ALL 0xffffffff 打开全部差错类型防攻击开关
*                              ICMP_ATTACKGUARD_SWITCH_UNREACH 0x01 不可达差错类型防攻击开关
*                              ICMP_ATTACKGUARD_SWITCH_REDIRECT 0x02 重定向差错类型防攻击开关
*                              ICMP_ATTACKGUARD_SWITCH_TIMXCEED 0x04 TTL声明周期类差错类型防攻击开关
*                              ICMP_ATTACKGUARD_SWITCH_MASKREP  0x08 响应地址掩码请求的开关
*                              ICMP_ATTACKGUARD_SWITCH_TSREP    0x10 响应时间戳请求的开关
*                              ICMP_ATTACKGUARD_SWITCH_PARAMPROB 0x20 IP首部选项错误回应的差错报文开关
*                              ICMP_ATTACKGUARD_SWITCH_SRCADDRANY 0x40 ICMP仿冒攻击请求报文源地址为0.0.0.0防范开关
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-22   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIcmpAttackGuardSwitch(ULONG *pulSwitch);

/* 获取自午夜0时到当前时刻的系统时间的钩子函数原型 */
typedef ULONG (*ICMP_GETTMSINCEMNHT_HOOK_FUNC)(VOID);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetTmSinceMnhtHook
* Date Created: 2009-07-29
*       Author: z00104207
*  Description: 注册获取自午夜0时到当前时刻的系统时间的钩子函数
*        Input: ICMP_GETTMSINCEMNHT_HOOK_FUNC pfHookFunc: 钩子函数指针
*       Output: 
*       Return: 
*      Caution: 返回的时间必须以毫秒表示，字节序是主机序
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-29   z00104207               Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetTmSinceMnhtHook(ICMP_GETTMSINCEMNHT_HOOK_FUNC pfHookFunc);


ULONG TCPIP_CreateIcmpFlowStat(ICMPFLOWSTAT_CFG_S *pstFlowStat);


ULONG TCPIP_GetIcmpFlowStat(UCHAR ucFlowStatType, ULONG ulVrfIndex, UCHAR *pucNumber, VOID *pStat);


ULONG TCPIP_ClearIcmpFlowStat(UCHAR ucFlowStatType, ULONG ulVrfIndex);


ULONG TCPIP_GetIcmpStatbyVrf(ULONG ulVrfIndex,ICMPSTATVRF_S *pstStat);


ULONG TCPIP_ClearIcmpStatbyVrf(ULONG ulVrfIndex);


ULONG TCPIP_EnableIcmpStat(ULONG ulFlag);

/*Added by yanlei00216869, 同步问题单-DTS2014102406433 CSEC扫描的地址暴露安全问题，针对控制器提供API开关，可动态控制, 2014/10/28   问题单号:DTS2014102701441 */
/*******************************************************************************
*    Func Name: TCPIP_SetIcmpSrcipProtectSwitch
* Date Created: 2014-10-25
*       Author: wangbin
*  Description: 设置ICMP源地址保护开关
*        Input:    
*       Output:  ulSwitch 0-  关闭, 1-打开,默认1:打开
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-25   wangbin               
*
*******************************************************************************/
ULONG TCPIP_SetIcmpSrcipProtectSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIcmpSrcipProtectSwitch
* Date Created: 2014-10-25
*       Author: wangbin
*  Description: 获取ICMP源地址保护开关
*        Input:    
*       Output:  pulSwitch 0-  关闭, 1-打开
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-25   wangbin               
*
*******************************************************************************/
ULONG TCPIP_GetIcmpSrcipProtectSwitch(ULONG *pulSwitch);
/* End of Added by yanlei00216869, 2014/10/28   问题单号:DTS2014102701441 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ICMP4_API_H_ */

