#ifndef _RIP_API_H
#define _RIP_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

#define  RIP_CFG_ADD     0/*设置*/
#define  RIP_CFG_DEL     1/*取消*/

#define  RIP_AUTH_SIZE   15
#define  RIP_MAX_EQUAL_ROUTE_NUM   32

#define    RIP_DEAFAULT_ROUTE_MAX_COST   15 

/*l61496 2008-11-4 添加条件编译*/
#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH 47
#endif
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define RIP_MAX_VRF_NAME_LENGTH 31
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#ifndef BOOL_T
#define BOOL_T  short   /* boolean */  
#endif 

/*RIP 收发报文注册钩子函数类型*/
/*注意: 如果修改该类型，请同步修改qrsmrcv.c qrsmsnd.c中的定义
为了避免头文件包含导致编译不过，定义类似类型
l61496 */
typedef ULONG (*RIP_PACKET_HOOK_FUNC)(USHORT usProcId ,ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);

typedef enum tagRIP_ERROR_E  
{
    /*Begin BC3D02305 修正错误码拼写错误 l00147446 09-11-13*/
    RIP_SUCCESS,
    /*End BC3D02305 修正错误码拼写错误 l00147446 09-11-13*/

    RIP_ERR_GEN_ERROR = MID_COMP_RIP + 2, 
    RIP_ERR_WRONG_VALUE, /*MIB配置的值错误*/
    RIP_ERR_INCONSISTENT_VALUE,/*MIB配置的值不一致*/
    RIP_ERR_RESOURCE_UNAVAILABLE,/*MIB配置的资源无效*/
    RIP_ERR_NO_SUCH_OBJECT, /*对象不存在*/
    RIP_ERR_END_OF_TABLE,/*表项结束*/
    RIP_ERR_AGENT_ERROR, 
    RIP_ERR_INCOMPLETE,  
    RIP_ERR_PARTIAL_FAMILY_OK,
    RIP_ERR_PRODUCT_NOT_READY,
    RIP_ERR_CFG_TIMEOUT = MID_COMP_RIP + 15,/*配置超时15*/ 
    RIP_ERR_INIT_FAILED, /*RIP 没有初始化成功*/
    /*Begin BC3D01911 RIP_ERR_POINTER_IS_NULL拼写错误 l00147446 09-08-17*/
    RIP_ERR_POINTER_IS_NULL,   
    /*End BC3D01911 RIP_ERR_POINTER_IS_NULL拼写错误 l00147446 09-08-17*/
    RIP_ERR_CONFIG_FLAG_INVALID,/*错误的配置标志，不是TRUE也不是FALSE*/
    RIP_ERR_PRAR_INVALID,/*参数不合法*/
    RIP_ERR_ALREADY_EXIST,/*RIP实例已经存在*/
    
    /*Begin BC3D02305 修正错误码拼写错误 l00147446 09-11-13*/
    RIP_ERR_INSTANCE_NOT_EXIST, /*RIP实例不存在*/       
    /*End BC3D02305 修正错误码拼写错误 l00147446 09-11-13*/
    
    RIP_ERR_INSTANCE_CANNOT_IS_ZERO, /*RIP实例号不能为0*/
    RIP_ERR_IPS_IS_NULL, /*RIP 的IPS消息为空*/
    RIP_ERR_RET_IPS_IS_NULL, /*返回的IPS消息*/
    RIP_ERR_CONF_DATA_IS_NULL,/*25 RIP 配置数据项 为空*/
    RIP_ERR_CONN_CB_IS_NULL,/*连接控制块为空*/
    RIP_ERR_NETWORK_INVALID, /*错误的网段地址*/
    RIP_ERR_AUTH_MODE_INVALID,/*错误验证模式*/
    RIP_ERR_MALLOC_FAILED,/*分配内存失败*/
    RIP_ERR_NODE_IS_NOT_EXIST,/*结点不存在*/
    RIP_ERR_HANDLE_IS_NOT_EXIST,/*句柄不存在*/
    RIP_ERR_INSTANCE_IS_EXCEED_LIMIT,/*RIP实例超过范围*/
    RIP_ERR_CAN_NOT_FIND_ROUTE,/*找不到RIP的路由*/
    RIP_ERR_HAVE_NO_NEXT_ROUTE,/*找不到下一条路由*/
    RIP_ERR_NETWORK_IS_EXIST,    /*network已经存在*/
    RIP_ERR_NETWORK_IS_NOT_EXIST,/*network不存在*/
    RIP_ERR_HAVE_NO_INTERFACE,/*找不到接口*/
    RIP_ERR_HAVE_NO_IP_ADDR,/*获取不到地址*/
    RIP_ERR_JOIN_FAILED,/*与其他模块JOIN失败*/
    RIP_ERR_CANCEL_JOIN_FAILED,/*与其他模块取消JOIN失败*/
    RIP_ERR_OPEN_IF_ENTRY_FAILED,/*打开接口 ENTRY失败*/
    RIP_ERR_IF_HAVE_NOT_CFG_METRIC,/*该接口没有配置度量值*/
    RIP_ERR_HAVE_NO_RIP_EXIST, /*目前没有RIP实例被创建*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    RIP_ERR_GET_VRF_INDEX,
    RIP_ERR_INVALID_VRF_INDEX,
    RIP_ERR_INST_NOT_IN_VRF,
    RIP_ERR_VRF_NOT_INIT,
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    RIP_ERR_GET_IF_INFO,/*0x0E2E0030 <获取接口信息错误>*/
    RIP_ERR_IF_TYPE,/*0x0E2E0031 <获取接口类型错误>*/
    RIP_ERR_IF_HAVE_BEEN_BIND,/*0x0E2E0032 <接口已经绑定>*/
    RIP_ERR_IF_HAVE_NOT_BEEN_BIND,/*0x0E2E0033 <接口还没有绑定过>*/
    RIP_ERR_PROCESS_IF_NOT_MATCH,/*0x0E2E0034 <接口不是绑定在指定进程中>*/
    RIP_ERR_PROCESS_NOT_BIND_IF,/*0x0E2E0035 <指定进程尚没有跟接口绑定>*/
    RIP_ERR_FILTER_RULE_EXIST,/*0x0E2E0036 <规则已存在或不存在要删除的规则>*/
    RIP_ERR_FILTER_RULE_NOT_EXIST, /*0x0E2E0037 <规则不存在>*/   
    RIP_ERR_GET_HAVE_NOT_OPEN,    /*0x0E2E0038 <没有进行OPEN操作>*/
    RIP_ERR_GETFIRST_FAIL,/*0x0E2E0039 <没有进行GET FIRST操作>*/
    RIP_ERR_INVALID_UPDATE_TIMEOUT,/*0x0E2E003A <update定时器配置值错误>*/
    RIP_ERR_INVALID_AGE_TIMEOUT,/*0x0E2E003B <age定时器配置值错误>*/
    RIP_ERR_INVALID_GARBAGE_TIMEOUT, /*0x0E2E003C <garbage定时器配置值错误>*/
    RIP_ERR_INVALID_PREFERENCE_VALUE,/*0x0E2E003D <优先级配置值错误>*/
    RIP_ERR_GET_RTM_INST,/*0x0E2E003E <获取RTM实例错误>*/
    RIP_ERR_CFG_PREFERENCE,/*0x0E2E003F <MIB内部配置优先级错误>*/
    RIP_ERR_GET_PREFERENCE,/*0x0E2E0040 <MIB内部获取优先级错误>*/
    RIP_ERR_VRFNAME_TOOLONG,/*0x0E2E0041 <vrf名过长>*/
    RIP_ERR_ACLNUM,/*0x0E2E0042 <过滤规则号超出范围>*/
    RIP_ERR_METRIC_INOUT_VALUE_ERR,/*0x0E2E0043 <配置的接收或发送metric值错误>*/
    RIP_ERR_DEFRT_METRIC_VALUE_ERR,/*0x0E2E0044 <配置的默认路由metric值错误>*/
    RIP_ERR_INVALID_BALANCE_NUMBER, /*0x0E2E0045 <配置的最大平衡路由个数错误>*/
    RIP_ERR_INVALID_PROTO_TYPE = MID_COMP_RIP + 0x46, /* 0x46 无效协议类型 */
    RIP_ERR_INVALID_METRIC_TYPE,                      /* 0x47 无效Metric类型 */
    RIP_ERR_INVALID_METRIC_VAL,                       /* 0x48 无效Metric值 */
    RIP_ERR_INVALID_STATIC_RPAID,                     /* 0x49 无效静态协议引入ID */
    RIP_ERR_INVALID_DYNAMIC_RPAID,                    /* 0x4A 无效动态协议引入ID */
    
    RIP_ERR_MAX = MID_COMP_RIP + 255,
}RIP_ERROR_E;


