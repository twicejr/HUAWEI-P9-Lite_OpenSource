/*
  * hisilicon perf_stat driver, hisi_perf_stat.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  */

#include <asm/memory.h>
#include <asm/cacheflush.h>
#include <asm/irq_regs.h>
#include <asm/irqflags.h>
/*lint -e451*/
#include <linux/bug.h>
/*lint +e451*/
#include <linux/uaccess.h>

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/device.h>
#include <linux/stddef.h>
#include <linux/types.h>
#include <linux/timer.h>
#include <linux/platform_device.h>
#include <linux/perf_event.h>
#include <linux/bitmap.h>
#include <linux/vmalloc.h>
#include <linux/gfp.h>
#include <linux/dma-direction.h>
#include <linux/ptrace.h>
#include <linux/mutex.h>
#include <linux/printk.h>
#include <linux/wakelock.h>
#include <linux/regulator/consumer.h>
#include <linux/syscalls.h>
#include <linux/workqueue.h>
#include <soc_pmctrl_interface.h>
#include "hisi_perf_stat.h"
#include <linux/atomic.h>
#include "soc_perfstat_interface.h"

static char *master_name_hi3650[PERF_PORT_NUM] = {
	"perf-dsssubsys0",	/*0:dss0 */
	"perf-dsssubsys1",	/*1:dss1 */
	"",			/*2:cci0 */
	"",			/*3:cci1 */
	"perf-g3d",		/*4:gpu */
	"",			/*5:modem0 */
	"",			/*6:modem1 */
	"perf-ispsubsys0",	/*7:isp0 */
	"perf-ispsubsys1",	/*8:isp1 */
	"perf-vdec",		/*8:vdec */
	"perf-venc",		/*10:venc */
	"perf-ivp",		/*11:ivp */
	"",			/*12:system noc */
	"perf-asp",		/*13:asp */
	"",			/*14:EMMC */
	"perf-usbotg"		/*15:usbotg */
};

static char *master_name_hi6250[PERF_PORT_NUM] = {
	"perf-dsssubsys0",	/*0:dss0 */
	"perf-dsssubsys1",	/*1:dss1 */
	"",			/*2:cci0 */
	"",			/*3:cci1 */
	"perf-g3d",		/*4:gpu */
	"",			/*5:modem0 */
	"",			/*6:modem1 */
	"perf-ispsubsys0",	/*7:isp0 */
	"perf-ispsubsys1",	/*8:isp1 */
	"perf-vdec",		/*8:vdec */
	"perf-venc",		/*10:venc */
	"",			/*11:ivp */
	"",			/*12:system noc */
	"perf-asp",		/*13:asp */
	"",			/*14:EMMC */
	""			/*15:usbotg */
};

static char **master_name;

static struct perfstat_dev_info *perfstat_info;
static void __iomem *perfstat_base;
static unsigned long sys_sample_time;
static bool perf_file_saved;
struct completion perf_comp;
static bool is_probe_comp;
static struct mutex perfstat_transaction_mutex;
static atomic_t is_recording = ATOMIC_INIT(0);

static struct of_device_id of_perfstat_match_tbl[] = {
	{
	 .compatible = "hisilicon,hi3650-perfstat-driver",
	 .data = master_name_hi3650,
	 },
	{
	 .compatible = "hisilicon,hi6250-perfstat-driver",
	 .data = master_name_hi6250,
	 },

	{ /* end */ }
};

#define perfstat_reg_read(reg_addr)  \
				(*(volatile int *)(reg_addr))
#define perfstat_reg_write(reg_addr, reg_value) \
				(*(volatile int *)(reg_addr) = reg_value)

static void perfstat_set_sample_cnt(int cnt)
{
	perfstat_reg_write(SOC_PERFSTAT_SAMPLE_CNT_REG_ADDR(perfstat_base),
			   cnt);
}

static void perfstat_set_sample_period(int usec)
{
	int value;
	struct perfstat_dev_info *dev_info = perfstat_info;

	value = usec * (int)(dev_info->sample_clk_rate / PERF_MILLION);
	perfstat_set_sample_cnt(value);
}

static void perfstat_set_sample_num(int times)
{
	perfstat_reg_write(SOC_PERFSTAT_SAMPLE_NUM_REG_ADDR(perfstat_base),
			   times);
}

static void perfstat_set_sample_port(int port)
{
	perfstat_reg_write(SOC_PERFSTAT_REAL_PORT_NUM_ADDR(perfstat_base),
			   port);
}

static void perfstat_set_addr_mode(int mode)
{
	perfstat_reg_write(SOC_PERFSTAT_AXI_ADDR_MODE_ADDR(perfstat_base),
			   mode);
}

static int perfstat_set_list_mode_addr(int addr)
{
	if (!PERF_IS_ALIGNED(addr, ALIGNED_NUM)) {
		pr_err("[%s] 8 bytes align needed\n", __func__);
		return PERF_ERROR;
	}

	perfstat_reg_write(SOC_PERFSTAT_DESCRIPTOR_ADDR_ADDR(perfstat_base),
			   addr);

	return PERF_OK;
}

static void perfstat_set_timeout_cnt(int cnt)
{
	perfstat_reg_write(SOC_PERFSTAT_OVERTIME_CFG_CNT_ADDR(perfstat_base),
			   cnt);
}

static void perfstat_set_timeout_duration(int msec)
{
	int value;
	struct perfstat_dev_info *dev_info = perfstat_info;

	value = msec * (int)(dev_info->sample_clk_rate / PERF_TIME_1MS);
	perfstat_set_timeout_cnt(value);
}

static void perfstat_set_monitor_reset(void)
{
	perfstat_reg_write(SOC_PERFSTAT_MONITOR_RESET_ADDR(perfstat_base),
			   RST_ADDR);
}

static void perfstat_trigger_sample_start(void)
{
	perfstat_reg_write(SOC_PERFSTAT_CMD_START_ADDR(perfstat_base),
			   RST_ADDR);
}

