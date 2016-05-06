#ifndef _RM_TYPE_H
#define _RM_TYPE_H

#ifdef  __cplusplus
    extern "C"{
#endif


#include "tcpip/acl4/include/acl_pub.h"
#include "tcpip/acl4/include/acl_def.h"
#include "tcpip/acl4/shell/include/acl_sh.h"
#include "rtpro/glue/i3agent/i3agent.h"

/*RTM模块使用的SID统一在此定义 */
#define SID_RTM_DEFROUTE_S             MID_COMP_RTM | 0x00000001
#define SID_RTM_SHOW_MIB               MID_COMP_RTM | 0x00000002
#define SID_RTM_REDIST_S               MID_COMP_RTM | 0x00000003
#define SID_RTM_PLYID                  MID_COMP_RTM | 0x00000004
#define SID_RTM_SHOW_NET               MID_COMP_RTM | 0x00000005
#define SID_RTM_BALROUTE_S             MID_COMP_RTM | 0x00000006

/*2008-10-27 61496 添加快查接口的 SID*/
#define SID_RTM_ACRT_ENTRY        10
#define SID_RTM_RIB_ENTRY         11
#define SID_RTM_STATIC_RT_ENTRY   12
#define SID_RTM_LSDB_ENTRY        13

/*Added by jijianhua00169178, 将RM_REDIST_CREATE定义一起放在RM_REDIST_S中, 2011/3/3   问题单号:DTS2011030203676 */
/* #define RM_REDIST_CREATE             0 */
/* End of Added by jijianhua00169178, 2011/3/3   问题单号:DTS2011030203676 */

/* Begin BC3D03313 liangjicheng 2010-06-22 */
#define RM_REDIST_OPTYPE_CREATE_IN              0
#define RM_REDIST_OPTYPE_CREATE_IN_FILTER       1
#define RM_REDIST_OPTYPE_CREATE_OUT             2
#define RM_REDIST_OPTYPE_ADD_IN                 3
#define RM_REDIST_OPTYPE_ADD_IN_FILTER          4
#define RM_REDIST_OPTYPE_DEL_IN                 5
#define RM_REDIST_OPTYPE_DEL_IN_FILTER          6
#define RM_REDIST_OPTYPE_DESTROY_IN             7
#define RM_REDIST_OPTYPE_DESTROY_IN_FILTER      8
#define RM_REDIST_OPTYPE_DESTROY_OUT            9
#define RM_REDIST_OPTYPE_UPDATE_ACL             10
#define RM_REDIST_OPTYPE_DESTROY_INSTANCE       11
#define RM_REDIST_OPTYPE_UPDATE_OUT             12

#define RM_REDIST_USER_FLAG_IN          0x01
#define RM_REDIST_USER_FLAG_IN_FILTER   0x02
#define RM_REDIST_USER_FLAG_OUT         0x04

#define RM_REDIST_USER_FLAG_SET         1
#define RM_REDIST_USER_FLAG_UNSET       0
/* End BC3D03313 liangjicheng 2010-06-22 */

/*rip ospf路由优先级*/
#define RM_RIP_ROUTE_PRI             1
#define RM_OSPF_INTROUTE_PRI         2
#define RM_OSPF_EXTROUTE_PRI         3 

#define RM_REDIST_MAX_PRIORITY  0x7fffffff
#define RM_REDIST_RIP_MAX_COST  15
#define RM_REDIST_OSPF_MAX_COST 0xffffff
#define RM_REDIST_MAX_POLICY_NUM  128

/*redist protocol type*/
#define RM_REDIST_PROT_CONNECTED      0x00020000 
#define RM_REDIST_PROT_STATIC         0x00030000 
#define RM_REDIST_PROT_RIP            0x00080000 
#define RM_REDIST_PROT_OSPF           0x000D0000 

/*OSPF Path type*/
#define RM_REDIST_PATH_OSPF_INTRA_AREA 0x000D0000 
#define RM_REDIST_PATH_OSPF_INTER_AREA 0x000D0001 
#define RM_REDIST_PATH_OSPF_TYPE1_EXT  0x000D0002
#define RM_REDIST_PATH_OSPF_TYPE2_EXT  0x000D0003

/*Metric(or cost) conversion type */
#define RM_REDIST_FLAG_METRIC_CONV_SAME        1
#define RM_REDIST_FLAG_METRIC_CONV_CONSTANT    2

/*Redist direct flag */
#define RM_REDIST_DIRECT_FLAG_IMPORT     1
#define RM_REDIST_DIRECT_FLAG_OUTPORT    0

/*Add begin by t00110672 for BC3D01783,   质量活动，消除魔鬼数字*/
#define RM_REDIST_FILTER_YES   1
#define RM_REDIST_FILTER_NO   2

#define RM_ROUTE_MIN_PRI  1
#define RM_ROUTE_MAX_PRI 255
/*End*/
/*RTM 类型区分: RTM4  或者RTM6*/
#define  RM_TYPE_IPV4  0  /*rtm4*/
#define  RM_TYPE_IPV6  1  /*rtm6*/

/*luogaowei 用于导出时候的RM标记
和如下路由类型对应
RM_PROTO_CONNECTED 
RM_PROTO_STATIC   
RM_PROTO_RIP    
RM_PROTO_OSPF    */

#define RM_PROTO_NONE       0x55

#define RM_IS_IPV6_LINK_LOCAL(address)                                          \
                               ((address[0] == 0xFE) &&                 \
                               ((address[1] & 0xC0) == 0x80))

/* Modified by lixs00177467, for rtm net route, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
#define GET_NETRT_STATE_BEGIN   1
#define GET_NETRT_STATE_MORE    0

 typedef struct tagRM_REDIST_FILTER
{
    ULONG ulRtmFlag; /*RTM 的标记, RM_TYPE_IPV4 0 是RTM4，RM_TYPE_IPV6 1则是RTM6 */
    ULONG ulFilterFlag; /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulDirectFlag; /*引入和导出方向选择*/
    ULONG ulProtocol;   /*路由引入的协议类型*/
    ULONG ulProcessId;  /*提供路由引入的进程ID*/
    /* Begin BC3D03313 liangjicheng 2010-06-22 */
    ULONG ulOnlyAdminUp; /*策略状态-用于区分引入过滤和引入*/
    /* End   BC3D03313 liangjicheng 2010-06-22 */
    ULONG ulAclMatchFlag; /*是否匹配acl 规则组:0 表示不匹配，1表示匹配*/
}RM_REDIST_FILTER_S;

