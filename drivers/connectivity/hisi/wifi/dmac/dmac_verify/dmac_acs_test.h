/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_acs_test.h
  版 本 号   : 初稿
  作    者   : 王山博
  生成日期   : 2014年4月21日
  最近修改   :
  功能描述   : dmac_acs_test.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月21日
    作    者   : w00196298
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_ACS_TEST_H__
#define __DMAC_ACS_TEST_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "dmac_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ACS_TEST_H

#if  defined(_PRE_WLAN_CHIP_TEST)  && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define ACS_CREATE_PROC_ENTRY           create_proc_entry
#define ACS_REMOVE_PROC_ENTRY           remove_proc_entry
#define ACS_VERIFY_PROC_NAME            "acs_meas_result"

#define ACS_SUMMARY_TEST_MODE           0
#define ACS_STATS_TEST_MODE             1
#define ACS_TX_TIME_TEST_MODE           2
#define ACS_READ_REG_MODE               3

#define ACS_SHOW_HW_INFO(title, member)                 \
        do{                                             \
        seq_printf(f, title);                           \
        for (ul_idx = 0; ul_idx < ul_cycles; ul_idx++)  \
        {                                               \
            if (ul_idx && ((ul_idx % 16) == 0))                \
            {                                                   \
                seq_printf(f, "\n");                            \
            }                                                   \
            seq_printf(f, "%-6d", pst_hw_vi->member[ul_idx]);   \
        }                                                     \
        seq_printf(f, "\n");                                  \
        }while(0)

#define ACS_HW_INFO_CLEAR(buffer)       \
                do{                                 \
                    if (OAL_PTR_NULL != buffer)     \
                    {\
                        OAL_MEM_FREE(buffer, OAL_TRUE);\
                        buffer = OAL_PTR_NULL;          \
                    }\
                }while(0)

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

typedef struct
{
    /* 信道统计 */
    oal_uint32  ul_pri20_free_time_us;
    oal_uint32  ul_pri40_free_time_us;
    oal_uint32  ul_pri80_free_time_us;
    oal_uint32  ul_ch_rx_time_us;
    oal_uint32  ul_ch_tx_time_us;

    /* 信道测量 */
    oal_int32   l_pri20_idle_power;
    oal_int32   l_pri40_idle_power;
    oal_int32   l_pri80_idle_power;

    /* 统计计数 */
    oal_uint32 aul_stats_cnt[3];
    oal_uint32 aul_meas_cnt[3];
    oal_uint32 ul_test_cnt;
}acs_hw_statics_stru;

typedef struct
{
    acs_hw_statics_stru             st_acs_stats_result;
    oal_int32                      *pul_20m_freetime;
    oal_int32                      *pul_40m_freetime;
    oal_int32                      *pul_80m_freetime;
    oal_int32                      *pul_20m_freepwr;
    oal_int32                      *pul_40m_freepwr;
    oal_int32                      *pul_80m_freepwr;
    oal_uint32                      ul_curr_idx;
    oal_uint32                      ul_cycles;
    oal_uint32                      ul_cycles_backup;
    oal_uint32                      ul_test_running;
    oal_uint32                      ul_test_mode;
    oal_uint32                      ul_reg_data;
}acs_hw_verify_stru;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void  dmac_acs_verify_init(oal_void);
extern oal_void  dmac_acs_verify_exit(oal_void);
extern oal_void  dmac_acs_channel_meas_comp_handler(mac_device_stru *pst_mac_dev, hal_ch_statics_irq_event_stru *pst_mac_stats_result);

#endif /* _PRE_WLAN_CHIP_TEST */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __DMAC_ACS_TEST_H__ */
