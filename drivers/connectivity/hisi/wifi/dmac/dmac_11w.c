


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_spec.h"
#include "wlan_types.h"
#include "wlan_mib.h"
#include "mac_user.h"
#include "mac_resource.h"
#include "mac_frame.h"
#include "dmac_main.h"
#include "dmac_vap.h"
#include "dmac_ext_if.h"
#include "dmac_11i.h"
#include "dmac_11w.h"
#include "hal_ext_if.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_11W_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)


OAL_STATIC oal_bool_enum_uint8  dmac_11w_robust_action(oal_netbuf_stru *pst_mgmt_buf)
{
    oal_uint8   uc_frame_type;
    oal_uint8  *puc_mac_header  = oal_netbuf_header(pst_mgmt_buf);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8  *puc_mac_payload = oal_netbuf_data(pst_mgmt_buf);
#else
    oal_uint8  *puc_mac_payload = puc_mac_header + MAC_80211_FRAME_LEN;
#endif

    uc_frame_type = mac_frame_get_subtype_value(puc_mac_header);
    if (WLAN_ACTION != uc_frame_type)
    {
        return OAL_FALSE;
    }

    switch (puc_mac_payload[MAC_ACTION_OFFSET_CATEGORY])
    {
        case MAC_ACTION_CATEGORY_SPECMGMT:
        case MAC_ACTION_CATEGORY_QOS:
        case MAC_ACTION_CATEGORY_DLS:
        case MAC_ACTION_CATEGORY_BA:
        case MAC_ACTION_CATEGORY_RADIO_MEASURMENT:
        case MAC_ACTION_CATEGORY_FAST_BSS_TRANSITION:
        case MAC_ACTION_CATEGORY_HT:
        case MAC_ACTION_CATEGORY_SA_QUERY:
        case MAC_ACTION_CATEGORY_PROTECTED_DUAL_OF_ACTION:
        case MAC_ACTION_CATEGORY_WNM:
        case MAC_ACTION_CATEGORY_MESH:
        case MAC_ACTION_CATEGORY_MULTIHOP:
        case MAC_ACTION_CATEGORY_VENDOR_SPECIFIC_PROTECTED:
        {
            return OAL_TRUE;
        }

        default:
            break;
    }

    return OAL_FALSE;
}


OAL_STATIC oal_bool_enum_uint8  dmac_11w_robust_non_action(oal_uint8 uc_frame_type, oal_uint8 *puc_payload)
{
    mac_reason_code_enum_uint16 en_reason_code = 0;
    oal_uint16                  us_reason_code = 0;
    us_reason_code = puc_payload[1];
    us_reason_code = (oal_uint16)((us_reason_code << 8) + puc_payload[0]);
    en_reason_code = (mac_reason_code_enum_uint16)us_reason_code;
    switch (uc_frame_type)
    {
        case WLAN_DISASOC:
        case WLAN_DEAUTH:
        {
            //OAM_INFO_LOG1(0, OAM_SF_PMF, "dmac_11w_robust_non_action:: deauth/disassoc reason code:[%d]", en_reason_code);
            /* 两种特殊情况不用加密 */
            if (MAC_NOT_AUTHED == en_reason_code || MAC_NOT_ASSOCED == en_reason_code)
            {
                return OAL_FALSE;
            }
            return OAL_TRUE;
        }

        default:
            break;
    }

    return OAL_FALSE;
}


