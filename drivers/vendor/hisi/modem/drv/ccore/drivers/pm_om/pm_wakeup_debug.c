/*lint --e{534}*/
#include <securec.h>
#include <osl_thread.h>
#include <osl_sem.h>
#include <bsp_softtimer.h>
#include <bsp_hardtimer.h>
#include <bsp_wakelock.h>
#include <bsp_pm.h>
#include <bsp_pm_om.h>

#define MAX_U32_TIME_MS (0xFFFFFFFF/32768*1000)

struct pm_wakeup_ctrl_s{
	struct softtimer_list wakeup_softtimer;
	OSL_TASK_ID wakeup_task;
	osl_sem_id wakeup_sem;
	spinlock_t lock;
	u32 timer_cb_para;
	u32 sleep_ms;
	u32 wakeup_ms;	
	u32 wakeup_times;
	u32 wakeup_acore_flag;
	u32 support_softtimer;
	u32 stay_wake_flag;
	FUNCPTR_1 period_cb;
	int para;
	u32 inited_flag;
}pm_wakeup_ctrl;

extern s32 pm_wakeup_acore(enum debug_wake_type type);
extern void debug_pm_wake_unlock(void);
extern void debug_pm_wake_lock(void);
static void pm_stay_wake_delay(void)
{
	if(pm_wakeup_ctrl.wakeup_ms)
	{
		debug_pm_wake_lock();
		osl_task_delay((int)pm_wakeup_ctrl.wakeup_ms/10);
		if(!pm_wakeup_ctrl.stay_wake_flag)
			debug_pm_wake_unlock();
	}
}
static void wakeup_timer_cb(u32 para){
	pm_wakeup_ctrl.wakeup_times++;
	osl_sem_up(&(pm_wakeup_ctrl.wakeup_sem));
}

s32 pm_wakeup_stop(void){
	s32 ret = 0;
	if(!pm_wakeup_ctrl.inited_flag)
	{
		pmom_pr_err("not inited\n");
		return -1;
	}
	pm_wakeup_ctrl.stay_wake_flag=1;
	debug_pm_wake_lock();
	if(pm_wakeup_ctrl.support_softtimer)
	{
		(void)bsp_softtimer_delete(&pm_wakeup_ctrl.wakeup_softtimer);
	}
	else
	{
		ret = mdrv_timer_stop(TIMER_CCPU_DRX_STAMP_ID);
		if(ret)
		{
			pmom_pr_err("mdrv_timer_stop failed,ret = 0x%x\n",ret);
			return -1;
		}
	}
	pm_wakeup_ctrl.period_cb=NULL;
	pm_wakeup_ctrl.para = 0;
	return 0;
		
}

s32 wakeup_sleep_and_delay(u32 sleep_ms, u32 wakeup_ms,u32 wakeup_acore_flag)
{
	s32 ret = 0;
	if(!pm_wakeup_ctrl.inited_flag)
	{
		pmom_pr_err("not inited\n");
		return -1;
	}
	if((sleep_ms>MAX_U32_TIME_MS)||(wakeup_ms>MAX_U32_TIME_MS))
	{
		pmom_pr_err("time overflow\n");
		return -1;
	}
	pm_wakeup_ctrl.sleep_ms = sleep_ms;
	pm_wakeup_ctrl.wakeup_ms = wakeup_ms;
	pm_wakeup_ctrl.wakeup_acore_flag = wakeup_acore_flag;
	
	pm_wakeup_ctrl.stay_wake_flag=0;
	if(pm_wakeup_ctrl.support_softtimer)
	{
		pm_wakeup_ctrl.wakeup_softtimer.timeout = sleep_ms;
		ret = bsp_softtimer_modify(&pm_wakeup_ctrl.wakeup_softtimer,sleep_ms);
		if(ret)
		{
			pmom_pr_err("bsp_softtimer_modify err\n");
			return -1;
		}
		bsp_softtimer_add(&pm_wakeup_ctrl.wakeup_softtimer);
	}
	else/*需要软关机，复用drx stamp timer*/
	{
		ret = mdrv_timer_start(TIMER_CCPU_DRX_STAMP_ID,(FUNCPTR_1)wakeup_timer_cb,0,sleep_ms,TIMER_ONCE_COUNT,TIMER_UNIT_MS);
		if(ret)
		{
			pmom_pr_err("mdrv_timer_start err\n");
			return -1;
		}
	}
	return 0;
		
}
s32 period(FUNCPTR_1 period_cb,int para,u32 period_time_ms,u32 stay_wake_time_ms)
{
	pm_wakeup_ctrl.period_cb = period_cb;
	pm_wakeup_ctrl.para = para;
	return wakeup_sleep_and_delay(period_time_ms,stay_wake_time_ms,0);
}

