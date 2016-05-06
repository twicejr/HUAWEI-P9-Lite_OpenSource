#include <dsm/dsm_pub.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/io.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include "protocol.h"
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include "rdr_sensorhub.h"
#include <linux/hisi/hisi_rproc.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/wakelock.h>
#include <linux/notifier.h>
#include <linux/delay.h>


struct rdr_register_module_result current_sh_info;
static pfn_cb_dump_done pfn_cb_sh_dumpdone;
static u64 current_sh_core_id = RDR_IOM3; //const
static u32 g_sh_modid;
static struct semaphore rdr_sh_sem;
static struct semaphore rdr_exce_sem;
static void __iomem *sysctrl_base= NULL;
static void __iomem *watchdog_base= NULL;
static unsigned int *dump_vir_addr = NULL;
static struct wake_lock rdr_wl;

extern void msleep(unsigned int msecs);
extern void __disable_irq(struct irq_desc *desc, unsigned int irq, bool suspend);
extern void __enable_irq(struct irq_desc *desc, unsigned int irq, bool resume);
extern int iom3_need_recovery(void);
extern int write_customize_cmd_noresp(int tag, int cmd, const void *data, int length);

static int get_watchdog_base(void)
{
	struct device_node *np = NULL;

	if (watchdog_base == NULL) {
		np = of_find_compatible_node(NULL, NULL, "hisilicon,iomcu-watchdog");
		if (!np) {
			hwlog_err("can not find  watchdog node !\n");
			return -1;
		}
		watchdog_base = of_iomap(np, 0);
		if (watchdog_base == NULL) {
			hwlog_err("get watchdog_base  error !\n");
			return -1;
		}
	}
	return 0;
}

static int get_sysctrl_base(void)
{
	struct device_node *np = NULL;

	if (sysctrl_base == NULL) {
		np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
		if (!np) {
			hwlog_err("can not find  sysctrl node !\n");
			return -1;
		}
		sysctrl_base = of_iomap(np, 0);
		if (sysctrl_base == NULL) {
			hwlog_err("get sysctrl_base  error !\n");
			return -1;
		}
	}
	return 0;
}

struct CONFIG_ON_DDR *pConfigOnDDr;

#define WARN_LEVEL 2
#define INFO_LEVEL 3

int write_ramdump_info_to_sharemem(void)
{
	hwlog_info("%s start!\n", __func__);

	pConfigOnDDr = (struct CONFIG_ON_DDR *)ioremap(IOMCU_CONFIG_START, IOMCU_CONFIG_SIZE);
	if (pConfigOnDDr == NULL) {
      		hwlog_err("ioremap (%llx) failed in %s!\n", IOMCU_CONFIG_START, __func__);
		return -1;
	}

	pConfigOnDDr ->dumpaddr64 = current_sh_info.log_addr;
	pConfigOnDDr ->dumpsize = current_sh_info.log_len;
	pConfigOnDDr->LogBuffCBBackup.mutex = 0;
	pConfigOnDDr->log_level = INFO_LEVEL;


	hwlog_warn("%s dumpaddr low is %x, dumpaddr high is %x, dumplen is %x, end!\n", __func__, (u32)(pConfigOnDDr ->dumpaddr64), (u32)((pConfigOnDDr ->dumpaddr64)>>32), pConfigOnDDr ->dumpsize);

	return 0;
}

extern void dmd_log_report(int dmd_mark,const char *err_func, const char *err_msg);

void __send_nmi(void)
{
   if (sysctrl_base != NULL) {
       writel(0x2, sysctrl_base + SCIOMCUCTRL);
       writel(0x0, sysctrl_base + SCIOMCUCTRL);
   }
   else
       hwlog_err(" sysctrl_base is null!\n");
}

