/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_cfg_api.h
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
#ifndef _OSPF6_CFG_API_H_
#define _OSPF6_CFG_API_H_
    
#ifdef __cplusplus
        extern "C"{
#endif /* __cplusplus */

/*STRUCT<创建OSPF6进程结构体>*/
typedef struct tagOSPF6_CFGPROC
{
    USHORT bNoFlag;                               /*0 - 配置
                                                    1 - 删除*/
    USHORT usProcessId;                           /*进程ID,取值范围:1-0xffff*/
    ULONG  ulRouterId;                            /*Router ID，主机序,取值范围:1-0xffffffff*/
    UCHAR  ucVrfName[OSPF6_MAX_VRFNAME_LENGTH+1]; /*VPN名,非空*/
}OSPF6_CFGPROC_S;

/*STRUCT<创建OSPF6区域结构体>*/
typedef struct tagOSPF6_CFGAREA
{
    USHORT bNoFlag;                               /*0 - 配置
                                                    1 - 删除*/
    USHORT usProcessId;                           /*进程ID,取值范围:1-0xffff*/
    ULONG  ulAreaId;                              /*区域ID,取值范围:0-0xffffffff*/ 
}OSPF6_CFGAREA_S;

/*STRUCT<配置OSPF6 Interface结构体>*/
typedef struct tagOSPF6_CFGINTF
{ 
    USHORT bNoFlag;                              /*0 - 配置
                                                   1 - 删除*/
    USHORT usProcessId;                          /*进程ID,取值范围:1-0xffff*/
    ULONG  ulAreaId;                             /*区域ID,取值范围:0-0xffffffff*/ 
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
} OSPF6_CFGINTF_S;

/*STRUCT<配置Interface的OSPF6 Network Type结构体>*/
typedef struct tagOSPF6_CFGINTF_NETTYPE
{ 
    USHORT bNoFlag;                              /*0 - 配置
                                                   1 - 删除*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    ULONG  ulNetType;                            /*网络类型,取值范围:
                                    #define OSPF6_NETWORK_BROADCAST       1 
                                    #define OSPF6_NETWORK_NBMA            2
                                    #define OSPF6_NETWORK_POINT_TO_POINT  3 
                                    #define OSPF6_NETWORK_POINT_T_MLTPNT  5
                                                */ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGINTF_NETTYPE_S;

/*STRUCT<配置Interface的OSPF6 Cost结构体>*/
typedef struct tagOSPF6_CFGINTF_COST
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    ULONG  ulCost;                               /*路径代价，默认1 
                                                   范围:1~65535*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGINTF_COST_S;

/*STRUCT<配置Interface的OSPF6 优先级结构体>*/
typedef struct tagOSPF6_CFGINTF_PRIORITY 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    ULONG  ulPriority;                           /*优先级，默认1
                                                    范围:0~255，其中0表示不参与DR选举，
                                                    需要特别提出的是这里该值越大，优先级越高*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGINTF_PRIORITY_S;

/*STRUCT<配置Interface的OSPF6 MTU Ignore功能结构体，默认为关闭>*/
typedef struct tagOSPF6_CFGMTU_IGNORE_S 
{ 
    USHORT bDefFlag;                             /*? - 配置
                                                   1 - 恢复默认值*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGMTU_IGNORE_S;

/*STRUCT<配置Interface的OSPF6 Retransmit Interval结构体>*/
typedef struct tagOSPF6_CFGRXMT_ITVL_S 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    ULONG  ulRxmtInterval;                       /*重传间隔，默认5s
                                                   范围:1~1800*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGRXMT_ITVL_S;

/*STRUCT<配置Interface的OSPF6 Transmission Delay结构体>*/
typedef struct tagOSPF6_CFGTRANSDELAY 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    ULONG  ulTransDelay;                         /*传输时延，默认1s
                                                   范围:1~1800*/  
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGTRANSDELAY_S;

/*STRUCT<配置Interface的OSPF6 Hello Interval结构体>*/
typedef struct tagOSPF6_CFGHELLO_ITVL 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    ULONG  ulHelloInterval;                      /*hello报文发送间隔，默认10s
                                                    范围:1~65535*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGHELLO_ITVL_S;

/*STRUCT<配置Interface的OSPF6 Dead Interval结构体>*/
typedef struct tagOSPF6_CFGDEAD_ITVL 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    ULONG  ulDeadInterval;                       /*Dead间隔，默认40s
                                                    范围:1~65535*/
    ULONG  ulFast_Hello_Multiplier;              /*表明在使能fast hello，
                                                    1s内发送hello报文的数目 
                                                    取值范围:3-20 默认值5*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGDEAD_ITVL_S;

/*STRUCT<配置Interface的Poll Interval结构体>*/
typedef struct tagOSPF6_CFGPOLL_ITVL
{
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    UCHAR  ucPadding[2];                         /*填充*/
    ULONG  ulInstanceId;                         /*实例ID,取值范围:0-255*/ 
    ULONG  ulPollInterval;                       /*Poll Interval(S)，默认120*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1]; /*接口名,非空*/ 
}OSPF6_CFGPOLL_ITVL_S;

/*STRUCT<配置区域NSSA属性结构体>*/
typedef struct tagOSPF6_CFGAREA_NSSA
{
    USHORT bNoFlag;                         /*0 - 配置
                                              1 - 恢复*/
    USHORT usProcessId;                     /*进程ID,取值范围:1-0xffff*/
    ULONG  ulAreaId;                        /*区域ID,取值范围:1-0xffffffff*/ 
    UCHAR  ucNssaOption;                    /*NSSA选项,Bit位有效,取值如下
                                                OSPF6_AREA_NSSAOPT_NOSUMMARY
                                                OSPF6_AREA_NSSAOPT_NOIMPORT*/
    UCHAR  ucPadding[3];                    /*填充*/
}OSPF6_CFGAREA_NSSA_S;

/*STRUCT<配置OSPF6 Stub区域>*/
typedef struct tagOSPF6_CFGAREASTUB 
{ 
    USHORT bNoFlag;                         /*0 - 配置
                                              1 - 恢复*/
    USHORT usProcessId;                     /*进程ID,取值范围:1-0xffff*/
    ULONG  ulAreaId;                        /*区域ID,取值范围:1-0xffffffff*/
    USHORT usSummaryFlag;                   /*Stub 选项,数值有效,如下
                                              是否引入summary lsa到stub，
                                              默认OSPF6_SUMM_SEND_AREA_SUMMARY
                                              OSPF6_SUMM_NO_AREA_SUMMARY - 不引入Summary
                                              OSPF6_SUMM_SEND_AREA_SUMMARY - 引入Summary*/
    UCHAR  ucPadding[2];                    /*填充*/
}OSPF6_CFGAREASTUB_S;

/*STRUCT<配置区域聚合结构体>*/
typedef struct tagOSPF6_CFGAREA_AGG
{ 
    USHORT bNoFlag;                         /*0 - 配置
                                              1 - 删除*/
    USHORT usProcessId;                     /*进程ID,取值范围:1-0xffff*/
    ULONG  ulAreaId;                        /*区域ID,取值范围:0-0xffffffff*/
    INET6_ADDRESS_S stPrefix;               /*前缀长度,范围 :3~128*/ 
    ULONG  ulAdvert;                        /*是否通告标志,取值如下:
                                              OSPF6_AGG_ADVRTISE - 通告
                                              OSPF6_AGG_DO_NOT_ADVRTISE - 不通告*/ 
}OSPF6_CFGAREA_AGG_S; 

/*STRUCT<配置OSPF6 Stub/NSSA区域的默认Cost>*/
typedef struct tagOSPF6_CFGSTUBAREA_COST 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    USHORT usProcessId;                          /*进程ID,取值范围:1-0xffff*/
    ULONG  ulAreaId;                             /*区域ID,取值范围:0-0xffffffff*/
    ULONG  ulAreaDefCost;                        /*默认Cost值，默认取值1, 
                                                    范围:0~OSPF6_MAX_AREA_COST_VALUE*/ 
} OSPF6_CFGSTUBAREA_COST_S;

/*STRUCT<配置OSPF6 区域的LSA重新泛洪的时间间隔Reflood Interval>*/
typedef struct OSPF6_CFGAREA_RFSHITVL
{
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    USHORT usProcessId;                          /*进程ID,取值范围:1-0xffff*/
    ULONG  ulAreaId;                             /*区域ID,取值范围:0-0xffffffff*/
    ULONG  ulRfshInterval;                       /*洪泛间隔(S)，默认1800, 
                                                    范围:1~3599*/
} OSPF6_CFGAREA_RFSHITVL_S;

/*STRUCT<配置OSPF6进程的SPF定时时间>*/
typedef struct tagOSPF6_CFGSPF_TIMERS 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    USHORT usProcessId;                          /*进程ID,取值范围:1-0xffff*/
    ULONG  ulDelay;                              /*SPF计算延时时间(DCL内部Point)，默认5000
                                                    范围:1~OSPF6_MAX_SPF_TIME*/ 
    ULONG  ulPause;                              /*SPF计算中断时间(DCL内部Point)，默认10000
                                                   范围:0~OSPF6_ERR_MAX_SPF_DELAY_TIME
                                                   0 - 每个计算步骤都会被打断
                                                   0xFFFFFFFF - 永远不会被打断*/ 
} OSPF6_CFGSPF_TIMERS_S;

/*STRUCT<配置OSPF6进程的最大平衡路由条数>*/
typedef struct tagOSPF6_CFGMAX_LOAD_BALANCE 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    USHORT usProcessId;                          /*进程ID,取值范围:1-0xffff*/
    USHORT usPathCount;                          /*平衡路由条数，默认5
                                                   范围:1~OSPF6_MAX_EQCOST_PATH*/ 
    UCHAR  ucPadding[2];                         /*填充*/
} OSPF6_CFGMAX_LOAD_BALANCE_S;

