#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/hisi/hisi_mailbox.h>
#include <linux/hisi/hisi_mailbox_dev.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/hisi_rproc.h>
#include <linux/hisi/ipc_msg.h>
#include <linux/hisi/util.h>

#include "../../mntn_filesys.h"
#include "../platform_ap/rdr_hisi_platform.h"
#include "../rdr_print.h"
#include "../rdr_inner.h"
#include "../rdr_field.h"
#include "rdr_hisi_lpm3.h"

#include <soc_acpu_baseaddr_interface.h>
#include <soc_syscounter_interface.h>
#include <soc_isp_watchdog_interface.h>
#include <soc_sctrl_interface.h>
#include <global_ddr_map.h>

#define M3_WDT_TIMEOUT_IRQ_NUM 206
#define AP_WDT_TIMEOUT_IRQ_NUM 77

enum RDR_LPM3_SYSTEM_ERROR_TYPE {
	M3_WDT_TIMEOUT = HISI_BB_MOD_LPM_START,
	AP_WDT_TIMEOUT,
	SYSTEM_ERROR_TYPE_MAX = HISI_BB_MOD_LPM_END,
};

#define LPMCU_RESET_OFF_MODID_PANIC     (0x1)
#define LPMCU_RESET_OFF_MODID_WDT       (0x2)

/*
如下PSCI_MSG_TYPE_M3_WDTTIMEOUT 等宏定义，如下三个文件要保持一致:
kernel\drivers\watchdog\sp805_wdt.c
kernel\drivers\hisi\mntn\blackbox\platform_lpm3\rdr_hisi_lpm3.c
vendor\hisi\confidential\lpmcu\include\psci.h
*/
#define PSCI_MSG_TYPE_M3_CTXSAVE IPC_CMD(OBJ_AP, OBJ_LPM3, CMD_INQUIRY, 0)
/*lint -emacro(750,*)*/
#define PSCI_MSG_TYPE_M3_WDTTIMEOUT IPC_CMD(OBJ_AP, OBJ_LPM3, CMD_INQUIRY, 1)
/*lint +emacro(750,*)*/
#define PSCI_MSG_TYPE_M3_RDRBUF IPC_CMD(OBJ_AP, OBJ_LPM3, CMD_INQUIRY, 2)
#define PSCI_MSG_TYPE_M3_PANIC_OFF IPC_CMD(OBJ_AP, OBJ_LPM3, CMD_INQUIRY, 3)
#define PSCI_MSG_TYPE_M3_STAT_DUMP IPC_CMD(OBJ_AP, OBJ_LPM3, CMD_INQUIRY, 4)

#define LPM3_RDR_SAVE_DONE IPC_CMD(OBJ_LPM3, OBJ_AP, CMD_NOTIFY, TYPE_RESET)


static u64 current_core_id = RDR_LPM3;
static struct rdr_register_module_result current_info;

u64 rdr_lpm3_buf_addr;
u32 rdr_lpm3_buf_len;

char *g_lpmcu_rdr_ddr_addr;
static struct semaphore rdr_lpm3_sem;
static volatile pfn_cb_dump_done pfn_cb_dumpdone;

static volatile u32 g_modid;

/*static char* counter_base;*/
static char *sctrl_base;

/* ap address -> m3 address */
u64 address_map(u64 orig_addr)
{
	u64 mapped_addr = orig_addr;
	return mapped_addr;
}

void m3_nmi_send(void)
{
	/* SCLPMCUCTRL nmi_in */
	pr_err("%s start\n", __func__);
	/* rdr will send the NMI to lpm3 */
	if (sctrl_base) {
		writel(0x1 << 2, (void *)(SOC_SCTRL_SCLPMCUCTRL_ADDR(sctrl_base)));/* the addr need ioremap */
	} else {
		pr_err("%s err\n", __func__);
	}
	pr_err("%s end\n", __func__);
}
#define LPMCU_DDR_MEM_PART_PATH_LEN 48
char g_lpmcu_ddr_memory_path[LOG_PATH_LEN + LPMCU_DDR_MEM_PART_PATH_LEN];
static void fn_dump(u32 modid, u32 etype, u64 coreid,
				char *pathname, pfn_cb_dump_done pfn_cb)
{
	s32 ret = -1;
	u32 msg[2] = {PSCI_MSG_TYPE_M3_CTXSAVE, 0};
	/*pr_err("[%s] [0x%x 0x%x] start\n", __func__, readl(SOC_SYSCOUNTER_CNTCV_H32_ADDR(counter_base)),
											readl(SOC_SYSCOUNTER_CNTCV_L32_ADDR(counter_base)));*/

	pr_err("modid:0x%x,etype:0x%x,coreid:0x%llx,%s,pfn_cb:%p\n", modid, etype, coreid, pathname, pfn_cb);
	msg[1] = modid;
	pfn_cb_dumpdone = pfn_cb;
	g_modid = modid;
	strncpy(g_lpmcu_ddr_memory_path, pathname, LOG_PATH_LEN-1);

	ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17, (mbox_msg_t *)&msg, 2);
	if (ret != 0) {
		pr_err("%s:RPROC_ASYNC_SEND failed! return (0x%x)\n", __func__, ret);
	}

	pr_err("%s end\n", __func__);
	return;
}
static void fn_reset(u32 modid, u32 etype, u64 coreid)
{
	/*pr_err("[%s] [0x%x 0x%x] start\n", __func__, readl(SOC_SYSCOUNTER_CNTCV_H32_ADDR(counter_base)),
											readl(SOC_SYSCOUNTER_CNTCV_L32_ADDR(counter_base)));
	pr_err("%s end\n", __func__);*/
	return;
}


