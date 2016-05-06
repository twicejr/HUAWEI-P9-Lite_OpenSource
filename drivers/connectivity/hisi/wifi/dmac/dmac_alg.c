/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_alg.c
  版 本 号   : 初稿
  作    者   : 陈艳
  生成日期   : 2013年3月21日
  最近修改   :
  功能描述   : 算法编程框架
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月21日
    作    者   : 陈艳
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "dmac_alg.h"
#include "dmac_config.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ALG_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* 算法框架主结构体 */
dmac_alg_stru  gst_alg_main;

/* 算法配置命令 */
dmac_alg_config_table_stru g_ast_dmac_alg_config_table[] =
{
#ifdef _PRE_WLAN_FEATURE_DBAC
    {"dbac",        DMAC_ALG_CONFIG_ID_DBAC},
#endif

#ifdef _PRE_WLAN_FEATURE_SCHEDULE
    {"sch",         DMAC_ALG_CONFIG_ID_SCH},
#endif

#ifdef _PRE_WLAN_FEATURE_TRAFFIC_CTL
    {"tfctl",      DMAC_ALG_CONFIG_ID_TRAFF_CTL},
#endif

#ifdef _PRE_WLAN_CHIP_TEST_ALG
    {"txbf",        DMAC_ALG_CONFIG_ID_TXBF},
    {"test",        DMAC_ALG_CONFIG_ID_TEST_MAIN},
    {"dbac_ct",     DMAC_ALG_CONFIG_ID_DBAC_TEST},
    {"ar_test",     DMAC_ALG_CONFIG_ID_AUTORATE_TEST},
    {"ant_test",    DMAC_ALG_CONFIG_ID_SMARTANT_TEST},
    {"rssi_test",   DMAC_ALG_CONFIG_ID_RSSI_TEST},
    {"tpc_test",    DMAC_ALG_CONFIG_ID_TPC_TEST},
#endif

    {"cmn",         DMAC_ALG_CONFIG_ID_COMMON},
    {"err_name",    DMAC_ALG_CONFIG_ID_ERROR}
};

#ifdef _PRE_WLAN_FEATURE_DBAC
extern frw_event_sub_table_item_stru g_ast_dmac_misc_event_sub_table[];
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
oal_uint32 gul_dmac_alg_pktno = 0;
#else
oal_uint8 guc_dmac_alg_pktno = 0;
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_alg_free_tid_priv_stru
 功能描述  : 释放user下的tid私有数据结构
 输入参数  : pst_user: 用户结构体;
 输出参数  : ul_output 出参
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_alg_free_tid_priv_stru(dmac_user_stru *pst_user)
{
    oal_uint8   uc_index;

    for (uc_index = 0; uc_index < WLAN_TID_MAX_NUM; uc_index++)
    {
        if (OAL_PTR_NULL == pst_user->ast_tx_tid_queue[uc_index].p_alg_priv)
        {
            break;
        }

        OAL_MEM_FREE(pst_user->ast_tx_tid_queue[uc_index].p_alg_priv, OAL_TRUE);

        pst_user->ast_tx_tid_queue[uc_index].p_alg_priv = OAL_PTR_NULL;
    }

}

/*****************************************************************************
 函 数 名  : dmac_alg_register_tx_notify_func
 功能描述  : 子算法注册回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_tx_notify_func(dmac_alg_tx_notify_enum_uint8    en_notify_sub_type,
                                                      p_alg_tx_notify_func             p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_TX_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);

    gst_alg_main.pa_tx_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_tx_complete_notify_func
 功能描述  : 子算法注册回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_tx_complete_notify_func(dmac_alg_tx_complete_notify_enum_uint8    en_notify_sub_type,
                                                                  p_alg_tx_complete_notify_func             p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_TX_COMPLETE_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_tx_complete_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_rx_notify_func
 功能描述  : 子算法注册回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_rx_notify_func(dmac_alg_rx_notify_enum_uint8    en_notify_sub_type,
                                                      p_alg_rx_notify_func             p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_RX_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_rx_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_tx_schedule_func
 功能描述  : 注册调度函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_tx_schedule_func(p_alg_tx_schedule_func  p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_tx_schedule_func = p_func;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
/*****************************************************************************
 函 数 名  : dmac_alg_register_tx_schedule_stat_event_notify_func
 功能描述  : 注册统计用户信息后修改调度参数函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : kongheng 00347307
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_tx_schedule_stat_event_notify_func(p_alg_tx_schedule_stat_event_notify_func  p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_tx_schedule_stat_event_notify_func = p_func;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_alg_register_tid_update_notify_func
 功能描述  : 注册调度函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_tid_update_notify_func(p_alg_update_tid_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_tid_update_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_tid_update_notify_func
 功能描述  : 注册调度函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_downlink_flowctl_notify_func(p_alg_downlink_flowctl_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_downlink_flowctl_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_add_vap_notify_func
 功能描述  : 子算法注册创建VAP回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_add_vap_notify_func(dmac_alg_add_vap_notify_enum_uint8    en_notify_sub_type,
                                                          p_alg_create_vap_notify_func        p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ADD_VAP_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_create_vap_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_del_vap_notify_func
 功能描述  : 子算法注册创建VAP回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_del_vap_notify_func(dmac_alg_del_vap_notify_enum_uint8   en_notify_sub_type,
                                                          p_alg_delete_vap_notify_func       p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_DEL_VAP_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_delete_vap_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_channel_notify_func
 功能描述  : 子算法注册设置信道回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_channel_notify_func(dmac_alg_cfg_channel_notify_enum_uint8  en_notify_sub_type,
                                                            p_alg_cfg_channel_notify_func      p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_CHANNEL_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_channel_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_start_connect_notify_func
 功能描述  : 子算法注册设置信道回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_start_connect_notify_func(dmac_alg_cfg_start_connect_notify_enum_uint8  en_notify_sub_type,
                                                                            p_alg_cfg_start_connect_notify_func     p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);

    gst_alg_main.pa_cfg_start_connect_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_btcoex_state_notify_func
 功能描述  : 子算法注册设置信道回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_btcoex_state_notify_func(dmac_alg_cfg_btcoex_state_notify_enum_uint8  en_notify_sub_type,
                                                                            p_alg_cfg_btcoex_state_notify_func     p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_BTCOEX_STATE_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);

    gst_alg_main.pa_cfg_btcoex_state_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
#endif
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */

