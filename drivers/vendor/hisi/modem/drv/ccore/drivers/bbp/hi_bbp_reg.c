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
/*lint -save -e537 -e656 -e801*/
#include "product_config.h"
#include "hi_base.h"
#include "hi_pwrctrl.h"
#include "hi_pwrctrl_interface.h"

#include "hi_bbp_ctu.h"
#include "hi_bbp_int.h"
#include "hi_bbp_lstu.h"
#include "hi_bbp_tstu.h"
#include "hi_bbp_ltedrx.h"
#include "hi_bbp_tdsdrx.h"
#include "hi_bbp_cdmadrx.h"
#include "hi_bbp_ul.h"

#include "osl_err.h"
#include "bsp_version.h"
#include "bsp_reset.h"
#include "bsp_hardtimer.h"
#include <bsp_sysctrl.h>
#include "bsp_clk.h"

#include "bbp_osl.h"
#include "hi_bbp_reg.h"
#include "bbp_balong.h"
#include "bsp_bbp.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct bbp_info g_bbpinfo;
struct clk          *bbp_tdl_clk;

/*1代表打开中断，0代表屏蔽中断*/
/*LTETF相关中断*/
void hi_bbp_int_ltetf_clear(void)
{
    //set_hi_bbp_int_marm_int_cls_arm_position_int_cls(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_set((reg_base + HI_BBP_INT_MARM_INT_CLS_OFFSET),(0x1 << 0));
}
void hi_bbp_int_ltetf_mask(void)
{
    //set_hi_bbp_int_marm_int_msk_arm_position_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_INT_MARM_INT_MSK_OFFSET),(0x1 << 0));
}
void hi_bbp_int_ltetf_unmask(void)
{
    //set_hi_bbp_int_marm_int_msk_arm_position_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_set((reg_base + HI_BBP_INT_MARM_INT_MSK_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_int_ltetf_status(void)
{
    //return get_hi_bbp_int_marm_int_msk_arm_position_int_msk();
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_INT_MARM_INT_MSK_OFFSET),(0x1 << 0));
}
/*TDSTF相关中断*/
void hi_bbp_int_tdstf_clear(void)
{
    //set_hi_bbp_tstu_pub_int_clear_arm_sfrm_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    bbp_bit_set((reg_base + HI_BBP_TSTU_PUB_INT_CLEAR_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdstf_mask(void)
{
    //set_hi_bbp_tstu_pub_int_msk_arm_sfrm_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_TSTU_PUB_INT_MSK_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdstf_unmask(void)
{
    //set_hi_bbp_tstu_pub_int_msk_arm_sfrm_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    bbp_bit_set((reg_base + HI_BBP_TSTU_PUB_INT_MSK_OFFSET),(0x1 << 1));
}
unsigned int hi_bbp_int_tdstf_status(void)
{
    //return get_hi_bbp_tstu_pub_int_msk_arm_sfrm_int_msk();
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_TSTU_PUB_INT_MSK_OFFSET),(0x1 << 1));
}
/*WAKEUP相关中断*/
void hi_bbp_int_ltewp_clear(void)
{
    //set_hi_bbp_ltedrx_arm_sleep_int_clear_wakeup_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
}
void hi_bbp_int_ltewp_mask(void)
{
    //set_hi_bbp_ltedrx_arm_sleep_int_msk_wakeup_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
}
void hi_bbp_int_ltewp_unmask(void)
{
    //set_hi_bbp_ltedrx_arm_sleep_int_msk_wakeup_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
}
unsigned int hi_bbp_int_ltewp_status(void)
{
    //return get_hi_bbp_ltedrx_arm_int_state_wakeup_int_state();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_LTEDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdswp_clear(void)
{
    //set_hi_bbp_tdsdrx_arm_sleep_int_clear_wakeup_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdswp_mask(void)
{
    //set_hi_bbp_tdsdrx_arm_sleep_int_msk_wakeup_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdswp_unmask(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
}
unsigned int hi_bbp_int_tdswp_status(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_TDSDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
}
#ifdef CONFIG_CBBE
void hi_bbp_int_cdma1xwp_clear(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_ARM_OFFSET),(0x1 << 8));
}
void hi_bbp_int_cdma1xwp_mask(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_ARM_OFFSET),(0x1 << 0));
}
void hi_bbp_int_cdma1xwp_unmask(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CDRX].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_ARM_OFFSET),(0x1 << 0));
    bbp_bit_set((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_ARM_OFFSET),((u32)0x1 << 31));
}
unsigned int hi_bbp_int_cdma1xwp_status(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CDRX].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_STA_ARM_OFFSET),(0x1 << 0));
}
void hi_bbp_int_cdmahrpdwp_clear(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_ARM_OFFSET),(0x1 << 9));
}
void hi_bbp_int_cdmahrpdwp_mask(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_ARM_OFFSET),(0x1 << 1));
}
void hi_bbp_int_cdmahrpdwp_unmask(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CDRX].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_ARM_OFFSET),(0x1 << 1));
    bbp_bit_set((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_ARM_OFFSET),((u32)0x1 << 31));
}
unsigned int hi_bbp_int_cdmahrpdwp_status(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CDRX].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_CDMADRX_WAKEUP_INT_STA_ARM_OFFSET),(0x1 << 1));
}
#endif
/* 说明  : 时钟频率不同，必须判断清除完成后才能进行下步操作 */
void hi_bbp_int_wakeup_lte_clear(void)
{
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    hi_bbp_int_ltewp_clear();
    time_stamp = bsp_get_slice_value();
    do{
        int_status = hi_bbp_int_ltewp_status();
        new_slice = bsp_get_slice_value();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));

    if(int_status != 0){
        bbp_print_error("wakeup lte int cannot clear!\n");
    }
    return ;
}
void hi_bbp_int_wakeup_tds_clear(void)
{
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    hi_bbp_int_tdswp_clear();
    time_stamp = bsp_get_slice_value();
    do{
        int_status = hi_bbp_int_tdswp_status();
        new_slice = bsp_get_slice_value();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));

    if(int_status != 0){
        bbp_print_error("wakeup tds int cannot clear!\n");
    }
    return ;
}
#ifdef CONFIG_CBBE
void hi_bbp_int_wakeup_cdma1x_clear(void)
{
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    hi_bbp_int_cdma1xwp_clear();
    time_stamp = bsp_get_slice_value();
    do{
        int_status = hi_bbp_int_cdma1xwp_status();
        new_slice = bsp_get_slice_value();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));

    if(int_status != 0){
        bbp_print_error("wakeup cdma 1x int cannot clear!\n");
    }
    return ;
}
void hi_bbp_int_wakeup_cdmahrpd_clear(void)
{
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    hi_bbp_int_cdmahrpdwp_clear();
    time_stamp = bsp_get_slice_value();
    do{
        int_status = hi_bbp_int_cdmahrpdwp_status();
        new_slice = bsp_get_slice_value();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));

    if(int_status != 0){
        bbp_print_error("wakeup cdma hrpd int cannot clear!\n");
    }
    return ;
}
#endif
/*系统帧相关*/
void hi_bbp_ltestu_tim_lock(void)
{
    //set_hi_bbp_stu_tim_lock_tim_lock(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    bbp_bit_set((reg_base + HI_BBP_LSTU_TIM_LOCK_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_get_lte_fn(void)
{
    //return get_hi_bbp_stu_sfn_rpt_sfn_rpt();
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    /*bit0~9*/
    return (readl((u32)reg_base + HI_BBP_LSTU_SFN_RPT_OFFSET)&0x3ff);
}
unsigned int hi_bbp_get_lte_sfn(void)
{
    //return get_hi_bbp_stu_subfrm_num_rpt_subfrm_num_rpt();
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    /*bit0~9*/
    return (readl((u32)reg_base + HI_BBP_LSTU_SUBFRM_NUM_RPT_OFFSET)&0x3ff);
}
unsigned int hi_bbp_get_tds_sfn(void)
{
    //return get_hi_bbp_tstu_tds_stu_sfn_tds_stu_sfn();
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    /*bit0~15*/
    return readl(reg_base + HI_BBP_TSTU_TDS_STU_SFN_OFFSET);
}
void hi_bbp_set_tds_sfn_oft(unsigned short sf_oft)
{
    //set_hi_bbp_tstu_sfn_oft_sfn_oft(sf_oft);
    //set_hi_bbp_tstu_time_adj_start_time_switch_start(1);
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    /*bit0~15*/
    writel((unsigned int)sf_oft,(reg_base + HI_BBP_TSTU_SFN_OFT_OFFSET));
    /*定时切换使能，TODO:和sunli确认，此处是否需要，脉冲有效*/
    bbp_bit_set((reg_base + HI_BBP_TSTU_TIME_ADJ_START_OFFSET),(0x1 << 1));
}
/*测试需要*/
void hi_bbp_get_tds_sfn_oft(unsigned short* sf_oft)
{
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    /*bit0~15*/
    *sf_oft = (unsigned short)readl(reg_base + HI_BBP_TSTU_SFN_OFT_OFFSET);
}
unsigned int hi_bbp_get_lte_slp_needtime(void)
{
    //return (get_hi_bbp_ltedrx_wakeup_32k_cnt_wakeup_32k_cnt()+get_hi_bbp_ltedrx_switch_32k_cnt_switch_32k_cnt());
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    return (readl(reg_base + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET) + \
            readl(reg_base + HI_BBP_LTEDRX_SWITCH_32K_CNT_OFFSET));
}
unsigned int hi_bbp_get_tds_slp_needtime(void)
{
    //return (get_hi_bbp_tdsdrx_wakeup_32k_cnt_wakeup_32k_cnt()+get_hi_bbp_tdsdrx_switch_32k_cnt_switch_32k_cnt());
    /*bit0~26*/
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    return (readl(reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET) + \
            readl(reg_base + HI_BBP_TDSDRX_SWITCH_32K_CNT_OFFSET));
}
unsigned int hi_bbp_get_lte_slp_time(void)
{
    //return get_hi_bbp_ltedrx_slp_time_cur_slp_time_cur();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    return readl(reg_base + HI_BBP_LTEDRX_SLP_TIME_CUR_OFFSET);
}
unsigned int hi_bbp_get_tds_slp_time(void)
{
    //return get_hi_bbp_tdsdrx_slp_time_cur_slp_time_cur();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    return readl(reg_base + HI_BBP_TDSDRX_SLP_TIME_CUR_OFFSET);
}
unsigned int hi_bbp_get_lte_clk_switch_state(void)
{
    //return get_hi_bbp_ltedrx_clk_switch_state_clk_switch_state();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    return bbp_bit_get((reg_base + HI_BBP_LTEDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_get_tds_clk_switch_state(void)
{
    //return get_hi_bbp_tdsdrx_clk_switch_state_clk_switch_state();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    return bbp_bit_get((reg_base + HI_BBP_TDSDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_get_lte_wakeup_time(void)
{
    u32 sleep_t = 0;/*一共要睡多长时间*/
    u32 sleeped_t = 0;/*已经睡了多长时间*/
    u32 effect = 0;/*睡眠时长是否生效*/
    u32 ret;

    /*判断睡眠时长是否有效,0xfff12000+0x200*/
    effect = hi_bbp_get_lte_clk_switch_state();

    if(0==effect)
    {   /*若睡眠时长无效，则返回最大值*/
        ret = 0xffffffff;
        goto out;
    }

    sleep_t += hi_bbp_get_lte_slp_needtime();/* *(0xfff12000+0x1c)+*(0xfff12000+0x20) */
    sleeped_t = hi_bbp_get_lte_slp_time();/*0xfff12000+0x20c*/

    ret = sleep_t-sleeped_t;

out:
    return ret;
}
unsigned int hi_bbp_get_tds_wakeup_time(void)
{
    u32 sleep_t = 0;/*一共要睡多长时间*/
    u32 sleeped_t = 0;/*已经睡了多长时间*/
    u32 effect = 0;/*睡眠时长是否生效*/
    u32 ret;

    /*判断睡眠时长是否有效*/
    effect = hi_bbp_get_tds_clk_switch_state();/*0xfff13400+0x200*/

    if(0==effect){/*若睡眠时长无效，则返回最大值*/
        ret = 0xffffffff;
        goto out;
    }

    sleep_t += hi_bbp_get_tds_slp_needtime();/* *(0xfff13400+0x1c)+*(0xfff13400+0x20) */
    sleeped_t =hi_bbp_get_tds_slp_time();/*0xfff13400+0x20c*/
    ret = sleep_t-sleeped_t;

out:
    return ret;
}
unsigned int hi_bbp_get_lte_meanflag(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_L_RD_OFFSET);
}
unsigned int hi_bbp_get_tds_meanflag(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_T_RD_OFFSET);
}
unsigned int hi_bbp_get_wcdma_meanflag(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_W_RD_OFFSET);
}
unsigned int hi_bbp_get_gsm_meanflag(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_GM_RD_OFFSET);
}

