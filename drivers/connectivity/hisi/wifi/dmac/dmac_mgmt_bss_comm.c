/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_mgmt_bss_comm.c
  版 本 号   : 初稿
  作    者   : huxiaotong
  生成日期   : 2013年4月9日
  最近修改   :
  功能描述   : DMAC模块下，AP与STA公用的管理帧处理的源文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年4月9日
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
#include "oal_ext_if.h"
#include "oal_aes.h"
#include "wlan_spec.h"
#include "wlan_mib.h"

/* TBD，待整改 保留hal_ext_if.h*/
#include "frw_ext_if.h"

#include "hal_ext_if.h"
//#include "hal_spec.h"
#include "mac_regdomain.h"
#include "mac_ie.h"
#include "mac_frame.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_blockack.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_mgmt_sta.h"
#include "dmac_psm_ap.h"
#include "dmac_scan.h"

#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#include "pm_extern.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_BSS_COMM_C

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_int32 g_l_proxysta_feature;
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_ba_encap_blockack_req
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16  dmac_ba_encap_blockack_req(
                dmac_vap_stru     *pst_dmac_vap,
                oal_netbuf_stru   *pst_netbuf,
                dmac_ba_tx_stru   *pst_ba_tx_hdl,
                oal_uint8          uc_tid)
{
    oal_uint8    *puc_mac_hdr;
    oal_uint8    *puc_payload;
    oal_uint16    us_bar_ctl =0;

    if ((OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_netbuf) || (OAL_PTR_NULL == pst_ba_tx_hdl))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA,
                       "{dmac_ba_encap_blockack_req::param null, pst_dmac_vap=%d puc_data=%d pst_ba_tx_hdl=%d.}",
                       pst_dmac_vap, pst_netbuf, pst_ba_tx_hdl);
        return 0;
    }

    puc_mac_hdr = (oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    puc_payload = OAL_NETBUF_PAYLOAD(pst_netbuf);
#else
    puc_payload = puc_mac_hdr + MAC_80211_CTL_HEADER_LEN;
#endif

    /*************************************************************************/
    /*                     BlockAck Request Frame Format                     */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BAR Control|BlockAck Starting    |FCS|  */
    /* |             |        |  |  |           |Sequence number      |   |  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |2          |2                    |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_mac_hdr, (oal_uint16)WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_CTL | WLAN_FC0_SUBTYPE_BAR);

    /* Set DA to the address of the STA requesting authentication */
    oal_set_mac_addr(puc_mac_hdr + 4, pst_ba_tx_hdl->puc_dst_addr);

    /* Set SA to the dot11MacAddress */
    oal_set_mac_addr(puc_mac_hdr + 10, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /*************************************************************************/
    /*                Set the fields in the frame payload                     */
    /*************************************************************************/
    /* BAR Control field */
    us_bar_ctl = (oal_uint16)(uc_tid << 12);

    /* BAR-Ack Policy is set to Normal Ack */
    us_bar_ctl &= ~BIT0;

    /* Multi-TID set to 0 */
    us_bar_ctl |= BIT2;

    puc_payload[0] = us_bar_ctl & 0xFF;
    puc_payload[1] = (us_bar_ctl >> 8) & 0xFF;

    /* Sequence number */
    puc_payload[2] = (oal_uint8)(pst_ba_tx_hdl->us_baw_start<< 4);
    puc_payload[3] = (oal_uint8)((pst_ba_tx_hdl->us_baw_start >> 4) & 0xFF);

    return WLAN_MAX_BAR_DATA_LEN;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_tx_addba_req
 功能描述  : ADDBA_REQ函数，需要将HMAC模块的生成的信息同步到DMAC模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月10日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_tx_addba_req(
                mac_device_stru                *pst_device,
                dmac_vap_stru                  *pst_dmac_vap,
                dmac_ctx_action_event_stru     *pst_ctx_action_event,
                oal_netbuf_stru                *pst_net_buff)
{
    oal_uint8                   uc_tidno;
    dmac_user_stru             *pst_dmac_user;
    dmac_tid_stru              *pst_tid;
    oal_uint16                  us_frame_len;
    mac_tx_ctl_stru            *pst_tx_ctl;
    oal_uint32                  ul_ret;
    oal_uint8                  *puc_data;
    oal_uint8                   uc_ac;

    if ((OAL_PTR_NULL == pst_device) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_ctx_action_event) || (OAL_PTR_NULL == pst_net_buff))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA,
                       "{dmac_ba_encap_blockack_req::param null, pst_device=%d pst_dmac_vap=%d pst_ctx_action_event=%d.}",
                       pst_device, pst_dmac_vap, pst_ctx_action_event);

        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_tidno                = pst_ctx_action_event->uc_tidno;
    us_frame_len            = pst_ctx_action_event->us_frame_len;

    /* 获取对应用户及对应的TID队列 */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_ctx_action_event->us_user_idx);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_tx_addba_req::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    if (uc_tidno >= WLAN_TID_MAX_NUM)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_tx_addba_req::invalid uc_tidno[%d].}", uc_tidno);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_tid         = &(pst_dmac_user->ast_tx_tid_queue[uc_tidno]);

    /* 申请该TID下的对应的发送BA处理结构 */
    if(OAL_PTR_NULL != pst_tid->pst_ba_tx_hdl)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_tx_addba_req::re-malloc mem, memory leak!}");
        dmac_ba_reset_tx_handle(pst_device, &pst_tid->pst_ba_tx_hdl, uc_tidno);
    }
    pst_tid->pst_ba_tx_hdl = (dmac_ba_tx_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_HI_LOCAL, OAL_SIZEOF(dmac_ba_tx_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_tid->pst_ba_tx_hdl)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_tx_addba_req::pst_ba_tx_hdl null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(pst_tid->pst_ba_tx_hdl,  OAL_SIZEOF(dmac_ba_tx_stru));

    /* 同步HMAC与DMAC的BA会话的信息 */
    pst_tid->pst_ba_tx_hdl->en_is_ba          = OAL_TRUE;
    pst_tid->pst_ba_tx_hdl->en_ba_conn_status = DMAC_BA_INPROGRESS;
    pst_tid->pst_ba_tx_hdl->uc_dialog_token   = pst_ctx_action_event->uc_dialog_token;
    pst_tid->pst_ba_tx_hdl->uc_ba_policy      = pst_ctx_action_event->uc_ba_policy;
    pst_tid->pst_ba_tx_hdl->us_baw_size       = pst_ctx_action_event->us_baw_size;
    pst_tid->pst_ba_tx_hdl->us_ba_timeout     = pst_ctx_action_event->us_ba_timeout;
    pst_tid->pst_ba_tx_hdl->uc_tx_ba_lut      = oal_get_lut_index(pst_device->auc_tx_ba_index_table, DMAC_TX_BA_LUT_BMAP_LEN, HAL_MAX_AMPDU_LUT_SIZE);
    pst_tid->pst_ba_tx_hdl->us_mac_user_idx   = pst_dmac_user->st_user_base_info.us_assoc_id;

    if (pst_dmac_user->st_user_base_info.st_ht_hdl.en_ht_capable)
    {
        pst_tid->pst_ba_tx_hdl->en_back_var = MAC_BACK_COMPRESSED;
    }
    else
    {
        pst_tid->pst_ba_tx_hdl->en_back_var = MAC_BACK_BASIC;
    }

    dmac_ba_update_start_seq_num(pst_tid->pst_ba_tx_hdl, pst_dmac_user->aus_txseqs[uc_tidno]);
    OAL_MEM_NETBUF_TRACE(pst_net_buff, OAL_TRUE);

    puc_data = oal_netbuf_data(pst_net_buff);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    *(oal_uint16 *)&puc_data[7] = (oal_uint16)((oal_host_to_le16(pst_dmac_user->aus_txseqs[uc_tidno])) << WLAN_SEQ_SHIFT);
#else
    /* Hi1151设置ssn，1151管理帧帧头和帧体存放在一起.DTS2015052811315  */
    *(oal_uint16 *)&puc_data[MAC_80211_FRAME_LEN+7] = (oal_uint16)((oal_host_to_le16(pst_dmac_user->aus_txseqs[uc_tidno])) << WLAN_SEQ_SHIFT);
#endif
    /* 填写netbuf的cb字段，共发送管理帧和发送完成接口使用 */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_net_buff);
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)      = (oal_uint8)pst_dmac_user->st_user_base_info.us_assoc_id;
    MAC_GET_CB_MPDU_NUM(pst_tx_ctl)         = 1;              /* 管理帧只有一个 */
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)      = OAL_FALSE;
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buff));
    mac_set_cb_tid(pst_tx_ctl, uc_tidno);
    uc_ac = WLAN_WME_TID_TO_AC(uc_tidno);
    mac_set_cb_ac(pst_tx_ctl, uc_ac);
    mac_set_cb_is_need_pause_tid(pst_tx_ctl, OAL_TRUE);

    dmac_tid_pause(pst_tid, DMAC_TID_PAUSE_RESUME_TYPE_BA);

    /*本来应该发送之前将netbuff中的action info删掉，通过传入实际长度，硬件应该不会发送后面的部分*/
    /* TBD */

    /* 调用发送管理帧接口 */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buff, us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        dmac_ba_reset_tx_handle(pst_device, &pst_tid->pst_ba_tx_hdl, uc_tidno);
        oal_netbuf_free(pst_net_buff);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_tx_addba_rsp
 功能描述  : ADDBA_RSP函数，需要将HMAC模块的获取的信息同步到DMAC模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月14日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_tx_addba_rsp(
                mac_device_stru                *pst_device,
                dmac_vap_stru                  *pst_dmac_vap,
                dmac_ctx_action_event_stru     *pst_ctx_action_event,
                oal_netbuf_stru                *pst_net_buff)
{
    oal_uint8                   uc_tidno;
    dmac_user_stru             *pst_dmac_user = OAL_PTR_NULL;
    dmac_tid_stru              *pst_tid;
    oal_uint8                   uc_status;
    mac_tx_ctl_stru            *pst_tx_ctl;
    oal_uint32                  ul_ret;
    oal_uint8                   uc_lut_index;
    oal_uint16                  us_baw_size;

    if ((OAL_PTR_NULL == pst_device) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_ctx_action_event))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA, "{dmac_mgmt_tx_addba_rsp::send addba rsp failed, param null, pst_device=0x%X pst_dmac_vap=0x%X pst_ctx_action_event=0x%X.}",
          pst_device, pst_dmac_vap, pst_ctx_action_event);

        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_tidno            = pst_ctx_action_event->uc_tidno;     //用于设置Mac Ba lut表使用
    uc_status           = pst_ctx_action_event->uc_stauts;
    uc_lut_index        = pst_ctx_action_event->uc_lut_index; //用于设置Mac Ba lut表使用
    us_baw_size         = pst_ctx_action_event->us_baw_size;  //配置硬件窗口大小与bufsize一致，解决fir303b兼容性问题

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_ctx_action_event->us_user_idx);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_tx_addba_rsp::send addba rsp failed, pst_dmac_user null idx[%d], tid[%d].}",
          pst_ctx_action_event->us_user_idx, uc_tidno);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tidno]);

    /* 成功时，同步信息到DMAC模块，失败时，直接发送rsp帧，不同步到DMAC模块  */
    if (MAC_SUCCESSFUL_STATUSCODE == uc_status)
    {
        if(OAL_PTR_NULL != pst_tid->pst_ba_rx_hdl)
        {
            hal_remove_machw_ba_lut_entry(pst_device->pst_device_stru, pst_tid->pst_ba_rx_hdl->uc_lut_index);
            OAL_MEM_FREE(pst_tid->pst_ba_rx_hdl, OAL_TRUE);
            pst_tid->pst_ba_rx_hdl = OAL_PTR_NULL;
        }
        pst_tid->pst_ba_rx_hdl = (dmac_ba_rx_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_HI_LOCAL, (oal_uint16)OAL_SIZEOF(dmac_ba_rx_stru), OAL_TRUE);
        if (OAL_PTR_NULL == pst_tid->pst_ba_rx_hdl)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_mgmt_tx_addba_rsp::send addba rsp failed, pst_ba_rx_hdl mem alloc failed.}");

            /* 发送DELBA帧 */
            dmac_mgmt_delba(pst_dmac_vap,
                            pst_dmac_user,
                            uc_tidno,
                            MAC_RECIPIENT_DELBA,
                            MAC_UNSPEC_QOS_REASON);

            return OAL_ERR_CODE_PTR_NULL;
        }

        /* 使用之前初始化，后续赋值 */
        OAL_MEMZERO(pst_tid->pst_ba_rx_hdl, OAL_SIZEOF(dmac_ba_rx_stru));

        pst_tid->pst_ba_rx_hdl->en_ba_conn_status   = DMAC_BA_COMPLETE;  //save
        pst_tid->pst_ba_rx_hdl->en_back_var         = pst_ctx_action_event->en_back_var; //for send bar save
        pst_tid->pst_ba_rx_hdl->puc_transmit_addr   = pst_dmac_user->st_user_base_info.auc_user_mac_addr;
        pst_tid->pst_ba_rx_hdl->uc_lut_index        = uc_lut_index;
        pst_tid->pst_ba_rx_hdl->us_baw_start        = pst_ctx_action_event->us_baw_start;     //用于设置Mac Ba lut表使用
        pst_tid->pst_ba_rx_hdl->uc_ba_policy        = pst_ctx_action_event->uc_ba_policy;
        OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_mgmt_tx_addba_rsp::MAC ADDR [%02X:XX:XX:%02X:%02X:%02X].}",
                        pst_dmac_user->st_user_base_info.auc_user_mac_addr[0], pst_dmac_user->st_user_base_info.auc_user_mac_addr[3],
                        pst_dmac_user->st_user_base_info.auc_user_mac_addr[4], pst_dmac_user->st_user_base_info.auc_user_mac_addr[5]);
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        /* 根据MAC硬件的要求,Root AP发送过来的BA req,BA rsp需要填写Proxy STA的地址，*/
        /* 不然硬件无法识别BA会话是和哪个Proxy STA建立的 */
        if((OAL_TRUE == g_l_proxysta_feature)
           && (OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta)
           && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
        {
            /* 设置发送端硬件LUT table，这里填的是Proxy STA的地址而不是Root AP的 */
            hal_add_machw_ba_lut_entry(pst_device->pst_device_stru, uc_lut_index,
                                       pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                                       uc_tidno, pst_tid->pst_ba_rx_hdl->us_baw_start,
                                       (oal_uint8)us_baw_size);
        }
        else
#endif
        {
            /*如果不是Proxy STA，则设置对端(发送addba req)的地址 */
            /* 设置接收端硬件LUT table，需要HAL提供接口 */
            hal_add_machw_ba_lut_entry(pst_device->pst_device_stru, uc_lut_index,
                                       pst_tid->pst_ba_rx_hdl->puc_transmit_addr,
                                       uc_tidno, pst_tid->pst_ba_rx_hdl->us_baw_start,
                                       (oal_uint8)us_baw_size);
        }

        /* 初始化接收端超时定时器 ba会话建立不删除 */
        pst_dmac_vap->us_del_timeout = pst_ctx_action_event->us_ba_timeout / 10;

    }
    OAL_MEM_NETBUF_TRACE(pst_net_buff, OAL_TRUE);

    /* 填写netbuf的cb字段，共发送管理帧和发送完成接口使用 */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_net_buff);

    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)   = (oal_uint8)pst_dmac_user->st_user_base_info.us_assoc_id;
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)   = OAL_FALSE;
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buff));
    mac_set_cb_tid(pst_tx_ctl, uc_tidno);
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    /* 调用发送管理帧接口 */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buff, pst_ctx_action_event->us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_net_buff);
    }

    OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_mgmt_tx_addba_rsp::tid[%d], status[%d], uc_lut_index[%d], ul_ret[%d].}",
                     uc_tidno, uc_status, uc_lut_index, ul_ret);

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_tx_delba
 功能描述  : HMAC模块删除BA会话后，DMAC需要进行同步的处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月14日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_tx_delba(
                mac_device_stru                *pst_device,
                dmac_vap_stru                  *pst_dmac_vap,
                dmac_ctx_action_event_stru     *pst_ctx_action_event,
                oal_netbuf_stru                *pst_net_buff)
{
    dmac_user_stru             *pst_dmac_user;
    dmac_tid_stru              *pst_tid;
    mac_tx_ctl_stru            *pst_tx_ctl;
    oal_uint32                  ul_ret;

    if ((OAL_PTR_NULL == pst_device) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_ctx_action_event))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA,
                       "{dmac_mgmt_tx_delba::param null, pst_device=%d pst_dmac_vap=%d pst_ctx_action_event=%d.}",
                       pst_device, pst_dmac_vap, pst_ctx_action_event);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_ctx_action_event->us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_tx_delba::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tid  = &(pst_dmac_user->ast_tx_tid_queue[pst_ctx_action_event->uc_tidno]);

    /* 重置BA会话 */
    if (MAC_RECIPIENT_DELBA == pst_ctx_action_event->uc_initiator)
    {
        dmac_ba_reset_rx_handle(pst_device, &(pst_tid->pst_ba_rx_hdl), pst_ctx_action_event->uc_tidno, pst_dmac_user);
    }
    else
    {
        dmac_ba_reset_tx_handle(pst_device,  &(pst_tid->pst_ba_tx_hdl), pst_ctx_action_event->uc_tidno);
    }

    if (OAL_TRUE == pst_tid->en_is_delba_ing)
    {
        OAL_MEM_NETBUF_TRACE(pst_net_buff, OAL_TRUE);

        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_tx_delba::delba already sent.}\r\n");
        oal_netbuf_free(pst_net_buff);

        OAL_MEM_NETBUF_TRACE(pst_net_buff, OAL_TRUE);
        return OAL_SUCC;
    }
    else
    {
        pst_tid->en_is_delba_ing = OAL_TRUE;
    }

    /* 填写netbuf的cb字段，共发送管理帧和发送完成接口使用 */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_net_buff);
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)          =(oal_uint8)pst_dmac_user->st_user_base_info.us_assoc_id;
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)          = OAL_FALSE;
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buff));
    mac_set_cb_tid(pst_tx_ctl, pst_ctx_action_event->uc_tidno);
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    /* 调用发送管理帧接口 */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buff, pst_ctx_action_event->us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_net_buff);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_rx_succstatus_addba_rsp
 功能描述  : 从空口接收到addba_rsp帧状态正确的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月12日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_mgmt_rx_succstatus_addba_rsp(
                mac_device_stru                *pst_device,
                dmac_vap_stru                  *pst_dmac_vap,
                dmac_ctx_action_event_stru     *pst_crx_action_event,
                dmac_user_stru                 *pst_dmac_user,
                oal_bool_enum_uint8            *pen_send_delba)
{
    dmac_tid_stru              *pst_tid;
    oal_uint8                   uc_tidno;
    mac_priv_req_args_stru      st_ampdu_req_arg;
    oal_uint32                  ul_ret;

    uc_tidno      = pst_crx_action_event->uc_tidno;
    pst_tid       = &(pst_dmac_user->ast_tx_tid_queue[uc_tidno]);

    if((pst_tid->pst_ba_tx_hdl->uc_dialog_token == pst_crx_action_event->uc_dialog_token) && (pst_tid->pst_ba_tx_hdl->en_is_ba))
    {
        if (pst_tid->pst_ba_tx_hdl->uc_ba_policy == pst_crx_action_event->uc_ba_policy)
        {
            /* 设置BA窗口的TIMEOUT时间 */
            pst_tid->pst_ba_tx_hdl->us_ba_timeout = pst_crx_action_event->us_ba_timeout;

            /* 设置BA窗口的SIZE值 */
            if ((0 == pst_tid->pst_ba_tx_hdl->us_baw_size)
              || (pst_tid->pst_ba_tx_hdl->us_baw_size > pst_crx_action_event->us_baw_size))
            {
                pst_tid->pst_ba_tx_hdl->us_baw_size = pst_crx_action_event->us_baw_size;
            }

            /* 设置BA会话的对AMSDU的支持 */
            pst_tid->pst_ba_tx_hdl->en_amsdu_supp = pst_tid->pst_ba_tx_hdl->en_amsdu_supp & pst_crx_action_event->en_amsdu_supp;

            /* 设置BA会话下，聚合AMPDU的最大个数 */
            pst_tid->pst_ba_tx_hdl->uc_ampdu_max_num = pst_crx_action_event->uc_ampdu_max_num;

            /* 设置接收端地址 */
            pst_tid->pst_ba_tx_hdl->puc_dst_addr = pst_dmac_user->st_user_base_info.auc_user_mac_addr;

            /* 设置BA的会话状态 */
            pst_tid->pst_ba_tx_hdl->en_ba_conn_status = DMAC_BA_COMPLETE;

            /* 初始化发送babitmap队列 */
            OAL_MEMZERO(pst_tid->pst_ba_tx_hdl->aul_tx_buf_bitmap, DMAC_TX_BUF_BITMAP_WORDS * OAL_SIZEOF(oal_uint32));

            /*
                当前版本建立BA会话后，只能发送AMPDU帧，因此，需设置ampdu的相关信息
                设置AMPDU开始时，st_req_arg结构各个成员意义如下
            */
            st_ampdu_req_arg.uc_type  = MAC_A_MPDU_START;
            st_ampdu_req_arg.uc_arg1  = uc_tidno;                                       /* 该数据帧对应的TID号 */
            st_ampdu_req_arg.uc_arg2  = (oal_uint8)pst_crx_action_event->us_baw_size;   /* 用户的能力 */
            st_ampdu_req_arg.uc_arg3  = WLAN_TX_NORMAL_ACK;                             /* AMPDU帧的确认策略 */
            st_ampdu_req_arg.us_user_idx  = pst_dmac_user->st_user_base_info.us_assoc_id;  /* 需要开启AMPDU对应的用户 */

            OAM_INFO_LOG4(0, OAM_SF_BA, "{uc_dialog_token %d; us_ba_timeout %d; uc_ba_policy %d; us_baw_size %d .}",
                          pst_crx_action_event->uc_dialog_token, pst_tid->pst_ba_tx_hdl->us_ba_timeout,
                          pst_crx_action_event->uc_ba_policy, pst_tid->pst_ba_tx_hdl->us_baw_size);

            OAM_INFO_LOG2(0, OAM_SF_BA, "{en_amsdu_supp %d; uc_ampdu_max_num %d.}",
                          pst_tid->pst_ba_tx_hdl->en_amsdu_supp, pst_tid->pst_ba_tx_hdl->uc_ampdu_max_num);

            ul_ret = dmac_mgmt_rx_ampdu_start(pst_device, pst_dmac_vap, &st_ampdu_req_arg);
            if (ul_ret != OAL_SUCC)
            {
                OAM_WARNING_LOG1(0, OAM_SF_BA, "{dmac_mgmt_rx_succstatus_addba_rsp::ul_ret=%d}", ul_ret);
                *pen_send_delba = OAL_TRUE;
            }
            else /* 成功时，开启TID队列状态 */
            {
                dmac_tid_resume(pst_device->pst_device_stru, pst_tid, DMAC_TID_PAUSE_RESUME_TYPE_BA);
            }
        }
        else
        {
            OAM_WARNING_LOG0(0, OAM_SF_BA, "{dmac_mgmt_rx_succstatus_addba_rsp::policy not equal.}");
            *pen_send_delba = OAL_TRUE;
        }
    }
    else
    {
        OAM_WARNING_LOG0(0, OAM_SF_BA, "{dmac_mgmt_rx_succstatus_addba_rsp::token not equal.}");
        *pen_send_delba = OAL_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_rx_addba_rsp
 功能描述  : 从空口接收到相应帧的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_rx_addba_rsp(
                mac_device_stru                *pst_device,
                dmac_vap_stru                  *pst_dmac_vap,
                dmac_ctx_action_event_stru     *pst_crx_action_event)
{
    oal_bool_enum_uint8         en_send_delba = OAL_FALSE;
    dmac_user_stru             *pst_dmac_user;
    dmac_tid_stru              *pst_tid;
    oal_uint8                   uc_tidno;

    if ((OAL_PTR_NULL == pst_device) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_crx_action_event))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA,
                       "{dmac_mgmt_tx_delba::param null, pst_device=%d pst_dmac_vap=%d pst_crx_action_event=%d.}",
                       pst_device, pst_dmac_vap, pst_crx_action_event);

        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_tidno      = pst_crx_action_event->uc_tidno;
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_crx_action_event->us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_addba_rsp::pst_dmac_user null.user_idx:%d}",pst_crx_action_event->us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tid       = &(pst_dmac_user->ast_tx_tid_queue[uc_tidno]);

    if (OAL_PTR_NULL == pst_tid->pst_ba_tx_hdl)
    {
        OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_addba_rsp::pst_ba_tx_hdl null. tidno:%d}", uc_tidno);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_crx_action_event->uc_stauts == MAC_SUCCESSFUL_STATUSCODE)
    {
        //OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_addba_rsp::ADDBA succ.tidno:%d}", uc_tidno);
        dmac_mgmt_rx_succstatus_addba_rsp(pst_device, pst_dmac_vap, pst_crx_action_event, pst_dmac_user, &en_send_delba);
    }
    else
    {
        /* 只有当tokens匹配，才可以继续处理 */
        if((pst_tid->pst_ba_tx_hdl->uc_dialog_token == pst_crx_action_event->uc_dialog_token) && (pst_tid->pst_ba_tx_hdl->en_is_ba))
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_addba_rsp::ADDBA failed.}");

            /* 状态不成功，删除当前的BA会话的句柄 */
            dmac_ba_reset_tx_handle(pst_device, &(pst_tid->pst_ba_tx_hdl), uc_tidno);

            return OAL_SUCC;
        }
        else
        {
            OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_addba_rsp::token not equal %d %d.}\r\n",
                             pst_tid->pst_ba_tx_hdl->uc_dialog_token, pst_crx_action_event->uc_dialog_token);
            en_send_delba = OAL_TRUE;
        }
    }

    if (OAL_TRUE == en_send_delba)
    {
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_addba_rsp::unexpected ADDBA, send delba.}\r\n");
        dmac_mgmt_delba(pst_dmac_vap,
                        pst_dmac_user,
                        uc_tidno,
                        MAC_ORIGINATOR_DELBA,
                        MAC_UNSPEC_QOS_REASON);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_rx_delba
 功能描述  : 从空口接收到DELBA帧的处理(HMAC模块抛事件同步到DMAC调用该函数)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_rx_delba(
                mac_device_stru                *pst_device,
                dmac_vap_stru                  *pst_dmac_vap,
                dmac_ctx_action_event_stru     *pst_crx_action_event)
{
    dmac_user_stru     *pst_dmac_user;
    dmac_tid_stru      *pst_tid;
    oal_uint8           uc_tidno;
    oal_uint8           uc_initiator;

    if ((OAL_PTR_NULL == pst_device) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_crx_action_event))
    {
        OAM_ERROR_LOG3(0, OAM_SF_BA,
                       "{dmac_mgmt_rx_delba::param null, pst_device=%d pst_dmac_vap=%d pst_crx_action_event=%d.}",
                       pst_device, pst_dmac_vap, pst_crx_action_event);

        return OAL_ERR_CODE_PTR_NULL;
    }

    //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_delba::enter func.}\r\n");

    uc_tidno      = pst_crx_action_event->uc_tidno;
    uc_initiator  = pst_crx_action_event->uc_initiator;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_crx_action_event->us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_delba::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tid       = &(pst_dmac_user->ast_tx_tid_queue[uc_tidno]);

    //OAM_INFO_LOG1(0, OAM_SF_BA, "{dmac_mgmt_rx_delba::uc_initiator=%d.}\r\n", uc_initiator);

    if (MAC_RECIPIENT_DELBA == uc_initiator)
    {
        /* 重置BA TX的信息 */
        dmac_ba_reset_tx_handle(pst_device, &(pst_tid->pst_ba_tx_hdl), uc_tidno);
    }
    else
    {
        /* 重置BA RX的信息 */
        dmac_ba_reset_rx_handle(pst_device, &(pst_tid->pst_ba_rx_hdl), uc_tidno, pst_dmac_user);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_delba
 功能描述  : DMAC触发删除BA会话的接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月14日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_delba(
                dmac_vap_stru          *pst_dmac_vap,
                dmac_user_stru         *pst_dmac_user,
                oal_uint8               uc_tid,
                oal_uint8               uc_initiator,
                oal_uint8               uc_reason)
{
    frw_event_mem_stru             *pst_event_mem;      /* 申请事件返回的内存指针 */
    frw_event_stru                 *pst_hmac_to_dmac_ctx_event;
    dmac_ctx_action_event_stru     *pst_wlan_ctx_action;

    if ((OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_BA, "{dmac_mgmt_delba::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 抛事件到HMAC生成DELBA帧 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_action_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_delba::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获得事件指针 */
    pst_hmac_to_dmac_ctx_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_ctx_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_DELBA,
                       OAL_SIZEOF(dmac_ctx_action_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_dmac_vap->st_vap_base_info.uc_chip_id,
                       pst_dmac_vap->st_vap_base_info.uc_device_id,
                       pst_dmac_vap->st_vap_base_info.uc_vap_id);

    /*填写事件payload */
    pst_wlan_ctx_action = (dmac_ctx_action_event_stru *)(pst_hmac_to_dmac_ctx_event->auc_event_data);
    pst_wlan_ctx_action->en_action_category  = MAC_ACTION_CATEGORY_BA;
    pst_wlan_ctx_action->uc_action           = MAC_BA_ACTION_DELBA;
    pst_wlan_ctx_action->uc_tidno            = uc_tid;
    pst_wlan_ctx_action->uc_stauts           = uc_reason;
    pst_wlan_ctx_action->uc_initiator        = uc_initiator;
    oal_memcopy(pst_wlan_ctx_action->auc_mac_addr, pst_dmac_user->st_user_base_info.auc_user_mac_addr, WLAN_MAC_ADDR_LEN);

    /* 分发 */
    frw_event_dispatch_event(pst_event_mem);

    /* 释放事件内存 */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_rx_ampdu_start
 功能描述  : 设置开启ampdu需要的参数,自定义管理帧(A_MPDU_START)的操作函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月26日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_rx_ampdu_start(
                mac_device_stru                *pst_device,
                dmac_vap_stru                  *pst_dmac_vap,
                mac_priv_req_args_stru         *pst_crx_req_args)
{
    oal_uint8               uc_tidno;
    dmac_user_stru         *pst_dmac_user;
    dmac_tid_stru          *pst_dmac_tid;
    dmac_ht_handle_stru    *pst_ht_hdl;

    if ((OAL_PTR_NULL == pst_device) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_crx_req_args))
    {
        OAM_ERROR_LOG3(0, OAM_SF_AMPDU,
                       "{dmac_mgmt_rx_ampdu_start::param null, pst_device=%d pst_dmac_vap=%d pst_crx_req_args=%d.}",
                       pst_device, pst_dmac_vap, pst_crx_req_args);

        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_tidno        = pst_crx_req_args->uc_arg1;                    /* AMPDU_START时，uc_arg1代表对应的tid队列号 */
    pst_dmac_user   = (dmac_user_stru *)mac_res_get_dmac_user(pst_crx_req_args->us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{dmac_mgmt_rx_ampdu_start::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_tid    = &(pst_dmac_user->ast_tx_tid_queue[uc_tidno]);  /* 获取对应的TID队列 */
    pst_ht_hdl      = &(pst_dmac_tid->st_ht_tx_hdl);

    /* AMPDU_START时，uc_arg3代表对应的确认策略 */
    if (WLAN_TX_NORMAL_ACK == pst_crx_req_args->uc_arg3)
    {
        if ((OAL_PTR_NULL == pst_dmac_tid->pst_ba_tx_hdl) ||
           ((pst_dmac_tid->pst_ba_tx_hdl != OAL_PTR_NULL) && (DMAC_BA_COMPLETE != pst_dmac_tid->pst_ba_tx_hdl->en_ba_conn_status)))
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{dmac_mgmt_rx_ampdu_start::ba session is not comp.}");
            return OAL_FAIL;
        }
    }

    if (OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_rifs_tx_on)
    {
        pst_dmac_tid->en_tx_mode  = DMAC_TX_MODE_RIFS;
    }
    else
    {
        pst_dmac_tid->en_tx_mode  = DMAC_TX_MODE_AGGR;
    }

    /* 获取ht最大的ampdu聚合个数 */
    pst_dmac_tid->st_ht_tx_hdl.us_ampdu_max_size = (oal_uint16)(1 << (13 + pst_dmac_user->st_user_base_info.st_ht_hdl.uc_max_rx_ampdu_factor)) - 1;

    OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_ampdu_start::ampdu max size=%d, en_tx_mode=%d.}",
                  pst_dmac_tid->st_ht_tx_hdl.us_ampdu_max_size, pst_dmac_tid->en_tx_mode);

    if ((WLAN_VHT_MODE == pst_dmac_user->st_user_base_info.en_protocol_mode)
     || (WLAN_VHT_ONLY_MODE == pst_dmac_user->st_user_base_info.en_protocol_mode))
    {
        pst_dmac_tid->st_ht_tx_hdl.ul_ampdu_max_size_vht = (oal_uint32)(1 << (13 + pst_dmac_user->st_user_base_info.st_vht_hdl.bit_max_ampdu_len_exp)) - 1;

        OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_mgmt_rx_ampdu_start::ampdu max size=%d}",
                      pst_dmac_tid->st_ht_tx_hdl.us_ampdu_max_size);
    }


    dmac_nontxop_txba_num_updata(pst_dmac_user, uc_tidno, OAL_TRUE);

    pst_ht_hdl->uc_ampdu_max_num = pst_crx_req_args->uc_arg2;   /* AMPDU_START时，uc_arg2代表对端可接收的MPDU的最大值 */

    /* NORMAL ACK情况下，更新BA会话的信息 */
    if (WLAN_TX_NORMAL_ACK == pst_crx_req_args->uc_arg3)
    {
        if (WLAN_VAP_MODE_BSS_AP == dmac_vap_get_bss_type((mac_vap_stru *)pst_dmac_vap))
        {
            dmac_update_txba_session_params_ap(pst_dmac_tid, pst_ht_hdl->uc_ampdu_max_num);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_rx_ampdu_end
 功能描述  : 设置关闭ampdu需要的参数,自定义管理帧(A_MPDU_END)的操作函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_rx_ampdu_end(
                mac_device_stru                *pst_device,
                dmac_vap_stru                  *pst_dmac_vap,
                mac_priv_req_args_stru         *pst_crx_req_args)
{
    oal_uint8               uc_tidno;
    dmac_user_stru         *pst_dmac_user;

    if ((OAL_PTR_NULL == pst_device) || (OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_crx_req_args))
    {
        OAM_ERROR_LOG3(0, OAM_SF_AMPDU,
                       "{dmac_mgmt_rx_ampdu_end::param null, pst_device=%d pst_dmac_vap=%d pst_crx_req_args=%d.}",
                       pst_device, pst_dmac_vap, pst_crx_req_args);

        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_tidno        = pst_crx_req_args->uc_arg1;                    /* AMPDU_START时，uc_arg1代表对应的tid队列号 */
    pst_dmac_user   = (dmac_user_stru *)mac_res_get_dmac_user(pst_crx_req_args->us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AMPDU, "{dmac_mgmt_rx_ampdu_end::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
  /* 获取对应的TID队列 */
    pst_dmac_user->ast_tx_tid_queue[uc_tidno].en_tx_mode  = DMAC_TX_MODE_NORMAL;
    dmac_reset_tx_ampdu_session(pst_device->pst_device_stru, pst_dmac_user, uc_tidno);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_mgmt_switch_channel
 功能描述  : 切换信道
 输入参数  : pst_mac_device: 指向device的结构体
             pst_channel: 信道
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月17日
    作    者   : zhangheng
    修改内容   : 新生成函数

  2.日    期   : 2014年4月15日
    作    者   : zhangheng
    修改内容   : 切换信道只需关闭mac/phy, 不需要挂起发送

*****************************************************************************/
oal_uint32  dmac_mgmt_switch_channel(mac_device_stru *pst_mac_device, mac_channel_stru *pst_channel)
{
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint                 ul_irq_flag;

    OAM_PROFILING_CHSWITCH_STATISTIC(OAM_PROFILING_CHSWITCH_START);

    pst_hal_device = pst_mac_device->pst_device_stru;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#if (_PRE_WLAN_CHIP_ASIC != _PRE_WLAN_CHIP_VERSION)
    /* 判断 BT 是否开启*/
    if(1 == pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        oal_uint32 ul_mode_sel = 0;
        oal_uint32 ul_delay_cnt = 0;
        hal_set_btcoex_occupied_period(50000);    // 50ms
        /* 判断是否是mode sel */
        hal_get_btcoex_pa_status(&ul_mode_sel);
        while (BIT23 == (ul_mode_sel & BIT23))
        {
            oal_udelay(10);
            if(ul_delay_cnt++ > 1000)
            {
                OAM_ERROR_LOG1(0, OAM_SF_COEX, "{dmac_mgmt_switch_channel:ul_mode_sel = 0x%x!}",ul_mode_sel);
                break;
            }
            hal_get_btcoex_pa_status(&ul_mode_sel);
        }
        oal_udelay(50);     // 50us
    }
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
    dmac_pm_enable_front_end(pst_mac_device,OAL_TRUE);
#endif

    /* 关中断，挂起硬件发送需要关中断 */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DMSC);

    /* 关闭pa */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    /* 设置频段 */
    hal_set_freq_band(pst_hal_device, pst_channel->en_band);

#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
        /*dummy*/
#else
    if (pst_channel->en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_mgmt_switch_channel:: fpga is not support 80M.}\r\n");
        pst_channel->en_bandwidth = WLAN_BAND_WIDTH_20M;
    }
#endif

    /* 设置带宽 */
    hal_set_bandwidth_mode(pst_hal_device, pst_channel->en_bandwidth);

    /* 设置信道号 */
    hal_set_primary_channel(pst_hal_device, pst_channel->uc_chan_number, pst_channel->en_band, pst_channel->uc_idx, pst_channel->en_bandwidth);

    /* 使能pa */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    /* 开中断 */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);

#ifdef _PRE_WLAN_DFT_EVENT
    oam_event_chan_report(pst_channel->uc_chan_number);
#endif

    OAM_PROFILING_CHSWITCH_STATISTIC(OAM_PROFILING_CHSWITCH_END);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#if (_PRE_WLAN_CHIP_ASIC != _PRE_WLAN_CHIP_VERSION)
    hal_set_btcoex_occupied_period(0);    // 0us
#endif
#endif
    return OAL_SUCC;
}
/*lint -e19*/
oal_module_symbol(dmac_mgmt_switch_channel);
/*lint +e19*/

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_mgmt_encap_csa_action
 功能描述  : 封装channel switch announcement action 管理帧
 输入参数  : pst_dmac_vap: DMAC VAP
             puc_buffer: buffer起始地址
             uc_channel: 新的主信道号
             en_bw: 带宽模式
 输出参数  : 无
 返 回 值  : 封装后的帧长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月15日
    作    者   : sunxiaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_encap_csa_action(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_buffer, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw)
{
    oal_uint8        uc_mgmt_len = 0;
    oal_uint8        uc_len;
    oal_uint8       *puc_buffer;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/
    puc_buffer = oal_netbuf_header(pst_buffer);

    /* 帧控制字段全为0，除了type和subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* 设置分片序号为0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* 设置地址1，广播地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, BROADCAST_MACADDR);

    /* 设置地址2为自己的MAC地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /* 地址3，为VAP自己的MAC地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    uc_mgmt_len += MAC_80211_FRAME_LEN;

    /*************************************************************************/
    /*                Set the fields in the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                       Channel Switch Announcement Frame - Frame Body  */
    /* --------------------------------------------------------------------- */
    /* |Category |Action |Ch switch IE| 2nd Ch offset|Wide bw IE (11ac only) */
    /* --------------------------------------------------------------------- */
    /* |1        |1      | 5          |  3           |5                      */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    puc_buffer = oal_netbuf_data(pst_buffer);

    /* 设置Action的Category   */
    /* 0: Spectrum Management */
    puc_buffer[0] = 0;

    /* 设置Spectrum Management Action Field */
    /* 4: Channel Switch Announcement Frame */
    puc_buffer[1] = 4;

    puc_buffer += 2;

    uc_mgmt_len += 2;

    /* 开始封装信道切换所需的各种IE */

    /* 封装CSA IE */
    if (OAL_SUCC != mac_set_csa_ie(uc_channel, uc_csa_cnt, puc_buffer, &uc_len))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "dmac_mgmt_encap_csa_action: build csa ie failed!");
        return 0;
    }
    puc_buffer += uc_len;
    uc_mgmt_len += uc_len;

    /* 封装Second channel offset IE */
    if (OAL_SUCC != mac_set_second_channel_offset_ie(en_bw, puc_buffer, &uc_len))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_encap_csa_action::mac_set_second_channel_offset_ie failed}");

        return 0;
    }
    puc_buffer += uc_len;
    uc_mgmt_len += uc_len;

    if (OAL_TRUE != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented)
    {
        return (oal_uint32)uc_mgmt_len;
    }

    /* 11AC Wide Bandwidth Channel Switch IE */
    if (OAL_SUCC != mac_set_11ac_wideband_ie(uc_channel, en_bw, puc_buffer, &uc_len))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_encap_csa_action::mac_set_11ac_wideband_ie failed}");

        return 0;
    }
    puc_buffer += uc_len;
    uc_mgmt_len += uc_len;

    OAM_ERROR_LOG1(0, OAM_SF_DFS, "{dmac_mgmt_encap_csa_action::LEN = %d.}", uc_mgmt_len);

    return (oal_uint32)uc_mgmt_len;
}

