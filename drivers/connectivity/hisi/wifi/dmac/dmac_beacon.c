/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_beacon.c
  版 本 号   : 初稿
  作    者   : zhangheng
  生成日期   : 2013年3月28日
  最近修改   :
  功能描述   : Beacon帧组帧 发送
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月28日
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
#include "wlan_spec.h"
#include "wlan_types.h"

#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "oam_main.h"

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#include "pm_extern.h"
#endif

#include "hal_ext_if.h"
#include "mac_frame.h"
#include "mac_ie.h"
#include "mac_vap.h"
#include "mac_frame.h"


#include "dmac_main.h"
#include "dmac_device.h"
#include "dmac_beacon.h"
#include "dmac_chan_mgmt.h"
#include "dmac_psm_ap.h"
#include "dmac_mgmt_sta.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_device.h"
#include "dmac_scan.h"
#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#include "dmac_lpm_test.h"
#endif
#ifdef _PRE_WLAN_DFT_STAT
#include "mac_device.h"
#include "dmac_dft.h"
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#include "dmac_sta_pm.h"
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "dmac_reset.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BEACON_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef _PRE_WLAN_CHIP_TEST
static dmac_beacon_test_stru g_beacon_offload_test; /*仅用于测试*/
#endif

/* wlan远场近场/p2p linkloss门限 */
dmac_beacon_linkloss_stru g_st_beacon_linkloss = {40, 100, 40, {0},};
#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_uint16 g_us_occupied_point[BTCOEX_LINKLOSS_OCCUPIED_NUMBER];
#endif
#define RX_DATA_RATE                            (50000) /* 50M */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
extern oal_uint8  dmac_psm_is_tid_queues_empty(dmac_vap_stru  *pst_dmac_vap);

/*****************************************************************************
 函 数 名  : dmac_init_dtim_count_ap
 功能描述  : 初始化设置DTIM count为DTIM period -1;次函数需在beacon alloc时，
             encap beacon前调用，否则会造成 Beacon 的第一帧的DTIM count 不正常
 输入参数  : pst_dmac_vap: 指向vap结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : lixiaochuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_init_dtim_count_ap(dmac_vap_stru *pst_dmac_vap)
{
    if (0 == pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_init_dtim_count_ap::DTIM period error!}");
        return;
    }
    pst_dmac_vap->uc_dtim_count = (oal_uint8)(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod - 1);
}

/*****************************************************************************
 函 数 名  : dmac_update_dtim_count_ap
 功能描述  : 在tbtt中断中，更新dtim count，保证每次tbtt中断来，dtim count自
             动减1
 输入参数  : dmac_vap_stru *pst_dmac_vap
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : lixiaochuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_update_dtim_count_ap(dmac_vap_stru *pst_dmac_vap)
{
    /* 将vap中保存的dtim_count值赋给DTIM Count字段，每次都会减1，在区间[0,DTIM_period]中循环 */
    if (0 == pst_dmac_vap->uc_dtim_count)
    {
        pst_dmac_vap->uc_dtim_count = (oal_uint8)(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod - 1);
    }
    else
    {
        pst_dmac_vap->uc_dtim_count--;
    }
}

/*****************************************************************************
 函 数 名  : dmac_set_tim_ie
 功能描述  : vap启动时以及每次tbtt中断，ap把本地的tim_bitmap拷贝到beacon帧里的
             TIM信息元素空间
 输入参数  : pst_vap: 指向vap
             puc_buffer: 指向buffer
 输出参数  : puc_ie_len: element的长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月11日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_set_tim_ie(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
    dmac_vap_stru  *pst_dmac_vap;
    oal_uint8       uc_tim_offset = 0;
    oal_uint8       uc_PVBitmap_len;

    /***************************************************************************
     ---------------------------------------------------------------------------
     |EID |Len |DTIM Count |DTIM Period |Bitmap Control |Partial Virtual Bitmap|
     ---------------------------------------------------------------------------
     |1   |1   |1          |1           |1              |1~251                 |
     ---------------------------------------------------------------------------
    ***************************************************************************/

    pst_dmac_vap = (dmac_vap_stru *)pst_vap;

    uc_PVBitmap_len  = pst_dmac_vap->puc_tim_bitmap[0];
    uc_tim_offset    = 2 + (pst_dmac_vap->puc_tim_bitmap[1] & (oal_uint8)(~BIT0));
    if (uc_PVBitmap_len + uc_tim_offset > pst_dmac_vap->uc_tim_bitmap_len)
    {
        OAM_ERROR_LOG3(0, OAM_SF_WIFI_BEACON, "{dmac_set_tim_ie::puc_tim_bitmap[0x%x] = 0x%x bitmap_len[%d] .}",
                       pst_dmac_vap->puc_tim_bitmap, OAL_NTOH_32(*(oal_uint32 *)(pst_dmac_vap->puc_tim_bitmap)), pst_dmac_vap->uc_tim_bitmap_len);
        uc_PVBitmap_len = 1;
    }

    puc_buffer[0] = MAC_EID_TIM;
    puc_buffer[1] = uc_PVBitmap_len + MAC_TIM_LEN_EXCEPT_PVB;
    puc_buffer[2] = pst_dmac_vap->uc_dtim_count;
    puc_buffer[3] = (oal_uint8)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod;
    puc_buffer[4] = pst_dmac_vap->puc_tim_bitmap[1];

    /* 保存Beacon帧中DTIM Control bit0的值，用于下次TBTT中断到来时来判断是否需要发送缓存广播和组播帧 */
    pst_dmac_vap->en_dtim_ctrl_bit0 = (oal_bool_enum_uint8)(pst_dmac_vap->puc_tim_bitmap[1] & BIT0);

    /* 将vap本地的bitmap不为0的部分复制到beacon帧相应空间，作为Partial Virtual Bitmap */
    oal_memcopy(&puc_buffer[5], pst_dmac_vap->puc_tim_bitmap + uc_tim_offset, uc_PVBitmap_len);


    *puc_ie_len = MAC_IE_HDR_LEN + MAC_TIM_LEN_EXCEPT_PVB + uc_PVBitmap_len;
}