#ifdef CONFIG_CBBE
unsigned int hi_bbp_get_cdma_meanflag(void)
{

    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_C_RD_OFFSET);
}
#endif
unsigned int hi_bbp_get_ta_value(void)
{
    /*v7r5 change this function,software not support this function ,by yeguohe*/
    return 0;
}


#define BBP_TIMING_LOOP 5
int hi_bbp_get_timing_val(BBP_TIMING_STRU *pstTiming)
{
    int iret = 0;
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    u32 reg_value = 0;
    u8 loop,flag = 0;
    unsigned long lock_flags = 0;
    u32 timing_getind,lock_valid,lte_timing,comm32k_timing = 0;

    /*check para*/
    if(!pstTiming)
        return -1;
    if(PRODUCT_DALLAS == bsp_get_version_info()->product_name)
    {
        timing_getind = 0x270;
        lock_valid = 0xca4;
        lte_timing = 0xcdc;
        comm32k_timing = 0xcf8;
    }
    else if(PRODUCT_CHICAGO == bsp_get_version_info()->product_name)
    {
        timing_getind = 0xc80;
        lock_valid = 0xc94;
        lte_timing = 0xcd4;
        comm32k_timing = 0xcf0;
    }
    else
    {
        return iret;
    }

    /*lock*/
    local_irq_save(lock_flags);
    /* 配置C模类型,锁存系统定时(锁存所有模式的系统定时和32 GT定时) */
    bbp_bit_set(reg_base + timing_getind,((u32)0x1 << 0));

    /* 等待锁存有效标志，连续读5次，读不到，则返回失败*/
    for ( loop = 0 ; loop < BBP_TIMING_LOOP ; loop++ )
    {
        reg_value = readl(reg_base + lock_valid);
        if(reg_value & 0x1)
        {
            flag = 1;
            break;
        }
    }
    if(!flag)
    {
        g_bbpinfo.dbg.timing_err++;
        iret = -1;
        goto out;
    }
    /*读取lte模定时器寄存器值*/
    pstTiming->uwLTETimeRegVal= readl(reg_base + lte_timing);
    /*读取32k系统定时器寄存器值*/
    pstTiming->uw32KSysTime = readl(reg_base + comm32k_timing);

out:
    local_irq_restore(lock_flags);

    bbp_print_debug("lte time reg value:0x%x,32k systime reg value:0x%x.\n",pstTiming->uwLTETimeRegVal,pstTiming->uw32KSysTime);

    return iret;
}

