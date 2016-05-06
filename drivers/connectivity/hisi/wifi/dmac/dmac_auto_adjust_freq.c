/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_auto_adjust_freq.c
  版 本 号   : 初稿
  作    者   : w00316376
  生成日期   : 2015年6月26日
  最近修改   :
  功能描述   :device调频相关函数实现
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月26日
    作    者   : w00316376
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
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#include "oam_ext_if.h"
#include "pm_extern.h"
#include "dmac_resource.h"
#include "dmac_auto_adjust_freq.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_AUTO_ADJUST_FREQ_C



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
oal_uint16 g_device_speed_freq[][FREQ_BUTT] = {
    /*device主频类型*/
    {PM_40MHZ,PM_160MHZ,PM_240MHZ,PM_480MHZ},     /*WLAN_BW_20*/
    {PM_40MHZ,PM_160MHZ,PM_240MHZ,PM_480MHZ},    /*WLAN_HT_BW_40*/
    {PM_40MHZ,PM_160MHZ,PM_240MHZ,PM_480MHZ},   /*WLAN_VHT_BW_40*/
    {PM_80MHZ,PM_160MHZ,PM_240MHZ,PM_480MHZ},   /*WLAN_VHT_BW_80*/
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_get_device_freq_level
 功能描述  : 获取device的调频等级
 输入参数  : 无
 输出参数  : device的调频类型
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : z00185449
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_get_device_freq_level(void)
{
    oal_uint8 uc_vap_id;
    mac_vap_stru *pst_mac_vap;
    wlan_auto_freq_bw_enum_uint8 uc_auto_freq_bw_type = WLAN_BW_20;

    for (uc_vap_id = 0; uc_vap_id < WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT; uc_vap_id++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(uc_vap_id);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_get_device_freq_type pst_mac_vap is null.}");
            continue;
        }
        if ((MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state) &&
            (MAC_VAP_STATE_PAUSE != pst_mac_vap->en_vap_state))
        {
            continue;
        }
        if ((pst_mac_vap->en_protocol != WLAN_VHT_MODE) &&
            (pst_mac_vap->en_protocol != WLAN_VHT_ONLY_MODE))   /*非11ac*/
        {
            if ((WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth) ||
                (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth))
            {
                if (uc_auto_freq_bw_type <= WLAN_HT_BW_40)
                {
                    uc_auto_freq_bw_type = WLAN_HT_BW_40;
                }
            }
        }
        else
        {
            if ((WLAN_BAND_WIDTH_20M == pst_mac_vap->st_channel.en_bandwidth) ||
                (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth) ||
                (WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth))
            {
                if (uc_auto_freq_bw_type <= WLAN_VHT_BW_40)
                {
                    uc_auto_freq_bw_type = WLAN_VHT_BW_40;
                }
            }
            else
            {
                uc_auto_freq_bw_type = WLAN_VHT_BW_80;
            }
        }
    }
//    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_config_get_device_freq_type uc_auto_freq_bw_type = %d.}",uc_auto_freq_bw_type);
    return uc_auto_freq_bw_type;
}
/*****************************************************************************
 函 数 名  : dmac_get_device_freq_value
 功能描述  : 获取device的调频类型
 输入参数  : 无
 输出参数  : oal_device_freq_type_enum_uint8 uc_device_freq_type,device的调频类型,
             wlan_auto_freq_bw_enum_uint8 uc_auto_freq_bw_type,调频频宽类型
             oal_uint16* pusdevice_freq_value,device主频值
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : z00185449
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_get_device_freq_value(oal_device_freq_type_enum_uint8 uc_device_freq_type,wlan_auto_freq_bw_enum_uint8 uc_auto_freq_bw_type,oal_uint16* pusdevice_freq_value)
{
    if (uc_device_freq_type > FREQ_HIGHEST)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_get_device_freq_value:para error,uc_device_freq_type = %d.}",uc_device_freq_type);
        return OAL_FAIL;
    }
    if (uc_auto_freq_bw_type >= WLAN_BW_BUTT)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_get_device_freq_value:para error,uc_auto_freq_bw_type = %d.}",uc_auto_freq_bw_type);
        return OAL_FAIL;
    }
    *pusdevice_freq_value = g_device_speed_freq[uc_auto_freq_bw_type][uc_device_freq_type];
//    OAM_WARNING_LOG3(0, OAM_SF_ANY, "{dmac_get_device_freq_value uc_auto_freq_bw_type = %d,uc_auto_freq_bw_type = %d,device_freq_value = %d.}",uc_auto_freq_bw_type,uc_device_freq_type,*pusdevice_freq_value);

    return OAL_SUCC;
}

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


