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
#include <soc_acpu_baseaddr_interface.h>
#include <soc_crgperiph_interface.h>
#include "hisi_perf_stat64.h"
#include <linux/atomic.h>

static char *master_name_hi3660[PERF_PORT_NUM] = { "perf-dsssubsys0",	/*0:dss0 */
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
	"",			/*15:usbotg */
	"",
	"",
	"",
	"",			/*19:cci3 */
	"",			/*20:cci4 */
	"",			/*21:dmss1 */
	"",			/*22:dmss0 */
	"",
	"",
	"",			/*25:dmc a */
	"",			/*26:dmc c */
	"",			/*27:dmc c */
	"",			/*28:dmc d */
	"",			/*29:reserve */
	"",			/*30:reserve */
	""			/*31:reserve */
};

static char **master_name;

struct perfstat_dev_info {
	struct resource *res;
	struct perf_event *event_bk;	/*backup when user creat a perf_event, needed when overflow called */
	struct clk *sample_clk;
	struct regulator *perf_supply;
	struct regulator *master_supply[PERF_PORT_NUM];

	struct wake_lock wakelock;
	spinlock_t synclock;	/*sync perf_interrupt and perf_del */

	int status;		/*perf_status flag, when it is set rest, interrupt returns directly */
	int irq;
	unsigned long sample_clk_rate;

/* hisilicon perf attibute get from dts
 event_id    : hisilicon perf event_id, when a evnet is initialized,
		we deal with the perf_event only if the evend_id matches ours.
 per_data_sz : hisilicon perf per data size,
		perf_add use it to count the per_size,
		per_size = sample_numer * per_data_sz + data_head_size.
 per_int_size  : when sampling, we should notice the user to copy the data,
		so every per_int_size we send a notice, it means we should
		config perf to generate a (list-done)interrupt every per_int_size */
	int event_id;
	int per_data_sz;
	int per_int_size;
	int sample_per_sz;
	int sprt;
	int vldmsk_of_sprt;
	struct delayed_work hs_record_data_work;	/*Record Data work in HighSpeed Mode */

/*We report the sample data in each (list-done)interrupt,
  of course we should know the data start address & size.
  The fisrt start address of data is virt_addr, once a interrupt
  comes, we report PAGE_SIZE*pages_u data, then the cur_page_n += pages_u,
  so we could know the next data start address according to the cur_page_n,
  however, when cur_page_n beyonds the total page numbers(pages_n),
  it becomes zero again.
  */
	int pages_n;
	void *virt_addr;

/*perf generates interrupt by analyzing the perf_list_descriptors,
  we config a serial of descriptors in a continuous address, and
  tell perf the first descriptor's address*/
	perf_list_descriptor *list;
	struct page **pages;
};

static struct perfstat_dev_info *perfstat_info;
static void __iomem *perfstat_base;
static void __iomem *pericrg_base;
static bool first_data = true;
static unsigned long sample_time;
static bool perf_file_saved;	/* default value is false */
struct completion perf_comp;
static atomic_t is_recording = ATOMIC_INIT(0);
static unsigned int suggest_clk = 60000000;

static struct of_device_id of_perfstat_match_tbl[] = {
	{
	 .compatible = "hisilicon,hi3660-perfstat-driver",
	 .data = master_name_hi3660,
	 },
	{ /* end */ }
};

#define perfstat_reg_read(reg_addr)  \
	(*(volatile int *)((char *)perfstat_base + reg_addr))
#define perfstat_reg_write(reg_addr, reg_value) \
	(*(volatile int *)((char *)perfstat_base + reg_addr) = reg_value)

static void perfstat_reset_en(void)
{
	writel(1 << SOC_CRGPERIPH_PERRSTEN0_ip_rst_perf_stat_START,
	       SOC_CRGPERIPH_PERRSTEN0_ADDR(pericrg_base));
	pr_err("[%s]\n", __func__);
}

static void perfstat_reset_dis(void)
{
	writel(1 << SOC_CRGPERIPH_PERRSTDIS0_ip_rst_perf_stat_START,
	       SOC_CRGPERIPH_PERRSTDIS0_ADDR(pericrg_base));
	pr_err("[%s]\n", __func__);
}

static void perfstat_cci_gtclk_bypass(void)
{
	writel(1 << 28, SOC_CRGPERIPH_CCI400_CTRL1_ADDR(pericrg_base));
	pr_err("[%s]\n", __func__);
}

static void perfstat_dmc_gtclk_bypass(void)
{
	writel(1 << 30, SOC_CRGPERIPH_PEREN11_ADDR(pericrg_base));
	pr_err("[%s]\n", __func__);
}

static void perfstat_set_sample_cnt(int cnt)
{
	perfstat_reg_write(PERF_SAMPCNT, cnt);
}

static void perfstat_set_sample_period(int usec)
{
	int value;
	struct perfstat_dev_info *dev_info = perfstat_info;

	value = usec * (int)(dev_info->sample_clk_rate / 1000000);
	pr_err("[%s] sample_clk_rate is 0x%llx\n", __func__,
	       dev_info->sample_clk_rate);
	perfstat_set_sample_cnt(value);
}

