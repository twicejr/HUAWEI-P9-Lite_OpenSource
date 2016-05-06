/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  hi_bbp_reg_hi6421.c
*
*   作    者 :  x00195528
*
*   描    述 :  实现bbp v711相关的寄存器操作及bug修复
*
*   修改记录 :  2013年2月2日  v1.00  x00195528  创建
*************************************************************************/
/*lint -save -e537 -e656 -e801*/
#include "hi_base.h"
#include "hi_version.h"
#include "hi_bbp_ctu.h"
#include "hi_bbp_int.h"
#include "hi_bbp_lstu.h"
#include "hi_bbp_tstu.h"
#include "hi_bbp_ltedrx.h"
#include "hi_bbp_tdsdrx.h"
#include "hi_bbp_ul.h"

#include <bsp_sysctrl.h>
#include "bsp_hardtimer.h"
#include "bsp_ipc.h"
#include <bsp_version.h>

#include "bbp_osl.h"
#include "hi_bbp_reg.h"
#include "bbp_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct bbp_info g_bbpinfo;
void* sysreg_base = NULL;
/*规避bbp drx区域连读bug*/
static void hi_bbp_drxbug_evade(void)
{
    if(sysreg_base)
        (void)readl((u32)sysreg_base + HI_VERSION_ID_OFFSET);
}

/*1代表打开中断，0代表屏蔽中断*/
/*LTETF相关中断*/
void hi_bbp_int_ltetf_clear(void)
{
    //set_hi_bbp_int_marm_int_cls_arm_position_int_cls(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_set((reg_base + HI_BBP_INT_ARM_INT_CLS_OFFSET),(0x1 << 0));
}
void hi_bbp_int_ltetf_mask(void)
{
    //set_hi_bbp_int_marm_int_msk_arm_position_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_INT_ARM_INT_MSK_OFFSET),(0x1 << 0));
}
void hi_bbp_int_ltetf_unmask(void)
{
    //set_hi_bbp_int_marm_int_msk_arm_position_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_set((reg_base + HI_BBP_INT_ARM_INT_MSK_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_int_ltetf_status(void)
{
    //return get_hi_bbp_int_marm_int_msk_arm_position_int_msk();
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_INT_ARM_INT_MSK_OFFSET),(0x1 << 0));
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
    unsigned long bbp_flag = 0;
    //set_hi_bbp_ltedrx_arm_sleep_int_clear_wakeup_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
