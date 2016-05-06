/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : pm.c */
/* Version       : 2.0 */
/* Created       : 2013-04-04*/
/* Last Modified : */
/* Description   :  pm drv*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/
/*lint --e{123,124,522,525,539,537,586,438}*/
/* Warning 537: (Warning -- Repeated include  */
/* Warning 438: (Warning -- Last value assigned  not used) */
/*lint *** --e{537,539,	666,713,732,701,746,762,773,438,830}*/
#ifdef __VXWORKS__
#include <taskLib.h>
#include <cacheLib.h>
#include <arch/arm/cacheArmArch7.h>
#include <string.h>
#include <tickLib.h>
#include "config.h"
#endif
#include <sre_lowpower.h>
#include <securec.h>
#include <string.h>
#include <osl_types.h>
#include <osl_irq.h>
#include <osl_bio.h>
#include <osl_thread.h>
#include <osl_bug.h>
#include <hi_base.h>
#include <soc_interrupts_m3.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <mdrv_pm.h>
#include <mdrv_memory.h>
#include <of.h>

#include <bsp_om.h>
#include <bsp_gic_pm.h>
#include <bsp_dpm.h>
#include <bsp_cpuidle.h>
#include <bsp_wakelock.h>
#include <bsp_uart.h>
#include <bsp_dpm.h>
#include <bsp_nvim.h>
#include <bsp_hardtimer.h>
#include <bsp_icc.h>
#include <bsp_wakelock.h>
#include <bsp_shared_ddr.h>
#include <bsp_pm.h>
#include <bsp_cpufreq.h>
#include <bsp_bbp.h>
#include <bsp_pinctrl.h>
#include <bsp_m3pm_log.h>
#include <tcxo_balong.h>
#include <bsp_dump.h>
#include <bsp_sysctrl.h>
#include <bsp_pm_om.h>
#include <bsp_gic_pm.h>
#include <bsp_coresight.h>
#include <bsp_dpm.h>
#include <bsp_rsracc.h>
#include "pm.h"


DRV_NV_PM_TYPE  g_nv_pm_config  = {0};      /* NV_ID_DRV_PM */
DRV_DRX_DELAY_STRU g_nv_drx_delay = {0};

typedef int suspend_state_t;
extern u32 ipc_c2m_base_addr;
extern u32 pm_stamp_addr;
extern u32 pm_stamp_addr_phy ;
extern u32 pm_mem_ccore_base_addr;
extern u32 pm_stamp_start_addr;
extern u32 pm_stamp_pwrup_code_begin ;
extern u32 pm_stamp_rstr_mmureg_begin ;
extern u32 pm_bak_mmu_reg_addr ;
extern u32 pm_stamp_rstr_mmureg_end ;
extern u32 pm_stamp_rstr_coreg_begin ;
extern u32 pm_bak_arm_co_reg_addr ;
extern u32 pm_stamp_rstr_coreg_end ;
extern u32 pm_bak_arm_reg_addr ;
extern u32 pm_stamp_sleep_asm_enter ;
extern u32 pm_stamp_bak_coreg_begin ;
extern u32 pm_stamp_bak_coreg_end ;
extern u32 pm_stamp_bak_mmureg_begin ;
extern u32 pm_stamp_bak_mmureg_end ;
extern u32 pm_stamp_before_send_ipc ;
extern u32 pm_stamp_after_send_ipc ;
extern u32 pm_stamp_after_wfi_nop ;
extern u32 pm_hi_uart1_regbase_addr_virt ;
extern u32 pm_hi_uart1_regbase_addr ;

void* mtcmos_state_addr[6]={NULL};

//extern u32 pm_hi_mdm_gic_base_addr ;
extern u32 pm_c2m_ipc_bit;

void pm_set_trace_level(u32 level)
{
    (void)bsp_mod_level_set(BSP_MODU_PM, level);
    pm_printk(BSP_LOG_LEVEL_ERROR,"bsp_mod_level_set(BSP_MODU_PM=%d, %d)\n",BSP_MODU_PM,level);
}

static inline void pm_timer_stamp(u32 stamp_addr)
{
    u32 curr_time=0;
    curr_time = readl(pm_stamp_addr);
    writel(curr_time, stamp_addr);
}
#define PM_SHM_TIMESTAMP_ADDR   ((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_TIMESTAMP)
#define DRX_PM_FLAG_FROM_M3     (PM_SHM_TIMESTAMP_ADDR)        /* m3 置的 drx 标志位 , 读到 1 后置为 2 */
#define DRX_PM_FLAG_FOR_MSP     (PM_SHM_TIMESTAMP_ADDR+0x4)    /* 给msp的标志位，msp读到后马上清*/
#define DRX_PM_TIMESTAMP_ADDR   (PM_SHM_TIMESTAMP_ADDR+0x100)
#define DRX_PM_TIMESTAMP_SIZE   (4*16)
#define PM_CHECK_SRAM_ADDR		(unsigned int)(((SRAM_SMALL_SECTIONS * )((unsigned long)SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_PM_CHECK_ADDR)
struct pm_check_s{
	u32 need_check_sram;
	u32 sram_flag_stamp;
	u32 need_check_mdm_sysctrl;
	u32 sysctrl_flag_stamp;
	void* sysctrl_check_ref_reg_addr;
}pm_check_ctrl={0,0,0,0,NULL};
s32 pm_suspend_late(struct dpm_device *dev){
	if(pm_check_ctrl.need_check_sram){
		pm_check_ctrl.sram_flag_stamp=bsp_get_slice_value();
		writel(pm_check_ctrl.sram_flag_stamp,PM_CHECK_SRAM_ADDR);
	}
	if(pm_check_ctrl.need_check_mdm_sysctrl){
		pm_check_ctrl.sysctrl_flag_stamp=bsp_get_slice_value();
		writel(pm_check_ctrl.sysctrl_flag_stamp,(u32)pm_check_ctrl.sysctrl_check_ref_reg_addr);
	}
	return 0;
}
s32 pm_resume_early(struct dpm_device *dev){
	u32 ret=0;
	if(pm_check_ctrl.need_check_sram){
		ret = readl(PM_CHECK_SRAM_ADDR);
		BUG_ON(pm_check_ctrl.sram_flag_stamp!=ret);
	}
	if(pm_check_ctrl.need_check_mdm_sysctrl){
		ret = readl((u32)pm_check_ctrl.sysctrl_check_ref_reg_addr);
		BUG_ON(pm_check_ctrl.sysctrl_flag_stamp!=ret);
	}
	return 0;
}
struct dpm_device pm_device={
	.device_name="pm_device",
	.suspend_late=pm_suspend_late,
	.resume_early=pm_resume_early,
};

