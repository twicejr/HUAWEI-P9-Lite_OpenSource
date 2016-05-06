/*----------------------------------------------------------------------------
 *      balongv7r2 m3 pm test
 *----------------------------------------------------------------------------
 *      Name:    m3_pm_test.c
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r2 PWR.
 *---------------------------------------------------------------------------*/

#include <ARMCM3.h>
#include "console.h"
#include "printk.h"

#include "osl_types.h"
#include "osl_bio.h"
#include "osl_irq.h"

#include "m3_pm.h"
#include "pm_api.h"
#include "mdrv_ipc.h"
#include "ipc_balong.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "bsp_nvim.h"
#include "m3_cpufreq.h"
#include "bsp_dsp.h"
#include "bsp_icc.h"
#include "bsp_hardtimer.h"
#include "wdt_balong.h"

#include <bsp_softtimer.h>
#include "m3_pm_test.h"

void m3_pm_timer_isr(void);


struct softtimer_list pm_test_softtimer ={   
    .func = (softtimer_func)m3_pm_timer_isr,
   .para = 0,
   .timeout = 2000,
   .wake_type = SOFTTIMER_WAKE,
  
};
u32 pm_test_inited = 0;
unsigned int pm_timer_cnt = 0;

/* 串口调用设置并启动timer */
void set_pm_test_timer(u32 timeout)
{
    if(0==pm_test_inited)
    {
        (void)bsp_softtimer_create(&pm_test_softtimer);
        (void)bsp_softtimer_modify(&pm_test_softtimer,timeout);
        bsp_softtimer_add(&pm_test_softtimer);
        pm_test_inited = 1;
    }
    else
    {
        (void)bsp_softtimer_delete(&pm_test_softtimer);
        (void)bsp_softtimer_modify(&pm_test_softtimer,timeout);
        bsp_softtimer_add(&pm_test_softtimer);
    }
}

void m3_pm_timer_isr(void)
{
    pm_timer_cnt++;
    printk(" pm_timer_cnt %d \n",pm_timer_cnt);
}

/* 如果使能了测试 睡眠流程中 add */
void pm_test_add_timer(void)
{
    if(1==pm_test_inited){
        bsp_softtimer_add(&pm_test_softtimer);
    }
}


/*
u32DebugCanSleepTime  深睡次数控制功能
0 表示正常睡眠，无睡眠次数限制
0xffffffff 表示不睡眠
其他 表示正常睡眠次数
*/
T_PM_COUNT_ST gPmCountSt;

u32 debug_can_sleep(void)
{
    if(0 == gPmCountSt.u32DebugCanSleepTime)
    {
        return 1;
    }
    else
    {
        if((u32)(-1) == gPmCountSt.u32DebugCanSleepTime)
        {
            return 0;
        }
        else if( 1 == gPmCountSt.u32DebugCanSleepTime)
        {
            gPmCountSt.u32DebugCanSleepTime = 0xffffffff;
            return 1;
        }
        else
        {
            gPmCountSt.u32DebugCanSleepTime--;
            return 1;
        }
    }
}

/* test for deepsleep state machine  */
struct pm_test_state_machine test_s_m ={
    .enable         = 0,
    .loop_min       = 0x1900,
    .loop_max       = 0x1c00,
    .loop_temp      = 0x1900,
    .first_no_sm    = 0,
    .tmp_no_sm      = 0,
};

void pm_test_loop(void)
{
    volatile u32 tmp;
    if( 0 == test_s_m.enable ){
        return;
    }
    
    tmp = test_s_m.loop_temp;
    while(tmp){
        tmp--;
    }
    test_s_m.loop_temp++;

    
    if(test_s_m.loop_temp == test_s_m.loop_max){
        test_s_m.loop_temp = test_s_m.loop_min;
        test_s_m.tmp_no_sm = 0;
    }
}
void pm_test_no_sm_record(void)
{
    if(test_s_m.first_no_sm == 0){
        test_s_m.first_no_sm = test_s_m.loop_temp;
    }
    if((test_s_m.tmp_no_sm == 0)&&(test_s_m.loop_temp != test_s_m.loop_min)){
        test_s_m.tmp_no_sm = test_s_m.loop_temp;
    }
}


/* send A/C core sleep ipc from m3 */
void m3_send_a_ipc(void)
{
    writel(PM_A2M_IPC_BIT, PM_A2M_IPC_ADDR);
}
void m3_send_c_ipc(void)
{
    writel(PM_C2M_IPC_BIT, PM_C2M_IPC_ADDR);
}



