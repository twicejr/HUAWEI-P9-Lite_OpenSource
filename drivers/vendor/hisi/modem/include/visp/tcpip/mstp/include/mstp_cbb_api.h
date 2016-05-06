/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mstp_cbb_api.h
*
*  Project Code: VISP
*   Module Name:   
*  Date Created: 2008-10-23
*        Author: wuhailan
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME           DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-10-23   wuhailan       Create
*
*******************************************************************************/
#ifndef _MSTP_CBB_API_H_
#define _MSTP_CBB_API_H_


#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef MID_COMP_BASE
#define MID_COMP_BASE               0x0E000000   /*VISP部分定义的MID值*/
#endif

#ifndef MID_COMP_MSTP
#define MID_COMP_MSTP               ( MID_COMP_BASE + 0x00390000 )
#endif


typedef enum tagMSTP_ERRCODE
{
    MSTP_OK = VOS_OK,                 /* 0 OK */
    MSTP_ERR,                         /* 1 错误 */
    MSTP_ERR_DISABLE = MID_COMP_MSTP + 1, /* 2 协议未使能 */
    MSTP_ERR_PARAWRONG,               /* 3 输入参数错误 */
    MSTP_ERR_NULL_POINTER,            /* 4 指针为空 */
    MSTP_ERR_MBUF_NULL,               /* 5 MBUF指针为空 */
    MSTP_ERR_IFNET_NULL,              /* 6 IFNET指针为空 */
    MSTP_ERR_ISNOT_L2PORT,            /* 7 不是二层普通端口 */
    MSTP_ERR_GET_PORTINDEX_FAIL,      /* 8 获取port索引失败 */
    MSTP_ERR_PORTNUM_OVERFLOW,        /* 9 PORT索引超出范围 */
    
    MSTP_ERR_FUNCHOOK_NOTREG,         /* 10 函数指针未注册 */
    MSTP_ERR_TASK_IS_RUNNING,         /* 11 mstp任务已经运行 */
    MSTP_ERR_PRI_INVALID,             /* 12 任务优先级超出 */
    MSTP_ERR_CRT_TIMEQUE_FAIL,        /* 13 创建定时器队列失败 */
    MSTP_ERR_CRT_EVTQUE_FAIL,         /* 14 创建事件队列失败 */
    MSTP_ERR_CRT_PKTQUE_FAIL,         /* 15 创建报文队列失败 */
    MSTP_ERR_CRT_TASK_FAIL,           /* 16 创建mstp任务失败 */
    MSTP_ERR_CRT_TIMER_FAIL,          /* 17 创建定时器失败 */
    MSTP_ERR_ISNOT_INIT,              /* 18 MSTP还未初始化 */
    MSTP_ERR_L2IF_NOTREG,             /* 19 MSTP依赖的L2IF模块未注册 */ 
    
    MSTP_ERR_PPINOREGISTER,           /* 20 MSTP下发NP PPI接口未注册 */    
    MSTP_ERR_EVENTNOREGISTER,         /* 21 MSTP事件处理钩子未注册 */
    MSTP_ERR_INSTANCE_OVERFLOW,       /* 22 配置的实例ID超出范围 */
    MSTP_ERR_NOREG_GET_PORT_LINK_STATUS_HOOK,   /* 23 没有注册获取port链路状态的钩子函数 */
    MSTP_ERR_GET_PORT_LINK_STATUS_FAIL,         /* 24 获取port链路状态失败 */
    MSTP_ERR_PORT_PRIORITY_OVERFLOW,            /* 25 用户输入的port优先级过大 */
    MSTP_ERR_BRIDGE_PRIORITY_OVERFLOW,/* 26 指定的桥优先级超出范围 */
    MSTP_ERR_BRIDGE_STP_DISABLE,      /* 27 桥STP未使能 */
    MSTP_ERR_PORT_NOTUSED,            /* 28 端口未使用 */
    MSTP_ERR_PARA_CIST,               /* 29 不能对CIST进行操作 */
    
    MSTP_ERR_MALLOC_FAIL,             /* 30 内存分配失败 */    
    MSTP_ERR_ENQUEUE_FAIL,            /* 31 入队列失败*/
    MSTP_ERR_GET_TRUNK_FAIL,          /* 32 获取成员端口的父接口失败 */
    MSTP_ERR_INVALID_PATHCOSTSTANDARD,/* 33 无效的路径开销计算方式 */
    MSTP_ERR_PRI_OR_SEC_ROOT,         /* 34 不允许对主交换机或备份交换机进行此操作 */
    MSTP_ERR_ROOT_TYPE_WRONG,          /* 35 设置根类型错误 */
    MSTP_ERR_DEBUG_TYPE,              /* 36 MSTP错误的调试类型 */
    MSTP_ERR_EDGEPORT,                /* 37 端口是边缘端口，操作失败 */             
    MSTP_ERR_LOOPGUARD,               /* 38 端口设置了环回保护，操作失败 */
    MSTP_ERR_ROOTGUARD,               /* 39 端口已设置根桥保护，操作失败 */    
    
    MSTP_ERR_WRITE_EVENT_FAILED,      /* 40 写事件失败 */
    MSTP_ERR_STAT_NULL,               /* 41 报文统计指针为空 */
    MSTP_ERR_HISTORY_OVERFLOW,        /* 42 历史日志条数超出限制 */
    MSTP_ERR_HISTORY_ISINIT,          /* 43 历史记录开关已打开 */
    MSTP_ERR_PORT_STP_DISABLE,        /* 44 端口STP未使能 */
    MSTP_ERR_PORT_ISNOTACTIVE,        /* 45 端口在实例上未生效 */
    
    MSTP_ERR_MAXCODE                  /* 最大错误码 */
}MSTP_ERRCODE_E;

#define MSTP_TRUE   1
#define MSTP_FALSE  0

#define MSTP_MAX_INSTANCE     16
#define MSTP_MAX_VLANBITMAP   128
#define MSTP_MAX_PORT_NUM     128
#define MSTP_MIN_VLAN         1
#define MSTP_MAX_VLAN         4096

#define MSTP_MAX_MAXAGE       40      /* 最大MaxAge */
#define MSTP_MIN_MAXAGE       6       /* 最小MaxAge */

#define MSTP_MAX_FWDDELAY     30      /* 最大Forward Delay */
#define MSTP_MIN_FWDDELAY     4       /* 最小Forward Delaye */

#define MSTP_MAX_HELLOTIME    10      /* 最大Hello Time */
#define MSTP_MIN_HELLOTIME    1       /* 最小Hello Time */