static void sh_dump( u32 modid, u32 etype, u64 coreid,
                char* pathname, pfn_cb_dump_done pfn_cb)
{
	hwlog_warn(" %s start!\n", __func__);

        dmd_log_report(DSM_SHB_ERR_IOM3_WDG, __func__, "watchdog reset, trigger rdr exception\n");

    __send_nmi();
	
	hwlog_warn(" ====================================\n");
	hwlog_warn(" modid:          [0x%x]\n", modid);
	hwlog_warn(" coreid:         [0x%llx]\n", coreid);
	hwlog_warn(" exce tpye:      [0x%x]\n", etype);
	hwlog_warn(" path name:      [%s]\n", pathname);
	hwlog_warn(" dump start:     [0x%llx]\n", current_sh_info.log_addr);
	hwlog_warn(" dump len:       [%d]\n", current_sh_info.log_len);
	hwlog_warn(" nve:            [0x%llx]\n", current_sh_info.nve);
	hwlog_warn(" callback:       [0x%p]\n", pfn_cb);
	hwlog_warn(" ====================================\n");
	pfn_cb_sh_dumpdone = pfn_cb;
	g_sh_modid = modid;
	up(&rdr_sh_sem);
}

static void sh_reset( u32 modid, u32 etype, u64 coreid)
{
	hwlog_warn(" %s start!\n", __func__);
	
	hwlog_warn(" ====================================\n");
	hwlog_warn(" modid:          [0x%x]\n", modid);
	hwlog_warn(" coreid:         [0x%llx]\n", coreid);
	hwlog_warn(" exce tpye:      [0x%x]\n", etype);
	hwlog_warn(" ====================================\n");

	if (dump_vir_addr != NULL) {
		memset(dump_vir_addr, 0, current_sh_info.log_len);
	}
	
#ifdef CONFIG_IOM3_RECOVERY	
	iom3_need_recovery();
#else
	restart_iom3();
#endif

	wake_unlock(&rdr_wl);
}

static int clean_rdr_memory(struct rdr_register_module_result rdr_info)
{
	int ret = 0;
	
	dump_vir_addr = (unsigned int *)hisi_bbox_map(rdr_info.log_addr, rdr_info.log_len);
	if (dump_vir_addr == NULL) {
      		hwlog_err("hisi_bbox_map (%llx) failed in %s!\n", rdr_info.log_addr, __func__);
		return -1;
	}
	memset(dump_vir_addr, 0, rdr_info.log_len);

	return ret;
}

static int rdr_sensorhub_register_core(void)
{
	struct rdr_module_ops_pub s_module_ops;
	int ret = -1;

	hwlog_info("%s start!\n", __func__);

	s_module_ops.ops_dump = sh_dump;
	s_module_ops.ops_reset = sh_reset;

	ret = rdr_register_module_ops(current_sh_core_id, &s_module_ops, &current_sh_info);
	if(ret != 0)
		return ret;
	
	ret = clean_rdr_memory(current_sh_info);
	if(ret != 0)
		return ret;

	hwlog_info("%s end!\n", __func__);
	
	return ret;
}

const char sh_module_name[] = "RDR_IOM7";
const char sh_module_desc[] = "RDR_IOM7 for watchdog timeout issue.";
static int sh_register_exception(void)
{
	struct rdr_exception_info_s einfo;
	int ret = -1;

	hwlog_info("%s start!\n", __func__);

	memset(&einfo, 0, sizeof(struct rdr_exception_info_s));
	einfo.e_modid = SENSORHUB_MODID;
	einfo.e_modid_end = SENSORHUB_MODID_END;
	einfo.e_process_priority = RDR_WARN;
	einfo.e_reboot_priority = RDR_REBOOT_NO;
	einfo.e_notify_core_mask = RDR_IOM3 | RDR_AP;
	einfo.e_reset_core_mask = RDR_IOM3;
	einfo.e_reentrant = RDR_REENTRANT_ALLOW;
	einfo.e_exce_type = IOM3_S_EXCEPTION;
	einfo.e_from_core = RDR_IOM3;
	einfo.e_upload_flag = RDR_UPLOAD_YES;
	memcpy(einfo.e_from_module, sh_module_name, sizeof(sh_module_name));
	memcpy(einfo.e_desc, sh_module_desc, sizeof(sh_module_desc));
	ret = rdr_register_exception(&einfo);

	hwlog_info("%s end!\n", __func__);

	return ret;
}