typedef struct tagRM_CFG_INST 
{
    LONG lActionType; /*配置或删除；0-delete；1-create*/
    ULONG ulRtmInstance; /*RTM实例号*/
    LONG lConnRoutePri; /*直连路由的优先级，默认为0，取值0-255*/
    LONG lStatRoutePri; /*静态路由的优先级，默认为1，取值0-255*/
    LONG lOspfIntRoutePri; /*OSPF自治域内路由的优先级，默认为30，取值0-255*/
    LONG lOspfExtRoutePri; /*OSPF自治域外路由的优先级，默认为110，取值0-255*/
    LONG lRipRoutePri;  /*RIP路由的优先级，默认为120，取值0-255*/
    LONG lAddrFamily;  /*地址族，如IPv4，IPv6等*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ulI3Instance; /*I3实例号*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_CFG_INST_S;

typedef struct tagRM_CFG_MJOIN
{
    LONG lActionType; /*配置或删除；0-delete；1-create*/
    ULONG ulMajorId; /*RTM实例号*/
    ULONG ulSlaveId; /*从实例号*/
    LONG lSaveType;  /*从实例类型，即ARI接口的类型，如从实例为FIB时，ARI接口类型为AMB_RTM_ARI_PARTNER_FT*/ 
}RM_CFG_MJOIN_S;


typedef struct tagRM_DSP_MJOIN
{
    ULONG ulMasterId;/*RTM实例号*/
    ULONG ulSlaveId; /*从实例号*/
    LONG lSaveType;  /*从实例类型，即ARI接口的类型，如从实例为FIB时，ARI接口类型为AMB_RTM_ARI_PARTNER_FT*/  
    LONG lIfType;    /*主加入的接口类型*/
    LONG lJoinStatus;  /*主加入的状态*/
}RM_DSP_MJOIN_S;

typedef struct tagRM_DSP_SJOIN 
{
    ULONG ulSlaveId; /*RTM实例号*/
    LONG lIfType;  /*加入的接口类型*/
    LONG lMasterType; /*Rpm协议类型*/
    ULONG ulMasterId; /*主实例号*/
    LONG lJoinStatus; /*从加入状态*/
}RM_DSP_SJOIN_S;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagMIB_RTM_RIB_FILTER
{
    ULONG ulFilterFlag; /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulFilterLevel;/*过滤器使用及组合情况*/
    ULONG ulInstance;/*根据IPv4或者IPv6实例号过滤*/
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*根据路由目的地址过滤*/
    ULONG ulMask; /*根据路由掩码过滤，取值0-128*/    
    ULONG ulProtocol; /*根据路由协议号过滤*/ 
    ULONG ulProcessId; /*根据提供路由的进程ID过滤*/   
    ULONG ulVrf;
}MIB_RTM_RIB_FILTER_S;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef struct tag_rtm_rib_key_index /*用于获取NEXT 对端信息的索引值*/
{
  ULONG fte_index;
  LONG tos;
  LONG dest_type;    
  ULONG dest_addr_len;
  UCHAR dest[RM_IPV6_ADDRESS_WORD_LEN]; 
  LONG dest_len;
  LONG next_hop_type;  
  ULONG next_hop_len;
  UCHAR next_hop[RM_IPV6_ADDRESS_WORD_LEN];
  LONG if_index;
  LONG relay_next_hop_type;  
  ULONG relay_next_hop_len;
  UCHAR relay_next_hop[RM_IPV6_ADDRESS_WORD_LEN];
  LONG proto;   
  LONG rpm_index;
  /*Added by wangchengyang/jijianhua,2011/5/19   问题单号:RTM-20110512-01 */
  ULONG ulIsStatic;
  /* End of Added by wangchengyang/jijianhua, 2011/5/19   问题单号:RTM-20110512-01 */
  ULONG ulVrf;

  /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
  /*RM_RIB_FILTER_S stRIBFilter;*/
  MIB_RTM_RIB_FILTER_S stRIBFilter;
  /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}MIB_RTM_RIB_KEY_INDEX_S;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagMIB_RTM_ACRT_FILTER
{
    ULONG ulFilterFlag; /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulFilterLevel;/*过滤器使用及组合情况*/
    ULONG ulInstance;/*根据IPv4或者IPv6实例号过滤*/
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*根据路由目的地址过滤*/
    ULONG ulMask; /*根据路由掩码过滤，取值0-32*/     
    ULONG ulProtocol; /*根据路由协议号过滤*/ 
    ULONG ulVrf;
}MIB_RTM_ACRT_FILTER_S;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef struct tag_rtm_acrt_key_index /*用于获取NEXT 对端信息的索引值*/
{
  ULONG fte_index;
  LONG tos;
  LONG dest_type;    
  ULONG dest_addr_len;
  UCHAR dest[RM_IPV6_ADDRESS_WORD_LEN]; 
  LONG dest_len;
  LONG next_hop_type;  
  ULONG next_hop_len;
  UCHAR next_hop[RM_IPV6_ADDRESS_WORD_LEN];
  LONG if_index;
  LONG relay_next_hop_type;  
  ULONG relay_next_hop_len;
  UCHAR relay_next_hop[RM_IPV6_ADDRESS_WORD_LEN];
  /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
  /*RM_ACRT_FILTER_S stACRTFilter;*/
  MIB_RTM_ACRT_FILTER_S stACRTFilter;
  /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}MIB_RTM_ACRT_KEY_INDEX_S;

