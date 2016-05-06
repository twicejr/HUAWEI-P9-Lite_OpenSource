/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_rx_data.c
  版 本 号   : 初稿
  作    者   : huxiaotong
  生成日期   : 2012年11月20日
  最近修改   :
  功能描述   : DMAC模块接收帧的公共操作函数以及数据帧的操作函数定义的源文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月20日
    作    者   : huxiaotong
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
#include "oal_net.h"
#include "oam_ext_if.h"
#include "oam_main.h"

#include "wlan_spec.h"
#include "wlan_mib.h"

#include "mac_frame.h"
#include "mac_data.h"

#ifdef _PRE_WLAN_DFT_REG
#include "hal_witp_debug.h"
#endif
#include "hal_ext_if.h"
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hal_device.h"
#endif
#include "dmac_device.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_blockack.h"
#include "dmac_rx_data.h"
#include "dmac_stat.h"
#include "dmac_ext_if.h"

#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#include "dmac_test_sch.h"
#endif
#include "dmac_reset.h"

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#include "oal_profiling.h"

#include "dmac_dfx.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RX_DATA_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#define MAX_ERR_INFO_LEN 50 /*指示打印的错误信息最大长度*/

OAL_STATIC oal_uint32 ul_deauth_flow_control_ms = 0;
#define DEAUTH_INTERVAL_MIN 300 /*报文过滤过程中，发送去认证的最小间隔 300ms*/

#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1102_DEV)
/* 接收帧的FCS的统计信息 */
dmac_rx_fcs_statistic g_ast_rx_fcs_statistic[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT] =
{
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}
};
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_int32 g_l_proxysta_feature;
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_uint32 gul_rx_window_offset;
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/
oal_uint32  dmac_rx_send_event(
                dmac_vap_stru                           *pst_dmac_vap,
                dmac_wlan_crx_event_sub_type_enum_uint8  en_event,
                oal_uint8                               *puc_param,
                oal_uint32                               ul_len);


/*****************************************************************************
 函 数 名  : dmac_null_fn
 功能描述  : 空函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月18日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_null_fn(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    return;
}


/*****************************************************************************
 函 数 名  : dmac_rx_vap_stat
 功能描述  : 统计接收到的msdu个数和字节数，字节数步包括80211头，不包括snap头
             ，不包括padding
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月21日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
OAL_STATIC oal_uint32  dmac_rx_vap_stat(dmac_vap_stru *pst_dmac_vap,
                                            oal_netbuf_head_stru *pst_netbuf_hdr,
                                            oal_netbuf_stru     *pst_buf,
                                            dmac_rx_ctl_stru *pst_rx_cb)
{
    oal_uint32          *pul_mac_hdr;
    oal_uint8            uc_buf_nums;
    oal_netbuf_stru     *pst_buf_next;
    oal_uint8            uc_msdu_nums_in_mpdu = 0;
    oal_uint16           us_bytes;
    mac_rx_ctl_stru     *pst_rx_info = &(pst_rx_cb->st_rx_info);
    mac_ieee80211_frame_stru  *pst_frame_hdr;

    pul_mac_hdr = mac_get_rx_cb_mac_hdr(pst_rx_info);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pul_mac_hdr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_vap_stat::mac_hdr is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_frame_hdr  = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(pst_rx_info));

    if (!pst_rx_info->bit_amsdu_enable)
    {
        /* 此mpdu只有一个msdu，字节数应该去掉snap长度 */
        if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_pkts,  1);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_bytes,
                                    pst_rx_cb->st_rx_info.us_frame_len - pst_rx_cb->st_rx_info.bit_mac_header_len - SNAP_LLC_FRAME_LEN);
#else
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_bytes,
                                    pst_rx_cb->st_rx_info.us_frame_len - pst_rx_cb->st_rx_info.uc_mac_header_len - SNAP_LLC_FRAME_LEN);

#endif
        }
    }
    /* 如果此mpdu里面是amsdu，需要获取sub_msdu个数和每一个sub_msdu的字节数 */
    else
    {

        for (uc_buf_nums = 0; uc_buf_nums < pst_rx_cb->st_rx_info.bit_buff_nums; uc_buf_nums++)
        {
            pst_buf_next = oal_get_netbuf_next(pst_buf);

            /* 更新mpdu中msdu的数目 */
            uc_msdu_nums_in_mpdu += pst_rx_cb->st_rx_info.uc_msdu_in_buffer;

            pst_buf = pst_buf_next;
            if ((oal_netbuf_head_stru *)pst_buf == pst_netbuf_hdr)
            {
                break;
            }
            pst_rx_cb = (dmac_rx_ctl_stru *)OAL_NETBUF_CB(pst_buf);
        }
        if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_pkts, uc_msdu_nums_in_mpdu);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            /* 计算此mpdu的字节数目，所有sub_msdt字节数之和，不包括snap，不包括padding，注意最后一个sub_msdu没有padding */
            us_bytes = pst_rx_cb->st_rx_info.us_frame_len - pst_rx_cb->st_rx_info.bit_mac_header_len
                     - SNAP_LLC_FRAME_LEN * uc_msdu_nums_in_mpdu;
#else
            /* 计算此mpdu的字节数目，所有sub_msdt字节数之和，不包括snap，不包括padding，注意最后一个sub_msdu没有padding */
            us_bytes = pst_rx_cb->st_rx_info.us_frame_len - pst_rx_cb->st_rx_info.uc_mac_header_len
                     - SNAP_LLC_FRAME_LEN * uc_msdu_nums_in_mpdu;

#endif
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_bytes, us_bytes);
        }

    }

    return OAL_SUCC;
}
#endif

 /*****************************************************************************
 函 数 名  : dmac_rx_check_mgmt_replay_failure
 功能描述  : 检测是否是管理帧的重放攻击
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月23日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  dmac_rx_check_mgmt_replay_failure(dmac_rx_ctl_stru  *pst_cb_ctrl)
{
    mac_ieee80211_frame_stru  *pst_frame_hdr;

    /* 获取802.11头指针 */
    pst_frame_hdr  = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info));

    if (MAC_IEEE80211_FTYPE_MGMT != pst_frame_hdr->st_frame_control.bit_type)
    {
        return OAL_TRUE;
    }

    switch (pst_cb_ctrl->st_rx_status.bit_dscr_status)
    {
        case HAL_RX_CCMP_REPLAY_FAILURE:
        case HAL_RX_TKIP_REPLAY_FAILURE:
        case HAL_RX_BIP_REPLAY_FAILURE:
        {
            return OAL_TRUE;
        }
        default:
        {
            return OAL_FALSE;
        }
    }
}

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif

/*****************************************************************************
 函 数 名  : hal_rx_update_dscr_queue
 功能描述  : 该函数将中断上报上来的描述符从描述符队列中摘除,并且将描述符链表中的
             信息放到对应的netbuf的cb字段中，将netbuf组成链表，归还描述符
 输入参数  : (1)接收的队列的头指针
             (2)接收的队列号
             (3)接收到的第一个描述符的地址(软件看见的首地址)
             (4)hal提供给dmac的device的指针
             (5)指向netbuf头的指针
             (6)描述符的个数
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_rx_update_dscr_queue(
                hal_to_dmac_device_stru            *pst_device,
                hal_hw_rx_dscr_info_stru           *pst_rx_dscr_info,
                oal_netbuf_head_stru               *pst_netbuf_header,
                oal_uint16                         *pus_pre_dscr_num)
{
    hal_rx_dscr_queue_header_stru  *pst_rx_dscr_queue;
    dmac_rx_ctl_stru               *pst_cb_ctrl;                    /* 填写netbuf的cb字段使用 */
    oal_netbuf_stru                *pst_netbuf = OAL_PTR_NULL;      /* 指向每一个描述符对应的netbuf */
    oal_uint32                     *pul_curr_dscr;                  /* 正在处理的描述符 */
    oal_uint32                     *pul_next_dscr;                  /* 下一个需要处理的描述符 */
    hal_rx_dscr_stru               *pst_hal_to_dmac_dscr;           /* HAL向DMAC提供的对外描述符结构 */
    oal_bool_enum_uint8             en_last_int_flag = OAL_FALSE;   /* 最后上报的中断的标识 OAL_TRUE 代表开始处理本次中断*/
    oal_uint16                      us_dscr_num = pst_rx_dscr_info->us_dscr_num;
    hal_rx_dscr_queue_id_enum_uint8 en_queue_num = pst_rx_dscr_info->uc_queue_id;
#if (_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)
    oal_uint8                       *puc_mac_hdr_addr;
    oal_uint8                       *puc_tail;
    oal_uint16                      us_frame_len;
#endif
    oal_uint8                       uc_sub_type;
    oam_sdt_print_beacon_rxdscr_type_enum_uint8           en_beacon_switch;
    oal_uint32                      ul_rx_dscr_len;
    oal_switch_enum_uint8           en_rx_dscr_switch;

    pst_rx_dscr_queue = &(pst_device->ast_rx_dscr_queue[pst_rx_dscr_info->uc_queue_id]);

    pul_curr_dscr = pst_rx_dscr_queue->pul_element_head;

#ifdef _PRE_DEBUG_MODE
    if (pul_curr_dscr != pst_rx_dscr_info->pul_base_dscr)
    {
        pst_device->ul_rx_irq_loss_cnt++;
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{dmac_rx_update_dscr_queue::Losed interrupt[%d].", pst_device->ul_rx_irq_loss_cnt);
    }
#endif

    en_rx_dscr_switch = oam_ota_get_rx_dscr_switch();
    while(OAL_PTR_NULL != pul_curr_dscr)
    {
        /* 判断是否已经开始本次中断处理 */
        if (pul_curr_dscr == pst_rx_dscr_info->pul_base_dscr)
        {
            en_last_int_flag = OAL_TRUE;
        }

        /* 获取描述符对应的netbuf */
        hal_rx_get_netbuffer_addr_dscr(pst_device, pul_curr_dscr, &pst_netbuf);

        pst_cb_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

        /* 获取描述符个字段信息，并将其加到netbuf的cb字段中 */
        dmac_rx_get_dscr_info(pst_device, pul_curr_dscr, pst_cb_ctrl);

        /* 给cb中的信道号进行赋值 */
        pst_cb_ctrl->st_rx_info.uc_channel_number = pst_rx_dscr_info->uc_channel_num;
        /* 如果是beacon帧的接收描述符，则需要根据开关情况上报 */

        if (OAL_SWITCH_ON == en_rx_dscr_switch)
        {
            uc_sub_type = mac_get_frame_sub_type((oal_uint8 *)mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info)));
            en_beacon_switch = oam_ota_get_beacon_switch();
            hal_rx_get_size_dscr(pst_device, &ul_rx_dscr_len);
            if ((WLAN_FC0_SUBTYPE_BEACON != uc_sub_type)
                || (OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_RXDSCR == en_beacon_switch)
                || (OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BOTH == en_beacon_switch))
            {
                oam_report_dscr(BROADCAST_MACADDR, (oal_uint8 *)pul_curr_dscr, (oal_uint16)ul_rx_dscr_len, OAM_OTA_TYPE_RX_DSCR);
            }
        }

        if (HAL_RX_NEW == pst_cb_ctrl->st_rx_status.bit_dscr_status)
        {
//#if(_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)
            /*2015/5/9已解决1102 RX NEW 问题! z00262551*/
            //OAL_IO_PRINT("RX_NEW!!\r\n");
//#endif
            if (OAL_TRUE == en_last_int_flag)
            {
                /* 硬件RX_NEW */
                OAM_ERROR_LOG4(0, OAM_SF_RX, "{dmac_rx_update_dscr_queue::RX_NEW HARDWARE!phy addr=0x%08x,base phy addr=0x%08x,cnt=%d,q=%d.}",
                               OAL_VIRT_TO_PHY_ADDR(HAL_RX_DSCR_GET_REAL_ADDR(pul_curr_dscr)),
                               OAL_VIRT_TO_PHY_ADDR(HAL_RX_DSCR_GET_REAL_ADDR(pst_rx_dscr_info->pul_base_dscr)), us_dscr_num, en_queue_num);
            }
            else
            {
                /* 软件RX_NEW */
                OAM_ERROR_LOG4(0, OAM_SF_RX, "{dmac_rx_update_dscr_queue::RX_NEW SOFTWARE!phy addr=0x%08x,base phy addr=0x%08x,cnt=%d,q=%d.}",
                               OAL_VIRT_TO_PHY_ADDR(HAL_RX_DSCR_GET_REAL_ADDR(pul_curr_dscr)),
                               OAL_VIRT_TO_PHY_ADDR(HAL_RX_DSCR_GET_REAL_ADDR(pst_rx_dscr_info->pul_base_dscr)), us_dscr_num, en_queue_num);
#if(_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)
                //return OAL_FAIL;
#else
                return OAL_FAIL;
#endif
            }
#if 0
            pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;
            if(NULL != pst_hal_to_dmac_dscr->pul_next_rx_dscr)
                pul_next_dscr = HAL_RX_DSCR_GET_SW_ADDR(oal_get_virt_addr(pst_hal_to_dmac_dscr->pul_next_rx_dscr));
            else
                pul_next_dscr = NULL;
            hal_rx_sync_invalid_dscr(pst_device, pul_curr_dscr, en_queue_num);
            pul_curr_dscr = pul_next_dscr;
            continue;
#endif
        }

#if(_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)
        puc_mac_hdr_addr = oal_netbuf_header(pst_netbuf);
        oal_netbuf_set_len(pst_netbuf, pst_cb_ctrl->st_rx_info.us_frame_len);

        us_frame_len = pst_cb_ctrl->st_rx_info.us_frame_len;
        if (us_frame_len < WLAN_LARGE_NETBUF_SIZE)
        {
            puc_tail = puc_mac_hdr_addr + us_frame_len;
        }
        else
        {
            puc_tail = puc_mac_hdr_addr + WLAN_LARGE_NETBUF_SIZE;
        }
        oal_set_netbuf_tail(pst_netbuf, puc_tail);
#else
        oal_netbuf_trim(pst_netbuf, OAL_NETBUF_LEN(pst_netbuf));
    #ifdef _PRE_WLAN_HW_TEST
        if (HAL_ALWAYS_RX_RESERVED == pst_device->bit_al_rx_flag)          /* 常收 */
        {
            if(pst_cb_ctrl->st_rx_info.us_frame_len < HAL_AL_RX_FRAME_LEN)
            {
                oal_netbuf_put(pst_netbuf, pst_cb_ctrl->st_rx_info.us_frame_len);
            }
            else
            {
                oal_netbuf_put(pst_netbuf, HAL_AL_RX_FRAME_LEN);
            }
        }
        else
    #endif
        {
            /* DTS2015060301543,帧长超过1600时，buf最大填成1600，后续buf依次填充帧长减去1600 */
            if(pst_cb_ctrl->st_rx_info.us_frame_len < WLAN_LARGE_NETBUF_SIZE)
            {
                oal_netbuf_put(pst_netbuf, pst_cb_ctrl->st_rx_info.us_frame_len);
            }
            else
            {
                oal_netbuf_put(pst_netbuf, WLAN_LARGE_NETBUF_SIZE);
            }
        }
        /*OAL_NETBUF_LEN(pst_netbuf)  = pst_cb_ctrl->st_rx_info.us_frame_len;
        OAL_NETBUF_TAIL(pst_netbuf) = (pst_cb_ctrl->st_rx_info.us_frame_len < WLAN_LARGE_NETBUF_SIZE)
                                       ? (oal_netbuf_data(pst_netbuf) + pst_cb_ctrl->st_rx_info.us_frame_len)
                                       : (oal_netbuf_data(pst_netbuf) + WLAN_LARGE_NETBUF_SIZE);*/
#endif
        /* 加入到netbuf的链表中 */
        oal_netbuf_add_to_list_tail(pst_netbuf, pst_netbuf_header);

        /* 获得下一个需要处理的描述符 */
        pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;

        if(NULL != pst_hal_to_dmac_dscr->pul_next_rx_dscr)
        {
            pul_next_dscr = HAL_RX_DSCR_GET_SW_ADDR(oal_get_virt_addr(pst_hal_to_dmac_dscr->pul_next_rx_dscr));
        }
        else
        {
            pul_next_dscr = NULL;
        }

        if (OAL_TRUE == en_last_int_flag)
        {
            us_dscr_num = OAL_SUB(us_dscr_num, 1);
        }
        else
        {
            (*pus_pre_dscr_num)++;    /* 非本次中断的描述符的个数增加1 */
        }

        /* 51 暂时取消该轨迹追踪DEBUG */
