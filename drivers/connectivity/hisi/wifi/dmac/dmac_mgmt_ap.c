/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_mgmt_ap.c
  版 本 号   : 初稿
  作    者   : zhangheng
  生成日期   : 2013年6月7日
  最近修改   :
  功能描述   : AP侧管理帧处理
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
#include "mac_resource.h"
#include "dmac_main.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_mgmt_ap.h"
#include "oal_net.h"
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_AP_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_mgmt_encap_probe_response
 功能描述  : 封装probe response帧
 输入参数  : pst_dmac_vap: DMAC vap
             puc_buffer  : probe response帧内存
             puc_ra      : 接收地址
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint16  dmac_mgmt_encap_probe_response(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint8 *puc_ra, oal_bool_enum_uint8 en_is_p2p_req)
{
    oal_uint8        uc_ie_len = 0;
    mac_vap_stru    *pst_mac_vap    = &(pst_dmac_vap->st_vap_base_info);
    oal_uint8       *puc_mac_header = oal_netbuf_header(pst_netbuf);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8       *puc_payload_addr        = oal_netbuf_data(pst_netbuf);
#else
    oal_uint8       *puc_payload_addr        = puc_mac_header + MAC_80211_FRAME_LEN;
#endif
    oal_uint8       *puc_payload_addr_origin = puc_payload_addr;
    oal_uint16       us_app_ie_len;

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
    mac_hdr_set_frame_control(puc_mac_header, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_PROBE_RSP);

    /* 设置地址1为发送probe request帧的STA */
    if(OAL_PTR_NULL != puc_ra)
    {
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR1_OFFSET, puc_ra);
    }
#ifdef _PRE_WLAN_FEATURE_P2P
    if (dmac_vap_is_in_p2p_listen(&(pst_dmac_vap->st_vap_base_info)))
    {
        /* 设置地址2为自己的MAC地址 */
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);

        /* 设置地址3为bssid */
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);
    }
    else
#endif
    {
        /* 设置地址2为自己的MAC地址 */
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR2_OFFSET, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        /* 设置地址3为bssid */
        oal_set_mac_addr(puc_mac_header + WLAN_HDR_ADDR3_OFFSET, pst_dmac_vap->st_vap_base_info.auc_bssid);
    }

    /* 设置分片序号, 管理帧为0 */
    mac_hdr_set_fragment_number(puc_mac_header, 0);

    /*************************************************************************/
    /*                  Probe Response Frame - Frame Body                    */
    /* ----------------------------------------------------------------------*/
    /* |Timestamp|BcnInt|CapInfo|SSID|SupRates|DSParamSet      |CountryElem |*/
    /* ----------------------------------------------------------------------*/
    /* |8        |2     |2      |2-34|3-10    |3               |8-256       |*/
    /* ----------------------------------------------------------------------*/
    /* |PowerConstraint |Quiet|TPC Report|ERP |RSN  |WMM |Extended Sup Rates|*/
    /* ----------------------------------------------------------------------*/
    /* |3               |8    |4         |3   |4-255|26  | 3-257            |*/
    /* ----------------------------------------------------------------------*/
    /* |BSS Load |HT Capabilities |HT Operation |Overlapping BSS Scan       |*/
    /* ----------------------------------------------------------------------*/
    /* |7        |28              |24           |16                         |*/
    /* ----------------------------------------------------------------------*/
    /* |Extended Capabilities |                                              */
    /* ----------------------------------------------------------------------*/
    /* |3-8                   |                                              */
    /*************************************************************************/
    /* Initialize index */
    //puc_buffer += MAC_80211_FRAME_LEN + MAC_TIME_STAMP_LEN;
    puc_payload_addr += MAC_TIME_STAMP_LEN;

    /* 设置beacon interval */
    mac_set_beacon_interval_field(pst_mac_vap, puc_payload_addr);
    puc_payload_addr += MAC_BEACON_INTERVAL_LEN;

    /* 设置capability information */
    dmac_set_cap_info_field(pst_mac_vap, puc_payload_addr);
    puc_payload_addr += MAC_CAP_INFO_LEN;

    /* 设置ssid element */
#ifdef _PRE_WLAN_FEATURE_P2P
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        mac_set_p2p0_ssid_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len, WLAN_FC0_SUBTYPE_PROBE_RSP);
        puc_payload_addr += uc_ie_len;
    }
    else