/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_bandwidth_notify_func
 功能描述  : 子算法注册设置VAP带宽回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_bandwidth_notify_func(dmac_alg_cfg_bandwidth_notify_enum_uint8    en_notify_sub_type,
                                                               p_alg_cfg_bandwidth_notify_func        p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_BANDWIDTH_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_bandwidth_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_user_bandwidth_notify_func
 功能描述  : 子算法注册设置USER带宽回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_user_bandwidth_notify_func(
                dmac_alg_cfg_user_bandwidth_notify_enum_uint8 en_notify_sub_type,
                p_alg_cfg_user_bandwidth_notify_func          p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_user_bandwidth_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_user_protocol_notify_func
 功能描述  : 子算法注册设置USER协议模式回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : liwenjun
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_user_protocol_notify_func(dmac_alg_cfg_user_protocol_notify_enum_uint8 en_notify_sub_type,
                                                               p_alg_cfg_user_protocol_notify_func        p_func)

{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_user_protocol_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_user_spatial_stream_notify_func
 功能描述  : 子算法注册设置USER空间流回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月10日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_user_spatial_stream_notify_func(
                dmac_alg_cfg_user_spatial_stream_notify_enum_uint8  en_notify_sub_type,
                p_alg_cfg_user_spatial_stream_notify_func          p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_user_spatial_stream_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_add_user_notify_func
 功能描述  : 子算法注册填加关联用户的回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_add_user_notify_func(
                dmac_alg_add_user_notify_enum_uint8     en_notify_sub_type,
                p_alg_add_assoc_user_notify_func        p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ADD_USER_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_add_assoc_user_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_add_user_notify_func
 功能描述  : 子算法注册填加关联用户的回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_del_user_notify_func(dmac_alg_del_user_notify_enum_uint8   en_notify_sub_type,
                                                                    p_alg_delete_assoc_user_notify_func       p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_DEL_USER_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_delete_assoc_user_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_rx_mgmt_notify_func
 功能描述  : 注册txbf/抗干扰算法功能中对接收管理帧处理函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月23日
    作    者   : caohaibin
    修改内容   : 新生成函数

  2.日    期   : 2014年12月22日
    作    者   : wanran
    修改内容   : 增加算法ID，以在算法模块通用

*****************************************************************************/
oal_uint32  dmac_alg_register_rx_mgmt_notify_func(dmac_alg_rx_mgmt_notify_enum_uint8 en_notify_sub_type, p_alg_rx_mgmt_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_RX_MGMT_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.p_rx_mgmt_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_alg_register_config_notify_func
 功能描述  : 注册算法配置命令函数
 输入参数  : dmac_alg_config_id_enum_uint8 en_notify_sub_type
             p_alg_config_func p_func
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_config_notify_func(dmac_alg_config_id_enum_uint8 en_notify_sub_type, p_alg_config_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CONFIG_ID_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_config_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_alg_unregister_config_notify_func
 功能描述  : 注销算法配置命令钩子函数
 输入参数  : dmac_alg_config_id_enum_uint8 en_notify_sub_type
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_config_notify_func(dmac_alg_config_id_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CONFIG_ID_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_config_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_DBAC
/*****************************************************************************
 函 数 名  : dmac_alg_register_dmac_misc_event
 功能描述  : 注册DMAC MISC事件钩子函数
 输入参数  : hal_dmac_misc_sub_type_enum en_event_type
             oal_uint32 (*p_func)(frw_event_mem_stru *)
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type, oal_uint32 (*p_func)(frw_event_mem_stru *))
{
    ALG_ASSERT_RET(en_event_type < HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT && NULL != p_func, OAL_FAIL);
    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = p_func;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_alg_unregister_dmac_misc_event
 功能描述  : 注销DMAC MISC事件钩子函数
 输入参数  : hal_dmac_misc_sub_type_enum en_event_type
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type)
{
    ALG_ASSERT_RET(en_event_type < HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT, OAL_FAIL);
    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = NULL;
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_enqueue_tid_notify_func
 功能描述  : 报文入tid队列回调函数注册
 输入参数  : en_notify_sub_type : 通知类型
             p_func  : 注册的函数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : liwenjun 68207
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_enqueue_tid_notify_func(dmac_alg_enqueue_tid_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_enqueue_tid_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ENQUEUE_TID_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_enqueue_tid_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_enqueue_tid_notify_func
 功能描述  : 报文入tid队列回调函数注销
 输入参数  : en_notify_sub_type : 通知类型
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : liwenjun 68207
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_enqueue_tid_notify_func(dmac_alg_enqueue_tid_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ENQUEUE_TID_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_enqueue_tid_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_vap_down_notify_func
 功能描述  : vap down回调函数注册
 输入参数  : en_notify_sub_type : 通知类型
             p_func  : 注册的函数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : liwenjun 68207
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_vap_down_notify_func(dmac_alg_vap_down_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_vap_down_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_VAP_DOWN_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_vap_down_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_vap_down_notify_func
 功能描述  : vap down回调函数注销
 输入参数  : en_notify_sub_type : 通知类型
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : liwenjun 68207
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_vap_down_notify_func(dmac_alg_vap_down_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_VAP_DOWN_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_vap_down_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_probe_req_rx_notify_func
 功能描述  : 收到probe req时的钩子函数
 输入参数  : en_notify_sub_type : 通知类型
             p_func  : 注册的函数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月1日
    作    者   : gaolin 196511
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  dmac_alg_register_probe_req_rx_notify_func(dmac_alg_probe_req_rx_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_probe_req_rx_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_PROBE_REQ_RX_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_probe_req_rx_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_probe_req_rx_notify_func
 功能描述  : 收到probe req时的钩子函数
 输入参数  : en_notify_sub_type : 通知类型
             p_func  : 注册的函数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月1日
    作    者   : gaolin 196511
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  dmac_alg_unregister_probe_req_rx_notify_func(dmac_alg_vap_down_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_PROBE_REQ_RX_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_probe_req_rx_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : dmac_alg_register_vap_up_notify_func
 功能描述  : vap up回调函数注册
 输入参数  : en_notify_sub_type : 通知类型
             p_func  : 注册的函数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : liwenjun 68207
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_vap_up_notify_func(dmac_alg_vap_up_notify_enum_uint8 en_notify_sub_type,
                                                      p_alg_vap_up_notify_func p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_VAP_UP_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_alg_vap_up_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_vap_up_notify_func
 功能描述  : vap up回调函数注销
 输入参数  : en_notify_sub_type : 通知类型
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : liwenjun 68207
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_vap_up_notify_func(dmac_alg_vap_up_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_VAP_UP_BUTT, OAL_FAIL);
    gst_alg_main.pa_alg_vap_up_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}


#ifdef _PRE_WLAN_CHIP_TEST_ALG
/*****************************************************************************
 函 数 名  : dmac_alg_register_rx_event_notify
 功能描述  : 注册对接收WLAN报文事件通知的处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : liwenjun
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_alg_register_rx_event_notify(p_alg_rx_event_notify_func p_func)
{
    gst_alg_main.p_rx_event_notify_func = p_func;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_rx_event_notify
 功能描述  : 注册对接收WLAN报文事件通知的处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月20日
    作    者   : liwenjun
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_alg_unregister_rx_event_notify(oal_void)
{
    gst_alg_main.p_rx_event_notify_func = OAL_PTR_NULL;
}

#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL

/*****************************************************************************
 函 数 名  : dmac_alg_register_flowctl_backp_notify_func
 功能描述  : 注册流量控制的反压函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_flowctl_backp_notify_func(p_alg_flowctl_backp_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_alg_flowctl_backp_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_flowctl_backp_notify_func
 功能描述  : 注册流量控制的反压函数
 输入参数  : en_notify_sub_type : 通知类型
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : liwenjun 68207
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_flowctl_backp_notify_func()
{
    gst_alg_main.p_alg_flowctl_backp_func = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_alg_flowctl_backp
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : x00189397
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_flowctl_backp(mac_vap_stru *pst_mac_vap, oal_uint16 us_assoc_id, oal_uint8 uc_tidno, oal_uint8 uc_is_stop)
{
    frw_event_mem_stru          *pst_event_mem;          /* 申请事件返回的内存指针 */
    frw_event_stru              *pst_dmac_to_hmac_event;  /* 指向申请事件的payload指针 */
    mac_ioctl_queue_backp_stru  *pst_flowctl_backp_event;
    oal_uint32                   ul_ret;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_ioctl_queue_backp_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_flowctl_backp::alloc event failed!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获得事件指针 */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_FLOWCTL_BACKP,
                       OAL_SIZEOF(mac_ioctl_queue_backp_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_flowctl_backp_event = (mac_ioctl_queue_backp_stru *)(pst_dmac_to_hmac_event->auc_event_data);

    pst_flowctl_backp_event->uc_vap_id      = pst_mac_vap->uc_vap_id;
    pst_flowctl_backp_event->us_assoc_id    = us_assoc_id;
    pst_flowctl_backp_event->uc_tidno       = uc_tidno;
    pst_flowctl_backp_event->uc_is_stop     = uc_is_stop;

    /* 分发 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_flowctl_backp::frw_event_dispatch_event fail, ul_ret=%d}", ul_ret);
        return ul_ret;
    }

    /* 释放事件内存 */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : dmac_alg_register_txbf_rx_cntl_notify_func
 功能描述  : 注册txbf功能中对接收控制帧处理函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月23日
    作    者   : caohaibin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_txbf_rx_cntl_notify_func(p_alg_txbf_rx_cntl_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_txbf_rx_cntl_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_tx_notify_func
 功能描述  : 子算法注册回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tx_notify_func(dmac_alg_tx_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_TX_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_tx_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_tx_complete_notify_func
 功能描述  : 子算法注册回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tx_complete_notify_func(dmac_alg_tx_complete_notify_enum_uint8  en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_TX_COMPLETE_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_tx_complete_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_rx_notify_func
 功能描述  : 子算法注册回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_rx_notify_func(dmac_alg_rx_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_RX_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_rx_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_tx_schedule_func
 功能描述  : 注册调度函数
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tx_schedule_func(oal_void)
{
    gst_alg_main.p_tx_schedule_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
/*****************************************************************************
 函 数 名  : dmac_alg_register_tx_schedule_stat_event_notify_func
 功能描述  : 注销注册统计用户信息后修改调度参数函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : kongheng 00347307
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tx_schedule_stat_event_notify_func(oal_void)
{

    gst_alg_main.p_tx_schedule_stat_event_notify_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_tid_update_notify_func
 功能描述  : 注册调度函数
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tid_update_notify_func(oal_void)
{
    gst_alg_main.p_tid_update_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_tid_update_notify_func
 功能描述  : 注册调度函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_downlink_flowctl_notify_func(oal_void)
{
    gst_alg_main.p_downlink_flowctl_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_add_vap_notify_func
 功能描述  : 子算法注册创建VAP回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_add_vap_notify_func(dmac_alg_add_vap_notify_enum_uint8  en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ADD_VAP_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_create_vap_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_alg_unregister_cfg_start_connect_notify_func
 功能描述  : 处理开始关联消息通知
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月17日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_start_connect_notify_func(dmac_alg_cfg_channel_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT, OAL_FAIL);

    gst_alg_main.pa_cfg_start_connect_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 函 数 名  : dmac_alg_unregister_btcoex_state_notify_func
 功能描述  : 处理开始关联消息通知
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : c0021210
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_btcoex_state_notify_func(dmac_alg_cfg_btcoex_state_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_BTCOEX_STATE_NOTIFY_BUTT, OAL_FAIL);

    gst_alg_main.pa_cfg_btcoex_state_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}
#endif
#endif /*_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_cfg_channel_notify_func
 功能描述  : 子算法注册设置信道回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_channel_notify_func(dmac_alg_cfg_channel_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_CHANNEL_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_channel_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_cfg_bandwidth_notify_func
 功能描述  : 子算法注册设置带宽回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_bandwidth_notify_func(dmac_alg_cfg_bandwidth_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_BANDWIDTH_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_bandwidth_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_cfg_user_bandwidth_notify_func
 功能描述  : 子算法去注册设置USER带宽回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_user_bandwidth_notify_func(dmac_alg_cfg_user_bandwidth_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_user_bandwidth_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_cfg_user_protocol_notify_func
 功能描述  : 子算法注销设置USER协议模式回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月19日
    作    者   : liwenjun
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_user_protocol_notify_func(dmac_alg_cfg_user_protocol_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_user_protocol_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_cfg_spatial_stream_notify_func
 功能描述  : 子算法去注册设置USER空间流回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月10日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_user_spatial_stream_notify_func(dmac_alg_cfg_user_spatial_stream_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_BUTT, OAL_FAIL);

    gst_alg_main.pa_cfg_user_spatial_stream_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_del_vap_notify_func
 功能描述  : 子算法注册创建VAP回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC




 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_del_vap_notify_func(dmac_alg_del_vap_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_DEL_VAP_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_delete_vap_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_add_user_notify_func
 功能描述  : 子算法注册填加关联用户的回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_del_user_notify_func(dmac_alg_del_user_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_DEL_USER_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_delete_assoc_user_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_add_user_notify_func
 功能描述  : 子算法注册填加去关联用户的回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_add_user_notify_func(dmac_alg_add_user_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_ADD_USER_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_add_assoc_user_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_alg_unregister_rx_mgmt_notify_func
 功能描述  : 去注册子算法功能中对接收管理帧处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月23日
    作    者   : caohaibin
    修改内容   : 新生成函数

  2.日    期   : 2014年12月22日
    作    者   : wanran
    修改内容   : 增加算法ID，以在算法模块通用

*****************************************************************************/
oal_uint32  dmac_alg_unregister_rx_mgmt_notify_func(dmac_alg_rx_mgmt_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_RX_MGMT_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.p_rx_mgmt_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_txbf_rx_cntl_notify_func
 功能描述  : 去注册txbf功能中对接收控制帧处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月23日
    作    者   : caohaibin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_txbf_rx_cntl_notify_func(oal_void)
{
    gst_alg_main.p_txbf_rx_cntl_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_timer
 功能描述  : 子算法注册定时功能函数
 输入参数  :
 输出参数  : ppst_timer
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_timer(oal_uint32  ul_file_id,
                                   oal_uint32  ul_line_num,
                                   oam_module_id_enum_uint16 en_module_id,
                                   oal_uint32 ul_core_id,
                                   p_alg_timer_notify_func p_timer_notify_func,
                                   oal_void *p_arg,
                                   oal_bool_enum_uint8 en_is_periodic,
                                   dmac_alg_timer_stru **ppst_timer)
{
    dmac_alg_timer_stru *pst_timer;

    if (OAL_UNLIKELY(OAL_PTR_NULL == ppst_timer
        || OAL_PTR_NULL == p_timer_notify_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_register_timer ERROR");
        return OAL_FAIL;
    }

    pst_timer = (dmac_alg_timer_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_timer_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_timer)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_register_timer OAL_MEM_ALLOC ERROR");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_timer->en_module_id   = en_module_id;
    pst_timer->p_func         = p_timer_notify_func;
    pst_timer->p_timeout_arg  = p_arg;
    pst_timer->en_is_periodic = en_is_periodic;
    pst_timer->ul_file_id     = ul_file_id;
    pst_timer->ul_line_num    = ul_line_num;
    pst_timer->en_is_enabled  = OAL_FALSE;
    pst_timer->en_is_registerd= OAL_TRUE;
    pst_timer->en_is_deleting = OAL_FALSE;
    pst_timer->en_is_running  = OAL_FALSE;
    pst_timer->ul_core_id     = ul_core_id;

    frw_timer_add_timer(pst_timer);

    *ppst_timer = pst_timer;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_timer
 功能描述  : 子算法注消定时功能函数
 输入参数  : pst_mac_dev
             pst_timer
 输出参数  :
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_timer(dmac_alg_timer_stru *pst_timer)
{

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_timer))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_unregister_timer ERROR");
        return OAL_FAIL;
    }

    /* 判断定时器是否停止 */
    if (pst_timer->en_is_enabled == OAL_TRUE)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_unregister_timer::pst_timer->en_is_enabled == OAL_TRUE}\r\n");
        return OAL_FAIL;
    }

    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(pst_timer);

    OAL_MEM_FREE(pst_timer, OAL_TRUE);


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_start_timer
 功能描述  : 子算法启动定时功能函数
 输入参数  : pst_timer
             ul_timeout_ms
 输出参数  :
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_start_timer(dmac_alg_timer_stru *pst_timer, oal_uint16 us_timeout_ms)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_timer
        || 0 == us_timeout_ms))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_start_timer ERROR");
        return OAL_FAIL;
    }

    frw_timer_restart_timer(pst_timer, us_timeout_ms, pst_timer->en_is_periodic);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_stop_timer
 功能描述  : 子算法停止定时功能函数
 输入参数  : pst_timer
             ul_timeout_ms
 输出参数  :
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_stop_timer(dmac_alg_timer_stru *pst_timer)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_timer))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_stop_timer ERROR");
        return OAL_FAIL;
    }

    frw_timer_stop_timer(pst_timer);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_device_priv_stru
 功能描述  : 注册设备级别的结构体
 输入参数  : en_dev_stru_type    : 结构体类型
             p_dev_stru          : 需要注册的结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_device_priv_stru(mac_device_stru                 *pst_mac_dev,
                                                  dmac_alg_device_stru_id_enum_uint8    en_dev_stru_type,
                                                  oal_void                        *p_dev_stru)
{
    dmac_alg_device_stru  *pst_dev_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_dev)
        || (OAL_PTR_NULL == p_dev_stru)
        || (en_dev_stru_type >= DMAC_ALG_DEVICE_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_register_device_priv_stru:: ERROR INFO: pst_mac_dev=0x%x, p_dev_stru=0x%x, en_dev_stru_type=%d.}",
                       pst_mac_dev, p_dev_stru, en_dev_stru_type);
        return OAL_FAIL;
    }

    pst_dev_info = (dmac_alg_device_stru *)MAC_DEV_ALG_PRIV(pst_mac_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_register_device_priv_stru:: pst_dev_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dev_info->p_alg_info[en_dev_stru_type] = p_dev_stru;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_device_priv_stru
 功能描述  : 注册设备级别的结构体
 输入参数  : en_dev_stru_type    : 结构体类型
             p_dev_stru          : 需要注册的结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_device_priv_stru(mac_device_stru                 *pst_mac_dev,
                                                  dmac_alg_device_stru_id_enum_uint8    en_dev_stru_type)
{
    dmac_alg_device_stru  *pst_dev_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_dev)
        || (en_dev_stru_type >= DMAC_ALG_DEVICE_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_alg_unregister_device_priv_stru:: ERROR INFO: pst_mac_dev=0x%x, en_dev_stru_type=%d.}",
                       pst_mac_dev, en_dev_stru_type);
        return OAL_FAIL;
    }

    pst_dev_info = (dmac_alg_device_stru *)MAC_DEV_ALG_PRIV(pst_mac_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_unregister_device_priv_stru:: pst_dev_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dev_info->p_alg_info[en_dev_stru_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_vap_priv_stru
 功能描述  : 注册VAP私有数据结构体
 输入参数  : pst_vap: VAP结构体
             en_vap_stru_type  : 结构体枚举类型
             p_vap_stru        : 需要注册的结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                              dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type,
                                              oal_void                     *p_vap_stru)
{
    dmac_alg_vap_stru  *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap)
        || (OAL_PTR_NULL == p_vap_stru)
        || (en_vap_stru_type >= DMAC_ALG_VAP_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_register_vap_priv_stru:: ERROR INFO: pst_vap=0x%x, p_vap_stru=0x%x, en_vap_stru_type=%d.}",
                       pst_vap, p_vap_stru, en_vap_stru_type);
        return OAL_FAIL;
    }

    pst_alg_info = ((dmac_vap_stru *)pst_vap)->p_alg_priv;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_register_vap_priv_stru:: pst_alg_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_vap_stru_type] = p_vap_stru;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_vap_priv_stru
 功能描述  : 注册VAP私有数据结构体
 输入参数  : pst_vap: VAP结构体
             en_vap_stru_type  : 结构体枚举类型
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                              dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type)
{
    dmac_alg_vap_stru  *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap)
        || (en_vap_stru_type >= DMAC_ALG_VAP_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_alg_unregister_vap_priv_stru:: ERROR INFO: pst_vap=0x%x, en_vap_stru_type=%d.}",
                       pst_vap, en_vap_stru_type);

        return OAL_FAIL;
    }

    pst_alg_info = ((dmac_vap_stru *)pst_vap)->p_alg_priv;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_unregister_vap_priv_stru:: pst_alg_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_vap_stru_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_user_priv_stru
 功能描述  : 注册USER私有数据结构体
 输入参数  : pst_user: user结构体
             en_user_stru_type : 结构体枚举类型
             p_user_stru       : 需要注册的结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_user_priv_stru(mac_user_stru                     *pst_user,
                                                       dmac_alg_user_stru_id_enum_uint8   en_user_stru_type,
                                                       oal_void                          *p_user_stru)
{
    dmac_user_stru         *pst_dmac_user;
    dmac_alg_user_stru     *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (OAL_PTR_NULL == p_user_stru)
                  || (en_user_stru_type >= DMAC_ALG_USER_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_register_user_priv_stru:: ERROR INFO: pst_user=0x%x, p_user_stru=0x%x, en_user_stru_type=%d.}",
                       pst_user, p_user_stru, en_user_stru_type);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_register_user_priv_stru:: pst_dmac_user is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_alg_info = ((dmac_user_stru *)pst_user)->p_alg_priv;
    pst_alg_info = (dmac_alg_user_stru *)pst_dmac_user->p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_register_user_priv_stru:: pst_alg_info is NULL!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_user_stru_type] = p_user_stru;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_user_priv_stru
 功能描述  : 注册USER私有数据结构体
 输入参数  : pst_user: user结构体
             en_user_stru_type : 结构体枚举类型
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_user_priv_stru(mac_user_stru                     *pst_user,
                                                       dmac_alg_user_stru_id_enum_uint8   en_user_stru_type)
{
    dmac_user_stru         *pst_dmac_user;
    dmac_alg_user_stru     *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (en_user_stru_type >= DMAC_ALG_USER_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_alg_unregister_user_priv_stru:: ERROR INFO: pst_user=0x%x, en_user_stru_type=%d.}",
                       pst_user, en_user_stru_type);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_register_user_priv_stru, mac_res_get_dmac_user RETURN NULL PTR.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_alg_info = ((dmac_user_stru *)pst_user)->p_alg_priv;
    pst_alg_info = (dmac_alg_user_stru *)pst_dmac_user->p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "ERROR INFO: p_alg_priv is NULL PTR");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_user_stru_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_tid_priv_stru
 功能描述  : 注册TID私有数据结构体
 输入参数  : pst_user: user结构体
             uc_tid_no : tid号
             en_tid_stru_type : 结构体类型
             p_tid_stru : TID结构体

 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_tid_priv_stru(
                mac_user_stru                      *pst_user,
                oal_uint8                           uc_tid_no,
                dmac_alg_tid_stru_id_enum_uint8     en_tid_stru_type,
                oal_void                           *p_tid_stru)
{
    dmac_alg_tid_stru      *pst_alg_info;
    dmac_user_stru         *pst_dmac_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (OAL_PTR_NULL == p_tid_stru)
                  || (uc_tid_no >= WLAN_TID_MAX_NUM)
                  || (en_tid_stru_type >= DMAC_ALG_TID_STRU_ID_BUTT)))
    {
         OAM_ERROR_LOG4(0, OAM_SF_ANY,
                        "{dmac_alg_register_tid_priv_stru:: ERROR INFO: pst_user=0x%x, p_tid_stru=0x%x, uc_tid_no=%d, en_tid_stru_type=%d.}",
                        pst_user, p_tid_stru, uc_tid_no, en_tid_stru_type);

         return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_register_tid_priv_stru, mac_res_get_dmac_user RETURN NULL PTR.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_alg_info = ((dmac_user_stru *)pst_user)->st_tx_tid_queue[uc_tid_no].p_alg_priv;
    pst_alg_info = (dmac_alg_tid_stru *)pst_dmac_user->ast_tx_tid_queue[uc_tid_no].p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
         OAM_ERROR_LOG0(0, OAM_SF_ANY, "ERROR INFO:pst_alg_info is NULL PTR.");

         return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_tid_stru_type] = p_tid_stru;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_tid_priv_stru
 功能描述  : 注册TID私有数据结构体
 输入参数  : pst_user: user结构体
             uc_tid_no : tid号
             en_tid_stru_type : 结构体类型
             p_tid_stru : TID结构体

 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_tid_priv_stru(
                mac_user_stru                      *pst_user,
                oal_uint8                           uc_tid_no,
                dmac_alg_tid_stru_id_enum_uint8     en_tid_stru_type)
{
    dmac_alg_tid_stru      *pst_alg_info;
    dmac_user_stru         *pst_dmac_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (uc_tid_no >= WLAN_TID_MAX_NUM)
                  || (en_tid_stru_type >= DMAC_ALG_TID_STRU_ID_BUTT)))
    {
         OAM_ERROR_LOG3(0, OAM_SF_ANY,
                        "{dmac_alg_unregister_tid_priv_stru:: ERROR INFO: pst_user=0x%x, uc_tid_no=%d, en_tid_stru_type=%d.}",
                        pst_user, uc_tid_no, en_tid_stru_type);

         return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(pst_user->uc_vap_id, OAM_SF_ANY, "dmac_alg_register_tid_priv_stru, mac_res_get_dmac_user[user idx %d] RETURN NULL PTR.", pst_user->us_assoc_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_alg_info = ((dmac_user_stru *)pst_user)->st_tx_tid_queue[uc_tid_no].p_alg_priv;
    pst_alg_info = (dmac_alg_tid_stru *)pst_dmac_user->ast_tx_tid_queue[uc_tid_no].p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
         OAM_ERROR_LOG2(pst_user->uc_vap_id, OAM_SF_ANY, "ERROR INFO:pst_alg_info is NULL PTR, user idx = %d, tid no = %d.", pst_user->us_assoc_id, uc_tid_no);

         return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info->p_alg_info[en_tid_stru_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_get_device_priv_stru
 功能描述  : 获取TID下的私有数据结构体
 输入参数  : pst_user: user结构体
             uc_tid_no : tid号
             en_tid_stru_type : 结构体类型
 输出参数  : p_tid_stru : TID结构体
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_device_priv_stru(
                mac_device_stru                        *pst_mac_dev,
                dmac_alg_device_stru_id_enum_uint8      en_dev_stru_type,
                oal_void                              **pp_dev_stru)
{
    dmac_alg_device_stru  *pst_dev_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_dev)
        || (OAL_PTR_NULL == pp_dev_stru)
        || (en_dev_stru_type >= DMAC_ALG_DEVICE_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_device_priv_stru:: ERROR INFO: pst_mac_dev=0x%x, pp_dev_stru=0x%x, en_dev_stru_type=%d.}",
                       pst_mac_dev, pp_dev_stru, en_dev_stru_type);


        return OAL_FAIL;
    }

    pst_dev_info = (dmac_alg_device_stru *)MAC_DEV_ALG_PRIV(pst_mac_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_device_priv_stru::pst_dev_info is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pp_dev_stru = pst_dev_info->p_alg_info[en_dev_stru_type];

    if (OAL_UNLIKELY(*pp_dev_stru == OAL_PTR_NULL))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_alg_get_device_priv_stru::pp_dev_stru is null, en_dev_stru_type=%d}", en_dev_stru_type);
        return OAL_ERR_CODE_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_get_vap_priv_stru
 功能描述  : 获取VAP私有数据结构体
 输入参数  : pst_vap: VAP结构体
             en_vap_stru_type  : 结构体枚举类型
             p_vap_stru        : 需要注册的结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_vap_priv_stru(mac_vap_stru                 *pst_vap,
                                        dmac_alg_vap_stru_id_enum_uint8    en_vap_stru_type,
                                        oal_void                     **pp_vap_stru)
{
    dmac_alg_vap_stru  *pst_alg_info;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap)
        || (OAL_PTR_NULL == pp_vap_stru)
        || (en_vap_stru_type >= DMAC_ALG_VAP_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_vap_priv_stru:: ERROR INFO: pst_vap=0x%x, pp_vap_stru=0x%x, en_vap_stru_type=%d.}",
                       pst_vap, pp_vap_stru, en_vap_stru_type);

        return OAL_FAIL;
    }

    pst_alg_info = ((dmac_vap_stru *)pst_vap)->p_alg_priv;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pp_vap_stru = pst_alg_info->p_alg_info[en_vap_stru_type];

    if (OAL_UNLIKELY(*pp_vap_stru == OAL_PTR_NULL))
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_get_vap_priv_stru::alg priv pp_vap_stru is null, en_vap_stru_type=%d}", en_vap_stru_type);
        return OAL_ERR_CODE_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_get_user_priv_stru
 功能描述  : 获取USER私有数据结构体
 输入参数  : pst_user: user结构体
             en_user_stru_type : 结构体枚举类型
             p_user_stru       : 需要注册的结构体
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_user_priv_stru(
                mac_user_stru                      *pst_user,
                dmac_alg_user_stru_id_enum_uint8    en_user_stru_type,
                oal_void                          **pp_user_stru)
{
    dmac_alg_user_stru     *pst_alg_info;
    dmac_user_stru         *pst_dmac_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (OAL_PTR_NULL == pp_user_stru)
                  || (en_user_stru_type >= DMAC_ALG_USER_STRU_ID_BUTT)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_user_priv_stru:: ERROR INFO: pst_user=0x%x, pp_user_stru=0x%x, en_user_stru_type=%d.}",
                       pst_user, pp_user_stru, en_user_stru_type);
        return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG1(pst_user->uc_vap_id, OAM_SF_ANY, "dmac_alg_get_user_priv_stru, mac_res_get_dmac_user RETURN NULL PTR, user idx = %d.", pst_user->us_assoc_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info = (dmac_alg_user_stru *)pst_dmac_user->p_alg_priv;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        if (MAC_USER_STATE_ASSOC != pst_user->en_user_asoc_state)
        {
           OAM_WARNING_LOG4(pst_user->uc_vap_id, OAM_SF_ANY,
                            "{dmac_alg_get_user_priv_stru:: us_assoc_id=%d, en_user_asoc_state=%d, user mac: %2x:%2x}",
                            pst_user->us_assoc_id,
                            pst_user->en_user_asoc_state,
                            pst_user->auc_user_mac_addr[0],
                            pst_user->auc_user_mac_addr[1]);
           OAM_WARNING_LOG4(pst_user->uc_vap_id, OAM_SF_ANY,
                            "{dmac_alg_get_user_priv_stru:: user mac:%2x:%2x:%2x:%2x}",
                            pst_user->auc_user_mac_addr[2],
                            pst_user->auc_user_mac_addr[3],
                            pst_user->auc_user_mac_addr[4],
                            pst_user->auc_user_mac_addr[5]);
        }

        return OAL_ERR_CODE_PTR_NULL;
    }

    *pp_user_stru = pst_alg_info->p_alg_info[en_user_stru_type];

    if (OAL_UNLIKELY(*pp_user_stru == OAL_PTR_NULL))
    {
        OAM_WARNING_LOG2(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_alg_get_user_priv_stru::alg priv pp_user_stru is null, en_user_stru_type=%d, user idx = %d}",
                         en_user_stru_type, pst_user->us_assoc_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_get_tid_priv_stru
 功能描述  : 获取TID下的私有数据结构体
 输入参数  : pst_user: user结构体
             uc_tid_no : tid号
             en_tid_stru_type : 结构体类型
 输出参数  : p_tid_stru : TID结构体
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月3日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_tid_priv_stru(
                mac_user_stru                      *pst_user,
                oal_uint8                           uc_tid_no,
                dmac_alg_tid_stru_id_enum_uint8     en_tid_stru_type,
                oal_void                          **pp_tid_stru)
{
    dmac_alg_tid_stru      *pst_alg_info;
    dmac_user_stru         *pst_dmac_user;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_user)
                  || (OAL_PTR_NULL == pp_tid_stru)
                  || (uc_tid_no >= WLAN_TID_MAX_NUM)
                  || (en_tid_stru_type >= DMAC_ALG_TID_STRU_ID_BUTT)))
    {
         OAM_ERROR_LOG4(0, OAM_SF_ANY,
                        "{dmac_alg_get_tid_priv_stru:: ERROR INFO: pst_user=0x%x, pp_tid_stru=0x%x, uc_tid_no=%d, en_tid_stru_type=%d.}",
                        pst_user, pp_tid_stru, uc_tid_no, en_tid_stru_type);

         return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_get_tid_priv_stru, mac_res_get_dmac_user RETURN NULL PTR.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info = (dmac_alg_tid_stru *)pst_dmac_user->ast_tx_tid_queue[uc_tid_no].p_alg_priv;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        if (MAC_USER_STATE_ASSOC != pst_user->en_user_asoc_state)
        {
            OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_alg_get_tid_priv_stru::p_alg_priv is null ptr. user state = %d, user_id=%d}",
                            pst_user->en_user_asoc_state,
                            pst_user->us_assoc_id);
        }

        return OAL_ERR_CODE_PTR_NULL;
    }

    *pp_tid_stru = pst_alg_info->p_alg_info[en_tid_stru_type];

    if (OAL_UNLIKELY(*pp_tid_stru == OAL_PTR_NULL))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_alg_get_tid_priv_stru::pp_tid_stru is null, en_tid_stru_type=%d}", en_tid_stru_type);
        return OAL_ERR_CODE_PTR_NULL;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_alg_cfg_channel_notify
 功能描述  : 处理设置信道
 输入参数  : pst_vap: VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_channel_notify(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_CFG_CHANNEL_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_channel_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_channel_notify_func[uc_index](pst_vap, en_type);
        }
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_alg_cfg_start_connect_notify
 功能描述  : 处理sta模式发起关联
 输入参数  : pst_vap: VAP结构体
             c_rssi: 准备关联AP的rssi
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月17日
    作    者   : t00190962
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_start_connect_notify(mac_vap_stru *pst_vap, oal_int8 c_rssi)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;
    oal_uint32      ul_ret;

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_CFG_START_CONNECT_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_start_connect_notify_func[uc_index])
        {
            ul_ret = pst_alg_stru->pa_cfg_start_connect_notify_func[uc_index](pst_vap, c_rssi);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_cfg_start_connect_notify::ul_ret=%d, uc_index=%d}", ul_ret, uc_index);
            }
        }
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX

/*****************************************************************************
 函 数 名  : dmac_alg_cfg_btcoex_state_notify
 功能描述  : 处理sta模式发起关联
 输入参数  : pst_vap: VAP结构体
             c_rssi: 准备关联AP的rssi
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_btcoex_state_notify(mac_device_stru *pst_device, dmac_alg_bt_state_type_uint8 en_type)
{
    dmac_alg_stru  *pst_alg_stru;

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_btcoex_state_notify_func[DMAC_ALG_CFG_START_CONNECT_NOTIFY_TPC])
    {
        pst_alg_stru->pa_cfg_btcoex_state_notify_func[DMAC_ALG_CFG_START_CONNECT_NOTIFY_TPC](pst_device, en_type);
    }

    return OAL_SUCC;
}
#endif /* _PRE_WLAN_FEATURE_BTCOEX */

#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */


#ifdef _PRE_WLAN_FEATURE_CCA_OPT

/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_cca_intf_mode_notify_func
 功能描述  : 子算法注册干扰模式改变回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : liuming 00222214
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_cca_intf_mode_notify_func(dmac_alg_cfg_cca_intf_mode_notify_enum_uint8 en_notify_sub_type,
                                                               p_alg_cfg_cca_intf_mode_notify_func        p_func)

{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_cca_intf_mode_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_cfg_cca_intf_mode_notify_func
 功能描述  : 子算法注销干扰模式改变回调函数
 输入参数  : en_feature    : 特性枚举
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : liuming 00222214
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_cca_intf_mode_notify_func(dmac_alg_cfg_cca_intf_mode_notify_enum_uint8 en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_cca_intf_mode_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_cfg_cca_intf_mode_notify
 功能描述  : 通知算法干扰模式改变
 输入参数  : pst_mac_user: MAC USER结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : liuming 00222214
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_cca_intf_mode_notify(mac_device_stru *pst_device, oal_uint8 uc_intf_mode_old,
                oal_uint8 uc_intf_mode_new, oal_int8 c_cca_opt_avg_rssi_20, oal_int8 c_cca_opt_avg_rssi_40, oal_int8 c_cca_opt_avg_rssi_80)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;

    pst_alg_stru = &gst_alg_main;

    /* 调用相关回调函数 */
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_CCA_INTF_MODE_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_cca_intf_mode_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_cca_intf_mode_notify_func[uc_index](pst_device, uc_intf_mode_old,
                    uc_intf_mode_new, c_cca_opt_avg_rssi_20, c_cca_opt_avg_rssi_40, c_cca_opt_avg_rssi_80);
        }
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_alg_cfg_user_bandwidth_notify
 功能描述  : 通知算法USER带宽改变
 输入参数  : pst_mac_user: MAC USER结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_user_bandwidth_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_mac_user)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;

    pst_alg_stru = &gst_alg_main;

    /* 调用相关回调函数 */
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_USER_BANDWIDTH_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_user_bandwidth_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_user_bandwidth_notify_func[uc_index](pst_vap, pst_mac_user);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_cfg_user_protocol_notify
 功能描述  : 通知算法USER协议模式改变
 输入参数  : pst_mac_user: MAC USER结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_user_protocol_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_mac_user)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;

    pst_alg_stru = &gst_alg_main;

    /* 调用相关回调函数 */
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_USER_PROTOCOL_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_user_protocol_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_user_protocol_notify_func[uc_index](pst_vap, pst_mac_user);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_cfg_bandwidth_notify
 功能描述  : 处理设置带宽
 输入参数  : pst_vap: VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_bandwidth_notify(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;
    oal_dlist_head_stru      *pst_entry;
    mac_user_stru            *pst_mac_user;
    wlan_bw_cap_enum_uint8    en_bwcap_ap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_ERR_CODE_PTR_NULL");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_CFG_BANDWIDTH_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_bandwidth_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_bandwidth_notify_func[uc_index](pst_vap, en_type);
        }
    }

    if (CH_BW_CHG_TYPE_SCAN == en_type)
    {
        return OAL_SUCC;
    }
    /* 获取VAP带宽能力 */
    mac_vap_get_bandwidth_cap(pst_vap, &en_bwcap_ap);

    /* 遍历VAP下所有USER */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_vap->st_mac_user_list_head))
    {
        pst_mac_user = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);

        /* 通知算法 */
        dmac_alg_cfg_user_bandwidth_notify(pst_vap, pst_mac_user);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_cfg_user_spatial_stream_notify
 功能描述  : 通知算法USER带宽改变
 输入参数  : pst_mac_user: MAC USER结构体指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月10日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_user_spatial_stream_notify(mac_user_stru *pst_mac_user)
{
    dmac_alg_stru            *pst_alg_stru;
    oal_uint8                 uc_index;

    pst_alg_stru = &gst_alg_main;

    /* 调用相关回调函数 */
    for (uc_index = 0; uc_index < DMAC_ALG_CFG_USER_SPATIAL_STREAM_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_user_spatial_stream_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_user_spatial_stream_notify_func[uc_index](pst_mac_user);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_add_assoc_user_notify
 功能描述  : 当DMAC添加一个关联用户时，会调用该函数
 输入参数  : pst_vap: VAP结构体; pst_user: 用户结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_alg_add_assoc_user_notify(dmac_vap_stru *pst_vap, dmac_user_stru *pst_user)
{
    dmac_alg_user_stru  *pst_user_info;
    dmac_alg_tid_stru   *pst_tid_info;
    dmac_alg_stru       *pst_alg_stru;
    oal_uint8            uc_index;
    oal_uint8            uc_loop = 0;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_ERR_CODE_PTR_NULL");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL != pst_user->p_alg_priv)
    {
        dmac_alg_del_assoc_user_notify(pst_vap, pst_user);
    }

    /* 挂接用户级别的数据结构 */
    pst_user_info = (dmac_alg_user_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_user_stru), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_add_assoc_user_notify: alloc mem fail, dmac_alg_user_stru, pool id is OAL_MEM_POOL_ID_LOCAL");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    for (uc_index = 0; uc_index < DMAC_ALG_USER_STRU_ID_BUTT; uc_index++)
    {
        pst_user_info->p_alg_info[uc_index] = OAL_PTR_NULL;
    }

    pst_user->p_alg_priv = pst_user_info;

    /* 挂接TID级别的数据结构 */
    for (uc_index = 0; uc_index < WLAN_TID_MAX_NUM; uc_index++)
    {
        pst_tid_info = (dmac_alg_tid_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_tid_stru), OAL_TRUE);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid_info))
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_add_assoc_user_notify: alloc mem fail, dmac_alg_tid_stru, pool id is OAL_MEM_POOL_ID_LOCAL");
            OAL_MEM_FREE((oal_void *)pst_user_info, OAL_TRUE);
            pst_user->p_alg_priv = OAL_PTR_NULL;

            dmac_alg_free_tid_priv_stru(pst_user);

            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        for (uc_loop = 0; uc_loop < DMAC_ALG_TID_STRU_ID_BUTT; uc_loop++)
        {
            pst_tid_info->p_alg_info[uc_loop] = OAL_PTR_NULL;
        }

        pst_user->ast_tx_tid_queue[uc_index].p_alg_priv = pst_tid_info;
    }

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_ADD_USER_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_add_assoc_user_notify_func[uc_index])
        {
            pst_alg_stru->pa_add_assoc_user_notify_func[uc_index](&(pst_vap->st_vap_base_info), &(pst_user->st_user_base_info));
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : alg_notify_del_assoc_user
 功能描述  : 当DMAC删除一个关联用户时，会调用该函数
 输入参数  : pst_vap: VAP结构体; pst_user: 用户结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_alg_del_assoc_user_notify(dmac_vap_stru *pst_vap, dmac_user_stru *pst_user)
{
    dmac_alg_user_stru     *pst_user_info;
    dmac_alg_stru          *pst_alg_stru;
    oal_uint8               uc_index;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_ERR_CODE_PTR_NULL");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_user->p_alg_priv)
    {
        return OAL_SUCC;
    }

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_DEL_USER_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_delete_assoc_user_notify_func[uc_index])
        {
            pst_alg_stru->pa_delete_assoc_user_notify_func[uc_index](&(pst_vap->st_vap_base_info), &(pst_user->st_user_base_info));
        }
    }

    /* 释放TID级别的数据结构 */
    dmac_alg_free_tid_priv_stru(pst_user);

    /* 释放用户级别的数据结构 */
    pst_user_info = pst_user->p_alg_priv;

    if (OAL_PTR_NULL != pst_user_info)
    {
        OAL_MEM_FREE(pst_user_info, OAL_TRUE);
        pst_user->p_alg_priv = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_rx_mgmt_notify
 功能描述  : 将接收管理帧通知算法txbf/抗干扰模块
 输入参数  : pst_vap      : VAP结构体
             pst_user     : user结构体
             pst_buf      : netbuf结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月23日
    作    者   : caohaibin
    修改内容   : 新生成函数

  2.日    期   : 2014年12月22日
    作    者   : wanran
    修改内容   : 增加算法ID, 删除pst user为空的判断，以在算法模块通用

*****************************************************************************/
oal_uint32  dmac_alg_rx_mgmt_notify(mac_vap_stru *pst_vap,  mac_user_stru *pst_user, oal_netbuf_stru *pst_buf)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_buf)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY,
                       "{dmac_alg_rx_mgmt_notify:: ERROR INFO: pst_vap=0x%x, pst_buf=0x%x.}",
                       pst_vap, pst_buf);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_RX_MGMT_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->p_rx_mgmt_func[uc_index])
        {
            pst_alg_stru->p_rx_mgmt_func[uc_index](pst_vap, pst_user, pst_buf);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_txbf_rx_cntl_notify
 功能描述  : 将接收控制帧通知算法txbf模块
 输入参数  : pst_vap      : VAP结构体
             pst_user     : user结构体
             pst_buf      : netbuf结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月23日
    作    者   : caohaibin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_txbf_rx_cntl_notify(mac_vap_stru *pst_vap,  mac_user_stru *pst_user, oal_netbuf_stru *pst_buf)
{
    dmac_alg_stru  *pst_alg_stru;


    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user) || (OAL_PTR_NULL == pst_buf)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_txbf_rx_cntl_notify:: ERROR INFO: pst_vap=0x%x, pst_user=0x%x, pst_buf=0x%x.}",
                       pst_vap, pst_user, pst_buf);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    if (OAL_PTR_NULL != pst_alg_stru->p_txbf_rx_cntl_func)
    {
        pst_alg_stru->p_txbf_rx_cntl_func(pst_vap, pst_user, pst_buf);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : alg_notify_create_vap
 功能描述  : 当创建VAP时，会调用该函数
 输入参数  : pst_event_mem: 事件结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_alg_create_vap_notify(dmac_vap_stru *pst_vap)
{
    dmac_alg_vap_stru  *pst_alg_info;
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_create_vap_notify::pst_vap is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_alg_info = (dmac_alg_vap_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_vap_stru), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_alg_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_create_vap_notify::pst_alg_infois null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_index = 0; uc_index < DMAC_ALG_VAP_STRU_ID_BUTT; uc_index++)
    {
        pst_alg_info->p_alg_info[uc_index] = OAL_PTR_NULL;
    }


    /* 挂接VAP级别的数据结构 */
    pst_vap->p_alg_priv = pst_alg_info;

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_ADD_VAP_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_create_vap_notify_func[uc_index])
        {
            pst_alg_stru->pa_create_vap_notify_func[uc_index]((mac_vap_stru *)pst_vap);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : alg_notify_delete_vap
 功能描述  : 当删除VAP时，会调用该函数
 输入参数  : pst_vap: VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_alg_delete_vap_notify(dmac_vap_stru *pst_vap)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_DEL_VAP_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_delete_vap_notify_func[uc_index])
        {
            pst_alg_stru->pa_delete_vap_notify_func[uc_index]((mac_vap_stru *)pst_vap);
        }
    }

    /* 删除VAP级别的数据结构 */
    if (OAL_PTR_NULL != pst_vap->p_alg_priv)
    {
        OAL_MEM_FREE(pst_vap->p_alg_priv, OAL_TRUE);
        /* DTS2015041407876 P2P与WLAN异频共存时，反复连接P2P和WLAN后，导致死机问题 */
        pst_vap->p_alg_priv = OAL_PTR_NULL;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_SMARTANT
/*****************************************************************************
 函 数 名  : dmac_alg_create_ba
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_create_ba(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_tid)
{
    frw_event_mem_stru          *pst_event_mem;          /* 申请事件返回的内存指针 */
    frw_event_stru              *pst_dmac_to_hmac_event;  /* 指向申请事件的payload指针 */
    dmac_to_hmac_ctx_event_stru *pst_create_ba_event;
    oal_uint32                   ul_ret;
    dmac_tid_stru               *pst_tid;
    dmac_user_stru              *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_alg_create_ba::null pointer,pst_dmac_user[%d].}", pst_mac_user->us_assoc_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_tid = &pst_dmac_user->ast_tx_tid_queue[uc_tid];

    if (OAL_PTR_NULL != pst_tid->pst_ba_tx_hdl)
    {
        return OAL_SUCC;
    }

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_ctx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "alloc event failed!");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获得事件指针 */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_SDT_REG,
                       DMAC_TO_HMAC_CREATE_BA,
                       OAL_SIZEOF(dmac_to_hmac_ctx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_create_ba_event = (dmac_to_hmac_ctx_event_stru *)(pst_dmac_to_hmac_event->auc_event_data);

    pst_create_ba_event->us_user_index  = pst_mac_user->us_assoc_id;
    pst_create_ba_event->uc_tid         = uc_tid;
    pst_create_ba_event->uc_vap_id      = pst_mac_vap->uc_vap_id;

    /* 分发 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_create_ba::frw_event_dispatch_event fail, ul_ret=%d}\r\n", ul_ret);
        return ul_ret;
    }

    /* 释放事件内存 */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_alg_create_ba
 功能描述  : 算法删除ba接口，此接口只是置一个标志位，并不真正删除
             约束: 软件只在发送完成检查此标志位，因此此接口只在发送完成流程中调用有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_del_ba(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_tid)
{
    dmac_user_stru *pst_dmac_user;

    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "user is null ptr!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = mac_res_get_dmac_user(pst_mac_user->us_assoc_id);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac user is null ptr!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->en_delete_ba_flag = OAL_TRUE;

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_alg_syn_info
 功能描述  : 算法改变协议，从dmac同步当前协议模式到hmac
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月21日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_syn_info(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    frw_event_mem_stru                      *pst_event_mem;          /* 申请事件返回的内存指针 */
    frw_event_stru                          *pst_dmac_to_hmac_event;  /* 指向申请事件的payload指针 */
    dmac_to_hmac_syn_info_event_stru        *pst_syn_info_event;
    oal_uint32                               ul_ret;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_syn_info_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_syn_info: alloc event failed! size=%d}", OAL_SIZEOF(dmac_to_hmac_syn_info_event_stru));

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获得事件指针 */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_SDT_REG,
                       DMAC_TO_HMAC_ALG_INFO_SYN,
                       OAL_SIZEOF(dmac_to_hmac_syn_info_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_syn_info_event = (dmac_to_hmac_syn_info_event_stru *)(pst_dmac_to_hmac_event->auc_event_data);

    pst_syn_info_event->us_user_index  = pst_mac_user->us_assoc_id;
    pst_syn_info_event->uc_cur_protocol = pst_mac_user->en_cur_protocol_mode;
    pst_syn_info_event->uc_cur_bandwidth = pst_mac_user->en_cur_bandwidth;

    /* 分发 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_syn_info::frw_event_dispatch_event fail, ul_ret=%d}", ul_ret);
    }

    /* 释放事件内存 */
    FRW_EVENT_FREE(pst_event_mem);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_alg_voice_aggr
 功能描述  : 算法改变支持Voice聚合的标志时，从dmac通知hmac
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月20日
    作    者   : liwenjun 00330043
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_voice_aggr(mac_vap_stru *pst_mac_vap)
{
    frw_event_mem_stru                      *pst_event_mem;          /* 申请事件返回的内存指针 */
    frw_event_stru                          *pst_dmac_to_hmac_event;  /* 指向申请事件的payload指针 */
    dmac_to_hmac_voice_aggr_event_stru      *pst_voice_aggr_event;
    oal_uint32                               ul_ret;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_voice_aggr_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_voice_aggr: alloc event failed! size=%d}", OAL_SIZEOF(dmac_to_hmac_voice_aggr_event_stru));

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获得事件指针 */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_SDT_REG,
                       DMAC_TO_HMAC_VOICE_AGGR,
                       OAL_SIZEOF(dmac_to_hmac_voice_aggr_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    pst_voice_aggr_event = (dmac_to_hmac_voice_aggr_event_stru *)(pst_dmac_to_hmac_event->auc_event_data);
    pst_voice_aggr_event->uc_vap_id     = pst_mac_vap->uc_vap_id;
    pst_voice_aggr_event->en_voice_aggr = pst_mac_vap->bit_voice_aggr;

    /* 分发 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_voice_aggr: frw_event_dispatch_event fail, ul_ret=%d}", ul_ret);
    }

    /* 释放事件内存 */
    FRW_EVENT_FREE(pst_event_mem);

    return ul_ret;
}

#endif
/*****************************************************************************
 函 数 名  : dmac_alg_get_qap_wme_info
 功能描述  : 读取当前AP自身的WME参数
 输入参数  : pst_vap      : 指向VAP的指针
             en_wme_type  : WME类型
 输出参数  : ppst_wme_info: 指向WME参数
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_qap_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info)
{
    if ((OAL_PTR_NULL == pst_vap)||(OAL_PTR_NULL == pst_wme_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_PTR_NULL == pst_vap");
        return OAL_FAIL;
    }

    /* config vap没有mib库，不能查询wme参数 */
    if (WLAN_VAP_MODE_CONFIG == pst_vap->en_vap_mode)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_qap_wme_info::config vap has no mib}\r\n");

        return OAL_FAIL;
    }

    if (en_wme_type >= WLAN_WME_AC_BUTT)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_get_qap_wme_info::en_wme_type=%d}", en_wme_type);
        return OAL_FAIL;
    }

    pst_wme_info->ul_aifsn      = pst_vap->pst_mib_info->st_wlan_mib_qap_edac[en_wme_type].ul_dot11QAPEDCATableAIFSN;
    pst_wme_info->ul_logcwmax   = pst_vap->pst_mib_info->st_wlan_mib_qap_edac[en_wme_type].ul_dot11QAPEDCATableCWmax;
    pst_wme_info->ul_logcwmin   = pst_vap->pst_mib_info->st_wlan_mib_qap_edac[en_wme_type].ul_dot11QAPEDCATableCWmin;
    pst_wme_info->ul_txop_limit = pst_vap->pst_mib_info->st_wlan_mib_qap_edac[en_wme_type].ul_dot11QAPEDCATableTXOPLimit;

    return OAL_SUCC;
}

