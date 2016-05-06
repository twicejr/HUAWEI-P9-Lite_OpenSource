

#ifndef _TCPIP_IFDEF_H_
#define _TCPIP_IFDEF_H_

#ifdef  __cplusplus
extern "C"{
#endif
/*IFNET模块SID定义*/

#define SID_COMP_IFNET_S      ( 1 )
/*Begin BC3D01858 liangjicheng 2009-09-22*/
#define SID_COMP_IF_FUNLINK_S ( 2 )
/*End   BC3D01858 */
#define SID_COMP_IF_TUNNEL_S ( 3 )


#define IF_VA_NONE        0   
#define IF_VA_MP          1
#define IF_VA_L2TP        2
#define IF_VA_PPPOE       3
#define IF_VA_PPPOA       4

#define LOGIC_PPPOA       1
#define LOGIC_PPPOE       2 
#define LOGIC_PPPOEOA     3
#define LOGIC_MP          4
#define LOGIC_L2TP        5 
#define LOGIC_NULL        6
#define LOGIC_LOOPBACK    7
#define LOGIC_VT          8
#define LOGIC_MTL         9
#define LOGIC_DIALER     10
#define LOGIC_MFR        11
#define LOGIC_INLOOPBACK 12
#define LOGIC_IPTRUNK    13
#define LOGIC_ETHTRUNK   14
#define LOGIC_VLANIF     15

#define IF_ISIS_ENABLE  1
#define IF_ISIS_DISABLE 0

#define PHY_STATUS_SYN              1
#define PHY_STATUS_ASYN             2


/*VRPV3R001M07_IFNET_XHZ_BEG for R.FUNC.IFNET.014 支持standby操作*/
/*#if (VRP_MODULE_LINK_IB == VRP_YES)*/
#define IF_INTERFACE_UP                 0x1
#define IF_INTERFACE_DOWN               0x2
#define IF_INTERFACE_STANDBY            0x3
/*#endif*/
/*VRPV3R001M07_IFNET_XHZ_END for R.FUNC.IFNET.014 支持standby操作*/


/****************************************************************************************
接口的属性标识

总结(z36377):
   仅当属性中含 IF_FLAG_CREATE 或 IF_FLAG_SUB_IF，才可以动态创建；
   
   仅当属性中含 IF_FLAG_CREATE 且不含 IF_FLAG_LOGIC_IF，才是三维编码的可动态创建接口类型；
       属性中含 IF_FLAG_CREATE | IF_FLAG_LOGIC_IF 时，是一维编码的可动态创建接口类型；
       属性中含 IF_FLAG_LOGIC_IF 但不含 IF_FLAG_CREATE 时，是不可动态创建的逻辑接口；
     若属性中还含有 IF_FLAG_SUB_IF，即表明还可以动态创建子接口。
*****************************************************************************************/
#define IF_FLAG_LOGIC_IF                       (1<<1)          /* 逻辑接口，表明是一维编码 */
#define IF_FLAG_SUB_IF                         (1<<2)          /* 可创建子接口 */
#define IF_FLAG_CREATE                         (1<<3)          /* 可动态创建与删除的接口 */
#define IF_FLAG_SUB_CHANNEL                    (1<<4)          /* 子通道 */
#define IF_FLAG_CONTROLLER                     (1<<5)          /* E1口 */
#define IF_FLAG_INTERFACE                      (1<<6)          /* 非E1口 */

/****************************************************************************
接口类型标识
****************************************************************************/
#define IF_FLAG_ETHERNET             IF_ETHERNET_TYPE   /* 以太网 */
#define IF_FLAG_SERIAL               IF_SERIAL_TYPE     /* 同异步口 */
#define IF_FLAG_ASYNC                IF_ASYNC_TYPE       /* 异步口 */
#define IF_FLAG_BRI                  IF_BRI_TYPE        /* BRI口 */
#define IF_FLAG_DIALER               IF_DIALER_TYPE      /* DDR */
#define IF_FLAG_TUNNEL               IF_TUNNEL_TYPE
#define IF_FLAG_VIRTUAL_TEMPLATE     IF_VIRTUAL_TEMPLATE_TYPE /* 虚模板 */
#define IF_FLAG_E1                   IF_E1_TYPE
#define IF_FLAG_ATM                  IF_ATM_TYPE
#define IF_FLAG_E1GROUP              IF_GROUPE1_TYPE
#define IF_FLAG_AUX                  IF_AUX_TYPE
#define IF_FLAG_VIRTUAL_ETHERNET     IF_VIRTUAL_ETHERNET_TYPE  /* 虚拟ETHERNET */
#define IF_FLAG_POS                  IF_POS_TYPE               /* POS */
#define IF_FLAG_GE                   IF_GIGABYTE_ETHERNET_TYPE /* 千兆ETHERNET */
#define IF_FLAG_NULL                 IF_NULL_TYPE
#define IF_FLAG_LOOPBACK             IF_LOOPBACK_TYPE
#define IF_FLAG_INLOOPBACK           IF_LOOP_TYPE
#define IF_FLAG_LOGIC_TUNNEL         IF_LOGICTUNNEL_TYPE
#define IF_FLAG_MFR                  IF_MFR_TYPE
#define IF_FLAG_MULTILINK            IF_MPGROUP_TYPE   /* mp-group接口*/
#define IF_FLAG_VLAN                 IF_VLAN_TYPE      /* VLAN接口 */
#define IF_FLAG_METH                 IF_METH_TYPE      /* MEth接口 */
#define IF_FLAG_ETH_TRUNK            IF_ETH_TRUNK_TYPE
#define IF_FLAG_IP_TRUNK             IF_IP_TRUNK_TYPE

/*This two flag is useless , just for compile ok*/
#define IF_FLAG_FASTETHERNET    43     /* 原24、25 与其它值冲突，改为此值. z36377*/
#define IF_FLAG_VPN_TUNNEL      42
/*8011*/

#define IF_FLAG_VRRP            41     /* useles now. 原32 可能冲突，改为此值. z36377 */
#define IF_FLAG_LOOP            40     /* useles? 原10 冲突，改为此值. z36377 */

#define IF_MAX_INTERFACE_NUM    64
/*****************************************************************************/

/*****************************************************************************
* 命令操作标识 (接口类的if_ulOpFlag字段中若含有此标识，则该接口类支持此命令) *
******************************************************************************/
#define CLI_OP_FLAG_ClEAR         (1<<1)      /* 标识 clear port 命令 */
/*  Others.....(To be continued.) */


/* for if_ulSubType */
#define IF_SUB_P2P              0x01
#define IF_SUB_MP               0x02    /* 缺省值 */




/*VRPV3R001M07_IFNET_XHZ_END for R.FUNC.IFNET.014 支持standby操作*/
#define IF_OPERATOR_UP            0x100
#define IF_STANDBY                4
#define IF_DELETE                 8
#define IF_BOARD_REMOVE           16
#define IF_PHY_REMOVE             16
#define PASSIVE                   1

/* Added by z43740 for TR报文发送增强, 2009-04-17 */
#define IF_REMOVE                 32  /* 为了显示方便，把IF_REMOVE标志位值有2修改为32 */
#define IF_NO_PHY_SHUTDOWN        2   /* 标识接口Shutdown还没有通知底层 */
/* End of addition */

/* used for if_ulSpoofing */
#define IF_SPOOFING               1

/* used for if_ulMoving */
#define IF_MOVING              0x0001  /* 可删除接口标志 */
#define IF_TEMPIF              0x0002  /* 临时接口标志 */
#define IF_INVISIBLE           0x0004  /* 接口不可见标志 */
#define IF_NOCONFIG            0x0008  /* 接口不可配置标志 */
#define IF_WAITTINGRECOVERY    0x0010 /* 接口配置还没有被恢复,此时不能对接口进行配置*/ 


/* 用于函数 IF_SearchIfFromChain */
#define IF_SEARCH_CHANNEL               0x0001  /* 搜索包括主干、子通道 */
#define IF_SEARCH_SUBIF                 0x0002  /* 搜索包括主干、子接口 */
#define IF_SEARCH_MAIN                  0x0004  /* 只搜索主干 */
#define IF_SEARCH_ONLY_CHANNEL          0x0008  /* 只搜索子通道 */
#define IF_SEARCH_ONLY_SUB              0x0010  /* 只搜索子接口 */

#define IF_SEARCH_ALL                   0x0FFF  /* 搜索所有 */
#define IF_SEARCH_TEMPIF                0x1000  /* 搜索包括临时接口 */

#define IF_CM_NOERR            0
#define IF_CM_ECONGEST         1
#define IF_CM_EDROPS           2
#define IF_CM_ETOOLARGE        3
#define IF_CM_NO_TURNKPORT_UP  4
#define IF_CM_TRUNK_COMP_NULL  5

/* 用于区分主干接口、子接口、子通道 */
#define IF_MAIN_IF             0x0001
#define IF_SUB_IF              0x0002
#define IF_CHANNEL_IF          0x0004

/*增加集中式热插拔和卡热插拔项目    */
#define IFHot_GETSLOTBYPTR(pIf)     ((pIf)->if_ulSlotNum & 0xffff)
#define IFHot_GETADAPTORBYPTR(pIf)  ((pIf)->if_ulSlotNum>>16)
/*end*/

#define IF_TRAP_ENABLE                  1
#define IF_TRAP_DISABLE                 2

#define IF_DEV_RESLEN   12

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
    SIOCAIPISIS,    /*通知链路层，使能ISIS收发功能*/
    SIOCDIPISIS,    /*通知链路层，去使能ISIS收发功能*/
    SIOCIPADDRINVALID,
    /* 提供一个命令字，只是刷新BuildRun信息，但是不通知链路层。*/
    /* 根据问题单D1370 用于从地址的添加 2002/01/11 Chenwejun */
    /* 由于删除和增加从地址都要使用，所以修改名字 2002/01/22 */
    SIOCPROADDRSEC,
    SIOCDADDRSEC,  /* 删除从地址, 通知Eth删除ARP表项. Added by z36377 for SWFD12089 sys VRPD038,20050715*/
    SIOCAIP6LINKLOCALADDR,  /*添加IPV6 Link_Local地址*/
    SIOCAIP6GLOBALADDR,
    SIOCAIP6SITELOCALADDR,    /*增加 IPv6地址*/
    SIOCDIP6LINKLOCALADDR,  /*删除IPV6 Link_Local地址*/
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






/* 接口类型描述 */



#define HOT_TEST  VRP_YES  /*pjmtest*/

/************************************************************************
 * 请在这里填写该头文件的具体内容                                       *
 ************************************************************************/

#define IFQUEUELENGTH                   75
#define IFMSG_QUEUE_MAX_LENGTH          0x1000          /* Max Length of IfMsg Queue */
#define MAX_IF_TYPE_LENGTH              20              /* 接口类型名称长度 */
#define MAX_IF_NAME_LENGTH              47              /* 接口名长度 */
#define MAX_IF_NAME_REAL_LENGTH         27              /* 实际可能的接口名最大长度,
                                                           如: GigabitEthernet15/1/15.1023*/
#define VRP_MAX_INTERFACE_TYPE      20
#define MAX_IF_NUMBER_LENGTH        27 
#define VRP_IFNET_IFINDEXNUM        128             /* 最大索引号 */        /* if_index.c */

/* if_ha定义/使用的错误码 */
#define IFNET_GET_DATA_END         VOS_ERR+2




#define VALUE_OVER                 -1      /* if_tree.c */
#define MAX_LONG                   0xFFFFFFFF      /* if_tree.c */

#define IF_DEFAULT_PROTOCOLLIMIT   30

#define IF_DEFAULT_MTU             1500
#define ETHERMTU                   1500
#define SERIALMTU                  1500
#define ISDNMTU                    1500
#define DIALERMTU                  1500
#define LOMTU                      (1024+512)      /* LoopBack interface MTU */
#define NULLMTU                    (1024+512)      /* NULL interface MTU */
#define DEFAULT_KEEPALIVE          10
#define TUNNELMTU                  1500

#define MIN_ETHERNETMTU            46
#define MIN_OTHERMTU               128
#define MIN_LOMTU                  MIN_ETHERNETMTU
#define MAX_MTU                    1500
#define MAX_MTU_EX               1800
#define MAX_MTU_NEW            1560
#define MIN_TUNNELMTU              46
#define MAX_TUNNELMTU              1536

#define MAX_ATMMTU             2000

#define ATM_INTERFACE_MAX_NUM   1024

#define POS_DEFAULT_MTU         4470 
#define MIN_IF_MTU              328  /* 根据EFU限制所有接口最小值为 328*/

/* Add for DTS2011042601883, by z00171897, at 2011-04-26. 修改原因: 最大MTU改为1492，默认MTU为1450 */
#define MAX_PPPOE_MTU           1492
#define DEFAULT_PPPOE_MTU       1450

#define ETHERSPEED_10M          10000000UL
#define ETHERSPEED_100M         100000000UL


#define IF_MATCH_COMPLETE_HELP          1       /* if_tree.c */
#define IF_MATCH_COMPLETE               2       /* if_tree.c */
#define IF_MATCH_NULL                   3       /* if_tree.c */
#define IF_MATCH_ERROR                  4       /* if_tree.c */
#define IF_MATCH_PART_HELP              5       /* if_tree.c */

#define IF_CHAR_DIAGONAL                '/'     /* if_tree.c */
#define IF_CHAR_DOT                     '.'     /* if_tree.c */
#define IF_CHAR_COLON                   ':'     /* if_tree.c */

#define IF_MALLOC_UNIT                   32              /* if_tree.c */

/*将子接口编号扩大到4095,但子接口数目还保留1024个。  pengjimei 2002/12/04*/
#define IF_SUBINTERFACE_NUMBER          4096
#define IF_FE_SUB_NUMBER                4094    /* FE允许4094个子接口 */
#define IF_GE_SUB_NUMBER                4094    /* GE允许4094个子接口 */

#define IF_ERROR_INDEX_OVER             2       /* if_tree.c */
#define IF_ERROR_VECTOR_MALLOC          3       /* if_tree.c */
#define IF_ERROR_VECTOR_INDEX_MALLOC    4       /* if_tree.c */
#define IF_ERROR_FATHER_NOT_EXIST       5


#define ERROR_NAME          1   /* if_tree.c */
#define ERROR_INDEX         2   /* if_tree.c */
#define ERROR_PARAM         3
#define ERROR_GROUP         4
#define ERROR_SUBINDEX      5

#define TIMESLOT            32

#define MAX_TIMESLOT        31      /* if_intr.c */



#define ATM_DEVFLAG_CARD_TYPE_155M 0
#define    MAXLoopNum      1000
#define    MAXNULLNum      1000
#define    MAXEtherNum     1000
#define    MAXSerialNum    1000
#define    MAXBriNum       1000
#define    MAXPriNum       1000
#define    MAXE1Num        1000
#define    MAXVANum        1000
#define    MAXVTNum        1024
#define    MAXGRETunnelNum 1000
#define    MAXVPNNum       1000
#define    MAXDialerNum    1000
#define    MAXATMNum       1000
#define    MAXPosNum       1000


#define VRP_INTERFACE_NAME_LENGTH   48


#define IF_MATCH_COMPLETE_HELP          1
#define IF_MATCH_COMPLETE               2
#define IF_MATCH_NULL                   3
#define IF_MATCH_ERROR                  4
#define IF_MATCH_PART_HELP              5

#define IF_CHAR_DIAGONAL                '/'
#define IF_CHAR_DOT                     '.'
#define IF_CHAR_COLON                   ':'

#define IF_ORDER_RETURN                 0
#define IF_ORDER_DOT                    1
#define IF_ORDER_COLON                  2
#define IF_ORDER_DIAGONAL               3

#define IF_INDEX_MALLOC                 128

#define IF_DELETE_TIME                  10000

#define MAX_ENABLE_DELAY                400000
#define MAX_DISABLE_DELAY               400000


#define MAX_TEMPLATE            25
#define MILLSEC_PER_SEC         950         /* 1 second = 1000 ms */

#define IF_ALLOW                1
#define IF_NOTCONNECT           2
#define IF_SECONDHELP           4
#define IF_SHOW                 8

#define IF_ADD_INVALID          8   /*if_func.c*/

#define IF_ISNATIVEIF(pIf)              ( (pIf)->if_usSlot == getSelfBoardId() )

#define MAXHELPADDR                             10

#define MAX_ALLOC                               4096L   /* if_tree.c */


#define IF_GET_VA_INVAILD_PARA  0xffffffff
#define IF_GET_VA_INFO_SIZE     4000

#define IF_RPC_DELAY    10000   /* RPC调用延时 */

/*****************************************
 *      系统最大板数                       *
 *****************************************/
/*
 * 对于逻辑槽位的支持，需要增加一个逻辑槽号最大值
 * 用于用户槽号帮助时的逻辑槽号显示的屏蔽，并不在接口名中出现
 * 在判断是否为逻辑槽号的时候，请使用函数 IF_IsLogicalSlot( ULONG )
 */

/*
VRP_MAX_BOARD_NUM       系统最大物理槽号     整个系统使用
IFNET_MAX_BOARD_NUM     系统最大槽号(含逻辑槽号)   接口管理使用，只用于索引操作函数和板状态函数
*/

#define IFNET_MAX_LOGICAL_BOARD         0
#define IFNET_MAX_BOARD_NUM                 (VRP_MAX_BOARD_NUM+IFNET_MAX_LOGICAL_BOARD)

/*******************************************
 *      一块接口板上的接口卡数             *
 *******************************************/
/*#define IFNET_MAX_ADAPTOR_NUM         3 */
#define IFNET_MAX_ADAPTOR_NUM        VRP_MAX_ADAPTOR_NUM

/*******************************************
 *      最大接口数                         *
 *******************************************/
#define IFNET_MAX_NUMBER_NUM          2048  /*在接口描述数组中精确定义*/

/* PPP接口个数上限 */
#define MAX_PPP_NUM 2048

/************************************************************
 *  最大接口维数(以接口名中 '/' 分隔的数来统计)             *
 ************************************************************/
#define IFNET_MAX_DIMENSION    2     /*  */

/************************************************************
 *  三维接口下一二三维值规格             *
 ************************************************************/
#define IFNET_FIRST_DIMENSION_NUM  32

#define IFNET_SECOND_DIMENSION_NUM 32

#define IFNET_THIRD_DIMENSION_NUM 2048


/*******************************************
 *      最大接口名解析深度                    *
 *******************************************/
 /* 例如在三维编码方式下名字最大深度为10，为Serial3/1/0:1.1*/
/* 在三维接口模式下，名字的最大深度是8(VISP目前不支持子接口)，如dialer1/0/1:0，为了防止访问越界，将数组下标改大一些 */
#define IFNET_MAX_IFNAME_INDEX  IFNET_MAX_DIMENSION*2+6

#define IFNET_NO_UPBOARD                                0xff

/*******************************************
 *             IFNET相关四层               *
 *******************************************/
typedef enum tagNETWORK_LAYER
{
    IF_LAYER_IP  = 0,    
    IF_LAYER_IPV6,    
    IF_LAYER_LINK,   
    IF_LAYER_PHISICAL,
    IF_LAYER_MAX
    
}NETWORK_LAYER;

#define IF_DEVICELINK_HEAD      0
#define IF_DEVICELINK_TAIL      1
#define IF_TEMP_DEVICELINK_HEAD 2
#define IF_TEMP_DEVICELINK_TAIL 3

#define IF_INTERFACE_NORMAL 0
#define IF_INTERFACE_VT     1
#define IF_INTERFACE_VA     2

#define IF_MACADDR_LEN      6

/***********************************************************
*  信息索引ID，在输出信息时要注意ID和中英文信息的对应
*
*   与 strIFNET_Info 中的信息必一一对应
************************************************************/
 enum enum_IFNET 
 {
    IFNET_SELECT_INTERFACE, 
    IFNET_TYPE, 
    IFNET_NUMBER, 
    IFNET_NAME, 
    IFNET_SUB_TYPE, 
    IFNET_NEGATE, 
    IFNET_SELECT_CONTROLLER, 
    IFNET_CONTROLLER_TYPE, 
    IFNET_CONTROLLER_NUMBER, 
    IFNET_CONTROLLER_NAME, 
    IFNET_TIMESLOT_PRI, 
    IFNET_LIST_TIMESLOT_PRI, 
    IFNET_TIMESLOT_NUMBER_LIST, 
    IFNET_E1_TIMESLOT_NUMBER_LIST, 
    IFNET_T1_TIMESLOT_NUMBER_LIST, 
    IFNET_SHUT, 
    IFNET_LINK_LIMIT, 
    IFNET_LIMIT_VALUE, 
    IFNET_SET_MTU, 
    IFNET_MTU_VALUE, 
    IFNET_BIND_TIMESLOT, 
    IFNET_CHANNEL_NUMBER, 
    IFNET_TIMESLOT, 
    IFNET_RESET,
    IFENT_COUNTERS,
    IFNET_INTERFACE,
    IFNET_SET_DESC, 
    IFNET_DESC_80, 
    IFNET_SET_KEEPALIVE, 
    IFNET_TIMER,
    IFNET_KEEPALIVE_VALUE, 
    IFNET_ENABLE,
    IFNET_QOS, 
    IFNET_SET_BANDWIDTH, 
    IFNET_BANDWIDTH_VALUE, 
    IFNET_SNMP,
    IFNET_ALLOW_SNMPTRAP, 
    IFNET_ALLOW_LINKUPDOWN, 
    IFNET_SHOW_RUN, 
    IFNET_SHOW_INTERFACE, 
    IFNET_SHOW_CONTROLLER, 
    /*D18713*/
    IFNET_SHUT_NO_INTERFACE,
    IFNET_HAVE_BEEN_SHUT,
    IFNET_NOT_HAVE_BEEN_SHUT,
    /*D18840*/
    IFNET_CONTROLLER_HAVE_BEEN_SHUT,
    IFNET_CONTROLLER_NOT_HAVE_BEEN_SHUT,
    IFNET_KEEPALIVE_VALUE_TOOBIG,
    IFNET_CAN_NOT_SUB_INTERFACE,
    IFNET_DESC_TOO_LONG,
    IFNET_TEMP_INTERFACE,
    IFNET_CHAN_EXIST,
    IFNET_GROUP_USED,
    IFNET_GROUP_SOME_USED,
    IFNET_INTERFACE_DELETED,
    IFNET_LOGIC_ENHENCE1,
    IFNET_LOGIC_ENHENCE2,
    IFNET_LOGIC_ENHENCE5,
    IFNET_LOGIC_ENHENCE6,
    IFNET_LOGIC_ENHENCE7,
    IFNET_LOGIC_ENHENCE8,
    IFNET_LOGIC_ENHENCE9,
    IFNET_LOGIC_ENHENCE10,
    IFNET_LOGIC_ENHENCE11,
    IFNET_LOGIC_ENHENCE12,
    IFNET_LOGIC_ENHENCE13,
    IFNET_LOGIC_ENHENCE14,
    IFNET_TIME_NOPRI,
    IFNET_SHOW_INTERFACE_DETAIL, 
    IFNET_SHOW_CONTROLLER_DETAIL, 
    IFNET_UP,
    /*将子接口编号扩大到4095,但子接口数目还保留1024个。  pengjimei 2002/12/04*/
    IFNET_MORE_SUBINTERFACE_ERROR,  
    IFNET_MAX 
};


/*************************************************************************
*  信息索引ID，在输出信息时要注意ID和中英文信息的对应
*
*   与 Msg_Router_En中的信息必一一对应
**************************************************************************/
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

/* if 二三层标记宏定义 */
#define SWITCHPORT_L3IF             0
#define SWITCHPORT_L2IF_PORT        1
#define SWITCHPORT_L2IF_TRUNKPORT   2

/* 判断是否为2/3层ETH/TRUNK口 */
#define IF_IS_L2ETH(pstIf) ((LINE_ETHERNET == (pstIf)->if_ulLineProtocol) && \
             ((SWITCHPORT_L2IF_PORT == (pstIf)->if_ulL2OrL3) || (SWITCHPORT_L2IF_TRUNKPORT == (pstIf)->if_ulL2OrL3)))