/*STRUCT<配置OSPF6进程的代价>*/
typedef struct tagOSPF6_CFGPREFERENCE 
{ 
    USHORT bDefFlag;                             /*0 - 配置
                                                   1 - 恢复默认值*/
    USHORT usType;                               /*配置类型，
                                                    范围:1~3
                                                   OSPF6_PREFERENCE_TYPE_INT - 设置在区域内路径上的代价
                                                   OSPF6_PREFERENCE_TYPE_EXT - 设置在外部路径上的代价*/
    UCHAR  ucPreferenceInt;                      /*区域内路径上的代价，默认值30
                                                   范围:1~255*/
    UCHAR  ucPreferenceExt;                      /*外部路径上的代价，默认值110
                                                   范围:1~255*/
    UCHAR  ucPadding[2];                         /*填充*/
    CHAR   szVrfName[OSPF6_MAX_VRFNAME_LENGTH + 1]; /*VRF名,非空*/
} OSPF6_CFGPREFERENCE_S;

/*STRUCT<OSPF6路由引入策略具体信息>*/
typedef struct tagOSPF6_RPM_PLCYREDIS
{
    UCHAR  ucProtoType;                     /* 协议ID类型,取值如下:
                                               #define RM_PROTO_CONNECTED  0x2  
                                               #define RM_PROTO_STATIC     0x3
                                               #define RM_PROTO_RIPNG      0x18
                                               #define RM_PROTO_OSPF6      0x1D
                                            */
    UCHAR  ucPadding;                       /*填充*/
    USHORT usProcessId;                     /*被引入端的进程ID,取值范围:1-0xffff*/
    ULONG  ulMetricType;                    /*Metric类型:1表示TYPE1, 2表示TYPE2*/
    ULONG  ulMetricVal;                     /*Metric值，默认值1
                                                      0 - 不配置Metric值*/
} OSPF6_RPM_PLCYREDIS_S;

