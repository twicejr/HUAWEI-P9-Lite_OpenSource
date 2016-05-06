


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"

#ifdef _PRE_WLAN_DFT_REG
#include "hal_witp_debug.h"
#endif

#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif

#include "dmac_ext_if.h"
#include "dmac_device.h"
#include "dmac_main.h"
#include "dmac_config.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_mgmt_sta.h"
#include "dmac_rx_data.h"
#include "dmac_tx_complete.h"
#include "dmac_beacon.h"
#include "dmac_scan.h"
#include "dmac_acs.h"
#include "dmac_stat.h"
#include "dmac_chan_mgmt.h"
#include "dmac_blockack.h"
#include "dmac_scan.h"
#include "frw_task.h"

#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#endif

#ifdef _PRE_WLAN_FEATURE_TXOPPS
#include "dmac_txopps.h"
#endif

#ifdef _PRE_WLAN_DFT_STAT
#include "dmac_dft.h"
#endif

#include "dmac_reset.h"

#include "dmac_data_acq.h"
#include "dmac_rx_filter.h"



#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#include "dmac_hcc_adapt.h"
#include "mac_board.h"
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif

#include "dmac_dfx.h"

#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
#include "oal_profiling.h"
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "pm_extern.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MAIN_C



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* dmac模块板子的全局控制变量 */
mac_board_stru g_st_dmac_board;

oal_uint32 g_device_main_init = 0;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_int32 dmac_hcc_adapt_init(oal_void);
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
 函 数 名  : dmac_cfg_vap_init_event
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_cfg_vap_init_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru        *pst_event;             /* 事件结构体 */
    mac_device_stru       *pst_device;
    dmac_vap_stru         *pst_dmac_vap;
    frw_event_mem_stru    *pst_event_mem_rate;

    //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_cfg_vap_init_event::func enter.}");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_cfg_vap_init_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_cfg_vap_init_event::pst_device is null ,device_id:%d.}", pst_event->st_event_hdr.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 分配dmac vap内存空间 */
    mac_res_alloc_dmac_vap(pst_event->st_event_hdr.uc_vap_id);
    pst_device->uc_cfg_vap_id = pst_event->st_event_hdr.uc_vap_id;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_device->uc_cfg_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_cfg_vap_init_event::pst_dmac_vap is null ,vap_id:%d.}", pst_device->uc_cfg_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if(MAC_VAP_VAILD == pst_dmac_vap->st_vap_base_info.uc_init_flag)
    {
        OAM_ERROR_LOG0(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{dmac_cfg_vap_init_event::cfg vap maybe double init!}");
    }
#endif

    /*VAP 初始清零 */
    OAL_MEMZERO(((oal_uint8 *)pst_dmac_vap), OAL_SIZEOF(dmac_vap_stru));

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* 统计信息清零 */
    oam_stats_clear_vap_stat_info(pst_device->uc_cfg_vap_id);
#endif

    /* 初始化cfg_vap信息 */
{
    mac_cfg_add_vap_param_stru  st_param = {0};       /* 构造配置VAP参数结构体 */
    st_param.en_vap_mode = WLAN_VAP_MODE_CONFIG;
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    st_param.bit_11ac2g_enable = OAL_TRUE;
#endif
    mac_vap_init(&(pst_dmac_vap->st_vap_base_info), pst_device->uc_chip_id, pst_device->uc_device_id, pst_device->uc_cfg_vap_id, &st_param);
}
#if 0
    /* 统计信息清零 */
    pst_dmac_vap->st_vap_base_info.uc_chip_id     = pst_device->uc_chip_id;
    pst_dmac_vap->st_vap_base_info.uc_device_id   = pst_device->uc_device_id;
    pst_dmac_vap->st_vap_base_info.uc_vap_id      = pst_device->uc_cfg_vap_id;
    pst_dmac_vap->st_vap_base_info.en_vap_mode    = WLAN_VAP_MODE_CONFIG;
#endif



#if 0
    /* 此时，dmac device初始化完成 */
    pst_device->en_device_state = OAL_TRUE;
#endif
    //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_cfg_vap_init_event::func out.}");
#if 1
	/* 1102 需要在device初始化成功后同步速率级 */
	pst_event_mem_rate = FRW_EVENT_ALLOC(0);
	if (OAL_PTR_NULL == pst_event_mem_rate)
	{
		OAL_IO_PRINT("hi1102_device_main_init: dmac_init_event_process FRW_EVENT_ALLOC result = OAL_PTR_NULL.\n");
		return OAL_FAIL;
	}
	if (OAL_SUCC != dmac_init_event_process(pst_event_mem_rate))
	{
		OAL_IO_PRINT("dmac_cfg_vap_init_event: dmac_init_event_process result = fale.\n");
		FRW_EVENT_FREE(pst_event_mem_rate);
		return OAL_FAIL;
	}

	FRW_EVENT_FREE(pst_event_mem_rate);
#endif
    return OAL_SUCC;
}
#endif


#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_init_event_create_cfg_vap
 功能描述  : hmac 抛给dmac的创建配置VAP事件, 只有offload情况下才会用到
 输入参数  : pst_event_mem: 事件结构体
 输出参数  :

 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : c00178899
    修改内容   : 新生成函数
  2.日    期   : 2014年10月22日
    作    者   : z00273164
    修改内容   : cfg_vap初始化只需要更新device chip id