#define IF_IS_L2TRUNKPORT(pstIf) (SWITCHPORT_L2IF_TRUNKPORT == (pstIf)->if_ulL2OrL3)
                 
#define IF_IS_L3ETH(pstIf) ((LINE_ETHERNET == (pstIf)->if_ulLineProtocol) && (SWITCHPORT_L3IF== (pstIf)->if_ulL2OrL3))

#define IF_IS_L2TRUNK(pstIf) ((LINE_ETHERNET == (pstIf)->if_ulLineProtocol) && \
                            (SWITCHPORT_L2IF_PORT == (pstIf)->if_ulL2OrL3) && \
                            (IF_ETH_TRUNK_TYPE == (pstIf)->if_ulType))

#define IF_IS_L2PORT(pstIf) ((LINE_ETHERNET == (pstIf)->if_ulLineProtocol) \
                            && (SWITCHPORT_L2IF_PORT == (pstIf)->if_ulL2OrL3))


/* OAM状态 */
#define IF_DETECT_EFMSTATUS    0x3
#define IF_DETECT_EFMUP        0x1
#define IF_DETECT_EFMDOWN      0x2

#define IF_IS_EFMINIT(pIf)     (IF_NORMAL == (pIf->if_ulPhyDetectStatus & IF_DETECT_EFMSTATUS))
#define IF_IS_EFMUP(pIf)       (IF_DETECT_EFMUP == (pIf->if_ulPhyDetectStatus & IF_DETECT_EFMSTATUS))
#define IF_IS_EFMDOWN(pIf)     (IF_DETECT_EFMDOWN == (pIf->if_ulPhyDetectStatus & IF_DETECT_EFMSTATUS))  

