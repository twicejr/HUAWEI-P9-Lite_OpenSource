#ifndef _RIPNG_API_H
#define _RIPNG_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

/*MACRO<RIPNG_Define> */
#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH              47          /*接口名最大长度*/
#endif
#define RIPNG_CFG_ADD                   0           /*配置添加*/
#define RIPNG_CFG_DEL                   1           /*配置删除*/
#define RIPNG_INPUT                     1           /*RIPng接收方向*/
#define RIPNG_OUTPUT                    2           /*RIPng发送方向*/
#define RIPNG_MAX_VRFNAME_LENGTH        31          /*VRF 名最大长度*/
#define RIPNG_MAX_VRF_NAME_LENGTH       31          /*VRF 名最大长度*/
#define RIPNG_IPV6_ADDRESS_WORD_LEN     16          /*IPV6地址字节 4*4 bytes*/
#define RIPNG_MAX_EQUAL_ROUTE_NUM       32          /*RIPng的平衡路由宏值*/
#define RIPNG_MAX_UPDATE_TIMEOUT        255         /*更新定时器,最大取值255秒*/
#define RIPNG_MIN_UPDATE_TIMEOUT        1           /*更新定时器,最小取值1秒*/
#define RIPNG_DEF_UPDATE_TIMEOUT        30          /*更新定时器,默认30秒*/
#define RIPNG_MAX_AGE_TIMEOUT           255         /*老化定时器最大取值255*/
#define RIPNG_MIN_AGE_TIMEOUT           1           /*老化定时器最小取值1*/
#define RIPNG_DEF_AGE_TIMEOUT           180         /*老化定时器,默认180秒*/
#define RIPNG_MAX_GARBAGE_TIMEOUT       255         /*垃圾搜集定时器最大取值255*/
#define RIPNG_MIN_GARBAGE_TIMEOUT       1           /*垃圾搜集定时器最小取值1*/
#define RIPNG_DEF_GARBAGE_TIMEOUT       120         /*垃圾搜集定时器,默认120秒*/
#define RIPNG_MAX_PREFERENCE            255         /*RIPNG路由优先级最大取值255*/
#define RIPNG_MIN_PREFERENCE            1           /*RIPNG路由优先级最小取值1*/
#define RIPNG_DEF_PREFERENCE            120         /*RIPNG路由优先级,默认120*/
#define RIPNG_MAX_BALANCE_NUMBER        4           /*最大平衡路由个数,最大取值4*/
#define RIPNG_MIN_BALANCE_NUMBER        1           /*最大平衡路由个数,最小取值1*/
#define RIPNG_DEF_BALANCE_NUMBER        4           /*最大平衡路由个数,默认4*/
#define RIPNG_SPLIT_ENABLE_B            0x01        /*设置水平分割使能位*/
#define RIPNG_POISON_ENABLE_B           0x02        /*设置毒性逆转使能位*/
#define RIPNG_METRICIN_ENABLE_B         0x04        /*设置接收附加度量值使能位*/
#define RIPNG_METRICOUT_ENABLE_B        0x08        /*设置发送附加度量值使能位*/
#define RIPNG_DEF_METRIC_ENABLE_B       0x10        /*设置默认路由附加度量值使能位*/
#define RIPNG_METRIC_INOUT_DEF          0           /*接收发送附加度量默认值*/
#define RIPNG_METRIC_INOUT_MIN          1           /*接收发送附加度量最小值*/
#define RIPNG_METRIC_INOUT_MAX          15          /*接收发送附加度量最大值*/
#define RIPNG_DEFAULT_METRIC_DEF        0           /*默认路由附加度量默认值*/
#define RIPNG_DEFAULT_METRIC_MIN        1           /*默认路由附加度量最小值*/
#define RIPNG_DEFAULT_METRIC_MAX        15          /*默认路由附加度量最大值*/

/*RIP 收发报文注册钩子函数类型*/
typedef ULONG (*RIPNG_PACKET_HOOK_FUNC)(ULONG ulProcId ,ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);


/*STRUCT<RIPNG进程配置,最多16个RIPNG>*/
typedef struct tagRIPNG_CFG_PROC
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - 配置
                           RIPNG_CFG_DEL  - 删除*/
    USHORT usProcId;      /*RIPNG的实例号取值范围：[1,0xffff]*/
    CHAR   szVrfName[RIPNG_MAX_VRF_NAME_LENGTH + 1]; /*vrf 名称，最大31字节 取值范围：非空*/
}RIPNG_CFG_PROC_S;

/*STRUCT<RIPNG 的定时器配置结构>*/
typedef struct tagRIPNG_CFG_TIMERS 
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - 配置
                           RIPNG_CFG_DEL  - 删除*/
    USHORT usProcId;            /*RIPNG的实例号取值范围：[1,0xffff]*/
    ULONG  ulUpdateTimeOutVal; /*更新定时器,默认30秒，取值范围1-255*/
    ULONG  ulAgeTimeOutVal;    /*老化定时器,默认180秒，取值范围1-255*/
    ULONG  ulGarbageTimeOutVal;/*垃圾搜集定时器,默认120秒，取值范围1-255*/
}RIPNG_CFG_TIMERS_S;

/*STRUCT<RIPNG的平衡路由个数配置>*/
typedef struct tagRIPNG_CFG_MAXLOAD 
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - 配置
                           RIPNG_CFG_DEL  - 删除*/
    USHORT usProcId;            /*RIPNG的实例号取值范围：[1,0xffff]*/
    USHORT usNumBalancePaths;   /*平衡路由个数,默认4，--取值范围1-4*/
    UCHAR  aucPad[2];           /*填充 --*/
}RIPNG_CFG_MAXLOAD_S;

/*STRUCT<RIPNG的接口使能>*/
typedef struct tagRIPNG_CFG_ENABLE
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - 配置
                           RIPNG_CFG_DEL  - 删除*/
    USHORT usProcId;     /*RIPNG的实例号取值范围：[1,0xffff]*/
    UCHAR  szIfName [MAX_IF_NAME_LENGTH + 1];   /*接口名,最大47字节--取值范围：非空*/
}RIPNG_CFG_ENABLE_S; 

