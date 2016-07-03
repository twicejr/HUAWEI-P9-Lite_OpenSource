


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_LTECOEX

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "dmac_ltecoex_verify.h"
#include "oal_util.h"
#include "mac_resource.h"
#include "dmac_vap.h"
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_board.h"
#include "oam_wdk.h"
#include "oam_ext_if.h"
#include "oal_mem.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_LTECOEX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if 0

/*****************************************************************************
  3 函数实现
*****************************************************************************/


oal_void dmac_btcoex_soft_rst(oal_void)
{
    hal_set_btcoex_soft_rst();
}


oal_void dmac_btcoex_soc_bt_int_mask(oal_uint8 uc_int_en)
{
    hal_set_btcoex_soc_bt_int_mask(uc_int_en);
}


oal_void dmac_btcoex_soc_wifi_switch_bt_timeout_set(oal_uint16 uc_time)
{
    hal_set_btcoex_soc_wifi_switch_bt_timeout(uc_time);
}


oal_uint16 dmac_btcoex_soc_wifi_switch_bt_timeout_get(oal_void)
{
    oal_uint16 us_val;
    hal_get_btcoex_soc_wifi_switch_bt_timeout(&us_val);
    return us_val;
}


oal_void dmac_btcoex_soc_bt_switch_wifi_timeout_set(oal_uint16 uc_time)
{
    hal_set_btcoex_soc_bt_switch_wifi_timeout(uc_time);
}


oal_uint16 dmac_btcoex_soc_bt_switch_wifi_timeout_get(oal_void)
{
    oal_uint16 us_val;
    hal_get_btcoex_soc_bt_switch_wifi_timeout(&us_val);
    return us_val;
}


oal_void dmac_btcoex_soc_int_en(oal_uint8 uc_int_en)
{
    hal_set_btcoex_soc_int_en(uc_int_en);
}



oal_void dmac_btcoex_abort_start_cnt_clear(oal_void)
{
    hal_set_btcoex_abort_start_cnt_clear();
}


oal_void dmac_btcoex_abort_done_cnt_clear(oal_void)
{
    hal_set_btcoex_abort_done_cnt_clear();
}


oal_void dmac_btcoex_abort_end_cnt_clear(oal_void)
{
    hal_set_btcoex_abort_end_cnt_clear();
}


oal_void dmac_btcoex_preempt_cnt_clear(oal_void)
{
    hal_set_btcoex_preempt_cnt_clear();
}


oal_void dmac_btcoex_post_preempt_succ_cnt_clear(oal_void)
{
    hal_set_btcoex_post_preempt_succ_cnt_clear();
}


oal_void dmac_btcoex_post_preempt_fail_cnt_clear(oal_void)
{
    hal_set_btcoex_post_preempt_fail_cnt_clear();
}


oal_uint8 dmac_btcoex_bt_ble_mode_get(oal_void)
{
    oal_uint8 uc_val;
    hal_get_btcoex_bt_ble_mode(&uc_val);
    return uc_val;
}


oal_uint8 dmac_btcoex_mode_select_get(oal_void)
{
    oal_uint8 uc_val;
    hal_get_btcoex_mode_select(&uc_val);
    return uc_val;
}


oal_uint8 dmac_btcoex_abort_preempt_time_out_get(oal_void)
{
    oal_uint8 uc_val;
    hal_get_btcoex_abort_preempt_time_out(&uc_val);
    return uc_val;
}

oal_uint8 dmac_btcoex_abort_preempt_done_get(oal_void)
{
    oal_uint8 uc_val;
    hal_get_btcoex_abort_preempt_done(&uc_val);
    return uc_val;
}



oal_uint8 dmac_btcoex_abort_post_preempt_done_get(oal_void)
{
    oal_uint8 uc_val;
    hal_get_btcoex_abort_post_preempt_done(&uc_val);
    return uc_val;
}


oal_void dmac_btcoex_post_preempt_tx_cnt_set(oal_uint8 uc_post_preempt_cnt)
{
    hal_set_btcoex_post_preempt_tx_cnt(uc_post_preempt_cnt);
}

oal_uint8 dmac_btcoex_post_preempt_tx_cnt_get(oal_void)
{
    oal_uint8 uc_val;
    hal_get_btcoex_post_preempt_tx_cnt(&uc_val);
    return uc_val;
}



oal_void dmac_btcoex_coex_abort_en_set(oal_uint8 ul_abort_en)
{
    hal_set_btcoex_coex_abort_en(ul_abort_en);
}


oal_uint8 dmac_btcoex_coex_abort_en_get(oal_void)
{
    oal_uint8 uc_val;
    hal_get_btcoex_coex_abort_en(&uc_val);
    return uc_val;
}


oal_void dmac_btcoex_all_abort_preempt_type_set(oal_uint32 uc_preempt_type)
{
    hal_set_btcoex_all_abort_preempt_type(uc_preempt_type);
}

