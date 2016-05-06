/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_route_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面路由ROUTE对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_ROUTE_API_H_
#define _SFE_ROUTE_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面路由模块错误码 */
typedef enum enumSfeRouteCode
{
    SFE_RT_SUCCESS = SFE_OK,               /* 操作成功 */
    SFE_RT_ERR_BEGIN = SFE_ROUTE_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    SFE_RT_NOTINIT,                        /* 1  本核没有初试化成功 */
    SFE_RT_NULL_PARA_ERR,                  /* 2  指针为空 */
    SFE_RT_OPER_ERR,                       /* 3  操作类型非法 */
    SFE_RT_VRF_PRECFG_ERR,                 /* 4  获取VRF预配置个数失败 */
    SFE_RT_ROUTE_PRECFG_ERR,               /* 5  获取普通路由节点预配置个数失败 */
    SFE_RT_ALLOC_ROUTE_ERR,                /* 6  分配路由节点失败 */
    SFE_RT_ALLOCBALANCE1_ERR,              /* 7  分配平衡路由节点失败 */
    SFE_RT_ALLOCBALANCE2_ERR,              /* 8  分配平衡路由节点失败 */
    SFE_RT_ALLOC_ROUTE_ADD_CURRLAYER1_ERR, /* 9  申请路由节点失败 */
    SFE_RT_ALLOC_ROUTE_ADD_CURRLAYER2_ERR, /* 10 申请路由节点失败 */
    SFE_RT_ALLOC_ROUTE_ADD_COVERTREE1_ERR, /* 11 申请路由节点失败 */
    SFE_RT_ALLOC_ROUTE_ADD_COVERTREE2_ERR, /* 12 申请路由节点失败 */
    SFE_RT_MALLOC_L1_TABLE_ERR,            /* 13 申请L1索引失败 */
    SFE_RT_ALLOCL2L3INDEX_EXCEED24_ERR,    /* 14 分配L2L3索引节点失败 */
    SFE_RT_ALLOCL2L3INDEX_ERR,             /* 15 分配L2L3索引节点失败 */
    SFE_RT_MASK_ERR,                       /* 16 掩码长度非法 */
    SFE_RT_OVER_MAX_VRF_ERR,               /* 17 VRF大于支持最大值 */
    SFE_RT_SAME_ORIGIN_ERR,                /* 18 配置路由相同,但是来源不同 */
    SFE_RT_SAME_ORIGIN_ADDBALANCE_ERR,     /* 19 配置路由相同,但是来源不同 */
    SFE_RT_MAX_BALANCE_ERR,                /* 20 到同一个目的的平衡路由达到最大值 */
    SFE_RT_OVER_LAYER_ERR,                 /* 21 添加路由超过3层,即掩码长度大于32 */
    SFE_RT_POOL_L2L3_ERR,                  /* 22 初始化POOL L2L3索引失败 */
    SFE_RT_POOL_ROUTE_NODE_ERR,            /* 23 初始化POOL普通路由节点失败 */
    SFE_RT_POOL_BLANCE_ROUTE_ERR,          /* 24 初始化POOL平衡路由节点失败 */
    SFE_RT_BALANCE_ROUTE_PRECFG_ERR,       /* 25 获取平衡路由节点预配置个数失败 */
    SFE_RT_ADD_COVER_TREE_ERR,             /* 26 添加到覆盖树失败 */
    SFE_RT_DEL_NOROUTE_ERR,                /* 27 删除路由失败,不存在相关路由 */
    SFE_RT_DEL_SAMEROUTE_ERR,              /* 28 不能删除来源不同的路由表项 */
    SFE_RT_DEL_SAMEBALROUTE_ERR,           /* 29 不能删除来源不同的平衡路由表项 */
    SFE_RT_DEL_OVER_LAYER_ERR,             /* 30 删除路由超过3层,即掩码长度大于32 */
    SFE_RT_DEL_CURRLAYER_ERR,              /* 31 从当前层次中删除失败 */
    SFE_RT_DEL_NOROUTE1_ERR,               /* 32 删除路由失败,L1索引下默认路由不存在*/
    SFE_RT_DEL_NOROUTE2_ERR,               /* 33 删除路由失败,L2索引下地址偏移不存在路由 */
    SFE_RT_DEL_NOROUTE3_ERR,               /* 34 删除路由失败,L2索引下默认路由不存在*/
    SFE_RT_DEL_NOROUTE4_ERR,               /* 35 删除路由失败,L3索引下地址偏移不存在路由 */
    SFE_RT_DEL_NOROUTE5_ERR,               /* 36 删除路由失败,L3索引下默认路由不存在*/
    SFE_RT_DEL_NOROUTE6_ERR,               /* 37 删除路由失败,属于内部异常,指针为空 */
    SFE_RT_DEL_NOROUTE7_ERR,               /* 38 删除路由失败,默认路由下不存在相关路由 */
    SFE_RT_DEL_NOROUTE8_ERR,               /* 39 删除路由失败,平衡路由下不存在相关路由 */
    SFE_RT_DEL_NOROUTE9_ERR,               /* 40 删除路由失败,整个覆盖树下不存在该路由 */
    SFE_RT_DEL_NOROUTE10_ERR,              /* 41 删除路由失败,当前节点和删除路由不匹配 */
    SFE_RT_DEL_SAMEROUTE_COVERTREE_ERR,    /* 42 不能删除来源不同的路由表项 */
    SFE_RT_SEARCH_UNREACH_VRF_INVALID,     /* 43 由于参数VRF超出最大值导致查找路由失败 */
    SFE_RT_SEARCH_UNREACH_IN_DEFAULT_ROUTE,/* 44 查找默认路由失败 */
    SFE_RT_SEARCH_UNREACH_L2L3,            /* 45 路由查找失败*/
    SFE_RT_SEARCH_UNREACH,                 /* 46 路由查找失败*/
    SFE_RT_SEARCH_UNREACH_IPV4,            /* 47 路由查找失败*/
    SFE_RT_SEARCH_BLACKHOLE,               /* 48 路由是黑洞路由 */
    SFE_RT_OPER_INTF_ERR,                  /* 49 配置路由接口非法 */
    SFE_RT_SEARCH_BYIP_VRF_PARA_ERR,       /* 50 路由查找参数错误*/
    SFE_RT_SEARCH_BYIP_NOT_EXIST,          /* 51 路由查找未命中*/
    SFE_RT_GET_FIB_VRF_ERR,                /* 52 获取路由时VRF索引错误 */
}SFE_ROUTE_ERR_CODE;

/*******************************************************************************
*    Func Name: SFE_ShowAllRouteInfo
* Date Created: 2009-8-6
*       Author: w60786
*      Purpose: 显示数据面所有路由信息
*  Description: 显示数据面所有路由信息
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-6     w60786/luowentong         Creat the first version.
*
*******************************************************************************/
VOID SFE_ShowAllRouteInfo(VOID);

#ifdef  __cplusplus
}
#endif

#endif


