/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_sta_pm.c
  版 本 号   : 初稿
  作    者   : l00280485
  生成日期   : 2014年11月25日
  最近修改   :
  功能描述   : STA侧节能状态机所在文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "dmac_sta_pm.h"
#include "dmac_psm_sta.h"
#include "dmac_ext_if.h"
#include "mac_resource.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_psm_ap.h"
#include "pm_extern.h"
#include "dmac_p2p.h"
#include "dmac_config.h"
#include "dmac_mgmt_classifier.h"

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif
#include "dmac_pm_sta.h"
#include "frw_timer.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_STA_PM_C

OAL_STATIC oal_void sta_power_state_active_entry(oal_void *p_ctx);
OAL_STATIC oal_void sta_power_state_active_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 sta_power_state_active_event(oal_void  *p_ctx, oal_uint16  us_event,
                                    oal_uint16 us_event_data_len,  oal_void  *p_event_data);
OAL_STATIC oal_void sta_power_state_doze_entry(oal_void *p_ctx);

OAL_STATIC oal_void sta_power_state_doze_exit(oal_void *p_ctx);

OAL_STATIC oal_uint32 sta_power_state_doze_event(oal_void  *p_ctx, oal_uint16  us_event,
                                    oal_uint16 us_event_data_len,  oal_void  *p_event_data);

OAL_STATIC oal_void sta_power_state_awake_entry(oal_void *p_ctx);

OAL_STATIC oal_void sta_power_state_awake_exit(oal_void *p_ctx);

OAL_STATIC oal_uint32 sta_power_state_awake_event(oal_void  *p_ctx, oal_uint16  us_event,
                                    oal_uint16 us_event_data_len,  oal_void  *p_event_data);

oal_void dmac_pm_sta_state_trans(mac_sta_pm_handler_stru* pst_handler,oal_uint8 uc_state, oal_uint16 us_event);
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
oal_uint32                 g_lightsleep_fe_awake_cnt = 0; //浅睡恢复前端计数
oal_uint32                 g_deepsleep_fe_awake_cnt  = 0; //深睡恢复前端计数

/* 全局状态机函数表 */
mac_fsm_state_info  g_sta_power_fsm_info[] = {

    {
        STA_PWR_SAVE_STATE_ACTIVE,
        "ACTIVE",
        sta_power_state_active_entry,
        sta_power_state_active_exit,
        sta_power_state_active_event,
    },

    {
        STA_PWR_SAVE_STATE_DOZE,
        "DOZE",
        sta_power_state_doze_entry,
        sta_power_state_doze_exit,
        sta_power_state_doze_event,
    },
    {
        STA_PWR_SAVE_STATE_AWAKE,
        "AWAKE",
        sta_power_state_awake_entry,
        sta_power_state_awake_exit,
        sta_power_state_awake_event,
    },
};
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_pm_key_info_dump
 功能描述  : 低功耗关键信息打印
 输入参数  : dmac_vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月22日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_pm_key_info_dump(dmac_vap_stru  *pst_dmac_vap)
{
    mac_sta_pm_handler_stru     *pst_mac_sta_pm_handle;

    if ((WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode) || (IS_P2P_DEV(&pst_dmac_vap->st_vap_base_info)))
    {
        return;
    }

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_key_info_dump::pst_mac_sta_pm_handle null}");
        return;
    }

    OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{tbtt_cnt[%d],bcn_cnt[%d],bcn_tout_cnt[%d],b_tout_forbid_sleep_cnt[%d],deep_sleep_cnt[%d].}",
                            5,pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_TBTT_CNT],pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_BEACON_CNT],
                            pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_BEACON_TIMEOUT_CNT],pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_BCNTIMOUT_DIS_ALLOW_SLEEP],
                            pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_DEEP_DOZE_CNT]);
}

/*****************************************************************************
 函 数 名  : dmac_pm_enable_front_end
 功能描述  : 低功耗唤醒前端操作
 输入参数  : p_ctx:状态机上下文，对节能状态机来说为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月14日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_pm_enable_front_end(mac_device_stru *pst_mac_device, oal_uint8 uc_enable_paldo)
{
    oal_uint32                  ulTimeOut;
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    UINT16                      usCpuFreq;

#endif

    if ((WLAN_LIGHT_SLEEP == g_us_PmWifiSleepRfPwrOn) || (WLAN_DEEP_SLEEP == g_us_PmWifiSleepRfPwrOn))
    {

        INT_DisableAll();


        /* wlan iq switch */
        rRF_WB_CTL_ABB_WB_IQ_EXCHANGE_REG = 0x4;
        rRF_WB_CTL_ABB_WB_DAT_PHASE_REG = 0x2;

        /* wlan open rfldo2 */
        PM_WLAN_OpenRfldo2();

        if (OAL_TRUE == g_us_PmEnablePaldo)
        {
            if (OAL_TRUE == uc_enable_paldo)
            {
                /* wlan timer restart */
                frw_timer_restart();

                /* wlan open paldo */
                PM_WLAN_OpenPaldo();

            }

        }

        /* wlan rfldo2 open check */
        ulTimeOut = PM_WLAN_TIMEOUT_INIT;
        while(ERR == PM_WLAN_CheckRfldo2())
        {
           ulTimeOut--;
           if(0 == ulTimeOut)
           {
               PM_WLAN_PRINT("Fail to open rfldo2"NEWLINE);
               break;
           }
        }


#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
        usCpuFreq   =   PM_WLAN_GetMaxCpuFreq();
        PM_WLAN_SetMaxCpuFreq(PM_480MHZ);
        PM_WLAN_SwitchToState(PM_WPF_ID, (PM_WPF_WK | PM_WLAN_GetMaxCpuFreq()));