/* record drx timer if waked up by bbp_wakeup */
void pm_save_drx_timer_stamp(void)
{
    u32* time_save_addr;
    u32* drx_time_save_addr;

    time_save_addr = (u32*)(pm_stamp_start_addr + STAMP_PWRUP_CODE_BEGIN);
    drx_time_save_addr = (u32*)DRX_PM_TIMESTAMP_ADDR;

    if(readl((unsigned)DRX_PM_FLAG_FROM_M3)==1)
    {
        *(u32*)DRX_PM_FLAG_FROM_M3 = 2;
        *(u32*)DRX_PM_FLAG_FOR_MSP = 1;
        for(;time_save_addr<=(u32*)(pm_stamp_start_addr + STAMP_AFTER_DPM_RESUME);)
        {
            *drx_time_save_addr = *time_save_addr;
            time_save_addr++;
            drx_time_save_addr++;
        }
        if(g_nv_drx_delay.drv_4 == 1)
        {
            debug_pm_wake_lock();
        }
    }
}

/* save clk/mtcmos status before sleep */
void pm_save_clk_mtcmos_status(void)
{
    *(u32*)(pm_stamp_start_addr + CHECK_STATUS_START) = (u32)PM_STAMP_START_FLAG;
    *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT1) = (u32)readl((u32)mtcmos_state_addr[0]);
    *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT2) = (u32)readl((u32)mtcmos_state_addr[1]);
    *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT3) = (u32)readl((u32)mtcmos_state_addr[2]);
    *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT4) = (u32)readl((u32)mtcmos_state_addr[3]);
    *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT5) = (u32)readl((u32)mtcmos_state_addr[4]);
    *(u32*)(pm_stamp_start_addr + CHECK_PWR_STAT1   ) = (u32)readl((u32)mtcmos_state_addr[5]);
}


/* do not clear stamps. only set some start_flag  */
void pm_stamp_init(void)
{
    *(u32*)(pm_stamp_start_addr + STAMP_START_ADDR) = (u32)PM_STAMP_START_FLAG;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_WFI_NOP) = (u32)PM_STAMP_START_FLAG;
    *(u32*)(pm_stamp_start_addr + CHECK_STATUS_START) = (u32)PM_STAMP_START_FLAG;
    writel(0, pm_stamp_start_addr + PM_ENTER_COUNT);
    writel(0, pm_stamp_start_addr + PM_DPM_FAIL_COUNT);
}
/*lint -e485*//*pclint误报，不能识别二层结构体变量初始化*/
struct pm_info pm_ctrl_info =
{
    .pm_om.dpm_fail_count = 0,
    .pm_om.pm_enter_count = 0,
    .pm_om.pm_enter_asm_count = 0,
    .pm_om.pm_enter_wfi_count = 0,
    .pm_om.pm_out_count = 0,
    .pm_om.suspend_start_time = 0,
    .pm_om.suspend_end_time = 0,
    .pm_om.suspend_max_start_time = 0,
    .pm_om.suspend_max_end_time = 0,
    .pm_om.suspend_max_time = 0,
    .pm_om.resume_start_time = 0,
    .pm_om.resume_end_time = 0,
    .pm_om.resume_max_time = 0,
    .pm_om.dpm_suspend_max = 0,
    .pm_om.dpm_resume_max = 0,
    .stamp_addr =0,//DUMP_EXT_OM_DRX_CCORE_ADDR,
    .mdm_sr_stamp_base = NULL,
    .gic_flag = 1,
    .sleep_flag = 1,
    .deepsleep_nv = 0,
    .deepsleep_Tth_nv = 100,        /* 参考v7r1 105 ,v7r2可能比较小    */
    .TLbbp_sleeptimer_Tth_nv = 320, /* 32k */
    .slice_freq = 0,
    .pm_base_tick = 0,
    .pm_base_slice = 0,
    .tick_adjust_before = 0,
    .tick_adjust_after = 0,
    .pm_init_tick = 0,
    .pm_init_slice = 0,
    .pm_wakeup_slice = 0,
    .sr_time_limit_flag = 0,/* default no enable */
    .bug_reset_modem_flag = 0,
    .print_to_ddr_flag = 0,
    .pm_suspend_threshold = 0xffffffff,
    .pm_resume_threshold= 0xffffffff,
    .dpm_suspend_threshold = 0xffffffff,
    .dpm_resume_threshold = 0xffffffff,
};
/*lint +e485*/