#if (_PRE_PRODUCT_ID_HI1151 != _PRE_PRODUCT_ID)
    #ifdef _PRE_DEBUG_MODE
        /* 记录下半部描述符处理轨迹 */
        if (OAL_FALSE == pst_device->ul_track_stop_flag)
        {
            pst_device->ul_dpart_save_idx++;
        }

        if (pst_device->ul_dpart_save_idx >= HAL_DOWM_PART_RX_TRACK_MEM)
        {
            pst_device->ul_dpart_save_idx = 0;
        }

        OAL_MEMZERO(&pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx], OAL_SIZEOF(hal_rx_dpart_track_stru));
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_phy_addr = OAL_VIRT_TO_PHY_ADDR(HAL_RX_DSCR_GET_REAL_ADDR(pul_curr_dscr));
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].uc_status   = pst_cb_ctrl->st_rx_status.bit_dscr_status;
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].uc_q        = en_queue_num;
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_timestamp= pul_curr_dscr[HAL_DEBUG_RX_DSCR_LINE];
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_irq_cnt  = pst_device->ul_irq_cnt;
        oal_get_cpu_stat(&pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].st_cpu_state);
    #endif
#endif

        OAL_MEM_TRACE(pul_curr_dscr, OAL_FALSE);
        /* 归还描述符 */
        hal_rx_free_dscr_list(pst_device, en_queue_num, pul_curr_dscr);

        /* 判断是否处理完成 */
        if (0 == us_dscr_num)
        {
            break;
        }

        pul_curr_dscr = pul_next_dscr;
    }

    return OAL_SUCC;
}
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

#if 0
/*****************************************************************************
 函 数 名  : dmac_rx_filter_wlan_security_supplicant
 功能描述  : 根据是否通过802.1X认证来过滤STA数据帧。通过认证，则不过滤；未通过
             认证，则过滤。
 输入参数  : mac_vap_stru   *pst_mac_vap
             dmac_user_stru *pst_dmac_user
 输出参数  : 无
 返 回 值  : oal_uint32    OAL_FAIL:   对数据过滤
                           OAL_SUCC:不对数据过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月9日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_rx_filter_wlan_security_supplicant(mac_vap_stru *pst_mac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint32       ul_ret       = OAL_SUCC;
    mac_user_stru   *pst_mac_user = (mac_user_stru *)&(pst_dmac_user->st_user_base_info);

    /* 判断加密方式是否为 WPA/WPA2 */
    if ((OAL_TRUE == pst_mac_vap->st_cap_flag.bit_wpa)
       || (OAL_TRUE == pst_mac_vap->st_cap_flag.bit_wpa2))
    {
        /* 判断认证方式是否为1X 认证 */
        if (WLAN_AUTH_SUITE_1X == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[0].uc_dot11RSNAConfigAuthenticationSuiteImplemented)
        {
            if (pst_mac_user->en_port_valid != OAL_TRUE)
            {
                ul_ret = OAL_FAIL;
            }
        }
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_rx_filter_wlan_security_authenticator
 功能描述  : 根据是否通过802.1X认证来过滤AP数据帧。通过认证，则不过滤；未通过
             认证，则过滤。
 输入参数  : mac_vap_stru   *pst_mac_vap
             dmac_user_stru *pst_dmac_user
 输出参数  : 无
 返 回 值  : oal_uint32    OAL_FAIL:   对数据过滤
                           OAL_SUCC:不对数据过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月9日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_rx_filter_wlan_security_authenticator(mac_vap_stru *pst_mac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint32       ul_ret       = OAL_SUCC;
    mac_user_stru   *pst_mac_user = (mac_user_stru *)&(pst_dmac_user->st_user_base_info);

    /* 判断加密方式是否为 WPA/WPA2 */
    if ((OAL_TRUE == pst_mac_vap->st_cap_flag.bit_wpa)
       || (OAL_TRUE == pst_mac_vap->st_cap_flag.bit_wpa2))
    {
        /* 判断认证方式是否为1X 认证 */
        if (WLAN_AUTH_SUITE_1X == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[0].uc_dot11RSNAConfigAuthenticationSuiteImplemented)
        {
            if (pst_mac_user->en_port_valid != OAL_TRUE)
            {
                ul_ret = OAL_FAIL;
            }
        }
    }

    return ul_ret;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_rx_filter_wlan_security
 功能描述  : 对接收到的帧进行安全过滤处理
 输入参数  : mac_vap_stru   *pst_mac_vap
             dmac_user_stru *pst_dmac_user
 输出参数  : 无
 返 回 值  : oal_uint32    OAL_FAIL:   对数据过滤
                           OAL_SUCC:不对数据过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月22日
    作    者   : l00218984
    修改内容   : 新生成函数
  2.日    期   : 2016年1月9日
    作    者   : g00260350
    修改内容   : 加密类型不需要比较，mac已经能解开这个报文了，只需要过滤eapol帧
*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
#endif
oal_uint32 dmac_rx_filter_wlan_security(mac_vap_stru *pst_mac_vap, dmac_rx_ctl_stru *pst_cb_ctrl, oal_netbuf_stru *pst_netbuf)
{
    mac_user_stru                       *pst_mac_user;
    mac_llc_snap_stru                   *pst_snap;
    oal_uint16                           us_user_idx;

    /* 接收数据时，针对非EAPOL 的数据帧做过滤 */
#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    us_user_idx    = MAC_GET_RX_CB_TA_USER_IDX(&(pst_cb_ctrl->st_rx_info));
    pst_mac_user   = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);
	if ( OAL_PTR_NULL == pst_mac_user)
	{
		OAM_WARNING_LOG1(0, OAM_SF_WPA,"{dmac_rx_filter_wlan_security::mac_res_get_mac_user fail.us_user_idx[%u]}",us_user_idx);
		return OAL_ERR_CODE_SECURITY_BUFF_LEN;
	}

    if (pst_mac_user->en_port_valid == OAL_FALSE)
    {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        pst_snap = (mac_llc_snap_stru *)(OAL_NETBUF_DATA(pst_netbuf) + pst_cb_ctrl->st_rx_info.uc_mac_header_len);
#else
        pst_snap = (mac_llc_snap_stru *)oal_netbuf_payload(pst_netbuf);
#endif
        if (OAL_PTR_NULL == pst_snap)
        {
            return OAL_ERR_CODE_SECURITY_BUFF_LEN;
        }

        if (OAL_HTON_16(ETHER_TYPE_PAE) != pst_snap->us_ether_type)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_rx_filter_wlan_security::TYPE 0x%04x not permission.}", pst_snap->us_ether_type);
            return OAL_ERR_CODE_SECURITY_PORT_INVALID;
        }
    }

#endif  //defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)

    return OAL_SUCC;
}
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/******************************************************************************
 函 数 名  : dmac_rx_mpdu_filter_duplicate_frame_proxysta
 功能描述  : proxysta的非聚合帧重复帧检测
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月28日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_mpdu_filter_duplicate_frame_proxysta(
                mac_vap_stru               *pst_mac_vap,
                mac_ieee80211_frame_stru   *pst_frame_hdr,
                dmac_rx_ctl_stru           *pst_cb_ctrl)
{
    oal_uint8               uc_tid;
    oal_uint16              us_seq_num;
    oal_bool_enum_uint8     en_is_4addr;
    oal_uint8               uc_is_tods;
    oal_uint8               uc_is_from_ds;

    us_seq_num = mac_get_seq_num((oal_uint8 *)pst_frame_hdr);

    /* 考虑四地址情况获取报文的tid */
    uc_is_tods    = mac_hdr_get_to_ds((oal_uint8 *)pst_frame_hdr);
    uc_is_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_frame_hdr);
    en_is_4addr   = uc_is_tods && uc_is_from_ds;

    if (0 == pst_frame_hdr->st_frame_control.bit_retry)
    {
        if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
        {
            pst_mac_vap->us_non_qos_seq_num   = us_seq_num;

        }
        else
        {
            uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

            pst_mac_vap->aus_last_qos_seq_num[uc_tid] = us_seq_num;
        }

        return OAL_SUCC;
    }

    /* 判断该帧是不是qos帧 */
    if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
    {
        if (us_seq_num == pst_mac_vap->us_non_qos_seq_num)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                             "{dmac_rx_mpdu_filter_duplicate_frame_proxysta::non qos duplicate frame[%d]}",
                             us_seq_num);

            return OAL_FAIL;
        }

        pst_mac_vap->us_non_qos_seq_num = us_seq_num;

        return OAL_SUCC;
    }

    uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

    /* qos过滤 */
    if (us_seq_num == pst_mac_vap->aus_last_qos_seq_num[uc_tid])
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                         "{dmac_rx_mpdu_filter_duplicate_frame_proxysta::tid is[%d],qos duplicate frame[%d]. }",
                         uc_tid,
                         us_seq_num);

        return OAL_FAIL;
    }
    else
    {
        pst_mac_vap->aus_last_qos_seq_num[uc_tid] = us_seq_num;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_rx_data_user_is_null
 功能描述  : 收到数据帧找不到用户时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月29日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_rx_data_user_is_null(mac_vap_stru *pst_mac_vap, mac_ieee80211_frame_stru *pst_frame_hdr)
{
    dmac_vap_stru           *pst_dmac_vap;
    oal_uint32               ul_cur_tick_ms;
    dmac_diasoc_deauth_event st_deauth_evt;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id,OAM_SF_PWR,"{dmac_rx_data_user_is_null::mac_res_get_dmac_vap fail}");
        return;
    }

    OAM_STAT_VAP_INCR(pst_mac_vap->uc_vap_id, rx_ta_check_dropped, 1);
    DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ta_check_dropped, 1);

    ul_cur_tick_ms = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    if (ul_cur_tick_ms < ul_deauth_flow_control_ms + DEAUTH_INTERVAL_MIN)
    {
        return;
    }

    ul_deauth_flow_control_ms = ul_cur_tick_ms;

    oal_memcopy(st_deauth_evt.auc_des_addr, pst_frame_hdr->auc_address2, WLAN_MAC_ADDR_LEN);
    st_deauth_evt.uc_reason = MAC_NOT_AUTHED;
    st_deauth_evt.uc_event  = DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH;

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_RX, "dmac_rx_data_user_is_null: ta: %02X:XX:XX:%02X:%02X:%02X. post sending deauth event to hmac",
                        pst_frame_hdr->auc_address2[0],
                        pst_frame_hdr->auc_address2[3],
                        pst_frame_hdr->auc_address2[4],
                        pst_frame_hdr->auc_address2[5]);

    dmac_rx_send_event(pst_dmac_vap, DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH, (oal_uint8 *)&st_deauth_evt, OAL_SIZEOF(st_deauth_evt));
}

/*****************************************************************************
 函 数 名  : dmac_rx_filter_frame_sta
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月13日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
#endif

oal_uint32  dmac_rx_filter_frame_sta(
                mac_vap_stru           *pst_vap,
                dmac_rx_ctl_stru       *pst_cb_ctrl,
                dmac_user_stru             *pst_dmac_user)
{
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    oal_uint32                  ul_ret = OAL_SUCC;

    /* 获取用户、帧信息 */
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info));

    if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
    {
        if (OAL_PTR_NULL == pst_dmac_user)
        {
            /* 返回OAL_FAIL 表示数据帧需要过滤 */
            dmac_rx_data_user_is_null(pst_vap, pst_frame_hdr);

            return OAL_FAIL;
        }
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (OAL_TRUE == g_l_proxysta_feature)
        {
            /* 非AMPDU重复帧过滤 */
            if (OAL_FALSE == pst_cb_ctrl->st_rx_status.bit_AMPDU)
            {
                ul_ret = dmac_rx_mpdu_filter_duplicate_frame_proxysta(pst_vap, pst_frame_hdr, pst_cb_ctrl);
                if(OAL_SUCC != ul_ret)
                {
                    return ul_ret;
                }
            }
        }
#endif

    #ifdef _PRE_WLAN_FEATURE_AMPDU
        ul_ret = dmac_ba_filter_serv(pst_vap, pst_dmac_user, pst_cb_ctrl, pst_frame_hdr);
    #endif


        /* 更新用户的RSSI统计信息 */
        if (OAL_PTR_NULL != pst_dmac_user)
        {
            pst_dmac_user->c_rx_rssi = wlan_rssi_lpf(pst_dmac_user->c_rx_rssi,
                                                                   pst_cb_ctrl->st_rx_statistic.c_rssi_dbm);
        }
    }

    /* 更新rx与11n协议相关的mib */
    dmac_rx_update_mib_11n(pst_vap, pst_cb_ctrl);

    return ul_ret;
}
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
#endif

/*****************************************************************************
 函 数 名  : dmac_mgmt_send_event
 功能描述  : DMAC抛事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月14日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_send_event(
                dmac_vap_stru         *pst_dmac_vap,
                dmac_wlan_crx_event_sub_type_enum_uint8 en_event,
                oal_uint8                 *puc_param,
                oal_uint32             ul_len)
{
    frw_event_mem_stru             *pst_event_mem;      /* 申请事件返回的内存指针 */
    frw_event_stru                 *pst_hmac_to_dmac_ctx_event;

    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)ul_len);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_send_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获得事件指针 */
    pst_hmac_to_dmac_ctx_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_ctx_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       en_event,
                       (oal_uint16)ul_len,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_dmac_vap->st_vap_base_info.uc_chip_id,
                       pst_dmac_vap->st_vap_base_info.uc_device_id,
                       pst_dmac_vap->st_vap_base_info.uc_vap_id);

    oal_memcopy(pst_hmac_to_dmac_ctx_event->auc_event_data,
                puc_param, ul_len);
    /* 分发 */
    frw_event_dispatch_event(pst_event_mem);

    /* 释放事件内存 */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_rx_mpdu_filter_duplicate_frame
 功能描述  : 非聚合帧重复帧检测
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月15日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_mpdu_filter_duplicate_frame(
                dmac_user_stru             *pst_dmac_user,
                mac_ieee80211_frame_stru   *pst_frame_hdr,
                dmac_rx_ctl_stru           *pst_cb_ctrl)
{
    oal_uint8               uc_tid;
    oal_uint16              us_seq_num;
    oal_uint16              us_seq_frag_num;
    oal_bool_enum_uint8     en_is_4addr;
    oal_uint8               uc_is_tods;
    oal_uint8               uc_is_from_ds;

    us_seq_num = mac_get_seq_num((oal_uint8 *)pst_frame_hdr);

    us_seq_frag_num = ((oal_uint16)(pst_frame_hdr->bit_seq_num) << 4) | pst_frame_hdr->bit_frag_num;

    /* 考虑四地址情况获取报文的tid */
    uc_is_tods    = mac_hdr_get_to_ds((oal_uint8 *)pst_frame_hdr);
    uc_is_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_frame_hdr);
    en_is_4addr   = uc_is_tods && uc_is_from_ds;

    if (0 == pst_frame_hdr->st_frame_control.bit_retry)
    {
        if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
        {
            pst_dmac_user->us_non_qos_seq_frag_num = us_seq_frag_num;
        }
        else
        {
            uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

            pst_dmac_user->ast_tx_tid_queue[uc_tid].us_last_seq_frag_num = us_seq_frag_num;
        }

        return OAL_SUCC;
    }

    /* 判断该帧是不是qos帧 */
    if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
    {
        if (us_seq_frag_num == pst_dmac_user->us_non_qos_seq_frag_num)
        {
            OAM_WARNING_LOG2(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_RX,
                             "{dmac_rx_ucast_filter_duplicate_frame::non qos duplicate frame[%d], seq_num with frag_num [%d]}",
                             us_seq_num, us_seq_frag_num);

            return OAL_FAIL;
        }

        pst_dmac_user->us_non_qos_seq_frag_num = us_seq_frag_num;

        return OAL_SUCC;
    }

    uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

    /* qos过滤 */
    if (us_seq_frag_num == pst_dmac_user->ast_tx_tid_queue[uc_tid].us_last_seq_frag_num)
    {
        OAM_WARNING_LOG3(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_RX,
                         "{dmac_rx_ucast_filter_duplicate_frame::tid is[%d],qos duplicate frame[%d], seq_num with frag num [%d].}",
                         uc_tid, us_seq_num, us_seq_frag_num);

        return OAL_FAIL;
    }
    else
    {
        pst_dmac_user->ast_tx_tid_queue[uc_tid].us_last_seq_frag_num = us_seq_frag_num;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_rx_filter_frame_ap
 功能描述  : AP模式下，对MPDU的帧头信息过滤
 输入参数  : (1)指向对应vap的指针
             (2)指向接收控制信息的结构的指针
 输出参数  : 无
 返 回 值  : OAL_FAIL:  表明需要过滤数据
             OAL_SUCC:  表明不需要过滤数据
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_filter_frame_ap(
                mac_vap_stru           *pst_vap,
                dmac_rx_ctl_stru       *pst_cb_ctrl)
{
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    dmac_user_stru             *pst_dmac_user;
    oal_uint32                  ul_ret = OAL_SUCC;
    dmac_diasoc_deauth_event    st_disasoc_evt;
    oal_uint32                  ul_len = 0;
    dmac_vap_stru              *pst_dmac_vap;
    oal_uint32                  ul_cur_tick_ms = 0;

    /* 获取用户、帧信息 */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&(pst_cb_ctrl->st_rx_info)));
    pst_frame_hdr = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info)));
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);

    if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
    {
        if (OAL_PTR_NULL == pst_dmac_user)  /* 用户不存在 */
        {
            /* 返回OAL_FAIL 表示数据帧需要过滤 */
            dmac_rx_data_user_is_null(pst_vap, pst_frame_hdr);

            return OAL_FAIL;
        }

        if(MAC_USER_STATE_ASSOC != pst_dmac_user->st_user_base_info.en_user_asoc_state)/* 用户未关联 */
        {
            /* 返回OAL_FAIL 表示数据帧需要过滤 */
            OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_frame_ap::status is not assoc,user index:%d,en_user_asoc_state:%d}",
                             pst_dmac_user->st_user_base_info.us_assoc_id,
                             pst_dmac_user->st_user_base_info.en_user_asoc_state);

            OAM_WARNING_LOG4(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_frame_ap::user mac:%02X:XX:XX:%02X:%02X:%02X}",
                             pst_dmac_user->st_user_base_info.auc_user_mac_addr[0],
                             pst_dmac_user->st_user_base_info.auc_user_mac_addr[3],
                             pst_dmac_user->st_user_base_info.auc_user_mac_addr[4],
                             pst_dmac_user->st_user_base_info.auc_user_mac_addr[5]);

            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_ta_check_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ta_check_dropped, 1);

            ul_cur_tick_ms = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            if (ul_cur_tick_ms < ul_deauth_flow_control_ms + DEAUTH_INTERVAL_MIN)
            {
                return OAL_FAIL;
            }

            ul_deauth_flow_control_ms = ul_cur_tick_ms;
            oal_memcopy(st_disasoc_evt.auc_des_addr, pst_frame_hdr->auc_address2, WLAN_MAC_ADDR_LEN);
            st_disasoc_evt.uc_reason = MAC_NOT_ASSOCED;
            st_disasoc_evt.uc_event  = DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC;
            ul_len = OAL_SIZEOF(st_disasoc_evt);

            dmac_rx_send_event(pst_dmac_vap, DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC, (oal_uint8 *)&st_disasoc_evt, ul_len);
            return OAL_FAIL;
        }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        /* 非AMPDU重复帧过滤 */
        if (OAL_FALSE == pst_cb_ctrl->st_rx_status.bit_AMPDU)
        {
            ul_ret = dmac_rx_mpdu_filter_duplicate_frame(pst_dmac_user, pst_frame_hdr, pst_cb_ctrl);
            if(OAL_SUCC != ul_ret)
            {
                return ul_ret;
            }
        }