/*STRUCT<配置OSPF6路由引入策略*/
typedef struct tagOSPF6_CFGREDISTRIBUTE
{
    USHORT bNoFlag;                         /*  0 - 配置
                                                1 - 删除*/
    USHORT usProcessId;                     /*配置进程ID,取值范围：1-0xffff*/
    OSPF6_RPM_PLCYREDIS_S stPolicyRedist;   /*引入策略,取值范围：非空*/
} OSPF6_CFGREDISTRIBUTE_S;

/*STRUCT<配置OSPF6路由引入/接收过滤策略信息>*/
typedef struct tagOSPF6_RPM_PLCYDIST
{
    USHORT usProcessId;                     /*进程ID 对于接收过滤来说，
                                              该字段无效,取值范围:1-0xffff*/
    UCHAR  ucProtocolID;                    /*协议ID类型,取值如下:
                                                       #define RM_PROTO_CONNECTED  0x2  
                                                       #define RM_PROTO_STATIC     0x3
                                                       #define RM_PROTO_RIPNG      0x18
                                                       #define RM_PROTO_OSPF6      0x1D
                                                       Protocol ID  对于接收过滤来说，
                                                      该字段无效*/
    UCHAR  ucPadding;                       /*填充*/
    union
    {
        ULONG ulAclNum;                     /*ACL6规则组号
                                              范围:2000~2999*/
    } stFltrName;   
    union
    {
        ULONG ulAclNum;                     /*ACL6规则组号
                                              范围:2000~2999*/
    } stHopFltrName;
} OSPF6_RPM_PLCYDIST_S;