#define MSTP_MAX_TIMEFACTOR   10      /* 最大时间因子 */
#define MSTP_MIN_TIMEFACTOR   1       /* 最小时间因子 */

#define MSTP_MAX_DIAMETER     7       /* 最大网络直径 */
#define MSTP_MIN_DIAMETER     2       /* 最小网络直径 */
#define MSTP_DIAMETER_TABLE   (MSTP_MAX_DIAMETER - MSTP_MIN_DIAMETER + 1)   /* 网络直径对应表大小 */

#define MSTP_MAX_MAXHOPS      40      /* 最大域跳数 */
#define MSTP_MIN_MAXHOPS      1       /* 最小域跳数 */



#define MSTP_DEFAULT_BRIDGE_PRIORITY  32768       /* 桥的优先级 */
#define MSTP_DEFAULT_PORT_PRIORITY    128         /* 端口的优先级 */

#define MSTP_DEFAULT_DIAMETER         7           /* 网络直径 */
#define MSTP_DEFAULT_FWDDELAY         15          /* Forward Delay时间间隔 */
#define MSTP_DEFAULT_HELLOTIME        2           /* Hello Time时间间隔 */
#define MSTP_DEFAULT_MAXAGE           20          /* Max Age时间间隔 */
#define MSTP_DEFAULT_MESSAGEAGE       0           /* Message Age时间值 */
#define MSTP_DEFAULT_MAXHOPS          20          /* MAX Hops */
#define MSTP_DEFAULT_TIMEFACTOR       1           /* 默认时间因子 */


#define MSTP_DEFAULT_PORTID           0           /* 端口ID */
#define MSTP_DEFAULT_TRANSMIT_LIMIT   3           /* 发送速率限制值 */
#define MSTP_DEFAULT_ALLTIMER_VALUE   0           /* 所有定时器的初始值*/

#define MSTP_DEFAULT_REVISION_LEVEL   0           /* 修订级别 */

#define MSTP_MAX_BRIDGE_PRIORITY      15          /* 桥的最大优先级 */
#define MSTP_MAX_PORT_PRIORITY        15          /* port最大优先级 */

#define MSTP_POINTTOPOINT      1
#define MSTP_NOPOINTTOPONIT    2
#define MSTP_AUTO              3

/* 缺省路径开销计算标准宏 */
#define MSTP_PATHCOSTSTANDARD_DOT1D     1 /* 802.1D-1998 */
#define MSTP_PATHCOSTSTANDARD_DOT1T     2 /* 802.1t */
#define MSTP_PATHCOSTSTANDARD_LEGACY    3 /* legacy */

/************************ MSTP消息事件宏定义 *******************************/
#define    MSTP_L2IF_EVENT              0x01         /*底层链路状态变化的消息事件*/
#define    MSTP_BPDU_EVENT              0x02         /*BPDU报文接收的消息事件*/
#define    MSTP_TIMER_EVENT             ( 1 << 15 )         /*MSTP状态机定时器消息事件*/

/* 端口角色宏定义 */
#define MSTP_ROLE_DISABLED              0x01    /* 初始值        */
#define MSTP_ROLE_ALTERNATE             0x02    /* Alternate端口 */
#define MSTP_ROLE_BACKUP                0x03    /* Backup端口    */
#define MSTP_ROLE_ROOT                  0x04    /* 根端口        */
#define MSTP_ROLE_DESIGNATED            0x05    /* 指定端口      */
#define MSTP_ROLE_MASTER                0x06    /* master端口    */

/* Force Version模式定义 */
#define MSTP_MODE                3    /* MSTP模式 */
#define RSTP_MODE                2    /* RSTP模式 */
#define STP_COMP_MODE            0    /* STP兼容模式 */
/* 配置域是否激活 */
#define MSTP_REGIONINFO_ACTIVE                  1
#define MSTP_REGIONINFO_INACTIVE                0


/* MSTP Enable Mode */
typedef enum tagMSTP_Enable_Mode_E
{
    MSTP_ENABLE_MODE_BRIDGE = 0,      /* 按全局模式使能/去使能MSTP */
    MSTP_ENABLE_MODE_PORT,            /* 按端口模式使能/去使能MSTP */
}MSTP_ENABLE_MODE_E;


/* MSTP PPI Msg Type */
typedef enum tagMSTP_PPI_MSG_TYPE_E
{
    PPI_SET_MSTP_ENABLE = 1,         /* 对指定接口使能或去使能MSTP */
    PPI_SET_MSTP_VLAN_INSTANCE,      /* 更新VLAN与实例的关系 */
    PPI_SET_MSTP_STATE               /* 设置指定的二层端口在MSTI实例中的状态 */
}MSTP_PPI_MSG_TYPE_E;

/*  描述端口的MSTP转发状态*/
typedef enum enMstpPortStatus
{
    PORT_MSTP_DISCARDING = 0,
    PORT_MSTP_LEARNING,
    PORT_MSTP_FORWARDING,
}MSTP_PORT_STATE_E;
typedef struct tagMSTP_INSTANCE_VLAN_MAPPING
{
    ULONG    ucInstanceID;       
    ULONG    ulVLANIDMap[MSTP_MAX_VLANBITMAP];
}MSTP_INSTANCE_VLAN_MAPPING_S;

/* 根交换机类型 */
typedef enum tagMSTP_ROOT_TYPE
{
    MSTP_NORMAL_ROOT = 0,   /* 普通类型 */ 
    MSTP_PRIMARY_ROOT,      /* 主根交换机 */
    MSTP_SECONDARY_ROOT,    /* 备份根交换机 */
}MSTP_ROOT_TYPE_E;

/* 删除MAC、ARP的消息*/
typedef enum tagMSTP_EVENT_TYPE
{
    MSTP_FDB_DEL_BY_VLANS_AND_ALL_PORT = 0,
    MSTP_ARP_DEL_BY_VLANS_AND_ALL_PORT,
    MSTP_ARP_AGE_BY_VLANS_AND_ALL_PORT,
    MSTP_L2IF_MSG_REFRESH_VLAN,
    MSTP_STP_PORT_STATE_DISCARDING,
    MSTP_STP_PORT_STATE_FORWARDING,
}MSTP_EVENT_TYPE_E;

/*协议类型*/
typedef enum tagMSTP_PROTOCOLTYPE
{
    MSTP_802DOT1S,          /*802.1s标准协议*/
    MSTP_LEGACY,            /*华为私有协议*/
    MSTP_COMPLIANCE_AUTO,   /*报文自适应格式*/
}MSTP_PROTOCOLTYPE_E;

