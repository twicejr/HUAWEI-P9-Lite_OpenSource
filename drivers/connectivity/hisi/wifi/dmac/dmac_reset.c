/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_reset.c
  版 本 号   : 初稿
  作    者   : zourong
  生成日期   : 2013年11月7日
  最近修改   :
  功能描述   : 软件复位硬件功能实现
  函数列表   :
  修改历史   :
  1.日    期   : 2013年11月7日
    作    者   : zourong 52447
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
#include "hal_ext_if.h"
#include "oal_net.h"
#include "oal_kernel_file.h"
#include "oal_mem.h"
#include "wlan_spec.h"
#include "mac_frame.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_user.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_rx_data.h"
#include "dmac_tx_complete.h"
#include "dmac_11i.h"
#include "dmac_ext_if.h"
#include "dmac_reset.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "dmac_pm_sta.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RESET_C

#ifndef _PRE_WLAN_PROFLING_MIPS
OAL_STATIC  oal_uint32 dmac_reset_lut_init(oal_void);
OAL_STATIC  oal_void dmac_reset_lut_destroy(oal_void);
OAL_STATIC oal_void dmac_reset_save_tsf(mac_device_stru* pst_mac_device,oal_uint32* pst_tsf_array);
OAL_STATIC oal_void dmac_reset_restore_tsf(mac_device_stru* pst_mac_device,oal_uint32* pst_tsf_array,oal_time_us_stru *pst_time_record);
#endif
oal_void dmac_reset_rx_dscr_queue_flush(hal_to_dmac_device_stru* pst_hal);

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

oal_void dmac_reset_debug_init(oal_void);
oal_void dmac_reset_debug_close(oal_void);
oal_void dmac_reset_debug_to_file(oal_uint8* pst_str);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_send_sys_event(
                mac_vap_stru                     *pst_mac_vap,
                wlan_cfgid_enum_uint16            en_cfg_id,
                oal_uint16                        us_len,
                oal_uint8                        *puc_param);
#else
OAL_STATIC oal_uint32 dmac_reset_save_txbf_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_txbf_lut);
OAL_STATIC oal_uint32 dmac_reset_restore_txbf_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_txbf_lut);
OAL_STATIC oal_uint32 dmac_reset_restore_cipher_lut(mac_device_stru* pst_mac_device);
OAL_STATIC oal_uint32 dmac_reset_restore_ba_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_ba_lut);
OAL_STATIC oal_uint32 dmac_reset_save_ba_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_ba_lut);
OAL_STATIC oal_uint32 dmac_reset_restore_seq_lut(mac_device_stru* pst_mac_device,oal_uint32 *pst_qos_seq,oal_uint32 *pst_nonqos_seq);
OAL_STATIC oal_uint32 dmac_reset_save_seq_lut(mac_device_stru* pst_mac_device,oal_uint32 *pst_qos_seq,oal_uint32 *pst_nonqos_seq);
OAL_STATIC oal_uint32 dmac_reset_save_pn_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_rx_pn_ucast,oal_uint32* pst_rx_pn_mcast,
                                                      oal_uint32* pst_tx_pn_ucast,oal_uint32* pst_tx_pn_mcast);
OAL_STATIC oal_uint32 dmac_reset_restore_pn_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_rx_pn_ucast,oal_uint32* pst_rx_pn_mcast,
                                                      oal_uint32* pst_tx_pn_ucast,oal_uint32* pst_tx_pn_mcast);
OAL_STATIC oal_uint32 dmac_reset_restore_peer_addr_lut(mac_device_stru* pst_mac_device);

#endif
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
dmac_reset_mng_stru g_st_dmac_reset_mng;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_reset_lut_init
 功能描述  : 复位mac reg时，申请保存LUT表现场的内存
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_reset_init(oal_void)
{
   OAL_MEMZERO(&g_st_dmac_reset_mng, OAL_SIZEOF(dmac_reset_mng_stru));
#ifdef _PRE_WALN_FEATURE_LUT_RESET
    g_st_dmac_reset_mng.bit_pn_lut_reset         = 1;
    g_st_dmac_reset_mng.bit_key_lut_reset        = 1;
    g_st_dmac_reset_mng.bit_txbf_lut_reset       = 1;
    g_st_dmac_reset_mng.bit_smartant_lut_reset   = 1;
    g_st_dmac_reset_mng.bit_peer_addr_lut_reset  = 1;
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION))|| (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION))
    g_st_dmac_reset_mng.bit_seq_lut_reset        = 1;
    g_st_dmac_reset_mng.bit_ba_lut_reset         = 1;
    g_st_dmac_reset_mng.bit_save_tx_fake_fifo    = 1;
#endif
#endif
}