void hi_bbp_int_ltewp_mask(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_ltedrx_arm_sleep_int_msk_wakeup_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_clr((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
void hi_bbp_int_ltewp_unmask(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_ltedrx_arm_sleep_int_msk_wakeup_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
unsigned int hi_bbp_int_ltewp_status(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_value = 0;
    //return get_hi_bbp_ltedrx_arm_int_state_wakeup_int_state();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    hi_bbp_drxbug_evade();
    reg_value = bbp_bit_chk((reg_base + HI_BBP_LTEDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
void hi_bbp_int_tdswp_clear(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_tdsdrx_arm_sleep_int_clear_wakeup_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
void hi_bbp_int_tdswp_mask(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_tdsdrx_arm_sleep_int_msk_wakeup_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_clr((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
void hi_bbp_int_tdswp_unmask(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_tdsdrx_arm_sleep_int_msk_wakeup_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}

unsigned int hi_bbp_int_tdswp_status(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_value = 0;
    //return get_hi_bbp_tdsdrx_arm_int_state_wakeup_int_state();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    hi_bbp_drxbug_evade();
    reg_value =  bbp_bit_chk((reg_base + HI_BBP_TDSDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
void hi_bbp_int_wakeup_lte_clear(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    /*清除wake up 中断*/
    /*为了不重复调用锁，不使用hi_bbp_int_ltewp_clear()接口，直接操作寄存器;*/
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
    time_stamp = bsp_get_slice_value();
    do{
        /*int_status = hi_bbp_int_ltewp_status();*/
        int_status = bbp_bit_chk((reg_base + HI_BBP_LTEDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
        new_slice = bsp_get_slice_value();
        /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
        hi_bbp_drxbug_evade();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));
    if(int_status != 0){
        bbp_print_error("wakeup lte int cannot clear!\n");
    }
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return;
}
void hi_bbp_int_wakeup_tds_clear(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    /*清除wake up 中断*/
    /*hi_bbp_int_tdswp_clear();*/
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
    time_stamp = bsp_get_slice_value();
    do{
        /*int_status = hi_bbp_int_tdswp_status();*/
        int_status = bbp_bit_chk((reg_base + HI_BBP_TDSDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
        new_slice = bsp_get_slice_value();
        /*归避bbp_on 连读问题,单号2013121200228*/
        hi_bbp_drxbug_evade();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));
    if(int_status != 0){
        bbp_print_error("wakeup tds int cannot clear!\n");
    }
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return;
}
/*系统帧相关*/
void hi_bbp_ltestu_tim_lock(void)
{
    //set_hi_bbp_stu_tim_lock_tim_lock(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    bbp_bit_set((reg_base + HI_BBP_STU_TIM_LOCK_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_get_lte_fn(void)
{
    //return get_hi_bbp_stu_sfn_rpt_sfn_rpt();
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    /*bit0~9*/
    return (readl((u32)reg_base + HI_BBP_STU_SFN_RPT_OFFSET)&0x3ff);
}
unsigned int hi_bbp_get_lte_sfn(void)
{
    //return get_hi_bbp_stu_subfrm_num_rpt_subfrm_num_rpt();
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    /*bit0~9*/
    return (readl((u32)reg_base + HI_BBP_STU_SUBFRM_NUM_RPT_OFFSET)&0x3ff);
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
    u32 reg_value = 0;
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    reg_value =  readl(reg_base + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET);
    /* get_chip是为归避bbp_on 连读问题，无实际意义,单号2013121200228*/
    hi_bbp_drxbug_evade();
    reg_value +=  readl(reg_base + HI_BBP_LTEDRX_SWITCH_32K_CNT_OFFSET);

    return reg_value;
}
unsigned int hi_bbp_get_tds_slp_needtime(void)
{
    u32 reg_value = 0;
    /*bit0~26*/
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    reg_value = readl(reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET);
    /* get_chip是为归避bbp_on 连读问题，无实际意义,单号2013121200228*/
    hi_bbp_drxbug_evade();
    reg_value += readl(reg_base + HI_BBP_TDSDRX_SWITCH_32K_CNT_OFFSET);

    return reg_value;
}
unsigned int hi_bbp_get_lte_slp_time(void)
{
    unsigned long bbp_flag;
    u32 reg_value = 0;
    //return get_hi_bbp_ltedrx_slp_time_cur_slp_time_cur();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    reg_value = readl(reg_base + HI_BBP_LTEDRX_SLP_TIME_CUR_OFFSET);
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
unsigned int hi_bbp_get_tds_slp_time(void)
{
    unsigned long bbp_flag;
    u32 reg_value = 0;
    //return get_hi_bbp_tdsdrx_slp_time_cur_slp_time_cur();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    reg_value = readl(reg_base + HI_BBP_TDSDRX_SLP_TIME_CUR_OFFSET);
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
unsigned int hi_bbp_get_lte_clk_switch_state(void)
{
    unsigned long bbp_flag;
    u32 reg_value = 0;
    //return get_hi_bbp_ltedrx_clk_switch_state_clk_switch_state();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    reg_value = bbp_bit_get((reg_base + HI_BBP_LTEDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
unsigned int hi_bbp_get_tds_clk_switch_state(void)
{
    unsigned long bbp_flag;
    u32 reg_value = 0;
    //return get_hi_bbp_tdsdrx_clk_switch_state_clk_switch_state();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    reg_value = bbp_bit_get((reg_base + HI_BBP_TDSDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
    return reg_value;
}
unsigned int hi_bbp_get_lte_wakeup_time(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    u32 sleep_t = 0;/*一共要睡多长时间*/
    u32 sleeped_t = 0;/*已经睡了多长时间*/
    u32 effect = 0;/*睡眠时长是否生效*/
    u32 ret;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*判断睡眠时长是否有效,0xfff12000+0x200*/
    //effect = hi_bbp_get_lte_clk_switch_state();
    effect = bbp_bit_get((reg_base + HI_BBP_LTEDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));

    if(0==effect)
    {   /*若睡眠时长无效，则返回最大值*/
        ret = 0xffffffff;
        goto out;
    }

    sleep_t += hi_bbp_get_lte_slp_needtime();/* *(0xfff12000+0x1c)+*(0xfff12000+0x20) */
    //sleeped_t = hi_bbp_get_lte_slp_time();/*0xfff12000+0x20c*/
    sleeped_t = readl(reg_base + HI_BBP_LTEDRX_SLP_TIME_CUR_OFFSET);

    ret = sleep_t-sleeped_t;

out:
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
    return ret;
}
unsigned int hi_bbp_get_tds_wakeup_time(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    u32 sleep_t = 0;/*一共要睡多长时间*/
    u32 sleeped_t = 0;/*已经睡了多长时间*/
    u32 effect = 0;/*睡眠时长是否生效*/
    u32 ret;

    /* IPC锁为归避bbp_on 连读问题,单号2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    /*判断睡眠时长是否有效*/
    //effect = hi_bbp_get_tds_clk_switch_state();/*0xfff13400+0x200*/
    effect = bbp_bit_get((reg_base + HI_BBP_TDSDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));

    if(0==effect){/*若睡眠时长无效，则返回最大值*/
        ret = 0xffffffff;
        goto out;
    }

    sleep_t += hi_bbp_get_tds_slp_needtime();/* *(0xfff13400+0x1c)+*(0xfff13400+0x20) */
    //sleeped_t =hi_bbp_get_tds_slp_time();/*0xfff13400+0x20c*/
    sleeped_t = readl(reg_base + HI_BBP_TDSDRX_SLP_TIME_CUR_OFFSET);
    ret = sleep_t-sleeped_t;

out:
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
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
unsigned int hi_bbp_get_ta_value(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_UL].reg_base;
    return readl(reg_base + HI_BBP_UL_UL_TA_REG_OFFSET);
}

int hi_bbp_get_timing_val(BBP_TIMING_STRU *pstTiming)
{
    return 0;
}

int hi_bbp_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
/*规避dma依赖lbbp clk的bug*/
unsigned int hi_lbbp_clk_status(void)
{
    return bbp_clkctrl_is_enabled(BBP_CLK_L);
}
void hi_lbbp_clk_enable(void)
{
    bbp_clkctrl_enable(BBP_CLK_L);
}
void hi_lbbp_clk_disable(void)
{
    bbp_clkctrl_disable(BBP_CLK_L);
}
static void bbp_common_clk_enable(void)
{
    bbp_clkctrl_enable(BBP_CLK_COMM);
}
static void bbp_ao_clk_enable(void)
{
    bbp_clkctrl_enable(BBP_CLK_AO);
}
void bbp_comm_reset(void)
{
}
void bbp_comm_unreset(void)
{
}
void hi_bbp_sepical_resume(void)
{
}
/*寄存器访问掉电保护*/
unsigned int bbp_get_twmtcmos_status(void)
{
    if(bsp_get_version_info()->board_type == BSP_BOARD_TYPE_SFT)
    {
        return 1;
    }
    else
    {
        return bbp_pwrctrl_is_enabled(BBP_PWR_TW)\
          &bbp_clkctrl_is_enabled(BBP_CLK_TW_T_122M)\
          &bbp_clkctrl_is_enabled(BBP_CLK_TW_T_245M);
    }
}

/*用作对lte寄存器访问掉电保护*/
unsigned int bbp_get_ltemtcmos_status(void)
{
    if(bsp_get_version_info()->board_type == BSP_BOARD_TYPE_SFT)
    {
        return 1;
    }
    else
    {
        return bbp_pwrctrl_is_enabled(BBP_PWR_L);
    }
}
void bbp_dpm_nv_init()
{
    g_bbpinfo.dpm.pwr_nv[BBP_PWR_G1] = g_bbpinfo.dpm.pwc_nv_config.drx_g1bbp_pd;
    g_bbpinfo.dpm.pwr_nv[BBP_PWR_G2] = g_bbpinfo.dpm.pwc_nv_config.drx_g2bbp_pd;
    g_bbpinfo.dpm.pwr_nv[BBP_PWR_TW] = g_bbpinfo.dpm.pwc_nv_config.drx_twbbp_pd;
    g_bbpinfo.dpm.pwr_nv[BBP_PWR_W] = g_bbpinfo.dpm.pwc_nv_config.drx_wbbp_pd;
    g_bbpinfo.dpm.pwr_nv[BBP_PWR_IRM] = g_bbpinfo.dpm.pwc_nv_config.drx_irm_pd;
}
void hi_bbp_init()
{
    /*打开BBP_COMMON的时钟*/
    bbp_common_clk_enable();
    /*打开BBP_AO的时钟*/
    bbp_ao_clk_enable();
    /*低功耗上下电nv控制*/
    bbp_dpm_nv_init();
    /*获取系统控制器基地址，规避drx连续访问bug*/
    sysreg_base = bsp_sysctrl_addr_byindex(sysctrl_ao);
    /*bbp解复位*/
	if(bsp_get_version_info()->board_type == BSP_BOARD_TYPE_SFT)
	{
    	writel(0xffffffff,0xe020007c);
	}
}
#ifdef __cplusplus
}
#endif
/*lint -restore*/