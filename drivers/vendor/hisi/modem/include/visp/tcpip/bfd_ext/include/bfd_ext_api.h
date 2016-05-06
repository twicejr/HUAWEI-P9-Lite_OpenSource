/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_ext_api.h
*
*  Project Code: VISPV100R007C02
*   Module Name: BFD EXTERN
*  Date Created: 
*        Author: 
*   Description: BFD EXTERN API 函数声明以及宏定义头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME         DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-11-03   Q62011       Add for BC3D00658, BFD_MAX_INTF_NAME_LEN,
*                            BFD_MAX_DESC_NAME_LEN,BFD_MAX_SESS_NAME_LEN改为
*                            BFD_EXT_MAX_INTF_NAME_LEN,BFD_EXT_MAX_DESC_NAME_LEN
*                            消除对bfd_def.h 的依赖
*                            BFD_OSPF_RULE_TYPE_INTF,BFD_OSPF_RULE_TYPE_PROC
*                            转移到api头文件中供用户使用
*  2009-09-30   l00147446    BC3D02152【BFDEXT】模块无用API，需清理。
*******************************************************************************/
#ifndef _BFD_EXT_API_H_
#define _BFD_EXT_API_H_

#ifdef __cplusplus
extern "C" {
#endif
/**************************************************/
/*               API 结构及宏定义                 */
/**************************************************/
#define BFD_EXT_MAX_INTF_NAME_LEN   47  /* 保持与BFD_MAX_INTF_NAME_LEN相同 */
#define BFD_EXT_MAX_DESC_NAME_LEN   47  /* 保持与BFD_MAX_DESC_NAME_LEN相同 */
#define BFD_EXT_MAX_SESS_NAME_LEN   15  /* 保持与BFD_MAX_SESS_NAME_LEN相同 */
#define BFD_EXT_MAX_VRF_NAME_LEN    31  /* 保持与BFD_MAX_VRF_NAME_LEN相同 */

/*BFD EXT模块API操作字类型*/
#define BFD_EXT_OP_ADD  1
#define BFD_EXT_OP_DEL  0

/*OSPF接口关联动作Action字段值定义*/
#define BFD_EXT_BLOCK      1
#define BFD_EXT_ENABLE     0

/*OSPF关联规则配置类型 : 接口关联，进程关联*/
#define BFD_OSPF_RULE_TYPE_INTF   1
#define BFD_OSPF_RULE_TYPE_PROC   2

/*过滤器有效位参数ulFltFlag取值，非0的参数可组合使用*/    
#define BFD_EXT_FILTER_ALL                    0
#define BFD_EXT_FILTER_DEST                0x01
#define BFD_EXT_FILTER_PREFIXLEN       0x02
#define BFD_EXT_FILTER_VRF                  0x04

#define  BFD_EXT_TYPE_STATIC 0  /*BFD 联动 类型：STATIC*/
#define  BFD_EXT_TYPE_OSPF   1  /*BFD 联动 类型：OSPF*/

/*Added by guojianjun178934, 配置BFD6 和OSPFv3联动，需要指定实例 Id, 2014/8/8   问题单号:S-IP-C20-002-BFD6.002 */
/*BFD OSPF过滤类型定义*/
#define BFD_OSPF_FILTER_NONE           0x00   /*无过滤*/
#define BFD_OSPF_FILTER_BY_PROC        0x01   /*按照OSPF进程过滤*/
#define BFD_OSPF_FILTER_BY_IF          0x02   /*按照接口过滤*/
#define BFD_OSPF_FILTER_BY_INSTANCE   0x04   /*按照接口实例过滤(当前只支持按照指定接口实例过滤)*/
/* End of Added by guojianjun178934, 2014/8/8   问题单号:S-IP-C20-002-BFD6.002 */

/*BFD EXT调试开关类型*/
typedef enum tagBFD_RM_DEBUG_E
{
    BFD_DEBUG_NO = 0,             /*联动的调试开关*/
    BFD_DEBUG_OSPF,               /*OSPF联动的调试开关*/
    BFD_DEBUG_RTM,                /*RTM联动的调试开关*/
    BFD_DEBUG_ALL,                /*OSPF,RTM联动的调试开关*/
    BFD_DEBUG_MAX                 /*调试开关最大值*/
}BFD_RM_DEBUG_E;

/* BFD EXT错误码定义如下 */
typedef enum tagBFD_EXT_ERR_E
{
    BFD_EXT_OK,                         /* 0 */
    BFD_EXT_ERR = MID_COMP_BFDEXT + 1,  /* 1 相关组件函数指针未初始化*/
    BFD_EXT_ERR_NO_INITAIL,             /* 2 BFD EXT模块未初始化*/
    BFD_EXT_ERR_NULL_POINTER,           /* 3 参数指针为空 */
    BFD_EXT_ERR_INVALID_PARAMETER,      /* 4 参数无效*/
    BFD_EXT_ERR_INTF_NOT_EXIST,         /* 5 指定接口不存在 */
    BFD_EXT_ERR_RX_INTERVAL,            /* 6 BFD接收时间间隔非法 */
    BFD_EXT_ERR_TX_INTERVAL,            /* 7 BFD发送时间间隔非法 */
    BFD_EXT_ERR_DETECT_MULT,            /* 8 BFD检测倍数非法 */
    BFD_EXT_ERR_MEM_ALLOC,              /* 9 内存分配出错 */
    BFD_EXT_ERR_STATIC_RT_DETECT_TIME,  /* 10 BFD静态路由联动的虚拟检测时间非法*/
    BFD_EXT_ERR_STATIC_RT_FULL,         /* 11 BFD For STATIC关联已满*/
    BFD_EXT_ERR_STATIC_RT_SESS_FAIL,    /* 12 会话已被使用，静态路由关联BFD会话失败 */
    BFD_EXT_ERR_STATIC_RT_NOT_EXIT,     /* 13 指定的静态路由关联不存在  */
    BFD_EXT_ERR_STATIC_SAME_RT,         /* 14 静态路由关联BFD会话失败，该路由已经关联 */
    BFD_EXT_ERR_SESSION_NAME,           /* 15 配置的BFD会话名异常*/
    BFD_EXT_ERR_PROCID_IFNAME,          /* 16 不能同时配置Process ID和Interface Name 或Process ID和Interface Name 都不配置*/
    BFD_EXT_ERR_ENA_BLOCK_FLAG,         /* 17 配置接口Enable、Block标志位取值异常*/
    BFD_EXT_ERR_OSPF_RULE_FULL,         /* 18 BFD For OSPF关联条件已满*/
    BFD_EXT_ERR_OSPF_BLOCK_FULL,        /* 19 接口Block功能配置满规格*/
    BFD_EXT_ERR_OSPF_RULE_NOT_EXIT,     /* 20 指定的关联条件不存在 */
    BFD_EXT_ERR_NO_SESS_MATCH_FILTER,   /* 21 没有符合过滤条件的会话 */
    BFD_EXT_ERR_GET_ENTRY_END,          /* 22 已到最后一个表项 */
    BFD_EXT_ERR_WAITLIST,               /* 23 WaitList机制返回异常*/
    BFD_EXT_ERR_PROC_TYPE,              /* 24 Proc Type与期望的不同*/
    BFD_EXT_ERR_BFDMDL,                 /* 25 调用BFD模块API返回错误码*/
    BFD_EXT_ERR_OSPF_PROCID,            /* 26 OSPF进程号非法*/
    BFD_EXT_ERR_GET_VRFINDEX,           /* 27 获取VRF索引失败 */
    BFD_EXT_ERR_GET_RTMINDEX,           /* 28 获取RTM实例号失败 */
    
    /*Begin BC3D01505 关闭句柄出现断错误l00147446 09-04-29*/
    BFD_EXT_ERR_MEM_RELEASE,                    /*29 BFD释放内存出错*/
    /*End BC3D01505 关闭句柄出现断错误l00147446 09-04-29*/
    BFD_EXT_ERR_IF_PROC_NOT_MATCH,      /* 30 OSPF进程和接口所在的VRF不一致 */
    BFD_EXT_ERR_BOTH_PID_IFNAME,        /*31 <进程号和接口名不能同时指定>*/
    BFD_EXT_ERR_BOTHNOT_PID_IFNAME,     /*32 <进程号和接口名不能都不指定>*/   
    BFD_EXT_ERR_OSPF_NOEXIST,            /* 33 OSPF进程号不存在*/
    BFD_EXT_ERR_GET_RELATIONBFDID,       /* 34 通过静态路由信息获取关联的BFDID失败 */
    BFD_EXT_ERR_INVALID_INSTANCEID,     /* 35 配置的OSPFV3接口InstanceID无效*/
    BFD_EXT_ERR_GET_RELATIONTABLE,       /*36指定的BFD关联表不存在*/
    BFD_EXT_ERR_ADD_DUPLICATERELATIONTABLE, /*37添加重复的关联表*/
    BFD_EXT_ERR_ADD_RELATIONTABLE,          /*38添加关联表失败*/

    BFD_EXT_ERR_MAX                     /* 错误码最大值*/
}BFD_EXT_ERR_E;

/* OSPF与BFD会话的关联规则配置接口 */ 
typedef struct tagBfdApiOspfRuleOption
{
    ULONG ulOpType;                                /* 操作字,0-删除，1-增加*/ 
    ULONG ulProcIndex;                             /* OSPF 进程号,增加删除配置时均有效*/ 
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1]; /* 接口名称(字符串格式),增加删除配置时均有效*/ 
    ULONG ulInstanceID;                            /*OSPFV3 基于接口的instance id ,和接口一起使用*/
    ULONG ulMinTxInterval;                         /* BFD期望的发送间隔 ,仅增加配置时有效*/ 
    ULONG ulMinRxInterval;                         /* BFD的本地接收能力 ,仅增加配置时有效*/ 
    ULONG ulDetectMult;                            /* BFD的本地检测倍数 ,仅增加配置时有效*/ 
    USHORT usEnable;                               /* Enable标志*/ 
    USHORT usBlock;                                /* Block标志*/ 
} BFD_API_OSPF_RULE_OP_S;

