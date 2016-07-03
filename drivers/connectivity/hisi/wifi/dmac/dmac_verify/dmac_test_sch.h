

#ifndef __DMAC_TEST_SCH_H__
#define __DMAC_TEST_SCH_H__

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
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TEST_SCH_H

/*****************************************************************************
  2 宏定义
*****************************************************************************/

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
extern  oal_void dmac_test_sch_modify_txdscp_timestamp(oal_uint16 *p_us_tsf, oal_int16 s_adjust_time_ms);
extern  oal_void dmac_test_sch_stat_tx_mpdu_num(dmac_user_stru *pst_dmac_user, oal_uint8 uc_tidno, hal_tx_dscr_ctrl_one_param st_tx_dscr_param, mac_tx_ctl_stru *pst_cb);
extern  oal_void dmac_test_sch_stat_rx_mpdu_num(frw_event_hdr_stru *pst_event_hdr, mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_rx_ctl);
extern  oal_void dmac_test_sch_set_long_nav_enable(hal_tx_dscr_stru *pst_tx_dscr);
extern  oal_void dmac_test_sch_stat_rx_sta_num(frw_event_hdr_stru *pst_event_hdr,mac_vap_stru *pst_vap, dmac_rx_ctl_stru *pst_rx_ctl);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __DMAC_TEST_SCH_H__ */

