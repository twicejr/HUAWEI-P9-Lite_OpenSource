/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_typ.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk  
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunk模块的数据结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_TYP_H_
#define _TRUNK_TYP_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Trunk信息表 */
typedef struct tagTrunkInfoTbl
{
    ULONG ulIfIndex;                                 /* Trunk接口索引 */
    ULONG ulIsUsed;                                  /* 该表项是否已使用，1－使用，0－未使用 */
    ULONG ulPortNum;                                 /* 成员端口总数 */
    ULONG ulTrunkPortIfIndex[TRUNK_PORT_MAX_NUM];    /* 成员端口信息表 */
    ULONG ulUpPortNum;                               /* 处于链路UP的成员端口总数 */
    ULONG ulTrunkUpPortIfIndex[TRUNK_PORT_MAX_NUM];  /* UP的成员端口信息表 */
    ULONG ulEnableLacp;                              /* 是否使能LACP，默认为使能 */
    ULONG ulRefIfIndex;                              /* 参考端口的接口索引 */
    UCHAR ucMacAddress[TRUNK_MACADDR_LEN];           /* Trunk接口physical地址 */
    UCHAR ucBfdTrunkMode;                            /* trunk或成员端口上建立单跳bfd的生效模式,默认trunk优先 */   
    UCHAR ucMacDynamic;                              /* Trunk physical地址获取模式是否为动态获取模式     */
    ULONG ulMacPortIndex;                            /* 动态获取Trunk mac时所使用mac的成员端口索引  */
    ULONG ulGateValue;                               /* Trunk门值 */
    ULONG ulPassive;                                 /* 是主动端还是被动端 */
    UCHAR ucBackupMode;                              /* 端口备份模式,0,普通模式;1,1:1备份模式，2,M:N备份模式 */ 
    UCHAR ucRecoverMode;                             /* 端口备份的恢复模式,0,恢复模式;1,非恢复模式 */
    USHORT usSysPri;                                 /* Trunk系统优先级 */
    ULONG ulMasterIfIndex;                           /* 端口1:1模式下配置的主端口索引 */
    ULONG ulActiveNum;                               /* 端口M:N模式下配置的激活端口数 */
    ULONG ulProductPolicy;                           /* 产品定制的TRUNK策略 */
    UCHAR ucIsTrunkNeedKeepUp;                       /* Trunk在UP成员端口均DOWN掉时是否需要DOWN, 1-不报DOWN，0-报DOWN(默认) */
    UCHAR ucPadding[3];                              /* 保留字段 */
    ULONG ulLbCheckTimerId;                          /* 环回检测定时器 */ 
    /*Added by z00208058, for USN产品需求，支持基于Trunk组配置系统MAC, 2014/10/15 */
    UCHAR ucTrunkIdSysMac[TRUNK_MACADDR_LEN];        /* 基于TRUNK组配置系统MAC*/
    UCHAR ucReserve[2];                              /* 保留字段*/
}TRUNK_INFO_TBL_S;

/* 报文统计信息表 */
typedef struct tagTrunkPortPktStat
{
    ULONG ulOutSum;       /* 发送的报文总数 */
    ULONG ulOutLacp;      /* 发送的LACP报文数 */
    ULONG ulOutDrop;      /* 发送时丢弃的报文数 */
    ULONG ulInSum;        /* 接收的报文总数 */
    ULONG ulInLacp;       /* 接收的LACP报文数 */
    ULONG ulInDrop;       /* 接收时丢弃的报文数 */
    /* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
    ULONG ulLacpExpired;  /* NP上报超时统计 */
    ULONG ulLacpPPIPKT;   /* LACP下发NP后，透传报文统计 */
}TRUNK_PORT_PKT_STAT_S;


