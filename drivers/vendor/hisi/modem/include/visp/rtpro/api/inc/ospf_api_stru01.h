/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_stru01.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF API 结构定义(基本开发)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create    
*  2009-01-20   l00147446                BC3D01126【OSPF】查询函数写越界  
*
*******************************************************************************/
#ifndef _OSPF_API_STRU01_H
#define _OSPF_API_STRU01_H
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*11 原开发接口结构体*/
/*此数据结构用来配置ASBR路由器*/
typedef struct tagOSPF_CFG_ASBR
{
    USHORT usProcessId;                   /*进程ID*/
    /*Modify for BC3D00579：描述错误 liangjicheng 2008-10-29 */
    USHORT usAsbrFlg;                    /*是否为ASBR的标志,1表示路由器为ASBR,
                                           0表示路由器不为ASBR，默认为1*/
    
    /*ULONG ulRouterId; */                   /*路由器ID*/
    
}OSPF_CFG_ASBR_S;



/*此数据结构用来创建或删除一个区域*/
typedef struct tagOSPF_CFGAREA
{
    ULONG  ulAreaId;                    /*区域ID*/ 
    USHORT bNoFlag;                     /*表明配置还是删除区域,0配置，1删除*/
    USHORT usProcessId;                 /*进程id*/
}OSPF_CFGAREA_S;

/*此数据结构用来配置路由聚合*/
typedef struct tagOSPF_CFGAREARANGE
{
    USHORT bNoFlag;                    /*表明是配置还是删除，1配置，0删除*/                 
    USHORT usProcessId;                /*进程ID*/
    ULONG ulAreaId;                    /*区域ID*/
    ULONG ulIpAddr;                    /*地址*/
    ULONG ulIpMask;                    /*掩码地址*/
    ULONG ulEffect;                    /*是否生效标志，1生效，0不生效*/
    ULONG ulLsdbType;                  /*lsdb type:summary link or nssa external link */
}OSPF_CFGAREARANGE_S;

/*此数据用来配置进程GR的相关参数*/
/*
#define OSPF_CFG_RESET_CFG_GRPARA   0x00
#define OSPF_CFG_RESET_SET_DOWN     0x01
#define OSPF_CFG_RESET_SET_UP       0x02
#define OSPF_CFG_RESET_SET_DOWNUP   0x03*/
typedef struct tagOSPF_CFGRESET
{
    USHORT usResetFlg;                 /*重启标志，
    0-设置参数，1-Down 2-UP 3-重起(DownUp)*/
    USHORT usProcessId;                /*进程ID*/
    ULONG ulDoGraceHitless;            /*平滑重启标志*/
    ULONG ulDoGraceUnplannedHitless;   /*无计划地平滑重启标志*/
    ULONG ulHitlessGrPeriod;           /*平滑重启周期*/
    ULONG ulhitlessGrReason;           /*平滑重启原因*/
}OSPF_CFGRESET_S;

/*Add for RPU BC3D02904*/
typedef struct tagOSPF_CFGFASTDOWN
{
  USHORT usProcessId;
  USHORT usFlag;/* 0 不使能  1 使能*/
}OSPF_CFGFASTDOWN_S;
/*End for RPU BC3D02904*/

typedef struct tagOSPF_CFGMAXPATH
{
    ULONG ulProcessId;
    ULONG ulEqRouterNums;
}OSPF_CFGMAXPATH_S;

typedef struct tagOSPF_CFGNEIGHBOR
{
    ULONG  ulNeighborIpAddr;
    USHORT bNoFlag;
    USHORT bPriority;
    USHORT usProcessId;
    UCHAR  ucPriority;
    UCHAR  ucRes;
}OSPF_CFGNEIGHBOR_S;

typedef struct tagOSPF_CFGNETWORK
{
    ULONG  ulAreaId;
    ULONG  ulNetworkAddr;
    ULONG  ulMaskLen;
    USHORT usProcessId;
    USHORT bNoFlag;
}OSPF_CFGNETWORK_S;

typedef struct tagOSPF_CFGPASSIVEIF
{
    /*被动标志,当时1时,接口不再接收发送Hello报文 默认:0*/
    USHORT usPassiveFlg;
    USHORT usProcessId;
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
}OSPF_CFGPASSIVEIF_S;