/*****************************************************************************
 函 数 名  : dmac_reset_lut_init
 功能描述  : 复位mac reg时，申请保存LUT表现场的内存
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
OAL_STATIC  oal_uint32 dmac_reset_lut_init(oal_void)
{
   g_st_dmac_reset_mng.pst_tsf = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,(WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE+WLAN_SERVICE_STA_MAX_NUM_PER_DEVICE)*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
   if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_tsf)
   {
       dmac_reset_lut_destroy();
       return OAL_ERR_CODE_ALLOC_MEM_FAIL;
   }

   if(g_st_dmac_reset_mng.bit_seq_lut_reset)
   {
       g_st_dmac_reset_mng.pst_sequence_qos = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ACTIVE_USER_MAX_NUM*WLAN_TID_MAX_NUM*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_sequence_qos)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }

   if(g_st_dmac_reset_mng.bit_ba_lut_reset)
   {
       g_st_dmac_reset_mng.pst_ba_rx = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_MAX_RX_BA*WLAN_BA_LUT_ENTRY_SIZE*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_ba_rx)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }

   if(g_st_dmac_reset_mng.bit_pn_lut_reset)
   {
       g_st_dmac_reset_mng.pst_rx_pn_ucast = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_TID_MAX_NUM*WLAN_ACTIVE_USER_MAX_NUM*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_rx_pn_ucast)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }

       g_st_dmac_reset_mng.pst_tx_pn_ucast = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ACTIVE_USER_MAX_NUM*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_tx_pn_ucast)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }

       g_st_dmac_reset_mng.pst_rx_pn_mcast = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ASSOC_AP_MAX_NUM*WLAN_TID_MAX_NUM*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_rx_pn_mcast)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }

       g_st_dmac_reset_mng.pst_tx_pn_mcast = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE*2*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_tx_pn_mcast)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }

   if(g_st_dmac_reset_mng.bit_txbf_lut_reset)
   {
       g_st_dmac_reset_mng.pst_txbf = (oal_uint32*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,WLAN_ACTIVE_USER_MAX_NUM*OAL_SIZEOF(oal_uint32),OAL_TRUE);
       if(OAL_PTR_NULL == g_st_dmac_reset_mng.pst_txbf)
       {
           dmac_reset_lut_destroy();
           return OAL_ERR_CODE_ALLOC_MEM_FAIL;
       }
   }
   return OAL_SUCC ;

}

/*****************************************************************************
 函 数 名  : dmac_reset_lut_destroy
 功能描述  : 复位mac reg时，释放保存LUT表现场的内存
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC  oal_void dmac_reset_lut_destroy(oal_void)
{

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_tsf)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_tsf, OAL_TRUE);
       g_st_dmac_reset_mng.pst_tsf = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_sequence_qos)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_sequence_qos, OAL_TRUE);
       g_st_dmac_reset_mng.pst_sequence_qos = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_ba_rx)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_ba_rx, OAL_TRUE);
       g_st_dmac_reset_mng.pst_ba_rx = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_rx_pn_ucast)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_rx_pn_ucast, OAL_TRUE);
       g_st_dmac_reset_mng.pst_rx_pn_ucast = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_tx_pn_ucast)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_tx_pn_ucast, OAL_TRUE);
       g_st_dmac_reset_mng.pst_tx_pn_ucast = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_rx_pn_mcast)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_rx_pn_mcast, OAL_TRUE);
       g_st_dmac_reset_mng.pst_rx_pn_mcast = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_tx_pn_mcast)
   {
       OAL_MEM_FREE(g_st_dmac_reset_mng.pst_tx_pn_mcast, OAL_TRUE);
       g_st_dmac_reset_mng.pst_tx_pn_mcast = OAL_PTR_NULL;
   }

   if(OAL_PTR_NULL != g_st_dmac_reset_mng.pst_txbf)
   {
        OAL_MEM_FREE(g_st_dmac_reset_mng.pst_txbf, OAL_TRUE);
       g_st_dmac_reset_mng.pst_txbf = OAL_PTR_NULL;
   }
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_reset_save_tx_queue
 功能描述  : reset时回收发送队列中的数据到reset专用虚假队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月2日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
OAL_STATIC oal_uint32 dmac_reset_save_tx_queue(hal_to_dmac_device_stru *pst_hal_device)
{
    oal_netbuf_stru     *pst_fake_buf;

    hal_tx_dscr_queue_header_stru  *pst_fake_queue;

    if (OAL_FALSE == g_st_dmac_reset_mng.bit_save_tx_fake_fifo)
    {
        return OAL_SUCC;
    }

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_reset_save_tx_queue::pst_hal_device null.}");
        return OAL_FAIL;
    }

    /* 申请fake_fifo_buff */
    pst_fake_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, (HAL_TX_QUEUE_NUM * OAL_SIZEOF(hal_tx_dscr_queue_header_stru)), OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_fake_buf)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,"dmac_reset_save_tx_queue::fake netbuff alloc error, device_id[%d]", pst_hal_device->uc_device_id);
        return OAL_ERR_CODE_HW_RESET_TX_QUEUE_MEMALLOC;
    }

    g_st_dmac_reset_mng.pst_fake_queue = pst_fake_buf;
    pst_fake_queue = (hal_tx_dscr_queue_header_stru *)OAL_NETBUF_PAYLOAD(pst_fake_buf);

    dmac_proc_save_tx_queue(pst_hal_device, pst_fake_queue);

    return OAL_SUCC;

}
/*****************************************************************************
 函 数 名  : dmac_reset_restore_tx_queue
 功能描述  : 恢复硬件发送队列中的内容
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月2日
    作    者   : z00273164
    修改内容   : 新生成函数

****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_tx_queue(hal_to_dmac_device_stru *pst_hal_device)
{
    hal_tx_dscr_queue_header_stru   *pst_fake_queue;

    if (OAL_FALSE == g_st_dmac_reset_mng.bit_save_tx_fake_fifo)
    {
        return OAL_SUCC;
    }

    pst_fake_queue = (hal_tx_dscr_queue_header_stru *)OAL_NETBUF_PAYLOAD(g_st_dmac_reset_mng.pst_fake_queue);

    dmac_proc_restore_tx_queue(pst_hal_device, pst_fake_queue);
    oal_netbuf_free(g_st_dmac_reset_mng.pst_fake_queue);

    return OAL_SUCC;

}
#endif
/*****************************************************************************
 函 数 名  : dmac_reset_hw
 功能描述  : reset hw的入口
 输入参数  : uc_type:
                 0x01：复位mac
                 0x10：复位phy
                 0x11:  复位mac&phy
             sub_module:
                 当uc_type = 0x01,即复位MAC时：
                 0: 全部模块复位
                 1：复位PA模块
                 2：复位TSF模块
                 3：复位master模块
                 4：复位CCMP/TKIP模块
             uc_reset_reg:
                 是否复位寄存器：
                 0：不复位寄存器
                 1：复位寄存器
             uc_reason:
                 复位原因：
                 0：error复位
                 1：配置命令复位
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月03日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_reset_hw(mac_device_stru* pst_device,oal_uint8* pst_param)
{
    oal_uint32                   ul_ret = OAL_SUCC;
#ifndef _PRE_WLAN_PROFLING_MIPS
    hal_to_dmac_device_stru     *pst_hal_device;
    dmac_reset_para_stru        *pst_reset_para;
    oal_uint                     ul_irq_flag;
    oal_time_us_stru             st_time_record =  {0,0};
    mac_reset_sys_stru           st_reset_sys;
    mac_vap_stru                *pst_mac_vap;
    mac_vap_stru                *pst_mac_sta;
    oal_uint8                    uc_vap_idx;

    /* 注意仅为了获取配置VAP */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->uc_cfg_vap_id);
    if(OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_reset_hw::Cannot find cfg_vap by vapID[%d],when devID[%d].}", pst_device->uc_cfg_vap_id, pst_device->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_device->en_reset_switch == OAL_FALSE)
    {
        //OAM_INFO_LOG0(0, OAM_SF_ANY, "{dmac_reset_hw::en_reset_switch is close.}");
        return OAL_SUCC;
    }

    pst_reset_para = (dmac_reset_para_stru*)pst_param;
    pst_hal_device = pst_device->pst_device_stru;

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_TOTAL_BEGIN);

    /* 设置复位处理中true */
    MAC_DEV_RESET_IN_PROGRESS(pst_device, OAL_TRUE);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_reset_sys.en_reset_sys_type = MAC_RESET_STATUS_SYS_TYPE;
    st_reset_sys.uc_value = pst_device->uc_device_reset_in_progress;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RESET_HW_OPERATE, OAL_SIZEOF(mac_reset_sys_stru), (oal_uint8 *)&st_reset_sys);
