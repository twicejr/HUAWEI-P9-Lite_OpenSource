/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_11i.c
  版 本 号   : 初稿
  作    者   : louyueyun
  生成日期   : 2013年8月15日
  最近修改   :
  功能描述   : 11i DMAC功能处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月15日
    作    者   : louyueyun
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
#include "oal_list.h"
#include "oal_net.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_resource.h"
#include "wlan_types.h"
#include "mac_vap.h"
#include "mac_user.h"
//#include "mac_11i.h"
#include "dmac_main.h"
#include "oal_net.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_mgmt_ap.h"
#include "dmac_11i.h"
#include "dmac_wep.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_11I_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define MAC_ADDR(_puc_mac)   ((oal_uint32)(((oal_uint32)_puc_mac[2] << 24) |\
                                                  ((oal_uint32)_puc_mac[3] << 16) |\
                                                  ((oal_uint32)_puc_mac[4] << 8) |\
                                                  ((oal_uint32)_puc_mac[5])))

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_check_igtk_exist
 功能描述  : 通过igtk index检查igtk是否存在
 输入参数  : uc_igtk_index : igtk的index值
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :
            <由于Hi1102 Device内存有限，暂时删除aes.c/h,oam_config.c/h文件，所以此函数搬移到此处。
            原型为oal_check_igtk_exist>
 修改历史      :
  1.日    期   : 2014年5月3日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_check_igtk_exist(oal_uint8 uc_igtk_index)
{
    /* igtk的key index 为4或5 */
    if ((WLAN_MAX_IGTK_KEY_INDEX < uc_igtk_index) ||
        ((WLAN_MAX_IGTK_KEY_INDEX - WLAN_NUM_IGTK) >= uc_igtk_index))
    {
        return OAL_ERR_CODE_PMF_IGTK_NOT_EXIST;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_update_key_to_ce
 功能描述  : 调用增加密钥写寄存器接口，将一个密钥写入硬件Lut表
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_11i_update_key_to_ce(mac_vap_stru *pst_mac_vap, hal_security_key_stru *pst_key, oal_uint8 *puc_addr)
{
    dmac_vap_stru           *pst_dmac_vap;

    /*2.1 获取dmac_vap*/
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_key))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    /* 重要信息打印warning */
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_update_key_to_ce::keyid=%u, keytype=%u,lutidx=%u,cipher=%u}",
                     pst_key->uc_key_id, pst_key->en_key_type, pst_key->uc_lut_idx, pst_key->en_cipher_type);
    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_update_key_to_ce::en_update_key=%u, en_key_origin=%u}",
                     pst_key->en_update_key, pst_key->en_key_origin);

    /* 3.1 写硬件寄存器   */
    hal_ce_add_key(pst_dmac_vap->pst_hal_device, pst_key, puc_addr);

#ifdef _PRE_WLAN_INIT_PTK_TX_PN
    /* 3.2 初始化TX PN */
    hal_init_ptk_tx_pn(pst_dmac_vap->pst_hal_device, pst_key);
    dmac_init_iv_word_lut(pst_dmac_vap->pst_hal_device, pst_key);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_del_key_to_ce
 功能描述  : 将一个密钥从硬件LUT表中删除
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月8日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_11i_del_key_to_ce(mac_vap_stru                   *pst_mac_vap,
                                            oal_uint8                       uc_key_id,
                                            hal_cipher_key_type_enum_uint8  en_key_type,
                                            oal_uint8                       uc_lut_index)
{
    hal_security_key_stru    st_security_key    = {0};
    dmac_vap_stru           *pst_dmac_vap       = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    st_security_key.uc_key_id      = uc_key_id;
    st_security_key.en_key_type    = en_key_type;
    st_security_key.uc_lut_idx     = uc_lut_index;
    st_security_key.en_update_key  = OAL_TRUE;
    st_security_key.puc_cipher_key = OAL_PTR_NULL;
    st_security_key.puc_mic_key    = OAL_PTR_NULL;

    /* 重要信息打印warning */
    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                     "{dmac_11i_del_key_to_ce::keyid=%u, keytype=%u,lutidx=%u}", uc_key_id, en_key_type, uc_lut_index);

    /* 写硬件寄存器   */
    hal_ce_del_key(pst_dmac_vap->pst_hal_device, &st_security_key);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_11i_get_auth_type
 功能描述  : 根据vap，获取认证类型
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC hal_key_origin_enum_uint8 dmac_11i_get_auth_type(mac_vap_stru *pst_mac_vap)
{
    if (IS_AP(pst_mac_vap))
    {
        return HAL_AUTH_KEY;
    }
    return HAL_SUPP_KEY;
}
/*****************************************************************************
 函 数 名  : dmac_11i_get_key_type
 功能描述  : 根据vap，获取密钥类型
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC hal_cipher_key_type_enum_uint8 dmac_11i_get_gtk_key_type(mac_vap_stru *pst_mac_vap, wlan_ciper_protocol_type_enum_uint8 en_cipher_type)
{
    oal_uint8           uc_rx_gtk        = HAL_KEY_TYPE_RX_GTK;
#if (_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)
    mac_user_stru      *pst_multi_user   = OAL_PTR_NULL;
#endif
    if (IS_AP(pst_mac_vap) && (WLAN_80211_CIPHER_SUITE_BIP != en_cipher_type))
    {
#if (_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)
        /* 1102 组播管理帧密钥的key type发送改变 */
        return HAL_KEY_TYPE_RX_GTK;
