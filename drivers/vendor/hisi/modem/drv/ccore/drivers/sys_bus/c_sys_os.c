/*
*此文件主要用于对RTOSck系统调度时，任务、中断等处理过程的性能记录和上报
*
*/
#include <sre_config.h>
#include <sre_task.h>
#include <sre_hwi.h>
#include <bsp_slice.h>
#include <c_sys_bus_core.h>
#include <c_sys_os.h>

/*全局变量*/
#define OS_HWI_MAX_SUPPORT_NUM    255         /*系统支持的最大中断号，系统不支持软中断*/

static struct sys_os_hwi g_os_hwi_array[OS_HWI_MAX_SUPPORT_NUM] = {};    /*中断信息数组*/
static struct sys_os_task g_os_task_array[OS_TSK_MAX_SUPPORT_NUM] = {};  /*任务信息数组*/
static u32 g_hwi_time_in_task = 0;                                       /*任务运行中中断花费的时间*/
static u32 g_hrtime_count_per_ms = 0; 
static u32 g_hrtime_count_per_10us = 0; 
static u32 hrtime_get_value(void)
{
    return bsp_get_slice_value_hrt();
}
static void hrtime_get_frequency(void)
{
    g_hrtime_count_per_ms = bsp_get_hrtimer_freq()/1000;
    g_hrtime_count_per_10us = bsp_get_hrtimer_freq()/100000;
}

/*注册给OS任务切换过程中的HOOK*/
static void os_task_switch_hook(u32 last_pid,u32 next_pid)
{   
    /*last pid*/
    g_os_task_array[last_pid&0xFF].pid = last_pid;
    g_os_task_array[last_pid&0xFF].spend_time = get_timer_slice_delta(g_os_task_array[last_pid&0xFF].spend_time,hrtime_get_value()) - g_hwi_time_in_task;
    g_hwi_time_in_task = 0;
    g_os_task_array[last_pid&0xFF].total_utime += ((g_os_task_array[last_pid&0xFF].spend_time%g_hrtime_count_per_ms)*10)/g_hrtime_count_per_10us; /*us*/
    g_os_task_array[last_pid&0xFF].total_mtime += (g_os_task_array[last_pid&0xFF].spend_time/g_hrtime_count_per_ms);/*ms*/
    if(g_os_task_array[last_pid&0xFF].spend_time > g_os_task_array[last_pid&0xFF].maxtime)
    {
        g_os_task_array[last_pid&0xFF].maxtime = g_os_task_array[last_pid&0xFF].spend_time;
    }
    g_os_task_array[last_pid&0xFF].count ++;
    
    /*next pid*/
    g_os_task_array[next_pid&0xFF].spend_time = hrtime_get_value();
    return;
}

/*注册给OS HWI进入时的HOOK*/
static void os_hwi_entry_hook(u32 vec_num)
{
    g_os_hwi_array[vec_num].spend_time = hrtime_get_value();
    return;
}

/*注册给OS HWI退出时的HOOK*/
static void os_hwi_exit_hook(u32 vec_num)
{
    g_os_hwi_array[vec_num].int_num= vec_num;
    g_os_hwi_array[vec_num].spend_time = get_timer_slice_delta(g_os_hwi_array[vec_num].spend_time,hrtime_get_value());
    g_os_hwi_array[vec_num].total_time += (g_os_hwi_array[vec_num].spend_time * 10)/g_hrtime_count_per_10us; /*us*/
    if(g_os_hwi_array[vec_num].spend_time > g_os_hwi_array[vec_num].maxtime)
    {
        g_os_hwi_array[vec_num].maxtime = g_os_hwi_array[vec_num].spend_time;
    }
    g_os_hwi_array[vec_num].count ++;
    g_hwi_time_in_task += g_os_hwi_array[vec_num].spend_time;
    return;
}
void sys_os_start(struct master* master)
{
    u32 ret = 0;
    ret = SRE_TaskSwitchHookAdd(os_task_switch_hook);

    if(SRE_OK != ret)
    {
        sys_bus_trace("os_task_switch_hook: register failed,errNo:0x%x\n",ret);
    }
    ret = SRE_HwiEntryHookAdd(os_hwi_entry_hook);
    if(SRE_OK != ret)
    {
        sys_bus_trace("os_hwi_entry_hook: register failed,errNo:0x%x\n",ret);
    }

    ret = SRE_HwiExitHookAdd(os_hwi_exit_hook);
    if(SRE_OK != ret)
    {
        sys_bus_trace("os_hwi_exit_hook: register failed,errNo:0x%x\n",ret);
    }
    hrtime_get_frequency();
    return;
}
void sys_os_stop(struct master* master)
{
    u32 ret = 0;
    ret = SRE_TaskSwitchHookDelete(os_task_switch_hook);
    if(SRE_OK != ret)
    {
        sys_bus_trace("os_task_switch_hook: unregister failed,errNo:0x%x\n",ret);
    }
    ret = SRE_HwiEntryHookDel(os_hwi_entry_hook);
    if(SRE_OK != ret)
    {
        sys_bus_trace("os_hwi_entry_hook: unregister failed,errNo:0x%x\n",ret);
    }
    ret = SRE_HwiExitHookDel(os_hwi_exit_hook);
    if(SRE_OK != ret)
    {
        sys_bus_trace("os_hwi_exit_hook: unregister failed,errNo:0x%x\n",ret);
    }
    return;
}
void sys_os_report(struct master* master)
{
    int i = 0;
    u32 av_value_us = 0;

    sys_bus_trace("\n");
    sys_bus_trace("Timer frequency = %d Hz\n",bsp_get_hrtimer_freq());
    sys_bus_trace("Note:this timer stop working in LPM3 deepsleep\n");
    sys_bus_trace("\n");
    do{
        if(g_os_hwi_array[i].count)
        {
             av_value_us = (u32)(g_os_hwi_array[i].total_time/g_os_hwi_array[i].count);
             sys_bus_trace("HwiNum:%d,count:%d,MaxTime:%d us,AvregeTime:%d us \n",g_os_hwi_array[i].int_num, \
             g_os_hwi_array[i].count,(g_os_hwi_array[i].maxtime * 10)/g_hrtime_count_per_10us,av_value_us);
        }
        i++;
    }while(i < OS_HWI_MAX_SUPPORT_NUM);
    i = 0;
    do{
        if(g_os_task_array[i].count)
        {
             if(SRE_OK == SRE_TaskNameGet(g_os_task_array[i].pid,&g_os_task_array[i].name))
             {
                 av_value_us = (u32)(g_os_task_array[i].total_utime/g_os_task_array[i].count) + \
                               ((u32)(g_os_task_array[i].total_mtime/g_os_task_array[i].count)*1000);                
                 sys_bus_trace("TaskName:%s,count:%d ,MaxTime:%d us,AvregeTime:%d us \n",g_os_task_array[i].name, \
                       g_os_task_array[i].count,(g_os_task_array[i].maxtime*10)/g_hrtime_count_per_10us,av_value_us);
             }
        }
        i++;
    }while(i < OS_TSK_MAX_SUPPORT_NUM);
    return;
}