#define PM_WAKEUP_DEBUG_TASK_PRI 62
#define PM_WAKEUP_DEBUG_TASK_SIZE 0X1000

static void pm_wakeup_debug_task_func(void* para)
{
	s32 ret = 0;
	for(;;)
	{
		osl_sem_down(&(pm_wakeup_ctrl.wakeup_sem));
		if(pm_wakeup_ctrl.wakeup_acore_flag)
		{
			ret = pm_wakeup_acore(PM_WAKEUP_THEN_SLEEP);
			if(ret)
			{
				pmom_pr_err("pm_wakeup_acore err\n");
				return;
			}
		}
		if(pm_wakeup_ctrl.period_cb)
			pm_wakeup_ctrl.period_cb(pm_wakeup_ctrl.para);
		pm_stay_wake_delay();
		if(pm_wakeup_ctrl.support_softtimer)
		{
			bsp_softtimer_add(&pm_wakeup_ctrl.wakeup_softtimer);
		}
		else
		{
			ret = mdrv_timer_start(TIMER_CCPU_DRX_STAMP_ID,(FUNCPTR_1)wakeup_timer_cb,0,pm_wakeup_ctrl.sleep_ms,TIMER_ONCE_COUNT,TIMER_UNIT_MS);
			if(ret)
			{
				pmom_pr_err("mdrv_timer_start err\n");
			}
		}
	}
}
void bsp_pm_wakeup_debug_init(void)
{
	s32 ret = 0;
	(void)memset_s((void*)&pm_wakeup_ctrl,sizeof(pm_wakeup_ctrl),0x0,sizeof(pm_wakeup_ctrl));
	pm_wakeup_ctrl.support_softtimer = check_softtimer_support_type(SOFTTIMER_WAKE);
	osl_sem_init(SEM_EMPTY,&(pm_wakeup_ctrl.wakeup_sem));
	if(ERROR == osl_task_init("pm_wakeup_debug", PM_WAKEUP_DEBUG_TASK_PRI, PM_WAKEUP_DEBUG_TASK_SIZE ,(OSL_TASK_FUNC)pm_wakeup_debug_task_func, (void*)NULL,
		&pm_wakeup_ctrl.wakeup_task))
	{
		pmom_pr_err("failed\n");
		return;
	}
	if(pm_wakeup_ctrl.support_softtimer)
	{
		pm_wakeup_ctrl.wakeup_softtimer.wake_type=SOFTTIMER_WAKE;	
		pm_wakeup_ctrl.wakeup_softtimer.func = wakeup_timer_cb;	
		ret = bsp_softtimer_create(&pm_wakeup_ctrl.wakeup_softtimer);
		if (ret)
		{
			pmom_pr_err("create error\n");
			return ;
		}
	}
	spin_lock_init(&pm_wakeup_ctrl.lock);
	pm_wakeup_ctrl.inited_flag = 1;
	pmom_pr_err("pm_wakeup_debug_init ok\n");
	
}
void show_sr_debug()
{
	pmom_pr_err("wakeup cb run times=0x%x\n",pm_wakeup_ctrl.wakeup_times);
	pmom_pr_err("wakeup acore flag=%d\n",pm_wakeup_ctrl.wakeup_acore_flag);
	pmom_pr_err("stay wake flag=%d\n",pm_wakeup_ctrl.stay_wake_flag);
	pmom_pr_err("sleep ms=%d\n",pm_wakeup_ctrl.sleep_ms);
	pmom_pr_err("wakeup ms=%d\n",pm_wakeup_ctrl.wakeup_ms);
}