#else
        return HAL_KEY_TYPE_TX_GTK;
#endif
    }

#if (_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)

    pst_multi_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_get_gtk_key_type::mac_res_get_mac_user null.}");
        return HAL_KEY_TYPE_TX_GTK;
    }

    if (WLAN_80211_CIPHER_SUITE_BIP == en_cipher_type)
    {
        /* Hi1102: HAL_KEY_TYPE_IGTK */
        uc_rx_gtk = HAL_KEY_TYPE_TX_GTK;
    }
    else if (0 == pst_multi_user->st_key_info.bit_gtk)
    {
        uc_rx_gtk = HAL_KEY_TYPE_RX_GTK;
        //pst_mac_vap->st_key_mgmt.bit_gtk = 1;
    }
    else
    {
        uc_rx_gtk = HAL_KEY_TYPE_RX_GTK2;
        //pst_mac_vap->st_key_mgmt.bit_gtk = 0;
    }
#endif
    return uc_rx_gtk;
}

/*****************************************************************************
 函 数 名  : dmac_reset_gtk_token
 功能描述  : 复位gtk乒乓位
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_reset_gtk_token(mac_vap_stru *pst_mac_vap)
{
    mac_user_stru  *pst_multi_user          = OAL_PTR_NULL;

    pst_multi_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_add_gtk_key::mac_res_get_mac_user[%d] null.}", pst_mac_vap->us_multi_user_idx);
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }
    pst_multi_user->st_key_info.bit_gtk = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_del_peer_macaddr
 功能描述  : 将一个密钥从硬件LUT表中删除
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : louyueyun 218984
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_11i_del_peer_macaddr(mac_vap_stru *pst_mac_vap, oal_uint8 uc_lut_index)
{
    dmac_vap_stru           *pst_dmac_vap       = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    /* 写硬件寄存器   */
    hal_ce_del_peer_macaddr(pst_dmac_vap->pst_hal_device, uc_lut_index);
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_add_ptk_key
 功能描述  : 设置单播密钥
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
 oal_uint32  dmac_11i_add_ptk_key(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint8 uc_key_index)
{
    oal_uint32                          ul_ret;
    dmac_user_stru                     *pst_current_dmac_user                  = OAL_PTR_NULL;
    mac_user_stru                      *pst_current_mac_user                   = OAL_PTR_NULL;
    wlan_priv_key_param_stru           *pst_key                                = OAL_PTR_NULL;
    oal_uint8                           auc_mic_key[WLAN_TEMPORAL_KEY_LENGTH]  = {0};
    oal_uint16                          us_user_idx                            = 0;
    hal_security_key_stru               st_security_key;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_device_stru                     *pst_mac_device;
#endif
    /*1.0 ptk index 检查 */
    if(uc_key_index >= WLAN_NUM_TK)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }
    if (OAL_PTR_NULL == puc_mac_addr)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*1.1 根据mac地址找到user索引*/
    pst_current_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, puc_mac_addr);
    if (OAL_PTR_NULL == pst_current_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_ptk_key::pst_current_dmac_user null.}");

        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }
    pst_current_mac_user = &pst_current_dmac_user->st_user_base_info;

    /*2.1 参数准备*/
    pst_key = &pst_current_mac_user->st_key_info.ast_key[uc_key_index];
    if ((WLAN_80211_CIPHER_SUITE_TKIP !=(oal_uint8)pst_key->ul_cipher)
        && (WLAN_80211_CIPHER_SUITE_CCMP != (oal_uint8)pst_key->ul_cipher))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_ptk_key::invalid chiper type[%d], uc_key_index=%d.}", uc_key_index, pst_key->ul_cipher);

        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    st_security_key.uc_key_id      = uc_key_index;
    st_security_key.en_key_type    = HAL_KEY_TYPE_PTK;
    st_security_key.en_key_origin  = dmac_11i_get_auth_type(pst_mac_vap);
    st_security_key.en_update_key  = OAL_TRUE;
    st_security_key.uc_lut_idx     = pst_current_dmac_user->uc_lut_index;
    st_security_key.en_cipher_type = pst_current_mac_user->st_key_info.en_cipher_type;
    st_security_key.puc_cipher_key = pst_key->auc_key;
    st_security_key.puc_mic_key    = OAL_PTR_NULL;



    if (WLAN_TEMPORAL_KEY_LENGTH < pst_key->ul_key_len)
    {
        st_security_key.puc_mic_key = auc_mic_key;
        /* 对于TKIP模式，MIC存在txrx交换bit顺序的情况，需要转换顺序*/
        if ((WLAN_80211_CIPHER_SUITE_TKIP == st_security_key.en_cipher_type) && (IS_STA(pst_mac_vap)))
        {
            oal_memcopy(auc_mic_key, pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH + WLAN_MIC_KEY_LENGTH, WLAN_MIC_KEY_LENGTH);
            oal_memcopy(auc_mic_key + WLAN_MIC_KEY_LENGTH, pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH, WLAN_MIC_KEY_LENGTH);
        }
        else
        {
            oal_memcopy(auc_mic_key, pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH, WLAN_MIC_KEY_LENGTH);
            oal_memcopy(auc_mic_key + WLAN_MIC_KEY_LENGTH, pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH + WLAN_MIC_KEY_LENGTH, WLAN_MIC_KEY_LENGTH);
        }
    }

    /*3.1 用户相关MIB信息保存*/
    us_user_idx = pst_current_mac_user->us_assoc_id;
    mibset_RSNAStatsSTAAddress(puc_mac_addr,pst_mac_vap, us_user_idx);
    mibset_RSNAStatsSelectedPairwiseCipher(pst_current_mac_user->st_key_info.en_cipher_type, pst_mac_vap, us_user_idx);
    mac_mib_set_RSNAPairwiseCipherSelected(pst_mac_vap, pst_current_mac_user->st_key_info.en_cipher_type);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PROXYSTA, "{dmac_11i_add_ptk_key::mac_res_get_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            /* 4.1 将加密方式和加密密钥写入CE中, 同时增加激活用户,写入地址为Proxy STA的地址 */
            ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, mac_mib_get_StationID(pst_mac_vap));
        }
        else
        {
            /* 4.1 repeater开关打开，普通的sta0需要将加密方式和加密密钥写入CE中, 同时增加激活用户 */
            ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, puc_mac_addr);
        }
    }
    else
    {
        /* 4.1 repeater开关关闭时，都需要将加密方式和加密密钥写入CE中, 同时增加激活用户 */
        ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, puc_mac_addr);
    }