#endif

    #ifdef _PRE_WLAN_FEATURE_AMPDU
        ul_ret = dmac_ba_filter_serv(pst_vap, pst_dmac_user, pst_cb_ctrl, pst_frame_hdr);
    #endif

        /* 更新用户的RSSI统计信息 */
        pst_dmac_user->c_rx_rssi = wlan_rssi_lpf(pst_dmac_user->c_rx_rssi,
                                                 pst_cb_ctrl->st_rx_statistic.c_rssi_dbm);
    }
    else
    {

    }

    /* 更新rx与11n协议相关的mib */
    dmac_rx_update_mib_11n(pst_vap, pst_cb_ctrl);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_rx_get_vap
 功能描述  : 获取每一个MPDU的对应的VAP
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月31日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_rx_get_vap(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_hal_vap_id, oal_uint8 uc_rx_queue_id, mac_vap_stru **pst_vap)
{
    hal_to_dmac_vap_stru       *pst_hal_vap  = OAL_PTR_NULL;
    oal_uint8                   uc_mac_vap_id;

#if (defined _PRE_WLAN_FEATURE_DBAC) || (defined _PRE_WLAN_FEATURE_PROXYSTA) || (defined _PRE_WLAN_DFT_STAT)
    mac_device_stru            *pst_device;

    pst_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_get_vap::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

#ifdef _PRE_WLAN_DFT_STAT
    if ((WLAN_HAL_OTHER_BSS_UCAST_ID == uc_hal_vap_id)
        && (OAL_TRUE == pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg))
    {
        pst_device->st_dbb_env_param_ctx.ul_non_directed_frame_num++;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        /* 如果开启Proxy STA特性，则hal_vap_id的合法范围为0~4,16~31 */
        if (uc_hal_vap_id > WLAN_PROXY_STA_END_ID)
        {
            //OAM_INFO_LOG1(0, OAM_SF_PROXYSTA, "{dmac_rx_get_vap::enable proxy sta vap index is exceed spec!uc_hal_vap_id:%d}", uc_hal_vap_id);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }
    else
    {
        /* 如果没有开启Proxy STA特性，则hal_vap_id的合法范围为0~4 */
        if (uc_hal_vap_id > WLAN_HAL_OHTER_BSS_ID)
        {
            //OAM_INFO_LOG1(0, OAM_SF_PROXYSTA, "{dmac_rx_get_vap::disable proxy sta vap index is exceed spec!uc_hal_vap_id:%d}", uc_hal_vap_id);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }
#else
    if (uc_hal_vap_id > WLAN_HAL_OHTER_BSS_ID)
    {
        //OAM_INFO_LOG1(0, OAM_SF_RX, "{dmac_rx_get_vap::vap index is exceed spec!uc_hal_vap_id:%d}", uc_hal_vap_id);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
         /* 通过hal接口获取mac层vap id */
        if ((uc_hal_vap_id < WLAN_HAL_OHTER_BSS_ID)||((uc_hal_vap_id >= WLAN_PROXY_STA_START_ID) && (uc_hal_vap_id <= WLAN_PROXY_STA_END_ID)))
        {
            hal_get_hal_vap(pst_hal_device, uc_hal_vap_id, &pst_hal_vap);
            if (OAL_PTR_NULL == pst_hal_vap)
            {
                *pst_vap = OAL_PTR_NULL;
                return OAL_ERR_CODE_PTR_NULL;
            }

            uc_mac_vap_id = pst_hal_vap->uc_mac_vap_id;
        }
        else    /* 广播帧使用配置vap进行操作 */
        {
            uc_mac_vap_id = 0;

            /* 其它BSS的广播数据帧直接过滤掉 */
            if (HAL_RX_DSCR_NORMAL_PRI_QUEUE == uc_rx_queue_id)
            {
                OAM_WARNING_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_get_vap::broadcast packets from other bss, should be filtered}");
                return OAL_FAIL;
            }
        }
    }
    else
    {
         /* 通过hal接口获取mac层vap id */
        if (uc_hal_vap_id < WLAN_HAL_OHTER_BSS_ID)
        {
            hal_get_hal_vap(pst_hal_device, uc_hal_vap_id, &pst_hal_vap);
            if (OAL_PTR_NULL == pst_hal_vap)
            {
                OAM_WARNING_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_get_vap::hal vap is null ptr}");
                return OAL_ERR_CODE_PTR_NULL;
            }

            uc_mac_vap_id = pst_hal_vap->uc_mac_vap_id;
        }
        else    /* 广播帧使用配置vap进行操作 */
        {
            uc_mac_vap_id = 0;

            /* 其它BSS的广播数据帧直接过滤掉 */
            if (HAL_RX_DSCR_NORMAL_PRI_QUEUE == uc_rx_queue_id)
            {
                //OAM_INFO_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_get_vap::broadcast packets from other bss, should be filtered}");
                return OAL_FAIL;
            }
        }
    }
#else
     /* 通过hal接口获取mac层vap id */
    if (uc_hal_vap_id < WLAN_HAL_OHTER_BSS_ID)
    {
        hal_get_hal_vap(pst_hal_device, uc_hal_vap_id, &pst_hal_vap);
        if (OAL_PTR_NULL == pst_hal_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_RX, "{dmac_rx_get_vap::pst_hal_vap null.hal_vap_id[%d]}", uc_hal_vap_id);

            return OAL_ERR_CODE_PTR_NULL;
        }

        uc_mac_vap_id = pst_hal_vap->uc_mac_vap_id;
    }
    else    /* 广播帧使用配置vap进行操作 */
    {
        uc_mac_vap_id = 0;

        /* 其它BSS的广播数据帧直接过滤掉 */
        if (HAL_RX_DSCR_NORMAL_PRI_QUEUE == uc_rx_queue_id)
        {
            //OAM_INFO_LOG0(0, OAM_SF_RX, "{dmac_rx_get_vap::broadcast packets from other bss, should be filtered.}");
            return OAL_FAIL;
        }
    }
#endif

    *pst_vap = (mac_vap_stru *)mac_res_get_dmac_vap(uc_mac_vap_id);
    if (OAL_PTR_NULL == *pst_vap)
    {
        OAM_ERROR_LOG0(uc_mac_vap_id, OAM_SF_RX, "{dmac_rx_get_vap::pst_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_RX_DISABLE == pst_hal_device->bit_al_rx_flag)
#endif
    {
        /* 数据帧情况下，判断VAP是否已经UP */
        if (((*pst_vap)->en_vap_state != MAC_VAP_STATE_UP) && (HAL_RX_DSCR_NORMAL_PRI_QUEUE == uc_rx_queue_id))
        {
            if ((*pst_vap)->en_vap_state == MAC_VAP_STATE_PAUSE
            #ifdef _PRE_WLAN_FEATURE_ROAM
                || (*pst_vap)->en_vap_state == MAC_VAP_STATE_ROAMING
            #endif //_PRE_WLAN_FEATURE_ROAM
                )
            {
                return OAL_SUCC;
            }

            OAM_WARNING_LOG2(uc_mac_vap_id, OAM_SF_RX, "{dmac_rx_get_vap::the vap is not up! en_dscr_queue_id=%d en_vap_state=%d.",
                             uc_rx_queue_id, (*pst_vap)->en_vap_state);
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

            /* 丢包统计 */
            (*pst_vap)->st_vap_stats.ul_rx_vap_non_up_dropped++;
#endif
            return OAL_FAIL;
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_rx_process_dscr
 功能描述  : 该函数包括对描述符同步、摘除需要操作的描述符的入口函数
 输入参数  : (1)指向接收队列指针
             (2)操作的队列号码
             (3)接收信息结构的指针
             (4)hal提供给dmac的device的指针
             (5)指向发给hmac的netbuf的指针
 输出参数  : 描述符数目
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif

OAL_STATIC oal_uint32  dmac_rx_get_dscr_list(
                hal_to_dmac_device_stru        *pst_device,
                hal_hw_rx_dscr_info_stru       *pst_rx_isr_info,
                frw_event_stru                 *pst_event,
                oal_netbuf_head_stru           *pst_netbuf_header)
{
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_vap_stru           *pst_vap;
#endif
    oal_uint8               uc_vap_id;
    oal_uint8               uc_rx_dscr_status;      /* 接收的描述符的状态 */
    oal_netbuf_stru        *pst_netbuf;
    oal_uint16              us_pre_dscr_num = 0;    /* 保存异常中断未处理的描述符的个数 */
    oal_uint32              ul_ret;

    hal_wlan_rx_event_stru *pst_wlan_rx_event = (hal_wlan_rx_event_stru *)(pst_event->auc_event_data);
    uc_vap_id = pst_event->st_event_hdr.uc_vap_id;

    /* 将中断上报的所有描述符从接收队列中摘除 */
    ul_ret = dmac_rx_update_dscr_queue(pst_device, pst_rx_isr_info, pst_netbuf_header, &us_pre_dscr_num);
    if (OAL_SUCC != ul_ret)
    {
        /* DTS2015042305849,出现软件RX NEW时，这里要保证pst_wlan_rx_event的num计数和buf链表里面buf个数一致，并且uc_pre_dscr_num改为us_pre_dscr_num */
#if(_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)
        //pst_wlan_rx_event->us_dscr_num += us_pre_dscr_num;
#else
        pst_wlan_rx_event->us_dscr_num += us_pre_dscr_num;
#endif
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_RX, "{dmac_rx_get_dscr_list::dmac_rx_update_dscr_queue failed[%d].", ul_ret);
        return OAL_FAIL;
    }

    if(oal_netbuf_list_empty(pst_netbuf_header))
    {
        if(pst_rx_isr_info->us_dscr_num)
        {
            OAL_IO_PRINT("[ERROR]did not found netbuf but us_dscr_num is %d\r\n", pst_rx_isr_info->us_dscr_num);
        }
        return OAL_SUCC;
    }

    /* 增加异常描述符的个数，该个数会在dmac_rx_update_dscr_queue函数中进行统计 */
    pst_wlan_rx_event->us_dscr_num += us_pre_dscr_num;

    /* 获取接收到的第一个描述符的状态 */
    uc_rx_dscr_status = ((dmac_rx_ctl_stru *)(oal_netbuf_cb(oal_netbuf_peek(pst_netbuf_header))))->st_rx_status.bit_dscr_status;

    /* 描述符异常:接收描述符更新异常 */
    if (OAL_UNLIKELY(HAL_RX_NEW == uc_rx_dscr_status))
    {
        OAM_WARNING_LOG0(uc_vap_id, OAM_SF_RX, "{dmac_rx_get_dscr_list::the rx_state of the base dscr is HAL_RX_NEW.}");

        pst_netbuf = oal_netbuf_peek(pst_netbuf_header);
        dmac_rx_free_netbuf_list(pst_netbuf_header, &pst_netbuf, pst_wlan_rx_event->us_dscr_num);
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        pst_vap = (mac_vap_stru *)mac_res_get_dmac_vap(uc_vap_id);
        if (OAL_PTR_NULL != pst_vap)
        {
           /* 丢包统计 */
            pst_vap->st_vap_stats.ul_rx_first_dscr_excp_dropped += pst_wlan_rx_event->us_dscr_num;
        }
#endif
        return OAL_FAIL;
    }

    return OAL_SUCC;
}
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

/*****************************************************************************
 函 数 名  : dmac_rx_process_data_event
 功能描述  : DMAC模块下，处理接收到帧的事件的入口函数，包括管理帧和数据帧
             接收流程总入口
 输入参数  : 指向事件结构体的指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
#endif

oal_void  dmac_rx_process_data_mgmt_event(frw_event_mem_stru *pst_event_mem,
                                       oal_netbuf_head_stru  *pst_netbuf_header,
                                       mac_vap_stru          *pst_vap,
                                       oal_netbuf_stru       *pst_netbuf)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    hal_wlan_rx_event_stru             *pst_wlan_rx_event;
    hal_to_dmac_device_stru            *pst_device;
    dmac_wlan_drx_event_stru           *pst_wlan_rx;
    oal_uint32                          ul_rslt;
    oal_netbuf_stru                    *pst_first_buf = OAL_PTR_NULL;
    dmac_vap_stru                      *pst_dmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_mgmt_event::pst_vap null.}");

        pst_first_buf = oal_netbuf_peek(pst_netbuf_header);

        /* 异常 释放资源 */
        dmac_rx_free_netbuf_list(pst_netbuf_header, &pst_first_buf, (oal_uint16)oal_netbuf_get_buf_num(pst_netbuf_header));

        return;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    /* 获取事件头和事件结构体指针 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_wlan_rx_event       = (hal_wlan_rx_event_stru *)(pst_event->auc_event_data);
    pst_device              = pst_wlan_rx_event->pst_hal_device;

    /* DMAC抛到HMAC的VAP ID改变成真正VAP的ID */
    pst_event_hdr->uc_vap_id = pst_vap->uc_vap_id;

    /* 数据帧处理 */
    if (FRW_EVENT_TYPE_WLAN_DRX == pst_event_hdr->en_type)
    {
        if (0 == pst_vap->uc_vap_id || WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT < pst_vap->uc_vap_id)
        {
            OAM_ERROR_LOG1(0, OAM_SF_RX, "{dmac_rx_process_data_mgmt_event::pst_event_mem vap[%d].}", pst_vap->uc_vap_id);
        }

        /* 将最后一个NETBUF置空 */
        oal_set_netbuf_next((oal_netbuf_tail(pst_netbuf_header)), OAL_PTR_NULL);

        if (WLAN_VAP_MODE_BSS_AP == dmac_vap_get_bss_type(pst_vap))
        {
            /* AP模式，继承事件，并且修改事件头 */
            FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_AP);
        }
        else if (WLAN_VAP_MODE_BSS_STA== dmac_vap_get_bss_type(pst_vap))
        {
            /* STA模式，继承事件，并且修改事件头 */
            FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_STA);
        }

        dmac_vap_linkloss_clean(pst_dmac_vap);

        pst_wlan_rx = (dmac_wlan_drx_event_stru *)(pst_event->auc_event_data);
        pst_wlan_rx->pst_netbuf    = oal_netbuf_peek(pst_netbuf_header);
        pst_wlan_rx->us_netbuf_num = (oal_uint16)oal_netbuf_get_buf_num(pst_netbuf_header);

        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dispatch to hmac.}\r\n");
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PREPARE_EVENT);

        /* 分发事件 */
        ul_rslt = frw_event_dispatch_event(pst_event_mem);
        if(ul_rslt != OAL_SUCC)
        {
             OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_mgmt_event::frw_event_dispatch_event fail[%d].}", ul_rslt);
             dmac_rx_free_netbuf_list(pst_netbuf_header, &pst_first_buf, (oal_uint16)oal_netbuf_get_buf_num(pst_netbuf_header));
        }


        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_END);