static void perfstat_trigger_sample_stop(void)
{
	perfstat_reg_write(SOC_PERFSTAT_SAMPLE_STOP_ADDR(perfstat_base),
			   RST_ADDR);
}

static void perfstat_enable_interrupt(int type)
{
	int value;

	value = perfstat_reg_read(SOC_PERFSTAT_INT_EN_ADDR(perfstat_base));
	value |= type;
	perfstat_reg_write(SOC_PERFSTAT_INT_EN_ADDR(perfstat_base), value);
}

static void perfstat_clear_interrupt(int type)
{
	perfstat_reg_write(SOC_PERFSTAT_INT_CLR_ADDR(perfstat_base), type);
}

static int perfstat_get_masked_int_stat(void)
{
	return
	    perfstat_reg_read(SOC_PERFSTAT_MASK_INT_STAT_ADDR(perfstat_base));
}

static int perfstat_get_cur_sample_cnt(void)
{
	return
	    perfstat_reg_read(SOC_PERFSTAT_ALL_SAMPLE_NUM_ADDR(perfstat_base));
}

static int perfstat_get_cur_data_addr(void)
{
	return
	    perfstat_reg_read(SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_ADDR
			      (perfstat_base));
}

static int perfstat_get_cur_list_addr(void)
{
	return
	    perfstat_reg_read(SOC_PERFSTAT_LAST_DESC_ADDR_ADDR(perfstat_base));
}

static int perfstat_get_fifo_status(void)
{
	return
	    perfstat_reg_read(SOC_PERFSTAT_DEBUG_FIFO_FULL_ADDR(perfstat_base));
}

static int perfstat_get_block_port(void)
{
	return
	    perfstat_reg_read(SOC_PERFSTAT_DEBUG_MONITOR_ADDR(perfstat_base));
}

static int perfstat_get_list_mode_addr(void)
{
	return
	    perfstat_reg_read(SOC_PERFSTAT_DESCRIPTOR_ADDR_ADDR(perfstat_base));
}

static int perfstat_get_reset_cnt(void)
{
	return perfstat_reg_read(SOC_PERFSTAT_STAT_RST_CNT_ADDR(perfstat_base));
}

static int perfstat_get_is_sampling(void)
{
	return perfstat_reg_read(SOC_PERFSTAT_CMD_START_ADDR(perfstat_base));
}

static void perfstat_debug_info_show(void)
{
	int cur_samp_cnt, cur_data_addr, cur_list_addr, dbg_fifo_stat,
	    dbg_block_port;

	cur_samp_cnt = perfstat_get_cur_sample_cnt();
	cur_data_addr = perfstat_get_cur_data_addr();
	cur_list_addr = perfstat_get_cur_list_addr();
	dbg_fifo_stat = perfstat_get_fifo_status();
	dbg_block_port = perfstat_get_block_port();

	pr_err("[%s]CurSampCnt   : 0x%x\n", __func__, cur_samp_cnt);
	pr_err("[%s]CurDataAddr  : 0x%x\n", __func__, cur_data_addr);
	pr_err("[%s]CurListAddr  : 0x%x\n", __func__, cur_list_addr);
	pr_err("[%s]DbgFIFOStat  : 0x%x\n", __func__, dbg_fifo_stat);
	pr_err("[%s]DbgBlockPort : 0x%x\n", __func__, dbg_block_port);

	return;
}

static void perfstat_list_done_handler(void)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	pr_err("[%s] list done", __func__);
	if (PERF_SAMPLE_HIGHSPEED == dev_info->samp_type) {
		if (!perf_file_saved && !atomic_read(&is_recording)) {
			pr_err("%s: save perf data...\n", __func__);
			schedule_delayed_work(&dev_info->hs_record_data_work,
					      0);
		}
	}
	return;
}

static void perfstat_sample_done_handler(void)
{
	struct perfstat_dev_info *dev_info = perfstat_info;

	pr_err("[%s]perf sample done\n", __func__);
	perfstat_debug_info_show();
	if (!dev_info->list) {
		pr_err("[%s]no list exits\n", __func__);
		return;
	}

	if (PERF_SAMPLE_HSCYCLE == dev_info->samp_type) {
		if (!perf_file_saved && !atomic_read(&is_recording)) {
			pr_err("%s: save perf data...\n", __func__);
			schedule_delayed_work(&dev_info->hs_record_data_work,
					      0);
		}
		return;
	}
}

static void perfstat_list_error_handler(void)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	int val;
	perf_list_descriptor *list_cfg;

	pr_err("[%s]perf list error\n", __func__);
	perfstat_debug_info_show();

	val = perfstat_get_list_mode_addr();
	pr_err("[%s]list addr inReg is 0x%x.\n", __func__, val);
	list_cfg = dev_info->list;
	if (!list_cfg)
		pr_err("[%s]list addr inSof is null.\n", __func__);
	else
		pr_err("[%s]list addr inSof is 0x%x.\n", __func__,
		       (int)__virt_to_phys(list_cfg));

	return;
}

static void perfstat_port_overtime_handler(void)
{
	pr_err("[%s] perf port overtime!\n", __func__);
	perfstat_debug_info_show();
}

static irqreturn_t perfstat_interrupt_handler(int irq, void *data)
{
	int val;
	struct perfstat_dev_info *dev_info = (struct perfstat_dev_info *)data;
	spin_lock(&dev_info->synclock);
	if (PERF_TASK_DONE == dev_info->status) {
		pr_err("[%s]perfstat is in TASK_DONE mode!\n", __func__);
		perfstat_clear_interrupt(PERF_INT_ALL);
		goto out;
	}

	val = perfstat_get_masked_int_stat();
	if (val & PERF_INT_SAMP_DONE) {
		perfstat_clear_interrupt(PERF_INT_ALL);
		perfstat_sample_done_handler();
	}

	if (val & PERF_INT_LIST_DONE) {
		perfstat_clear_interrupt(PERF_INT_LIST_DONE);
		perfstat_list_done_handler();
	}

	if (val & PERF_INT_LIST_ERR) {
		perfstat_clear_interrupt(PERF_INT_LIST_ERR);
		perfstat_list_error_handler();
	}

	if (val & PERF_INT_OVER_TIME) {
		perfstat_clear_interrupt(PERF_INT_OVER_TIME);
		perfstat_port_overtime_handler();
	}

out:
	spin_unlock(&dev_info->synclock);
	return IRQ_HANDLED;
}