#else
    /* 4.1 将加密方式和加密密钥写入CE中, 同时增加激活用户 */
    ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, puc_mac_addr);
#endif

    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_update_key_to_ce::dmac_11i_update_key_to_ce failed[%d].}", ul_ret);

        return ul_ret;
    }


    /* 寄存器写入成功后，更新单播用户密钥 */
    mac_user_set_key(pst_current_mac_user, st_security_key.en_key_type, st_security_key.en_cipher_type, st_security_key.uc_key_id);

    /*5.1 打开1X端口认证状态*/
    mac_user_set_port(pst_current_mac_user, OAL_TRUE);

    /*6.1 打开发送描述符的加密属性*/
    pst_current_mac_user->st_user_tx_info.st_security.en_cipher_key_type = HAL_KEY_TYPE_PTK;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_11i_add_gtk_key
 功能描述  : 设置组播密钥
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 输出参数  : oal_uint32
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_11i_add_gtk_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index)
{
    oal_uint32                          ul_ret;
    dmac_vap_stru                      *pst_dmac_vap            = OAL_PTR_NULL;
    mac_user_stru                      *pst_multi_user          = OAL_PTR_NULL;
    wlan_priv_key_param_stru           *pst_key                 = OAL_PTR_NULL;
    oal_uint8                           auc_mic_key[8]          = {0};
    hal_security_key_stru               st_security_key;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*1.1 根据索引找到组播user内存区域*/
    pst_multi_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*1.2 根据mac_vap获取dmac_vap*/
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    /*2.1 参数准备*/
    pst_key = &pst_multi_user->st_key_info.ast_key[uc_key_index];

#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_SW_BIP)

    if (WLAN_80211_CIPHER_SUITE_BIP == (oal_uint8)pst_key->ul_cipher)
    {
        /* BIP由软件完成，不需要设置给mac*/
        return OAL_SUCC;
    }
#endif
    if (WLAN_80211_CIPHER_SUITE_TKIP != (oal_uint8)pst_key->ul_cipher
        && WLAN_80211_CIPHER_SUITE_CCMP != (oal_uint8)pst_key->ul_cipher
        && WLAN_80211_CIPHER_SUITE_BIP != (oal_uint8)pst_key->ul_cipher)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_gtk_key::invalid chiper type[%d].}", pst_key->ul_cipher);

        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }


    st_security_key.en_cipher_type = (oal_uint8)pst_key->ul_cipher;
    st_security_key.uc_key_id      = uc_key_index;
    st_security_key.en_key_type    = dmac_11i_get_gtk_key_type(pst_mac_vap, st_security_key.en_cipher_type);

    pst_multi_user->st_key_info.bit_gtk ^= BIT0; /* GTK 槽位乒乓使用 */
    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_add_gtk_key::new bit_gtk=%u .}", pst_multi_user->st_key_info.bit_gtk);

    st_security_key.en_key_origin  = dmac_11i_get_auth_type(pst_mac_vap);
    st_security_key.en_update_key  = OAL_TRUE;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    st_security_key.uc_lut_idx     = pst_dmac_vap->pst_hal_vap->uc_vap_id;
