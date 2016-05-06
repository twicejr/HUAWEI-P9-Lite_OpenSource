/*lint --e{123,506,586,774}*/
#include <osl_bug.h>
#include <bsp_pm_om.h>
#include <bsp_icc.h>
#include <bsp_wakelock.h>
#include "pm.h"
extern struct pm_info pm_ctrl_info;
extern int sysClkRateGet(void);
extern u32 pm_asm_gic_flag; /* debug, 1:gic suspend ,0:gic not suspend,and ipc not send */
extern u32 pm_stamp_start_addr;

void set_pm_threshold(u32 deepsleep_Tth,u32 TLbbp_Tth)
{
    pm_ctrl_info.deepsleep_Tth_nv = deepsleep_Tth;
    pm_ctrl_info.TLbbp_sleeptimer_Tth_nv = TLbbp_Tth;
}
void set_pm_debug_flag(u32 gic_flag,u32 sleep_flag)
{
    pm_ctrl_info.gic_flag= gic_flag;
    pm_asm_gic_flag = pm_ctrl_info.gic_flag;
    pm_ctrl_info.sleep_flag= sleep_flag;
}
void tick_show(void)
{
	u64 ret = 0;
	pm_printk(BSP_LOG_LEVEL_ERROR,"before adjust tick(low 32bit) = 0x%x \n",(u32)pm_ctrl_info.tick_adjust_before);
	pm_printk(BSP_LOG_LEVEL_ERROR,"before adjust tick(high 32bit) = 0x%x \n",(u32)(pm_ctrl_info.tick_adjust_before>>32));
	pm_printk(BSP_LOG_LEVEL_ERROR,"after adjust tick(low 32bit) = 0x%x \n",(u32)pm_ctrl_info.tick_adjust_after);
	pm_printk(BSP_LOG_LEVEL_ERROR,"after adjust tick(high 32bit) = 0x%x \n",(u32)(pm_ctrl_info.tick_adjust_after>>32));
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm_wakeup_slice(low 32bit) = 0x%x \n",(u32)pm_ctrl_info.pm_wakeup_slice);
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm_wakeup_slice(high 32bit) = 0x%x \n",(u32)(pm_ctrl_info.pm_wakeup_slice>>32));
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm base tick(low 32bit) = 0x%x \n",(u32)pm_ctrl_info.pm_base_tick);
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm base tick(high 32bit) = 0x%x \n",(u32)(pm_ctrl_info.pm_base_tick>>32));
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm base slice(low 32bit) = 0x%x \n",(u32)pm_ctrl_info.pm_base_slice);
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm base slice(high 32bit) = 0x%x \n",(u32)(pm_ctrl_info.pm_base_slice>>32));
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm init slice(low 32bit) = 0x%x \n",(u32)pm_ctrl_info.pm_init_slice);
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm init slice(high 32bit) = 0x%x \n",(u32)(pm_ctrl_info.pm_init_slice>>32));
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm init tick(low 32bit) = 0x%x \n",(u32)pm_ctrl_info.pm_init_tick);
	pm_printk(BSP_LOG_LEVEL_ERROR,"pm init tick(high 32bit) = 0x%x \n",(u32)(pm_ctrl_info.pm_init_tick>>32));
	ret = osl_tick_get();
	pm_printk(BSP_LOG_LEVEL_ERROR,"os tick now(low 32bit) = 0x%x \n",(u32)ret);
	pm_printk(BSP_LOG_LEVEL_ERROR,"os tick now(high 32bit) = 0x%x \n",(u32)(ret>>32));
	ret = (pm_ctrl_info.pm_wakeup_slice-pm_ctrl_info.pm_init_slice+pm_ctrl_info.slice_freq/2)*(u32)sysClkRateGet()/pm_ctrl_info.slice_freq+pm_ctrl_info.pm_init_tick;
	pm_printk(BSP_LOG_LEVEL_ERROR,"calculate accuracy tick compare tick_adjust_after to judge tick compensation:\n"); 
	pm_printk(BSP_LOG_LEVEL_ERROR,"calculate accuracy tick:\n \
	(pm_wakeup_slice-pm_init_slice+slice_freq/2)*100/slice_freq+pm_init_tick\n");
	pm_printk(BSP_LOG_LEVEL_ERROR,"low 32bit = 0x%x \n  high 32bit = 0x%x \n",(u32)ret,(u32)(ret>>32));
}