OAL_STATIC oal_bool_enum_uint8  dmac_11w_robust_frame(oal_netbuf_stru *pst_mgmt_frame)
{
    oal_uint8   uc_frame_type;
    oal_uint8  *puc_mac_header;
    oal_uint8  *puc_payload;
    puc_mac_header = oal_netbuf_header(pst_mgmt_frame);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    puc_payload = oal_netbuf_data(pst_mgmt_frame);
#else
    puc_payload = puc_mac_header + MAC_80211_FRAME_LEN;
#endif

    /*非管理帧*/
    uc_frame_type  = mac_frame_get_type_value(puc_mac_header);
    if (WLAN_MANAGEMENT != uc_frame_type)
    {
        return OAL_FALSE;
    }

    uc_frame_type = mac_frame_get_subtype_value(puc_mac_header);
    if ((OAL_TRUE == dmac_11w_robust_action(pst_mgmt_frame))||
        (OAL_TRUE == dmac_11w_robust_non_action(uc_frame_type, puc_payload)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}


oal_uint32 dmac_11w_get_pmf_cap(mac_vap_stru *pst_mac_vap, wlan_pmf_cap_status_uint8 *pen_pmf_cap)
{
    oal_bool_enum_uint8 en_MFPC;
    oal_bool_enum_uint8 en_MFPR;

    *pen_pmf_cap = MAC_PMF_DISABLED;
    en_MFPC = pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC;
    en_MFPR = pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR;

    /* 判断vap的PMF能力 */
    if ((OAL_FALSE == en_MFPC) && (OAL_TRUE == en_MFPR))
    {
         OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PMF, "{dmac_11w_get_pmf_cap::invalid en_MFPR.}");
         return OAL_ERR_CODE_PMF_VAP_CAP_FAIL;
    }

    if ((OAL_FALSE == en_MFPC) && (OAL_FALSE == en_MFPR))
    {
        *pen_pmf_cap = MAC_PMF_DISABLED;
        return OAL_SUCC;
    }

    if ((OAL_TRUE == en_MFPC) && (OAL_FALSE == en_MFPR))
    {
        *pen_pmf_cap = MAC_PMF_ENABLED;
        return OAL_SUCC;
    }

    *pen_pmf_cap = MAC_PME_REQUIRED;

    return OAL_SUCC;
}


OAL_STATIC oal_bool_enum_uint8 dmac_11w_check_multicast_mgmt(oal_netbuf_stru *pst_mgmt_buf)
{
    oal_uint8                 *puc_da;
    mac_ieee80211_frame_stru  *pst_frame_hdr;
    pst_frame_hdr = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_mgmt_buf);
    puc_da        = pst_frame_hdr->auc_address1;

    if (OAL_TRUE != ETHER_IS_MULTICAST(puc_da))
    {
       return OAL_FALSE;
    }

    return dmac_11w_robust_frame(pst_mgmt_buf);
}


OAL_STATIC oal_bool_enum_uint8 dmac_11w_check_vap_pmf_cap(dmac_vap_stru *pst_dmac_vap, wlan_pmf_cap_status_uint8  en_pmf_cap)
{
    mac_user_stru               *pst_multi_user;

    pst_multi_user = mac_res_get_mac_user(pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_PTR_NULL;
    }

    /* 具备pmf管理帧加密的前提条件:
       1) mib项打开:RSN Active mib
       2) 能力支持 :user 支持pmf
       3) igtk存在 :用于广播Robust mgmt加密
     */
    if ((OAL_TRUE == mac_mib_get_dot11RSNAActivated(&pst_dmac_vap->st_vap_base_info)) &&
        ( MAC_PMF_DISABLED != en_pmf_cap) &&
        (OAL_SUCC == dmac_check_igtk_exist(pst_multi_user->st_key_info.uc_igtk_key_index)))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}


