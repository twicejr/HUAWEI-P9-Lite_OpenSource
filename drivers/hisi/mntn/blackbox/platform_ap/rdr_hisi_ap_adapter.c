/*******************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
 文 件 名   : rdr_hisi_ap_adapter.c
 版 本 号   : 初稿
 作    者   : 蒋孝伟 00207786
 生成日期   : 2015年1月12日
 最近修改   :
 功能描述   : 基于RDR框架，AP侧适配，实现资源、异常初始化，dump及reset操作
 修改历史   :
 1.日  期   : 2015年1月12日
   作  者   : 蒋孝伟 00207786
 修改内容   : 创建文件

 *******************************************************************************/

/*******************************************************************************
  1 头文件包含
 *******************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/thread_info.h>
#include <linux/hardirq.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/kthread.h>
#include <linux/notifier.h>
#include <linux/delay.h>
#include <linux/syscalls.h>
#include <linux/preempt.h>
#include <asm/cacheflush.h>
#include <linux/kmsg_dump.h>
#include <linux/slab.h>
#include <linux/kdebug.h>

#include <linux/hisi/util.h>
#include <linux/hisi/rdr_pub.h>
#include "rdr_hisi_platform.h"
#include "rdr_hisi_ap_ringbuffer.h"
#include "../rdr_inner.h"
#include "../../mntn_filesys.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define BUFFER_SIZE			128
#define BUILD_DISPLAY_ID	"ro.confg.hw_systemversion"
#define SRC_KERNELDUMP		"/proc/balong/memory/kernel_dump"
#define SRC_DUMPEND		"/proc/balong/memory/dump_end"
#define SRC_LPMCU_DDR_MEMORY		"/proc/balong/memory/lpmcu_ddr_mem"
#define SRC_BL31_MNTN_MEMORY		"/proc/balong/memory/bl31_mntn_mem"

static AP_EH_ROOT *g_rdr_ap_root;
static AP_RECORD_PC *g_bbox_ap_record_pc;
u64 g_hisiap_addr;
static char g_log_path[LOG_PATH_LEN];
static int rdr_ap_init;
static void __iomem *sctrl_map_addr;
static void __iomem *g_32k_timer_l32bit_addr;
static void __iomem *g_32k_timer_h32bit_addr;
static struct rdr_register_module_result current_info;
static struct mutex dump_mem_mutex;
static u64 g_mi_notify_lpm3_addr;
static unsigned long long g_pmu_reset_reg;
int g_bbox_fpga_flag = -1;
/* -1 未初始化；0 非fpga板；1 fpga板 */
struct semaphore modemddrc_happen_sem;

#ifdef CONFIG_HISI_CORESIGHT_TRACE
AP_RECORD_ETR g_bbox_etr_info;	/* save etr head information */
u32 g_bbox_etr_info_init;
#endif

static unsigned int g_dump_buffer_size_tbl[HK_MAX] = {
	AP_TRACE_IRQ_SIZE,
	AP_TRACE_TASK_SIZE,
	AP_TRACE_CPU_IDLE_SIZE,
	AP_TRACE_WORKER_SIZE,
	AP_TRACE_CPU_ON_OFF_SIZE,
	AP_TRACE_SYSCALL_SIZE,
	AP_TRACE_HUNG_TASK_SIZE,
	AP_TRACE_BUDD_FAIL_SIZE,
	AP_TRACE_TASKLET_SIZE
};

/*struct rdr_exception_info_s {
struct list_head e_list;
u32 e_modid;
u32 e_modid_end;
u32 e_process_priority;
u32 e_reboot_priority;
u64 e_notify_core_mask;
u64 e_reset_core_mask;
u64 e_from_core;
u32 e_reentrant;
u32 e_exce_type;
u32 e_upload_flag;
u8  e_from_module[MODULE_NAME_LEN];
u8  e_desc[STR_EXCEPTIONDESC_MAXLEN];
u32 e_reserve_u32;
void*   e_reserve_p;
rdr_e_callback e_callback;
};*/
struct rdr_exception_info_s einfo[] = {
	{{0, 0}, MODID_AP_S_PANIC, MODID_AP_S_PANIC, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, AP_S_PANIC, RDR_UPLOAD_YES, "ap", "ap",
	 0, 0, 0},
	{{0, 0}, MODID_AP_S_NOC, MODID_AP_S_NOC, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, AP_S_NOC, RDR_UPLOAD_YES, "ap", "ap",
	 0, 0, 0},
	{{0, 0}, MODID_AP_S_DDRC_SEC, MODID_AP_S_DDRC_SEC, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, AP_S_DDRC_SEC, RDR_UPLOAD_YES, "ap",
	 "ap", 0, 0, 0},
	{{0, 0}, MODID_AP_S_COMBINATIONKEY, MODID_AP_S_COMBINATIONKEY,
	 RDR_ERR, RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, AP_S_COMBINATIONKEY, RDR_UPLOAD_YES,
	 "ap", "ap", 0, 0, 0},
	{{0, 0}, MODID_FASTBOOT_S_PANIC, MODID_FASTBOOT_S_PANIC,
	 RDR_ERR, RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, FASTBOOT_S_PANIC, RDR_UPLOAD_YES,
	 "fastboot", "fastboot", 0, 0, 0},
	{{0, 0}, MODID_AP_S_MAILBOX, MODID_AP_S_MAILBOX, RDR_WARN,
	 RDR_REBOOT_NO, RDR_AP, 0, RDR_AP,
	 RDR_REENTRANT_DISALLOW, AP_S_MAILBOX, RDR_UPLOAD_YES, "ap",
	 "ap", 0, 0, 0},
	{{0, 0}, MODID_AP_S_PMU, MODID_AP_S_PMU, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, AP_S_PMU, RDR_UPLOAD_YES, "ap pmu", "ap pmu",
	 0, 0, 0},
	 {{0, 0}, MODID_AP_S_SMPL, MODID_AP_S_SMPL, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, AP_S_SMPL, RDR_UPLOAD_YES, "ap smpl", "ap smpl",
	 0, 0, 0},
	 {{0, 0}, MODID_AP_S_SCHARGER, MODID_AP_S_SCHARGER, RDR_ERR,
	 RDR_REBOOT_NOW, RDR_AP, RDR_AP, RDR_AP,
	 RDR_REENTRANT_DISALLOW, AP_S_SCHARGER, RDR_UPLOAD_YES, "ap scharger", "ap scharger",
	 0, 0, 0},
};

/* 以下是给AP的其他维测模块、IP使用的dump内存 */
unsigned int g_dump_modu_mem_size_tbl[MODU_MAX] = {
	AP_DUMP_MEM_MODU_NOC_SIZE,
	AP_DUMP_MEM_MODU_DDR_SIZE,
#ifdef CONFIG_HISI_CORESIGHT_TRACE
	AP_DUMP_MEM_MODU_TMC_SIZE,
#endif
	AP_DUMP_MEM_MODU_GAP_SIZE
};

static int acpu_panic_loop_notify(struct notifier_block *nb,
				  unsigned long event, void *buf);
static int rdr_hisiap_panic_notify(struct notifier_block *nb,
				   unsigned long event, void *buf);
static int rdr_hisiap_die_notify(struct notifier_block *nb,
				 unsigned long event, void *pReg);
static int save_exception_info(void *arg);
static void get_product_version_work_fn(struct work_struct *work);
static int rdr_copy_file_apend(char *dst, char *src);

static struct notifier_block acpu_panic_loop_block = {
	.notifier_call = acpu_panic_loop_notify,
	.priority = INT_MAX,
};

static struct notifier_block rdr_hisiap_panic_block = {
	.notifier_call = rdr_hisiap_panic_notify,
	.priority = INT_MIN,
};

static struct notifier_block rdr_hisiap_die_block = {
	.notifier_call = rdr_hisiap_die_notify,
	.priority = INT_MIN,
};

static DECLARE_DELAYED_WORK(get_product_version_work,
			    get_product_version_work_fn);

extern struct cmdword reboot_reason_map[];
extern struct task_struct *g_last_task_ptr[NR_CPUS];

/*version < 32byte*/
void get_product_version(char *version, size_t count)
{
	struct file *fp;
	mm_segment_t old_fs;
	char buf[BUFFER_SIZE];
	char *p;
	int i;
	ssize_t length;

	if (IS_ERR_OR_NULL(version)) {
		printk(KERN_ERR "[%s], invalid para version [0x%p]!\n",
		       __func__, version);
		return;
	}
	memset(version, 0, count);

	/* 等待文件系统ok，读取/system/build.prop的ro.confg.hw_systemversion=BalongV100R001C50B310属性 */
	/* 不能在module_init调用 */
	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	fp = filp_open(SYSTEM_BUILD_POP, O_RDONLY, FILE_LIMIT);
	if (IS_ERR_OR_NULL(fp)) {
		set_fs(old_fs);
		printk(KERN_ERR "[%s], open [%s] failed! err [%p]\n",
		       __func__, SYSTEM_BUILD_POP, fp);
		return;
	}

	while ((length =
		vfs_read(fp, buf, BUFFER_SIZE, &fp->f_pos)) > 0) {
		for (i = 0; i < BUFFER_SIZE; i++) {
			if ('\n' == buf[i])
				break;	/* 找到完整1行 */
		}
		memset(buf, '\0', BUFFER_SIZE);
		vfs_llseek(fp, -length, SEEK_CUR);
		if (BUFFER_SIZE == i) {	/* 1行超过128byte */
			i--;
		}
		if (0 != i) {
			vfs_read(fp, buf, i, &fp->f_pos);
			p = strstr(buf, BUILD_DISPLAY_ID);
			if (NULL != p) {
				p = p + strlen(BUILD_DISPLAY_ID);
				if ('=' == *p) {
					p++;
					strncpy(version, p,
						strlen(p) >= count ? count - 1 : strlen(p));
					break;
				}
			}
			memset(buf, '\0', BUFFER_SIZE);
		} else {
			vfs_llseek(fp, 1, SEEK_CUR);	/* 去掉空行 */
		}
	}

	filp_close(fp, NULL);
	set_fs(old_fs);
	printk(KERN_ERR "[%s], version [%s]!\n", __func__, version);
}