#endif


        /* 深睡恢复前端 */
        if (WLAN_DEEP_SLEEP == g_us_PmWifiSleepRfPwrOn)
        {
            /* wlan rf awake */
            dmac_psm_rf_awake(OAL_TRUE);
            g_deepsleep_fe_awake_cnt++;
        }
        /* 浅睡恢复前端 */
        else
        {
            dmac_psm_rf_awake(OAL_FALSE);
            g_lightsleep_fe_awake_cnt++;
        }

        if (OAL_TRUE == g_us_PmEnablePaldo)
        {
            if (OAL_TRUE == uc_enable_paldo)
            {
                /* wlan open paldo */
                PM_WLAN_PaldoWorkMode();

                g_us_PmEnablePaldo = OAL_FALSE;
            }
        }

        /* 开启PHY 时钟 */
        PM_Driver_Cbb_PhyCtl_WlanPhyClkOn();

        /* 使能pa */
        hal_enable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

        /* 恢复硬件发送 目前无此功能 */
       //hal_set_machw_tx_resume(pst_mac_device->pst_device_stru);

        g_us_PmWifiSleepRfPwrOn = WLAN_NOT_SLEEP;

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
        PM_WLAN_SetMaxCpuFreq(usCpuFreq);
        PM_WLAN_SwitchToState(PM_WPF_ID, (PM_WPF_WK | PM_WLAN_GetMaxCpuFreq()));
#endif

        INT_EnableAll();

    }

    if (OAL_TRUE == g_us_PmEnablePaldo)
    {
        if (OAL_TRUE == uc_enable_paldo)
        {
            frw_timer_restart();

            /* lilin */
            PM_WLAN_OpenPaldo();
            oal_udelay(120);
            PM_WLAN_PaldoWorkMode();
            g_us_PmEnablePaldo = OAL_FALSE;
        }

    }
}

/*****************************************************************************
 函 数 名  : dmac_pm_process_deassociate
 功能描述  : 处理去关联事件的接口
 输入参数  : p_ctx:状态机上下文，对节能状态机来说为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_pm_process_deassociate(mac_sta_pm_handler_stru* pst_sta_pm_handler)
{
    dmac_vap_stru               *pst_dmac_vap;
    mac_cfg_ps_open_stru         st_ps_open;

    pst_dmac_vap = (dmac_vap_stru *)(pst_sta_pm_handler->p_mac_fsm->p_oshandler);

    if(STA_GET_PM_STATE(pst_sta_pm_handler) != STA_PWR_SAVE_STATE_ACTIVE)
    {
        dmac_pm_sta_state_trans(pst_sta_pm_handler, STA_PWR_SAVE_STATE_ACTIVE, STA_PWR_EVENT_DEASSOCIATE);/* 再设状态 */
    }
    /*去关联后需要关闭协议低功耗否则会在下次重新关联时还会获取dhcp前进入低功耗模式--发睡眠null帧 */
    st_ps_open.uc_pm_enable      = MAC_STA_PM_SWITCH_OFF;
    st_ps_open.uc_pm_ctrl_type   = MAC_STA_PM_CTRL_TYPE_HOST;

    dmac_config_set_sta_pm_on(&(pst_dmac_vap->st_vap_base_info), OAL_SIZEOF(mac_cfg_ps_open_stru), (oal_uint8 *)&st_ps_open);

    /* 由于去关联删除定时器 */
    if(OAL_TRUE == pst_sta_pm_handler->st_inactive_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_sta_pm_handler->st_inactive_timer));
    }

    /* 去关联后输出本次关联过程中的协议低功耗关键统计信息(临时) */
    dmac_pm_key_info_dump(pst_dmac_vap);

    /* 去关联后协议低功耗统计计数清零 */
    OAL_MEMZERO(&(pst_sta_pm_handler->aul_pmDebugCount),OAL_SIZEOF(pst_sta_pm_handler->aul_pmDebugCount));

    /* p2p cl 去关联时恢复深睡,防止noa浅睡最后未收到beacon没有恢复深睡 */
    if (IS_P2P_CL(&(pst_dmac_vap->st_vap_base_info)))
    {
        PM_WLAN_EnableDeepSleep();
    }

    /* 去关联后service id 去注册 */
    hal_pm_wlan_servid_unregister(pst_dmac_vap->pst_hal_vap);
}