#ifdef _PRE_WLAN_PROFLING_MIPS
        oal_profiling_stop_rx_save();
#endif
    }
    else    /* 管理帧的处理 */
    {
        /* 此处while作用:处理管理帧丢中断 */
        while (OAL_FALSE == oal_netbuf_list_empty(pst_netbuf_header))
        {
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_mgmt_mpdu_num_cnt, 1);
            pst_netbuf = oal_netbuf_delist(pst_netbuf_header);
            if (OAL_PTR_NULL == pst_netbuf)
            {
                OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_mgmt_event::pst_netbuf null.}");
                return;
            }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);
#endif
            /* 调用管理帧接口 */
            ul_rslt = dmac_rx_process_mgmt(pst_event_mem, pst_event_hdr, pst_device, pst_netbuf);
            if (ul_rslt != OAL_SUCC)
            {
//                OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dmac_rx_process_mgmt failed[%d].", ul_rslt);
                OAL_IO_PRINT("\r\n dmac_rx_process_data_event::dmac_rx_process_mgmt failed[%d].\r\n", ul_rslt);
                oal_netbuf_free(pst_netbuf);
                DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_mgmt_abnormal_dropped, 1);
            }
        }
    }

}
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
#endif

/*****************************************************************************
 函 数 名  : dmac_rx_compare_frame_type_and_rx_queue
 功能描述  : 比较帧类型与接收队列号
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月22日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_compare_frametype_and_rxq(
                oal_uint8                           uc_frametype,
                hal_rx_dscr_queue_id_enum_uint8     en_q,
                dmac_rx_ctl_stru                   *pst_cb_ctrl,
                oal_netbuf_stru                    *pst_curr_netbuf)
#else
OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_compare_frametype_and_rxq(
                oal_uint8                           uc_frametype,
                hal_rx_dscr_queue_id_enum_uint8     en_q)
#endif
{
#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    oal_uint8                    *puc_payload;
    mac_ieee80211_frame_stru     *pst_frame_hdr;
#endif

    /* 数据帧 上报的队列是高优先级队列，异常 */
    if (WLAN_FC0_TYPE_DATA == uc_frametype && HAL_RX_DSCR_HIGH_PRI_QUEUE == en_q)
    {
        OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_compare_frametype_and_rxq::data frame, but hi rx q.}");
    }
    else if (WLAN_FC0_TYPE_DATA != uc_frametype && HAL_RX_DSCR_NORMAL_PRI_QUEUE == en_q)
    {
        OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_compare_frametype_and_rxq::mgmt frame, but normal rx q.}");
    }
    else
    {
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    puc_payload = MAC_GET_RX_PAYLOAD_ADDR(&(pst_cb_ctrl->st_rx_info), pst_curr_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info));

    if (OAL_SWITCH_ON == oam_report_data_get_global_switch(OAM_OTA_FRAME_DIRECTION_TYPE_TX))
    {
        oam_report_80211_frame(BROADCAST_MACADDR,
                               (oal_uint8 *)(pst_frame_hdr),
                               MAC_GET_RX_CB_MAC_HEADER_LEN(&(pst_cb_ctrl->st_rx_info)),
                               puc_payload,
                               pst_cb_ctrl->st_rx_info.us_frame_len,
                               OAM_OTA_FRAME_DIRECTION_TYPE_TX);

        if (OAL_SUCC != oam_report_netbuf_cb(BROADCAST_MACADDR, (oal_uint8 *)pst_cb_ctrl, OAM_OTA_TYPE_RX_DMAC_CB))
        {
            OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_compare_frametype_and_rxq::oam_report_netbuf_cb return err: 0x%x.}\r\n");
            return OAL_FAIL;
        }
    }
#endif

    return OAL_FAIL;
}


/*****************************************************************************
 函 数 名  : dmac_rx_process_data_event
 功能描述  : DMAC模块下，处理接收到帧的事件的入口函数，包括管理帧和数据帧
 输入参数  : 指向事件结构体的指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
#endif

oal_uint32  dmac_rx_process_data_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    hal_wlan_rx_event_stru             *pst_wlan_rx_event;
    hal_to_dmac_device_stru            *pst_device;
    oal_uint16                          us_dscr_num;                    /* 存储中断上来的描述符个数 */
    oal_netbuf_head_stru                st_netbuf_header;               /* 存储传给HMAC模块sk_buf链表的header指针 */
    oal_netbuf_stru                    *pst_curr_netbuf;                /* 存储正在处理的SK_BUF */
    dmac_rx_ctl_stru                   *pst_cb_ctrl;                    /* 指向SK_BUF的cb字段的指针 */
    mac_vap_stru                       *pst_vap          = OAL_PTR_NULL;
    oal_uint8                           uc_vap_id        = 0xFF;        /* 保存本次处理的VAP ID */
    dmac_rx_frame_ctrl_enum_uint8       en_frame_ctrl    = DMAC_RX_FRAME_CTRL_BUTT;
    oal_uint32                          ul_netbuf_index;
    oal_netbuf_stru                    *pst_netbuf = OAL_PTR_NULL;
    hal_rx_dscr_queue_id_enum_uint8     en_dscr_queue_id;
    oal_uint32                          ul_rslt;
    oal_uint8                           uc_frame_type;
    oal_dlist_head_stru                *pst_rx_isr_list;
    hal_hw_rx_dscr_info_stru           *pst_rx_isr_info;
    mac_ieee80211_frame_stru           *pst_frame_hdr;
    dmac_vap_stru                      *pst_dmac_vap;
    oal_uint8                           uc_data_type;
    mac_rx_ctl_stru                     *pst_rx_info;
#if defined (_PRE_WLAN_FEATURE_BTCOEX) || defined (_PRE_WLAN_FEATURE_DBAC)
    mac_device_stru                    *pst_mac_device;
#endif

    /* 51 暂时取消该轨迹追踪DEBUG, wwx293928 */
#if (_PRE_PRODUCT_ID_HI1151 != _PRE_PRODUCT_ID)
#ifdef _PRE_DEBUG_MODE
    oal_uint32                          ul_profingling_time1;
    oal_uint32                          ul_profingling_time2;

    ul_profingling_time1 = oal_5115timer_get_10ns();
#endif
#endif

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_DMAC_START);
    //OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_START);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件头和事件结构体指针 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_wlan_rx_event       = (hal_wlan_rx_event_stru *)(pst_event->auc_event_data);
    pst_device              = pst_wlan_rx_event->pst_hal_device;

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_event::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*常收模式处理, 避免影响51常收 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    if((HAL_ALWAYS_RX_DISABLE != pst_device->bit_al_rx_flag))
    {
        OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_event:: always rx data process already done in isr.}");
        return OAL_SUCC;
    }
#endif
#endif

    /* 获取产生本次事件RX QUEUE ID */
    en_dscr_queue_id = (FRW_EVENT_TYPE_WLAN_DRX == pst_event_hdr->en_type) ? HAL_RX_DSCR_NORMAL_PRI_QUEUE : HAL_RX_DSCR_HIGH_PRI_QUEUE;

    /* 初始化netbuf链表的头 */
    oal_netbuf_list_head_init(&st_netbuf_header);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 数据帧使用描述符链表进行乒乓操作 */
    if (FRW_EVENT_TYPE_WLAN_DRX == pst_event_hdr->en_type)
    {

        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_START);

        pst_wlan_rx_event->us_dscr_num = 0;

        /*切换Ping-pong链表时需要锁住Mac rx中断*/
        dmac_rx_pingpong_list_lock(pst_device);
        /* 获取需要处理的链表 */
        pst_rx_isr_list = &(pst_device->ast_rx_isr_info_list[pst_device->uc_current_rx_list_index]);

        /* 更换将存储接收中断信息的链表 */
        pst_device->uc_current_rx_list_index = (pst_device->uc_current_rx_list_index + 1) & HAL_HW_MAX_RX_DSCR_LIST_IDX;

        dmac_rx_pingpong_list_unlock(pst_device);
        while (!oal_dlist_is_empty(pst_rx_isr_list))
        {
            pst_rx_isr_info = (hal_hw_rx_dscr_info_stru *)oal_dlist_delete_head(pst_rx_isr_list);

            /* 更新本次中断需要处理的描述符的信息 */
            //pst_wlan_rx_event->pul_base_dscr = pst_rx_isr_info->pul_base_dscr;
            pst_wlan_rx_event->us_dscr_num  += pst_rx_isr_info->us_dscr_num;
            OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_GET_INTR_INFO_FROM_LIST);

            /* 将需要处理的描述符从描述符链表中摘取出来，并且将描述符归还到描述符链表 */
            ul_rslt = dmac_rx_get_dscr_list(pst_device,
                                            pst_rx_isr_info,
                                            pst_event,
                                            &st_netbuf_header);
            OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_GET_DSCR_AND_RET_BACK);

            /* 释放本次描述符的节点信息 */
            hal_free_rx_isr_info(pst_device, pst_rx_isr_info);

            if (oal_netbuf_list_empty(&st_netbuf_header) && (OAL_SUCC != ul_rslt))
            {
                /* 释放所有描述符节点信息 */
                hal_free_rx_isr_list(pst_device, pst_rx_isr_list);
                OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_ppdu_dropped, 1);
                DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ppdu_dropped, 1);

                return ul_rslt;
            }
        }
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_INTR_LIST_OVER);

    }
    else
    {
        hal_hw_rx_dscr_info_stru    st_rx_isr_info;
        st_rx_isr_info.uc_queue_id    = en_dscr_queue_id;
        st_rx_isr_info.uc_channel_num = pst_wlan_rx_event->uc_channel_num;
        st_rx_isr_info.us_dscr_num    = pst_wlan_rx_event->us_dscr_num;
        st_rx_isr_info.pul_base_dscr  = pst_wlan_rx_event->pul_base_dscr;

        /* 将需要处理的描述符从描述符链表中摘取出来，并且将描述符归还到描述符链表 */
        ul_rslt = dmac_rx_get_dscr_list(pst_device, &st_rx_isr_info, pst_event, &st_netbuf_header);
        if (oal_netbuf_list_empty(&st_netbuf_header) && (OAL_SUCC != ul_rslt))
        {
            OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dmac_rx_get_dscr_list failed[%d].}", ul_rslt);

            OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_ppdu_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ppdu_dropped, 1);
            return ul_rslt;
        }
    }

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_DMAC_GET_CB_LIST);
    //OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_GET_CB_LIST);

    /* 更新接收的描述符的个数，在dmac_rx_get_dscr_list函数中，有对丢中断的处理 */
    us_dscr_num = pst_wlan_rx_event->us_dscr_num;

    /* 循环处理每一个MPDU */
    while (0 != us_dscr_num)
    {
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_START);
        pst_curr_netbuf = oal_netbuf_peek(&st_netbuf_header);
        if (OAL_PTR_NULL == pst_curr_netbuf)
        {
            OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::pst_curr_netbuf null.}");

            OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_abnormal_cnt, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);
            break;
        }

        OAL_MEM_NETBUF_TRACE(pst_curr_netbuf, OAL_TRUE);

        /* 获取每一个MPDU的控制信息 */
        pst_cb_ctrl = (dmac_rx_ctl_stru*)oal_netbuf_cb(pst_curr_netbuf);

        pst_rx_info = &(pst_cb_ctrl->st_rx_info);

        /* 硬件上报的NUM RX buffers for current MPDU等于0的异常处理 */
        if (0 == pst_rx_info->bit_buff_nums)
        {
            /* 释放后续所有的netbuf */
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, us_dscr_num);
            OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_abnormal_cnt, 1);

            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);

            OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event:: 0 == pst_cb_ctrl->st_rx_info.bit_buff_nums");
            break;
        }

        /* 硬件上报的RX Frame Length长度的异常处理 */
        if (OAL_FALSE == pst_rx_info->bit_amsdu_enable)
        {
        #ifdef _PRE_WLAN_HW_TEST
            /* 常收流程仪器发包为大包 */
            if (HAL_ALWAYS_RX_RESERVED == pst_device->bit_al_rx_flag)
            {
                if (pst_rx_info->us_frame_len > HAL_AL_RX_FRAME_LEN)
                {
                    /* 释放当前MPDU的内存 */
                    us_dscr_num -= pst_cb_ctrl->st_rx_info.bit_buff_nums;
                    OAM_ERROR_LOG2(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::non_amsdu mpdu \
                                   too long! mpdu_len=[%d], mpdu_len_limit=[%d].}", pst_rx_info->us_frame_len,
                                   HAL_AL_RX_FRAME_LEN);

                    dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
                    DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);

                    continue;
                }
            }
            else
        #endif
            {
                if (pst_rx_info->us_frame_len > WLAN_MAX_NETBUF_SIZE)
                {
                    /* 释放当前MPDU的内存 */
                    us_dscr_num -= pst_cb_ctrl->st_rx_info.bit_buff_nums;
                    OAM_ERROR_LOG2(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::non_amsdu mpdu \
                                   too long! mpdu_len=[%d], mpdu_len_limit=[%d].}", pst_rx_info->us_frame_len,
                                   WLAN_MAX_NETBUF_SIZE);

                    dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
                    DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);

                    continue;
                }
            }
        }

    #ifdef _PRE_WLAN_HW_TEST
        if (HAL_ALWAYS_RX_DISABLE == pst_device->bit_al_rx_flag)
    #endif
        {
            /* FCS错误的帧 硬件回填的接收描述符无意义，第一时间drop */
            if (HAL_RX_FCS_ERROR == pst_cb_ctrl->st_rx_status.bit_dscr_status)
            {
                /* 释放当前MPDU的内存 */
                us_dscr_num -= pst_rx_info->bit_buff_nums;
                OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event:: HAL_RX_FCS_ERROR == pst_cb_ctrl->st_rx_status.bit_dscr_status");
                dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);

                continue;
            }
        }

        pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(pst_rx_info);
        uc_frame_type = mac_get_frame_type((oal_uint8 *)pst_frame_hdr);

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
        ul_rslt = dmac_rx_compare_frametype_and_rxq(uc_frame_type, en_dscr_queue_id, pst_cb_ctrl, pst_curr_netbuf);
#else
        ul_rslt = dmac_rx_compare_frametype_and_rxq(uc_frame_type, en_dscr_queue_id);
#endif
        if (OAL_SUCC != ul_rslt)
        {
            /* 释放当前MPDU的内存 */
            us_dscr_num -= pst_rx_info->bit_buff_nums;
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event:: dmac_rx_compare_frametype_and_rxq fail[%u]", ul_rslt);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);
            continue;
        }
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_FRAME_RXQ);

        /* 检测接收到的MPDU异常 */
        ul_rslt = dmac_rx_filter_mpdu(pst_cb_ctrl, us_dscr_num);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dmac_rx_filter_mpdu failed[%d].", ul_rslt);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, us_dscr_num);

            /* 释放后续所有的netbuf */
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, us_dscr_num);
            OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_abnormal_cnt, 1);

            break;
        }
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_CB_CHECK);

    #ifdef _PRE_WLAN_CHIP_TEST_ALG
        dmac_alg_rx_event_notify(uc_vap_id, pst_curr_netbuf, pst_cb_ctrl);
    #endif
        /* 此处的vap id为hal层的vap id */
        uc_vap_id = pst_rx_info->bit_vap_id;

        ul_rslt = dmac_rx_get_vap(pst_device, uc_vap_id, en_dscr_queue_id, &pst_vap);
        if (OAL_SUCC != ul_rslt)
        {
            //OAM_INFO_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dmac_rx_get_vap ul_rslt=%d.}", ul_rslt);

            /* 释放当前MPDU占用的netbuf */
            us_dscr_num -= pst_rx_info->bit_buff_nums;
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
            OAM_STAT_VAP_INCR(0, rx_abnormal_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);
            continue;
        }

        if (WLAN_DATA_BASICTYPE == mac_frame_get_type_value((oal_uint8 *)pst_frame_hdr) &&
             WLAN_NULL_FRAME    != mac_frame_get_subtype_value((oal_uint8 *)pst_frame_hdr))
        {

            /* 维测，输出一个关键帧打印. DBAC场景下标记收到VIP帧 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            uc_data_type = mac_get_data_type_from_80211(pst_curr_netbuf, pst_rx_info->uc_mac_header_len);
            if(MAC_DATA_DHCP == uc_data_type || MAC_DATA_EAPOL == uc_data_type) /* 51 arp帧太多容易引起刷屏打印，wapi帧暂时不考虑 */
#else
            uc_data_type = mac_get_data_type(pst_curr_netbuf);
            if((uc_data_type <= MAC_DATA_VIP) && (uc_data_type != MAC_DATA_ARP_REQ))  /* arp_req大多为转发帧，容易引起日志刷屏 */
#endif
            {
                OAM_WARNING_LOG4(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_rx_process_data_event::rx datatype=%u, len=%u}[0:dhcp 1:arp_req 2:arp_rsp 3:eapol] from XX:XX:XX:XX:%x:%x",uc_data_type, pst_cb_ctrl->st_rx_info.us_frame_len, pst_frame_hdr->auc_address2[4], pst_frame_hdr->auc_address2[5]);
                if((MAC_DATA_EAPOL == uc_data_type) && (OAL_EAPOL_TYPE_KEY == mac_get_eapol_type(pst_curr_netbuf)))
                {
                    /*lint -e666*/
                    OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_rx_process_data_event::rx eapol, info is %x }", OAL_NET2HOST_SHORT(mac_get_eapol_keyinfo(pst_curr_netbuf)));
                    /*lint +e666*/
                }
            }