/* OSPF与BFD会话的关联规则数据结构 */ 
typedef struct tagBfdApiForOspfRule
{
    ULONG   ulRuleType; 
    ULONG   ulIfIdOrProcId; 
    UCHAR   szIfFullName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    ULONG   ulInstanceId;        /*OSPFV3 基于接口的instance id ,和接口一起使用*/
    ULONG   ulMinTxInterval;    /* BFD期望的发送间隔 */ 
    ULONG   ulMinRxInterval;    /* BFD的本地接收能力 */ 
    ULONG   ulDetectMult ;      /* BFD的本地检测倍数 */ 
    ULONG   ulAction ;          /* 关联动作:接口关联规则有效,BFD_EXT_ENABLE - 0,BFD_EXT_BLOCK - 1 */ 
} BFD_API_FOR_OSPF_RULE_S;

/* OSPF与BFD会话的关联信息数据结构 */ 
typedef struct tagBfdApiForOspfRelation
{ 
    ULONG ulProcIndex; 
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1]; 
    ULONG ulNeighborId; /*OSPF模块的Neighbor ID，主机序*/
    ULONG ulInstanceId;         /*Instance ID，OSPFV3时有效*/
    ULONG ulSessionId; 
    UCHAR szSessionDes[BFD_EXT_MAX_DESC_NAME_LEN + 1]; 
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
}BFD_API_FOR_OSPF_RELATION_S;