/*****************************************************************************
 函 数 名  : dmac_encap_beacon
 功能描述  : beacon帧组帧
 输入参数  : pst_dmac_vap  : 指向vap的结构体
             puc_beacon_buf: 指向beacon buffer
 输出参数  : puc_beacon_len: beacon帧的长度
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_encap_beacon(
                dmac_vap_stru               *pst_dmac_vap,
                oal_uint8                   *puc_beacon_buf,
                oal_uint16                  *pus_beacon_len)
{

    oal_uint8        uc_ie_len;
    oal_uint8       *puc_bf_origin = puc_beacon_buf;
    mac_device_stru *pst_mac_device;
    mac_vap_stru    *pst_mac_vap;
    oal_uint16       us_app_ie_len = 0;

    if (puc_beacon_buf == OAL_PTR_NULL)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_encap_beacon::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/
    /* 设置Frame Control字段 */
    mac_hdr_set_frame_control(puc_beacon_buf, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_BEACON);

    /* 设置duration为0，由硬件填 */
    mac_hdr_set_duration(puc_beacon_buf, 0);

    /* 设置address1, DA是一个广播地址 */
    oal_memcopy(puc_beacon_buf + WLAN_HDR_ADDR1_OFFSET, BROADCAST_MACADDR, WLAN_MAC_ADDR_LEN);

    /* 设置address2，SA是mac地址 */
    oal_memcopy(puc_beacon_buf + WLAN_HDR_ADDR2_OFFSET,
                pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                WLAN_MAC_ADDR_LEN);

    /* 设置address3, BSSID */
    oal_memcopy(puc_beacon_buf + WLAN_HDR_ADDR3_OFFSET,
                pst_dmac_vap->st_vap_base_info.auc_bssid,
                WLAN_MAC_ADDR_LEN);

    /* 设置分片序号为0，beacon帧没有sequence number */
    mac_hdr_set_fragment_number(puc_beacon_buf, 0);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*                       Beacon Frame - Frame Body                       */
    /* ----------------------------------------------------------------------*/
    /* |Timestamp|BcnInt|CapInfo|SSID|SupRates|DSParamSet|TIM  |CountryElem |*/
    /* ----------------------------------------------------------------------*/
    /* |8        |2     |2      |2-34|3-10    |3         |6-256|8-256       |*/
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
    /* timestamp由硬件设置 */
    puc_beacon_buf += MAC_80211_FRAME_LEN;
    OAL_MEMZERO(puc_beacon_buf, 8);

    /* Initialize index */
    puc_beacon_buf += MAC_TIME_STAMP_LEN;

    /* 设置beacon interval */
    mac_set_beacon_interval_field(pst_mac_vap, puc_beacon_buf);
    puc_beacon_buf += MAC_BEACON_INTERVAL_LEN;

    /* 设置capability information */
    mac_set_cap_info_ap(pst_mac_vap, puc_beacon_buf);
    puc_beacon_buf += MAC_CAP_INFO_LEN;

    /* 设置ssid element,如果打开隐藏ssid开关的话，则不填ssid */
    mac_set_ssid_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len, WLAN_FC0_SUBTYPE_BEACON);
    puc_beacon_buf += uc_ie_len;

    /* 设置支持的速率集 */
    mac_set_supported_rates_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 设置dsss参数集 */
    mac_set_dsss_params(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;
    /* 更新TIM信息元素在beacon帧中的偏移 */
    pst_dmac_vap->uc_tim_offset_in_beacon = (oal_uint8)(puc_beacon_buf - puc_bf_origin);

    /* 填充tim信息 */
    dmac_set_tim_ie(pst_dmac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

#ifdef _PRE_WLAN_FEATURE_11D
    /* 填充country信息 */
    mac_set_country_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;
#endif

#ifdef _PRE_WLAN_FEATURE_11AC2G
    mac_set_vendor_hisi_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

#endif

    /* 填充power constraint信息 */
    mac_set_pwrconstraint_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充quiet信息 */
    mac_set_quiet_ie(pst_mac_vap, puc_beacon_buf, MAC_QUIET_COUNT, MAC_QUIET_PERIOD,
                      MAC_QUIET_DURATION, MAC_QUIET_OFFSET, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充TPC Report信息 */
    mac_set_tpc_report_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充erp信息 */
    mac_set_erp_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

#if defined(_PRE_WLAN_FEATURE_WPA2)
    /* 填充WPA2 安全相关信息 */
    mac_set_security_ie_authenticator(pst_mac_vap, puc_beacon_buf, &uc_ie_len, DMAC_RSNA_802_11I);
    puc_beacon_buf += uc_ie_len;
#endif /* (_PRE_WLAN_FEATURE_WPA2) */

#if defined (_PRE_WLAN_FEATURE_WPA)
    /* 填充WPA 安全相关信息 */
    mac_set_security_ie_authenticator(pst_mac_vap, puc_beacon_buf, &uc_ie_len, DMAC_WPA_802_11I);
    puc_beacon_buf += uc_ie_len;
#endif /* (_PRE_WLAN_FEATURE_WPA) */

    /* 填充wmm信息 */
    //mac_set_wmm_params_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    mac_set_wmm_params_ie(pst_mac_vap, puc_beacon_buf, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充extended supported rates信息 */
    mac_set_exsup_rates_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充bss load信息 */
    mac_set_bssload_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充HT Capabilities信息 */
    mac_set_ht_capabilities_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充HT Operation信息 */
    mac_set_ht_opern_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充Overlapping BSS Scan信息 */
    mac_set_obss_scan_params(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充Extended Capabilities信息 */
    mac_set_ext_capabilities_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充vht cap信息 */
    mac_set_vht_capabilities_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充vht opern信息 */
    mac_set_vht_opern_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;

    /* 填充CSA IE */

    if (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_csa_present_in_bcn)
    {
        mac_set_csa_ie(pst_mac_vap->st_ch_switch_info.uc_announced_channel,
                   pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt,
                   puc_beacon_buf, &uc_ie_len);
        puc_beacon_buf += uc_ie_len;
    }

#ifdef _PRE_WLAN_CHIP_TEST
    if (1 == g_beacon_offload_test.uc_csa_in_beacon)
    {
        mac_set_csa_ie(g_beacon_offload_test.uc_announced_channel,
                   g_beacon_offload_test.uc_switch_cnt,
                   puc_beacon_buf, &uc_ie_len);
        puc_beacon_buf += uc_ie_len;
    }
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    if (1 == g_beacon_offload_test.uc_opmode_in_beacon)
    {
        puc_beacon_buf[0] = MAC_EID_OPMODE_NOTIFY;
        puc_beacon_buf[1] = MAC_OPMODE_NOTIFY_LEN;
        puc_beacon_buf[2] = g_beacon_offload_test.uc_opmode;
        puc_beacon_buf += (MAC_IE_HDR_LEN + MAC_OPMODE_NOTIFY_LEN);
    }
#endif
#endif
#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_set_11ntxbf_vendor_ie(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
    puc_beacon_buf += uc_ie_len;
#endif

    /* 填充WPS信息 */
    mac_add_app_ie((oal_void *)pst_mac_vap, puc_beacon_buf, &us_app_ie_len, OAL_APP_BEACON_IE);
    puc_beacon_buf += us_app_ie_len;

#ifdef _PRE_WLAN_FEATURE_P2P
    /* 填充p2p noa Attribute*/
    if((IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
        (IS_P2P_NOA_ENABLED(pst_dmac_vap) || IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
    {
        mac_set_p2p_noa(pst_mac_vap, puc_beacon_buf, &uc_ie_len);
        puc_beacon_buf += uc_ie_len;
    }
#endif
    *pus_beacon_len = (oal_uint16)(puc_beacon_buf - puc_bf_origin);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_beacon_alloc
 功能描述  : 申请beacon帧内存
 输入参数  : pst_dmac_vap: 指向vap结构体
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_beacon_alloc(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8                  *pauc_beacon_buf[DMAC_VAP_BEACON_BUFFER_BUTT];
    oal_uint16                  us_beacon_len = 0;
    hal_beacon_tx_params_stru   st_beacon_tx_params;
    hal_tx_txop_alg_stru       *pst_tx_param;
    wlan_channel_band_enum_uint8 en_band;

    /* 目前acs会把up的vap做一次wait再up，这个时候beacon帧在第一次up的时候内存已经申请，这里再次进入时直接返回即可 */
    if((OAL_PTR_NULL != pst_dmac_vap->pauc_beacon_buffer[0]) && (OAL_PTR_NULL != pst_dmac_vap->pauc_beacon_buffer[1]))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_beacon_alloc::vap beacon buf has been alloc.}\r\n");
        return OAL_SUCC;
    }

    /* 申请第一个beacon帧内存 */
    pauc_beacon_buf[0] = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_MGMT_PKT, WLAN_MEM_SHARED_MGMT_PKT_SIZE1, OAL_TRUE);
    if (OAL_PTR_NULL == pauc_beacon_buf[0])
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_beacon_alloc::pauc_beacon_buf[0] null.}");

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* 申请第二个beacon帧内存 */
    pauc_beacon_buf[1] = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_MGMT_PKT, WLAN_MEM_SHARED_MGMT_PKT_SIZE1, OAL_TRUE);
    if (OAL_PTR_NULL == pauc_beacon_buf[1])
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_beacon_alloc::pauc_beacon_buf[1] null.}");

        /* 释放已申请的内存 */
        OAL_MEM_FREE(pauc_beacon_buf[0], OAL_TRUE);
        pauc_beacon_buf[0] = OAL_PTR_NULL;

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* 第一次初始化DTIM count,规范化使其从period -1开始 */
    dmac_init_dtim_count_ap(pst_dmac_vap);

    /* 初始beacon组帧 */
    dmac_encap_beacon(pst_dmac_vap, pauc_beacon_buf[0], &us_beacon_len);

    oal_memcopy(pauc_beacon_buf[1], pauc_beacon_buf[0], us_beacon_len);

    /* 将beacon帧挂到vap上 */
    pst_dmac_vap->pauc_beacon_buffer[0] = pauc_beacon_buf[0];
    pst_dmac_vap->pauc_beacon_buffer[1] = pauc_beacon_buf[1];

    pst_dmac_vap->uc_beacon_idx = 0;    /* 初始化放入硬件的beacon帧索引 */
    pst_dmac_vap->us_beacon_len = us_beacon_len;

    /* 填写发送Beacon帧参数 */
    en_band  = pst_dmac_vap->st_vap_base_info.st_channel.en_band;
    pst_tx_param = &pst_dmac_vap->ast_tx_mgmt_bmcast[en_band];
    pst_tx_param->ast_per_rate[0].rate_bit_stru.bit_reserve = 0;

    st_beacon_tx_params.ul_pkt_ptr   = (oal_uint32)((pauc_beacon_buf[0]));
    st_beacon_tx_params.us_pkt_len   = us_beacon_len;
    st_beacon_tx_params.pst_tx_param = pst_tx_param;

    /* 设置beacon period */
    hal_vap_set_machw_beacon_period(pst_dmac_vap->pst_hal_vap, (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);

    /* 判断是否开启了双路轮流发送 */
    if(1 == pst_dmac_vap->en_beacon_chain_active)
    {
        /* 第一个beacon帧由通道0发送，第二个beacon帧由通道1发送 */
        if(pst_dmac_vap->uc_beacon_idx == DMAC_VAP_BEACON_BUFFER1)
        {
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
        }
        else
        {
            pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 2;
        }
    }

    /* HAL发送Beacon帧接口 */
    hal_vap_send_beacon_pkt(pst_dmac_vap->pst_hal_vap, &st_beacon_tx_params);

    /* DBAC使能后，让DBAC自行启动TSF */
#ifdef _PRE_WLAN_FEATURE_DBAC
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
     /* 1102 DBAC todo DBAC未启动的时候，通过enable信息判断，导致GO不会发送Beacon帧*/
    {
        mac_device_stru *pst_device = mac_res_get_dev((oal_uint32)pst_dmac_vap->st_vap_base_info.uc_device_id);

        if(pst_device->en_dbac_enabled)
        {
			/* force PAUSE when DBAC enabled */
            pst_dmac_vap->st_vap_base_info.en_vap_state = MAC_VAP_STATE_PAUSE;
            return OAL_SUCC;
        }
    }
#endif
#endif

    /* 开启tsf */
    hal_vap_start_tsf(pst_dmac_vap->pst_hal_vap, OAL_FALSE);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_beacon_free
 功能描述  : 释放beacon帧内存
 输入参数  : pst_dmac_vap: 指向dmac vap
 输出参数  : 无
 返 回 值  : OAL_SUCC
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_beacon_free(dmac_vap_stru *pst_dmac_vap)
{
    OAL_MEM_FREE(pst_dmac_vap->pauc_beacon_buffer[0], OAL_TRUE);
    OAL_MEM_FREE(pst_dmac_vap->pauc_beacon_buffer[1], OAL_TRUE);

    pst_dmac_vap->pauc_beacon_buffer[0] = OAL_PTR_NULL;
    pst_dmac_vap->pauc_beacon_buffer[1] = OAL_PTR_NULL;

    /* 关闭tsf */
    hal_vap_set_machw_tsf_disable(pst_dmac_vap->pst_hal_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_tbtt_exception_handler
 功能描述  : 统计MAC错误中断计数
 输入参数  : pst_dmac_vap: DMAC VAP结构体指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月28日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_tbtt_exception_handler(dmac_vap_stru *pst_dmac_vap)
{
    hal_to_dmac_device_stru         *pst_hal_device = pst_dmac_vap->pst_hal_device;
    hal_dfr_err_opern_stru          *pst_dfr_err;
    hal_mac_error_type_enum_uint8    en_error_id;

    /* DTS2015120501662 begin--vap删除，tbtt中断发现pst_hal_device为空 */
    if (OAL_PTR_NULL == pst_hal_device)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ACS, "{vap %d may be deleted::tbtt exception handle err!}", pst_dmac_vap->st_vap_base_info.uc_vap_id);
        return;
    }

    /* 遍历所有错误类型 */
    for (en_error_id = 0; en_error_id < HAL_MAC_ERROR_TYPE_BUTT; en_error_id++)
    {
        pst_dfr_err = &(pst_hal_device->st_dfr_err_opern[en_error_id]);

        pst_dfr_err->us_tbtt_cnt++;

        if (pst_dfr_err->us_tbtt_cnt >= 10)
        {
            pst_dfr_err->us_tbtt_cnt = 0;

            /* 每10次TBTT中断，将此计数清零 */
            pst_dfr_err->us_err_cnt = 0;
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_handle_tbtt_chan_mgmt_ap
 功能描述  : AP侧TBTT中断中进行信道管理
 输入参数  : pst_dmac_vap: DMAC VAP结构体指针，指向AP
 输出参数  : pst_dmac_vap: DMAC VAP结构体指针，指向ap
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月24日
    作    者   : mayuan
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_handle_tbtt_chan_mgmt_ap(dmac_vap_stru *pst_dmac_vap)
{
    mac_vap_stru              *pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);
    mac_ch_switch_info_stru   *pst_csi = &(pst_mac_vap->st_ch_switch_info);

    /* AP准备进行信道切换 */
    if (WLAN_CH_SWITCH_STATUS_1 == pst_csi->en_ch_switch_status)
    {
        if (0 == pst_csi->uc_ch_switch_cnt)
        {
            oal_uint8   auc_null_addr[6] = {0};

            /* 在当前信道挂起beacon帧发送 */
            hal_vap_beacon_suspend(pst_dmac_vap->pst_hal_vap);

            /* 从Beacon帧中移除Channel Switch Announcement IE */
            pst_csi->en_csa_present_in_bcn = OAL_FALSE;

            mac_vap_set_bssid(pst_mac_vap, auc_null_addr);
            dmac_chan_attempt_new_chan(pst_dmac_vap, pst_csi->uc_announced_channel, pst_csi->en_announced_bandwidth);
        }
        else
        {
            pst_csi->uc_ch_switch_cnt--;
        }
    }
    else if (0 == pst_dmac_vap->uc_dtim_count)
    {
        if (WLAN_BW_SWITCH_40_TO_20 == pst_csi->en_bw_switch_status || WLAN_BW_SWITCH_20_TO_40 == pst_csi->en_bw_switch_status)
        {

            pst_csi->en_bw_switch_status = WLAN_BW_SWITCH_DONE;

            /* 现在VAP下的"带宽模式"应该为 WLAN_BAND_WIDTH_20MHz */
            dmac_chan_select_channel_mac(pst_mac_vap, pst_mac_vap->st_channel.uc_chan_number, pst_mac_vap->st_channel.en_bandwidth);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            dmac_switch_complete_notify(pst_mac_vap, OAL_FALSE);
#endif
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_send_disasoc_misc_event
 功能描述  : DMAC发送去关联MISC事件
 输入参数  : pst_mac_vap: MAC VAP结构体指针
             uc_sub_type: 事件子类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : zhangyu 00241943
    修改内容   : 新生成函数
****************************************************************************/
oal_uint32  dmac_send_disasoc_misc_event(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx, oal_uint16 us_disasoc_reason)
{
    frw_event_mem_stru       *pst_event_mem;
    frw_event_stru           *pst_event;
    oal_uint32                ul_ret;
    dmac_disasoc_misc_stru    st_disasoc_misc;

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_disasoc_misc_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN,
                "{dmac_send_disasoc_misc_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                            FRW_EVENT_TYPE_DMAC_MISC,
                            DMAC_MISC_SUB_TYPE_DISASOC,
                            WLAN_MEM_EVENT_SIZE1,
                            FRW_EVENT_PIPELINE_STAGE_1,
                            pst_mac_vap->uc_chip_id,
                            pst_mac_vap->uc_device_id,
                            pst_mac_vap->uc_vap_id);

    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_send_disasoc_misc_event::user_id=%d reason=%d}",
                    us_user_idx, us_disasoc_reason);

    st_disasoc_misc.en_disasoc_reason = us_disasoc_reason;
    st_disasoc_misc.us_user_idx       = us_user_idx;
    oal_memcopy(pst_event->auc_event_data, &st_disasoc_misc, OAL_SIZEOF(dmac_disasoc_misc_stru));

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_send_disasoc_misc_event::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return ul_ret;
    }

    /* 释放事件 */
    FRW_EVENT_FREE(pst_event_mem);
    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_ROAM

/*****************************************************************************
 函 数 名  : dmac_sta_roam_trigger_init
 功能描述  : 初始化roam_trigger信息, 在上层下发 connect 时重新初始化。
 输入参数  : pst_dmac_vap

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : g00260350
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32 dmac_sta_roam_trigger_init(dmac_vap_stru *pst_dmac_vap)
{
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{dmac_sta_roam_trigger_init:: pst_dmac_vap NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap->st_roam_trigger.ul_cnt         = 0;
    pst_dmac_vap->st_roam_trigger.ul_time_stamp  = 0;
    pst_dmac_vap->st_roam_trigger.c_trigger_2G   = ROAM_TRIGGER_RSSI_NE70_DB;
    pst_dmac_vap->st_roam_trigger.c_trigger_5G   = ROAM_TRIGGER_RSSI_NE70_DB;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_sta_roam_trigger_check
 功能描述  : 判断漫游触发是否需要上报HMAC
 输入参数  : pst_dmac_vap

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : g00260350
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32 dmac_sta_roam_trigger_check(dmac_vap_stru *pst_dmac_vap)
{
    mac_device_stru          *pst_mac_device;
    frw_event_mem_stru       *pst_event_mem     = OAL_PTR_NULL;
    frw_event_stru           *pst_event         = OAL_PTR_NULL;
    oal_uint32                ul_ret            = OAL_SUCC;
    oal_uint32                ul_delta_time     = 0;
    oal_bool_enum             en_trigger_enable = OAL_FALSE;
    oal_int8                  c_trigger_rssi    = 0;
    oal_int8                  c_current_rssi    = 0;
    oal_uint8                 uc_vap_id;
    oal_uint16                us_linkloss_threshold = 0;       /*  LinkLoss门限  */
    oal_uint32                ul_cur_time       = 0;

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device  = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::pst_mac_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
     /* 过滤非 WLAN0 设备 */
    if (!(IS_LEGACY_VAP(&pst_dmac_vap->st_vap_base_info)))
    {
        return OAL_FAIL;
    }

     /* p2p在运行,直接return */
    if ((OAL_SUCC == mac_device_is_p2p_connected(pst_mac_device)))
    {
        return OAL_FAIL;
    }

    if (WLAN_BAND_5G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
    {
        c_trigger_rssi = pst_dmac_vap->st_roam_trigger.c_trigger_5G;
    }
    else
    {
        c_trigger_rssi = pst_dmac_vap->st_roam_trigger.c_trigger_2G;
    }

    c_current_rssi = (oal_int8)pst_dmac_vap->st_query_stats.ul_signal;

    if (c_current_rssi >= c_trigger_rssi)
    {
        pst_dmac_vap->st_roam_trigger.ul_cnt = 0;
    }
    else
    {
        /* 连续若干次rssi小于门限时发起一次漫游  */
        if (pst_dmac_vap->st_roam_trigger.ul_cnt++ >= ROAM_TRIGGER_COUNT_THRESHOLD)
        {
            /* 漫游触发事件需要满足上报最小间隔 */
            ul_cur_time    = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            ul_delta_time  = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_dmac_vap->st_roam_trigger.ul_time_stamp, ul_cur_time);

            if ((c_current_rssi <= ROAM_TRIGGER_RSSI_NE80_DB && ul_delta_time >= ROAM_TRIGGER_INTERVAL_10S) ||
                (c_current_rssi <= ROAM_TRIGGER_RSSI_NE75_DB && ul_delta_time >= ROAM_TRIGGER_INTERVAL_15S) ||
                (ul_delta_time >= ROAM_TRIGGER_INTERVAL_20S))
            {
                en_trigger_enable  = OAL_TRUE;
                pst_dmac_vap->st_roam_trigger.ul_cnt = 0;
            }
        }
    }

    /* WLAN0: LINK LOSS计数满足1/2、3/4的门限时发起一次漫游，rssi为0表示强制漫游  */
    us_linkloss_threshold = pst_dmac_vap->st_linkloss_info.us_linkloss_threshold;
    if ((pst_dmac_vap->st_linkloss_info.us_link_loss == (us_linkloss_threshold >> 1)) ||
        (pst_dmac_vap->st_linkloss_info.us_link_loss == (us_linkloss_threshold >> 1) + (us_linkloss_threshold >> 2)))
    {
        /* 为了防止重复上报，强制+1 */
        pst_dmac_vap->st_linkloss_info.us_link_loss++;
        c_current_rssi     = -127;
        en_trigger_enable  = OAL_TRUE;
    }

    if (en_trigger_enable == OAL_FALSE)
    {
        return OAL_FAIL;
    }

    /* 漫游触发需要与正常关联保持时间间隔，WIFI+切换频繁，与漫游冲突。正常关联，并且 IP ADDR 已获取 */
    ul_delta_time  = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_dmac_vap->st_roam_trigger.ul_ip_obtain_stamp, ul_cur_time);

    if(OAL_FALSE == pst_dmac_vap->st_roam_trigger.ul_ip_addr_obtained ||
       ul_delta_time < ROAM_WPA_CONNECT_INTERVAL_TIME)
    {
        OAM_WARNING_LOG2(0, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check:: ip_addr_check, ul_ip_addr_obtained = %d, ul_delta_time = %d}",
                        pst_dmac_vap->st_roam_trigger.ul_ip_addr_obtained,ul_delta_time);
        return OAL_FAIL;
    }

    uc_vap_id      = pst_dmac_vap->st_vap_base_info.uc_vap_id;

    /* 申请事件内存 */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_disasoc_misc_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::pst_event_mem fail.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                            FRW_EVENT_TYPE_DMAC_MISC,
                            DMAC_MISC_SUB_TYPE_ROAM_TRIGGER,
                            WLAN_MEM_EVENT_SIZE1,
                            FRW_EVENT_PIPELINE_STAGE_1,
                            pst_dmac_vap->st_vap_base_info.uc_chip_id,
                            pst_dmac_vap->st_vap_base_info.uc_device_id,
                            uc_vap_id);

    oal_memcopy(pst_event->auc_event_data, &c_current_rssi, OAL_SIZEOF(oal_uint8));

    /* 分发事件 */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_sta_roam_trigger_check::frw_event_dispatch_event failed[%d].}", ul_ret);
        FRW_EVENT_FREE(pst_event_mem);
        return ul_ret;
    }

    /* 释放事件 */
    FRW_EVENT_FREE(pst_event_mem);

    pst_dmac_vap->st_roam_trigger.ul_time_stamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    return OAL_SUCC;
}
#endif //_PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 函 数 名  : dmac_LinkLoss_send_probe_req
 功能描述  :  非背景扫描阶段，LinkLoss计数器超过一半，准备开始发送单播探测帧接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : zhongwen
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_linkloss_send_probe_req(dmac_vap_stru *pst_dmac_vap, mac_device_stru *pst_mac_device)
{
    mac_vap_stru       *pst_mac_vap;

    pst_mac_vap = &(pst_dmac_vap->st_vap_base_info);

    /* 扫描、雷达、2040切信道时候，linkloss计数器不计数,所以不额外发送单播探测帧 */
    if ((0 == pst_mac_vap->st_ch_switch_info.uc_new_ch_swt_cnt)&&
        (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state))
    {
        /* 根据索引号，准备probe req帧的ssid信息 */
        dmac_scan_send_probe_req_frame(pst_dmac_vap,
                                       pst_mac_vap->auc_bssid,
                                       (oal_int8 *)(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID));
    }
}
/*****************************************************************************
 函 数 名  : dmac_vap_linkloss_incr
 功能描述  : 对linkloss计数器加1
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : zhongwen
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_vap_linkloss_incr(dmac_vap_stru *pst_dmac_vap, mac_device_stru *pst_mac_device)
{
    /* 扫描、雷达、2040切信道时候，linkloss计数器不计数 */
    if ((0 == pst_dmac_vap->st_vap_base_info.st_ch_switch_info.uc_new_ch_swt_cnt)&&
        (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state))
    {
        pst_dmac_vap->st_linkloss_info.us_link_loss++;
    }

}