/*STRUCT<配置OSPF6路由引入/接收过滤>*/
typedef struct tagOSPF6_CFGDISTRIBUTE
{
    USHORT bNoFlag;                         /*0 - 配置
                                              1 - 删除*/
    USHORT usProcessId;                     /*进程ID,取值范围：1-0xffff*/
    OSPF6_RPM_PLCYDIST_S stPolicyDist;      /*引入/接收过滤,取值范围:非空*/
} OSPF6_CFGDISTRIBUTE_S;

/*STRUCT<配置静态OSPF6邻居>*/
typedef struct tagOSPF6_CFGPEER
{
    USHORT bNoFlag;                             /*0 - 配置
                                                  1 - 删除*/
    UCHAR  ucPadding[2];                        /*填充*/
    ULONG  ulInstanceId;                        /*实例ID,取值范围:0-255*/ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1];/*接口名,非空*/ 
    UCHAR  ucAddress[OSPF6_MAX_INET_ADDR_LEN];  /*对端LinkLocal地址*/
    ULONG  ulPriOpFlag;                         /*用户配置优先级选项
                                                0 - 设置
                                                1 - 不设置*/    
    ULONG  ulPriority;                          /*优先级，默认值1
                                                范围:0~0xFF,0为不参与DR选举*/
} OSPF6_CFGPEER_S;

/*S-IP-003-OSPFv3-005 配置OSPFv3 进程GR重启*/

/*Hitless Restart Reason*/
#define OSPF6_RESTART_REASON_UNKNOWN 0
#define OSPF6_RESTART_REASON_SOFTWARE_RESTART 1
#define OSPF6_RESTART_REASON_SOFTWARE_RELOAD  2
#define OSPF6_RESTART_REASON_SWITCH_TO_BACKUP 3

#define OSPF6_GR_MIN_PERIOD 1          /*最小GR周期时间 1s*/
#define OSPF6_GR_MAX_PERIOD 1800       /*最大GR周期时间 1800s*/

typedef struct tagOSPF6_CFG_GR 
{ 
    USHORT usProcessId;                 /*进程ID*/
    UCHAR  ucPad[2];
    ULONG ulDoGraceHitless;            /*平滑重启标志*/
    ULONG ulDoGraceUnplannedHitless;  /*无计划地平滑重启标志*/
    ULONG ulHitlessGrPeriod;           /*平滑重启周期*/
    ULONG ulhitlessGrReason;           /*平滑重启原因*/
} OSPF6_CFG_GR_S;

/*Added by w00207740, 支持ospfv3 GR功能, 2014/3/14 */
typedef struct tagOSPF6_CFG_GRHELPER
{
    UCHAR szIfname[OSPF6_MAX_IF_NAME_LENGTH+1];          /*接口名称*/
    ULONG ulInstanceId;                                 /*接口实例号*/
    ULONG ulHelperMode;                                 /*Gr Helper模式*/
    ULONG ulGrPeriod;                                   /*配置等待Gr时长*/
    ULONG ulAccNum;                                     /*配置过滤组号*/
    
}OSPF6_CFG_GRHELPER_S;

/*S-IP-004-OSPFv3-003*/
typedef struct tagOSPF6_CFGGRHELPER
{
    USHORT usProcessId;
    USHORT usPad;
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    ULONG ulAccNum;
}OSPF6_CFGGRHELPER_PRO_S;



typedef ULONG(*OSPF6_PACKET_HOOK_FUNC)(USHORT usProcId, ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);