typedef enum enMstpPortGuardType        
{
    MSTP_NOTGUARD,         /* 未启用保护 */
    MSTP_ROOTGUARD,        /* 启动了根保护 */   
    MSTP_LOOPGUARD,        /* 启动了环保护 */
    MSTP_BPDUGUARD,        /* BPDU保护 */
}MSTP_PORTGUARDTYPE_E;


typedef struct tagMSTP_PPI_STATE_MSG
{ 
    /*ULONG ulIfIndex;*/
    ULONG ulInstance;
    ULONG ulState;
}MSTP_PPI_STATE_MSG_S;

typedef struct tagMSTP_PPI_VLANMAP_MSG
{ 
    ULONG ulInstance;
    ULONG ulVLANIDMap[MSTP_MAX_VLANBITMAP];
}MSTP_PPI_VLANMAP_MSG_S;

typedef struct tagMSTP_PPI_ENABLE_MSG
{ 
    ULONG ulIfIndex;
    ULONG ulMSTPEnable;
}MSTP_PPI_ENABLE_MSG_S;


typedef struct tagMSTP_PPI_COUNT
{ 
    ULONG ulMSTPUpdateTotal;  /* MSTP更新通知总次数 */
    ULONG ulMSTPUpdateFailure; /* MSTP更新通知失败次数 */    
}MSTP_PPI_COUNT_S;

typedef struct tagMstpStateChangeInfo
{
    ULONG  ulState;                /*描述是什么状态发生变化*/
    ULONG  ulPortIndex;             /* 端口的逻辑索引值 */
    ULONG  ulCurrentValue;          /* 对应的状态变化的取值 */
}MSTP_STATECHANGEINFO_S;

typedef enum enARP_AGE_TYPE
{
    ARP_AGING_MODE_DEL = 0x01,  /* 采用直接删除的老化方式 */
    ARP_AGING_MODE_AGE,         /* 采用发送报文的老化方式 */
}ARP_AGE_TYPE_E;

typedef struct tagMSTP_GUARD_WARNING
{
    ULONG ulIfIndex;     /* 接口索引*/
    ULONG ulInstanceId;  /* 实例ID */
    ULONG ulWarningType; /* 告警类型*/
}MSTP_GUARD_WARNING_S;

#define MSTP_WARN_BPDUGUARD      1   /* BPDU保护告警类型*/
#define MSTP_WARN_LOOPGUARD      2   /* 环回保护告警类型*/
#define MSTP_WARN_ROOTGUARD      3   /* ROOT保护告警类型*/

/* 端口统计信息 */
typedef struct tagMSTPStatistic
{
    ULONG   ulTxConfigBPDU;     /* 端口发送的Config BPDU的数目 */
    ULONG   ulTxTCNBPDU;        /* 端口发送的TCN BPDU的数目 */
    ULONG   ulTxRSTPBPDU;       /* 端口发送的RSTP BPDU的数目 */ 
    ULONG   ulTxMSTPBPDU;       /* 端口发送的MSTP BPDU的数目 */ 

    ULONG   ulRcvdConfigBPDU;   /* 端口接收到的Config BPDU的数目 */
    ULONG   ulRcvdTCNBPDU;      /* 端口接收到的TCN BPDU的数目 */
    ULONG   ulRcvdRSTPBPDU;     /* 端口接收到的RSTP BPDU的数目 */
    ULONG   ulRcvdMSTPBPDU;     /* 端口接收到的MSTP BPDU的数目 */
    
    ULONG   ulRcvdTCBPDU;       /* 端口记录收到的TC报文拓扑变化的数目 */

    ULONG   ulRecordFlag;       /* 端口收发报文标志，有收发过报文为1，否则为0 */
}MSTP_PORTSTATISTIC_S;

typedef MSTP_PORTSTATISTIC_S MSTP_PORTSTATISTIC_S_ARRAY[MSTP_MAX_PORT_NUM];  

typedef ULONG (*MSTP_GET_LOCALMAC_HOOK_FUNC)(UCHAR szMacAddr[6]);
typedef ULONG (*MSTP_GET_PORTLINKSTATUS_HOOK_FUNC)(ULONG ulPortIndex, ULONG *pulLinkStatus);
typedef ULONG (*MSTP_GET_PORTINDEXBYIFINDEX_HOOK_FUNC)(ULONG ulIfIndex,ULONG *pulPortIndex);
typedef ULONG (*MSTP_GET_IFINDEXBYPORTINDEX_HOOK_FUNC)(ULONG ulPortIndex,ULONG *pulIfIndex);
typedef ULONG (*MSTP_IF_PORTISUSED_HOOK_FUNC)(ULONG ulPortIndex);
typedef ULONG (*MSTP_GET_PORTLISTINVLAN_HOOK_FUNC)(USHORT usVlanId, ULONG *pulPortNum, ULONG ulIfList[MSTP_MAX_PORT_NUM]);
typedef ULONG (*MSTP_SENDPACKET_HOOK_FUNC)(ULONG ulIfIndex, UCHAR *pucBuf, ULONG ulDataLen);
typedef ULONG (*MSTP_PPI_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulCmd, VOID *pData);
typedef ULONG (*MSTP_EVENT_HOOK_FUNC)(ULONG ulIfIndex,ULONG ulCmd, ULONG ulInstanceId);
typedef ULONG (*MSTP_GET_PORT_DUPLEX_STATE_HOOK_FUNC)(ULONG ulIfIndex, ULONG *pulPortDuplexState);
typedef ULONG (*MSTP_GET_IFNAMEBYINDEX_HOOK_FUNC)(ULONG ulIfIndex, UCHAR *pIfName);
typedef ULONG (*MSTP_GET_IFINDEXBYNAME_HOOK_FUNC)(CHAR* szIfName, ULONG *pulIfIndex);
typedef ULONG (*MSTP_IF_ISL2PORT_HOOK_FUNC)(ULONG ulIfIndex);
typedef ULONG (*MSTP_GET_PORTSPEED_HOOK_FUNC)(ULONG ulPortIndex,ULONG *pulPortActualSpeed);
typedef ULONG (*MSTP_ISPORTINVLAN_HOOK_FUNC)(ULONG ulPortIndex,USHORT usVlanId);
typedef ULONG (*MSTP_IF_SHUTDOWN_HOOK_FUNC)(ULONG ulIfIndex);
typedef VOID (*MSTP_BEGIN_PT_HOOK_FUNC)();
typedef VOID (*MSTP_END_PT_HOOK_FUNC)();
typedef VOID (*MSTP_INFOOUTPUT_HOOK_FUNC)(CHAR *pszMsg);
typedef VOID (*MSTP_WARNINGOUTPUT_HOOK_FUNC)(ULONG ulWarningID, VOID* pWarnParam);
typedef VOID (*MSTP_DEBUGOUTPUT_HOOK_FUNC)(CHAR *pBuf);
typedef VOID (*MSTP_HEALTH_BATCHCHECKUP_HOOK_FUNC)();