#endif

     /* 挂起硬件发送 */
    hal_set_machw_tx_suspend(pst_hal_device);

    /* 关闭pa */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    /* 关中断，在挂起硬件发送之后 */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DMSC);

    if (pst_reset_para->uc_reset_mac_reg)
    {
       /*保存LUT现场所需内存申请*/
       ul_ret = dmac_reset_lut_init();
       if(OAL_SUCC != ul_ret)
       {
            oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_hw::dmac_reset_lut_init return error[%d]}", ul_ret);
            return  ul_ret ;
       }

       /* 处理完接收事件队列 */
       frw_event_flush_event_queue(FRW_EVENT_TYPE_WLAN_CRX);
       frw_event_flush_event_queue(FRW_EVENT_TYPE_WLAN_DRX);

       /* 保存发送队列的内容 */
       dmac_reset_save_tx_queue(pst_hal_device);

       /*复位寄存器前操作,清发送队列，保存LUT内容*/
       dmac_tx_reset_flush(pst_hal_device);

       /*保存各VAP的TSF的值，并记录当前时间*/
       dmac_reset_save_tsf(pst_device,g_st_dmac_reset_mng.pst_tsf);
       oal_time_get_stamp_us(&st_time_record);
    }


    hal_reset_phy_machw(pst_hal_device,
                         pst_reset_para->uc_reset_type,
                         pst_reset_para->uc_reset_mac_mod,
                         pst_reset_para->uc_reset_phy_reg,
                         pst_reset_para->uc_reset_mac_reg);

    if ((HAL_RESET_HW_TYPE_ALL == pst_reset_para->uc_reset_type) ||(HAL_RESET_HW_TYPE_RF == pst_reset_para->uc_reset_type))
    {
        hal_reset_reg_restore(pst_hal_device, HAL_RESET_HW_TYPE_RF);

        for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
        {
          pst_mac_sta = mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
          if (OAL_PTR_NULL == pst_mac_sta)
          {
              oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);
              OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_tsf::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
              return OAL_ERR_CODE_PTR_NULL;
          }

          if (WLAN_VAP_MODE_BSS_STA == pst_mac_sta->en_vap_mode)
          {

              /* 调用hal接口设置信道号 */
              hal_set_primary_channel(pst_hal_device,
                                    pst_mac_sta->st_channel.uc_chan_number,
                                    pst_mac_sta->st_channel.en_band,
                                    pst_mac_sta->st_channel.uc_idx,
                                    pst_mac_sta->st_channel.en_bandwidth);
              break;
          }
        }

    }

    if(pst_reset_para->uc_reset_phy_reg)
    {
        hal_reset_reg_restore(pst_hal_device,HAL_RESET_HW_NORMAL_TYPE_PHY);
    }

    if(pst_reset_para->uc_reset_mac_reg)
    {
       /*复位寄存器后操作: 恢复寄存器和LUT*/
       hal_reset_reg_restore(pst_hal_device,HAL_RESET_HW_NORMAL_TYPE_MAC);

       /*避免复位过程中接收描述符队列异常，重新初始化接收描述符队列*/
       dmac_reset_rx_dscr_queue_flush(pst_hal_device);

       /* 恢复发送队列内容 */
       dmac_reset_restore_tx_queue(pst_hal_device);

       /*重写TSF*/
       dmac_reset_restore_tsf(pst_device,g_st_dmac_reset_mng.pst_tsf,&st_time_record);

       dmac_reset_lut_destroy();
    }


    /* 开中断 */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);

    /* 使能pa */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    /* 恢复硬件发送 */
    hal_set_machw_tx_resume(pst_hal_device);

    /* 设置复位处理中false */
    MAC_DEV_RESET_IN_PROGRESS(pst_device, OAL_FALSE);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_reset_sys.en_reset_sys_type = MAC_RESET_STATUS_SYS_TYPE;
    st_reset_sys.uc_value = pst_device->uc_device_reset_in_progress;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RESET_HW_OPERATE, OAL_SIZEOF(mac_reset_sys_stru), (oal_uint8 *)&st_reset_sys);
#endif

    pst_device->us_device_reset_num++;

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_TOTAL_END);

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_hw::current dmac reset num=%d.}", pst_device->us_device_reset_num);

    /*TBD:report reset event & reason to SDT*/

    OAM_WARNING_LOG4(0, OAM_SF_ANY, "{dmac_reset_hw::Here just performed a reset operation, reasen[%d], type[%d], phy_reg[%d], mac_reg[%d].}",
                         pst_reset_para->uc_reset_type,
                         pst_reset_para->en_reason,
                         pst_reset_para->uc_reset_phy_reg,
                         pst_reset_para->uc_reset_mac_reg);
#endif
    return ul_ret;
}
#else
/*****************************************************************************
 函 数 名  : dmac_reset_hw
 功能描述  : reset hw的入口
 输入参数  : uc_type:
                 0x01：复位mac
                 0x10：复位phy
                 0x11:  复位mac&phy
             sub_module:
                 当uc_type = 0x01,即复位MAC时：
                 0: 全部模块复位
                 1：复位PA模块
                 2：复位TSF模块
                 3：复位master模块
                 4：复位CCMP/TKIP模块
             uc_reset_reg:
                 是否复位寄存器：
                 0：不复位寄存器
                 1：复位寄存器
             uc_reason:
                 复位原因：
                 0：error复位
                 1：配置命令复位
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数
  2.日    期   : 2014年3月1日
    作    者   : zourong
    修改内容   : 复位MAC的寄存器，部分LUT受影响，部分LUT不受影响。
                 hi1151受复位影响的lut：
                    key lut，
                    peer addr lut，
                    matrix info lut，
                    smart antenna lut
                 不受复位影响的lut：
                    tx pn lut，
                    rx pn lut，
                    seq num lut，
                    dup det lut，
                    ba bitmap lut
   因此原来实现的PN LUT,SEQ LUT,BA LUT的保存与恢复动作在1151多余，通过全局管理变量中的
   bit位来区分。
*****************************************************************************/
oal_uint32  dmac_reset_hw(mac_device_stru* pst_device,oal_uint8* pst_param)
{
    oal_uint32                   ul_ret = OAL_SUCC;
    oal_uint32                   ul_sequence_nonqos = 0;
    hal_to_dmac_device_stru     *pst_hal_device;
    dmac_reset_para_stru        *pst_reset_para;
    oal_uint                     ul_irq_flag;
    oal_time_us_stru             st_time_record =  {0,0};
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_reset_sys_stru           st_reset_sys;
    mac_vap_stru                *pst_mac_vap;

    /* 注意仅为了获取配置VAP */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(0);
    if(OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_reset_hw::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif
    if (pst_device->en_reset_switch == OAL_FALSE)
    {
        return OAL_SUCC;
    }

    pst_reset_para = (dmac_reset_para_stru*)pst_param;

    pst_hal_device = pst_device->pst_device_stru;

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_TOTAL_BEGIN);

    /* 设置复位处理中true */
    MAC_DEV_RESET_IN_PROGRESS(pst_device, OAL_TRUE);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_reset_sys.en_reset_sys_type = MAC_RESET_STATUS_SYS_TYPE;
    st_reset_sys.uc_value = pst_device->uc_device_reset_in_progress;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RESET_HW_OPERATE, OAL_SIZEOF(mac_reset_sys_stru), (oal_uint8 *)&st_reset_sys);