#else
    st_security_key.uc_lut_idx     = (IS_AP(pst_mac_vap)) ? pst_dmac_vap->pst_hal_vap->uc_vap_id : 0;
#endif
    st_security_key.puc_cipher_key = pst_key->auc_key;
    st_security_key.puc_mic_key    = OAL_PTR_NULL;
    if (WLAN_TEMPORAL_KEY_LENGTH < pst_key->ul_key_len)
    {
        st_security_key.puc_mic_key = pst_key->auc_key + WLAN_TEMPORAL_KEY_LENGTH;
        /* 对于TKIP模式，MIC存在txrx交换bit顺序的情况，需要转换顺序*/
        if ((WLAN_80211_CIPHER_SUITE_TKIP == st_security_key.en_cipher_type) && (IS_STA(pst_mac_vap)))
        {
            oal_memcopy(auc_mic_key, st_security_key.puc_mic_key, 8);
            oal_memcopy(st_security_key.puc_mic_key, st_security_key.puc_mic_key + 8, 8);
            oal_memcopy(st_security_key.puc_mic_key + 8, auc_mic_key, 8);
        }
    }

    /*3.1 将加密方式和加密密钥写入CE中*/
    ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_gtk_key::dmac_11i_update_key_to_ce failed[%d].}", ul_ret);

        return ul_ret;
    }

    /* 设置成功后，更新一下multiuser中的安全信息,目前只有keyid在发送组播帧时会使用到 */
    mac_user_set_key(pst_multi_user, st_security_key.en_key_type, st_security_key.en_cipher_type, st_security_key.uc_key_id);

    /*4.1 打开1X端口认证状态*/
    mac_user_set_port(pst_multi_user, OAL_TRUE);

    /*5.1 打开发送描述符的加密属性*/
    if (WLAN_KEY_TYPE_TX_GTK == st_security_key.en_key_type)
    {
        pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_add_wep_key
 功能描述  : 设置组播密钥
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 输出参数  : oal_uint32
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月20日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_11i_add_wep_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index)
{
    mac_user_stru                      *pst_multi_user;
    wlan_priv_key_param_stru           *pst_key                   = OAL_PTR_NULL;
    hal_security_key_stru               st_security_key;
    dmac_vap_stru                      *pst_dmac_vap              = OAL_PTR_NULL;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_device_stru                    *pst_mac_device;
#endif


    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE != mac_is_wep_enabled(pst_mac_vap))
    {
        return OAL_SUCC;
    }


    /*1.1 根据索引找到组播user内存区域*/
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*1.2 根据mac_vap获取dmac_vap*/
    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;

    if (WLAN_80211_CIPHER_SUITE_WEP_104 != pst_multi_user->st_key_info.en_cipher_type
        && WLAN_80211_CIPHER_SUITE_WEP_40 != pst_multi_user->st_key_info.en_cipher_type)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_wep_key::invalid ul_cipher type[%d].}", pst_multi_user->st_key_info.en_cipher_type);

        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }
    pst_key = &pst_multi_user->st_key_info.ast_key[uc_key_index];
    /*2.1 参数准备*///未覆盖
    st_security_key.uc_key_id      = uc_key_index;
    st_security_key.en_cipher_type = pst_multi_user->st_key_info.en_cipher_type;

    st_security_key.en_key_type    = dmac_11i_get_gtk_key_type(pst_mac_vap, st_security_key.en_cipher_type);
    st_security_key.en_key_origin  = dmac_11i_get_auth_type(pst_mac_vap);
    st_security_key.en_update_key  = OAL_TRUE;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            if (WLAN_KEY_TYPE_PTK == st_security_key.en_key_type)
            {
                st_security_key.uc_lut_idx = pst_mac_vap->st_vap_proxysta.uc_lut_idx; /* Proxy STA 需要和lut idx对齐 */
            }
            else
            {
                st_security_key.uc_lut_idx = 0; /* Proxy STA 需要和lut idx对齐 */
            }
        }
        else
        {
            st_security_key.uc_lut_idx = pst_dmac_vap->pst_hal_vap->uc_vap_id;
            if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode && WLAN_KEY_TYPE_RX_GTK == st_security_key.en_key_type)
            {
                /* sta0的rx gtk的lut idx为0 */
                st_security_key.uc_lut_idx = 0;
            }
        }
    }
    else
    {
        st_security_key.uc_lut_idx = pst_dmac_vap->pst_hal_vap->uc_vap_id;
    }
#else
    st_security_key.uc_lut_idx = pst_dmac_vap->pst_hal_vap->uc_vap_id;
