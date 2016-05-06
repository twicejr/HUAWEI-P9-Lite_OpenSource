/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  modem.c
*
*   作    者 :  y00184236
*
*   描    述 :  k3v3 lpm3上modem代码总入口
*
*   修改记录 :
*      1> 2013年11月02日  v1.00  y00184236  创建
*************************************************************************/
#include <bsp_ipc.h>
#include <bsp_icc.h>
#include <bsp_nvim.h>
#include <bsp_hkadc.h>
#include <bsp_softtimer.h>
#include <socp_balong.h>
#include <om_balong.h>
#include <regulator_balong.h>
#include <temperature.h>
#include <wdt_balong.h>
#include <m3_pm_modem.h>
#include <m3_cpufreq_modem.h>
#include <bsp_hardtimer.h>
#include <m3_modem.h>
#include <modem_start.h>
#include <ccpu_start.h>
#include <bsp_reset.h>
#include <bsp_pmu_hi6561.h>
#include <bsp_dual_modem.h>

#ifdef K3V3_LPM3_HAS_MODEM_FEATURE

__ao_data T_MODEM_ST g_modem_st={0};

void modem_init()
{
    memcpy((void*)(PWR_TCM_MODEM_INIT_ADDR), "modem_init", sizeof("modem_init"));
    if(get_modem_init_flag() != MODEM_ALREADY_INIT_MAGIC)
    {
        modem_start_init();
    }
    else
    {
        pm_modem_to_a9pll();
    }
    writel(bsp_get_slice_value(), PWR_TCM_MODEM_INIT_ADDR + 0x10);
	(void)bsp_softtimer_init();
    bsp_ipc_init();
    ccpu_start_init();
	bsp_icc_init();
    bsp_nvm_init();
    modem_regulator_init();
    bsp_wdt_init();
	socp_m3_init();
	om_log_init();
#if defined(CONFIG_HKADC)
    bsp_hkadc_init();
#endif
	tem_protect_init();
    cpufreq_init();
    pastar_init();
	pm_modem_init();
#if defined(CONFIG_BALONG_MODEM_RESET)
    bsp_reset_init();
#endif
	wakeup_modem_init();
	g_modem_st.init_flag = MODEM_ALREADY_INIT_MAGIC;
    writel(bsp_get_slice_value(), PWR_TCM_MODEM_INIT_ADDR + 0x14);
    if(get_modem_init_flag() == MODEM_ALREADY_INIT_MAGIC)
    {
        pm_modem_to_192();
    }
}

u32 get_modem_init_flag(void)
{
    return g_modem_st.init_flag;
}


#endif

