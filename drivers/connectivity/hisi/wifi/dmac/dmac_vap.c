/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_vap.c
  版 本 号   : 初稿
  作    者   : huxiaotong
  生成日期   : 2012年10月19日
  最近修改   : DMAC不需要destroy的动作，
               因为destroy是从hmac发起的，分别会调用down和del
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
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
#include "oam_ext_if.h"

#include "wlan_spec.h"

#include "mac_vap.h"
#include "dmac_vap.h"
#include "dmac_user.h"
#include "dmac_main.h"
#include "dmac_blockack.h"
#include "dmac_alg.h"
#include "dmac_beacon.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_mgmt_sta.h"
#include "dmac_uapsd.h"
#include "dmac_psm_ap.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_dbac.h"
#endif
#ifdef _PRE_WIFI_DMT
#include "dmt_stub.h"
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_sta_pm.h"
#endif
#include "dmac_device.h"
#include "mac_device.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_VAP_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
oal_uint16 g_us_occupied_point[BTCOEX_LINKLOSS_OCCUPIED_NUMBER];
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_vap_linkloss_init
 功能描述  :  初始化linkloss检测工具
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : zhongwen
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_vap_linkloss_init(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    oal_uint8 uc_index;
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;
#endif

    dmac_vap_linkloss_clean(pst_dmac_vap);
    if (WLAN_VAP_MODE_BSS_STA != pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_dmac_vap->st_linkloss_info.us_linkloss_threshold  = 0; /* 无效 */
        return;
    }

    /* 尚未关联，预先设置对端ap的beacon周期为100 */
    pst_dmac_vap->st_linkloss_info.ul_old_dot11BeaconPeriod = WLAN_BEACON_INTVAL_DEFAULT;
    pst_dmac_vap->st_linkloss_info.uc_linkloss_times = 1;
    pst_dmac_vap->st_linkloss_info.en_old_bt_on        = OAL_FALSE;
    pst_dmac_vap->st_linkloss_info.en_old_dbac_runing  = OAL_FALSE;
    pst_dmac_vap->st_linkloss_info.en_old_far_distance = OAL_FALSE;
    /* staut/p2p cl linkloss门限一致 */
    pst_dmac_vap->st_linkloss_info.us_linkloss_threshold  = (oal_uint16)(40); /* 4s */

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    g_us_occupied_point[0] = 5;     /* pst_dmac_vap->st_linkloss_info.us_linkloss_threshold / BTCOEX_LINKLOSS_OCCUPIED_NUMBER */

    for (uc_index = 0; uc_index < BTCOEX_LINKLOSS_OCCUPIED_NUMBER - 1; uc_index++)
    {
        g_us_occupied_point[uc_index + 1] = g_us_occupied_point[uc_index] + 5;
    }

    pst_btcoex_wifi_status = &(pst_dmac_vap->pst_hal_device->st_btcoex_wifi_status);
    pst_btcoex_wifi_status->uc_linkloss_index = 1;
    pst_btcoex_wifi_status->uc_linkloss_occupied_times = 0;
#endif

}

/*****************************************************************************
 函 数 名  : dmac_vap_init
 功能描述  : 初始化要添加的dmac vap的一些特性信息
 输入参数  : 指向要添加的vap的指针
 输出参数  : 无
 返 回 值  : 成功或者失败原因
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月24日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_vap_init(
                dmac_vap_stru              *pst_dmac_vap,
                oal_uint8                   uc_chip_id,
                oal_uint8                   uc_device_id,
                oal_uint8                   uc_vap_id,
                mac_cfg_add_vap_param_stru *pst_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32  ul_ret;
#endif
    mac_device_stru               *pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_vap_init::pst_mac_device[%d] null!}", uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* DMAC VAP 部分初始清零 */
    OAL_MEMZERO(((oal_uint8 *)pst_dmac_vap) + OAL_SIZEOF(mac_vap_stru), OAL_SIZEOF(dmac_vap_stru) - OAL_SIZEOF(mac_vap_stru));
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

    /* 统计信息清零 */
    oam_stats_clear_vap_stat_info(uc_vap_id);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 在非OFFLOAD情况下，这些操作HMAC都已经做过了 */
    /* 初始化mac vap */
    ul_ret = mac_vap_init(&pst_dmac_vap->st_vap_base_info,
                           uc_chip_id,
                           uc_device_id,
                           uc_vap_id,
                           pst_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_CFG,
                         "{dmac_vap_init::dmac_vap_init failed[%d].", ul_ret);
        return ul_ret;
    }
    pst_dmac_vap->bit_beacon_timeout_times = 0;