/* LACP协商信息表 */
typedef struct tagLacpNego
{
    /* 本端信息 */
    ULONG ulDefaulted;             /* 端口是否为defaulted端口 */
    UCHAR ucActorAdminState;       /* 本端端口管理状态值 */
    UCHAR ucActorOperState;        /* 本端端口运作状态值 */
    USHORT usActorAdminKey;        /* 本端端口管理Key */
    USHORT usActorOperKey;         /* 本端端口运作Key */
    USHORT usActorPortPri;         /* 本端端口优先级 */
    USHORT usActorPortIndex;       /* 本端端口号 */

    /* 对端信息 */
    UCHAR ucPartnerAdminState;     /* 对端端口管理状态值 */
    UCHAR ucPartnerOperState;      /* 对端端口运作状态值 */
    USHORT usPartnerAdminKey;      /* 对端端口管理KEY */
    USHORT usPartnerOperKey;       /* 对端端口运作Key */
    USHORT usPartnerAdminPortPri;  /* 对端端口管理优先级 */
    USHORT usPartnerOperPortPri;   /* 对端端口运作优先级 */
    USHORT usPartnerAdminPortIndex; /* 对端端口管理端口号 */
    USHORT usPartnerOperPortIndex;  /* 对端端口运作端口号 */
    USHORT usPartnerAdminSysPri;   /* 对端系统管理优先级 */
    USHORT usPartnerOperSysPri;    /* 对端系统运作优先级 */
    UCHAR ucPartnerAdminSysMac[6]; /* 对端系统管理physical地址 */
    UCHAR ucPartnerOperSysMac[6];  /* 对端系统运作physical地址 */
    ULONG ulRemoteDefaulted;        /* 对端是否进入default状态 */
}LACP_NEGO_S;

/* 状态机状态 */
typedef struct tagLacpFsm
{
    BOOL_T bEnter;       /* 是否能够进入状态机 FALSE表示退出状态机 */
    UCHAR  ucState;      /* 状态机当前的状态 */
    UCHAR ucPadding;     /* 保留字段 */
}LACP_FSM_S;

/* 逻辑定时器信息 */
typedef struct tagLacpTimers
{
    BOOL_T bActive;                 /*定时器是否开启*/
    USHORT usValue;                 /* 定时器的值,即定时器超时次数,DTS2013060100805 m59090 */
}LACP_TIMERS_S;

/* LACP协商状态机信息表 */
typedef struct tagLacpPortFsm
{
    BOOL_T bRXBEGIN;                /* RX状态机初始化标志 */
    BOOL_T bPTXBEGIN;               /* PTX状态机初始化标志 */
    BOOL_T bMUXBEGIN;               /* MUX状态机初始化标志 */

    BOOL_T bNTT;                    /* NTT标志 */
    BOOL_T bPortEnable;             /* 端口Enable/Disable事件激励 */    
    BOOL_T bLacpOperEnabled;        /* TURE：端口全双工 */
    BOOL_T bReady;                  /* 端口Ready_N置位表示该端口可以Attach了 */
    BOOL_T bPortMoved;              /* DOWN端口所保存的信息被其它端口收到则置位 */
    USHORT usSelected;              /* 端口Selected状态标志 */
    USHORT usTxSendCount;           /* Tx状态机在1s内发送报文的次数 */

    /*以下为LACP各定时器的当前状态*/
    LACP_TIMERS_S stPeriodicTimer;  /* short_periodic_timer定时器 */
    LACP_TIMERS_S stCurWhileTimer;  /* CurrentWhileTimer定时器 */

    /* 以下为LACP各状态机的当前状态 */
    LACP_FSM_S stRx;                /* 接收状态机 */
    LACP_FSM_S stPtx;               /* 周期性发送状态机 */
    LACP_FSM_S stMux;               /* MUX状态机 */
}LACP_PORT_FSM_S;


#define WARN_PORT_DUPLEX  0x1
#define WARN_PORT_SPEED   0x2

/* 位设置/清除/是否设置判断宏 */
#define BITS_FLAG_SET(t,f)    ((t) |= (f))
#define BITS_FLAG_CLR(t,f)    ((t) &= ~(f))
#define BITS_FLAG_ISSET(t,f)  (((t) & (f)) ? 1 : 0)

/*Added by z00208058/w00207740, TRUNK LACP下移需求开发, 2012/5/2 */
#define LACP_UNDOWNLOAD 0
#define LACP_DOWNLOAD   1

