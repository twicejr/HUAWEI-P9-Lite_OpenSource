
/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/******************************************************************************

 ******************************************************************************
  文 件 名   : pwrctrl_cpuidle.c
  版 本 号   : 初稿
  作    者   : 王振伟00176398
  生成日期   : 2013年6月13日
  最近修改   :
  功能描述   : CPU  idle驱动代码
  函数列表   :
              cpuidle_init
              cpuidle_init
              cpuidle_pm_notify
              enter_lowpm
              get_enter_state
  修改历史   :
  1.日    期   : 2013年6月13日
    作    者   : 王振伟00176398
    修改内容   : 创建文件

******************************************************************************/

#include <linux/sched.h>
#include <linux/cpuidle.h>
#include <asm/proc-fns.h>
#include <linux/io.h>
#include <mach/hipm.h>
#include <linux/suspend.h>
#include <linux/pm_qos_params.h>
#include "drv_timer.h"
#include <linux/time.h>
#include <linux/ktime.h>
#include <linux/hrtimer.h>
#include <linux/tick.h>
#include "pwrctrl_multi_def.h"
#include <mach/common/mem/bsp_mem.h>
#include <mach/pwrctrl/pwrctrl_common.h>


#ifdef CONFIG_CPU_IDLE
#define MEM_AXI_CPU_IDLE_ADDR       (IO_ADDRESS(MEMORY_AXI_CPU_IDLE_ADDR))

/*C3之后的状态都会切换时钟到32Khz时钟，需要做特殊处理*/
#define SPECIAL_HANDLE_STATE CPU_IDLE_C3

/*register offset definition*/
#define WDG_LOAD		0x0000
#define WDG_VALUE		0x0004
#define WDG_CONTROL 	0x0008
#define WDG_INTCLR		0x000c
#define WDG_RIS			0x0010
#define WDG_MIS			0x0014
#define WDG_LOCK		0x0018
#define UNLOCK_KEY      0x1acce551
#define WDG_ENABLE      0x11

u32_t wdt_base = 0;

#define CPU_IDLE_TIMER  TIMER_ACPU_IDLE_ID
#define IDLE_ACTIVE_DELAY_S 0x56000
#define IDLE_ENABLE 1
#define IDLE_DISABLE 0

extern s32_t pwrctrl_sleep_mgr_get_next_schedule_time( u32_t ulAllTimer,
                                           u32_t *pTimerID, u32_t *pNextScheduleTime);

extern int  pwrctrl_deep_sleep( void_t );
int get_enter_state(struct cpuidle_state *state, int *enter_state);


void_t pwrctrl_wdt_disable(void_t)
{
	/*set disable*/
	writel(UNLOCK_KEY, wdt_base + WDG_LOCK);
	writel(0, wdt_base + WDG_CONTROL);
	writel(0, wdt_base + WDG_LOCK);
}

void_t pwrctrl_wdt_enable(void_t)
{
	writel(UNLOCK_KEY, wdt_base + WDG_LOCK);
	writel(WDG_ENABLE, wdt_base + WDG_CONTROL);
	writel(0, wdt_base + WDG_LOCK);
}


static int cpuidle_pm_notify(struct notifier_block *nfb, unsigned long action, void *ignored)
{
	switch (action) {
	case PM_SUSPEND_PREPARE:
		disable_hlt();
		pr_info("PM_SUSPEND_PREPARE for CPUIDLE\n");
		return NOTIFY_OK;
	case PM_POST_RESTORE:
	case PM_POST_SUSPEND:
		enable_hlt();
		pr_info("PM_POST_SUSPEND for CPUIDLE\n");
		return NOTIFY_OK;
	}
	return NOTIFY_DONE;
}

static struct notifier_block cpuidle_pm_nb = {
	.notifier_call = cpuidle_pm_notify,
};

volatile unsigned int *gp_cpuidle_state;

void cpu_idle_timer_isr()
{
    printk("cpu_idle_timer_isr \r\n");
}
int enter_lowpm(struct cpuidle_device *dev,
			struct cpuidle_state *state)
{
	int icanidle = 0;
	int idle_time;
	int cpu_id = 0;
	int cpu_idle_flag = IDLE_DISABLE;
	struct cpuidle_state *new_state = state;
	struct timeval before, after;
    int enter_state;
    struct timespec t;
	unsigned int timer_id = 0;
	unsigned int schedule_time = 0xffffffff;
    unsigned int expected_us;

