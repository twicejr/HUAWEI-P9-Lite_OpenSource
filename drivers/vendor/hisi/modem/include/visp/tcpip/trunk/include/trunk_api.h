/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_api.h
*
*  Project Code: VISPV1R6
*   Module Name:   
*  Date Created: 2008-3-8
*        Author: LY(57500)
*   Description: trunk模块对外提供的用户接口声明、数据结构和宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-3-8  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _TRUNK_API_H_
#define _TRUNK_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Trunk模块用户API错误码 */
enum enTrunkErrInfo
{
    TK_OK  = VOS_OK,
    TK_ERR = VOS_ERR,
    TK_PARAM_ERR,                  /* 2、输入参数不合法 */
    TK_IF_NULL,                    /* 3、根据接口索引获取接口指针为空 */
    TK_REPEAT_JOIN,                /* 4、端口已经加入了Trunk */
    TK_TRUNKID_NULL,               /* 5、Trunk ID无对应Trunk接口 */
    TK_PORT_FULL,                  /* 6、Trunk下已经有8个成员端口 */
    TK_PORT_ISNOT_FE,              /* 7、端口不是FE口或GE口 */
    TK_PORT_HAVE_IP,               /* 8、端口具有IP相关属性，如已经配置了地址，已经借用地址给其他接口 */
    TK_IF_ISNOT_MEMBERSHIPPORT,    /* 9、接口不是成员端口 */
    TK_TRUNKCB_NULL,               /* 10、接口的Trunk控制块为空 */
    TK_PORT_HAVE_PPPOE,            /* 11、端口已经使能PPPOE */
    TK_LACP_NEGOTBL_NULL,          /* 12、端口的LACP协商信息表为空 */
    TK_LACP_FSMTBL_NULL,           /* 13、端口的状态机信息表为空 */
    TK_TRUNK_HAVE_PORT,            /* 14、Trunk下已有成员端口 */
    TK_HA_IS_SMOOTHING,            /* 15、HA正在手动倒换或平滑处理*/
    TK_IF_ISNOT_TRUNK,             /* 16、接口不是Trunk接口 */ 
    TK_PORT_CFG_DHCP4R,            /* 17、接口配置了DHCP4 RELAY     */ 
    TK_TRUNKID_ERR,                /* 18、Trunk ID值非法            */ 
    TK_PORT_HAVE_MULTIIP,          /* 19、端口具有多播IP            */
    TK_PORT_HAVE_IPV6,             /* 20、端口有ipv6地址            */ 
    TK_TRUNK_IF_NULL,              /* 21、Trunk接口为空             */ 
    TK_IPIF_NULL,                  /* 22、接口的ipif控制块为空      */
    TK_TRUNKCB_NOMEM,              /* 23、分配trunk cb控制块内存失败    */
    TK_PORTINFO_NOMEM,             /* 24、分配port info控制块内存失败   */
    TK_LACPNEGO_NOMEM,             /* 25、分配lacp nego控制块内存失败   */
    TK_LACPFSM_NOMEM,              /* 26、分配lacp fsm控制块内存失败    */
    TK_PORTINFO_NULL,              /* 27、port info控制块为空           */
    TK_NO_PORT,                    /* 28、trunk内没有成员端口           */ 
    TK_PORT_SETVLAN,               /* 29、成员端口使能了vlan            */
    TK_PORT_SETARPPROXY,           /* 30、成员端口设置了ARP代理         */ 
    TK_NOT_REGISTER,               /* 31、trunk模块未注册               */ 
    TK_DYNAMIC_MAC_FIRST_PORT,     /* 32、动态physical地址分配策略第一个端口必须最后一个退出  */
    TK_PORT_ENABLE_1AG,            /* 33、待加入Trunk的Eth口已经使能了1AG功能 */
    
    TK_IS_NOT_L3_ETH,              /* 34、将非三层eth口加入到L3-TRUNK中或者将映射端口加入到三层TRUNK中 */
    TK_IS_NOT_L2_TRUNKPORT,        /* 35、待非L2_TRUNKPORT接口加入到L2-TRUNK中 */
    TK_IS_L2IF,                    /* 36、待操作的是L2TRUNK */
    TK_IS_NOT_L2IF,                /* 37、待操作的不是L2TRUNK */
    TK_WRONG_LACP_STATUS,          /* 38、设置LACP状态时传入错误的状态 */
    TK_NOT_VIRTUAL,                /* 39、待设置的端口不是映射端口(不是虚加入方式加入L2TRUNK) */
    TK_NEG_TIME_REACHMAX,          /* 40 达到首次协商不过对外告警最大时间 */
    TK_DELETE_TIMER_FAIL,          /* 41 删除首次协商不过对外告警定时器失败 */   
    TK_CREATE_TIMER_FAIL,          /* 42 创建首次协商不过对外告警定时器失败 */  
    TK_NULL_POINTER,               /* 43 输入指针参数为空       */   

    TK_GET_PORTNO_FAIL,            /* 44 获取Port type和Port number失败 */
    TK_IS_NOT_TRUNK_TYPE,          /* 45 不是Trunk接口类型 */
    TK_IS_NOT_MTON_MODE,           /* 46 不是M:N备份模式 */
    TK_LACP_ENABLE,                /* 47 已使能了LACP协商，不能设置为1:1备份模式 */
    TK_PORT_NOT_IN_TRUNK,          /* 48 成员端口不属于该TRUNK组 */
    TK_WRONG_RECOVER_MODE,         /* 49 错误的恢复模式 */
    TK_WRONG_BACKUP_MODE,          /* 50 错误的备份模式 */
    TK_ONETOONE_PORT_FULL,         /* 51 1:1模式端口数已满 */
    TK_IS_NOT_THISBORAD,           /* 52 非本板接口 */

    TK_POLICY_IS_RECOVER_MODE,     /* 53 产品该定制策略下TRUNK不能为恢复模式 */
    TK_POLICY_IS_LACP_ENABLE,      /* 54 产品该定制策略下TRUNK不能使能LACP */
    TK_POLICY_HAVE_MEMBERPORT,     /* 55 使能/去使能产品该定制策略下TRUNK不能存在成员端口 */
    TK_POLICY_IS_BAKCUP_MODE_NORMAL,  /* 56 产品该定制策略下TRUNK不能为正常备份模式 */
    TK_POLICY_ACTIVEPORT_MUST_ONE, /* 57 产品该定制策略下TRUNK在M:N模式下激活端口数必须为1 */
    TK_POLICY_MEMBERPORT_IS_FULL,  /* 58 产品该定制策略下TRUNK在M:N模式下添加端口数不能超过2个*/
    TK_POLICY_WRONG_TYPE,          /* 59 错误的定制策略 */
    TK_POLICY_IS_STATIC_GETMAC,    /* 60 产品该定制策略下TRUNK的physical地址获取策略不能为固定physical地址分配策略 */
    
    TK_PPI_CALLBACK,               /* 61 PPI下发钩子函数未注册*/