#else
/*****************************************************************************
 函 数 名  : dmac_mgmt_encap_csa_action
 功能描述  : 封装channel switch announcement action 管理帧
 输入参数  : pst_dmac_vap: DMAC VAP
             puc_buffer: buffer起始地址
             uc_channel: 新的主信道号
             en_bw: 带宽模式
 输出参数  : 无
 返 回 值  : 封装后的帧长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_encap_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_buffer, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw)
{
    oal_uint8       *puc_origin = puc_buffer;
    oal_uint8        uc_len;
    oal_uint32       ul_ret;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/
    /* 帧控制字段全为0，除了type和subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* 设置分片序号为0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* 设置地址1，广播地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, BROADCAST_MACADDR);

    /* 设置地址2为自己的MAC地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /* 地址3，为VAP自己的MAC地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /*************************************************************************/
    /*                Set the fields in the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                       Channel Switch Announcement Frame - Frame Body  */
    /* --------------------------------------------------------------------- */
    /* |Category |Action |Ch switch IE| 2nd Ch offset|Wide bw IE (11ac only) */
    /* --------------------------------------------------------------------- */
    /* |1        |1      | 5          |  3           |5                      */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    puc_buffer += MAC_80211_FRAME_LEN;

    /* 设置Action的Category   */
    /* 0: Spectrum Management */
    puc_buffer[0] = 0;

    /* 设置Spectrum Management Action Field */
    /* 4: Channel Switch Announcement Frame */
    puc_buffer[1] = 4;

    puc_buffer += 2;

    /* 开始封装信道切换所需的各种IE */

    /* 封装CSA IE */
    ul_ret = mac_set_csa_ie(uc_channel, uc_csa_cnt, puc_buffer, &uc_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "dmac_mgmt_encap_csa_action: build csa ie failed!");
        return 0;
    }
    puc_buffer += uc_len;

    /* 封装Second channel offset IE */
    ul_ret = mac_set_second_channel_offset_ie(en_bw, puc_buffer, &uc_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_encap_csa_action::mac_set_second_channel_offset_ie failed[%d].}", ul_ret);

        return 0;
    }
    puc_buffer += uc_len;

    if (OAL_TRUE != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented)
    {
        return (oal_uint16)(puc_buffer - puc_origin);
    }

    /* 11AC Wide Bandwidth Channel Switch IE */
    ul_ret = mac_set_11ac_wideband_ie(uc_channel, en_bw, puc_buffer, &uc_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_encap_csa_action::mac_set_11ac_wideband_ie failed[%d].}", ul_ret);

        return 0;
    }
    puc_buffer += uc_len;

    return (oal_uint32)(puc_buffer - puc_origin);
}