static void perfstat_set_sample_num(int times)
{
	perfstat_reg_write(PERF_SAMPNUM, times);
}

static void perfstat_set_sample_port(int port)
{
	perfstat_reg_write(PERF_SAMPPORT, port);
}

static void perfstat_set_addr_mode(int mode)
{
	perfstat_reg_write(PERF_ADDRMODE, mode);
}

static int perfstat_set_seq_mode_addr(u64 addr)
{
	if (!PERF_IS_ALIGNED(addr, 32)) {
		pr_err("[%s] 64 bytes align needed\n", __func__);
		return PERF_ERROR;
	}

	perfstat_reg_write(PERF_SEQADDR_L, (u32) addr);
	perfstat_reg_write(PERF_SEQADDR_H, (u32) (addr >> 32));

	return PERF_OK;
}

static int perfstat_set_seq_mode_len(int len)
{
	if (!PERF_IS_ALIGNED(len, 32)) {
		pr_err("[%s] 32 bytes align needed\n", __func__);
		return PERF_ERROR;
	}

	perfstat_reg_write(PERF_SEQLEN, len);

	return PERF_OK;
}

static int perfstat_set_list_mode_addr(u64 addr)
{
	if (!PERF_IS_ALIGNED(addr, 8)) {
		pr_err("[%s] 8 bytes align needed\n", __func__);
		return PERF_ERROR;
	}

	perfstat_reg_write(PERF_LISTADDR_L, (u32) addr);
	perfstat_reg_write(PERF_LISTADDR_H, (u32) (addr >> 32));

	return PERF_OK;
}

static void perfstat_set_timeout_cnt(int cnt)
{
	perfstat_reg_write(PERF_OVERTIMECNT, cnt);
}

static void perfstat_set_timeout_duration(int msec)
{
	int value;
	struct perfstat_dev_info *dev_info = perfstat_info;

	value = msec * (int)(dev_info->sample_clk_rate / 1000);
	perfstat_set_timeout_cnt(value);
}

static void perfstat_set_monitor_reset(void)
{
	perfstat_reg_write(PERF_MONITORRST, 0x1);
}

static void perfstat_trigger_sample_start(void)
{
	perfstat_reg_write(PERF_SAMPSTART, 0x1);
}

static void perfstat_trigger_sample_stop(void)
{
	perfstat_reg_write(PERF_SAMPSTOP, 0x1);
}

static void perfstat_enable_interrupt(int type)
{
	int value;

	value = perfstat_reg_read(PERF_INTEN);
	value |= type;
	perfstat_reg_write(PERF_INTEN, value);
}

static void perfstat_disable_interrupt(int type)
{
	int value;

	value = perfstat_reg_read(PERF_INTEN);
	value &= ~type;
	perfstat_reg_write(PERF_INTEN, value);
}

static void perfstat_clear_interrupt(int type)
{
	perfstat_reg_write(PERF_INTCLR, type);
}

static int perfstat_get_masked_int_stat(void)
{
	return perfstat_reg_read(PERF_INTMASKSTAT);
}

static int perfstat_get_cur_sample_cnt(void)
{
	return perfstat_reg_read(PERF_CURSAMPCNT);
}

static u64 perfstat_get_cur_data_addr(void)
{
	u64 val_l, val_h, val;
	val_l = perfstat_reg_read(PERF_CURSAMPADDR_L);
	val_h = perfstat_reg_read(PERF_CURSAMPADDR_H);
	val = (val_h << 32) | (val_l & 0xffffffff);
	return val;
}

static u64 perfstat_get_cur_list_addr(void)
{
	u64 val_l, val_h, val;
	val_l = perfstat_reg_read(PERF_LASTDESCADDR_L);
	val_h = perfstat_reg_read(PERF_LASTDESCADDR_H);
	val = (val_h << 32) | (val_l & 0xffffffff);
	return val;
}

static int perfstat_get_fifo_status(void)
{
	return perfstat_reg_read(PERF_DBGFIFOFULL);
}

static int perfstat_get_block_port(void)
{
	return perfstat_reg_read(PERF_DBGBLOCK);
}

static u64 perfstat_get_list_mode_addr(void)
{
	u64 val;

	val = perfstat_reg_read(PERF_LISTADDR_H);
	val |= (val << 32) + perfstat_reg_read(PERF_LISTADDR_L);
	return val;
}

static int perfstat_get_reset_cnt(void)
{
	return perfstat_reg_read(PERF_RSTCNT);
}

static int perfstat_get_is_sampling(void)
{
	return perfstat_reg_read(PERF_SAMPSTART);
}

