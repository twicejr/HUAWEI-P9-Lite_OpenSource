

#ifndef __HMAC_PROTECTION_H__
#define __HMAC_PROTECTION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_PROTECTION_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WLAN_PROTECTION_NON_ERP_AGING_THRESHOLD        (12)   /*ERP 老化计数最大值*/
#define WLAN_PROTECTION_NON_HT_AGING_THRESHOLD         (12)   /*HT 老化计数最大值*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_uint32 hmac_protection_update_mib_ap(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_protection_update_mode_ap(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_protection_update_mode_sta(mac_vap_stru *pst_mac_vap_sta, hmac_user_stru *pst_hmac_user);
extern oal_uint32 hmac_protection_obss_aging_ap(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_protection_del_user(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32 hmac_protection_set_autoprot(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_mode);
extern oal_uint32 hmac_protection_start_timer(hmac_vap_stru  *pst_hmac_vap);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_protection.h */
