/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_btcoex.c
  版 本 号   : 初稿
  作    者   : c00221210
  生成日期   : 2014年12月02日
  最近修改   :
  功能描述   : WiFi和bt共存特性文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月02日
    作    者   : c00221210
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "mac_data.h"
#include "dmac_btcoex.h"
#include "dmac_alg_if.h"
#include "dmac_alg.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BTCOEX_C

#define WLAN_TIDNO_COEX_QOSNULL     WLAN_TIDNO_ANT_TRAINING_HIGH_PRIO   /* 发送qos null复用智能天线高优先级训练帧 */
#define BTCOEX_RATE_THRESHOLD_MIN   0
#define BTCOEX_RATE_THRESHOLD_MAX   1
#define BTCOEX_RATE_THRESHOLD_BUTT  2


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
dmac_btcoex_stru gst_dmac_btcoex = {0};

extern oal_uint32  dmac_send_sys_event(mac_vap_stru *pst_mac_vap,
                                                wlan_cfgid_enum_uint16 en_cfg_id,
                                                oal_uint16 us_len,
                                                oal_uint8 *puc_param);
oal_uint8 g_auc_rx_win_size[BTCOEX_RX_WINDOW_SIZE_GRADES][BTCOEX_RX_WINDOW_SIZE_INDEX_MAX] = {
    {1, 4, 8, 64}, {1, 8, 32, 64}
};
/****************************************
              音乐    电话    数传
    2G/20M      0       0       0
    5G/20M      0       0       0
    2G/40M      0       1       1
    5G/40M      0       0       1
    5G/80M      1       1       1
*****************************************/
oal_uint8 g_auc_rx_win_size_grage[WLAN_BAND_BUTT][WLAN_BW_CAP_BUTT][BTCOEX_BT_NUM_OF_ACTIVE_MODE] = {
    /* 2G */
    /* 20M */  /* 40M */
    /* 音乐, 电话, 数传 */
    {{0, 0, 0}, {0, 1, 1}, {1, 1, 1}, {1, 1, 1}},
    /* 5G */
    /* 20M */  /* 40M */  /* 80M */
    /* 音乐, 电话, 数传 */
    {{0, 0, 0}, {0, 0, 1}, {1, 1, 1}, {1, 1, 1}}
};
oal_uint16 g_aus_btcoex_rate_thresholds[WLAN_BAND_BUTT][WLAN_BW_CAP_BUTT][BTCOEX_RATE_THRESHOLD_BUTT] = {
    /* 2G */
    /* 20M */  /* 40M */
    {{23, 60}, {50, 130}, {0, 0},     {0, 0}},
    /* 5G */
    /* 20M */  /* 40M */  /* 80M */
    {{23, 80}, {50, 160}, {108, 340}, {0, 0}}
};
oal_uint32 g_BTCOEX_RX_LOW_RATE_TIME = 5000;
oal_uint32 g_BTCOEX_RX_STATISTICS_TIME = 2000;
oal_uint32 g_rx_statistics_print = 0;
oal_uint32 g_delba = 1;


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_btcoex_encap_preempt_sta
 功能描述  : 根据指定的PS位封null data帧
 输入参数  : oal_uint8 *puc_frame

 输出参数  : 无
 返 回 值  : OAL_STATIC  OAL_INLINE  void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月10日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_btcoex_encap_preempt_sta(oal_uint8 *puc_frame,
                                                               oal_uint8 *puc_da,
                                                               oal_uint8 *puc_sa,
                                                               coex_preempt_frame_enum_uint8 en_preempt_type)
{
    oal_uint32                        ul_qosnull_seq_num = 0;
    /* 填写帧头,其中from ds为1，to ds为0，ps=1 因此frame control的第二个字节为12 */
    if (BTCOEX_NULLDATA == en_preempt_type)
    {

        mac_ieee80211_frame_stru *pst_mac_header = (mac_ieee80211_frame_stru *)puc_frame;
        mac_null_data_encap(puc_frame,
                            WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA | 0x1100,
                            puc_da,
                            puc_sa);
        /* 设定seq num和frag */
        puc_frame[22] = 0;
        puc_frame[23] = 0;
        pst_mac_header->st_frame_control.bit_power_mgmt = 1;
    }
    else if (BTCOEX_QOSNULL == en_preempt_type)
    {
        dmac_btcoex_qosnull_frame_stru *pst_mac_header = (dmac_btcoex_qosnull_frame_stru *)puc_frame;
        mac_null_data_encap(puc_frame,
                            WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS_NULL | 0x1100,
                            puc_da,
                            puc_sa);
        pst_mac_header->st_frame_control.bit_power_mgmt = 1;
        pst_mac_header->bit_qc_tid = WLAN_TIDNO_COEX_QOSNULL;
        pst_mac_header->bit_qc_eosp = 0;

        /* 设置seq的序列号 */
        hal_get_btcoex_abort_qos_null_seq_num(&ul_qosnull_seq_num);
        pst_mac_header->bit_sc_seq_num = (ul_qosnull_seq_num + 1);
        hal_set_btcoex_abort_qos_null_seq_num(pst_mac_header->bit_sc_seq_num);

        /*协议规定单播的QOS NULL DATA只允许normal ack 共存里面要设置0是对方会回ack */
        pst_mac_header->bit_qc_ack_polocy = WLAN_TX_NORMAL_ACK;

    }
    else
    {
    }

}

