/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_cmm_api.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2009-07-13
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-13   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _OSPF6_CMM_API_H_
#define _OSPF6_CMM_API_H_
        
#ifdef __cplusplus
            extern "C"{
#endif /* __cplusplus */

/*STRUCT<OSPF6 LSDB过滤条件结构体>*/
typedef struct tagOSPF6_LSDB_FILTER
{
    USHORT usProcessId;                    /*进程ID
                                             范围：0~0xffff。
                                             0：存在的所有进程；
                                             1～0xffff：指定的OSPF进程号。*/
    USHORT usLsaType;                      /*LSA类型，
                                                OSPF6_ROUTER_LSA
                                                OSPF6_NETWORK_LSA
                                                OSPF6_INTER_AREA_PRFX_LSA
                                                OSPF6_INTER_AREA_RTR_LSA
                                                OSPF6_AS_EXTERNAL_LSA
                                                OSPF6_NSSA_EXT_LSA
                                                OSPF6_LINK_LSA
                                                OSPF6_INTRA_AREA_PRFX_LSA */
} OSPF6_LSDB_FILTER_S;

/*STRUCT<通用OSPF6聚合查询过滤条件结构体>*/
typedef struct tagOSPF6_AREA_AGG_FILTER
{
    USHORT usProcessId;                     /*进程ID
                                              范围：0~0xffff。
                                              0：存在的所有进程；(ulAreaId字段无效)
                                              1～0xffff：指定的OSPF进程号。*/
    UCHAR  ucPadding[2];                    /*填充*/
    ULONG  ulAreaId;                        /*区域ID，0-0xffffffff*/
} OSPF6_AREA_AGG_FILTER_S;

/*STRUCT<通用OSPF6过滤条件结构体>*/
typedef struct tagOSPF6_FILTER
{
    USHORT usProcessId;                      /*进程ID
                                              范围：0-0xffff。
                                              0：存在的所有进程；
                                              1-0xffff：指定的OSPF进程号。*/
    UCHAR  ucPadding[2];                     /*填充*/
} OSPF6_FILTER_S;

/*STRUCT<OSPF6 静态邻居生效过滤条件结构体>*/
typedef struct tagOSPF6_PEER_FILTER
{
    USHORT usProcessId;                      /*进程ID
                                              范围：0-0xffff。
                                              0：存在的所有进程；
                                              1-0xffff：指定的OSPF进程号。*/
    UCHAR  ucPadding[2];                     /*填充*/
    ULONG  ulInstanceId;                     /*实例 ID 
                                                范围: 0-255
                                                OSPF6_ALL_INST_FILTER:不指定实例号查询*/ 
    ULONG  ulIfIndex;                        /*接口索引，为0表示不指定接口查询*/
} OSPF6_PEER_FILTER_S;

/*STRUCT<OSPF6 静态邻居配置过滤条件结构体>*/
typedef struct tagOSPF6_CFGPEER_FILTER
{
    ULONG  ulInstanceId;                     /*实例 ID 
                                                范围: 0~255
                                                OSPF6_ALL_INST_FILTER:不指定实例号查询*/ 
    ULONG  ulIfIndex;                        /*接口索引，为0表示不指定接口查询*/
} OSPF6_CFGPEER_FILTER_S;

/*STRUCT<OSPF6接口绑定信息查询的过滤条件结构体>*/
typedef struct tagOSPF6_INTF_BIND_FILTER
{
    USHORT usProcessId;                      /*进程ID
                                              范围：0-0xffff。
                                              0：存在的所有进程；
                                              1-0xffff：指定的OSPF进程号。*/
    UCHAR  ucPadding[2];                     /*填充*/
    ULONG  ulIfIndex;                        /*接口索引，为0表示不指定接口查询*/
} OSPF6_INTF_BIND_FILTER_S;

/*STRUCT<OSPF6 接口属性过滤条件结构体>*/
typedef struct tagOSPF6_INTF_ATTR_FILTER
{
    ULONG  ulInstanceId;                     /*Instance ID 
                                                范围: 0~255
                                                OSPF6_ALL_INST_FILTER:不指定实例号查询*/ 
    ULONG  ulIfIndex;                        /*接口索引，为0表示不指定接口查询*/
} OSPF6_INTF_ATTR_FILTER_S;

/*STRUCT<OSPF6实体信息查询结构体，此数据结构包括ospf6 entity mib(amb_osp3_pm_ent)中供用户获取的字段>*/
typedef struct tagOSPF6_ENTITY_SHOW
{
    ULONG  ulProcessId;                     /*进程ID*/
    ULONG  ulRouterId;                      /*Router ID*/
    ULONG  ulAdminStatus;                   /*管理状态: 1-up；0-down*/
    ULONG  ulOperStatus;                    /*操作状态*/
    ULONG  ulOspfVersion;                   /*Ospf6版本*/
    ULONG  ulAbrFlg;                        /*Abr标志*/
    ULONG  ulAsbrFlg;                       /*Asbr标志*/
    ULONG  ulAsChkSumSum;                   /*自治区域内LSA CheckSum的和，用来确认LSA是否有变化*/
    ULONG  ulAsExtLsa;                      /*自治区域外LSA数目*/
    ULONG  ulMaxPaths;                      /*等价路由数目*/
    ULONG  ulCalcPauseFreq;                 /*区域内重计算停顿时间*/
    ULONG  ulCalcMaxDelay;                  /*区域内重计算延时时间*/
    ULONG  ulVrfIndex;                      /*VRF名*/
    ULONG  ulCfgRouterId;                   /*Cfg Route ID*/
    ULONG  ulDoGR;                          /*是否使能计划GR*/
    ULONG  ulDoGRUnplanned;                 /*是否使能非计划GR*/
    ULONG  ulGRPeriod;                      /*GR周期*/
    ULONG  ulRestartReson;                  /*GR重启原因*/
    ULONG  ulTrafficEngSupport;             /*This flag is used to determine if this router canoriginate its own traffic engineering LSAs.*/       
}OSPF6_ENTITY_SHOW_S;


/*STRUCT<OSPF6接口绑定信息查询结构体，此数据结构包括ospf6 if mib(amb_osp3_pm_if)中用户所关心的字段>*/
typedef struct tagOSPF6_SHOWINTF
{
    ULONG  ulProcessId;                         /*进程ID*/
    ULONG  ulInstanceId;                        /*Instance ID */ 
    ULONG  ulAreaId;                            /*区域ID*/
    UCHAR ucIpAddr[OSPF6_MAX_INET_ADDR_LEN];     /*IP6地址*/
    ULONG  ulIfNetworkType;                     /*接口网络类型
                                                  1 - 广播
                                                  2 - NBMA
                                                  3 - 点到点
                                                  5 - 点到多点
                                                  10 - 环回*/
    ULONG  ulIfIndex;                           /*接口索引 */ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH + 1];/*接口名*/
    ULONG  ulIfState;                           /*接口状态*/  
    ULONG  ulAdminStatus;                       /*admin 状态*/
    ULONG  ulOperStatus;                        /*操作状态*/
    ULONG  ulIfMetric;                          /*接口COST*/
    ULONG  ulIfPriority;                        /*优先级*/
    ULONG  ulDr;                                /*DR*/ 
    ULONG  ulBdr;                               /*BDR*/ 
    ULONG  ulFastHelloMultiplier;               /*FastHello频率*/
    ULONG  ulFastHelloInterval;                 /*FastHello间隔 0无效 其它有效*/
    ULONG  ulRxmtInterval;                      /*LSA重传时间*/ 
    ULONG  ulTransDelay;                        /*接口传输延时*/ 
    ULONG  ulHelloInterval;                     /*Hello间隔 FastHello无效时有效*/  
    ULONG  ulDeadInterval;                      /*Dead间隔*/ 
    ULONG  ulPollInterval;                      /*轮询间隔*/ 
    ULONG  ulIfMtuSize;                         /*接口上的MTU*/
    ULONG  ulMtuSizePcntge;                     /*接口MTU*/ 
    ULONG  ulMtuIgnoreFlg;                      /*接口MTU忽略标记*/ 
    ULONG  ulLSUTransmitDelay;                  /*LSU packet delay for reduce the network traffic Unit:ms Default:100 */
    ULONG  ulLsaCount;                          /*LSA数*/   
    ULONG  ulPassive;                           /*被动标志,默认:0
                                                  1 - 接口不再接收发送Hello报文*/

    /* Added by likaikun00213099, 基于接口统计各状态的邻居, 2014/4/15 */
    USHORT usNumNeighbors;                      /*本接口邻居个数*/
    USHORT usNeighborsInState[OSPF6_NBR_MAX_STATES + 1]; /*不同状态邻居个数*/
    ULONG  ulRouterId;                          /*本接口所属于的Router ID*/
    ULONG ulInterfaceId;            /* 本接口的接口ID */
    ULONG ulAddrlessif;
    ULONG ulMaxHitlessGracePeriod;
    ULONG ulAutoDelNbrFlag;                         /*Default: 1*/
    ULONG ulGrHelperMode;
    ULONG ulAccNum;
    ULONG ulRemoteIfIndex;
    /* End of Added by likaikun00213099, 基于接口统计各状态的邻居, 2014/4/15 */
}OSPF6_SHOWINTF_S;