oal_void dmac_11w_set_protectframe(dmac_vap_stru  *pst_dmac_vap,
                                             wlan_security_txop_params_stru  *pst_security,
                                             oal_netbuf_stru *pst_netbuf)
{
    oal_bool_enum_uint8 en_MFPC       = OAL_FALSE;
    oal_bool_enum_uint8 en_pmf_active = OAL_FALSE;
	oal_uint8           auc_addr1[6]  = {0};
	dmac_user_stru     *pst_dmac_user = OAL_PTR_NULL;
	oal_uint16          us_user_idx;
	oal_uint8          *puc_frame_hdr = oal_netbuf_header(pst_netbuf);

    mac_get_address1(puc_frame_hdr, auc_addr1);

    /* 查找用户:auth帧情况下不会有用户，找不到用户属于正常情况 */
    if (OAL_SUCC != mac_vap_find_user_by_macaddr(&pst_dmac_vap->st_vap_base_info, auc_addr1, &us_user_idx))
    {
        return;
    }
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        return;
    }

    /* 能力检查 */
    en_MFPC = mac_mib_get_dot11RSNAMFPC(&(pst_dmac_vap->st_vap_base_info));
    en_pmf_active = pst_dmac_user->st_user_base_info.st_cap_info.bit_pmf_active;
    if ((OAL_FALSE == en_MFPC) || (OAL_FALSE == en_pmf_active) ||
        (OAL_TRUE == ETHER_IS_MULTICAST(auc_addr1)))
    {
        return;
    }
    if (OAL_TRUE == dmac_11w_robust_frame(pst_netbuf))
    {
        mac_set_protectedframe(puc_frame_hdr);
        pst_security->en_cipher_key_type      = pst_dmac_user->st_user_base_info.st_user_tx_info.st_security.en_cipher_key_type;
        pst_security->en_cipher_protocol_type = pst_dmac_user->st_user_base_info.st_user_tx_info.st_security.en_cipher_protocol_type;

        return;
    }

}


oal_uint32 dmac_bip_crypto(dmac_vap_stru *pst_dmac_vap,
                                 oal_netbuf_stru *pst_netbuf_mgmt,
                                 wlan_security_txop_params_stru  *pst_security,
                                 oal_uint16 *pus_len)
{
#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_SW_BIP)

    wlan_priv_key_param_stru    *pst_pmf_igtk;
#endif
    mac_user_stru               *pst_multi_user;
    oal_uint8                    uc_pmf_igtk_keyid;
    oal_uint32                   ul_relt;
    wlan_pmf_cap_status_uint8    en_pmf_cap;

    /* 判断vap的pmf能力 */
    ul_relt = dmac_11w_get_pmf_cap(&pst_dmac_vap->st_vap_base_info,&en_pmf_cap);
    if (OAL_SUCC != ul_relt)
    {
         return OAL_ERR_CODE_PMF_VAP_CAP_FAIL;
    }

    pst_multi_user = mac_res_get_mac_user(pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_PTR_NULL;
    }

    /* 判断是否需要加密的组播/广播 强健管理帧 */
    if ((OAL_TRUE == dmac_11w_check_multicast_mgmt(pst_netbuf_mgmt)) &&
        (OAL_TRUE == dmac_11w_check_vap_pmf_cap(pst_dmac_vap,en_pmf_cap)))
    {
        uc_pmf_igtk_keyid = pst_multi_user->st_key_info.uc_igtk_key_index;
        oal_netbuf_set_len(pst_netbuf_mgmt, *pus_len);

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)

        pst_security->en_cipher_protocol_type = WLAN_80211_CIPHER_SUITE_BIP;
        pst_security->uc_cipher_key_id        = uc_pmf_igtk_keyid;
#else
        pst_pmf_igtk      = &pst_multi_user->st_key_info.ast_key[uc_pmf_igtk_keyid];
        pst_security->en_cipher_protocol_type = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
        /* 11w组播管理帧加密 */
        ul_relt = oal_crypto_bip_enmic(uc_pmf_igtk_keyid,
                                       pst_pmf_igtk->auc_key,
                                       pst_pmf_igtk->auc_seq,
                                       pst_netbuf_mgmt,
                                       pus_len);
        if(OAL_SUCC != ul_relt)
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PMF, "{dmac_bip_crypto::oal_crypto_bip_enmic failed[%d].}", ul_relt);
            return OAL_ERR_CODE_PMF_BIP_CRIPTO_FAIL;
        }
#endif

     }

    return OAL_SUCC;
}

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_SW_BIP)