/*******************************************************************************
*    Func Name: OSPF6_CFG_Proc
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: 创建/删除OSPF6进程
*  Description: 创建/删除OSPF6进程,并指定对应的route ID;现支持进程规格数为:32
*        Input: OSPF6_CFGPROC_S *pstProcIn:进程配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 指定的VrfName 必需先创建，如果不指定VrfName表示为公网
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_Proc(OSPF6_CFGPROC_S *pstProcIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Intf
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: 配置/删除OSPF6进程中的接口
*  Description: 配置/删除OSPF6进程与接口,实例的绑定操作,目前只支持在eth/trunk/ppp/mp链路上绑定进程信息
*        Input: OSPF6_CFGINTF_S *pstIntfIn:接口配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 同一个接口上绑定的进程和实例信息必须不同，不同接口上可以绑定相同的进程与实例信息
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_Intf(OSPF6_CFGINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_IntfNetType
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: 配置/恢复OSPF6接口的网络类型.
*  Description: 配置/恢复OSPF6接口的网络类型,
*               当设置NBMA或者P2MP网络类型时,默认Hello间隔为30s,Dead间隔为120s;
*               当设置BROADCAST或者P2P网络类型时,默认Hello间隔为10s,Dead间隔为30s.
*        Input: OSPF6_CFGINTF_NETTYPE_S *psNetTypeIn:接口网络类型配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 如果改变网络类型前,Hello间隔与Dead间隔用户都已经指定,
*               那么网络类型改变时将不会自动改变这两个参数;
*               如果改变网络类型前,Hello间隔用户已经指定,但是Dead间隔用户没有指定,
*               那么网络类型改变时,Hello间隔不变,Dead间隔等于Hello间隔4倍;
*               如果改变网络类型前,Dead间隔用户已经指定,但是Hello间隔用户没有指定,
*               那么网络类型改变时,Dead间隔不变,Hello间隔为网络类型改变后的初始值.              
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_IntfNetType(OSPF6_CFGINTF_NETTYPE_S *psNetTypeIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_IntfCost
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复接口的OSPF6 Cost.
*  Description: 配置/恢复接口的OSPF6 路由花销值.
*        Input: OSPF6_CFGINTF_COST_S * pstIfCostIn:接口Cost配置信息
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
ULONG OSPF6_CFG_IntfCost(OSPF6_CFGINTF_COST_S * pstIfCostIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_IntfPriority
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复接口的OSPF6 优先级.
*  Description: 配置/恢复接口的OSPF6 优先级,该优先级直接参与路由器的DR选举中,
*               优先级较高者,被选举为DR.
*        Input: OSPF6_CFGINTF_PRIORITY_S *pstIfPriorityIn:接口优先级配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 优先级数值越高越优先.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_IntfPriority(OSPF6_CFGINTF_PRIORITY_S *pstIfPriorityIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_MtuIgnore
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: 配置/恢复接口的OSPF6 MTU Ignore功能.
*  Description: 配置/恢复接口的OSPF6 MTU Ignore功能,MTU值直接关系到邻居关系建立,
*               默认情况下MTU值不同,则OSPFv3路由器间无法成功建立邻居关系;
*               配置了MTU值忽略功能,则OSPFv3路由器间不管MTU值相同与否都成功建立邻居关系.
*        Input: OSPF6_CFGMTU_IGNORE_S *pstMtuIgnIn:MTU Ignore功能配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 邻居已经成功建立后,改变MTU值,设置/恢复接口MTU Ignore功能都只能等
*               新一轮建立邻居过程发挥作用;
*               比如接口去绑定进程来达到邻居重新建立的目的.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_MtuIgnore(OSPF6_CFGMTU_IGNORE_S *pstMtuIgnIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_RxmtItvl
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: 配置/恢复接口的OSPF6 Retransmission Interval.
*  Description: 配置/恢复接口的OSPF6 Retransmission Interval,即LSA重传间隔;
*               为了确保洪泛的可靠性，LSA将被重传直至收到确认。
*        Input: OSPF6_CFGRXMT_ITVL_S *pstRxItvlIn:Retransmission Interval配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 接口重传间隔设置太短,会造成不必要重传;
*               接口重传间隔设置太长,在丢包时就会影响洪泛的速度.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_RxmtItvl(OSPF6_CFGRXMT_ITVL_S *pstRxItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_TransDelay
* Date Created: 2009-06-16
*       Author: qinyun62011
*      Purpose: 配置/恢复接口的OSPF6 Transmission Delay.
*  Description: 配置/恢复接口的OSPF6 Transmission Delay,即LSA传输时延;
*               接口传送一个LSU包所需要的秒数.
*        Input: OSPF6_CFGTRANSDELAY_S *pstTrDlyIn:Transmission Delay配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-16   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_TransDelay(OSPF6_CFGTRANSDELAY_S *pstTrDlyIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_HelloItvl
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复接口的OSPF6 Hello Interval.
*  Description: 配置/恢复接口的OSPF6 Hello Interval,即Hello报文间隔时间.
*               当设置NBMA或者P2MP网络类型时,默认Hello间隔为30s,Dead间隔为120s;
*               当设置BROADCAST或者P2P网络类型时,默认Hello间隔为10s,Dead间隔为30s.
*        Input: OSPF6_CFGHELLO_ITVL_S* pstHelloItvlIn:Hello Interval配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 如果改变网络类型前,Hello间隔与Dead间隔用户都已经指定,
*               那么网络类型改变时将不会自动改变这两个参数;
*               如果改变网络类型前,Hello间隔用户已经指定,但是Dead间隔用户没有指定,
*               那么网络类型改变时,Hello间隔不变,Dead间隔等于Hello间隔4倍;
*               如果改变网络类型前,Dead间隔用户已经指定,但是Hello间隔用户没有指定,
*               那么网络类型改变时,Dead间隔不变,Hello间隔为网络类型改变后的初始值.              
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_HelloItvl(OSPF6_CFGHELLO_ITVL_S* pstHelloItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_DeadItvl
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复接口的OSPF6 Dead Interval.
*  Description: 配置/恢复接口的OSPF6 Dead Interval,即Dead间隔时间.
*               当设置NBMA或者P2MP网络类型时,默认Hello间隔为30s,Dead间隔为120s;
*               当设置BROADCAST或者P2P网络类型时,默认Hello间隔为10s,Dead间隔为30s.
*               当Dead间隔时间为1s时,意味着启动了FastHello功能,
*               Fast_Hello_Multiplier字段就是FastHello报文发送频率.
*        Input: OSPF6_CFGDEAD_ITVL_S *pstDeadItvlIn:Dead Interval配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 如果改变网络类型前,Hello间隔与Dead间隔用户都已经指定,
*               那么网络类型改变时将不会自动改变这两个参数;
*               如果改变网络类型前,Hello间隔用户已经指定,但是Dead间隔用户没有指定,
*               那么网络类型改变时,Hello间隔不变,Dead间隔等于Hello间隔4倍;
*               如果改变网络类型前,Dead间隔用户已经指定,但是Hello间隔用户没有指定,
*               那么网络类型改变时,Dead间隔不变,Hello间隔为网络类型改变后的初始值.              
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_DeadItvl(OSPF6_CFGDEAD_ITVL_S *pstDeadItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_PollItvl
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复接口的Poll Interval.
*  Description: 配置/恢复接口的Poll Interval,即Poll间隔时间.该字段仅对NBMA网络中的邻居有效,
*               邻居状态Down,每隔PollInterval秒发送Hello包;
*               其他状态时,每隔HelloInterval秒发送Hello包.
*        Input: OSPF6_CFGPOLL_ITVL_S *pstPollItvlIn:Poll Interval配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 仅对NBMA网络中的邻居有效.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_PollItvl(OSPF6_CFGPOLL_ITVL_S *pstPollItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AreaNssa
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 设置/取消区域为NSSA区域.
*  Description: 设置/取消区域为NSSA区域,具有NSSA属性的区域会拒绝5类LSA扩散;
*               区域被配置NSSA属性同时还可以追加配置选项如no-summary选项拒绝3类/4类LSA扩散;
*               区域被配置NSSA属性同时还可以追加配置选项如no-import选项来选择是否要将7类LSA转换为5类LSA.
*        Input: OSPF6_CFGAREA_NSSA_S *pstAreaNssaIn:NSSA属性配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: no-import选项作用只发生在区域边界路由器上,路由器设置该选项后,就将7类LSA转换为5类LSA;
*               路由器不设置该选项,则会根据几台边界路由器来候选一台来将7类LSA转换为5类LSA;
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_AreaNssa(OSPF6_CFGAREA_NSSA_S *pstAreaNssaIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AreaStub
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 设置/取消区域为STUB区域.
*  Description: 设置/取消区域为STUB区域,具有STUB属性的区域会拒绝5类LSA扩散;
*        Input: OSPF6_CFGAREASTUB_S *pstAreaStubIn:STUB区域配置信息
*               区域被配置STUB属性同时还可以追加配置选项如no-summary选项拒绝3类/4类LSA扩散;
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
ULONG OSPF6_CFG_AreaStub(OSPF6_CFGAREASTUB_S *pstAreaStubIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_StubAreaCost
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复OSPF6 STUB/NSSA区域默认Cost值.
*  Description: 配置/恢复OSPF6 STUB/NSSA区域默认Cost值,即STUB/NSSA区域默认路由metric值.
*        Input: OSPF6_CFGSTUBAREA_COST_S * pstAreaCostIn:默认Cost值配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 针对STUB/NSSA区域有效.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_StubAreaCost(OSPF6_CFGSTUBAREA_COST_S * pstAreaCostIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AreaRfshItvl
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复OSPF6区域LSA的Reflood Interval.
*  Description: 配置/恢复OSPF6区域LSA的Reflood Interval,即LSA重新泛洪时间间隔.
*        Input: OSPF6_CFGAREA_RFSHITVL_S *pstAreaRfshItvlIn:Reflood Interval配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 针对所有区域有效.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_AreaRfshItvl(OSPF6_CFGAREA_RFSHITVL_S *pstAreaRfshItvlIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AreaAgg
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/删除区域聚合
*  Description: 配置/删除区域聚合,配置聚合后，只有落入该网段内的路由才会聚合
*        Input: OSPF6_CFGAREA_AGG_S *pstAreaAggIn:区域聚合配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 现在只支持3类lsa的聚合实现
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_AreaAgg(OSPF6_CFGAREA_AGG_S * pstAreaAggIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_SpfTimers
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复OSPF6进程SPF定时时间.
*  Description: 配置/恢复OSPF6进程SPF定时时间,包括SPF计算延时时间和SPF计算中断时间.
*        Input: OSPF6_CFGSPF_TIMERS_S * pstSpftimersIn:SPF定时时间配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 计量单位不是秒,而是DCL内部Point.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_SpfTimers (OSPF6_CFGSPF_TIMERS_S * pstSpftimersIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_MaxLoadBalance
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 设置/恢复OSPF6进程的最大平衡路由条数.
*  Description: 设置/恢复OSPF6进程的最大平衡路由条数.
*        Input: OSPF6_CFGMAX_LOAD_BALANCE_S * pstMaxLoadBalanceIn:平衡路由条数配置信息
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
ULONG OSPF6_CFG_MaxLoadBalance(OSPF6_CFGMAX_LOAD_BALANCE_S * pstMaxLoadBalanceIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Preference
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/恢复OSPF6区域内路径和外部路径上的代价.
*  Description: 配置/恢复OSPF6区域内路径和外部路径上的代价,外部路径指AS外部路由引入的路由代价.
*        Input: OSPF6_CFGPREFERENCE_S* pstPrefIn:代价配置信息
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
ULONG OSPF6_CFG_Preference(OSPF6_CFGPREFERENCE_S* pstPrefIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Redistribute
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/删除OSPF6路由引入策略
*  Description: 配置/删除OSPF6路由引入策略,可引入的类型有：直连路由、静态路由、OSPFv3路由以及RIPng路由
*        Input: OSPF6_CFGREDISTRIBUTE_S* pstRedistIn:路由引入策略配置信息
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
ULONG OSPF6_CFG_Redistribute(OSPF6_CFGREDISTRIBUTE_S* pstRedistIn);

/*******************************************************************************
*    Func Name: OSPF6_CFG_RouteFilterExport
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/删除OSPF6进程路由引入过滤
*  Description: 本函数用于OSPF6的路由引入策略的ACL过滤配置，先进行OSPF6路由引入的策略配置后，再根据该策略配置过滤条件。
*        Input: OSPF6_CFGDISTRIBUTE_S* pstDistExpIn:路由引入过滤配置信息
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
ULONG OSPF6_CFG_RouteFilterExport(OSPF6_CFGDISTRIBUTE_S* pstDistExpIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_RouteFilterImport
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/删除OSPF6进程路由接收过滤
*  Description: 本函数用于OSPF6的学习到的路由进行ACL过滤配置
*        Input: OSPF6_CFGDISTRIBUTE_S*  pstDistImpIn:路由接收过滤配置信息
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
ULONG OSPF6_CFG_RouteFilterImport(OSPF6_CFGDISTRIBUTE_S*  pstDistImpIn);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Peer
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: 配置/删除静态OSPF6邻居.
*  Description: 配置/删除静态OSPF6邻居,实际生效时,网络类型必须为NBMA网络.
*        Input: OSPF6_CFGPEER_S *pstPeerIn:邻居配置信息
*       Output: 
*       Return: 成功返回OSPF6_OK
*               失败返回错误码
*      Caution: 优先级字段设置为0时,表示不参与DR选举;
*               优先级字段设置为非0时,表示都参与DR选举,
*               选举按照接口路由优先级,然后rouer-id大小的原则来选举DR.
*               实际生效时,网络类型必须为NBMA网络.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CFG_Peer(OSPF6_CFGPEER_S *pstPeerIn);


/*******************************************************************************
*    Func Name: OSPF6_Intermediate_Hook_Register
* Date Created: 2010-3-30
*       Author: luoagaowei
*  Description: OSPFv3 报文收发注册钩子
*        Input: ULONG ulDirection:输出或者输入
*               OSPF6_PACKET_HOOK_FUNC pfOspfFwHookFunc:
*       Output: 
*       Return: OSPFv3错误码
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-3-30  luoagaowei         Creat the first version.
*
*******************************************************************************/