static int perfstat_check_ready(void)
{
	volatile int val;
	volatile int count;

	count = 200;
	do {
		val = perfstat_get_reset_cnt();
		count--;
	} while (val & count);

	if (!count)
		return PERF_ERROR;

	perfstat_set_monitor_reset();
	return PERF_OK;
}

static int perfstat_is_modem_powerup(void)
{
	struct device_node *np = NULL;
	void __iomem *pmctrl_base;
	int modem_noc_idleack;
	int ret = PERF_OK;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmctrl");
	pmctrl_base = of_iomap(np, 0);
	if (!pmctrl_base)
		return PERF_ERROR;

	modem_noc_idleack =
	    readl_relaxed(pmctrl_base + SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(0));
	if (modem_noc_idleack & BIT(3))
		ret = PERF_ERROR;

	iounmap(pmctrl_base);
	pmctrl_base = NULL;
	return ret;
}

static int perfstat_master_is_valid(unsigned long *sample_port)
{
	int i;
	struct perfstat_dev_info *dev_info = perfstat_info;

	pr_err("[%s]port is 0x%x\n", __func__, (int)*sample_port);
	for (i = 0; i < PERF_PORT_NUM; i++) {
		if (*sample_port & PERF_PORT_BIT(i)) {
			if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i))) {
				pr_err("[%s] (%d)%s this port is not valid!\n",
				       __func__, i, master_name[i]);
				/* clear this port */
				*sample_port &= (~PERF_PORT_BIT(i));
			}
		}
	}

	/* If no master is powered up, not need to start perfstat. */
	if (0 == *sample_port) {
		pr_err("[%s]no master is valid\n", __func__);
		return PERF_ERROR;
	}

	pr_err("[%s]port is 0x%x\n", __func__, (int)*sample_port);
	return PERF_OK;
}

/**
* Judge if the master is powerup and
* only monitor the powerup ones.
**/
static int perfstat_master_is_powerup(unsigned long *sample_port)
{
	int i, ret = PERF_OK;
	struct perfstat_dev_info *dev_info = perfstat_info;

	pr_err("[%s]port is 0x%x\n", __func__, (int)*sample_port);

	for (i = 0; i < PERF_PORT_NUM; i++) {
		if (*sample_port & PERF_PORT_BIT(i)) {
			/*if master is not valid, goto next master */
			if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i))) {
				pr_err("[%s] %s-supply is not valid!\n",
				       __func__, master_name[i]);
				*sample_port &= ~PERF_PORT_BIT(i);
				continue;
			}
			if ((PERF_PORT_MODEM0 == i) || (PERF_PORT_MODEM1 == i)) {
				ret = perfstat_is_modem_powerup();
				if (ret != PERF_OK) {
					pr_err
					    ("[%s] modem-supply is not enabled\n",
					     __func__);
					*sample_port &=
					    ~(PERF_PORT_BIT(PERF_PORT_MODEM0) |
					      PERF_PORT_BIT(PERF_PORT_MODEM1));
				}
				continue;
			}
			if (!strncmp
			    ("", master_name[i], strlen(master_name[i]) + 1)) {
				continue;
			}
			ret = regulator_is_enabled(dev_info->master_supply[i]);
			if (!ret) {
				pr_err("[%s] %s-supply is not enabled\n",
				       __func__, master_name[i]);
				*sample_port &= ~PERF_PORT_BIT(i);
			}
		}
	}

	/* If no master is powered up, not need to start perfstat. */
	if (0 == *sample_port) {
		pr_err("[%s]no master is powerup\n", __func__);
		return PERF_ERROR;
	}

	pr_err("[%s]port is 0x%x\n", __func__, (int)*sample_port);
	return PERF_OK;
}