#endif

     /* 挂起硬件发送 */
    hal_set_machw_tx_suspend(pst_hal_device);

    /* 关闭pa */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    /* 关中断，在挂起硬件发送之后 */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_DMSC);

    if (pst_reset_para->uc_reset_mac_reg)
    {
       /*保存LUT现场所需内存申请*/
       ul_ret = dmac_reset_lut_init();
       if(OAL_SUCC != ul_ret)
       {
            oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);
            return  ul_ret ;
       }

       /*复位寄存器前操作,清发送队列，保存LUT内容*/
       dmac_tx_reset_flush(pst_hal_device);

       dmac_reset_save_seq_lut(pst_device,g_st_dmac_reset_mng.pst_sequence_qos,&ul_sequence_nonqos);

       dmac_reset_save_ba_lut(pst_device,g_st_dmac_reset_mng.pst_ba_rx);

       dmac_reset_save_pn_lut(pst_device,g_st_dmac_reset_mng.pst_rx_pn_ucast,
                                        g_st_dmac_reset_mng.pst_rx_pn_mcast,
                                        g_st_dmac_reset_mng.pst_tx_pn_ucast,
                                        g_st_dmac_reset_mng.pst_tx_pn_mcast);

       dmac_reset_save_txbf_lut(pst_device,g_st_dmac_reset_mng.pst_txbf);

       /*保存各VAP的TSF的值，并记录当前时间*/
       dmac_reset_save_tsf(pst_device,g_st_dmac_reset_mng.pst_tsf);
       oal_time_get_stamp_us(&st_time_record);
    }

    hal_reset_phy_machw(pst_hal_device,
                         pst_reset_para->uc_reset_type,
                         pst_reset_para->uc_reset_mac_mod,
                         pst_reset_para->uc_reset_phy_reg,
                         pst_reset_para->uc_reset_mac_reg);

    if (pst_reset_para->uc_reset_rf_reg)
    {
        hal_reset_reg_restore(pst_hal_device, HAL_RESET_HW_TYPE_RF);
    }

    if(pst_reset_para->uc_reset_phy_reg)
    {
        hal_reset_reg_restore(pst_hal_device,HAL_RESET_HW_TYPE_PHY);
    }

    if(pst_reset_para->uc_reset_mac_reg)
    {
       /*复位寄存器后操作: 恢复寄存器和LUT*/
       hal_reset_reg_restore(pst_hal_device,HAL_RESET_HW_TYPE_MAC);

       /*避免复位过程中接收描述符队列异常，重新初始化接收描述符队列*/
       dmac_reset_rx_dscr_queue_flush(pst_hal_device);

       /*LUT表的恢复*//* TBD zhongwen 复位lut表需要在hal接口封装，不能再dmac，zourong */
       dmac_reset_restore_ba_lut(pst_device,g_st_dmac_reset_mng.pst_ba_rx);

       dmac_reset_restore_seq_lut(pst_device,g_st_dmac_reset_mng.pst_sequence_qos,&ul_sequence_nonqos);

       dmac_reset_restore_txbf_lut(pst_device,g_st_dmac_reset_mng.pst_txbf);

       dmac_reset_restore_cipher_lut(pst_device);

       /*因为重配置密钥硬件会自动重置PN，所以必须在重配置密钥后再恢复pn*/
       dmac_reset_restore_pn_lut(pst_device,
                                 g_st_dmac_reset_mng.pst_rx_pn_ucast,
                                 g_st_dmac_reset_mng.pst_rx_pn_mcast,
                                 g_st_dmac_reset_mng.pst_tx_pn_ucast,
                                 g_st_dmac_reset_mng.pst_tx_pn_mcast);

       dmac_reset_restore_peer_addr_lut(pst_device);

       /*重写TSF*/
       dmac_reset_restore_tsf(pst_device,g_st_dmac_reset_mng.pst_tsf,&st_time_record);

       dmac_reset_lut_destroy();
    }

    /* 开中断 */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_DMSC);

    /* 使能pa */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    /* 恢复硬件发送 */
    hal_set_machw_tx_resume(pst_hal_device);

    /* 设置复位处理中false */
    MAC_DEV_RESET_IN_PROGRESS(pst_device, OAL_FALSE);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    st_reset_sys.en_reset_sys_type = MAC_RESET_STATUS_SYS_TYPE;
    st_reset_sys.uc_value = pst_device->uc_device_reset_in_progress;
    dmac_send_sys_event(pst_mac_vap, WLAN_CFGID_RESET_HW_OPERATE, OAL_SIZEOF(mac_reset_sys_stru), (oal_uint8 *)&st_reset_sys);
#endif

    pst_device->us_device_reset_num++;

    OAM_PROFILING_STARTTIME_STATISTIC(OAM_PROFILING_RESET_TOTAL_END);

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_hw::current dmac reset num=%d.}", pst_device->us_device_reset_num);

    /*TBD:report reset event & reason to SDT*/

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_reset_save_seq_lut
 功能描述  : 保存sequnce lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_save_seq_lut(mac_device_stru* pst_mac_device,oal_uint32 *pst_qos_seq,oal_uint32 *pst_nonqos_seq)
{

    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;
    oal_dlist_head_stru *pst_entry;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;
    oal_uint8            uc_tid_loop;
    oal_uint32           *pst_reg_read;

    if(g_st_dmac_reset_mng.bit_seq_lut_reset)
    {
        /* 遍历device下所有用户，读寄存器，保存每个TID对应的sequence */
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_mac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_save_seq_lut::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user_tmp)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_reset_save_seq_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user_tmp->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* 非活跃用户，直接返回 */
                if (OAL_FALSE == pst_dmac_user_tmp->bit_active_user)
                {
                    continue;
                }

                if(pst_dmac_user_tmp->st_user_base_info.st_cap_info.bit_qos)
                {
                    for(uc_tid_loop = 0;uc_tid_loop<WLAN_TID_MAX_NUM;uc_tid_loop++)
                    {
                         pst_reg_read = pst_qos_seq + (pst_dmac_user_tmp->uc_lut_index)*WLAN_TID_MAX_NUM + uc_tid_loop;
                         hal_get_tx_sequence_num(pst_mac_device->pst_device_stru,
                                                pst_dmac_user_tmp->uc_lut_index,
                                                uc_tid_loop,
                                                1,
                                                pst_reg_read);
                     }
                }
            }
        }
    }
    /*non-qos,index和tid没有意义*/
    hal_get_tx_sequence_num(pst_mac_device->pst_device_stru,
                            0,
                            0,
                            0,
                            pst_nonqos_seq);


	return  OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_reset_restore_seq_lut
 功能描述  : 保存sequnce lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_seq_lut(mac_device_stru* pst_mac_device,oal_uint32 *pst_qos_seq,oal_uint32 *pst_nonqos_seq)
{

    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;
    oal_dlist_head_stru *pst_entry;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;
    oal_uint8            uc_tid_loop;
    oal_uint32           ul_reg_value;


    if(g_st_dmac_reset_mng.bit_seq_lut_reset)
    {
        /* 遍历device下所有用户，读寄存器，保存每个TID对应的sequence */
        /* 业务VAP从0开始*/
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_mac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_seq_lut::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user_tmp)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_reset_restore_seq_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user_tmp->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* 非活跃用户，直接返回 */
                if (OAL_FALSE == pst_dmac_user_tmp->bit_active_user)
                {
                    continue;
                }

                if(pst_dmac_user_tmp->st_user_base_info.st_cap_info.bit_qos)
                {
                    for(uc_tid_loop = 0;uc_tid_loop<WLAN_TID_MAX_NUM;uc_tid_loop++)
                    {
                         ul_reg_value = *(pst_qos_seq + (pst_dmac_user_tmp->uc_lut_index)*WLAN_TID_MAX_NUM + uc_tid_loop);
                         hal_set_tx_sequence_num(pst_mac_device->pst_device_stru,
                                                pst_dmac_user_tmp->uc_lut_index,
                                                uc_tid_loop,
                                                1,
                                                ul_reg_value);
                     }
                }

            }
        }
    }

    /*non-qos,index和tid没有意义*/
    hal_set_tx_sequence_num(pst_mac_device->pst_device_stru,
                            0,
                            0,
                            0,
                            *(pst_nonqos_seq));

	return  OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_reset_save_ba_lut
 功能描述  : 保存ba lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_save_ba_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_ba_lut)
{

    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;

    if(g_st_dmac_reset_mng.bit_ba_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop=0;uc_index_loop < WLAN_MAX_RX_BA;uc_index_loop++)
        {
            pst_current_entry = pst_ba_lut + uc_index_loop*WLAN_BA_LUT_ENTRY_SIZE;
            hal_get_machw_ba_params(pst_hal_device,
                                    uc_index_loop,
                                    pst_current_entry,
                                    pst_current_entry + 1,
                                    pst_current_entry + 2);
        }
    }

    return  OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_reset_restore_ba_lut
 功能描述  : restore ba lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_ba_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_ba_lut)
{
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;


    if(g_st_dmac_reset_mng.bit_ba_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop = 0; uc_index_loop < WLAN_MAX_RX_BA; uc_index_loop++)
        {
            pst_current_entry = pst_ba_lut + uc_index_loop*WLAN_BA_LUT_ENTRY_SIZE;
            hal_restore_machw_ba_params(pst_hal_device,
                                        uc_index_loop,
                                        *(pst_current_entry),
                                        *(pst_current_entry + 1),
                                        *(pst_current_entry + 2));
        }
    }

    return  OAL_SUCC;

}


