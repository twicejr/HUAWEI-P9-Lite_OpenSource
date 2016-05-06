/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_route.h
*
*  Project Code: VISPV100R008C02
*   Module Name: ROUTE
*  Date Created: 2009-9-20
*        Author: z62474
*   Description: ROUTE模块数据面和控制面共用的结构,宏等定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-9-20    z62474           Creat the first version.
*
*******************************************************************************/
#ifndef _IPSFE_ROUTE_H_
#define _IPSFE_ROUTE_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 路由数据结构 */
typedef struct tagSFE_ROUTE
{
    UINT32    u32VrfIndex;          /* 实例索引 */
    UINT32    u32DstIp;             /* 目的地址 */
    UINT32    u32Nexthop;           /* 下一跳 */
    SFE_IFID  stOutIf;              /* 出接口信息 */
    UINT32    u32LocalIp;           /* 本地出接口地址 */
    UINT32    u32Flags;             /* 路由标记 */
    UINT32    u32Origin;            /* 来源 */
    UINT32    u32ATIndex;           /* 保留，暂不使用*/
    UINT8     u8DstPrefixLength;    /* 目的地址掩码长度 */
    UINT8     u8LocalPrefixLength;  /* 本地出接口地址掩码长度 */
    UINT16    u16RTPri;             /* 路由优先级 */
    UINT32    u32OutIfIndex;        /* 出接口接口索引 */
}SFE_ROUTE_S;

/* 路由获取KEY */
typedef struct tagSFE_ROUTE_GET
{
    UINT32    u32VrfIndex;          /* 实例索引 */
    UINT32    u32DstIp;             /* 目的地址 */
}SFE_GET_ROUTE_KEY_S;

/* 设置数据面源地址数据结构,目前数据面接口没有维护地址,在发送报文的时候,
   根据用户配置VRF下的IP填充报文的源IP */
typedef struct tagSFE_SRCIPADDR
{
    UINT32 u32VrfIndex;                    /* VRF index */
    UINT32 u32SrcIpAddr;                   /* IP Addr */
}SFE_SRCIPADDR_S;

#ifdef  __cplusplus
}
#endif

#endif