ULONG OSPF6_Intermediate_Hook_Register(ULONG ulDirection, 
                                OSPF6_PACKET_HOOK_FUNC pfOspfFwHookFunc); 

/*******************************************************************************
*    Func Name: OSPF6_Intermediate_UnHook_Register
* Date Created: 2010-3-30
*       Author: luoagaowei
*  Description: OSPFv3报文钩子函数解注册
*        Input: ULONG ulDirection:输出或者输入
*       Output: 
*       Return: OSPFv3错误码
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2010-3-30  luoagaowei         Creat the first version.
*
*******************************************************************************/
ULONG OSPF6_Intermediate_UnHook_Register(ULONG ulDirection);
/*******************************************************************************
*    Func Name: OSPF6_CFG_Area
* Date Created: 2014-03-04
*       Author: w00207740
*  Description: 配置OSPFv3区域
*        Input: OSPF6_CFGAREA_S *pstAreaIn:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-04   w00207740               Create      参考OSPF_CFG_CmdAreaProc编写
*
*******************************************************************************/
ULONG OSPF6_CFG_Area(OSPF6_CFGAREA_S *pstAreaIn);

/*******************************************************************************
*    Func Name: OSPF6_CFG_RouterId
* Date Created: 2014-03-12
*       Author: w00207740
*  Description: 配置/修改进程route id
*        Input: USHORT usProcessId:
*               ULONG ulRouterId:
*       Output: 
*       Return: 
*      Caution: 若需要新配置的route id生效，需要重启进程
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-12   w00207740               Create      参考OSPF_CFG_RouterId
*
*******************************************************************************/
ULONG OSPF6_CFG_RouterId(USHORT usProcessId, ULONG ulRouterId);
/*******************************************************************************
*    Func Name: OSPF6_CFG_AdminProc
* Date Created: 2014-03-12
*       Author: w00207740
*  Description: 由用户配置进程UP/DOWN/RESET
*        Input: USHORT usProcessId:
*               ULONG ulOperation:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-12   w00207740               Create
*
*******************************************************************************/
ULONG OSPF6_CFG_AdminProc(USHORT usProcessId,ULONG ulOperation);