int hi_bbp_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
int hi_bbp_ccpu_reset_and_wait_idle(void)
{
    unsigned int regvalue = 0;
    unsigned int u32slicebegin = 0;
    u32 bbp_dma_base = g_bbpinfo.part[BBP_DMA].reg_base;
    u32 wbbp_base = g_bbpinfo.part[BBP_WBBP].reg_base;
    u32 g1bbp_base = g_bbpinfo.part[BBP_G0BBP].reg_base;
    u32 g2bbp_base = g_bbpinfo.part[BBP_G1BBP].reg_base;
    u32 ucbbp_base = g_bbpinfo.part[BBP_UCBBP].reg_base;
    u32 abb_base = g_bbpinfo.part[BBP_ABB].reg_base;
    u32 bbpsc_base = g_bbpinfo.part[BBP_SCTRL].reg_base;
    u32 bbpctu_base = g_bbpinfo.part[BBP_CTU].reg_base;
    u32 sysapcrg_base = 0;
    u32 sysreg_base = 0;
    u32 i = 0;
    u32 wtc_id,g1_id,g2_id = 0;

    if(CHIP_V8R5 == bsp_get_version_info()->chip_type)
    {
        wtc_id = 1;
        g1_id = 2;
        g2_id = 3;
        bsp_reset_timestamp(0xaa, STAMP_RESET_BBP_DEBUG);

        /*查询BBPHY桥PLL时钟的状态*/
        sysapcrg_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_ap_pericrg);
        sysreg_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
        /*查询是否来源于DSPPLL 0xfff350dc[bit 4\5] == 2*/
        regvalue = readl(sysapcrg_base + 0xdc);
        regvalue &= (unsigned int)(0x3 << 4);
        if(regvalue == 0x20){
            bsp_reset_timestamp(0xbb, STAMP_RESET_BBP_DEBUG);
            /*dsp pll是否关闭 0xe020020c bit26*/
            regvalue = readl(sysreg_base + 0x20c);
            regvalue &= (unsigned int)(0x1 << 26);
            if(regvalue != (unsigned int)(0x1 << 26)){
                bsp_reset_timestamp(0x1, STAMP_RESET_WBBP_MSTER_STOP);
                return BBP_OK;
            }
        }

        /*查询BBPHY桥门控参考时钟的状态*/
        regvalue = readl(sysreg_base + 0x8);
        regvalue &= (unsigned int)(0x1 << 19);
        if(regvalue != (unsigned int)(0x1 << 19)){
            bsp_reset_timestamp(0x2, STAMP_RESET_WBBP_MSTER_STOP);
            return BBP_OK;
        }
        /*查询BBP 解复位的状态*/
        regvalue = readl(sysreg_base + 0x38);
        regvalue &= (unsigned int)(0x1 << 29);
        if(regvalue != 0x0){
            bsp_reset_timestamp(0x3, STAMP_RESET_WBBP_MSTER_STOP);
            return BBP_OK;
        }
        /*查询COMM的cmos状态*/
        regvalue = readl(sysreg_base + 0xe04);
        regvalue &= (unsigned int)(0x1 << 4);
        if(regvalue != (unsigned int)(0x1 << 4)){
            bsp_reset_timestamp(0x4, STAMP_RESET_WBBP_MSTER_STOP);
            return BBP_OK;
        }
        /*查询COMM的iso状态*/
        regvalue = readl(sysreg_base + 0xc14);
        regvalue &= (unsigned int)(0x1 << 4);
        if(regvalue != 0x0){
            bsp_reset_timestamp(0x5, STAMP_RESET_WBBP_MSTER_STOP);
            return BBP_OK;
        }
        /*查询COMM的clk状态*/
        regvalue = readl(sysreg_base + 0x18);
        regvalue &= (unsigned int)(0x1 << 30);
        if(regvalue != (unsigned int)(0x1 << 30)){
            bsp_reset_timestamp(0x6, STAMP_RESET_WBBP_MSTER_STOP);
            return BBP_OK;
        }
        /*查询COMM的reset状态*/
        regvalue = readl(sysreg_base + 0x38);
        regvalue &= (unsigned int)(0x1 << 30);
        if(regvalue != 0x0){
            bsp_reset_timestamp(0x7, STAMP_RESET_WBBP_MSTER_STOP);
            return BBP_OK;
        }
        bsp_reset_timestamp(0x1, STAMP_RESET_BBP_DEBUG);

        /*com_tldma clk*/
        if(!bbp_bit_chk(bbpsc_base + 0xe8,((u32)0x1 << 5)))
        {
            bsp_reset_timestamp(0x8, STAMP_RESET_BBP_DMA_ENTER_IDLE);
            goto gucbbp_idle;
        }
        /*com_tldma rst*/
        if(bbp_bit_chk(bbpsc_base + 0xf8,((u32)0x1 << 5)))
        {
            bsp_reset_timestamp(0x9, STAMP_RESET_BBP_DMA_ENTER_IDLE);
            goto gucbbp_idle;
        }

        /*disable dma*/
        writel(0x0, bbp_dma_base + 0x0294);/*data*/
        writel(0x0, bbp_dma_base + 0x02A8);/*channel_0*/
        writel(0x0, bbp_dma_base + 0x02B4);/*channel_1*/
        writel(0x0, bbp_dma_base + 0x02B8);/*log*/
        bsp_reset_timestamp(0x2, STAMP_RESET_BBP_DEBUG);
        /*comm*/
        for (i = 0; i < 240; i++)
        {
            writel(0x0, bbp_dma_base + 0x0308 + 0x10 *i);
        }
        bsp_reset_timestamp(0x3, STAMP_RESET_BBP_DEBUG);
        /*fast*/
        for (i = 0; i < 64; i++)
        {
            regvalue = readl(bbp_dma_base + 0x0A0C + 0x10 *i);
            regvalue &= ~(1 << 28);
            writel(regvalue, bbp_dma_base + 0x0A0C + 0x10 *i);
        }
        bsp_reset_timestamp(0x4, STAMP_RESET_BBP_DEBUG);

        /*delay 50ms*/
        u32slicebegin = bsp_get_slice_value();
        do{
        }while(CHECK_TIMEOUT_50MS(u32slicebegin));
        bsp_reset_timestamp(0x5, STAMP_RESET_BBP_DEBUG);
        /*reset bbpdma*/
        writel(0x7, bbp_dma_base);
        bsp_reset_timestamp(0x6, STAMP_RESET_BBP_DEBUG);
        /*delay 50ms*/
        u32slicebegin = bsp_get_slice_value();
        do{
        }while(CHECK_TIMEOUT_50MS(u32slicebegin));
        bsp_reset_timestamp(0x7, STAMP_RESET_BBP_DEBUG);

        /*查询BBP DMA 8/9/10bit 3类通道(包含所有)是否空闲*/
        u32slicebegin = bsp_get_slice_value();
        do{
            regvalue = readl(bbp_dma_base+ 0x10);
            regvalue &= (unsigned int)0x700;
        }while((0x0 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
        if(0x0 != regvalue){
            *(u32 *)STAMP_RESET_IDLE_FAIL_COUNT |= (u32)0x1 << ENUM_RESET_BBP_DMA;
            goto gucbbp_idle;
        }

        bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_BBP_DMA_ENTER_IDLE);

gucbbp_idle:
        /*查询ABB的解复位状态*/
        regvalue = readl(sysreg_base + 0x38);
        regvalue &= (unsigned int)0x80000000;
        if(regvalue != 0x0){
            bsp_reset_timestamp(0x1, STAMP_RESET_WBBP_ENTER_IDLE);
            goto comm_rst;
        }
        /*查询gucmst的clk状态*/
        regvalue = readl(bbpsc_base + 0xe8);
        regvalue &= (unsigned int)(0x1 << 7);
        if(regvalue != (0x1 << 7)){
            bsp_reset_timestamp(0xb1, STAMP_RESET_WBBP_ENTER_IDLE);
            goto comm_rst;
        }
        regvalue = readl(bbpsc_base + 0xf8);
        regvalue &= (unsigned int)(0x1 << 7);
        if(regvalue != 0){
            bsp_reset_timestamp(0xb2, STAMP_RESET_WBBP_ENTER_IDLE);
            goto comm_rst;
        }

        /*uc*/
        /*查询WBBP(3gp)的clk状态*/
        if(!bbp_pwr_clk_status(wtc_id)){
            bsp_reset_timestamp(0x2, STAMP_RESET_WBBP_ENTER_IDLE);
            goto gbbp_idle;
        }

        /*查询WBBP(3gp)的reset状态*/
        if(bbp_pwr_rst_status(wtc_id)){
            bsp_reset_timestamp(0x3, STAMP_RESET_WBBP_ENTER_IDLE);
            goto gbbp_idle;
        }

        /*查询WBBP(3gp)的ISO状态*/
        if(bbp_pwr_iso_status(wtc_id)){
            bsp_reset_timestamp(0x4, STAMP_RESET_WBBP_ENTER_IDLE);
            goto gbbp_idle;
        }

        /*查询WBBP(3gp)的MTCOMS状态*/
        if(!bbp_pwr_cmos_status(wtc_id)){
            bsp_reset_timestamp(0x5, STAMP_RESET_WBBP_ENTER_IDLE);
            goto gbbp_idle;
        }

        /*u*/
        /*查询ABB SCPLL0的状态*/
        regvalue = readl(abb_base + (0x800 << 2));
        regvalue &= (unsigned int)0x21;
        if(regvalue != 0x21){
            bsp_reset_timestamp(0x6, STAMP_RESET_WBBP_MSTER_STOP);
            goto cbbp_idle;
        }
        /*0xE1FC00A8，bit0/1/2/4/11，为1，时钟打开。
            0xE1FC00B8，bit0/1/2/4/11，为0，复位解除。*/
        regvalue = readl(bbpsc_base + 0xa8);
        regvalue &= (unsigned int)((0x1 << 0)|(0x1 << 1)|(0x1 <<2)|(0x1 << 4)|(0x1 << 11));
        if(regvalue != (unsigned int)((0x1 << 0)|(0x1 << 1)|(0x1 <<2)|(0x1 << 4)|(0x1 << 11))){
            bsp_reset_timestamp(0xc1, STAMP_RESET_WBBP_ENTER_IDLE);
            bsp_reset_timestamp(regvalue, STAMP_RESET_WBBP_MSTER_STOP);
            goto cbbp_idle;
        }

        regvalue = readl(bbpsc_base + 0xb8);
        regvalue &= (unsigned int)((0x1 << 0)|(0x1 << 1)|(0x1 <<2)|(0x1 << 4)|(0x1 << 11));
        if(regvalue != 0){
            bsp_reset_timestamp(0xc2, STAMP_RESET_WBBP_ENTER_IDLE);
            bsp_reset_timestamp(regvalue, STAMP_RESET_WBBP_MSTER_STOP);
            goto cbbp_idle;
        }

        bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_WBBP_MSTER_STOP);
        writel(0x0, wbbp_base + 0x9070);
        bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_WBBP_SLAVE_STOP);
        writel(0x0, wbbp_base + 0x29070);

        bsp_reset_timestamp(0x7, STAMP_RESET_WBBP_ENTER_IDLE);
        bbp_bit_clr(wbbp_base + 0x98000,((u32)0x1 << 0));
        bsp_reset_timestamp(0x8, STAMP_RESET_WBBP_ENTER_IDLE);