/*****************************************************************************
 函 数 名  : dmac_vap_update_linkloss_threshold
 功能描述  :  更新linkloss门限值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : zhongwen
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_vap_update_linkloss_threshold(dmac_vap_stru *pst_dmac_vap, mac_device_stru *pst_mac_device)
{
    oal_uint32                         ul_dot11BeaconPeriod;
    dmac_vap_linkloss_stru            *pst_linkloss_info;
    oal_uint16                         us_linkloss_threshold;
    oal_bool_enum_uint8                en_bt_on = OAL_FALSE;
    oal_bool_enum_uint8                en_dbac_running = OAL_FALSE;
    oal_bool_enum_uint8                en_far_distance = OAL_FALSE;
    oal_bool_enum_uint8                en_threshold_change_flag = OAL_FALSE;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    oal_uint8 uc_index;
    oal_uint16 us_linkloss_interval_for_100ms;
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;
#endif
    ul_dot11BeaconPeriod = pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod;

    /* 无效beacon间隔(为0)，强行按照beacon间隔为100ms计算linkloss门限 */
    if (0 == ul_dot11BeaconPeriod)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                "{dmac_vap_update_linkloss_threshold::pst_mib.ul_dot11BeaconPeriod[%d] is Abnormal, when STAUT_mode and UP_status!}", ul_dot11BeaconPeriod);
        ul_dot11BeaconPeriod = WLAN_BEACON_INTVAL_DEFAULT;
    }

    pst_linkloss_info = &(pst_dmac_vap->st_linkloss_info);

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    en_bt_on = pst_dmac_vap->pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on;
    /* 如果bt开关改变 */
    if (pst_linkloss_info->en_old_bt_on != en_bt_on)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
            "{dmac_vap_update_linkloss_threshold::bt change to [%d]!}", en_bt_on);
        en_threshold_change_flag = OAL_TRUE;
        pst_linkloss_info->en_old_bt_on = en_bt_on;

        pst_linkloss_info->us_link_loss = (en_bt_on) ?
                        ((oal_uint16)(pst_linkloss_info->us_link_loss << 1)) :
                        ((oal_uint16)(pst_linkloss_info->us_link_loss >> 1));  /* 关闭bt恢复linkloss基础器2倍之前的值 */
    }
