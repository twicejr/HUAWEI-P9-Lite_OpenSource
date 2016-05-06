/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_uapsd.c
  版 本 号   : 初稿
  作    者   : huxiaotong
  生成日期   : 2012年12月17日
  最近修改   :
  功能描述   : uapsd特性操作的源文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月17日
    作    者   : huxiaotong
    修改内容   : 创建文件
  2.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 重新设计实现
******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_net.h"
#include "wlan_spec.h"
#include "hal_ext_if.h"
#include "mac_frame.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_user.h"
#include "dmac_psm_ap.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_rx_data.h"
#include "dmac_uapsd.h"
#include "dmac_config.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_UAPSD_C

#define  DMAC_UAPSD_INVALID_TRIGGER_SEQ 0xffff

OAL_STATIC oal_void  dmac_uapsd_print_info(dmac_user_stru *pst_dmac_user);

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_uapsd_usr_init
 功能描述  : USR初始化时u-apsd的初始化
 输入参数  : pst_dmac_usr
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_uapsd_user_init(dmac_user_stru * pst_dmac_usr)
{
    dmac_user_uapsd_stru       *pst_uapsd_stru;
    /*调用者保证入参指针非空*/
    pst_uapsd_stru = &(pst_dmac_usr->st_uapsd_stru);
#ifdef _PRE_WLAN_DFT_STAT
    pst_uapsd_stru->pst_uapsd_statis = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,OAL_SIZEOF(dmac_usr_uapsd_statis_stru),OAL_TRUE);
    if(OAL_PTR_NULL == pst_uapsd_stru->pst_uapsd_statis)
    {
        OAM_ERROR_LOG2(pst_dmac_usr->st_user_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_user_init:: user[%d] alloc uapsd_statis mem fail, size[%d]!}",
                    pst_dmac_usr->st_user_base_info.us_assoc_id,
                    OAL_SIZEOF(dmac_usr_uapsd_statis_stru));
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    OAL_MEMZERO(pst_uapsd_stru->pst_uapsd_statis, OAL_SIZEOF(dmac_usr_uapsd_statis_stru));
#endif
    oal_spin_lock_init(&(pst_uapsd_stru->st_lock_uapsd));
    oal_netbuf_list_head_init(&(pst_uapsd_stru->st_uapsd_queue_head));
    oal_atomic_set(&pst_uapsd_stru->uc_mpdu_num,0);
    pst_uapsd_stru->us_uapsd_trigseq[WLAN_WME_AC_BK] = DMAC_UAPSD_INVALID_TRIGGER_SEQ;
    pst_uapsd_stru->us_uapsd_trigseq[WLAN_WME_AC_BE] = DMAC_UAPSD_INVALID_TRIGGER_SEQ;
    pst_uapsd_stru->us_uapsd_trigseq[WLAN_WME_AC_VI] = DMAC_UAPSD_INVALID_TRIGGER_SEQ;
    pst_uapsd_stru->us_uapsd_trigseq[WLAN_WME_AC_VO] = DMAC_UAPSD_INVALID_TRIGGER_SEQ;

    /*还要初始化mac_usr结构中参数*/
    OAL_MEMZERO(&(pst_dmac_usr->st_uapsd_status),OAL_SIZEOF(mac_user_uapsd_status_stru));
    pst_dmac_usr->uc_uapsd_flag = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_uapsd_usr_destroy
 功能描述  : USR删除时u-apsd资源的销毁
 输入参数  : pst_dmac_usr
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

oal_void  dmac_uapsd_user_destroy(dmac_user_stru *pst_dmac_usr)
{
    dmac_user_uapsd_stru       *pst_uapsd_stru;

    oal_netbuf_stru             *pst_net_buf;

    /*调用者保证入参指针非空*/
    pst_uapsd_stru = &(pst_dmac_usr->st_uapsd_stru);

#ifdef _PRE_WLAN_DFT_STAT
    /* 首先，释放统计计数器占用的内存 */
    if(OAL_PTR_NULL != pst_uapsd_stru->pst_uapsd_statis)
    {
        OAL_MEM_FREE(pst_uapsd_stru->pst_uapsd_statis, OAL_TRUE);
        pst_uapsd_stru->pst_uapsd_statis = OAL_PTR_NULL;
    }
#endif

    /* 释放节能队列中的mpdu */
    oal_spin_lock(&pst_uapsd_stru->st_lock_uapsd);
    while (0 != oal_atomic_read(&pst_uapsd_stru->uc_mpdu_num))
    {
        pst_net_buf = dmac_tx_dequeue_first_mpdu(&pst_uapsd_stru->st_uapsd_queue_head);

        if(OAL_PTR_NULL == pst_net_buf)
        {
            break;
        }
        oal_atomic_dec(&pst_uapsd_stru->uc_mpdu_num);
        dmac_tx_excp_free_netbuf(pst_net_buf);

    }
    oal_spin_unlock(&pst_uapsd_stru->st_lock_uapsd);

    return ;

}