cbbp_idle:
         /*c*/
        /*查询ABB SCPLL1的状态*/
        regvalue = readl(abb_base + (0x80a << 2));
        regvalue &= (unsigned int)0x21;
        if(regvalue != 0x21){
            bsp_reset_timestamp(0x9, STAMP_RESET_WBBP_ENTER_IDLE);
            goto gbbp_idle;
        }
        /*0xE1FC0068，bit2/3，为1，时钟打开。*/
       /* 0xE1FC0078，bit2/3，为0，复位解除。*/
        regvalue = readl(bbpsc_base + 0x68);
        regvalue &= (unsigned int)((0x1 << 2)|(0x1 <<3));
        if(regvalue != (unsigned int)((0x1 << 2)|(0x1 <<3))){
            bsp_reset_timestamp(0xd1, STAMP_RESET_WBBP_ENTER_IDLE);
            bsp_reset_timestamp(regvalue, STAMP_RESET_WBBP_MSTER_STOP);
            goto gbbp_idle;
        }
        regvalue = readl(bbpsc_base + 0x78);
        regvalue &= (unsigned int)((0x1 << 2)|(0x1 <<3));
        if(regvalue != 0){
            bsp_reset_timestamp(0xd2, STAMP_RESET_WBBP_ENTER_IDLE);
            bsp_reset_timestamp(regvalue, STAMP_RESET_WBBP_MSTER_STOP);
            goto gbbp_idle;
        }

        /*0xE1298000[0]=0*/
        bbp_bit_clr(ucbbp_base + 0x98000,((u32)0x1 << 0));
        bsp_reset_timestamp(0xa, STAMP_RESET_WBBP_ENTER_IDLE);
        /*0xE1298100，bit0/4 =0*/
        regvalue = readl(ucbbp_base +0x98100);
        regvalue &=~ (unsigned int)0x11;
        writel(regvalue, ucbbp_base +0x98100);
        bsp_reset_timestamp(0xa1, STAMP_RESET_WBBP_ENTER_IDLE);
        /*0xE12E4008[0]=0*/
        bbp_bit_clr(ucbbp_base + 0xe4008,((u32)0x1 << 0));
        bsp_reset_timestamp(0xb, STAMP_RESET_WBBP_ENTER_IDLE);