#endif
    en_dbac_running = mac_is_dbac_running(pst_mac_device);
    if (pst_linkloss_info->en_old_dbac_runing != en_dbac_running)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
            "{dmac_vap_update_linkloss_threshold::dbac_runing change to [%d]!}", en_dbac_running);
        en_threshold_change_flag = OAL_TRUE;
        pst_linkloss_info->en_old_dbac_runing = en_dbac_running;
        pst_linkloss_info->us_link_loss = (en_dbac_running) ? ((oal_uint16)(pst_linkloss_info->us_link_loss << 1)) :(pst_linkloss_info->us_link_loss >> 1); /* 停止dbac恢复linkloss基础器2倍之前的值 */
    }

    en_far_distance = (pst_dmac_vap->st_query_stats.ul_signal < WLAN_FAR_DISTANCE_RSSI);
    if(pst_linkloss_info->en_old_far_distance != en_far_distance)
    {
        en_threshold_change_flag = OAL_TRUE;
        pst_linkloss_info->en_old_far_distance = en_far_distance;
        pst_linkloss_info->us_link_loss = (en_far_distance) ? ((oal_uint16)(pst_linkloss_info->us_link_loss << 1)) : (pst_linkloss_info->us_link_loss >> 1);  /* 状态切换近场恢复linkloss基础器2倍之前的值 */
    }

    /* 如果beacon周期改变 */
    if (ul_dot11BeaconPeriod != pst_linkloss_info->ul_old_dot11BeaconPeriod)
    {
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
            "{dmac_vap_update_linkloss_threshold::old_BeaconPeriod[%d], new_BeaconPeriod[%d]!}",
            pst_linkloss_info->ul_old_dot11BeaconPeriod,
            ul_dot11BeaconPeriod);
        en_threshold_change_flag = OAL_TRUE;
        pst_linkloss_info->ul_old_dot11BeaconPeriod = ul_dot11BeaconPeriod;
    }

    /* 状态无改变，不用重新刷新门限 */
    if (OAL_TRUE != en_threshold_change_flag)
    {
        return;
    }

    pst_linkloss_info->uc_linkloss_times = (WLAN_BEACON_INTVAL_DEFAULT > ul_dot11BeaconPeriod) ? (WLAN_BEACON_INTVAL_DEFAULT / ul_dot11BeaconPeriod) : 1;

    /* 设置门限基数。当beacon周期为默认设置时，优化为用位移方式(约等于 time*10>>8) */
    if (IS_LEGACY_VAP(&pst_dmac_vap->st_vap_base_info))
    {
        /* 近场 */
        if (WLAN_FAR_DISTANCE_RSSI <= pst_dmac_vap->st_query_stats.ul_signal)
        {
            us_linkloss_threshold  = (WLAN_BEACON_INTVAL_DEFAULT == ul_dot11BeaconPeriod) ? (oal_uint16)(g_st_beacon_linkloss.us_linkloss_threshold_wlan_near)  : (oal_uint16)(100*g_st_beacon_linkloss.us_linkloss_threshold_wlan_near / ul_dot11BeaconPeriod); /* 4s in normal BeaconPeriod*/
        }
        else
        {
            us_linkloss_threshold  = (WLAN_BEACON_INTVAL_DEFAULT == ul_dot11BeaconPeriod) ? (oal_uint16)(g_st_beacon_linkloss.us_linkloss_threshold_wlan_far)  :  (oal_uint16)(100*g_st_beacon_linkloss.us_linkloss_threshold_wlan_far/ ul_dot11BeaconPeriod); /* 10s in normal BeaconPeriod*/
        }

    }
    else
    {
        us_linkloss_threshold  = (WLAN_BEACON_INTVAL_DEFAULT == ul_dot11BeaconPeriod) ? (oal_uint16)(g_st_beacon_linkloss.us_linkloss_threshold_p2p)  :  (oal_uint16)(100*g_st_beacon_linkloss.us_linkloss_threshold_p2p/ ul_dot11BeaconPeriod); /* 4s in normal BeaconPeriod*/
    }


    /* 根据具体情况调整门限值 */
    if (OAL_TRUE == en_dbac_running)
    {
        us_linkloss_threshold = (oal_uint16)(us_linkloss_threshold << 1); /* DBAC模式，门限翻2倍 */
    }

    if (OAL_TRUE == en_bt_on)
    {
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        us_linkloss_threshold = (oal_uint16)(us_linkloss_threshold << 1); /* 共存模式，门限翻2倍 */
#endif
    }

    /* 异常保护:当linkloss门限过低，在糟糕的环境下极容易出现linkloss。此处设置门限最低值 */
    if (WLAN_LINKLOSS_MIN_THRESHOLD > us_linkloss_threshold)
    {
        OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
            "{dmac_vap_update_linkloss_threshold::The linkloss_threshold[%d]is too little that we have to change it to[%d],and now BeaconPeriod is[%d]!}",
            us_linkloss_threshold,
            WLAN_LINKLOSS_MIN_THRESHOLD,
            ul_dot11BeaconPeriod);
        us_linkloss_threshold = WLAN_LINKLOSS_MIN_THRESHOLD;
    }

    pst_linkloss_info->us_linkloss_threshold = us_linkloss_threshold;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    us_linkloss_interval_for_100ms = us_linkloss_threshold / BTCOEX_LINKLOSS_OCCUPIED_NUMBER;
    g_us_occupied_point[0] = us_linkloss_interval_for_100ms;

    for (uc_index = 0; uc_index < BTCOEX_LINKLOSS_OCCUPIED_NUMBER - 1; uc_index++)
    {
        g_us_occupied_point[uc_index + 1] = g_us_occupied_point[uc_index] + us_linkloss_interval_for_100ms;
    }

    pst_btcoex_wifi_status = &(pst_dmac_vap->pst_hal_device->st_btcoex_wifi_status);
    pst_btcoex_wifi_status->uc_linkloss_index = 1;
    pst_btcoex_wifi_status->uc_linkloss_occupied_times = 0;
#endif

}

OAL_STATIC void dmac_sta_tbtt_prior_linkloss_handler(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint16           us_linkloss_period;
    mac_device_stru     *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {

        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                        "{dmac_sta_up_misc::Cannot find mac_dev,by vap.device_id[%d]} ",
                        pst_dmac_vap->st_vap_base_info.uc_device_id);
        return ;
    }

    dmac_vap_update_linkloss_threshold(pst_dmac_vap, pst_mac_device);
    dmac_vap_linkloss_incr(pst_dmac_vap, pst_mac_device);

#define LINKLOSS_DFT_PERIOD  10
    us_linkloss_period = (pst_dmac_vap->st_linkloss_info.us_link_loss % LINKLOSS_DFT_PERIOD);

    /* linkloss计数超过一半,"且每隔16个tbtt周期" or "linklos门限计数值小于16"，准备发送单播探测帧 */
    if ((pst_dmac_vap->st_linkloss_info.us_link_loss >= (pst_dmac_vap->st_linkloss_info.us_linkloss_threshold >> 1))&&
        ((0 == us_linkloss_period) || (pst_dmac_vap->st_linkloss_info.us_linkloss_threshold < LINKLOSS_DFT_PERIOD )))
    {
        dmac_linkloss_send_probe_req(pst_dmac_vap, pst_mac_device);
    }

    /*linkloss每统计达到10次，上报一次维测信息，扫描或切信道时刻不打印*/
    if ((0 == us_linkloss_period) && (0 == pst_dmac_vap->st_vap_base_info.st_ch_switch_info.uc_new_ch_swt_cnt)&&
        (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state))
    {
#ifdef _PRE_WLAN_DFT_STAT
        dmac_dft_report_all_para(pst_dmac_vap,OAL_FALSE);
#endif
    }
}

/*****************************************************************************
 函 数 名  : dmac_sta_up_misc
 功能描述  : up状态下, misc事件处理.向ap发去关联。如果sta与ap处于关联状态，应
             使用去关联踢掉对方。
 输入参数  : dmac_vap_stru *pst_dmac_sta
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : zhangyu 00241943
    修改内容   : 新生成函数
 ****************************************************************************/
 OAL_STATIC void dmac_sta_up_misc(dmac_vap_stru *pst_dmac_vap)
 {

#ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    pst_dmac_vap->uc_beacon_miss_cnt++;
#endif

    dmac_sta_tbtt_prior_linkloss_handler(pst_dmac_vap);

#ifdef _PRE_WLAN_FEATURE_ROAM
    dmac_sta_roam_trigger_check(pst_dmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM

    dmac_handle_tbtt_chan_mgmt_sta(pst_dmac_vap);

    /* sta与ap丢失连接超过上限处理 */
    if (DMAC_IS_LINKLOSS(pst_dmac_vap))
    {
        OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                        "{dmac_sta_up_misc::Oh no,LinkLoss!! BSSID[%02X:XX:XX:%02X:%02X:%02X]} ",
                        pst_dmac_vap->st_vap_base_info.auc_bssid[0],
                        pst_dmac_vap->st_vap_base_info.auc_bssid[3],
                        pst_dmac_vap->st_vap_base_info.auc_bssid[4],
                        pst_dmac_vap->st_vap_base_info.auc_bssid[5]);
#ifdef _PRE_WLAN_DFT_STAT
        dmac_dft_report_all_para(pst_dmac_vap,OAL_TRUE);
#endif
        dmac_vap_linkloss_clean(pst_dmac_vap);
        dmac_send_disasoc_misc_event(&(pst_dmac_vap->st_vap_base_info),pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id, DMAC_DISASOC_MISC_LINKLOSS);
    }

    return ;
}

/*****************************************************************************
 函 数 名  : dmac_tbtt_event_sta
 功能描述  : sta tbtt中断处理, 抛到hmac去处理
 输入参数  : pst_dmac_vap: DMAC VAP
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_tbtt_event_sta(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru  *pst_event;
    dmac_vap_stru   *pst_dmac_vap;

#ifdef _PRE_WLAN_CHIP_TEST
    if (1 == dmac_test_lpm_get_wow_en())
    {
         return;
    }
#endif

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_dmac_vap = mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "dmac_tbtt_event_sta, pst_dmac_vap is null, vap id [%d].", pst_event->st_event_hdr.uc_vap_id);
        return;
    }

    if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)
    {
        dmac_sta_up_misc(pst_dmac_vap);
    }
    else
    {
        FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(&(pst_event->st_event_hdr), DMAC_TBTT_EVENT_SUB_TYPE);

        /* 分发事件 */
        frw_event_dispatch_event(pst_event_mem);
    }

    return;
}

/*****************************************************************************
 函 数 名  : dmac_tbtt_event_ap
 功能描述  : ap tbtt中断处理
 输入参数  : pst_dmac_vap: DMAC VAP
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月8日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_tbtt_event_ap(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8                    uc_bcn_idx_for_soft;   /* 软件更新beacon帧编号 */
    oal_uint8                   *puc_bcn_buf;
    hal_beacon_tx_params_stru    st_beacon_tx_params;
    hal_tx_txop_alg_stru        *pst_tx_param;
    dmac_user_stru              *pst_dmac_multi_user;
    oal_uint32                   ul_ret;
    mac_device_stru             *pst_macdev;
    wlan_channel_band_enum_uint8 en_band;
    oal_uint8                    uc_bcn_chain_switch;
#ifdef  _PRE_WLAN_FEATURE_PM
    oal_uint32                   ul_bcn_interval_temp;
    hal_tx_txop_tx_power_stru    st_tx_power_temp;
    mac_pm_handler_stru          *pst_mac_pm_handle;
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_btcoex_wifi_status_stru    *pst_hal_btcoex_wifi_status;
    oal_uint32 ul_beacon_count_new;
#endif
    if ((MAC_VAP_STATE_UP != pst_dmac_vap->st_vap_base_info.en_vap_state) &&
        (MAC_VAP_STATE_PAUSE != pst_dmac_vap->st_vap_base_info.en_vap_state))
    {
        //OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_ap::vap state=%d.}", pst_dmac_vap->st_vap_base_info.en_vap_state);
        return;
    }

    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON,
                       "{dmac_tbtt_event_ap::dev is null!}");
        return;
    }
    /* 计算软件更新beacon帧编号 */
    uc_bcn_idx_for_soft = (DMAC_VAP_BEACON_BUFFER_BUTT == (pst_dmac_vap->uc_beacon_idx + 1)) ? DMAC_VAP_BEACON_BUFFER1 : DMAC_VAP_BEACON_BUFFER2;

    /* 软件要更新的beacon帧 */
    puc_bcn_buf = pst_dmac_vap->pauc_beacon_buffer[uc_bcn_idx_for_soft];

    if(puc_bcn_buf == NULL)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_ap::beacon buf = NULL. uc_bcn_idx_for_soft=%d.}\r\n", uc_bcn_idx_for_soft);
        return;
    }
    /* 如果此次tbtt中断对应的是DTIM周期，则需要发送组播/广播节能队列中的缓存帧 */
//    if (0 == pst_dmac_vap->uc_dtim_count)
    if ((0 == pst_dmac_vap->uc_dtim_count) && (OAL_TRUE == pst_dmac_vap->en_dtim_ctrl_bit0))
    {
        pst_dmac_multi_user = mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
        if (OAL_PTR_NULL == pst_dmac_multi_user)
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_ap::get multi user[%d] fail.}", pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
            return;
        }
        /* 解决当前PSM未开启时引入的节能队列刷新问题 */
        dmac_psm_queue_flush(pst_dmac_vap, pst_dmac_multi_user);
    }

    /* DTS2015121601339 确保DTIM count在tbtt中更新，保证count值顺序减1 */
    dmac_update_dtim_count_ap(pst_dmac_vap);

    if((WITP_TX_CHAIN_DOUBLE == pst_macdev->uc_tx_chain)&&
        (OAL_TRUE == pst_dmac_vap->en_beacon_chain_active))
    {
        uc_bcn_chain_switch = 1;
    }
    else
    {
        uc_bcn_chain_switch = 0;
    }

    /* 信道管理 */
    dmac_handle_tbtt_chan_mgmt_ap(pst_dmac_vap);

    en_band = pst_dmac_vap->st_vap_base_info.st_channel.en_band;
    pst_tx_param =&(pst_dmac_vap->ast_tx_mgmt_bmcast[en_band]);
    pst_tx_param->ast_per_rate[0].rate_bit_stru.bit_reserve = 0;