/*****************************************************************************
 函 数 名  : dmac_reset_save_pn_lut
 功能描述  : 保存ba lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_save_pn_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_rx_pn_ucast,oal_uint32* pst_rx_pn_mcast,
                                                      oal_uint32* pst_tx_pn_ucast,oal_uint32* pst_tx_pn_mcast)
{

    hal_pn_lut_cfg_stru      st_pn_lut_cfg;
    oal_uint32              *pst_curr_entry;
    oal_uint8                uc_vap_idx;
    dmac_vap_stru            *pst_dmac_vap;
    oal_dlist_head_stru     *pst_entry;
    mac_user_stru           *pst_user_tmp;
    dmac_user_stru          *pst_dmac_user_tmp;
    oal_uint8                uc_tid_loop;

    if(g_st_dmac_reset_mng.bit_pn_lut_reset)
    {
        /* 遍历device下所有用户，读寄存器，保存单播PN LUT */
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_dmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_save_pn_lut::pst_dmac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_dmac_vap->st_vap_base_info.st_mac_user_list_head))
            {
                pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user_tmp)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_reset_save_pn_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user_tmp->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }

                /* 非活跃用户，直接返回 */
                if (OAL_FALSE == pst_dmac_user_tmp->bit_active_user)
                {
                    continue;
                }

                {
                 /* 单播tx pn */
                 st_pn_lut_cfg.uc_pn_key_type = 1;
                 st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_user_tmp->uc_lut_index;
                 hal_get_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);


                 /*保存读取到DBB mac的值*/
                 pst_curr_entry         = pst_tx_pn_ucast + (pst_dmac_user_tmp->uc_lut_index)*2;
                *pst_curr_entry         = st_pn_lut_cfg.ul_pn_msb;
                *(pst_curr_entry + 1)   = st_pn_lut_cfg.ul_pn_lsb;
                }

                /* 单播rx pn */
                for(uc_tid_loop = 0; uc_tid_loop < WLAN_TID_MAX_NUM; uc_tid_loop++)
                {
                     st_pn_lut_cfg.uc_pn_key_type = 1;
                     st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_user_tmp->uc_lut_index;
                     st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
                     hal_get_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

                     /*保存读取到DBB mac的值*/
                     pst_curr_entry         = pst_rx_pn_ucast + ((pst_dmac_user_tmp->uc_lut_index)*WLAN_TID_MAX_NUM + uc_tid_loop)*2;
                    *pst_curr_entry         = st_pn_lut_cfg.ul_pn_msb;
                    *(pst_curr_entry + 1)   = st_pn_lut_cfg.ul_pn_lsb;
                }
            }

        }

        /*组播 rx pn*/
        for(uc_vap_idx = 0; uc_vap_idx < WLAN_ASSOC_AP_MAX_NUM; uc_vap_idx++)
        {
            for(uc_tid_loop = 0;uc_tid_loop < WLAN_TID_MAX_NUM;uc_tid_loop++)
            {
                 st_pn_lut_cfg.uc_pn_key_type = 0;
                 st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
                 st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
                 hal_get_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

                 /*保存读取到DBB mac的值*/
                 pst_curr_entry         = pst_rx_pn_mcast + (uc_vap_idx*WLAN_TID_MAX_NUM + uc_tid_loop)*2;
                *pst_curr_entry         = st_pn_lut_cfg.ul_pn_msb;
                *(pst_curr_entry + 1)   = st_pn_lut_cfg.ul_pn_lsb;
            }
        }

        /*组播 Tx pn*/
        for(uc_vap_idx = 0; uc_vap_idx < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_vap_idx++)
        {
             st_pn_lut_cfg.uc_pn_key_type = 0;
             st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
             hal_get_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

             /*保存读取到DBB mac的值*/
             pst_curr_entry         = pst_tx_pn_mcast + uc_vap_idx*2;
            *pst_curr_entry         = st_pn_lut_cfg.ul_pn_msb;
            *(pst_curr_entry + 1)   = st_pn_lut_cfg.ul_pn_lsb;
        }
    }

    return  OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_reset_restore_pn_lut
 功能描述  : restore ba lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_pn_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_rx_pn_ucast,oal_uint32* pst_rx_pn_mcast,
                                                      oal_uint32* pst_tx_pn_ucast,oal_uint32* pst_tx_pn_mcast)
{
    hal_pn_lut_cfg_stru      st_pn_lut_cfg;
    oal_uint32              *pst_curr_entry;
    oal_uint8                uc_vap_idx;
    dmac_vap_stru            *pst_dmac_vap;
    oal_dlist_head_stru     *pst_entry;
    mac_user_stru           *pst_user_tmp;
    dmac_user_stru          *pst_dmac_user_tmp;
    oal_uint8                uc_tid_loop;


    if(g_st_dmac_reset_mng.bit_pn_lut_reset)
    {
        /* 遍历device下所有VAP的活跃用户，恢复单播PN lut*/
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_dmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_pn_lut::pst_dmac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_dmac_vap->st_vap_base_info.st_mac_user_list_head))
            {
                pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user_tmp)
                {
                    OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_reset_restore_pn_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user_tmp->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* 非活跃用户，直接返回 */
                if (OAL_FALSE == pst_dmac_user_tmp->bit_active_user)
                {
                    continue;
                }

                {
                    /* 单播tx pn */
                     pst_curr_entry               = pst_tx_pn_ucast + (pst_dmac_user_tmp->uc_lut_index)*2;
                     st_pn_lut_cfg.uc_pn_key_type = 1;
                     st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_user_tmp->uc_lut_index;
                     st_pn_lut_cfg.ul_pn_msb      = *pst_curr_entry;
                     st_pn_lut_cfg.ul_pn_lsb      = *(pst_curr_entry + 1);

                     hal_set_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);
                }

                /* 单播rx pn */
                for(uc_tid_loop = 0;uc_tid_loop < WLAN_TID_MAX_NUM;uc_tid_loop++)
                {
                     pst_curr_entry               = pst_rx_pn_ucast + ((pst_dmac_user_tmp->uc_lut_index)*WLAN_TID_MAX_NUM + uc_tid_loop)*2;
                     st_pn_lut_cfg.uc_pn_key_type = 1;
                     st_pn_lut_cfg.uc_pn_peer_idx = pst_dmac_user_tmp->uc_lut_index;
                     st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
                     st_pn_lut_cfg.ul_pn_msb      = *pst_curr_entry ;
                     st_pn_lut_cfg.ul_pn_lsb      = *(pst_curr_entry + 1);

                     hal_set_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

                }

            }

        }

        /*组播 rx pn*/
        for(uc_vap_idx = 0; uc_vap_idx < WLAN_ASSOC_AP_MAX_NUM; uc_vap_idx++)
        {
            for(uc_tid_loop = 0;uc_tid_loop < WLAN_TID_MAX_NUM;uc_tid_loop++)
            {
                 pst_curr_entry               = pst_rx_pn_mcast + (uc_vap_idx*WLAN_TID_MAX_NUM + uc_tid_loop)*2;
                 st_pn_lut_cfg.uc_pn_key_type = 0;
                 st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
                 st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
                 st_pn_lut_cfg.ul_pn_msb      = *pst_curr_entry;
                 st_pn_lut_cfg.ul_pn_lsb      = *(pst_curr_entry + 1);

                 hal_set_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

            }
        }

        /*组播 Tx pn*/
        for(uc_vap_idx = 0; uc_vap_idx < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_vap_idx++)
        {
             pst_curr_entry               = pst_tx_pn_mcast + uc_vap_idx*2;
             st_pn_lut_cfg.uc_pn_key_type = 0;
             st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
             st_pn_lut_cfg.ul_pn_msb      = *pst_curr_entry;
             st_pn_lut_cfg.ul_pn_lsb      = *(pst_curr_entry + 1);

             hal_set_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

        }
    }

    return  OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_reset_restore_cipher_lut
 功能描述  : restore 加密 lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_cipher_lut(mac_device_stru* pst_mac_device)
{
    oal_uint8                            uc_vap_idx;
    dmac_vap_stru                       *pst_dmac_vap;
    mac_vap_stru                        *pst_mac_vap;
    oal_dlist_head_stru                 *pst_entry;
    mac_user_stru                       *pst_user;
    dmac_user_stru                      *pst_dmac_user;
    oal_uint8                            uc_key_idx;
    mac_user_stru                       *pst_multi_user;

    if(g_st_dmac_reset_mng.bit_key_lut_reset)
    {
        /* 遍历device下所有用户，读寄存器，保存每个TID对应的sequence */
        /* 业务VAP从1开始*/
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_dmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_cipher_lut::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }
            pst_mac_vap = &pst_dmac_vap->st_vap_base_info;
            /*不加密模式跳过*/
            pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_multi_user))
            {
                OAM_ERROR_LOG1(0, OAM_SF_DBAC, "{dmac_reset_restore_cipher_lut::pst_mac_user[%d] is NULL!}", pst_mac_vap->us_multi_user_idx);
                continue;
            }
            if(WLAN_80211_CIPHER_SUITE_NO_ENCRYP == pst_multi_user->st_key_info.en_cipher_type)
            {
                continue;
            }

            /*wep key恢复*/
            if(OAL_TRUE == mac_is_wep_allowed(pst_mac_vap))
            {
                uc_key_idx = mac_get_wep_default_keyid(pst_mac_vap);
                dmac_11i_add_wep_key(pst_mac_vap,uc_key_idx);
            }

            /*GTK恢复*/
            uc_key_idx = pst_multi_user->st_key_info.uc_default_index;
            dmac_11i_add_gtk_key(pst_mac_vap, uc_key_idx);

            /*PTK恢复*/
            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user = mac_res_get_dmac_user(pst_user->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_reset_restore_cipher_lut::pst_dmac_user null, assoc id=%d.", pst_user->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* 非活跃用户，直接返回 */
                if (OAL_FALSE == pst_dmac_user->bit_active_user)
                {
                    continue;
                }

                uc_key_idx = pst_user->st_key_info.uc_default_index;
                dmac_11i_add_ptk_key(pst_mac_vap, pst_dmac_user->st_user_base_info.auc_user_mac_addr, uc_key_idx);
             }

        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_reset_save_txbf_lut
 功能描述  : 保存ba lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_save_txbf_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_txbf_lut)
{
#ifdef _PRE_WLAN_FEATURE_TXBF
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;

    if(g_st_dmac_reset_mng.bit_txbf_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop=0;uc_index_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_index_loop++)
        {
            pst_current_entry = pst_txbf_lut + uc_index_loop;
            hal_get_txbf_lut_info(pst_hal_device,uc_index_loop,pst_current_entry);
        }
    }
 #endif
    return  OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_reset_restore_txbf_lut
 功能描述  : 保存ba lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_txbf_lut(mac_device_stru* pst_mac_device,oal_uint32* pst_txbf_lut)
{
#ifdef _PRE_WLAN_FEATURE_TXBF
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32              *pst_current_entry;

    if(g_st_dmac_reset_mng.bit_txbf_lut_reset)
    {
        pst_hal_device = pst_mac_device->pst_device_stru;
        for(uc_index_loop=0;uc_index_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_index_loop++)
        {
            pst_current_entry = pst_txbf_lut + uc_index_loop;
            hal_set_txbf_lut_info(pst_hal_device,uc_index_loop,*pst_current_entry);
        }
    }
#endif
    return  OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_reset_restore_peer_addr_lut
 功能描述  : restore ba lut的值
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_reset_restore_peer_addr_lut(mac_device_stru* pst_mac_device)
{
    oal_uint8                            uc_vap_idx;
    dmac_vap_stru                       *pst_dmac_vap;
    mac_vap_stru                        *pst_mac_vap;
    oal_dlist_head_stru                 *pst_entry;
    mac_user_stru                       *pst_user;
    dmac_user_stru                      *pst_dmac_user;


    if(g_st_dmac_reset_mng.bit_peer_addr_lut_reset)
    {
        /* 遍历device下所有用户， */
        for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
            if (OAL_PTR_NULL == pst_dmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_peer_addr_lut::pst_dmac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
                return OAL_ERR_CODE_PTR_NULL;
            }
            pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

            OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
            {
                pst_user      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
                pst_dmac_user = mac_res_get_dmac_user(pst_user->us_assoc_id);
                if (OAL_PTR_NULL == pst_dmac_user)
                {
                    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_reset_restore_peer_addr_lut::pst_dmac_user_tmp null, assoc_id id=%d.", pst_user->us_assoc_id);
                    return OAL_ERR_CODE_PTR_NULL;
                }
                /* 非活跃用户，直接返回 */
                if (OAL_FALSE == pst_dmac_user->bit_active_user)
                {
                    continue;
                }


               hal_ce_add_peer_macaddr(pst_mac_device->pst_device_stru,pst_dmac_user->uc_lut_index,pst_dmac_user->st_user_base_info.auc_user_mac_addr);

             }
        }
    }

    return OAL_SUCC;

}