/*****************************************************************************
 函 数 名  : dmac_ps_process_send_null_succ_event
 功能描述  : null帧发送成功事件的处理
 输入参数  : pst_pm_handler:对节能状态机结构体 pst_mac_hdr:mac头结构体
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_process_send_null_succ_event(mac_sta_pm_handler_stru  *pst_pm_handler, mac_ieee80211_frame_stru  *pst_mac_hdr)
{
    dmac_vap_stru               *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);

    if (OAL_PTR_NULL == pst_mac_hdr)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_ps_process_send_null_succ_event::pst_mac_hdr NULL.}");
        return;
    }
    /* 收beacon从awake状态切换到active状态发送null帧成功 */
    if (STA_PWR_SAVE_STATE_ACTIVE == pst_mac_hdr->st_frame_control.bit_power_mgmt)
    {
        /* fast_ps才会再次进入active状态 */
        if (OAL_TRUE == pst_pm_handler->st_null_wait.en_active_null_wait)
        {
            pst_pm_handler->st_null_wait.en_active_null_wait  = OAL_FALSE;

            /* active null帧发成功重启activity 定时器 */
            dmac_psm_start_activity_timer(pst_dmac_vap,pst_pm_handler);

            /* No need to track this flag in ACTIVE state */
            pst_pm_handler->en_more_data_expected = OAL_FALSE;

            if (STA_PWR_SAVE_STATE_ACTIVE != STA_GET_PM_STATE(pst_pm_handler))
            {
                dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_ACTIVE, STA_PWR_EVENT_SEND_NULL_SUCCESS);

                /* 睡眠到唤醒的次数统计 */
                pst_pm_handler->aul_pmDebugCount[PM_MSG_WAKE_TO_ACTIVE]++;
            }
        }
    }
    /* 超时函数进入,此时切换到doze状态 */
    else
    {
        if(OAL_TRUE == (pst_pm_handler->st_null_wait.en_doze_null_wait))
        {
            pst_pm_handler->st_null_wait.en_doze_null_wait  = OAL_FALSE;
            pst_pm_handler->en_ps_deep_sleep                = OAL_TRUE;     /* 切换到浅睡 */

            if (STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_pm_handler))
            {
                /* 唤醒到睡眠的次数统计 */
                pst_pm_handler->aul_pmDebugCount[PM_MSG_WAKE_TO_DOZE]++;
            }
            else if (STA_PWR_SAVE_STATE_ACTIVE == STA_GET_PM_STATE(pst_pm_handler))
            {
                /* 唤醒到睡眠的次数统计 */
                pst_pm_handler->aul_pmDebugCount[PM_MSG_ACTIVE_TO_DOZE]++;
            }

            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, STA_PWR_EVENT_SEND_NULL_SUCCESS);
        }
    }

}
/*****************************************************************************
 函 数 名  : sta_power_state_active_entry
 功能描述  : active状态的entry接口
 输入参数  : p_ctx:状态机上下文，对节能状态机来说为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_active_entry(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : sta_power_state_active_exit
 功能描述  : active状态的exit接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_active_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_work_event
 功能描述  : active状态的event接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
             us_event:待处理事件
             us_event_data_len:事件中携带的数据长度
             p_event_data:事件中携带的事件对应的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 sta_power_state_active_event(oal_void   *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    oal_uint32                       ul_ret;
    mac_ieee80211_frame_stru        *pst_mac_hdr;
    dmac_vap_stru                   *pst_dmac_vap = OAL_PTR_NULL;
    mac_device_stru                 *pst_mac_device;

    mac_sta_pm_handler_stru*  pst_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;
    if(OAL_PTR_NULL == pst_pm_handler)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_active_event::pst_pm_handler null.}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);
    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_active_event::pst_dmac_vap null.}");
        return OAL_FAIL;
    }
    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_active_event::pst_mac_device null.}");
        return OAL_FAIL;
    }

    switch(us_event)
    {
        case STA_PWR_EVENT_TIMEOUT:
            //OAM_INFO_LOG0(0, OAM_SF_PWR, "{sta_power_state_active_event::dmac_send_null_frame_to_ap doze}");
            ul_ret = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_DOZE, OAL_FALSE);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_active_event:dmac_send_null_frame_to_ap:[%d].}", ul_ret);

                /* pspoll模式第一个睡眠的null帧发送失败重启睡眠定时器重新发送 */
                dmac_psm_start_activity_timer(pst_dmac_vap,pst_pm_handler);
            }
        break;

        /* active 状态下null帧发送成功重新进入节能模式 */
        case STA_PWR_EVENT_SEND_NULL_SUCCESS:
        	pst_mac_hdr = (mac_ieee80211_frame_stru *)(p_event_data);
            dmac_process_send_null_succ_event(pst_pm_handler, pst_mac_hdr);
        break;

        /* active 下启动keepalive定时器 */
        case STA_PWR_EVENT_KEEPALIVE:
            /* 此时开启keepalive */
            pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_keepalive   =  OAL_TRUE;

            if (OAL_TRUE != pst_pm_handler->st_inactive_timer.en_is_registerd)
            {
                /* 节能下超时时间和非节能下的超时时间不一样，启动定时器 */
                FRW_TIMER_CREATE_TIMER(&(pst_pm_handler->st_inactive_timer),
                                    dmac_psm_alarm_callback,
                                    pst_pm_handler->ul_activity_timeout ,
                                    pst_dmac_vap,
                                    OAL_FALSE,
                                    OAM_MODULE_ID_DMAC,
                                    pst_mac_device->ul_core_id);
            }
        break;

        /* p2p 此时应RESTART active->doze的定时器 */
        case STA_PWR_EVENT_P2P_SLEEP:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_TRUE);

            if ((WLAN_MIB_PWR_MGMT_MODE_PWRSAVE == mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info))) &&
              (OAL_TRUE == dmac_is_sta_fast_ps_enabled(pst_pm_handler)))
            {
                dmac_psm_start_activity_timer(pst_dmac_vap,pst_pm_handler);
            }
        break;

        case STA_PWR_EVENT_P2P_AWAKE:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        break;

        case STA_PWR_EVENT_DEASSOCIATE:
            dmac_pm_process_deassociate(pst_pm_handler);
        break;

        case STA_PWR_EVENT_TX_MGMT:
            dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);
        break;
        default:
        break;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_is_sta_allow_to_sleep
 功能描述  : 允许低功耗状态机的状态切到doze状态,但不允许投票深睡
 输入参数  : pst_device:device pst_dmac_vap:dmac_vap pst_sta_pm_handler:节能状态机
 输出参数  : OAL_TRUE:OAL_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月12日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  dmac_is_sta_allow_to_sleep(mac_device_stru *pst_device, dmac_vap_stru *pst_dmac_vap, mac_sta_pm_handler_stru* pst_sta_pm_handler)
{
    /* 正在扫描不睡眠 */
    if (MAC_SCAN_STATE_RUNNING == pst_device->en_curr_scan_state)
    {
        pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_SCAN_DIS_ALLOW_SLEEP]++;
        return OAL_FALSE;
    }

    /* 睡眠null帧发送成功,低功耗状态机切到doze,但如果不满足深睡条件不投票睡眠 */
    if (OAL_FALSE == pst_sta_pm_handler->uc_can_sta_sleep)
    {
        pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_NULL_NOT_SLEEP]++;
        return OAL_FALSE;
    }

    /* p2p 开启了noa oppps时收beacon时不投睡眠票,仅在noa oppps期间浅睡 */
    if (OAL_TRUE == (oal_uint8)IS_P2P_PS_ENABLED(pst_dmac_vap))
    {
        pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_PSM_P2P_PS]++;
        return OAL_FALSE;
    }

    /* DBAC running 不睡眠 */
    if(OAL_TRUE == mac_is_dbac_running(pst_device))
    {
        pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_DBAC_DIS_ALLOW_SLEEP]++;
        return OAL_FALSE;
    }

    return OAL_TRUE;

}