#ifdef  _PRE_WLAN_FEATURE_PM
    ul_bcn_interval_temp = pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod;
#endif
#ifdef  _PRE_WLAN_FEATURE_PM
    /*保存配置值,本函数结束后恢复*/
    st_tx_power_temp     = pst_tx_param->st_tx_power;
    pst_mac_pm_handle    = (mac_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    if(PWR_SAVE_STATE_IDLE == dmac_pm_vap_current_state((oal_void *)pst_dmac_vap))
    {
        if(WITP_TX_CHAIN_DOUBLE == pst_macdev->uc_tx_chain)
        {
            uc_bcn_chain_switch  = 1;
        }

        #ifdef _PRE_WLAN_FEATURE_DBAC
        if (!mac_is_dbac_enabled(mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id)))
        {
            // DBAC使能时,beacon不做调整
            pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = WLAN_BEACON_INTVAL_IDLE;
        }
        #endif

        oal_memcopy((oal_void*)&(pst_tx_param->st_tx_power),(oal_void*)&(pst_mac_pm_handle->ul_idle_beacon_txpower),4);

    }

#endif

    /* 更新beacon帧 */
    dmac_encap_beacon(pst_dmac_vap, puc_bcn_buf, &(pst_dmac_vap->us_beacon_len));

    /* 将更新的beacon帧写入硬件beacon帧寄存器 */
    /* 填写发送Beacon帧参数 */
    st_beacon_tx_params.pst_tx_param = pst_tx_param;
    st_beacon_tx_params.ul_pkt_ptr   = (oal_uint32)puc_bcn_buf;
    st_beacon_tx_params.us_pkt_len   = pst_dmac_vap->us_beacon_len;

    /* 判断是否开启了双路轮流发送 */
    if(1 == uc_bcn_chain_switch)
    {
        /* 第一个beacon帧由通道0发送，第二个beacon帧由通道1发送 */
        if(pst_dmac_vap->uc_beacon_idx == DMAC_VAP_BEACON_BUFFER1)
        {
            //pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
            st_beacon_tx_params.ul_tx_chain_mask= 0x1;
        }
        else
        {
            //pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 2;
            st_beacon_tx_params.ul_tx_chain_mask = 0x2;
        }
    }
    else
    {
        if (0x3 == pst_dmac_vap->uc_vap_tx_chain)
        {
            st_beacon_tx_params.ul_tx_chain_mask   = 0x1;
        }
        else
        {
            st_beacon_tx_params.ul_tx_chain_mask   = pst_dmac_vap->uc_vap_tx_chain;
        }
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_btcoex_update_ap_beacon_count(&ul_beacon_count_new);
    pst_hal_btcoex_wifi_status = &(pst_macdev->pst_device_stru->st_btcoex_wifi_status);

    /* 每5个beacon发送失败上报一次BEACON MISS中断，所以在发出了5个beacon后，计数减1 */
    if (ul_beacon_count_new - pst_hal_btcoex_wifi_status->ul_ap_beacon_count >= 5)
    {
        pst_hal_btcoex_wifi_status->ul_ap_beacon_count += 5;
        pst_hal_btcoex_wifi_status->uc_ap_beacon_miss = OAL_SUB(pst_hal_btcoex_wifi_status->uc_ap_beacon_miss, 1);

        /* 如果存在大于5的情况，则可能出现过TBTT中断丢失，实际确有发生beacon miss计数无法清零的情况 */
        if (ul_beacon_count_new > pst_hal_btcoex_wifi_status->ul_ap_beacon_count)
        {
            OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_WIFI_BEACON, "{TBTT interrupt miss may be happened: new beacon cnt [%d] & record beacon cnt [%d]!}", \
            ul_beacon_count_new, pst_hal_btcoex_wifi_status->ul_ap_beacon_count);
        }
    }
    else if (ul_beacon_count_new < pst_hal_btcoex_wifi_status->ul_ap_beacon_count)
    {
        /* 防止硬件的beacon计数翻转 */
        pst_hal_btcoex_wifi_status->ul_ap_beacon_count = ul_beacon_count_new;
    }

    if (pst_macdev->pst_device_stru->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_page)
    {
        /* 达到30个beacon miss就拉高occupied */
        if (pst_hal_btcoex_wifi_status->uc_ap_beacon_miss > 5)
        {
            hal_set_btcoex_occupied_period(10000);  // 10ms
        }
    }

#endif

    /* HAL发送Beacon帧接口 */
    hal_vap_send_beacon_pkt(pst_dmac_vap->pst_hal_vap, &st_beacon_tx_params);

    ul_ret = oam_report_beacon(puc_bcn_buf, MAC_80211_FRAME_LEN,
                               puc_bcn_buf + MAC_80211_FRAME_LEN,
                               pst_dmac_vap->us_beacon_len,  OAM_OTA_FRAME_DIRECTION_TYPE_TX);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_ap::oam_report_beacon return err: 0x%x.}\r\n", ul_ret);
    }

#ifdef _PRE_WLAN_DFT_STAT
    /* 发送beacon帧数目统计 */
    DMAC_DFT_MGMT_STAT_INCR(pst_macdev->st_mgmt_stat.aul_tx_mgmt_soft[WLAN_BEACON]);
#endif
    /* 交换两个beacon帧 */
    pst_dmac_vap->uc_beacon_idx = uc_bcn_idx_for_soft;

#ifdef  _PRE_WLAN_FEATURE_PM
/*恢复配置值*/
    pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = ul_bcn_interval_temp;
    pst_tx_param->st_tx_power = st_tx_power_temp;
#endif

}


#ifdef _PRE_WLAN_FEATURE_BTCOEX
OAL_STATIC OAL_INLINE oal_void dmac_btcoex_linkloss_occupied_process(dmac_vap_stru *pst_dmac_vap)
{
    dmac_vap_linkloss_stru *pst_linkloss_info;
    hal_btcoex_wifi_status_stru *pst_btcoex_wifi_status;
    oal_uint16 us_linkloss_threshold;
    oal_uint16 us_linkloss;
    oal_uint16 us_linkloss_tmp;
    oal_uint8 uc_linkloss_times;

    if (OAL_FALSE == pst_dmac_vap->pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        return;
    }

    pst_linkloss_info = &(pst_dmac_vap->st_linkloss_info);
    pst_btcoex_wifi_status = &(pst_dmac_vap->pst_hal_device->st_btcoex_wifi_status);
    us_linkloss_threshold = pst_linkloss_info->us_linkloss_threshold;
    us_linkloss = pst_linkloss_info->us_link_loss;
    uc_linkloss_times = pst_linkloss_info->uc_linkloss_times;

    if (0 == us_linkloss_threshold)
    {
        return;
    }
    /* linkloss 大于1/4门限值进行处理 */
    if (us_linkloss < (us_linkloss_threshold >> 2))
    {
        return;
    }

    /* 门限值为异常值，即beacon周期很大 */
    if (us_linkloss_threshold <= WLAN_LINKLOSS_MIN_THRESHOLD)
    {
        hal_set_btcoex_occupied_period(COEX_LINKLOSS_OCCUP_PERIOD);
        OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_COEX,
                "{dmac_btcoex_linkloss_occupied_process::occupied time == [%d], linkloss == [%d], threshold == [%d].}",
                COEX_LINKLOSS_OCCUP_PERIOD, us_linkloss, us_linkloss_threshold);
        return;
    }

    us_linkloss_tmp = g_us_occupied_point[pst_btcoex_wifi_status->uc_linkloss_index] + pst_btcoex_wifi_status->uc_occupied_times;

    if (us_linkloss > us_linkloss_tmp)
    {
        pst_btcoex_wifi_status->uc_occupied_times = 0;
        pst_btcoex_wifi_status->uc_linkloss_index++;
    }
    /* 在整个linkloss阶段拉高occupied 6-7个阶段, 每个阶段为300ms，每100ms拉一次20ms, 连续拉3次 */
    else if (us_linkloss == us_linkloss_tmp)
    {
        pst_btcoex_wifi_status->uc_occupied_times += uc_linkloss_times;
        if (pst_btcoex_wifi_status->uc_occupied_times > (uc_linkloss_times << 1))
        {
            pst_btcoex_wifi_status->uc_occupied_times = 0;
            pst_btcoex_wifi_status->uc_linkloss_index++;
            if (pst_btcoex_wifi_status->uc_linkloss_index > BTCOEX_LINKLOSS_OCCUPIED_NUMBER - 1)
            {
                pst_btcoex_wifi_status->uc_linkloss_index = 1;
            }
        }

        hal_set_btcoex_occupied_period(COEX_LINKLOSS_OCCUP_PERIOD);
        OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_COEX,
                "{dmac_btcoex_linkloss_occupied_process::occupied time == [%d], linkloss == [%d], threshold == [%d].}",
                COEX_LINKLOSS_OCCUP_PERIOD, us_linkloss, us_linkloss_threshold);

    }
    else
    {}
}
#endif

#ifndef WIN32
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
 函 数 名  : dmac_over_temp_handler
 功能描述  : dmac层过温保护函数
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月24日
    作    者   : wangzhenzhong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_over_temp_handler(mac_device_stru* pst_device)
{
    dmac_reset_para_stru        st_reset_param;
    hal_to_dmac_device_stru     *pst_hal_device;

    pst_hal_device = pst_device->pst_device_stru;

#if (_PRE_WLAN_CHIP_ASIC == _PRE_WLAN_CHIP_VERSION)
    hal_over_temp_handler(pst_hal_device);
#endif

    if (OAL_TRUE == pst_hal_device->uc_over_temp)
    {
        pst_device->en_reset_switch = OAL_TRUE;

        st_reset_param.uc_reset_type    = HAL_RESET_HW_TYPE_ALL;
        st_reset_param.uc_reset_mac_reg = OAL_TRUE;
        st_reset_param.uc_reset_phy_reg = OAL_TRUE;
        st_reset_param.uc_reset_mac_mod = HAL_RESET_MAC_ALL;
        st_reset_param.en_reason = DMAC_RETST_REASON_OVER_TEMP;

        hal_dft_report_all_reg_state(pst_hal_device);

        dmac_reset_hw(pst_device, (oal_uint8 *)&st_reset_param);

        pst_device->en_reset_switch = OAL_FALSE;
    }
}


#endif
#endif  /* WIN32 */