oal_uint8 dmac_btcoex_all_abort_preempt_type_get(oal_void )
{
    oal_uint8 uc_val;
    hal_get_btcoex_all_abort_preempt_type(&uc_val);
    return uc_val;
}


oal_void dmac_btcoex_abort_selfcts_duration_set(oal_uint32 ul_selfcts_duration)
{
    hal_set_btcoex_abort_selfcts_duration(ul_selfcts_duration);
}



oal_uint32 dmac_btcoex_abort_selfcts_duration_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_selfcts_duration(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_abort_selfcts_phy_mode_set(oal_uint32 ul_selfcts_phy_mode)
{
    /*
    [31:31] smothing
    [28:27] Sounding mode
    [23:16] Power level:
            [23:22] dac_gain_level  [21:18]micro_tx_power_gain_level  [17:17]:pa_gain_leval  [16:16]:upc_gain_level
    [6:3]   freq bandwidth mode:
            0000:BW20   0100:BW40  0101:BW_20-Duplicate Legacy in 40MHz
            1000: BW80   1001: BW_20 - Duplicate Legacy in 80MHz
            1100: BW160  1101: BW_20 - Duplicate Legacy in 160MHz
            1111: BW80_80
    [2:2]   Channel Code
    [1:0]   extended spatial streams
    */
    hal_set_btcoex_abort_selfcts_phy_mode(ul_selfcts_phy_mode);
}



oal_uint32 dmac_btcoex_abort_selfcts_phy_mode_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_selfcts_phy_mode(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_abort_selfcts_data_rate_set(oal_uint32 ul_selfcts_data_rate)
{
    hal_set_btcoex_abort_selfcts_data_rate(ul_selfcts_data_rate);
}



oal_uint32 dmac_btcoex_abort_selfcts_data_rate_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_selfcts_data_rate(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_abort_cf_end_phy_mode_set(oal_uint32 ul_cfend_phy_mode)
{
    hal_set_btcoex_abort_cf_end_phy_mode(ul_cfend_phy_mode);
}



oal_uint32 dmac_btcoex_abort_cf_end_phy_mode_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_cf_end_phy_mode(&ul_val);
    return ul_val;
}


oal_uint32 dmac_btcoex_abort_cf_end_data_rate_get(oal_void )
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_cf_end_data_rate(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_abort_cf_end_data_rate_set(oal_uint32 ul_cfend_data_rate)
{
    hal_set_btcoex_abort_cf_end_data_rate(ul_cfend_data_rate);
}



oal_void dmac_btcoex_occupied_period_set(oal_uint32 ul_occupied_period)
{
    hal_set_btcoex_occupied_period(ul_occupied_period);
}



oal_uint32 dmac_btcoex_occupied_period_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_occupied_period(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_post_preempt_timeout_val_set(oal_uint32 ul_post_preempt_time)
{
    hal_set_btcoex_post_preempt_timeout_val(ul_post_preempt_time);
}



oal_uint32 dmac_btcoex_post_preempt_timeout_val_get(oal_void )
{
    oal_uint32 ul_val;
    hal_get_btcoex_post_preempt_timeout_val(&ul_val);
    return ul_val;
}


oal_void dmac_btcoex_abort_timeout_val_set(oal_uint16 us_bt_time)
{
    hal_set_btcoex_abort_timeout_val(us_bt_time);
}



oal_uint16 dmac_btcoex_abort_timeout_val_get(oal_void)
{
    oal_uint16 us_val;
    hal_get_btcoex_abort_timeout_val(&us_val);
    return us_val;
}



oal_void dmac_blecoex_abort_timeout_val_set(oal_uint16 us_ble_time)
{
    hal_set_blecoex_abort_timeout_val(us_ble_time);
}



oal_uint16 dmac_blecoex_abort_timeout_val_get(oal_void )
{
    oal_uint16 us_val;
    hal_get_blecoex_abort_timeout_val(&us_val);
    return us_val;
}



oal_void dmac_btcoex_abort_null_phy_mode_set(oal_uint32 ul_null_phy_mode)
{
    hal_set_btcoex_abort_null_phy_mode(ul_null_phy_mode);
}



oal_uint32 dmac_btcoex_abort_null_phy_mode_get(oal_void )
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_null_phy_mode(&ul_val);
    return ul_val;
}


oal_void dmac_btcoex_abort_null_data_rate_set(oal_uint32 ul_null_data_rate)
{
    hal_set_btcoex_abort_null_data_rate(ul_null_data_rate);
}



oal_uint32 dmac_btcoex_abort_null_data_rate_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_null_data_rate(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_abort_qos_null_seq_num_set(oal_uint32 ul_qosnull_seq_num)
{
    hal_set_btcoex_abort_qos_null_seq_num(ul_qosnull_seq_num);
}



oal_uint32 dmac_btcoex_abort_qos_null_seq_num_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_qos_null_seq_num(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_abort_null_buff_addr_set(oal_uint32 ul_abort_null_buff_addr)
{
    hal_set_btcoex_abort_null_buff_addr(ul_abort_null_buff_addr);
}



oal_uint32 dmac_btcoex_abort_null_buff_addr_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_null_buff_addr(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_max_cnt_set(oal_uint32 ul_abort_max_cnt)
{
    hal_set_btcoex_max_cnt(ul_abort_max_cnt);
}



oal_uint32 dmac_btcoex_max_cnt_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_max_cnt(&ul_val);
    return ul_val;
}


oal_void dmac_btcoex_rf_stable_time_set(oal_uint32 ul_rf_stable_time)
{
    hal_set_btcoex_rf_stable_time(ul_rf_stable_time);
}



oal_uint32 dmac_btcoex_rf_stable_time_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_rf_stable_time(&ul_val);
    return ul_val;
}



oal_uint32 dmac_btcoex_abort_start_cnt_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_start_cnt(&ul_val);
    return ul_val;
}


oal_uint32 dmac_btcoex_abort_done_cnt_get(oal_void )
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_done_cnt(&ul_val);
    return ul_val;
}




oal_uint32 dmac_btcoex_abort_end_cnt_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_abort_end_cnt(&ul_val);
    return ul_val;
}


oal_uint32 dmac_btcoex_preempt_cnt_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_preempt_cnt(&ul_val);
    return ul_val;
}