/*****************************************************************************
 函 数 名  : dmac_btcoex_init_preempt
 功能描述  :
 输入参数  : pst_dmac_vap
             pst_dmac_user
 输出参数  : 无
 返 回 值  : OAL_SUCC或者其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_init_preempt(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, coex_preempt_frame_enum_uint8 en_preempt_type)
{
    /* 填写帧头*/
    dmac_btcoex_encap_preempt_sta(gst_dmac_btcoex.auc_null_qosnull_frame,
                                  pst_mac_user->auc_user_mac_addr,
                                  pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                                  en_preempt_type);

    hal_set_btcoex_abort_null_buff_addr((oal_uint32)gst_dmac_btcoex.auc_null_qosnull_frame);

    return;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_status_event_handler
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : g00306640
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_btcoex_update_ba_size(mac_vap_stru *pst_mac_vap, hal_btcoex_wifi_status_stru *pst_wifi_status, hal_btcoex_btble_status_stru *pst_btble_status)
{
    bt_status_stru *pst_bt_status;
    ble_status_stru *pst_ble_status;
    oal_uint8 uc_bt_active_mode;
    oal_uint8 uc_bt_rx_win_size_grade;
    oal_uint8 uc_band;
    oal_uint8 uc_bandwidth;

    pst_bt_status = &(pst_btble_status->un_bt_status.st_bt_status);
    pst_ble_status = &(pst_btble_status->un_ble_status.st_ble_status);

    uc_band = pst_mac_vap->st_channel.en_band;
    mac_vap_get_bandwidth_cap(pst_mac_vap, &uc_bandwidth);
    if ((uc_band >= WLAN_BAND_BUTT) || (uc_bandwidth >= WLAN_BW_CAP_BUTT))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_update_ba_size::band %d, bandwidth %d exceed scale!}",
                         uc_band, uc_bandwidth);
        return;
    }
    if (pst_wifi_status->uc_ba_size_index >= BTCOEX_RX_WINDOW_SIZE_INDEX_MAX)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_update_ba_size::ba_size_index %d exceed scale!}",
                         pst_wifi_status->uc_ba_size_index);
        return;
    }

    if (pst_bt_status->bit_bt_sco)
    {
        uc_bt_active_mode = 1;
    }
    else if (pst_bt_status->bit_bt_a2dp || pst_ble_status->bit_ble_scan)
    {
        uc_bt_active_mode = 0;
    }
    else if (pst_ble_status->bit_bt_transfer)
    {
        uc_bt_active_mode = 2;
    }
    else
    {
        uc_bt_active_mode = BTCOEX_BT_NUM_OF_ACTIVE_MODE;
    }

    /* BT没有业务, 聚合64 */
    if (uc_bt_active_mode >= BTCOEX_BT_NUM_OF_ACTIVE_MODE)
    {
        uc_bt_active_mode = 0;
        pst_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
    }

    uc_bt_rx_win_size_grade = g_auc_rx_win_size_grage[uc_band][uc_bandwidth][uc_bt_active_mode];

    pst_wifi_status->uc_ba_size = g_auc_rx_win_size[uc_bt_rx_win_size_grade][pst_wifi_status->uc_ba_size_index];
}

