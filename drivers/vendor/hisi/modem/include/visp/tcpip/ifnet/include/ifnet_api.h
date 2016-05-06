/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ifnet_api.h
*
*  Project Code: VISPV100R007
*   Module Name: IFNET
*  Date Created: 2008年1月25日
*        Author: x00100259
*   Description: IFNET模块对外提供的数据结构定义和用户API声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008年1月25日  x00100259         Create the first version.
*
*******************************************************************************/


#ifndef _IFNET_API_H_
#define _IFNET_API_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


/**********************************************************************
*                        对外提供的错误码
***********************************************************************/

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
    VRP_IFNET_IS_L2IF,                   /* 57 L2IF接口 */
    VRP_IFNET_L2IFVTBLNULL,              /* 58 L2IF虚函数表指针为空*/

    /*Add for BC3D00792,DR.131获取链路层状态 start*/
    VRP_IFNET_IPOA_NOINIT,              /* 59 IPOA模块未使用 */ 
    VRP_IFNET_IPOA_ERR,                 /* 60 IPOA模块API处理失败 */ 
    VRP_IFNET_ETH_NOINIT,               /* 61 Eth模块未使用*/ 
    VRP_IFNET_ETH_ERR,                  /* 62 Eth模块API处理失败 */ 
    /*Add for BC3D00792,DR.131获取链路层状态 end*/
    VRP_IFNET_PPIGETMTU_ERR,            /* 63 向底层查询最大MTU错误 */

    VRP_IFNET_L2TRUNKPHYTRANSMIT_NULL,  /* 64 二层TRUNK的物理层报文发送函数为空 */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    VRP_IFNET_VRF_ERR,                  /* 65 VRF模块API处理失败 */ 
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    
    /* 66 Begin l00147446 判断g_pstIfFunVtbl是否为空 09-03-13*/
    VRP_IFNET_VRF_NOT_INIT,            
    /*End l00147446 判断g_pstIfFunVtbl是否为空 09-03-13*/
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

/**********************************************************************
*                        对外提供的宏定义 
***********************************************************************/

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN                 47       /* 同iifnet_inc.h */ 
#endif
#define MAX_INTERFACE_DESCRIPTION_LEN          80       /* 描述最大长度 */
#define IF_MAX_MAC_LEN                         6

#define IF_RTATTR_BROADCAST             0x2
#define IF_RTATTR_NBMA                  0X4
#define IF_RTATTR_LOOPBACK              0x8
#define IF_RTATTR_POINT2POINT           0x10
#define IF_RTATTR_MULTICAST             0x8000

/*Added by z00208058, for 可创建的最大ETH接口数扩展, 2012/12/7 */
#define ETHIF_DEF_MAXNUM               4096

/* 网络层协议类型 */
#define NETPROTO_IP                    0x0001
#define NETPROTO_IPX                   0x0002
#define NETPROTO_BRIDGE                0x0004
#define NETPROTO_OSI                   0x0008
#define NETPROTO_LCP                   0x0010
#define NETPROTO_LACP                  0x0020
#define NETPROTO_IPv6                  0x0040
#define NETPROTO_PPPMUXCP              0x0080
#define NETPROTO_LQM                   0x0100
#define ALL_INDEX                      0xFFFFFFFF

/* 通知函数链类型码 */
#define IFC_LINKMSG_NOTIFY  0       /* 链路层消息通知类型 */
#define IFC_DEVMSG_NOTIFY   1       /* 底层消息通知类型 */ 
#define IFC_ADDIF_NOTIFY    2       /* 接口创建通知类型 */
#define IFC_ADDSUBIF_NOTIFY 3       /* 子接口创建通知类型 */
#define IFC_DELIF_NOTIFY    4       /* 接口删除通知类型 */
#define IFC_SHUTIF_NOTIFY   5       /* 接口shutdown通知类型 */

#define IFC_PRIORITY_HIGHEST   0    /* 通知优先级上限 */
#define IFC_PRIORITY_LOWEST    5    /* 通知优先级下限 */


/* 接口链路状态 */ 
#define IF_STATUS_PROT_DOWN          0x1
#define IF_STATUS_LOW_DOWN           0x2
#define IF_STATUS_PROT_UP            0x4
#define IF_STATUS_PROT6_DOWN         0x8   /*表示IPv6 line protocol 处于DOWN的状态*/
#define IF_STATUS_PROT6_UP           0x10  /*表示IPv6 line protocol 处于UP的状态*/


/* used for if_ulShutdown */
#define IF_PHY_SHUTDOWN         1
#define IF_SHUTDOWN             ( IF_PHY_SHUTDOWN )


/*usMsgType value: */
#define RTM_CREATE  0x01    /* 接口、虚链路创建 */
#define RTM_DEL     0x02    /* 接口、虚链路删除*/
#define RTM_STATE   0x04    /* 接口、虚链路的usIfStste 或 usIfFlags 发生改变*/
#define RTM_CONFIG  0x08    /* 接口、虚链路的参数信息sIfData发生改变*/
#define RTM_BOARDREMOVE 0x10

/*usIfState value: 必须设置正确*/
#define  IF_UP                 0x01
#define  IF_DOWN               0x02
#define  IF_SETMAC             0x04
#define  IF_UNBIND             0x08
#define  IF_STATES             IF_UP | IF_DOWN
#define  OSI_UP                0x10    /*当OSICP协商成功，通知产品接口状态变成UP (光网络路由模块使用)*/
#define  OSI_DOWN              0x20    /*当OSICP协商失败，通知产品接口状态变成DOWN (光网络路由模块使用)*/

/* l2if ifnet flag */
#define L2IF_PORT       1
#define L2IF_TRUNKPORT  2

/* NP处理LCPECHO报文 */
#define NP_HANDLE_LCP_ECHO   0xFFFFFFFA


typedef LONG (*FUNC_PHY_INITIAL)(VOID * , ULONG *, ULONG *, ULONG );
typedef ULONG (*FUNC_PHY_IOCTL)(VOID * , ULONG , CHAR * );

typedef ULONG (*TCPIP_GETVIADDR_HOOK_FUNC)(VOID);

/**********************************************************************
*                        对外提供的数据结构定义
***********************************************************************/
/* 物理层控制字 */
/**********************************************************
*  在此定义ioctl函数的case项,注意不能与syst_pub.h中的
*  命令项 DRV_TEST_ENTRY 重合,测试命令进入各个驱动的总入口
\*********************************************************/
enum  enumPhyIoCtl
{
    PHY_POWERUP = 0,                    /* 0 上电 */
    PHY_INIT,                           /* 1 初始化，VISP暂不使用（预留） */
    PHY_SHUTDOWN,                       /* 2 关闭（ShutDown）底层物理接口 */
    PHY_NO_SHUT,                        /* 3 打开（UP）底层物理接口 */
    PHY_ENABLERECV,                     /* 4 使能接收 */
    PHY_DISABLERECV,                    /* 5 去使能接收 */
    PHY_CHECKFLOW,                      /* 6 CHECKFLOW，VISP暂不使用（预留） */
    PHY_BUILDRUN,                       /* 7 BUILDRUN，VISP暂不使用（预留） */
    PHY_CHECK,                          /* 8 CHECK，VISP暂不使用（预留） */
    PHY_DELETE,                         /* 9 通知底层删除物理接口 */
    PHY_SETMACADDR,                     /* 10 配置physical地址 */
    PHY_SETMACTABLE,                    /* 11 配置mac表，VISP暂不使用（预留） */
    PHY_GETMACADDR,                     /* 12 获取physical地址，VISP暂不使用（预留） */
    PHY_MAP,                            /* 13 MAP，VISP暂不使用（预留） */
    PHY_PROTOCOL_CHG,                   /* 14 更改协议类型 */
    PHY_GETINFO,                        /* 15 获取接口信息 */
    PHY_GETSTATISTIC,                   /* 16 获取统计信息 */
    PHY_CLEAR_PORT,                     /* 17 清除端口 */
    PHY_GETMAXBD,                       /* 18 GETMAXBD */
    PHY_SETLEASED,                      /* 19 SETLEASED */
    PHY_ISPURE_SYNC,                    /* 20 ISPURE_SYNC，VISP暂不使用（预留） */
    PHY_ISASYNC,                        /* 21 询问底层是同步链路还是异步链路：返回0，表示同步链路，返回1，表示异步链路（默认为0） */
    PHY_ISSOFTCVT,                      /* 22 询问底层是硬件还是软件完成PPP报文的同异步转换：0，硬件完成；1，软件完成（默认1）注：前提条件是底层是异步链路 */
    PHY_ATMMCLK,                        /* 23 ATMMCLK */
    PHY_ATMMSERV,                       /* 24 ATMMSERV */
    PHY_ATMMOAMPVC,                     /* 25 ATMMOAMPVC */
    PHY_ATMMOAMRETRY,                   /* 26 ATMMOAMRETRY */
    PHY_ATMAPVC,                        /* 27 添加PVC */
    PHY_ATMDPVC,                        /* 28 删除PVC */
    PHY_ATMINIT,                        /* 29 ATMINIT */
    PVC_STA_CHANGE,                     /* 30 状态变化 */