typedef struct tagRIP_AUTH 
{ 
    ULONG ulAuthMode;   /*认证模式：不认证、text、MD5*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];  /*指定接口的接口名，最大长度47字节。*/
    BOOL_T bUndoConfig ;  /*TRUE表示设置，FALSE表示恢复默认值*/
    USHORT usProcId;   /*RIP实例ID号，取值范围1~65535。*/  
    UCHAR  ucAuthKey[RIP_AUTH_SIZE + 1]; /*验证KEY,最大长度16字节。*/
}RIP_AUTH_S;

typedef struct tagRIP_CFG_INFO 
{  
    UCHAR IsHostRoute;/*是否允许主机路由*/
    UCHAR ucUpdateTimeOutVal;/*刷新时间*/ 
    UCHAR ucAgeTimeOutVal; /*老化超时时间*/
    UCHAR ucGarbageTimeOutVal;/*垃圾搜集时间*/ 
    USHORT usMaxBalCount; /*最大平衡路由个数*/ 
    USHORT usProcId; /*RIP实例号*/
    /*Begin BC3D01346 l00147446 OSPF、RIP获取和显示接口缺少VRF信息 09-03-28*/
    ULONG ulVrfIndex;
    /*End BC3D01346 l00147446 OSPF、RIP获取和显示接口缺少VRF信息 09-03-28*/
} RIP_CFG_INFO_S;

