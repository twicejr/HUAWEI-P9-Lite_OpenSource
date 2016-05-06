#ifndef _RM_API_H
#define _RM_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

/*l61496 2008-11-4 添加条件编译*/
#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH            47              /* 接口名长度 */
#endif

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define RM_MAX_VRF_NAME_LENGTH        31
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define RM_USR_DSCP_LEN               19
#define RM_IPV6_ADDRESS_WORD_LEN      16

#define RM_INETWK_ADDR_TYPE_IPV4         0x00000001
#define RM_INETWK_ADDR_TYPE_IPV6         0x00000002

/*static route 's max number*/
/* mody for BC3D03406 at 2010-06-24 */
/*#define MAX_STATIC_ROUTE_NUM         1024 */

/* modified by jijianhua For MCCP routeing extend                             */
/* 10K -> 25K                                                                 */
/* checked with SGSN, No impact, as SGSN has its own limition                 */
#define MAX_STATIC_ROUTE_NUM         25000 
/* end of modification by jijianhua                                           */

/*equal route 's max number*/
#define MAX_EQUAL_ROUTE_NUM          16
#define MAX_STATIC_ROUTE_COST        0xFFFF


/*static route's ulOper*/
#define RM_CFGAPI_OPER_CREATE  1
#define RM_CFGAPI_OPER_DELETE  0
#define RM_CFGAPI_OPER_ENABLE  1
#define RM_CFGAPI_OPER_DISABLE 0


/*static route's ulAction*/
#define ROUTE_ACTION_LOCAL           0x01
#define ROUTE_ACTION_FORWARD         0x02
#define ROUTE_ACTION_REJECT          0x03
#define ROUTE_ACTION_DISCARD         0x04

/*API's parameter - ulInstance*/
/*RIB/ACRT/静态路由的实例号查找类型,当RM_FILTER_RTMINST被使用时才有效 */
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define RM_INSTANCE_IPV4            1
#define RM_INSTANCE_IPV6            2
#define RM_API_TYPE_IPV4            1
#define RM_API_TYPE_IPV6            2
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*RIB/ACRT/静态路由的查找过滤标记- 结构RM_RIB_FILTER_S 和RM_ACRT_FILTER_S中字段ulFilterFlag*/
#define RM_CFGAPI_SHOW_ALL           0 
#define RM_CFGAPI_SHOW_WITH_FILTER   1

/*RIB/ACRT查找过滤器类型，可以组合使用*
*  - 结构RM_RIB_FILTER_S 和RM_ACRT_FILTER_S中字段ulFilterLevel*/
#define RM_FILTER_RTMINST   0x00000001
#define RM_FILTER_DESTADDR  0x00000010
#define RM_FILTER_MASK      0x00000100
#define RM_FILTER_PROTOCOL  0x00001000
#define RM_FILTER_RPMINDEX  0x00010000
#define RM_FILTER_VRF       0x00100000

/*RIB/ACRT 协议查询类型，直连/静态/RIP/OSPF,
* 当 RM_FILTER_PROTOCOL 被使用时才有效*/
#define RM_PROTO_CONNECTED  0x2  
#define RM_PROTO_STATIC     0x3
#define RM_PROTO_RIP        0x8
#define RM_PROTO_OSPF       0xD
#define RM_PROTO_VLINK      0x12
#define RM_PROTO_DHCP       0x13
/* Modified by lixs00177467, for rtm net route, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
#define RM_PROTO_NET        0x14
#define RM_PROTO_RIPNG      0x18
#define RM_PROTO_OSPF6      0x1D


/*OSPF子协议类型*/
#define RM_SUBPROT_OSPF_INTRA_AREA           0x000D0000
#define RM_SUBPROT_OSPF_INTER_AREA           0x000D0001
#define RM_SUBPROT_OSPF_TYPE1_EXT            0x000D0002
#define RM_SUBPROT_OSPF_TYPE2_EXT            0x000D0003
#define RM_SUBPROT_OSPF_NSSA1                0x000D0004
#define RM_SUBPROT_OSPF_NSSA2                0x000D0005

/*RIB/ACRT 路由查询时，route type类型*/
#define RM_ROUTE_TYPE_OTHER                    1
#define RM_ROUTE_TYPE_REJECT                   2
#define RM_ROUTE_TYPE_LOCAL                    3
#define RM_ROUTE_TYPE_REMOTE                   4