gbbp_idle:
        /*查询ABB GPLL1的状态*/
        regvalue = readl(abb_base + (0x814 << 2));
        regvalue &= (unsigned int)0x21;
        if(regvalue != 0x21){
            bsp_reset_timestamp(0xc, STAMP_RESET_WBBP_ENTER_IDLE);
            goto gucmaster_idle;
        }
/*g1bbp_idle:*/
        /*g1*/
        if(!bbp_pwr_clk_status(g1_id)){
            bsp_reset_timestamp(0xd, STAMP_RESET_WBBP_ENTER_IDLE);
            goto g2bbpidle;
        }

        if(bbp_pwr_rst_status(g1_id)){
            bsp_reset_timestamp(0xe, STAMP_RESET_WBBP_ENTER_IDLE);
            goto g2bbpidle;
        }
        /*gsdr*/
        /*0xE1FC00E8，bit 3，为1，时钟打开。*/
        /*0xE1FC00F8，bit 3，为0，复位解除。*/
        regvalue = readl(bbpsc_base + 0xe8);
        regvalue &= (unsigned int)(0x1 << 3);
        if(regvalue != (unsigned int)(0x1 << 3)){
            bsp_reset_timestamp(0xe1, STAMP_RESET_WBBP_ENTER_IDLE);
            goto g2bbpidle;
        }
        regvalue = readl(bbpsc_base + 0xf8);
        regvalue &= (unsigned int)(0x1 << 3);
        if(regvalue != 0){
            bsp_reset_timestamp(0xe2, STAMP_RESET_WBBP_ENTER_IDLE);
            goto g2bbpidle;
        }

        bbp_bit_set(g1bbp_base + 0x1350,((u32)0x1 << 10));
        bsp_reset_timestamp(0xf, STAMP_RESET_WBBP_ENTER_IDLE);
        bbp_bit_clr(g1bbp_base + 0x45000,((u32)0x1 << 0));
        bsp_reset_timestamp(0x10, STAMP_RESET_WBBP_ENTER_IDLE);
g2bbpidle:
        /*g2*/
        if(!bbp_pwr_clk_status(g2_id)){
            bsp_reset_timestamp(0x11, STAMP_RESET_WBBP_ENTER_IDLE);
            goto gucmaster_idle;
        }

        if(bbp_pwr_rst_status(g2_id)){
            bsp_reset_timestamp(0x12, STAMP_RESET_WBBP_ENTER_IDLE);
            goto gucmaster_idle;
        }
        bbp_bit_set(g2bbp_base + 0x1350,((u32)0x1 << 10));
        bsp_reset_timestamp(0x13, STAMP_RESET_WBBP_ENTER_IDLE);

