/*****************************************************************************
*RTOSCK小系统对外入口，此文件不允许随意更改
*owner:xujingcui
*****************************************************************************/
#include <sre_io_intf.h>
#include "sre_task.h"
#include "sre_typedef.h"
#include <bsp_gic_pm.h>
#include <of.h>
#include <bsp_sysctrl.h>
#include <bsp_s_memory.h>
#include <bsp_hardtimer.h>
#include <bsp_uart.h>
#include <bsp_l2cache.h>
#include "bsp_dump.h"
#include "bsp_coresight.h"
/*小系统需要的函数,除systimer，其他需要控制*/
extern void rtosckClkStart(void);
extern void drv_entry (void);
extern int syslog_recv_fun(char ch);

#ifdef CONFIG_SMART_SYSTEM_MODEM
void gic_init(void)
{}
#endif


/*****************************************************************************
 函 数 名  : SRE_HardBootInit
 功能描述  : 操作系统启动时调用，初始化在启动初期要求使能的硬件模块;
             不需要，故打桩
 输入参数  : NA
 输出参数  : NA
 返 回 值  : NA
 调用函数  :
 被调函数  :

*****************************************************************************/

#ifdef DRV_BUILD_GCOV
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

void __libc_init_array (void)
{
    unsigned int i     = 0;
    unsigned int count = __init_array_end - __init_array_start;

    for (i = 0; i < count; i++)
        __init_array_start[i]();
}
#endif

VOID SRE_HardBootInit()
{
#ifdef DRV_BUILD_GCOV
    __libc_init_array();
#endif


	(void)bsp_dts_init();



    l2cache_HardBootInit();


	return;
}

/*****************************************************************************
 函 数 名  : SRE_HardDrvInit
 功能描述  : 操作系统启动时调用，初始化需要早期需要使能的模块，如UART,timer
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UINT32
 调用函数  :
 被调函数  :

*****************************************************************************/
UINT32 SRE_HardDrvInit(VOID)
{

    /*映射gic空间*/
    gic_init();
    /*初始化serial*/
	(void)SRE_SendChrToChlHookReg((OS_SENDCHR2CHL_HOOK_FUNC)syslog_recv_fun);
    bsp_serial_init();
    return SRE_OK;
}

/*****************************************************************************
 函 数 名  : SRE_AppInit
 功能描述  : 操作系统后期调用，用来创建一个最高优先级的任务，初始化各模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  : UINT32
 调用函数  :
 被调函数  :

*****************************************************************************/

UINT32 SRE_AppInit()
{
    TSK_HANDLE_T       uwTaskUsrInitId;
    TSK_INIT_PARAM_S stTaskUsrInit={0};
    UINT32 uwRet;
    stTaskUsrInit.pfnTaskEntry = (TSK_ENTRY_FUNC)drv_entry;
    stTaskUsrInit.uwStackSize  = 0x4000;
    stTaskUsrInit.usTaskPrio    = 0;
    stTaskUsrInit.pcName        = "drv_entry";
    stTaskUsrInit.usQNum        = 0;
    stTaskUsrInit.uwStackAddr  = 0;
    dt_sysctrl_init();
	bsp_shared_mem_init();
	bsp_timer_iomap_and_clk_cfg();
    /*初始化timer*/
    rtosckClkStart();

    uwRet = SRE_TaskCreate(&uwTaskUsrInitId, &stTaskUsrInit);
    if (SRE_OK != uwRet)
    {
        return uwRet;
    }
    return SRE_OK;
}