void run_sleep_ops_suspend_cb(void)
{
	int i = MAX_PWR_OPS_SIZE-1;
	unsigned int delta = 0;
    for( ; i>=0; i -- )
    {
        if((NULL != pm_ctrl_info.g_stSleepOps[i].funcSleepIn) )
        {
        	pm_ctrl_info.g_stSleepOps[i].latest_suspend_time[0] = bsp_get_slice_value();
            pm_ctrl_info.g_stSleepOps[i].funcSleepIn();
			pm_ctrl_info.g_stSleepOps[i].latest_suspend_time[1] = bsp_get_slice_value();
			delta = get_timer_slice_delta(pm_ctrl_info.g_stSleepOps[i].latest_suspend_time[0],pm_ctrl_info.g_stSleepOps[i].latest_suspend_time[1]);		
			if(delta > pm_ctrl_info.g_stSleepOps[i].max_suspend_time_duration)
				pm_ctrl_info.g_stSleepOps[i].max_suspend_time_duration = delta;
        }
    }
}
void run_sleep_ops_resume_cb(void)
{
	int i = 0;
	unsigned int delta = 0;
    for( ; i<MAX_PWR_OPS_SIZE; i++ )
    {
        if((NULL != pm_ctrl_info.g_stSleepOps[i].funcSleepOut) )
        {
        	pm_ctrl_info.g_stSleepOps[i].latest_resume_time[0] = bsp_get_slice_value();
            pm_ctrl_info.g_stSleepOps[i].funcSleepOut();
			pm_ctrl_info.g_stSleepOps[i].latest_resume_time[1] = bsp_get_slice_value();
			delta = get_timer_slice_delta(pm_ctrl_info.g_stSleepOps[i].latest_resume_time[0],pm_ctrl_info.g_stSleepOps[i].latest_resume_time[1]);		
			if(delta > pm_ctrl_info.g_stSleepOps[i].max_resume_time_duration)
				pm_ctrl_info.g_stSleepOps[i].max_resume_time_duration = delta;
        }
    }
}

static int sleep_ops_register(ST_PWC_SLEEP_OPS_STRU ops)
{
	int i = 0;

    for( ; i<MAX_PWR_OPS_SIZE; i ++ )
    {
        if((NULL == pm_ctrl_info.g_stSleepOps[i].funcSleepIn) && (NULL == pm_ctrl_info.g_stSleepOps[i].funcSleepOut))
        {
            pm_ctrl_info.g_stSleepOps[i] = ops;
            break;
        }
    }
    if(MAX_PWR_OPS_SIZE == i)
    {
        return BSP_ERROR;
    }
    else
    {
        return BSP_OK;
    }
}
int pm_register_sleep_ops(unsigned char* pname,PWC_SLEEP_FUNCPTR suspend,PWC_SLEEP_FUNCPTR resume){
	ST_PWC_SLEEP_OPS_STRU ops;
    if((NULL == pname) || ((NULL == suspend) && (NULL==resume)))
    {
        return -1;
    }
    (void)memset_s(&ops,sizeof(ST_PWC_SLEEP_OPS_STRU),0x0,sizeof(ST_PWC_SLEEP_OPS_STRU));
    (void)strncpy((char *)ops.name,(const char *)pname,MAX_PWR_ID_NAME_SIZE-1);
    ops.funcSleepIn = suspend;
    ops.funcSleepOut = resume;
    return sleep_ops_register(ops);
}

void drv_udelay (u32 ms, u32 flag)
{
    u32 start = 0;
    u32 end = 0;
    u32 tmp = 0;

    if(flag == 1)
    {
        start = bsp_get_slice_value();
        do
        {
            end = bsp_get_slice_value();
            tmp = end - start;
        }while(tmp<(ms*32));
    }
}

u32 pm_asm_flag = 0;
u32 pm_in_waiting_pd(void)
{
	return pm_asm_flag;
}
void pm_asm_flag_set(u32 flag)
{
	pm_asm_flag=flag;
}

void balong_pm_enter(suspend_state_t state)
{
    unsigned long flags = 0;
    unsigned int  ret = 0;
    UNUSED(state);

    local_irq_save(flags);

    pm_timer_stamp(pm_stamp_start_addr + STAMP_PM_ENTER_START);
    pm_ctrl_info.pm_om.pm_enter_count++;
    writel(pm_ctrl_info.pm_om.pm_enter_count, pm_stamp_start_addr + PM_ENTER_COUNT);
    if(pm_ctrl_info.sleep_flag)
    {
        if (0 == SRE_LowPowerSuspend(LOW_POWER_TYPE_GIC))
        {
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_DISABLE_GIC);
            bsp_rsracc_suspend_end();
            #ifdef CONFIG_BALONG_L2CACHE
            ret = SRE_LowPowerSuspend(LOW_POWER_TYPE_L2CACHE);
            if(ret)
            {
                pm_printk(BSP_LOG_LEVEL_ERROR,"suspend l2cache failed ,ret = 0x%x\n",ret);	
                BUG();
            }
            #endif
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_BAK_GIC);

            bsp_coresight_suspend();
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_UTRACE_SUSPEND);

           tcxo_suspend();
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_TCXO_SUSPEND);

            pm_save_clk_mtcmos_status();

            (void)modem_pintrl_config(MODEM_PIN_POWERDOWN);
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_PIN_POWERDOWN);
            pm_ctrl_info.mdm_sr_stamp_base->auwCcpuDrvSRStamp[3] = readl(pm_stamp_start_addr + STAMP_AFTER_PIN_POWERDOWN);
            pm_ctrl_info.pm_om.pm_enter_asm_count++;
            m3_mdm_sr_update();
            pm_asm_flag_set(1);
            pm_asm_cpu_go_sleep();
            pm_asm_flag_set(0);
            m3_mdm_pm_dpm_log();
            pm_timer_stamp(pm_stamp_start_addr + STAMP_SLEEP_ASM_OUT);
            pm_ctrl_info.mdm_sr_stamp_base->auwCcpuDrvSRStamp[4] = readl(pm_stamp_start_addr + STAMP_SLEEP_ASM_OUT);
            (void)modem_pintrl_config(MODEM_PIN_NORMAL);
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_PIN_NORMAL);

            tcxo_resume();
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_TCXO_RESUME);

            bsp_coresight_resume();
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_UTRACE_RESUME);
            #ifdef CONFIG_BALONG_L2CACHE
            ret = SRE_LowPowerResume(LOW_POWER_TYPE_L2CACHE);
            if(ret)
            {
                pm_printk(BSP_LOG_LEVEL_ERROR,"resume LOW_POWER_TYPE_L2CACHE fail,ret=0x%x \n",ret);
                BUG();
            }
            #endif
            bsp_rsracc_resume_begin();
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_SLEEPOPS_RESUME);
            ret = SRE_LowPowerResume(LOW_POWER_TYPE_GIC);
            if(ret)
            {
                pm_printk(BSP_LOG_LEVEL_ERROR,"resume LOW_POWER_TYPE_GIC fail,ret=0x%x \n",ret);
                BUG();
            }
            pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_ENABLE_GIC);
            
            /*debug: 如果此flag为偶数，则pm流程只走一次*/
            pm_ctrl_info.sleep_flag = pm_ctrl_info.sleep_flag&1;
            drv_udelay(5, g_nv_drx_delay.drv_0);
        }
        else
        {
        	bsp_rsracc_suspend_end();
            cpufreq_set_max_freq();
        }
    }
    else
    {
        pm_ctrl_info.pm_om.pm_enter_wfi_count++;
        WFI();/*lint !e522*/
    }

    pm_ctrl_info.pm_om.pm_out_count++;
    pm_timer_stamp(pm_stamp_start_addr + STAMP_PM_ENTER_END);
    local_irq_restore(flags);
}