#if defined (_PRE_WLAN_FEATURE_BTCOEX) || defined(_PRE_WLAN_FEATURE_DBAC)
            pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
            if( pst_mac_device != OAL_PTR_NULL)
            {

#ifdef _PRE_WLAN_FEATURE_BTCOEX
                dmac_btcoex_release_rx_prot(pst_mac_device, uc_data_type);
#endif
#if defined(_PRE_WLAN_FEATURE_DBAC) && (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
                /* VIP帧优化主要是针对STA模式，1151 DBAC不需要 */
                if (mac_is_dbac_running(pst_mac_device) &&
                    (pst_device->uc_current_chan_number == pst_vap->st_channel.uc_chan_number) &&
                    (MAC_DATA_DHCP == uc_data_type || MAC_DATA_EAPOL == uc_data_type))
                {
                    pst_mac_device->en_dbac_has_vip_frame = OAL_TRUE;
                }
#endif
            } // ( pst_mac_device != OAL_PTR_NULL)
#endif //(_PRE_WLAN_FEATURE_BTCOEX) || defined(_PRE_WLAN_FEATURE_DBAC)

        }

        /* 记录到cb中 */
        pst_rx_info->uc_mac_vap_id = pst_vap->uc_vap_id;
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_GET_VAP_ID);

#ifdef _PRE_WLAN_DFT_DUMP_FRAME

        /* DTS2015072003017维测，读到的硬件Beacon Interval寄存器值为0，硬件怀疑Beacon帧里的值为0 */
        /* 软件解析Beacon帧中的Beacon Interval，为0时打一个ERROR。 问题单关闭后可删除此维测 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        {
            oal_uint8   uc_sub_type;
            oal_uint8  *puc_frame_body;
            oal_uint16 *pus_bi;

            uc_sub_type = mac_get_frame_sub_type((oal_uint8 *)mac_get_rx_cb_mac_hdr(pst_rx_info));
            puc_frame_body = oal_netbuf_payload(pst_curr_netbuf);
            pus_bi = (oal_uint16 *)(puc_frame_body + 8); /* 偏移8字节tsf后是beacon interval */

            if ((WLAN_FC0_SUBTYPE_BEACON == uc_sub_type || WLAN_FC0_SUBTYPE_PROBE_RSP == uc_sub_type)
                 && (0 == *pus_bi))
            {
                OAM_ERROR_LOG1(0, OAM_SF_ANY, "DEBUG: rx beacon/probe rsp Beacon Interval:%d", *pus_bi);
            }
        }
#else /* AP模式下此处会收到很多不属于自己的广播帧，02管理帧维测不放在此处 */
        /* 上报帧和帧对应的CB字段到SDT */
        if ((FRW_EVENT_TYPE_WLAN_DRX != pst_event_hdr->en_type)||
            (OAL_SWITCH_ON == oam_report_data_get_global_switch(OAM_OTA_FRAME_DIRECTION_TYPE_RX)))
        {
            if (pst_cb_ctrl->st_rx_status.bit_dscr_status == HAL_RX_SUCCESS)
            {
                mac_rx_report_80211_frame((oal_uint8 *)pst_vap, (oal_uint8 *)(pst_rx_info), pst_curr_netbuf, OAM_OTA_TYPE_RX_DMAC_CB);
            }
        }
#endif /* #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) */
#endif /* #ifdef _PRE_WLAN_DFT_DUMP_FRAME */

        /* 放到其它位置统计 */
        //dmac_rx_vap_stat(pst_vap, &st_netbuf_header, pst_curr_netbuf, pst_cb_ctrl);

        en_frame_ctrl = dmac_rx_process_frame(pst_vap, pst_cb_ctrl, pst_curr_netbuf, &st_netbuf_header);

        if (DMAC_RX_FRAME_CTRL_DROP == en_frame_ctrl)
        {
            /* 释放当前MPDU的内存 */
            us_dscr_num -= pst_rx_info->bit_buff_nums;
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_dropped_misc, 1);
            continue;
        }
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_OVER);

#ifdef _PRE_WLAN_PERFORM_STAT
        /* 更新接收数据统计量 */
        dmac_stat_rx_thrpt(pst_event_hdr, pst_vap, pst_cb_ctrl);
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        if ((WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type) && (OAL_TRUE == pst_cb_ctrl->st_rx_status.bit_AMPDU))
        {
            dmac_btcoex_bt_low_rate_process(pst_vap, pst_device);
        }
#endif

#ifdef _PRE_WLAN_CHIP_TEST

        DMAC_CHIP_TEST_CALL(dmac_test_sch_stat_rx_mpdu_num(pst_event_hdr, pst_vap, pst_cb_ctrl));

        DMAC_CHIP_TEST_CALL(dmac_test_sch_stat_rx_sta_num(pst_event_hdr, pst_vap, pst_cb_ctrl));

#endif

        /* 将该帧从队列头摘除，放入到队列尾，交与HMAC处理 */
        for (ul_netbuf_index = pst_rx_info->bit_buff_nums; ul_netbuf_index > 0; ul_netbuf_index--)
        {
            pst_netbuf = oal_netbuf_delist(&st_netbuf_header);

            OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_FALSE);
            oal_netbuf_add_to_list_tail(pst_netbuf, &st_netbuf_header);
        }

        /* 更新未处理的描述符的个数 */
        us_dscr_num     -= pst_rx_info->bit_buff_nums;

        /* 统计接收的MPDU个数 */
        dmac_rx_update_aggr_mib(pst_vap, 1);

        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_MAKE_NETBUF_LIST);
    }

    //OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_DMAC_HANDLE_MPDU);
    //OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_MPDU);

    if (OAL_FALSE == oal_netbuf_list_empty(&st_netbuf_header))
    {
        dmac_rx_process_data_mgmt_event(pst_event_mem, &st_netbuf_header, pst_vap, pst_netbuf);
    }

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_DMAC_END);
    //OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_END);

    /* 51 暂时取消该轨迹追踪DEBUG */
#if (_PRE_PRODUCT_ID_HI1151 != _PRE_PRODUCT_ID)
#ifdef _PRE_DEBUG_MODE
    ul_profingling_time2 = oal_5115timer_get_10ns();

    pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_arrive_time = ul_profingling_time1;
    pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_handle_time = ul_profingling_time1 - ul_profingling_time2;
#endif
#endif
    return OAL_SUCC;
}

#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
#endif

/*****************************************************************************
 函 数 名  : dmac_rx_invalid_vap_event
 功能描述  : 硬件上报的VAP不合理，释放对应的内存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rx_invalid_vap_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    hal_wlan_rx_event_stru             *pst_wlan_rx_event;
    hal_to_dmac_device_stru            *pst_device;
    oal_uint32                         *pul_base_dscr;
    oal_uint32                         *pul_curr_dscr;
    oal_uint32                         *pul_next_dscr;
    hal_rx_dscr_stru                   *pst_hal_to_dmac_dscr;
    oal_uint16                          us_dscr_num;            /* 存储中断上来的描述符个数 */
    hal_rx_dscr_queue_id_enum_uint8     en_dscr_queue_id;
#ifdef _PRE_DEBUG_MODE
    oal_uint32                          ul_rx_dscr_len;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_invalid_vap_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_wlan_rx_event       = (hal_wlan_rx_event_stru *)(pst_event->auc_event_data);

    pst_device              = pst_wlan_rx_event->pst_hal_device;
    pul_base_dscr           = pst_wlan_rx_event->pul_base_dscr;
    en_dscr_queue_id        = pst_wlan_rx_event->uc_queue_id;
    us_dscr_num             = pst_wlan_rx_event->us_dscr_num;

    pul_curr_dscr = pul_base_dscr;

    while(us_dscr_num)
    {
        /* 获得下一个需要处理的描述符 */
        pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;
        pul_next_dscr        = HAL_RX_DSCR_GET_SW_ADDR(oal_get_virt_addr(pst_hal_to_dmac_dscr->pul_next_rx_dscr));

    #ifdef _PRE_DEBUG_MODE
        hal_rx_get_size_dscr(pst_device, &ul_rx_dscr_len);
        oam_report_dscr(BROADCAST_MACADDR, (oal_uint8 *)pul_curr_dscr, (oal_uint16)ul_rx_dscr_len, OAM_OTA_TYPE_RX_DSCR);
    #endif

        /* 归还不合理的描述符 */
        hal_rx_sync_invalid_dscr(pst_device, pul_curr_dscr, en_dscr_queue_id);

        pul_curr_dscr = pul_next_dscr;

        us_dscr_num--;
    }

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 函 数 名  : dmac_error_irq_resume_dscr_queue
 功能描述  : 将描述符队列从NULL状态恢复到正常状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月27日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_error_irq_resume_dscr_queue(
                hal_error_irq_event_stru           *pst_error_irq_event,
                hal_rx_dscr_queue_id_enum_uint8     en_queue_num)
{
    hal_to_dmac_device_stru            *pst_hal_device;
    oal_uint16                          us_netbuf_free_cnt;     /* netbuf内存池的空闲netbuf的数目 */
    oal_uint16                          us_dscr_free_cnt;       /* 共享描述符内存池中空闲的描述符的个数 */
    oal_uint16                          us_actual_free_cnt;     /* 保存netbuf和dscr的较小的值 */
    oal_uint16                          us_curr_dscr_num;       /* 当前的描述符的个数 */
    oal_uint16                          us_target_num;          /* 实际可以补充的描述符的个数 */

    pst_hal_device = pst_error_irq_event->pst_hal_device;

    /* 暂停硬件 */
    hal_set_machw_tx_suspend(pst_hal_device);

    /* disable PHY and PA */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    oal_mem_get_free_count(OAL_MEM_POOL_ID_NETBUF, 1, &us_netbuf_free_cnt);     /* 1代表第二个子池 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    oal_mem_get_free_count(OAL_MEM_POOL_ID_TX_DSCR_1, 0, &us_dscr_free_cnt);  /* 0代表第一个子池 */
#else
    oal_mem_get_free_count(OAL_MEM_POOL_ID_SHARED_DSCR, 0, &us_dscr_free_cnt);  /* 0代表第一个子池 */
#endif
    /* 获取内存器的空闲个数 */
    us_actual_free_cnt = (us_netbuf_free_cnt > us_dscr_free_cnt) ? us_dscr_free_cnt : us_netbuf_free_cnt;
    if (0 == us_actual_free_cnt)    /* 无可使用空间 */
    {
        return;
    }

    /* 获取能补充的描述符的个数 */
    us_curr_dscr_num = pst_hal_device->ast_rx_dscr_queue[en_queue_num].us_element_cnt;

    if ((us_actual_free_cnt + us_curr_dscr_num) < HAL_NORMAL_RX_MAX_BUFFS)
    {
        us_target_num = us_actual_free_cnt;
    }
    else
    {
        us_target_num = HAL_NORMAL_RX_MAX_BUFFS - us_curr_dscr_num;
    }

    /* 添加描述符到描述符队列 */
    while (0 != us_target_num)
    {
        hal_rx_add_dscr(pst_hal_device, en_queue_num);
        us_target_num--;
    }

    /* enable PHY and PA */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    /* 恢复硬件 */
    hal_set_machw_tx_resume(pst_hal_device);
}
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
/*****************************************************************************
 函 数 名  : dmac_rx_resume_dscr_queue
 功能描述  : 出现qemty后，1102需要重新申请描述符，挂在原有队列的后面，
             同时将新增的描述符的第一个挂给mac
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_rx_resume_dscr_queue(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    hal_to_dmac_device_stru        *pst_hal_device;
    frw_event_type_enum_uint8       en_event_type;
    hal_rx_dscr_queue_id_enum_uint8 en_queue_num;
    oal_uint32                      ul_event_succ;
    hal_rx_dscr_queue_header_stru  *pst_rx_dscr_queue;

    pst_hal_device = pst_mac_dev->pst_device_stru;
    if (OAL_PTR_NULL ==  pst_hal_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::pst_hal_device null.}");
        return;
    }

    /* 1.1 获取需要恢复的队列号 */
    en_queue_num = (oal_uint8)ul_param;
    if (en_queue_num >= HAL_RX_QUEUE_NUM)
    {
        OAM_ERROR_LOG1(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::en_queue_num[%d] error.}", en_queue_num);
        return;
    }

    /* 2.1 diable MAC/PHY */
    /*hal_disable_machw_phy_and_pa(pst_hal_device);*/

    /* 3.1 清空接收残留事件 */
    en_event_type = (HAL_RX_DSCR_HIGH_PRI_QUEUE == en_queue_num) ? FRW_EVENT_TYPE_WLAN_CRX : FRW_EVENT_TYPE_WLAN_DRX;
    /* TBD 目前1102的管理帧有可能被mac放在普通优先级队列中上报给驱动，这就要求驱动在入事件队列之前做特殊的过滤操作。
           这部分逻辑暂时没有实现，为了防止4.1操作时，head指针还在事件队列中，因此这里需要将普通优先级事件队列及
           高优先级事件队列都flush掉 */
    ul_event_succ = frw_event_flush_event_queue(en_event_type);

    /* 4.1 将接收描述符重新挂给mac，如果描述符队列为空，需要重新申请 */
    pst_rx_dscr_queue = &(pst_hal_device->ast_rx_dscr_queue[en_queue_num]);
    oal_irq_disable();
    hal_rx_add_dscr(pst_hal_device, en_queue_num, 1);
    /*上半部补充描述符不配置寄存器，统一在Q-EMPTY时重新配置，保证唯一,配置过程中可以不锁PA*/
    if(0 != pst_rx_dscr_queue->us_element_cnt)
    {
        if(OAL_TRUE != hal_set_machw_rx_buff_addr_sync(pst_hal_device,
                                (oal_uint32)pst_rx_dscr_queue->pul_element_head,
                                en_queue_num))
        {
            /* DTS2015071600780 如果收到短帧，硬件可能已经读走从而返回错误，不是问题。*/
            OAM_WARNING_LOG1(0, OAM_SF_RX,"[ERROR]Q-EMPTY[%d] but machw reg still not zero!\r\n",en_queue_num);
        }
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{Q-EMPTY[%d] and did not catch any buffs!}",en_queue_num);
    }
    oal_irq_enable();

    OAM_INFO_LOG3(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue[%d]::OK [%u] flushed & [%u] left.}",
                   en_queue_num, ul_event_succ, pst_rx_dscr_queue->us_element_cnt);

    /* 5.1 enable MAC/PHY */
    /*hal_enable_machw_phy_and_pa(pst_hal_device);*/

}
#if 0
/*****************************************************************************
 函 数 名  : dmac_rx_resume_dscr_queue_all
 功能描述  : 出现qemty后，1102需要重新申请描述符，挂在原有队列的后面，
             同时将新增的描述符的第一个挂给mac
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_rx_resume_dscr_queue_all(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    dmac_rx_resume_dscr_queue(pst_mac_dev, 0);
    dmac_rx_resume_dscr_queue(pst_mac_dev, 1);
    dmac_rx_resume_dscr_queue(pst_mac_dev, 2);
}
#endif
#else
/*****************************************************************************
 函 数 名  : dmac_rx_resume_dscr_queue
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月14日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_rx_resume_dscr_queue(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    hal_to_dmac_device_stru        *pst_hal_device;
    hal_rx_dscr_queue_header_stru  *pst_rx_dscr_queue;
    dmac_rx_ctl_stru               *pst_cb_ctrl;                    /* 填写netbuf的cb字段使用 */
    oal_netbuf_stru                *pst_netbuf = OAL_PTR_NULL;      /* 指向每一个描述符对应的netbuf */
    oal_uint32                     *pul_curr_dscr;                  /* 正在处理的描述符 */
    oal_uint32                     *pul_next_dscr;
    hal_rx_dscr_stru               *pst_hal_to_dmac_dscr;
    oal_uint32                      ul_dscr_idx;
    frw_event_type_enum_uint8       en_event_type;
    hal_rx_dscr_queue_id_enum_uint8 en_queue_num;
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
    oal_uint16                      aus_dscr_num[HAL_RX_DSCR_QUEUE_ID_BUTT] = {HAL_NORMAL_RX_MAX_BUFFS, HAL_HIGH_RX_MAX_BUFFS, HAL_SMALL_RX_MAX_BUFFS};