*****************************************************************************/
oal_uint32 dmac_init_event_create_cfg_vap(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru        *pst_event;             /* 事件结构体 */
    mac_device_stru       *pst_device;
    oal_uint8              uc_vap_idex = 0;
    dmac_vap_stru         *pst_dmac_vap;

    //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_init_event_create_cfg_vap::func enter.}");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_init_event_create_cfg_vap::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_init_event_create_cfg_vap::pst_device is null ,device_id:%d.}", pst_event->st_event_hdr.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 分配dmac vap内存空间 */
    mac_res_alloc_dmac_vap(&uc_vap_idex);
    pst_device->uc_cfg_vap_id = uc_vap_idex;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_device->uc_cfg_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_init_event_create_cfg_vap::pst_dmac_vap is null ,vap_id:%d.}", pst_device->uc_cfg_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*VAP 初始清零 */
    OAL_MEMZERO(((oal_uint8 *)pst_dmac_vap), OAL_SIZEOF(dmac_vap_stru));

    /* 初始化cfg_vap信息 */
    pst_dmac_vap->st_vap_base_info.uc_chip_id     = pst_device->uc_chip_id;
    pst_dmac_vap->st_vap_base_info.uc_device_id   = pst_device->uc_device_id;
    pst_dmac_vap->st_vap_base_info.uc_vap_id      = pst_device->uc_cfg_vap_id;
    pst_dmac_vap->st_vap_base_info.en_vap_mode    = WLAN_VAP_MODE_CONFIG;

    /* 此时，dmac device初始化完成 */
    pst_device->en_device_state = OAL_TRUE;
    //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_init_event_create_cfg_vap::func out.}");

    return OAL_SUCC;
}
#endif
#endif //mac公共函数整改


#ifdef _PRE_WLAN_REALTIME_CALI
/*****************************************************************************
 函 数 名  : dmac_rf_cali_realtime_timeout
 功能描述  : realtime校准超时入口函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月10日
    作    者   : z00285102
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_rf_realtime_cali_timeout(oal_void * p_arg)
{
    mac_device_stru           *pst_mac_device = (mac_device_stru *)p_arg;
    hal_to_dmac_device_stru   *pst_hal_device;
    oal_uint8                  uc_channel_idx;
    dmac_vap_stru             *pst_dmac_vap = OAL_PTR_NULL;
    oal_uint32                 ul_ret;

    pst_hal_device = pst_mac_device->pst_device_stru;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[0]);

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        return  OAL_SUCC;
    }

    if((WLAN_BAND_2G == pst_mac_device->en_max_band) || (WLAN_BAND_5G == pst_mac_device->en_max_band))
    {
        ul_ret = mac_get_channel_idx_from_num(pst_mac_device->en_max_band, pst_mac_device->uc_max_channel, &uc_channel_idx);
        if (OAL_SUCC != ul_ret)
        {
            return OAL_FAIL;
        }
    }

    hal_rf_cali_realtime(pst_hal_device,
                         pst_mac_device->en_max_band,
                         uc_channel_idx,
                         pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth,
                         pst_dmac_vap->st_vap_base_info.en_protocol);

    dmac_alg_cfg_channel_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_MOVE_WORK);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_init_hardware
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月30日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_init_hardware(mac_board_stru *pst_board)
{
    oal_uint8                  uc_chip_idx;
    oal_uint8                  uc_device;
    mac_chip_stru             *pst_chip;
    mac_device_stru           *pst_dev;
    hal_to_dmac_device_stru   *pst_hal_device;
    oal_uint8                  uc_chip_id_bitmap = pst_board->uc_chip_id_bitmap;

    while (0 != uc_chip_id_bitmap)
    {
        /* 获取最右边一位为1的位数，此值即为chip的数组下标 */
        uc_chip_idx = oal_bit_find_first_bit_one_byte(uc_chip_id_bitmap);
        if (OAL_UNLIKELY(uc_chip_idx >= WLAN_CHIP_MAX_NUM_PER_BOARD))
        {
            OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_init_hardware::invalid uc_chip_idx[%d] uc_chip_id_bitmap=%d.}",
                           uc_chip_idx, pst_board->uc_chip_id_bitmap);

            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }

        pst_chip = &pst_board->ast_chip[uc_chip_idx];

        for (uc_device = 0; uc_device < pst_chip->uc_device_nums; uc_device++)
        {
            if(uc_device >= WLAN_DEVICE_MAX_NUM_PER_CHIP)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_init_hardware::array overflow,uc_device count[%d] is exceeded.}",
                    uc_device);
                return OAL_ERR_CODE_ARRAY_OVERFLOW;
            }
            pst_dev = mac_res_get_dev(pst_chip->auc_device_id[uc_device]);

            if (OAL_PTR_NULL == pst_dev)
            {
                MAC_WARNING_LOG(0, "dmac_init_hardware: pst_dev is null ptr.");
                OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_init_hardware::pst_dev null.}");

                continue;
            }

            pst_hal_device = pst_dev->pst_device_stru;

            /* 使能PA和PHY的工作 */
            hal_enable_machw_phy_and_pa(pst_hal_device);
#ifdef _PRE_WLAN_FEATURE_STA_PM
            g_us_PmWifiSleepRfPwrOn = WLAN_NOT_SLEEP;