OAL_STATIC oal_uint32 dmac_bip_decrypto(dmac_vap_stru  *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
   wlan_priv_key_param_stru          *pst_pmf_igtk;
   mac_user_stru                     *pst_multi_user;
   oal_uint8                          uc_pmf_igtk_keyid = 0xff;
   wlan_mib_Dot11RSNAStatsEntry_stru *pst_mib_rsna_status;
   dmac_rx_ctl_stru                  *pst_rx_ctl;
   oal_uint32                         ul_relt;
   wlan_pmf_cap_status_uint8          en_pmf_cap;

   if (OAL_TRUE != dmac_11w_check_multicast_mgmt(pst_netbuf))
   {
       return OAL_SUCC;
   }

   /* 获取帧头信息 */
   pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);


   /* 获取包含 重放 & CMAC解密失败 的统计mib指针 */
   pst_mib_rsna_status = (pst_dmac_vap->st_vap_base_info.pst_mib_info->ast_wlan_mib_rsna_status) + (pst_rx_ctl->st_rx_info.us_ta_user_idx);


   /* 判断vap的pmf能力 */
   ul_relt = dmac_11w_get_pmf_cap(&pst_dmac_vap->st_vap_base_info,&en_pmf_cap);
   if (OAL_SUCC != ul_relt)
   {
        return OAL_FAIL;
   }

   pst_multi_user = mac_res_get_mac_user(pst_dmac_vap->st_vap_base_info.us_multi_user_idx);
   if (OAL_PTR_NULL == pst_multi_user)
   {
       return OAL_PTR_NULL;
   }

   /* 强健组播管理帧解密 */
   if ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode) &&
       (OAL_TRUE == dmac_11w_check_vap_pmf_cap(pst_dmac_vap,en_pmf_cap)))
    {
        /* 获取igtk信息 */
        uc_pmf_igtk_keyid = pst_multi_user->st_key_info.uc_igtk_key_index;
        pst_pmf_igtk      = &(pst_multi_user->st_key_info.ast_key[uc_pmf_igtk_keyid]);
        /* 管理帧解密 */
        ul_relt = oal_crypto_bip_demic(uc_pmf_igtk_keyid,
                                       pst_pmf_igtk->auc_key,
                                       pst_pmf_igtk->auc_seq,
                                       pst_netbuf,
                                      &pst_mib_rsna_status->ul_dot11RSNAStatsCMACReplays,
                                      &pst_mib_rsna_status->ul_dot11RSNAStatsCMACICVErrors);
        if(OAL_SUCC != ul_relt)
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PMF, "{dmac_bip_decrypto::oal_crypto_bip_demic failed[%d].}", ul_relt);
            return OAL_ERR_CODE_PMF_BIP_DECRIPTO_FAIL;
        }
    }

   return OAL_SUCC;
}
#endif /* (_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_SW_BIP) */


oal_void dmac_11w_update_users_status(dmac_vap_stru  *pst_dmac_vap, mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_user_pmf)
{
#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)

    wlan_pmf_cap_status_uint8  en_pmf_cap;
    oal_uint32                 ul_user_pmf_old = 0;
    oal_uint32                 ul_flag = BIT0;
#endif

    mac_user_set_pmf_active(pst_mac_user, en_user_pmf);

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)

    ul_user_pmf_old = pst_dmac_vap->ul_user_pmf_status;
    if (OAL_FALSE == pst_mac_user->st_cap_info.bit_pmf_active)
    {
        pst_dmac_vap->ul_user_pmf_status &= (oal_uint32)(~(ul_flag << (pst_mac_user->us_assoc_id)));
    }
    else
    {
        pst_dmac_vap->ul_user_pmf_status |= ul_flag << (pst_mac_user->us_assoc_id);
    }

    /* 如果没有改变 */
    if (ul_user_pmf_old == pst_dmac_vap->ul_user_pmf_status)
    {
        return;
    }

    /* 硬件PMF控制开关填写 */
    dmac_11w_get_pmf_cap(&pst_dmac_vap->st_vap_base_info, &en_pmf_cap);
    if (MAC_PMF_DISABLED != en_pmf_cap)
    {
        hal_set_pmf_crypto(pst_dmac_vap->pst_hal_vap, (oal_bool_enum_uint8)IS_OPEN_PMF_REG(pst_dmac_vap));
    }
