/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_tx_bss_comm.c
  版 本 号   : 初稿
  作    者   : mayuan
  生成日期   : 2012年11月15日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月15日
    作    者   : mayuan
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
#include "oal_util.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"

#include "hal_ext_if.h"
/*TBD，待去除本文件*/
#include "hal_witp_mac.h"


#include "mac_frame.h"
#include "mac_data.h"

#include "dmac_ext_if.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_blockack.h"
#include "dmac_tx_complete.h"
#include "dmac_psm_ap.h"
#include "dmac_uapsd.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_11w.h"
#include "dmac_11i.h"
#include "dmac_dft.h"

#ifdef _PRE_WLAN_FEATURE_DBAC
#include "mac_device.h"
#include "dmac_device.h"
#endif

#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_dbac.h"
#endif

#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#include "dmac_lpm_test.h"
#include "dmac_test_sch.h"
#include "dmac_config.h"
#endif

#ifdef _PRE_WIFI_DMT
#include "hal_witp_dmt_if.h"
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#include "pm_extern.h"
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#include "oal_profiling.h"
#include "dmac_config.h"

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern oal_int32 g_l_proxysta_feature;
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TX_BSS_COMM_C

/*****************************************************************************
  2 函数原型声明
*****************************************************************************/
//OAL_STATIC oal_uint32  dmac_tx_process_data_excp(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
OAL_STATIC oal_uint32  dmac_tx_update_protection_txop_alg(dmac_vap_stru *pst_dmac_vap, hal_tx_txop_alg_stru *pst_txop_alg, oal_uint8 uc_do_default_cfg, oal_bool_enum_uint8 en_mcast);
extern oal_bool_enum_uint8 mac_is_p2p_action_frame(oal_uint8 *puc_data);

/*****************************************************************************
  3 全局变量定义
*****************************************************************************/
typedef oal_uint32 (*p_dmac_tx_process_data_func)(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
/* 默认的MAC协议到PHY协议的映射关系 */
oal_uint8 g_auc_default_mac_to_phy_protocol_mapping[WLAN_PROTOCOL_BUTT] =
{
    WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE,     /* WLAN_LEGACY_11A_MODE            = 0 */
    WLAN_11B_PHY_PROTOCOL_MODE,             /* WLAN_LEGACY_11B_MODE            = 1 */
    WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE,     /* WLAN_LEGACY_11G_MODE            = 2 */
    WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE,     /* WLAN_MIXED_ONE_11G_MODE         = 3 */
    WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE,     /* WLAN_MIXED_TWO_11G_MODE         = 4 */
    WLAN_HT_PHY_PROTOCOL_MODE,              /* WLAN_HT_MODE                    = 5 */
    WLAN_VHT_PHY_PROTOCOL_MODE,             /* WLAN_VHT_MODE                   = 6 */
    WLAN_HT_PHY_PROTOCOL_MODE,              /* WLAN_HT_ONLY_MODE               = 7 */
    WLAN_VHT_PHY_PROTOCOL_MODE,             /* WLAN_VHT_ONLY_MODE              = 8 */
    WLAN_HT_PHY_PROTOCOL_MODE,              /* WLAN_HT_11G_MODE                = 9 */
};
#endif

/*****************************************************************************
  4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : dmac_tx_dump_get_switch
 功能描述  : 获取管理帧或者数据帧的打印开关
 输入参数  : en_frame_type     :帧是管理帧还是数据帧
             pen_frame_switch  :帧内容开关
             pen_cb_switch     :帧CB字段开关
             pen_dscr_switch   :帧的发送描述符开关
             pst_tx_cb         :skb的发送控制字段
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月22日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_dump_get_switch(
                                    oam_user_track_frame_type_enum_uint8     en_frame_type,
                                    oal_uint8                               *pen_frame_switch,
                                    oal_uint8                               *pen_cb_switch,
                                    oal_uint8                               *pen_dscr_switch,
                                    mac_tx_ctl_stru                         *pst_tx_cb)
{
    oal_uint32                   ul_ret;
    mac_ieee80211_frame_stru    *pst_frame_hdr;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pen_frame_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pen_cb_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pen_dscr_switch)
        || OAL_UNLIKELY(OAL_PTR_NULL == pst_tx_cb))
    {
        OAM_ERROR_LOG4(0, OAM_SF_TX,
                        "{dmac_tx_dump_get_switch::param null, pen_frame_switch=%d pen_cb_switch=%d pen_dscr_switch=%d pst_tx_cb=%d.}",
                        pen_frame_switch, pen_cb_switch, pen_dscr_switch, pst_tx_cb);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 判断是否是probe request或者probe response，先获取一下开关 */
    pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_cb);
    if (OAL_PTR_NULL == pst_frame_hdr)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_dump_get_switch::pst_frame_hdr null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_MANAGEMENT == pst_frame_hdr->st_frame_control.bit_type)
    {
        if(WLAN_PROBE_REQ == pst_frame_hdr->st_frame_control.bit_sub_type
        || WLAN_PROBE_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            ul_ret = oam_report_80211_probe_get_switch(OAM_OTA_FRAME_DIRECTION_TYPE_TX,
                                                       pen_frame_switch,
                                                       pen_cb_switch,
                                                       pen_dscr_switch);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dump_get_switch::oam_report_80211_probe_get_switch failed[%d].}", ul_ret);
                return ul_ret;
            }

            return OAL_SUCC;
        }
        else if(WLAN_ACTION == pst_frame_hdr->st_frame_control.bit_sub_type
                || WLAN_ACTION_NO_ACK == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
                *pen_cb_switch    = 1;
                *pen_dscr_switch  = 1;
                *pen_frame_switch = 1;
                return OAL_SUCC;
        }
    }
    /* 获取非probe request和probe response的开关 */
    if (OAL_TRUE == MAC_GET_CB_IS_MCAST(pst_tx_cb))
    {
        ul_ret = oam_report_80211_mcast_get_switch(OAM_OTA_FRAME_DIRECTION_TYPE_TX,
                                                   en_frame_type,
                                                   pen_frame_switch,
                                                   pen_cb_switch,
                                                   pen_dscr_switch);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(0, OAM_SF_TX,
                             "{dmac_tx_dump_get_switch::dmac_tx_dump_get_switch failed! ul_ret=[%d],frame_type=[%d]}",
                             ul_ret, en_frame_type);
            return ul_ret;
        }
    }
    else
    {
        /* 如果是0xffff，说明没有此用户 */
        if (MAX_TX_USER_IDX == MAC_GET_CB_TX_USER_IDX(pst_tx_cb))
        {
            if (WLAN_MANAGEMENT == pst_frame_hdr->st_frame_control.bit_type
                && (WLAN_DISASOC == pst_frame_hdr->st_frame_control.bit_sub_type
                || WLAN_DEAUTH == pst_frame_hdr->st_frame_control.bit_sub_type))
            {
                *pen_cb_switch    = 1;
                *pen_dscr_switch  = 1;
                *pen_frame_switch = 1;
            }
            else
            {
                *pen_cb_switch    = 0;
                *pen_dscr_switch  = 0;
                *pen_frame_switch = 0;
            }

            return OAL_FAIL;
        }

        /* 获取非probe response 的开关 */
        ul_ret = oam_report_80211_ucast_get_switch(OAM_OTA_FRAME_DIRECTION_TYPE_TX,
                                                   en_frame_type,
                                                   pen_frame_switch,
                                                   pen_cb_switch,
                                                   pen_dscr_switch,
                                                   MAC_GET_CB_TX_USER_IDX(pst_tx_cb));
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG3(0, OAM_SF_TX,
                             "{dmac_tx_dump_get_switch::oam_report_80211_ucast_get_switch failed! ul_ret=[%d],frame_type=[%d], user_idx=[%d]}",
                             ul_ret, en_frame_type, MAC_GET_CB_TX_USER_IDX(pst_tx_cb));
            OAM_WARNING_LOG3(0, OAM_SF_TX, "{dmac_tx_dump_get_switch::frame_switch=[%d], cb_switch=[%d], dscr_switch=[%d]",
                             pen_frame_switch, pen_cb_switch, pen_dscr_switch);
            return ul_ret;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_get_user_macaddr
 功能描述  : 获取目的用户的mac地址，用于SDT过滤
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月21日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_tx_get_user_macaddr(mac_tx_ctl_stru *pst_tx_cb,
                                                        oal_uint8 auc_user_macaddr[])
{
    mac_user_stru      *pst_mac_user;

    if (OAL_TRUE == MAC_GET_CB_IS_MCAST(pst_tx_cb))
    {
        oal_set_mac_addr(auc_user_macaddr, BROADCAST_MACADDR);
    }
    else
    {
        pst_mac_user = mac_res_get_mac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_cb));
        if (OAL_PTR_NULL == pst_mac_user)
        {
            OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_tx_get_user_macaddr::pst_mac_user[%d] null.", MAC_GET_CB_TX_USER_IDX(pst_tx_cb));

            return OAL_ERR_CODE_PTR_NULL;
        }
        oal_set_mac_addr(auc_user_macaddr, pst_mac_user->auc_user_mac_addr);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_dump_get_user_macaddr
 功能描述  : 发送流程打印帧获取用户mac地址，用于sdt过滤
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月28日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_dump_get_user_macaddr(mac_tx_ctl_stru *pst_tx_cb,
                                                     oal_uint8 auc_user_macaddr[])
{
    mac_ieee80211_frame_stru    *pst_frame_hdr;
    oal_uint8                    uc_tx_user_idx;

    pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_cb);
    if (OAL_PTR_NULL == pst_frame_hdr)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_dump_get_user_macaddr::pst_frame_hdr null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 判断是否是probe request或者probe response，GO Neg, GAS 不用去找用户，因为找不到 */
    uc_tx_user_idx  =  (oal_uint8)MAC_GET_CB_TX_USER_IDX(pst_tx_cb);
    if (WLAN_MANAGEMENT == pst_frame_hdr->st_frame_control.bit_type
        && ((WLAN_PROBE_REQ == pst_frame_hdr->st_frame_control.bit_sub_type)
        || (WLAN_PROBE_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
        || ((WLAN_ACTION == pst_frame_hdr->st_frame_control.bit_sub_type) && (uc_tx_user_idx == (oal_uint8)MAX_TX_USER_IDX))))
    {
        oal_set_mac_addr(auc_user_macaddr, BROADCAST_MACADDR);
        return OAL_SUCC;
    }

    return dmac_tx_get_user_macaddr(pst_tx_cb, auc_user_macaddr);
}


/*****************************************************************************
 函 数 名  : dmac_tx_dump
 功能描述  : tx流程打印帧，帧cb字段，发送描述符
 输入参数  : pst_tx_dump_param:tx流程打印参数结构
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月28日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_tx_dump(dmac_tx_dump_param_stru *pst_tx_dump_param)
{
    oal_uint32               ul_dscr_one_size = 0;
    oal_uint32               ul_dscr_two_size = 0;
    oal_uint32               ul_ret;

    /* 上报帧内容 */
    if (OAL_SWITCH_ON == pst_tx_dump_param->en_frame_switch)
    {
       ul_ret =  oam_report_80211_frame(pst_tx_dump_param->auc_user_macaddr,
                               pst_tx_dump_param->puc_mac_hdr_addr,
                               pst_tx_dump_param->uc_mac_hdr_len,
                               pst_tx_dump_param->puc_mac_payload_addr,
                               pst_tx_dump_param->us_mac_frame_len,
                               OAM_OTA_FRAME_DIRECTION_TYPE_TX);
       if (OAL_SUCC != ul_ret)
       {
           OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dump::oam_report_80211_frame return err: 0x%x.}\r\n", ul_ret);
       }
    }

    /* 上报帧对应的发送描述符 */
    if (OAL_SWITCH_ON == pst_tx_dump_param->en_dscr_switch)
    {
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        hal_tx_get_size_dscr(pst_tx_dump_param->pst_hal_device,
                             pst_tx_dump_param->pst_tx_cb->bit_netbuf_num,
                             &ul_dscr_one_size,
                             &ul_dscr_two_size);
#else
        hal_tx_get_size_dscr(pst_tx_dump_param->pst_hal_device,
                             pst_tx_dump_param->pst_tx_cb->uc_netbuf_num,
                             &ul_dscr_one_size,
                             &ul_dscr_two_size);
#endif
        ul_ret = oam_report_dscr(pst_tx_dump_param->auc_user_macaddr,
                        (oal_uint8 *)pst_tx_dump_param->pst_tx_dscr,
                        (oal_uint16)(ul_dscr_one_size + ul_dscr_two_size),
                        OAM_OTA_TYPE_TX_DSCR);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dump::oam_report_dscr return err: 0x%x.}\r\n", ul_ret);
        }
    }

    /* 上报帧对应的CB */
    if (OAL_SWITCH_ON == pst_tx_dump_param->en_cb_switch)
    {
        ul_ret = oam_report_netbuf_cb(pst_tx_dump_param->auc_user_macaddr,
                             OAL_NETBUF_CB(pst_tx_dump_param->pst_netbuf),
                             OAM_OTA_TYPE_TX_CB);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dump::oam_report_netbuf_cb return err: 0x%x.}\r\n", ul_ret);
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_tx_dump_data
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_tx_dump_data(
                            hal_to_dmac_device_stru     *pst_hal_device,
                            mac_tx_ctl_stru             *pst_tx_ctl,
                            oal_dlist_head_stru         *pst_tx_dscr_list_hdr)
{
    oal_netbuf_stru         *pst_netbuf = OAL_PTR_NULL;
    hal_tx_dscr_stru        *pst_dscr   = OAL_PTR_NULL;
    oal_dlist_head_stru     *pst_dlist_node;
    oal_switch_enum_uint8    en_frame_switch = 0;
    oal_switch_enum_uint8    en_cb_switch = 0;
    oal_switch_enum_uint8    en_dscr_switch = 0;
    oal_uint32               ul_ret = 0;
    oal_uint8                auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0};
    dmac_tx_dump_param_stru  st_tx_dump_param;

    pst_dlist_node = pst_tx_dscr_list_hdr->pst_next;
    while (pst_dlist_node != pst_tx_dscr_list_hdr)
    {
        pst_dscr = OAL_DLIST_GET_ENTRY(pst_dlist_node, hal_tx_dscr_stru, st_entry);
        pst_netbuf = pst_dscr->pst_skb_start_addr;

        if(OAL_PTR_NULL != pst_netbuf)
        {
            pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

            /* 获取打印开关 */
            ul_ret = dmac_tx_dump_get_switch(OAM_USER_TRACK_FRAME_TYPE_DATA,
                                             &en_frame_switch,
                                             &en_cb_switch,
                                             &en_dscr_switch,
                                             pst_tx_ctl);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dump_data::dmac_tx_dump_get_switch failed[%d].}", ul_ret);
                pst_dlist_node = pst_dlist_node->pst_next;
                continue;
            }

            /* 获取用户mac地址，用于SDT过滤 */
            ul_ret = dmac_tx_dump_get_user_macaddr(pst_tx_ctl, auc_user_macaddr);
            if (OAL_SUCC != ul_ret)
            {
                OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_tx_dump_get_switch::dmac_tx_dump_get_switch failed[%d].}", ul_ret);

                pst_dlist_node = pst_dlist_node->pst_next;
                continue;
            }

            /* 填写打印参数 */
            st_tx_dump_param.pst_hal_device       = pst_hal_device;
            st_tx_dump_param.pst_netbuf           = pst_netbuf;
            st_tx_dump_param.pst_tx_cb            = pst_tx_ctl;
            st_tx_dump_param.pst_tx_dscr          = pst_dscr;

            st_tx_dump_param.puc_mac_hdr_addr     = (oal_uint8 *)(mac_get_cb_frame_hdr(pst_tx_ctl));
            st_tx_dump_param.puc_mac_payload_addr = oal_netbuf_payload(pst_netbuf);
            st_tx_dump_param.uc_mac_hdr_len       = MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl);
            st_tx_dump_param.us_mac_frame_len     = (oal_uint16)MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)
                                                  + (oal_uint16)oal_netbuf_get_len(pst_netbuf);

            st_tx_dump_param.en_frame_switch      = en_frame_switch;
            st_tx_dump_param.en_cb_switch         = en_cb_switch;
            st_tx_dump_param.en_dscr_switch       = en_dscr_switch;
            oal_set_mac_addr(st_tx_dump_param.auc_user_macaddr, auc_user_macaddr);

            dmac_tx_dump(&st_tx_dump_param);
        }
        else
        {
            OAM_WARNING_LOG0(0, OAM_SF_TX, "{dmac_tx_dump_data::pst_netbuf null.}");
        }

        pst_dlist_node = pst_dlist_node->pst_next;
    }
}

/*****************************************************************************
 函 数 名  : dmac_tx_dump_mgmt
 功能描述  : 打印管理帧以及对应的发送描述符
 输入参数  : us_frame_len:帧长度(帧头+帧体)
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_tx_dump_mgmt(
                                        hal_to_dmac_device_stru *pst_hal_device,
                                        oal_netbuf_stru *pst_netbuf_mgmt,
                                        oal_uint16 us_frame_len,
                                        oal_uint8  uc_mac_hdr_len,
                                        hal_tx_dscr_stru *pst_mgmt_dscr)
{
    mac_tx_ctl_stru       *pst_tx_cb;
    oal_switch_enum_uint8  en_frame_switch = 0;
    oal_switch_enum_uint8  en_cb_switch = 0;
    oal_switch_enum_uint8  en_dscr_switch = 0;
    oal_uint32             ul_ret;
    oal_uint8              auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    dmac_tx_dump_param_stru  st_tx_dump_param;

    pst_tx_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf_mgmt);

    /* 获取开关，要区分是组播帧还是单播帧的开关 */
    ul_ret = dmac_tx_dump_get_switch(OAM_USER_TRACK_FRAME_TYPE_MGMT,
                                     &en_frame_switch,
                                     &en_cb_switch,
                                     &en_dscr_switch,
                                     pst_tx_cb);
    if (OAL_ERR_CODE_PTR_NULL == ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dump_mgmt::dmac_tx_dump_get_switch failed[%d].}", ul_ret);
        return;
    }

    if (OAL_SUCC == ul_ret)
    {
        /* 获取用户mac地址，用于SDT过滤 */
        ul_ret = dmac_tx_dump_get_user_macaddr(pst_tx_cb, auc_user_macaddr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_tx_dump_mgmt::dmac_tx_get_user_macaddr failed[%d].", ul_ret);

            return;
        }
    }
    /* 填写打印参数 */
    st_tx_dump_param.en_cb_switch = en_cb_switch;
    st_tx_dump_param.en_dscr_switch = en_dscr_switch;
    st_tx_dump_param.en_frame_switch = en_frame_switch;
    st_tx_dump_param.pst_hal_device = pst_hal_device;
    st_tx_dump_param.pst_netbuf = pst_netbuf_mgmt;
    st_tx_dump_param.pst_tx_cb = pst_tx_cb;
    st_tx_dump_param.pst_tx_dscr = pst_mgmt_dscr;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    st_tx_dump_param.puc_mac_hdr_addr =  (oal_uint8 *)(mac_get_cb_frame_hdr(pst_tx_cb));
    st_tx_dump_param.uc_mac_hdr_len = MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_cb);
    st_tx_dump_param.puc_mac_payload_addr =  (oal_uint8 *)(mac_get_cb_frame_hdr(pst_tx_cb))+st_tx_dump_param.uc_mac_hdr_len;
    st_tx_dump_param.us_mac_frame_len =  (oal_uint16)MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_cb)
                                                  + (oal_uint16)MAC_GET_CB_MPDU_LEN(pst_tx_cb);
#else
    st_tx_dump_param.puc_mac_hdr_addr = oal_netbuf_header(pst_netbuf_mgmt);
    st_tx_dump_param.puc_mac_payload_addr = oal_netbuf_payload(pst_netbuf_mgmt);
    st_tx_dump_param.uc_mac_hdr_len = uc_mac_hdr_len;
    st_tx_dump_param.us_mac_frame_len = us_frame_len;
#endif

    oal_set_mac_addr(st_tx_dump_param.auc_user_macaddr, auc_user_macaddr);

    dmac_tx_dump(&st_tx_dump_param);
}

/*****************************************************************************
 函 数 名  : dmac_tx_pause_info
 功能描述  : 用于定位发送过程TID发送挂起问题，主要是移窗卡死以及pause队列暂停
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月10日
    作    者   : t00190962
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_tx_pause_info(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_tx_ctl_stru            *pst_tx_ctl_first;
    dmac_user_stru             *pst_dmac_user;
#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
    dmac_user_query_stats_stru *pst_query_stats;
    mac_device_stru            *pst_mac_device;
    oal_rate_info_stru          st_txrate;
    static oal_uint8            uc_fe_print_ctrl = 0;   /* 寄存器输出，每进入此函数3次输出一次 */
#endif /* #if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV) */
    dmac_tid_stru              *pst_tid_queue;
    dmac_ba_tx_stru            *pst_tid_ba_hdl;

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_netbuf_stru            *pst_netbuf_tmp;
    oal_dlist_head_stru        *pst_entry_tmp;
    oal_uint32                  ul_count = 0;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    oal_uint32                 ul_mode_sel;
#endif

    pst_tx_ctl_first  = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    if(OAL_PTR_NULL == pst_tx_ctl_first)
    {
        return;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl_first));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        return;
    }

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        return;
    }
#endif /* #if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV) */

    /* 取TID队列0信息 */
    pst_tid_queue = &pst_dmac_user->ast_tx_tid_queue[0];
#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1151)
    OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_pause_info::uc_is_paused = %d, uc_num_dq = %d, uc_retry_num = %d, us_mpdu_num = %d",
      pst_tid_queue->uc_is_paused, pst_tid_queue->uc_num_dq, pst_tid_queue->uc_retry_num, pst_tid_queue->us_mpdu_num);
#else
    OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_pause_info::user idx = %d, uc_is_paused = %d, uc_num_dq = %d, uc_retry_num = %d, us_mpdu_num = %d", 5,
                          pst_tid_queue->us_user_idx, pst_tid_queue->uc_is_paused, pst_tid_queue->uc_num_dq, pst_tid_queue->uc_retry_num, pst_tid_queue->us_mpdu_num);
#endif /* #if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1151) */

    pst_tid_ba_hdl = pst_tid_queue->pst_ba_tx_hdl;

    if (pst_tid_ba_hdl != OAL_PTR_NULL)
    {
        OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_pause_info::start = %d, last_seq_num = %d, size = %d, baw_head = %d",
          pst_tid_ba_hdl->us_baw_start, pst_tid_ba_hdl->us_last_seq_num, pst_tid_ba_hdl->us_baw_size, pst_tid_ba_hdl->us_baw_head);
    }

    /* 加入判断，当前低功耗以及算法都依赖于mpdu和retry数，mpdu个数包含retry num数，如果与队列中数据不匹配会出错 */
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    ul_count = 0;
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry_tmp, &pst_tid_queue->st_retry_q)
    {
        ul_count++;
    }
    if (ul_count != pst_tid_queue->uc_retry_num)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_pause_info::warning!!! retry num:%d != retry q element num.}", ul_count);
    }

    OAL_NETBUF_SEARCH_FOR_EACH(pst_netbuf_tmp, &pst_tid_queue->st_buff_head)
    {
        ul_count++;
    }
    if (ul_count != pst_tid_queue->us_mpdu_num)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_pause_info::warning!!! mpdu num:%d != retry q and netbuf q element num.", ul_count);
    }
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

#if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV)
    pst_query_stats = &pst_dmac_user->st_query_stats;

    /* 定时打印统计，信息上报字段st_query_stats，1102专用 */
    OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_pause_info: stat info rssi = %d, tx succ pkt = %u, tx fail pkt = %u, tx retry cnt = %u, rx pkt = %u, rx dropped misc= %u.}", 6,
        pst_dmac_vap->st_query_stats.ul_signal, pst_query_stats->ul_hw_tx_pkts, pst_query_stats->ul_tx_failed, pst_query_stats->ul_tx_retries, pst_query_stats->ul_drv_rx_pkts, pst_query_stats->ul_rx_dropped_misc);

    dmac_config_get_tx_rate_info(&(pst_dmac_vap->st_tx_alg), &(pst_mac_device->st_mac_rates_11g[0]), &st_txrate);
    OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_pause_info: tx rate info legacy = %d, mcs = %d, flags = %d, nss = %d, rx rate(kbps) = %d}", 5,
        st_txrate.legacy, st_txrate.mcs, st_txrate.flags, st_txrate.nss, pst_mac_device->pst_device_stru->ul_rx_rate);

    OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_pause_info: hardware Q inf be= %d, vi = %d, vo = %d, mgmt = %d, netbuf(1544)free = %d}", 5,
        pst_hal_device->ast_tx_dscr_queue[WLAN_WME_AC_BE].uc_ppdu_cnt,
        pst_hal_device->ast_tx_dscr_queue[WLAN_WME_AC_VI].uc_ppdu_cnt,
        pst_hal_device->ast_tx_dscr_queue[WLAN_WME_AC_VO].uc_ppdu_cnt,
        pst_hal_device->ast_tx_dscr_queue[WLAN_WME_AC_MGMT].uc_ppdu_cnt,
        g_st_netbuf_pool.ast_subpool_table[2].us_free_cnt);

    dmac_rx_compatibility_show_stat(pst_dmac_user);
    /* 异常发送完成时间的统计信息 */
    if (pst_hal_device->st_tx_excp_info.us_tx_excp_cnt)
    {
        OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                    "{dmac_tx_pause_info:: Excp_tx_cnt %d; The max_offset_tsf %d, with mpdu_len %d, q_num %d}",
                    pst_hal_device->st_tx_excp_info.us_tx_excp_cnt,
                    pst_hal_device->st_tx_excp_info.us_max_offset_tsf,
                    pst_hal_device->st_tx_excp_info.us_mpdu_len,
                    pst_hal_device->st_tx_excp_info.uc_q_num);
        OAL_MEMZERO((oal_uint8 *)&pst_hal_device->st_tx_excp_info, OAL_SIZEOF(hal_tx_excp_info_stru));
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_get_btcoex_pa_status(&ul_mode_sel);
    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_COEX, "{dmac_tx_pause_info:: mode select: 0x%x}", ul_mode_sel);
#endif

    /* 进入此函数，每隔一段时间输出寄存器OTA信息和低功耗统计信息 */
    if (0 == ((++uc_fe_print_ctrl) % 3))
    {
#ifdef _PRE_WLAN_DFT_STAT
        dmac_dft_report_all_ota_state(&pst_dmac_vap->st_vap_base_info);
#endif  /* _PRE_WLAN_DFT_STAT */
        /* 打印sta低功耗维测信息 */
#ifdef _PRE_WLAN_FEATURE_STA_PM
        /* 协议的计数 */
        dmac_pm_key_info_dump(pst_dmac_vap);

        /* 平台的计数*/
        PM_WLAN_DumpSleepCnt();
#endif  /* _PRE_WLAN_FEATURE_STA_PM */

    }
#endif  /* #if (_PRE_PRODUCT_ID ==_PRE_PRODUCT_ID_HI1102_DEV) */

    return;
}

/*****************************************************************************
 函 数 名  : dmac_tx_excp_free_dscr
 功能描述  : 异常释放描述符
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_tx_excp_free_dscr(oal_dlist_head_stru *pst_tx_dscr_list_hdr, hal_to_dmac_device_stru *pst_hal_device)
{
    oal_netbuf_stru     *pst_netbuf = OAL_PTR_NULL;
    hal_tx_dscr_stru    *pst_dscr;
    oal_dlist_head_stru *pst_dscr_node;

    while (OAL_FALSE == oal_dlist_is_empty(pst_tx_dscr_list_hdr))
    {
        pst_dscr_node = oal_dlist_delete_head(pst_tx_dscr_list_hdr);
        pst_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_node, hal_tx_dscr_stru, st_entry);

        pst_netbuf = pst_dscr->pst_skb_start_addr;
        pst_dscr->pst_skb_start_addr = OAL_PTR_NULL;
        if (OAL_SUCC != OAL_MEM_FREE((oal_void *)pst_dscr, OAL_TRUE))
        {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_excp_free_dscr::pst_dscr null.}");
        }

        dmac_tx_excp_free_netbuf(pst_netbuf);
    }

    return;
}

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
/*****************************************************************************
 函 数 名  : dmac_tx_excp_free_netbuf
 功能描述  : 因错误返回释放netbuf内存空间
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_excp_free_netbuf(oal_netbuf_stru *pst_netbuf)
{
    oal_netbuf_stru             *pst_buf_next = OAL_PTR_NULL;
    mac_ieee80211_frame_stru    *pst_frame_header = OAL_PTR_NULL;
    mac_tx_ctl_stru             *pst_tx_ctl = OAL_PTR_NULL;
    wlan_frame_type_enum_uint8   en_type;
#ifdef _PRE_MEM_DEBUG_MODE
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    /*lint -e718*//*lint -e746*/
    oal_uint32 ul_return_addr      = (oal_uint32)__return_address();
    /*lint +e718*//*lint +e746*/