/*****************************************************************************
 函 数 名  : dmac_bt_transfer_status_handler
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : c000221210
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_bt_transfer_status_handler(frw_event_mem_stru *pst_event_mem)
{
    oal_uint8 uc_vap_idx;
    frw_event_stru *pst_event;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
    mac_device_stru *pst_mac_device;
    mac_vap_stru *pst_mac_vap;
    hal_to_dmac_device_stru *pst_hal_device;
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_bt_transfer_status_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_bt_transfer_status_handler::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;
    pst_btcoex_btble_status = &(pst_hal_device->st_btcoex_btble_status);

    if (pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_transfer)
    {
        dmac_alg_cfg_btcoex_state_notify(pst_mac_device,BT_TRANSFER_ON);
    }
    else
    {
        dmac_alg_cfg_btcoex_state_notify(pst_mac_device,BT_TRANSFER_OFF);
    }

    pst_btcoex_wifi_status = &(pst_hal_device->st_btcoex_wifi_status);

    /* 正常bt打开和关闭场景下，对聚合进行处理 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_bt_transfer_status_handler::vap is null! vap id is %d}", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state || MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state)
        {
            if ((pst_btcoex_btble_status->un_bt_status.st_bt_status.bit_bt_on) && (pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_transfer))
            {
                pst_btcoex_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
                pst_btcoex_wifi_status->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
            }
            else
            {
                pst_btcoex_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
                pst_btcoex_wifi_status->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
            }
            dmac_btcoex_update_ba_size(pst_mac_vap, pst_btcoex_wifi_status, pst_btcoex_btble_status);
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_bt_transfer_status_handler::bt transfer status changed:%d, bar_size: %d}",
                    pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_transfer,
                    pst_btcoex_wifi_status->uc_ba_size);

            dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, pst_btcoex_wifi_status->uc_ba_size);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_rx_rate_statistics_flag_callback
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : g00306640
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_rx_rate_statistics_flag_callback(oal_void *p_arg)
{
    mac_device_stru *pst_mac_device;
    mac_vap_stru *pst_mac_vap;
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;

    pst_mac_vap = (mac_vap_stru *)p_arg;
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_DBAC, "{dmac_btcoex_rx_rate_statistics_flag_callback::pst_device[id:%d] NULL}",
                    pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_btcoex_wifi_status = &(pst_mac_device->pst_device_stru->st_btcoex_wifi_status);
    pst_btcoex_btble_status = &(pst_mac_device->pst_device_stru->st_btcoex_btble_status);

    if (pst_btcoex_wifi_status->st_btcoex_rx_info.us_rx_rate_stat_count < BTCOEX_RX_COUNT_LIMIT)
    {
        OAL_MEMZERO(&(pst_btcoex_wifi_status->st_btcoex_rx_info), OAL_SIZEOF(hal_btcoex_wifi_rx_info_stru));
        return OAL_SUCC;
    }

    pst_btcoex_wifi_status->uc_rx_rate_statistics_timeout = OAL_TRUE;

    /* BT业务结束 */
    if (OAL_FALSE == pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_ba)
    {
        pst_btcoex_wifi_status->uc_rx_rate_statistics_flag = OAL_FALSE;
        FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->bt_coex_statistics_timer));
        FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->bt_coex_low_rate_timer));
        if (BTCOEX_RX_WINDOW_SIZE_INDEX_3 != pst_btcoex_wifi_status->uc_ba_size_addba_rsp_index)
        {
            pst_btcoex_wifi_status->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
            pst_btcoex_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
            dmac_btcoex_update_ba_size(pst_mac_vap, pst_btcoex_wifi_status, pst_btcoex_btble_status);
            dmac_btcoex_delba_trigger(pst_mac_vap, OAL_TRUE, pst_btcoex_wifi_status->uc_ba_size);
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_status_event_handler
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月19日
    作    者   : c000221210
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_status_event_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru *pst_event;
    oal_uint8 uc_vap_idx;
    mac_vap_stru *pst_mac_vap;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    hal_btcoex_btble_status_stru *pst_btble_status;
    hal_btcoex_wifi_status_stru *pst_wifi_status;
    oal_uint8 uc_need_delba;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_btble_status = &(pst_hal_device->st_btcoex_btble_status);
    pst_wifi_status = &(pst_hal_device->st_btcoex_wifi_status);
    uc_need_delba = OAL_FALSE;

    /* 正常bt打开和关闭场景下，对聚合进行处理 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::vap is null! vap id is %d}", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state || MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state)
        {
            if ((pst_btble_status->un_bt_status.st_bt_status.bit_bt_on) && (pst_btble_status->un_ble_status.st_ble_status.bit_bt_ba))
            {
                if (BTCOEX_RX_WINDOW_SIZE_INDEX_3 == pst_wifi_status->uc_ba_size_addba_rsp_index)
                {
                    if (pst_btble_status->un_bt_status.st_bt_status.bit_bt_sco)
                    {
                        /* 电话场景下，需要立即删减ba，不然，很快会导致有些AP速率降低成1M */
                        pst_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_0;
                        uc_need_delba = OAL_TRUE;
                    }
                    else
                    {
                        pst_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
                    }
                }
                else
                {
                    pst_wifi_status->uc_ba_size_index = pst_wifi_status->uc_ba_size_addba_rsp_index;
                }
            }
            else
            {
                pst_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
            }
            dmac_btcoex_update_ba_size(pst_mac_vap, pst_wifi_status, pst_btble_status);
            OAM_WARNING_LOG3(0, OAM_SF_COEX, "{dmac_btcoex_status_event_handler::bt ba status changed:%d, bar_size: %d uc_need_delba:%d}",
                    pst_btble_status->un_ble_status.st_ble_status.bit_bt_ba,
                    pst_wifi_status->uc_ba_size,uc_need_delba);
            dmac_btcoex_delba_trigger(pst_mac_vap, uc_need_delba, pst_wifi_status->uc_ba_size);

            pst_wifi_status->uc_rx_rate_statistics_flag = OAL_TRUE;
            pst_wifi_status->uc_rx_rate_statistics_timeout = OAL_FALSE;
            FRW_TIMER_CREATE_TIMER(&(pst_mac_device->bt_coex_statistics_timer),
                                       dmac_btcoex_rx_rate_statistics_flag_callback,
                                       g_BTCOEX_RX_STATISTICS_TIME,
                                       (void *)pst_mac_vap,
                                       OAL_TRUE,
                                       OAM_MODULE_ID_DMAC,
                                       pst_mac_device->ul_core_id);
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_register_dmac_misc_event
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : g00306640
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32 dmac_btcoex_register_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type, oal_uint32 (*p_func)(frw_event_mem_stru *))
{
    if(en_event_type >= HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT || NULL == p_func)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "dmac_alg_register_dmac_misc_event fail");
        return  OAL_FAIL;
    }

    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = p_func;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_unregister_dmac_misc_event
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : g00306640
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  dmac_btcoex_unregister_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type)
{
    if(en_event_type >= HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "dmac_alg_unregister_dmac_misc_event fail");
        return  OAL_FAIL;
    }

    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = NULL;
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_init()
 功能描述  : 初始化共存相关的参数
 输出参数  : 无
 返 回 值  : oal_err_code_enum_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月02日
    作    者   : c00221210
    修改内容   : 新生成函数
  2.日    期   : 2014年12月25日
    作    者   : g00306640
    修改内容   : 修改

