/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_fcs.c
  版 本 号   : 初稿
  作    者   : g00196511 gaolin
  生成日期   : 2012年12月13日
  最近修改   :
  功能描述   : 调度算法
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月13日
    作    者   : gaolin
    修改内容   : 创建文件

******************************************************************************/
#ifdef  __cplusplus
#if     __cplusplus
extern  "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
 *****************************************************************************/
#include    "wlan_spec.h"
#include    "mac_device.h"
#include    "dmac_vap.h"
#include    "frw_ext_if.h"
#include    "dmac_main.h"
#include    "dmac_mgmt_bss_comm.h"
#include    "mac_regdomain.h"
#include    "dmac_tx_bss_comm.h"
#include    "mac_vap.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include    "alg_dbac.h"
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_sta_pm.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_FCS_C

/*****************************************************************************
  2 全局变量定义
 *****************************************************************************/

#define BT_COEX_RELEASE_TIMEOUT 1000

/* FIXME : 设置初始值 */
mac_fcs_reg_record_stru g_ast_fcs_mac_regs[] = {
    { 0x0000, { 0,        0,       } },     /* MAC_REG_PA_CTRL        */
    { 0x000C, { 0,        0,       } },     /* MAC_REG_HT_CTRL        */
    { 0x0440, { 0,        0,       } },     /* NULL_FRM_TX_PHY_MODE   */
    { 0x0444, { 0,        0,       } },     /* NULL_FRM_TX_DATA_RATE  */
    { 0x0448, { 0,        0,       } },     /* PROT_PHY_TX_MODE       */
    { 0x044C, { 0,        0,       } },     /* PROT_DATARATE          */
    { 0x0458, { 0,        0,       } },     /* RESP_PHY_TX_MODE       */
    { 0x045C, { 0,        0,       } },     /* RESP_DATARATE          */
    { 0x0900, { 0,        0,       } },     /* SLOT_TIME              */
    { 0x0A14, { 0,        0,       } },     /* SIFS_TIME              */
    { 0x0A18, { 0,        0,       } },     /* EIFS_TIME              */
    { 0x0A1C, { 0,        0,       } },     /* SEC_CH_SLOT            */
    { 0x0A20, { 0,        0,       } },     /* SIFS_TIME2             */
    { 0x0464, { 0,        0,       } },     /* PHYTXPOWLVL            */
};
mac_fcs_reg_record_stru g_ast_fcs_phy_regs[] = {
    { 0x001C, { 0,        0,       } },     /* PHY_CTRL               */
    { 0x0020, { 0,        0,       } },     /* RX_MULT_ANT_SEL        */
    { 0x0024, { 0,        0,       } },     /* RX_ONE_ANT_SEL         */
};
/*****************************************************************************
  3 函数实现
****************************************************************************/

OAL_STATIC oal_void mac_fcs_notify_chain_init(mac_fcs_notify_chain_stru *pst_chain)
{
    oal_memset(pst_chain, 0, sizeof(mac_fcs_notify_chain_stru));
}
/*****************************************************************************
 函 数 名  : mac_fcs_set_channel
 功能描述  : 用于FCS的设置信道接口，不会重启MAC
 输入参数  : mac_device_stru    *pst_mac_device
             mac_channel_stru   *pst_channel
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_fcs_set_channel(mac_device_stru    *pst_mac_device,
                                mac_channel_stru   *pst_channel)
{
    oal_uint32               ul_ret;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint                 ul_irq_flag;

    if ((OAL_PTR_NULL == pst_mac_device) || (OAL_PTR_NULL == pst_channel))
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{mac_fcs_set_channel::null param %p %p", pst_mac_device, pst_channel);
        return OAL_FAIL;
    }

    /* 检测信道号是否合法 */
    ul_ret = mac_is_channel_num_valid(pst_channel->en_band, pst_channel->uc_chan_number);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{mac_fcs_set_channel::invalid channel num. en_band=%d, uc_chan_num=%d", pst_channel->en_band, pst_channel->uc_chan_number);
        return ul_ret;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_PTR_NULL == pst_hal_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{mac_fcs_set_channel::pst_hal_device null].}");
        return OAL_FAIL;
    }

    /* 关中断，挂起硬件发送需要关中断 */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_MFSC);

    /* 关闭pa */
    //hal_disable_machw_phy_and_pa(pst_hal_device);

    /* 设置频段 */
    hal_set_freq_band(pst_hal_device, pst_channel->en_band);

    /* 设置带宽 */
#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
        /*dummy*/
#else
    if (pst_channel->en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{mac_fcs_set_channel:: fpga is not support 80M.}\r\n");
        pst_channel->en_bandwidth = WLAN_BAND_WIDTH_20M;
    }
