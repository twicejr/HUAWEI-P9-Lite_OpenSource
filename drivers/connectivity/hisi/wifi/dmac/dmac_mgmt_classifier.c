/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_mgmt_classifier.c
  版 本 号   : 初稿
  作    者   : t00231215
  生成日期   : 2012年12月18日
  最近修改   :
  功能描述   : dmac 管理帧处理
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月18日
    作    者   : t00231215
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
#include "mac_frame.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "dmac_main.h"
#include "dmac_vap.h"
#include "dmac_rx_data.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_blockack.h"
#include "dmac_psm_ap.h"
#include "dmac_mgmt_ap.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_scan.h"
#include "dmac_alg_if.h"
#include "mac_vap.h"
#include "dmac_11w.h"
#include "dmac_dft.h"
#include "dmac_mgmt_sta.h"
#include "dmac_p2p.h"
#include "oal_net.h"
#include "dmac_beacon.h"
#include "dmac_dft.h"
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#include "dmac_mgmt_sta.h"
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif


#ifdef _PRE_WLAN_RF_110X_CALI_DPD
#include "hal_ext_if.h"
#include "dmac_config.h"
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_device.h"
#include "dmac_resource.h"
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#include "pm_extern.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_rx_process_control
 功能描述  : 控制帧处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月3日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_process_control(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint8 *pen_go_on)
{
    dmac_rx_ctl_stru                 *pst_rx_ctl;
    mac_ieee80211_frame_stru         *pst_frame_hdr;
    mac_ieee80211_pspoll_frame_stru  *pst_pspoll_frame_hdr;
    oal_uint8                        *puc_payload;
    dmac_tid_stru                    *pst_tid;
    dmac_user_stru                   *pst_ta_user;
    oal_uint8                        *puc_sa_addr;
    oal_uint16                        us_user_idx = 0xFFFF;
    oal_uint8                         uc_tidno;
    oal_uint32                        ul_rslt;

    *pen_go_on = OAL_FALSE;//默认不上报control帧

    /* 获取帧头信息 */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru  *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));
    /* 过滤ACK帧 */
    if (WLAN_ACK == pst_frame_hdr->st_frame_control.bit_sub_type)
    {
#if(_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
    /*****************************************************************************/
        /*信息上报暂时使用，算法提供后删除该部分*/
        /* 获取源地址 */
        puc_sa_addr = pst_frame_hdr->auc_address2;

        /*  获取用户指针 */
        ul_rslt = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), puc_sa_addr, &us_user_idx);
        /*
            查找用户失败: 程序异常，返回，在外围释放空间
            没有找到对应的用户: 程序继续执行
        */
        if (OAL_SUCC != ul_rslt)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                             "{dmac_rx_process_control::mac_vap_find_user_by_macaddr failed[%d]}", ul_rslt);

            return ul_rslt;
        }

        /* 转化为dmac user */
        pst_ta_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
        if (OAL_PTR_NULL != pst_ta_user)
        {
            pst_ta_user->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
        /*pst_ta_user->st_query_stats.ul_signal = smooth_signal_rssi(pst_ta_user->st_query_stats.ul_signal,pst_rx_ctl->st_rx_statistic.c_rssi_dbm);*/
        }
    /*****************************************************************************/
#endif
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::ack frame.}\r\n");
        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_ack_dropped, 1);
        return OAL_SUCC;
    }

    /* 获取源地址 */
    puc_sa_addr = pst_frame_hdr->auc_address2;

    /*  获取用户指针 */
    ul_rslt = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), puc_sa_addr, &us_user_idx);
    /*
        查找用户失败: 程序异常，返回，在外围释放空间
        没有找到对应的用户: 程序继续执行
    */
    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                         "{dmac_rx_process_control::mac_vap_find_user_by_macaddr failed[%d]}", ul_rslt);

        return ul_rslt;
    }

    /* 转化为dmac user */
    pst_ta_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_ta_user)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::pst_ta_user null, us_user_idx=%d.}", us_user_idx);

        mac_rx_report_80211_frame((oal_uint8 *)&(pst_dmac_vap->st_vap_base_info),
                                  (oal_uint8 *)&(pst_rx_ctl->st_rx_info),
                                  pst_netbuf,
                                  OAM_OTA_TYPE_RX_DMAC_CB);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 接收找到用户: 更新时间戳 */
    pst_ta_user->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    if (WLAN_BLOCKACK_REQ == (pst_frame_hdr->st_frame_control.bit_sub_type))    /* BAR 1000 */
    {
        /* 获取帧头和payload指针*/
        puc_payload = MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctl->st_rx_info), pst_netbuf);

        /*************************************************************************/
        /*                     BlockAck Request Frame Format                     */
        /* --------------------------------------------------------------------  */
        /* |Frame Control|Duration|DA|SA|BAR Control|BlockAck Starting    |FCS|  */
        /* |             |        |  |  |           |Sequence number      |   |  */
        /* --------------------------------------------------------------------  */
        /* | 2           |2       |6 |6 |2          |2                    |4  |  */
        /* --------------------------------------------------------------------  */
        /*                                                                       */
        /*************************************************************************/

        uc_tidno        = (puc_payload[1] & 0xF0) >> 4;
        //us_start_seqnum = mac_get_bar_start_seq_num(puc_payload);

        pst_tid = &(pst_ta_user->ast_tx_tid_queue[uc_tidno]);
        if (OAL_PTR_NULL == pst_tid->pst_ba_rx_hdl)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::pst_ba_rx_hdl null.}");
            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_bar_process_dropped, 1);
            dmac_mgmt_delba(pst_dmac_vap, pst_ta_user, uc_tidno, MAC_RECIPIENT_DELBA, MAC_QSTA_SETUP_NOT_DONE);
            return OAL_ERR_CODE_PTR_NULL;
        }
        /*Bar帧上传到Hmac处理*/
        //dmac_reorder_ba_rx_buffer_bar(pst_tid->pst_ba_rx_hdl, us_start_seqnum, &(pst_dmac_vap->st_vap_base_info));
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::receive bar.}");
        *pen_go_on = OAL_TRUE;
        return OAL_SUCC;

    }

    if (WLAN_PS_POLL == (pst_frame_hdr->st_frame_control.bit_sub_type))         /* PS_POLL 1010 */
    {
        /* 如果是ps-poll，则应该把帧头转换为ps-poll的帧头格式 */
        pst_pspoll_frame_hdr = (mac_ieee80211_pspoll_frame_stru  *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

        /* AP需要判断PS_POLL里面的AID与AP保存的用户AID是否一致,不一致的话直接忽略 */
        if (pst_pspoll_frame_hdr->bit_aid_value != pst_ta_user->st_user_base_info.us_assoc_id)
        {
            OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                           "{dmac_rx_process_control::AID in pspoll and AID in user_stru mismatch, bit_aid_value=%d us_assoc_id=%d.}",
                           pst_pspoll_frame_hdr->bit_aid_value, pst_ta_user->st_user_base_info.us_assoc_id);

            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_pspoll_process_dropped, 1);
            return OAL_FAIL;
        }

        /* 直接调用PS_POLL, 后续使用帧类型即可 */
        ul_rslt = dmac_psm_resv_ps_poll(pst_dmac_vap, pst_ta_user);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_pspoll_process_dropped, 1);
            return ul_rslt;
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_rx_filter_mgmt
 功能描述  : dmac_rx_filter_mgmt
 输入参数  : pst_dmac_vap
             pst_netbuf
             pst_event_mem
             &en_go_on
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月30日
    作    者   : z00185449
    修改内容   : 新生成函数