/* 低功耗主流程 */

extern int sysClkRateGet(void);

int pm_suspend(suspend_state_t state)/**/
{
    u64 pm_time = 0;
	u32 delta = 0;
    pm_timer_stamp(pm_stamp_start_addr + STAMP_PM_SUSPEND_START);
    if(0 == pm_ctrl_info.pm_om.dpm_fail_count)
        writel(0, (pm_stamp_start_addr + STAMP_DPM_SUSPEND_FAIL));
    pm_ctrl_info.mdm_sr_stamp_base->auwCcpuDrvSRStamp[1] = readl(pm_stamp_start_addr + STAMP_PM_SUSPEND_START);
	if(bsp_rsracc_suspend_begin())
	{
		bsp_rsracc_suspend_halt();
		return -1;
	}
    if(bsp_dpm_suspend())
    {
        pm_ctrl_info.pm_om.dpm_fail_count++;
        pm_timer_stamp(pm_stamp_start_addr + STAMP_DPM_SUSPEND_FAIL);
        writel(pm_ctrl_info.pm_om.dpm_fail_count, pm_stamp_start_addr + PM_DPM_FAIL_COUNT);
		bsp_rsracc_suspend_halt();
        return -1;
    }
	/*first in pm, record the base tick and base slice,base slice init value is 0*/
	if(!pm_ctrl_info.pm_base_slice)
	{
		pm_ctrl_info.pm_base_tick = osl_tick_get();
		(void)bsp_slice_getcurtime(&pm_ctrl_info.pm_base_slice);
	}
    pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_DPM_SUSPEND);
	pm_ctrl_info.mdm_sr_stamp_base->auwCcpuDrvSRStamp[2] = readl(pm_stamp_start_addr + STAMP_AFTER_DPM_SUSPEND);
    delta = get_timer_slice_delta( \
		readl((u32)(pm_stamp_start_addr + STAMP_PM_SUSPEND_START)), \
		readl((u32)(pm_stamp_start_addr + STAMP_AFTER_DPM_SUSPEND)) );
	if(delta > pm_ctrl_info.pm_om.dpm_suspend_max)
		pm_ctrl_info.pm_om.dpm_suspend_max = delta;
    

   (void)uart_suspend_port(); /*lint !e746*/
    pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_UART_SUSPEND);

    balong_pm_enter(state);

    (void)uart_resume_port(); /*lint !e746*/
    pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_UART_RESUME);

    
    pm_timer_stamp(pm_stamp_start_addr + STAMP_BEFORE_DPM_RESUME);
    #if defined(CONFIG_K3V3_CLK_CRG)
    bsp_tcxo1_set_flag(1);
    #endif
	(void)bsp_slice_getcurtime(&pm_ctrl_info.pm_wakeup_slice);
	pm_time = pm_ctrl_info.pm_wakeup_slice-pm_ctrl_info.pm_base_slice;
    pm_time = (u64)(pm_time + pm_ctrl_info.slice_freq/2)*(u32)sysClkRateGet()/pm_ctrl_info.slice_freq;
    /*time repair*/
	pm_ctrl_info.tick_adjust_before = osl_tick_get();
    osl_tick_set(pm_time+pm_ctrl_info.pm_base_tick);
	pm_ctrl_info.tick_adjust_after = osl_tick_get();
    pm_ctrl_info.mdm_sr_stamp_base->auwCcpuDrvSRStamp[5] = readl(pm_stamp_start_addr + STAMP_BEFORE_DPM_RESUME);
    bsp_dpm_resume();
	bsp_rsracc_resume_end();
    pm_timer_stamp(pm_stamp_start_addr + STAMP_AFTER_DPM_RESUME);
    delta =get_timer_slice_delta( \
		readl((u32)(pm_stamp_start_addr + STAMP_BEFORE_DPM_RESUME)), \
		readl((u32)(pm_stamp_start_addr + STAMP_AFTER_DPM_RESUME)) );
    pm_ctrl_info.mdm_sr_stamp_base->auwCcpuDrvSRStamp[6] = readl(pm_stamp_start_addr + STAMP_AFTER_DPM_RESUME);
	if(delta > pm_ctrl_info.pm_om.dpm_resume_max)
		pm_ctrl_info.pm_om.dpm_resume_max = delta;
    pm_save_drx_timer_stamp();
    drv_udelay(5, g_nv_drx_delay.drv_1);
    return 0;
}
u32 debug_pm_threshold = 0;
static inline void pm_om_record(void)
{
    u32 temp = 0;
    pm_ctrl_info.pm_om.suspend_start_time = readl((u32)(pm_stamp_start_addr + STAMP_PM_SUSPEND_START));
    pm_ctrl_info.pm_om.suspend_end_time = readl((u32)(pm_stamp_start_addr + STAMP_AFTER_SEND_IPC));
	if(pm_ctrl_info.pm_om.suspend_end_time<pm_ctrl_info.pm_om.suspend_start_time)
		return;
    temp = get_timer_slice_delta(pm_ctrl_info.pm_om.suspend_start_time,pm_ctrl_info.pm_om.suspend_end_time);
    if(temp>pm_ctrl_info.pm_om.suspend_max_time){
		pm_ctrl_info.pm_om.suspend_max_start_time = pm_ctrl_info.pm_om.suspend_start_time;
		pm_ctrl_info.pm_om.suspend_max_end_time =pm_ctrl_info.pm_om.suspend_end_time;
		pm_ctrl_info.pm_om.suspend_max_time = temp;
		}
    pm_ctrl_info.pm_om.resume_start_time = readl((u32)(pm_stamp_start_addr + STAMP_PWRUP_CODE_BEGIN));
    pm_ctrl_info.pm_om.resume_end_time = readl((u32)(pm_stamp_start_addr + STAMP_AFTER_DPM_RESUME));
    temp = get_timer_slice_delta(pm_ctrl_info.pm_om.resume_start_time,pm_ctrl_info.pm_om.resume_end_time);
    if(temp>pm_ctrl_info.pm_om.resume_max_time)
		pm_ctrl_info.pm_om.resume_max_time = temp;
    (void)bsp_pm_log_type((u32)PM_OM_PMC,(u32)PM_LOG_NORMAL_RECORD,(u32)sizeof(struct pm_om_info ),(void*)&pm_ctrl_info.pm_om);
}
static inline void idle_pm_record(unsigned int idle_time_ms,unsigned int BBP_sleeptimer ){
	struct idle_pm_s record = {0};
	record.slice = bsp_get_slice_value();
	record.idle_time_ms = idle_time_ms;
	record.bbp_sleeptimer = BBP_sleeptimer;
	(void)bsp_pm_log_type((u32)PM_OM_PMC,(u32)PM_LOG_IDLE_RECORD,(u32)sizeof(struct idle_pm_s),(void*)&record);
}
int bsp_suspend(void)
{
    u32 idle_time_ms=0;;
    unsigned long flags = 0;
    u32 BBP_sleeptimer=0;
    s32 ret = -1;
    local_irq_save(flags);
    osl_task_lock();
    pm_ctrl_info.mdm_sr_stamp_base->auwCcpuDrvSRStamp[0] = bsp_get_slice_value();
    idle_time_ms = get_next_schedule_time();
   BBP_sleeptimer = bsp_bbp_get_wakeup_time();

    if( (idle_time_ms >= pm_ctrl_info.deepsleep_Tth_nv)\
        &&(BBP_sleeptimer>=pm_ctrl_info.TLbbp_sleeptimer_Tth_nv)\
        &&(bsp_bbp_get_gubbp_wakeup_status()==0) )
    {
		run_sleep_ops_suspend_cb();
		ret = pm_suspend(0);
		run_sleep_ops_resume_cb();
  }/*lint !e525*/
    else
    {
        if(debug_pm_threshold)
            pm_printk(BSP_LOG_LEVEL_ERROR,"idle_time_ms=%d ms, BBP_sleeptimer=%d slice \n",idle_time_ms,BBP_sleeptimer);/* [false alarm]:误报 dead code*/
		idle_pm_record(idle_time_ms,BBP_sleeptimer);
    }
    pm_om_record();
    pm_ctrl_info.mdm_sr_stamp_base->auwCcpuDrvSRStamp[7] = bsp_get_slice_value();
    pm_check_time_limit();
    osl_task_unlock();
    local_irq_restore(flags);
    return ret;
}