/*****************************************************************************
 函 数 名  : dmac_uapsd_tx_enqueue
 功能描述  : 发送时报文入UAPSD队列
 输入参数  : pst_dmac_vap:
             pst_dmac_usr:
             pst_net_buf: 待入队列的netbuf链,可能是多个MPDU
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_uapsd_tx_enqueue(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_netbuf_stru *pst_net_buf)
{
	oal_netbuf_stru        *pst_first_net_buf;
    oal_netbuf_stru        *pst_netbuf;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint8               uc_netbuf_num_in_mpdu;
#endif
    mac_tx_ctl_stru        *pst_tx_ctrl;
    oal_uint8               uc_max_qdepth;
    mac_ieee80211_frame_stru *pst_frame_hdr = OAL_PTR_NULL;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_usr_uapsd_statis_stru *pst_uapsd_statis;

    pst_uapsd_statis = pst_dmac_user->st_uapsd_stru.pst_uapsd_statis;
    if(OAL_PTR_NULL == pst_uapsd_statis)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_tx_enqueue::pst_uapsd_statis null.}");
        return OAL_FAIL;
    }
#endif

    DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_tx_enqueue_count);

    /* 获取U-APSD队列的最大允许长度和当前队列长度 */
    uc_max_qdepth = pst_dmac_vap->uc_uapsd_max_depth;

    /* 判断是否需要更新bitmap */
    if ((0 == oal_atomic_read(&pst_dmac_user->st_uapsd_stru.uc_mpdu_num))
        && MAC_USR_UAPSD_USE_TIM(pst_dmac_user))
    {
        /* 调用PSM的TIM设置接口 */
        //OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_TX,
        //              "dmac_uapsd_rx_trigger_check:set PVB to 1,usr id = %d",
        //              pst_dmac_user->st_user_base_info.us_assoc_id);

        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 1);
    }

    //OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_TX,
    //               "dmac_uapsd_tx_enqueue:before enqueue, the num of mpdus in uapsd queue are %d:",
    //               oal_atomic_read(&pst_dmac_user->st_uapsd_stru.uc_mpdu_num));


    /* 对UAPSD节能队列进行操作，加锁保护 */
    oal_spin_lock(&pst_dmac_user->st_uapsd_stru.st_lock_uapsd);

    pst_first_net_buf = pst_net_buf;
    while ((oal_atomic_read(&pst_dmac_user->st_uapsd_stru.uc_mpdu_num) < uc_max_qdepth)
            && (OAL_PTR_NULL != pst_first_net_buf))
    {
        /* 从每一个mpdu中第一个net_buf的CB字段获取该mpdu一共包含几个net_buff */
        pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_first_net_buf);

        /*入队时设置more data bit，减少出队时的操作*/
        pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_ctrl);
        pst_frame_hdr->st_frame_control.bit_more_data = 0x01;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        uc_netbuf_num_in_mpdu = MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl);
#endif

        /* 将该mpdu的每一个net_buff加入到节能队列中 */
        pst_netbuf = pst_first_net_buf;
        while (
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            (0 != uc_netbuf_num_in_mpdu) &&
#endif
            (OAL_PTR_NULL != pst_netbuf))
        {
            pst_first_net_buf = oal_get_netbuf_next(pst_netbuf);

            oal_netbuf_add_to_list_tail(pst_netbuf, &pst_dmac_user->st_uapsd_stru.st_uapsd_queue_head);

            pst_netbuf = pst_first_net_buf;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            uc_netbuf_num_in_mpdu--;
#endif
        }
        /* 更新节能队列中mpdu的个数 */
        oal_atomic_inc(&pst_dmac_user->st_uapsd_stru.uc_mpdu_num);

    }

    oal_spin_unlock(&pst_dmac_user->st_uapsd_stru.st_lock_uapsd);

    /*
       判断是mpdu全都入队了还是队列满了，如果是因为队列满了并且还有mpdu没有入队，
       则将剩下的mpdu释放
    */
    if ((uc_max_qdepth == oal_atomic_read(&pst_dmac_user->st_uapsd_stru.uc_mpdu_num))
        && (OAL_PTR_NULL != pst_first_net_buf))
    {
        dmac_tx_excp_free_netbuf(pst_first_net_buf);

        DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_tx_enqueue_free_count);

        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_uapsd_tx_enqueue::some mpdus are released due to queue full.}");
    }

    return OAL_SUCC;

}