#endif
    st_security_key.puc_cipher_key = pst_key->auc_key;
    st_security_key.puc_mic_key    = OAL_PTR_NULL;

    /*3.1 将加密方式和加密密钥写入CE中*/
    if (OAL_SUCC != dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, OAL_PTR_NULL))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_11i_add_wep_key::dmac_11i_update_key_to_ce invalid.}");

        return OAL_FAIL;
    }

    /*5.1 打开发送描述符的加密属性*/
    if (WLAN_KEY_TYPE_TX_GTK == st_security_key.en_key_type)
    {
        pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = HAL_KEY_TYPE_TX_GTK;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_del_ptk_key
 功能描述  : 删除单播密钥
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 输出参数  : oal_uint32
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_11i_del_ptk_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index, oal_uint8 *puc_mac_addr)
{
    oal_uint32                          ul_ret;
    dmac_user_stru                     *pst_current_dmac_user     = OAL_PTR_NULL;
    oal_uint8                           uc_key_id;
    oal_uint8                           uc_ce_lut_index;
    hal_cipher_key_type_enum_uint8      en_key_type;

    /*1.1 根据mac地址找到user索引*/
    pst_current_dmac_user = mac_vap_get_dmac_user_by_addr(pst_mac_vap, puc_mac_addr);
    if (OAL_PTR_NULL == pst_current_dmac_user)
    {
        OAM_WARNING_LOG0(0, OAM_SF_WPA, "{dmac_11i_del_ptk_key::mac_vap_find_user_by_macaddr failed.}");
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*2.1 参数准备*/
    en_key_type     = HAL_KEY_TYPE_PTK;
    uc_key_id       = uc_key_index;
    uc_ce_lut_index = pst_current_dmac_user->uc_lut_index;

    /*3.1 去激活用户*/
    ul_ret = dmac_11i_del_peer_macaddr(pst_mac_vap, uc_ce_lut_index);
    if (OAL_SUCC != ul_ret)
    {//weifugai
        OAM_ERROR_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                      "{dmac_11i_del_ptk_key::dmac_11i_del_peer_macaddr failed[%d],uc_key_id=%d en_key_type=%d uc_ce_lut_index=%d.}",
                       ul_ret, uc_key_id, en_key_type, uc_ce_lut_index);
        return ul_ret;
    }

    /*3.2 删除CE中的对应密钥*/
    ul_ret = dmac_11i_del_key_to_ce(pst_mac_vap, uc_key_id, en_key_type, uc_ce_lut_index);
    if (OAL_SUCC != ul_ret)
    {//weifugai
        OAM_ERROR_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                      "{dmac_11i_del_ptk_key::dmac_11i_del_key_to_cefailed[%d],uc_key_id=%d en_key_type=%d uc_ce_lut_index=%d.}",
                       ul_ret, uc_key_id, en_key_type, uc_ce_lut_index);

        return ul_ret;
    }

    /*4.1 关闭1X端口认证状态*/
    mac_user_set_port(&pst_current_dmac_user->st_user_base_info, OAL_FALSE);

    /*5.1 关闭发送描述符的加密属性*/
    pst_current_dmac_user->st_user_base_info.st_user_tx_info.st_security.en_cipher_key_type = HAL_KEY_TYPE_BUTT;


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_del_gtk_key
 功能描述  : 删除组播密钥
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 输出参数  : oal_uint32
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_11i_del_gtk_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index)
{
    oal_uint32                          ul_ret;
    dmac_vap_stru                      *pst_dmac_vap;
    mac_user_stru                      *pst_current_mac_user;
    oal_uint8                           uc_key_id;
    oal_uint8                           uc_ce_lut_index;
    hal_cipher_key_type_enum_uint8      en_key_type;

    if(OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*1.1 根据索引找到组播user内存区域*/
    pst_current_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if(OAL_PTR_NULL == pst_current_mac_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*1.2 根据mac_vap获取dmac_vap*/
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    /*2.1 参数准备*/
    uc_key_id = 0;
    en_key_type = dmac_11i_get_gtk_key_type(pst_mac_vap, pst_current_mac_user->st_key_info.en_cipher_type);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    uc_ce_lut_index = pst_dmac_vap->pst_hal_vap->uc_vap_id;
#else
    uc_ce_lut_index = (IS_AP(pst_mac_vap)) ? pst_dmac_vap->pst_hal_vap->uc_vap_id : 0;
#endif

    /*3.1 删除CE中的对应密钥*/
    ul_ret = dmac_11i_del_key_to_ce(pst_mac_vap, uc_key_id, en_key_type, uc_ce_lut_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                      "{dmac_11i_del_gtk_key::dmac_11i_del_key_to_ce[%d],uc_key_id=%d en_key_type=%d uc_ce_lut_index=%d.}",
                       ul_ret, uc_key_id, en_key_type, uc_ce_lut_index);

        return ul_ret;
    }

    /*4.1 关闭1X端口认证状态*/
    mac_user_set_port(pst_current_mac_user, OAL_FALSE);

    /*5.1 关闭发送描述符的加密属性*/
    if (HAL_KEY_TYPE_TX_GTK == en_key_type)
    {
        pst_current_mac_user->st_user_tx_info.st_security.en_cipher_key_type = HAL_KEY_TYPE_BUTT;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_add_key_from_user
 功能描述  : 设置用户的加密套件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_11i_add_key_from_user(mac_vap_stru *pst_mac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint8                           uc_key_id;
    oal_uint8                          *puc_cipkey;
    oal_uint8                          *puc_mickey;
    oal_uint8                           en_auth_supp;
    oal_uint32                          ul_ret;
    hal_security_key_stru               st_security_key;

    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == pst_dmac_user)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        en_auth_supp = HAL_AUTH_KEY;
    }
    else
    {
        en_auth_supp = HAL_SUPP_KEY;
    }

    /* wep加密时不需要恢复PTK密钥 */
    if(OAL_TRUE == mac_is_wep_allowed(pst_mac_vap))
    {
        return OAL_SUCC;
    }


    for(uc_key_id=0; uc_key_id <= pst_dmac_user->uc_max_key_index; uc_key_id++)
    {
        puc_cipkey = pst_dmac_user->st_user_base_info.st_key_info.ast_key[uc_key_id].auc_key;        /* 前16字节是cipherkey */
        puc_mickey = pst_dmac_user->st_user_base_info.st_key_info.ast_key[uc_key_id].auc_key + 16;   /* 后16字节是mickey */

        st_security_key.uc_key_id      = uc_key_id;
        st_security_key.en_key_type    = HAL_KEY_TYPE_PTK;
        st_security_key.en_key_origin  = en_auth_supp;
        st_security_key.en_update_key  = OAL_TRUE;
        st_security_key.uc_lut_idx     = pst_dmac_user->uc_lut_index;
        st_security_key.en_cipher_type = pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type;
        st_security_key.puc_cipher_key = puc_cipkey;
        st_security_key.puc_mic_key    = puc_mickey;

        ul_ret = dmac_11i_update_key_to_ce(pst_mac_vap, &st_security_key, pst_dmac_user->st_user_base_info.auc_user_mac_addr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_11i_add_key_from_user::dmac_11i_update_key_to_ce failed[%d].}", ul_ret);

            return ul_ret;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_remove_key_from_user
 功能描述  : 删除用户加密套件
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_11i_remove_key_from_user(mac_vap_stru *pst_mac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint8   uc_key_id;
    oal_uint32  ul_ret;

    /*只需要删除TIKP/CCMP单播密钥*/
    switch (pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type)
    {
        case WLAN_80211_CIPHER_SUITE_GROUP_CIPHER:
        case WLAN_80211_CIPHER_SUITE_WEP_40:
        case WLAN_80211_CIPHER_SUITE_NO_ENCRYP:
        case WLAN_80211_CIPHER_SUITE_WEP_104:
        case WLAN_80211_CIPHER_SUITE_BIP:
        case WLAN_80211_CIPHER_SUITE_GROUP_DENYD:
        {
            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_11i_remove_key_from_user::cipher type=%d.}", pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type);
            break;
        }
        case WLAN_80211_CIPHER_SUITE_TKIP:
        case WLAN_80211_CIPHER_SUITE_CCMP:
        {
            for(uc_key_id=0; uc_key_id <= pst_dmac_user->uc_max_key_index; uc_key_id++)
            {
                ul_ret = dmac_11i_del_key_to_ce(pst_mac_vap, uc_key_id, HAL_KEY_TYPE_PTK, pst_dmac_user->uc_lut_index);
                if (OAL_SUCC != ul_ret)
                {//weifugai
                    OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                                   "{dmac_11i_remove_key_from_user::dmac_11i_del_key_to_ce failed[%d], uc_key_id=%d uc_lut_index=%d.}",
                                   ul_ret, uc_key_id, pst_dmac_user->uc_lut_index);
                }
            }
            break;
        }
        default:
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_11i_remove_key_from_user::invalid cipher type[%d].}", pst_dmac_user->st_user_base_info.st_key_info.en_cipher_type);

            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_11i_init_port
 功能描述  : 初始化port
 输入参数  :
 输出参数  : oal_uint32
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月15日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_config_11i_init_port(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    mac_user_stru                               *pst_mac_user;

    MAC_11I_ASSERT(OAL_PTR_NULL != pst_mac_vap, OAL_ERR_CODE_PTR_NULL);

    /* 根据mac找到对应AP USER结构 */
    pst_mac_user = mac_vap_get_user_by_addr(pst_mac_vap, puc_param);
    MAC_11I_ASSERT(OAL_PTR_NULL != pst_mac_user, OAL_ERR_CODE_PTR_NULL);

    mac_vap_init_user_security_port(pst_mac_vap, pst_mac_user);
#endif
    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_config_11i_add_key_set_reg
 功能描述  : add key 处理
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 输出参数  : oal_uint32
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月27日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_11i_add_key_set_reg(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index, oal_uint8 *puc_mac_addr)
{
    oal_uint32                            ul_ret;

    /*1.1 入参检查*/
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*2.1 如果是单播，需要设置PTK*/
    if (OAL_PTR_NULL != puc_mac_addr)
    {
        ul_ret = dmac_11i_add_ptk_key(pst_mac_vap, puc_mac_addr, uc_key_index);
    }
    /*2.2 如果是组播，需要设置GTK*/
    else
    {
        ul_ret = dmac_11i_add_gtk_key(pst_mac_vap, uc_key_index);
    }
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_config_11i_add_key
 功能描述  : add key处理key,需要更新寄存器和相关的mib，还有其他配置
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 输出参数  :
 返 回 值  : 0:成功,其他:失败
 调用函数  :
 被调函数  :
 其他说明  :1.由于1102 hmac2dmac跨实体，目前一个事件内存大约为52字节，所以addkey
                事件必须分成两个事件下发。
            2.由于跨实体，hmac的内容必须同步到dmac。
 修改历史      :
  1.日    期   : 2014年11月21日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_11i_add_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32                       ul_ret;
    mac_addkey_param_stru           *pst_payload_addkey_params;
    oal_uint8                       *puc_mac_addr;
    oal_uint8                        uc_key_index;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_stru                   *pst_mac_user;
    mac_key_params_stru             *pst_key;
    oal_uint16                       us_user_idx;
#endif
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{dmac_config_11i_add_key::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*2.1 获取参数*/
    pst_payload_addkey_params = (mac_addkey_param_stru *)puc_param;
    uc_key_index = pst_payload_addkey_params->uc_key_index;
    puc_mac_addr = (oal_uint8*)pst_payload_addkey_params->auc_mac_addr;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    pst_key      = &(pst_payload_addkey_params->st_key);

    /*2.2 索引值最大值检查*/
    if(uc_key_index >= WLAN_NUM_TK + WLAN_NUM_IGTK)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::invalid uc_key_index[%d].}", uc_key_index);
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }


    /*2.3 密钥参数指针不能为空*/
    if (OAL_PTR_NULL == pst_key)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::pst_params null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == pst_payload_addkey_params->en_pairwise)
    {
        /* 单播密钥存放在单播用户中 */
        ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::find_user_by_macaddr fail[%d].}", ul_ret);
            return ul_ret;
        }
    }
    else
    {
        /* 组播密钥存放在组播用户中 */
        us_user_idx  = pst_mac_vap->us_multi_user_idx;
    }

    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::get_mac_user null.}");
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /*3.1 将加密属性更新到用户中*/
    ul_ret = mac_vap_add_key(pst_mac_vap, pst_mac_user, uc_key_index, pst_key);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{hmac_config_11i_add_key::mac_11i_add_key fail[%d].}", ul_ret);
        return ul_ret;
    }

