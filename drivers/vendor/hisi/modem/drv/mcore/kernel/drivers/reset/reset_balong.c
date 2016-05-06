/*************************************************************************
*   版权所有(C) 2008-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  reset_balong.c
*
*   作    者 :  y00184236
*
*   描    述 :  本文件主要完成C核单独复位辅助处理
*
*   修改记录 :  2014年02月15日  v1.00  y00184236  创建
*************************************************************************/
#include <product_config.h>
#include <bsp_memmap.h>
#include <bsp_reset.h>
#include <bsp_icc.h>
#include <wakelock.h>
#include <wdt_balong.h>
#include <modem_start.h>
#include "reset_balong.h"

#ifndef NOC_LOCK_ID
#define NOC_LOCK_ID 16
#endif

struct mcore_reset_ctrl g_mreset_ctrl = {0};

u32 print_sw = 1;

#define  reset_print_debug(fmt, ...) \
do {                               \
    if (print_sw)    \
        reset_print_err(fmt, ##__VA_ARGS__);\
} while (0)

#define CCORE_RST_TIMEOUT_NUM         (327) /*10ms*/
#define CHECK_TIMEOUT(a)   (get_timer_slice_delta(a, bsp_get_slice_value()) < CCORE_RST_TIMEOUT_NUM)

#ifdef CONFIG_BALONG_MODEM_RESET

__ao_func void ccore_freq_drop(void)
{
	//reset_print_debug("(%d)\n", ++g_mreset_ctrl.main_stage);
}
__ao_func void ccore_freq_raise(void)
{
	//reset_print_debug("(%d)\n", ++g_mreset_ctrl.main_stage);
}
extern void ccore_ipc_disable(void);
extern void ccore_ipc_enable(void);
extern void reset_ipc_status_bakup(void);
extern void reset_ipc_status_resume(void);
extern void ipc_modem_reset_cb(DRV_RESET_CALLCBFUN_MOMENT stage, int userdata);
extern void cpufreq_resume(void);
extern int bsp_ipf_reset_ccore_lpm3_cb(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);
__ao_func void modem_a9_unreset(void)
{
	//reset_print_debug("(%d)\n", ++g_mreset_ctrl.main_stage);
    /* 16 a9 start addr */
    *(u32 *)STAMP_UNRESET_M3_A9_STAR_ADDR = bsp_get_slice_value();
#ifdef ROM_COMPRESS
    writel(MCORE_TEXT_START_ADDR_COMPRESSED >> 16,0xA8A09C18);
#else
    writel(MCORE_TEXT_START_ADDR >> 16,0xA8A09C18);
#endif

    /* 18 unreset a9*/
    *(u32 *)STAMP_UNRESET_M3_UNRESET_A9 = bsp_get_slice_value();
    writel(0x1<<15, HI_SYSCTRL_BASE_ADDR + HI_CRG_SRSTDIS1_OFFSET);
    writel(0x1<<6, HI_SYSCTRL_BASE_ADDR + HI_CRG_SRSTDIS1_OFFSET);
}
__ao_func void reset_m3_stamp_addr_value(void)
{
    *(u32 *)STAMP_RESET_M3_BASE_ADDR = 0x33333333;
    *(u32 *)STAMP_RESET_M3_BUSERROR_STEP1 = 0x0;
    *(u32 *)STAMP_RESET_M3_BUSERROR_STEP2 = 0x0;
    *(u32 *)STAMP_RESET_M3_BUSERROR_STEP3 = 0x0;
    *(u32 *)STAMP_RESET_M3_NOC_PROBE_DISABLE = 0x0;
    *(u32 *)STAMP_RESET_M3_NOC_ENTER_LPMODE_CONFIG = 0x0;
    *(u32 *)STAMP_RESET_M3_NOC_ENTER_LPMODE_STEP1 = 0x0;
    *(u32 *)STAMP_RESET_M3_NOC_ENTER_LPMODE_STEP2 = 0x0;
    *(u32 *)STAMP_RESET_M3_CLEAN_NMI = 0x0;
    *(u32 *)STAMP_RESET_M3_RESET_SUBSYS = 0x0;
    *(u32 *)STAMP_UNRESET_M3_BASE_ADDR = 0x33333333;
    *(u32 *)STAMP_UNRESET_M3_UNRESET_SUBSYS = 0x0;
    *(u32 *)STAMP_UNRESET_M3_A9_STAR_ADDR = 0x0;
    *(u32 *)STAMP_UNRESET_M3_UNRESET_A9 = 0x0;
}

__ao_func int modem_subsys_reset(void)
{
    u32 tmp = 0;
    u32 slicebegin = 0;
    reset_m3_stamp_addr_value();

    /* ap侧访问modem子系统, 是否modem子系统总线已经挂死: PMCtrl中，modem global总线是否挂死[17]==0x1 */
    *(u32 *)STAMP_RESET_M3_BUSERROR_STEP1 = bsp_get_slice_value();
    tmp = readl(0x402313A4);
    tmp &= ((u32)0x1 << 17);
    if(tmp)
	{
        reset_print_err("\r modem global bus error, total count: %d\n", ++g_mreset_ctrl.mdm_global_bus_err_cnt);
        return (int)RESET_MCORE_BEFORE_MODEM_GLOBAL_BUS_ERR;
    }

    /* modem侧访问AP, 是否modem子系统被挂死: PCtrl中，modem 子系统是否挂死[9]==0x0 */
    *(u32 *)STAMP_RESET_M3_BUSERROR_STEP2 = bsp_get_slice_value();
    slicebegin = bsp_get_slice_value();
    do
	{
		tmp = readl(0xA8A090A0);
		tmp &= ((u32)0x1 << 9);
	}while((tmp == 0x0) && CHECK_TIMEOUT(slicebegin));
    if(!tmp)
	{
        reset_print_err("\r modem sysbus bus error,  total count: %d, spend time: %d slice\n",
			++g_mreset_ctrl.mdm_sub_bus_err_cnt, get_timer_slice_delta(slicebegin, bsp_get_slice_value()));
        return (int)RESET_MCORE_BEFORE_MODEM_BUS_ERR;
    }

    /* modem访问DDRC，是否已经挂死: ddrc phy中，modem 访问DDR是否挂死[0]==0x1 */
    *(u32 *)STAMP_RESET_M3_BUSERROR_STEP3 = bsp_get_slice_value();
    slicebegin = bsp_get_slice_value();
    do
	{
		tmp = readl(0x40220600);
		tmp &= ((u32)0x1 << 0);
	}while((tmp == (u32)0x1) && CHECK_TIMEOUT(slicebegin));
    if(tmp)
	{
        reset_print_err("\r modem access ddr error,  total count: %d, spend time: %d slice\n",
			++g_mreset_ctrl.mdm_ddr_access_err_cnt, get_timer_slice_delta(slicebegin, bsp_get_slice_value()));
        return (int)RESET_MCORE_BEFORE_MODEM_ACCESS_DDRC_ERR;
    }

    /*配置error probe特性disable*/
    *(u32 *)STAMP_RESET_M3_NOC_PROBE_DISABLE = bsp_get_slice_value();
    tmp = readl(0xA8080408);
    tmp &= ~((u32)0x1 << 0);
    writel(tmp, 0xA8080408);

	hwspin_lock_timeout(NOC_LOCK_ID, WAITFVR); /* 当前分支引用不到，AP在2014/06/05合入他们主线 */
    /*配置NOC进入低功耗模式*/
    *(u32 *)STAMP_RESET_M3_NOC_ENTER_LPMODE_CONFIG = bsp_get_slice_value();
    tmp = readl(0x40231380);
    tmp |= ((u32)0x1 << 3);
    writel(tmp, 0x40231380);
	hwspin_unlock(NOC_LOCK_ID);

    slicebegin = bsp_get_slice_value();
    /*等待NOC进入低功耗模式*/
    *(u32 *)STAMP_RESET_M3_NOC_ENTER_LPMODE_STEP1 = bsp_get_slice_value();
    do
	{
		tmp = readl(0x40231388);
		tmp &= ((u32)0x1 << 3);
	}while(tmp != ((u32)0x1 << 3) && CHECK_TIMEOUT(slicebegin));
    if(tmp != ((u32)0x1 << 3))
	{
        reset_print_err("\r wait NOC enter spend time: %d slice\n", get_timer_slice_delta(slicebegin, bsp_get_slice_value()));
        return (int)RESET_MCORE_BEFORE_NOC_POWER_IDLE_ERR;
    }

    *(u32 *)STAMP_RESET_M3_NOC_ENTER_LPMODE_STEP2 = bsp_get_slice_value();
    slicebegin = bsp_get_slice_value();
    do
	{
		tmp = readl(0x40231384);
		tmp &= ((u32)0x1 << 3);
	}while(tmp != ((u32)0x1 << 3) && CHECK_TIMEOUT(slicebegin));
    if(tmp != ((u32)0x1 << 3))
	{
        reset_print_err("\r wait NOC enter spend time: %d slice\n", get_timer_slice_delta(slicebegin, bsp_get_slice_value()));
        return (int)RESET_MCORE_BEFORE_NOC_POWER_IDLEACK_ERR;
    }

    /*清除NMI中断*/
    *(u32 *)STAMP_RESET_M3_CLEAN_NMI = bsp_get_slice_value();
    tmp = readl(0x4023512C);
    tmp |= ((u32)0x1 << 12);
    writel(tmp, 0x4023512C);

     /*reset subsys*/
    *(u32 *)STAMP_RESET_M3_RESET_SUBSYS = bsp_get_slice_value();
    writel(0x10000000, 0x40235090);
    return 0;
}

__ao_func void modem_subsys_unreset(void)
{
    u32 tmp = 0;
    u32 slicebegin = 0;

    /*unreset subsys*/
    writel(0x804, 0x40235050);
    writel(0x18000000, 0x40235064);
    writel(0x10000000, 0x40235094);

	hwspin_lock_timeout(NOC_LOCK_ID, WAITFVR); /* 当前分支引用不到，2014/06/05合入AP主线 */
    /*配置NOC退出低功耗模式*/
    tmp = readl(0x40231380);
    tmp &= 0xFFFFFFF7;
    writel(tmp, 0x40231380);
	hwspin_unlock(NOC_LOCK_ID);

    /*等待NOC退出低功耗模式*/
    slicebegin = bsp_get_slice_value();
    do
	{
		tmp = readl(0x40231388);
		tmp = (tmp >> 3) & 0x1;
	}while(tmp && CHECK_TIMEOUT(slicebegin));
    if(tmp){
        reset_print_err("\r wait NOC quit spend time: %d slice\n", get_timer_slice_delta(slicebegin, bsp_get_slice_value()));
        return;
    }
    slicebegin = bsp_get_slice_value();
    do
	{
		tmp = readl(0x40231384);
		tmp = (tmp >> 3) & 0x1;
	}while(tmp && CHECK_TIMEOUT(slicebegin));
    if(tmp){
        //reset_print_err("\r wait NOC quit spend time: %d slice\n", get_timer_slice_delta(slicebegin, bsp_get_slice_value()));
        return;
    }

    /*配置error probe特性enable*/
    tmp = readl(0xA8080408);
    tmp |= ((u32)0x1 << 0);
    writel(tmp, 0xA8080408);

    /* sec config*/
    /*writel(0x0, HI_SYSCTRL_BASE_ADDR + HI_SEC_CTRL0_OFFSET);*/
	tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_SEC_CTRL0_OFFSET);
	tmp = tmp & ~((u32)0x1 << 9);  /*nsec-read ok*/
	writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_SEC_CTRL0_OFFSET)

    /* 1 2 mtcmos power up and wait for complete */
    writel(0x1<<1, HI_SYSCTRL_BASE_ADDR + HI_PWR_CTRL6_OFFSET);

    do
	{
		tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_PWR_STAT1_OFFSET);
		tmp = (tmp >> 1) & 0x1;
	}while(!tmp);
    udelay(30);

    mdm_a9pll_init();

	mdm_bbepll_init();

    mdm_bbppll_init();

    /* a9 dsp ref_clk enable*/
    writel(0x3<<24, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKEN3_OFFSET);

    /* 13 bus div: 0,0,3*/
    writel(0x40040300, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

    /* 14 switch on a9 pll*/
    writel(0x40010300, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

    /* 15 enable a9 and L2 clk */
    writel(0x3<<3, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKEN4_OFFSET);

    /* 17 disable iso */
    writel(0x1<<1, HI_SYSCTRL_BASE_ADDR + HI_PWR_CTRL5_OFFSET);

    *(u32 *)STAMP_UNRESET_M3_UNRESET_SUBSYS = bsp_get_slice_value();
}

__ao_func s32 send_msg_to_acore(u32 msg)
{
	u32 channel_id = ICC_CHANNEL_ID_MAKEUP(ICC_CHN_MCORE_ACORE, MCORE_ACORE_FUNC_RESET);
	s32 ret = RESET_ERROR;

	//reset_print_debug("(%d) channel_id=0x%x\n", ++g_mreset_ctrl.main_stage, channel_id);

	ret = bsp_icc_send((u32)ICC_CPU_APP, channel_id, (u8 *)(&msg), sizeof(msg));
	if(ret < 0)
	{
		reset_print_err("Fail to reply msg to cpu%d\n", ICC_CPU_MODEM);
		return RESET_ERROR;
	}

	return RESET_OK;
}

extern void pm_mdma9_nvic_disable(void);
extern void pm_mdma9_nvic_enable(void);
extern void bsp_socp_ccore_reset_stop_channel(void);

__ao_func s32 msg_from_ap_ipc(union ipc_data *msg)
{
	u32 reset_info = 0;
    int irqlock = 0;
	u32 action = 0xff;
	u32 stage  = 0xff;
	s32 ret = RESET_ERROR;

	if(msg->data[0]== AP_TO_LPM3_IPC_FLAG)
	{
		reset_info = (u32)msg->data[1];
		stage  = RESET_STAGE_GET(reset_info);
		action = RESET_STAGE_GET(reset_info);
		printk("reset_info=0x%x, stage=0x%x, action=0x%x\n", reset_info, stage, action);
		local_irq_save(irqlock);
	    switch(stage)
	    {
			/* 复位前 */
			case DRV_RESET_CALLCBFUN_RESET_BEFORE:
				wake_lock(MODEM_MASK);

				g_mreset_ctrl.main_stage = 0;
				ccore_msg_switch_off(g_mreset_ctrl.multicore_msg_switch, CCORE_STATUS);
				pm_mdma9_nvic_disable(); /* 屏蔽唤醒C核的中断 */
				ccore_ipc_disable();
				(void)bsp_ipf_reset_ccore_lpm3_cb(DRV_RESET_CALLCBFUN_RESET_BEFORE, 0);
				ipc_modem_reset_cb(DRV_RESET_CALLCBFUN_RESET_BEFORE, 0);
				reset_ipc_status_bakup();
				bsp_socp_ccore_reset_stop_channel();

				ret = modem_subsys_reset();
				if (ret)
				{
					msg->data[1] = (u32)ret;
					break;
				}
				modem_subsys_unreset();
				cpufreq_resume();
				reset_ipc_status_resume();
				msg->data[1] = (u32)RESET_MCORE_BEFORE_RESET_OK;

				if (MODEM_POWER_OFF == action)
				{
					wake_unlock(MODEM_MASK);
				}
				break;

			/* 复位中 */
			case DRV_RESET_CALLCBFUN_RESETING:
				wake_lock(MODEM_MASK);

				ccore_msg_switch_on(g_mreset_ctrl.multicore_msg_switch, CCORE_STATUS);
				pm_mdma9_nvic_enable(); /* 屏蔽唤醒C核的中断重新打开 */
				ipc_modem_reset_cb(DRV_RESET_CALLCBFUN_RESETING, 0);
				ccore_ipc_enable();
				//ccore_freq_drop();
				bsp_wdt_enable();
				modem_a9_unreset();
				msg->data[1] = (u32)RESET_MCORE_RESETING_OK;
				break;

			/* 复位后 */
			case DRV_RESET_CALLCBFUN_RESET_AFTER:
				(void)bsp_ipf_reset_ccore_lpm3_cb(DRV_RESET_CALLCBFUN_RESET_AFTER, 0);
				msg->data[1] = (u32)RESET_MCORE_AFTER_RESET_OK;
				break;
			default:
				break;
	    }
		local_irq_restore(irqlock);

	}
	return 0;
}

__ao_func s32 bsp_reset_init(void)
{
	memset((void *)&g_mreset_ctrl, 0, sizeof(g_mreset_ctrl));
	g_mreset_ctrl.multicore_msg_switch = 1;

	if(ipc_request_callback(OBJ_MODEM, CMD_SETTING, msg_from_ap_ipc))
	{
		reset_print_err("ipc_request_callback error\n");
		goto fail;
	}

	g_mreset_ctrl.boot_mode = CCORE_BOOT_NORMAL;
	g_mreset_ctrl.state = 1;

	reset_print_err("ok\n");
	return 0;
fail:
	reset_print_err("error\n");
	return 1;
}

__ao_func s32 bsp_reset_ccpu_status_get(void)
{
	enum RESET_MULTICORE_CHANNEL_STATUS channel_status = CCORE_STATUS;
	return (g_mreset_ctrl.multicore_msg_switch & channel_status) ? 1 : 0;
}

#else  /* !CONFIG_BALONG_MODEM_RESET */

__ao_func s32 bsp_reset_ccpu_status_get(void)
{
	return 1;
}

#endif /* end of CONFIG_BALONG_MODEM_RESET */