#endif
#endif
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_FAIL;
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    if (DMAC_USER_ALG_SMARTANT_NULLDATA_PROBE == pst_tx_ctl->en_is_probe_data)
    {
        return OAL_FAIL;
    }

    en_type = (wlan_frame_type_enum_uint8) MAC_GET_CB_FRAME_TYPE(pst_tx_ctl);
    pst_frame_header = (mac_ieee80211_frame_stru *)mac_get_cb_frame_hdr(pst_tx_ctl);
    if (OAL_PTR_NULL == pst_frame_header)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_excp_free_netbuf::pst_frame_header null.}");

        return OAL_FAIL;
    }
    mac_set_cb_frame_hdr(pst_tx_ctl, OAL_PTR_NULL);

    /*如果802.11mac头不在skb中，则释放其占用的内存*/
    if((0 == mac_get_cb_80211_mac_head_type(pst_tx_ctl)) && (WLAN_DATA_BASICTYPE == en_type))
    {
        if (OAL_SUCC != OAL_MEM_FREE((oal_void *)pst_frame_header, OAL_TRUE))
        {
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_excp_free_netbuf::pst_frame_header null.}");

            return OAL_FAIL;
        }
    }

    while (OAL_PTR_NULL != pst_netbuf)
    {
        pst_buf_next = oal_get_netbuf_next(pst_netbuf);

        if(OAL_ERR_CODE_OAL_MEM_ALREADY_FREE==oal_netbuf_free(pst_netbuf))
        {
        #ifdef _PRE_MEM_DEBUG_MODE
        #if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
            OAL_IO_PRINT("double free caller[%x]!\r\n",ul_return_addr);
        #endif
        #endif
        }

        pst_netbuf = pst_buf_next;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_save_frag_seq
 功能描述  : 记录分片报文的seq num
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_save_frag_seq(dmac_user_stru     *pst_dmac_user,
                                                         mac_tx_ctl_stru    *pst_tx_ctl)
{
    oal_uint8                   uc_tid = 0;
    mac_ieee80211_frame_stru   *pst_mac_header = OAL_PTR_NULL;

    pst_mac_header = (mac_ieee80211_frame_stru   *)mac_get_cb_frame_hdr(pst_tx_ctl);
    uc_tid         = mac_get_cb_tid(pst_tx_ctl);

    if (pst_mac_header->st_frame_control.bit_more_frag != 0 && 0 == pst_mac_header->bit_frag_num)
    {
        pst_dmac_user->aus_txseqs_frag[uc_tid] = pst_dmac_user->aus_txseqs[uc_tid];
        pst_dmac_user->aus_txseqs[uc_tid] = DMAC_BA_SEQ_ADD(pst_dmac_user->aus_txseqs[uc_tid], 1);
    }
}

/*****************************************************************************
 函 数 名  : dmac_tx_seqnum_set
 功能描述  : 填写seq num
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_tx_seqnum_set(dmac_user_stru *pst_dmac_user, mac_tx_ctl_stru *pst_tx_ctl)
{
    oal_uint8                   uc_tid = 0;
    mac_ieee80211_frame_stru   *pst_mac_header = OAL_PTR_NULL;

    pst_mac_header = (mac_ieee80211_frame_stru *)mac_get_cb_frame_hdr(pst_tx_ctl);
    uc_tid         = mac_get_cb_tid(pst_tx_ctl);

    if (OAL_TRUE != mac_get_cb_is_qosdata(pst_tx_ctl))
    {
        return;
    }

    if (OAL_LIKELY((0 == pst_mac_header->st_frame_control.bit_more_frag ) && (0 == pst_mac_header->bit_frag_num)))
    {
        pst_mac_header->bit_seq_num 	= pst_dmac_user->aus_txseqs[uc_tid];
        mac_set_cb_seqnum(pst_tx_ctl, pst_dmac_user->aus_txseqs[uc_tid]);
        pst_dmac_user->aus_txseqs[uc_tid] = DMAC_BA_SEQ_ADD(pst_dmac_user->aus_txseqs[uc_tid], 1);
    }
    else
    {
        pst_mac_header->bit_seq_num = pst_dmac_user->aus_txseqs_frag[uc_tid];
    }
}

/*****************************************************************************
 函 数 名  : dmac_tx_seqnum_set_ampdu
 功能描述  : 填写seq num
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_tx_seqnum_set_ampdu(dmac_user_stru *pst_dmac_user, mac_tx_ctl_stru *pst_tx_ctl)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_ieee80211_frame_stru   *pst_frame_hdr = OAL_PTR_NULL;
#endif
    oal_uint8                   uc_tid = 0;
    uc_tid                           = mac_get_cb_tid(pst_tx_ctl);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_frame_hdr                    = mac_get_cb_frame_hdr(pst_tx_ctl);
    pst_frame_hdr->bit_seq_num       = pst_dmac_user->aus_txseqs[uc_tid];
#endif
    mac_set_cb_seqnum(pst_tx_ctl, pst_dmac_user->aus_txseqs[uc_tid]);
    pst_dmac_user->aus_txseqs[uc_tid] = DMAC_BA_SEQ_ADD(pst_dmac_user->aus_txseqs[uc_tid], 1);
}
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_tx_get_amsdu_params
 功能描述  : 填写发送参数，amsdu中子msdu的地址和长度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或者错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月19日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_get_amsdu_params(
                                        oal_netbuf_stru  *pst_netbuf,
                                        mac_tx_ctl_stru  *pst_tx_ctl,
                                        hal_tx_mpdu_stru *pst_mpdu)
{
    oal_uint8            uc_msdu_num;                /* MPDU中子msdu的个数 */
    oal_uint8            uc_loop;
    oal_netbuf_stru     *pst_next_buf;
    oal_uint8           *puc_netbuf_data;            /* netbuf的data指针 */

    if (OAL_UNLIKELY((OAL_TRUE == mac_get_cb_is_amsdu(pst_tx_ctl)) &&
                     (OAL_TRUE != MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctl))))
    {
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{dmac_tx_get_amsdu_params::not first MSDU in MPDU.");
        return OAL_FAIL;
    }

    uc_msdu_num = MAC_GET_CB_NETBUF_NUM(pst_tx_ctl);
    if((uc_msdu_num >> 1) > WLAN_DSCR_SUBTABEL_MAX_NUM)
    {
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{dmac_tx_get_amsdu_params::buffer overflow.");
        return OAL_FAIL;
    }

    for (uc_loop = 0; uc_loop < uc_msdu_num; uc_loop++)
    {
        pst_next_buf = oal_get_netbuf_next(pst_netbuf);

        /* 获取SUB-MSDU的头指针 */
        puc_netbuf_data   = oal_netbuf_payload(pst_netbuf);

        /* 填写子帧发送参数 */
        if (!(uc_loop & 0x1))
        {
            pst_mpdu->ast_msdu_addr[uc_loop >> 1].ul_msdu_addr0 = (oal_uint32)puc_netbuf_data;
            pst_mpdu->ast_msdu_addr[uc_loop >> 1].us_msdu0_len  = (oal_uint16)oal_netbuf_get_len(pst_netbuf);
        }
        else
        {
            pst_mpdu->ast_msdu_addr[uc_loop >> 1].ul_msdu_addr1 = (oal_uint32)puc_netbuf_data;
            pst_mpdu->ast_msdu_addr[uc_loop >> 1].us_msdu1_len  = (oal_uint16)oal_netbuf_get_len(pst_netbuf);
        }

        pst_netbuf = pst_next_buf;
    }

    /* 如果子帧个数是奇数，则最后填的子表的第二段不存在，清零 */
    if (uc_msdu_num & 0x1)
    {
        pst_mpdu->ast_msdu_addr[uc_msdu_num >> 1].ul_msdu_addr1 = 0;
        pst_mpdu->ast_msdu_addr[uc_msdu_num >> 1].us_msdu1_len  = 0;
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_dequeue_first_mpdu
 功能描述  : 从队列中取出第一个mpdu,将它从队列删除并返回，一个mpdu中可能有多个skb
 输入参数  : st_queue_head: 队列头
 输出参数  : 无
 返 回 值  : oal_netbuf_stru*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : z00237171
    修改内容   : 新生成函数
  2.日    期   : 2013年9月22日
    作    者   : z52447
    修改内容   : 从PSM模块提取出来作为公共函数

*****************************************************************************/
oal_netbuf_stru* dmac_tx_dequeue_first_mpdu(oal_netbuf_head_stru  *pst_netbuf_head)
{
    oal_netbuf_stru        *pst_first_net_buf;
    oal_netbuf_stru        *pst_tmp_net_buf;
    oal_netbuf_stru        *pst_net_buf;
    mac_tx_ctl_stru        *pst_tx_ctrl;
    oal_uint8               uc_netbuf_num_per_mpdu;

    if(OAL_PTR_NULL == pst_netbuf_head)
    {
        return OAL_PTR_NULL;
    }

    pst_first_net_buf = OAL_NETBUF_HEAD_NEXT(pst_netbuf_head);
    pst_tx_ctrl       = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_first_net_buf);

    /* mpdu不是a-msdu，返回第一个net_buff即可 */
    if (OAL_FALSE == mac_get_cb_is_amsdu(pst_tx_ctrl))
    {
        //OAM_INFO_LOG0(0, OAM_SF_TX, "{dmac_dequeue_first_mpdu::not amsdu.}\r\n");

        pst_first_net_buf = oal_netbuf_delist(pst_netbuf_head);

        return pst_first_net_buf;
    }

    /* 出现这种异常只能将所有缓存帧释放掉 */
    if (OAL_FALSE == MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl))
    {
       /* 这个错误只有踩内存才会出现，如果出现就无法恢复，以太网来的包无法释放，
           软件复位也没用，内存也会泄漏
        */
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_dequeue_first_mpdu::not the first msdu.}");

        return OAL_PTR_NULL;
    }

    /* 节能队列中的第一个mpdu是a-msdu，获取skb个数 */
    uc_netbuf_num_per_mpdu = MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl);

    /* 将第一个mpdu中的所有skb从节能队列中取出，然后组成一个net_buff链 */
    pst_first_net_buf = oal_netbuf_delist(pst_netbuf_head);
    uc_netbuf_num_per_mpdu--;

    pst_tmp_net_buf = pst_first_net_buf;
    while (0 != uc_netbuf_num_per_mpdu)
    {
        pst_net_buf = oal_netbuf_delist(pst_netbuf_head);
        oal_set_netbuf_prev(pst_net_buf, pst_tmp_net_buf);
        oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

        oal_set_netbuf_next(pst_tmp_net_buf, pst_net_buf);

        pst_tmp_net_buf = pst_net_buf;

        uc_netbuf_num_per_mpdu--;
    }

    return pst_first_net_buf;

}

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
/*****************************************************************************
 函 数 名  : dmac_tx_queue_mpdu
 功能描述  : 将mpdu下所有netbuf加入skb链表中的尾部,需要考虑一个mpdu有多个netbuf
 输入参数  : pst_new: 要插入的新skb指针
             pst_head: skb链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月14日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_queue_mpdu(oal_netbuf_stru *pst_netbuf, oal_netbuf_head_stru *pst_head)
{
    oal_netbuf_stru    *pst_netbuf_tmp;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    mac_tx_ctl_stru    *pst_cb;
    oal_uint8           uc_netbuf_num_in_mpdu;
#endif

    pst_netbuf_tmp = pst_netbuf;
    /* 需要将所有的netbuf链加入 */
    while (OAL_PTR_NULL != pst_netbuf_tmp)
    {
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        /* 从每一个mpdu中第一个net_buf的CB字段获取该mpdu一共包含几个net_buff */
        pst_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf_tmp);
        uc_netbuf_num_in_mpdu = MAC_GET_CB_NETBUF_NUM(pst_cb);
#endif
        /* 将该mpdu的每一个net_buff加入到节能队列中 */
        pst_netbuf = pst_netbuf_tmp;
        while (
        #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            (0 != uc_netbuf_num_in_mpdu) &&
        #endif
            (OAL_PTR_NULL != pst_netbuf))
        {
            pst_netbuf_tmp = oal_get_netbuf_next(pst_netbuf);

            oal_netbuf_add_to_list_tail(pst_netbuf, pst_head);

            pst_netbuf = pst_netbuf_tmp;

        #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            uc_netbuf_num_in_mpdu--;
        #endif
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_tx_queue_mpdu_head
 功能描述  : 将mpdu下所有netbuf加入skb链表中的头部,51需要考虑一个mpdu有多个netbuf;02amsdu只占单buf,不需考虑
 输入参数  : pst_new: 要插入的新skb指针
             pst_head: skb链表头指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月31日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_queue_mpdu_head(oal_netbuf_stru *pst_netbuf, oal_netbuf_head_stru *pst_head)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_netbuf_addlist(pst_head, pst_netbuf);
#else/* 1151需要考虑mpdu占多个buf场景,暂未修改 */
    dmac_tx_queue_mpdu(pst_netbuf, pst_head);
#endif
    return;
}
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

/*****************************************************************************
 函 数 名  : mac_check_cb_tid
 功能描述  : 更新所有txop alg结构体中与保护模式相关的参数
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
OAL_STATIC OAL_INLINE oal_void mac_check_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl)
{
    if(mac_get_cb_tid(pst_tx_ctrl) > (WLAN_WME_MAX_TID_NUM -1))
    {
        oam_report_netbuf_cb(BROADCAST_MACADDR,(oal_uint8 *)pst_tx_ctrl,OAM_OTA_TYPE_TX_CB);
        OAM_ERROR_LOG2(0, OAM_SF_ANY,"{mac_set_cb_tid: uc_tid: [0x%x]; cb addr:0x%x}\r\n",mac_get_cb_tid(pst_tx_ctrl), pst_tx_ctrl);
    }
}

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
/*****************************************************************************
 函 数 名  : dmac_tx_set_txopps_param
 功能描述  : 把txop ps相关的量填到txop_feature中，后续填到描述符里面
 输入参数  : pst_dmac_vap :     DMAC模块vap指针
             pst_dmac_user:     DMAC模块用户指针
             pst_txop_feature:  txop指针
             en_ismcast      :  是否是组播帧
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月18日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_set_txopps_param(dmac_vap_stru  *pst_dmac_vap,
                                                      dmac_user_stru *pst_dmac_user,
                                                      hal_tx_txop_feature_stru *pst_txop_feature,
                                                      oal_bool_enum_uint8       en_ismcast)
{
    /* 以下根据Draft P802.11ac_D3.1.pdf 9.17a填写 */
    if (en_ismcast)
    {
        pst_txop_feature->st_groupid_partial_aid.uc_group_id    = 63;
        pst_txop_feature->st_groupid_partial_aid.us_partial_aid = 0;
    }
    else
    {
        pst_txop_feature->st_groupid_partial_aid.uc_group_id    = pst_dmac_user->uc_groupid;
        pst_txop_feature->st_groupid_partial_aid.us_partial_aid = pst_dmac_user->us_partial_aid;
    }

    switch (pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        case WLAN_VAP_MODE_BSS_STA:
            pst_txop_feature->st_groupid_partial_aid.uc_txop_ps_not_allowed = OAL_TRUE;
        break;

        case WLAN_VAP_MODE_BSS_AP:
            if (pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_txop_ps)
            {
                pst_txop_feature->st_groupid_partial_aid.uc_txop_ps_not_allowed = OAL_FALSE;
            }
            else
            {
                pst_txop_feature->st_groupid_partial_aid.uc_txop_ps_not_allowed = OAL_TRUE;
            }
        break;

        default:
        break;
    }
}

/*****************************************************************************
 函 数 名  : dmac_tx_get_txop
 功能描述  : 根据dmac信息，填写txop的参数
 输入参数  : pst_dmac_vap :     DMAC模块vap指针
             pst_dmac_user:     DMAC模块用户指针
             pst_txop_feature:  txop指针
             en_ismcast      :  是否是组播帧
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月22日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_tx_get_txop(dmac_vap_stru  *pst_dmac_vap,
                                          dmac_user_stru *pst_dmac_user,
                                          hal_tx_txop_feature_stru *pst_txop_feature,
                                          oal_bool_enum_uint8       en_ismcast)
{
    /* 获取TXOP特性发送参数 */
    pst_txop_feature->pst_security = &(pst_dmac_user->st_user_base_info.st_user_tx_info.st_security);
    pst_txop_feature->pst_security->en_cipher_protocol_type = pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type;
    pst_txop_feature->pst_security->uc_cipher_key_id        = pst_dmac_user->st_user_base_info.st_key_info.uc_default_index;

    dmac_tx_set_txopps_param(pst_dmac_vap, pst_dmac_user, pst_txop_feature, en_ismcast);
}
#if 0
/*****************************************************************************
 函 数 名  : dmac_tx_update_bandwidth_mode_ap
 功能描述  : AP更新发送描述符中的"freq bandwidth mode"
 输入参数  : pst_dmac_vap : 指向AP
             pst_dmac_user: 指向STA
 输出参数  : pst_txop_alg : 算法结构体指针，其中包含"freq bandwidth mode"，用于
                            发送描述符的填写
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月27日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_update_bandwidth_mode_ap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, hal_tx_txop_alg_stru *pst_txop_alg)
{
    oal_uint8   uc_channel_bandwidth = 0;    /* BW20 */

    /* AP能够发送40MHz数据 */
    /* (1) AP本身支持40MHz发送 */
    /* (2) 对端STA支持40MHz发送 */
    if ((WLAN_BAND_WIDTH_40PLUS  == pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth)  ||
        (WLAN_BAND_WIDTH_40MINUS ==  pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth))
    {
        if (1 == pst_dmac_user->st_user_base_info.st_ht_hdl.bit_supported_channel_width)
        {
            uc_channel_bandwidth = BIT2;     /* BW40 */

        }
    }

    /* AP能够发送80MHz数据 */
    /* (1) AP本身支持80MHz发送 */
    /* (2) 对端STA支持80MHz发送 */
    if ((WLAN_BAND_WIDTH_80PLUSPLUS   == pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth)  ||
        (WLAN_BAND_WIDTH_80PLUSMINUS  ==  pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth) ||
        (WLAN_BAND_WIDTH_80MINUSPLUS  == pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth)  ||
        (WLAN_BAND_WIDTH_80MINUSMINUS == pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth))
    {
        if (0 == pst_dmac_user->st_user_base_info.st_vht_hdl.bit_supported_channel_width)
        {
            uc_channel_bandwidth = BIT3;     /* BW80 */
        }
    }

    pst_txop_alg->st_rate.uc_channel_bandwidth = OAL_MIN(pst_txop_alg->st_rate.uc_channel_bandwidth, uc_channel_bandwidth);
}

/*****************************************************************************
 函 数 名  : dmac_tx_update_bandwidth_mode_sta
 功能描述  : STA更新发送描述符中的"freq bandwidth mode"
 输入参数  : pst_dmac_vap : 指向STA
             pst_dmac_user: 指向AP
 输出参数  : pst_txop_alg : 算法结构体指针，其中包含"freq bandwidth mode"，用于
                            发送描述符的填写
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月27日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_update_bandwidth_mode_sta(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, hal_tx_txop_alg_stru *pst_txop_alg)
{
    pst_txop_alg->st_rate.uc_channel_bandwidth = 0;             /* BW20 */

    /* STA能够发送40MHz数据 */
    /* (1) STA本身支持40MHz发送，对端AP支持40MHz发送 */
    /* (2) 对端AP运行在40MHz */
    if ((WLAN_BAND_WIDTH_40PLUS  == pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth)  ||
        (WLAN_BAND_WIDTH_40MINUS ==  pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth))
    {
        if (1 == pst_dmac_user->st_user_base_info.st_ht_hdl.bit_sta_chan_width)
        {
            pst_txop_alg->st_rate.uc_channel_bandwidth = BIT2;  /* BW40 */
        }
    }

    /* STA能够发送40MHz数据 */
    /* (1) STA本身支持80MHz发送，对端AP支持80MHz发送 */
    /* (2) 对端AP运行在80MHz */
    if ((WLAN_BAND_WIDTH_80PLUSPLUS   == pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth)  ||
        (WLAN_BAND_WIDTH_80PLUSMINUS  ==  pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth) ||
        (WLAN_BAND_WIDTH_80MINUSPLUS  == pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth)  ||
        (WLAN_BAND_WIDTH_80MINUSMINUS == pst_dmac_vap->st_vap_base_info.st_channel.en_bandwidth))
    {
        if (1 == pst_dmac_user->st_user_base_info.st_vht_hdl.uc_channel_width)
        {
            pst_txop_alg->st_rate.uc_channel_bandwidth = BIT3; /* BW80 */
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_tx_update_bandwidth_mode
 功能描述  : 更新发送描述符中的"freq bandwidth mode"
 输入参数  : pst_dmac_vap : VAP结构体指针
             pst_dmac_user: USER结构体指针
 输出参数  : pst_txop_alg : 算法结构体指针，其中包含"freq bandwidth mode"，用于
                            发送描述符的填写
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月27日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_update_bandwidth_mode(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, hal_tx_txop_alg_stru *pst_txop_alg)
{
    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_tx_update_bandwidth_mode_ap(pst_dmac_vap, pst_dmac_user, pst_txop_alg);
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_tx_update_bandwidth_mode_sta(pst_dmac_vap, pst_dmac_user, pst_txop_alg);
    }
}
#endif
#ifdef  _PRE_WLAN_FEATURE_TSF_SYNC
/*****************************************************************************
 函 数 名  : dmac_tx_get_timestamp
 功能描述  : tsf sync
 输入参数  :
             pst_hal_vap:     vap hal指针
 输出参数  : pus_tsf:         当前时间戳
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月12日
    作    者   : liuzhengqi
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16 dmac_sync_tx_dscr_tsf(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 us_tsf)
{
    oal_uint16      us_tmp_tsf_lo = 0;
    dmac_vap_stru   *pst_dmac_vap;


    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_hal_vap->uc_mac_vap_id);
    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        return us_tmp_tsf_lo;
    }

    us_tmp_tsf_lo = us_tsf - pst_dmac_vap->us_sync_tsf_value; /*sync the tsf*/
    if (pst_dmac_vap->us_sync_tsf_value != 0)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "dmac_sync_tx_dscr_tsf:origi tsf:[%d],after sync us_tmp_tsf_lo:[%d]",us_tsf, us_tmp_tsf_lo);
    }
    return us_tmp_tsf_lo;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_tx_get_timestamp
 功能描述  : 获取时间戳
 输入参数  :
             pst_hal_vap:     vap hal指针
 输出参数  : pus_tsf:         当前时间戳
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月22日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_tx_get_timestamp(hal_to_dmac_vap_stru *pst_hal_vap, oal_uint16 *pus_tsf)
{
    oal_uint32                   ul_tsf = 0;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    hal_to_dmac_device_stru     *pst_hal_device;
    hal_to_dmac_vap_stru        *pst_hal_vap_sta0;

    hal_get_hal_to_dmac_device(pst_hal_vap->uc_chip_id,pst_hal_vap->uc_device_id, &pst_hal_device);

    /* proxysta 没有tsf寄存器，如果取Proxy STA的寄存器，用sta的tsf寄存器代替,这里将Proxy STA的hal_vap换成sta0的hal_vap */
    if ((pst_hal_vap->uc_vap_id >= WLAN_PROXY_STA_START_ID) &&(pst_hal_vap->uc_vap_id <= WLAN_PROXY_STA_END_ID))
    {
        //OAM_ERROR_LOG0(pst_hal_vap->uc_vap_id,OAM_SF_PROXYSTA, "{dmac_tx_get_timestamp::vap is a proxysta}");
        hal_get_hal_vap(pst_hal_device, WLAN_STA0_HAL_VAP_ID, &pst_hal_vap_sta0);
        hal_vap_tsf_get_32bit(pst_hal_vap_sta0, &ul_tsf);
    }
    else
    {
        //OAM_ERROR_LOG0(pst_hal_vap->uc_vap_id,OAM_SF_PROXYSTA, "{dmac_tx_get_timestamp::vap is not a proxysta}");
        hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf);
    }
#else
    hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf);
#endif

#if ((_PRE_OS_VERSION_RAW == _PRE_OS_VERSION) &&(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV))
    /*Zourong add for debug,make sure not read tsf when inner tsf is being stopped*/
    if(0!=(READW(0x50000400)&(1<<3)))
    {
        OAM_ERROR_LOG0(pst_hal_vap->uc_vap_id,OAM_SF_TX, "{dmac_tx_get_timestamp::Read TSF When ext tsf is working}");
    }
#endif
     /* DTS2014102201798 规避芯片lifetime问题，获取硬件tsf值时减去1ms，再写入描述符 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    *pus_tsf = ((ul_tsf >> 10) & 0xffff) - 1; /* 将微妙换算成毫秒，取16位 */
#else
    *pus_tsf = ((ul_tsf >> 10) & 0xffff); /* 将微妙换算成毫秒，取16位 */

#ifdef  _PRE_WLAN_FEATURE_TSF_SYNC
    *pus_tsf = dmac_sync_tx_dscr_tsf(pst_hal_vap, *pus_tsf);
#endif

#endif
}

/*****************************************************************************
 函 数 名  : dmac_tx_bf_add_ht_control_field
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_tx_bf_add_ht_control_field(
                                    hal_to_dmac_device_stru  *pst_hal_device,
                                    mac_tx_ctl_stru          *pst_tx_ctl,
                                    oal_dlist_head_stru      *pst_tx_dscr_list_hdr,
                                    hal_tx_txop_alg_stru     *pst_txop_alg,
                                    hal_tx_ppdu_feature_stru *pst_ppdu_feature)
{
    hal_tx_dscr_stru            *pst_tx_dscr        = OAL_PTR_NULL;
    oal_dlist_head_stru         *pst_dscr_entry     = OAL_PTR_NULL;
    oal_dlist_head_stru         *pst_dlist_tmp      = OAL_PTR_NULL;

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dscr_entry, pst_dlist_tmp, pst_tx_dscr_list_hdr)
    {
        pst_tx_dscr = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        /* frame control B15(Order)改为1，加上HTC部分，并且HTC字段的B22B23值是11,改写描述符 */
        dmac_tx_set_htc_field(pst_hal_device,pst_tx_dscr ,pst_tx_ctl, pst_ppdu_feature);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_dscr_queue_add_dscr_list
 功能描述  : 将一个发送描述符链表加入发送描述符队列
 输入参数  : past_tx_dscr_queue  : 发送描述符队列头
             uc_qid              : 发送描述符队列ID
             pst_tx_dscr_list_hdr: 发送描述符链表头指针
 输出参数  : 无
 返 回 值  : OAL_SUCC 或者其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_tx_dscr_queue_add_dscr_list(
                hal_to_dmac_device_stru *       pst_hal_device,
                oal_uint8                       uc_qid,
                oal_dlist_head_stru            *pst_tx_dscr_list_hdr,
                oal_uint8                       uc_ppdu_cnt)
{
    /* 将指定的发送描述符链表加入发送描述符队列 需要唐慧超提供 */
    oal_dlist_join_tail(&(pst_hal_device->ast_tx_dscr_queue[uc_qid].st_header), pst_tx_dscr_list_hdr);
    pst_hal_device->ast_tx_dscr_queue[uc_qid].uc_ppdu_cnt += uc_ppdu_cnt;

#ifdef _PRE_DEBUG_MODE
    if (pst_hal_device->ast_tx_dscr_queue[uc_qid].uc_ppdu_cnt > 8)
    {
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }
#endif

    return OAL_SUCC;
}

oal_void dmac_post_soft_tx_complete_event(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_base_dscr, oal_uint8 uc_dscr_num)
{
    frw_event_mem_stru         *pst_event_mem = OAL_PTR_NULL;          /* 申请事件返回的内存指针 */
    frw_event_stru             *pst_hal_to_dmac_event = OAL_PTR_NULL;  /* 指向申请事件的payload指针 */
    hal_tx_complete_event_stru *pst_tx_comp_event;

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hal_tx_complete_event_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        return;
    }

    /* 获得事件指针 */
    pst_hal_to_dmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&pst_hal_to_dmac_event->st_event_hdr,
                        FRW_EVENT_TYPE_WLAN_TX_COMP,
                        HAL_TX_COMP_SUB_TYPE_TX,
                        OAL_SIZEOF(hal_tx_complete_event_stru),
                        FRW_EVENT_PIPELINE_STAGE_0,
                        pst_hal_device->uc_chip_id,
                        pst_hal_device->uc_device_id,
                        0);

    /*填写tx complete事件 */
    pst_tx_comp_event = (hal_tx_complete_event_stru *)(pst_hal_to_dmac_event->auc_event_data);
    pst_tx_comp_event->pst_base_dscr    = pst_base_dscr;        /* 设置描述符基地址 */
    pst_tx_comp_event->uc_dscr_num      = uc_dscr_num;          /* 发送的描述符的个数 */
    pst_tx_comp_event->pst_hal_device   = pst_hal_device;

    /* 分发 */
    frw_event_dispatch_event(pst_event_mem);

    /* 释放事件内存 */
    FRW_EVENT_FREE(pst_event_mem);
}