#endif
    {
        mac_set_ssid_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len, WLAN_FC0_SUBTYPE_PROBE_RSP);
        puc_payload_addr += uc_ie_len;
    }

    /* 设置支持的速率集 */
    mac_set_supported_rates_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 设置dsss参数集 */
    mac_set_dsss_params(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

#ifdef _PRE_WLAN_FEATURE_11D
    /* 填充country信息 */
    mac_set_country_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;
#endif

    /* 填充power constraint信息 */
    mac_set_pwrconstraint_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 填充quiet信息 */
    mac_set_quiet_ie(pst_mac_vap, puc_payload_addr, MAC_QUIET_COUNT, MAC_QUIET_PERIOD,
                     MAC_QUIET_DURATION, MAC_QUIET_OFFSET, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 填充TPC Report信息 */
    mac_set_tpc_report_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 填充erp信息 */
    mac_set_erp_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

#if defined(_PRE_WLAN_FEATURE_WPA2)
    /* 填充WPA2 安全相关信息 */
    mac_set_security_ie_authenticator(pst_mac_vap, puc_payload_addr, &uc_ie_len, DMAC_RSNA_802_11I);
    puc_payload_addr += uc_ie_len;
#endif /* (_PRE_WLAN_FEATURE_WPA2) */

#if defined (_PRE_WLAN_FEATURE_WPA)
    /* 填充WPA 安全相关信息 */
    mac_set_security_ie_authenticator(pst_mac_vap, puc_payload_addr, &uc_ie_len, DMAC_WPA_802_11I);
    puc_payload_addr += uc_ie_len;
#endif /* (_PRE_WLAN_FEATURE_WPA) */

    /* 填充wmm信息 */
    //mac_set_wmm_params_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    mac_set_wmm_params_ie(pst_mac_vap, puc_payload_addr, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 填充extended supported rates信息 */
    mac_set_exsup_rates_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 填充bss load信息 */
    mac_set_bssload_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

   /* 填充HT Capabilities信息 */
   mac_set_ht_capabilities_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
   puc_payload_addr += uc_ie_len;

   /* 填充HT Operation信息 */
   mac_set_ht_opern_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
   puc_payload_addr += uc_ie_len;

    /* 填充Overlapping BSS Scan信息 */
    mac_set_obss_scan_params(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 填充Extended Capabilities信息 */
    mac_set_ext_capabilities_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 填充vht cap信息 */
    mac_set_vht_capabilities_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;

    /* 填充vht opern信息 */
    mac_set_vht_opern_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;
#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_set_11ntxbf_vendor_ie(pst_mac_vap, puc_payload_addr, &uc_ie_len);
    puc_payload_addr += uc_ie_len;
#endif

    if(OAL_TRUE == en_is_p2p_req)
    {
        /* 填充WPS P2P信息 */
        mac_add_app_ie((oal_void *)pst_mac_vap, puc_payload_addr, &us_app_ie_len, OAL_APP_PROBE_RSP_IE);
    }
    else
    {
        /* 对于非p2p 设备发起的扫描，回复probe resp 帧不能携带p2p ie 信息，回复WPS 信息 */
        mac_add_wps_ie((oal_void *)pst_mac_vap, puc_payload_addr, &us_app_ie_len, OAL_APP_PROBE_RSP_IE);
    }
    puc_payload_addr += us_app_ie_len;

#ifdef _PRE_WLAN_FEATURE_P2P
    /* 填充p2p noa Attribute*/
    if((OAL_TRUE == en_is_p2p_req)&&
        (IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
        (IS_P2P_NOA_ENABLED(pst_dmac_vap) || IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
    {
        mac_set_p2p_noa(pst_mac_vap, puc_payload_addr, &uc_ie_len);
        puc_payload_addr += uc_ie_len;
    }
#endif

    return (oal_uint16)(puc_payload_addr - puc_payload_addr_origin + MAC_80211_FRAME_LEN);
}

/*****************************************************************************
 函 数 名  : dmac_ap_check_ssid
 功能描述  : 检查ssid正确性
 输入参数  : pst_dmac_vap           : dmac vap
             puc_probe_req_ssid     : 收到关联请求中所含ssid
 输出参数  : 无
 返 回 值  : 成功/失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月3日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_ap_check_ssid(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_probe_req_ssid)
{
    oal_uint8           uc_prb_req_ssid_len;
    oal_uint8           uc_ssid_len;
    oal_uint8          *puc_ssid;
    oal_uint8          *puc_prb_req_ssid;
    oal_uint8           uc_hide_ssid;

    uc_prb_req_ssid_len = puc_probe_req_ssid[1];
    puc_prb_req_ssid    = &puc_probe_req_ssid[MAC_IE_HDR_LEN];
#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P device 检查ssid 是否为"DIRECT-"
        P2P GO 需要和AP 一样，检查probe req ssid 内容 */
    if (IS_P2P_CL(&pst_dmac_vap->st_vap_base_info)|| IS_P2P_DEV(&pst_dmac_vap->st_vap_base_info))
    {
        if (IS_P2P_WILDCARD_SSID(puc_prb_req_ssid, uc_prb_req_ssid_len))
        {
            return OAL_SUCC;
        }
        else
        {
            return OAL_FAIL;
        }
    }

    /* begin: DTS2015071604582 GO 接收到probe req 携带ssid 内容为DIRECT- ， 需要回复probe rsp 帧 */
    if (IS_P2P_GO(&pst_dmac_vap->st_vap_base_info) && IS_P2P_WILDCARD_SSID(puc_prb_req_ssid, uc_prb_req_ssid_len))
    {
        return OAL_SUCC;
    }
    /* end: DTS2015071604582 GO 接收到probe req 携带ssid 内容为DIRECT- ， 需要回复probe rsp 帧 */
#endif

    puc_ssid = pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID;
    uc_hide_ssid = pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_hide_ssid;


    if(0 == uc_prb_req_ssid_len)
    {
        /* 隐藏ssid配置下，不接受ssid len为0的情况 */
        if(uc_hide_ssid)
        {
            //OAM_INFO_LOG0(0, OAM_SF_SCAN, "{dmac_ap_check_ssid::hide_ssid && ssid len==0 .}");
            return OAL_FAIL;
        }
        return OAL_SUCC;
    }

    uc_ssid_len = (oal_uint8)OAL_STRLEN((oal_int8*)puc_ssid);
    if (uc_prb_req_ssid_len != uc_ssid_len)
    {
        return OAL_FAIL;
    }

    return ((0 == oal_memcmp(&puc_probe_req_ssid[MAC_IE_HDR_LEN], puc_ssid, uc_prb_req_ssid_len)) ? OAL_SUCC : OAL_FAIL);
    /* return OAL_SUCC; */

}

/*****************************************************************************
 函 数 名  : dmac_ap_check_probe_req
 功能描述  : 检测probe request帧，判断是否要发probe response帧
 输入参数  : pst_dmac_vap  : 指向DMAC VAP
             puc_probe_req : probe request帧帧体
             puc_bssid     : probe request帧帧头 地址3，bssid
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  dmac_ap_check_probe_req(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_probe_req, oal_uint8 *puc_bssid)
{
    if(OAL_SUCC != dmac_ap_check_ssid(pst_dmac_vap, puc_probe_req))
    {
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_ap_check_probe_req::probe req check ssid error.}\r\n");
        return OAL_FALSE;
    }

    /* 检查probe request帧中的bssid是不是本AP的bssid或者广播地址 */
    if ((0 != oal_compare_mac_addr(BROADCAST_MACADDR, puc_bssid)) &&
        (0 != oal_compare_mac_addr(pst_dmac_vap->st_vap_base_info.auc_bssid, puc_bssid)))
    {
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_ap_check_probe_req::probe req check ssid err.}\r\n");
        return OAL_FALSE;
    }

    return OAL_TRUE;
}


/*****************************************************************************
 函 数 名  : dmac_ap_up_rx_probe_req
 功能描述  : AP在UP状态下接收到probe req帧处理
 输入参数  : pst_dmac_vap: dmac vap
             pst_netbuf: 接收到的net buffer
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_ap_up_rx_probe_req(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    oal_netbuf_stru            *pst_mgmt_buf;
    oal_uint16                  us_mgmt_len;
    oal_uint8                  *puc_probe_req;
    mac_tx_ctl_stru            *pst_tx_ctl;
    dmac_rx_ctl_stru           *pst_rx_ctl;
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    oal_uint32                  ul_ret;
    oal_uint16                  us_frame_len;
    oal_bool_enum_uint8         en_is_p2p_req = OAL_FALSE;

    /* 获取帧头信息 */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info)));
    puc_probe_req = MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctl->st_rx_info), pst_netbuf);
    us_frame_len  = (oal_uint16)oal_netbuf_get_len(pst_netbuf);