void pm_print_debug_info(void)
{
    pm_printk(BSP_LOG_LEVEL_ERROR,"============= pm_ctrl_info ============\n");
    pm_printk(BSP_LOG_LEVEL_ERROR," pm_enter_count      %d\n", pm_ctrl_info.pm_om.pm_enter_count);
	pm_printk(BSP_LOG_LEVEL_ERROR," dpm_fail_count      %d\n", pm_ctrl_info.pm_om.dpm_fail_count);
    pm_printk(BSP_LOG_LEVEL_ERROR," pm_enter_asm_count  %d\n", pm_ctrl_info.pm_om.pm_enter_asm_count);
    pm_printk(BSP_LOG_LEVEL_ERROR," pm_enter_wfi_count  %d\n", pm_ctrl_info.pm_om.pm_enter_wfi_count);
    pm_printk(BSP_LOG_LEVEL_ERROR," pm_out_count        %d\n", pm_ctrl_info.pm_om.pm_out_count);
    pm_printk(BSP_LOG_LEVEL_ERROR," stamp_addr 0x%x\n", pm_ctrl_info.stamp_addr);
    pm_printk(BSP_LOG_LEVEL_ERROR," gic_flag        %d\n", pm_ctrl_info.gic_flag);
    pm_printk(BSP_LOG_LEVEL_ERROR," sleep_flag      %d\n", pm_ctrl_info.sleep_flag);
    pm_printk(BSP_LOG_LEVEL_ERROR," deepsleep_nv    %d\n", pm_ctrl_info.deepsleep_nv);
    pm_printk(BSP_LOG_LEVEL_ERROR," deepsleep_Tth_nv        %d\n", pm_ctrl_info.deepsleep_Tth_nv);
    pm_printk(BSP_LOG_LEVEL_ERROR," TLbbp_sleeptimer_Tth_nv %d\n", pm_ctrl_info.TLbbp_sleeptimer_Tth_nv);
}

void pm_debug_clear_stamp(void)
{
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_START_ADDR =0x%x \n",pm_stamp_start_addr +STAMP_START_ADDR);
	/* 后续请改成memset */
    /*start form pm_suspend()*/
    *(u32*)(pm_stamp_start_addr + STAMP_PM_SUSPEND_START  ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_DPM_SUSPEND_FAIL  ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_DPM_SUSPEND ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_UART_SUSPEND) = 0;
    /* pm enter */
    *(u32*)(pm_stamp_start_addr + STAMP_PM_ENTER_START      ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_DISABLE_GIC   ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_BAK_GIC       ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_UTRACE_SUSPEND) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_TCXO_SUSPEND  ) = 0;
    /*in sleep ASM power down*/
    *(u32*)(pm_stamp_start_addr + STAMP_SLEEP_ASM_ENTER  ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_BAK_COREG_BEGIN  ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_BAK_COREG_END    ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_BAK_MMUREG_BEGIN ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_BAK_MMUREG_END   ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_BEFORE_SEND_IPC  ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_SEND_IPC   ) = 0;
    /* after wfi, should not be stamped */
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_WFI_NOP) = 0;
    /*in sleep ASM power up*/
    *(u32*)(pm_stamp_start_addr + STAMP_PWRUP_CODE_BEGIN ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_RSTR_MMUREG_BEGIN) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_RSTR_MMUREG_END  ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_RSTR_COREG_BEGIN ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_RSTR_COREG_END   ) = 0;
    /* out from sleep ASM,in pm enter */
    *(u32*)(pm_stamp_start_addr + STAMP_SLEEP_ASM_OUT      ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_TCXO_RESUME  ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_UTRACE_RESUME) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_ENABLE_GIC   ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_SLEEPOPS_RESUME ) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_PM_ENTER_END       ) = 0;
    /* out from pm enter, in pm suspend*/
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_UART_RESUME) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_BEFORE_DPM_RESUME) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_AFTER_DPM_RESUME ) = 0;
    /* stamp for debug     */
    *(u32*)(pm_stamp_start_addr + STAMP_DEBUG_1) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_DEBUG_2) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_DEBUG_3) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_DEBUG_4) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_DEBUG_5) = 0;
    *(u32*)(pm_stamp_start_addr + STAMP_DEBUG_6) = 0;
}