void wdt_stop(void)
{
	writel(REG_UNLOCK_KEY, watchdog_base + WDOGLOCK);
	writel(0x0, watchdog_base + WDOGCTRL);
	writel(0x1, watchdog_base + WDOGINTCLR);
	writel(0x01, watchdog_base + WDOGLOCK);
}

static irqreturn_t watchdog_handler(int irq, void *data)
{
	wdt_stop();

	hwlog_warn("%s start!\n", __func__);
	
	wake_lock(&rdr_wl);
	
	//release exception sem
	up(&rdr_exce_sem);

	return IRQ_HANDLED;
}

static int rdr_sh_thread(void *arg)
{
	hwlog_warn("%s start!\n", __func__);
	while(1) {	
		down(&rdr_sh_sem);
		hwlog_warn(" ==============dump sensorhub log start==============\n");
		hwlog_warn(" ... ... ... ... ... ... ... ... ... ... ... .\n");
		msleep(2000);
		hwlog_warn(" ==============dump sensorhub log end==============\n");
		if (pfn_cb_sh_dumpdone != NULL) {
			pfn_cb_sh_dumpdone(g_sh_modid, current_sh_core_id);
		}
	}
	return 0;
}

static int rdr_exce_thread(void *arg)
{
	hwlog_warn("%s start!\n", __func__);
	while (1) {
		down(&rdr_exce_sem);
		hwlog_warn(" ==============trigger exception==============\n");
		rdr_system_error(SENSORHUB_MODID, 0, 0);
	}
	return 0;
}

/*
return value
0:success
<0:error
*/
static int rdr_sensorhub_init_early(void)
{
	int ret = 0;
	//register module.
	ret = rdr_sensorhub_register_core();
	if (ret != 0 ) return ret;
	//write ramdump info to share mem
	ret = write_ramdump_info_to_sharemem();
	if (ret != 0 ) return ret;
	//regitster exception.
	ret = sh_register_exception(); //0:error
	if (ret == 0) 
		ret = -EINVAL;
	else
		ret = 0;
	
	return ret;
}

static int sensorhub_panic_notify(void)
{
    __send_nmi();
    printk("sensorhub_panic_notify\n");
    mdelay(25);
    return 0;
}

static struct notifier_block sensorhub_panic_block = {
    .notifier_call = sensorhub_panic_notify,
};




/*
return value
0:success
<0:error
*/
int rdr_sensorhub_init(void)
{
	int ret = 0;
	if(is_sensorhub_disabled())
	    return -1;
	if(0 != rdr_sensorhub_init_early()) {
       	hwlog_err("rdr_sensorhub_init_early faild.\n");
		ret = -EINVAL;
		return ret;
	}

	sema_init(&rdr_sh_sem, 0);
	if (!kthread_run(rdr_sh_thread, NULL, "rdr_sh_thread")) {
       	hwlog_err("create thread rdr_sh_main_thread faild.\n");
		ret = -EINVAL;
		return ret;
	}

	sema_init(&rdr_exce_sem, 0);
	if (!kthread_run(rdr_exce_thread, NULL, "rdr_exce_thread")) {
       	 hwlog_err("create thread rdr_sh_exce_thread faild.\n");
		ret = -EINVAL;
		return ret;
	}

	 ret = get_sysctrl_base();
	 if (ret != 0) {
       	        hwlog_err("get sysctrl addr faild.\n");
		ret = -EINVAL;
		return ret;
	}

	ret = get_watchdog_base();
	 if (ret != 0) {
       	        hwlog_err("get watchdog addr faild.\n");
		ret = -EINVAL;
		return ret;
	}
	 		
	ret = request_irq(WD_INT, watchdog_handler, 0, "watchdog", NULL);
	if (ret) {
		hwlog_err("%s failure requesting watchdog irq!\n", __func__);
		ret = -EINVAL;
		return ret;
	} else
		ret = 0;

	wake_lock_init(&rdr_wl, WAKE_LOCK_SUSPEND, "rdr_sensorhub");

    ret = atomic_notifier_chain_register(&panic_notifier_list, &sensorhub_panic_block);
    if (ret) {
       hwlog_err("%s atomic_notifier_chain_register failed !\n", __func__);
       ret = -EINVAL;
       return ret;
   }

	return ret;
}