*****************************************************************************/
oal_uint32 dmac_btcoex_init(oal_void)
{
    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_PS_BTCOEX, dmac_btcoex_status_event_handler))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event fail!}");
        return OAL_FAIL;
    }

    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_BT_TRANSFER, dmac_bt_transfer_status_handler))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event fail!}");
        dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_PS_BTCOEX);
        return OAL_FAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_exit()
 功能描述  : 初始化共存相关的参数
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月02日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_btcoex_exit(oal_void)
{
    /* init coexit wifi bt param */
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_PS_BTCOEX);
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_BT_TRANSFER);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_wlan_priority_set()
 功能描述  : 软件设定高优先级保护
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月27日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_wlan_priority_set(mac_device_stru *pst_mac_device, oal_uint8 uc_value, oal_uint8 uc_timeout_ms)
{
    oal_uint8 *puc_state;
    oal_uint8 uc_set = OAL_FALSE;
    oal_uint32 ul_now_ms;
    oal_uint32 *pul_old_timestamp_ms;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device) || OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device->pst_device_stru))
    {
        OAM_ERROR_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_wlan_priority_set::pst_mac_device/pst_hal_device null, prio value: %d}", uc_value);
        return;
    }

    puc_state = &(pst_mac_device->pst_device_stru->st_btcoex_wifi_status.uc_prio_occupied_state);
    pul_old_timestamp_ms = &(pst_mac_device->pst_device_stru->st_btcoex_wifi_status.ul_timestamp);


    /* 需要拉高prio */
    if (OAL_TRUE == uc_value)
    {
        /* 当前没有拉高prio并且可以拉高prio */
        if (OAL_FALSE == *puc_state)
        {

            /* 需要与上一次拉低时间间隔至少100ms */
            ul_now_ms = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            if (ul_now_ms - (*pul_old_timestamp_ms) > 50)
            {
                /* 启动priority定时器 */
                FRW_TIMER_CREATE_TIMER(&pst_mac_device->bt_coex_priority_timer,
                                           dmac_btcoex_wlan_priority_timeout_callback,
                                           uc_timeout_ms,
                                           (oal_void *)pst_mac_device,
                                           OAL_FALSE,
                                           OAM_MODULE_ID_DMAC,
                                           pst_mac_device->ul_core_id);
                (*puc_state) = OAL_TRUE;

                uc_set = OAL_TRUE;
            }
            else
            {
            }
        }
    }
    /* 需要拉低prio */
    else
    {
        if (OAL_TRUE == *puc_state)
        {
            (*puc_state) = OAL_FALSE;

            *pul_old_timestamp_ms = (oal_uint32)OAL_TIME_GET_STAMP_MS();
        }
        uc_set = OAL_TRUE;
    }

    if (OAL_TRUE == uc_set)
    {
        /* uc_value == 1, 软件配置高优先级；uc_value == 0, 返回给硬件配置 */
        hal_set_btcoex_hw_rx_priority_dis((oal_uint8)(!uc_value));

        /* 设置软件配置优先级 */
        hal_set_btcoex_hw_priority_en((oal_uint8)(!uc_value));

        /* 软件设置优先级 */
        hal_set_btcoex_sw_priority_flag(uc_value);
    }

}