typedef struct tag_rtm_majoin_key_index /*用于获取NEXT 对端信息的索引值*/
{
  ULONG rtm_index;
  ULONG slave_id;
  LONG slave_type;
}MIB_RTM_MAJOIN_KEY_INDEX_S;

typedef struct tag_rtm_sljoin_key_index /*用于获取NEXT 对端信息的索引值*/
{
  ULONG rtm_index;
  LONG rpm_index;
}MIB_RTM_SLJOIN_KEY_INDEX_S;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagMIB_RTM_STATIC_FILTER
{
    ULONG ulFilterFlag; /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulFilterLevel;/*过滤器使用及组合情况*/
    ULONG ulInstance;/*实例号*/
    /*用于IPv4默认路由查询*/
    ULONG ulType;/*根据IPv4或者IPv6类型过滤*/
    ULONG ulVrfIndex;/*根据Vrf索引值过滤*/
    ULONG ulLinkGetFlg;/*根据链表获取默认路由*/
}MIB_RTM_STATIC_FILTER_S;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef struct tag_rtm_static_route_key_index /*用于获取NEXT 对端信息的索引值*/
{
  ULONG fte_index;
  LONG dest_addr_type; 
  ULONG dest_addr_len;                      
  UCHAR dest_addr[RM_IPV6_ADDRESS_WORD_LEN];  
  LONG dest_len;
  LONG next_hop_type; 
  ULONG next_hop_len;                     
  UCHAR next_hop[RM_IPV6_ADDRESS_WORD_LEN]; 
  LONG if_index;
  /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
  /*RM_STATIC_FILTER_S stStaticFilter;*/
  MIB_RTM_STATIC_FILTER_S stStaticFilter;
  /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}MIB_RTM_STATIC_ROUTE_KEY_INDEX_S;

typedef struct tagMIB_RTM_BRIEF_FILTER
{
    ULONG ulFilterFlag; /*过滤标记，1为过滤，0为不过滤*/
    ULONG ulFilterLevel;/*过滤器使用及组合情况*/
    ULONG ulInstance;/*实例号*/
    ULONG ulType;/*根据IPv4或者IPv6类型过滤*/
    ULONG ulVrfIndex;/*根据Vrf索引值过滤*/
}MIB_RTM_BRIEF_FILTER_S;

typedef struct tag_rtm_entity_key_index /*用于获取NEXT 对端信息的索引值*/
{
  ULONG fte_index;
  MIB_RTM_BRIEF_FILTER_S stBriefFilter;
}MIB_RTM_ENTITY_KEY_INDEX_S;

typedef struct tag_rtm_redist_key_index /*用于获取NEXT 对端信息的索引值*/
{
  ULONG fte_index;
  ULONG entry_id;
  ULONG ulGetState; /*当前的操作状态: GET_STATE_BEGIN, GET_STATE_MORE*/
  RM_REDIST_FILTER_S stRedistFilter;
}MIB_RTM_REDIST_KEY_INDEX_S;


typedef enum tagRTMMATCHERRCODE
{
    RTM_MATCH_DENY          = 0,
    RTM_MATCH_PERMIT        = 1,    
    RTM_MATCH_ERR_NOGROUP   = 2,
    RTM_MATCH_ERR_NORULE    = 3,
    RTM_NOT_MATCH   = 4,  /*luogaowei wangbin 2009-9-15 没有匹配上*/
}RTMMATCHERRCODE_E;

typedef struct tagRM_CFG_REDIST
{
    LONG lActionType; /*配置或删除；0-delete；1-create*/
    ULONG ulInstance; /*实例号*/ 
    ULONG ulPolicyId;  /*引入策略ID*/
    LONG lAddrFamily; /*地址族类型*/
    LONG lPriority; /*引入策略优先级，Default: 0x7FFFFFFF*/
    ULONG ulDirectFlag;
}RM_CFG_REDIST_S;


typedef struct tagRM_CFG_REDIST_SRCINSTFLT
{
    LONG lSrcProtoInfo; /*源路由协议信息，默认为所有，值为0*/
    LONG lSrcInstFlt; /*是否针对源实例过滤，默认为否，值为0*/
    ULONG ulSrcInst;  /*使用源实例过滤时，源实例号，默认为0*/
}RM_CFG_REDIST_SRCINSTFLT_S;

typedef struct tagRM_CFG_REDIST_DESTINSTFLT
{
    LONG lDestProtoInfo;  /*目的路由协议信息，默认为所有，值为0*/
    LONG lDestInstFlt;  /*是否针对目的实例过滤，默认为否，值为0*/
    ULONG ulDestInst;  /*使用目的实例过滤时，源实例号，默认为0*/
}RM_CFG_REDIST_DESTINSTFLT_S;

typedef struct tagRM_CFG_REDIST_DESTADDRFLT
{
    UCHAR aucAddrFilter[RM_IPV6_ADDRESS_WORD_LEN]; /*目的地址过滤*/
    LONG lAddrFltLen;  /*目的地址过滤器前缀（比特位），默认为0*/
}RM_CFG_REDIST_DESTADDRFLT_S;

typedef struct tagRM_CFG_REDIST_HOPADDRFLT
{
    UCHAR aucHopFltVal[RM_IPV6_ADDRESS_WORD_LEN];  /*下一跳地址过滤*/
    LONG lHopFltLen;  /*下一跳地址过滤器前缀（比特位），默认为0*/
}RM_CFG_REDIST_HOPADDRFLT_S;


typedef struct tagRM_CFG_REDIST_IFINDEXFLT
{
    LONG lIfIndexFlt; /*是否使用出接口索引过滤*/
    LONG lIfIndex;  /*出接口索引过滤*/
}RM_CFG_REDIST_IFINDEXFLT_S;