/* OAM-3ah协议为DOWN则物理状态为DOWN，否则等于真实物理状态*/
#define IF_COMBINE_PHYSTATUS(pIf)                       \
{                                                       \
    if(IF_IS_EFMDOWN(pIf))                              \
    {                                                   \
        IF_SET_PHYSTATUS(pIf, IF_STATUS_DOWN);          \
    }                                                   \
    else                                                \
    {                                                   \
        IF_SET_PHYSTATUS(pIf, pIf->if_ulRawPhyStatus);  \
    }                                                   \
}

/* 底层上报状态UP，置接口原始物理状态为UP，并与OAM-3ah状态叠加计算出接口物理状态 */
#define IF_SET_PHYUP(pIf)                           \
{                                                   \
    pIf->if_ulRawPhyStatus = IF_STATUS_UP;          \
    IF_COMBINE_PHYSTATUS(pIf);                      \
}

/* 底层上报状态DOWN，置接口原始物理状态为DOWN，并与OAM-3ah状态叠加计算出接口物理状态 */
#define IF_SET_PHYDOWN(pIf)                         \
{                                                   \
    pIf->if_ulRawPhyStatus = IF_STATUS_DOWN;        \
    IF_COMBINE_PHYSTATUS(pIf);                      \
}

/* add by L00105073 for 主备倒换后PPP重协商 */
#define IF_SET_RAWPHYSTATUS(pIf, ulRawPhyStatus)    \
{                                                   \
    if ((ulRawPhyStatus) == IF_STATUS_UP)           \
    {                                               \
        IF_SET_PHYUP(pIf);                          \
    }                                               \
    else                                            \
    {                                               \
        IF_SET_PHYDOWN(pIf);                        \
    }                                               \
}