/*****************************************************************************
 函 数 名  : dmac_tx_data
 功能描述  : 数据帧发送处理函数
 输入参数  : pst_dmac_vap : DMAC模块VAP指针
             pst_dmac_user: DMAC模块用户指针
             pst_netbuf   : netbuf缓存
             uc_mpdu_num  : 需要发送的MPDU的个数
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月19日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint32  dmac_tx_data(
                dmac_vap_stru            *pst_dmac_vap,
                dmac_user_stru           *pst_dmac_user,
                mac_tx_ctl_stru          *pst_tx_ctl,
                oal_dlist_head_stru      *pst_tx_dscr_list_hdr,
                hal_tx_ppdu_feature_stru *pst_ppdu_feature,
                hal_tx_txop_alg_stru     *pst_txop_alg)
{
    hal_to_dmac_device_stru     *pst_hal_device;
    hal_tx_dscr_stru            *pst_tx_dscr;
    hal_tx_txop_feature_stru     st_txop_feature;
    oal_dlist_head_stru         *pst_dscr_entry;
    hal_tx_dscr_stru            *pst_dscr_temp;
    oal_uint8                    uc_ppdu_cnt;
    mac_tx_ctl_stru             *pst_cb = OAL_PTR_NULL;
    oal_uint8                    uc_ac;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    oal_uint32                   ul_bank3_bcn_period = 0;
#endif
    hal_tx_dscr_stru    *pst_last_dscr;
    oal_dlist_head_stru *pst_last_dscr_entry;
    oal_uint32           ul_tx_q_status;
    hal_tx_queue_type_enum_uint8 uc_q_num;

#ifdef _PRE_DEBUG_MODE
	oal_uint8                    uc_tid;
	dmac_tid_stru               *pst_tid_queue = OAL_PTR_NULL;
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    oal_uint8                    uc_data_type;
    oal_uint8                    uc_coex_data_type;
    oal_uint8                    uc_coex_wl_time = 0;

    bt_status_stru              *pst_bt_status;
#endif

    mac_device_stru             *pst_mac_device;
    pst_mac_device = (mac_device_stru*)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);



    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_data::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_hal_device = pst_dmac_vap->pst_hal_device;

#ifdef _PRE_WLAN_CHIP_TEST
    DMAC_CHIP_TEST_CALL(dmac_test_lpm_txopps_set_partial_aid(pst_dmac_vap, pst_dmac_user, DMAC_TEST_STUB_BEGIN));
    DMAC_CHIP_TEST_CALL(dmac_test_lpm_smps_set_rate(pst_tx_ctl,pst_txop_alg,DMAC_TEST_STUB_BEGIN));
    DMAC_CHIP_TEST_CALL(dmac_test_dfx_set_tx_cnt(pst_txop_alg));
#endif

    dmac_tx_get_txop(pst_dmac_vap, pst_dmac_user, &st_txop_feature, pst_tx_ctl->en_ismcast);

    /* DTS2015080507103 发送4 次握手eapol key 帧设置为不加密 */
    if (pst_tx_ctl->bit_is_eapol_key_ptk == OAL_TRUE)
    {
        st_txop_feature.pst_security->en_cipher_protocol_type = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    }
    /* DTS2015080507103 发送4 次握手eapol key 帧设置为不加密 */

    /*如果用户处于节能状态，则需要考虑设置当前帧的more data*/
    if (OAL_TRUE == pst_dmac_user->bit_ps_mode)
    {
        dmac_psm_tx_set_more_data(pst_dmac_user, pst_tx_ctl);
    }
#ifdef _PRE_WLAN_FEATURE_STA_PM
    dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);
#endif

    /* STA模式下根据节能模式设置power_mgmt位 */
#ifdef _PRE_WLAN_FEATURE_STA_PM
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_psm_tx_set_power_mgmt_bit(pst_dmac_vap, pst_tx_ctl);
    }
#endif
    pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_tx_dscr_list_hdr->pst_next, hal_tx_dscr_stru, st_entry);

/* 只1102需要tsf_restore逻辑 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    if ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode))
    {
    	/* 发送时如果发现staut bank3 的beacon周期为0 需要将ap的tsf同步给sta */
        hal_vap_get_beacon_period(pst_dmac_vap->pst_hal_vap, &ul_bank3_bcn_period);
        if (0 == ul_bank3_bcn_period)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"tx data staut bank3 bcn period 0 ap sync tsf to sta");
            hal_sta_tsf_restore(pst_dmac_vap->pst_hal_vap);
        }
    }
#endif

    /* debug版本中所有队列都需要填写tsf*/
#ifdef _PRE_DEBUG_MODE
    dmac_tx_get_timestamp(pst_dmac_vap->pst_hal_vap, &pst_ppdu_feature->us_tsf);
#else
    /* release版本中VO/VI队列都需要填写tsf*/
    if ((WLAN_WME_AC_VI == mac_get_cb_ac(pst_tx_ctl)) || (WLAN_WME_AC_VO == mac_get_cb_ac(pst_tx_ctl)))
    {
        dmac_tx_get_timestamp(pst_dmac_vap->pst_hal_vap, &pst_ppdu_feature->us_tsf);
    }
    /* g00260350 1102需要增加该维测*/
    dmac_tx_get_timestamp(pst_dmac_vap->pst_hal_vap, &pst_ppdu_feature->us_tsf);
#endif

    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_TX_GET_TSF);
    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_GET_TSF);

    if (WLAN_STAGGERED_SOUNDING == pst_txop_alg->st_rate.en_sounding_mode)
    {
        /*AMPDU的第一个MPDU帧控制字段（或者普通MPDU帧的控制字段）B15(Order)改为1，加上HTC部分，并且HTC字段的B22B23值是11 */
        dmac_tx_bf_add_ht_control_field(pst_hal_device, pst_tx_ctl, pst_tx_dscr_list_hdr, pst_txop_alg, pst_ppdu_feature);
    }

#ifdef _PRE_WLAN_CHIP_TEST
    DMAC_CHIP_TEST_CALL(dmac_test_sch_modify_txdscp_timestamp(&pst_ppdu_feature->us_tsf,
                        g_st_dmac_test_mng.s_ct_sch_lifetime_delay_ms));
    DMAC_CHIP_TEST_CALL(dmac_test_sch_set_long_nav_enable(pst_tx_dscr));
#endif

    /* 填写发送参数,只有ampdu可以只填写第一个描述符 */
    if (OAL_TRUE == pst_ppdu_feature->uc_ampdu_enable)
    {
        hal_tx_ucast_data_set_dscr(pst_hal_device, pst_tx_dscr, &st_txop_feature, pst_txop_alg, pst_ppdu_feature);
        uc_ppdu_cnt = 1;
    }
    else  /*MPDU每个描述都需要填写*/
    {
         OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_entry, pst_tx_dscr_list_hdr)
         {
            pst_dscr_temp = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);

            pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_dscr_temp->pst_skb_start_addr);

            /* 组播 广播数据帧调用hal_tx_umbcast_set_dscr接口填写描述符*/
            if (OAL_TRUE == MAC_GET_CB_IS_MCAST(pst_cb))
            {
                pst_txop_alg = &(pst_dmac_vap->st_tx_data_mcast);
                hal_tx_non_ucast_data_set_dscr(pst_hal_device, pst_dscr_temp, &st_txop_feature, pst_txop_alg, pst_ppdu_feature);

            }
            else
            {
                hal_tx_ucast_data_set_dscr(pst_hal_device, pst_dscr_temp, &st_txop_feature, pst_txop_alg, pst_ppdu_feature);
            }
         }

        uc_ppdu_cnt = MAC_GET_CB_MPDU_NUM(pst_tx_ctl);
        if (0 == uc_ppdu_cnt)
        {
            OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_tx_data::tid %d, uc_dscr_num is zero.}", mac_get_cb_tid(pst_cb));
        }
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    /* EAPOL帧，DHCP和ARP帧的共存保护 */
    pst_bt_status = &(pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status);
    if (pst_bt_status->bit_bt_on
#ifdef _PRE_WLAN_FEATURE_LTECOEX
        || pst_hal_device->ul_lte_coex_status
#endif
        )
    {
        OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_entry, pst_tx_dscr_list_hdr)
        {
            pst_dscr_temp = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
            pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_dscr_temp->pst_skb_start_addr);

            if (OAL_TRUE == MAC_GET_CB_IS_VIPFRAME(pst_cb))
            {
                uc_data_type = mac_get_data_type(pst_dscr_temp->pst_skb_start_addr);
                if(MAC_DATA_BUTT > uc_data_type)
                {
                    switch (uc_data_type)
                    {
                        case MAC_DATA_DHCP:
                        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_data:DHCP! len==%u.}", pst_cb->us_mpdu_bytes);
                        uc_coex_data_type = 1;
                        uc_coex_wl_time   = BTCOEX_PRIO_TIMEOUT_100MS; /* DHCP超时保护时间为100ms */
                        break;
                        case MAC_DATA_ARP_REQ:
                        case MAC_DATA_ARP_RSP:
                        uc_coex_data_type = 2;
                        uc_coex_wl_time   = BTCOEX_PRIO_TIMEOUT_60MS; /* arp超时保护时间为60ms */
                        break;
                        case MAC_DATA_EAPOL:

                        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_data:EAPOL! len==%u.}", pst_cb->us_mpdu_bytes);
                        uc_coex_data_type = 3;
                        uc_coex_wl_time   = BTCOEX_PRIO_TIMEOUT_100MS; /* EAPOL超时保护时间为100ms */
                        break;
                        default:
                        uc_coex_data_type = 0;
                    }

                    hal_set_btcoex_soc_gpreg0(uc_coex_data_type, BIT10 | BIT11 | BIT12, 10);   // 发送关键帧
                    hal_coex_sw_irq_set(BIT5);
                }

                /*为提高p2p配对成功率，在非BT电话场景下，保护EAPOL帧收发*/
                if ((uc_data_type == MAC_DATA_EAPOL) && !(pst_bt_status->bit_bt_sco))
                {
                    hal_set_btcoex_occupied_period(60000);//60ms
                }
                else if (MAC_DATA_EAPOL >= uc_data_type)
                {
                    /* 软件拉高priority */
                    dmac_btcoex_wlan_priority_set(pst_mac_device, 1, uc_coex_wl_time);
                }
            }
        }
    }
#endif

    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_TX_SET_DSCR);
    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_SET_DSCR);

    if (OAL_SWITCH_ON == oam_report_data_get_global_switch(OAM_OTA_FRAME_DIRECTION_TYPE_TX))
    {
        dmac_tx_dump_data(pst_hal_device, pst_tx_ctl, pst_tx_dscr_list_hdr);
    }

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    /* 常发模式根据标志位决定mac头的内容，随机情况下不改变mac头 */
    if (OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag)
    {
        pst_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_tx_dscr->pst_skb_start_addr);
        if(RF_PAYLOAD_ALL_ZERO == pst_dmac_vap->st_vap_base_info.bit_payload_flag)
        {
            OAL_MEMZERO(mac_get_cb_frame_hdr(pst_cb), OAL_SIZEOF(mac_ieee80211_frame_stru));
        }
        else if(RF_PAYLOAD_ALL_ONE == pst_dmac_vap->st_vap_base_info.bit_payload_flag)
        {
            oal_memset(mac_get_cb_frame_hdr(pst_cb), 0xFF, OAL_SIZEOF(mac_ieee80211_frame_stru));
        }
    }

#endif

    /* 将发送描述符链表插入发送描述符队列 */
    uc_ac = mac_get_cb_ac(pst_tx_ctl);
    dmac_tx_dscr_queue_add_dscr_list(pst_hal_device, HAL_AC_TO_Q_NUM(uc_ac), pst_tx_dscr_list_hdr, uc_ppdu_cnt);

#ifdef _PRE_WLAN_CHIP_TEST
    /* 适配成4地址 */
    DMAC_CHIP_TEST_CALL(dmac_test_set_addr4(pst_tx_dscr));
    DMAC_CHIP_TEST_CALL(dmac_test_set_dscr_software_retry(pst_hal_device, pst_tx_dscr));
    DMAC_CHIP_TEST_CALL(dmac_test_lpm_txopps_set_partial_aid(pst_dmac_vap, pst_dmac_user, DMAC_TEST_STUB_END));
    DMAC_CHIP_TEST_CALL(dmac_test_lpm_smps_set_rate(pst_tx_ctl,pst_txop_alg,DMAC_TEST_STUB_END));
	//DMAC_CHIP_TEST_CALL(dmac_test_always_tx(pst_hal_device, pst_tx_dscr));
#endif

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    /* 没有打开chip test,先放在外面 */
    if (OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag)
    {
         hal_rf_test_enable_al_tx(pst_hal_device, pst_tx_dscr);
    }
#endif /* #ifdef _PRE_WLAN_FEATURE_ALWAYS_TX */

#ifdef _PRE_DEBUG_MODE
    g_ast_tx_complete_stat[pst_hal_device->uc_mac_device_id].ul_tx_data_num += uc_ppdu_cnt;
    OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "ul_tx_data_num = %d", g_ast_tx_complete_stat[pst_hal_device->uc_mac_device_id].ul_tx_data_num);

    uc_tid = mac_get_cb_tid(pst_tx_ctl);
    pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid]);

    if ((pst_tx_dscr->bit_is_ampdu == 0) && (DMAC_TX_MODE_AGGR == pst_tid_queue->en_tx_mode))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_data::sending none_ampdu while ba is setup.}");
    }
    else if ((pst_tx_dscr->bit_is_ampdu == 1) && (DMAC_TX_MODE_NORMAL == pst_tid_queue->en_tx_mode))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_data::sending ampdu while ba is not setup.}");
    }

#endif

    /* 根据队列类型，将一个描述符链表的首地址，告知硬MAC */
    uc_ac = mac_get_cb_ac(pst_tx_ctl);

#ifdef _PRE_WLAN_FEATURE_DBAC
    if ((pst_hal_device->uc_current_chan_number != pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number) &&
         (MAC_VAP_STATE_INIT != pst_dmac_vap->st_vap_base_info.en_vap_state))
    {
        oal_uint8                       auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xff,0xff,0xff,0xff,0xff,0xff};

        OAM_ERROR_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "put tx_dscr in wrong channel. vap chan:%d, hal chan:%d. vap state:%d",
                                pst_dmac_vap->st_vap_base_info.st_channel.uc_chan_number,
                                pst_hal_device->uc_current_chan_number,
                                pst_dmac_vap->st_vap_base_info.en_vap_state);

        oam_report_80211_frame(auc_user_macaddr,
                            (oal_uint8*)mac_get_cb_frame_hdr(pst_tx_ctl),
                            MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl),
                            (oal_uint8*)oal_netbuf_payload(pst_tx_dscr->pst_skb_start_addr),
                            MAC_GET_CB_MPDU_LEN(pst_tx_ctl),
                            OAM_OTA_FRAME_DIRECTION_TYPE_TX);
    }
#endif

    /* DTS2015052706839:为防止管理帧进入数据帧处理流程后，高优先级队列Overrun */
    uc_q_num = HAL_AC_TO_Q_NUM(uc_ac);

    if (OAL_GET_THRUPUT_BYPASS_ENABLE(OAL_TX_HAL_HARDWARE_BYPASS))
    {
        dmac_post_soft_tx_complete_event(pst_hal_device, pst_tx_dscr, MAC_GET_CB_MPDU_NUM(pst_tx_ctl));
        return OAL_SUCC;
    }

    /* 读取发送队列状态寄存器*/
    hal_get_tx_q_status(pst_hal_device, &ul_tx_q_status, uc_q_num);

    /* 状态寄存器非0，表示硬件发送队列FIFO满 */
    if ((HAL_TX_QUEUE_HI == uc_q_num) && (0 != ul_tx_q_status))
    {
        OAL_MEM_TRACE(pst_tx_dscr, OAL_FALSE);
        /* 挂到最后一个写入硬件的描述符队列队尾 */
        pst_last_dscr_entry = pst_hal_device->ast_tx_dscr_queue[uc_q_num].st_header.pst_prev->pst_prev;
        pst_last_dscr       = OAL_DLIST_GET_ENTRY(pst_last_dscr_entry, hal_tx_dscr_stru, st_entry);

        hal_tx_ctrl_dscr_link(pst_hal_device, pst_last_dscr, pst_tx_dscr);
        if (pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt > 10)
        {
            OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "dmac_tx_data::q_num = [%d], ul_tx_q_status = [%d], ppdu_cnt[%d], tid num [%d]",
                             uc_q_num, ul_tx_q_status, pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt, mac_get_cb_tid(pst_tx_ctl));
        }
    }
    else
    {

        OAL_MEM_TRACE(pst_tx_dscr, OAL_FALSE);
        /* 写入硬件 */
        hal_tx_put_dscr(pst_hal_device, uc_q_num, pst_tx_dscr);
    }

    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_TX_PUT_DSCR);
    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_PUT_DSCR);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_need_enqueue_tid
 功能描述  : 判断数据帧是否需要入发送TID缓存队列
 输入参数  : pst_hal_device: HAL向DMAC提供的device指针
             pst_tid_queue : TID缓存队列指针
             uc_ac         : 接入类别(Access Category)
 输出参数  : 无
 返 回 值  : OAL_TRUE : 需要入队
             OAL_FALSE: 无需入队
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月21日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  dmac_tx_need_enqueue_tid(
                hal_to_dmac_device_stru *pst_hal_device,
#ifdef _PRE_WLAN_FEATURE_DBAC
                mac_vap_stru            *pst_mac_vap,
#endif
                dmac_tid_stru           *pst_tid_queue,
                oal_uint8                uc_q_num)
{
    mac_device_stru   *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_need_enqueue_tid::pst_mac_device null.}");
        return OAL_TRUE;
    }

    /* (1)如果硬件队列达到发送上限
       (2)或者对应的TID缓存队列不为空，
       (3)或者TID被暂停
       (4)wlan过来的且个数大于1?
       (5)ampdu聚合                      */
       /* DBAC运行后，若VAP暂停则需要入队 */
    if ((DMAC_TX_MODE_NORMAL != pst_tid_queue->en_tx_mode) ||
        (pst_tid_queue->uc_is_paused > 0) ||
        ((0 != pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt) && (HAL_TX_QUEUE_HI != uc_q_num)) ||
#ifdef _PRE_WLAN_FEATURE_DBAC
        (OAL_TRUE == mac_need_enqueue_tid_for_dbac(pst_mac_device, pst_mac_vap)) ||
#endif
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        (OAL_FALSE == oal_dlist_is_empty(&pst_tid_queue->st_retry_q)) ||
        (OAL_FALSE == oal_netbuf_list_empty(&pst_tid_queue->st_buff_head)))
#else
        (OAL_FALSE == oal_dlist_is_empty(&pst_tid_queue->st_hdr)))
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    {
        return OAL_TRUE;
    }

    /* 扫描期间，主要是背景扫描期间，数据帧发送需要先进入tid队列，防止5g发11b */
    if (MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)
    {
        if (uc_q_num < HAL_TX_QUEUE_HI)
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}


/*****************************************************************************
 函 数 名  : dmac_tid_tx_queue_enqueue
 功能描述  : 将一个MPDU或多个MPDU加入用户的TID缓存队列
 输入参数  : pst_tid_queue: 发送tid缓存队列指针
             pst_netbuf   : netbuf指针
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
OAL_STATIC OAL_INLINE oal_uint32  dmac_tid_tx_queue_enqueue(
                mac_device_stru    *pst_device,
                mac_vap_stru       *pst_vap,
                dmac_tid_stru      *pst_tid_queue,
                oal_uint8           uc_mpdu_num,
                oal_netbuf_stru    *pst_netbuf)
#else
OAL_STATIC OAL_INLINE oal_uint32  dmac_tid_tx_queue_enqueue(
                mac_device_stru    *pst_device,
                mac_vap_stru       *pst_vap,
                dmac_tid_stru      *pst_tid_queue,
                hal_tx_dscr_stru   *pst_tx_dscr,
                oal_uint8           uc_mpdu_num,
                oal_netbuf_stru    *pst_netbuf)
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
{
    oal_time_us_stru            st_timestamp_us = {0, 0};
    oal_netbuf_stru            *pst_netbuf_tmp;
    mac_tx_ctl_stru            *pst_cb;
#ifdef _PRE_WLAN_FEATURE_DBAC
    oal_uint32                  ul_ret;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    dmac_tid_stats_stru   *pst_tid_stats;
    pst_tid_stats = pst_tid_queue->pst_tid_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid_stats))
    {
        OAM_ERROR_LOG4(pst_tid_queue->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue::tid_stats is null. tid:%d,is paused:%d,mpdu_num:%d,user idx:%d}",
                       pst_tid_queue->uc_tid,
                       pst_tid_queue->uc_is_paused,
                       pst_tid_queue->us_mpdu_num,
                       pst_tid_queue->us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }
#endif
#endif

    /* 更新device结构体下的统计信息 */
    if (OAL_UNLIKELY((pst_device->us_total_mpdu_num + 1) > WLAN_TID_MPDU_NUM_LIMIT))
    {
        OAM_WARNING_LOG0(pst_vap->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue::us_total_mpdu_num exceed.}");
        DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_enqueue_full_cnt, uc_mpdu_num);

        return OAL_FAIL;
    }

    pst_netbuf_tmp = pst_netbuf;
    while (OAL_PTR_NULL != pst_netbuf_tmp)
    {
        pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf_tmp);
        /* VO/VI 队列需要打时间戳，算法需要*/
        if ((WLAN_WME_AC_VI == mac_get_cb_ac(pst_cb)) || (WLAN_WME_AC_VO == mac_get_cb_ac(pst_cb)))
        {
            /*只需要获取一次时间戳，所有的netbuf使用同一个时间戳*/
            if ((0 == st_timestamp_us.i_sec) && (0 ==st_timestamp_us.i_usec))
            {
                dmac_timestamp_get(&st_timestamp_us);
            }

            MAC_GET_CB_TIMESTAMP(pst_cb).i_sec  = st_timestamp_us.i_sec;
            MAC_GET_CB_TIMESTAMP(pst_cb).i_usec = st_timestamp_us.i_usec;
        }
        pst_netbuf_tmp = oal_get_netbuf_next(pst_netbuf_tmp);
    }

    pst_device->us_total_mpdu_num += uc_mpdu_num;
    pst_tid_queue->us_mpdu_num += uc_mpdu_num;
    DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_enqueue_total_cnt, uc_mpdu_num);
    pst_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id] += uc_mpdu_num;
    pst_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)] += uc_mpdu_num;

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    dmac_alg_flowctl_backp_notify(pst_vap, pst_device->us_total_mpdu_num, pst_device->aus_ac_mpdu_num);
#endif

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    dmac_tx_queue_mpdu(pst_netbuf, &pst_tid_queue->st_buff_head);
#else
    OAL_MEM_TRACE(pst_tx_dscr, OAL_FALSE);
    oal_dlist_add_tail(&pst_tx_dscr->st_entry, &pst_tid_queue->st_hdr);
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

#ifdef _PRE_WLAN_FEATURE_DBAC
    ul_ret = dmac_alg_enqueue_tid_notify(pst_vap, pst_tid_queue, uc_mpdu_num);
    if (OAL_UNLIKELY(OAL_SUCC !=  ul_ret))
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_enqueue::dmac_alg_enqueue_tid_notify failed[%d].}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_al_tx_set_mpdu_param
 功能描述  : 为了解决02常发发送大数据的问题，重新设置一下mpdu参数
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void  dmac_al_tx_set_mpdu_param (mac_vap_stru *pst_mac_vap, oal_uint16 us_payload_len, hal_tx_mpdu_stru *pst_mpdu)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    if(OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)
    {
        pst_mpdu->ast_msdu_addr[0].us_msdu0_len = us_payload_len;
    }
#endif
#endif

}
/*****************************************************************************
 函 数 名  : dmac_is_al_tx
 功能描述  : 判断是否常发模式
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月6日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_bool_enum_uint8  dmac_is_al_tx (dmac_vap_stru *pst_dmac_vap)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

        /* 常发下返回状态OK */
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
        if((OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag))
        {
            return OAL_TRUE;
        }
#endif

#endif
        return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_is_vap_state_ok
 功能描述  : 判断vap状态是否正常，决定是否需要中止发送
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月6日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_bool_enum_uint8  dmac_is_vap_state_ok (dmac_vap_stru *pst_dmac_vap)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 针对上下状态不同步的问题，增加对damc状态的异常检查 问题单: DTS2015030907649 */
    if (OAL_UNLIKELY(!((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state) ||
    (MAC_VAP_STATE_PAUSE == pst_dmac_vap->st_vap_base_info.en_vap_state))))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
        "{dmac_tx_process_data_event:vap state[%d] != MAC_VAP_STATE_{UP|PAUSE}!}\r\n",
        pst_dmac_vap->st_vap_base_info.en_vap_state);
        return OAL_FALSE;
    }
#endif
    return OAL_TRUE;

}

/*****************************************************************************
 函 数 名  : dmac_is_user_state_ok
 功能描述  : 判断user状态是否正常，决定是否需要中止发送
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月6日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_bool_enum_uint8  dmac_is_user_state_ok (dmac_user_stru *pst_dmac_user)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if(MAC_USER_STATE_BUTT == pst_dmac_user->st_user_base_info.en_user_asoc_state)
    {
        /*data frames stored in the hmac/dmac pipeline when dmac offload*/
        OAM_WARNING_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_TX,
                         "{dmac_is_user_state_ok::user(id[%d]) state is MAC_USER_STATE_BUTT! ", pst_dmac_user->st_user_base_info.us_assoc_id);
        return OAL_FALSE;
    }
#endif
    return OAL_TRUE;
}
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
hal_tx_dscr_stru* dmac_tx_dscr_alloc(hal_to_dmac_device_stru   *pst_hal_device,
                                                        dmac_vap_stru *pst_dmac_vap,
                                                      oal_netbuf_stru *pst_netbuf)
{
    oal_uint32                 ul_ret;
    mac_tx_ctl_stru           *pst_tx_ctl_first;
    hal_tx_mpdu_stru           st_mpdu;
    oal_uint16                 us_tx_dscr_len;
    hal_tx_dscr_stru          *pst_tx_dscr;
    mac_device_stru           *pst_mac_device;
    oal_uint8                  uc_ac;
    oal_uint8                  uc_q_num;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    oal_mem_pool_id_enum_uint8 en_mem_poo_id;
#endif

    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_dscr_alloc::tx pkt is dropped, pst_mac_device null.}");
        return OAL_PTR_NULL;
    }

    pst_tx_ctl_first  = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    if(OAL_PTR_NULL == pst_tx_ctl_first)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_dscr_alloc::tx pkt is dropped, tx ctl null.}");
        return OAL_PTR_NULL;
    }

    uc_ac       = mac_get_cb_ac(pst_tx_ctl_first);
    uc_q_num    = HAL_AC_TO_Q_NUM(uc_ac);

    /* 获取MPDU发送参数 */
    ul_ret = dmac_tx_get_mpdu_params(pst_netbuf, pst_tx_ctl_first, &st_mpdu);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_dscr_alloc::tx pkt is dropped, dmac_tx_get_mpdu_params failed[%d].", ul_ret);
        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);

        return OAL_PTR_NULL;
    }

    dmac_al_tx_set_mpdu_param(&pst_dmac_vap->st_vap_base_info, MAC_GET_CB_MPDU_BYTES(pst_tx_ctl_first), &st_mpdu);

    //OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_GET_SET_MPDU_PARAMS);

    /*为减少开销，直接指定发送描述符大小，不使用hal_tx_get_size_dscr函数获取*/
    //us_tx_dscr_len = (MAC_GET_CB_NETBUF_NUM(pst_tx_ctl_first) == 1) ? WLAN_MEM_SHARED_TX_DSCR_SIZE1 : WLAN_MEM_SHARED_TX_DSCR_SIZE2;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    if (MAC_GET_CB_NETBUF_NUM(pst_tx_ctl_first) == 1)
    {
        us_tx_dscr_len = WLAN_MEM_SHARED_TX_DSCR_SIZE1;
        en_mem_poo_id = OAL_MEM_POOL_ID_TX_DSCR_1;
    }
    else
    {
        us_tx_dscr_len = WLAN_MEM_SHARED_TX_DSCR_SIZE2;
        en_mem_poo_id = OAL_MEM_POOL_ID_TX_DSCR_2;
    }

    /* 申请发送描述符内存 */
    pst_tx_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(en_mem_poo_id, us_tx_dscr_len, OAL_FALSE);
#else
    us_tx_dscr_len = (MAC_GET_CB_NETBUF_NUM(pst_tx_ctl_first) == 1) ? WLAN_MEM_SHARED_TX_DSCR_SIZE1 : WLAN_MEM_SHARED_TX_DSCR_SIZE2;
    pst_tx_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_DSCR, us_tx_dscr_len, OAL_FALSE);
#endif
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tx_dscr))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_dscr_alloc::tx pkt is dropped, pst_tx_dscr alloc failed.}");

        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);
#ifdef _PRE_WLAN_DFT_STAT
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        dmac_dft_print_mac_phy_rf(pst_mac_device);
#endif
#endif
        return OAL_PTR_NULL;
    }

    OAL_MEM_TRACE(pst_tx_dscr, OAL_FALSE);
    OAL_MEMZERO(pst_tx_dscr, us_tx_dscr_len);

    /* 填写mpdu长度 包括帧头 */
    pst_tx_dscr->us_original_mpdu_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctl_first) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl_first);
    pst_tx_dscr->bit_is_retried = OAL_FALSE;
    pst_tx_dscr->bit_is_first   = 0;

    /* 填写描述符ac */
    pst_tx_dscr->uc_q_num = uc_q_num;

    hal_tx_fill_basic_ctrl_dscr(pst_hal_device, pst_tx_dscr, &st_mpdu);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == g_l_proxysta_feature)
    {
        if((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta)
        && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
        {
            /* bit_tx_hal_vap_id 为真正的Proxy STA的hal vap id,Proxy STA的hal vap id取值范围为16~31,*/
            /* 因为只有四位，故减去16的偏移量,且用1~15表示Proxy STA的16~31，此位非0就是Proxy STA */
            pst_tx_dscr->bit_tx_hal_vap_id = (pst_dmac_vap->pst_hal_vap->uc_vap_id - HAL_PROXY_STA_START_IDX + 1);
        }
    }
#endif

    return pst_tx_dscr;
}

#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