    local_irq_disable();
    cpu_id = get_cpu();
    put_cpu();
    if(get_enter_state(state, &enter_state) != 0)
    {
        local_irq_enable();
        return 0;
    }

    /* Used to keep track of the total time in idle */
	getnstimeofday(&before);

    #if 1
    /*启动过程中不允许ACPU下电*/
    /*if((CPU_IDLE_C1 <= enter_state)&&(CPU_IDLE_C3 >= enter_state)&&(before.tv_sec < IDLE_ACTIVE_DELAY_S))*/
    if((CPU_IDLE_C1 <= enter_state)&&(CPU_IDLE_C3 >= enter_state)&&(0 == g_pwc_init_flag))
    {
        PRINT_PWC_DBG(PWC_SWITCH_CPUIDLE,"before.tv_sec:0x%x\n",before.tv_sec);

        local_irq_enable();
        return 0;
    }
    #endif

    if((RET_OK == pwrctrl_is_func_on(PWC_SWITCH_CPUIDLE))&&((CPU_IDLE_C0 < enter_state)&&(CPU_IDLE_C4 > enter_state))&&(0 == cpu_id))
    {
        cpu_idle_flag = IDLE_ENABLE;
    }
    else
    {
        cpu_idle_flag = IDLE_DISABLE;
    }


    /*C3起定时器来唤醒 后续可优化*/
    if((enter_state >= CPU_IDLE_C3)&&(IDLE_ENABLE == cpu_idle_flag))
    {
        pwrctrl_sleep_mgr_get_next_schedule_time(0, &timer_id, &schedule_time);

        if(schedule_time > (0xFFFFFFFF / 1000))
        {
            schedule_time = 0xFFFFFFFF;
        }
        else
        {
            schedule_time *= USEC_PER_MSEC;
        }
        /*C3停止所有TCXO定时器,待优化*/

    	/* determine the expected residency time, round up */
    	t = ktime_to_timespec(tick_nohz_get_sleep_length());
    	expected_us = t.tv_sec * USEC_PER_SEC + t.tv_nsec / NSEC_PER_USEC;

        if(schedule_time < expected_us)
        {
            PRINT_PWC_DBG(PWC_SWITCH_CPUIDLE,"enter_lowpm,system time:%d private time:%d\n",expected_us, schedule_time);
            expected_us = schedule_time;
        }

        expected_us -= state->exit_latency;
        DRV_TIMER_STOP(CPU_IDLE_TIMER);
        DRV_TIMER_START((unsigned int)CPU_IDLE_TIMER, cpu_idle_timer_isr, (int)0, (expected_us / MSEC_PER_SEC), TIMER_ONCE_COUNT, TIMER_UNIT_MS);
    }


    if(IDLE_ENABLE == cpu_idle_flag)
    {
        *gp_cpuidle_state = (enter_state << CPUIDLE_STATE_START_BIT) | (CPU_IDLE_STAT_VALID << CPUIDLE_STATE_MAGIC_START_BIT);
        /*pwrctrl_wdt_disable();*/
    }

    if(0 == cpu_id)
    {
        PRINT_PWC_DBG(PWC_SWITCH_CPUIDLE,"system will enter cpuidle state(%d)\n",enter_state);
    }

    if(CPU_IDLE_C0 == enter_state)
    {
        cpu_do_idle();
    }
    else if(IDLE_ENABLE == cpu_idle_flag)
    {
        pwrctrl_deep_sleep();
    }

    if(enter_state >= SPECIAL_HANDLE_STATE)
    {
        /*清除timer中断*/
        /*C3恢复之前停止所有TCXO定时器,待优化*/
    }

    if(IDLE_ENABLE == cpu_idle_flag)
    {
        *gp_cpuidle_state = (CPU_IDLE_C4 << CPUIDLE_STATE_START_BIT) | (CPU_IDLE_STAT_VALID << CPUIDLE_STATE_MAGIC_START_BIT);
        /*pwrctrl_wdt_enable();*/
    }

    getnstimeofday(&after);

    idle_time = (after.tv_sec - before.tv_sec) * USEC_PER_SEC +
		    (after.tv_usec - before.tv_usec);
    local_irq_enable();