*****************************************************************************/
#define RELATIVE_VALUE_POS_H 10
#define RELATIVE_VALUE_POS_M 6
#define RELATIVE_VALUE_POS_L 2
#define RELATIVE_VALUE_NEG_H -10
#define RELATIVE_VALUE_NEG_M -6
#define RELATIVE_VALUE_NEG_L -2
#define FACTOR_H 5
#define FACTOR_M 3
#define FACTOR_L 2
#define ABS(a,b)  ((a) >= 0 ? (b) : (-(b)))

oal_int32 smooth_signal_rssi(oal_int32 pre_rssi, oal_int32 rssi)
{
    oal_int32 factor;
    oal_int32 delta;

    /*若上报的值超过了合法范围，则分别取极值*/
    if(rssi < DMAC_RSSI_SIGNAL_MIN)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{smooth_signal_rssi::invalid rssi = %d}" , rssi);
        rssi = DMAC_RSSI_SIGNAL_MIN;
    }
    if(rssi > DMAC_RSSI_SIGNAL_MAX)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{smooth_signal_rssi::invalid rssi = %d}" , rssi);
        rssi = DMAC_RSSI_SIGNAL_MAX;
    }
    /* 判断为初始非法值直接返回芯片上报的rssi*/
    if(pre_rssi > DMAC_RSSI_SIGNAL_MAX)
    {
        return rssi;
    }
    /*取当前值和历史值的差值，差值在-10~10范围外，取-10或10*/
    delta = rssi - pre_rssi;
    if( delta > RELATIVE_VALUE_POS_H)
    {
        delta = RELATIVE_VALUE_POS_H;
    }
    else if( delta < RELATIVE_VALUE_NEG_H)
    {
        delta = RELATIVE_VALUE_NEG_H;
    }
    /*获取差值比重因子，1/5,1/3或1/2*/
    if( delta > RELATIVE_VALUE_POS_M || delta < RELATIVE_VALUE_NEG_M )
    {
        factor = FACTOR_H;
    }
    else if( delta > RELATIVE_VALUE_NEG_L && delta < RELATIVE_VALUE_POS_L)
    {
        factor = FACTOR_L;
    }
    else
    {
        factor = FACTOR_M;
    }
    /*计算平滑后的rssi*/
    pre_rssi = pre_rssi + (delta*2 + ABS(delta,factor))/(factor*2);
    return pre_rssi;

}