/*****************************************************************************
 函 数 名  : dmac_judge_forbid_rts
 功能描述  : 判断若需要强制关闭RTS, 则将描述符相应的RTS字段置为FALSE
 输入参数  : pst_dmac_user  : DMAC USER指针
             pst_txop_alg   : 描述符参数指针
 输出参数  : pst_txop_alg
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月30日
    作    者   : liwenjun 00330043
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_judge_forbid_rts(dmac_user_stru *pst_dmac_user, hal_tx_txop_alg_stru *pst_txop_alg)
{
    oal_uint8   uc_rate_rank;

    /* 在开启RTS存在兼容性问题时, 强制关闭RTS */
    if (OAL_TRUE == pst_dmac_user->bit_forbid_rts)
    {
        for (uc_rate_rank = 0; uc_rate_rank < HAL_TX_RATE_MAX_NUM; uc_rate_rank++)
        {
            pst_txop_alg->ast_per_rate[uc_rate_rank].rate_bit_stru.bit_rts_cts_enable = OAL_FALSE;
        }
    }
}

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
/*****************************************************************************
 函 数 名  : dmac_frame_is_null_data
 功能描述  : 该帧是否为NULL DATA帧
 输入参数  : pst_net_buf: 帧指针
 输出参数  : 无
 返 回 值  : OAL_TRUE 或 OAL_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月14日
    作    者   : zhangyu
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_frame_is_null_data(oal_netbuf_stru *pst_net_buf)
{
    mac_ieee80211_frame_stru       *pst_mac_header;
    oal_uint8                       uc_frame_type;
    oal_uint8                       uc_frame_subtype;

    pst_mac_header  = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf);
    uc_frame_type    = mac_frame_get_type_value((oal_uint8 *)pst_mac_header);
    uc_frame_subtype = mac_frame_get_subtype_value((oal_uint8 *)pst_mac_header);

    if ((WLAN_DATA_BASICTYPE == uc_frame_type)
         && ((WLAN_NULL_FRAME == uc_frame_subtype) || (WLAN_QOS_NULL_FRAME == uc_frame_subtype)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_tx_process_data
 功能描述  : 接收从HMAC传过来的数据帧，并进行发送前的处理(传过来的MPDU属于
             同一个用户，并且TID相同)
 输入参数  : pst_hal_device: HAL向DMAC提供的device指针
             pst_dmac_vap  : DMAC VAP指针
             pst_netbuf    : netbuf链表指针(其中保存的MPDU属于同一个用户下的同一个TID)
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月21日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_uint32  dmac_tx_process_data(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_tx_ctl_stru             *pst_tx_ctl_first;
    dmac_user_stru              *pst_dmac_user;
    dmac_tid_stru               *pst_tid_queue;
    oal_uint32                   ul_ret = OAL_SUCC;
    hal_tx_dscr_stru            *pst_tx_dscr = OAL_PTR_NULL;
    oal_dlist_head_stru          st_tx_dscr_list_hdr;
#ifndef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_uint16                   us_tx_dscr_len = 0;
    hal_tx_mpdu_stru             st_mpdu;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    oal_uint8                    uc_mpdu_num;
    oal_bool_enum_uint8          en_is_pkt_need_buff;  /* mpdu是否需要入节能队列的标志 */
    hal_tx_ppdu_feature_stru     st_ppdu_feature;
    hal_tx_txop_alg_stru        *pst_txop_alg = OAL_PTR_NULL;
    mac_device_stru             *pst_mac_device;
    oal_uint8                    uc_ac;
    oal_uint8                    uc_q_num;

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_DATA);

    /* 获取netbuf链中第一个netbuf的CB */
    pst_tx_ctl_first  = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    if(OAL_PTR_NULL == pst_tx_ctl_first)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{oal_netbuf_cb::skb buf poiter null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    uc_mpdu_num = 1;

    /* 获取DMAC模块用户结构体 */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl_first));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::pst_dmac_user null.user idx [%d]}", MAC_GET_CB_TX_USER_IDX(pst_tx_ctl_first));
        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if(OAL_TRUE != dmac_is_al_tx(pst_dmac_vap))
    {
        if(OAL_TRUE != dmac_is_vap_state_ok(pst_dmac_vap)
            || OAL_TRUE != dmac_is_user_state_ok(pst_dmac_user))
        {
            dmac_tx_excp_free_netbuf(pst_netbuf);
            return OAL_SUCC;
        }
    }

    /* 非活跃用户处理 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* DTS2015030700626 判断用户是否存在，异常情况下用户可能已经被删除了*/
    if(0 != MAC_GET_CB_TX_USER_IDX(pst_tx_ctl_first))
    {
        if(0 != g_st_mac_res.st_hash_res.puc_user_cnt[MAC_GET_CB_TX_USER_IDX(pst_tx_ctl_first) - 1])
        {
            if (OAL_UNLIKELY(OAL_FALSE == pst_dmac_user->bit_active_user))
            {
                ul_ret = dmac_user_tx_inactive_user_handler(pst_dmac_user);
                if (OAL_SUCC != ul_ret)
                {
                    OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_process_data::dmac_user_tx_inactive_user_handler failed[%d].", ul_ret);
                    OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);
                    return ul_ret;
                }
            }
        }
    }
#else
    if (OAL_UNLIKELY(OAL_FALSE == pst_dmac_user->bit_active_user))
    {
        ul_ret = dmac_user_tx_inactive_user_handler(pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_process_data::dmac_user_tx_inactive_user_handler failed[%d].", ul_ret);
            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);
            return ul_ret;
        }
    }
#endif

    /* 只有发送分片报文才会循环 */
#ifdef _PRE_WLAN_FEATURE_UAPSD
    if(mac_vap_get_uapsd_en(&pst_dmac_vap->st_vap_base_info)
        &&(OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctl_first))
        &&(OAL_FALSE == MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctl_first))
        &&(MAC_USR_UAPSD_AC_CAN_DELIVERY(mac_get_cb_ac(pst_tx_ctl_first), pst_dmac_user)))
    {
        return dmac_uapsd_tx_enqueue(pst_dmac_vap, pst_dmac_user, pst_netbuf);
    }
#endif

    /* 判断要被发送的帧是否需要入节能缓存队列,如果需要，则入队，返回 */
    if (0 != pst_dmac_vap->uc_ps_user_num)/* 性能优化 */
    {
        en_is_pkt_need_buff = dmac_psm_pkt_need_buff(pst_dmac_vap, pst_dmac_user, pst_netbuf);
        if (OAL_TRUE == en_is_pkt_need_buff)
        {
            return dmac_psm_enqueue(pst_dmac_vap, pst_dmac_user, pst_netbuf);
        }
    }
    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_tx_process_data::pst_mac_device[%d] null!}", pst_hal_device->uc_mac_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_INACTIVE_USER_HDL);

    /* 调用拥塞控制的钩子 */
    ul_ret = dmac_alg_downlink_flowctl_notify(&pst_dmac_vap->st_vap_base_info,
                                     &pst_dmac_user->st_user_base_info,
                                     pst_netbuf);

    /* 如果拥塞控制算法判断为丢包*/
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_alg_process_dropped, 1);
        OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                      "{dmac_tx_process_data:: alg_flowctl process return [%d], dev_mpdu_num = %d}", ul_ret, pst_mac_device->us_total_mpdu_num);
        OAM_INFO_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data:: be = %d, bk = %d, vi = %d, vo = %d}",
                      pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_BE],
                      pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_BK],
                      pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_VI],
                      pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_VO]);
#ifdef _PRE_WLAN_PERFORM_STAT
        dmac_stat_tid_per(&(pst_dmac_user->st_user_base_info), mac_get_cb_tid(pst_tx_ctl_first), 1, 1, DMAC_STAT_PER_BUFF_OVERFLOW);
#endif
        return ul_ret;
    }

#ifdef _PRE_WLAN_PERFORM_STAT
    dmac_stat_tid_per(&(pst_dmac_user->st_user_base_info), mac_get_cb_tid(pst_tx_ctl_first), 1, 0, DMAC_STAT_PER_BUFF_OVERFLOW);
#endif

    /* 初始化发送描述符单项链表 */
    oal_dlist_init_head(&st_tx_dscr_list_hdr);

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_FLOWCTRL);

    uc_ac       = mac_get_cb_ac(pst_tx_ctl_first);
    uc_q_num    = HAL_AC_TO_Q_NUM(uc_ac);

#ifndef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    /* 获取MPDU发送参数 */
    ul_ret = dmac_tx_get_mpdu_params(pst_netbuf, pst_tx_ctl_first, &st_mpdu);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::dmac_tx_get_mpdu_params failed[%d].", ul_ret);

        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);

        return OAL_FAIL;
    }

    dmac_al_tx_set_mpdu_param(&pst_dmac_vap->st_vap_base_info, MAC_GET_CB_MPDU_BYTES(pst_tx_ctl_first), &st_mpdu);

    //OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_GET_SET_MPDU_PARAMS);

    /*为减少开销，直接指定发送描述符大小，不使用hal_tx_get_size_dscr函数获取*/
    us_tx_dscr_len = (MAC_GET_CB_NETBUF_NUM(pst_tx_ctl_first) == 1) ? WLAN_MEM_SHARED_TX_DSCR_SIZE1 : WLAN_MEM_SHARED_TX_DSCR_SIZE2;

    /* 申请发送描述符内存 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    pst_tx_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_TX_DSCR_1, us_tx_dscr_len, OAL_FALSE);
#else
    pst_tx_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_DSCR, us_tx_dscr_len, OAL_FALSE);
#endif
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tx_dscr))
    {
        OAM_ERROR_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
        "{dmac_tx_process_data::pst_tx_dscr alloc failed, us_tx_dscr_len[%d], NETBUF_NUM[%d], amsdu capable[%d].}",
        us_tx_dscr_len, MAC_GET_CB_NETBUF_NUM(pst_tx_ctl_first), pst_tx_ctl_first->en_is_amsdu);

        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);
#ifdef _PRE_WLAN_DFT_STAT
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        dmac_dft_print_mac_phy_rf(pst_mac_device);
#endif
#endif
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_MEM_TRACE(pst_tx_dscr, OAL_FALSE);
    OAL_MEMZERO(pst_tx_dscr, us_tx_dscr_len);
    /* 填写mpdu长度 包括帧头 */
    pst_tx_dscr->us_original_mpdu_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctl_first) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl_first);
    pst_tx_dscr->bit_is_retried = OAL_FALSE;
    pst_tx_dscr->bit_is_first   = 0;

    /* 填写描述符ac */
    pst_tx_dscr->uc_q_num = uc_q_num;

    hal_tx_fill_basic_ctrl_dscr(pst_hal_device, pst_tx_dscr, &st_mpdu);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == g_l_proxysta_feature)
    {
        if((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta)
        && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
        {
            /* bit_tx_hal_vap_id 为真正的Proxy STA的hal vap id,Proxy STA的hal vap id取值范围为16~31,*/
            /* 因为只有四位，故减去16的偏移量,且用1~15表示Proxy STA的16~31，此位非0就是Proxy STA */
            pst_tx_dscr->bit_tx_hal_vap_id = (pst_dmac_vap->pst_hal_vap->uc_vap_id - HAL_PROXY_STA_START_IDX + 1);
        }
    }
#endif
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_FILL_DSCR);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 对cb字段的tid进行检查 */
    mac_check_cb_tid(pst_tx_ctl_first);
#endif

    /* 获取用户的特定TID队列 */
    pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[mac_get_cb_tid(pst_tx_ctl_first)]);

    /* 如果硬件队列满或者对应的TID缓存队列不为空，则将本次将要发送的MPDU入TID缓存队列 */
#ifdef _PRE_WLAN_FEATURE_DBAC
    if (OAL_TRUE == dmac_tx_need_enqueue_tid(pst_hal_device, &pst_dmac_vap->st_vap_base_info, pst_tid_queue, uc_q_num))
#else
    if (OAL_TRUE == dmac_tx_need_enqueue_tid(pst_hal_device, pst_tid_queue, uc_q_num))
#endif
    {
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
        /* 常发模式下不入队 */
        if (OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag)
        {
            return OAL_SUCC;
        }
#endif
        pst_tid_queue->uc_vap_id = pst_dmac_user->st_user_base_info.uc_vap_id;
    #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        ul_ret = dmac_tid_tx_queue_enqueue(pst_mac_device, &pst_dmac_vap->st_vap_base_info, pst_tid_queue, uc_mpdu_num, pst_netbuf);
    #else
        ul_ret = dmac_tid_tx_queue_enqueue(pst_mac_device, &pst_dmac_vap->st_vap_base_info, pst_tid_queue, pst_tx_dscr, uc_mpdu_num, pst_netbuf);
    #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
        if (OAL_LIKELY(OAL_SUCC == ul_ret))
        {
            dmac_alg_tid_update_notify(pst_tid_queue);
        }
        else
        {
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
            pst_dmac_vap->st_vap_base_info.st_vap_stats.ul_tx_dropped_packets += MAC_GET_CB_NETBUF_NUM(pst_tx_ctl_first);
#endif
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::dmac_tid_tx_queue_enqueue fail.}");
        #ifndef _PRE_WLAN_FEATURE_TX_DSCR_OPT
            OAL_MEM_FREE((oal_void *)pst_tx_dscr, OAL_TRUE);
        #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

            /* Amsdu场景下必须释放netbuf list否则会内存泄露 */
            dmac_tx_excp_free_netbuf(pst_netbuf);
        }

        OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_TID_ENQUEUE);

#if 0  /* mayuan */
        OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::uc_ppdu_cnt = %d and pst_tid_queue->uc_is_paused = %d.}",
                    pst_hal_device->ast_tx_dscr_queue[pst_tx_dscr->uc_q_num].uc_ppdu_cnt,
                    pst_tid_queue->c_is_paused);
#endif

#ifdef _PRE_WIFI_DMT
        /* AMPDU聚合由软件硬件条件判断，需要增加聚合数来模拟聚合条件开关 */
        if ((1 >= pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt) && (0 == pst_tid_queue->uc_is_paused)
        && (pst_tid_queue->us_mpdu_num >= witp_dmt_get_ampdu_aggr_num()))
#else
        if ((1 >= pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt) && (0 == pst_tid_queue->uc_is_paused))
#endif
        {
            dmac_tx_complete_schedule(pst_hal_device, mac_get_cb_ac(pst_tx_ctl_first));
        }

        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    pst_tx_dscr = dmac_tx_dscr_alloc(pst_hal_device, pst_dmac_vap, pst_netbuf);
    if (OAL_PTR_NULL == pst_tx_dscr)
    {
        if (OAL_FALSE == dmac_frame_is_null_data(pst_netbuf))
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::alloc tx dscr failed, pkt need enqueue tid queue.}");
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
            if (OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag)
            {
                /* 常发模式下不入队 */
                return OAL_SUCC;
            }
#endif
            pst_tid_queue->uc_vap_id = pst_dmac_user->st_user_base_info.uc_vap_id;

            ul_ret = dmac_tid_tx_queue_enqueue(pst_mac_device, &pst_dmac_vap->st_vap_base_info, pst_tid_queue, uc_mpdu_num, pst_netbuf);
            if (OAL_LIKELY(OAL_SUCC == ul_ret))
            {
                dmac_alg_tid_update_notify(pst_tid_queue);
            }
            else
            {
                OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::enqueue tid queue fail, pkt is dropped.}");
                /* Amsdu场景下必须释放netbuf list否则会内存泄露 */
                dmac_tx_excp_free_netbuf(pst_netbuf);
            }

            OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_TID_ENQUEUE);
            return OAL_SUCC;
        }

        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::pkt is dropped, alloc tx dscr failed.}");
        return OAL_FAIL;
    }
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

    /*如果硬件处于复位中，不发送*/
    if((OAL_PTR_NULL != pst_mac_device) && (OAL_TRUE == MAC_DEV_IS_RESET_IN_PROGRESS(pst_mac_device)))
    {
       OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::MAC_DEV_IS_RESET_IN_PROGRESS.}");

       OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);

       OAL_MEM_FREE((oal_void *)pst_tx_dscr, OAL_TRUE);
       return OAL_ERR_CODE_RESET_INPROGRESS;
    }

    /* 将同一个需要发送的描述符加入描述符链表 */
    oal_dlist_add_tail(&pst_tx_dscr->st_entry, &st_tx_dscr_list_hdr);

    /* 单播帧描述符中的字段要置空 */
    hal_tx_ctrl_dscr_unlink(pst_hal_device, pst_tx_dscr);

    /* 初始化ppdu发送参数 */
    dmac_tx_init_ppdu_feature(pst_dmac_vap, pst_dmac_user, 1, &st_ppdu_feature);
    dmac_tx_update_ppdu_feature(pst_netbuf, &st_ppdu_feature);

    MAC_GET_CB_MPDU_NUM(pst_tx_ctl_first) = 1;

    /* 获取TXOP算法发送参数 */
    dmac_tx_get_txop_alg_params(pst_dmac_vap, pst_dmac_user, pst_tx_ctl_first, &pst_txop_alg);
    if (OAL_PTR_NULL == pst_txop_alg)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data::pst_txop_alg null.}");
        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, tx_abnormal_mpdu_dropped, 1);

        OAL_MEM_FREE((oal_void *)pst_tx_dscr, OAL_TRUE);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_PROT_NO != pst_dmac_vap->st_vap_base_info.st_protection.en_protection_mode)
    {
        /*保护模式特性更新发送参数*/
        dmac_tx_update_protection_txop_alg(pst_dmac_vap, pst_txop_alg, OAL_FALSE, pst_tx_ctl_first->en_ismcast);
    }

    /* 判断是否强制关闭RTS */
    dmac_judge_forbid_rts(pst_dmac_user, pst_txop_alg);

    /* 2040共存特性更新带宽模式 */
    /* dmac_tx_update_bandwidth_mode(pst_dmac_vap, pst_dmac_user, pst_txop_alg); */

    dmac_save_frag_seq(pst_dmac_user, pst_tx_ctl_first);
    dmac_tx_seqnum_set(pst_dmac_user, pst_tx_ctl_first);

#ifdef _PRE_WLAN_DFT_STAT

    /* 不是以太网来的不统计 */
    if (FRW_EVENT_TYPE_HOST_DRX == MAC_GET_CB_EVENT_TYPE(pst_tx_ctl_first))
    {
        DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_tx_pkts,
                                    MAC_GET_CB_NETBUF_NUM(pst_tx_ctl_first));
        DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_tx_bytes,
                                    MAC_GET_CB_MPDU_BYTES(pst_tx_ctl_first));
    }

#endif

    /* 正常发送流程 */
    dmac_tx_data(pst_dmac_vap, pst_dmac_user, pst_tx_ctl_first, &st_tx_dscr_list_hdr, &st_ppdu_feature, pst_txop_alg);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_process_data_event
 功能描述  : DMAC模块处理HOST_DRX、WLAN_DTX事件入口函数,从hmac抛过来的事件内容有
             两种情况:(1)一个MPDU包含一个MSDU(2)一个MPDU包含一个AMSDU
 输入参数  : pst_event_mem: 事件结构体内存指针
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_process_data_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru            *pst_event;
    frw_event_hdr_stru        *pst_event_hdr;
    hal_to_dmac_device_stru   *pst_hal_device;
    dmac_vap_stru             *pst_dmac_vap;
    dmac_tx_event_stru        *pst_tx_event;
    oal_netbuf_stru           *pst_netbuf;
    mac_tx_ctl_stru           *pst_tx_ctl;
    oal_netbuf_stru           *pst_netbuf_next;
    oal_uint32                 ul_ret;
    oal_uint8                  uc_data_type;

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_START);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_process_data_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &pst_event->st_event_hdr;
    pst_tx_event  = (dmac_tx_event_stru *)pst_event->auc_event_data;

    /* 获取vap结构信息 */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data_event::mac_res_get_dmac_vap fail.vap_id = %d}",pst_event_hdr->uc_vap_id);
        dmac_tx_excp_free_netbuf(pst_tx_event->pst_netbuf);
        OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, tx_abnormal_mpdu_dropped, 1);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_dmac_vap->pst_hal_device;

    /* 获取device结构信息 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data_event::pst_hal_device null.}");

        dmac_tx_excp_free_netbuf(pst_tx_event->pst_netbuf);

        OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, tx_abnormal_mpdu_dropped, 1);
        return OAL_SUCC;
    }

    pst_netbuf = pst_tx_event->pst_netbuf;

    /* 循环处理分片报文 */
    while (pst_netbuf != OAL_PTR_NULL)
    {
        pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
        /* 排除amsdu的情况amsdu不进行循环，分片报文每个报文的next必须为NULL */
        if (OAL_TRUE != mac_get_cb_is_amsdu(pst_tx_ctl))
        {
            pst_netbuf_next = oal_get_netbuf_next(pst_netbuf);
            oal_set_netbuf_next(pst_netbuf, OAL_PTR_NULL);
        }
        else
        {
            pst_netbuf_next = OAL_PTR_NULL;
        }

        /* 漫游状态时，强制发送该数据帧 */
#ifdef _PRE_WLAN_FEATURE_ROAM
        if (MAC_VAP_STATE_ROAMING == pst_dmac_vap->st_vap_base_info.en_vap_state)
        {
            OAM_WARNING_LOG2(0, OAM_SF_TX, "{dmac_tx_process_data_event::dmac_tx_process_data statel[%d] len[%d].}", pst_dmac_vap->st_vap_base_info.en_vap_state, pst_tx_event->us_frame_len);
            ul_ret = dmac_tx_force(pst_dmac_vap, pst_netbuf, pst_tx_event->us_frame_len, 0);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG2(0, OAM_SF_TX, "{dmac_tx_process_data_event::dmac_tx_force [roam] len[%d] fail[%lu]}", pst_tx_event->us_frame_len, ul_ret);
                dmac_tx_excp_free_netbuf(pst_netbuf);
            }
            return ul_ret;
        }
        else
        {
            pst_tx_ctl->bit_roam_data = OAL_FALSE;
        }
#endif //_PRE_WLAN_FEATURE_ROAM

        if (OAL_TRUE == MAC_GET_CB_IS_VIPFRAME(pst_tx_ctl))
        {
            uc_data_type =  mac_get_data_type(pst_netbuf);
            /* 维测，输出一个关键帧打印 */
            if((MAC_DATA_DHCP == uc_data_type) ||
        #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
                (MAC_DATA_ARP_REQ == uc_data_type) ||
                (MAC_DATA_ARP_RSP == uc_data_type) ||
        #endif
                (MAC_DATA_EAPOL == uc_data_type))
            {
                OAM_WARNING_LOG3(pst_event_hdr->uc_vap_id, OAM_SF_WPA, "{dmac_tx_process_data_event::datatype==%u, qos==%u, usridx=%d}[0:dhcp 1:arp_req 2:arp_rsp 3:eapol]", uc_data_type, mac_get_cb_is_qosdata(pst_tx_ctl), MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));

                /* 定位窗口卡死或TID队列无效维测信息 */
                dmac_tx_pause_info(pst_hal_device, pst_dmac_vap, pst_netbuf);
            }
        }

        ul_ret = dmac_tx_process_data(pst_hal_device, pst_dmac_vap, pst_netbuf);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_INFO_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_data_event::dmac_tx_process_data fail[%u].}", ul_ret);
            dmac_tx_excp_free_netbuf(pst_netbuf);
        }

        pst_netbuf = pst_netbuf_next;
    }

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_TX_DMAC_END);

    return OAL_SUCC;
}
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