/*****************************************************************************
 函 数 名  : dmac_power_state_process_doze
 功能描述  : active状态的entry接口
 输入参数  : p_ctx:状态机上下文，对节能状态机来说为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_power_state_process_doze(mac_sta_pm_handler_stru* pst_sta_pm_handler, oal_uint8 uc_ps_mode)
{

    mac_device_stru             *pst_device;
    dmac_vap_stru               *pst_dmac_vap;

    pst_dmac_vap    = (dmac_vap_stru *)(pst_sta_pm_handler->p_mac_fsm->p_oshandler);

    pst_device      = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_psm_check_txrx_state::pst_device[id:0](%p) is NULL!}",
                    pst_dmac_vap->st_vap_base_info.uc_device_id,
                    pst_device);
        return ;
    }


    pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_PROCESS_DOZE_CNT]++;

	if(OAL_FALSE == dmac_is_sta_allow_to_sleep(pst_device,pst_dmac_vap,pst_sta_pm_handler))
	{
		return ;
	}

    if ((pst_sta_pm_handler->en_hw_ps_enable))
    {

        if (STA_PS_DEEP_SLEEP == uc_ps_mode)
        {                  
            pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_DEEP_DOZE_CNT]++;
	        /* 调用平台接口切换到deepsleep 状态 */
			PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_DEEPSLEEP_PROCESS);
	    }
	    else
	    {
            pst_sta_pm_handler->aul_pmDebugCount[PM_MSG_LIGHT_DOZE_CNT]++;
			PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_LIGHTSLEEP_PROCESS);
	    }
	}

#ifdef PM_WLAN_FPGA_DEBUG
    /*睡眠流程时间观测点P12,拉低*/
    //WRITEW(0x50002174,READW(0x50002174)&(~(1<<2)));
#endif

    return;
}

/*****************************************************************************
 函 数 名  : sta_power_state_doze_entry
 功能描述  : active状态的entry接口
 输入参数  : p_ctx:状态机上下文，对节能状态机来说为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_doze_entry(oal_void *p_ctx)
{
    oal_uint8                   uc_ps_mode;
    mac_sta_pm_handler_stru*    pst_sta_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_sta_pm_handler)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_doze_entry::pst_pm_handler null.}");
        return;
    }

    /* 确定是深睡还是浅睡 */
    uc_ps_mode = (OAL_TRUE == pst_sta_pm_handler->en_ps_deep_sleep) ? STA_PS_DEEP_SLEEP : STA_PS_LIGHT_SLEEP;

    /* 将所有缓存帧发送到host,todo */

    /* 处理doze状态下的深睡和浅睡，调用平台的接口 */
    dmac_power_state_process_doze(pst_sta_pm_handler, uc_ps_mode);

    /* Increment the number of STA sleeps */
    //DMAC_STA_PSM_STATS_INCR(pst_sta_pm_handler->st_psm_stat_info.ul_sta_doze_times);
    return;
}

