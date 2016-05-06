#include <osl_types.h>
#include <osl_irq.h>
#include <bsp_memmap.h>
#include <hi_timer.h>
#include <soc_interrupts.h>
#include <soc_clk.h>
#include "pm.h"
#include <bsp_om.h>

#ifdef PM_TEST_WSRC

/* 启用 timer 用于测试  ( 使用 timer 作为wsrc ) */
// 使用32k作为 wsrc, a-timer11 0x9000403c   c-timer20  0x90004050

irqreturn_t timer20_irq(void* arg);
int timer_wsrc_test_init(u32 sec);

OSL_IRQ_FUNC(irqreturn_t, timer20_irq, intLvl,arg)
{
    u32 ret = 0;
    u32 t20_addr = HI_TIMER_20_REGBASE_ADDR_VIRT;
    ret = readl(t20_addr+HI_TIMER_EOI_OFFSET);
    pm_printk(BSP_LOG_LEVEL_ERROR,"ccore timer20 irq handled : 0x%x \n",ret);
    return IRQ_HANDLED;
}
static u32 timer_irq_requested = 0;
int timer_wsrc_test_init(u32 sec)
{
    u32 t20_addr = HI_TIMER_20_REGBASE_ADDR_VIRT;
    if(timer_irq_requested)
    {
        free_irq( INT_LVL_TIMER20 , 0);
    }
    /* 初始值 */
    *(u32*)(t20_addr+HI_TIMER_LOADCOUNT_OFFSET) = HI_TIMER20_CLK*sec;
    /*  config */
    *(u32*)(t20_addr+HI_TIMER_CONTROLREG_OFFSET) = 3;
    if(request_irq(INT_LVL_TIMER20, (irq_handler_t)timer20_irq, 0, "timer20", 0))
    {
        pm_printk(BSP_LOG_LEVEL_ERROR, "request_irq INT_LVL_TIMER20 - FAILED! \n");
        return -1;
    }
    timer_irq_requested = 1;
    return 0;
}

#endif

