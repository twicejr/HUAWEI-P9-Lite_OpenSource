/*************************************************************************
*   版权所有(C) 2008-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  reset_balong.c
*
*   作    者 :  y00184236
*
*   描    述 :  本文件主要完成C核单独复位主控流程
*
*   修改记录 :  2014年02月15日  v1.00  y00184236  创建
*************************************************************************/
#include <osl_cache.h>
#include <securec.h>
#include <bsp_pm.h>
#include <bsp_reset.h>
#include <mdrv_misc.h>
#include <mdrv_sync.h>
#include <socp_balong.h>
#include <bsp_gic_pm.h>
#include <bsp_hwadp.h>
#include <bsp_wakelock.h>
#include "reset_balong.h"
/*lint --e{539,666,722,801,830} */

static unsigned int scbakdata13_offset = 0;
u32 print_sw = 1;
#define  reset_print_debug(fmt, ...) \
do {                               \
    if (print_sw)    \
        reset_print_err(fmt, ##__VA_ARGS__);\
} while (0)

#define CCORE_RST_OK                  (0)
#define CCORE_RST_ERR                 (-1)

#define CCORE_RST_TIME_PRINT(a)   \
    do{ \
        reset_print_debug("\r wait idle spend time: %d slice\n", (bsp_get_slice_value() - a)); \
    }while(0)

struct ccore_reset_ctrl g_reset_ctrl = {0};
struct wake_lock reset_wakelock;

int mdrv_sysboot_ok(void)
{
	reset_print_debug("boot mode=0x%x\n", readl(get_scbakdata13()));
	if(!bsp_reset_ccore_is_reboot())
	{
		reset_print_debug("normal\n");
		return 0;
	}
	else
	{
		bsp_ipc_int_send(IPC_CORE_ACORE, g_reset_ctrl.ipc_send_irq_reboot_ok); /* [false alarm]:fortify */
		wake_unlock(&reset_wakelock);
		reset_print_debug("reboot\n");
	}

	return 0;

}

/*****************************************************************************
 函 数 名  : ccpu_reset_hdlc_and_wait_idle
 功能描述  : c核复位后关闭并等待hdlc进入空闲态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : ccpu_reset_hdlc_and_wait_idle
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月05日
    修改内容   : 新生成函数

*****************************************************************************/
int ccpu_reset_hdlc_and_wait_idle(void)
{
    unsigned int regvalue = 0;;
    unsigned int u32slicebegin = 0;

    if (NULL != mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_HDLC)) {
        /* reset HDLC*/
        writel(0x1, (unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_HDLC) + 0x0);

        u32slicebegin = bsp_get_slice_value();
        do{
            regvalue = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_HDLC) + 0x0);
        }while(regvalue && CHECK_TIMEOUT(u32slicebegin));
        if(0x0 != regvalue){
            bsp_reset_timestamp((0x1U << ENUM_RESET_HDLC)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
            return CCORE_RST_ERR;
        }
    }

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_HDLC_SOFT_RESET);

    return CCORE_RST_OK;
}

/*****************************************************************************
 函 数 名  : ccpu_reset_cicom_and_wait_idle
 功能描述  : c核复位后关闭并等待cicom进入空闲态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : ccpu_reset_cicom_and_wait_idle
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    修改内容   : 新生成函数

*****************************************************************************/
int ccpu_reset_cicom_and_wait_idle(void)
{
    unsigned int regvalue = 0;
    unsigned int regvalue1 = 0;
    unsigned int u32slicebegin = 0;

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_CICOM0_SOFT_RESET);

    if (NULL != mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM0)) {
        u32slicebegin = bsp_get_slice_value();
        do{
            regvalue = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM0) + 0x28);
            regvalue1 = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM0) + 0x128);
        }while((regvalue || regvalue1)&& CHECK_TIMEOUT(u32slicebegin));
        if((0x0 != regvalue)||(0x0 != regvalue1)){
            bsp_reset_timestamp((0x1U << ENUM_RESET_CICOM)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
            return CCORE_RST_ERR;
        }
    }

    if (NULL != mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM1)) {
        u32slicebegin = bsp_get_slice_value();
        do{
            regvalue = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM1) + 0x28);
            regvalue1 = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM1) + 0x128);
        }while((regvalue || regvalue1)&& CHECK_TIMEOUT(u32slicebegin));
        if((0x0 != regvalue)||(0x0 != regvalue1)){
            bsp_reset_timestamp((0x1U << ENUM_RESET_CICOM)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
            return CCORE_RST_ERR;
        }
    }

    if (NULL != mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM0)) {
        /*复位cicom0*/
        regvalue = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM0) + 0x0);
        regvalue |= (unsigned int)0x1;
        writel(regvalue, (unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM0) + 0x0);
    }

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_CICOM1_SOFT_RESET);

    if (NULL != mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM1)) {
        /*复位cicom1*/
        regvalue = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM1) + 0x0);
        regvalue |= (unsigned int)0x1;
        writel(regvalue, (unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_CICOM1) + 0x0);
    }

    return CCORE_RST_OK;
}