/* OAM-3ah上报状态init，置接口OAM状态为init，并与接口原始物理状态叠加计算出接口物理状态 */
#define IF_SET_EFMINIT(pIf)\
{\
        pIf->if_ulPhyDetectStatus &= ~IF_DETECT_EFMSTATUS;\
        IF_COMBINE_PHYSTATUS(pIf);\
}
/* OAM-3ah上报状态UP，置接口OAM状态为UP，并与接口原始物理状态叠加计算出接口物理状态 */
#define IF_SET_EFMUP(pIf)\
{\
        pIf->if_ulPhyDetectStatus &= ~IF_DETECT_EFMSTATUS;\
        pIf->if_ulPhyDetectStatus |= IF_DETECT_EFMUP;\
        IF_COMBINE_PHYSTATUS(pIf);\
}
/* OAM-3ah上报状态DOWN，置接口OAM状态为DOWN，并与接口原始物理状态叠加计算出接口物理状态 */
#define IF_SET_EFMDOWN(pIf)\
{\
        pIf->if_ulPhyDetectStatus &= ~IF_DETECT_EFMSTATUS;\
        pIf->if_ulPhyDetectStatus |= IF_DETECT_EFMDOWN;\
        IF_COMBINE_PHYSTATUS(pIf);\
}

/* 设置端口的物理状态并记录UP/DOWN变化次数 */
#define IF_SET_PHYSTATUS(pIf, ulPhyStatus)\
{\
    ULONG ulSetPhyStatus = ulPhyStatus;\
    if (IF_STATUS_UP == ulSetPhyStatus)\
    {\
        if (IF_STATUS_UP != pIf->if_ulPhyStatus)\
        {\
             pIf->if_ulPhyStatus = IF_STATUS_UP; \
             pIf->if_ulPhyUpCount++;\
        }\
    }\
    else if (IF_STATUS_DOWN == ulSetPhyStatus)\
    {\
        if (IF_STATUS_DOWN != pIf->if_ulPhyStatus)\
        {\
            pIf->if_ulPhyStatus = IF_STATUS_DOWN; \
            pIf->if_ulPhyDownCount++;\
        }\
    }\
    else\
    {\
        pIf->if_ulPhyStatus = ulPhyStatus;\
    }\
}