#endif /* #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) */

    /* WEP模式下不需要在addkey流程设置寄存器 */
    if (OAL_TRUE == mac_is_wep_enabled(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    if (OAL_FALSE == pst_payload_addkey_params->en_pairwise)
    {
        puc_mac_addr = OAL_PTR_NULL;
    }

    /* 设置硬件寄存器 */
    ul_ret = dmac_config_11i_add_key_set_reg(pst_mac_vap, uc_key_index, puc_mac_addr);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_add_key::set_reg fail[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_WAPI
/*****************************************************************************
 函 数 名  : dmac_config_wapi_add_key
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 其他说明  :1.
 修改历史      :
  1.日    期   : 2015年5月27日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_wapi_add_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    dmac_vap_stru       *pst_dmac_vap;

    /*1.2 根据mac_vap获取dmac_vap*/
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_wapi_add_key::pst_dmac_vap null.}");
        return OAL_FAIL;
    }

    /* 关掉硬件的加解密功能 */
    hal_disable_ce(pst_dmac_vap->pst_hal_device);

    return OAL_SUCC;
}

#endif



/*****************************************************************************
 函 数 名  : dmac_config_11i_remove_key
 功能描述  : remove key
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 输出参数  : oal_uint32
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月4日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_11i_remove_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32                       ul_ret;
    oal_uint8                        uc_key_index;
    oal_bool_enum_uint8              en_pairwise;
    oal_uint8                       *puc_mac_addr = OAL_PTR_NULL;
    mac_removekey_param_stru        *pst_removekey_params         = OAL_PTR_NULL;

    /*1.1 入参检查*/
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{dmac_config_11i_remove_key::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /*2.1 获取参数*/
    pst_removekey_params = (mac_removekey_param_stru *)puc_param;
    uc_key_index = pst_removekey_params->uc_key_index;
    en_pairwise  = pst_removekey_params->en_pairwise;
    puc_mac_addr = (oal_uint8*)pst_removekey_params->auc_mac_addr;


    /*3.1 如果是单播*/
    if((OAL_TRUE != mac_addr_is_zero(puc_mac_addr)) && (OAL_TRUE == en_pairwise))
    {
        ul_ret = dmac_11i_del_ptk_key(pst_mac_vap, uc_key_index, puc_mac_addr);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_config_11i_remove_key::dmac_11i_del_ptk_key failed[%d].}", ul_ret);

            return ul_ret;
        }
    }
    /*3.2 如果是组播*/
    else
    {
        ul_ret = dmac_11i_del_gtk_key(pst_mac_vap, uc_key_index);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{dmac_config_11i_remove_key::dmac_11i_del_gtk_key failed[%d].}", ul_ret);

            return ul_ret;
        }
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_set_default_key
 功能描述  : set deault key 逻辑处理
 输入参数  : mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月8日
    作    者   : g00260350
    修改内容   : 新生成函数