OAL_STATIC oal_uint32 dmac_uapsd_state_trans(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,mac_ieee80211_qos_frame_stru *pst_mac_header)
{
    dmac_user_uapsd_stru            *pst_uapsd_stru;
    oal_uint8                       uc_uapsd_flag;
    oal_int32                       ul_uapsd_qdepth;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_usr_uapsd_statis_stru      *pst_uapsd_statis;

    pst_uapsd_statis = pst_dmac_user->st_uapsd_stru.pst_uapsd_statis;
#endif


    pst_uapsd_stru = &pst_dmac_user ->st_uapsd_stru;

    uc_uapsd_flag = pst_dmac_user->uc_uapsd_flag;
    if(((1==(pst_mac_header->st_frame_control.bit_power_mgmt))&&(0==(uc_uapsd_flag & MAC_USR_UAPSD_TRIG)))
        ||((0==(pst_mac_header->st_frame_control.bit_power_mgmt))&&(0!=(uc_uapsd_flag & MAC_USR_UAPSD_TRIG))))
    {
       //OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
       //               "dmac_uapsd_rx_trigger_check:state transfer,(uc_uapsd_flag & MAC_USR_UAPSD_TRIG)=%d",uc_uapsd_flag & MAC_USR_UAPSD_TRIG);

       DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_rx_trigger_state_trans);

       pst_dmac_user->uc_uapsd_flag &= ~MAC_USR_UAPSD_SP;
       if(pst_mac_header->st_frame_control.bit_power_mgmt)
       {
          /*从非节能态迁移到节能态*/
          oal_memset(&pst_uapsd_stru->us_uapsd_trigseq[0], 0xff, OAL_SIZEOF(pst_uapsd_stru->us_uapsd_trigseq));
          pst_dmac_user->uc_uapsd_flag |= MAC_USR_UAPSD_TRIG;
       }
       else
       {
         /*flush 节能队列*/
         ul_uapsd_qdepth = dmac_uapsd_flush_queue(pst_dmac_vap,pst_dmac_user);
         if((0 == ul_uapsd_qdepth)&& MAC_USR_UAPSD_USE_TIM(pst_dmac_user))
         {
            /* 调用PSM的TIM设置接口 */
            dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
         }
        /*从节能态迁移到非节能态*/
         pst_dmac_user->uc_uapsd_flag &= ~MAC_USR_UAPSD_TRIG;
       }
       return OAL_TRUE;
    }

    return OAL_FALSE;
}
/*****************************************************************************
 函 数 名  : dmac_uapsd_trigger_check
 功能描述  : 接收报文流程中检查是否trigger帧
 输入参数  : pst_dmac_vap:
             pst_dmac_usr:
             pst_net_buf: 待入队列的netbuf链,可能是多个MPDU
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_uapsd_rx_trigger_check (dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_netbuf_stru *pst_net_buf)
{
    mac_ieee80211_qos_frame_stru    *pst_mac_header;
    mac_rx_ctl_stru                 *pst_rx_ctrl;
    oal_uint8                       uc_uapsd_flag;
    oal_uint32                      ul_istrigger = OAL_FALSE;
    oal_uint8                       uc_tid;
    oal_uint8                       uc_ac = WLAN_WME_AC_BE;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_usr_uapsd_statis_stru      *pst_uapsd_statis;

    pst_uapsd_statis = pst_dmac_user->st_uapsd_stru.pst_uapsd_statis;
    if(OAL_PTR_NULL == pst_uapsd_statis)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_rx_trigger_check::pst_uapsd_statis null.}");
        return ;
    }
#endif

    uc_uapsd_flag = pst_dmac_user->uc_uapsd_flag;

    /*如果当前Usr不是uapsd使能的或者是处于一个Service Period中，返回*/
    if(!(uc_uapsd_flag & MAC_USR_UAPSD_EN)||
        (uc_uapsd_flag & MAC_USR_UAPSD_SP))
    {
        DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_rx_trigger_in_sp);
        return ;
    }

    pst_rx_ctrl = (mac_rx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    pst_mac_header = (mac_ieee80211_qos_frame_stru*)(mac_get_rx_cb_mac_hdr(pst_rx_ctrl));
    if(OAL_TRUE == dmac_uapsd_state_trans(pst_dmac_vap,pst_dmac_user,pst_mac_header))
    {
        return;
    }

    /* 检查是否是一个trigger帧:QOS DATA or Qos NULL DATA，非trigger帧也要继续处理是否需要状态切换 */
    if((WLAN_DATA_BASICTYPE == pst_mac_header->st_frame_control.bit_type)&&
        ((WLAN_QOS_DATA == pst_mac_header->st_frame_control.bit_sub_type)||
        (WLAN_QOS_NULL_FRAME == pst_mac_header->st_frame_control.bit_sub_type)))
    {
        ul_istrigger = OAL_TRUE;
        uc_tid = pst_mac_header->bit_qc_tid;
        uc_ac = WLAN_WME_TID_TO_AC(uc_tid);
    }

    if((OAL_TRUE == ul_istrigger) && (MAC_USR_UAPSD_AC_CAN_TIGGER(uc_ac,pst_dmac_user)))
    {
        dmac_uapsd_process_trigger(pst_dmac_vap,pst_dmac_user,uc_ac,pst_net_buf);
    }

    return ;

}
/*****************************************************************************
 函 数 名  : dmac_uapsd_process_trigger
 功能描述  : trigger帧的处理
 输入参数  : pst_dmac_vap:
             pst_dmac_usr:
             pst_net_buf: 待入队列的netbuf链,可能是多个MPDU
 输出参数  : 无
 返 回 值  : 成功或者失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_uapsd_process_trigger (dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 uc_ac,oal_netbuf_stru *pst_net_buf)
{

    mac_ieee80211_qos_frame_stru    *pst_mac_header;
    mac_rx_ctl_stru                 *pst_rx_ctrl;
    oal_int32                       al_uapsd_qdepth;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru                         *pst_mac_device         = OAL_PTR_NULL;
#endif

#ifdef _PRE_WLAN_DFT_STAT
    dmac_usr_uapsd_statis_stru      *pst_uapsd_statis;

    pst_uapsd_statis = pst_dmac_user->st_uapsd_stru.pst_uapsd_statis;
#endif

    pst_rx_ctrl = (mac_rx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    pst_mac_header = (mac_ieee80211_qos_frame_stru*)(mac_get_rx_cb_mac_hdr(pst_rx_ctrl));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /*TBD ALG未合入，下面的临时测试使用 zengjun add start*/
    pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_uapsd_tx_pkt:: mac_res_get_dev is null.}");
        dmac_tx_excp_free_netbuf(pst_net_buf);
        return;
    }
    if (OAL_FALSE == pst_dmac_user->st_user_base_info.en_is_multi_user)
    {
        dmac_tid_resume(pst_mac_device->pst_device_stru, &pst_dmac_user->ast_tx_tid_queue[uc_ac], DMAC_TID_PAUSE_RESUME_TYPE_PS);
    }
    dmac_psm_disable_user_to_psm_back(pst_mac_device, pst_dmac_user);
    /*TBD ALG未合入，下面的临时测试使用 zengjun add end*/
#endif
    if((OAL_TRUE == pst_mac_header->st_frame_control.bit_retry)&&
        (pst_mac_header->bit_seq_num == pst_dmac_user->st_uapsd_stru.us_uapsd_trigseq[uc_ac]))
    {
        //OAM_INFO_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR, "dmac_uapsd_process_trigger:sequnce duplicated");

        DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_rx_trigger_dup_seq);
        return ;
    }
    pst_dmac_user->st_uapsd_stru.us_uapsd_trigseq[uc_ac] = pst_mac_header->bit_seq_num;

    al_uapsd_qdepth = dmac_uapsd_process_queue(pst_dmac_vap,pst_dmac_user,uc_ac);
    /*在设置DMAC_USR_UAPSD_SP前，需判断是否有发送报文，-1表示没有报文发送，不应该置上DMAC_USR_UAPSD_SP*/
    if( DMAC_UAPSD_NOT_SEND_FRAME == al_uapsd_qdepth)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_process_trigger::DMAC_UAPSD_NOT_SEND_FRAME == al_uapsd_qdepth.}");
        return ;
    }

    pst_dmac_user->uc_uapsd_flag |= MAC_USR_UAPSD_SP;

    if((0 == al_uapsd_qdepth)&& MAC_USR_UAPSD_USE_TIM(pst_dmac_user))
     {
        /* 调用PSM的TIM设置接口 */
        OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
              "dmac_uapsd_process_trigger:set PVB to 0,usr id = %d",pst_dmac_user->st_user_base_info.us_assoc_id);

        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
     }
}