#endif

    pst_dmac_vap->en_bfer_actived       = pst_mac_device->bit_su_bfmer;
    pst_dmac_vap->en_bfee_actived       = pst_mac_device->bit_su_bfmee;
    pst_dmac_vap->en_mu_bfee_actived    = pst_mac_device->bit_mu_bfmee;
    pst_dmac_vap->en_txstbc_actived     = pst_mac_device->bit_tx_stbc;
    pst_dmac_vap->en_multi_user_multi_ac_flag = OAL_FALSE;
    pst_dmac_vap->uc_traffic_type    = OAL_TRAFFIC_NORMAL;

    /* 初始化特性标识中BEACON帧不轮流发送 */
    pst_dmac_vap->en_beacon_chain_active = OAL_FALSE;

    /* VAP发送通道默认值赋值，按照device下能力赋值 */
    pst_dmac_vap->uc_vap_tx_chain = pst_mac_device->uc_tx_chain;

    /* 速率结构体赋初值 */
    /* 按照PHY给出的初始值 ul_value = 0x00800211 */
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_count = 1;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = 0;
#endif
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna = 2;


    /* FPGA zhangyu Debug 11n */
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = 0;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_protocol_mode = WLAN_HT_PHY_PROTOCOL_MODE;

    /* 默认是HOST VAP */
    pst_dmac_vap->en_is_host_vap = OAL_TRUE;

    /* 默认天线组合 */
    pst_dmac_vap->uc_default_ant_bitmap = 0xFF;

    /* 初始化节能相关参数 */
    pst_dmac_vap->uc_ps_user_num = 0;
    pst_dmac_vap->uc_dtim_count  = WLAN_DTIM_DEFAULT;
#ifdef _PRE_WLAN_CHIP_TEST
    pst_dmac_vap->pst_wow_probe_resp = OAL_PTR_NULL;
    pst_dmac_vap->pst_wow_null_data  = OAL_PTR_NULL;
#endif
    pst_dmac_vap->uc_sw_retry_limit  = DMAC_MAX_SW_RETRIES;

    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        /* DTS2015050301014,双芯片实现时bitmap_len计算要乘以device(也即是chip)个数  */
        pst_dmac_vap->uc_tim_bitmap_len = (oal_uint8)(2 + (((g_us_max_asoc_user + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE)* MAC_RES_MAX_DEV_NUM + 7 ) >> 3));
        pst_dmac_vap->puc_tim_bitmap = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, pst_dmac_vap->uc_tim_bitmap_len, OAL_TRUE);
        if (OAL_PTR_NULL == pst_dmac_vap->puc_tim_bitmap)
        {
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_vap_init::puc_tim_bitmap null.}");

            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        OAL_MEMZERO(pst_dmac_vap->puc_tim_bitmap, pst_dmac_vap->uc_tim_bitmap_len);
        /* TIM bitmap len is default 1*/
        pst_dmac_vap->puc_tim_bitmap[0] = 1;
    }
    if(WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_DFS
        mac_mib_set_SpectrumManagementImplemented(&pst_dmac_vap->st_vap_base_info, OAL_TRUE);
#endif
    }

    /* 初始化重排序超时时间 */
    pst_dmac_vap->us_del_timeout                = DMAC_BA_DELBA_TIMEOUT;

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    pst_dmac_vap->pst_ip_addr_info = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_vap_ip_entries_stru), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap->pst_ip_addr_info))
    {
        if ((WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode) && (OAL_PTR_NULL != pst_dmac_vap->puc_tim_bitmap))
        {
            OAL_MEM_FREE(pst_dmac_vap->puc_tim_bitmap, OAL_TRUE);
            pst_dmac_vap->puc_tim_bitmap = OAL_PTR_NULL;
        }
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_PWR, "{dmac_vap_init::Alloc memory for IP address record array failed.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    oal_memset(pst_dmac_vap->pst_ip_addr_info, 0, OAL_SIZEOF(dmac_vap_ip_entries_stru));

#endif

    pst_dmac_vap->st_query_stats.ul_signal = DMAC_INVALID_SIGNAL_INITIAL;

    pst_dmac_vap->us_beacon_timeout  = DMAC_DEFAULT_STA_BEACON_WAIT_TIME;
    pst_dmac_vap->us_in_tbtt_offset  = DMAC_DEFAULT_STA_INTER_TBTT_OFFSET;
    pst_dmac_vap->us_ext_tbtt_offset = DMAC_DEFAULT_EXT_TBTT_OFFSET;

	pst_dmac_vap->us_psm_dtim_period = 0;
	pst_dmac_vap->us_psm_listen_interval = 0;

	pst_dmac_vap->en_non_erp_exist = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_vap_init_tx_data_ucast
 功能描述  : 初始化单播数据帧发送速率参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月7日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_vap_init_tx_data_ucast(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_protocol_mode, oal_uint8 uc_legacy_rate)
{
    oal_uint32          ul_data_rate = 0;

    pst_dmac_vap->st_tx_alg.ast_per_rate[0].ul_value = 0x0;

    /* 单播数据帧参数 */
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_count           = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_stbc_mode          = 0;
#endif
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna     = 1;

    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = uc_legacy_rate;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = uc_protocol_mode;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable     = 0;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_txbf_mode          = 0;

    /* 11b 1M速率不可以使用短导码 */
    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0 == uc_legacy_rate))
    {
        pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 0;
    }
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable    = 0;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_reserve            = 0;

    ul_data_rate = pst_dmac_vap->st_tx_alg.ast_per_rate[0].ul_value;

    pst_dmac_vap->st_tx_alg.ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_alg.ast_per_rate[1].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_alg.ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_alg.ast_per_rate[2].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_alg.ast_per_rate[3].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_alg.ast_per_rate[3].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_alg.st_rate.bit_lsig_txop = OAL_FALSE;
}