gucmaster_idle:
        /*delay 1ms*/
        u32slicebegin = bsp_get_slice_value();
        do{
        }while(CHECK_TIMEOUT_1MS(u32slicebegin));

        /*查询gucmst 通道是否空闲*/
        u32slicebegin = bsp_get_slice_value();
        do{
            regvalue = readl(bbpctu_base + 0xc098);
        }while((0x0 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
        bsp_reset_timestamp(0x14, STAMP_RESET_WBBP_ENTER_IDLE);
        if(0x0 != regvalue){
            bsp_reset_timestamp((0x1U << ENUM_RESET_WBBP)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
            bsp_reset_timestamp(regvalue, STAMP_RESET_WBBP_SLAVE_STOP);
        }
        bsp_reset_timestamp(0x15, STAMP_RESET_WBBP_ENTER_IDLE);
        /*disable gucmaster*/
        bbp_bit_clr(bbpctu_base + 0xc000,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc020,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc040,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc4b0,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc100,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc120,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc140,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc200,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc3b0,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc3d0,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc160,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc4d0,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc4f0,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc3f0,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc410,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc430,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc560,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc580,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc5a0,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc450,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc470,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc490,((u32)0x1 << 9));
        bbp_bit_clr(bbpctu_base + 0xc5e0,((u32)0x1 << 9));

        bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_WBBP_ENTER_IDLE);

comm_rst:
        bsp_reset_timestamp(0x16, STAMP_RESET_BBP_DEBUG);
        /*reset bbpcomm*/
        writel(0x40000000, sysreg_base + 0x30);
        bsp_reset_timestamp(0xff, STAMP_RESET_BBP_DEBUG);
    }

    return BBP_OK;
}

/*dma依赖clk*/
void hi_bbpdma_clk_enable(void)
{
    unsigned long bbp_flags = 0;

    spin_lock_irqsave(&g_bbpinfo.dma.clk_spinlock, bbp_flags);
    /*clk enable*/
    bbp_bit_set(g_bbpinfo.part[BBP_SCTRL].reg_base + 0xe0,(u32)0x1 << 5);
    /*rst disable*/
    bbp_bit_set(g_bbpinfo.part[BBP_SCTRL].reg_base + 0xf4,(u32)0x1 << 5);

    g_bbpinfo.dma.clk_cnts++;
    g_bbpinfo.om->dma_clkcnt = g_bbpinfo.dma.clk_cnts;
    spin_unlock_irqrestore(&g_bbpinfo.dma.clk_spinlock, bbp_flags);
}

void hi_bbpdma_clk_disable(void)
{
    unsigned long bbp_flags = 0;

    spin_lock_irqsave(&g_bbpinfo.dma.clk_spinlock, bbp_flags);

    g_bbpinfo.dma.clk_cnts--;
    g_bbpinfo.om->dma_clkcnt = g_bbpinfo.dma.clk_cnts;
    if(!g_bbpinfo.dma.clk_cnts)
    {
        /*clk disable*/
        bbp_bit_set(g_bbpinfo.part[BBP_SCTRL].reg_base + 0xe4,(u32)0x1 << 5);
        /*rst enable*/
        bbp_bit_set(g_bbpinfo.part[BBP_SCTRL].reg_base + 0xf0,(u32)0x1 << 5);
    }

    spin_unlock_irqrestore(&g_bbpinfo.dma.clk_spinlock, bbp_flags);
}

void bbp_comm_reset_v7r5(void)
{
    u32 sysmdm_addr= 0;

    /*close comm mipi*/
    bbp_rstctrl_enable(27);
    bbp_clkctrl_disable(27);

    /*close comm sys*/
    bbp_rstctrl_enable(28);
    bbp_clkctrl_disable(28);

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    /*bbp_off crg/bbc rst ,bit 30-29 should be 0*/
    writel(0x60000000,sysmdm_addr + 0x30);
    /*bbp_off crg/bbc clkdis bit31-30*/
    writel(0xc0000000,sysmdm_addr + 0x14);
}

void bbp_comm_reset_v722(void)
{
    u32 sysmdm_addr= 0;

    /*close comm mipi*/
    bbp_rstctrl_enable(27);
    bbp_clkctrl_disable(27);

    /*close comm sys*/
    bbp_rstctrl_enable(28);
    bbp_clkctrl_disable(28);

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    /*bbp_off crg/bbc rst ,bit 30-29 should be 0*/
    writel(0x60000000,sysmdm_addr + 0x30);
    /*bbp_off crg/bbc clkdis bit31-30*/
    writel(0xc0000000,sysmdm_addr + 0x14);
}

void bbp_comm_pwron_v8r5(void)
{
    u32 sysmdm_addr = 0;
    u32 value = 0;

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);

    writel((0x1 << 30), sysmdm_addr + 0x14);

    writel((0x1 << 4),sysmdm_addr + 0xc18);
    /*等待上电完成*/
    do
    {
        value = readl(sysmdm_addr + 0xe04) & (0x1 << 4);
    }while(value==0);
    udelay(30);
    /*配置解复位*/
    writel((0x1 << 30),sysmdm_addr + 0x34);
    /*配置嵌位不使能*/
    writel((0x1 << 4),sysmdm_addr + 0xc10);
    /**/
    writel((0x1 << 29), sysmdm_addr + 0x30);
    (void)readl(sysmdm_addr + 0x38);
    writel((0x1 << 29), sysmdm_addr + 0x34);
    /*配置时钟使能*/
    writel((0x1 << 30),sysmdm_addr + 0x10);
}
void bbp_comm_pwroff_v8r5(void)
{
    u32 sysmdm_addr = 0;

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);

    /*配置时钟关闭*/
    writel((0x1 << 30),sysmdm_addr + 0x14);
    /*配置嵌位使能*/
    writel((0x1 << 4),sysmdm_addr + 0xc0c);
    /*配置复位*/
    writel((0x1 << 30),sysmdm_addr + 0x30);
    /*配置下电*/
    writel((0x1 << 4),sysmdm_addr + 0xc1c);
}
void bbp_comm_reset_v8r5(void)
{
    u32 sysmdm_addr= 0;

    /*close comm mipi*/
    /* coverity[overrun-call] */
    bbp_clkrst_disable(36);
    /*close comm sys*/
    /* coverity[overrun-call] */
    bbp_clkrst_disable(37);

    /*bbp comm 下电*/
    bbp_comm_pwroff_v8r5();
    /*bbp off 复位*/
    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    writel(0x20000000,sysmdm_addr + 0x30);
}
void bbp_comm_reset(void)
{
    switch(bsp_get_version_info()->chip_type){
    case CHIP_V750:
        bbp_comm_reset_v7r5();
        break;
    case CHIP_V8R5:
        bbp_comm_reset_v8r5();
        break;
    case CHIP_V722:
        bbp_comm_reset_v722();
        break;
    default:
        break;
    }
}
void bbp_comm_unreset_v7r5(void)
{
    u32 sysmdm_addr= 0;
    u32 i = 0;

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    /*bbp_off crg/bbc clken bit31-30*/
    writel(0xc0000000,sysmdm_addr + 0x10);
    /*bbp_off crg/bbc rst disable,bit 30-29 should be 0*/
    writel(0x60000000,sysmdm_addr + 0x34);

    /*open comm mipi*/
    bbp_clkctrl_enable(27);
    bbp_rstctrl_disable(27);
    /*open comm sys*/
    bbp_clkctrl_enable(28);
    bbp_rstctrl_disable(28);

    /*disable bbpdma*/
    hi_bbpdma_clk_enable();
    for(i = 0;i <= 239;i++)
    {
        writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
    }
    hi_bbpdma_clk_disable();
}
static void bbp_debug_config(void)
{
    if(CHIP_V8R5 == bsp_get_version_info()->chip_type)
    {
        writel(0x1c9a,g_bbpinfo.part[BBP_SCTRL].reg_base+0x204);
        writel(0x1c9b,g_bbpinfo.part[BBP_SCTRL].reg_base+0x204);
        writel(0x00ff00ff,g_bbpinfo.part[BBP_SCTRL].reg_base+0x20c);
        writel(0x01,g_bbpinfo.part[BBP_SCTRL].reg_base+0x208);
    }
}

