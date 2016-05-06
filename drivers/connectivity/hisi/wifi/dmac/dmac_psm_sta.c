/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_psm_sta.c
  版 本 号   : 初稿
  作    者   : l00280485
  生成日期   : 2014年11月25日
  最近修改   :
  功能描述   : sta ps_poll低功耗功能所在函数
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
#include "dmac_psm_sta.h"
#include "dmac_psm_ap.h"
#include "mac_data.h"
#include "pm_extern.h"
#include "dmac_sta_pm.h"
#include "dmac_config.h"

#include "frw_timer.h"

#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PSM_STA_C

oal_uint32 g_device_wlan_pm_timeout = 50;
oal_uint32 g_pm_timer_restart_cnt   =  4;
oal_uint8  g_uc_max_powersave = OAL_FALSE;
oal_uint8  g_uc_max_powersave_limit = 100;		/*beacon*dtim<=100ms*/

oal_uint32 dmac_send_null_frame_to_ap(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_psm, oal_bool_enum_uint8 en_qos);
oal_uint32 dmac_psm_alarm_callback(void *p_arg);
oal_uint8  dmac_psm_is_tx_queues_empty(dmac_vap_stru  *pst_dmac_vap);
oal_uint8  dmac_psm_is_hw_queues_empty(mac_device_stru  *pst_device);
oal_uint8  dmac_psm_is_tid_queues_empty(dmac_vap_stru  *pst_dmac_vap);

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


//OAL_STATIC oal_uint8  g_uc_bmap[8] = {1, 2, 4, 8, 16, 32, 64, 128}; /* Bit map */
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_psm_get_max_sleep_time
 功能描述  : 获取协议最大允许睡眠时间
 输入参数  : pst_dmac_vap dmac_vap 结构体
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月08日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_get_max_sleep_time(dmac_vap_stru  *pst_dmac_vap)
{
    oal_uint32    ul_dtim_period;
    oal_uint32    ul_bank3_bcn_period;
    oal_uint32    ul_max_allow_sleep_time;
    //oal_uint32    aul_addr[]              = {0x2010020c,0x20100234,0x2010025c};

    /* 关联上后才计算最大睡眠时间 */
    if ((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state) || (MAC_VAP_STATE_PAUSE == pst_dmac_vap->st_vap_base_info.en_vap_state))
    {
        //ul_dtim_period = mac_mib_get_dot11dtimperiod(&(pst_dmac_vap->st_vap_base_info));
        ul_dtim_period = pst_dmac_vap->us_psm_dtim_period;
        hal_vap_get_beacon_period(pst_dmac_vap->pst_hal_vap, &ul_bank3_bcn_period);

        if (0 == ul_bank3_bcn_period)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id,OAM_SF_PWR,"{dmac_psm_get_max_sleep_time::bank3 beacon period is 0.}");

            hal_sta_tsf_restore(pst_dmac_vap->pst_hal_vap);

        }

        ul_max_allow_sleep_time = (ul_bank3_bcn_period * ul_dtim_period + 20);
    }
    /* 否则不计算睡眠时间*/
    else
    {
        ul_max_allow_sleep_time = 0xFFFFFFFF;
    }

    return ul_max_allow_sleep_time;
}

/*****************************************************************************
 函 数 名  : dmac_psm_process_no_powersave
 功能描述  : 非节能模式下，处于非active状态的处理
 输入参数  : pst_dmac_vap dmac_vap 结构体
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月19日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_process_no_powersave(dmac_vap_stru *pst_dmac_vap)
{

    if (IS_P2P_DEV(&(pst_dmac_vap->st_vap_base_info)) || (WLAN_VAP_MODE_BSS_STA != pst_dmac_vap->st_vap_base_info.en_vap_mode))
    {
        return;
    }

    /* 异常此时应该处于active状态 */
    if (STA_GET_PM_STATE((mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler)) != STA_PWR_SAVE_STATE_ACTIVE)
    {
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_NO_POWERSAVE, 0, OAL_PTR_NULL);
    }

}
/*****************************************************************************
 函 数 名  : dmac_psm_process_fast_ps_state_change
 功能描述  : fast ps 节能模式下的状态切换
 输入参数  : pst_dmac_vap dmac_vap 结构体 uc_psm 要切换到的状态
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月22日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_process_fast_ps_state_change(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_psm)
{
    mac_sta_pm_handler_stru *pst_mac_sta_pm_handle;
    oal_uint32 ul_retval  = OAL_SUCC;

     pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

     /* awake->active 需要发送唤醒null帧 */
     if (STA_PWR_SAVE_STATE_AWAKE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
     {
         if((STA_PWR_SAVE_STATE_ACTIVE == uc_psm) && (OAL_FALSE == pst_mac_sta_pm_handle->st_null_wait.en_active_null_wait))
         {

             ul_retval = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE);

         }
         else
         {
             OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_process_fast_ps_state_change::state:awake,send[%d]null frame,active null wait:[%d].}",uc_psm,pst_mac_sta_pm_handle->st_null_wait.en_active_null_wait);
         }
     }

     /* active->doze的超时需要发送睡眠null帧 */
     else if (STA_PWR_SAVE_STATE_ACTIVE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
     {
         if((STA_PWR_SAVE_STATE_DOZE == uc_psm) && (OAL_FALSE == pst_mac_sta_pm_handle->st_null_wait.en_doze_null_wait))
         {

             ul_retval = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_DOZE, OAL_FALSE);
         }
         else
         {
             OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_process_fast_ps_state_change::state:active,send[%d]null frame,doze null wait:[%d].}",uc_psm,pst_mac_sta_pm_handle->st_null_wait.en_doze_null_wait);
         }
     }

     return ul_retval;

}

/*****************************************************************************
 函 数 名  : dmac_psm_start_activity_timer
 功能描述  : 启动activity 定时器
 输入参数  : pst_dmac_vap dmac_vap 结构体
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_start_activity_timer(dmac_vap_stru *pst_dmac_vap, mac_sta_pm_handler_stru *pst_sta_pm_handle)
{

    if((OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_sta_pm_handle))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PWR, "{dmac_psm_start_activity_timer has null point:dmac_vap =%p pm_handle=%p}",pst_dmac_vap,pst_sta_pm_handle);
        return;
    }

    if(WLAN_MIB_PWR_MGMT_MODE_PWRSAVE == mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)))
    {
        pst_sta_pm_handle->ul_activity_timeout = g_device_wlan_pm_timeout;

#ifdef _PRE_WLAN_FEATURE_P2P
        /* 修改定时器时间使发送睡眠null帧的时间落在go active时间内 */
        if (IS_P2P_NOA_ENABLED(pst_dmac_vap))
        {
            pst_sta_pm_handle->ul_activity_timeout = (pst_dmac_vap->st_p2p_noa_param.ul_duration / 1000);
        }
        else if (IS_P2P_OPPPS_ENABLED(pst_dmac_vap))
        {
            pst_sta_pm_handle->ul_activity_timeout = (pst_dmac_vap->st_p2p_ops_param.uc_ct_window);
        }
#endif
    }
    else
    {
        pst_sta_pm_handle->ul_activity_timeout = MIN_ACTIVITY_TIME_OUT;
    }

    /* 节能下超时时间和非节能下的超时时间不一样，启动定时器 */
    FRW_TIMER_CREATE_TIMER(&(pst_sta_pm_handle->st_inactive_timer),
                        dmac_psm_alarm_callback,
                        pst_sta_pm_handle->ul_activity_timeout ,
                        pst_dmac_vap,
                        OAL_FALSE,
                        OAM_MODULE_ID_DMAC,
                        0);
}
/*****************************************************************************
 函 数 名  : dmac_psm_sync_dtim_count
 功能描述  : dtim listen interval count设置
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月10日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_sync_dtim_count(dmac_vap_stru *pst_dmac_vap, dmac_tim_ie_stru *pst_time_ie)
{
    oal_uint16               us_listen_interval_count;

    /* 写STA dtim_count寄存器, dtim update 寄存器不允许写0 */
    if (0 == pst_time_ie->uc_dtim_count)
    {
        hal_set_psm_dtim_count(pst_dmac_vap->pst_hal_vap, (oal_uint8)pst_dmac_vap->us_psm_dtim_period);
        hal_set_psm_listen_interval_count(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->us_psm_listen_interval);
    }
    else
    {
        hal_set_psm_dtim_count(pst_dmac_vap->pst_hal_vap, (oal_uint8)pst_time_ie->uc_dtim_count);

        if(pst_time_ie->uc_dtim_count <= pst_dmac_vap->us_psm_listen_interval)
        {
            us_listen_interval_count = pst_time_ie->uc_dtim_count;
        }
        else
        {
            us_listen_interval_count = pst_dmac_vap->us_psm_listen_interval;
        }
        
        hal_set_psm_listen_interval_count(pst_dmac_vap->pst_hal_vap, us_listen_interval_count);
    }

}