/*****************************************************************************
 函 数 名  : dmac_vap_init_tx_data_mcast
 功能描述  : 初始化组播数据帧发送速率参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_vap_init_tx_data_mcast(
                dmac_vap_stru               *pst_dmac_vap,
                wlan_protocol_enum_uint8     en_protocol,
                wlan_channel_band_enum_uint8 en_band)
{
    oal_uint8       uc_protocol_mode;
    oal_uint8       uc_legacy_rate;
    oal_uint32      ul_data_rate;

    switch (en_protocol)
    {
        /* 11b 1M */
        case WLAN_LEGACY_11B_MODE:
        case WLAN_MIXED_ONE_11G_MODE:
        case WLAN_HT_MODE:
            if (WLAN_BAND_2G == en_band)
            {
                uc_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0;
#ifdef _PRE_WLAN_FEATURE_P2P
                /* P2P 设备不能发送11b 速率的帧 */
                uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0xB;
#endif  /* _PRE_WLAN_FEATURE_P2P */
            }
            else
            {
                uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0xB;
            }
            break;

        /* OFDM 6M */
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
        case WLAN_VHT_MODE:
        case WLAN_HT_11G_MODE:
            uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            uc_legacy_rate   = 0xB;
            break;

        /* OFDM 24M */
        case WLAN_HT_ONLY_MODE:
        case WLAN_VHT_ONLY_MODE:
            uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            uc_legacy_rate   = 0x9;
            break;

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{dmac_vap_init_tx_data_mcast::invalid en_protocol[%d].}", en_protocol);
            return;
    }


    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value = 0x0;

    /* 广播数据帧参数 */
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_count           = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_stbc_mode          = 0;

    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0x3 == pst_dmac_vap->uc_vap_tx_chain))
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
    }