2.日    期   : 2014年11月25日
  作    者   : 即使不用更新寄存器，02也需要同步hmac的配置，因此把 非加密套件的
                判断挪到dmac
  修改内容   : 新生成函数
*****************************************************************************/
oal_uint32  dmac_config_11i_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_setdefaultkey_param_stru    *pst_defaultkey_params = OAL_PTR_NULL;
    oal_uint32                       ul_ret;
    oal_uint8                        uc_key_index;
    oal_bool_enum_uint8              en_unicast;
    oal_bool_enum_uint8              en_multicast;

    /*1.1 入参检查*/
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{dmac_config_11i_set_default_key::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*2.1 获取参数*/
    pst_defaultkey_params = (mac_setdefaultkey_param_stru *)puc_param;
    uc_key_index = pst_defaultkey_params->uc_key_index;

    /*2.2 索引值最大值检查*/
    if(uc_key_index >= (WLAN_NUM_TK + WLAN_NUM_IGTK))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                      "{dmac_config_11i_set_default_key::invalid uc_key_index[%d].}", uc_key_index);

        return OAL_FAIL;
    }
    en_unicast   = pst_defaultkey_params->en_unicast;
    en_multicast = pst_defaultkey_params->en_multicast;
    /*2.3 参数有效性检查*/
    if ((OAL_FALSE == en_multicast) && (OAL_FALSE == en_unicast))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_config_11i_set_default_key::invalid mode.}");
        return OAL_FAIL;
    }
 
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

    if (uc_key_index >= WLAN_NUM_TK)
    {
        /*3.1 设置default mgmt key属性*/
        ul_ret = mac_vap_set_default_mgmt_key(pst_mac_vap, uc_key_index);
    }
    else
    {
        /*3.2 设置 WEP default key属性*/
        ul_ret = mac_vap_set_default_key(pst_mac_vap, uc_key_index);
    }

    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{dmac_config_11i_set_default_key::set key[%d] failed[%d].}", uc_key_index, ul_ret);
        return ul_ret;
    }