/*****************************************************************************
 函 数 名  : dmac_psm_max_powersave_enable
 功能描述  : 使能或去使能最大节能(dtim*2策略)，同时需更新keepalive的门限
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : zourong 274374
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_max_powersave_enable(mac_device_stru *pst_mac_device)
{
    oal_uint8       uc_vap_idx;
    dmac_vap_stru   *pst_dmac_vap;

    if(OAL_PTR_NULL == pst_mac_device)
    {
        return ;
    }
    
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "{dmac_psm_max_powersave_enable:enable[%d]}",pst_mac_device->uc_in_suspend);

    g_uc_max_powersave = (0== pst_mac_device->uc_in_suspend)?0:1;
    
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);

        if ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
            &&(0!=pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod))
        {          
            dmac_psm_update_dtime_period(pst_dmac_vap,
                                        (oal_uint8)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod,
                                        pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);

            dmac_psm_update_keepalive(pst_dmac_vap);
        }
    }

}

/*****************************************************************************
 函 数 名  : dmac_psm_update_dtime_period
 功能描述  : 跟新低功耗实际采用的dtime周期和listen interval的设置
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/

oal_void dmac_psm_update_dtime_period(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_mib_dtim_period,oal_uint32 ul_beacon_period)
{
    if(g_uc_max_powersave)
    {
        if(g_uc_max_powersave_limit >= (uc_mib_dtim_period*ul_beacon_period))
        {
            pst_dmac_vap->us_psm_dtim_period = 2*uc_mib_dtim_period;
            pst_dmac_vap->us_psm_listen_interval = pst_dmac_vap->us_psm_dtim_period;
            OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_update_dtime_period::use dtim2,beacon[%d],dtim period[%d]}",ul_beacon_period,uc_mib_dtim_period);
        }
        else
        {
            pst_dmac_vap->us_psm_dtim_period = uc_mib_dtim_period;
            pst_dmac_vap->us_psm_listen_interval = (pst_dmac_vap->us_psm_dtim_period  < DMAC_DEFAULT_DTIM_LISTEN_DIFF) ? ((oal_uint16)(pst_dmac_vap->us_psm_dtim_period )) : DMAC_DEFAULT_LISTEN_INTERVAL;
        }
    }
    else
    {
        pst_dmac_vap->us_psm_dtim_period = uc_mib_dtim_period;

        pst_dmac_vap->us_psm_listen_interval = (pst_dmac_vap->us_psm_dtim_period  < DMAC_DEFAULT_DTIM_LISTEN_DIFF) ? ((oal_uint16)(pst_dmac_vap->us_psm_dtim_period )) : DMAC_DEFAULT_LISTEN_INTERVAL;
    }

    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_update_dtime_period:set psm dtim period[%d]}",pst_dmac_vap->us_psm_dtim_period);
    /* 设置period寄存器的值 */
    hal_set_sta_dtim_period(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->us_psm_dtim_period);
    hal_set_psm_listen_interval(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->us_psm_listen_interval);

}

/*****************************************************************************
 函 数 名  : dmac_psm_update_keepalive
 功能描述  : 跟新keepalive的设置
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/

oal_void dmac_psm_update_keepalive(dmac_vap_stru *pst_dmac_vap)
{
    mac_sta_pm_handler_stru 	   *pst_mac_sta_pm_handle; /* STA节能状态下结构体 */
    oal_uint32                      ul_dtime_period;
    oal_uint32                      ul_keepalive_time;

    /* 根据Beacon interval修改对应的STA节能下keepalive的DTIM interval */
    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_psm_update_keepalive::pst_mac_sta_pm_handle null}");
    }
    else
    {
        if (0!=pst_dmac_vap->us_psm_dtim_period)
        {
            ul_dtime_period = pst_dmac_vap->us_psm_dtim_period;
        }
        else
        {
            ul_dtime_period = pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod;
        }

        if ((0 != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod)
            && (0 != ul_dtime_period))
        {
            ul_keepalive_time = WLAN_STA_KEEPALIVE_TIME;

        #ifdef _PRE_WLAN_FEATURE_P2P
            if (IS_P2P_CL(&pst_dmac_vap->st_vap_base_info))
            {
                ul_keepalive_time = WLAN_CL_KEEPALIVE_TIME;
            }
        #endif

            pst_mac_sta_pm_handle->ul_ps_keepalive_max_num = ul_keepalive_time /
                                        ((pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod)*(ul_dtime_period));

            OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_update_keepalive::set keepalive[%d],beacon[%d],dtim[%d]}",
                pst_mac_sta_pm_handle->ul_ps_keepalive_max_num,pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod,
                ul_dtime_period);
        }
        else
        {

            OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_update_keepalive::beacon[%d],dtim period[%d]}",
            pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod,
            ul_dtime_period);
        }
    }

}

/*****************************************************************************
 函 数 名  : dmac_psm_is_tim_dtim_set
 功能描述  : 检查 beacon帧内，tim/dtim是否被set
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_psm_is_tim_dtim_set(dmac_vap_stru *pst_dmac_vap, oal_uint8* puc_tim_elm)
{
    oal_uint32                  ul_aid;
    oal_uint32                  ul_min_ix;
    oal_uint32                  ul_max_ix;
    oal_uint32                  ul_tim_dtim_present      = 0;
    dmac_tim_ie_stru            *pst_time_ie;

    pst_time_ie = (dmac_tim_ie_stru *)puc_tim_elm;
    ul_aid = WLAN_AID(pst_dmac_vap->st_vap_base_info.us_sta_aid);
    //ul_ix = ul_aid / WLAN_NBBY;
    ul_min_ix =  pst_time_ie->uc_tim_bitctl &~ 1;
    ul_max_ix =  pst_time_ie->uc_tim_len + ul_min_ix - 4;

    /*检查是否是TIM*/
    if(pst_time_ie->uc_tim_ie != MAC_EID_TIM)
    {
        return ul_tim_dtim_present;
    }
    /* 读dtim period寄存器 */
    //hal_get_sta_dtim_period(pst_dmac_vap->pst_hal_vap, &ul_dtim_period);

    /* Check if AP's DTIM period has changed */
    if((pst_time_ie->uc_dtim_period != mac_mib_get_dot11dtimperiod(&pst_dmac_vap->st_vap_base_info)) || (0 == pst_dmac_vap->us_psm_dtim_period))
    {
		mac_mib_set_dot11dtimperiod(&(pst_dmac_vap->st_vap_base_info), pst_time_ie->uc_dtim_period);

		dmac_psm_update_dtime_period(pst_dmac_vap,pst_time_ie->uc_dtim_period,pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);

        /* 设置count寄存器的值 */
        dmac_psm_sync_dtim_count(pst_dmac_vap, pst_time_ie);

		dmac_psm_update_keepalive(pst_dmac_vap);
    }

    /* DTIM IS SET */
    if(OAL_TRUE == (pst_time_ie->uc_tim_bitctl & BIT0))
    {
		ul_tim_dtim_present |= DMAC_DTIM_IS_SET;
    }

    /* TIM IS SET */
    if (((ul_aid >> 3) >= ul_min_ix) && ((ul_aid >> 3) <= ul_max_ix) && WLAN_TIM_ISSET(pst_time_ie->auc_tim_bitmap - ul_min_ix, ul_aid))
    {

        //OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_is_tim_dtim_set::aid:%d, min_ix:[%d]}", ul_aid, ul_min_ix);
        //OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{max_ix:%d, bitmap[0]:[%d], bitmap[1]:[%d]}", ul_max_ix, pst_time_ie->auc_tim_bitmap[0], pst_time_ie->auc_tim_bitmap[1]);
        ul_tim_dtim_present |= DMAC_TIM_IS_SET;
    }
    return ul_tim_dtim_present;
    }