#else
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
#endif
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna     = 1;

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = uc_legacy_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = uc_protocol_mode;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable     = 0;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_txbf_mode          = 0;

    /* 11b 1M速率不可以使用短导码 */
    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0 == uc_legacy_rate))
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 0;
    }

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable    = 0;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_reserve            = 0;

    ul_data_rate = pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value;

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[1].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[2].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[3].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[3].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_mcast.st_rate.bit_lsig_txop = OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_vap_init_tx_data_bcast
 功能描述  : 初始化广播数据帧发送速率参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_data_bcast(
                dmac_vap_stru               *pst_dmac_vap,
                wlan_protocol_enum_uint8     en_protocol,
                wlan_channel_band_enum_uint8 en_band)
{
    oal_uint8       uc_protocol_mode;
    oal_uint8       uc_legacy_rate;
    oal_uint32      ul_data_rate;

    switch (en_protocol)
    {
        /* 11b 1M */
        case WLAN_LEGACY_11B_MODE:
        case WLAN_MIXED_ONE_11G_MODE:
        case WLAN_HT_MODE:
            if (WLAN_BAND_2G == en_band)
            {
                uc_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0;
#ifdef _PRE_WLAN_FEATURE_P2P
                /* P2P 设备不能发送11b 速率的帧 */
                uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0xB;
#endif  /* _PRE_WLAN_FEATURE_P2P */
            }
            else
            {
                uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0xB;
            }
            break;

        /* OFDM 6M */
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
        case WLAN_VHT_MODE:
        case WLAN_HT_11G_MODE:
            uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            uc_legacy_rate   = 0xB;
            break;

        /* OFDM 24M */
        case WLAN_HT_ONLY_MODE:
        case WLAN_VHT_ONLY_MODE:
            uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            uc_legacy_rate   = 0x9;
            break;

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{dmac_vap_init_tx_data_bcast::invalid en_protocol[%d].}", en_protocol);
            return OAL_FAIL;
    }

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].ul_value = 0x0;

    /* 广播数据帧参数 */
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_tx_count           = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_stbc_mode          = 0;

    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0x3 == pst_dmac_vap->uc_vap_tx_chain))
    {
        pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
    }
#else
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
#endif
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna     = 1;

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = uc_legacy_rate;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = uc_protocol_mode;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable     = 0;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_txbf_mode          = 0;

    /* 11b 1M速率不可以使用短导码 */
    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0 == uc_legacy_rate))
    {
        pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 0;
    }

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable    = 0;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_reserve            = 0;

    ul_data_rate = pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].ul_value;

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[1].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[2].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[3].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[3].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_bcast.st_rate.bit_lsig_txop = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_vap_init_tx_mgmt_ucast
 功能描述  : 初始化单播管理帧发送速率参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_mgmt_ucast(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint32 ul_value;

    /* 初始化2.4G参数 */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode            = 0;
#endif
    if (0x3 == pst_dmac_vap->uc_vap_tx_chain)
    {
        pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = 1;
    }
    else
    {
        pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = pst_dmac_vap->uc_vap_tx_chain;
    }

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna       = 1;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable       = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode            = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable      = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_reserve              = 0;

    /* 2.4G初始化为11b 1M, long preable */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode                            = 1;
#ifdef _PRE_WLAN_FEATURE_P2P
    if (!IS_LEGACY_VAP(&(pst_dmac_vap->st_vap_base_info)))
    {
        /* P2P 设备不能发送11b 速率的帧 */
        pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0xb;  /* 6M */
        pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    }
#endif  /* _PRE_WLAN_FEATURE_P2P */

    ul_value = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].ul_value;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[1].ul_value = ul_value;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[2].ul_value = ul_value;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[3].ul_value = ul_value;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.bit_lsig_txop = OAL_FALSE;

    /* 初始化5G参数 */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode            = 0;
#endif
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = pst_dmac_vap->uc_vap_tx_chain;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna       = 1;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable       = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode            = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable      = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_reserve              = 0;

    /* 5G初始化为OFDM 6M, short preable */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0xb;  /* 6M */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode                            = 0;

    ul_value = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].ul_value;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[1].ul_value = ul_value;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[2].ul_value = ul_value;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[3].ul_value = ul_value;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.bit_lsig_txop = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_vap_init_tx_mgmt_bmcast
 功能描述  : 初始化组播、广播管理帧发送速率参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_mgmt_bmcast(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint32  ul_data_rate;

    /* 初始化2.4G参数 */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].ul_value                               = 0x0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode            = 0;
#endif
    if (0x3 == pst_dmac_vap->uc_vap_tx_chain)
    {
        pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = 1;
    }
    else
    {
        pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = pst_dmac_vap->uc_vap_tx_chain;
    }

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna       = 1;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable       = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode            = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable      = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_reserve              = 0;

    /* 2.4G初始化为11b 1M, long preable */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode                            = 1;
#ifdef _PRE_WLAN_FEATURE_P2P
    if (!IS_LEGACY_VAP(&(pst_dmac_vap->st_vap_base_info)))
    {
        /* P2P 设备不能发送11b 速率的帧 */
		/* DTS2015033002930:初始化P2P 广播管理帧发送速率和协议模式为6Mbps，OFDM  */
        pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0xb;  /* 6M */
        pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    }