/*静态路由使能状态*/
#define RM_STATIC_ROUTE_ENABLE        1
#define RM_STATIC_ROUTE_DISABLE       0

/*Add begin by t00110672 for BC3D01783,   质量活动，消除魔鬼数字*/
#define RM_TRUE        1
#define RM_FALSE       0

#define RM_IPV4_ADDRESS_LEN     4
#define RM_IPV4_MASK_LEN     32
/*End*/
typedef struct tagRM_CFG_USR4
{
    ULONG ulOper; /*配置或删除；0-delete；1-create*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*出接口名字*/
    ULONG ulRtPri;/*路由优先级，默认为1，取值1-255*/
    ULONG ulDestAddr;/*目的地址*/
    ULONG ulMask;/*掩码，取值0-32*/
    ULONG ulNextHopAddr;/*下一跳或网关地址*/
    ULONG ulAction; /*静态路由的ACTION类型*/
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*路由描述 19 bytes*/
    ULONG ulPathCost;/*路径cost值，取值0－0xFFFF*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_CFG_USR4_S;

typedef struct tagRM_ENABLE_USR4
{
    ULONG ulOper; /*使能或去使能；0-disable；1-enable*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*出接口名字*/
    ULONG ulDestAddr;/*目的地址*/
    ULONG ulMask;/*掩码，取值0-32*/
    ULONG ulNextHopAddr;/*下一跳或网关地址*/
    ULONG ulAction; /*静态路由的ACTION类型*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_ENABLE_USR4_S;

typedef struct tagRM_MOD_USR4
{
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*出接口名字*/
    ULONG ulRtPri;/*路由优先级，默认为1，取值1-255*/
    ULONG ulDestAddr;/*目的地址*/
    ULONG ulMask;/*掩码，取值0-32*/
    ULONG ulNextHopAddr;/*下一跳或网关地址*/
    ULONG ulAction; /*静态路由的ACTION类型*/
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*路由描述 19 bytes*/
    ULONG ulPathCost;/*路径cost值，取值0－0xFFFF*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_MOD_USR4_S;

typedef struct tagRM_CFG_USR6
{
    ULONG ulOper; /*配置或删除；0-delete；1-create*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*出接口名字*/
    ULONG ulRtPri;/*路由优先级，默认为1，取值1-255*/
    UCHAR aucDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址 4*4 bytes*/
    ULONG ulPrefixLen;/*前缀长度，取值0-128*/
    UCHAR aucNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*下一跳或网关地址 4*4 bytes*/
    ULONG ulAction; /*静态路由的ACTION类型*/   
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*路由描述 19 chars*/
    ULONG ulPathCost;/*路径cost值，取值0－0xFFFF*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_CFG_USR6_S;

typedef struct tagRM_MOD_USR6
{
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*出接口名字*/
    ULONG ulRtPri;/*路由优先级，默认为1，取值1-255*/
    UCHAR aucDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址 4*4 bytes*/
    ULONG ulPrefixLen;/*前缀长度，取值0-128*/
    UCHAR aucNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*下一跳或网关地址 4*4 bytes*/
    ULONG ulAction; /*静态路由的ACTION类型*/   
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*路由描述 19 chars*/
    ULONG ulPathCost;/*路径cost值，取值0－0xFFFF*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_MOD_USR6_S;

typedef struct tagRM_RIB_FILTER
{
    ULONG ulFilterFlag; /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulFilterLevel;/*过滤器使用及组合情况*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*根据IPv4或者IPv6实例号过滤*/
    ULONG ulType;/*根据IPv4或者IPv6类型过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*根据路由目的地址过滤*/
    ULONG ulMask; /*根据路由掩码过滤，取值0-128*/    
    ULONG ulProtocol; /*根据路由协议号过滤*/ 
    ULONG ulProcessId; /*根据提供路由的进程ID过滤*/   
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*根据路由目的地址过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_RIB_FILTER_S;

typedef struct tagRM_ACRT_FILTER
{
    ULONG ulFilterFlag; /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulFilterLevel;/*过滤器使用及组合情况*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*根据IPv4或者IPv6实例号过滤*/
    ULONG ulType;/*根据IPv4或者IPv6类型过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*根据路由目的地址过滤*/
    ULONG ulMask; /*根据路由掩码过滤，取值0-128*/     
    ULONG ulProtocol; /*根据路由协议号过滤*/ 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*根据路由目的地址过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_ACRT_FILTER_S;

typedef struct tagRM_STATIC_FILTER
{
    ULONG ulFilterFlag; /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulFilterLevel;/*过滤器使用及组合情况*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*根据IPv4或者IPv6实例号过滤*/
    ULONG ulType;/*根据IPv4或者IPv6实例号过滤*/
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*根据路由目的地址过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_STATIC_FILTER_S;

/* Modified by lixs00177467, for rtm net route, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
typedef struct tagRM_NETRT_FILTER
{
    ULONG ulIfIndex;/*接口索引,0为不过滤,非0为指定接口索引*/
}RM_NETRT_FILTER_S;
/*End of Modified by lixs00177467, 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */

/*********************注意******************************
l61496: RM_DSP_ACRT_S的结构和RM_DSP_RIB_S始终只相差一个字段
        LONG lFibRoute 
*********************************************************/
typedef struct tagRM_DSP_RIB
{
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*根据IPv4或者IPv6实例号过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址*/
    ULONG ulMask;/*掩码，取值0-128*/
    UCHAR szNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*下一跳地址*/
    UCHAR szRelayNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*依赖下一跳地址*/
    ULONG ulExitIf; /*出接口*/
    ULONG ulRoutetype;  /*路由类型，表示路由是本机，还是转发*/
    ULONG ulProto;  /*路由协议8-RIP;13-OSPF;*/  
    ULONG ulSubProto;  /*路由子协议，只对OSPF有效;*/  
    ULONG ulRouteAge; /*路由老化时间*/
    ULONG ulPriority; /*优先级*/ 
    LONG lMetric1; /*cost值*/
    LONG lMetric2; /*cost值，RIP无效，OSPF有效*/
    ULONG ulFibRoute;  /*是否下到FIB，1-下到FIB中，0-没有下到FIB中*/ 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*根据路由目的地址过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    /* Begin BC3D01402 l00147446 增加ulType(区别IPV4/IPV6) 09-04-13*/
    ULONG ulType;
    /* End BC3D01402 l00147446 增加ulType(区别IPV4/IPV6) 09-04-13*/
}RM_DSP_RIB_S;


typedef struct tagRM_DSP_ACRT
{
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*根据IPv4或者IPv6实例号过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址*/
    ULONG ulMask;/*掩码，取值0-128*/
    UCHAR szNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*下一跳或网关地址*/
    UCHAR szRelayNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*依赖下一跳地址*/
    ULONG ulExitIf; /*出接口*/
    ULONG ulRoutetype;  /*路由类型，表示路由是本机，还是转发*/
    ULONG ulProto;  /*路由协议8-RIP;13-OSPF;*/    
    ULONG ulSubProto;  /*路由子协议，只对OSPF有效;*/  
    ULONG ulRouteAge; /*路由老化时间*/
    ULONG ulPriority; /*优先级*/
    LONG lMetric1; /*cost值*/
    LONG lMetric2; /*cost值，RIP无效，OSPF有效*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*根据路由目的地址过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    
    /* Begin BC3D01402 l00147446 增加ulType(区别IPV4/IPV6) 09-04-13*/
    ULONG ulType;
    /* End BC3D01402 l00147446 增加ulType(区别IPV4/IPV6) 09-04-13*/
}RM_DSP_ACRT_S;


typedef struct tagRM_DSP_STATICRT
{
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*根据IPv4或者IPv6实例号过滤*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址*/
    ULONG ulMask;/*掩码，取值0-128*/
    UCHAR szNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*下一跳或网关地址*/
    ULONG ulExitIf; /*出接口*/
    ULONG ulPriority; /*优先级*/
    ULONG ulPathCost; /*Cost*/  /*Add by q62011 for BC3D00968*/
    ULONG ulAdminStat; /*管理状态，1-使能状态，0-去使能状态*/
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*路由描述 19 chars*/
    
    /* Begin BC3D01402 l00147446 增加ulType(区别IPV4/IPV6) 09-04-13*/
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*根据路由目的地址过滤*/
    ULONG ulType;
    /* End BC3D01402 l00147446 增加ulType(区别IPV4/IPV6) 09-04-13*/
    
    ULONG loose_num;
    /*Mod End*/
}RM_DSP_STATICRT_S;

/*RTM概要信息数据结构*/
typedef struct tagRM_BRIEF_INFO
{
  CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];  /*VRF NAME*/
  ULONG ulEqualCostOpt;              /* 当RPM向RTM查询路由时，如果存在平衡路由，是返回所有平衡路由还是只返回其中一条,*/
                                                 /*AMB_RTM_EQUAL_COST_ALL ---返回所有平衡路由、AMB_RTM_EQUAL_COST_ONE ---返回其中一条,*/
                                                 /*默认：AMB_RTM_EQUAL_COST_ALL;  */
  ULONG ulAddrFamily;                 /* 协议族.默认: AMB_INETWK_ADDR_TYPE_IPV4; */
  ULONG ulTotalRouteNum;             /* 当前路由表中的路由总数*/   
  ULONG ulActRouteNum;             /* 当前路由表中激活的路由数*/                                       
  ULONG ulStaticRouteNum;          /*当前路由表中静态的路由数*/
  ULONG ulActStaticRouteNum;          /*当前路由表中静态的路由数*/
  ULONG ulFromOspfRtNum;          /*当前路由表中来自OSPF的路由数*/
  ULONG ulFromRipRtNum;             /*当前路由表中来自RIP的路由数*/
  ULONG ulVlinkRtNum;                 /*当前路由表中的Vlink路由个数*/
  ULONG ulConnectRtNum;            /*当前路由表中的直连路由个数*/
}RM_BRIEF_INFO_S;

typedef struct tagRM_BRIEF_FILTER
{
    ULONG ulFilterFlag;    /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulFilterLevel;  /*过滤器使用及组合情况*/
    ULONG ulType;/*根据IPv4或者IPv6实例号过滤*/
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*根据VRF过滤，如果不填，显示所有的*/
}RM_BRIEF_FILTER_S;

/* Modified by lixs00177467, for rtm net route, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
typedef struct tagRM_DSP_NETRT
{
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址*/
    ULONG ulPrefixLen;/*前缀长度*/
    UCHAR szNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*下一跳或网关地址*/
    ULONG ulIfIndex; /*出接口*/
}RM_DSP_NETRT_S;
/*End of Modified by lixs00177467, 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */

typedef enum enumRMError
{
    RM_OK = 0,
    /*以下错误码由DCL通过mib机制直接返回,只有IPS返回的时候才使用*/
    /*Modified begin by t00110672 for BC3D01783,   质量活动，错误码基数调整*/
    RM_NO_ERROR,                 /*成功*/
    RM_ERR_GEN_ERROR = MID_COMP_RTM + 2,
    /*End*/
    RM_ERR_WRONG_VALUE,                             /*MIB配置的值错误*/
    RM_ERR_INCONSISTENT_VALUE,                      /*MIB配置的值不一致*/
    RM_ERR_RESOURCE_UNAVAILABLE,                    /*MIB配置的资源无效*/
    RM_ERR_NO_SUCH_OBJECT,                          /*对象不存在*/
    RM_ERR_AMB_RC_END_OF_TABLE,                     /*表项结束*/
    RM_ERR_AGENT_ERROR,
    RM_ERR_INCOMPLETE,
    RM_ERR_PARTIAL_FAMILY_OK,
    RM_ERR_PRODUCT_NOT_READY,
    RM_ERR_CFG_TIME_OUT = MID_COMP_RTM + 15,        /*15*/
    /*以下API内部通用类错误码*/
    RM_ERR_ADDR_LINKLOCAL,
    RM_ERR_PARA, 
    RM_ERR_MALLOC_FAILED,
    RM_ERR_HANDLE_IS_NOT_EXSIT,
    RM_ERR_CONF_DATA_IS_NULL,                       /*20*/
    RM_ERR_CONN_CB_IS_NULL,
    RM_ERR_RETURN_IPS_IS_NULL,
    RM_ERR_REDIST_STEP,
    /*以下API内部专用类错误码*/    
    RM_ERR_ACTIONTYPE,
    RM_ERR_ROUTE_ACTION,
    RM_ERR_ENABLE,
    RM_ERR_INSTANCE,
    RM_ERR_IFNAME,
    RM_ERR_IFLLOOPBACK,
    RM_ERR_IFNULL,                                  /*30*/
    RM_ERR_RTPRI,
    RM_ERR_DESTADDR,
    RM_ERR_DESTADDR_1,
    RM_ERR_DESTADDR_2,
    RM_ERR_DESTADDR_3,
    RM_ERR_MASK,
    RM_ERR_HOPADDR,
    RM_ERR_HOPADDR_1,
    RM_ERR_HOPADDR_2,
    RM_ERR_HOPADDR_3,                               /*40*/
    RM_ERR_NOT_HOPIFNAME,
    RM_ERR_NOT_PPP_LINE,
    RM_ERR_MAX_SROUTE_NUM,
    RM_ERR_ADDRFAMILY,
    RM_ERR_PROTO,
    RM_ERR_IF_NH_CHECK,
    RM_ERR_EQUAL_ROUTE_NUM,
    RM_ERR_DIRECT_ROUTE_COST,
    RM_ERR_STATIC_ROUTE_COST,
    RM_ERR_DESTACL_NUM,                             /*50*/
    RM_ERR_POINTER_IS_NULL,                         /*指针为空*/
    RM_ERR_RTM_HAVE_NOT_ENABLE,                     /*RTM还没有创建*/
    RM_ERR_CAN_NOT_FIND_ROUTE,                      /*找不到路由*/
    RM_ERR_CAN_NOT_FIND_NEXT_ROUTE,                 /*找不到下一条路由*/
    RM_ERR_HANDLE_IS_NULL,
    RM_ERR_INVALID_VERSION,                         /*错误的版本，非IPV4，非IPV6*/
    RM_ERR_REDIST_SRCINST_FILTER,
    RM_ERR_REDIST_DESTINST_FILTER,
    RM_ERR_REDIST_IFINDEX_FILTER,
    RM_ERR_REDIST_OSPFAREA_FILTER,                  /*60*/
    RM_ERR_REDIST_OSPFTAG_FILTER,
    RM_ERR_REDIST_FLAG_FILTER,
    RM_ERR_REDIST_PATHTYPE_FILTER,
    RM_ERR_REDIST_DESTACL_FILTER,
    RM_ERR_REDIST_PRIORITY,
    RM_ERR_REDIST_DIRECTFLAG,
    RM_ERR_REDIST_RIP_COST,
    RM_ERR_REDIST_OSPF_COST,
    RM_ERR_REDIST_METRIC_CONV,
    RM_ERR_REDIST_POLICY_NOT_EXIST,                 /*70*/
    RM_ERR_REDIST_SRCPROTO,
    RM_ERR_REDIST_PROTO_NO_PROCESS,
    RM_ERR_REDIST_NO_SRC_PROCESS,
    RM_ERR_REDIST_SRC_SAME_PROTO,
    RM_ERR_REDIST_SRC_SAME_PROCESS,
    RM_ERR_REDIST_DESTPROTO_1,
    RM_ERR_REDIST_DESTPROTO_2,
    RM_ERR_REDIST_NO_DEST_PROCESS,
    RM_ERR_REDIST_DEST_SAME_PROTO,
    RM_ERR_REDIST_DEST_SAME_PROCESS,                /*80*/
    RM_ERR_REDIST_SRC_NOT_OSPF_1,
    RM_ERR_REDIST_SRC_NOT_OSPF_2,
    RM_ERR_REDIST_RIP_NO_PATHTYPE,
    RM_ERR_REDIST_RIP_NO_OSPFTAG,
    RM_ERR_REDIST_OSPF_PATHTYPE,
    RM_ERR_REDIST_OSPF_OSPFTAG,  
    RM_ERR_REDIST_NO_SRC_DEST,
    RM_ERR_REDIST_MAX_POLICY_NUM,
    RM_ERR_CONFIG_FLAG_INVALID,                     /*配置参数错误，不是TURE也不是FALSE*/
    RM_ERR_PRAR_INVALID,                            /*90:参数错误不合法*/
    RM_ERR_PROCID_CAN_NOT_ZERO,                     /*进程Id不能为0*/
    RM_ERR_POLICY_ID_NOT_EXIST,                     /*策略ID不存在*/
    RM_ERR_POLICY_ID_EXIST,                         /*策略ID存在*/
    RM_ERR_POLICY_ID_EXCEED_LIMIT,                  /*策略ID超过最大值*/
    RM_ERR_POLICY_ID_ZERO,                          /*策略ID不能为0*/
    RM_ERR_SOURCE_PRO_TYPE,                         /*错误的源协议类型*/
    RM_ERR_INIT_FAILED,                             /*RM全局资源没有初始化完毕*/
    RM_ERR_HOPADDR_IN_DEST,                         /*只指定下一跳地址时，下一跳不可以在目的网段中*/
    RM_ERR_HOOKFUNC_IS_NULL,
    RM_ERR_IFNET_IS_NULL,                           /*100:接口ifnet为空*/
    RM_ERR_INTERFACE_IS_L2,                         /*接口为二层接口*/
    RM_ERR_METRIC_TYPE,                             /*错误的metric 类型*/
    RM_ERR_NOT_OSPF_METRIC_TYPE_MUST_ZERO,          /*非 OSPF 类型的metric类型必须是0*/
    RM_ERR_PROCID_MUST_ZERO,                        /*静态或者直连的实例号必须是0*/
    RM_ERR_GET_IPV6_FUNCTION,                       /*获取IPv6组件指针错误*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    RM_ERR_GET_VRF_INDEX,
    RM_ERR_VRF_INDEX_INVALID,
    RM_ERR_GET_INST_NUM,
    RM_ERR_GET_VRF_NAME,
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*Begin BC3D01416 直连路由设置支持VRF l00147446 09-04-13*/
    RM_ERR_DIRECT_ROUTE,                            /*110*/
    /*End BC3D01416 直连路由设置支持VRF l00147446 09-04-13*/
    RM_ERR_IPV_TYPE,                      /*错误的IPV类型(非IPV4/IPV6)*/

    /* BEGIN V2R3TEST */

    RM_ERR_FILTER_RULE_NOT_EXIST,   /*过滤规则不存在:引入/接收*/
    RM_ERR_FILTER_RULE_EXIST,        /*过滤规则已经存在:引入/接收*/
    RM_ERR_GET_HAVE_NOT_OPEN,    /*没有进行OPEN操作*/
    RM_ERR_GETFIRST_FAIL,       /*FIRST返回失败操作*/
    RM_ERR_VRF_NULL_POINT,/*VRF树为空*/
    RM_ERR_VRF_ADDR_NULL_POINT,/*VRF地址树为空*/
    RM_ERR_DESTADDR_NOT_GLOBAL,/*静态路由目的地址不为Global或全0地址*/
    RM_ERR_NETRT_PREFIX,/*网段路由前缀无效*//*VISPV1R8C03 for rtm net route*/
    RM_ERR_NETRT_GET_IF_INFO,/*120:*//*获取网段路由出接口信息出错*/
    RM_ERR_NETRT_IF_TYPE_INVALID,/*网段路由出接口类型无效*/
    RM_ERR_NETRT_NEXTHOP_INVALID,/*下一跳必须为指定接口Global地址*/
    RM_ERR_NETRT_DESTADDR_INVALID,/*目的地址与下一跳和前缀相与结果不等*/
    RM_ERR_NETRT_EXIST,/*网段路由已经存在*/
    RM_ERR_NETRT_NO_MORE,/*不能有更多网段路由*/
    RM_ERR_NETRT_NOT_EXIST,/*网段路由不存在*/
    RM_ERR_NETRT_RM_MODE,/*RM模式错误*/
    /*Begin BC3D02905 liangjicheng 2010-04-12*/
    RM_ERR_REDIST_HOPACL_FILTER,  /*128 下一跳ACL过滤*/
    RM_ERR_HOPACL_NUM,
    RM_ERR_DESTHOPACL_NUM,
/* END V2R3TEST */

    RM_ERR_MAX = MID_COMP_RTM + 255
}RM_ERROR_S;