typedef struct tagBfdApiStaticRelationOption
{
    ULONG ulOpType;             /* 操作字,0-删除，1-增加*/ 
    ULONG ulDestIp;
    ULONG ulPrefixLen;
    ULONG ulNextHop;
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
    UCHAR szVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-12 */
    USHORT usSpeciRouteVrfFlag;/*1表示指定静态路由Vrf*/
    USHORT usReserve;
    UCHAR  szRouteVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
} BFD_API_STATIC_RELATION_OP_S;

/* 路由信息结构体，V4和V6公用 */
typedef struct tagBfdApiStaticRtInfo
{
    ULONG ulDestIp[4];   /* 网络序,V4地址填在ulDestIp[0]里 */
    ULONG ulPrefixLen;
    ULONG ulNextHop[4];  /* 网络序,V4地址填在ulNextHop[0]里 */
    ULONG ulIfindex;
    ULONG ulVrfIndex;
    ULONG ulIpVersion;   /* 0是IPV4, 1是IPV6 */
    ULONG ulBfdSessionId; /* 出参 */
    ULONG ulBfdVrfIndex;  /*BFD的VRF索引*/
} BFD_API_STATIC_RTINFO_S;

/* Static Router与BFD会话的关联信息数据结构 */ 
typedef struct tagBfdApiForStaticRelation
{ 
    ULONG ulDestIp; 
    ULONG ulPrefixLen; 
    ULONG ulNextHop; 
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1]; 
    ULONG ulSessionId; 
    UCHAR szSessionDes[BFD_EXT_MAX_DESC_NAME_LEN + 1]; 
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
    ULONG ulVrfIndex;
    ULONG ulRouteVrfIndex; /*静态路由的VRF 索引*/
}BFD_API_FOR_STATIC_RELATION_S;