#endif
    hal_set_bandwidth_mode(pst_hal_device, pst_channel->en_bandwidth);

    /* 设置信道号 */
    hal_set_primary_channel(pst_hal_device, pst_channel->uc_chan_number, pst_channel->en_band, pst_channel->uc_idx, pst_channel->en_bandwidth);

    /* 打开pa */
    //hal_enable_machw_phy_and_pa(pst_hal_device);
    //OAM_WARNING_LOG0(0, OAM_SF_DBAC, "{mac_fcs_set_channel::after set channel enable pa!}");

    /* 开中断 */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_MFSC);

#ifdef _PRE_WLAN_DFT_EVENT
    oam_event_chan_report(pst_channel->uc_chan_number);
#endif
    OAM_INFO_LOG1(0, OAM_SF_ANY, "fcs_event: switch chan to:%d", pst_channel->uc_chan_number);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_fcs_init
 功能描述  : FCS初始化接口
 输入参数  : mac_fcs_mgr_stru  *pst_fcs_mgr
             oal_uint8           uc_chip_id
             oal_uint8           uc_device_id
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32    mac_fcs_init(mac_fcs_mgr_stru  *pst_fcs_mgr,
                            oal_uint8         uc_chip_id,
                            oal_uint8         uc_device_id)
{
    oal_uint8        uc_idx;

    if (OAL_PTR_NULL == pst_fcs_mgr)
    {
        return OAL_FAIL;
    }

    if ((uc_chip_id >= WLAN_CHIP_MAX_NUM_PER_BOARD) || (uc_device_id >= WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC))
    {
        return OAL_FAIL;
    }


    oal_memset(pst_fcs_mgr, 0, sizeof(mac_fcs_mgr_stru));

    oal_spin_lock_init(&pst_fcs_mgr->st_lock);

    pst_fcs_mgr->en_fcs_state   = MAC_FCS_STATE_STANDBY;
    pst_fcs_mgr->pst_fcs_cfg    = OAL_PTR_NULL;
    pst_fcs_mgr->uc_chip_id     = uc_chip_id;
    pst_fcs_mgr->uc_device_id   = uc_device_id;
    pst_fcs_mgr->uc_fcs_cnt     = 0;

    for (uc_idx = 0; uc_idx < MAC_FCS_NOTIFY_TYPE_BUTT; uc_idx++)
    {
        mac_fcs_notify_chain_init(pst_fcs_mgr->ast_notify_chain + uc_idx);
    }

    mac_fcs_verify_init();

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_fcs_request
 功能描述  : 申请占用FCS
 输入参数  : mac_fcs_mgr_stru             *pst_fcs_mgr
             mac_fcs_state_enum_uint8     *puc_state
             mac_fcs_cfg_stru             *pst_fcs_cfg
 输出参数  : 无
 返 回 值  : mac_fcs_err_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
mac_fcs_err_enum_uint8  mac_fcs_request(mac_fcs_mgr_stru             *pst_fcs_mgr,
                                        mac_fcs_state_enum_uint8     *puc_state,
                                        mac_fcs_cfg_stru             *pst_fcs_cfg)
{
    mac_fcs_err_enum_uint8  en_ret;
    //oal_uint                ul_irq_save;

    if (pst_fcs_mgr == OAL_PTR_NULL)
    {
        return MAC_FCS_ERR_NULL_PTR;
    }

    /* 02mips优化，51&02 fcs暂无并发，注掉 */
    //oal_spin_lock_irq_save(&pst_fcs_mgr->st_lock, &ul_irq_save);

    if (puc_state != OAL_PTR_NULL)
    {
        *puc_state = pst_fcs_mgr->en_fcs_state;
    }

    switch (pst_fcs_mgr->en_fcs_state)
    {
        case    MAC_FCS_STATE_STANDBY    :
                    pst_fcs_mgr->en_fcs_state   = MAC_FCS_STATE_REQUESTED;
                    en_ret                      = MAC_FCS_SUCCESS;
                    break;

        case    MAC_FCS_STATE_IN_PROGESS :
                    if (pst_fcs_cfg != OAL_PTR_NULL)
                    {
                        *pst_fcs_cfg = *pst_fcs_mgr->pst_fcs_cfg;
                    }
                    /* no break  */

        case    MAC_FCS_STATE_REQUESTED :
                    en_ret = MAC_FCS_ERR_BUSY;
                    break;

        default:
                    en_ret = MAC_FCS_ERR_UNKNOWN_ERR;
                    break;
    }

    //oal_spin_unlock_irq_restore(&pst_fcs_mgr->st_lock, &ul_irq_save);

    return en_ret;
}
/*****************************************************************************
 函 数 名  : mac_fcs_release
 功能描述  : 释放FCS
 输入参数  : mac_fcs_mgr_stru *pst_fcs_mgr
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_void    mac_fcs_release(mac_fcs_mgr_stru *pst_fcs_mgr)
{
#if 0
    if (pst_fcs_mgr != OAL_PTR_NULL)
    {
        oal_uint    ul_irq_save;

        oal_spin_lock_irq_save(&pst_fcs_mgr->st_lock, &ul_irq_save);
        pst_fcs_mgr->en_fcs_state   = MAC_FCS_STATE_STANDBY;
        oal_spin_unlock_irq_restore(&pst_fcs_mgr->st_lock, &ul_irq_save);
    }
#endif

    pst_fcs_mgr->en_fcs_state = MAC_FCS_STATE_STANDBY;
}

/*****************************************************************************
 函 数 名  : mac_fcs_flush_event_by_channel
 功能描述  : fcs切信道之前flush事件队列
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
OAL_STATIC oal_void  mac_fcs_flush_event_by_channel(mac_device_stru *pst_mac_device, mac_channel_stru *pst_chl)
{
    oal_uint8               uc_vap_idx;
    mac_vap_stru           *pst_mac_vap;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "pst_mac_vap null.", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (mac_fcs_is_same_channel(&(pst_mac_vap->st_channel), pst_chl))
        {
            frw_event_vap_flush_event(pst_mac_vap->uc_vap_id, FRW_EVENT_TYPE_WLAN_TX_COMP, OAL_FALSE);
        }
    }
}

/*****************************************************************************
 函 数 名  : mac_fcs_wait_one_packet_done
 功能描述  : 等待one packet中断
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
OAL_STATIC oal_uint32  mac_fcs_wait_one_packet_done(mac_fcs_mgr_stru *pst_fcs_mgr)
{
    oal_uint32 ul_delay_cnt = 0;

    while (OAL_TRUE != pst_fcs_mgr->en_fcs_done)
    {
        /* en_fcs_done will be set 1 in one_packet_done_isr */
        oal_udelay(10);

        ul_delay_cnt++;

        /* 10us*1000 = 10ms */
        if (ul_delay_cnt > MAC_ONE_PACKET_TIME_OUT)
        {
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "wait one packet done timeout > 10ms !");
            return OAL_FAIL;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_fcs_send_one_packet_start
 功能描述  : 发送一次one packet 报文
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
oal_void mac_fcs_send_one_packet_start(mac_fcs_mgr_stru *pst_fcs_mgr,
                                            hal_one_packet_cfg_stru *pst_one_packet_cfg,
                                            hal_to_dmac_device_stru *pst_device,
                                         hal_one_packet_status_stru *pst_status,
                                                oal_bool_enum_uint8  en_ps)
{
    oal_uint32                  ul_ret;
    mac_ieee80211_frame_stru   *pst_mac_header;

    /* 准备报文 */
    if (HAL_FCS_PROTECT_TYPE_NULL_DATA == pst_one_packet_cfg->en_protect_type)
    {
        pst_mac_header = (mac_ieee80211_frame_stru *)pst_one_packet_cfg->auc_protect_frame;
        pst_mac_header->st_frame_control.bit_power_mgmt = en_ps;
    }

    pst_fcs_mgr->en_fcs_done    = OAL_FALSE;
    mac_fcs_verify_timestamp(MAC_FCS_STAGE_ONE_PKT_START);

    /* 启动发送 */
    hal_one_packet_start(pst_device, pst_one_packet_cfg);
#if ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    pst_fcs_mgr->en_fcs_done = OAL_TRUE;
#endif

    /* 等待发送结束 */
    ul_ret = mac_fcs_wait_one_packet_done(pst_fcs_mgr);
    if (OAL_SUCC != ul_ret)
    {
        hal_show_fsm_info(pst_device);
    }

    mac_fcs_verify_timestamp(MAC_FCS_STAGE_ONE_PKT_DONE);
    if (OAL_PTR_NULL != pst_status)
    {
        hal_one_packet_get_status(pst_device, pst_status);
    }
}

/*****************************************************************************
 函 数 名  : mac_fcs_start
 功能描述  : 启动one packet，将发送队列保存到虚假队列，切信道
 输入参数  : pst_fcs_mgr: fcs mgr
             pst_fcs_cfg: fcs配置
             uc_fake_tx_q_id: 将当前硬件队列帧保存到哪个虚假队列中去
             mac_fcs_cfg_stru    *pst_fcs_cfg
 输出参数  : pst_status: 获取one packet的状态
 返 回 值  : mac_fcs_err_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
mac_fcs_err_enum_uint8    mac_fcs_start(
                mac_fcs_mgr_stru            *pst_fcs_mgr,
                mac_fcs_cfg_stru            *pst_fcs_cfg,
                hal_one_packet_status_stru  *pst_status,
                oal_uint8                    uc_fake_tx_q_id)
{
    hal_to_dmac_device_stru            *pst_device;
    mac_device_stru                    *pst_mac_device;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#if (_PRE_WLAN_CHIP_ASIC != _PRE_WLAN_CHIP_VERSION)
    oal_uint32 							ul_mode_sel;
	oal_uint32 							coex_cnt = 0;
#endif
#endif
    if ((OAL_PTR_NULL == pst_fcs_mgr) || (OAL_PTR_NULL == pst_fcs_cfg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_fcs_start::param null.}");
        return  MAC_FCS_ERR_INVALID_CFG;
    }

    pst_mac_device = mac_res_get_dev(pst_fcs_mgr->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_fcs_start::pst_mac_device null.}");
        return  MAC_FCS_ERR_INVALID_CFG;
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#if (_PRE_WLAN_CHIP_ASIC != _PRE_WLAN_CHIP_VERSION)
    hal_set_btcoex_occupied_period(15000);    // 15ms
    hal_get_btcoex_pa_status(&ul_mode_sel);
    while ((BIT23 == (ul_mode_sel & BIT23)) && (coex_cnt < BT_COEX_RELEASE_TIMEOUT))//wait 10ms for BT release
    {
        oal_udelay(10);
        hal_get_btcoex_pa_status(&ul_mode_sel);
		coex_cnt++;/*10us*/
    }

	if(coex_cnt == BT_COEX_RELEASE_TIMEOUT)
	{
        OAM_WARNING_LOG0(0, OAM_SF_DBAC, "{mac_fcs_start::bt release timeout!}");
	}
    oal_udelay(50);     // delay 50us