static void perfstat_debug_info_show(void)
{
	int cur_samp_cnt, dbg_fifo_stat, dbg_block_port;
	u64 cur_data_addr, cur_list_addr;

	cur_samp_cnt = perfstat_get_cur_sample_cnt();
	cur_data_addr = perfstat_get_cur_data_addr();
	cur_list_addr = perfstat_get_cur_list_addr();
	dbg_fifo_stat = perfstat_get_fifo_status();
	dbg_block_port = perfstat_get_block_port();

	pr_err("[%s]CurSampCnt   : 0x%x\n", __func__, cur_samp_cnt);
	pr_err("[%s]CurDataAddr  : 0x%llx\n", __func__, cur_data_addr);
	pr_err("[%s]CurListAddr  : 0x%llx\n", __func__, cur_list_addr);
	pr_err("[%s]DbgFIFOStat  : 0x%x\n", __func__, dbg_fifo_stat);
	pr_err("[%s]DbgBlockPort : 0x%x\n", __func__, dbg_block_port);

	return;
}

static void perfstat_list_done_handler(void)
{
	pr_err("[%s]perfstat list done.\n", __func__);
	perfstat_debug_info_show();

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

	if (!perf_file_saved && !atomic_read(&is_recording)) {
		pr_err("%s: save perf data...\n", __func__);
		schedule_delayed_work(&dev_info->hs_record_data_work, 0);
	}
	return;
}

static void perfstat_list_error_handler(void)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	u64 val;
	perf_list_descriptor *list_cfg;

	pr_err("[%s]perf list error\n", __func__);
	perfstat_debug_info_show();

	val = perfstat_get_list_mode_addr();
	pr_err("[%s]list addr inReg is 0x%llx.\n", __func__, val);
	list_cfg = dev_info->list;
	if (!list_cfg)
		pr_err("[%s]list addr inSof is null.\n", __func__);
	else
		pr_err("[%s]list addr inSof is 0x%llx.\n", __func__,
		       (u64) __virt_to_phys(list_cfg));

	return;
}

static void perfstat_port_overtime_handler(void)
{
	pr_err("[%s]perf port overtime\n", __func__);
	perfstat_debug_info_show();
}

static irqreturn_t perfstat_interrupt_handler(int irq, void *data)
{
	int val;
	struct perfstat_dev_info *dev_info = (struct perfstat_dev_info *)data;

	spin_lock(&dev_info->synclock);
	if (PERF_IS_REST == dev_info->status) {
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
	if (modem_noc_idleack & BIT(3)) {
		ret = PERF_ERROR;
	}

	iounmap(pmctrl_base);
	pmctrl_base = NULL;
	return ret;
}

static int perfstat_master_is_valid(unsigned long *sprt)
{
	int i;
	struct perfstat_dev_info *dev_info = perfstat_info;

	pr_err("[%s]port is 0x%x\n", __func__, (int)*sprt);

	for (i = 0; i < PERF_PORT_NUM; i++) {
		if (*sprt & PERF_PORT_BIT(i)) {
			if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i))) {
				pr_err("[%s] (%d)%s this port is not valid!\n",
				       __func__, i, master_name[i]);
				*sprt &= (~PERF_PORT_BIT(i));	/* clear this port */
			}
		}
	}

	/* If no master is powered up, not need to start perfstat. */
	if (0 == *sprt) {
		pr_err("[%s]no master is valid\n", __func__);
		return PERF_ERROR;
	}

	pr_err("[%s]port is 0x%x\n", __func__, (int)*sprt);
	return PERF_OK;
}

/**
* Judge if the master is powerup and
* only monitor the powerup ones.
**/
static int perfstat_master_is_powerup(unsigned long *sprt)
{
	int i, ret = PERF_OK;
	struct perfstat_dev_info *dev_info = perfstat_info;

	pr_err("[%s]port is 0x%x\n", __func__, (int)*sprt);

	for (i = 0; i < PERF_PORT_NUM; i++) {
		if (*sprt & PERF_PORT_BIT(i)) {
			pr_err("[%s] %s-supply\n", __func__, master_name[i]);
			if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i))) {	/*if master is not valid, goto next master */
				pr_err("[%s] %s-supply is not valid!\n",
				       __func__, master_name[i]);
				*sprt &= ~PERF_PORT_BIT(i);
				continue;
			}
			if ((PERF_PORT_MODEM0 == i) || (PERF_PORT_MODEM1 == i)) {
				ret = perfstat_is_modem_powerup();
				if (ret != PERF_OK) {
					pr_err("[%s] modem-supply is not enabled\n",
					     __func__);
					*sprt &= ~(PERF_PORT_BIT(PERF_PORT_MODEM0) |
					      PERF_PORT_BIT(PERF_PORT_MODEM1));
				}
				pr_err("[%s] %s-supply is modem\n", __func__,
				       master_name[i]);
				continue;
			}
			if ((PERF_PORT_CCI0 == i) || (PERF_PORT_CCI1 == i)
			    || (PERF_PORT_CCI3 == i) || (PERF_PORT_CCI4 == i)) {
				perfstat_cci_gtclk_bypass();
				perfstat_dmc_gtclk_bypass();
			}

			if (!strncmp
			    ("", master_name[i], strlen(master_name[i]) + 1)) {
				pr_err("[%s] %s-supply is null\n", __func__,
				       master_name[i]);
				continue;
			}
			ret = regulator_is_enabled(dev_info->master_supply[i]);
			pr_err("[%s] %s-supply regulator enable\n", __func__,
			       master_name[i]);
			if (!ret) {
				pr_err("[%s] %s-supply is not enabled\n",
				       __func__, master_name[i]);
				/* *sprt &= ~PERF_PORT_BIT(i); */
			}
		}
	}

	/* If no master is powered up, not need to start perfstat. */
	if (0 == *sprt) {
		pr_err("[%s]no master is powerup\n", __func__);
		return PERF_ERROR;
	}

	pr_err("[%s]port is 0x%x\n", __func__, (int)*sprt);
	return PERF_OK;
}