#ifdef _PRE_WLAN_FEATURE_SMARTANT
/*****************************************************************************
 函 数 名  : dmac_tx_training_data
 功能描述  : 发送训练报文
 输入参数  : pst_user, pst_netbuf
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_tx_training_data(mac_user_stru *pst_user, oal_uint8 uc_tid_num, oal_netbuf_stru *pst_netbuf, oal_uint16 us_msdu_len)
{
    hal_to_dmac_device_stru *pst_hal_device;
    dmac_vap_stru           *pst_dmac_vap;
    mac_tx_ctl_stru         *pst_tx_ctl;

    if (OAL_UNLIKELY(uc_tid_num >= WLAN_TID_MAX_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_tx_dump_mgmt::invalid uc_tid_num[%d].", uc_tid_num);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取vap结构信息 */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_user->uc_vap_id);

    pst_hal_device = pst_dmac_vap->pst_hal_device;

    /* 获取device结构信息 */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_WARNING_LOG0(pst_user->uc_vap_id, OAM_SF_TX, "{dmac_tx_training_data::pst_hal_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取netbuf链中第一个netbuf的CB */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* 设置CB字段 */
    MAC_GET_CB_MPDU_NUM(pst_tx_ctl)                 = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctl)               = 1;
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)              = OAL_FALSE;
    MAC_GET_CB_FRAME_TYPE(pst_tx_ctl)            = WLAN_DATA_BASICTYPE;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctl)                 = us_msdu_len;
    mac_set_cb_is_qosdata(pst_tx_ctl, pst_user->st_cap_info.bit_qos);
    mac_set_cb_tid(pst_tx_ctl, uc_tid_num);
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_TID_TO_AC(uc_tid_num));
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl)            = FRW_EVENT_TYPE_WLAN_DRX;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)              = (oal_uint8) pst_user->us_assoc_id;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctl)         = DMAC_USER_ALG_SMARTANT_NULLDATA_PROBE;
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)      = MAC_80211_FRAME_LEN;

    if (OAL_SUCC != dmac_tx_process_data(pst_hal_device, pst_dmac_vap, pst_netbuf))
    {
        dmac_tx_excp_free_netbuf(pst_netbuf);
        return OAL_FAIL;
    }

    return OAL_SUCC;
}
#endif
#ifdef _PRE_WLAN_FEATURE_DBAC
/*****************************************************************************
 函 数 名  : dmac_is_need_enqueue_fake_for_dbac
 功能描述  : dbac是否缓存帧到FAKE队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月14日
    作    者   : zhangyu 00241943
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 dmac_is_need_enqueue_fake_for_dbac(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_netbuf)
{
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_ieee80211_frame_stru       *pst_mac_header;
    oal_uint8                      *puc_sa = OAL_PTR_NULL;
#endif
    if (pst_mac_device->pst_device_stru->uc_current_chan_number != pst_mac_vap->st_channel.uc_chan_number)
    {
        return OAL_TRUE;
    }
    else
    {
        if (dmac_alg_dbac_is_pause(pst_mac_device))
        {
#ifdef _PRE_WLAN_FEATURE_P2P
            if (MAC_SCAN_FUNC_P2P_LISTEN == pst_mac_device->st_scan_params.uc_scan_func)
            {
                pst_mac_header  = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf);
                mac_rx_get_sa(pst_mac_header, &puc_sa);

                if (!oal_compare_mac_addr(puc_sa, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID))
                {
                    return OAL_FALSE;
                }
            }
#endif
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_proc_restore_tx_queue
 功能描述  : 从目标 虚假队列 中恢复发送队列信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月3日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_proc_restore_tx_queue(hal_to_dmac_device_stru     *pst_hal_device,
                                                hal_tx_dscr_queue_header_stru *pst_fake_queue)
{
    hal_tx_dscr_stru                *pst_tx_dscr;
    hal_tx_dscr_stru                *pst_tx_dscr_next;
    oal_uint8                        uc_q_idx;
    oal_dlist_head_stru             *pst_dscr_entry;
    oal_bool_enum_uint8              en_mpdu_skip;
    oal_uint32                       ul_tx_q_full;
    oal_uint32                       ul_put_cnt = 0;
    hal_tx_dscr_stru                *pst_tail_dscr;


    /* DTS2015031608823，0在02是BE，在51是BK队列 */
    for (uc_q_idx = 0; uc_q_idx < HAL_TX_QUEUE_BUTT; uc_q_idx++)
    {
        /* 将虚假队列里的帧恢复到硬件队列中去 */
        oal_dlist_join_head(&pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header,
                            &pst_fake_queue[uc_q_idx].st_header);
        pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt = pst_fake_queue[uc_q_idx].uc_ppdu_cnt;
        oal_dlist_init_head(&pst_fake_queue[uc_q_idx].st_header);
        pst_fake_queue[uc_q_idx].uc_ppdu_cnt = 0;

        ul_put_cnt      = 0;
        ul_tx_q_full    = 0;
        pst_tail_dscr   = OAL_PTR_NULL;

        en_mpdu_skip = OAL_FALSE;

        OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_entry, &pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header)
        {
            pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
            if (OAL_FALSE == en_mpdu_skip)
            {
                /* DTS2015061804889 不仅对高优先级队列，对普通数据队列也要做检查*/
                hal_get_tx_q_status(pst_hal_device, &ul_tx_q_full, uc_q_idx);

                if (ul_tx_q_full)
                {
                    if (OAL_PTR_NULL == pst_tail_dscr)
                    {
                        /* 此处异常一般是因为没有清fifo所致 */
                        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_restore_tx_queue::hw queue full while no frame put.}");
                        return;
                    }
                    hal_tx_ctrl_dscr_link(pst_hal_device, pst_tail_dscr, pst_tx_dscr);
                }
                else
                {
                    hal_tx_put_dscr(pst_hal_device, uc_q_idx, pst_tx_dscr);
                    ul_put_cnt++;
                }
            }

            hal_get_tx_dscr_next(pst_hal_device, pst_tx_dscr, &pst_tx_dscr_next);

            if (pst_tx_dscr_next != OAL_PTR_NULL)
            {
                en_mpdu_skip = OAL_TRUE;
            }
            else
            {
                en_mpdu_skip = OAL_FALSE;
                pst_tail_dscr = pst_tx_dscr;
            }

            if (ul_put_cnt > DMAC_MAX_FIFO_PUT)
            {
                OAM_ERROR_LOG3(0, OAM_SF_TX, "{dmac_tx_restore_tx_queue::TX FIFO OVERRUN invoked, ppdu=%d Q=%d cnt=%d}",
                                pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt, uc_q_idx, ul_put_cnt);
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : dmac_tx_restore_tx_queue
 功能描述  : 将发送队列中的描述符地址告知硬件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月28日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_restore_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id)
{
    hal_tx_dscr_queue_header_stru   *pst_fake_queue;

    if (OAL_UNLIKELY(uc_fake_q_id >= HAL_TX_FAKE_QUEUE_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_tx_restore_tx_queue::uc_fake_q_id is invalid, %d.}", uc_fake_q_id);
        return OAL_FAIL;
    }

    pst_fake_queue = pst_hal_device->ast_tx_dscr_queue_fake[uc_fake_q_id];
    dmac_proc_restore_tx_queue(pst_hal_device, pst_fake_queue);

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_tx_hw_send
 功能描述  : 将描述符挂入发送队列并将描述符地址告知硬件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月28日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_tx_mgmt_hw_send(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, hal_tx_dscr_stru *pst_mgmt_dscr, mac_tx_ctl_stru *pst_tx_ctl)
{
    hal_tx_dscr_stru    *pst_last_dscr;
    oal_dlist_head_stru *pst_last_dscr_entry;
    oal_uint32           ul_tx_q_status;
    hal_tx_queue_type_enum_uint8 uc_q_num;
    oal_uint8           uc_ac;

    uc_ac = mac_get_cb_ac(pst_tx_ctl);
    uc_q_num = HAL_AC_TO_Q_NUM(uc_ac);

    /*****************************************************************************
        Step 1. 挂到软件维护的发送队列队尾
    *****************************************************************************/
    oal_dlist_add_tail(&pst_mgmt_dscr->st_entry, &(pst_hal_device->ast_tx_dscr_queue[uc_q_num].st_header));
    pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt++;

    /*****************************************************************************
        Step 2. 写到硬件发送队列，有两种情况
        1) 如果硬件发送队列FIFO已满，直接挂到最后一个写入硬件的描述符队列队尾
        2) 如果不满，直接将此描述符写入硬件FIFO
    *****************************************************************************/
    /* 读取发送队列状态寄存器 */
    hal_get_tx_q_status(pst_hal_device, &ul_tx_q_status, uc_q_num);

#ifdef _PRE_DEBUG_MODE
    g_ast_tx_complete_stat[pst_hal_device->uc_mac_device_id].ul_tx_mgnt_num++;
    OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "dmac_tx_mgmt_hw_send:ul_tx_mgnt_num = %d", g_ast_tx_complete_stat[pst_hal_device->uc_mac_device_id].ul_tx_mgnt_num);
#endif

    /* 状态寄存器非0，表示硬件发送队列FIFO满 */
    if (0 != ul_tx_q_status)
    {
        OAL_MEM_TRACE(pst_mgmt_dscr, OAL_FALSE);
        /* 挂到最后一个写入硬件的描述符队列队尾 */
        pst_last_dscr_entry = pst_hal_device->ast_tx_dscr_queue[uc_q_num].st_header.pst_prev->pst_prev;
        pst_last_dscr       = OAL_DLIST_GET_ENTRY(pst_last_dscr_entry, hal_tx_dscr_stru, st_entry);

        hal_tx_ctrl_dscr_link(pst_hal_device, pst_last_dscr, pst_mgmt_dscr);
        OAM_WARNING_LOG3(0, OAM_SF_TX, "dmac_tx_mgmt_hw_send::uc_q_num = [%d], ul_tx_q_status = [%d], ppdu_cnt[%d]",
                         uc_q_num, ul_tx_q_status, pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        /* DTS2015112502032 硬件数据发送不出去，导致描述符耗尽、netbuf耗尽等维测代码，定位后删除 start */
        if ((pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt % 10) == 0)
        {
            hal_dft_print_rfhw_stat(pst_hal_device);
            hal_get_btcoex_statistic(OAL_FALSE);
        }

        if ((pst_hal_device->ast_tx_dscr_queue[uc_q_num].uc_ppdu_cnt % 30) == 0)
        {
            hal_dft_report_all_reg_state(pst_hal_device);
        }
        /* DTS2015112502032 硬件数据发送不出去，导致描述符耗尽、netbuf耗尽等维测代码，定位后删除 end */
#endif
    }
    else
    {

        OAL_MEM_TRACE(pst_mgmt_dscr, OAL_FALSE);
        /* 写入硬件 */
        hal_tx_put_dscr(pst_hal_device, uc_q_num, pst_mgmt_dscr);
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 函 数 名  : dmac_tx_force
 功能描述  : 强制发送接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_force(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint16 us_len, oal_uint8 uc_mgmt)
{
    hal_to_dmac_device_stru            *pst_hal_device;
    mac_tx_ctl_stru                    *pst_tx_ctl;
    hal_tx_dscr_stru                   *pst_tx_dscr;
    dmac_user_stru                     *pst_dmac_user;
    mac_ieee80211_frame_stru           *pst_mac_header;
    mac_device_stru                    *pst_mac_device;
    hal_tx_txop_alg_stru               *pst_txop_alg;
    hal_tx_txop_feature_stru            st_txop_feature     = {0};
    wlan_security_txop_params_stru      security_info = {0};
    hal_tx_ppdu_feature_stru            st_ppdu_feature;
    hal_tx_mpdu_stru                    st_mpdu;
    wlan_channel_band_enum_uint8        en_band;
    oal_uint32                          ul_ret;
    oal_uint8                           uc_ac;
    oal_uint8                           uc_vapid;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    oal_uint32                          ul_bank3_bcn_period;
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    bt_status_stru                     *pst_bt_status;
#endif //_PRE_WLAN_FEATURE_BTCOEX
    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_netbuf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* netbuf维测 */
    OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);

    uc_vapid = pst_dmac_vap->st_vap_base_info.uc_vap_id;

    pst_hal_device = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }
    if (OAL_TRUE == MAC_DEV_IS_RESET_IN_PROGRESS(pst_mac_device))
    {
        return OAL_ERR_CODE_RESET_INPROGRESS;
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    uc_ac      = mac_get_cb_ac(pst_tx_ctl);

    /* 强制发送只处理一个netbuf的报文 */
    if (MAC_GET_CB_NETBUF_NUM(pst_tx_ctl) != 1)
    {
       OAM_WARNING_LOG1(uc_vapid, OAM_SF_TX, "{dmac_tx_force::netbuf num[%d] != 1}", MAC_GET_CB_NETBUF_NUM(pst_tx_ctl));
       return OAL_FAIL;
    }

    /* 不支持加密帧特殊处理 */
    if (mac_is_protectedframe((oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf)) == 1)
    {
       OAM_WARNING_LOG0(uc_vapid, OAM_SF_TX, "{dmac_tx_force::protectedframe detected}");
       return OAL_FAIL;
    }

    /* 强制发送期间，用户必须存在 */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_WARNING_LOG0(uc_vapid, OAM_SF_TX, "{dmac_tx_force::pst_dmac_user null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tx_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_TX_DSCR_1, WLAN_MEM_SHARED_TX_DSCR_SIZE1, OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tx_dscr))
    {
        OAM_ERROR_LOG0(uc_vapid, OAM_SF_TX, "{dmac_tx_force::pst_tx_dscr alloc failed.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_MEM_TRACE(pst_tx_dscr, OAL_FALSE);

    OAL_MEMZERO(pst_tx_dscr, WLAN_MEM_SHARED_TX_DSCR_SIZE1);

    pst_mac_header = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf);

    pst_mac_header->bit_frag_num = 0;

    if (uc_mgmt)
    {
        pst_mac_header->bit_seq_num  = 0;
        dmac_get_mgmt_mpdu_param(pst_netbuf, pst_tx_ctl, us_len, &st_mpdu);
    }
    else
    {
        dmac_tx_seqnum_set(pst_dmac_user, pst_tx_ctl);
        ul_ret = dmac_tx_get_mpdu_params(pst_netbuf, pst_tx_ctl, &st_mpdu);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_force::dmac_tx_get_mpdu_params failed[%d].", ul_ret);
            OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);
            return OAL_FAIL;
        }
#ifdef _PRE_WLAN_FEATURE_BTCOEX

        /* 非BT电话场景下为提高漫游成功率，发送完EAPOL，增加occupied_period以增加接收到对端的EAPOL的概率 */
        pst_bt_status = &(pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status);
        if ((mac_get_data_type(pst_netbuf) == MAC_DATA_EAPOL) && (pst_bt_status->bit_bt_on) && !(pst_bt_status->bit_bt_sco))
        {
            hal_set_btcoex_occupied_period(60000);//60ms
        }
#endif //_PRE_WLAN_FEATURE_BTCOEX
    }

    /* 获取组播、广播帧、单播帧发送参数 */
    en_band = pst_dmac_vap->st_vap_base_info.st_channel.en_band;
    if (OAL_TRUE == MAC_GET_CB_IS_MCAST(pst_tx_ctl))
    {
        pst_txop_alg = &(pst_dmac_vap->ast_tx_mgmt_bmcast[en_band]);
    }
    else
    {
        pst_txop_alg = &(pst_dmac_vap->ast_tx_mgmt_ucast[en_band]);
    }

    if (0 == uc_mgmt)
    {
        pst_tx_ctl->bit_roam_data = OAL_TRUE;
    }
    else
    {
        pst_tx_ctl->bit_roam_data = OAL_FALSE;
    }

    /* 初始化ppdu发送参数 */
    dmac_tx_init_ppdu_feature(pst_dmac_vap, OAL_PTR_NULL, 1, &st_ppdu_feature);

    /* 初始化获取txop */
    dmac_tx_set_txopps_param(pst_dmac_vap, pst_dmac_user, &st_txop_feature, MAC_GET_CB_IS_MCAST(pst_tx_ctl));

    st_txop_feature.pst_security = &security_info;
    st_txop_feature.pst_security->en_cipher_key_type       = WLAN_KEY_TYPE_TX_GTK;
    st_txop_feature.pst_security->en_cipher_protocol_type  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    st_txop_feature.pst_security->uc_cipher_key_id         = 0;

    /* 填写发送描述符基本信息 */
    hal_tx_fill_basic_ctrl_dscr(pst_hal_device, pst_tx_dscr, &st_mpdu);
    pst_tx_dscr->us_original_mpdu_len = us_len;
    pst_tx_dscr->bit_is_retried       = OAL_FALSE;
    pst_tx_dscr->bit_is_first         = 0;
    pst_tx_dscr->uc_q_num             = HAL_AC_TO_Q_NUM(uc_ac);

/* 只1102需要tsf_restore逻辑 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    if ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode))
    {
    	/* 发送时如果发现staut bank3 的beacon周期为0 需要将ap的tsf同步给sta */
        hal_vap_get_beacon_period(pst_dmac_vap->pst_hal_vap, &ul_bank3_bcn_period);
        if (0 == ul_bank3_bcn_period)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"tx force staut bank3 bcn period 0 ap sync tsf to sta");
            hal_sta_tsf_restore(pst_dmac_vap->pst_hal_vap);
        }
    }
#endif

    dmac_tx_get_timestamp(pst_dmac_vap->pst_hal_vap, &st_ppdu_feature.us_tsf);
    /* 调用管理帧和广播、组播数据帧填写描述符接口 */
    hal_tx_non_ucast_data_set_dscr(pst_hal_device, pst_tx_dscr, &st_txop_feature, pst_txop_alg, &st_ppdu_feature);
    hal_tx_ctrl_dscr_unlink(pst_hal_device, pst_tx_dscr);

    dmac_tx_dump_mgmt(pst_hal_device, pst_netbuf, us_len, st_mpdu.st_mpdu_mac_hdr.uc_mac_hdr_len, pst_tx_dscr);

    /* 将发送描述符挂接到硬件队列 */
    dmac_tx_mgmt_hw_send(pst_hal_device, pst_dmac_vap, pst_tx_dscr, pst_tx_ctl);

    return OAL_SUCC;
}

#endif //_PRE_WLAN_FEATURE_ROAM

#define PROBE_REQ_THREHOD_MS 100

/*****************************************************************************
 函 数 名  : dmac_tx_mgmt_buffer_proc
 功能描述  : 发送管理帧缓存处理，DBAC或背景扫描时管理帧需要缓存
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_tx_mgmt_buffer_proc(
                mac_device_stru     *pst_mac_device,
                dmac_vap_stru       *pst_dmac_vap,
                hal_tx_dscr_stru    *pst_mgmt_dscr,
                oal_netbuf_stru     *pst_netbuf_mgmt)
{
    hal_to_dmac_device_stru        *pst_hal_device;
    oal_uint8                       uc_q_id = 0;
    oal_uint8                       uc_mgmt_type;
    oal_uint8                       uc_mgmt_subtype;
    mac_ieee80211_frame_stru       *pst_mac_header;

    pst_hal_device = pst_dmac_vap->pst_hal_device;

#ifdef _PRE_WLAN_FEATURE_DBAC
    /* DBAC运行时判断管理帧是否需要缓存且不需要走到下面的背景扫描缓存判断 */
    if (mac_is_dbac_running(pst_mac_device))
    {
        if (dmac_is_need_enqueue_fake_for_dbac(pst_mac_device, &(pst_dmac_vap->st_vap_base_info), pst_netbuf_mgmt))
        {
            mac_fcs_get_fake_q_id(&pst_dmac_vap->st_vap_base_info, &uc_q_id);

            oal_dlist_add_tail(&pst_mgmt_dscr->st_entry, &(pst_hal_device->ast_tx_dscr_queue_fake[uc_q_id][pst_mgmt_dscr->uc_q_num].st_header));
            pst_hal_device->ast_tx_dscr_queue_fake[uc_q_id][pst_mgmt_dscr->uc_q_num].uc_ppdu_cnt++;

            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "dmac_tx_mgmt: buffered by dbac. fake q id:%d", uc_q_id);

            return OAL_TRUE;
        }

        return OAL_FALSE;
    }
#endif

    pst_mac_header  = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf_mgmt);
    uc_mgmt_type    = mac_frame_get_type_value((oal_uint8 *)pst_mac_header);
    uc_mgmt_subtype = mac_frame_get_subtype_value((oal_uint8 *)pst_mac_header);

    /* 是否需要背景扫描缓存 */
    /* DTS2015081404830,增加是否是前景扫描的判断，防止前景扫描时管理帧会入虚拟队列但是扫描完成后不会发出 */
    /* DTS2015112300401,删除管理帧判断，防止控制帧及nulldata在背景扫描时的发送 */
    if (MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state &&
        MAC_SCAN_FUNC_P2P_LISTEN != pst_mac_device->st_scan_params.uc_scan_func &&
        WLAN_SCAN_MODE_FOREGROUND != pst_mac_device->st_scan_params.en_scan_mode &&
        WLAN_SCAN_MODE_BACKGROUND_CCA != pst_mac_device->st_scan_params.en_scan_mode &&
        WLAN_SCAN_MODE_BACKGROUND_PNO != pst_mac_device->st_scan_params.en_scan_mode)
    {
        /*在背景扫描时,中间会切回工作信道,此时管理帧不需要缓存*/
        if (MAC_VAP_STATE_UP != pst_dmac_vap->st_vap_base_info.en_vap_state)
        {
            uc_q_id = HAL_TX_FAKE_QUEUE_BGSCAN_ID;

            oal_dlist_add_tail(&pst_mgmt_dscr->st_entry,
                               &(pst_hal_device->ast_tx_dscr_queue_fake[uc_q_id][pst_mgmt_dscr->uc_q_num].st_header));

            pst_hal_device->ast_tx_dscr_queue_fake[uc_q_id][pst_mgmt_dscr->uc_q_num].uc_ppdu_cnt++;

            OAM_WARNING_LOG3(0, OAM_SF_DBAC, "dmac_tx_mgmt: buffered by scan. scan mode:%d, type:%d, subtype:%d",
                             pst_mac_device->st_scan_params.en_scan_mode,
                             uc_mgmt_type,
                             uc_mgmt_subtype);

            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_tx_mgmt
 功能描述  : 发送管理帧接口
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
oal_uint32  dmac_tx_mgmt(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf_mgmt, oal_uint16 us_len)
{
    hal_tx_mpdu_stru                st_mpdu;
    mac_tx_ctl_stru                *pst_tx_ctl;
    hal_tx_dscr_stru               *pst_mgmt_dscr;
    hal_tx_txop_feature_stru        st_txop_feature     = {0};
    hal_tx_txop_alg_stru            st_txop_alg;
#ifdef _PRE_WLAN_CHIP_TEST
    hal_tx_txop_alg_stru           *pst_txop_alg        = OAL_PTR_NULL;
#endif
    hal_tx_ppdu_feature_stru        st_ppdu_feature;
    hal_to_dmac_device_stru        *pst_hal_device;
    wlan_security_txop_params_stru  st_security         = {0};
    dmac_user_stru                 *pst_dmac_user;
    oal_bool_enum_uint8             en_is_pkt_need_buff;  /* mpdu是否需要入节能队列的标志 */
    mac_ieee80211_frame_stru       *pst_mac_header;
    mac_device_stru                *pst_mac_device;
    mac_user_stru                  *pst_multi_user;
    wlan_channel_band_enum_uint8    en_band;
    oal_uint8                       uc_ac;
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    oal_uint32                      ul_relt;
#endif
    oal_uint8                       uc_mgmt_subtype;
    oal_uint8                       uc_mgmt_type;
    oal_bool_enum_uint8             en_need_buffer = OAL_FALSE;
    oal_uint8                       uc_subtype;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    oal_uint32                      ul_bank3_bcn_period;
#endif

#if defined(_PRE_WLAN_FEATURE_DBAC) && (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    mac_vap_stru                   *pst_mac_vap1;           /* 已经UP的1个VAP */
    mac_vap_stru                   *pst_mac_vap2;           /* 已经UP的1个VAP */
    mac_vap_stru                   *pst_current_chan_vap;   /* 当前信道上的VAP */
    oal_uint8                       uc_fake_q_id = 0;
    mac_fcs_mgr_stru               *pst_fcs_mgr;
    mac_fcs_cfg_stru               *pst_fcs_cfg;
#endif

    OAL_MEM_NETBUF_TRACE(pst_netbuf_mgmt, OAL_TRUE);

    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_netbuf_mgmt)
    {
        OAM_ERROR_LOG2(0, OAM_SF_TX, "{dmac_tx_mgmt::param null, pst_dmac_vap=%d, pst_netbuf_mgmt=%d.}",
                       pst_dmac_vap, pst_netbuf_mgmt);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_dmac_vap->pst_hal_device;
    if (OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_mgmt::pst_hal_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if((OAL_PTR_NULL == pst_mac_device) || (OAL_TRUE == MAC_DEV_IS_RESET_IN_PROGRESS(pst_mac_device)))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_mgmt::MAC_DEV_IS_RESET_IN_PROGRESS.}");

        return OAL_ERR_CODE_RESET_INPROGRESS;
    }

    pst_mac_header = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf_mgmt);

    if ((WLAN_CONTROL != pst_mac_header->st_frame_control.bit_type) ||
        (WLAN_BLOCKACK_REQ != pst_mac_header->st_frame_control.bit_sub_type))
    {
        pst_mac_header->bit_frag_num = 0;
        pst_mac_header->bit_seq_num  = 0;
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf_mgmt);

    dmac_get_mgmt_mpdu_param(pst_netbuf_mgmt, pst_tx_ctl, us_len, &st_mpdu);

    /*
       查找用户，判断帧是否需要入节能队列，如果需要，则入队，发送流程不再往下走,
       如果用户找不到了也就不涉及节能，直接略过即可
    */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
    if (OAL_PTR_NULL != pst_dmac_user)
    {
     #ifdef _PRE_WLAN_FEATURE_UAPSD
        if(mac_vap_get_uapsd_en(&pst_dmac_vap->st_vap_base_info)
            &&(OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctl))
            &&(OAL_FALSE == MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctl))
            &&(pst_dmac_user->uc_uapsd_flag & MAC_USR_UAPSD_TRIG))
        {
            mac_set_cb_is_need_pause_tid(pst_tx_ctl, OAL_FALSE);
            return dmac_uapsd_tx_enqueue(pst_dmac_vap, pst_dmac_user, pst_netbuf_mgmt);

        }
     #endif

       en_is_pkt_need_buff = dmac_psm_pkt_need_buff(pst_dmac_vap, pst_dmac_user, pst_netbuf_mgmt);
       if (OAL_TRUE == en_is_pkt_need_buff)
       {
           oal_set_netbuf_prev(pst_netbuf_mgmt, OAL_PTR_NULL);
           oal_set_netbuf_next(pst_netbuf_mgmt, OAL_PTR_NULL);
           mac_set_cb_is_need_pause_tid(pst_tx_ctl, OAL_FALSE);

           return dmac_psm_enqueue(pst_dmac_vap, pst_dmac_user, pst_netbuf_mgmt);
       }

       /* 获取group id 和 partial aid */
       dmac_tx_set_txopps_param(pst_dmac_vap, pst_dmac_user, &st_txop_feature, pst_tx_ctl->en_ismcast);
    }

    en_band = pst_dmac_vap->st_vap_base_info.st_channel.en_band;

    if (OAL_TRUE == MAC_GET_CB_IS_MCAST(pst_tx_ctl))
    {
        /* 获取组播、广播管理帧 发送参数 */
#ifdef _PRE_WLAN_CHIP_TEST
        pst_txop_alg = &(pst_dmac_vap->ast_tx_mgmt_bmcast[en_band]);
#endif
        oal_memcopy(&st_txop_alg, &(pst_dmac_vap->ast_tx_mgmt_bmcast[en_band]), OAL_SIZEOF(hal_tx_txop_alg_stru));
    }
    else
    {
        /* 获取单播 管理帧 发送参数 */
#ifdef _PRE_WLAN_CHIP_TEST
        pst_txop_alg = &(pst_dmac_vap->ast_tx_mgmt_ucast[en_band]);
#endif
        oal_memcopy(&st_txop_alg, &(pst_dmac_vap->ast_tx_mgmt_ucast[en_band]), OAL_SIZEOF(hal_tx_txop_alg_stru));

    }

    /* 初始化ppdu发送参数 */
    dmac_tx_init_ppdu_feature(pst_dmac_vap, pst_dmac_user, 1, &st_ppdu_feature);

    /* 不是发给关连用户的管理桢，TX描述幅ra lut index要填为最大用户数目(8, index 0~7) 场景：AP响应未关连用户的probe req*/
    if (MAX_TX_USER_IDX == MAC_GET_CB_TX_USER_IDX(pst_tx_ctl))
    {
        st_ppdu_feature.st_ppdu_addr_index.uc_ra_lut_index = (oal_uint8)g_us_wlan_assoc_user_max_num;
    }

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    pst_mgmt_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_TX_DSCR_1, WLAN_MEM_SHARED_TX_DSCR_SIZE1, OAL_TRUE);
#else
    pst_mgmt_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_DSCR, WLAN_MEM_SHARED_TX_DSCR_SIZE1, OAL_TRUE);
#endif
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mgmt_dscr))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_mgmt::pst_mgmt_dscr null.}");
#ifdef _PRE_WLAN_DFT_STAT
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

        dmac_dft_print_mac_phy_rf(pst_mac_device);
#endif
#endif
        return OAL_FAIL;
    }

    OAL_MEM_TRACE(pst_mgmt_dscr, OAL_FALSE);

    OAL_MEMZERO(pst_mgmt_dscr, WLAN_MEM_SHARED_TX_DSCR_SIZE1);

    /* 填写MPDU基本参数 */
    pst_mgmt_dscr->us_original_mpdu_len = us_len;
    uc_ac = mac_get_cb_ac(pst_tx_ctl);
    pst_mgmt_dscr->uc_q_num = HAL_AC_TO_Q_NUM(uc_ac);

    /* 管理帧默认不加密*/
    st_security.en_cipher_key_type      = WLAN_KEY_TYPE_TX_GTK;
    st_security.en_cipher_protocol_type = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    /* 如果报文中的加密位置1了,需要设置发送描述符为加密*/
    /* 需要区别如下2种情况下*/
    /* 1、WEP加密套件下，认证的第三帧,此时，用户还没有关联成功*/
    /* 2、WPA2加密套件下，协商11W成功后，11W规定的部分管理帧*/
    if (mac_is_protectedframe((oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf_mgmt)) == 1)
    {
        pst_multi_user = mac_res_get_mac_user(pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_multi_user))
        {
            OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_tx_mgmt::pst_multi_user[%d] is NULL!}", pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
            OAL_MEM_FREE(pst_mgmt_dscr, OAL_TRUE);
            return OAL_ERR_CODE_PTR_NULL;
        }
        //st_security.en_cipher_protocol_type = pst_multi_user->en_cipher_type;
        st_security.en_cipher_protocol_type = pst_multi_user->st_user_tx_info.st_security.en_cipher_protocol_type;
        st_security.en_cipher_key_type      = pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type;

        if (OAL_TRUE == mac_is_wep_enabled(&pst_dmac_vap->st_vap_base_info))

        {
            /* TBD非法值处理 */
            st_security.uc_cipher_key_id = mac_vap_get_default_key_id(&pst_dmac_vap->st_vap_base_info);
        }
    }

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

    /* 设置PMF管理帧单播加密位 */
    dmac_11w_set_protectframe(pst_dmac_vap, &st_security, pst_netbuf_mgmt);

    if ((OAL_TRUE == ETHER_IS_MULTICAST(pst_mac_header->auc_address1)) &&
        (0 == mac_is_protectedframe((oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf_mgmt))))
    {
        /* 强健组播管理帧加密 */
        ul_relt = dmac_bip_crypto(pst_dmac_vap, pst_netbuf_mgmt, &st_security, &us_len);
        if(OAL_SUCC != ul_relt)
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                           "{dmac_tx_mgmt::dmac_bip_crypto failed[%d].}", ul_relt);
            OAL_MEM_FREE(pst_mgmt_dscr, OAL_TRUE);
            return OAL_ERR_CODE_PMF_BIP_CRIPTO_FAIL;
        }
        /* 更新发送帧的长度 */
        pst_mgmt_dscr->us_original_mpdu_len    = us_len;
        st_mpdu.ast_msdu_addr[0].us_msdu0_len  = us_len - st_mpdu.st_mpdu_mac_hdr.uc_mac_hdr_len;
     }
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)  */
    st_txop_feature.pst_security    = &st_security;

    /* 填写发送描述符参数 */
    hal_tx_fill_basic_ctrl_dscr(pst_hal_device, pst_mgmt_dscr, &st_mpdu);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (OAL_TRUE == g_l_proxysta_feature)
        {
            if((OAL_TRUE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_proxysta)
            && (OAL_FALSE == pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta))
            {
                /* bit_tx_hal_vap_id 为真正的Proxy STA的hal vap id,Proxy STA的hal vap id取值范围为16~31,*/
                /* 因为只有四位，故减去16的偏移量,且用1~15表示Proxy STA的16~31，此位非0就是Proxy STA */
                pst_mgmt_dscr->bit_tx_hal_vap_id = (pst_dmac_vap->pst_hal_vap->uc_vap_id - HAL_PROXY_STA_START_IDX + 1);
            }
        }
#endif

/* 只1102需要tsf_restore逻辑 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    if ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode))
    {
    	/* 发送时如果发现staut bank3 的beacon周期为0 需要将ap的tsf同步给sta */
        hal_vap_get_beacon_period(pst_dmac_vap->pst_hal_vap, &ul_bank3_bcn_period);
        if (0 == ul_bank3_bcn_period)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,"tx mgmt staut bank3 bcn period 0 ap sync tsf to sta");
            hal_sta_tsf_restore(pst_dmac_vap->pst_hal_vap);
        }
    }
#endif

    dmac_tx_get_timestamp(pst_dmac_vap->pst_hal_vap, &st_ppdu_feature.us_tsf);
    /* 调用管理帧和广播、组播数据帧填写描述符接口 */
    hal_tx_non_ucast_data_set_dscr(pst_hal_device, pst_mgmt_dscr, &st_txop_feature, &st_txop_alg, &st_ppdu_feature);
    hal_tx_ctrl_dscr_unlink(pst_hal_device, pst_mgmt_dscr);

#ifdef _PRE_WLAN_CHIP_TEST
    DMAC_CHIP_TEST_CALL(dmac_test_dfx_set_tx_cnt(pst_txop_alg));
#endif


#ifdef _PRE_WLAN_DFT_STAT
    /* 软件发送管理帧统计 */
    dmac_dft_mgmt_stat_incr(pst_mac_device, (oal_uint8 *)pst_mac_header, MAC_DEV_MGMT_STAT_TYPE_TX);
#endif

    uc_subtype     =  mac_get_frame_sub_type((oal_uint8 *)pst_mac_header);
    if ((WLAN_FC0_SUBTYPE_NODATA | WLAN_FC0_TYPE_DATA) != uc_subtype  && (WLAN_FC0_SUBTYPE_QOS_NULL | WLAN_FC0_TYPE_DATA) != uc_subtype)/*null data帧不需要打印*/
    {
        dmac_tx_dump_mgmt(pst_hal_device, pst_netbuf_mgmt, us_len, st_mpdu.st_mpdu_mac_hdr.uc_mac_hdr_len, pst_mgmt_dscr);
    }

    /*****************************************************************************
        到此发送描述符已填写完毕，接下来放到硬件队列
    *****************************************************************************/
    uc_mgmt_type    = mac_frame_get_type_value((oal_uint8 *)pst_mac_header);
    uc_mgmt_subtype = mac_frame_get_subtype_value((oal_uint8 *)pst_mac_header);

    /* 先判断此管理帧是否要缓存 */
    if (WLAN_MANAGEMENT == uc_mgmt_type && WLAN_PROBE_REQ == uc_mgmt_subtype)
    {
        /* probe req在任何情况下都不需要缓存 */
        /* do nothing */
        //OAM_INFO_LOG0(0, OAM_SF_SCAN, "dmac_tx_mgmt: tx probe req");
    }
    else
    {
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        if (WLAN_MANAGEMENT == uc_mgmt_type && WLAN_DISASOC == uc_mgmt_subtype)
        {
#ifdef _PRE_WLAN_DFT_STAT
            dmac_dft_report_all_ota_state(&(pst_dmac_vap->st_vap_base_info));
#endif
        }
#endif

/* 1102 sta+p2p共存引入的优化，1151 DBAC不需要 */
#if defined(_PRE_WLAN_FEATURE_DBAC) && (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        if ((WLAN_MANAGEMENT == uc_mgmt_type && WLAN_DISASOC == uc_mgmt_subtype)
             && mac_is_dbac_running(pst_mac_device)
             && (MAC_VAP_STATE_PAUSE == pst_dmac_vap->st_vap_base_info.en_vap_state))
        {
            /* 暂停两个VAP的发送 */
            if (OAL_SUCC == mac_device_find_2up_vap(pst_mac_device, &pst_mac_vap1, &pst_mac_vap2))
            {
                pst_fcs_mgr = dmac_fcs_get_mgr_stru(pst_mac_device);
                pst_fcs_cfg = &(pst_mac_device->st_fcs_cfg);
                OAL_MEMZERO(pst_fcs_cfg, OAL_SIZEOF(mac_fcs_cfg_stru));
                dmac_vap_pause_tx(pst_mac_vap1);
                dmac_vap_pause_tx(pst_mac_vap2);
                /* 暂停DBAC切信道 */
                dmac_alg_dbac_pause(pst_mac_device);
                if (pst_mac_device->pst_device_stru->uc_current_chan_number == pst_mac_vap1->st_channel.uc_chan_number)
                {
                    pst_current_chan_vap = pst_mac_vap1;
                }
                else
                {
                    pst_current_chan_vap = pst_mac_vap2;
                }

                mac_fcs_get_fake_q_id(pst_current_chan_vap, &uc_fake_q_id);

                pst_fcs_cfg->st_src_chl = pst_current_chan_vap->st_channel;
                pst_fcs_cfg->st_dst_chl = pst_dmac_vap->st_vap_base_info.st_channel;
                mac_fcs_prepare_one_packet_cfg(pst_current_chan_vap, &(pst_fcs_cfg->st_one_packet_cfg), 20);
                mac_fcs_start(pst_fcs_mgr, pst_fcs_cfg, 0, uc_fake_q_id);
                mac_fcs_release(pst_fcs_mgr);
            }
        }
        else