/*****************************************************************************
 函 数 名  : dmac_btcoex_wlan_priority_timeout_callback()
 功能描述  : 软件设定高优先级保护超时函数
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月27日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_btcoex_wlan_priority_timeout_callback(oal_void *p_arg)
{
    mac_device_stru     *pst_mac_device = (mac_device_stru *)p_arg;

    dmac_btcoex_wlan_priority_set(pst_mac_device, 0, 0);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_change_state_syn
 功能描述  : 同步dmac vap状态
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月25日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_change_state_syn(mac_vap_stru *pst_mac_vap)
{
    switch (pst_mac_vap->en_vap_state)
    {
    case MAC_VAP_STATE_STA_WAIT_SCAN:
    case MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2:
    case MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4:
    case MAC_VAP_STATE_STA_AUTH_COMP:
    case MAC_VAP_STATE_STA_WAIT_ASOC:
    case MAC_VAP_STATE_STA_OBSS_SCAN:
    case MAC_VAP_STATE_STA_BG_SCAN:
        hal_set_btcoex_hw_rx_priority_dis(0);
        break;
    default:
        hal_set_btcoex_hw_rx_priority_dis(1);
    }
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_rx_delba_trigger
 功能描述  : Change ba size
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_delba_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_need_delba,oal_uint8 uc_ba_size)
{
    dmac_to_hmac_btcoex_rx_delba_trigger_event_stru  st_dmac_to_hmac_btcoex_rx_delba;

    st_dmac_to_hmac_btcoex_rx_delba.uc_need_delba = uc_need_delba;
    st_dmac_to_hmac_btcoex_rx_delba.uc_ba_size = uc_ba_size;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_BTCOEX_RX_DELBA_TRIGGER, OAL_SIZEOF(dmac_to_hmac_btcoex_rx_delba_trigger_event_stru), (oal_uint8 *)&st_dmac_to_hmac_btcoex_rx_delba);
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_vap_up_handle
 功能描述  : 处理vap_up，给BT发送中断
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_vap_up_handle(mac_vap_stru *pst_mac_vap)
{
    oal_uint8 uc_chan_idx;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    bt_status_stru *pst_bt_status;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_btcoex_vap_up_handle::pst_mac_device null.}");
        return;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    if (OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_vap_up_handle::pst_hal_device null.}");
        return;
    }

    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_band, BIT0, 0);   // 频段
    mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.uc_chan_number, &uc_chan_idx);
    hal_set_btcoex_soc_gpreg0(uc_chan_idx, BIT5 | BIT4 | BIT3 | BIT2 | BIT1, 1);   // 信道
    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_bandwidth, BIT8 | BIT7 | BIT6, 6);   // 带宽
    hal_set_btcoex_soc_gpreg0(OAL_TRUE, BIT13, 13);
    hal_coex_sw_irq_set(BIT5);

    hal_update_btcoex_btble_status(pst_hal_device);

    pst_bt_status = &(pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status);

    if (pst_bt_status->bit_bt_on)
    {
        hi1102_set_btcoex_sw_all_abort_ctrl(OAL_TRUE);
    }

    /* 状态上报BT: 信道，带宽，频率等*/
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                 "{dmac_btcoex_vap_up_handle::VAP state->TRUE, channel state: band->%d, channel->%d, bandwidth->%d, bit status[%d]",
                 pst_mac_vap->st_channel.en_band,
                 pst_mac_vap->st_channel.uc_chan_number,
                 pst_mac_vap->st_channel.en_bandwidth,
                 pst_bt_status->bit_bt_on);
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_vap_down_handle
 功能描述  : 处理vap_down，给BT发送中断
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_vap_down_handle(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_btcoex_vap_down_handle::pst_mac_device null.}");

        return;
    }

    if (0 == mac_device_calc_up_vap_num(pst_mac_device))
    {
        /* 状态上报BT */
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_btcoex_vap_down_handle::Notify BT cancel AFH.}");
        hal_set_btcoex_soc_gpreg1(OAL_FALSE, BIT3, 3);
        hal_coex_sw_irq_set(BIT5);
    }
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_update_rx_rate_threshold
 功能描述  : 获取速率门限
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月23日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_update_rx_rate_threshold (mac_vap_stru *pst_mac_vap, hal_btcoex_wifi_status_stru *pst_wifi_status)
{
    oal_uint8 uc_band;
    oal_uint8 uc_bandwidth;

    uc_band = pst_mac_vap->st_channel.en_band;
    mac_vap_get_bandwidth_cap(pst_mac_vap, &uc_bandwidth);

    if ((uc_band >= WLAN_BAND_BUTT) || (uc_bandwidth >= WLAN_BW_CAP_BUTT))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_update_rx_rate_threshold::band %d, bandwidth %d exceed scale!}",
                         uc_band, uc_bandwidth);
        return;
    }
    pst_wifi_status->ul_rx_rate_threshold_min = g_aus_btcoex_rate_thresholds[uc_band][uc_bandwidth][BTCOEX_RATE_THRESHOLD_MIN];
    pst_wifi_status->ul_rx_rate_threshold_max = g_aus_btcoex_rate_thresholds[uc_band][uc_bandwidth][BTCOEX_RATE_THRESHOLD_MAX];

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_update_rx_rate_threshold:: min: %d, max: %d, band %d, bandwidth %d.}",
                        pst_wifi_status->ul_rx_rate_threshold_min, pst_wifi_status->ul_rx_rate_threshold_max, uc_band, uc_bandwidth);

}

