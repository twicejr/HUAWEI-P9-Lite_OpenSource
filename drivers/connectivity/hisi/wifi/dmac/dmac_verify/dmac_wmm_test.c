/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_wmm_test.c
  版 本 号   : 初稿
  作    者   : z00260280
  生成日期   : 2014年1月27日
  最近修改   :
  功能描述   : 芯片验证WMM动态开关等
  函数列表   :
  修改历史   :
  1.日    期   : 2014年1月27日
    作    者   : z00260280
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ?????
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "dmac_ext_if.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_wmm_test.h"
#include "dmac_config.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_WMM_TEST_C

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 内部函数声明
*****************************************************************************/
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* WME初始参数定义，按照OFDM初始化 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : dmac_test_open_wmm_test
 功能描述  : 暂停发包的情况下，开启wmm
 输入参数  : pst_mac_vap: MAC VAP
             uc_test_type:测试类型
 输出参数  :
 返 回 值  : 成功/失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : z00260280
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_test_open_wmm_test(mac_vap_stru *pst_mac_vap, oal_uint8 uc_test_type)
{
    hal_to_dmac_device_stru *pst_hal_device;
    mac_device_stru         *pst_mac_device;
    dmac_vap_stru           *pst_dmac_vap;
    oal_uint32               ul_tsf = 0;
    oal_uint32               ul_tsf_passed = 0;
    mac_wme_param_stru      *pst_wmm;
    hal_to_dmac_vap_stru    *pst_hal_vap;
    oal_uint                 ul_irq_flag;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_PTR_NULL == pst_hal_device)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_hal_vap  = pst_dmac_vap->pst_hal_vap;
    pst_wmm = mac_get_wmm_cfg(pst_mac_vap->en_vap_mode);

    /* 关中断，挂起硬件发送需要关中断 */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DTOWT);

    if (DMAC_TEST_WMM_SUSPEND == (uc_test_type & DMAC_TEST_WMM_SUSPEND))
    {
        /* 挂起硬件发送 */
        hal_set_machw_tx_suspend(pst_hal_device);
    }

    /* 获取时间戳 */
    hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf);

    /* 触发硬件abort */
    hal_set_tx_abort_en(pst_hal_device, 1);

    if (DMAC_TEST_WMM_ENABLE == (uc_test_type & DMAC_TEST_WMM_ENABLE))
    {
        /* 打开WMM */
        hal_enable_machw_edca(pst_hal_device);
        /* 重新设置WMM参数 */
        dmac_config_set_wmm_open_cfg(pst_hal_vap, pst_wmm);
    }
    else
    {
        /* 关闭WMM */
        hal_disable_machw_edca(pst_hal_device);
        /* 重新设置WMM参数 */
        dmac_config_set_wmm_close_cfg(pst_hal_vap, pst_wmm);
    }

    /* 退出abort */
    hal_set_tx_abort_en(pst_hal_device, 0);

    if (DMAC_TEST_WMM_SUSPEND == (uc_test_type & DMAC_TEST_WMM_SUSPEND))
    {
        /* 重新设置硬件发送 */
        hal_set_machw_tx_resume(pst_hal_device);
    }

    /* 再次获取时间戳 */
    hal_vap_tsf_get_32bit(pst_hal_vap, &ul_tsf_passed);

    /* 开中断 */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DTOWT);

    /*打印消耗的时间，单位为us*/
    OAM_WARNING_LOG1(0, OAM_SF_WMM, "{dmac_test_open_wmm_test::wmm time passed=%u}\r\n",
                                     (ul_tsf_passed - ul_tsf));
    return OAL_SUCC;
}


#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

