/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_mgmt_sta.c
  版 本 号   : 初稿
  作    者   : zhangheng
  生成日期   : 2013年6月7日
  最近修改   :
  功能描述   : sta侧管理帧处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月7日
    作    者   : zhangheng
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
#include "dmac_mgmt_sta.h"
#include "dmac_main.h"
#include "oal_net.h"
#include "dmac_chan_mgmt.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_STA_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_mgmt_wmm_update_edca_machw_sta
 功能描述  : STA模式下VAP更新EDCA寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月25日
    作    者   : z00237171
    修改内容   : 新生成函数
  2.日    期   : 2015年4月29日
    作    者   : s00304087
    修改内容   : 02新增同步hmac mib参数
*****************************************************************************/
oal_uint32 dmac_mgmt_wmm_update_edca_machw_sta(frw_event_mem_stru  *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_sta_asoc_set_edca_reg_stru *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_vap_stru                       *pst_dmac_sta;
    wlan_wme_ac_type_enum_uint8         en_ac_type;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_sta_asoc_set_edca_reg_stru *)pst_event->auc_event_data;

    /* 获取device结构的信息 */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_device[idx=%d] null.}", pst_event_hdr->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_sta = mac_res_get_dmac_vap(pst_reg_params->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_sta)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_WMM, "{dmac_mgmt_wmm_update_edca_machw_sta::pst_dmac_vap[idx=%d] null.}", pst_reg_params->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_WMM_SET_PARAM_TYPE_DEFAULT == pst_reg_params->en_set_param_type)
    {
        /*去使能EDCA*/
        hal_disable_machw_edca(pst_device->pst_device_stru);
        pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = OAL_FALSE;

        /* 设置VO默认参数 */
        hal_vap_set_machw_aifsn_ac(pst_dmac_sta->pst_hal_vap, WLAN_WME_AC_VO, DMAC_WMM_VO_DEFAULT_DECA_AIFSN);

        hal_vap_set_edca_machw_cw(pst_dmac_sta->pst_hal_vap,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmax,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableCWmin,
                                  WLAN_WME_AC_VO);
        hal_vap_set_machw_prng_seed_val_all_ac(pst_dmac_sta->pst_hal_vap);
        return OAL_SUCC;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_memcopy((oal_uint8*)&pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac, (oal_uint8*)&pst_reg_params->ast_wlan_mib_qap_edac, (OAL_SIZEOF(wlan_mib_Dot11QAPEDCAEntry_stru) * WLAN_WME_AC_BUTT));
#endif

    hal_enable_machw_edca(pst_dmac_sta->pst_hal_device);

    /* 更新edca寄存器参数 */
    hal_vap_set_machw_aifsn_all_ac(pst_dmac_sta->pst_hal_vap,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableAIFSN,
                                   (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableAIFSN);

    for (en_ac_type = 0; en_ac_type < WLAN_WME_AC_BUTT; en_ac_type++)
    {
        hal_vap_set_edca_machw_cw(pst_dmac_sta->pst_hal_vap,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmax,
                                 (oal_uint8)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[en_ac_type].ul_dot11QAPEDCATableCWmin,
                                  en_ac_type);
    }

    /* TXOP不使能时,同步AP参数;否则使用配置值 */
    if(OAL_FALSE == pst_device->en_txop_enable)
    {
        hal_vap_set_machw_txop_limit_bkbe(pst_dmac_sta->pst_hal_vap,
                                          (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit,
                                          (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
    }

    hal_vap_set_machw_txop_limit_vivo(pst_dmac_sta->pst_hal_vap,
                                      (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableTXOPLimit);

    /*DTS: 1102 beacon帧中EDCA参数中没有LIFETIME值，STA根据本地mib值更新(mib值为0),
    注释掉这个配置，按照寄存器配置来生效即可 */

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    hal_vap_set_machw_edca_bkbe_lifetime(pst_dmac_sta->pst_hal_vap,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableMSDULifetime,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableMSDULifetime);
    hal_vap_set_machw_edca_vivo_lifetime(pst_dmac_sta->pst_hal_vap,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VO].ul_dot11QAPEDCATableMSDULifetime,
                                         (oal_uint16)pst_dmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_VI].ul_dot11QAPEDCATableMSDULifetime);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_chan_adjust_bandwidth_sta
 功能描述  : 根据AP和(STA)自身的能力，计算准备要切换到的带宽模式
 输入参数  : pst_mac_vap  : MAC VAP结构体指针，指向STA
 输出参数  : pen_bandwidth: 更新后的带宽模式
 返 回 值  : 无+ 调用函数  :+ 被调函数  :
 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : mayuan
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_void  dmac_chan_adjust_bandwidth_sta(mac_vap_stru *pst_mac_vap, wlan_channel_bandwidth_enum_uint8 *pen_bandwidth)
{
    wlan_channel_bandwidth_enum_uint8   en_curr_bandwidth;
    wlan_channel_bandwidth_enum_uint8   en_announced_bandwidth;
    en_curr_bandwidth      = pst_mac_vap->st_channel.en_bandwidth;
    en_announced_bandwidth = pst_mac_vap->st_ch_switch_info.en_new_bandwidth;
    *pen_bandwidth = en_curr_bandwidth;

    /* 如果当前带宽模式与新带宽模式相同，则直接返回 */
    if (en_announced_bandwidth == en_curr_bandwidth)
    {
        return;
    }

    if (WLAN_BAND_WIDTH_20M == en_announced_bandwidth)
    {
        *pen_bandwidth = WLAN_BAND_WIDTH_20M;
    }
    else   /* 新带宽模式不是20MHz，则STA侧带宽模式需要根据自身能力进行匹配 */
    {
        /* 使能40MHz */
        /* (1) 用户开启"40MHz运行"特性(即STA侧 dot11FortyMHzOperationImplemented为true) */
        /* (2) AP在40MHz运行 */
        if (OAL_TRUE == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap))
        {
            switch (en_announced_bandwidth)
            {
                case WLAN_BAND_WIDTH_40PLUS:
                case WLAN_BAND_WIDTH_80PLUSPLUS:
                case WLAN_BAND_WIDTH_80PLUSMINUS:
                    *pen_bandwidth = WLAN_BAND_WIDTH_40PLUS;
                    break;

                case WLAN_BAND_WIDTH_40MINUS:
                case WLAN_BAND_WIDTH_80MINUSPLUS:
                case WLAN_BAND_WIDTH_80MINUSMINUS:
                    *pen_bandwidth = WLAN_BAND_WIDTH_40MINUS;
                    break;

                default:
                    *pen_bandwidth = WLAN_BAND_WIDTH_20M;
                    break;
            }
        }

        /* 使能80MHz */
        /* (1) 用户支持80MHz带宽(即STA侧 dot11VHTChannelWidthOptionImplemented为0) */
        if (OAL_TRUE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        {
            if (WLAN_MIB_VHT_SUPP_WIDTH_80 == mac_mib_get_VHTChannelWidthOptionImplemented(pst_mac_vap))
            {
                *pen_bandwidth = en_announced_bandwidth;
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_chan_multi_select_channel_mac
 功能描述  : 遍历device下所有VAP，设置SW/MAC/PHY/RF中的信道和带宽，使VAP工作在新信道上
 输入参数  : pst_mac_vap : MAC VAP结构体指针
             uc_channel  : 将要被设置的信道号
             en_bandwidth: 将要被设置的带宽模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : mayuan
    修改内容   : 新生成函数
*****************************************************************************/
oal_void  dmac_chan_multi_select_channel_mac(mac_vap_stru *pst_mac_vap, oal_uint8 uc_channel, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    oal_uint8          uc_vap_idx;
    mac_device_stru   *pst_device;
    mac_vap_stru      *pst_vap;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
        "{hmac_chan_multi_select_channel_mac::pst_device null,device_id=%d.}", pst_mac_vap->uc_device_id);
        return;
    }

    if (0 == pst_device->uc_vap_num)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_chan_multi_select_channel_mac::none vap.}");
        return;
    }

    OAL_IO_PRINT("[DFS]hmac_chan_multi_select_channel_mac, Switching channel to %d! BW %d mode.\n", uc_channel, en_bandwidth);

#ifdef _PRE_WLAN_FEATURE_DBAC
    if (mac_is_dbac_running(pst_device))
    {
        dmac_chan_select_channel_mac(pst_mac_vap, uc_channel, en_bandwidth);
        return;
    }
#endif

    /* 遍历device下所有vap */
    for (uc_vap_idx = 0; uc_vap_idx <pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
            "{hmac_chan_multi_select_channel_mac::pst_vap null,vap_id=%d.}", pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        /* 切换至新信道工作 */
        dmac_chan_select_channel_mac(pst_mac_vap, uc_channel, en_bandwidth);
    }
}

/*****************************************************************************
 函 数 名  : dmac_chan_sta_switch_channel
 功能描述  : STA切换信道
 输入参数  : pst_mac_vap: MAC VAP结构体指针，指向sta
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : mayuan
    修改内容   : 新生成函数
*****************************************************************************/
oal_void  dmac_chan_sta_switch_channel(mac_vap_stru *pst_mac_vap)
{
    wlan_channel_bandwidth_enum_uint8   en_new_bandwidth = WLAN_BAND_WIDTH_20M;

    if (WLAN_BAND_WIDTH_BUTT != pst_mac_vap->st_ch_switch_info.en_new_bandwidth)
    {
        dmac_chan_adjust_bandwidth_sta(pst_mac_vap, &en_new_bandwidth);
    }

    /* 禁止硬件全部发送直到STA信道切换完毕 */
    dmac_chan_disable_machw_tx(pst_mac_vap);
    /* 切换信道 */
    dmac_chan_multi_select_channel_mac(pst_mac_vap, pst_mac_vap->st_ch_switch_info.uc_new_channel, en_new_bandwidth);

    /* 设置该变量，避免STA在信道切换时发生link loss */
    //pst_mac_vap->st_ch_switch_info.en_waiting_for_ap           = OAL_TRUE;

    /* STA已切换至新信道， */
    pst_mac_vap->st_ch_switch_info.en_channel_swt_cnt_zero     = OAL_FALSE;
    pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel = OAL_FALSE;
    pst_mac_vap->st_ch_switch_info.en_new_bandwidth            = WLAN_BAND_WIDTH_BUTT;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    dmac_switch_complete_notify(pst_mac_vap, OAL_FALSE);
#endif
}

/*****************************************************************************
 函 数 名  : dmac_handle_tbtt_chan_mgmt_sta
 功能描述  : STA侧TBTT中断中进行信道管理
 输入参数  : pst_hmac_vap: HMAC VAP结构体指针，指向sta
 输出参数  : 无+ 返 回 值  : 无+ 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年3月13日
    作    者   : mayuan
    修改内容   : 新生成函数
*****************************************************************************/
oal_void  dmac_handle_tbtt_chan_mgmt_sta(dmac_vap_stru *pst_dmac_vap)
{
    mac_vap_stru *pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);

    if (OAL_FALSE == mac_mib_get_SpectrumManagementImplemented(pst_mac_vap))
    {
        return;
    }

    /* 如果AP发送的CSA IE中的"信道切换计数"为零，则立即切换信道 */
    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_channel_swt_cnt_zero)
    {
        dmac_chan_sta_switch_channel(pst_mac_vap);
        dmac_chan_enable_machw_tx(pst_mac_vap);
        //dmac_vap_linkloss_clean(pst_dmac_vap);
    }
#if 0
    /* 信道切换已经完成。现在新信道上等待接收AP发送的Beacon帧 */
    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_for_ap)
    {
        /* 等待一段时间后，在新信道上恢复硬件发送(即便这时AP有可能还没有切换至新信道) */
        if (pst_dmac_vap->st_linkloss_info.us_link_loss > WLAN_LINKLOSS_OFFSET_11H)
        {
            pst_mac_vap->st_ch_switch_info.en_waiting_for_ap = OAL_FALSE;
            dmac_chan_enable_machw_tx(pst_mac_vap);
            dmac_vap_linkloss_clean(pst_dmac_vap);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            dmac_switch_complete_notify(pst_mac_vap, OAL_FALSE);
#endif
        }
    }
#endif

    /* 如果AP发送的CSA IE中的"信道切换计数"不为零，则每一次TBTT中断中减一 */
    if (pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt > 0)
    {
        pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt--;
        if (0 == pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt)
        {
            if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_waiting_to_shift_channel)
            {
                dmac_chan_sta_switch_channel(pst_mac_vap);
                dmac_chan_enable_machw_tx(pst_mac_vap);
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_is_active_htsta
 功能描述  : 判断sta是否为活跃sta
 输入参数  : pst_hmac_vap: HMAC VAP结构体指针，指向sta
 输出参数  : 无+ 返 回 值  : 无+ 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : l00311403
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint8  dmac_mgmt_is_active_htsta(mac_vap_stru *pst_mac_vap)
{
    //TODO 目前该函数始终返回true, 如有必要在此处加上判断sta是否为活跃ht sta的代码
    return OAL_TRUE;
}

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 函 数 名  : dmac_mgmg_need_obss_scan
 功能描述  : 判断是否需要启动obss scan
 输入参数  : pst_hmac_vap: HMAC VAP结构体指针，指向sta
 输出参数  : 无+ 返 回 值  : 无+ 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年3月30日
    作    者   : l00311403
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint8  dmac_mgmt_need_obss_scan(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru                     *pst_device;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_2040, "dmac_mgmt_need_obss_scan::null param");
        return OAL_FALSE;
    }

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN,
            "{dmac_mgmt_need_obss_scan::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    if (0 != pst_device->st_p2p_info.uc_p2p_goclient_num)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN,
            "{dmac_mgmt_need_obss_scan:: stop obss can since this is p2p scanrio}");
        return OAL_FALSE;
    }
#endif

    //l00311403 当前vht不启用obss扫描
    if ( (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode) &&
         (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state) &&
         (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)&&
         (OAL_TRUE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap)) &&
         (OAL_TRUE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)) &&
         (OAL_TRUE == dmac_mgmt_is_active_htsta(pst_mac_vap))
          )
     {
        return OAL_TRUE;
     }

    return OAL_FALSE;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