static void perfstat_record_sample_data(struct work_struct *work)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	int cur_list_addr, cur_data_addr, list_addr;
	unsigned long fs;
	long fd = 0;
	int ret = 0;
	void *start;
	int size_l = 0, size_h = 0;
	unsigned long size = 0;
	unsigned long all_sample_cnt = 0;
	unsigned long total_sample_size = 0;
	int i, page_idx, offset;
	int addr_mod = 0;

	if (!atomic_add_unless(&is_recording, 1, 1)) {
		pr_err("[%s] is recording, failed to record.\n", __func__);
		return;
	}

	if (!dev_info->virt_addr) {
		pr_err("[%s] store address has already freed.\n", __func__);
		return;
	}

	pr_err("[%s] sampe_type is 0x%x.\n", __func__, dev_info->samp_type);
	start = dev_info->virt_addr;
	size = PAGE_SIZE * dev_info->pages_n;
	/*invalid data buffer to be copied */
	__dma_map_area((const void *)start, size, DMA_FROM_DEVICE);

	all_sample_cnt = perfstat_get_cur_sample_cnt();
	pr_err("[%s] sampe cnt is 0x%lx.\n", __func__, all_sample_cnt);
	total_sample_size = dev_info->per_sample_size * all_sample_cnt;
	pr_err("[%s] total sampe size is 0x%lx.\n",
	       __func__, total_sample_size);
	if (total_sample_size > size &&
	    dev_info->samp_type == PERF_SAMPLE_HSCYCLE) {
		/*find out the current page_idx in pages */
		cur_list_addr = perfstat_get_cur_list_addr();
		cur_data_addr = perfstat_get_cur_data_addr();
		pr_err("[%s] cur_list_addr = %x.\n", __func__, cur_list_addr);
		pr_err("[%s] cur_data_addr = %x.\n", __func__, cur_data_addr);
		list_addr = (int)__virt_to_phys(dev_info->list);
		for (i = 0; i < dev_info->pages_n; i++) {
			if (list_addr == cur_list_addr)
				break;
			list_addr = list_addr + sizeof(u64);
		}
		if (unlikely(dev_info->pages_n == i)) {
			pr_err("[%s]no list addr matched\n", __func__);
			goto record_err;
		} else {
			page_idx = i;
		}

		pr_err("[%s] page_id = %d.\n", __func__, page_idx);
		/*count the data start_addr & size */
		addr_mod = (dev_info->pages_n * PAGE_SIZE) %
		    dev_info->per_sample_size + sizeof(perf_sample_data_head);
		offset =
		    cur_data_addr - dev_info->list[page_idx].bit_config.address;
		start =
		    (void *)((char *)(dev_info->virt_addr) +
			     PAGE_SIZE * page_idx + offset + addr_mod);
		size_l =
		    PAGE_SIZE * (dev_info->pages_n - page_idx) - offset -
		    addr_mod;
		size_h = PAGE_SIZE * page_idx + offset + addr_mod;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);
	fd = sys_open(PERF_HIGHSPEED_DATA_PATH, O_CREAT | O_WRONLY | O_TRUNC,
		      0660);
	if (fd < 0) {
		pr_err("[%s]open file failed, ret is %ld.\n", __func__, fd);
		goto record_err;
	}
	/*write time info */
	ret =
	    sys_write(fd, (const char *)&sys_sample_time,
		      sizeof(sys_sample_time));
	if (ret < 0) {
		pr_err("[%s]write file failed, ret is %d.\n", __func__, ret);
		goto write_err;
	}
	/*write perfstat raw data */
	if (total_sample_size > size &&
	    dev_info->samp_type == PERF_SAMPLE_HSCYCLE) {
		ret = sys_write(fd, start, size_l);
		if (ret < 0) {
			pr_err("[%s]write file failed, ret is %d.\n", __func__,
			       ret);
			goto write_err;
		}
		ret = sys_write(fd, dev_info->virt_addr, size_h);
		if (ret < 0) {
			pr_err("[%s]write file failed, ret is %d.\n", __func__,
			       ret);
			goto write_err;
		}
	} else {
		ret = sys_write(fd, start, size);
		if (ret < 0) {
			pr_err("[%s]write file failed, ret is %d.\n", __func__,
			       ret);
			goto write_err;
		}
	}

	ret = sys_fsync(fd);
	if (ret < 0)
		pr_err("[%s]sys_fsync failed, ret is %d\n", __func__, ret);

	perf_file_saved = true;
	pr_err("[%s]perf data saved complete!\n", __func__);
	complete(&perf_comp);
write_err:
	ret = sys_close(fd);
	if (ret < 0)
		pr_err("[%s]sys_close failed, ret is %d\n", __func__, ret);
	set_fs(fs);
record_err:
	atomic_dec(&is_recording);
}

static void perfstat_event_destroy(struct perf_event *event)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	int i, ret;
	mutex_lock(&perfstat_transaction_mutex);
	if (PERF_DEL_DONE != dev_info->status) {
		pr_err("[%s] perfstat is not running.\n", __func__);
		goto err_end;
	}

	pr_err("[%s] perfstat_event_destroy start...\n", __func__);
	if (perfstat_get_is_sampling())
		perfstat_trigger_sample_stop();

	if (PERF_SAMPLE_HIGHSPEED == dev_info->samp_type
	    || PERF_SAMPLE_HSCYCLE == dev_info->samp_type) {
		wait_for_completion(&perf_comp);
	}

	if (dev_info->virt_addr) {
		vunmap((const void *)dev_info->virt_addr);
		dev_info->virt_addr = NULL;
	}
	if (dev_info->pages) {
		for (i = 0; i < dev_info->pages_n; i++)
			__free_pages(dev_info->pages[i], 0);
		kfree(dev_info->pages);
		dev_info->pages = NULL;
	}
	if (dev_info->list) {
		kfree(dev_info->list);
		dev_info->list = NULL;
	}

	ret = regulator_disable(dev_info->perf_supply);
	if (ret < 0)
		pr_err("[%s]perf-supply disable fail\n", __func__);
	perf_file_saved = false;

	spin_lock(&dev_info->synclock);
	dev_info->status = PERF_TASK_DONE;
	spin_unlock(&dev_info->synclock);
	pr_err("[%s] perfstat_event_destroy end.\n", __func__);
err_end:
	mutex_unlock(&perfstat_transaction_mutex);
	return;
}

static int perfstat_print_sample_type(int event_id,
				      struct perfstat_dev_info *dev_info)
{
	if (dev_info == NULL)
		return -1;
	if (event_id == dev_info->event_id + PERF_SAMPLE_HSCYCLE) {
		dev_info->samp_type = PERF_SAMPLE_HSCYCLE;
		pr_err("[%s]perfstat use high speed cycle sample type.\n",
		       __func__);
	} else if (event_id == dev_info->event_id + PERF_SAMPLE_HIGHSPEED) {
		dev_info->samp_type = PERF_SAMPLE_HIGHSPEED;
		pr_err("[%s]perfstat use high speed sample type.\n", __func__);
	} else {
		pr_err("[%s] use mode error.\n", __func__);
		return -1;
	}
	return 0;
}

static int perfstat_check_perm(struct perf_event *event,
			      struct perfstat_dev_info *dev_info)
{
	int ret;
	int event_id;
	int sample_period;

	if (event->attr.type != PERF_TYPE_RAW) {
		goto check_err;
	}

	/*get the high 32 bit from attr.config as event id. */
	event_id = (int)(event->attr.config >> 32);
	ret = perfstat_print_sample_type(event_id, dev_info);
	if (ret < 0) {
		goto check_err;
	}