//#if ALG_SCHEUDLE_EDCA_FEATURE
/*****************************************************************************
 函 数 名  : dmac_alg_set_wme_info
 功能描述  : 设置AP的WME参数
 输入参数  : pst_vap     : 指向VAP的指针
             en_wme_type : WME类型枚举
             pst_wme_info: 指向WME参数的指针
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_set_qap_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info)
{
    oal_uint32   aul_param[3];

    if ((OAL_PTR_NULL == pst_vap)||(OAL_PTR_NULL == pst_wme_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_PTR_NULL == pst_vap");
        return OAL_FAIL;
    }

    if (en_wme_type >= WLAN_WME_AC_BUTT)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_set_qap_wme_info::en_wme_type=%d}", en_wme_type);
        return OAL_FAIL;
    }

    /* 调用配置接口 */
    aul_param[0] = WLAN_CFGID_EDCA_TABLE_CWMIN;
    aul_param[1] = en_wme_type;
    aul_param[2] = pst_wme_info->ul_logcwmin;
    dmac_config_set_qap_cwmin(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);

    aul_param[0] = WLAN_CFGID_EDCA_TABLE_CWMAX;
    aul_param[1] = en_wme_type;
    aul_param[2] = pst_wme_info->ul_logcwmax;
    dmac_config_set_qap_cwmax(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);

    aul_param[0] = WLAN_CFGID_EDCA_TABLE_AIFSN;
    aul_param[1] = en_wme_type;
    aul_param[2] = pst_wme_info->ul_aifsn;
    dmac_config_set_qap_aifsn(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);

    aul_param[0] = WLAN_CFGID_EDCA_TABLE_TXOP_LIMIT;
    aul_param[1] = en_wme_type;
    aul_param[2] = pst_wme_info->ul_txop_limit;
    dmac_config_set_qap_txop_limit(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);

    return OAL_SUCC;
}
//#endif