static void perfstat_record_sample_data(struct work_struct *work)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	unsigned long fs;
	long fd = 0;
	int ret = 0;
	u64 cur_list_addr, list_addr, cur_data_addr;
	void *start;
	int size, offset;
	int size_l = 0, size_h = 0;
	int page_idx, i;
	int sample_total_size, addr_mod;

	if (!atomic_add_unless(&is_recording, 1, 1)) {
		pr_err("[%s] is recording, failed to record.\n", __func__);
		return;
	}

	pr_err("[%s]perf sample done\n", __func__);
	perfstat_debug_info_show();
	if (!dev_info->list) {
		pr_err("[%s]no list exits\n", __func__);
		return;
	}

	start = dev_info->virt_addr;
	size = PAGE_SIZE * dev_info->pages_n;
	/*invalid data buffer to be copied */
	__dma_map_area((const void *)start, size, DMA_FROM_DEVICE);

	sample_total_size =
	    dev_info->sample_per_sz * perfstat_get_cur_sample_cnt();
	pr_err("[%s]sample_total_size is 0x%x.\n", __func__,
	       sample_total_size);
	pr_err("[%s]sample_per_sz is 0x%x,perfstat_get_cur_sample_cnt() is 0x%x.\n",
	     __func__, dev_info->sample_per_sz,
	     perfstat_get_cur_sample_cnt());
	pr_err("[%s]size is 0x%x, pages_n is 0x%x.\n", __func__, size,
	       dev_info->pages_n);
	if (sample_total_size > PAGE_SIZE * dev_info->pages_n) {
		/*find out the current page_idx in pages */
		cur_list_addr = perfstat_get_cur_list_addr();
		cur_data_addr = perfstat_get_cur_data_addr();
		list_addr = __virt_to_phys(dev_info->list);

		pr_err("[%s] cur_list_addr is 0x%llx.\n", __func__,
		       cur_list_addr);
		pr_err("[%s] cur_data_addr is 0x%llx.\n", __func__,
		       cur_data_addr);
		pr_err("[%s] list_addr is 0x%llx.\n", __func__, list_addr);
		for (i = 0; i < dev_info->pages_n; i++) {
			if (list_addr == cur_list_addr)
				break;
			list_addr = list_addr + sizeof(perf_list_descriptor);
		}
		pr_err("[%s] cur_list_addr is 0x%llx.\n", __func__,
		       cur_list_addr);
		pr_err("[%s] cur_data_addr is 0x%llx.\n", __func__,
		       cur_data_addr);
		pr_err("[%s] list_addr is 0x%llx.\n", __func__, list_addr);
		if (unlikely(dev_info->pages_n == i)) {
			pr_err("[%s]no list addr matched,dev_info->pagns_n is 0x%x \n",
			     __func__, dev_info->pages_n);
			return;
		} else {
			page_idx = i;
		}
		/*count the data start_addr & size */
		addr_mod = (dev_info->pages_n * PAGE_SIZE) % dev_info->sample_per_sz +
		    bitmap_weight((const unsigned long *)&(dev_info->sprt),
				  4 * sizeof((dev_info->sprt))) * 0x20;
		offset = cur_data_addr - dev_info->list[page_idx].bit_config.address;
		start = (void *)((char *)(dev_info->virt_addr) +
			     PAGE_SIZE * page_idx + offset + addr_mod);
		size_l = PAGE_SIZE * (dev_info->pages_n - page_idx) - offset -
		    addr_mod;
		size_h = PAGE_SIZE * page_idx + offset + addr_mod;
		pr_err("[%s] end\n", __func__);
	}

	fs = get_fs();
	set_fs(KERNEL_DS);
	fd = sys_open(PERF_HIGHSPEED_DATA_PATH, O_CREAT | O_WRONLY | O_TRUNC,
		      0660);
	if (fd < 0) {
		pr_err("[%s]open file failed, ret is %lu.\n", __func__, fd);
		set_fs(fs);
		goto record_err;
	}

	/*write time info */
	ret = sys_write(fd, (const char *)&sample_time, sizeof(sample_time));
	if (ret < 0) {
		pr_err("[%s]write file failed, ret is %d.\n", __func__, ret);
		set_fs(fs);
		goto record_err;
	}

	if (sample_total_size > PAGE_SIZE * dev_info->pages_n) {
		/*write perfstat raw data */
		ret = sys_write(fd, start, size_l);
		if (ret < 0) {
			pr_err("[%s]write file failed, ret is %d.\n", __func__,
			       ret);
			set_fs(fs);
			goto record_err;
		}
		/*write perfstat raw data */
		ret = sys_write(fd, dev_info->virt_addr, size_h);
		if (ret < 0) {
			pr_err("[%s]write file failed, ret is %d.\n", __func__,
			       ret);
			set_fs(fs);
			goto record_err;
		}
	} else {
		/*write perfstat raw data */
		ret = sys_write(fd, start, size);
		if (ret < 0) {
			pr_err("[%s]write file failed, ret is %d.\n", __func__,
			       ret);
			set_fs(fs);
			goto record_err;
		}
	}

	ret = sys_fsync(fd);
	if (ret < 0) {
		pr_err("[%s]sys_fsync failed, ret is %d\n", __func__, ret);
	}

	ret = sys_close(fd);
	if (ret < 0) {
		pr_err("[%s]sys_close failed, ret is %d\n", __func__, ret);
		set_fs(fs);
		goto record_err;
	}

	set_fs(fs);
	perf_file_saved = true;
	complete(&perf_comp);
	pr_err("[%s]perf data saved complete!\n", __func__);