typedef struct tagOSPF_CFGPROC_WITHRID
{
    ULONG  ulRouterId;                /*路由器ID,用户指定*/
    USHORT usProcessId;               /*进程ID*/
    USHORT bNoFlag;                   /*创建或删除标志*/
    /* Modified by zhangliangzhi00187023, 【检视发现问题】在OSPF_CFG_CmdRouterOspfProc支持配置OSPF路由表中的平衡路由数目, 2012/8/7   问题单号:DTS2012080703017  */
    ULONG ulMaxEqCostPaths;           /* OSPF路由表中的等价路由条数，
                                        取值范围：0~32
                                        当设置为0时，表示不设置
                                        系统启动时默认为5条 */   
    /*End of Modified by zhangliangzhi00187023, 2012/8/7   问题单号:DTS2012080703017  */
                                        
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[OSPF_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_CFGPROC_WITHRID_S;

typedef struct tagOSPF_CFGPROC
{
    USHORT usProcessId;               /*进程ID*/
    USHORT bNoFlag;                   /*创建或删除标志*/
    /*Added by zhangliangzhi00187023, 【检视发现问题】支持配置OSPF路由表中的平衡路由数目, 2012/8/1   问题单号:DTS2012080105986 */
    ULONG ulMaxEqCostPaths;           /* OSPF路由表中的等价路由条数，
                                        取值范围：0~32
                                        当设置为0时，表示不设置
                                        系统启动时默认为5条 */
    /* End of Added by zhangliangzhi00187023, 2012/8/1   问题单号:DTS2012080105986 */

    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[OSPF_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_CFGPROC_S;
/*Add for BC3D02908*/
typedef struct tagOSPF_CFGGRHELPER
{
    /* ULONG usProcessId;*//* BC3D03437 取消进程配置 */
    UCHAR szIfname[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    ULONG ulAccNum;
    
}OSPF_CFGGRHELPER_S;
/*end BC3D02908*/
typedef struct tagOSPF_CFGGRHELPER_PRO
{
    ULONG usProcessId;
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    ULONG ulAccNum;
}OSPF_CFGGRHELPER_PRO_S;
/*End for BC3D03437 at 2010-07-16*/
typedef struct tagOSPF_CFGCOMPRFC1583
{
    ULONG ulProcessId;
    ULONG ulCompFlg;
}OSPF_CFGCOMPRFC1583_S;

typedef struct tagOSPF_CFGIFLSADELAY
{
    USHORT usProcessId;  /*ULONG->USHORT L*/ 
    USHORT usPadding;
    ULONG ulAreaId;
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG ulLsaDelay; 
}OSPF_CFGIFLSADELAY_S;

typedef struct tagOSPF_CFGIF_POLL
{
    ULONG ulProcessId;
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG ulPollItvl;
}OSPF_CFGIF_POLL_S;

typedef struct tagOSPF_CFG_MAXMTU
{
    /*Modified by liangjicheng 00103192, 接口修改，这里不做MTU设置, 2010/11/18   问题单号:DTS2010110104080  */
    /*ULONG ulProcessId;*/
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    /*ULONG ulMtuLen;*/  /*MTU 46-1560 Default 576 the same to VRP*/
    ULONG ulMtuIgnore;
    /*End of Modified by liangjicheng 00103192, 2010/11/18   问题单号:DTS2010110104080  */
}OSPF_CFG_MAXMTU_S;

typedef struct OSPF_CFGAREA_RFSHITVL
{
    ULONG ulProcessId;
    ULONG ulAreaId;
    ULONG ulRfshItvl;
}OSPF_CFGAREA_RFSHITVL_S;

typedef struct tagOSPF_CFGSPFITVL
{
    ULONG ulProcessId;
    ULONG ulSpfItvl;
}OSPF_CFGSPFITVL_S;

typedef struct tagOSPF_CFGAREASTUB
{
    USHORT bNoFlag;
    USHORT bNoSummaryFlag; /*1-VOS_TRUE不引入Summary  0-VOS_FALSE*/
    ULONG  ulAreaId;
    USHORT usProcessId; 
    USHORT usRes;
}OSPF_CFGAREASTUB_S;

typedef struct tagOSPF_CFG_VLINKPEER
{
    ULONG ulCfgFlg;
    ULONG ulProcessId;
    ULONG ulAreaId;
    ULONG ulNbrId;
}OSPF_CFG_VLINKPEER_S;

typedef struct tagOSPF_CFG_VLINKAUTH
{
    ULONG ulProcessId;
    ULONG ulAreaId;
    ULONG ulNbrId;
    ULONG ulAuthType;
    ULONG ulAuthkeyLen;
    UCHAR szAuthKeyValue[256];
    ULONG ulAuthUserDataLen;
    UCHAR szAuthUserDataValue[4];
}OSPF_CFG_VLINKAUTH_S;

typedef struct tagOSPF_CFG_VLINKPARA
{
    ULONG ulProcessId;
    ULONG ulAreaId;
    ULONG ulNbrId;
    ULONG ulHelloItvl;
    ULONG ulDeadItvl;
    ULONG ulRetransItvl;
    ULONG ulTransDelay;
}OSPF_CFG_VLINKPARA_S;


/*if中需要显示的数据项*/

/*此数据结构中包含AMB_OSPF_PM_LSDB中的用户关心的字段*/
typedef struct tagOSPF_SHOW_LSDB
{
    UCHAR ucAreaId[4];
    ULONG ulType;
    UCHAR ucLsId[4];
    UCHAR ucRouterId[4];
    ULONG ulProcessId;
    ULONG ulSequence;
    ULONG ulAge;
    ULONG ulChksum;
}OSPF_SHOW_LSDB_S;

/*此数据结构包含AMB_OSPF_PM_NBR中用户所关心的数据字段*/
typedef struct tagOSPF_SHOWINFO_NBR
{
    UCHAR ucIpAddr[4];
    ULONG ulAddr_Less_If;
    ULONG ulProcessId;
    UCHAR ucRouterId[4];
    ULONG ulPriority;
    ULONG ulPermanence;
    ULONG ulHello_Suppressed;
    UCHAR ucIf_Ip_Addr[4];
    ULONG ulDead_Time;
    UCHAR ucArea_Id[4];
    ULONG ulState;              /*neighbor state*/
}OSPF_SHOWINFO_NBR_S;

typedef struct tagINET_ADDRESS
{
    UCHAR ucType;
    UCHAR ucLength;
    UCHAR ucPad[2];
    UCHAR ucAddress[OSPF_MAX_INET_ADDR_LEN];
}INET_ADDRESS_S;

/*此数据结构包含ospf routing表中next-hop相关信息*/
typedef struct tagOSPF_ROUTING_NEXTHOP
{
    ULONG ulOutput_If_Index;
    INET_ADDRESS_S next_hop_inet_addr;
}OSPF_ROUTING_NEXTHOP_S;

/*此数据结构包含virtual if中用户关心的字段*/
typedef struct tagOSPF_SHOW_VIRTUAL_IF
{
    UCHAR ucAreaId[4];
    UCHAR ucNeighbor[4];
    ULONG ulProcessId;
    ULONG ulTransit_Delay;
    ULONG ulRetrans_Interval;
    ULONG ulHello_Interval;
    ULONG ulRtr_Dead_Interval;
    ULONG ulState;
    ULONG ulAuth_Type;
}OSPF_SHOW_VIRTUAL_IF_S;

/*此数据结构包含用户所关心的virtual lsdb中的字段*/
typedef struct tagOSPF_SHOW_VIRTUAL_LSDB
{
    UCHAR uctransit_area_id[4];
    UCHAR ucneighbor[4];
    ULONG ultype;
    UCHAR ucls_id[4];
    UCHAR ucrouter_id[4];
    ULONG ulappl_index;
    ULONG ulsequence;
    ULONG ulage;    
}OSPF_SHOW_VIRTUAL_LSDB_S;

typedef struct tagOSPF_SHOW_VIRTUAL_NBR
{
    UCHAR ucarea_id[4];
    UCHAR ucrtr_id[4];
    ULONG ulappl_index;
    UCHAR ucip_addr[4];
    ULONG ulstate;
    ULONG uldead_time;
}OSPF_SHOW_VIRTUAL_NBR_S;

#define OSPF_FILTER_ALL        0    
#define OSPF_FILTER_PROC       0x01
#define OSPF_FILTER_AREA       0x02
typedef struct tagOSPF_SHOWAREA
{
    USHORT  usFltFlag;/*取值范围:OSPF_FILTER_ALL        0    
                                OSPF_FILTER_PROC       0x01
                                OSPF_FILTER_AREA       0x02*/
    USHORT  usProcessId;       /* Process Id of the process */
    ULONG   ulAreaId;
}OSPF_SHOWAREA_S;

typedef struct tagOSPF_AREA_INFO
{
    ULONG ulAreaId;       /*host liangjicheng 2008-10-28*/
    LONG  lAuthType;
    ULONG ulAuthKeyLen;
    UCHAR ucAuthKeyValue[256]; 
    /*Begin for BC3D02736 接口认证（或区域认证）Keyid值用户可配 l00147446 10-02-27*/
    UCHAR ucAuthKeyId;
    UCHAR ucPad[3];
    /*End for BC3D02736*/
    ULONG ulAuthUserDataLen;
    UCHAR ucAuthUserData[4];   
}OSPF_AREA_INFO_S;

typedef struct tagOSPF_NETWORK
{
    ULONG ulOspfInstance;
    ULONG ulAreaId;
    ULONG ulNetworkAddr;
    ULONG ulNetworkAddrMaskLen;
}OSPF_NETWORK_S;

/*此数据结构包括ospf entity mib中供用户获取的字段*/
typedef struct tagOSPF_ENTITY_SHOW
{
    ULONG ulProcessId;             /*OSPF实例号*/
    UCHAR ucRouter_Id[4];          /*Router id*/
    ULONG ulAdmin_Status;          /*Admin Status 1-up 0-down  */
    ULONG ulOspfVersion;           /*Ospf version*/
    ULONG ulAsbrFlg;               /*Asbr flag*/
    ULONG ulCompRfc1583;           /*兼容Rfc1583标志 1-True(兼容) 0-False*/
    ULONG ulMaxPaths;              /*等价路由数目*/
    ULONG ulDo_Gr;                 /*Do grace hitless*/
    ULONG ulDo_Gr_Unplanned;       /*Do grace unplanned hitless*/
    ULONG ulGr_Period;             /*Gr period*/
    ULONG ulRestart_Reason;        /*Restart Reason*/
    ULONG ulCalc_Thrsh_Inc_Spf_Upd;/*区域内重计算门限值*/
    ULONG ulOper_Status;           /*操作状态*/
    /*Begin BC3D01346 l00147446 OSPF、RIP获取和显示接口缺少VRF信息 09-03-28*/
    ULONG ulVrfIndex;
    /*End BC3D01346 l00147446 OSPF、RIP获取和显示接口缺少VRF信息 09-03-28*/
    /*Added by guo00178934, 【Story】ROUTE_DR_023_S_001 进程查询添加默认值显示, 2011/5/20   问题单号:OSPF_20110519_02 */
    ULONG ulCalc_Max_Delay;         /*路由计算时延*/
    ULONG ulOpaque_Lsa_Support;    /*是否支持Opaque LSA*/
    ULONG ulTraffic_Eng_Support;   /*是否支持TE*/
    /* End of Added by guo00178934, 2011/5/20   问题单号:OSPF_20110519_02 */
    /*Added by guo00178934, SPC200需求：配置Router_ID, 2012/10/17   问题单号:20121013_1 */
    UCHAR ucCFGRouterId[4];       /*配置的Router id */
    /* End of Added by guo00178934, 2012/10/17   问题单号:20121013_1 */
}OSPF_ENTITY_SHOW_S;

/*此数据结构包括ospf if metric mib中用户所关心的字段*/
typedef struct tagOSPF_IF_METRIC_SHOW
{
    UCHAR ucIPAddr[4];             /*address*/
    ULONG ulAddr_Less_If;          /*address less if*/
    ULONG ulTos;                   /*The type of service metric being referenced*/
    ULONG ulProcess_Id;            /*Process Id*/
    ULONG ulValue;                 /*Metric value*/
}OSPF_IF_METRIC_SHOW_S;

/*此数据结构包括ospf area mib中用户所关心的字段*/
typedef struct tagOSPF_SHOW_AREA
{
    UCHAR ucAreaId[4];
    ULONG ulProcessId;

    /*BC3D00572 liangjicheng 2008-10-29 */
    ULONG ulImport_As_Extern; /*1-IMPORT_EXTERNAL 2-IMPORT_NO_EXTERNAL 3-IMPORT_NSSA*/

    /*BC3D00574 liangjicheng 2008-10-29 */
    ULONG ulSummary;          /*1-SEND_AREA_SUMMARY  0-NO_AREA_SUMMARY*/
    
    /*ADD for BC3D02758 增加默认路由控制 l00147446 10-03-02*/  
    ULONG ulDefaultlsa;       /*1-DEFAULT_AREA_LSA  0-NO_DEFAULT_AREA_LSA*/    
    /*End for BC3D02758*/
    ULONG ulNssaNoImport; /*Add by q62011 for DTS2010090302774:【OSPF】增加实现 路由器的 no-import-route 选项的功能*/
    
    /* Description: Indicates an NSSA Border router's ability to perform NSSA  */
    /*              translation of type-7 LSAs into type-5 LSAs.               */
    /* 1-ALWAYS  2-CANDIDATE                                                   */
    ULONG ulNssa_Translator_Role;

    /* Description: Indicates if and how an NSSA Border router is performing   */
    /*              NSSA translation of type-7 LSAs into type-5 LSAs.  When    */
    /*              this object set to enabled, the NSSA Border router's       */
    /*              ddrpPmAreaNssaTranslatorRole has been set to always.  When */
    /*              this object is set to elected, a candidate NSSA Border     */
    /*              router is Translating type-7 LSAs into type-5.  When this  */
    /*              object is set to disabled, a candidate NSSA Border router  */
    /*              is NOT translating type-7 LSAs into type-5.                */
    /*1-ENABLED   2-ELECTED  3-DISABLED                                        */
    ULONG ulNssa_Translator_State;

    /* Description: This parameter indicates whether the area can carry data   */
    /*              traffic that neither originates nor terminates in the area */
    /*              itself.  This parameter is calculated when the area's      */
    /*              shortest-path tree is built.                               */
    /* 1-TRUE 2-FASLE                                                          */
    ULONG ulTransitCapability;
    ULONG ulAdmin_Status;
    ULONG ulLsa_Rfsh_Intvl;
    ULONG ulAuthType;                           /*区域认证类型*/ 
    /*Begin for BC3D02824 显示OSPF 区域信息时，MD5 KEYID需要能显示出来 l00147446 10-02-27*/
    UCHAR ucAuthKeyId;                          /*区域认证Key ID*/  
    UCHAR ucPad[3];
    /*End for BC3D02824*/
    /*Modified by qinyun62011, DTS2010102700720维测增强 for VISP1.8C01, 2010/10/27 */
    /* Description: The number of LSAs with LS type-1 in this area's Link State Database. */
    ULONG ulRtrLsaCount;
    /* Description: The number of LSAs with LS type-2 in this area's Link State Database.*/
    ULONG ulNetLsaCount;
    /* Description: The number of LSAs with LS type-3 in this area's Link State Database.*/
    ULONG ulSummLsaCount;
    /* Description: The number of LSAs with LS type-4 in this area's Link State Database.*/
    ULONG ulSummAsLsaCount;
    /* Description: The number of LSAs with LS type-7 in this area's Link State Database.*/
    ULONG ulNssaLsaCount;
    /* Description: The number of LSAs with LS type-10 in this area's Link State Database.*/
    ULONG ulOpLsaCount;
    /* Description: The total number of link-state advertisements in this      */
    /*              area's link-state database, excluding AS External LSA's.   */
    ULONG ulLsaCount;
    /* Description: The total number of area border routers reachable within   */
    /*              this area.  This is initially zero, and is calculated in   */
    /*              each SPF Pass.                                             */
    ULONG ulBdrRtrCount;
    /* Description: The total number of Autonomous System border routers       */
    /*              reachable within this area.  This is initially zero, and   */
    /*              is calculated in each SPF Pass.                            */
    ULONG ulAsBdrRtrCount;
    /* Description: The number of times that the intra-area route table  has   */
    /*              been calculated using this area's link-state database.     */
    /*              This is typically done using Dijkstra's algorithm.         */
    ULONG ulSpfRuns;
}OSPF_SHOW_AREA_S;

/*此数据结构包括ospf area agg中用户关心的字段*/
typedef struct tagOSPF_SHOW_AREA_AGG
{
    UCHAR ucAreaId[4];             /*area id*/
    ULONG ulLsdb_Type;             /*Lsdb type*/
    UCHAR ucIpAddr[4];             /*address*/
    UCHAR ucIpMask[4];             /*ip mask*/
    ULONG ulEffect;                /*a flag,indicata advertise or not advertise*/
    ULONG ulProcessId;             /*process id*/
}OSPF_SHOW_AREA_AGG_S;

/* #endif */

/*Added by guojianjun178934, 【DOPRA IP V3R2C10-同步问题单-DTS2014040401470】【SGSN产品：OSPF】linux x86 系统函数times存在bug，需要VISP提供规避方案 , 2014/6/3   问题单号:DTS2014052908271 */
/*定时器切换信息*/
typedef struct tagOSPF_SHOW_TIMER_SWITCH
{
  /*初始化时的定时器类型*/
  ULONG ulInitTimerType;
  /*当前定时器类型,默认为Dopra时间处理函数*/
  ULONG ulCurTimerType;
  /*切换前的定时器类型*/
  ULONG ulOldTimerType;
  /*定时器补偿(以毫秒为单位)*/
  LONG lMSOffset;
  /*是否需要计算偏移*/
  BOOL_T bNeedCalcOffset;
  UCHAR pad[2];
}OSPF_SHOW_TIMER_SWITCH_S;
/* End of Added by guojianjun178934, 2014/6/3   问题单号:DTS2014052908271 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 
