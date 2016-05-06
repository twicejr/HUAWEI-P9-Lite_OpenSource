/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_uapsd_sta.c
  版 本 号   : 初稿
  作    者   : l00280485
  生成日期   : 2014年12月19日
  最近修改   :
  功能描述   : sta uapsd特性所在函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月19日
    作    者   : l00280485
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "dmac_uapsd_sta.h"
#include "dmac_psm_sta.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_UAPSD_STA_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_uapsd_trigger_sp_sta
 功能描述  : 确定是否发送qos null帧触发一个uapsd sp
 输入参数  : pst_dmac_vap:dmac_vap 结构体
 输出参数  : oal_void
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_uapsd_trigger_sp_sta(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8                 uc_tid;
    oal_uint32                ul_ret;
    mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_trigger_sp_sta::pst_mac_sta_pm_handle null}");
        return;
    }

    DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_trigsp);

    /* The service period is triggered only if it is not in progress. If in  */
    /* progress or waiting to start there is no need to trigger. Do nothing. */
    if(OAL_FALSE == dmac_is_uapsd_sp_not_in_progress(pst_mac_sta_pm_handle))
    {
        pst_mac_sta_pm_handle->uc_eosp_timeout_cnt++;

        if(pst_mac_sta_pm_handle->uc_eosp_timeout_cnt <= DMAC_STA_EOSP_TIMEOUT_CNT)
        {
            DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_trspnr);
            return;
        }
        else
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_trigger_sp_sta::ESOP [%d] TIMEOUT}", pst_mac_sta_pm_handle->uc_eosp_timeout_cnt);
        }
    }

    uc_tid = dmac_get_highest_trigger_enabled_priority(pst_dmac_vap);

    /* If no trigger enabled AC is found the STA is unable to start a UAPSD  */
    /* service period and can switch back to DOZE mode.                      */
    if(WLAN_TID_MAX_NUM == uc_tid)
    {
        if (OAL_TRUE == dmac_psm_is_tid_queues_empty(pst_dmac_vap))
        {
            pst_mac_sta_pm_handle->en_ps_deep_sleep = OAL_TRUE;
            dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_NORMAL_SLEEP, 0, OAL_PTR_NULL);
        }
    }

    /* If a trigger enabled AC is found the STA sends a QoS NULL trigger     */
    /* frame from this AC and starts the UAPSD service period.               */
    else
    {
        //OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_trigger_sp_sta::send QOS NULL[%d]}", uc_tid);
        dmac_wait_uapsd_sp_start(pst_mac_sta_pm_handle);
        ul_ret = dmac_send_null_frame_to_ap(pst_dmac_vap, STA_PWR_SAVE_STATE_DOZE, OAL_TRUE);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_trigger_sp_sta::dmac_send_null_frame_to_ap to active failed[%d]}", ul_ret);
            return;
        }
    	pst_mac_sta_pm_handle->uc_eosp_timeout_cnt = 0;
    }
}
/*****************************************************************************
 函 数 名  : dmac_uapsd_rx_process_data_sta
 功能描述  : uapsd 特性下接收数据的处理
 输入参数  : pst_dmac_vap:dmac_vap 结构体
 输出参数  : oal_void
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_uapsd_rx_process_data_sta(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    oal_uint8                   uc_tid;
    mac_tx_ctl_stru             *pst_ctl;
    mac_sta_pm_handler_stru     *pst_mac_sta_pm_handle;
    mac_ieee80211_frame_stru    *pst_frame_hdr;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_rx_process_data_sta::pst_mac_sta_pm_handle null}");
        return;
    }

    pst_frame_hdr = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_netbuf);
    pst_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    uc_tid = mac_get_cb_tid(pst_ctl);

    /* Received frames are processed only for delivery enabled ACs */
   if(OAL_TRUE == dmac_is_delivery_enabled(pst_dmac_vap, uc_tid))
   {
       /* TAG-ITTIAM新增代码合入 */
       /* Reception of packets within a SP indicates there is no hang       */
       /* Hence reset the eosp timeout counter which is used to track any   */
       /* such hang scenearios                                              */
       if(OAL_FALSE == dmac_is_uapsd_sp_not_in_progress(pst_mac_sta_pm_handle))
       {
           pst_mac_sta_pm_handle->uc_eosp_timeout_cnt = 0;
       }

       /* If EOSP is set indicating the UAPSD service period is ended check */
       /* what the STA should do next.                                      */
       if(1 == dmac_get_eosp(pst_netbuf))
       {
           /* Stop the UAPSD service period */
           dmac_stop_uapsd_sp(pst_mac_sta_pm_handle);

           if(OAL_TRUE == dmac_psm_get_more_data_sta(pst_frame_hdr))
           {
               /* If More Data bit is set it indicates that the AP has more */
               /* packets buffered for STA. In this case trigger a service  */
               /* period.                                                   */
               dmac_uapsd_trigger_sp_sta(pst_dmac_vap);
           }
           else
           {

                if (OAL_TRUE == dmac_psm_is_tid_queues_empty(pst_dmac_vap))
                {
                    /* If More Data bit is not set go back to doze */
                    pst_mac_sta_pm_handle->en_ps_deep_sleep = OAL_TRUE;
                    dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_NORMAL_SLEEP, 0, OAL_PTR_NULL);
                }
           }
       }
   }
   else if(OAL_TRUE == dmac_is_trigger_enabled(pst_dmac_vap, uc_tid))
   {
       /* Exception case. Should not occur. If it is an only trigger        */
       /* AC there should be no downlink traffic.                           */
       DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_tacdl);
   }

}
/*****************************************************************************
 函 数 名  : dmac_uapsd_tx_process_data_sta
 功能描述  : This functions handles a packet transmission event for STA mode based on
                the protocol defined
 输入参数  : pst_dmac_vap:dmac_vap 结构体 pst_tx_ctl: TX CB
 输出参数  : oal_void
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_uapsd_tx_process_data_sta(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint8                 uc_tid;
    mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    uc_tid = mac_get_cb_tid(pst_tx_ctl);

    /* If the AP is UAPSD capable and the AC for given priority is trigger   */
    /* enabled the UAPSD service period is started. Note that the frame      */
    /* transmission status needs to be checked before actually starting the  */
    /* service period. This is done during transmit complete processing.     */
    /* The power save state is STA_DOZE so that the AP continues to buffer   */
    /* packets for this STA                                                  */
    if(OAL_TRUE == dmac_is_ap_uapsd_capable(pst_dmac_vap))
    {
        if(OAL_TRUE == dmac_is_trigger_enabled(pst_dmac_vap, uc_tid))
        {
            dmac_wait_uapsd_sp_start(pst_mac_sta_pm_handle);
            return STA_PWR_SAVE_STATE_DOZE;
        }

        else if(OAL_TRUE == dmac_is_delivery_enabled(pst_dmac_vap, uc_tid))
        {
            /* Exception case. Should not occur. If it is an only delivery   */
            /* enabled AC there should be no uplink traffic.                 */
    		DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_dacul);
        }
    }

    return STA_PWR_SAVE_STATE_ACTIVE;
}

