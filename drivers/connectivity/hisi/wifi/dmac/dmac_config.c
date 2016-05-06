/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_config.c
  版 本 号   : 初稿
  作    者   : zourong
  生成日期   : 2013年1月8日
  最近修改   :
  功能描述   : 和配置相关的操作接口函数实现的源文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年1月8日
    作    者   : zourong
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
#include "oal_sdio_comm.h"
#include "oal_sdio.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hal_hi1102_mac.h"
#include "hal_device.h"
#endif
#include "oal_mem.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "alg_tpc.h"
#endif
#endif
#include "mac_data.h"
#include "mac_device.h"
#include "mac_ie.h"
#include "mac_regdomain.h"
#include "mac_vap.h"
#include "dmac_ext_if.h"
#include "dmac_main.h"
#include "dmac_vap.h"
#include "dmac_psm_ap.h"
#include "dmac_rx_data.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_mgmt_sta.h"
#include "dmac_tx_complete.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_uapsd.h"
#include "dmac_blockack.h"
#include "dmac_beacon.h"
#include "dmac_user.h"
#include "dmac_11i.h"
#include "dmac_wep.h"
#include "dmac_uapsd.h"
#include "dmac_acs.h"
#include "dmac_reset.h"
#include "dmac_config.h"
#include "dmac_stat.h"
#include "dmac_data_acq.h"
#include "dmac_user_track.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_txopps.h"
#include "dmac_dft.h"
#include "dmac_ap_pm.h"
#include "dmac_beacon.h"
#include "dmac_scan.h"
#include "dmac_psm_ap.h"

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
#include "cali_data.h"
#include "pm_extern.h"
#endif
#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#include "dmac_lpm_test.h"
#include "dmac_frame_filter_test.h"
#include "dmac_wmm_test.h"
#endif
#ifdef _PRE_WLAN_DFT_STAT
#include "hal_witp_phy_reg.h"
#include "hal_witp_pa_reg.h"

#include "hal_hi1102_phy_reg.h"
#include "hal_hi1102_mac_reg.h"
#endif

#ifdef _PRE_WIFI_DMT
#include "hal_witp_dmt_if.h"
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#include "pm_extern.h"
#include "dmac_sta_pm.h"
#endif

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

#include "dmac_11w.h"
#endif
#include "dmac_chan_mgmt.h"

#include "dmac_reset.h"
#include "oal_net.h"
#include "dmac_config.h"
#include "dmac_main.h"
#include "dmac_rx_filter.h"

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#include "core_cr4.h"
#endif
#include "oal_profiling.h"

#ifdef _PRE_SUPPORT_ACS
#include "dmac_acs.h"
#endif
#ifdef _PRE_WLAN_DFT_STAT
#include "mac_board.h"
#endif

#include "dmac_arp_offload.h"

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#include "dmac_auto_adjust_freq.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_CONFIG_C

mac_rssi_debug_switch_stru  g_st_rssi_debug_switch_info = {0};

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
extern oal_uint16 g_usUsedMemForStop;
extern oal_uint16 g_usUsedMemForstart;
#endif
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
extern dmac_beacon_linkloss_stru g_st_beacon_linkloss;
extern oal_uint32 g_d2h_hcc_assemble_count;
extern oal_uint32 g_ul_phy_power0_ref_2g;
extern oal_uint32 g_ul_phy_power0_ref_5g;
extern hal_customize_stru g_st_customize;
extern oal_uint8 g_auc_rate_pow_table_margin[ALG_TPC_RATE_TPC_CODE_TABLE_LEN][WLAN_BAND_BUTT];
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

/*****************************************************************************
  3 静态函数声明
*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_fbm(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_pgl(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_mtpgl(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_ta(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_ra(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_cc(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_data0(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_data1(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_data2(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_data3(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_power(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_shortgi(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_preamble_mode(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_rtscts(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_lsigtxop(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_smooth(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_snding(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_txbf(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
OAL_STATIC oal_void  dmac_config_set_dscr_stbc(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
#endif
OAL_STATIC oal_void  dmac_config_get_dscr_ess(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_dyn_bw(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_dyn_bw_exist(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_void  dmac_config_set_dscr_ch_bw_exist(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap);
OAL_STATIC oal_uint32  dmac_config_get_version(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32   dmac_config_rx_fcs_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);

#ifdef _PRE_DEBUG_MODE
OAL_STATIC oal_uint32  dmac_config_get_all_reg_value(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#if !((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))
extern oal_uint32  dmac_config_set_meta(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param);
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
extern void OML_LOG_SetLevel(oal_uint8 ucModuleID, oal_uint8 ucLevel);
#endif

#ifdef _PRE_WLAN_DFT_STAT
OAL_STATIC oal_uint32  dmac_config_report_vap_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

extern oal_void  hi1102_rf_cali_read_phy_reg_bits(
                oal_uint32          ul_reg_addr,
                oal_uint8           uc_offset,
                oal_uint8           uc_bits,
                oal_uint32         *pul_reg_val);

extern oal_void  hi1102_rf_cali_write_phy_reg_bits(
                oal_uint32          ul_reg_addr,
                oal_uint8           uc_offset,
                oal_uint8           uc_bits,
                oal_uint32          ul_reg_val);
extern oal_uint32  hi1102_rf_cali_get_scaling_addr(
                oal_uint8 uc_offset_addr_a);

#define DMAC_SET_NETBUF_CB(  evt_type, \
                            tx_usr_idx,  \
                            ismcast, \
                            is_bar,  \
                            tid)  do{\
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);\
    OAL_MEMZERO(pst_tx_ctl, OAL_NETBUF_CB_SIZE());\
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl)               = evt_type;    \
        MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)             = tx_usr_idx;   \
        MAC_GET_CB_IS_MCAST(pst_tx_ctl)             = ismcast; \
        mac_set_cb_is_bar(pst_tx_ctl, is_bar);               \
        mac_set_cb_tid(pst_tx_ctl, tid);                        \
        mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);}while(0)




OAL_STATIC dmac_set_dscr_func  g_dmac_config_set_dscr_param[] =
{
    dmac_config_set_dscr_fbm,       /* fbm, 对应发送描述符13行的freq bandwidth mode */
    dmac_config_set_dscr_pgl,       /* 已废弃 */
    dmac_config_set_dscr_mtpgl,     /* 已废弃 */
    OAL_PTR_NULL,                   /* 已废弃 */
    dmac_config_set_dscr_ta,        /* ta：tx antena，对应发送描述符15行的TXRTS Antenna */
    dmac_config_set_dscr_ra,        /* ra: rx antena, 对应发送描述符15行的RXCTRL Antenna */
    dmac_config_set_dscr_cc,        /* cc: channel code, 对应发送描述符13行的channel code */
    dmac_config_set_dscr_data0,     /* data0：对应发送描述符14行，32bit 10进制值 */
    dmac_config_set_dscr_data1,     /* data1：对应发送描述符19行， */
    dmac_config_set_dscr_data2,     /* data2：对应发送描述符20行， */
    dmac_config_set_dscr_data3,     /* data3：对应发送描述符21行， */
    dmac_config_set_dscr_power,     /* tx power: 对应发送描述符22行 */
    dmac_config_set_dscr_shortgi,         /* 配置short GI或long GI*/
    dmac_config_set_dscr_preamble_mode,   /* 配置preamble mode*/
    dmac_config_set_dscr_rtscts,         /* 配置rts/cts是否使能*/
    dmac_config_set_dscr_lsigtxop,       /* 配置lsig txop是否使能*/
    dmac_config_set_dscr_smooth,        /* 配置接收端是否对信道矩阵做平滑 */
    dmac_config_set_dscr_snding,        /* 配置Sounding模式 */
    dmac_config_set_dscr_txbf,          /* 配置txbf模式 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    dmac_config_set_dscr_stbc,          /* 配置stbc模式 */
#endif
    dmac_config_get_dscr_ess,           /* 读取扩展空间流 */
    dmac_config_set_dscr_dyn_bw,        /* 配置DYN_BANDWIDTH_IN_NON_HT */
    dmac_config_set_dscr_dyn_bw_exist,  /* 配置DYN_BANDWIDTH_IN_NON_HT exist */
    dmac_config_set_dscr_ch_bw_exist,   /* 配置CH_BANDWIDTH_IN_NON_HT exist*/
};

oal_uint32 g_ul_first_timestamp = 0;    /*记录性能统计第一次时间戳*/
/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_send_sys_event
 功能描述  : 抛事件到HMAC层, 同步HMAC数据
 输入参数  : pst_mac_vap  : VAP
             en_cfg_id: 配置id
             us_len: 消息长度
             puc_param: 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月1日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_send_sys_event(
                mac_vap_stru                     *pst_mac_vap,
                wlan_cfgid_enum_uint16            en_cfg_id,
                oal_uint16                        us_len,
                oal_uint8                        *puc_param)
{
    oal_uint32                  ul_ret;
    frw_event_mem_stru         *pst_event_mem;
    dmac_to_hmac_cfg_msg_stru  *pst_syn_msg;
    frw_event_stru             *pst_event;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_cfg_msg_stru) - 4 + us_len);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_send_sys_event::pst_event_mem null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填充事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_HOST_SDT_REG,
                        DMAC_TO_HMAC_SYN_CFG,
                        OAL_SIZEOF(dmac_to_hmac_cfg_msg_stru) - 4 + us_len,
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_mac_vap->uc_chip_id,
                        pst_mac_vap->uc_device_id,
                        pst_mac_vap->uc_vap_id);

    pst_syn_msg = (dmac_to_hmac_cfg_msg_stru *)pst_event->auc_event_data;

    DMAC_INIT_SYN_MSG_HDR(pst_syn_msg, en_cfg_id, us_len);

    /* 填写配置同步消息内容 */
    oal_memcopy(pst_syn_msg->auc_msg_body, puc_param, us_len);

    /* 抛出事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_send_sys_event::frw_event_dispatch_event failed[%d].}",ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return ul_ret;
    }

    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_fbm
 功能描述  : 设置描述符频带宽
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_fbm(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_rate.uc_channel_bandwidth = (oal_uint8)l_value;
    (WLAN_BAND_ASSEMBLE_AUTO == pst_dmac_vap->st_tx_alg.st_rate.uc_channel_bandwidth)?(pst_dmac_vap->bit_bw_cmd = 0):(pst_dmac_vap->bit_bw_cmd = 1);
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_pgl
 功能描述  : 设置描述符的power gain level字段
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_pgl(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_tx_power.bit_pa_gain_level3 = (oal_uint8)l_value;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_mtpgl
 功能描述  : 设置Micro Tx power gain level
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_mtpgl(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_tx_power.bit_pa_gain_level0 = (oal_uint8)l_value;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_ta
 功能描述  : 设置TXRTS Antenna
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_ta(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_antenna_params.uc_tx_rts_antenna = (oal_uint8)l_value;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_ra
 功能描述  : 设置RXCTRL Antenna
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_ra(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    pst_dmac_vap->st_tx_alg.st_antenna_params.uc_rx_ctrl_antenna = (oal_uint8)l_value;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_cc
 功能描述  : 设置Channel Code
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_cc(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    hal_to_dmac_device_stru         *pst_hal_device_base;
    wlan_phy_protocol_enum_uint8    en_curr_prot;

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
       OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                             "{dmac_config_set_dscr_cc::pst_hal_device_base null.}");
       return;
    }

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.en_channel_code  = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.en_channel_code = (oal_uint8)l_value;
            en_curr_prot = pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_cc::invalid frame type[%02x].}", uc_type);
            return;
    }

    /* 常发模式下在线配置 */
    if (OAL_SWITCH_ON == pst_hal_device_base->uc_al_tx_flag)
    {
       hal_set_tx_dscr_field(pst_hal_device_base, (oal_uint8)l_value, HAL_RF_TEST_CHAN_CODE);
    }

    /* 设置值回显 */
    if ((1 == l_value) && (WLAN_11B_PHY_PROTOCOL_MODE == en_curr_prot || WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE == en_curr_prot))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                         "{dmac_config_set_dscr_cc::can not set channel code to 1 in non-HT mode.}");
    }
    else if ((1 == l_value) || (0 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_cc::channel code=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_cc::invalid channel code=%d", l_value);
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_data0
 功能描述  : 设置0级速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_data0(oal_int32 l_value, oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].ul_value = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;

    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_data1
 功能描述  : 设置1级速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_data1(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[1].ul_value = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_data2
 功能描述  : 设置2级速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_config_set_dscr_data2(oal_int32 l_value, oal_uint8 uc_type,dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[2].ul_value = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_data3
 功能描述  : 设置3级速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_data3(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[3].ul_value = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_power
 功能描述  : 设置发送功率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_power(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    oal_uint32 *pul_txpower;

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_data_mcast.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_data_bcast.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg_vht.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg_ht.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg_11ag.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pul_txpower  = (oal_uint32 *)(&(pst_dmac_vap->st_tx_alg_11b.st_tx_power));
            *pul_txpower = (oal_uint32)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_shortgi
 功能描述  : 设置gi类别
 输入参数  :  l_value  : 0 long GI, 1: short GI
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : 曹海彬
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_shortgi(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
       OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                             "{dmac_config_set_dscr_cc::pst_hal_device_base null.}");
       return;
    }
#endif

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_shortgi::uc_type=%d", uc_type);
            return;
    }

#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
    /* 常发模式下在线配置 */
    if (OAL_SWITCH_ON == pst_hal_device_base->uc_al_tx_flag)
    {
       hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    if ((0 == l_value) || (1 == l_value))
    {
        pst_dmac_vap->uc_short_gi = (oal_uint8)l_value;
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_shortgi::short gi enable l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_shortgi::invalid short gi enable l_value=%d", l_value);
    }
#endif
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_preamble_mode
 功能描述  : 设置preamble_mode
 输入参数  :
             Protocol mode：11b
               0: 11b Short Preamble
               1: 11b Long Preamble
             Protocol mode：legacy OFDM
               0: legacy OFDM tx format
               1: reserved
             Protocol mode：HT
               0: HT Mixed Mode Frame
               1: HT Green Field Frame
             Protocol mode：VHT
               0: VHT Preamble
               1: reserved
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : 曹海彬
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_preamble_mode(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
        hal_to_dmac_device_stru         *pst_hal_device_base;

        pst_hal_device_base = pst_dmac_vap->pst_hal_device;
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
        {
           OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                                 "{dmac_config_set_dscr_cc::pst_hal_device_base null.}");
           return;
        }
#endif

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_preamble_mode::invalid frame type=%d", uc_type);
            return;
    }

#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
	/* 常发模式下在线配置 */
    if (OAL_SWITCH_ON == pst_hal_device_base->uc_al_tx_flag)
    {
       hal_set_tx_dscr_field(pst_hal_device_base, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_preamble_mode::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_preamble_mode::invalid l_value=%d", l_value);
    }
#endif
}


/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_rtscts
 功能描述  : 设置rts cts enable
 输入参数  :  l_value  : 0 long GI, 1: short GI
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : 曹海彬
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_rtscts(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = (oal_uint8)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_lsigtxop
 功能描述  : 设置lsig txop
 输入参数  :  l_value  : 0 lsig txop diable, 1: lsig txop enable
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月29日
    作    者   : 曹海彬
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_lsigtxop(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.bit_lsig_txop = (oal_uint8)l_value;
            break;
    #endif

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_smooth
 功能描述  : 设置smoothing
 输入参数  :  l_value  : 0 smoothing is not recommended,
                         1 smoothing is recommended
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 杨桂森
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_smooth(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.uc_smoothing  = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.uc_smoothing = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_smooth::invalid frame type=%d", uc_type);
            return;
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_smooth::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_smooth::invalid l_value=%d", l_value);
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_snding
 功能描述  : 设置sounding模式
 输入参数  :  l_value  : 0: no sounding             1: NDP sounding
                         2: staggered sounding      3: legacy sounding
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 杨桂森
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_snding(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.en_sounding_mode  = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.en_sounding_mode = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_snding::invalid frame type=%d", uc_type);
            return;
    }

    /* 打印TX描述符 */
    if ((l_value >= 0) && (l_value <= 3))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_snding::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_snding::invalid l_value=%d", l_value);
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_txbf
 功能描述  : 设置TXBF
 输入参数  :  l_value  : 0: Non TXBF                1: Explicit TXBF
                         2: 用户无感知TXBF          3: Reserved
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 杨桂森
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_txbf(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode  = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_txbf_mode = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_txbf::invalid frame type=%d", uc_type);
            return;
    }

    /* 打印TX描述符 */
    if ((l_value >= 0) && (l_value <= 3))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_txbf::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_txbf::invalid l_value=%d", l_value);
    }
}
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_stbc
 功能描述  : 设置STBC
 输入参数  :  l_value  : 0: 不采用STBC              1: Nsts - Nss = 1
                         2: Nsts - Nss = 2          3: Reserved
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 杨桂森
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_stbc(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode  = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_stbc::invalid frame type=%d", uc_type);
            return;
    }

    /* 打印TX描述符 */
    if ((l_value >= 0) && (l_value <= 3))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_stbc::l_valuee=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_stbc::invalid l_value=%d", l_value);
    }
}
#endif
/*****************************************************************************
 函 数 名  : dmac_config_get_dscr_ess
 功能描述  : 读取TX描述符中扩展空间流
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 杨桂森
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_get_dscr_ess(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8   uc_ess_num;

    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_data_mcast.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_data_bcast.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            uc_ess_num = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            uc_ess_num = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            uc_ess_num = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            uc_ess_num = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.uc_extend_spatial_streams;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg_vht.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg_ht.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg_11ag.st_rate.uc_extend_spatial_streams;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            uc_ess_num = pst_dmac_vap->st_tx_alg_11b.st_rate.uc_extend_spatial_streams;
            break;
    #endif

        default:
            uc_ess_num = 0;
            break;
    }

    /* 打印TX描述符 */
    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_get_dscr_ess::uc_ess_num=%d", uc_ess_num);
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_dyn_bw
 功能描述  : 设置STBC
 输入参数  :  l_value  : 0: not present
                         1: present
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 杨桂森
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_dyn_bw(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.dyn_bandwidth_in_non_ht  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.dyn_bandwidth_in_non_ht   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.dyn_bandwidth_in_non_ht   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.dyn_bandwidth_in_non_ht   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.dyn_bandwidth_in_non_ht   = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.dyn_bandwidth_in_non_ht = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw::invalid frame type=%d", uc_type);
            return;
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw::invalid l_value=%d", l_value);
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_dyn_bw_exist
 功能描述  : 设置STBC
 输入参数  :  l_value  : 0: no existance
                         1: existance
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 杨桂森
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_dyn_bw_exist(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.dyn_bandwidth_in_non_ht_exist  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.dyn_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.dyn_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.dyn_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.dyn_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.dyn_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw_exist::invalid frame type=%d", uc_type);
            return;
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw_exist::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_dyn_bw_exist::invalid l_value=%d", l_value);
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dscr_ch_bw_exist
 功能描述  : 设置STBC
 输入参数  :  l_value  : 0: no existance
                         1: existance
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月1日
    作    者   : 杨桂森
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_dscr_ch_bw_exist(oal_int32 l_value,oal_uint8 uc_type, dmac_vap_stru *pst_dmac_vap)
{
    switch (uc_type)
    {
        case MAC_VAP_CONFIG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MCAST_DATA:
            pst_dmac_vap->st_tx_data_mcast.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_BCAST_DATA:
            pst_dmac_vap->st_tx_data_bcast.st_rate.ch_bandwidth_in_non_ht_exist  = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.ch_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_UCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.ch_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_2G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.ch_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_MBCAST_MGMT_5G:
            pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.ch_bandwidth_in_non_ht_exist   = (oal_uint8)l_value;
            break;
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        case MAC_VAP_CONFIG_VHT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_vht.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_HT_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_ht.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11AG_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11ag.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
        case MAC_VAP_CONFIG_11B_UCAST_DATA:
            pst_dmac_vap->st_tx_alg_11b.st_rate.ch_bandwidth_in_non_ht_exist = (oal_uint8)l_value;
            break;
    #endif

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_ch_bw_exist::invalid frame type=%d", uc_type);
            return;
    }

    if ((0 == l_value) || (1 == l_value))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_ch_bw_exist::l_value=%d", l_value);
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr_ch_bw_exist::invalid l_valueype=%d", l_value);
    }
}

/*****************************************************************************
 函 数 名  : dmac_get_cmd_one_arg
 功能描述  : 获取字符串第一个参数 以空格为参数区分标识
 输入参数  : pc_cmd         : 传入的字符串
 输出参数  : pc_arg         : 第一个参数
             pul_cmd_offset : 第一个参数的长度
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月13日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_get_cmd_one_arg(oal_int8 *pc_cmd, oal_int8 *pc_arg, oal_uint32 *pul_cmd_offset)
{
    oal_int8   *pc_cmd_copy;
    oal_uint32  ul_pos = 0;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pc_cmd) || (OAL_PTR_NULL == pc_arg) || (OAL_PTR_NULL == pul_cmd_offset)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_CFG,
                       "{dmac_get_cmd_one_arg::param null, pc_cmd=%d pc_arg=%d pul_cmd_offset=%d.}",
                       pc_cmd, pc_arg, pul_cmd_offset);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pc_cmd_copy = pc_cmd;

    /* 去掉字符串开始的空格 */
    while (' ' == *pc_cmd_copy)
    {
        ++pc_cmd_copy;
    }

    while ((' ' != *pc_cmd_copy) && ('\0' != *pc_cmd_copy))
    {
        pc_arg[ul_pos] = *pc_cmd_copy;
        ++ul_pos;
        ++pc_cmd_copy;

        if (OAL_UNLIKELY(ul_pos >= DMAC_HIPRIV_CMD_NAME_MAX_LEN))
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_get_cmd_one_arg::ul_pos=%d", ul_pos);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }

    pc_arg[ul_pos]  = '\0';

    /* 字符串到结尾，返回错误码 */
    if (0 == ul_pos)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_get_cmd_one_arg::ul_pos=0.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    *pul_cmd_offset = (oal_uint32)(pc_cmd_copy - pc_cmd);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_reg_display_test
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_reg_display_test(mac_vap_stru *pst_mac_vap, oal_uint32 ul_start_addr, oal_uint32 ul_end_addr)
{
    mac_device_stru      *pst_device;
    oal_uint32            ul_addr;
    oal_uint32            ul_val = 0;

    if (ul_start_addr % 4 != 0 || ul_end_addr % 4 != 0)
    {
        return;
    }

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        return;
    }

    for (ul_addr = ul_start_addr; ul_addr <= ul_end_addr; ul_addr += 4)
    {
        hal_reg_info(pst_device->pst_device_stru, ul_addr, &ul_val);
        OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_display_test::reg_info addr=0x%08x, value=0x%08x", ul_addr, ul_val);
        OAL_IO_PRINT("dmac_config_reg_display_test::reg_info addr=0x%08x, value=0x%08x\r\n", ul_addr, ul_val);
    }
}



/*****************************************************************************
 函 数 名  : dmac_config_reg_display_test16
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_reg_display_test16(mac_vap_stru *pst_mac_vap, oal_uint32 ul_start_addr, oal_uint32 ul_end_addr)
{
    mac_device_stru      *pst_device;
    oal_uint32            ul_addr;
    oal_uint16            us_val = 0;

    if (ul_start_addr % 2 != 0 || ul_end_addr % 2 != 0)
    {
        OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_display_test16::not mod 2, start[%08x], end[%08x].", ul_start_addr, ul_end_addr);
        return;
    }

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_reg_display_test16::pst_device null.");
        return;
    }

    for (ul_addr = ul_start_addr; ul_addr <= ul_end_addr; ul_addr += 2)
    {
        hal_reg_info16(pst_device->pst_device_stru, ul_addr, &us_val);
        OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_display_test::reg_info addr=0x%08x, value=0x%08x", ul_addr, us_val);
        OAL_IO_PRINT("dmac_config_reg_display_test::reg_info addr=0x%08x, value=0x%08x\r\n", ul_addr, us_val);
    }
}



/*****************************************************************************
 函 数 名  : dmac_config_reg_write_test
 功能描述  : 写寄存器，包含PHY,SOC,MAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_reg_write_test(mac_vap_stru *pst_mac_vap, oal_uint32 ul_addr, oal_uint32 ul_val)
{
    mac_device_stru      *pst_device;
    oal_int8              ac_buf[64] = {0};

    if (ul_addr % 4 != 0)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_reg_write_test::ul_addr=%d", ul_addr);
        return;
    }

    OAL_SPRINTF((char*)ac_buf, OAL_SIZEOF(ac_buf), "reg_write:addr=0x%08x, val=0x%08x.\n", ul_addr, ul_val);
    OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_write_test::reg_write:addr=0x%08x, val=0x%08x.", ul_addr, ul_val);
    oam_print(ac_buf);

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        return;
    }

    hal_reg_write(pst_device->pst_device_stru, ul_addr, ul_val);
}

/*****************************************************************************
 函 数 名  : dmac_config_reg_write_test16
 功能描述  : 写寄存器，包含PHY,SOC,MAC
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_reg_write_test16(mac_vap_stru *pst_mac_vap, oal_uint32 ul_addr, oal_uint16 us_val)
{
    mac_device_stru      *pst_device;
    oal_int8              ac_buf[64] = {0};

    if (ul_addr % 2 != 0)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_reg_write_test::ul_addr=%d", ul_addr);
        return;
    }

    OAL_SPRINTF((char*)ac_buf, OAL_SIZEOF(ac_buf), "reg_write:addr=0x%08x, val=0x%04x.\n", ul_addr, us_val);
    OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_reg_write_test::reg_write:addr=0x%08x, val=0x%04x.", ul_addr, us_val);
    oam_print(ac_buf);

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        return;
    }

    hal_reg_write16(pst_device->pst_device_stru, ul_addr, us_val);
}

/*****************************************************************************
 函 数 名  : dmac_config_set_bss_type
 功能描述  : 设置bss type
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* 设置mib值 */
    return mac_mib_set_bss_type(pst_mac_vap, uc_len, puc_param);
}


#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
/*****************************************************************************
 函 数 名  : dmac_config_get_hipkt_stat
 功能描述  : 获取高优先级报文的统计情况
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_hipkt_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_get_hipkt_stat();

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_set_mode
 功能描述  : 设置模式 包括协议 频段 带宽
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : zhangheng
    修改内容   : 新生成函数
  1.日    期   : 2015年5月5日
    作    者   : g00260350
    修改内容   : 函数整改，dmac配置流程应该是
                           1、参数校验并设置mac vap及mib的信息(使用offload宏)
                           2、设置mac device下的信息(使用offload宏)
                           2、设置dmac vap信息并设置hal接口，配置寄存器
*****************************************************************************/
oal_uint32  dmac_config_set_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_mode_param_stru     *pst_prot_param;
    dmac_vap_stru               *pst_dmac_vap;
    mac_device_stru             *pst_mac_device;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_mode::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mode::pst_mac_device null.}");
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    /* 获取dmac vap结构体 */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_TXBF, "{dmac_config_set_mode::pst_dmac_vap null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    #if 0 // gaolin：ACS运行之后，会设置不同的信道，DMAC不能旁路，否则导致系band和channel错位
    /* 已经配置过时，不需要再配置*/
    if (WLAN_BAND_WIDTH_BUTT != pst_mac_device->en_max_bandwidth)
    {
        return OAL_SUCC;
    }
    #endif

    pst_prot_param = (mac_cfg_mode_param_stru *)puc_param;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 记录协议模式, band, bandwidth到mac_vap下 */
    pst_mac_vap->en_protocol                              = pst_prot_param->en_protocol;
    pst_mac_vap->st_channel.en_band                       = pst_prot_param->en_band;
    pst_mac_vap->st_channel.en_bandwidth                  = pst_prot_param->en_bandwidth;
    pst_mac_vap->st_ch_switch_info.en_user_pref_bandwidth = pst_prot_param->en_bandwidth;

#ifdef _PRE_WLAN_FEATURE_11AC2G
    if ((WLAN_VHT_MODE == pst_mac_vap->en_protocol)
        && (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band))
    {
        mac_vap_set_11ac2g(pst_mac_vap, OAL_TRUE);
    }
    else
    {
        mac_vap_set_11ac2g(pst_mac_vap, OAL_FALSE);
    }
#endif



    /* 根据协议更新vap能力 */
    mac_vap_init_by_protocol(pst_mac_vap, pst_prot_param->en_protocol);

    /* 根据带宽信息更新Mib */
    mac_vap_change_mib_by_bandwidth(pst_mac_vap, pst_prot_param->en_bandwidth);

    /* 更新device的频段及最大带宽信息 */
    pst_mac_device->en_max_bandwidth = pst_prot_param->en_bandwidth;
    pst_mac_device->en_max_band      = pst_prot_param->en_band;

#endif
#ifdef _PRE_WLAN_FEATURE_TXBF
    if ((pst_mac_vap->en_protocol >= WLAN_HT_MODE)
        && (OAL_TRUE == pst_mac_device->bit_su_bfmee))
    {
        pst_mac_vap->st_cap_flag.bit_11ntxbf = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->st_cap_flag.bit_11ntxbf = OAL_FALSE;
    }
#endif


    if (pst_mac_vap->en_protocol < WLAN_HT_MODE)
    {
        pst_dmac_vap->en_bfee_actived       = OAL_FALSE;
        pst_dmac_vap->en_bfer_actived       = WLAN_BFER_ACTIVED;
        pst_dmac_vap->en_mu_bfee_actived    = OAL_FALSE;
        pst_dmac_vap->en_txstbc_actived     = OAL_FALSE;
    }
    else
    {
        pst_dmac_vap->en_bfee_actived       = OAL_TRUE;
        pst_dmac_vap->en_bfer_actived       = WLAN_BFER_ACTIVED;
        pst_dmac_vap->en_mu_bfee_actived    = OAL_TRUE;
        pst_dmac_vap->en_txstbc_actived     = WLAN_TXSTBC_ACTIVED;
#ifdef _PRE_WLAN_FEATURE_TXOPPS
        if (pst_mac_vap->en_protocol == WLAN_VHT_MODE ||
             pst_mac_vap->en_protocol == WLAN_VHT_ONLY_MODE)
        {
            pst_dmac_vap->en_mu_bfee_actived   = WLAN_MU_BFEE_ACTIVED;
        }
#endif
    }

    hal_disable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

    /* 调hal接口设置频段 */
    hal_set_freq_band(pst_mac_device->pst_device_stru, pst_prot_param->en_band);
#if 0
#ifdef _PRE_WLAN_FEATURE_DFS
    /* mayuan DFS begin */
    /* 关闭雷达检测，定时器超时后在打开 */
    if (WLAN_BAND_5G == pst_prot_param->en_band)
    {
        if (0 != pst_mac_device->us_dfs_timeout)
        {
            hal_enable_radar_det(pst_mac_device->pst_device_stru, 0);
            /* 启动定时器 */
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_dfs.st_dfs_radar_timer,
                                   dmac_mgmt_scan_dfs_timeout,
                                   pst_mac_device->us_dfs_timeout,
                                   pst_mac_device,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
        }
    }
    /* mayuan DFS end */
#endif
#endif
    /* 调hal接口设置带宽 */
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    /*dummy*/
#else
    if (pst_prot_param->en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_config_set_mode:: fpga is not support 80M.}\r\n");
        pst_prot_param->en_bandwidth = WLAN_BAND_WIDTH_20M;
    }
#endif
    hal_set_bandwidth_mode(pst_mac_device->pst_device_stru, pst_prot_param->en_bandwidth);

    hal_enable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

    /* 通知算法 */
    dmac_alg_cfg_bandwidth_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_mac_addr
 功能描述  : dmac设置mac地址
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_mac_addr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_staion_id_param_stru  *pst_param;
    dmac_vap_stru                 *pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_device_stru               *pst_mac_device;
    hal_to_dmac_device_stru       *pst_hal_device;
#endif

    pst_param = (mac_cfg_staion_id_param_stru *)puc_param;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P 设置MAC 地址mib 值需要区分P2P DEV 或P2P_CL/P2P_GO,P2P_DEV MAC 地址设置到p2p0 MIB 中 */
    if (pst_param->en_p2p_mode == WLAN_P2P_DEV_MODE)
    {
        /* 如果是p2p0 device，则配置MAC 地址到auc_p2p0_dot11StationID 成员中 */
        oal_set_mac_addr(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID,
                        pst_param->auc_station_id);
    }
    else
#endif
    {
        /* 设置mib值, Station_ID */
        mac_mib_set_station_id(pst_mac_vap, OAL_SIZEOF(mac_cfg_staion_id_param_stru), puc_param);
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{dmac_config_set_mac_addr::mac_res_get_dev pst_mac_device null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* 设置mib值, Station_ID */
            mac_mib_set_station_id(pst_mac_vap, OAL_SIZEOF(mac_cfg_staion_id_param_stru), puc_param);

            /* 将Proxy STA的mac 地址写入到peer addr 寄存器中,这样hal_vap_id与Proxy STA的mac_addr是相对应的 */
            hal_set_proxysta_vap_addr(pst_hal_device, pst_dmac_vap->pst_hal_vap->uc_vap_id, mac_mib_get_StationID(pst_mac_vap));
        }
        else if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* 将main proxysta(sta0)的地址写入 mac_device_stru中 */
            oal_set_mac_addr(pst_mac_device->st_device_proxysta.auc_mac_addr, pst_param->auc_station_id);

            /* hal设置mac地址 */
            hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_param->auc_station_id);
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,"{dmac_config_set_mac_addr::set main proxysta mac addr succ!}");
        }
        else
        {
            /* hal设置mac地址 */
            hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_param->auc_station_id);
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,"{dmac_config_set_mac_addr::set mac addr succ!}");

        }
    }
    else
    {
        /* hal设置mac地址 */
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_param->auc_station_id);
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA,"{dmac_config_set_mac_addr::set mac addr succ!}");
    }
#else
    /* hal设置mac地址 */
#ifdef _PRE_WLAN_FEATURE_P2P
    if (pst_param->en_p2p_mode == WLAN_P2P_DEV_MODE)
    {
        /* 设置p2p0 网络地址，需要设置到p2p0_hal_vap 中，其他类型MAC 地址设置到hal_vap 中 */
        hal_vap_set_macaddr(pst_dmac_vap->pst_p2p0_hal_vap, pst_param->auc_station_id);
    }
    else
#endif
    {
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_param->auc_station_id);
    }
    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"{dmac_config_set_mac_addr::set mac addr succ!}");
#endif


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_freq
 功能描述  : 设置信道
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_freq(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32               l_value;
    mac_device_stru        *pst_mac_device;
    oal_uint8               uc_channel_idx;
    oal_uint32              ul_ret;
#ifdef _PRE_WLAN_HW_TEST
    mac_cfg_mode_param_stru     st_prot_param;
    oal_uint8                   uc_msg_len = 0;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_cfg_channel_param_stru l_channel_param;
#endif

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_freq::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    l_value = *((oal_int32 *)puc_param);



#ifdef _PRE_WIFI_DMT
    if (l_value >= 36)
    {
        g_ul_dmt_scan_flag = 1;   /* DMT用例扫描根据信道进行扫描，而不进行全信道扫描   */
    }
#endif

    ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, (oal_uint8)l_value, &uc_channel_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                       "{dmac_config_set_freq::mac_get_channel_idx_from_num failed[%d], band[%d], channel num[%d].}", ul_ret, pst_mac_vap->st_channel.en_band, (oal_uint8)l_value);
        return ul_ret;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mac_vap->st_channel.uc_chan_number = (oal_uint8)l_value;
    pst_mac_vap->st_channel.uc_idx         = uc_channel_idx;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#if 0
    pst_mac_device->uc_max_channel = (oal_uint8)l_value;    /* hi1102-cb allways set at both side */
#else
    mac_device_get_channel(pst_mac_device, &l_channel_param);
    l_channel_param.uc_channel = (oal_uint8)l_value;
    mac_device_set_channel(pst_mac_device, &l_channel_param);
#endif

#endif

    /* 通知算法 */
    dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

    hal_disable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    /* 调用hal接口设置信道号 */
    hal_set_primary_channel(pst_mac_device->pst_device_stru,
                           (oal_uint8)l_value,
                            pst_mac_vap->st_channel.en_band,
                            uc_channel_idx,
                            pst_mac_vap->st_channel.en_bandwidth);
#else
    if (pst_mac_vap->st_channel.en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_config_set_freq:: fpga is not support 80M.}\r\n");
        /* 调用hal接口设置信道号 */
        hal_set_primary_channel(pst_mac_device->pst_device_stru,
                                (oal_uint8)l_value,
                                pst_mac_vap->st_channel.en_band,
                                uc_channel_idx,
                                WLAN_BAND_WIDTH_20M);
    }
    else
    {
        /* 调用hal接口设置信道号 */
        hal_set_primary_channel(pst_mac_device->pst_device_stru,
                                (oal_uint8)l_value,
                                pst_mac_vap->st_channel.en_band,
                                uc_channel_idx,
                                pst_mac_vap->st_channel.en_bandwidth);
    }
#endif

    hal_enable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

#ifdef _PRE_WLAN_DFT_EVENT
    oam_event_chan_report((oal_uint8)l_value);
#endif

#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_RX_RESERVED == pst_mac_device->pst_device_stru->bit_al_rx_flag)
    {
        if (WLAN_BAND_2G == (pst_mac_vap->st_channel.en_band) && (WLAN_VHT_MODE == pst_mac_vap->en_protocol))
        {
            hal_set_phy_tx_scale(pst_mac_device->pst_device_stru, OAL_TRUE);

            st_prot_param.en_band       = pst_mac_vap->st_channel.en_band;
            st_prot_param.en_bandwidth  = pst_mac_vap->st_channel.en_bandwidth;
            st_prot_param.en_protocol   = pst_mac_vap->en_protocol;

            dmac_config_set_mode(pst_mac_vap, uc_msg_len, (oal_uint8 *)&st_prot_param);
        }
        else
        {
            hal_set_phy_tx_scale(pst_mac_device->pst_device_stru, OAL_FALSE);
        }
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_concurrent
 功能描述  : dmac 设置设备并发用户数
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_concurrent(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32  l_value;

    l_value = *((oal_int32 *)puc_param);

    mac_res_set_max_asoc_user((oal_uint16)l_value);

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_concurrent::l_value=%d.}", l_value);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_ssid
 功能描述  : 设置ssid
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* 设置mib值 */
    return mac_mib_set_ssid(pst_mac_vap, uc_len, puc_param);
}

/*****************************************************************************
 函 数 名  : dmac_config_stop_sched_scan
 功能描述  : 停止PNO调度扫描
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_stop_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                         *pst_mac_device;
    mac_pno_sched_scan_mgmt_stru            *pst_pno_scan_mgmt;

    /* 获取mac device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_config_stop_sched_scan::pst_mac_device is null.}");
        return OAL_FAIL;
    }

    /* 判断pno是否已经停止，如果停止，则pno扫描的管理结构体指针为null */
    if (OAL_PTR_NULL == pst_mac_device->pst_pno_sched_scan_mgmt)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_config_stop_sched_scan::pno sched scan already stop.}");
        return OAL_SUCC;
    }

    /* 获取pno扫描管理结构体 */
    pst_pno_scan_mgmt = pst_mac_device->pst_pno_sched_scan_mgmt;

    /* 删除PNO调度扫描定时器 */
    dmac_scan_stop_pno_sched_scan_timer((void *)pst_pno_scan_mgmt);

    /* 停止本次PNO调度扫描并调用一次扫描结束 */
    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state) &&
        (WLAN_SCAN_MODE_BACKGROUND_PNO == pst_mac_device->st_scan_params.en_scan_mode))
    {
        /* 删除扫描定时器 */
        if (OAL_TRUE == pst_mac_device->st_scan_timer.en_is_registerd)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_mac_device->st_scan_timer);
        }
        dmac_scan_end(pst_mac_device);

        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_stop_sched_scan::stop pno scan.}");

        /* 设置扫描状态为空闲 */
        pst_mac_device->en_curr_scan_state = MAC_SCAN_STATE_IDLE;
    }

    /* 释放PNO管理结构体内存 */
    OAL_MEM_FREE(pst_mac_device->pst_pno_sched_scan_mgmt, OAL_TRUE);
    pst_mac_device->pst_pno_sched_scan_mgmt = OAL_PTR_NULL;

    //OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_stop_sched_scan::go last.}");

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_scan_abort
 功能描述  : 扫描终止
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_scan_abort(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru     *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_scan_abort::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 如果扫描正在进行则停止扫描 */
    if (MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_scan_abort::stop scan.}");
        dmac_scan_abort(pst_mac_device);
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
 函 数 名  : dmac_config_set_shortgi       for hi1102-cb add sync
 功能描述  : 设置 shortgi
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : c00280521
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_shortgi(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    shortgi_cfg_stru    *shortgi_cfg;

    shortgi_cfg = (shortgi_cfg_stru *)puc_param;

    switch(shortgi_cfg->uc_shortgi_type)
    {
        case SHORTGI_20_CFG_ENUM:

            if (0 != shortgi_cfg->uc_enable)
            {
                pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented = OAL_TRUE;
            }
            else
            {
                pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented = OAL_FALSE;
            }
            break;

        case SHORTGI_40_CFG_ENUM:

            if (0 != shortgi_cfg->uc_enable)
            {
                pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInFortyImplemented = OAL_TRUE;
            }
            else
            {
                pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInFortyImplemented = OAL_FALSE;
            }
            break;

        case SHORTGI_80_CFG_ENUM:

            if (0 != shortgi_cfg->uc_enable)
            {
                pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented = OAL_TRUE;
            }
            else
            {
                pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented = OAL_FALSE;
            }
            break;
        default:
            break;

    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_vap_state_syn
 功能描述  : 复位硬件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_vap_state_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
//#if defined(_PRE_WLAN_FEATURE_STA_PM) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
    dmac_vap_stru *pst_dmac_vap;
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_vap_state_syn::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

//#endif

    //OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_vap_state_syn::uc_len = %d, en state = %d.}", uc_len, *puc_param);

    /* 同步vap状态 */
    //if (!(IS_P2P_CL(pst_mac_vap) && (pst_mac_vap->us_user_nums > 0)))
    {
        pst_mac_vap->en_vap_state = (mac_vap_state_enum_uint8)(*puc_param);
    }

    /* STA 模式下只有UP状态才开启keepalive定时器 */
    if ((MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state)
        && (pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_STA))
    {
#ifdef _PRE_WLAN_FEATURE_STA_PM
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_KEEPALIVE, 0, OAL_PTR_NULL);
#endif
    }
    /* STA 模式下只有UP状态才开启keepalive定时器 */
    if ((MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state)
    && (pst_mac_vap->en_vap_mode == WLAN_VAP_MODE_BSS_STA))
    {
        /* 此时关闭keepalive */
        pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_keepalive   =  OAL_FALSE;

    }

    /* 20/40共存逻辑开启时，判断是否启动obss扫描定时器 */
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    /* STA模式，才需要obss扫描定时器开启定时器 */
    if ((OAL_TRUE == dmac_mgmt_need_obss_scan(pst_mac_vap)) &&
         (OAL_FALSE == pst_dmac_vap->uc_obss_scan_timer_started) )
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{dmac_config_vap_state_syn:: start obss scan}");
        dmac_scan_start_obss_timer(pst_mac_vap);
    }
    //else if (OAL_TRUE == pst_dmac_vap->uc_obss_scan_timer_started)
    //{
    //    OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_config_vap_state_syn:: obss scan timer already started}");
    //}
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_stbc_cap
 功能描述  : 设置stbc能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月24日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_stbc_cap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    oal_bool_enum_uint8   uc_value;

    uc_value = (oal_bool_enum_uint8)*puc_param;

    if (uc_value > 1)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_stbc_cap::stbc_value is limit! value = [%d].}", uc_value);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionImplemented                = uc_value;
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11RxSTBCOptionImplemented                = uc_value;
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionActivated                  = uc_value;
    pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTTxSTBCOptionImplemented   = uc_value;
    pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTRxSTBCOptionImplemented   = uc_value;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_ldpc_cap
 功能描述  : 设置stbc能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月24日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_ldpc_cap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_bool_enum_uint8   uc_value;

    uc_value = (oal_bool_enum_uint8)(*puc_param);

    if (uc_value > 1)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_ldpc_cap::ldpc_value is limit! value = [%d].}\r\n", uc_value);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionImplemented                = uc_value;
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionActivated                  = uc_value;
    pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTLDPCCodingOptionImplemented   = uc_value;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_STA_PM
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
/*****************************************************************************
 函 数 名  : dmac_config_set_uapsd_para
 功能描述  : uapsd 信息同步
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月4日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_uapsd_para(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_uapsd_sta_stru   *pst_uapsd_info = (mac_cfg_uapsd_sta_stru *)puc_param;

    /* uc_max_sp_len */
    if (pst_uapsd_info->uc_max_sp_len > 6)
    {
       OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_set_uapsd_para::uc_max_sp_len[%d] > 6!}\r\n", pst_uapsd_info->uc_max_sp_len);
       return OAL_FAIL;
    }

    mac_vap_set_uapsd_para(pst_mac_vap, pst_uapsd_info);

    return OAL_SUCC;
}
#endif
#endif
#endif  /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC */

/*****************************************************************************
 函 数 名  : dmac_config_user_asoc_state_syn
 功能描述  : 复位硬件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_user_asoc_state_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    mac_h2d_user_asoc_state_stru *pst_user_asoc_info;
    mac_user_stru                *pst_mac_user;

    pst_user_asoc_info = (mac_h2d_user_asoc_state_stru *)puc_param;

    OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_user_asoc_state_syn::us_user_idx = %d, user state = %d.}",
                  pst_user_asoc_info->us_user_idx, pst_user_asoc_info->en_asoc_state);

    /* 获取DMAC模块用户结构体 */
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_user_asoc_info->us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_user_asoc_state_syn::pst_mac_user null.user idx [%d]}", pst_user_asoc_info->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 同步user关联状态 */
    mac_user_set_asoc_state(pst_mac_user, pst_user_asoc_info->en_asoc_state);
#endif
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_user_cap_syn
 功能描述  : 同步mac user的能力信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月11日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_user_cap_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_stru              *pst_mac_user;
    mac_h2d_usr_cap_stru       *pst_mac_h2d_usr_cap;

    pst_mac_h2d_usr_cap = (mac_h2d_usr_cap_stru *)puc_param;
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_h2d_usr_cap->us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_user_cap_syn::pst_mac_user null.user idx [%d]}", pst_mac_h2d_usr_cap->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }


#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    dmac_11w_update_users_status((dmac_vap_stru *)pst_mac_vap, pst_mac_user, pst_mac_h2d_usr_cap->st_user_cap_info.bit_pmf_active);
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

    oal_memcopy(&pst_mac_user->st_cap_info, &pst_mac_h2d_usr_cap->st_user_cap_info, OAL_SIZEOF(mac_h2d_usr_cap_stru));

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_config_btcoex_assoc_state_syn(pst_mac_vap, pst_mac_user);
#endif
#endif /* (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) */
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_user_rate_info_syn
 功能描述  : 同步速率信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月26日
    作    者   : j00196483
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_user_rate_info_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    mac_h2d_usr_rate_info_stru        *pst_usr_info;
    dmac_user_stru                    *pst_dmac_user;

    if (OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_user_rate_info_syn::the input is null pointer.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_usr_info = (mac_h2d_usr_rate_info_stru *)puc_param;


    /* 获取DMAC模块用户结构体 */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_usr_info->us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_user_rate_info_syn::pst_dmac_user null.user idx [%d]}", pst_usr_info->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_set_protocol_mode(&(pst_dmac_user->st_user_base_info), pst_usr_info->en_protocol_mode);

    /* 同步legacy速率集信息 */
    mac_user_set_avail_op_rates(&pst_dmac_user->st_user_base_info, pst_usr_info->uc_avail_rs_nrates, pst_usr_info->auc_avail_rs_rates);

    /* 同步ht速率集信息 */
    mac_user_set_ht_hdl(&pst_dmac_user->st_user_base_info, &pst_usr_info->st_ht_hdl);

    /* 同步vht速率集信息 */
    mac_user_set_vht_hdl(&pst_dmac_user->st_user_base_info, &pst_usr_info->st_vht_hdl);

    /* 信息同步后续处理 */
    if (pst_dmac_user->st_user_base_info.st_vht_hdl.bit_vht_txop_ps)
    {
        pst_mac_vap->st_cap_flag.bit_txop_ps = OAL_TRUE;
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_sta_usr_info_syn
 功能描述  : 复位硬件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_sta_usr_info_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_h2d_usr_info_stru   *pst_usr_info;
    mac_user_stru           *pst_mac_user;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_ht_hdl_stru     st_ht_hdl;
#endif
    pst_usr_info = (mac_h2d_usr_info_stru *)puc_param;

    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_usr_info->us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_sta_usr_info_syn::pst_mac_user null.user idx [%d]}", pst_usr_info->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 更新mac地址，漫游时mac会更新 */
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        oal_set_mac_addr(pst_mac_user->auc_user_mac_addr, pst_mac_vap->auc_bssid);
    }

    /* 同步USR带宽 */
    mac_user_set_bandwidth_cap(pst_mac_user, pst_usr_info->en_bandwidth_cap);
    mac_user_set_bandwidth_info(pst_mac_user, pst_usr_info->en_avail_bandwidth, pst_usr_info->en_cur_bandwidth);

    mac_user_get_ht_hdl(pst_mac_user, &st_ht_hdl);
    st_ht_hdl.uc_max_rx_ampdu_factor    = pst_usr_info->uc_arg1;
    st_ht_hdl.uc_min_mpdu_start_spacing = pst_usr_info->uc_arg2;
    mac_user_set_ht_hdl(pst_mac_user, &st_ht_hdl);

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

    /* 同步user pmf的能力 */
    dmac_11w_update_users_status((dmac_vap_stru *)pst_mac_vap, pst_mac_user, pst_usr_info->en_user_pmf);
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

    /* 同步协议模式 */
    mac_user_set_avail_protocol_mode(pst_mac_user, pst_usr_info->en_avail_protocol_mode);
    mac_user_set_cur_protocol_mode(pst_mac_user, pst_usr_info->en_avail_protocol_mode);
    mac_user_set_protocol_mode(pst_mac_user, pst_usr_info->en_protocol_mode);
    mac_user_set_asoc_state(pst_mac_user, pst_usr_info->en_user_asoc_state);

    /* 初始化slottime */
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        dmac_user_init_slottime(pst_mac_vap, pst_mac_user);
    }

#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        /* 调用算法改变带宽通知链 */
        dmac_alg_cfg_user_bandwidth_notify(pst_mac_vap, pst_mac_user);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_vap_state_syn
 功能描述  : 复位硬件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月4日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_vap_info_syn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    mac_h2d_vap_info_stru   *pst_vap_info;

    pst_vap_info = (mac_h2d_vap_info_stru *)puc_param;

    /* 同步vap信息 */
    pst_mac_vap->us_sta_aid = pst_vap_info->us_sta_aid;
    mac_vap_set_uapsd_cap(pst_mac_vap, pst_vap_info->uc_uapsd_cap);
#endif
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
/*****************************************************************************
 函 数 名  : dmac_config_set_device_freq
 功能描述  : 设置device的主频
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月16日
    作    者   : z00185449
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_device_freq(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    wlan_auto_freq_bw_enum_uint8 uc_auto_freq_bw_type = WLAN_BW_20;
    oal_uint16 us_device_freq;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    config_device_freq_h2d_stru   *pst_device_freq;

    pst_device_freq = (config_device_freq_h2d_stru *)puc_param;

#if 0
    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_config_set_device_freq::uc_device_freq_type [%d]}", pst_device_freq->uc_device_freq_type);
#endif

    if (FREQ_HIGHEST_DBG_480MHZ == pst_device_freq->uc_device_freq_type)
    {
        us_device_freq = PM_480MHZ;
    }
    else
    {
        uc_auto_freq_bw_type = dmac_get_device_freq_level();
        dmac_get_device_freq_value(pst_device_freq->uc_device_freq_type, uc_auto_freq_bw_type, &us_device_freq);
    }
    PM_WLAN_SetMaxCpuFreq(us_device_freq);
    if (us_device_freq < PM_80MHZ)
    {
        g_device_wlan_pm_timeout       = DMAC_PSM_TIMER_IDLE_TIMEOUT;
        g_pm_timer_restart_cnt         = DMAC_PSM_TIMER_IDLE_CNT;

    }
    else if ((us_device_freq >= PM_80MHZ) && (us_device_freq < PM_160MHZ))
    {
        g_device_wlan_pm_timeout       = DMAC_PSM_TIMER_MIDIUM_TIMEOUT;
        g_pm_timer_restart_cnt         = DMAC_PSM_TIMER_MIDIUM_CNT;
    }
    else
    {
        g_device_wlan_pm_timeout       = DMAC_PSM_TIMER_BUSY_TIMEOUT;
        g_pm_timer_restart_cnt         = DMAC_PSM_TIMER_BUSY_CNT;
    }
    PM_WLAN_SwitchToState(PM_WPF_ID, (PM_WPF_WK | PM_WLAN_GetMaxCpuFreq()));
#endif
    return OAL_SUCC;
}
#endif
#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
/*****************************************************************************
 函 数 名  : dmac_config_get_tx_rate_info
 功能描述  : 获取发送速率信息
 输入参数  : hal_tx_txop_alg_stru     *pst_tx_alg,
 			 mac_data_rate_stru       *pst_mac_rates_11g,
             oal_rate_info_stru       *pst_rate_info
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : l00179018
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_config_get_tx_rate_info(hal_tx_txop_alg_stru     *pst_tx_alg,
                                                        mac_data_rate_stru       *pst_mac_rates_11g,
                                                        oal_rate_info_stru       *pst_rate_info)
{
    oal_uint32                          ul_loop = 0;
    oal_uint8                           uc_tx_dscr_protocol_type = 0;
    wlan_legacy_rate_value_enum_uint8   en_legacy_rate = 0;

    /* 初始化清零 */
    OAL_MEMZERO(pst_rate_info, OAL_SIZEOF(oal_rate_info_stru));

    /* 获取的protocol type取值范围为0-3,其中0为11b type, 1为legacy OFDM type，2为HT type，3为VHT type */
    uc_tx_dscr_protocol_type = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
    switch(uc_tx_dscr_protocol_type)
    {
        /* 11b or legacy OFDM type */
        case 0:
        case 1:
            en_legacy_rate = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate;

            for (ul_loop = 0; ul_loop < MAC_DATARATES_PHY_80211G_NUM; ul_loop++)
            {
                if (en_legacy_rate == pst_mac_rates_11g[ul_loop].uc_phy_rate)
                {
                    pst_rate_info->legacy = pst_mac_rates_11g[ul_loop].uc_mbps;
                    break;
                }
            }

            /* 未查找到对应的legacy速率，可能是软件配置错误 */
            if (ul_loop >= MAC_DATARATES_PHY_80211G_NUM)
            {
                OAM_ERROR_LOG2(0, OAM_SF_ANY,
                               "{dmac_config_get_tx_rate_info::protocol_type[%d], legacy_rate[%d] is invalid, may be software config error.}",
                               uc_tx_dscr_protocol_type, en_legacy_rate);
            }
            break;

        /* HT type */
        case 2:
            pst_rate_info->flags |= RATE_INFO_FLAGS_MCS;
            pst_rate_info->mcs = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs;
            if (pst_tx_alg->ast_per_rate[0].rate_bit_stru.bit_short_gi_enable)
            {
                pst_rate_info->flags |= RATE_INFO_FLAGS_SHORT_GI;
            }
            break;

        /* VHT type */
        case 3:
            pst_rate_info->flags |= RATE_INFO_FLAGS_VHT_MCS;
            pst_rate_info->mcs = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_vht_mcs;
            if (pst_tx_alg->ast_per_rate[0].rate_bit_stru.bit_short_gi_enable)
            {
                pst_rate_info->flags |= RATE_INFO_FLAGS_SHORT_GI;
            }

            /* 设置nss mode */
            pst_rate_info->nss = pst_tx_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_nss_mode + 1;
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_RSSI,
                           "{dmac_config_get_tx_rate_info:: protocol type[%d] invalid, software config error.}",
                           uc_tx_dscr_protocol_type);
            break;
    }

    /* 根据信道宽度，置对应的标记位 */
    switch (pst_tx_alg->st_rate.uc_channel_bandwidth)
    {
        case WLAN_BAND_ASSEMBLE_40M:
        case WLAN_BAND_ASSEMBLE_40M_DUP:
            pst_rate_info->flags |= RATE_INFO_FLAGS_40_MHZ_WIDTH;
            break;

        case WLAN_BAND_ASSEMBLE_80M:
        case WLAN_BAND_ASSEMBLE_80M_DUP:
            pst_rate_info->flags |= RATE_INFO_FLAGS_80_MHZ_WIDTH;
            break;

        case WLAN_BAND_ASSEMBLE_160M:
        case WLAN_BAND_ASSEMBLE_160M_DUP:
            pst_rate_info->flags |= RATE_INFO_FLAGS_160_MHZ_WIDTH;
            break;

        case WLAN_BAND_ASSEMBLE_80M_80M:
            pst_rate_info->flags |= RATE_INFO_FLAGS_80P80_MHZ_WIDTH;
            break;

        default:
            /* do nothing */
            break;
    }

    OAM_INFO_LOG4(0, OAM_SF_ANY,
                     "{dmac_config_get_tx_rate_info::protocol_type[%d],legacy_rate[%d],short_gi[%d],bandwidth[%d].}",
                     uc_tx_dscr_protocol_type, en_legacy_rate,
                     pst_tx_alg->ast_per_rate[0].rate_bit_stru.bit_short_gi_enable,
                     pst_tx_alg->st_rate.uc_channel_bandwidth);

    OAM_INFO_LOG4(0, OAM_SF_ANY,
                     "{dmac_config_get_tx_rate_info::legacy[%d]:mcs[%d]:flags[%d]:nss[%d].}",
                     pst_rate_info->legacy, pst_rate_info->mcs, pst_rate_info->flags, pst_rate_info->nss);

    return;
}

/*****************************************************************************
 函 数 名  : dmac_config_proc_query_sta_info_event
 功能描述  : 处理上层下发的查询vap统计信息的事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月30日
    作    者   : z00185449
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_proc_query_sta_info_event(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                         *pst_mac_device;
    dmac_vap_stru                           *pst_dmac_vap;
    dmac_user_stru                          *pst_dmac_user;
    dmac_query_request_event                *pst_query_requset_event;
    dmac_query_station_info_response_event   st_query_station_info;

    pst_query_requset_event     = (dmac_query_request_event *)puc_param;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                         "{dmac_config_proc_query_sta_info_event::pst_mac_device is null, device_id[%d].}",
                         pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    if (OAL_QUERY_STATION_INFO_EVENT == pst_query_requset_event->query_event)
    {
        pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_proc_query_sta_info_event::pst_dmac_vap null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
        {
            /* sta查询信息赋值 */
            st_query_station_info.query_event        = pst_query_requset_event->query_event;
            /*从算法处获取RSSI*/
            st_query_station_info.ul_signal          = pst_dmac_vap->st_query_stats.ul_signal;
            /*数据包统计，与维测不能放在同一个预编译宏下面*/
            st_query_station_info.ul_rx_packets      = pst_dmac_vap->st_query_stats.ul_drv_rx_pkts;
            st_query_station_info.ul_tx_packets      = pst_dmac_vap->st_query_stats.ul_hw_tx_pkts;
            st_query_station_info.ul_rx_bytes        = pst_dmac_vap->st_query_stats.ul_drv_rx_bytes;
            st_query_station_info.ul_tx_bytes        = pst_dmac_vap->st_query_stats.ul_hw_tx_bytes;
            st_query_station_info.ul_tx_failed       = pst_dmac_vap->st_query_stats.ul_tx_failed;
            st_query_station_info.ul_tx_retries      = pst_dmac_vap->st_query_stats.ul_tx_retries;
            st_query_station_info.ul_rx_dropped_misc = pst_dmac_vap->st_query_stats.ul_rx_dropped_misc;
        }
        else if(WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_query_requset_event->auc_query_sta_addr);
            if (OAL_PTR_NULL == pst_dmac_user)
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_proc_query_sta_info_event::pst_dmac_user null.}");
                return OAL_ERR_CODE_PTR_NULL;
            }

            /* sta查询信息赋值 */
            st_query_station_info.query_event        = pst_query_requset_event->query_event;
            /*从算法处获取RSSI*/
            st_query_station_info.ul_signal          = pst_dmac_user->st_query_stats.ul_signal;

            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                             "{dmac_config_proc_query_sta_info_event::get rssi=%d in ap mode!", st_query_station_info.ul_signal );

            /*数据包统计，与维测不能放在同一个预编译宏下面*/
            st_query_station_info.ul_rx_packets      = pst_dmac_user->st_query_stats.ul_drv_rx_pkts;
            st_query_station_info.ul_tx_packets      = pst_dmac_user->st_query_stats.ul_hw_tx_pkts;
            st_query_station_info.ul_rx_bytes        = pst_dmac_user->st_query_stats.ul_drv_rx_bytes;
            st_query_station_info.ul_tx_bytes        = pst_dmac_user->st_query_stats.ul_hw_tx_bytes;
            st_query_station_info.ul_tx_failed       = pst_dmac_user->st_query_stats.ul_tx_failed;
            st_query_station_info.ul_tx_retries      = pst_dmac_user->st_query_stats.ul_tx_retries;
            st_query_station_info.ul_rx_dropped_misc = pst_dmac_user->st_query_stats.ul_rx_dropped_misc;
        }
        else
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RSSI,
                             "{dmac_config_proc_query_sta_info_event::vap_mode[%d] don't support query statistics info.}",
                             pst_mac_vap->en_vap_mode);
            return OAL_FAIL;
        }

        /* 获取发送速率 */
        dmac_config_get_tx_rate_info(&(pst_dmac_vap->st_tx_alg), &(pst_mac_device->st_mac_rates_11g[0]), &(st_query_station_info.st_txrate));

        dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_QUERY_STATION_STATS, OAL_SIZEOF(dmac_query_station_info_response_event), (oal_uint8 *)&st_query_station_info);

    }

    return OAL_SUCC;
}
#endif   /* end of (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV) */
#ifdef _PRE_WLAN_FEATURE_DFS
/*****************************************************************************
 函 数 名  : dmac_config_dfs_radartool
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dfs_radartool(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param)
{
#ifndef _PRE_WLAN_PROFLING_MIPS
    mac_device_stru       *pst_mac_device;
    oal_int8              *pc_token;
    oal_int8              *pc_end;
    oal_int8              *pc_ctx;
    oal_int8              *pc_sep = " ";
    oal_bool_enum_uint8    en_val;
    oal_uint32             ul_val;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取命令类型 */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == oal_strcmp(pc_token, "dfsenable"))
    {
        /* 获取DFS使能开关*/
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        en_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);

        mac_dfs_set_dfs_enable(pst_mac_device, en_val);
    }
    else if (0 == oal_strcmp(pc_token, "cacenable"))
    {
        /* 获取CAC检测使能开关*/
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        en_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);

        mac_dfs_set_cac_enable(pst_mac_device, en_val);
    }
    else if (0 == oal_strcmp(pc_token, "dfsdebug"))
    {
        /* 获取debug level */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

        mac_dfs_set_debug_level(pst_mac_device, (oal_uint8)ul_val);
    }
    else if(0 == oal_strcmp(pc_token, "offchannum"))
    {
        /* 获取OFF-CHAN CAC检测信道*/
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);

        mac_dfs_set_offchan_number(pst_mac_device, ul_val);
    }
    else if(0 == oal_strcmp(pc_token, "ctsdura"))
    {
        /* 获取cts duration */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_mac_device->st_dfs.st_dfs_info.uc_cts_duration = (oal_uint8)oal_strtol(pc_token, &pc_end, 10);
    }
    else if(0 == oal_strcmp(pc_token, "radarfilter"))
    {
        /* 获取雷达过滤 chirp_enable */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.en_chirp_enable = (oal_bool_enum_uint8)ul_val;

        /* 获取雷达过滤 chirp_cnt */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_chirp_cnt_threshold = ul_val;

        /* 获取雷达过滤 chirp threshold */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_chirp_time_threshold = ul_val;

        /* 获取雷达过滤 threshold */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 10);

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_time_threshold = ul_val;

        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_last_burst_timestamp = 0;
        pst_mac_device->pst_device_stru->st_dfs_radar_filter.ul_last_burst_timestamp_for_chirp = 0;
    }
    else if(0 == oal_strcmp(pc_token, "enabletimer"))
    {
        /* 获取屏蔽误报定时器时间 */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        ul_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);
        pst_mac_device->us_dfs_timeout = (oal_uint16)ul_val;
        //OAM_INFO_LOG1(0, OAM_SF_DFS, "[DFS]enable timer: %d. ", pst_mac_device->us_dfs_timeout);
    }
    else if(0 == oal_strcmp(pc_token, "offchanenable"))
    {
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        /* 1102 DBAC todo 默认开启DBAC时导致GO不发送beacon帧*/
        hal_vap_start_tsf(((dmac_vap_stru *)pst_mac_vap)->pst_hal_vap, OAL_FALSE);
#endif
    }
    else
    {
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }
#endif
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_set_shpreamble
 功能描述  : 设置dmac AMPDU能力位
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* 设置mib值 */
    mac_mib_set_shpreamble(pst_mac_vap, uc_len, puc_param);
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_MONITOR
/*****************************************************************************
 函 数 名  : dmac_config_set_addr_filter
 功能描述  : 设置dmac 地址过滤能力位
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_addr_filter(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8        uc_value;
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_get_cmd_one_arg::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_value = (*((oal_int32 *)puc_param) == 0) ? 0 : 1;

    if (0 != uc_value)
    {
        /* 开启monitor模式，不根据帧类型过滤 */
        hal_enable_monitor_mode(pst_mac_device->pst_device_stru);
    }
    else
    {
        /* 关闭monitor模式，根据帧类型过滤 */
        hal_disable_monitor_mode(pst_mac_device->pst_device_stru);
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_config_set_prot_mode
 功能描述  : 设置dmac 保护模式
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_prot_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32 l_value;

    l_value = *((oal_int32 *)puc_param);

    pst_mac_vap->st_protection.en_protection_mode = (oal_uint8)l_value;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_pause_tid
 功能描述  : 配置命令去关联1个用户
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_pause_tid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_pause_tid_param_stru   *pst_pause_tid_param;
    dmac_user_stru                 *pst_dmac_user;
    oal_uint8                       uc_tid;
    mac_device_stru                *pst_mac_device;

    pst_pause_tid_param = (mac_cfg_pause_tid_param_stru *)puc_param;
    uc_tid = pst_pause_tid_param->uc_tid;

    pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_pause_tid_param->auc_mac_addr);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pause_tid::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pause_tid::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if  (OAL_TRUE == pst_pause_tid_param->uc_is_paused)
    {
        dmac_tid_pause(&(pst_dmac_user->ast_tx_tid_queue[uc_tid]), DMAC_TID_PAUSE_RESUME_TYPE_BA);
    }
    else
    {
        dmac_tid_resume(pst_mac_device->pst_device_stru, &(pst_dmac_user->ast_tx_tid_queue[uc_tid]), DMAC_TID_PAUSE_RESUME_TYPE_BA);
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_config_dump_timer
 功能描述  : 配置输出timer信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月14日
    作    者   : zhangyu
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_timer(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    frw_timer_dump_timer(pst_mac_vap->ul_core_id);
#if 0
    oal_dlist_head_stru *pst_entry;
    oal_dlist_head_stru *pst_user_list_head;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;

    pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);

    /* 遍历VAP下面的用户，dump用户last active timestamp  */
    for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
    {
        pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);

        /* 指向双向链表下一个节点 */
        pst_entry = pst_entry->pst_next;

        if (OAL_PTR_NULL == pst_dmac_user_tmp)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "dmac_config_dump_timer::user is null. us_assoc_id is %d", pst_user_tmp->us_assoc_id);
            continue;
        }

        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "dmac_config_dump_timer::us_assoc_id is %d, last_active_timestamp[%u]",
                         pst_user_tmp->us_assoc_id, pst_dmac_user_tmp->ul_last_active_timestamp);

    }
#endif
    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_config_set_user_vip
 功能描述  : 配置用户的vip flag
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月22日
    作    者   : xiechunhui
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_user_vip(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_user_vip_param_stru    *pst_user_vip_param;
    dmac_user_stru                 *pst_dmac_user;

    pst_user_vip_param = (mac_cfg_user_vip_param_stru *)puc_param;

    pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_user_vip_param->auc_mac_addr);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_user_vip::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->en_vip_flag = pst_user_vip_param->uc_vip_flag;

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_user_vip, vip_flag = %d}", pst_dmac_user->en_vip_flag);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_vap_host
 功能描述  : 配置vap为host vap;
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月22日
    作    者   : xiechunhui
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_vap_host(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                  *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_vap_host::param null.}");
         return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap->en_is_host_vap = *puc_param;

    OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_vap_host, host_flag = %d}", pst_dmac_vap->en_is_host_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_send_bar
 功能描述  : 配置命令去关联1个用户
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_send_bar(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_pause_tid_param_stru   *pst_pause_tid_param;
    dmac_user_stru                 *pst_dmac_user;
    oal_uint8                       uc_tid;
    dmac_tid_stru                  *pst_tid;

    pst_pause_tid_param = (mac_cfg_pause_tid_param_stru *)puc_param;
    uc_tid = pst_pause_tid_param->uc_tid;

    pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_pause_tid_param->auc_mac_addr);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_bar::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tid = &pst_dmac_user->ast_tx_tid_queue[uc_tid];

    if (OAL_PTR_NULL == pst_tid->pst_ba_tx_hdl || DMAC_BA_COMPLETE != pst_tid->pst_ba_tx_hdl->en_ba_conn_status)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_bar::ba not established.}");
        return OAL_FAIL;
    }

    return dmac_ba_send_bar(pst_tid->pst_ba_tx_hdl, pst_dmac_user, pst_tid);
}



/*****************************************************************************
 函 数 名  : dmac_config_set_bintval
 功能描述  : 设置beacon interval
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_bintval(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru  *pst_dmac_vap;
    oal_int32       l_value;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru             *pst_mac_device;
    oal_uint8                    uc_vap_idx;
    mac_vap_stru*               pst_vap;
#endif

    l_value = *((oal_int32 *)puc_param);
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mac_device              = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_config_set_bintval::pst_mac_device[%d] is NULL!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_device_set_beacon_interval(pst_mac_device, *((oal_uint32 *)puc_param));

    /* 遍历device下所有vap */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_config_set_bintval::pst_mac_vap(%d) null.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* 只有AP VAP需要beacon interval */
        if ((WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode))
        {
             /* 设置mib值 */
            mac_mib_set_beacon_period(pst_vap, (oal_uint8)uc_len, puc_param);
        }
    }
#endif

    hal_vap_set_machw_beacon_period(pst_dmac_vap->pst_hal_vap, (oal_uint16)l_value);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_alg
 功能描述  : 算法配置命令
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_alg(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32        ul_ret = OAL_FAIL;
    oal_uint8         uc_idx;

    oal_int8         *pac_argv[DMAC_ALG_CONFIG_MAX_ARG + 1];

    mac_ioctl_alg_config_stru *pst_alg_config = (mac_ioctl_alg_config_stru *)puc_param;

    for (uc_idx = OAL_SIZEOF(mac_ioctl_alg_config_stru); uc_idx < uc_len; uc_idx++)
    {
        if(puc_param[uc_idx] == ' ')
        {
            puc_param[uc_idx] = 0;
        }
    }

    for(uc_idx = 0; uc_idx < pst_alg_config->uc_argc; uc_idx++)
    {
        pac_argv[uc_idx] = (oal_int8 *)puc_param + OAL_SIZEOF(mac_ioctl_alg_config_stru) + pst_alg_config->auc_argv_offset[uc_idx];
    }

    pac_argv[uc_idx] = NULL;

    for(uc_idx = 0; uc_idx < DMAC_ALG_CONFIG_ID_BUTT; uc_idx++)
    {
        if(0 == oal_strcmp(pac_argv[0], g_ast_dmac_alg_config_table[uc_idx].puc_alg_name))
        {
            break;
        }
    }

    if (uc_idx == DMAC_ALG_CONFIG_ID_BUTT)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_alg: uc_idx error: %d}", uc_idx);

        return OAL_FAIL;
    }


    if(gst_alg_main.pa_alg_config_notify_func[uc_idx])
    {
        ul_ret = gst_alg_main.pa_alg_config_notify_func[uc_idx](pst_mac_vap, pst_alg_config->uc_argc - 1, pac_argv + 1);
    }
    else
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_alg::p_func null.}");
    }

    return ul_ret;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_dtimperiod
 功能描述  : 设置dtim period
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月17日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 设置mib值 */
    mac_mib_set_dtim_period(pst_mac_vap, uc_len, puc_param);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_nobeacon
 功能描述  : 设置dmac no beacon能力位
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_nobeacon(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8            uc_value;
    dmac_vap_stru       *pst_dmac_vap;

    uc_value      = (*((oal_int32 *)puc_param) == 0) ? 0 : 1;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_nobeacon::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 != uc_value)
    {
        hal_vap_beacon_suspend(pst_dmac_vap->pst_hal_vap);
    }
    else
    {
        hal_vap_beacon_resume(pst_dmac_vap->pst_hal_vap);
    }

    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_nobeacon succ!");

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_txchain
 功能描述  : 设置dmac 发送通道
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_txchain(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32           l_value;
    mac_device_stru    *pst_mac_device;

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_txchain::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    l_value = *((oal_int32 *)puc_param);

#if 0
    pst_mac_device->uc_tx_chain = (oal_uint8)l_value;
#else
    mac_device_set_txchain(pst_mac_device, (oal_uint8)l_value);
#endif

    /* 发送通道没有寄存器，放在描述符里 */
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_rxchain
 功能描述  : 设置dmac 发送通道
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_rxchain(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32           l_value;
    mac_device_stru    *pst_mac_device;

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rxchain::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    l_value = *((oal_int32 *)puc_param);

#if 0
    pst_mac_device->uc_rx_chain = (oal_uint8)l_value;
#else
    mac_device_set_rxchain(pst_mac_device, (oal_uint8)l_value);
#endif
    /* 调用HAL接口 */
    hal_set_rx_multi_ant(pst_mac_device->pst_device_stru, pst_mac_device->uc_rx_chain);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_txpower
 功能描述  : 设置dmac 发送功率
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_txpower(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32                       l_value;
    mac_regclass_info_stru          *pst_regdom_info;
    oal_uint8                       uc_cur_ch_num;
    wlan_channel_band_enum_uint8    en_freq_band;

    l_value = *((oal_int32 *)puc_param);

    mac_vap_set_tx_power(pst_mac_vap, (oal_uint8)l_value);

    /* 设置管制域最大功率以控制TPC发送最大功率*/
    en_freq_band  = pst_mac_vap->st_channel.en_band;
    uc_cur_ch_num = pst_mac_vap->st_channel.uc_chan_number;

    pst_regdom_info = mac_get_channel_num_rc_info(en_freq_band, uc_cur_ch_num);
    if (OAL_PTR_NULL == pst_regdom_info)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_txpower::this channel isnot support by this country.freq_band = %d,cur_ch_num = %d}",
                            en_freq_band,uc_cur_ch_num);
    }
    else
    {
        pst_regdom_info->uc_max_reg_tx_pwr = (oal_uint8)l_value;
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_config_set_txpower::max_reg_tx_pwr[%d]!}\r\n", pst_regdom_info->uc_max_reg_tx_pwr);
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_cwmin
 功能描述  : 设置cwmin参数
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_cwmin(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32 *pul_param;
    oal_uint8   uc_cwmin;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    uc_cwmin  = (oal_uint8)pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_cwmin::invalid param, ul_ac=%d uc_cwmin=%d.", ul_ac, uc_cwmin);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableCWmin = uc_cwmin;
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_cwmax
 功能描述  : 设置cwmax参数
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_cwmax(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32 *pul_param;
    oal_uint8   uc_cwmax;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    uc_cwmax  = (oal_uint8)pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_cwmax::invalid param, ul_ac=%d uc_cwmax=%d.", ul_ac, uc_cwmax);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableCWmax = (oal_uint32)uc_cwmax;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_aifsn
 功能描述  : 设置aifsn参数
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_aifsn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_aifsn::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableAIFSN = ul_value;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_aifsn
 功能描述  : 设置txop_limit参数
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_txop_limit(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_txop_limit::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableTXOPLimit = ul_value;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_msdu_lifetime
 功能描述  : 设置msdu_lifetime参数
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_msdu_lifetime(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_msdu_lifetime::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].ul_dot11EDCATableMSDULifetime = ul_value;

    return OAL_SUCC;
}



/*****************************************************************************
 函 数 名  : dmac_config_set_edca_mandatory
 功能描述  : 设置edca_mandatory参数
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_edca_mandatory(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_edca_mandatory::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[ul_ac].en_dot11EDCATableMandatory = (oal_uint8)ul_value;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_qap_cwmin
 功能描述  : 设置AP的cwmin参数，需要操作寄存器
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_qap_cwmin(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32 *pul_param;
    oal_uint8   uc_cwmax = 0;
    oal_uint8   uc_cwmin = 0;
    oal_uint8   uc_cwmin_pre = 0;

    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    uc_cwmin  = (oal_uint8)pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_cwmin::invalid param, ul_ac=%d uc_cwmin=%d.", ul_ac, uc_cwmin);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableCWmin = uc_cwmin;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_cwmin::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }


    hal_vap_get_edca_machw_cw(pst_dmac_vap->pst_hal_vap, &uc_cwmax, &uc_cwmin_pre, (oal_uint8)ul_ac);
    hal_vap_set_edca_machw_cw(pst_dmac_vap->pst_hal_vap, uc_cwmax, uc_cwmin, (oal_uint8)ul_ac);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_qap_cwmax
 功能描述  : 设置AP的cwmax参数，需要操作寄存器
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_qap_cwmax(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32 *pul_param;
    oal_uint8   uc_cwmax = 0;
    oal_uint8   uc_cwmin = 0;
    oal_uint8   uc_cwmax_pre = 0;

    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    uc_cwmax  = (oal_uint8)pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_cwmax::invalid param, ul_ac=%d uc_cwmax=%d.", ul_ac, uc_cwmax);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableCWmax = uc_cwmax;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_cwmax::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    hal_vap_get_edca_machw_cw(pst_dmac_vap->pst_hal_vap, &uc_cwmax_pre, &uc_cwmin, (oal_uint8)ul_ac);
    hal_vap_set_edca_machw_cw(pst_dmac_vap->pst_hal_vap, uc_cwmax, uc_cwmin, (oal_uint8)ul_ac);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_qap_aifsn
 功能描述  : 设置AP的aifsn参数，需要操作寄存器
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_qap_aifsn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;
    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_aifsn::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableAIFSN = ul_value;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_aifsn::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    hal_vap_set_machw_aifsn_ac(pst_dmac_vap->pst_hal_vap, (wlan_wme_ac_type_enum_uint8)ul_ac, (oal_uint8)ul_value);

    return OAL_SUCC;
}



/*****************************************************************************
 函 数 名  : dmac_config_set_qap_aifsn
 功能描述  : 设置AP的txop_limit参数，需要操作寄存器
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_qap_txop_limit(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;
    oal_uint16  us_txop_bk = 0;
    oal_uint16  us_txop_be = 0;
    oal_uint16  us_txop_vi = 0;
    oal_uint16  us_txop_vo = 0;
    oal_uint16  us_pre_value = 0;

    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_txop_limit::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableTXOPLimit = ul_value;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_txop_limit::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }


    switch (ul_ac)
    {
        case WLAN_WME_AC_BK:
            hal_vap_get_machw_txop_limit_bkbe(pst_dmac_vap->pst_hal_vap, &us_txop_be, &us_pre_value);
            hal_vap_set_machw_txop_limit_bkbe(pst_dmac_vap->pst_hal_vap, us_txop_be, (oal_uint16)ul_value);
            break;

        case WLAN_WME_AC_BE:
            hal_vap_get_machw_txop_limit_bkbe(pst_dmac_vap->pst_hal_vap, &us_pre_value, &us_txop_bk);
            hal_vap_set_machw_txop_limit_bkbe(pst_dmac_vap->pst_hal_vap, (oal_uint16)ul_value, us_txop_bk);
            break;

        case WLAN_WME_AC_VI:
            hal_vap_get_machw_txop_limit_vivo(pst_dmac_vap->pst_hal_vap, &us_txop_vo, &us_pre_value);
            hal_vap_set_machw_txop_limit_vivo(pst_dmac_vap->pst_hal_vap, us_txop_vo, (oal_uint16)ul_value);
            break;

        case WLAN_WME_AC_VO:
            hal_vap_get_machw_txop_limit_vivo(pst_dmac_vap->pst_hal_vap, &us_pre_value, &us_txop_vi);
            hal_vap_set_machw_txop_limit_vivo(pst_dmac_vap->pst_hal_vap, (oal_uint16)ul_value, us_txop_vi);
            break;

        default:
            break;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_qap_msdu_lifetime
 功能描述  : 设置AP的msdu_lifetime参数，需要操作寄存器
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_qap_msdu_lifetime(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    oal_uint16  us_lifetime_bk = 0;
    oal_uint16  us_lifetime_be = 0;
    oal_uint16  us_lifetime_vi = 0;
    oal_uint16  us_lifetime_vo = 0;
    oal_uint16  us_pre_value = 0;

    dmac_vap_stru               *pst_dmac_vap;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_msdu_lifetime::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].ul_dot11QAPEDCATableMSDULifetime = ul_value;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_wfa_cfg_aifsn::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }


    switch (ul_ac)
    {
        case WLAN_WME_AC_BK:
            hal_vap_get_machw_edca_bkbe_lifetime(pst_dmac_vap->pst_hal_vap, &us_lifetime_be, &us_pre_value);
            hal_vap_set_machw_edca_bkbe_lifetime(pst_dmac_vap->pst_hal_vap, us_lifetime_be, (oal_uint16)ul_value);
            break;

        case WLAN_WME_AC_BE:
            hal_vap_get_machw_edca_bkbe_lifetime(pst_dmac_vap->pst_hal_vap, &us_pre_value, &us_lifetime_bk);
            hal_vap_set_machw_edca_bkbe_lifetime(pst_dmac_vap->pst_hal_vap, (oal_uint16)ul_value, us_lifetime_bk);
            break;

        case WLAN_WME_AC_VI:
            hal_vap_get_machw_edca_vivo_lifetime(pst_dmac_vap->pst_hal_vap, &us_lifetime_vo, &us_pre_value);
            hal_vap_set_machw_edca_vivo_lifetime(pst_dmac_vap->pst_hal_vap, us_lifetime_vo, (oal_uint16)ul_value);
            break;

        case WLAN_WME_AC_VO:
            hal_vap_get_machw_edca_vivo_lifetime(pst_dmac_vap->pst_hal_vap, &us_pre_value, &us_lifetime_vi);
            hal_vap_set_machw_edca_vivo_lifetime(pst_dmac_vap->pst_hal_vap, (oal_uint16)ul_value, us_lifetime_vi);
            break;

        default:
            break;
    }

    return OAL_SUCC;
}



/*****************************************************************************
 函 数 名  : dmac_config_set_qap_edca_mandatory
 功能描述  : 设置AP的edca_mandatory参数
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : kangguochang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_qap_edca_mandatory(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ac;
    oal_uint32  ul_value;
    oal_uint32 *pul_param;

    pul_param = (oal_uint32 *)puc_param;

    ul_ac     = pul_param[1];
    ul_value  = pul_param[2];

    if (ul_ac >= WLAN_WME_AC_BUTT)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_qap_edca_mandatory::invalid param, ul_ac=%d ul_value=%d.", ul_ac, ul_value);
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[ul_ac].en_dot11QAPEDCATableMandatory = (oal_uint8)ul_value;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_channel
 功能描述  : HOSTAPD 设置信道频段，信道号和带宽
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月26日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_channel_param_stru      *pst_channel_param;
    mac_device_stru                 *pst_mac_device;
    oal_uint8                        uc_channel_idx = 0;
    oal_uint32                       ul_beacon_rate;
    mac_vap_stru                    *pst_vap_up;

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_channel::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_channel_param = (mac_cfg_channel_param_stru *)puc_param;

    mac_get_channel_idx_from_num(pst_channel_param->en_band, pst_channel_param->uc_channel, &uc_channel_idx);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mac_vap->st_channel.uc_chan_number  = pst_channel_param->uc_channel;
    pst_mac_vap->st_channel.en_band         = pst_channel_param->en_band;
    pst_mac_vap->st_channel.en_bandwidth    = pst_channel_param->en_bandwidth;

    /* DTS2015032606908 信道索引号未保存，导致背景扫描结束后恢复时PHY寄存器配置是VAP工作信道，但实际PLL锁频在默认值0，即信道1 */
    pst_mac_vap->st_channel.uc_idx = uc_channel_idx;

    if(MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state)
    {
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_AP_WAIT_START;
    }

    //OAM_INFO_LOG3(0, OAM_SF_2040, "dmac_config_set_channel::chan=%d band=%d bandwidth=%d\r\n", pst_channel_param->uc_channel, pst_channel_param->en_band,
      //                                            pst_channel_param->en_bandwidth);
    /* 根据带宽信息更新Mib */
    mac_vap_change_mib_by_bandwidth(pst_mac_vap, pst_channel_param->en_bandwidth);

    mac_device_set_channel(pst_mac_device, pst_channel_param);
#endif

    /* 更新beacon的发送参数 */
    if ((WLAN_BAND_2G == pst_channel_param->en_band) || (WLAN_BAND_5G == pst_channel_param->en_band))
    {
        ul_beacon_rate = ((dmac_vap_stru *)pst_mac_vap)->ast_tx_mgmt_ucast[pst_channel_param->en_band].ast_per_rate[0].ul_value;
        hal_vap_set_beacon_rate(((dmac_vap_stru *)pst_mac_vap)->pst_hal_vap, ul_beacon_rate);
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_set_channel::en_band=%d", pst_channel_param->en_band);
    }

    /* disable TSF */
    hal_vap_set_machw_tsf_disable(((dmac_vap_stru *)pst_mac_vap)->pst_hal_vap);

#ifdef _PRE_WLAN_FEATURE_DFS
    /* 使能去使能雷达检测 */
    if ((WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)&&(OAL_TRUE == mac_dfs_get_dfs_enable(pst_mac_device)))
    {
        oal_bool_enum_uint8      en_enable_dfs;

        en_enable_dfs = mac_is_ch_in_radar_band(pst_mac_device->en_max_band, pst_mac_vap->st_channel.uc_idx);
        hal_enable_radar_det(pst_mac_device->pst_device_stru, en_enable_dfs);
    }
#endif

    /* 调hal接口设置带宽 */
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    /*dummy*/
#else
    if (pst_channel_param->en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_config_set_channel:: fpga is not support 80M.}\r\n");
        pst_channel_param->en_bandwidth = WLAN_BAND_WIDTH_20M;
    }
#endif

    /* 通知算法 */
    dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);
    dmac_alg_cfg_bandwidth_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);

    mac_device_find_up_sta(pst_mac_device, &pst_vap_up);

    dmac_mgmt_connect_set_channel(pst_mac_device, pst_vap_up, &(pst_mac_vap->st_channel));

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* DTS2015080703361 解决在APUT准备好Beacon帧信息之前发送就启动TSF，致使TBTT中断上报后Beacon Buf为空的问题，临时修改方案，待
       1151 APUT启动方案修改后，该预编宏包裹的代码删除 */
#ifdef _PRE_WLAN_FEATURE_DBAC
    if(mac_is_dbac_enabled(pst_mac_device))
    {

    }
    else
#endif
    {
        hal_vap_start_tsf(((dmac_vap_stru *)pst_mac_vap)->pst_hal_vap, OAL_FALSE);
    }
#endif

    return OAL_SUCC;
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 函 数 名  : dmac_config_set_beacon_debug
 功能描述  : DMAC add beacon 信息调试输出
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月24日
    作    者   : zwx287476
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_config_set_beacon_debug(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param)
{
    mac_beacon_param_stru           *pst_beacon_param;
    oal_uint32                       ul_loop;
    oal_uint8                        uc_vap_id;

    pst_beacon_param = (mac_beacon_param_stru*)puc_param;
    uc_vap_id = pst_mac_vap->uc_vap_id;

    OAM_INFO_LOG1(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug::crypto_mode=%d.}", pst_beacon_param->uc_crypto_mode);
    OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:gourp %d, group_size %d, auth %d.} bit_wpa %d, bit_wpa2 %d \r\n",
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher,
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize,
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteSelected);

    OAM_INFO_LOG2(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:bit_wpa %d, bit_wpa2 %d.}",
        pst_mac_vap->st_cap_flag.bit_wpa,
        pst_mac_vap->st_cap_flag.bit_wpa2);

    for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
    {
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:[%d] %d, %d}",
            (ul_loop + 1),
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].uc_dot11RSNAConfigPairwiseCipherImplemented,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented);
    }

    for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
    {
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:[%d] %d, %d}",
            ul_loop + 1,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].uc_dot11RSNAConfigPairwiseCipherImplemented,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented);
    }

    OAM_INFO_LOG1(uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon_debug:rsn_capability %02x}", pst_beacon_param->us_rsn_capability);
}

/*****************************************************************************
 函 数 名  : dmac_config_add_beacon_debug
 功能描述  : DMAC add beacon 信息调试输出
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月11日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_config_add_beacon_debug(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param)
{
    mac_beacon_param_stru           *pst_beacon_param;
    oal_uint32                       ul_loop;
    oal_uint8                        uc_vap_id;

    pst_beacon_param = (mac_beacon_param_stru*)puc_param;
    uc_vap_id = pst_mac_vap->uc_vap_id;

    OAM_INFO_LOG1(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug::crypto_mode=%d.}", pst_beacon_param->uc_crypto_mode);
    OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:gourp %d, group_size %d, auth %d.} bit_wpa %d, bit_wpa2 %d \r\n",
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher,
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize,
        pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteSelected);

    OAM_INFO_LOG2(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:bit_wpa %d, bit_wpa2 %d.}",
        pst_mac_vap->st_cap_flag.bit_wpa,
        pst_mac_vap->st_cap_flag.bit_wpa2);

    for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
    {
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:[%d] %d, %d}",
            (ul_loop + 1),
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].uc_dot11RSNAConfigPairwiseCipherImplemented,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented);
    }

    for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
    {
        OAM_INFO_LOG3(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:[%d] %d, %d}",
            ul_loop + 1,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].uc_dot11RSNAConfigPairwiseCipherImplemented,
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented);
    }

    OAM_INFO_LOG1(uc_vap_id, OAM_SF_CFG, "{dmac_config_add_beacon_debug:rsn_capability %02x}", pst_beacon_param->us_rsn_capability);
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_set_beacon
 功能描述  : HOSTAPD 设置AP 参数，包括beacon interval，dtim_period, WPA/WPA2
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月24日
    作    者   : zwx287476
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_beacon(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_device;
    mac_beacon_param_stru           *pst_beacon_param;
    dmac_vap_stru                   *pst_dmac_vap;

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_beacon_param = (mac_beacon_param_stru*)puc_param;
    pst_beacon_param = pst_beacon_param;/* 解决pclint告警，pst_beacon_param未引用 */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 1102适配新内核start ap和change beacon接口复用此接口，不同的是change beacon时，不在设置beacon周期
       和dtim周期，因此，change beacon时，interval和dtim period参数为全零，此时不应该被设置到mib中 */
    if ((0 != pst_beacon_param->l_dtim_period) || (0 != pst_beacon_param->l_interval))
    {
        /* 设置mib */
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod   = (oal_uint32)pst_beacon_param->l_dtim_period;
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = (oal_uint32)pst_beacon_param->l_interval;
    }

    /* 根据下发的参数，更改vap隐藏ssid的能力位信息 */
    mac_vap_set_hide_ssid(pst_mac_vap, pst_beacon_param->uc_hidden_ssid);

    if (MAC_ADD_BEACON == pst_beacon_param->en_operation_type)
    {
        mac_vap_add_beacon(pst_mac_vap, pst_beacon_param);
    }
    else
	{
        mac_vap_set_beacon(pst_mac_vap, pst_beacon_param);
	}

    /* 设置short gi */
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented = pst_beacon_param->en_shortgi_20;
    pst_mac_vap->pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInFortyImplemented  = pst_beacon_param->en_shortgi_40;
    pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented = pst_beacon_param->en_shortgi_80;

    mac_vap_init_by_protocol(pst_mac_vap, pst_beacon_param->en_protocol);
    mac_vap_init_rates(pst_mac_vap);
#endif

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_beacon::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_DEBUG_MODE
    if (MAC_ADD_BEACON == pst_beacon_param->en_operation_type)
    {
        dmac_config_add_beacon_debug(pst_mac_vap, puc_param);
    }
    else
	{
        dmac_config_set_beacon_debug(pst_mac_vap, puc_param);
	}
#endif
    dmac_vap_init_tx_frame_params(pst_dmac_vap, OAL_TRUE);
    dmac_vap_init_tx_ucast_data_frame(pst_dmac_vap);

    /* DTS2015022702135 解决GO无法发送Beacon帧问题 */
    hal_vap_set_machw_beacon_period(pst_dmac_vap->pst_hal_vap, (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_add_user
 功能描述  : DMAC用户添加用户同步操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_add_user(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint16                      us_user_idx;
    mac_cfg_add_user_param_stru    *pst_add_user;
    dmac_user_stru                 *pst_dmac_user;
    mac_device_stru                *pst_device;
    oal_uint32                      ul_tid_idx;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_ht_hdl_stru            st_ht_hdl;
#endif
    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_user::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_add_user = (mac_cfg_add_user_param_stru *)puc_param;

    us_user_idx = pst_add_user->us_user_idx;

    /* 获取dmac user */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_user::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* TBD hmac_config_add_user此接口删除，相应调用需要整改，duankaiyong&guyanjie */

    /* 设置qos域，后续如有需要可以通过配置命令参数配置 */
    mac_user_set_qos(&pst_dmac_user->st_user_base_info, OAL_TRUE);

    /* 设置HT域 */
    mac_user_get_ht_hdl(&pst_dmac_user->st_user_base_info, &st_ht_hdl);
    st_ht_hdl.en_ht_capable = pst_add_user->en_ht_cap;

    if (OAL_TRUE == pst_add_user->en_ht_cap)
    {
        pst_dmac_user->st_user_base_info.en_cur_protocol_mode                = WLAN_HT_MODE;
        pst_dmac_user->st_user_base_info.en_avail_protocol_mode              = WLAN_HT_MODE;
    }

    /* 设置HT相关的信息:应该在关联的时候赋值 这个值配置的合理性有待考究 2012->page:786 */
    st_ht_hdl.uc_min_mpdu_start_spacing = 6;
    st_ht_hdl.uc_max_rx_ampdu_factor    = 3;
    mac_user_set_ht_hdl(&pst_dmac_user->st_user_base_info, &st_ht_hdl);

    mac_user_set_asoc_state(&pst_dmac_user->st_user_base_info, MAC_USER_STATE_ASSOC);
#endif

    /* 初始化dmac_ht_handle_stru结构体中的uc_ampdu_max_size值 */
    for (ul_tid_idx = 0; ul_tid_idx < WLAN_TID_MAX_NUM; ul_tid_idx++)
    {
        pst_dmac_user->ast_tx_tid_queue[ul_tid_idx].st_ht_tx_hdl.us_ampdu_max_size = 65535;
    }

    /* lut idx已在创建时申请，此处写到硬件中去 */
    hal_machw_seq_num_index_update_per_tid(pst_device->pst_device_stru,
                                           pst_dmac_user->uc_lut_index,
                                           OAL_TRUE);

    /* 配置命令模拟添加用户，完成后将STA VAP置为UP状态 */
    if ((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)&&
        (IS_LEGACY_VAP(pst_mac_vap)))
    {
        /*将vap状态改变信息上报*/
        mac_vap_state_change(pst_mac_vap, MAC_VAP_STATE_UP);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_del_user
 功能描述  : 删除用户的调测命令
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_del_user(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint16                      us_user_idx;
    mac_cfg_del_user_param_stru    *pst_del_user;
    dmac_user_stru                 *pst_dmac_user;
    mac_device_stru                *pst_mac_device;

    pst_del_user = (mac_cfg_del_user_param_stru *)puc_param;

    us_user_idx = pst_del_user->us_user_idx;

    /* 获取dmac user */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_del_user::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_del_user::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 归还RA LUT IDX */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* do nothing, 不需要移除user，因为Proxy STA的uc_lut_index范围为16~31，用的是vap的，不是user的 */
        }
        else
        {
            mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
        }
    }
    else
    {
        mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
    }
#else
    mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
#endif
    /* 配置命令模拟删除用户，完成后将STA VAP置为FAKE_UP状态 */
    if ((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)&&
        (IS_LEGACY_VAP(pst_mac_vap)))

    {
        /*将vap状态改变信息上报*/
        mac_vap_state_change(pst_mac_vap, MAC_VAP_STATE_STA_FAKE_UP);
    }

    dmac_alg_del_assoc_user_notify((dmac_vap_stru *)pst_mac_vap, pst_dmac_user);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_dump_ba_bitmap
 功能描述  : 显示各类中断个数次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月8日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_ba_bitmap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifdef _PRE_DEBUG_MODE
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
//#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB != _PRE_CONFIG_TARGET_PRODUCT) )
#if 0
        hal_to_dmac_device_stru          *pst_hal_device;
        dmac_vap_stru                    *pst_dmac_vap;
	 dmac_user_stru			 *pst_dmac_user;
        oal_uint16                        us_track_index;
        oal_uint16                        us_seq_index;
        oal_uint8                         uc_num = 0;
        oal_uint8                         uc_lut_idx;
        dmac_tx_ba_track_stru            *pst_tx_ba_track;
        mac_cfg_mpdu_ampdu_tx_param_stru *pst_aggr_tx_on_param;
        oal_file                         *pst_fs = OAL_PTR_NULL;
        oal_mm_segment_t                  old_fs;
        dmac_seq_track_stru               *pst_seq_track = OAL_PTR_NULL;

        pst_aggr_tx_on_param = (mac_cfg_mpdu_ampdu_tx_param_stru *)puc_param;

        pst_dmac_vap    = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
        pst_hal_device  = pst_dmac_vap->pst_hal_device;
        pst_dmac_user = (dmac_user_stru *)mac_vap_get_user_by_addr(pst_mac_vap, pst_aggr_tx_on_param->auc_ra_mac);

	 if (OAL_PTR_NULL == pst_dmac_user)
	 {
	     OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_ba_bitmap::dmac_user_null!\n.}");
	     return OAL_FAIL;
	 }

	 if ( (pst_aggr_tx_on_param->uc_tid >= WLAN_TIDNO_BUTT) || (pst_aggr_tx_on_param->uc_tid < WLAN_TIDNO_BEST_EFFORT) )
	 {
	     OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_config_dump_ba_bitmap::invalid input tid number[%d]\n.}", pst_aggr_tx_on_param->uc_tid);
	     return OAL_FAIL;
	 }

	 if ( OAL_PTR_NULL == (pst_dmac_user->ast_tx_tid_queue[pst_aggr_tx_on_param->uc_tid].pst_ba_tx_hdl) )
	 {
	     OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_ba_bitmap::pst_tx_ba_handle null\n.}");
	     return OAL_FAIL;
	 }

	 uc_lut_idx = pst_dmac_user->ast_tx_tid_queue[pst_aggr_tx_on_param->uc_tid].pst_ba_tx_hdl->uc_tx_ba_lut;

	 if (uc_lut_idx >= HAL_MAX_AMPDU_LUT_SIZE)
	 {
	     OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_ba_bitmap::invalid uc_lut_idx[%d].}", uc_lut_idx);
	     return OAL_FAIL;
	 }

        pst_tx_ba_track = &g_ast_tx_ba_track[pst_mac_vap->uc_device_id][uc_lut_idx];
        us_track_index  = pst_tx_ba_track->us_track_head;

        pst_fs = oal_kernel_file_open(DMAC_DUMP_BA_BITMAP_PATH, OAL_O_RDWR|OAL_O_CREAT|OAL_O_APPEND);
        if(!pst_fs)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "witp_reset_dump_mac_reg,fail to open file!\n");
            return OAL_FAIL;
        }

        old_fs = oal_get_fs();
        oal_set_fs(OAL_KERNEL_DS);                  //扩展内核空间到用户空间

        if (pst_tx_ba_track->us_track_head > OAM_SEQ_TRACK_NUM - 1 || pst_tx_ba_track->us_track_tail > OAM_SEQ_TRACK_NUM - 1)
        {
            oal_kernel_file_print(pst_fs, "head: %d  tail:%d \n", pst_tx_ba_track->us_track_head, pst_tx_ba_track->us_track_tail);
            return OAL_FAIL;
        }
        oal_kernel_file_print(pst_fs, "tid %d \n", pst_tx_ba_track->ast_seq_bitmap_log[us_track_index].uc_tid);

        while (pst_tx_ba_track->us_track_tail != us_track_index)
        {
            pst_seq_track = &(pst_tx_ba_track->ast_seq_bitmap_log[us_track_index]);
            oal_kernel_file_print(pst_fs, "********************************************************************\n");
            oal_kernel_file_print(pst_fs, "No.%d \n", uc_num);
            uc_num++;

            /*发送完成， 上报描述符链打印*/
            if (pst_seq_track->en_is_before_tx_track == OAL_FALSE)
            {
                oal_kernel_file_print(pst_fs, "ba track AFTER tx \n");
                oal_kernel_file_print(pst_fs, "tx status =  %d, report_dscr_num = %d \n", pst_seq_track->un_mix_dscr.st_report.uc_tx_status, pst_seq_track->un_mix_dscr.st_report.uc_report_mpdu_num);
                oal_kernel_file_print(pst_fs, "report seqnum by hw : ");

                for (us_seq_index = 0; us_seq_index < pst_seq_track->un_mix_dscr.st_report.uc_report_mpdu_num; us_seq_index++)
                {
                    oal_kernel_file_print(pst_fs, "%d ", pst_seq_track->un_mix_dscr.st_report.aus_report_seqnum[us_seq_index]);
                }

                oal_kernel_file_print(pst_fs, "\n");
            }
            else /*发送前， 调度描述符链打印*/
            {
                oal_kernel_file_print(pst_fs, "ba track BEFORE tx \n");
                oal_kernel_file_print(pst_fs, "schedule_mpdu_num = %d \n", pst_seq_track->un_mix_dscr.st_schedule.uc_schedule_mpdu_num);
                oal_kernel_file_print(pst_fs, "schedule seqnum : ");
                for (us_seq_index = 0; us_seq_index < pst_seq_track->un_mix_dscr.st_schedule.uc_schedule_mpdu_num; us_seq_index++)
                {
                     oal_kernel_file_print(pst_fs, "%d ", pst_seq_track->un_mix_dscr.st_schedule.aus_schedule_seqnum[us_seq_index]);
                }

                oal_kernel_file_print(pst_fs, "\n");
            }

            /*tid 队列信息打印*/
            oal_kernel_file_print(pst_fs, "tid_total_mpdu_num = %d, tid_retry_mpdu_num = %d)\n", pst_seq_track->us_tid_total_mpdu_num, pst_seq_track->uc_tid_retry_mpdu_num);
            oal_kernel_file_print(pst_fs, "tid_queue_seqnum : ");
            for (us_seq_index = 0; us_seq_index < pst_seq_track->uc_tid_record_mpdu_num; us_seq_index++)
            {
                oal_kernel_file_print(pst_fs, "%d ", pst_tx_ba_track->ast_seq_bitmap_log[us_track_index].aus_tid_seqnum[us_seq_index]);
            }
            oal_kernel_file_print(pst_fs, "\n");

            /*ba handle信息打印*/
            oal_kernel_file_print(pst_fs, "ba bitmap : %08x %08x %08x %08x \n",
                         pst_seq_track->aul_bitmap[0],
                         pst_seq_track->aul_bitmap[1],
                         pst_seq_track->aul_bitmap[2],
                         pst_seq_track->aul_bitmap[3]);

            oal_kernel_file_print(pst_fs, "baw_start: %d , baw_lsn: %d, baw_head: %d, baw_tail: %d \n",
                         pst_seq_track->us_seq_start,
                         pst_seq_track->us_lsn,
                         pst_seq_track->us_baw_head,
                         pst_seq_track->us_baw_tail);

            us_track_index = (us_track_index + 1) & (OAM_SEQ_TRACK_NUM - 1);
        }
//#endif
#endif
#endif
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_get_mpdu_num
 功能描述  : 获取mpdu数目
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月17日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_mpdu_num(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_get_mpdu_num_stru   *pst_param;
    mac_device_stru             *pst_mac_dev;
    dmac_user_stru              *pst_dmac_user;
    oam_report_mpdu_num_stru     st_mpdu_num;

    pst_param = (mac_cfg_get_mpdu_num_stru *)puc_param;

    pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_param->auc_user_macaddr);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_get_mpdu_num:: pst_dmac_user is Null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_get_mpdu_num:: pst_mac_dev is Null");
        return OAL_ERR_CODE_PTR_NULL;
    }

    st_mpdu_num.us_total_mpdu_num_in_device = pst_mac_dev->us_total_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid0         = pst_dmac_user->ast_tx_tid_queue[0].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid1         = pst_dmac_user->ast_tx_tid_queue[1].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid2         = pst_dmac_user->ast_tx_tid_queue[2].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid3         = pst_dmac_user->ast_tx_tid_queue[3].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid4         = pst_dmac_user->ast_tx_tid_queue[4].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid5         = pst_dmac_user->ast_tx_tid_queue[5].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid6         = pst_dmac_user->ast_tx_tid_queue[6].us_mpdu_num;
    st_mpdu_num.us_mpdu_num_in_tid7         = pst_dmac_user->ast_tx_tid_queue[7].us_mpdu_num;

    return oam_report_mpdu_num(pst_dmac_user->st_user_base_info.auc_user_mac_addr, &st_mpdu_num);
}
#if 0
/*****************************************************************************
 函 数 名  : dmac_config_ota_switch
 功能描述  : OTA开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月23日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ota_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    wal_specific_event_type_param_stru      *pst_specific_event_param;
    oal_uint8                                uc_vap_id_loop;
    oal_uint32                               ul_ret;

    pst_specific_event_param = (wal_specific_event_type_param_stru *)puc_param;

    OAL_IO_PRINT("dmac_config_ota_switch: en_ota_type:%d  en_switch_type:%d \n", pst_specific_event_param->l_event_type, pst_specific_event_param->l_param);

    for (uc_vap_id_loop = 0; uc_vap_id_loop < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; uc_vap_id_loop++)
    {
        ul_ret = oam_ota_set_switch(uc_vap_id_loop,
                                    (oal_switch_enum_uint8)pst_specific_event_param->l_param,
                                    (oam_ota_type_enum_uint8)pst_specific_event_param->l_event_type);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(uc_vap_id_loop, OAM_SF_ANY, "{dmac_config_ota_switch::ota switch set failed!}\r\n");
            return ul_ret;
        }
    }
    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_RF_110X_CALI_DPD

#define DPD_CALI_LUT_LENGTH 128
oal_uint32  dmac_dpd_data_processed_recv(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    oal_netbuf_stru            *pst_dpd_data_netbuf;
    dpd_cali_data_stru         *pst_dpd_cali_data_processed;
    dmac_tx_event_stru         *pst_dtx_event;
    mac_vap_stru               *pst_mac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
      OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_recv::pst_event_mem null.}");
      return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_dtx_event       = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dpd_data_netbuf = pst_dtx_event->pst_netbuf;

    pst_dpd_cali_data_processed = (dpd_cali_data_stru *)OAL_NETBUF_DATA(pst_dpd_data_netbuf);

    pst_mac_vap = mac_res_get_mac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_recv::mac_res_get_mac_vap fail,vap_id:%u.}",
                         pst_event->st_event_hdr.uc_vap_id);
        oal_netbuf_free(pst_dpd_data_netbuf);
        return OAL_FAIL;
    }

    if (0 == pst_dpd_cali_data_processed->us_data_len)
    {
        OAM_WARNING_LOG0(0, 0, "dmac_dpd_data_processed_recv: DPD FAIL");

        oal_netbuf_free(pst_dpd_data_netbuf);
        pst_mac_vap->st_cap_flag.bit_dpd_enbale = OAL_FALSE;

        return OAL_FAIL;
    }

    // write dpd data back to register
    hal_dpd_cali_func(HAL_DPD_CALI_DATA_WRITE, 0, 0, pst_dpd_cali_data_processed->us_dpd_data);
    oal_netbuf_free(pst_dpd_data_netbuf);


    pst_mac_vap->st_cap_flag.bit_dpd_done = OAL_TRUE;

    return OAL_SUCC;
}


OAL_STATIC oal_uint32  dmac_dpd_cali_data_send(mac_vap_stru *pst_mac_vap, oal_void *p_param)
{
    frw_event_mem_stru      *pst_event_mem;
    frw_event_stru          *pst_event;
    dmac_tx_event_stru      *pst_dpd_event;
    oal_netbuf_stru         *pst_netbuf_dpd_data;
    dpd_cali_data_stru      *pst_dpd_cali_data;


    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CALIBRATE,
                       "{dmac_send_dpd_calibrated_data::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_netbuf_dpd_data = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, OAL_SIZEOF(dpd_cali_data_stru), OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_netbuf_dpd_data)
    {
        FRW_EVENT_FREE(pst_event_mem);
        OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_dpd_cali_data_send::pst_netbuf_dpd_data null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_TO_HMAC_DPD_CALIBRATED_DATA_SEND,
                       OAL_SIZEOF(dmac_tx_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    OAL_MEMZERO(oal_netbuf_cb(pst_netbuf_dpd_data), OAL_TX_CB_LEN);

    pst_dpd_cali_data = (dpd_cali_data_stru *)(OAL_NETBUF_DATA(pst_netbuf_dpd_data));
    oal_memcopy(pst_dpd_cali_data, p_param, OAL_SIZEOF(dpd_cali_data_stru));

    pst_dpd_event              = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dpd_event->pst_netbuf  = pst_netbuf_dpd_data;
    pst_dpd_event->us_frame_len = OAL_SIZEOF(dpd_cali_data_stru);

    frw_event_dispatch_event(pst_event_mem);

    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

oal_void dmac_start_dpd_calibration(mac_vap_stru *pst_mac_vap)
{
   oal_uint32 ul_status = OAL_FAIL;
   //oal_uint8 index = 0;
   oal_uint32 ul_wifibt_mode_sel;
   dpd_cali_data_stru dpd_cali_data_read;
   //dpd_cali_data_stru dpd_cali_data_calc;

   if(OAL_PTR_NULL == pst_mac_vap)
   {
     OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "dmac_start_dpd_calibration fail PTR_NULL\n\r");
     return;
   }

   OAM_WARNING_LOG0(0, OAM_SF_CALIBRATE, "DPD Calibration Start\n\r");

   hal_btcoex_get_rf_control(30000, &ul_wifibt_mode_sel, 0xff);

   if (ul_wifibt_mode_sel)
   {
        OAM_WARNING_LOG0(0, 0, "DPD RETURN GET RF CONTROL FAIL");
        return;
   }

   hal_dpd_cali_func(HAL_DPD_CALI_START, 0, 0, 0);

   hal_set_btcoex_occupied_period(0);
   hal_dpd_cali_func(HAL_DPD_CALI_STATUS, &ul_status, 0, 0);

   if (OAL_SUCC == ul_status)
   {
        hal_dpd_cali_func(HAL_DPD_CALI_DATA_READ, 0, dpd_cali_data_read.us_dpd_data, 0);
        dpd_cali_data_read.us_data_len = HI1102_DMAC_DPD_CALI_LUT_LENGTH;

#if 0
        for(index = 0; index < HI1102_DMAC_DPD_CALI_LUT_LENGTH; index++)
        {
            OAM_WARNING_LOG1(0, 0, "{dmac_start_dpd_calibration::[%x]!}\r\n", dpd_cali_data_read.us_dpd_data[index]);
            //dpd_cali_data_calc.us_dpd_data[index] = 0;
        }

        hi1102_rf_cali_dpd_corr_calc(dpd_cali_data_read.us_dpd_data, dpd_cali_data_calc.us_dpd_data);
        OAL_IO_PRINT("show dpd results.\n\r", dpd_cali_data_calc.us_dpd_data[index]);
        for(index = 0; index < HI1102_DMAC_DPD_CALI_LUT_LENGTH; index++)
        {
            OAL_IO_PRINT("out = 0x%6x\n\r", dpd_cali_data_calc.us_dpd_data[index]);
        }
        hal_dpd_cali_func(HAL_DPD_CALI_DATA_WRITE, 0, 0, dpd_cali_data_calc.us_dpd_data);
        hal_dpd_cali_func(HAL_DPD_CALI_DATA_READ, 0, dpd_cali_data_read.us_dpd_data, 0);
        dpd_cali_data_read.us_data_len = HI1102_DMAC_DPD_CALI_LUT_LENGTH;
        for(index = 0; index < HI1102_DMAC_DPD_CALI_LUT_LENGTH; index++)
        {
            OAL_IO_PRINT("read lut = 0x%6x\n\r", dpd_cali_data_read.us_dpd_data[index]);
            dpd_cali_data_calc.us_dpd_data[index] = 0;
        }
#else
     dmac_dpd_cali_data_send(pst_mac_vap, (oal_void*)(&dpd_cali_data_read));
#endif
   }
}

//
//
//
OAL_STATIC oal_uint32 dmac_config_start_dpd(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

 dmac_start_dpd_calibration(pst_mac_vap);


   return OAL_SUCC;
}

#endif/*_PRE_WLAN_RF_110X_CALI_DPD end*/


oal_uint32  dmac_cali_hmac2dmac_recv(frw_event_mem_stru *pst_event_mem)
{
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    frw_event_stru             *pst_event;
    oal_netbuf_stru            *pst_cali_data_netbuf;
    oal_uint8                  *puc_cali_data;
    dmac_tx_event_stru         *pst_dtx_event;
   //oal_uint8                  *puc_content;
   //oal_uint32                  ul_byte;

   OAM_WARNING_LOG0(0, OAM_SF_CALIBRATE, "{dmac_cali_hmac2dmac_recv function called.}");
   //OAL_IO_PRINT("dmac_cali_hmac2dmac_recv: start\r\n");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CALIBRATE, "{dmac_cali_hmac2dmac_recv::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_dtx_event       = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_cali_data_netbuf = pst_dtx_event->pst_netbuf;

    puc_cali_data = (oal_uint8 *)OAL_NETBUF_DATA(pst_cali_data_netbuf);
#if 0
    puc_content = (oal_uint8 *)puc_cali_data;

    for (ul_byte = 0; ul_byte < OAL_SIZEOF(oal_cali_param_stru); ul_byte+=4)
    {
        OAL_IO_PRINT("%02X %02X %02X %02X\r\n", puc_content[ul_byte], puc_content[ul_byte+1],
                      puc_content[ul_byte+2], puc_content[ul_byte+3]);
    }

    for(idx = 0; idx < DPD_CALI_LUT_LENGTH; idx++)
    {
      OAM_ERROR_LOG1(0, OAM_SF_CALIBRATE, "{dmac_dpd_data_processed_recv  received: 0x%X}", pst_dpd_cali_data_processed->us_dpd_data[idx]);
    }
#endif
    // write dpd data back to register


    hal_cali_send_func(puc_cali_data);

    oal_netbuf_free(pst_cali_data_netbuf);
#endif
    return OAL_SUCC;
}


#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
 函 数 名  : dmac_config_beacon_offload_test
 功能描述  : OTA开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月23日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_beacon_offload_test(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_sta_beacon_offload_test(pst_mac_vap, puc_param);
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_ota_beacon_switch
 功能描述  : beacon帧的OTA开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月23日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ota_beacon_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8                                uc_vap_id_loop;
    oal_uint32                               ul_ret;
    oal_int32                                l_value;

    l_value = *((oal_int32 *)puc_param);

    for (uc_vap_id_loop = 0; uc_vap_id_loop < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; uc_vap_id_loop++)
    {
        ul_ret = oam_ota_set_beacon_switch(uc_vap_id_loop,
                                          (oam_sdt_print_beacon_rxdscr_type_enum_uint8)l_value);

        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(uc_vap_id_loop, OAM_SF_CFG, "{dmac_config_ota_beacon_switch::ota beacon switch set failed!}\r\n");
            return ul_ret;
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_ota_rx_dscr_switch
 功能描述  : beacon帧的OTA开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月19日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ota_rx_dscr_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8                                uc_vap_id_loop;
    oal_uint32                               ul_ret;
    oal_int32                                l_value;

    l_value = *((oal_int32 *)puc_param);

    for (uc_vap_id_loop = 0; uc_vap_id_loop < WLAN_VAP_SUPPOTR_MAX_NUM_SPEC; uc_vap_id_loop++)
    {
          ul_ret = oam_ota_set_rx_dscr_switch(uc_vap_id_loop,
                                             (oal_switch_enum_uint8)l_value);

        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(uc_vap_id_loop, OAM_SF_CFG, "{dmac_config_ota_rx_dscr_switch::ota rx_dscr switch set failed!}\r\n");
            return ul_ret;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_all_ota
 功能描述  : 设置OAM模块的输出位置
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月23日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_all_ota(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_switch_enum_uint8      en_switch;

    en_switch = *((oal_switch_enum_uint8 *)puc_param);
    return oam_report_set_all_switch(en_switch);
}

/*****************************************************************************
 函 数 名  : dmac_config_oam_output
 功能描述  : 设置所有用户帧上报的所有开关，如果是1，则上报所有类型帧的帧内容，
             cb字段，描述符；如果是0，则什么都不上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月23日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_oam_output(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32                   l_value;
    oal_uint32                  ul_ret;

    l_value = *((oal_int32 *)puc_param);

    /* 设置OAM log模块的开关 */
    ul_ret = oam_set_output_type((oam_output_type_enum_uint8)l_value);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_oam_output::oam_set_output_type failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_probe_switch
 功能描述  : 设置probe request和probe response上报的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月29日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_probe_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifndef _PRE_WLAN_PROFLING_MIPS

    mac_cfg_probe_switch_stru       *pst_probe_switch;
    oal_uint32                       ul_ret = 0;

    pst_probe_switch = (mac_cfg_probe_switch_stru *)puc_param;

    ul_ret = oam_report_80211_probe_set_switch(pst_probe_switch->en_frame_direction,
                                               pst_probe_switch->en_frame_switch,
                                               pst_probe_switch->en_cb_switch,
                                               pst_probe_switch->en_dscr_switch);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_probe_switch::oam_report_80211_probe_set_switch failed[%d].}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_80211_mcast_switch
 功能描述  : 设置80211组播\广播帧上报开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月29日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_80211_mcast_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_80211_mcast_switch_stru *pst_80211_switch_param;
    oal_uint32                       ul_ret = 0;

    pst_80211_switch_param = (mac_cfg_80211_mcast_switch_stru *)puc_param;

    ul_ret = oam_report_80211_mcast_set_switch(pst_80211_switch_param->en_frame_direction,
                                               pst_80211_switch_param->en_frame_type,
                                               pst_80211_switch_param->en_frame_switch,
                                               pst_80211_switch_param->en_cb_switch,
                                               pst_80211_switch_param->en_dscr_switch);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_80211_mcast_switch::oam_report_80211_mcast_set_switch failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_rssi_switch
 功能描述  : 设置打印rssi信息的开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月7日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_rssi_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_rssi_debug_switch_stru      *pst_rssi_switch;

    pst_rssi_switch = (mac_rssi_debug_switch_stru *)puc_param;

    /* 设置rssi开关信息 */
    oal_memcopy(&g_st_rssi_debug_switch_info, pst_rssi_switch, OAL_SIZEOF(mac_rssi_debug_switch_stru));

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_config_report_vap_info
 功能描述  : 根据flags标记位上报对应的vap信息
 输入参数  : mac_vap_stru *pst_mac_vap,
             oal_uint8 uc_len,
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月20日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_report_vap_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifdef _PRE_WLAN_DFT_STAT
    oal_uint32               ul_flags_value;

    /* 参数合法性判断 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_config_report_vap_info::input params is invalid, %p, %p.}",
                         pst_mac_vap, puc_param);
        return OAL_FAIL;
    }

    ul_flags_value = *(oal_uint32 *)puc_param;

    OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_config_report_vap_info::vap_id[%d], flags_value[0x%08x].}",
                     pst_mac_vap->uc_vap_id, ul_flags_value);

    /* 上报硬件信息 */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_HARDWARE_INFO)
    {
        dmac_dft_report_mac_hardware_info(pst_mac_vap);
    }

    /* 上报队列信息 */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_QUEUE_INFO)
    {
        dmac_dft_report_dmac_queue_info(pst_mac_vap);
    }

    /* 上报内存信息 */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_MEMORY_INFO)
    {
        dmac_dft_report_dmac_memory_info(pst_mac_vap);
    }

    /* 上报事件信息 */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_EVENT_INFO)
    {
        dmac_dft_report_dmac_event_info(pst_mac_vap);
    }

    /* 上报vap信息 */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_VAP_INFO)
    {
        dmac_dft_report_dmac_vap_info(pst_mac_vap);
    }

    /* 上报用户信息 */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_USER_INFO)
    {
        dmac_dft_report_dmac_user_info(pst_mac_vap);
    }

    /* 上报收发包统计信息 */
    if (ul_flags_value & MAC_REPORT_INFO_FLAGS_TXRX_PACKET_STATISTICS)
    {
        dmac_config_report_vap_stat(pst_mac_vap, uc_len, puc_param);
    }
#else
    OAM_WARNING_LOG0(0, OAM_SF_ANY,
                     "{dmac_config_report_vap_info::DFT macro switch is not open, do nothing.}");
#endif

    return OAL_SUCC;
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_config_80211_ucast_switch
 功能描述  : 设置单播管理帧开关开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_80211_ucast_switch(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param)
{
    mac_cfg_80211_ucast_switch_stru *pst_80211_switch_param;
    oal_uint16                       us_user_idx = 0;
    oal_uint32                       ul_ret;

    pst_80211_switch_param = (mac_cfg_80211_ucast_switch_stru *)puc_param;

    /* 广播地址，操作所有用户的单播帧开关 */
    if (ETHER_IS_BROADCAST(pst_80211_switch_param->auc_user_macaddr))
    {
        for (us_user_idx = 0; us_user_idx < WLAN_ACTIVE_USER_MAX_NUM + WLAN_MAX_MULTI_USER_NUM_SPEC; us_user_idx++)
        {
            oam_report_80211_ucast_set_switch(pst_80211_switch_param->en_frame_direction,
                                              pst_80211_switch_param->en_frame_type,
                                              pst_80211_switch_param->en_frame_switch,
                                              pst_80211_switch_param->en_cb_switch,
                                              pst_80211_switch_param->en_dscr_switch,
                                              us_user_idx);
        }
        return OAL_SUCC;
    }

    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap,
                                          pst_80211_switch_param->auc_user_macaddr,
                                          &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_80211_ucast_switch::mac_vap_find_user_by_macaddr[%02X:XX:XX:%02X:%02X:%02X]failed !!}",
                        pst_80211_switch_param->auc_user_macaddr[0],
                        pst_80211_switch_param->auc_user_macaddr[3],
                        pst_80211_switch_param->auc_user_macaddr[4],
                        pst_80211_switch_param->auc_user_macaddr[5]);
        return ul_ret;
    }

    ul_ret = oam_report_80211_ucast_set_switch(pst_80211_switch_param->en_frame_direction,
                                               pst_80211_switch_param->en_frame_type,
                                               pst_80211_switch_param->en_frame_switch,
                                               pst_80211_switch_param->en_cb_switch,
                                               pst_80211_switch_param->en_dscr_switch,
                                               us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_80211_ucast_switch::Set switch of report_ucast failed[%d]!!frame_switch[%d], cb_switch[%d], dscr_switch[%d].}",
                ul_ret,
                pst_80211_switch_param->en_frame_switch,
                pst_80211_switch_param->en_cb_switch,
                pst_80211_switch_param->en_dscr_switch);
        return ul_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_wfa_cfg_aifsn
 功能描述  : 设置aifsn固定值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月23日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_wfa_cfg_aifsn(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param)
{
    mac_edca_cfg_stru   *pst_edca_cfg_param;
    dmac_vap_stru               *pst_dmac_vap;

    /* 参数合法性判断 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_config_wfa_cfg_aifsn::input params is invalid, %p, %p.}",
                         pst_mac_vap, puc_param);
        return OAL_FAIL;
    }

    pst_edca_cfg_param = (mac_edca_cfg_stru *)puc_param;
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_config_wfa_cfg_aifsn::mac_res_get_dmac_vap fail or pst_dmac_vap->pst_hal_vap NULL,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    hal_vap_set_machw_aifsn_ac_wfa(pst_dmac_vap->pst_hal_vap, pst_edca_cfg_param->en_ac, (oal_uint8)pst_edca_cfg_param->us_val, pst_edca_cfg_param->en_switch);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_wfa_cfg_cw
 功能描述  : 设置cw固定值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月23日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_wfa_cfg_cw(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param)
{
    mac_edca_cfg_stru   *pst_edca_cfg_param;
    dmac_vap_stru               *pst_dmac_vap;

    /* 参数合法性判断 */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_config_wfa_cfg_cw::input params is invalid, %p, %p.}",
                         pst_mac_vap, puc_param);
        return OAL_FAIL;
    }

    pst_edca_cfg_param = (mac_edca_cfg_stru *)puc_param;
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_config_wfa_cfg_aifsn::mac_res_get_dmac_vap fail or pst_dmac_vap->pst_hal_vap NULL,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    hal_vap_set_edca_machw_cw_wfa(pst_dmac_vap->pst_hal_vap, (oal_uint8)pst_edca_cfg_param->us_val, pst_edca_cfg_param->en_ac, pst_edca_cfg_param->en_switch);
    return OAL_SUCC;
}

#endif /* DMAC_OFFLOAD */

/*****************************************************************************
 函 数 名  : dmac_config_dump_all_rx_dscr
 功能描述  : 打印所有接收描述符
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月8日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_all_rx_dscr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru    *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_all_rx_dscr::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_dump_all_rx_dscr(pst_device->pst_device_stru);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_reset_hw
 功能描述  : 复位硬件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月8日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_reset_hw(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifndef _PRE_WLAN_PROFLING_MIPS

    mac_device_stru    *pst_device;
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[DMAC_HIPRIV_CMD_NAME_MAX_LEN];
    dmac_reset_para_stru            st_reset_param;

    /* 复位硬件phy&mac: hipriv "Hisilicon0 reset_hw 0|1|2|3(all|phy|mac|debug) 0|1(reset phy reg) 0|1(reset mac reg)"*/
    /* 命令复用来debug显示lut表和寄存器:hipriv "Hisilicon0 reset_hw 3(debug) 0|1|2(all|mac reg|phy reg|lut) "*/

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    /* 设置配置命令参数 */
    if(OAL_PTR_NULL == pst_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_reset_hw::pst_device is null,id=%d}", pst_mac_vap->uc_device_id);

        return OAL_FAIL;
    }

    OAL_MEMZERO(ac_name, DMAC_HIPRIV_CMD_NAME_MAX_LEN);
    /* 获取复位类型*/
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
    st_reset_param.uc_reset_type = (oal_uint8)oal_atoi(ac_name);
    /* 偏移，取下一个参数 */
    puc_param = puc_param + ul_off_set;

    //if (st_reset_param.uc_reset_type <= HAL_RESET_HW_TYPE_MAC_PHY)
    if (st_reset_param.uc_reset_type < HAL_RESET_HW_TYPE_DUMP_MAC)
    {
        /* 获取是否复位phy reg */
        dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
        st_reset_param.uc_reset_phy_reg = (oal_uint8)oal_atoi(ac_name);
        /* 偏移，取下一个参数 */
        puc_param = puc_param + ul_off_set;

        /* 获取是否复位mac reg */
        dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
        st_reset_param.uc_reset_mac_reg = (oal_uint8)oal_atoi(ac_name);
        /* 偏移，取下一个参数 */
        puc_param = puc_param + ul_off_set;

        st_reset_param.uc_reset_mac_mod = HAL_RESET_MAC_ALL;    /* HAL_RESET_MAC_ALL*/
        st_reset_param.en_reason = DMAC_RESET_REASON_HW_ERR;           /*DMAC_RESET_REASON_CONFIG*/
        dmac_reset_hw(pst_device,(oal_uint8*)&st_reset_param);
    }
    else
    {

        /* 获取debug类型:0|1|2(all|mac reg|phy reg|lut) */
        dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
        st_reset_param.uc_debug_type= (oal_uint8)oal_atoi(ac_name);
        /* 偏移，取下一个参数 */
        puc_param = puc_param + ul_off_set;

        dmac_reset_debug_all(pst_device,&st_reset_param);
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_dump_rx_dscr
 功能描述  : dump rx 描述符队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月2日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_rx_dscr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifndef _PRE_WLAN_PROFLING_MIPS

    hal_rx_dscr_queue_header_stru   *pst_rx_dscr_queue;
    mac_device_stru                 *pst_mac_device;
    hal_to_dmac_device_stru         *pst_hal_device;
    oal_uint32                      *pul_curr_dscr;
    hal_rx_dscr_stru                *pst_hal_to_dmac_dscr;
    oal_uint32                       ul_value;
    oal_uint32                       ul_rx_dscr_len = 0;
#ifdef _PRE_DEBUG_MODE
    oal_uint32                       ul_loop;
    oal_uint32                      *pul_original_dscr;
    oal_uint32                       ul_dscr_num;
#endif

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_dump_rx_dscr::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    ul_value = *((oal_uint32 *)puc_param);

    if (ul_value >= HAL_RX_DSCR_QUEUE_ID_BUTT)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_config_dump_rx_dscr::invalid rx dscr queue[%d].}", ul_value);
        return OAL_FAIL;
    }

    hal_rx_get_size_dscr(pst_hal_device, &ul_rx_dscr_len);

#ifdef _PRE_DEBUG_MODE
    /* 将描述符原始地址打出来 */
    OAM_INFO_LOG0(0, OAM_SF_CFG, "the origin dscr phy addr and virtual addr:\n");

    if (HAL_RX_DSCR_NORMAL_PRI_QUEUE == ul_value)
    {
        pul_original_dscr = pst_hal_device->aul_nor_rx_dscr;
        ul_dscr_num       = HAL_NORMAL_RX_MAX_BUFFS;
    }
    else
    {
        pul_original_dscr = pst_hal_device->aul_hi_rx_dscr;
        ul_dscr_num       = HAL_HIGH_RX_MAX_BUFFS;
    }

    for (ul_loop = 0; ul_loop < ul_dscr_num; ul_loop++)
    {
        pul_curr_dscr = OAL_PHY_TO_VIRT_ADDR(pul_original_dscr[ul_loop]);
        OAM_INFO_LOG3(0, OAM_SF_CFG, "%2d 0x%08x, 0x%08x\n",
                     ul_loop,
                     pul_original_dscr[ul_loop],
                     (oal_uint32)pul_curr_dscr);

        oam_report_dscr(BROADCAST_MACADDR, (oal_uint8 *)pul_curr_dscr, (oal_uint16)ul_rx_dscr_len, OAM_OTA_TYPE_RX_DSCR);
    }

    OAM_INFO_LOG1(0, OAM_SF_CFG, "dscr exception free cnt is %d\n", pst_hal_device->ul_exception_free);
#endif

    pst_rx_dscr_queue = &(pst_hal_device->ast_rx_dscr_queue[ul_value]);

    pul_curr_dscr = pst_rx_dscr_queue->pul_element_head;

    //OAM_INFO_LOG1(0, OAM_SF_CFG, "the current dscr cnt is: %d\n", pst_rx_dscr_queue->us_element_cnt);
    //OAM_INFO_LOG1(0, OAM_SF_CFG, "head ptr virtual addr is: 0x%08x\n", (oal_uint32)pst_rx_dscr_queue->pul_element_head);
    //OAM_INFO_LOG1(0, OAM_SF_CFG, "tail ptr virtual addr is: 0x%08x\n", (oal_uint32)pst_rx_dscr_queue->pul_element_tail);

    OAM_INFO_LOG0(0, OAM_SF_CFG, "the current dscr addr and dscr's content:\n");
    while(OAL_PTR_NULL != pul_curr_dscr)
    {
        OAM_INFO_LOG2(0, OAM_SF_CFG, "virtual addr:0x%08x, phy addr:0x%08x\n", (oal_uint32)pul_curr_dscr, (oal_uint32)OAL_VIRT_TO_PHY_ADDR(HAL_RX_DSCR_GET_REAL_ADDR(pul_curr_dscr)));
        oam_report_dscr(BROADCAST_MACADDR, (oal_uint8 *)pul_curr_dscr, (oal_uint16)ul_rx_dscr_len, OAM_OTA_TYPE_RX_DSCR);

        pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;
        pul_curr_dscr        = HAL_RX_DSCR_GET_SW_ADDR(oal_get_virt_addr(pst_hal_to_dmac_dscr->pul_next_rx_dscr));
    }

    hal_rx_show_dscr_queue_info(pst_hal_device, (oal_uint8)ul_value);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_dump_tx_dscr
 功能描述  : dump tx 描述符队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月2日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dump_tx_dscr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_device;
    hal_to_dmac_device_stru         *pst_hal_device;
    oal_uint32                       ul_value;
    hal_tx_dscr_stru                *pst_dscr;
    oal_dlist_head_stru             *pst_pos;
    oal_netbuf_stru                 *pst_netbuf;
    mac_tx_ctl_stru                 *pst_tx_cb;
    oal_uint32                       ul_dscr_one_size = 0;
    oal_uint32                       ul_dscr_two_size = 0;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_tx_dscr::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_hal_device = pst_mac_device->pst_device_stru;

    ul_value = *((oal_uint32 *)puc_param);

    if (ul_value >= HAL_TX_QUEUE_NUM)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{dmac_config_dump_rx_dscr::invalid tx dscr queue[%d].}", ul_value);
        return OAL_FAIL;
    }

    OAL_DLIST_SEARCH_FOR_EACH(pst_pos, &(pst_hal_device->ast_tx_dscr_queue[ul_value].st_header))
    {
        pst_dscr   = OAL_DLIST_GET_ENTRY(pst_pos, hal_tx_dscr_stru, st_entry);
        pst_netbuf = pst_dscr->pst_skb_start_addr;
        pst_tx_cb  = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);

        hal_tx_get_size_dscr(pst_hal_device, MAC_GET_CB_NETBUF_NUM(pst_tx_cb), &ul_dscr_one_size, &ul_dscr_two_size);
        oam_report_dscr(BROADCAST_MACADDR,
                        (oal_uint8 *)pst_dscr,
                        (oal_uint16)(ul_dscr_one_size + ul_dscr_two_size),
                        OAM_OTA_TYPE_TX_DSCR);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_connect
 功能描述  : dmac 处理connect请求，
 输入参数  :
 输出参数  : 无
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_connect(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32                                   ul_ret;
    mac_cfg80211_connect_security_stru          *pst_conn;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_connect::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_conn = (mac_cfg80211_connect_security_stru *)puc_param;

    ul_ret = mac_vap_init_privacy(pst_mac_vap, pst_conn);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_connect::mac_11i_init_privacy fail [%d].}", ul_ret);
        return ul_ret;
    }
#ifdef _PRE_WLAN_FEATURE_11R
    ul_ret = mac_mib_init_ft_cfg(pst_mac_vap, pst_conn->auc_mde);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_connect::mac_mib_init_ft_cfg fail[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
#endif //_PRE_WLAN_FEATURE_11R

    /* 通知算法 */
    dmac_alg_cfg_start_connect_notify(pst_mac_vap, pst_conn->c_rssi);
#endif

    return OAL_SUCC;
}

#ifdef _PRE_DEBUG_MODE_USER_TRACK
/*****************************************************************************
 函 数 名  : dmac_config_report_thrput_stat
 功能描述  : 上报影响用户实时吞吐相关的统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_report_thrput_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_usr_thrput_stru             *pst_usr_thrput_param;
    dmac_user_stru                      *pst_dmac_user;

    pst_usr_thrput_param = (mac_cfg_usr_thrput_stru *)puc_param;

    /* 获取用户 */
    pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_usr_thrput_param->auc_user_macaddr);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_report_thrput_stat::dmac_user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_usr_thrput_param->uc_param)
    {
        /* 停止上报 */
        return dmac_user_track_clear_usr_thrput_stat(&pst_dmac_user->st_user_base_info);
    }
    else
    {
        return dmac_user_track_report_usr_thrput_stat(&pst_dmac_user->st_user_base_info);
    }
}

#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 函 数 名  : dmac_config_print_btcoex_status
 功能描述  : 打印共存维测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月17日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_print_btcoex_status(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    hal_get_btcoex_statistic(OAL_TRUE);
    return OAL_SUCC;
}

#endif

#ifdef _PRE_WLAN_FEATURE_LTECOEX
/*****************************************************************************
 函 数 名  : dmac_config_ltecoex_mode_set
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月19日
    作    者   : z00196432
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ltecoex_mode_set(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                *pst_macdev;

    OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_ltecoex_mode_set! ltecoex_mode:%d}" , *puc_param);

    pst_macdev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_ltecoex_mode_set::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if(*puc_param)
    {
        /*设置LTE共存开启标志位*/
        pst_macdev->pst_device_stru->ul_lte_coex_status = 1;

        /*使能 mac的共存功能，COEX_ABORT_CTRL 的 bit0置为1*/
        hal_set_btcoex_sw_all_abort_ctrl(1);

        /*使能PTA对lte业务的处理*/
        hal_ltecoex_req_mask_ctrl(0);
    }
    else
    {
        /*设置LTE共存关闭标志位*/
        pst_macdev->pst_device_stru->ul_lte_coex_status = 0;

        /*如果BT没有开启,才关闭mac的共存功能*/
        if(0 == pst_macdev->pst_device_stru->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
        {
            hal_set_btcoex_sw_all_abort_ctrl(0);
            hal_set_btcoex_hw_rx_priority_dis(1);
        }

        /*屏蔽PTA对lte业务的处理*/
        hal_ltecoex_req_mask_ctrl(0xF);
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_DFT_STAT

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
 函 数 名  : dmac_config_phy_stat_info
 功能描述  : 上报phy统计收发包数目信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月13日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_phy_stat_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if 0
    oam_stats_phy_stat_stru         st_phy_stat;
    mac_device_stru                *pst_macdev;
    oal_uint8                       auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_macdev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_phy_stat_info::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_phy_stat, OAL_SIZEOF(oam_stats_phy_stat_stru));

    hal_dft_get_phyhw_stat_info(pst_macdev->pst_device_stru,&st_phy_stat);

    /* 将获取到的统计值上报 */
    return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_phy_stat,(oal_uint16)OAL_SIZEOF(oam_stats_phy_stat_stru), OAM_OTA_TYPE_PHY_STAT);
#endif
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_machw_stat_info
 功能描述  : 上报或者清零mac统计收发包数目信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_machw_stat_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if 0
    mac_device_stru                 *pst_mac_dev;
#if 0
    oal_uint8                        uc_loop;
    oal_uint32                       ul_reg_addr;
    oal_uint32                       ul_reg_val = 0;
#endif
    oam_stats_machw_stat_stru        st_machw_stat;
    oal_uint8                        auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_machw_stat_info::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == *puc_param)
    {
        /* 清零mac统计,mac统计清零寄存器的bit2~bit22,bit4是发送beacon帧数目，bit9是高优先级队列发送数目，不清零，
           这两个统计值放在管理帧统计功能控制
        */
        hal_dft_clear_machw_stat_info(pst_mac_dev->pst_device_stru);
        return OAL_SUCC;
    }
    else
    {
        OAL_MEMZERO(&st_machw_stat, OAL_SIZEOF(oam_stats_machw_stat_stru));

        /* 从MAC寄存器获取统计值 */
        dmac_dft_get_machw_stat_info(pst_mac_dev->pst_device_stru, &st_machw_stat);
    #if 0
        /* 获取mac rx统计信息，直接读mac寄存器 */
        for (ul_reg_addr = (oal_uint32)WITP_PA_RX_AMPDU_COUNT_REG, uc_loop = 0;
             ul_reg_addr <= (oal_uint32)WITP_PA_RX_FILTERED_CNT_REG && uc_loop < OAM_MACHW_STAT_RX_MEMBER_CNT;
             ul_reg_addr += 4, uc_loop++)
        {
            hal_reg_info(pst_mac_dev->pst_device_stru, ul_reg_addr, &ul_reg_val);
            st_machw_stat.aul_machw_stat_rx_cnt[uc_loop] = ul_reg_val;
        }

        /* 获取mac tx统计信息，直接读mac寄存器 */
        for (ul_reg_addr = (oal_uint32)WITP_PA_TX_HI_PRI_MPDU_CNT_REG, uc_loop = 0;
             ul_reg_addr <= (oal_uint32)WITP_PA_HI_PRI_RETRY_CNT_REG && uc_loop < OAM_MACHW_STAT_TX_MEMBER_CNT;
             ul_reg_addr += 4, uc_loop++)
        {
            hal_reg_info(pst_mac_dev->pst_device_stru, ul_reg_addr, &ul_reg_val);
            st_machw_stat.aul_machw_stat_tx_cnt[uc_loop] = ul_reg_val;
        }
    #endif
        return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_machw_stat,(oal_uint16)OAL_SIZEOF(oam_stats_machw_stat_stru), OAM_OTA_TYPE_MACHW_STAT);
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_report_mgmt_stat
 功能描述  : 上报或者清零管理帧统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_report_mgmt_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_dev;
    oam_stats_mgmt_stat_stru         st_mgmt_stat;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_report_mgmt_stat::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == *puc_param)
    {
        /* 清零mac统计的发送beacon帧数目、高优先级队列发送数目:MAC统计寄存器的bit4和bit9 */
        hal_reg_write(pst_mac_dev->pst_device_stru, (oal_uint32)HI1102_MAC_COUNTER_CLEAR_REG, 0x210);

        /* 清零软件统计的管理帧收发数目 */
        OAL_MEMZERO(&pst_mac_dev->st_mgmt_stat, OAL_SIZEOF(mac_device_mgmt_statistic_stru));

        return OAL_SUCC;
    }
    else
    {
        /* 获取mac统计的发送beacon帧数目和高优先级队列发送数目 */
        hal_reg_info(pst_mac_dev->pst_device_stru, (oal_uint32)HI1102_MAC_TX_BCN_COUNT_REG, &st_mgmt_stat.ul_machw_stat_tx_bcn_cnt);
        hal_reg_info(pst_mac_dev->pst_device_stru, (oal_uint32)HI1102_MAC_TX_HI_PRI_MPDU_CNT_REG, &st_mgmt_stat.ul_machw_stat_tx_hi_cnt);

        /* 获取软件的管理帧收发统计 */
        oal_memcopy(st_mgmt_stat.aul_sw_rx_mgmt_cnt,
                    &pst_mac_dev->st_mgmt_stat,
                    OAL_SIZEOF(mac_device_mgmt_statistic_stru));

        /* 将统计值上报 */
        return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_mgmt_stat, (oal_uint16)OAL_SIZEOF(oam_stats_mgmt_stat_stru),OAM_OTA_TYPE_MGMT_STAT);
    }
}


#else

/*****************************************************************************
 函 数 名  : dmac_config_phy_stat_info
 功能描述  : 上报phy统计收发包数目信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月13日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_phy_stat_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oam_stats_phy_stat_stru         st_phy_stat;
    mac_device_stru                *pst_macdev;
    oal_uint8                       uc_loop;
    oal_uint32                      ul_reg_addr;
    oal_uint32                      ul_reg_val = 0;

    pst_macdev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_phy_stat_info::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_phy_stat, OAL_SIZEOF(oam_stats_phy_stat_stru));

    /* 获取用户指定统计的4个phy统计值 */
    for (ul_reg_addr = (oal_uint32)WITP_PHY_PHY_STA0_RPT_REG, uc_loop = 0;
         ul_reg_addr <= (oal_uint32)WITP_PHY_PHY_STA3_RPT_REG && uc_loop < OAM_PHY_STAT_NODE_ENABLED_MAX_NUM;
         ul_reg_addr += 4, uc_loop++)
    {
        hal_reg_info(pst_macdev->pst_device_stru, ul_reg_addr, &ul_reg_val);
        st_phy_stat.aul_user_requested_stat_cnt[uc_loop] = ul_reg_val;
    }

    /* 获取phy按照协议模式统计的接收正确和错误帧个数 */
    for (ul_reg_addr = (oal_uint32)WITP_PHY_DOTB_OK_FRM_NUM_REG, uc_loop = 0;
         ul_reg_addr <= (oal_uint32)WITP_PHY_LEGA_ERR_FRM_NUM_REG && uc_loop < OAM_PHY_STAT_RX_PPDU_CNT;
         ul_reg_addr += 4, uc_loop++)
    {
        hal_reg_info(pst_macdev->pst_device_stru, ul_reg_addr, &ul_reg_val);
        st_phy_stat.aul_phy_stat_rx_ppdu_cnt[uc_loop] = ul_reg_val;
    }

    /* 将获取到的统计值上报 */
    return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_phy_stat,(oal_uint16)OAL_SIZEOF(oam_stats_phy_stat_stru), OAM_OTA_TYPE_PHY_STAT);
}


/*****************************************************************************
 函 数 名  : dmac_config_machw_stat_info
 功能描述  : 上报或者清零mac统计收发包数目信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_machw_stat_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_dev;
    oam_stats_machw_stat_stru        st_machw_stat;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_machw_stat_info::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == *puc_param)
    {
        /* 清零mac统计,mac统计清零寄存器的bit2~bit22,bit4是发送beacon帧数目，bit9是高优先级队列发送数目，不清零，
           这两个统计值放在管理帧统计功能控制
        */
        hal_reg_write(pst_mac_dev->pst_device_stru, (oal_uint32)WITP_PA_COUNTER_CLEAR_REG, 0x7FFDEC);

        return OAL_SUCC;
    }
    else
    {
        OAL_MEMZERO(&st_machw_stat, OAL_SIZEOF(oam_stats_machw_stat_stru));

        /* 从MAC寄存器获取统计值 */
        dmac_dft_get_machw_stat_info(pst_mac_dev->pst_device_stru, &st_machw_stat);
        return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_machw_stat,(oal_uint16)OAL_SIZEOF(oam_stats_machw_stat_stru), OAM_OTA_TYPE_MACHW_STAT);
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_report_mgmt_stat
 功能描述  : 上报或者清零管理帧统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_report_mgmt_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_dev;
    oam_stats_mgmt_stat_stru         st_mgmt_stat;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_report_mgmt_stat::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == *puc_param)
    {
        /* 清零mac统计的发送beacon帧数目、高优先级队列发送数目:MAC统计寄存器的bit4和bit9 */
        hal_reg_write(pst_mac_dev->pst_device_stru, (oal_uint32)WITP_PA_COUNTER_CLEAR_REG, 0x210);

        /* 清零软件统计的管理帧收发数目 */
        OAL_MEMZERO(&pst_mac_dev->st_mgmt_stat, OAL_SIZEOF(mac_device_mgmt_statistic_stru));

        return OAL_SUCC;
    }
    else
    {
        /* 获取mac统计的发送beacon帧数目和高优先级队列发送数目 */
        hal_reg_info(pst_mac_dev->pst_device_stru, (oal_uint32)WITP_PA_TX_BCN_COUNT_REG, &st_mgmt_stat.ul_machw_stat_tx_bcn_cnt);
        hal_reg_info(pst_mac_dev->pst_device_stru, (oal_uint32)WITP_PA_TX_HI_PRI_MPDU_CNT_REG, &st_mgmt_stat.ul_machw_stat_tx_hi_cnt);

        /* 获取软件的管理帧收发统计 */
        oal_memcopy(st_mgmt_stat.aul_sw_rx_mgmt_cnt,
                    &pst_mac_dev->st_mgmt_stat,
                    OAL_SIZEOF(mac_device_mgmt_statistic_stru));

        /* 将统计值上报 */
        return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_mgmt_stat,(oal_uint16)OAL_SIZEOF(oam_stats_mgmt_stat_stru), OAM_OTA_TYPE_MGMT_STAT);
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_usr_queue_stat
 功能描述  : 上报或者清零用户队列统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_usr_queue_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_usr_queue_param_stru        *pst_usr_queue_param;
    dmac_user_stru                      *pst_dmac_user;

    pst_usr_queue_param = (mac_cfg_usr_queue_param_stru *)puc_param;

    /* 获取用户 */
    pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_usr_queue_param->auc_user_macaddr);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_usr_queue_stat::dmac_user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_usr_queue_param->uc_param)
    {
        /* 清空用户队列统计信息 */
        return dmac_dft_clear_usr_queue_stat(pst_dmac_user);
    }
    else
    {
        return dmac_dft_report_usr_queue_stat(pst_dmac_user);
    }
}

#endif
/*****************************************************************************
 函 数 名  : dmac_config_report_vap_stat
 功能描述  : 上报或者停止上报vap吞吐统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月19日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_report_vap_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;
    dmac_vap_query_stats_stru    st_vap_dft_stats;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_config_report_vap_stat::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_OS_VERSION == _PRE_OS_VERSION_RAW)
    OAM_WARNING_LOG_ALTER(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_config_report_vap_stat::drv_tx_pkts[%lu], hw_tx_pkts_succ[%lu], tx_fail[%lu], rx_mpdus[%lu], rx_drops[%lu], rx_null[%lu], rx_mgmt[%lu]}", 7,
                        pst_dmac_vap->st_query_stats.ul_drv_tx_pkts, pst_dmac_vap->st_query_stats.ul_hw_tx_pkts, pst_dmac_vap->st_query_stats.ul_tx_failed,
                        pst_dmac_vap->st_query_stats.ul_rx_mpdu_total_num,
                        (pst_dmac_vap->st_query_stats.ul_rx_dropped_misc + pst_dmac_vap->st_query_stats.ul_rx_alg_process_dropped + pst_dmac_vap->st_query_stats.ul_rx_security_check_fail_dropped),
                        pst_dmac_vap->st_query_stats.ul_rx_null_frame_dropped,
                        pst_dmac_vap->st_query_stats.ul_rx_mgmt_mpdu_num_cnt);
#endif
    oal_memcopy(&st_vap_dft_stats,
                &(pst_dmac_vap->st_query_stats),
                OAL_SIZEOF(dmac_vap_query_stats_stru));

    return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_vap_dft_stats,(oal_uint16)OAL_SIZEOF(dmac_vap_query_stats_stru),OAM_OTA_TYPE_VAP_STAT);
}

/*****************************************************************************
 函 数 名  : dmac_config_set_phy_stat_en
 功能描述  : 设置phy统计使能节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月13日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_phy_stat_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oam_stats_phy_node_idx_stru     *pst_phy_node_idx;
    mac_device_stru                 *pst_mac_dev;

    pst_phy_node_idx = (oam_stats_phy_node_idx_stru *)puc_param;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_phy_stat_en::dev is null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return dmac_dft_set_phy_stat_node(pst_mac_dev, pst_phy_node_idx);
}

/*****************************************************************************
 函 数 名  : dmac_config_dbb_env_param
 功能描述  : 上报或者停止上报空口环境类维测参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月15日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dbb_env_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    if (OAL_FALSE == *puc_param)
    {
        /* 停止上报，并清除资源 */
        return dmac_dft_stop_report_dbb_env(pst_mac_vap);
    }
    else
    {
        /* 开始周期(20ms)采集,周期(2s)上报 */
        return dmac_dft_start_report_dbb_env(pst_mac_vap);
    }
}

/*****************************************************************************
 函 数 名  : dmac_config_report_irq_info
 功能描述  : 显示各类中断个数次数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月8日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_report_irq_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)

    mac_device_stru    *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_show_irq_info::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_show_irq_info(pst_device->pst_device_stru, *puc_param);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_report_all_stat
 功能描述  : 上报或者清零所有维测统计信息
 输入参数  : puc_param:"Hisilicon0 reprt_all_stat type(phy/machw/mgmt/irq/all)  0|1"
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月20日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_report_all_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int8             *pc_token_type;
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_uint8             uc_val;

    /* 获取要读取的寄存器类型 */
    pc_token_type = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token_type)
    {
        return OAL_FAIL;
    }
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    uc_val = (oal_uint8)oal_strtol(pc_token, &pc_end, 16);

    if (0 == oal_strcmp(pc_token, "soc"))
    {
        if (OAL_TRUE == uc_val)
        {
            dmac_config_phy_stat_info(pst_mac_vap, uc_len, &uc_val);
        }
    }
    else if (0 == oal_strcmp(pc_token, "machw"))
    {
        dmac_config_machw_stat_info(pst_mac_vap, uc_len, &uc_val);
    }
    else if (0 == oal_strcmp(pc_token, "mgmt"))
    {
        dmac_config_report_mgmt_stat(pst_mac_vap, uc_len, &uc_val);
    }
    else if (0 == oal_strcmp(pc_token, "irq"))
    {
        dmac_config_report_irq_info(pst_mac_vap, uc_len, &uc_val);
    }
    else
    {
        dmac_config_report_irq_info(pst_mac_vap, uc_len, &uc_val);
        dmac_config_report_mgmt_stat(pst_mac_vap, uc_len, &uc_val);
        dmac_config_machw_stat_info(pst_mac_vap, uc_len, &uc_val);
        if (OAL_TRUE == uc_val)
        {
            dmac_config_phy_stat_info(pst_mac_vap, uc_len, &uc_val);
        }
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_config_user_info
 功能描述  : 打印dmac的user信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月29日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_user_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* mips????????,??????? */
#ifndef _PRE_WLAN_PROFLING_MIPS
    dmac_user_stru                  *pst_dmac_user;
    mac_cfg_user_info_param_stru    *pst_dmac_event;
    oam_output_type_enum_uint8      en_output_type  = OAM_OUTPUT_TYPE_BUTT;
    oal_uint8                       uc_tid_index;
    //oal_uint32                      ul_tid_mpdu_num    = 0;

    /* 获取dmac user */
    pst_dmac_event = (mac_cfg_user_info_param_stru *)puc_param;
    pst_dmac_user  = (dmac_user_stru *)mac_res_get_dmac_user(pst_dmac_event->us_user_idx);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_user_info::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_config_user_info::us_assoc_id is %d, last_active_timestamp[%u]}",
                     pst_dmac_user->st_user_base_info.us_assoc_id, pst_dmac_user->ul_last_active_timestamp);
#if 0
    for (uc_tid_index = 0; uc_tid_index < WLAN_TID_MAX_NUM; uc_tid_index ++)
    {
        ul_tid_mpdu_num += pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num;
        if(pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num)
        {
            OAL_IO_PRINT("TID[%d],mpdu_num[%d],retry[%d],paused[%d]\r\n",
                   uc_tid_index,
                   pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num,
                   pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_retry_num,
                   pst_dmac_user->ast_tx_tid_queue[uc_tid_index].c_is_paused);
        }
    }
    OAL_IO_PRINT("dmac_config_user_info:totoal tid_mpdu_num %d\r\n", ul_tid_mpdu_num);
#endif
    oam_get_output_type(&en_output_type);
    if (OAM_OUTPUT_TYPE_SDT != en_output_type)
    {
#if 0
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_lut_index :        %d \n", pst_dmac_user->uc_lut_index);
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "bit_ps :              %d \n", pst_dmac_user->bit_ps_mode);
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "en_vip_flag :         %d \n", pst_dmac_user->en_vip_flag);
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "en_smartant_training :%d \n", pst_dmac_user->en_smartant_training);
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "\n");

        for (uc_tid_index = 0; uc_tid_index < WLAN_TID_MAX_NUM; uc_tid_index ++)
        {
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "tid               %d \n", uc_tid_index);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_is_paused : %d \n", (oal_uint8)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].c_is_paused);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_dq : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_dq);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_retry_num : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_retry_num);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "us_mpdu_num : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "ul_mpdu_avg_len : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].ul_mpdu_avg_len);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_tx_ba : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_tx_ba);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_rx_ba : %d \n", pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_rx_ba);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "pst_ba_tx_hdl : %u \n", (oal_uint32)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].pst_ba_tx_hdl);
            OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "pst_ba_rx_hdl : %u \n\n", (oal_uint32)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].pst_ba_rx_hdl);
        }

        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "power save related user_info:\n");
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "mpdu num in ps_queue-->%d\n", oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num));
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "user ps mode is -->%d\n", pst_dmac_user->bit_ps_mode);
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "pspoll process state is -->%d\n", pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing);
#endif

        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_lut_index[%d]; bit_ps[%d];en_vip_flag[%d];en_smartant_training[%d]\n",
                      pst_dmac_user->uc_lut_index, pst_dmac_user->bit_ps_mode, pst_dmac_user->en_vip_flag, pst_dmac_user->en_smartant_training);

        for (uc_tid_index = 0; uc_tid_index < WLAN_TID_MAX_NUM; uc_tid_index++)
        {
            OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "tid[%d]; uc_is_paused[%d]\n",
                          uc_tid_index, (oal_uint8)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_is_paused);

            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_dq[%d]; uc_retry_num[%d]; us_mpdu_num[%d]; ul_mpdu_avg_len[%d]\n",
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_dq,
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_retry_num,
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].us_mpdu_num,
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].ul_mpdu_avg_len);

            OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_num_tx_ba[%d]; uc_num_rx_ba[%d]; pst_ba_tx_hdl[%u]; pst_ba_rx_hdl[%u]\n",
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_tx_ba,
                          pst_dmac_user->ast_tx_tid_queue[uc_tid_index].uc_num_rx_ba,
                          (oal_uint32)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].pst_ba_tx_hdl,
                          (oal_uint32)pst_dmac_user->ast_tx_tid_queue[uc_tid_index].pst_ba_rx_hdl);
        }

        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "power save related user_info:mpdu num in ps_queue[%d]; user ps mode[%d]; pspoll process state[%d]\n",
                      oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num),
                      pst_dmac_user->bit_ps_mode,
                      pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing);
    }
    else
    {
        oam_ota_report((oal_uint8 *)&pst_dmac_user->uc_lut_index,
                       (oal_uint16)(OAL_SIZEOF(dmac_user_stru) - OAL_SIZEOF(mac_user_stru)),
                       0, 0, OAM_OTA_TYPE_DMAC_USER);
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_set_dscr
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月31日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_dscr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_set_dscr_param_stru     *pst_event_set_dscr;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_event_set_dscr = (mac_cfg_set_dscr_param_stru *)puc_param;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    /* 若输入默认的set_ucast_data命令, 则将所有针对特定协议的配置valid标志清0 */
    if (pst_event_set_dscr->en_type == MAC_VAP_CONFIG_UCAST_DATA)
    {
        pst_dmac_vap->un_mode_valid.uc_mode_param_valid = 0;
    }
    /* 否则, 如果是输入新的set_mode_ucast_data命令, 则将对应协议的配置valid标志置1 */
    else if (pst_event_set_dscr->en_type >= MAC_VAP_CONFIG_MODE_UCAST_DATA)
    {
        switch (pst_event_set_dscr->en_type)
        {
            case MAC_VAP_CONFIG_VHT_UCAST_DATA:
                pst_dmac_vap->un_mode_valid.st_spec_mode.bit_vht_param_vaild = 1;
                break;
            case MAC_VAP_CONFIG_HT_UCAST_DATA:
                pst_dmac_vap->un_mode_valid.st_spec_mode.bit_ht_param_vaild = 1;
                break;
            case MAC_VAP_CONFIG_11AG_UCAST_DATA:
                pst_dmac_vap->un_mode_valid.st_spec_mode.bit_11ag_param_vaild = 1;
                break;
            case MAC_VAP_CONFIG_11B_UCAST_DATA:
                pst_dmac_vap->un_mode_valid.st_spec_mode.bit_11b_param_vaild = 1;
                break;
            default:
                OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_dscr::pst_event_set_dscr->en_type = %u, invalid}", pst_event_set_dscr->en_type);
                return OAL_FAIL;
        }
    }
#endif

    g_dmac_config_set_dscr_param[pst_event_set_dscr->uc_function_index](pst_event_set_dscr->l_value,
                                                                        pst_event_set_dscr->en_type,
                                                                        pst_dmac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_log_level
 功能描述  : 设置日志级别
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月21日
    作    者   : jwx222439
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_log_level(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    // 设置device log level，业务添加处理逻辑
    return oam_log_set_vap_level(pst_mac_vap->uc_vap_id, *puc_param);
}

/*****************************************************************************
 函 数 名  : dmac_config_set_feature_log
 功能描述  : 设置日志特性
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月21日
    作    者   : jwx222439
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_feature_log(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    // 设置device log level，业务添加处理逻辑
    oal_uint16      us_param;
    us_param = *(oal_uint16 *)puc_param;
    return oam_log_set_feature_level(pst_mac_vap->uc_vap_id, (oal_uint8)(us_param>>8), (oal_uint8)us_param) ;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_log_lowpower
 功能描述  : 设置日志低功耗模式开启
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月21日
    作    者   : z00274374
    修改内容   : 新生成函数

*****************************************************************************/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC oal_uint32 dmac_config_set_log_lowpower(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    // 设置device log level，业务添加处理逻辑
    oal_uint8      uc_param = *(oal_uint8 *)puc_param;
    return oam_log_set_pm_enable((oal_uint8)uc_param) ;
}

OAL_STATIC oal_uint32 dmac_config_set_pm_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    // 设置device log level，业务添加处理逻辑
    oal_uint8      uc_param = *(oal_uint8 *)puc_param;

    g_pm_switch = uc_param;

    OAM_WARNING_LOG1(0, OAM_SF_PWR, "dmac_config_set_pm_switch %d", g_pm_switch);

    return OAL_SUCC ;
}

#endif
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/*****************************************************************************
 函 数 名  : is_fcc_country
 功能描述  : 判断是否是有FCC认证的国家
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2016年1月11日
    作    者   : huchikun
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 is_fcc_country(oal_int8* country_code)
{
    oal_int8   *ac_fcc_country[] = {"AR", "BR", "CA", "CL", "IN", "MX", "PR", "US", "VE", OAL_PTR_NULL};
    oal_int8  **pp_country = ac_fcc_country;

    while (*pp_country != OAL_PTR_NULL)
    {
        if (oal_memcmp(country_code, *(pp_country++), WLAN_COUNTRY_STR_LEN) == 0)
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_config_set_country
 功能描述  : 设置国家码信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月7日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_country(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_regdomain_info_stru *pst_mac_regdom;
    mac_regdomain_info_stru *pst_regdomain_info;
    oal_uint8                uc_rc_num;
    oal_uint32               ul_size;
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    mac_device_stru                     *pst_mac_device = OAL_PTR_NULL;
    hal_to_dmac_device_stru             *pst_hal_device = OAL_PTR_NULL;
#endif

    pst_mac_regdom = (mac_regdomain_info_stru *)puc_param;

    /* 获取管制类的个数 */
    uc_rc_num = pst_mac_regdom->uc_regclass_num;

    /* 计算配置命令 */
    ul_size = OAL_SIZEOF(mac_regclass_info_stru) * uc_rc_num + MAC_RD_INFO_LEN;
    /*获取管制域全局变量*/
    mac_get_regdomain_info(&pst_regdomain_info);

    /* 更新管制域信息 */
    oal_memcopy(pst_regdomain_info, pst_mac_regdom, ul_size);

    /* 更新信道的管制域信息 */
    mac_init_channel_list();

#ifdef _PRE_SUPPORT_ACS
    dmac_acs_report_support_chan(pst_mac_vap);
#endif
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    /* 对于有FCC认证要求的国家，调整边带dbb scaling值，降低发射功率 */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_DFS, "dmac_config_set_country::pst_mac_device null.device:%u",pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    /* 根据是否FCC认证要求国家，更新标志位 */
    pst_hal_device->uc_fcc_country = is_fcc_country(pst_mac_regdom->ac_country) ? OAL_TRUE : OAL_FALSE;
#endif

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_DFS
/*****************************************************************************
 函 数 名  : dmac_config_set_country_for_dfs
 功能描述  : 设置国家码中dfs信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : zhangxiang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_country_for_dfs(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_dfs_domain_enum_uint8       en_dfs_domain;
    hal_to_dmac_device_stru        *pst_hal_device;
    mac_device_stru                *pst_mac_device;

    en_dfs_domain = *puc_param;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_DFS, "dmac_config_set_country_for_dfs::mac_res_get_dev fail.device:%u",pst_mac_vap->uc_device_id);
        return OAL_FAIL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    if(OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_DFS, "dmac_config_set_country_for_dfs::pointer null.");
        return OAL_FAIL;
    }

    hal_radar_config_reg(pst_hal_device, en_dfs_domain);

    pst_hal_device->st_dfs_radar_filter.ul_last_burst_timestamp           = 0;
    pst_hal_device->st_dfs_radar_filter.ul_last_burst_timestamp_for_chirp = 0;
    pst_hal_device->st_dfs_radar_filter.en_chirp_enable                   = 1;
    pst_hal_device->st_dfs_radar_filter.ul_time_threshold                 = 100;
    switch(en_dfs_domain)
    {
        case MAC_DFS_DOMAIN_ETSI:
            pst_hal_device->st_dfs_radar_filter.ul_chirp_cnt_threshold  = 3;
            pst_hal_device->st_dfs_radar_filter.ul_chirp_time_threshold = 100;
            break;
        case MAC_DFS_DOMAIN_FCC:
            pst_hal_device->st_dfs_radar_filter.ul_chirp_cnt_threshold  = 4;
            pst_hal_device->st_dfs_radar_filter.ul_chirp_time_threshold = 12000;
            break;
        default :
            break;
    }

    OAM_WARNING_LOG0(0, OAM_SF_DFS, "{dmac_config_set_country_for_dfs::set radar filter params.}");

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_alrxtx_set_pm
 功能描述  : 常发常发设置低功耗
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_alrxtx_set_pm(mac_vap_stru *pst_mac_vap, oal_uint32 ul_switch)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_bool_enum_uint8              en_pm_switch;

    en_pm_switch = ((OAL_SWITCH_OFF == ul_switch) ? OAL_TRUE : OAL_FALSE);
    dmac_config_set_pm_switch(pst_mac_vap, 0, &en_pm_switch);
#endif

    return OAL_SUCC;
}



#if 0
/*****************************************************************************
 函 数 名  : dmac_config_list_channel
 功能描述  : 上报国家码信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : zhangxiang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_list_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_regdomain_info_stru *pst_regdomain_info                     = OAL_PTR_NULL;
    oal_uint8                uc_chan_num;
    oal_uint8                uc_chan_idx;
    oal_uint32               ul_ret                                 = OAL_FAIL;
    oal_int8                 ac_string[OAM_PRINT_FORMAT_LENGTH];
    oal_int8                *pc_str_offset;
    mac_regclass_info_stru  *pst_rc_info;

    mac_get_regdomain_info(&pst_regdomain_info);

    OAL_SPRINTF(ac_string, sizeof(ac_string), "Country is: %s %s\n",
                pst_regdomain_info->ac_country,
                "2G(chan_num reg_tx_pwr max_tx_pwr):\n");
    for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_chan_idx++)
    {
        pc_str_offset = ac_string + OAL_STRLEN(ac_string);
        ul_ret = mac_is_channel_idx_valid(MAC_RC_START_FREQ_2, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(MAC_RC_START_FREQ_2, uc_chan_idx, &uc_chan_num);
            pst_rc_info = mac_get_channel_idx_rc_info(WLAN_BAND_2G, uc_chan_idx);
            OAL_IO_PRINT("%d,%d,%d\r\n", uc_chan_num, pst_rc_info->uc_max_reg_tx_pwr, pst_rc_info->uc_max_tx_pwr);
            OAL_SPRINTF(pc_str_offset, 10, "%d %d %d\n", uc_chan_num, pst_rc_info->uc_max_reg_tx_pwr, pst_rc_info->uc_max_tx_pwr);
        }
    }

    oam_print(ac_string);

    OAL_SPRINTF(ac_string, sizeof(ac_string), "%s", "5G(chan_num reg_tx_pwr max_tx_pwr):\n");
    for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT/2; uc_chan_idx++)
    {
        pc_str_offset = ac_string + OAL_STRLEN(ac_string);
        ul_ret = mac_is_channel_idx_valid(MAC_RC_START_FREQ_5, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(MAC_RC_START_FREQ_5, uc_chan_idx, &uc_chan_num);
            pst_rc_info = mac_get_channel_idx_rc_info(WLAN_BAND_5G, uc_chan_idx);
            OAL_SPRINTF(pc_str_offset, 12, "%d %d %d\n", uc_chan_num, pst_rc_info->uc_max_reg_tx_pwr, pst_rc_info->uc_max_tx_pwr);
        }
    }
    oam_print(ac_string);

    ac_string[0] = '\0';
    for (uc_chan_idx = MAC_CHANNEL_FREQ_5_BUTT/2; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_chan_idx++)
    {
        pc_str_offset = ac_string + OAL_STRLEN(ac_string);
        ul_ret = mac_is_channel_idx_valid(MAC_RC_START_FREQ_5, uc_chan_idx);
        if (OAL_SUCC == ul_ret)
        {
            mac_get_channel_num_from_idx(MAC_RC_START_FREQ_5, uc_chan_idx, &uc_chan_num);
            pst_rc_info = mac_get_channel_idx_rc_info(WLAN_BAND_5G, uc_chan_idx);
            OAL_SPRINTF(pc_str_offset, 12, "%d %d %d\n", uc_chan_num, pst_rc_info->uc_max_reg_tx_pwr, pst_rc_info->uc_max_tx_pwr);
        }
    }
    oam_print(ac_string);
    return OAL_SUCC;
}
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_config_set_regdomain_pwr
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : zhangxiang
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32   dmac_config_set_regdomain_pwr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_regdomain_max_pwr_stru *pst_cfg;

    pst_cfg = (mac_cfg_regdomain_max_pwr_stru *)puc_param;

    mac_regdomain_set_max_power(pst_cfg->uc_pwr, pst_cfg->en_exceed_reg);

    return OAL_SUCC;

}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_reduce_sar
 功能描述  : 降SAR
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : huchikun
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_reduce_sar(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru*        pst_mac_device;
    oal_uint32              ul_ret;
    /* 刷新supplicant下发的芯片口功率限制值 */
    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_reduce_sar::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_device->uc_sar_pwr_limit = *puc_param;
    /* 通知算法信道改变 */
    ul_ret = dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_reduce_sar:dmac_alg_cfg_channel_notify FAIL!}");
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_set_rate
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
OAL_STATIC oal_uint32  dmac_config_set_rate(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_non_ht_rate_stru        *pst_event_set_rate;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rate::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 设置数据 */
    pst_event_set_rate = (mac_cfg_non_ht_rate_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate = pst_event_set_rate->en_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_event_set_rate->en_protocol_mode;

    /* 使用长前导码，兼容1Mbps */
    if (WLAN_LEGACY_11b_RESERVED1 == pst_event_set_rate->en_rate)
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode = 1;
    }

    /* 更新协议速率 */
    pst_dmac_vap->uc_protocol_rate_dscr = (oal_uint8)((pst_event_set_rate->en_protocol_mode << 6) | pst_event_set_rate->en_rate);

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
    /* 根据模式、频点、带宽、速率来设置DAC和LPF增益 */
    hal_set_dac_lpf_gain(pst_dmac_vap->pst_hal_device, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_rate->en_protocol_mode, pst_event_set_rate->en_rate);
#else
#ifdef _PRE_WLAN_HW_TEST
    hal_set_dac_lpf_gain(pst_dmac_vap->pst_hal_device, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_rate->en_protocol_mode, pst_event_set_rate->en_rate);
#endif
#endif

    /* 常发模式下在线配置 */
    if (OAL_SWITCH_ON == pst_dmac_vap->pst_hal_device->uc_al_tx_flag)
    {
       hal_set_tx_dscr_field(pst_dmac_vap->pst_hal_device, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rate::en_rate=%d,protocol=%d.",
                    pst_event_set_rate->en_rate, pst_event_set_rate->en_protocol_mode);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_set_mcs
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_mcs(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_mcs;
    dmac_vap_stru                   *pst_dmac_vap;


    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_event_set_mcs = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = pst_event_set_mcs->uc_param;

#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
    /* 根据模式、频点、带宽、速率来设置DAC和LPF增益 */
    hal_set_dac_lpf_gain(pst_dmac_vap->pst_hal_device, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_mcs->en_protocol_mode, pst_event_set_mcs->uc_param);
#else
#ifdef _PRE_WLAN_HW_TEST
    hal_set_dac_lpf_gain(pst_dmac_vap->pst_hal_device, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_mcs->en_protocol_mode, pst_event_set_mcs->uc_param);
#endif
#endif

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_event_set_mcs->en_protocol_mode;

    /* 更新速率及协议模式 */
    pst_dmac_vap->uc_protocol_rate_dscr = (oal_uint8)((pst_event_set_mcs->en_protocol_mode << 6) | pst_event_set_mcs->uc_param);

    /* 常发模式下在线配置 */
    if (OAL_SWITCH_ON == pst_dmac_vap->pst_hal_device->uc_al_tx_flag)
    {
        hal_set_tx_dscr_field(pst_dmac_vap->pst_hal_device, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::tx dscr mcs=%d.", pst_event_set_mcs->uc_param);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_set_mcsac
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_mcsac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_mcsac;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcsac::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 设置数据 */
    pst_event_set_mcsac = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_vht_mcs = pst_event_set_mcsac->uc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_event_set_mcsac->en_protocol_mode;

    /* 更新协议速率 */
    pst_dmac_vap->uc_protocol_rate_dscr = (oal_uint8)((pst_event_set_mcsac->en_protocol_mode << 6) | pst_event_set_mcsac->uc_param);
#if (_PRE_MULTI_CORE_MODE==_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC)
    /* 根据模式、频点、带宽、速率来设置DAC和LPF增益 */
    hal_set_dac_lpf_gain(pst_dmac_vap->pst_hal_device, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_mcsac->en_protocol_mode, pst_event_set_mcsac->uc_param);
#else
#ifdef _PRE_WLAN_HW_TEST
    hal_set_dac_lpf_gain(pst_dmac_vap->pst_hal_device, pst_mac_vap->st_channel.en_band, pst_mac_vap->st_channel.en_bandwidth, pst_event_set_mcsac->en_protocol_mode, pst_event_set_mcsac->uc_param);
#endif
#endif

    /* 常发模式下在线配置 */
    if (OAL_SWITCH_ON == pst_dmac_vap->pst_hal_device->uc_al_tx_flag)
    {
        hal_set_tx_dscr_field(pst_dmac_vap->pst_hal_device, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::tx dscr mcsac=%d.", pst_event_set_mcsac->uc_param);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_set_nss
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_nss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_nss;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_nss::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 设置数据 */
    pst_event_set_nss = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_nss_mode = pst_event_set_nss->uc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_event_set_nss->en_protocol_mode;

    /* 更新协议速率 */
    pst_dmac_vap->uc_protocol_rate_dscr = (oal_uint8)((pst_event_set_nss->en_protocol_mode << 6) | pst_event_set_nss->uc_param);

    if (OAL_SWITCH_ON == pst_dmac_vap->pst_hal_device->uc_al_tx_flag)
    {
        hal_set_tx_dscr_field(pst_dmac_vap->pst_hal_device, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::tx dscr nss=%d.", pst_event_set_nss->uc_param);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_set_rfch
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_rfch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_rfch;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rfch::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 设置数据 */
    pst_event_set_rfch = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_event_set_rfch->uc_param;

    /* 常发模式下在线配置 */
    if (OAL_SWITCH_ON == pst_dmac_vap->pst_hal_device->uc_al_tx_flag)
    {
        hal_set_tx_dscr_field(pst_dmac_vap->pst_hal_device, pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value, HAL_RF_TEST_DATA_RATE_ZERO);
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_mcs::tx dscr tx chain selection=%d.", pst_event_set_rfch->uc_param);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_set_bw
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_bw(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_bw;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_bw::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


     /* 设置数据 */
    pst_event_set_bw = (mac_cfg_tx_comp_stru *)puc_param;
    pst_dmac_vap->st_tx_data_mcast.st_rate.uc_channel_bandwidth = pst_event_set_bw->uc_param;

    pst_dmac_vap->uc_bw_flag = pst_event_set_bw->uc_param;

    /* 常发模式下在线配置 */
    if (OAL_SWITCH_ON == pst_dmac_vap->pst_hal_device->uc_al_tx_flag)
    {
        hal_set_tx_dscr_field(pst_dmac_vap->pst_hal_device, pst_event_set_bw->uc_param, HAL_RF_TEST_BAND_WIDTH);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_always_tx
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_always_tx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_al_tx;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint32                       ul_ret;

    pst_event_set_al_tx = (mac_cfg_tx_comp_stru *)puc_param;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 设置常发模式标志 */
    mac_vap_set_al_tx_flag(pst_mac_vap, pst_event_set_al_tx->uc_param);
    mac_vap_set_al_tx_payload_flag(pst_mac_vap, pst_event_set_al_tx->en_payload_flag);
    pst_dmac_vap->pst_hal_device->uc_al_tx_flag = pst_event_set_al_tx->uc_param;
    pst_dmac_vap->pst_hal_device->bit_al_tx_flag = pst_event_set_al_tx->uc_param;

    if (OAL_SWITCH_OFF == pst_dmac_vap->pst_hal_device->uc_al_tx_flag)
    {
        pst_mac_vap->st_cap_flag.bit_keepalive = OAL_TRUE;
        hal_rf_test_disable_al_tx(pst_dmac_vap->pst_hal_device);
        mac_vap_set_al_tx_first_run(pst_mac_vap, OAL_FALSE);
    }
    else
    {
        ul_ret = dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx:dmac_config_al_tx_set_pow fail!}");
            return ul_ret;
        }
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
/*****************************************************************************
 函 数 名  : dmac_config_al_set_addresses
 功能描述  : 常发设置地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_al_tx_set_addresses(
                mac_vap_stru                           *pst_vap,
                mac_ieee80211_frame_stru  *pst_hdr)
{
    oal_uint8       auc_bcst[6] = {0xff,0xff,0xff,0xff,0xff,0xff};

    /* From DS标识位设置 */
    mac_hdr_set_from_ds((oal_uint8 *)pst_hdr, 0);

    /* to DS标识位设置 */
    mac_hdr_set_to_ds((oal_uint8 *)pst_hdr, 1);

    /* Set Address1 field in the WLAN Header with BSSID */
    oal_set_mac_addr(pst_hdr->auc_address1, auc_bcst);


    /* Set Address2 field in the WLAN Header with the source address */
    oal_set_mac_addr(pst_hdr->auc_address2, pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* Set Address3 field in the WLAN Header with the destination address */
    oal_set_mac_addr(pst_hdr->auc_address3, auc_bcst);

	return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_al_tx_set_frame_ctrl
 功能描述  : 常发设置frame ctrl字段
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_al_tx_set_frame_ctrl(
                                                      mac_tx_ctl_stru                         *pst_tx_ctl,
                                                      mac_ieee80211_frame_stru  *pst_hdr)
{
    /* 设置帧控制字段 */
    mac_hdr_set_frame_control((oal_uint8 *)pst_hdr, WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_DATA);

    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl) = MAC_80211_FRAME_LEN;

	return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_al_tx_packet_send
 功能描述  : 常发发送数据
 输入参数  : pst_vap pst_buf
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_al_tx_packet_send(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf)
{
    frw_event_mem_stru    *pst_event_mem;
    //oal_uint32             ul_ret = HMAC_TX_PASS;
    frw_event_stru        *pst_event;
    dmac_tx_event_stru    *pst_dtx_stru;

    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_tx_event_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{hmac_tx_lan_to_wlan::FRW_EVENT_ALLOC failed.}");
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        pst_vap->st_vap_stats.ul_tx_dropped_packets++;
#endif
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_HOST_DRX,
                        DMAC_TX_HOST_DRX,
                        OAL_SIZEOF(dmac_tx_event_stru),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_vap->uc_chip_id,
                        pst_vap->uc_device_id,
                        pst_vap->uc_vap_id);

    pst_dtx_stru             = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dtx_stru->pst_netbuf = pst_buf;

    dmac_tx_process_data_event(pst_event_mem);

     /* 释放事件 */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;

}
/*****************************************************************************
 函 数 名  : dmac_config_al_tx_packet
 功能描述  : 常发设置cb字段
 输入参数  : pst_vap pst_buf
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_al_tx_packet(mac_vap_stru *pst_vap, oal_netbuf_stru *pst_buf, oal_uint32 ul_len)
{
    mac_tx_ctl_stru                     *pst_tx_ctl;       /* SKB CB */
    mac_ieee80211_qos_htc_frame_stru    *pst_hdr;

    /* 初始化CB tx rx字段 , CB字段在前面已经被清零， 在这里不需要重复对某些字段赋零值*/

    /* netbuff需要申请内存  */
    pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);
    MAC_GET_CB_MPDU_NUM(pst_tx_ctl)                  = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctl)                       = 1;
    MAC_GET_CB_FRAME_TYPE(pst_tx_ctl)             = WLAN_DATA_BASICTYPE;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctl)          = DMAC_USER_ALG_NON_PROBE;
    //MAC_GET_CB_EN_ACK_POLICY(pst_tx_ctl)             = WLAN_TX_NORMAL_ACK;
    mac_set_cb_ack_policy(pst_tx_ctl, WLAN_TX_NO_ACK);
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl)           = pst_vap->uc_vap_id;
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_VO);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl)             = FRW_EVENT_TYPE_WLAN_DTX;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)           = (oal_uint8)pst_vap->us_multi_user_idx;
    mac_set_cb_80211_mac_head_type(pst_tx_ctl, 0); /*指示mac头部不在skb中，申请了额外内存存放的*/
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)    = MAC_80211_FRAME_LEN;
    MAC_GET_CB_IS_MCAST(pst_tx_ctl) = OAL_TRUE;

    pst_hdr = (mac_ieee80211_qos_htc_frame_stru *)OAL_NETBUF_HEADER(pst_buf);
    pst_hdr->bit_qc_amsdu = OAL_FALSE;

    /* 挂接802.11头,在data_tx里会将802.11头全部清0 */
    dmac_config_al_tx_set_frame_ctrl(pst_tx_ctl,(mac_ieee80211_frame_stru *)pst_hdr);
    dmac_config_al_tx_set_addresses(pst_vap, (mac_ieee80211_frame_stru *)pst_hdr);
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)pst_hdr);

    /* 更新frame长度 */
    MAC_GET_CB_MPDU_BYTES(pst_tx_ctl) = (oal_uint16)ul_len;
    //MAC_GET_CB_MPDU_LEN(pst_tx_ctl) = (oal_uint16)ul_len;
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_create_al_tx_packet
 功能描述  : 随便组一个报文
 输入参数  : size表示报文长度， 包含以太网头部， 不包括FCS， 取值范围应该为60~1514
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_netbuf_stru*  dmac_config_create_al_tx_packet(oal_uint32 ul_size,
                                                    mac_rf_payload_enum_uint8        en_payload_flag)
{
    oal_netbuf_stru         *pst_buf;
    oal_uint32               ul_loop = 0;
    oal_uint8                       *puc_data;

    //pst_buf = OAL_MEM_NETBUF_ALLOC((oal_uint16)ul_size, OAL_TRUE);/* 需要换成刘正奇提供的专门接口 */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if(WLAN_LARGE_NETBUF_SIZE >= ul_size)
    {
        pst_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (oal_uint16)ul_size, OAL_NETBUF_PRIORITY_MID);
    }
    else
    {
        pst_buf = OAL_MEM_MULTI_NETBUF_ALLOC((oal_uint16)ul_size);
    }
#else
    pst_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (oal_uint16)ul_size, OAL_NETBUF_PRIORITY_MID);
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "dmac_config_create_al_tx_packet::alloc Fail");
        return OAL_PTR_NULL;
    }

    //oal_netbuf_put(pst_buf, ul_size);
    puc_data = OAL_NETBUF_DATA(pst_buf);
    switch (en_payload_flag)
    {
        case RF_PAYLOAD_ALL_ZERO:
            OAL_MEMZERO(puc_data, ul_size);
            break;
        case RF_PAYLOAD_ALL_ONE:
            oal_memset(puc_data, 0xFF, ul_size);
            break;
        case RF_PAYLOAD_RAND:
            puc_data[0] = oal_gen_random(18, 1);
            for (ul_loop = 1; ul_loop < ul_size; ul_loop++)
            {
                puc_data[ul_loop] = oal_gen_random(18, 0);
            }
            break;
        default:
        	break;
    }

    pst_buf->next = OAL_PTR_NULL;
    //pst_buf->prev = OAL_PTR_NULL;

    OAL_MEMZERO(oal_netbuf_cb(pst_buf), OAL_TX_CB_LEN);

    return pst_buf;
}

/*****************************************************************************
 函 数 名  : dmac_config_bcast_pkt
 功能描述  : 广播数据包
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_al_tx_bcast_pkt(mac_vap_stru *pst_mac_vap, oal_uint32 ul_len)
{
    oal_netbuf_stru                *pst_netbuf;
    oal_uint32                      ul_ret;

    /* 组包 */
    pst_netbuf = dmac_config_create_al_tx_packet(ul_len, (oal_uint8)pst_mac_vap->bit_payload_flag);

    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_bcast_pkt::return null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写cb和mac头 */
    ul_ret = dmac_config_al_tx_packet(pst_mac_vap, pst_netbuf, ul_len);

    /* 发送数据 */
    ul_ret |= dmac_config_al_tx_packet_send(pst_mac_vap, pst_netbuf);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_bcast_pkt::hmac_tx_lan_to_wlan return error %d!}\r\n", ul_ret);
    }

    return ul_ret;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_always_tx
 功能描述  : 设置描述符参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月4日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_always_tx_1102(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_tx_comp_stru            *pst_event_set_al_tx;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint32                       ul_ret;
#ifndef WIN32
    mac_device_stru                 *pst_mac_device;
#endif  /* WIN32 */

    pst_event_set_al_tx = (mac_cfg_tx_comp_stru *)puc_param;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 设置常发模式标志 */
    mac_vap_set_al_tx_flag(pst_mac_vap, pst_event_set_al_tx->uc_param);
    mac_vap_set_al_tx_payload_flag(pst_mac_vap, pst_event_set_al_tx->en_payload_flag);
    pst_dmac_vap->pst_hal_device->uc_al_tx_flag = pst_event_set_al_tx->uc_param;
    pst_dmac_vap->pst_hal_device->bit_al_tx_flag = pst_event_set_al_tx->uc_param;

    /* 先关闭寄存器 */
    pst_mac_vap->st_cap_flag.bit_keepalive = OAL_TRUE;
    //hal_rf_test_disable_al_tx(pst_hal_device_base);

    dmac_config_alrxtx_set_pm(pst_mac_vap, pst_dmac_vap->pst_hal_device->uc_al_tx_flag);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifndef WIN32
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_config_set_always_tx::pst_mac_device[%d] is NULL!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }


#ifdef _PRE_WLAN_FEATURE_STA_PM
    dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);
#endif   /* _PRE_WLAN_FEATURE_STA_PM */
#endif  /* WIN32 */
#endif

    if (OAL_SWITCH_ON == pst_dmac_vap->pst_hal_device->uc_al_tx_flag)
    {
        pst_mac_vap->st_cap_flag.bit_keepalive = OAL_FALSE;
        /* hal_rf_test_enable_al_tx寄存器和描述符在dmac_tx_data中完成  */
        /* 此处为了兼容51的开关，此处可以看成is_not_first_run */
        if (OAL_TRUE == pst_mac_vap->bit_first_run)
        {
            return OAL_SUCC;
        }
        mac_vap_set_al_tx_first_run(pst_mac_vap, OAL_TRUE);


        /* 更新TPC code表单并配置功率描述符 */
        ul_ret = dmac_alg_cfg_channel_notify(pst_mac_vap, CH_BW_CHG_TYPE_MOVE_WORK);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx_1102:dmac_config_al_tx_set_pow fail!}");
            return ul_ret;
        }

        return dmac_config_al_tx_bcast_pkt(pst_mac_vap, pst_event_set_al_tx->ul_payload_len);

    }
    else
    {
        pst_mac_vap->st_cap_flag.bit_keepalive = OAL_TRUE;
        hal_rf_test_disable_al_tx(pst_dmac_vap->pst_hal_device);
    #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
        dmac_config_update_rate_pow_table();        /* resume rate_pow_table */
        dmac_config_update_scaling_reg();           /* resume phy scaling reg */
    #endif  /* _PRE_PLAT_FEATURE_CUSTOMIZE */
        mac_vap_set_al_tx_first_run(pst_mac_vap, OAL_FALSE);
    }

    return OAL_SUCC;
}
#endif /* #ifdef _PRE_WLAN_FEATURE_ALWAYS_TX */

oal_uint32 g_ul_al_ampdu_num               = WLAN_AMPDU_TX_MAX_NUM; /*ampdu 常发聚合长度*/
oal_uint32 g_ul_al_mpdu_len                = 1510; /*指示常发mpdu长度， 可根据实际情况修改*/
//oal_uint32 g_ul_first_timestamp = 0;    /*记录性能统计第一次时间戳*/

/*****************************************************************************
 函 数 名  : dmac_config_always_rx_set_hal
 功能描述  : 设置常收模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 曹海彬
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_always_rx_set_hal(hal_to_dmac_device_stru *pst_hal_device_base, oal_uint8 uc_switch)
{
    /* 停止mac phy接收 */
    hal_disable_machw_phy_and_pa(pst_hal_device_base);

    if(uc_switch)
    {
        /* 释放所有正常接收描述符 */
        hal_rx_destroy_dscr_queue(pst_hal_device_base,OAL_TRUE);

        /* 初始化常收接收描述符队列 */
        hal_al_rx_init_dscr_queue(pst_hal_device_base);
    }
    else
    {
        /* 释放所有常收接收描述符队列 */
        hal_al_rx_destroy_dscr_queue(pst_hal_device_base);

        /* 初始化正常描述符队列 */
        hal_rx_init_dscr_queue(pst_hal_device_base,OAL_TRUE);
    }

    /* 恢复 mac phy接收*/
    hal_enable_machw_phy_and_pa(pst_hal_device_base);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_always_rx
 功能描述  : 设置常收模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月23日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_always_rx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                   *pst_dmac_vap;
#ifdef _PRE_WLAN_FEATURE_STA_PM
    mac_device_stru                 *pst_mac_device;
#endif  /* _PRE_WLAN_FEATURE_STA_PM */

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_rx::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 聚合帧个数更新，即使常收指令连续两次相同也要更新，以使常发生效 */
    pst_dmac_vap->pst_hal_device->bit_al_txrx_ampdu_num = g_ul_al_ampdu_num;

    /* 如果新下发的命令开关状态没变，则直接返回 */
    if(*(oal_bool_enum_uint8 *)puc_param == pst_dmac_vap->pst_hal_device->bit_al_rx_flag)
    {
        return OAL_SUCC;
    }

    /* 设置常收模式标志 */
    pst_dmac_vap->pst_hal_device->bit_al_rx_flag = *(oal_bool_enum_uint8 *)puc_param;
    dmac_config_alrxtx_set_pm(pst_mac_vap, pst_dmac_vap->pst_hal_device->bit_al_rx_flag);

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
#ifdef _PRE_WLAN_FEATURE_STA_PM
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_config_set_always_rx::pst_mac_device[%d] is NULL!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);
#endif  /* _PRE_WLAN_FEATURE_STA_PM */
#endif

#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_RX_RESERVED == pst_dmac_vap->pst_hal_device->bit_al_rx_flag)
    {
        hal_reg_write(pst_dmac_vap->pst_hal_device, WITP_PA_RX_FRAMEFILT_REG, 0x0);
    }
#endif

    /* 仅RF常收使用，AMPDU常收不需要此逻辑 */
    if ((HAL_ALWAYS_RX_RESERVED == pst_dmac_vap->pst_hal_device->bit_al_rx_flag)
    || (HAL_ALWAYS_RX_DISABLE == pst_dmac_vap->pst_hal_device->bit_al_rx_flag))
    {
        dmac_config_always_rx_set_hal(pst_dmac_vap->pst_hal_device, pst_dmac_vap->pst_hal_device->bit_al_rx_flag);
    }

    return OAL_SUCC;
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 函 数 名  : dmac_config_dync_txpower
 功能描述  : 设置动态功率校准开关
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月14日
    作    者   : pwx287475
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dync_txpower(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    hal_to_dmac_device_stru         *pst_hal_device_base;
    mac_device_stru                 *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device_base = pst_device->pst_device_stru;

    if (*puc_param == pst_hal_device_base->ul_dync_txpower_flag)
    {
        return OAL_SUCC;
    }

    pst_hal_device_base->ul_dync_txpower_flag = *puc_param;

    #ifdef _PRE_WLAN_REALTIME_CALI
    if (HAL_DOUBLE_CHIP_5G_ID == pst_hal_device_base->uc_chip_id)
    {
        OAL_IO_PRINT("dmac_config_dync_txpower:5G dync txpower can not use!\n");
        return OAL_SUCC;
    }

    /* 创建定时器 */
    if (1 == pst_hal_device_base->ul_dync_txpower_flag)
    {
        FRW_TIMER_CREATE_TIMER(&(pst_device->st_realtime_cali_timer),
                        dmac_rf_realtime_cali_timeout,
                        WLAN_REALTIME_CALI_INTERVAL,
                        pst_device,
                        OAL_TRUE,
                        OAM_MODULE_ID_DMAC,
                        pst_device->ul_core_id);
    }
    /* 删除定时器 */
    else if (0 == pst_hal_device_base->ul_dync_txpower_flag)
    {
        FRW_TIMER_STOP_TIMER(&pst_device->st_realtime_cali_timer);
    }
    #endif

    OAM_INFO_LOG1(0, OAM_SF_CFG, "dmac_config_dync_txpower:uc_dync_power_flag = %d\n", pst_hal_device_base->ul_dync_txpower_flag);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_get_thruput
 功能描述  : 获取芯片吞吐量信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : 曹海彬
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_thruput(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint32                       ul_rx_octects_in_ampdu;
    oal_uint32                       ul_tx_octects_in_ampdu;
    oal_uint32                       ul_rx_normal_mdpu_succ_num;
    oal_uint32                       ul_rx_ampdu_succ_num;
    oal_uint32                       ul_tx_ppdu_succ_num;
    oal_uint32                       ul_rx_ppdu_fail_num;
    oal_uint32                       ul_tx_ppdu_fail_num;
    oal_uint32                       ul_rx_ampdu_fcs_num;
    oal_uint32                       ul_rx_delimiter_fail_num;
    oal_uint32                       ul_rx_mpdu_fcs_num;
    oal_uint32                       ul_rx_phy_err_mac_passed_num;
    oal_uint32                       ul_rx_phy_longer_err_num;
    oal_uint32                       ul_rx_phy_shorter_err_num;
    oal_uint32                       ul_timestamp;
    oal_uint8                        uc_stage;       /*0为开始统计阶段， 1为结束统计阶段*/
    oal_uint32                       ul_rx_rate;     /*单位mpbs*/
    oal_uint32                       ul_tx_rate;     /*单位mpbs*/
    oal_uint32                       ul_time_offest; /*统计时间差, 单位ms*/
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_cpu_usage_stat_stru          st_cpu_stat;
    oal_uint64                       ull_alltime;
#endif
    mac_device_stru                 *pst_mac_device;
    oal_uint32                       ul_cycles = 0;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    frw_event_mem_stru             *pst_event_mem;
    frw_event_stru                 *pst_event_up;
    dmac_thruput_info_sync_stru     *pst_thruput_info_sync;
#endif

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_thruput::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_thruput::pst_dmac_vap or pst_dmac_vap->pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    uc_stage = *(oal_bool_enum_uint8 *)puc_param;

    if(0 == uc_stage)
    {
        pst_mac_device->ul_first_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    #if (!defined(_PRE_PC_LINT) && !defined(WIN32))
        enable_cycle_counter();
    #endif
    #endif

        /*清零*/
        hal_set_counter_clear(pst_dmac_vap->pst_hal_device);
        pst_dmac_vap->pst_hal_device->ul_rx_normal_mdpu_succ_num = 0;
        pst_dmac_vap->pst_hal_device->ul_rx_ampdu_succ_num = 0;
        pst_dmac_vap->pst_hal_device->ul_tx_ppdu_succ_num = 0;
        pst_dmac_vap->pst_hal_device->ul_rx_ppdu_fail_num = 0;
        pst_dmac_vap->pst_hal_device->ul_tx_ppdu_fail_num = 0;
    }
    else
    {
        ul_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
        ul_time_offest = ul_timestamp - pst_mac_device->ul_first_timestamp;

        #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        #if (!defined(_PRE_PC_LINT) && !defined(WIN32))
            disable_cycle_counter();

            ul_cycles = get_cycle_count();
        #endif
        #endif

        ul_rx_normal_mdpu_succ_num = pst_dmac_vap->pst_hal_device->ul_rx_normal_mdpu_succ_num;
        ul_rx_ampdu_succ_num = pst_dmac_vap->pst_hal_device->ul_rx_ampdu_succ_num;
        ul_tx_ppdu_succ_num = pst_dmac_vap->pst_hal_device->ul_tx_ppdu_succ_num;
        ul_rx_ppdu_fail_num = pst_dmac_vap->pst_hal_device->ul_rx_ppdu_fail_num;
        ul_tx_ppdu_fail_num = pst_dmac_vap->pst_hal_device->ul_tx_ppdu_fail_num;

        if (HAL_ALWAYS_TX_MPDU == pst_dmac_vap->pst_hal_device->bit_al_tx_flag)
        {
            ul_tx_rate = ((ul_tx_ppdu_succ_num + ul_tx_ppdu_fail_num)*g_ul_al_mpdu_len/(ul_time_offest))*8;
            ul_rx_rate = ((ul_rx_normal_mdpu_succ_num + ul_rx_ppdu_fail_num)*g_ul_al_mpdu_len/(ul_time_offest))*8;
        }
        else
        {
            hal_get_ampdu_bytes(pst_dmac_vap->pst_hal_device, &ul_tx_octects_in_ampdu, &ul_rx_octects_in_ampdu);

            ul_rx_rate = (ul_rx_octects_in_ampdu/(ul_time_offest))*8;
            ul_tx_rate = (ul_tx_octects_in_ampdu/(ul_time_offest))*8;

            OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_all_rx_dscr::tx octects=%u, rx octects=%u, cycles=%u.}",
                           ul_tx_octects_in_ampdu, ul_rx_octects_in_ampdu, ul_cycles);

        }

        /*错误检查*/
        hal_get_rx_err_count(pst_dmac_vap->pst_hal_device,
                        &ul_rx_ampdu_fcs_num,
                        &ul_rx_delimiter_fail_num,
                        &ul_rx_mpdu_fcs_num,
                        &ul_rx_phy_err_mac_passed_num,
                        &ul_rx_phy_longer_err_num,
                        &ul_rx_phy_shorter_err_num);

        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{tx succ num: %u, tx fail num: %u}", ul_tx_ppdu_succ_num, ul_tx_ppdu_fail_num);
        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{rx normal succ num: %u, rx ampdu succ num: %u, rx fail num: %u}", ul_rx_normal_mdpu_succ_num, ul_rx_ampdu_succ_num, ul_rx_ppdu_fail_num);
        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{tx rate(Mbps): %u, rx rate(Mbps): %u, ul_cycles: %u,}", ul_tx_rate, ul_rx_rate, ul_cycles);
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{rx ampdu fcs num: %u, rx delimiter fail num: %u,}", ul_rx_ampdu_fcs_num, ul_rx_delimiter_fail_num);
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{rx mpdu fcs num: %u, rx phy err mac passed num: %u,}", ul_rx_mpdu_fcs_num, ul_rx_phy_err_mac_passed_num);
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{rx phy longer err num: %u, rx phy shorter err num: %u,}", ul_rx_phy_longer_err_num, ul_rx_phy_shorter_err_num);

#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        oal_get_cpu_stat(&st_cpu_stat);
        ull_alltime = st_cpu_stat.ull_user + st_cpu_stat.ull_nice + st_cpu_stat.ull_system + st_cpu_stat.ull_idle + st_cpu_stat.ull_iowait +
                      st_cpu_stat.ull_irq + st_cpu_stat.ull_softirq + st_cpu_stat.ull_steal + st_cpu_stat.ull_guest;
	    OAL_IO_PRINT("user=%llu, nice=%llu, system=%llu, idle=%llu, iowait=%llu, irq=%llu, softirq=%llu, steal=%llu, guest=%llu, alltime=%llu\r\n",
	                 st_cpu_stat.ull_user, st_cpu_stat.ull_nice, st_cpu_stat.ull_system, st_cpu_stat.ull_idle, st_cpu_stat.ull_iowait,
	                 st_cpu_stat.ull_irq,  st_cpu_stat.ull_softirq, st_cpu_stat.ull_steal, st_cpu_stat.ull_guest, ull_alltime);
#endif

        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_all_rx_dscr::TX succ num=%d,fail num=%d;RX succ num=%d, fail num=%d}",
                       ul_tx_ppdu_succ_num, ul_tx_ppdu_fail_num, ul_rx_normal_mdpu_succ_num, ul_rx_ppdu_fail_num);
        OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_dump_all_rx_dscr::tx rate(Mbps)=%d, rx rate(Mbps)=%d, ul_cycles=%d}",
                       ul_tx_rate, ul_rx_rate, ul_cycles);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /* 将需要同步的数据抛事件同步到hmac */
        pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_thruput_info_sync_stru));
        if (OAL_PTR_NULL == pst_event_mem)
        {
            OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_query_event_response::pst_event_memory null.}");

            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_event_up              = (frw_event_stru *)pst_event_mem->puc_data;
        pst_thruput_info_sync = (dmac_thruput_info_sync_stru *)pst_event_up->auc_event_data;
        pst_thruput_info_sync->ul_cycles        = ul_cycles;
        pst_thruput_info_sync->ul_sw_tx_succ_num = ul_tx_ppdu_succ_num;
        pst_thruput_info_sync->ul_sw_tx_fail_num = ul_tx_ppdu_fail_num;
        pst_thruput_info_sync->ul_sw_rx_ampdu_succ_num = ul_rx_ampdu_succ_num;
        pst_thruput_info_sync->ul_sw_rx_ppdu_fail_num = ul_rx_ppdu_fail_num;
        pst_thruput_info_sync->ul_sw_rx_mpdu_succ_num  = ul_rx_normal_mdpu_succ_num;
        pst_thruput_info_sync->ul_hw_rx_ampdu_fcs_fail_num = ul_rx_ampdu_fcs_num;
        pst_thruput_info_sync->ul_hw_rx_mpdu_fcs_fail_num = ul_rx_mpdu_fcs_num;
        dmac_send_sys_event((mac_vap_stru *)&(pst_dmac_vap->st_vap_base_info), WLAN_CFGID_THRUPUT_INFO, OAL_SIZEOF(dmac_thruput_info_sync_stru), (oal_uint8 *)pst_thruput_info_sync);
        FRW_EVENT_FREE(pst_event_mem);
#endif
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_freq_skew
 功能描述  : 设置频率纠偏参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月27日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_freq_skew(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifdef _PRE_WLAN_PHY_PLL_DIV
    mac_cfg_freq_skew_stru *pst_freq_skew;
    mac_device_stru      *pst_device;
    hal_to_dmac_device_stru         *pst_hal_device_base;

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 参数判断 */
    pst_freq_skew = (mac_cfg_freq_skew_stru*)puc_param;
    if (pst_freq_skew->us_idx >= WITP_RF_SUPP_NUMS)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_freq_skew::us_idx=%d.", pst_freq_skew->us_idx);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    pst_hal_device_base = pst_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_freq_skew::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_rf_set_freq_skew(pst_device->pst_device_stru, pst_freq_skew->us_idx, pst_freq_skew->us_chn, pst_freq_skew->as_corr_data);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_adjust_ppm
 功能描述  : 设置PPM校准
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月9日
    作    者   : pengdunmeng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_adjust_ppm(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_cfg_adjust_ppm_stru         *pst_adjust_ppm;
    mac_device_stru                 *pst_device;

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 参数判断 */
    pst_adjust_ppm = (mac_cfg_adjust_ppm_stru*)puc_param;

    hal_rf_adjust_ppm(pst_device->pst_device_stru, pst_adjust_ppm->c_ppm_val, pst_mac_vap->st_channel.en_bandwidth, pst_adjust_ppm->uc_clock_freq);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_reg_info
 功能描述  : 读取mac寄存器

 输入参数  : puc_param:"16|32 regtype(soc/mac/phy) startaddr endaddr"
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月31日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_reg_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_bool_enum_uint8   en_reg_info32 = OAL_TRUE;

    struct dmac_reg_info_stru
    {
        oal_int8     *pc_reg_type;
        oal_uint32    ul_start_addr;
        oal_uint32    ul_end_addr;

    }st_dmac_reg_info = {0};

    /* 选择读取单位(32/16) */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    /*lint -e960*/
    /* 兼容原有"regtype(soc/mac/phy/all) startaddr endaddr"命令格式，默认32位读取寄存器 */
    if (0 == oal_strcmp(pc_token, "all"))
    {
#ifdef _PRE_WLAN_DFT_STAT
        dmac_dft_report_all_ota_state(pst_mac_vap);
#endif
        return OAL_SUCC;
    }

    if ((0 != oal_strcmp(pc_token, "soc")) &&
    (0 != oal_strcmp(pc_token, "mac")) &&
    (0 != oal_strcmp(pc_token, "phy")))
    {
        if (0 == oal_strcmp(pc_token, "16"))
        {
            en_reg_info32 = OAL_FALSE;
        }

        /* 获取要读取的寄存器类型 */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (NULL == pc_token)
        {
            return OAL_FAIL;
        }
        /* 参数检查 */
        if ((0 != oal_strcmp(pc_token, "soc")) &&
        (0 != oal_strcmp(pc_token, "mac")) &&
        (0 != oal_strcmp(pc_token, "phy")))
        {
            return OAL_FAIL;
        }

    }

    /*lint +e960*/

    st_dmac_reg_info.pc_reg_type = pc_token;

    /* 获取起始地址 */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_dmac_reg_info.ul_start_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /* 获取终止地址 */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_dmac_reg_info.ul_end_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    if (OAL_TRUE == en_reg_info32)
    {
        /*lint -e960*/
        dmac_config_reg_display_test(pst_mac_vap, st_dmac_reg_info.ul_start_addr, st_dmac_reg_info.ul_end_addr);
        /*lint +e960*/
        return OAL_SUCC;
    }
    /*lint -e960*/
    dmac_config_reg_display_test16(pst_mac_vap, st_dmac_reg_info.ul_start_addr, st_dmac_reg_info.ul_end_addr);
    /*lint +e960*/
    return OAL_SUCC;
}

/*****************************************************************************

 函 数 名  : dmac_config_dbb_scaling_amend
 功能描述  : 通过修改dbb scaling 寄存器值修改TX Power

 输入参数  : sh hipriv.sh "wlan0 dbb_scaling_amend band 0 bw 20 mcs 0 287"
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月11日
    作    者   : liuweiqiang
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_dbb_scaling_amend(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))

    oal_uint8                   uc_offset_addr_a = 0;
    oal_uint8                   uc_offset_addr_b = 0;
    //oal_uint32                  ul_scaling_addr = HI1102_PHY_SCALING_VALUE_11B_REG;
    oal_uint32                  ul_scaling_addr = 0;
    oal_uint32                  ul_dbb_scaling_value = 0;
    oal_uint16                  us_delta_gain = (1 << MAC_DBB_SCALING_FIX_POINT_BITS);
    mac_cfg_dbb_scaling_stru    *pst_dbb_scaling;

    pst_dbb_scaling = (mac_cfg_dbb_scaling_stru *)puc_param;

    if (OAL_PTR_NULL == pst_dbb_scaling)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_dbb_scaling_amend::  param NULL");
        return OAL_ERR_CODE_PTR_NULL;
    }


    uc_offset_addr_a = pst_dbb_scaling->uc_offset_addr_a;
    uc_offset_addr_b = pst_dbb_scaling->uc_offset_addr_b;
    us_delta_gain = pst_dbb_scaling->us_delta_gain;

    /*更新dbb scaling值*/
    //ul_scaling_addr += uc_offset_addr_a*4;
    ul_scaling_addr = hi1102_rf_cali_get_scaling_addr(uc_offset_addr_a);

    hi1102_rf_cali_read_phy_reg_bits(ul_scaling_addr,
                                         (oal_uint8)(uc_offset_addr_b*MAC_DBB_SCALING_CFG_BITS),
                                         MAC_DBB_SCALING_CFG_BITS,
                                         &ul_dbb_scaling_value);
    OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_dbb_scaling_amend::  old ul_dbb_scaling_value = %d. \r\n",
                                                    ul_dbb_scaling_value);
    ul_dbb_scaling_value = ((ul_dbb_scaling_value * us_delta_gain) >> MAC_DBB_SCALING_FIX_POINT_BITS);
    ul_dbb_scaling_value = ul_dbb_scaling_value > 0xff ? 0xff : ul_dbb_scaling_value; //超过0xff，取值0xff
    hi1102_rf_cali_write_phy_reg_bits(ul_scaling_addr,
                                         (oal_uint8)(uc_offset_addr_b*MAC_DBB_SCALING_CFG_BITS),
                                         MAC_DBB_SCALING_CFG_BITS,
                                         ul_dbb_scaling_value);
    OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_dbb_scaling_amend::  new ul_dbb_scaling_value = %d. \r\n",
                                                    ul_dbb_scaling_value);
#endif
    return OAL_SUCC;
}

#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))

/*****************************************************************************
 函 数 名  : dmac_config_sdio_flowctrl
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : mayuan
    修改内容   : 新生成函数
  2.日    期   : 2015年10月26日
    作    者   : h00349274
    修改内容   : 参数有效性判断

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_sdio_flowctrl(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_uint16            us_UsedMemForStop;
    oal_uint16            us_UsedMemForstart;

    /* 获取要读取的寄存器类型 */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    us_UsedMemForStop = (oal_uint16)oal_strtol(pc_token, &pc_end, 10);

    /* 获取寄存器地址 */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    us_UsedMemForstart = (oal_uint16)oal_strtol(pc_token, &pc_end, 10);
    /* cfg_hisi.ini参数有效性判断 */
    g_usUsedMemForStop  = (1 <= us_UsedMemForStop && OAL_SDIO_FLOWCTRL_MAX >= us_UsedMemForStop) ? us_UsedMemForStop : g_usUsedMemForStop;
    g_usUsedMemForstart  = (1 <= us_UsedMemForstart && OAL_SDIO_FLOWCTRL_MAX >= us_UsedMemForstart) ? us_UsedMemForstart : g_usUsedMemForStop;

    OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_sdio_flowctrl::UsedMemForStop=%d, UsedMemForstart=%d.", us_UsedMemForStop, us_UsedMemForstart);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_reg_write
 功能描述  : 写寄存器接口
 输入参数  : puc_param:"32/16(51没有16位写寄存器功能) regtype(soc/mac/phy) addr val"
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_reg_write(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_bool_enum_uint8   en_reg_info32 = OAL_TRUE;
    struct dmac_reg_write_stru
    {
        oal_int8     *pc_reg_type;
        oal_uint32    ul_addr;
        oal_uint32    ul_val;    /* 写32位寄存器 */
    }st_dmac_reg_write = {0};

    /* 选择写操作单位(32/16) */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    /*lint -e960*/
    /* 兼容原有" regtype(soc/mac/phy) addr val"命令格式，默认32位读取寄存器 */
    if ((0 != oal_strcmp(pc_token, "soc")) && (0 != oal_strcmp(pc_token, "mac")) && (0 != oal_strcmp(pc_token, "phy")))
    {
        if (0 == oal_strcmp(pc_token, "16"))
        {
            en_reg_info32 = OAL_FALSE;
        }

        /* 获取要读取的寄存器类型 */
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (NULL == pc_token)
        {
            return OAL_FAIL;
        }
        /* 参数检查 */
        if ((0 != oal_strcmp(pc_token, "soc")) && (0 != oal_strcmp(pc_token, "mac")) && (0 != oal_strcmp(pc_token, "phy")))
        {
            return OAL_FAIL;
        }

    }
    /*lint +e960*/
    st_dmac_reg_write.pc_reg_type = pc_token;

    /* 获取寄存器地址 */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_dmac_reg_write.ul_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /* 获取需要写入的值 */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    if (OAL_TRUE == en_reg_info32)
    {
        st_dmac_reg_write.ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);
        /*lint -e960*/
        dmac_config_reg_write_test(pst_mac_vap, st_dmac_reg_write.ul_addr, st_dmac_reg_write.ul_val);
        /*lint +e960*/
        return OAL_SUCC;
    }

    st_dmac_reg_write.ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /*lint -e960*/
    dmac_config_reg_write_test16(pst_mac_vap, st_dmac_reg_write.ul_addr, (oal_uint16)(st_dmac_reg_write.ul_val));
    /*lint +e960*/

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_vap_info
 功能描述  : 显示vap信息
 输入参数  : frw_event_mem_stru *pst_event_mem
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月3日,星期五
    作    者   : y00201072
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_vap_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;

    pst_dmac_vap    = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_vap_info::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    //print protection info
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "en_protection_mode=%d. uc_obss_non_erp_aging_cnt=%d. uc_obss_non_ht_aging_cnt=%d. bit_auto_protection=%d",
                                                                                                                pst_mac_vap->st_protection.en_protection_mode,
                                                                                                                pst_mac_vap->st_protection.uc_obss_non_erp_aging_cnt,
                                                                                                                pst_mac_vap->st_protection.uc_obss_non_ht_aging_cnt,
                                                                                                                pst_mac_vap->st_protection.bit_auto_protection);

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "bit_obss_non_erp_present=%d. bit_obss_non_ht_present=%d. bit_rts_cts_protect_mode=%d. bit_lsig_txop_protect_mode=%d.",
                                                                                                                pst_mac_vap->st_protection.bit_obss_non_erp_present,
                                                                                                                pst_mac_vap->st_protection.bit_obss_non_ht_present,
                                                                                                                pst_mac_vap->st_protection.bit_rts_cts_protect_mode,
                                                                                                                pst_mac_vap->st_protection.bit_lsig_txop_protect_mode);

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_sta_no_short_slot_num=%d. uc_sta_no_short_preamble_num=%d. uc_sta_non_erp_num=%d. uc_sta_non_ht_num=%d.",
                                                                                                                pst_mac_vap->st_protection.uc_sta_no_short_slot_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_no_short_preamble_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_non_erp_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_non_ht_num);

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "uc_sta_non_gf_num=%d. uc_sta_20M_only_num=%d. uc_sta_no_40dsss_cck_num=%d. uc_sta_no_lsig_txop_num=%d. ",
                                                                                                                pst_mac_vap->st_protection.uc_sta_non_gf_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_20M_only_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_no_40dsss_cck_num,
                                                                                                                pst_mac_vap->st_protection.uc_sta_no_lsig_txop_num);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_machw_wmm
 功能描述  : 设置硬件wmm参数
 输入参数  : pst_hal_vap: hal vap
             pst_mac_vap: mac vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月24日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_config_set_machw_wmm(hal_to_dmac_vap_stru *pst_hal_vap, mac_vap_stru *pst_mac_vap)
{
    wlan_wme_ac_type_enum_uint8     en_ac_type;
    /* 设置AIFSN */
    hal_vap_set_machw_aifsn_all_ac(pst_hal_vap,
                                   (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableAIFSN);

    /* cwmin cwmax */
    for (en_ac_type = 0; en_ac_type < WLAN_WME_AC_BUTT; en_ac_type++)
    {
        hal_vap_set_edca_machw_cw(pst_hal_vap,
                                 (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmax,
                                 (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmin,
                                  en_ac_type);
    }

#if 0
    hal_vap_set_machw_cw_bk(pst_hal_vap,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_be(pst_hal_vap,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_vi(pst_hal_vap,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableCWmin);
    hal_vap_set_machw_cw_vo(pst_hal_vap,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
                            (oal_uint8)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin);
#endif
    /* txop */
    hal_vap_set_machw_txop_limit_bkbe(pst_hal_vap,
                                      (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
    hal_vap_set_machw_txop_limit_vivo(pst_hal_vap,
                                      (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableTXOPLimit);


}

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 函 数 名  : dmac_add_p2p_cl_vap
 功能描述  : 添加p2p cl vap的事件调度函数
 输入参数  : pst_mac_vap : 业务vap，而不是配置VAP
             puc_param   : 参数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月25日
    作    者   : huxiaotong
    修改内容   : 新生成函数

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : zhongwen
    修改内容   : 添加函数内容

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_add_p2p_cl_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                *pst_device;
    mac_cfg_add_vap_param_stru     *pst_param;
    dmac_vap_stru                  *pst_dmac_vap;
    hal_to_dmac_vap_stru           *pst_hal_vap = OAL_PTR_NULL;
    oal_uint8                       uc_vap_idx;
    mac_vap_stru                   *pst_mac_cfg_vap;

    pst_param = (mac_cfg_add_vap_param_stru *)puc_param;

    /* 获取device */
    pst_mac_cfg_vap = (mac_vap_stru*)mac_res_get_mac_vap(pst_param->uc_cfg_vap_indx);
    if (OAL_PTR_NULL == pst_mac_cfg_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::pst_cfg_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_cfg_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device || OAL_PTR_NULL == pst_device->pst_device_stru)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::pst_device or pst_device->pst_device_stru null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 由于P2P CL 和P2P DEV 共用VAP，故P2P CL 不需要申请内存，也不需要初始化dmac vap 结构 */
    uc_vap_idx     = pst_device->st_p2p_info.uc_p2p0_vap_idx;/* uc_p2p0_vap_idx在创建p2p0 时初始化 */
    pst_dmac_vap   = (dmac_vap_stru *)mac_res_get_dmac_vap(uc_vap_idx);

    /* 检查hmac和dmac创建vap idx是否一致 */
    if (uc_vap_idx != pst_param->uc_vap_id)
    {
        OAM_ERROR_LOG2(pst_mac_cfg_vap->uc_vap_id, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::HMAC and DMAC vap indx not same!.saved_vap_id[%d], new_vap_id[%d]}",
                        uc_vap_idx, pst_param->uc_vap_id);
        return OAL_ERR_CODE_ADD_VAP_INDX_UNSYNC;
    }



#if defined (_PRE_WLAN_FEATURE_PROXYSTA)
    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* 如果是Proxy STA，则在hal 配置为Proxy STA模式，这个模式只在hal层使用 */
            hal_add_vap(pst_device->pst_device_stru, WLAN_VAP_MODE_PROXYSTA, uc_vap_idx, &pst_hal_vap);
        }
        else
        {
            hal_add_vap(pst_device->pst_device_stru, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
        }
    }
    else
    {
        hal_add_vap(pst_device->pst_device_stru, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
    }
#elif defined (_PRE_WLAN_FEATURE_P2P)
    /* 同一个vap ，能够挂接多个hal_vap */
    /* 由于MAC 硬件对于P2P 相关寄存器的限制。
    *  GO 只能创建在hal_vap_id = 1,
    *  CL 只能创建在hal_vap_id = 5,
    *  需要将P2P 模式传到hal_add_vap 函数中  */
    /*
    *  |7      4|3      0|
    *  |p2p_mode|vap_mode|
    */

    hal_add_vap(pst_device->pst_device_stru, ((pst_param->en_vap_mode) | ((oal_uint8)(pst_param->en_p2p_mode << 4))),
                uc_vap_idx, &pst_hal_vap);
#else
    /* 同一个vap ，能够挂接多个hal_vap */
    hal_add_vap(pst_device->pst_device_stru, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
#endif

    if (OAL_PTR_NULL == pst_hal_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::pst_hal_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap->pst_hal_vap = pst_hal_vap;

    /* 保存到dmac vap结构体中，方便获取 */
    pst_dmac_vap->pst_hal_device = pst_device->pst_device_stru;

    //pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id = pst_hal_vap->uc_vap_id;


    /* 配置RTS发送参数 */
    //hal_vap_set_machw_prot_params(pst_dmac_vap->pst_hal_vap, &(pst_dmac_vap->st_tx_alg.st_rate), &(pst_dmac_vap->st_tx_alg.ast_per_rate[0]));


    /* P2P 设置MAC 地址 */
    hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);


    /* 配置硬件WMM参数 */
    dmac_config_set_machw_wmm(pst_dmac_vap->pst_hal_vap, pst_mac_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* device下sta个数加1 */
    if (WLAN_VAP_MODE_BSS_STA == pst_param->en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (1 == pst_device->st_cap_flag.bit_proxysta)
        {
            if ((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta) &&
                (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
            {
                pst_device->uc_proxysta_num++;
            }
        }
#endif
        /* 初始化uc_assoc_vap_id为最大值代表ap未关联 */
        mac_vap_set_assoc_id(pst_mac_vap, 0xff);
    }
    mac_vap_set_p2p_mode(&pst_dmac_vap->st_vap_base_info, pst_param->en_p2p_mode);
    mac_inc_p2p_num(&pst_dmac_vap->st_vap_base_info);


#endif
    /* 初始化业务VAP，区分AP、STA和WDS模式 */
    dmac_alg_create_vap_notify(pst_dmac_vap);

#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* 初始化P2P CLIENT 节能状态机 */
    dmac_pm_sta_attach(pst_dmac_vap);
#endif
    /* 检查hmac和dmac创建muti user idx是否一致 */
    if (pst_param->us_muti_user_id != pst_mac_vap->us_multi_user_idx)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::HMAC and DMAC muti user indx not same!.}");
        return OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC;
    }
#if 0
    /* 将dmac 侧mac_vap 中uc_p2p0_hal_vap_id/uc_p2p_gocl_hal_vap_id 同步到hmac 的mac_vap 结构中 */
    /* 将需要同步的数据抛事件同步到hmac */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_add_vap_sync_data_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_P2P, "{dmac_add_p2p_cl_vap::pst_event_memory null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_up              = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_add_vap_sync_data = (mac_add_vap_sync_data_stru *)pst_event_up->auc_event_data;
    //pst_mac_add_vap_sync_data->uc_p2p0_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id;
    //pst_mac_add_vap_sync_data->uc_p2p_gocl_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id;
    //dmac_send_sys_event((mac_vap_stru *)&(pst_dmac_vap->st_vap_base_info), WLAN_CFGID_ADD_VAP, OAL_SIZEOF(mac_add_vap_sync_data_stru), (oal_uint8 *)pst_mac_add_vap_sync_data);
    FRW_EVENT_FREE(pst_event_mem);
#endif
    /*初始化p2p节能参数*/
    OAL_MEMZERO(&(pst_dmac_vap->st_p2p_ops_param), OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
    OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_add_p2p_cl_vap::add vap [%d] sucess.}", uc_vap_idx);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_del_p2p_cl_vap
 功能描述  : 删除p2p cl vap
 输入参数  : pst_mac_config_vap : dmac业务vap
             uc_len             : 参数长度
             puc_param          : 参数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_del_p2p_cl_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                  *pst_dmac_vap;
    hal_to_dmac_device_stru        *pst_hal_device;
    pst_dmac_vap   = (dmac_vap_stru *)pst_mac_vap;
    pst_hal_device = pst_dmac_vap->pst_hal_device;

    /* 停止P2P 节能寄存器 */
    hal_vap_set_noa(pst_dmac_vap->pst_hal_vap, 0, 0, 0, 0);
    hal_vap_set_ops(pst_dmac_vap->pst_hal_vap, 0, 0);
    OAL_MEMZERO(&(pst_dmac_vap->st_p2p_ops_param), OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
    OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));

#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* 节能状态机删除*/
    dmac_pm_sta_detach(pst_dmac_vap);
#endif
    /* 如果是p2p0,删除p2p0_hal_vap */

    hal_del_vap(pst_hal_device, pst_mac_vap->en_vap_mode, pst_dmac_vap->pst_hal_vap->uc_vap_id);

    /* DTS2015042704768 P2P CL删除时需要将num减1 */
#ifdef _PRE_WLAN_FEATURE_P2P
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_dec_p2p_num(pst_mac_vap);
#endif
#endif

    /* 删除p2p cl 后，需要将dmac vap 结构中hal_vap 指针指向p2p0_hal_vap,以便p2p0 发送数据 */
    pst_dmac_vap->pst_hal_vap    = pst_dmac_vap->pst_p2p0_hal_vap;
    mac_vap_set_p2p_mode(&pst_dmac_vap->st_vap_base_info, WLAN_P2P_DEV_MODE);
	//pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id;
    oal_memcopy(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID,
                WLAN_MAC_ADDR_LEN);

    /* 删除与算法相关的接口 */
    dmac_alg_delete_vap_notify(pst_dmac_vap);


    if (WLAN_VAP_MODE_CONFIG == pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_del_p2p_cl_vap::config vap should not be here.}");
        return OAL_FAIL;
    }

    return OAL_SUCC;
}

#endif
/*****************************************************************************
 函 数 名  : dmac_config_add_vap
 功能描述  : 添加vap的事件调度函数
 输入参数  : pst_mac_vap : 业务vap，而不是配置VAP
             puc_param   : 参数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月25日
    作    者   : huxiaotong
    修改内容   : 新生成函数

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : zhangheng
    修改内容   : 添加函数内容

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_add_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                *pst_device;
    mac_cfg_add_vap_param_stru     *pst_param;
    dmac_vap_stru                  *pst_dmac_vap;
    hal_to_dmac_device_stru        *pst_hal_device;
    hal_to_dmac_vap_stru           *pst_hal_vap = OAL_PTR_NULL;
    oal_uint32                      ul_ret;
    oal_uint8                       uc_vap_idx;
    mac_vap_stru                   *pst_mac_cfg_vap;

    pst_param = (mac_cfg_add_vap_param_stru *)puc_param;

#ifdef _PRE_WLAN_FEATURE_P2P
    if (WLAN_P2P_CL_MODE == pst_param->en_p2p_mode)
    {
        return dmac_add_p2p_cl_vap(pst_mac_vap, uc_len, puc_param);
    }
#endif
    /* 获取device */
    pst_mac_cfg_vap = (mac_vap_stru*)mac_res_get_mac_vap(pst_param->uc_cfg_vap_indx);
    if (OAL_PTR_NULL == pst_mac_cfg_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_add_vap::add vap failed. pst_cfg_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_cfg_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::add vap failed. pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    uc_vap_idx = pst_param->uc_vap_id;
    /* 分配dmac vap内存空间 */
    ul_ret = mac_res_alloc_dmac_vap(uc_vap_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::mac_res_alloc_dmac_vap error.}");
        return ul_ret;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(uc_vap_idx);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::add vap failed. pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if(MAC_VAP_VAILD == pst_dmac_vap->st_vap_base_info.uc_init_flag)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                        "{dmac_config_add_vap::add vap maybe double init!}");
    }
#endif
#ifdef _PRE_WLAN_FEATURE_UAPSD
    if (WLAN_VAP_MODE_BSS_AP == pst_param->en_vap_mode)
    {
        g_uc_uapsd_cap = pst_param->bit_uapsd_enable;
    }
#endif
    ul_ret = dmac_vap_init(pst_dmac_vap,
                           pst_device->uc_chip_id,
                           pst_device->uc_device_id,
                           uc_vap_idx,
                           pst_param);
    if (OAL_SUCC != ul_ret)
    {
        if (OAL_PTR_NULL != pst_dmac_vap->st_vap_base_info.pst_mib_info)
        {
            OAL_MEM_FREE(pst_dmac_vap->st_vap_base_info.pst_mib_info, OAL_TRUE);
            pst_dmac_vap->st_vap_base_info.pst_mib_info = OAL_PTR_NULL;
        }
        /* 释放资源池 */
        mac_res_free_mac_vap(uc_vap_idx);
        return ul_ret;
    }

    /* 调用hal_add_vap */
    pst_hal_device = pst_device->pst_device_stru;

#if defined (_PRE_WLAN_FEATURE_PROXYSTA)
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{dmac_config_add_vap::mac_res_get_dev fail.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* 如果是Proxy STA，则在hal 配置为Proxy STA模式，这个模式只在hal层使用 */
            hal_add_vap(pst_hal_device, WLAN_VAP_MODE_PROXYSTA, uc_vap_idx, &pst_hal_vap);
        }
        else
        {
            hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
        }
    }
    else
    {
        hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
    }
#elif defined (_PRE_WLAN_FEATURE_P2P)
    /* 同一个vap ，能够挂接多个hal_vap */
    /* 由于MAC 硬件对于P2P 相关寄存器的限制。
    *  GO 只能创建在hal_vap_id = 1,
    *  CL 只能创建在hal_vap_id = 5,
    *  需要将P2P 模式传到hal_add_vap 函数中  */
    /*
    *  |7      4|3      0|
    *  |p2p_mode|vap_mode|
    */

    /* 同一个vap ，能够挂接多个hal_vap */
    hal_add_vap(pst_hal_device, (pst_param->en_vap_mode) | (oal_uint8)(pst_param->en_p2p_mode << 4) ,
                uc_vap_idx, &pst_hal_vap);
#else
    /* 同一个vap ，能够挂接多个hal_vap */
    hal_add_vap(pst_hal_device, pst_param->en_vap_mode, uc_vap_idx, &pst_hal_vap);
#endif

    if (OAL_PTR_NULL == pst_hal_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_event_add_vap::add hal_vap failed. pst_hal_vap null.}");

        if (OAL_PTR_NULL != pst_dmac_vap->st_vap_base_info.pst_mib_info)
        {
            OAL_MEM_FREE(pst_dmac_vap->st_vap_base_info.pst_mib_info, OAL_TRUE);
            pst_dmac_vap->st_vap_base_info.pst_mib_info = OAL_PTR_NULL;
        }

        /* 释放资源池 */
        mac_res_free_mac_vap(uc_vap_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    /* 分别初始化P2P CL 和P2P DEV */
    if (WLAN_P2P_DEV_MODE == pst_param->en_p2p_mode)
    {
        pst_dmac_vap->pst_p2p0_hal_vap = pst_hal_vap;
        pst_device->st_p2p_info.uc_p2p0_vap_idx = pst_mac_vap->uc_vap_id;
    }
#endif /* _PRE_WLAN_FEATURE_P2P */
    pst_dmac_vap->pst_hal_vap = pst_hal_vap;

    /* 保存到dmac vap结构体中，方便获取 */
    pst_dmac_vap->pst_hal_device = pst_hal_device;

    /* 配置RTS发送参数 */
    //hal_vap_set_machw_prot_params(pst_dmac_vap->pst_hal_vap, &(pst_dmac_vap->st_tx_alg.st_rate), &(pst_dmac_vap->st_tx_alg.ast_per_rate[0]));

#if defined (_PRE_WLAN_FEATURE_PROXYSTA)
    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta) && (OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta))
        {
            /* 把hal vap id(16~31) 的值传给作为 user id */
            pst_mac_vap->st_vap_proxysta.uc_lut_idx = pst_hal_vap->uc_vap_id;
        }
        else
        {
            hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, mac_mib_get_StationID(pst_mac_vap));
        }
    }
    else
    {
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    }
#elif defined (_PRE_WLAN_FEATURE_P2P)
    /* P2P 设置MAC 地址 */
    if ((WLAN_P2P_DEV_MODE == pst_param->en_p2p_mode) && (WLAN_VAP_MODE_BSS_STA == pst_param->en_vap_mode))
    {
        /* 设置p2p0 MAC 地址 */
        hal_vap_set_macaddr(pst_dmac_vap->pst_p2p0_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);
    }
    else
    {
        /* 设置其他vap 的mac 地址 */
        hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    }
#else
    /* 配置MAC地址 */
    hal_vap_set_macaddr(pst_dmac_vap->pst_hal_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
#endif

    /* 配置硬件WMM参数 */
    dmac_config_set_machw_wmm(pst_dmac_vap->pst_hal_vap, pst_mac_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_set_vap_id(pst_device, &(pst_dmac_vap->st_vap_base_info),uc_vap_idx, pst_param->en_vap_mode, pst_param->en_p2p_mode, OAL_TRUE);

    /* 初始化STA AID 为 0 */
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        mac_vap_set_aid(pst_mac_vap, 0);
    }
#endif

    /* 初始化linkloss检测工具 */
    dmac_vap_linkloss_init(pst_dmac_vap);

    /* 初始化业务VAP，区分AP、STA和WDS模式 */
    switch(pst_param->en_vap_mode)
    {
        case WLAN_VAP_MODE_BSS_AP:
            /* 执行特性初始化vap的函数 */
            /* 执行算法相关VAP初始化接口 */
            dmac_alg_create_vap_notify(pst_dmac_vap);
        #ifdef _PRE_WLAN_FEATURE_UAPSD
            pst_dmac_vap->uc_uapsd_max_depth = DMAC_UAPSD_QDEPTH_DEFAULT;
            #if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
                mac_vap_set_uapsd_en(&pst_dmac_vap->st_vap_base_info, OAL_TRUE);
            #endif
        #endif

        #ifdef  _PRE_WLAN_FEATURE_PM
            if(OAL_TRUE == pst_device->en_pm_enable)
            {
                dmac_pm_ap_attach(pst_dmac_vap);
            }
        #endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

            /* add vap时,ap注册到平台,防止平台睡眠 */
            hal_pm_wlan_servid_register(pst_dmac_vap->pst_hal_vap, &ul_ret);

            if (OAL_SUCC != ul_ret)
            {
                OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                                   "{dmac_pm_sta_attach:hal_pm_wlan_servid_register hal vap:[%d]fail",pst_dmac_vap->pst_hal_vap->uc_vap_id);

            }

            /* DTS2015120403256,在业务注册时立刻恢复前端,防止aput在发送第一个beacon帧之前被狗咬死 */
            dmac_pm_enable_front_end(pst_device,OAL_TRUE);

            /* ap不降频 */
            pst_hal_device->uc_full_phy_freq_user_cnt++;

            OAM_WARNING_LOG1(0,OAM_SF_PWR,"dmac_config_add_vap ap::full phy freq user[%d]",pst_hal_device->uc_full_phy_freq_user_cnt);

            hal_process_phy_freq(pst_device->pst_device_stru);

#endif
            break;

        case WLAN_VAP_MODE_BSS_STA:
            /* 执行特性初始化vap的函数 */
            /* 执行算法相关VAP初始化接口 */
            if(IS_LEGACY_VAP(&pst_dmac_vap->st_vap_base_info))
            {
                dmac_alg_create_vap_notify(pst_dmac_vap);
#ifdef  _PRE_WLAN_FEATURE_STA_PM    //是否需要仿照上面的ap(liuzhengqi)
                /* P2P DEVICE 和 P2P client 公用vap 结构，针对P2P DEVICE 不注册节能状态机 */
                dmac_pm_sta_attach(pst_dmac_vap);
#endif
            }
            break;

        case WLAN_VAP_MODE_WDS:

            break;

        default:

            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                         "{dmac_vap_init::invalid vap mode[%d].", pst_param->en_vap_mode);
            return OAL_ERR_CODE_INVALID_CONFIG;
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta)
            && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
        {
            /* Proxysta 不创建组播用户*/
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap:: proxysta don't add multicast user.}");
        }
        else
        {
            /* 申请创建dmac组播用户 */
            dmac_user_add_multi_user(pst_mac_vap, pst_param->us_muti_user_id);
            mac_vap_set_multi_user_idx(pst_mac_vap, pst_param->us_muti_user_id);

            /* 检查hmac和dmac创建muti user idx是否一致 */
            if (pst_param->us_muti_user_id != pst_mac_vap->us_multi_user_idx)
            {
                OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::HMAC and DMAC muti user indx not same!.}");
                return OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC;
            }
        }
    }
    else
    {
        /* 申请创建dmac组播用户 */
        dmac_user_add_multi_user(pst_mac_vap, pst_param->us_muti_user_id);
        mac_vap_set_multi_user_idx(pst_mac_vap, pst_param->us_muti_user_id);

        /* 检查hmac和dmac创建muti user idx是否一致 */
        if (pst_param->us_muti_user_id != pst_mac_vap->us_multi_user_idx)
        {
            OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::HMAC and DMAC muti user indx not same!.}");
            return OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC;
        }
    }
#else
    /* 申请创建dmac组播用户 */
    dmac_user_add_multi_user(pst_mac_vap, pst_param->us_muti_user_id);
    mac_vap_set_multi_user_idx(pst_mac_vap, pst_param->us_muti_user_id);

    /* 检查hmac和dmac创建muti user idx是否一致 */
    if (pst_param->us_muti_user_id != pst_mac_vap->us_multi_user_idx)
    {
        OAM_ERROR_LOG0(pst_mac_cfg_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::HMAC and DMAC muti user indx not same!.}");
        return OAL_ERR_CODE_ADD_MULTI_USER_INDX_UNSYNC;
    }
#endif

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)

    pst_dmac_vap->ul_user_pmf_status = 0;
#endif /* #if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP) */
#if 0
#ifdef _PRE_WLAN_FEATURE_P2P
    /* 如果是创建P2P_DEV,需要设置device 侧mac_device 结构体下p2p0_vap_id 成员赋初值 */
    if (WLAN_P2P_DEV_MODE == en_p2p_mode)
    {
		/* 初始化p2p0 时，需要将新创建p2p0_vap 的vap_id 赋值给device中对应成员 */
        pst_device->st_p2p_info.uc_p2p0_vap_idx = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    }

    /* 将dmac 侧mac_vap 中uc_p2p0_hal_vap_id/uc_p2p_gocl_hal_vap_id 同步到hmac 的mac_vap 结构中 */
    /* 将需要同步的数据抛事件同步到hmac */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_add_vap_sync_data_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_query_event_response::pst_event_memory null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_up              = (frw_event_stru *)pst_event_mem->puc_data;
    pst_mac_add_vap_sync_data = (mac_add_vap_sync_data_stru *)pst_event_up->auc_event_data;
    pst_mac_add_vap_sync_data->uc_p2p0_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p0_hal_vap_id;
    pst_mac_add_vap_sync_data->uc_p2p_gocl_hal_vap_id = pst_dmac_vap->st_vap_base_info.uc_p2p_gocl_hal_vap_id;
    dmac_send_sys_event((mac_vap_stru *)&(pst_dmac_vap->st_vap_base_info), WLAN_CFGID_ADD_VAP, OAL_SIZEOF(mac_add_vap_sync_data_stru), (oal_uint8 *)pst_mac_add_vap_sync_data);
    FRW_EVENT_FREE(pst_event_mem);

    /*GO 初始化p2p节能参数*/
    if (WLAN_P2P_GO_MODE == en_p2p_mode)
    {
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_ops_param), OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
    }

#endif
#endif

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_add_vap::add vap succ. mode[%d] state[%d].}",
                             pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_beacon_chain_switch
 功能描述  : dmac 配置关闭/开启beacon帧双路轮流发送策略
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月13日
    作    者   : daihu 00262548
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_beacon_chain_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8         uc_value;
    dmac_vap_stru    *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_beacon_chain_switch::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_value = *((oal_uint8 *)puc_param);

    /* 配置beacon帧关闭/开启双路轮流发送，1为开启,0为关闭 */
    pst_dmac_vap->en_beacon_chain_active = uc_value;

    return OAL_SUCC;
}
#if 0
/*****************************************************************************
 函 数 名  : dmac_config_tdls_prohibited
 功能描述  : TDLS禁用开关
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : daihu 00262548
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_tdls_prohibited(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8         uc_value;

    uc_value = *((oal_uint8 *)puc_param);

    /* 配置tdls prohibited,1为开启禁止,0为关闭禁止 */
    mac_vap_set_tdls_prohibited(pst_mac_vap, uc_value);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_tdls_channel_switch_prohibited
 功能描述  : TDLS信道切换禁用开关
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月26日
    作    者   : daihu 00262548
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_tdls_channel_switch_prohibited(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8         uc_value;

    uc_value = *((oal_uint8 *)puc_param);

    mac_vap_set_tdls_channel_switch_prohibited(pst_mac_vap, uc_value);

    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_tdls_channel_switch_prohibited succ!");
#endif
    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_config_hide_ssid
 功能描述  : 使能隐藏ssid
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月5日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_hide_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8         uc_value;

    uc_value = *((oal_uint8 *)puc_param);
    mac_vap_set_hide_ssid(pst_mac_vap, uc_value);
    OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_config_hide_ssid::mac_vap_set_hide_ssid [%d].}", uc_value);

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "dmac_config_hide_ssid[%d] succ!", uc_value);
#endif
    return OAL_SUCC;
}


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
 函 数 名  : dmac_config_offload_start_vap
 功能描述  : offload情况下vap start
 输入参数  : pst_mac_config_vap : dmac业务vap
 输出参数  : 无
 返 回 值  : OAL_SUCC
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_offload_start_vap(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_param)
{
    mac_cfg_start_vap_param_stru *pst_start_vap_param;

    pst_start_vap_param = (mac_cfg_start_vap_param_stru *)puc_param;

    pst_mac_vap->st_channel.en_band = pst_start_vap_param->uc_band;
    pst_mac_vap->st_channel.en_bandwidth = pst_start_vap_param->uc_bandwidth;
    mac_vap_init_by_protocol(pst_mac_vap, pst_start_vap_param->uc_protocol);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* 设置bssid */
        mac_vap_set_bssid(pst_mac_vap, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        /*将vap状态改变信息上报*/
        mac_vap_state_change(pst_mac_vap, MAC_VAP_STATE_UP);

    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {

#ifdef _PRE_WLAN_FEATURE_P2P
        /* P2P0 和P2P-P2P0 共VAP 结构，P2P CL UP时候，不需要设置vap 状态 */
        if (WLAN_P2P_CL_MODE != pst_start_vap_param->en_p2p_mode)
#endif
        {
        #ifdef _PRE_WLAN_FEATURE_ROAM
            if (MAC_VAP_STATE_ROAMING != pst_mac_vap->en_vap_state)
        #endif //_PRE_WLAN_FEATURE_ROAM
            {
                pst_mac_vap->st_channel.uc_chan_number = 0;//DTS2015112900713初始化信道号防止信道号跟频段出现不匹配的情况
                mac_vap_state_change(pst_mac_vap, MAC_VAP_STATE_STA_FAKE_UP);
            }
        }
    }

    /* 初始化速率集 */
    mac_vap_init_rates(pst_mac_vap);
    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : dmac_config_del_vap
 功能描述  : 删除vap
 输入参数  : pst_mac_config_vap : dmac业务vap
             uc_len             : 参数长度
             puc_param          : 参数
 输出参数  : 无
 返 回 值  : OAL_SUCC
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_del_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                  *pst_dmac_vap = OAL_PTR_NULL;
    hal_to_dmac_device_stru        *pst_hal_device;
    oal_uint8                       uc_vap_id;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_cfg_del_vap_param_stru     *pst_del_vap_param;
    wlan_p2p_mode_enum_uint8        en_p2p_mode = WLAN_LEGACY_VAP_MODE;
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    mac_device_stru *pst_mac_device;
#endif

    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_del_vap::del vap. mode[%d] state[%d] p2p_mode[%d].}",
                      pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state, pst_mac_vap->en_p2p_mode);

    pst_dmac_vap   = (dmac_vap_stru *)pst_mac_vap;
    pst_hal_device = pst_dmac_vap->pst_hal_device;
    uc_vap_id      = pst_dmac_vap->st_vap_base_info.uc_vap_id;

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)
    pst_dmac_vap->ul_user_pmf_status = 0;
#endif /* #if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP) */

#ifdef _PRE_WLAN_FEATURE_P2P
    pst_del_vap_param = (mac_cfg_del_vap_param_stru *)puc_param;
    en_p2p_mode       = pst_del_vap_param->en_p2p_mode;
    if (WLAN_P2P_CL_MODE == en_p2p_mode)
    {
        return dmac_del_p2p_cl_vap(pst_mac_vap, uc_len, puc_param);
    }
    if (WLAN_P2P_GO_MODE == en_p2p_mode)
    {
        /* 停止P2P 节能寄存器 */
        hal_vap_set_noa(pst_dmac_vap->pst_hal_vap, 0, 0, 0, 0);
        hal_vap_set_ops(pst_dmac_vap->pst_hal_vap, 0, 0);
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_ops_param), OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
    }
    /* 如果是p2p0,删除p2p0_hal_vap */
    if (WLAN_P2P_DEV_MODE == en_p2p_mode)
    {
        hal_del_vap(pst_hal_device, pst_mac_vap->en_vap_mode, pst_dmac_vap->pst_p2p0_hal_vap->uc_vap_id);
        pst_dmac_vap->pst_p2p0_hal_vap    = OAL_PTR_NULL;
    }
    else
#endif
    {
        /* STA节能状态机删除*/
#ifdef _PRE_WLAN_FEATURE_STA_PM
        if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {
            dmac_pm_sta_detach(pst_dmac_vap);
        }
#endif
        if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {
            /* 节能状态机删除*/
#ifdef _PRE_WLAN_FEATURE_PM
            dmac_pm_ap_deattach(pst_dmac_vap);
#endif

            hal_pm_wlan_servid_unregister(pst_dmac_vap->pst_hal_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            if (pst_hal_device->uc_full_phy_freq_user_cnt > 0)
            {
                pst_hal_device->uc_full_phy_freq_user_cnt--;
            }
            else
            {
                OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"dmac_config_del_vap::full_phy_freq_user_cnt is 0");
            }

            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_del_vap ap::full phy freq user cnt[%d]",pst_hal_device->uc_full_phy_freq_user_cnt);
#endif
        }


        /* 直接调用hal_del_vap */
        hal_del_vap(pst_hal_device, pst_mac_vap->en_vap_mode, pst_dmac_vap->pst_hal_vap->uc_vap_id);
		/* 删除与算法相关的接口 */
        dmac_alg_delete_vap_notify(pst_dmac_vap);
    }
    pst_dmac_vap->pst_hal_device = OAL_PTR_NULL;
    pst_dmac_vap->pst_hal_vap    = OAL_PTR_NULL;

    if (WLAN_VAP_MODE_CONFIG != pst_mac_vap->en_vap_mode)
    {
        /* 删除DMAC组播用户 */
        dmac_user_del_multi_user(pst_mac_vap, pst_mac_vap->us_multi_user_idx);
    }
    else
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_del_vap::config vap should not be here.}");
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    if (OAL_PTR_NULL != pst_dmac_vap->pst_ip_addr_info)
    {
        OAL_MEM_FREE(pst_dmac_vap->pst_ip_addr_info, OAL_TRUE);
        pst_dmac_vap->pst_ip_addr_info = OAL_PTR_NULL;
    }
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_vap_exit(pst_mac_vap);
#endif

    /* 释放tim_bitmap */
    if (OAL_PTR_NULL != pst_dmac_vap->puc_tim_bitmap)
    {
        OAL_MEM_FREE(pst_dmac_vap->puc_tim_bitmap, OAL_TRUE);
        pst_dmac_vap->puc_tim_bitmap = OAL_PTR_NULL;
    }

    if (OAL_PTR_NULL != pst_dmac_vap)
    {
        mac_res_free_mac_vap(uc_vap_id);
        OAM_WARNING_LOG2(uc_vap_id, OAM_SF_CFG, "{dmac_config_del_vap:: del vap[%d] success, multe user idx[%d].}", uc_vap_id, pst_mac_vap->us_multi_user_idx);
    }
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    /* 共存恢复优先级 */
    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_COEX, "{dmac_config_del_vap::pst_mac_device null.}");
        return OAL_FAIL;
    }

    dmac_btcoex_wlan_priority_set(pst_mac_device, 0, 0);
    hal_set_btcoex_occupied_period(0);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_start_vap
 功能描述  : dmac启动vap
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月11日
    作    者   : zhangheng
    修改内容   : 新生成函数
  2.日    期   : 2013年11月6日
    作    者   : y00184180 yaorui
    修改内容   : 增加写EIFS TIME 寄存器

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_start_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;
    oal_uint32                    ul_ret;
    wlan_protocol_enum_uint8      en_protocol;
    hal_to_dmac_device_stru      *pst_hal_device;
    mac_cfg_start_vap_param_stru *pst_start_vap_param;

    pst_start_vap_param = (mac_cfg_start_vap_param_stru *)puc_param;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_start_vap::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    ul_ret = dmac_config_offload_start_vap(pst_mac_vap, puc_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_start_vap::dmac_config_offload_start_vap failed[%d].}", ul_ret);
        return ul_ret;
    }
#endif
    en_protocol    = pst_mac_vap->en_protocol;
    pst_hal_device = pst_dmac_vap->pst_hal_device;

    /* 配置MAC EIFS_TIME 寄存器 */
    hal_config_eifs_time(pst_hal_device, en_protocol);

#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P0 和P2P-P2P0 共VAP 结构，P2P CL UP时候，不需要设置vap 状态 */
    if (WLAN_P2P_DEV_MODE == pst_start_vap_param->en_p2p_mode)
    {
        /* 使能PA_CONTROL的vap_control位: bit0~3对应AP0~3 bit4对应sta */
        hal_vap_set_opmode(pst_dmac_vap->pst_p2p0_hal_vap, pst_dmac_vap->st_vap_base_info.en_vap_mode);
    }
    else
#endif
    {
        /* 使能PA_CONTROL的vap_control位: bit0~3对应AP0~3 bit4对应sta */
        hal_vap_set_opmode(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->st_vap_base_info.en_vap_mode);
    }

    /* 初始化除单播数据帧以外所有帧的发送参数 */
    dmac_vap_init_tx_frame_params(pst_dmac_vap, pst_start_vap_param->en_mgmt_rate_init_flag);

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    /* 初始化默认不采用针对特定协议的固定速率配置 */
    pst_dmac_vap->un_mode_valid.uc_mode_param_valid = 0;
    OAL_MEMZERO(&pst_dmac_vap->st_tx_alg_vht, OAL_SIZEOF(hal_tx_txop_alg_stru));
    OAL_MEMZERO(&pst_dmac_vap->st_tx_alg_ht, OAL_SIZEOF(hal_tx_txop_alg_stru));
    OAL_MEMZERO(&pst_dmac_vap->st_tx_alg_11ag, OAL_SIZEOF(hal_tx_txop_alg_stru));
    OAL_MEMZERO(&pst_dmac_vap->st_tx_alg_11b, OAL_SIZEOF(hal_tx_txop_alg_stru));
#endif

    /* 初始化单播数据帧的发送参数 */
    dmac_vap_init_tx_ucast_data_frame(pst_dmac_vap);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* 创建beacon帧 */

        /* 入网优化，不同频段下的能力不一样 */
        if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
        {
            mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
            mac_mib_set_SpectrumManagementRequired(pst_mac_vap, OAL_FALSE);
        }
        else
        {
            mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
            mac_mib_set_SpectrumManagementRequired(pst_mac_vap, OAL_TRUE);
        }

        ul_ret = dmac_beacon_alloc(pst_dmac_vap);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_start_vap::dmac_beacon_alloc failed[%d].}", ul_ret);
            return ul_ret;
        }
        dmac_alg_vap_up_notify(pst_mac_vap);
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
    #ifdef _PRE_WLAN_FEATURE_TXOPPS
        /* 作为sta，需要根据txop ps能力初始化mac txop ps使能寄存器 */
        dmac_txopps_init_machw_sta(pst_dmac_vap);
    #endif
    }
    else
    {

    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_vap_up_handle(pst_mac_vap);
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
    {
    mac_device_stru              *pst_mac_device;

    /* 修改p2p ci 问题。P2P start vap，打开前端RF接收。 */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (pst_mac_device == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                         "{dmac_config_start_vap::start vap FAIL.get mac_device is null.device_id[%d]",
                         pst_mac_vap->uc_device_id);
        return OAL_FAIL;
    }

    dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);
    }
#endif

    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                     "{dmac_config_start_vap::start vap success.vap_mode[%d] state[%d], p2p mode[%d]",
                     pst_mac_vap->en_vap_mode,
                     pst_mac_vap->en_vap_state,
                     pst_mac_vap->en_p2p_mode);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_down_vap
 功能描述  : 停用vap
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_down_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru   *pst_mac_device;
    dmac_user_stru     *pst_dmac_user;
    dmac_vap_stru     *pst_dmac_vap;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_down_vap::pst_mac_device[%d] null.}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap  = (dmac_vap_stru *)pst_mac_vap;
    pst_dmac_user = (dmac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_down_vap::pst_multi_dmac_user[%d] null.}", pst_mac_vap->us_multi_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 删除组播用户tid队列中的所有信息 */
    dmac_tid_clear(&pst_dmac_user->st_user_base_info, pst_mac_device);


    /* 清除PA_CONTROL的vap_control位: bit0~3对应AP0~3 bit4对应sta */
    hal_vap_clr_opmode(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->st_vap_base_info.en_vap_mode);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* 节能队列不为空的情况下，释放节能队列中的mpdu */
        dmac_psm_clear_ps_queue(pst_dmac_user);

        /* 释放beacon帧 */
        dmac_beacon_free(pst_dmac_vap);
#ifdef _PRE_WLAN_FEATURE_DBAC
        dmac_alg_vap_down_notify(pst_mac_vap);
#endif
#ifdef _PRE_WLAN_FEATURE_DFS
        hal_enable_radar_det(pst_dmac_vap->pst_hal_device, 0);
#endif
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        /* 关闭sta tsf定时器 */
        hal_disable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);
    }
    else
    {

    }

    /* 通知扫描特性 */
    dmac_mgmt_scan_vap_down(pst_mac_vap);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#ifdef _PRE_WLAN_FEATURE_P2P
    if (WLAN_P2P_CL_MODE == mac_get_p2p_mode(pst_mac_vap))
    {
    	mac_vap_state_change(pst_mac_vap, MAC_VAP_STATE_STA_SCAN_COMP);
    }
    else
#endif
    {
    	mac_vap_state_change(pst_mac_vap, MAC_VAP_STATE_INIT);
    }
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_vap_down_handle(pst_mac_vap);
#endif


    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_down_vap::down vap succ.vap mode[%d] state[%d].}",
                      pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_wifi_en
 功能描述  : disable wifi,以业务VAP为操作单位
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_PM
OAL_STATIC oal_uint32  dmac_config_wifi_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    oal_int32                    l_value;
    dmac_vap_stru               *pst_dmac_vap;
    oal_uint16                   us_type;
    mac_device_stru             *pst_mac_dev;
    oal_uint8                    uc_state_to;

    l_value = *((oal_int32 *)puc_param);
    if(1 == l_value)
    {
        us_type = AP_PWR_EVENT_WIFI_ENABLE;
    }
    else
    {
        us_type = AP_PWR_EVENT_WIFI_DISABLE;
    }

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_config_wifi_en::pst_mac_dev[%d] is NULL!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if(pst_mac_dev->uc_cfg_vap_id == pst_mac_vap->uc_vap_id)
    {
        /*cfg vap,直接配置device*/
        if (AP_PWR_EVENT_WIFI_ENABLE == us_type)
        {
            uc_state_to = DEV_PWR_STATE_WORK;
        }
        else
        {
            uc_state_to = DEV_PWR_STATE_DEEP_SLEEP;
        }
        mac_pm_set_hal_state(pst_mac_dev,uc_state_to);
    }
    else
    {
        if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
        /*业务VAP，给PM推送事件*/
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

            dmac_pm_post_event(pst_dmac_vap,us_type,0,OAL_PTR_NULL);
        }
    }
    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_config_pm_info
 功能描述  : pm信息,VAP为配置VAP，用于查找device
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC oal_uint32  dmac_config_pm_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru             *pst_device;
    dmac_vap_stru               *pst_dmac_vap;
    mac_pm_arbiter_stru         *pst_pm_arbiter;
    mac_pm_handler_stru         *pst_pm_handler;
    mac_fsm_stru                *pst_pm_fsm;
    oal_uint32                   ul_loop;
    oal_uint8                    uc_vap_idx;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pm_info::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*device下arbiter的信息*/
    pst_pm_arbiter = pst_device->pst_pm_arbiter;
    if(OAL_PTR_NULL == pst_pm_arbiter)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "Requestor num = %d,id_bitmap = 0x%x\n",pst_pm_arbiter->uc_requestor_num,pst_pm_arbiter->ul_id_bitmap);
    for(ul_loop=0;ul_loop<pst_pm_arbiter->uc_requestor_num;ul_loop++)
    {
        if(0 == ul_loop%4)
        {
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "\n");
        }
        OAL_IO_PRINT("Requestor id %d:%s ,",ul_loop,pst_pm_arbiter->requestor[ul_loop].auc_id_name);

    }
    /*state bitmap*/
    for(ul_loop=0;ul_loop<DEV_PWR_STATE_BUTT;ul_loop++)
    {
        if(0 == ul_loop%4)
        {
            OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "\n");
        }
        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "state %d bitmap:0x%x ,",
                        ul_loop,pst_pm_arbiter->ul_state_bitmap[ul_loop]);
    }

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "\n Curr State:(%d), Prev State:(%d)\n",
                  pst_pm_arbiter->uc_cur_state, pst_pm_arbiter->uc_prev_state);
   /*每VAP状态机FSM*/
   /* 遍历device下所有vap */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
      pst_dmac_vap = mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
      if (OAL_PTR_NULL == pst_dmac_vap)
      {
          OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_CFG, "{hmac_config_wifi_enable::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
          return OAL_ERR_CODE_PTR_NULL;
      }
      pst_pm_handler = pst_dmac_vap->pst_pm_handler;
      if(!pst_pm_handler)
      {
        return OAL_ERR_CODE_PTR_NULL;
      }
      pst_pm_fsm = pst_pm_handler->p_mac_fsm;
      if(!pst_pm_fsm)
      {
        return OAL_ERR_CODE_PTR_NULL;
      }
      OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"Arbiter id = %d,max_inactive_time = %d\n",
                    pst_pm_handler->ul_pwr_arbiter_id,pst_pm_handler->ul_max_inactive_time);
      OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"inactive_time = %d,user_check_count = %d,user_num = %d\n",
                    pst_pm_handler->ul_inactive_time,pst_pm_handler->ul_user_check_count,pst_dmac_vap->st_vap_base_info.us_user_nums);
      OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"auto_sleep_en = %d, wow_en = %d, siso_en = %d\n",
                    pst_pm_handler->bit_pwr_sleep_en,pst_pm_handler->bit_pwr_wow_en,
                    pst_pm_handler->bit_pwr_siso_en);
      OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"Cur State:(%d), Prev state:(%d), Last event:(%d)\n",
                    pst_pm_fsm->uc_cur_state, pst_pm_fsm->uc_prev_state, pst_pm_fsm->us_last_event);

    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_pm_en
 功能描述  : pm功能开关,VAP为配置VAP，用于查找device
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_pm_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru             *pst_device;
    dmac_vap_stru               *pst_dmac_vap;
    mac_pm_arbiter_stru         *pst_pm_arbiter;
    oal_uint8                    uc_vap_idx;
    oal_int32                    l_value;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pm_en::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*device下arbiter的信息*/
    pst_pm_arbiter = pst_device->pst_pm_arbiter;
    if(OAL_PTR_NULL == pst_pm_arbiter)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pm_en::pst_pm_arbiter null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    l_value = *((oal_int32 *)puc_param);
    pst_device->en_pm_enable = (1==l_value)?OAL_TRUE:OAL_FALSE;


    /*使能,为每个VAP attach pm handler*/
    /*去使能,为每个VAP deattach pm handler*/
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
      pst_dmac_vap = mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
      if (OAL_PTR_NULL == pst_dmac_vap)
      {
          OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_CFG, "{dmac_config_pm_en::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
          return OAL_ERR_CODE_PTR_NULL;
      }

      /*STA模式待开发*/
      if(WLAN_VAP_MODE_BSS_STA ==  pst_dmac_vap->st_vap_base_info.en_vap_mode)
      {
        continue;
      }

      if(OAL_TRUE == pst_device->en_pm_enable)
      {
        dmac_pm_ap_attach(pst_dmac_vap);
      }
      else
      {
        dmac_pm_ap_deattach(pst_dmac_vap);
      }
    }
    return OAL_SUCC;
}

#endif

#ifdef _PRE_WLAN_PERFORM_STAT
/*****************************************************************************
 函 数 名  : dmac_config_pfm_stat
 功能描述  : 开始性能统计
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_pfm_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_stat_param_stru        *pst_stat_param  = OAL_PTR_NULL;
    mac_user_stru                  *pst_user        = OAL_PTR_NULL;
    dmac_tid_stru                  *pst_tid         = OAL_PTR_NULL;
    oal_void                       *p_void          = OAL_PTR_NULL;
    oal_uint32                      ul_ret          = OAL_SUCC;

    pst_stat_param = (mac_cfg_stat_param_stru *)puc_param;

    switch (pst_stat_param->en_stat_type)
    {
        case MAC_STAT_TYPE_TID_DELAY:
        case MAC_STAT_TYPE_TID_PER:
        case MAC_STAT_TYPE_TID_THRPT:
            pst_user = mac_vap_get_user_by_addr(pst_mac_vap, pst_stat_param->auc_mac_addr);

            ul_ret = dmac_user_get_tid_by_num(pst_user, pst_stat_param->uc_tidno, &pst_tid);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::dmac_user_get_tid_by_num failed[%d].}", ul_ret);
                return ul_ret;
            }

            p_void = (oal_void *)pst_tid;

            break;

        case MAC_STAT_TYPE_USER_THRPT:
            pst_user = mac_vap_get_user_by_addr(pst_mac_vap, pst_stat_param->auc_mac_addr);

            p_void = (oal_void *)pst_user;

            break;

        case MAC_STAT_TYPE_VAP_THRPT:
            p_void = (oal_void *)pst_mac_vap;

            break;

        default:
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
            return OAL_FAIL;
    }

    /* 注册统计节点 */
    ul_ret = dmac_stat_register(OAM_MODULE_ID_PERFORM_STAT, pst_stat_param->en_stat_type, p_void, OAL_PTR_NULL, OAL_PTR_NULL,pst_mac_vap->ul_core_id);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::invalid en_stat_type[%d].}", pst_stat_param->en_stat_type);
        return ul_ret;
    }

    /* 同时开始启动统计 */
    ul_ret = dmac_stat_start(OAM_MODULE_ID_PERFORM_STAT,
                             pst_stat_param->en_stat_type,
                             pst_stat_param->us_stat_period,
                             pst_stat_param->us_stat_num,
                             p_void);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_stat::dmac_stat_start failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_pfm_display
 功能描述  : 显示性能日志
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_pfm_display(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_display_param_stru     *pst_display_param  = OAL_PTR_NULL;
    mac_user_stru                  *pst_user            = OAL_PTR_NULL;
    dmac_tid_stru                  *pst_tid             = OAL_PTR_NULL;
    oal_void                       *p_void              = OAL_PTR_NULL;
    oal_uint32                      ul_ret              = OAL_SUCC;

    pst_display_param = (mac_cfg_display_param_stru *)puc_param;

    switch (pst_display_param->en_stat_type)
    {
        case MAC_STAT_TYPE_TID_DELAY:
        case MAC_STAT_TYPE_TID_PER:
        case MAC_STAT_TYPE_TID_THRPT:
            pst_user = mac_vap_get_user_by_addr(pst_mac_vap, pst_display_param->auc_mac_addr);

            ul_ret = dmac_user_get_tid_by_num(pst_user, pst_display_param->uc_tidno, &pst_tid);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::dmac_user_get_tid_by_num failed[%d].}", ul_ret);
                return ul_ret;
            }

            p_void = (oal_void *)pst_tid;

            break;

        case MAC_STAT_TYPE_USER_THRPT:
            pst_user = mac_vap_get_user_by_addr(pst_mac_vap, pst_display_param->auc_mac_addr);

            p_void = (oal_void *)pst_user;

            break;

        case MAC_STAT_TYPE_VAP_THRPT:
            p_void = (oal_void *)pst_mac_vap;

            break;

        default:
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::invalid en_stat_type[%d].}", pst_display_param->en_stat_type);
            return OAL_FAIL;
    }

    /* 显示统计信息 */
    ul_ret = dmac_stat_display(OAM_MODULE_ID_PERFORM_STAT, pst_display_param->en_stat_type, p_void);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::dmac_stat_display failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* 注销统计节点 */
    ul_ret = dmac_stat_unregister(OAM_MODULE_ID_PERFORM_STAT, pst_display_param->en_stat_type, p_void);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_pfm_display::dmac_stat_unregister failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

#endif

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
 函 数 名  : dmac_config_set_pm_chip_state
 功能描述  : 设置芯片睡眠或唤醒
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_chip_state(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru             *pst_device;
    hal_lpm_state_param_stru     st_para;
    mac_cfg_lpm_sleep_para_stru  *pst_set_para;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_lpm_chip_state::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_set_para = (mac_cfg_lpm_sleep_para_stru*)puc_param;
    if (MAC_LPM_STATE_SOFT_SLEEP == pst_set_para->uc_pm_switch)
    {

        st_para.bit_soft_sleep_en = 1;
        st_para.ul_sleep_time     = 1000*(pst_set_para->us_sleep_ms);   /*15ms*/

        //dmac_test_lpm_create_sleep_timer(pst_device,st_para.us_sleep_time);

        hal_set_lpm_state(pst_device->pst_device_stru,HAL_LPM_STATE_NORMAL_WORK,HAL_LPM_STATE_DEEP_SLEEP,&st_para);

    }

    if (MAC_LPM_STATE_GPIO_SLEEP == pst_set_para->uc_pm_switch)
    {
        st_para.bit_gpio_sleep_en = 1;
        hal_set_lpm_state(pst_device->pst_device_stru,HAL_LPM_STATE_NORMAL_WORK,HAL_LPM_STATE_DEEP_SLEEP,&st_para);

    }

    if (MAC_LPM_STATE_WORK == pst_set_para->uc_pm_switch)
    {
        /*唤醒*/
        hal_set_lpm_state(pst_device->pst_device_stru,HAL_LPM_STATE_DEEP_SLEEP,HAL_LPM_STATE_NORMAL_WORK,OAL_PTR_NULL);

    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_lpm_soc_mode
 功能描述  : 设置SOC低功耗节能模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_soc_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                  *pst_device;
    mac_cfg_lpm_soc_set_stru         *pst_soc_para;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL ;
    }
    pst_soc_para = (mac_cfg_lpm_soc_set_stru*)puc_param;

    switch(pst_soc_para->en_mode)
    {
        case MAC_LPM_SOC_BUS_GATING:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_BUS_GATING,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        case MAC_LPM_SOC_PCIE_RD_BYPASS:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_PCIE_RD_BYPASS,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        case MAC_LPM_SOC_MEM_PRECHARGE:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_MEM_PRECHARGE,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        case MAC_LPM_SOC_PCIE_L0_S:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_PCIE_L0,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        case MAC_LPM_SOC_PCIE_L1_0:
            hal_set_soc_lpm(pst_device->pst_device_stru,HAL_LPM_SOC_PCIE_L1_PM,pst_soc_para->uc_on_off,pst_soc_para->uc_pcie_idle);
            break;
        default:
            break;
    }

    return OAL_SUCC ;

}

/*****************************************************************************
 函 数 名  : dmac_config_set_lpm_psm_param
 功能描述  : 设置芯片PSM寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_psm_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                  *pst_device;
    mac_cfg_lpm_psm_param_stru       *pst_psm_para;
    dmac_vap_stru                    *pst_dmac_vap;
    hal_to_dmac_vap_stru             *pst_hal_vap;

    /* 转化为DMAC VAP */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_hal_vap = pst_dmac_vap->pst_hal_vap;

	pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if(OAL_PTR_NULL == pst_hal_vap || OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }
    pst_psm_para = (mac_cfg_lpm_psm_param_stru*)puc_param;
    if(0 == pst_psm_para->uc_psm_on||1 == pst_psm_para->uc_psm_on)
    {
        hal_set_psm_listen_interval(pst_hal_vap, pst_psm_para->us_psm_listen_interval);
        hal_set_psm_tbtt_offset(pst_hal_vap, pst_psm_para->us_psm_tbtt_offset);
        hal_set_psm_wakeup_mode(pst_device->pst_device_stru, pst_psm_para->uc_psm_wakeup_mode);
        hal_set_psm_status(pst_device->pst_device_stru, pst_psm_para->uc_psm_on);

        hal_test_lpm_set_psm_en(pst_psm_para->uc_psm_on);
    }
    else
    {
        /*debug显示结果*/
        hal_test_lpm_psm_dump_record();
    }

    return OAL_SUCC;

}


/*****************************************************************************
 函 数 名  : dmac_config_set_lpm_smps_mode
 功能描述  : 设置芯片睡眠或唤醒
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru    *pst_device;
    oal_uint8           uc_mode;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_lpm_smps_mode::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_mode = *puc_param;
    hal_set_smps_mode(pst_device->pst_device_stru,uc_mode);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_lpm_smps_stub
 功能描述  : smps ap侧发包打桩发送速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_smps_stub(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru						 *pst_device;
    mac_cfg_lpm_smps_stub_stru           *pst_smps_stub;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }

    pst_smps_stub = (mac_cfg_lpm_smps_stub_stru*)puc_param;
    g_st_dmac_test_mng.st_lpm_smps_stub.uc_stub_type= pst_smps_stub->uc_stub_type;
    g_st_dmac_test_mng.st_lpm_smps_stub.uc_rts_en = pst_smps_stub->uc_rts_en;

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_config_set_lpm_txop_ps
 功能描述  : 设置芯片txop ps寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_txop_ps(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                 *pst_device;
    mac_cfg_lpm_txopps_set_stru* pst_txopps_set;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }
    pst_txopps_set = (mac_cfg_lpm_txopps_set_stru*)puc_param;
    if((0 == pst_txopps_set->uc_txop_ps_on)||(1 == pst_txopps_set->uc_txop_ps_on))
    {
        hal_set_txop_ps_condition1(pst_device->pst_device_stru, pst_txopps_set->uc_conditon1);
        hal_set_txop_ps_condition2(pst_device->pst_device_stru, pst_txopps_set->uc_conditon2);
        hal_set_txop_ps_enable(pst_device->pst_device_stru,     pst_txopps_set->uc_txop_ps_on);

        dmac_test_lpm_txopps_en(pst_txopps_set->uc_txop_ps_on);
    }
    else
    {
        dmac_test_lpm_txopps_debug();
    }

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_config_set_lpm_txop_ps_tx_stub
 功能描述  : 设置芯片txop ps寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_txop_ps_tx_stub(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru						 *pst_device;
    mac_cfg_lpm_txopps_tx_stub_stru      *pst_txopps_tx_stub;
    dmac_lpm_txopps_tx_stub_stru         *pst_txop_stub;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }
    pst_txopps_tx_stub = (mac_cfg_lpm_txopps_tx_stub_stru*)puc_param;
    pst_txop_stub = &g_st_dmac_test_mng.st_lpm_txop_stub;
    pst_txop_stub->uc_stub_on = pst_txopps_tx_stub->uc_stub_on;
    pst_txop_stub->us_begin_num = pst_txopps_tx_stub->us_begin_num;
    pst_txop_stub->us_curr_num = 0;
    pst_txop_stub->us_partial_aid_real = 0;

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_config_set_lpm_wow_en
 功能描述  : 设置芯片txop ps寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_lpm_wow_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                 *pst_mac_device;
    mac_cfg_lpm_wow_en_stru         *pst_wow_en;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint8                       uc_vap_idx;
    oal_uint32                      ul_wow_set_bitmap = 0;
    hal_wow_param_stru              st_wow_para;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_FAIL;
    }
    pst_wow_en = (mac_cfg_lpm_wow_en_stru*)puc_param;
    OAL_MEMZERO(&st_wow_para, OAL_SIZEOF(hal_wow_param_stru));
    dmac_test_lpm_set_wow_en(pst_wow_en->uc_en);

    /*hipriv "Hisilicon0 lpm_wow_en 0|1|2(0不使能|1使能|2调试信息) 0|1(Null data是否唤醒)"*/
    if(pst_wow_en->uc_en==1||pst_wow_en->uc_en==0)
    {
        if(pst_wow_en->uc_en)
        {
            ul_wow_set_bitmap|= HAL_WOW_PARA_EN;
            for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
            {

                pst_dmac_vap =  mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
                if (OAL_PTR_NULL == pst_dmac_vap)
                {
                    OAM_WARNING_LOG0(pst_mac_device->auc_vap_id[uc_vap_idx], OAM_SF_CFG, "{dmac_config_set_lpm_wow_en::pst_dmac_vap null.");
                    return OAL_ERR_CODE_PTR_NULL;
                }
                dmac_test_lpm_wow_prepare_probe_resp(pst_dmac_vap);
                dmac_test_lpm_wow_prepare_null_data(pst_dmac_vap);
                if(0 == pst_dmac_vap->pst_hal_vap->uc_vap_id)
                {
                  if(!pst_dmac_vap->pst_wow_probe_resp)
                   {
                        continue;
                   }
                  st_wow_para.ul_ap0_probe_resp_address = OAL_VIRT_TO_PHY_ADDR((oal_uint32 *)oal_netbuf_data(pst_dmac_vap->pst_wow_probe_resp));
                  st_wow_para.ul_ap0_probe_resp_len = pst_dmac_vap->us_wow_probe_resp_len;
                  st_wow_para.uc_ap0_probe_resp_phy = 0;    /*11b*/
                  st_wow_para.uc_ap0_probe_resp_rate = 0;   /*1M*/
                  ul_wow_set_bitmap |= HAL_WOW_PARA_AP0_PROBE_RESP;
                }
                else if(1 == pst_dmac_vap->pst_hal_vap->uc_vap_id)
                {
                  if(!pst_dmac_vap->pst_wow_probe_resp)
                   {
                        continue;
                   }
                  st_wow_para.ul_ap1_probe_resp_address = OAL_VIRT_TO_PHY_ADDR((oal_uint32 *)oal_netbuf_data(pst_dmac_vap->pst_wow_probe_resp));
                  st_wow_para.ul_ap1_probe_resp_len = pst_dmac_vap->us_wow_probe_resp_len;
                  st_wow_para.uc_ap1_probe_resp_phy = 0;    /*11b*/
                  st_wow_para.uc_ap1_probe_resp_rate = 0;   /*1M*/
                  ul_wow_set_bitmap |= HAL_WOW_PARA_AP1_PROBE_RESP;
                }
                else if(4 == pst_dmac_vap->pst_hal_vap->uc_vap_id)
                {
                   if(!pst_dmac_vap->pst_wow_null_data)
                   {
                        continue;
                   }
                   st_wow_para.ul_nulldata_address = OAL_VIRT_TO_PHY_ADDR((oal_uint32 *)oal_netbuf_data(pst_dmac_vap->pst_wow_null_data));
                   st_wow_para.uc_nulldata_rate = 0;
                   st_wow_para.uc_nulldata_phy_mode = 0;
                   ul_wow_set_bitmap |= HAL_WOW_PARA_NULLDATA;

                   st_wow_para.ul_nulldata_interval = 1000; /*1s*/
                }
            }
            st_wow_para.uc_nulldata_awake = pst_wow_en->uc_null_wake;
            ul_wow_set_bitmap |= HAL_WOW_PARA_NULLDATA_AWAKE;

            hal_set_wow_en(pst_mac_device->pst_device_stru,ul_wow_set_bitmap,&st_wow_para);

            OAL_IO_PRINT("call dmac_test_lpm_create_sleep_timer \n");
            dmac_test_lpm_create_sleep_timer(pst_mac_device,30);

        }
        else
        {
            ul_wow_set_bitmap = 0;
            for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
            {

                pst_dmac_vap =  mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
                if (OAL_PTR_NULL == pst_dmac_vap)
                {
                    OAM_WARNING_LOG0(pst_mac_device->auc_vap_id[uc_vap_idx], OAM_SF_CFG, "{dmac_config_set_lpm_wow_en::pst_dmac_vap null.");
                    return OAL_ERR_CODE_PTR_NULL;
                }
                dmac_test_lpm_wow_release_probe_resp(pst_dmac_vap);
                dmac_test_lpm_wow_release_null_data(pst_dmac_vap);
            }

            hal_set_wow_en(pst_mac_device->pst_device_stru,ul_wow_set_bitmap,&st_wow_para);

            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(g_st_dmac_test_mng.st_sleep_timer));
        }

    }
    else
    {
#if(_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

        /*显示中断次数*/
        //dmac_test_lpm_wow_debug();
        oal_uint32          ul_val = 0x0;

        /*GPIO 47*/
        /*1.设置成软件模式*/
        ul_val = oal_readl((oal_uint32)(g_pst_5610_mode + 0x1a4));
        ul_val |= BIT15;
        oal_writel(ul_val, (oal_uint32)(g_pst_5610_mode + 0x1a4));

        /*2.设置数据方向in*/
        ul_val =  oal_readl((oal_uint32)(g_pst_5610_gpio + 0x4));
        ul_val &= ~BIT15;
        oal_writel(ul_val, (oal_uint32)(g_pst_5610_gpio + 0x4));

        /*读数据寄存器*/
        ul_val =  oal_readl((oal_uint32)(g_pst_5610_gpio + 0x50));

        OAL_IO_PRINT("GPIO 47 0x10107000 = 0x%x \n",ul_val);
#endif
#endif
    }
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_lpm_tx_probe_request
 功能描述  : 设置芯片txop ps寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_lpm_tx_probe_request(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_device ;
    dmac_vap_stru                   *pst_dmac_vap ;
    mac_cfg_lpm_tx_data_stru        *pst_lpm_tx_data ;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_FAIL ;
    }

    if (0 == pst_mac_device->uc_vap_num)
    {
       OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_lpm_tx_probe_request::can't find existed vap to send probe_req.}");
       return OAL_FAIL ;
    }

   pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[0]);
   if (OAL_PTR_NULL == pst_dmac_vap)
   {
       OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_lpm_tx_probe_request::pst_dmac_vap null.}");

       return OAL_ERR_CODE_PTR_NULL;
   }

   pst_lpm_tx_data = (mac_cfg_lpm_tx_data_stru*)puc_param;

   dmac_test_lpm_send_probe_requst(pst_dmac_vap,pst_lpm_tx_data->uc_positive,pst_lpm_tx_data->auc_da);

   return OAL_SUCC ;
}

/*****************************************************************************
 函 数 名  : dmac_config_remove_user_lut
 功能描述  : 删除/恢复用户LUT
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_remove_user_lut(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_remove_lut_stru *pst_param;    /* 复用删除用户结构体 */
    dmac_user_stru          *pst_dmac_user;


    pst_param = (mac_cfg_remove_lut_stru *)puc_param;

    pst_dmac_user = mac_res_get_dmac_user(pst_param->us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_remove_user_lut::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (1 == pst_param->uc_is_remove)
    {
        /* remove lut */
        dmac_user_inactive(pst_dmac_user);


    }
    else
    {
        /* resume lut */
        dmac_user_active(pst_dmac_user);
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_send_frame
 功能描述  : 根据指定的mac地址发管理帧/控制帧
 输入参数  : vap指针
             uc_len 参数长度
             puc_param 参数指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_send_frame(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_user_stru                  *pst_dmac_user;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_netbuf_stru                 *pst_netbuf;
    oal_uint32                       ul_frame_len = 0;
    mac_tx_ctl_stru                 *pst_tx_ctl;
    oal_uint32                       ul_ret;
    mac_cfg_send_frame_param_stru   *pst_param = (mac_cfg_send_frame_param_stru  *)puc_param;
    dmac_test_encap_frame            pst_test_encap_frame_fun;

    pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_param->auc_mac_ra);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                       "{dmac_config_send_frame::cannot find user by addr!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_send_frame::cannot find vap by user[user_id is %d]!}",
                                pst_dmac_user->st_user_base_info.uc_vap_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 申请帧内存 */
    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_MGMT_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_send_frame::cannot alloc netbuff in size[%d].}", WLAN_LARGE_NETBUF_SIZE);

        return OAL_ERR_CODE_PTR_NULL;
    }
     /* 初始化前后指针为NULL */
    oal_set_netbuf_prev(pst_netbuf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_netbuf, OAL_PTR_NULL);


    /* 填写netbuf的cb字段，供发送管理帧和发送完成接口使用 */
    DMAC_SET_NETBUF_CB(FRW_EVENT_TYPE_HOST_CRX, pst_dmac_user->st_user_base_info.us_assoc_id,
                        OAL_FALSE, OAL_FALSE, 0);
    MAC_GET_CB_FRAME_TYPE(pst_tx_ctl) = WLAN_CONTROL;

    /* 组帧 */
    pst_test_encap_frame_fun = dmac_test_get_encap_func(pst_param->en_frame_type);
    if(OAL_PTR_NULL == pst_test_encap_frame_fun)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_send_frame::pst_test_encap_frame_fun null.}");

        oal_netbuf_free(pst_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }
    ul_frame_len = pst_test_encap_frame_fun(&(pst_dmac_vap->st_vap_base_info),
                                            (oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf),
                                            puc_param, uc_len);

    if (0 == ul_frame_len)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_send_frame::ul_frame_len=0.}");


        oal_netbuf_free(pst_netbuf);

        return OAL_FAIL;
    }

    /* 调用发送管理帧接口 */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_netbuf, (oal_uint16)ul_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_netbuf);
        return ul_ret;
    }
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_rx_pn
 功能描述  : 写rx pn寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_rx_pn(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    mac_device_stru                 *pst_device;
    mac_cfg_set_rx_pn_stru          *pst_rx_pn;
    dmac_user_stru                  *pst_dmac_usr;
    hal_pn_lut_cfg_stru             st_pn_lut_cfg;

    pst_rx_pn = (mac_cfg_set_rx_pn_stru *)puc_param;

    pst_dmac_usr = mac_res_get_dmac_user(pst_rx_pn->us_user_idx);
    if(OAL_PTR_NULL == pst_dmac_usr)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rx_pn::pst_dmac_usr null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rx_pn::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    st_pn_lut_cfg.uc_pn_key_type = 1;
    st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_usr->uc_lut_index;
    st_pn_lut_cfg.uc_pn_tid      = 0;
    st_pn_lut_cfg.ul_pn_msb      = 0;
    st_pn_lut_cfg.ul_pn_lsb      = pst_rx_pn->us_rx_pn;
    hal_set_rx_pn(pst_device->pst_device_stru,&st_pn_lut_cfg);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_soft_retry
 功能描述  : 写Software Retry描述符
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_soft_retry(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_test_set_software_retry(puc_param);
	return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_open_addr4
 功能描述  : 写Software Retry描述符
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_open_addr4(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_test_open_addr4(puc_param);
	return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_open_wmm_test
 功能描述  : 芯片验证打开/关闭 WMM
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_open_wmm_test(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_test_open_wmm_test(pst_mac_vap, *((oal_uint8 *)puc_param));
	return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_chip_test_open
 功能描述  : 打开芯片验证开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_chip_test_open(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_test_set_chip_test(*(oal_uint8*)puc_param);
	return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_coex
 功能描述  : 打开/关闭 共存开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_coex(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_device;
    mac_cfg_coex_ctrl_param_stru    *pst_coex_ctrl;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }
    pst_coex_ctrl = (mac_cfg_coex_ctrl_param_stru *)puc_param;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_coex::ul_mac_ctrl=%d ul_rf_ctrl=%d.}",
                  pst_coex_ctrl->ul_mac_ctrl, pst_coex_ctrl->ul_rf_ctrl);

    hal_set_coex_ctrl(pst_device->pst_device_stru, pst_coex_ctrl->ul_mac_ctrl, pst_coex_ctrl->ul_rf_ctrl);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_dfx
 功能描述  : 设置DFX特性开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月21日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_dfx(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value = *((oal_int32 *)puc_param);

    g_st_dmac_test_mng.en_cfg_tx_cnt = (oal_switch_enum_uint8)l_value;

    return OAL_SUCC;
}


#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
/*****************************************************************************
 函 数 名  : dmac_config_enable_pmf
 功能描述  : chip test强制设置pmf能力
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月13日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_enable_pmf(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_bool_enum_uint8        en_pmf_active;
    wlan_pmf_cap_status_uint8 *puc_pmf_cap;
    oal_dlist_head_stru       *pst_entry;
    oal_dlist_head_stru       *pst_user_list_head;
    mac_user_stru             *pst_user_tmp;
    dmac_vap_stru             *pst_dmac_vap;
    mac_device_stru           *pst_device;

    puc_pmf_cap = (wlan_pmf_cap_status_uint8 *)puc_param;
    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_PMF, "{dmac_config_enable_pmf:: pointer is null,pst_mac_vap[%d], puc_param[%d] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PMF, "{dmac_config_enable_pmf::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    switch(*puc_pmf_cap)
    {
        case MAC_PMF_DISABLED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_FALSE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_FALSE);
            mac_mib_set_dot11RSNAActivated(pst_mac_vap, OAL_FALSE);
            en_pmf_active = OAL_FALSE;

             /* 配置pmf的加解密总开关 */
            hal_set_pmf_crypto(pst_dmac_vap->pst_hal_vap, OAL_FALSE);
        }
        break;
        /* enable状态，不改变现有user和硬件的 */
        case MAC_PMF_ENABLED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_FALSE);
            mac_mib_set_dot11RSNAActivated(pst_mac_vap, OAL_TRUE);
            return OAL_SUCC;
        }
        case MAC_PME_REQUIRED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAActivated(pst_mac_vap, OAL_TRUE);
            en_pmf_active = OAL_TRUE;

             /* 配置pmf的加解密总开关 */
            hal_set_pmf_crypto(pst_dmac_vap->pst_hal_vap, OAL_TRUE);

        }
        break;
        default:
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PMF, "{dmac_config_enable_pmf: commend error!}");
            return OAL_FALSE;
        }
    }

    if (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state)
    {
        pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);

        for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
        {
            pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);

            /* 指向双向链表下一个节点 */
            pst_entry = pst_entry->pst_next;
            if (OAL_PTR_NULL == pst_user_tmp)
            {
                OAM_ERROR_LOG0(0, OAM_SF_PMF, "dmac_config_enable_pmf:: pst_user_tmp is null");
                return OAL_ERR_CODE_PTR_NULL;
            }
            mac_user_set_pmf_active(pst_user_tmp, en_pmf_active);

        }

    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_send_pspoll
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月30日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_send_pspoll(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_netbuf_stru         *pst_netbuf;
    oal_uint8               *puc_data;
    mac_tx_ctl_stru         *pst_tx_cb;
    oal_uint32               ul_ret;

    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_netbuf))
    {
        return OAL_PTR_NULL;
    }

    oal_netbuf_put(pst_netbuf, 16);

    puc_data = OAL_NETBUF_HEADER(pst_netbuf);

    /* frame control,发往DS的ps-poll */
    puc_data[0] = 0xA4;
    puc_data[1] = 0x01;

    /* AID */
    puc_data[2] = (oal_uint8)pst_mac_vap->us_sta_aid;
    puc_data[3] = 0xC0;

    /* BSSID */
    oal_set_mac_addr(&puc_data[4], pst_mac_vap->auc_bssid);

    /* Transmitter address */
    oal_set_mac_addr(&puc_data[10], pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_netbuf_next(pst_netbuf, OAL_PTR_NULL);
    oal_set_netbuf_prev(pst_netbuf, OAL_PTR_NULL);

    pst_tx_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    OAL_MEMZERO(pst_tx_cb, OAL_NETBUF_CB_SIZE());
    MAC_GET_CB_TX_USER_IDX(pst_tx_cb)   = pst_mac_vap->uc_assoc_vap_id;
    MAC_GET_CB_IS_MCAST(pst_tx_cb)   = OAL_FALSE;
    mac_set_cb_ac(pst_tx_cb, WLAN_WME_AC_MGMT);
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_cb)          = OAL_TRUE;
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_cb)           = pst_mac_vap->uc_vap_id;
    MAC_GET_CB_FRAME_TYPE(pst_tx_cb)          = WLAN_CONTROL;
    MAC_GET_CB_IS_MCAST(pst_tx_cb)            = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_cb, OAL_FALSE);
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_cb)   = OAL_TRUE;
    mac_set_cb_frame_hdr(pst_tx_cb, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_cb)    = 16;
    MAC_GET_CB_MPDU_NUM(pst_tx_cb)               = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_cb)             = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_cb)               = 0;

    ul_ret = dmac_tx_mgmt((dmac_vap_stru *)pst_mac_vap, pst_netbuf, 16);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_pspoll::dmac_tx_mgmt failed[%d].", ul_ret);
        oal_netbuf_free(pst_netbuf);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_send_nulldata
 功能描述  : sta发送空帧给ap，通知ap自己的节能状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月3日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_send_nulldata(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_netbuf_stru                 *pst_net_buf;
    mac_tx_ctl_stru                 *pst_tx_ctrl;
    oal_uint32                       ul_ret;
    oal_uint16                       us_frame_ctl_second_byte = 0;
    mac_user_stru                   *pst_user;
    oal_uint8                       *puc_frame;
    mac_ieee80211_qos_frame_stru    *pst_qos_header;
    mac_cfg_tx_nulldata_stru        *pst_tx_nulldata;

    /* 申请net_buff */
    pst_net_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_nulldata::pst_net_buf null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_tx_nulldata = (mac_cfg_tx_nulldata_stru *)puc_param;

    oal_set_netbuf_prev(pst_net_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

    if (pst_tx_nulldata->l_is_qos)
    {
        oal_netbuf_put(pst_net_buf, OAL_SIZEOF(mac_ieee80211_qos_frame_stru));
    }
    else
    {
        oal_netbuf_put(pst_net_buf, 24);
    }

    puc_frame = OAL_NETBUF_HEADER(pst_net_buf);

    if (0 == pst_tx_nulldata->l_is_psm)
    {
        us_frame_ctl_second_byte = 0x0100;
    }
    else
    {
        us_frame_ctl_second_byte = 0x1100;
    }

    pst_user = mac_res_get_mac_user((oal_uint16)pst_mac_vap->uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_nulldata::pst_user null.}");
        dmac_tx_excp_free_netbuf(pst_net_buf);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写帧头,其中from ds为1，to ds为0，因此frame control的第二个字节为02 */
    if (pst_tx_nulldata->l_is_qos)
    {
        mac_hdr_set_frame_control(puc_frame, (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS_NULL) | us_frame_ctl_second_byte);
    }
    else
    {
        mac_hdr_set_frame_control(puc_frame, (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | us_frame_ctl_second_byte);
    }

    if (pst_tx_nulldata->l_is_qos)
    {
        pst_qos_header = (mac_ieee80211_qos_frame_stru *)puc_frame;
        pst_qos_header->bit_qc_tid = (oal_uint8)pst_tx_nulldata->l_tidno;
        pst_qos_header->bit_qc_eosp = 1;
        pst_qos_header->bit_qc_ack_polocy = WLAN_TX_NORMAL_ACK;
    }

    /* BSSID */
    oal_set_mac_addr(&puc_frame[4], pst_user->auc_user_mac_addr);

    /* SA */
    oal_set_mac_addr(&puc_frame[10], pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* DA */
    oal_set_mac_addr(&puc_frame[16], pst_user->auc_user_mac_addr);

    /* 填写cb字段 */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    OAL_MEMZERO(pst_tx_ctrl, OAL_SIZEOF(mac_tx_ctl_stru));

    /* 填写tx部分 */
    mac_set_cb_ack_policy(pst_tx_ctrl, WLAN_TX_NORMAL_ACK);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctrl)            = FRW_EVENT_TYPE_WLAN_DTX;
    mac_set_cb_is_bar(pst_tx_ctrl, OAL_FALSE);

    if (pst_tx_nulldata->l_is_qos)
    {
        mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_TID_TO_AC(pst_tx_nulldata->l_tidno));
    }
    else
    {
        mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_AC_BE);
    }
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl)        = OAL_TRUE;
    MAC_GET_CB_RETRIED_NUM(pst_tx_ctrl)          = 0;
    if (pst_tx_nulldata->l_is_qos)
    {
        mac_set_cb_tid(pst_tx_ctrl, (oal_uint8)pst_tx_nulldata->l_tidno);
    }
    else
    {
        mac_set_cb_tid(pst_tx_ctrl, WLAN_TID_FOR_DATA);
    }

    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctrl)          = pst_mac_vap->uc_vap_id;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)           = pst_mac_vap->uc_assoc_vap_id;

    /* 填写tx rx公共部分 */
    //MAC_GET_CB_FRAME_TYPE(pst_tx_ctrl)               = WLAN_DATA_NULL;
    MAC_GET_CB_IS_MCAST(pst_tx_ctrl)                 = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_ctrl, OAL_FALSE);
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)         = OAL_TRUE;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctrl)            = OAL_FALSE;
    mac_set_cb_is_use_4_addr(pst_tx_ctrl, OAL_FALSE);
    mac_set_cb_frame_hdr(pst_tx_ctrl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf));
    if (pst_tx_nulldata->l_is_qos)
    {
        MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)     = OAL_SIZEOF(mac_ieee80211_qos_frame_stru);
    }
    else
    {
        MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)     = OAL_SIZEOF(mac_ieee80211_frame_stru);
    }

    MAC_GET_CB_MPDU_NUM(pst_tx_ctrl)                = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl)              = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctrl)                = 0;

    ul_ret = dmac_tx_process_data(((dmac_vap_stru *)pst_mac_vap)->pst_hal_device, (dmac_vap_stru *)pst_mac_vap, pst_net_buf);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_send_nulldata::dmac_tx_process_data failed[%d].}", ul_ret);

        dmac_tx_excp_free_netbuf(pst_net_buf);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_clear_all_stat
 功能描述  : 清除统计信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_clear_all_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru    *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_clear_all_stat::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    /* 清除中断统计信息 */
    hal_clear_irq_stat(pst_device->pst_device_stru);

    return OAL_SUCC;
}

#endif /* CHIP_TEST */

/*****************************************************************************
 函 数 名  : dmac_config_get_fem_pa_status
 功能描述  : 获取fem和pa是否烧毁状态
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : zhangxiang
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_fem_pa_status(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                       *pst_device;
    dmac_atcmdsrv_atcmd_response_event     st_atcmdsrv_fem_pa_info;
    oal_uint32                             ul_cali_check_fem_pa_status = 0;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_fem_pa_status::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    st_atcmdsrv_fem_pa_info.uc_event_id = OAL_ATCMDSRV_FEM_PA_INFO_EVENT;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hal_get_hw_status(pst_device->pst_device_stru,&ul_cali_check_fem_pa_status);
#endif
    st_atcmdsrv_fem_pa_info.ul_event_para = ul_cali_check_fem_pa_status;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_CHECK_FEM_PA, OAL_SIZEOF(dmac_atcmdsrv_atcmd_response_event), (oal_uint8 *)&st_atcmdsrv_fem_pa_info);
    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_config_set_mib
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月19日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_mib(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    return mac_config_set_mib(pst_mac_vap, uc_len, puc_param);
}

/*****************************************************************************
 函 数 名  : dmac_config_set_obss_mib
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月28日
    作    者   : l00311403
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_obss_mib(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    wlan_mib_Dot11OperationEntry_stru *pst_new_mib;
    wlan_mib_Dot11OperationEntry_stru *pst_mib;

    pst_new_mib = (wlan_mib_Dot11OperationEntry_stru*)puc_param;
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_new_mib))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_obss_mib::null param}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mib = &pst_mac_vap->pst_mib_info->st_wlan_mib_operation;
    pst_mib->ul_dot11BSSWidthTriggerScanInterval = pst_new_mib->ul_dot11BSSWidthTriggerScanInterval;
    pst_mib->ul_dot11BSSWidthChannelTransitionDelayFactor = pst_new_mib->ul_dot11BSSWidthChannelTransitionDelayFactor;
    pst_mib->ul_dot11OBSSScanPassiveDwell = pst_new_mib->ul_dot11OBSSScanPassiveDwell;
    pst_mib->ul_dot11OBSSScanActiveDwell = pst_new_mib->ul_dot11OBSSScanActiveDwell;
    pst_mib->ul_dot11OBSSScanPassiveTotalPerChannel = pst_new_mib->ul_dot11OBSSScanPassiveTotalPerChannel;
    pst_mib->ul_dot11OBSSScanActiveTotalPerChannel = pst_new_mib->ul_dot11OBSSScanActiveTotalPerChannel;
    pst_mib->ul_dot11OBSSScanActivityThreshold = pst_new_mib->ul_dot11OBSSScanActivityThreshold;

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : dmac_config_set_thruput_bypass
 功能描述  : 设置thruput_bypass维测点
 输入参数  :
 输出参数  :
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_thruput_bypass(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_set_thruput_bypass_stru *pst_set_thruput_bypass = (mac_cfg_set_thruput_bypass_stru *)puc_param;

    OAL_SET_THRUPUT_BYPASS_ENABLE(pst_set_thruput_bypass->uc_bypass_type, pst_set_thruput_bypass->uc_value);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_performance_log_switch
 功能描述  : 设置性能打印控制开关
 输入参数  :
 输出参数  :
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月15日
    作    者   : z00185449
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
OAL_STATIC oal_uint32  dmac_config_set_performance_log_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_set_performance_log_switch_stru *pst_set_performance_log_switch = (mac_cfg_set_performance_log_switch_stru *)puc_param;
    oal_uint8                    uc_loop_index;
    dmac_vap_stru *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if(pst_set_performance_log_switch->uc_performance_log_switch_type >= DFX_PERFORMANCE_LOG_BUTT)
    {
        for(uc_loop_index = 0;uc_loop_index < DFX_PERFORMANCE_LOG_BUTT;uc_loop_index++)
        {
            DFX_SET_PERFORMANCE_LOG_SWITCH_ENABLE(uc_loop_index,pst_set_performance_log_switch->uc_value);
        }
    }
    else if(pst_set_performance_log_switch->uc_performance_log_switch_type == DFX_PERFORMANCE_DUMP)
    {
        if(0 == pst_set_performance_log_switch->uc_value )
        {
            OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_TX, "{ampdu length (1-14)%d  (15-17)%d  (18-30)%d  (31-32)%d\n.}",
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_0],
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_1],
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_2],
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_3]
            );
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{ul_tx_hardretry_count = %d,ul_tx_cts_fail = %d\n.}",
                pst_dmac_vap->st_query_stats.ul_tx_retries,
                pst_dmac_vap->st_query_stats.ul_tx_cts_fail);
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{ul_tx_mpdu_succ_num = %d, ul_tx_mpdu_fail_num = %d\n.}",
                pst_dmac_vap->st_query_stats.ul_tx_mpdu_succ_num,
                pst_dmac_vap->st_query_stats.ul_tx_mpdu_fail_num);
            OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{ul_tx_ampdu_succ_num = %d, ul_tx_mpdu_in_ampdu = %d,ul_tx_ampdu_fail_num = %d, ul_tx_mpdu_fail_in_ampdu = %d\n.}",
                pst_dmac_vap->st_query_stats.ul_tx_ampdu_succ_num,
                pst_dmac_vap->st_query_stats.ul_tx_mpdu_in_ampdu,
                pst_dmac_vap->st_query_stats.ul_tx_ampdu_fail_num,
                pst_dmac_vap->st_query_stats.ul_tx_mpdu_fail_in_ampdu);
        }
        else
        {
            for(uc_loop_index = 0;uc_loop_index < DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_BUTT;uc_loop_index++)
            {
                pst_dmac_vap->st_query_stats.aul_tx_count_per_apmpdu_length[uc_loop_index] = 0;
            }
        }
    }
    else
    {
        DFX_SET_PERFORMANCE_LOG_SWITCH_ENABLE(pst_set_performance_log_switch->uc_performance_log_switch_type,pst_set_performance_log_switch->uc_value);
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_set_wmm_open_cfg
 功能描述  : 打开WMM，配置WMM寄存器
 输入参数  : pst_mac_device: DMAC VAP

 输出参数  :
 返 回 值  : 成功/失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_config_set_wmm_open_cfg(hal_to_dmac_vap_stru *pst_hal_vap, mac_wme_param_stru  *pst_wmm)
{
    wlan_wme_ac_type_enum_uint8     en_ac_type;

    if(OAL_PTR_NULL == pst_hal_vap || OAL_PTR_NULL == pst_wmm)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_wmm_open_cfg::param null.}");

        return;
    }
    for (en_ac_type = 0; en_ac_type < WLAN_WME_AC_BUTT; en_ac_type++)
    {
        hal_vap_set_edca_machw_cw(pst_hal_vap,
                                 (oal_uint8)(pst_wmm[en_ac_type].ul_logcwmax),
                                 (oal_uint8)(pst_wmm[en_ac_type].ul_logcwmin),
                                  en_ac_type);

        hal_vap_set_machw_aifsn_ac(pst_hal_vap, en_ac_type, (oal_uint8)pst_wmm[en_ac_type].ul_aifsn);
    }

#if 0
    hal_vap_set_machw_cw_bk(pst_hal_vap, (oal_uint8)(pst_wmm[WLAN_WME_AC_BK].ul_logcwmax), (oal_uint8)(pst_wmm[WLAN_WME_AC_BK].ul_logcwmin));
    hal_vap_set_machw_cw_be(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmin);
    hal_vap_set_machw_cw_vi(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_VI].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_VI].ul_logcwmin);
    hal_vap_set_machw_cw_vo(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_VO].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_VO].ul_logcwmin);

    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_BK, (oal_uint8)pst_wmm[WLAN_WME_AC_BK].ul_aifsn);
    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_BE, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_aifsn);
    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_VI, (oal_uint8)pst_wmm[WLAN_WME_AC_VI].ul_aifsn);
    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_VO, (oal_uint8)pst_wmm[WLAN_WME_AC_VO].ul_aifsn);
#endif

    hal_vap_set_machw_txop_limit_bkbe(pst_hal_vap, (oal_uint16)pst_wmm[WLAN_WME_AC_BE].ul_txop_limit, (oal_uint16)pst_wmm[WLAN_WME_AC_BK].ul_txop_limit);
    hal_vap_set_machw_txop_limit_vivo(pst_hal_vap, (oal_uint16)pst_wmm[WLAN_WME_AC_VO].ul_txop_limit, (oal_uint16)pst_wmm[WLAN_WME_AC_VI].ul_txop_limit);

}

/*****************************************************************************
 函 数 名  : dmac_config_set_wmm_close_cfg
 功能描述  : 关闭WMM，配置WMM寄存器，注意，硬MAC在关闭WMM条件下使用VO发送后续帧，
             而张炜要求使用BE配置参数进行数据发送，折衷一下，使用BE配置VO
 输入参数  : pst_mac_device: DMAC VAP

 输出参数  :
 返 回 值  : 成功/失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_config_set_wmm_close_cfg(hal_to_dmac_vap_stru *pst_hal_vap, mac_wme_param_stru  *pst_wmm)
{
    if(OAL_PTR_NULL == pst_hal_vap || OAL_PTR_NULL == pst_wmm)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_wmm_close_cfg::param null.}");

        return;
    }
   // hal_vap_set_machw_cw_vo(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmin);
    hal_vap_set_edca_machw_cw(pst_hal_vap, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmax, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_logcwmin, WLAN_WME_AC_VO);
    hal_vap_set_machw_aifsn_ac(pst_hal_vap, WLAN_WME_AC_VO, (oal_uint8)pst_wmm[WLAN_WME_AC_BE].ul_aifsn);
    hal_vap_set_machw_txop_limit_vivo(pst_hal_vap, (oal_uint16)pst_wmm[WLAN_WME_AC_BE].ul_txop_limit, (oal_uint16)pst_wmm[WLAN_WME_AC_VI].ul_txop_limit);
}

/*****************************************************************************
 函 数 名  : dmac_config_set_wmm_register
 功能描述  : 关闭或者打开WMM，配置WMM相关寄存器
 输入参数  : pst_mac_device: DMAC VAP

 输出参数  :
 返 回 值  : 成功/失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_config_set_wmm_register(mac_vap_stru *pst_mac_vap,  oal_bool_enum_uint8 en_wmm)
{
    mac_device_stru         *pst_mac_device;
    dmac_vap_stru           *pst_dmac_vap;
    mac_wme_param_stru      *pst_wmm;
    oal_uint                 ul_irq_flag;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device || OAL_PTR_NULL == pst_mac_device->pst_device_stru)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_device_id, OAM_SF_CFG, "{dmac_config_set_wmm_register::mac_res_get_dev fail or pst_mac_device->pst_device_stru NULL,device_id:%u.}",
                         pst_mac_vap->uc_device_id);
        return;
    }
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_wmm_register::mac_res_get_dmac_vap fail or pst_dmac_vap->pst_hal_vap NULL,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return;
    }

    pst_wmm = mac_get_wmm_cfg(pst_mac_vap->en_vap_mode);

    /* 关中断，挂起硬件发送需要关中断 */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DCSWR);

    /* 挂起硬件发送 */
    /* hal_set_machw_tx_suspend(pst_hal_device); */

    /* 获取时间戳 */
    /* hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf); */

    /*DTS2015080609133:设置wmm开关时, 不需要打开abort中断(共存中断) */
     /* 触发硬件abort */
    /* hal_set_tx_abort_en(pst_hal_device, 1); */
    /* 关闭wmm */
    if(!en_wmm)
    {
        /* 回收所有数据 */
        dmac_flush_txq_to_tid_of_vo(pst_mac_device->pst_device_stru);
        /* 关闭WMM */
        hal_disable_machw_edca(pst_mac_device->pst_device_stru);
        /* 重新设置WMM参数 */
        dmac_config_set_wmm_close_cfg(pst_dmac_vap->pst_hal_vap, pst_wmm);

        /* 关WMM，mib信息位中的Qos位置0 */
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = OAL_FALSE;
    }
    else
    {
        /* 打开WMM */
        hal_enable_machw_edca(pst_mac_device->pst_device_stru);
        /* 重新设置WMM参数 */
        dmac_config_set_wmm_open_cfg(pst_dmac_vap->pst_hal_vap, pst_wmm);

        /* 开WMM，mib信息位中的Qos位置1 */
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = OAL_TRUE;
    }

    /* 退出abort */
    /* hal_set_tx_abort_en(pst_hal_device, 0); */

    /* 重新设置硬件发送 */
    /* hal_set_machw_tx_resume(pst_hal_device); */

    /* 再次获取时间戳 */
    /* hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf_passed); */

    /* 开中断 */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DCSWR);
}

/*****************************************************************************
 函 数 名  : dmac_config_wmm_switch
 功能描述  : 打开/关闭 WMM
 输入参数  : pst_mac_vap:mac vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_wmm_switch(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru         *pst_mac_device;
    oal_bool_enum_uint8            en_wmm = OAL_FALSE;
    en_wmm = *(oal_bool_enum_uint8 *)puc_param;
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 配置状态没有变化，不再进行后续流程 */
    if(en_wmm == pst_mac_device->en_wmm)
    {
        return OAL_SUCC;
    }
    /* 设置dev中的wmm_en，使能或者关闭4通道 */
    pst_mac_device->en_wmm = en_wmm;

    dmac_config_set_wmm_register(pst_mac_vap, en_wmm);
    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_set_rts_param
 功能描述  : 设置rts发送参数
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : c00260463
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_rts_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru            *pst_device           = OAL_PTR_NULL;
    mac_cfg_rts_tx_param_stru  *pst_mac_rts_tx_param = OAL_PTR_NULL;
    hal_cfg_rts_tx_param_stru   st_hal_rts_tx_param;

    pst_mac_rts_tx_param = (mac_cfg_rts_tx_param_stru *)puc_param;

    /*mac参数赋值给hal参数*/
    oal_memcopy(&st_hal_rts_tx_param, pst_mac_rts_tx_param, OAL_SIZEOF(st_hal_rts_tx_param));

    pst_device= mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_rts_param::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_set_rts_rate_params(pst_device->pst_device_stru, &st_hal_rts_tx_param);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_update_protection_tx_param
 功能描述  : 更新数据帧/管理帧与保护模式相关的发送参数
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : c00260463
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_update_protection_tx_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru                 *pst_mac_device;
    dmac_vap_stru                   *pst_dmac_vap;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_update_protection_tx_param::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == pst_mac_device->uc_vap_num)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_update_protection_tx_param::can't find existed vap.}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_update_protection_tx_param::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_tx_update_protection_all_txop_alg(pst_dmac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_protection
 功能描述  : 同步保护模式相关的参数
 输入参数  : mac_vap_stru *pst_mac_vap
             uc_len 数据长度
             puc_param 数据
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : l00311403
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_protection(mac_vap_stru *pst_mac_vap,
            oal_uint8 uc_len, oal_uint8 *puc_param)
{
    wlan_mib_Dot11OperationEntry_stru *pst_mib;
    mac_h2d_protection_stru     *pst_h2d_prot;
    dmac_user_stru              *pst_dmac_user;
    oal_uint32                  ul_ret;

    DMAC_CHECK_NULL(puc_param);

    pst_h2d_prot = (mac_h2d_protection_stru *)puc_param;

    //mac_dump_protection(pst_mac_vap, puc_param);

    if (pst_h2d_prot->ul_sync_mask & H2D_SYNC_MASK_BARK_PREAMBLE)
    {
        pst_dmac_user = mac_res_get_dmac_user(pst_h2d_prot->us_user_idx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
        {
            OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_protection:: user is null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }
        mac_user_set_barker_preamble_mode(&pst_dmac_user->st_user_base_info, pst_h2d_prot->st_user_cap_info.bit_barker_preamble_mode);

    }

    if (pst_h2d_prot->ul_sync_mask & H2D_SYNC_MASK_MIB)
    {
        pst_mib = &pst_mac_vap->pst_mib_info->st_wlan_mib_operation;
        pst_mib->en_dot11HTProtection = pst_h2d_prot->en_dot11HTProtection;
        pst_mib->en_dot11RIFSMode = pst_h2d_prot->en_dot11RIFSMode;
        pst_mib->en_dot11LSIGTXOPFullProtectionActivated =
            pst_h2d_prot->en_dot11LSIGTXOPFullProtectionActivated;
        pst_mib->en_dot11NonGFEntitiesPresent = pst_h2d_prot->en_dot11NonGFEntitiesPresent;
    }

    if (pst_h2d_prot->ul_sync_mask & H2D_SYNC_MASK_PROT)
    {
        oal_memcopy((oal_uint8*)&pst_mac_vap->st_protection, (oal_uint8*)&pst_h2d_prot->st_protection,
                    OAL_SIZEOF(mac_protection_stru));
    }

    ul_ret = dmac_config_update_protection_tx_param(pst_mac_vap, uc_len, puc_param);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_config_get_version
 功能描述  : 获取版本信息
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : zhangyu
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_version(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru             *pst_device;
    oal_uint32                   ul_hw_version = 0;
    oal_uint32                   ul_hw_version_data = 0;
    oal_uint32                   ul_hw_version_num = 0;
    oal_uint8                    auc_sw_version[] = "Hi1151 V100R001C01B371_20151022";
    oal_int8                     ac_tmp_buff[200];

    dmac_atcmdsrv_atcmd_response_event    st_atcmdsrv_dbb_num_info;


    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_version::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取FPGA版本 */
    hal_get_hw_version(pst_device->pst_device_stru, &ul_hw_version, &ul_hw_version_data, &ul_hw_version_num);

    OAL_SPRINTF((char*)ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "Software Version: %s. \nFPGA Version: %04x-%04x-%02x.\n", auc_sw_version, ul_hw_version, ul_hw_version_data, ul_hw_version_num);
    oam_print(ac_tmp_buff);

    st_atcmdsrv_dbb_num_info.uc_event_id = OAL_ATCMDSRV_DBB_NUM_INFO_EVENT;
    st_atcmdsrv_dbb_num_info.ul_event_para = ul_hw_version;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_GET_VERSION, OAL_SIZEOF(dmac_atcmdsrv_atcmd_response_event), (oal_uint8 *)&st_atcmdsrv_dbb_num_info);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_rx_fcs_info
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32   dmac_config_rx_fcs_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    hal_to_dmac_device_stru        *pst_hal_device;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    dmac_atcmdsrv_atcmd_response_event   st_atcmdsrv_rx_pkcg;
#endif
    hal_get_hal_to_dmac_device(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, &pst_hal_device);
    OAM_WARNING_LOG2(0, OAM_SF_CFG, "dmac_config_rx_fcs_info:packets info, succ[0x%x], fail[0x%x]\n", pst_hal_device->ul_rx_normal_mdpu_succ_num, pst_hal_device->ul_rx_ppdu_fail_num);

    /*装备测试需要将接收正确的包数上报到host侧*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        st_atcmdsrv_rx_pkcg.uc_event_id = OAL_ATCMDSRV_GET_RX_PKCG;
        st_atcmdsrv_rx_pkcg.ul_event_para = pst_hal_device->ul_rx_normal_mdpu_succ_num;
        st_atcmdsrv_rx_pkcg.s_always_rx_rssi = pst_hal_device->s_always_rx_rssi;
        dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RX_FCS_INFO, OAL_SIZEOF(dmac_atcmdsrv_atcmd_response_event), (oal_uint8 *)&st_atcmdsrv_rx_pkcg);
#endif

    /* 读后清零 */
    pst_hal_device->ul_rx_normal_mdpu_succ_num = 0;
    pst_hal_device->ul_rx_ppdu_fail_num = 0;


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_vap_nss
 功能描述  : dmac设置vap nss
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             us_len     : 参数长度
             puc_param  : 参数指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月3日
    作    者   : g00260350
    修改内容   : 增加配置到DMAC流程

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_vap_nss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
	oal_uint8            uc_value;

	uc_value = *puc_param;

	mac_vap_init_rx_nss_by_protocol(pst_mac_vap);
	mac_vap_set_rx_nss(pst_mac_vap, OAL_MIN(pst_mac_vap->en_vap_rx_nss, (uc_value - 1)));

	return OAL_SUCC;
}


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_config_resume_rx_intr_fifo
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32   dmac_config_resume_rx_intr_fifo(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_resume_rx_intr_fifo_stru   *pst_param;
    mac_device_stru              *pst_mac_dev;

    pst_param = (mac_cfg_resume_rx_intr_fifo_stru *)puc_param;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_resume_rx_intr_fifo::pst_mac_dev null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_dev->pst_device_stru->en_rx_intr_fifo_resume_flag = pst_param->uc_is_on;

    return OAL_SUCC;
}
#endif

#ifdef  _PRE_DEBUG_MODE
/*****************************************************************************
 函 数 名  : dmac_config_get_all_reg_value
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月1日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_get_all_reg_value(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru             *pst_device;


    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_get_all_reg_value:pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 读取寄存器的值 */
    hal_get_all_reg_value(pst_device->pst_device_stru);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_report_ampdu_stat
 功能描述  : 上报获取清零某一个tid下的ampdu业务流程统计
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月27日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_report_ampdu_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ampdu_stat_stru     *pst_ampdu_stat;
    dmac_user_stru              *pst_dmac_user;
    dmac_tid_stru               *pst_tid;

    pst_ampdu_stat = (mac_cfg_ampdu_stat_stru *)puc_param;

    pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, pst_ampdu_stat->auc_user_macaddr);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_report_ampdu_stat:: user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取tid，如果tid_no为8，代表对所有tid进行操作 */
    if (pst_ampdu_stat->uc_tid_no > WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{dmac_config_report_ampdu_stat::tid_no invalid, tid_no = [%d]}", pst_ampdu_stat->uc_tid_no);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (WLAN_TID_MAX_NUM == pst_ampdu_stat->uc_tid_no)
    {
        return dmac_dft_report_all_ampdu_stat(pst_dmac_user, pst_ampdu_stat->uc_param);
    }
    else
    {
        pst_tid = &pst_dmac_user->ast_tx_tid_queue[pst_ampdu_stat->uc_tid_no];

        return dmac_dft_report_ampdu_stat(pst_tid, pst_ampdu_stat->auc_user_macaddr, pst_ampdu_stat->uc_param);
    }
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_set_ampdu_aggr_num
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_ampdu_aggr_num(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_aggr_num_stru   *pst_aggr_num_ctrl;

    pst_aggr_num_ctrl = (mac_cfg_aggr_num_stru *)puc_param;

    g_uc_aggr_num_switch = pst_aggr_num_ctrl->uc_aggr_num_switch;

    if (0 != pst_aggr_num_ctrl->uc_aggr_num_switch)
    {
        g_uc_max_aggr_num = pst_aggr_num_ctrl->uc_aggr_num;

        //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_ampdu_aggr_num::aggr num start, num is [%d].}", g_uc_max_aggr_num);
    }
    else
    {
        g_uc_max_aggr_num = 0;

        //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_ampdu_aggr_num::aggr num stop.}");
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_config_freq_adjust
 功能描述  : 频偏设置
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月29日
    作    者   : h00212953
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_freq_adjust(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_freq_adjust_stru    *pst_freq_adjust;
    mac_device_stru             *pst_mac_device;

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_freq_adjust::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_freq_adjust = (mac_cfg_freq_adjust_stru *)puc_param;

    hal_freq_adjust(pst_mac_device->pst_device_stru, pst_freq_adjust->us_pll_int, pst_freq_adjust->us_pll_frac);

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 函 数 名  : dmac_config_set_smps_mode
 功能描述  : 配置命令设置SMPS模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
     1.日    期   : 2014年9月18日
       作    者   : z00241943
       修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  dmac_config_set_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_smps_mode_stru                 *pst_smps_mode;
    mac_device_stru                        *pst_mac_device;
    mac_vap_stru                           *pst_mac_vap_tmp;
    wlan_mib_mimo_power_save_enum_uint8     en_mib_smps_mode;
    oal_uint8                               uc_vap_idx;

    pst_smps_mode           = (mac_cfg_smps_mode_stru *)puc_param;

    /* 获取device结构的信息 */
    pst_mac_device   = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{dmac_config_set_smps_mode::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    en_mib_smps_mode = (wlan_mib_mimo_power_save_enum_uint8)(pst_smps_mode->uc_smps_mode);
    if (en_mib_smps_mode >= WLAN_MIB_MIMO_POWER_SAVE_BUTT)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{dmac_config_set_smps_mode::unexpect mode[%d].}", en_mib_smps_mode);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 遍历device下所有vap，设置vap下的信道号 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap_tmp = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap_tmp)
        {
            continue;
        }

        if (OAL_TRUE != pst_mac_vap_tmp->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
        {
            continue;
        }
        /* 信道设置只针对AP模式，非AP模式则跳出 */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap_tmp->en_vap_mode)
        {
            /* STA暂时不开发 */
            /* 设置STA的SMPS能力，并发送SM Power Save Frame帧 */
            continue;
        }

        /* 设置mib项 */
        pst_mac_vap_tmp->pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MIMOPowerSave = en_mib_smps_mode;
        mac_vap_set_smps(pst_mac_vap_tmp, en_mib_smps_mode);

        /* VAP下user头指针不应该为空 */
        if (OAL_FALSE == oal_dlist_is_empty(&pst_mac_vap->st_mac_user_list_head))
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_smps_mode::st_mac_user_list_head is not empty.}");
        }
    }

    if (WLAN_MIB_MIMO_POWER_SAVE_MIMO == en_mib_smps_mode)
    {
        pst_mac_device->en_smps = OAL_FALSE;
        pst_mac_device->uc_dev_smps_mode = HAL_SMPS_MODE_DISABLE;
    }
    else
    {
        pst_mac_device->en_smps = OAL_TRUE;
        pst_mac_device->uc_dev_smps_mode = en_mib_smps_mode;
    }

    /* 写SMPS控制寄存器 */
    hal_set_smps_mode(pst_mac_device->pst_device_stru, pst_mac_device->uc_dev_smps_mode);

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : dmac_config_set_app_ie_to_vap
 功能描述  : 设置APP IE 到DMAC
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_app_ie_to_vap(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_app_ie_stru         *pst_app_ie;

    if ((OAL_PTR_NULL == puc_param) || (OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_app_ie_to_vap::param is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_app_ie = (oal_app_ie_stru *)puc_param;

    mac_vap_save_app_ie(pst_mac_vap, pst_app_ie, pst_app_ie->en_app_ie_type);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_show_device_memleak
 功能描述  : device侧memleak配置命令接口
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月231日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_show_device_memleak(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_pool_id_stru          *pst_pool_id_param;
    oal_uint8                         uc_pool_id;

    pst_pool_id_param = (mac_device_pool_id_stru *)puc_param;
    uc_pool_id  = pst_pool_id_param->uc_pool_id;

    if (uc_pool_id >=  OAL_MEM_POOL_ID_BUTT)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_show_device_memleak::uc_pool_id %d >= OAL_MEM_POOL_ID_BUTT.}", uc_pool_id);
        return OAL_FAIL;
    }

    if (uc_pool_id < OAL_MEM_POOL_ID_NETBUF)
    {
        oal_mem_leak(uc_pool_id);
    }
    else if (OAL_MEM_POOL_ID_NETBUF == uc_pool_id)
    {
        oal_mem_netbuf_leak();
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_show_device_meminfo
 功能描述  : device侧meminfo配置命令接口
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月231日
    作    者   : lingxuemeng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_show_device_meminfo(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_pool_id_stru          *pst_pool_id_param;
    oal_uint8                         uc_pool_id;

    pst_pool_id_param = (mac_device_pool_id_stru *)puc_param;
    uc_pool_id  = pst_pool_id_param->uc_pool_id;

    if (uc_pool_id >=  OAL_MEM_POOL_ID_BUTT)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_show_device_meminfo::uc_pool_id %d >= OAL_MEM_POOL_ID_BUTT.}", uc_pool_id);
        return OAL_FAIL;
    }

    OAL_MEM_INFO_PRINT(uc_pool_id);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_cancel_remain_on_channel
 功能描述  : 设置wifi 返回指定信道
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_cancel_remain_on_channel(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_scan_req_stru       *pst_scan_req_params;
    mac_device_stru         *pst_mac_device;

    /* 获取mac dev */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_config_cancel_remain_on_channel::pst_mac_device[%d] is NULL!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 1.判断当前是否正在扫描，如果不是在扫描，直接返回 */
    if (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_cancel_remain_on_channel::scan is not running.}");
        return OAL_SUCC;
    }

    pst_scan_req_params = &(pst_mac_device->st_scan_params);

    /* 2.判断当前扫描的vap是不是p2p的，如果不是，直接返回，如果是，判断是否在监听，不是直接返回 */
    if ((pst_mac_vap->uc_vap_id != pst_scan_req_params->uc_vap_id) ||
        (MAC_SCAN_FUNC_P2P_LISTEN != pst_scan_req_params->uc_scan_func))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                        "{dmac_config_cancel_remain_on_channel::other vap is scanning, scan_func[%d].}",
                        pst_scan_req_params->uc_scan_func);
        return OAL_SUCC;
    }

    /* 3.删除定时器，并且调用扫描完成 */
    if (OAL_TRUE == pst_mac_device->st_scan_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_mac_device->st_scan_timer);
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_config_cancel_remain_on_channel::stop scan.}");

        dmac_scan_end(pst_mac_device);
    }
    else
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "shouldn't go here");
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 函 数 名  : dmac_config_set_p2p_ps_ops
 功能描述  : 设置P2P OPS 节能
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_p2p_ps_ops(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;
    hal_to_dmac_vap_stru        *pst_hal_vap;
    mac_cfg_p2p_ops_param_stru  *pst_p2p_ops;


    pst_p2p_ops = (mac_cfg_p2p_ops_param_stru *)puc_param;
    /* 获取hal_vap 结构体 */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_p2p_ps_ops::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }


    /*  sanity check, CTwindow 7bit*/
    if(pst_p2p_ops->uc_ct_window < 127)
    {
        /*wpa_supplicant只设置ctwindow size,保存dmac,不写寄存器*/
        pst_dmac_vap->st_p2p_ops_param.uc_ct_window= pst_p2p_ops->uc_ct_window;
        return OAL_SUCC;
    }
    /*  sanity check, opps ctrl 1bit*/
    if(pst_p2p_ops->en_ops_ctrl <  2)
    {
        if((pst_p2p_ops->en_ops_ctrl ==  0)&& IS_P2P_OPPPS_ENABLED(pst_dmac_vap))
        {
            /* 恢复发送 */
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        }
        pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl = pst_p2p_ops->en_ops_ctrl;
    }
    else
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_ops:invalid ops ctrl value[%d]\r\n",
                           pst_p2p_ops->en_ops_ctrl);
        return OAL_FAIL;
    }
    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_ops:ctrl[%d] ct_window[%d] vap state[%d]\r\n",
                pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl,
                pst_dmac_vap->st_p2p_ops_param.uc_ct_window,
                pst_mac_vap->en_vap_state);
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;
    /* 设置P2P ops 寄存器 */
    hal_vap_set_ops(pst_hal_vap, pst_dmac_vap->st_p2p_ops_param.en_ops_ctrl, pst_dmac_vap->st_p2p_ops_param.uc_ct_window);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_p2p_ps_noa
 功能描述  : 设置P2P NOA 节能
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_p2p_ps_noa(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru               *pst_dmac_vap;
    mac_cfg_p2p_noa_param_stru  *pst_p2p_noa;
    oal_uint32                   ul_current_tsf_lo;
    mac_device_stru             *pst_mac_device;

    pst_p2p_noa = (mac_cfg_p2p_noa_param_stru *)puc_param;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_config_set_p2p_ps_noa::pst_mac_device[%d] is NULL!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    if(IS_P2P_GO(pst_mac_vap))
    {
#ifdef _PRE_WLAN_FEATURE_DBAC
        if (mac_is_dbac_running(pst_mac_device))
        {
            /* dbac运行中 go的noa由dbac接管 */
            return OAL_SUCC;
        }
#endif

        /*如果是GO, interval设为beacon interval*/
        pst_p2p_noa->ul_interval = pst_mac_device->ul_beacon_interval * 1024;
    }

    /* 获取dmac_vap 结构体 */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id,OAM_SF_ANY,"{dmac_config_set_p2p_ps_noa::mac_res_get_dmac_vap fail or pst_dmac_vap->pst_hal_vap NULL}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 保存参数用于encap probe rsp,beacon*/
    if (pst_p2p_noa->uc_count != 0)
	{
        pst_dmac_vap->st_p2p_noa_param.uc_count = pst_p2p_noa->uc_count;
        pst_dmac_vap->st_p2p_noa_param.ul_duration = pst_p2p_noa->ul_duration;
        pst_dmac_vap->st_p2p_noa_param.ul_interval = pst_p2p_noa->ul_interval;
        hal_vap_tsf_get_32bit(pst_dmac_vap->pst_hal_vap, &ul_current_tsf_lo);
        pst_p2p_noa->ul_start_time += ul_current_tsf_lo;
        pst_dmac_vap->st_p2p_noa_param.ul_start_time = pst_p2p_noa->ul_start_time;
    }
    else
    {
    	if(IS_P2P_NOA_ENABLED(pst_dmac_vap))
        {
            /* 恢复发送 */
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        }

        OAL_MEMZERO(&(pst_dmac_vap->st_p2p_noa_param), OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
    }
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_noa:start_time:%d, duration:%d, interval:%d, count:%d\r\n",
                    pst_dmac_vap->st_p2p_noa_param.ul_start_time,
                    pst_dmac_vap->st_p2p_noa_param.ul_duration,
                    pst_dmac_vap->st_p2p_noa_param.ul_interval,
                    pst_dmac_vap->st_p2p_noa_param.uc_count);
    /* 设置P2P noa 寄存器 */
    hal_vap_set_noa(pst_dmac_vap->pst_hal_vap,
                    pst_dmac_vap->st_p2p_noa_param.ul_start_time,
                    pst_dmac_vap->st_p2p_noa_param.ul_duration,
                    pst_dmac_vap->st_p2p_noa_param.ul_interval,
                    pst_dmac_vap->st_p2p_noa_param.uc_count);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_p2p_ps_stat
 功能描述  : 设置P2P 节能统计
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_config_set_p2p_ps_stat(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_p2p_stat_param_stru *pst_p2p_stat;
    hal_to_dmac_device_stru     *pst_hal_device;
    pst_p2p_stat = (mac_cfg_p2p_stat_param_stru *)puc_param;
    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_stat::ctrl:%d\r\n",
    //                pst_p2p_stat->uc_p2p_statistics_ctrl);
    /* 获取hal_device 结构体 */
    hal_get_hal_to_dmac_device(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, &pst_hal_device);
    if (pst_p2p_stat->uc_p2p_statistics_ctrl == 0)
    {
        /* 清除统计值 */
        hal_clear_irq_stat(pst_hal_device);
    }
    else if (pst_p2p_stat->uc_p2p_statistics_ctrl == 1)
    {
        /* 打印统计值 */
        hal_show_irq_info(pst_hal_device, 0);
    }
    else
    {
        /* 错误控制命令 */
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_set_p2p_ps_stat:: wrong p2p ps ctrl vale \r\n");
        return OAL_FAIL;
    }

    return OAL_SUCC;
}
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
/*****************************************************************************
 函 数 名  : dmac_config_set_sta_ps_mode
 功能描述  : 设置sta ps mode
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_sta_ps_mode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru                   *pst_dmac_vap;
    mac_cfg_ps_mode_param_stru      *pst_ps_mode_param;

    pst_ps_mode_param = (mac_cfg_ps_mode_param_stru *)puc_param;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_set_sta_ps_mode::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    if (pst_ps_mode_param->uc_vap_ps_mode < NUM_PS_MODE)
    {
        pst_dmac_vap->uc_cfg_pm_mode = pst_ps_mode_param->uc_vap_ps_mode;
    }
    else
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"dmac set pm mode[%d]> max mode fail",pst_ps_mode_param->uc_vap_ps_mode);
    }

    return OAL_SUCC;

}
/*****************************************************************************
 函 数 名  : dmac_set_sta_pm_on
 功能描述  : 开启sta低功耗
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月12日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_set_sta_pm_on(mac_vap_stru *pst_mac_vap, oal_uint8 uc_vap_ps_mode)
{
    dmac_vap_stru                   *pst_dmac_vap;
    mac_sta_pm_handler_stru         *pst_sta_pm_handle;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id,OAM_SF_PWR,"{dmac_set_sta_pm_on::mac_res_get_dmac_vap fail}");
        return;
    }
    pst_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    if (OAL_PTR_NULL == pst_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_set_sta_pm_on::pst_sta_pm_handle null}");
        return;
    }

    /* STA PM 的状态清理 */
    dmac_sta_initialize_psm_globals(pst_sta_pm_handle);

    /* 如果当前低功耗模式与需设置的模式一样，协议上不再重复设置低功耗 */
    if ((uc_vap_ps_mode == pst_sta_pm_handle->uc_vap_ps_mode))
    {
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_set_sta_pm_on:the same ps mode:[%d],hw_ps:[%d]}", pst_sta_pm_handle->uc_vap_ps_mode, pst_sta_pm_handle->en_hw_ps_enable);
        return;
    }

    if (uc_vap_ps_mode == NO_POWERSAVE)
    {
        pst_sta_pm_handle->uc_vap_ps_mode = uc_vap_ps_mode;
        mac_mib_set_powermanagementmode(pst_mac_vap, WLAN_MIB_PWR_MGMT_MODE_ACTIVE);
    }

    /* 确保低功耗模式和定时器同步,开低功耗必须在关联上的时候才设置模式,重启activity定时器 */
    if ((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_dmac_vap->st_vap_base_info.en_vap_state))
    {
        pst_sta_pm_handle->uc_vap_ps_mode = uc_vap_ps_mode;
        if (uc_vap_ps_mode != NO_POWERSAVE)
        {
            mac_mib_set_powermanagementmode(pst_mac_vap, WLAN_MIB_PWR_MGMT_MODE_PWRSAVE);
        }
        dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);
    }
    else
    {
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"{dmac_set_sta_pm_on::vap state:[%d],assoc aid:[%d] not start timer}",pst_dmac_vap->st_vap_base_info.en_vap_state,pst_dmac_vap->st_vap_base_info.us_sta_aid);
        return;
    }

    OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_set_sta_pm_on:ps mode:[%d],aid[%d]}", uc_vap_ps_mode,pst_dmac_vap->st_vap_base_info.us_sta_aid);
}
/*****************************************************************************
 函 数 名  : dmac_show_ps_info
 功能描述  : sta psm维测统计信息
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月16日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_PSM_DEBUG_MODE
extern  oal_uint8 g_pm_wlan_debug;
oal_uint32 dmac_show_ps_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ps_info_stru            *pst_ps_info;
    dmac_vap_stru                   *pst_dmac_vap;
    mac_sta_pm_handler_stru         *pst_sta_pm_handle;
    oal_uint8                        uc_psm_info_enable;  //开启psm的维测输出
    oal_uint8                        uc_psm_debug_mode;
    oal_uint8                        uc_doze_trans_flag;
    oal_uint32                       uiCnt;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_vap->pst_hal_device)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_show_ps_info::mac_res_get_dmac_vap fail or pst_dmac_vap->pst_hal_device NULL,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    pst_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    if (OAL_PTR_NULL == pst_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_show_ps_info::pst_sta_pm_handle null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ps_info = (mac_cfg_ps_info_stru *)puc_param;
    uc_psm_info_enable = pst_ps_info->uc_psm_info_enable;
    uc_psm_debug_mode  = pst_ps_info->uc_psm_debug_mode;


    /* 切doze的条件 */
    uc_doze_trans_flag = (pst_sta_pm_handle->en_beacon_frame_wait) | (pst_sta_pm_handle->st_null_wait.en_doze_null_wait << 1) | (pst_sta_pm_handle->en_more_data_expected << 2)
                 | (pst_sta_pm_handle->st_null_wait.en_active_null_wait << 3) | (pst_sta_pm_handle->en_send_active_null_frame_to_ap << 4);

    if (1 == uc_psm_info_enable)
    {
        for(uiCnt= 0; uiCnt < PM_MSG_COUNT; uiCnt++)
        {
            OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{pm debug msg[%d] [%d]}",uiCnt,pst_sta_pm_handle->aul_pmDebugCount[uiCnt]);
        }
    }
    /* 增加配置命令2查看低功耗关键维测 */
    else if (2 == uc_psm_info_enable)
    {
        OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id,OAM_SF_PWR,"{dmac_show_ps_info::now pm state:[%d],ps mode:[%d],don't doze reason[0x%x],aid[%d],rfpwron[%d],paldo[%d].}",6,
                     STA_GET_PM_STATE(pst_sta_pm_handle),pst_sta_pm_handle->uc_vap_ps_mode,uc_doze_trans_flag,pst_dmac_vap->st_vap_base_info.us_sta_aid,g_us_PmWifiSleepRfPwrOn,g_us_PmEnablePaldo);

        OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id,OAM_SF_PWR,"{full phy freq user[%d],psm timer:timout[%d],cnt[%d].}",pst_dmac_vap->pst_hal_device->uc_full_phy_freq_user_cnt,g_device_wlan_pm_timeout,g_pm_timer_restart_cnt,
                           pst_sta_pm_handle->uc_psm_timer_restart_cnt);

        dmac_pm_key_info_dump(pst_dmac_vap);
    }
    else
    {
        OAL_MEMZERO(&(pst_sta_pm_handle->aul_pmDebugCount),OAL_SIZEOF(pst_sta_pm_handle->aul_pmDebugCount));
        g_deepsleep_fe_awake_cnt   = 0;
        g_lightsleep_fe_awake_cnt  = 0;
    }

    if (OAL_TRUE == uc_psm_debug_mode)
    {
        g_pm_wlan_debug = 1;
    }
    else
    {
        g_pm_wlan_debug = 0;
    }

    return OAL_SUCC;
}
#endif
 /*****************************************************************************
 函 数 名  : dmac_set_psm_param
 功能描述  : staut 低功耗内外tbtt offset，listen interval设置
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_succ
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月29日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_set_psm_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ps_param_stru           *pst_ps_param;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint16                       us_beacon_timeout;
    oal_uint16                       us_tbtt_offset;
    oal_uint16                       us_ext_tbtt_offset;
	oal_uint16                       us_dtim3_on;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_set_psm_param::mac_res_get_dmac_vap fail,vap_id:%u.}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }


    pst_ps_param = (mac_cfg_ps_param_stru *)puc_param;
    us_beacon_timeout = pst_ps_param->us_beacon_timeout;
    us_tbtt_offset = pst_ps_param->us_tbtt_offset;
    us_ext_tbtt_offset = pst_ps_param->us_ext_tbtt_offset;
	us_dtim3_on        = pst_ps_param->us_dtim3_on;

	/* beacon timeout value */
	if (us_beacon_timeout != 0)
	{
		//hal_set_psm_listen_interval(pst_dmac_vap->pst_hal_vap, us_listen_interval);
		//hal_set_psm_listen_interval_count(pst_dmac_vap->pst_hal_vap, us_listen_interval);
		pst_dmac_vap->us_beacon_timeout = us_beacon_timeout;
		hal_set_beacon_timeout_val(pst_dmac_vap->pst_hal_device, us_beacon_timeout);
	}

	/* INTER TBTT OFFSET */
	if (us_tbtt_offset != 0)
	{
		pst_dmac_vap->us_in_tbtt_offset = us_tbtt_offset;
		hal_set_psm_tbtt_offset(pst_dmac_vap->pst_hal_vap, us_tbtt_offset);
	}

	/* EXT TBTT OFFSET*/
	if (us_ext_tbtt_offset != 0)
	{
		pst_dmac_vap->us_ext_tbtt_offset = us_ext_tbtt_offset;
		hal_set_psm_ext_tbtt_offset(pst_dmac_vap->pst_hal_vap, us_ext_tbtt_offset);
	}

	g_uc_max_powersave = (0==us_dtim3_on)?0:1;

	dmac_psm_update_dtime_period(pst_dmac_vap,
								(oal_uint8)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod,
								pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);

	dmac_psm_update_keepalive(pst_dmac_vap);

    return OAL_SUCC;
}

 /*****************************************************************************
 函 数 名  : dmac_psm_check_module_ctrl
 功能描述  : 低功耗使能控制公共接口中，多模块之间低功耗冲突控制的仲裁检查接口。
             按照 bit控制，mac_pm_ctrl_type_enum 模块类型分别对应于1bit。
 输入参数  : mac_vap_stru *pst_mac_vap
             mac_pm_ctrl_type_enum_uint8 pm_ctrl_type
             mac_pm_switch_enum_uint8 pm_enable
 输出参数  : oal_uint8 *puc_psm_result 输出 multi module psm 结果，是否需要执行低功耗
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月29日
    作    者   : l00350000
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_psm_check_module_ctrl(mac_vap_stru *pst_mac_vap, mac_pm_ctrl_type_enum_uint8 pm_ctrl_type, mac_pm_switch_enum_uint8 pm_enable, oal_uint8 *puc_psm_result)
{
    oal_uint32      ul_sta_pm_close_status;
    dmac_vap_stru  *pst_dmac_vap            = OAL_PTR_NULL;

    if(OAL_PTR_NULL == pst_mac_vap ||
       OAL_PTR_NULL == puc_psm_result)
    {
        OAM_ERROR_LOG2(0, OAM_SF_PWR,"{dmac_psm_check_module_ctrl::Param NULL, pst_mac_vap = 0x%X, puc_psm_result = 0x%X.}",
                         pst_mac_vap,puc_psm_result);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap    = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR,"{dmac_psm_check_module_ctrl::pst_dmac_vap is NULL.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PWR,"{dmac_psm_check_module_ctrl::module[%d],open/close[%d],last open_by_host[%d],close status[%d].}",pm_ctrl_type, pm_enable, pst_dmac_vap->uc_sta_pm_open_by_host,pst_dmac_vap->uc_sta_pm_close_status);

    ul_sta_pm_close_status = pst_dmac_vap->uc_sta_pm_close_status;

    if(MAC_STA_PM_SWITCH_ON == pm_enable)
    {
        //清空 pm_close 对应模块的 bit 位
        ul_sta_pm_close_status &= (~(oal_uint32)(1<<(oal_uint32)pm_ctrl_type));
        if(MAC_STA_PM_CTRL_TYPE_HOST == pm_ctrl_type)
        {
            pst_dmac_vap->uc_sta_pm_open_by_host = MAC_STA_PM_SWITCH_ON;
        }
    }
    else if(MAC_STA_PM_SWITCH_OFF == pm_enable)
    {
        //置 pm_close 对应模块的 bit 位
        ul_sta_pm_close_status |= (1<<(oal_uint32)pm_ctrl_type);
        if(MAC_STA_PM_CTRL_TYPE_HOST == pm_ctrl_type)
        {
            pst_dmac_vap->uc_sta_pm_open_by_host = MAC_STA_PM_SWITCH_OFF;
        }
    }
    else
    {
        //外部参数检查
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR,"{dmac_psm_check_module_ctrl::pm_enable = %d ERROR!!}",pm_enable);
    }

    pst_dmac_vap->uc_sta_pm_close_status = (oal_uint8)ul_sta_pm_close_status;

    /* 如果有模块关闭低功耗，则关闭低功耗 */
    if(0 != pst_dmac_vap->uc_sta_pm_close_status)
    {
        *puc_psm_result = MAC_STA_PM_SWITCH_OFF;
    }
    else
    {
        /* HOST 侧是否已经打开低功耗*/
        *puc_psm_result = pst_dmac_vap->uc_sta_pm_open_by_host;
    }

    return OAL_SUCC;
}

 /*****************************************************************************
  函 数 名  : dmac_set_psm_vote
  功能描述  : 提供低功耗使能控制公共接口，管理多模块之间低功耗的控制冲突
  输入参数  : mac_vap_stru *pst_mac_vap
              oal_uint8 uc_len
              oal_uint8 *puc_param : mac_cfg_ps_open_stru 结构，包括外部模块类型、低功耗开关信息。
  输出参数  : 无
  返 回 值  : oal_uint32
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2015年2月16日
     作    者   : l00280485
     修改内容   : 新生成函数

 *****************************************************************************/
 oal_uint32 dmac_config_set_sta_pm_on(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
 {
    mac_cfg_ps_open_stru            *pst_sta_pm_open = OAL_PTR_NULL;
    dmac_vap_stru                   *pst_dmac_vap = OAL_PTR_NULL;
    oal_uint8                        uc_final_open_sta_pm = 0;
    oal_uint32                       ul_ret = OAL_SUCC;
    oal_uint8                        uc_cfg_pm_mode;
    mac_device_stru                 *pst_mac_device;

    pst_dmac_vap    = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_set_sta_pm_on::pst_dmac_vap null}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
      OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_config_set_sta_pm_on::pst_mac_device null.}");

      return OAL_ERR_CODE_PTR_NULL;
    }

    pst_sta_pm_open = (mac_cfg_ps_open_stru *)puc_param;

    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR,"{dmac_config_set_sta_pm_on::vap mode is:[%d] not sta}",pst_mac_vap->en_vap_mode);
        return OAL_SUCC;
    }

    ul_ret = dmac_psm_check_module_ctrl(pst_mac_vap, pst_sta_pm_open->uc_pm_ctrl_type, pst_sta_pm_open->uc_pm_enable, &uc_final_open_sta_pm);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_sta_pm_on::dmac_psm_check_module_ctrl failed, ul_ret=%d.}", ul_ret);
        return ul_ret;
    }

    if (MAC_STA_PM_SWITCH_ON == uc_final_open_sta_pm)
    {
        uc_cfg_pm_mode = pst_dmac_vap->uc_cfg_pm_mode;

        /*保证开低功耗时的pm mode不为 NO_POWERSAVE */
        if (NO_POWERSAVE == uc_cfg_pm_mode)
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG,"{dmac_config_set_sta_pm_on::modual[%d]want to open[%d]pm,but pm mode is no powersave}",pst_sta_pm_open->uc_pm_ctrl_type,pst_sta_pm_open->uc_pm_enable);
            uc_cfg_pm_mode = MIN_FAST_PS;
        }
    }
    else
    {
        /* 关闭低功耗时立刻向平台投work票 */
        PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_WORK_PROCESS);

        /* 关闭低功耗立刻恢复前端 */
        dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);

        /* 关闭低功耗时,低功耗模式切回NO_POWERSAVE */
        uc_cfg_pm_mode = NO_POWERSAVE;

    }

    dmac_set_sta_pm_on(pst_mac_vap, uc_cfg_pm_mode);

    return OAL_SUCC;

 }


#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
/*****************************************************************************
 函 数 名  : dmac_config_set_mips
 功能描述  :
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_set_mips(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_mips_type_param_stru      *pst_mips_type_param;

    pst_mips_type_param = (oal_mips_type_param_stru *)puc_param;

    switch (pst_mips_type_param->l_mips_type)
    {
        case OAL_MIPS_TX:
        {
            if (OAL_SWITCH_ON == pst_mips_type_param->l_switch)
            {
                if (OAL_SWITCH_OFF == g_mips_tx_statistic.en_switch)
                {
                    oal_profiling_mips_tx_init();
                    oal_profiling_enable_cycles();

                    g_mips_tx_statistic.en_switch = OAL_SWITCH_ON;
                    g_mips_tx_statistic.uc_flag |= BIT0;
                }
            }
            else if (OAL_SWITCH_OFF == pst_mips_type_param->l_switch)
            {
                if (OAL_SWITCH_ON == g_mips_tx_statistic.en_switch)
                {
                    oal_profiling_disable_cycles();

                    g_mips_tx_statistic.en_switch = OAL_SWITCH_OFF;
                }
            }
        }
        break;

        case OAL_MIPS_RX:
        {
            if (OAL_SWITCH_ON == pst_mips_type_param->l_switch)
            {
                if (OAL_SWITCH_OFF == g_mips_rx_statistic.en_switch)
                {
                    oal_profiling_mips_rx_init();
                    oal_profiling_enable_cycles();

                    g_mips_rx_statistic.en_switch = OAL_SWITCH_ON;
                }
            }
            else if (OAL_SWITCH_OFF == pst_mips_type_param->l_switch)
            {
                if (OAL_SWITCH_ON == g_mips_rx_statistic.en_switch)
                {
                    oal_profiling_disable_cycles();

                    g_mips_rx_statistic.en_switch = OAL_SWITCH_OFF;
                }
            }
        }
        break;

        default:
        {
            OAL_IO_PRINT("dmac_config_set_mips: mips type is wrong!\r\n");
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_show_mips
 功能描述  :
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_show_mips(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32 l_mips_type;

    l_mips_type = *((oal_int32 *)puc_param);

    switch (l_mips_type)
    {
        case OAL_MIPS_TX:
        {
            oal_profiling_tx_mips_show();
        }
        break;

        case OAL_MIPS_RX:
        {
            oal_profiling_rx_mips_show();
        }
        break;

        default:
        {
            OAL_IO_PRINT("dmac_config_show_mips: mips type is wrong!\r\n");
        }
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_config_nss
 功能描述  : 配置user空间流信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_nss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_nss_stru  *pst_user_nss;
    mac_user_stru      *pst_mac_user;

    pst_user_nss = (mac_user_nss_stru *)puc_param;
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_user_nss->us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_spatial_stream::mac user(idx=%d) is null!", pst_user_nss->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_set_num_spatial_stream(pst_mac_user, pst_user_nss->uc_num_spatial_stream);
    mac_user_set_avail_num_spatial_stream(pst_mac_user, pst_user_nss->uc_avail_num_spatial_stream);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_opmode
 功能描述  : 配置user opmode 信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月22日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_opmode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY

    mac_user_opmode_stru  *pst_user_opmode;
    mac_user_stru         *pst_mac_user;

    pst_user_opmode = (mac_user_opmode_stru *)puc_param;
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_user_opmode->us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "dmac_config_opmode::mac user(idx=%d) is null!", pst_user_opmode->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_avail_bf_num_spatial_stream(pst_mac_user, pst_user_opmode->uc_avail_bf_num_spatial_stream);
    if (OAL_FALSE == mac_check_is_assoc_frame(pst_user_opmode->uc_frame_type))
    {
        /* 调用算法钩子函数 */
        dmac_alg_cfg_user_spatial_stream_notify(pst_mac_user);
    }

    mac_user_set_avail_num_spatial_stream(pst_mac_user, pst_user_opmode->uc_avail_num_spatial_stream);
    if (OAL_FALSE == mac_check_is_assoc_frame(pst_user_opmode->uc_frame_type))
    {
        /* 调用算法钩子函数 */;
        dmac_alg_cfg_user_spatial_stream_notify(pst_mac_user);
    }

    mac_user_set_bandwidth_info(pst_mac_user, pst_user_opmode->en_avail_bandwidth, pst_user_opmode->en_cur_bandwidth);
    if (OAL_FALSE == mac_check_is_assoc_frame(pst_user_opmode->uc_frame_type))
    {
        /* 调用算法钩子函数 */;
        dmac_alg_cfg_user_bandwidth_notify(pst_mac_vap, pst_mac_user);
    }
#endif
    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
/*****************************************************************************
 函 数 名  : dmac_config_enable_arp_offload
 功能描述  : 配置ARP offload信息
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_enable_arp_offload(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru *pst_dmac_vap  = (dmac_vap_stru *)pst_mac_vap;

    pst_dmac_vap->en_arp_offload_switch = *(oal_switch_enum_uint8 *)puc_param;
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_ip_add
 功能描述  : 增加IP地址
 输入参数  : mac_vap_stru *pst_mac_vap
             dmac_ip_addr_config_stru *pst_ip_addr_info
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月7日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ip_add(dmac_vap_stru *pst_dmac_vap, dmac_ip_addr_config_stru *pst_ip_addr_info)
{
    mac_vap_stru              *pst_mac_vap       = &pst_dmac_vap->st_vap_base_info;
    oal_uint32                 ul_loop;
    oal_bool_enum_uint8        en_comp           = OAL_FALSE;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap->pst_ip_addr_info))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_add::IP record array memory is not alloced.}");
        return OAL_FAIL;
    }

    if (DMAC_CONFIG_IPV4 == pst_ip_addr_info->en_type)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV4_ENTRIES; ul_loop++)
        {
            if ((OAL_FALSE == en_comp) && (0 == *(oal_uint32 *)(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr)))
            {
                en_comp = OAL_TRUE; /* 增加完成 */
                oal_memcopy(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV4_ADDR_SIZE);
            }
            else if (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV4_ADDR_SIZE))
            {
                if (OAL_TRUE == en_comp)
                {
                    oal_memset(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, 0, OAL_IPV4_ADDR_SIZE);
                }
                else
                {
                    en_comp = OAL_TRUE;
                }
            }
        }
    }
    else if (DMAC_CONFIG_IPV6 == pst_ip_addr_info->en_type)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV6_ENTRIES; ul_loop++)
        {
            if ((OAL_FALSE == en_comp) && OAL_IPV6_IS_UNSPECIFIED_ADDR(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))
            {
                en_comp = OAL_TRUE; /* 增加完成 */
                oal_memcopy(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV6_ADDR_SIZE);
            }
            else if (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV6_ADDR_SIZE))
            {
                if (OAL_TRUE == en_comp)
                {
                    oal_memset(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, 0, OAL_IPV6_ADDR_SIZE);
                }
                else
                {
                    en_comp = OAL_TRUE;
                }
            }
        }
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_add::IP type[%d] is wrong.}", pst_ip_addr_info->en_type);
        return OAL_FAIL;
    }

    if (OAL_FALSE == en_comp)
    {
        if (DMAC_CONFIG_IPV4 == pst_ip_addr_info->en_type)
        {
            OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_add::Add IPv4 address[%d.X.X.%d] failed, there is no empty array.}",
                           ((oal_uint8 *)&(pst_ip_addr_info->auc_ip_addr))[0],
                           ((oal_uint8 *)&(pst_ip_addr_info->auc_ip_addr))[3]);
        }
        else if (DMAC_CONFIG_IPV6 == pst_ip_addr_info->en_type)
        {
            OAM_ERROR_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_add::Add IPv6 address[%04x:%04x:XXXX:XXXX:XXXX:XXXX:%04x:%04x] failed, there is no empty array.}",
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[0]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[1]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[6]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[7]));
        }
        return OAL_FAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_ip_del
 功能描述  : 删除IP地址
 输入参数  : mac_vap_stru *pst_mac_vap
             dmac_ip_addr_config_stru *pst_ip_addr_info
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月7日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_ip_del(dmac_vap_stru *pst_dmac_vap, dmac_ip_addr_config_stru *pst_ip_addr_info)
{
    mac_vap_stru              *pst_mac_vap       = &pst_dmac_vap->st_vap_base_info;
    oal_uint32                 ul_loop;
    oal_bool_enum_uint8        en_comp           = OAL_FALSE;

    if (DMAC_CONFIG_IPV4 == pst_ip_addr_info->en_type)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV4_ENTRIES; ul_loop++)
        {
            if ((OAL_FALSE == en_comp) && (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV4_ADDR_SIZE)))
            {
                en_comp = OAL_TRUE; /* 删除完成 */
                oal_memset(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, 0, OAL_IPV4_ADDR_SIZE);
                break;
            }
        }
    }
    else if (DMAC_CONFIG_IPV6 == pst_ip_addr_info->en_type)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV6_ENTRIES; ul_loop++)
        {
            if ((OAL_FALSE == en_comp) && (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, pst_ip_addr_info->auc_ip_addr, OAL_IPV6_ADDR_SIZE)))
            {
                en_comp = OAL_TRUE; /* 删除完成 */
                oal_memset(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, 0, OAL_IPV6_ADDR_SIZE);
                break;
            }
        }
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_del::IP type[%d] is wrong.}", pst_ip_addr_info->en_type);
        return OAL_FAIL;
    }

    if (OAL_FALSE == en_comp)
    {
        if (DMAC_CONFIG_IPV4 == pst_ip_addr_info->en_type)
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_del::Delete IPv4 address[%d.X.X.%d] failed, there is not the IP address.}",
                           ((oal_uint8 *)&(pst_ip_addr_info->auc_ip_addr))[0],
                           ((oal_uint8 *)&(pst_ip_addr_info->auc_ip_addr))[3]);
        }
        else if (DMAC_CONFIG_IPV6 == pst_ip_addr_info->en_type)
        {
            OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_ip_del::Delete IPv6 address[%04x:%04x:XXXX:XXXX:XXXX:XXXX:%04x:%04x] failed, there is not the IP address.}",
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[0]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[1]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[6]),
                           OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_ip_addr_info->auc_ip_addr))[7]));
        }
        return OAL_FAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_ip_addr
 功能描述  : 配置IP地址信息
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_ip_addr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru             *pst_dmac_vap      = (dmac_vap_stru *)pst_mac_vap;
    dmac_ip_addr_config_stru  *pst_ip_addr_info  = (dmac_ip_addr_config_stru *)puc_param;

    switch (pst_ip_addr_info->en_oper)
    {
        case DMAC_IP_ADDR_ADD:
        {
            return dmac_config_ip_add(pst_dmac_vap, pst_ip_addr_info);
        }

        case DMAC_IP_ADDR_DEL:
        {
            return dmac_config_ip_del(pst_dmac_vap, pst_ip_addr_info);
        }

        default:
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_set_ip_addr::IP operation[%d] is wrong.}", pst_ip_addr_info->en_oper);
            break;
        }
    }
    return OAL_FAIL;
}

/*****************************************************************************
 函 数 名  : dmac_config_show_arpoffload_info
 功能描述  : 查看Device侧ARPOFFLOAD维测信息
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : w00316376
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_show_arpoffload_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_arpoffload_info_stru    *pst_ps_info;
    mac_device_stru                 *pst_mac_dev;
    dmac_vap_stru                   *pst_dmac_vap;
    oal_uint8                        uc_show_ip_addr;
    oal_uint8                        uc_show_arpoffload_info;
    oal_uint32                       ul_loop;

    pst_mac_dev  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    pst_ps_info                 = (mac_cfg_arpoffload_info_stru *)puc_param;
    uc_show_ip_addr             = pst_ps_info->uc_show_ip_addr;
    uc_show_arpoffload_info     = pst_ps_info->uc_show_arpoffload_info;
    if ((OAL_PTR_NULL == pst_mac_dev) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_ps_info))
    {
        OAM_ERROR_LOG3(0, OAM_SF_CFG, "{dmac_config_show_arpoffload_info:: pointer is null,pst_mac_de[0x%x],vpst_mac_vap[0x%x],puc_param[0x%x]",pst_mac_dev,pst_dmac_vap,pst_ps_info);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (1 == uc_show_ip_addr)
    {
        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV4_ENTRIES; ul_loop++)
        {
            OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_show_ip_addr::IPv4 index[%d]: %d.X.X.%d.}",
                             ul_loop,
                             pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr[0],
                             pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr[3]);
        }

        for (ul_loop = 0; ul_loop < DMAC_MAX_IPV6_ENTRIES; ul_loop++)
        {
            OAM_WARNING_LOG_ALTER(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_show_ip_addr::IPv6 index[%d]: %04x:%04x:XXXX:XXXX:XXXX:XXXX:%04x:%04x.}",
                                  5,
                                  ul_loop,
                                  OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))[0]),
                                  OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))[1]),
                                  OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))[6]),
                                  OAL_NET2HOST_SHORT(((oal_uint16 *)&(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))[7]));
        }
    }

    if (1 == uc_show_arpoffload_info)
    {
        OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"suspend state:[%d],arpofflad drop frame:[%d],send arp rsp:[%d]",pst_mac_dev->uc_in_suspend,g_ul_arpoffload_drop_frame,g_ul_arpoffload_send_arprsp);
    }
    /* 统计清零 */
    else if (0 == uc_show_arpoffload_info)
    {
        g_ul_arpoffload_drop_frame  = 0;
        g_ul_arpoffload_send_arprsp = 0;
    }
    return OAL_SUCC;
}
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM

/*****************************************************************************
 函 数 名  : dmac_config_roam_enable
 功能描述  : 进入/退出漫游模式
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_roam_enable(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8                       uc_roaming_mode;
    mac_device_stru                *pst_mac_device;
    mac_user_stru                  *pst_mac_user;


    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_config_roam_enable::param null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_roaming_mode  = (oal_uint8)*puc_param;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if ((uc_roaming_mode == 1) && (pst_mac_vap->en_vap_state == MAC_VAP_STATE_UP))
    {
        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_mac_user)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY,
                           "{dmac_config_roam_enable::pst_mac_user[%d] null.}", pst_mac_vap->uc_assoc_vap_id);
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* 删除tid队列中的所有信息 */
        dmac_tid_clear(pst_mac_user, pst_mac_device);

        /* 漫游过程中可能发生了睡眠，增加维测，漫游前平台睡眠计数 */
        PM_WLAN_DumpSleepCnt();

        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_enable:: [MAC_VAP_STATE_UP]->[MAC_VAP_STATE_ROAMING]}");
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_ROAMING;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        dmac_btcoex_wlan_priority_set(pst_mac_device, 1, BTCOEX_PRIO_TIMEOUT_100MS);
#endif //_PRE_WLAN_FEATURE_BTCOEX
    }
    else if ((uc_roaming_mode == 0) && (pst_mac_vap->en_vap_state == MAC_VAP_STATE_ROAMING))
    {
        /* 漫游过程中可能发生了睡眠，增加维测，漫游后平台睡眠计数 */
        PM_WLAN_DumpSleepCnt();

        /* 漫游结束后，刷掉occupied_period以保证BT竞争到 */
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        hal_set_btcoex_occupied_period(0);
        dmac_btcoex_wlan_priority_set(pst_mac_device, 0, 0);
#endif //_PRE_WLAN_FEATURE_BTCOEX

        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_enable:: [MAC_VAP_STATE_ROAMING]->[MAC_VAP_STATE_UP]}");
        pst_mac_vap->en_vap_state = MAC_VAP_STATE_UP;
    }
    else
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_enable::unexpect state[%d] or mode[%d]}",
                       pst_mac_vap->en_vap_state, uc_roaming_mode);
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_roam_trigger
 功能描述  : 进入/退出漫游模式
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月17日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_roam_trigger(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_roam_trigger_stru   *pst_roam_trigger;
    dmac_vap_stru           *pst_dmac_vap;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{dmac_config_set_roam_trigger::param null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_roam_trigger  = (mac_roam_trigger_stru *)puc_param;
    pst_dmac_vap      = (dmac_vap_stru *)pst_mac_vap;

    pst_dmac_vap->st_roam_trigger.c_trigger_2G = pst_roam_trigger->c_trigger_2G;
    pst_dmac_vap->st_roam_trigger.c_trigger_5G = pst_roam_trigger->c_trigger_5G;

    /* 设置门限时，reset统计值，重新设置门限后，可以马上触发一次漫游 */
    pst_dmac_vap->st_roam_trigger.ul_cnt        = 0;
    pst_dmac_vap->st_roam_trigger.ul_time_stamp = 0;

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ROAM, "{dmac_config_set_roam_trigger, trigger[%d, %d]}",
                     pst_roam_trigger->c_trigger_2G, pst_roam_trigger->c_trigger_5G);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_roam_hmac_sync_dmac
 功能描述  : 漫游模式下更新 hmac info 到 dmac
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月25日
    作    者   : l00350000
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_roam_hmac_sync_dmac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_user_stru                   *pst_mac_user;
    mac_h2d_roam_sync_stru          *pst_sync_param = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_config_roam_hmac_sync_dmac::param null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        /* 漫游中会遇到 kick user 的情况，降低 log level*/
        OAM_WARNING_LOG1(0, OAM_SF_ANY,
                       "{dmac_config_roam_hmac_sync_dmac::pst_mac_user[%d] null.}", pst_mac_vap->uc_assoc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_sync_param = (mac_h2d_roam_sync_stru *)puc_param;

    if(OAL_TRUE == pst_sync_param->ul_back_to_old)
    {
        /* 恢复原来bss相关信息 */
        pst_mac_vap->us_sta_aid = pst_sync_param->us_sta_aid;
        oal_memcopy(&(pst_mac_vap->st_channel), &pst_sync_param->st_channel, OAL_SIZEOF(mac_channel_stru));
        oal_memcopy(&(pst_mac_user->st_cap_info), &pst_sync_param->st_cap_info, OAL_SIZEOF(mac_user_cap_info_stru));
        oal_memcopy(&(pst_mac_user->st_key_info), &pst_sync_param->st_key_info, OAL_SIZEOF(mac_key_mgmt_stru));
        oal_memcopy(&(pst_mac_user->st_user_tx_info),&pst_sync_param->st_user_tx_info, OAL_SIZEOF(mac_user_tx_param_stru));
    }

    /* 设置用户8021x端口合法性的状态为合法 */
    mac_user_set_port(pst_mac_user, OAL_TRUE);

    OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_hmac_sync_dmac:: Sync Done!!}");

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_roam_notify_state
 功能描述  : 通知当前wpas关联状态进展
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 uc_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月18日
    作    者   : l00350000
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_roam_notify_state(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru   *pst_dmac_vap           = OAL_PTR_NULL;
    oal_uint32       ul_ip_addr_obtained    = OAL_FALSE;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_config_roam_notify_state::param null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ip_addr_obtained     = *(oal_uint32 *)puc_param;
    pst_dmac_vap            = (dmac_vap_stru *)pst_mac_vap;

    pst_dmac_vap->st_roam_trigger.ul_ip_addr_obtained = ul_ip_addr_obtained;
    pst_dmac_vap->st_roam_trigger.ul_ip_obtain_stamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_config_roam_notify_state:: ul_ip_addr_obtained = %d!!}",ul_ip_addr_obtained);

    return OAL_SUCC;
}

#endif  //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 函 数 名  : dmac_config_enable_2040bss
 功能描述  : 20/40 bss检测开关设置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月31日
    作    者   : w00249967
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_config_enable_2040bss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru           *pst_mac_device;
    oal_bool_enum_uint8        en_2040bss_switch;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_enable_2040bss:: pointer is null,pst_mac_vap[%d], puc_param[%d] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_enable_2040bss::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    en_2040bss_switch = (*puc_param == 0) ? OAL_FALSE : OAL_TRUE;
    mac_set_2040bss_switch(pst_mac_device, en_2040bss_switch);

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_enable_2040bss::set 2040bss switch[%d].}", en_2040bss_switch);

    return OAL_SUCC;
}
#endif /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_config_suspend_action_sync
 功能描述  : 亮暗屏状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月15日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_suspend_action_sync(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru             *pst_mac_device;
    mac_cfg_suspend_stru        *pst_suspend;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_suspend_action_sync:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_suspend_action_sync::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_suspend = (mac_cfg_suspend_stru *)puc_param;

    pst_mac_device->uc_in_suspend = pst_suspend->uc_in_suspend; //亮暗屏状态

    pst_mac_device->uc_arpoffload_switch = pst_suspend->uc_arpoffload_switch; //arp 开关

    /*暗屏实施dtim2策略*/
    dmac_psm_max_powersave_enable(pst_mac_device);

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
oal_uint32 dmac_pkt_mem_opt_stat_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    oal_bool_enum_uint8      en_dscr_opt_state;
    mac_device_stru         *pst_mac_device;
    hal_to_dmac_device_stru *pst_hal_device;

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);

    en_dscr_opt_state = pst_event->auc_event_data[0];

    pst_mac_device = (mac_device_stru*)mac_res_get_dev(pst_event_hdr->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{dmac_dscr_opt_stat_event_process::mac device is null.}");
        return OAL_FAIL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    if(OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{dmac_dscr_opt_stat_event_process::hal device is null.}");
        return OAL_FAIL;
    }

    if(en_dscr_opt_state)
    {
        pst_hal_device->ul_rx_normal_dscr_cnt = HAL_NORMAL_RX_MAX_RX_OPT_BUFFS;
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dscr_opt_stat_event_process::rx dscr opt change to %d. }", pst_hal_device->ul_rx_normal_dscr_cnt);
    }
    else
    {
        oal_irq_disable();
        hal_disable_machw_phy_and_pa(pst_hal_device);
        pst_hal_device->ul_rx_normal_dscr_cnt = HAL_NORMAL_RX_MAX_BUFFS;
        hal_rx_dscr_opt_reset_normal(pst_hal_device);
        hal_enable_machw_phy_and_pa(pst_hal_device);
        oal_irq_enable();
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dscr_opt_stat_event_process::rx dscr reset to %d. }", pst_hal_device->ul_rx_normal_dscr_cnt);
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/*****************************************************************************
 函 数 名  : dmac_config_set_device_cap_rely_on_customize
 功能描述  : 根据定制化5g能力更新device的频带能力和带宽能力
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_config_set_device_cap_rely_on_customize(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru              *pst_mac_device;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_config_set_device_cap_rely_on_customize:: pointer is null,pst_mac_vap[0x%x] .}", pst_mac_vap);
        return;
    }
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "dmac_config_set_device_cap_rely_on_customize: mac_device is null.device_id[%d]", pst_mac_vap->uc_device_id);
        return;
    }
    /* 根据定制化5g能力更新device的频带能力和带宽能力 */
    if (!g_st_customize.st_cali.uc_band_5g_enable)
    {
        pst_mac_device->en_bandwidth_cap = WLAN_BW_CAP_40M;
        pst_mac_device->en_band_cap = WLAN_BAND_CAP_2G;
    }
}
/*****************************************************************************
 函 数 名  : dmac_config_set_linkloss_threshold
 功能描述  : linkloss threshold
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_linkloss_threshold(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_linkloss_threshold*     pst_threshold;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_linkloss_threshold:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_threshold = (mac_cfg_linkloss_threshold *)puc_param;
    g_st_beacon_linkloss.us_linkloss_threshold_wlan_near = pst_threshold->uc_linkloss_threshold_wlan_near;
    g_st_beacon_linkloss.us_linkloss_threshold_wlan_far  = pst_threshold->uc_linkloss_threshold_wlan_far;
    g_st_beacon_linkloss.us_linkloss_threshold_p2p       = pst_threshold->uc_linkloss_threshold_p2p;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_all_log_level
 功能描述  : device all vap log level
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_all_log_level(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32      ul_ret = 0;
    oal_uint8       uc_vap_idx;
    oal_uint8       uc_level;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_all_log_level:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }
    uc_level = (oal_uint8)(*puc_param);

    for (uc_vap_idx = 0; uc_vap_idx < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vap_idx++)
    {
        ul_ret += oam_log_set_vap_level(uc_vap_idx, uc_level);

        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_d2h_hcc_assemble_cnt
 功能描述  : d2h sdio
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_d2h_hcc_assemble_cnt(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32      ul_val;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_d2h_hcc_assemble_cnt:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_val = (oal_uint32)(*puc_param);
    g_d2h_hcc_assemble_count = (1 <= ul_val && HISDIO_DEV2HOST_SCATT_MAX >= ul_val) ? ul_val : g_d2h_hcc_assemble_count;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_chn_est_ctrl
 功能描述  : WIFI PHY寄存器，仅在针对Golden AP时使用“evb-1102初始值”和“mt7双4g-1102初始值”，其他时候使用“fpga-1102初始值”
             evb-1102初始值:        0x3C192240
             mt7双4g-1102初始值:    0x3C193240
             fpga-1102初始值:       0x3C19A243
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_chn_est_ctrl(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_d2h_hcc_assemble_cnt:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    g_st_customize.ul_chn_est_ctrl = *(oal_uint32*)puc_param;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_power_ref
 功能描述  : DTS2015091905865 power_ref 定制化
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_power_ref(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_power_ref*      pst_mac_cfg_power_ref;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_d2h_hcc_assemble_cnt:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_cfg_power_ref = (mac_cfg_power_ref *)puc_param;
    g_ul_phy_power0_ref_5g = pst_mac_cfg_power_ref->ul_power_ref_5g;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_pm_cfg_param
 功能描述  : 时钟定制化
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_pm_cfg_param(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    st_pm_cfg_param*        pst_pm_cfg_param;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_d2h_hcc_assemble_cnt:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_pm_cfg_param = (st_pm_cfg_param *)puc_param;

    g_st_customize.st_pm.ul_rtc_clk_freq = pst_pm_cfg_param->ul_rtc_clk_freq;
    g_st_customize.st_pm.uc_clk_type = pst_pm_cfg_param->uc_clk_type;

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_cus_rf
 功能描述  : RF定制化
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_cus_rf(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32      ul_offset = 0;
    oal_uint8       uc_agc_ref;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_cus_rf:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(&g_st_customize.st_rf, puc_param, OAL_SIZEOF(g_st_customize.st_rf));
    ul_offset += OAL_SIZEOF(g_st_customize.st_rf);
    oal_memcopy(&g_st_customize.st_ratio_temp_pwr_comp, puc_param + ul_offset, OAL_SIZEOF(g_st_customize.st_ratio_temp_pwr_comp));

    uc_agc_ref = (oal_uint8)(g_st_customize.st_rf.ac_gain_db_2g[0].c_rf_gain_db_2g_mult4 + ((DMAC_RX_LPF_GAIN + DMAC_DBM_CH + DMAC_SINGLE_DOUBLE_SWITCH_GAIN) << 2));

    g_ul_phy_power0_ref_2g = OAL_JOIN_WORD32(uc_agc_ref, uc_agc_ref - DMAC_RSSI_REF_DIFFERENCE, uc_agc_ref - DMAC_RADAR_REF_DIFFERENCE, 0);

    OAM_WARNING_LOG1(0, 0, "g_ul_phy_power0_ref_2g 0x%x", g_ul_phy_power0_ref_2g);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_set_cus_dts_cali
 功能描述  : dts 校准参数
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_cus_dts_cali(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1151)
    mac_device_stru              *pst_mac_device;
    hal_device_stru              *pst_device;
#endif
    oal_uint32                  ul_offset = 0;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_cus_dts_cali:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(&g_st_customize.st_cali, puc_param, OAL_SIZEOF(g_st_customize.st_cali));
    ul_offset += OAL_SIZEOF(g_st_customize.st_cali);
    /* 根据定制化5g能力更新device的频带能力和带宽能力 */
    dmac_config_set_device_cap_rely_on_customize(pst_mac_vap);
    oal_memcopy(&g_st_customize.ast_band_edge_limit, puc_param + ul_offset, OAL_SIZEOF(g_st_customize.ast_band_edge_limit));
    ul_offset += OAL_SIZEOF(g_st_customize.ast_band_edge_limit);
    oal_memcopy(&g_st_customize.st_rf_reg, puc_param + ul_offset, OAL_SIZEOF(g_st_customize.st_rf_reg));
    ul_offset += OAL_SIZEOF(g_st_customize.st_rf_reg);

#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1151)
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "dmac_config_set_cus_dts_cali: mac_device is null.device_id[%d]", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = (hal_device_stru *)pst_mac_device->pst_device_stru;
    /* 停止PA和PHY的工作 */
    hal_disable_machw_phy_and_pa(&pst_device->st_hal_device_base);
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)

    /* 初始化PHY */
    //hal_initialize_phy(&pst_device->st_hal_device_base);
    hal_set_rf_custom_reg(&pst_device->st_hal_device_base);
#endif
    /* FPGA zhangyu Debug */
    /* 初始化RF系统 */
    hal_initialize_rf_sys(&pst_device->st_hal_device_base);

#endif
    SDIO_SendMsgSync(D2H_MSG_WLAN_READY);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_update_rate_pow_table
 功能描述  : 更新各速率下最大允许发射功率
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :
 定制化ast_nvram_params表与各协议速率对应关系:

    24G_11b 1M_2M           ast_nvram_params[0].uc_max_txpower
    24G_11b 5.5M_11M        ast_nvram_params[1].uc_max_txpower
    24G_11g 6M_9M           ast_nvram_params[2].uc_max_txpower
    24G_11g 12M_18M         ast_nvram_params[3].uc_max_txpower
    24G_11g 24M_36M         ast_nvram_params[4].uc_max_txpower
    24G_11g 48M             ast_nvram_params[5].uc_max_txpower
    24G_11g 54M             ast_nvram_params[6].uc_max_txpower
    24G_HT20_VHT20 MCS0_1   ast_nvram_params[7].uc_max_txpower
    24G_HT20_VHT20 MCS2_3   ast_nvram_params[8].uc_max_txpower
    24G_HT20_VHT20 MCS4_5   ast_nvram_params[9].uc_max_txpower
    24G_HT20_VHT20 MCS6     ast_nvram_params[10].uc_max_txpower
    24G_HT20_VHT20 MCS7     ast_nvram_params[11].uc_max_txpower
    24G_VHT20 MCS8          ast_nvram_params[12].uc_max_txpower
    24G_HT40_VHT40 MCS0_1   ast_nvram_params[13].uc_max_txpower
    24G_HT40_VHT40 MCS2_3   ast_nvram_params[14].uc_max_txpower
    24G_HT40_VHT40 MCS4_5   ast_nvram_params[15].uc_max_txpower
    24G_HT40_VHT40 MCS6     ast_nvram_params[16].uc_max_txpower
    24G_HT40_VHT40 MCS7     ast_nvram_params[17].uc_max_txpower
    24G_VHT40 MCS8          ast_nvram_params[18].uc_max_txpower
    24G_VHT40 MCS9          ast_nvram_params[19].uc_max_txpower
    24G_HT40 MCS32          ast_nvram_params[20].uc_max_txpower
    5G_11a 6M_9M            ast_nvram_params[21].uc_max_txpower
    5G_11a 12M_18M          ast_nvram_params[22].uc_max_txpower
    5G_11a 24M_36M          ast_nvram_params[23].uc_max_txpower
    5G_11a 48M              ast_nvram_params[24].uc_max_txpower
    5G_11a 54M              ast_nvram_params[25].uc_max_txpower
    5G_HT20_VHT20 MCS0_1    ast_nvram_params[26].uc_max_txpower
    5G_HT20_VHT20 MCS2_3    ast_nvram_params[27].uc_max_txpower
    5G_HT20_VHT20 MCS4_5    ast_nvram_params[28].uc_max_txpower
    5G_HT20_VHT20 MCS6      ast_nvram_params[29].uc_max_txpower
    5G_HT20_VHT20 MCS7      ast_nvram_params[30].uc_max_txpower
    5G_VHT20 MCS8           ast_nvram_params[31].uc_max_txpower
    5G_HT40_VHT40 MCS0_1    ast_nvram_params[32].uc_max_txpower
    5G_HT40_VHT40 MCS2_3    ast_nvram_params[33].uc_max_txpower
    5G_HT40_VHT40 MCS4_5    ast_nvram_params[34].uc_max_txpower
    5G_HT40_VHT40 MCS6      ast_nvram_params[35].uc_max_txpower
    5G_HT40_VHT40 MCS7      ast_nvram_params[36].uc_max_txpower
    5G_VHT40 MCS8_9         ast_nvram_params[37].uc_max_txpower
    5G_HT40 MCS32           ast_nvram_params[38].uc_max_txpower
    5G_VHT80 MCS0_1         ast_nvram_params[39].uc_max_txpower
    5G_VHT80 MCS2_3         ast_nvram_params[40].uc_max_txpower
    5G_VHT80 MCS4_5         ast_nvram_params[41].uc_max_txpower
    5G_VHT80 MCS6           ast_nvram_params[42].uc_max_txpower
    5G_VHT80 MCS7           ast_nvram_params[43].uc_max_txpower
    5G_VHT80 MCS8_9         ast_nvram_params[44].uc_max_txpower

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_config_update_rate_pow_table(oal_void)
{
    hal_cfg_customize_nvram_params_stru* past_src = g_st_customize.ast_nvram_params;

    /* update 24g:pauc_dst[][WLAN_BAND_2G] */
    /*11b 0~3*/
    /*    1 Mb */   g_auc_rate_pow_table_margin[0][0] = past_src[0].uc_max_txpower;
    /*    2 Mb */   g_auc_rate_pow_table_margin[1][0] = past_src[0].uc_max_txpower;
    /*  5.5 Mb */   g_auc_rate_pow_table_margin[2][0] = past_src[1].uc_max_txpower;
    /*   11 Mb */   g_auc_rate_pow_table_margin[3][0] = past_src[1].uc_max_txpower;

    /*11g 4~11*/
    /*    6 Mb */   g_auc_rate_pow_table_margin[4][0] = past_src[2].uc_max_txpower;
    /*    9 Mb */   g_auc_rate_pow_table_margin[5][0] = past_src[2].uc_max_txpower;
    /*   12 Mb */   g_auc_rate_pow_table_margin[6][0] = past_src[3].uc_max_txpower;
    /*   18 Mb */   g_auc_rate_pow_table_margin[7][0] = past_src[3].uc_max_txpower;
    /*   24 Mb */   g_auc_rate_pow_table_margin[8][0] = past_src[4].uc_max_txpower;
    /*   36 Mb */   g_auc_rate_pow_table_margin[9][0] = past_src[4].uc_max_txpower;
    /*   48 Mb */   g_auc_rate_pow_table_margin[10][0] = past_src[5].uc_max_txpower;
    /*   54 Mb */   g_auc_rate_pow_table_margin[11][0] = past_src[6].uc_max_txpower;

    /*11n&11ac20M 12~20*/
    /*  6.5 Mb */   g_auc_rate_pow_table_margin[12][0] = past_src[7].uc_max_txpower;
    /*   13 Mb */   g_auc_rate_pow_table_margin[13][0] = past_src[7].uc_max_txpower;
    /* 19.5 Mb */   g_auc_rate_pow_table_margin[14][0] = past_src[8].uc_max_txpower;
    /*   26 Mb */   g_auc_rate_pow_table_margin[15][0] = past_src[8].uc_max_txpower;
    /*   39 Mb */   g_auc_rate_pow_table_margin[16][0] = past_src[9].uc_max_txpower;
    /*   52 Mb */   g_auc_rate_pow_table_margin[17][0] = past_src[9].uc_max_txpower;
    /* 58.5 Mb */   g_auc_rate_pow_table_margin[18][0] = past_src[10].uc_max_txpower;
    /*   65 Mb */   g_auc_rate_pow_table_margin[19][0] = past_src[11].uc_max_txpower;

    /*   mcs8 */    g_auc_rate_pow_table_margin[20][0] = past_src[12].uc_max_txpower;

    /*11n&11ac40M 21~30*/
    /* 13.5 Mb */   g_auc_rate_pow_table_margin[21][0] = past_src[13].uc_max_txpower;
    /*   27 Mb */   g_auc_rate_pow_table_margin[22][0] = past_src[13].uc_max_txpower;
    /* 40.5 Mb */   g_auc_rate_pow_table_margin[23][0] = past_src[14].uc_max_txpower;
    /*   54 Mb */   g_auc_rate_pow_table_margin[24][0] = past_src[14].uc_max_txpower;
    /*   81 Mb */   g_auc_rate_pow_table_margin[25][0] = past_src[15].uc_max_txpower;
    /*  108 Mb */   g_auc_rate_pow_table_margin[26][0] = past_src[15].uc_max_txpower;
    /*121.5 Mb */   g_auc_rate_pow_table_margin[27][0] = past_src[16].uc_max_txpower;
    /*  135 Mb */   g_auc_rate_pow_table_margin[28][0] = past_src[17].uc_max_txpower;
    /*  162 Mb */   g_auc_rate_pow_table_margin[29][0] = past_src[18].uc_max_txpower;
    /*  180 Mb */   g_auc_rate_pow_table_margin[30][0] = past_src[19].uc_max_txpower;

    /*  MCS32  31*/
    /*    6 Mb */   g_auc_rate_pow_table_margin[31][0] = past_src[20].uc_max_txpower;

    /* update 5g:pauc_dst[][WLAN_BAND_5G] */
    /*11g 4~11*/
    /*    6 Mb */   g_auc_rate_pow_table_margin[4][1] = past_src[21].uc_max_txpower;
    /*    9 Mb */   g_auc_rate_pow_table_margin[5][1] = past_src[21].uc_max_txpower;
    /*   12 Mb */   g_auc_rate_pow_table_margin[6][1] = past_src[22].uc_max_txpower;
    /*   18 Mb */   g_auc_rate_pow_table_margin[7][1] = past_src[22].uc_max_txpower;
    /*   24 Mb */   g_auc_rate_pow_table_margin[8][1] = past_src[23].uc_max_txpower;
    /*   36 Mb */   g_auc_rate_pow_table_margin[9][1] = past_src[23].uc_max_txpower;
    /*   48 Mb */   g_auc_rate_pow_table_margin[10][1] = past_src[24].uc_max_txpower;
    /*   54 Mb */   g_auc_rate_pow_table_margin[11][1] = past_src[25].uc_max_txpower;

    /*11n&11ac20M 12~20*/
    /*  6.5 Mb */   g_auc_rate_pow_table_margin[12][1] = past_src[26].uc_max_txpower;
    /*   13 Mb */   g_auc_rate_pow_table_margin[13][1] = past_src[26].uc_max_txpower;
    /* 19.5 Mb */   g_auc_rate_pow_table_margin[14][1] = past_src[27].uc_max_txpower;
    /*   26 Mb */   g_auc_rate_pow_table_margin[15][1] = past_src[27].uc_max_txpower;
    /*   39 Mb */   g_auc_rate_pow_table_margin[16][1] = past_src[28].uc_max_txpower;
    /*   52 Mb */   g_auc_rate_pow_table_margin[17][1] = past_src[28].uc_max_txpower;
    /* 58.5 Mb */   g_auc_rate_pow_table_margin[18][1] = past_src[29].uc_max_txpower;
    /*   65 Mb */   g_auc_rate_pow_table_margin[19][1] = past_src[30].uc_max_txpower;

    /*   mcs8 */    g_auc_rate_pow_table_margin[20][1] = past_src[31].uc_max_txpower;

    /*11n&11ac40M 21~30*/
    /* 13.5 Mb */   g_auc_rate_pow_table_margin[21][1] = past_src[32].uc_max_txpower;
    /*   27 Mb */   g_auc_rate_pow_table_margin[22][1] = past_src[32].uc_max_txpower;
    /* 40.5 Mb */   g_auc_rate_pow_table_margin[23][1] = past_src[33].uc_max_txpower;
    /*   54 Mb */   g_auc_rate_pow_table_margin[24][1] = past_src[33].uc_max_txpower;
    /*   81 Mb */   g_auc_rate_pow_table_margin[25][1] = past_src[34].uc_max_txpower;
    /*  108 Mb */   g_auc_rate_pow_table_margin[26][1] = past_src[34].uc_max_txpower;
    /*121.5 Mb */   g_auc_rate_pow_table_margin[27][1] = past_src[35].uc_max_txpower;
    /*  135 Mb */   g_auc_rate_pow_table_margin[28][1] = past_src[36].uc_max_txpower;
    /*  162 Mb */   g_auc_rate_pow_table_margin[29][1] = past_src[37].uc_max_txpower;
    /*  180 Mb */   g_auc_rate_pow_table_margin[30][1] = past_src[37].uc_max_txpower;

    /*  MCS32  31*/
    /*    6 Mb */   g_auc_rate_pow_table_margin[31][1] = past_src[38].uc_max_txpower;

    /*11ac80M  32~41*/
    /* 29.3 Mb */   g_auc_rate_pow_table_margin[32][1] = past_src[39].uc_max_txpower;
    /* 58.5 Mb */   g_auc_rate_pow_table_margin[33][1] = past_src[39].uc_max_txpower;
    /* 87.8 Mb */   g_auc_rate_pow_table_margin[34][1] = past_src[40].uc_max_txpower;
    /*  117 Mb */   g_auc_rate_pow_table_margin[35][1] = past_src[40].uc_max_txpower;
    /*175.5 Mb */   g_auc_rate_pow_table_margin[36][1] = past_src[41].uc_max_txpower;
    /*  234 Mb */   g_auc_rate_pow_table_margin[37][1] = past_src[41].uc_max_txpower;
    /*263.3 Mb */   g_auc_rate_pow_table_margin[38][1] = past_src[42].uc_max_txpower;
    /*292.5 Mb */   g_auc_rate_pow_table_margin[39][1] = past_src[43].uc_max_txpower;
    /*  351 Mb */   g_auc_rate_pow_table_margin[40][1] = past_src[44].uc_max_txpower;
    /*  390 Mb */   g_auc_rate_pow_table_margin[41][1] = past_src[44].uc_max_txpower;
}
/*****************************************************************************
 函 数 名  : dmac_config_update_scaling_reg
 功能描述  : 更新各速率下的scaling寄存器
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :
 定制化ast_nvram_params表与各协议速率下dbb scaling寄存器对应关系:

    24G_11b 1_2M_gain           ast_nvram_params[0].uc_dbb_scale
    24G_11b 5.5_11M_gain        ast_nvram_params[1].uc_dbb_scale
    24G_11g 6M_9M_gain          ast_nvram_params[2].uc_dbb_scale
    24G_11g 12M_18M_gain        ast_nvram_params[3].uc_dbb_scale
    24G_11g 24M_36M_gain        ast_nvram_params[4].uc_dbb_scale
    24G_11g 48M_gain            ast_nvram_params[5].uc_dbb_scale
    24G_11g 54M_gain            ast_nvram_params[6].uc_dbb_scale
    24G_HT20 MCS0_1_gain        ast_nvram_params[7].uc_dbb_scale
    24G_HT20 MCS2_3_gain        ast_nvram_params[8].uc_dbb_scale
    24G_HT20 MCS4_5_gain        ast_nvram_params[9].uc_dbb_scale
    24G_HT20 MCS6_gain          ast_nvram_params[10].uc_dbb_scale
    24G_HT20 MCS7_gain          ast_nvram_params[11].uc_dbb_scale
    24G_HT40 MCS0_1_gain        ast_nvram_params[13].uc_dbb_scale
    24G_HT40 MCS2_3_gain        ast_nvram_params[14].uc_dbb_scale
    24G_HT40 MCS4_5_gain        ast_nvram_params[15].uc_dbb_scale
    24G_HT40 MCS6_gain          ast_nvram_params[16].uc_dbb_scale
    24G_HT40 MCS7_gain          ast_nvram_params[17].uc_dbb_scale
    24G_HT40 MCS32_gain         ast_nvram_params[20].uc_dbb_scale
    5G_11a 6M_9M_gain           ast_nvram_params[21].uc_dbb_scale
    5G_11a 12M_18M_gain         ast_nvram_params[22].uc_dbb_scale
    5G_11a 24M_36M_gain         ast_nvram_params[23].uc_dbb_scale
    5G_11a 48M_gain             ast_nvram_params[24].uc_dbb_scale
    5G_11a 54M_gain             ast_nvram_params[25].uc_dbb_scale
    5G_HT20_VHT20 MCS0_1_gain   ast_nvram_params[26].uc_dbb_scale
    5G_HT20_VHT20 MCS2_3_gain   ast_nvram_params[27].uc_dbb_scale
    5G_HT20_VHT20 MCS4_5_gain   ast_nvram_params[28].uc_dbb_scale
    5G_HT20_VHT20 MCS6_gain     ast_nvram_params[29].uc_dbb_scale
    5G_HT20_VHT20 MCS7_gain     ast_nvram_params[30].uc_dbb_scale
    5G_HT20_VHT20 MCS8_gain     ast_nvram_params[31].uc_dbb_scale
    5G_HT40_VHT40 MCS0_1_gain   ast_nvram_params[32].uc_dbb_scale
    5G_HT40_VHT40 MCS2_3_gain   ast_nvram_params[33].uc_dbb_scale
    5G_HT40_VHT40 MCS4_5_gain   ast_nvram_params[34].uc_dbb_scale
    5G_HT40_VHT40 MCS6_gain     ast_nvram_params[35].uc_dbb_scale
    5G_HT40_VHT40 MCS7_gain     ast_nvram_params[36].uc_dbb_scale
    5G_HT40_VHT40 MCS8_9_gain   ast_nvram_params[37].uc_dbb_scale
    5G_HT40_VHT40 MCS32_gain    ast_nvram_params[38].uc_dbb_scale
    5G_VHT80 MCS0_1_gain        ast_nvram_params[39].uc_dbb_scale
    5G_VHT80 MCS2_3_gain        ast_nvram_params[40].uc_dbb_scale
    5G_VHT80 MCS4_5_gain        ast_nvram_params[41].uc_dbb_scale
    5G_VHT80 MCS6_gain          ast_nvram_params[42].uc_dbb_scale
    5G_VHT80 MCS7_gain          ast_nvram_params[43].uc_dbb_scale
    5G_VHT80 MCS8_9_gain        ast_nvram_params[44].uc_dbb_scale

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_config_update_scaling_reg(oal_void)
{
    hal_cfg_customize_nvram_params_stru* past_src = g_st_customize.ast_nvram_params;

    /* 11b DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_SCALING_VALUE_11B_REG,
                        OAL_JOIN_WORD32(past_src[0].uc_dbb_scale, past_src[0].uc_dbb_scale, past_src[1].uc_dbb_scale, past_src[1].uc_dbb_scale));

    /* 11g DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_U1_SCALING_VALUE_11G_REG,
                        OAL_JOIN_WORD32(past_src[2].uc_dbb_scale, past_src[2].uc_dbb_scale, past_src[3].uc_dbb_scale, past_src[3].uc_dbb_scale));
    HI1102_REG_WRITE32(HI1102_PHY_U2_SCALING_VALUE_11G_REG,
                        OAL_JOIN_WORD32(past_src[4].uc_dbb_scale, past_src[4].uc_dbb_scale, past_src[5].uc_dbb_scale, past_src[6].uc_dbb_scale));

    /* 11n 2G HT20 DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_U1_SCALING_VALUE_11N_2D4G_REG,
                        OAL_JOIN_WORD32(past_src[7].uc_dbb_scale, past_src[7].uc_dbb_scale, past_src[8].uc_dbb_scale, past_src[8].uc_dbb_scale));
    HI1102_REG_WRITE32(HI1102_PHY_U2_SCALING_VALUE_11N_2D4G_REG,
                        OAL_JOIN_WORD32(past_src[9].uc_dbb_scale, past_src[9].uc_dbb_scale, past_src[10].uc_dbb_scale, past_src[11].uc_dbb_scale));

    /* 11n 2G HT40 DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_U1_SCALING_VALUE_11N40M_2D4G_REG,
                        OAL_JOIN_WORD32(past_src[13].uc_dbb_scale, past_src[13].uc_dbb_scale, past_src[14].uc_dbb_scale, past_src[14].uc_dbb_scale));
    HI1102_REG_WRITE32(HI1102_PHY_U2_SCALING_VALUE_11N40M_2D4G_REG,
                        OAL_JOIN_WORD32(past_src[15].uc_dbb_scale, past_src[15].uc_dbb_scale, past_src[16].uc_dbb_scale, past_src[17].uc_dbb_scale));

    /* 11a DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_U1_SCALING_VALUE_11A_REG,
                        OAL_JOIN_WORD32(past_src[21].uc_dbb_scale, past_src[21].uc_dbb_scale, past_src[22].uc_dbb_scale, past_src[22].uc_dbb_scale));
    HI1102_REG_WRITE32(HI1102_PHY_U2_SCALING_VALUE_11A_REG,
                        OAL_JOIN_WORD32(past_src[23].uc_dbb_scale, past_src[23].uc_dbb_scale, past_src[24].uc_dbb_scale, past_src[25].uc_dbb_scale));

    /* 11n 5G HT20 DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_U0_SCALING_VALUE_11N_5G_REG,
                        OAL_JOIN_WORD32(past_src[31].uc_dbb_scale, 0x00, 0x00, 0x00));
    HI1102_REG_WRITE32(HI1102_PHY_U1_SCALING_VALUE_11N_5G_REG,
                        OAL_JOIN_WORD32(past_src[26].uc_dbb_scale, past_src[26].uc_dbb_scale, past_src[27].uc_dbb_scale, past_src[27].uc_dbb_scale));
    HI1102_REG_WRITE32(HI1102_PHY_U2_SCALING_VALUE_11N_5G_REG,
                        OAL_JOIN_WORD32(past_src[28].uc_dbb_scale, past_src[28].uc_dbb_scale, past_src[29].uc_dbb_scale, past_src[30].uc_dbb_scale));

    /* 11n 5G HT40 DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_U1_SCALING_VALUE_11N40M_5G_REG,
                        OAL_JOIN_WORD32(past_src[32].uc_dbb_scale, past_src[32].uc_dbb_scale, past_src[33].uc_dbb_scale, past_src[33].uc_dbb_scale));
    HI1102_REG_WRITE32(HI1102_PHY_U2_SCALING_VALUE_11N40M_5G_REG,
                        OAL_JOIN_WORD32(past_src[34].uc_dbb_scale, past_src[34].uc_dbb_scale, past_src[35].uc_dbb_scale, past_src[36].uc_dbb_scale));
    HI1102_REG_WRITE32(HI1102_PHY_U3_SCALING_VALUE_11N40M_5G_REG,
                        OAL_JOIN_WORD32(past_src[37].uc_dbb_scale, past_src[37].uc_dbb_scale, 0x00, 0x00));

    /* 11ac 5G HT80 DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_U1_SCALING_VALUE_11AC_REG,
                        OAL_JOIN_WORD32(past_src[39].uc_dbb_scale, past_src[39].uc_dbb_scale, 0x00, 0x00));
    HI1102_REG_WRITE32(HI1102_PHY_U2_SCALING_VALUE_11AC_REG,
                        OAL_JOIN_WORD32(past_src[40].uc_dbb_scale, past_src[40].uc_dbb_scale, past_src[41].uc_dbb_scale, past_src[41].uc_dbb_scale));
    HI1102_REG_WRITE32(HI1102_PHY_U3_SCALING_VALUE_11AC_REG,
                        OAL_JOIN_WORD32(past_src[42].uc_dbb_scale, past_src[43].uc_dbb_scale, past_src[44].uc_dbb_scale, past_src[44].uc_dbb_scale));

    /* 11n 2G&5G HT40 MCS32 DBB scaling */
    HI1102_REG_WRITE32(HI1102_PHY_U3_SCALING_VALUE_11N40M_REG,
                        OAL_JOIN_WORD32(past_src[38].uc_dbb_scale, past_src[20].uc_dbb_scale, 0x00, 0x00));
}
/*****************************************************************************
 函 数 名  : dmac_config_set_cus_nvram_params
 功能描述  : 设置nvram中的参数:各协议速率的max txpwr、dbb scale以及dpd算法开关
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_set_cus_nvram_params(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_set_cus_nvram_params:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(&g_st_customize.ast_nvram_params, puc_param, OAL_SIZEOF(g_st_customize.ast_nvram_params));
    g_st_customize.uc_dpd_enable = (oal_uint8)*(puc_param + OAL_SIZEOF(g_st_customize.ast_nvram_params));

    /* close dpd alg */
    //pst_mac_vap->st_cap_flag.bit_dpd_enbale = g_st_customize.uc_dpd_enable;

    /* update rate_pow_table */
    dmac_config_update_rate_pow_table();
    /* update phy scaling reg */
    dmac_config_update_scaling_reg();

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_config_customize_info
 功能描述  : 调试使用:打印必要参数信息,不必要时可删除
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或 失败错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : h00349274
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_customize_info(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{dmac_config_customize_info:: pointer is null,pst_mac_vap[0x%x], puc_param[0x%x] .}", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 调试使用:打印必要参数信息 */
    OAM_WARNING_LOG2(0, OAM_SF_CFG, "[CUSTOMIZE::[dpd:%d][11ac2g_cap_bit:%d].]", g_st_customize.uc_dpd_enable, pst_mac_vap->st_cap_flag.bit_11ac2g);

    return OAL_SUCC;
}
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

/*****************************************************************************
    HMAC到DMAC配置同步事件操作函数表
*****************************************************************************/
OAL_STATIC OAL_CONST dmac_config_syn_stru g_ast_dmac_config_syn[] =
{
    /* 同步ID                    保留2个字节            函数操作 */
    {WLAN_CFGID_BSS_TYPE,           {0, 0},         dmac_config_set_bss_type},
    {WLAN_CFGID_ADD_VAP,            {0, 0},         dmac_config_add_vap},
    {WLAN_CFGID_START_VAP,          {0, 0},         dmac_config_start_vap},
    {WLAN_CFGID_DEL_VAP,            {0, 0},         dmac_config_del_vap},
    {WLAN_CFGID_DOWN_VAP,           {0, 0},         dmac_config_down_vap},
    {WLAN_CFGID_MODE,               {0, 0},         dmac_config_set_mode},
    {WLAN_CFGID_CURRENT_CHANEL,     {0, 0},         dmac_config_set_freq},
    {WLAN_CFGID_STATION_ID,         {0, 0},         dmac_config_set_mac_addr},
    {WLAN_CFGID_CONCURRENT,         {0, 0},         dmac_config_set_concurrent},
    {WLAN_CFGID_SSID,               {0, 0},         dmac_config_set_ssid},
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    {WLAN_CFGID_GET_HIPKT_STAT,     {0, 0},         dmac_config_get_hipkt_stat},
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_SHORTGI,            {0, 0},         dmac_config_set_shortgi},   /* hi1102-cb add sync */
    {WLAN_CFGID_VAP_STATE_SYN,      {0, 0},         dmac_config_vap_state_syn},
    {WLAN_CFGID_REGDOMAIN_PWR,      {0, 0},         dmac_config_set_regdomain_pwr},
    {WLAN_CFGID_SET_STBC_CAP,       {0, 0},         dmac_config_set_stbc_cap},
    {WLAN_CFGID_SET_LDPC_CAP,       {0, 0},         dmac_config_set_ldpc_cap},
#endif
    {WLAN_CFGID_SCAN_ABORT,         {0, 0},         dmac_config_scan_abort},
    {WLAN_CFGID_STOP_SCHED_SCAN,    {0, 0},         dmac_config_stop_sched_scan},
    {WLAN_CFGID_USER_ASOC_STATE_SYN,{0, 0},         dmac_config_user_asoc_state_syn},
    {WLAN_CFGID_USER_RATE_SYN,      {0, 0},         dmac_config_user_rate_info_syn},
    {WLAN_CFGID_USR_INFO_SYN,       {0, 0},         dmac_config_sta_usr_info_syn},
    {WLAN_CFGID_STA_VAP_INFO_SYN,   {0, 0},         dmac_config_vap_info_syn},

#ifdef _PRE_WLAN_FEATURE_TXOPPS
    {WLAN_CFGID_STA_TXOP_AID,         {0, 0},      dmac_txopps_set_machw_partialaid_sta},
#endif

    {WLAN_CFGID_SHORT_PREAMBLE,     {0, 0},         dmac_config_set_shpreamble},
#ifdef _PRE_WLAN_FEATURE_MONITOR
    {WLAN_CFGID_ADDR_FILTER,        {0, 0},         dmac_config_set_addr_filter},
#endif
    {WLAN_CFGID_PROT_MODE,          {0, 0},         dmac_config_set_prot_mode},
    {WLAN_CFGID_BEACON_INTERVAL,    {0, 0},         dmac_config_set_bintval},
    {WLAN_CFGID_NO_BEACON,          {0, 0},         dmac_config_set_nobeacon},
    {WLAN_CFGID_TX_CHAIN,           {0, 0},         dmac_config_set_txchain},
    {WLAN_CFGID_RX_CHAIN,           {0, 0},         dmac_config_set_rxchain},
    {WLAN_CFGID_TX_POWER,           {0, 0},         dmac_config_set_txpower},
    {WLAN_CFGID_DTIM_PERIOD,        {0, 0},         dmac_config_set_dtimperiod},
    {WLAN_CFGID_GET_MPDU_NUM,       {0, 0},         dmac_config_get_mpdu_num},
#if 0
    {WLAN_CFGID_OTA_SWITCH,         {0, 0},         dmac_config_ota_switch},
#endif
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    {WLAN_CFGID_START_DPD,         {0, 0},          dmac_config_start_dpd},
#endif
#ifdef _PRE_WLAN_CHIP_TEST
    {WLAN_CFGID_SET_BEACON_OFFLOAD_TEST, {0, 0},    dmac_config_beacon_offload_test},
#endif
    {WLAN_CFGID_OTA_BEACON_SWITCH,  {0, 0},         dmac_config_ota_beacon_switch},
    {WLAN_CFGID_OTA_RX_DSCR_SWITCH, {0, 0},         dmac_config_ota_rx_dscr_switch},
    {WLAN_CFGID_SET_ALL_OTA,        {0, 0},         dmac_config_set_all_ota},
    {WLAN_CFGID_OAM_OUTPUT_TYPE,    {0, 0},         dmac_config_oam_output},
    {WLAN_CFGID_PROBE_SWITCH,       {0, 0},         dmac_config_probe_switch},
    {WLAN_CFGID_80211_MCAST_SWITCH, {0, 0},         dmac_config_80211_mcast_switch},
    {WLAN_CFGID_RSSI_SWITCH,        {0, 0},         dmac_config_rssi_switch},

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
	{WLAN_CFGID_REPORT_VAP_INFO,         {0, 0},    dmac_config_report_vap_info},
    {WLAN_CFGID_80211_UCAST_SWITCH, {0, 0},         dmac_config_80211_ucast_switch},
    {WLAN_CFGID_WFA_CFG_AIFSN,         {0, 0},      dmac_config_wfa_cfg_aifsn},
    {WLAN_CFGID_WFA_CFG_CW,         {0, 0},         dmac_config_wfa_cfg_cw},
#endif /* DMAC_OFFLOAD */


#ifdef _PRE_WLAN_FEATURE_UAPSD
    {WLAN_CFGID_UAPSD_EN,           {0, 0},         dmac_config_set_uapsden},
    {WLAN_CFGID_UAPSD_DEBUG,        {0, 0},         dmac_config_uapsd_debug},
    {WLAN_CFGID_UAPSD_UPDATE,       {0, 0},         dmac_config_set_uapsd_update},
#endif
    {WLAN_CFGID_EDCA_TABLE_CWMIN,           {0, 0},         dmac_config_set_cwmin},
    {WLAN_CFGID_EDCA_TABLE_CWMAX,           {0, 0},         dmac_config_set_cwmax},
    {WLAN_CFGID_EDCA_TABLE_AIFSN,           {0, 0},         dmac_config_set_aifsn},
    {WLAN_CFGID_EDCA_TABLE_TXOP_LIMIT,      {0, 0},         dmac_config_set_txop_limit},
    {WLAN_CFGID_EDCA_TABLE_MSDU_LIFETIME,   {0, 0},         dmac_config_set_msdu_lifetime},
    {WLAN_CFGID_EDCA_TABLE_MANDATORY,       {0, 0},         dmac_config_set_edca_mandatory},
    {WLAN_CFGID_QEDCA_TABLE_CWMIN,          {0, 0},         dmac_config_set_qap_cwmin},
    {WLAN_CFGID_QEDCA_TABLE_CWMAX,          {0, 0},         dmac_config_set_qap_cwmax},
    {WLAN_CFGID_QEDCA_TABLE_AIFSN,          {0, 0},         dmac_config_set_qap_aifsn},
    {WLAN_CFGID_QEDCA_TABLE_TXOP_LIMIT,     {0, 0},         dmac_config_set_qap_txop_limit},
    {WLAN_CFGID_QEDCA_TABLE_MSDU_LIFETIME,  {0, 0},         dmac_config_set_qap_msdu_lifetime},
    {WLAN_CFGID_QEDCA_TABLE_MANDATORY,      {0, 0},         dmac_config_set_qap_edca_mandatory},

    {WLAN_CFGID_VAP_INFO,                   {0, 0},         dmac_config_vap_info},
    {WLAN_CFGID_ADD_USER,                   {0, 0},         dmac_config_add_user},
    {WLAN_CFGID_DEL_USER,                   {0, 0},         dmac_config_del_user},
    {WLAN_CFGID_PAUSE_TID,                  {0, 0},         dmac_config_pause_tid},
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_DUMP_TIEMR,                 {0, 0},         dmac_config_dump_timer},
#endif
    {WLAN_CFGID_SET_USER_VIP,               {0, 0},         dmac_config_set_user_vip},
    {WLAN_CFGID_SET_VAP_HOST,               {0, 0},         dmac_config_set_vap_host},
    {WLAN_CFGID_SEND_BAR,                   {0, 0},         dmac_config_send_bar},
    {WLAN_CFGID_RESET_HW,                   {0, 0},         dmac_config_reset_hw},
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_RESET_HW_OPERATE,           {0, 0},         dmac_reset_sys_event},
#endif
    {WLAN_CFGID_DUMP_RX_DSCR,               {0, 0},         dmac_config_dump_rx_dscr},
    {WLAN_CFGID_DUMP_TX_DSCR,               {0, 0},         dmac_config_dump_tx_dscr},
#ifdef _PRE_DEBUG_MODE_USER_TRACK
    {WLAN_CFGID_USR_THRPUT_STAT,            {0, 0},         dmac_config_report_thrput_stat},
#endif
#ifdef _PRE_WLAN_FEATURE_TXOPPS
    {WLAN_CFGID_TXOP_PS_MACHW,              {0, 0},         dmac_config_set_txop_ps_machw},
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    {WLAN_CFGID_BTCOEX_STATUS_PRINT,        {0, 0},         dmac_config_print_btcoex_status},
#endif
#ifdef _PRE_WLAN_FEATURE_LTECOEX
    {WLAN_CFGID_LTECOEX_MODE_SET,           {0, 0},         dmac_config_ltecoex_mode_set},
#endif
#ifdef _PRE_WLAN_DFT_STAT
    {WLAN_CFGID_PHY_STAT_EN,                {0, 0},         dmac_config_set_phy_stat_en},
    {WLAN_CFGID_DBB_ENV_PARAM,              {0, 0},         dmac_config_dbb_env_param},
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    {WLAN_CFGID_USR_QUEUE_STAT,             {0, 0},         dmac_config_usr_queue_stat},
#endif
    {WLAN_CFGID_VAP_STAT,                   {0, 0},         dmac_config_report_vap_stat},
    {WLAN_CFGID_ALL_STAT,                   {0, 0},         dmac_config_report_all_stat},
#endif

    {WLAN_CFGID_SET_LOG_LEVEL,              {0, 0},         dmac_config_set_log_level},
    {WLAN_CFGID_SET_FEATURE_LOG,            {0, 0},         dmac_config_set_feature_log},
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_SET_LOG_PM,                 {0, 0},         dmac_config_set_log_lowpower},
    {WLAN_CFGID_SET_PM_SWITCH,              {0, 0},         dmac_config_set_pm_switch},
#endif
    /*wpa-wpa2*/
    {WLAN_CFGID_ADD_KEY,           {0, 0},              dmac_config_11i_add_key},
	//{WLAN_CFGID_ADD_KEY_KEY,       {0, 0},              dmac_config_11i_add_key},
    //{WLAN_CFGID_ADD_KEY_SEQ,       {0, 0},              dmac_config_11i_add_key_seq},
    {WLAN_CFGID_REMOVE_KEY,        {0, 0},              dmac_config_11i_remove_key},
    {WLAN_CFGID_DEFAULT_KEY,       {0, 0},              dmac_config_11i_set_default_key},
    //{WLAN_CFGID_ADD_WEP_KEY,       {0, 0},              dmac_config_wep_add_key},
    {WLAN_CFGID_ADD_WEP_ENTRY,     {0, 0},              dmac_config_wep_add_entry},
    {WLAN_CFGID_REMOVE_WEP_KEY,    {0, 0},              dmac_config_wep_remove_key},
	{WLAN_CFGID_CONNECT_REQ,        {0, 0},             dmac_config_connect},

#ifdef _PRE_WLAN_FEATURE_WAPI
    {WLAN_CFGID_ADD_WAPI_KEY,       {0, 0},             dmac_config_wapi_add_key},
#endif

    {WLAN_CFGID_INIT_SECURTIY_PORT, {0, 0},             dmac_config_11i_init_port},
    {WLAN_CFGID_ALG,               {0, 0},              dmac_config_alg},
    {WLAN_CFGID_DUMP_BA_BITMAP,    {0, 0},              dmac_config_dump_ba_bitmap},
    {WLAN_CFGID_DUMP_ALL_RX_DSCR,  {0, 0},              dmac_config_dump_all_rx_dscr},
    {WLAN_CFGID_USER_INFO,         {0, 0},              dmac_config_user_info},
    {WLAN_CFGID_SET_DSCR,          {0, 0},              dmac_config_set_dscr},
    {WLAN_CFGID_COUNTRY,           {0, 0},              dmac_config_set_country},
#ifdef _PRE_WLAN_FEATURE_DFS
    {WLAN_CFGID_COUNTRY_FOR_DFS,   {0, 0},              dmac_config_set_country_for_dfs},
#endif
#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
    {WLAN_CFGID_SET_RATE,          {0, 0},              dmac_config_set_rate},
    {WLAN_CFGID_SET_MCS,           {0, 0},              dmac_config_set_mcs},
    {WLAN_CFGID_SET_MCSAC,         {0, 0},              dmac_config_set_mcsac},
    {WLAN_CFGID_SET_NSS,           {0, 0},              dmac_config_set_nss},
    {WLAN_CFGID_SET_RFCH,          {0, 0},              dmac_config_set_rfch},
    {WLAN_CFGID_SET_BW,            {0, 0},              dmac_config_set_bw},
    {WLAN_CFGID_SET_ALWAYS_TX,     {0, 0},              dmac_config_set_always_tx},
#endif

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    {WLAN_CFGID_SET_ALWAYS_TX_1102,{0, 0},              dmac_config_set_always_tx_1102},
#endif
    {WLAN_CFGID_SET_ALWAYS_RX,     {0, 0},              dmac_config_set_always_rx},
#ifdef _PRE_DEBUG_MODE
    {WLAN_CFGID_DYNC_TXPOWER,      {0, 0},              dmac_config_dync_txpower},
#endif
    {WLAN_CFGID_GET_THRUPUT,       {0, 0},              dmac_config_get_thruput},
    {WLAN_CFGID_SET_FREQ_SKEW,     {0, 0},              dmac_config_set_freq_skew},
    {WLAN_CFGID_ADJUST_PPM,        {0, 0},              dmac_config_adjust_ppm},
    {WLAN_CFGID_REG_INFO,          {0, 0},              dmac_config_reg_info},
    {WLAN_CFGID_DBB_SCALING_AMEND,          {0, 0},     dmac_config_dbb_scaling_amend},
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_HOST))
    {WLAN_CFGID_SDIO_FLOWCTRL,     {0, 0},              dmac_config_sdio_flowctrl},
#endif
    {WLAN_CFGID_REG_WRITE,         {0, 0},              dmac_config_reg_write},
    {WLAN_CFGID_CFG80211_SET_CHANNEL,      {0, 0},      dmac_config_set_channel},

    {WLAN_CFGID_CFG80211_CONFIG_BEACON,    {0, 0},      dmac_config_set_beacon},

    {WLAN_CFGID_BEACON_CHAIN_SWITCH,       {0, 0},      dmac_config_beacon_chain_switch},
#if 0
    {WLAN_CFGID_TDLS_PROHI,                {0, 0},      dmac_config_tdls_prohibited},
    {WLAN_CFGID_TDLS_CHASWI_PROHI,         {0, 0},      dmac_config_tdls_channel_switch_prohibited},
#endif
    {WLAN_CFGID_HIDE_SSID,                 {0, 0},      dmac_config_hide_ssid},
    {WLAN_CFGID_WMM_SWITCH,                {0, 0},      dmac_config_wmm_switch},

#ifdef _PRE_WLAN_PERFORM_STAT
    {WLAN_CFGID_PFM_STAT,                  {0, 0},      dmac_config_pfm_stat},
    {WLAN_CFGID_PFM_DISPLAY,               {0, 0},      dmac_config_pfm_display},
#endif

#ifdef _PRE_WLAN_CHIP_TEST

    {WLAN_CFGID_LPM_TX_PROBE_REQUEST,     {0, 0},       dmac_config_lpm_tx_probe_request},
    {WLAN_CFGID_LPM_CHIP_STATE,     {0, 0},             dmac_config_set_lpm_chip_state},
    {WLAN_CFGID_LPM_SOC_MODE,      {0, 0},              dmac_config_set_lpm_soc_mode},
    {WLAN_CFGID_LPM_PSM_PARAM,      {0, 0},             dmac_config_set_lpm_psm_param},
    {WLAN_CFGID_LPM_SMPS_MODE,      {0, 0},             dmac_config_set_lpm_smps_mode},
    {WLAN_CFGID_LPM_SMPS_STUB,      {0, 0},             dmac_config_set_lpm_smps_stub},
    {WLAN_CFGID_LPM_TXOP_PS_SET,    {0, 0},             dmac_config_set_lpm_txop_ps},
    {WLAN_CFGID_LPM_TXOP_TX_STUB,   {0, 0},             dmac_config_set_lpm_txop_ps_tx_stub},
    {WLAN_CFGID_LPM_WOW_EN,         {0, 0},             dmac_config_set_lpm_wow_en},
    {WLAN_CFGID_SEND_FRAME,         {0, 0},             dmac_config_send_frame},
    {WLAN_CFGID_SET_RX_PN_REG,      {0, 0},             dmac_config_set_rx_pn},
    {WLAN_CFGID_SET_SOFT_RETRY,     {0, 0},             dmac_config_set_soft_retry},
    {WLAN_CFGID_OPEN_ADDR4,         {0, 0},             dmac_config_open_addr4},
    {WLAN_CFGID_OPEN_WMM_TEST,      {0, 0},             dmac_config_open_wmm_test},
    {WLAN_CFGID_CHIP_TEST_OPEN,     {0, 0},             dmac_config_chip_test_open},
    {WLAN_CFGID_SET_COEX,           {0, 0},             dmac_config_set_coex},
    {WLAN_CFGID_DFX_SWITCH,         {0, 0},             dmac_config_set_dfx},
    {WLAN_CFGID_REMOVE_LUT,         {0, 0},             dmac_config_remove_user_lut},
    {WLAN_CFGID_SEND_PSPOLL,        {0, 0},             dmac_config_send_pspoll},
    {WLAN_CFGID_SEND_NULLDATA,      {0, 0},             dmac_config_send_nulldata},
    {WLAN_CFGID_CLEAR_ALL_STAT,    {0, 0},              dmac_config_clear_all_stat},

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    {WLAN_CFGID_PMF_ENABLE,         {0, 0},             dmac_config_enable_pmf},
#endif
#endif
    {WLAN_CFGID_CHECK_FEM_PA,        {0, 0},            dmac_config_get_fem_pa_status},

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_SET_MIB,            {0, 0},             dmac_config_set_mib},
    {WLAN_CFGID_SET_OBSS_MIB,       {0, 0},             dmac_config_set_obss_mib},
#endif


#ifdef _PRE_SUPPORT_ACS
    {WLAN_CFGID_ACS_PARAM,          {0, 0},             dmac_acs_recv_msg},
    {WLAN_CFGID_ACS_CONFIG,         {0, 0},             dmac_config_acs},
#endif
#ifdef _PRE_WLAN_FEATURE_DFS
    {WLAN_CFGID_RADARTOOL,          {0, 0},             dmac_config_dfs_radartool},
#endif

    {WLAN_CFGID_SET_RTS_PARAM,      {0, 0},             dmac_config_set_rts_param},

    {WLAN_CFGID_UPDTAE_PROT_TX_PARAM,{0, 0},            dmac_config_update_protection_tx_param},
    {WLAN_CFGID_SET_PROTECTION,      {0, 0},            dmac_config_set_protection},

    {WLAN_CFGID_GET_VERSION,         {0, 0},            dmac_config_get_version},
    {WLAN_CFGID_RX_FCS_INFO,         {0, 0},            dmac_config_rx_fcs_info},
    {WLAN_CFGID_SET_THRUPUT_BYPASS,  {0, 0},            dmac_config_set_thruput_bypass},
#ifdef _PRE_WLAN_DFT_STAT
    {WLAN_CFGID_SET_PERFORMANCE_LOG_SWITCH,  {0, 0},            dmac_config_set_performance_log_switch},
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_RESUME_RX_INTR_FIFO, {0, 0},            dmac_config_resume_rx_intr_fifo},
#endif

#ifdef _PRE_DEBUG_MODE
    {WLAN_CFGID_GET_ALL_REG_VALUE,   {0, 0},            dmac_config_get_all_reg_value},
    {WLAN_CFGID_REPORT_AMPDU_STAT,   {0, 0},            dmac_config_report_ampdu_stat},
#endif
    {WLAN_CFGID_SET_VAP_NSS,         {0, 0},            dmac_config_set_vap_nss},
    {WLAN_CFGID_SET_AGGR_NUM,        {0, 0},            dmac_config_set_ampdu_aggr_num},

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_FREQ_ADJUST,         {0, 0},            dmac_config_freq_adjust},
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ
    {WLAN_CFGID_DATA_ACQ,            {0, 0},            dmac_config_data_acq},
#endif
#ifdef _PRE_WLAN_FEATURE_SMPS
    {WLAN_CFGID_SET_SMPS,            {0, 0},            dmac_config_set_smps_mode},
#endif

#ifdef _PRE_WLAN_FEATURE_PM
    {WLAN_CFGID_WIFI_EN,          {0, 0},               dmac_config_wifi_en},
    {WLAN_CFGID_PM_INFO,          {0, 0},               dmac_config_pm_info},
    {WLAN_CFGID_PM_EN,          {0, 0},                 dmac_config_pm_en},
#endif
    {WLAN_CFGID_SET_WPS_P2P_IE,    {0, 0},              dmac_config_set_app_ie_to_vap},
    {WLAN_CFGID_DEVICE_MEM_LEAK,   {0, 0},              dmac_config_show_device_memleak},
    {WLAN_CFGID_DEVICE_MEM_INFO,   {0, 0},              dmac_config_show_device_meminfo},
    {WLAN_CFGID_CFG80211_CANCEL_REMAIN_ON_CHANNEL,  {0, 0},  dmac_config_cancel_remain_on_channel},
#ifdef _PRE_WLAN_FEATURE_STA_PM
    {WLAN_CFGID_SET_PS_MODE,         {0, 0},                 dmac_config_set_sta_ps_mode},  /* hi1102 pspoll配置命令 */
#ifdef _PRE_PSM_DEBUG_MODE
    {WLAN_CFGID_SHOW_PS_INFO,        {0, 0},                 dmac_show_ps_info},/* sta psm 维测统计信息 */
#endif
    {WLAN_CFGID_SET_PSM_PARAM,       {0, 0},                 dmac_set_psm_param},/* sta psm tbtt offset/listen interval 设置 */
    {WLAN_CFGID_SET_STA_PM_ON,        {0, 0},                dmac_config_set_sta_pm_on},/* sta psm tbtt offset/listen interval 设置 */

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    {WLAN_CFGID_SET_UAPSD_PARA,        {0, 0},              dmac_config_set_uapsd_para},
#endif
#endif

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
    {WLAN_CFGID_QUERY_STATION_STATS, {0, 0},                dmac_config_proc_query_sta_info_event},
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
    {WLAN_CFGID_SET_P2P_PS_OPS,     {0, 0},                 dmac_config_set_p2p_ps_ops},
    {WLAN_CFGID_SET_P2P_PS_NOA,     {0, 0},                 dmac_config_set_p2p_ps_noa},
    {WLAN_CFGID_SET_P2P_PS_STAT,    {0, 0},                 dmac_config_set_p2p_ps_stat},
#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
    {WLAN_CFGID_SET_MIPS,           {0, 0},             dmac_config_set_mips},
    {WLAN_CFGID_SHOW_MIPS,          {0, 0},             dmac_config_show_mips},
#endif
    {WLAN_CFGID_NSS,                {0, 0},             dmac_config_nss},
    {WLAN_CFGID_UPDATE_OPMODE,      {0, 0},             dmac_config_opmode},
    {WLAN_CFGID_USER_CAP_SYN,       {0, 0},             dmac_config_user_cap_syn},

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    {WLAN_CFGID_ENABLE_ARP_OFFLOAD,         {0, 0},     dmac_config_enable_arp_offload},
    {WLAN_CFGID_SET_IP_ADDR,                {0, 0},     dmac_config_set_ip_addr},
    {WLAN_CFGID_SHOW_ARPOFFLOAD_INFO,       {0, 0},     dmac_config_show_arpoffload_info},
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
    {WLAN_CFGID_SET_ROAMING_MODE,       {0, 0},         dmac_config_roam_enable},
    {WLAN_CFGID_SET_ROAM_TRIGGER,       {0, 0},         dmac_config_set_roam_trigger},
    {WLAN_CFGID_ROAM_HMAC_SYNC_DMAC,    {0, 0},         dmac_config_roam_hmac_sync_dmac},
    {WLAN_CFGID_ROAM_NOTIFY_STATE,      {0, 0},         dmac_config_roam_notify_state},
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    {WLAN_CFGID_2040BSS_ENABLE,     {0, 0},             dmac_config_enable_2040bss},
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_SUSPEND_ACTION_SYN,        {0, 0},      dmac_config_suspend_action_sync},
#endif
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    {WLAN_CFGID_SET_DEVICE_FREQ,   {0, 0},         dmac_config_set_device_freq},
#endif
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    {WLAN_CFGID_SET_LINKLOSS_THRESHOLD,     {0, 0},       dmac_config_set_linkloss_threshold},
    {WLAN_CFGID_SET_ALL_LOG_LEVEL,          {0, 0},       dmac_config_set_all_log_level},
    {WLAN_CFGID_SET_D2H_HCC_ASSEMBLE_CNT,   {0, 0},       dmac_config_set_d2h_hcc_assemble_cnt},
    {WLAN_CFGID_SET_CHN_EST_CTRL,           {0, 0},       dmac_config_set_chn_est_ctrl},
    {WLAN_CFGID_SET_POWER_REF,              {0, 0},       dmac_config_set_power_ref},
    {WLAN_CFGID_SET_PM_CFG_PARAM,           {0, 0},       dmac_config_set_pm_cfg_param},
    {WLAN_CFGID_SET_CUS_RF,                 {0, 0},       dmac_config_set_cus_rf},
    {WLAN_CFGID_SET_CUS_DTS_CALI,           {0, 0},       dmac_config_set_cus_dts_cali},
    {WLAN_CFGID_SET_CUS_NVRAM_PARAM,        {0, 0},       dmac_config_set_cus_nvram_params},
    /* show customize info */
    {WLAN_CFGID_SHOW_DEV_CUSTOMIZE_INFOS,   {0, 0},       dmac_config_customize_info},
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */
    {WLAN_CFGID_REDUCE_SAR,                 {0, 0},       dmac_config_reduce_sar},
    {WLAN_CFGID_BUTT,               {0, 0},             OAL_PTR_NULL},
};


oal_uint32 dmac_cali_to_hmac(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;

    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);

    //OAL_IO_PRINT("dmac_cali_to_hmac start\r\n");
    FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_MISC_SUB_TYPE_CALI_TO_HMAC);
    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_event_config_syn
 功能描述  : dmac配置同步事件处理入口
 输入参数  : pst_event_mem: 事件内存结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_event_config_syn(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    hmac_to_dmac_cfg_msg_stru  *pst_hmac2dmac_msg;
    mac_vap_stru               *pst_mac_vap;
    mac_device_stru            *pst_mac_device;
    oal_uint32                  ul_ret;
    oal_uint16                  us_cfgid;


    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_event_config_syn::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件 */
    pst_event         = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr     = &(pst_event->st_event_hdr);
    pst_hmac2dmac_msg = (hmac_to_dmac_cfg_msg_stru *)pst_event->auc_event_data;

    //OAM_INFO_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::a dmac config syn event occur, cfg_id=%d.}", pst_hmac2dmac_msg->en_syn_id);
    /* 获取dmac vap */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::pst_mac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取mac device */
    pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if(OAL_TRUE == MAC_DEV_IS_RESET_IN_PROGRESS(pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::MAC_DEV_IS_RESET_IN_PROGRESS.}");

        return OAL_FAIL;
    }

    /* 获得cfg id对应的操作函数 */
    for (us_cfgid = 0; WLAN_CFGID_BUTT != g_ast_dmac_config_syn[us_cfgid].en_cfgid; us_cfgid++)
    {
        if (g_ast_dmac_config_syn[us_cfgid].en_cfgid == pst_hmac2dmac_msg->en_syn_id)
        {
            break;
        }
    }

    /* 异常情况，cfgid在g_ast_dmac_config_syn中不存在 */
    if (WLAN_CFGID_BUTT == g_ast_dmac_config_syn[us_cfgid].en_cfgid)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_CFG, "{dmac_event_config_syn::invalid en_cfgid[%d].", pst_hmac2dmac_msg->en_syn_id);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* 执行操作函数 */
    ul_ret = g_ast_dmac_config_syn[us_cfgid].p_set_func(pst_mac_vap, (oal_uint8)(pst_hmac2dmac_msg->us_len), (oal_uint8 *)pst_hmac2dmac_msg->auc_msg_body);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG2(pst_event_hdr->uc_vap_id, OAM_SF_CFG,
                         "{dmac_event_config_syn::p_set_func failed, ul_ret=%d en_syn_id=%d.", ul_ret, pst_hmac2dmac_msg->en_syn_id);
        return ul_ret;
    }

    return OAL_SUCC;
}
/*lint -e578*//*lint -e19*/

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    oal_module_symbol(dmac_config_set_qap_cwmin);
    oal_module_symbol(dmac_config_set_qap_cwmax);
    oal_module_symbol(dmac_config_set_qap_aifsn);
#endif
/*lint +e578*//*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