#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 函 数 名  : dmac_mgmt_encap_ext_csa_action
 功能描述  : 封装extended channel switch announcement action 管理帧
 输入参数  : pst_dmac_vap  : DMAC VAP结构体指针
             puc_buffer    : 帧内存
             uc_opert_class:
             uc_channel    : 新信道号
             uc_csa_cnt    : 信道切换计数
             en_bw         : 带宽模式
 输出参数  : 无
 返 回 值  : 封装后的帧长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月28日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_encap_ext_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_buffer, oal_uint8 uc_opert_class, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw)
{
    oal_uint8       *puc_origin = puc_buffer;
    oal_uint8        uc_len;
    oal_uint32       ul_ret;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/
    /* 帧控制字段全为0，除了type和subtype */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* 设置分片序号为0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* 设置地址1，广播地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, BROADCAST_MACADDR);

    /* 设置地址2为自己的MAC地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /* 地址3，为VAP自己的MAC地址 */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);

    /*************************************************************************/
    /*                Set the fields in the frame body                       */
    /*************************************************************************/

    /****************************************************************************************************/
    /*                             Channel Switch Announcement Frame - Frame Body                       */
    /* ------------------------------------------------------------------------------------------------ */
    /* |Category |Action |Chan Swt Mode|New Opert Class|New Channel|Chan Swt Cnt|Wide bw IE (11ac only) */
    /* ------------------------------------------------------------------------------------------------ */
    /* |1        |1      |1            |1              |1          |1           |5                    | */
    /* ------------------------------------------------------------------------------------------------ */
    /*                                                                                                  */
    /****************************************************************************************************/
    puc_buffer += MAC_80211_FRAME_LEN;

    /* Category Field */
    puc_buffer[0] = MAC_ACTION_CATEGORY_PUBLIC;

    /* Action Field */
    puc_buffer[1] = MAC_PUB_EX_CH_SWITCH_ANNOUNCE;

    /* Channel Switch Mode */
    puc_buffer[2] = 1;

    /* New Operating Class */
    puc_buffer[3] = uc_opert_class;

    /* New Channel Number */
    puc_buffer[4] = uc_channel;

    /* Channel Switch Count */
    puc_buffer[5] = uc_csa_cnt;

    puc_buffer += 6;

    /* 开始封装信道切换所需的各种IE */
    if (OAL_TRUE != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented)
    {
        return (oal_uint16)(puc_buffer - puc_origin);
    }

    /* 11AC Wide Bandwidth Channel Switch IE */
    ul_ret = mac_set_11ac_wideband_ie(uc_channel, en_bw, puc_buffer, &uc_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_encap_ext_csa_action::mac_set_11ac_wideband_ie failed[%d].}", ul_ret);

        return 0;
    }
    puc_buffer += uc_len;

    return (oal_uint32)(puc_buffer - puc_origin);
}
#endif
/*****************************************************************************
 函 数 名  : dmac_mgmt_send_csa_action
 功能描述  : 发送信道切换广播管理帧
 输入参数  : pst_dmac_vap: DMAC VAP
             uc_channel   : 新的信道
             en_bw        : 新的带宽模式
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月14日
    作    者   : wangshanbo
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_send_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw)
{
    oal_netbuf_stru        *pst_mgmt_buf;
    oal_uint16              us_mgmt_len;
    mac_tx_ctl_stru        *pst_tx_ctl;
    oal_uint32              ul_ret;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_mgmt_send_csa_action::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_send_csa_action: prepare to send Channel Switch Announcement frame.");

    /* 至少应该是HT(11n)才能发送该帧 */
    if (OAL_TRUE != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_send_csa_action::vap not in HT mode.}");

        return OAL_FAIL;
    }

    /* 申请管理帧内存 */
    pst_mgmt_buf = OAL_MEM_NETBUF_ALLOC(OAL_MGMT_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_mgmt_buf)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_send_csa_action::pst_mgmt_buf null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_set_netbuf_prev(pst_mgmt_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_mgmt_buf,OAL_PTR_NULL);
    OAL_MEM_NETBUF_TRACE(pst_mgmt_buf, OAL_TRUE);

    /* 封装 Channel Switch Announcement 帧 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    us_mgmt_len = (oal_uint16)dmac_mgmt_encap_csa_action(pst_dmac_vap, pst_mgmt_buf, uc_channel, uc_csa_cnt, en_bw);
#else
    us_mgmt_len = (oal_uint16)dmac_mgmt_encap_csa_action(pst_dmac_vap, oal_netbuf_header(pst_mgmt_buf), uc_channel, uc_csa_cnt, en_bw);
#endif
    if (0 == us_mgmt_len)
    {
        oal_netbuf_free(pst_mgmt_buf);
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_send_csa_action::encap csa action failed.}");
        return OAL_FAIL;
    }

    /* 填写netbuf的cb字段，供发送管理帧和发送完成接口使用 */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_buf);

    OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)  =(oal_uint8)pst_dmac_vap->st_vap_base_info.us_multi_user_idx; /* channel switch帧是广播帧 */
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)  = OAL_TRUE;
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    /* 调用发送管理帧接口 */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_mgmt_buf, us_mgmt_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_mgmt_buf);
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_send_csa_action::tx csa action failed.}");
        return ul_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_mgmt_scan_vap_down
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月8日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_mgmt_scan_vap_down(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_scan_vap_down::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 如果AP在扫描状态，则需要删除定时器 */
    if (MAC_VAP_STATE_AP_WAIT_START == pst_mac_vap->en_vap_state)
    {
        if (OAL_TRUE == pst_mac_device->st_scan_timer.en_is_registerd)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_mac_device->st_scan_timer);
        }
    }

    /* vap down的时候如果设备处于扫描状态，并且down掉的vap和扫描的vap是同一个，则停止扫描 */
    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state) &&
        (pst_mac_vap->uc_vap_id == pst_mac_device->st_scan_params.uc_vap_id))
    {
        /* 删除扫描定时器 */
        if (OAL_TRUE == pst_mac_device->st_scan_timer.en_is_registerd)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_mac_device->st_scan_timer);
        }

        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{dmac_mgmt_scan_vap_down::stop scan.}");
        dmac_scan_end(pst_mac_device);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_set_cap_info_field
 功能描述  : hmac组帧设置cap info field
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
oal_void  dmac_set_cap_info_field(oal_void *pst_vap, oal_uint8 *puc_buffer)
{
#ifdef   _PRE_WLAN_FEATURE_P2P
    mac_cap_info_stru  *pst_cap_info = (mac_cap_info_stru *)puc_buffer;
    mac_vap_stru       *pst_mac_vap  = (mac_vap_stru *)pst_vap;
#endif

    mac_set_cap_info_ap(pst_vap, puc_buffer);

#ifdef   _PRE_WLAN_FEATURE_P2P
    /* DTS2015022500399 解决P2P模式下Listen 状态下发送的帧的capability info ess bit不为0的问题 */
    if (dmac_vap_is_in_p2p_listen(pst_mac_vap))
    {
        pst_cap_info->bit_ess = 0;
    }
#endif
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