#endif
        }

        #ifdef _PRE_WLAN_REALTIME_CALI
        if (1 == pst_hal_device->ul_dync_txpower_flag)
        {
            FRW_TIMER_CREATE_TIMER(&(pst_dev->st_realtime_cali_timer),
                                    dmac_rf_realtime_cali_timeout,
                                    WLAN_REALTIME_CALI_INTERVAL,
                                    pst_dev,
                                    OAL_TRUE,
                                    OAM_MODULE_ID_DMAC,
                                    pst_dev->ul_core_id);
        }
        #endif

        /* 清除对应的bitmap位 */
        oal_bit_clear_bit_one_byte(&uc_chip_id_bitmap, uc_chip_idx);
    }

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_init_event_process
 功能描述  : hmac 抛给dmac的初始化事件
 输入参数  : pst_event_mem: 事件结构体
 输出参数  :

 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : c00178899
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_init_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru        *pst_event;             /* 事件结构体 */
    oal_uint32             ul_relt;
    mac_device_stru       *pst_mac_device;
    dmac_tx_event_stru    *pst_dtx_event;
    oal_netbuf_stru       *pst_netbuf;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_init_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_INIT,
                       WLAN_MEM_EVENT_SIZE1,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       0,0,0);

    /* 申请netbuf，存放速率级信息 */
    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, sizeof(mac_data_rate_stru) * MAC_DATARATES_PHY_80211G_NUM, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_init_event_process::pst_netbuf null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(0);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_init_event_process::pst_mac_device null.}");
        oal_netbuf_free(pst_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*************************************************************************/
    /*            netbuf data域的上报的data rate                */
    /* --------------------------------------------------------------------  */
    /*              | st_mac_rates_11g info     |                            */
    /* --------------------------------------------------------------------  */
    /*              | sizeof(mac_data_rate_stru) |                            */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /* 清空cb字段 */
    OAL_MEMZERO(oal_netbuf_cb(pst_netbuf), OAL_TX_CB_LEN);

    /* 将速率集的信息拷贝到netbuf中，上报hmac */
    oal_memcopy((oal_uint8 *)((oal_uint8 *)(OAL_NETBUF_DATA(pst_netbuf))),
                (oal_uint8 *)(pst_mac_device->st_mac_rates_11g),
                sizeof(mac_data_rate_stru) * MAC_DATARATES_PHY_80211G_NUM);

    /* 业务事件信息 */
    pst_dtx_event               = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_dtx_event->pst_netbuf   = pst_netbuf;
    pst_dtx_event->us_frame_len = sizeof(mac_data_rate_stru) * MAC_DATARATES_PHY_80211G_NUM;

    OAL_IO_PRINT("chip0, chip_ver[0x%x]\n", g_st_dmac_board.ast_chip[0].ul_chip_ver);
    OAL_IO_PRINT("pst_dtx_event->us_frame_len[%u]\n", pst_dtx_event->us_frame_len);

    frw_event_dispatch_event(pst_event_mem);

    ul_relt = dmac_init_hardware(&g_st_dmac_board);

    if (OAL_SUCC == ul_relt)
    {
        g_device_main_init = 1;
        frw_set_init_state(FRW_INIT_STATE_ALL_SUCC);
    }

    return ul_relt;
}
#else
/*****************************************************************************
 函 数 名  : dmac_init_event_process
 功能描述  : hmac 抛给dmac的初始化事件
 输入参数  : pst_event_mem: 事件结构体
 输出参数  :

 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月15日
    作    者   : c00178899
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_init_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru        *pst_event;             /* 事件结构体 */
    oal_uint32             ul_relt;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru       *pst_mac_device;
    dmac_tx_event_stru    *pst_dtx_event;
    oal_netbuf_stru       *pst_netbuf;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_init_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_INIT,
                       WLAN_MEM_EVENT_SIZE1,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       0,0,0);

     /* 将chip结构体发给HMAC */
    oal_memcopy(pst_event->auc_event_data,
                g_st_dmac_board.ast_chip,
                OAL_SIZEOF(mac_chip_stru) * WLAN_CHIP_MAX_NUM_PER_BOARD);

    frw_event_dispatch_event(pst_event_mem);

    ul_relt = dmac_init_hardware(&g_st_dmac_board);


    return ul_relt;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_sdt_recv_reg_cmd
 功能描述  : dmac处理hmac抛来的SDT下发读写寄存器命令
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月31日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_sdt_recv_reg_cmd(frw_event_mem_stru *pst_event_mem)
{
    oal_uint32                ul_reg_val = 0;
    oal_uint32               *pst_reg_val;
    frw_event_stru           *pst_event_down;
    frw_event_stru           *pst_event_up;
    mac_device_stru          *pst_mac_device;
    dmac_sdt_reg_frame_stru  *pst_reg_frame;
    frw_event_mem_stru       *pst_event_memory;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_sdt_recv_reg_cmd::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_down     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_reg_frame = (dmac_sdt_reg_frame_stru *)pst_event_down->auc_event_data;

    pst_mac_device  = mac_res_get_dev(pst_event_down->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_sdt_recv_reg_cmd::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_SDT_MODE_WRITE == pst_reg_frame->uc_mode)
    {

       hal_reg_write(pst_mac_device->pst_device_stru, pst_reg_frame->ul_addr, pst_reg_frame->ul_reg_val);

    }
    else if (MAC_SDT_MODE_READ == pst_reg_frame->uc_mode)
    {
        hal_reg_info(pst_mac_device->pst_device_stru, pst_reg_frame->ul_addr, &ul_reg_val);

        /* 将读取到的寄存器值抛事件给hmac */
        pst_event_memory = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint32));
        if (OAL_PTR_NULL == pst_event_memory)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_sdt_recv_reg_cmd::pst_event_memory null.}");

            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_event_up = (frw_event_stru *)pst_event_memory->puc_data;

        /* 填写事件头 */
        FRW_EVENT_HDR_INIT(&(pst_event_up->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_SDT_REG,
                       DMAC_TO_HMAC_SYN_UP_REG_VAL,
                       OAL_SIZEOF(oal_uint32),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_event_down->st_event_hdr.uc_chip_id,
                       pst_event_down->st_event_hdr.uc_device_id,
                       pst_event_down->st_event_hdr.uc_vap_id);

        pst_reg_val = (oal_uint32 *)pst_event_up->auc_event_data;
       *pst_reg_val = ul_reg_val;

        frw_event_dispatch_event(pst_event_memory);
        FRW_EVENT_FREE(pst_event_memory);
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_event_fsm_tx_adapt_subtable_register
 功能描述  : dmac模块事件发送适配函数子表注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : h00217255
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_event_fsm_tx_adapt_subtable_register(oal_void)
{
    /* 注册WLAN_DRX事件子表 */
    g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_STA].p_tx_adapt_func = dmac_proc_wlan_drx_event_tx_adapt;
    g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_AP].p_tx_adapt_func  = dmac_proc_wlan_drx_event_tx_adapt;
    g_ast_hmac_wlan_drx_event_sub_table[DMAC_WLAN_DRX_EVENT_SUB_TYPE_TKIP_MIC_FAILE].p_tx_adapt_func  = dmac_proc_tkip_mic_fail_tx_adapt;

    /* 注册TBTT事件子表 */
    g_ast_hmac_tbtt_event_sub_table[DMAC_TBTT_EVENT_SUB_TYPE].p_tx_adapt_func = dmac_hcc_tx_convert_event_to_netbuf_uint16;

    /* 注册MISC事件子表 */
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_RADAR_DETECT].p_tx_adapt_func = dmac_hcc_tx_convert_event_to_netbuf_uint16;
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_DISASOC].p_tx_adapt_func      = dmac_proc_disasoc_misc_event_tx_adapt;
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_CALI_TO_HMAC].p_tx_adapt_func = dmac_cali2hmac_misc_event_tx_adapt;

