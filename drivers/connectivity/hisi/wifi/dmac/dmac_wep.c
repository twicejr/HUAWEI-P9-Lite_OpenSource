


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
#include "hal_ext_if.h"
//#include "mac_11i.h"
#include "dmac_wep.h"
#include "dmac_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_WEP_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern oal_uint32 dmac_11i_update_key_to_ce(mac_vap_stru *pst_mac_vap, hal_security_key_stru *pst_security_key, oal_uint8 *puc_addr);


/*****************************************************************************
  3 函数实现
*****************************************************************************/

oal_void  dmac_wep_remove_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_id)
{
    hal_security_key_stru    st_wep_key         = {0};
    dmac_vap_stru           *pst_dmac_vap       = OAL_PTR_NULL;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WEP, "{dmac_wep_remove_key::pst_dmac_vap null.}");

        return;
    }

    st_wep_key.uc_key_id     = uc_key_id;
    st_wep_key.en_key_type   = WLAN_KEY_TYPE_TX_GTK;
    st_wep_key.uc_lut_idx    = pst_dmac_vap->pst_hal_vap->uc_vap_id;

    /* 写硬件寄存器   */
    hal_ce_del_key(pst_dmac_vap->pst_hal_device, &st_wep_key);


}


oal_uint32  dmac_config_wep_add_entry(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    hal_security_key_stru             st_wep_key         = {0};
    dmac_vap_stru                    *pst_dmac_vap       = OAL_PTR_NULL;
    mac_user_stru                    *pst_mac_user       = OAL_PTR_NULL;
    oal_uint8                        *puc_addr           = OAL_PTR_NULL;
    oal_uint32                        ul_ret;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_device_stru                    *pst_mac_device;
#endif

    puc_addr = puc_param;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WEP, "{dmac_config_wep_add_entry::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user =  (mac_user_stru *)mac_vap_get_user_by_addr(pst_mac_vap, puc_addr);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WEP, "{dmac_config_wep_add_entry::mac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 设置用户的发送加密套件*/
    ul_ret = mac_user_update_wep_key(pst_mac_user, pst_mac_vap->us_multi_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WEP, "{dmac_config_wep_add_entry::mac_wep_add_usr_key FAIL[%d].}", ul_ret);
        return OAL_ERR_CODE_PTR_NULL;
    }

    st_wep_key.uc_key_id       = pst_mac_user->st_key_info.uc_default_index;
    st_wep_key.en_cipher_type  = pst_mac_user->st_key_info.en_cipher_type;
    st_wep_key.en_key_type     = WLAN_KEY_TYPE_PTK;
    st_wep_key.uc_lut_idx      = ((dmac_user_stru *)pst_mac_user)->uc_lut_index;
    st_wep_key.en_update_key   = OAL_TRUE;
    st_wep_key.en_key_origin   = WLAN_AUTH_KEY;

    /*密钥已经添加过，不需要重复添加，只需要激活用户即可*/
    st_wep_key.puc_cipher_key  = pst_mac_user->st_key_info.ast_key[st_wep_key.uc_key_id].auc_key;
    st_wep_key.puc_mic_key     = OAL_PTR_NULL;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{dmac_config_wep_add_entry::mac_res_get_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) && (OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* 写硬件寄存器 */
            /* 对于proxysta来讲，peer_macaddr需要配置为自身mac地址，创建时已经配置过 */
            hal_ce_add_key(pst_dmac_vap->pst_hal_device, &st_wep_key, OAL_PTR_NULL);
        }
        else
        {
            /* 写硬件寄存器 */
            hal_ce_add_key(pst_dmac_vap->pst_hal_device, &st_wep_key, puc_addr);
        }
    }
    else
    {
        /* 写硬件寄存器   */
        hal_ce_add_key(pst_dmac_vap->pst_hal_device, &st_wep_key, puc_addr);
    }
#else
    /* 写硬件寄存器   */
    hal_ce_add_key(pst_dmac_vap->pst_hal_device, &st_wep_key, puc_addr);
#endif

    return OAL_SUCC;
}


oal_uint32  dmac_config_wep_remove_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint8                  uc_key_id;
    mac_removekey_param_stru  *puc_wep_key_prarm;

    puc_wep_key_prarm = (mac_removekey_param_stru *)puc_param;
    uc_key_id = puc_wep_key_prarm->uc_key_index;

	/*初始化wep相关MIB信息*/
    mac_mib_set_wep(pst_mac_vap, uc_key_id);

    /*从硬件Lut表删除 wep key */
    if(IS_STA(pst_mac_vap))
    {
        dmac_wep_remove_key(pst_mac_vap,uc_key_id);
    }

    return OAL_SUCC;

}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