/*****************************************************************************
 函 数 名  : ccpu_reset_upacc_and_wait_idle
 功能描述  : c核复位后关闭并等待upacc进入空闲态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : ccpu_reset_upacc_and_wait_idle
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    修改内容   : 新生成函数

*****************************************************************************/
int ccpu_reset_upacc_and_wait_idle(void)
{
    unsigned int regvalue = 0;
    unsigned int u32slicebegin = 0;

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_UPACC_ENTER_IDLE_1);

    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_UPACC) + 0x0);
        regvalue &= (unsigned int)0x3;
    }while((0x0 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x0 != regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_UPACC_STEP1)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        return CCORE_RST_ERR;
    }

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_UPACC_ENTER_IDLE_2);
    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_UPACC) + 0x100);
        regvalue &= (unsigned int)0x3;
    }while((0x0 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x0 != regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_UPACC_STEP2)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        return CCORE_RST_ERR;
    }

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_UPACC_ENTER_IDLE_3);
    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = readl((unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_UPACC) + 0x200);
        regvalue &= (unsigned int)0x3;
    }while((0x0 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x0 != regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_UPACC_STEP3)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        return CCORE_RST_ERR;
    }

	/*disable UPACC*/
	writel(0x0,(unsigned long)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_UPACC) + 0xD8);

    return CCORE_RST_OK;
}

int (*master_idle_func[MASTER_IDLE_SUM])(void);

int bsp_register_master_idle(BSP_MASTER_IDLE_E type, MASTER_IDLE_HOOK_FUNC master_idle)
{
    if(type < MASTER_IDLE_SUM)
        master_idle_func[type] = master_idle;
    else {
        reset_print_err("master enter idle register fail type: %d\n", type);
        return BSP_ERROR;
    }
    return BSP_OK;
}

void bsp_modem_master_enter_idle(void)
{
    unsigned int i;
    unsigned long flags = 0;
    UNUSED(flags);
    local_irq_save(flags);
    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_MASTER_ENTER_IDLE);

    /*lint --e{701}*/
    for(i = 0; i < MASTER_IDLE_SUM; i++) {
        if (master_idle_func[i] != NULL) {
            bsp_reset_timestamp((0x1 << (i<<1))|*(u32 *)STAMP_RESET_MASTER_INOUT_IDLE, STAMP_RESET_MASTER_INOUT_IDLE);
            master_idle_func[i]();
            bsp_reset_timestamp((0x3 << (i<<1))|*(u32 *)STAMP_RESET_MASTER_INOUT_IDLE, STAMP_RESET_MASTER_INOUT_IDLE);
        }
    }

    (void)osl_cache_flush_all();

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_MASTER_IDLE_QUIT);
    return;/*lint !e438*/
}

/*****************************************************************************
 函 数 名  : FIQ_IntHandle
 功能描述  : 中断处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月20日
    作    者   : x68638
    修改内容   : 新生成函数

*****************************************************************************/
static void reset_stamp_addr_value(void)
{
    unsigned int len = 0;

    len = STAMP_RESET_MASTER_IDLE_QUIT - STAMP_RESET_IDLE_FAIL_COUNT;
    bsp_reset_timestamp(0xcccccccc, STAMP_RESET_BASE_ADDR);
    (void)memset_s((void*)STAMP_RESET_IDLE_FAIL_COUNT, len, 0, len);
}

void FIQ_IntHandle(void)
{
    /* 清 NMI 中断 */
    u32 tmp = 0;
    tmp = readl((unsigned long)bsp_sysctrl_addr_byindex(sysctrl_ap_pericrg) + 0x12c);
    tmp |= (((u32)0x1 << 12));
    writel(tmp, (unsigned long)bsp_sysctrl_addr_byindex(sysctrl_ap_pericrg) + 0x12c);

    g_reset_ctrl.fiq_cnt++;

    bsp_reset_timestamp(g_reset_ctrl.fiq_cnt, STAMP_RESET_FIQ_COUNT);

	/* 关闭gic，确保ccore不再接收中断 */
	gic_cpu_disable();

    reset_stamp_addr_value();
	if(!pm_in_waiting_pd()){
		bsp_modem_master_enter_idle();
	}
	bsp_ipc_int_send(IPC_CORE_ACORE, g_reset_ctrl.ipc_send_irq_in_idle);

	g_reset_ctrl.fiq_out++;
	writel(g_reset_ctrl.fiq_out, STAMP_RESET_FIQ_OUT_COUNT);

    /* coverity[INFINITE_LOOP] */
    /* coverity[no_escape] */
    while(1)
        asm volatile ("wfe;");/*lint !e123 */
}