typedef struct tagRIP_CONFIG_IF_DEF_ORG /*默认路由的默认cost值配置结构*/
{ 
    USHORT usProcId;  /*RIP实例ID号，取值范围1~65535。*/  
    USHORT usDfltOriginCost; /*默认路由的cost值*/
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1]; /*指定接口的接口名，最大长度47字节。*/
    BOOL_T bUndoConfig; /*TRUE表示设置，FALSE表示恢复默认值*/
    UCHAR aucPad[2]; 
} RIP_CONFIG_IF_DEF_ORG_S; 


typedef struct tagRIP_CONFIG_IF 
{ 
    UCHAR   szIfName[MAX_IF_NAME_LENGTH + 1]; /*接口名*/
    USHORT  usProcId;  /*RIP实例ID号，取值范围1~65535。*/     
    BOOL_T  bUndoConfig; 
} RIP_CONFIG_IF_S;

typedef struct tagRIP_CONFIG_JOIN 
{ 
    ULONG ulInterfaceId; 
    ULONG ulPartnerIndex; 
    BOOL_T bUndoConfig; 
    USHORT usProcId;  /*RIP实例ID号，取值范围1~65535。*/  
} RIP_CONFIG_JOIN_S;

typedef struct tagRIP_CONFIG_MAXLOAD_BAL /*最大平衡路由数目*/
{ 
    USHORT  usProcId; /*RIP实例ID号，取值范围1~65535。*/  
    USHORT  usMaxNumBalancePaths; /*平衡路由个数*/
    BOOL_T  bUndoConfig; /*TURE表示设置，FALSE表示恢复默认值4*/
    UCHAR aucPad[2]; 
} RIP_CONFIG_MAXLOAD_BAL_S;