/* 成员端口控制块 */
typedef struct tagTrunkPortInfo
{
    ULONG  ulIfIndex;                          /* 端口的接口索引 */
    ULONG  ulLacpStatus;                       /* 端口LACP协议状态：0－DOWN，1－UP */
    LACP_NEGO_S* pstLacpNego;                  /* LACP协商信息表指针 */
    LACP_PORT_FSM_S* pstLacpPortFsm;           /* LACP状态机信息表指针 */
    TRUNK_PORT_PKT_STAT_S stPortPktStat;       /* 成员端口报文统计信息 */
    UCHAR  ucOldMacAddress[6];                 /* 成员端口加入Trunk前的physical地址 */
    UCHAR  ucBakMacAddress[6];              /* 保存主板成员端口的physical地址，用于主备一致 */
    UCHAR  ucVirtualAdd;                       /* 真实端口还是映射端口 */
    UCHAR  ucNoWarningFlag;                    /* 当设置为1时,将成员端口从Trunk中移除时不进行告警 */
    USHORT usNoLacpPortKey;                    /* 手工绑定方式下记录端口的性能，以支持速率/双工模式等变化 */
    ULONG  ulNegTimeCnt;                       /* 首次协商未通过计时 */ 
    ULONG  ulPortWarnFlag;                     /* 对外告警状态记录: WARN_PORT_DUPLEX(0x1) 已通告双工模式不正确告警, 
                                                                    WARN_PORT_SPEED (0x2) 已通告速率不一致告警 */
    USHORT usPortPri;                          /* 记录端口优先级 */
    USHORT usPortIndex;                        /* 记录端口号 */

    ULONG  ulNeedResendArpFlag;                /* DTS2011022802677 重传distribute，collect置位前发送的ARP请求报文*/
    ULONG  ulDownReason;                       /* LACP协议down 原因ID */
    /* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
    ULONG  ulLacpLinkMode;                      /*Lacp收发模式 1，数据面收发；0，控制面收发*/
#if (TCPIP_NSR == VRP_YES)    
    ULONG  ulTrunkNsrFailReason;                /* NSR失败原因记录 */
    USHORT usLacpNsrCurrentMode;                /* 记录链路当前恢复状态 */
    UCHAR  ucNsrPPIFlag;                        /* NSR过程中PPI下发标志*/
    UCHAR  ucPad[1];
#endif
}TRUNK_PORT_INFO_S;

/* Trunk控制块 */
typedef struct tagTrunkBasicInfo
{
    ULONG ulType;                             /* 接口类型：0－Trunk接口，1－成员端口 */
    ULONG ulTrunkId;                          /* Trunk ID（0－31） */
    TRUNK_PORT_INFO_S* pstTrunkPortInfo;      /* 成员端口控制块，对于Trunk接口来说，该指针为空 */

    ULONG ulTrunk1agMepCnt;  /* Trunk组上的MEP计数，成员端口上该计数无意义
                                因为成员端口上的多播下发计数等于MEP计数，所以这里不需要单独计数
                                但是TRUNK组上的多播下发计数可能不等于MEP计数 */
}TRUNK_BASIC_INFO_S;

#pragma    pack( 1 )

/* LACP报文首部结构 */
typedef struct tagLacpPdu
{
    UCHAR  ucSubType;                  /* 慢速协议中LACP的协议号 */
    UCHAR  ucVersion;                  /* 协议版本号 */
    UCHAR  ucActorType;                /* 指示为Actor类型 */
    UCHAR  ucActorInfoLen;             /* Actor信息的长度 */
    USHORT usActorSysPriority;         /* Actor的系统优先级 */
    UCHAR  ucActorSysMac[6];           /* Actor的系统MAC */
    USHORT usActorKey;                 /* Actor的端口操作Key */
    USHORT usActorPortPriority;        /* Actor的端口优先级 */
    USHORT usActorPortIndex;           /* Actor的端口号 */
    UCHAR  ucActorPortState;           /* Actor的端口LACP状态 */
    UCHAR  ucReserved1[3];             /* 保留 */
    UCHAR  ucPartnerType;              /* 指示为partner的类型 */
    UCHAR  ucPartnerInfoLen;           /* partner信息的长度 */
    USHORT usPartnerSysPriority;       /* Partner的系统优先级 */
    UCHAR  ucPartnerSysMac[6];         /* Partner的系统MAC */
    USHORT usPartnerKey;               /* Partner的端口操作Key */
    USHORT usPartnerPortPriority;      /* Partner的端口优先级 */
    USHORT usPartnerPortIndex;         /* Partner的端口号 */
    UCHAR  ucPartnerPortState;         /* Partner的端口LACP状态 */
    UCHAR  ucReserved2[3];             /* 保留 */
    UCHAR  ucCollectorType;            /* 指示为collector类型 */
    UCHAR  ucCollectorLen;             /* collector信息的长度 */
    USHORT usMaxCollectDelay;          /* 最大收集延迟,状态机并没有使用这个变量 */
    UCHAR  ucReserved3[12];            /* 保留 */
    UCHAR  ucTerminatorType;           /* 指示为terminator类型 */
    UCHAR  ucTerminatorLen;            /* terminator信息的长度 */
    UCHAR  ucReserved4[50];            /* 保留 */
} LACP_PDU_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* Trunk模块信息 */
typedef struct tagTrunkModInfo
{
    ULONG ulMID_Trunk;  /* Trunk模块ID */
    ULONG ulQUE_LACP;   /* LACP报文队列ID */
}TRUNK_MOD_INFO_S;