#endif

/*****************************************************************************
 函 数 名  : dmac_reset_rx_dscr_queue_flush
 功能描述  : 复位后销毁接收描述符队列并重新初始化接收描述符队列
 输入参数  : uc_type:
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_reset_rx_dscr_queue_flush(hal_to_dmac_device_stru* pst_hal)
{
    hal_rx_destroy_dscr_queue(pst_hal,OAL_TRUE);
    hal_rx_init_dscr_queue(pst_hal,OAL_TRUE);
}

/*****************************************************************************
 函 数 名  : dmac_reset_save_tsf
 功能描述  : 读取并保存每个业务VAP的time stamp的值
 输入参数  : 记录timestamp的指针
 输出参数  :
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
OAL_STATIC oal_void dmac_reset_save_tsf(mac_device_stru* pst_mac_device,oal_uint32* pst_tsf_array)
{
    oal_uint8                uc_vap_idx;
    dmac_vap_stru           *pst_dmac_vap;
    oal_uint32              *pst_tsf_entry;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_save_tsf::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
            return ;
        }
        /*每个timestamp 64位，占用数组的2个条目*/
        pst_tsf_entry = pst_tsf_array + uc_vap_idx*2;

        hal_vap_tsf_get_64bit(pst_dmac_vap->pst_hal_vap, pst_tsf_entry, pst_tsf_entry + 1);

    }
}