/*****************************************************************************
 函 数 名  : dmac_config_btcoex_assoc_state_syn
 功能描述  : 同步共存下mac的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : c00221210
    修改内容   : 新生成函数
  2.日    期   : 2015年07月28日
    作    者   : g00306640
    修改内容   : 不区分sta和ap

*****************************************************************************/
oal_uint32 dmac_config_btcoex_assoc_state_syn(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    oal_uint8 uc_chan_idx;
    oal_uint8 uc_need_delba;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    coex_preempt_frame_enum_uint8 en_preempt_type;
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
    ble_status_stru *pst_ble_status;

    pst_mac_device = mac_res_get_dev((oal_uint32)pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_config_btcoex_assoc_state_syn::VAP STATE[%d].}", pst_mac_vap->en_vap_state);
        return OAL_FAIL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    en_preempt_type = BTCOEX_NOFRAME;

    pst_btcoex_wifi_status = &(pst_hal_device->st_btcoex_wifi_status);

    pst_btcoex_wifi_status->en_all_abort_preempt_type = en_preempt_type;

    dmac_btcoex_update_rx_rate_threshold(pst_mac_vap, pst_btcoex_wifi_status);

    dmac_btcoex_init_preempt(pst_mac_vap, pst_mac_user, en_preempt_type);

    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_band, BIT0, 0);    // 频段
    mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.uc_chan_number, &uc_chan_idx);
    hal_set_btcoex_soc_gpreg0(uc_chan_idx, BIT5 | BIT4 | BIT3 | BIT2 | BIT1, 1);    // 信道
    hal_set_btcoex_soc_gpreg0(pst_mac_vap->st_channel.en_bandwidth, BIT8 | BIT7 | BIT6, 6); // 带宽
    hal_set_btcoex_soc_gpreg0(OAL_TRUE, BIT13, 13);
    hal_set_btcoex_soc_gpreg1(OAL_FALSE, BIT2, 2);
    hal_set_btcoex_soc_gpreg1(OAL_TRUE, BIT3, 3);
    hal_coex_sw_irq_set(BIT5);

    pst_btcoex_wifi_status = &(pst_hal_device->st_btcoex_wifi_status);
    pst_btcoex_btble_status = &(pst_hal_device->st_btcoex_btble_status);
    pst_ble_status = &(pst_btcoex_btble_status->un_ble_status.st_ble_status);

    uc_need_delba = OAL_FALSE;
    pst_btcoex_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;
    pst_btcoex_wifi_status->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_3;

    /* DTS2016010901179 BT无业务时,恢复wifi控制聚合 */
    if (0 == pst_ble_status->bit_bt_transfer && 0 == pst_ble_status->bit_bt_ba)
    {
        dmac_btcoex_delba_trigger(pst_mac_vap, OAL_FALSE, 0);
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_COEX, "{dmac_config_btcoex_assoc_state_syn::bt not working, ba size to default.}");
        return OAL_SUCC;
    }

    if (pst_ble_status->bit_bt_transfer)
    {
        dmac_alg_cfg_btcoex_state_notify(pst_mac_device, BT_TRANSFER_ON);

        pst_btcoex_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
        pst_btcoex_wifi_status->uc_ba_size_addba_rsp_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
    }
    else if (pst_ble_status->bit_bt_ba)
    {
        pst_btcoex_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_2;
        pst_btcoex_wifi_status->uc_rx_rate_statistics_flag = OAL_TRUE;
        pst_btcoex_wifi_status->uc_rx_rate_statistics_timeout = OAL_FALSE;
        FRW_TIMER_CREATE_TIMER(&(pst_mac_device->bt_coex_statistics_timer),
                                   dmac_btcoex_rx_rate_statistics_flag_callback,
                                   g_BTCOEX_RX_STATISTICS_TIME,
                                   (void *)pst_mac_vap,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
    }

    dmac_btcoex_update_ba_size(pst_mac_vap, pst_btcoex_wifi_status, pst_btcoex_btble_status);
    OAM_WARNING_LOG4(0, OAM_SF_COEX, "{dmac_config_btcoex_assoc_state_syn::bt ba status:%d, transfer status:%d, bar_size:%d, uc_need_delba:%d}",
                        pst_ble_status->bit_bt_ba,
                        pst_ble_status->bit_bt_transfer,
                        pst_btcoex_wifi_status->uc_ba_size,
                        uc_need_delba);
    dmac_btcoex_delba_trigger(pst_mac_vap, uc_need_delba, pst_btcoex_wifi_status->uc_ba_size);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_rx_average_rate_calculate
 功能描述  : 统计平均速率
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月23日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_btcoex_rx_average_rate_calculate (hal_to_dmac_device_stru *pst_hal_device, oal_int32 *pl_rx_rssi, oal_uint32 *pul_rx_rate)
{
    hal_btcoex_wifi_rx_info_stru *pst_btcoex_wifi_rx_rate_info;

    pst_btcoex_wifi_rx_rate_info = &(pst_hal_device->st_btcoex_wifi_status.st_btcoex_rx_info);

    if (0 != pst_btcoex_wifi_rx_rate_info->us_rx_rssi_stat_count)
    {
        *pl_rx_rssi = pst_btcoex_wifi_rx_rate_info->l_rx_rssi / pst_btcoex_wifi_rx_rate_info->us_rx_rssi_stat_count;
    }
    else
    {
        pst_btcoex_wifi_rx_rate_info->l_rx_rssi = 0;
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_rx_average_rate_calculate::rx_rssi_count == 0}");
        return;
    }
    if (0 != pst_btcoex_wifi_rx_rate_info->us_rx_rate_stat_count)
    {
        *pul_rx_rate = pst_btcoex_wifi_rx_rate_info->ul_rx_rate_mbps / pst_btcoex_wifi_rx_rate_info->us_rx_rate_stat_count;
    }
    else
    {
        pst_btcoex_wifi_rx_rate_info->ul_rx_rate_mbps = 0;
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_rx_average_rate_calculate::rx_rate_count == 0}");
        return;
    }
    OAL_MEMZERO(pst_btcoex_wifi_rx_rate_info, OAL_SIZEOF(hal_btcoex_wifi_rx_info_stru));

}

