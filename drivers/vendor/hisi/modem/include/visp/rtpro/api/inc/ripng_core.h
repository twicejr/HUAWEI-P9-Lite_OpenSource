#ifndef _RIPNG_CORE_H
#define _RIPNG_CORE_H

#ifdef  __cplusplus
    extern "C"{
#endif


#define SID_RIPNG_ENTRY        11
#define SID_RIPNG_IF_CFG       12
#define SID_RIPNG_NBR          13
#define SID_RIPNG_ROUTE        14
#define SID_RIPNG_CFG_IF_INFO  15
#define SID_RIPNG_FILTER        16

#define  RIPNG_MAX_INSTANCE_NUM  65535 /*RIPNG从1开始编号*/
#define  RIPNG_MAX_INSTANCE_LIMIT  8 /*RIPNG最多8个*/

#define RIPNG_IPV6_MAX_ADDR_LEN  16
#define RIPNG_ROUTE_TAG_LEN      2

#define RIPNG_IPV6_ADDR_TYPE     2

#define  RIPNG_ROUTE_ONE_PATH 1 /*route中只有一个path*/ 
/*对于用户来说，
RIPV2 的范围是1--65535,
RIPng的范围也是1--65535,但是DCL 内部创建的时候开始不能区分的。
那么需要用户传入的索引值 和内存索引值建立一个映射关系
当返回给用户的时候要恢复用户传入的索引值
*/
#define   RIPV2_INDEX_USER_BASE     0x0000000  /*RIPV2内部偏移量*/
#define   RIPNG_INDEX_USER_BASE     0x4000000  /*RIPNG内部偏移量*/

#define   RIPNG_VERSION_V1                      1        /*RIPNG版本号1*/
#define   RIPNG_ROUTE_ENTRY_SIZE                20  /*每组路由条目 占20个字节*/
#define   RIPNG_ROUTE_ENTRY_MAX_NUM             25   /*最大25个条目*/

#define RIPNG_SPLIT_CFG      1 /*设置水平分割*/
#define RIPNG_POISON_CFG     2 /*设置毒性逆转*/
#define RIPNG_METRICIN_CFG   3 /*设置接收附加度量值*/
#define RIPNG_METRICOUT_CFG  4 /*设置发送附加度量值*/
#define RIPNG_DEF_METRIC_CFG 5 /*设置默认路由附加度量值*/

/*进程属性MIB配置项标志位*/
#define RIPNG_PRO_ATTR_TIMER_BIT    0x0001 /*定时器标志*/
#define RIPNG_PRO_ATTR_BALANCE_BIT       0x0002 /*最大平衡路由标志*/

extern RIPNG_PACKET_HOOK_FUNC g_pstRipngInputPktHook;
extern RIPNG_PACKET_HOOK_FUNC g_pstRipngOuputPktHook;

typedef struct tagRIPng_If_Cfg_Ex
{  
    USHORT usFlag;         /*配置有效标志位*/
    USHORT usDefRtMetric;  /*默认路由附加路由权值*/ 
    UCHAR  ucSplitHorizon; /*是否配置水平分割*/
    UCHAR  ucPoisonReverse;/*是否配置毒性逆转*/
    UCHAR  ucMetricIn;     /*接收附加路由权值*/
    UCHAR  ucMetricOut;    /*发送附加路由权值*/ 
    ULONG ulIfIndex;          /*接口索引*/ 
}RIPNG_IF_CFG_EX_S; 

typedef struct tagRIPng_If_Ex_Cfg_list
{  
    RIPNG_IF_CFG_EX_S stIfExInfo;    
    NBB_LLQE  stRIPngIfExNode;    /*RIPNG 接口扩展属性配置链表*/
}RIPNG_IF_EX_CFG_LIST_S;

typedef struct tagRIPng_If_Cfg_list
{  
    ULONG ulProcId;
    ULONG ulIfIndex;
    NBB_LLQE  stRIPngIfNode;/*RIPNG 接口配置链表*/
}RIPNG_IF_CFG_LIST_S; 


#define RIPNG_IF_CFG_PT_BEGIN       (VOID)TCPIP_SmP(g_ulSemRIPngIfCfg)
#define RIPNG_IF_CFG_PT_END         (VOID)TCPIP_SmV(g_ulSemRIPngIfCfg)

#define RIPNG_IF_MIB_CFG_PT_BEGIN       (VOID)TCPIP_SmP(g_ulSemRIPngMibIfCfg)
#define RIPNG_IF_MIB_CFG_PT_END         (VOID)TCPIP_SmV(g_ulSemRIPngMibIfCfg)


typedef struct tagRIPng_Proc
{
    ULONG  ulProcessPId;/*RIPng实例进程PID*/
    ULONG  ulProcId;    /*RIPng的实例号*/
    UCHAR  ucUsedFlag;  /*实例是否被使用*/
    UCHAR  ucRipVersion;/*RIPV2 还是RIPng*/
    UCHAR  ucPad[2];     /*填充字段*/
}RIPNG_PROC_S; /*RIP PROC 结构:关联实例号和进程ID*/


/*RIPNG 查询的索引值*/
typedef struct tagRIPNG_PROC_KEY
{
    ULONG ulProcId;/*下一个RIPNG 进程id*/
    ULONG ulFltProcId;/*保存用户传入的查询条件*/
}RIPNG_PROC_KEY_S;


/*RIPNG 接口配置查询KEY*/
typedef struct tagRIPNG_If_Cfg_KEY
{
    ULONG ulProcId;/*下一个RIPNG 进程id*/
    ULONG ulFltProcId;/*保存用户传入的查询条件*/
    ULONG ulIfIndex; /*接口索引值*/    
    ULONG ulGetState; /*当前的操作状态: GET_STATE_BEGIN, GET_STATE_MORE*/
}RIPNG_IF_CFG_KEY_S;


typedef struct tagRIPNG_ROUTE_KEY
{
  CHAR ucDestAddr[LEN_16]; /*IPV6 地址*/
  ULONG ulPrefixLen;   /*IPV6 地址前缀长度*/
  ULONG ulProcId;/*下一个RIPNG 进程id*/
  ULONG ulFltProcId;/*保存用户传入的查询条件*/   
  ULONG ulGetState; /*当前的操作状态: GET_STATE_BEGIN, GET_STATE_MORE*/
} RIPNG_ROUTE_KEY_S;/*RIPng 路由查询KEY*/

/*RIPNG 用于获取Next Nbr信息的索引值*/
typedef struct tagRIPNG_NBR_NEXT
{
    ULONG ent_index;    /*RIPNG实例号*/
    LONG address_type;  /*地址类型*/               
    ULONG address_len;  /*地址长度*/              
    UCHAR address[RIPNG_IPV6_MAX_ADDR_LEN];  /*地址*/
    UCHAR domain[RIPNG_ROUTE_TAG_LEN];  /*域*/
    UCHAR ucPad[2];
}RIPNG_NBR_NEXT_S;

/*RIPNG 邻居显示查询KEY*/
typedef struct tagRIPNG_NBR_KEY
{
    ULONG flt_procid;   /*过滤进程ID*/ 
    ULONG addr_type;    /*地址类型，区分是IPv4还是IPv6查询*/
    RIPNG_NBR_NEXT_S nbr_next;
}RIPNG_NBR_KEY_S;

/*RIPNG的DCL实例号*/
typedef struct tagRIPNG_FILTER
{
    ULONG flt_procid;   /*过滤进程ID*/ 
    ULONG addr_type;    /*地址类型，区分是IPv4还是IPv6查询*/
} RIPNG_FILTER_S; 

/*RIPNG 接口绑定配置查询KEY*/
typedef struct tagRIPNG_CFG_IF_KEY
{
    ULONG ulFltProcessId;   /*过滤进程ID*/ 
    ULONG ulFltIfIndex;     /*过滤接口索引*/ 
    ULONG ulIfIndex;        /*接口索引*/    
}RIPNG_CFG_IF_KEY_S;


#define  RIPNG_FILTER_IMPORT_TYPE       0x01   /*接收过滤类型*/
#define  RIPNG_FILTER_DISTRIBUTE_TYPE  0x02   /*发布过滤类型*/

typedef struct tagRIPng_FilterList
{
    ULONG ulFilterFlag;/*RIPNG_FILTER_IMPORT_TYPE RIPNG_FILTER_DISTRIBUTE_TYPE   */
    ULONG ulProcId;/*RIP实例号*/
    ULONG ulAclNum;
    NBB_LLQE  stFilterNode;/*链表*/
}RIPNG_FILTER_LIST_S; /*存放RIP 的网段链表*/


typedef struct tagRIPng_Filter_ips
{
    NBB_IPS ips_hdr;
    ULONG ulPad;
}RIPNG_FILTER_IPS_S;

/*RIPNG 发布过滤或者接收过滤配置查询KEY*/
typedef struct tagRIPng_Filter_Get_Key
{
    ULONG ulProcId;/*下一个RIPNG 进程id*/
    ULONG ulFltProcId;/*保存用户传入的查询条件*/    
    ULONG ulGetState; /*当前的操作状态: GET_STATE_BEGIN, GET_STATE_MORE*/
}RIPNG_FILTER_GET_KEY_S;

/*RIPNG 报文首部 4字节*/
typedef struct tagRipngPacketHead{
    UCHAR   ucCmd;
    UCHAR   ucVersion;
    USHORT usRtDomain;
}RIPNG_PACKET_HEAD_S; 

 /*RIPNG报文每个条目结构 20字节*/
typedef struct tagRipngEntryInfo{
    UCHAR   ucDestIp[RIPNG_IPV6_ADDRESS_WORD_LEN];
    USHORT usRtTag;
    UCHAR   ucMask;
    UCHAR   ucMetric;    
}RIPNG_ENTRY_INFO_S;

 /*RIPNG 接口扩展属性配置查询key*/
typedef struct tagRipng_If_Cfg_Ex_Key
{
    ULONG ulFltIfIndex;     /*过滤接口索引*/ 
    ULONG ulIfIndex;        /*接口索引*/    
}RIPNG_IF_CFG_EX_KEY_S;

 /*RIPNG 的进程属性MIB配置结构*/
typedef struct tagRIPNG_PRO_ATTR_MIB_CFG 
{ 
    BOOL_T bUndoConfig;  /*表明配置还是删除;
                                                  RIPNG_CFG_ADD - 配置
                                                  RIPNG_CFG_DEL  - 删除*/
    USHORT usProcId;     /*RIPNG的实例号*/
    ULONG  ulUpdateTimeOutVal; /*更新定时器,默认30秒，取值范围1-255*/
    ULONG  ulAgeTimeOutVal;    /*老化定时器,默认180秒，取值范围1-255*/
    ULONG  ulGarbageTimeOutVal;/*垃圾搜集定时器,默认120秒，取值范围1-255*/
    USHORT usNumBalancePaths; /*平衡路由个数,默认4，取值范围1-4*/
    USHORT usAttrFlag;    /*属性项标志*/
}RIPNG_PRO_ATTR_MIB_CFG_S;
 
/*RIP初始化条件检查*/
#define   RIPng_Valid_Check(pInfoInput)\
{\
    if (NULL == g_pstI3VRFFunTable)\
    {\
        ulRet = RIP_ERR_VRF_NOT_INIT;\
        goto EXIT_LABEL;\
    }\
    \
    if (RIP_INIT_SUCCESS != g_ulRIPInitState)/*RIP资源初始化没有成功*/\
    {\
        ulRet = RIP_ERR_INIT_FAILED;\
        goto EXIT_LABEL;\
    }\
    \
    if (NULL == pInfoInput)/*输入指针为空*/\
    {\
        ulRet = RIP_ERR_POINTER_IS_NULL;\
        goto EXIT_LABEL;\
    }\
}

/*RIPng 的undoflag 有效性检查*/
#define RIPng_UndoFlag_Check(bUndoFlag)\
{\
    if (RIP_CFG_ADD != bUndoFlag  && RIP_CFG_DEL != bUndoFlag)\
    {\
        ulRet = RIP_ERR_CONFIG_FLAG_INVALID;\
        goto EXIT_LABEL;\
    }\
    if ((RIP_CFG_ADD == bUndoFlag) && (g_ulCurRIPngCount >= g_ulRIPngMaxNum))/*超过设置的范围*/\
    {\
        ulRet = RIP_ERR_INSTANCE_IS_EXCEED_LIMIT;\
        goto EXIT_LABEL;\
    }\
}

#define  RIPng_Add_Join(ulProcId, rtmIndex)\
{\
    ulRet = RIP_CFG_JoinToOther(ulProcId, RIP_CFG_ADD,\
         AMB_RIP_IF_RTE_PROT_INPUT, rtmIndex);/*RTM IPV6*/\
    if (RIP_SUCCESS != ulRet)\
    {\
        ulRet = RIP_ERR_JOIN_FAILED;/*JOIN失败*/\
        goto EXIT_LABEL;\
    }\
}

#define  RIPng_Cancel_Join(ulProcId, rtmIndex)\
{\
    ulRet = RIP_CFG_JoinToOther(ulProcId, RIP_CFG_DEL, \
         AMB_RIP_IF_RTE_PROT_INPUT, rtmIndex);/*RTM IPV6*/\
    if (RIP_SUCCESS != ulRet)\
    {\
        ulRet = RIP_ERR_CANCEL_JOIN_FAILED;/*取消JOIN失败*/\
        goto EXIT_LABEL;\
    }\
}

#define  RIPng_Ret_Opt(ret)\
{\
    if (VOS_OK != ret)\
    {\
        goto EXIT_LABEL;\
    }\
}

/*发送IPS消息后返回的判断操作*/
#define  RIPng_IPS_Ret_Opt(ulRet, ips)\
{\
    if (RIP_SUCCESS != ulRet)\
    {\
        ulRet  += MID_COMP_RIP;\
        goto EXIT_LABEL;\
    }\
    \
    if (NULL == ips)\
    {\
        ulRet = RIP_ERR_RET_IPS_IS_NULL;\
        goto EXIT_LABEL;\
    }\
    \
    ulRet = ((AMB_SET *)ips)->ret_code;\
    if (ulRet == AMB_RC_NO_ERROR)\
    {\
        ulRet = RIP_SUCCESS;\
    }\
    else\
    {\
        ulRet += MID_COMP_RIP;\
        goto EXIT_LABEL;\
    }\
}

/* 主机序转为网络序 */
#define RIPNG_ADDRESS_HTON(x) \
{\
    (x)[0] = VOS_HTONL((x)[0]);\
    (x)[1] = VOS_HTONL((x)[1]);\
    (x)[2] = VOS_HTONL((x)[2]);\
    (x)[3] = VOS_HTONL((x)[3]);\
}

/* 网络序 转为主机序*/
#define RIPNG_ADDRESS_NTOH(x) \
{\
    (x)[0] = VOS_NTOHL((x)[0]);\
    (x)[1] = VOS_NTOHL((x)[1]);\
    (x)[2] = VOS_NTOHL((x)[2]);\
    (x)[3] = VOS_NTOHL((x)[3]);\
}


extern ULONG RIPng_Init(VOID);
extern ULONG RIPng_Destroy(VOID);
extern   BOOL_T  IsRipngExist(ULONG ulProcId, ULONG ulRipVersion);
/*消除Warning */
extern VOID TCPIP_InfoOutput(CHAR *pInfo);
extern VOID RIPng_proc_info_ouput(RIPNG_PROC_INFO_S *pstShowInfo);
extern ULONG RIPng_get_next_proc(ULONG ulProcId);
extern ULONG RIPng_get_proc_mib(ULONG ulProcId, RIPNG_PROC_INFO_S *pstProcInfo);
extern ULONG RIPng_AddIfCfgNode(ULONG ulIfIndex, ULONG ulProcId);
extern ULONG RIPng_DelIfCfgNode(ULONG ulIfIndex, ULONG ulProcId);
extern BOOL_T RIPng_BindCheck(ULONG ulIfIndex, RIPNG_IF_CFG_LIST_S **pstIfStores);
extern VOID RIPng_intf_info_ouput(RIPNG_INTF_INFO_S *pstShowInfo);
extern ULONG RIPng_get_if_mib(RIPNG_IF_CFG_KEY_S *pstKeyInfo, RIPNG_INTF_INFO_S *pstIntfInfo);
extern ULONG RIPng_Mib_Cfg_Proc(RIPNG_CFG_PROC_S *pstCfgInfo, ULONG ulVrfIndex, ULONG ulRtmIPV6Instance);
extern ULONG RIPng_If_Cfg_Check(CHAR *pszIfName, ULONG *pulIfIndex);
extern ULONG RIPng_Mib_Cfg_Intf(ULONG ulInnerPorcId,  BOOL_T bUndoConfig, ULONG ulIfIndex);
extern ULONG RIPng_ReCfgIfMibFromI3(ULONG ulType, ULONG ulIfIndex);
extern ULONG  RIPng_ReCfgIfMib(ULONG ulProcId);
extern ULONG TCPIP_SmP(ULONG ulMutexID);
extern ULONG TCPIP_SmV(ULONG ulMutexID);
extern ULONG  RIPng_BindJuge(BOOL_T bUndoConfig,  BOOL_T bExist);
extern ULONG RIPng_get_one_route(RIPNG_ROUTE_KEY_S *pstIndex, RIPNG_ROUTE_GROUP_S *pstRouteInfo);
extern VOID RIPng_route_info_ouput(RIPNG_ROUTE_GROUP_S *pstShowInfo);
extern ULONG RIPng_nbr_get_process(ULONG ulSessionId, RIPNG_NBR_INFO_S *pstNbrInfo,ULONG ulStep);
extern VOID RIPng_nbr_info_ouput(RIPNG_NBR_INFO_S *pstRIPngOut);
extern ULONG RIPng_get_nbr_mib(RIPNG_NBR_KEY_S *pstIndex, RIPNG_NBR_INFO_S *pstNbrInfo,ULONG step);
extern VOID RIPng_Route_FilterForInterface(RIPNG_ROUTE_GROUP_S *pstRouteInfo);
extern BOOL_T RIPng_BindCheck(ULONG ulIfIndex, RIPNG_IF_CFG_LIST_S **pstIfStores);
extern VOID RIPng_cfg_intf_info_output(RIPNG_SHOWCFGINTF_S *pstCfgIntfIn);
extern VOID RIPng_copy_cfg_intf_info(RIPNG_IF_CFG_LIST_S *pstIfStores,RIPNG_SHOWCFGINTF_S *pstIntfIn);
extern RIPNG_IF_CFG_LIST_S *RIPng_get_next_if(ULONG ulIfIndex, ULONG ulProcessId);
extern BOOL_T RIPng_proc_bind_check(ULONG ulProcessId);
extern VOID RIPng_GetPacket_In(ULONG ulProcId ,ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);
extern VOID RIPng_GetPacket_Out(ULONG ulProcId ,ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);
extern BOOL_T RIPng_filter_rule_is_exist(RIPNG_CFG_FILTER_INFO_S* pstFilterCfg, ULONG ulFilterType);
extern ULONG RIPng_add_filter_rule(RIPNG_CFG_FILTER_INFO_S* pstFilterCfg, ULONG ulFilterType);
extern ULONG RIPng_del_filter_rule(RIPNG_CFG_FILTER_INFO_S* pstFilterCfg, ULONG ulFilterType);
extern ULONG RIPng_cfg_resource_clear(USHORT usProcessId, ULONG ulMode);
extern ULONG RIPng_acl6_change_notify(ULONG ulAclGroupNum, ULONG ulReserve1, ULONG ulReserve2);
extern ULONG RIPng_get_filter_rule(ULONG ulProcId, ULONG ulFilterFlag, ULONG *pulAclNum);
extern VOID RIPng_cmm_import_show_one(RIPNG_SHOW_REDIST_S  *pstConfigInfo);
extern ULONG RIPng_acl6_match_by_dest_ip (ULONG ulProcId, ULONG ulACLNumber, UCHAR ucAddr[LEN_16], ULONG ulPrfixLen);
extern VOID RIPng_cmm_export_filter_show_one(RIPNG_SHOW_EXPORT_FILTER_S  *pstConfigInfo);
extern ULONG RIPng_update_import_route(ULONG ulProcId);
extern ULONG RIPng_get_cfg_import_filter_info(ULONG ulProcId, ULONG ulFilterType, 
            RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut);
extern VOID RIPng_cmm_distribute_filter_show_one(RIPNG_SHOW_DISTRIBUTE_FILTER_S  *pstConfigInfo);
extern VOID RIPng_cmm_import_filter_show_one(RIPNG_SHOW_IMPORT_FILTER_S  *pstConfigInfo);

extern ULONG RIPng_get_cfg_distribute_filter_info(ULONG ulProcId, ULONG ulFilterType, 
        RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut);       
ULONG RIPng_pro_attr_cfg_mib(RIPNG_PRO_ATTR_MIB_CFG_S *pstMibCfgInfo);
extern ULONG RIPng_IntfExProcess (BOOL_T bUndoConfig, ULONG ulIfIndex, USHORT usType, USHORT usValue);
extern VOID RIPng_intf_Ex_info_output(RIPNG_INTF_EX_INFO_S *pstIntfExIn);
extern ULONG RIPng_del_all_filter_rule(ULONG ulProcId);
extern VOID RIPng_GetIfCfgExInfoByInf (ULONG ulIfIndex, RIPNG_IF_CFG_EX_S *pstIfCfgExInfo);
extern RIPNG_IF_EX_CFG_LIST_S *RIPng_AddIfExCfgNode(ULONG ulIfIndex);
extern VOID RIPng_DelIfExCfgNode(ULONG ulIfIndex);
extern RIPNG_IF_EX_CFG_LIST_S *RIPng_get_next_if_excfg(ULONG ulIfIndex);
extern RIPNG_IF_EX_CFG_LIST_S *RIPng_get_spec_if_excfg(ULONG ulIfIndex);
extern ULONG RIPng_cfg_defrtorig_mib(BOOL_T bUndoConfig, ULONG ulInnerProcId,  ULONG ulIfIndex, USHORT usMetricVal);
extern ULONG  RIPng_CMM_Route_GetProc(ULONG ulHandle, RIPNG_ROUTE_GROUP_S *pstRouteInfo);
extern ULONG  RIPng_CMM_Intf_GetProc(ULONG ulSessionId, RIPNG_INTF_INFO_S *pstIntfInfo);
extern ULONG RIPng_get_next_policy_exist_proc(ULONG ulProcId,ULONG ulFilterType);
extern ULONG RIPng_get_process_info (ULONG ulSessionId, RIPNG_PROC_INFO_S *pstProcInfo, ULONG ulStep);
#ifdef  __cplusplus
}
#endif

#endif 