	return idle_time;
}

static struct cpuidle_state cpuidle_set[] = {
	[0] = {
		.enter			= enter_lowpm,
		.exit_latency		= 10000,
		.target_residency	= 10000,
		.flags			= CPUIDLE_FLAG_TIME_VALID,
		.name			= "LOW_POWER_C0",
		.desc			= "ARM clock gating(WFI)",
		.power_usage    = 3,
	},
	[1] = {
		.enter			= enter_lowpm,
		.exit_latency		= 1000000,//1000000
		.target_residency	= 1600000,//1600000
		.flags			= CPUIDLE_FLAG_TIME_VALID,
		.name			= "LOW_POWER_C1",
		.desc			= "ARM power down",
		.power_usage    = 2,
	},
	[2] = {
		.enter			= enter_lowpm,
		.exit_latency		= 1500000,
		.target_residency	= 2200000,
		.flags			= CPUIDLE_FLAG_TIME_VALID,
		.name			= "LOW_POWER_C2",
		.desc			= "ARM power down&ddr can selref",
		.power_usage    = 1,
	},
	[3] = {
		.enter			= enter_lowpm,
		.exit_latency		= 5000000,
		.target_residency	= 5800000,
		.flags			= CPUIDLE_FLAG_TIME_VALID,
		.name			= "LOW_POWER_C3",
		.desc			= "ARM power down&clk can switch to 32Khz",
		.power_usage    = 0,
	},
};

/*0 成功  负值失败*/
int get_enter_state(struct cpuidle_state *state, int *enter_state)
{
    int i;
    int state_num;
    int ret = -1;

    if(NULL == enter_state || NULL == state)
    {
        return ret;
    }

    state_num = sizeof(cpuidle_set) / sizeof(cpuidle_set[0]);

    for(i = 0; i < state_num; i++)
    {
        if(memcmp(state->name, cpuidle_set[i].name, CPUIDLE_NAME_LEN) == 0 && \
            memcmp(state->desc, cpuidle_set[i].desc, CPUIDLE_DESC_LEN) == 0)
            break;
    }

    if(i != state_num)
    {
        *enter_state = i;
        ret = 0;
    }

    return ret;
}

DEFINE_PER_CPU(struct cpuidle_device, idle_dev);

struct cpuidle_driver idle_driver = {
	.name =		"cpuidle",
	.owner =	THIS_MODULE,
};


/**
 * cpuidle_init - Init routine for v9r1 idle
 *
 * Registers the v9r1 specific cpuidle driver to the cpuidle
 * framework with the valid set of states.
 */
int __init cpuidle_init(void)
{
	struct cpuidle_device *dev;
	int i, max_cpuidle_state, cpu_id;

	cpuidle_register_driver(&idle_driver);

	wdt_base = ioremap(REG_BASE_WD0, REG_WD0_IOSIZE);

    gp_cpuidle_state = (unsigned int *)MEM_AXI_CPU_IDLE_ADDR;
    *gp_cpuidle_state = (CPU_IDLE_C4 << CPUIDLE_STATE_START_BIT) | (CPU_IDLE_STAT_VALID << CPUIDLE_STATE_MAGIC_START_BIT);/*init*/

	for_each_cpu(cpu_id, cpu_online_mask) {
		dev = &per_cpu(idle_dev, cpu_id);
		dev->cpu = cpu_id;

		printk(KERN_ERR "cpu=%d\n", dev->cpu);

		if (cpu_id == 0)
			dev->state_count = ARRAY_SIZE(cpuidle_set);
		else
			dev->state_count = 1;	/* Support IDLE only */

		max_cpuidle_state = dev->state_count;

		for (i = 0; i < max_cpuidle_state; i++) {
			memcpy(&dev->states[i], &cpuidle_set[i],
					sizeof(struct cpuidle_state));
		}

		dev->safe_state = &dev->states[0];

		if (cpuidle_register_device(dev)) {
			cpuidle_unregister_driver(&idle_driver);
			printk(KERN_ERR "CPUidle register device failed\n,");
			return -EIO;
		}
	}

	register_pm_notifier(&cpuidle_pm_nb);

	return 0;
}
#else
int __init cpuidle_init(void)
{
	return 0;
}
#endif /* CONFIG_CPU_IDLE */
late_initcall(cpuidle_init);