/*****************************************************************************
 函 数 名  : dmac_uapsd_process_queue
 功能描述  : U-APSD节能队列发包
 输入参数  : pst_dmac_vap
             pst_dmac_usr:
             uc_ac: trigger帧的AC
             uc_flush:是否是flush队列操作
 输出参数  : 无
 返 回 值  : -1:没有发送报文。其它:当前队列长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

OAL_STATIC oal_int32 dmac_uapsd_tx_pkt (oal_netbuf_stru *pst_net_buf, dmac_vap_stru* pst_dmac_vap, dmac_user_stru *pst_dmac_user,
                                                oal_uint8 uc_ac,oal_uint8 uc_sp_last,oal_uint8* pst_extra_qosnull)
{
    dmac_user_uapsd_stru *pst_dmac_uapsd;
    mac_tx_ctl_stru             *pst_tx_ctrl;
    mac_ieee80211_qos_frame_stru    *pst_mac_header;
    mac_ieee80211_frame_stru        *pst_frame_hdr;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_usr_uapsd_statis_stru  *pst_uapsd_statis;

    pst_uapsd_statis = pst_dmac_user->st_uapsd_stru.pst_uapsd_statis;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_uapsd_statis))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_uapsd_tx_pkt::uapsd_statis is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    pst_dmac_uapsd = &pst_dmac_user->st_uapsd_stru;

    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl) = OAL_TRUE;

    /*非flush操作，tid设置为uapsd专用tid，ac设置为trigger的AC*/
    mac_set_cb_tid(pst_tx_ctrl, WLAN_TIDNO_UAPSD);
    mac_set_cb_ac(pst_tx_ctrl, uc_ac);

    pst_mac_header =(mac_ieee80211_qos_frame_stru*)mac_get_cb_frame_hdr(pst_tx_ctrl);

    /*管理帧没有EOSP位，因此额外发送一个qos null结束USP*/
    if (WLAN_MANAGEMENT == pst_mac_header->st_frame_control.bit_type) {
        pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_ctrl);
        pst_frame_hdr->st_frame_control.bit_more_data = 0;
        *pst_extra_qosnull = OAL_TRUE;
    } else {
    /*
            每次发送时如果后面还有帧，则将EOSP置0，More Data置1。
            如果到max sp length，后面还有缓存帧，则将EOSP置1，More Data置1。
            如果后面没有帧发送，则将EOSP置1，More Data置0。
            当delivery-enable的AC队列中没有缓存帧，发送一个QoSNull帧，More Data置0。
    */
        if (OAL_FALSE == uc_sp_last) {
            pst_mac_header->st_frame_control.bit_more_data = 1;
            pst_mac_header->bit_qc_eosp = 0;
        } else if (1 == oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num)) {
            pst_mac_header->st_frame_control.bit_more_data = 0;
            pst_mac_header->bit_qc_eosp = 1;
        } else {
            pst_mac_header->st_frame_control.bit_more_data = 1;
            pst_mac_header->bit_qc_eosp = 1;
        }

    }

    oal_atomic_dec(&pst_dmac_uapsd->uc_mpdu_num);

    if(WLAN_DATA_BASICTYPE == pst_mac_header->st_frame_control.bit_type)
    {
        /*发送不成功，则终止本次USP*/
        if(OAL_SUCC != dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_net_buf))
        {
            OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_tx_pkt::dmac_tx_process_data failed.}");

            DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_process_queue_error);
            *pst_extra_qosnull = OAL_TRUE;

            dmac_tx_excp_free_netbuf(pst_net_buf);
            return OAL_FAIL;
        }
    }
    else
    {
        /*发送不成功，则终止本次USP*/
        if(OAL_SUCC != dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)))
        {
            oal_netbuf_free(pst_net_buf);
            OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_tx_pkt::dmac_tx_mgmt failed.}");

            DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_process_queue_error);
            *pst_extra_qosnull = OAL_TRUE;
            return OAL_FAIL;
        }
    }

    return  OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_uapsd_process_queue
 功能描述  : U-APSD节能队列发包
 输入参数  : pst_dmac_vap
             pst_dmac_usr:
             uc_ac: trigger帧的AC
             uc_flush:是否是flush队列操作
 输出参数  : 无
 返 回 值  : -1:没有发送报文。其它:当前队列长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