/* 桥标识号,描述桥的标识号 */
typedef struct tagMSTP_BridgeID
{
    ULONG   ulHigh;         /* 高32位 */
    ULONG   ulLow;          /* 低32位 */
}MSTP_BRIDGEID_S;

/* CIST桥信息 */
typedef struct tagMSTP_CISTBRIDGE_INFO
{
    MSTP_BRIDGEID_S  stLocalBridgeID;  /* 本桥ID */
    MSTP_BRIDGEID_S  stRootBridgeID;   /* 根桥ID */
    MSTP_BRIDGEID_S  stRegRootBridgeID;/* 域根ID */
    ULONG  ulPortIfIndex;              /* 根端口接口索引 */
    ULONG  ulPriority;                 /* 桥在实例中的优先级 */
    ULONG  ulExtRootPathCost;          /* 网桥到CIST根桥的路径开销 */
    ULONG  ulIntRootPathCost;          /* 网桥到域根的路径开销 */
       
    /* 时间向量 */
    UCHAR  ucAdminMaxAge;              /* 配置消息的最大生存期 */
    UCHAR  ucAdminFwdDelay;            /* 端口进入Forwarding状态的延迟时间 */
    UCHAR  ucAdminHelloTime;           /* 定时发送配置BPDUs的最大间隔时间 */
    UCHAR  ucAdminMaxHops;             /* 配置的最大跳数 */

    UCHAR  ucOperMaxAge;               /* 生效的BPDU的最大生存期 */
    UCHAR  ucOperMessageAge;           /* 生效的BPDU的当前生存期 */
    UCHAR  ucOperFwdDelay;             /* 生效的端口进入Forwarding状态的延迟时间 */
    UCHAR  ucOperHelloTime;            /* 生效的定时发送配置BPDUs的最大间隔时间 */
    UCHAR  ucOperMaxHops;              /* 生效的最大跳数 */
    
    UCHAR  ucBridgeStpEnable;          /* True:桥的生产树协议已经开启 False:桥的生产树协议未开启 */ 
    UCHAR  ucTimeFactor;               /* 时间因子 */
    UCHAR  ucArpAgingMode;             /* ARP表项删除时采用的老化方式，初始化为ARP_AGING_MODE_SEND  */
    UCHAR  ucStpDiameter;              /* CIST上的网络直径 */
    UCHAR  ucForceVersion;             /* 0:STP兼容模式; 2:RSTP模式 ;3:MSTP模式 */
    UCHAR  ucBpduGuard;                /* 设置BPDU Guard后，如果portfast端口收到BPDU报文， 则该端口将被shutdown掉 */
    UCHAR  ucDefaultPathCostStandard;  /* 缺省PathCost计算标准1- IEEE 802.1D-1998  2- IEEE 802.1t */
    UCHAR  ucRootType;                 /* 交换机的根类型 0: normal; 1:Secondary Root; 2: Primary Root */
    UCHAR  ucReserve[3];
}MSTP_CISTBRIDGE_INFO_S;

/* MSTI桥信息 */
typedef struct tagMSTP_MSTIBRIDGE_INFO
{
    MSTP_BRIDGEID_S  stLocalBridgeID;     /* 本桥ID */
    MSTP_BRIDGEID_S  stRegRootBridgeID;   /* 域根ID */
    MSTP_BRIDGEID_S  stMasterBridgeID;    /* MASTER桥ID */

    ULONG            ulIntRegRootPathCost;/* 网桥到MSTI域根的路径开销 */
    ULONG            ulIntMasterPathCost; /* 网桥到MASTER桥的路径开销 */
    ULONG            ulPortIfIndex;       /* 根端口接口索引 */
    ULONG            ulPriority;          /* 桥在实例中的优先级 */
    UCHAR            ucAdminMaxHops;      /* 配置的最大跳数 */
    UCHAR            ucOperMaxHops;       /* 生效的最大跳数 */ 
    UCHAR            ucRootType;          /* 交换机的根类型 0: normal; 1:Secondary Root; 2: Primary Root */
    UCHAR            ucReserve;
}MSTP_MSTIBRIDGE_INFO_S;

/* CIST端口信息 */
typedef struct tagMSTP_CISTPORT_INFO
{
    MSTP_BRIDGEID_S stDesignatedBridgeID; /* 指定桥ID */
    UCHAR ucPortStpEnable;                /* 端口协议是否使能 */
    UCHAR ucPortState;                    /* 端口状态 */
    UCHAR ucPortRole;                     /* 端口角色 */
    UCHAR ucPortProtection;               /* 端口保护信息,BPDU保护或边缘端口保护 */
    
    UCHAR ucAdminPointToPointMAC;         /* 该端口是否可连接点对点链路配置信息 */
    UCHAR ucOperPointToPointMAC;          /* 该端口是否可连接点对点链路生效信息 */
    UCHAR ucNoAgreementCheck;             /* 是否配置NoAgreement功能 */ 
    UCHAR ucConfigDigestSnoop;            /* 是否配置摘要探测功能 */ 
    
    ULONG ulAdminPortPathCost;            /* 系统设置的端口路径值 */ 
    ULONG ulOperPortPathCost;             /* 端口实际对应的路径开销 */  
    ULONG ulPortPriority;                 /* 端口优先级值 */
    ULONG ulTransitLimit;                 /* hello time时间内允许发送的报文个数 */
    
    USHORT usDesignatedPortID;            /* 指定端口ID*/
    UCHAR ucIsAdminEdged;                 /* 是否配置为边缘端口 */
    UCHAR ucIsOperEdged;                  /* 是否生效的边缘端口 */

    UCHAR ucAdminProtocolType;            /* 配置的端口收发BPDU报文格式 */  
    UCHAR ucOperProtocolType;             /* 生效的端口收发BPDU报文格式 */  
    UCHAR ucSendVersion;                  /* 发送BPDU报文版本 */
    UCHAR ucPortActive;                   /* 端口是否使能MSTP并端口UP */
}MSTP_CISTPORT_INFO_S;