/*STRUCT<RIPNG的实例查询结构>*/
typedef struct tagRIPNG_PROC_INFO
{  
    USHORT usProcId;            /*RIPNG的实例号取值范围：[1,0xffff]*/
    USHORT usMaxBalCount;       /*最大平衡路由个数，默认4，--取值范围1-4*/ 
    ULONG  ulVrfIndex;          /*VRF索引值--取值范围非0的32为整型*/
    UCHAR  ucUpdateTimeOutVal;  /*刷新时间,默认30秒，--取值范围1-255*/ 
    UCHAR  ucAgeTimeOutVal;     /*老化超时时间,默认180秒，--取值范围1-255*/
    UCHAR  ucGarbageTimeOutVal; /*垃圾搜集时间,默认120秒，--取值范围1-255*/ 
    UCHAR  ucPad;               /*填充 --*/
}RIPNG_PROC_INFO_S;

/*STRUCT<用于查询RIPNG实例的过滤信息>*/ 
typedef struct tagRIPNG_PROC_FILTER
{
    USHORT usProcId;            /*RIPNG的实例号--取值范围：[0,0xffff]*/
    UCHAR  aucPad[2];           /*填充 --*/
}RIPNG_PROC_FILTER_S;


/*STRUCT<附加路由权值的配置结构>*/
typedef struct  tagRIPNG_CFG_METRIC 
{ 
    BOOL_T bUndoConfig;    /*RIPNG_CFG_ADD - 配置
                             RIPNG_CFG_DEL  - 删除*/
    UCHAR  ucMetricVal;                     /*附加路由权值,默认值为0,--取值范围1-15*/
    UCHAR  aucPad;                          /*填充 --*/
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1];/*指定接口的接口名，最大长度47字节。--取值范围：非空*/
}RIPNG_CFG_METRIC_S;

/*STRUCT<RIPNG的接口配置>*/
typedef struct tagRIPNG_IFCFG
{
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - 配置
                           RIPNG_CFG_DEL  - 删除*/
    UCHAR  aucPad[2];                       /*填充 --*/
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1];/*RIPNG的接口名，最大47字节--取值范围：非空*/
}RIPNG_IFCFG_S;

/*STRUCT<路由的默认cost值配置结构>*/
typedef struct tagRIPNG_CFG_DEFCOST
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - 配置
                           RIPNG_CFG_DEL  - 删除*/ 
    USHORT usDefRtMetric;                    /*默认路由的Metric值,默认0(表示该接口不发送RIPng 默认路由),--取值范围1-15*/
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1]; /*指定接口的接口名，最大长度47字节。--取值范围：非空*/
}RIPNG_CFG_DEFCOST_S; 


/*STRUCT<RIP的路由表项>*/
typedef struct tagRIPNG_ROUTE
{ 
    UCHAR  ucDestAddr[RIPNG_IPV6_ADDRESS_WORD_LEN];   /*目的地址--取值范围：非空*/
    ULONG  ulPrefixLen;                               /*前缀长度，--取值0-128*/
    UCHAR  ucNextHopAddr[RIPNG_IPV6_ADDRESS_WORD_LEN];/*下一跳或网关地址--取值范围：非空*/
    USHORT usAge;                                     /*老化时间--取值范围：[0,0xffff]*/
    USHORT usMetric;                                  /*度量值--取值范围：[0,0xffff]*/
    USHORT usRouteTag;                                /*路由标记--取值范围：[0,0xffff]*/
    USHORT usRouteType;                               /*路由类型:接口类型、协议、RPI--取值范围：[0,0xffff]*/    
    ULONG ulTimerType; /*用于描述usAge字段，当前生效的定时器类型
                                    0:老化定时器
                                    1:垃圾回收定时器*/
}RIPNG_ROUTE_S; 

/*STRUCT<用于查询邻居的过滤信息>*/
typedef struct tagRIPNG_ROUTE_FILTER
{
    USHORT usProcId;            /*RIPNG的实例号--取值范围：[0,0xffff]*/
    UCHAR  aucPad[2];           /*填充 --*/
} RIPNG_ROUTE_FILTER_S; 

/*STRUCT<RIP的一组路由:所有目的地址和下一跳相同的路由>*/
typedef struct tagRIPNG_ROUTE_GROUP
{ 
    USHORT usProcessId;                                     /*RIPNG的实例号--取值范围：[1,0xffff]*/
    USHORT usRouteNum;                                      /*路由数目 --取值范围：[0,0xffff]*/
    RIPNG_ROUTE_S stRipngRoutes[RIPNG_MAX_EQUAL_ROUTE_NUM]; /*路由具体信息--取值范围：非空*/
} RIPNG_ROUTE_GROUP_S;

/*STRUCT<用于查询邻居的过滤信息>*/
typedef struct tagRIPNG_NBR_FILTER
{
    USHORT usProcId;        /*RIPNG的实例号--取值范围：[0,0xffff]*/
    UCHAR  aucPad[2];       /*填充 --*/
} RIPNG_NBR_FILTER_S; 

/*STRUCT<RIPNG的邻居信息>*/
typedef struct tagRIPNG_NBR_INFO 
{   
    ULONG  ulAddressType;                           /*地址类型 --取值范围：0x00-0x12*/
    ULONG  ulAddressLen;                            /*地址长度,--取值范围：RIP为4，RIPNG为16*/
    UCHAR  aucAddress[RIPNG_IPV6_ADDRESS_WORD_LEN]; /*RIPNG邻居的地址--取值范围：非空*/
    ULONG  ulVersion;                               /*版本号--取值范围：1-2*/
    ULONG  ulRcvBadPackets;                         /*接收错误的报文个数--取值范围：[0,0xffffffff]*/
    ULONG  ulRcvBadRoutes;                          /*接收错误的路由个数--取值范围：[0,0xffffffff]*/
    USHORT usProcId;                                /*RIPNG的实例号--取值范围：[0,0xffff]*/
    UCHAR  ucPad[2];                               /*填充字段*/  
} RIPNG_NBR_INFO_S; 