    PHY_IMA_SETLINKNUM,                 /* 31 SETLINKNUM */
    PHY_CLI_ATMIMA_GETFRAMELENGTH,      /* 32 ATMIMA_GETFRAMELENGTH */

    PHY_ATMGETPVCINFO,                  /* 33 获取PVC信息，VISP暂不使用（预留） */
    PHY_LINK_DOWN,                      /* 34 链路down */
    /*added by liuhui, for PPPoE Client, to notify PPPoE Client Link down*/
    PHY_POECLIENT_LINK_DOWN_WITHPADT,   /* 35 POEC链路因为PADT报文down，VISP的POEC模块使用，用户不用处理 */
    PHY_POECLIENT_LINK_DOWN_NOPADT,     /* 36 POEC链路非因为PADT报文down，VISP的POEC模块使用，用户不用处理 */
    /*add ends*/
    PHY_GETMIBINFO,                     /* 37 获取MIB信息 */
    PHY_SETPROMODE,                     /* 38 SETPROMODE */
    PHY_SETRCVADDRSTATUS,               /* 39 SETRCVADDRSTATUS */
    /* 判断底层是否UP 2001-03-26 */
    PHY_ISUP,                           /* 40 判断是否UP，VISP的POEC模块使用，用户不用处理 */
    /* Notify low layer ACCM */
    PHY_SETACCM,                        /* 41 SETACCM，通知底层同异步转换字符集（ACCM）注：前提条件是底层为异步链路 */
    /* for D10708 */
    PHY_GET_HARD_INFO,                  /* 42 GET_HARD_INFO */
    PHY_GETASYNMODE,                    /* 43 GETASYNMODE */
    PHY_ENABLE,                         /* 44 使能 */
    PHY_DISABLE,                        /* 45 去使能 */
    PHY_INIT_BUFFER,                    /* 46 初始化缓冲区 */
    PHY_GET_VER,                        /* 47 GET_VER */
    PHY_GETPHYSTATUS,                   /* 48 GETPHYSTATUS */
    PHY_DEBUG,                          /* 49 DEBUG */
    PHY_SETLOOPBACK,                    /* 50 SETLOOPBACK */
    PHY_E1DELETE,                       /* 51 E1DELETE */
    PHY_LINECODE,                       /* 52 LINECODE */
    PHY_FRAMING,                        /* 53 FRAMING */
    PHY_LINECLOCK,                      /* 54 LINECLOCK */
    PHY_E1BUILDRUN,                     /* 55 E1BUILDRUN */
    PHY_BOARD_RESET,                    /* 56 BOARD_RESET */
    PHY_E1CHECKSTAT,                    /* 57 E1CHECKSTAT */
    PHY_T1DELETE,                       /* 58 T1DELETE */
    PHY_T1BUILDRUN,                     /* 59 T1BUILDRUN */
    PHY_T1CHECKSTAT,                    /* 60 T1CHECKSTAT */
    PHY_CHANNEL_SPEED,                  /* 61 CHANNEL_SPEED */
    PHY_T1_CABLE,                       /* 62 T1_CABLE */
    PHY_READREG,                        /* 63 READREG */
    PHY_WRITEREG,                       /* 64 写寄存器 */
    PHY_SETPORT,                        /* 65 SETPORT，VISP暂未使用（预留） */
    PHY_ADDLINK,                        /* 66 PHY_ADDLINK */
    PHY_DELELELINK,                     /* 67 PHY_DELELELINK */
    PHY_CANDELELTE,                     /* 68 PHY_CANDELELTE */
    PHY_LOOPBACK_STATE,                 /* 69 PHY_LOOPBACK_STATE */
    PHY_IPV6_ADD_MCAST_ADDR,            /* 70 PHY_IPV6_ADD_MCAST_ADDR */
    PHY_IPV6_DEL_MCAST_ADDR,            /* 71 PHY_IPV6_DEL_MCAST_ADDR */
    /*This 2 value were moved here by ZhuKun 36377,20040827,For D00575*/
    PHY_JOINMULTI,                      /* 72 加入多播组 */
    PHY_LEAVEMULTI,                     /* 73 离开多播组 */
    PHY_GET_ROUTFLAG,                   /* 74 获取UI接口路由属性 */
    PHY_GETDOWNMODE,                    /* 75 删除接口或shutdown接口，获取底层是DownAll(发送TR报文)还是Down(不发送TR报文) */
    PHY_ADD_VRRP_VIRTUAL_MAC,           /* 76 添加VRRP虚拟MAC */
    PHY_DEL_VRRP_VIRTUAL_MAC,           /* 77 删除VRRP虚拟MAC */
    PHY_ENABLE_VRRP,                    /* 78 使能/去使能VRRP命令字 */
    PHY_LCPECHOOPEN,                    /* 79 LCP Echo Open命令字 */
    PHY_LCPECHODOWN,                    /* 80 LCP Echo Open命令字 */
    PHY_LCPECHOSETCONF,                 /* 81 LCP Echo Open命令字 */

    PHY_GETINTFSTATUS,                  /* 82 查询接口状态命令字 */
    PHY_GETINTFTYPE,                    /* 83 查询接口类型命令字 */

    PHY_MAX_PHYWORD  /*No use actually.Just for adding enum word easily. ZhuKun,20041020*/
};
/* 底层上报信息 */
enum enumLowToUp
{
    ISLUP = 0,              /* 0 底层上报本端接口UP消息 */
    ISLDOWN,                /* 1 底层上报本端接口DOWN消息 */
    ISLCHGBAUD,             /* 2 更换波特率命令字，VISP暂不处理此命令字（预留） */
    ISLASYTOSYN,            /* 3 同异步更改命令字，VISP暂不处理此命令字（预留） */
    ISLSYNTOASY,            /* 4 同异步更改命令字，VISP暂不处理此命令字（预留） */
    ISLSHUTDOWN,            /* 5 SHUTDOWN命令字，VISP暂不处理此命令字（预留） */
    ISLNOSHUT,              /* 6 UNSHUTDOWN命令字，VISP暂不处理此命令字（预留） */
    ISLDELETE,              /* 7 删除命令字，VISP暂不处理此命令字（预留） */
    ISLCHGPROTOCOL,         /* 8 改变协议类型，VISP暂不处理此命令字（预留） */
    ISLGETPROTOCOL,         /* 9 获取协议类型，VISP暂不处理此命令字（预留） */
    ISLSETMAC,              /* 10 配置physical地址 */
    /*D18794*/
    ISLSPEED,               /* 11 更改速率命令字 */
    /* 2001/02/22 sunshengtao */
    ISLATMOAMSTATE,         /* 12 更改ATM可维可测状态命令字，VISP暂不处理此命令字（预留） */
     
     /* ,ISLJOINMULTI, */ /*add by luohanjun*/
     /* ISLLEAVEMULTI */
     
    ISLDOWNALL,             /* 13 (仅用于PPP接口)底层上报本端PPP接口DOWN消息,并通知对端PPP接口也DOWN */ 
    ISLDUPLEX,              /* 14 visvp1r7c03,l2if ADD, 底层上报双工模式 */

    /* OAM-3ah上报的状态 */
    ISLEFMNORMAL,           /* 15 3ah上报的Normal状态 */
    ISLEFMUP,               /* 16 3ah上报的Up状态 */
    ISLEFMDOWN,             /* 17 3ah上报的Down状态 */
    
    ISLPPPNPLOOKBACK,       /* 18 NP探测到自环 */
    ISLPPPNPLCPDOWN,        /* 19 NP探测到LCP Down */
    ISLPPPNPINTERCROSS,     /* 20 NP探测到串接 */

    ISLNEEDRESENDARP,       /* 21 DTS2011022802677 增加Trunk接口的ARP请求报文的重传机制 */

    /* Modified by lihaiming218630, nsr倒换出现1way hello, 2013/4/20   问题单号:lhm */
    LSIFFINISH,             /*22 NSR实现中，倒换后底层上报完所有接口状态后，会上报一个finish*/    
    /*End of Modified by lihaiming218630, 2013/4/20   问题单号:lhm */

    ISSETLINESTATUS,        /*23 设置链路状态 */
    
    ISMAX_END     
};

/*接口的物理状态(对应IFNET_S的if_ulPhyStatus字段*/
enum enumPhyStatus{
    IF_NORMAL= 0,           /* 0  Normal*/
    IF_STATUS_UP,           /* 1  UP*/
    IF_STATUS_DOWN,         /* 2  Down*/
    IF_STATUS_SPOOFING,     /* 3  spoofing*/
    IF_STATUS_STANDBY,      /* 4  stand by*/
    IF_STATUS_SHUTDOWN,     /* 5  shut down */
    IF_STATUS_NOTUSED,      /* 6  not use*/
    IF_STATUS_DELETE,       /* 7  delete*/
    IF_STATUS_NOTEXIST,     /* 8  not exist*/
    IF_STATUS_REMOVE,       /* 9  remove*/
    IF_STATUS_END
};