/*****************************************************************************
 函 数 名  : sta_power_state_active_exit
 功能描述  : active状态的exit接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_doze_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_work_event
 功能描述  : active状态的event接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
             us_event:待处理事件
             us_event_data_len:事件中携带的数据长度
             p_event_data:事件中携带的事件对应的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 sta_power_state_doze_event(oal_void   *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    oal_uint32                  ul_ret;
    mac_sta_pm_handler_stru*    pst_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;
    dmac_vap_stru              *pst_dmac_vap;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_doze_event::pst_pm_handler null.}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);
    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_doze_event::pst_dmac_vap null.}");
        return OAL_FAIL;
    }

    switch(us_event)
    {
        /* null帧发送成功此时却是与doze状态的异常处理 */
        case STA_PWR_EVENT_SEND_NULL_SUCCESS:
        case STA_PWR_EVENT_TX_DATA:
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);
            pst_pm_handler->aul_pmDebugCount[PM_MSG_HOST_AWAKE]++;
        break;

        /* DOZE状态下的TBTT事件 */
        case STA_PWR_EVENT_TBTT:
            /* TBTT事件切换到awake状态 */
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);
        break;

        /* 异常处理,fast ps 模式下，切到doze后tbtt中断还未上来唤醒devie，手动唤醒 */
        case STA_PWR_EVENT_FORCE_AWAKE:
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);
        break;

        case STA_PWR_EVENT_P2P_SLEEP:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_TRUE);
        break;

        case STA_PWR_EVENT_P2P_AWAKE:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        break;

        /*非节能模式下，处于doze状态的异常处理 */
        case STA_PWR_EVENT_NO_POWERSAVE:
            if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)
            {
                ul_ret = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_awake_event:dmac_send_null_frame_to_ap:[%d].}", ul_ret);
                }
            }
            //dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);/* 先唤醒 */
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_ACTIVE, us_event);/* 再设状态 */
        break;
        case STA_PWR_EVENT_DEASSOCIATE:
            dmac_pm_process_deassociate(pst_pm_handler);
        break;

        case STA_PWR_EVENT_TX_MGMT:
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_AWAKE, us_event);
        break;
        default:
        break;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : sta_power_state_active_entry
 功能描述  : awake状态的entry接口
 输入参数  : p_ctx:状态机上下文，对节能状态机来说为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_awake_entry(oal_void *p_ctx)
{
    mac_sta_pm_handler_stru*    pst_sta_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;
    dmac_vap_stru               *pst_dmac_vap;
    mac_device_stru             *pst_mac_device;

    if(OAL_PTR_NULL == pst_sta_pm_handler)
    {
        return;
    }

    pst_dmac_vap    = (dmac_vap_stru *)(pst_sta_pm_handler->p_mac_fsm->p_oshandler);

    /* 获取device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_awake_entry::pst_mac_device null.}");
        return;
    }

    if (OAL_TRUE == pst_sta_pm_handler->en_hw_ps_enable)
    {
        //PM_WLAN_PRINT("PSM awake entry vote wakeup"NEWLINE);
        #ifdef HI1102_FPGA
            /*睡眠流程时间观测点P12*/
            //WRITEW(0x50002174,READW(0x50002174)|((1<<2)));
        #endif
        //dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);

    	PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_WORK_PROCESS);
        //frw_timer_restart();

	}
}
/*****************************************************************************
 函 数 名  : sta_power_state_active_exit
 功能描述  : active状态的exit接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void sta_power_state_awake_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 函 数 名  : ap_power_state_work_event
 功能描述  : active状态的event接口
 输入参数  : p_ctx:状态机上下文，节能状态机为pm_handler
             us_event:待处理事件
             us_event_data_len:事件中携带的数据长度
             p_event_data:事件中携带的事件对应的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 sta_power_state_awake_event(oal_void   *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    oal_uint32                           ul_ret;
    mac_ieee80211_frame_stru            *pst_mac_hdr;
    dmac_vap_stru                       *pst_dmac_vap;

    mac_sta_pm_handler_stru*    pst_pm_handler = (mac_sta_pm_handler_stru*)p_ctx;
    if(OAL_PTR_NULL == pst_pm_handler)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_awake_event::pst_pm_handler null}");
        return OAL_FAIL;
    }

    pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);
    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{sta_power_state_awake_event::pst_dmac_vap null}");
        return OAL_FAIL;
    }


    switch(us_event)
    {
        case STA_PWR_EVENT_RX_UCAST:
            ul_ret = dmac_send_pspoll_to_ap(pst_dmac_vap);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_awake_event::rx ucast event dmac_send_pspoll_to_ap fail [%d].}", ul_ret);
            }

        break;

        /* TIM is set */
        case STA_PWR_EVENT_TIM:
            if (OAL_TRUE == pst_pm_handler->en_more_data_expected)
            {
                ul_ret = dmac_send_pspoll_to_ap(pst_dmac_vap);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_awake_event::rx beacon event dmac_send_pspoll_to_ap fail [%d].}", ul_ret);
                }
            }
        break;

        /* DTIM set, stay in AWAKE mode to recieve all broadcast frames */
        case STA_PWR_EVENT_DTIM:
            pst_pm_handler->en_more_data_expected = OAL_TRUE;
            pst_pm_handler->aul_pmDebugCount[PM_MSG_DTIM_AWAKE]++;
        break;

        /* AWAKE状态下接收null帧发送成功的处理 */
        case STA_PWR_EVENT_SEND_NULL_SUCCESS:
            pst_mac_hdr = (mac_ieee80211_frame_stru *)(p_event_data);
            dmac_process_send_null_succ_event(pst_pm_handler, pst_mac_hdr);
        break;

       /* 睡眠事件 */
       case STA_PWR_EVENT_BEACON_TIMEOUT:
       case STA_PWR_EVENT_NORMAL_SLEEP:
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, us_event);
       break;

        /* Awake 状态下收到最后一个组播/广播 */
        case STA_PWR_EVENT_LAST_MCAST:
            pst_pm_handler->en_more_data_expected   = OAL_FALSE;
            pst_pm_handler->en_ps_deep_sleep        = OAL_TRUE;
            pst_pm_handler->aul_pmDebugCount[PM_MSG_LAST_DTIM_SLEEP]++;
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, us_event);
        break;

        /* 超时函数处理事件 pspoll模式下,不需要超时进doze,直接看beacon tim 元素 */
        case STA_PWR_EVENT_TIMEOUT:
            pst_pm_handler->en_ps_deep_sleep        = OAL_TRUE;   /* 切换到浅睡状态 */
            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_DOZE, us_event);
        break;

        case STA_PWR_EVENT_P2P_SLEEP:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_TRUE);
        break;

        case STA_PWR_EVENT_P2P_AWAKE:
            dmac_p2p_handle_ps(pst_dmac_vap, OAL_FALSE);
        break;

        /* 非节能模式事件 */
         case STA_PWR_EVENT_NO_POWERSAVE:
            if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)
            {
                ul_ret = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{sta_power_state_awake_event::dmac_send_null_frame_to_ap:[%d]}", ul_ret);
                }
            }

            dmac_pm_sta_state_trans(pst_pm_handler, STA_PWR_SAVE_STATE_ACTIVE, us_event);/* 设状态 */
        break;
        case STA_PWR_EVENT_DEASSOCIATE:
            dmac_pm_process_deassociate(pst_pm_handler);
        break;
        default:
        break;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_pm_sta_doze_state_trans
 功能描述  : PM节能状态机的状态切换到doze状态
 输入参数  : pst_handler:pm handler指针
             uc_state:切换状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_pm_sta_doze_state_trans(mac_sta_pm_handler_stru* pst_handler, oal_uint16 us_event)
{
    mac_fsm_stru    *pst_fsm = pst_handler->p_mac_fsm;
    dmac_vap_stru    *pst_dmac_vap;
    oal_uint8         uc_doze_trans_flag;
    oal_uint8         uc_beacon_timeout_count = DMAC_BEACON_TIMEOUT_MAX_NUM;

    pst_dmac_vap = (dmac_vap_stru *)(pst_fsm->p_oshandler);
    uc_doze_trans_flag = (pst_handler->en_beacon_frame_wait) | (pst_handler->st_null_wait.en_doze_null_wait << 1) | (pst_handler->en_more_data_expected << 2)
                | (pst_handler->st_null_wait.en_active_null_wait << 3) | (pst_handler->en_send_active_null_frame_to_ap << 4);

    if (us_event != STA_PWR_EVENT_BEACON_TIMEOUT)
    {
        if ((OAL_FALSE == uc_doze_trans_flag) && (OAL_TRUE == dmac_can_sta_doze_prot(pst_dmac_vap)))
        {
            pst_handler->uc_doze_event = (oal_uint8)us_event;
            pst_handler->uc_state_fail_doze_trans_cnt = 0;                      //失败统计清零
            pst_handler->uc_can_sta_sleep = OAL_TRUE;                           //允许深睡
            mac_fsm_trans_to_state(pst_fsm, STA_PWR_SAVE_STATE_DOZE);
        }
        else if (OAL_FALSE != uc_doze_trans_flag)
        {
            /* 睡眠null发送完成允许协议上切到doze状态,但不向平台投票睡眠,避免重复的睡眠唤醒null帧发送 */
            if (STA_PWR_EVENT_SEND_NULL_SUCCESS == us_event)
            {
                pst_handler->uc_can_sta_sleep = OAL_FALSE;                    //只允许切状态不允许睡
                pst_handler->uc_doze_event = (oal_uint8)us_event;
                mac_fsm_trans_to_state(pst_fsm, STA_PWR_SAVE_STATE_DOZE);
            }

            pst_handler->uc_state_fail_doze_trans_cnt++;

            if (DMAC_STATE_DOZE_TRANS_FAIL_NUM == pst_handler->uc_state_fail_doze_trans_cnt)
            {
                pst_handler->uc_state_fail_doze_trans_cnt = 0;

                OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_doze_state_trans::now event:[%d],but wait flag:[%d] can not vote sleep.}",us_event,uc_doze_trans_flag);
            }
        }
    }
    else
    {
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        if(pst_dmac_vap->pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
        {
            uc_beacon_timeout_count = DMAC_BEACON_TIMEOUT_MAX_NUM_COEX;
        }
        else
        {
            uc_beacon_timeout_count = DMAC_BEACON_TIMEOUT_MAX_NUM;
        }
#endif

        /* beacon连续收不到DMAC_BEACON_TIMEOUT_MAX_NUM次不睡眠低功耗状态停在awake状态 */
        if (pst_dmac_vap->bit_beacon_timeout_times > uc_beacon_timeout_count)
        {
            pst_handler->aul_pmDebugCount[PM_MSG_BCNTIMOUT_DIS_ALLOW_SLEEP]++;
            return;
        }

        pst_handler->uc_can_sta_sleep = OAL_TRUE;                             //beacon超时允许深睡
        pst_handler->en_beacon_frame_wait = OAL_FALSE;
        pst_handler->st_null_wait.en_doze_null_wait = OAL_FALSE;
        pst_handler->en_more_data_expected = OAL_FALSE;
        pst_handler->st_null_wait.en_active_null_wait = OAL_FALSE;
        pst_handler->en_send_active_null_frame_to_ap  = OAL_FALSE;

        pst_handler->uc_doze_event = (oal_uint8)us_event;

        mac_fsm_trans_to_state(pst_fsm, STA_PWR_SAVE_STATE_DOZE);
    }
}
/*****************************************************************************
 函 数 名  : dmac_pm_state_trans
 功能描述  : PM节能状态机的状态切换接口
 输入参数  : pst_handler:pm handler指针
             uc_state:切换状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_pm_sta_state_trans(mac_sta_pm_handler_stru* pst_handler,oal_uint8 uc_state, oal_uint16 us_event)
{
    mac_fsm_stru    *pst_fsm = pst_handler->p_mac_fsm;
    dmac_vap_stru   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru*)(pst_fsm->p_oshandler);

    if(uc_state >= STA_PWR_SAVE_STATE_BUTT)
    {
        /* OAM日志中不能使用%s*/
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_state_trans:invalid state %d}",uc_state);
        return;
    }

    /* 1102新增切状态时记录抛事件的类型 */
    switch (uc_state)
    {
        case STA_PWR_SAVE_STATE_ACTIVE:
            pst_handler->uc_active_event = (oal_uint8)us_event;
            if (STA_PWR_SAVE_STATE_ACTIVE != STA_GET_PM_STATE(pst_handler))
            {
                mac_fsm_trans_to_state(pst_fsm, uc_state);
            }
            else
            {
                OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_state_trans::dmac event:[%d]trans state to active in[%d]state}", us_event, STA_GET_PM_STATE(pst_handler));
            }
        break;

        case STA_PWR_SAVE_STATE_AWAKE:
            pst_handler->uc_awake_event = (oal_uint8)us_event;
            if (STA_PWR_SAVE_STATE_AWAKE != STA_GET_PM_STATE(pst_handler))
            {
                mac_fsm_trans_to_state(pst_fsm, uc_state);
            }
            else
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_state_trans::dmac event:[%d]trans state to awake in awake}", us_event);
            }
        break;

        /* 必须满足条件才能切换到doze状态,否则会造成sta没有真正睡下去,状态却已经切成doze,tbtt重复唤醒 */
        case STA_PWR_SAVE_STATE_DOZE:
        if (STA_PWR_SAVE_STATE_DOZE != STA_GET_PM_STATE(pst_handler))
        {
            dmac_pm_sta_doze_state_trans(pst_handler, us_event);
        }
        else
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_state_trans::dmac event:[%d]trans state to doze in doze}", us_event);
        }
        break;

        default:
        break;
    }
    return;

}
/*****************************************************************************
 函 数 名  : dmac_sta_pm_post_event
 功能描述  : 节能状态机的事件处理接口,节能状态机的状态切换以事件来驱动，基于frw的事件分发机制来承载pm的内部事件
 输入参数  : pst_event_mem: frw的事件结构指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月17日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_pm_sta_post_event(oal_void* pst_oshandler, oal_uint16 us_type, oal_uint16 us_datalen, oal_uint8* pst_data)
{
    mac_sta_pm_handler_stru     *pst_handler;
    mac_fsm_stru                *pst_fsm;
    oal_uint32                  ul_ret;
    oal_uint8                   uc_pm_state;
    oal_uint8                   uc_event = 0;
    dmac_vap_stru*              pst_dmac_vap = (dmac_vap_stru*)pst_oshandler;

    OAL_REFERENCE(uc_event);

    if(pst_dmac_vap == OAL_PTR_NULL)
    {
        OAM_WARNING_LOG1(0, OAM_SF_PWR, "{dmac_pm_sta_post_event::pst_dmac_vap null.event:[%d]}", us_type);
        return OAL_FAIL;
    }

    pst_handler = (mac_sta_pm_handler_stru *)pst_dmac_vap->pst_pm_handler;
    if(pst_handler == OAL_PTR_NULL)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_post_event::pst_pm_handler null.event:[%d]}", us_type);
        return OAL_FAIL;
    }

    pst_fsm = pst_handler->p_mac_fsm;
    uc_pm_state = STA_GET_PM_STATE(pst_handler);

    /* 上次切换到xx状态的事件 */
    switch (uc_pm_state)
    {
        case STA_PWR_SAVE_STATE_DOZE:
            uc_event = pst_handler->uc_doze_event;
        break;

        case STA_PWR_SAVE_STATE_AWAKE:
            uc_event = pst_handler->uc_awake_event;
        break;

        case STA_PWR_SAVE_STATE_ACTIVE:
            uc_event = pst_handler->uc_active_event;
        break;

        default:
        break;

    }

    /* 期望所在的状态抛出的事件和现实所在状态不一致的错误维测打印 */
    switch(us_type)
    {
        case STA_PWR_EVENT_TX_DATA:
        case STA_PWR_EVENT_TBTT:
        case STA_PWR_EVENT_FORCE_AWAKE:
            if (STA_PWR_SAVE_STATE_DOZE != uc_pm_state)
            {
                OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_post_event::now event:[%d],but event:[%d]change state to[%d]not doze}",us_type, uc_event, uc_pm_state);
            }
        break;

        case STA_PWR_EVENT_RX_UCAST:
        case STA_PWR_EVENT_LAST_MCAST:
        case STA_PWR_EVENT_TIM:
        case STA_PWR_EVENT_DTIM:
        case STA_PWR_EVENT_NORMAL_SLEEP:
            if (STA_PWR_SAVE_STATE_AWAKE != uc_pm_state)
            {
                OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_post_event::now event:[%d],but event:[%d]change state to[%d]not awake}",us_type, uc_event, uc_pm_state);
            }
        break;

        default:
        break;

    }
    ul_ret = mac_fsm_event_dispatch(pst_fsm, us_type, us_datalen, pst_data);

    return ul_ret;

}
/*****************************************************************************
 函 数 名  : dmac_pm_sta_attach
 功能描述  : sta pm 变量初始化
 输入参数  : p_fsm:状态机指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月4日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_sta_initialize_psm_globals(mac_sta_pm_handler_stru *p_handler)
{
        p_handler->en_beacon_frame_wait             = OAL_FALSE;
        p_handler->st_null_wait.en_active_null_wait = OAL_FALSE;
        p_handler->st_null_wait.en_doze_null_wait   = OAL_FALSE;
        p_handler->en_more_data_expected            = OAL_FALSE;
        p_handler->en_ps_deep_sleep                 = OAL_FALSE;
        p_handler->en_send_null_delay               = OAL_FALSE;
        p_handler->ul_tx_rx_activity_cnt            = 0;
        p_handler->en_send_active_null_frame_to_ap  = OAL_FALSE;
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
        p_handler->uc_uaspd_sp_status               = DMAC_SP_NOT_IN_PROGRESS;
        p_handler->uc_eosp_timeout_cnt              = 0;
#endif
        p_handler->ul_activity_timeout              = MIN_ACTIVITY_TIME_OUT;
        p_handler->ul_ps_keepalive_cnt              = 0;
        p_handler->ul_ps_keepalive_max_num          = WLAN_PS_KEEPALIVE_MAX_NUM;
        p_handler->uc_timer_fail_doze_trans_cnt     = 0;
        p_handler->uc_state_fail_doze_trans_cnt     = 0;
        p_handler->en_ps_back_active_pause          = OAL_FALSE;
        p_handler->en_ps_back_doze_pause            = OAL_FALSE;
        p_handler->uc_psm_timer_restart_cnt         = 0;

}

/*****************************************************************************
 函 数 名  : dmac_pm_sta_attach
 功能描述  : sta类型VAP创建pm handler
 输入参数  : p_fsm:状态机指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
mac_sta_pm_handler_stru * dmac_pm_sta_attach(oal_void* pst_oshandler)
{
    mac_sta_pm_handler_stru *p_handler  = OAL_PTR_NULL;
    dmac_vap_stru           *p_dmac_vap = (dmac_vap_stru*)pst_oshandler;
    oal_uint8                auc_fsm_name[6] = {0};

    if(OAL_PTR_NULL != p_dmac_vap->pst_pm_handler)
    {
        return p_dmac_vap->pst_pm_handler;
    }

    p_handler = (mac_sta_pm_handler_stru*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_sta_pm_handler_stru), OAL_TRUE);
    if(OAL_PTR_NULL == p_handler)
    {
        OAM_ERROR_LOG1(p_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_attach:alloc[%d]memory for pm handler fail!}",OAL_SIZEOF(mac_sta_pm_handler_stru));
        return OAL_PTR_NULL;
    }

    OAL_MEMZERO(p_handler, OAL_SIZEOF(mac_sta_pm_handler_stru));

    p_handler->en_beacon_frame_wait             = OAL_FALSE;
    p_handler->st_null_wait.en_active_null_wait = OAL_FALSE;
    p_handler->st_null_wait.en_doze_null_wait   = OAL_FALSE;
    p_handler->en_more_data_expected            = OAL_FALSE;
    p_handler->uc_vap_ps_mode                   = NO_POWERSAVE;
    p_handler->en_ps_deep_sleep                 = OAL_FALSE;
    p_handler->en_send_null_delay               = OAL_FALSE;
    p_handler->ul_tx_rx_activity_cnt            = 0;
    p_handler->en_send_active_null_frame_to_ap  = OAL_FALSE;
    p_handler->en_hw_ps_enable                  = OAL_TRUE;    /* 是否仅是协议栈低功耗,配置命令可配 */
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    p_handler->uc_uaspd_sp_status               = DMAC_SP_NOT_IN_PROGRESS;
    p_handler->uc_eosp_timeout_cnt              = 0;
