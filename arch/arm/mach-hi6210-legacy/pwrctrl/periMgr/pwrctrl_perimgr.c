

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_perimgr.h>
#include <mach/pwrctrl/pwrctrl_sleepmgr.h>
#include <mach/pwrctrl/pwrctrl_sleep.h>

#ifndef WIN32
#include <linux/string.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/memory.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <linux/delay.h>
#include <linux/pm_qos_params.h>
#include <mach/irqs.h>
#include <asm/hardware/gic.h>
#include <asm/hardware/arm_timer.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <mach/io.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* the input clock frequency of timer */
u32_t g_ulPWRCTRLTimerClock[PWRCTRL_ACPU_TIMER_TOTAL_NUM] =
{
    PWRCTRL_TIMECLK_19M2,       /*timer0 0-0*/
    PWRCTRL_TIMECLK_19M2,
    PWRCTRL_TIMECLK_32K,        /*timer2 1-0*/
    PWRCTRL_TIMECLK_32K,
    PWRCTRL_TIMECLK_19M2,       /*timer4 2-0*/
    PWRCTRL_TIMECLK_32K,
    PWRCTRL_TIMECLK_19M2,       /*timer6 3-0*/
    PWRCTRL_TIMECLK_19M2,
    PWRCTRL_TIMECLK_19M2,       /*timer8 4-0*/
    PWRCTRL_TIMECLK_19M2,                           /*resev*/
    PWRCTRL_TIMECLK_19M2,       /*timer10 5-0*/     /*hifi*/
    PWRCTRL_TIMECLK_19M2,                           /*hifi*/
    PWRCTRL_TIMECLK_32K,        /*timer12 6-0*/
    PWRCTRL_TIMECLK_19M2,                           /*resev*/
    PWRCTRL_TIMECLK_19M2,       /*timer14 7-0*/     /*resev*/
    PWRCTRL_TIMECLK_19M2,                           /*resev*/
    PWRCTRL_TIMECLK_19M2,       /*timer16 8-0*/     /*resev*/
    PWRCTRL_TIMECLK_19M2,                           /*resev*/
};
/* the remap base address of timer */
u32_t g_ulPWRCTRLTimerAddr[PWRCTRL_ACPU_TIMER_TOTAL_NUM]={0};

extern int pwrctrl_hotplug_timer_exit ( void );

/*****************************************************************************
  3 函数实现
*****************************************************************************/

static int pm_reboot_notify(struct notifier_block *nb, unsigned long event, void *buf)
{
    /*struct pm_qos_request_list pm_reboot_maxcpu; */
    unsigned int cpu_online_num;
    /*pm_reboot_maxcpu.pm_qos_class = 0;*/
    
    if ((event == SYS_RESTART) || (event == SYS_POWER_OFF) || (event == SYS_HALT)) {
        cpu_online_num = num_online_cpus();
        printk("%s:%d cpu:%d\n", __func__, event, cpu_online_num);
        /*pm_qos_add_request(&pm_reboot_maxcpu, PM_QOS_CPU_NUMBER_MAX, 1);*/
        pwrctrl_hotplug_timer_exit();
        
        msleep(200);
        cpu_online_num = num_online_cpus();
        printk("%s:%d cpu:%d\n", __func__, event, cpu_online_num);
    }


    return NOTIFY_OK;
}

struct notifier_block pm_reboot_nb = {
    .notifier_call = pm_reboot_notify,
    .next       = NULL,
    .priority   = INT_MAX,
};


u32_t pwrctrl_get_timer_count( void_t )
{
    return pwrctrl_read_reg32(PWRCTRL_SLICE_TIMER_VADDR);
}




u32_t pwrctrl_get_timer_base_addr( u32_t timerId)
{
    return g_ulPWRCTRLTimerAddr[timerId];
}

s32_t pwrctrl_timer_addr_remap(void)
{
    int i = 0;
    u32_t timerMap = 0;

    for(i=0;i<PWRCTRL_ACPU_TIMER_TOTAL_NUM;i++)
    {
        timerMap = ioremap((SOC_Timer0_BASE_ADDR+0x1000*i),SZ_4K);
        if(NULL == timerMap)
        {
            return RET_ERR;
        }
        g_ulPWRCTRLTimerAddr[i] = SOC_TIMER_TIMERN_LOAD_ADDR(timerMap,0);
        //printk(KERN_INFO "pwrctrl_timer_addr_remap g_ulPWRCTRLTimerAddr %d :0x%x\n",i,g_ulPWRCTRLTimerAddr[i]);
        g_ulPWRCTRLTimerAddr[i+1] = SOC_TIMER_TIMERN_LOAD_ADDR(timerMap,1);
        //printk(KERN_INFO "pwrctrl_timer_addr_remap g_ulPWRCTRLTimerAddr %d :0x%x\n",i+1,g_ulPWRCTRLTimerAddr[i+1]);
        i++;

    }
    return RET_OK;
}