typedef struct tagRM_CFG_REDIST_PATHTYPEFLT
{
    LONG lPathtypeFlt;  /*是否使用路径类型过滤*/
    LONG lPathType;  /*路径类型过滤，默认为无路径过滤，值为0*/
}RM_CFG_REDIST_PATHTYPEFLT_S;

typedef struct tagRM_CFG_REDIST_OSPFFLT
{
    LONG lOspfAreaFlt;  /*是否使用OSPF区域过滤*/
    UCHAR aucOspfArea[4]; /*OSPF区域过滤器，默认为区域0，值为0*/
    LONG lOspfTagFlt;   /*是否使用OSPF tag过滤*/
    ULONG ulOspfTag;    /*OSPF tag过滤器，默认值为0*/
}RM_CFG_REDIST_OSPFFLT_S;

typedef struct tagRM_CFG_REDIST_DESTACLFLT
{
    LONG lDestAclFlt;  /*是否使用ACL过滤*/    
    ULONG ulDestAcl;  /*目的地址过滤器 ACL*/
}RM_CFG_REDIST_DESTACLFLT_S;

/* Modified by lixs00177467, for redirect by nexthop acl, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
typedef struct tagRM_CFG_REDIST_FLTGROUP
{
    LONG lDestAclFlt;  /*是否使用ACL过滤*/    
    ULONG ulDestAcl;  /*目的地址过滤器 ACL*/
    LONG lHopAclFlt;  /*是否使用ACL过滤*/    
    ULONG ulHopAcl;  /*目的地址过滤器 ACL*/
}RM_CFG_REDIST_FLTGROUP_S;
/*End of Modified by lixs00177467, 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */

typedef struct tagRM_CFG_REDIST_FLAG
{
    LONG lRedistFlag; /*引入标记*/
    LONG lMetricConv; /*引入路由cost值如何转变标记*/
    ULONG ulMetricValue; /*路由cost值*/   
    LONG lNwPathType;  /*路由路径类型*/  
    LONG lNwOspfTag;   /*OSPF tag值*/ 
}RM_CFG_REDIST_FLAG_S;

typedef struct tagRM_DSP_REDIST
{
    ULONG ulInstance;  /*实例号*/ 
    ULONG ulPolicyId;  /*引入策略ID*/
    LONG lAddrFamily;  /*地址族类型*/
    LONG lAdminStat;
    LONG lPriority;    /*引入策略优先级，Default: 0x7FFFFFFF*/
    ULONG ulDirectFlag;
    RM_CFG_REDIST_SRCINSTFLT_S  stRmRedistSrcInstFlt; 
    RM_CFG_REDIST_DESTINSTFLT_S  stRmRedistDestInstFlt; 
    RM_CFG_REDIST_DESTADDRFLT_S  stRmRedistDestAddrFlt; 
    RM_CFG_REDIST_HOPADDRFLT_S  stRmRedistHopAddrFlt;  
    RM_CFG_REDIST_IFINDEXFLT_S  stRmRedistIfIndexFlt;
    RM_CFG_REDIST_PATHTYPEFLT_S  stRmRedistPathTypeFlt; 
    RM_CFG_REDIST_OSPFFLT_S  stRmRedistOspfFlt;   
    RM_CFG_REDIST_DESTACLFLT_S  stRmRedistDestAclFlt;
    RM_CFG_REDIST_FLAG_S  stRmRedistFlagFlt;  
    /* Modified by lixs00177467, for redirect by nexthop acl, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
    RM_CFG_REDIST_FLTGROUP_S  stRmRedistGroupFlt;
    /*End of Modified by lixs00177467, 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
}RM_DSP_REDIST_S;

typedef enum enumRMRedist
{
/*Added by jijianhua00169178, 将RM_REDIST_CREATE定义一起放在RM_REDIST_S中, 2011/3/3   问题单号:DTS2011030203676 */
    RM_REDIST_CREATE = 0,
    RM_REDIST_SRCINST,
/* End of Added by jijianhua00169178, 2011/3/3   问题单号:DTS2011030203676 */
    RM_REDIST_DESTINST,
    RM_REDIST_DESTADDR,
    RM_REDIST_HOPADDR,
    RM_REDIST_IFINDEX,
    RM_REDIST_PATHTYPE,    
    RM_REDIST_OSPF,
    RM_REDIST_DESTACL,
    RM_REDIST_FLAG,
    /* Modified by lixs00177467, for redirect by nexthop acl, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
    RM_REDIST_FLTGROUP,
    /*End of Modified by lixs00177467, 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
    RM_REDIST_MAXNUM
}RM_REDIST_S;

typedef struct tagRMREDIST
{
    ULONG ulPolicyId;  /*引入策略ID*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ulRtmInstance;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    LONG lAdminStat;
    ULONG ulDirectFlag;
    RM_CFG_REDIST_SRCINSTFLT_S  stRmRedistSrcInstFlt; 
    RM_CFG_REDIST_DESTINSTFLT_S  stRmRedistDestInstFlt; 
    RM_CFG_REDIST_DESTADDRFLT_S  stRmRedistDestAddrFlt; 
    RM_CFG_REDIST_HOPADDRFLT_S  stRmRedistHopAddrFlt;  
    RM_CFG_REDIST_IFINDEXFLT_S  stRmRedistIfIndexFlt;
    RM_CFG_REDIST_PATHTYPEFLT_S  stRmRedistPathTypeFlt; 
    RM_CFG_REDIST_OSPFFLT_S  stRmRedistOspfFlt;   
    RM_CFG_REDIST_DESTACLFLT_S  stRmRedistDestAclFlt;
    RM_CFG_REDIST_FLAG_S  stRmRedistFlagFlt;   
    /* Modified by lixs00177467, for redirect by nexthop acl, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
    RM_CFG_REDIST_FLTGROUP_S  stRmRedistGroupFlt;
    /*End of Modified by lixs00177467, 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
    struct tagRMREDIST  *ia_pNext;
}RMREDIST_S;

typedef struct tagRM_STATIC_ROUTE4
{
    LONG row_status;
    LONG admin_status;
    ULONG dest_addr;/*目的地址*/
    LONG dest_len;/*掩码，取值0-32*/
    LONG if_index;/*出接口索引*/
    ULONG next_hop;/*下一跳或网关地址*/
    LONG use_action;
    LONG action;
    LONG override;
    LONG admin_dist;/*路由优先级，默认为1，取值1-255*/
    LONG use_path_cost;
    ULONG path_cost; /* 范围: 0 0xFFFFFFFF */
    LONG use_strt_dscp;
    UCHAR strt_dscp[RM_USR_DSCP_LEN + 1];/*路由描述 19 bytes*/
}RM_STATIC_ROUTE4_S;