void print_debug_info(void)
{
	int i;
	regs_info *regs_info = g_rdr_ap_root->dump_regs_info;

	printk(KERN_INFO "=================AP_EH_ROOT================");
	printk(KERN_INFO "[%s], dump_magic [0x%x]\n", __func__,
	       g_rdr_ap_root->dump_magic);
	printk(KERN_INFO "[%s], version [%s]\n", __func__,
	       g_rdr_ap_root->version);
	printk(KERN_INFO "[%s], modid [0x%x]\n", __func__,
	       g_rdr_ap_root->modid);
	printk(KERN_INFO "[%s], e_exce_type [0x%x],\n", __func__,
	       g_rdr_ap_root->e_exce_type);
	printk(KERN_INFO "[%s], coreid [0x%llx]\n", __func__,
	       g_rdr_ap_root->coreid);
	printk(KERN_INFO "[%s], slice [%llu]\n", __func__,
	       g_rdr_ap_root->slice);
	printk(KERN_INFO "[%s], enter_times [0x%x]\n", __func__,
	       g_rdr_ap_root->enter_times);
	printk(KERN_INFO "[%s], num_reg_regions [0x%x]\n", __func__,
	       g_rdr_ap_root->num_reg_regions);

	for (i = 0; i < g_rdr_ap_root->num_reg_regions; i++) {
		printk(KERN_INFO
		       "[%s], reg_name [%s], reg_base [0x%p], reg_size [0x%x], reg_dump_addr [0x%p]\n",
		       __func__, regs_info[i].reg_name,
		       (void *)regs_info[i].reg_base,
		       regs_info[i].reg_size,
		       regs_info[i].reg_dump_addr);
	}
}

static int check_addr_overflow(unsigned char *addr)
{
	unsigned char *max_addr;

	max_addr = g_rdr_ap_root->rdr_ap_area_map_addr +
	    g_rdr_ap_root->ap_rdr_info.log_len;
	if ((addr < g_rdr_ap_root->rdr_ap_area_map_addr)
	    || (addr >= max_addr)) {
		return 1;
	}
	return 0;
}

/* 不包括AP_EH_ROOT所占1K空间 */
static unsigned char *get_rdr_hisiap_dump_start_addr(void)
{
	unsigned char *addr;
	unsigned int timers = sizeof(AP_EH_ROOT) / SIZE_1K + 1;

	addr = g_rdr_ap_root->rdr_ap_area_map_addr +
	    ALIGN(sizeof(AP_EH_ROOT), timers * SIZE_1K);
	printk(KERN_INFO
	       "[%s], aligned by %dK, dump_start_addr [0x%p]\n",
	       __func__, timers, addr);
	if (check_addr_overflow(addr)) {
		printk(KERN_ERR
		       "[%s], there is no space left for ap to dump!\n",
		       __func__);
		return NULL;
	}
	return addr;
}

int io_resources_init(void)
{
	int i, ret;
	struct device_node *np = NULL;
	struct resource res;
	regs_info *regs = NULL;
	unsigned char *tmp = NULL;
	u32 data[4];

	regs = g_rdr_ap_root->dump_regs_info;
	memset((void *)regs, 0, REGS_DUMP_MAX_NUM * sizeof(regs_info));

	np = of_find_compatible_node(NULL, NULL,
				     "hisilicon,rdr_ap_adapter");
	if (!np) {
		printk(KERN_ERR
		       "[%s], cannot find rdr_ap_adapter node in dts!\n",
		       __func__);
		return -ENODEV;
	}

	ret = of_property_read_u32(np, "reg-dump-regions",
				   &g_rdr_ap_root->num_reg_regions);
	if (ret) {
		printk(KERN_ERR
		       "[%s], cannot find reg-dump-regions in dts!\n",
		       __func__);
		goto timer_ioinit;
	}

	if (0 == g_rdr_ap_root->num_reg_regions) {
		printk(KERN_ERR
		       "[%s], reg-dump-regions in zero, so no reg resource to init.\n",
		       __func__);
		goto timer_ioinit;
	}

	for (i = 0; i < g_rdr_ap_root->num_reg_regions; i++) {
		if (of_address_to_resource(np, i, &res)) {
			printk(KERN_ERR
			       "[%s], of_address_to_resource [%d] fail!\n",
			       __func__, i);
			ret = -ENODEV;
			goto timer_ioinit;
		}

		strncpy(regs[i].reg_name, res.name, REG_NAME_LEN - 1);
		regs[i].reg_name[REG_NAME_LEN - 1] = '\0';
		regs[i].reg_base = res.start;
		regs[i].reg_size = resource_size(&res);

		regs[i].reg_map_addr = of_iomap(np, i);
		printk(KERN_INFO
		       "[%s], regs_info[%d].reg_name[%s], reg_base[0x%p], reg_size[0x%x], map_addr[0x%p]\n",
		       __func__, i, regs[i].reg_name,
		       (void *)regs[i].reg_base, regs[i].reg_size,
		       regs[i].reg_map_addr);
		if (!regs[i].reg_map_addr) {
			printk(KERN_ERR
			       "[%s], unable to map [%s] registers\n",
			       __func__, (regs[i].reg_name));
			ret = -ENXIO;
			goto timer_ioinit;
		}

		if (0 == i) {
			regs[i].reg_dump_addr =
			    get_rdr_hisiap_dump_start_addr();
			if (IS_ERR_OR_NULL(regs[i].reg_dump_addr)) {
				printk(KERN_ERR
				       "[%s], reg_dump_addr is invalid!\n",
				       __func__);
				ret = -ENOSPC;
				goto timer_ioinit;
			}
		} else {
			regs[i].reg_dump_addr =
			    regs[i - 1].reg_dump_addr + regs[i - 1].reg_size;
		}

		printk(KERN_INFO "[%s], map [%s] registers ok\n",
		       __func__, (regs[i].reg_name));
	}

	tmp = regs[i - 1].reg_dump_addr + regs[i - 1].reg_size;
	if (check_addr_overflow(tmp)) {
		printk(KERN_ERR
		       "[%s], there is no space left for ap to dump regs!\n",
		       __func__);
		ret = -ENOSPC;
	}
timer_ioinit:

	/*io resource of 32k timer */
	ret = of_property_read_u32_array(np, "ldrx2dbg-abs-timer",
				       &data[0], 4);
	if (ret) {
		printk(KERN_ERR
		       "[%s], cannot find ldrx2dbg-abs-timer in dts!\n",
		       __func__);
		return ret;
	}

	sctrl_map_addr = ioremap(data[0], data[1]);
	if (NULL == sctrl_map_addr) {
		printk(KERN_ERR
		       "[%s], cannot find ldrx2dbg-abs-timer in dts!\n",
		       __func__);
		return -EFAULT;
	}
	g_32k_timer_l32bit_addr = sctrl_map_addr + data[2];
	g_32k_timer_h32bit_addr = sctrl_map_addr + data[3];

	return 0;
}

static unsigned int get_total_regdump_region_size(regs_info *regs_info)
{
	int i;
	u32 total = 0;
	if (!regs_info) {
		printk(KERN_ERR "[%s],\n", __func__);
		return 0;
	}

	for (i = 0; i < g_rdr_ap_root->num_reg_regions; i++) {
		total += regs_info[i].reg_size;
	}

	printk(KERN_INFO
	       "[%s], num_reg_regions [%u], regdump size [0x%x]\n",
	       __func__, g_rdr_ap_root->num_reg_regions, total);
	return total;
}