/*STRUCT<用于查询接口配置的过滤信息>*/
typedef struct tagRIPNG_INTF_FILTER
{
    USHORT usProcId;        /*RIPNG的实例号--取值范围：[0,0xffff]*/
    UCHAR  aucPad[2];       /*填充 --*/
} RIPNG_INTF_FILTER_S;

/*STRUCT<接口查询信息结构>*/
typedef struct tagRIPNG_INTF_INFO
{  
    USHORT usProcId;        /*RIPNG的实例号--取值范围：[0,0xffff]*/
    UCHAR  ucSend;          /*发送状态--取值范围：[0,1]*/
    UCHAR  ucReceive;       /*接收状态--取值范围：[0,1]*/
    ULONG  ulDefaultMetric; /*默认路由度量值--取值范围：[0,16]*/
    ULONG  ulIfIndex;       /*接口索引值--取值范围：非0的32为整型*/
    UCHAR  ucSplitHorizon;  /*是否配置水平分割--取值范围：[0,1]*/
    UCHAR  ucPoisonReverse; /*是否配置毒性逆转--取值范围：[0,1]*/
    UCHAR  ucMetricIn;      /*附加路由权值 输入--取值范围：[0,16]*/
    UCHAR  ucMetricOut;     /*附加路由权值 输出--取值范围：[0,16]*/ 
} RIPNG_INTF_INFO_S;

/*STRUCT<用于查询接口扩展配置的过滤信息>*/
typedef struct tagRIPNG_INTF_EX_FILTER
{
    ULONG ulIfIndex;        /*接口索引值--取值范围：非0的32为整型*/
} RIPNG_INTF_EX_FILTER_S; 


/*STRUCT<一个接口只能配置一个RIP>*/
typedef struct tagRIPNG_INTF_EX_INFO 
{  
    ULONG  ulIfIndex;      /*接口索引值--取值范围：非0的32为整型*/  
    USHORT usFlag;         /*接口属性配置生效标志位--取值范围：[0,1]*/  
    USHORT usDefRtMetric;  /*默认路由的Metric值,默认0,--取值范围1-15*/
    UCHAR  ucSplitHorizon; /*是否配置水平分割--取值范围：[0,1]*/
    UCHAR  ucPoisonReverse;/*是否配置毒性逆转--取值范围：[0,1]*/
    UCHAR  ucMetricIn;     /*附加路由权值 输入--取值范围：[0,16]*/
    UCHAR  ucMetricOut;    /*附加路由权值 输出--取值范围：[0,16]*/ 
} RIPNG_INTF_EX_INFO_S;

/*STRUCT<RIPNG过滤接口配置信息查询条件>*/
typedef struct tagRIPNG_CFG_FILTER
{
    USHORT usProcessId;                     /*进程ID
                                              范围：0~0xffff。
                                              0：存在的所有进程；
                                              1～0xffff：指定的RIPNG进程号。*/
    UCHAR  ucPadding[2];                    /*填充 --*/
    ULONG  ulIfIndex;                       /*接口索引，为0表示不指定接口查询--取值范围：32为整型*/
} RIPNG_CFG_FILTER_S;

/*STRUCT<ipv6地址结构>*/
typedef struct tagRIPNG_INET6_ADDRESS
{
    UCHAR ucAddress[RIPNG_IPV6_ADDRESS_WORD_LEN]; /*IP6地址--取值范围：非空*/
    UCHAR ucPrefixLen;                            /*IP6掩码长度--取值范围：[1,128]*/
    UCHAR ucPad[3];                               /*填充 --*/  
}RIPNG_INET6_ADDRESS_S;

/*STRUCT<RIPNG接口配置信息查询>*/
typedef struct tagRIPNG_SHOWCFGINTF
{
    CHAR   szIfName[MAX_IF_NAME_LENGTH + 1];      /*接口名--取值范围：非空*/
    RIPNG_INET6_ADDRESS_S ulIpAddr;               /*IP6地址--取值范围：非空*/
    ULONG  ulProcessId;                           /*进程ID--取值范围：[0,0xffff]*/
    ULONG  ulIfIndex;                             /*接口索引--取值范围：非0的32为整型*/
    ULONG  ulDefaultMetric;                       /*默认路由度量值--取值范围：[0,16]*/
}RIPNG_SHOWCFGINTF_S;

/*STRUCT<RIPNG引入接口配置信息查询条件>*/
typedef struct tagRIPng_RPM_PLCYREDIS
{
    UCHAR  ucProtoType;                     /*    
                                                        #define RM_PROTO_CONNECTED  0x2  
                                                        #define RM_PROTO_STATIC     0x3
                                                        #define RM_PROTO_RIPNG      0x18
                                                        #define RM_PROTO_OSPF6      0x1D
                                                        协议ID类型*/
    UCHAR  ucPadding;                       /*填充 --*/
    USHORT usProcessId;                     /*被引入端的进程ID--取值范围：[0,0xffff]*/
    ULONG  ulMetricVal;                      /*Metric值，默认值1,0 - 不配置Metric值--取值范围：[0,16]*/
} RIPNG_RPM_PLCYREDIST_S;

/*STRUCT<RIPNG过滤接口配置信息查询条件>*/
typedef struct tagRIPng_RPM_PLCYDIST
{
    USHORT usProcId;                      /*进程ID: --取值范围1~65535*/
    UCHAR  ucProtocolId;                  /* 引入的源协议类型
                                                       #define RM_PROTO_CONNECTED  0x2  
                                                       #define RM_PROTO_STATIC     0x3
                                                       #define RM_PROTO_RIPNG      0x18
                                                       #define RM_PROTO_OSPF6      0x1D
                                                       Protocol ID  对于接收过滤来说，
                                                      该字段无效*/
    UCHAR  ucPadding;                     /*填充 --*/  
    union
    {
        ULONG ulAclNum;                   /*ACL6规则组号--取值范围:2000~2999*/
    } stFltrName;
} RIPNG_RPM_PLCYDIST_S;