	/*get the period from attr.sample_period. */
	sample_period = event->attr.sample_period & SAMPLE_PERIOD_MASK;
	if (sample_period <= 0) {
		pr_err("[%s]sample_period(%d)<=0\n", __func__, sample_period);
		goto check_err;
	}

	return 0;
check_err:
	return -1;
}

static int perfstat_calculate_pages(struct perfstat_dev_info *dev_info,
				    struct page **pages, int *page_n,
				    int sample_period, int sample_time)
{
	int sz;
	if (0 == sample_time) {
		pr_err("%s: timing not specified, use default time.\n",
		       __func__);
		*page_n = PERF_MALLOC_PAGES_100M;
	} else {
		if (PERF_SAMPLE_HSCYCLE == dev_info->samp_type) {
			/*when in this mode, sptm means sample space size. */
			*page_n = sample_time * PERF_SIZE_1M / PAGE_SIZE;
		} else {
			sz = dev_info->per_sample_size *
			    ((sample_time * PERF_TIME_1US / sample_period) + 1);
			*page_n = Count_xINy_Num(PAGE_SIZE, sz);
		}
	}
	return 0;
}

static int perfstat_initialize_list_cfg(struct perfstat_dev_info *dev_info,
					perf_list_descriptor *list_cfg,
					int *list_head_phyaddr)
{
	signed int i = 0;
	int phy_addr;

	if (NULL == list_cfg) {
		pr_err("[%s]list_cfg is not intialized\n", __func__);
		return -1;
	}

	if (NULL == dev_info) {
		pr_err("[%s]dev_info is not intialized\n", __func__);
		return -1;
	}

	*list_head_phyaddr = (int)__virt_to_phys(list_cfg);
	pr_info("[%s] list_head_phyaddr is 0x%x\n", __func__,
		*list_head_phyaddr);
	for (i = 0; i < dev_info->pages_n; i++) {
		dev_info->pages[i] = alloc_page(GFP_KERNEL);
		if (!dev_info->pages[i])
			return -1;
		phy_addr =
		    (int)__virt_to_phys(page_address(dev_info->pages[i]));
		if (PERF_SAMPLE_HIGHSPEED == dev_info->samp_type) {
			if (unlikely(i == dev_info->pages_n - 1))
				list_cfg[i].value = PERF_LIST_CFG_INT;
			else
				list_cfg[i].value =
					PERF_LIST_CFG_NORMAL;
		} else {
				list_cfg[i].value = PERF_LIST_CFG_NORMAL;
		}
			list_cfg[i].bit_config.address = phy_addr;
			list_cfg[i].bit_config.length = PAGE_SIZE;
	}
	if (PERF_SAMPLE_HSCYCLE == dev_info->samp_type) {
		list_cfg[i].value = PERF_LIST_CFG_LINK;
		list_cfg[i].bit_config.address = *list_head_phyaddr;
	}
	return 0;
}

static int perfstat_intialize_data(struct perf_event *event, int *sample_period,
				   unsigned long *sample_port, int *sample_time)
{
	int ret;

	if (NULL == event) {
		pr_err("[%s]perf_event is not intialized\n", __func__);
		goto intialize_err;
	}

	if (NULL == sample_port) {
		pr_err("[%s]samplr_port is not intialized\n", __func__);
		goto intialize_err;
	}

	if (NULL == sample_period) {
		pr_err("[%s]sample_period is not intialized\n", __func__);
		goto intialize_err;
	}

	if (NULL == sample_time) {
		pr_err("[%s]sample_time is not intialized\n", __func__);
		goto intialize_err;
	}

	/*count buffer size to store data,then figure out
	   the pages size needed, and also the page size
	   reported once a interrupt */
	/*get the period from attr.sample_period. */
	*sample_period = event->attr.sample_period & SAMPLE_PERIOD_MASK;
	/*get the low 16 bit from attr.config as sample port. */
	*sample_port = event->attr.config & PERF_PORT_ALL;
	/*get the second low 16 bit from attr.config as sample time or perf data space size. */
	*sample_time = (int)((event->attr.config >> 16) & SAMPLE_TIME_MASK);

	ret = perfstat_master_is_valid(sample_port);
	if (PERF_OK != ret) {
		pr_err("[%s]no master is valid!\n", __func__);
		goto intialize_err;
	}

	ret = perfstat_master_is_powerup(sample_port);
	if (PERF_OK != ret) {
		pr_err("[%s]no master is powered up!\n", __func__);
		goto intialize_err;
	}

	event->attr.sample_type = PERF_SAMPLE_RAW;
	event->attr.mmap = 0;
	event->attr.comm = 0;
	event->attr.task = 0;
	event->destroy = perfstat_event_destroy;
	event->attr.disabled = 0;
	event->state = PERF_EVENT_STATE_INACTIVE;

	return 0;

intialize_err:
	return -1;
}

