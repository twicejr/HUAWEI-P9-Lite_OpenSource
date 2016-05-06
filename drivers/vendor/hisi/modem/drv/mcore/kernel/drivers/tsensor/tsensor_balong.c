#ifdef __cplusplus
extern "C"
{
#endif

#include <libfdt.h>
#include <soc_memmap_comm.h>
#include <hi_tsensor.h>
#include <hi_crg_ao.h>
#include <osl_common.h>
#include <osl_irq.h>
#include <osl_types.h>
#include <osl_spinlock.h>
#include <bsp_icc.h>
#include <bsp_slice.h>
#include <bsp_shared_ddr.h>
#include <bsp_sysctrl.h>
#include "tsensor_balong.h"
#include "m3_pm.h"

irqreturn_t tsensor_int_handler(void * args)
{
    u32 cur_code = 0, flags = 0, len = sizeof(s32);
    s32 temp = 0, ret = TSEN_OK;
    UNUSED(flags);
    
    spin_lock_irqsave(&g_tsensor_lock, flags);
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_INT_MSK1_OFFSET);/* disable int */
    writel(1, HI_TSENSOR_BASE_ADDR + HI_TEMP_INT_CLR1_OFFSET);/* clear int */

    cur_code = TSEN_TEMP1_MASK & readl(HI_TSENSOR_BASE_ADDR + HI_TEMP1_OFFSET);
    temp = TSEN_CODE2TEMP(cur_code);

    ret = (s32)pm_is_wake_lock(PM_PWR_VOTE_CCORE);            /* 0, no wakelock, c core sleep already */
    if(!ret)
        goto out;

    ret = bsp_icc_send(ICC_CPU_MODEM, TSENSOR_ICC_CHAN, (u8 *)&temp, len);
    if(ret != len){
        tsensor_print_error("icc fail: %d\n", ret);
    }

out:
    writel(1, HI_TSENSOR_BASE_ADDR + HI_TEMP_INT_MSK1_OFFSET);/* enable int */
    spin_unlock_irqrestore(&g_tsensor_lock, flags);
    return IRQ_HANDLED;
}

void tsensor_clk_enable(void)
{
    writel(0x2, (u32)bsp_sysctrl_addr_byindex(sysctrl_ao) + HI_AO_CRG_CLKEN1_OFFSET);
}
void tsensor_clk_disable(void)
{
    writel(0x2, (u32)bsp_sysctrl_addr_byindex(sysctrl_ao) + HI_AO_CRG_CLKDIS1_OFFSET);  /* clk disable */
}

void bsp_tsensor_init(void)
{
    struct device_node *dev = NULL;
    const char* compatible = "hisilicon,tsensor_balong_m3";
    u32 interrupt = 0;
    s32 ret = TSEN_OK;

    memset((void *)TSENSOR_SHM_BASE, 0, SHM_SIZE_TSENSOR_STAMP);
    spin_lock_init(&g_tsensor_lock);    
    tsensor_clk_enable();
    
    dev = of_find_compatible_node(NULL, NULL, compatible);
    if(!dev){
        tsensor_print_error("dts failed\n");
        goto error;
    }
    
    interrupt = irq_of_parse_and_map(dev, 0);
    if(!interrupt){
        tsensor_print_error("irq-map failed\n");
        goto error;
    }

    /* ×¢²áÖÐ¶Ï»Øµ÷ */
    ret = request_irq(interrupt, (irq_handler_t)tsensor_int_handler, 0, "TSENSOR_IRQ", NULL);
    if(ret){
        tsensor_print_error("int conn fail: %d\n", ret);
        goto error;
    }
    tsensor_print_error("init ok\n");
    return;

error:
    tsensor_print_error("init failed\n");
    return;
}

void bsp_tsensor_enable(void)
{
    tsensor_clk_enable();
    writel(0x3, HI_TSENSOR_BASE_ADDR + HI_TEMP_DET_EN1_OFFSET);                         /* tsensor enable */
    writel(bsp_get_slice_value(), TSENSOR_ENABLE_STAMP);
}
void bsp_tsensor_disable(void)
{
    writel(0x2, HI_TSENSOR_BASE_ADDR + HI_TEMP_DET_EN1_OFFSET);                         /* tsensor disable */
    tsensor_clk_disable();
}

#ifdef __cplusplus
}
#endif