#ifdef _PRE_WLAN_FEATURE_ROAM
    g_ast_hmac_wlan_misc_event_sub_table[DMAC_MISC_SUB_TYPE_ROAM_TRIGGER].p_tx_adapt_func = dmac_proc_roam_trigger_event_tx_adapt;
#endif //_PRE_WLAN_FEATURE_ROAM

    /* 注册WLAN_CRX事件子表 */
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_INIT].p_tx_adapt_func = dmac_proc_init_event_process_tx_adapt;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX].p_tx_adapt_func = dmac_proc_crx_event_tx_adapt;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_DELBA].p_tx_adapt_func = dmac_proc_mgmt_rx_delba_event_tx_adapt;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPR_CH_SWITCH_COMPLETE].p_tx_adapt_func = dmac_switch_to_new_chan_complete_tx_adapt;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPR_DBAC].p_tx_adapt_func = dmac_dbac_status_notify_tx_adapt;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_EVERY_SCAN_RESULT].p_tx_adapt_func = dmac_scan_report_scanned_bss_tx_adapt;
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_TO_HMAC_DPD_CALIBRATED_DATA_SEND].p_tx_adapt_func = dmac_dpd_data_cali_tx_adapt;
#endif
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC].p_tx_adapt_func = dmac_rx_send_event_tx_adapt;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH].p_tx_adapt_func   = dmac_rx_send_event_tx_adapt;
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_ALG_INFO_SYN].p_tx_adapt_func = dmac_alg_syn_info_adapt;
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_VOICE_AGGR].p_tx_adapt_func   = dmac_alg_voice_aggr_adapt;
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_OBSS_SCAN_COMP].p_tx_adapt_func = dmac_scan_proc_obss_scan_comp_event_tx_adapt;
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_FLOWCTL_BACKP].p_tx_adapt_func = dmac_alg_flowctl_backp_tx_adapt;
#endif

    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP].p_tx_adapt_func = dmac_scan_proc_scan_comp_event_tx_adapt;
    g_ast_hmac_wlan_crx_event_sub_table[DMAC_WLAN_CRX_EVENT_SUB_TYPE_CHAN_RESULT].p_tx_adapt_func = dmac_proc_chan_result_event_tx_adapt;

    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_DEL_BA].p_tx_adapt_func = dmac_proc_event_del_ba_tx_adapt;
	g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_SYN_CFG].p_tx_adapt_func = dmac_proc_event_config_syn_tx_adapt;
#ifdef _PRE_WLAN_CHIP_TEST_ALG
    g_ast_hmac_wlan_ctx_event_sub_table[DMAC_TO_HMAC_ALG_TEST].p_tx_adapt_func = dmac_alg_ct_result_tx_adapt;
#endif
}