#if 0
/*****************************************************************************
 函 数 名  : dmac_psm_is_tim_dtim_set
 功能描述  : 检查 beacon帧内，tim/dtim是否被set
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_psm_is_tim_dtim_set(dmac_vap_stru *pst_dmac_vap, oal_uint8* puc_tim_elm)
{
    oal_uint8                   uc_len  = 0;
    oal_uint8                   uc_bmap_ctrl = 0;
    oal_uint8                   uc_bmap_offset  = 0;
    oal_uint8                   uc_byte_offset = 0;
    oal_uint8                   uc_bit_offset  = 0;
    oal_uint8                   uc_status      = 0 ;
    oal_uint32                  ul_aid;
    mac_sta_pm_handler_stru     *pst_mac_sta_pm_handle;

    ul_aid = pst_dmac_vap->st_vap_base_info.us_sta_aid;
    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    /*检查是否是TIM*/
    if(puc_tim_elm[0]!= MAC_EID_TIM)
    {
      return uc_status;
    }

    uc_len = puc_tim_elm[1];
    uc_bmap_ctrl = puc_tim_elm[4];

    /* Check if AP's DTIM period has changed */
    if(puc_tim_elm[3] != mac_mib_get_dot11dtimperiod(&(pst_dmac_vap->st_vap_base_info)))
    {
      /* 重新设置DTIM寄存器的值 */
      hal_set_psm_dtim_period(pst_dmac_vap->pst_hal_vap, puc_tim_elm[3], pst_mac_sta_pm_handle->uc_listen_intervl_to_dtim_times,
                                  pst_mac_sta_pm_handle->en_receive_dtim);
    }

    /* Compute the bit map offset, which is given by the MSB 7 bits in the   */
    /* bit map control field of the TIM element.  */
    uc_bmap_offset = (uc_bmap_ctrl & 0xFE);

    /* A DTIM count of zero indicates that the current TIM is a DTIM. The    */
    /* BIT0 of the bit map control field is set (for TIMs with a value of 0  */
    /* in the DTIM count field) when one or more broadcast/multicast frames  */
    /* are buffered at the AP.                                               */
    if(OAL_TRUE == (uc_bmap_ctrl & BIT0))
    {
        uc_status |= DMAC_DTIM_IS_SET;
    }

    /* Traffic Indication Virtual Bit Map within the AP, generates the TIM   */
    /* such that if a station has buffered packets, then the corresponding   */
    /* bit (which can be found from the association ID) is set. The byte     */
    /* offset is obtained by dividing the association ID by '8' and the bit  */
    /* offset is the remainder of the association ID when divided by '8'.    */
    uc_byte_offset = ul_aid >> 3;
    uc_bit_offset  = ul_aid & 0x07;

    /* Bit map offset should always be greater than the computed byte offset */
    /* and the byte offset should always be lesser than the 'maximum' number */
    /* of bytes in the Virtual Bitmap. If either of the above two conditions */
    /* are not satisfied, then the 'status' is returned as is.               */
    if(uc_byte_offset < uc_bmap_offset || uc_byte_offset > uc_bmap_offset + uc_len - 4)
    {
        return uc_status;
    }

    /* The station has buffered packets only if the corresponding bit is set */
    /* in the Virtual Bit Map field. Note: Virtual Bit Map field starts      */
    /* 5 bytes from the start of the TIM element.                            */
    if((puc_tim_elm[5 + uc_byte_offset - uc_bmap_offset] & g_uc_bmap[uc_bit_offset]) != 0)
    {
        uc_status |= DMAC_TIM_IS_SET;
    }
    return uc_status;
}
#endif
#if (!defined(HI1102_EDA))
/*****************************************************************************
 函 数 名  : dmac_psm_process_tim_elm
 功能描述  : 处理STA power save模式下的tim信息元素，每次处理beacon帧时，
             进入该函数，tim如果是set，则发送ps_poll帧去获取ap侧缓存的数据。
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif

oal_void dmac_psm_process_tim_elm(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    dmac_rx_ctl_stru            *pst_rx_ctrl;
    mac_rx_ctl_stru             *pst_rx_info;
    dmac_tim_ie_stru            *pst_time_ie;
    oal_uint16                   us_frame_len;
    oal_uint32                   ul_tim_dtim_present;
    hal_to_dmac_vap_stru        *pst_hal_vap;
    oal_uint8                   *puc_tim_elm = OAL_PTR_NULL;
    oal_uint8                   *puc_payload;
    mac_sta_pm_handler_stru     *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_process_tim_elm::pst_mac_sta_pm_handle null}");
        return;
    }

    /* 接收beacon计数统计 */
    pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_BEACON_CNT]++;

    pst_hal_vap         = pst_dmac_vap->pst_hal_vap;
    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
    us_frame_len        = pst_rx_info->us_frame_len - pst_rx_info->bit_mac_header_len; /* 帧体长度 */
    puc_payload         = OAL_NETBUF_PAYLOAD(pst_netbuf);

    /* Reset beacon wait bit位 */
    pst_mac_sta_pm_handle->en_beacon_frame_wait  = OAL_FALSE;
    puc_tim_elm = mac_find_ie(MAC_EID_TIM, puc_payload + MAC_DEVICE_BEACON_OFFSET, us_frame_len - MAC_DEVICE_BEACON_OFFSET);
    if (OAL_PTR_NULL == puc_tim_elm)
    {
        return;
    }
    
    /* 非节能模式不进行beacon帧处理 */
    if ((mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_PWRSAVE) ||
            (0 == pst_dmac_vap->st_vap_base_info.us_sta_aid))
    {
        return;
    }

    ul_tim_dtim_present = dmac_psm_is_tim_dtim_set(pst_dmac_vap, puc_tim_elm);
    pst_time_ie         = (dmac_tim_ie_stru *)puc_tim_elm;

	/* 非tim元素也不处理 */
    if (MAC_EID_TIM != pst_time_ie->uc_tim_ie)
    {
        return;
    }

    /* 取DTIM值,保证睡眠与AP同步 先不打开dtim cnt 同步 */
    if (pst_hal_vap->uc_dtim_cnt != pst_time_ie->uc_dtim_count)
    {
        /* 设置count寄存器的值 */
        dmac_psm_sync_dtim_count(pst_dmac_vap, pst_time_ie);

        //hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf_lo);
        //OAL_IO_PRINT("diff dtim count ap:[%d], sta:[%d],bank3 dtim cnt:[%d], tbtt status:[%d]\r\n", pst_time_ie->uc_dtim_count, pst_hal_vap->uc_dtim_cnt, uc_dtim_cnt, (READL(0X20100658)));
        //OAL_IO_PRINT("diff dtim count ap:[%d], sta:[%d],tbtt status:[%d]\r\n\r\n", pst_time_ie->uc_dtim_count, pst_hal_vap->uc_dtim_cnt, (READL(0X20100658)));
        //OAL_IO_PRINT("tsf timer:[%u]\r\n",ul_tsf_lo);
    }

    /* 如果此时处于doze状态先切到awake状态 DTS2016010901870 此处不能加日志,同频会刷屏,且这里的日志属无效日志 */
    if (STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
    {
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TBTT, 0, OAL_PTR_NULL);
    }

    if (STA_PWR_SAVE_STATE_AWAKE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
    {
        /* TIM/DTIM is not set */
        if (0 == ul_tim_dtim_present)
        {
        #ifdef _PRE_WLAN_FEATURE_P2P
            dmac_set_ps_poll_rsp_pending(pst_dmac_vap, OAL_FALSE);
        #endif

            pst_mac_sta_pm_handle->en_more_data_expected = OAL_FALSE;

            /* 状态切换成功后才能进行TIM元素的后续处理 */
            if ((OAL_FALSE == pst_mac_sta_pm_handle->st_null_wait.en_active_null_wait) &&
            (OAL_FALSE == pst_mac_sta_pm_handle->st_null_wait.en_doze_null_wait))
            {
                pst_mac_sta_pm_handle->uc_beacon_fail_doze_trans_cnt = 0;

                if((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_keepalive)
                  && ((pst_mac_sta_pm_handle->ul_ps_keepalive_cnt) >= (pst_mac_sta_pm_handle->ul_ps_keepalive_max_num)))
                {
                    if(OAL_SUCC != dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_DOZE, OAL_FALSE))
                    {
                        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_process_tim_elm::keepalive send null data fail.}");
                    }

                    pst_mac_sta_pm_handle->ul_ps_keepalive_cnt = 0;
                    return;
                }
       
                pst_mac_sta_pm_handle->en_ps_deep_sleep = OAL_TRUE;
                dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_NORMAL_SLEEP, 0, OAL_PTR_NULL);

            }
            else
            {
                pst_mac_sta_pm_handle->uc_beacon_fail_doze_trans_cnt++;
                if (DMAC_BEACON_DOZE_TRANS_FAIL_NUM  < pst_mac_sta_pm_handle->uc_beacon_fail_doze_trans_cnt)
                {
                    pst_mac_sta_pm_handle->uc_beacon_fail_doze_trans_cnt = 0;
                    OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_process_tim_elm::beacon trans doze fail:reason:active null:[%d],doze null:[%d].}",
                                        pst_mac_sta_pm_handle->st_null_wait.en_active_null_wait, pst_mac_sta_pm_handle->st_null_wait.en_doze_null_wait);
                }
            }
        }

        /* TIM is set */
        else if ((ul_tim_dtim_present & DMAC_TIM_IS_SET) != 0 )
        {
            if (OAL_TRUE == dmac_is_any_legacy_ac_present(pst_dmac_vap))
            {
                pst_mac_sta_pm_handle->en_more_data_expected = OAL_TRUE;

                if (OAL_FALSE == dmac_is_sta_fast_ps_enabled(pst_mac_sta_pm_handle))
                {
                    /* Changes state to STA_ACTIVE and send ACTIVE NULL frame to */
                    /* AP immeditately in case of FAST PS mode                   */
                    dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TIM, 0, OAL_PTR_NULL);
                }
                else
                {
                    if (OAL_SUCC != dmac_psm_process_fast_ps_state_change(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE))
                    {
                        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"{dmac_psm_process_tim_elm::dmac_psm_process_fast_ps_state_change failed.}");
                    }
                }
            }
            else
            {
                dmac_psm_process_tim_set_sta_prot(pst_dmac_vap);
            }

            pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_TIM_AWAKE]++;
        }

        /* DTIM set, stay in AWAKE mode to recieve all broadcast frames */
        else
        {
            dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_DTIM, 0, OAL_PTR_NULL);
        }
    }
    else
    {
        /* Some APs (For Eg. Buffalo AP) sends TIM element set even after  */
        /* our NULL FRAME(ACTIVE) reception. If the TIM element says more  */
        /* data is on the way, then set the appropriate flag else reset it */
        pst_mac_sta_pm_handle->en_more_data_expected = (ul_tim_dtim_present != 0) ? OAL_TRUE : OAL_FALSE;

		/* staut会丢tbtt中断，软件暂时规避 */
        if (OAL_TRUE == (ul_tim_dtim_present & DMAC_TIM_IS_SET))
        {
            if (STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
            {
                dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TBTT, 0, OAL_PTR_NULL);
            }

            if (OAL_TRUE == dmac_is_any_legacy_ac_present(pst_dmac_vap))
            {
                if (OAL_TRUE == dmac_is_sta_fast_ps_enabled(pst_mac_sta_pm_handle)) /* fast ps 模式 */
                {
                    dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE);
                }
                else
                {
                    dmac_send_pspoll_to_ap(pst_dmac_vap);                           /* pspoll 模式 */
                }
            }
            else
            {
                dmac_psm_process_tim_set_sta_prot(pst_dmac_vap);                    /* UAPSD模式 */
            }
        }
    }
}
#else
/*****************************************************************************
 函 数 名  : dmac_psm_process_tim_elm
 功能描述  : eda用例使用,收到beacon后立刻睡眠
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_process_tim_elm(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
        mac_sta_pm_handler_stru     *pst_mac_sta_pm_handle;

        pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

        pst_mac_sta_pm_handle->en_ps_deep_sleep = OAL_TRUE;
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_BEACON_TIMEOUT, 0, OAL_PTR_NULL);

}
#endif
/*****************************************************************************
 函 数 名  : dmac_psm_rx_process_data_sta
 功能描述  : Ps低功耗模式下的接收帧处理，ps_poll模式下如果是单播帧并且moredata位是1，则继续发送ps_poll帧获取缓存帧。
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_psm_rx_process_data_sta(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_buf)
{
    oal_uint8                *puc_dest_addr;      /* 目的地址 */
    mac_ieee80211_frame_stru *pst_frame_hdr;
    mac_tx_ctl_stru          *pst_tx_ctl;
    mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_rx_process_data_sta::pst_mac_sta_pm_handle null}");
        return;
    }

    pst_frame_hdr = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_buf);
    puc_dest_addr = pst_frame_hdr->auc_address1;

    pst_tx_ctl  = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_buf);

    if ((mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_PWRSAVE) ||
        (0 == pst_dmac_vap->st_vap_base_info.us_sta_aid))
    {
        dmac_psm_process_no_powersave(pst_dmac_vap);

        /* SW-FIX:问题单DTS2013011502377,收到组播帧,不更新定时器 */
        if (!ETHER_IS_MULTICAST(puc_dest_addr))
        {
            //OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_KEEPALIVE, "keepalive rx data:type:[%d],subtype:[%d]", pst_frame_hdr->st_frame_control.bit_type, pst_frame_hdr->st_frame_control.bit_sub_type);
            dmac_psm_sta_incr_activity_cnt(pst_mac_sta_pm_handle);
        }
        return;
    }

    if (STA_PWR_SAVE_STATE_ACTIVE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
    {
        if ((OAL_TRUE == dmac_is_legacy_ac(pst_dmac_vap, pst_tx_ctl))
			&&(((WLAN_NULL_FRAME != pst_frame_hdr->st_frame_control.bit_sub_type)
     			&&(WLAN_QOS_NULL_FRAME != pst_frame_hdr->st_frame_control.bit_sub_type))))
        {
            pst_mac_sta_pm_handle->ul_psm_pkt_cnt++;
        }

    }
    else
    {
        /* 如果此时处于doze状态先切到awake状态 */
        if (STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
        {
            OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"{dmac_psm_rx_process_data_sta::event[%d] change state doze,frame is multi[%d],bcn wait[%d]}",pst_mac_sta_pm_handle->uc_doze_event,ETHER_IS_MULTICAST(puc_dest_addr),pst_mac_sta_pm_handle->en_beacon_frame_wait);
            dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TBTT, 0, OAL_PTR_NULL);
        }

        /* Handle Multicast/Broadcast frames and switch to DOZE state based on the More Data bit */
        if (OAL_TRUE == ETHER_IS_MULTICAST(puc_dest_addr))
        {
            if (OAL_FALSE == dmac_psm_get_more_data_sta(pst_frame_hdr))
            {
                dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_LAST_MCAST, 0, OAL_PTR_NULL);
            }
            else
            {
                pst_mac_sta_pm_handle->en_more_data_expected = OAL_TRUE;
            }
        }

        /* 收到单播的处理 */
        else
        {
            if (OAL_FALSE == dmac_psm_get_more_data_sta(pst_frame_hdr))
            {
                pst_mac_sta_pm_handle->en_more_data_expected = OAL_FALSE;
            }
            else
            {
                if (OAL_TRUE == dmac_is_any_legacy_ac_present(pst_dmac_vap))
                {
                    //OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_rx_process_data_sta::type is %d, sub type is %d\r\n}", pst_frame_hdr->st_frame_control.bit_type,
                    //                                                                            pst_frame_hdr->st_frame_control.bit_sub_type);
                    dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_RX_UCAST, 0, OAL_PTR_NULL);
                }

                pst_mac_sta_pm_handle->en_more_data_expected = OAL_TRUE;
            }
            dmac_process_rx_process_data_sta_prot(pst_dmac_vap, pst_buf);
        }
    }
}
/*****************************************************************************
 函 数 名  : dmac_psm_tx_process_data_sta
 功能描述  : 主要查询MAC省电状态，并决定在帧控制字段中是否设置节能比特位
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_psm_tx_process_data_sta(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint8                 uc_pwr_mgmt_bit = 0;
    mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_tx_process_data_sta::pst_mac_sta_pm_handle null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 非节能模式下的处理 */
    if ((mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_PWRSAVE) ||
        (0 == pst_dmac_vap->st_vap_base_info.us_sta_aid))
    {
        dmac_psm_process_no_powersave(pst_dmac_vap);
        //OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_KEEPALIVE, "keepalive tx data ismcast:[%d],is eapol:[%d]", MAC_GET_CB_IS_MCAST(pst_tx_ctl), MAC_GET_CB_IS_EAPOL(pst_tx_ctl));

        /* Increment activity counter */
        dmac_psm_sta_incr_activity_cnt(pst_mac_sta_pm_handle);
        return uc_pwr_mgmt_bit;
    }

    if (STA_PWR_SAVE_STATE_ACTIVE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
    {
        /* 传统AC重启activity定时器 */
        if (OAL_TRUE == dmac_is_legacy_ac(pst_dmac_vap, pst_tx_ctl)
			&&(((WLAN_NULL_FRAME !=  mac_get_cb_frame_hdr(pst_tx_ctl)->st_frame_control.bit_sub_type)
     			&&(WLAN_QOS_NULL_FRAME != mac_get_cb_frame_hdr(pst_tx_ctl)->st_frame_control.bit_sub_type))))
        {
            pst_mac_sta_pm_handle->ul_psm_pkt_cnt++;
        }
    }
    else
    {
        uc_pwr_mgmt_bit = 1;
        /*lint -e731*/
        /* In case the STA is in Doze state switch to AWAKE state */
        if ((STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))&& (OAL_FALSE == IS_P2P_PS_ENABLED(pst_dmac_vap)))
        {
            //OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_tx_process_data_sta::pm state:[%d] not awake}", STA_GET_PM_STATE(pst_mac_sta_pm_handle));
            dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TX_DATA, 0, OAL_PTR_NULL);
        }
        /*lint +e731*/
        if (STA_PWR_SAVE_STATE_ACTIVE == dmac_psm_process_tx_process_data_sta_prot(pst_dmac_vap, pst_tx_ctl))
        {
            if(OAL_TRUE == dmac_is_sta_fast_ps_enabled(pst_mac_sta_pm_handle))
            {
                /* 只有在awake状态下,tx data时才需要发送actice null 帧 */
                if ((STA_PWR_SAVE_STATE_AWAKE == STA_GET_PM_STATE(pst_mac_sta_pm_handle)))
                {
                    pst_mac_sta_pm_handle->en_send_active_null_frame_to_ap = OAL_TRUE;
                    uc_pwr_mgmt_bit = 0;
                }
            }
        }
    }
    return uc_pwr_mgmt_bit;
}
/*****************************************************************************
 函 数 名  : dmac_psm_tx_set_power_mgmt_bit
 功能描述  : 根据是否是节能，设置MAC头里的power_mgmt位
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月29日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_tx_set_power_mgmt_bit(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint8                 uc_pwr_mgmt_bit = 0;

    /* 检查是否是节能模式 */
    uc_pwr_mgmt_bit = dmac_psm_tx_process_data_sta(pst_dmac_vap, pst_tx_ctl);
    if (OAL_TRUE == uc_pwr_mgmt_bit)
    {
        mac_get_cb_frame_hdr(pst_tx_ctl)->st_frame_control.bit_power_mgmt = OAL_TRUE;
    }
}
/*****************************************************************************
 函 数 名  : dmac_null_frame_complete
 功能描述  : 如果当前STA处于非省电模式，则不做任何处理，只作定时器更新；
            如果STA处于省电模式，则判断当前发送的帧是否为NULL帧，对NULL帧再进行处理。
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_null_frame_complete_sta(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_dscr_status, oal_netbuf_stru  *pst_netbuf)
{
    mac_sta_pm_handler_stru             *pst_mac_sta_pm_handle;
    mac_ieee80211_frame_stru            *pst_mac_header;

    pst_mac_header = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_netbuf);
    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_null_frame_complete_sta::pst_mac_sta_pm_handle null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((OAL_TRUE == pst_mac_sta_pm_handle->st_null_wait.en_active_null_wait) ||
        (OAL_TRUE == pst_mac_sta_pm_handle->st_null_wait.en_doze_null_wait))
    {
        /* NULL帧发送成功的处理 */
        if (DMAC_TX_SUCC == uc_dscr_status)
        {
            /* PM的状态不应该处于DOZE状态，如果是此状态切换到awake状态 */
            if (STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
            {
                //OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_null_frame_complete_sta::pm state is [%d] not awake}", STA_GET_PM_STATE(pst_mac_sta_pm_handle));
                //OAL_IO_PRINT("dmac_null_frame_complete_sta::event:[%d] change state to doze not awake\r\n", pst_mac_sta_pm_handle->uc_doze_event);
                dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_SEND_NULL_SUCCESS, 0, OAL_PTR_NULL);
            }
            /* null 帧重传标志清零 */
            if (STA_PWR_SAVE_STATE_ACTIVE == pst_mac_header->st_frame_control.bit_power_mgmt)
            {
                pst_mac_sta_pm_handle->uc_active_null_retran_cnt = 0;

                pst_mac_sta_pm_handle->en_ps_back_active_pause = OAL_FALSE;
            }
            else
            {
                pst_mac_sta_pm_handle->uc_doze_null_retran_cnt = 0;

                pst_mac_sta_pm_handle->en_ps_back_doze_pause   = OAL_FALSE;
            }
            dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_SEND_NULL_SUCCESS, OAL_SIZEOF(mac_ieee80211_frame_stru), (oal_uint8 *)pst_mac_header);

        }
        /* NULL帧发送不成功,软重传10次,硬件重传8次(一共80次)后,对端依然没有响应,代表此时链路异常,去关联liuzhengqi todo */
        else
        {
            if ((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state))
            {
                /* If  transmission status is timeout reset the global flags and retransmit the NULL frame */
                if (STA_PWR_SAVE_STATE_ACTIVE == pst_mac_header->st_frame_control.bit_power_mgmt)
                {
                    pst_mac_sta_pm_handle->uc_active_null_retran_cnt++;

                    if (DMAC_TX_SOFT_PSM_BACK == uc_dscr_status)
                    {
                        pst_mac_sta_pm_handle->en_ps_back_active_pause = OAL_TRUE;
                    }

                    pst_mac_sta_pm_handle->st_null_wait.en_active_null_wait = OAL_FALSE;

                    /*唤醒的null帧重传失败,1、下次ap beacon告知缓存继续发送,2、主动唤醒,发下个数据帧继续发送唤醒null帧 */
                    if (pst_mac_sta_pm_handle->uc_active_null_retran_cnt > WLAN_MAX_NULL_SENT_NUM)
                    {
                        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_null_frame_complete_sta::sta_pm state[%d],retrans active null data to max cnt}",STA_GET_PM_STATE(pst_mac_sta_pm_handle));
                        pst_mac_sta_pm_handle->uc_active_null_retran_cnt = 0;
                        return OAL_SUCC;
                    }

                }
                else
                {
                    pst_mac_sta_pm_handle->uc_doze_null_retran_cnt++;

                    if (DMAC_TX_SOFT_PSM_BACK == uc_dscr_status)
                    {
                        pst_mac_sta_pm_handle->en_ps_back_doze_pause = OAL_TRUE;
                    }

                    pst_mac_sta_pm_handle->st_null_wait.en_doze_null_wait = OAL_FALSE;

                    if (pst_mac_sta_pm_handle->uc_doze_null_retran_cnt > WLAN_MAX_NULL_SENT_NUM)
                    {
                        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_null_frame_complete_sta::sta_pm state[%d],retrans sleep null data to max cnt}",STA_GET_PM_STATE(pst_mac_sta_pm_handle));

                        /* awake状态下发送睡眠null帧失败此时应该为keepalive的null帧,缩短下一次的keepalive的到来时间5s后触发 */
                        if ((STA_PWR_SAVE_STATE_AWAKE == STA_GET_PM_STATE(pst_mac_sta_pm_handle)))
                        {
                            pst_mac_sta_pm_handle->ul_ps_keepalive_cnt = (pst_mac_sta_pm_handle->ul_ps_keepalive_max_num) >> 2;
                        }

                        /* acticve->doze的睡眠null帧,重发WLAN_MAX_NULL_SENT_NUM次,重启定时器相当于延迟一个定时器时间再发 */
                        else
                        {
                            dmac_psm_start_activity_timer(pst_dmac_vap,pst_mac_sta_pm_handle);
                        }

                        pst_mac_sta_pm_handle->uc_doze_null_retran_cnt = 0;
                        return OAL_SUCC;
                    }
                }

                /* 非软件节能回退继续软件重传,否则在noa唤醒的时候发送此null帧 */
                if (DMAC_TX_SOFT_PSM_BACK != uc_dscr_status)
                {
                    if (OAL_SUCC != dmac_send_null_frame_to_ap(pst_dmac_vap, (oal_uint8)(pst_mac_header->st_frame_control.bit_power_mgmt), OAL_FALSE))
                    {
                        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_null_frame_complete_sta::retrans null data fail}");
                    }
                }
            }
        }
    }
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_psm_tx_complete_sta
 功能描述  : 如果当前STA处于非省电模式，则不做任何处理，只作定时器更新；
            如果STA处于省电模式，则判断当前发送的帧是否为NULL帧，对NULL帧再进行处理。
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_tx_complete_sta(dmac_vap_stru *pst_dmac_vap, hal_tx_dscr_stru  *pst_dscr, oal_netbuf_stru *pst_netbuf)
{
    hal_to_dmac_device_stru             *pst_hal_device;
    mac_ieee80211_frame_stru            *pst_mac_header;
    mac_sta_pm_handler_stru             *pst_mac_sta_pm_handle;
    oal_uint8                            uc_dscr_status;
    oal_uint8                            uc_subtype;

    /* p2p 扫描用dev 无低功耗状态机结构体，不需要进行低功耗处理 */
    if (IS_P2P_DEV(&(pst_dmac_vap->st_vap_base_info)))
    {
        return;
    }

    /* 非节能模式下的处理 */
    if ((mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_PWRSAVE)
         || (0 == pst_dmac_vap->st_vap_base_info.us_sta_aid))
    {
        dmac_psm_process_no_powersave(pst_dmac_vap);

        return;
    }

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    pst_hal_device        = pst_dmac_vap->pst_hal_device;
    if ((OAL_PTR_NULL == pst_mac_sta_pm_handle) || (OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_tx_complete_sta has null point pm_handle =%p hal_device=%p}}",pst_mac_sta_pm_handle,pst_hal_device);
        return;
    }

    /* 节能模式下的处理 */
    if (WLAN_MIB_PWR_MGMT_MODE_PWRSAVE == (mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info))))
    {
        pst_mac_header = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf);
        uc_subtype     =  mac_get_frame_sub_type((oal_uint8 *)pst_mac_header);

        /* 获取发送状态位 */
        hal_tx_get_dscr_status(pst_dmac_vap->pst_hal_device, pst_dscr, &uc_dscr_status);

        /* DTS2014052908727 发送成功情况:keep alive功能只有数据帧发送成功后才清0，避免因为probe req帧导致keep alive失效 */
        if ((DMAC_TX_SUCC == uc_dscr_status) && (WLAN_FC0_TYPE_DATA == mac_get_frame_type((oal_uint8 *)pst_mac_header)))
        {
            pst_mac_sta_pm_handle->ul_ps_keepalive_cnt = 0;
        }

        /* NULL帧的发送完成 */
        if ((WLAN_FC0_SUBTYPE_NODATA | WLAN_FC0_TYPE_DATA) == uc_subtype)
        {
            if (OAL_SUCC != (dmac_null_frame_complete_sta(pst_dmac_vap, uc_dscr_status, pst_netbuf)))
            {
                return;
            }
        }

        /* For non-NULL frame check if a NULL ACTIVE frame has to be sent to */
        /* the AP and then process the frame based on protocol.              */
        else
        {
            if ((OAL_TRUE == pst_mac_sta_pm_handle->en_send_active_null_frame_to_ap) &&
                    (OAL_FALSE == pst_mac_sta_pm_handle->st_null_wait.en_active_null_wait))
            {
                pst_mac_sta_pm_handle->en_send_active_null_frame_to_ap = OAL_FALSE;

                if (STA_PWR_SAVE_STATE_AWAKE == STA_GET_PM_STATE(pst_mac_sta_pm_handle))
                {
                    dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE);
                }
            }
            dmac_psm_process_tx_complete_sta_prot(pst_dmac_vap, uc_dscr_status, pst_netbuf);
        }
    }
}
/*****************************************************************************
 函 数 名  : dmac_psm_process_tbtt_sta
 功能描述  : 主要用于STA省电状态切换到AWAKE（包括RF上电，PHY上电的操作），
            等待接收BEACON帧。在收到BEACON帧后，通过查询TIM信息元素确定AP中是否有缓存帧
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月27日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_process_tbtt_sta(dmac_vap_stru *pst_dmac_vap, mac_device_stru  *pst_mac_device)
{
    mac_sta_pm_handler_stru         *pst_sta_pm_handle;
    oal_uint32                       ul_max_allow_sleep_time;
    oal_uint32                       ul_max_pl_sleep_time;

    pst_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_process_tbtt_sta::pst_sta_pm_handle null}");
        return;
    }

    if (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state)
    {
        /* 接收tbtt计数统计 */
        pst_sta_pm_handle->aul_pmDebugCount[PM_MSG_TBTT_CNT]++;
    }

    pst_sta_pm_handle->ul_ps_keepalive_cnt++;

    if ((mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_PWRSAVE)
        ||(0 == pst_dmac_vap->st_vap_base_info.us_sta_aid))
    {
        dmac_psm_process_no_powersave(pst_dmac_vap);
        return;
    }


    ul_max_allow_sleep_time = dmac_psm_get_max_sleep_time(pst_dmac_vap);
    ul_max_pl_sleep_time    = g_ul_max_deep_sleep_time > g_ul_max_light_sleep_time ? g_ul_max_deep_sleep_time : g_ul_max_light_sleep_time;

    /* 平台最大睡眠时间*/
    if (ul_max_pl_sleep_time > ul_max_allow_sleep_time)
    {
        OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id,OAM_SF_PWR,"{dmac_psm_process_tbtt_sta::deep sleep[%d]light sleep[%d] > allow[%d]}",g_ul_max_deep_sleep_time,g_ul_max_light_sleep_time,ul_max_allow_sleep_time);

        g_ul_max_deep_sleep_time   = 0;
        g_ul_max_light_sleep_time   = 0;

        /* 协议的关键计数 */
        dmac_pm_key_info_dump(pst_dmac_vap);

        /* 平台的睡眠计数*/
        PM_WLAN_DumpSleepCnt();
    }

    /* 协议的状态和平台的状态分开 */
    PM_WLAN_PsmHandle(pst_dmac_vap->pst_hal_vap->uc_service_id, PM_WLAN_WORK_PROCESS);
    dmac_pm_enable_front_end(pst_mac_device, OAL_FALSE);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD

    if ((pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_dpd_done == OAL_FALSE) &&
        (pst_dmac_vap->st_vap_base_info.en_p2p_mode == WLAN_LEGACY_VAP_MODE) &&
        (pst_dmac_vap->st_vap_base_info.en_vap_mode == WLAN_VAP_MODE_BSS_STA) &&
        (pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_dpd_enbale == OAL_TRUE) &&
        (pst_dmac_vap->st_vap_base_info.st_channel.en_band == WLAN_BAND_2G))
    {
        //DTS2015120303724 疯狂打印
        //OAM_WARNING_LOG2(0, 0, "mac_vap address 0x%x, vap id %d", &pst_dmac_vap->st_vap_base_info, pst_dmac_vap->st_vap_base_info.uc_vap_id);
        //pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_dpd_done = OAL_TRUE;
        //dmac_start_dpd_calibration(&pst_dmac_vap->st_vap_base_info);
    }