#ifdef _PRE_WLAN_FEATURE_DBAC
    dmac_alg_probe_req_rx_notify(pst_dmac_vap, pst_netbuf);
#endif

    if (OAL_FALSE == dmac_ap_check_probe_req(pst_dmac_vap, puc_probe_req, pst_frame_hdr->auc_address3))
    {
        return OAL_SUCC;
    }

    /* 申请管理帧内存 */
    pst_mgmt_buf = OAL_MEM_NETBUF_ALLOC(OAL_MGMT_NETBUF, WLAN_MGMT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_mgmt_buf)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_ap_up_rx_probe_req::pst_mgmt_buf null.}");
        /* device netbuf 申请不到维测，以后删除， l00324381 20150902 */
        OAL_MEM_INFO_PRINT(OAL_MEM_POOL_ID_NETBUF);
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_set_netbuf_prev(pst_mgmt_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_mgmt_buf, OAL_PTR_NULL);

    OAL_MEM_NETBUF_TRACE(pst_mgmt_buf, OAL_TRUE);

    /* 收到的probe req 帧包含P2P_IE */
    en_is_p2p_req = (OAL_PTR_NULL != mac_find_vendor_ie(MAC_WLAN_OUI_WFA, MAC_WLAN_OUI_TYPE_WFA_P2P, puc_probe_req, us_frame_len)) ? OAL_TRUE : OAL_FALSE;
    /* 封装probe request帧 */
    us_mgmt_len = dmac_mgmt_encap_probe_response(pst_dmac_vap, pst_mgmt_buf, pst_frame_hdr->auc_address2, en_is_p2p_req);

    /* 调用发送管理帧接口 */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_buf);

    OAL_MEMZERO(pst_tx_ctl, sizeof(mac_tx_ctl_stru));
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)              = MAX_TX_USER_IDX;       /* 此时对端用户不存在，填一个非法值，发送完成会直接释放 */
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)              = OAL_FALSE;
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_mgmt_buf, us_mgmt_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_ap_up_rx_probe_req::dmac_tx_mgmt failed[%d].", ul_ret);
        oal_netbuf_free(pst_mgmt_buf);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_ap_up_rx_generate_chtxt
 功能描述  : 为接收到的seq = 1 的shared key认证帧弄一个challenge text
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月28日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_ap_up_rx_generate_chtxt(dmac_vap_stru                 *pst_dmac_vap,
                                                    oal_netbuf_stru                *pst_netbuf,
                                                    frw_event_mem_stru             *pst_event_mem)
{
    dmac_wlan_crx_event_stru  *pst_rx_auth_event;
    oal_uint8                  auc_chtxt[WLAN_CHTXT_SIZE] = {0};
    oal_uint8                  uc_chtxt_index;
    frw_event_stru            *pst_event;
    frw_event_hdr_stru        *pst_event_hdr;

    pst_event           = (frw_event_stru *)(pst_event_mem->puc_data);
    pst_event_hdr       = &pst_event->st_event_hdr;

    if (WLAN_WITP_AUTH_SHARED_KEY == mac_get_auth_algo_num(pst_netbuf))
    {
        /* 获取challenge text */
        for (uc_chtxt_index = 0; uc_chtxt_index < WLAN_CHTXT_SIZE; uc_chtxt_index++)
        {
             hal_get_random_byte(&auc_chtxt[uc_chtxt_index]);
        }
    }

    /* 继承事件，并且修改事件头，暂时未区分STA和AP模式 */
    FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX);

    pst_rx_auth_event = (dmac_wlan_crx_event_stru *)(pst_event->auc_event_data);
    pst_rx_auth_event->pst_netbuf = pst_netbuf;
    pst_rx_auth_event->puc_chtxt  = auc_chtxt;

    /* 分发 */
    return frw_event_dispatch_event(pst_event_mem);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