#ifdef _PRE_WLAN_FEATURE_BTCOEX
OAL_STATIC oal_uint32 dmac_btcoex_wlan_occupied_timeout_callback(oal_void *p_arg)
{
    mac_device_stru *pst_mac_device = (mac_device_stru *)p_arg;
    oal_uint8 *puc_occupied_times = &(pst_mac_device->pst_device_stru->st_btcoex_wifi_status.uc_occupied_times);
    if ((*puc_occupied_times) > 0)
    {
        OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_wlan_occupied_timeout_callback::g_occupied_times = %d}" , *puc_occupied_times);
        (*puc_occupied_times)--;
        hal_set_btcoex_occupied_period(OCCUPIED_PERIOD);
    }
    else
    {
        FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->bt_coex_occupied_timer));
    }
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_rx_mgmt_update_tsf
 功能描述  : DMAC接收关联帧更新TSF
 输入参数  : pst_dmac_vap
             pst_frame_hdr
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月25日
    作    者   : z00241943
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_void dmac_rx_mgmt_update_tsf(dmac_vap_stru *pst_dmac_vap,
                                            mac_ieee80211_frame_stru *pst_frame_hdr,
                                            mac_device_stru    *pst_mac_device,
                                            oal_netbuf_stru    *pst_netbuf)
{
    /* 扫描状态、STA UP/PAUSE状态下收到Beacon和probe rsp帧更新TSF */
    if (OAL_TRUE == pst_mac_device->st_scan_params.bit_is_p2p0_scan)
    {
        return;
    }

    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)  ||
        ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
          && ((MAC_VAP_STATE_PAUSE  == pst_dmac_vap->st_vap_base_info.en_vap_state)
#ifdef _PRE_WLAN_FEATURE_ROAM
          || (MAC_VAP_STATE_ROAMING == pst_dmac_vap->st_vap_base_info.en_vap_state)
#endif
          || (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state))))
    {
        if ((WLAN_PROBE_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
             || (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type))
        {
            if (!OAL_MEMCMP(pst_frame_hdr->auc_address3, pst_dmac_vap->st_vap_base_info.auc_bssid, WLAN_MAC_ADDR_LEN))
            {
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
                dmac_get_tsf_from_bcn(pst_dmac_vap, pst_netbuf);
#endif
                hal_sta_tsf_save(pst_dmac_vap->pst_hal_vap, OAL_TRUE);
            }
            else
            {
                hal_sta_tsf_restore(pst_dmac_vap->pst_hal_vap);
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : dmac_rx_filter_mgmt
 功能描述  : dmac_rx_filter_mgmt
 输入参数  : pst_dmac_vap
             pst_netbuf
             pst_event_mem
             &en_go_on
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月3日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_filter_mgmt(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, frw_event_mem_stru *pst_event_mem, oal_uint8 *pen_go_on)
{
    mac_device_stru            *pst_mac_device;
    dmac_rx_ctl_stru           *pst_rx_ctl;
    mac_ieee80211_frame_stru   *pst_frame_hdr;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_rx_ctl_stru            *pst_rx_info;
    oal_uint8                  *puc_wps_ie      = OAL_PTR_NULL;
    oal_uint8                  *puc_payload     = OAL_PTR_NULL;
    oal_uint16                  us_msg_len;         /* 消息总长度,不包括FCS */
#endif

    oal_uint8                   auc_bssid[WLAN_MAC_ADDR_LEN];  /* sta关联的ap mac地址 */
    oal_uint8                   auc_bad_bssid[WLAN_MAC_ADDR_LEN] = {0x0,0x0,0x0,0x0,0x0,0x0};  /* 非法bssid，全0 */
    oal_uint32                  ul_ret;
    oal_bool_enum_uint8         en_report_bss = OAL_FALSE;      /* 是否上报了bss */
    //static oal_uint8 smooth_count = 0;
    oal_int32                   delta;
    oal_uint16                  us_user_idx;

    /* 获取mac device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_mgmt::pst_mac_device is NULL.}");
        return OAL_FAIL;
    }

    /* 获取帧头信息 */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

    *pen_go_on = OAL_TRUE;  /* 函数返回后是否发到HMAC，初始为true */

    mac_get_bssid((oal_uint8 *)pst_frame_hdr, auc_bssid);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type)
    {
        if(OAL_TRUE == PM_WLAN_IsHostSleep())
        {
            *pen_go_on = OAL_FALSE;
        }
        pst_rx_ctl->st_rx_info.bit_is_beacon = OAL_TRUE;
    }
#endif

    /*STA UT的beacon需优先尽快处理，待机时尽早提前关闭前端节能*/
    if((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)
        && (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        && (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type))
    {

        /* 获取Beacon帧中的mac地址，即AP的mac地址 */
         #if (!defined(HI1102_EDA))
        if(0 == oal_memcmp(auc_bssid,pst_dmac_vap->st_vap_base_info.auc_bssid,OAL_SIZEOF(auc_bssid)))
        {

            #ifdef _PRE_WLAN_FEATURE_STA_PM
            dmac_psm_process_tim_elm(pst_dmac_vap, pst_netbuf);
            #endif

            #ifdef _PRE_WLAN_FEATURE_P2P
            if (IS_P2P_CL((&pst_dmac_vap->st_vap_base_info)))
            {
                /* 获取GO Beacon帧中的NoA资讯 */
                dmac_process_p2p_noa(pst_dmac_vap, pst_netbuf);
            }

            /* DTS2015042506406 P2P WFA 7.1.3，OppPS 节能接收到beacon 帧后， 才使能发送 */
            if ((IS_P2P_CL(&pst_dmac_vap->st_vap_base_info))&&
                (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
            {
                dmac_p2p_oppps_ctwindow_start_event(pst_dmac_vap);
            }
            #endif  /* #ifdef _PRE_WLAN_FEATURE_P2P */

            #ifdef _PRE_WLAN_FEATURE_TSF_SYNC
            dmac_sync_tsf_by_bcn(pst_dmac_vap, pst_netbuf);
            #endif


        }
        #else
            #ifdef _PRE_WLAN_FEATURE_STA_PM
            dmac_psm_process_tim_elm(pst_dmac_vap, pst_netbuf);
            #endif
        #endif /*(!defined(HI1102_EDA))*/

        dmac_sta_up_rx_beacon(pst_dmac_vap, pst_netbuf, pen_go_on);
    }


    /* 规避TSF跳变问题 */
    dmac_rx_mgmt_update_tsf(pst_dmac_vap, pst_frame_hdr, pst_mac_device, pst_netbuf);

    if(0 == oal_memcmp(auc_bssid,auc_bad_bssid,OAL_SIZEOF(auc_bssid)))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_mgmt::drop bssid zero packet}");
        *pen_go_on = OAL_FALSE;
        oal_netbuf_free(pst_netbuf);
        return OAL_SUCC;

    }


#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

    ul_ret = dmac_11w_rx_filter(pst_dmac_vap, pst_netbuf);
    if (OAL_SUCC != ul_ret)
    {
        /* 组播解密失败，不上报管理帧 */
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                       "{dmac_rx_mgmt_classify::dmac_11w_rx_filter failed[%d].}", ul_ret);
        *pen_go_on = OAL_FALSE;

        oal_netbuf_free(pst_netbuf);
        return OAL_SUCC;
    }
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(pst_mac_device->pst_device_stru->st_btcoex_btble_status.un_ble_status.st_ble_status.bit_ble_scan)
    {
        if ((WLAN_ASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
            ||(WLAN_REASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type))
        {
            hal_set_btcoex_occupied_period(OCCUPIED_PERIOD);

            pst_mac_device->pst_device_stru->st_btcoex_wifi_status.uc_occupied_times = OCCUPIED_TIMES;
            /* 启动occupied定时器 */
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->bt_coex_occupied_timer,
                                   dmac_btcoex_wlan_occupied_timeout_callback,
                                   OCCUPIED_INTERVAL,
                                   (oal_void *)pst_mac_device,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
        }
    }
#endif


    /* 如果当前device处于扫描状态，处理收到的管理帧 */
    if (MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)
    {
/* kaiyong监听处理转移到扫描模块处理时，执行如下代码 */
#ifdef _PRE_WLAN_FEATURE_P2P
        if (MAC_SCAN_FUNC_P2P_LISTEN == pst_mac_device->st_scan_params.uc_scan_func)
        {
            /* P2P 设备接收到管理帧 */
            if (!IS_LEGACY_VAP((&pst_dmac_vap->st_vap_base_info)))
            {
                *pen_go_on = dmac_p2p_listen_rx_mgmt(pst_dmac_vap, pst_netbuf);
            }
        }
        else
#endif
        {
            /* 如果扫描动作关心bss信息，那么进行扫描管理帧过滤，进行对应的处理动作，其它do nothing  */
            if (pst_mac_device->st_scan_params.uc_scan_func & MAC_SCAN_FUNC_BSS)
            {
                /*DTS2015102002093 扫描时也是会偶尔切回工作信道工作,不能过滤掉所有管理帧 */
// *pen_go_on = OAL_FALSE;

                /* 扫描状态的帧过滤处理 */
                dmac_scan_mgmt_filter(pst_dmac_vap, pst_netbuf, &en_report_bss);
            }
        }
    }

    if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state && WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        if (WLAN_PROBE_REQ == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            *pen_go_on      = OAL_FALSE;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
            pst_rx_info     = (mac_rx_ctl_stru *)(&(pst_rx_ctl->st_rx_info));
            puc_payload     = MAC_GET_RX_PAYLOAD_ADDR(pst_rx_info, pst_netbuf);
            us_msg_len      = pst_rx_info->us_frame_len;                          /* 消息总长度,不包括FCS */
            //puc_wps_ie      = mac_get_wps_ie(puc_payload, us_msg_len, 0);
            puc_wps_ie      = mac_find_vendor_ie(MAC_WLAN_OUI_MICROSOFT, MAC_WLAN_OUI_TYPE_MICROSOFT_WPS, puc_payload, us_msg_len);
            if (OAL_PTR_NULL != puc_wps_ie)
            {
                *pen_go_on = OAL_TRUE;
            }
#endif
            //OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_ap_up_rx_probe}");
            dmac_ap_up_rx_probe_req(pst_dmac_vap, pst_netbuf);
        }
        else if (WLAN_AUTH == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            *pen_go_on = OAL_FALSE;
            ul_ret = dmac_ap_up_rx_generate_chtxt(pst_dmac_vap, pst_netbuf, pst_event_mem);
            if (OAL_SUCC != ul_ret)
            {
                oal_netbuf_free(pst_netbuf);
            }
            /*OAL_SUCC, netbuf已经提交给hcc上报host*/
            return ul_ret;
        }
        else if(WLAN_ACTION == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
#ifdef _PRE_WLAN_FEATURE_P2P
            /* DTS2015082401460  P2P GO接收到P2P action 管理帧处理 */
            if (IS_P2P_GO((&pst_dmac_vap->st_vap_base_info)))
            {
                *pen_go_on = dmac_p2p_listen_rx_mgmt(pst_dmac_vap, pst_netbuf);
            }
#endif

            ul_ret = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info),  pst_frame_hdr->auc_address2, &us_user_idx);
            if(OAL_SUCC != ul_ret)
            {
                *pen_go_on = OAL_FALSE;
            }

        }
        else if (WLAN_DISASOC == pst_frame_hdr->st_frame_control.bit_sub_type||(WLAN_DEAUTH == pst_frame_hdr->st_frame_control.bit_sub_type))
        {
            if(0 != oal_memcmp(auc_bssid,pst_dmac_vap->st_vap_base_info.auc_bssid,OAL_SIZEOF(auc_bssid)))
            {
                *pen_go_on = OAL_FALSE;
                OAM_INFO_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                                "{dmac_rx_filter_mgmt::drop  disasoc frame! bssid not match! local bssid[%x:X:X:%x:%x:%x]}",
                                  pst_dmac_vap->st_vap_base_info.auc_bssid[0],
                                  pst_dmac_vap->st_vap_base_info.auc_bssid[3],
                                  pst_dmac_vap->st_vap_base_info.auc_bssid[4],
                                  pst_dmac_vap->st_vap_base_info.auc_bssid[5]);
            }
        }

    }

    /*RSSI更新的逻辑单独出来，不和beacon的处理混在一起*/
    if ((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state) && (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode))
    {
        if (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            if(0 == oal_memcmp(auc_bssid,pst_dmac_vap->st_vap_base_info.auc_bssid,OAL_SIZEOF(auc_bssid)))
            {

                //pst_dmac_vap->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;

                delta = pst_dmac_vap->st_query_stats.ul_signal - pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
                if (DMAC_INVALID_SIGNAL_DELTA <= GET_ABS(delta))
                {
                    /*lint -e571*/
                    OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_mgmt::rssi interval err! pre=%d, cur=%d.}",
                                                                                            pst_dmac_vap->st_query_stats.ul_signal,
                                                                                            pst_rx_ctl->st_rx_statistic.c_rssi_dbm);
                    /*lint +e571*/
                    #ifdef _PRE_WLAN_DFT_STAT
                    dmac_dft_report_all_para(pst_dmac_vap,OAL_TRUE);
                    #endif

                }

                pst_dmac_vap->st_query_stats.ul_signal = smooth_signal_rssi( pst_dmac_vap->st_query_stats.ul_signal,pst_rx_ctl->st_rx_statistic.c_rssi_dbm);

            }


        }
    }
    else
    {
        if ((WLAN_ASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
            || (WLAN_REASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type))
        {
            pst_dmac_vap->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
        }
    }

    if(OAL_TRUE == en_report_bss)
    {
        /*如果在扫描中已经上报，此处不应该再上报该netbuf,并且不能释放netbuf*/
        *pen_go_on = OAL_FALSE;
        return OAL_SUCC;
    }

    if (OAL_FALSE == *pen_go_on)
    {
        /* 将netbuf归还内存池 */
        oal_netbuf_free(pst_netbuf);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_rx_mgmt_classify
 功能描述  : DMAC模块，接收流程管理帧处理入口，主要用于帧在DMAC或者HMAC的分发
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_mgmt_classify(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                mac_vap_stru                   *pst_vap,
                oal_netbuf_stru                *pst_netbuf)
{
    frw_event_stru                    *pst_event;
    dmac_wlan_crx_event_stru          *pst_crx_event;
    dmac_vap_stru                     *pst_dmac_vap;
    dmac_rx_ctl_stru                  *pst_rx_ctl;
    mac_ieee80211_frame_stru          *pst_frame_hdr;
    oal_bool_enum_uint8                en_go_on          = OAL_TRUE;           /* 是否继续到hmac处理 */
    mac_user_stru                     *pst_user;


    /* 获取事件头和事件结构体指针 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 更新事件头中的VAP ID */
    pst_event_hdr->uc_vap_id = pst_vap->uc_vap_id;

    /* 获取帧头信息 */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

    /* 转化为DMAC VAP */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_mgmt_classify::pst_dmac_vap null.}");

        OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user = (mac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&(pst_rx_ctl->st_rx_info)));

    /* 控制帧处理，目前没有上报到HMAC，直接return */
    if (WLAN_CONTROL == pst_frame_hdr->st_frame_control.bit_type)
    {
        if (OAL_PTR_NULL != pst_user)
        {
            dmac_alg_txbf_rx_cntl_notify(&(pst_dmac_vap->st_vap_base_info), pst_user, pst_netbuf);
        }

        dmac_rx_process_control(pst_dmac_vap, pst_netbuf, &en_go_on);
        if (OAL_FALSE == en_go_on)
        {
            oal_netbuf_free(pst_netbuf);
            return OAL_SUCC;
        }
    }

    /* DMAC管理帧处理 */
    if (WLAN_MANAGEMENT == pst_frame_hdr->st_frame_control.bit_type)
    {
        /*dmac_rx_filter_mgmt里可能会更改netbuf内容，所以需先通知算法*/
        if (OAL_PTR_NULL != pst_user)
        {
            dmac_alg_rx_mgmt_notify(&(pst_dmac_vap->st_vap_base_info), pst_user, pst_netbuf);
        }


        dmac_rx_filter_mgmt(pst_dmac_vap, pst_netbuf, pst_event_mem, &en_go_on);

    }

    if (OAL_TRUE == en_go_on)
    {
        /* 其它管理帧统一上报到HMAC处理 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#ifdef _PRE_WLAN_DFT_DUMP_FRAME
        mac_rx_report_80211_frame((oal_uint8 *)&(pst_dmac_vap->st_vap_base_info), (oal_uint8 *)&(pst_rx_ctl->st_rx_info), pst_netbuf, OAM_OTA_TYPE_RX_DMAC_CB);
#endif /* #ifdef _PRE_WLAN_DFT_DUMP_FRAME */
#endif /* #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) */
        /* 继承事件，并且修改事件头，暂时未区分STA和AP模式 */
        FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX);

        pst_crx_event = (dmac_wlan_crx_event_stru *)(pst_event->auc_event_data);
        pst_crx_event->pst_netbuf = pst_netbuf;

        /* 分发 */
        /*DTS2015031608237 如果直接返回，netbuf会内存泄露*/
        return frw_event_dispatch_event(pst_event_mem);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_rx_multi_mgmt_pre_process
 功能描述  : 预处理来自其他BSS的广播管理帧，根据本vap 状态和帧类型判断是否需要处理。
            probe req 帧(广播)
                （1）如果是go/ap ，接收到probe req 信道和本vap 工作信道不同，则不做复制和进一步处理。
                （2）如果是sta， 接收到prob req ，不做复制和处理。
                （3）如果是p2p device 或者p2p client ,接收dao probe req ，判断是否为监听状态，如果是监听状态，则复制，否则不复制。
            beacon 帧
                （1）ap/p2p go, 信道选择时的扫描接收到的beacon 帧需要处理
                （2）sta/p2p gc/p2p dev 一直需要beacon 帧
            action 帧(广播)
                （1）广播action 帧，复制给其他vap
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_rx_multi_mgmt_pre_process(mac_device_stru    *pst_mac_device,
                                                                mac_vap_stru     *pst_mac_vap,
                                                                oal_uint8         uc_channel_number,
                                                                oal_uint8         uc_mgmt_type)
{
    oal_bool_enum_uint8          en_need_copy = OAL_TRUE;

    /* 判断接收到的beacon / probe req 是否允许复制给其他vap 处理 */
    switch (uc_mgmt_type)
    {
        case (WLAN_FC0_SUBTYPE_PROBE_REQ | WLAN_FC0_TYPE_MGT):
        {
            //OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX,
            //    "{dmac_rx_multi_mgmt_pre_process::rx probe req}");
            if (IS_AP(pst_mac_vap)
                && uc_channel_number != pst_mac_vap->st_channel.uc_chan_number)
            {
                en_need_copy = OAL_FALSE;
            }
            else if (IS_STA(pst_mac_vap))
            {
                if (IS_LEGACY_VAP(pst_mac_vap))
                {
                    en_need_copy = OAL_FALSE;
                }
                else
                {
                    if(OAL_FALSE == mac_device_is_listening(pst_mac_device))
                    {
                        en_need_copy = OAL_FALSE;
                    }
                }
            }
            break;
        }
        case (WLAN_FC0_SUBTYPE_BEACON | WLAN_FC0_TYPE_MGT):
        {
            //OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX,
            //    "{dmac_rx_multi_mgmt_pre_process::rx beacon}");
            if (IS_AP(pst_mac_vap))
            {
                if(OAL_FALSE == mac_device_is_scaning(pst_mac_device))
                {
                    en_need_copy = OAL_FALSE;
                }
            }
            break;
        }
        default:
        {
            en_need_copy = OAL_TRUE;
            break;
        }
    }

    //OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX,
    //    "{dmac_rx_multi_mgmt_pre_process::en_need_copy[%d]}", en_need_copy);
    return en_need_copy;
}

/*****************************************************************************
 函 数 名  : dmac_rx_multi_mgmt_frame
 功能描述  : 处理来自其他BSS的广播管理帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_multi_mgmt_frame(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                oal_netbuf_stru                *pst_netbuf)
{
    mac_device_stru    *pst_device;
    mac_vap_stru       *pst_mac_vap;
    oal_netbuf_stru    *pst_netbuf_copy = OAL_PTR_NULL;
    dmac_rx_ctl_stru   *pst_rx_ctrl;
    oal_uint8           uc_vap_idx;
    oal_uint32          ul_rslt;

    mac_ieee80211_frame_stru    *pst_mac_header;
    oal_bool_enum_uint8          en_orig_netbuffer_used = OAL_FALSE;
    oal_uint8                    uc_channel_number;
    oal_uint8                    uc_subtype;

    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX,
                       "{dmac_rx_multi_mgmt_frame::pst_device null, uc_device_id=%d.}", pst_event_hdr->uc_device_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 当device下的设备数为0时，直接释放接收到的包 */
    if (0 == pst_device->uc_vap_num)
    {
        //OAM_INFO_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::the device have none vap.}\r\n");

        oal_netbuf_free(pst_netbuf);
        return OAL_SUCC;
    }

    pst_rx_ctrl       = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_mac_header    = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctrl->st_rx_info));
    uc_channel_number = pst_rx_ctrl->st_rx_info.uc_channel_number;
    uc_subtype        = mac_get_frame_sub_type((oal_uint8 *)pst_mac_header);

    /* 来自其他BSS的广播管理帧，转发给每一个VAP一份 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
            //return OAL_ERR_CODE_PTR_NULL;
            continue;
        }

        if (OAL_FALSE == dmac_rx_multi_mgmt_pre_process(pst_device, pst_mac_vap, uc_channel_number, uc_subtype))
        {
            //OAM_WARNING_LOG0(pst_device->auc_vap_id[uc_vap_idx], OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::probe req or beacon do not dispatch to the vap which do not needed.}");
            continue;
        }

        /* 最后一个VAP直接发送原来的netbuf */
        if (uc_vap_idx == pst_device->uc_vap_num - 1)
        {
            pst_netbuf_copy = pst_netbuf;
            en_orig_netbuffer_used = OAL_TRUE;
        }
        else
        {
            pst_netbuf_copy = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_LARGE_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
            if (OAL_PTR_NULL == pst_netbuf_copy)
            {
                OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::pst_netbuf_copy null.}");
                continue;
            }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            OAL_MEM_NETBUF_TRACE(pst_netbuf_copy, OAL_TRUE);