typedef struct tagBfd6ApiStaticRelationOption
{
    ULONG ulOpType;             /* 操作字,0-删除，1-增加*/ 
    ULONG ulDestIp[4];
    ULONG ulPrefixLen;
    ULONG ulNextHop[4];
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
    UCHAR szVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
    USHORT usSpeciRouteVrfFlag;/*1表示指定静态路由Vrf，默认为0，不使用*/
    USHORT usReserve;
    UCHAR szRouteVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1]; /*静态路由绑定的VRF*/
} BFD6_API_STATIC_RELATION_OP_S;

typedef struct tagBfd6ApiForStaticRelation
{ 
    ULONG ulDestIp[4]; 
    ULONG ulPrefixLen; 
    ULONG ulNextHop[4]; 
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1]; 
    ULONG ulSessionId; 
    UCHAR szSessionDes[BFD_EXT_MAX_DESC_NAME_LEN + 1]; 
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
    ULONG ulVrfIndex;
    ULONG ulRouteVrfIndex; /*静态路由的VRF 索引*/
}BFD6_API_FOR_STATIC_RELATION_S;
/*************************************/
/*         过滤器结构体              */
/*************************************/
/* OSPF与BFD会话关联过滤信息数据结构 */
typedef struct tagBfdApiForOspfFilter
{ 
    ULONG ulProcIndex;
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
}BFD_API_FOR_OSPF_FILTER_S;

/* OSPF与BFD会话关联过滤信息数据结构 */
typedef struct tagBfd6ApiForOspfFilter
{
    ULONG ulProcIndex;
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    ULONG ulInstanceId;  
    UCHAR ucType;         /* 支持 OSPF 进程号、指定接口、指定接口 & instance id 三种查询模式*/
    UCHAR ucPad[3]; 
}BFD6_API_FOR_OSPF_FILTER_S;


/* 静态路由与BFD会话关联过滤信息数据结构 */ 
typedef struct tagBfdApiForStaticFilter
{ 
    ULONG ulFltFlag;/*取值范围:BFD_EXT_FILTER_ALL                0    
                              BFD_EXT_FILTER_DEST                0x01
                              BFD_EXT_FILTER_PREFIXLEN       0x02
                              BFD_EXT_FILTER_VRF                  0x04*/
    ULONG ulDestIp;
    ULONG ulPrefixLen;
    /*Begin BC3D02529 查询BFD与静态路由绑定关系，必须输入出接口不合理【重新修改】 l00147446 10-02-08*/
    UCHAR szVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
    /* End for BC3D02529 */
}BFD_API_FOR_STATIC_FILTER_S;
typedef struct tagBfd6ApiForStaticFilter
{ 
    ULONG ulFltFlag;/*取值范围:BFD_EXT_FILTER_ALL                0    
                              BFD_EXT_FILTER_DEST                0x01
                              BFD_EXT_FILTER_PREFIXLEN       0x02
                              BFD_EXT_FILTER_VRF                  0x04*/
    ULONG ulDestIp[4];
    ULONG ulPrefixLen;
    UCHAR szVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
}BFD6_API_FOR_STATIC_FILTER_S;