#endif
    p_handler->ul_activity_timeout              = MIN_ACTIVITY_TIME_OUT;
    p_handler->ul_ps_keepalive_cnt              = 0;
    p_handler->ul_ps_keepalive_max_num          = WLAN_PS_KEEPALIVE_MAX_NUM;
    p_handler->uc_timer_fail_doze_trans_cnt     = 0;
    p_handler->uc_state_fail_doze_trans_cnt     = 0;
    p_handler->en_ps_back_active_pause          = OAL_FALSE;
    p_handler->en_ps_back_doze_pause            = OAL_FALSE;
    p_handler->uc_psm_timer_restart_cnt         = 0;

    /* 准备一个唯一的fsmname */
    auc_fsm_name[0] = (oal_uint8)(p_dmac_vap->st_vap_base_info.ul_core_id);
    auc_fsm_name[1] = p_dmac_vap->st_vap_base_info.uc_chip_id;
    auc_fsm_name[2] = p_dmac_vap->st_vap_base_info.uc_device_id;
    auc_fsm_name[3] = p_dmac_vap->st_vap_base_info.uc_vap_id;
    auc_fsm_name[4] = p_dmac_vap->st_vap_base_info.en_vap_mode;
    auc_fsm_name[5] = 0;

    p_handler->p_mac_fsm = mac_fsm_create((oal_void*)p_dmac_vap,
                                          auc_fsm_name,
                                          p_handler,
                                          STA_PWR_SAVE_STATE_ACTIVE,
                                          g_sta_power_fsm_info,
                                          OAL_SIZEOF(g_sta_power_fsm_info)/OAL_SIZEOF(mac_fsm_state_info)
                                          );
    p_dmac_vap->pst_pm_handler = p_handler;

    return p_dmac_vap->pst_pm_handler;
}