oal_uint32 dmac_btcoex_post_preempt_cnt_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_post_preempt_cnt(&ul_val);
    return ul_val;
}



oal_uint32 dmac_btcoex_post_preempt_fail_cnt_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_post_preempt_fail_cnt(&ul_val);
    return ul_val;
}


oal_uint32 dmac_btcoex_phy_tx_r_status_get(oal_void)
{
    oal_uint32 ul_val;
    hal_get_btcoex_phy_tx_r_status(&ul_val);
    return ul_val;
}



oal_void dmac_btcoex_sw_all_abort_req_set(oal_uint8 uc_sw_abort_req)
{
    hal_set_btcoex_sw_all_abort_req(uc_sw_abort_req);
}

oal_uint8 dmac_btcoex_sw_all_abort_req_get(oal_void)
{
    oal_uint8 uc_val;
    hal_get_btcoex_sw_all_abort_req(&uc_val);
    return uc_val;
}

oal_void dmac_btcoex_sw_all_abort_ctrl_set(oal_uint8 uc_sw_abort_ctrl)
{
    hal_set_btcoex_sw_all_abort_ctrl(uc_sw_abort_ctrl);
}


oal_void dmac_btcoex_sw_all_abort_mode_set(oal_uint8 uc_sw_abort_mode)
{
    hal_set_btcoex_sw_all_abort_mode(uc_sw_abort_mode);
}


oal_uint8 dmac_btcoex_sw_all_abort_mode_get(oal_void )
{
    oal_uint8 uc_val;
    hal_get_btcoex_sw_all_abort_mode(&uc_val);
    return uc_val;
}


oal_void dmac_btcoex_set_wifi_high_occup_time(oal_uint16 ul_time)
{
    hal_set_btcoex_wifi_high_occup_time(ul_time);
}