record_err:
	atomic_dec(&is_recording);
}

static void perfstat_event_destroy(struct perf_event *event)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	struct page **pages;
	int i;

	if (perfstat_get_is_sampling()) {
		perfstat_trigger_sample_stop();
	}

	wait_for_completion(&perf_comp);

	pages = dev_info->pages;
	vunmap((const void *)dev_info->virt_addr);
	for (i = 0; i < dev_info->pages_n; i++) {
		__free_pages(pages[i], 0);
	}

	kfree(dev_info->list);
	kfree(dev_info->pages);
	dev_info->list = NULL;
	dev_info->pages = NULL;

	perfstat_reset_en();
	first_data = true;
	perf_file_saved = false;
	dev_info->event_bk = NULL;
	dev_info->virt_addr = NULL;

	spin_lock(&dev_info->synclock);
	dev_info->status = PERF_IS_REST;
	spin_unlock(&dev_info->synclock);

	return;
}

static int perfstat_event_init(struct perf_event *bp)
{
	int event_id;
	struct perfstat_dev_info *dev_info = perfstat_info;
	int sprd;
	unsigned long sprt;
	int spn;
	int page_n;
	signed int i = 0;
	int ret;
	struct page **pages = NULL;
	perf_list_descriptor *list_cfg = NULL;
	u64 list_head_phyaddr;
	u64 phy_addr;

	perfstat_reset_dis();
	clk_enable(dev_info->sample_clk);

	ret = perfstat_check_ready();
	if (ret < 0) {
		pr_err("[%s]perfstat is not ready\n", __func__);
		goto perf_supply_err;
	}

	if (bp->attr.type != PERF_TYPE_RAW)
		goto perf_supply_err;

	event_id = (int)(bp->attr.config >> 32);
	if (event_id != dev_info->event_id)
		goto perf_supply_err;

	bp->attr.sample_type = PERF_SAMPLE_RAW;
	bp->attr.mmap = 0;
	bp->attr.comm = 0;
	bp->attr.task = 0;
	bp->destroy = perfstat_event_destroy;
	bp->attr.disabled = 0;
	bp->state = PERF_EVENT_STATE_INACTIVE;

	pr_err("==============[hisi perf prepare +]================\n");
	/*count buffer size to store data,then figure out
	   the pages size needed, and also the page size
	   reported once a interrupt */
	sprd = bp->attr.sample_period & 0xffffffff;
	sprt = bp->attr.config & PERF_PORT_ALL;

	ret = perfstat_master_is_valid(&sprt);
	if (PERF_OK != ret) {
		pr_err("[%s]no master is valid!\n", __func__);
		goto perf_supply_err;
	}

	ret = perfstat_master_is_powerup(&sprt);
	if (PERF_OK != ret) {
		pr_err("[%s]no master is powered up!\n", __func__);
		goto perf_supply_err;
	}

	if (dev_info->status != PERF_IS_REST) {
		pr_err("[%s] Perf sampleing, please wait for it finished!\n",
		       __func__);
		goto perf_supply_err;
	}

	spn = bitmap_weight((const unsigned long *)&sprt, 4 * sizeof(sprt));
	dev_info->sample_per_sz =
	    (spn * dev_info->per_data_sz) + sizeof(perf_sample_data_head) +
	    sizeof(perf_sample_data_end);
	pr_err("[%s] spn is 0x%x,dev_info->sample_per_sz is 0x%x \n", __func__,
	       spn, dev_info->sample_per_sz);
	pr_err("[%s] sprt is 0x%lx,dev_info->per_data_sz is 0x%x \n", __func__,
	       sprt, dev_info->per_data_sz);
	pr_err("[%s] perf_sample_data_head size is 0x%lx,perf_sample_data_end sz is 0lx%x \n",
	     __func__, sizeof(perf_sample_data_head),
	     sizeof(perf_sample_data_end));

	page_n = PERF_MALLOC_PAGES_100M;
	pages = kzalloc((page_n * sizeof(struct page *)), GFP_KERNEL | GFP_DMA);
	if (!pages) {
		pr_err("[%s] cannot allocate pages ptr buffer\n", __func__);
		goto err;
	}

	dev_info->pages = pages;
	dev_info->pages_n = page_n;
	dev_info->sprt = (int)sprt;

	pr_err("[%s] port   : 0x%x\n", __func__, (int)sprt);
	pr_err("[%s] period : %dus\n", __func__, sprd);
	pr_err("[%s] page_n  : %d\n", __func__, page_n);

	list_cfg = kzalloc(((page_n + 1) * sizeof(perf_list_descriptor)),
		    GFP_KERNEL | GFP_DMA);
	pr_info("[%s]  kzalloc list_cfg is 0x%llx\n", __func__, (u64) list_cfg);
	if (!list_cfg) {
		pr_err("[%s] cannot allocate list_cfg buffer\n", __func__);
		goto err;
	}
	dev_info->list = list_cfg;
	list_head_phyaddr = (u64) __virt_to_phys(list_cfg);
	pr_info("[%s] list_head_phyaddr is 0x%llx\n", __func__,
		list_head_phyaddr);

	for (i = 0; i < page_n; i++) {
		pages[i] = alloc_page(GFP_KERNEL);
		if (!pages[i])
			goto err;
		phy_addr = (u64) __virt_to_phys(page_address(pages[i]));
		list_cfg[i].value.value0 = PERF_LIST_CFG_NORMAL;
		list_cfg[i].bit_config.address = phy_addr;
		list_cfg[i].bit_config.length = PAGE_SIZE;
	}
	/*last descriptor is a link to the head */
	list_cfg[page_n].value.value0 = PERF_LIST_CFG_LINK;
	list_cfg[page_n].bit_config.address = list_head_phyaddr;
	/*flush list_cfg into ddr */
	__dma_map_area((const void *)list_cfg,
		       ((page_n + 1) * sizeof(perf_list_descriptor)),
		       DMA_TO_DEVICE);

	/*map pages to a continuous virtual address */
	dev_info->virt_addr = vmap(pages, page_n, VM_MAP, PAGE_KERNEL);

	if (!dev_info->virt_addr) {
		pr_err("[%s] vmap pages error\n", __func__);
		goto err;
	}

	memset(dev_info->virt_addr, 0, page_n * PAGE_SIZE);
	__dma_map_area((const void *)dev_info->virt_addr, (page_n * PAGE_SIZE),
		       DMA_FROM_DEVICE);

	pr_info("[%s] vmap is %p\n", __func__, dev_info->virt_addr);

	perfstat_set_sample_period(sprd);
	perfstat_set_sample_port((int)sprt);
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

	pr_err("==============[hisi perf prepare -]================\n");

	dev_info->event_bk = bp;

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
	perfstat_reset_en();
	return -ENOENT;
}