/*****************************************************************************
 函 数 名  : dmac_alg_set_msdu_lifetime
 功能描述  : 设置AP的msdu的lifetime参数
 输入参数  : pst_vap     : 指向VAP的指针
             en_wme_type : WME类型枚举
             ul_msdu_lifetime: 待设置的ac的lifetime参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月4日
    作    者   : xiechunhui
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_set_qap_msdu_lifetime(
                                    mac_vap_stru               *pst_vap,
                                    wlan_wme_ac_type_enum_uint8 en_wme_type,
                                    oal_uint32                  ul_msdu_lifetime)
{
    oal_uint32   aul_param[3];
    oal_uint32   ul_ret = OAL_SUCC;

    if (OAL_PTR_NULL == pst_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "OAL_PTR_NULL == pst_vap");
        return OAL_FAIL;
    }

    if (en_wme_type >= WLAN_WME_AC_BUTT)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_set_qap_msdu_lifetime::en_wme_type=%d}", en_wme_type);
        return OAL_FAIL;
    }

    /* 调用配置接口 */
    aul_param[1] = (oal_uint32)en_wme_type;
    aul_param[2] = ul_msdu_lifetime;

    ul_ret = dmac_config_set_qap_msdu_lifetime(pst_vap, OAL_SIZEOF(aul_param), (oal_uint8 *)aul_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "dmac_config_set_msdu_lifetime failed");
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_alg_register
 功能描述  : 算法注册
 输入参数  : en_alg_id: 算法的枚举类型
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register(dmac_alg_id_enum_uint32 en_alg_id)
{
    ALG_ASSERT_RET(en_alg_id < DMAC_ALG_ID_BUTT, OAL_ERR_CODE_ARRAY_OVERFLOW);
    gst_alg_main.ul_alg_bitmap |= en_alg_id;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register
 功能描述  : 算法注销
 输入参数  : en_alg_id: 算法的枚举类型
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister(dmac_alg_id_enum_uint32 en_alg_id)
{
    ALG_ASSERT_RET(en_alg_id < DMAC_ALG_ID_BUTT, OAL_ERR_CODE_ARRAY_OVERFLOW);
    gst_alg_main.ul_alg_bitmap &= (~en_alg_id);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_is_registered
 功能描述  : 查看算法是否注册
 输入参数  : p_mac_dev: MAC DEVICE; en_alg_id: 算法的枚举类型
 输出参数  : pen_is_registered: 是否注册
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_is_registered(dmac_alg_id_enum_uint32 en_alg_id, oal_bool_enum_uint8 *pen_is_registered)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != pen_is_registered && en_alg_id < DMAC_ALG_ID_BUTT, OAL_ERR_CODE_PTR_NULL);
    if((gst_alg_main.ul_alg_bitmap & en_alg_id) == en_alg_id)
    {
        *pen_is_registered = OAL_TRUE;
    }
    else
    {
        *pen_is_registered = OAL_FALSE;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : alg_main_init
 功能描述  : ALG模块初始化总入口，包含ALG模块内部所有特性的初始化。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回码，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_init(mac_device_stru  *pst_device)
{
    dmac_alg_device_stru *p_alg_dev_stru;     /* device级别算法的私有数据结构 */
    oal_uint32  uc_idx;

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_init: OAL_PTR_NULL == pst_device");
        return OAL_ERR_CODE_PTR_NULL;
    }

    p_alg_dev_stru = (dmac_alg_device_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_alg_device_stru), OAL_TRUE);

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_alg_dev_stru))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "alg_main_init: OAL_PTR_NULL == p_alg_stru\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_idx = 0; uc_idx < DMAC_ALG_DEVICE_STRU_ID_BUTT; uc_idx++)
    {
        p_alg_dev_stru->p_alg_info[uc_idx] = OAL_PTR_NULL;
    }

    /* 挂接算法主结构体 */
    MAC_DEV_ALG_PRIV(pst_device) = p_alg_dev_stru;

    /* 主结构体初始化 */
    oal_dlist_init_head(&gst_alg_main.st_timer_list);     /* 定时器双向链表初始化 */

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : alg_main_exit
 功能描述  : ALG模块卸载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 卸载返回码，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_exit(mac_device_stru  *pst_device)
{
    dmac_alg_device_stru *p_alg_dev_stru;     /* device级别算法的私有数据结构 */

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_exit: OAL_PTR_NULL == pst_device");
        return OAL_ERR_CODE_PTR_NULL;
    }

    p_alg_dev_stru = MAC_DEV_ALG_PRIV(pst_device);
    if (OAL_UNLIKELY(OAL_PTR_NULL == p_alg_dev_stru))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_exit::OAL_PTR_NULL == p_alg_stru}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_FREE(p_alg_dev_stru, OAL_TRUE);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : alg_main_exit
 功能描述  : 获取某硬件队列中ppdu的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 卸载返回码，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32   dmac_alg_get_hal_queue_ppdu_num(oal_uint16 us_assoc_id, oal_uint8 uc_ac_num, oal_uint8 *puc_ppdu_num)
{
    dmac_vap_stru             *pst_dmac_vap;
    mac_user_stru             *pst_user;
    pst_user = (mac_user_stru *)mac_res_get_mac_user(us_assoc_id);
    if(OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_get_hal_queue_ppdu_num: OAL_PTR_NULL == pst_user");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap    = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_user->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_alg_get_hal_queue_ppdu_num::mac_res_get_dmac_vap fail. vap_id[%u]}",pst_user->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    *puc_ppdu_num   = pst_dmac_vap->pst_hal_device->ast_tx_dscr_queue[HAL_AC_TO_Q_NUM(uc_ac_num)].uc_ppdu_cnt;

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_alg_set_hal_queue_ppdu_num
 功能描述  : 设置某硬件队列中ppdu的个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 卸载返回码，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年6月23日
    作    者   : pwx284245
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32   dmac_alg_set_hal_queue_ppdu_num(oal_uint16 us_assoc_id, oal_uint8 uc_ac_num, oal_uint8 puc_ppdu_num)
{
    dmac_vap_stru             *pst_dmac_vap;
    hal_to_dmac_device_stru   *pst_hal_device;
    mac_user_stru             *pst_user;
    pst_user = (mac_user_stru *)mac_res_get_mac_user(us_assoc_id);
    if(OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_alg_set_hal_queue_ppdu_num: OAL_PTR_NULL == pst_user");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap    = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_user->uc_vap_id);
    pst_hal_device  = pst_dmac_vap->pst_hal_device;
    pst_hal_device->ast_tx_dscr_queue[HAL_AC_TO_Q_NUM(uc_ac_num)].uc_ppdu_cnt = puc_ppdu_num;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_alg_get_hal_to_dmac_vap
 功能描述  : 根据mac_vap_id获取hal_to_dmac_vap结构
 输入参数  : oal_uint8 uc_mac_vap_id
 输出参数  : 无
 返 回 值  : hal_to_dmac_vap_stru *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
hal_to_dmac_vap_stru *dmac_alg_get_hal_to_dmac_vap(oal_uint8 uc_mac_vap_id)
{
    dmac_vap_stru   *pst_dmac_vap;

    if (uc_mac_vap_id >= WLAN_VAP_SUPPOTR_MAX_NUM_SPEC)
    {
        return OAL_PTR_NULL;
    }

    pst_dmac_vap = mac_res_get_dmac_vap(uc_mac_vap_id);
    if (NULL == pst_dmac_vap)
    {
        return OAL_PTR_NULL;
    }

    return pst_dmac_vap->pst_hal_vap;
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 函 数 名  : dmac_alg_register_cfg_smps_notify_func
 功能描述  : 子算法注册设置SMPS的回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_cfg_smps_notify_func(dmac_alg_cfg_smps_notify_enum_uint8    en_notify_sub_type,
                                                   p_alg_cfg_smps_notify_func        p_func)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_SMPS_NOTIFY_BUTT && OAL_PTR_NULL != p_func, OAL_FAIL);
    gst_alg_main.pa_cfg_smps_notify_func[en_notify_sub_type] = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_cfg_smps_notify_func
 功能描述  : 子算法注册设置SMPS的回调函数
 输入参数  : en_feature    : 特性枚举
             p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_cfg_smps_notify_func(dmac_alg_cfg_smps_notify_enum_uint8    en_notify_sub_type)
{
    ALG_ASSERT_RET(en_notify_sub_type < DMAC_ALG_CFG_SMPS_NOTIFY_BUTT, OAL_FAIL);
    gst_alg_main.pa_cfg_smps_notify_func[en_notify_sub_type] = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_cfg_smps_notify
 功能描述  : 处理设置SMPS模式
 输入参数  : pst_vap: VAP结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月6日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_cfg_smps_notify(mac_vap_stru *pst_vap, mac_user_stru *pst_user)
{
    dmac_alg_stru  *pst_alg_stru;
    oal_uint8       uc_index;

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    for (uc_index = 0; uc_index < DMAC_ALG_CFG_SMPS_NOTIFY_BUTT; uc_index++)
    {
        if (OAL_PTR_NULL != pst_alg_stru->pa_cfg_smps_notify_func[uc_index])
        {
            pst_alg_stru->pa_cfg_smps_notify_func[uc_index](pst_vap, pst_user);
        }
    }

    return OAL_SUCC;
}

#endif

/* 单用户跟踪获取参数相关接口 */
#ifdef _PRE_DEBUG_MODE_USER_TRACK
/*****************************************************************************
 函 数 名  : dmac_alg_register_start_stat_rssi_notify
 功能描述  : 注册启动统计rssi功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_start_stat_rssi_notify(
                                        p_alg_start_stat_rssi_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_start_stat_rssi_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_start_stat_rssi_notify
 功能描述  : 去注册启动统计rssi功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_start_stat_rssi_notify(oal_void)
{
    gst_alg_main.p_start_stat_rssi_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_get_rssi_notify
 功能描述  : 注册获取rssi功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_get_rssi_notify(p_alg_get_rssi_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_rssi_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_get_rssi_notify
 功能描述  : 去注册获取rssi功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_rssi_notify(oal_void)
{
    gst_alg_main.p_get_rssi_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_alg_register_stop_stat_rssi_notify
 功能描述  : 注册停止统计rssi功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_stop_stat_rssi_notify(
                                        p_alg_stop_stat_rssi_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_stop_stat_rssi_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_stop_stat_rssi_notify
 功能描述  : 去注册停止统计rssi功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_stop_stat_rssi_notify(oal_void)
{
    gst_alg_main.p_stop_stat_rssi_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_start_stat_rate_notify
 功能描述  : 注册启动统计rate功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_start_stat_rate_notify(
                                        p_alg_start_stat_rate_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_start_stat_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_start_stat_rate_notify
 功能描述  : 去注册启动统计rate功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_start_stat_rate_notify(oal_void)
{
    gst_alg_main.p_start_stat_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_get_rate_notify
 功能描述  : 注册获取rate功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_get_rate_notify(p_alg_get_rate_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_get_rate_notify
 功能描述  : 去注册获取rate功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_rate_notify(oal_void)
{
    gst_alg_main.p_get_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_alg_register_stop_stat_rate_notify
 功能描述  : 注册停止统计rate功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_stop_stat_rate_notify(
                                        p_alg_start_stat_rate_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_stop_stat_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_stop_stat_rate_notify
 功能描述  : 去注册停止统计rate功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_stop_stat_rate_notify(oal_void)
{
    gst_alg_main.p_stop_stat_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_start_stat_best_rate_notify
 功能描述  : 注册启动统计最优速率相关参数功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_start_stat_best_rate_notify(
                                        p_alg_start_stat_best_rate_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_start_stat_best_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_start_stat_best_rate_notify
 功能描述  : 去注册启动统计最优速率功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_start_stat_best_rate_notify(oal_void)
{
    gst_alg_main.p_start_stat_best_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_get_best_rate_notify
 功能描述  : 注册获取最优速率功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_get_best_rate_notify(p_alg_get_best_rate_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_best_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_get_best_rate_notify
 功能描述  : 去注册获取最优速率功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_best_rate_notify(oal_void)
{
    gst_alg_main.p_get_best_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_alg_register_stop_stat_best_rate_notify
 功能描述  : 注册停止统计最优速率功能的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_stop_stat_best_rate_notify(
                                        p_alg_stop_stat_best_rate_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_stop_stat_best_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_stop_stat_best_rate_notify
 功能描述  : 去注册停止统计最优速率功能的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_stop_stat_best_rate_notify(oal_void)
{
    gst_alg_main.p_stop_stat_best_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_alg_start_stat_rssi
 功能描述  : 封装全局钩子，开始统计收发rssi
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_start_stat_rssi(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "param null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_start_stat_rssi_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "p_start_stat_rssi_func null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_start_stat_rssi_func(pst_mac_user);
}

/*****************************************************************************
 函 数 名  : dmac_alg_get_rssi
 功能描述  : 封装全局钩子，获取收发rssi
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_rssi(mac_user_stru *pst_mac_user,
                                  oal_int8      *pc_tx_rssi,
                                  oal_int8      *pc_rx_rssi)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user
       || OAL_PTR_NULL == pc_rx_rssi || OAL_PTR_NULL == pc_tx_rssi))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_rssi:: ERROR INFO: pst_mac_user=0x%x, pc_tx_rssi=0x%x, pc_rx_rssi=0x%x.}",
                       pst_mac_user, pc_tx_rssi, pc_rx_rssi);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_rssi_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_rssi::p_get_rssi_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_rssi_func(pst_mac_user, pc_tx_rssi, pc_rx_rssi);
}


/*****************************************************************************
 函 数 名  : dmac_alg_stop_stat_rssi
 功能描述  : 封装钩子，停止统计收发rssi
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月2日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_stop_stat_rssi(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_rssi::pst_mac_user is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_stop_stat_rssi_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_rssi::p_stop_stat_rssi_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_stop_stat_rssi_func(pst_mac_user);
}

/*****************************************************************************
 函 数 名  : dmac_alg_start_stat_rate
 功能描述  : 封装全局钩子，开始统计收发rate
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_start_stat_rate(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_start_stat_rate::pst_mac_user is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_start_stat_rate_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "p_start_stat_rate_func null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_start_stat_rate_func(pst_mac_user);
}


/*****************************************************************************
 函 数 名  : dmac_alg_get_rate
 功能描述  : 封装全局钩子，获取收发rate
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_rate(mac_user_stru *pst_mac_user,
                                  oal_uint32     *pul_tx_rate,
                                  oal_uint32     *pul_rx_rate)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user
       || OAL_PTR_NULL == pul_rx_rate || OAL_PTR_NULL == pul_tx_rate))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_rate:: ERROR INFO: pst_mac_user=0x%x, pul_tx_rate=0x%x, pul_rx_rate=0x%x.}",
                       pst_mac_user, pul_tx_rate, pul_rx_rate);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_rate_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_rate::p_get_rate_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_rate_func(pst_mac_user, pul_tx_rate, pul_rx_rate);
}

/*****************************************************************************
 函 数 名  : dmac_alg_stop_stat_rate
 功能描述  : 封装钩子，停止统计收发rate
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月2日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_stop_stat_rate(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_rate::pst_mac_user is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_stop_stat_rate_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_rate::p_stop_stat_rate_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_stop_stat_rate_func(pst_mac_user);
}

/*****************************************************************************
 函 数 名  : dmac_alg_start_stat_best_rate
 功能描述  : 封装全局钩子，开始统计最优rate
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_start_stat_best_rate(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_start_stat_best_rate::user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_start_stat_best_rate_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_start_stat_best_rate::p_start_stat_best_rate_func is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_start_stat_best_rate_func(pst_mac_user);
}


/*****************************************************************************
 函 数 名  : dmac_alg_get_best_rate
 功能描述  : 封装全局钩子，获取最优rate
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_best_rate(
                                  mac_user_stru   *pst_mac_user,
                                  dmac_best_rate_stat_info_stru *pst_best_rate_info)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user || OAL_PTR_NULL == pst_best_rate_info))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_alg_get_best_rate::pst_mac_user = [%d], \
                       pst_best_rate_info = [%d].}", pst_mac_user, pst_best_rate_info);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_best_rate_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_best_rate::p_get_best_rate_func is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_best_rate_func(pst_mac_user, pst_best_rate_info);
}

/*****************************************************************************
 函 数 名  : dmac_alg_stop_stat_best_rate
 功能描述  : 封装钩子，停止统计最优rate
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月2日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_stop_stat_best_rate(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_best_rate::usr is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_stop_stat_best_rate_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_alg_stop_stat_best_rate::p_stop_stat_best_rate_func is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_stop_stat_best_rate_func(pst_mac_user);
}


#endif
/*****************************************************************************
 函 数 名  : dmac_alg_register_get_rate_by_table_notify
 功能描述  : 注册通过速率表查询速率的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_get_rate_by_table_notify(p_alg_get_rate_by_table_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_rate_by_table_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_get_rate_by_table_notify
 功能描述  : 注销通过速率表查询速率的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_rate_by_table_notify(oal_void)
{
    gst_alg_main.p_get_rate_by_table_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_get_rate_by_table
 功能描述  : 封装全局钩子，获取速率大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_rate_by_table(mac_user_stru *pst_mac_user,
                                  hal_rx_statistic_stru *pst_rx_stats,
                                  oal_uint32 *pul_rate_kbps)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user
       || OAL_PTR_NULL == pst_rx_stats || OAL_PTR_NULL == pul_rate_kbps))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY,
                       "{dmac_alg_get_rate_by_table:: ERROR INFO: pst_mac_user=0x%x, pst_rx_stats=0x%x, pul_rate_kbps=0x%x.}",
                       pst_mac_user, pst_rx_stats, pst_rx_stats);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_rate_by_table_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_rate_by_table::p_get_rate_by_table_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_rate_by_table_func(pst_mac_user, pst_rx_stats, pul_rate_kbps);
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_get_tx_best_rate_notify
 功能描述  : 注册查询tx速率的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_get_tx_best_rate_notify(p_alg_get_tx_best_rate_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_get_tx_best_rate_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_get_rate_by_table_notify
 功能描述  : 注销查询tx速率的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月9日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_get_tx_best_rate_notify(oal_void)
{
    gst_alg_main.p_get_tx_best_rate_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_get_tx_best_rate
 功能描述  : 封装全局钩子，获取tx最优速率大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_get_tx_best_rate(mac_user_stru *pst_mac_user,
                                  wlan_wme_ac_type_enum_uint8 en_traffic_type,
                                  oal_uint32 *pul_rate_kbps)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user
       ||  OAL_PTR_NULL == pul_rate_kbps))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY,
                       "{dmac_alg_get_tx_best_rate:: ERROR INFO: pst_mac_user=0x%x, pul_rate_kbps=0x%x.}",
                       pst_mac_user, pul_rate_kbps);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_get_tx_best_rate_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_get_tx_best_rate::p_get_rate_by_table_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_get_tx_best_rate_func(pst_mac_user, en_traffic_type, pul_rate_kbps);
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_delete_ba_fail_notify
 功能描述  : 注册删除ba失败的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月15日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_delete_ba_fail_notify(p_alg_delete_ba_fail_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_delete_ba_fail_notify_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_unregister_delete_ba_fail_notify
 功能描述  : 注销删除ba失败的接口
 输入参数  : p_func:算法注册上来的函数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月15日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_delete_ba_fail_notify(oal_void)
{
    gst_alg_main.p_delete_ba_fail_notify_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_delete_ba_fail_notify
 功能描述  : 封装通知算法ba删除失败的钩子
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月15日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_delete_ba_fail_notify(mac_user_stru *pst_mac_user)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,
                       "{dmac_alg_delete_ba_fail_notify:: ERROR INFO: pst_mac_user=0x%x.}",
                       pst_mac_user);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_delete_ba_fail_notify_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_alg_delete_ba_fail_notify::p_delete_ba_fail_notify_func is null}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_delete_ba_fail_notify_func(pst_mac_user);
}

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
/*****************************************************************************
 函 数 名  : dmac_edca_opt_stat_event_process
 功能描述  : 当edca优化统计信息事件处理函数
 输入参数  : pst_event_mem
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月20日
    作    者   : wanran
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_edca_opt_stat_event_process(frw_event_mem_stru *pst_event_mem)
{

    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    dmac_alg_stru           *pst_alg_stru;
    oal_uint8                uc_vap_id;
    oal_uint8                uc_device_id;
    oal_uint32               ul_ret;
    oal_uint8                aast_uc_traffic_num[WLAN_WME_AC_BUTT][ALG_TXRX_DATA_BUTT];

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANTI_INTF, "{dmac_join_set_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);
    uc_vap_id       = pst_event_hdr->uc_vap_id;
    uc_device_id    = pst_event_hdr->uc_device_id;

    oal_memcopy(aast_uc_traffic_num, pst_event->auc_event_data, OAL_SIZEOF(aast_uc_traffic_num));

    /* 调用相关回调函数 */
    pst_alg_stru = &gst_alg_main;

    /* EDCA 算法钩子函数，内部识别多用户多优先级和32用户单优先级业务 */
    if (OAL_PTR_NULL != pst_alg_stru->p_edca_stat_event_notify_func)
    {
        ul_ret = pst_alg_stru->p_edca_stat_event_notify_func(uc_device_id, uc_vap_id, aast_uc_traffic_num);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(uc_vap_id, OAM_SF_ANTI_INTF, "{dmac_edca_opt_stat_event_process::ul_ret=%d", ul_ret);
            return ul_ret;
        }
    }

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
    /*调度更新参数算法钩子函数*/
    if (OAL_PTR_NULL != pst_alg_stru->p_tx_schedule_stat_event_notify_func)
    {
        ul_ret = pst_alg_stru->p_tx_schedule_stat_event_notify_func(uc_device_id, uc_vap_id, aast_uc_traffic_num);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(uc_vap_id, OAM_SF_ANTI_INTF, "{dmac_edca_opt_stat_event_process::ul_ret=%d", ul_ret);
            return ul_ret;
        }
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_edca_stat_event_notify
 功能描述  : 注册抗干扰中EDCA优化统计信息事件的通知函数
 输入参数  : p_func        : 注册的函数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : wanran
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_edca_stat_event_notify(p_alg_edca_stat_event_notify_func p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_edca_stat_event_notify_func = p_func;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_alg_unregister_edca_stat_event_notify
 功能描述  : 去注册抗干扰中EDCA优化统计信息事件的通知函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : wanran
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_unregister_edca_stat_event_notify(oal_void)
{
    gst_alg_main.p_edca_stat_event_notify_func = OAL_PTR_NULL;

    return OAL_SUCC;
}

#endif
/*****************************************************************************
 函 数 名  : dmac_alg_register_dbac_pause_notify
 功能描述  : 注册dbac pause回调
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_dbac_pause_notify(
                p_alg_dbac_pause_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_dbac_pause_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_dbac_resume_notify
 功能描述  : 注册dbac resume回调
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_dbac_resume_notify(
                p_alg_dbac_pause_func   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_dbac_resume_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_register_dbac_is_pause
 功能描述  : 注册dbac pause状态查询回调
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_register_dbac_is_pause(
                p_alg_dbac_is_pause   p_func)
{
    ALG_ASSERT_RET(OAL_PTR_NULL != p_func, OAL_ERR_CODE_PTR_NULL);
    gst_alg_main.p_dbac_is_pause_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_alg_dbac_pause
 功能描述  : 暂停DBAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_dbac_pause(mac_device_stru *pst_mac_device)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_dbac_pause_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_dbac_pause_func(pst_mac_device);
}

/*****************************************************************************
 函 数 名  : dmac_alg_dbac_resume
 功能描述  : 暂停DBAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_alg_dbac_resume(mac_device_stru *pst_mac_device)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_dbac_resume_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_dbac_resume_func(pst_mac_device);
}

/*****************************************************************************
 函 数 名  : dmac_alg_dbac_is_pause
 功能描述  : 暂停DBAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  dmac_alg_dbac_is_pause(mac_device_stru *pst_mac_device)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_alg_main.p_dbac_is_pause_func))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return gst_alg_main.p_dbac_is_pause_func(pst_mac_device);
}





/*lint -e19*/
oal_module_symbol(dmac_alg_register_add_user_notify_func);
oal_module_symbol(dmac_alg_register_device_priv_stru);
oal_module_symbol(dmac_alg_get_device_priv_stru);
oal_module_symbol(dmac_alg_register_tx_schedule_func);
oal_module_symbol(dmac_alg_unregister_tx_schedule_func);

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
oal_module_symbol(dmac_alg_register_tx_schedule_stat_event_notify_func);
oal_module_symbol(dmac_alg_unregister_tx_schedule_stat_event_notify_func);
#endif

oal_module_symbol(dmac_alg_unregister_device_priv_stru);
oal_module_symbol(dmac_alg_unregister_add_user_notify_func);
oal_module_symbol(dmac_alg_create_vap_notify);
oal_module_symbol(dmac_alg_add_assoc_user_notify);
oal_module_symbol(dmac_alg_register_del_user_notify_func);
oal_module_symbol(dmac_alg_unregister_del_user_notify_func);
oal_module_symbol(dmac_alg_unregister_user_priv_stru);
oal_module_symbol(dmac_alg_unregister);
oal_module_symbol(dmac_alg_register_tx_complete_notify_func);
oal_module_symbol(dmac_alg_unregister_tx_notify_func);
oal_module_symbol(dmac_alg_register_user_priv_stru);
oal_module_symbol(dmac_alg_register);
oal_module_symbol(dmac_alg_stop_timer);
oal_module_symbol(dmac_alg_register_timer);
oal_module_symbol(dmac_alg_register_tx_notify_func);
oal_module_symbol(dmac_alg_unregister_tx_complete_notify_func);
oal_module_symbol(dmac_alg_start_timer);
oal_module_symbol(dmac_alg_is_registered);
oal_module_symbol(dmac_alg_unregister_timer);
oal_module_symbol(dmac_alg_register_tid_update_notify_func);
oal_module_symbol(dmac_alg_get_tid_priv_stru);
oal_module_symbol(dmac_alg_register_tid_priv_stru);
oal_module_symbol(dmac_alg_unregister_vap_priv_stru);
oal_module_symbol(dmac_alg_unregister_tid_update_notify_func);
oal_module_symbol(dmac_alg_register_vap_priv_stru);
oal_module_symbol(dmac_alg_unregister_add_vap_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_channel_notify_func);
oal_module_symbol(dmac_alg_register_cfg_channel_notify_func);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_module_symbol(dmac_alg_register_cfg_start_connect_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_start_connect_notify_func);
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */
oal_module_symbol(dmac_alg_register_del_vap_notify_func);
oal_module_symbol(dmac_alg_unregister_tid_priv_stru);
oal_module_symbol(dmac_alg_get_vap_priv_stru);
oal_module_symbol(dmac_alg_unregister_del_vap_notify_func);
oal_module_symbol(dmac_alg_register_add_vap_notify_func);
oal_module_symbol(dmac_alg_get_user_priv_stru);
oal_module_symbol(dmac_alg_register_rx_notify_func);
oal_module_symbol(dmac_alg_unregister_rx_notify_func);
oal_module_symbol(dmac_alg_del_ba);
oal_module_symbol(dmac_alg_get_hal_queue_ppdu_num);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
oal_module_symbol(dmac_alg_set_hal_queue_ppdu_num);
#endif

oal_module_symbol(dmac_alg_get_qap_wme_info);
//#if ALG_SCHEUDLE_EDCA_FEATURE
oal_module_symbol(dmac_alg_set_qap_wme_info);
//#endif
oal_module_symbol(dmac_alg_set_qap_msdu_lifetime);
oal_module_symbol(dmac_alg_get_hal_to_dmac_vap);
oal_module_symbol(dmac_alg_register_config_notify_func);
oal_module_symbol(dmac_alg_unregister_config_notify_func);
oal_module_symbol(dmac_alg_register_downlink_flowctl_notify_func);
oal_module_symbol(dmac_alg_unregister_downlink_flowctl_notify_func);

oal_module_symbol(dmac_alg_register_cfg_user_bandwidth_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_user_bandwidth_notify_func);
oal_module_symbol(dmac_alg_register_cfg_user_protocol_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_user_protocol_notify_func);
oal_module_symbol(dmac_alg_cfg_user_protocol_notify);
oal_module_symbol(dmac_alg_register_rx_mgmt_notify_func);
oal_module_symbol(dmac_alg_unregister_rx_mgmt_notify_func);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_module_symbol(dmac_alg_syn_info);
oal_module_symbol(dmac_alg_voice_aggr);
#endif

#ifdef _PRE_WLAN_FEATURE_DBAC
oal_module_symbol(dmac_alg_register_dmac_misc_event);
oal_module_symbol(dmac_alg_unregister_dmac_misc_event);
oal_module_symbol(dmac_alg_register_enqueue_tid_notify_func);
oal_module_symbol(dmac_alg_unregister_enqueue_tid_notify_func);
oal_module_symbol(dmac_alg_register_vap_down_notify_func);
oal_module_symbol(dmac_alg_unregister_vap_down_notify_func);
oal_module_symbol(dmac_alg_register_probe_req_rx_notify_func);
oal_module_symbol(dmac_alg_unregister_probe_req_rx_notify_func);
#endif

oal_module_symbol(dmac_alg_register_vap_up_notify_func);
oal_module_symbol(dmac_alg_unregister_vap_up_notify_func);

#ifdef _PRE_WLAN_CHIP_TEST_ALG
oal_module_symbol(dmac_alg_register_rx_event_notify);
oal_module_symbol(dmac_alg_unregister_rx_event_notify);
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
oal_module_symbol(dmac_alg_register_flowctl_backp_notify_func);
oal_module_symbol(dmac_alg_unregister_flowctl_backp_notify_func);
oal_module_symbol(dmac_alg_flowctl_backp);
#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
oal_module_symbol(dmac_alg_register_start_stat_rssi_notify);
oal_module_symbol(dmac_alg_unregister_start_stat_rssi_notify);
oal_module_symbol(dmac_alg_register_start_stat_rate_notify);
oal_module_symbol(dmac_alg_unregister_start_stat_rate_notify);
oal_module_symbol(dmac_alg_register_start_stat_best_rate_notify);
oal_module_symbol(dmac_alg_unregister_start_stat_best_rate_notify);
oal_module_symbol(dmac_alg_register_get_rssi_notify);
oal_module_symbol(dmac_alg_unregister_get_rssi_notify);
oal_module_symbol(dmac_alg_register_get_best_rate_notify);
oal_module_symbol(dmac_alg_unregister_get_best_rate_notify);
oal_module_symbol(dmac_alg_register_get_rate_notify);
oal_module_symbol(dmac_alg_unregister_get_rate_notify);
oal_module_symbol(dmac_alg_register_stop_stat_rssi_notify);
oal_module_symbol(dmac_alg_unregister_stop_stat_rssi_notify);
oal_module_symbol(dmac_alg_register_stop_stat_best_rate_notify);
oal_module_symbol(dmac_alg_unregister_stop_stat_best_rate_notify);
oal_module_symbol(dmac_alg_register_stop_stat_rate_notify);
oal_module_symbol(dmac_alg_unregister_stop_stat_rate_notify);

#endif

oal_module_symbol(dmac_alg_register_get_rate_by_table_notify);
oal_module_symbol(dmac_alg_unregister_get_rate_by_table_notify);


oal_module_symbol(dmac_alg_register_cfg_user_spatial_stream_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_user_spatial_stream_notify_func);
oal_module_symbol(dmac_alg_register_dbac_pause_notify);
oal_module_symbol(dmac_alg_register_dbac_resume_notify);
oal_module_symbol(dmac_alg_register_dbac_is_pause);

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
oal_module_symbol(dmac_alg_register_edca_stat_event_notify);
oal_module_symbol(dmac_alg_unregister_edca_stat_event_notify);
#endif

oal_module_symbol(dmac_alg_cfg_user_bandwidth_notify);
oal_module_symbol(dmac_alg_unregister_get_tx_best_rate_notify);
oal_module_symbol(dmac_alg_register_get_tx_best_rate_notify);

#ifdef _PRE_WLAN_FEATURE_CCA_OPT
oal_module_symbol(dmac_alg_register_cfg_cca_intf_mode_notify_func);
oal_module_symbol(dmac_alg_unregister_cfg_cca_intf_mode_notify_func);
oal_module_symbol(dmac_alg_cfg_cca_intf_mode_notify);
#endif

oal_module_symbol(dmac_alg_register_delete_ba_fail_notify);
oal_module_symbol(dmac_alg_unregister_delete_ba_fail_notify);
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