oal_int32 dmac_uapsd_process_queue (dmac_vap_stru* pst_dmac_vap, dmac_user_stru *pst_dmac_user,oal_uint8 uc_ac)
{
    dmac_user_uapsd_stru        *pst_dmac_uapsd;
    mac_user_uapsd_status_stru  *pst_mac_uapsd_status;
    oal_uint8                   uc_send_num;
    oal_uint8                   uc_loop;
    oal_netbuf_stru             *pst_net_buf;
    oal_uint8                   uc_extra_qosnull = OAL_FALSE;
    oal_uint8                   uc_sp_last = OAL_FALSE;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_usr_uapsd_statis_stru  *pst_uapsd_statis;
    pst_uapsd_statis = pst_dmac_user->st_uapsd_stru.pst_uapsd_statis;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_uapsd_statis))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_uapsd_process_queue::uapsd_statis is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    pst_dmac_uapsd = &pst_dmac_user->st_uapsd_stru;

    if(0 == oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num))
    {
         DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_send_qosnull);
         //OAM_INFO_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
         //         "dmac_uapsd_process_queue:queue is empty，send a qosnull");

         if(OAL_SUCC != dmac_uapsd_send_qosnull(pst_dmac_vap,pst_dmac_user,uc_ac))
         {
            return DMAC_UAPSD_NOT_SEND_FRAME;
         }
         else
         {
            return 0;
         }

    }

    pst_mac_uapsd_status = &pst_dmac_user->st_uapsd_status;

    uc_send_num = (pst_mac_uapsd_status->uc_max_sp_len < (oal_uint8)oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num))?
                   pst_mac_uapsd_status->uc_max_sp_len : (oal_uint8)oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num);

    for(uc_loop = 0;uc_loop < uc_send_num;uc_loop++)
    {
        oal_spin_lock(&pst_dmac_uapsd->st_lock_uapsd);
        pst_net_buf = dmac_tx_dequeue_first_mpdu(&(pst_dmac_uapsd->st_uapsd_queue_head));
        if(OAL_PTR_NULL == pst_net_buf)
        {
           oal_spin_unlock(&pst_dmac_uapsd->st_lock_uapsd);

           DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_process_queue_error);

           OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                          "{dmac_uapsd_process_queue::pst_net_buf null, uc_mpdu_num=%d.}",
                          oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num));
           return oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num);
        }

        DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_tx_dequeue_count);
        oal_spin_unlock(&pst_dmac_uapsd->st_lock_uapsd);

        if(uc_loop == uc_send_num-1)
        {
            uc_sp_last = OAL_TRUE;
        }

        if(OAL_SUCC!= dmac_uapsd_tx_pkt(pst_net_buf,pst_dmac_vap,pst_dmac_user,uc_ac,uc_sp_last,&uc_extra_qosnull))
        {
            OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                          "{dmac_uapsd_process_queue::dmac_uapsd_tx_pkt failed:us_assoc_id = %d.}",pst_dmac_user->st_user_base_info.us_assoc_id);
            break;
        }
    }

    if(OAL_TRUE == uc_extra_qosnull)
    {
        DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_send_extra_qosnull);
        //OAM_INFO_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
        //              "dmac_uapsd_process_queue:send a extra qosnull");
        dmac_uapsd_send_qosnull(pst_dmac_vap,pst_dmac_user,uc_ac);
    }

    return oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num);

}

/*****************************************************************************
 函 数 名  : dmac_uapsd_flush_queue
 功能描述  : U-APSD节能队列flush
 输入参数  : pst_dmac_vap
             pst_dmac_usr:

 输出参数  : 无
 返 回 值  : -1:没有发送报文。其它:当前队列长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

oal_int32 dmac_uapsd_flush_queue (dmac_vap_stru* pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    dmac_user_uapsd_stru        *pst_dmac_uapsd;
    oal_netbuf_stru             *pst_net_buf;
    mac_tx_ctl_stru             *pst_tx_ctrl;
    mac_ieee80211_frame_stru    *pst_frame_hdr;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_usr_uapsd_statis_stru  *pst_uapsd_statis;

    pst_uapsd_statis = pst_dmac_user->st_uapsd_stru.pst_uapsd_statis;
    if(OAL_PTR_NULL == pst_uapsd_statis )
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                       "{dmac_uapsd_flush_queue::pst_uapsd_statis null.}");
        return DMAC_UAPSD_NOT_SEND_FRAME;
    }
#endif

    pst_dmac_uapsd = &pst_dmac_user->st_uapsd_stru;

    while(0 != oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num))
    {
        oal_spin_lock(&pst_dmac_uapsd->st_lock_uapsd);
        pst_net_buf = dmac_tx_dequeue_first_mpdu(&(pst_dmac_uapsd->st_uapsd_queue_head));
        if(OAL_PTR_NULL == pst_net_buf)
        {
           oal_spin_unlock(&pst_dmac_uapsd->st_lock_uapsd);

           DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_flush_queue_error);

           OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                          "{dmac_uapsd_flush_queue::pst_net_buf null, uc_mpdu_num=%d.}",
                          oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num));
           return oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num);
        }

        DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_tx_dequeue_count);
        oal_spin_unlock(&pst_dmac_uapsd->st_lock_uapsd);

        pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
        MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl) = OAL_TRUE;

        /*flush流程，视为正常流程的继续，清掉more data bit*/
        if (1 == oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num))
        {
            pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_ctrl);
            pst_frame_hdr->st_frame_control.bit_more_data = 0;
        }

        oal_atomic_dec(&pst_dmac_uapsd->uc_mpdu_num);

        pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_ctrl);

        if(WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
            /*发送不成功，则终止本次USP*/
            if(OAL_SUCC != dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_net_buf))
            {
                OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                               "{dmac_uapsd_flush_queue::dmac_tx_process_data failed.}");

                DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_flush_queue_error);

                dmac_tx_excp_free_netbuf(pst_net_buf);
                continue;
            }
        }
        else
        {
            /*发送不成功，则终止本次USP*/
            if(OAL_SUCC != dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)))
            {
                OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                               "{dmac_uapsd_flush_queue::dmac_tx_mgmt failed.}");

                DMAC_UAPSD_STATS_INCR(pst_uapsd_statis->ul_uapsd_flush_queue_error);

                dmac_tx_excp_free_netbuf(pst_net_buf);
                continue;
            }
        }

    }

    return oal_atomic_read(&pst_dmac_uapsd->uc_mpdu_num);

}


