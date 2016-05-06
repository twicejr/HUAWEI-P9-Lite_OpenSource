/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_apiadp_stru01.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF 适配模块定义的结构(外围配置管理)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/

#ifndef OSPF_APIADP_STRU01_H
#define OSPF_APIADP_STRU01_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*认证接口基本信息
    AREA_CFG_LIST_ENTRY
    IF_CFG_LIST_ENTRY  */
typedef struct cfg_auth_data_tag
{
  NBB_ULONG auth_key_len;
  NBB_CHAR auth_key_value[256]; 
  NBB_ULONG auth_user_data_len;
  NBB_CHAR auth_user_data[4];
  NBB_BYTE auth_key_id;
  NBB_BYTE padding[3];
}CFG_AUTH_DATA;

/*01 OSPF 全局链表头结构*/
typedef struct ospf_cfg_list_info_tag
{
  /***************************************************************************/
  /* List root of ospf processes                                             */
  /***************************************************************************/
  NBB_ULONG ospf_num;
  NBB_LLQE_ROOT ospf_cfg_list_root;
}OSPF_CFG_LIST_INFO;

/*02 Network 全局链表头结构*/
typedef struct network_cfg_list_info_tag
{
  /***************************************************************************/
  /* List root of interfaces that ospf notified by I3.                       */
  /***************************************************************************/
  NBB_ULONG network_num;
  NBB_LLQE_ROOT network_cfg_list_root;
}NETWORK_CFG_LIST_INFO;

/*03 接口 全局链表头结构*/
typedef struct if_cfg_list_info_tag
{
  /***************************************************************************/
  /* List root of interfaces that ospf notified by I3.                       */
  /***************************************************************************/
  NBB_ULONG if_num;
  NBB_LLQE_ROOT if_cfg_list_root;
}IF_CFG_LIST_INFO;

/*11 OSPF 节点信息*/
typedef struct ospf_cfg_list_entry_tag
{
  NBB_LLQE ospf_cfg_list_node;          /*用来连在全局进程链表*/
  NBB_LLQE_ROOT ospf_area_cfg_list_root;/*用来管理OSPF区域*/

  /*进程基本信息*/
  NBB_ULONG ospf_process_id;  
  NBB_ULONG area_num;  
  NBB_ULONG ulGrHelperMode;
  NBB_ULONG ulGrPeriod;
  NBB_ULONG ulGrAccNum;
  /*End for BC3D03437 at 2010-07-16*/
   
  NBB_ULONG ulReserved1;
  NBB_ULONG ulReserved2;
}OSPF_CFG_LIST_ENTRY;

/*12 Area 节点信息*/
typedef struct area_cfg_list_entry_tag
{
  NBB_LLQE ospf_area_cfg_list_node; /*用来连在OSPF区域链表中*/
  OSPF_CFG_LIST_ENTRY *ospf_process;/*所属进程信息*/

  NBB_LLQE_ROOT area_network_cfg_list_root;/*用来管理区域中所有network*/

  /*基本信息*/ 
  NBB_ULONG area_id;  
  NBB_ULONG network_num;  
  NBB_LONG auth_type;
  CFG_AUTH_DATA auth_data;  /*指针变数组*/ 
  NBB_ULONG ulReserved1;
  NBB_ULONG ulReserved2;
}AREA_CFG_LIST_ENTRY;

/*13 Network 节点信息*/
typedef struct network_cfg_list_entry_tag
{
  NBB_LLQE network_cfg_list_node;       /*用来连在全局network链表中*/
  
  NBB_LLQE area_network_cfg_list_node;  /*用来连在区域的network链表中*/
  AREA_CFG_LIST_ENTRY *area;            /*所属区域信息*/
  
  NBB_LLQE_ROOT network_if_cfg_list_root; /*用来管理network所有接口*/
    
  /*network基本信息*/
  NBB_ULONG ip_addr;
  NBB_ULONG prefix_len; 
  NBB_ULONG ulReserved1;
  NBB_ULONG ulReserved2;
}NETWORK_CFG_LIST_ENTRY;