#endif

    if (uc_key_index < WLAN_NUM_TK)
    {
        ul_ret = dmac_11i_add_wep_key(pst_mac_vap, uc_key_index);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                        "{dmac_config_11i_set_default_key::dmac_11i_add_wep_key failed[%d].}", ul_ret);
            return ul_ret;
        }
    }


    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_11i_tkip_mic_failure_handler
 功能描述  : 将mic事件上报到hmac
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_11i_tkip_mic_failure_handler(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_user_mac, oal_nl80211_key_type en_key_type)
{
    frw_event_mem_stru           *pst_event_mem;          /* 申请事件返回的内存指针 */
    frw_event_stru               *pst_dmac_to_hmac_event; /* 指向申请事件的payload指针 */
    dmac_to_hmac_mic_event_stru  *pst_mic_event;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_user_mac))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{dmac_11i_tkip_mic_failure_handler::param null.}");

        return;
    }
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_to_hmac_mic_event_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{dmac_11i_tkip_mic_failure_handler::pst_event_mem null.}");
        return;
    }

    /* 获得事件指针 */
    pst_dmac_to_hmac_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 填写事件头 */
    FRW_EVENT_HDR_INIT(&(pst_dmac_to_hmac_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_DRX,
                       DMAC_WLAN_DRX_EVENT_SUB_TYPE_TKIP_MIC_FAILE,/* DMAC tkip mic faile 上报给HMAC */
                       OAL_SIZEOF(dmac_to_hmac_mic_event_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    /*将mic信息上报给hmac*/
    pst_mic_event = (dmac_to_hmac_mic_event_stru *)(pst_dmac_to_hmac_event->auc_event_data);
    oal_memcopy(pst_mic_event->auc_user_mac, puc_user_mac, WLAN_MAC_ADDR_LEN);
    pst_mic_event->en_key_type   = en_key_type;
    pst_mic_event->l_key_id     = 0;/*tkip 只支持1个密钥，写死0*/

    /* 分发 */
    frw_event_dispatch_event(pst_event_mem);

    /* 释放事件内存 */
    FRW_EVENT_FREE(pst_event_mem);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