/*****************************************************************************
 函 数 名  : dmac_pm_sta_deattach
 功能描述  : sta类型VAP销毁pm handler
 输入参数  : p_fsm:状态机指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_pm_sta_detach(oal_void* pst_oshandler)
{
    mac_sta_pm_handler_stru *pst_handler = OAL_PTR_NULL;
    dmac_vap_stru           *pst_dmac_vap = (dmac_vap_stru*)pst_oshandler;

    pst_handler = (mac_sta_pm_handler_stru *)pst_dmac_vap->pst_pm_handler;
    if(OAL_PTR_NULL == pst_handler)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_pm_sta_detach::pst_handler null.}");
        return;
    }

    /* 不是active状态切换到active状态 */
    if (STA_GET_PM_STATE(pst_handler) != STA_PWR_SAVE_STATE_ACTIVE)
    {
        dmac_pm_sta_state_trans(pst_handler, STA_PWR_SAVE_STATE_AWAKE, STA_PWR_EVENT_DETATCH);
        dmac_pm_sta_state_trans(pst_handler, STA_PWR_SAVE_STATE_ACTIVE, STA_PWR_EVENT_DETATCH);
    }

    if (OAL_TRUE == pst_handler->st_inactive_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_handler->st_inactive_timer));
    }

    if(OAL_PTR_NULL != pst_handler->p_mac_fsm)
    {
        mac_fsm_destroy(pst_handler->p_mac_fsm);
    }

    OAL_MEM_FREE(pst_handler,OAL_TRUE);

    pst_dmac_vap->pst_pm_handler = OAL_PTR_NULL;

    return;

}

#endif /* _PRE_WLAN_FEATURE_STA_PM */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