#endif
#endif

    pst_device = pst_mac_device->pst_device_stru;

    pst_fcs_mgr->pst_fcs_cfg    = pst_fcs_cfg;
    pst_fcs_mgr->en_fcs_state   = MAC_FCS_STATE_IN_PROGESS;

#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* 深睡眠唤醒后，背景扫描 one packet timeout修改 */
    dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);
#endif
    /* 函数封装 */
    mac_fcs_send_one_packet_start(pst_fcs_mgr, &pst_fcs_mgr->pst_fcs_cfg->st_one_packet_cfg, pst_device, pst_status, OAL_TRUE);

    /* DTS2015080801407 发null data等待ACK时可能导致one packet超时，开关一下pa */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_disable_machw_phy_and_pa(pst_device);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(1 == pst_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        hal_reset_phy_machw(pst_device, HAL_RESET_HW_TYPE_MAC, HAL_RESET_MAC_LOGIC, OAL_FALSE, OAL_FALSE);
    }
#endif
#endif

    /* flush发送完成事件 */
    mac_fcs_flush_event_by_channel(pst_mac_device, &pst_fcs_cfg->st_src_chl);

    /* 保存当前硬件队列的帧到虚假队列 */
    if (uc_fake_tx_q_id < HAL_TX_FAKE_QUEUE_NUM)
    {
        dmac_tx_save_tx_queue(pst_mac_device->pst_device_stru, uc_fake_tx_q_id);
    }

    mac_fcs_verify_timestamp(MAC_FCS_STAGE_RESET_HW_START);
    mac_fcs_set_channel(pst_mac_device,  &pst_fcs_cfg->st_dst_chl);
    hal_reset_nav_timer(pst_device);
    hal_clear_hw_fifo(pst_device);
    hal_one_packet_stop(pst_device);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_enable_machw_phy_and_pa(pst_device);
