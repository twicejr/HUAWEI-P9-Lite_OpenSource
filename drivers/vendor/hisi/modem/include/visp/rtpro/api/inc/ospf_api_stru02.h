/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_stru02.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description:
*   01 OSPF API 结构定义(SGSN接口整改)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                
*  2008-12-23   wangchengyang            modify for statis(error & cumul)
*******************************************************************************/
#ifndef _OSPF_API_STRU02_H
#define _OSPF_API_STRU02_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*21 新开发接口结构体*/

/* Begin BC3D03313 liangjicheng 2010-06-22 调整与RTM结构一致*/
/*配置/删除 OSPF出方向的路由过滤，即配置从OSPF到RM的路由过滤*/
typedef struct tagOSPF_RPM_PLCYDIST
{
    union
    {
        ULONG ulAccNum;         /* Access List Number */
    } stFltrName;
    USHORT  usProcessID;    /* AS Number/Process ID */
    UCHAR   ucProtocolID;    /* Protocol ID */
    UCHAR   ucPadding;
     
    /*Begin BC3D02905 liangjicheng*/
    union
    {        
        ULONG ulAccNum;      /* Next hop Access List Number */        
    } stHopFltrName;
    /*End    BC3D02905 liangjicheng*/
    
} OSPF_RPM_PLCYDIST_S;
/* End   BC3D03313 liangjicheng 2010-06-22 */

#if 101 
typedef struct tagOSPF_SHOWIF
{
    USHORT  usProcessId; 
    USHORT  usPadding;    
}OSPF_SHOWIF_S;

typedef struct tagOSPF_SHOWIF_OUT
{
    ULONG ulAreaId;                             /*01 区域ID*/
    ULONG ulIfIpAddr;                             /*02 地址*/
    ULONG ulIfIpMask;                             /*-- 地址掩码*/
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH + 1];/*03 接口名*/
    ULONG ulIfMetric;                           /*04 接口COST*/

    /*OSPF接口网络类型 1-广播 2-NBMA 3-点到点 5-点到多点 10 环回*/
    ULONG ulIfNetworkType;                      /*05 网络类型*/
    ULONG ulDrPriority;                         /*06 DR优先级*/
    /* no item*/                                /*07 --------*/
    ULONG ulIfState;                            /*08 接口状态*/  
    ULONG ulHelloInterval;                      /*09 Hello间隔 FastHello无效时有效*/  
    ULONG ulFastHelloInterval;                  /*-- FastHello间隔 0无效 其它有效*/
    ULONG ulDeadInterval;                       /*10 Dead间隔*/ 
    ULONG ulDr;                                 /*11 DR*/ 
    ULONG ulBdr;                                /*12 BDR*/ 
    
    ULONG ulAuthType;                           /*13 接口生效的认证类型*/ 
    ULONG ulIfCfgAuthType;                      /*-- 接口配置的认证类型*/ 

    /*Begin for BC3D02736 接口认证（或区域认证）Keyid值用户可配 l00147446 10-02-27*/
    ULONG ulAuthKeyId;                          /*13 接口生效的认证Key Id*/ 
    ULONG ulIfCfgAuthKeyId;                     /*-- 接口配置的认证Key Id*/ 
    /*End for BC3D02736*/

    /* no item*/                                /*14 Smart hello是否使能*/
    ULONG ulProcessId;                          /*15 进程号*/ 

    ULONG ulPollInterval;                       /*-- 轮询间隔*/ 
    ULONG ulRxmtInterval;                       /*-- LSA重传时间*/ 
    ULONG ulInfTransDelay;                      /*-- 接口传输延时*/ 
    ULONG ulIfMtuSize;                          /*-- 接口MTU*/ 

    /*以下字段为VISP特有字段*/
    ULONG ulAddrlessif;     
    ULONG ulIfIndex;
    ULONG ulLsaCount;   
    
    /*LSU packet delay for reduce the network traffic Unit:ms Default:100 */
    ULONG ulLSUTransmitDelay; 
    /*被动标志,当时1时,接口不再接收发送Hello报文 默认:0*/
    ULONG ulPassive;
    ULONG ulRemoteIfIndex;
    ULONG ulMtusizePcntge;
    ULONG ulMaxHitlessGracePeriod;
    ULONG ulFastHelloMultiplier;
    ULONG ulMtuIgnoreFlg;
    ULONG ulAdminStatus;
    ULONG ulAutoDelNbrFlag;                         /*Default: 1*/
    ULONG ulGrHelperMode;
    /* add for BC3D02908  */
    ULONG ulAccNum;
    /* end for BC3D02908  */
    /*Added by liubinKF35460, 增加一个流量工程属性变量, 2011/5/20   问题单号:OSPF_20110519_01 */
    ULONG ulSupportQos;
    /* End of Added by liubinKF35460, 2011/5/20   问题单号:OSPF_20110519_01 */
}OSPF_SHOWIF_OUT_S;