/*****************************************************************************
 函 数 名  : dmac_sta_update_txop_process
 功能描述  : 配置txop值，在如下条件时 配置为enable
             1.发送非聚合模式,
             2.没有non-erp设备,
             3.且不处于bt和dbac模式时
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月25日
    作    者   : y00196452
    修改内容   : 新生成函数
  2.日    期   : 2015年12月9日
    作    者   : s00304087
    修改内容   : 修改为不只是11bg,只要非聚合模式即使能TXOP
  2.日    期   : 2015年1月5日
    作    者   : s00304087
    修改内容   : 更新策略,聚合个数少时使能TXOP
*****************************************************************************/
OAL_STATIC oal_void dmac_update_txop_process(mac_vap_stru* pst_mac_vap)
{
    mac_device_stru*   pst_mac_dev;
    dmac_vap_stru*              pst_dmac_vap;
    oal_bool_enum_uint8         en_cur_bt_dbac_running = OAL_FALSE;
    oal_uint16                  aus_txop_limit[WLAN_BAND_WIDTH_BUTT] = {4000, 1300, 1300, 600, 600, 600, 600};

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WMM, "{pst_mac_device null, fail to set legacy txop val}");

        return;
    }
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WMM, "{dmac_sta_update_txop_process::pst_dmac_vap[idx=%d] null.}", pst_mac_vap->uc_vap_id);
        return;
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    en_cur_bt_dbac_running = pst_mac_dev->pst_device_stru->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on;
#endif
    en_cur_bt_dbac_running |= mac_is_dbac_running(pst_mac_dev);


    if(OAL_FALSE == pst_mac_dev->en_txop_enable)
    {
        if((OAL_FALSE == pst_dmac_vap->en_non_erp_exist)&&
           (OAL_FALSE == en_cur_bt_dbac_running)&&
           (0 == pst_mac_dev->uc_tx_ba_num))
        {
            pst_mac_dev->en_txop_enable = OAL_TRUE;
            hal_vap_set_machw_txop_limit_bkbe(pst_dmac_vap->pst_hal_vap,
                                      aus_txop_limit[pst_mac_vap->st_channel.en_bandwidth],
                                      (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
        }
    }
    else
    {
        if((OAL_TRUE == pst_dmac_vap->en_non_erp_exist)||
           (OAL_TRUE == en_cur_bt_dbac_running)||
           (0 != pst_mac_dev->uc_tx_ba_num))
        {
            pst_mac_dev->en_txop_enable = OAL_FALSE;
            hal_vap_set_machw_txop_limit_bkbe(pst_dmac_vap->pst_hal_vap,
                                      (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit,
                                      (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : dmac_tbtt_event_handler
 功能描述  : TBTT中断事件处理函数
 输入参数  : pst_event_mem: 指向事件内存
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_tbtt_event_handler(frw_event_mem_stru *pst_event_mem)
{
    dmac_vap_stru               *pst_dmac_vap;
    frw_event_stru              *pst_event;
    mac_device_stru             *pst_mac_device;
	hal_error_state_stru         st_err_state;
#ifndef WIN32
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_int16                    s_power_comp_val = 0;
#endif
#endif  /* WIN32 */

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_handler::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)(pst_event_mem->puc_data);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_handler::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_tbtt_exception_handler(pst_dmac_vap);

	pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_handler::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifndef WIN32
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    //OAM_WARNING_LOG2(0, OAM_SF_WIFI_BEACON, "{dmac_tbtt_event_handler::ul_duty_ratio=%d,beacon interval = %d!}",pst_mac_device->ul_duty_ratio,pst_mac_device->ul_beacon_interval);
    if(0 != pst_mac_device->ul_beacon_interval)
    {
        hal_get_pwr_comp_val(pst_mac_device->pst_device_stru, pst_mac_device->ul_duty_ratio, &s_power_comp_val);

        dmac_over_temp_handler(pst_mac_device);

        if(pst_mac_device->s_upc_amend != s_power_comp_val)
        {
            pst_mac_device->s_upc_amend = s_power_comp_val;
            /* 通知算法 */
            dmac_alg_cfg_channel_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_MOVE_WORK);
        }
    }

#endif
#endif  /* WIN32 */

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    if (OAL_SWITCH_ON == pst_dmac_vap->st_vap_base_info.bit_al_tx_flag)
    {
        return OAL_SUCC;
    }
#endif  /* _PRE_WLAN_FEATURE_ALWAYS_TX */

    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_P2P
        if ((IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
            (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
        {
            dmac_p2p_oppps_ctwindow_start_event(pst_dmac_vap);
        }
#endif
        dmac_tbtt_event_ap(pst_dmac_vap);
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        /* STA侧pspoll低功耗处理 */
#ifdef _PRE_WLAN_FEATURE_STA_PM
        dmac_psm_process_tbtt_sta(pst_dmac_vap, pst_mac_device);
#endif
#if (!defined(HI1102_EDA))
        dmac_tbtt_event_sta(pst_event_mem);
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        /* 扫描、雷达、2040切信道时候，不进入bt防护wifi linkloss流程 */
        if ((0 == pst_dmac_vap->st_vap_base_info.st_ch_switch_info.uc_new_ch_swt_cnt)&&
            (MAC_SCAN_STATE_RUNNING != pst_mac_device->en_curr_scan_state))
        {
            dmac_btcoex_linkloss_occupied_process(pst_dmac_vap);
        }
#endif

    }
    /* 清除mac错误计数器，保证每一个tbtt间隙中，最多处理的错误数 */
    /* 当多vap时，会有误差，暂不处理误差*/
    dmac_mac_error_cnt_clr(pst_mac_device);
    st_err_state.ul_error1_val = 0xffffffff;
    st_err_state.ul_error2_val = 0xffffffdf;
    hal_unmask_mac_error_init_status(pst_dmac_vap->pst_hal_device, &st_err_state);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    dmac_update_txop_process(&pst_dmac_vap->st_vap_base_info);
#endif

#if 0
    /* 1102芯片测试，打印所有tsf的状态 */
    if (pst_dmac_vap->pst_hal_vap->uc_vap_id == 4)
    {
        oal_uint8             i;
        hal_to_dmac_vap_stru *pst_hal_vap;
        oal_uint32            ul_tsf;

        uc_cnt++;

        if (uc_cnt > 10)
        {
            uc_cnt = 0;

            for (i = 0; i < 2; i++)
            {
                hal_get_hal_vap(pst_dmac_vap->pst_hal_device, i, &pst_hal_vap);
                hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf);

                OAM_INFO_LOG2(0, OAM_SF_DBAC, "hal_vap_id:%d, tsf:%d", i, ul_tsf);
            }

            for (i = 4; i < 7; i++)
            {
                hal_get_hal_vap(pst_dmac_vap->pst_hal_device, i, &pst_hal_vap);
                hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf);

                OAM_INFO_LOG2(0, OAM_SF_DBAC, "hal_vap_id:%d, tsf:%d", i, ul_tsf);
            }
        }
    }
#endif

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 函 数 名  : dmac_beacon_set_p2p_noa
 功能描述  : 设置beacon帧中的p2p ie noa属性
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_beacon_set_p2p_noa(
                mac_vap_stru           *pst_mac_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count)
{
    dmac_vap_stru              *pst_dmac_vap;
    /*保存节能参数，用于encap beacon,probe response*/
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_WIFI_BEACON, "{dmac_beacon_set_p2p_noa::mac_res_get_dmac_vap fail.vap_id = %u}",pst_mac_vap->uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap->st_p2p_noa_param.uc_count = uc_count;
    pst_dmac_vap->st_p2p_noa_param.ul_duration = ul_duration;
    pst_dmac_vap->st_p2p_noa_param.ul_interval = ul_interval;
    pst_dmac_vap->st_p2p_noa_param.ul_start_time = ul_start_tsf;
    return OAL_SUCC;
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_beacon_set_p2p_noa);
/*lint +e578*//*lint +e19*/

#endif
#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
 函 数 名  : dmac_sta_test_info_dump
 功能描述  : 仅用于测试，模拟host sleep场景
 输入参数  : uc_host_sleep
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月3日
    作    者   : l00311403
    修改内容   : 新生成函数
*****************************************************************************/
void dmac_sta_test_info_dump(mac_vap_stru *pst_mac_vap)
{
    mac_opmode_notify_stru *pst_opmode;

    OAL_IO_PRINT("uc_test_flag=%d\r\n", g_beacon_offload_test.uc_test_flag);
    OAL_IO_PRINT("uc_host_sleep=%d\r\n", g_beacon_offload_test.uc_host_sleep);
    OAL_IO_PRINT("uc_opmode_in_beacon=%d\r\n", g_beacon_offload_test.uc_opmode_in_beacon);
    OAL_IO_PRINT("uc_opmode=%d\r\n", g_beacon_offload_test.uc_opmode);

    pst_opmode = (mac_opmode_notify_stru*)&g_beacon_offload_test.uc_opmode;
    OAL_IO_PRINT("bit_channel_width=%d bit_rx_nss=%d bit_rx_nss_type=%d\r\n",
            pst_opmode->bit_channel_width, pst_opmode->bit_rx_nss, pst_opmode->bit_rx_nss_type);
    OAL_IO_PRINT("uc_csa_in_beacon=%d\r\n", g_beacon_offload_test.uc_csa_in_beacon);
    OAL_IO_PRINT("uc_announced_channel=%d\r\n", g_beacon_offload_test.uc_announced_channel);
    OAL_IO_PRINT("uc_switch_cnt=%d\r\n", g_beacon_offload_test.uc_switch_cnt);
    OAL_IO_PRINT("wmm in beacon=%d\r\n", pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented);
    OAL_IO_PRINT("wmm cnt=%d\r\n", pst_mac_vap->uc_wmm_params_update_count);
}


/*****************************************************************************
 函 数 名  : dmac_sta_host_force_sleep
 功能描述  : 仅用于测试，模拟host sleep场景
 输入参数  : uc_host_sleep
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月3日
    作    者   : l00311403
    修改内容   : 新生成函数
*****************************************************************************/
void dmac_sta_beacon_offload_test(mac_vap_stru *pst_mac_vap, oal_uint8 *uc_param)
{
    if (!uc_param)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRAME_FILTER, "dmac_sta_beacon_offload_test::uc_param null");
        return;
    }

    OAL_IO_PRINT("param[0]=%d param[1]=%d param[2]=%d param[3]=%d\r\n",
                uc_param[0], uc_param[1], uc_param[2], uc_param[3]);
    switch (uc_param[0])
    {
    case 0: //打开，关闭测试
        g_beacon_offload_test.uc_test_flag = uc_param[1];
        if (1 == uc_param[1])
        {
            oal_memset(&g_beacon_offload_test, 0, OAL_SIZEOF(g_beacon_offload_test));
            g_beacon_offload_test.uc_test_flag = uc_param[1];
            g_beacon_offload_test.uc_host_sleep = 0;
            g_beacon_offload_test.uc_opmode_in_beacon = 0;
            g_beacon_offload_test.uc_opmode = 0;
            g_beacon_offload_test.uc_csa_in_beacon = pst_mac_vap->st_ch_switch_info.en_csa_present_in_bcn;
            g_beacon_offload_test.uc_announced_channel = pst_mac_vap->st_ch_switch_info.uc_announced_channel;
            g_beacon_offload_test.uc_switch_cnt = pst_mac_vap->st_ch_switch_info.uc_ch_switch_cnt;
        }
        break;

    case 1: //手动模拟host sleep
        g_beacon_offload_test.uc_host_sleep = uc_param[1];
        break;

    case 2: //设置opmode ie
        g_beacon_offload_test.uc_opmode_in_beacon = uc_param[1];
        g_beacon_offload_test.uc_opmode = uc_param[2];
        break;

    case 3: //设置csa ie
        g_beacon_offload_test.uc_csa_in_beacon = uc_param[1];
        g_beacon_offload_test.uc_announced_channel = uc_param[2];
        g_beacon_offload_test.uc_switch_cnt = uc_param[3];
        break;

    case 4:
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented = uc_param[1];
        pst_mac_vap->uc_wmm_params_update_count = uc_param[2];
        break;

    default:
        OAL_IO_PRINT("wrong type\r\n");
        break;
    }

    dmac_sta_test_info_dump(pst_mac_vap);
    return;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_sta_opmode_is_changed
 功能描述  : 判断beacon帧中opmode ie相对于上一个beacon帧是否发生改变
 输入参数  : pst_mac_vap
             puc_frame_body
             us_frame_len
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : l00311403
    修改内容   : 新生成函数
*****************************************************************************/
oal_bool_enum_uint8 dmac_sta_host_is_sleep(void)
{
#ifdef _PRE_WLAN_CHIP_TEST
    if (g_beacon_offload_test.uc_test_flag && g_beacon_offload_test.uc_host_sleep)
    {
        return OAL_TRUE;
    }
#endif
    //l00311403 加上zourong的接口
    return OAL_FALSE;
}

/*****************************************************************************
 函 数 名  : dmac_sta_opmode_is_changed
 功能描述  : 判断beacon帧中opmode ie相对于上一个beacon帧是否发生改变
 输入参数  : pst_mac_vap
             puc_frame_body
             us_frame_len
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : l00311403
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_sta_opmode_is_changed(
                mac_vap_stru  *pst_mac_vap,
                mac_user_stru *pst_mac_user,
                oal_uint8     *puc_frame_body,
                oal_uint16    us_frame_len)
{
    oal_uint8              uc_modify_flag = OAL_FALSE;
#if defined _PRE_WLAN_FEATURE_OPMODE_NOTIFY || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
    mac_opmode_notify_stru *pst_opmode_notify;
    const oal_uint8        *puc_opmode_ie;

    if ((OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        || (OAL_FALSE == mac_mib_get_OperatingModeNotificationImplemented(pst_mac_vap)))
    {
        return OAL_FALSE;
    }

    puc_opmode_ie = mac_find_ie(MAC_EID_OPMODE_NOTIFY, puc_frame_body, us_frame_len);

    if (OAL_PTR_NULL == puc_opmode_ie)
    {
        return OAL_FALSE;
    }

    pst_opmode_notify = (mac_opmode_notify_stru *)(puc_opmode_ie + MAC_IE_HDR_LEN);

    if ( (1 == pst_opmode_notify->bit_rx_nss_type) &&
         (pst_opmode_notify->bit_rx_nss != pst_mac_user->uc_avail_bf_num_spatial_stream) )
    {
        mac_user_avail_bf_num_spatial_stream(pst_mac_user, pst_opmode_notify->bit_rx_nss);
        uc_modify_flag = OAL_TRUE;
    }

    if (pst_opmode_notify->bit_channel_width != pst_mac_user->en_avail_bandwidth)
    {
        mac_user_set_bandwidth_info(pst_mac_user, pst_opmode_notify->bit_channel_width, pst_mac_user->en_cur_bandwidth);
        uc_modify_flag = OAL_TRUE;
    }

    if ( pst_mac_user->uc_avail_num_spatial_stream !=
         OAL_MIN(pst_mac_vap->en_vap_rx_nss, pst_opmode_notify->bit_rx_nss))
    {
        mac_user_set_avail_num_spatial_stream(pst_mac_user, OAL_MIN(pst_mac_vap->en_vap_rx_nss, pst_opmode_notify->bit_rx_nss));
        uc_modify_flag = OAL_TRUE;
    }

    if (OAL_TRUE == uc_modify_flag)
    {
        OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                "{dmac_sta_opmode_is_changed::opmode changed=%d bit_channel_width=%d bit_rx_nss=%d bit_rx_nss_type=%d}\r\n",
                uc_modify_flag, pst_opmode_notify->bit_channel_width, pst_opmode_notify->bit_rx_nss,
                pst_opmode_notify->bit_rx_nss_type);
    }
#endif

    return uc_modify_flag;
}

/*****************************************************************************
 函 数 名  : dmac_sta_csa_is_changed
 功能描述  : 判断beacon帧中Channel Switch Annoucement ie相对于上一个beacon帧是
             否发生改变
 输入参数  : pst_mac_vap
             puc_frame_body
             us_frame_len
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : l00311403
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_sta_csa_is_changed(
                mac_vap_stru  *pst_mac_vap,
                oal_uint8     *puc_frame_body,
                oal_uint16    us_frame_len)
{
    const oal_uint8   *puc_csa_ie;
    oal_uint8         uc_new_chan = 0xff; /*当CSA IE不存在时*/
    oal_uint8         uc_old_chan;
    oal_uint8         uc_modify_flag = OAL_FALSE;

    puc_csa_ie = mac_find_ie(MAC_EID_CHANSWITCHANN, puc_frame_body, us_frame_len);

    if (OAL_PTR_NULL != puc_csa_ie)
    {
        uc_new_chan   = puc_csa_ie[MAC_IE_HDR_LEN + 1];
    }
    else
    {
        puc_csa_ie = mac_find_ie(MAC_EID_EXTCHANSWITCHANN, puc_frame_body, us_frame_len);
        if (OAL_PTR_NULL != puc_csa_ie)
        {
            uc_new_chan   = puc_csa_ie[MAC_IE_HDR_LEN + 2];
        }
        else
        {
            return OAL_FALSE;
        }
    }

    uc_old_chan = pst_mac_vap->st_ch_switch_info.uc_new_channel;
    if (uc_old_chan != uc_new_chan)
    {
        pst_mac_vap->st_ch_switch_info.uc_new_channel = uc_new_chan;
        uc_modify_flag = OAL_TRUE;
    }

    if (uc_modify_flag)
    {
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                        "dmac_sta_csa_is_changed::csa changed=%d", uc_modify_flag);
    }

    return uc_modify_flag;
}


/*****************************************************************************
 函 数 名  : dmac_sta_edca_is_changed
 功能描述  : 判断beacon帧中EDCA ie相对于上一个beacon帧是否发生改变
 输入参数  : pst_mac_vap
             puc_frame_body
             us_frame_len
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : l00311403
    修改内容   : 新生成函数
  2.日    期   : 2015年5月26日
    作    者   : wanran
    修改内容   : 只在多核下更新dmac的count
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_sta_edca_is_changed(
                mac_vap_stru  *pst_mac_vap,
                oal_uint8     *puc_frame_body,
                oal_uint16    us_frame_len)
{
    oal_uint8         uc_param_set_cnt;
    oal_uint8         uc_modify_flag = OAL_FALSE;
    const oal_uint8   *puc_edca_ie;

    puc_edca_ie = mac_find_vendor_ie(MAC_WLAN_OUI_MICROSOFT, MAC_WLAN_OUI_TYPE_MICROSOFT_WMM, puc_frame_body, us_frame_len);

    if (OAL_PTR_NULL == puc_edca_ie)
    {
        return OAL_FALSE;
    }

    if (OAL_TRUE == mac_is_wmm_ie((oal_uint8*)puc_edca_ie))
    {
        uc_param_set_cnt = puc_edca_ie[DMAC_WMM_QOS_PARAMS_HDR_LEN] & 0x0F;

        if (uc_param_set_cnt != pst_mac_vap->uc_wmm_params_update_count)
        {
            OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                    "dmac_sta_edca_is_changed::edca is changed=%d, old_cnt=%d new_cnt=%d\r\n",
                    uc_modify_flag, pst_mac_vap->uc_wmm_params_update_count, uc_param_set_cnt);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            mac_vap_set_wmm_params_update_count(pst_mac_vap, uc_param_set_cnt);
#endif
            uc_modify_flag = OAL_TRUE;
        }
    }

    return uc_modify_flag;
}

/*****************************************************************************
 函 数 名  : dmac_sta_channel_is_changed
 功能描述  : 判断beacon帧中DSSS ie信息，是否和sta vap 中保存的信道信息相同。
 输入参数  : pst_mac_vap        staut vap 结构
             puc_frame_body     beacon 帧体
             us_frame_len       beacon 整体长度
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   : d00194999
    修改内容   : 新生成函数
*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_sta_channel_is_changed(
                mac_vap_stru  *pst_mac_vap,
                oal_uint8     *puc_frame_body,
                oal_uint16    us_frame_len)
{
    oal_uint8        uc_channel;
    oal_uint8        uc_modify_flag;
    oal_uint8       *puc_dsss_ie;

    //puc_dsss_ie = mac_get_dsss_param_ie(puc_frame_body, us_frame_len, 0);
    puc_dsss_ie = mac_find_ie(MAC_EID_DSPARMS, puc_frame_body, us_frame_len);
    if (OAL_PTR_NULL == puc_dsss_ie)
    {
        return OAL_FALSE;
    }

    uc_channel = puc_dsss_ie[MAC_IE_HDR_LEN];

    if (uc_channel != pst_mac_vap->st_channel.uc_chan_number)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                "dmac_sta_channel_is_changed::AP channel is changed, old_channel=%d new_channel=%d\r\n",
                pst_mac_vap->st_channel.uc_chan_number, uc_channel);
        uc_modify_flag = OAL_TRUE;
    }
    else
    {
        uc_modify_flag = OAL_FALSE;
    }

    return uc_modify_flag;
}

/*****************************************************************************
 函 数 名  : dmac_sta_update_slottime
 功能描述  : 在有non_erp站点时更新slottime
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月22日
    作    者   : y00196452
    修改内容   : 新生成函数
*****************************************************************************/
oal_void dmac_sta_update_slottime(mac_vap_stru* pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 *puc_payload, oal_uint16 us_msg_len)
{
    dmac_vap_stru              *pst_dmac_vap;
    mac_erp_params_stru        *pst_erp_ie;
    const oal_uint8            *puc_erp_ie;
    hal_to_dmac_device_stru    *pst_hal_device;

    pst_dmac_vap = (dmac_vap_stru*)pst_mac_vap;

    /* 保存non_erp信息,sta模式下，保存BSS中是否有erp站点的信息 */
    puc_erp_ie = mac_find_ie(MAC_EID_ERP, puc_payload, us_msg_len);
    if (OAL_PTR_NULL == puc_erp_ie)
    {
        return;
    }

    /* NON_ERP站点进出时更新slottime类型 */
    pst_erp_ie = (mac_erp_params_stru*)&(puc_erp_ie[MAC_IE_HDR_LEN]);
    if (pst_dmac_vap->en_non_erp_exist != pst_erp_ie->bit_non_erp)
    {
        pst_dmac_vap->en_non_erp_exist = pst_erp_ie->bit_non_erp;

        hal_get_hal_to_dmac_device(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, &pst_hal_device);
        if (OAL_PTR_NULL == pst_hal_device)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_sta_update_slottime::hal dev null, fail to update slot time.}");
            return;
        }

        /* 有NON_ERP站点时，使用short slottime发数据；否则使用long slottime */
        hal_cfg_slottime_type(pst_hal_device, pst_erp_ie->bit_non_erp);
    }
}

/*****************************************************************************
 函 数 名  : dmac_sta_up_rx_beacon
 功能描述  : 判断beacon帧是否需要上报HMAC
 输入参数  : pst_dmac_vap
             pst_netbuf
 输出参数  : pen_go_on
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : l00311403
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  dmac_sta_up_rx_beacon(
                dmac_vap_stru   *pst_dmac_vap,
                oal_netbuf_stru *pst_netbuf,
                oal_uint8       *pen_go_on)
{
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    mac_vap_stru               *pst_mac_vap;
    mac_user_stru              *pst_mac_user;
    dmac_rx_ctl_stru           *pst_rx_ctl;
    mac_rx_ctl_stru            *pst_rx_info;
    oal_uint8                  *puc_payload;
    oal_uint16                  us_ie_offset;
    oal_uint16                  us_msg_len;
    oal_uint32                  ul_ret;
    oal_uint16                  us_beacon_timeout_adjust    =   0UL;
#if (_PRE_OS_VERSION_RAW == _PRE_PRODUCT_ID_HI1102_DEV)
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    oal_uint16                  us_in_tbtt_adjust           =   0UL;
#endif
#endif

    *pen_go_on = OAL_FALSE;

    pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

    pst_rx_ctl     = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr  = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));
    pst_rx_info    = (mac_rx_ctl_stru *)(&(pst_rx_ctl->st_rx_info));
    puc_payload    = MAC_GET_RX_PAYLOAD_ADDR(pst_rx_info, pst_netbuf);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    us_msg_len     = pst_rx_info->us_frame_len - pst_rx_info->bit_mac_header_len; /*帧体长度*/
#else
    us_msg_len     = pst_rx_info->us_frame_len - pst_rx_info->uc_mac_header_len; /*帧体长度*/
#endif
    /* 来自其它bss的Beacon不做处理 */
    ul_ret = oal_compare_mac_addr(pst_mac_vap->auc_bssid, pst_frame_hdr->auc_address3);
    if(0 != ul_ret)
    {
        return OAL_SUCC;
    }

    dmac_vap_linkloss_clean(pst_dmac_vap);

    /* 成功接收到beacon, beacon timeout超时的计数清零 */
    pst_dmac_vap->bit_beacon_timeout_times = 0;



#if (_PRE_OS_VERSION_RAW == _PRE_PRODUCT_ID_HI1102_DEV)
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    PM_Driver_Cbb_Mac_WlanRxBeaconAdjust(&us_in_tbtt_adjust, &us_beacon_timeout_adjust);
#endif
#endif

    hal_set_beacon_timeout_val(pst_dmac_vap->pst_hal_device, pst_dmac_vap->us_beacon_timeout + us_beacon_timeout_adjust);

    hal_set_psm_ext_tbtt_offset(pst_dmac_vap->pst_hal_vap,pst_dmac_vap->us_ext_tbtt_offset);

    hal_set_psm_tbtt_offset(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->us_in_tbtt_offset);

#ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    pst_dmac_vap->uc_beacon_miss_cnt = 0;
#endif

    /* 如果host侧不是处于深睡状态，beacon直接上报HMAC */
#ifdef _PRE_WIFI_DMT
    *pen_go_on = OAL_TRUE;
    return OAL_SUCC;
#else

    us_ie_offset = MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
    puc_payload += us_ie_offset;
    us_msg_len  -= us_ie_offset;
    /* BEGIN:DTS2015052810869 STA发现AP信道修改，则删除用户，而不发送去认证帧 */
    if (OAL_TRUE == dmac_sta_channel_is_changed(pst_mac_vap, puc_payload, us_msg_len))
    {
        ul_ret = dmac_send_disasoc_misc_event(pst_mac_vap, pst_mac_vap->uc_assoc_vap_id, DMAC_DISASOC_MISC_CHANNEL_MISMATCH);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(0, OAM_SF_WIFI_BEACON,
                       "{dmac_sta_up_rx_beacon::dmac_send_disasoc_misc_event fail.}");
        }
    }
    /* END:DTS2015052810869 STA发现AP信道修改，则删除用户，而不发送去认证帧 */

    pst_mac_user = (mac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&(pst_rx_ctl->st_rx_info)));
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
                       "{dmac_sta_up_rx_beacon::pst_mac_user null}");
        return OAL_FALSE;
    }

    /* 有non_erp站点时使用long slottime */
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        dmac_sta_update_slottime(pst_mac_vap, pst_mac_user, puc_payload, us_msg_len);
    }

    //dmac_sta_update_txop_process(pst_mac_vap, pst_mac_user);

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    if ((mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info)) != WLAN_MIB_PWR_MGMT_MODE_PWRSAVE))
    {
        *pen_go_on = OAL_TRUE;
        return OAL_SUCC;
    }
