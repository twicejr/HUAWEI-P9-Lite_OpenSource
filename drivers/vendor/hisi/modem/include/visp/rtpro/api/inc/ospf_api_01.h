/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_01.h
*
*  Project Code: Dopra V3R2
*   Module Name:   
*  Date Created: 2013-09-13
*        Author: guojianjun178934
*   Description: 该文件用于OSPF通过I3通知产品相关的对外结构体定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-09-13   guojianjun178934        Create
*
*******************************************************************************/
#ifndef _OSPF_API_01_H_
#define _OSPF_API_01_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define OSPF_CLASH_ROUTER_MAX   5   /* 2-LSA冲突的最大路由器数(包括路由器自身)*/

#define OSPF_ROUTE_CALCULATE_SUCCESS   1    /*路由计算成功*/
#define OSPF_ROUTE_CALCULATE_FAILURE    2    /*路由计算失败*/

typedef struct tagOSPF_NETWORK_LSA_CLASH_WARNING_S
{
    ULONG ulProcessID;
    ULONG ulAreaID;
    ULONG ulClashIPAddr;
    ULONG ulClashRouterCount;
    ULONG szClashRouterID[OSPF_CLASH_ROUTER_MAX];
}OSPF_NETWORK_LSA_CLASH_WARNING_S;

/*路由计算抑制通知*/
typedef struct tagOSPF_ROUTE_CALCULATE_THRESHOLD_NOTIFY
{
    ULONG ulProcessID;                   /* 进程ID */
    ULONG ulCalcResult;                 /*路由计算结果*/
    ULONG ulAreaID;                     /* 区域ID */
    ULONG ulRouterLSACount;             /*当前区域Router LSA总数*/
    ULONG ulNetworkLSACount;           /* 当前区域Network LSA总数*/
}OSPF_ROUTE_CALCULATE_THRESHOLD_NOTIFY;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