    TK_NSR_STATE_ERR,              /* 62 NSR当前状态错误*/
    TK_NSR_ETHER_MAC_CHANG,        /* 63 发现Trunk成员端口上报的以太MAC出现不一致 */
    TK_NSR_ETHER_MAC_INVALID,         /* 64 控制面上报的以太MAC为空 */
    TK_NSR_WRONG_LINK_STATUS,          /*65 转发面维护的的链路状态错误*/
    TK_NSR_WRONG_LINK_KEY,          /*66 转发面维护的key值与控制面不一致 */ 
    TK_NSR_WRONG_LINK_PORT_NO,      /*67 转发面维护的port NO. 为无效值*/
    TK_NSR_WRONG_LINK_EXPIRED,      /*68 转发面维护的超时模式不一致 */
    TK_NSR_WRONG_LINK_SYSMAC,       /*69 转发面维护的系统MAC错误*/
    TK_NSR_ERR_PRECONFIG,           /*70 与配置未开启NSR特性 */
    TK_NSR_ERR_DISABLING,           /*71 TRUNK NSR在去使能过程中*/
    TK_NSR_ERR_DISABLE,             /*72 TRUNK NSR未使能  */
    TK_NSR_LACP_MODE,               /*73 TRUNK LACP下移未使能 */
    TK_NSR_NOT_FINISHED,            /*74 TRUNK NSR 过程没有结束 */
    TK_NSR_IF_NOT_EXIST,            /*75 调用TRUNK NSR 查询api时找不到对应接口 */
    TK_NSR_IF_NOT_ETHERNET,         /*76 调用TRUNK NSR 查询api时对应接口不是ethernet */
    TK_NSR_IF_NOT_THIS_BOARD,       /*77 调用TRUNK NSR 查询api时对应接口不是本板的 */
    TK_NSR_LINK_RESUME_FAIL,        /*78 此链路恢复失败 */
    TK_NSR_TRUNK_MAC_RESUME_FAIL,   /*79 此trunk mac恢复失败 */
    TK_HA_CFGSYSMAC_ERR,            /*80 TRUNK HA不支持按照TRUNK组配置系统MAC*/
}; 

/* 输出成员端口统计信息 */
typedef struct tagPORT_STAT_INFO
{
    ULONG ulOutSum;     /* 发送的报文总数 */
    ULONG ulOutLacp;    /* 发送的LACP报文数 */
    ULONG ulOutDrop;    /* 发送时丢弃的报文数 */
    ULONG ulInSum;      /* 接收的报文总数 */
    ULONG ulInLacp;     /* 接收的LACP报文数 */
    ULONG ulInDrop;     /* 接收时丢弃的报文数 */
    /* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
    ULONG ulLacpExpired;  /* NP上报超时统计 */
    ULONG ulLacpPPIPKT;   /* LACP下发NP后，透传报文统计 */
}PORT_STAT_INFO_S;

/* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
typedef struct tagTRUNK_LACP_NOTIFY
{
    UCHAR  ucOper;             /* 通知消息类型：LACP_WARNING_TIMEOUT*/
    UCHAR  ucRes[3];
    ULONG  ulPortIfIndex;      /* 成员端口接口索引 */
}TRUNK_LACP_NOTIFY_S;

/* Trunk接口最小成员端口数目 */
#define TRUNK_PORT_MIN_NUM      1

/* Trunk接口最大成员端口数目 */
/* Modified by w00207740, Trunk Msp大规格需求，上调每个Trunk接口下最大成员端口数目, 2014/1/9 */
#define TRUNK_PORT_MAX_NUM      32

/* SGSN Trunk跨板协商需求:根据三维值获取PortId的钩子函数原型 */
typedef ULONG (*TRUNK_GETLACPPORTID_HOOK_FUNC)(
    ULONG ulFirstDimension,      /* Input: 接口第一维值 */
    ULONG ulSecondDimension,     /* Input: 接口第二维值 */
    ULONG ulThirdDimension,      /* Input: 接口第三维值 */
    USHORT* pusPortID);          /* Output: 返回的Port Id */

typedef ULONG (*TRUNK_NSR_FINISHNOTIFY)(ULONG ulMsgType);


/* 输出Trunk接口信息和其下成员端口信息 */
typedef struct tagTRUNK_INFO
{
    ULONG ulIfIndex;                             /* Trunk接口索引 */
    ULONG ulTrunkId;                             /* Trunk ID */
    UCHAR ucMacAddress[6];                       /* Trunk的physical地址 */
    UCHAR ucBfdTrunkMode;                        /* trunk或成员端口上建立单跳bfd的生效模式,默认trunk优先 */   
    UCHAR ucMacDynamic;                          /* Trunk physical地址获取模式是否为动态获取模式              */
    ULONG ulPortNum;                             /* Trunk成员端口总数 */
    ULONG ulPortIfIndex[TRUNK_PORT_MAX_NUM];     /* 成员端口接口索引数组 */
    ULONG ulUpPortNum;                           /* UP的成员端口数 */
    ULONG ulUpPortIfIndex[TRUNK_PORT_MAX_NUM];   /* UP的成员端口接口索引数组 */
    ULONG ulEnableLacp;                          /* 是否使能LACP */
    ULONG ulRefIfIndex;                          /* 参考端口接口索引 */
    ULONG ulMacPortIndex;                        /* 动态获取Trunk mac时所使用mac的成员端口索引 */
    ULONG ulGateValue;                           /* Trunk 门值信息 */
    ULONG ulVPortIfIndex[TRUNK_PORT_MAX_NUM];    /* Trunk内以映射端口方式加入的成员端口索引 */
    ULONG ulPassive;                             /* 是主动端还是被动端 */
    UCHAR ucBackupMode;                          /* 端口备份模式,0,普通模式;1,1:1备份模式，2,M:N备份模式 */ 
    UCHAR ucRecoverMode;                         /* 端口备份的恢复模式,0,恢复模式;1,非恢复模式 */
    USHORT usSysPri;                             /* Trunk组的系统优先级 */
    ULONG ulMasterIfIndex;                       /* 端口1:1模式下配置的主端口索引 */
    ULONG ulActiveNum;                           /* 端口M:N模式下配置的激活端口数 */
    ULONG ulProductPolicy;                       /* 产品定制的TRUNK策略 */
}TRUNK_INFO_S;

/* 输出成员端口的状态机信息表信息 */
typedef struct tagLACP_FSM_INFO
{
    BOOL_T bRXBegin;              /* 接收状态机初始化标志 */
    BOOL_T bPTXBegin;             /* 周期发送状态机初始化标志 */
    BOOL_T bMUXBegin;             /* MUX状态机初始化标志 */
    BOOL_T bPortEnable;           /* 端口物理状态标志 */
    USHORT usSelected;            /* 端口选择结果 */
    BOOL_T bCurWhileTimerActive;  /* 接收定时器开启标志 */
    BOOL_T bPeriodicTimerActive;  /* 周期发送定时器开启标志 */
    UCHAR ucRXState;              /* 接收状态机状态 */
    UCHAR ucPTXState;             /* 周期发送状态机状态 */
    UCHAR ucMUXState;             /* MUX状态机状态 */
    UCHAR ucPadding[3];
} LACP_FSM_INFO_S;