/*****************************************************************************
 函 数 名  : dmac_reset_restore_tsf
 功能描述  : 重新写每个业务VAP的time stamp的寄存器
 输入参数  : 记录timestamp的指针
             保存timstamp时的时间戳
 输出参数  :
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_reset_restore_tsf(mac_device_stru* pst_mac_device,oal_uint32* pst_tsf_array,oal_time_us_stru *pst_time_record)
{
    oal_uint8                uc_vap_idx;
    dmac_vap_stru           *pst_dmac_vap;
    oal_uint32              *pst_tsf_entry;
    oal_time_us_stru         st_now_time;
    oal_uint32               ul_diff_time_us;
    oal_uint32               ul_tsf_hi;
    oal_uint32               ul_tsf_lo;
    oal_uint32               ul_tsf_lo_plus;

    /*当前时间*/
    oal_time_get_stamp_us(&st_now_time);

    /*计算时差*/
    ul_diff_time_us = (oal_uint32)DMAC_TIME_USEC_DIFF(pst_time_record, &st_now_time);

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_reset_restore_tsf::pst_mac_vap null, vap id=%d.", pst_mac_device->auc_vap_id[uc_vap_idx]);
            return ;
        }
        /*每个timestamp 64位，占用数组的2个条目*/
        pst_tsf_entry = pst_tsf_array + uc_vap_idx*2;
        ul_tsf_hi     = *pst_tsf_entry;
        ul_tsf_lo     = *(pst_tsf_entry + 1);

        /*加上差值*/
        ul_tsf_lo_plus = ul_tsf_lo + ul_diff_time_us;
        if((ul_tsf_lo_plus < ul_tsf_lo )|| (ul_tsf_lo_plus < ul_diff_time_us))
        {
            ul_tsf_hi++ ;
            //OAM_INFO_LOG1(0, OAM_SF_ANY, "tsf ul_tsf_hi = %d\n",ul_tsf_hi);
        }

        hal_vap_tsf_set_64bit(pst_dmac_vap->pst_hal_vap, ul_tsf_hi, ul_tsf_lo_plus);
    }
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_reset_sys_event
 功能描述  : host进行复位时，同步device事件处理
 输入参数  : pst_event_mem事件
 输出参数  : 无
 返 回 值  : OAL_SUCC | OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : zhangyu 00241943
    修改内容   : 新生成函数