static int perfstat_event_init(struct perf_event *event)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	int sample_period, sample_time;
	unsigned long sample_port;
	int sample_port_num;
	int page_n;
	signed int i = 0;
	int ret;
	struct page **pages = NULL;
	perf_list_descriptor *list_cfg = NULL;
	int list_head_phyaddr;
	mutex_lock(&perfstat_transaction_mutex);
	if (event == NULL) {
		pr_err("[%s]perf_event is not intialized\n", __func__);
		goto err_end;
	}

	if (dev_info->status != PERF_TASK_DONE) {
		pr_err("[%s] Perf is sampling, please wait for it finished!\n",
		       __func__);
		goto err_end;
	}

	ret = regulator_enable(dev_info->perf_supply);
	if (ret < 0) {
		pr_err("[%s]perf-supply enable fail\n", __func__);
		goto err_end;
	}


	ret = perfstat_check_ready();
	if (ret < 0) {
		pr_err("[%s]perfstat is not ready\n", __func__);
		goto perf_supply_err;
	}

	ret = perfstat_check_perm(event, dev_info);
	if (ret < 0)
		goto perf_supply_err;

	ret =
	    perfstat_intialize_data(event, &sample_period, &sample_port,
				    &sample_time);
	if (ret < 0)
		goto perf_supply_err;

	pr_err("==============[hisi perf prepare +]================\n");

	sample_port_num =
	    bitmap_weight((unsigned long const *)&sample_port,
			  2 * sizeof(sample_port));
	dev_info->per_sample_size =
	    (sample_port_num * dev_info->per_data_sz) +
	    sizeof(perf_sample_data_head);
	if (PERF_SAMPLE_HIGHSPEED == dev_info->samp_type
	    || PERF_SAMPLE_HSCYCLE == dev_info->samp_type) {
		ret =                   /* [false alarm]:fortify */
		    perfstat_calculate_pages(dev_info, pages, &page_n,
					     sample_period, sample_time);
		if (ret < 0)
			goto err;

		pages =
		    kzalloc((page_n * sizeof(struct page *)),
			    GFP_KERNEL | GFP_DMA);
		if (!pages) {
			pr_err("[%s] cannot allocate pages ptr buffer\n",
			       __func__);
			goto err;
		}

		dev_info->pages = pages;
		dev_info->pages_n = page_n;
		dev_info->sprt = (int)sample_port;

		pr_err("[%s] port   : 0x%x\n", __func__, (int)sample_port);
		pr_err("[%s] period : %dus\n", __func__, sample_period);
		pr_err("[%s] page_n  : %d\n", __func__, page_n);
		pr_err("[%s] per_sample_size  : %d\n", __func__,
		       dev_info->per_sample_size);

		/*page_n + 1: add one more cfg for link. */
		list_cfg =
		    kzalloc(((page_n + 1) * sizeof(perf_list_descriptor)),
			    GFP_KERNEL | GFP_DMA);
		if (!list_cfg) {
			pr_err("[%s] cannot allocate list_cfg buffer\n",
			       __func__);
			goto err;
		}
		dev_info->list = list_cfg;
		ret =
		    perfstat_initialize_list_cfg(dev_info, list_cfg,
						 &list_head_phyaddr);
		if (ret < 0)
			goto err;
		/*flush list_cfg into ddr */
		__dma_map_area((const void *)list_cfg,
			       ((page_n + 1) * sizeof(perf_list_descriptor)),
			       DMA_TO_DEVICE);
	} else {
		pr_err("[%s] high speed mode only!\n", __func__);
		goto err;
	}

	/*map pages to a continuous virtual address */
	dev_info->virt_addr = vmap(pages, page_n, VM_MAP, PAGE_KERNEL);
	if (!dev_info->virt_addr) {
		pr_err("[%s] vmap pages error\n", __func__);
		goto err;
	}

	memset(dev_info->virt_addr, 0, page_n * PAGE_SIZE);
	__dma_map_area((const void *)dev_info->virt_addr,
		       (page_n * PAGE_SIZE), DMA_FROM_DEVICE);
	pr_info("[%s] vmap is %p\n", __func__, dev_info->virt_addr);

	perfstat_set_sample_period(sample_period);
	perfstat_set_sample_port((int)sample_port);
	perfstat_set_sample_num(PERF_SAMPLE_ALWAYS);
	perfstat_set_addr_mode(PERF_LIST_ADDR_MODE);
	ret = perfstat_set_list_mode_addr(list_head_phyaddr);
	if (PERF_OK != ret) {
		pr_err("[%s] set list addr error\n", __func__);
		goto err;
	}
	perfstat_clear_interrupt(PERF_INT_ALL);
	perfstat_enable_interrupt(PERF_INT_ALL);
	perfstat_set_timeout_duration(10);
	dev_info->status = PERF_INIT_DONE;
	mutex_unlock(&perfstat_transaction_mutex);
	pr_err("==============[hisi perf prepare -]================\n");

	return 0;

err:
	if (dev_info->virt_addr) {
		vunmap(dev_info->virt_addr);
		dev_info->virt_addr = NULL;
	}
	if (dev_info->list) {
		kfree(dev_info->list);
		dev_info->list = NULL;
	}
	if (dev_info->pages) {
		for (i = i - 1; i >= 0; i--)
			__free_pages(dev_info->pages[i], 0);
		kfree(dev_info->pages);
		dev_info->pages = NULL;
	}
perf_supply_err:
	ret = regulator_disable(dev_info->perf_supply);
	dev_info->status = PERF_TASK_DONE;
	if (ret < 0)
		pr_err("[%s]perf-supply disable fail\n", __func__);
err_end:
	mutex_unlock(&perfstat_transaction_mutex);
	return -ENOENT;
}

static int perfstat_add(struct perf_event *bp, int flags)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	mutex_lock(&perfstat_transaction_mutex);
	if (PERF_INIT_DONE != dev_info->status) {
		pr_err("[%s] perf is sampling cannot add event\n", __func__);
		goto err_end;
	}
	wake_lock(&dev_info->wakelock);

	pr_info("[%s][hisi perf start sample...]\n", __func__);
	perfstat_trigger_sample_start();

	sys_sample_time = hisi_getcurtime();
	pr_err("[%s] sample time is %lu\n", __func__, sys_sample_time);

	dev_info->status = PERF_ADD_DONE;
	mutex_unlock(&perfstat_transaction_mutex);
	return 0;
err_end:
	mutex_unlock(&perfstat_transaction_mutex);
	return -ENOENT;
}

static void perfstat_del(struct perf_event *bp, int flags)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	mutex_lock(&perfstat_transaction_mutex);
	if (PERF_ADD_DONE != dev_info->status) {
		pr_err("[%s] perf is sampling cannot del event", __func__);
		goto err_end;
	}

	if ((PERF_SAMPLE_HIGHSPEED == dev_info->samp_type) && (!perf_file_saved)
	    && !atomic_read(&is_recording)) {
		pr_err("%s: save perf data...\n", __func__);
		schedule_delayed_work(&dev_info->hs_record_data_work, 0);
	}

	pr_info("[%s][hisi perf stop sample]\n", __func__);
	perfstat_trigger_sample_stop();

	pr_err("==============[hisi perf finish +]================\n");
	perfstat_debug_info_show();
	pr_err("==============[hisi perf finish -]================\n");
	wake_unlock(&dev_info->wakelock);
	dev_info->status = PERF_DEL_DONE;