#endif
    /* p2p noa可以在active状态浅睡,tbtt中断后需要确定收到了beacon才能noa浅睡 */
    pst_sta_pm_handle->en_beacon_frame_wait         = OAL_TRUE;

    /* pspoll节能模式下,设置beacon等待标志，如果目前状态为doze，切换到awake状态 */
    if (STA_GET_PM_STATE(pst_sta_pm_handle) != STA_PWR_SAVE_STATE_ACTIVE)
    {
        if (STA_PWR_SAVE_STATE_DOZE == STA_GET_PM_STATE(pst_sta_pm_handle))
        {
            pst_sta_pm_handle->en_more_data_expected    = OAL_FALSE;
            dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TBTT, 0, OAL_PTR_NULL);
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_psm_is_tid_queues_empty
 功能描述  : 硬件发送队列是否为空
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  dmac_psm_is_hw_queues_empty(mac_device_stru  *pst_device)
{
    hal_to_dmac_device_stru         *pst_hal_device;
    oal_uint8                        uc_queue_num;

    
    /*低功耗前面的流程已检查过合法性，不需要重复检查*/
    pst_hal_device = pst_device->pst_device_stru;

    /* 硬件发送队列 */
    for (uc_queue_num = 0; uc_queue_num < HAL_TX_QUEUE_BUTT; uc_queue_num++)
    {
        /*对应的硬件队列检查 */
        if (OAL_FALSE == (oal_dlist_is_empty(&(pst_hal_device->ast_tx_dscr_queue[uc_queue_num].st_header))))
        {
            //PRINT("{hw queue[%d]not empty}\r\n", uc_queue_num);
            return OAL_FALSE;
        }
    }

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : dmac_psm_is_tid_queues_empty
 功能描述  : STA的TID是否为空
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  dmac_psm_is_tid_queues_empty(dmac_vap_stru  *pst_dmac_vap)
{
    dmac_user_stru                   *pst_user;
    oal_uint8                        uc_tid_idx;

    /* TID队列 */
    pst_user = (dmac_user_stru *)mac_res_get_dmac_user((oal_uint16)(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id));

    if (OAL_PTR_NULL != pst_user)
    {
        if (OAL_FALSE == dmac_psm_is_tid_empty(pst_user))
        {
            //PM_WLAN_PRINT("{tid queue not empty,psm state[%d]}\r\n",dmac_psm_get_state(pst_dmac_vap));

            for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx ++)
            {
                if(pst_user->ast_tx_tid_queue[uc_tid_idx].us_mpdu_num)
                {
                    PM_WLAN_PRINT("TID[%d],mpdu_num[%d],retry[%d],paused[%d]\r\n",uc_tid_idx,
                          pst_user->ast_tx_tid_queue[uc_tid_idx].us_mpdu_num,
                          pst_user->ast_tx_tid_queue[uc_tid_idx].uc_retry_num,
                          pst_user->ast_tx_tid_queue[uc_tid_idx].uc_is_paused);
                }
            }
            //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_KEEPALIVE, "psm call back::tid queue not empty");
            return OAL_FALSE;
        }
        return OAL_TRUE;
    }
    else
    {
        return OAL_TRUE;
    }

}


/*****************************************************************************
 函 数 名  : dmac_psm_is_tx_queues_empty
 功能描述  : STA的发送队列(硬件队列、TID队列)是否为空
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  dmac_psm_is_tx_queues_empty(dmac_vap_stru  *pst_dmac_vap)
{
    oal_uint8 uc_ret = OAL_TRUE;
    mac_device_stru  *pst_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

    if(OAL_FALSE == dmac_psm_is_hw_queues_empty(pst_device))
    {
        uc_ret =  OAL_FALSE;
    }

    if(OAL_FALSE == dmac_psm_is_tid_queues_empty(pst_dmac_vap))
    {
        uc_ret = OAL_FALSE;
    }

    return uc_ret;
}

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

/*****************************************************************************
 函 数 名  : dmac_send_pspoll_to_ap
 功能描述  : 发送ps_poll帧给AP，以获取缓存的数据。
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_send_pspoll_to_ap(dmac_vap_stru *pst_dmac_vap)
{
    oal_netbuf_stru                     *pst_net_buf;
    mac_tx_ctl_stru                     *pst_tx_ctrl;
    oal_uint32                           ul_ret;
    oal_uint16                           us_frame_ctl;
    dmac_user_stru                      *pst_dmac_user;
    mac_ieee80211_pspoll_frame_stru     *pst_pspoll_frame_hdr;

    /* 申请net_buff */
    pst_net_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_send_pspoll_to_ap::pst_netbuf null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    oal_set_netbuf_prev(pst_net_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

    pst_pspoll_frame_hdr = (mac_ieee80211_pspoll_frame_stru *)OAL_NETBUF_HEADER(pst_net_buf);

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user((oal_uint16)(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_send_pspoll_to_ap::null pointer,pst_dmac_user[%d].}", pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
        oal_netbuf_free(pst_net_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 设置pspoll的frame control域 */
    us_frame_ctl  = WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_CTL | WLAN_FC0_SUBTYPE_PS_POLL; //低八位
    us_frame_ctl |= (WLAN_FC1_DIR_NODS << 8 ) | (WLAN_FC1_PWR_MGT << 8); //高八位
    mac_hdr_set_frame_control((oal_uint8 *)pst_pspoll_frame_hdr, us_frame_ctl);

    /* Set bits 14 and 15 to 1 when duration field carries Association ID */
    pst_pspoll_frame_hdr->bit_aid_value = WLAN_AID(pst_dmac_vap->st_vap_base_info.us_sta_aid);
    pst_pspoll_frame_hdr->bit_aid_flag1 = OAL_TRUE;
    pst_pspoll_frame_hdr->bit_aid_flag2 = OAL_TRUE;

    /* mode, Address1 = BSSID, Address2 = Source Address (SA) */
    oal_set_mac_addr(pst_pspoll_frame_hdr->auc_bssid, pst_dmac_user->st_user_base_info.auc_user_mac_addr);
    oal_set_mac_addr(pst_pspoll_frame_hdr->auc_trans_addr, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* 填写cb字段 */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    OAL_MEMZERO(pst_tx_ctrl, OAL_SIZEOF(mac_tx_ctl_stru));

    /* 填写tx部分 */
    mac_set_cb_ack_policy(pst_tx_ctrl, WLAN_TX_NORMAL_ACK);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctrl)         = FRW_EVENT_TYPE_WLAN_DTX;
    mac_set_cb_is_bar(pst_tx_ctrl, OAL_FALSE);
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl)         = OAL_TRUE;
    MAC_GET_CB_RETRIED_NUM(pst_tx_ctrl)           = 0;
    mac_set_cb_tid(pst_tx_ctrl, WLAN_TID_FOR_DATA);
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctrl)          = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)           = pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id; //sta方式和ap不一样

    /* 填写tx rx公共部分 */
    MAC_GET_CB_IS_MCAST(pst_tx_ctrl)            = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_ctrl, OAL_FALSE);
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)   = OAL_TRUE;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctrl)       = OAL_FALSE;
    mac_set_cb_is_use_4_addr(pst_tx_ctrl, OAL_FALSE);
    mac_set_cb_frame_hdr(pst_tx_ctrl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)    = OAL_SIZEOF(mac_ieee80211_frame_stru);
    MAC_GET_CB_MPDU_NUM(pst_tx_ctrl)               = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl)             = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctrl)               = 0;
    mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_AC_MGMT);

    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, OAL_SIZEOF(mac_ieee80211_pspoll_frame_stru));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                 "{dmac_send_pspoll_to_ap failed[%d].}", ul_ret);
        dmac_tx_excp_free_netbuf(pst_net_buf);
        return ul_ret;
    }
    /* Do the protocol specific processing */
    dmac_send_ps_poll_to_ap_prot(pst_dmac_vap);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_send_null_frame_to_ap_opt
 功能描述  : null帧发送后状态机的NULL帧等待变量切换
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_send_null_frame_to_ap_opt(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_psm, oal_bool_enum_uint8 en_qos)
{
    mac_sta_pm_handler_stru  *pst_sta_pm_handle;

    pst_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                            "{dmac_send_null_frame_to_ap_opt::pst_sta_pm_handle NULL");
        return;
    }

    if(OAL_FALSE == en_qos)
    {
        if(STA_PWR_SAVE_STATE_ACTIVE == uc_psm)
        {
            pst_sta_pm_handle->st_null_wait.en_active_null_wait = OAL_TRUE;
            pst_sta_pm_handle->st_null_wait.en_doze_null_wait   = OAL_FALSE;
        }
        else
        {
            pst_sta_pm_handle->st_null_wait.en_active_null_wait = OAL_FALSE;
            pst_sta_pm_handle->st_null_wait.en_doze_null_wait   = OAL_TRUE;
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_send_null_frame_to_ap
 功能描述  : 组一个NULL帧，发送给AP
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_send_null_frame_to_ap(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_psm, oal_bool_enum_uint8 en_qos)
{
    oal_uint32      ul_ret = OAL_SUCC;
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    oal_uint32      uc_ac = WLAN_WME_AC_BE; //qos的ac默认为be，后续再根据业务需要动态获取
#endif
    oal_uint8       en_ps;
    dmac_user_stru  *pst_dmac_user;

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
	oal_uint8       uc_tid;
#endif
    mac_device_stru     *pst_device;

    if ((OAL_PTR_NULL == pst_dmac_vap) || (uc_psm >= STA_PWR_SAVE_STATE_BUTT))
    {
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "{dmac_send_null_frame_to_ap::pst_dmac_vap [%d], en_psm [%d]}",
                        (oal_uint32)pst_dmac_vap, uc_psm);
        return OAL_FAIL;
    }

    pst_device      = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_send_null_frame_to_ap::pst_device[%d] is NULL!}", pst_dmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* DBAC running 不发送null帧，此时低功耗关闭,睡眠定时器可以停掉,dbac后再开低功耗 */
    if(OAL_TRUE == mac_is_dbac_running(pst_device))
    {
        return OAL_SUCC;
    }

    /* 不是UP状态,不发送null帧 */
    if (MAC_VAP_STATE_UP != pst_dmac_vap->st_vap_base_info.en_vap_state)
    {
        return OAL_FAIL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user((oal_uint16)(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id));
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_send_null_frame_to_ap::pst_dmac_vap [%d],pst_dmac_user NULL, AID = [%d]}", pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 设置pm位是否置true */
    en_ps = (uc_psm > 0) ? 1 : 0;

    //OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"{dmac_send_null_frame_to_ap::ps:[%d],return addr[0x%x]}", en_ps,__return_address());
    if(OAL_FALSE == en_qos)
    {
        ul_ret = dmac_psm_send_null_data(pst_dmac_vap, pst_dmac_user, en_ps);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                 "{dmac_send_null_frame_to_ap::dmac_psm_send_null_data failed[%d].}", ul_ret);
            return ul_ret;
        }
    }

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    else
    {
        uc_tid = dmac_get_highest_trigger_enabled_priority(pst_dmac_vap);
        uc_ac = WLAN_WME_TID_TO_AC(uc_tid);

        ul_ret = dmac_send_qosnull(pst_dmac_vap, pst_dmac_user, (oal_uint8)uc_ac, en_ps);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                 "{dmac_send_null_frame_to_ap::dmac_send_qosnull failed[%d].}", ul_ret);
            return ul_ret;
        }

    }