/*STRUCT<RIPNG发布过滤接口配置信息查询条件>*/
typedef struct tagRIPng_CFGDISTRIBUTE
{
    USHORT bNoFlag;                         /*RIPNG_CFG_ADD - 配置
                                              RIPNG_CFG_DEL - 删除*/
    USHORT usProcId;                        /*RIPNG的实例号取值范围：[1,0xffff]*/
    RIPNG_RPM_PLCYDIST_S stPolicyDist;      /*引入/接收过滤--取值范围:非空*/
} RIPNG_CFGDISTRIBUTE_S;

/*STRUCT<RIPNG 路由引入策略配置结构>*/
typedef struct tagRIPNG_CFG_REDIST
{
    BOOL_T bNoFlag;     /*RIPNG_CFG_ADD - 配置
                          RIPNG_CFG_DEL  - 删除*/
    USHORT usProcId;                        /*RIPNG的实例号取值范围：[1,0xffff]*/ 
    RIPNG_RPM_PLCYREDIST_S stPolicyRedist;  /*引入/接收过滤--取值范围:非空*/
}RIPNG_CFG_REDIST_S;



/*STRUCT<配置 RIPng 的接收过滤或者发布过滤>*/
typedef struct tagRIPng_Cfg_Filter_Info
{
    USHORT bNoFlag;                 /*RIPNG_CFG_ADD - 配置
                                      RIPNG_CFG_DEL - 删除*/
    USHORT usProcId;               /*RIPNG的实例号取值范围：[1,0xffff]*/
    union
    {
        ULONG ulAclNum;            /*ACL6规则组号--取值范围:2000~2999*/
    } stFltrName;   
} RIPNG_CFG_FILTER_INFO_S;


/*STRUCT<用于RIPng 过滤查询的条件>*/
typedef struct tagRIPng_Plcy_Filter
{
    USHORT usProcId;                 /*进程ID
                                              范围：0~65535。
                                              0：查询所有进程；
                                              1～0xffff：指定的RIPng进程号。*/
    UCHAR  ucPadding[2];             /*填充 --*/ 
} RIPNG_PLCY_FILTER_S;

/*STRUCT<RIPng 引入策略的查询信息>*/
typedef struct tagRIPng_Show_Redist
{
    ULONG  ulProcId;                        /*RIPNG的实例号取值范围：[1,0xffff]*/
    RIPNG_RPM_PLCYREDIST_S stReDist;        /*引入/接收过滤--取值范围:非空*/
}RIPNG_SHOW_REDIST_S;  


/*STRUCT<RIPng 引入过滤的查询信息>*/
typedef struct tagRIPng_SHOW_EXPORT_FILTER_S
{
    ULONG  ulProcId;                        /*RIPNG的实例号取值范围：[1,0xffff]*/
    RIPNG_RPM_PLCYDIST_S stPlcyDist;        /*引入/接收过滤--取值范围:非空*/
}RIPNG_SHOW_EXPORT_FILTER_S; 


/*STRUCT<RIPng 的接收过滤查询信息>*/
typedef struct tagRIPng_Show_Import_Filter
{
    ULONG  ulProcId;                        /*进程ID: --取值范围1~65535*/
    union
    {
        ULONG ulAclNum;                     /*ACL6规则组号--取值范围:2000~2999*/
    } stFltrName;   
}RIPNG_SHOW_IMPORT_FILTER_S; 


/*STRUCT<RIPng 的接收过滤查询信息>*/
typedef struct tagRIPng_Show_Distribute_Filter
{
    ULONG  ulProcId;                      /*RIPNG的实例号取值范围：[1,0xffff]*/
    union
    {
        ULONG ulAclNum;                   /*ACL6规则组号--取值范围:2000~2999*/
    } stFltrName;   
}RIPNG_SHOW_DISTRIBUTE_FILTER_S; 


/*STRUCT<配置RIPNG进程的代价>*/
typedef struct tagRIPNG_CFGPREFERENCE 
{ 
    USHORT bDefFlag;                               /*RIPNG_CFG_ADD - 配置
                                                     RIPNG_CFG_DEL - 恢复默认值*/
    UCHAR  ucPreference;                            /*代价，默认值120--取值范围:1~255*/
    UCHAR  ucPadding;                               /*填充--*/
    CHAR   szVrfName[RIPNG_MAX_VRF_NAME_LENGTH + 1];/*VRF名字--取值范围:非空*/
}RIPNG_CFGPREFERENCE_S;

/*STRUCT<获取RIPNG进程的代价>*/
typedef struct tagRIPNG_PREFERENCE_SHOW
{
    ULONG  ulVrfIndex;                      /*VRF索引--取值范围:非0*/
    UCHAR  ucPreference;                    /*代价，--取值范围:1~255*/
    UCHAR  ucPadding[3];                    /*填充--*/  
}RIPNG_PREFERENCE_SHOW_S;




