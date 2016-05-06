/*----------------------------------------------------------------------------
 *      balongv7r2 m3 pm
 *----------------------------------------------------------------------------
 *      Name:    pm.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r2 PWR.
 *---------------------------------------------------------------------------*/

#include <ARMCM3.h>
#include "console.h"
#include "printk.h"
#include "product_config.h"
#include "osl_types.h"
#include "osl_bio.h"
#include "osl_irq.h"
#include "mdrv_ipc.h"
#include "ipc_balong.h"
#include "hi_common.h"
#include <wdt_balong.h>
#include <m3_cpufreq.h>
#ifndef CCPU_A9_WAKE_LOCK
#include "m3_pm.h"
#else
#include <wakelock.h>
#endif
static void IntIpcCcpuStartHandler(u32 irq)
{
    int irqlock = 0;
    local_irq_save(irqlock);
    printk("start ccpu,ipc=%d\n", get_irq());
    bsp_wdt_enable();
    /*设置A9启动地址并启动，中断中调用，注意时间*/
#ifdef ROM_COMPRESS
    start_ccpu_a9(MCORE_TEXT_START_ADDR_COMPRESSED);
#else
    start_ccpu_a9(MCORE_TEXT_START_ADDR);
#endif
#ifndef CCPU_A9_WAKE_LOCK
    pm_wake_lock(PM_PWR_VOTE_CCORE);
#else
    wake_lock(MODEM_MASK);
#endif
    cpufreq_ccore_cti_init();
    local_irq_restore(irqlock);
}

void ccpu_start_init(void)
{
    /*A9正常运行需要的准备工作*/
    prepare_ccpu_a9();

    /*IPC挂接*/
	if(bsp_ipc_int_connect(IPC_MCU_INT_SRC_CCPU_START, IntIpcCcpuStartHandler, 0) != OK)
	{
		printk("ccpu_start ipc connect err\n");
	}

	if(bsp_ipc_int_enable(IPC_MCU_INT_SRC_CCPU_START) != OK)
	{
		printk("ccpu_start ipc en err\n");
	}
}