/*****************************************************************************
 函 数 名  : dmac_btcoex_low_rate_callback
 功能描述  : 接收降速后处理
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月9日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_btcoex_low_rate_callback(oal_void *p_arg)
{
    mac_vap_stru *pst_vap = (mac_vap_stru *)p_arg;
    mac_device_stru *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;
    hal_btcoex_wifi_status_stru *pst_wifi_status;
    hal_btcoex_btble_status_stru *pst_btble_status;
    oal_int32 l_rx_rssi = 0;
    oal_uint32 ul_rx_rate = 0;
    oal_uint32 ul_rate_threshold_min;
    oal_uint32 ul_rate_threshold_max;

    pst_mac_device = mac_res_get_dev(0);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_DBAC, "{dmac_btcoex_low_rate_callback::pst_device[id:0] is NULL}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    pst_wifi_status = &(pst_hal_device->st_btcoex_wifi_status);
    pst_btble_status = &(pst_hal_device->st_btcoex_btble_status);
    ul_rate_threshold_min = pst_wifi_status->ul_rx_rate_threshold_min;
    ul_rate_threshold_max = pst_wifi_status->ul_rx_rate_threshold_max;

    if (OAL_FALSE == pst_wifi_status->uc_get_addba_req_flag)
    {
        dmac_btcoex_rx_average_rate_calculate(pst_hal_device, &l_rx_rssi, &ul_rx_rate);

        if (l_rx_rssi > BTCOEX_RSSI_THRESHOLD)
        {
            if (((BTCOEX_RX_WINDOW_SIZE_DECREASE == pst_wifi_status->uc_ba_size_tendence)
                    && (ul_rx_rate < pst_wifi_status->ul_rx_rate_threshold_min))
                || ((BTCOEX_RX_WINDOW_SIZE_INCREASE == pst_wifi_status->uc_ba_size_tendence)
                    && (ul_rx_rate > pst_wifi_status->ul_rx_rate_threshold_max))
                || ((BTCOEX_RX_WINDOW_SIZE_DECREASE == pst_wifi_status->uc_ba_size_tendence)
                    && (BTCOEX_RX_WINDOW_SIZE_INDEX_3 == pst_wifi_status->uc_ba_size_addba_rsp_index)
                    && (ul_rx_rate < (ul_rate_threshold_min + (ul_rate_threshold_max >> 1)))))
            {
                if (g_delba)
                {
                    pst_wifi_status->uc_ba_size_addba_rsp_index = pst_wifi_status->uc_ba_size_index;
                    dmac_btcoex_update_ba_size(pst_vap, pst_wifi_status, pst_btble_status);
                    dmac_btcoex_delba_trigger(pst_vap, OAL_TRUE, pst_wifi_status->uc_ba_size);
                    OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_low_rate_callback::ba_size change to: %d, rate: %d.}", pst_wifi_status->uc_ba_size, ul_rx_rate);
                }
            }
            else
            {
                /* 保持现有聚合不变 */
                pst_wifi_status->uc_ba_size_index = pst_wifi_status->uc_ba_size_addba_rsp_index;
                dmac_btcoex_update_ba_size(pst_vap, pst_wifi_status, pst_btble_status);
                OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_low_rate_callback::ba_size dont change: %d, rate: %d.}", pst_wifi_status->uc_ba_size, ul_rx_rate);
            }
        }
    }
    else
    {
        pst_wifi_status->uc_ba_size_addba_rsp_index = pst_wifi_status->uc_ba_size_index;
        OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_low_rate_callback::receive addba req before delba.}");
    }

    FRW_TIMER_RESTART_TIMER(&(pst_mac_device->bt_coex_statistics_timer), g_BTCOEX_RX_STATISTICS_TIME, OAL_TRUE);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_btcoex_bt_low_rate_process
 功能描述  : 接收降速后处理
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月9日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_bt_low_rate_process (mac_vap_stru *pst_vap,
                                                hal_to_dmac_device_stru *pst_hal_device)
{
    mac_device_stru *pst_mac_device;
    oal_uint32 ul_rx_rate_temp_mbps = 0;
    oal_uint32 ul_rx_rate = 0;
    oal_int32 l_rx_rssi = 0;
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
    bt_status_stru *pst_bt_status;
    oal_uint32 ul_rate_threshold_min;
    oal_uint32 ul_rate_threshold_max;

    pst_btcoex_wifi_status = &(pst_hal_device->st_btcoex_wifi_status);

    /* 累加接收速率 */
    if (pst_btcoex_wifi_status->uc_rx_rate_statistics_flag)
    {
        if (0 != pst_hal_device->l_rx_rssi)
        {
            pst_btcoex_wifi_status->st_btcoex_rx_info.l_rx_rssi += pst_hal_device->l_rx_rssi;
            pst_btcoex_wifi_status->st_btcoex_rx_info.us_rx_rssi_stat_count++;
        }
        if (0 != pst_hal_device->ul_rx_rate)
        {
            ul_rx_rate_temp_mbps = pst_hal_device->ul_rx_rate >> 10;
            pst_btcoex_wifi_status->st_btcoex_rx_info.ul_rx_rate_mbps += ul_rx_rate_temp_mbps;
            pst_btcoex_wifi_status->st_btcoex_rx_info.us_rx_rate_stat_count++;
        }
    }
    else
    {
        return;
    }

    /* 计算接收速率 */
    if (pst_btcoex_wifi_status->uc_rx_rate_statistics_timeout)
    {
        pst_btcoex_wifi_status->uc_rx_rate_statistics_timeout = OAL_FALSE;

        dmac_btcoex_rx_average_rate_calculate(pst_hal_device, &l_rx_rssi, &ul_rx_rate);

        if (g_rx_statistics_print)
        {
            OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::rssi: %d, rate: %d.}", l_rx_rssi, ul_rx_rate);
        }
    }
    else
    {
        return;
    }

    /* 处理近场速率 */
    if (l_rx_rssi > BTCOEX_RSSI_THRESHOLD)
    {
        pst_btcoex_btble_status = &(pst_hal_device->st_btcoex_btble_status);
        pst_bt_status = &(pst_btcoex_btble_status->un_bt_status.st_bt_status);
        pst_btcoex_wifi_status->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_HOLD;
        pst_btcoex_wifi_status->uc_ba_size_index = pst_btcoex_wifi_status->uc_ba_size_addba_rsp_index;
        ul_rate_threshold_min = pst_btcoex_wifi_status->ul_rx_rate_threshold_min;
        ul_rate_threshold_max = pst_btcoex_wifi_status->ul_rx_rate_threshold_max;

        /* 5G80M音乐固定2档 */
        if ((WLAN_BAND_5G == pst_vap->st_channel.en_band) && (pst_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_40MINUS)
                && (pst_bt_status->bit_bt_a2dp))
        {
            if ((BTCOEX_RX_WINDOW_SIZE_INDEX_3 == pst_btcoex_wifi_status->uc_ba_size_index)
                    && (ul_rx_rate < (ul_rate_threshold_min + (ul_rate_threshold_max >> 1))))
            {
                pst_btcoex_wifi_status->uc_ba_size_index--;
                pst_btcoex_wifi_status->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_DECREASE;
            }
            else if (pst_btcoex_wifi_status->uc_ba_size_index < BTCOEX_RX_WINDOW_SIZE_INDEX_2)
            {
                pst_btcoex_wifi_status->uc_ba_size_index++;
                pst_btcoex_wifi_status->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_INCREASE;
            }
        }
        else
        {
            switch (pst_btcoex_wifi_status->uc_ba_size_index)
            {
                case BTCOEX_RX_WINDOW_SIZE_INDEX_3:
                    if (ul_rx_rate < (ul_rate_threshold_min + (ul_rate_threshold_max >> 1)))
                    {
                        /* 20M电话优先档位0 */
                        if ((WLAN_BAND_WIDTH_20M == pst_vap->st_channel.en_bandwidth) && (pst_bt_status->bit_bt_sco))
                        {
                            pst_btcoex_wifi_status->uc_ba_size_index = BTCOEX_RX_WINDOW_SIZE_INDEX_0;
                        }
                        else
                        {
                            pst_btcoex_wifi_status->uc_ba_size_index--;
                        }
                        pst_btcoex_wifi_status->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_DECREASE;
                    }
                    break;
                case BTCOEX_RX_WINDOW_SIZE_INDEX_2:
                    if (ul_rx_rate < ul_rate_threshold_min)
                    {
                        pst_btcoex_wifi_status->uc_ba_size_index--;
                        pst_btcoex_wifi_status->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_DECREASE;
                    }
                    break;
                case BTCOEX_RX_WINDOW_SIZE_INDEX_1:
                    if (ul_rx_rate < ul_rate_threshold_min)
                    {
                        pst_btcoex_wifi_status->uc_ba_size_index--;
                        pst_btcoex_wifi_status->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_DECREASE;
                    }
                    /* 电话场景不升到2档，最大升到1档 */
                    else if ((ul_rx_rate > ul_rate_threshold_max) && (OAL_FALSE == pst_bt_status->bit_bt_sco))
                    {
                        pst_btcoex_wifi_status->uc_ba_size_index++;
                        pst_btcoex_wifi_status->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_INCREASE;
                    }
                    break;
                case BTCOEX_RX_WINDOW_SIZE_INDEX_0:
                    if (ul_rx_rate > ul_rate_threshold_max)
                    {
                        pst_btcoex_wifi_status->uc_ba_size_index++;
                        pst_btcoex_wifi_status->uc_ba_size_tendence = BTCOEX_RX_WINDOW_SIZE_INCREASE;
                    }
                    break;
                default:
                    OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::ba_size_index error: %d.}",
                                pst_btcoex_wifi_status->uc_ba_size_index);
                    break;
            }
        }

        if (BTCOEX_RX_WINDOW_SIZE_HOLD != pst_btcoex_wifi_status->uc_ba_size_tendence)
        {
            dmac_btcoex_update_ba_size(pst_vap, pst_btcoex_wifi_status, pst_btcoex_btble_status);
            dmac_btcoex_delba_trigger(pst_vap, OAL_FALSE, pst_btcoex_wifi_status->uc_ba_size);

            OAM_WARNING_LOG3(pst_vap->uc_vap_id, OAM_SF_COEX, "{dmac_btcoex_bt_low_rate_process::ba_size will change to: %d in 5s,rssi: %d, rate: %d.}",
                                pst_btcoex_wifi_status->uc_ba_size, l_rx_rssi, ul_rx_rate);

            pst_btcoex_wifi_status->uc_get_addba_req_flag = OAL_FALSE;
            pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
            {
                OAM_ERROR_LOG1(0, OAM_SF_DBAC, "{dmac_btcoex_bt_low_rate_process::pst_mac_device[%d] is NULL!}", pst_vap->uc_device_id);
                return;
            }
            FRW_TIMER_STOP_TIMER(&(pst_mac_device->bt_coex_statistics_timer));
            FRW_TIMER_CREATE_TIMER(&(pst_mac_device->bt_coex_low_rate_timer),
                                           dmac_btcoex_low_rate_callback,
                                           g_BTCOEX_RX_LOW_RATE_TIME,
                                           (oal_void *)pst_vap,
                                           OAL_FALSE,
                                           OAM_MODULE_ID_DMAC,
                                           pst_mac_device->ul_core_id);
        }
    }
}
/*****************************************************************************
 函 数 名  : dmac_btcoex_release_rx_prot
 功能描述  : 共存对于关键帧的操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月27日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_btcoex_release_rx_prot(mac_device_stru *pst_mac_device, oal_uint8 uc_data_type)
{
    bt_status_stru              *pst_bt_status;
    pst_bt_status = &(pst_mac_device->pst_device_stru->st_btcoex_btble_status.un_bt_status.st_bt_status);
    if (!pst_bt_status->bit_bt_on || (uc_data_type == MAC_DATA_BUTT))
    {
        return;
    }
    /* 收到EAPOL帧以后，刷掉occupied_period以保证BT竞争到 */
    if ((uc_data_type == MAC_DATA_EAPOL) && !(pst_bt_status->bit_bt_sco))
    {
        hal_set_btcoex_occupied_period(0);
    }
    else if ((MAC_DATA_EAPOL == uc_data_type)
          || (MAC_DATA_DHCP == uc_data_type)
          || (MAC_DATA_ARP_RSP == uc_data_type))
    {
        dmac_btcoex_wlan_priority_set(pst_mac_device, 0, 0);
    }
 }


#endif /* end of _PRE_WLAN_FEATURE_COEXIST_BT */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