#endif
#endif

    if ( (OAL_TRUE == dmac_sta_opmode_is_changed(pst_mac_vap, pst_mac_user, puc_payload, us_msg_len)) ||
          (OAL_TRUE == dmac_sta_csa_is_changed(pst_mac_vap, puc_payload, us_msg_len)) ||
          (OAL_TRUE == dmac_sta_edca_is_changed(pst_mac_vap, puc_payload, us_msg_len)))
    {
        *pen_go_on = OAL_TRUE;
    }

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_FRAME_FILTER,
    //                "dmac_sta_up_rx_beacon::pen_go_on=%d", *pen_go_on);

    return OAL_SUCC;
}

/****************************************************************************
 函 数 名  : dmac_beacon_timeout_event_hander
 功能描述  : 等待beacon超时中断处理事件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月30日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_beacon_timeout_event_hander(frw_event_mem_stru *pst_event_mem)
{
#ifdef _PRE_WLAN_FEATURE_STA_PM
    dmac_vap_stru               *pst_dmac_vap;
    frw_event_stru              *pst_event;
    mac_device_stru             *pst_mac_device;
    mac_sta_pm_handler_stru     *pst_mac_sta_pm_handle;
    oal_uint16                  us_beacon_timeout_adjust    =   0UL;
#if (_PRE_OS_VERSION_RAW == _PRE_PRODUCT_ID_HI1102_DEV)
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    oal_uint16                  us_in_tbtt_adjust           =   0UL;
#endif
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_beacon_timeout_event_hander:event is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)(pst_event_mem->puc_data);
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);

    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WIFI_BEACON, "{dmac_beacon_timeout_event_hander:vap is null }");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
    if (OAL_PTR_NULL == pst_mac_device || OAL_PTR_NULL == pst_mac_sta_pm_handle)
    {
        OAM_ERROR_LOG2(0, OAM_SF_WIFI_BEACON, "{beacon timeout has null point: mac_device:%p sta_pm_handle:%p.}",pst_mac_device,pst_mac_sta_pm_handle);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)
    {
        return OAL_SUCC;
    }


#if (_PRE_OS_VERSION_RAW == _PRE_PRODUCT_ID_HI1102_DEV)
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    PM_Driver_Cbb_Mac_WlanRxTimeOutAdjust(&us_in_tbtt_adjust, &us_beacon_timeout_adjust);
#endif
#endif

    hal_set_beacon_timeout_val(pst_dmac_vap->pst_hal_device, pst_dmac_vap->us_beacon_timeout + us_beacon_timeout_adjust);

    /*每次发生beacon timeout,外置和内置offset提前,收到beacon随即恢复*/
    //hal_set_psm_ext_tbtt_offset(pst_dmac_vap->pst_hal_vap, (pst_dmac_vap->us_ext_tbtt_offset+1));
    hal_set_psm_tbtt_offset(pst_dmac_vap->pst_hal_vap, (pst_dmac_vap->us_in_tbtt_offset + DMAC_BEACON_TIMEOUT_FIX_OFFSET));

    /* 接收beacon超时计数 */
    pst_dmac_vap->bit_beacon_timeout_times++;

    /* 接收beacon超时计数 */
    pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_BEACON_TIMEOUT_CNT]++;

    if(pst_mac_sta_pm_handle->ul_psm_pkt_cnt || pst_mac_device->pst_device_stru->ul_rx_rate > RX_DATA_RATE)
    {
        return OAL_SUCC;
    }

    /* p2p 开启了noa oppps时beacon超时不投睡眠票,仅在noa oppps期间浅睡 */
    if (OAL_TRUE == (oal_uint8)IS_P2P_PS_ENABLED(pst_dmac_vap))
    {
        return OAL_SUCC;
    }

    /* 低功耗模式下才会有beacon timeout 睡眠 */
    if (WLAN_MIB_PWR_MGMT_MODE_PWRSAVE == (mac_mib_get_powermanagementmode(&(pst_dmac_vap->st_vap_base_info))))
    {
        /* 接收beacon超时计数且投票睡的计数 */
        pst_mac_sta_pm_handle->aul_pmDebugCount[PM_MSG_BCN_TOUT_SLEEP]++;
        pst_mac_sta_pm_handle->en_ps_deep_sleep = OAL_TRUE;
        if (OAL_TRUE == dmac_psm_is_tid_queues_empty(pst_dmac_vap))
        {
        	dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_BEACON_TIMEOUT, 0, OAL_PTR_NULL);
        }
    }