#endif

            pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf_copy);
            /* 信息复制 */
            oal_memcopy(oal_netbuf_cb(pst_netbuf_copy), oal_netbuf_cb(pst_netbuf), OAL_SIZEOF(dmac_rx_ctl_stru));

#if (_PRE_PRODUCT_ID !=_PRE_PRODUCT_ID_HI1102_DEV)
            oal_memcopy(pst_netbuf_copy->head, pst_netbuf->head, (oal_uint32)(pst_netbuf->end - pst_netbuf->head));
#else
            oal_memcopy(oal_netbuf_header(pst_netbuf_copy), oal_netbuf_header(pst_netbuf), (oal_uint32)(pst_rx_ctrl->st_rx_info.bit_mac_header_len));
            oal_memcopy(oal_netbuf_payload(pst_netbuf_copy), oal_netbuf_payload(pst_netbuf),
                       ((oal_uint32)(pst_rx_ctrl->st_rx_info.us_frame_len) - (oal_uint32)(pst_rx_ctrl->st_rx_info.bit_mac_header_len)));
#endif

            /* 设置netbuf长度、TAIL指针 */
            oal_netbuf_set_len(pst_netbuf_copy, oal_netbuf_get_len(pst_netbuf));
            oal_set_netbuf_tail(pst_netbuf_copy, oal_netbuf_data(pst_netbuf_copy) + oal_netbuf_get_len(pst_netbuf_copy));

            /* 调整MAC帧头的指针(copy后，对应的mac header的头已经发生变化) */
            mac_set_rx_cb_mac_hdr(&(pst_rx_ctrl->st_rx_info), (oal_uint32 *)oal_netbuf_header(pst_netbuf_copy));
        }

        /* 调用处理管理帧接口 */
        ul_rslt = dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_mac_vap, pst_netbuf_copy);
        if (ul_rslt != OAL_SUCC)
        {
//            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::dmac_rx_mgmt_classify failed[%d].", ul_rslt);
            OAL_IO_PRINT("\r\n dmac_rx_multi_mgmt_frame::dmac_rx_mgmt_classify failed[%d].\r\n", ul_rslt);

            oal_netbuf_free(pst_netbuf_copy);
        }
    }

    /* 未使用传入的netbuffer， 直接释放 */
    if(OAL_FALSE == en_orig_netbuffer_used)
    {
        oal_netbuf_free(pst_netbuf);
    }
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_rx_process_mgmt
 功能描述  : 管理帧总入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_process_mgmt(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                hal_to_dmac_device_stru        *pst_hal_device,
                oal_netbuf_stru                *pst_netbuf)
{
    hal_to_dmac_vap_stru   *pst_hal_vap = OAL_PTR_NULL;
    dmac_rx_ctl_stru       *pst_cb_ctrl;
    oal_uint8               uc_vap_id;
    mac_vap_stru           *pst_vap;
    mac_device_stru        *pst_mac_device;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_ieee80211_frame_stru *pst_mac_ieee80211_frame;
#endif

    pst_cb_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_mgmt::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
#ifdef _PRE_WLAN_DFT_STAT
    /* 管理帧接收统计 */
    dmac_dft_mgmt_stat_incr(pst_mac_device, oal_netbuf_header(pst_netbuf), MAC_DEV_MGMT_STAT_TYPE_RX);
#endif

    /* 获取该帧对应的VAP ID */
    uc_vap_id = pst_cb_ctrl->st_rx_info.bit_vap_id;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((uc_vap_id < WLAN_HAL_OHTER_BSS_ID)||((uc_vap_id >= WLAN_PROXY_STA_START_ID) && (uc_vap_id <= WLAN_PROXY_STA_END_ID)))        /* 来自本device下的某一BSS的帧 */
        {
            hal_get_hal_vap(pst_hal_device, uc_vap_id, &pst_hal_vap);
            if (OAL_PTR_NULL == pst_hal_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::hal vap failed!}");
                OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

                return OAL_ERR_CODE_PTR_NULL;
            }

            pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hal_vap->uc_mac_vap_id);
            if (OAL_PTR_NULL == pst_vap)
            {
                OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::mac vap is null!}");

                OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

                return OAL_ERR_CODE_PTR_NULL;
            }

            /* 如果是发送给sta0的广播/组播管理帧，给device下的每个vap(包括Proxy STA)都发送一份 */
            pst_mac_ieee80211_frame = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf);

            if ((WLAN_STA0_HAL_VAP_ID == uc_vap_id) && (ETHER_IS_MULTICAST(pst_mac_ieee80211_frame->auc_address1)))
            {
               return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
            }

            return dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_vap, pst_netbuf);
        }
        else if (WLAN_HAL_OHTER_BSS_ID == uc_vap_id)  /* 来自其他bss的广播管理帧 */
        {
            return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
        }
        else                                                /* 异常帧 */
        {
            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }
    else
    {
        if (uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC)        /* 来自本device下的某一BSS的帧 */
        //if (HAL_VAP_ID_IS_VALID(uc_vap_id))  /* TODO proxy sta打开后HAL VAP ID不一样 */
        {
            /* 获取对应的hal vap */
            hal_get_hal_vap(pst_hal_device, uc_vap_id, &pst_hal_vap);
            if (OAL_PTR_NULL == pst_hal_vap)
            {
                OAM_ERROR_LOG1(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::hal vap failed!}", uc_vap_id);
                OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

                return OAL_ERR_CODE_PTR_NULL;
            }

            pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hal_vap->uc_mac_vap_id);
            if (OAL_PTR_NULL == pst_vap)
            {
                OAM_ERROR_LOG1(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::mac vap is null!}", pst_hal_vap->uc_mac_vap_id);
                OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

                return OAL_ERR_CODE_PTR_NULL;
            }

            return dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_vap, pst_netbuf);
        }
        else if (WLAN_HAL_OHTER_BSS_ID == uc_vap_id)  /* 来自其他bss的广播管理帧 */
        {
            return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
        }
        else                                                /* 异常帧 */
        {
            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }
#else
    //if (uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_SPEC)        /* 来自本device下的某一BSS的帧 */
    if (HAL_VAP_ID_IS_VALID(uc_vap_id))
    {
        /* 获取对应的hal vap */
        hal_get_hal_vap(pst_hal_device, uc_vap_id, &pst_hal_vap);
        if (OAL_PTR_NULL == pst_hal_vap)
        {
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_RX, "{dmac_rx_process_mgmt::pst_hal_vap null.}");

            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hal_vap->uc_mac_vap_id);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_RX, "{dmac_rx_process_mgmt::pst_vap null.}");

            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

            return OAL_ERR_CODE_PTR_NULL;
        }

        return dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_vap, pst_netbuf);
    }
    else if (WLAN_HAL_OHTER_BSS_ID == uc_vap_id)  /* 来自其他bss的广播管理帧 */
    {
        return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
    }
    else                                                /* 异常帧 */
    {
        OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }
#endif
}

/*****************************************************************************
 函 数 名  : dmac_tx_process_action_event
 功能描述  : DMAC模块，ACTION发送处理接口，主要是进行信息同步和调用管理帧发送接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月10日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_process_action_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    dmac_ctx_action_event_stru *pst_ctx_action_event;
    dmac_tx_event_stru         *pst_tx_event;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;
    oal_uint32                  ul_action_info_offset;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_process_action_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_tx_event            = (dmac_tx_event_stru *)pst_event->auc_event_data;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    ul_action_info_offset   = pst_tx_event->us_frame_len - OAL_SIZEOF(dmac_ctx_action_event_stru) - MAC_80211_FRAME_LEN;
#else
    ul_action_info_offset   = pst_tx_event->us_frame_len - OAL_SIZEOF(dmac_ctx_action_event_stru);
#endif
    pst_ctx_action_event    = (dmac_ctx_action_event_stru *)(oal_netbuf_data(pst_tx_event->pst_netbuf) + ul_action_info_offset);

    /* 获取全局board控制信息 */

    /* 获取device结构的信息 */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /*复位状态暂停调度*/
    if(OAL_PTR_NULL != pst_device && OAL_TRUE == MAC_DEV_IS_RESET_IN_PROGRESS(pst_device))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX,
                       "{dmac_tx_process_action_event::MAC_DEV_IS_RESET_IN_PROGRESS.}");

        return OAL_SUCC;
    }

    OAM_INFO_LOG2(0, OAM_SF_TX, "{dmac_tx_process_action_event::category %d, action %d.}",
                  pst_ctx_action_event->en_action_category, pst_ctx_action_event->uc_action);

    /* 获取vap结构信息 */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    switch (pst_ctx_action_event->en_action_category)
    {
        case MAC_ACTION_CATEGORY_BA:
            switch (pst_ctx_action_event->uc_action)
            {
                case MAC_BA_ACTION_ADDBA_REQ:

                    dmac_mgmt_tx_addba_req(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                case MAC_BA_ACTION_ADDBA_RSP:

                    dmac_mgmt_tx_addba_rsp(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                case MAC_BA_ACTION_DELBA:

                    dmac_mgmt_tx_delba(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                default:

                    OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_action_event::invalid ba action type.}");
                    break;
            }

            break;

        default:

            OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_action_event::invalid ba action category.}");
            break;
    }


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_tx_event_process
 功能描述  : 通用的（那些不需要damc做任何业务处理的管理帧，认证关联）处理hmac抛来的发送管理帧事件，填写相应cb参数，发送管理帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月25日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_tx_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    dmac_tx_event_stru      *pst_ctx_event;
    dmac_vap_stru           *pst_dmac_vap;
    oal_netbuf_stru         *pst_mgmt_frame;
    mac_tx_ctl_stru         *pst_tx_ctl;
    oal_uint32               ul_ret;
    oal_uint8                uc_mgmt_frm_type;
    mac_user_stru           *pst_mac_user;
    mac_device_stru         *pst_mac_device;

    if ((OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);

    pst_ctx_event   = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_mgmt_frame  = pst_ctx_event->pst_netbuf;
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_frame);

    oal_set_netbuf_next(pst_mgmt_frame, OAL_PTR_NULL);
    oal_set_netbuf_prev(pst_mgmt_frame, OAL_PTR_NULL);
    /* 填写netbuf的cb字段，共发送管理帧和发送完成接口使用 */
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)        = OAL_FALSE;
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_mgmt_frame));
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