/* 输出成员端口的协商信息表信息 */
typedef struct tagLACP_NEGO_INFO
{
    ULONG ulActor_TimeOutMode;    /* 本端周期模式（0－长周期，1－短周期）*/
    BOOL_T bActor_PortUp;         /* 本端端口数据收发使能标志 */
    BOOL_T bActor_Defaulted;      /* 本端端口处于默认状态标志 */
    ULONG ulActor_Key;            /* 本端端口运作key */
    ULONG ulActor_PortPri;        /* 本端端口优先级 */
    ULONG ulActor_PortNum;        /* 本端端口号 */

    ULONG ulPartner_TimeOutMode;  /* 对端周期模式（0－长周期，1－短周期）*/
    BOOL_T bPartner_Collecting;   /* 对端端口数据接收使能标志 */
    BOOL_T bPartner_Distributing; /* 对端端口数据发送使能标志 */
    ULONG ulPartner_Key;          /* 对端端口运作key */
    ULONG ulPartner_PortPri;      /* 对端端口优先级 */
    ULONG ulPartner_PortNum;      /* 对端端口号 */
    ULONG ulPartner_SysPri;       /* 对端系统优先级 */
    BOOL_T bPartner_Syn;          /* 对端端口同步状态（是否选择成功） */
    UCHAR ucPartner_SysMac[6];    /* 对端系统MAC */
}LACP_NEGO_INFO_S;

typedef struct tagTRUNK_NSR_GLOBAL_INFO
{
    ULONG ulTrunkNsrState;                  /* 当前Trunk Nsr状态 */
    ULONG ulTrunkNsrTimeout;                /* Trunk Nsr 超时 */
    ULONG ulAddPortNum;                     /* NSR过程中，用户添加成员端口数目*/
    ULONG ulRemovePortNum;                  /* NSR过程中，用户移除成员端口数目*/
    ULONG ulSuccessResumeLinkNum;           /* 恢复成功链路数量 */
    ULONG ulResumeWrongInfoNum;             /* 转发面恢复信息错误 */
    ULONG ulResumeWrongMacNum;              /* 转发面恢复以太mac错误 */
    ULONG ulResumeLinkNotExistNum;          /* 没有从底层获取到 */
    ULONG ulSuccessSmoothLinkNum;           /* 平滑成的链路数量 */
    ULONG ulFailSmoothLinkNum;              /* 平滑失败链路数量 */
    ULONG ulFailSmoothWrongMacNum;          /* 因恢复的trunk的mac不是trunk任何一个成员端口的mac，平滑失败链路数量 */
}TRUNK_NSR_GLOBAL_INFO_S;

typedef struct tagTRUNK_NSR_LINK_INFO
{
    ULONG  ulTrunkNsrFailReason;                /* NSR失败原因记录 */
    UCHAR  ucNsrPPIFlag;                        /* NSR过程中PPI下发标志*/
    UCHAR  ucPad[3];
}TRUNK_NSR_LINK_INFO_S;

/* Trunk模块调试信息开关 */
enum enumTRUNKDEBUGTYPE
{
    TRUNK_DEBUG_ALL = 0,           /* 设置全部调试信息 */
    TRUNK_DEBUG_LACPPKT,           /* 设置LACP调试信息 */
    TRUNK_DEBUG_OTHERPPKT,         /* 设置其他报文调试信息 */
    TRUNK_DEBUG_FSM                /* 设置状态机变迁调试信息 */
};

/* LACP状态机事件 */
enum enumLACPFSMEVENTTYPE
{
    LACP_UP = 0,
    LACP_DOWN, 
};

/* 成员端口的选择状态 */
enum enumAggPortType
{
    LACP_UNSELECTED = 0,
    LACP_SELECTED,
    LACP_STANDBY,
};

/* 端口类型 */
enum enumTrunkType
{
    TRUNK_ISTRUNK = 0,      /* TRUNK接口    */
    TRUNK_ISTRUNKPORT,      /* 成员端口     */
    TRUNK_IFTYPEERR,        /* 其他类型端口 */
    TRUNK_IFNULL,           /* 端口为空     */
    TRUNK_INNERERR,         /* 端口内部异常 */
};

/*Added by wangtong207740, LACP下移需求，DTS2012052505387 , 2012/5/26 */
typedef enum enumTcpipLacpWarning
{
    LACP_WARNING_NO = 0,
    LACP_WARNING_TIMEOUT = 1,  /*NP 探测到*/     

    LACP_WARNING_NOTIFY_MAX,
}TCPIP_LACP_WARNING_E;

/*Added by w00207740, NSR TRUNK,新增消息与PPI下发命令, 2013/9/10 */
enum tagTrunkNsrPpiType
{
    PPI_TRUNK_NSR_GET_LINKINFO  ,                       /* 从底层获取信息 */
    PPI_TRUNK_NSR_LINK_SMOOTH_SUCCESS,                  /* 通知转发链路恢复成功*/
    PPI_TRUNK_NSR_LINK_SMOOTH_FAIL,                     /* 通知转发面链路恢复失败*/
    PPI_TRUNK_NSR_PROCESS_COMPLETE,                     /* 链路恢复完成之后下发通知控制面 */
    PPI_TRUNK_NSR_PROCESS_FAIL,                         /* 链路恢复失败通知命令 */
    PPI_TRUNK_NSR_ENABLE,                               /* 通知转发面使能NSR功能 */
    PPI_TRUNK_NSR_DISABLE,                              /* 通知转发面去使能NSR功能 */
    PPI_TRUNK_NSR_MAX,
};

/* trunk报文用户分发策略函数的三种返回值 */
#define TRUNK_PKT_USEROUT      0   /* 由用户指定成员端口发送 */
#define TRUNK_PKT_DEFAULTOUT   1   /* 按VISP缺省分发策略发送 */
#define TRUNK_PKT_DISCARD      2   /* 丢弃报文，不予发送 */


/* 加入Trunk的成员端口是实端口还是映射端口 */
#define TRUNK_PORT_REAL        0
#define TRUNK_PORT_VIRTUAL     1

#define   TRUNK_BACKUP_MODE_NORMAL        0  /*正常模式(默认)*/
#define   TRUNK_BACKUP_MODE_ONE_TO_ONE    1  /*1:1 备份模式*/
#define   TRUNK_BACKUP_MODE_M_TO_N        2  /*M:N备份模式*/

#define   TRUNK_RECOVER_MODE_YES        0  /*恢复模式*/
#define   TRUNK_RECOVER_MODE_NO         1  /*非恢复模式*/

#define   TRUNK_MIN_ACTIVE_NUMBER       1 /* M:N模式最小激活端口数 */
#define   TRUNK_MAX_ACTIVE_NUMBER       8 /* M:N模式最大激活端口数 */