*****************************************************************************/
oal_uint32 dmac_reset_sys_event(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_device_stru     *pst_mac_dev;
    mac_reset_sys_stru  *pst_reset_sys;

    pst_reset_sys = (mac_reset_sys_stru *)puc_param;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_reset_sys_event::pst_mac_dev null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    switch(pst_reset_sys->en_reset_sys_type)
    {
        case MAC_RESET_STATUS_SYS_TYPE:
            /* 下发复位 */
            break;
        case MAC_RESET_SWITCH_SYS_TYPE:
            pst_mac_dev->en_reset_switch = pst_reset_sys->uc_value;

            break;
        default:
            break;
    }

    return OAL_SUCC;
}
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
/*****************************************************************************
 函 数 名  : dmac_reset_debug_sequence_lut
 功能描述  : 读取硬件的LUT表，显示
 输入参数  :

 输出参数  :
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_reset_debug_sequence_lut(mac_device_stru* pst_device)
{

    oal_uint32           ul_reg_read;
    oal_uint8            uc_user_loop;
    oal_uint8            uc_tid_loop;
    oal_file             *pst_fs = OAL_PTR_NULL;

    dmac_reset_debug_init();
    pst_fs = g_st_dmac_reset_mng.pst_debug_file;

    oal_kernel_file_print(pst_fs,"------------------------sequence_lut--------------------------\n");
    for(uc_user_loop = 0;uc_user_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_user_loop++ )
    {
        for(uc_tid_loop = 0;uc_tid_loop<WLAN_TID_MAX_NUM;uc_tid_loop++)
        {
            hal_get_tx_sequence_num(pst_device->pst_device_stru,
                                    uc_user_loop,
                                    uc_tid_loop,
                                    1,
                                    &ul_reg_read);
           oal_kernel_file_print(pst_fs,"user lut index = %d, tid index = %d, sequence = %d\n",uc_user_loop,uc_tid_loop,ul_reg_read);
         }
    }

    dmac_reset_debug_close();

}

/*****************************************************************************
 函 数 名  : dmac_reset_debug_ba_lut
 功能描述  : 读取硬件的LUT表，显示
 输入参数  :

 输出参数  :
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_reset_debug_ba_lut(mac_device_stru* pst_mac_device)
{
    oal_uint8                uc_index_loop;
    hal_to_dmac_device_stru *pst_hal_device;
    oal_uint32               ul_addr_h;
    oal_uint32               ul_addr_l;
    oal_uint32               ul_ba_para;
    oal_uint32               ul_tid ;
    oal_uint32               ul_winstart ;
    oal_uint32               ul_winsize ;
    oal_file                *pst_fs = OAL_PTR_NULL;

    dmac_reset_debug_init();
    pst_fs = g_st_dmac_reset_mng.pst_debug_file;

    oal_kernel_file_print(pst_fs,"------------------------ba_lut--------------------------\n");

    pst_hal_device = pst_mac_device->pst_device_stru;
    for(uc_index_loop=0;uc_index_loop < WLAN_MAX_RX_BA;uc_index_loop++)
    {
        hal_get_machw_ba_params(pst_hal_device,
                                uc_index_loop,
                                &ul_addr_h,
                                &ul_addr_l,
                                &ul_ba_para);

        ul_tid      = (ul_ba_para&0x0000000f);
        ul_winstart = (ul_ba_para&0x000000f0)>>4;
        ul_winsize  = (ul_ba_para&0x00003f00)>>8;
        oal_kernel_file_print(pst_fs," addr hi = %x,addr lo = %x,param = %d,TID = %d, winstart = %d,winsize = %d\n",
                            ul_addr_h, ul_addr_l,ul_ba_para,ul_tid,
                            ul_winstart,ul_winsize);
    }

    dmac_reset_debug_close();
 }

/*****************************************************************************
 函 数 名  : dmac_reset_debug_ba_lut
 功能描述  : 读取硬件的LUT表，显示
 输入参数  :

 输出参数  :
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_reset_debug_pn_lut(mac_device_stru* pst_mac_device)
{
    oal_uint8                uc_user_loop;
    oal_uint8                uc_tid_loop;
    oal_uint8                uc_vap_idx;
    hal_pn_lut_cfg_stru      st_pn_lut_cfg;
    oal_file                *pst_fs = OAL_PTR_NULL;

    dmac_reset_debug_init();
    pst_fs = g_st_dmac_reset_mng.pst_debug_file;

    oal_kernel_file_print(pst_fs,"------------------------rx_pn_ucast lut--------------------------\n");
    for(uc_user_loop = 0;uc_user_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_user_loop++ )
    {
        for(uc_tid_loop = 0;uc_tid_loop<WLAN_TID_MAX_NUM;uc_tid_loop++)
        {
            st_pn_lut_cfg.uc_pn_key_type = 1;
            st_pn_lut_cfg.uc_pn_peer_idx = uc_user_loop;
            st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
            hal_get_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

           oal_kernel_file_print(pst_fs,"user lut index = %d, tid index = %d, ul_pn_msb = %d,ul_pn_lsb = %d\n",
                        uc_user_loop,uc_tid_loop,st_pn_lut_cfg.ul_pn_msb,st_pn_lut_cfg.ul_pn_lsb);

         }
    }


    oal_kernel_file_print(pst_fs,"------------------------rx_pn_mcast lut--------------------------\n");
    for(uc_vap_idx = 0; uc_vap_idx < WLAN_ASSOC_AP_MAX_NUM; uc_vap_idx++)
    {
        for(uc_tid_loop = 0;uc_tid_loop < WLAN_TID_MAX_NUM;uc_tid_loop++)
        {
             st_pn_lut_cfg.uc_pn_key_type = 0;
             st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
             st_pn_lut_cfg.uc_pn_tid      = uc_tid_loop;
             hal_get_rx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

             oal_kernel_file_print(pst_fs,"uc_pn_peer_idx index = %d, tid index = %d, ul_pn_msb = %d,ul_pn_lsb = %d\n",
                        uc_vap_idx,uc_tid_loop,st_pn_lut_cfg.ul_pn_msb,st_pn_lut_cfg.ul_pn_lsb);
        }
    }


    oal_kernel_file_print(pst_fs,"------------------------tx_pn_ucast lut--------------------------\n");
    for(uc_user_loop = 0;uc_user_loop < WLAN_ACTIVE_USER_MAX_NUM;uc_user_loop++ )
    {
        st_pn_lut_cfg.uc_pn_key_type = 1;
        st_pn_lut_cfg.uc_pn_peer_idx = uc_user_loop;
        hal_get_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

        oal_kernel_file_print(pst_fs,"user lut index = %d, tid index = %d, ul_pn_msb = %d,ul_pn_lsb = %d\n",
                    uc_user_loop,uc_tid_loop,st_pn_lut_cfg.ul_pn_msb,st_pn_lut_cfg.ul_pn_lsb);
    }


    oal_kernel_file_print(pst_fs,"------------------------tx_pn_mcast lut--------------------------\n");
    for(uc_vap_idx = 0; uc_vap_idx < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_vap_idx++)
    {
         st_pn_lut_cfg.uc_pn_key_type = 0;
         st_pn_lut_cfg.uc_pn_peer_idx = uc_vap_idx;
         hal_get_tx_pn(pst_mac_device->pst_device_stru,&st_pn_lut_cfg);

         oal_kernel_file_print(pst_fs,"uc_pn_peer_idx index = %d, ul_pn_msb = %d,ul_pn_lsb = %d\n",
                      uc_vap_idx,st_pn_lut_cfg.ul_pn_msb,st_pn_lut_cfg.ul_pn_lsb);

    }

    dmac_reset_debug_close();
}


/*****************************************************************************
 函 数 名  : dmac_reset_debug_init
 功能描述  : reset维测使用，维测时一开始调用本函数，打开一个文件，扩展内核空间到用户空间
 输入参数  : 无:
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

oal_void dmac_reset_debug_init(oal_void)
{

    g_st_dmac_reset_mng.pst_debug_file = oal_kernel_file_open(DMAC_RESET_DUMP_LUT_PATH,OAL_O_RDWR|OAL_O_CREAT|OAL_O_APPEND);
    if(g_st_dmac_reset_mng.pst_debug_file)
    {
        g_st_dmac_reset_mng.old_fs = oal_get_fs();
        oal_set_fs(OAL_KERNEL_DS);                  //扩展内核空间到用户空间
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "open file fail\n");
    }

    return;
}

/*****************************************************************************
 函 数 名  : dmac_reset_debug_close
 功能描述  : reset维测使用，维测结束时调用本函数，关闭打开的文件，恢复到内核空间
 输入参数  : 无:
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/

oal_void dmac_reset_debug_close(oal_void)
{
    oal_kernel_file_close(g_st_dmac_reset_mng.pst_debug_file);
    oal_set_fs(g_st_dmac_reset_mng.old_fs);  //恢复内核空间
}

/*****************************************************************************
 函 数 名  : dmac_reset_debug_close
 功能描述  : reset维测使用，将字符串写到打开的文件
 输入参数  : pst_str: 字符串
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_reset_debug_to_file(oal_uint8 *pst_str)
{
    oal_kernel_file_write(g_st_dmac_reset_mng.pst_debug_file,pst_str,OAL_STRLEN(pst_str));
}

/*****************************************************************************
 函 数 名  : dmac_reset_debug_all
 功能描述  : 读取硬件的LUT表，显示
             读取所有的寄存器，显示
 输入参数  :

 输出参数  :
 返 回 值  : OAL_SUCC | OAL_FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月6日
    作    者   : zourong
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_reset_debug_all(mac_device_stru* pst_device,dmac_reset_para_stru* pst_debug_para)
{

    /* debug显示lut表和寄存器:hipriv "Hisilicon0 reset_hw 3(debug) 0|1|2(all|mac reg|phy reg|lut) "*/

    if(pst_debug_para->uc_debug_type == 0)
    {
        /*输出所有的*/
        hal_reset_reg_restore(pst_device->pst_device_stru,HAL_RESET_HW_TYPE_DUMP_MAC);
        hal_reset_reg_restore(pst_device->pst_device_stru,HAL_RESET_HW_TYPE_DUMP_PHY);
        dmac_reset_debug_sequence_lut(pst_device);
        dmac_reset_debug_ba_lut(pst_device);
        dmac_reset_debug_pn_lut(pst_device);

    }
    else if(pst_debug_para->uc_debug_type == 1)
    {
         /*输出mac寄存器*/
       hal_reset_reg_restore(pst_device->pst_device_stru,HAL_RESET_HW_TYPE_DUMP_MAC);

    }
    else if(pst_debug_para->uc_debug_type == 2)
    {
        /*输出phy指定bank的reg*/
        hal_reset_reg_restore(pst_device->pst_device_stru,HAL_RESET_HW_TYPE_DUMP_PHY);
    }
    else if(pst_debug_para->uc_debug_type == 3)
    {
        dmac_reset_debug_sequence_lut(pst_device);
        dmac_reset_debug_ba_lut(pst_device);
        dmac_reset_debug_pn_lut(pst_device);
    }

}

#else /*win32*/
oal_void dmac_reset_debug_all(mac_device_stru* pst_device,dmac_reset_para_stru* pst_debug_para)
{
    return;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