#endif

#if 102
typedef struct tagOSPF_SHOWNEIGHBOR
{
    USHORT  usProcessId; 
    USHORT  usPadding;   
}OSPF_SHOWNEIGHBOR_S;

typedef struct tagOSPF_SHOWNBR_OUT_S
{     
    ULONG ulAreaId;                                     /*01 区域ID*/
    ULONG ulIfIpAddr;                                   /*02 接口地址*/
    ULONG ulNeighborRouterId;                           /*03 邻居Router ID*/   
    ULONG ulNeighborIpAddr;                             /*04 邻居地址*/
    ULONG ulProcessId;                                  /*05 进程ID*/
    ULONG ulNeighborState;                              /*06 邻居状态*/
    ULONG ulNeighborPriority;                           /*07 邻居优先级*/
                                       
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH + 1];        /*08 出接口名称*/ 
    ULONG ulInactivityInterval;                         /*09 邻居失效间隔*/
    ULONG ulNeighbourDR;                                /*10 邻居DR*/
    ULONG ulNeighbourBDR;                               /*10 邻居BDR*/
    ULONG ulNeighbourGRState;                           /*11 邻居BDR*/
    ULONG ulBFDSessionID;                               /*12 邻居BFD会话ID*/

    ULONG ulHelloSuppressed;                            /*-- Hellp 抑制*/
    /*Neighbor is Dynamical, Peer is static, Here return Dynamical*/
    ULONG ulPermanence;                                 /*-- 邻居动态or静态*/
    
    ULONG ulNbrLastUpdTime;                           /*邻居达到FULL或离开FULL之后的累计时间，单位:秒*/
    ULONG ulNbrUpDownTimes;                         /*邻居UP/DOWN次数*/
}OSPF_SHOWNBR_OUT_S;
#endif

#if 103
typedef struct tagOSPF_SHOWROUTING
{
    USHORT  usProcessId; 
    USHORT  usPadding;   
}OSPF_SHOWROUTING_S;