/*****************************************************************************
 函 数 名  : dmac_uapsd_send_qosnull
 功能描述  : U-APSD qos null data发送
 输入参数  : pst_dmac_vap
             pst_dmac_usr:
             uc_ac: trigger帧的AC
 输出参数  : 无
 返 回 值  : OAL_SUCESS或者其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_uapsd_send_qosnull(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 uc_ac)
{
    oal_netbuf_stru                 *pst_net_buf;
    mac_tx_ctl_stru                 *pst_tx_ctrl;
    oal_uint32                       ul_ret;
    mac_ieee80211_qos_frame_stru    *pst_mac_header;

    /* 申请net_buff */
    pst_net_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_uapsd_send_qosnull::pst_net_buf failed.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_MEM_NETBUF_TRACE(pst_net_buf, OAL_TRUE);

    oal_set_netbuf_prev(pst_net_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

    /* 填写帧头,其中from ds为1，to ds为0，因此frame control的第二个字节为02 */
    OAL_MEMZERO(oal_netbuf_header(pst_net_buf), OAL_SIZEOF(mac_ieee80211_qos_frame_stru));
    mac_null_data_encap(oal_netbuf_header(pst_net_buf),
                        (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS_NULL) | 0x0200,
                        pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                        pst_dmac_vap->st_vap_base_info.auc_bssid);

    pst_mac_header = (mac_ieee80211_qos_frame_stru*)oal_netbuf_header(pst_net_buf);
    pst_mac_header->bit_qc_tid = WLAN_WME_AC_TO_TID(uc_ac);
    pst_mac_header->bit_qc_eosp = 1;
    /*协议规定单播的QOS NULL DATA只允许normal ack*/
    pst_mac_header->bit_qc_ack_polocy = WLAN_TX_NORMAL_ACK;

    /* 填写cb字段 */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    OAL_MEMZERO(pst_tx_ctrl, OAL_SIZEOF(mac_tx_ctl_stru));

    /* 填写tx部分 */
    mac_set_cb_ack_policy(pst_tx_ctrl, WLAN_TX_NORMAL_ACK);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctrl)       = FRW_EVENT_TYPE_WLAN_DTX;
    //MAC_GET_CB_EN_IS_BAR(pst_tx_ctrl)           = OAL_FALSE;
    //MAC_GET_CB_AC(pst_tx_ctrl)                  = uc_ac;
    mac_set_cb_is_bar(pst_tx_ctrl, OAL_FALSE);
    mac_set_cb_ac(pst_tx_ctrl, uc_ac);
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl)       = OAL_TRUE;
    MAC_GET_CB_RETRIED_NUM(pst_tx_ctrl)         = 0;
    //MAC_GET_CB_TID(pst_tx_ctrl)                 = WLAN_TIDNO_UAPSD;
    mac_set_cb_tid(pst_tx_ctrl, WLAN_TIDNO_UAPSD);
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctrl)        = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)         = pst_dmac_user->st_user_base_info.us_assoc_id;
    //MAC_GET_CB_EN_IS_QOSDATA(pst_tx_ctrl)       = OAL_TRUE;
    mac_set_cb_is_qosdata(pst_tx_ctrl, OAL_TRUE);
    /* 填写tx rx公共部分 */
    //MAC_GET_CB_FRAME_TYPE(pst_tx_ctrl)          = WLAN_DATA_NULL;
    MAC_GET_CB_IS_MCAST(pst_tx_ctrl)            = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_ctrl, OAL_FALSE);
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)   = OAL_TRUE;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctrl)       = OAL_FALSE;
    //MAC_GET_CB_EN_IS_USE_4_ADDR(pst_tx_ctrl)       = OAL_FALSE;
    mac_set_cb_is_use_4_addr(pst_tx_ctrl, OAL_FALSE);
    //MAC_GET_CB_FRAME_HEADER(pst_tx_ctrl)           = (mac_ieee80211_frame_stru *)oal_netbuf_data(pst_net_buf);
    mac_set_cb_frame_hdr(pst_tx_ctrl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)    = OAL_SIZEOF(mac_ieee80211_qos_frame_stru);
    MAC_GET_CB_MPDU_NUM(pst_tx_ctrl)               = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl)             = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctrl)               = 0;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)            = pst_dmac_user->st_user_base_info.us_assoc_id;

    ul_ret = dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_net_buf);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                       "{dmac_uapsd_send_qosnull::dmac_tx_process_data failed[%d].}", ul_ret);

        dmac_tx_excp_free_netbuf(pst_net_buf);

        if (OAL_LIKELY(OAL_PTR_NULL != pst_dmac_user->st_uapsd_stru.pst_uapsd_statis))
        {
            DMAC_UAPSD_STATS_INCR(pst_dmac_user->st_uapsd_stru.pst_uapsd_statis->ul_uapsd_send_qosnull_fail);
        }

        return ul_ret;
    }

    return ul_ret;

}