void dmac_btcoex_encap_null_data(oal_uint8 *puc_frame, oal_uint8 *puc_da, oal_uint8 *puc_sa)
{
    oal_uint16  us_frame_ctl;

    /* 填写帧头,其中from ds为1，to ds为0，ps=1 因此frame control的第二个字节为12 */
    us_frame_ctl = (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | 0x1100;

    /*
     *  +----------+----------+----------+----------+----------+----------+
     *  | frame    | Duration/|  ADDR1   |  ADDR2   | ADDR3    | SeqCtl   |
     *  | control  |    ID    |          |          |          |          |
     *  +----------+----------+----------+----------+----------+----------+
     *
     *  SeqCtl : sw set frag_num=0
     *           hw will set seq num
     */

    mac_null_data_encap(puc_frame, us_frame_ctl, puc_da, puc_sa);

    puc_frame[22] = 0;
    puc_frame[23] = 0;
}



oal_uint32 dmac_btcoex_init_null_data(oal_uint8 *puc_frame,oal_uint8 *puc_da, oal_uint8 *puc_sa)
{
    mac_ieee80211_frame_stru        *pst_mac_header;


    /* 申请最大的80211头 */
    pst_mac_header = (mac_ieee80211_frame_stru *)puc_frame;

    /* 填写帧头*/
    dmac_btcoex_encap_null_data((oal_uint8*)pst_mac_header,puc_da,puc_sa);
    pst_mac_header->st_frame_control.bit_power_mgmt = 1;
    pst_mac_header->bit_seq_num = 1;

    dmac_btcoex_abort_null_buff_addr_set((oal_uint32)pst_mac_header);
    OAM_ERROR_LOG1(0, OAM_SF_COEX, "{(oal_uint32)pst_mac_header = 0x%x.}",(oal_uint32)pst_mac_header);

   // while(count < 24)
    {
        OAM_ERROR_LOG_ALTER(0, OAM_SF_COEX, "{bit_power_mgmt[0x%x], bit_protocol_version[0x%x], bit_to_ds[0x%x],
                bit_type[0x%x],bit_sub_type[0x%x], bit_seq_num[%d],bit_duration_value[%d].}",
                7,
                pst_mac_header->st_frame_control.bit_power_mgmt,
                pst_mac_header->st_frame_control.bit_protocol_version,
                pst_mac_header->st_frame_control.bit_to_ds,
                pst_mac_header->st_frame_control.bit_type,
                pst_mac_header->st_frame_control.bit_sub_type,
                pst_mac_header->bit_seq_num,
                pst_mac_header->bit_duration_value);
        OAM_ERROR_LOG4(0, OAM_SF_COEX, "{auc_address3 %02X:XX:XX:%02X:%02X:%02X.}",
            pst_mac_header->auc_address3[0],pst_mac_header->auc_address3[3],pst_mac_header->auc_address3[4],pst_mac_header->auc_address3[5]);
        OAM_ERROR_LOG4(0, OAM_SF_COEX, "{auc_address2 %02X:XX:XX:%02X:%02X:%02X.}",
            pst_mac_header->auc_address2[0],pst_mac_header->auc_address2[3],pst_mac_header->auc_address2[4],pst_mac_header->auc_address2[5]);
        OAM_ERROR_LOG4(0, OAM_SF_COEX, "{auc_address1 %02X:XX:XX:%02X:%02X:%02X.}",
            pst_mac_header->auc_address1[0],pst_mac_header->auc_address1[3],pst_mac_header->auc_address1[4],pst_mac_header->auc_address1[5]);

    }

    return OAL_SUCC;
}



void dmac_btcoex_encap_qosnull_data(oal_uint8 *puc_frame, oal_uint8 *puc_da, oal_uint8 *puc_sa)
{


    oal_uint16  us_frame_ctl;

    /* 填写帧头,其中from ds为1，to ds为0，ps=1 因此frame control的第二个字节为12 */
    us_frame_ctl = (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS_NULL) | 0x1100;

    /*
     *  +----------+----------+----------+----------+----------+----------+
     *  | frame    | Duration/|  ADDR1   |  ADDR2   | ADDR3    | SeqCtl   |
     *  | control  |    ID    |          |          |          |          |
     *  +----------+----------+----------+----------+----------+----------+
     *
     *  SeqCtl : sw set frag_num=0
     *           hw will set seq num
     */

    mac_null_data_encap((oal_uint8*)puc_frame, us_frame_ctl, puc_da, puc_sa);

    puc_frame[22] = 0;
    puc_frame[23] = 0;

}


OAL_STATIC oal_uint32 dmac_btcoex_init_qosnull_data(oal_void)
{


     mac_ieee80211_qoscoex_frame_stru         *pst_mac_header;
     oal_uint8                       count = 0;


     /* 申请最大的80211头 */
     pst_mac_header = (mac_ieee80211_qoscoex_frame_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_SHARED_MGMT_PKT,MAC_80211_QOS_FRAME_LEN,OAL_FALSE);
     if (OAL_PTR_NULL == pst_mac_header)
     {
         OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_psm_send_null_data_ap::pst_mac_header null.}");

         return OAL_ERR_CODE_ALLOC_MEM_FAIL;
     }

     /* 填写帧头*/
     dmac_btcoex_encap_qosnull_data((oal_uint8*)pst_mac_header,g_auc_ap_bssid,g_auc_sta_mac);
     pst_mac_header->st_frame_control.bit_power_mgmt = 1;
     pst_mac_header->bit_qc_tid = 0;
     pst_mac_header->bit_qc_eosp = 0;

     /* 设置seq的序列号 */
     pst_mac_header->bit_sc_seq_num = (dmac_btcoex_abort_qos_null_seq_num_get() + 1);

     dmac_btcoex_abort_qos_null_seq_num_set(pst_mac_header->bit_sc_seq_num);

     /*协议规定单播的QOS NULL DATA只允许normal ack 共存里面要设置0是对方会回ack */
     pst_mac_header->bit_qc_ack_polocy = WLAN_TX_NORMAL_ACK;

     OAM_INFO_LOG1(0, OAM_SF_COEX, "{(oal_uint32)pst_mac_header = 0x%x.}",(oal_uint32)pst_mac_header);

     dmac_btcoex_abort_null_buff_addr_set((oal_uint32)pst_mac_header);

     if(g_btcoex_soft_abort_switch)
     {
         OAM_INFO_LOG_ALTER(0, OAM_SF_COEX, "{bit_power_mgmt[0x%x], bit_protocol_version[0x%x], bit_to_ds[0x%x],
                    bit_type[0x%x],bit_sub_type[0x%x], bit_seq_num[%d],bit_duration_value[%d].}",
                    7,
                    pst_mac_header->st_frame_control.bit_power_mgmt,
                    pst_mac_header->st_frame_control.bit_protocol_version,
                    pst_mac_header->st_frame_control.bit_to_ds,
                    pst_mac_header->st_frame_control.bit_type,
                    pst_mac_header->st_frame_control.bit_sub_type,
                    pst_mac_header->bit_seq_num,
                    pst_mac_header->bit_duration_value);
         OAM_INFO_LOG4(0, OAM_SF_COEX, "{auc_address3 %02X:XX:XX:%02X:%02X:%02X.}",
            pst_mac_header->auc_address3[0],pst_mac_header->auc_address3[3],pst_mac_header->auc_address3[4],pst_mac_header->auc_address3[5]);
         OAM_INFO_LOG4(0, OAM_SF_COEX, "{auc_address2 %02X:XX:XX:%02X:%02X:%02X.}",
            pst_mac_header->auc_address2[0],pst_mac_header->auc_address2[3],pst_mac_header->auc_address2[4],pst_mac_header->auc_address2[5]);
         OAM_INFO_LOG4(0, OAM_SF_COEX, "{auc_address1 %02X:XX:XX:%02X:%02X:%02X.}",
            pst_mac_header->auc_address1[0],pst_mac_header->auc_address1[3],pst_mac_header->auc_address1[4],pst_mac_header->auc_address1[5]);
     }

    return OAL_SUCC;
}