typedef struct tagOSPF_SHOWROUTING_OUT
{
    ULONG ulProcessId;                                  /* NR01*/
    ULONG ulAreaId;                                     /*01 区域ID*/
    ULONG ulDestIpAddr;                                 /*02 目的网路地址*/
    ULONG ulDestIpMask;                                 /*03 目的网路地址掩码*/ 
    ULONG ulAdvRouterId;
    
    /* 04 路径类型
    0x01 Indicates a path to a destination belonging to one of the router's 
         attached OSPF areas.  
    0x02 Indicates a path to a destination in another OSPF area. 
    0x03 Indicates a path to a destination external to OSPF with a metric
         expressed in the same units as the OSPF internal metric.  
    0x04 Indicates a path to a destination external to OSPF with a metric an order
         of magnitude larger than the OSPF internal metric.  A cost in the type-2
         metric is considered greater than any cost in the type-1 metric. */

    ULONG ulPathCost;                                   /*05 路径代价*/   
    ULONG ulType2Cost;                                  /*Only valid for type 2 external paths*/
    
    UCHAR ucPathType;                                   /*04 路径类型*/ 
    UCHAR ucOriginType;              /*DCL 尚未完善。路由来源类型 1-RTM引入路由 2-LSA引入*/
   
    /*-- 路由目的地址类型 
    0x01 Area boundary or AS boundary router.    
    0x02 Transit or stub network.    
    0x03 Address range which if active will be a reject route. 
    0x04 Address range corresponding to an NSSA type-7 area aggregation.
    0x05 Route entry used solely for the root of the patricia tree.   */    
    UCHAR ucDestType;    
    UCHAR ucEntryType;                                  /*06 路由状态0-Inactive 1-active*/
    
    UCHAR ucRouterEntryFlags; 
    UCHAR ucRouterEntryFlags2;    
    UCHAR ucPadding[2];
    
    ULONG ulExternalRouteTag;
    /***************************************************************************/
    /* External route tag.  This is not used by the OSPF protocol, but         */
    /* external routes with a different external route tag should be           */
    /* considered different, and all should be advertised.                     */
    /***************************************************************************/
    /*UCHAR ucExternal_Route_Tag[4]; Don't use Delete it                       */

    /***************************************************************************/
    /* NextHop Infomation                                                      */
    /***************************************************************************/
    /*--01 The size of the appended next hops. */
    /*ULONG ulNextHopSize;*/     
    /*--02 The number of equal cost paths */
    
    USHORT usNumOfEqualCostPaths;
    USHORT usPadding;                                       
    /*--03 path Infomation*/
    OSPF_ROUTING_NEXTHOP_S stOspfRt[OSPF_MAX_EQCOST_PATH];
}OSPF_SHOWROUTING_OUT_S;
#endif

#if 105
typedef struct tagOSPF_SHOWPEERCFG
{
    USHORT   usProcessId;
    USHORT   usRes;
}OSPF_SHOWPEERCFG_S;
typedef struct tagOSPF_SHOWPEERCFG_OUT
{
    ULONG   ulPeerIpAddr;                   /*01 手工配置对端的地址*/
    ULONG   ulProcessId;                    /*02 进程ID*/
    ULONG   ulNbrPriority;                  /*03 邻居优先级*/
}OSPF_SHOWPEERCFG_OUT_S;
#endif

