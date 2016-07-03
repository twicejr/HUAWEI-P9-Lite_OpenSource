

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#ifndef WIN32
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/wakelock.h>
#endif
#include  <mach/pwrctrl/pwrctrl_common.h>
#include  <mach/pwrctrl/pwrctrl_perimgr.h>
#include  <mach/pwrctrl/pwrctrl_sleeptst.h>
#include  "soc_ao_sctrl_interface.h"

#if 0   /*acpu softtimer hasn't ready*/
#include  "softtimer.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/



/*****************************************************************************
  3 函数实现
*****************************************************************************/


s32_t pwrctrl_mntn_show(void_t)
{

     PWC_TRACE(PWC_LOG_ERROR, "exc vaddr: %x, paddr: %x \n", (s32_t)g_stAcpuPwcExcLog, EXCH_ACPU_CORE_PWC_ADDR, 0, 0, 0, 0);
     PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: %x, slice: %x \n", (s32_t)(g_stAcpuPwcExcLog->core0.SlpCnt), (s32_t)(g_stAcpuPwcExcLog->core0.SlpMgrSTm), 0, 0, 0, 0);
     PWC_TRACE(PWC_LOG_ERROR, "wake cnt: %x, slice: %x \n", (s32_t)(g_stAcpuPwcExcLog->core0.WkCnt), (s32_t)(g_stAcpuPwcExcLog->core0.WkMgrSTm), 0, 0, 0, 0);

}




s32_t pwrctrl_test_time_int(void_t)
{
    pwrctrl_write_reg32(PWC_REG_UART_PHY, 'A');
    pwrctrl_write_reg32(PWC_REG_UART_PHY, '\n');


    return RET_OK;
}


s32_t pwrctrl_test_time_set(u32_t time)
{

#if 0  /*after acpu softtimer ready, should be deleted*/
    /*注册硬件定时器中断*/
    setup_irq ( PWRCTRL_ACPU_TST_TIMER_INT_ID, &pwrctrl_tst_timer_irq);

    /*配置timer参数*/
    pwrctrl_write_reg32(SOC_TIMER_TIMERN_LOAD_ADDR(SOC_Timer4_BASE_ADDR,1),time);
    pwrctrl_write_reg32(SOC_TIMER_TIMERN_CONTROL_ADDR(SOC_Timer4_BASE_ADDR,1),PWCTRL_ACPU_TST_TIMER_CTRL);

#endif

    return RET_OK;

}






s32_t pwrctrl_test_init(void_t)
{
    return RET_OK;
}







late_initcall(pwrctrl_test_init);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