/*STRUCT<区域查询信息结构体，此数据结构包括ospf6 area mib(amb_osp3_pm_area)中用户所关心的字段>*/
typedef struct tagOSPF6_SHOW_AREA
{
    ULONG  ulProcessId;                     /*进程ID*/
    ULONG  ulAreaId;                        /*区域ID*/
    ULONG  ulAdminStatus;                   /*admin状态*/
    ULONG  ulOperStatus;                    /*操作状态*/
    ULONG  ulImportAsExtern;                /*区域类型
                                              1 - IMPORT_EXTERNAL
                                              2 - IMPORT_NO_EXTERNAL
                                              3 - IMPORT_NSSA*/
    ULONG  ulSummary;                       /*引入Summary LSAs到stub和NSSA区域的标志
                                              1 - SEND_AREA_SUMMARY
                                              0 - NO_AREA_SUMMARY*/
    ULONG  ulNssaTranslatorRole;            /*NSSA区域中的边界路由有把7类报文转换为5类报文的能力
                                              1 - ALWAYS
                                              2 - CANDIDATE备选*/
    ULONG  ulNssaTranslatorState;           /*NSSA区域中的边界路由是否把7类报文转换为5类报文
                                              1 - STATE_ENABLED，上面参数将修改为ALWAYS
                                              2 - STATE_ELECTED，备选NSSA边界路由将进行报文转换
                                              3 - STATE_DISABLED，备选NSSA边界路由不进行报文转换*/
    ULONG  ulTransitCapability;             /*This parameter indicates whether the area can carry data
                                              traffic that neither originates nor terminates in the area itself.
                                              1 - TRUE
                                              2 - FASLE*/
    ULONG  ulLsaRfshIntvl;                  /*LSA周期泛洪间隔时间*/
    ULONG  ulStubMetric;                    /*Stub区域的默认Metric值*/
}OSPF6_SHOW_AREA_S;

/*STRUCT<NBR显示结构体，此数据结构包括ospf6 nbr mib(amb_osp3_pm_nbr)中用户所关心的字段>*/
typedef struct tagOSPF6_SHOWNBR_S
{     
    ULONG  ulProcessId;                     /*进程ID*/
    ULONG  ulInstanceId;                    /*Instance ID */ 
    ULONG  ulAreaId;                        /*区域ID*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1];/*出接口名称*/ 
    ULONG  ulNbrId;                         /*邻居Router ID*/   
    UCHAR  ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN]; /*邻居地址*/
    ULONG  ulNbrState;                      /*邻居状态*/
    ULONG  ulNbrPriority;                   /*邻居优先级*/
    ULONG  ulDeadTime;                      /*邻居失效间隔*/
    ULONG  ulBFDSessionID;                  /*邻居BFD会话ID*/
    ULONG  ulHelloSuppressed;               /*Hello抑制*/
    ULONG  ulPermanence;                    /*邻居动态or静态*/

    /* Added by likaikun00213099, 邻居查询新增维测信息, 2014/4/18 */
    UCHAR  ucNbrIfIpAddr[OSPF6_MAX_INET_ADDR_LEN]; /*邻居接口地址*/
    ULONG  ulNeighbourDR;                   /*邻居DR*/
    ULONG  ulNeighbourBDR;                  /*邻居BDR*/
    ULONG  ulNeighbourGRState;              /*邻居GR状态*/
    ULONG  ulNbrLastUpdTime;                /*邻居达到FULL或离开FULL之后的累计时间，单位:秒*/
    ULONG  ulNbrUpDownTimes;                /*邻居UP/DOWN次数*/
    ULONG  ulOptions;                       /*邻居选项*/
    /* End of Added by likaikun00213099, 邻居查询新增维测信息, 2014/4/18 */
}OSPF6_SHOWNBR_S;

/*Added by w00207740, 查询MJ信息, 2013/12/28 */
typedef struct tagOSPF6_PMMJSHOW_S
{
  ULONG ApplIndex;
  ULONG InterfaceId;              
  ULONG PartnerIndex;
  ULONG RowStatus;                
  ULONG AdminStatus;      
  ULONG OperStatus;                      
  ULONG JoinStatus;           
} OSPF6_PMMJSHOW_S;

typedef struct tagOSPF6_PMSJSHOW_S
{
  ULONG ApplIndex;
  ULONG MasterIndex;
  ULONG JoinIndex;
  ULONG JoinStatus;
  ULONG InterfaceId;
} OSPF6_PMSJSHOW_S;


/*STRUCT<路由器LSA具体信息>*/
typedef struct tagOSPF6_LINK_DESC
{
    UCHAR   ucType;                            /* Type(1~4) */
    UCHAR   ucPadding;                         /*填充*/
    USHORT  usMetric;                          /* Metric */
    ULONG   ulLinkIfId;                        /* Link Interface ID */
    ULONG   ulNbrLinkIfId;                     /* Neighbor Link Interface ID */
    ULONG   ulNbrRouterId;                     /* Neighbor Router ID */
}OSPF6_LINK_DESC_S;

/*STRUCT<路由器LSA结构体>*/
typedef struct tagOSPF6_ROUTER_LSA
{
    ULONG  ulOptions;                          /* Option:DC(0x20) R(0x10) NP(0x08) MC(0x04) E(0x02) V6(0x01)*/
    UCHAR  ucBitFlags;                         /* Bit:NT(0x10) W(0x08) V(0x04) E(0x02) B(0x01)*/
    UCHAR  ucPadding;                          /*填充*/
    USHORT usLinkCount;                        /*link数*/
    OSPF6_LINK_DESC_S   stRtrDescription[OSPF6_LSA_MAX_RTR_LINK_D]; /*Route LSA具体信息*/
}OSPF6_ROUTER_LSA_S;

/*STRUCT<网络LSA结构体>*/
typedef struct tagOSPF6_NETWORK_LSA
{
    ULONG  ulOptions;                             /* Option:DC(0x20) R(0x10) NP(0x08) MC(0x04) E(0x02) V6(0x01)*/
    ULONG  ulNetNum;                              /* 网络个数 */
    ULONG  ulAttachedRtrId[OSPF6_LSA_MAX_NET_NBR];/*attached rt ID*/
}OSPF6_NETWORK_LSA_S;

/*STRUCT<区域间前缀LSA结构体>*/
typedef struct tagOSPF6_PREFIX_DESC
{
    UCHAR  ucPrfxLen;                           /* Prefix Length */
    UCHAR  ucPrfxOpt;                           /* Prefix Option:NU(0x01) LA(0x02) MC(0x04)P(0x08) */
    USHORT usPrfxMetric;                        /* Prefix Metric */
    UCHAR  ucPrfxAddr[OSPF6_MAX_INET_ADDR_LEN];  /* Prefix address */
}OSPF6_PREFIX_DESC_S;