void pm_print_sleepops_stamp(void)
{
	u32 i = 0;
	for(i=0;i<MAX_PWR_OPS_SIZE;i++){
		 pm_printk(BSP_LOG_LEVEL_ERROR,"ops name =%s \n",pm_ctrl_info.g_stSleepOps[i].name);
		 pm_printk(BSP_LOG_LEVEL_ERROR,"max suspend time =0x%x \n",pm_ctrl_info.g_stSleepOps[i].max_suspend_time_duration);
		 pm_printk(BSP_LOG_LEVEL_ERROR,"max resume time = 0x%x \n",pm_ctrl_info.g_stSleepOps[i].max_resume_time_duration);
		 pm_printk(BSP_LOG_LEVEL_ERROR,"latest suspend start =0x%x \n",pm_ctrl_info.g_stSleepOps[i].latest_suspend_time[0]);
		 pm_printk(BSP_LOG_LEVEL_ERROR,"latest suspend end =0x%x \n",pm_ctrl_info.g_stSleepOps[i].latest_suspend_time[1]);
		 pm_printk(BSP_LOG_LEVEL_ERROR,"latest resume start =0x%x \n",pm_ctrl_info.g_stSleepOps[i].latest_resume_time[0]);
		 pm_printk(BSP_LOG_LEVEL_ERROR,"latest resume end =0x%x \n",pm_ctrl_info.g_stSleepOps[i].latest_resume_time[1]);
	}
}
void pm_debug_print_stamp(void)
{
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_START_ADDR =0x%x \n",STAMP_START_ADDR);
    /*start form pm_suspend()*/
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_PM_SUSPEND_START     =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_PM_SUSPEND_START));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_DPM_SUSPEND    =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_DPM_SUSPEND));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_UART_SUSPEND   =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_UART_SUSPEND));
    /* pm enter */
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_PM_ENTER_START       =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_PM_ENTER_START));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_DISABLE_GIC    =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_DISABLE_GIC));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_BAK_GIC        =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_BAK_GIC));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_UTRACE_SUSPEND =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_UTRACE_SUSPEND));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_TCXO_SUSPEND   =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_TCXO_SUSPEND));
    /*in sleep ASM power down*/
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_SLEEP_ASM_ENTER      =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_SLEEP_ASM_ENTER));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_BAK_COREG_BEGIN      =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_BAK_COREG_BEGIN));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_BAK_COREG_END        =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_BAK_COREG_END));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_BAK_MMUREG_BEGIN     =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_BAK_MMUREG_BEGIN));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_BAK_MMUREG_END       =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_BAK_MMUREG_END));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_BEFORE_SEND_IPC      =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_BEFORE_SEND_IPC));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_SEND_IPC       =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_SEND_IPC));
    /* after wfi, should not be stamped */
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_WFI_NOP        =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_WFI_NOP));
    /*in sleep ASM power up*/
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_PWRUP_CODE_BEGIN     =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_PWRUP_CODE_BEGIN));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_RSTR_MMUREG_BEGIN    =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_RSTR_MMUREG_BEGIN));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_RSTR_MMUREG_END      =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_RSTR_MMUREG_END));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_RSTR_COREG_BEGIN     =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_RSTR_COREG_BEGIN));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_RSTR_COREG_END       =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_RSTR_COREG_END));
    /* out from sleep ASM,in pm enter */
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_SLEEP_ASM_OUT        =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_SLEEP_ASM_OUT));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_TCXO_RESUME    =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_TCXO_RESUME));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_UTRACE_RESUME  =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_UTRACE_RESUME));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_RSTR_GIC       =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_SLEEPOPS_RESUME));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_ENABLE_GIC     =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_ENABLE_GIC));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_PM_ENTER_END         =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_PM_ENTER_END));
    /* out from pm enter, in pm suspend*/
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_UART_RESUME    =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_UART_RESUME));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_BEFORE_DPM_RESUME    =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_BEFORE_DPM_RESUME));
    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_AFTER_DPM_RESUME     =0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_AFTER_DPM_RESUME));
	
	pm_printk(BSP_LOG_LEVEL_ERROR," pm suspend max 			  =0x%x\n", pm_ctrl_info.pm_om.suspend_max_time);
	pm_printk(BSP_LOG_LEVEL_ERROR," pm resume max 			  =0x%x\n", pm_ctrl_info.pm_om.resume_max_time);
	pm_printk(BSP_LOG_LEVEL_ERROR," dpm suspend max			  =0x%x\n", pm_ctrl_info.pm_om.dpm_suspend_max);
	pm_printk(BSP_LOG_LEVEL_ERROR," dpm resume max			  =0x%x\n", pm_ctrl_info.pm_om.dpm_resume_max);

    pm_printk(BSP_LOG_LEVEL_ERROR,"STAMP_DEBUG_1->     =0x%x 0x%x 0x%x 0x%x \n",  *(u32*)(pm_stamp_start_addr + STAMP_DEBUG_1),
                    *(u32*)(pm_stamp_start_addr + STAMP_DEBUG_2),
					*(u32*)(pm_stamp_start_addr + STAMP_DEBUG_3),
					*(u32*)(pm_stamp_start_addr + STAMP_DEBUG_4));
}
void pm_show(void){
	pm_printk(BSP_LOG_LEVEL_ERROR," print debug info,call func: 	pm_print_debug_info\n");
	pm_printk(BSP_LOG_LEVEL_ERROR," print stamp info,call func: 	pm_debug_print_stamp\n");
	pm_printk(BSP_LOG_LEVEL_ERROR," clear stamp info,call func: 	pm_debug_clear_stamp\n");
	pm_printk(BSP_LOG_LEVEL_ERROR," stop c core sleep,call func: 	debug_pm_wake_lock\n");
	pm_printk(BSP_LOG_LEVEL_ERROR," allow c core sleep,call func: 	debug_pm_wake_unlock\n");
	pm_printk(BSP_LOG_LEVEL_ERROR," sleep ops info,call func: 	pm_print_sleepops_stamp\n");
	pm_printk(BSP_LOG_LEVEL_ERROR," wakeup acore,call func: 		pm_wakeup_acore 0/1(0:acore still wake,1:acore wakeup then sleep)\n");
}

