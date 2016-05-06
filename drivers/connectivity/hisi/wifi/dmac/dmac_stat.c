/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_stat.c
  版 本 号   : 初稿
  作    者   : x00189397
  生成日期   : 2014年1月10日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_PERFORM_STAT

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "dmac_stat.h"
#include "mac_resource.h"
#include "dmac_alg_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_STAT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
OAL_STATIC dmac_stat_stru      g_ast_pfm_stat[MAC_STAT_TYPE_BUTT];
OAL_STATIC oal_uint32          g_ul_stat_node_limit[MAC_STAT_TYPE_BUTT];

/*****************************************************************************
  3 静态函数声明
*****************************************************************************/

OAL_STATIC dmac_stat_node_stru* dmac_stat_search_node(oal_dlist_head_stru        *pst_node_dlist_head,
                                                      oam_module_id_enum_uint16   en_module_id,
                                                      oal_void                   *p_void);
OAL_STATIC oal_uint32  dmac_stat_format_title_string(oal_int8                  *pac_output_data,
                                                      oal_uint16                 ul_data_len,
                                                      dmac_stat_node_stru       *pst_stat_node);
OAL_STATIC oal_uint32  dmac_stat_format_data_string(oal_int8                  *pac_output_data,
                                                     oal_uint16                 ul_data_len,
                                                     mac_stat_type_enum_uint8   en_stat_type,
                                                     oal_uint32                 ul_index,
                                                     oal_uint32                *pul_data);
OAL_STATIC oal_uint32  dmac_stat_print(dmac_stat_node_stru     *pst_stat_node, oam_output_type_enum_uint8 en_output_type);
OAL_STATIC oal_uint32  dmac_stat_timer_handler(oal_void * p_void);
OAL_STATIC oal_uint32  dmac_stat_unregister_node(dmac_stat_node_stru   *pst_stat_node);
OAL_STATIC oal_uint32  dmac_stat_get_rx_tid(mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_rx_ctl, oal_uint8 *puc_tidno);
OAL_STATIC oal_uint32  dmac_stat_update_thrpt(mac_vap_stru *pst_vap,
                                  mac_user_stru *pst_user,
                                  dmac_tid_stru *pst_tid,
                                  oal_uint32     ul_stat_bytes,
                                  dmac_stat_direct_enum_uint8 en_stat_direct);