u32_t  pwrctrl_get_timer_clk( u32_t timerId)
{
    return g_ulPWRCTRLTimerClock[timerId];
}



u32_t pwrctrl_get_timer_active( u32_t timerId)
{
    u32_t ulControlVal;
    u32_t ulTimerValue;
    u32_t ulTimerAddr = 0;

    ulTimerAddr = pwrctrl_get_timer_base_addr(timerId);
    ulControlVal = pwrctrl_read_reg32(PWRCTRL_TIMER_CONTROL_ADDR(ulTimerAddr));
    ulTimerValue = pwrctrl_read_reg32(PWRCTRL_TIMER_VALUE_ADDR(ulTimerAddr));

    if((0 == (ulControlVal & PWRCTRL_ENABLE)) || (0 == (ulControlVal & PWRCTRL_INTENABLE))
        || ((0 == (ulControlVal & PWRCTRL_FREE)) && (0 == ulTimerValue)) )
    {
        return PWRCTRL_FALSE;
    }

    return PWRCTRL_TRUE;
}



u32_t pwrctrl_get_timer_cnt( u32_t timerId)
{
    u32_t load_val = 0;
    u32_t curr_val = 0;
    u32_t ulTimerAddr = 0;

    ulTimerAddr = pwrctrl_get_timer_base_addr(timerId);
    curr_val = pwrctrl_read_reg32(PWRCTRL_TIMER_VALUE_ADDR(ulTimerAddr));

    /*
     * Here we need do one more step to check if current timer count is valid.
     * If curr_val>load_val, we think curr_val is invalid and return the
     * load_val. It is a SOC bug, but we just evade it.
     */
    load_val = pwrctrl_read_reg32(PWRCTRL_TIMER_LOAD_ADDR(ulTimerAddr));

    return curr_val>load_val ? load_val : curr_val;
}



s32_t pwrctrl_sleep_mgr_get_next_schedule_time( u32_t ulAllTimer,
                                           u32_t *pTimerID, u32_t *pNextScheduleTime)
{
    u32_t ulTimerValue = 0;
    u32_t i = 0;
    u32_t ulState = 0;
    u32_t ulTimclk = 0;

    u32_t ulCount = 0;
    u32_t ulTimerId = PWRCTRL_MAX_TIME;
    u32_t ulNextScheduleTime = PWRCTRL_MAX_TIME;

    if ((PWRCTRL_TRUE != ulAllTimer) && (PWRCTRL_FALSE != ulAllTimer))
    {
        (int)PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_get_next_scheduletime: ulAllTimer[%x] is err\n", ulAllTimer,0, 0, 0, 0, 0);
        return (s32_t)RET_ERR;
    }

    if (NULL == pTimerID)
    {
        (int)PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_get_next_scheduletime: pTimerID is null\n", 0,0, 0, 0, 0, 0);
        return (s32_t)RET_ERR;
    }

    if (NULL == pNextScheduleTime)
    {
        (int)PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_get_next_scheduletime: pNextScheduleTime is null\n", 0,0, 0, 0, 0, 0);
        return (s32_t)RET_ERR;
    }

    for (i = 0; i < PWRCTRL_ACPU_TIMER_TOTAL_NUM; i++)
    {
        ulTimerValue = 0;
        ulState = pwrctrl_get_timer_active(i);

        /*if the timer is disable*/
        if (PWRCTRL_FALSE == ulState)
        {
            /*do nothing,see next timer*/
            continue;
        }

        /*get the TIMCLK from SC .spc2.0 is 19.2M*/
        /*时钟源频率*/
        ulTimclk = pwrctrl_get_timer_clk(i);

        /*get the timer div*/
        /*分频因子*/

        /*ulDIV = pwrctrl_get_timer_div(g_ulPWRCTRLTimerAddr[i]);*/

        /*get the timer count*/
        /*获得剩余计数值*/
        ulCount = pwrctrl_get_timer_cnt(i);

        /*calc the remain time, unit is ms */
        ulTimerValue = (ulCount * PWRCTRL_THOUSAND_TIME) / (ulTimclk / PWRCTRL_THOUSAND_TIME);

        if (ulNextScheduleTime > ulTimerValue)
        {
            ulNextScheduleTime = ulTimerValue;
            ulTimerId = i;
        }
    }

    /*BBP TIMER IS TRANSLATE INTO TIMER*/

    /*output the next schedule*/
    *pNextScheduleTime = ulNextScheduleTime;

    *pTimerID = ulTimerId;

    PRINT_PWC_DBG(PWC_SWITCH_CPUIDLE, "the timerID is %d, the left time is %d[ms]\n", ulTimerId,ulNextScheduleTime, 0, 0, 0, 0);

    /*Log timer id and timer value to Exc space.*/

    return (s32_t)RET_OK;
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
