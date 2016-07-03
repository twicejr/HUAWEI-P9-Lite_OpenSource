


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "hal_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_rx_filter.h"
#include "dmac_vap.h"
#include "dmac_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RX_FILTER_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


oal_uint32 dmac_set_rx_filter_value(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                         *pst_event;
    frw_event_hdr_stru                     *pst_event_hdr;
    mac_device_stru                        *pst_device;
    oal_uint32                             *pul_rx_filter_value;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_set_rx_filter_value::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pul_rx_filter_value     = (oal_uint32 *)pst_event->auc_event_data;

    /* 获取device结构的信息 */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{dmac_set_rx_filter_value::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_set_rx_filter(pst_device->pst_device_stru,*pul_rx_filter_value);

    return OAL_SUCC;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