/*14 接口 节点信息*/
typedef struct if_cfg_list_entry_tag
{
  NBB_LLQE if_cfg_list_node;        /*用来连接在主接口链表上*/  
  NBB_LLQE second_ip_node;          /*B016 01 用来连接在从地址链表上*/  
  
  NBB_LLQE network_if_cfg_list_node;/*用来连接在network接口链表上*/ 
  /*指向所属于的network信息，可以获取区域信息进程信息*/
  NETWORK_CFG_LIST_ENTRY *network;  

  /*主从地址管理*/  
  NBB_ULONG primary_flag;               /*B016 02 1-primary 0-sencondary*/  
  /*指向所属于的接口*/
  struct if_cfg_list_entry_tag * primary_if;       /*B016 03*/
  NBB_ULONG second_ip_num;              /*B016 04*/
  NBB_LLQE_ROOT second_ip_list_root;    /*B016 05*/
  
  NBB_ULONG ref_cnt;  /*暂时无用，原来用来管理属于多个进程情况*/
  
  /*接口基本信息*/
  NBB_CHAR if_name[47+1]; 
  
  NBB_ULONG if_index;
  NBB_ULONG ip_addr;    /*网络序*/
  NBB_ULONG prefix_len;
  /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
  NBB_ULONG vrf_index;
  /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

  /*配置数据*/  
  USHORT usHelloInterval;
  USHORT usDeadItvl; 
  ULONG  ulFast_Hello_Multiplier;
  ULONG  ulIfCost;    
  UCHAR  ucNetworkType;
  UCHAR  ucPriority;
  USHORT usRetransInterval;
  NBB_BOOL	auth_configured;	/*DTS2010101601584 licheng lKF35457 2010-10-18 是否配置认证方式*/
  NBB_LONG auth_type;
  CFG_AUTH_DATA auth_data;   /*指针变数组*/ 
  /*Modified by liangjicheng 00103192, MTU基于接口配置, 2010/11/18   问题单号:DTS2010110104080  */
  NBB_ULONG ulMtuIgnore;
  /*End of Modified by liangjicheng 00103192, 2010/11/18   问题单号:DTS2010110104080  */

  NBB_ULONG ulReserved1;
  NBB_ULONG ulReserved2;
}IF_CFG_LIST_ENTRY;

/*Added by guojianjun178934, 适配中保持的OSPF NSR信息, 2012/12/10   问题单号:20121208_1 */
typedef struct nsr_ospf_api_adapt_info
{
    NSR_OSPF_ADP_STATISTICS stNSRAdpOSPFStat;
}NSR_OSPF_API_ADAPT_INFO;
/* End of Added by guojianjun178934, 2012/12/10   问题单号:20121208_1 */

/*进程全局管理*/
/*此数据结构用来标示一个ospf是否已经被使用*/
typedef struct tagOSPF_PROCESS_USED
{
    USHORT usProcessId;          /*实例id,由用户配置*/
    USHORT usUsedFlg;            /*1表明已经使用，0表示没有使用*/
    ULONG ulDclPid;              /*DCL内部使用的伪进程id*/
    
    /*Added by guojianjun178934, 适配中保存OSPF NSR信息, 2012/12/8   问题单号:20121208_1 */
    NSR_OSPF_API_ADAPT_INFO stNSRInfo;
    /* End of Added by guojianjun178934, 2012/12/8   问题单号:20121208_1 */
}OSPF_PROCESS_USED_S;

/*内部维护测试结构*/
typedef struct cfg_area_info
{
  NBB_ULONG ospf_process_id;
  NBB_ULONG area_id;
  NBB_LONG auth_type;
  NBB_ULONG auth_key_len;
  NBB_BYTE auth_key_value[256]; 
  NBB_ULONG auth_user_data_len;
  NBB_BYTE auth_user_data[4];
}CFG_AREA_INFO;

typedef struct cfg_network_info_tag
{
  NBB_ULONG ospf_process_id;
  NBB_ULONG area_id;
  NBB_ULONG ip_addr;
  NBB_ULONG prefix_len;
}CFG_NETWORK_INFO;

/*垃圾结构*/
/*此数据结构用来配置区域管理状态*/
typedef struct tagOSPF_CFGIF_AREAADMIN
{
    ULONG ulProcessId;                   /*进程ID*/
    ULONG ulAreaId;                      /*区域ID*/
    ULONG ulAdminStatus;                 /*区域管理状态*/
}OSPF_CFGIF_AREAADMIN_S;

typedef struct tagOSPF_CFG_IF_AREAID
{
    ULONG ulProcessId;
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG ulAreaId;
    ULONG ulEnableFlg;
}OSPF_CFG_IF_AREAID_S;

typedef struct tagOSPF_IF_DCL_FILTER
{
    ULONG  ulProcessId;
    ULONG  ulAdminStatus;
    ULONG  ulPassive;
} OSPF_IF_DCL_FILTER_S; /*用于DCL 内部查询过滤*/


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