/*****************************************************************************
 函 数 名  : dmac_event_fsm_rx_adapt_subtable_register
 功能描述  : dmac模块事件接收适配处理子表注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : h00217255
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_event_fsm_rx_adapt_subtable_register(oal_void)
{
    /*default reset to dmac_hcc_rx_convert_netbuf_to_event_default*/
    frw_event_sub_rx_adapt_table_init(g_ast_dmac_host_crx_table, 
                                        OAL_SIZEOF(g_ast_dmac_host_crx_table)/OAL_SIZEOF(frw_event_sub_table_item_stru),
                                        dmac_hcc_rx_convert_netbuf_to_event_default);

    frw_event_sub_rx_adapt_table_init(g_ast_dmac_wlan_ctx_event_sub_table, 
                                        OAL_SIZEOF(g_ast_dmac_wlan_ctx_event_sub_table)/OAL_SIZEOF(frw_event_sub_table_item_stru),
                                        dmac_hcc_rx_convert_netbuf_to_event_default);


    /* 注册DMAC模块HOST_DRX事件处理函数表 */
    g_ast_dmac_tx_host_drx[DMAC_TX_HOST_DRX].p_rx_adapt_func = dmac_process_rx_data_event_adapt_default;

    /* 注册DMAC模块WLAN_CTX事件处理函数表 */
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION].p_rx_adapt_func        = dmac_process_rx_data_event_adapt_default;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT].p_rx_adapt_func          = dmac_process_rx_data_event_adapt_default;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCAN_REQ].p_rx_adapt_func = dmac_scan_proc_scan_req_event_rx_adapt;
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_DPD_DATA_PROCESSED].p_rx_adapt_func = dmac_dpd_data_processed_event_rx_adapt;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_CALI_HMAC2DMAC].p_rx_adapt_func = dmac_cali_hmac2dmac_rx_adapt;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCHED_SCAN_REQ].p_rx_adapt_func = dmac_scan_proc_sched_scan_req_event_rx_adapt;

    /* 注册DMAC模块WLAN_DTX事件 */
}

#endif
/*****************************************************************************
 函 数 名  : dmac_event_fsm_action_subtable_register
 功能描述  : dmac模块事件执行函数子表注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : h00217255
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_event_fsm_action_subtable_register(oal_void)
{
    /* 注册DMAC模块HOST_CRX事件 */
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_INIT].p_func = dmac_init_event_process;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#if 0
    /* OFFLOAD情况下用与配置vap同步 */
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_CREATE_CFG_VAP].p_func = dmac_init_event_create_cfg_vap;
#else
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_CREATE_CFG_VAP].p_func = dmac_cfg_vap_init_event;
#endif

#endif

    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_CFG].p_func = dmac_event_config_syn;
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_REG].p_func = dmac_sdt_recv_reg_cmd;

    /* 注册DMAC模块HOST_CRX事件 */
    g_ast_dmac_tx_host_drx[DMAC_TX_HOST_DRX].p_func = dmac_tx_process_data_event;

    /* 注册DMAC模块WLAN_DTX事件处理函数表 */
    g_ast_dmac_tx_wlan_dtx[DMAC_TX_WLAN_DTX].p_func = dmac_tx_process_data_event;

    /* 注册DMAC模块WLAN_CTX事件处理函数表 */
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION].p_func                 = dmac_tx_process_action_event;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_ADD_USER].p_func               = dmac_user_add;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_NOTIFY_ALG_ADD_USER].p_func    = dmac_user_add_notify_alg;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_DEL_USER].p_func               = dmac_user_del;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_BA_SYNC].p_func                   = dmac_rx_process_sync_event;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_PRIV_REQ].p_func               = dmac_rx_process_priv_req_event;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCAN_REQ].p_func               = dmac_scan_proc_scan_req_event;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCHED_SCAN_REQ].p_func         = dmac_scan_proc_sched_scan_req_event;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT].p_func                   = dmac_mgmt_tx_event_process;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_RESET_PSM].p_func              = dmac_psm_reset;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_SET_REG].p_func           = dmac_join_set_reg_event_process;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG].p_func      = dmac_join_set_dtim_reg_event_process;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_ASOC_WRITE_REG].p_func      = dmac_asoc_set_reg_event_process;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_EDCA_REG].p_func       = dmac_mgmt_wmm_update_edca_machw_sta;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_CONN_RESULT].p_func            = dmac_mgmt_conn_result_event;
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_DPD_DATA_PROCESSED].p_func     = dmac_dpd_data_processed_recv;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_CALI_HMAC2DMAC].p_func     = dmac_cali_hmac2dmac_recv;

#if 0
#ifdef _PRE_WLAN_FEATURE_TXOPPS
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_PARTIAL_AID_REG].p_func = dmac_txopps_set_machw_partialaid_sta;
#endif
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SWITCH_TO_NEW_CHAN].p_func     = dmac_chan_initiate_switch_to_new_channel;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WALN_CTX_EVENT_SUB_TYPR_SELECT_CHAN].p_func            = dmac_chan_sync;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WALN_CTX_EVENT_SUB_TYPR_DISABLE_TX].p_func             = dmac_chan_disable_machw_tx_event_process;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WALN_CTX_EVENT_SUB_TYPR_ENABLE_TX].p_func              = dmac_chan_enable_machw_tx_event_process;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_RESTART_NETWORK].p_func        = dmac_chan_restart_network_after_switch_event;
#ifdef _PRE_WLAN_FEATURE_DFS
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_OFF_CHAN].p_func     = dmac_dfs_switch_to_offchan_event_process;
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_HOME_CHAN].p_func    = dmac_dfs_switch_back_event_process;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_DFS_TEST].p_func               = dmac_dfs_test;
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_SMPS].p_func               = dmac_set_smps_process;
#endif

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_PSM_OPMODE_NOTIFY].p_func      = dmac_psm_opmode_notify_process;
#endif
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_RX_FILTER].p_func          = dmac_set_rx_filter_value;

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPR_EDCA_OPT].p_func = dmac_edca_opt_stat_event_process;
#endif