/*******************************************************************************
*    Func Name: RIPng_CFG_Proc
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 配置RIPNG 进程
*  Description: 配置RIPNG 进程,支持创建的进程规格为8
*        Input: RIPNG_CFG_PROC_S *pstCfgInfo:进程配置信息<非空>
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_Proc(RIPNG_CFG_PROC_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_Timers
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 配置RIPNG 定时器值
*  Description: 配置RIPNG 定时器值,支持对更新定时器,老化定时器和垃圾收集定时器的配置
*        Input: RIPNG_CFG_TIMERS_S *pstCfgInfo:定时器配置信息
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_Timers(RIPNG_CFG_TIMERS_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_Enable
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 接口上使能RIPng
*  Description: 接口上使能RIPng,同一个接口上只支持使能绑定同一个进程，不同接口上支持使能绑定相同进程
*        Input: RIPNG_CFG_ENABLE_S *pstCfgInfo:绑定配置信息
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_Enable(RIPNG_CFG_ENABLE_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_MaxLoadBalance
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 配置/恢复RIPng最大平衡路由数量
*  Description: 配置/恢复RIPng最大平衡路由数量，该值在RIPng路由下发RTM时生效
*        Input: RIPNG_CFG_MAXLOAD_S *pstCfgInfo:平衡路由数量配置信息
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_MaxLoadBalance(RIPNG_CFG_MAXLOAD_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Proc_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取RIPng实例信息查询的句柄
*  Description: 获取RIPng实例信息查询的句柄
*        Input: RIPNG_PROC_FILTER_S *pstDspProcFlt:过滤条件<非空>
*       Output: ULONG *pulSessionId:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_Proc_GetFirst
*               RIPng_CMM_Proc_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CMM_Proc_Open (ULONG *pulSessionId, RIPNG_PROC_FILTER_S *pstDspProcFlt);

/*******************************************************************************
*    Func Name: RIPng_CMM_Handle_Close
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 关闭RIPng信息查询的句柄
*  Description: 关闭RIPng信息查询的句柄
*        Input: ULONG ulSessionId:句柄<非空>
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CMM_Handle_Close (ULONG ulSessionId);

/*******************************************************************************
*    Func Name: RIPng_CMM_Proc_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取第一个RIPng实例信息
*  Description: 获取第一个RIPng实例信息
*        Input: ULONG ulSessionId:句柄<非空>
*       Output: RIPNG_PROC_INFO_S *pstProcInfo:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_Proc_Open
*               RIPng_CMM_Proc_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CMM_Proc_GetFirst (ULONG ulSessionId, RIPNG_PROC_INFO_S *pstProcInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Proc_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 
*  Description: 获取下一个RIPng实例信息
*        Input: ULONG ulSessionId:
*       Output: RIPNG_PROC_INFO_S *pstProcInfo:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_Proc_Open
*               RIPng_CMM_Proc_GetFirst
*               RIPng_CMM_Handle_Close 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CMM_Proc_GetNext (ULONG ulSessionId, RIPNG_PROC_INFO_S *pstProcInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowProcInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 显示指定RIPng 实例信息
*  Description: 显示指定RIPng 实例信息 
*        Input: USHORT usProcId:
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID RIPng_ShowProcInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CFG_MetricIn
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 配置RIPng接收附加度量值
*  Description: 附加路由度量值是在RIPNG路由原来度量值的基础上所增加的度量值（跳数），
*               它并不直接改变路由表中RIPNG路由的度量值。接收附加度量值是在接收
*               RIPNG路由时增加的一个权值。默认接收附加度量值为0，取值范围为1~15，
*               如果加权后度量值超过16，则设置为16。
*        Input: RIPNG_CFG_METRIC_S *pstCfgInfo:接收附加度量值结构<非空>
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 配置时接口必须存在
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_MetricIn(RIPNG_CFG_METRIC_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_MetricOut
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 配置RIPng发送附加度量值
*  Description: 附加路由度量值是在RIPNG路由原来度量值的基础上所增加的度量值（跳数），
*               它并不直接改变路由表中RIPNG路由的度量值。发送附加度量值是在发布
*               RIPNG路由时增加的一个权值。默认发送附加度量值为0，取值范围为1~15，
*               如果加权后度量值超过16，则设置为16。
*        Input: RIPNG_CFG_METRIC_S *pstCfgInfo:发送附加度量值结构<非空>
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 配置时接口必须存在
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_MetricOut(RIPNG_CFG_METRIC_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_PoisonReverse
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 配置RIPng毒性逆转
*  Description: 毒性逆转是RIPNG从某个接口学到的路由，将该路由的Cost变成16，
*               然后再从该接口发布出去，可以清除对方路由表中的无用信息，默认不启动该功能。
*               如果同时设置水平分割和毒性逆转功能，仅毒性逆转功能生效。  
*        Input: RIPNG_IFCFG_S *pstCfgInfo:毒性逆转配置结构<非空>
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 配置时接口必须存在
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CFG_PoisonReverse(RIPNG_IFCFG_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_SplitHorizon
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 配置RIPng水平分割
*  Description: 水平分割则是RIPNG从某个接口学到的路由不再从该接口发布给其他路由器，
*               这在某种程度上避免了路由循环。但在特殊情况下，必须禁止水平分割功能，
*               以牺牲效率来换取路由的正确发布。默认情况下启动该功能。如果同时设置
*               水平分割和毒性逆转功能，仅毒性逆转功能生效。在点对点链路上禁止水平
*               分割功能是无效的。
*        Input: RIPNG_IFCFG_S *pstCfgInfo:水平分割配置结构<非空>
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 配置时接口必须存在
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CFG_SplitHorizon(RIPNG_IFCFG_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_DefaultRouteOrig
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 配置默认路由度量值
*  Description: 默认值为0，即不向外发布到本端的默认路由；可配置范围:1~15，一旦配置
*               后即向外发布到本端的默认路由
*        Input: RIPNG_CFG_DEFCOST_S *pstCfgInfo:默认路由度量值配置结构<非空>
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 配置时接口必须存在
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CFG_DefaultRouteOrig(RIPNG_CFG_DEFCOST_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Route_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取RIPng路由信息查询的句柄
*  Description: 获取RIPng路由信息查询的句柄
*        Input: RIPNG_ROUTE_FILTER_S* pstDspRouteFlt:
*       Output: ULONG *pulHandle:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Route_GetFirst
*                 RIPng_CMM_Route_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Route_Open(ULONG *pulHandle, RIPNG_ROUTE_FILTER_S* pstDspRouteFlt);

/*******************************************************************************
*    Func Name: RIPng_CMM_Route_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取第一组RIPng路由信息
*  Description: 获取第一组RIPng路由信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_ROUTE_GROUP_S *pstRouteInfo:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Route_Open
*                 RIPng_CMM_Route_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Route_GetFirst(ULONG ulHandle, RIPNG_ROUTE_GROUP_S *pstRouteInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Route_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取下一组RIPng路由信息
*  Description: 获取下一组RIPng路由信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_ROUTE_GROUP_S *pstRouteInfo:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Route_Open
*                 RIPng_CMM_Route_GetFirst
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Route_GetNext(ULONG ulHandle, RIPNG_ROUTE_GROUP_S *pstRouteInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowRouteInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 显示RIPng的路由信息
*  Description: 显示RIPng的路由信息
*        Input: USHORT usProcId:
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID RIPng_ShowRouteInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CMM_Nbr_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取RIPng邻居信息查询的句柄
*  Description: 获取RIPng邻居信息查询的句柄
*        Input: RIPNG_NBR_FILTER_S* pstDspNbrFlt:
*       Output: ULONG *pulSessionId:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Nbr_GetFirst
*                 RIPng_CMM_Nbr_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Nbr_Open(ULONG *pulSessionId, RIPNG_NBR_FILTER_S* pstDspNbrFlt);


/*******************************************************************************
*    Func Name: RIPng_CMM_Nbr_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取第一条RIPng邻居信息
*  Description: 获取第一条RIPng邻居信息
*        Input: ULONG ulSessionId:
*       Output: RIPNG_NBR_INFO_S *pstNbrInfo:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Nbr_Open
*                 RIPng_CMM_Nbr_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Nbr_GetFirst(ULONG ulSessionId, RIPNG_NBR_INFO_S *pstNbrInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Nbr_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取下一条RIPng邻居信息
*  Description: 获取下一条RIPng邻居信息
*        Input: ULONG ulSessionId:
*       Output: RIPNG_NBR_INFO_S *pstNbrInfo:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Nbr_Open
*                 RIPng_CMM_Nbr_GetFirst
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Nbr_GetNext(ULONG ulSessionId, RIPNG_NBR_INFO_S *pstNbrInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowNbrInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 显示指定RIPng实例的邻居信息
*  Description: 显示指定RIPng实例的邻居信息
*        Input: USHORT usProcId:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID RIPng_ShowNbrInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CMM_Intf_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取RIPng接口配置信息查询的句柄
*  Description: 获取RIPng接口配置信息查询的句柄
*        Input: RIPNG_INTF_FILTER_S* pstDspIntfFlt:
*       Output: ULONG *pulSessionId:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Intf_GetFirst
*                 RIPng_CMM_Intf_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Intf_Open(ULONG *pulSessionId, RIPNG_INTF_FILTER_S* pstDspIntfFlt);

/*******************************************************************************
*    Func Name: RIPng_CMM_Intf_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取第一条RIPng接口配置信息
*  Description: 获取第一条RIPng接口配置信息
*        Input: ULONG ulSessionId:
*       Output: RIPNG_INTF_INFO_S *pstIntfInfo:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Intf_Open
*                 RIPng_CMM_Intf_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Intf_GetFirst(ULONG ulSessionId, RIPNG_INTF_INFO_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Intf_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取下一条RIPng接口配置信息
*  Description: 获取下一条RIPng接口配置信息
*        Input: ULONG ulSessionId:
*       Output: RIPNG_INTF_INFO_S *pstIntfInfo:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Intf_Open
*                 RIPng_CMM_Intf_GetFirst
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Intf_GetNext(ULONG ulSessionId, RIPNG_INTF_INFO_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowIntfInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 显示指定RIPng实例及指定接口的接口配置信息
*  Description: 显示指定RIPng实例及指定接口的接口配置信息
*        Input: USHORT usProcId:
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID  RIPng_ShowIntfInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CMM_IntfEx_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取RIPng接口扩展配置信息查询的句柄
*  Description: 获取RIPng接口扩展配置信息查询的句柄
*        Input: RIPNG_INTF_EX_FILTER_S* pstDspIntfExFlt:过滤条件<为空表示不指定过滤>
*       Output: ULONG *pulHandle:查询句柄
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_IntfEx_GetFirst
*               RIPng_CMM_IntfEx_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_IntfEx_Open(ULONG *pulHandle, RIPNG_INTF_EX_FILTER_S* pstDspIntfExFlt);

/*******************************************************************************
*    Func Name: RIPng_CMM_IntfEx_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取第一条RIPng接口扩展配置信息
*  Description: 获取第一条RIPng接口扩展配置信息
*        Input: ULONG ulHandle:查询句柄<非空>
*       Output: RIPNG_INTF_EX_INFO_S *pstIntfExInfo:接口扩展配置信息<非空>
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_IntfEx_Open
*               RIPng_CMM_IntfEx_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_IntfEx_GetFirst(ULONG ulHandle, RIPNG_INTF_EX_INFO_S *pstIntfExInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_IntfEx_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 获取下一条RIPng接口扩展配置信息
*  Description: 获取下一条RIPng接口扩展配置信息
*        Input: ULONG ulHandle:查询句柄<非空>
*       Output: RIPNG_INTF_EX_INFO_S *pstIntfExInfo:接口扩展配置信息<非空>
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_IntfEx_GetFirst
*               RIPng_CMM_IntfEx_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_IntfEx_GetNext(ULONG ulHandle, RIPNG_INTF_EX_INFO_S *pstIntfExInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowIntfExInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 显示RIPng指定接口的接口扩展配置信息
*  Description: 显示RIPng指定接口的接口扩展配置信息
*        Input: UCHAR *pszIfName:接口名<非空>
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID RIPng_ShowIntfExInfo(CHAR *pszIfName);

/*******************************************************************************
*    Func Name: RIPng_Intermediate_Hook_Register
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: RIPng报文收发钩子注册函数
*  Description: RIPng报文收发钩子注册函数 
*        Input: ULONG ulDirection:RIPng的报文收发方向
*               RIPNG_PACKET_HOOK_FUNC pfRipngFwHookFunc:钩子处理函数
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_Intermediate_Hook_Register(ULONG ulDirection, RIPNG_PACKET_HOOK_FUNC pfRipngFwHookFunc);

/*******************************************************************************
*    Func Name: RIPng_Intermediate_UnHook_Register
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: RIPng报文收发钩子解注册函数
*  Description: RIPng报文收发钩子解注册函数
*        Input: ULONG ulDirection:RIPng的报文收发方向
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_Intermediate_UnHook_Register(ULONG ulDirection);

/*******************************************************************************
*    Func Name: RIPng_CMM_CfgIntf_Open
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: 获取RIPng接口配置信息的句柄
*  Description: 返回一个Handle，用于打开下一个结点获取接口配置信息
*        Input: RIPNG_CFG_FILTER_S *pstFilterIn:进程ID和接口索引可以组合查询
*       Output: ULONG *pulHandle:Handle
*       Return: 成功返回VOS_OK
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_CfgIntf_GetFirst
*               RIPng_CMM_CfgIntf_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
extern  ULONG RIPng_CMM_CfgIntf_Open(ULONG *pulHandle, RIPNG_CFG_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: RIPng_CMM_CfgIntf_GetFirst
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: 获取一个接口配置信息
*  Description: 获取一个接口配置信息
*        Input: ULONG ulHandle:Handle
*       Output: RIPNG_SHOWCFGINTF_S *pstIntfIn:接口配置信息
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_CfgIntf_Open
*               RIPng_CMM_CfgIntf_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
extern  ULONG RIPng_CMM_CfgIntf_GetFirst(ULONG ulHandle,RIPNG_SHOWCFGINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: RIPng_CMM_CfgIntf_GetNext
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: 获取下一个接口配置信息
*  Description: 获取下一个接口配置信息
*        Input: ULONG ulHandle:Handle
*       Output: RIPNG_SHOWCFGINTF_S *pstIntfIn:接口配置信息
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: RIPng_CMM_CfgIntf_Open
*               RIPng_CMM_CfgIntf_GetFirst
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
extern  ULONG RIPng_CMM_CfgIntf_GetNext(ULONG ulHandle,RIPNG_SHOWCFGINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: RIPng_ShowCfgIntfInfo
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: 显示用户配置的接口信息
*  Description: 显示用户配置的接口信息
*        Input: USHORT usProcId:进程ID,范围：0~0xffff。
*               CHAR *szIfName:接口名
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
extern  VOID RIPng_ShowCfgIntfInfo(USHORT usProcId,CHAR *szIfName);

/*******************************************************************************
*    Func Name: RIPng_CFG_Redistribute
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 配置RIPng 引入策略配置
*  Description: RIPng 引入策略配置,可引入的类型有：直连路由、静态路由、OSPFv3路由以及RIPng路由
*        Input: RIPNG_CFG_REDIST_S* pstRedistIn: 传入的配置信息
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CFG_Redistribute(RIPNG_CFG_REDIST_S* pstRedistIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_Redist_Open
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: RIPng 引入策略配置查询的Open操作
*  Description: RIPng 引入策略配置查询的Open操作，usProcId为0代表查询所有
*        Input: RIPNG_PLCY_FILTER_S *pstFilterIn: 查询的过滤条件
*       Output: ULONG *pulHandle:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Redist_GetFirst
*                      RIPng_CMM_Redist_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_Redist_Open(ULONG *pulHandle, RIPNG_PLCY_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_Redist_GetFirst
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 引入策略配置的第一条信息
*  Description: 查询RIPng 引入策略配置的第一条信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_REDIST_S *pstRedistOut:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Redist_Open
*                      RIPng_CMM_Redist_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_Redist_GetFirst(ULONG ulHandle, RIPNG_SHOW_REDIST_S *pstRedistOut);

/*******************************************************************************
*    Func Name: RIPng_CMM_Redist_GetNext
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 引入策略配置的下一条信息
*  Description: 查询RIPng 引入策略配置的下一条信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_REDIST_S *pstRedistOut:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_Redist_Open
*                      RIPng_CMM_Redist_GetFirst
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_Redist_GetNext (ULONG ulHandle, RIPNG_SHOW_REDIST_S *pstRedistOut);

/*******************************************************************************
*    Func Name: RIPng_ShowRedistInfo
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 显示指定条件的引入策略查询信息
*  Description: 显示指定条件的引入策略查询信息
*        Input: USHORT usProcId:指定的RIPng 进程id, 0 表示查询所有
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
VOID RIPng_ShowRedistInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CFG_RouteExportFilter
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 配置RIPng 的引入过滤，
*  Description: 本函数用于RIPng的路由引入策略的ACL过滤配置，先进行RIPng 路由引入的策略配置后，再根据该策略配置过滤条件。
*        Input: RIPNG_CFGDISTRIBUTE_S* pstExportFilterIn:
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CFG_RouteExportFilter(RIPNG_CFGDISTRIBUTE_S* pstExportFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_ExportFilter_Open
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: RIPng 引入过滤的open操作
*  Description: RIPng 引入过滤的open操作，usProcId为0代表查询所有
*        Input: RIPNG_PLCY_FILTER_S *pstFilterIn:
*       Output: ULONG *pulHandle:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_ExportFilter_GetFirst
*                      RIPng_CMM_ExportFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ExportFilter_Open(ULONG *pulHandle, RIPNG_PLCY_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_ExportFilter_GetFirst
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 的第一条引入信息
*  Description: 查询RIPng 的第一条引入信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_EXPORT_FILTER_S *pstExportInfoOut:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_ExportFilter_Open
*                      RIPng_CMM_ExportFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ExportFilter_GetFirst(ULONG ulHandle, RIPNG_SHOW_EXPORT_FILTER_S *pstExportInfoOut);

/*******************************************************************************
*    Func Name: RIPng_CMM_ExportFilter_GetNext
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 的下一条引入信息
*  Description: 查询RIPng 的下一条引入信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_EXPORT_FILTER_S *pstExportInfoOut:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_ExportFilter_Open
*                      RIPng_CMM_ExportFilter_GetFirst
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ExportFilter_GetNext (ULONG ulHandle, RIPNG_SHOW_EXPORT_FILTER_S *pstExportInfoOut);

/*******************************************************************************
*    Func Name: RIPng_ShowExportFilterInfo
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询指定RIPng 的引入过滤信息
*  Description: 查询指定RIPng 的引入过滤信息
*        Input: USHORT usProcId:指定的RIPng 进程id, 0 表示查询所有
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
VOID RIPng_ShowExportFilterInfo(USHORT usProcId);


/*******************************************************************************
*    Func Name: RIPng_CFG_RouteImportFilter
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: RIPng接收过滤
*  Description: RIPng接收过滤,对接收到的路由进行RIPng的接收过滤配置
*        Input: RIPNG_CFG_FILTER_INFO_S* pstFilterCfg:
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CFG_RouteImportFilter(RIPNG_CFG_FILTER_INFO_S* pstImportFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_ImportFilter_Open
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: RIPng 接收过滤的open 操作
*  Description: RIPng 接收过滤的open 操作，usProcId为0代表查询所有
*        Input: RIPNG_PLCY_FILTER_S *pstFilterIn:
*       Output: ULONG *pulHandle:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_ImportFilter_GetFirst
*                      RIPng_CMM_ImportFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ImportFilter_Open(ULONG *pulHandle, RIPNG_PLCY_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_ImportFilter_GetFirst
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 接收过滤的第一条信息
*  Description: 查询RIPng 接收过滤的第一条信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_ImportFilter_Open
*                      RIPng_CMM_ImportFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ImportFilter_GetFirst(ULONG ulHandle, RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut);

/*******************************************************************************
*    Func Name: RIPng_CMM_ImportFilter_GetNext
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 接收过滤的下一条信息
*  Description: 查询RIPng 接收过滤的下一条信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_ImportFilter_Open
*                      RIPng_CMM_ImportFilter_GetFirst
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ImportFilter_GetNext (ULONG ulHandle, RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut);

/*******************************************************************************
*    Func Name: RIPng_ShowImportFilterInfo
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 的接收过滤信息
*  Description: 查询RIPng 的接收过滤信息
*        Input: USHORT usProcId:指定的RIPng 进程id, 0 表示查询所有
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
VOID RIPng_ShowImportFilterInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CFG_RouteDistributeFilter
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 配置RIPng发布过滤
*  Description: 配置RIPng发布过滤
*        Input: RIPNG_CFG_FILTER_INFO_S* pstDistributeFilterIn:
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CFG_RouteDistributeFilter(RIPNG_CFG_FILTER_INFO_S* pstDistributeFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_DistributeFilter_Open
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询 RIPng 发布过滤的open 操作
*  Description: 查询 RIPng 发布过滤的open 操作，usProcId为0代表查询所有
*        Input: RIPNG_PLCY_FILTER_S *pstFilterIn:
*       Output: ULONG *pulHandle:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_DistributeFilter_GetFirst
*                      RIPng_CMM_DistributeFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_DistributeFilter_Open(ULONG *pulHandle, RIPNG_PLCY_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: RIPng_CMM_DistributeFilter_GetFirst
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 的第一条发布过滤信息
*  Description: 查询RIPng 的第一条发布过滤信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_DistributeFilter_Open
*                      RIPng_CMM_DistributeFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_DistributeFilter_GetFirst(ULONG ulHandle, RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut);

/*******************************************************************************
*    Func Name: RIPng_CMM_DistributeFilter_GetNext
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询RIPng 的下一条发布过滤信息
*  Description: 查询RIPng 的下一条发布过滤信息
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut:
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码
*      Caution: 
*      Reference: RIPng_CMM_DistributeFilter_Open
*                      RIPng_CMM_DistributeFilter_GetFirst
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_DistributeFilter_GetNext (ULONG ulHandle, RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut);

/*******************************************************************************
*    Func Name: RIPng_ShowDistributeFilterInfo
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: 查询指定RIPng 的发布过滤信息
*  Description: 查询指定RIPng 的发布过滤信息
*        Input: USHORT usProcId:指定的RIPng 进程id, 0 表示查询所有
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
VOID RIPng_ShowDistributeFilterInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CFG_Preference
* Date Created: 2009-10-15
*       Author: hanna55555
*      Purpose: 配置/恢复RIPNG路由优先级
*  Description: 配置/恢复RIPNG路由优先级
*        Input: RIPNG_CFGPREFERENCE_S* pstPrefIn:RIPNG路由优先级配置信息
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码 
*      Caution: 该函数针对指定VRF全局有效,不是针对进程的。
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   hanna55555              Create
*
*******************************************************************************/
extern  ULONG RIPng_CFG_Preference(RIPNG_CFGPREFERENCE_S* pstPrefIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_Pref_GetByVrfName
* Date Created: 2009-10-15
*       Author: hanna55555
*      Purpose: 获取RIPNG路由优先级
*  Description: 获取RIPNG路由优先级
*        Input: CHAR *pszVrfName:VRF名字
*               RIPNG_PREFERENCE_SHOW_S *pstPrefIn:RIPNG路由优先级获取信息
*       Output: 
*       Return: 成功返回RIP_SUCCESS
*               失败返回错误码 
*      Caution: 该函数针对指定VRF全局有效,不是针对进程的。 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   hanna55555              Create
*
*******************************************************************************/
extern  ULONG RIPng_CMM_Pref_GetByVrfName(CHAR *pszVrfName,RIPNG_PREFERENCE_SHOW_S *pstPrefIn);

/*******************************************************************************
*    Func Name: RIPng_ShowPreferenceInfo
* Date Created: 2009-10-15
*       Author: hanna55555
*      Purpose: 显示RIPNG路由优先级
*  Description: 显示RIPNG路由优先级
*        Input: CHAR *pszVrfName:VRF名字
*       Output: 
*       Return: VOID
*      Caution: 该函数针对指定VRF全局有效,不是针对进程的。
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   hanna55555              Create
*
*******************************************************************************/
extern  VOID RIPng_ShowPreferenceInfo(CHAR *pszVrfName);


#ifdef  __cplusplus
}
#endif

#endif 