/* pm_asm_gic_flag: set by pm init ,used in asm */

#define WAKESRC_MAX_NUM 10
struct pm_wake_src_inttrupt_info_s{
	u32 index;
	u32 interrupt;/*lint !e19*/
	char *name;
}pm_wake_src_inttrupt_info[WAKESRC_MAX_NUM];


static inline int bsp_get_pm_dts_value(void){
	 u32 state_offset[6] = {0},boot_addr_shift=0,pm_remap_offset=0,ret = 0,sysctrl_enum=0,id = 0;;
     struct device_node *node = NULL,*child_node = NULL;
	void* sys_baseaddr = NULL;
	int ret_value = 0;
	u32 temp = 0xFFFFFFFF,i=0,pm_boot_reg[2]={0},boot_addr_bit_cfg[2]={0};

    /* for mdma9 boot addr set */
	node = of_find_compatible_node(NULL, NULL,"hisilicon,mdm_a9_boot_addr");
	if(!node)
	{
		pm_printk(BSP_LOG_LEVEL_ERROR,"mdm_a9_boot_addr of_find_compatible_node failed. pm init failed\n");
		return -1;
	}
	ret_value = of_property_read_u32_array(node, "pm_boot_reg", pm_boot_reg,2);
	ret_value |= of_property_read_u32_array(node, "boot_addr_bit_cfg", boot_addr_bit_cfg,2);
	if(ret_value)
	{
		pm_printk(BSP_LOG_LEVEL_ERROR,"pm_boot not find.\n");
		return -1;
	}
	sys_baseaddr=bsp_sysctrl_addr_byindex((BSP_SYSCTRL_INDEX)pm_boot_reg[0]);/*获取系统控制器基地址*/
	if(!sys_baseaddr){
		pm_printk(BSP_LOG_LEVEL_ERROR,"boot_offset_sysctrl get failed\n");
		return -1;
	}
	boot_addr_shift = boot_addr_bit_cfg[0]+boot_addr_bit_cfg[1];
	for(i=boot_addr_bit_cfg[0];i<boot_addr_shift;i++)
		temp &=~((unsigned int)1<<i);/*写启动地址的bit清零*/
	ret = readl((u32)sys_baseaddr+pm_boot_reg[1]);
	ret &= temp;
	writel(ret |(pm_mem_ccore_base_addr>>(32-boot_addr_shift)),(u32)sys_baseaddr+pm_boot_reg[1]);

    /* remap_size may not exit */
	if(of_property_read_u32(node, "remap_size_offset", &pm_remap_offset)){
		pm_printk(BSP_LOG_LEVEL_ERROR,"pm_remap_offset do not need set in this version.\n");
	}
    else{
		ret = readl((u32)sys_baseaddr+pm_remap_offset);
		writel(A9_BOOT_ALIGN_16K|ret,(u32)sys_baseaddr+pm_remap_offset);
	}

    /* for clk state save */
	 node = of_find_compatible_node(NULL, NULL,"hisilicon,clk_state");/*lint !e539*/
	if(!node){
		pm_printk(BSP_LOG_LEVEL_ERROR,"clk_state of_find_compatible_node failed. pm init failed\n");
		return -1;
	}
	if(of_property_read_u32(node, "clk_state_sysctrl", &sysctrl_enum)){
        pm_printk(BSP_LOG_LEVEL_ERROR,"clk_state_sysctrl = 0x%x.\n",sys_baseaddr);
    }
    else{
        sys_baseaddr=bsp_sysctrl_addr_byindex((BSP_SYSCTRL_INDEX)sysctrl_enum);/*获取系统控制器基地址*/
        if(!sys_baseaddr){
            pm_printk(BSP_LOG_LEVEL_ERROR,"clk_state_sysctrl get failed\n");
            return -1;
        }
    }
	if(of_property_read_u32_array(node, "state_offset", state_offset,6)){
		pm_printk(BSP_LOG_LEVEL_ERROR,"state_offset not find. pm init failed\n");
		return -1;
	}
	for(ret = 0;ret <6;ret++)
	{
		mtcmos_state_addr[ret] = sys_baseaddr + state_offset[ret];/*lint !e124*/
	}
	node = of_find_compatible_node(NULL, NULL,"hisilicon,wakesrc_int");
	if(!node)
	{
		pm_printk(BSP_LOG_LEVEL_ERROR,"wakesrc_int of_find_compatible_node failed. pm init failed\n");
		return -1;
	}
	i = 0;
	for_each_child_of_node(node, child_node){
		ret_value = of_property_read_u32(child_node, "index", &id) ;
		pm_wake_src_inttrupt_info[i].index = id;
		ret_value |= of_property_read_u32(child_node, "interrupt", &pm_wake_src_inttrupt_info[i].interrupt) ;/*lint !e50*/
		ret_value |= of_property_read_string(child_node,"wakesource_name",(const char**)&pm_wake_src_inttrupt_info[i].name);/*lint !e545*/	
		i++;
		if(ret_value||i>=WAKESRC_MAX_NUM){
			pm_printk(BSP_LOG_LEVEL_ERROR,"wakesrc_int child read failed,i=%d\n",i);
			return -1;
		}
	}
	node = of_find_compatible_node(NULL, NULL,"hisilicon,pm_check");
	if(node)
	{
		ret_value = of_property_read_u32(node, "mdm_check_offset", &ret) ;
		if(ret_value){
			pm_printk(BSP_LOG_LEVEL_ERROR,"mdm_check_offset read failed\n");
			return -1;
		}
		pm_check_ctrl.sysctrl_check_ref_reg_addr=bsp_sysctrl_addr_byindex(sysctrl_mdm)+ret;
		ret_value = of_property_read_u32(node, "check_sram_flag", &pm_check_ctrl.need_check_sram) ;
		if(!ret_value){
			pm_check_ctrl.need_check_sram=0;
		}
		ret_value = of_property_read_u32(node, "check_mdm_ctrl_flag", &pm_check_ctrl.need_check_mdm_sysctrl) ;
		if(!ret_value){
			pm_check_ctrl.need_check_mdm_sysctrl=0;
		}
	}
	else{
		pm_check_ctrl.need_check_sram=0;
		pm_check_ctrl.need_check_mdm_sysctrl=0;
	}
	return  0;
}
static inline void pm_init_var_in_asm(void){
	ipc_c2m_base_addr = bsp_get_ipc_base_addr()+IPC_CPU_RAW_INT_M3;
    pm_stamp_addr = (u32)bsp_get_stamp_addr();
    pm_stamp_addr_phy =pm_stamp_addr;
    pm_mem_ccore_base_addr = (u32)((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_MDMA9_PM_BOOT);
    pm_stamp_start_addr = (u32)bsp_dump_register_field(DUMP_CP_DRX, "DRX_CCORE", NULL, NULL, PM_DUMP_CCORE_DRX_SIZE, 0)+CDRX_DUMP_PM_OFFSET;
    pm_stamp_pwrup_code_begin = (pm_stamp_start_addr + STAMP_PWRUP_CODE_BEGIN);
    pm_stamp_rstr_mmureg_begin = (pm_stamp_start_addr + STAMP_RSTR_MMUREG_BEGIN);
    pm_bak_mmu_reg_addr = BAK_MMU_REG_ADDR;
    pm_stamp_rstr_mmureg_end = (pm_stamp_start_addr + STAMP_RSTR_MMUREG_END);
    pm_stamp_rstr_coreg_begin = (pm_stamp_start_addr + STAMP_RSTR_COREG_BEGIN);
    pm_bak_arm_co_reg_addr = BAK_ARM_CO_REG_ADDR;
    pm_stamp_rstr_coreg_end = (pm_stamp_start_addr + STAMP_RSTR_COREG_END);
    pm_bak_arm_reg_addr = BAK_ARM_REG_ADDR;
    pm_stamp_sleep_asm_enter	= (pm_stamp_start_addr + STAMP_SLEEP_ASM_ENTER);
    pm_stamp_bak_coreg_begin = (pm_stamp_start_addr + STAMP_BAK_COREG_BEGIN);
    pm_stamp_bak_coreg_end = (pm_stamp_start_addr + STAMP_BAK_COREG_END);
    pm_stamp_bak_mmureg_begin = (pm_stamp_start_addr + STAMP_BAK_MMUREG_BEGIN);
    pm_stamp_bak_mmureg_end = (pm_stamp_start_addr + STAMP_BAK_MMUREG_END);
    pm_stamp_before_send_ipc = (pm_stamp_start_addr + STAMP_BEFORE_SEND_IPC);
    pm_stamp_after_send_ipc = (pm_stamp_start_addr + STAMP_AFTER_SEND_IPC);
    pm_stamp_after_wfi_nop = (pm_stamp_start_addr + STAMP_AFTER_WFI_NOP);
    pm_ctrl_info.stamp_addr = pm_stamp_start_addr;
    pm_c2m_ipc_bit= (0x1<<IPC_MCU_INT_SRC_CCPU_PD);

    pm_hi_uart1_regbase_addr_virt=(u32)bsp_get_uart_base_addr();
    pm_hi_uart1_regbase_addr = pm_hi_uart1_regbase_addr_virt;
}
struct wake_lock pm_wakelock;

static s32 pm_wakeup_icc_cb(u32 id , u32 len, void* context)
{
	int ret = 0;
	struct debug_pm_s read_data;
	ret = bsp_icc_read(id, (u8*)&read_data, len);
	if (ret != (int)sizeof(read_data))
	{
		pm_printk(BSP_LOG_LEVEL_ERROR,"pm icc read error, return length:%x", ret);
		return -1;
	}
	if(PM_WAKEUP == read_data.wake_type){
			debug_pm_wake_lock();
		}
	else if(PM_WAKEUP_THEN_SLEEP== read_data.wake_type){
			debug_pm_wake_unlock();
		}
	else{}
	return 0;
}

void pm_wakeup_init(void)
{
	s32 ret;
	u32 channel_id_set = ((ICC_CHN_MCORE_CCORE << 16) | MCORE_CCORE_FUNC_WAKEUP);
    wake_lock_init(&pm_wakelock, PWRCTRL_SLEEP_TEST, "pm_wakeup");
	ret = bsp_icc_event_register(channel_id_set, (read_cb_func)pm_wakeup_icc_cb, (void *)NULL, (write_cb_func)NULL, (void *)NULL);
    if(ret)
        pm_printk(BSP_LOG_LEVEL_DEBUG,"register icc to mcore error: %d\n", ret);
    /*挂接A核唤醒回调*/
	ret = bsp_icc_event_register( ICC_CHN_IFC << 16 | IFC_RECV_FUNC_WAKEUP, (read_cb_func)pm_wakeup_icc_cb, (void *)NULL, (write_cb_func)NULL, (void *)NULL);/*lint !e539*/
    if(ret)
        pm_printk(BSP_LOG_LEVEL_ERROR,"register icc to ccore error: %d\n", ret);
}

void balong_pm_init(void)
{
    u32 ret=0;
    NV_ID_DRV_ENUM nv_id;
    u32 pm_code_begin = 0,pm_code_size = 0;
	ST_PWC_SWITCH_STRU nv_pwc_switch = {0};
	BSP_DDR_SECT_QUERY_S modem_sr_sect_query;
	BSP_DDR_SECT_INFO_S modem_sr_sect_info = {BSP_DDR_SECT_TYPE_MODEM_SR_STAMP, };
	ST_PWC_PM_DEBUG_CFG_STRU nv_pm_debug_cfg = {0};
	(void)memset_s(pm_ctrl_info.g_stSleepOps,sizeof(pm_ctrl_info.g_stSleepOps),0x0,sizeof(pm_ctrl_info.g_stSleepOps));
    pm_init_var_in_asm();
    pm_ctrl_info.slice_freq = bsp_get_slice_freq();
	(void)bsp_slice_getcurtime(&pm_ctrl_info.pm_init_slice);
	pm_ctrl_info.pm_init_tick = osl_tick_get();
	modem_sr_sect_query.enSectType = BSP_DDR_SECT_TYPE_MODEM_SR_STAMP;
	(void)mdrv_get_fix_ddr_addr(&modem_sr_sect_query, &modem_sr_sect_info);
	pm_ctrl_info.mdm_sr_stamp_base = (T_MODEM_SR_STAMP_STRU *)((unsigned long)modem_sr_sect_info.pSectVirtAddr);
    nv_id = NV_ID_DRV_PM;
    ret = bsp_nvm_read(nv_id, (u8 *)(&g_nv_pm_config), sizeof(DRV_NV_PM_TYPE));
    if(ret!=0)
    {
        pm_printk(BSP_LOG_LEVEL_ERROR,"bsp_nvm_read FAILED id=0x%x,ret=%d \n",nv_id,ret);
        return;
    }

    nv_id = NV_ID_DRV_DRX_DELAY;
    ret = bsp_nvm_read(nv_id, (u8 *)&g_nv_drx_delay, sizeof(DRV_DRX_DELAY_STRU));
    if(ret != 0)
    {
        pm_printk(BSP_LOG_LEVEL_ERROR,"bsp_nvm_read FAILED id=0x%x,ret=%d \n",nv_id,ret);
        return;
    }

    ret = bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)(&nv_pwc_switch), sizeof(ST_PWC_SWITCH_STRU));/*lint !e713*/
    if(ret!=0)
    {
        pm_printk(BSP_LOG_LEVEL_ERROR,"NV_ID_DRV_NV_PWC_SWITCH:D10B read failure!\n");
    }

    pm_ctrl_info.deepsleep_nv =nv_pwc_switch.deepsleep;//1;
    pm_ctrl_info.deepsleep_Tth_nv =g_nv_pm_config.deepsleep_Tth;//100;
    pm_ctrl_info.TLbbp_sleeptimer_Tth_nv = g_nv_pm_config.TLbbp_Tth;//320;
    ret = bsp_nvm_read(NV_ID_DRV_PM_DEBUG_CFG, (u8 *)(&nv_pm_debug_cfg), sizeof(ST_PWC_PM_DEBUG_CFG_STRU));/*lint !e713*/
    if(!ret)
    {
		pm_ctrl_info.sr_time_limit_flag = nv_pm_debug_cfg.sr_time_ctrl;
		pm_ctrl_info.bug_reset_modem_flag = nv_pm_debug_cfg.bugon_reset_modem;
		pm_ctrl_info.print_to_ddr_flag = nv_pm_debug_cfg.print_to_ddr;
		pm_ctrl_info.dpm_suspend_threshold = nv_pm_debug_cfg.dpm_suspend_time_threshold;
		pm_ctrl_info.dpm_resume_threshold = nv_pm_debug_cfg.dpm_resume_time_threshold;
		pm_ctrl_info.pm_suspend_threshold = nv_pm_debug_cfg.pm_suspend_time_threshold;
		pm_ctrl_info.pm_resume_threshold = nv_pm_debug_cfg.pm_resume_time_threshold;
    }
	else
        pm_printk(BSP_LOG_LEVEL_ERROR,"NV_ID_DRV_PM_DEBUG_CFG:D14B not exist,use default!\n");

    pm_stamp_init();
    //pm_asm_gic_flag = pm_ctrl_info.gic_flag; /* flag for pm_asm_sleep.s */
    pm_code_begin = (u32)pm_asm_boot_code_begin;
    pm_code_size = (u32)pm_asm_sleep_end-pm_code_begin;
	/* copy the pm_asm_sleep code to PM MEMORY */
    (void)memcpy_s((void*)PM_MEM_CCORE_BASE_ADDR,(size_t)(pm_code_size+PM_ASM_CODE_COPY_OFFSET),(void*)pm_code_begin,(size_t)(pm_code_size+PM_ASM_CODE_COPY_OFFSET));/*lint !e534*/
 	if(bsp_get_pm_dts_value()){
		pm_printk(BSP_LOG_LEVEL_ERROR," ccore pm init failed \n");
		return;
 	}
    pm_wakeup_init();
	if(bsp_device_pm_add(&pm_device))
	{
		pm_printk(BSP_LOG_LEVEL_ERROR," pm_device dpm add failed \n");
		return;
	}
	/* NV control , system will not suspend if ops is not set */
    if(0==pm_ctrl_info.deepsleep_nv){
        pm_printk(BSP_LOG_LEVEL_ERROR," pm_NV [sleep] not open \n");
        return;
    }
    else{
        cpuidle_set_deepsleep_ops(bsp_suspend);
        pm_printk(BSP_LOG_LEVEL_ERROR," ccore pm init ok \n");
    }

}