#endif
}


oal_uint32 dmac_11w_rx_filter(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru  *pst_netbuf)
{
    oal_uint32                           ul_relt = OAL_SUCC;
    oal_uint8                           *puc_da;
    dmac_rx_ctl_stru                    *pst_rx_ctl;
    mac_ieee80211_frame_stru            *pst_frame_hdr;
    mac_user_stru                       *pst_user;
    oal_uint16                           us_ta_user_idx;
    wlan_ciper_protocol_type_enum_uint8  en_cipher_protocol_type;

    pst_frame_hdr = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_netbuf);
    puc_da        = pst_frame_hdr->auc_address1;
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    en_cipher_protocol_type = hal_ctype_to_cipher_suite(pst_rx_ctl->st_rx_status.bit_cipher_protocol_type);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    us_ta_user_idx  = pst_rx_ctl->st_rx_info.bit_ta_user_idx;
#else
    us_ta_user_idx  = pst_rx_ctl->st_rx_info.us_ta_user_idx;
#endif

    pst_user = (mac_user_stru *)mac_res_get_dmac_user(us_ta_user_idx);
    if (OAL_PTR_NULL == pst_user)
    {
        return OAL_SUCC;
    }

    if ((OAL_TRUE != pst_user->st_cap_info.bit_pmf_active) ||
        (OAL_TRUE != dmac_11w_robust_frame(pst_netbuf) ))
    {
       return OAL_SUCC;
    }

    /* 广播Robust帧过滤 */
    if (OAL_TRUE == ETHER_IS_MULTICAST(puc_da))
    {
        ul_relt = OAL_SUCC;

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)

        if (WLAN_80211_CIPHER_SUITE_BIP !=  en_cipher_protocol_type)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PMF,
                "{dmac_11w_rx_filter::PMF is open,but is Robust muti frame chipertype is[%d].}", en_cipher_protocol_type);
            return OAL_ERR_CODE_PMF_NO_PROTECTED_ERROR;
        }
#else
        /* 11w组播管理帧解密 */
        ul_relt = dmac_bip_decrypto(pst_dmac_vap, pst_netbuf);
        if (OAL_SUCC != ul_relt)
        {
            /* 组播解密失败，不上报管理帧 */
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PMF,
                           "{dmac_11w_rx_filter::dmac_bip_decrypto failed[%d].}", ul_relt);
        }
#endif
        return ul_relt;
    }

    /* pmf使能，对硬件不能过滤的未加密帧进行过滤 */
    if (WLAN_80211_CIPHER_SUITE_NO_ENCRYP ==  en_cipher_protocol_type)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PMF,
                  "{dmac_11w_rx_filter::PMF is open,but the Robust frame is CIPHER_SUITE_NO_ENCRYP.}");
        return OAL_ERR_CODE_PMF_NO_PROTECTED_ERROR;
    }

    /* PMF单播管理帧校验 */
    if ((OAL_FALSE == pst_frame_hdr->st_frame_control.bit_protected_frame)||
        (WLAN_80211_CIPHER_SUITE_CCMP !=  en_cipher_protocol_type))
    {
        OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PMF,
                      "{dmac_11w_rx_filter::robust_action protecter incorect. bit_protected_frame[%d], cipher_type[%d].}",
                      pst_frame_hdr->st_frame_control.bit_protected_frame,
                      en_cipher_protocol_type);
        return OAL_ERR_CODE_PMF_NO_PROTECTED_ERROR;
    }

    return OAL_SUCC;
}

#endif /* (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