/*STRUCT<区域内路由器LSA结构体>*/
typedef struct tagOSPF6_INTRA_PREFIX_LSA
{
    ULONG  ulMetric;                            /* Metric */
    OSPF6_PREFIX_DESC_S stPrfxDescription;      /*前缀具体信息*/
}OSPF6_INTRA_PREFIX_LSA_S;

/*STRUCT<区域间路由器LSA结构体>*/
typedef struct tagOSPF6_INTER_AREA_RTR_LSA
{
    ULONG  ulOptions;                           /* Option:DC(0x20) R(0x10) NP(0x08) MC(0x04) E(0x02) V6(0x01)*/
    ULONG  ulMetric;                            /* Metric */
    ULONG  ulDestRouterId;                      /* Destination Router ID */
}OSPF6_INTER_AREA_RTR_LSA_S;

/*STRUCT<AS外部LSA结构体>*/
typedef struct tagOSPF6_AS_EXTERNAL_LSA
{
    UCHAR  ucBitFlags;                          /* Bit:E(0x04) F(0x02) T(0x01)*/
    UCHAR  ucPadding[3];                        /*填充*/
    ULONG  ulMetric;                            /* Metric */
    UCHAR  ucPrfxLen;                           /* Prefix Length */
    UCHAR  ucPrfxOpt;                           /* Prefix Option:NU(0x01) LA(0x02) MC(0x04)P(0x08) */
    USHORT usRefLsType;                         /* Referenced LS type */
    UCHAR ucPrfxAddr[OSPF6_MAX_INET_ADDR_LEN]; /* Prefix address */
    UCHAR ucFwdAddr[OSPF6_MAX_INET_ADDR_LEN];   /* Forwarding address */
    ULONG  ulExtRouteTag;                       /* External Route Tag */
    ULONG  ulRefLinkStateID;                    /* Referenced Link State ID : 暂时该字段为0
                                                   取决于usRefLsType*/
}OSPF6_AS_EXTERNAL_LSA_S;

/*STRUCT<NSSA LSA结构体>*/
typedef OSPF6_AS_EXTERNAL_LSA_S OSPF6_NSSA_LSA_S;

/*STRUCT<链路LSA结构体>*/
typedef struct tagOSPF6_LINK_LSA
{
    UCHAR  ucRtrPri;                            /* Router Priority */
    UCHAR  ucPadding[3];                        /*填充*/
    ULONG  ulOptions;                           /* Option:DC(0x20) R(0x10) NP(0x08) MC(0x04) E(0x02) V6(0x01)*/
    ULONG  ulPrfxNum;                           /* prefixes number */
    UCHAR ucLinkLocalAddr[OSPF6_MAX_INET_ADDR_LEN]; /* link-local address */
    OSPF6_PREFIX_DESC_S stPrfxDescription[OSPF6_LSA_MAX_PRFX_D];/*前缀具体信息*/
}OSPF6_LINK_LSA_S;

/*STRUCT<区域内前缀LSA结构体>*/
typedef struct tagOSPF6_INTRA_AREA_PRFX_LSA
{
    USHORT usPrfxNum;                           /* Prefix Number */
    USHORT usRefLsType;                         /* Referenced LS type */
    ULONG  ulRefLsId;                           /* Referenced LS ID */
    ULONG  ulRefAdvRouterId;                    /* Referenced advertising router ID */
    OSPF6_PREFIX_DESC_S stPrfxDescription[OSPF6_LSA_MAX_PRFX_D];/*前缀具体信息*/
}OSPF6_INTRA_AREA_PRFX_LSA_S;

/*STRUCT<LSA的头部信息结构体>*/
typedef struct tagOSPF6_LSAHdr
{
    USHORT usLsAge;                             /* 老化时间 */
    USHORT usLsType;                            /* LSA 类型 */
    UCHAR  ucLsTypeBits;                        /* 链路状态:U(0x80,LSA Handling) S2(0x40) S1(0x20,Flooding Scope) */
    UCHAR  ucPadding[3];                        /*填充*/
    ULONG  ulLinkId;                            /* 链路ID */
    ULONG  ulAdvRtr;                            /* 通告路由器ID */
    LONG   lLsSeqNum;                           /* 序列号 */
    USHORT usLsChksum;                          /* 校验和 */
    USHORT usLength;                            /* 包含LSA头部在内的LSA长度 */
}OSPF6_LSAHDR_S;

/*STRUCT<所有的LSA共有结构体>*/
typedef struct tagOSPF6_SHOW_LSADATA
{
    OSPF6_LSAHDR_S stLsaHdr;                            /* LSA header */
    union
    {
        OSPF6_ROUTER_LSA_S          stRtr6Lsa;           /* Router LSA */
        OSPF6_NETWORK_LSA_S         stNet6Lsa;           /* Network LSA */
        OSPF6_INTRA_PREFIX_LSA_S    stIntraPrfx6Lsa;     /* Intra-prefix LSA */
        OSPF6_INTER_AREA_RTR_LSA_S  stInterAreaRtr6Lsa;  /* Inter-Area_Router LSA */ 
        OSPF6_AS_EXTERNAL_LSA_S     stAsExternal6Lsa;    /* AS-external LSA */ 
        OSPF6_NSSA_LSA_S            stNssa6Lsa;          /* NSSA LSA */ 
        OSPF6_LINK_LSA_S            stLink6Lsa;          /* Link LSA*/ 
        OSPF6_INTRA_AREA_PRFX_LSA_S stInterAreaPrfx6Lsa; /* Inter_Area_prefix LSA */ 
    }OSPF6_LSA_U;
}OSPF6_SHOW_LSADATA_S;

/*STRUCT<LSA DB查询结构体>*/
typedef struct tagOSPF6_SHOWLSDB 
{ 
    ULONG  ulRouterId;                          /*Router ID*/
    ULONG  ulAreaId;                            /*区域ID*/
    USHORT usProcessId;                         /*进程ID*/
    USHORT usRes;                               /*填充*/
    OSPF6_SHOW_LSADATA_S stLSAData;             /*区域查询信息*/
} OSPF6_SHOWLSDB_S;

#define  stRtrLsa   stLSAData.OSPF6_LSA_U.stRtr6Lsa
#define  stNetLsa   stLSAData.OSPF6_LSA_U.stNet6Lsa
#define  stIntraPrfxLsa   stLSAData.OSPF6_LSA_U.stIntraPrfx6Lsa
#define  stInterAreaRtrLsa   stLSAData.OSPF6_LSA_U.stInterAreaRtr6Lsa
#define  stAsExternalLsa   stLSAData.OSPF6_LSA_U.stAsExternal6Lsa
#define  stNssaLsa   stLSAData.OSPF6_LSA_U.stNssa6Lsa
#define  stLinkLsa   stLSAData.OSPF6_LSA_U.stLink6Lsa
#define  stInterAreaPrfxLsa   stLSAData.OSPF6_LSA_U.stInterAreaPrfx6Lsa


/*STRUCT<路由下一条信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_ROUTING_NEXTHOP
{
    ULONG ulOutIfIndex;                         /*出接口索引*/
    UCHAR ucAddress[OSPF6_MAX_INET_ADDR_LEN];   /*下一跳地址*/
}OSPF6_ROUTING_NEXTHOP_S;