/* Add by shuxieliu00176784/baiweiqiang00177000, at 2011-06-30. 修改原因:  产品定制策略类型 */
#define   TRUNK_POLICY_DEFAULT_PROCESS          0 /* VISP默认处理方式 */
#define   TRUNK_POLICY_PROTMAC_NOTREFRESH       1 /* 定制TRUNK组网优化功能策略(TRUNK成员端口physical地址不变更,TRUNK physical地址与当前UP的成员端口physical地址一致） */


/* 参数说明：
struct tagMBuf *pstMBuf         报文MBuf指针
USHORT usPid                    以太报文协议号
ULONG ulIsVanPkt                以太报文是否是VLAN报文
ULONG ulUpPortNum               UP的成员端口数
ULONG* pulUpPortIfIndex         UP的成员端口索引数组指针
ULONG* pulIfIndex               输出参数：分发接口索引，即从哪个端口发送
*/
typedef ULONG (*TRUNK_DISTRIBUTE_HOOK_FUNC)(struct tagMBuf *pstMBuf, USHORT usPid, ULONG ulIsVanPkt, ULONG ulUpPortNum, ULONG* pulUpPortIfIndex, ULONG* pulIfIndex);

/* 获取physical地址 */
typedef ULONG (*TRUNK_GETMACADDRRESS_HOOK_FUNC)(ULONG ulTrunkId, UCHAR* pucMacAddr);
/* 释放physical地址 */
typedef VOID  (*TRUNK_FREEMACADDRRESS_HOOK_FUNC)(ULONG ulTrunkId, UCHAR* pucMacAddr);

/*Added by w00207740, NSR TRUNK,新增钩子函数, 2013/8/7 */
typedef ULONG (*TRUNK_NSR_PPI_HOOK)(ULONG ulIfIndex, ULONG ulCmd, UCHAR *pucData);
    
/* api declare  */
/*******************************************************************************
*    Func Name: TCPIP_AddToTrunk
*  Description: 添加Trunk成员端口，有共享数据互斥保护
*        Input: ULONG ulIfIndex: 待添加的成员端口接口索引
*               ULONG ulTrunkId: Trunk ID（0－31）
*               USHORT usPri:    端口优先级（值域有效，0为最高优先级）
*       Output: 
*       Return: VOS_OK（0）                  成功
*               VOS_ERR（1）                 失败
*               TK_PARAM_ERR                 2、输入参数不合法 
*               TK_IF_NULL                   3、根据接口索引获取接口指针为空
*               TK_REPEAT_JOIN               4、端口已经加入了Trunk 
*               TK_TRUNKID_NULL              5、Trunk ID无对应Trunk接口
*               TK_PORT_FULL                 6、Trunk下已经有8个成员端口
*               TK_PORT_ISNOT_FE             7、端口不是FE口
*               TK_PORT_HAVE_IP              8、端口具有IP相关属性，如已经配置了地址，已经借用地址给其他接口
*               TK_TRUNKCB_NULL              10、Trunk接口的Trunk控制块为空
*               TK_PORT_HAVE_PPPOE           11、端口已经配置了PPPOE
*               TK_PORT_CFG_DHCP4R           12、端口已使能dhcp relay
*               TK_TRUNKID_ERR               18、trunk id非法
*               TK_PORT_HAVE_MULTIIP         19、端口有多播ip
*               TK_PORT_HAVE_IPV6            20、端口有ipv6地址
*               TK_TRUNK_IF_NULL             21、Trunk接口为空
*               TK_IPIF_NULL                 22、接口的ipif控制块为空
*               TK_TRUNKCB_NOMEM             23、分配trunk cb控制块内存失败
*               TK_PORTINFO_NOMEM            24、分配port info控制块内存失败
*               TK_LACPNEGO_NOMEM            25、分配lacp nego控制块内存失败
*               TK_LACPFSM_NOMEM             26、分配lacp fsm控制块内存失败
*               TK_PORT_SETVLAN              29、端口已经使能了VLAN     
*               TK_PORT_SETARPPROXY          30、端口设置了ARP代理
*               TK_NOT_REGISTER              31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_AddToTrunk(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);

/*******************************************************************************
*    Func Name: TCPIP_AddVPortToTrunk
* Date Created: 2008-11-21
*       Author: luowentong105073
*  Description: 将映射端口加入到TRUNK(vispv1r7c03 l2if,TGW应用场景)
*        Input: ULONG ulIfIndex:待加入的端口索引
*               ULONG ulTrunkId:要加入的trunkid
*               USHORT usPri:优先级
*       Output: 
*       Return: TK_OK:成功/其它:失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-21   luowentong105073        Create
*
*******************************************************************************/
extern ULONG  TCPIP_AddVPortToTrunk(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);