#endif

    mac_fcs_verify_timestamp(MAC_FCS_STAGE_RESET_HW_DONE);

    pst_fcs_mgr->en_fcs_state   = MAC_FCS_STATE_REQUESTED;
    pst_fcs_mgr->pst_fcs_cfg    = OAL_PTR_NULL;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#if (_PRE_WLAN_CHIP_ASIC != _PRE_WLAN_CHIP_VERSION)
    hal_set_btcoex_occupied_period(0);    // 0us
#endif
#endif

    return MAC_FCS_SUCCESS;
}


/*****************************************************************************
 函 数 名  : mac_fcs_start_enhanced
 功能描述  : 增强版FCS接口，启动两次onepacket 用于双STA背景扫描
 输入参数  : pst_fcs_mgr: fcs mgr
             pst_fcs_cfg: fcs配置
             uc_fake_tx_q_id: 将当前硬件队列帧保存到哪个虚假队列中去
             mac_fcs_cfg_stru    *pst_fcs_cfg
 输出参数  : pst_status: 获取one packet的状态
 返 回 值  : mac_fcs_err_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
mac_fcs_err_enum_uint8    mac_fcs_start_enhanced(
                mac_fcs_mgr_stru            *pst_fcs_mgr,
                mac_fcs_cfg_stru            *pst_fcs_cfg)
{
    hal_to_dmac_device_stru            *pst_device;
    mac_device_stru                    *pst_mac_device;
    hal_one_packet_status_stru          st_status;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#if (_PRE_WLAN_CHIP_ASIC != _PRE_WLAN_CHIP_VERSION)
    oal_uint32                          ul_mode_sel;
    oal_uint32                          coex_cnt = 0;
#endif
#endif

    if ((OAL_PTR_NULL == pst_fcs_mgr) || (OAL_PTR_NULL == pst_fcs_cfg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_fcs_start::param null.}");
        return  MAC_FCS_ERR_INVALID_CFG;
    }

    pst_mac_device = mac_res_get_dev(pst_fcs_mgr->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_fcs_start::pst_mac_device null.}");
        return  MAC_FCS_ERR_INVALID_CFG;
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#if (_PRE_WLAN_CHIP_ASIC != _PRE_WLAN_CHIP_VERSION)
    hal_set_btcoex_occupied_period(15000);    // 15ms
    hal_get_btcoex_pa_status(&ul_mode_sel);
    while ((BIT23 == (ul_mode_sel & BIT23)) && (coex_cnt < BT_COEX_RELEASE_TIMEOUT))//wait 10ms for BT release
    {
        hal_get_btcoex_pa_status(&ul_mode_sel);
        coex_cnt++;/*10us*/
    }

    if(coex_cnt == BT_COEX_RELEASE_TIMEOUT)
    {
        OAM_WARNING_LOG0(0, OAM_SF_DBAC, "{alg_dbac_fcs_event_handler::bt release timeout!}");
    }
    oal_udelay(50);     // delay 50us