/*STRUCT<路由信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_SHOWROUTE
{
    ULONG  ulProcessId;                     /*进程ID*/
    ULONG  ulAreaId;                        /*区域ID*/
    INET6_ADDRESS_S stDestIpAddr;           /*目的网路地址*/
    ULONG  ulAdvRouterId;                   /*通告路由器ID*/
    ULONG  ulPathCost;                      /*路径代价*/   
    ULONG  ulType2Cost;                     /*Only valid for type 2 external paths*/
    UCHAR  ucPathType;                      /*路径类型
                                              0x01 Indicates a path to a destination belonging to one of the router's 
                                                   attached OSPF areas.  
                                              0x02 Indicates a path to a destination in another OSPF area. 
                                              0x03 Indicates a path to a destination external to OSPF with a metric
                                                   expressed in the same units as the OSPF internal metric.  
                                              0x04 Indicates a path to a destination external to OSPF with a metric an order
                                                   of magnitude larger than the OSPF internal metric.  A cost in the type-2
                                                   metric is considered greater than any cost in the type-1 metric. */
    UCHAR  ucOriginType;                    /*DCL 尚未完善,目前只为0*/
    UCHAR  ucDestType;                      /*路由目的地址类型 
                                              0x01 Area boundary or AS boundary router.    
                                              0x02 Transit or stub network.    
                                              0x03 Address range which if active will be a reject route. 
                                              0x04 Address range corresponding to an NSSA type-7 area aggregation.
                                              0x05 Route entry used solely for the root of the patricia tree.   */    
    UCHAR  ucEntryType;                     /*路由状态0-active 1-Inactive*/
    UCHAR  ucRouterEntryFlags;              /*路由标记1*/
    UCHAR  ucRouterEntryFlags2;             /*路由标记2*/
    UCHAR  ucPadding[2];                    /*填充*/
    ULONG  ulExternalRouteTag;              /*外部路由标记*/
    USHORT usNumOfEqualCostPaths;           /*平衡路由个数*/
    USHORT usPadding;                       /*填充*/                                     
    OSPF6_ROUTING_NEXTHOP_S stOspf6Rt[OSPF6_MAX_EQCOST_PATH];/*path Infomation*/
}OSPF6_SHOWROUTE_S;

/*STRUCT<区域聚合查询信息结构体，此数据结构包括ospf6 area agg(amb_osp3_pm_area_aggregate)中用户关心的字段>*/
typedef struct tagOSPF6_SHOWAREA_AGG
{
    ULONG  ulProcessId;                     /*进程ID*/
    ULONG  ulAreaId;                        /*区域ID*/
    ULONG  ulAdvert;                        /*1代表通告， 0代表不通告*/
    INET6_ADDRESS_S stPrefixAddr;           /*Prefix address*/
}OSPF6_SHOWAREA_AGG_S;


/*STRUCT<OSPF6引入策略信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_SHOWREDIST
{
    ULONG  ulProcessId;                     /*进程ID*/
    OSPF6_RPM_PLCYREDIS_S stReDis;          /*指定进程对应的引入策略信息*/
}OSPF6_SHOWREDIST_S;

/*STRUCT<OSPF6引入过滤信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_SHOW_EXPORT_FILTER_S
{
    ULONG  ulProcessId;                     /*进程ID*/
    OSPF6_RPM_PLCYDIST_S stPlcyDist;        /*指定进程对应的引入过滤信息*/
}OSPF6_SHOW_EXPORT_FILTER_S;

/*STRUCT<OSPF6接收过滤信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_SHOW_IMPORT_FILTER_S
{
    ULONG  ulProcessId;                     /*进程ID*/
    union
    {
        ULONG ulAclNum;                    /*ACL6规则组号
                                              范围:2000~2999*/
    } stFltrName;   
}OSPF6_SHOW_IMPORT_FILTER_S;

/*STRUCT<OSPF6静态邻居生效信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_SHOWPEER
{
    ULONG  ulProcessId;                          /*进程ID*/
    ULONG  ulInstanceId;                         /*Instance ID*/ 
    ULONG  ulIfIndex;                            /*接口索引*/ 
    UCHAR  ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN];   /*手工配置对端的地址*/
    ULONG  ulNbrPriority;                        /*邻居优先级*/
    ULONG  ulNbrState;                          /*邻居的状态*/
    ULONG  ulNbrRtrId;                          /*邻居router id*/
}OSPF6_SHOWPEER_S;

/*STRUCT<OSPF6静态邻居配置信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_SHOWCFGPEER
{
    ULONG  ulInstanceId;                         /*Instance ID*/ 
    ULONG  ulIfIndex;                            /*接口索引*/ 
    UCHAR  ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN];   /*手工配置对端的地址*/
    ULONG  ulNbrPriority;                        /*邻居优先级*/
}OSPF6_SHOWCFGPEER_S;

/*STRUCT<接口绑定信息查询结构体，供查询接口输出>*/
typedef struct tagOSPF6_SHOWINTFBIND
{
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH + 1];/*接口名*/
    UCHAR  ucIpAddr[OSPF6_MAX_INET_ADDR_LEN];       /*IP6地址*/
    ULONG  ulProcessId;                           /*进程ID*/
    ULONG  ulInstanceId;                          /*Instance ID */ 
    ULONG  ulAreaId;                              /*区域ID*/
    ULONG  ulIfIndex;                             /*接口索引值*/
}OSPF6_SHOWINTFBIND_S;

/*STRUCT<OSPF6接口属性信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_SHOWINTFATTR
{
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH + 1];/*接口名*/
    ULONG  ulInstanceId;                        /*Instance ID */ 
    ULONG  ulIfIndex;                           /*接口索引*/ 
    ULONG  ulAttrBits;                          /*有效属性Bits位 */ 
    ULONG  ulIfNetworkType;                     /*接口网络类型
                                                  1 - 广播
                                                  2 - NBMA
                                                  3 - 点到点
                                                  5 - 点到多点*/
    ULONG  ulIfMetric;                          /*接口COST*/
    ULONG  ulIfPriority;                        /*优先级*/
    ULONG  ulRxmtInterval;                      /*LSA重传时间*/ 
    ULONG  ulTransDelay;                        /*接口传输延时*/ 
    ULONG  ulHelloInterval;                     /*Hello间隔 FastHello无效时有效*/  
    ULONG  ulDeadInterval;                      /*Dead间隔*/ 
    ULONG  ulFastHelloMulti;                    /*Fast Hello Multiple*/
    ULONG  ulPollInterval;                      /*轮询间隔*/ 
    ULONG  ulMtuIgnoreFlg;                      /*MTU忽略标记*/ 
    ULONG  ulGrHelperMode;
    ULONG  ulGrHelperPeriod;
    ULONG  ulGrHelperAccNum;
}OSPF6_SHOWINTFATTR_S;

/*STRUCT<OSPF6协议优先级信息结构体，供查询接口输出>*/
typedef struct tagOSPF6_PREFERENCE_SHOW
{
    ULONG  ulVrfIndex;                      /*VRF索引*/
    UCHAR  ucPreferenceInt;                 /*区域内路径上的代价，范围:1~255*/
    UCHAR  ucPreferenceExt;                 /*外部路径上的代价，范围:1~255*/    
    UCHAR  ucPadding[2];                    /*填充*/
}OSPF6_PREFERENCE_SHOW_S;




typedef struct tagOSPF6_SHOWCUMLTVE_OUT
{
    ULONG  ulRouterId;
    USHORT usProcessId;
    USHORT usPadding;/*后续扩展*/
   
    /* packets stat. */
    ULONG  ulInHello;              /* input hello pkts */
    ULONG  ulOutHello;
    ULONG  ulInDbDescr;            /* input DB Description */
    ULONG  ulOutDbDescr;   
    ULONG  ulInLinkStateReq;       /* input Link-State Req */
    ULONG  ulOutLinkStateReq;  
    ULONG  ulInLinkStateUpdate;    /* Input Link-State Update */
    ULONG  ulOutLinkStateUpdate;
    ULONG  ulInLinkStateAck;       /* Link-State Ack  */
    ULONG  ulOutLinkStateAck;

    /* LSAs originated by this router  */
    ULONG  ulRouter;
    ULONG  ulNetwork;
    ULONG  ulInterAreaPrefix;
    ULONG  ulInterAreaRouter;
    ULONG  ulExternal;
    ULONG  ulNssa;   
    ULONG  ulLinkScope;
    ULONG  ulIntraAreaPrefix;
    ULONG  ulIntraAreaTE;
    ULONG  ulOpqExternal;
    ULONG  ulOriginateNewLsas;
    ULONG  ulRxNewLsas;

    ULONG  ulAreaBdr;    /* Area 边界路由器 */
    ULONG  ulAsBdr;      /* as 边界路由器 */

    /* Added by likaikun00213099, 统计进程的各状态的邻居, 2014/4/21 */
    ULONG  ulNumNbr;     /* 进程的邻居总数 */
    ULONG  ulNbrState[OSPF6_NBR_MAX_STATES + 1]; /* 不同状态的邻居个数 */
    /* End of Added by likaikun00213099, 统计进程的各状态的邻居, 2014/4/21 */
}OSPF6_SHOWCUMLTVE_OUT_S;