#else
    oal_uint16                      aus_dscr_num[HAL_RX_DSCR_QUEUE_ID_BUTT] = {HAL_NORMAL_RX_MAX_BUFFS, HAL_HIGH_RX_MAX_BUFFS};
#endif
#if 0
    if (0 == pst_mac_dev->uc_resume_qempty_flag)
    {
        /* qempty flag设置为0时，不使能qempty恢复 */
        return;
    }
#endif
    pst_hal_device = pst_mac_dev->pst_device_stru;

    /* 获取需要恢复的队列号 */
    en_queue_num = (oal_uint8)ul_param;
    if (en_queue_num >= HAL_RX_QUEUE_NUM)
    {
        OAM_ERROR_LOG1(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::en_queue_num[%d] error.}", en_queue_num);
        return;
    }

    /* diable MAC/PHY */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    /* 处理接收事件 */
    en_event_type = (HAL_RX_DSCR_NORMAL_PRI_QUEUE == en_queue_num) ? FRW_EVENT_TYPE_WLAN_DRX : FRW_EVENT_TYPE_WLAN_CRX;
    frw_event_flush_event_queue(en_event_type);

    /* 接收队列恢复 */
    pst_rx_dscr_queue = &(pst_hal_device->ast_rx_dscr_queue[en_queue_num]);
    if (OAL_PTR_NULL ==  pst_rx_dscr_queue)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::pst_rx_dscr_queue null.}");
        return;
    }
    pul_curr_dscr = pst_rx_dscr_queue->pul_element_head;

    oal_irq_disable();
    for (ul_dscr_idx = 0; ul_dscr_idx < aus_dscr_num[en_queue_num]; ul_dscr_idx++)
    {
        if (OAL_PTR_NULL == pul_curr_dscr)
        {
            OAM_ERROR_LOG2(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::pul_curr_dscr null, ul_dscr_idx=%d en_queue_num=%d.}",
                           ul_dscr_idx, en_queue_num);
            oal_irq_enable();
            return;
        }

        /* 获得下一个需要处理的描述符 */
        pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;
        pul_next_dscr        = HAL_RX_DSCR_GET_SW_ADDR(oal_get_virt_addr(pst_hal_to_dmac_dscr->pul_next_rx_dscr));

        /* 获取描述符对应的netbuf */
        hal_rx_get_netbuffer_addr_dscr(pst_hal_device, pul_curr_dscr, &pst_netbuf);

        pst_cb_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

        /* 获取描述符个字段信息，并将其加到netbuf的cb字段中 */
        dmac_rx_get_dscr_info(pst_hal_device, pul_curr_dscr, pst_cb_ctrl);

        if (HAL_RX_NEW == pst_cb_ctrl->st_rx_status.bit_dscr_status)
        {
            pul_curr_dscr = pul_next_dscr;

            continue;
        }

        hal_rx_sync_invalid_dscr(pst_hal_device, pul_curr_dscr, en_queue_num);

        pul_curr_dscr = pul_next_dscr;
    }
    oal_irq_enable();

    /* 接收描述符重新挂给MAC */
    hal_set_machw_rx_buff_addr(pst_hal_device, (oal_uint32)(pst_rx_dscr_queue->pul_element_head), en_queue_num);

    /* enable MAC/PHY */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    return;
}

#if 0
OAL_STATIC oal_void  dmac_rx_resume_dscr_queue_all(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    return;
}
#endif
#endif
/*****************************************************************************
 函 数 名  : dmac_log_txq_overrun
 功能描述  : 记录MAC上报发送队列满时的日志信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_log_txq_overrun(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    oal_uint32                     ul_tx_q_status;
    hal_tx_dscr_queue_header_stru *pst_tx_queue;
    oal_uint32                     ul_value;
    hal_tx_queue_type_enum_uint8   en_queue;
    hal_tx_dscr_stru              *pst_dscr;
    oal_dlist_head_stru           *pst_pos;
    hal_to_dmac_device_stru       *pst_hal_device;
    oal_uint32                     ul_act_ppdu_cnt = 0;
    oal_uint32                     ul_rec_ppdu_cnt = 0;

    en_queue = (hal_tx_queue_type_enum_uint8)ul_param;

    if (OAL_PTR_NULL == pst_device || en_queue >= HAL_TX_QUEUE_BUTT)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_log_txq_overrun::invalid param.}");

        return;
    }

    pst_hal_device = pst_device->pst_device_stru;
    pst_tx_queue = &pst_hal_device->ast_tx_dscr_queue[en_queue];

    hal_get_tx_q_status(pst_hal_device, &ul_tx_q_status, en_queue);
    hal_get_all_tx_q_status(pst_hal_device, &ul_value);
    ul_rec_ppdu_cnt = pst_tx_queue->uc_ppdu_cnt;

    OAL_DLIST_SEARCH_FOR_EACH(pst_pos, &(pst_tx_queue->st_header))
    {
        pst_dscr = OAL_DLIST_GET_ENTRY(pst_pos, hal_tx_dscr_stru, st_entry);
        if(OAL_PTR_NULL != pst_dscr)
        {
            if (OAL_TRUE == pst_dscr->bit_is_first)
            {
                ul_act_ppdu_cnt++;
            }
            oam_report_dscr(BROADCAST_MACADDR, (oal_uint8*)pst_dscr, WLAN_MEM_SHARED_TX_DSCR_SIZE1, OAM_OTA_TYPE_TX_DSCR);
        }
    }

    OAM_ERROR_LOG4(0, OAM_SF_TX, "{dmac_log_txq_overrun::sw act ppdu_cnt=%d, sw record ppdu_cnt=%d, ul_tx_q_status=%d, ul_value=%d.}",
                   ul_act_ppdu_cnt, ul_rec_ppdu_cnt, ul_tx_q_status, ul_value);
}


OAL_STATIC oal_void dmac_dump_all_tx_dscr(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    oal_uint32                       ul_qnum;
    hal_tx_dscr_stru                *pst_dscr;
    oal_dlist_head_stru             *pst_pos;
    hal_to_dmac_device_stru         *pst_hal_device = pst_device->pst_device_stru;

    for(ul_qnum = 0; ul_qnum < HAL_TX_QUEUE_NUM; ul_qnum++)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_dump_all_tx_dscr::tx dscr dump. qnum[%d],ppducnt[%d]}",
                                        ul_qnum, pst_hal_device->ast_tx_dscr_queue[ul_qnum].uc_ppdu_cnt);

        OAL_DLIST_SEARCH_FOR_EACH(pst_pos, &(pst_hal_device->ast_tx_dscr_queue[ul_qnum].st_header))
        {
            pst_dscr   = OAL_DLIST_GET_ENTRY(pst_pos, hal_tx_dscr_stru, st_entry);

            if(OAL_PTR_NULL != pst_dscr)
            {
                oam_report_dscr(BROADCAST_MACADDR,
                            (oal_uint8*)pst_dscr,
                            WLAN_MEM_SHARED_TX_DSCR_SIZE1,
                            OAM_OTA_TYPE_TX_DSCR);
            }
        }
    }
}
/*****************************************************************************
 函 数 名  : dmac_log_txq_overrun
 功能描述  : 记录MAC上报发送队列满时的日志信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月15日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_proc_rxbuf_too_small_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    pst_device->ul_rx_buf_too_small_show_counter++;
}
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 函 数 名  : dmac_proc_para_cfg_error
 功能描述  : 记录三类mac错误日志信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : d00262548
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_proc_rx_fsm_st_timeout_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    pst_device->ul_rx_fsm_st_timeout_show_counter++;
}
OAL_STATIC oal_void  dmac_proc_tx_fsm_st_timeout_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    pst_device->ul_tx_fsm_st_timeout_show_counter++;
}
OAL_STATIC oal_void  dmac_proc_beacon_miss_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    pst_device->ul_beacon_miss_show_counter++;
}
OAL_STATIC oal_void dmac_tx_dataflow_break_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    hal_to_dmac_device_stru *pst_hal_device = pst_device->pst_device_stru;
    mac_tx_dataflow_brk_bypass_struc *pst_brk_bypass = &(pst_device->st_dataflow_brk_bypass);
    oal_uint32 ul_tx_comp_cnt = 0;

    /* 每隔128个DataFlow Break的错误中断，比对当前的发送完成中断个数和之前记录的发送完成中断个数 */
    if(0 != ((++pst_brk_bypass->ul_tx_dataflow_brk_cnt) & ((1 << 7) - 1)))
    {
        return;
    }

    hal_get_irq_stat(pst_hal_device, (oal_uint8 *)&ul_tx_comp_cnt, sizeof(ul_tx_comp_cnt), HAL_IRQ_TX_COMP_CNT);
    if(pst_brk_bypass->ul_last_tx_complete_isr_cnt == ul_tx_comp_cnt)
    {
        dmac_reset_para_stru            st_reset_param;

        OAM_INFO_LOG1(0, OAM_SF_TX, "{dmac_tx_dataflow_break_error::No TX Complete irq between 128 dataflow break, CurTxCompCnt: %d", ul_tx_comp_cnt);

        /* 降低最大聚合个数 */
        if(OAL_TRUE == pst_brk_bypass->en_brk_limit_aggr_enable)
        {
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dataflow_break_error::Bypass Fail, CurTxCompCnt: %d", ul_tx_comp_cnt);
        }
        else
        {
            pst_brk_bypass->en_brk_limit_aggr_enable = OAL_TRUE;
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dataflow_break_error::Enable DataFlowBreak limit, CurTxCompCnt: %d", ul_tx_comp_cnt);
        }

        /* 初始化Mac逻辑 */
        OAL_MEMZERO(&st_reset_param, sizeof(st_reset_param));
        st_reset_param.uc_reset_type = HAL_RESET_HW_TYPE_MAC;
        dmac_reset_hw(pst_device, (oal_uint8 *)&st_reset_param);
    }

    /* 重置相关计数器 */
    pst_brk_bypass->ul_last_tx_complete_isr_cnt = ul_tx_comp_cnt;
}
#endif
#if 0
/*****************************************************************************
 函 数 名  : dmac_check_txq
 功能描述  : 检查硬件队列中的数据帧,如果有丢中断,软件处理该数据
 输入参数  : pst_dmac_vap
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月14日
    作    者   : wangweigang
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_check_txq(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    oal_uint8                uc_q_idx           = 0;
    hal_tx_dscr_stru        *pst_tx_dscr_first  = OAL_PTR_NULL;
    hal_to_dmac_device_stru *pst_hal_device     = OAL_PTR_NULL;
    oal_uint32               ul_txq_ptr_status  = 0;
    oal_uint32               ul_txq_reg_dscr    = 0;
    oal_uint32               ul_reg_addr        = 0;
    oal_uint32               ul_ret             = OAL_SUCC;
    oal_uint32               ul_time_start;
    oal_uint32               ul_time_end;
    oal_uint32               ul_time_delay;

    pst_hal_device = pst_mac_dev->pst_device_stru;

    for (uc_q_idx = 0; uc_q_idx <= HAL_TX_QUEUE_VI; uc_q_idx++)
    {
        /* 如果该发送队列没有数据,检查下一个队列 */
        if (pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt == 0)
        {
            continue;
        }

        /* 延时2ms,等待MAC刷新寄存器之后再读取 */
        ul_time_start = oal_5115timer_get_10ns();
        do
        {
            ul_time_end = oal_5115timer_get_10ns();
            if (ul_time_end < ul_time_start)
            {
                ul_time_delay = ul_time_start - ul_time_end;
            }
            else
            {
                ul_time_delay = ul_time_start + (0xFFFFFFFF - ul_time_end);
            }
        } while (ul_time_delay < MAX_DELAY_TIME);

        ul_reg_addr = (oal_uint32)(WITP_PA_AC_BK_FIRST_FRM_PTR_STATUS_REG + (uc_q_idx * 8));
        hal_reg_info(pst_hal_device, ul_reg_addr, &ul_txq_ptr_status);
        ul_txq_reg_dscr = (oal_uint32)OAL_PHY_TO_VIRT_ADDR(ul_txq_ptr_status);

        /* 取出该队列中的第一个描述符 */
        pst_tx_dscr_first  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header.pst_next, hal_tx_dscr_stru, st_entry);
        /* 如果丢中断了，则处理该ppdu */
        if (OAL_UNLIKELY((oal_uint32)pst_tx_dscr_first != ul_txq_reg_dscr))
        {
            OAM_WARNING_LOG2(0, OAM_SF_TX, "{dmac_check_txq::MAC loss tx complete irq, q_num[%d], dscr_addr[0x%x]}", pst_tx_dscr_first->uc_q_num, pst_tx_dscr_first);
            ul_ret = dmac_tx_complete_buff(pst_hal_device, pst_tx_dscr_first);
            if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
            {
                OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_check_txq::dmac_tx_complete failed[%d].", ul_ret);
            }
        }
    }
}
#endif

#if 0
/*****************************************************************************
 函 数 名  : dmac_mac_error_msg_report
 功能描述  : mac错误日志上报
 输入参数  : oal_uint8 uc_vap_id
             hal_mac_error_type_enum_uint8 en_error_id
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月27日,星期二
    作    者   : y00201072
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_mac_error_msg_report(oal_uint8 uc_vap_id, hal_mac_error_type_enum_uint8 en_error_id)
{
    mac_device_stru *pst_mac_device;
    mac_vap_stru    *pst_mac_vap;
    pst_mac_vap    = mac_res_get_mac_vap(uc_vap_id);

    if(OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_mac_error_msg_report::OAL_PTR_NULL == pst_mac_vap.}");
        return OAL_FAIL;
    }
    pst_mac_device = mac_res_get_dev((oal_uint32)pst_mac_vap->uc_device_id);

    if (HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL == en_error_id)
    {
        if ((pst_mac_device->ul_rx_buf_too_small_show_counter % 1000) != 1)
        {
            return OAL_SUCC;
        }

        OAM_WARNING_LOG1(0, OAM_SF_IRQ, "{dmac_mac_error_msg_report::error type[RXBUFF_LEN_TOO_SMALL] %d.}\r\n", pst_mac_device->ul_rx_buf_too_small_show_counter);
    }

    switch (en_error_id)
    {
        case HAL_MAC_ERROR_PARA_CFG_ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_PARA_CFG_ERR}\r\n");
            break;

        case HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL:  /* PHY解析异常时出现，软件无需处理 */
            //OAM_INFO_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL}\r\n");
            break;

        case HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND}\r\n");
            break;

        case HAL_MAC_ERROR_PHY_TRLR_TIME_OUT:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_PHY_TRLR_TIME_OUT}\r\n");
            break;

        case HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN:
            /* 1151因为预取PCIE延迟大，出现该错误正常；1102芯片上出现该错误需要定位
            PHY给的数据太快，MAC处理不过来，如果有问题会有TIMEOUT体现 */
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_PHY_RX_FIFO_OVERRUN}\r\n");
            break;

        case HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_TX_DATAFLOW_BREAK:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_DATAFLOW_BREAK}\r\n");
            break;

        case HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_RX_HANDLER_ST_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_HANDLER_ST_TIMEOUT}\r\n");
            break;


        case HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN:
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            /* 修改重传帧描述符的timestamp后，看是否还会出现该错误，不出现的话统一修改为ERROR级别 */
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN}\r\n");
#else /* DTS2014121503359问题单规避 */
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_INTR_FIFO_OVERRUN}\r\n");
#endif
            break;

        case HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN:
            /* 软件处理太慢引起的错误，造成丢中断，但是软件会将丢失的中断进行处理 */
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_RX_INTR_FIFO_OVERRUN}\r\n");
            break;

        case HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN:
            /* 软件处理太慢引起的错误，造成丢中断，但是软件会将丢失的中断进行处理 */
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN}\r\n");
            break;

        case HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY:
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY}\r\n");
#else
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY}\r\n");
#endif
            break;

        case HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY:
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY}\r\n");
#else
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY}\r\n");
#endif
            break;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        case HAL_MAC_ERROR_BUS_RLEN_ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_BUS_RLEN_ERR}\r\n");
            break;

        case HAL_MAC_ERROR_BUS_RADDR_ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_BUS_RADDR_ERR}\r\n");
            break;
#else /* DTS2014102206753/DTS2014112105106 软件规避 */
        case HAL_MAC_ERROR_BUS_RLEN_ERR:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_BUS_RLEN_ERR}\r\n");
            break;

        case HAL_MAC_ERROR_BUS_RADDR_ERR:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_BUS_RADDR_ERR}\r\n");
            break;
