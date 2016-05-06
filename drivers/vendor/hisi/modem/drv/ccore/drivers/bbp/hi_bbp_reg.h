/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  hi_bbp.c
*
*   作    者 :  x00195528
*
*   描    述 :
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/
#ifndef __HI_BBP_RGE_H__
#define __HI_BBP_RGE_H__

#include "hi_bbp.h"
#include "bbp_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

/*1代表打开中断，0代表屏蔽中断*/
/*LTETF相关中断*/
void hi_bbp_int_ltetf_clear(void);
void hi_bbp_int_ltetf_mask(void);
void hi_bbp_int_ltetf_unmask(void);
unsigned int hi_bbp_int_ltetf_status(void);
/*TDSTF相关中断*/
void hi_bbp_int_tdstf_clear(void);
void hi_bbp_int_tdstf_mask(void);
void hi_bbp_int_tdstf_unmask(void);
unsigned int hi_bbp_int_tdstf_status(void);
/*WAKEUP相关中断*/
void hi_bbp_int_ltewp_clear(void);
void hi_bbp_int_ltewp_mask(void);
void hi_bbp_int_ltewp_unmask(void);
unsigned int  hi_bbp_int_ltewp_status(void);
void hi_bbp_int_tdswp_clear(void);
void hi_bbp_int_tdswp_mask(void);
void hi_bbp_int_tdswp_unmask(void);
unsigned int  hi_bbp_int_tdswp_status(void);
void hi_bbp_int_cdma1xwp_clear(void);
void hi_bbp_int_cdma1xwp_mask(void);
void hi_bbp_int_cdma1xwp_unmask(void);
unsigned int hi_bbp_int_cdma1xwp_status(void);
void hi_bbp_int_cdmahrpdwp_clear(void);
void hi_bbp_int_cdmahrpdwp_mask(void);
void hi_bbp_int_cdmahrpdwp_unmask(void);
unsigned int hi_bbp_int_cdmahrpdwp_status(void);

void hi_bbp_int_wakeup_lte_clear(void);
void hi_bbp_int_wakeup_tds_clear(void);
void hi_bbp_int_wakeup_cdma1x_clear(void);
void hi_bbp_int_wakeup_cdmahrpd_clear(void);
/*系统时间相关*/
unsigned int hi_bbp_systime_low(void);
unsigned int hi_bbp_systime_high(void);
/*系统帧相关*/
void hi_bbp_ltestu_tim_lock(void);
unsigned int  hi_bbp_get_lte_fn(void);
unsigned int hi_bbp_get_lte_sfn(void);
unsigned int hi_bbp_get_tds_sfn(void);
void hi_bbp_set_tds_sfn_oft(unsigned short sf_oft);
void hi_bbp_get_tds_sfn_oft(unsigned short* sf_oft);
unsigned int hi_bbp_get_lte_slp_needtime(void);
unsigned int hi_bbp_get_tds_slp_needtime(void);
unsigned int hi_bbp_get_lte_slp_time(void);
unsigned int hi_bbp_get_tds_slp_time(void);
unsigned int hi_bbp_get_lte_clk_switch_state(void);
unsigned int hi_bbp_get_tds_clk_switch_state(void);
unsigned int hi_bbp_get_lte_wakeup_time(void);
unsigned int hi_bbp_get_tds_wakeup_time(void);
unsigned int hi_bbp_get_lte_meanflag(void);
unsigned int hi_bbp_get_tds_meanflag(void);
unsigned int hi_bbp_get_wcdma_meanflag(void);
unsigned int hi_bbp_get_gsm_meanflag(void);
unsigned int hi_bbp_get_cdma_meanflag(void);
unsigned int hi_bbp_get_ta_value(void);
int hi_bbp_get_timing_val(BBP_TIMING_STRU *pstTiming);
int hi_bbp_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);
int hi_bbp_ccpu_reset_and_wait_idle(void);
void hi_bbp_sepical_resume(void);

/*寄存器访问掉电保护*/
unsigned int bbp_get_twmtcmos_status(void);
/*用作对lte寄存器访问掉电保护*/
unsigned int bbp_get_ltemtcmos_status(void);

void bbp_comm_reset(void);
void bbp_comm_unreset(void);
unsigned int hi_lbbp_clk_status(void);
void hi_lbbp_clk_enable(void);
void hi_lbbp_clk_disable(void);
void hi_bbpdma_clk_enable(void);
void hi_bbpdma_clk_disable(void);
unsigned int hi_bbp_pll_status(void);
void hi_bbp_pll_enable(void);
void hi_bbp_pll_disable(void);
void hi_bbp_init(void);

/*测试验证需要*/
void hi_bbp_fpga_init(void);


#ifdef __cplusplus
}
#endif

#endif