#ifdef _PRE_WLAN_FEATURE_ROAM
    /* 漫游状态时，强制发送该管理帧 */
    if (MAC_VAP_STATE_ROAMING == pst_dmac_vap->st_vap_base_info.en_vap_state)
    {
        ul_ret = dmac_tx_force(pst_dmac_vap, pst_ctx_event->pst_netbuf, pst_ctx_event->us_frame_len, 1);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::dmac_tx_force [roam] len[%d] fail[%ld]}",
                           pst_ctx_event->us_frame_len, ul_ret);
            oal_netbuf_free(pst_ctx_event->pst_netbuf);
        }
        return ul_ret;
    }
#endif //_PRE_WLAN_FEATURE_ROAM
    uc_mgmt_frm_type = mac_get_frame_sub_type((oal_uint8 *)mac_get_cb_frame_hdr(pst_tx_ctl));
    if (uc_mgmt_frm_type == WLAN_FC0_SUBTYPE_AUTH)
    {
        pst_mac_user = mac_res_get_mac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
        pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
        if (OAL_PTR_NULL == pst_mac_device)
        {
            oal_netbuf_free(pst_ctx_event->pst_netbuf);
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::pst_mac_device is null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }
        if (OAL_PTR_NULL != pst_mac_user)
        {
            dmac_tid_clear(pst_mac_user, pst_mac_device);
        }

    }

    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_ctx_event->pst_netbuf, pst_ctx_event->us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_ctx_event->pst_netbuf);

        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_rx_process_sync_event
 功能描述  : 收到wlan的Delba和addba rsp用于到dmac的同步
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_process_sync_event(frw_event_mem_stru *pst_event_mem)
{

    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    dmac_ctx_action_event_stru *pst_crx_action_sync;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_sync_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_crx_action_sync    = (dmac_ctx_action_event_stru *)pst_event->auc_event_data;

    /* 获取device结构的信息 */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /* 获取vap结构信息 */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    OAM_INFO_LOG2(0, OAM_SF_RX, "{dmac_rx_process_sync_event::category %d, action %d.}",
                  pst_crx_action_sync->en_action_category, pst_crx_action_sync->uc_action);
    switch (pst_crx_action_sync->en_action_category)
    {
        case MAC_ACTION_CATEGORY_BA:
            switch (pst_crx_action_sync->uc_action)
            {
                case MAC_BA_ACTION_ADDBA_RSP:

                    dmac_mgmt_rx_addba_rsp(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_action_sync);
                    break;

                case MAC_BA_ACTION_DELBA:

                    dmac_mgmt_rx_delba(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_action_sync);
                    break;

                default:

                    OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_sync_event::invalid ba action type.}");

                    break;
            }

            break;

        default:

            OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_sync_event::invalid ba action category.}");
            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_rx_process_priv_req_event
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_process_priv_req_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    mac_priv_req_args_stru     *pst_crx_priv_req_args;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_priv_req_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_crx_priv_req_args   = (mac_priv_req_args_stru *)pst_event->auc_event_data;

    /* 获取device结构的信息 */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /* 获取vap结构信息 */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    switch (pst_crx_priv_req_args->uc_type)
    {
        case MAC_A_MPDU_START:

            dmac_mgmt_rx_ampdu_start(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_priv_req_args);
            break;

        case MAC_A_MPDU_END:
            dmac_mgmt_rx_ampdu_end(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_priv_req_args);
            break;

        default:

            OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_priv_req_event::invalid priv action type.}");
            break;
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 函 数 名  : dmac_btcoex_tx_addba_rsp_check
 功能描述  : 判断一个帧是否是addba_rsp
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月18日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_btcoex_tx_addba_rsp_check(oal_netbuf_stru *pst_netbuf, hal_to_dmac_device_stru *pst_hal_device)
{
    oal_uint8 *puc_mac_header  = oal_netbuf_header(pst_netbuf);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8 *puc_mac_payload = oal_netbuf_data(pst_netbuf);
#else
    oal_uint8 *puc_mac_payload = puc_mac_header + MAC_80211_FRAME_LEN;
#endif
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;

    /* Management frame */
    if (WLAN_FC0_SUBTYPE_ACTION == mac_get_frame_sub_type(puc_mac_header))
    {
        if ((MAC_ACTION_CATEGORY_BA == puc_mac_payload[0]) && (MAC_BA_ACTION_ADDBA_RSP == puc_mac_payload[1]))
        {
            pst_btcoex_wifi_status = &(pst_hal_device->st_btcoex_wifi_status);
            pst_btcoex_wifi_status->uc_get_addba_req_flag = OAL_TRUE;
            pst_btcoex_wifi_status->uc_ba_size_addba_rsp_index = pst_btcoex_wifi_status->uc_ba_size_index;
        }
    }
}
#endif