/* Shell向Core注册的回调函数集 */
typedef struct tagTrunkShellCallbackSet
{
    /* 调试信息输出函数 */
    VOID (*pfTRUNK_DebugOutString) (CHAR * szStr);

    /* 创建队列函数 */
    ULONG (*pfTRUNK_CreateQueue)(ULONG ulQueID,ULONG ulGetCntPerTimes,
            ULONG (*TRUNK_QueDealPacketFunc)(MBUF_S *),
            ULONG (*TRUNK_QueIsDropThisPacketFunc)(MBUF_S *,ULONG,CHAR*),
            ULONG ulMaxLen);

    /* 激活队列函数 */
    ULONG (*pfTRUNK_ActiveQueue)(ULONG ulQueID);

    /* 入队列函数 */
    ULONG (*pfTRUNK_EnQueue)(MBUF_S *);

    /* 丢弃报文函数 */
    ULONG (*pfTRUNK_DropQueue)(MBUF_S *);

    /* 释放队列中指定类型报文的函数 */
    VOID (*pfTRUNK_FreePacketInQueue)(ULONG ulQueID,ULONG ulCmd,CHAR* pData);

    /* 空函数 */
    ULONG (*pfTRUNK_DoNothing)(MBUF_S *);
    
}TRUNK_SHELL_CALLBACK_SET_S;


/* LACP状态机相关数据结构 */
/* 有状态变迁的状态机 */
enum enumLacpFsm
{
    LACP_FSM_RX = 0,        /* RX状态机 */
    LACP_FSM_PTX,           /* PTX状态机 */
    LACP_FSM_MUX,           /* MUX状态机 */
        
    LACP_FSM_END           
};

/* 接收状态机的各状态 */
enum enumLacpFsmRx
{
    LACP_RX_NOSTATE = 0,            /* 0 状态机无状态 */
    LACP_RX_CURRENT = 1,            /* 1 CURRENT状态 */
    LACP_RX_EXPIRED,                /* 2 EXPIRED状态 */
    LACP_RX_DEFAULT,                /* 3 DEFAULT状态 */
    LACP_RX_INIT,                   /* 4 INITLIZE状态*/
    LACP_RX_LACP_DISABLED,          /* 5 LACP_DISABLED状态 */
    LACP_RX_PORT_DISABLED           /* 6 PORT_DISABLED状态*/
};

/* 周期发送状态机的各状态 */
enum enumLacpFsmPtx
{
    LACP_PTX_NOSTATE = 0,           /* 状态机无状态 */
    LACP_PTX_NO_PERIODIC = 1,       /* NO_PERIODIC状态*/
    LACP_PTX_FAST_PERIODIC,         /* FAST_PERIODIC状态 */
    LACP_PTX_SLOW_PERIODIC,         /* SLOW_PERIODIC状态 */
    LACP_PTX_PERIODIC_TX            /* PERIODIC_TX状态 */
};

/* MUX状态机的各状态 */
enum enumLacpFsmMux
{
    LACP_MUX_NOSTATE = 0,       /* 状态机无状态 */
    LACP_MUX_DETACHED = 1,      /* DETACHED状态*/
    LACP_MUX_WAITING,           /* WAITING状态 */
    LACP_MUX_ATTACHED,          /* ATTACHED状态 */
    LACP_MUX_COLLECTING,        /*COLLECTING状态*/
    LACP_MUX_DISTRIBUTING,      /*DISTRIBUTING状态*/
    LACP_MUX_DISTRICOLLECT      /* DISTRIBUTING_COLLECTING状态 */
};