typedef struct tagOSPF6_SHOWERROR_OUT
{    
    USHORT   usProcessId;   /* Process Id of the process */
    USHORT   usRes;
 
    /* general error,还未识别出报文类型 */
    ULONG ulGenErrLen;       /* 长度非法 */
    ULONG ulGenErrIntf;      /* 找不到对应的接口 */
    ULONG ulGenErrType;      /* 报文类型非法 */
    ULONG ulGenErrChck;      /* check sum 非法 */
    ULONG ulGenErrArea;      /* 域非法 */
    ULONG ulGenErrNbr;       /* 邻居不匹配 */
    ULONG ulGenErrAuth;

    /* hello error */
    ULONG ulHelloErrSuppressed; /* 禁止hello报文 */
    ULONG ulHelloErrLen;        /* 报文长度非法 */
    ULONG ulHelloErrChck;       /* check sum 失败 */
    ULONG ulHelloErrNBMA;       /* 未知的NBMA邻居 */
    ULONG ulHelloErrP2P;        /* 未知的P2P邻居 */

    /* DD error */
    ULONG ulDdErrLen;           /* 报文长度 */
    ULONG ulDdErrMTU;           /* MTU非法 */
    ULONG ulDdErrNbState;       /* 邻居状态非法 */
    ULONG ulDdErrSequence;      /* 报文序列号非法 */
    ULONG ulDdErrDuplicate;     /* 报文为复制 */
    ULONG ulDdErrBadPkt;        /* 其他非法 */

    /* LS Req error */
    ULONG ulLsReqErrNbState;    /* 邻居状态非法 */
    ULONG ulLsReqErrLen;        /* 报文长度非法 */
    ULONG ulLsReqErrBadReq;     /* 其他ls req非法 */

    /* LS Update error */
    ULONG ulLsUdpErrLen;        /* 报文长度非法 */
    ULONG ulLsUdpErrNbState;    /* 邻居状态非法 */
    
    /* LS Ack error */
    ULONG ulLsAckErrLen;       /* 报文长度非法 */
    ULONG ulLsAckErrNbState;   /* 邻居状态非法 */
}OSPF6_SHOWERROR_OUT_S;

/*add for S-IP-003-OSPFv3-102*/
typedef struct tagOSPF6_SHOWPLCYDIST_OUT
{
    USHORT  usProcessId;
    CHAR    ucPadding[2];
    /* 
    for ulPlcyDirectFlag:
        #define DF_OSPF_TO_RM 1
        #define DF_RM_TO_OSPF 2
    */
    ULONG   ulPlcyDirectFlag;
    OSPF6_RPM_PLCYDIST_S stPlcyDist;
}OSPF6_SHOWPLCYDIST_OUT_S;