#define IF_1D_MODE 0                 /* 表示一维接口 */
#define IF_3D_MODE_DISTRIBUTE 1      /* 表示三维分步式接口 */
#define IF_3D_MODE_CENTRAL 2         /* 表示三维集中式接口 */
/*接口类型(对应IFNET_S的if_ulType字段*/
enum enumIFTYPE
{
    IF_ASYNC_TYPE=0,
    IF_AUX_TYPE,  
    IF_NULL_TYPE,   
    IF_LOOPBACK_TYPE,
    IF_LOOP_TYPE,
    IF_SERIAL_TYPE,
    IF_CONSOLE_TYPE,
    IF_ETHERNET_TYPE,

    IF_VIRTUAL_TEMPLATE_TYPE,       
    IF_VLAN_TYPE,
    IF_POS_TYPE,    
    IF_VIRTUAL_ETHERNET_TYPE,
    IF_GIGABYTE_ETHERNET_TYPE,

    IF_GROUPE1_TYPE,        
    IF_ATM_TYPE,
    IF_BRI_TYPE,
    IF_E1_TYPE,
    
    IF_MPGROUP_TYPE,
    IF_DIALER_TYPE,
    IF_MTUNNEL_TYPE, /* 代码同步, 增加新类型. z36377, 2004/09/18 */

    /*VISP.III 增加VA接口类型*/
    IF_TEMPLATE_CHAN_TYPE,  /*模板下的VA接口*/
    IF_VIRTUAL_ACCESS_TYPE, /*Dialer下的VA接口*/

    /* VISPV1R6增加Trunk接口类型 */
    IF_ETH_TRUNK_TYPE,    /* 以太Trunk接口 */

    IF_VI_TYPE,         /*VI 接口*/

    IF_UI_TYPE,         /*UI 接口*/
    IF_TUNNEL_TYPE,
    