/* MSTI端口信息 */
typedef struct tagMSTP_MSTIPORT_INFO
{
    MSTP_BRIDGEID_S stDesignatedBridgeID; /* 指定桥ID */
    ULONG ulPortPriority;                 /* 端口优先级值 */
    ULONG ulAdminPortPathCost;            /* 系统设置的端口路径值 */ 
    ULONG ulOperPortPathCost;             /* 端口实际对应的路径开销 */  

    USHORT usDesignatedPortID;            /* 指定端口ID*/
    UCHAR ucPortStpEnable;                /* 端口协议是否使能 */
    UCHAR ucPortState;                    /* 端口状态 */

    UCHAR ucPortRole;                     /* 端口角色 */
    UCHAR ucPortActive;                   /* 端口是否使能MSTP并端口UP */
    UCHAR ucReserve[2];
}MSTP_MSTIPORT_INFO_S;

/* 端口简要信息 */
typedef struct tagMSTP_BRIEF_INFO
{
    UCHAR ucPortRole;         /* 端口角色 */
    UCHAR ucPortState;        /* 端口状态 */
    UCHAR ucReserve[2];
}MSTP_BRIEF_INFO_S;

/*******************************************************************************
*    Func Name: MSTP_SetRegionName
* Date Created: 2008-12-05
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 设置MSTP域名
*        Input: UCHAR *pcRegionName:MSTP域名
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码。
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-05   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern ULONG MSTP_SetRegionName(UCHAR *pcRegionName);

/*******************************************************************************
*    Func Name: MSTP_SetRegionRevisionLevel
* Date Created: 2008-12-05
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 设置MSTP修订级别
*        Input: USHORT usRevisinLevel:MSTP域修订级别(取值0~65535)
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码。
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-05   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern ULONG MSTP_SetRegionRevisionLevel(USHORT usRevisinLevel);


/*******************************************************************************
*    Func Name: MSTP_SetRegionInstanceVlanMap
* Date Created: 2008-12-05
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 配置域的实例与VLAN的映射关系
*        Input: MSTP_INSTANCE_VLAN_MAPPING_S *pstInstanceVlanMap:实例对应的VLAN映射关系
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码。
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-05   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern ULONG MSTP_SetRegionInstanceVlanMap(MSTP_INSTANCE_VLAN_MAPPING_S *pstInstanceVlanMap);

/*******************************************************************************
*    Func Name: MSTP_GetRegionInfo
* Date Created: 2008-12-08
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 获取域配置信息
*        Input: ULONG ulType:域是否激活.0：未激活；1：激活
*       Output: UCHAR *pcRegionName:    已配置的域名
*               ULONG *plRevisionLevel: 已配置的域修订级别
*               MSTP_INSTANCE_VLAN_MAPPING_S  stVlanMap[MSTP_MAX_INSTANCE + 1]:域中实例与VLAN的映射关系
*       Return: 成功返回MSTP_OK，失败返回错误码
*      Caution: 传入的stVlanMap数组空间和清零由用户保证
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-08   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern ULONG MSTP_GetRegionInfo(ULONG ulType, UCHAR *pcRegionName, ULONG *plRevisionLevel, 
                                MSTP_INSTANCE_VLAN_MAPPING_S  stVlanMap[MSTP_MAX_INSTANCE + 1]);

/*******************************************************************************
*    Func Name: MSTP_ActiveRegionInfo
* Date Created: 2008-12-05
*       Author: zhangchi(00142640)
*  Description: 激活域信息
*        Input: VOID
*       Output: 
*       Return: 成功MSTP_OK,其他返回错误码 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-05   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_ActiveRegionInfo(VOID);


/*******************************************************************************
*    Func Name: MSTP_ShowRegionInfo
* Date Created: 2008-12-08
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 显示域配置信息
*        Input: ULONG ulType: 域配置是否激活(0:未激活;1:激活)
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-08   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern VOID MSTP_ShowRegionInfo(ULONG ulType);


/*******************************************************************************
*    Func Name: MSTP_GetPortStateInInstance
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: 获取端口在实例中的转发状态
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulInstanceID:实例ID
*       Output: ULONG *pulProtState: 端口的转发状态，共有PORT_MSTP_FORWARDING,
*               PORT_MSTP_LEARNING和PORT_MSTP_DISCARDING三种
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetPortStateInInstance(ULONG ulIfIndex, ULONG ulInstanceID, ULONG *pulProtState);

/*******************************************************************************
*    Func Name: MSTP_GetInstanceIDByVlanId
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: 
*        Input: ULONG ulVlanID: VLAN ID
*       Output: ULONG *pulInstanceID: 实例ID
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetInstanceIDByVlanId(ULONG ulVlanID, ULONG *pulInstanceID);

/*******************************************************************************
*    Func Name: MSTP_SetEnable
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: 按全局模式或按接口模式使能/去使能MSTP
*        Input: ULONG ulType: 按全局模式或按接口使能/去使能MSTP，取值有
*               MSTP_ENABLE_MODE_BRIDGE和MSTP_ENABLE_MODE_PORT
*               ULONG ulIfIndex: 二层端口的接口索引。按接口使能MSTP时，需传入；而
*               按全局模式使能时，无需传入，程序不对该值处理。
*               ULONG ulSetYes: 使能/去使能MSTP，取值有MSTP_TRUE和MSTP_FALSE
*       Output: 
*       Return: 成功则返回MSTP_OK，失败则返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_SetEnable(ULONG ulType, ULONG ulIfIndex, ULONG ulSetYes);


/*******************************************************************************
*    Func Name: MSTP_SetBridgeDiameter
* Date Created: 2008-12-08
*       Author: zhangchi(00142640)
*  Description: 设置网络直径
*        Input: ULONG ulDiameter:网络直径(2~7,默认7)
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-08   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_SetBridgeDiameter(ULONG ulDiameter);

/*******************************************************************************
*    Func Name: MSTP_SetConverge
* Date Created: 2008-12-09
*       Author: zhangchi(00142640)
*  Description: 设置MSTP收敛方式
*        Input: ULONG ulType:收敛方式(ARP_AGING_MODE_DEL:直接删除
*                                     ARP_AGING_MODE_AGE:老化删除
*                                     默认直接删除)
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_SetConverge(ULONG ulType);

/*******************************************************************************
*    Func Name: MSTP_SetBpduProtection
* Date Created: 2008-12-13
*       Author:  ZhengSenHuo/GeXianJun(104483/121208) 
*  Description: 设置BPDU保护
*        Input: ULONG ulSetYes: 使能: 1；去使能: 0
*       Output: 
*       Return: 成功: MSTP_OK；失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    ZhengSenHuo/GeXianJun(104483/121208)   Create
*
*******************************************************************************/
extern ULONG MSTP_SetBpduProtection(ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_SetRootProtection
* Date Created: 2008-12-13
*       Author:  ZhengSenHuo/GeXianJun(104483/121208) 
*  Description: 设置根保护
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSetYes: 使能: 1；去使能: 0
*       Output: 
*       Return: 成功: MSTP_OK；失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    ZhengSenHuo/GeXianJun(104483/121208)   Create
*
*******************************************************************************/
extern ULONG MSTP_SetRootProtection(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_SetPortLoopProtection
* Date Created: 2008-12-13
*       Author:  ZhengSenHuo/GeXianJun(104483/121208) 
*  Description: 设置环回保护
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSetYes: 使能: 1；去使能: 0
*       Output: 
*       Return: 成功: MSTP_OK；失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    ZhengSenHuo/GeXianJun(104483/121208)   Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortLoopProtection(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_SetPortMcheck
* Date Created: 2008-12-13
*       Author:  ZhengSenHuo/GeXianJun(104483/121208) 
*  Description: 设置基于端口的Mcheck功能
*        Input: ULONG ulIfIndex: 接口索引
*       Output: 
*       Return: 成功: MSTP_OK；失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    ZhengSenHuo/GeXianJun(104483/121208)   Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortMcheck(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: MSTP_SetPortPathCostInInstance
* Date Created: 2008-12-04
*       Author: zengshaoyang62531
*  Description: 在实例中设置Port的路径开销
*        Input: ULONG ulIfIndex:Port索引
*               ULONG ulInstance:实例ID
*               ULONG ulCost:路径开销
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortPathCostInInstance(ULONG ulIfIndex, ULONG ulInstance, ULONG ulCost);

/*******************************************************************************
*    Func Name: MSTP_SetDefaultPortPathCostInInstance
* Date Created: 2009-01-13
*       Author: zengshaoyang62531
*  Description: 恢复实例中接口的缺省路径开销
*        Input: ULONG ulIfIndex:Port ifnet索引
*               ULONG ulInstance:实例ID
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-13   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG MSTP_SetDefaultPortPathCostInInstance(ULONG ulIfIndex, ULONG ulInstance);

/*******************************************************************************
*    Func Name: MSTP_SetEdgedPort
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: 设置port为边缘端口
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:1,设置为边缘端口，0表示取消
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                       DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531,luowentong00105073       Create
*
*******************************************************************************/
extern ULONG MSTP_SetEdgedPort(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_SetPriorityInInstance
* Date Created: 2008-12-12
*       Author: lianglong111779
*  Description: 设置交换机在指定实例中的优先级
*        Input: ULONG ulInstanceID: 实例ID
*               ULONG ulPriority: 优先级值，取值范围0~15
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_SetPriorityInInstance(ULONG ulInstanceID, ULONG ulPriority);

/*******************************************************************************
*    Func Name: MSTP_SetPortPriorityInInstance
* Date Created: 2008-12-04
*       Author: zengshaoyang62531/luowentong
*  Description: 在实例中设置Port的优先级
*        Input: ULONG ulIfIndex:Port的优先级
*               ULONG ulInstance:实例ID
*               ULONG ulPriority:优先级
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortPriorityInInstance(ULONG ulIfIndex,ULONG ulInstance, ULONG ulPriority);

/*******************************************************************************
*    Func Name: MSTP_SetRootType
* Date Created: 2008-12-18
*       Author: lianglong111779
*  Description: 设置交换机的根类型
*        Input: ULONG ulInstanceId: 实例ID
*               ULONG ulRootType:   类型
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-18   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_SetRootType(ULONG ulInstanceId, ULONG ulRootType);

/*******************************************************************************
*    Func Name: MSTP_SetForwardDelay
* Date Created: 2008-12-08
*       Author: zhangchi(00142640)
*  Description: 设置Forward Delay时间,取值范围4~30，默认15
*        Input: ULONG ulTimer:Forward Delay时间
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-08   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_SetForwardDelay(ULONG ulTimer);

/*******************************************************************************
*    Func Name: MSTP_SetHelloTimer
* Date Created: 2008-10-22
*       Author: zhangchi(00142640)
*  Description: 设置Hello Time,取值范围1~10，默认2
*        Input: ULONG ulTimer:Hello Time时间
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_SetHelloTimer(ULONG ulTimer);

/*******************************************************************************
*    Func Name: MSTP_SetMaxAge
* Date Created: 2008-10-22
*       Author: zhangchi
*  Description: 设置MaxAge
*        Input: ULONG ulTimer:MaxAge Time(6~40S,默认20S)
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   zhangchi                 Create
*
*******************************************************************************/
extern ULONG MSTP_SetMaxAge(ULONG ulTimer);

/*******************************************************************************
*    Func Name: MSTP_SetTimerFactor
* Date Created: 2008-12-08
*       Author: zhangchi(00142640)
*  Description: 设置时间因子
*        Input: ULONG ulFactor:时间因子(1~10,默认1)
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-08   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_SetTimerFactor(ULONG ulFactor);

/*******************************************************************************
*    Func Name: MSTP_SetMaxhop
* Date Created: 2008-12-09
*       Author: zhangchi(00142640)
*  Description: 设置域的最大跳数
*        Input: ULONG ulhop:最大跳数(1~40,默认20)
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_SetMaxhop(ULONG ulhop);

/*******************************************************************************
*    Func Name: MSTP_SetPathCostStandard
* Date Created: 2008-10-23
*       Author: lianglong111779
*  Description: 设置路径开销的计算方式
*        Input: ulong ulStandard: 路径开销的计算方式，取值有MSTP_PATHCOSTSTANDARD_DOT1D,
*               MSTP_PATHCOSTSTANDARD_DOT1T和MSTP_PATHCOSTSTANDARD_LEGACY
*       Output: 
*       Return: 成功MSTP_OK，失败其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_SetPathCostStandard(ULONG ulStandard);

/*******************************************************************************
*    Func Name: MSTP_SetNoAgreementCheck
* Date Created: 2008-12-13
*       Author:  ZhengSenHuo/GeXianJun(104483/121208) 
*  Description: 设置端口的NoAgreement check功能
*               VISP默认不等待上游端口的A报文
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSetYes:  使能:1；去使能: 0
*       Output: 
*       Return: 成功:返回MSTP_OK；失败: 返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    ZhengSenHuo/GeXianJun(104483/121208)   Create
*
*******************************************************************************/
extern ULONG MSTP_SetNoAgreementCheck(ULONG ulIfIndex, ULONG ulSetYes);


/*******************************************************************************
*    Func Name: MSTP_SetPortConfigDigestSnoop
* Date Created: 2008-12-13
*       Author:  ZhengSenHuo/GeXianJun(104483/121208) 
*  Description: 设置MSTP的摘要侦听功能
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSetYes:  使能: 1；去使能: 0
*       Output: 
*       Return: 成功: MSTP_OK；失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    ZhengSenHuo/GeXianJun(104483/121208)   Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortConfigDigestSnoop(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_SetPortBPDUType
* Date Created: 2008-12-16
*       Author: wuhailan
*  Description: 设置指定端口的BPDU报文收发格式 
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulType:报文类型
*                            MSTP_802DOT1S:802.1s标准协议
*                            MSTP_LEGACY:华为私有协议
*                            MSTP_COMPLIANCE_AUTO:报文自适应格式
*                            默认配置为自适应格式
*       Output: 
*       Return: 成功: MSTP_OK；失败: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-16   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortBPDUType(ULONG ulIfIndex, ULONG ulType);

/*******************************************************************************
*    Func Name: MSTP_SetPortPointToPoint
* Date Created: 2008-12-04
*       Author: zengshaoyang62531,luowentong
*  Description: 设置端口的链路类型
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulType:链路类型
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531,luowentong       Create
*
*******************************************************************************/
ULONG MSTP_SetPortPointToPoint(ULONG ulIfIndex, ULONG ulType);

/*******************************************************************************
*    Func Name: MSTP_SetPortTransmitLimit
* Date Created: 2008-12-04
*       Author: zengshaoyang62531,luowentong
*  Description: 设置hello time时间内发送的BPDU报文数目
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulLimit:hello time时间内发送的BPDU报文数目
*       Output: 
*       Return: 成功返回MSTP_OK,失败返回错误码。
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531,luowentong       Create
*
*******************************************************************************/
ULONG MSTP_SetPortTransmitLimit(ULONG ulIfIndex, ULONG ulLimit);

/*******************************************************************************
*    Func Name: MSTP_GetVersion
* Date Created: 2008-10-22
*       Author: wuhailan
*  Description: 获取MSTP CBB的版本号和编译时间
*        Input: CHAR *szVerInfo: MSTP CBB的版本信息和编译时间字符串
*                                由用户分配256字节空间。
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_GetVersion(CHAR *szVerInfo);

/*******************************************************************************
*    Func Name: MSTP_ShowVersion
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: 显示MSTP版本号
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
extern VOID MSTP_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: MSTP_Init
* Date Created: 2008-11-29
*       Author: wuhailan 
*  Description: MSTP CBB初始化入口函数
*        Input: ULONG ulTaskPri:任务优先级
*               ULONG ulTaskStackSize:栈大小
*       Output: 
*       Return: 成功MSTP_OK,其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-29   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_Init(ULONG ulTaskPri, ULONG ulTaskStackSize);

/*******************************************************************************
*    Func Name: MSTP_ShowBrief
* Date Created: 2008-12-03
*       Author: zengshaoyang62531
*  Description: 显示MSTP简要信息
*        Input: VOID
*       Output: VOID
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-03   zengshaoyang62531       Create
*
*******************************************************************************/
extern VOID MSTP_ShowBrief(VOID);

/*******************************************************************************
*    Func Name: MSTP_GetCISTBridgeInfo
* Date Created: 2008-12-10
*       Author: lianglong111779
*  Description: 获取CIST桥信息
*        Input: 
*       Output: MSTP_CISTBRIDGE_INFO_S *pstCistBridgeInfo: CIST桥信息输出缓冲区
*       Return: 成功MSTP_OK，失败其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetCISTBridgeInfo(MSTP_CISTBRIDGE_INFO_S *pstCistBridgeInfo);

/*******************************************************************************
*    Func Name: MSTP_GetMSTIBridgeInfo
* Date Created: 2008-12-10
*       Author: lianglong111779
*  Description: 获取指定实例中的MSTI桥信息
*        Input: ULONG ulInstanceID: 实例ID
*       Output: MSTP_MSTIBRIDGE_INFO_S *pstMstiBridgeInfo: MSTI桥信息输出缓冲区
*       Return: 成功MSTP_OK，失败其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetMSTIBridgeInfo(ULONG ulInstanceID, MSTP_MSTIBRIDGE_INFO_S *pstMstiBridgeInfo);

/*******************************************************************************
*    Func Name: MSTP_GetCISTPortInfo
* Date Created: 2008-12-10
*       Author: lianglong111779
*  Description: 获取CIST中指定端口的信息
*        Input: ULONG ulIfIndex: 二层端口对应的接口索引
*       Output: MSTP_CISTPORT_INFO_S *pstCistPortInfo: 端口信息输出缓冲区
*       Return: 成功MSTP_OK，失败其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetCISTPortInfo(ULONG ulIfIndex, MSTP_CISTPORT_INFO_S *pstCistPortInfo);

/*******************************************************************************
*    Func Name: MSTP_GetMSTIPortInfo
* Date Created: 2008-12-10
*       Author: lianglong111779
*  Description: 获取指定的MSTI端口信息
*        Input: ULONG ulIfIndex: 二层端口对应的接口索引
*               ULONG ulInstanceID: 实例ID
*       Output: MSTP_MSTIPORT_INFO_S *pstMstiPortInfo: 端口信息输出缓冲区
*       Return: 成功MSTP_OK，失败其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetMSTIPortInfo(ULONG ulIfIndex, ULONG ulInstanceID, MSTP_MSTIPORT_INFO_S *pstMstiPortInfo);

/*******************************************************************************
*    Func Name: MSTP_GetBriefInfo
* Date Created: 2008-12-23
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 根据接口索引和实例ID获取端口简要信息
*        Input: ULONG ulIfIndex:    接口索引
*               ULONG ulInstanceId: 实例ID
*       Output: MSTP_BRIEF_INFO_S *pstMstpBriefInfo:端口角色和端口状态的简要信息
*       Return: 成功返回MSTP_OK; 失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-23   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG MSTP_GetBriefInfo(ULONG ulIfIndex, ULONG ulInstanceId, MSTP_BRIEF_INFO_S *pstMstpBriefInfo);


/*******************************************************************************
*    Func Name: MSTP_SetDebug
* Date Created: 2008-12-12
*       Author: wuhailan
*  Description: MSTP调试开关设置接口
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulType:设置的调试类型
*                            MSTP_DEBUG_PACKET,报文类调试开关
*                            MSTP_DEBUG_ERROR,报文错误类调试开关
*                            MSTP_DEBUG_STATE,状态机类调试开关
*                            MSTP_DEBUG_EVENT,错误事件类调试开关
*                            MSTP_DEBUG_ALL,打开全部类型调试开关
*               ULONG ulSetYes:调试开关
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_SetDebug(ULONG ulPortIndex, ULONG ulType, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_ShowInfoAll
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: 显示所有生成树实例及端口详细信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowInfoAll(VOID);

/*******************************************************************************
*    Func Name: MSTP_ShowStpTimer
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: 在指定port和指定实例的情况下显示各定时器的值
*        Input: CHAR* szIfName:接口名称
*               ULONG ulInstance:实例id
*       Output: 
*       Return: VOID
*      Caution: 该显示接口显示MSTP内部定时器计数值,只作为VISP内部开发人员定位问题参考
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                              DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowStpTimer(CHAR* szIfName, ULONG ulInstance);

/*******************************************************************************
*    Func Name: MSTP_ShowCistBridge
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: 显示CIST信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                            DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong        Create
*
*******************************************************************************/
extern VOID MSTP_ShowCistBridge(VOID);

/*******************************************************************************
*    Func Name: MSTP_ShowCISTPortInfo
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: 显示CISP端口信息
*        Input: CHAR* szIfName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowCISTPortInfo(CHAR* szIfName);

/*******************************************************************************
*    Func Name: MSTP_ShowMSTIBridgeInfo
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: 显示msti桥信息
*        Input: ULONG ulInstance:实例ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                        DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowMSTIBridgeInfo(ULONG ulInstance);

/*******************************************************************************
*    Func Name: MSTP_ShowMSTIPortInfo
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: 显示MSTI端口信息
*        Input: CHAR* szIfName:接口名
*               ULONG ulInstance:实例ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowMSTIPortInfo(CHAR* szIfName, ULONG ulInstance);

/*******************************************************************************
*    Func Name: MSTP_PacketEnQueue
* Date Created: 2008-12-01
*       Author: lianglong111779
*  Description: 当接收到MSTP报文时将报文入MSTP的报文队列
*        Input: UCHAR *pucBuf:MSTP报文指针
*               ULONG ulIfIndex:接口索引
*               ULONG ulBpduLen:报文长度
*       Output: 
*       Return: 成功MSTP_OK,其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-01   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_PacketEnQueue(UCHAR *pucBuf, ULONG ulIfIndex, ULONG ulBpduLen);

/*******************************************************************************
*    Func Name: MSTP_LinkChgEnQuenue
* Date Created: 2008-12-09
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 端口状态变化消息入队列函数。
*               包括端口加入/离开VLAN，端口UP/DOWN、端口速率变化、端口双工模式变化
*        Input: MSTP_STATECHANGEINFO_S *pstInfo: 消息内存指针
*       Output: 
*       Return: 成功返回MSTP_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern ULONG MSTP_LinkChgEnQuenue(MSTP_STATECHANGEINFO_S *pstInfo);

/*******************************************************************************
*    Func Name: MSTP_SetForceVersion
* Date Created: 2008-12-16
*       Author: wuhailan
*  Description: 设置版本报文处理版本信息
*        Input: ULONG ulForceVersion:版本信息,默认MSTP_MODE.可取值MSTP_MODE/RSTP_MODE/STP_COMP_MODE
*       Output: 
*       Return: 成功MSTP_OK，其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-16   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_SetForceVersion(ULONG ulForceVersion);

/*******************************************************************************
*    Func Name: MSTP_GetVlanMapByInstance
* Date Created: 2008-12-19
*       Author:  ZhengSenHuo/GeXianJun(104483/121208) 
*  Description: 根据实例和激活类型获取VLAN与实例的映射关系
*        Input: ULONG ulType:     激活类型
*               ULONG ulInstance: 实例ID
*               ULONG ulVLANIDMap[MSTP_MAX_VLANBITMAP]: VLAN与实例的映射数组
*       Output: 
*       Return: 成功返回MSTP_OK; 失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-19    ZhengSenHuo/GeXianJun(104483/121208)   Create
*
*******************************************************************************/
extern ULONG MSTP_GetVlanMapByInstance(ULONG ulType,ULONG ulInstance,
                                                        ULONG ulVLANIDMap[MSTP_MAX_VLANBITMAP]);

/*******************************************************************************
*    Func Name: MSTP_SetRecoredHistory
* Date Created: 2008-12-19
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: MSTP设置历史信息统计开关函数
*        Input: ULONG ulSetYes:    统计开关
*               ULONG ulHistoryLen:信息条数
*       Output: 
*       Return: 成功MSTP_OK,其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-19   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG MSTP_SetRecoredHistory(ULONG ulSetYes, ULONG ulHistoryLen);

/*******************************************************************************
*    Func Name: MSTP_ShowHistory
* Date Created: 2008-12-19
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 显示端口状态变化历史信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-19   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern VOID MSTP_ShowHistory(VOID);

/*******************************************************************************
*    Func Name: MSTP_ResetBpduStatistic
* Date Created: 2008-12-19
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 清空Bpdu报文统计信息
*        Input: 
*       Output: 
*       Return: 成功MSTP_OK,其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-19   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG MSTP_ResetBpduStatistic(VOID);

/*******************************************************************************
*    Func Name: MSTP_GetBpduStatistic
* Date Created: 2008-12-19
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 获取Bpdu报文统计信息
*        Input: ULONG ulIfIndex:    接口索引
*               ULONG ulInstanceID: 实例ID
*       Output: MSTP_PORTSTATISTIC_S *pstPortStatistic:统计信息
*       Return: 成功MSTP_OK,其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-19   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern ULONG MSTP_GetBpduStatistic(ULONG ulIfIndex, ULONG ulInstanceID, MSTP_PORTSTATISTIC_S *pstPortStatistic);

/*******************************************************************************
*    Func Name: MSTP_ShowBpduStatistic
* Date Created: 2008-12-19
*       Author: wuhailan/zhangchi(00103194/00142640)
*  Description: 显示Bpdu报文统计
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-19   wuhailan/zhangchi(00103194/00142640)  Create
*
*******************************************************************************/
extern VOID MSTP_ShowBpduStatistic(VOID);


#ifdef  __cplusplus
}
#endif

#endif