extern RM_ERROR_S RM_SetIpv4Route(RM_CFG_USR4_S * pstUsrIpTable);
extern RM_ERROR_S RM_EnableIpv4Route(RM_ENABLE_USR4_S * pstUsrIpEnable);
extern RM_ERROR_S RM_UpdateIpv4Route(RM_MOD_USR4_S * pstUsrIpTable);
extern RM_ERROR_S RM_SetIpv6Route(RM_CFG_USR6_S *pstUsrIpTable);
/*Add by h55555 for defect BC3D00774*/
extern RM_ERROR_S RM_SetEqualRouteNum(ULONG ulInstance,ULONG ulEqualRtNum);
extern RM_ERROR_S RM_GetEqualRouteNum(ULONG ulInstance,ULONG *pulEqualRtNum);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern RM_ERROR_S RM_SetEqualRouteNumByVrf(ULONG ulType,ULONG ulEqualRtNum,CHAR *pszVrfName);
extern RM_ERROR_S RM_GetEqualRouteNumByVrf(ULONG ulType,ULONG *pulEqualRtNum,CHAR *pszVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

extern RM_ERROR_S RM_CMM_RIB_TableOpen(ULONG * pulSessionID,RM_RIB_FILTER_S *pstRIBFilter);
extern RM_ERROR_S RM_CMM_RIB_TableClose(ULONG ulSessionID );
extern RM_ERROR_S RM_CMM_RIB_GetFirst(ULONG ulSessionID, RM_DSP_RIB_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_RIB_GetNext(ULONG ulSessionID, RM_DSP_RIB_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_ACRT_TableOpen(ULONG * pulSessionID,RM_ACRT_FILTER_S *pstACRTFilter);
extern RM_ERROR_S RM_CMM_ACRT_TableClose(ULONG ulSessionID );
extern RM_ERROR_S RM_CMM_ACRT_GetFirst(ULONG ulSessionID, RM_DSP_ACRT_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_ACRT_GetNext(ULONG ulSessionID, RM_DSP_ACRT_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_StaticRt_TableOpen(ULONG * pulSessionID,RM_STATIC_FILTER_S *pstStaticFilter);
extern RM_ERROR_S RM_CMM_StaticRt_TableClose(ULONG ulSessionID );
extern RM_ERROR_S RM_CMM_StaticRt_GetFirst(ULONG ulSessionID, RM_DSP_STATICRT_S * pstConfigInfo);  
extern RM_ERROR_S RM_CMM_StaticRt_GetNext(ULONG ulSessionID, RM_DSP_STATICRT_S * pstConfigInfo);

extern RM_ERROR_S RM_CMM_Brief_Open(ULONG *pulSessionID,RM_BRIEF_FILTER_S *pstBriefFilter);
extern RM_ERROR_S RM_CMM_Brief_GetFirst(ULONG ulSessionID,RM_BRIEF_INFO_S *psBriefInfo);
extern RM_ERROR_S RM_CMM_Brief_GetNext(ULONG ulSessionID, RM_BRIEF_INFO_S *psBriefInfo);
extern RM_ERROR_S RM_CMM_Brief_Close(ULONG ulSessionID );

extern VOID RM_ShowEqualRouteNum(ULONG ulInstance);
extern VOID RM_ShowIPv4RIBInfoAll(VOID);
extern VOID RM_ShowIPv6RIBInfoAll(VOID);
extern VOID RM_ShowIPv4ACRTInfoAll(VOID);
extern VOID RM_ShowIPv6ACRTInfoAll(VOID);
extern VOID RM_ShowIPv4StaticInfoAll(VOID);
extern VOID RM_ShowIPv6StaticInfoAll(VOID);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern VOID RM_ShowEqualRouteNumByVrf(ULONG ulType,CHAR *pszVrfName);
extern VOID RM_ShowIPv4RIBInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv6RIBInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv4ACRTInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv6ACRTInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv4StaticInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv6StaticInfoAllByVrf(CHAR *szVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

extern VOID RM_ShowIPv4RtmBriefInfoByVrf(CHAR *szVrfName,ULONG ulFlag,ULONG ulFilterLevel);
extern VOID RM_ShowIPv6RtmBriefInfoByVrf(CHAR *szVrfName,ULONG ulFlag,ULONG ulFilterLevel);

/*rm_api.h 数据结构
*/
#define RM_RPM_MTYPE_INVALID   0
#define RM_RPM_MTYPE_INTERNAL  1
#define RM_RPM_MTYPE_EXTERNAL  2
#define RM_RPM_MTYPE_TYPE1     3
#define RM_RPM_MTYPE_TYPE2     4

typedef struct tagRM_RPM_PLCYDIST
{
    union
    {
        ULONG ulAccNum;         /* Access List Number */
    } stFltrName;            
    USHORT  usProcessID;        /* AS Number/Process ID */
    UCHAR   ucProtocolID;       /* Protocol ID */    
    UCHAR  ucPad;
} RM_RPM_PLCYDIST_S;

typedef struct tagRM_RPM_PLCYREDIS
{
    UCHAR   ucRPAID;
    UCHAR   ucPad;
    USHORT  usRPAProcessID;
    ULONG   enMetricType;/*由于产品已经使用，命名不修改为ul开头*/ 
    ULONG   ulMetricVal;
} RM_RPM_PLCYREDIS_S;  

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef ULONG (*DCL_SET_RT4_FUNC)(RM_CFG_USR4_S * pstUsrIpTable);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*Modified by liangjicheng 00103192, Calc Delay, 2011/10/27   问题单号: REQ-201106295399-OSPF-PER */
#define NBASE_CPU_SWITCH_VALUE_MIN  1     
#define NBASE_CPU_SWITCH_VALUE_MAX  1000 

#define SCKSTUB_CPU_SWITCH_VALUE_MIN  1     
#define SCKSTUB_CPU_SWITCH_VALUE_MAX  1000 

#define SCKSTUB_CPU_SWITCH_TIME_MIN  1     
#define SCKSTUB_CPU_SWITCH_TIME_MAX  100 

#define OSPF_PERTENLSA_CALC_DELAY_MIN  1     
#define OSPF_PERTENLSA_CALC_DELAY_MAX  100 

typedef struct tagDCL_CPUSW
{
    ULONG ulNbaseCpuSwitchValue;    /* Nbase消息处理计数门限，默认10个IPS   范围:1~1000*/
    ULONG ulSckStubCpuSwitchValue;  /* SckStub任务处理计数门限，默认10个IPS 范围:1~1000*/
    ULONG ulSwitchTime;             /* 切换CPU的休眠时间，默认为1ms         范围:1~100 */
    ULONG ulOspfPerTenLSACalcDelay; /* OSPF 两次路由计算的延时控制，单位:每10条LSA最小延时时间(ms)。默认50 (ms/10-lsa) 范围:1~100 */
}DCL_CPUSW_S;

/*******************************************************************************
*    Func Name: TCPIP_SetDclCpuSwitchValue
* Date Created: 2011-10-28
*       Author: liangjicheng 00103192
*  Description: 设置DCL相关性能控制参数
*        Input: DCL_CPUSW_S *pstSwitchValue:
*    ULONG ulNbaseCpuSwitchValue;     Nbase消息处理计数门限，默认10个IPS   范围:1~1000
*    ULONG ulSckStubCpuSwitchValue;   SckStub任务处理计数门限，默认10个IPS 范围:1~1000
*    ULONG ulSwitchTime;              切换CPU的休眠时间，默认为1ms         范围:1~100 
*    ULONG ulOspfPerTenLSACalcDelay;  OSPF 两次路由计算的延时控制，单位:每10条LSA最小延时时间(ms)。默认50 (ms/10-lsa) 范围:1~100
*       Output: 
*       Return: 成功返回 RM_OK; 失败返回  RM_ERR_PARA RM_ERR_WRONG_VALUE; 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-28   liangjicheng 00103192   Create
*
*******************************************************************************/
ULONG TCPIP_SetDclCpuSwitchValue(DCL_CPUSW_S *pstSwitchValue);

/*******************************************************************************
*    Func Name: TCPIP_GetDclCpuSwitchValue
* Date Created: 2011-10-28
*       Author: liangjicheng 00103192
*  Description: 设置DCL相关性能控制参数
*        Input: 
*       Output: DCL_CPUSW_S *pstSwitchValue:
*    ULONG ulNbaseCpuSwitchValue;     Nbase消息处理计数门限，默认10个IPS   范围:1~1000
*    ULONG ulSckStubCpuSwitchValue;   SckStub任务处理计数门限，默认10个IPS 范围:1~1000
*    ULONG ulSwitchTime;              切换CPU的休眠时间，默认为1ms         范围:1~100 
*    ULONG ulOspfPerTenLSACalcDelay;  OSPF 两次路由计算的延时控制，单位:每10条LSA最小延时时间(ms)。默认50 (ms/10-lsa) 范围:1~100
*       Return: 成功返回 RM_OK; 失败返回  RM_ERR_PARA; 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-28   liangjicheng 00103192   Create
*
*******************************************************************************/
ULONG TCPIP_GetDclCpuSwitchValue(DCL_CPUSW_S *pstSwitchValue);
/*End of Modified by liangjicheng 00103192, 2011/10/27   问题单号: REQ-201106295399-OSPF-PER */

/*******************************************************************************
*    Func Name: TCPIP_SetDclCpuSwitchValue
* Date Created: 2013-4-16
*       Author: qinyun 62011
*  Description: 设置RTM迭代递归次数门限
*        Input: ULONG ulCoun:值域有效，0表示不作门限处理。默认为0
*       Output: 
*       Return: 成功返回 RM_OK; 失败返回  RM_ERR_PARA RM_ERR_WRONG_VALUE; 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-4-16  qinyun 62011   Create
*
*******************************************************************************/
ULONG TCPIP_SetRtmResolveCount(ULONG ulCount);

extern RM_ERROR_S RM_EnableIpv4RouteExt(RM_ENABLE_USR4_S * pstUsrIpEnable, ULONG ulVrfIndex);

#ifdef  __cplusplus
}
#endif

#endif 