typedef ULONG(*BFD_RM_NOTIFY_HOOK_FUNC)( ULONG ulType, ULONG ulProcIndex, ULONG ulStat,VOID * pPara);


typedef struct tagBfdApiDynamicNodeInfo
{ 
    ULONG ulProcType;   /* 类型：BFD_EXT_TYPE_OSPF （目前仅支持OSPF类型）*/
    ULONG ulProcId;     /* OSPF实例号*/
    ULONG ulVrfIndex;   /* VRF索引*/
    ULONG ulInstanceId; /* Instace ID，OSPFV3有效*/
    ULONG ulRouterId;    /* Route ID(网络序)*/
    ULONG ulIfIndex;    /* 新邻居的接口索引*/
    ULONG ulNetworkType;/* 地址类型:IPv4 BFD_EXT_TABLE_IPV4 或者IPv6 BFD_EXT_TABLE_IPV6*/
    ULONG ulSrcIP[4];   /* 本端地址*/
    ULONG ulDstIP[4];   /* 对端地址*/
}BFD_API_DYNAMIC_NODE_INFO_S;

typedef struct tagBfdApiDynamicNodeCfg
{ 
    ULONG ulProtocal;  /*草案4协议或RFC协议的BFD    
                       BFD_PROTO_DRAFT4    0 
                       BFD_PROTO_STD       1*/
}BFD_API_DYNAMIC_NODE_CFG_S;

typedef ULONG(*BFD_GET_DYN_SESS_PRO_HOOK_FUNC)(BFD_API_DYNAMIC_NODE_INFO_S *pstNode, BFD_API_DYNAMIC_NODE_CFG_S *pstOutInfo);

/*BFD For OSPF API*/
extern ULONG BFD_SetRtStaticDetecTime(ULONG ulTime);
extern ULONG BFD_AddDelOspfRule(BFD_API_OSPF_RULE_OP_S stOspfRule);
extern ULONG BFD_OpenOspfRuleTable(UINTPTR *pulWaitListHandle,BFD_API_FOR_OSPF_FILTER_S *pstFilter);
extern ULONG BFD_CloseOspfRuleTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetOspfRuleEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_OSPF_RULE_S *pstRules);
extern ULONG BFD_OpenOspfRelationTable(UINTPTR *pulWaitListHandle,BFD_API_FOR_OSPF_FILTER_S *pstFilter);
extern ULONG BFD_CloseOspfRelationTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetOspfRelationEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_OSPF_RELATION_S *pstRelations);
extern ULONG BFD_AddDelOspf6Rule(BFD_API_OSPF_RULE_OP_S stOspfRule);
extern ULONG BFD_OpenOspf6RuleTable(UINTPTR *pulWaitListHandle, BFD6_API_FOR_OSPF_FILTER_S *pstFilter);
extern ULONG BFD_CloseOspf6RuleTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetOspf6RuleEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_OSPF_RULE_S *pstRules);
extern ULONG BFD_OpenOspf6RelationTable(UINTPTR *pulWaitListHandle,BFD6_API_FOR_OSPF_FILTER_S *pstFilter);
extern ULONG BFD_CloseOspf6RelationTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetOspf6RelationEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_OSPF_RELATION_S *pstRelations);

/*BFD For Static API*/
extern ULONG BFD_AddDelRtStatic(BFD_API_STATIC_RELATION_OP_S stStaticRelation);
extern ULONG BFD_OpenRtStaticRelationTable(UINTPTR *pulWaitListHandle,BFD_API_FOR_STATIC_FILTER_S *pstFilter);
extern ULONG BFD_CloseRtStaticRelationTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetRtStaticRelationEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_STATIC_RELATION_S *pstRelations);