#endif
#endif

    pst_device = pst_mac_device->pst_device_stru;

    pst_fcs_mgr->pst_fcs_cfg    = pst_fcs_cfg;
    pst_fcs_mgr->en_fcs_state   = MAC_FCS_STATE_IN_PROGESS;

    /* 第一次启动one packet */
    pst_fcs_mgr->en_fcs_done    = OAL_FALSE;

    hal_one_packet_start(pst_device, &pst_fcs_mgr->pst_fcs_cfg->st_one_packet_cfg);
    mac_fcs_wait_one_packet_done(pst_fcs_mgr);
    hal_one_packet_get_status(pst_device, &st_status);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_disable_machw_phy_and_pa(pst_device);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(1 == pst_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        hal_reset_phy_machw(pst_device, HAL_RESET_HW_TYPE_MAC, HAL_RESET_MAC_LOGIC, OAL_FALSE, OAL_FALSE);
    }
#endif
#endif

    hal_clear_hw_fifo(pst_device);

    /* flush发送完成事件 */
    mac_fcs_flush_event_by_channel(pst_mac_device, &pst_fcs_cfg->st_src_chl);

    dmac_tx_save_tx_queue(pst_mac_device->pst_device_stru, HAL_TX_FAKE_QUEUE_BGSCAN_ID);

    hal_one_packet_stop(pst_device);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_enable_machw_phy_and_pa(pst_device);
#endif

    /* 再一次启动one packet模式 */
    pst_fcs_mgr->en_fcs_done    = OAL_FALSE;

    hal_one_packet_start(pst_device, &pst_fcs_mgr->pst_fcs_cfg->st_one_packet_cfg2);
    mac_fcs_wait_one_packet_done(pst_fcs_mgr);
    hal_one_packet_get_status(pst_device, &st_status);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_disable_machw_phy_and_pa(pst_device);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(1 == pst_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        hal_reset_phy_machw(pst_device, HAL_RESET_HW_TYPE_MAC, HAL_RESET_MAC_LOGIC, OAL_FALSE, OAL_FALSE);
    }
#endif
#endif

    mac_fcs_set_channel(pst_mac_device,  &pst_fcs_cfg->st_dst_chl);
    hal_reset_nav_timer(pst_device);
    hal_one_packet_stop(pst_device);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_enable_machw_phy_and_pa(pst_device);
#endif

    pst_fcs_mgr->en_fcs_state   = MAC_FCS_STATE_REQUESTED;
    pst_fcs_mgr->pst_fcs_cfg    = OAL_PTR_NULL;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#if (_PRE_WLAN_CHIP_ASIC != _PRE_WLAN_CHIP_VERSION)
    hal_set_btcoex_occupied_period(0);    // 0us
#endif
#endif

    return MAC_FCS_SUCCESS;
}

/*****************************************************************************
 函 数 名  : mac_fcs_notify_chain_register
 功能描述  : 注册FCS通知链
 输入参数  : mac_fcs_mgr_stru               *pst_fcs_mgr
             mac_fcs_notify_type_enum_uint8  uc_notify_type
             mac_fcs_hook_id_enum_uint8      en_hook_id
             mac_fcs_notify_func             p_func
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_fcs_notify_chain_register(mac_fcs_mgr_stru               *pst_fcs_mgr,
                                         mac_fcs_notify_type_enum_uint8  uc_notify_type,
                                         mac_fcs_hook_id_enum_uint8      en_hook_id,
                                         mac_fcs_notify_func             p_func)
{
    oal_uint    ul_irq_save;

    if ((uc_notify_type >= MAC_FCS_NOTIFY_TYPE_BUTT) || (en_hook_id >= MAC_FCS_HOOK_ID_BUTT))
    {
        return OAL_FAIL;
    }

    // NOTE:can register new func before old one unregistered
    oal_spin_lock_irq_save(&pst_fcs_mgr->st_lock, &ul_irq_save);
    pst_fcs_mgr->ast_notify_chain[uc_notify_type].ast_notify_nodes[en_hook_id].p_func = p_func;
    oal_spin_unlock_irq_restore(&pst_fcs_mgr->st_lock, &ul_irq_save);

    return  OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : mac_fcs_notify
 功能描述  : 触发FCS通知链
 输入参数  : mac_fcs_mgr_stru                *pst_fcs_mgr
             mac_fcs_notify_type_enum_uint8   uc_notify_type
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_fcs_notify(mac_fcs_mgr_stru                *pst_fcs_mgr,
                          mac_fcs_notify_type_enum_uint8   uc_notify_type)
{
    /* notify特性暂不使用 */