#endif

        {
            en_need_buffer = dmac_tx_mgmt_buffer_proc(pst_mac_device, pst_dmac_vap, pst_mgmt_dscr, pst_netbuf_mgmt);

            if (OAL_TRUE == en_need_buffer)
            {
                oal_uint8                       auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xff,0xff,0xff,0xff,0xff,0xff};

                OAL_MEM_TRACE(pst_mgmt_dscr, OAL_FALSE);

                /* 将缓存帧直接通过OTA上报，方便问题定位 */
                oam_report_80211_frame(auc_user_macaddr,
                                        (oal_uint8*)mac_get_cb_frame_hdr(pst_tx_ctl),
                                        MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl),
                                        (oal_uint8*)oal_netbuf_payload(pst_netbuf_mgmt),
                                        us_len,
                                        OAM_OTA_FRAME_DIRECTION_TYPE_TX);

                return OAL_SUCC;
            }
        }
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if (pst_mac_device->pst_device_stru->st_btcoex_btble_status.un_ble_status.st_ble_status.bit_ble_scan)
    {
        if ((WLAN_AUTH == uc_mgmt_subtype) || (WLAN_ASSOC_REQ == uc_mgmt_subtype))
        {
            hal_set_btcoex_occupied_period(50000);//50ms
        }
    }
#endif

#if 0
	/* 启动无发送完成中断检测定时器 */
    if (OAL_FALSE == pst_hal_device->st_dfr_tx_prot.st_tx_prot_timer.en_is_enabled)
    {
        FRW_TIMER_RESTART_TIMER(&pst_hal_device->st_dfr_tx_prot.st_tx_prot_timer, WLAN_TX_PROT_TIMEOUT, OAL_TRUE);
    }
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        /* 单p2p dev无低功耗状态机单独恢复前端 */
        if ((IS_P2P_DEV(&pst_dmac_vap->st_vap_base_info)))
        {
            dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);
        }
        /* cl || legacy sta抛事件恢复前端 */
        else
        {
            dmac_pm_enable_front_end(pst_mac_device, OAL_TRUE);
            dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_TX_MGMT, 0, OAL_PTR_NULL);
        }
    }
#endif

    dmac_tx_mgmt_hw_send(pst_hal_device, pst_dmac_vap, pst_mgmt_dscr, pst_tx_ctl);

    /* pst_hal_device->uc_mpdu_num++; */ /* 无用，删除 */


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_rifs_process
 功能描述  : rifs发送处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_tx_rifs_process(hal_to_dmac_device_stru *pst_hal_dev,
                                      dmac_vap_stru *pst_dmac_vap,
                                      dmac_tid_stru *pst_tid_queue,
                                      hal_tx_ppdu_feature_stru *pst_ppdu_feature,
                                      oal_dlist_head_stru *pst_dscr_list)
{
    hal_tx_dscr_stru    *pst_first_dscr;
    hal_tx_dscr_stru    *pst_last_dscr;
    hal_tx_dscr_stru    *pst_bar_dscr;
    oal_netbuf_stru     *pst_bar_buf;
    dmac_ba_tx_stru     *pst_tx_ba_handle;
    mac_tx_ctl_stru     *pst_tx_ctl;
    oal_uint16           us_bar_len;
    hal_tx_mpdu_stru     st_mpdu;
    oal_dlist_head_stru *pst_dscr_entry;
    hal_tx_dscr_stru    *pst_dscr;
    mac_ieee80211_qos_frame_addr4_stru *pst_4addr_hdr;
    mac_ieee80211_qos_frame_stru       *pst_hdr;


    pst_tx_ba_handle = pst_tid_queue->pst_ba_tx_hdl;

    /* 申请bar描述符 */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    pst_bar_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_TX_DSCR_1, WLAN_MEM_SHARED_TX_DSCR_SIZE1, OAL_TRUE);
#else
    pst_bar_dscr = (hal_tx_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_DSCR, WLAN_MEM_SHARED_TX_DSCR_SIZE1, OAL_TRUE);
#endif
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_bar_dscr))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_rifs_process::pst_bar_dscr null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_MEM_TRACE(pst_bar_dscr, OAL_FALSE);
    OAL_MEMZERO(pst_bar_dscr, WLAN_MEM_SHARED_TX_DSCR_SIZE1);

    /* 申请bar帧体 */
    pst_bar_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
    OAL_MEM_NETBUF_TRACE(pst_bar_buf, OAL_FALSE);
    if (OAL_PTR_NULL == pst_bar_buf)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_rifs_process::pst_bar_buf null.}");

        OAL_MEM_FREE(pst_bar_dscr, OAL_TRUE);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_NETBUF_TRACE(pst_bar_buf, OAL_TRUE);

    /* 组bar帧 */
    us_bar_len = dmac_ba_encap_blockack_req(pst_dmac_vap, pst_bar_buf, pst_tx_ba_handle, pst_tid_queue->uc_tid);
    if (0 == us_bar_len)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_rifs_process::us_bar_len=0.}");
        OAL_MEM_FREE(pst_bar_dscr, OAL_TRUE);
        oal_netbuf_free(pst_bar_buf);

        return OAL_FAIL;
    }

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_bar_buf);
    OAL_MEMZERO(pst_tx_ctl, OAL_NETBUF_CB_SIZE());

    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl) = FRW_EVENT_TYPE_WLAN_CTX;
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)   = OAL_FALSE;
    mac_set_cb_is_bar(pst_tx_ctl, OAL_TRUE);
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl) = MAC_80211_CTL_HEADER_LEN;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctl)            = us_bar_len;


    oal_set_netbuf_prev(pst_bar_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_bar_buf, OAL_PTR_NULL);

    dmac_get_mgmt_mpdu_param(pst_bar_buf, pst_tx_ctl, us_bar_len, &st_mpdu);

    /* 填写bar描述符基本信息 */
    hal_tx_fill_basic_ctrl_dscr(pst_hal_dev, pst_bar_dscr, &st_mpdu);

    pst_last_dscr = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dscr_list->pst_prev, hal_tx_dscr_stru, st_entry);

    hal_tx_ctrl_dscr_link(pst_hal_dev, pst_last_dscr, pst_bar_dscr);
    hal_tx_ctrl_dscr_unlink(pst_hal_dev, pst_bar_dscr);

    /* 将bar串到rifs burst的最后 */
    oal_dlist_add_tail(&pst_bar_dscr->st_entry, pst_dscr_list);

    OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_entry, pst_dscr_list)
    {
        pst_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);

        pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_dscr->pst_skb_start_addr);

        if (OAL_TRUE == mac_get_cb_is_use_4_addr(pst_tx_ctl))
        {
            pst_4addr_hdr = (mac_ieee80211_qos_frame_addr4_stru *)mac_get_cb_frame_hdr(pst_tx_ctl);
            pst_4addr_hdr->bit_qc_ack_polocy = WLAN_TX_NO_ACK;
        }
        else
        {
            pst_hdr = (mac_ieee80211_qos_frame_stru *)mac_get_cb_frame_hdr(pst_tx_ctl);
            pst_hdr->bit_qc_ack_polocy = WLAN_TX_NO_ACK;
        }
    }

    pst_ppdu_feature->uc_ampdu_enable       = OAL_FALSE;
    pst_ppdu_feature->uc_rifs_enable        = OAL_TRUE;
    pst_ppdu_feature->ul_ampdu_length       = 0;
    pst_ppdu_feature->us_min_mpdu_length    = 0;

    pst_ppdu_feature->uc_mpdu_num++;

    pst_first_dscr = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dscr_list->pst_next, hal_tx_dscr_stru, st_entry);
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_first_dscr->pst_skb_start_addr);

    mac_set_cb_bar_dscr(pst_tx_ctl, pst_bar_dscr);
    return OAL_SUCC;
}

/*用于统计ampdu的聚合度*/
#ifdef _PRE_PROFILING_MODE
oal_uint32 g_ul_tx_mpdu_num = 0;
oal_uint32 g_ul_tx_ampdu_num = 0;
#endif

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif

/*****************************************************************************
 函 数 名  : dmac_tid_tx_queue_remove_ampdu
 功能描述  : 将一串MPDU从TID缓存队列中删除，组成ampdu并作ba窗口的处理，并发送
 输入参数  :
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tid_tx_queue_remove_ampdu(
                hal_to_dmac_device_stru   *pst_hal_device,
                dmac_vap_stru             *pst_dmac_vap,
                dmac_user_stru            *pst_user,
                dmac_tid_stru             *pst_tid_queue,
                oal_uint8                  uc_mpdu_num)
{
    mac_device_stru            *pst_dev;
    oal_uint8                   uc_mpdu_idx         = 0;
    oal_dlist_head_stru        *pst_dscr_entry      = OAL_PTR_NULL;
#ifndef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_dlist_head_stru        *pst_dscr_entry_next = OAL_PTR_NULL;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    hal_tx_dscr_stru           *pst_tx_dscr         = OAL_PTR_NULL;   /*当前处理的发送描述*/
    hal_tx_dscr_stru           *pst_tx_dscr_prev    = OAL_PTR_NULL;   /*前一个发送描述符*/
    hal_tx_txop_alg_stru       *pst_txop_alg        = OAL_PTR_NULL;
    mac_tx_ctl_stru            *pst_cb              = OAL_PTR_NULL;
    mac_tx_ctl_stru            *pst_cb_first        = OAL_PTR_NULL;
    oal_netbuf_stru            *pst_netbuf;
    hal_tx_ppdu_feature_stru    st_ppdu_feature;
    oal_uint16                  us_seq_num          = 0;
    dmac_ba_tx_stru            *pst_tx_ba_handle;
    oal_uint16                  us_roundup_len;
    oal_uint16                  us_baw_end;               /*可以发送的最大seq num*/
    oal_uint16                  us_new_mpdu_max_num = 0;  /*本次调度可以新发送的mpdu数码*/
    oal_uint16                  us_pad_len          = 0;
    oal_uint16                  us_null_len         = 0;
    oal_uint32                  ul_ret;
    oal_uint16                  us_mpdu_len;
    oal_uint16                  us_ext_mpdu_len;  /*每个MPDU额外添加的长度*/
    oal_dlist_head_stru         st_dscr_head;
    oal_uint8                   uc_vap_id;
    oal_uint8                   uc_retry_mpdu_num   = 0;  /*amdpu中重传mpdu的数目*/
#ifdef _PRE_DEBUG_MODE
    oal_dlist_head_stru        *pst_dscr_tra_entry  = OAL_PTR_NULL;
    hal_tx_dscr_stru           *pst_trace_dscr      = OAL_PTR_NULL;
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    oal_uint32                  ul_have_short_packet = OAL_FALSE;
#endif
    oal_uint32                  ul_max_ampdu_length;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    dmac_tid_stats_stru        *pst_tid_stats;

    pst_tid_stats = pst_tid_queue->pst_tid_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tid_tx_queue_remove::tid_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif
#endif
    uc_vap_id = pst_dmac_vap->st_vap_base_info.uc_vap_id;

    pst_tx_ba_handle = pst_tid_queue->pst_ba_tx_hdl;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tx_ba_handle))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::pst_tx_ba_handle null.}");

        return OAL_FAIL;
    }

    /* 更新device结构体下的统计信息 */
    pst_dev = mac_res_get_dev(pst_user->st_user_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::pst_dev null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((WLAN_VHT_MODE == pst_user->st_user_base_info.en_cur_protocol_mode)
      || (WLAN_VHT_ONLY_MODE == pst_user->st_user_base_info.en_cur_protocol_mode))
    {
        ul_max_ampdu_length = pst_tid_queue->st_ht_tx_hdl.ul_ampdu_max_size_vht;
    }
    else
    {
        ul_max_ampdu_length = pst_tid_queue->st_ht_tx_hdl.us_ampdu_max_size;
    }

    /* 初始化ppdu feature参数 */
    dmac_tx_init_ppdu_feature(pst_dmac_vap, pst_user, 0, &st_ppdu_feature);

    us_baw_end = DMAC_BA_SEQNO_ADD(pst_tx_ba_handle->us_baw_start, pst_tx_ba_handle->us_baw_size);
    us_baw_end = DMAC_BA_SEQNO_SUB(us_baw_end, 1);

    /*获取本次可以新发送mpdu的最大数目*/
    us_new_mpdu_max_num = DMAC_BA_SEQNO_SUB(us_baw_end, pst_tx_ba_handle->us_last_seq_num);

    us_ext_mpdu_len = WLAN_HDR_FCS_LENGTH + WLAN_DELIMETER_LENGTH;
    /* 判断是否加密增加加密字节数 */
    if (WLAN_80211_CIPHER_SUITE_CCMP == pst_user->st_user_base_info.st_key_info.en_cipher_type)
    {
        us_ext_mpdu_len += WLAN_CCMP_ENCRYP_LEN;
    }

    oal_dlist_init_head(&st_dscr_head);

#ifndef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    pst_dscr_entry_next = pst_tid_queue->st_hdr.pst_next;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_AMPDU_GET_INFO);
    while (uc_mpdu_idx != uc_mpdu_num)
    {
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        /* 出队顺序:先重传队列，再netbuf队列 */
        if (OAL_FALSE == oal_dlist_is_empty(&pst_tid_queue->st_retry_q))
        {
            /* 重传队列非空 */
            pst_dscr_entry = oal_dlist_delete_head(&pst_tid_queue->st_retry_q);
            pst_tx_dscr    = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
            oal_dlist_add_tail(pst_dscr_entry, &st_dscr_head);
        }
        else if (OAL_FALSE == oal_netbuf_list_empty(&pst_tid_queue->st_buff_head))
        {
            /* netbuf队列非空 */
            pst_netbuf  = dmac_tx_dequeue_first_mpdu(&pst_tid_queue->st_buff_head);
            pst_tx_dscr = dmac_tx_dscr_alloc(pst_hal_device, pst_dmac_vap, pst_netbuf);
            if (OAL_PTR_NULL == pst_tx_dscr)
            {
                OAM_WARNING_LOG3(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::put the pkt back into tid netbuf Q, alloc tx dscr failed. retry = %d, mpdu = %d, uc_mpdu_num = %d}",
                                 pst_tid_queue->uc_retry_num, pst_tid_queue->us_mpdu_num, uc_mpdu_num);

                dmac_tx_queue_mpdu_head(pst_netbuf, &pst_tid_queue->st_buff_head);
                break;
            }
            oal_dlist_add_tail(&pst_tx_dscr->st_entry, &st_dscr_head);
        }
        else
        {
            /* 都为空的情况下跳出 */
            break;
        }
#else
        if (pst_dscr_entry_next == (&pst_tid_queue->st_hdr))
        {
            //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::no more mpdus in tid queue.}\r\n");
            break;
        }

        pst_dscr_entry      = pst_dscr_entry_next;
        pst_dscr_entry_next = pst_dscr_entry->pst_next;

        pst_tx_dscr         = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
        pst_tx_dscr->bit_is_first = 0;

        if (0 == pst_tid_queue->uc_retry_num) /*非重传包*/
        {
            /* 如果窗口被塞满，则退出循环 */
            if ((uc_mpdu_idx - uc_retry_mpdu_num) == us_new_mpdu_max_num)
            {
            #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
                OAM_WARNING_LOG4(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::tx ba win full, pst_tx_dscr->bit_is_retried=%d, idx=%d, mpdu=%d, max=%d.}", pst_tx_dscr->bit_is_retried, uc_mpdu_idx, uc_retry_mpdu_num, us_new_mpdu_max_num);
                if (OAL_TRUE == pst_tx_dscr->bit_is_retried)
                {
                    /* 需要放回重传队列，从队列尾放回到重传队列头 */
                    pst_dscr_entry = oal_dlist_delete_tail(&st_dscr_head);
                    oal_dlist_add_head(pst_dscr_entry, &pst_tid_queue->st_retry_q);
                }
                else
                {
                    /* 放回netbuf队列 */
                    pst_dscr_entry = oal_dlist_delete_tail(&st_dscr_head);
                    pst_tx_dscr    = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
                    pst_netbuf     = pst_tx_dscr->pst_skb_start_addr;

                    dmac_tx_queue_mpdu_head(pst_netbuf, &pst_tid_queue->st_buff_head);
                    OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);
                }
            #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
                break;
            }
        }
        else /*重传包*/
        {
            /* 获取seq num */
            hal_tx_get_dscr_seq_num(pst_hal_device, pst_tx_dscr, &us_seq_num);
            /*OAM_INFO_LOG1(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::seq num of a retried packet=%d.}",us_seq_num);*/

            /* 如果该包不在窗内，需要丢弃 */
            if (!DMAC_BAW_WITHIN(pst_tx_ba_handle->us_baw_start, pst_tx_ba_handle->us_baw_size, us_seq_num))
            {
                OAM_WARNING_LOG3(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::a retry packet shall be dropped. baw_start=%d baw_size=%d sqe_num=%d.}",
                                 pst_tx_ba_handle->us_baw_start, pst_tx_ba_handle->us_baw_size, us_seq_num);
                pst_tid_queue->uc_retry_num--;
                pst_tid_queue->us_mpdu_num--;
                pst_dev->us_total_mpdu_num--;
                pst_dev->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
                pst_dev->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
                DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_ampdu_cnt, 1);
                DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_total_cnt, 1);
#endif
                oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
                dmac_free_tx_dscr(pst_tx_dscr);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)

        #ifdef _PRE_WLAN_DFT_STAT
                if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
                {
                    DMAC_TID_STATS_INCR(pst_tid_queue->pst_tid_stats->ul_tid_retry_dequeue_cnt, 1);
                }
        #endif
#endif
                continue;
            }

            pst_tid_queue->uc_retry_num--;
            uc_retry_mpdu_num++; /*注意调度出的都为重传帧，且字节长度超过协商值时候，uc_retry_mpdu_num有可能大于uc_mpdu_idx*/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    #ifdef _PRE_WLAN_DFT_STAT
            if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
            {
                DMAC_TID_STATS_INCR(pst_tid_queue->pst_tid_stats->ul_tid_retry_dequeue_cnt, 1);
            }
    #endif
#endif
        }

        us_mpdu_len = pst_tx_dscr->us_original_mpdu_len + us_ext_mpdu_len;
        /* 判断长度是否超过协商值 */
        if ((st_ppdu_feature.ul_ampdu_length + us_mpdu_len + us_pad_len + us_null_len) > ul_max_ampdu_length)
        {
            /* 对于重传包，retry_num在之前先减，此时超出长度后直接break而不挂到硬件队列，重传数异常*/
            /* DTS2015061905630，若retry_num 减为零，且BA窗口满，下一次无法调度，BA窗卡死 */
    #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
            if (OAL_TRUE == pst_tx_dscr->bit_is_retried)
            {
                pst_tid_queue->uc_retry_num++;

                /* 需要放回重传队列，从队列尾放回到重传队列头 */
                pst_dscr_entry = oal_dlist_delete_tail(&st_dscr_head);
                oal_dlist_add_head(pst_dscr_entry, &pst_tid_queue->st_retry_q);
            }
            else
            {
                /* 放回netbuf队列 */
                pst_dscr_entry = oal_dlist_delete_tail(&st_dscr_head);
                pst_tx_dscr    = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
                pst_netbuf     = pst_tx_dscr->pst_skb_start_addr;

                dmac_tx_queue_mpdu_head(pst_netbuf, &pst_tid_queue->st_buff_head);
                OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);
            }
    #else
            if(OAL_TRUE == pst_tx_dscr->bit_is_retried)
            {
                pst_tid_queue->uc_retry_num++;
            }
    #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

            break;
        }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
        /* 判断长度是否超过协商值 */
        if (us_mpdu_len < BT_WLAN_COEX_SMALL_PKT_THRES)
        {
            ul_have_short_packet = OAL_TRUE;
        }

        /*
           BT共存情况下 判断长度是否超过芯片门限
        */
        if ((OAL_TRUE == ul_have_short_packet))
        {
    #if 0
            /*需要BT或BLE打开时，触发聚合的整理，清理类似包*/
            hal_get_btcoex_soc_bt_gpreg((oal_uint16 *)(&us_bt_status));
            hal_get_btcoex_soc_ble_gpreg((oal_uint8 *)(&uc_ble_status));

            /*针对(us_bt_status.bit_bt_ps == OAL_FALSE)还是增量优化，避免睡眠和唤醒遇到的小概率问题*/
            if ((us_bt_status.bit_bt_on) || (uc_ble_status.bit_ble_on))
    #endif
            if (pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
            {
                if ((st_ppdu_feature.ul_ampdu_length + us_mpdu_len + us_pad_len + us_null_len) > BT_WLAN_COEX_SMALL_FIFO_THRES)
                {
            #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
                    if (OAL_TRUE == pst_tx_dscr->bit_is_retried)
                    {
                        pst_tid_queue->uc_retry_num++;

                        /* 需要放回重传队列，从队列尾放回到重传队列头 */
                        pst_dscr_entry = oal_dlist_delete_tail(&st_dscr_head);
                        oal_dlist_add_head(pst_dscr_entry, &pst_tid_queue->st_retry_q);
                    }
                    else
                    {
                        /* 放回netbuf队列 */
                        pst_dscr_entry = oal_dlist_delete_tail(&st_dscr_head);
                        pst_tx_dscr    = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
                        pst_netbuf     = pst_tx_dscr->pst_skb_start_addr;

                        dmac_tx_queue_mpdu_head(pst_netbuf, &pst_tid_queue->st_buff_head);
                        OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);
                    }
            #else
                    if(OAL_TRUE == pst_tx_dscr->bit_is_retried)
                    {
                        pst_tid_queue->uc_retry_num++;
                    }
            #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
                    break;
                }

                if (pst_tx_dscr->us_original_mpdu_len < BT_WLAN_COEX_UNAVAIL_PAYLOAD_THRES)
                {
                    OAM_ERROR_LOG1(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::ampdu length bug, length is %d}", pst_tx_dscr->us_original_mpdu_len);
                }
            }
        }
#endif

        pst_netbuf              = pst_tx_dscr->pst_skb_start_addr;
        pst_cb                  = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

        if (0 != uc_mpdu_idx)
        {
           /*描述符依次link*/
           hal_tx_ctrl_dscr_link(pst_hal_device, pst_tx_dscr_prev, pst_tx_dscr);
        }
        else
        {
            MAC_GET_CB_TX_USER_IDX(pst_cb)  =(oal_uint8)pst_user->st_user_base_info.us_assoc_id;
            pst_cb_first = pst_cb;

            /***** 临时维测 *****/
            if (OAL_TRUE == MAC_GET_CB_IS_VIPFRAME(pst_cb_first))
            {
                MAC_GET_CB_IS_VIPFRAME(pst_cb_first)  = OAL_FALSE;
                MAC_GET_CB_IS_NEEDRETRY(pst_cb_first) = OAL_FALSE;
                MAC_GET_CB_RETRIED_NUM(pst_cb_first)      = 0;
            }

            MAC_GET_CB_MPDU_NUM(pst_cb) = uc_mpdu_num;
            if (0 == uc_mpdu_num)
            {
                OAM_ERROR_LOG1(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::tid %d, uc_dscr_num is zero.}", mac_get_cb_tid(pst_cb));
            }

            /* 获取TXOP算法发送参数 */
            dmac_tx_get_txop_alg_params(pst_dmac_vap, pst_user, pst_cb, &pst_txop_alg);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_txop_alg))
            {
                OAM_ERROR_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::pst_txop_alg null.}");
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
                pst_dmac_vap->st_vap_base_info.st_vap_stats.ul_tx_dropped_packets += MAC_GET_CB_NETBUF_NUM(pst_cb);
#endif
        #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
                /* 需要释放所有已出队的内存 */
                OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_entry, &st_dscr_head)
                {
                    pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
                    oal_dlist_delete_entry(pst_dscr_entry);
                    dmac_free_tx_dscr(pst_tx_dscr);
                }

                /* 更新报文个数 */
                uc_mpdu_idx++;
                st_ppdu_feature.uc_mpdu_num += uc_mpdu_idx;
                pst_tid_queue->us_mpdu_num -= uc_mpdu_idx;
                pst_dev->us_total_mpdu_num -= uc_mpdu_idx;
                pst_dev->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id] -= uc_mpdu_idx;
                pst_dev->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)] -= uc_mpdu_idx;

                DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_ampdu_cnt, uc_mpdu_idx);
                DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_total_cnt, uc_mpdu_idx);
        #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

                return OAL_ERR_CODE_PTR_NULL;
            }

            if (WLAN_PROT_NO != pst_dmac_vap->st_vap_base_info.st_protection.en_protection_mode)
            {
                /*保护模式特性更新发送参数*/
                dmac_tx_update_protection_txop_alg(pst_dmac_vap, pst_txop_alg, OAL_FALSE, MAC_GET_CB_IS_MCAST(pst_cb));
            }

            /* 判断是否强制关闭RTS */
            dmac_judge_forbid_rts(pst_user, pst_txop_alg);

            /* 2040共存特性更新带宽模式 */
            /* dmac_tx_update_bandwidth_mode(pst_dmac_vap, pst_user, pst_txop_alg); */

            OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_AMPDU_AGGR_PREPARE);
            OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_AMPDU_AGGR_PREPARE);

            /* 查表找min mpdu len */
            st_ppdu_feature.us_min_mpdu_length = dmac_ba_calculate_min_mpdu_len(pst_user, pst_txop_alg);
            OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_AMPDU_CALCULATE_MINLEN);
            OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_AMPDU_CALCULATE_MINLEN);

            /*OAM_INFO_LOG1(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::us_min_mpdu_len=%d.}", st_ppdu_feature.us_min_mpdu_length);*/
        }

        /* 给ampdu总长度加上前一个帧的pad和null data这个帧的长度 */
        st_ppdu_feature.ul_ampdu_length += us_pad_len + us_null_len + us_mpdu_len;

        /* 计算 pad len，mpdu的长度需要4字节对齐*/
        us_pad_len = (4 - (us_mpdu_len & 0x3)) & 0x3;
        us_roundup_len = us_mpdu_len + us_pad_len;

        us_null_len = OAL_MAX(us_roundup_len, st_ppdu_feature.us_min_mpdu_length) - us_roundup_len;

        /*OAM_INFO_LOG4(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::ul_ampdu_length=%d us_roundup_len=%d us_pad_len=%d us_null_len=%d .}", \
                      st_ppdu_feature.ul_ampdu_length, us_roundup_len, us_pad_len, us_null_len);*/

        pst_tx_dscr_prev = pst_tx_dscr;
        uc_mpdu_idx++;

        /*非重传包才设置seq num并调整窗口*/
        if (OAL_FALSE == pst_tx_dscr->bit_is_retried)
        {
            dmac_tx_seqnum_set_ampdu(pst_user, pst_cb);
            /*发送窗口调整*/
            dmac_ba_addto_baw(pst_tx_ba_handle);
        }

#ifdef _PRE_WLAN_DFT_STAT
        /* 不是以太网来的不统计 */
        if ((FRW_EVENT_TYPE_HOST_DRX == MAC_GET_CB_EVENT_TYPE(pst_cb))
            && (OAL_TRUE != pst_tx_dscr->bit_is_retried))
        {
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_tx_pkts,
                                        MAC_GET_CB_NETBUF_NUM(pst_cb));
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_tx_bytes,
                                        MAC_GET_CB_MPDU_BYTES(pst_cb));
        }


#endif
    }

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_AMPDU_LINK_MPDUS);

#ifdef _PRE_DEBUG_MODE
    if (OAL_PTR_NULL == pst_cb_first || OAL_PTR_NULL == pst_txop_alg)
    {
        if (pst_tid_queue->us_mpdu_num > 0)
        {
            OAM_WARNING_LOG1(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::no element can be removed from the tid[%d].", pst_tid_queue->uc_tid);

            OAM_WARNING_LOG4(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::bitmap is %x %x %x %x.",
                             pst_tx_ba_handle->aul_tx_buf_bitmap[0], pst_tx_ba_handle->aul_tx_buf_bitmap[1],
                             pst_tx_ba_handle->aul_tx_buf_bitmap[2], pst_tx_ba_handle->aul_tx_buf_bitmap[3]);

            OAM_WARNING_LOG4(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::win start is %d win head is %d win tail is %d lsn is %d",
                             pst_tx_ba_handle->us_baw_start,
                             pst_tx_ba_handle->us_baw_head,
                             pst_tx_ba_handle->us_baw_tail,
                             pst_tx_ba_handle->us_last_seq_num);
        }

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        OAM_ERROR_LOG2(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::pst_cb_first null 0x%X or pst_txop_alg null 0x%X.}", pst_cb_first, pst_txop_alg);

        /* 需要释放所有已出队的内存 */
        OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_entry, &st_dscr_head)
        {
            pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
            oal_dlist_delete_entry(pst_dscr_entry);
            dmac_free_tx_dscr(pst_tx_dscr);
        }

        /* 更新报文个数 */
        st_ppdu_feature.uc_mpdu_num += uc_mpdu_idx;
        pst_tid_queue->us_mpdu_num -= uc_mpdu_idx;
        pst_dev->us_total_mpdu_num -= uc_mpdu_idx;
        pst_dev->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id] -= uc_mpdu_idx;
        pst_dev->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)] -= uc_mpdu_idx;

        DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_ampdu_cnt, uc_mpdu_idx);
        DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_total_cnt, uc_mpdu_idx);
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
        return OAL_FAIL;
    }