#endif  /* _PRE_WLAN_FEATURE_P2P */

    ul_data_rate = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].ul_value;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[3].ul_value = ul_data_rate;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.bit_lsig_txop = OAL_FALSE;

    /* 初始化5G参数 */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].ul_value                               = 0x0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode            = 0;
#endif
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = pst_dmac_vap->uc_vap_tx_chain;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna       = 1;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable       = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode            = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable      = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_reserve              = 0;

    /* 5G初始化为OFDM 6M, short preable */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0xb;  /* 6M */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode                            = 0;

    ul_data_rate = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].ul_value;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[3].ul_value = ul_data_rate;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.bit_lsig_txop = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_vap_tx_frame_init
 功能描述  : 初始化除单播数据帧以外帧的发送速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_frame_params(dmac_vap_stru *pst_dmac_vap, oal_bool_enum_uint8  en_mgmt_rate_init_flag)
{
    wlan_protocol_enum_uint8            en_protocol;        /* 工作的协议模式 */
    wlan_channel_band_enum_uint8        en_band;            /* 频段 */

    en_protocol  = pst_dmac_vap->st_vap_base_info.en_protocol;
    en_band      = pst_dmac_vap->st_vap_base_info.st_channel.en_band;

    if (OAL_TRUE == en_mgmt_rate_init_flag)
    {
        /* 初始化单播管理帧参数 */
        dmac_vap_init_tx_mgmt_ucast(pst_dmac_vap);

        /* 初始化组播、广播管理帧参数 */
        dmac_vap_init_tx_mgmt_bmcast(pst_dmac_vap);
    }

    /* 初始化组播数据帧发送参数 */
    dmac_vap_init_tx_data_mcast(pst_dmac_vap, en_protocol, en_band);

    /* 初始化广播数据帧发送参数 */
    dmac_vap_init_tx_data_bcast(pst_dmac_vap, en_protocol, en_band);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_vap_init_tx_ucast_data_frame_params
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月7日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_ucast_data_frame(dmac_vap_stru *pst_dmac_vap)
{
    switch(pst_dmac_vap->st_vap_base_info.en_protocol)
    {
        /* BPSK 1M */
        case WLAN_LEGACY_11B_MODE:
        case WLAN_MIXED_ONE_11G_MODE:
             dmac_vap_init_tx_data_ucast(pst_dmac_vap,WLAN_11B_PHY_PROTOCOL_MODE,0);
            break;

        /* OFDM 6M*/
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
            dmac_vap_init_tx_data_ucast(pst_dmac_vap,WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE,0xB);
            break;

        /* HT MCS0*/
        case WLAN_HT_ONLY_MODE:
        case WLAN_HT_11G_MODE:
        case WLAN_HT_MODE:
            dmac_vap_init_tx_data_ucast(pst_dmac_vap,WLAN_HT_PHY_PROTOCOL_MODE,0);
        break;

        /* VHT MCS0 */
        case WLAN_VHT_MODE:
        case WLAN_VHT_ONLY_MODE:
            dmac_vap_init_tx_data_ucast(pst_dmac_vap,WLAN_VHT_PHY_PROTOCOL_MODE,0);
             break;
        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{dmac_vap_init_tx_ucast_data_frame::invalid en_protocol[%d].}", pst_dmac_vap->st_vap_base_info.en_protocol);
        return OAL_FAIL;
    }

    OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                     "{dmac_vap_init_tx_ucast_data_frame::en_protocol[%d], bit_protocol_mode:%d.}",
                     pst_dmac_vap->st_vap_base_info.en_protocol,
                     pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_vap_is_host
 功能描述  : 判断是否是master VAP,需要export_symbol
 输入参数  : pst_vap VAP结构体;
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月4日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  dmac_vap_is_host(mac_vap_stru *pst_vap)
{
    return ((dmac_vap_stru *)pst_vap)->en_is_host_vap;
}

#if 0
/*****************************************************************************
 函 数 名  : dmac_vap_get_default_ant
 功能描述  : 获取VAP下默认的天线组合，返回的是可以填写到描述符中的BITMAP
 输入参数  : pst_vap VAP结构体;
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月4日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  dmac_vap_get_default_ant(mac_vap_stru *pst_vap)
{
    return ((dmac_vap_stru *)pst_vap)->uc_default_ant_bitmap;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_vap_sta_reset
 功能描述  : STA与某个AP去关联后的复位操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_vap_sta_reset(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8   auc_bssid[WLAN_MAC_ADDR_LEN] = {0, 0, 0, 0, 0, 0};
    mac_device_stru *pst_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_vap_sta_reset::pst_device[%d] null!}", pst_dmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 恢复帧过滤寄存器 */
    //hal_disable_non_frame_filter(pst_dmac_vap->pst_hal_device);

    /* 删除BSSID */
    hal_set_sta_bssid(pst_dmac_vap->pst_hal_vap, auc_bssid);

    /* 停止STA tsf */
    hal_disable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);

    /* 恢复slottime类型为short */
    hal_cfg_slottime_type(pst_dmac_vap->pst_hal_device, 0);

    /* 恢复TXOP不使能状态 */
    if (pst_device->en_txop_enable)
    {
        pst_device->en_txop_enable = OAL_FALSE;
        hal_vap_set_machw_txop_limit_bkbe(pst_dmac_vap->pst_hal_vap,
                                          (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit,
                                          (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_pause_tx
 功能描述  : 暂停VAP, 置vap状态为pause，期望调度判断此状态: 如果为pause则停止调度
 输入参数  : mac_vap_stru *pst_vap
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_pause_tx(mac_vap_stru *pst_vap)
{
    pst_vap->en_vap_state = MAC_VAP_STATE_PAUSE;

    return  OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_vap_resume_tx
 功能描述  : 使能VAP
 输入参数  : mac_vap_stru *pst_vap
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_vap_resume_tx(mac_vap_stru *pst_vap)
{
    pst_vap->en_vap_state = MAC_VAP_STATE_UP;

    return  OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_vap_pause_tx
 功能描述  : 暂停此VAP的发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_vap_pause_tx(mac_vap_stru *pst_mac_vap)
{
    dmac_vap_stru  *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_TX, "dmac_vap_pause_tx: dmac vap is null. vap mode:%d, vap state:%d",
                        pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state);
        return;
    }

    if (MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state)
    {
        return;
    }

    mac_vap_pause_tx(pst_mac_vap);
    hal_vap_beacon_suspend(pst_dmac_vap->pst_hal_vap);
}


/*****************************************************************************
 函 数 名  : dmac_vap_pause_tx_by_chl
 功能描述  : 切信道前，暂停原信道上VAP的发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_vap_pause_tx_by_chl(mac_device_stru *pst_device, mac_channel_stru *pst_src_chl)
{
    oal_uint8               uc_vap_idx;
    mac_vap_stru           *pst_vap;

    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_vap_pause_tx_by_chl::pst_vap null, vap id is %d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (OAL_TRUE == mac_fcs_is_same_channel(&pst_vap->st_channel, pst_src_chl) && (MAC_VAP_STATE_UP == pst_vap->en_vap_state))
        {
            dmac_vap_pause_tx(pst_vap);
        }
    }
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
/*****************************************************************************
 函 数 名  : dmac_one_packet_send_null_data
 功能描述  : 通过one packet机制发送null报文
 输入参数  : pst_dmac_vap
             pst_dmac_user
 输出参数  : 无
 返 回 值  : OAL_SUCC或者其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月4日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_one_packet_send_null_data(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_ps)
{
    mac_fcs_mgr_stru               *pst_fcs_mgr;
    mac_fcs_cfg_stru               *pst_fcs_cfg;
    hal_one_packet_status_stru      st_status;

    pst_fcs_mgr = dmac_fcs_get_mgr_stru(pst_mac_device);
    pst_fcs_cfg = &pst_mac_device->st_fcs_cfg;

    OAL_MEMZERO(pst_fcs_cfg, OAL_SIZEOF(mac_fcs_cfg_stru));

    mac_fcs_prepare_one_packet_cfg(pst_mac_vap, &pst_fcs_cfg->st_one_packet_cfg, 20);
    mac_fcs_send_one_packet_start(pst_fcs_mgr, &pst_fcs_cfg->st_one_packet_cfg, pst_mac_device->pst_device_stru, &st_status, en_ps);

    /* 开关PA只需要在02的产品中打开 */
    hal_disable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(1 == pst_mac_device->pst_device_stru->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        hal_reset_phy_machw(pst_mac_device->pst_device_stru, HAL_RESET_HW_TYPE_MAC, HAL_RESET_MAC_LOGIC, OAL_FALSE, OAL_FALSE);
    }
#endif
    hal_one_packet_stop(pst_mac_device->pst_device_stru);

    hal_enable_machw_phy_and_pa(pst_mac_device->pst_device_stru);
}
#endif /* _PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV */

/*****************************************************************************
 函 数 名  : dmac_vap_resume_tx_by_chl
 功能描述  : 切信道后，恢复目的信道上VAP的发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_vap_resume_tx_by_chl(mac_device_stru *pst_device, mac_channel_stru *pst_dst_channel)
{
    dmac_vap_stru                  *pst_dmac_vap;
    oal_uint8                       uc_vap_idx;
    dmac_user_stru                 *pst_dmac_user;

#ifdef _PRE_WLAN_FEATURE_STA_PM
    mac_sta_pm_handler_stru        *pst_sta_pm_handler;
#endif
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_vap_resume_tx_by_chl::pst_dmac_vap null, vap id is %d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (OAL_TRUE == mac_fcs_is_same_channel(&(pst_dmac_vap->st_vap_base_info.st_channel), pst_dst_channel))
        {
            if (MAC_VAP_STATE_PAUSE != pst_dmac_vap->st_vap_base_info.en_vap_state)
            {
                continue;
            }

            mac_vap_resume_tx(&(pst_dmac_vap->st_vap_base_info));
            hal_vap_beacon_resume(pst_dmac_vap->pst_hal_vap);

            /* 判断目的信道上的vap模式, 如果是sta则需要发节能位置0的null data */
            if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
            {
                pst_dmac_user = mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
                if(OAL_PTR_NULL == pst_dmac_user)
                {
                    OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "{dmac_vap_resume_tx_by_chl::mac_res_get_dmac_user failed! uc_assoc_vap_id=%d. vap_mode:%d, p2p_mode:%d}",
                                            pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id,
                                            pst_dmac_vap->st_vap_base_info.en_vap_mode,
                                            mac_get_p2p_mode(&(pst_dmac_vap->st_vap_base_info)));
                    return;
                }
            #ifdef _PRE_WLAN_FEATURE_STA_PM
                pst_sta_pm_handler = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
                if (STA_GET_PM_STATE(pst_sta_pm_handler) == STA_PWR_SAVE_STATE_ACTIVE)
            #endif
                {
            #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
                    dmac_one_packet_send_null_data(pst_device, &pst_dmac_vap->st_vap_base_info, OAL_FALSE);
            #else
                    dmac_psm_send_null_data(pst_dmac_vap, pst_dmac_user, OAL_FALSE);
            #endif /* */
                }


            }
        }
    }

    dmac_tx_complete_schedule(pst_device->pst_device_stru, WLAN_WME_AC_BE);
}