err_end:
	mutex_unlock(&perfstat_transaction_mutex);
	return;
}

static void perfstat_start(struct perf_event *bp, int flags)
{
	bp->hw.state = 0;
}

static void perfstat_stop(struct perf_event *bp, int flags)
{
	bp->hw.state = PERF_HES_STOPPED;
}

static void perfstat_read(struct perf_event *bp)
{
	return;
}

static int perfstat_event_idx(struct perf_event *bp)
{
	return 0;
}

static struct pmu perf_stat_pmu = {
	.event_init = perfstat_event_init,
	.add = perfstat_add,
	.del = perfstat_del,
	.start = perfstat_start,
	.stop = perfstat_stop,
	.read = perfstat_read,
	.event_idx = perfstat_event_idx,
};

static int fake_of_get_perfstat_attribute(const struct device_node *np,
					  struct perfstat_dev_info *dev_info)
{
	int ret;

	ret =
	    of_property_read_u32(np, "hisilicon,perf-event-id",
				 &dev_info->event_id);
	if (ret < 0) {
		pr_err("[%s] cannot get perf-event-id\n", __func__);
		return -ENOENT;
	}

	ret =
	    of_property_read_u32(np, "hisilicon,per-data-size",
				 &dev_info->per_data_sz);
	if (ret < 0) {
		pr_err("[%s] cannot get per-data-size\n", __func__);
		return -ENOENT;
	}

	ret =
	    of_property_read_u32(np, "hisilicon,vldmsk-of-sprt",
				 &dev_info->vldmsk_of_sprt);
	if (ret < 0) {
		pr_err("[%s] cannot get vldmsk-of-sprt\n", __func__);
		return -ENOENT;
	}
	return 0;
}

static int perfstat_get_fpga_flag(unsigned int *pFpga)
{
	struct device_node *np = NULL;
	unsigned int fpga_flag = 0;
	int ret = 0;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,hisifb");
	if (!np) {
		pr_err("NOT FOUND device node 'hisilicon,hisifb'!\n");
		return -ENXIO;
	}
	ret = of_property_read_u32(np, "fpga_flag", &fpga_flag);
	if (ret) {
		pr_err("failed to get fpga_flag resource.\n");
		return -ENXIO;
	}
	*pFpga = fpga_flag;
	return 0;
}

static int perfstat_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int i, ret;
	struct perfstat_dev_info *dev_info;
	unsigned int fpga_flag = 0;
	const struct of_device_id *match;

	pr_err("================[hisi perf probe s]================\n");

	/* Get fpga flag first */
	perfstat_get_fpga_flag(&fpga_flag);

	/* to check which type of regulator this is */
	match = of_match_device(of_perfstat_match_tbl, dev);
	if (NULL == match) {
		pr_err("[%s]: mismatch of perf_stat driver\n", __func__);
		return -ENODEV;
	}

	master_name = (char **)match->data;

	dev_info =
	    devm_kzalloc(dev, sizeof(struct perfstat_dev_info), GFP_KERNEL);
	if (!dev_info) {
		pr_err("[%s] cannot alloc perfstat desc\n", __func__);
		return -ENOMEM;
	}
	perfstat_info = dev_info;

	dev_info->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!dev_info->res) {
		pr_err("[%s] platform_get_resource err\n", __func__);
		return -ENOENT;
	}

	if (!devm_request_mem_region(dev, dev_info->res->start,
				     resource_size(dev_info->res),
				     pdev->name)) {
		pr_err("[%s] cannot claim register memory\n", __func__);
		return -ENOMEM;
	}

	perfstat_base =
	    ioremap(dev_info->res->start, resource_size(dev_info->res));
	if (!perfstat_base) {
		pr_err("[%s] base address ioremap fail\n", __func__);
		return -ENOMEM;
	}

	dev_info->irq = platform_get_irq(pdev, 0);
	if (dev_info->irq < 0) {
		pr_err("[%s] platform_get_irq err\n", __func__);
		return -ENXIO;
	}

	ret =
	    request_threaded_irq(dev_info->irq, perfstat_interrupt_handler,
				 NULL, IRQF_NO_SUSPEND, "pertstat-irq",
				 dev_info);
	if (ret < 0) {
		pr_err("[%s] requset irq error\n", __func__);
		return -ENODEV;
	}

	dev_info->sample_clk = devm_clk_get(&pdev->dev, "sample_clk");
	if (IS_ERR(dev_info->sample_clk)) {
		pr_err("[%s] get sample_clk error\n", __func__);
		return -ENODEV;
	}

	if (!fpga_flag) {	/*When fpga mode, no need to set sample clock to 60MHz */
		ret = clk_set_rate(dev_info->sample_clk, 60000000);
		if (ret) {
			pr_err("[%s] set sample_clk error\n", __func__);
			return -ENODEV;
		}
	}
	dev_info->sample_clk_rate = clk_get_rate(dev_info->sample_clk);
	pr_err("[%s] sample_clk is %lu\n", __func__, dev_info->sample_clk_rate);

	dev_info->perf_supply = devm_regulator_get(&pdev->dev, "perf-power");
	if (IS_ERR(dev_info->perf_supply)) {
		pr_err("[%s] get perf-power-supply error\n", __func__);
		return -ENODEV;
	}

	ret = fake_of_get_perfstat_attribute(np, dev_info);
	if (ret < 0) {
		pr_err("[%s] get hisilicon dts fail\n", __func__);
		return -ENOENT;
	}

	for (i = 0; i < PERF_PORT_NUM; i++) {
		pr_debug("[%s] %s\n", __func__, master_name[i]);
		if (!strncmp("", master_name[i], strlen(master_name[i]) + 1))
			continue;

		if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i)))
			continue;

		pr_debug("[%s] get %s-supply\n", __func__, master_name[i]);
		dev_info->master_supply[i] =
		    devm_regulator_get(&pdev->dev, master_name[i]);
		if (IS_ERR(dev_info->master_supply[i])) {
			pr_err("[%s] get %s-supply error\n", __func__,
			       master_name[i]);
			return -ENODEV;
		}
	}

	ret = perf_pmu_register(&perf_stat_pmu, "HiPERFSTAT", PERF_TYPE_RAW);
	if (ret < 0) {
		pr_err("[%s] register perf pmu fail\n", __func__);
		return -ENODEV;
	}

	INIT_DELAYED_WORK(&dev_info->hs_record_data_work,
			  perfstat_record_sample_data);
	init_completion(&perf_comp);
	mutex_init(&perfstat_transaction_mutex);
	is_probe_comp = true;
	spin_lock_init(&dev_info->synclock);
	wake_lock_init(&dev_info->wakelock, WAKE_LOCK_SUSPEND,
		       "perf-stat-wakelock");
	dev_info->status = PERF_TASK_DONE;

	pr_err("================[hisi perf probe e]================\n");

	return 0;
}