#endif

    /*确认是否有mpdu发送*/
    if (0 == uc_mpdu_idx)
    {
    #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_entry, &st_dscr_head)
        {
            OAM_ERROR_LOG2(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::tx pkt dropped .}", pst_tid_queue->us_mpdu_num, pst_tid_queue->uc_retry_num);
            pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
            oal_dlist_delete_entry(pst_dscr_entry);
            dmac_free_tx_dscr(pst_tx_dscr);
        }
    #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
        return OAL_SUCC;
    }
    else
    {
        /*发送窗口调整*/
        //dmac_ba_addto_baw_multi(pst_tx_ba_handle, uc_mpdu_idx - uc_retry_mpdu_num);
        /*OAM_INFO_LOG4(uc_vap_id, OAM_SF_AMPDU,
                      "{dmac_tid_tx_queue_remove_ampdu::baw info:us_baw_start=%d us_last_seq_num=%d us_baw_head=%d us_baw_tail=%d}",
                      pst_tx_ba_handle->us_baw_start, pst_tx_ba_handle->us_last_seq_num,
                      pst_tx_ba_handle->us_baw_head, pst_tx_ba_handle->us_baw_tail);*/

        /*描述符队列从tid队列移到发送队列中*/
        if (OAL_PTR_NULL != pst_tx_dscr_prev)
        {
            hal_tx_ctrl_dscr_unlink(pst_hal_device, pst_tx_dscr_prev);

    #ifndef _PRE_WLAN_FEATURE_TX_DSCR_OPT
            oal_dlist_remove_head(&st_dscr_head, &(pst_tid_queue->st_hdr), &(pst_tx_dscr_prev->st_entry));
    #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
        }

        /*更新计数*/
        st_ppdu_feature.uc_mpdu_num += uc_mpdu_idx;
        pst_tid_queue->us_mpdu_num -= uc_mpdu_idx;
        pst_dev->us_total_mpdu_num -= uc_mpdu_idx;
        pst_dev->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id] -= uc_mpdu_idx;
        pst_dev->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)] -= uc_mpdu_idx;

        DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_ampdu_cnt, uc_mpdu_idx);
        DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_total_cnt, uc_mpdu_idx);

#ifdef _PRE_PROFILING_MODE
        g_ul_tx_mpdu_num +=uc_mpdu_idx;
        g_ul_tx_ampdu_num ++;
#endif
    }

#ifdef _PRE_DEBUG_MODE
    OAL_DLIST_SEARCH_FOR_EACH(pst_dscr_tra_entry, &st_dscr_head)
    {
        pst_trace_dscr = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dscr_tra_entry, hal_tx_dscr_stru, st_entry);
        OAL_MEM_TRACE(pst_trace_dscr, OAL_FALSE);
    }
#ifdef _PRE_WLAN_FEATURE_AMPDU
//#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB != _PRE_CONFIG_TARGET_PRODUCT) )
#if 0
    /*记录ba handle信息*/
    dmac_ba_track_ba_hander(pst_dev->uc_device_id, pst_tx_ba_handle, pst_tid_queue->uc_tid, OAL_TRUE);
    /*记录tid queue相关信息*/
    dmac_ba_track_tid_queue(pst_dev->uc_device_id, pst_hal_device, pst_tx_ba_handle->uc_tx_ba_lut, pst_tid_queue);
    /*记录调度描述符链信息*/
    dmac_ba_track_schedule_seqnum(pst_dev->uc_device_id, pst_tx_ba_handle->uc_tx_ba_lut, &st_dscr_head);
    /*本次记录完成，更新记录位置*/
    dmac_ba_track_tail_update(pst_dev->uc_device_id, pst_tx_ba_handle->uc_tx_ba_lut);
//#endif
#endif
#endif   /* end of _PRE_WLAN_FEATURE_AMPDU */
#endif   /* end of _PRE_DEBUG_MODE */

    /*OAM_INFO_LOG4(uc_vap_id, OAM_SF_AMPDU,
                  "{dmac_tid_tx_queue_remove_ampdu::baw info after aggr %d %d %d %d.}",
                  pst_tx_ba_handle->us_baw_start, pst_tx_ba_handle->us_last_seq_num,
                  pst_tx_ba_handle->us_baw_head, pst_tx_ba_handle->us_baw_tail);*/

    /* 11ac AMPDU最后一个子MPDU需要有pading */
    if (OAL_UNLIKELY(OAL_PTR_NULL != pst_txop_alg)) {
        if (WLAN_VHT_PHY_PROTOCOL_MODE == pst_txop_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_protocol_mode)
        {
            st_ppdu_feature.ul_ampdu_length += us_pad_len;
        }
    }

    if (DMAC_TX_MODE_RIFS != pst_tid_queue->en_tx_mode)
    {
        st_ppdu_feature.uc_ampdu_enable = OAL_TRUE;
    }
    else
    {
        ul_ret = dmac_tx_rifs_process(pst_hal_device, pst_dmac_vap, pst_tid_queue, &st_ppdu_feature, &st_dscr_head);
        if (OAL_SUCC != ul_ret)
        {
            st_ppdu_feature.uc_ampdu_enable = OAL_TRUE;
        }
    }

    if (OAL_LIKELY(OAL_PTR_NULL != pst_cb_first))
    {
        MAC_GET_CB_MPDU_NUM(pst_cb_first) = st_ppdu_feature.uc_mpdu_num;
    }

    /*OAM_INFO_LOG1(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove_ampdu::st_ppdu_feature uc_mpdu_num=%d.}", st_ppdu_feature.uc_mpdu_num);*/

    OAM_PROFILING_TX_STATISTIC(OAL_PTR_NULL, OAM_PROFILING_FUNC_AMPDU_REMOVE_QUEUE);
    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_AMPDU_REMOVE_QUEUE);

    dmac_tx_data(pst_dmac_vap, pst_user, pst_cb_first, &st_dscr_head, &st_ppdu_feature, pst_txop_alg);

    return OAL_SUCC;
}

oal_uint32  dmac_tid_tx_dequeue(hal_to_dmac_device_stru    *pst_hal_device,
                                        dmac_vap_stru      *pst_dmac_vap,
                                        dmac_tid_stru      *pst_tid_queue,
                                        hal_tx_dscr_stru   *pst_tx_dscr,
                                        mac_device_stru    *pst_dev,
                                        dmac_user_stru     *pst_user)
{
    mac_tx_ctl_stru            *pst_cb;
    oal_netbuf_stru            *pst_netbuf;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    dmac_tid_stats_stru *pst_tid_stats;
    pst_tid_stats = pst_tid_queue->pst_tid_stats;
    if (OAL_PTR_NULL == pst_tid_stats)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tid_tx_dequeue::dequeue from netbuff Q or retry Q failed, pst_tid_stats NULL.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif
#endif

    OAL_MEM_TRACE(pst_tx_dscr, OAL_FALSE);
    pst_tx_dscr->bit_is_first = 0;

    pst_tid_queue->us_mpdu_num--;
    if ((OAL_TRUE == pst_tx_dscr->bit_is_retried) && (pst_tid_queue->uc_retry_num > 0))
    {
        pst_tid_queue->uc_retry_num--;
    }

    DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_normal_cnt, 1);
    DMAC_TID_STATS_INCR(pst_tid_stats->ul_tid_dequeue_total_cnt, 1);

    pst_dev->us_total_mpdu_num--;
    pst_dev->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]--;
    pst_dev->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]--;

    pst_netbuf = pst_tx_dscr->pst_skb_start_addr;
    pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    if (OAL_PTR_NULL == pst_cb)
    {
        OAM_ERROR_LOG0(pst_tid_queue->uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_dequeue::dequeue from netbuff Q or retry Q failed, pst_cb null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    MAC_GET_CB_TX_USER_IDX(pst_cb)  = (oal_uint8)pst_user->st_user_base_info.us_assoc_id;

#ifdef _PRE_WLAN_DFT_STAT
    /* 不是以太网来的不统计 */
    if ((FRW_EVENT_TYPE_HOST_DRX == MAC_GET_CB_EVENT_TYPE(pst_cb))
        && (OAL_TRUE != pst_tx_dscr->bit_is_retried))
    {
        DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_tx_pkts,
                               MAC_GET_CB_NETBUF_NUM(pst_cb));
        DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_tx_bytes,
                                MAC_GET_CB_MPDU_BYTES(pst_cb));
    }

#endif

    /*非重传的qos帧需要软件维护seqnum*/
    if ((OAL_FALSE == pst_tx_dscr->bit_is_retried) && (OAL_TRUE == mac_get_cb_is_qosdata(pst_cb)))
    {
        dmac_save_frag_seq(pst_user, pst_cb);
        dmac_tx_seqnum_set(pst_user, pst_cb);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tid_tx_queue_remove
 功能描述  : 将一个MPDU从TID缓存队列中删除，并发送
 输入参数  : pst_tid_queue: TID缓存队列
             uc_mpdu_num  : 需从tid缓存队列中删除的MPDU个数
 输出参数  : 无
 返 回 值  : OAL_SUCC 或其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月22日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint32  dmac_tid_tx_queue_remove(hal_to_dmac_device_stru   *pst_hal_device,
                                     dmac_vap_stru             *pst_dmac_vap,
                                     dmac_tid_stru             *pst_tid_queue,
                                     oal_uint8                  uc_dscr_num)
{
    mac_device_stru            *pst_dev = OAL_PTR_NULL;
    dmac_user_stru             *pst_user = OAL_PTR_NULL;
    oal_dlist_head_stru        *pst_dscr_entry  = OAL_PTR_NULL;
    hal_tx_dscr_stru           *pst_tx_dscr = OAL_PTR_NULL;
    hal_tx_txop_alg_stru       *pst_txop_alg = OAL_PTR_NULL;
    mac_tx_ctl_stru            *pst_cb = OAL_PTR_NULL;
    oal_netbuf_stru            *pst_netbuf = OAL_PTR_NULL;
    hal_tx_ppdu_feature_stru    st_ppdu_feature;
    oal_uint8                   uc_dscr_idx;
    hal_tx_dscr_stru           *pst_tx_dscr_prev = OAL_PTR_NULL;
    oal_dlist_head_stru         st_dscr_head;
    oal_uint8                   uc_vap_id;
    oal_uint8                   uc_dscr_num_tmp;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    dmac_tid_stats_stru *pst_tid_stats;
    pst_tid_stats = pst_tid_queue->pst_tid_stats;
    if (OAL_PTR_NULL == pst_tid_stats)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tid_tx_queue_remove::tid_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif
#endif
    uc_vap_id = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    pst_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_tid_queue->us_user_idx);
    if (OAL_PTR_NULL == pst_user)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove::pst_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 更新device结构体下的统计信息 */
    pst_dev = mac_res_get_dev(pst_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_dev)
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove::pst_dev null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_dlist_init_head(&st_dscr_head);

    uc_dscr_num_tmp = uc_dscr_num;

    /* 先从重传队列中取 */
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    for (uc_dscr_idx = 0; uc_dscr_idx < uc_dscr_num; uc_dscr_idx++)
    {
        if (OAL_TRUE == oal_dlist_is_empty(&(pst_tid_queue->st_retry_q)))
        {
            break;
        }

        pst_dscr_entry = oal_dlist_delete_head(&(pst_tid_queue->st_retry_q));
        pst_tx_dscr    = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        oal_dlist_add_tail(pst_dscr_entry, &st_dscr_head);

        if (0 != uc_dscr_idx)
        {
            hal_tx_ctrl_dscr_link(pst_hal_device, pst_tx_dscr_prev, pst_tx_dscr);
        }
        pst_tx_dscr_prev = pst_tx_dscr;

        dmac_tid_tx_dequeue(pst_hal_device, pst_dmac_vap, pst_tid_queue, pst_tx_dscr, pst_dev, pst_user);
        pst_netbuf = pst_tx_dscr->pst_skb_start_addr;
        pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    }

    /* 减掉重传报文数 */
    uc_dscr_num -= uc_dscr_idx;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

    /* 再从TID队列取 */
    for (uc_dscr_idx = 0; uc_dscr_idx < uc_dscr_num; uc_dscr_idx++)
    {
    #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        if (OAL_TRUE == oal_netbuf_list_empty(&pst_tid_queue->st_buff_head))
        {
            break;
        }

        pst_netbuf  = dmac_tx_dequeue_first_mpdu(&pst_tid_queue->st_buff_head);
        pst_tx_dscr = dmac_tx_dscr_alloc(pst_hal_device, pst_dmac_vap, pst_netbuf);
        if (OAL_PTR_NULL == pst_tx_dscr)
        {
            OAM_WARNING_LOG3(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove::put the pkt back into tid netbuf Q, alloc tx dscr failed. retry = %d, mpdu = %d, uc_mpdu_num = %d}",
                             pst_tid_queue->uc_retry_num, pst_tid_queue->us_mpdu_num, uc_dscr_num);

            dmac_tx_queue_mpdu(pst_netbuf, &pst_tid_queue->st_buff_head);
            break;
        }
        oal_dlist_add_tail(&pst_tx_dscr->st_entry, &st_dscr_head);
    #else
        /* 如果tid缓存队列为空，程序直接退出 */
        if (oal_dlist_is_empty(&(pst_tid_queue->st_hdr)))
        {
            //OAM_INFO_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove::empty tid.}\r\n");
            break;
        }

        pst_dscr_entry = oal_dlist_delete_head(&(pst_tid_queue->st_hdr));
        pst_tx_dscr    = OAL_DLIST_GET_ENTRY(pst_dscr_entry, hal_tx_dscr_stru, st_entry);
        oal_dlist_add_tail(pst_dscr_entry, &st_dscr_head);

    #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
        if (0 != uc_dscr_idx)
        {
            hal_tx_ctrl_dscr_link(pst_hal_device, pst_tx_dscr_prev, pst_tx_dscr);
        }

        pst_tx_dscr_prev = pst_tx_dscr;

        dmac_tid_tx_dequeue(pst_hal_device, pst_dmac_vap, pst_tid_queue, pst_tx_dscr, pst_dev, pst_user);
        pst_netbuf = pst_tx_dscr->pst_skb_start_addr;
        pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    }

    if (oal_dlist_is_empty(&st_dscr_head))
    {
    #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        /* 描述符优化后，会造成虽然缓存队列有数据包，但由于无更多描述符 */
        OAM_WARNING_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove::no packets can be transmitted.}");
    #else
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove::no packets can be transmitted.}");
    #endif /* */
        return OAL_FAIL;
    }

    if (OAL_PTR_NULL != pst_tx_dscr_prev)
    {
        hal_tx_ctrl_dscr_unlink(pst_hal_device, pst_tx_dscr_prev);
    }

    /* 初始化ppdu feature参数 */
    dmac_tx_init_ppdu_feature(pst_dmac_vap, pst_user, 1, &st_ppdu_feature);
    dmac_tx_update_ppdu_feature(pst_netbuf, &st_ppdu_feature);
    hal_tx_ctrl_dscr_unlink(pst_hal_device, pst_tx_dscr);

    if (OAL_PTR_NULL == pst_cb)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tid_tx_queue_remove::pst_cb null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    MAC_GET_CB_MPDU_NUM(pst_cb) = uc_dscr_num_tmp;
    if (0 == uc_dscr_num_tmp)
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove::tid %d, uc_dscr_num_tmp is zero.}", mac_get_cb_tid(pst_cb));
    }

    /* 获取TXOP算法发送参数 */
    dmac_tx_get_txop_alg_params(pst_dmac_vap, pst_user, pst_cb, &pst_txop_alg);
    if (OAL_PTR_NULL == pst_txop_alg)
    {
        OAM_WARNING_LOG0(uc_vap_id, OAM_SF_TX, "{dmac_tid_tx_queue_remove::pst_txop_alg null.}");
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        if (OAL_PTR_NULL != pst_cb)
        {
            pst_dmac_vap->st_vap_base_info.st_vap_stats.ul_tx_dropped_packets += MAC_GET_CB_NETBUF_NUM(pst_cb);
        }
#endif
        dmac_tx_excp_free_dscr(&st_dscr_head, pst_hal_device);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_cb)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_PROT_NO != pst_dmac_vap->st_vap_base_info.st_protection.en_protection_mode)
    {
        /*保护模式特性更新发送参数*/
        dmac_tx_update_protection_txop_alg(pst_dmac_vap, pst_txop_alg, OAL_FALSE, pst_cb->en_ismcast);
    }

    /* 判断是否强制关闭RTS */
    dmac_judge_forbid_rts(pst_user, pst_txop_alg);

    /* 2040共存特性更新带宽模式 */
    /* dmac_tx_update_bandwidth_mode(pst_dmac_vap, pst_user, pst_txop_alg); */

    OAL_MIPS_TX_STATISTIC(DMAC_PROFILING_FUNC_MPDU_REMOVE_QUEUE);

    dmac_tx_data(pst_dmac_vap, pst_user, pst_cb, &st_dscr_head, &st_ppdu_feature, pst_txop_alg);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_update_protection_lsig_txop
 功能描述  : 更新txop alg中与保护模式相关的lsig txop参数
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
             uc_do_default_cfg: 1: 表示需要恢复配置到默认值，用于在保护模式发送变化时候更改dmac vap结构体下发送参数变量
                                0: 表示不恢复配置到默认值, 仅用于处理算法提供的发送参数
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : c00260463
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_tx_update_protection_lsig_txop(dmac_vap_stru *pst_dmac_vap, hal_tx_txop_alg_stru *pst_txop_alg, oal_uint8 uc_do_default_cfg)
{
    mac_protection_stru          *pst_protection;
    wlan_phy_protocol_enum_uint8  en_protocol_mode;

    en_protocol_mode = pst_txop_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_protocol_mode;
    pst_protection = &(pst_dmac_vap->st_vap_base_info.st_protection);

    /*如果VAP启用了L-SIG TXOP保护机制来做ht保护，并且发送协议模式是HT, 则需要设置发送描述符中bit_lsig_txop置1*/
    if ((OAL_SWITCH_ON == pst_protection->bit_lsig_txop_protect_mode)
         &&(WLAN_HT_PHY_PROTOCOL_MODE == en_protocol_mode))
    {
        pst_txop_alg->st_rate.bit_lsig_txop = OAL_TRUE;
    }
    else
    {
        /*在保护模式发生变化时候需要恢复lsig txop默认值为0*/
        if (OAL_TRUE == uc_do_default_cfg)
        {
            pst_txop_alg->st_rate.bit_lsig_txop = OAL_FALSE;
        }
        else /*其他情况不强制要求bit_lsig_txop置1或置0*/
        {
            /*当入参是算法提供的发送参数时候，不需要对bit_lsig_txop做修改， 保持算法提供值*/
        }
    }

    return OAL_SUCC;
}

/* DTS2015101910770、DTS2015102804770: 由于启用HT和ERP保护模式时, 强制开启RTS导致性能下降,
   因此CCB决策禁用"HT和ERP保护模式强制开RTS功能" */
#if 0
/*****************************************************************************
 函 数 名  : dmac_tx_update_protection_rtscts_enable
 功能描述  : 更新txop alg中与保护模式相关的rts cts enable参数
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
             uc_do_default_cfg: 1: 表示需要恢复配置到默认值，用于在保护模式发送变化时候更改dmac vap结构体下发送参数变量
                                0: 表示不恢复配置到默认值, 仅用于处理算法提供的发送参数
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : c00260463
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_tx_update_protection_rtscts_enable(dmac_vap_stru *pst_dmac_vap, hal_tx_txop_alg_stru *pst_txop_alg, oal_uint8 uc_do_default_cfg, oal_bool_enum_uint8 en_mcast)
{
    mac_protection_stru          *pst_protection;
    wlan_phy_protocol_enum_uint8  en_protocol_mode;
    oal_uint8                     uc_rts_cts_enable = 0xFF;

    en_protocol_mode = pst_txop_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_protocol_mode;
    pst_protection = &(pst_dmac_vap->st_vap_base_info.st_protection);

    /*如果VAP启用了RTS-CTS机制来做erp保护， 并且发送协议模式不是11b, 则需要设置发送描述符中bit_rts_cts_enable置1*/
    if ((WLAN_PROT_ERP == pst_protection->en_protection_mode)
         &&(OAL_SWITCH_ON == pst_protection->bit_rts_cts_protect_mode)
         && (WLAN_11B_PHY_PROTOCOL_MODE != en_protocol_mode))
    {
        uc_rts_cts_enable = OAL_TRUE;
    }

    /*如果VAP启用了RTS-CTS机制来做ht保护， 并且发送协议模式是HT或VHT, 则需要设置发送描述符中bit_rts_cts_enable置1*/
    else if ((WLAN_PROT_HT == pst_protection->en_protection_mode)
         && (OAL_SWITCH_ON == pst_protection->bit_rts_cts_protect_mode)
         && ((WLAN_HT_PHY_PROTOCOL_MODE == en_protocol_mode) || (WLAN_VHT_PHY_PROTOCOL_MODE == en_protocol_mode)))
    {
        uc_rts_cts_enable = OAL_TRUE;
    }
    else
    {
        /*在保护模式发生变化时候需要恢复bit_rts_cts_enable默认值为0*/
        if (OAL_TRUE == uc_do_default_cfg)
        {
            uc_rts_cts_enable = OAL_FALSE;
        }
        else /*其他情况不强制要求bit_lsig_txop置1或置0*/
        {
            /*当入参是算法提供的发送参数时候，不需要对bit_rts_cts_enable做修改， 保持算法提供值*/
        }
    }

    /* 避免发出广播RTS */
    if (en_mcast == OAL_TRUE)
    {
        uc_rts_cts_enable = OAL_FALSE;
    }

    /*OAM_INFO_LOG2(0, OAM_SF_TX, "{dmac_tx_update_protection_rtscts_enable::rts_cts_enable=%d en_protocol_mode=%d}",
                        uc_rts_cts_enable, en_protocol_mode);*/

    /*uc_rts_cts_enable不为0xFF时候，则说明需要修改bit_rts_cts_enable的值*/
    if (0xFF != uc_rts_cts_enable)
    {
        pst_txop_alg->ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable = uc_rts_cts_enable;
        pst_txop_alg->ast_per_rate[1].rate_bit_stru.bit_rts_cts_enable = uc_rts_cts_enable;
        pst_txop_alg->ast_per_rate[2].rate_bit_stru.bit_rts_cts_enable = uc_rts_cts_enable;
        pst_txop_alg->ast_per_rate[3].rate_bit_stru.bit_rts_cts_enable = uc_rts_cts_enable;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_tx_update_protection_preamble_mode
 功能描述  : 更新txop alg中与保护模式相关的preamble_mode参数
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
             uc_do_default_cfg: 1: 表示需要恢复配置到默认值，用于在保护模式发送变化时候更改dmac vap结构体下发送参数变量
                                0: 表示不恢复配置到默认值, 仅用于处理算法提供的发送参数
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : c00260463
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_tx_update_protection_preamble_mode(dmac_vap_stru *pst_dmac_vap, hal_tx_txop_alg_stru *pst_txop_alg, oal_uint8 uc_do_default_cfg)
{
    dmac_user_stru               *pst_dmac_user;
    mac_protection_stru          *pst_protection;
    wlan_phy_protocol_enum_uint8  en_protocol_mode;
    oal_uint8                     uc_preamble_mode = 0;
    oal_uint8                     uc_rate_index = 0;
    oal_uint8                     uc_legacy_rate = 0;

    pst_protection = &(pst_dmac_vap->st_vap_base_info.st_protection);

    for(uc_rate_index = 0; uc_rate_index < HAL_TX_RATE_MAX_NUM; uc_rate_index++)
    {
        /*如果发送count为0， 则说明本级速率无效*/
        if (0 == pst_txop_alg->ast_per_rate[uc_rate_index].rate_bit_stru.bit_tx_count)
        {
            continue;
        }

        uc_preamble_mode = 0xFF;
        en_protocol_mode = pst_txop_alg->ast_per_rate[uc_rate_index].rate_bit_stru.un_nss_rate.st_ht_rate.bit_protocol_mode;
        uc_legacy_rate   = pst_txop_alg->ast_per_rate[uc_rate_index].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate;

        /*11b协议下， 确认是否需要设置long preamble*/
        if (WLAN_11B_PHY_PROTOCOL_MODE == en_protocol_mode)
        {
            /*VAP 为 AP情况下*/
            if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
            {
                /* 如果有不支持short preamble站点与AP关联， 或者AP自身不支持short preamble，或者发送率为1mpbs，则需要设置AP使用long preamble方式发送管理帧*/
                if ((0 != pst_protection->uc_sta_no_short_preamble_num)
                     || (OAL_TRUE != mac_mib_get_ShortPreambleOptionImplemented(&(pst_dmac_vap->st_vap_base_info)))
                     || (WLAN_PHY_RATE_1M == uc_legacy_rate))
                {
                    uc_preamble_mode = WLAN_LEGACY_11B_DSCR_LONG_PREAMBLE;
                }
                else
                {
                    /*在保护模式发生变化时候需要恢复为默认值short preamble*/
                    if (OAL_TRUE == uc_do_default_cfg)
                    {
                        uc_preamble_mode = WLAN_LEGACY_11B_DSCR_SHORT_PREAMBLE;
                    }
                    else /*其他情况不做强制要求*/
                    {
                        /*当入参是算法提供的发送参数时候，不需要对uc_preamble_mode做修改， 保持算法提供值*/
                    }
                }

            }
            else/*VAP 为 STA情况下*/
            {
                pst_dmac_user = mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id); /*user保存的是AP的信息*/
                if (OAL_PTR_NULL == pst_dmac_user)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_update_protection_preamble_mode::pst_dmac_user null, assoc_vap_id [%d].}",
                                    pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }

                /* 如果接收到beacon帧中携带的ERP信息元素中baker preamble mode为1， 或者STA自身不支持short preamble， 则需要设置STA使用long preamble方式发送管理帧*/
                if ((OAL_TRUE == pst_dmac_user->st_user_base_info.st_cap_info.bit_barker_preamble_mode)
                      || (OAL_TRUE != mac_mib_get_ShortPreambleOptionImplemented(&(pst_dmac_vap->st_vap_base_info)))
                      || (WLAN_PHY_RATE_1M == uc_legacy_rate))
                {
                    uc_preamble_mode = WLAN_LEGACY_11B_DSCR_LONG_PREAMBLE;
                }
                else
                {
                    /*在保护模式发生变化时候需要恢复为默认值short preamble*/
                    if (OAL_TRUE == uc_do_default_cfg)
                    {
                        uc_preamble_mode = WLAN_LEGACY_11B_DSCR_SHORT_PREAMBLE;
                    }
                    else /*其他情况不做强制要求*/
                    {
                        /*当入参是算法提供的发送参数时候，不需要对uc_preamble_mode做修改， 保持算法提供值*/
                    }
                }
            }
        }
        /*HT协议下*/
        else if (WLAN_HT_PHY_PROTOCOL_MODE == en_protocol_mode)
        {
            /*启用了GF保护时候， 管理帧发送需要设置为MF前导码发送*/
            if (WLAN_PROT_GF == pst_protection->en_protection_mode)
            {
                uc_preamble_mode = OAL_FALSE;
            }
            else
            {
                /*在保护模式发生变化时候需要恢复为默认值,1151方案目前默认就是用MF前导码发送*/
                if (OAL_TRUE == uc_do_default_cfg)
                {
                    uc_preamble_mode = OAL_FALSE;
                }
                else /*其他情况不做强制要求*/
                {
                    /*当入参是算法提供的发送参数时候，不需要对uc_preamble_mode做修改， 保持算法提供值*/
                }
            }
        }
        else /*其他协议模式下preamble为0*/
        {
            uc_preamble_mode = 0;
        }

        if(0xFF != uc_preamble_mode)
        {
            pst_txop_alg->ast_per_rate[uc_rate_index].rate_bit_stru.bit_preamble_mode = uc_preamble_mode;
        }

    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_update_protection_txop_alg
 功能描述  : 更新txop alg中与保护模式相关的参数
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 *puc_param
             uc_do_default_cfg: 1: 表示需要恢复配置到默认值，用于在保护模式发送变化时候更改dmac vap结构体下发送参数变量
                                0: 表示不恢复配置到默认值, 仅用于处理算法提供的发送参数

 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月18日
    作    者   : c00260463
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_tx_update_protection_txop_alg(dmac_vap_stru *pst_dmac_vap, hal_tx_txop_alg_stru *pst_txop_alg, oal_uint8 uc_do_default_cfg, oal_bool_enum_uint8 en_mcast)
{
    oal_uint32 ul_ret = OAL_SUCC;

    /*更新lsig txop参数*/
    dmac_tx_update_protection_lsig_txop(pst_dmac_vap, pst_txop_alg, uc_do_default_cfg);

    /* DTS2015101910770、DTS2015102804770: 由于启用HT和ERP保护模式时, 强制开启RTS导致性能下降,
       因此CCB决策禁用"HT和ERP保护模式强制开RTS功能" */
#if 0
    /*更新rts cts enable参数*/
    dmac_tx_update_protection_rtscts_enable(pst_dmac_vap, pst_txop_alg, uc_do_default_cfg, en_mcast);
#endif

    /*更新preamble参数*/
    ul_ret = dmac_tx_update_protection_preamble_mode(pst_dmac_vap, pst_txop_alg, uc_do_default_cfg);

    return ul_ret;
}
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