static int perfstat_add(struct perf_event *bp, int flags)
{
	struct perfstat_dev_info *dev_info = perfstat_info;

	wake_lock(&dev_info->wakelock);

	dev_info->status = PERF_IS_WORK;

	sample_time = hisi_getcurtime();
	pr_err("[%s] sample time is %lu\n", __func__, sample_time);
	pr_info("[%s][hisi perf start sample...]\n", __func__);
	perfstat_trigger_sample_start();

	return 0;
}

static void perfstat_del(struct perf_event *bp, int flags)
{
	struct perfstat_dev_info *dev_info = perfstat_info;

	pr_info("[%s][hisi perf stop sample]\n", __func__);
	perfstat_trigger_sample_stop();

	pr_err("==============[hisi perf finish +]================\n");
	perfstat_debug_info_show();
	pr_err("==============[hisi perf finish -]================\n");

	wake_unlock(&dev_info->wakelock);

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

	ret = of_property_read_u32(np, "hisilicon,perf-event-id",
				 &dev_info->event_id);
	if (ret < 0) {
		pr_err("[%s] cannot get perf-event-id\n", __func__);
		return -ENOENT;
	}

	ret = of_property_read_u32(np, "hisilicon,per-int-size",
				 &dev_info->per_int_size);
	if (ret < 0) {
		pr_err("[%s] cannot get per-int-size\n", __func__);
		return -ENOENT;
	}

	ret = of_property_read_u32(np, "hisilicon,per-data-size",
				 &dev_info->per_data_sz);
	if (ret < 0) {
		pr_err("[%s] cannot get per-data-size\n", __func__);
		return -ENOENT;
	}

	ret = of_property_read_u32(np, "hisilicon,vldmsk-of-sprt",
				 &dev_info->vldmsk_of_sprt);
	if (ret < 0) {
		pr_err("[%s] cannot get vldmsk-of-sprt\n", __func__);
		return -ENOENT;
	}

	ret = of_property_read_u32(np, "suggest_clk", &suggest_clk);
	if (ret < 0) {
		pr_err("[%s] cannot get suggest_clk\n", __func__);
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
		printk("NOT FOUND device node 'hisilicon,hisifb'!\n");
		return -ENXIO;
	}
	ret = of_property_read_u32(np, "fpga_flag", &fpga_flag);
	if (ret) {
		printk("failed to get fpga_flag resource.\n");
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
		pr_err("[%s]: mismatch of perf_stat driver \n\r", __func__);
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

	pericrg_base = ioremap_wc(SOC_ACPU_PERI_CRG_BASE_ADDR, 0x2000);

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

	ret = fake_of_get_perfstat_attribute(np, dev_info);
	if (ret < 0) {
		pr_err("[%s] get hisilicon dts fail\n", __func__);
		return -ENOENT;
	}

	dev_info->sample_clk = devm_clk_get(&pdev->dev, "sample_clk");
	if (IS_ERR(dev_info->sample_clk)) {
		pr_err("[%s] get sample_clk error\n", __func__);
		return -ENODEV;
	}

	if (!fpga_flag) {	/*When fpga mode, no need to set sample clock to 60MHz */
		ret = clk_set_rate(dev_info->sample_clk, suggest_clk);
		if (ret) {
			pr_err("[%s] set sample_clk error\n", __func__);
			return -ENODEV;
		}
	}
	dev_info->sample_clk_rate = clk_get_rate(dev_info->sample_clk);
	pr_err("[%s] sample_clk is %lu\n", __func__, dev_info->sample_clk_rate);
	ret = fake_of_get_perfstat_attribute(np, dev_info);
	if (ret < 0) {
		pr_err("[%s] get hisilicon dts fail\n", __func__);
		return -ENOENT;
	}

	for (i = 0; i < PERF_PORT_NUM; i++) {
		pr_err("[%s][%d] %s\n", __func__, i, master_name[i]);
		if (!strncmp("", master_name[i], strlen(master_name[i]) + 1)) {
			continue;
		}
		if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i))) {
			continue;
		}
		pr_err("[%s] get %s-supply\n", __func__, master_name[i]);
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

	spin_lock_init(&dev_info->synclock);
	wake_lock_init(&dev_info->wakelock, WAKE_LOCK_SUSPEND,
		       "perf-stat-wakelock");
	dev_info->status = PERF_IS_REST;

	pr_err("================[hisi perf probe e]================\n");

	return 0;
}