/*6   此接口没有，按照如下形式补充 */
#if 106
typedef struct tagOSPF_SHOWNETWORK
{
    USHORT   usProcessId;
    USHORT   usIsAllVRF;
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR    szVrfName[OSPF_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_SHOWNETWORK_S;

typedef struct tagOSPF_SHOWNETWORK_OUT
{
    ULONG   ulAreaId;                       /*01 区域ID*/
    ULONG   ulIpAddr;                       /*02 地址*/
    ULONG   ulIpMask;                       /*03 地址掩码*/
    ULONG   ulProcessId;                    /*04 进程ID*/
    ULONG   ulVrfIndex;                     /*05 VrfIndex */
    /*End for BC3D03465, 2010/8/5 */
}OSPF_SHOWNETWORK_OUT_S;

#endif

#if 107
typedef struct tag_OSPF_SHOWOSPF_BRIEF
{
    USHORT   usProcessId;       /* Process Id of the process */
    USHORT   usRes;
}OSPF_SHOWOSPF_BRIEF_S;

typedef struct tag_OSPF_SHOWOSPF_BRIEF_OUT
{
    ULONG   ulRouterId;         /*01 RouterId for this process */
    USHORT  usProcessId;        /*02 Process Id for the process */
    UCHAR   ucPreferenceINT;
    UCHAR   ucPreferenceEXT;
    ULONG   ulExternLsaCount;
    ULONG   ulOriginateNewLsaCount;
    ULONG   ulRxNewLsaCount;
    ULONG   ulExtLsaRfshIntvl;
    ULONG   ulAsbrFlg;          /*Asbr flag*/
    ULONG   ulCompRfc1583;      /*兼容Rfc1583标志 1-True(兼容) 0-False*/
    ULONG   ulDoGrHitless;           /*Do grace hitless*/
    ULONG   ulDoGrUnplannedHitless;  /*Do grace unplanned hitless*/
    ULONG   ulHitlessGrPeriod;       /*Gr period*/
    ULONG   ulHitlessRestartReason;  /*Restart Reason*/
    ULONG   ulCalcThrshIncSpfUpd;    /*区域内重计算门限值*/
    ULONG   ulFastDownFlag;          /* 快速down标记 for CGP BC3D02904*/
    /*Add for BC3D02970 添加VrfIndex*/
    ULONG   ulVrfIndex;
    /*End for BC3D02866*/

    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    ULONG ulAccNum;
    /*End for BC3D03437 at 2010-07-16*/
    ULONG   ulCFGRouterId;      /*配置的Router ID */
}OSPF_SHOWOSPF_BRIEF_OUT_S;
#endif

#if 108
typedef struct tagOSPF_SHOWCUMLTVE
{
    USHORT  usProcessId;
    USHORT  usRes;
}OSPF_SHOWCUMLTVE_S;

typedef struct tagOSPF_SHOWCUMLTVE_OUT
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
    ULONG  ulSumNet;
    ULONG  ulSumAsbr;
    ULONG  ulExternal;
    ULONG  ulNssa;
    ULONG  ulOpqLink;
    ULONG  ulOpqArea;
    ULONG  ulOpqExternal;
    ULONG  ulOriginateNewLsas;
    ULONG  ulRxNewLsas;

    ULONG  ulAreaBdr;    /* Area 边界路由器 */
    ULONG  ulAsBdr;      /* as 边界路由器 */
    /* End:wangchengyang 2008-12-23 */

    /*Modified by liangjicheng 00103192, OSPF-03, 2010/10/25   问题单号:DTS2010102501546 */
    ULONG  ulMaxAgeLsaNoImport;    /*OSPF 引入路由删除造成的 MAX-AGE LSA 个数*/
    ULONG  ulMaxAgeLsaTimer;       /*3600秒到时 MAX-AGE LSA 个数*/
    ULONG  ulMaxAgeLsaTotal;       /*所有flush的LSA个数）*/
    /*End of Modified by liangjicheng 00103192, 2010/10/25   问题单号:DTS2010102501546 */

    /*Added by guojianjun178934, 添加OSPF NSR性能临时调试信息, 2013/4/7   问题单号:20130118_01 */
    ULONG  ulRestoreTime;
    ULONG  ulRestoreUnpacketTime;
    ULONG  ulRestorePacket;
    /* End of Added by guojianjun178934, 2013/4/7   问题单号:20130118_01 */
}OSPF_SHOWCUMLTVE_OUT_S;
#endif

#if 109
typedef struct tagOSPF_SHOWERROR
{
    USHORT   usProcessId;   /* Process Id of the process */
    USHORT   usRes;
}OSPF_SHOWERROR_S;

typedef struct tagOSPF_SHOWERROR_OUT
{    
    USHORT   usProcessId;   /* Process Id of the process */
    USHORT   usRes;
    ULONG ulBadVersion;         /* 版本不匹配 */
    ULONG ulAreaMismatch;       /* 区域号不匹配*/
    ULONG ulUnknownNbmaNbr;     /* 未知NBMA网络邻居*/
    ULONG ulUnknownVirtualNbr;  /* 未知虚邻居 */
    ULONG ulAuthTypeMismatch;   /* 认证类型不匹配 */
    ULONG ulAuthKeyIdMismatch;  /* 认证KeyID不匹配 */
    ULONG ulAuthFailure;        /* 认证失败 */
    ULONG ulNetmaskMismatch;    /* 掩码不匹配 */
    ULONG ulHelloInterval;      /* HelloInterval不匹配 */
    ULONG ulDeadInterval;       /* DeadInterval不匹配 */
    ULONG ulOptionMismatch;     /* 选项位不匹配 */
    ULONG ulMtuMismatch;        /* MTU不匹配 */
    ULONG ulDuplicateRouterId;  /* RouterID重复 */
    ULONG ulBadPacket;          /* 非上述错误导致packet drop */
}OSPF_SHOWERROR_OUT_S;
#endif

#if 110
typedef struct tagOSPF_RPM_PLCYREDIS
{
    UCHAR   ucRPAID;
    UCHAR   ucPadding;
    USHORT  usRPAProcessID;
    ULONG   enMetricType;
    ULONG   ulMetricVal;
} OSPF_RPM_PLCYREDIS_S;
 
typedef struct tagOSPF_SHOWIMPORT
{
    USHORT   usProcessId;
    USHORT   usRes;
}OSPF_SHOWIMPORT_S;

typedef struct tagOSPF_SHOWIMPORT_OUT
{
    ULONG   ulProcessId;
    OSPF_RPM_PLCYREDIS_S stReDis;
}OSPF_SHOWIMPORT_OUT_S;
#endif

#if 111

typedef struct tagOSPF_SHOWPLCYDIST
{
    USHORT   usProcessId;
    USHORT   usRes;
}OSPF_SHOWPLCYDIST_S;

typedef struct tagOSPF_SHOWPLCYDIST_OUT
{
    USHORT  usProcessId;
    CHAR    ucPadding[2];
/*#define DF_OSPF_TO_RM 1
#define DF_RM_TO_OSPF 2*/
    ULONG   ulPlcyDirectFlag;
    OSPF_RPM_PLCYDIST_S stPlcyDist;
}OSPF_SHOWPLCYDIST_OUT_S;
#endif

#if 201 
            
typedef struct tagOSPF_CFGREDISTRIBUTE
{
    USHORT bNoFlag;
    USHORT usProcessId;
    OSPF_RPM_PLCYREDIS_S stPolicyRedist;
}OSPF_CFGREDISTRIBUTE_S;
#endif

#if 202
typedef struct tagOSPF_CFGDISTRIBUTE
{
    USHORT bNoFlag;
    USHORT usProcessId;
    OSPF_RPM_PLCYDIST_S stPolicyDist;
}OSPF_CFGDISTRIBUTE_S;
#endif

#if 203
/*Notes:参见ospf_api.h结构*/
#endif

#if 204
/*Notes:参见ospf_api.h结构*/
typedef struct tagOSPF_CFGIF_NETTYPE
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    UCHAR  bNoFlag;
    UCHAR  ucNetworkType;
    UCHAR ucPadding[2]; 
}OSPF_CFGIF_NETTYPE_S;