typedef struct  tagRIP_CONFIG_METRIC /*附加路由权值的配置结构*/
{ 
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1];/*指定接口的接口名，最大长度47字节。*/
    USHORT  usMetricInVal;  /*输入附加路由权值*/
    USHORT  usMetricOutVal; /*输出附加路由权值*/
    BOOL_T  bUndoConfig;  /*TURE表示设置，FLASE表示取消，恢复到0*/
    UCHAR   ucPad[2];
} RIP_CONFIG_METRIC_S;

typedef struct tagRIP_CONFIG_NETWORK /*配置网段*/
{ 
    ULONG ulNetwork; /*网段的地址*/
    BOOL_T bUndoConfig; /*TRUE表示配置，FALSE表示删除*/
    USHORT usProcId;  /*RIP实例ID号，取值范围1~65535。*/  
} RIP_CONFIG_NETWORK_S;

typedef struct tagRIP_CONFIG 
{ 
    USHORT usProcId;  /*RIP实例ID号，取值范围1~65535。*/  
    BOOL_T bUndoConfig; 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RIP_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RIP_CONFIG_S;

typedef struct tagRIP_IFCONFIG
{
    UCHAR   szIfName[MAX_IF_NAME_LENGTH + 1];
    BOOL_T  bUndoConfig;
    UCHAR   aucPad[2];
}RIP_IFCONFIG_S;

typedef struct tagRIP_CONFIG_TIMERS 
{ 
    ULONG ulUpdateTimeOutVal;/*刷新时间*/ 
    ULONG ulAgeTimeOutVal; /*老化超时时间*/
    ULONG ulGarbageTimeOutVal;/*1-255*/ 
    BOOL_T bUndoConfig; 
    USHORT usProcId; /*RIP实例ID号，取值范围1~65535。*/  
} RIP_CONFIG_TIMERS_S;

typedef struct tagRIP_IF_CFG_INFO 
{  
    UCHAR  ucAuthType;
    UCHAR  ucSend;
    UCHAR  ucReceive;
    UCHAR  ucPad;
    ULONG  ulDefaultMetric;
} RIP_IF_CFG_INFO_S;


typedef struct tagRIP_IF_STAT_INFO 
{   
    ULONG  ulRcv_bad_packets;/**/
    ULONG  ulRcv_bad_routes;
    ULONG  ulSent_updates;
} RIP_IF_STAT_INFO_S;

/*问题单:BC3D00770  luogaowei 2008-11-26 修改变量命名*/
typedef struct tagRIP_PEER_INFO 
{   
    ULONG  ulAddressType;/*0x00-0x12*/
    ULONG  ulAddressLen;/*1-16*/
    UCHAR  ucAddress[16];
    ULONG  ulVersion;/*1-2*/
    ULONG  ulRcvBadPackets;
    ULONG  ulRcvBadRoutes;
    USHORT usProcId;  /*RIP实例ID号，取值范围1~65535。*/ 
    UCHAR  ucPad[2];
} RIP_PEER_INFO_S; /*RIP的邻居信息*/

typedef struct tagRIP_RESET 
{ 
    USHORT usProcId;  /*RIP实例ID号，取值范围1~65535。*/  
    UCHAR aucPad[2]; 
}RIP_RESET_S;

#define RIP_ROUTE_TYPE_INTERFACE      0x10  /*接口路由*/
#define RIP_ROUTE_TYPE_PROTOCOL       0x20  /*RIP学习到的路由*/
#define RIP_ROUTE_TYPE_RPI            0x30  /*RM引入的路由*/
#define RIP_ROUTE_TYPE_OTHER          0x40  /*其他*/

typedef struct tagRip_route
{ 
    ULONG ulDstAddr; /*目的地址*/
    ULONG ulMaskLen; /*掩码长度*/
    USHORT route_tag; /*路由标记*/
    USHORT usMetric; /*度量值*/
    ULONG  ulNextHop;/*下一跳地址*/
    USHORT  usRouteType; /*路由类型:接口类型、协议、RPI*/    
    USHORT  usAge; /*老化时间*/
} RIP_ROUTE_S; /*RIP的路由表项*/


typedef struct tagRip_route_group_s
{ 
    ULONG ulRouteNum;
    RIP_ROUTE_S stRipRoutes[RIP_MAX_EQUAL_ROUTE_NUM];
} RIP_ROUTE_GROUP_S; /*RIP的一组路由:所有目的地址和下一跳相同的路由*/

/***********************************************/

typedef struct tagRIP_NETWORKINFO_FILTER_S
{
   USHORT  usProcId;
   UCHAR   ucPad[2];
   /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
   UCHAR   szVrfName[RIP_MAX_VRF_NAME_LENGTH + 1];
   /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
} RIP_NETWORKINFO_FILTER_S; /*RIP 网段信息查询的过滤条件*/


typedef struct tagRIP_NETWORKINFO_S
{
    USHORT usProcId; /*RIP 实例号*/
    USHORT usCount; /*返回的网段个数*/
    ULONG* pulNetWork;
} RIP_NETWORKINFO_S; /*用于查询RIP 的网段信息*/

typedef struct tagRIP_PEERINFO_FILTER_S
{
    USHORT usProcId;
    UCHAR ucPad[2];
} RIP_PEERINFO_FILTER_S; /*用于查询邻居的过滤信息*/

typedef struct tagRIP_If_Cfg_Info_Ex /*一个接口只能配置一个RIP*/
{  
    ULONG  ulIfIndex; /*接口索引值*/    
    UCHAR  ucSplitHorizon;/*是否配置水平分割*/
    UCHAR  ucPoisonReverse;/*是否配置毒性逆转*/
    UCHAR  ucMetricIn;/*附加路由权值 输入*/
    UCHAR  ucMetricOut;/*附加路由权值 输出*/ 
} RIP_IF_CFG_EX_S;/*根据DCL 扩展的接口配置信息*/

typedef struct tagRIP_CFGINFO_FILTER_S
{
   USHORT  usProcId;
   UCHAR   ucPad[2];
}RIP_CFGINFO_FILTER_S; /*RIP 全局配置信息查询的过滤条件*/


extern RIP_ERROR_E RIP_CFG_CmdRipProcess (RIP_CONFIG_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdNetwork (const RIP_CONFIG_NETWORK_S *pstConfigInfo); 
extern RIP_ERROR_E RIP_CFG_CmdTimers(const RIP_CONFIG_TIMERS_S *pstConfigInfo);

extern RIP_ERROR_E   RIP_CFG_CmdHostRoute (const RIP_CONFIG_S *pstConfigInfo);
extern  RIP_ERROR_E RIP_CFG_CmdPoisonReverse (const RIP_IFCONFIG_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdSplitHorizon(const RIP_IFCONFIG_S *pstConfigInfo);


extern RIP_ERROR_E RIP_CFG_CmdResetStat(const RIP_RESET_S *pstConfigInfo);
extern RIP_ERROR_E  RIP_CFG_DefaultRouteOrig(const RIP_CONFIG_IF_DEF_ORG_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdMaxLoadBal(const RIP_CONFIG_MAXLOAD_BAL_S *pstConfigInfo);

extern RIP_ERROR_E RIP_CFG_CmdInput (const RIP_CONFIG_IF_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdOutput (const RIP_CONFIG_IF_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdSilentInterface (const RIP_CONFIG_IF_S *pstConfigInfo);

extern RIP_ERROR_E RIP_CFG_CmdMetricIn (const RIP_CONFIG_METRIC_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdMetricOut (const RIP_CONFIG_METRIC_S *pstConfigInfo);
extern RIP_ERROR_E RIP_CFG_CmdAuth (const RIP_AUTH_S *pstConfigInfo);

extern RIP_ERROR_E RIP_GetCfgInfo (USHORT usProcId, RIP_CFG_INFO_S *pstConfigInfo);
extern RIP_ERROR_E RIP_GetIfStatInfo (USHORT usProcId, UCHAR  szIfName[], RIP_IF_STAT_INFO_S *pstStatInfo);
extern RIP_ERROR_E RIP_GetIfCfgInfo (USHORT usProcId, UCHAR szIfName[48], RIP_IF_CFG_INFO_S *pstConfigInfo);

extern RIP_ERROR_E RIP_OpenPeerInfoEntry(ULONG *pulSessionId, RIP_PEERINFO_FILTER_S* pstDispRipFilter);
extern RIP_ERROR_E RIP_ClosePeerInfoEntry(ULONG ulSessionId);
extern RIP_ERROR_E RIP_GetFirstPeerInfo (ULONG ulSessionId, RIP_PEER_INFO_S *pstConfigInfo);
extern RIP_ERROR_E RIP_GetNextPeerInfo(ULONG ulSessionId, RIP_PEER_INFO_S *pstConfigInfo);


extern RIP_ERROR_E RIP_OpenRouteEntry(ULONG *pulHandle);
extern RIP_ERROR_E RIP_CloseRouteEntry(ULONG ulHandle);
extern RIP_ERROR_E RIP_GetFirstRouteInfo (USHORT usProcId, ULONG ulHandle, RIP_ROUTE_GROUP_S *pstRipGrpRoutes);
extern RIP_ERROR_E RIP_GetNextRouteInfo (USHORT usProcId, ULONG ulHandle, RIP_ROUTE_GROUP_S *pstRipGrpRoutes);

extern  RIP_ERROR_E RIP_OpenNetworkInfoEntry (ULONG *pulSessionId, RIP_NETWORKINFO_FILTER_S* pstDispProcFilter);
extern  RIP_ERROR_E RIP_CloseNetworkInfoEntry(ULONG ulSessionId);
extern  RIP_ERROR_E RIP_GetFirstNetworkInfo(ULONG ulSessionId, RIP_NETWORKINFO_S* pstConfigInfo);
extern  RIP_ERROR_E RIP_GetNextNetworkInfo(ULONG ulSessionId, RIP_NETWORKINFO_S* pstConfigInfo);

extern  RIP_ERROR_E RIP_GetIfCfgExInfo (CHAR *pszIfName, RIP_IF_CFG_EX_S *pstIfCfgExInfo);

extern RIP_ERROR_E RIP_Direct_OpenPeerInfoEntry(ULONG *pulSessionId ,USHORT usProcId);
extern RIP_ERROR_E RIP_Direct_ClosePeerInfoEntry(ULONG ulSessionId);
extern RIP_ERROR_E RIP_Direct_GetFirstPeerInfo(ULONG ulSessionId, RIP_PEER_INFO_S *pstPeerInfo);
extern RIP_ERROR_E RIP_Direct_GetNextPeerInfo(ULONG ulSessionId, RIP_PEER_INFO_S *pstPeerInfo);

extern VOID RIP_ShowGlobalInfo(USHORT usProcId);
extern VOID RIP_ShowPeerInfo(USHORT usProcId);
extern VOID RIP_ShowRipIfCfgInfo(USHORT usProcId);
extern VOID RIP_ShowRipRouteInfo(USHORT usProcId);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*extern VOID RIP_ShowNetWorkInfo(USHORT usProcId);*/
extern VOID RIP_ShowNetWorkInfo(USHORT usProcId,CHAR *pszVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
extern VOID RIP_ShowExIfCfgInfo (VOID);
extern VOID RIP_Direct_ShowPeerInfo(USHORT usProcId);

extern ULONG RIP_Intermediate_UnHook_Register(ULONG ulDirection);
extern ULONG RIP_Intermediate_Hook_Register(ULONG ulDirection, 
        RIP_PACKET_HOOK_FUNC pfRipFwHookFunc);


extern RIP_ERROR_E RIP_OpenCfgInfoEntry (ULONG *pulSessionId, RIP_CFGINFO_FILTER_S* pstDispProcFilter);
extern RIP_ERROR_E RIP_CloseCfgInfoEntry(ULONG ulSessionId);
extern RIP_ERROR_E RIP_GetFirstRipCfgInfo(ULONG ulSessionId, RIP_CFG_INFO_S *pstConfigInfo);
extern RIP_ERROR_E RIP_GetNextRipCfgInfo(ULONG ulSessionId, RIP_CFG_INFO_S *pstConfigInfo);

/************************路由引入新需求****************************************/
typedef struct tagRIP_CFGREDISTRIBUTE
{
    BOOL_T bNoFlag;
    USHORT usProcessId;
    RM_RPM_PLCYREDIS_S stPolicyRedist;
}RIP_CFGREDISTRIBUTE_S; /*RIP 路由引入策略配置结构*/

typedef struct tagRIP_CFGDISTRIBUTE
{
    BOOL_T bNoFlag;
    USHORT usProcessId;
    RM_RPM_PLCYDIST_S stPolicyDist;
}RIP_CFGDISTRIBUTE_S;/*RIP 路由过滤配置结构*/

extern RIP_ERROR_E RIP_CFG_CmdRedistributeProc(RIP_CFGREDISTRIBUTE_S* pstRedistIn);
extern RIP_ERROR_E RIP_CFG_CmdDistributeOutProc(RIP_CFGDISTRIBUTE_S* pstDistExpIn);
extern RIP_ERROR_E RIP_CFG_CmdDistributeInProc (RIP_CFGDISTRIBUTE_S*  pstDistImpIn);


typedef struct tagRIP_IMPORTINFO_FILTER_S
{
    USHORT  usProcId;
    UCHAR   ucPad[2];
} RIP_IMPORTINFO_FILTER_S;/*RIP路由策略查询条件*/

typedef struct tagRIP_IMPORTINFO_S
{
    USHORT usProcessId;
    UCHAR  ucPad[2];
    RM_RPM_PLCYREDIS_S  stReDis;
}RIP_IMPORTINFO_S; /*RIP 路由策略查询信息*/

extern RIP_ERROR_E RIP_OpenImportInfoEntry(ULONG *pulSessionId, RIP_IMPORTINFO_FILTER_S* pstDispProcFilter);
extern RIP_ERROR_E RIP_GetFirstImportInfo(ULONG ulSessionId, RIP_IMPORTINFO_S* pstConfigInfo);
extern RIP_ERROR_E RIP_GetNextImportInfo (ULONG ulSessionId, RIP_IMPORTINFO_S* pstConfigInfo);
extern RIP_ERROR_E RIP_CloseImportInfoEntry(ULONG ulSessionId);
extern VOID RIP_ShowImportPolicyInfo(USHORT usProcId);


typedef struct tagRIP_FILTERPOLICYINFO_FILTER_S
{
    USHORT  usProcId;
    UCHAR  ucPad[2];
} RIP_FILTERPOLICYINFO_FILTER_S; /*RIP过滤信息查询条件*/

typedef struct tagRIP_FILTERPOLICYINFO_S
{
    USHORT usProcessId;
    UCHAR  ucPad[2];
    #define RIP_TO_RM 1
    #define RM_TO_RIP 2
    ULONG  ulPlcyDirectFlag;
    RM_RPM_PLCYDIST_S stPlcyDist;
}RIP_FILTERPOLICYINFO_S;/*RIP 过滤信息查询*/


extern RIP_ERROR_E RIP_OpenFilterPolicyInfoEntry (ULONG *pulSessionId, 
            RIP_FILTERPOLICYINFO_FILTER_S* pstDispProcFilter);
extern RIP_ERROR_E RIP_GetFirstFilterPolicyInfo(ULONG ulSessionId, RIP_FILTERPOLICYINFO_S* pstConfigInfo);
extern RIP_ERROR_E RIP_GetNextFilterPolicyInfo(ULONG ulSessionId, RIP_FILTERPOLICYINFO_S* pstConfigInfo);
extern RIP_ERROR_E RIP_CloseFilterPolicyInfoEntry(ULONG ulSessionId);
extern  VOID RIP_ShowFilterPolicyInfo(USHORT usProcId);

#ifdef  __cplusplus
}
#endif

#endif 