#endif

        case HAL_MAC_ERROR_BUS_WLEN_ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_BUS_WLEN_ERR}\r\n");
            break;

        case HAL_MAC_ERROR_BUS_WADDR_ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_BUS_WADDR_ERR}\r\n");
            break;

        case HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN}\r\n");
            break;

        case HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN}\r\n");
            break;

        case HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN}\r\n");
            break;

        case HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN}\r\n");
            break;

        case HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN}\r\n");
            break;

        case HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT:
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT}\r\n");
#else
            OAM_INFO_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT}\r\n");
#endif
            break;

        case HAL_MAC_ERROR_CCA_TIME_OUT:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_CCA_TIMEOUT}\r\n");
            break;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        case HAL_MAC_ERROR_DCOL_DATA_OVERLAP:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_DCOL_DATA_OVERLAP}\r\n");
            break;
#endif

        case HAL_MAC_ERROR_BEACON_MISS:
            /* 可能由于CCA TIMEOUT导致 Beacon帧无法发送 */
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_BEACON_MISS}\r\n");
            break;

        case HAL_MAC_ERROR_INTR_FIFO_UNEXPECTED_READ:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_INTR_FIFO_UNEXPECTED_READ}\r\n");
            break;

        case HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR:
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR}\r\n");
#else
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR}\r\n");
#endif
            break;

        case HAL_MAC_ERROR_RX_OVERLAP_ERR:
            /* MAC处理不过来, 可以自恢复，如果不可恢复会有TIMEOUT错误上报 */
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_RX_OVERLAP_ERR}\r\n");
            break;

        case HAL_MAC_ERROR_TX_ACBE_BACKOFF_TIMEOUT:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_ACBE_BACKOFF_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_TX_ACBK_BACKOFF_TIMEOUT:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_ACBK_BACKOFF_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_TX_ACVI_BACKOFF_TIMEOUT:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_ACVI_BACKOFF_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_TX_ACVO_BACKOFF_TIMEOUT:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_ACVO_BACKOFF_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_TX_HIPRI_BACKOFF_TIMEOUT:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_TX_HIPRI_BACKOFF_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_RX_SMALL_Q_EMPTY:
            OAM_WARNING_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_RX_SMALL_Q_EMPTY_TIMEOUT}\r\n");
            break;

        case HAL_MAC_ERROR_PARA_CFG_2ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_PARA_CFG_2ERR}\r\n");
            break;

        case HAL_MAC_ERROR_PARA_CFG_3ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_PARA_CFG_3ERR}\r\n");
            break;

        case HAL_MAC_ERROR_EDCA_ST_TIMEOUT:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::HAL_MAC_ERROR_EDCA_ST_TIMEOUT}\r\n");
            break;

        default:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_mac_error_msg_report::unknown mac error}\r\n");
            break;

    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_soc_error_msg_report
 功能描述  : soc错误日志上报
 输入参数  : oal_uint8 uc_vap_id
             hal_mac_error_type_enum_uint8 en_error_id
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月27日,星期二
    作    者   : y00201072
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_soc_error_msg_report(oal_uint8 uc_vap_id, hal_mac_error_type_enum_uint8 en_error_id)
{
    switch (en_error_id)
    {
        case HAL_SOC_ERROR_BUCK_OCP:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_BUCK_OCP}\r\n");
            break;

        case HAL_SOC_ERROR_BUCK_SCP:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_BUCK_SCP}\r\n");
            break;

        case HAL_SOC_ERROR_OCP_RFLDO1:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_OCP_RFLDO1}\r\n");
            break;

        case HAL_SOC_ERROR_OCP_RFLDO2:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_OCP_RFLDO2}\r\n");
            break;

        case HAL_SOC_ERROR_OCP_CLDO:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_OCP_CLDO}\r\n");
            break;

        case HAL_SOC_ERROR_RF_OVER_TEMP:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_RF_OVER_TEMP}\r\n");
            break;

        case HAL_SOC_ERROR_CMU_UNLOCK:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_CMU_UNLOCK}\r\n");
            break;

        case HAL_SOC_ERROR_PCIE_SLV_ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_PCIE_SLV_ERR}\r\n");
            break;

        default:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::unknown soc error.}\r\n");
            break;
    }

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 函 数 名  : dmac_handle_mac_error_immediately
 功能描述  : MAC错误中断处理函数(立即处理)
 输入参数  : pst_mac_device: MAC DEVICE结构体指针
             en_error_id   : MAC错误中断类型，注意此处枚举值与错误中断状态寄存器的位一一对应
 输出参数  : 无
 返 回 值  : OAL_SUCC或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月28日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_handle_reset_mac_error_immediately(
                mac_device_stru                 *pst_mac_device,
                hal_mac_error_type_enum_uint8    en_error_id)
{
    hal_to_dmac_device_stru   *pst_hal_device;
    dmac_reset_para_stru       st_reset_param;

    if (OAL_UNLIKELY(en_error_id >= HAL_MAC_ERROR_TYPE_BUTT))
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    /* 复位: 清除所有异常统计，重新开始计数 */
    OAL_MEMZERO(pst_hal_device->st_dfr_err_opern, OAL_SIZEOF(pst_hal_device->st_dfr_err_opern));

    /*复位MAC + PHY的逻辑*/
    st_reset_param.uc_reset_type    = HAL_RESET_HW_TYPE_ALL;
    st_reset_param.uc_reset_mac_mod = HAL_RESET_MAC_ALL;
    st_reset_param.uc_reset_mac_reg = OAL_FALSE;
    st_reset_param.uc_reset_phy_reg = OAL_FALSE;

    dmac_reset_hw(pst_mac_device, (oal_uint8 *)&st_reset_param);

    return OAL_SUCC;
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_set_agc_lock_channel
 功能描述  : wavetest仪器性能测试场景，设定AGC绑定通道
 输入参数  : pst_vap:mac vap指针

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月02日
    作    者   : ywx282918
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_set_agc_lock_channel(
            mac_vap_stru        *pst_vap,
            dmac_rx_ctl_stru    *pst_cb_ctrl)
{
    mac_device_stru           *pst_mac_device = OAL_PTR_NULL;
    dmac_vap_stru             *pst_dmac_vap = OAL_PTR_NULL;
    hal_to_dmac_device_stru   *pst_hal_device = OAL_PTR_NULL;

    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        return;
    }

    if (pst_mac_device->en_is_wavetest)
    {
        /* Wavetest性能测试场景下,设定AGC固定绑定通道0  */
        if (pst_mac_device->uc_lock_channel == 0x00)
        {
            return;
        }
        else
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_vap->uc_vap_id);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
            {
                return;
            }

            pst_hal_device = pst_dmac_vap->pst_hal_device;
            hal_reg_write(pst_hal_device, 0x20038d40, 0x00);

            pst_mac_device->uc_lock_channel = 0x00;
        }
    }
    else
    {
        /* 非Wavetest性能测试场景下,设定AGC绑定通道为自适应 */
        if (pst_mac_device->uc_lock_channel == 0x02)
        {
            return;
        }
        else
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_vap->uc_vap_id);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
            {
                return;
            }

            pst_hal_device = pst_dmac_vap->pst_hal_device;
            hal_reg_write(pst_hal_device, 0x20038d40, 0x02);

            pst_mac_device->uc_lock_channel = 0x02;
        }
    }
}
#endif

/*****************************************************************************
 函 数 名  : dmac_mac_error_process_event
 功能描述  : 接收错误中断处理函数入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : huxiaotong
    修改内容   : 新生成函数
 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : zhangyu 00241943
    修改内容   : 1102错误寄存器有两个，需要上报两个错误码，将其合为一个uint64错误码之后进行错误遍历
                 ul_error2_irq_state:1151代码会填写为0，1102填写ERR2_INTR_STATUS_REG读取值

*****************************************************************************/
oal_uint32  dmac_mac_error_process_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    hal_error_irq_event_stru           *pst_error_irq_event;
    hal_error_state_stru                st_error_state;
    hal_to_dmac_device_stru            *pst_hal_device;
    mac_device_stru                    *pst_device;
    oal_uint32                          ul_error1_irq_state = 0;
    oal_uint32                          ul_error2_irq_state = 0;
    hal_mac_error_type_enum_uint8       en_error_id = 0;
    oal_uint8                           uc_show_error_mask[] = {
                                        HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL,
                                    #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
                                        HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY,
                                        HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY,
                                        HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR,
                                    #endif
                                        HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND};
    oal_uint32                          ul_error_mask = 0;
    oal_uint8                           uc_err_mask_idx;
    oal_uint8                           uc_status_idx    = 0;
    oal_uint32                          ul_err_code      = 0;

    dmac_error_proc_stru                st_err_proc_func[HAL_MAC_ERROR_TYPE_BUTT] =
    {
      {dmac_dump_all_tx_dscr,0},
      {dmac_proc_rxbuf_too_small_error,0},
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
      {dmac_tx_dataflow_break_error,0},
      {dmac_proc_rx_fsm_st_timeout_error,0},{dmac_proc_tx_fsm_st_timeout_error,0},
#else
      {dmac_dump_all_tx_dscr,0},  /* HAL_MAC_ERROR_TX_DATAFLOW_BREAK */
      {dmac_null_fn,0},{dmac_null_fn,0},
#endif
      {dmac_null_fn,0},{dmac_null_fn,0},
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},  /* HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND 至 HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN*/
      {dmac_rx_resume_dscr_queue, 0},    /* HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY */
      {dmac_rx_resume_dscr_queue, 1},    /* HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY */
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_BK},  /* HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN */
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_BE},  /* HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN */
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_VI},  /* HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN */
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_VO},  /* HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN */
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_HI},  /* HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN */
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
      {dmac_proc_beacon_miss_error,0},
#else
      {dmac_null_fn,0},
#endif
      {dmac_null_fn,0},
#if 0
      {dmac_rx_resume_dscr_queue_all,0},  /* HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR 29 */
#else
      /*do nothing，DTS2015042800155,z00262551*/
      {dmac_null_fn,0}, /* HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR 29 */
#endif
      {dmac_null_fn,0},
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},
      {dmac_null_fn,0},{dmac_null_fn,0},
      {dmac_rx_resume_dscr_queue,2}, /* HAL_MAC_ERROR_RX_SMALL_Q_EMPTY */
      {dmac_dump_all_tx_dscr,0},{dmac_dump_all_tx_dscr,0},{dmac_null_fn,0}   /* OTHER */
    };

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::null param.}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件头和事件结构体指针 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_error_irq_event     = (hal_error_irq_event_stru *)(pst_event->auc_event_data);
    pst_hal_device          = pst_error_irq_event->pst_hal_device;
    ul_error1_irq_state = pst_error_irq_event->st_error_state.ul_error1_val;
    ul_error2_irq_state = pst_error_irq_event->st_error_state.ul_error2_val;;

#ifdef _PRE_WLAN_DFT_REG
    if (OAL_SUCC == hi1151_debug_refresh_reg(pst_hal_device, OAM_REG_EVT_RX))
    {
        hi1151_debug_frw_evt(pst_hal_device);
    }
#endif

    pst_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::mac_res_get_dev return null. device_id=[%d]}\r\n",
                       pst_event->st_event_hdr.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 上报的HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL 和 HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT 和 HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND 错误中断，不用打印device id */
    if((ul_error1_irq_state & (~(1 << HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL | 1 << HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT | 1 << HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND))) || ul_error2_irq_state)
    {
        OAM_WARNING_LOG3(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::chip id=[%d], error1 state=[0x%08x], erro2 state=[0x%08x]\r\n",
            pst_event->st_event_hdr.uc_chip_id, ul_error1_irq_state, ul_error2_irq_state);
    }

    for (uc_status_idx = 0; uc_status_idx < 2; uc_status_idx++)
    {
        if (uc_status_idx == 0)
        {
            ul_err_code = ul_error1_irq_state;
            en_error_id = 0;
        }
        else
        {
            ul_err_code = ul_error2_irq_state;
            en_error_id = HAL_MAC_ERROR_TX_ACBE_BACKOFF_TIMEOUT;
        }

        while (ul_err_code)
        {
            if (HAL_MAC_ERROR_TYPE_BUTT <= en_error_id)
            {
                OAM_WARNING_LOG2(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::error type[%d], ul_err_code = [%d].}\r\n",
                                en_error_id, ul_err_code);
                ul_err_code = 0;

                break;
            }

            if (0 == (ul_err_code & BIT0))
            {
                en_error_id++;
                ul_err_code = ul_err_code >> 1;
                continue;
            }

            st_err_proc_func[en_error_id].p_func(pst_device, (st_err_proc_func[en_error_id].ul_param));

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
            if((en_error_id == HAL_MAC_ERROR_BEACON_MISS) ||(en_error_id == HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT)||(en_error_id == HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT))
            {
                if((en_error_id == HAL_MAC_ERROR_BEACON_MISS)&&((pst_device->ul_beacon_miss_show_counter <= 50) || (pst_device->ul_beacon_miss_show_counter % 100 == 0)))
                {
                    hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
                    /* BEACON MISS维测 */
                    hal_get_beacon_miss_status(pst_device->pst_device_stru);
                }
                else if((en_error_id == HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT)&&((pst_device->ul_rx_fsm_st_timeout_show_counter <= 50) || (pst_device->ul_rx_fsm_st_timeout_show_counter % 100 == 0)))
                {
                    hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
                }
                else if((en_error_id == HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT)&&((pst_device->ul_tx_fsm_st_timeout_show_counter <= 50) || (pst_device->ul_tx_fsm_st_timeout_show_counter % 100 == 0)))
                {
                    hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
                }
            }
            else
            {
                hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
            }
#else
            hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
#endif

            if (dmac_mac_error_overload(pst_device, en_error_id))
            {
                 /*错误出现太多的时候，不允许再上报，因此不需要unmask该bit,在tbtt中断中统一将0xffffffff unmask全部错误*/
                 if ((en_error_id == HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL)
                   ||(en_error_id == HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND))
                 {
                     OAM_WARNING_LOG1(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::error type[%d] overload.}\r\n", en_error_id);
                     ul_error1_irq_state &= ~((oal_uint32)1 << en_error_id);
                 }
                 else
                 {
                     OAM_ERROR_LOG1(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::error type[%d] overload.}\r\n", en_error_id);
                     if (en_error_id <= HAL_MAC_ERROR_RESERVED_31)
                     {
                         ul_error1_irq_state &= ~((oal_uint32)1 << en_error_id);
                     }
                     else
                     {
                         ul_error2_irq_state &= ~((oal_uint32)1 << (en_error_id - HAL_MAC_ERROR_TX_ACBE_BACKOFF_TIMEOUT));
                     }
                 }
            }

            /* 检查mac 错误是否需要软件复位 */
            dmac_dfr_process_mac_error(pst_device, en_error_id, ul_error1_irq_state, ul_error2_irq_state);

            en_error_id++;
            ul_err_code = ul_err_code >> 1;
        }
    }

    /*计算不需要打印pcie错误类型的组合位图*/
    for (uc_err_mask_idx = 0; uc_err_mask_idx < OAL_SIZEOF(uc_show_error_mask) / OAL_SIZEOF(oal_uint8); uc_err_mask_idx++)
    {
        ul_error_mask |= 1 << uc_show_error_mask[uc_err_mask_idx];
    }
    st_error_state.ul_error1_val = 0xFFFFFFFF;
    st_error_state.ul_error2_val = 0xFFFFFFFF;

    /* 存在非MASK的Error时才打印pcie状态 */
    if ((ul_error1_irq_state & ~(ul_error_mask)) || (ul_error2_irq_state))
    {
        hal_show_fsm_info(pst_device->pst_device_stru);
    }

    /* 清中断 */
    hal_clear_mac_error_int_status(pst_hal_device, &st_error_state);

    /* 清中断状态 */
    hal_clear_mac_int_status(pst_hal_device, (1 << DMAC_PA_ERROR_OFFSET));

    /* unmask error stauts */

    st_error_state.ul_error1_val = ul_error1_irq_state;
    st_error_state.ul_error2_val = ul_error2_irq_state & 0xffffffdf;
    hal_unmask_mac_error_init_status(pst_hal_device, &st_error_state);

    /* unmask mac stauts */
    hal_unmask_mac_init_status(pst_hal_device, (1 << DMAC_PA_ERROR_OFFSET));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_soc_error_process_event
 功能描述  : 处理soc错误中断
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月1日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_soc_error_process_event(frw_event_mem_stru *pst_event_mem)
{
    dmac_reset_para_stru                st_reset;
    frw_event_stru                     *pst_event;
    hal_error_irq_event_stru           *pst_error_irq_event;
    mac_device_stru                    *pst_device;
    hal_soc_error_type_enum_uint8       en_error_id = 0;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_soc_error_process_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件头和事件结构体指针 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_error_irq_event     = (hal_error_irq_event_stru *)(pst_event->auc_event_data);

    pst_device= mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_soc_error_process_event::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /*获取fsm状态机信息*/
    hal_show_fsm_info(pst_device->pst_device_stru);

    for (en_error_id = 0; en_error_id < HAL_SOC_ERROR_TYPE_BUTT; en_error_id++)
    {
        if (pst_error_irq_event->st_error_state.ul_error1_val & (1 << en_error_id))
        {
            dmac_soc_error_msg_report(0, en_error_id);
        }
    }

    /*复位MAC+PHY的逻辑*/
    st_reset.uc_reset_type = HAL_RESET_HW_TYPE_ALL;
    st_reset.uc_reset_mac_mod = HAL_RESET_MAC_ALL;
    st_reset.uc_reset_mac_reg = OAL_FALSE;
    st_reset.uc_reset_phy_reg = OAL_FALSE;

    dmac_reset_hw(pst_device, (oal_uint8*)&st_reset);
    hal_en_soc_intr(pst_device->pst_device_stru);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_rx_process_frame
 功能描述  : 处理每一个帧的操作的函数,主要针对接收流程中的帧的各种过滤处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月29日
    作    者   : huxiaotong
    修改内容   : 新生成函数
  2.日    期   : 2013年12月29日
    作    者   : g00260350
    修改内容   : mic攻击，不在驱动处理，只需要上报到host
  3.日    期   : 2014年05月23日
    作    者   : z00273164
    修改内容   : 忽略CCMP重放攻击

*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif

dmac_rx_frame_ctrl_enum_uint8  dmac_rx_process_frame(
                mac_vap_stru                   *pst_vap,
                dmac_rx_ctl_stru               *pst_cb_ctrl,
                oal_netbuf_stru                *pst_netbuf,
                oal_netbuf_head_stru           *pst_netbuf_header)
                //dmac_rx_frame_ctrl_enum_uint8  *pen_frame_ctrl)
{
    mac_ieee80211_frame_stru           *pst_frame_hdr;
    oal_uint8                          *puc_transmit_addr;
    oal_uint8                          *puc_dest_addr;
    dmac_user_stru                     *pst_ta_dmac_user = OAL_PTR_NULL;
    oal_uint16                          us_user_idx      = 0xffff;
    oal_nl80211_key_type                en_key_type;
    oal_uint32                          ul_ret;
    oal_uint16                          us_dscr_status;
#ifdef _PRE_WLAN_HW_TEST
    mac_device_stru                    *pst_mac_device = OAL_PTR_NULL;
#endif

#ifdef _PRE_WLAN_DFT_STAT
    dmac_vap_stru               *pst_dmac_vap;
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "mac_res_get_dmac_vap::pst_dmac_vap null. vap_id[%u]",pst_vap->uc_vap_id);
        return DMAC_RX_FRAME_CTRL_DROP;
    }