#endif

    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
extern oal_uint64 g_ull_sta0_tsf_timestamp;
extern oal_uint64 g_ull_sta1_tsf_timestamp;
/****************************************************************************
 函 数 名  : dmac_get_tsf_from_bcn
 功能描述  : 通过Beacon帧获取tsf, 保证该函数是STA调用且只有Beacon帧模式调用
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月12日
    作    者   : z00241943
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_get_tsf_from_bcn(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    oal_uint32                          ul_beacon_timestamp_low    = 0;
    oal_uint64                          ul_beacon_timestamp_high   = 0;
    oal_uint64                          ul_beacon_timestamp        = 0;
    oal_uint8                          *puc_payload                = OAL_PTR_NULL;

    puc_payload = OAL_NETBUF_PAYLOAD(pst_netbuf);

    ul_beacon_timestamp_low  =  puc_payload[0];
    ul_beacon_timestamp_low |= (puc_payload[1] << 8);
    ul_beacon_timestamp_low |= (puc_payload[2] << 16);
    ul_beacon_timestamp_low |= (puc_payload[3] << 24);

    ul_beacon_timestamp_high  =  puc_payload[4];
    ul_beacon_timestamp_high |= (puc_payload[5] << 8);
    ul_beacon_timestamp_high |= (puc_payload[6] << 16);
    ul_beacon_timestamp_high |= ((oal_uint32)puc_payload[7] << 24);

    ul_beacon_timestamp  = ul_beacon_timestamp_low;
    ul_beacon_timestamp |= (ul_beacon_timestamp_high << 32);

    if ((IS_LEGACY_VAP(&pst_dmac_vap->st_vap_base_info)))
    {
        g_ull_sta0_tsf_timestamp  = ul_beacon_timestamp;
    }
    else
    {
        g_ull_sta1_tsf_timestamp  = ul_beacon_timestamp;
    }
}
#endif
#ifdef _PRE_WLAN_FEATURE_TSF_SYNC
/****************************************************************************
 函 数 名  : dmac_sync_tsf_by_bcn
 功能描述  : tp_link_841 timestamps error end DTS2013101403081
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月12日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_sync_tsf_by_bcn(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    oal_uint16                          us_beacon_interval         = 0;
    oal_uint32                          ul_beacon_timestamp_low    = 0;
    oal_uint64                          ul_beacon_timestamp_high   = 0;
    oal_uint64                          ul_beacon_timestamp        = 0;
    oal_uint8                           *puc_payload			   = OAL_PTR_NULL;

    if (pst_dmac_vap->uc_beacon_miss_cnt != 0)
    {
        pst_dmac_vap->uc_beacon_miss_cnt--;  /* dec after the beacon has been received */
    }

    puc_payload         = OAL_NETBUF_PAYLOAD(pst_netbuf);

    /*get the timestamp and beacon interval*/
    ul_beacon_timestamp_low  = puc_payload[0];
    ul_beacon_timestamp_low |= (puc_payload[1] << 8);
    ul_beacon_timestamp_low |= (puc_payload[2] << 16);
    ul_beacon_timestamp_low |= (puc_payload[3] << 24);

    ul_beacon_timestamp_high  =  puc_payload[4];
    ul_beacon_timestamp_high |= (puc_payload[5] << 8);
    ul_beacon_timestamp_high |= (puc_payload[6] << 16);
    /*lint -e647*/
    ul_beacon_timestamp_high |= (puc_payload[7] << 24);
    /*lint +e647*/

    /* 用于keep alive计时之用 */
    //g_stKeepAliveTime.ulLow  = beacon_timestamp_low;
    //g_stKeepAliveTime.ulHigh = beacon_timestamp_high;

    ul_beacon_timestamp  = ul_beacon_timestamp_low;

    /*lint -e647*/
    ul_beacon_timestamp |= (ul_beacon_timestamp_high << 32);
    /*lint +e647*/

    us_beacon_interval   = puc_payload[MAC_TIME_STAMP_LEN];
    us_beacon_interval  |= (puc_payload[MAC_TIME_STAMP_LEN + 1] << 8);


    if (0 != pst_dmac_vap->uc_beacon_miss_cnt)
    {

        //OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_sync_tsf_by_bcn::beacon miss cnt:[%d]",pst_dmac_vap->uc_beacon_miss_cnt);
        /*if beacon is missed,then clear saved*/
        pst_dmac_vap->ul_old_beacon_timestamp = 0;
        pst_dmac_vap->uc_beacon_miss_cnt = 0;
    }
    else if ((0 == pst_dmac_vap->uc_beacon_miss_cnt) && (0 == pst_dmac_vap->ul_old_beacon_timestamp))
    {
        /*saved the first timestamp*/
        pst_dmac_vap->ul_old_beacon_timestamp = ul_beacon_timestamp;
    }
    else if ((0 == pst_dmac_vap->uc_beacon_miss_cnt) && (0 != pst_dmac_vap->ul_old_beacon_timestamp))
    {
        /* cal the SyncTsfValue after receive the second beacon beacon帧会有抖动，需要加入5ms防抖 */
        if (((oal_uint64)((ul_beacon_timestamp >> 10) - (pst_dmac_vap->ul_old_beacon_timestamp >> 10))) < (oal_uint64)(us_beacon_interval - 5))
        {
            pst_dmac_vap->us_sync_tsf_value = us_beacon_interval - (oal_uint16)((oal_uint64)((ul_beacon_timestamp >> 10) - ((pst_dmac_vap->ul_old_beacon_timestamp) >> 10))) + 70;
            OAM_INFO_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_sync_tsf_by_bcn::sync value:[%d],beacon interval:[%d],\
                                         new time:[%lu],old time:[%lu]}",pst_dmac_vap->us_sync_tsf_value,us_beacon_interval,(ul_beacon_timestamp),((pst_dmac_vap->ul_old_beacon_timestamp)));

        }
        else
        {
            pst_dmac_vap->us_sync_tsf_value = 0;
        }


        /*clear after fix once*/
        pst_dmac_vap->ul_old_beacon_timestamp  = ul_beacon_timestamp;
    }
}
#endif /* TSF_SYNC_OPT */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