/*****************************************************************************
 函 数 名  : dmac_tx_complete_mgmt_notify
 功能描述  : 发送完成管理帧处理入口
 输入参数  : pst_dscr: 描述符地址
             pst_dmac_user: sta结构体指针
             pst_dmac_vap: vap结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月14日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_complete_mgmt_notify(
                hal_to_dmac_device_stru *pst_hal_device,
                dmac_user_stru         *pst_dmac_user,
                hal_tx_dscr_stru       *pst_dscr,
                oal_netbuf_stru        *pst_buf)
{
    mac_tx_ctl_stru                *pst_tx_ctl;
    oal_uint8                       uc_tid;

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);

    if (OAL_TRUE == mac_is_delba_frame(pst_buf, &uc_tid))
    {
        pst_dmac_user->ast_tx_tid_queue[uc_tid].en_is_delba_ing = OAL_FALSE;
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_tx_addba_rsp_check(pst_buf, pst_hal_device);
#endif

    if (OAL_TRUE == mac_get_cb_is_bar(pst_tx_ctl))
    {
        dmac_tid_resume(pst_hal_device, &pst_dmac_user->ast_tx_tid_queue[mac_get_cb_tid(pst_tx_ctl)], DMAC_TID_PAUSE_RESUME_TYPE_BA);
        return OAL_SUCC;
    }

    return OAL_SUCC;
}
#if 0
/*****************************************************************************
 函 数 名  : dmac_tx_complete_security
 功能描述  : 发送完成安全处理入口
 输入参数  : pst_dscr: 描述符地址
             pst_dmac_user: sta结构体指针
             pst_dmac_vap: vap结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月14日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_complete_security_ap(
                dmac_user_stru     *pst_dmac_user,
                hal_tx_dscr_stru   *pst_dscr,
                oal_netbuf_stru    *pst_buf)
{

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_mgmt_connect_set_channel
 功能描述  : STA入网设信道或者AP设置信道接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月8日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_mgmt_connect_set_channel(
                mac_device_stru    *pst_mac_device,
                mac_vap_stru       *pst_up_vap,
                mac_channel_stru   *pst_channel)
{
    /* 当前没有处在关联状态的VAP，可以直接切信道 */
    if (OAL_PTR_NULL == pst_up_vap)
    {
        dmac_tx_clear_tx_queue(pst_mac_device->pst_device_stru);
        dmac_mgmt_switch_channel(pst_mac_device, pst_channel);

        return;
    }

    OAM_WARNING_LOG4(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel: has up vap. up_vap_chan:%d bw:%d, new_chan:%d bw:%d",
                         pst_up_vap->st_channel.uc_chan_number,
                         pst_up_vap->st_channel.en_bandwidth,
                         pst_channel->uc_chan_number,
                         pst_channel->en_bandwidth);

    if (pst_channel->uc_chan_number != pst_up_vap->st_channel.uc_chan_number)
    {
        /* 暂停工作信道上VAP发送 */
        dmac_vap_pause_tx_by_chl(pst_mac_device, &(pst_up_vap->st_channel));

        OAM_WARNING_LOG1(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel: diff chan_num. switch off to chan %d.",
                            pst_channel->uc_chan_number);

        /* 发保护帧的信道切离 */
        dmac_switch_channel_off(pst_mac_device, pst_up_vap, pst_channel, 20);
    }
    else
    {
        /* DTS2015073102639 同信道时需要切到更大带宽的信道 */
        if (pst_channel->en_bandwidth > pst_up_vap->st_channel.en_bandwidth)
        {
            OAM_WARNING_LOG2(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel:  same chan_num[%d], switch to bw[%d].",
                            pst_channel->uc_chan_number,
                            pst_channel->en_bandwidth);

            dmac_mgmt_switch_channel(pst_mac_device, pst_channel);
        }
    }

}

/*****************************************************************************
 函 数 名  : dmac_join_set_reg_event_process
 功能描述  : 更新jion req时，设置相应寄存器
 输入参数  : 事件结构体
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : z00241943
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_join_set_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                 *pst_event;
    frw_event_hdr_stru             *pst_event_hdr;
    dmac_ctx_join_req_set_reg_stru *pst_reg_params;
    mac_device_stru                *pst_device;
    dmac_vap_stru                  *pst_dmac_vap;
    mac_vap_stru                   *pst_vap_up;     /* 处在UP状态的VAP */


    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_join_req_set_reg_stru *)pst_event->auc_event_data;

    /* 获取device结构的信息 */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_dpd_enbale = OAL_TRUE;

    pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_dpd_done   = OAL_FALSE;

    /* 同步dmac vap的信道信息 */
    pst_dmac_vap->st_vap_base_info.st_channel = pst_reg_params->st_current_channel;

    mac_vap_set_bssid(&pst_dmac_vap->st_vap_base_info, pst_reg_params->auc_bssid);

    /* 写STA BSSID寄存器*/
    hal_set_sta_bssid(pst_dmac_vap->pst_hal_vap, pst_reg_params->auc_bssid);

    /* 同步beacon period */
    pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = pst_reg_params->us_beacon_period;

    if (0 != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::beacon period[%d]}",
                         pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);
        /* 将beacon的周期写入寄存器 */
        hal_vap_set_psm_beacon_period(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);
    }
    /* 内置tbtt offset单位us */
    hal_set_psm_tbtt_offset(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->us_in_tbtt_offset);

    /* 开启sta tbtt定时器 */
    hal_enable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 外置tbtt offset 单位ms */
    hal_set_psm_ext_tbtt_offset(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->us_ext_tbtt_offset);

    /* 设置接收beacon超时中断的时间 */
    hal_set_beacon_timeout_val(pst_dmac_vap->pst_hal_device, pst_dmac_vap->us_beacon_timeout);

    /*开启beacon timout中断 */
    hal_vap_set_psm_tsf_ctrl(pst_dmac_vap->pst_hal_vap, 0x3);