static irqreturn_t m3_wdt_irq_handler(int irq, void *data)
{
	pr_err("enter %s, irq num %d\n", __func__, irq);
	disable_irq_nosync(irq);
	m3_nmi_send();
	return IRQ_HANDLED;
}

static int rdr_lpm3_msg_handler(struct notifier_block *nb,
										unsigned long len, void *msg)
{
	u32 *_msg = msg;
	pr_err("%s, [lpm3] -> [ap]: 0x%x\n", __func__, _msg[0]);
	if (_msg[0] == LPM3_RDR_SAVE_DONE) {	/* lpm3 -> ap: "my sys context save is done" */
		up(&rdr_lpm3_sem);
		pr_err("%s lpm3 tell me that its sys context has saved\n", __func__);
	}
	return 0;
}

/* work for rdr lpm3 */
static int rdr_lpm3_thread_body(void *arg)
{
	char *lpmcu_ddr_base = NULL;
	while (1) {
		if (down_interruptible(&rdr_lpm3_sem)) {
			return -1;
		}
		pr_err(" %s %d pfn_cb_dumpdone:%p\n", __func__, __LINE__, pfn_cb_dumpdone);
		if (pfn_cb_dumpdone != NULL) {
			strncat(g_lpmcu_ddr_memory_path, "/lpmcu_log/lpmcu_ddr_memory.bin", LPMCU_DDR_MEM_PART_PATH_LEN);
			lpmcu_ddr_base = (char *)ioremap((phys_addr_t)HISI_RESERVED_LPMX_CORE_PHYMEM_BASE_UNIQUE, HISI_RESERVED_LPMX_CORE_PHYMEM_SIZE);
			if (lpmcu_ddr_base) {
				mntn_filesys_write_log(g_lpmcu_ddr_memory_path, lpmcu_ddr_base, HISI_RESERVED_LPMX_CORE_PHYMEM_SIZE, 0);
				iounmap(lpmcu_ddr_base);
				lpmcu_ddr_base = NULL;
			}
			pfn_cb_dumpdone(g_modid, current_core_id);
			pfn_cb_dumpdone = NULL;
			pr_err("modid:0x%x,coreid:0x%llx\n", g_modid, current_core_id);
		}
	}
}

int rdr_lpm3_reset_off(int mod, int sw)
{
	s32 ret = -1;
	unsigned int msg[2] = {0};
	u32 tmp = 0;

	if (LPMCU_RESET_OFF_MODID_PANIC == mod) {
		msg[0] = PSCI_MSG_TYPE_M3_PANIC_OFF;
		msg[1] = sw;

		ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17, (mbox_msg_t *)msg, 2);
		if (ret != 0) {
			pr_err("RPROC_ASYNC_SEND failed! return 0x%x, &msg:(%p)\n", ret, msg);
			return ret;
		}
		pr_err("%s: (ap)->(lpm3) ipc send (0x%x 0x%x)!\n", __func__, msg[0], msg[1]);
	} else if (LPMCU_RESET_OFF_MODID_WDT == mod) {
		if (sctrl_base) {
			tmp = readl(SOC_SCTRL_SCBAKDATA10_ADDR(sctrl_base));
			if (sw) {
				tmp &= ~((unsigned int)0x1 << 2);
			} else {
				tmp |= ((unsigned int)0x1 << 2);
			}
			writel(tmp, (void *)(SOC_SCTRL_SCBAKDATA10_ADDR(sctrl_base)));
		}
	}

	return 0;

}

#if 0
int rdr_lpm3_panic_off(int sw)
{
	s32 ret;
	unsigned int msg[2] = {0};
	msg[0] = PSCI_MSG_TYPE_M3_PANIC_OFF;
	msg[1] = sw;

	ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17, (mbox_msg_t *)msg, 2);

	if (ret != 0) {
		pr_err("RPROC_ASYNC_SEND failed! return 0x%x, &msg:(%p)\n", ret, msg);
		return ret;
	}
	pr_err("%s: (ap)->(lpm3) ipc send (0x%x 0x%x)!\n", __func__, msg[0], msg[1]);
	return 0;
}
#endif

int rdr_lpm3_stat_dump(void)
{
	s32 ret;
	unsigned int msg = PSCI_MSG_TYPE_M3_STAT_DUMP;

	ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17, (mbox_msg_t *)&msg, 1);

	if (ret != 0) {
		pr_err("RPROC_ASYNC_SEND failed! return 0x%x, msg:(0x%x)\n", ret, msg);
		return ret;
	}

	msleep(1);
	return 0;
}