#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    g_ast_dmac_wlan_ctx_event_sub_table[DMAC_WLAN_CTX_EVENT_SUB_TYPE_DSCR_OPT].p_func = dmac_pkt_mem_opt_stat_event_process;
#endif

    /* 注册DMAC模块WLAN_DRX事件子表 */
    g_ast_dmac_wlan_drx_event_sub_table[HAL_WLAN_DRX_EVENT_SUB_TYPE_RX].p_func = dmac_rx_process_data_event;
    g_ast_dmac_wlan_drx_event_sub_table[HAL_WLAN_DRX_EVENT_VAP_INVALID].p_func = dmac_rx_invalid_vap_event;

    /* 注册DMAC模块WLAN_CRX事件子表 */
    g_ast_dmac_wlan_crx_event_sub_table[HAL_WLAN_CRX_EVENT_SUB_TYPE_RX].p_func = dmac_rx_process_data_event;

    /* 注册DMAC模块TX_COMP事件子表 */
    g_ast_dmac_tx_comp_event_sub_table[HAL_TX_COMP_SUB_TYPE_TX].p_func = dmac_tx_complete_event_handler;

    /* 注册DMAC模块TBTT事件字表 */
    g_ast_dmac_tbtt_event_sub_table[HAL_EVENT_TBTT_SUB_TYPE].p_func = dmac_tbtt_event_handler;

    /* 注册DMAC模块ERR事件子表 */
    g_ast_dmac_high_prio_event_sub_table[HAL_EVENT_ERROR_IRQ_MAC_ERROR].p_func = dmac_mac_error_process_event;
    g_ast_dmac_high_prio_event_sub_table[HAL_EVENT_ERROR_IRQ_SOC_ERROR].p_func = dmac_soc_error_process_event;

    /* 注册DMAC模块MISC事件字表 */
    g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_MISC_CH_STATICS_COMP].p_func = dmac_scan_channel_statistics_complete;
    g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_CALI_TO_HMAC].p_func = dmac_cali_to_hmac;

#ifdef _PRE_WLAN_DFT_REG
    g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_REG_REPORT].p_func = dmac_reg_report;
#endif

#ifdef _PRE_WLAN_FEATURE_DFS
    g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_MISC_RADAR_DETECTED].p_func  = dmac_dfs_radar_detect_event;
#endif

    g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_BEACON_TIMEOUT].p_func = dmac_beacon_timeout_event_hander;

#ifdef _PRE_WLAN_FEATURE_P2P
    g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_P2P_NOA_ABSENT_START].p_func  = dmac_p2p_noa_absent_start_event;
    g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_P2P_NOA_ABSENT_END].p_func  = dmac_p2p_noa_absent_end_event;
    g_ast_dmac_misc_event_sub_table[HAL_EVENT_DMAC_P2P_CTWINDOW_END].p_func  = dmac_p2p_oppps_ctwindow_end_event;
#endif
}

/*****************************************************************************
 函 数 名  : dmac_event_fsm_register
 功能描述  : dmac模块事件及其处理函数的注册函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : h00217255
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_event_fsm_register(oal_void)
{

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    /*注册所有事件的tx adapt子表*/
    dmac_event_fsm_tx_adapt_subtable_register();

    /*注册所有事件的rx adapt子表*/
    dmac_event_fsm_rx_adapt_subtable_register();
#endif

    /*注册所有事件的执行函数子表*/
    dmac_event_fsm_action_subtable_register();

    event_fsm_table_register();

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_alg_syn_event_register
 功能描述  : 注册算法配置命令钩子
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月11日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_alg_config_event_register(oal_uint32 p_func(frw_event_mem_stru *))
{
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_ALG].p_func = p_func;
}