/*****************************************************************************
 函 数 名  : dmac_uapsd_tx_complete
 功能描述  : U-APSD 发送完成检查
 输入参数  : pst_dmac_vap
             pst_dmac_usr:
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月14日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_uapsd_tx_complete(dmac_user_stru *pst_dmac_user,mac_tx_ctl_stru *pst_cb)
{
    mac_ieee80211_qos_frame_stru    *pst_mac_header;

    if(!mac_get_cb_frame_hdr(pst_cb))
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_TX,
                       "{dmac_uapsd_tx_complete::pst_frame_header null.}");

        return;
    }

    pst_mac_header = (mac_ieee80211_qos_frame_stru*)(mac_get_cb_frame_hdr(pst_cb));
    if((WLAN_DATA_BASICTYPE == pst_mac_header->st_frame_control.bit_type)&&
        ((WLAN_QOS_DATA == pst_mac_header->st_frame_control.bit_sub_type)||
        (WLAN_QOS_NULL_FRAME== pst_mac_header->st_frame_control.bit_sub_type)))
        {
            if(1 == pst_mac_header->bit_qc_eosp)
            {
                pst_dmac_user->uc_uapsd_flag &= ~MAC_USR_UAPSD_SP;
            }
        }
}

/*****************************************************************************
 函 数 名  : dmac_config_set_uapsden
 功能描述  : 设置VAP U-APSD使能
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_set_uapsden(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8               uc_value;
    dmac_vap_stru           *pst_dmac_vap;
    dmac_user_stru          *pst_dmac_user;
    oal_dlist_head_stru     *pst_entry;
    mac_user_stru           *pst_user_tmp;
    oal_int32               al_uapsd_qdepth;

    uc_value = *puc_param;

    /* 设置mib值 */
    mac_vap_set_uapsd_en(pst_mac_vap, uc_value);
    g_uc_uapsd_cap = *puc_param;

    /*如果是非使能，清除每个User*/
    if(0 == uc_value)
    {
        if(WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user_tmp = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
                {
                    OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_config_set_uapsden::null pointer,pst_dmac_user[%d].}", pst_user_tmp->us_assoc_id);
                    continue;
                }

                al_uapsd_qdepth = dmac_uapsd_flush_queue(pst_dmac_vap, pst_dmac_user);
                if((0 == al_uapsd_qdepth)&& MAC_USR_UAPSD_USE_TIM(pst_dmac_user))
                {
                    /* 调用PSM的TIM设置接口 */
                    dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
                }
                else
                {
                    if(0 != al_uapsd_qdepth)
                    {
                        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_config_set_uapsden::al_uapsd_qdepth null.}");
                    }
                }
            }
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_set_uapsd_update
 功能描述  : VAP U-APSD UPDATE
 输入参数  : pst_mac_vap: 指向VAP的指针
             uc_len     : 参数长度
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月26日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint32 dmac_config_set_uapsd_update(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param) {
    oal_uint16                      us_user_id;
    oal_uint8                       uc_uapsd_flag;
    mac_user_uapsd_status_stru     *pst_uapsd_status;
    dmac_user_stru                 *pst_dmac_user;
    oal_uint8                       uc_len_tmp;

    us_user_id = *(oal_uint16 *)puc_param;
    uc_len_tmp = OAL_SIZEOF(us_user_id);
    uc_uapsd_flag = *(puc_param + uc_len_tmp);
    uc_len_tmp += OAL_SIZEOF(uc_uapsd_flag);
    pst_uapsd_status = (mac_user_uapsd_status_stru *)(puc_param + uc_len_tmp);

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user)) {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_set_uapsd_update::pst_dmac_user [%d] null.}", us_user_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(&pst_dmac_user->uc_uapsd_flag, &uc_uapsd_flag, OAL_SIZEOF(oal_uint8));
    oal_memcopy(&pst_dmac_user->st_uapsd_status, pst_uapsd_status, OAL_SIZEOF(mac_user_uapsd_status_stru));

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_config_uapsd_debug
 功能描述  : 调测命令
 输入参数  : pst_mac_vap: 指向VAP的指针
             puc_param  : 参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_uapsd_debug(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    /* uapsd维测信息，sh hipriv "vap0 uapsd_debug 0|1|2(单用户|all user|清空统计计数器) xx:xx:xx:xx:xx:xx(mac地址)" */
    mac_device_stru         *pst_device;
    oal_uint32               ul_off_set = 0;
    oal_int8                 ac_name[DMAC_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                auc_user_addr[WLAN_MAC_ADDR_LEN] = {0};
    oal_uint8                uc_debug_all = 0;
    dmac_user_stru          *pst_dmac_user;
    oal_dlist_head_stru            *pst_entry;
    mac_user_stru                  *pst_user_tmp;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    /* 设置配置命令参数 */
    if(OAL_PTR_NULL == pst_device)
    {
        return OAL_FAIL;
    }

    OAL_MEMZERO(ac_name, DMAC_HIPRIV_CMD_NAME_MAX_LEN);

    /* 所有用户还是单用户? */
    dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
    uc_debug_all = (oal_uint8)oal_atoi(ac_name);
    /* 偏移，取下一个参数 */
    puc_param = puc_param + ul_off_set;

    if(0 == uc_debug_all)
    {
        /* 获取用户地址 */
        dmac_get_cmd_one_arg((oal_int8*)puc_param, ac_name, &ul_off_set);
        oal_strtoaddr(ac_name, auc_user_addr);

        pst_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, auc_user_addr);
        if (OAL_PTR_NULL == pst_dmac_user)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_config_uapsd_debug::pst_dmac_user null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        dmac_uapsd_print_info(pst_dmac_user);
        return OAL_SUCC;
    }

    /* 遍历vap下所有用户 ,输出信息*/
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
    {
        pst_user_tmp = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
        if (OAL_PTR_NULL == pst_dmac_user)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_config_uapsd_debug::pst_dmac_user[%d] null.}", pst_user_tmp->us_assoc_id);
            continue;
        }
        if (1 == uc_debug_all)
        {
            dmac_uapsd_print_info(pst_dmac_user);
        }
        else
        {
            oal_memset(pst_dmac_user->st_uapsd_stru.pst_uapsd_statis, 0, OAL_SIZEOF(dmac_usr_uapsd_statis_stru));
        }
    }

    return OAL_SUCC;
}