/*S-IP-003-OSPFv3-005 配置OSPFv3 进程GR重启*/
/*******************************************************************************
*    Func Name: OSPF6_CFG_GR
* Date Created: 2014-03-18
*       Author: guojianjun178934
*  Description: OPSFV3配置GR参数
*        Input: OSPF6_CFG_GR_S * pstOSPFGR:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   guojianjun178934        Create
*
*******************************************************************************/
ULONG OSPF6_CFG_GR(OSPF6_CFG_GR_S * pstOSPFGR);


ULONG OSPF6_CFG_CmdGrHelper(OSPF6_CFG_GRHELPER_S * pstGrHelper);
/*******************************************************************************
*    Func Name: OSPF6_CFG_CmdGrHelperProc
* Date Created: 2014-04-15
*       Author: w00207740
*  Description: 针对进程配置Gr Helper
*        Input: OSPF6_CFGGRHELPER_PRO_S * pstGrHelperProc:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-15   w00207740               Create
*
*******************************************************************************/
ULONG OSPF6_CFG_CmdGrHelperProc(OSPF6_CFGGRHELPER_PRO_S * pstGrHelperProc);

/*******************************************************************************
*    Func Name: OSPF6_Warning_Hook_Register
* Date Created: 2014-05-12
*       Author: guojianjun178934
*  Description: OSPFV3告警注册函数
*        Input: OSPFV3_WARNING_HOOK_FUNC pfOSPFV3WarningHookFun:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-12   guojianjun178934        Create
*
*******************************************************************************/
ULONG OSPF6_Warning_Hook_Register(OSPFV3_WARNING_HOOK_FUNC pfOSPFV3WarningHookFun);


#ifdef __cplusplus
        }
#endif /* __cplusplus */
        
#endif /* _OSPF6_CFG_API_H_ */