static struct notifier_block rdr_ipc_block;
int __init rdr_lpm3_init(void)
{
	struct rdr_module_ops_pub s_module_ops;
	struct rdr_exception_info_s einfo;
	s32 ret = -1;
	static u32 msg[4] = {0};
	pr_err("enter %s\n", __func__);


	/*counter_base = (char*)ioremap((phys_addr_t)SOC_ACPU_SYS_CNT_BASE_ADDR,0x1000);*/
	sctrl_base = (char *)ioremap((phys_addr_t)SOC_ACPU_SCTRL_BASE_ADDR, 0x1000);

	/*pr_err("counter_base: %p, sctrl_base: %p\n", counter_base, sctrl_base);*/
	pr_err("sctrl_base: %p\n", sctrl_base);


	ret = request_irq(M3_WDT_TIMEOUT_IRQ_NUM, m3_wdt_irq_handler, 0, "m3 wdt handler", NULL);
	if (ret != 0) {
		pr_err("request_irq m3_wdt_irq_handler failed! return 0x%x\n", ret);
		/*return ret;*/
	}


	rdr_ipc_block.next = NULL;
	rdr_ipc_block.notifier_call = rdr_lpm3_msg_handler;
	ret = RPROC_MONITOR_REGISTER(HISI_RPROC_RDR_MBX1, &rdr_ipc_block);
	if (ret != 0) {
		pr_info("%s:RPROC_MONITOR_REGISTER failed", __func__);
		return ret;
	}

	sema_init(&rdr_lpm3_sem, 0);
	if (!kthread_run(rdr_lpm3_thread_body, NULL, "rdr_lpm3_thread")) {
		pr_err("%s: create thread rdr_main_thread faild.\n", __func__);
		return -1;
	}

#if 0
	ret = request_irq(AP_WDT_TIMEOUT_IRQ_NUM, ap_wdt_irq_handler, 0, "ap wdt handler", NULL);
	if (ret != 0) {
		pr_err("request_irq ap_wdt_irq_handler failed! return 0x%x\n", ret);
		return ret;
	}
#endif

	s_module_ops.ops_dump = fn_dump;
	s_module_ops.ops_reset = fn_reset;
	ret = rdr_register_module_ops(current_core_id, &s_module_ops, &current_info);
	if (ret != 0) {
		pr_err("rdr_register_module_ops failed! return 0x%x\n", ret);
		return ret;
	}


	memset(&einfo, 0, sizeof(struct rdr_exception_info_s));
	einfo.e_modid = M3_WDT_TIMEOUT;
	einfo.e_modid_end = M3_WDT_TIMEOUT;
	einfo.e_process_priority = RDR_ERR;
	einfo.e_reboot_priority = RDR_REBOOT_WAIT;
	einfo.e_notify_core_mask = RDR_AP | RDR_LPM3;
	einfo.e_reset_core_mask = RDR_LPM3;
	einfo.e_reentrant = RDR_REENTRANT_DISALLOW;
	einfo.e_exce_type = LPM3_S_EXCEPTION;
	einfo.e_from_core = RDR_LPM3;
	memcpy(einfo.e_from_module, "RDR M3 WDT", sizeof("RDR M3 WDT"));
	memcpy(einfo.e_desc, "RDR M3 WDT",
			sizeof("RDR M3 WDT"));
	ret = rdr_register_exception(&einfo);


	rdr_lpm3_buf_addr = address_map(current_info.log_addr);
	rdr_lpm3_buf_len = current_info.log_len;

	g_lpmcu_rdr_ddr_addr = (char *)hisi_bbox_map((phys_addr_t)current_info.log_addr, current_info.log_len);

	if (g_lpmcu_rdr_ddr_addr)
		memset(g_lpmcu_rdr_ddr_addr, 0 , rdr_lpm3_buf_len);

	msg[0] = PSCI_MSG_TYPE_M3_RDRBUF;
	msg[1] = rdr_lpm3_buf_addr;
	msg[2] = rdr_lpm3_buf_addr >> 32;
	msg[3] = rdr_lpm3_buf_len;

	ret = RPROC_ASYNC_SEND(HISI_RPROC_LPM3_MBX17, (mbox_msg_t *)msg, 4);

	if (ret != 0) {
		pr_err("RPROC_ASYNC_SEND failed! return 0x%x, &msg:(%p)\n", ret, msg);
		/*return ret;*/
	}
	pr_err("%s: (ap)->(lpm3) ipc send (0x%x 0x%x 0x%x 0x%x)!\n", __func__, msg[0], msg[1], msg[2], msg[3]);

	(void)rdr_lpm3_reset_off(LPMCU_RESET_OFF_MODID_PANIC, check_himntn(HIMNTN_LPM3_PANIC_INTO_LOOP));

	return ret;
}

static void __exit rdr_lpm3_exit(void)
{
	return;
}


/* test code start */
/*
void test_sys_err()
{
    rdr_system_error(M3_WDT_TIMEOUT, 0x505050, 0xa0a0a);
}
*/
/* test code end */



subsys_initcall(rdr_lpm3_init);
module_exit(rdr_lpm3_exit);