#endif
    /* 统计VAP级别接收到的MPDU个数 */
    OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_mpdu_total_num, 1);
    DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_mpdu_total_num, 1);

    /* 获取802.11头指针、发送端地址 */
    pst_frame_hdr     = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info)));
    puc_transmit_addr = pst_frame_hdr->auc_address2;
    puc_dest_addr     = pst_frame_hdr->auc_address1;

    dmac_rx_record_tid(pst_vap, pst_frame_hdr);

    /* 发送端地址为广播帧，直接丢弃 */
    if (ETHER_IS_MULTICAST(puc_transmit_addr))
    {
        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::the transmit addr is multicast.}");

// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;
        return DMAC_RX_FRAME_CTRL_DROP;
    }

    us_dscr_status = pst_cb_ctrl->st_rx_status.bit_dscr_status;

    /* VAP ID 为0，代表该帧是来自其他BSS的广播管理帧 */
    if (0 == pst_vap->uc_vap_id)
    {
        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "this frame is bcast frame from other bss. exit func dmac_rx_process_frame");

        if ((HAL_RX_SUCCESS != us_dscr_status)
             || (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type))
        {
            //OAM_INFO_LOG2(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::dscr_status[%d]type[%d]", us_dscr_status, pst_frame_hdr->st_frame_control.bit_type);
            return DMAC_RX_FRAME_CTRL_DROP;
        }

        return DMAC_RX_FRAME_CTRL_BUTT;
    }

    /* 对单播帧进行过滤 不是发给我的帧，直接过滤掉 */
    if (OAL_FALSE == ETHER_IS_MULTICAST(puc_dest_addr))
    {
#ifdef _PRE_WLAN_FEATURE_P2P
        /* DTS2015022702328 需要比对P2P0的MAC地址和WLAN的MAC地址 */
        ul_ret = oal_compare_mac_addr(puc_dest_addr, pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID)
                    && oal_compare_mac_addr(puc_dest_addr, pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);
#else
        ul_ret = oal_compare_mac_addr(puc_dest_addr, pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
#endif  /* _PRE_WLAN_FEATURE_P2P */
        if (0 != ul_ret)
        {
            return DMAC_RX_FRAME_CTRL_DROP;
        }
    }
    OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_ADDR_VAP);

    if (WLAN_VAP_MODE_BSS_STA == dmac_vap_get_bss_type(pst_vap))
    {
        us_user_idx = pst_vap->uc_assoc_vap_id;
    }
    else if(WLAN_VAP_MODE_BSS_AP == dmac_vap_get_bss_type(pst_vap))
    {
        /* 获取发送端的用户指针，并存到cb字段中，uapd节能管理时会用到 */
        ul_ret = mac_vap_find_user_by_macaddr(pst_vap, puc_transmit_addr, &us_user_idx);
        if (OAL_ERR_CODE_PTR_NULL == ul_ret)
        {
            //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::mac_vap_find_user_by_macaddr return null.}");
            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_ta_check_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ta_check_dropped, 1);

// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;
            return DMAC_RX_FRAME_CTRL_DROP;
        }
    }
    pst_ta_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);

    if (OAL_PTR_NULL != pst_ta_dmac_user)
    {
        /* 更新用户时间戳 */
        pst_ta_dmac_user->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    #ifdef _PRE_DEBUG_MODE_USER_TRACK
        /* 检查来自此用户的帧协议模式是否改变，如果改变了则上报 */
        dmac_user_check_txrx_protocol_change(pst_ta_dmac_user,
                                        HAL_GET_DATA_PROTOCOL_MODE(*((oal_uint8 *)&(pst_cb_ctrl->st_rx_statistic.un_nss_rate))),
                                        OAM_USER_INFO_CHANGE_TYPE_RX_PROTOCOL);
    #endif
        if ((HAL_RX_SUCCESS != us_dscr_status))
        {
            /*信息上报统计，提供给linux内核PKT生成*/
            DMAC_USER_STATS_PKT_INCR(pst_ta_dmac_user->st_query_stats.ul_rx_dropped_misc,1);
        }
    }

#ifdef _PRE_WLAN_HW_TEST
    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {

        return DMAC_RX_FRAME_CTRL_DROP;
    }
    /* 常收会走该流程 */
    if (HAL_ALWAYS_RX_RESERVED == pst_mac_device->pst_device_stru->bit_al_rx_flag)
    {
        /* phy性能测试统计入口 */
        dmac_rx_fcs_statistic_info(pst_frame_hdr, pst_vap, pst_cb_ctrl);
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_phy_perform_dropped, 1);

        /* 由于当前软件处理速度较慢，暂时直接释放，返回 */
// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;

        return DMAC_RX_FRAME_CTRL_DROP;
    }
#endif

    /*OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::bit_dscr_status=%d. }", pst_cb_ctrl->st_rx_status.bit_dscr_status);*/

    if (HAL_RX_SUCCESS != us_dscr_status)
    {
        /* 接收描述符status为key search fail时的异常处理 */
        if (HAL_RX_KEY_SEARCH_FAILURE == us_dscr_status)
        {
            dmac_user_key_search_fail_handler(pst_ta_dmac_user);
// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;

            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_key_search_fail_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_key_search_fail_dropped, 1);

            return DMAC_RX_FRAME_CTRL_DROP;
        }

        /* 接收描述符status为 tkip mic faile 时的异常处理 */
        if (HAL_RX_TKIP_MIC_FAILURE == us_dscr_status)
        {
            /*判断密钥类型,peerkey 暂不处理*/
            en_key_type = ETHER_IS_MULTICAST(puc_dest_addr) ? NL80211_KEYTYPE_GROUP : NL80211_KEYTYPE_PAIRWISE;
            dmac_11i_tkip_mic_failure_handler(pst_vap, puc_transmit_addr, en_key_type);
            //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::bit_dscr_status=HAL_RX_TKIP_MIC_FAILURE.");

// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;

            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_tkip_mic_fail_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_tkip_mic_fail_dropped, 1);
            return DMAC_RX_FRAME_CTRL_DROP;
        }

        if (OAL_TRUE != dmac_rx_check_mgmt_replay_failure(pst_cb_ctrl))
        {
            /*DTS2013122406910  硬件上报了重放错误，软件需要暂时规避，跟硬件解决后再放开*/
            /* if ((HAL_RX_TKIP_REPLAY_FAILURE != pst_cb_ctrl->st_rx_status.bit_dscr_status) && (HAL_RX_CCMP_REPLAY_FAILURE != pst_cb_ctrl->st_rx_status.bit_dscr_status)) */
            OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_rx_process_frame::bit_dscr_status=%d.}", us_dscr_status);
// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;

            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_replay_fail_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_replay_fail_dropped, 1);
            return DMAC_RX_FRAME_CTRL_DROP;
        }
    }

    /* 获取的用户index存放在在cb字段中，后续过滤使用(dmac_rx_filter_frame) */
    MAC_GET_RX_CB_TA_USER_IDX(&(pst_cb_ctrl->st_rx_info)) = (oal_uint8)us_user_idx;

    OAM_STAT_USER_INCR(us_user_idx, rx_mpdu_num, 1);
    if (OAL_PTR_NULL != pst_ta_dmac_user)
    {
        /*信息上报统计，提供给linux内核PKT生成*/
        if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
            DMAC_USER_STATS_PKT_INCR(pst_ta_dmac_user->st_query_stats.ul_drv_rx_pkts, 1);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            DMAC_USER_STATS_PKT_INCR(pst_ta_dmac_user->st_query_stats.ul_drv_rx_bytes,
                                    pst_cb_ctrl->st_rx_info.us_frame_len - pst_cb_ctrl->st_rx_info.bit_mac_header_len - SNAP_LLC_FRAME_LEN);
#else
            DMAC_USER_STATS_PKT_INCR(pst_ta_dmac_user->st_query_stats.ul_drv_rx_bytes,
                                    pst_cb_ctrl->st_rx_info.us_frame_len - pst_cb_ctrl->st_rx_info.uc_mac_header_len - SNAP_LLC_FRAME_LEN);
#endif
        }
    }

    OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_DSCR_SEC);
    /* 过滤一:针对发送端地址过滤(包括关联状态、AMPDU特性、加密处理) */
    ul_ret = dmac_rx_filter_frame(pst_vap, pst_cb_ctrl, pst_ta_dmac_user);
    if (OAL_SUCC != ul_ret)        /* 程序异常 */
    {
        //OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::dmac_rx_filter_frame failed[%d].}", ul_ret);
        return DMAC_RX_FRAME_CTRL_DROP;
    }
    OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_CIPHER_AMPDU);

    if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
    {
        /* AGC绑定通道设定  */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        dmac_set_agc_lock_channel(pst_vap, pst_cb_ctrl);
#endif
        /* 安全端口过滤 */
        ul_ret = dmac_rx_filter_wlan_security(pst_vap, pst_cb_ctrl, pst_netbuf);
        if (OAL_SUCC != ul_ret)
        {
            return DMAC_RX_FRAME_CTRL_DROP;
        }

        ul_ret = dmac_rx_process_data_frame(pst_vap, pst_cb_ctrl, pst_netbuf);

        OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);

        if (OAL_SUCC != ul_ret)
        {
// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;
            //OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::dmac_rx_process_data_frame failed[%d].}", ul_ret);
            return DMAC_RX_FRAME_CTRL_DROP;
        }
    }
#ifdef _PRE_WLAN_DFT_STAT
    dmac_rx_vap_stat(pst_dmac_vap, pst_netbuf_header, pst_netbuf, pst_cb_ctrl);
#endif
    OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_ALG_PSM_NULL);

    return DMAC_RX_FRAME_CTRL_BUTT;
}
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

#if 0
/*****************************************************************************
 函 数 名  : dmac_start_stat_rssi
 功能描述  : 开始统计平均rssi接口
 输入参数  : pst_user : User指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_start_stat_rssi(dmac_user_stru *pst_dmac_user)
{
    pst_dmac_user->st_user_rate_info.en_dmac_rssi_stat_flag = OAL_TRUE;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_get_stat_rssi
 功能描述  : 获取统计平均rssi接口
 输入参数  : pst_dmac_user : dmac user指针
 输出参数  : pc_tx_rssi:平均ACK rssi
             pc_rx_rssi:平均上行rssi
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_get_stat_rssi(dmac_user_stru *pst_dmac_user, oal_int8 *pc_tx_rssi, oal_int8 *pc_rx_rssi)
{
    dmac_user_rate_info_stru   *pst_user_info;

    pst_user_info = &pst_dmac_user->st_user_rate_info;

    /* 获取平均ACK RSSI */
    if (0 != pst_user_info->st_dmac_rssi_stat_info.us_tx_rssi_stat_count)
    {
        *pc_tx_rssi = (oal_int8)(pst_user_info->st_dmac_rssi_stat_info.l_tx_rssi / pst_user_info->st_dmac_rssi_stat_info.us_tx_rssi_stat_count);
    }

    /* 获取平均上行 RSSI */
    if (0 != pst_user_info->st_dmac_rssi_stat_info.us_rx_rssi_stat_count)
    {
        *pc_rx_rssi = (oal_int8)(pst_user_info->st_dmac_rssi_stat_info.l_rx_rssi / pst_user_info->st_dmac_rssi_stat_info.us_rx_rssi_stat_count);
    }

    /* 清空统计信息 */
    OAL_MEMZERO(&pst_user_info->st_dmac_rssi_stat_info, OAL_SIZEOF(dmac_rssi_stat_info_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_stop_stat_rssi
 功能描述  : 停止统计平均rssi接口
 输入参数  : pst_dmac_user : dmac user指针
 输出参数  :
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_stop_stat_rssi(dmac_user_stru *pst_dmac_user)
{
    pst_dmac_user->st_user_rate_info.en_dmac_rssi_stat_flag = OAL_FALSE;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_start_stat_rate
 功能描述  : 开始统计平均速率接口
 输入参数  : pst_user : User指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_start_stat_rate(dmac_user_stru *pst_dmac_user)
{
    pst_dmac_user->st_user_rate_info.en_dmac_rate_stat_flag = OAL_TRUE;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_get_stat_rate
 功能描述  : 获取统计平均速率接口
 输入参数  : pst_mac_user : User指针
 输出参数  : pul_tx_rate:平均发送速率
             pul_rx_rate:平均接收速率
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_get_stat_rate(dmac_user_stru *pst_dmac_user, oal_uint32 *pul_tx_rate, oal_uint32 *pul_rx_rate)
{
    dmac_user_rate_info_stru   *pst_user_info;

    pst_user_info = &pst_dmac_user->st_user_rate_info;

    /* 获取平均发送速率 */
    if (0 != pst_user_info->st_dmac_rate_stat_info.us_tx_rate_stat_count)
    {
        *pul_tx_rate = (oal_uint32)(pst_user_info->st_dmac_rate_stat_info.ul_tx_rate / pst_user_info->st_dmac_rate_stat_info.us_tx_rate_stat_count);
    }

    /* 获取平均接收速率 */
    if (0 != pst_user_info->st_dmac_rate_stat_info.us_rx_rate_stat_count)
    {
        *pul_rx_rate = (oal_uint32)(pst_user_info->st_dmac_rate_stat_info.ul_rx_rate / pst_user_info->st_dmac_rate_stat_info.us_rx_rate_stat_count);
    }

    /* 清空统计信息 */
    OAL_MEMZERO(&pst_user_info->st_dmac_rate_stat_info, OAL_SIZEOF(dmac_rate_stat_info_stru));

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 函 数 名  : dmac_stop_stat_rate
 功能描述  : 停止统计平均速率接口
 输入参数  : pst_mac_user : User指针
 输出参数  :
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_stop_stat_rate(dmac_user_stru *pst_dmac_user)
{
    dmac_user_rate_info_stru   *pst_user_info;
    pst_user_info = &pst_dmac_user->st_user_rate_info;

    if (OAL_TRUE == pst_user_info->en_dmac_rate_stat_flag)
    {
        pst_user_info->en_dmac_rate_stat_flag = OAL_FALSE;
        /* 清空统计信息 */
        OAL_MEMZERO(&pst_user_info->st_dmac_rate_stat_info, OAL_SIZEOF(dmac_rate_stat_info_stru));
    }
    return OAL_SUCC;
}
#endif

/*lint -e19*/
oal_module_symbol(dmac_rx_process_data_event);
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1102_DEV)
oal_module_symbol(g_ast_rx_fcs_statistic);     /* add for phy(2) */
#endif
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

