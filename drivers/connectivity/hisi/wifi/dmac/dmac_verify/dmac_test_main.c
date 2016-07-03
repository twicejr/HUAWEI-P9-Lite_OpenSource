


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "dmac_ext_if.h"
#include "oam_ext_if.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_test_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TEST_MAIN_C

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define DMAC_TEST_OFFSET(type, member) ((long) &((type *) 0)->member)

dmac_test_mng_stru  g_st_dmac_test_mng;

/*****************************************************************************
  3 函数实现
*****************************************************************************/

oal_void  dmac_test_init(oal_void)
{
    OAL_MEMZERO(&g_st_dmac_test_mng, OAL_SIZEOF(dmac_test_mng_stru));

    dmac_test_encap_init(g_st_dmac_test_mng.ast_dmac_encap_frame);

    dmac_test_lpm_wow_init();
}


dmac_test_encap_frame *dmac_test_get_encap_frame(oal_void)
{
    return g_st_dmac_test_mng.ast_dmac_encap_frame;
}


oal_void dmac_test_set_software_retry(oal_uint8 * puc_param)
{
    mac_cfg_set_soft_retry_stru *puc_soft_retry = (mac_cfg_set_soft_retry_stru *)puc_param;
    g_st_dmac_test_mng.uc_software_retry = puc_soft_retry->uc_software_retry;
    g_st_dmac_test_mng.uc_retry_test = puc_soft_retry->uc_retry_test;
}



oal_void dmac_test_set_dscr_software_retry(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr)
{
    if (0 == g_st_dmac_test_mng.uc_retry_test)
    {
        return;
    }
    hal_tx_set_dscr_seqno_sw_generate(pst_hal_device, pst_tx_dscr, g_st_dmac_test_mng.uc_software_retry);
}



oal_void dmac_test_open_addr4(oal_uint8 *puc_add4_open)
{
    g_st_dmac_test_mng.uc_add4_open = *puc_add4_open;
    return;
}


oal_void dmac_test_get_addr4(oal_uint8 *puc_add4_open)
{
    *puc_add4_open = g_st_dmac_test_mng.uc_add4_open ;
    return;
}


oal_void dmac_test_set_addr4(hal_tx_dscr_stru * pst_tx_dscr)
{
    mac_ieee80211_qos_frame_addr4_stru          st_qos_addr4;
    mac_ieee80211_qos_frame_stru               *pst_qos = NULL;
    oal_uint8                                  *pst_cb = NULL;
    mac_tx_ctl_stru                            *pst_tx_ctrl = NULL;
    oal_uint32                                  ul_len;
    oal_uint32                                  ul_left_len;
    if(0 == g_st_dmac_test_mng.uc_add4_open)
    {
       return;
    }

    pst_cb = OAL_NETBUF_CB(pst_tx_dscr->pst_skb_start_addr);
    pst_tx_ctrl = (mac_tx_ctl_stru *)pst_cb;
    pst_qos = (mac_ieee80211_qos_frame_stru *)mac_get_cb_frame_hdr(pst_tx_ctrl);

    oal_memset(&st_qos_addr4, 0, sizeof(mac_ieee80211_qos_frame_addr4_stru));
    /*lint -e413*/
    ul_len = DMAC_TEST_OFFSET(mac_ieee80211_qos_frame_addr4_stru, auc_address4);
    /*lint +e413*/
    ul_left_len = OAL_SIZEOF(mac_ieee80211_qos_frame_stru) - ul_len;
    /* 复制addr4前的字段 */
    oal_memcopy(&st_qos_addr4, pst_qos, ul_len);
    /* 设置addr4字段 */
    oal_memcopy(st_qos_addr4.auc_address4, pst_qos->auc_address3, OAL_MAC_ADDR_LEN);
    /* 复制addr4后的字段 */
    oal_memcopy((oal_uint8 *)&st_qos_addr4 + WLAN_MAC_ADDR_LEN + ul_len, (oal_uint8 *)pst_qos + ul_len, ul_left_len);

    /* 设置TO DS和FROM DS */
    st_qos_addr4.st_frame_control.bit_from_ds = 1;
    st_qos_addr4.st_frame_control.bit_to_ds = 1;
    /* 设置描述符，帧头长度为4地址长度  */
    oal_memcopy(mac_get_cb_frame_hdr(pst_tx_ctrl), &st_qos_addr4, OAL_SIZEOF(mac_ieee80211_qos_frame_addr4_stru));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl) = MAC_80211_QOS_4ADDR_FRAME_LEN;
    return;
}


oal_void dmac_test_set_chip_test(oal_uint8 uc_chip_test_open)
{
    g_st_dmac_test_mng.uc_chip_test_open = uc_chip_test_open;
    return;
}


oal_uint32 dmac_test_get_chip_test(oal_void)
{
    return g_st_dmac_test_mng.uc_chip_test_open;
}


oal_uint32 dmac_test_check_chip_test(oal_uint8 uc_value)
{
    DMAC_CHIP_TEST_CALL(dmac_test_set_chip_test(uc_value));
    return 0;
}

/*lint -e19*/
oal_module_symbol(g_st_dmac_test_mng);
oal_module_symbol(dmac_test_get_chip_test);
/*lint +e19*/

#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