typedef struct tagOSPF_CFGIF_HELLO
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    USHORT usHelloInterval;
    USHORT bNoFlag;        /*1配置，0恢复默认值 10*/                  
}OSPF_CFGIF_HELLO_S;

typedef struct tagOSPF_CFGIF_DEAD
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    USHORT usDeadItvl;
    USHORT bNoFlag;        /*0配置，1恢复默认值 40*/   
    
    /*表明在使能fast hello，1s内发送hello报文的数目 Range<3-20> Default 5*/
    ULONG ulFast_Hello_Multiplier;
                             
}OSPF_CFGIF_DEAD_S;

typedef struct tagOSPF_CFGIF_RETRANSMIT
{
    CHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    USHORT usRetransInterval;
    UCHAR bNoFlag;
    UCHAR ucPadding[1];
}OSPF_CFGIF_RETRANSMIT_S;

typedef struct tagOSPF_CFGIF_PRIORITY
{
    CHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    UCHAR bNoFlag;
    UCHAR  ucPriority;
    UCHAR ucPadding[2];
}OSPF_CFGIF_PRIORITY_S;

typedef struct tagOSPF_CFGIF_COST
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG  ulIfCost;  /*Interface Metric [1-65535] default:1*/
    USHORT bNoFlag;   /*0-Set 1-Recover default */
    UCHAR ucPadding[2];
}OSPF_CFGIF_COST_S;
#endif

/*#endif*/
#if 22  /*22*/