/*中断、任务、cpuidle根据cpu频繁度划分区域，以及其他不区分cpu的轨迹区域初始化*/
int __init hook_buffer_alloc(void)
{
	int ret;

	printk(KERN_INFO "[%s], irq_buffer_init start!\n", __func__);
	ret = irq_buffer_init(&g_rdr_ap_root->hook_percpu_buffer[HK_IRQ],
			    g_rdr_ap_root->hook_buffer_addr[HK_IRQ],
			    g_dump_buffer_size_tbl[HK_IRQ]);
	if (ret) {
		printk(KERN_ERR "[%s], irq_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	printk(KERN_INFO "[%s], task_buffer_init start!\n", __func__);
	ret = task_buffer_init(&g_rdr_ap_root->hook_percpu_buffer[HK_TASK],
			     g_rdr_ap_root->hook_buffer_addr[HK_TASK],
			     g_dump_buffer_size_tbl[HK_TASK]);
	if (ret) {
		printk(KERN_ERR "[%s], task_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	printk(KERN_INFO "[%s], cpuidle_buffer_init start!\n",
	       __func__);
	ret = cpuidle_buffer_init(&g_rdr_ap_root->hook_percpu_buffer[HK_CPUIDLE],
				g_rdr_ap_root->hook_buffer_addr[HK_CPUIDLE],
				g_dump_buffer_size_tbl[HK_CPUIDLE]);
	if (ret) {
		printk(KERN_ERR "[%s], cpuidle_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	printk(KERN_INFO "[%s], worker_buffer_init start!\n", __func__);
	ret = worker_buffer_init(&g_rdr_ap_root->hook_percpu_buffer[HK_WORKER],
			       g_rdr_ap_root->hook_buffer_addr[HK_WORKER],
			       g_dump_buffer_size_tbl[HK_WORKER]);
	if (ret) {
		printk(KERN_ERR "[%s], worker_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	printk(KERN_INFO "[%s], cpu_onoff_buffer_init start!\n",
	       __func__);
	ret = cpu_onoff_buffer_init(g_rdr_ap_root->hook_buffer_addr[HK_CPU_ONOFF],
				  g_dump_buffer_size_tbl[HK_CPU_ONOFF]);
	if (ret) {
		printk(KERN_ERR "[%s], cpu_onoff_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	printk(KERN_INFO "[%s], syscall_buffer_init start!\n",
	       __func__);
	ret = syscall_buffer_init(g_rdr_ap_root->hook_buffer_addr[HK_SYSCALL],
				g_dump_buffer_size_tbl[HK_SYSCALL]);
	if (ret) {
		printk(KERN_ERR "[%s], syscall_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	printk(KERN_INFO "[%s], hung_task_buffer_init start!\n",
	       __func__);
	ret = hung_task_buffer_init(g_rdr_ap_root->hook_buffer_addr[HK_HUNGTASK],
				  g_dump_buffer_size_tbl[HK_HUNGTASK]);
	if (ret) {
		printk(KERN_ERR "[%s], hung_task_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	printk(KERN_INFO "[%s], buddy_fail_buffer_init start!\n",
	       __func__);
	ret = buddy_fail_buffer_init(g_rdr_ap_root->hook_buffer_addr[HK_BUDDY_FAIL],
				   g_dump_buffer_size_tbl[HK_BUDDY_FAIL]);
	if (ret) {
		printk(KERN_ERR
		       "[%s], buddy_fail_buffer_init failed!\n",
		       __func__);
		return ret;
	}
	printk(KERN_INFO "[%s], tasklet_buffer_init start!\n",
	       __func__);
	ret = tasklet_buffer_init(g_rdr_ap_root->hook_buffer_addr[HK_TASKLET],
				g_dump_buffer_size_tbl[HK_TASKLET]);
	if (ret) {
		printk(KERN_ERR "[%s], tasklet_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	return 0;
}

void rdr_hisiap_print_all_dump_addrs(void)
{
	int i;
	if (IS_ERR_OR_NULL(g_rdr_ap_root)) {
		printk(KERN_ERR
		       "[%s], g_rdr_ap_root [0x%p] is invalid \n",
		       __func__, g_rdr_ap_root);
		return;
	}

	for (i = 0; i < g_rdr_ap_root->num_reg_regions; i++) {
		printk(KERN_INFO
		       "[%s], reg_name [%s], reg_dump_addr [0x%p] \n",
		       __func__,
		       g_rdr_ap_root->dump_regs_info[i].reg_name,
		       g_rdr_ap_root->dump_regs_info[i].reg_dump_addr);
	}

	printk(KERN_INFO "[%s], rdr_ap_area_map_addr [0x%p].\n",
	       __func__, g_rdr_ap_root->rdr_ap_area_map_addr);
	printk(KERN_INFO "[%s], kirq_switch_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_IRQ]);
	printk(KERN_INFO "[%s], ktask_switch_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_TASK]);
	printk(KERN_INFO "[%s], cpu_on_off_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_CPU_ONOFF]);
	printk(KERN_INFO "[%s], cpu_idle_stat_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_CPUIDLE]);
	printk(KERN_INFO "[%s], worker_trace_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_WORKER]);
	printk(KERN_INFO "[%s], syscall_trace_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_SYSCALL]);
	printk(KERN_INFO "[%s], hung_task_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_HUNGTASK]);
	printk(KERN_INFO "[%s], buddy_fail_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_BUDDY_FAIL]);
	printk(KERN_INFO "[%s], tasklet_trace_addr [0x%p].\n", __func__,
	       g_rdr_ap_root->hook_buffer_addr[HK_TASKLET]);

	for (i = 0; i < NR_CPUS; i++) {
		printk(KERN_INFO
		       "[%s], last_task_stack_dump_addr[%d] [0x%p].\n",
		       __func__, i,
		       g_rdr_ap_root->last_task_stack_dump_addr[i]);
	}
	for (i = 0; i < NR_CPUS; i++) {
		printk(KERN_INFO
		       "[%s], last_task_struct_dump_addr[%d] [0x%p].\n",
		       __func__, i,
		       g_rdr_ap_root->last_task_struct_dump_addr[i]);
	}

	for (i = 0; i < MODU_MAX; i++) {
		if (0 != g_rdr_ap_root->module_dump_info[i].dump_size) {
			printk(KERN_INFO
			       "[%s], module_dump_info[%d].dump_addr [0x%p].\n",
			       __func__, i,
			       g_rdr_ap_root->module_dump_info[i].
			       dump_addr);
		}
	}
}

void module_dump_mem_init(void)
{
	int i;
	for (i = 0; i < MODU_MAX; i++) {
		if (0 == i) {
			g_rdr_ap_root->module_dump_info[0].dump_addr =
			    g_rdr_ap_root->last_task_stack_dump_addr[NR_CPUS - 1] +
			    THREAD_SIZE;
		} else {
			g_rdr_ap_root->module_dump_info[i].dump_addr =
			    g_rdr_ap_root->module_dump_info[i - 1].dump_addr +
			    g_dump_modu_mem_size_tbl[i - 1];
		}

		if (check_addr_overflow
		    (g_rdr_ap_root->module_dump_info[i].dump_addr +
		     g_dump_modu_mem_size_tbl[i])) {
			printk(KERN_ERR
			       "[%s], there is no enough space for modu [%d] to dump mem!\n",
			       __func__, i);
			break;
		}
		g_rdr_ap_root->module_dump_info[i].dump_size =
		    g_dump_modu_mem_size_tbl[i];

		printk(KERN_INFO
		       "[%s], dump_addr [0x%p] dump_size [0x%x]!\n",
		       __func__,
		       g_rdr_ap_root->module_dump_info[i].dump_addr,
		       g_rdr_ap_root->module_dump_info[i].dump_size);
	}
}

static int __init ap_dump_buffer_init(void)
{
	int i;

	/* 轨迹记录区 */
	g_rdr_ap_root->hook_buffer_addr[0] =
	    get_rdr_hisiap_dump_start_addr()
	    + get_total_regdump_region_size(g_rdr_ap_root->dump_regs_info);
	for (i = 1; i < HK_MAX; i++) {
		g_rdr_ap_root->hook_buffer_addr[i] =
		    g_rdr_ap_root->hook_buffer_addr[i - 1] +
		    g_dump_buffer_size_tbl[i - 1];
	}

	/* 任务记录区 */
	g_rdr_ap_root->last_task_struct_dump_addr[0] =
	    g_rdr_ap_root->hook_buffer_addr[HK_MAX - 1]
	    + g_dump_buffer_size_tbl[HK_MAX - 1];
	for (i = 1; i < NR_CPUS; i++) {
		g_rdr_ap_root->last_task_struct_dump_addr[i] =
		    g_rdr_ap_root->last_task_struct_dump_addr[i - 1]
		    + sizeof(struct task_struct);
	}

	g_rdr_ap_root->last_task_stack_dump_addr[0] = (unsigned char *)
	    ALIGN(((unsigned long)g_rdr_ap_root->last_task_struct_dump_addr[NR_CPUS - 1] + sizeof(struct task_struct)), SIZE_1K);	/* 按1K对齐 */
	for (i = 1; i < NR_CPUS; i++) {
		g_rdr_ap_root->last_task_stack_dump_addr[i] =
		    g_rdr_ap_root->last_task_stack_dump_addr[i - 1] +
		    THREAD_SIZE;
	}

	if (check_addr_overflow(g_rdr_ap_root->last_task_stack_dump_addr[NR_CPUS - 1] +
	     THREAD_SIZE)) {
		printk(KERN_ERR
		       "[%s], there is no enough space for ap to dump!\n",
		       __func__);
		return -ENOSPC;
	}
	printk(KERN_INFO "[%s], module_dump_mem_init start.\n",
	       __func__);
	module_dump_mem_init();

	rdr_hisiap_print_all_dump_addrs();
	return hook_buffer_alloc();
}

u64 get_32k_abs_timer_value(void)
{
	u64 timer_count = 0;
	if (!g_32k_timer_l32bit_addr || !g_32k_timer_h32bit_addr) {
		return 0;
	}
	timer_count = *(volatile unsigned int *)g_32k_timer_l32bit_addr;
	timer_count |=
	    ((u64) (*(volatile unsigned int *)g_32k_timer_h32bit_addr)) << 32;
	return timer_count;
}

void rdr_set_wdt_kick_slice(void)
{
	static u32 kicktimes = 0;
	u64 kickslice = get_32k_abs_timer_value();

	if (g_rdr_ap_root != NULL) {
		g_rdr_ap_root->wdt_kick_slice[kicktimes % WDT_KICK_SLICE_TIMES] = kickslice;
		kicktimes++;
	}
}


void regs_dump(void)
{
	int i;
	regs_info *regs_info = NULL;

	regs_info = g_rdr_ap_root->dump_regs_info;

	/* NOTE:sctrl在上电区, pctrl, pericrg在外设区,A核访问不要做domain域判断 */
	for (i = 0; i < g_rdr_ap_root->num_reg_regions; i++) {
		if (IS_ERR_OR_NULL(regs_info[i].reg_map_addr)
		    || IS_ERR_OR_NULL(regs_info[i].reg_dump_addr)) {
			printk(KERN_ERR
			       "[%s], regs_info[%d].reg_map_addr [%p] reg_dump_addr [%p] invalid!\n",
			       __func__, i, regs_info[i].reg_map_addr,
			       regs_info[i].reg_dump_addr);
			continue;
		}
		printk(KERN_INFO
		       "[%s], memcpy [0x%x] size from regs_info[%d].reg_map_addr [%p] to reg_dump_addr [%p].\n",
		       __func__, regs_info[i].reg_size, i,
		       regs_info[i].reg_map_addr,
		       regs_info[i].reg_dump_addr);

		memcpy(regs_info[i].reg_dump_addr,
		       regs_info[i].reg_map_addr,
		       regs_info[i].reg_size);
	}
}

void last_task_stack_dump(void)
{
	int i;
	unsigned char *dst = NULL;
	for (i = 0; i < NR_CPUS; i++) {
		dst = g_rdr_ap_root->last_task_struct_dump_addr[i];
		if (IS_ERR_OR_NULL(dst)
		    || IS_ERR_OR_NULL(g_last_task_ptr[i])) {
			printk(KERN_ERR
			       "[%s], last_task_struct_dump_addr[%d] [0x%p] is invalid!\n",
			       __func__, i, dst);
			continue;
		}
		if (!kern_addr_valid((unsigned long)g_last_task_ptr[i])) {
			printk(KERN_ERR
			       "[%s], g_last_task_ptr[%d] [0x%p] is invalid!\n",
			       __func__, i, g_last_task_ptr[i]);
			continue;
		}
		memcpy((void *)dst, (void *)g_last_task_ptr[i],
		       sizeof(struct task_struct));

		dst = g_rdr_ap_root->last_task_stack_dump_addr[i];
		if (IS_ERR_OR_NULL(dst)
		    || IS_ERR_OR_NULL(g_last_task_ptr[i]->stack)) {
			printk(KERN_ERR
			       "[%s], last_task_stack_dump_addr[%d] [0x%p] is invalid!\n",
			       __func__, i, dst);
			continue;
		}
		if (!kern_addr_valid
		    ((unsigned long)g_last_task_ptr[i]->stack)) {
			printk(KERN_ERR
			       "[%s], g_last_task_ptr[%d] stack [0x%p] is invalid!\n",
			       __func__, i, g_last_task_ptr[i]->stack);
			continue;
		}
		memcpy((void *)dst, (void *)g_last_task_ptr[i]->stack,
		       THREAD_SIZE);
	}
}
static int hisi_trace_hook_install(void)
{
	int ret = 0;
	hook_type hk;

	for (hk = HK_IRQ; hk < HK_MAX; hk++) {
		ret = hisi_ap_hook_install(hk);
		if (ret) {
			printk(KERN_ERR
			       "[%s], hook_type [%d] install failed!\n",
			       __func__, hk);
			return ret;
		}
	}
	return ret;
}

static void hisi_trace_hook_uninstall(void)
{
	hook_type hk;
	for (hk = HK_IRQ; hk < HK_MAX; hk++) {
		hisi_ap_hook_uninstall(hk);
	}
}

static void get_product_version_work_fn(struct work_struct *work)
{
	printk(KERN_ERR "[%s], enter!\n", __func__);
	if (!g_rdr_ap_root) {
		printk(KERN_ERR "[%s], g_rdr_ap_root is NULL!\n",
		       __func__);
		return;
	}

	get_product_version(g_rdr_ap_root->version,
			    PRODUCT_VERSION_LEN);
	printk(KERN_ERR "[%s], exit!\n", __func__);
}

/*******************************************************************************
Function:       register_module_dump_mem_func
Description:    向AP维测模块及IP提供的内存dump注册接口；
Input:          func:注册的dump函数, module_name:模块名, modu:模块ID，此为统一分配;
Output:         NA
Return:         0:注册成功，<0:失败
********************************************************************************/
int register_module_dump_mem_func(rdr_hisiap_dump_func_ptr func,
				  char *module_name,
				  dump_mem_module modu)
{
	int ret = -1;

	if (modu >= MODU_MAX) {
		printk(KERN_ERR "[%s], modu [%d] is invalid!\n",
		       __func__, modu);
		return -EINVAL;
	}

	if (IS_ERR_OR_NULL(func)) {
		printk(KERN_ERR "[%s], func [0x%p] is invalid!\n",
		       __func__, func);
		return -EINVAL;
	}

	if (IS_ERR_OR_NULL(module_name)) {
		printk(KERN_ERR "[%s], module_name is invalid!\n",
		       __func__);
		return -EINVAL;
	}

	if (NULL == g_rdr_ap_root) {
		printk(KERN_ERR "[%s], g_rdr_ap_root is null!\n",
		       __func__);
		return -1;
	}

	printk(KERN_ERR "[%s], module_name [%s]\n", __func__,
	       module_name);
	mutex_lock(&dump_mem_mutex);
	if (0 != g_rdr_ap_root->module_dump_info[modu].dump_size) {
		g_rdr_ap_root->module_dump_info[modu].dump_funcptr = func;
		strncpy(g_rdr_ap_root->module_dump_info[modu].module_name,
			module_name, AMNTN_MODULE_NAME_LEN - 1);
		g_rdr_ap_root->module_dump_info[modu].module_name[AMNTN_MODULE_NAME_LEN - 1] = '\0';
		ret = 0;
	}
	mutex_unlock(&dump_mem_mutex);

	if (ret) {
		printk(KERN_ERR
		       "[%s], func[0x%p], size[%d], [%s] register failed!\n",
		       __func__, func,
		       g_rdr_ap_root->module_dump_info[modu].dump_size,
		       module_name);
	}
	return ret;
}

/*******************************************************************************
Function:       save_module_dump_mem
Description:    异常复位前，调用AP维测模块及IP提供的内存dump注册函数；
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
void save_module_dump_mem(void)
{
	int i;
	void *addr = NULL;
	unsigned int size = 0;

	printk(KERN_ERR "[%s], enter.\n", __func__);
	for (i = 0; i < MODU_MAX; i++) {
		if (NULL != g_rdr_ap_root->module_dump_info[i].dump_funcptr) {
			addr = (void *)g_rdr_ap_root->module_dump_info[i].dump_addr;
			size = g_rdr_ap_root->module_dump_info[i].dump_size;
			if (!g_rdr_ap_root->module_dump_info[i].dump_funcptr(addr, size)) {
				printk(KERN_ERR
				       "[%s], [%s] dump failed!\n",
				       __func__,
				       g_rdr_ap_root->module_dump_info[i].module_name);
				continue;
			}
		}
	}
	printk(KERN_ERR "[%s], exit.\n", __func__);
}

/*****************************************************
Description:   get device id. ex: hi3650, hi6250...
*****************************************************/
static void get_device_platform(unsigned char* device_platform, size_t count)
{
	memset(device_platform, '\0', count);

	if (of_machine_is_compatible("hisilicon,hi3650")) {
		strncpy(device_platform, "hi3650", count);
	} else if (of_machine_is_compatible("hisilicon,hi6250")) {
		strncpy(device_platform, "hi6250", count);
	}else if (of_machine_is_compatible("hisilicon,hi3660")) {
		strncpy(device_platform, "hi3660", count);
	} else {
		strncpy(device_platform, "unknown", count);
		printk(KERN_ERR "unrecognizable device_id? new or old product.\n");
	}
	device_platform[count - 1] = '\0';
}

int __init rdr_hisiap_dump_init(struct rdr_register_module_result *retinfo)
{
	int ret = 0;

	printk(KERN_ERR "[%s], begin.\n", __func__);

	g_rdr_ap_root = (AP_EH_ROOT *) g_hisiap_addr;
	strncpy(g_log_path, g_rdr_ap_root->log_path, LOG_PATH_LEN - 1);
	g_log_path[LOG_PATH_LEN - 1] = '\0';

	/* 由于pmu扣板还没有，暂时用ap异常区的后8个字节替代 */
	memset((void *)g_hisiap_addr, 0,
	       retinfo->log_len - PMU_RESET_RECORD_DDR_AREA_SIZE);
	g_rdr_ap_root = (AP_EH_ROOT *) g_hisiap_addr;
	g_rdr_ap_root->ap_rdr_info.log_addr = retinfo->log_addr;
	g_rdr_ap_root->ap_rdr_info.log_len = retinfo->log_len;
	g_rdr_ap_root->ap_rdr_info.nve = retinfo->nve;
	g_rdr_ap_root->rdr_ap_area_map_addr = (void *)g_hisiap_addr;
	get_device_platform(g_rdr_ap_root->device_id, PRODUCT_DEVICE_LEN);
	g_rdr_ap_root->bbox_version = BBOX_VERSION;
	g_rdr_ap_root->dump_magic = AP_DUMP_MAGIC;
	g_rdr_ap_root->end_magic = AP_DUMP_END_MAGIC;

	printk(KERN_ERR "[%s], io_resources_init start.\n", __func__);
	ret = io_resources_init();
	if (ret) {
		printk(KERN_ERR "[%s], io_resources_init failed!\n",
		       __func__);
		return ret;
	}

	printk(KERN_ERR "[%s], ap_dump_buffer_init start.\n", __func__);
	ret = ap_dump_buffer_init();
	if (ret) {
		printk(KERN_ERR "[%s], ap_dump_buffer_init failed!\n",
		       __func__);
		return ret;
	}

	mutex_init(&dump_mem_mutex);

	printk(KERN_ERR "[%s], register_arch_timer_func_ptr start.\n",
	       __func__);
	ret = register_arch_timer_func_ptr(get_32k_abs_timer_value);
	if (ret) {
		printk(KERN_ERR
		       "[%s], register_arch_timer_func_ptr failed!\n",
		       __func__);
		return ret;
	}

	if (check_himntn(HIMNTN_KERNEL_DUMP_ENABLE)) {	/* 轨迹是否生成保持和kernel dump一致 */
		printk(KERN_ERR
		       "[%s], hisi_trace_hook_install start.\n",
		       __func__);
		ret = hisi_trace_hook_install();
		if (ret) {
			printk(KERN_ERR
			       "[%s], hisi_trace_hook_install failed!\n",
			       __func__);
			return ret;
		}
	}

	schedule_delayed_work(&get_product_version_work, 0);

	printk(KERN_ERR "[%s], end.\n", __func__);
	return ret;
}

static void save_bl31_exc_memory(void)
{
	int iret = 0;
	int len = 0;
	static mm_segment_t oldfs;
	char fullpath_arr[LOG_PATH_LEN] = "";
	char dst_str[LOG_PATH_LEN] = "";
	memset(fullpath_arr, 0, LOG_PATH_LEN);
	strncat(fullpath_arr, g_log_path,
		(LOG_PATH_LEN - 1 - strlen(fullpath_arr)));
	strncat(fullpath_arr, "/ap_log/",
		(LOG_PATH_LEN - 1 - strlen(fullpath_arr)));
	printk(KERN_ERR "%s: %s\n", __func__, fullpath_arr);

	oldfs = get_fs();
	set_fs(KERNEL_DS);
	iret = mntn_filesys_create_dir(fullpath_arr, DIR_LIMIT);
	if (0 != iret) {
		printk(KERN_ERR "%s: iret is [%d]\n", __func__, iret);
		set_fs(oldfs);
		return;
	}
	len = strlen(fullpath_arr);
	memcpy(dst_str, fullpath_arr, len + 1);
	strncat(&dst_str[len], "/bl31_mntn_memory.bin",
		(LOG_PATH_LEN - 1 - len));
	iret = rdr_copy_file_apend(dst_str, SRC_BL31_MNTN_MEMORY);
	if (iret) {
		printk(KERN_ERR
		       "[%s], save bl31_mntn_memory.bin error, ret = %d\n",
		       __func__, iret);
	}
	set_fs(oldfs);
	return;
}

#ifdef CONFIG_HISI_CORESIGHT_TRACE
static void save_etr_dump(void)
{
	int iret = 0;
	int len = 0;
	static mm_segment_t oldfs;
	char fullpath_arr[LOG_PATH_LEN] = "";
	char dst_str[LOG_PATH_LEN] = "";
	memset(fullpath_arr, 0, LOG_PATH_LEN);
	strncat(fullpath_arr, g_log_path,
		(LOG_PATH_LEN - 1 - strlen(fullpath_arr)));
	strncat(fullpath_arr, "ap_log/",
		(LOG_PATH_LEN - 1 - strlen(fullpath_arr)));
	printk(KERN_ERR "%s: %s\n", __func__, fullpath_arr);

	oldfs = get_fs();
	set_fs(KERNEL_DS);
	iret = mntn_filesys_create_dir(fullpath_arr, 0770);
	if (0 != iret) {
		printk(KERN_ERR "%s: iret is [%d]\n", __func__,
		       iret);
		set_fs(oldfs);
		return;
	}
	len = strlen(fullpath_arr);
	memcpy(dst_str, fullpath_arr, len + 1);
	strncat(&dst_str[len], ETR_DUMP_NAME, (LOG_PATH_LEN - 1 - len));
	iret =
	    rdr_copy_file_apend(dst_str,
				"/proc/balong/memory/etr_dump");
	if (iret) {
		printk(KERN_ERR
		       "[%s], save etr_dump.bin error, ret = %d\n",
		       __func__, iret);
	}
	set_fs(oldfs);
	return;
}
#endif
static void save_lpmcu_exc_memory(void)
{
	int iret = 0;
	int len = 0;
	static mm_segment_t oldfs;
	char fullpath_arr[LOG_PATH_LEN] = "";
	char dst_str[LOG_PATH_LEN] = "";
	memset(fullpath_arr, 0, LOG_PATH_LEN);
	strncat(fullpath_arr, g_log_path, strlen(g_log_path));
	strncat(fullpath_arr, "/lpmcu_log/", strlen("/lpmcu_log/"));
	printk(KERN_ERR "%s: %s\n", __func__, fullpath_arr);

	oldfs = get_fs();
	set_fs(KERNEL_DS);
	iret = mntn_filesys_create_dir(fullpath_arr, DIR_LIMIT);
	if (0 != iret) {
		printk(KERN_ERR "%s: iret is [%d]\n", __func__, iret);
		set_fs(oldfs);
		return;
	}
	len = strlen(fullpath_arr);
	memcpy(dst_str, fullpath_arr, len + 1);
	memcpy(&dst_str[len], "/lpmcu_ddr_memory.bin",
	       strlen("/lpmcu_ddr_memory.bin") + 1);
	iret = rdr_copy_file_apend(dst_str, SRC_LPMCU_DDR_MEMORY);
	if (iret) {
		printk(KERN_ERR
		       "[%s], save lpmcu_ddr_memory.bin error, ret = %d\n",
		       __func__, iret);
	}
	set_fs(oldfs);
	return;
}

int save_kernel_dump(void *arg)
{
	int fd;
	int ret;
	int len;
	long long cnt;
	char buf[SZ_4K / 4];
	char date[DATATIME_MAXLEN];
	static mm_segment_t oldfs;
	char dst_str[LOG_PATH_LEN] = "";
	char exce_dir[LOG_PATH_LEN] = "";

	snprintf(exce_dir, LOG_PATH_LEN, "%s%s/", PATH_ROOT,
		 PATH_MEMDUMP);

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;
	mntn_rm_old_log(exce_dir, 1);
	memset(dst_str, 0, LOG_PATH_LEN);
	memset(date, 0, DATATIME_MAXLEN);

	printk("exce_dir is [%s]\n", exce_dir);

	/* 如果arg为真，表示是起线程保存kerneldump，此时要从内存中获取异常时间戳 */
	if (arg && (LOG_PATH_LEN - 1 >= strlen(g_log_path))) {
		len = strlen(g_log_path);
		memcpy(date, &g_log_path[len - DATATIME_MAXLEN],
		       DATATIME_MAXLEN - 1);
	} else {
		/* 如果arg为空，则认为是ap侧的异常，是复位之后保存的log，则获取当前时间即可 */
		snprintf(date, DATATIME_MAXLEN, "%s-%08lld",
			 rdr_get_timestamp(), rdr_get_tick());
	}

	fd = sys_open(exce_dir, O_DIRECTORY, 0);

	/* if dir is not exist,then create new dir */
	if (fd < 0) {
		printk(KERN_ERR "%s %d\n", __func__, fd);
		fd = sys_mkdir(exce_dir, DIR_LIMIT);
		if (fd < 0) {
			printk(KERN_ERR "%s %d\n", __func__, fd);
			return fd;
		}
	} else {
		sys_close(fd);
	}
	strncat(exce_dir, "/", strlen("/"));
	strncat(exce_dir, date, strlen(date));
	fd = sys_mkdir(exce_dir, DIR_LIMIT);
	if (fd < 0) {
		printk(KERN_ERR "%s %d\n", __func__, fd);
		return fd;
	}

	len = strlen(exce_dir);
	memcpy(dst_str, exce_dir, len + 1);
	memcpy(&dst_str[len], "/kerneldump_",
	       strlen("/kerneldump_") + 1);

	strncat(dst_str, date, strlen(date));
	printk("dst_str is [%s]\n", dst_str);

	if (check_himntn(HIMNTN_KERNEL_DUMP_ENABLE)) {
		ret = rdr_copy_file_apend(dst_str, SRC_KERNELDUMP);
		if (ret) {
			printk(KERN_ERR
			       "[%s], save kerneldump error, ret = %d\n",
			       __func__, ret);
			set_fs(oldfs);
			return -1;
		}
	}

	/* After cpoying kerneldump to filesystem, need to free memory.
	 * So we just  need to read SRC_DUMPEND.
	 */
	fd = sys_open(SRC_DUMPEND, O_RDONLY, FILE_LIMIT);
	if (fd < 0) {
		pr_err("[%s]: open %s failed, return [%d]\n", __func__,
		       SRC_DUMPEND, fd);
		set_fs(oldfs);
		return -1;
	}
	while (1) {
		cnt = sys_read(fd, buf, SZ_4K / 4);
		if (cnt == 0)
			break;
		if (cnt < 0) {
			pr_err("[%s]: read %s failed, return [%lld]\n",
			       __func__, SRC_DUMPEND, cnt);
			sys_close(fd);
			set_fs(oldfs);
			return -1;
		}
	}

	sys_close(fd);
	set_fs(oldfs);
	return 0;
}

void rdr_hisiap_dump(u32 modid, u32 etype, u64 coreid, char *log_path,
		     pfn_cb_dump_done pfn_cb)
{
	unsigned long exception_info = 0;
	unsigned long exception_info_len = 0;
	int ret = 0, path_root_len = 0;
	struct rdr_exception_info_s temp = {
		{0, 0}, 0x80000001, 0x80000001, RDR_ERR, RDR_REBOOT_NOW,
		    RDR_AP, RDR_AP, RDR_AP,
		RDR_REENTRANT_DISALLOW, COLDBOOT, RDR_UPLOAD_YES, "ap",
		    "ap", 0, (void *)0, 0
	};
	temp.e_from_core = RDR_AP;
	temp.e_exce_type = rdr_get_reboot_type();

	if (temp.e_exce_type == LPM3_S_EXCEPTION) {
		temp.e_from_core = RDR_LPM3;
	}

	if (temp.e_exce_type == MMC_S_EXCEPTION) {
		temp.e_from_core = RDR_EMMC;
	}
	if (modid == RDR_MODID_AP_ABNORMAL_REBOOT
	    || modid == BBOX_MODID_LAST_SAVE_NOT_DONE) {
		printk("RDR_MODID_AP_ABNORMAL_REBOOT\n");
		if (log_path && check_himntn(HIMNTN_GOBAL_RESETLOG)) {
			strncpy(g_log_path, log_path, LOG_PATH_LEN - 1);
			g_log_path[LOG_PATH_LEN - 1] = '\0';

			if (check_himntn(HIMNTN_LINUX_DUMP_MEM)
			    && (LPM3_S_EXCEPTION == temp.e_exce_type
			    || LPM3_S_LPMCURST == temp.e_exce_type
			    || (REBOOT_REASON_LABEL1 < temp.e_exce_type
			    && REBOOT_REASON_LABEL3 > temp.e_exce_type))) {
				save_lpmcu_exc_memory();
			}

			if ((REBOOT_REASON_LABEL1 < temp.e_exce_type)
			    && (REBOOT_REASON_LABEL3 > temp.e_exce_type)
			    && check_himntn(HIMNTN_LINUX_DUMP_MEM)) {
				save_bl31_exc_memory();
				ret = save_kernel_dump(NULL);
				if (ret) {
					printk(KERN_ERR
					       "save_kernel_dump fail, ret = [%d]\n",
					       ret);
				}
			}
#ifdef CONFIG_HISI_CORESIGHT_TRACE
			save_etr_dump();
#endif
			save_exception_info(NULL);

			path_root_len = strlen(PATH_ROOT);
			/* 如果是走简易流程复位的异常，则history.log中正常记录 */
			if (modid == RDR_MODID_AP_ABNORMAL_REBOOT) {
				rdr_save_history_log(&temp,
						     &log_path[path_root_len],
						     true);
			} else if (modid == BBOX_MODID_LAST_SAVE_NOT_DONE) {
				rdr_save_history_log(&temp, &log_path[path_root_len], false);	/* 记录时，增加last_save_not_done字符串 */
			}
		}
		printk(KERN_INFO
		       "%s: create save_exception_info, return \n",
		       __func__);

		/* 文件系统sync，保证读写任务完成 */
		if (!in_atomic() && !irqs_disabled() && !in_irq()) {
			sys_sync();
		}

		/* 在异常目录下面新建DONE文件，标志此次异常log保存完毕 */
		bbox_save_done(g_log_path, BBOX_SAVE_STEP_DONE);
		if (pfn_cb) {
			pfn_cb(modid, coreid);
		}
		return;
	}

	console_loglevel = 7;

	/* 如果是panic，则需要将pc指针记录下来，并传递到fastboot  */
	if (etype == AP_S_PANIC) {
		get_exception_info(&exception_info,
				   &exception_info_len);
		memset(g_bbox_ap_record_pc->exception_info, 0,
		       RECORD_PC_STR_MAX_LENGTH);
		memcpy(g_bbox_ap_record_pc->exception_info,
		       (char *)exception_info, exception_info_len);
		printk(KERN_ERR "exception_info is [%s],len is [%ld]\n",
		       (char *)exception_info, exception_info_len);
		g_bbox_ap_record_pc->exception_info_len = exception_info_len;
	}

	printk("rdr_hisiap_dump modid[%x],etype[%x],coreid[%llx], log_path[%s]\n",
	     modid, etype, coreid, log_path);
	printk(KERN_ERR "[%s], hisi_trace_hook_uninstall start!\n",
	       __func__);
	hisi_trace_hook_uninstall();

	g_rdr_ap_root->modid = modid;
	g_rdr_ap_root->e_exce_type = etype;
	g_rdr_ap_root->coreid = coreid;
	printk("rdr_hisiap_dump log_path_ptr [%p]\n",
	       g_rdr_ap_root->log_path);
	if (log_path) {
		strncpy(g_rdr_ap_root->log_path, log_path,
			LOG_PATH_LEN - 1);
		g_rdr_ap_root->log_path[LOG_PATH_LEN - 1] = '\0';
	}

	g_rdr_ap_root->slice = get_32k_abs_timer_value();

	printk(KERN_ERR "[%s], regs_dump start!\n", __func__);
	regs_dump();

	printk(KERN_ERR "[%s], last_task_stack_dump start!\n",
	       __func__);
	last_task_stack_dump();

	g_rdr_ap_root->enter_times++;

	printk(KERN_ERR "[%s], save_module_dump_mem start!\n",
	       __func__);
	save_module_dump_mem();

	print_debug_info();
	printk(KERN_ERR "[%s], exit!\n", __func__);
	if (pfn_cb) {
		pfn_cb(modid, coreid);
	}
}

/*****************************************************************************
Description : 初始化复位原因
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void hisiap_nmi_notify_lpm3(void)
{
	unsigned int value;
	u64 addr = 0;

	addr = g_mi_notify_lpm3_addr;
	if (!addr) {
		printk(KERN_ERR "[%s]", __func__);
		return;
	}
	value = readl((char *)addr);
	value |= (0x1 << 2);
	writel(value, (char *)addr);
	value &= ~(0x1 << 2);
	writel(value, (char *)addr);

	return;
}

void get_bbox_curtime_slice(void)
{
	u64 curtime, curslice;
	curtime = hisi_getcurtime();
	curslice = get_32k_abs_timer_value();
	printk(KERN_ERR
	       "printk_time is %llu, 32k_abs_timer_value is %llu.\n",
	       curtime, curslice);
}
/*****************************************************************************
Description : 异常时，ap的reset函数
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void rdr_hisiap_reset(u32 modid, u32 etype, u64 coreid)
{
	printk("%s start\n", __func__);
	get_bbox_curtime_slice();
	if (!in_atomic() && !irqs_disabled() && !in_irq()) {
		sys_sync();
	}
	if (AP_S_PANIC != etype) {
		printk(KERN_ERR "etype is not panic\n");
		dump_stack();
		preempt_disable();
		smp_send_stop();
	}

	kmsg_dump(KMSG_DUMP_PANIC);
	flush_cache_all();

	hisiap_nmi_notify_lpm3();
	printk("%s end\n", __func__);

	while (1)
		;
}

int get_pmu_reset_base_addr(void)
{
	u64 pmu_reset_reg_addr;
	unsigned int fpga_flag = 0;

	struct device_node *np = NULL;
	int ret;
	np = of_find_compatible_node(NULL, NULL, "hisilicon,hisifb");
	if (!np) {
		printk("NOT FOUND device node 'hisilicon,hisifb'!\n");
		return -ENXIO;
	}
	ret = of_property_read_u32(np, "fpga_flag", &fpga_flag);
	if (ret) {
		printk("failed to get fpga_flag resource.\n");
		return -ENXIO;
	}
	if (fpga_flag == 1) {
		g_bbox_fpga_flag = 1;
		pmu_reset_reg_addr = FPGA_RESET_REG_ADDR;
	} else {
		g_bbox_fpga_flag = 0;
		pmu_reset_reg_addr = PMU_RESET_REG_ADDR;
	}

	printk("pmu reset reg phy is 0x%llx\n", pmu_reset_reg_addr);
	if (fpga_flag == 1)
		g_pmu_reset_reg = (unsigned long long)
		    hisi_bbox_map(pmu_reset_reg_addr, 0x4);
	else
		g_pmu_reset_reg =
		    (unsigned long long)ioremap(pmu_reset_reg_addr,
						0x4);
	if (!g_pmu_reset_reg) {
		printk(KERN_ERR "get pmu reset reg error\n");
		return -1;
	}
	printk("pmu reset reg is %llx\n", g_pmu_reset_reg);
	return 0;
}

/*****************************************************************************
Description : 获取记录复位原因的pmu寄存器的地址
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
unsigned long long get_pmu_reset_reg(void)
{
	return g_pmu_reset_reg;
}

/*****************************************************************************
Description : 供rdr使用，将异常记录到pmu中
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void record_exce_type(struct rdr_exception_info_s *einfo)
{
	struct rdr_exception_info_s *e = NULL;
	unsigned long long pmu_reset_reg = 0;
	unsigned int value = 0;
	if (!einfo) {
		printk(KERN_ERR "einfo is null\n");
		return;
	}

	e = einfo;
	pmu_reset_reg = get_pmu_reset_reg();
	if (pmu_reset_reg) {
		value = readl((char *)pmu_reset_reg);
		value &= (PMU_RESET_REG_MASK);
		e->e_exce_type &= (RST_FLAG_MASK);
		value |= e->e_exce_type;
		printk("record_exce_type pmu_reset_reg is %d\n", value);
		writel(value, (char *)pmu_reset_reg);
	}
	return;
}
/*****************************************************************************
Description : 注册异常的参数，在dump和reset之间调用
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
void hisiap_callback(u32 argc, void *argv)
{
	int ret;

	if (check_himntn(HIMNTN_GOBAL_RESETLOG)) {
		ret = hisi_trace_hook_install();

		if (ret) {
			printk("[%s]\n", __func__);
		}
	}
	return;
}

/*****************************************************************************
Description : 向rdr注册异常
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static void rdr_hisiap_register_exception(void)
{
	int i;
	u32 ret;
	for (i = 0;
	     i < sizeof(einfo) / sizeof(struct rdr_exception_info_s);
	     i++) {
		printk("register exception:%d", einfo[i].e_exce_type);
		einfo[i].e_callback = hisiap_callback;
		if (0 == i) {
			/* 注册AP core公共callback函数，其他core有通知ap core dump，则调用此callback函数，
			   RDR_COMMON_CALLBACK为公共callback标记，没有标记的为ap core私有callback函数 */
			einfo[i].e_callback = (rdr_e_callback) (
				(u64)(einfo[i].e_callback) | BBOX_COMMON_CALLBACK);
		}
		ret = rdr_register_exception(&einfo[i]);
		if (ret == 0) {
			printk(KERN_ERR
			       "rdr_register_exception fail, ret = [%d]\n",
			       ret);
		}
	}
	printk("[%s], end\n", __func__);
}

/*****************************************************************************
Description : 向rdr注册dump和reset函数
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static int rdr_hisiap_register_core(void)
{
	struct rdr_module_ops_pub s_soc_ops;
	struct rdr_register_module_result retinfo;
	int ret = 0;
	u64 coreid = RDR_AP;

	s_soc_ops.ops_dump = rdr_hisiap_dump;
	s_soc_ops.ops_reset = rdr_hisiap_reset;

	ret = rdr_register_module_ops(coreid, &s_soc_ops, &retinfo);
	if (ret < 0) {
		printk(KERN_ERR
		       "rdr_register_module_ops fail, ret = [%d]\n",
		       ret);
		return ret;
	}

	current_info.log_addr = retinfo.log_addr;
	current_info.log_len = retinfo.log_len;
	current_info.nve = retinfo.nve;

	return ret;
}

/*****************************************************************************
Description : 获取初始化状态
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
bool rdr_get_ap_init_done(void)
{
	return rdr_ap_init == 1;
}

/*****************************************************************************
Description : 将一个文件的内容copy到另一个文件中
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static int rdr_copy_file_apend(char *dst, char *src)
{
	long fddst, fdsrc;
	char buf[SZ_4K / 4];
	static mm_segment_t oldfs;
	long cnt;
	int ret = 0;

	if (NULL == dst || NULL == src) {
		pr_err("rdr:%s():dst(0x%p) or src(0x%p) is NULL.\n",
		       __func__, dst, src);
		return -1;
	}

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	fdsrc = sys_open(src, O_RDONLY, FILE_LIMIT);
	if (fdsrc < 0) {
		pr_err("rdr:%s():open %s failed, return [%ld]\n",
		       __func__, src, fdsrc);
		ret = -1;
		goto out;
	}
	fddst =
	    sys_open(dst, O_CREAT | O_WRONLY | O_APPEND, FILE_LIMIT);
	if (fddst < 0) {
		pr_err("rdr:%s():open %s failed, return [%ld]\n",
		       __func__, dst, fddst);
		sys_close(fdsrc);
		ret = -1;
		goto out;
	}

	while (1) {
		cnt = sys_read(fdsrc, buf, SZ_4K / 4);
		if (cnt == 0)
			break;
		if (cnt < 0) {
			pr_err
			    ("rdr:%s():read %s failed, return [%ld]\n",
			     __func__, src, cnt);
			ret = -1;
			goto close;
		}

		cnt = sys_write(fddst, buf, SZ_4K / 4);
		if (cnt <= 0) {
			pr_err
			    ("rdr:%s():write %s failed, return [%ld]\n",
			     __func__, dst, cnt);
			ret = -1;
			goto close;
		}
	}

close:
	sys_close(fdsrc);
	sys_close(fddst);
out:
	set_fs(oldfs);
	return ret;
}

/*******************************************************************************
Function:       save_exception_info
Description:    保存异常信息
Input:          void *arg暂不使用
Output:         NA
Return:         -1 : error, 0 : ok
********************************************************************************/
int save_exception_info(void *arg)
{
	int fd, ret, len, i, tmp_cnt;
	u32 reboot_type = 0;
	static mm_segment_t oldfs;
	char date[DATATIME_MAXLEN];
	char dst_str[NEXT_LOG_PATH_LEN];
	char exce_dir[LOG_PATH_LEN];
	char dst_dir_str[DEST_LOG_PATH_LEN];
	char default_dir[LOG_PATH_LEN];
	char fullpath_arr[LOG_PATH_LEN];
	char fastbootlog_path[NEXT_LOG_PATH_LEN];
	char last_fastbootlog_path[NEXT_LOG_PATH_LEN];
	char *pbuff = NULL;

	ret = 0;
	tmp_cnt =
	    MNTN_FILESYS_MAX_CYCLE * MNTN_FILESYS_PURE_DIR_NAME_LEN;

	printk("[%s], start\n", __func__);

	/* 等待直到data分区可用，才向后运行 */
	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;

	/* 从全局变量中获取此次异常的log目录路径 */
	memset(exce_dir, 0, LOG_PATH_LEN);
	if (LOG_PATH_LEN - 1 < strlen(g_log_path)) {
		printk(KERN_ERR "g_log_path's len too large\n");
		return -1;
	}
	memcpy(exce_dir, g_log_path, strlen(g_log_path) + 1);
	printk("exce_dir is [%s]\n", exce_dir);

	/* 申请一块内存用于存储遍历/sys/fs/pstore/目录下所有文件的名字 */
	pbuff = kmalloc(tmp_cnt, GFP_KERNEL);
	if (NULL == pbuff) {
		printk(KERN_ERR
		       "kmalloc tmp_cnt fail, tmp_cnt = [%d]\n",
		       tmp_cnt);
		return -1;
	}
	/* 清空申请的buff */
	memset((void *)pbuff, 0, tmp_cnt);

	rdr_wait_partition(PSTORE_PATH, 60);
	/* 调用接口将/sys/fs/pstore/目录下的所有文件名字存入pbuff中 */
	tmp_cnt =
	    mntn_filesys_dir_list(PSTORE_PATH, pbuff, tmp_cnt, DT_REG);

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	/* 打开异常目录，如果不存在则以当前时间为目录创建 */
	fd = sys_open(exce_dir, O_DIRECTORY, 0);
	if (fd < 0) {
		printk(KERN_ERR
		       "sys_open exce_dir[%s] fail,fd = [%d]\n",
		       exce_dir, fd);
		memset(date, 0, DATATIME_MAXLEN);
		memset(default_dir, 0, LOG_PATH_LEN);
		snprintf(date, DATATIME_MAXLEN, "%s-%08lld",
			 rdr_get_timestamp(), rdr_get_tick());
		snprintf(default_dir, LOG_PATH_LEN, "%s%s", PATH_ROOT,
			 date);
		printk("default_dir is [%s]\n", default_dir);
		fd = sys_mkdir(default_dir, DIR_LIMIT);
		if (fd < 0) {
			printk(KERN_ERR
			       "sys_mkdir default_dir[%s] fail, fd = [%d]\n",
			       default_dir, fd);
			ret = -1;
			goto out;
		}
		memset(dst_dir_str, 0, DEST_LOG_PATH_LEN);
		len = strlen(default_dir);
		memcpy(dst_dir_str, default_dir, len + 1);
		memcpy(&dst_dir_str[len], "/ap_log",
		       strlen("/ap_log") + 1);
	} else {
		sys_close(fd);
		memset(dst_dir_str, 0, DEST_LOG_PATH_LEN);
		len = strlen(exce_dir);
		memcpy(dst_dir_str, exce_dir, len + 1);
		memcpy(&dst_dir_str[len], "/ap_log",
		       strlen("/ap_log") + 1);
	}

	/* 打开异常目录下的ap_log目录，如果不存在则创建 */
	fd = sys_open(dst_dir_str, O_DIRECTORY, 0);
	if (fd < 0) {
		fd = sys_mkdir(dst_dir_str, DIR_LIMIT);
		if (fd < 0) {
			printk(KERN_ERR
			       "sys_mkdir dst_dir_str[%s] fail, fd = [%d]\n",
			       dst_dir_str, fd);
			ret = -1;
			goto out;
		}
	} else {
		sys_close(fd);
	}

	/* 组合last_kmsg和fastbootlog的文件的绝对路径 */
	memset(dst_str, 0, NEXT_LOG_PATH_LEN);
	memset(last_fastbootlog_path, 0, NEXT_LOG_PATH_LEN);
	memset(fastbootlog_path, 0, NEXT_LOG_PATH_LEN);
	len = strlen(dst_dir_str);
	memcpy(dst_str, dst_dir_str, len + 1);
	memcpy(&dst_str[len], "/last_kmsg", strlen("/last_kmsg") + 1);
	memcpy(last_fastbootlog_path, dst_dir_str, len + 1);
	memcpy(&last_fastbootlog_path[len], "/last_fastboot_log",
	       strlen("/last_fastboot_log") + 1);
	memcpy(fastbootlog_path, dst_dir_str, len + 1);
	memcpy(&fastbootlog_path[len], "/fastboot_log",
	       strlen("/fastboot_log") + 1);

	/* 生成last_fastbootlog文件 */
	ret = rdr_copy_file_apend(last_fastbootlog_path,
				  LAST_FASTBOOT_LOG_FILE);
	if (ret) {
		printk("rdr_copy_file_apend [%s] fail, ret = [%d]\n",
		       LAST_FASTBOOT_LOG_FILE, ret);
	}

	/* 生成curr_fastbootlog文件 */
	ret = rdr_copy_file_apend(fastbootlog_path, FASTBOOT_LOG_FILE);
	if (ret) {
		printk("rdr_copy_file_apend [%s] fail, ret = [%d]\n",
		       FASTBOOT_LOG_FILE, ret);
	}

	/* 生成last_kmsg文件及dmesg-ramoops-x文件 */
	for (i = 0; i < tmp_cnt; i++) {
		/* 生成源文件绝对路径 */
		memset((void *)fullpath_arr, 0, sizeof(fullpath_arr));
		strncat(fullpath_arr, PSTORE_PATH, strlen(PSTORE_PATH));
		len =
		    strlen(pbuff + i * MNTN_FILESYS_PURE_DIR_NAME_LEN);
		printk("file is [%s]\n",
		       (pbuff + i * MNTN_FILESYS_PURE_DIR_NAME_LEN));
		strncat(fullpath_arr,
			(const char *)(pbuff + i * MNTN_FILESYS_PURE_DIR_NAME_LEN),
			len);

		/* 如果不是console则目的文件非last_kmsg，为dmesg-ramoops-x */
		if (i > 0) {
			memset((void *)dst_str, 0, NEXT_LOG_PATH_LEN);
			strncat(dst_str, dst_dir_str,
				strlen(dst_dir_str));
			strncat(dst_str, "/", strlen("/"));
			strncat(dst_str,
				(const char *)(pbuff + i * MNTN_FILESYS_PURE_DIR_NAME_LEN),
				len);
		}

		/* 将源文件的内容拷贝到目的文件中 */
		ret = rdr_copy_file_apend(dst_str, fullpath_arr);
		if (ret) {
			printk(KERN_ERR
			       "rdr_copy_file_apend [%s] fail, ret = [%d]\n",
			       fullpath_arr, ret);
			ret = -1;
			goto out;
		}

		/* 如果是console，则不需要删除源文件，否则删除 */
		if (i == 0)
			continue;

		/* 删除源文件 */
		ret = mntn_filesys_rm_file(fullpath_arr);
		if (ret) {
			printk(KERN_ERR
			       "mntn_filesys_rm_file [%s] fail, ret = [%d]\n",
			       fullpath_arr, ret);
			ret = -1;
			goto out;
		}
	}

out:
	set_fs(oldfs);
	kfree(pbuff);
	reboot_type = rdr_get_reboot_type();

	/* 如果是modem的dmss异常，需要保存bl31的log */
	if (CP_S_MODEMDMSS == reboot_type) {
		save_bl31_exc_memory();
	}

	/* 如果异常触发不是通过rdr_system_error触发的，则在rdr_hisiap_dump文件中新建DONE文件 */
	if (reboot_type < REBOOT_REASON_LABEL3
	    || LPM3_S_EXCEPTION == reboot_type
	    || MMC_S_EXCEPTION == reboot_type
	    || (REBOOT_REASON_LABEL4 <= reboot_type
	    && REBOOT_REASON_LABEL5 > reboot_type)) {
		return ret;
	}

	/* 文件系统sync，保证读写任务完成 */
	if (!in_atomic() && !irqs_disabled() && !in_irq()) {
		sys_sync();
	}

	/* 在异常目录下面新建DONE文件，标志此次异常log保存完毕 */
	bbox_save_done(g_log_path, BBOX_SAVE_STEP_DONE);

	/* 如果函数入参是null，则表示是在rdr_hisiap_dump中调用的，不需要chown */
	if (!arg) {
		return ret;
	}

	/* 根据权限要求，hisi_logs目录及子目录群组调整为root-system */
	ret = (int)bbox_chown((const char __user *)g_log_path, ROOT_UID,
			      SYSTEM_GID, true);
	if (ret) {
		printk(KERN_ERR
		       "[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
		       __func__, PATH_ROOT, ROOT_UID, SYSTEM_GID, ret);
	}

	return ret;
}

/*****************************************************************************
Description : 将未注册到rdr的异常写入history.log中
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
int record_reason_task(void *arg)
{
	char date[DATATIME_MAXLEN];
	struct rdr_exception_info_s temp = {
		{0, 0}, 0x80000001, 0x80000001, RDR_ERR, RDR_REBOOT_NOW,
		RDR_AP, RDR_AP, RDR_AP, RDR_REENTRANT_DISALLOW,
		COLDBOOT, RDR_UPLOAD_YES, "ap", "ap", 0, (void *)0, 0
	};
	temp.e_from_core = RDR_AP;
	temp.e_exce_type = rdr_get_reboot_type();

	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;
	memset(date, 0, DATATIME_MAXLEN);
	snprintf(date, DATATIME_MAXLEN, "%s-%08lld",
		 rdr_get_timestamp(), rdr_get_tick());
	rdr_save_history_log(&temp, &date[0], true);
	return 0;
}

/*****************************************************************************
Description : 钩子函数，用于系统panic处理之前死循环，使现场保留
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static int acpu_panic_loop_notify(struct notifier_block *nb,
				  unsigned long event, void *buf)
{
	if (check_himntn(HIMNTN_PANIC_INTO_LOOP) == 1) {
		do {
		} while (1);
	}

	return 0;
}

/*****************************************************************************
Description : panic复位的钩子函数
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static int rdr_hisiap_panic_notify(struct notifier_block *nb,
				   unsigned long event, void *buf)
{
	printk(KERN_ERR "[%s], ===> enter panic notify!\n", __func__);
	rdr_syserr_process_for_ap(MODID_AP_S_PANIC, 0, 0);
	return 0;
}

/*****************************************************************************
Description : die复位的钩子函数
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
static int rdr_hisiap_die_notify(struct notifier_block *nb,
				 unsigned long event, void *pReg)
{
	return 0;
}

/*******************************************************************************
Function:       modemddrc_happen
Description:    当modem触发了ddrc异常时，保存log，然后再复位系统
Input:          NA
Output:         NA
Return:         -1 : error, 0 : ok
********************************************************************************/
int modemddrc_happen(void)
{
	printk(KERN_ERR "modemddrc_happen start\n");
	down(&modemddrc_happen_sem);
	printk(KERN_ERR "modemddrc_happen goto rdr_system_error\n");
	rdr_system_error(RDR_MODEM_DMSS_MOD_ID, 0, 0);
	return 0;
}
#ifdef CONFIG_HISI_CORESIGHT_TRACE
/*******************************************************************************
Function:       set_etr_trace_info
Description:    set etr trace data information
Input:      paddr : etr trace buffer's physical addres
		size : etr trace buffer's size
		offset: etr trace buffer's offset
Output:         NA
Return:         NA
others:         在etm enable和tmc初始化的时候调用
********************************************************************************/
void set_etr_trace_info(u64 paddr, u32 size, u32 offset)
{
	AP_RECORD_ETR *petr;
	printk(KERN_SOH "[%s]:enter g_bbox_ap_record_pc=%p\n",
	       __func__, g_bbox_ap_record_pc);

	/*check if ap record is ready */
	if (!g_bbox_ap_record_pc) {
		printk(KERN_ERR
		       "[%s]:g_bbox_ap_record_pc isn't ready\n",
		       __func__);
		g_bbox_etr_info.paddr = paddr;
		g_bbox_etr_info.size = size;
		g_bbox_etr_info.rd_offset = (offset == (u32)-1) ? 0 : offset;
		g_bbox_etr_info_init = 1;
		return;
	}

	petr = (AP_RECORD_ETR *) ((char *)g_bbox_ap_record_pc +
			       ETR_TRACE_OFFSET_BBOX);
	printk(KERN_ERR "[%s]:enter petr=%p,offset=0x%x\n",
	       __func__, petr, offset);
	strncpy(petr->magic, ETR_MAGIC_START, ETR_MAGIC_SIZE);
	petr->magic[ETR_MAGIC_SIZE - 1] = '\0';
	petr->paddr = paddr;
	petr->size = size;
	petr->rd_offset = (offset == (u32)-1) ? 0 : offset;

	printk(KERN_SOH "[%s]:exit\n", __func__);
}
/*******************************************************************************
Function:       fill_etr_trace_info
Description:    将etr head信息保存到bbox
Input:          NA
Output:         NA
Return:         NA
others:
********************************************************************************/
void fill_etr_trace_info(void)
{
	AP_RECORD_ETR *petr;

	printk(KERN_SOH "[%s]:enter\n", __func__);
	if (!g_bbox_ap_record_pc)
		return;
	petr = (AP_RECORD_ETR *) ((char *)g_bbox_ap_record_pc +
			       ETR_TRACE_OFFSET_BBOX);
	memset(petr, 0, sizeof(AP_RECORD_ETR));
	if (!g_bbox_etr_info_init) {
		return;
	}
	strncpy(petr->magic, ETR_MAGIC_START, ETR_MAGIC_SIZE);
	petr->magic[ETR_MAGIC_SIZE - 1] = '\0';
	petr->paddr = g_bbox_etr_info.paddr;
	petr->size = g_bbox_etr_info.size;
	petr->rd_offset = g_bbox_etr_info.rd_offset;
	printk(KERN_SOH "[%s]:exit\n", __func__);
}
#endif

/*****************************************************************************
Description : 初始化函数
History
1.Date: 2015/02/06
Author : l00249396
Modification : Created function
*****************************************************************************/
int __init rdr_hisiap_init(void)
{
	struct task_struct *recordTask = NULL;
	u32 reboot_type = 0;
	int ret = 0;
	printk("%s init start\n", __func__);

	if (get_pmu_reset_base_addr())
		return -1;

	g_mi_notify_lpm3_addr = (u64)ioremap(NMI_NOTIFY_LPM3_ADDR, 0x4);
	if (!g_mi_notify_lpm3_addr) {
		printk(KERN_ERR "[%s]", __func__);
		return -1;
	}

	rdr_hisiap_register_exception();
	ret = rdr_hisiap_register_core();
	if (ret) {
		printk("%s rdr_hisiap_register_core fail, ret = [%d]\n",
		       __func__, ret);
		return ret;
	}
	g_bbox_ap_record_pc = hisi_bbox_map(current_info.log_addr,
					   PMU_RESET_RECORD_DDR_AREA_SIZE);
	if (!g_bbox_ap_record_pc) {
		printk(KERN_ERR
		       "hisi_bbox_map g_bbox_ap_record_pc fail\n");
		return -1;
	}
#ifdef CONFIG_HISI_CORESIGHT_TRACE
	fill_etr_trace_info();
#endif
	g_hisiap_addr =
	    (u64) hisi_bbox_map(current_info.log_addr +
				PMU_RESET_RECORD_DDR_AREA_SIZE,
				current_info.log_len - PMU_RESET_RECORD_DDR_AREA_SIZE);
	if (!g_hisiap_addr) {
		printk(KERN_ERR "hisi_bbox_map g_hisiap_addr fail\n");
		return -1;
	}
	printk(KERN_ERR "[%s], retinfo: log_addr [0x%llx][0x%llx]",
	       __func__, current_info.log_addr, g_hisiap_addr);

	ret = rdr_hisiap_dump_init(&current_info);
	if (ret) {
		printk("%s rdr_hisiap_dump_init fail, ret = [%d]\n",
		       __func__, ret);
		return -1;
	}
	reboot_type = rdr_get_reboot_type();

	if (REBOOT_REASON_LABEL3 <= reboot_type
	    && REBOOT_REASON_LABEL4 > reboot_type
	    && MMC_S_EXCEPTION != reboot_type
	    && LPM3_S_EXCEPTION != reboot_type) {
		recordTask = kthread_run(save_exception_info, "thread",
				"save_exception");
		printk(KERN_INFO
		       "%s: create save_exception_info, return %p\n",
		       __func__, recordTask);
	}
	if ((REBOOT_REASON_LABEL1 > reboot_type
	    || (REBOOT_REASON_LABEL4 <= reboot_type
	    && REBOOT_REASON_LABEL5 > reboot_type))
	    && check_himntn(HIMNTN_GOBAL_RESETLOG)) {
		recordTask = kthread_run(record_reason_task, NULL, "recordTask");
		printk(KERN_INFO
		       "%s: create record_reason_task, return %p\n",
		       __func__, recordTask);
	}

	/*如果异常类型为CP_S_MODEMAP，则需要保存kerneldump文件 */
	if (CP_S_MODEMAP == reboot_type
	    || CP_S_MODEMNOC == reboot_type
	    || CP_S_MODEMDMSS == reboot_type
	    || CP_S_RESETFAIL == reboot_type) {
		recordTask = kthread_run(save_kernel_dump, "thread",
				"save_kerneldump");
		printk(KERN_INFO
		       "%s: create save_kernel_dump, return %p\n",
		       __func__, recordTask);
	}

	atomic_notifier_chain_register(&panic_notifier_list,
				       &acpu_panic_loop_block);
	atomic_notifier_chain_register(&panic_notifier_list,
				       &rdr_hisiap_panic_block);
	panic_on_oops = 1;
	register_die_notifier(&rdr_hisiap_die_block);
	get_bbox_curtime_slice();

	sema_init(&modemddrc_happen_sem, 0);

	/*创建modem的ddrc处理任务 */
	if (!kthread_run(modemddrc_happen, NULL, "modemddrc_emit")) {
		printk(KERN_ERR
		       "create thread modemddrc_happen faild.\n");
	}
	rdr_ap_init = 1;
	printk("%s init end\n", __func__);

	return 0;
}

static void __exit rdr_hisiap_exit(void)
{
	return;
}

module_init(rdr_hisiap_init);
module_exit(rdr_hisiap_exit);

MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
