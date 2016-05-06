#ifndef _RIP_CORE_H
#define _RIP_CORE_H

#ifdef  __cplusplus
    extern "C"{
#endif
#include "rpm_type.h"


#ifndef TRUE
#define TRUE 1
#endif

#ifndef TRUE
#define FALSE 0
#endif

#define  RIP_INIT_SUCCESS     0x01 /*RIP初始化成功*/
#define  RIP_INIT_FAILED      0x00 /*RIP初始化失败*/

#define  RIP_MAX_INSTANCE_NUM  65535 /*RIP从1开始编号*/
#define  RIP_MAX_INSTANCE_LIMIT  16 /*RIP最多16个*/

#define  RIP_TIMER_MAX_VALUE    255  /*定时器最大255秒*/
#define  RIP_TIMER_MIN_VALUE     1     /*定时器最小1秒*/

#define  QRPM_RPI_MIN_HOPS     1   /*平衡路由个数最小1 ，最大QRPM_RPI_MAX_HOPS*/

#define  RIP_COST_MAX_VALUE   16  /*cost最大16*/
#define  RIP_COST_MIN_VALUE   1   /*cost 最小1*/

#define SID_RIP_METRIC            1
#define SID_RIP_PEER_ENTRY        2
#define SID_RIP_ROUTE_ENTRY       3
#define SID_RIP_NETWORK           4
#define SID_RIP_AUTH              5
#define SID_RIP_WORKMODE          6
#define SID_RIP_DFT_ROUTE_COST    7
#define SID_RIP_CFG_IF            8
#define SID_RIP_CFG               9
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define SID_RIP_INIT               9
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */


#define RIP_SILENT_MODE 0
#define RIP_INPUT  1
#define RIP_OUTPUT 2


#define RIP_SPLIT_CFG  1 /*设置水平分割*/
#define RIP_POISON_CFG 2 /*设置毒性逆转*/


#define RIP_ADD 1
#define RIP_DEL 0

#define RIP_DEL_BY_INTF_INDEX  0 
#define RIP_DEL_BY_RIP_INDEX   1

#define  IPV4_ADDR_LEN   4


#define RIP_NETWORK_PT_BEGIN           (VOID)TCPIP_SmP(g_ulSemForRipNetWork)
#define RIP_NETWORK_PT_END             (VOID)TCPIP_SmV(g_ulSemForRipNetWork)

#define RIP_IF_CFG_PT_BEGIN       (VOID)TCPIP_SmP(g_ulSemForIfCfg)
#define RIP_IF_CFG_PT_END         (VOID)TCPIP_SmV(g_ulSemForIfCfg)

/*问题单 BC3D01592 begin */
#define RIP_MIB_CFG_PT_BEGIN       (VOID)TCPIP_SmP(g_ulSemForRipMibCfg)
#define RIP_MIB_CFG_PT_END          (VOID)TCPIP_SmV(g_ulSemForRipMibCfg)
/*问题单 BC3D01592 end */


enum  RIP_PM_ENT_TYPE
{
    RIP_PM_ENT_PM_INDEX = 1,
    RIP_PM_ENT_PM_ADMIN_STATUS = 2,
    RIP_PM_ENT_PM_ROW_STATUS  = 4,
    RIP_PM_ENT_PM_MAX_ECMP_HOPS = 5,
    RIP_PM_ENT_TIMERS,
    RIP_PM_ENT_CLEAR_STATS = 16, /*统计清除*/
    RIP_PM_ENT_USER_DATA = 17,
    RIP_PM_ENT_HOST_ROUTE = 18,/*是否允许接收主机路由*/
    RIP_PM_ENT_SPLIT_HORIZON = 19,/*是否允许水平分割*/
    RIP_PM_ENT_POISON_REVERSE = 20,/*是否允许毒性逆转*/   
};


typedef struct tagRip_Cfg_If_Store
{
    RIP_IF_CFG_EX_S stIfCfgEx; /*接口的扩展配置*/
    UCHAR  ucActive; /*是否激活配置该节点*/
    UCHAR  ucPad[3];
    NBB_LLQE  stListNode;/*链表*/
}RIP_IF_CFG_STORE_EX_S; /*只针对接口配置而不针对某个RIP的存储结构*/


typedef struct tagRIP_Proc
{
    NBB_ULONG ulProcessId;/*RIP实例进程ID*/
    NBB_USHORT usProcId;/*RIP的实例号*/
    NBB_CHAR  IsUsed;
    NBB_CHAR  ucPad;
}RIP_PROC_S; /*RIP PROC 结构:关联实例号和进程ID*/



typedef struct tagRip_route_key_index /*用于NEXT 路由CB的索引值*/
{ 
    ULONG ulDstAddr;
    ULONG ulMaskLen;
} RIP_ROUTE_KEY_INDEX_S;

typedef struct tag_mib_if_conf_key_index/*用于NEXT 接口配置表项的索引值*/
{  
    NBB_ULONG ent_index;  
    NBB_ULONG filter_length; 
    NBB_BYTE address[IPV4_ADDR_LEN];  
    NBB_LONG if_index;  
}MIB_IF_CONF_KEY_INDEX_S; 


typedef struct tag_mib_if_stat_key_index
{ 
    NBB_ULONG ent_index; 
    NBB_BYTE address[IPV4_ADDR_LEN];
    NBB_LONG if_index;   
}MIB_IF_STAT_KEY_INDEX_S; 

typedef struct tag_rip_peer_key_index /*用于获取NEXT 对端信息的索引值*/
{ 
    NBB_ULONG ent_index; 
    NBB_LONG address_type;                  
    NBB_ULONG address_len;                 
    NBB_BYTE address[AMB_RIP_MAX_ADDR_LEN]; 
    NBB_BYTE domain[AMB_RIP_ROUTE_TAG_LEN];
    NBB_CHAR ucPad[2];
}MIB_RIP_PEER_KEY_INDEX_S;


/*
 一个RIP 可以有多个网段；
 一个RIP 可以有一个网段，但是多个接口
 4元组决定一个表项
*/
typedef struct tagRip_NetWorkStore
{
    NBB_ULONG ulNetWork;/*网段地址*/
    NBB_ULONG ulIfIndex; /*接口索引值*/
    NBB_USHORT usProcId;/*RIP实例号*/
    NBB_USHORT Used; /*该表项是否生效*/
    NBB_ULONG ulIPAddr;/*本表项保存的地址*/
    NBB_LLQE  NetWorkListNode;/*链表*/
}RIP_NETWORK_STORE_S; /*存放RIP 的网段链表*/


typedef struct tagRip_Cfg_Auth_info
{  
    NBB_ULONG ulIfIndex; /*接口索引值*/
    NBB_USHORT usProcId; /*RIP实例号*/ 
    NBB_BYTE authType; /*验证类型*/
    NBB_BYTE Pad; 
    NBB_BYTE authKey[16]; /*auth key*/
}RIP_CFG_AUTH_INFO_S; /*存放RIP 的接口配置AUTH链表*/

typedef struct tagRip_Cfg_Auth_list
{  
    RIP_CFG_AUTH_INFO_S stAuthInfo;/*本地保存的配置的信息*/
    NBB_LLQE  AuthListNode;/*链表*/
}RIP_CFG_AUTH_LIST_S; /*存放RIP 的接口配置链表*/


typedef struct tagRip_Cfg_SendRecv_info
{  
    NBB_ULONG ulIfIndex; /*接口索引值*/
    NBB_USHORT usProcId; /*RIP实例号*/ 
    NBB_BYTE send; 
    NBB_BYTE recv; 
}RIP_CFG_SENDRECV_INFO_S; /*存放RIP 的接口配置发送接收链表*/

typedef struct tagRip_Cfg_SendRecv_list
{  
    RIP_CFG_SENDRECV_INFO_S stSndRcvInfo;/*本地保存的配置的信息*/
    NBB_LLQE  SendRecvListNode;/*链表*/
}RIP_CFG_SENDRECV_LIST_S; 

typedef struct tagRip_Cfg_Dft_Rt_Cost_info
{  
    NBB_ULONG ulIfIndex; /*接口索引值*/
    NBB_USHORT usProcId; /*RIP实例号*/ 
    NBB_USHORT defaultRtCost; 
}RIP_CFG_DFT_RT_COST_INFO_S; /*存放RIP 的默认度量值配置链表*/

typedef struct tagRip_Cfg_Dft_Rt_Cost_list
{  
    RIP_CFG_DFT_RT_COST_INFO_S stDftRtCostInfo;/*本地保存的配置的信息*/
    NBB_LLQE  DftRtCostNode;/*链表*/
}RIP_CFG_DFT_RT_COST_LIST_S; 

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagRIP_NETWORKINFO_FILTER_INFO_S
{
   USHORT  usProcId;
   UCHAR   ucPad[2];
   ULONG   ulVrfIndex;
} RIP_NETWORKINFO_FILTER_INFO_S; /*RIP 网段信息查询的过滤条件*/
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef struct tagRIP_NETWORKINFO_KEY_S
{
   /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
   /*RIP_NETWORKINFO_FILTER_S stNetworkFilter;*/
   RIP_NETWORKINFO_FILTER_INFO_S stNetworkFilter;
   /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
   ULONG ulData;  /*指向存放网段信息的内存空间*/
   USHORT usCrtProcId; /*当前查找的RIP实例号*/
   UCHAR ucPad[2];
   /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
   ULONG ulVrfIndex;
   /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
} RIP_NETWORKINFO_KEY_S; /*RIP 网段信息查询的过滤条件*/

/*变量声明*/
extern ULONG g_ulRIPMaxNum;
extern ULONG g_ulCurRIPCount;
extern ULONG g_ulRIPInitState;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*extern NBB_LLQE_ROOT  g_RIPNetWorkList;*/
extern NBB_LLQE_ROOT  *g_RIPNetWorkList;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
extern NBB_LLQE_ROOT  g_CfgIfStoreList;/*存放接口配置的水平分割和毒性逆转的链表*/

extern ULONG g_ulSemForIfCfg;
extern ULONG g_ulSemForRipNetWork;
extern RIP_PROC_S g_ulRIPProc[];
extern RIP_PACKET_HOOK_FUNC g_pstRipInputPktHook; 
extern RIP_PACKET_HOOK_FUNC g_pstRipOuputPktHook;

#define   RIP_VERSION_V2       2        /*RIP版本号2*/
#define   RIP_ROUTE_ENTRY_SIZE      20  /*每组路由条目 占20个字节*/
#define   RIP_ROUTE_ENTRY_MAX_NUM   25   /*最大25个条目*/

typedef struct tagRipPacketHead{
    UCHAR   ucCmd;
    UCHAR   ucVersion;
    USHORT usRtDomain;
}RIP_PACKET_HEAD_S; /*RIP报文首部 4字节*/

typedef struct tagRipEntryInfo{
    USHORT usFamily;
    USHORT usRtTag;
    ULONG   ulDestIp;
    ULONG   ulMask;
    ULONG   ulNextHop;
    ULONG   ulMetric;    
}RIP_ENTRY_INFO_S; /*RIP报文每个条目结构 20字节*/


typedef struct tagRip_host_proc_ips
{
    NBB_IPS ips_hdr;
    USHORT usType;
    USHORT usProcId;
    ULONG ulIfIndex;
    ULONG ulIPAddr;
}RIP_HOST_PROC_IPS;


/*参数声明*/
extern ULONG RIP_Global_Init(VOID);
extern ULONG RIP_Global_Destroy(VOID);
extern RIP_ERROR_E RIP_SetInstanceLimit(USHORT usMaxSize);
extern RIP_ERROR_E RIP_Ent_United_EnabeIntf(ULONG ulType, USHORT usProcId, BOOL_T bFlag);
extern RIP_ERROR_E  RIP_Set_DefaultRouteCostForIP(USHORT usProcId, BOOL_T bUndoConfig, ULONG ulIPAddr, ULONG ulDefaultMetric);
extern RIP_ERROR_E RIP_SetWorkModeForIP(USHORT usProcId, ULONG ulIPAddress, ULONG ulType, ULONG ulFlag);
extern RIP_ERROR_E RIP_MetricProcess (BOOL_T bUndoConfig, ULONG ulIfIndex, USHORT usInOrOut, USHORT usMetricValue);
extern BOOL_T  IP_ISNatureNet(ULONG ulIPAddr);
extern RIP_ERROR_E RIP_CFG_CmdAuthForSingleIP (USHORT usProcId, BOOL_T bUndoConfig, ULONG ulIPAddr, ULONG ulAuthMode, 
            UCHAR  ucAuthKey[]);
extern VOID RIP_ShowGlobalInfoByOne(USHORT usProcId);
extern VOID RIP_ShowPeerInfoByOne(USHORT usProcId);
extern VOID RIP_ShowRipCfgIfInfoByOne(USHORT usProcId);
extern VOID RIP_ShowRipRouteInfoByeOne(USHORT usProcId);

/*Modified by liangjicheng 00103192, G3, 2011/1/31   问题单号:V2R3C03-ROTUE-MERGE */
extern RIP_ERROR_E  RIP_CFG_JoinToOther(ULONG ulProcId, BOOL_T bConfig, LONG  InterfaceId , LONG PartnerIndex);
/*End of Modified by liangjicheng 00103192, 2011/1/31   问题单号:V2R3C03-ROTUE-MERGE */

extern BOOL_T  IsRipExist(USHORT usProcId);
extern USHORT  RIP_GetFirstEffectIndex(VOID);
extern USHORT  RIP_GetNextEffectIndex(USHORT usProcId);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*extern BOOL_T  IsNetWorkExist(ULONG ulNetWork);*/
extern BOOL_T  IsNetWorkExist(ULONG ulNetWork,ULONG ulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
extern BOOL_T  IsEmptyNetworkNodeExist(USHORT usProcId, ULONG ulNetWork);
extern BOOL_T IsNetworkEffectNodeExist(USHORT usProcId,ULONG ulIfIndex, ULONG ulNetWork, ULONG ulIPAddr);

extern BOOL_T IsRipHasNetWork(USHORT usProcId);

extern RIP_ERROR_E  AddRIPNetWork(USHORT usProcId, ULONG ulNetWork, ULONG ulIfIndex,ULONG ulIPAddr);
extern RIP_ERROR_E  DelRIPNetWork(USHORT usProcId,ULONG ulNetWork);
extern BOOL_T  IsInterfaceEnableRIP(ULONG ulIfIndex, USHORT usProcId);

extern ULONG  RIP_CFG_Add_IF_ReCfg(USHORT usRipIndex, ULONG ulIfIndex,ULONG ulIPAddr);
extern ULONG  RIP_CFG_Del_IF_ReCfg(USHORT usRipIndex, ULONG ulIPAddr, ULONG ulIfIndex);

extern RIP_ERROR_E RIP_GetIPFromCfgIf(USHORT usProcId, ULONG ulIfIndex, ULONG *pulNum, ULONG ulIPAddrs[]);
extern ULONG RIP_ReCfgFromI3Msg(USHORT usType, USHORT ulRIPIndex ,ULONG ulIfIndex, ULONG ulIPAddr);

extern ULONG RIP_AddCfgAuthInfo(RIP_CFG_AUTH_INFO_S *pstAuthInfo); 
extern ULONG RIP_DelCfgAuthInfo(RIP_CFG_AUTH_INFO_S *pstAuthInfo);
extern ULONG RIP_SetCfgAuthInfo(BOOL_T bAddOrDel, RIP_CFG_AUTH_INFO_S *pstAuthInfo);
extern ULONG RIP_GetCfgAuthInfo(RIP_CFG_AUTH_INFO_S *pstCfgAuthInfo); 

extern ULONG RIP_SetCfgSndRcvInfo(ULONG ulType, RIP_CFG_SENDRECV_INFO_S  *pstSndRcvInfo);
extern ULONG RIP_GetCfgSndRcvInfo(RIP_CFG_SENDRECV_INFO_S *pstCfgSndRcvInfo);

extern ULONG RIP_AddCfgDftRtCostInfo(RIP_CFG_DFT_RT_COST_INFO_S  *pstDftRtCostInfo);
extern ULONG RIP_DelCfgDftRtCostInfo(RIP_CFG_DFT_RT_COST_INFO_S  *pstDftRtCostInfo);
extern ULONG RIP_SetCfgDftRtCostInfo(ULONG ulType, RIP_CFG_DFT_RT_COST_INFO_S  *pstDftRtCostInfo);
extern ULONG RIP_GetCfgDftRtCostInfo(RIP_CFG_DFT_RT_COST_INFO_S *pstCfgDftRtCostInfo);

extern ULONG RIP_ReCfg_Auth(USHORT usRipIndex, ULONG ulIfIndex, ULONG ulIPAddr);
extern ULONG RIP_ReCfg_WorkMode(USHORT usRipIndex, ULONG ulIfIndex, ULONG ulIPAddr);
extern ULONG RIP_ReCfg_DftRouteCost(USHORT usRipIndex, ULONG ulIfIndex, ULONG ulIPAddr);
extern ULONG RIP_DelCfgAuthInfoByType(ULONG ulType, ULONG ulPara);
extern ULONG RIP_DelCfgSndRcvInfoByType(ULONG ulType, ULONG ulPara);
extern ULONG RIP_DelCfgDftRtCostInfoByType(ULONG ulType, ULONG ulPara);
extern ULONG RIP_DelLocalInfoByIntf(ULONG ulIfIndex);
extern ULONG RIP_DelLocalInfoByRipIndex(USHORT usRipIndex);
/*Modified by liangjicheng 00103192, 错误内部函数删除, 2011/8/6   问题单号:   OSPF_20110616_01 */
/*End of Modified by liangjicheng 00103192, 2011/8/6   问题单号:DTS2011070706274   OSPF_20110616_01 */
extern VOID RIP_Direct_ShowPeerInfoByOne(USHORT usProcId);
extern VOID RIP_ShowRipIfCfgInfoByOne(USHORT usProcId);
extern RIP_ERROR_E RIP_SplitPoisonProcess (BOOL_T bUndoConfig, ULONG ulIfIndex, USHORT usType);

extern ULONG RIP_AddIfCfgInfoNode(ULONG ulIfIndex);
extern ULONG RIP_DelIfCfgInfoNode(ULONG ulIfIndex);

extern ULONG RIP_GetIfCfgExInfoByInf (ULONG ulIfIndex, RIP_IF_CFG_EX_S *pstIfCfgExInfo);
extern VOID RIP_ImportInfoOutput(RIP_IMPORTINFO_S  *pstConfigInfo);
extern VOID RIP_FilterInfoOutput(RIP_FILTERPOLICYINFO_S  *pstConfigInfo);

/*问题单 BC3D01592 begin */
extern ULONG  RIP_GetIPAddrByNetwork(USHORT usProcId,  ULONG ulNetWork, ULONG *pulCount, ULONG *pulIndex, ULONG **pNetWorkInfo);
extern ULONG RIP_CFG_DelNetwork (USHORT  usProcId , ULONG ulNetWork, ULONG ulVrfIndex);
extern ULONG RIP_CFG_AddNetwork(USHORT  usProcId , ULONG ulNetWork, ULONG ulVrfIndex);
extern ULONG  g_ulSemForRipMibCfg ;
/*问题单 BC3D01592 end*/

extern ULONG RIP_send_ips_to_self_hostroute_proc(USHORT usType, USHORT usProcId, ULONG ulIfIndex, ULONG ulIPAddr);
extern BOOL_T RIP_check_hostroute_network(USHORT usProcId, ULONG ulIpAddr);

/*Added by guojianjun178934, V2R3C06SPC100代码检视路由部分意见修改_RIP网段删除，可能存在多个接口，只获取第一个接口索引有问题, 2013/4/20   问题单号:DTS2012090601039  */
typedef struct tagRIP_IF_INFO_GET_BY_NETWORK_S
{
    ULONG ulIfIndex;
    ULONG ulIfIPAddr;

}RIP_IF_INFO_GET_BY_NETWORK_S;
/* End of Added by guojianjun178934, 2013/4/20   问题单号:DTS2012090601039  */

#ifdef  __cplusplus
}
#endif

#endif 