/* 设置端口的协议状态并记录UP/DOWN变化次数 */
#define IF_SET_LINESTATUS(pIf, ulLineStatus)\
{\
    if (NULL != pIf)\
    {\
        ULONG ulSetLineStatus = ulLineStatus;\
        if (IF_STATUS_UP == ulSetLineStatus)\
        {\
            if (IF_STATUS_UP != pIf->if_ulLineStatus)\
            {\
                 pIf->if_ulLineStatus = IF_STATUS_UP; \
                 pIf->if_ulLineUpCount++;\
            }\
        }\
        else if (IF_STATUS_DOWN == ulSetLineStatus)\
        {\
            if (IF_STATUS_DOWN != pIf->if_ulLineStatus)\
            {\
                pIf->if_ulLineStatus = IF_STATUS_DOWN; \
                pIf->if_ulLineDownCount++;\
            }\
        }\
        else\
        {\
            pIf->if_ulLineStatus = ulLineStatus;\
        }\
    }\
}

#define ETH_MAC_BAK_SMOOTH_ACT      1  /* 主备physical地址一致，平滑后生效 */
#define ETH_MAC_BAK_REALTIME_ACT    2  /* 主备physical地址一致，实时生效 */

#if (TCPIP_MODULE_MINI == VRP_YES)
#define IF_MAP_MAC_INTERFACEID(enaddr , interfaceid) \
{ \
   (interfaceid)[0] = (enaddr)[0] | (CHAR)0x02; \
   (interfaceid)[1] = (enaddr)[1];  \
   (interfaceid)[2] = (enaddr)[2];  \
   (interfaceid)[3] = (CHAR)  0xff; \
   (interfaceid)[4] = (CHAR)  0xfe; \
   (interfaceid)[5] =(enaddr)[3]; \
   (interfaceid)[6] =(enaddr)[4]; \
   (interfaceid)[7] =(enaddr)[5]; \
}
#endif

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TCPIP_IFDEF_H_ */