oal_uint32  dmac_btcoex_abort_timeout(void *p_arg)
{
    hal_to_dmac_device_stru    *pst_device;
    oal_uint32                 uc_post_status = 0;
    oal_uint32                 uc_preempt_status;
    oal_uint32                uc_preempt_time_status;
    static oal_uint32         uc_count = 0;

    mac_device_stru     *pst_mac_device = (mac_device_stru *)p_arg;


#if 0
    /* 维测代码 统计查询preempt机制是否失败 */
    uc_preempt_time_status = dmac_btcoex_abort_preempt_time_out_get();
    uc_preempt_status = dmac_btcoex_abort_preempt_done_get();
    uc_post_status = dmac_btcoex_abort_post_preempt_done_get();
    if((BIT16 == uc_preempt_time_status) || (OAL_FALSE == uc_preempt_status) || (OAL_FALSE == uc_post_status))
    {
        OAM_WARNING_LOG3(0, OAM_SF_COEX, "{preempt(1 succ 0 fail)= %d preempt start failed = %d preempt post failed = %d",uc_preempt_time_status, uc_preempt_status,uc_post_status);
    }
#endif

    /* 发送preempt 帧 */
    dmac_btcoex_sw_all_abort_req_set(0x1);
    OAM_INFO_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_preempt_timeout uc_count = %d}",uc_count);

    FRW_TIMER_DESTROY_TIMER(&pst_mac_device->bt_coex_abort_timer);

    return OAL_SUCC;
}




oal_uint32 dmac_btcoex_preempt_timeout(void *p_arg)
{
    hal_to_dmac_device_stru    *pst_device;
    oal_uint32                 uc_post_status = 0;
    oal_uint32                 uc_preempt_status;
    oal_uint32                 uc_preempt_time_status;
    static oal_uint32          uc_count = 0;

    mac_device_stru     *pst_mac_device = (mac_device_stru *)p_arg;
#if 0

    /* 维测代码 统计查询preempt机制是否失败 */
    uc_preempt_time_status = dmac_btcoex_abort_preempt_time_out_get();
    uc_preempt_status = dmac_btcoex_abort_preempt_done_get();
    uc_post_status = dmac_btcoex_abort_post_preempt_done_get();
    if((BIT16 == uc_preempt_time_status) || (OAL_FALSE == uc_preempt_status) || (OAL_FALSE == uc_post_status))
    {
        OAM_WARNING_LOG3(0, OAM_SF_COEX, "{preempt(1 succ 0 fail)= %d preempt start failed = %d preempt post failed = %d",uc_preempt_time_status, uc_preempt_status,uc_post_status);
    }
#endif

    /* 发送post preempt 帧 */
    dmac_btcoex_sw_all_abort_req_set(0x0);
    OAM_INFO_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_post_preempt_timeout uc_count = %d}",uc_count);

    FRW_TIMER_DESTROY_TIMER(&pst_mac_device->bt_coex_preempt_timer);

    return OAL_SUCC;
}