extern struct wake_lock pm_wakelock;
void debug_pm_wake_unlock(void)
{
    wake_unlock(&pm_wakelock);
}
void debug_pm_wake_lock(void)
{
    wake_lock(&pm_wakelock);
}


s32 pm_wakeup_acore(enum debug_wake_type type)
{
	u32 channel_id = (ICC_CHN_IFC << 16) | IFC_RECV_FUNC_WAKEUP;
	s32 ret = 0;
    struct debug_pm_s pm_msg;
	u32 msglen = sizeof(pm_msg);

	pm_msg.wake_type = type;
	ret = bsp_icc_send(ICC_CPU_APP, channel_id, (u8*)(&pm_msg), msglen);
	if((u32)ret != msglen)
	{
		return -1;
	}
    return 0;
}
/* print clk/mtcmos status saved */
void pm_print_clk_mtcmos_status(void)
{
    pm_printk(BSP_LOG_LEVEL_ERROR,"CHECK_STATUS_START =0x%x \n",  *(u32*)(pm_stamp_start_addr + CHECK_STATUS_START));
    pm_printk(BSP_LOG_LEVEL_ERROR,"CHECK_CRG_CLKSTAT1 =0x%x \n",  *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT1));
    pm_printk(BSP_LOG_LEVEL_ERROR,"CHECK_CRG_CLKSTAT2 =0x%x \n",  *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT2));
    pm_printk(BSP_LOG_LEVEL_ERROR,"CHECK_CRG_CLKSTAT3 =0x%x \n",  *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT3));
    pm_printk(BSP_LOG_LEVEL_ERROR,"CHECK_CRG_CLKSTAT4 =0x%x \n",  *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT4));
    pm_printk(BSP_LOG_LEVEL_ERROR,"CHECK_CRG_CLKSTAT5 =0x%x \n",  *(u32*)(pm_stamp_start_addr + CHECK_CRG_CLKSTAT5));
    pm_printk(BSP_LOG_LEVEL_ERROR,"CHECK_PWR_STAT1    =0x%x \n",  *(u32*)(pm_stamp_start_addr + CHECK_PWR_STAT1   ));
}

extern void bsp_dpm_show(void);
static void time_check(void)
{
	static u32 limit_count = 0;
	/*1. check dpm suspend time is or not overflow threshold*/
	/*2. check dpm resume time is or not overflow threshold*/
	/*3. check pm suspend time is or not overflow threshold*/
	/*4. check pm resume time is or not overflow threshold*/
	if((pm_ctrl_info.pm_om.dpm_suspend_max > pm_ctrl_info.dpm_suspend_threshold)\
		||(pm_ctrl_info.pm_om.dpm_resume_max > pm_ctrl_info.dpm_resume_threshold)\
		||(pm_ctrl_info.pm_om.suspend_max_time>pm_ctrl_info.pm_suspend_threshold)\
		||(pm_ctrl_info.pm_om.resume_max_time>pm_ctrl_info.pm_resume_threshold))
	{
		limit_count++;
		pm_printk(BSP_LOG_LEVEL_ERROR,"pm time over flow\n");
		if(pm_ctrl_info.print_to_ddr_flag)
		{
			writel(limit_count,(u32)PM_SLICE_OVERFLOW_CNT);
			print_stamp((u32)PM_SLICE_OVERFLOW_CNT);
		}
		else
		{
			pm_debug_print_stamp();
			bsp_dpm_show();
		}
		if(pm_ctrl_info.bug_reset_modem_flag)
			BUG_ON(1);
	}
}
void pm_check_time_limit(void)
{
	u32 temp[2]={0};
	if(pm_ctrl_info.sr_time_limit_flag)
	{
		temp[0] = readl(pm_stamp_start_addr + STAMP_PM_ENTER_START);
		temp[1] = readl(pm_stamp_start_addr + STAMP_DPM_SUSPEND_FAIL);
		/*if dpm suspend failed,no need check,derect return*/
		if(temp[1]!=0 && get_timer_slice_delta(temp[0],temp[1])>0)
			return;
		time_check();
	}
}