typedef struct tagRM_CHECK_USR4
{
    /*add forSGSN联调 增加默认路由功能-增加ulOper，ulIfIndex，aucDescription l00147446 2010-1-18*/
    ULONG ulOper; /*配置或删除；0-delete；1-create*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*出接口名字*/
    ULONG ulRtPri;/*路由优先级，默认为1，取值1-255*/
    ULONG ulDestAddr;/*目的地址*/
    ULONG ulMask;/*掩码，取值0-32*/
    ULONG ulNextHopAddr;/*下一跳或网关地址*/
    ULONG ulAction; /*静态路由的ACTION类型*/
    ULONG ulPathCost;/*路径cost值，取值0－0xFFFF*/
    ULONG ulChkLocalIp;/*是否检查下一跳是本地Local IP*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ulIfIndex;
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*路由描述 19 bytes*/
}RM_CHECK_USR4_S;

typedef struct tagRM_DSP_INST
{
    ULONG ulInstance; /*实例号*/
    LONG lConnRoutePri; /*直连路由的优先级，默认为0，取值0-255*/
    LONG lStatRoutePri; /*静态路由的优先级，默认为1，取值1-255*/
    LONG lOspfIntRoutePri; /*OSPF自治域内路由的优先级，默认为30，取值0-255*/
    LONG lOspfExtRoutePri; /*OSPF自治域外路由的优先级，默认为110，取值0-255*/
    LONG lRipRoutePri;  /*RIP路由的优先级，默认为120，取值0-255*/
    LONG lAddrFamily;  /*地址族，如IPv4，IPv6等*/
    ULONG ulI3Index;   /*I3接口索引值*/
    LONG lI3JoinStatus; /*I3接口加入状态*/
}RM_DSP_INST_S;

typedef struct tagRM_ENABLE_USR6
{
    ULONG ulOper; /*使能或去使能；0-disable；1-enable*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];/*出接口名字*/
    UCHAR aucDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址 4*4 bytes */
    ULONG ulPrefixLen;/*前缀长度，取值0-128*/
    UCHAR aucNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*下一跳或网关地址 4*4 bytes */
    ULONG ulAction; /*静态路由的ACTION类型,只支持数值为2*/   
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];
}RM_ENABLE_USR6_S;