/*****************************************************************************
  4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_stat_int
 功能描述  : dmac模块性能统计模块初始化。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0:代表正常，其他代表异常
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_stat_init(oal_void)
{
    oal_uint8   uc_loop = 0;

    /* 初始化所有性能统计节点链表 */
    for (uc_loop = 0; uc_loop < MAC_STAT_TYPE_BUTT; uc_loop++)
    {
        g_ast_pfm_stat[uc_loop].ul_node_num = 0;
        oal_dlist_init_head(&(g_ast_pfm_stat[uc_loop].st_stat_node_dlist));
    }

    /* 初始化各统计类型的统计节点数量限制 */
    g_ul_stat_node_limit[MAC_STAT_TYPE_TID_DELAY]   = DMAC_STAT_TID_DELAY_NODE_LIMIT;
    g_ul_stat_node_limit[MAC_STAT_TYPE_TID_PER]     = DMAC_STAT_TID_PER_NODE_LIMIT;
    g_ul_stat_node_limit[MAC_STAT_TYPE_TID_THRPT]   = DMAC_STAT_TID_THRPT_NODE_LIMIT;
    g_ul_stat_node_limit[MAC_STAT_TYPE_USER_THRPT]  = DMAC_STAT_USER_THRPT_NODE_LIMIT;
    g_ul_stat_node_limit[MAC_STAT_TYPE_VAP_THRPT]   = DMAC_STAT_VAP_THRPT_NODE_LIMIT;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_exit
 功能描述  : dmac模块性能统计模块卸载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_stat_exit(oal_void)
{
    mac_stat_type_enum_uint8     uc_stat_type       = 0;
    dmac_stat_stru              *pst_stat           = OAL_PTR_NULL;
    oal_dlist_head_stru         *pst_dlist_pos      = OAL_PTR_NULL;
    oal_dlist_head_stru         *pst_dlist_tmp      = OAL_PTR_NULL;
    dmac_stat_node_stru         *pst_stat_node      = OAL_PTR_NULL;
    oal_uint32                   ul_ret             = OAL_SUCC;

    for (uc_stat_type = 0; uc_stat_type < MAC_STAT_TYPE_BUTT; uc_stat_type++)
    {
        pst_stat = &(g_ast_pfm_stat[uc_stat_type]);

        /* 遍列该统计类型的所有统计节点 */
        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_tmp, &(pst_stat->st_stat_node_dlist))
        {
            pst_stat_node = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_stat_node_stru, st_entry);

            /* 注销统计节点  */
            ul_ret = dmac_stat_unregister_node(pst_stat_node);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_scan_ch_statics_complete::pst_mac_device null.}");
                return ul_ret;
            }
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_register
 功能描述  : 注册统计节点
 输入参数  : en_module_id:模块名称
             en_stat_type:统计类型;
             p_void: dmac_stat_param_stru结构体指针:用于存储每个周期的统计值；
             p_func:统计周期到期处理函数指针，函数指针类型:dmac_stat_timeout_func)(dmac_stat_param_stru *);
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32	dmac_stat_register(oam_module_id_enum_uint16        en_module_id,
                                mac_stat_type_enum_uint8        en_stat_type,
                                oal_void                       *p_void,
                                dmac_stat_param_stru           *pst_output_param,
                                dmac_stat_timeout_func          p_func,
								oal_uint32						ul_core_id)
{
    dmac_stat_node_stru     *pst_stat_node      = OAL_PTR_NULL;
    oal_uint8                uc_index           = 0;
    dmac_stat_stru          *pst_stat           = &(g_ast_pfm_stat[en_stat_type]);

    if ((OAL_PTR_NULL == p_void)
		|| ((OAL_PTR_NULL == pst_output_param) && (OAM_MODULE_ID_PERFORM_STAT != en_module_id))
        || ((OAL_PTR_NULL == p_func) && (OAM_MODULE_ID_PERFORM_STAT != en_module_id)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_register::invalid param.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 判断统计节点是否超过限制 */
    if (pst_stat->ul_node_num >= g_ul_stat_node_limit[en_stat_type])
    {
        return OAL_SUCC;
    }

    /* 检查统计节点是否已存在 */
    pst_stat_node = dmac_stat_search_node(&(pst_stat->st_stat_node_dlist), en_module_id, p_void);
    if (OAL_PTR_NULL != pst_stat_node)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_stat_register::the stat_node has been existed.}");
        return OAL_FAIL;
    }

    /* 申请统计节点空间 */
    pst_stat_node = (dmac_stat_node_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_stat_node_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_stat_node)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_register::pst_stat_node null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    OAL_MEMZERO(pst_stat_node, sizeof(dmac_stat_node_stru));

    /* 初始化stat_node的参数 */
    pst_stat_node->p_inner_func                     = p_func;
    pst_stat_node->uc_stat_flag                     = OAL_FALSE;
    pst_stat_node->us_total_item                    = DMAC_STAT_ITEM_LIMIT;
    pst_stat_node->us_curr_item                     = 0;

    for (uc_index = 0; uc_index < DMAC_STAT_PER_BUTT; uc_index++)
    {
        pst_stat_node->aul_stat_cnt[uc_index]   = 0;
        pst_stat_node->aul_stat_sum[uc_index]   = 0;
    }

    /* 为OAM_MODULE_ID_PERFORM_STAT模块申请存储空间 */
    if ( OAM_MODULE_ID_PERFORM_STAT == en_module_id)
    {
        pst_stat_node->pst_stat_param = (dmac_stat_param_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_stat_param_stru), OAL_TRUE);
        if (OAL_PTR_NULL == pst_stat_node->pst_stat_param)
        {
            /* 释放空间 */
            OAL_MEM_FREE(pst_stat_node, OAL_TRUE);
            pst_stat_node = OAL_PTR_NULL;

            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        if ((MAC_STAT_TYPE_TID_THRPT == en_stat_type)
            ||(MAC_STAT_TYPE_USER_THRPT == en_stat_type)
            ||(MAC_STAT_TYPE_VAP_THRPT == en_stat_type))
        {
            pst_stat_node->pul_stat_avg = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                    (DMAC_STAT_BUTT) * (DMAC_STAT_ITEM_LIMIT) * OAL_SIZEOF(oal_uint32), OAL_TRUE);
        }
        else
        {
            pst_stat_node->pul_stat_avg = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                        (DMAC_STAT_ITEM_LIMIT) * OAL_SIZEOF(oal_uint32), OAL_TRUE);
        }

        if (OAL_PTR_NULL == pst_stat_node->pul_stat_avg)
        {
            /* 释放空间 */
            OAL_MEM_FREE(pst_stat_node->pst_stat_param, OAL_TRUE);
            pst_stat_node->pst_stat_param = OAL_PTR_NULL;
            OAL_MEM_FREE(pst_stat_node, OAL_TRUE);
            pst_stat_node = OAL_PTR_NULL;

            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }
    }
    else
    {
        pst_stat_node->pst_stat_param = pst_output_param;
    }

    pst_stat_node->pst_stat_param->en_module_id       = en_module_id;
    pst_stat_node->pst_stat_param->en_stat_type       = en_stat_type;
    pst_stat_node->pst_stat_param->p_void             = p_void;

    /* 定时器参数赋值, 统计周期默认值设为100ms */
    pst_stat_node->st_timer.ul_timeout      = DMAC_STAT_TIMER_CYCLE_MS;
    pst_stat_node->st_timer.en_module_id    = en_module_id;

    /* 注册定时器 */
    FRW_TIMER_CREATE_TIMER(&(pst_stat_node->st_timer),
                            dmac_stat_timer_handler,
                            pst_stat_node->st_timer.ul_timeout,
                            (oal_void *)(pst_stat_node->pst_stat_param),
                            OAL_TRUE,
                            en_module_id,
                            ul_core_id);
    /* 将统计节点插入相应的链表 */
    oal_dlist_add_tail(&(pst_stat_node->st_entry), &(pst_stat->st_stat_node_dlist));
    pst_stat->ul_node_num++;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_unregister
 功能描述  : 注销统计节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32	dmac_stat_unregister(oam_module_id_enum_uint16      en_module_id,
                                 mac_stat_type_enum_uint8       en_stat_type,
                                 oal_void                      *p_void)
{
    oal_uint32               ul_ret             = OAL_SUCC;
    dmac_stat_node_stru     *pst_stat_node      = OAL_PTR_NULL;
    dmac_stat_stru          *pst_stat           = &(g_ast_pfm_stat[en_stat_type]);

    if (OAL_PTR_NULL == p_void)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_unregister::p_void null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 查找统计节点 */
    pst_stat_node = dmac_stat_search_node(&(pst_stat->st_stat_node_dlist), en_module_id, p_void);
    if (OAL_PTR_NULL == pst_stat_node)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_unregister::pst_stat_node null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 注销节点，包括注销定时器 */
    ul_ret = dmac_stat_unregister_node(pst_stat_node);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_stat_unregister::dmac_stat_unregister_node failed[%d].}", ul_ret);

        return ul_ret;
    }

    /*更新统计节点数量 */
    pst_stat->ul_node_num--;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_stat_start
 功能描述  : 停止stat_stat定时器
 输入参数  : en_module_id: 模块名称，如果没有，请添加；
             en_stat_type: 见结构体说明；
             us_stat_period: 统计周期;
             us_stat_num: 统计周期数量;
             p_void: 统计对象指针:dmac_tid_stru *, mac_user_stru *, mac_vap_stru *;
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32	dmac_stat_start( oam_module_id_enum_uint16      en_module_id,
                             mac_stat_type_enum_uint8       en_stat_type,
                             oal_uint16                     us_stat_period,
                             oal_uint16                     us_stat_num,
                             oal_void                      *p_void)
{
    dmac_stat_node_stru     *pst_stat_node      = OAL_PTR_NULL;
    dmac_stat_stru          *pst_stat           = &(g_ast_pfm_stat[en_stat_type]);
    oal_uint8                uc_cnt             = 0;

    if (OAL_PTR_NULL == p_void)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_start::p_void null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 查找相应的统计节点 */
    pst_stat_node = dmac_stat_search_node(&(pst_stat->st_stat_node_dlist), en_module_id, p_void);
    if (OAL_PTR_NULL == pst_stat_node)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_start::pst_stat_node null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 初始化相关统计量 */
    pst_stat_node->uc_stat_flag                 = OAL_TRUE;
    pst_stat_node->us_total_item                = OAL_MIN(us_stat_num, DMAC_STAT_ITEM_LIMIT);
    pst_stat_node->us_curr_item                 = 0;

    for (uc_cnt = 0; uc_cnt < DMAC_STAT_PER_BUTT; uc_cnt++)
    {
        pst_stat_node->aul_stat_cnt[uc_cnt]   = 0;
        pst_stat_node->aul_stat_sum[uc_cnt]   = 0;
    }

    /* 给OAM_MODULE_ID_PERFORM_STAT模块初始化内存，以便重新统计 */
    if ( OAM_MODULE_ID_PERFORM_STAT == en_module_id)
    {
        if ((MAC_STAT_TYPE_TID_THRPT == en_stat_type)
            ||(MAC_STAT_TYPE_USER_THRPT == en_stat_type)
            ||(MAC_STAT_TYPE_VAP_THRPT == en_stat_type))
        {
            OAL_MEMZERO(pst_stat_node->pul_stat_avg, ((DMAC_STAT_BUTT) * (DMAC_STAT_ITEM_LIMIT) * OAL_SIZEOF(oal_uint32)));
        }
        else
        {
            OAL_MEMZERO(pst_stat_node->pul_stat_avg, ((DMAC_STAT_ITEM_LIMIT) * OAL_SIZEOF(oal_uint32)));
        }
    }

    pst_stat_node->st_timer.ul_timeout  = us_stat_period;

    frw_timer_restart_timer(&(pst_stat_node->st_timer),
                              pst_stat_node->st_timer.ul_timeout,
                              OAL_TRUE);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_stop
 功能描述  : 启动stat定时器，开始统计
 输入参数  : en_module_id:模块名称
             en_stat_type: 统计类型；
             p_void: 统计对象指针:dmac_tid_stru *, mac_user_stru *, mac_vap_stru *;
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32	dmac_stat_stop(oam_module_id_enum_uint16      en_module_id,
                             mac_stat_type_enum_uint8     en_stat_type,
                             oal_void                    *p_void)
{
    dmac_stat_node_stru     *pst_stat_node      = OAL_PTR_NULL;
    dmac_stat_stru          *pst_stat           = &(g_ast_pfm_stat[en_stat_type]);

    if (OAL_PTR_NULL == p_void)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_stop::p_void null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_stat_node = dmac_stat_search_node(&(pst_stat->st_stat_node_dlist), en_module_id, p_void);
    if (OAL_PTR_NULL == pst_stat_node)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_stop::pst_stat_node null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    frw_timer_stop_timer(&(pst_stat_node->st_timer));

    /* 该节点停止统计 */
    pst_stat_node->uc_stat_flag = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_tid_delay
 功能描述  : 根据每次调度结果统计时延
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_stat_tid_delay(dmac_tid_stru *pst_dmac_tid)
{
    dmac_stat_stru          *pst_stat           = &(g_ast_pfm_stat[MAC_STAT_TYPE_TID_DELAY]);
    oal_dlist_head_stru     *pst_dlist_pos      = OAL_PTR_NULL;
    dmac_stat_node_stru     *pst_stat_node      = OAL_PTR_NULL;
    oal_netbuf_stru         *pst_netbuf         = OAL_PTR_NULL;
    oal_uint32               ul_diff_time_us    = 0;
    oal_uint16               us_delay_ms        = 0;
    mac_tx_ctl_stru         *pst_tx_ctl         = OAL_PTR_NULL;
    hal_tx_dscr_stru        *pst_dscr           = OAL_PTR_NULL;
    oal_dlist_head_stru     *pst_dscr_entry     = OAL_PTR_NULL;
    oal_time_us_stru         st_time;

    if (OAL_PTR_NULL == pst_dmac_tid)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_tid_delay::pst_dmac_tid null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    if (OAL_FALSE == oal_dlist_is_empty(&pst_dmac_tid->st_retry_q))
    {
        pst_dscr_entry = pst_dmac_tid->st_retry_q.pst_next;

        pst_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        pst_netbuf = pst_dscr->pst_skb_start_addr;
    }
    else if (OAL_FALSE == oal_netbuf_list_empty(&pst_dmac_tid->st_buff_head))
    {
        pst_netbuf = pst_dmac_tid->st_buff_head.pst_next;
    }
    else
    {
        return OAL_FAIL;
    }
#else
    if (oal_dlist_is_empty(&pst_dmac_tid->st_hdr))
    {
        return OAL_FAIL;
    }

    pst_dscr_entry = pst_dmac_tid->st_hdr.pst_next;

    pst_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
    pst_netbuf = pst_dscr->pst_skb_start_addr;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

    pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);

    /* 获取系统时间 */
    oal_time_get_stamp_us(&st_time);

    /* 计算报文的等待时延 */
    ul_diff_time_us = (oal_uint32)DMAC_STAT_TIME_USEC_DIFF(&(MAC_GET_CB_TIMESTAMP(pst_tx_ctl)), &st_time);
    us_delay_ms = (oal_uint16) (ul_diff_time_us >> 10);

    /* 遍列该统计类型的所有统计节点 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &(pst_stat->st_stat_node_dlist))
    {
        pst_stat_node = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_stat_node_stru, st_entry);

        if (((oal_void *)pst_dmac_tid == pst_stat_node->pst_stat_param->p_void)
            && (OAL_TRUE == pst_stat_node->uc_stat_flag))
        {
            pst_stat_node->aul_stat_cnt[DMAC_STAT_TX]++;
            pst_stat_node->aul_stat_sum[DMAC_STAT_TX] += us_delay_ms;

            return OAL_SUCC;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_tid_per
 功能描述  : 根据每次发送完成中断结果，统计per
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_stat_tid_per(mac_user_stru *pst_user,
                             oal_uint8 uc_tidno,
                             oal_uint16 us_mpdu_num,
                             oal_uint16 us_err_mpdu_num,
                             dmac_stat_per_reason_enum_uint8 en_per_reason)
{
    dmac_stat_stru          *pst_stat           = &(g_ast_pfm_stat[MAC_STAT_TYPE_TID_PER]);
    oal_dlist_head_stru     *pst_dlist_pos      = OAL_PTR_NULL;
    dmac_stat_node_stru     *pst_stat_node      = OAL_PTR_NULL;
    dmac_tid_stru           *pst_tid            = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_tid_per::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_user_get_tid_by_num(pst_user, uc_tidno, &pst_tid);

    /* video报文丢弃，增加日志打印 */
    if ((WLAN_TIDNO_VIDEO == pst_tid->uc_tid)
            && (en_per_reason != DMAC_STAT_PER_MAC_TOTAL)
            && (0 != us_err_mpdu_num))
    {
        switch(en_per_reason)
        {
            case DMAC_STAT_PER_BUFF_OVERFLOW:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video drop!!!, reason = %d(buff_overflow), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            case DMAC_STAT_PER_BUFF_BE_SEIZED:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video drop!!!, reason = %d(vi_be_seized), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            case DMAC_STAT_PER_DELAY_OVERTIME:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video drop!!!, reason = %d(vi_overtime), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            case DMAC_STAT_PER_SW_RETRY_AMPDU:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video pkt drop!!!, reason = %d(whole ampdu failed), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            case DMAC_STAT_PER_SW_RETRY_SUB_AMPDU:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video pkt drop!!!, reason = %d(ampdu's sub_mpdu failed), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            case DMAC_STAT_PER_SW_RETRY_MPDU:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video pkt drop!!!, reason = %d(non_ampdu mpdu failed), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            case DMAC_STAT_PER_SW_RETRY_OVERFLOW:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video pkt drop!!!, reason = %d(retry mpdu re_insert failed), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            case DMAC_STAT_PER_RTS_FAIL:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video pkt drop!!!, reason = %d(rts_fail), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            case DMAC_STAT_PER_HW_SW_FAIL:
                OAM_INFO_LOG2(0, OAM_SF_ANY, "{video pkt drop!!!, reason = %d(hw_sw_fail), drop_num = %d}", en_per_reason, us_err_mpdu_num);
                break;
            default:
                OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_stat_tid_per::unknown stat_per_reaion type.}");
        }
    }

    /* 遍列该统计类型的所有统计节点 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &(pst_stat->st_stat_node_dlist))
    {
        pst_stat_node = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_stat_node_stru, st_entry);

        if ((pst_tid == pst_stat_node->pst_stat_param->p_void)
            && (OAL_TRUE == pst_stat_node->uc_stat_flag))
        {
            switch (en_per_reason)
            {
                case DMAC_STAT_PER_MAC_TOTAL:
                case DMAC_STAT_PER_BUFF_OVERFLOW:
                case DMAC_STAT_PER_RTS_FAIL:
                case DMAC_STAT_PER_HW_SW_FAIL:
                    pst_stat_node->aul_stat_cnt[en_per_reason] += us_mpdu_num;
                    pst_stat_node->aul_stat_sum[en_per_reason] += us_err_mpdu_num;
                    break;

                case DMAC_STAT_PER_BUFF_BE_SEIZED:
                case DMAC_STAT_PER_DELAY_OVERTIME:
                case DMAC_STAT_PER_SW_RETRY_AMPDU:
                case DMAC_STAT_PER_SW_RETRY_SUB_AMPDU:
                case DMAC_STAT_PER_SW_RETRY_MPDU:
                case DMAC_STAT_PER_SW_RETRY_OVERFLOW:
                    pst_stat_node->aul_stat_sum[en_per_reason] += us_err_mpdu_num;
                    break;

                default:
                    OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_tid_per::wrong stat_per_reason type.}");
                    return OAL_FAIL;
            }
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_stat_tx_thrpt
 功能描述  : 根据每次发送完成中断结果统计吞吐量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_stat_tx_thrpt(dmac_user_stru *pst_dmac_user, oal_uint8 uc_tidno, hal_tx_dscr_ctrl_one_param st_tx_dscr_param)
{
    dmac_tid_stru               *pst_tid            = OAL_PTR_NULL;
    mac_vap_stru                *pst_vap            = OAL_PTR_NULL;
    mac_user_stru               *pst_user           = OAL_PTR_NULL;
    oal_uint32                   ul_ret             = 0;
    oal_uint32                   ul_stat_bytes      = 0;

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_tx_thrpt::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tidno]);

    pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_tid->uc_vap_id);

    pst_user = (mac_user_stru *)(&(pst_dmac_user->st_user_base_info));

    ul_stat_bytes = st_tx_dscr_param.us_mpdu_len
                        * (st_tx_dscr_param.uc_mpdu_num - st_tx_dscr_param.uc_error_mpdu_num);

    /* 更新统计量 */
    ul_ret = dmac_stat_update_thrpt(pst_vap, pst_user, pst_tid,
                                            ul_stat_bytes, DMAC_STAT_TX);

    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_RX, "{dmac_stat_tx_thrpt::dmac_stat_update_thrpt failed[%d].}", ul_ret);

        return ul_ret;

    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_stat_rx_thrpt
 功能描述  : 根据每次接收完成中断统计吞吐量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_stat_rx_thrpt(frw_event_hdr_stru *pst_event_hdr, mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_rx_ctl)
{
    dmac_user_stru             *pst_dmac_user   = OAL_PTR_NULL;
	mac_user_stru			   *pst_mac_user	= OAL_PTR_NULL;
    dmac_tid_stru              *pst_tid         = OAL_PTR_NULL;
    oal_uint32                  ul_ret          = OAL_SUCC;
    oal_uint8                   uc_tidno;

    if ((OAL_PTR_NULL == pst_event_hdr) || (OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_rx_ctl))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_stat_rx_thrpt::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 管理帧不需要统计 */
    if (FRW_EVENT_TYPE_WLAN_DRX != pst_event_hdr->en_type)
    {
        return OAL_SUCC;
    }

    /* 获取用户、帧信息 */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&pst_rx_ctl->st_rx_info));
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_stat_rx_thrpt::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

	/* 广播用户不需要统计 */
	pst_mac_user  = (mac_user_stru *)(&(pst_dmac_user->st_user_base_info));
	if (OAL_TRUE == pst_mac_user->en_is_multi_user)
	{
		return OAL_SUCC;
	}

    /* 获取接收报文的tidno */
	ul_ret = dmac_stat_get_rx_tid(pst_vap, pst_rx_ctl, &uc_tidno);
	if (OAL_SUCC != ul_ret)
	{
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_stat_rx_thrpt::dmac_stat_get_rx_tid failed[%d].}", ul_ret);

        return ul_ret;
	}

    pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tidno]);

    /* 更新统计量 */
    ul_ret = dmac_stat_update_thrpt(pst_vap, pst_mac_user, pst_tid,
                                (oal_uint32)pst_rx_ctl->st_rx_info.us_frame_len, DMAC_STAT_RX);

    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_stat_rx_thrpt::dmac_stat_update_thrpt failed[%d].}", ul_ret);

        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_update_thrpt
 功能描述  : 更新发送或者接收吞吐量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_stat_update_thrpt(mac_vap_stru *pst_vap,
                                              mac_user_stru *pst_user,
                                              dmac_tid_stru *pst_tid,
                                              oal_uint32     ul_stat_bytes,
                                              dmac_stat_direct_enum_uint8 en_stat_direct)
{
    oal_uint8                uc_stat_type    = 0;
    oal_void                *p_void          = OAL_PTR_NULL;
    dmac_stat_stru          *pst_stat        = OAL_PTR_NULL;
    oal_dlist_head_stru     *pst_dlist_pos   = OAL_PTR_NULL;
    dmac_stat_node_stru     *pst_stat_node   = OAL_PTR_NULL;

    for (uc_stat_type = MAC_STAT_TYPE_TID_THRPT; uc_stat_type <= MAC_STAT_TYPE_VAP_THRPT; uc_stat_type++)
    {
        /* 根据统计类型的不同，对p_void进行赋值 */
        if (MAC_STAT_TYPE_TID_THRPT == uc_stat_type)
        {
            p_void = (oal_void *)pst_tid;
        }
        else if (MAC_STAT_TYPE_USER_THRPT == uc_stat_type)
        {
            p_void = (oal_void *)pst_user;
        }
        else if (MAC_STAT_TYPE_VAP_THRPT == uc_stat_type)
        {
            p_void = (oal_void *)pst_vap;
        }

        pst_stat = &(g_ast_pfm_stat[uc_stat_type]);

        /* 遍列该统计类型的所有统计节点 */
        OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &(pst_stat->st_stat_node_dlist))
        {
            pst_stat_node = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_stat_node_stru, st_entry);

            if ((p_void == pst_stat_node->pst_stat_param->p_void))
            {
                pst_stat_node->aul_stat_cnt[en_stat_direct]++;
                pst_stat_node->aul_stat_sum[en_stat_direct] += ul_stat_bytes;

                pst_stat_node->aul_stat_cnt[DMAC_STAT_BOTH]++;
                pst_stat_node->aul_stat_sum[DMAC_STAT_BOTH] += ul_stat_bytes;

                return OAL_SUCC;
            }
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_stat_get_rx_tid
 功能描述  : 停止stat_stat定时器
 输入参数  :
 输出参数  :
 返 回 值  : 如果找到，则返回OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_stat_get_rx_tid(mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_rx_ctl, oal_uint8 *puc_tidno)
{
    mac_ieee80211_frame_stru   *pst_frame_hdr   = OAL_PTR_NULL;
    oal_bool_enum_uint8         en_is_4addr;
    oal_uint8                   uc_is_tods;
    oal_uint8                   uc_is_from_ds;

    if ((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_rx_ctl) || (OAL_PTR_NULL == puc_tidno))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_stat_get_rx_tid::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&pst_rx_ctl->st_rx_info);

    if (OAL_PTR_NULL == pst_frame_hdr)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_stat_get_rx_tid::pst_frame_hdr null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 如果 该vap不是ht，或者该帧不是qos帧， 或者该帧是组播，则tid直接标记为be
       否则，则根据qos获取tid号 */
    if ((OAL_FALSE == pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
        ||((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
        ||(mac_is_grp_addr((oal_uint8 *)pst_frame_hdr)))
    {
        *puc_tidno = WLAN_TIDNO_BEST_EFFORT;
    }
    else
    {
        /* 考虑四地址情况获取报文的tid */
        uc_is_tods    = mac_hdr_get_to_ds((oal_uint8 *)pst_frame_hdr);
        uc_is_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_frame_hdr);
        en_is_4addr   = uc_is_tods && uc_is_from_ds;

        *puc_tidno = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_search_node
 功能描述  : 停止stat_stat定时器
 输入参数  : pst_node_dlist_head:统计节点指针
             p_void:统计节点的tid,user或者vap的指针；
 输出参数  : pst_stat_node:找到的统计节点，如果为空，表示没有找到
 返 回 值  : 如果找到，则返回OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC dmac_stat_node_stru* dmac_stat_search_node(oal_dlist_head_stru        *pst_node_dlist_head,
                                                      oam_module_id_enum_uint16   en_module_id,
                                                      oal_void                   *p_void)
{
    oal_dlist_head_stru     *pst_dlist_pos      = OAL_PTR_NULL;
    dmac_stat_node_stru     *pst_stat_node      = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == pst_node_dlist_head) || (OAL_PTR_NULL == p_void))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_search_node::param null.}");

        return OAL_PTR_NULL;
    }

    if (OAL_TRUE == oal_dlist_is_empty(pst_node_dlist_head))
    {
        return OAL_PTR_NULL;
    }

    /* 查找对应的统计节点 */
    OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, pst_node_dlist_head)
    {
        pst_stat_node = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_stat_node_stru, st_entry);

        if ((p_void == pst_stat_node->pst_stat_param->p_void) && (en_module_id == pst_stat_node->pst_stat_param->en_module_id))
        {
            return pst_stat_node;
        }
    }

    /* 没有找到，则返回空指针 */
    return OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : dmac_stat_display
 功能描述  : 显示统计结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32	dmac_stat_display(oam_module_id_enum_uint16         en_module_id,
                                 mac_stat_type_enum_uint8       en_stat_type,
                                 oal_void                      *p_void)
{
    dmac_stat_node_stru         *pst_stat_node      = OAL_PTR_NULL;
    dmac_stat_stru              *pst_stat           = &(g_ast_pfm_stat[en_stat_type]);
    oal_uint32                   ul_ret             = OAL_SUCC;
    oam_output_type_enum_uint8   en_output_type     = OAM_OUTPUT_TYPE_BUTT;

    /* 查找统计节点 */
    pst_stat_node = dmac_stat_search_node(&(pst_stat->st_stat_node_dlist), en_module_id, p_void);
    if (OAL_PTR_NULL == pst_stat_node)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_display::pst_stat_nodenull.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 停止定时器 */
    frw_timer_stop_timer(&(pst_stat_node->st_timer));

    /* 从oam模块获取输出方式 */
    ul_ret = oam_get_output_type(&en_output_type);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    ul_ret = dmac_stat_print(pst_stat_node, en_output_type);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_stat_unregister_node
 功能描述  : 注销某个节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32	dmac_stat_unregister_node(dmac_stat_node_stru   *pst_stat_node)
{
    if (OAL_PTR_NULL == pst_stat_node)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_unregister_node::ps_stat_node null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 注销定时器 */
    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_stat_node->st_timer));

    /* 从链表中删除该节点 */
    oal_dlist_delete_entry(&(pst_stat_node->st_entry));

    /* 释放存储统计值的内存空间 */
    if (OAM_MODULE_ID_PERFORM_STAT == pst_stat_node->pst_stat_param->en_module_id)
    {
        OAL_MEM_FREE(pst_stat_node->pul_stat_avg, OAL_TRUE);

        OAL_MEM_FREE(pst_stat_node->pst_stat_param, OAL_TRUE);
    }

    /* 注销统计节点 */
    OAL_MEM_FREE(pst_stat_node, OAL_TRUE);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_stat_timer_handler
 功能描述  : 定时器到期处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化成功或返回其他错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月10日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32	dmac_stat_timer_handler(oal_void * p_void)
{
    dmac_stat_param_stru    *pst_stat_param     = OAL_PTR_NULL;
    dmac_stat_node_stru     *pst_stat_node      = OAL_PTR_NULL;
    dmac_stat_stru          *pst_stat           = OAL_PTR_NULL;
    oal_uint32               ul_index           = 0;
    oal_uint8                uc_cnt             = 0;

    if (OAL_PTR_NULL == p_void)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_timer_handler::p_void null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_stat_param = (dmac_stat_param_stru *)(p_void);
    pst_stat       = &(g_ast_pfm_stat[pst_stat_param->en_stat_type]);

    /* 查找统计节点 */
    pst_stat_node = dmac_stat_search_node(&(pst_stat->st_stat_node_dlist), pst_stat_param->en_module_id, pst_stat_param->p_void);

    /* 更新统计量 */
    pst_stat_node->us_curr_item++;

    /* 根据统计类型更新统计量 */
    switch (pst_stat_param->en_stat_type)
    {
        case MAC_STAT_TYPE_TID_DELAY:
            pst_stat_param->aul_stat_avg[DMAC_STAT_TX]= pst_stat_node->aul_stat_cnt[DMAC_STAT_TX] ?
                (10 * pst_stat_node->aul_stat_sum[DMAC_STAT_TX] / pst_stat_node->aul_stat_cnt[DMAC_STAT_TX]) : 0;
            break;

        case MAC_STAT_TYPE_TID_PER:

            /* 统计mac层per */
            pst_stat_param->aul_stat_avg[DMAC_STAT_PER_MAC_TOTAL] = pst_stat_node->aul_stat_cnt[DMAC_STAT_PER_MAC_TOTAL] ?
                (10000 * pst_stat_node->aul_stat_sum[DMAC_STAT_PER_MAC_TOTAL] / pst_stat_node->aul_stat_cnt[DMAC_STAT_PER_MAC_TOTAL]) : 0;

            /* 分类统计各种原因导致的per */
            for (uc_cnt = DMAC_STAT_PER_BUFF_OVERFLOW; uc_cnt < DMAC_STAT_PER_RTS_FAIL; uc_cnt++)
            {
                if (0 == pst_stat_node->aul_stat_cnt[DMAC_STAT_PER_BUFF_OVERFLOW])
                {
                    pst_stat_param->aul_stat_avg[uc_cnt] = 0;
                }
                else
                {
                    pst_stat_param->aul_stat_avg[uc_cnt] = (10000 * pst_stat_node->aul_stat_sum[uc_cnt]) / pst_stat_node->aul_stat_cnt[DMAC_STAT_PER_BUFF_OVERFLOW];
                }
            }

            /* 统计硬件RTS发送失败情况，统计硬件重传和软件重传对应的数据帧失败情况 */
            for (uc_cnt = DMAC_STAT_PER_RTS_FAIL; uc_cnt < DMAC_STAT_PER_BUTT; uc_cnt++)
            {
                pst_stat_param->aul_stat_avg[uc_cnt] = pst_stat_node->aul_stat_cnt[uc_cnt] ?
                    (10000 * pst_stat_node->aul_stat_sum[uc_cnt] / pst_stat_node->aul_stat_cnt[uc_cnt]) : 0;
            }

            OAM_ERROR_LOG4(0, OAM_SF_ANY, "IP_layer stat1: ip_total = %d, ip_err_of = %d, ip_err_sz = %d, ip_err_ot = %d",
                                pst_stat_node->aul_stat_cnt[DMAC_STAT_PER_BUFF_OVERFLOW],
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_BUFF_OVERFLOW],
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_BUFF_BE_SEIZED],
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_DELAY_OVERTIME]);

            OAM_ERROR_LOG4(0, OAM_SF_ANY, "IP_layer stat2: ip_err_sw_ampdu = %d, ip_err_sw_sub_ampdu = %d, ip_err_sw_mpdu = %d, ip_err_sw_rt_of = %d",
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_SW_RETRY_AMPDU],
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_SW_RETRY_SUB_AMPDU],
								pst_stat_node->aul_stat_sum[DMAC_STAT_PER_SW_RETRY_MPDU],
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_SW_RETRY_OVERFLOW]);

            OAM_ERROR_LOG4(0, OAM_SF_ANY, "MAC_layer stat: mac_total(sw) = %d, mac_err_total(sw) = %d, mac_total(hw&sw) = %d, mac_err_total(hw&sw) = %d",
                                pst_stat_node->aul_stat_cnt[DMAC_STAT_PER_MAC_TOTAL],
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_MAC_TOTAL],
                                pst_stat_node->aul_stat_cnt[DMAC_STAT_PER_HW_SW_FAIL],
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_HW_SW_FAIL]);

            OAM_ERROR_LOG2(0, OAM_SF_ANY, "MAC_layer stat: rts_total = %d, rts_fail = %d",
                                pst_stat_node->aul_stat_cnt[DMAC_STAT_PER_RTS_FAIL],
                                pst_stat_node->aul_stat_sum[DMAC_STAT_PER_RTS_FAIL]);
            break;

        case MAC_STAT_TYPE_TID_THRPT:
        case MAC_STAT_TYPE_USER_THRPT:
        case MAC_STAT_TYPE_VAP_THRPT:
            if(0 != pst_stat_node->st_timer.ul_timeout)
            {
                pst_stat_param->aul_stat_avg[DMAC_STAT_TX]     = 8 * pst_stat_node->aul_stat_sum[DMAC_STAT_TX] / pst_stat_node->st_timer.ul_timeout;
                pst_stat_param->aul_stat_avg[DMAC_STAT_RX]     = 8 * pst_stat_node->aul_stat_sum[DMAC_STAT_RX] / pst_stat_node->st_timer.ul_timeout;
                pst_stat_param->aul_stat_avg[DMAC_STAT_BOTH]   = 8 * pst_stat_node->aul_stat_sum[DMAC_STAT_BOTH] / pst_stat_node->st_timer.ul_timeout;
            }
            else
            {
                OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_stat_timer_handler: Error! 0 == timeout!");
                pst_stat_param->aul_stat_avg[DMAC_STAT_TX] = 0;
                pst_stat_param->aul_stat_avg[DMAC_STAT_RX] = 0;
                pst_stat_param->aul_stat_avg[DMAC_STAT_BOTH] = 0;
            }
            break;

        default:
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_timer_handler::invalid en_stat_type.}");

            return OAL_FAIL;
    }

    /* 如果为命令配置模块，则更新至内部存储空间 */
    if (OAM_MODULE_ID_PERFORM_STAT == pst_stat_param->en_module_id)
    {
        ul_index = pst_stat_node->us_curr_item - 1;

        if ((MAC_STAT_TYPE_TID_THRPT == pst_stat_param->en_stat_type)
            ||(MAC_STAT_TYPE_USER_THRPT == pst_stat_param->en_stat_type)
            ||(MAC_STAT_TYPE_VAP_THRPT == pst_stat_param->en_stat_type))
        {
            for (uc_cnt = 0; uc_cnt <= DMAC_STAT_BOTH; uc_cnt++)
            {
                *(pst_stat_node->pul_stat_avg + ul_index + uc_cnt * DMAC_STAT_ITEM_LIMIT) = pst_stat_param->aul_stat_avg[uc_cnt];
            }
        }
        else if (MAC_STAT_TYPE_TID_PER == pst_stat_param->en_stat_type)
        {
            for (uc_cnt = 0; uc_cnt < DMAC_STAT_PER_BUTT; uc_cnt++)
            {
                *(pst_stat_node->pul_stat_avg + ul_index + uc_cnt * DMAC_STAT_ITEM_LIMIT) = pst_stat_param->aul_stat_avg[uc_cnt];
            }
        }
        else
        {
            *(pst_stat_node->pul_stat_avg + ul_index) = pst_stat_param->aul_stat_avg[0];
        }
    }
    else    /* 调用相应的处理函数 */
    {
        pst_stat_node->p_inner_func(pst_stat_param);
    }

    /* 该周期内的统计参数清零 */
    for (uc_cnt = 0; uc_cnt < DMAC_STAT_PER_BUTT; uc_cnt++)
    {
        pst_stat_node->aul_stat_cnt[uc_cnt]   = 0;
        pst_stat_node->aul_stat_sum[uc_cnt]   = 0;
    }

    /* 统计结束 */
    if (pst_stat_node->us_curr_item >= pst_stat_node->us_total_item)
    {
        frw_timer_stop_timer(&(pst_stat_node->st_timer));
        pst_stat_node->uc_stat_flag = OAL_FALSE;
        return OAL_SUCC;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stat_format_title_string
 功能描述  : 将数据信息格式化
 输入参数  :
 输出参数  : 无
 返 回 值  : 函数返回成功或其他错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_stat_format_title_string(oal_int8                  *pac_output_data,
                                                      oal_uint16                 ul_data_len,
                                                      dmac_stat_node_stru       *pst_stat_node)
{
    switch (pst_stat_node->pst_stat_param->en_stat_type)
    {
        case MAC_STAT_TYPE_TID_PER:

            /* 格式化输出tid per统计信息 */
            OAL_SPRINTF(pac_output_data,
                        ul_data_len,
                        "stat_num=%u,stat_period(ms)=%u,start_time =%u\r\n%15s%15s%15s%15s%15s%15s%15s%15s%15s%15s%15s\r\n",
                        pst_stat_node->us_total_item,
                        pst_stat_node->st_timer.ul_timeout,
                        pst_stat_node->st_timer.ul_time_stamp,
                        "idx",
                        "mac_per(10^-4)",
                        "overflow_per",
                        "seize_per",
                        "overtime_per",
                        "sw_per_ampdu",
                        "sw_per_sub",
                        "sw_per_mpdu",
						"sw_overf_per",
						"rts_fail",
						"mac_per(sw&hw)");
            break;

        case MAC_STAT_TYPE_TID_DELAY:

            /* 格式化输出tid delay统计信息 */
            OAL_SPRINTF(pac_output_data,
                        ul_data_len,
                        "stat_num=%u,stat_period(ms)=%u,start_time=%u\r\n%15s%15s\r\n",
                        pst_stat_node->us_total_item,
                        pst_stat_node->st_timer.ul_timeout,
                        pst_stat_node->st_timer.ul_time_stamp,
                        "index",
                        "delay(0.1ms)");

            break;

        case MAC_STAT_TYPE_TID_THRPT:
        case MAC_STAT_TYPE_USER_THRPT:
        case MAC_STAT_TYPE_VAP_THRPT:

            /* 格式化输出吞吐量统计信息 */
            OAL_SPRINTF(pac_output_data,
                        ul_data_len,
                        "stat_num=%u,stat_period=%u,start_time=%15u\r\n%15s%15s%15s%15s\r\n",
                        pst_stat_node->us_total_item,
                        pst_stat_node->st_timer.ul_timeout,
                        pst_stat_node->st_timer.ul_time_stamp,
                        "index",
                        "tx(kbps)",
                        "rx(kbps)",
                        "total(kbps)");

            break;

        default:
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_format_title_string::invalid en_stat_type.}");

            return OAL_FAIL;
    }
    return OAL_SUCC;

}