    IF_MAX_TYPE,
    IF_OTHER_TYPE = 0xFFFF
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
/* #if (VRP_IFNET_E1_T1_E3_T3_CPOS == VRP_YES) */
    PORT_E3,
    PORT_T3,
    PORT_CPOS,
/* #endif */
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

/*IP协议状态(对应TCPIP_SetIpProtocolState的入参ulState*/
typedef enum IP_PROTOCOL_ENUM
{
    TCPIP_IP_PROTOCOL_UP,           /* 接口IP协议UP */
    TCPIP_IP_PROTOCOL_DOWN          /* 接口IP协议DOWN */
}IP_PROTOCOL_ENUM;

/* VISPV1R7C03,底层上报的全双工/半双工状态 */
typedef enum enPhyDuplex
{
    TCPIP_DUPLEX_FULL,    /* 全双工,ETH接口初始化时默认值 */
    TCPIP_DUPLEX_HALF,    /* 半双工 */
}PHY_DUPLEX_EN;

/*Add for BC3D00792,DR.131获取链路层状态*/
typedef enum IF_LINK_STATUS_ENUM
{
    TCPIP_NOMAL = 0x0,             /* 接口上无该特性状态*/
    TCPIP_PROT_DOWN = 0x1,         /* IF_STATUS_PROT_DOWN*/
    TCPIP_LOW_DOWN = 0x2,          /* IF_STATUS_LOW_DOWN */
    TCPIP_PROT_UP = 0x4,           /* IF_STATUS_PROT_UP */
}IF_LINK_STATUS_ENUM;

typedef struct  tagIF_LINKSTATUS_S
{
    ULONG   ulIfLinkStatus;
    ULONG   ulIfLink6Status;
}IF_LINKSTATUS_S;
/*Add for BC3D00792,DR.131获取链路层状态*/

typedef struct  tagIF_Config
{
    USHORT  usIfDelay;
    USHORT  usIfReliability;
    USHORT  usIfLoad;
    UCHAR   ucPadding[2]; 
    ULONG   ulIfBandwidth;
    ULONG   ulIfBaudrate;
    ULONG   ulIfMtu;
    /*add sunyu for bandwidth,delay command*/
    ULONG   ulConfIfDelay;
    ULONG   ulConfIfBandwidth;

    ULONG   ulData;
} IF_CONFIG_S;

#define CONFIG_MTU    0x01  /*VLINKSTATUS_S的RTM_CONFIG标记,表示MTU变化*/
#define CONFIG_SPEED  0x00  /*VLINKSTATUS_S的RTM_CONFIG标记,表示SPEED变化*/

typedef struct tagVLINKSTATUS_S
{
    ULONG  ulIntfIndex;     /* 接口唯一索引值 */
    ULONG  ulVlinkIndex;    /* 虚链路索引值。最高的一字节为同步号，低两字节为索引号。接口事件时置为0 */
    USHORT  usSlot;         /* 接口所在槽号，new in 3.0 */
    USHORT  usMsgType;      /* 见下面定义 */
    USHORT  usIfState;      /* 接口状态 */
    USHORT  usIfFlags;      /* 接口标志 */        
    CHAR    cIfName[IF_MAX_INTERFACE_NAME_LEN + 1];    /* 接口名称 */
    USHORT  usIfType;       /* 接口类型 */
    USHORT  usConfigTag;    /*RTM_CONFIG的标记，CONFIG_MTU为MTU改变, CONFIG_SPEED为波特率改变*/
    IF_CONFIG_S  stIfData;
    SOCKADDR_S  stPeerAddr; /* 对端地址，创建虚链路时必须有对端地址 */
    ULONG ulMacAddrLen;
    UCHAR ucMacAddr[IF_MAX_MAC_LEN + 1];
    UCHAR ucPadding_2; 
    ULONG ulVrfIndex;

}VLINKSTATUS_S;



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


typedef struct tagDEVLINK
{
#define DEVICE_NAME_LEN 50
    CHAR   dev_pDeviceName[DEVICE_NAME_LEN];
    USHORT dev_usSlot;           /* 该字段VISP当前未使用，而在PARC1.9产品中，被用于保存链路配置信息 */
                                 /* 无线产品用到该字段 */
                                 /* SGSN用到该字段 */
    USHORT dev_usAdaptor;        /* 该字段VISP当前未使用，而在PARC1.9产品中，被用于保存链路配置信息 */
                                 /* SGSN用到该字段 */
    USHORT dev_usUnit;           /* 该字段VISP当前未使用，而在PARC1.9产品中，被用于保存链路配置信息 */
                                 /* 无线产品用到该字段 */
                                 /* SGSN用到该字段 */
                                 /* NodeBV1版本中，用于保存端口号或者通道索引号 */
    USHORT dev_usSubChan;        /* 该字段VISP当前未使用，而在PARC1.9产品中，被用于保存链路配置信息 */
    USHORT dev_usMaxChannel;
    USHORT dev_usAuxFlag;        /* wether a AUX. 1 - aux, 0 - not aux. */
    USHORT dev_usIntPri;
    ULONG  dev_ulFlag;
    ULONG  dev_ulIf;
    /* add by xiehuaguo for support np */
    ULONG  dev_ulTimeSlotBitMap;       /* 该通道占用的时隙，每个比特表示一个时隙，为1时表示配置对应的时隙，
                                                为0时表示不配置对应的时隙 */
                                       /* 该字段VISP当前未使用，而在PARC1.9产品中，被用于保存链路配置信息 */
                                       /* 无线产品用到该字段 */
    ULONG  dev_ulBandWidth;            /* 接口带宽 */
    FUNC_PHY_INITIAL   dev_pfInitial;  /* 设备初始化函数 */
    FUNC_PHY_IOCTL     dev_pfIoCtl;    /* 设备控制函数 */
    struct  tagDEVLINK *dev_pNext;     /* point to the next node in link */
}DEVLINK_S;

#ifndef _IN6ADDR_S
#define _IN6ADDR_S
typedef   struct    tagIN6Addr
{
    union
    {
        UCHAR     u6_ucaddr[16];
        USHORT    u6_usaddr[8];
        ULONG     u6_uladdr[4];
    } u6_addr;    /* 128-bit IP6 address */
} IN6ADDR_S;
#endif
/* 为了引用方便，进行如下宏定义*/
#ifndef s6_addr
#define s6_addr      u6_addr.u6_ucaddr
#endif
#ifndef s6_addr8
#define s6_addr8     u6_addr.u6_ucaddr
#endif
#ifndef s6_addr16
#define s6_addr16    u6_addr.u6_usaddr
#endif
#ifndef s6_addr32
#define s6_addr32    u6_addr.u6_uladdr
#endif

typedef struct tagTCPIP_IFNET
{
    CHAR  if_szIfName[ IF_MAX_INTERFACE_NAME_LEN+1];           /* 接口名*/
    CHAR  if_szDescript[ MAX_INTERFACE_DESCRIPTION_LEN+1 ]; /* 接口描述字符串 */
    UCHAR ucPadding_1[3]; 

    ULONG if_ulIfIndex;             /* VISP私有索引结构 */
    ULONG if_ulProductIfIndex;      /* 与产品相关的接口索引 */       
    
    ULONG if_ulSlotNum;         /* 高16位为卡号，低16位为槽号 */
    ULONG if_ulTopIfIndex;      /* 该接口的配置父亲的索引 */
    ULONG if_ulNetIfIndex;      /* 该接口的网络层策略父亲的索引 */

    ULONG if_ulIsisFlag ;       /* 接口下ISIS使能标志 */

    /* 端口属性 */
    ULONG if_ulSpoofing;            /* Spoofing 标识，1表示具有 spoofing 特性, 0表示不具有这个特性 */
    ULONG if_ulMoving;        
    ULONG if_ulShutdown;            /* shutdown标识,&IF_SHUTDOWN非空表示执行了shutdown操作，否则没有执行 */
    ULONG if_ulSubIndex;            /*  0 表示非子接口；非0 表示子接口(子接口编号) */   
    ULONG if_ulSubIfNum;            /*  该接口下配置的子接口数 */
    ULONG if_ulLineProtocol;        /* 端口封装的链路层协议 */
    ULONG if_ulLineStatus;          /* 端口协议状态, 1 为UP, 2为DOWN*/
    ULONG if_ulPhyStatus;       /* 端口物理状态，对于子接口来说，看主接口状态 */

    ULONG if_ulLine6Status;         /* 端口协议状态, 1 为UP, 0为DOWN*/      
    ULONG if_ulPhyType;             /* 端口的物理属性 */
    ULONG if_ulPortType;            /* 端口的类型 */
    
    /* 与网络层和路由模块相关的信息 */
    ULONG if_ulBaud;        /* 端口的波特率 */
    ULONG if_ulMTU;         /* 协商生效的MTU */
    ULONG if_ulCfgMTU;      /* 配置MTU */
    ULONG if_ulFlags;       /* P-P，NBMA，Broadcast ,  表示接口的路由属性 */    
    ULONG if_ulKeepAlive;   /* 链路层协商用和链路层探测链路状态用 */    
        
    /* 以下为扩展特性 */
    ULONG if_ulBandWidth;       /* 纪录接口缺省的bandwidth, 等于接口初始化时的波特率 */
    ULONG if_ulCfgBandWidth;    /* 纪录接口配置的bandwidth, 若不曾配置, 该值为0 */    
    ULONG if_ulType;           /*接口类型*/    

    /* VISPV1R7C03 L2IF 增加 */
    ULONG  if_ulL2OrL3;         /* 接口的二三层属性标记: 0表示三层接口,1表示L2IF_PORT,2表示L2IF_TRUNKPORT */

    ULONG  if_ulDuplexStatus;   /* 接口全双工/单双工工作状态,由底层上报,只对ETH有效.取值PHY_DUPLEX_EN */

    /* OAM协议扩展支持主备信息增加字段 */
    ULONG if_ulRawPhyStatus;    /* 保存底层上报的原始物理状态 */
    ULONG if_ulPhyDetectStatus; /* 保存OAM状态，接口OAM状态有以下三种：0 EFMNORMAL，1 EFMUP，2 EFMDOWN */

    /* 记录接口物理、协议UP/Down变化次数 */
    ULONG if_ulPhyUpCount;      /* 接口变化到物理UP次数 */
    ULONG if_ulPhyDownCount;    /* 接口变化到物理Down次数 */
    ULONG if_ulLineUpCount;     /* 接口变化到协议UP次数 */
    ULONG if_ulLineDownCount;   /* 接口变化到协议Down次数 */
    
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG if_ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ip6if_ulMtu;
}TCPIP_IFNET_S;

/*隧道接口下发PPI消息类型*/
#define TUNNEL_PPI_ADD  0x1
#define TUNNEL_PPI_DEL   0x2

/*隧道IP版本标识*/
#define TUNNEL_IP_VERSION_IPV4    0x1 /*IPv4版本*/
#define TUNNEL_IP_VERSION_IPV6    0x2 /*IPv6版本*/

/*隧道协议模式*/
#define TUNNEL_MODE_TYPE_NONE   0x0  /*隧道协议为空*/
#define TUNNEL_MODE_TYPE_GRE    0x1  /*GRE隧道协议*/

/* v6地址类型 */
#define TCPIP_ADDR_LINKLOCAL_FLAG  0x1
#define TCPIP_ADDR_GLOBAL_FLAG     0x2

typedef struct tagTCPIP_TUNNEL_IF_PPI
{
    ULONG  ulMsgType;      /*消息类型，指明配置参数或者删除参数*/
    ULONG  ulIpVer;        /* IP版本标识:TUNNEL_IP_VERSION_IPV4--IPv4;TUNNEL_IP_VERSION_IPV6--IPv6 */
    ULONG  ulProMode;      /* 隧道协议模式*/
    ULONG  ulDstIP[4];     /* 隧道的目的地址，主机序，V4地址ulDstIP[0]有效*/
    ULONG  ulSrcIP[4];     /* 隧道的源地址，主机序，V4地址ulSrcIP[0]有效*/
    ULONG  ulGreKey;       /* GRE Key，范围为0~0xFFFFFFFF*/
    UCHAR  ucNeedGreKey;   /* 标识用户是否配置了Gre key，1(VRP_YES)表示配置Gre Key， 0(VRP_NO)表示不配置Gre Key*/
    UCHAR  ucPad[3];       /* 保留字段*/
}TCPIP_TUNNEL_IF_PPI_S;

/**********************************************************************
*                        对外提供的用户API声明
***********************************************************************/

/*接口类命令模式预处理函数声明，可以将接口索引转换为某些特性索引，如port index*/
typedef VOID (*IF_MSG_NOTIFYFN)( ULONG ulIfIndex, ULONG ulCmd, CHAR *pcData);
typedef VOID (*IF_LMSG_NOTIFYFN)( ULONG ulProtocol,ULONG ulIfIndex, ULONG ulCmd, CHAR *pcData);

typedef VOID (*IF_PTR_NOTIFYFN)(ULONG ulIfIndex);/*通知接口增加、删除、关闭，参数为接口指针*/

typedef ULONG (*IF_TRANSMIT_FUNC)(ULONG,MBUF_S *);
typedef ULONG (*IF_PHYIOCTL_FUNC)(ULONG, ULONG, CHAR *);
typedef ULONG (*LinkMsgSend_HOOK_FUNC)(VLINKSTATUS_S *pstIFNETMsg);
typedef ULONG(*LinkMsg6Send_HOOK_FUNC)(IFVLINKENTRY6_S *pstIFNETMsg);
typedef ULONG (*ATMLinkIntVTable_HOOK_FUNC)(VOID** ppstLinkInt);
typedef VOID  (*NotifyIfState_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulProtoType, ULONG ulIFState);
typedef ULONG (*VIOutput_HOOK_FUNC)(MBUF_S* pstMbuf);

typedef ULONG (*L2Trunk_PhyTransmit_HOOK_FUNC)(ULONG ulIfIndex, MBUF_S* pstMbuf);

/* Description:为满足核心网RPU的应用,VISP实现L2 Trunk默认的分发策略:即VISP默认选择二层
               Trunk的一个成员端口进行报文发送.发送钩子中同时携带Tunrk接口索引及默认选择的
               一个成员端口的接口索引,由用户自行决定使用哪个参数 
   Parameter : ULONG ulTrunkIfIndex: L2 Trunk接口索引
               ULONG ulTrunkPortIfIndex:VISP默认选择的一个成员端口的接口索引
               MBUF_S *pstMbuf:报文*/
typedef ULONG (*L2TrunkPort_PhyTransmit_HOOK_FUNC)(ULONG ulTrunkIfIndex, 
                                                           ULONG ulTrunkPortIfIndex,
                                                           MBUF_S *pstMbuf);

typedef ULONG (*IF_VLANCHECKFN)(VOID *pIf);

/* 产品注册链路层发送函数，挂靠在三维虚接口上 */
typedef ULONG (* Interface3dOutput_HOOK_FUNC) (MBUF_S *pMBuf);
typedef ULONG (*PhySetDevLink_HOOK_FUNC)(VOID);

/* 产品注册的接口QoS发送函数原型 */
typedef ULONG (*IF_QosTransmitDone_HOOK_FUNC)(ULONG ulIfIndex, UINTPTR ulPhyLink, MBUF_S *pMBuf);
typedef ULONG (*IF_QosTransmit_HOOK_FUNC)(ULONG ulIfIndex, UINTPTR ulPhyLink, MBUF_S *pMBuf);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef ULONG (* IF_PROD_CHECK_HOOK_FUNC) (CHAR *szFullName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef ULONG (* IF_GET_VLINK_INDEX_HOOK_FUNC) (ULONG ulIfIndex,ULONG ulNextHop,ULONG ulVrfIndex,ULONG *pulVLinkIndex);

typedef struct tagTCPIP_ADDR_INFO
{
    ULONG ulIfIndex;
    IN6ADDR_S stDestAddr;
    IN6ADDR_S stSrcAddr;
    ULONG ulFlag;
}TCPIP_ADDR_INFO_S;

typedef struct tagTCPIP_ADDR_HOOK
{
    ULONG (*pfIF_MATCHSRCADDR_FUNC)(TCPIP_ADDR_INFO_S *pstMatchSrcAddr);
    ULONG (*pfIF_ISLOCALADDR_FUNC)(TCPIP_ADDR_INFO_S *pstLocalAddr);
    ULONG (*pfIF_HAVEADDRCHECK_FUNC)(TCPIP_ADDR_INFO_S *pstAddrCheck);
}TCPIP_ADDR_HOOK_S;


/*******************************************************************************
*    Func Name: TCPIP_ShutDownIf
*  Description: shutdown接口
*        Input: ULONG ulIfIndex:接口索引
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   x00100259               Create
*
*******************************************************************************/
extern ULONG TCPIP_ShutDownIf(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_CloseIfConfigEntry
*  Description: close watilist object
*        Input: ULONG ulWaitListHandle:WaitList Handle
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_CloseIfConfigEntry( UINTPTR ulWaitListHandle );
/*******************************************************************************
*    Func Name: TCPIP_CreateIFByDev
*  Description: 创建接口
*        Input: DEVLINK_S * pstDev:设备指针 
*               ULONG *pulIfIndex:接口索引指针
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_CreateIFByDev( DEVLINK_S * pstDev, ULONG *pulIfIndex );
/*******************************************************************************
*    Func Name: TCPIP_DeleteIF
*  Description: 删除接口
*        Input: ULONG ulIfIndex:接口索引
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_DeleteIF( ULONG ulIfIndex );
/*******************************************************************************
*    Func Name: TCPIP_DynamicCreateIF
*  Description: 动态创建接口
*        Input: CHAR* szFullName:接口名称
*               
*               
*       Output: ULONG *pulIfIndex:接口索引
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_DynamicCreateIF( CHAR* szFullName,  ULONG *pulIfIndex );

/*******************************************************************************
*    Func Name: TCPIP_RegFuncL2TrunkPhyTransmitHook
* Date Created: 2009-02-13
*       Author: L00105073
*  Description: 注册L2Trunk 的物理层报文发送函数
*        Input: L2Trunk_PhyTransmit_HOOK_FUNC pfHookFunc:要注册的钩子函数
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-13   L00105073                          Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncL2TrunkPhyTransmitHook(L2Trunk_PhyTransmit_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncL2TrunkPortPhyTransmitHook
* Date Created: 2009-11-21
*       Author: z62531
*  Description:为满足核心网RPU的应用,VISP实现L2 Trunk默认的分发策略:即VISP默认选择二层
*               Trunk的一个成员端口进行报文发送.发送钩子中同时携带Tunrk接口索引及默认选择的
*              一个成员端口的接口索引,由用户自行决定使用哪个参数 
*        Input: L2TrunkPort_PhyTransmit_HOOK_FUNC pfHookFunc:要注册的钩子函数
*       Output: 
*       Return: 成功或错误码
*      Caution: TCPIP_RegFuncL2TrunkPhyTransmitHook和TCPIP_RegFuncL2TrunkPortPhyTransmitHook
*               钩子用户只需要注册其中之一即可
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-21   z62531                             Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncL2TrunkPortPhyTransmitHook(L2TrunkPort_PhyTransmit_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_CreateL2Trunk
* Date Created: 2008-11-18
*       Author: LY(57500)
*  Description: 创建L2 trunk接口
*        Input: CHAR* szFullName: 接口名
*               ULONG *pulIfIndex: 输出创建接口的接口索引
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-11-18    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_CreateL2Trunk(CHAR* szFullName, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetConfigMtu
*  Description: 获取接口的配置MTU值
*        Input: ULONG ulIfIndex:接口索引
*               
*       Output: ULONG *pulMtu:MTU值
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*  2008-05-14   x36317                  A82D25788:直接访问IFNET_S字段获取,不再调用组件接口,
*                                       避免在关中断期间获取信号量
*
*******************************************************************************/
extern ULONG  TCPIP_GetConfigMtu( ULONG ulIfIndex, ULONG *pulMtu );
/*******************************************************************************
*    Func Name: TCPIP_GetFullNameByIfIndex
*  Description: 根据接口索引获取接口名称
*        Input: ULONG ulIfIndex:接口索引
*               CHAR *pszIfName:接口名称
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetFullNameByIfIndex( ULONG ulIfIndex,CHAR *pszIfName );
/*******************************************************************************
*    Func Name: TCPIP_GetIfConfigEntry
*  Description: Get object for IfConfig
*        Input: ULONG ulEntryWaitList:WaitList Handle 
*               
*       Output: TCPIP_IFNET_S * pstIfConfig:指向获取到的TCPIP_IFNET_S的指针
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetIfConfigEntry( UINTPTR ulEntryWaitList, TCPIP_IFNET_S * pstIfConfig );
/*******************************************************************************
*    Func Name: TCPIP_GetIfIndexByFullName
*  Description: 根据接口名称获取接口索引
*        Input: CHAR *pszIfName:接口名称              
*       Output: ULONG *pulIfIndex:接口索引
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetIfIndexByFullName( CHAR *pszIfName, ULONG *pulIfIndex );
/*******************************************************************************
*    Func Name: TCPIP_GetIfindexByPortInfo
*  Description: 根据接口号和设备号获取接口索引
*        Input: ULONG ulPortType:接口类型
*               ULONG ulPortNo:接口号
*       Output: ULONG *pulIfIndex:接口索引               
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetIfindexByPortInfo( ULONG *pulIfIndex, ULONG ulPortType,  ULONG ulPortNo);
/*******************************************************************************
*    Func Name: TCPIP_GetIfnetHADbg
*  Description: 获取IFNET模块HA调试开关
*        Input: 无
*       Output: ULONG *pulDbg:HA调试开关
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetIfnetHADbg( ULONG *pulDbg );
/*******************************************************************************
*    Func Name: TCPIP_GetIsisFlag
*  Description: 获取ISIS开关
*        Input: ULONG ulIfIndex:接口索引
*               
*       Output: ULONG *pulFlag:ISIS开关
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetIsisFlag(  ULONG ulIfIndex ,ULONG *pulFlag );
/*******************************************************************************
*    Func Name: TCPIP_GetKeepAliveValue
*  Description: 获取接口的KEEPALIVE值
*        Input: ULONG ulIfIndex:接口索引
*               
*       Output: ULONG *pulValue:KEEPALIVE值
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetKeepAliveValue( ULONG ulIfIndex, ULONG *pulValue );
/*******************************************************************************
*    Func Name: TCPIP_GetLinkMtu
*  Description: 获取接口的MTU值
*        Input: ULONG ulIfIndex:接口索引
*               
*       Output: ULONG *pulMtu:接口MTU值
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*  2008-05-14   x36317                  A82D25788:直接访问IFNET_S字段获取,不再调用组件接口,
*                                       避免在关中断期间获取信号量
*
*******************************************************************************/
extern ULONG  TCPIP_GetLinkMtu( ULONG ulIfIndex, ULONG *pulMtu );
/*******************************************************************************
*    Func Name: TCPIP_GetLinkState
*  Description: 获取接口的链路状态
*        Input: ULONG ulIfIndex:接口索引
*               
*       Output: ULONG *pulState:接口状态
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetLinkState( ULONG ulIfIndex, ULONG *pulState );

/*******************************************************************************
*    Func Name: TCPIP_GetIP6LinkState
* Date Created: 2009-03-30
*       Author: tuyan45114
*  Description: 获取接口的IP6链路状态
*        Input: ULONG ulIfIndex:接口索引
*               
*       Output: ULONG *pulState:接口状态
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-30   t45114               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetIP6LinkState(ULONG ulIfIndex, ULONG *pulState);

/*******************************************************************************
*    Func Name: TCPIP_GetPhyCtlBlk
*  Description: 获取接口的物理层控制块
*        Input: ULONG ulIfIndex:
*               ULONG *pulPhyCtlBlk:
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetPhyCtlBlk( ULONG ulIfIndex,UINTPTR *pulPhyCtlBlk );
/*******************************************************************************
*    Func Name: TCPIP_GetPortInfo
*  Description: 根据IFINDEX查询端口类型端口号的API函数
*        Input: ULONG ulIfIndex:接口索引
*               
*       Output: ULONG *pulPortType:接口类型
*               ULONG *pulPortNo:接口号
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG   TCPIP_GetPortInfo( ULONG ulIfIndex, ULONG *pulPortType, ULONG *pulPortNo);
/*******************************************************************************
*    Func Name: TCPIP_IF_LinkIoCtl
*  Description: 链路层IOCTL函数
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulCmdIndex:命令字
*               CHAR *pData:命令字参数
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_IF_LinkIoCtl( ULONG ulIfIndex, ULONG ulCmdIndex, CHAR *pData );
/*******************************************************************************
*    Func Name: TCPIP_IF_LinkReceived
*  Description: 链路层接收报文函数
*        Input: ULONG ulIfIndex:接口索引
*               MBUF_S *pstMbuf:报文
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_IF_LinkReceived( ULONG ulIfIndex,MBUF_S *pstMbuf);
/*******************************************************************************
*    Func Name: TCPIP_OpenIfConfigEntry
*  Description: Open object for IfConfig  
*        Input: 无  
*       Output: ULONG *pulWaitListHandle:指向WaitList Handle的指针
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_OpenIfConfigEntry( UINTPTR *pulWaitListHandle );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncATMLinkIntVTableHook
*  Description: 注册atm接口虚表
*        Input: ATMLinkIntVTable_HOOK_FUNC pfHookFunc:接口虚表指针
*       Output: 无
*       Return: VRP_IFNET_NOERR:成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncATMLinkIntVTableHook( ATMLinkIntVTable_HOOK_FUNC pfHookFunc );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncIFNotifyHook
*  Description: 注册通知链函数
*        Input: ULONG ulType:注册类型
*               ULONG ulPriority:适配函数优先级
*               IF_NOTIFY_FUNC* pfNotifyFn:通知函数
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncIFNotifyHook( ULONG ulType, ULONG ulPriority, VOID *pfNotifyFn );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncLinkMsgSendHook
*  Description: 接口状态变化通知给路由管理模块注册接口
*        Input: LinkMsgSend_HOOK_FUNC pfHookFunc:接口状态变化通知给路由管理模块适配函数
*       Output: 无
*       Return: VRP_IFNET_NOERR:成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncLinkMsgSendHook( LinkMsgSend_HOOK_FUNC pfHookFunc  );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncNotifyIfStateHook
*  Description: 注册接口状态变化通知函数
*        Input: NotifyIfState_HOOK_FUNC pfHookFunc:接口状态变化通知函数
*       Output: 无
*       Return: VRP_IFNET_NOERR:成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncNotifyIfStateHook( NotifyIfState_HOOK_FUNC pfHookFunc );

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPhyIoCtlHook
*  Description: 注册物理层IOCTL函数
*        Input: ULONG ulIfIndex:接口索引
*               IF_PHYIOCTL_FUNC pfPhyIoctl:物理层IOCTL函数
*       Output: 无
*       Return: VRP_IFNET_NOERR:成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncPhyIoCtlHook( ULONG ulIfIndex,IF_PHYIOCTL_FUNC pfPhyIocl );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncPhyTransmitHook
*  Description: 注册物理层发送函数
*        Input: ULONG ulIfIndex:接口索引
*               IF_TRANSMIT_FUNC *pfTransmitFn:物理层发送函数
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncPhyTransmitHook( ULONG ulIfIndex,IF_TRANSMIT_FUNC pfTransmitFn );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncVIOutputHook
*  Description: 注册VI接口链路层发送函数
*        Input: VIOutput_HOOK_FUNC pfHookFunc:VI接口链路层发送函数
*       Output: 无
*       Return: VRP_IFNET_NOERR:成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncVIOutputHook( VIOutput_HOOK_FUNC pfHookFunc );
/*******************************************************************************
*    Func Name: TCPIP_ResumeIf
*  Description: UNSHUTDOWN接口
*        Input: ULONG ulIfIndex:接口索引
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_ResumeIf( ULONG ulIfIndex );
/*******************************************************************************
*    Func Name: TCPIP_SetIfnetHADbg
*  Description: 配置IFNET模块HA调试开关
*        Input: ULONG ulDbg:HA调试开关
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_SetIfnetHADbg( ULONG ulDbg );
/*******************************************************************************
*    Func Name: TCPIP_SetIsisFlag
*  Description: 配置ISIS开关
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulFlag:ISIS开关
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_SetIsisFlag( ULONG ulIfIndex ,ULONG ulFlag );
/*******************************************************************************
*    Func Name: TCPIP_SetKeepAliveValue
*  Description: 配置接口的KEEPALIVE值
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulValue:KEEPALIVE值
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_SetKeepAliveValue( ULONG ulIfIndex, ULONG ulValue );
/*******************************************************************************
*    Func Name: TCPIP_SetLinkMtu
*  Description: 配置接口的MTU值
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulMtu:接口MTU
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_SetLinkMtu( ULONG ulIfIndex, ULONG ulMtu);
/*******************************************************************************
*    Func Name: TCPIP_SetPhyCtlBlk
*  Description: 配置接口的物理层控制块
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulPhyCtlBlk:物理层控制块
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_SetPhyCtlBlk( ULONG ulIfIndex,UINTPTR ulPhyCtlBlk );
/*******************************************************************************
*    Func Name: TCPIP_UnRegFuncIFNotifyHook
*  Description: 注销通知链函数
*        Input: ULONG ulType:注销函数类型
*               IF_NOTIFY_FUNC* pfNotifyFn:通知函数
*       Output: 无
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_UnRegFuncIFNotifyHook ( ULONG ulType, VOID *pfNotifyFn );
/*******************************************************************************
*    Func Name: TCPIP_QosTransmitDone
*  Description: 驱动transmit done通知函数
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulPhyLink:接口链路层控制块
*               MBUF_S *pMBuf:报文
*       Output: 
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-05-08   x00100259               Create
*  2008-09-19   m59090                  Modified(add semaphore protect)
*******************************************************************************/
extern ULONG  TCPIP_QosTransmitDone(ULONG ulIfIndex, UINTPTR ulPhyLink, MBUF_S *pMBuf);
/*扩展支持三维接口相关的用户API*/
/*******************************************************************************
*    Func Name: TCPIP_SetIFDimension
*  Description: 设置本板接口的一二维值，
*        Input: ULONG ulPara1:接口第一维值
*               ULONG ulPara2:接口第二维值
*       Output: 
*       Return: VRP_IFNET_HA_IS_SMOOTHING:  系统处于平滑或手动倒换阶段
                VRP_IFNET_PARA_INVALID:     参数错误
                VRP_IFNET_DIMENSION_MULTI:  多次重复配置
                VRP_IFNET_NOERR:            处理成功
*      Caution: 在协议栈初始化起来后进行配置下发
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIFDimension(ULONG ulPara1, ULONG ulPara2);
/*******************************************************************************
*    Func Name: TCPIP_GetIFDimension
*  Description: 获取本板接口的一二维值
*        Input: 
*               
*       Output: ULONG* pulPara1
                ULONG* pulPara2
*       Return: VRP_IFNET_NULLPOINTER:指针为空
                VRP_IFNET_NOERR:      处理成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIFDimension(ULONG* pulPara1, ULONG* pulPara2);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncInterface3dOutputHook
*  Description: 注册产品发送钩子函数
*        Input: Interface3dOutput_HOOK_FUNC pfHookFunc
*               
*       Output: 
*       Return: VOS_ERR
                VOS_OK
*      Caution:三维模式下,挂在非本板接口的发送函数指针上
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/

extern ULONG TCPIP_RegFuncInterface3dOutputHook(Interface3dOutput_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_GetPortInfoEx
*  Description: 根据接口索引获取接口的一二三维值
*        Input: ULONG ulIfIndex:    接口索引
*               
*       Output: ULONG *pulPortType: 端口类型
                ULONG *pulFirstDim: 接口第一维值
                ULONG *pulSecondDim:接口第二维值
                ULONG *pulThirdDim: 接口第三维值
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

extern ULONG  TCPIP_GetPortInfoEx(ULONG ulIfIndex, 
                                  ULONG *pulPortType, 
                                  ULONG *pulFirstDim,
                                  ULONG *pulSecondDim,
                                  ULONG *pulThirdDim);
/*******************************************************************************
*    Func Name: TCPIP_GetIfindexByPortInfoEx
*  Description: 根据接口类型及接口的一二三维值获取接口索引
*        Input: ULONG ulPortType:   端口类型
*               ULONG pulFirstDim:  接口第一维值
*               ULONG ulSecondDim:接口第二维值
*               ULONG ulThirdDim: 接口第三维值
*       Output: ULONG ulIfIndex:  接口索引
*       Return: VOS_ERR
                VOS_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   wangbin(62223)                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfindexByPortInfoEx(ULONG *pulIfIndex, 
                                          ULONG ulPortType,  
                                          ULONG ulFirstDim,
                                          ULONG ulSecondDim,
                                          ULONG ulThirdDim);
/*******************************************************************************
*    Func Name: TCPIP_SetIpProtocolState
*  Description: 设置三维虚拟接口的IP协议状态
*        Input: ULONG ulIfIndex:
*               ULONG ulState:
                        0:TCPIP_IP_PROTOCOL_UP:     IP协议UP
                        1:TCPIP_IP_PROTOCOL_DOWN:   IP协议DOWN
*       Output: 
*       Return: VRP_IFNET_HA_IS_SMOOTHING:          系统处于平滑或手动倒换阶段
                VRP_IFNET_PARA_INVALID:             参数错误
                VRP_IFNET_NOT_3D_MODE:              非三维模式下
                VRP_IFNET_ENOSUCHIF:                接口指针为空
                VRP_IFNET_NOERR:                    处理成功
*      Caution: 该接口是实接口上上报产品全局管理模块后在分发配置到非本板对应虚接口上
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-14   wangbin62223                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIpProtocolState(ULONG ulIfIndex,ULONG ulState);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetCrossVIAddr
*  Description: 注册钩子函数，以获取出接口为VI的报文源地址
*        Input: TCPIP_GETVIADDR_HOOK_FUNC pfHookFunc: 钩子函数,返回地址为网络序
*       Output: 
*       Return: VOS_OK: 成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-4-2    wujie(61195)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetCrossVIAddr(TCPIP_GETVIADDR_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_QosTransmit
*  Description: 链路层Qos发送函数
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulPhyLink:底层控制块的指针 
*               MBUF_S *pMBuf:指向待发送的报文的指针
*       Output: 无
*       Return: 成功返回VOS_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-06-04   x00100259               Create
*  2008-09-19   m59090                  Modified(add semaphore protect)
*******************************************************************************/
extern ULONG TCPIP_QosTransmit(ULONG ulIfIndex, UINTPTR ulPhyLink, MBUF_S *pMBuf);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncPhySetDevLink
*  Description: 注册初始化设备链的钩子函数
*        Input: PhySetDevLink_HOOK_FUNC pfHookFunc:设备链初始化的钩子函数
*       Output: 
*       Return: 成功: VRP_IFNET_NOERR; 失败: VRP_IFNET_NULLPOINTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-06-17   XiongChangSheng36317    Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPhySetDevLink(PhySetDevLink_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_IF_RegFuncQosTransmitDoneHook
*  Description: 产品向接口IFNET注册QOS发送函数
*        Input: ULONG ulIfIndex: 接口索引
*               IF_QosTransmitDone_HOOK_FUNC pfHookFunc: 注册的函数指针
*       Output: 
*       Return: VRP_IFNET_NOERR: 注册成功/其他: 注册失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-23    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_IF_RegFuncQosTransmitDoneHook(ULONG ulIfIndex, IF_QosTransmitDone_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_IF_RegFuncQosTransmitHook
*  Description: 产品向接口IFNET注册QOS发送函数(有拥塞控制)
*        Input: ULONG ulIfIndex: 
*               IF_QosTransmit_HOOK_FUNC pfHookFunc: 注册的函数指针
*       Output: 
*       Return: VRP_IFNET_NOERR: 注册成功/其他: 注册失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-23    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_IF_RegFuncQosTransmitHook(ULONG ulIfIndex, IF_QosTransmit_HOOK_FUNC pfHookFunc);
extern ULONG TCPIP_CreateDelSubIf( ULONG ulOperType, CHAR* szFullName );
extern ULONG TCPIP_GetIfInfobyFullName(  TCPIP_IFNET_S* pstIfnetInfo, CHAR* szName );
extern ULONG TCPIP_VlinkIoCtl(VLINKSTATUS_S *pVLinkStatus, VOID *pCB);
extern ULONG TCPIP_Vlink6IoCtl(IFVLINKENTRY6_S *pVLinkStatus, VOID *pCB);

/*Add for BC3D00792,DR.131获取链路层状态 start*/
/*******************************************************************************
*    Func Name: TCPIP_GetLinkStatus
* Date Created: 2008-11-25
*       Author: q62011
*  Description: 获取链路层状态信息
*        Input: ULONG ulIfIndex : 接口索引
*       Output: IF_LINKSTATUS_S *pStatus : 返回的链路层状态
*       Return: VRP_IFNET_NOERR   获取成功
*               其它              获取失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-25   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLinkStatus(ULONG ulIfIndex,IF_LINKSTATUS_S *pStatus);
/*Add for BC3D00792,DR.131获取链路层状态 end*/

extern ULONG TCPIP_GetPortInfoByIfNameEx(UCHAR *pucName, ULONG *pulPortType, 
                                        ULONG *pulFirstDim,ULONG *pulSecondDim,
                                        ULONG *pulThirdDim);
extern ULONG TCPIP_GetPortInfoByIfName(UCHAR *pucName,
                                       ULONG *pulPortType, 
                                       ULONG *pulPortNo);

extern ULONG TCPIP_IF_FindNextSubIfIndex( ULONG ulNextSubIfIndex, 
                                          ULONG* ulSubIfIndex);

extern ULONG TCPIP_GetMainIfIndex(ULONG ulIfIndex,ULONG *pulMainIfIndex);

extern ULONG TCPIP_GetPortInfoExSub(ULONG ulIfIndex, ULONG *pulPortType, 
                             ULONG *pulFirstDim,ULONG *pulSecondDim,
                             ULONG *pulThirdDim,ULONG *pulSubPortNum);
                             
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*******************************************************************************
*    Func Name: TCPIP_RegProdIfCheckHook
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 注册产品检查特殊接口的钩子函数
*        Input: IF_PROD_CHECK_HOOK_FUNC pfHookFunc
*       Output: 
*       Return: VOS_OK
                VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegProdIfCheckHook(IF_PROD_CHECK_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_GetVrfByIfIndex
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 获取VRF ID
*        Input: ULONG ulIfIndex:接口索引
*               
*       Output: ULONG *pulVrfIndex:VRF ID
*       Return: 成功或错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetVrfByIfIndex(ULONG ulIfIndex, ULONG *pulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */


ULONG  TCPIP_GetVrf6ByIfIndex(ULONG ulIfIndex, ULONG *pulVrf6Index);

/*****************************************************************************
 函 数 名  : TCPIP_GetIfInfobyFullName
 功能描述  : 根据接口索引获取接口信息
 输入参数  :  
             ULONG ulIfIndex :接口索引             
 输出参数  : TCPIP_IFNET_S* pstIfnetInfo 
 返 回 值  : ULONG
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2009年4月24日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/
extern ULONG TCPIP_GetIfInfobyIfIndex(  TCPIP_IFNET_S* pstIfnetInfo, ULONG ulIfIndex );

/*******************************************************************************
*    Func Name: TCPIP_SetDevLink
* Date Created: 2009-08-04
*       Author: z00104207
*  Description: 设置接口物理参数DEVLINK
*        Input: DEVLINK_S *pstDevLink: 物理参数DEVLINK结构指针
*       Output: 
*       Return: 成功则返回VRP_IFNET_NOERR，失败则返回其他错误码
*      Caution: 操作的接口必须是本板接口，接口类型必须是ETH/PPP/ATM/UI接口
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDevLink(DEVLINK_S *pstDevLink);

/*******************************************************************************
*    Func Name: TCPIP_GetDevLink
* Date Created: 2009-08-04
*       Author: z00104207
*  Description: 获取接口物理参数DEVLINK
*        Input: ULONG ulIfIndex:       接口索引
*       Output: DEVLINK_S *pstDevLink: 物理参数DEVLINK结构指针
*       Return: 成功则返回VRP_IFNET_NOERR，失败则返回其他错误码
*      Caution: 操作的接口必须是本板接口，接口类型必须是ETH/PPP/ATM/UI接口
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDevLink(ULONG ulIfIndex, DEVLINK_S *pstDevLink);

/*******************************************************************************
*    Func Name: TCPIP_ShowDevLink
* Date Created: 2009-08-04
*       Author: z00104207
*  Description: 显示接口的物理参数DEVLINK信息
*        Input: CHAR *szIfName: 接口名字
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   z00104207               Create
*
*******************************************************************************/
extern VOID TCPIP_ShowDevLink(CHAR *szIfName);

/*******************************************************************************
*    Func Name: TCPIP_SetIfEventDebugSwitch
* Date Created: 2009-08-06
*       Author: z00104207
*  Description: 设置底层上报事件调试开关
*        Input: ULONG ulValue: -1(全F)打开所有接口，0关闭；等于接口索引，打开指定接口索引开关。
*       Output: 
*       Return: VRP_IFNET_NOERR:成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-06   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIfEventDebugSwitch(ULONG ulValue);

/*******************************************************************************
*    Func Name: TCPIP_GetIfEventDebugSwitch
* Date Created: 2009-08-06
*       Author: z00104207
*  Description: 获取底层上报事件调试开关
*        Input: 
*       Output: ULONG *pulValue: 获取调试开关指针-1(全F)打开所有接口，0关闭；
*                                等于接口索引，打开指定接口索引开关。
*       Return: VRP_IFNET_NULLPOINTER:参数为空
*               VRP_IFNET_NOERR:      成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-06   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfEventDebugSwitch(ULONG *pulValue);

/*******************************************************************************
*    Func Name: TCPIP_ShowInterfaceByName
* Date Created: 2009-11-13
*       Author: zhangchi(00142640)
*  Description: 根据接口名显示接口信息
*        Input: CHAR *pszIfName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-13   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID TCPIP_ShowInterfaceByName(CHAR *pszIfName);


/*******************************************************************************
*    Func Name: TCPIP_IF_GetISIStatus
* Date Created: 2009-12-15
*       Author: Gexianjun/h00121208
*  Description: 获取接口ISIS状态
*        Input: ULONG ulIfIndex:  接口索引
*       Output: ULONG *pulIfState: 接口ISIS状态
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-15   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_IF_GetISIStatus(ULONG ulIfIndex, ULONG *pulIfState);

/*******************************************************************************
*    Func Name: TCPIP_IF_GetIfNum
* Date Created: 2009-12-15
*       Author: Gexianjun/h00121208
*  Description: 获取接口数目,不包括NULL接口
*        Input: 
*       Output: ULONG *pulIfNum: 接口数目
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-15   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_IF_GetIfNum(ULONG *pulIfNum);

/*******************************************************************************
*    Func Name: TCPIP_IF_GetAllIfIndex
* Date Created: 2009-12-15
*       Author: Gexianjun/h00121208
*  Description: 更根据用户设定的获取接口数目,获取接口数目和接口索引列表,不包括NULL接口
*        Input: ULONG *pulIfNum:  用户需要获取的接口数目
*               ULONG *pulIfIndex:获取的接口索引列表
*       Output: ULONG *pulIfNum:  实际获取的接口数目
*               ULONG *pulIfIndex:获取的接口索引列表
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 接口索引列表pIfIndexList内存由用户分配，内存大小由用户需要获取
*               的接口数目(*pulIfNum)决定, *pulIfNum为输入和输出参数,用户必须
*               在传参数时给*pulIfNum赋值。 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-15   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_IF_GetAllIfIndex(ULONG *pulIfNum, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncLinkMsg6SendHook
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 注册IPv6接口状态变化通知路由管理模块的钩子
*        Input: LinkMsg6Send_HOOK_FUNC pfHookFunc:接口状态变化通知处理钩子
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 只能在光网络定制RM方式下正常使用.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create for VISPV1R8C03
*
*******************************************************************************/
ULONG TCPIP_RegFuncLinkMsg6SendHook(LinkMsg6Send_HOOK_FUNC pfHookFunc);

/* 通知产品创建逻辑接口的钩子函数原型 */
typedef ULONG (*TCPIP_CreateLogicIf_HookFunc)(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncCreateLogicIfHook
* Date Created: 2010-03-11
*       Author: z00104207
*  Description: 注册创建逻辑接口时的对外通知钩子函数
*        Input: TCPIP_CreateLogicIf_HookFunc pfHookFunc: 钩子函数
*       Output: 成功则返回VRP_IFNET_NOERR，否则返回其他错误码
*       Return: 
*      Caution: 用户需判断是否自己关注的接口类型
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-11   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCreateLogicIfHook(TCPIP_CreateLogicIf_HookFunc pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegRtVLinkIndexHook
* Date Created: 2010-09-07
*       Author: wangbin (62223)
*  Description: 注册获取IPC路由的vlink Index
*        Input: IF_GET_VLINK_INDEX_HOOK_FUNC pfHookFunc:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-07   wangbin (62223)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegRtVLinkIndexHook(IF_GET_VLINK_INDEX_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_GetPortInfoSub
* Date Created: 2011-02-23
*       Author: mengzechao/00176865
*  Description: 根据接口索引获取接口类型，接口主接口号和子接口号
*        Input: ULONG ulIfIndex         接口索引 
*       Output: ULONG *pulPortType      接口类型
*               ULONG *pulMainPortNo    主接口号
*               ULONG *pulSubPortNo     子接口号
*       Return: VRP_IFNET_NULLPOINTER   输入指针为空
*               VRP_IFNET_NOT_3D_MODE   配置为三维接口
*               VRP_IFNET_ENOSUCHIF     接口不存在
*               VRP_IFNET_NOERR         执行成功
*      Caution: 1、支持eth子接口，trunk子接口
*               2、支持所有类型主接口。
*                  输入主接口索引时返回主接口编号，子接口编号返回0xffffffff。
*               3、不支持三维接口。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-02-23   mengzechao/00176865         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPortInfoSub(  ULONG ulIfIndex,
                                    ULONG *pulPortType,
                                    ULONG *pulMainPortNo, 
                                    ULONG *pulSubPortNo );

/*******************************************************************************
*    Func Name: TCPIP_GetIfIndexByPortSub
* Date Created: 2010-12-07
*       Author: wangbin (62223)
*  Description: 根据接口类型和接口的一二三维值、子接口号获取对应的接口索引值
*        Input:   
*               ULONG ulPortType:接口类型
*               ULONG ulFirstDim:接口第一维值
*               ULONG ulSecondDim:接口第二维值
*               ULONG ulThirdDim:接口第三维值
*               ULONG ulSubPortNum:子接口号
*       Output: ULONG *pulIfIndex:  接口索引
*       Return: 
*      Caution: 当ulSubPortNum为0则返回主接口对应的索引，否则返回子接口对应的索引值
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-12-07   wangbin (62223)         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfIndexByPortSub(ULONG *pulIfIndex, ULONG ulPortType, 
                          ULONG ulFirstDim,ULONG ulSecondDim,
                          ULONG ulThirdDim,ULONG ulSubPortNum);

/*******************************************************************************
*    Func Name: TCPIP_SetLineStatus
* Date Created: 2014-05-28
*       Author: likaikun213099
*  Description: 设置指定端口的协议状态
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulStatus:  端口协议状态, 1 为UP, 2为DOWN
*       Output: 
*       Return: 
*      Caution: 调用说明：在产品报接口DOWN接口后，UP接口前
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-28   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLineStatus(ULONG ulIfIndex, ULONG ulStatus);

/*******************************************************************************
*    Func Name: TCPIP_Tunn_SetTunnelPara
* Date Created: 2014-11-13
*       Author: wuling201943
*  Description: 
*        Input: ULONG ulIfIndex:隧道接口索引
*               TCPIP_TUNNEL_IF_PPI_S *pstTunnelInfo:隧道配置信息
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-13   wuling201943            Create
*
*******************************************************************************/
extern ULONG TCPIP_Tunn_SetTunnelPara(ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnelInfo);

/*******************************************************************************
*    Func Name: TCPIP_Tunn_GetIfInfoByIfIndex
* Date Created: 2014-11-13
*       Author: wuling201943
*  Description: 
*        Input: ULONG ulIfIndex:  隧道接口索引
*       Output: TCPIP_TUNNEL_IF_PPI_S *pstTunnInfo:隧道配置信息
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-13   wuling201943            Create
*
*******************************************************************************/
ULONG TCPIP_Tunn_GetIfInfoByIfIndex(ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnInfo);

/*******************************************************************************
*    Func Name: TCPIP_Tunn_ShowIfByName
* Date Created: 2014-11-13
*       Author: wuling201943
*  Description: 
*        Input: CHAR *szIfName:tunnel接口名
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-13   wuling201943            Create
*
*******************************************************************************/
ULONG TCPIP_Tunn_ShowIfByName(CHAR *szIfName);

/*******************************************************************************
*    Func Name: TCPIP_Tunn_DelTunnelPara
* Date Created: 2014-11-14
*       Author: wuling201943
*  Description: 
*        Input: ULONG ulIfIndex:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-14   wuling201943            Create
*
*******************************************************************************/
ULONG TCPIP_Tunn_DelTunnelPara(ULONG ulIfIndex);


/*******************************************************************************
*    Func Name: ADDR_AddIP6Address
* Date Created: 2015-03-02
*       Author: wangbin
*  Description: cfg ipv6 addr on host mode
*        Input: CHAR *szIfName:interface name
*               CHAR *szIP6Addr:ipv6 addr
*               ULONG ulIP6PrefixLen:PrefixLen:128,host mode
*               ULONG ulFlag:0 -Global Address support only
*       Output: 
*       Return: 
*      Caution: host mode, ipv6 addr custom-tailor API for balong
*               support global-addr only,support config an ipv6 address only
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-03-02   wangbin          Create
*
*******************************************************************************/
extern ULONG ADDR_AddIP6Address(CHAR *szIfName, CHAR *szIP6Addr,ULONG ulIP6PrefixLen, ULONG ulFlag);



extern ULONG ADDR_DelIP6Address(CHAR *szIfName, CHAR *szIP6Addr,ULONG ulIP6PrefixLen, ULONG ulFlag);


/*******************************************************************************
*    Func Name: ADDR_Set_Mtu
* Date Created: 2015-03-02
*       Author: wangbin
*  Description: set ipv6 if mtu
*        Input: ULONG ulIfIndex
*               ULONG ulMtu
*       Output: 
*       Return: 
*      Caution: host mode, set ipv6 if mtu
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-03-02   wangbin          Create
*
*******************************************************************************/
extern ULONG ADDR_Set_Mtu(ULONG ulIfIndex, ULONG ulMtu);


/*******************************************************************************
*    Func Name: ADDR_IPv6EnableOnIntf_Host
* Date Created: 2015-03-02
*       Author: wangbin
*  Description: Enable/disable IPv6 on host mode
*        Input: CHAR *szIfName
*               ULONG ulFlag
*       Output: 
*       Return: 
*      Caution: host mode, enable ipv6
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-03-02   wangbin          Create
*
*******************************************************************************/
extern ULONG ADDR_IPv6EnableOnIntf_Host(CHAR *szIfName,ULONG ulFlag);


ULONG TCPIP_RegAddrHook(TCPIP_ADDR_HOOK_S *pstAddrHook);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IFNET_API_H_ */