static int perfstat_remove(struct platform_device *pdev)
{
	return 0;
}

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

/*sc:sample cnt, sn:sample num, sp:sample port, al:actual len*/
void test_seq_addr_mode(u32 sc, u32 sn, u32 sp, u32 al)
{
#define SAMPLE_DATA_SIZE_SEQ  0x4000	/*16K */

	static void *sample_data_addr;
	static u64 phy_addr;
	static u32 flag;
	s32 ret;
	struct perfstat_dev_info *dev_info;

	printk("sc: 0x%x, sn: 0x%x, sp: 0x%x, lm: 0x%x\n", sc, sn, sp, al);
	dev_info = perfstat_info;

	perfstat_reset_dis();
	dev_info->status = PERF_IS_WORK;

	if (!flag) {
		sample_data_addr = kmalloc(SAMPLE_DATA_SIZE_SEQ, GFP_KERNEL);
		if (!sample_data_addr) {
			printk(KERN_ERR "[%s]malloc sample data area fail.\n",
			       __func__);
			return;
		}
		phy_addr = (u64) __virt_to_phys(sample_data_addr);
		flag = 1;
	}
	printk(KERN_ERR "[%s]vir addr is %p.\n", __func__,
	       sample_data_addr);
	printk(KERN_ERR "[%s]phy addr is 0x%llx.\n", __func__, phy_addr);

	perfstat_set_sample_period(sc);
	perfstat_set_sample_num(sn);
	perfstat_set_sample_port(sp);
	perfstat_set_addr_mode(PERF_SEQ_ADDR_MODE);

	ret = perfstat_set_seq_mode_addr(phy_addr);
	if (PERF_ERROR == ret) {
		return;
	}

	ret = perfstat_set_seq_mode_len(al);
	if (PERF_ERROR == ret) {
		return;
	}

	perfstat_clear_interrupt(PERF_INT_ALL);
	perfstat_disable_interrupt(PERF_INT_ALL);
	perfstat_enable_interrupt(PERF_INT_SAMP_DONE | PERF_INT_OVER_TIME);
	perfstat_set_timeout_duration(200);

	perfstat_trigger_sample_start();

	return;
}