/*******************************************************************************
*    Func Name: TCPIP_DelFromTrunk
*  Description: 将端口从Trunk接口中解除，有共享数据互斥保护
*        Input: ULONG ulIfIndex: 接口索引
*       Output: 
*       Return: VOS_OK（0）                  成功
*               VOS_ERR（1）                 失败
*               TK_IF_NULL                   3、根据接口索引获取接口指针为空
*               TK_IF_ISNOT_MEMBERSHIPPORT   9、接口不是成员端口
*               TK_TRUNKID_NULL              5、Trunk ID无对应Trunk接口
*               TK_TRUNKCB_NULL              10、接口的Trunk控制块为空 
*               TK_TRUNKID_ERR               18、Trunk ID值非法               
*               TK_IPIF_NULL                 22、接口的ipif控制块为空 
*               TK_PORTINFO_NULL             27、port info控制块为空
*               TK_NO_PORT                   28、trunk内没有成员端口
*               TK_NOT_REGISTER              31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_DelFromTrunk(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkSonStat
*  Description: 获取成员端口统计信息，有共享数据互斥保护
*        Input: ULONG ulIfIndex: ifnet接口索引
*               PORT_STAT_INFO_S *pstPortStatInfo: 获取成员端口信息指针
*       Output: pstPortStatInfo:成员端口统计信息
*       Return: VOS_OK:成功
*               TK_PARAM_ERR:参数不合法
*               TK_IF_NULL:ifnet接口指针为空
*               TK_IF_ISNOT_MEMBERSHIPPORT:接口不是成员端口
*               TK_TRUNKCB_NULL  10、接口的Trunk控制块为空
*               TK_NOT_REGISTER  31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkSonStat(ULONG ulIfIndex, PORT_STAT_INFO_S * pstPortStatInfo);
/*******************************************************************************
*    Func Name: TCPIP_ClrTrunkSonStat
*  Description: 清除成员端口信息，有共享数据互斥保护
*        Input: ULONG ulIfIndex: 成员端口ifnet指针
*       Output: 
*       Return: VOS_OK:成功
*               TK_PARAM_ERR:参数不合法
*               TK_IF_NULL:ifnet接口指针为空
*               TK_IF_ISNOT_MEMBERSHIPPORT:接口不是成员端口
*               TK_TRUNKCB_NULL  10、接口的Trunk控制块为空
*               TK_NOT_REGISTER  31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_ClrTrunkSonStat(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetTrunkDebug
*  Description: 设置调试开关选项，有共享数据互斥保护
*        Input: ULONG ulSwitch: 开关类型（0－所有信息，1－LACP报文处理信息
*                               2－其它报文处理信息，3－状态机变迁信息，其它－非法值）
*               ULONG ulValue: 设置值（0－关闭，1－打开，其它非法）
*       Output: 
*       Return: VOS_OK（0）        成功
*               TK_PARAM_ERR（2）  输入参数不合法
*               TK_NOT_REGISTER  31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_SetTrunkDebug(ULONG ulSwitch, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkDebug
*  Description: 获取trunk调试开关状态
*        Input: ULONG *pulLacpPktDbgSw: LACP报文调试开关
*               ULONG *pulOtherPktDbgSw: 其他报文调试开关
*               ULONG *pulFsmDbgSw: 状态机调试开关
*       Output: 
*       Return: VOS_OK 获取成功
*               TK_PARAM_ERR 参数错误
*               TK_NOT_REGISTER  31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkDebug(ULONG *pulLacpPktDbgSw, ULONG *pulOtherPktDbgSw, ULONG *pulFsmDbgSw);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkInfo
*  Description: 查询Trunk接口及其下属成员端口信息，有共享数据互斥保护
*        Input: ULONG ulTrunkId: 成员ID
*               TRUNK_INFO_S * pstTrunkInfo: 用于输出Trunk接口信息的空间指针
*       Output: TRUNK_INFO_S * pstTrunkInfo: 输出Trunk接口信息和其下成员端口信息
*       Return: VOS_OK                  0 成功
*               TK_PARAM_ERR            2、输入参数不合法
*               TK_TRUNKID_NULL         5、Trunk ID无对应的Trunk接口
*               TK_TRUNKID_ERR          18、Trunk ID值非法
*               TK_NOT_REGISTER         31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkInfo(ULONG ulTrunkId, TRUNK_INFO_S *  pstTrunkInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkIdByIf
*  Description: 根据接口索引获取Trunk ID，有共享数据互斥保护
*        Input: ULONG ulIfIndex: 输入ifnet索引
*               ULONG *pulTrunkId: 用于输出的trunk ID号的空间指针
*       Output: ULONG *pulTrunkId: 输出的trunk ID号
*       Return: VOS_OK（0）             成功
*               TK_PARAM_ERR（2）       输入参数不合法
*               TK_IF_NULL（3）         根据接口索引获取接口指针为空
*               TK_TRUNKCB_NULL（10）   接口的Trunk控制块为空
*               TK_NOT_REGISTER         31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkIdByIf(ULONG ulIfIndex, ULONG *pulTrunkId);
/*******************************************************************************
*    Func Name: TCPIP_Lacp
*  Description: 使能/去使能LACP，有共享数据互斥保护
*        Input: ULONG ulIfIndex: 输入ifnet接口索引
*               ULONG ulValue:  使能/去使能标记（0－去使能，1－使能）
*       Output: 
*       Return: VOS_OK（0）                  成功
*               TK_PARAM_ERR（2）            输入参数不合法
*               TK_IF_NULL（3）              根据接口索引获取接口指针为空
*               TK_TRUNKID_NULL（5）         Trunk ID无对应Trunk接口
*               TK_TRUNKCB_NULL（10）        接口的Trunk控制块为空
*               TK_TRUNK_HAVE_PORT(14)       Trunk下已有成员端口
*               TK_IF_ISNOT_TRUNK(16)        接口不是Trunk接口
*               TK_HA_IS_SMOOTHING(15)       HA正在手动倒换或平滑处理 
*               TK_NOT_REGISTER              31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_Lacp(ULONG ulIfIndex, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_SetLacpPeriodMode
* Description: 配置长周期/短周期模式，有共享数据互斥保护
*       Input: ULONG ulIfIndex: ifnet接口索引
*              ULONG ulValue:  长周期/短周期配置值（0－长周期,1－短周期）
*      Output: 
*      Return: VOS_OK（0）                       成功
*              TK_PARAM_ERR（2）                 输入参数不合法
*              TK_IF_NULL（3）                   根据接口索引获取接口指针为空
*              TK_IF_ISNOT_MEMBERSHIPPORT（9）   接口不是成员端口
*              TK_LACP_NEGOTBL_NULL（12）        端口的LACP协商信息表为空
*              TK_LACP_FSMTBL_NULL (13）         端口的状态机信息表为空
*              TK_HA_IS_SMOOTHING(15)            HA正在手动倒换或平滑处理
*              TK_NOT_REGISTER                   31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_SetLacpPeriodMode(ULONG ulIfIndex, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetLacpFsmInfo
*  Description:查询指定端口的LACP状态机信息，有共享数据互斥保护
*        Input: ULONG ulIfIndex: ifnet接口指针
*               LACP_FSM_INFO_S *pstFsmInfo: (stay here for avoid HCC warning)
*       Output: LACP_FSM_INFO_S *pstFsmInfo: 用于输出LACP状态信息表的结构指针
*       Return: VOS_OK（0）                       成功
*               TK_PARAM_ERR（2）                 输入参数不合法
*               TK_IF_NULL（3）                   根据接口索引获取接口指针为空
*               TK_IF_ISNOT_MEMBERSHIPPORT（9）   接口不是成员端口
*               TK_LACP_FSMTBL_NULL (13）         端口的状态机信息表为空
*               TK_TRUNKCB_NULL(10)               接口的Trunk控制块为空
*               TK_NOT_REGISTER                   31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetLacpFsmInfo(ULONG ulIfIndex, LACP_FSM_INFO_S * pstFsmInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetLacpNegoInfo
*  Description: 查询指定端口的LACP协商信息
*        Input: ULONG ulIfIndex: ifnet接口指针
*               LACP_NEGO_INFO_S *pstNegoInfo: 输出的LACP协商信息
*       Output: 
*       Return: VOS_OK（0）                        成功
*               TK_PARAM_ERR（2）                  输入参数不合法
*               TK_IF_NULL（3）                    根据接口索引获取接口指针为空
*               TK_IF_ISNOT_MEMBERSHIPPORT（9）    接口不是成员端口
*               TK_LACP_NEGOTBL_NULL（12）         端口的LACP协商信息表为空
*               TK_TRUNKCB_NULL(10)                接口的Trunk控制块为空
*               TK_NOT_REGISTER                    31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetLacpNegoInfo(ULONG ulIfIndex, LACP_NEGO_INFO_S * pstNegoInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkSysPri
*  Description: 获取TRUNK系统优先级
*        Input: USHORT *pusSysPri: 保存输出系统优先级的内存指针
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-10    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkSysPri(USHORT *pusSysPri);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkSysPriById
* Date Created: 2010-10-13
*       Author: TanYiming(171953)
*  Description: 获取Trunk组的系统优先级
*        Input: ULONG ulTrunkId：Trunk组ID<0~31>
*               USHORT *pusSysPri：Trunk组的系统优先级<非空>
*       Output: USHORT *pusSysPri：Trunk组的系统优先级
*       Return: 成功：TK_OK
*               失败：返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-10-13   TanYiming(171953)  Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkSysPriById(ULONG ulTrunkId, USHORT *pusSysPri);
/*******************************************************************************
*    Func Name: TCPIP_TrunkDistributeHookRegister
*  Description: 
*        Input: TRUNK_DISTRIBUTE_HOOK_FUNC pfTrunkHookFunc:注册的分发策略函数指针 
*       Output: 
*       Return: TK_OK: 注册/解注册成功
*               TK_NOT_REGISTER  31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_TrunkDistributeHookRegister (TRUNK_DISTRIBUTE_HOOK_FUNC pfTrunkHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetMacAddressHook
*  Description: 用户注册获取系统mac和trunk mac的适配函数
*        Input: TRUNK_GETMACADDRRESS_HOOK_FUNC pfHookFunc: 函数指针
*       Output: 
*       Return: TK_OK:  注册成功
*               TK_ERR: 注册失败
*      Caution: 产品实现时将分配的physical地址Copy到pucMacAddr指向的内存，pucMacAddr指向的内存由VISP分配
*               由于各个Trunk接口都是直接与对端相连，因此Trunk的physical地址是否相同并不影响报文收发。
*               如果产品为系统MAC和各个Trunk接口分别分配不同的physical地址，那么在删除Trunk接口时要注意回收已分配的physical地址
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncGetMacAddressHook(TRUNK_GETMACADDRRESS_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncFreeMacAddressHook
*  Description: 用户注册释放TRUNK MAC的适配函数
*        Input: TRUNK_FREEMACADDRRESS_HOOK_FUNC pfHookFunc: 函数指针
*       Output: 
*       Return: TK_OK:  注册成功
*               TK_ERR: 注册失败
*      Caution: 释放VISP获取的physical地址
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncFreeMacAddressHook(TRUNK_FREEMACADDRRESS_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_JudgeTrunkIf
*  Description: 获取Trunk类型
*        Input: ULONG ulIfIndex: ifnet接口索引
*       Output: 
*       Return: TRUNK_ISTRUNK(0)       接口是Trunk接口
*               TRUNK_ISTRUNKPORT(1)   接口是成员端口
*               TRUNK_IFTYPEERR(2)     接口不存在或者是其它类型接口
*               TRUNK_IFNULL(3),       端口为空
*               TRUNK_INNERERR(4),     端口内部异常
*               TK_NOT_REGISTER        31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_JudgeTrunkIf(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetTrunkHADbg
*  Description: 设置trunk ha调试开关
*        Input: ULONG ulDbg: 开关状态 1-open;0-close
*       Output: 
*       Return: VOS_OK                 设置成功
*               VOS_ERR                设置失败
*               TK_NOT_REGISTER        31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_SetTrunkHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkHADbg
*  Description: 获取trunk ha调试开关
*        Input: ULONG* pulDbg: 保存输出的ha调试开关状态
*       Output: 
*       Return: VOS_OK:     获取成功
*               VOS_ERR:    获取失败(指针参数为空)
*               TK_NOT_REGISTER        31、trunk模块未注册
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkHADbg(ULONG* pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetTrunkBfdMode
*  Description: trunk或成员端口上创建单跳bfd会话时需要指定生效模式，只有满足生效模式的会话才可能UP
*        Input: ULONG ulTrunkIfIndex: trunk接口索引
*               ULONG ucValue: 生效模式 0,trunk上的单跳bfd会话生效;1-成员端口上的单跳bfd会话生效(默认trunk生效)
*       Output: 
*       Return: TK_OK: 设置成功
*               其他:  设置失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_SetTrunkBfdMode( ULONG ulTrunkIfIndex, UCHAR ucValue);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkBfdMode
*  Description: 获取trunk或成员端口上建立bfd会话的生效模式
*        Input: ULONG ulTrunkIfIndex: trunk索引
*               ULONG *pucValue: 保存输出值的指针
*       Output: 
*       Return: TK_OK: 获取成功
*               其他:  获取失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkBfdMode( ULONG ulTrunkIfIndex, UCHAR* pucValue);
/*******************************************************************************
*    Func Name: TCPIP_ShowTrunkInfo
*  Description: 显示trunk组信息
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID   TCPIP_ShowTrunkInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowTrunkStatistic
*  Description: 显示成员端口接口上trunk统计信息
*        Input: CHAR * pName: 接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID   TCPIP_ShowTrunkStatistic(CHAR * pName);
extern ULONG TCPIP_SetTrunkGateValue(ULONG ulTrunkId,ULONG ulGateValue);
extern ULONG TCPIP_GetTrunkGateValue(ULONG ulTrunkId,ULONG *pulGateValue);

/*******************************************************************************
*    Func Name: TCPIP_NotifyLacpStatus
* Date Created: 2008-11-21
*       Author: luowentong105073
*  Description: 接口板状态同步到主控板，适用于TGW应用场景
*        Input: ULONG ulIfIndex:要同步的接口索引
*               ULONG ulStatus:要同步的接口状态 LACP_UP 0/LACP_DOWN 1
*       Output: 
*       Return: TK_OK: 获取成功
*               其他:  错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-21   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_NotifyLacpStatus(ULONG ulIfIndex, ULONG ulStatus);

/*******************************************************************************
*    Func Name: TCPIP_TRUNK_Set_NegTimeoutWaring
* Date Created: 2009-02-28
*       Author: LiuYong/GeXianJun(57500/121208)
*  Description: 设置/取消首次协商不过对外告警功能
*        Input: ULONG ulTime:为0时表示取消协商不过对外告警功能
*                            非0表示设置协商不过对外告警功能，
*                            ulTime数值表示用户指定的协商时间
*       Output: 
*       Return: 成功: TK_OK;失败:返回错误码
*      Caution: ulTime必须为5的倍数,否则返回错误,最大为600s
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-28   LiuYong/GeXianJun(57500/121208)  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkNegTimeoutWaring(ULONG ulTime);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkNegTimeoutWaring
* Date Created: 2009-02-28
*       Author:  LiuYong/GeXianJun(57500/121208) 
*  Description:  获取首次协商不过对外告警时间
*        Input: ULONG *pulTime: 用户指定的协商时间
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-28    LiuYong/GeXianJun(57500/121208)    Create
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkNegTimeoutWaring(ULONG *pulTime);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkSysPri
* Date Created: 2009-5-11
*       Author: LY(57500)
*  Description: 设置系统优先级
*        Input: USHORT usSysPri: 0－65535，值越小优先级越高
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-5-11    LY(57500)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkSysPri(USHORT usSysPri);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkSysPriById
* Date Created: 2010-10-13
*       Author: TanYiming(171953)
*  Description: 根据TrunkID,设置Trunk组的系统优先级. 
*        Input: ULONG ulTrunkId：Trunk组ID<0~31>
*               USHORT usSysPri：要设置的系统优先级, 值越小优先级越高
*       Output:
*       Return: 成功：TK_OK
*               失败：返回错误码
*      Caution: 使用原有接口ULONG TCPIP_SetTrunkSysPri(USHORT usSysPri)，会修改所有的Trunk组的系统优先级
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-10-13   TanYiming(171953)  Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkSysPriById(ULONG ulTrunkId, USHORT usSysPri);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkPortPri
* Date Created: 2009-5-11
*       Author: LY(57500)
*  Description: 设置trunk端口的优先级，只对lacp协商的trunk端口才可配置
*        Input: ULONG ulIfIndex: 端口索引
*               USHORT usPri: 端口优先级
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-5-11    LY(57500)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkPortPri(ULONG ulIfIndex, USHORT usPri);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkPortPri
* Date Created: 2010-05-21
*       Author: zhangchi(00142640)
*      Purpose: 获取Trunk成员端口的优先级
*  Description: 
*        Input: ULONG ulIfIndex: 接口索引<非空>
*               USHORT *pusPri: 优先级指针<非空>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-21   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkPortPri(ULONG ulIfIndex, USHORT *pusPri);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkBackupMode
* Date Created: 2010-05-18
*       Author: zhangchi(00142640)
*      Purpose: 设置Trunk端口备份模式
*  Description: 
*        Input: ULONG ulTrunkId: Trunk组ID<0~31>
*               ULONG ulMode: 备份模式(0:普通模式，1: 1:1备份，2: M:N备份，默认0)<0~2>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 只能在创建Trunk组后加入成员端口前配置模式
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-18   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkBackupMode(ULONG ulTrunkId, ULONG ulMode);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkBackupMode
* Date Created: 2010-05-18
*       Author: zhangchi(00142640)
*      Purpose: 获取Trunk端口备份模式
*  Description: 
*        Input: ULONG ulTrunkId: Trunk组ID<0~31>
*               ULONG *pulMode: 获取备份模式指针<非空>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-18   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkBackupMode(ULONG ulTrunkId, ULONG *pulMode);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkMasterPort
* Date Created: 2010-05-18
*       Author: zhangchi(00142640)
*      Purpose: 设置TRUNK1:1端口备份模式的主端口
*  Description: 
*        Input: ULONG ulTrunkId: Trunk组ID<0~31>
*               ULONG ulIfIndex: 主端口接口索引<非空>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-18   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkMasterPort(ULONG ulTrunkId,ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkMasterPort
* Date Created: 2010-05-18
*       Author: zhangchi(00142640)
*      Purpose: 获取TRUNK1:1端口备份模式的主端口
*  Description: 
*        Input: ULONG ulTrunkId: Trunk组ID<0~31>
*               ULONG *pulIfIndex: 接口索引指针<非空>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-18   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkMasterPort(ULONG ulTrunkId,ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkActiveNum
* Date Created: 2010-05-18
*       Author: zhangchi(00142640)
*      Purpose: 设置TRUNK M:N端口备份模式的最大激活端口数
*  Description: 
*        Input: ULONG ulTrunkId: Trunk组ID<0~31>
*               ULONG ulActiveNum: 激活端口数(默认值:1)<1~8>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-18   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkActiveNum(ULONG ulTrunkId, ULONG ulActiveNum);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkActiveNum
* Date Created: 2010-05-18
*       Author: zhangchi(00142640)
*      Purpose: 获取TRUNK M:N端口备份模式的最大激活端口数
*  Description: 
*        Input: ULONG ulTrunkId: Trunk组ID<0~31>
*               ULONG *pulActiveNum: 端口数指针<非空>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-18   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkActiveNum(ULONG ulTrunkId, ULONG *pulActiveNum);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkRecoverMode
* Date Created: 2010-05-18
*       Author: zhangchi(00142640)
*      Purpose: 设置TRUNK端口备份恢复模式
*  Description: 
*        Input: ULONG ulTrunkId: Trunk组ID<0~31>
*               ULONG ulMode: 恢复模式(0:恢复模式，1:非恢复模式，默认0)<0~1>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 只能在创建Trunk组后加入成员端口前配置模式
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-18   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkRecoverMode(ULONG ulTrunkId, ULONG ulMode);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkRecoverMode
* Date Created: 2010-05-18
*       Author: zhangchi(00142640)
*      Purpose: 获取设置TRUNK端口备份恢复模式
*  Description: 
*        Input: ULONG ulTrunkId: Trunk组ID<0~31>
*               ULONG *pulMode: 获取恢复模式指针<非空>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-18   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkRecoverMode(ULONG ulTrunkId, ULONG *pulMode);

typedef ULONG (* TrunkLacpChangeNotify)(ULONG ulIfIndex, ULONG ulOper);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncNotifyLacpChangeHook
* Date Created: 2010-05-21
*       Author: zhangchi(00142640)
*      Purpose: 注册TRUNK LACP状态变化通知函数
*  Description: 
*        Input: TrunkLacpChangeNotify pfHookFunc: 钩子指针<非空>
*       Output: 
*       Return: 成功:TK_OK;失败:返回错误码
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-21   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNotifyLacpChangeHook(TrunkLacpChangeNotify pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_ShowTrunkPortInfo
* Date Created: 2010-05-25
*       Author: zhangchi(00142640)
*      Purpose: 显示Trunk成员端口的简要信息
*  Description: 
*        Input: CHAR *szIfName: 接口名<非空>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V1R8C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-25   zhangchi(00142640)      Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowTrunkPortInfo(CHAR *szIfName);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetLACPPortIDHook
* Date Created: 2010-06-22
*       Author: zengshaoyang62531
*  Description: 用户注册钩子函数，用来根据三维值获取Port Id
*        Input: TRUNK_GETLACPPORTID_HOOK_FUNC pfHookFunc:待注册钩子函数
*       Output: 
*       Return: VOS_OK
*      Caution: 此函数仅限在集中式三维接口模式下调用，否则返回错误!
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-22   zengshaoyang62531       Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetLACPPortIDHook(TRUNK_GETLACPPORTID_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkPortOriginalMac
* Date Created: 2011-06-27
*       Author: shuxieliu00176784/baiweiqiang00177000
*      Purpose: 获取TRUNK成员端口的原始physical地址
*  Description: 
*        Input: ULONG ulIfIndex: 成员端口IFNET索引
*               UCHAR* pucMac:   成员端口原始的physical地址，保证长度大于等于6字节
*       Output: UCHAR* pucMac:   成员端口原始的physical地址
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-27   shuxieliu00176784       Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkPortOriginalMac(ULONG ulIfIndex, UCHAR* pucMac);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkProductProcPolicy
* Date Created: 2011-06-28
*       Author: shuxieliu00176784/baiweiqiang00177000
*      Purpose: 设置产品的定制策略
*  Description: 
*        Input: ULONG ulTrunkId:  TRUNK Id号
*               ULONG ulPolicy:   TRUNK产品处理策略
*                                 取值: TRUNK_POLICY_DEFAULT_PROCESS     0 VISP默认处理方式 
*                                       TRUNK_POLICY_PROTMAC_NOTREFRESH  1 定制TRUNK组网优化功能策略
*
*       Output: 
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-27   shuxieliu00176784       Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkProductProcPolicy(ULONG ulTrunkId, ULONG ulPolicy);
/*******************************************************************************
*    Func Name: TCPIP_NotifyTrunkLacp
* Date Created: 2012-04-13
*       Author: z00208058/w00207740
*  Description: 处理NP的LACP Expired消息
*        Input: TRUNK_LACP_NOTIFY_S *pstData
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-04-13   z00208058/w00207740               Create
*
*******************************************************************************/
extern ULONG TCPIP_NotifyTrunkLacp(TRUNK_LACP_NOTIFY_S *pstData);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkPartnerMacChangeDropSwitch
* Date Created: 2012-11-06
*       Author: luogaowei 61496
*      Purpose: 设置对端系统MAC变化是否丢包的策略开关
*  Description: 
*        Input: ULONG ulSwitch:  设置对端系统MAC变化丢包开关(VRP_YES 1 :丢包  VRP_NO 0 :不丢包)
*       Output: 
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-06  luogaowei 61496       Create the first version.(TD-RNC 需求)
*  丢包条件:1、对端的系统MAC发生变化   && 2、本端处于非default 状态  && 3、本端处于UP状态
*  默认不丢包，丢包对带来协商时间长达6秒，问题由产品自行组网保证
*******************************************************************************/
extern ULONG TCPIP_SetTrunkPartnerMacChangeDropSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkPartnerMacChangeDropSwitch
* Date Created: 2012-11-06
*       Author: luogaowei 61496
*      Purpose: 获取对端系统MAC变化是否丢包的开关
*  Description: 
*        Input: 
*       Output: ULONG *pulSwitch:  设置对端系统MAC变化丢包开关(VRP_YES 1 :丢包  VRP_NO 0 :不丢包)
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-06  luogaowei 61496       Create the first version.(TD-RNC 需求)
*  丢包条件:1、对端的系统MAC发生变化   && 2、本端处于非default 状态  && 3、本端处于UP状态
*  默认不丢包，丢包对带来协商时间长达6秒，问题由产品自行组网保证
*******************************************************************************/
extern ULONG TCPIP_GetTrunkPartnerMacChangeDropSwitch(ULONG *pulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_NSR_TrunkSendMsg
* Date Created: 2013-04-10
*       Author: w00207740
*  Description: 对于Trunk在NSR其间产生的所有消息通过这个接口上报Trunk模块
*        Input: ULONG ulMsgType:
*               UCHAR ucpData:
*               ULONG ulLength:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-04-10   w00207740               Create
*
*******************************************************************************/
extern VOID TCPIP_NSR_TrunkSendMsg(ULONG ulMsgType, UCHAR *pucData, ULONG ulLength);

/*******************************************************************************
*    Func Name: TCPIP_NSR_SetCheckTrunkNsrFinishTimer
* Date Created: 2013-07-29
*       Author: w00207740
*  Description: 
*        Input: ULONG ulTime:0 -- 关闭定时器
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-07-29   w00207740               Create
*
*******************************************************************************/
extern ULONG TCPIP_NSR_SetCheckTrunkNsrFinishTimer(ULONG ulTime);

/*******************************************************************************
*    Func Name: TCPIP_NSR_TrunkPpiDownLoadHook
* Date Created: 2013-08-06
*       Author: w00207740
*  Description: 
*        Input: TRUNK_NSR_PPI_HOOK pstTrunkNspPpiHook:
*       Output: 
*       Return: 
*      Caution: 在协议栈
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-08-06   w00207740               Create
*
*******************************************************************************/
extern ULONG TCPIP_NSR_TrunkPpiDownLoadHook(TRUNK_NSR_PPI_HOOK pstTrunkNspPpiHook);

extern ULONG TCPIP_NSR_GetCheckTrunkNsrFinishTimer(ULONG *pulTime);

extern ULONG TCPIP_NSR_GetTrunkNsrGobalInfo(TRUNK_NSR_GLOBAL_INFO_S *pstTrunkNsrGlobalInfo);
extern ULONG TCPIP_NSR_EnableTrunkNsr(UCHAR ucEnable);

extern ULONG TCPIP_NSR_GetTrunkNsrLinkInfo(CHAR *pIfname, TRUNK_NSR_LINK_INFO_S *pstTrunkNsrLinkInfo);
/*******************************************************************************
*    Func Name: TCPIP_SetDropNoLacpPacketSwitch
* Date Created: 2014-01-10
*       Author: w00207740
*  Description: 配置非LACP报文丢弃
*        Input: ULONG ulSwitch: 0 - 关闭，不丢弃；1 - 开启，丢弃；默认为 0
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-01-10   w00207740               Create
*
*******************************************************************************/
extern ULONG  TCPIP_SetDropNoLacpPacketSwitch(ULONG ulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_GetDropNoLacpPacketSwitch
* Date Created: 2014-01-10
*       Author: w00207740
*  Description: 获取非LACP报文丢弃配置
*        Input: ULONG *pulSwitch:不可为空
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-01-10   w00207740               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetDropNoLacpPacketSwitch(ULONG *pulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_SetTrunkSystemMac
* Date Created: 2014-02-11
*       Author: w00207740
*  Description: 配置Trunk系统mac
*        Input: UCHAR *pucMac:
*       Output: 
*       Return: 
*      Caution: 对于VISP任务Trunk Systme Mac唯一，若对其进行动态修改，会导致链路闪断
*               为了避免不同设备特殊处理，请不要将系统MAC设置为全0或全F
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-11   w00207740               Create
*
*******************************************************************************/
ULONG TCPIP_SetTrunkSystemMac(UCHAR *pucMac);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkSystemMac
* Date Created: 2014-02-11
*       Author: w00207740
*  Description: 获取Trunk System Mac
*        Input: UCHAR *pucMac:
*       Output: 
*       Return: 
*      Caution: 输入指向空间的大小需要保证不小于6字节
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-11   w00207740               Create
*
*******************************************************************************/
ULONG TCPIP_GetTrunkSystemMac(UCHAR *pucMac);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkIdSystemMac
* Date Created: 2014-10-15
*       Author: z00208058
*  Description: 支持基于Trunk组配置系统MAC
*        Input: ULONG ulTrunkId:Trunk组Id
*               UCHAR *pucMac:返回的系统MAC(6个字节)
*       Output: 
*       Return: 成功:VOS_OK 失败:其他错误码
*      Caution: 在Trunk组创建后且在Trunk成员端口添加前；
*               如果在添加Trunk成员端口后修改系统MAC，NP模式下立即下发新模板给产品，根据对端的LACP报文进行重协商。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-15   z00208058               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkIdSystemMac(ULONG ulTrunkId, UCHAR *pucMac);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkIdSystemMac
* Date Created: 2014-10-15
*       Author: z00208058
*  Description: 支持基于Trunk组配置系统MAC
*        Input: ULONG ulTrunkId:Trunk组Id
*               UCHAR *pucMac:返回的系统MAC(6个字节)
*       Output: 
*       Return: 成功:VOS_OK 失败:其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-15   z00208058               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkIdSystemMac(ULONG ulTrunkId, UCHAR *pucMac);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_API_H_ */