/*****************************************************************************
 函 数 名  : dmac_stat_format_data_string
 功能描述  : 将打印信息格式化
 输入参数  :
 输出参数  : 无
 返 回 值  : 函数返回成功或其他错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_stat_format_data_string(oal_int8                  *pac_output_data,
                                                     oal_uint16                 ul_data_len,
                                                     mac_stat_type_enum_uint8   en_stat_type,
                                                     oal_uint32                 ul_index,
                                                     oal_uint32                *pul_data)
{
    switch (en_stat_type)
    {
        case MAC_STAT_TYPE_TID_THRPT:
        case MAC_STAT_TYPE_USER_THRPT:
        case MAC_STAT_TYPE_VAP_THRPT:
            /* 格式化输出吞吐量信息 */
            OAL_SPRINTF(pac_output_data,
                        ul_data_len,
                        "%15u%15u%15u%15u\r\n",
                        ul_index,
                        *(pul_data),
                        *(pul_data + DMAC_STAT_ITEM_LIMIT),
                        *(pul_data + 2 * DMAC_STAT_ITEM_LIMIT));
            break;
        case MAC_STAT_TYPE_TID_DELAY:
            /* 格式化输tid delay,per信息 */
            OAL_SPRINTF(pac_output_data,
                        ul_data_len,
                        "%15u%15u\r\n",
                        ul_index,
                        *(pul_data));
            break;
        case MAC_STAT_TYPE_TID_PER:
            /* 格式化输出吞吐量信息 */
            OAL_SPRINTF(pac_output_data,
                        ul_data_len,
                        "%15u%15u%15u%15u%15u%15u%15u%15u%15u%15u%15u\r\n",
                        ul_index,
                        *(pul_data),
                        *(pul_data + 1 * DMAC_STAT_ITEM_LIMIT),
                        *(pul_data + 2 * DMAC_STAT_ITEM_LIMIT),
                        *(pul_data + 3 * DMAC_STAT_ITEM_LIMIT),
                        *(pul_data + 4 * DMAC_STAT_ITEM_LIMIT),
						*(pul_data + 5 * DMAC_STAT_ITEM_LIMIT),
						*(pul_data + 6 * DMAC_STAT_ITEM_LIMIT),
						*(pul_data + 7 * DMAC_STAT_ITEM_LIMIT),
						*(pul_data + 8 * DMAC_STAT_ITEM_LIMIT),
						*(pul_data + 9 * DMAC_STAT_ITEM_LIMIT));
            break;
        default:
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_format_data_string::invalid en_stat_type.}");
            return OAL_FAIL;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_stat_print
 功能描述  : 将性能统计信息用不同的方式进行输出
 输入参数  :
 输出参数  : 无
 返 回 值  : 函数返回成功或其他错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_stat_print(dmac_stat_node_stru     *pst_stat_node,
                                       oam_output_type_enum_uint8 en_output_type)
{
    oal_uint32              ul_ret              = OAL_SUCC;
    oal_uint16              us_index            = 0;

    oal_int8                ac_output_data[OAM_PRINT_FORMAT_LENGTH];

    if (OAL_PTR_NULL == pst_stat_node)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_stat_print_to_std::pst_stat_node null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 格式化抬头信息 */
    ul_ret = dmac_stat_format_title_string(ac_output_data,
                                           OAM_PRINT_FORMAT_LENGTH,
                                           pst_stat_node);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /* 根据输出方式进行输出 */
    switch (en_output_type)
    {
        /* 输出至控制台 */
        case OAM_OUTPUT_TYPE_CONSOLE:
            OAL_IO_PRINT("%s\r\n", ac_output_data);
            break;

        /* 输出至PC侧调测工具平台 */
        case OAM_OUTPUT_TYPE_SDT:
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            oam_print(ac_output_data);
#endif
            break;

        /* 无效配置 */
        default:
            ul_ret = OAL_ERR_CODE_INVALID_CONFIG;
			return ul_ret;
    }

    /* 打印所有的统计数据 */
    for (us_index = 0; us_index < pst_stat_node->us_total_item; us_index++)
    {
        ul_ret = dmac_stat_format_data_string(ac_output_data,
                                               OAM_PRINT_FORMAT_LENGTH,
                                               pst_stat_node->pst_stat_param->en_stat_type,
                                               us_index,
                                               pst_stat_node->pul_stat_avg + us_index);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }

        /* 根据输出方式进行输出 */
        switch (en_output_type)
        {
            /* 输出至控制台 */
            case OAM_OUTPUT_TYPE_CONSOLE:
                OAL_IO_PRINT("%s\r\n", ac_output_data);
                break;

            /* 输出至PC侧调测工具平台 */
            case OAM_OUTPUT_TYPE_SDT:
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
                oam_print(ac_output_data);
#endif
        }
    }

    return ul_ret;
}

/*lint -e19*/
oal_module_symbol(dmac_stat_register);
oal_module_symbol(dmac_stat_unregister);
oal_module_symbol(dmac_stat_start);
oal_module_symbol(dmac_stat_stop);
oal_module_symbol(dmac_stat_tid_per);
/*lint +e19*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