/*****************************************************************************
 函 数 名  : dmac_alg_syn_event_register
 功能描述  : 去注册算法配置命令钩子
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月11日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_alg_config_event_unregister(oal_void)
{
    g_ast_dmac_host_crx_table[HMAC_TO_DMAC_SYN_ALG].p_func = OAL_PTR_NULL;
}


#ifdef _PRE_WLAN_DFT_REG

/*****************************************************************************
 函 数 名  : dmac_reg_report
 功能描述  : 上报寄存器数据到app
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_reg_report(frw_event_mem_stru *pst_event_mem)
{

    oam_reg_report();
    return OAL_SUCC;
}

#endif



OAL_STATIC dmac_timeStamp_stru g_ast_dmac_timestamp[WLAN_FRW_MAX_NUM_CORES];

/*****************************************************************************
 函 数 名  : dmac_timestamp_update_timer
 功能描述  : dmac更新时钟
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : caohaibin
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_timestamp_update_timer(oal_void* p_NULL)
{
    oal_uint32 ul_timestamp = 0;   /* 获取硬时钟计数 */
    oal_uint32 ul_offset_ns = 0;   /* 时间差 */
    oal_uint32 ul_usec      = 0;   /* us 计数 */
    oal_uint32 ul_core_id;

    ul_core_id = OAL_GET_CORE_ID();

    ul_timestamp = oal_5115timer_get_10ns();
    ul_offset_ns = g_ast_dmac_timestamp[ul_core_id].ul_last_timestamp - ul_timestamp;
    ul_usec = (oal_uint32)g_ast_dmac_timestamp[ul_core_id].st_timestamp_us.i_usec + ul_offset_ns/100; /*微妙us*/

    /*更新秒*/
    while(ul_usec >= 1000000)
    {
        ul_usec -= 1000000;
        g_ast_dmac_timestamp[ul_core_id].st_timestamp_us.i_sec++;
    }
    /*更新微秒*/
    g_ast_dmac_timestamp[ul_core_id].st_timestamp_us.i_usec = (oal_int32)ul_usec;

    g_ast_dmac_timestamp[ul_core_id].ul_last_timestamp = ul_timestamp;

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : dmac_timestamp_get
 功能描述  : 获取dmac提供的时钟
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : caohaibin
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_timestamp_get(oal_time_us_stru *pst_usec)
{
#if (_PRE_PRODUCT_ID_HI1151 ==_PRE_PRODUCT_ID)
    oal_uint32  ul_core_id;
    ul_core_id = OAL_GET_CORE_ID();

    dmac_timestamp_update_timer(OAL_PTR_NULL);
    pst_usec->i_sec  = g_ast_dmac_timestamp[ul_core_id].st_timestamp_us.i_sec;
    pst_usec->i_usec = g_ast_dmac_timestamp[ul_core_id].st_timestamp_us.i_usec;
#else
    oal_uint64  ull_ts_ms = 0;
    ull_ts_ms = OAL_TIME_GET_STAMP_MS();

    pst_usec->i_sec     = (oal_int) (ull_ts_ms / 1000);
    pst_usec->i_usec    = (oal_int) (ull_ts_ms % 1000) * 1000;
#endif
}

/*****************************************************************************
 函 数 名  : dmac_timestamp_init
 功能描述  : 利用系统提供时钟和硬件时钟结合的方式，维护dmac自身时钟
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : caohaibin
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_timestamp_init(oal_void)
{
    oal_uint32  ul_core_id;

    OAL_MEMZERO((void *)g_ast_dmac_timestamp, OAL_SIZEOF(g_ast_dmac_timestamp));
    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        if (OAL_FALSE == g_ast_dmac_timestamp[ul_core_id].st_timer.en_is_registerd)
        {
            oal_time_get_stamp_us(&g_ast_dmac_timestamp[ul_core_id].st_timestamp_us);
            g_ast_dmac_timestamp[ul_core_id].ul_last_timestamp = oal_5115timer_get_10ns();

            FRW_TIMER_CREATE_TIMER(&g_ast_dmac_timestamp[ul_core_id].st_timer,
                                   dmac_timestamp_update_timer,
                                   1000,               /* 1000ms触发一次 */
                                   (oal_void*)OAL_PTR_NULL,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   ul_core_id);
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_timestamp_exit
 功能描述  : 注销dmac timer的定时器
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : caohaibin
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_timestamp_exit(oal_void)
{
    oal_uint32      ul_core_id;

    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        if (OAL_TRUE== g_ast_dmac_timestamp[ul_core_id].st_timer.en_is_registerd)
        {
    	    FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&g_ast_dmac_timestamp[ul_core_id].st_timer);
        }
    }
}


#if 0 /* 1102 device timer2 test, add by zhangheng */
OAL_STATIC void timer_test_start(void)
{
    enable_cycle_counter();

    Timer_DBAC_start(DBAC_STIME_INDEX, 10000);

    //Timer_Start(DBAC_STIME_INDEX, &g_st_timer_para);
}

OAL_STATIC void timer_test_isr(void)
{
    oal_uint32 ul_ret;

    disable_cycle_counter();

    ul_ret = get_cycle_count();

    //Timer_Stop(DBAC_STIME_INDEX);
    Timer_DBAC_stop(DBAC_STIME_INDEX);

    ul_ret = ul_ret/80;

    OAL_IO_PRINT("timer_test_isr, time is %d us\r\n", ul_ret);

    timer_test_start();
}

OAL_STATIC void timer_test_setup(void)
{
    Timer_DBAC_setup(DBAC_STIME_INDEX, timer_test_isr);
}

#endif
/*****************************************************************************
 函 数 名  : dmac_param_check
 功能描述  : Check the struct and var used in hmac
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC means ok, others failed!
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : z00262551 zhouxinfeng
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 dmac_param_check(oal_void)
{
    /*netbuf's cb size!*/
    oal_uint32 ul_netbuf_cb_size = (oal_uint32)OAL_NETBUF_CB_SIZE();
    if(ul_netbuf_cb_size < (oal_uint32)OAL_SIZEOF(mac_tx_ctl_stru))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "mac_tx_ctl_stru size[%u] large then netbuf cb max size[%u]",
                                    (oal_uint32)OAL_SIZEOF(mac_tx_ctl_stru),ul_netbuf_cb_size);
        return OAL_EFAIL;
    }

    if(ul_netbuf_cb_size < (oal_uint32)OAL_SIZEOF(mac_rx_ctl_stru))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "mac_rx_ctl_stru size[%u] large then netbuf cb max size[%u]",
                                    (oal_uint32)OAL_SIZEOF(mac_rx_ctl_stru),ul_netbuf_cb_size);
        return OAL_EFAIL;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_main_init
 功能描述  : DMAC模块初始化总入口，包含DMAC模块内部所有特性的初始化。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回码，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

  2.日    期   : 2013年5月24日
    作    者   : 张禹
    修改内容   : 删除dmac_event_fsm_register异常分支判断，目前函数无异常返回

