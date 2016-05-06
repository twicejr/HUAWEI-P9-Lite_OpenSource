/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_test_main.h
  版 本 号   : 初稿
  作    者   : 邹嵘
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : dmac_chip_test.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : z52447
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_TEST_MAIN_H__
#define __DMAC_TEST_MAIN_H__

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
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TEST_MAIN_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/
typedef oal_uint32 (* dmac_test_encap_frame)(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len);

/* 用于芯片验证调用前，检查开关 */
#ifdef _PRE_WLAN_CHIP_TEST
#define DMAC_CHIP_TEST_CALL(func_call) do{\
    if(0 != dmac_test_get_chip_test())\
    {\
        (func_call);\
    }\
}while(0);
#else
#define DMAC_CHIP_TEST_CALL(func_call)
#endif


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
typedef struct dmac_lpm_txopps_tx_stub
{
    oal_uint8                       uc_stub_on;            /*0:off, 1:on*/
    oal_uint8                       auc_rsv[1];
    oal_uint16                      us_partial_aid_real;     /*真实的Partial AID*/
    oal_uint16                      us_begin_num;            /* 第n个报文打桩 */
    oal_uint16                      us_curr_num;             /* 当前是第几个包 */
}dmac_lpm_txopps_tx_stub_stru;

typedef struct dmac_lpm_smps_tx_stub
{
    oal_uint8                       uc_stub_type;            /*0:off, 1:单流,2:双流*/
    oal_uint8                       uc_rts_en;             /* 第一个包是否发RTS */
    oal_uint8                       auc_rsv[2];
    oal_uint32                      ul_rate_real[HAL_TX_RATE_MAX_NUM];         /*真实的速率*/
}dmac_lpm_smps_tx_stub_stru;

/*****************************************************************************
结构说明:以下为测试的主管理结构，用于统一管理所有测试中用到的各种控制开关，各测试特性自行
根据需要在其中添加子结构成员或者是变量
*****************************************************************************/
typedef struct dmac_test_mng
{
   dmac_lpm_txopps_tx_stub_stru 
st_lpm_txop_stub;    /*TXOP PS测试开关和桩使能条件*/
   dmac_lpm_smps_tx_stub_stru    st_lpm_smps_stub;    /*SMPS 打桩使能和条件*/
   oal_uint32                    ul_wow_int_cnt;      /*wow唤醒中断次数*/
   oal_uint8                     uc_wow_en;           /*wow测试使能*/
   oal_uint8                     uc_txop_ps_en;       /*txopps 测试使能*/
   oal_uint8                     us_txop_rx_cnt;      /*txopps 测试中接收到的测试报文个数*/

   frw_timeout_stru              st_sleep_timer;      /* 软件寄存器睡眠定时器 */

   /* 用于帧过滤特性，组帧 */
   dmac_test_encap_frame  ast_dmac_encap_frame[MAC_TEST_MAX_TYPE_NUM];
   oal_uint8              uc_software_retry;
   oal_uint8              uc_retry_test;
   /* add4模式开关 */
   oal_uint8              uc_add4_open;

   /* 芯片验证功能总开关 */
   oal_uint8              uc_chip_test_open;

   /* 用于芯片验证DFX特性 */
   oal_switch_enum_uint8  en_cfg_tx_cnt;

   /* 用于msdu_life_time 测试 */
   oal_uint8              uc_lifetime_flag;             /* 0:表示off，1表示on */
   oal_int16              s_ct_sch_lifetime_delay_ms;   /* 调整的tx_dscp时间offset */
   oal_uint32             ul_tx_mpdu_num;               /* 发送mpdu个数 */
   oal_uint32             ul_tx_succ_mpdu_num;          /* 发送成功的mpdu个数*/
   oal_uint32             ul_rx_mpdu_num;               /* 接收的mpdu个数 */

   /* 用于txop测试 */
   oal_uint8              uc_long_nav_flag;             /* long nav 测试功能开关 */
   oal_uint8              uc_long_nav_is_enabled;       /* long nav是否使能 */

   /* 用于cca测试 */
   oal_uint8              uc_cca_flag;                  /* cca测试功能开关 */
   oal_uint32             ul_cca_rx_sta_num;            /* cca测试接收到的STA报文 */
   oal_uint32             ul_cca_rx_ap_num;             /* 捕获门限测试接收到的ap报文 */
   oal_uint32             ul_mean_backoff;              /* 平均退避时间 */
}dmac_test_mng_stru;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#ifdef _PRE_WLAN_CHIP_TEST
extern dmac_test_mng_stru  g_st_dmac_test_mng;
#endif

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern oal_void     dmac_test_init(oal_void);
extern dmac_test_encap_frame *dmac_test_get_encap_frame(oal_void);
extern oal_uint32   dmac_test_encap_init(dmac_test_encap_frame *pst_encap_fun);
extern oal_void     dmac_test_set_software_retry(oal_uint8 * puc_param);
extern oal_void     dmac_test_open_addr4(oal_uint8 *puc_add4_open);
extern oal_void     dmac_test_set_addr4(hal_tx_dscr_stru * pst_tx_dscr);

extern oal_void     dmac_test_set_dscr_software_retry(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr);
extern oal_uint32   dmac_test_get_chip_test(oal_void);
extern oal_void     dmac_test_set_chip_test(oal_uint8 uc_chip_test_open);
extern oal_void dmac_test_lpm_wow_init(oal_void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __HMAC_CHIP_TEST_H__ */