/*****************************************************************************
 函 数 名  : dmac_vap_update_bi_from_hw
 功能描述  : 读取硬件beacon周期寄存器，更新mib值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月9日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_vap_update_bi_from_hw(mac_vap_stru *pst_mac_vap)
{
    /* DTS2015122404462 1151 STAUT不支持从硬件读Beacon周期，不需要此动作 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    dmac_vap_stru *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0,OAM_SF_SCAN,"{dmac_vap_update_bi_from_hw::mac_res_get_dmac_vap fail.vap_id[%u]}",pst_mac_vap->uc_vap_id);
        return;
    }

    hal_vap_get_beacon_period(pst_dmac_vap->pst_hal_vap, &(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod));
#endif

}

/*****************************************************************************
 函 数 名  : dmac_vap_is_in_p2p_listen
 功能描述  : DMAC判断是否是在p2p listen状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月18日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_vap_is_in_p2p_listen(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_vap_is_in_p2p_listen::pst_mac_device[%d] null!}", pst_mac_vap->uc_device_id);
        return OAL_FALSE;
    }

    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state) &&
         (MAC_SCAN_FUNC_P2P_LISTEN == pst_mac_device->st_scan_params.uc_scan_func))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}




/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_vap_is_host);
#if 0
oal_module_symbol(dmac_vap_get_default_ant);
#endif
oal_module_symbol(mac_vap_pause_tx);
oal_module_symbol(mac_vap_resume_tx);
oal_module_symbol(dmac_vap_pause_tx_by_chl);
oal_module_symbol(dmac_vap_resume_tx_by_chl);
oal_module_symbol(dmac_vap_update_bi_from_hw);
/*lint +e578*//*lint +e19*/









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

