/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_perimgr.c
  版 本 号   : 初稿
  作    者   : 刘永富 56193
  生成日期   : 2012年7月25日
  最近修改   :
  功能描述   : 外设低功耗模块
  函数列表   :
              pwrctrl_get_timer_active
              pwrctrl_get_timer_base_addr
              pwrctrl_get_timer_clk
              pwrctrl_get_timer_cnt

  修改历史   :
  1.日    期   : 2012年7月25日
    作    者   : 刘永富 56193
    修改内容   : 创建文件

******************************************************************************/

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

/*****************************************************************************
 函 数 名  : pwrctrl_get_timer_count
 功能描述  : 获取TIMER的当前计数值(sliceTimer)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 定时器计数值；
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月7日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
u32_t pwrctrl_get_timer_count( void_t )
{
    return pwrctrl_read_reg32(PWRCTRL_SLICE_TIMER_VADDR);
}



/*****************************************************************************
 函 数 名  : pwrctrl_get_timer_base_addr
 功能描述  : 根据timerId获取timer基地址
 输入参数  : timerId        定时器ID
 输出参数  : 无
 返 回 值  : 定时器基地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月8日
    作    者   : 俞伟 00242753
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : pwrctrl_get_timer_clk
 功能描述  : 根据timerId获取timer的CLK
 输入参数  : timerId        定时器ID
 输出参数  : 无
 返 回 值  : 定时器时钟频率
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月8日
    作    者   : 俞伟 00242753
    修改内容   : 新生成函数

*****************************************************************************/
u32_t  pwrctrl_get_timer_clk( u32_t timerId)
{
    return g_ulPWRCTRLTimerClock[timerId];
}


/*****************************************************************************
 函 数 名  : pwrctrl_get_timer_active
 功能描述  : 获取timer的当前的运行状态
 输入参数  : timerId        定时器ID
 输出参数  : 无
 返 回 值  : 定时器运行状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月8日
    作    者   : 俞伟 00242753
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : pwrctrl_get_timer_cnt
 功能描述  : 获取timer的当前计数值
 输入参数  : timerId        定时器ID
 输出参数  : 无
 返 回 值  : 定时器计数值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月8日
    作    者   : 俞伟 00242753
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : pwrctrl_sleep_mgr_get_next_schedule_time
 功能描述  : 读取ACPU所有私有timer的超时时间并返回最短的超时时间
 输入参数  : ulAllTimer         检查类型
             pTimerID           最近的timer ID
             pNextScheduleTime  最近的timer 的计数时间(单位:ms)
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : 俞伟 00242753
    修改内容   : 新生成函数

*****************************************************************************/
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