static int perfstat_remove(struct platform_device *pdev)
{
	return 0;
}

static struct perf_event *create_perf_event(int sample_period,
					    unsigned long sample_port,
					    int sample_time, int event_id)
{
	struct perf_event *event;
	if (sample_period <= 0) {
		pr_err("[%s] sample_period is negative: %d\n", __func__,
		       sample_period);
		goto err;
	}
	if (sample_port >= 1 << 16) {
		pr_err("[%s] sample_port is out of range: %ld\n", __func__,
		       sample_port);
		goto err;
	}
	if (sample_time < 0 || sample_time >= 1 << 16) {
		pr_err("[%s] sample_time is out of range: %d\n", __func__,
		       sample_time);
		goto err;
	}
	event = kmalloc(sizeof(struct perf_event), GFP_KERNEL);
	if (NULL == event)
		goto err;

	event->attr.type = PERF_TYPE_RAW;
	event->attr.sample_period = sample_period;
	event->attr.config =
	    (u64) sample_port + ((u64) sample_time << 16) +
	    ((u64) event_id << 32) + ((u64) 8 << 60);
	return event;

err:
	return NULL;
}

int perfstat_start_sampling(int sample_period, unsigned long sample_port,
			    int sample_time, int event_id)
{
	struct perf_event *event;
	int ret;
	struct perfstat_dev_info *dev_info = perfstat_info;
	pr_err("[%s] perfstat_start_sampling begin.\n", __func__);
	ret = -ENOENT;
	if (false == is_probe_comp || NULL == dev_info) {
		pr_err("[%s] perfstat is not intialized", __func__);
		goto out_err;
	}

	if (sample_period <= 0) {
		pr_err("[%s] sample_period is negative: %d\n", __func__,
		       sample_period);
		goto out_err;
	}
	if (sample_port >= 1 << 16) {
		pr_err("[%s] sample_port is out of range: %ld\n", __func__,
		       sample_port);
		goto out_err;
	}
	if (sample_time < 0 || sample_time >= 1 << 16) {
		pr_err("[%s] sample_time is out of range: %d\n", __func__,
		       sample_time);
		goto out_err;
	}
	if (!
	    (event_id == PERF_SAMPLE_HIGHSPEED
	     || event_id == PERF_SAMPLE_HSCYCLE)) {
		pr_err("[%s] Wrong sample type: %d", __func__, event_id);
		goto out_err;
	}

	event =
	    create_perf_event(sample_period, sample_port, sample_time,
			      event_id);
	if (NULL == event) {
		pr_err("[%s] creating perf_event fails.\n", __func__);
		goto out_err;
	}

	ret = perfstat_event_init(event);

	if (ret < 0) {
		pr_err("[%s] perfstat init fails.\n", __func__);
		ret = -ENOENT;
		goto event_err;
	}

	ret = perfstat_add(event, 0);

	kfree(event);
	event = NULL;
	pr_err("[%s] perfstat_start_sampling end.\n", __func__);
	return ret;

event_err:
	if (NULL != event) {
		kfree(event);
		event = NULL;
	}
out_err:
	pr_err("[%s] perfstat_start_sampling fails.\n", __func__);
	return ret;
}
EXPORT_SYMBOL_GPL(perfstat_start_sampling);

int perfstat_stop_sampling(void)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	pr_err("[%s] perfstat_stop_sampling begin.\n", __func__);
	if (false == is_probe_comp || NULL == dev_info) {
		pr_err("[%s] perfstat is not intialized.", __func__);
		return -1;
	}
	if (PERF_TASK_DONE == dev_info->status) {
		pr_err("[%s] perfstat is not running.\n", __func__);
		return -1;
	}
	perfstat_del(NULL, 0);
	perfstat_event_destroy(NULL);
	pr_err("[%s] perfstat_stop_sampling end.\n", __func__);
	return 0;
}
EXPORT_SYMBOL_GPL(perfstat_stop_sampling);

static struct platform_driver perfstat_driver = {
	.driver = {
		   .name = "HiPERFSTAT",
		   .owner = THIS_MODULE,
		   .of_match_table = of_perfstat_match_tbl,
		   },
	.probe = perfstat_probe,
	.remove = perfstat_remove,
};

static __init int perfstat_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&perfstat_driver);
	if (ret) {
		pr_err("[%s] platform_driver_register failed %d\n",
		       __func__, ret);
	}

	return ret;
}

static void __exit perfstat_exit(void)
{
	platform_driver_unregister(&perfstat_driver);
}

module_init(perfstat_init);
module_exit(perfstat_exit);