/*******************************************************************************
*    Func Name: OSPF6_CMM_Handle_Close
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 用于OSPF6 查询的关闭操作
*  Description: 关闭Handle句柄
*        Input: ULONG ulHandle:Handle<非空>
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Handle_Close(ULONG ulHandle);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Entity_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: OSPF6进程信息查询的Open操作
*  Description: OSPF6进程信息查询的Open操作,用于获取OSPF6进程信息
*        Input: OSPF6_FILTER_S *pstFilterIn:过滤条件指针<非空> 
*       Output: ULONG *pulHandle:Handle句柄<非空>
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Entity_GetFirst
*               OSPF6_CMM_Entity_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Entity_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Entity_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取第一个OSPFv3实例信息
*  Description: 获取第一个OSPFv3实例信息
*        Input: ULONG ulHandle:Handle句柄<非空> 
*       Output: OSPF6_ENTITY_SHOW_S *pstShow:实例信息<非空> 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Entity_Open
*               OSPF6_CMM_Entity_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Entity_GetFirst(ULONG ulHandle,OSPF6_ENTITY_SHOW_S *pstShow); 
/*******************************************************************************
*    Func Name: OSPF6_CMM_Entity_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个OSPFv3实例信息
*  Description: 获取下一个OSPFv3实例信息
*        Input: ULONG ulHandle:Handle句柄<非空> 
*       Output: OSPF6_ENTITY_SHOW_S *pstShow:实例信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Entity_Open
*               OSPF6_CMM_Entity_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Entity_GetNext(ULONG ulHandle,OSPF6_ENTITY_SHOW_S *pstShow);
/*******************************************************************************
*    Func Name: OSPF6_ShowEntityInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示OSPFv3实例信息
*  Description: 显示OSPFv3实例信息
*        Input: USHORT usProcId:进程ID<0~0xffff；0：存在的所有进程；1～0xffff：指定的OSPF进程号>
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowEntityInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Intf_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 返回一个Handle，用于打开下一个结点获取接口信息
*  Description: 返回一个Handle，用于打开下一个结点获取接口信息
*        Input: OSPF6_FILTER_S *pstFilterIn:过滤条件<非空>
*       Output: ULONG *pulHandle:Handle句柄
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Intf_GetFirst
*               OSPF6_CMM_Intf_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Intf_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Intf_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个接口信息
*  Description: 获取一个接口信息
*        Input: ULONG ulHandle:Handle句柄<非空>
*       Output: OSPF6_SHOWINTF_S *pstIntfIn:接口信息<非空>
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Intf_Open
*               OSPF6_CMM_Intf_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Intf_GetFirst(ULONG ulHandle,OSPF6_SHOWINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Intf_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个接口信息
*  Description: 获取下一个接口信息
*        Input: ULONG ulHandle:Handle句柄<非空>
*       Output: OSPF6_SHOWINTF_S *pstIntfIn:接口信息<非空>
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Intf_Open
*               OSPF6_CMM_Intf_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Intf_GetNext (ULONG ulHandle,OSPF6_SHOWINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowIntfInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示接口信息
*  Description: 显示接口信息
*        Input: USHORT usProcId:进程ID<0~0xffff；0：存在的所有进程；1～0xffff：指定的OSPF进程号>
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowIntfInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Area_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 返回一个Handle，用于打开下一个结点获取区域信息
*  Description: 返回一个Handle，用于打开下一个结点获取区域信息
*        Input: OSPF6_FILTER_S *pstFilterIn:过滤条件
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Area_GetFirst
*               OSPF6_CMM_Area_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Area_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Area_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个区域信息
*  Description: 获取一个区域信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_AREA_S *pstAreaIn:区域信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Area_Open
*               OSPF6_CMM_Area_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Area_GetFirst(ULONG ulHandle,OSPF6_SHOW_AREA_S *pstAreaIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Area_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个区域信息
*  Description: 获取下一个区域信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_AREA_S *pstAreaIn:区域信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Area_Open
*               OSPF6_CMM_Area_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Area_GetNext (ULONG ulHandle,OSPF6_SHOW_AREA_S *pstAreaIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowAreaInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示区域信息
*  Description: 显示区域信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*                               0：存在的所有进程；1～0xffff：指定的OSPF进程号。
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowAreaInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Nbr_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 返回一个Handle，用于打开下一个结点获取邻居信息
*  Description: 返回一个Handle，用于打开下一个结点获取邻居信息
*        Input: OSPF6_FILTER_S *pstFilterIn:过滤条件<非空>
*       Output: ULONG *pulHandle:Handle句柄
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Nbr_GetFirst
*               OSPF6_CMM_Nbr_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Nbr_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Nbr_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个邻居信息
*  Description: 获取一个邻居信息
*        Input: ULONG ulHandle:Handle句柄<非空>
*       Output: OSPF6_SHOWNBR_S *pstNbrIn:邻居信息<非空>
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Nbr_Open
*               OSPF6_CMM_Nbr_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Nbr_GetFirst(ULONG ulHandle,OSPF6_SHOWNBR_S *pstNbrIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Nbr_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个邻居信息
*  Description: 获取下一个邻居信息
*        Input: ULONG ulHandle:Handle句柄<非空>
*       Output: OSPF6_SHOWNBR_S *pstNbrIn:邻居信息<非空>
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Nbr_Open
*               OSPF6_CMM_Nbr_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Nbr_GetNext (ULONG ulHandle,OSPF6_SHOWNBR_S *pstNbrIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowNbrInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示邻居信息
*  Description: 显示邻居信息
*        Input: USHORT usProcId:进程ID<0~0xffff；0：存在的所有进程；1～0xffff：指定的OSPF进程号>
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowNbrInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Lsdb_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 返回一个Handle，用于打开下一个结点获取LSDB信息
*  Description: 返回一个Handle，用于打开下一个结点获取LSDB信息
*        Input: OSPF6_LSDB_FILTER_S *pstFilterIn:过滤条件
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Lsdb_GetFirst
*               OSPF6_CMM_Lsdb_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Lsdb_Open(ULONG *pulHandle,OSPF6_LSDB_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Lsdb_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个LSDB信息
*  Description: 获取一个LSDB信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWLSDB_S *pstLsdbIn:LSDB信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Lsdb_Open
*               OSPF6_CMM_Lsdb_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Lsdb_GetFirst(ULONG ulHandle,OSPF6_SHOWLSDB_S *pstLsdbIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Lsdb_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个LSDB信息
*  Description: 获取下一个LSDB信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWLSDB_S *pstLsdbIn:LSDB信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Lsdb_Open
*               OSPF6_CMM_Lsdb_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Lsdb_GetNext (ULONG ulHandle,OSPF6_SHOWLSDB_S *pstLsdbIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowLsdbInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示LSDB信息
*  Description: 显示LSDB信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*                               0：存在的所有进程；1～0xffff：指定的OSPF进程号。
*               USHORT usLsaType:LSA类型,范围：0,宏定义OSPF6_XXXXX_LSA
*                               0：所有的LSA类型；OSPF6_XXXXX_LSA：指定的LSA类型。
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowLsdbInfo(USHORT usProcId,USHORT usLsaType);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Route_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 返回一个Handle，用于打开下一个结点获取Route信息
*  Description: 返回一个Handle，用于打开下一个结点获取Route信息
*        Input: OSPF6_FILTER_S *pstFilterIn:过滤条件
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Route_GetFirst
*               OSPF6_CMM_Route_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Route_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Route_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个Route信息
*  Description: 获取一个Route信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWROUTE_S *pstRouteIn:Route信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Route_Open
*               OSPF6_CMM_Route_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Route_GetFirst(ULONG ulHandle,OSPF6_SHOWROUTE_S *pstRouteOut);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Route_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个Route信息
*  Description: 获取下一个Route信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWROUTE_S *pstRouteIn:Route信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Route_Open
*               OSPF6_CMM_Route_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Route_GetNext (ULONG ulHandle,OSPF6_SHOWROUTE_S *pstRouteOut);
/*******************************************************************************
*    Func Name: OSPF6_ShowRouteInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示Route信息
*  Description: 显示Route信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*                               0：存在的所有进程；1～0xffff：指定的OSPF进程号。
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowRouteInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Redist_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 查询OSPF6引入策略配置的第一条信息
*  Description: 返回一个Handle，用于打开下一个结点获取Redistribute信息
*        Input: OSPF6_FILTER_S *pstFilterIn:过滤条件
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Redist_GetFirst
*               OSPF6_CMM_Redist_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Redist_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Redist_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个路由引入策略信息
*  Description: 获取一个路由引入策略信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWREDIST_S *pstRedistIn:Redistribute信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Redist_Open
*               OSPF6_CMM_Redist_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Redist_GetFirst(ULONG ulHandle,OSPF6_SHOWREDIST_S *pstRedistIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Redist_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个路由引入策略信息
*  Description: 获取下一个路由引入策略信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWREDIST_S *pstRedistIn:Redistribute信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Redist_Open
*               OSPF6_CMM_Redist_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Redist_GetNext (ULONG ulHandle,OSPF6_SHOWREDIST_S *pstRedistIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowRedistInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示路由引入策略信息
*  Description: 显示路由引入策略信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*                                  0：存在的所有进程；1～0xffff：指定的OSPF进程号。
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowRedistInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_ExportFilter_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 查询OSPF6引入过滤配置的第一条信息
*  Description: 返回一个Handle，用于打开下一个结点获取过滤信息
*        Input: OSPF6_FILTER_S *pstFilterIn:过滤条件
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_ExportFilter_GetFirst
*               OSPF6_CMM_ExportFilter_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ExportFilter_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ExportFilter_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个过滤信息
*  Description: 获取一个过滤信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_EXPORT_FILTER_S *pstDistIn:过滤信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_ExportFilter_Open
*               OSPF6_CMM_ExportFilter_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ExportFilter_GetFirst(ULONG ulHandle,OSPF6_SHOW_EXPORT_FILTER_S *pstDistIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ExportFilter_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个过滤信息
*  Description: 获取下一个过滤信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_EXPORT_FILTER_S *pstDistIn:过滤信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_ExportFilter_Open
*               OSPF6_CMM_ExportFilter_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ExportFilter_GetNext (ULONG ulHandle,OSPF6_SHOW_EXPORT_FILTER_S *pstDistIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowExportFilterInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示过滤信息
*  Description: 显示过滤信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*                                  0：存在的所有进程；1～0xffff：指定的OSPF进程号。
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowExportFilterInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_AreaAgg_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 查询OSPF6区域聚合的第一条信息
*  Description: 返回一个Handle，用于打开下一个结点获取区域聚合信息
*        Input: OSPF6_AREA_AGG_FILTER_S *pstFilterIn:过滤条件
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_AreaAgg_GetFirst
*               OSPF6_CMM_AreaAgg_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_AreaAgg_Open(ULONG *pulHandle,OSPF6_AREA_AGG_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_AreaAgg_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个区域聚合信息
*  Description: 获取一个区域聚合信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWAREA_AGG_S *pstAreaAggIn:区域聚合信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_AreaAgg_Open
*               OSPF6_CMM_AreaAgg_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_AreaAgg_GetFirst(ULONG ulHandle,OSPF6_SHOWAREA_AGG_S *pstAreaAggIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_AreaAgg_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个区域聚合信息
*  Description: 获取下一个区域聚合信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWAREA_AGG_S *pstAreaAggIn:区域聚合信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_AreaAgg_Open
*               OSPF6_CMM_AreaAgg_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_AreaAgg_GetNext (ULONG ulHandle,OSPF6_SHOWAREA_AGG_S *pstAreaAggIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowAreaAggInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示区域聚合信息
*  Description: 显示区域聚合信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*                               0：存在的所有进程；1～0xffff：指定的OSPF进程号。
*               ULONG ulAreaId: 区域ID
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowAreaAggInfo(USHORT usProcId,ULONG ulAreaId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Peer_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 返回一个Handle，用于打开下一个结点获取静态配置邻居信息
*  Description: 返回一个Handle，用于打开下一个结点获取静态配置邻居信息
*        Input: OSPF6_PEER_FILTER_S *pstFilterIn:过滤条件
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Peer_GetFirst
*               OSPF6_CMM_Peer_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Peer_Open(ULONG *pulHandle,OSPF6_PEER_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Peer_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取一个静态配置邻居信息
*  Description: 获取一个静态配置邻居信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWPEER_S *pstPeerIn:静态配置邻居信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Peer_Open
*               OSPF6_CMM_Peer_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Peer_GetFirst(ULONG ulHandle,OSPF6_SHOWPEER_S *pstPeerIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Peer_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 获取下一个静态配置邻居信息
*  Description: 获取下一个静态配置邻居信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWPEER_S *pstPeerIn:静态配置邻居信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_Peer_Open
*               OSPF6_CMM_Peer_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Peer_GetNext (ULONG ulHandle,OSPF6_SHOWPEER_S *pstPeerIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowPeerInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 显示静态配置邻居信息
*  Description: 显示静态配置邻居信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*                                  0：存在的所有进程；1～0xffff：指定的OSPF进程号。
*               ULONG ulInstanceId:实例ID,范围: 0~255。
*                                  OSPF6_ALL_INST_FILTER:不指定实例号查询。
*               CHAR *szIfName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowPeerInfo(USHORT usProcId,ULONG ulInstanceId,CHAR *szIfName);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfBind_Open
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: 返回一个Handle，用于打开下一个结点获取接口配置信息
*  Description: 返回一个Handle，用于打开下一个结点获取接口配置信息，其中过滤条件接口索引
*               和进程ID可以组合查询
*        Input: OSPF6_INTF_BIND_FILTER_S *pstFilterIn:过滤条件<非空>
*       Output: ULONG *pulHandle:Handle句柄
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_IntfBind_GetFirst
*               OSPF6_CMM_IntfBind_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfBind_Open(ULONG *pulHandle,OSPF6_INTF_BIND_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfBind_GetFirst
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: 获取一个接口配置信息
*  Description: 获取一个接口配置信息
*        Input: ULONG ulHandle:Handle句柄<非空>
*               OSPF6_SHOWINTFBIND_S *pstIntfIn:接口配置信息<非空>
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_IntfBind_Open
*               OSPF6_CMM_IntfBind_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfBind_GetFirst(ULONG ulHandle,OSPF6_SHOWINTFBIND_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfBind_GetNext
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: 获取下一个接口配置信息
*  Description: 获取下一个接口配置信息
*        Input: ULONG ulHandle:Handle句柄<非空>
*               OSPF6_SHOWINTFBIND_S *pstIntfIn:接口配置信息<非空>
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_IntfBind_Open
*               OSPF6_CMM_IntfBind_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfBind_GetNext(ULONG ulHandle,OSPF6_SHOWINTFBIND_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowIntfBindInfo
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: 显示用户配置的接口信息
*  Description: 显示用户配置的接口信息
*        Input: USHORT usProcId:进程ID<0~0xffff；0：存在的所有进程；1～0xffff：指定的OSPF进程号>
*               CHAR *szIfName:接口名<非空>
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowIntfBindInfo(USHORT usProcId,CHAR *szIfName);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Pref_GetByVrfName
* Date Created: 2009-09-04
*       Author: hanna55555
*      Purpose: 获取指定VRF下的OSPF协议优先级
*  Description: 获取指定VRF下的OSPF协议优先级
*        Input: CHAR *pszVrfName:VRF名字
*               OSPF6_PREFERENCE_SHOW_S *pstPrefIn:优先级配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-04   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Pref_GetByVrfName(CHAR *pszVrfName,OSPF6_PREFERENCE_SHOW_S *pstPrefIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowPreferenceInfo
* Date Created: 2009-09-04
*       Author: hanna55555
*      Purpose: 显示指定VRF下的OSPF协议优先级
*  Description: 显示指定VRF下的OSPF协议优先级
*        Input: CHAR *pszVrfName:VRF名字
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-04   hanna55555              Create
*
*******************************************************************************/
VOID OSPF6_ShowPreferenceInfo(CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ImportFilter_Open
* Date Created: 2009-06-17
*       Author: wangbin (62223) & luogaowei(61496)
*      Purpose: 查询OSPF6接收过滤配置的第一条信息
*  Description: 返回一个Handle，用于打开下一个结点获取过滤信息
*        Input: OSPF6_FILTER_S *pstFilterIn:过滤条件
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_ImportFilter_GetFirst
*               OSPF6_CMM_ImportFilter_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   wangbin (62223) & luogaowei(61496)             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ImportFilter_Open(ULONG *pulHandle, OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ImportFilter_GetFirst
* Date Created: 2009-06-17
*       Author: wangbin (62223) & luogaowei(61496)
*      Purpose: 获取一个过滤信息
*  Description: 获取一个过滤信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_IMPORT_FILTER_S *pstDistIn:过滤信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_ImportFilter_Open
*               OSPF6_CMM_ImportFilter_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   wangbin (62223) & luogaowei(61496)             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ImportFilter_GetFirst(ULONG ulHandle, OSPF6_SHOW_IMPORT_FILTER_S *pstDistIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ImportFilter_GetNext
* Date Created: 2009-06-17
*       Author: wangbin (62223) & luogaowei(61496)
*      Purpose: 获取下一个过滤信息
*  Description: 获取下一个过滤信息
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_IMPORT_FILTER_S *pstDistIn:过滤信息
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_ImportFilter_Open
*               OSPF6_CMM_ImportFilter_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   wangbin (62223) & luogaowei(61496)             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ImportFilter_GetNext (ULONG ulHandle, OSPF6_SHOW_IMPORT_FILTER_S *pstDistIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowImportFilterInfo
* Date Created: 2009-06-17
*       Author: wangbin (62223) & luogaowei(61496)
*      Purpose: 显示接收过滤信息
*  Description: 显示接收过滤信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*                                  0：存在的所有进程；1～0xffff：指定的OSPF进程号。
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-10   wangbin (62223) & luogaowei(61496)             Create
*
*******************************************************************************/
VOID OSPF6_ShowImportFilterInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfAttr_Open
* Date Created: 2009-09-18
*       Author: hanna55555
*      Purpose: 返回一个Handle，用于打开下一个结点获取接口属性配置信息
*  Description: 返回一个Handle，用于打开下一个结点获取接口属性配置信息
*        Input: OSPF6_INTF_ATTR_FILTER_S *pstFilterIn:实例ID和接口索引可以组合查询
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_IntfAttr_GetFirst
*               OSPF6_CMM_IntfAttr_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-18   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfAttr_Open(ULONG *pulHandle,OSPF6_INTF_ATTR_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfAttr_GetFirst
* Date Created: 2009-09-18
*       Author: hanna55555
*      Purpose: 获取一个接口属性配置信息
*  Description: 获取一个接口属性配置信息
*        Input: ULONG ulHandle:句柄
*               OSPF6_SHOWINTFBIND_S *pstIntfIn:接口属性配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_IntfAttr_Open
*               OSPF6_CMM_IntfAttr_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-18   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfAttr_GetFirst(ULONG ulHandle,OSPF6_SHOWINTFATTR_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfAttr_GetNext
* Date Created: 2009-09-18
*       Author: hanna55555
*      Purpose: 获取下一个接口属性配置信息
*  Description: 获取下一个接口属性配置信息
*        Input: ULONG ulHandle:句柄
*               OSPF6_SHOWINTFBIND_S *pstIntfIn:接口属性配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_IntfAttr_Open
*               OSPF6_CMM_IntfAttr_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-18   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfAttr_GetNext(ULONG ulHandle,OSPF6_SHOWINTFATTR_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowIntfAttrInfo
* Date Created: 2009-09-18
*       Author: hanna55555
*      Purpose: 显示用户配置的接口属性信息
*  Description: 显示用户配置的接口属性信息
*        Input: ULONG ulInstanceId:实例ID,范围: 0~255。
*                                  OSPF6_ALL_INST_FILTER:不指定实例号查询。
*               CHAR *szIfName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-18   hanna55555              Create
*
*******************************************************************************/
VOID OSPF6_ShowIntfAttrInfo(ULONG ulInstanceId,CHAR *szIfName);
/*******************************************************************************
*    Func Name: OSPF6_CMM_CfgPeer_Open
* Date Created: 2009-09-21
*       Author: hanna55555
*      Purpose: 返回一个Handle，用于打开下一个结点获取静态邻居配置信息
*  Description: 返回一个Handle，用于打开下一个结点获取静态邻居配置信息
*        Input: OSPF6_CFGPEER_FILTER_S *pstFilterIn:实例ID和接口索引可以组合查询
*       Output: ULONG *pulHandle:句柄
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_CfgPeer_GetFirst
*               OSPF6_CMM_CfgPeer_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-21   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_CfgPeer_Open(ULONG *pulHandle,OSPF6_CFGPEER_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_CfgPeer_GetFirst
* Date Created: 2009-09-21
*       Author: hanna55555
*      Purpose: 获取用户配置的第一个静态邻居信息
*  Description: 获取用户配置的第一个静态邻居信息
*        Input: ULONG ulHandle:句柄
*               OSPF6_SHOWCFGPEER_S *pstPeerIn:用户配置静态邻居信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_CfgPeer_Open
*               OSPF6_CMM_CfgPeer_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-21   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_CfgPeer_GetFirst(ULONG ulHandle,OSPF6_SHOWCFGPEER_S *pstPeerIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_CfgPeer_GetNext
* Date Created: 2009-09-21
*       Author: hanna55555
*      Purpose: 获取用户配置的下一个静态邻居信息
*  Description: 获取用户配置的下一个静态邻居信息
*        Input: ULONG ulHandle:句柄
*               OSPF6_SHOWCFGPEER_S *pstPeerIn:用户配置静态邻居信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: OSPF6_CMM_CfgPeer_Open
*               OSPF6_CMM_CfgPeer_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-21   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_CfgPeer_GetNext(ULONG ulHandle,OSPF6_SHOWCFGPEER_S *pstPeerIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowCfgPeerInfo
* Date Created: 2009-09-21
*       Author: hanna55555
*      Purpose: 显示用户配置的静态邻居信息
*  Description: 显示用户配置的静态邻居信息
*        Input: ULONG ulInstanceId:实例ID,范围: 0~255。
*                                  OSPF6_ALL_INST_FILTER:不指定实例号查询。
*               CHAR *szIfName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-21   hanna55555              Create
*
*******************************************************************************/
VOID OSPF6_ShowCfgPeerInfo(ULONG ulInstanceId,CHAR *szIfName);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Cumul_Clear
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: 清除OSPF6的正确报文统计信息
*        Input: USHORT usProcessId:进程ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
VOID OSPF6_CMM_Cumul_Clear(USHORT usProcessId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Cumul_Open
* Date Created: 2010-03-30
*       Author: zhangbo146309
*      Purpose: 返回一个Handle，用于打开下一个结点获取正确报文的统计信息
*        Input: ULONG* pulHandle: Handle句柄
*               OSPF6_FILTER_S *pstFilterIn: 正确报文统计的过滤信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Cumul_Open(ULONG *pulHandle, OSPF6_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Cumul_GetFirst
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: 返回一个Handle，用于打开第一个结点获取正确报文的统计信息
*        Input: ULONG ulHandle: Handle句柄
*               OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut: 正确报文统计的信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Cumul_GetFirst (ULONG ulHandle, OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Cumul_GetNext
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: 获取一个Handle，用于打开下一个结点获取正确报文的统计信息
*        Input: ULONG ulHandle: Handle句柄
*               OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut: 正确报文统计的信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Cumul_GetNext (ULONG ulHandle, OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut); 

/*******************************************************************************
*    Func Name: OSPF6_ShowCumul
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: 显示OSPF6的正确报文统计信息
*        Input: USHORT usProcessId:进程ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
VOID OSPF6_ShowCumul(USHORT usProcessId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Error_Clear
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: 清除OSPF6的错误报文统计信息
*        Input: USHORT usProcessId:进程ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
VOID OSPF6_CMM_Error_Clear(USHORT usProcessId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Error_Open
* Date Created: 2010-03-30
*       Author: zhangbo146309
*      Purpose: 返回一个Handle，用于打开下一个结点获取错误的报文的统计信息
*        Input: ULONG* pulHandle: Handle句柄
*               OSPF6_FILTER_S *pstFilterIn: 错误报文统计的过滤信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Error_Open (ULONG *pulHandle, OSPF6_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Error_GetFirst
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: 返回一个Handle，用于打开第一个结点获取错误报文的统计信息
*        Input: ULONG ulHandle: Handle句柄
*               OSPF6_SHOWERROR_OUT_S *pstErrorOut: 错误报文统计的信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Error_GetFirst (ULONG ulHandle,OSPF6_SHOWERROR_OUT_S * pstErrorOut );


/*******************************************************************************
*    Func Name: OSPF6_CMM_Error_GetNext
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: 返回一个Handle，用于打开下一个结点获取错误报文的统计信息
*        Input: ULONG ulHandle: Handle句柄
*               OSPF6_SHOWERROR_OUT_S *pstErrorOut: 错误报文统计的信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Error_GetNext (ULONG ulHandle, OSPF6_SHOWERROR_OUT_S * pstErrorOut );

/*******************************************************************************
*    Func Name: OSPF6_ShowError
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: 显示OSPF6的错误报文统计信息
*        Input: USHORT usProcessId:进程ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
VOID OSPF6_ShowError(USHORT usProcessId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_PolicyDist_Open
* Date Created: 2014-04-10
*       Author: w00207740
*  Description: 打开OSPFv3引入／导出过滤策略表
*        Input: ULONG* pulHandle: 出参，返回句柄
*               OSPF6_FILTER_S * pstPolicyDistIn:过滤条件
*       Output: 
*       Return: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-10   w00207740               Create for story S-IP-003-OSPFv3-102
*
*******************************************************************************/
ULONG  OSPF6_CMM_PolicyDist_Open ( ULONG* pulHandle, OSPF6_FILTER_S * pstPolicyDistIn );
/*******************************************************************************
*    Func Name: OSPF6_CMM_PolicyDist_GetFirst
* Date Created: 2014-04-10
*       Author: w00207740
*  Description: 用于获取一条OSPF引入／导出过滤策略
*        Input: ULONG ulHandle:策略表句柄
*               OSPF6_SHOWPLCYDIST_OUT_S * pstPolicyDistOut:返回策略信息
*       Output: 
*       Return: 错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-10   w00207740               Create for story S-IP-003-OSPFv3-102
*
*******************************************************************************/
ULONG OSPF6_CMM_PolicyDist_GetFirst ( ULONG ulHandle, OSPF6_SHOWPLCYDIST_OUT_S * pstPolicyDistOut );

/*******************************************************************************
*    Func Name: OSPF6_CMM_PolicyDist_GetNext
* Date Created: 2014-04-10
*       Author: w00207740
*  Description: 用于获取下一条OSPF引入／导出过滤策略
*        Input: ULONG ulHandle:策略表句柄
*               OSPF6_SHOWPLCYDIST_OUT_S * pstPolicyDistOut:返回策略信息
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-10   w00207740               Create for story S-IP-003-OSPFv3-102
*
*******************************************************************************/
ULONG OSPF6_CMM_PolicyDist_GetNext ( ULONG ulHandle, OSPF6_SHOWPLCYDIST_OUT_S * pstPolicyDistOut );


VOID OSPF6_ShowPolicyDistInfo(USHORT usProcessId);


#ifdef __cplusplus
        }
#endif /* __cplusplus */
        
#endif /* _OSPF6_CMM_API_H_ */