#endif
    if (mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_ACTIVE)
    {
        dmac_send_null_frame_to_ap_opt(pst_dmac_vap, uc_psm, en_qos);
    }
    return ul_ret;
}


/*****************************************************************************
 函 数 名  : dmac_psm_alarm_callback
 功能描述  : 节能定时器（Activity Timer）主要用于监控STA的工作状态，
            当STA完成一次操作发送或接收这个定时器都被重新启动。
            如果一段时间没有检测到STA有动作，则STA将进入DOZE模式。
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_psm_alarm_callback(void *p_arg)
{
    dmac_vap_stru                   *pst_dmac_vap;
    mac_sta_pm_handler_stru         *pst_sta_pm_handle;
    oal_uint32                       ul_ps_ret = OAL_SUCC;
    oal_uint8                        uc_doze_trans_flag;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_device_stru                 *pst_mac_device;
#endif
    pst_dmac_vap                    = (dmac_vap_stru *)(p_arg);

    pst_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

#ifdef _PRE_WLAN_FEATURE_P2P
    pst_mac_device  = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
       OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_alarm_callback::pst_mac_device is null.}");
       return OAL_SUCC;
    }

    /* p2p节能开启,如果处于pause状态,重启定时器 */
    if ((OAL_TRUE == (oal_uint8)IS_P2P_PS_ENABLED(pst_dmac_vap)) && (OAL_TRUE == pst_mac_device->st_p2p_info.en_p2p_ps_pause))
    {
        dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);
        pst_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_RESTART_P2P_PAUSE]++;

        return OAL_SUCC;
    }