*****************************************************************************/
oal_int32  dmac_main_init(oal_void)
{
    frw_init_enum_uint16 en_init_state = 0;
    oal_uint32 ul_ret;

    if(OAL_SUCC != dmac_param_check())
    {
        return -OAL_EFAIL;
    }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if(OAL_SUCC != dmac_hcc_adapt_init())
    {
        return -OAL_EFAIL;
    }
#endif

    /* 资源池初始化*/
    //WLAN_EDA_TRACE_TAG(0x4221UL);
    ul_ret = mac_res_init();
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "dmac_main_init: mac_res_init return err code %d\n", ul_ret);
        frw_timer_delete_all_timer();
        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }

    //WLAN_EDA_TRACE_TAG(0x4222UL);
    dmac_event_fsm_register();

    //WLAN_EDA_TRACE_TAG(0x4223UL);
    en_init_state = frw_get_init_state();
    /* 说明: 在offload方案下，在host侧DMAC也可能存在(部分MIB相关信息挂接)，此时DMAC直接依赖FRW模块，此处状态判断需要修改 */
    if ((FRW_INIT_STATE_BUTT == en_init_state) || (en_init_state < FRW_INIT_STATE_HAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "dmac_main_init:en_init_state error %d\n", en_init_state);
        frw_timer_delete_all_timer();
        event_fsm_unregister();
        mac_res_exit();

        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }

    //WLAN_EDA_TRACE_TAG(0x4224UL);
    /* 如果初始化状态处于配置VAP成功前的状态，表明此次为DMAC第一次初始化，即重加载或启动初始化 */
    if (en_init_state < FRW_INIT_STATE_DMAC_CONFIG_VAP_SUCC)
    {
        dmac_timestamp_init();

        OAL_MEMZERO(&g_st_dmac_board, OAL_SIZEOF(mac_board_stru));

        ul_ret = dmac_board_init(&g_st_dmac_board);
        if (ul_ret != OAL_SUCC)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "dmac_main_init:mac_board_init return fail %d\n.", ul_ret);
            frw_timer_delete_all_timer();
            event_fsm_unregister();
            mac_res_exit();

            OAL_BUG_ON(1);
            return -OAL_EFAIL;
        }

        frw_set_init_state(FRW_INIT_STATE_DMAC_CONFIG_VAP_SUCC);

#ifdef _PRE_WLAN_PERFORM_STAT
        /* 性能统计模块初始化 */
        ul_ret = dmac_stat_init();
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "dmac_stat_init failed \n");
            return OAL_FAIL;
        }
#endif

#ifdef _PRE_WLAN_CHIP_TEST
       dmac_test_init();
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ
        dmac_data_acq_init();
#endif

        dmac_dfx_init();

        dmac_reset_init();

#ifdef _PRE_WLAN_FEATURE_BTCOEX
        dmac_btcoex_init();
#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
        oal_profiling_mips_init();
#endif

        //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_main_init::end func.}");

        /* 1102 device timer2 test, add by zhangheng */
        //timer_test_setup();
        //timer_test_start();

        return OAL_SUCC;
    }

    /* TBD 迭代10 康国昌修改 如果初始化状态为配置VAP成功后的状态，则表明本次为配置触发的初始化，
       需要遍历所有业务VAP，并检查其状态；如未初始化，则需要初始化其相关内容
       如支持特性接口挂接 */
    //WLAN_EDA_TRACE_TAG(0x4225UL);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_main_exit
 功能描述  : DMAC模块卸载
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 模块卸载返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : 康国昌
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_main_exit(oal_void)
{
    oal_uint32           ul_ret;

#ifdef _PRE_WLAN_FEATURE_DAQ
    dmac_data_acq_exit();
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
    /* 性能统计模块卸载 */
    ul_ret = dmac_stat_exit();
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_main_exit::dmac_stat_exit failed.}");

        return;
    }
#endif

    event_fsm_unregister();

    dmac_timestamp_exit();

#if 0
    ul_ret = mac_board_exit(&g_st_dmac_board);
    if (OAL_SUCC != ul_ret)
    {
        return ;
    }
#else
    ul_ret = dmac_board_exit(&g_st_dmac_board);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_main_exit::hmac_board_exit failed[%d].}", ul_ret);
        return ;
    }
#endif

    frw_set_init_state(FRW_INIT_STATE_HAL_SUCC);

    mac_res_exit();

    dmac_dfx_exit();

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_exit();
#endif

    return ;
}

/*lint -e578*//*lint -e19*/
#if (_PRE_PRODUCT_ID_HI1151==_PRE_PRODUCT_ID)
oal_module_init(dmac_main_init);
oal_module_exit(dmac_main_exit);
#endif
oal_module_symbol(dmac_main_init);
oal_module_symbol(dmac_main_exit);
oal_module_symbol(dmac_alg_config_event_register);
oal_module_symbol(dmac_alg_config_event_unregister);
oal_module_symbol(dmac_timestamp_get);
/*lint +e578*//*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