OAL_STATIC oal_void  dmac_uapsd_print_info(dmac_user_stru *pst_dmac_user)
{
   dmac_user_uapsd_stru         *pst_uapsd_stru;
   dmac_usr_uapsd_statis_stru   *pst_uapsd_statis;
   mac_user_stru                *pst_mac_user;
   mac_user_uapsd_status_stru   *pst_uapsd_status;

   pst_mac_user     = &(pst_dmac_user->st_user_base_info);
   pst_uapsd_status = &(pst_dmac_user->st_uapsd_status);
   pst_uapsd_stru   = &(pst_dmac_user->st_uapsd_stru);
   pst_uapsd_statis =  pst_uapsd_stru->pst_uapsd_statis;

   /*基本信息*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
   OAM_WARNING_LOG_ALTER(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY,
                          "{dmac_uapsd_print_info:User assoc id = %d,macaddr = %02X:XX:XX:%02X:%02X:%02X\n}",
                          5, pst_mac_user->us_assoc_id,
                          pst_mac_user->auc_user_mac_addr[0],pst_mac_user->auc_user_mac_addr[3],
                          pst_mac_user->auc_user_mac_addr[4],pst_mac_user->auc_user_mac_addr[5]);
   OAM_WARNING_LOG_ALTER(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY,
                         "{dmac_uapsd_print_info:uc_uapsd_flag=%d,uc_qos_info=%d,max_sp_len=%d,ac_trigger_ena:BK=%d,BE=%d,Vi=%d,Vo=%d,"
                         "ac_delievy_ena: BK=%d,BE=%d,Vi=%d,Vo=%d\n}",
                         11,
                         pst_dmac_user->uc_uapsd_flag, pst_uapsd_status->uc_qos_info, pst_uapsd_status->uc_max_sp_len,
                         pst_uapsd_status->uc_ac_trigger_ena[WLAN_WME_AC_BK], pst_uapsd_status->uc_ac_trigger_ena[WLAN_WME_AC_BE],
                         pst_uapsd_status->uc_ac_trigger_ena[WLAN_WME_AC_VI], pst_uapsd_status->uc_ac_trigger_ena[WLAN_WME_AC_VO],
                         pst_uapsd_status->uc_ac_delievy_ena[WLAN_WME_AC_BK], pst_uapsd_status->uc_ac_delievy_ena[WLAN_WME_AC_BE],
                         pst_uapsd_status->uc_ac_delievy_ena[WLAN_WME_AC_VI], pst_uapsd_status->uc_ac_delievy_ena[WLAN_WME_AC_VO]);
   OAM_WARNING_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_uapsd_print_info:total mpdu in queue = %d,following is statistic...\n}",
                    oal_atomic_read(&pst_uapsd_stru->uc_mpdu_num));
#endif
      OAL_IO_PRINT("---------User assoc id = %d,macaddr = %02X:XX:XX:%02X:%02X:%02X---------------\n",
                               pst_mac_user->us_assoc_id,
                               pst_mac_user->auc_user_mac_addr[0],pst_mac_user->auc_user_mac_addr[3],
                               pst_mac_user->auc_user_mac_addr[4],pst_mac_user->auc_user_mac_addr[5]);
      OAL_IO_PRINT("uc_uapsd_flag = %d; uc_qos_info = %d; max_sp_len = %d\n",
                    pst_dmac_user->uc_uapsd_flag, pst_uapsd_status->uc_qos_info, pst_uapsd_status->uc_max_sp_len);

      OAL_IO_PRINT("ac_trigger_ena: BK=%d,BE=%d,Vi=%d,Vo=%d\n",
                                          pst_uapsd_status->uc_ac_trigger_ena[WLAN_WME_AC_BK],
                                          pst_uapsd_status->uc_ac_trigger_ena[WLAN_WME_AC_BE],
                                          pst_uapsd_status->uc_ac_trigger_ena[WLAN_WME_AC_VI],
                                          pst_uapsd_status->uc_ac_trigger_ena[WLAN_WME_AC_VO]);
      OAL_IO_PRINT("ac_delievy_ena: BK=%d,BE=%d,Vi=%d,Vo=%d\n",
                                          pst_uapsd_status->uc_ac_delievy_ena[WLAN_WME_AC_BK],
                                          pst_uapsd_status->uc_ac_delievy_ena[WLAN_WME_AC_BE],
                                          pst_uapsd_status->uc_ac_delievy_ena[WLAN_WME_AC_VI],
                                          pst_uapsd_status->uc_ac_delievy_ena[WLAN_WME_AC_VO]);
      OAL_IO_PRINT("total mpdu in queue = %d\n",oal_atomic_read(&pst_uapsd_stru->uc_mpdu_num));

      OAL_IO_PRINT("following is statistic................\n");
   /*统计计数器*/
   OAL_REFERENCE(pst_uapsd_statis);
   OAL_REFERENCE(pst_mac_user);
   OAL_REFERENCE(pst_uapsd_status);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
      OAM_WARNING_LOG_ALTER(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY,
                             "{dmac_uapsd_print_info:tx enqueue count=%d free_count=%d,rx trigger_in_sp=%d state_trans=%d dup_seq=%d,"
                             "send qosnull=%d extra_qosnull=%d,process_queue_error=%d,flush_queue_error = %d\n}",
                             9, pst_uapsd_statis->ul_uapsd_tx_enqueue_count,
                             pst_uapsd_statis->ul_uapsd_tx_enqueue_free_count, pst_uapsd_statis->ul_uapsd_rx_trigger_in_sp,
                             pst_uapsd_statis->ul_uapsd_rx_trigger_state_trans, pst_uapsd_statis->ul_uapsd_rx_trigger_dup_seq,
                             pst_uapsd_statis->ul_uapsd_send_qosnull, pst_uapsd_statis->ul_uapsd_send_extra_qosnull,
                             pst_uapsd_statis->ul_uapsd_process_queue_error, pst_uapsd_statis->ul_uapsd_flush_queue_error);
#endif
   OAL_IO_PRINT("tx_enqueue_count = %d\n",pst_uapsd_statis->ul_uapsd_tx_enqueue_count);             /*dmac_uapsd_tx_enqueue调用次数*/
   OAL_IO_PRINT("tx_enqueue_free_count = %d\n",pst_uapsd_statis->ul_uapsd_tx_enqueue_free_count);   /*入队过程中MPDU被释放的次数，一次可能释放多个MPDU*/
   OAL_IO_PRINT("rx_trigger_in_sp = %d\n",pst_uapsd_statis->ul_uapsd_rx_trigger_in_sp);             /*trigger检查发现处于SP中的次数*/
   OAL_IO_PRINT("rx_trigger_state_trans = %d\n",pst_uapsd_statis->ul_uapsd_rx_trigger_state_trans); /*trigger帧是重复帧的个数*/
   OAL_IO_PRINT("rx_trigger_dup_seq = %d\n",pst_uapsd_statis->ul_uapsd_rx_trigger_dup_seq);         /*dmac_uapsd_tx_enqueue调用次数*/
   OAL_IO_PRINT("send_qosnull = %d\n",pst_uapsd_statis->ul_uapsd_send_qosnull);                     /*队列为空，发送qos null data的个数*/
   OAL_IO_PRINT("send_extra_qosnull = %d\n",pst_uapsd_statis->ul_uapsd_send_extra_qosnull);         /*最后一个为管理帧，发送额外qosnull的个数*/
   OAL_IO_PRINT("process_queue_error = %d\n",pst_uapsd_statis->ul_uapsd_process_queue_error);       /*队列处理过程中出错的次数*/
   OAL_IO_PRINT("flush_queue_error = %d\n",pst_uapsd_statis->ul_uapsd_flush_queue_error);           /*flush队列处理过程中出错的次数*/
}
#endif /* _PRE_WLAN_FEATURE_UAPSD */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