void bbp_comm_unreset_v722(void)
{
    u32 sysmdm_addr= 0;
    u32 i = 0;

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    /*bbp_off crg/bbc clken bit31-30*/
    writel(0xc0000000,sysmdm_addr + 0x10);
    /*bbp_off crg/bbc rst disable,bit 30-29 should be 0*/
    writel(0x60000000,sysmdm_addr + 0x34);

    /*open comm mipi*/
    bbp_clkctrl_enable(27);
    bbp_rstctrl_disable(27);
    /*open comm sys*/
    bbp_clkctrl_enable(28);
    bbp_rstctrl_disable(28);

    /*disable bbpdma*/
    hi_bbpdma_clk_enable();
    for(i = 0;i <= 239;i++)
    {
        writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
    }
    hi_bbpdma_clk_disable();
}

void bbp_comm_unreset_v8r5(void)
{
    u32 sysmdm_addr= 0;
    u32 i = 0;

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    /*bbp_off crg/bbc rst disable,bit 30-29 should be 0*/
    writel(0x20000000,sysmdm_addr + 0x34);
    /*bbp comm 上电*/
    bbp_comm_pwron_v8r5();

    /*open comm mipi*/
    /* coverity[overrun-call] */
    bbp_clkrst_enable(36);
    /*open comm sys*/
    /* coverity[overrun-call] */
    bbp_clkrst_enable(37);

    /*disable bbpdma*/
    hi_bbpdma_clk_enable();
    for(i = 0;i <= 239;i++)
    {
        writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
    }
    hi_bbpdma_clk_disable();

    bbp_debug_config();
}
void bbp_comm_unreset(void)
{
    switch(bsp_get_version_info()->chip_type){
    case CHIP_V750:
        bbp_comm_unreset_v7r5();
        break;
    case CHIP_V8R5:
        bbp_comm_unreset_v8r5();
        break;
    case CHIP_V722:
        bbp_comm_unreset_v722();
        break;
    default:
        break;
    }
}
/*寄存器访问掉电保护*/
unsigned int bbp_get_twmtcmos_status(void)
{
    if(CHIP_V750 == bsp_get_version_info()->chip_type)
    {
        return bbp_pwrctrl_is_enabled(1)\
          &bbp_clkctrl_is_enabled(15);/*pwr:wtc;clk:wtc_122m_tw*/
    }
    else if(CHIP_V8R5 == bsp_get_version_info()->chip_type)
    {
        /* coverity[overrun-call] */
        return bbp_pwrctrl_is_enabled(6)\
          &bbp_clkctrl_is_enabled(38);/*pwr:wtc;clk:wtc_122m_tw*/
    }
    else
        return 1;
}

/*用作对lte寄存器访问掉电保护*/
unsigned int bbp_get_ltemtcmos_status(void)
{
    if(CHIP_V750 == bsp_get_version_info()->chip_type)
        return bbp_pwrctrl_is_enabled(4);/*pwr lte*/
    else if(CHIP_V8R5 == bsp_get_version_info()->chip_type)
        /* coverity[overrun-call] */
        return bbp_pwrctrl_is_enabled(5);/*pwr lte*/
    else
        return 1;
}
void hi_bbp_sepical_resume(void)
{
    if(CHIP_V750 == bsp_get_version_info()->chip_type)
    {
        /*mask buserr irq*/
        writel(0xfffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x210);
    }
}
void hi_bbp_v7r5_init()
{
    u32 i = 0;
    u32 sysmdm_addr,syson_addr = 0;

    if(g_bbpinfo.dpm.pwc_nv.drx_bbp_init == 0)
    {
        /*open comm mipi*/
        bbp_clkctrl_enable(27);
        bbp_rstctrl_disable(27);
        /*open comm sys*/
        bbp_clkctrl_enable(28);
        bbp_rstctrl_disable(28);
    }
    else
    {
        if(BSP_BOARD_TYPE_BBIT != bsp_get_version_info()->board_type)
        {
            sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
            syson_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_ao);

            /*******************bbp_on**********************/
            /*rst disable*//*bit31-26*/
            writel(0xfc000000,syson_addr + 0x64);

            /*apb clk*//*bit30*/
            writel(0x40000000,syson_addr);

            /*******************bbp_off*********************/
            /*soc*/
            /*bbp_off crg/bbc clken bit31-30*/
            writel(0xc0000000,sysmdm_addr + 0x10);
            /*bbp_off crg/bbc rst disable,bit 30-29 should be 0*/
            writel(0x60000000,sysmdm_addr + 0x34);
        }

        /*上电*/
        for(i = 0;i <= 4;i++)
        {
            bbp_pwrctrl_enable(i);
        }

        /*clk and rst*/
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x80);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x94);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xa0);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xb4);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xc0);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xd4);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xe0);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xf4);

        if(BSP_BOARD_TYPE_BBIT != bsp_get_version_info()->board_type)
        {
            /*turbo*/
            writel(0x10d70,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x100);
        }
    }
    /*mask buserr irq*/
    writel(0xfffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x210);
    /*disable bbpdma*/
    hi_bbpdma_clk_enable();
    for(i = 0;i <= 239;i++)
    {
        writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
    }
    hi_bbpdma_clk_disable();
}
void hi_bbp_fpga_init(void)
{
    u32 sctrl_addr = g_bbpinfo.part[BBP_SCTRL].reg_base;

    /* dallas fpga bbit */
    writel(0xff,sctrl_addr + 0x0);
    writel(0xff,sctrl_addr + 0x14);
    writel(0xff,sctrl_addr + 0x20);
    writel(0xff,sctrl_addr + 0x34);
    writel(0xffffffff,sctrl_addr + 0x60);
    writel(0xffffffff,sctrl_addr + 0x74);
    writel(0xffffffff,sctrl_addr + 0x80);
    writel(0xffffffff,sctrl_addr + 0x94);
    writel(0xffffffff,sctrl_addr + 0xa0);
    writel(0xffffffff,sctrl_addr + 0xb4);
    writel(0xffffffff,sctrl_addr + 0xc0);
    writel(0xffffffff,sctrl_addr + 0xd4);
    writel(0xffffffff,sctrl_addr + 0xe0);
    writel(0xffffffff,sctrl_addr + 0xf4);
}