/*****************************************************************************
 函 数 名  : dmac_uapsd_process_tx_complete_sta
 功能描述  : uapsd 特性下发送完成中断的处理
 输入参数  : pst_dmac_vap:dmac_vap 结构体 uc_dscr_status:发送描述符的状态 pst_netbuf: netbuf结构体
 输出参数  : oal_void
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月20日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_uapsd_process_tx_complete_sta(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_dscr_status, oal_netbuf_stru *pst_netbuf)
{
    oal_uint8                        uc_tid;
    mac_tx_ctl_stru                 *pst_ctl;
    mac_sta_pm_handler_stru         *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    pst_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
    uc_tid = mac_get_cb_tid(pst_ctl);

    if((dmac_is_uapsd_sp_wait_in_progress(pst_mac_sta_pm_handle) == OAL_TRUE) &&
       (dmac_is_trigger_frame(pst_dmac_vap, pst_netbuf, uc_tid) == OAL_TRUE))
    {

        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_process_tx_complete_sta::dmac_start_uapsd_sp\r\n}");

        if(DMAC_TX_SUCC == uc_dscr_status)
        {
            dmac_start_uapsd_sp(pst_mac_sta_pm_handle);
        }
        else
        {
            dmac_stop_uapsd_sp(pst_mac_sta_pm_handle);
            dmac_uapsd_trigger_sp_sta(pst_dmac_vap);
        }
    }
    else
    {
        /* Do nothing */
    }
}

#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