/* 状态机状态变迁的原因 */
enum enumLacpSti
{
    LACP_BEGIN_FALSE =1,            /* 非初始化状态*/
    LACP_BEGIN_TRUE,                /* 初始化*/
    LACP_UCT,                       /* 无条件转移 */
    LACP_PORTMOVED_TRUE,            /* 端口转移*/
    LACP_PORTMOVED_FALSE,           /* 端口未转移*/
    LACP_PORT_ENABLED_TRUE,         /* 端口可用*/
    LACP_PORT_ENABLED_FALSE,        /* 端口不可用*/
    LACP_ENABLED_TRUE,              /* 端口使能LACP*/
    LACP_ENABLED_FALSE,             /* 端口关闭LACP*/
    LACP_PDU_INDICATE,              /*收到LACPDU*/
    LACP_CURRENTTIMER_EXPIRED,      /*CURRENT定时器超时*/
    LACP_PASSIVE,                   /*双方都是passive模式*/    
    LACP_PERIOTIMER_EXPIRED,        /* 周期定时器超时*/
    LACP_LONGTIMEOUT,               /* LACP信息长超时*/
    LACP_SHORTTIMEOUT,              /* LACP信息短超时*/
    LACP_PORT_SELECTED,             /* Selected变量为SELECTED*/
    LACP_PORT_UNSELECTED,           /* Selected变量为UNSELECTED*/
    LACP_PORT_STANDBY,              /* Selected变量为STANDBY*/
    LACP_READY,                     /* READY为真*/
    LACP_ACTOR_INSYNC,              /* 本端协议信息同步*/
    LACP_ACTOR_OUTSYNC,             /* 本端协议信息失步*/
    LACP_PARTNER_INSYNC,            /* 对端协议信息同步*/
    LACP_PARTNER_OUTSYNC,           /* 对端协议信息失步*/
    LACP_ACTORCHURNTIMER_EXPIRED,   /* ACTORCHURN定时器超时*/
    LACP_PARTNERCHURNTIMER_EXPIRED, /* PARTNERCHURN定时器超时*/
    LACP_NTT_TRUE,                  /* 需要发送LACPDU*/
};

/* 成员端口的状态 */
enum enumPortLinkStatus
{
    LACP_PORT_DOWN = 0,            /* lacp status 端口DOWN */
    LACP_PORT_UP = 1,              /* lacp status 端口UP */
};

/* 以下为状态机迁移的数据结构定义 */
typedef struct tagLacpFsmTran
{
    UCHAR ucStartState;       /* 初始状态,枚举值,参见相关定义 */
    UCHAR ucTranCondition;     /* 激励条件,枚举值,参见相关定义 */
    UCHAR ucEndState;          /* 终止状态,枚举值,参见相关定义 */
}LACP_FSMTRAN_S;

/* End of LACP状态机相关数据结构 */

/* LACP接收的外部事件 */
enum enumLACPEVENTTYPE
{
    LACP_EVENT_UP = 0,
    LACP_EVENT_DOWN,  
    LACP_EVENT_INIT,   
    LACP_EVENT_LEAVE
};

/* 选择逻辑中的待选端口信息 */
typedef struct tagTrunkLacpSelectPortInfo
{ 
    IFNET_S *pIf;         /* 成员端口IFNET指针 */
    LACP_NEGO_S * pstLacpNego;    /* 成员端口控制块 */
    LACP_PORT_FSM_S *pstLacpPortFsm; /* 状态机信息表指针 */
}TRUNK_LACP_SELECT_PORT_INFO_S;

/* 手工trunk中选择逻辑中的待选端口信息 */
typedef struct tagTrunkNoLacpSelectPortInfo
{ 
    IFNET_S *pIf;                       /* 成员端口IFNET指针 */
    TRUNK_PORT_INFO_S * pstPortInfo;    /* 成员端口控制块 */
}TRUNK_NOLACP_SELECT_PORT_INFO_S;

/* SGSN需求 BC3D02743 20100224: 为支持告警处理新增此数据结构，在选择逻辑遍历时记录必要信息，防止为告警重复遍历 */
typedef struct tagTrunkWarnPortInfo
{ 
    IFNET_S *pIf;         /* 成员端口IFNET指针 */
    TRUNK_PORT_INFO_S * pstPortInfo;    /* 成员端口控制块 */        
    ULONG    ulIsHalfDuplex;
    ULONG    ulPortSpeedKey;
}TRUNK_WARN_SELECT_PORT_INFO_S;

/* 选择逻辑中的待选M:N端口信息 */
typedef struct tagTrunkMtoNSelectPortInfo
{ 
    ULONG  ulIndex; /*端口索引*/
    USHORT usPortNumber;
    USHORT usPortPri;
    ULONG  ulRemoteDefault;         /* 对端是否处于Defaulted状态 */
}TRUNK_LACP_MTON_PORT_INFO_S;

/* LACP状态字段的activity位的取值 */
enum enumLacpStateActivity
{
    LACP_State_Passive = 0,
    LACP_State_Active,
};

/* LACP状态字段的TimeOut位的取值 */
enum enumLacpStateTimeOut
{
    LACP_State_LongTimeOut = 0,
    LACP_State_ShortTimeOut,
};

/*Add by Q62011 for BC3D00939*/
typedef ULONG (*TRUNK_VLANCHECK_HOOK_FUNC)(IFNET_S *pIfnet);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_TYP_H_ */