void test_list_addr_mode(u32 sc, u32 sn, u32 sp, u32 lm)
{
#define LIST_DATA_SIZE  0x200
#define LIST_NUM        0x2	/*just test, only 2 */
#define LIST_CFG_NORMAL 0x25ULL
#define LIST_CFG_LINK   0x35ULL
#define LIST_CFG_END_ERROR   0x22ULL	/*list end bit set to 1 */
#define LIST_CFG_VALID_ERROR   0x20ULL	/*list valid bit set to 0 */

	perf_list_descriptor *list_desc;
	u64 phy_list_head_addr;
	perf_list_descriptor temp;
	u32 index;
	void *list_data_addr;
	u64 phy_addr;
	s32 ret;
	struct perfstat_dev_info *dev_info;

	printk("sc: 0x%x, sn: 0x%x, sp: 0x%x, lm: 0x%x\n", sc, sn, sp, lm);
	dev_info = perfstat_info;

	perfstat_reset_dis();

	temp.value.value0 = LIST_CFG_NORMAL;
	temp.bit_config.length = LIST_DATA_SIZE;

	list_desc = (perf_list_descriptor *)
	    kmalloc((LIST_NUM * sizeof(perf_list_descriptor)),
		    GFP_DMA | GFP_KERNEL);
	phy_list_head_addr = (u64) __virt_to_phys(list_desc);
	printk(KERN_ERR "[%s]phy_list_head_addr is 0x%llx.\n", __func__,
	       phy_list_head_addr);
	ret = perfstat_set_list_mode_addr(phy_list_head_addr);
	if (PERF_ERROR == ret) {
		return;
	}

	if (lm == 1) {		/*limited list mode */
		for (index = 0; index < LIST_NUM; index++) {
			list_data_addr = kzalloc(LIST_DATA_SIZE, GFP_KERNEL);
			if (!list_data_addr) {
				printk(KERN_ERR "[%s]malloc list[%d] fail.\n",
				       __func__, index);
				return;
			}
			phy_addr = (u32) __virt_to_phys(list_data_addr);
			printk(KERN_ERR "[%s]phyaddr[%d] is 0x%llx\n",
			       __func__, index, phy_addr);

			temp.bit_config.address = phy_addr;
			list_desc[index] = temp;
		}
	} else if (lm == 2) {	/*cycled list mode */
		for (index = 0; index < (LIST_NUM - 1); index++) {
			list_data_addr = kmalloc(LIST_DATA_SIZE, GFP_KERNEL);
			if (!list_data_addr) {
				printk(KERN_ERR "[%s]malloc list[%d] fail.\n",
				       __func__, index);
				return;
			}
			phy_addr = (u64) __virt_to_phys(list_data_addr);

			temp.bit_config.address = phy_addr;
			list_desc[index] = temp;
		}

		/*last descriptor is a linker to the head descriptor */
		temp.value.value0 = LIST_CFG_LINK;
		temp.bit_config.address = phy_list_head_addr;
		list_desc[LIST_NUM - 1] = temp;
	} else if (lm == 3) {	/*LIST_CFG_END_ERROR */
		dev_info->status = PERF_IS_WORK;
		temp.value.value0 = LIST_CFG_END_ERROR;
		for (index = 0; index < LIST_NUM; index++) {
			list_data_addr = kzalloc(LIST_DATA_SIZE, GFP_KERNEL);
			if (!list_data_addr) {
				printk(KERN_ERR "[%s]malloc list[%d] fail.\n",
				       __func__, index);
				return;
			}
			phy_addr = (u64) __virt_to_phys(list_data_addr);
			printk(KERN_ERR "[%s]phyaddr[%d] is 0x%llx\n",
			       __func__, index, phy_addr);

			temp.bit_config.address = phy_addr;
			list_desc[index] = temp;
		}
	} else if (lm == 4) {	/*LIST_CFG_VALID_ERROR */
		dev_info->status = PERF_IS_WORK;
		temp.value.value0 = LIST_CFG_VALID_ERROR;
		for (index = 0; index < LIST_NUM; index++) {
			list_data_addr = kzalloc(LIST_DATA_SIZE, GFP_KERNEL);
			if (!list_data_addr) {
				printk(KERN_ERR "[%s]malloc list[%d] fail.\n",
				       __func__, index);
				return;
			}
			phy_addr = (u64) __virt_to_phys(list_data_addr);
			printk(KERN_ERR "[%s]phyaddr[%d] is 0x%llx\n",
			       __func__, index, phy_addr);

			temp.bit_config.address = phy_addr;
			list_desc[index] = temp;
		}
	} else if (lm == 5) {	/*cycled list mode */
		dev_info->status = PERF_IS_WORK;
		for (index = 0; index < (LIST_NUM - 1); index++) {
			list_data_addr = kmalloc(LIST_DATA_SIZE, GFP_KERNEL);
			if (!list_data_addr) {
				printk(KERN_ERR "[%s]malloc list[%d] fail.\n",
				       __func__, index);
				return;
			}
			phy_addr = (u64) __virt_to_phys(list_data_addr);

			temp.bit_config.address = phy_addr;
			list_desc[index] = temp;
		}

		/*last descriptor is a linker to the head descriptor */
		temp.value.value0 = PERF_LIST_CFG_INT;
		temp.bit_config.address = phy_list_head_addr;
		list_desc[LIST_NUM - 1] = temp;
	}

	perfstat_set_sample_period(sc);
	perfstat_set_sample_num(sn);
	perfstat_set_sample_port(sp);
	perfstat_set_addr_mode(PERF_LIST_ADDR_MODE);

	perfstat_clear_interrupt(PERF_INT_ALL);
	perfstat_enable_interrupt(PERF_INT_ALL);
	perfstat_set_timeout_duration(200);

	flush_cache_all();

	perfstat_trigger_sample_start();

	return;
}

void test_perfstat_stop(void)
{
	perfstat_trigger_sample_stop();
}

void test_perfstat_powerdonw(void)
{
	perfstat_reset_en();
}