#endif

    /* 通知算法 */
    dmac_alg_cfg_channel_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_MOVE_WORK);
    dmac_alg_cfg_bandwidth_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_MOVE_WORK);

    /* 如果有处在UP状态的VAP，此次入网切信道需要发保护帧 */
    mac_device_find_up_vap(pst_device, &pst_vap_up);
    dmac_mgmt_connect_set_channel(pst_device, pst_vap_up, &(pst_reg_params->st_current_channel));

/* 如果是02模式下，需要将信道信息同步到dmac vap结构体中 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_memcopy(&(pst_dmac_vap->st_vap_base_info.st_channel), &(pst_reg_params->st_current_channel), OAL_SIZEOF(mac_channel_stru));
#endif

    dmac_vap_init_tx_ucast_data_frame(pst_dmac_vap);

    /* 初始化默认接收beacon帧 */
    /* 防止其他操作中修改寄存器，再写寄存器接收beacon帧 */
    if(OAL_FALSE == pst_reg_params->ul_beacon_filter)
    {
        /* 关闭beacon帧过滤  */
        hal_disable_beacon_filter(pst_device->pst_device_stru);
    }

    /* 初始化默认不接收non_direct_frame帧*/
    /* 为防止其他操作中修改寄存器再写寄存器不接收non_direct_frame帧 */
    if(OAL_TRUE == pst_reg_params->ul_non_frame_filter)
    {
        /* 打开non frame帧过滤 */
        hal_enable_non_frame_filter(pst_device->pst_device_stru);
    }

    /* 入网优化，不同频段下的能力不一样 */
    if (WLAN_BAND_2G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
    {
        mac_mib_set_ShortPreambleOptionImplemented(&pst_dmac_vap->st_vap_base_info, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&pst_dmac_vap->st_vap_base_info, OAL_FALSE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(&pst_dmac_vap->st_vap_base_info, WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&pst_dmac_vap->st_vap_base_info, OAL_TRUE);
    }

    /* 更新ssid */
    oal_memcopy(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID, pst_reg_params->auc_ssid, WLAN_SSID_MAX_LEN);
    pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID[WLAN_SSID_MAX_LEN - 1] = '\0';



#if 0
OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{call DPD Calibration Start function}");

#ifdef _PRE_WLAN_RF_110X_CALI_DPD

    if (WLAN_BAND_2G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
    {
      dmac_start_dpd_calibration(pst_vap_up);
    }
#endif
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_join_set_dtim_reg_event_process
 功能描述  : join时设置dtim相应寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月4日
    作    者   : z00241943
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_join_set_dtim_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_set_dtim_tsf_reg_stru      *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_vap_stru                       *pst_dmac_vap;


    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_join_set_dtim_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_set_dtim_tsf_reg_stru *)pst_event->auc_event_data;

    /* 获取device结构的信息 */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_dtim_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 写bssid 寄存器 */
    hal_set_sta_bssid(pst_dmac_vap->pst_hal_vap,pst_reg_params->auc_bssid);

    /* */
    mac_vap_set_bssid(&pst_dmac_vap->st_vap_base_info, pst_reg_params->auc_bssid);

    /* 写tsf 寄存器 */
    if(OAL_TRUE == (oal_uint32)pst_reg_params->us_tsf_bit0)
    {
       /* enable tbtt */
       hal_enable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);
    }

    return OAL_SUCC;

}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 函 数 名  : dmac_set_smps_process
 功能描述  : DMAC设置SMPS模式处理函数(配置MAC寄存器，使能SMPS)
 输入参数  : pst_event_mem--事件指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月17日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_set_smps_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                         *pst_event;
    frw_event_hdr_stru                     *pst_event_hdr;
    mac_cfg_smps_mode_stru                 *pst_smps_mode;
    hal_smps_mode_enum_uint8                en_smps_mode;
    mac_device_stru                        *pst_device;
    mac_vap_stru                           *pst_mac_vap;
    mac_user_stru                          *pst_mac_user;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SMPS, "{dmac_set_smps_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_smps_mode           = (mac_cfg_smps_mode_stru *)pst_event->auc_event_data;

    /* 获取device结构的信息 */
    pst_device   = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_mac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user = mac_res_get_mac_user(pst_smps_mode->us_user_idx);

    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_mac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_alg_cfg_smps_notify(pst_mac_vap, pst_mac_user);

    pst_device->uc_dev_smps_mode = pst_smps_mode->uc_smps_mode;

    if (WLAN_MIB_MIMO_POWER_SAVE_MIMO == pst_smps_mode->uc_smps_mode)
    {
        pst_device->en_smps = OAL_FALSE;
        en_smps_mode = HAL_SMPS_MODE_DISABLE;
    }
    else
    {
        pst_device->en_smps = OAL_TRUE;
        en_smps_mode = (hal_smps_mode_enum_uint8)(pst_smps_mode->uc_smps_mode);
    }

    /* 写SMPS控制寄存器 */
    hal_set_smps_mode(pst_device->pst_device_stru, en_smps_mode);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_asoc_set_reg_event_process
 功能描述  : 关联时写寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月18日
    作    者   : z00241943
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_asoc_set_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_asoc_set_reg_stru       *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_user_stru                      *pst_dmac_user;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{dmac_asoc_set_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_asoc_set_reg_stru *)pst_event->auc_event_data;

    /* 获取device结构的信息 */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ASSOC, "{dmac_join_set_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_dmac_user = mac_res_get_dmac_user(pst_reg_params->uc_user_index);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ASSOC, "{dmac_join_set_reg_event_process::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 支持QOS 遍历寄存器*/
    hal_machw_seq_num_index_update_per_tid(pst_device->pst_device_stru, pst_dmac_user->uc_lut_index, OAL_TRUE);

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_mgmt_conn_result_event
 功能描述  : 处理hmac抛来的关联结果事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月15日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_conn_result_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    oal_uint32                           ul_result;
    oal_uint32                           ul_ret;
    mac_device_stru                     *pst_device;
    mac_vap_stru                        *pst_vap_up;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "pst_event_mem null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    ul_result               = *((oal_uint32 *)pst_event->auc_event_data);

    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_mgmt_conn_result_event::pst_device[%d] is NULL!}", pst_event_hdr->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_SUCC != ul_result)
    {
        /* 如果有vap up，则恢复到那个vap所在的信道 */
        ul_ret = mac_device_find_up_vap(pst_device, &pst_vap_up);
        if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
        {
            if (MAC_VAP_STATE_PAUSE == pst_vap_up->en_vap_state)
            {
                pst_device->st_home_channel = pst_vap_up->st_channel;
                dmac_scan_switch_channel_back(pst_device);

                OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_DBAC, "dmac_mgmt_conn_result_event: conn fail, switch to up vap. channel num:%d",
                                pst_device->st_home_channel.uc_chan_number);
            }
        }
    }

    dmac_tx_fake_queue_empty_assert(pst_device->pst_device_stru, HAL_TX_FAKE_QUEUE_BGSCAN_ID, THIS_FILE_ID);

    return OAL_SUCC;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