oal_void  dmac_btcoex_set_null_params(oal_void)
{
    oal_uint32         ul_post_preempt_val = dmac_btcoex_post_preempt_timeout_val_get();
    oal_uint8          uc_btble_val        = dmac_btcoex_bt_ble_mode_get();
    oal_uint8          uc_bt_high_val      = dmac_btcoex_mode_select_get();
    oal_uint32         ul_bt_time_val      = dmac_btcoex_abort_timeout_val_get();
    oal_uint32         ul_ble_time_val     = dmac_blecoex_abort_timeout_val_get();
    oal_uint32         ul_null_phy_val     = dmac_btcoex_abort_null_phy_mode_get();
    oal_uint32         ul_null_rate_val    = dmac_btcoex_abort_null_data_rate_get();

    if(BT == uc_btble_val)
    {
        /* 暂且使用默认值，当需要更改时候更改参数 */
        dmac_btcoex_abort_timeout_val_set(ul_bt_time_val);
    }
    else if(BLE == uc_btble_val)
    {
        /* 暂且使用默认值，当需要更改时候更改参数 */
       dmac_blecoex_abort_timeout_val_set(ul_ble_time_val);
    }

    /* 暂且使用默认值，当需要更改时候更改参数 */
    dmac_btcoex_post_preempt_timeout_val_set(ul_post_preempt_val);

    /* 暂且使用默认值，当需要更改时候更改参数 */
    dmac_btcoex_abort_null_phy_mode_set(ul_null_phy_val);

    /* 暂且使用默认值，当需要更改时候更改参数 */
    dmac_btcoex_abort_null_data_rate_set(ul_null_rate_val);
}


oal_void  dmac_btcoex_set_cf_end_cts_params(oal_void)
{
    oal_uint8          uc_btble_val        = dmac_btcoex_bt_ble_mode_get();
    oal_uint8          uc_bt_high_val      = dmac_btcoex_mode_select_get();
    oal_uint32         ul_cf_phy_val       = dmac_btcoex_abort_cf_end_phy_mode_get();
    oal_uint32         ul_cf_daterate_val  = dmac_btcoex_abort_cf_end_data_rate_get();
    oal_uint32         ul_cts_duration_val = dmac_btcoex_abort_selfcts_duration_get();
    oal_uint32         ul_cts_phy_val      = dmac_btcoex_abort_selfcts_phy_mode_get();
    oal_uint32         ul_cts_date_val     = dmac_btcoex_abort_selfcts_data_rate_get();
    oal_uint32         ul_null_rate_val    = dmac_btcoex_abort_null_data_rate_get();
    oal_uint32         ul_bt_time_val      = dmac_btcoex_abort_timeout_val_get();
    oal_uint32         ul_ble_time_val     = dmac_blecoex_abort_timeout_val_get();

    if(BT == uc_btble_val)
    {
        /* 暂且使用默认值，当需要更改时候更改参数 */
        dmac_btcoex_abort_timeout_val_set(ul_bt_time_val);
    }
    else if(BLE == uc_btble_val)
    {
        /* 暂且使用默认值，当需要更改时候更改参数 */
        dmac_blecoex_abort_timeout_val_set(ul_ble_time_val);
    }

    /* 暂且使用默认值，当需要更改时候更改参数 */
    dmac_btcoex_abort_cf_end_phy_mode_set(ul_cf_phy_val);

    /* 暂且使用默认值，当需要更改时候更改参数 */
    dmac_btcoex_abort_cf_end_data_rate_set(ul_cf_daterate_val);

    /* 暂且使用默认值，当需要更改时候更改参数 */
    dmac_btcoex_abort_selfcts_duration_set(ul_cts_duration_val);

    /* 暂且使用默认值，当需要更改时候更改参数 */
    dmac_btcoex_abort_selfcts_phy_mode_set(ul_cts_phy_val);

    /* 暂且使用默认值，当需要更改时候更改参数 */
    dmac_btcoex_abort_selfcts_data_rate_set(ul_cts_date_val);


}