#if 0
    mac_fcs_notify_chain_stru  *pst_chain = pst_fcs_mgr->ast_notify_chain + uc_notify_type;
    mac_fcs_notify_node_stru   *pst_node;
    mac_fcs_notify_func         p_func;
    mac_fcs_event_stru          st_fcs_event;
    oal_uint8                    uc_idx;

    st_fcs_event.uc_notify_type =  uc_notify_type;
    st_fcs_event.uc_chip_id     =  pst_fcs_mgr->uc_chip_id;
    st_fcs_event.uc_device_id   =  pst_fcs_mgr->uc_device_id;
    st_fcs_event.st_fcs_cfg     = *pst_fcs_mgr->pst_fcs_cfg;

    for (uc_idx = 0; uc_idx < MAC_FCS_HOOK_ID_BUTT; uc_idx++)
    {
        pst_node    = pst_chain->ast_notify_nodes + uc_idx;
        p_func      = pst_node->p_func;

        if (p_func)
        {
            p_func(&st_fcs_event);
        }
    }
#endif

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : mac_fcs_notify_chain_unregister
 功能描述  : 注销FCS通知链
 输入参数  : mac_fcs_mgr_stru               *pst_fcs_mgr
             mac_fcs_notify_type_enum_uint8  uc_notify_type
             mac_fcs_hook_id_enum_uint8      en_hook_id
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_fcs_notify_chain_unregister(mac_fcs_mgr_stru               *pst_fcs_mgr,
                                           mac_fcs_notify_type_enum_uint8  uc_notify_type,
                                           mac_fcs_hook_id_enum_uint8      en_hook_id)
{
    oal_uint    ul_irq_save;

    if ((uc_notify_type >= MAC_FCS_NOTIFY_TYPE_BUTT) || (en_hook_id >= MAC_FCS_HOOK_ID_BUTT))
    {
        return OAL_FAIL;
    }

    oal_spin_lock_irq_save(&pst_fcs_mgr->st_lock, &ul_irq_save);
    pst_fcs_mgr->ast_notify_chain[uc_notify_type].ast_notify_nodes[en_hook_id].p_func = OAL_PTR_NULL;
    oal_spin_unlock_irq_restore(&pst_fcs_mgr->st_lock, &ul_irq_save);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : mac_fcs_notify_chain_destroy
 功能描述  : 销毁FCS通知链
 输入参数  : mac_fcs_mgr_stru *pst_fcs_mgr
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 mac_fcs_notify_chain_destroy(mac_fcs_mgr_stru *pst_fcs_mgr)
{
    oal_uint8   uc_idx;
    oal_uint    ul_irq_save;

    oal_spin_lock_irq_save(&pst_fcs_mgr->st_lock, &ul_irq_save);

    for (uc_idx = 0; uc_idx < MAC_FCS_HOOK_ID_BUTT; uc_idx++)
    {
        mac_fcs_notify_chain_init(pst_fcs_mgr->ast_notify_chain + uc_idx);
    }

    oal_spin_unlock_irq_restore(&pst_fcs_mgr->st_lock, &ul_irq_save);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : mac_fcs_get_prot_mode
 功能描述  : 获取保护帧发送模式
 输入参数  : mac_vap_stru *pst_src_vap
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月31日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_fcs_get_prot_mode(mac_vap_stru *pst_src_vap)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : mac_fcs_get_prot_datarate
 功能描述  : 获取保护帧速率
 输入参数  : mac_vap_stru *pst_src_vap
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月31日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_fcs_get_prot_datarate(mac_vap_stru *pst_src_vap)
{
    /* OFDM 6M: 0x004b0113 */
    /* 11b 1M:  0x08000113 */
    if ((!IS_LEGACY_VAP(pst_src_vap)) || (WLAN_BAND_5G == pst_src_vap->st_channel.en_band))
    {
        return 0x004b0113;
    }
    else
    {
        return 0x08000113;
    }
}

/*****************************************************************************
 函 数 名  : mac_fcs_prepare_one_packet_cfg
 功能描述  : 准备one packet参数
 输入参数  : us_protect_time: ms, 用于设置CTS的duration
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  mac_fcs_prepare_one_packet_cfg(
                mac_vap_stru                *pst_mac_vap,
                hal_one_packet_cfg_stru     *pst_one_packet_cfg,
                oal_uint16                   us_protect_time)
{
    oal_uint32  ul_duration;

    ul_duration = ((oal_uint32)us_protect_time) << 10;

    pst_one_packet_cfg->en_protect_type    = mac_fcs_get_protect_type(pst_mac_vap);
    pst_one_packet_cfg->en_protect_cnt     = mac_fcs_get_protect_cnt(pst_mac_vap);
    pst_one_packet_cfg->ul_tx_mode         = mac_fcs_get_prot_mode(pst_mac_vap);
    pst_one_packet_cfg->ul_tx_data_rate    = mac_fcs_get_prot_datarate(pst_mac_vap);
    pst_one_packet_cfg->us_duration        = (oal_uint16)OAL_MIN(ul_duration, MAC_FCS_CTS_MAX_DURATION);
    pst_one_packet_cfg->us_timeout         = MAC_FCS_DEFAULT_PROTECT_TIME_OUT;

    if (HAL_FCS_PROTECT_TYPE_NULL_DATA == pst_one_packet_cfg->en_protect_type)
    {
        /* DTS2015081100355 背景扫描发送的null data BSSID填错，改为0x1100表示ToAP */
        mac_null_data_encap(pst_one_packet_cfg->auc_protect_frame,
                    (WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA | 0x1100),
                    pst_mac_vap->auc_bssid,
                    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    }
}


#ifdef _PRE_WLAN_FEATURE_DBAC
/*****************************************************************************
 函 数 名  : alg_dbac_get_fake_q_id
 功能描述  : 根据vap获取虚假队列q id
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月9日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_fcs_get_fake_q_id(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_q_id)
{
    mac_device_stru     *pst_mac_device;
    alg_dbac_mgr_stru   *pst_dbac_mgr;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_q_id)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dbac_mgr = alg_dbac_get_mgr_stru(pst_mac_device);
    if (OAL_PTR_NULL == pst_dbac_mgr)
    {
        OAM_WARNING_LOG0(0, OAM_SF_DBAC, "pst_dbac_mgr == NULL");
        return OAL_FAIL;
    }

    if (pst_dbac_mgr->ast_fcs_cfg[0].st_src_chl.uc_chan_number == pst_mac_vap->st_channel.uc_chan_number)
    {
        *puc_q_id = 0;
    }
    else
    {
        *puc_q_id = 1;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : mac_fcs_update_dbac_config
 功能描述  : 更新dbac运行中的信道配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月7日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  mac_fcs_update_dbac_config(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru     *pst_mac_device;
    alg_dbac_mgr_stru   *pst_dbac_mgr;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_fcs_update_dbac_config::pst_mac_device[%d] is NULL!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (!mac_is_dbac_running(pst_mac_device))
    {
        return OAL_FAIL;
    }

    pst_dbac_mgr = alg_dbac_get_mgr_stru(pst_mac_device);
    if (OAL_PTR_NULL == pst_dbac_mgr)
    {
        OAM_WARNING_LOG0(0,OAM_SF_ANY,"{mac_fcs_update_dbac_config::alg_dbac_get_mgr_stru fail}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_mac_vap->uc_vap_id == pst_dbac_mgr->st_dbac_cfg.auc_mac_vap_id[0])
    {
        pst_dbac_mgr->ast_fcs_cfg[0].st_src_chl = pst_mac_vap->st_channel;
        pst_dbac_mgr->ast_fcs_cfg[1].st_dst_chl = pst_mac_vap->st_channel;
    }
    else if (pst_mac_vap->uc_vap_id == pst_dbac_mgr->st_dbac_cfg.auc_mac_vap_id[1])
    {
        pst_dbac_mgr->ast_fcs_cfg[1].st_src_chl = pst_mac_vap->st_channel;
        pst_dbac_mgr->ast_fcs_cfg[0].st_dst_chl = pst_mac_vap->st_channel;
    }
    else
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_DBAC, "mac_fcs_update_dbac_config: wrong vap id. mac_vap_id[0]:%d, mac_vap_id[1]:%d",
                        pst_dbac_mgr->st_dbac_cfg.auc_mac_vap_id[0],
                        pst_dbac_mgr->st_dbac_cfg.auc_mac_vap_id[1]);
    }

    OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_DBAC, "mac_fcs_update_dbac_config. new vap chan_num:%d, band:%d, bw:%d",
                    pst_mac_vap->st_channel.uc_chan_number,
                    pst_mac_vap->st_channel.en_bandwidth,
                    pst_mac_vap->st_channel.en_band);

    return OAL_SUCC;
}

#endif



/*lint -e578*//*lint -e19*/
oal_module_symbol(mac_fcs_init);
oal_module_symbol(mac_fcs_request);
oal_module_symbol(mac_fcs_release);
oal_module_symbol(mac_fcs_start);
oal_module_symbol(mac_fcs_send_one_packet_start);
oal_module_symbol(mac_fcs_notify_chain_register);
oal_module_symbol(mac_fcs_notify);
oal_module_symbol(mac_fcs_notify_chain_unregister);
oal_module_symbol(mac_fcs_notify_chain_destroy);
oal_module_symbol(mac_fcs_set_channel);
oal_module_symbol(mac_fcs_get_prot_mode);
oal_module_symbol(mac_fcs_get_prot_datarate);
#ifdef _PRE_WLAN_FEATURE_DBAC
oal_module_symbol(mac_fcs_get_fake_q_id);
oal_module_symbol(mac_fcs_update_dbac_config);
#endif


#if (_PRE_TEST_MODE_BOARD_ST == _PRE_TEST_MODE)

OAL_STATIC mac_fcs_verify_stat_stru   g_st_fcs_verify_stat;

/*****************************************************************************
 函 数 名  : mac_fcs_verify_init
 功能描述  : 初始化统计
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月19日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_fcs_verify_init(oal_void)
{
    OAL_MEMZERO(&g_st_fcs_verify_stat, OAL_SIZEOF(g_st_fcs_verify_stat));

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)

#else
    oal_5115timer_init();
#endif
}

/*****************************************************************************
 函 数 名  : mac_fcs_verify_start
 功能描述  : 开始统计
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月19日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_fcs_verify_start(oal_void)
{
    OAL_MEMZERO(&g_st_fcs_verify_stat, OAL_SIZEOF(g_st_fcs_verify_stat));

    g_st_fcs_verify_stat.en_enable = OAL_TRUE;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#if (!defined(_PRE_PC_LINT) && !defined(WIN32))
    enable_cycle_counter();
#endif
#endif

}

/*****************************************************************************
 函 数 名  : mac_fcs_verify_timestamp
 功能描述  : 打时间戳
 输入参数  : mac_fcs_stage_enum_uint8 en_stage
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月19日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_fcs_verify_timestamp(mac_fcs_stage_enum_uint8 en_stage)
{
    if(g_st_fcs_verify_stat.en_enable)
    {
        if(g_st_fcs_verify_stat.ul_item_cnt < MAC_FCS_VERIFY_MAX_ITEMS)
        {
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#if (!defined(_PRE_PC_LINT) && !defined(WIN32))
            g_st_fcs_verify_stat.aul_timestamp[g_st_fcs_verify_stat.ul_item_cnt][en_stage] = get_cycle_count();
#endif
#else
            g_st_fcs_verify_stat.aul_timestamp[g_st_fcs_verify_stat.ul_item_cnt][en_stage] = ~0 - oal_5115timer_get_10ns();
#endif
        }
        else
        {
            mac_fcs_verify_stop();
        }

        if(en_stage == MAC_FCS_STAGE_COUNT-1)
        {
            g_st_fcs_verify_stat.ul_item_cnt++;
        }
    }
}

/*****************************************************************************
 函 数 名  : mac_fcs_verify_stop
 功能描述  : 停止统计
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月19日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_void mac_fcs_verify_stop(oal_void)
{
    oal_uint16  us_item_idx;
    oal_uint16  us_stage_idx;

    g_st_fcs_verify_stat.en_enable = OAL_FALSE;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#if (!defined(_PRE_PC_LINT) && !defined(WIN32))
    disable_cycle_counter();
#endif
#endif

    for(us_item_idx = 0; us_item_idx < g_st_fcs_verify_stat.ul_item_cnt; us_item_idx++)
    {
        for(us_stage_idx = 0; us_stage_idx < MAC_FCS_STAGE_COUNT; us_stage_idx++)
        {
            oal_uint32 *pst_tmp = g_st_fcs_verify_stat.aul_timestamp[us_item_idx];

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
            OAL_REFERENCE(pst_tmp);
            OAL_IO_PRINT("%d ", us_stage_idx == 0 ? 0 : (pst_tmp[us_stage_idx] - pst_tmp[us_stage_idx-1])/80);
#else
            OAL_IO_PRINT("%d ", us_stage_idx == 0 ? pst_tmp[us_stage_idx] : pst_tmp[us_stage_idx] - pst_tmp[us_stage_idx-1]);
#endif
        }

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        OAL_IO_PRINT(" sum=%d us\r\n", (g_st_fcs_verify_stat.aul_timestamp[us_item_idx][MAC_FCS_STAGE_EVENT_DONE] - g_st_fcs_verify_stat.aul_timestamp[us_item_idx][MAC_FCS_STAGE_INTR_START])/80);
#else
        OAL_IO_PRINT(" sum=%d\r\n", g_st_fcs_verify_stat.aul_timestamp[us_item_idx][MAC_FCS_STAGE_EVENT_DONE] - g_st_fcs_verify_stat.aul_timestamp[us_item_idx][MAC_FCS_STAGE_INTR_START]);
#endif

    }
}
/*lint -e19 */
oal_module_symbol(mac_fcs_verify_start);
oal_module_symbol(mac_fcs_verify_timestamp);
oal_module_symbol(mac_fcs_verify_stop);
#endif



#ifdef  __cplusplus
#if     __cplusplus
    }
#endif
#endif