/*
动态设置唤醒源
参数 wake_src 对应 drv_pm.h 中的 enum pm_wake_src
*/
#define ENABLE_WAKE_SRC     (PM_TYEP_CSET_WSRC)
#define DISABLE_WAKE_SRC    (PM_TYEP_CUNSET_WSRC)

void pm_set_wake_src(enum pm_wake_src wake_src, T_PM_TYPE pm_type)
{
    T_PM_MAIL pm_msg;
    u32 channel_id = (ICC_CHN_MCORE_CCORE << 16) | MCU_CCORE_WSRC;
	u32 ret = 0,i=0;
    u32 int_id = 0;
    u32 msglen = 0;
	if(wake_src>=PM_WAKE_SRC_BUT)
	{
		pm_printk(BSP_LOG_LEVEL_ERROR,"wake_src id error\n");
		return;
	}
	for(i=0;i<WAKESRC_MAX_NUM;i++)
	{
		if((u32)wake_src == pm_wake_src_inttrupt_info[i].index){
			int_id = pm_wake_src_inttrupt_info[i].interrupt;
			break;
		}
	}
    pm_msg.type = pm_type;
    pm_msg.addr = int_id;
	msglen = sizeof(T_PM_MAIL);

	ret = (u32)bsp_icc_send(ICC_CPU_MCU, channel_id, (u8*)(&pm_msg), msglen);
	if(ret != msglen)
	{
		pm_printk(BSP_LOG_LEVEL_ERROR,"PM icc_send_mcore error\n");
		return;
	}
    return;
}

void pm_wake_src_record(T_PM_TYPE set_type,enum pm_wake_src wake_src){
	struct pm_wake_src_s record = {0,0,0,0};
	record.time_slice = bsp_get_slice_value();
	record.set_type = (unsigned int)set_type;
	record.wake_src = (unsigned int)wake_src;
	record.task_id = osl_task_self();
	(void)bsp_pm_log_type((u32)PM_OM_PMC,(u32)PM_LOG_SET_WAKE_SRC_RECORD,(u32)sizeof(struct pm_wake_src_s ),(void*)&record);
}
void pm_enable_wake_src(enum pm_wake_src wake_src)
{
    pm_wake_src_record(ENABLE_WAKE_SRC,wake_src);
    pm_set_wake_src(wake_src,ENABLE_WAKE_SRC);
}

void pm_disable_wake_src(enum pm_wake_src wake_src)
{
     pm_wake_src_record(DISABLE_WAKE_SRC,wake_src);
     pm_set_wake_src(wake_src,DISABLE_WAKE_SRC);
}