/*可维可测 API*/
extern ULONG BFD_SetDbgSwitch(ULONG ulSwitch);
extern ULONG BFD_SetV6DbgSwitch(ULONG ulSwitch);
extern VOID BFD_ShowOspfRule(VOID);
extern VOID BFD_ShowOspfSession(VOID);
extern VOID BFD_ShowRtStaticSession(VOID);
extern VOID BFD_ShowOspf6Rule(VOID);
extern VOID BFD_ShowOspf6Session(VOID);

extern ULONG BFD_RegFuncGetDynamicSessionPro (BFD_GET_DYN_SESS_PRO_HOOK_FUNC pfFunc);
/*******************************************************************************
*    Func Name:    BFD6_AddDelRtStatic
*    Date Created: 
*    Author: 
*    Description:  增加、删除静态路由与BFD6会话关联
*    Input:        stStaticRelation: BFD与路由关联会话配置参数；
*    Output:       无；
*    Return:       成功返回       BFD_EXT_OK
*                  失败返回       错误码
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_AddDelRtStatic(BFD6_API_STATIC_RELATION_OP_S stStaticRelation);

/*******************************************************************************
*    Func Name:    BFD6_OpenRtStaticRelationTable
*    Date Created: 
*    Author: 
*    Description:  获取BFD6与Ststic会话关联表的WaitList句柄
*    Input:        pFilter: 过滤器
*                  ulSizeOfFilter: 过滤器长度
*    Output:       pulWaitListHandle: WaitList句柄
*    Return:       成功返回       BFD_EXT_OK
*                  失败返回       错误码
*                  BFD_EXT_ERR_GET_ENTRY_END 从表中获取不到符合过滤器的数据指针
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_OpenRtStaticRelationTable(UINTPTR *pulWaitListHandle,BFD6_API_FOR_STATIC_FILTER_S *pstFilter);

/*******************************************************************************
*    Func Name:    BFD6_CloseRtStaticRelationTable
*    Date Created: 
*    Author: 
*    Description:  关闭BFD6与Ststic会话关联表的WaitList句柄
*    Input:        ulWaitListHandle: WaitList句柄
*    Output:       
*    Return:       成功返回       BFD_EXT_OK
*                  失败返回       错误码
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_CloseRtStaticRelationTable(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name:    BFD6_GetRtStaticRelationEntry
*    Date Created: 
*    Author: 
*    Description:  通过WaitList句柄，获取下一条满足过滤器的数据指针
*    Input:        ulEntryWaitList: WaitList句柄
*    Output:       pstRelations:获取到的数据
*    Return:       成功返回       BFD_EXT_OK
*                  失败返回       错误码
*                  BFD_EXT_ERR_GET_ENTRY_END 从表中获取不到符合过滤器的数据指针
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetRtStaticRelationEntry(UINTPTR ulEntryWaitList, BFD6_API_FOR_STATIC_RELATION_S *pstRelations);

/*******************************************************************************
*    Func Name:    BFD6_ShowRtStaticSession
*    Date Created: 
*    Author: 
*    Description:  显示所有静态路由与BFD6会话的关联表项
*    Input:        
*    Output:       
*    Return:       
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
VOID BFD6_ShowRtStaticSession(VOID);

/*******************************************************************************
*    Func Name:    BFD_GetBFDSessionByRtInfo
*    Date Created: 2014-07-07
*    Author:       fengjing209023
*    Description:  通过静态路由信息获取绑定的关联BFD会话ID
*    Input:        BFD_API_STATIC_RTINFO_S pstBfdRtInfo: 路由信息结构体，
*                  出参也包含在里面
*    Output:       pstBfdRtInfo->ulBfdSessionId
*    Return:       成功返回BFD_EXT_OK，否则返回错误码
*    Caution:      调用者需保证参数的有效性
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2014-07-07      fengjing209023        Create
*******************************************************************************/
ULONG BFD_GetBFDSessionByRtInfo(BFD_API_STATIC_RTINFO_S *pstBfdRtInfo);

#ifdef __cplusplus
}
#endif

#endif