oal_uint32  dmac_btcoex_abort_start_event_handler(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru            *pst_event;
    frw_event_hdr_stru        *pst_event_hdr;
    dmac_vap_stru             *pst_dmac_vap;
    dmac_user_stru            *pst_dmac_user;
    oal_uint16                *pus_user_id;
    mac_device_stru           *pst_mac_device;

    OAM_INFO_LOG1(0, OAM_SF_ANY, "{dmac_btcoex_abort_start_event_handler= %d}",g_btcoex_abort_start_server++);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_abort_start_event_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 获取事件、事件头以及事件payload结构体 */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &pst_event->st_event_hdr;
    pst_mac_device = (mac_device_stru*)mac_res_get_dev(pst_event_hdr->uc_device_id);
    /* 获取vap结构信息 */
    pst_dmac_vap  = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_abort_start_event_handler::pst_dmac_vap null.}");
        return OAL_ERR_CODE_KEEPALIVE_PTR_NULL;
    }

    if(g_btcoex_soft_abort_switch)
    {
        /* 初始化寄存器读取定时器 */
        FRW_TIMER_CREATE_TIMER(&pst_mac_device->bt_coex_preempt_timer,
                   dmac_btcoex_preempt_timeout,
                   g_btcoex_abort_timeout_ms,
                   (oal_void *)pst_mac_device,
                   OAL_TRUE,
                   OAM_MODULE_ID_DMAC,pst_mac_device->ul_core_id);
    }


  //  dmac_btcoex_send_null_data(pst_dmac_vap, pst_dmac_user, OAL_TRUE);
    if(g_btcoex_null_one)
    {
#if 0
        if(NULLFRAME == dmac_btcoex_all_abort_preempt_type_get())
        {
            dmac_btcoex_init_null_data(g_frame_length,g_auc_ap_bssid,g_auc_sta_mac);
            OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_abort_start_event_handler::succ.}");
        }
        else if(OQSNULL == dmac_btcoex_all_abort_preempt_type_get())
        {
            OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_tx_qosnull_frame::succ.}");
            dmac_btcoex_send_qosnull_init();
        }
#endif
       // dmac_btcoex_init_null_data(g_frame_length,g_auc_ap_bssid,g_auc_sta_mac);
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_abort_start_event_handler::succ.}");
        dmac_btcoex_init_qosnull_data();
        g_btcoex_null_one = 0;
    }



    return  OAL_SUCC;
}



oal_uint32  dmac_btcoex_abort_end_event_handler(frw_event_mem_stru *pst_event_mem)
{

    frw_event_stru            *pst_event;
    frw_event_hdr_stru        *pst_event_hdr;
    dmac_vap_stru             *pst_dmac_vap;
    dmac_user_stru            *pst_dmac_user;
    mac_device_stru           *pst_mac_device;

    OAM_ERROR_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_abort_end_event_handler.g_btcoex_abort_end_server = %d}",g_btcoex_abort_end_server++);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_abort_end_event_handler::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 获取事件、事件头以及事件payload结构体 */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &pst_event->st_event_hdr;

    pst_mac_device = (mac_device_stru*)mac_res_get_dev(pst_event_hdr->uc_device_id);

    FRW_TIMER_DESTROY_TIMER(&pst_mac_device->bt_coex_abort_timer);
    /* 获取vap结构信息 */
    pst_dmac_vap  = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_abort_end_event_handler::pst_dmac_vap null.}");
        return OAL_ERR_CODE_KEEPALIVE_PTR_NULL;
    }

    if(g_btcoex_soft_abort_switch)
    {
        /* 初始化寄存器读取定时器 */
        FRW_TIMER_CREATE_TIMER(&pst_mac_device->bt_coex_abort_timer,
                                   dmac_btcoex_abort_timeout,
                                   g_btcoex_post_timeout_ms,
                                   (oal_void *)pst_mac_device,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,pst_mac_device->ul_core_id);
    }

    return  OAL_SUCC;
}


oal_uint32  dmac_btcoex_register_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type, oal_uint32 (*p_func)(frw_event_mem_stru *))
{
    if(en_event_type >= HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT || NULL == p_func)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "dmac_alg_register_dmac_misc_event fail");
        return  OAL_FAIL;
    }

    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = p_func;

    return OAL_SUCC;
}

oal_uint32  dmac_btcoex_unregister_dmac_misc_event(hal_dmac_misc_sub_type_enum en_event_type)
{
    if(en_event_type >= HAL_EVENT_DMAC_MISC_SUB_TYPE_BUTT)
    {
        OAM_ERROR_LOG0(0, OAM_SF_COEX, "dmac_alg_unregister_dmac_misc_event fail");
        return  OAL_FAIL;
    }

    g_ast_dmac_misc_event_sub_table[en_event_type].p_func = NULL;
    return OAL_SUCC;
}