void reset_ipc_isr(u32 data)
{
	wake_lock(&reset_wakelock);
	(void)mdrv_sync_give(SYNC_MODULE_RESET);
	//asm volatile ( "wfi;");
}

unsigned long get_scbakdata13(void)
{
	return ((unsigned long)bsp_sysctrl_addr_byindex(sysctrl_ao) + scbakdata13_offset);
}

int reset_of_node_init(void)
{
	struct device_node *node = NULL;
	int i, ret = RESET_OK;

	node = of_find_compatible_node(NULL, NULL, "hisilicon,cp_reset_mdm");
	if (!node)
	{
		reset_print_err("dts node not found!\n");
		return RESET_ERROR;
	}

	ret = of_property_read_u32(node, "scbakdata13", &scbakdata13_offset);
	if(ret)
	{
		reset_print_err("read scbakdata13 from dts is failed,ret = %d!\n", ret);
		return RESET_ERROR;
	}

	for(i = 0; i < MASTER_IDLE_SUM; i++)
		master_idle_func[i] = NULL;

	reset_print_err("ok\n");

	return RESET_OK;
}

s32 bsp_reset_init(void)
{
    (void)memset_s(&(g_reset_ctrl), sizeof(g_reset_ctrl), 0, sizeof(g_reset_ctrl));

    wake_lock_init(&reset_wakelock, PWRCTRL_SLEEP_RESET, "reset_wakeup");

    (void)bsp_register_master_idle(UPACC_IDLE,ccpu_reset_upacc_and_wait_idle);
    (void)bsp_register_master_idle(CICOM_IDLE,ccpu_reset_cicom_and_wait_idle);
    (void)bsp_register_master_idle(HDLC_IDLE, ccpu_reset_hdlc_and_wait_idle);

	g_reset_ctrl.ipc_send_irq_in_idle = IPC_ACPU_INT_SRC_CCPU_RESET_IDLE;
	g_reset_ctrl.ipc_send_irq_reboot_ok = IPC_ACPU_INT_SRC_CCPU_RESET_SUCC;
	g_reset_ctrl.ipc_recv_irq_wakeup = IPC_CCPU_INT_SRC_ACPU_RESET;

    g_reset_ctrl.stamp_ccpu_addr = STAMP_RESET_BASE_ADDR;
    g_reset_ctrl.stamp_m3_reset_addr = STAMP_RESET_M3_BASE_ADDR;
    g_reset_ctrl.stamp_m3_unreset_addr = STAMP_UNRESET_M3_BASE_ADDR;
	if (bsp_ipc_int_connect(g_reset_ctrl.ipc_recv_irq_wakeup, (voidfuncptr)reset_ipc_isr, 0))
	{
		goto ipc_err;
	}
	if (bsp_ipc_int_enable(g_reset_ctrl.ipc_recv_irq_wakeup))
	{
		goto ipc_err;
	}
	if (!bsp_reset_ccore_is_reboot())
	{
		g_reset_ctrl.fiq_cnt = 0;
		g_reset_ctrl.fiq_out = 0;
		(void)memset_s((void*)STAMP_RESET_FIQ_OUT_COUNT, 4, 0, 4);
		bsp_reset_timestamp(0x0, STAMP_RESET_FIQ_COUNT);
		bsp_reset_timestamp(0x0, STAMP_RESET_IDLE_FAIL_COUNT);
	}
	else
	{
		wake_lock(&reset_wakelock);
	}

    /*此标记用于记录失败*/
    if(*(u32 *)(STAMP_RESET_IDLE_FAIL_COUNT)){
        reset_print_err("master enter idle fail cnt: 0x%x\n", *(u32 *)(STAMP_RESET_IDLE_FAIL_COUNT));
    }
	g_reset_ctrl.fiq_cnt = *(u32 *)(STAMP_RESET_FIQ_COUNT);
	g_reset_ctrl.fiq_out = readl(STAMP_RESET_FIQ_OUT_COUNT);
	reset_print_err("master enter fiq cnt:%d, out_fiq_cnt:%d\n", g_reset_ctrl.fiq_cnt, g_reset_ctrl.fiq_out);

	g_reset_ctrl.state = 1;
	reset_print_err("ok\n");
	return 0;

ipc_err:
	reset_print_err("ipc error\n");
	return 0;

}