/*****************************************************************************
 函 数 名  : dmac_tx_clear_tx_queue
 功能描述  : 删除tx队列中的所有帧，同时清空硬件FIFO
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月29日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_clear_tx_queue(hal_to_dmac_device_stru *pst_hal_device)
{
    oal_uint8            uc_q_id            = 0;
    oal_dlist_head_stru *pst_dlist_entry    = OAL_PTR_NULL;
    hal_tx_dscr_stru    *pst_tx_dscr        = OAL_PTR_NULL;
    oal_uint8            uc_loop_idx        = 0;

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_clear_tx_queue::pst_hal_device null.}");

        return OAL_FAIL;
    }

    pst_hal_device->bit_clear_fifo_st = OAL_TRUE;
    hal_clear_hw_fifo(pst_hal_device);

    /*首先清空发送完成事件队列*/
    frw_event_flush_event_queue(FRW_EVENT_TYPE_WLAN_TX_COMP);

    /* 遍历5个发送队列 一定要先处理高优先级队列防止普通优先级队列发送完成产生管理帧入错队列 */
    for (uc_loop_idx = 0; uc_loop_idx <= HAL_TX_QUEUE_HI; uc_loop_idx++)
    {
        uc_q_id = HAL_TX_QUEUE_HI - uc_loop_idx;
        while(!oal_dlist_is_empty(&pst_hal_device->ast_tx_dscr_queue[uc_q_id].st_header))
        {
            pst_dlist_entry = pst_hal_device->ast_tx_dscr_queue[uc_q_id].st_header.pst_next;

            pst_tx_dscr     = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_entry, hal_tx_dscr_stru, st_entry);

            dmac_tx_complete_free_dscr(pst_tx_dscr);
        }

        pst_hal_device->ast_tx_dscr_queue[uc_q_id].uc_ppdu_cnt = 0;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_proc_save_tx_queue
 功能描述  : 操作将发送队列中的缓存至目标虚假队列中
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月3日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_proc_save_tx_queue(hal_to_dmac_device_stru       *pst_hal_device,
                                            hal_tx_dscr_queue_header_stru *pst_fake_queue)
{
    oal_uint8            uc_q_id            = 0;
    oal_dlist_head_stru *pst_dlist_entry    = OAL_PTR_NULL;
    hal_tx_dscr_stru    *pst_tx_dscr        = OAL_PTR_NULL;
    hal_tx_dscr_stru    *pst_tx_dscr_tmp    = OAL_PTR_NULL;
    oal_uint8            uc_tx_status;
    mac_tx_ctl_stru     *pst_cb;
    oal_netbuf_stru     *pst_buf;


    /*
     * 遍历5个发送队列 一定要先处理非管理帧队列，防止普通优先级队列发送完成产生管理帧(BAR)入错队列
     * 保险起见，另启循环独立save。
     *
     * 此处有两种情形:
     *  1、发送完成事件已经入队列，若该AMPDU发送失败，则会在flush event时发送BAR，
     *     BAR直接入硬件队列(应为还未切信道)，而后被save
     *  2、save过程中，发现发送失败的AMPDU，强调irq loss，产生BAR，该BAR直接入硬件队列，
     *     而后被本函数最后的交换操作save，因此必须最后处理管理帧队列。
     */
    /* DTS2015031608823，0在02是BE，在51是BK队列 */
    for (uc_q_id = 0; uc_q_id <= HAL_TX_QUEUE_HI; uc_q_id++)
    {
        while(!oal_dlist_is_empty(&pst_hal_device->ast_tx_dscr_queue[uc_q_id].st_header))
        {
            pst_dlist_entry = pst_hal_device->ast_tx_dscr_queue[uc_q_id].st_header.pst_next;

            pst_tx_dscr     = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_entry, hal_tx_dscr_stru, st_entry);
            if(OAL_PTR_NULL == pst_tx_dscr)
            {
                OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_save_tx_queue::pst_tx_dscr poiter is null.}");
                break;
            }
            hal_tx_get_dscr_status(pst_hal_device, pst_tx_dscr, &uc_tx_status);

            // 据王浩介绍，聚合帧中各子帧的status并不一定都是9，因此需要各个处理
            // 另外，假如软件不清除某个单帧的status，那么硬件不会为之更新seq number
            if (DMAC_TX_PENDING == uc_tx_status)
            {
                pst_buf = pst_tx_dscr->pst_skb_start_addr;
                pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);
                (MAC_GET_CB_RETRIED_NUM(pst_cb))++;

                if (MAC_GET_CB_RETRIED_NUM(pst_cb) > DMAC_MAX_PENDING_RETRY)
                {
                    OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_save_tx_queue::retry cnt=%d, break}", MAC_GET_CB_RETRIED_NUM(pst_cb));
                    dmac_tx_complete_buff(pst_hal_device, pst_tx_dscr);
                    break;
                }

                pst_tx_dscr_tmp  = pst_tx_dscr;
                do
                {
                    pst_tx_dscr_tmp->bit_is_retried = OAL_TRUE;
#if 0
                    hal_tx_set_dscr_seqno_sw_generate(pst_hal_device, pst_tx_dscr_tmp, 1);
#else
                    hal_tx_set_dscr_seqno_sw_generate(pst_hal_device, pst_tx_dscr_tmp, 0);
#endif
                    hal_tx_set_dscr_status(pst_hal_device, pst_tx_dscr_tmp, DMAC_TX_INVALID);
                    hal_get_tx_dscr_next(pst_hal_device, pst_tx_dscr_tmp, &pst_tx_dscr_tmp);
                }while(OAL_PTR_NULL != pst_tx_dscr_tmp);

                break; // 认定不可能同时传输两个帧
            }
            else if (DMAC_TX_INVALID != uc_tx_status)
            {
                dmac_tx_complete_buff(pst_hal_device, pst_tx_dscr);

                continue;
            }
            else
            {
                break;
            }
        }
    }

    /* DTS2015031608823，0在02是BE，在51是BK队列 */
    for (uc_q_id = 0; uc_q_id <= HAL_TX_QUEUE_HI; uc_q_id++)
    {
        /* 将硬件队列里的内容放到虚假队列中去 */
        oal_dlist_join_head(&pst_fake_queue[uc_q_id].st_header, &pst_hal_device->ast_tx_dscr_queue[uc_q_id].st_header);
        pst_fake_queue[uc_q_id].uc_ppdu_cnt += pst_hal_device->ast_tx_dscr_queue[uc_q_id].uc_ppdu_cnt;

        oal_dlist_init_head(&pst_hal_device->ast_tx_dscr_queue[uc_q_id].st_header);
        pst_hal_device->ast_tx_dscr_queue[uc_q_id].uc_ppdu_cnt = 0;
    }

    return;
}

/*****************************************************************************
 函 数 名  : dmac_tx_save_tx_queue
 功能描述  : 将发送队列中的缓存至虚假发送队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月3日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_save_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id)
{
    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        MAC_ERR_LOG(0, "pst_hal_device is null");
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_save_tx_queue::pst_hal_device null.}");

        return OAL_FAIL;
    }

    if (OAL_UNLIKELY(uc_fake_q_id >= HAL_TX_FAKE_QUEUE_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "dmac_tx_save_tx_queue: uc_fake_q_id is invalid, %d", uc_fake_q_id);
        return OAL_FAIL;
    }

    dmac_proc_save_tx_queue(pst_hal_device, pst_hal_device->ast_tx_dscr_queue_fake[uc_fake_q_id]);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_clear_fake_queue
 功能描述  : 清除虚假缓存队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_clear_fake_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id)
{
    hal_tx_dscr_queue_header_stru  *pst_fake_queue;
    oal_uint8                       uc_q_id;
    oal_uint8                       uc_loop_idx;
    oal_dlist_head_stru            *pst_dlist_entry;
    hal_tx_dscr_stru               *pst_tx_dscr;

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "pst_hal_device is null.}");
        return OAL_FAIL;
    }

    if (OAL_UNLIKELY(uc_fake_q_id >= HAL_TX_FAKE_QUEUE_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "uc_fake_q_id is invalid, %d", uc_fake_q_id);
        return OAL_FAIL;
    }

    pst_fake_queue = pst_hal_device->ast_tx_dscr_queue_fake[uc_fake_q_id];

    /* 遍历5个发送队列 一定要先处理高优先级队列防止普通优先级队列发送完成产生管理帧入错队列 */
    for (uc_loop_idx = 0; uc_loop_idx <= HAL_TX_QUEUE_HI; uc_loop_idx++)
    {
        uc_q_id = HAL_TX_QUEUE_HI - uc_loop_idx;

        while(!oal_dlist_is_empty(&pst_fake_queue[uc_q_id].st_header))
        {
            pst_dlist_entry = pst_fake_queue[uc_q_id].st_header.pst_next;

            pst_tx_dscr     = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_entry, hal_tx_dscr_stru, st_entry);

            dmac_tx_complete_free_dscr(pst_tx_dscr);
        }

        pst_fake_queue[uc_q_id].uc_ppdu_cnt = 0;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_fake_queue_empty_assert
 功能描述  : 虚假队列不为空时打印error
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月18日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_fake_queue_empty_assert(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_fake_q,
                oal_uint32               ul_file_id)
{
    hal_tx_dscr_queue_header_stru  *pst_fake_queue;
    oal_uint8                       uc_q_idx;
    oal_dlist_head_stru            *pst_dlist_entry;
    hal_tx_dscr_stru               *pst_tx_dscr;
    oal_netbuf_stru                *pst_netbuf;
    oal_uint8                       auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xff,0xff,0xff,0xff,0xff,0xff};
    mac_tx_ctl_stru                *pst_tx_ctl;
    oal_uint32                      ul_ret = OAL_TRUE;

    pst_fake_queue = pst_hal_device->ast_tx_dscr_queue_fake[uc_fake_q];

    for (uc_q_idx = 0; uc_q_idx < HAL_TX_QUEUE_BUTT; uc_q_idx++)
    {
        if (!oal_dlist_is_empty(&pst_fake_queue[uc_q_idx].st_header))
        {
            /* 虚假队列不为空，将第一个帧通过OTA上报上来 */

            pst_dlist_entry = pst_fake_queue[uc_q_idx].st_header.pst_next;
            pst_tx_dscr     = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_entry, hal_tx_dscr_stru, st_entry);
            oam_report_dscr(auc_user_macaddr, (oal_uint8 *)pst_tx_dscr, WLAN_MEM_SHARED_TX_DSCR_SIZE1, OAM_OTA_TYPE_TX_DSCR);

            pst_netbuf = pst_tx_dscr->pst_skb_start_addr;

            pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

            oam_report_80211_frame(auc_user_macaddr,
                                    (oal_uint8*)mac_get_cb_frame_hdr(pst_tx_ctl),
                                    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl),
                                    (oal_uint8*)oal_netbuf_payload(pst_netbuf),
                                    MAC_GET_CB_MPDU_LEN(pst_tx_ctl),
                                    OAM_OTA_FRAME_DIRECTION_TYPE_TX);

            OAM_ERROR_LOG4(0, OAM_SF_DBAC, "fake q is not empty. q_id:%d, ac:%d, file_id:%d, ppdu_cnt:%d",
                            uc_fake_q, uc_q_idx, ul_file_id, pst_fake_queue[uc_q_idx].uc_ppdu_cnt);
            ul_ret = OAL_FALSE;
        }
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_tx_switch_tx_queue
 功能描述  : 交换两个虚假队列里的帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月7日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tx_switch_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id1, oal_uint8 uc_fake_q_id2)
{
    oal_uint8                       uc_q_idx;
    oal_uint8                       uc_ppdu_num;
    hal_tx_dscr_queue_header_stru  *pst_fake_queue1;
    hal_tx_dscr_queue_header_stru  *pst_fake_queue2;
    oal_dlist_head_stru             st_head_tmp;

    pst_fake_queue1 = pst_hal_device->ast_tx_dscr_queue_fake[uc_fake_q_id1];
    pst_fake_queue2 = pst_hal_device->ast_tx_dscr_queue_fake[uc_fake_q_id2];

    for (uc_q_idx = 0; uc_q_idx < HAL_TX_QUEUE_BUTT; uc_q_idx++)
    {
        oal_dlist_init_head(&st_head_tmp);
        oal_dlist_join_head(&st_head_tmp, &pst_fake_queue1[uc_q_idx].st_header);

        oal_dlist_init_head(&pst_fake_queue1[uc_q_idx].st_header);
        oal_dlist_join_head(&pst_fake_queue1[uc_q_idx].st_header, &pst_fake_queue2[uc_q_idx].st_header);

        oal_dlist_init_head(&pst_fake_queue2[uc_q_idx].st_header);
        oal_dlist_join_head(&pst_fake_queue2[uc_q_idx].st_header, &st_head_tmp);

        uc_ppdu_num                           = pst_fake_queue1[uc_q_idx].uc_ppdu_cnt;
        pst_fake_queue1[uc_q_idx].uc_ppdu_cnt = pst_fake_queue2[uc_q_idx].uc_ppdu_cnt;
        pst_fake_queue2[uc_q_idx].uc_ppdu_cnt = uc_ppdu_num;
    }

    return OAL_SUCC;
}


#if 0
/*****************************************************************************
 函 数 名  : dmac_flush_txq_to_tid
 功能描述  : 将发送队列中的报文放回tid队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月3日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_flush_txq_to_tid(hal_to_dmac_device_stru *pst_hal_device)
{
    oal_uint8            uc_q_idx           = 0;
    oal_dlist_head_stru *pst_dlist_entry    = OAL_PTR_NULL;
    hal_tx_dscr_stru    *pst_tx_dscr        = OAL_PTR_NULL;
    mac_tx_ctl_stru     *pst_cb             = OAL_PTR_NULL;
    dmac_tid_stru       *pst_tid            = OAL_PTR_NULL;
    dmac_user_stru      *pst_dmac_user      = OAL_PTR_NULL;
    mac_device_stru     *pst_mac_device;
#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    mac_vap_stru        *pst_vap            = OAL_PTR_NULL;
#endif

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        MAC_ERR_LOG(0, "pst_hal_device is null");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_flush_txq_to_tid::pst_hal_device null.}");

        return OAL_FAIL;
    }

    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        MAC_ERR_LOG(0, "pst_mac_device is null");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_flush_txq_to_tid::pst_mac_device null.}");

        return OAL_FAIL;
    }

    /* 遍历高优先级发送队列并释放所有未发送的管理帧 */
    while(!oal_dlist_is_empty(&pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_HI].st_header))
    {
        pst_dlist_entry = oal_dlist_delete_tail(&pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_HI].st_header);
        pst_tx_dscr     = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_entry, hal_tx_dscr_stru, st_entry);
        oal_netbuf_free(pst_tx_dscr->pst_skb_start_addr);
        OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);
    }

    /* 遍历其余4个发送队列 */
    for (uc_q_idx = 0; uc_q_idx < HAL_TX_QUEUE_HI; uc_q_idx++)
    {
        if (!oal_dlist_is_empty(&pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header))
        {
            dmac_tx_dump_data(pst_hal_device, pst_cb, &pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header);
        }

        /* 将发送队列下的报文塞回对应的tid缓存队列 */
        while(!oal_dlist_is_empty(&pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header))
        {
            pst_dlist_entry = oal_dlist_delete_tail(&pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header);

            if(pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt == 0)
            {
                MAC_ERR_VAR(0, "hw queue%d.len == 0\n", uc_q_idx);
                OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_flush_txq_to_tid::uc_q_idx=%d.}", uc_q_idx);

                continue;
            }
            pst_tx_dscr     = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_entry, hal_tx_dscr_stru, st_entry);

            pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_tx_dscr->pst_skb_start_addr);

            pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_CB_TX_USER_IDX(pst_cb));
            pst_tid       = &pst_dmac_user->ast_tx_tid_queue[mac_get_cb_tid(pst_cb)];

            oal_dlist_add_head(pst_dlist_entry, &pst_tid->st_hdr);
            pst_tid->us_mpdu_num++;
            pst_mac_device->us_total_mpdu_num++;
            pst_mac_device->aus_vap_mpdu_num[pst_tid->uc_vap_id]++;
            pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid->uc_tid)]++;
#ifdef _PRE_WLAN_FEATURE_FLOWCTL
            pst_vap = mac_res_get_mac_vap(pst_tid->uc_vap_id);
            dmac_alg_flowctl_backp_notify(pst_vap, pst_mac_device->us_total_mpdu_num, pst_mac_device->aus_ac_mpdu_num);
#endif
        }

        pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt = 0;
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_flush_txq_to_tid_of_vo
 功能描述  : 回收bk,be,vi,vo队列的数据回tid为6的队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月3日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_flush_txq_to_tid_of_vo(hal_to_dmac_device_stru *pst_hal_device)
{
    oal_uint8            uc_q_idx           = 0;
    oal_dlist_head_stru *pst_dlist_entry    = OAL_PTR_NULL;
    hal_tx_dscr_stru    *pst_tx_dscr        = OAL_PTR_NULL;
    mac_tx_ctl_stru     *pst_cb             = OAL_PTR_NULL;
    dmac_tid_stru       *pst_tid            = OAL_PTR_NULL;
    dmac_user_stru      *pst_dmac_user      = OAL_PTR_NULL;
    mac_device_stru                     *pst_mac_device;
    mac_ieee80211_qos_htc_frame_stru *pst_frame_head = OAL_PTR_NULL;
#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    mac_vap_stru        *pst_vap            = OAL_PTR_NULL;
#endif
    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        MAC_ERR_LOG(0, "pst_hal_device is null");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_flush_txq_to_tid_of_vo::pst_hal_device null.}");

        return OAL_FAIL;
    }

    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_device_id);
    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        MAC_ERR_LOG(0, "pst_mac_device is null");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_flush_txq_to_tid_of_vo::pst_mac_device null.}");

        return OAL_FAIL;
    }

    /* 遍历其余4个发送队列 */
    for (uc_q_idx = 0; uc_q_idx < HAL_TX_QUEUE_HI; uc_q_idx++)
    {
        /* 将发送队列下的报文塞回对应的tid缓存队列 */
        while(!oal_dlist_is_empty(&pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header))
        {
            pst_dlist_entry = oal_dlist_delete_tail(&pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header);
            pst_tx_dscr     = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_entry, hal_tx_dscr_stru, st_entry);

            pst_cb = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_tx_dscr->pst_skb_start_addr);

            pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_CB_TX_USER_IDX(pst_cb));
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_flush_txq_to_tid_of_vo::mac_res_get_dmac_user fail.user_idx = %u}",MAC_GET_CB_TX_USER_IDX(pst_cb));
                continue;
            }
            /* 修改描述符和cb里edca相关的字段 */
            pst_tx_dscr->uc_q_num = HAL_TX_QUEUE_VO;
            mac_set_cb_tid(pst_cb, MAC_WMM_SWITCH_TID);
            mac_set_cb_ac(pst_cb, WLAN_WME_AC_VO);
            /* 修改帧头的tid */
            pst_frame_head = (mac_ieee80211_qos_htc_frame_stru *)mac_get_cb_frame_hdr(pst_cb);
            pst_frame_head->bit_qc_tid = MAC_WMM_SWITCH_TID;

            /* 关闭WMM前，将所有Q回收到TID为6的队列 */
            pst_tid       = &pst_dmac_user->ast_tx_tid_queue[MAC_WMM_SWITCH_TID];
        #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
            pst_tx_dscr->bit_is_retried = OAL_TRUE;
            oal_dlist_add_head(pst_dlist_entry, &pst_tid->st_retry_q);
        #else
            oal_dlist_add_head(pst_dlist_entry, &pst_tid->st_hdr);
        #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
            pst_tid->us_mpdu_num++;
            pst_mac_device->us_total_mpdu_num++;
            pst_mac_device->aus_vap_mpdu_num[pst_tid->uc_vap_id]++;
            pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid->uc_tid)]++;
#ifdef _PRE_WLAN_FEATURE_FLOWCTL
            pst_vap = mac_res_get_mac_vap(pst_tid->uc_vap_id);
            dmac_alg_flowctl_backp_notify(pst_vap, pst_mac_device->us_total_mpdu_num, pst_mac_device->aus_ac_mpdu_num);
#endif
        }
        pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt = 0;
    }


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tx_update_protection_all_txop_alg
 功能描述  : 更新所有txop alg结构体中与保护模式相关的参数
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
    2.日    期   : 2015年4月6日
      作    者   : l00311403
      修改内容   : 当为组播/广播时，dmac_tx_update_protection_txop_alg
                   的参数en_mcast由OAL_FALSE变成OAL_TRUE
*****************************************************************************/
oal_uint32  dmac_tx_update_protection_all_txop_alg(dmac_vap_stru *pst_dmac_vap)
{
    if(OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_TX, "{dmac_tx_update_protection_all_txop_alg::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*更新单播数据帧txop alg参数*/
    dmac_tx_update_protection_txop_alg(pst_dmac_vap, &(pst_dmac_vap->st_tx_alg), OAL_TRUE, OAL_FALSE);

    /*更新组播数据帧txop alg参数*/
    dmac_tx_update_protection_txop_alg(pst_dmac_vap, &(pst_dmac_vap->st_tx_data_mcast), OAL_TRUE, OAL_TRUE);

     /*更新广播数据帧txop alg参数*/
    dmac_tx_update_protection_txop_alg(pst_dmac_vap, &(pst_dmac_vap->st_tx_data_bcast), OAL_TRUE, OAL_TRUE);

    /*更新单播管理帧txop alg参数*/
    dmac_tx_update_protection_txop_alg(pst_dmac_vap, &(pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G]), OAL_TRUE, OAL_TRUE);

    dmac_tx_update_protection_txop_alg(pst_dmac_vap, &(pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G]), OAL_TRUE, OAL_TRUE);

    /*更新组播广播管理帧txop alg参数*/
    dmac_tx_update_protection_txop_alg(pst_dmac_vap, &(pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G]), OAL_TRUE, OAL_TRUE);

    dmac_tx_update_protection_txop_alg(pst_dmac_vap, &(pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G]), OAL_TRUE, OAL_TRUE);

    return OAL_SUCC;
}

#if defined (_PRE_WLAN_FEATURE_UAPSD) || defined (_PRE_WLAN_FEATURE_STA_PM)
/*****************************************************************************
 函 数 名  : dmac_send_qosnull
 功能描述  : 组帧并发送Qos null帧
 输入参数  : pst_dmac_vap :dmac vap结构体指针
             pst_dmac_user :dmac user结构体指针
             en_ps :节能位是否设置
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2014年7月3日
    作    者   : z00273164
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32 dmac_send_qosnull(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_ac, oal_bool_enum_uint8 en_ps)
{
    oal_netbuf_stru                 *pst_net_buf;
    mac_tx_ctl_stru                 *pst_tx_ctrl;
    oal_uint32                       ul_ret;
    mac_ieee80211_qos_frame_stru    *pst_mac_header;
    oal_uint16                       us_tx_direction = WLAN_FRAME_FROME_AP;
    /* 入参检查 */
    if ((OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_KEEPALIVE, "{dmac_uapsd_send_qosnull:: func input  is null.}");
        return OAL_ERR_CODE_KEEPALIVE_PTR_NULL;
    }
    if (uc_ac >= MAC_AC_PARAM_LEN)
    {
        OAM_ERROR_LOG1(0, OAM_SF_KEEPALIVE, "{dmac_uapsd_send_qosnull:: uc_ac %d is too large.}", uc_ac);
        return OAL_FAIL;
    }
    /* 申请net_buff */
    pst_net_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_uapsd_send_qosnull::pst_net_buf failed.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    OAL_MEM_NETBUF_TRACE(pst_net_buf, OAL_TRUE);
    oal_set_netbuf_prev(pst_net_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);
    /* null帧发送方向From AP || To AP */
    us_tx_direction = (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode) ? WLAN_FRAME_FROME_AP : WLAN_FRAME_TO_AP;
    /* 填写帧头 */
    OAL_MEMZERO(OAL_NETBUF_HEADER(pst_net_buf), OAL_SIZEOF(mac_ieee80211_qos_frame_stru));
    mac_null_data_encap(OAL_NETBUF_HEADER(pst_net_buf),
                        ((oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS_NULL) | us_tx_direction),
                        pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                        pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    pst_mac_header = (mac_ieee80211_qos_frame_stru*)OAL_NETBUF_HEADER(pst_net_buf);
    pst_mac_header->bit_qc_tid = WLAN_WME_AC_TO_TID(uc_ac);
    pst_mac_header->bit_qc_eosp = 0;
    pst_mac_header->st_frame_control.bit_power_mgmt = en_ps;

    /*协议规定单播的QOS NULL DATA只允许normal ack*/
    pst_mac_header->bit_qc_ack_polocy = WLAN_TX_NORMAL_ACK;
    /* 填写cb字段 */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    OAL_MEMZERO(pst_tx_ctrl, OAL_SIZEOF(mac_tx_ctl_stru));
    /* 填写tx部分 */
    mac_set_cb_is_qosdata(pst_tx_ctrl, OAL_TRUE);
    mac_set_cb_ack_policy(pst_tx_ctrl, WLAN_TX_NORMAL_ACK);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctrl)      = FRW_EVENT_TYPE_WLAN_DTX;
    mac_set_cb_is_bar(pst_tx_ctrl, OAL_FALSE);
    mac_set_cb_ac(pst_tx_ctrl,uc_ac);
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl)    = OAL_TRUE;
    MAC_GET_CB_RETRIED_NUM(pst_tx_ctrl)      = 0;
    mac_set_cb_tid(pst_tx_ctrl, WLAN_WME_AC_TO_TID(uc_ac));
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctrl)     = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)      = (oal_uint8)pst_dmac_user->st_user_base_info.us_assoc_id;
    /* 填写tx rx公共部分 */
    //MAC_GET_CB_FRAME_TYPE(pst_tx_ctrl)              = WLAN_DATA_NULL;
    MAC_GET_CB_IS_MCAST(pst_tx_ctrl)                = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_ctrl, OAL_FALSE);
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)       = OAL_FALSE;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctrl)           = OAL_FALSE;
    mac_set_cb_is_use_4_addr(pst_tx_ctrl, OAL_FALSE);
    mac_set_cb_frame_hdr(pst_tx_ctrl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)     = OAL_SIZEOF(mac_ieee80211_qos_frame_stru);
    MAC_GET_CB_MPDU_NUM(pst_tx_ctrl)                = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl)              = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctrl)                = 0;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)             = (oal_uint8)pst_dmac_user->st_user_base_info.us_assoc_id;
    //MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctrl)        = 1;/* NULL帧软重传10次 */
    ul_ret = dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_net_buf);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_KEEPALIVE,
                       "{dmac_uapsd_send_qosnull::dmac_tx_process_data failed[%d].}", ul_ret);
        dmac_tx_excp_free_netbuf(pst_net_buf);
        return ul_ret;
    }
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_alg_tid_update_notify
 功能描述  : 更新TID队列时回调算法
 输入参数  : pst_tid: TID结构体
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月20日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_alg_downlink_flowctl_notify(mac_vap_stru *pst_vap,
                                                                mac_user_stru *pst_user,
                                                                oal_netbuf_stru *pst_buf)
{
    oal_uint32                         ul_ret;
    dmac_txrx_output_type_enum_uint8   en_output;
    mac_device_stru                   *pst_mac_device;
    dmac_vap_stru               *pst_dmac_vap;

    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device) || (OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_downlink_flowctl_notify::pst_mac_device  or pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 不用拥塞控制算法 进行判断(当tx buffer使用完以后，后来的报文直接丢弃) */
    if (OAL_PTR_NULL == gst_alg_main.p_downlink_flowctl_func)
    {
        if( WLAN_TID_MPDU_NUM_LIMIT <= pst_mac_device->us_total_mpdu_num)
        {
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ACS, "tx buffer is full[%d],the coming buffer drop", pst_mac_device->us_total_mpdu_num);
            return OAL_FAIL;
        }
        else
        {
            return OAL_SUCC;
        }
    }
    else
    {
        /* 多用户多优先级跑流时不使能拥塞控制 */
        if (OAL_FALSE == pst_dmac_vap->en_multi_user_multi_ac_flag)
        {
            /* 根据拥塞控制算法 判断报文是否丢弃 */
            ul_ret = gst_alg_main.p_downlink_flowctl_func(pst_vap, pst_user, pst_buf, &en_output);
            if ((OAL_SUCC != ul_ret)||(DMAC_TXRX_DROP == en_output))
            {
                OAM_INFO_LOG2(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_alg_downlink_flowctl_notify::ul_ret=%d, en_output=%d}",
                              ul_ret, en_output);
                return OAL_FAIL;
            }
        }
	return OAL_SUCC;
    }

}

/*lint -e578*//*lint -e19*/
#if 0
oal_module_symbol(dmac_flush_txq_to_tid);
#endif
oal_module_symbol(dmac_tx_save_tx_queue);
oal_module_symbol(dmac_tx_clear_fake_queue);
oal_module_symbol(dmac_tx_restore_tx_queue);
oal_module_symbol(dmac_tx_switch_tx_queue);
oal_module_symbol(dmac_tx_process_data_event);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_module_symbol(dmac_tx_training_data);
#endif
oal_module_symbol(dmac_tx_mgmt);
oal_module_symbol(dmac_tx_clear_tx_queue);
oal_module_symbol(dmac_alg_downlink_flowctl_notify);
oal_module_symbol(dmac_tx_fake_queue_empty_assert);
/*lint +e578*//*lint +e19*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