#if 205
/*Notes:ospf_api.h 存在不一致的结构*/
typedef struct tagOSPF_CFGIFAUTHKEY
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    USHORT bNoFlag;
/*
#define OSPF_CFG_IF_AUTH_NULL         0x0
#define OSPF_CFG_IF_AUTH_SIMPLE       0x01
#define OSPF_CFG_IF_AUTH_MD5          0x02
#define OSPF_CFG_IF_AUTH_HMAC         0x03*/
    UCHAR  ucAuthenType;
    
/*
#define OSPF_IF_P***W***_PLAIN        0x01
#define OSPF_IF_P***W***_CIPHER       0x02*/
    UCHAR  ucPasswordType;

    CHAR  szPassword[OSPF_ENCRYPT_DATA_LENGTH+1];
    UCHAR  ucKeyId;
    UCHAR  ucPadding[3];
}OSPF_CFGIFAUTHKEY_S;

typedef struct tagOSPF_CFGAUTHENMODE
{
    USHORT bNoFlag;
    USHORT usProcessId;
    ULONG  ulAreaId;
    CHAR  szPassword[OSPF_ENCRYPT_DATA_LENGTH + 1];
    UCHAR  ucKeyId;

/*  #define OSPF_CFG_IF_AUTH_NULL         0x0
    #define OSPF_CFG_IF_AUTH_SIMPLE       0x01
    #define OSPF_CFG_IF_AUTH_MD5          0x02 
    #define OSPF_CFG_IF_AUTH_HMAC         0x03  */
    UCHAR  ucAuthenType;

/*  #define OSPF_AREA_P***W***_PLAIN    0x01
    #define OSPF_AREA_P***W***_CIPHER   0x02 */      
    UCHAR  ucPasswordType;
    UCHAR  ucPadding;
}OSPF_CFGAUTHENMODE_S;

#endif

#if 206        
typedef struct tagOSPF_CFGPREFERENCE
{
    USHORT bNoFlag;
    /*USHORT usProcessId;    */ /*进程id 不提供 */
    UCHAR  ucINTPreference;
    UCHAR  ucEXTPreference;
/*
#define OSPF_PREFERENCE_SWITH_INT        0x01
#define OSPF_PREFERENCE_SWITH_EXT        0x02
*/
    UCHAR  ucSwitch;
    UCHAR  ucPadding;
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[OSPF_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_CFGPREFERENCE_S;
#endif   

#if 207
/*此数据结构用来配置NSSA区域*/
typedef struct tagOSPF_CFGAREANSSA
{
    USHORT bNoFlag; /*表明是否把一个区域配置成nssa,0-设置 1-恢复普通区域*/
    USHORT usProcessId;                 /*进程id*/
    ULONG  ulAreaId;                    /*区域ID*/
/*
#define OSPF_CFG_NSSAOPT_DEFAULT    0x01  DCL不支持 bring default Type-7LSA to area NSSA   
#define OSPF_CFG_NSSAOPT_NOIMPORT   0x02  no import exterior route to NSSA area 
#define OSPF_CFG_NSSAOPT_NOSUMMARY  0x04  forbid ABR send Summary LSA to NSSA area 
#define OSPF_CFG_NSSAOPT_TRANSLATE_ROLE_ALWAYS  0x08  forbid NSSA area import route*/
    UCHAR  ucNssaOption;                /*NSSA option*/
    UCHAR  ucRes[3];                     /*填充位*/
}OSPF_CFGAREANSSA_S;
#endif

/*Modified by liangjicheng 00103192, Calc Delay, 2011/10/27   问题单号: REQ-201106295399-OSPF-PER */
/*此数据结构用来配置进程的计算延迟*/
typedef struct tagOSPF_CFGCALCDELAY
{
    USHORT usProcessId; 
    USHORT usPadding; 
    ULONG ulCaclDelay;  /*路由计算最大延时间隔(ms)，默认值2000，取值范围：1~10000*/
}OSPF_CFGCALCDELAY_S;
/*End of Modified by liangjicheng 00103192, 2011/10/27   问题单号: REQ-201106295399-OSPF-PER */

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 