typedef struct tagRM_STATIC_ROUTE6
{
    LONG row_status;
    LONG admin_status;
    UCHAR dest_addr[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址 4*4 bytes*/
    LONG dest_len;/*掩码，取值0-128*/
    LONG if_index;/*出接口索引*/
    UCHAR next_hop[RM_IPV6_ADDRESS_WORD_LEN];/*目的地址 4*4 bytes*/
    LONG use_action;
    LONG action;
    LONG override;
    LONG admin_dist;/*路由优先级，默认为1，取值1-255*/
    LONG use_path_cost;
    ULONG path_cost; /* 范围: 0 0xFFFFFFFF */
    LONG use_strt_dscp;
    UCHAR strt_dscp[RM_USR_DSCP_LEN + 1];/*路由描述 19 bytes*/
}RM_STATIC_ROUTE6_S;

typedef struct tagRM_CHECK_USR6
{
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*出接口名字*/
    ULONG ulRtPri;/*路由优先级，默认为1，取值1-255*/
    ULONG ulDestAddr[4];/*目的地址 主机序 4*4 bytes*/
    ULONG ulPrefixLen;/*前缀长度，取值0-128*/
    ULONG ulNextHopAddr[4];/*下一跳或网关地址 主机序 4*4 bytes*/
    ULONG ulAction; /*静态路由的ACTION类型*/   
    ULONG ulPathCost;/*路径cost值，取值0－0xFFFF*/    
    ULONG ulChkLocalIp;/*检查下一跳是否与本地Local IP*/
}RM_CHECK_USR6_S;

/* Modified by lixs00177467, for rtm net route, VISPV2R3C03SPC010-G2 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */
typedef struct tagMIB_RTM_NET_FILTER
{
    ULONG ulIfIndex;/*根据接口索引值过滤*/
}MIB_RTM_NET_FILTER_S;

typedef struct tag_rtm_net_route_key_index /*用于获取NEXT 对端信息的索引值*/
{
  USHORT usNum;
  USHORT usGetState;
  RM_NETRT_FILTER_S stNetFilter;
}RTM_NET_ROUTE_KEY_INDEX_S;
/*End of Modified by lixs00177467, 2011/1/22   问题单号:V2R3C03-ROTUE-MERGE  */

typedef ACCESSLISTGROUP_S * (*RTMACLGETGROUP_HOOK_FUNC )(ULONG);
typedef ULONG(*RTMACLREFRESHREGISTER_HOOK_FUNC )(PF_ACLREFRESHCALLBACK, ULONG);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef ULONG (*RTMACLGETVRF_HOOK_FUNC )(ULONG,ULONG *);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/* BEGIN V2R3TEST */
/*IPV6 RTM  for  ACL6 */
typedef VOID * (*RTM6ACLGETGROUP_HOOK_FUNC )(ULONG);
typedef VOID  (*RTM6ACL6_LOCK_FUNC )(VOID);
typedef VOID  (*RTM6ACL6_UNLOCK_FUNC )(VOID);

typedef VOID  (*RTMACL_LOCK_FUNC )(VOID);
typedef VOID  (*RTMACL_UNLOCK_FUNC )(VOID);

extern RTM6ACL6_LOCK_FUNC  g_acl6Lock;
extern RTM6ACL6_UNLOCK_FUNC  g_acl6UnLock;
/* END V2R3TEST */
#define RM6_ACL6LOCK() \
{\
    if (g_acl6Lock) \
    {\
        (*g_acl6Lock)();\
    }\
}\

#define RM6_ACL6UNLOCK() \
{\
    if (g_acl6UnLock) \
    {\
        (*g_acl6UnLock)();\
    }\
}\

extern RTMACL_LOCK_FUNC  g_aclLock;
extern RTMACL_UNLOCK_FUNC  g_aclUnLock;

#define RM_ACLLOCK() \
{\
    if (g_aclLock)\
    {\
        (*g_aclLock)();\
    }\
}\

#define RM_ACLUNLOCK() \
{\
    if (g_aclUnLock)\
    {\
        (*g_aclUnLock)();\
    }\
}\


extern RTMACLGETGROUP_HOOK_FUNC g_pstRTMACLGetGroupCallBack;
extern RTMACLREFRESHREGISTER_HOOK_FUNC g_pstRTMACLRefreshRegisterCallBack;
/*************************新需求结构定义以及变量声明*******************/
/*****************************begin************************************/
typedef struct tagRM_CFGREDISTRIBUTE
{
    BOOL_T bNoFlag;
    USHORT usProcessId; /*RIP实例ID*/
    RM_RPM_PLCYREDIS_S stPolicyRedist;
}RM_CFGREDISTRIBUTE_S;

typedef struct tagRM_CFGDISTRIBUTE
{
    BOOL_T bNoFlag;
    USHORT usProcessId;
    RM_RPM_PLCYDIST_S stPolicyDist;
}RM_CFGDISTRIBUTE_S;

/*extern ULONG  g_ulProcessRTM4;*/  /*l61496 RTM4 的N-BASE 进程ID*/
/*extern ULONG  g_ulProcessRTM6;*/  /*l61496 RTM6 的N-BASE 进程ID*/

#define  RM_INIT_SUCCESS     0x01 /*RM初始化成功*/
#define  RM_INIT_FAILED      0x00 /*RM初始化失败*/

#define RPM_TO_RTM   1  /*RIP/OSPF 导出给RTM*/
#define RTM_TO_RPM   0  /*RTM 导入给RIP、OSPF*/
#define RTM_AND_RPM  2  /*两个方向都查询*/


#define RM_PLYCFG_PT_BEGIN           (VOID)TCPIP_SmP(g_ulSemForPlyCfg)
#define RM_PLYCFG_PT_END             (VOID)TCPIP_SmV(g_ulSemForPlyCfg)

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define RM_FILL_ROUTE_OID(inst,oid,dest_addr,dest_len,next_hop,if_index)\
{\
    NBB_INT ii;\
    oid[0] = AMB_QCR_STRT_OID_LEN;\
    oid[1] = AMB_FAM_CIPR_RTM_STATIC_RT;\
    oid[2] = (inst);\
\
    oid[AMB_QCR_STRT_DEST_ADDR_TYPE_IX] = AMB_INETWK_ADDR_TYPE_IPV4;\
    /*Modified begin by t00110672 for BC3D01783,   质量活动，消除魔鬼数字*/\
    oid[AMB_QCR_STRT_DEST_ADDR_INDEX] = ATS_INET_ADDR_TYPE_IPV4_LEN;\
\
    dest_addr = VOS_HTONL(dest_addr);\
    for (ii = 0; ii < ATS_INET_ADDR_TYPE_IPV4_LEN; ii++)\
    {\
        oid[AMB_QCR_STRT_DEST_ADDR_INDEX + 1 + ii] =\
                                         (NBB_ULONG)(((NBB_BYTE *)&dest_addr)[ii]);\
    }\
    oid[AMB_QCR_STRT_DEST_LEN_INDEX] = dest_len;\
    oid[AMB_QCR_STRT_NEXT_HOP_TYPE_IX] = AMB_INETWK_ADDR_TYPE_IPV4;\
    oid[AMB_QCR_STRT_NEXT_HOP_INDEX] = ATS_INET_ADDR_TYPE_IPV4_LEN;\
\
    next_hop = VOS_HTONL(next_hop);\
    for (ii = 0; ii < ATS_INET_ADDR_TYPE_IPV4_LEN; ii++)\
    {\
        oid[AMB_QCR_STRT_NEXT_HOP_INDEX + 1 + ii] =\
                                          (NBB_ULONG)(((NBB_BYTE *)&next_hop)[ii]);\
    }\
    /*End*/\
    oid[AMB_QCR_STRT_IF_INDEX_INDEX] = if_index;\
}
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*#define RM_FILL_ROUTE6_OID(oid,dest_addr,dest_len,next_hop,if_index)*/
#define RM_FILL_ROUTE6_OID(inst,oid,dest_addr,dest_len,next_hop,if_index)\
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */\
{\
    NBB_INT ii;\
    oid[0] = AMB_QCR_STRT_OID_LEN;\
    oid[1] = AMB_FAM_CIPR_RTM_STATIC_RT;\
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */\
    oid[2] = inst;\
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */\
\
    oid[AMB_QCR_STRT_DEST_ADDR_TYPE_IX] = AMB_INETWK_ADDR_TYPE_IPV6;\
    oid[AMB_QCR_STRT_DEST_ADDR_INDEX] = RM_IPV6_ADDRESS_WORD_LEN;\
\
    for (ii = 0; ii < 16; ii++)\
    {\
        oid[AMB_QCR_STRT_DEST_ADDR_INDEX + 1 + ii] =\
                                       (NBB_ULONG)(((NBB_BYTE *)dest_addr)[ii]);\
    }\
\
    oid[AMB_QCR_STRT_DEST_LEN_INDEX] = dest_len;\
\
    oid[AMB_QCR_STRT_NEXT_HOP_TYPE_IX] = AMB_INETWK_ADDR_TYPE_IPV6;\
    oid[AMB_QCR_STRT_NEXT_HOP_INDEX] = RM_IPV6_ADDRESS_WORD_LEN;\
    for (ii = 0; ii < 16; ii++)\
    {\
        oid[AMB_QCR_STRT_NEXT_HOP_INDEX + 1 + ii] =\
                                        (NBB_ULONG)(((NBB_BYTE *)next_hop)[ii]);\
    }\
\
    oid[AMB_QCR_STRT_IF_INDEX_INDEX] = if_index;\
}\


/****************************end *************************************/

/***************************************************************************/
/* Modified by jijianhua00169178, 消除coverity告警,   2011/8/12            */
/* ucPrefixLen==128时，数组越界访问,    问题单号:DTS2011081606263     */
/***************************************************************************/
#define RM_SUBADDR_BUILD(ucAddrType,pAddr,pSubAddr,ucPrefixLen)\
{\
  NBB_BYTE szMask[AMB_MAX_IPV6_ADDR_LEN];\
  NBB_BYTE qmfl_mask_byte = 0xFF;\
  NBB_LONG ulAddrType = (NBB_LONG)ucAddrType;\
  NBB_BYTE ucAddrLen,i;\
  NBB_BYTE *pDst,*pSrc;\
  ucAddrLen = ((AMB_INETWK_ADDR_TYPE_IPV4 == ulAddrType)?AMB_MAX_IPV4_ADDR_LEN : AMB_MAX_IPV6_ADDR_LEN);\
  (VOID)TCPIP_Mem_Set((CHAR*)szMask, 0, AMB_MAX_IPV6_ADDR_LEN);\
  if (0 != (ucPrefixLen/QCRT_NUM_BITS_IN_BYTE))\
  {\
    (VOID)TCPIP_Mem_Set((CHAR *)szMask, (CHAR)0xFF, (ucPrefixLen / QCRT_NUM_BITS_IN_BYTE));\
  }\
  qmfl_mask_byte = (NBB_BYTE)(qmfl_mask_byte << (QCRT_NUM_BITS_IN_BYTE - ((ucPrefixLen) % QCRT_NUM_BITS_IN_BYTE)));\
  if ((ucPrefixLen / QCRT_NUM_BITS_IN_BYTE) < AMB_MAX_IPV6_ADDR_LEN)\
  {                                                                 \
    szMask[(ucPrefixLen / QCRT_NUM_BITS_IN_BYTE)] = qmfl_mask_byte;\
  }                                                                 \
  for(i = 0;i < ucAddrLen;i++)\
  {\
    pSrc = ((NBB_BYTE*)(pAddr)+i);\
    pDst = ((NBB_BYTE*)(pSubAddr)+i);\
    *pDst = (NBB_BYTE)(*pSrc & szMask[i]);\
  }\
}
/*End of Modified by jijianhua00169178,2011/8/12问题单号:DTS2011081606263 */

/* Modified by chenwurui00206030 & zhongyu206043, 存在写越界情况（len=128） 2012/4/1   问题单号:fortify_dcl */
#define RM_SUBBCAST_BUILD(ucAddrType,pAddr,pSubAddr,ucPrefixLen)\
{\
  NBB_BYTE szMask[AMB_MAX_IPV6_ADDR_LEN];\
  NBB_BYTE qmfl_mask_byte = 0xFF;\
  NBB_LONG lAddrLen,i;\
  NBB_BYTE *pDst,*pSrc;\
  lAddrLen = ((AMB_INETWK_ADDR_TYPE_IPV4 == ucAddrType) ? AMB_MAX_IPV4_ADDR_LEN: AMB_MAX_IPV6_ADDR_LEN);\
  (VOID)TCPIP_Mem_Set((CHAR *)szMask, (CHAR)0xFF, AMB_MAX_IPV6_ADDR_LEN);\
  (VOID)TCPIP_Mem_Set((CHAR *)szMask, 0, (ucPrefixLen / QCRT_NUM_BITS_IN_BYTE));\
  qmfl_mask_byte = (NBB_BYTE)(qmfl_mask_byte >> ((ucPrefixLen) % QCRT_NUM_BITS_IN_BYTE));\
  if ((ucPrefixLen / QCRT_NUM_BITS_IN_BYTE) < AMB_MAX_IPV6_ADDR_LEN)\
  {\
    szMask[(ucPrefixLen / QCRT_NUM_BITS_IN_BYTE)] = qmfl_mask_byte;\
  }\
  for(i = 0;i < lAddrLen;i++)\
  {\
    pSrc = ((NBB_BYTE*)(pAddr)+i);\
    pDst = ((NBB_BYTE*)(pSubAddr)+i);\
    /*李雪生修改，DTS2011040100048 */\
    /**pDst = (NBB_BYTE)(*pSrc & szMask[i]);*/\
    *pDst = (NBB_BYTE)(*pSrc | szMask[i]);\
  }\
}
/*End of Modified by chenwurui00206030 & zhongyu206043, 2012/4/1   问题单号:fortify_dcl */


extern VOID RM_ShowMajorJoinAll();
extern VOID RM_ShowSlaveJoinAll();
extern RM_ERROR_S RM_SetMajorJoin(RM_CFG_MJOIN_S * pstRmMajorJoin);
extern RM_ERROR_S RM_CreateRtmInstance(RM_CFG_INST_S * pstRmInstance);
extern RM_ERROR_S RM_SetRouteRedist_Filter(ULONG ulInstance,ULONG ulPolicyId,ULONG redist_step,
                                     VOID * pstRedistFilter);
extern RM_ERROR_S RM_ApplyRouteRedist(ULONG ulInstance,ULONG ulPolicyId,LONG lEnableType);
extern RM_ERROR_S RM_GetRedist_WithPolicy(ULONG ulInstance, ULONG ulPolicyId,RM_DSP_REDIST_S * pstRedistPolicy);
extern RM_ERROR_S RM_CMM_REDIST_TableOpen(ULONG * pulSessionID,RM_REDIST_FILTER_S *pstRedistFilter);
extern RM_ERROR_S RM_CMM_REDIST_TableClose(ULONG ulSessionID );
extern RM_ERROR_S RM_CMM_REDIST_GetFirst(ULONG ulSessionID, RM_DSP_REDIST_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_REDIST_GetNext(ULONG ulSessionID, RM_DSP_REDIST_S * pstConfigInfo);
extern RM_ERROR_S RM_SetProtoPriority(ULONG ulInstance,ULONG ulProto,ULONG ulPriority);
extern RM_ERROR_S RM_GetProtoPriority(ULONG ulInstance,RM_DSP_INST_S *pstInstance);


/*Begin BC3D02811 默认路由功能修改有遗漏 l00147446 2010-03-10*/
extern RM_ERROR_S IP_ActiveIpv4Route(RM_CHECK_USR4_S *pstRmCheckRoute);
/*End BC3D02811 默认路由功能修改有遗漏 l00147446 2010-03-10*/
extern RM_ERROR_S IP_ActiveIpv6Route(RM_MOD_USR6_S *pstUsrIpTable);
extern RM_ERROR_S IP_CheckIpv4Route(RM_CHECK_USR4_S * pstUsrChkTable);
extern RM_ERROR_S IP_CheckIpv6Route(RM_CHECK_USR6_S * pstUsrChkTable);
extern RM_ERROR_S RM_EnableIpv6Route(RM_ENABLE_USR6_S * pstUsrIpEnable);
extern VOID RM_IPv4RIB_InfoOuput(RM_DSP_RIB_S *pstRib);
extern VOID RM_IPv4ACRT_InfoOuput(RM_DSP_ACRT_S *pstAcrt);
extern VOID RM_IPv6RIB_InfoOuput(RM_DSP_RIB_S *pstRib);
extern VOID RM_IPv6ACRT_InfoOuput(RM_DSP_ACRT_S *pstAcrt);
extern VOID RM_IPv4Static_InfoOuput(RM_DSP_STATICRT_S *pstStatic);
extern VOID RM_IPv6Static_InfoOuput(RM_DSP_STATICRT_S *pstStatic);
extern VOID RM_IPv4RtmBriefInfoOuput(RM_BRIEF_INFO_S *pstBrief);
extern RM_ERROR_S RM_IpAddrIsValid(ULONG ip_addr);
/************************************新需求函数声明****************************************************/
extern ULONG RM_Global_Init(VOID);
extern ULONG RM_GetFreePlyId(ULONG ulAddrFamily);
extern ULONG RM_AllocPolicyId(USHORT usDstType, USHORT usDstProcId, USHORT usSrcType, 
                                 USHORT usSrcProcId, ULONG ulDirection, ULONG *pulPolicyId,
                                 ULONG ulAddrFamily);
extern ULONG RM_FreePolicyId(ULONG ulPolicyId, ULONG ulAddrFamily);
extern ULONG RM_GetPolicyId(USHORT usDstType, USHORT usDstProcId ,USHORT usSrcType, USHORT usSrcProcId,
                            ULONG ulAddrFamily);
extern LONG RM_ProType_DclToApi(LONG ulSrcPro);
extern LONG RM_ProType_ApiToDcl(LONG ulSrcPro);
extern LONG RM_MetricType_DclToApi(LONG lPathType);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*extern RM_ERROR_S RM_CFG_CmdPolicyInProc (ULONG ulProType, RM_CFGREDISTRIBUTE_S* pstRedistIn);*/
/*extern RM_ERROR_S RM_CFG_CmdPolicyOutProc (ULONG ulProType, RM_CFGREDISTRIBUTE_S* pstRedistOut);*/
/*extern RM_ERROR_S RM_CFG_CmdDistributeOutProc (ULONG ulProType, RM_CFGDISTRIBUTE_S* pstDistExpIn);*/
/*extern RM_ERROR_S RM_CFG_CmdDistributeInProc (ULONG ulProType , RM_CFGDISTRIBUTE_S*  pstDistImpIn);*/
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/* Begin BC3D03313 liangjicheng 2010-06-22 */
RM_ERROR_S RM_CfgRedistContent(ULONG ulProtocol, LONG action_type, ULONG ulPolicyId, USHORT usProcessId , VOID *content);
ULONG RM_CfgPlyUserFlag( ULONG ulPolicyId, ULONG ulOpType, ULONG ulUserFlag);
ULONG RM_GetPlyUserFlag( ULONG ulPolicyId, ULONG *pulUserFlag);
ULONG RM_CfgPlyUserFilter( ULONG ulPolicyId, ULONG ulAclNo);
VOID RM_DelPlyWhenDestroy(USHORT usProcType, USHORT usProcId);
/* End   BC3D03313 liangjicheng 2010-06-22 */

/*快查内部接口*/

/* Deleted by jijianhua00169178, netroute删除, 2011/7/8   问题单号:DTS2011070700898 */
/* End of Deleted by jijianhua00169178, 2011/7/8   问题单号:DTS2011070700898*/

extern RM_ERROR_S RM_EnableIpv6RouteExt(RM_ENABLE_USR6_S * pstUsrIpEnable, ULONG ulVrfIndex);

#ifdef  __cplusplus
}
#endif

#endif 