void hi_bbp_v8r5_init(void)
{
    u32 sctrl_addr = g_bbpinfo.part[BBP_SCTRL].reg_base;
    u32 i = 0;

    /*bbp comm 上电*/
    bbp_comm_pwron_v8r5();

    /*open bbp clk */
    if(g_bbpinfo.dpm.pwc_nv.drx_bbp_init == 0)
    {
        /*open comm mipi*/
        /* coverity[overrun-call] */
        bbp_clkrst_enable(36);
        /*open comm sys*/
        /* coverity[overrun-call] */
        bbp_clkrst_enable(37);

        /*disable bbpdma*/
        hi_bbpdma_clk_enable();
        for(i = 0;i <= 239;i++)
        {
            writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
        }
        hi_bbpdma_clk_disable();
    }
    else
    {
        hi_bbp_fpga_init();
        writel(0xff,sctrl_addr + 0x100);
        writel(0xff,sctrl_addr + 0x114);
        writel(0xff,sctrl_addr + 0x120);
        writel(0xff,sctrl_addr + 0x134);

        /*software ctrl tdl clk*/
        writel(0x0008cd78,sctrl_addr + 0x228);

        for(i = 0;i <= 239;i++)
        {
            writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
        }
    }

    bbp_debug_config();

    /*open yima clk,form peri_refclk*/
    bbp_tdl_clk = clk_get(NULL,"bbp_tdl_clk");
    if(IS_ERR(bbp_tdl_clk))
    {
        bbp_print_error("bbp_tdl_clk get failed!\n");
        return;
    }
    (void)clk_enable(bbp_tdl_clk);
}

void hi_bbp_v722_init()
{
    u32 i = 0;
    u32 sysmdm_addr,syson_addr = 0;

    if(g_bbpinfo.dpm.pwc_nv.drx_bbp_init == 0)
    {
        /*open comm mipi*/
        bbp_clkctrl_enable(27);
        bbp_rstctrl_disable(27);
        /*open comm sys*/
        bbp_clkctrl_enable(28);
        bbp_rstctrl_disable(28);
    }
    else
    {
        if(BSP_BOARD_TYPE_BBIT != bsp_get_version_info()->board_type)
        {
            sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
            syson_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_ao);

            /*******************bbp_on**********************/
            /*rst disable*//*bit31-26*/
            writel(0xfc000000,syson_addr + 0x64);

            /*apb clk*//*bit30*/
            writel(0x40000000,syson_addr);

            /*******************bbp_off*********************/
            /*soc*/
            /*bbp_off crg/bbc clken bit31-30*/
            writel(0xc0000000,sysmdm_addr + 0x10);
            /*bbp_off crg/bbc rst disable,bit 30-29 should be 0*/
            writel(0x60000000,sysmdm_addr + 0x34);
            /*上电*/
            for(i = 0;i <= 4;i++)
            {
                bbp_pwrctrl_enable(i);
            }

            writel(0x2,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x00);/*wtc pd for fpga*/
            writel(0x2,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x14);/*wtc pd for fpga*/
            /*clk and rst*/
            writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x80);/*lte pd clk*/
            writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x94);/*lte pd rst disable*/
            writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xa0);/*wtc pd clk*/
            writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xb4);/*wtc pd rst disable*/
            writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xc0);/*irm pd clk*/
            writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xd4);/*irm pd rst disable*/
            writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xe0);/*com pd clk*/
            writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xf4);/*com pd rst disable*/

             /*turbo*/
            writel(0x80d70, g_bbpinfo.part[BBP_SCTRL].reg_base + 0x228);

            /*mask bus err irq*/
            writel(0xfffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x210);

            for(i = 0;i <= 239;i++)
            {
                writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
            }

        }
        else{

            /* v722 fpga bbit */
            hi_bbp_fpga_init();

            writel(0x00,g_bbpinfo.part[BBP_CTU].reg_base +0x10010);/*chn0 et config*/
            writel(0x00,g_bbpinfo.part[BBP_CTU].reg_base +0x11010);/*chn1 et config*/

        }

         /*bbp on 0x21fa9a20*/
        writel(0x01,g_bbpinfo.part[BBP_LDRX].reg_base + 0x1a20);


    }


    return ;
}

void hi_bbp_k3v6_init()
{
    u32 bbpon_addr = g_bbpinfo.part[BBP_LDRX].reg_base;
    u32 bbpctu_addr = g_bbpinfo.part[BBP_CTU].reg_base;
    u32 sysmdm_addr = 0;

    if(BSP_BOARD_TYPE_SFT == bsp_get_version_info()->board_type)
    {
        sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);

        writel(0x10, sysmdm_addr + 0xC10);
        writel(0x60000000, sysmdm_addr + 0x34);
        writel(0x10, sysmdm_addr + 0xC18);
        writel(0x40000000, sysmdm_addr + 0x10);
    }

    hi_bbp_fpga_init();

    writel(0x00,bbpctu_addr+0x10000);/*chn0 et config*/
    writel(0x00,bbpctu_addr+0x11000);/*chn1 et config*/
    writel(0x01,bbpon_addr+0x1a20);/*bbp on */
}

void hi_bbp_init()
{
    switch(bsp_get_version_info()->chip_type){
    case CHIP_V750:
        hi_bbp_v7r5_init();
        break;
    case CHIP_V8R5:
        hi_bbp_v8r5_init();
        break;
    case CHIP_V722:
        hi_bbp_v722_init();
        break;
    case CHIP_K3V6:
        hi_bbp_k3v6_init();
        break;
    default:
        break;
    }

#ifdef V722_BBP
    hi_bbp_v722_init();
#endif
#ifdef K3V6_BBP
    hi_bbp_k3v6_init();
#endif

}

#ifdef __cplusplus
}
#endif
/*lint -restore*/