#endif

    pst_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    if ((mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_PWRSAVE) &&
        (OAL_FALSE == dmac_psm_sta_is_activity_cnt_zero(pst_sta_pm_handle)))
    {
        /* restart 定时器 */
        dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);
        pst_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_TIMEOUT_PM_OFF]++;

        dmac_psm_sta_reset_activity_cnt(pst_sta_pm_handle);

        return OAL_SUCC;
    }

    /* 超时切doze的条件 */
    uc_doze_trans_flag = (pst_sta_pm_handle->en_beacon_frame_wait) | (pst_sta_pm_handle->st_null_wait.en_doze_null_wait << 1) | (pst_sta_pm_handle->en_more_data_expected << 2)
            | (pst_sta_pm_handle->st_null_wait.en_active_null_wait << 3) | (pst_sta_pm_handle->en_send_active_null_frame_to_ap << 4);


    /* STA的发送队列(TID队列)是否为空,因为会多vap共存,单vap不检查硬件队列 */

    /* 队列不为空,restart定时器 */
    if (OAL_TRUE != dmac_psm_is_tid_queues_empty(pst_dmac_vap))
    {
        dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);
        pst_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_TIMEOUT_QUEUE_NO_EMPTY]++;
    }
    else if(pst_sta_pm_handle->ul_psm_pkt_cnt)
    {
        dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);
        pst_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_TIMEOUT_PKT_CNT]++;
        pst_sta_pm_handle->ul_psm_pkt_cnt = 0;
        pst_sta_pm_handle->uc_psm_timer_restart_cnt = 0; //有包收发从start count重头开始计
    }
     /* 队列为空,分低功耗模式和非低功耗KEEPALVIVE模式 */
    else
    {
        if (WLAN_MIB_PWR_MGMT_MODE_PWRSAVE == (mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info))))
        {
            /* uc_doze_trans_flag条件不满足,不需等待uc_psm_timer_restart_cnt*g_device_wlan_pm_timeout时间,只需下一个g_device_wlan_pm_timeout */
            pst_sta_pm_handle->uc_psm_timer_restart_cnt++;

            /* 节能模式下的超时函数只有在非doze的情况下才作用 */
            if (STA_PWR_SAVE_STATE_DOZE != STA_GET_PM_STATE(pst_sta_pm_handle))
            {
                /* 此处, 从非节能的active态可以切换到节能的doze态 */
                if((OAL_FALSE == uc_doze_trans_flag) && (pst_sta_pm_handle->uc_psm_timer_restart_cnt >= g_pm_timer_restart_cnt))
                {
                    pst_sta_pm_handle->uc_timer_fail_doze_trans_cnt = 0;

                    if (OAL_TRUE == dmac_is_sta_fast_ps_enabled(pst_sta_pm_handle))
                    {
                        ul_ps_ret = dmac_psm_process_fast_ps_state_change(pst_dmac_vap, STA_PWR_SAVE_STATE_DOZE);
                    }
                    else
                    {
                        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TIMEOUT, 0, OAL_PTR_NULL);
                    }

                    pst_sta_pm_handle->uc_psm_timer_restart_cnt = 0; //满足睡眠条件计数清0,即使null帧发送失败，下一次也还是重头计数
                }
                else
                {
                    pst_sta_pm_handle->uc_timer_fail_doze_trans_cnt++;

                    pst_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_RESTART_A]++;

                    /* 重启activity 定时器 */
                    dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);
                }
            }
            else
            {
                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_alarm_callback::event:[%d]change pm state doze.}", pst_sta_pm_handle->uc_doze_event);
            }

            if (DMAC_TIMER_DOZE_TRANS_FAIL_NUM < pst_sta_pm_handle->uc_timer_fail_doze_trans_cnt)
            {
                OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_alarm_callback::pm state:[%d],doze trans flag:[%d]timer restart cnt[%d].}", STA_GET_PM_STATE(pst_sta_pm_handle),uc_doze_trans_flag,pst_sta_pm_handle->uc_psm_timer_restart_cnt);
                pst_sta_pm_handle->uc_timer_fail_doze_trans_cnt = 0;
            }
        }

        /* If no data is expected and the STA is not in power save send a NULL frame to AP indicating that STA is alive and active.  */
        /* Restart the activity timer with increased timeout.*/
        else
        {
            if (OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_keepalive)
            {
                ul_ps_ret = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_ACTIVE, OAL_FALSE);
                dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);
                pst_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_RESTART_B]++;
            }
        }

        if(OAL_SUCC != ul_ps_ret)
        {
            /* fast模式切换失败重启activity 定时器 */
            pst_sta_pm_handle->aul_pmDebugCount[PM_MSG_PSM_RESTART_C]++;
            dmac_psm_start_activity_timer(pst_dmac_vap,pst_sta_pm_handle);

            return ul_ps_ret;
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_get_state
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : z00274374
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8  dmac_psm_get_state(dmac_vap_stru* pst_dmac_vap)
{
    mac_sta_pm_handler_stru     *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_get_state::pst_mac_sta_pm_handle null.}");
        return STA_PWR_SAVE_STATE_ACTIVE;
    }

    return STA_GET_PM_STATE(pst_mac_sta_pm_handle);
}

#endif /*_PRE_WLAN_FEATURE_STA_PM*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

