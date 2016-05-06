/*************************************************************************
 *
 *              Copyright 2006, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         VISP_IR_IFNET.H  
 *
 *  Project Code: VISP1.6
 *   Module Name: IFNET
 *  Date Created: 2006/11/16   
 *        Author: liuyong 57500
 *   Description: 这个头文件内容是从VISP IFNET相关的各个头文件抽取IR需要的宏和结构构成，
 *                在后续开发和维护时，需要关注同VISP保持同步!
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *
 ************************************************************************/
#ifndef _VISP_IR_IFNET_H_
#define _VISP_IR_IFNET_H_

#ifdef  __cplusplus
extern "C"{
#endif


/***************  from if_type.h ******************/
/* 通知函数链类型码 */
#define IFC_LINKMSG_NOTIFY  0       /* 链路层消息通知类型 */
#define IFC_DEVMSG_NOTIFY   1       /* 底层消息通知类型 */ 
#define IFC_ADDIF_NOTIFY    2       /* 接口创建通知类型 */
#define IFC_ADDSUBIF_NOTIFY 3       /* 子接口创建通知类型 */
#define IFC_DELIF_NOTIFY    4       /* 接口删除通知类型 */
#define IFC_SHUTIF_NOTIFY   5       /* 接口shutdown通知类型 */


/***************  from if_def.h ******************/
#define IFQUEUELENGTH                   75
#define IFMSG_QUEUE_MAX_LENGTH          0x1000          /* Max Length of IfMsg Queue */
#define MAX_IF_TYPE_LENGTH              20              /* 接口类型名称长度 */
#define MAX_IF_NAME_LENGTH              47              /* 接口名长度 */
#define MAX_IF_NAME_REAL_LENGTH         27              /* 实际可能的接口名最大长度,
                                                           如: GigabitEthernet15/1/15.1023*/
#define VRP_MAX_INTERFACE_TYPE      20
#define MAX_IF_NUMBER_LENGTH        27 
#define VRP_IFNET_IFINDEXNUM        128             /* 最大索引号 */        /* if_index.c */

/* IFNET模块用户API错误码 */
enum enIfnetErrInfo
{
    VRP_IFNET_NOERR = 0,                /* 0 if_index.c */
    VRP_IFNET_ENOMEM,                   /* 1 if_index.c */
    VRP_IFNET_EINDEXCHAOS,              /* 2 if_index.c */
    VRP_IFNET_ECANOTSPLIMP ,            /* 3 if_index.c */
    VRP_IFNET_ENOSUCHIF,                /* 4 接口不存在 */
    VRP_IFNET_GENERR,                   /* 5 ifnet模块通用错误 */
    VRP_IFNET_EINDEXNOTINIT,            /* 6 当前无索引 */
    VRP_IFNET_CANOTDELVT,               /* 7 can't delete VT*/
    VRP_IFNET_CANOTDELVE,               /* 8 can't delete VE*/
    VRP_IFNET_HAVE_BEEN_DOWN,           /* 9 接口已经被shutdown*/
    VRP_IFNET_NO_HAVE_BEEN_DOWN,        /* 10 接口没有被shutdown*/
    VPR_IFNET_KEEPALIVE_VALUE_TOOBIG,   /* 11 KEEPALIVE 值太大*/
    VRP_IFNET_DESC_TOO_LONG,            /* 12 接口描述太长*/
    VRP_IFNET_CANOT_BE_SHUTDOWN,        /* 13 接口不可被关闭,added for SWFD04676,20041228*/

    VRP_IFNET_NULLPOINTER,              /* 14 输入参数指针为空 */
    VRP_IFNET_MTU_INVALID,              /* 15 用户配置的MTU值不在允许范围之内 */
    VRP_IFNET_REGISTERPRI_ERR,          /* 16 注册的通知优先级错误 */
    VRP_IFNET_REGISTERTYPE_ERR,         /* 17 注册类型不支持 */
    VRP_IFNET_HA_IS_SMOOTHING,          /* 18 HA正在平滑处理或手动倒换处理*/
    VRP_IFNET_PORT_CANOT_BE_SHUTDOWN,   /* 19 成员端口所属的Trunk接口被Shutdown, 因此不能对该成员端口进行NoShutdown */
    VRP_IFNET_CANOTDELVTBINDED,         /* 20 不能删除已经绑定到以太接口的VT接口 */
    VRP_IFNET_ISTRUNKPORT,              /* 21 接口是trunk成员端口 */
    VRP_IFNET_IFNAMEERROR,              /* 22 接口名字错误 */
    VRP_IFNET_GETTRUNKIFFAILED,         /* 23 根据成员端口获取trunk接口失败 */
    VRP_IFNET_TRUNKIFNULL,              /* 24 根据成员端口获取trunk接口失败 */
    VRP_IFNET_WAITLISTEND,              /* 25 链表完，waitlist访问结束 */
    VRP_WAITLIST_OPEN_FAILED,           /* 26 注册waitlist失败 */
    VRP_WAITLIST_SET_FAILED,            /* 27 设置waitlist关键数据失败 */
    VRP_WAITLIST_GET_FAILED,            /* 28 获取waitlist关键数据失败 */
    VRP_WAITLIST_CLOSE_FAILED,          /* 29 关闭waitlist失败 */
    VRP_IFNET_EENQUEUE,                 /* 30 Fail to put mbuf into link queue */
    VRP_IFNET_EWRITEQUEUE,              /* 31 Fail to write ioctl msg */

    /* 由l00105073修改，问题单A82D20097:ifnet模块错误码唯一性整改 */    
    VRP_IFNET_TYPEERR,                  /* 32 ifnet的类型不匹配*/
    VRP_IFNET_ISNOTTRUNK,               /* 33 ifnet的类型不是TRUNK(当需要的是TRUNK时)*/
    VRP_IFNET_TRUNKVTBLNULL,            /* 34 TRUNK虚函数表指针为空*/
    VRP_IFNET_TRUNKHAVEPORT,            /* 35 TRUNK已经存在端口*/
    /* 由l00105073修改，问题单A82D20097:ifnet模块错误码唯一性整改 */
    
    /* 由l52889修改，问题单A82D20371:IF_DeleteMpgroupIf函数错误码有问题 */
    VRP_IFNET_MPVTBLNULL,               /* 36 MP组件虚表为空 */
    VRP_IFNET_MPHAVESON,                /* 37 MP下有子接口 */
    
    VRP_IFNET_ISDIALER,                 /* 38 接口是Dialer接口，不能用pfIf_delete删除 */
    VRP_IFNET_CANOT_ISIS,               /* 39 该接口不能使能去使能ISIS */
    VRP_IFNET_IOCTLERR,                 /* 40 控制命令字下发/上送失败 */
    VRP_IFNET_GETL3STATE,               /* 41 */
    VRP_IFNET_NOLCPINFO,                /* 42 */
    VRP_IFNET_NOFSM,                    /* 43 */
    VRP_IFNET_COPYCBINFO,               /* 44 */
    VRP_IFNET_NOIPCPINFO,               /* 45 */
    VRP_IFNET_NOIPCPFSM,                /* 46 */
    VRP_IFNET_PARA_INVALID,             /* 47 配置参数越界 */  
    VRP_IFNET_DIMENSION_MULTI,          /* 48 接口一二维信息多次配置 */  
    VRP_IFNET_IS_3D_VIRTUAL,            /* 49 三维虚拟接口 */
    VRP_IFNET_NOT_3D_MODE,              /* 50 */
    VRP_IFNET_CREATEFAIL,               /* 51 */
    VRP_IFNET_SELF_BOARD,               /* 52 三维本板接口 */
    VRP_IFNET_VISP_NOT_INIT_DONE,       /* 53 协议栈未完全启动前不能接收报文 */
    VRP_IFNET_IS_3D_MODE,               /* 54 3D模式 */ 
    VRP_IFNET_DOWNORSHUTDOWN,           /* 55 接口Down或者被shutdown */
    VRP_IFNET_DEL_IF_FAIL,              /* 56 删除接口失败 */ 
    VRP_IFNET_IS_L2IF,                  /* 57 L2IF接口 */
    VRP_IFNET_L2IFVTBLNULL,             /* 58 L2IF虚函数表指针为空*/
    /*Add for BC3D00792,DR.131获取链路层状态 start*/
    VRP_IFNET_IPOA_NOINIT,              /* 59 IPOA模块未使用 */ 
    VRP_IFNET_IPOA_ERR,                 /* 60 IPOA模块API处理失败 */ 
    VRP_IFNET_ETH_NOINIT,               /* 61 Eth模块未使用*/ 
    VRP_IFNET_ETH_ERR,                  /* 62 Eth模块API处理失败 */ 
    /*Add for BC3D00792,DR.131获取链路层状态 end*/
    VRP_IFNET_PPIGETMTU_ERR,            /* 63 向底层查询最大MTU错误 */
    VRP_IFNET_L2TRUNKPHYTRANSMIT_NULL,  /* 64 二层TRUNK的物理层报文发送函数为空 */
    VRP_IFNET_VRF_ERR,                  /* 65 VRF模块API处理失败 */ 
    VRP_IFNET_VRF_NOT_INIT,             /* 66 VRF模块未初始化 */ 

    VRP_IFNET_NOIP6CPFSM,               /* 67 IP6CP状态机不存在*/
    VRP_IFNET_NO_DEVLINK,               /* 68 不存在对应的DEVLINK物理结点，同步自V1R7C01 */
    VRP_IFNET_KEEPALIVE,                /* 69 PPP接口没有完成保活处理,处于保活状态 */ 
    VRP_IFNET_UNRECGPHYIF,              /* 70 接口不是VISP支持的物理接口类型，同步自V1R6C05 */
    VRP_IFNET_NULL_PPPLINK,             /* 71 PPP接口链路层指针为空 */    
    VRP_IFNET_NULL_ETHLINK,             /* 72 Eth接口链路层指针为空 */
    VRP_IFNET_ERRLINETYPE,              /* 73 接口类型非Eth/PPP链路类型 */
    VRP_IFNET_NULL_PPI,                 /* 74产品注册ifnet PPI为空*/
    VRP_IFNET_NOTIFY_PPI_ERR,           /* 75下发PPI错误*/
    VRP_IFNET_MALLOC_FAIL,              /* 76申请内存失败*/
    VRP_IFNET_TUNNEL_INFO_NULL,         /* 77tunnel配置为空*/

    VRP_IFNET_MAXERR                    /* 枚举值上限，无实意，新增枚举值必在其前添加 */
};


#define IF_SEARCH_ALL                   0x0FFF  /* 搜索所有 */
#define IF_SEARCH_TEMPIF                0x1000  /* 搜索包括临时接口 */

#define IF_RTATTR_BROADCAST             0x2
#define IF_RTATTR_NBMA                  0X4
#define IF_RTATTR_LOOPBACK              0x8
#define IF_RTATTR_POINT2POINT           0x10
#define IF_RTATTR_MULTICAST             0x8000

#define IF_STATUS_PROT_DOWN             0x1
#define IF_STATUS_LOW_DOWN              0x2
#define IF_STATUS_PROT_UP               0x4
#define IF_STATUS_PROT6_DOWN            0x8   /*表示IPv6 line protocol 处于DOWN的状态*/
#define IF_STATUS_PROT6_UP              0x10  /*表示IPv6 line protocol 处于UP的状态*/

/*******************   from iifnet_inc.h  *********************************/
#define IF_MAX_INTERFACE_NAME_LEN                 47       /* 最大的接口名长度 */ 
#define MAX_IFCMD_NAME_LEN                     47
#define MAX_INTERFACE_SIMPLENAME_LEN           20       /* 最大的简单接口名长度 */ 
#define MAX_INTERFACE_DESCRIPTION_LEN          80       /* 描述最大长度 */
#define IF_MAX_INDEX                           100000   /* 最大的接口数目 */   
#define IF_MAX_MAC_LEN                         6

/***********************************************************************/
/*usIfState value: 必须设置正确*/
#define  IF_UP                 0x01
#define  IF_DOWN               0x02
#define  IF_SETMAC             0x04
#define  IF_UNBIND             0x08
#define  IF_STATES             IF_UP | IF_DOWN

/******************  from if_vlink.h  ************/
#define RTM_CREATE  0x01    /* 接口、虚链路创建 */
#define RTM_DEL     0x02    /* 接口、虚链路删除*/
#define RTM_STATE   0x04    /* 接口、虚链路的usIfStste 或 usIfFlags 发生改变*/
#define RTM_CONFIG  0x08    /* 接口、虚链路的参数信息sIfData发生改变*/
#define RTM_BOARDREMOVE 0x10
#define RTM_NEWADDRESS  0x20    /* IP层汇报本地接口的地址*/
#define RTM_DELADDRESS  0x40    /*IP层删除本地接口的地址*/
#define RTM_DELVLINK    0x80    /*删除VLINK*/

#define	IF_SEARCH_CONFIG_CHAIN  1000


 typedef struct  tagIFConfigVlink
{
    USHORT  usIfDelay;
    USHORT  usIfReliability;
    USHORT  usIfLoad;
    UCHAR   ucPadding[2]; 
    ULONG   ulIfBandwidth;
    ULONG   ulIfBaudrate;
    ULONG   ulIfMtu;
    ULONG   ulConfIfDelay;
    ULONG   ulConfIfBandwidth;
    ULONG   ulData;    
    /*x36530 syn D030 20050317*/
    ULONG   ulIfBandwidthHigh;
    ULONG   ulIfBaudrateHigh;

} IFCONFIGVLINK_S;

typedef struct tagIfVLINKentry6
{
    ULONG   ulIntfIndex;            /*接口唯一索引值*/
    ULONG   ulVlinkIndex;           /*虚链路索引值，接口事件时置为0*/
    ULONG   aulPeerAddr[4];         /*对端地址，创建虚链路时必须有对端地址*/
    ULONG   ulMacAddrLen;
    USHORT  usSlot;                 /*接口所在槽号， new in 3.0 */
    USHORT  usMsgType;              /*见下面定义*/
    USHORT  usIfState;              /*接口状态*/
    USHORT  usIfFlags;              /* 接口标志*/
    USHORT  usIfType;               /*  接口类型*/
    UCHAR   ucPadding_1[2]; 
    IFCONFIGVLINK_S  stIfData;           /*接口参数*/
    UCHAR   ucMacAddr[IF_MAX_MAC_LEN];
    UCHAR   ucPadding_2[2];
    CHAR    cIfName[IF_MAX_INTERFACE_NAME_LEN + 1];   /*接口名称*/
    ULONG   ulVrfIndex;
}IFVLINKENTRY6_S;

#define RTM_CREATE  0x01
#define RTM_DEL     0x02    

#define VLINK6_TABLELINE_EMPTY  0
#define VLINK6_TABLELINE_USED   1

typedef struct tagVLINK6TABLE
{
    ULONG  ulPrevFreeIndex;     /*previous free struct*/
    ULONG  ulNextFreeIndex;     /*next free struct*/
    ULONG  ulPrevUsedIndex;     /*previous used struct*/
    ULONG  ulNextUsedIndex;     /*next used struct*/
    ULONG  ulIfIndex;           /* the IFNET index map belong to*/
    ULONG  ulUsedFlag;          /*if the struct inused 0-empty 1-used*/
    ULONG  ulSynCount;          /*syn count */
    IFVLINKENTRY6_S tLastStatus ;   /* save last change status */
    VOID*  pCB;                 /*Control Block of VLINK */
}VLINK6TABLE_S;

typedef struct tagIF_WAITLIST_PARAM
{
    UINTPTR   ulWaitListHandle;       /* WAITLIST句柄 */
    ULONG     ulSearchType ;          /* 搜索类型 */
    VOID      *pSearch ;                      /* 入口指针 */
}IF_WAITLIST_PARAM ;

/******************   from  if_def.h   *************/

/**********************************************************
*  在此定义ioctl函数的case项,注意不能与syst_pub.h中的
*  命令项 DRV_TEST_ENTRY 重合,测试命令进入各个驱动的总入口
\*********************************************************/
enum  enumPhyIoCtl
{
    PHY_POWERUP = 0,
    PHY_INIT,
    PHY_SHUTDOWN,
    PHY_NO_SHUT,
    PHY_ENABLERECV,
    PHY_DISABLERECV,
    PHY_CHECKFLOW,
    PHY_BUILDRUN,
    PHY_CHECK,
    PHY_DELETE,
    PHY_SETMACADDR,
    PHY_SETMACTABLE,
    PHY_GETMACADDR,
    PHY_MAP,
    PHY_PROTOCOL_CHG,
    PHY_GETINFO,
    PHY_GETSTATISTIC,
    PHY_CLEAR_PORT,
    PHY_GETMAXBD,
    PHY_SETLEASED,
    PHY_ISPURE_SYNC,
    PHY_ISASYNC,
    PHY_ISSOFTCVT,
    PHY_ATMMCLK,
    PHY_ATMMSERV,
    PHY_ATMMOAMPVC,
    PHY_ATMMOAMRETRY,
    PHY_ATMAPVC,
    PHY_ATMDPVC,
    PHY_ATMINIT,
    PVC_STA_CHANGE,

    PHY_IMA_SETLINKNUM,
    PHY_CLI_ATMIMA_GETFRAMELENGTH,

    PHY_ATMGETPVCINFO,
    PHY_LINK_DOWN,
    /*added by liuhui, for PPPoE Client, to notify PPPoE Client Link down*/
    PHY_POECLIENT_LINK_DOWN_WITHPADT,
    PHY_POECLIENT_LINK_DOWN_NOPADT,
    /*add ends*/
    PHY_GETMIBINFO,
    PHY_SETPROMODE,
    PHY_SETRCVADDRSTATUS,
    PHY_ISUP,       /* 判断底层是否UP 2001-03-26 */
    PHY_SETACCM,  /* Notify low layer ACCM */
    PHY_GET_HARD_INFO, /* for D10708 */
    PHY_GETASYNMODE,
    PHY_ENABLE,
    PHY_DISABLE,
    PHY_INIT_BUFFER,
    PHY_GET_VER,
    PHY_GETPHYSTATUS,
    PHY_DEBUG,
    PHY_SETLOOPBACK,
    PHY_E1DELETE,
    PHY_LINECODE,
    PHY_FRAMING,
    PHY_LINECLOCK,
    PHY_E1BUILDRUN,
    PHY_BOARD_RESET,
    PHY_E1CHECKSTAT,
    PHY_T1DELETE,
    PHY_T1BUILDRUN,
    PHY_T1CHECKSTAT,
    PHY_CHANNEL_SPEED,
    PHY_T1_CABLE,
    PHY_READREG,
    PHY_WRITEREG,
    PHY_SETPORT
    ,
    PHY_ADDLINK,
    PHY_DELELELINK,
    PHY_CANDELELTE,
    PHY_LOOPBACK_STATE,
    
    PHY_IPV6_ADD_MCAST_ADDR,
    PHY_IPV6_DEL_MCAST_ADDR,

    /*This 2 value were moved here by ZhuKun 36377,20040827,For D00575*/
    PHY_JOINMULTI,
    PHY_LEAVEMULTI,
    
    PHY_GET_ROUTFLAG,

    PHY_GETDOWNMODE,

    PHY_ADD_VRRP_VIRTUAL_MAC,   /* 添加VRRP虚拟MAC */
    PHY_DEL_VRRP_VIRTUAL_MAC,   /* 删除VRRP虚拟MAC */
    PHY_ENABLE_VRRP,   

    PHY_LCPECHOOPEN,
    PHY_LCPECHODOWN,
    PHY_LCPECHOSETCONF,    

    PHY_GETINTFSTATUS,
    PHY_GETINTFTYPE,

    PHY_MAX_PHYWORD  /*No use actually.Just for adding enum word easily. ZhuKun,20041020*/
};

/* 接口物理属性 */
enum enumPhyType
{
    PHY_ETHERNET=1,
    PHY_SYNC,
    PHY_ASYNC,
    PHY_ISDN,
    PHY_DIALER,
    PHY_LOOP,
    PHY_E1,
    PHY_BRI,
    PHY_PRI,
    PHY_BCHAN,
    PHY_TEMPLATE,
    PHY_TEMPLATECHAN,
    PHY_TEMPLATEMPCHAN,
    PHY_VPN_TUNNEL,
    PHY_TUNNEL,
    PHY_ATM,
    PHY_ATMCHAN,
    PHY_ATM_NOTSURE,
    PHY_CONSOLE,
    PHY_POS,
    PHY_VIRTUAL_ETHERNET,
    PHY_GE,
    PHY_GROUPE1,
    PHY_AUX,
    PHY_NULL,
    PHY_LOOPBACK,
    PHY_VIRTUAL_ACCESSS,
    PHY_MP_GROUP,
    PHY_VLAN,
    PHY_DPT,
    PHY_ETH_TRUNK,
    PHY_IP_TRUNK,
    PHY_METH,
    PHY_MTUNNEL,     /* 代码同步, 增加新类型. z36377, 2004/09/18 */
    PHY_VI,          /*VI接口*/
    PHY_UI,          /*UI接口*/
    PHY_MAX
};

/* 物理层类型 */
enum enumPortType
{
    PORT_ETHERNET=1,
    PORT_SYNC,
    PORT_ASYNC,
    PORT_BRI,
    PORT_E1,
    PORT_T1,
    PORT_E3,
    PORT_T3,
    PORT_CPOS,
    PORT_DIALER,
    PORT_LOOP,
    PORT_TEMPLATE,
    PORT_TEMPLATECHAN,
    PORT_TEMPLATEMPCHAN,
    PORT_VPN_TUNNEL,
    PORT_TUNNEL,
    PORT_ATM,
    PORT_ATMCHAN,
    PORT_FASTETHERNET,
    PORT_CONSOLE,
    PORT_VIRTUAL_ETHERNET,
    PORT_POS ,
    PORT_GE ,
    PORT_GROUPE1,
    PORT_AUX,
    PORT_NULL,
    PORT_VIRTUAL_ACCESSS,
    PORT_MP_GROUP,
    PORT_VLAN,
    PORT_DPT,
    PORT_ETH_TRUNK,
    PORT_IP_TRUNK,
    PORT_METH,
    PORT_MTUNNEL,   /* 代码同步, 增加新类型. z36377, 2004/09/18 */
    PORT_VI,     /*VI 接口*/
    PORT_UI,     /*UI 接口*/
    PORT_MAX
};

/* 网络层 to 链路层 */
enum enumUpToLink
{
    SIOCAIPADDR=0 ,
    SIOCDIPADDR ,
    SIOCMIPADDR ,
    SIOCHENCAP ,        /* 去封装 */
    SIOCSDOWN ,
    SIOCSUP ,
    SIOCSNETPROTO,
    SIOCHNETPROTO,
    SIOCBUILDENCAP ,
    SIOCGETINFO ,
    SIOCADDTODIALER ,
    SIOCDELFROMDIALER ,
    SIOCSIPFRAMETYPE ,
    SIOCSIPXFRAMETYPE ,
    SIOCGIPXFRAMETYPE ,
    SIOCHIPXFRAMEIF ,
    SIOCGIPXFRAMEIF ,
    SIOCSIPXFRAMEIF ,
    SIOCGIPXNODE ,
    SIOCSDELETEIF ,
    SIOCGADDRIF,
    SIOCLINKSTATE ,
    SIOCHNEGOTIATE,
    SIOCSNEGOTIATE,
    SIOCHUNNUMBER,
    SIOCSUNNUMBER,
    SIOCENCAPSUB,       /* 封装子接口 */
    SIOCMMTU,           /*通知链路层 mtu 改变*/
    SIOCKEEPALIVE,      /*通知链路层 keepalive 改变*/
    SIOCGETMAC, 
    SIOCLINKSMOOTH,
    SIOCVLAN,
    SIOCAIPISIS,
    SIOCDIPISIS,
    SIOCIPADDRINVALID,
    /* 提供一个命令字，只是刷新BuildRun信息，但是不通知链路层。*/
    /* 根据问题单D1370 用于从地址的添加 2002/01/11 Chenwejun */
    /* 由于删除和增加从地址都要使用，所以修改名字 2002/01/22 */
    SIOCPROADDRSEC,
    SIOCDADDRSEC,  /* 删除从地址, 通知Eth删除ARP表项. Added by z36377 for SWFD12089 sys VRPD038,20050715*/
    SIOCAIP6LINKLOCALADDR,
    SIOCAIP6GLOBALADDR,
    SIOCAIP6SITELOCALADDR,    /*增加 IPv6地址*/
    SIOCDIP6LINKLOCALADDR,
    SIOCDIP6GLOBALADDR,
    SIOCDIP6SITELOCALADDR,     /*删除 IPv6地址*/
    SIOC6LINKSTATE,            /*得到ipv6 line protocol 的状态*/
    SIOC6GETINFO,              /*得到链路层信息*/
    SIOC6GETINTERFACEID,       /*得到接口ID*/
    SIOCJOINMULTI,  /*add by luohanjun*/
    SIOCLEAVEMULTI,
    SIOCISISENABLE,    /*向链路层获取ISIS开关*/

    SIOCMADDRSEC,  /* 修改从地址掩码长度, Added by l143205 for BC3D00874, 2008-12-9 */
    SIOC_MAX_SIOCWORD1 /*No use actually.Just for adding enum word easily. ZhuKun,20041020*/
};

/* 链路层类型 */
enum enumLineProtocol
{
    LINE_ETHERNET = 1,
    LINE_ATM,
    LINE_PPP,
    LINE_SLIP,
    LINE_CISCO_HDLC,
    LINE_FR,
    LINE_X25,
    LINE_X25_BFE,
    LINE_X25_DCE,
    LINE_X25_DDN,
    LINE_X25_DTE,
    LINE_X25_IETF,
    LINE_X25_DTE_BFE,
    LINE_X25_DTE_DDN,
    LINE_X25_DCE_DDN,
    LINE_X25_DTE_IETF,
    LINE_X25_DCE_IETF,
    LINE_LAPB,
    LINE_LAPB_DTE,
    LINE_LAPB_DCE,
    LINE_LAPB_DTE_IP,
    LINE_LAPB_DCE_IP,
    LINE_LOOP,
    LINE_NULL,
    LINE_LOOPBACK,
    LINE_SHOW,
    LINE_TEMPLATE,
    LINE_VPN_TUNNEL,
    LINE_TUNNEL,
    LINE_CONSOLE,
    LINE_VIRTUAL_ETHERNET,
    LINE_GE,
    LINE_MTUNNEL,   /* 代码同步, 增加新类型. z36377, 2004/09/18 */
    LINE_UI,
    LINE_VLAN,
    LINE_OTHER_TYPE = 0xFFFF
};

/* 底层上报信息 */
enum enumLowToUp
{
    ISLUP=0 ,
    ISLDOWN , /*底层上报本端接口DOWN消息*/
    ISLCHGBAUD ,
    ISLASYTOSYN ,
    ISLSYNTOASY ,
    ISLSHUTDOWN ,
    ISLNOSHUT,
    ISLDELETE,
    ISLCHGPROTOCOL,
    ISLGETPROTOCOL,
    ISLSETMAC,
    ISLSPEED,               /*D18794*/
    ISLATMOAMSTATE,     /* 2001/02/22 sunshengtao */
     
     /* ,ISLJOINMULTI, */ /*add by luohanjun*/
     /* ISLLEAVEMULTI */
     
    ISLDOWNALL,   /*(仅用于PPP接口)底层上报本端PPP接口DOWN消息,并通知对端PPP接口也DOWN*/ 
    ISLDUPLEX,    /* visvp1r7c03,l2if ADD, 底层上报双工模式 */

    /* OAM-3ah上报的状态 */
    ISLEFMNORMAL,
    ISLEFMUP,
    ISLEFMDOWN,
    
    ISMAX_END     
};

/* 链路层 to 网络层 */
enum enumLinkToUp
{
    SIOCIFUP=0 ,
    SIOCIFDOWN ,
    SIOCGIPADDR ,
    SIOCGIPMASK ,
    SIOCGIF ,
    SIOCADDR ,
    SIOCGADDR ,
    SIOCCALLBACK ,
    SIOCIFUPSPOOFING ,
    SIOCIFDOWNSPOOFING ,
    SIOCDNEGOADDR ,
    SIOCIFMTU ,
    SIOCSIPFLAGS ,
    SIOCCIPFLAGS,
    SIOCSECONDIFUP,
    SIOCFIRSTDOWN,
    SIOCSHOW,
    SIOCHOT,
    SIOCDELVLINK,   /* 删除接口板VLINK */
    SIOCDDRCALLIN,
    SIOCDDRNAME,
    SIOCDDRIF,
    SIOCDDRIFUP,
    SIOCOSIENABLE,
    SIOCRCVMAC,
    /*add by huzhiyong 新增两个PPP与DDR之间的接口命令字2002/01/24*/
    SIOCDDRIFDOWN,
    SIOCDDRLOWERDOWN,

    SIOCNDDAD,  /*ND DAD检测*/
    SIOCGIP6LINKLOCALADDR, /* get link-local address */
    SIOCSIP6INTERFACEID, /* notify interface id changed */

    SIOCMSPEED            /*IFNET通知通知网络层baudrate的变化*/
    /* Added by Mayun for VRPv5 MPLS TE */
    ,SIOCMPLSTEB,       /* the event type for notifying resource information of MPLS TE interface */
    SIOCMPLSTEATTR     /* the event type for notifying IGP SHORT-CUT and FORWARDING information */

    ,SIOCCREATEIF, /*add by luohanjun*/
    SIOCDELETEIF,
    SIOCIFIPC,          /*IPC传送标志，强制要求传送到主控板进行处理*/

    /*以上为锁定区域，请勿修改，只能从本行后增加命令字  add by luohanjun*/
    SIOCIFOTHER,

    SIOCLACPUP,   /* LACP UP */
    SIOCLACPDOWN, /* LACP DOWN */

    SIOC_MAX_SIOCWORD2 /*No use actually.Just for adding enum word easily. ZhuKun,20041020*/
};

enum enumRouterMsg
{
    Help_Router_Async=0,
    Help_Router_Atm,
    Help_Router_Aux,
    Help_Router_Bri ,
    Help_Router_Console,
    Help_Router_Dialer ,
    Help_Router_E1 ,
    Help_Router_Ethernet ,
    Help_Router_GE ,
    Help_Router_FastEthernet ,
    Help_Router_Loop,
    Help_Router_E1Group,
    Help_Router_Serial ,
    Help_Router_Pos ,
    Help_Router_Tunnel ,
    Help_Router_VpnTunnel ,
    Help_Router_VirtualTemplate ,
    Help_Router_MP_Group,
    Help_Router_VirtualEthernet,
    Help_Router_Null,
    Help_Router_LoopBack,
    Help_Router_AsyncIndex ,
    Help_Router_AtmIndex ,
    Help_Router_AuxIndex ,
    Help_Router_BriIndex ,
    Help_Router_DialerIndex ,
    Help_Router_E1Index ,
    Help_Router_EthernetIndex ,
    Help_Router_GEIndex ,
    Help_Router_FastEthernetIndex ,
    Help_Router_LoopIndex,
    Help_Router_E1GroupIndex ,
    Help_Router_SerialIndex ,
    Help_Router_PosIndex ,
    Help_Router_TunnelIndex ,
    Help_Router_VpnTunnelIndex ,
    Help_Router_VirtualTemplateIndex ,
    Help_Router_MP_GroupIndex,
    Help_Router_VirtualEthernetIndex,
    Help_Router_NullIndex,
    Help_Router_LoopBackIndex,
    Help_Router_SubInterface,
    Help_Router_Slot,
    Help_Router_Adaptor,
    Help_Router_InterfaceNum,
    Help_Router_Return,
    Help_Router_Colon,
    Help_Router_Point,
    Help_Router_Diagnol,
    Err_Router_NotCreate,
    Err_Router_QueueLen,
    Err_Router_UnknownQueue,
    Err_Router_MemoryStart,
    Err_Router_MemoryEnd,
    Err_Router_MemoryBeyond,
    Err_Router_ModemCantBeZero,
    Err_Router_ChannelGroup,
    Err_Router_ChannelISDN,
    Err_Router_CanNotDeleteInterface,
    Err_Router_CanNotDeleteInterface1,
    Err_Router_InDeletedInterface,
    Err_Router_CreateDeletedInterface,
    Err_Router_CanNotCreateAccress,
    Err_Router_TemplateNotEmpty,
    Help_Router_InterfaceDeleted,
    Help_Router_InterfaceRemoved,
    Help_Router_Hardware,
    Help_Router_Physical,
    Help_Router_BaudRate,
    Help_Router_Physical1,
    Help_Router_PhysicalLayer,
    Help_Router_PhysicalLayer1,
    Help_Router_Cable,
    Help_Router_Internet1,
    Help_Router_Internet2,
    Help_Router_Counter,
    Help_Router_Counter1,
    Help_Router_Ethernet2,
    Help_Router_Ethernet1,
    Help_Router_NoCable,
    Help_Router_HardTemplate,
    Help_Router_HardTemplateAccess,
    Help_Router_HardTemplateAccessMP,
    Help_Router_HardUnknown,
    Help_Router_LinkStatus,
    Help_Router_MTU,
    Help_Router_MoreThanDChannel,
    Help_Router_CanNotBackupSelf,
    Help_Router_CanNotBackupDialer,
    Help_Router_CanNotBackupSub,
    Help_Router_CanNotUseSubBackup,
    Help_Router_CanNotBackupTwoPort,
    Help_Router_CanNotMainPortBackup,
    Help_Router_CanNotBackupBackupInterface,
    Help_Router_MainIsInRotoryGroup,
    Help_Router_BackupIsInRotoryGroup,
    Help_Router_EnableDelay,
    Help_Router_DisableDelay,
    Err_Router_NotSupport,
    Help_Router_ShowBackup,
    Help_Router_Queue,
    Help_Router_TimeSlots,
    Help_Router_ShowInterfaceQueue,
    Help_Router_ShowProtocolQueue,
    Help_Router_ShowQueue,
    Help_Router_QueueLen,
    Help_Router_SetInterfaceQueLen,
    Help_Router_MemoryStart,
    Help_Router_MemoryEnd,
    Help_Router_ShowController,
    Help_Router_Balanced,
    Help_Router_Unbalanced,
    Help_Router_BriChan,
    Help_Router_PriChan,
    Help_Router_VirtualAccess,
    Help_Router_InterfaceDisabled,
    Help_Router_InterfaceHasDeleted,
    Help_Router_Loopback,
    Help_Router_Admin,
    Help_Router_Removed,
    Help_Router_E1AlreadyBeenShutdown,
    Help_Router_E1ShutDown,
    Help_Router_E1NoBeenShutdown,
    Help_Router_E1IsReset,
    Help_Router_TimeSlot,
    Err_TooManyParam ,
    Err_InvalidParam ,
    Err_IncompleteCmd ,
    Err_NoSuchInter ,
    Err_IncorrectCmd ,
    Err_InvalidIPAddr ,
    Err_InvalidIPXAddr ,
    Err_UnknownCmd ,
    Err_TooManyUsers ,
    Err_TooManyCharsInOneWord,
    Err_ExistAnotherPri ,
    Err_ExistE1 ,
    Err_ExistAnotherE1 ,
    Err_ExistPri ,
    Err_Overgroup ,
    Err_TimeSlot ,
    Err_CanNotEncap ,
    Err_CanNotEncapSLIP,
    Err_CanNotCreateSub ,
    Err_SlipIsRun ,
    Err_CanNotChange ,
    Err_AlreadyInSameMode ,
    Err_SyncProtocolIsRun ,
    Err_SyncNotModem,
    Err_OutOfMemory ,
    Err_ModemCantChange ,
    Err_ModemSync ,
    Err_ModemBackup,
    Help_Return ,
    Help_WithSemiColon ,
    Help_Point ,
    Help_Ce1TimeSlot ,
    Help_ChannellizeGroup ,
    Help_Administratively ,
    Help_ProtocolIPAddr,
    Help_ProtocolIPXAddr,
    Help_InterfaceUp,
    Help_InterfaceDown,
    Help_LineSpoofing,
    Help_InterfaceSpoofingInterface,
    Help_InterfaceStandby,
    Help_InterfaceAdminDown,
    Help_LineUp,
    Help_LineDown,
    Help_AlreadyBeenShutdown,
    Help_ShutDown,
    Help_NoBeenShutdown,
    Help_IsReset,
    Help_Enabled,
    Help_Disabled,
    Help_Sync,
    Help_Asyn,
    Help_sync,
    Help_asyn,
    Help_Modem,
    Help_ModemEnd,
    Help_SubType_P2P,
    Help_SubType_MP,
    Help_Router_Mtu,
    Help_If_Descript,
    Help_If_Route,
    IF_SHOW_ALL_INTERFACE,
    IF_SHOW_ALL_SLOT,
    Help_Router_Vlan,
    Help_Router_MEth,
    Help_Router_SRP,
    Help_Router_Eth_Trunk,
    Help_Router_IP_Trunk,
    Help_Router_SRPIndex,
    Help_Router_Eth_TrunkIndex,
    Help_Router_IP_TrunkIndex,
    Help_Router_VlanIndex,
    Help_Router_MEthIndex,
    Err_Ifnet_NoVlan,
    Err_Ifnet_CreateVlanIfOnSubvlan,
    Err_Ifnet_RoutedOnAggrPortVlan,
    Err_Ifnet_RoutedOnMultiPortVlan,
    Err_Ifnet_RoutedOnSuperVlan,
    
    Help_NullHelp,
    Help_Diagnol_Clarify,
    Err_NoSlot,

    Help_Router_VI,
    Help_Router_VIIndex,
        
    Help_Router_UI,
    Help_Router_UIIndex,
    
    RouterMsgMax    /* Only stands for the sum, no according msg. added by z36377 */
};

enum enumIfnetHotMsgNotify
{
    IFNET_HOT_MSG_INTF_INSERT = 1,
    IFNET_HOT_MSG_INTF_REMOVE,
    IFNET_HOT_MSG_SLOT_INSERT,
    IFNET_HOT_MSG_SLOT_REMOVE
};

/* 用于表示函数功能, 对命令中的接口名进行帮助检查时使用 */
enum enumFuncFlag
{
    IF_FUNC_TYPE_CHECK=0,      /* 类型检查 */
    IF_FUNC_TYPE_HELP,         /* 类型帮助 */
    IF_FUNC_NUMBER_CHECK,      /* 编号检查 */
    IF_FUNC_NUMBER_HELP,       /* 编号帮助 */
    IF_FUNC_NAME_CHECK,        /* 名称检查 */
    IF_FUNC_NAME_HELP,         /* 名称帮助 */
    IF_FUNC_FULLNAME,          /* 接口名称扩展 */
    IF_FUNC_FULLTYPE,          /* 接口类型扩展 */
    IF_FUNC_HELP,              /* 检查函数的标志 */
    IF_FUNC_CHECK              /* 帮助函数的标志 */
};

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _VISP_IR_IFNET_H_ */