oal_err_code_enum_uint32 dmac_btcoex_init(oal_void)
{
    oal_uint16 ul_wl_to_bt_time;
    oal_uint16 ul_bt_to_wl_time;

    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_ABROT_START_MISC, dmac_btcoex_abort_start_event_handler))
    {
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event fail!}");
        goto ABORT_START_INIT_FAIL_EVENT;
    }

    if (OAL_SUCC != dmac_btcoex_register_dmac_misc_event(HAL_EVENT_DMAC_ABROT_END_MISC, dmac_btcoex_abort_end_event_handler))
    {
        OAM_WARNING_LOG0(0, OAM_SF_COEX, "{dmac_btcoex_register_dmac_misc_event end fail!}");
        goto ABORT_END_INIT_FAIL_EVENT;
    }


    /* init coexit wifi bt NUll frame param */
    dmac_btcoex_set_null_params();

    dmac_btcoex_set_cf_end_cts_params();

    /* wifi 切 bt的切换时间 */
    ul_wl_to_bt_time = dmac_btcoex_soc_wifi_switch_bt_timeout_get();

    /* 默认是0xFFF 根据实际场景来调试 */
    dmac_btcoex_soc_wifi_switch_bt_timeout_set(ul_wl_to_bt_time);


    /* bt 切 wifi的切换时间 */
    ul_bt_to_wl_time = dmac_btcoex_soc_bt_switch_wifi_timeout_get();

    /* 默认是0xFFF 根据实际场景来调试 */
    dmac_btcoex_soc_bt_switch_wifi_timeout_set(ul_bt_to_wl_time);

    /* 测试代码，软件触发abort中断 */
    dmac_btcoex_sw_all_abort_ctrl_set(1);
    dmac_btcoex_sw_all_abort_mode_set(1);

    /* send null data need configuration frame head */
   // dmac_btcoex_all_abort_preempt_type_set(NULLFRAME);


    OAM_INFO_LOG0(0, OAM_SF_COEX, "{dmac_btcoex init succ.}");

    return OAL_SUCC;

    ABORT_END_INIT_FAIL_EVENT:
    dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_ABROT_START_MISC);

    ABORT_START_INIT_FAIL_EVENT:
    return OAL_FAIL;
}


oal_err_code_enum_uint32 dmac_btcoex_exit(oal_void)
{
    /* init coexit wifi bt param */
    oal_uint8 rev_value = OAL_SUCC;


    if (OAL_SUCC != dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_ABROT_START_MISC))
    {
        rev_value = OAL_FAIL;
    }
    if (OAL_SUCC != dmac_btcoex_unregister_dmac_misc_event(HAL_EVENT_DMAC_ABROT_END_MISC))
    {
        rev_value = OAL_FAIL;
    }

    OAM_INFO_LOG1(0, OAM_SF_COEX, "{btcoex_exit rev_value = %d !}",rev_value);

    return rev_value;
}


OAL_STATIC oal_bool_enum_uint8 dmac_btcoex_enable(oal_void)
{
    /* init coexit wifi bt param */
    return 0;
}


OAL_STATIC oal_bool_enum_uint8 dmac_btcoex_disable(oal_void)
{
    /* init coexit wifi bt param */
    return 0;
}

OAL_STATIC oal_void dmac_btcoex_sw_trigger_abort_verify(oal_void)
{
    /* 软件触发 BT共存AllAbort使能模式 */
    dmac_btcoex_sw_all_abort_req_set(0x1);
    dmac_btcoex_sw_all_abort_mode_set(0x1);

}


OAL_STATIC oal_void dmac_btcoex_abort_count_verify(oal_void)
{
    oal_uint32 ul_start_cnt,ul_done_cnt,ul_end_cnt;

    ul_start_cnt = dmac_btcoex_abort_start_cnt();
    ul_done_cnt  = dmac_btcoex_abort_done_cnt();
    ul_end_cnt  = dmac_btcoex_abort_done_cnt();

    OAM_INFO_LOG3(0, OAM_SF_COEX, "{ul_start_cnt = %d  ul_done_cnt = %d ul_end_cnt= %d!}",ul_start_cnt,ul_done_cnt,ul_end_cnt);
}



OAL_STATIC oal_void dmac_btcoex_abort_count_clear_verify(oal_void)
{
    dmac_btcoex_abort_start_cnt_clear();
    dmac_btcoex_abort_done_cnt_clear();
    dmac_btcoex_abort_end_cnt_clear();

    OAM_INFO_LOG0(0, OAM_SF_COEX, "{clear all abort cnt}");
}


OAL_STATIC oal_void dmac_btcoex_preempt_count_clear_verify(oal_void)
{
    dmac_btcoex_preempt_cnt_clear();
    dmac_btcoex_post_preempt_succ_cnt_clear();
    dmac_btcoex_post_preempt_fail_cnt_clear();

    OAM_INFO_LOG0(0, OAM_SF_COEX, "{clear all abort cnt}");
}



OAL_STATIC oal_void dmac_btcoex_preempt_cnt_verify(oal_void)
{
    oal_uint32 ul_preempt_cnt,ul_post_succ_cnt,ul_post_succ_fail;

    ul_preempt_cnt    = dmac_btcoex_preempt_cnt();
    ul_post_succ_cnt  = dmac_btcoex_post_preempt_succ_cnt();
    ul_post_succ_fail = dmac_btcoex_post_preempt_fail_cnt();

    OAM_INFO_LOG3(0, OAM_SF_COEX, "{ul_post_succ_fail = %d  ul_post_succ_cnt = %d ul_post_succ_fail= %d!}",ul_post_succ_fail,ul_post_succ_cnt,ul_post_succ_fail);
}
#endif
#endif /* end of _PRE_WLAN_FEATURE_LTECOEX */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

