#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/uaccess.h>
#include <linux/clk.h>
#include <linux/bitops.h>
#include <linux/dma-mapping.h>
#include <soc_ddrc_qosb_interface.h>
#include <soc_dmss_interface.h>
#include <soc_acpu_baseaddr_interface.h>
#include <soc_ddrc_dmc_interface.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>
#include <global_ddr_map.h>
#include "hisi_ddr_ddrcflux.h"
#include "../../atfdriver/atfdriver.h"

/*lint -e438 -e514 -e550 -e715 -e749 -e754 -e774 -e818 -e835 -e838 -e845*/

typedef struct hisi_bw_timer {
	spinlock_t	lock;
	void __iomem	*base;
	struct clk	*clk;
	struct clk	*pclk;
	int		irq;
	int		irq_per_cpu;
} BwTimer;

struct ddrc_flux_device {
	spinlock_t	lock;
	void __iomem	*ddrflux_base;
	void __iomem	*dmss_base;
	void __iomem	*qosb_base[2];
	void __iomem	*dmc_base[4];
	void __iomem	*flux_en_va;
	void __iomem	*dramtype_va;
	void __iomem	*flux_pull_va;
	void __iomem	*flux_staid_va;
	dma_addr_t      flux_en_dma_pa;
	dma_addr_t      dramtype_dma_pa;
	dma_addr_t      flux_pull_dma_pa;
	dma_addr_t      flux_staid_pa;
	u32		katf_data_len;
	BwTimer		*ddrc_flux_timer;
	int		dram_type;
	struct clk	*ddrc_freq_clk;
	void __iomem	*sctrl;
	slice_info	slice;
};

struct ddrflux_pull {
	unsigned int	addr;
	unsigned int	offset;
	unsigned int	byte_len;
	const char	*head;
};

enum DDRMODE {
	reserved = 0,
	LPDDR,
	LPDDR2,
	LPDDR3,
	DDR,
	DDR2,
	DDR3,
	DDR4,
	LPDDR4,
};
enum DDRC_BASE {
	DMSS = 0,
	QOSB0,
	QOSB1,
	DMC00,
	DMC01,
	DMC10,
	DMC11,
};
static unsigned int	count;
struct ddrc_flux_device	*dfdev = NULL;
static u32 usr[12] = {0};
static u32 flag = 0;
#define VIRT(ADDR, n)      		(ioremap(ADDR, PAGE_ALIGN(SZ_4K*(n))))
/*#define MAX_STATISTIC_CYCLE			20000000*/
#define MIN_STATISTIC_INTERVAL_UNSEC		100
#define MIN_STATISTIC_INTERVAL_SEC		1000
#define MAX_DMSS_REG_NUM			33
#define MAX_QOSB_REG_NUM			10
#define MAX_DMC_REG_NUM				80
/*#define MAX_SLICE_LEN				4*/
#define IRQ_CPU_CORE				3
#define MAX_FLUX_REG_NUM		((MAX_QOSB_REG_NUM + MAX_DMC_REG_NUM + MAX_DMSS_REG_NUM))
#define BIT_FLUX_STAT_WR_EN		SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_wr_en_START
#define BIT_FLUX_STAT_RD_EN		SOC_DMSS_ASI_FLUX_STAT_CTRL_flux_stat_rd_en_START
#define BIT_QOSB_PERF_EN		SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_en_START
#define BIT_DMC_EN		SOC_DDRC_DMC_DDRC_CFG_STADAT_dat_stat_en_START
#define DDRC_DRAM_TYPE_MASK			0xF
#define MODULE_NAME				"ddr_flux_irq"
#define DEFAULT_SLICE_NAME			"test"
#define MAX_DMSS_ASI_BASE			10
/*lint -e750 -esym(750,*)*/
#define DDR_DMC_STD_ID_MASK_SHIFT		16
#define MAX_DDRFLUX_PULL_DATA			0x06400000 /*100M*/
#define NS_DDRC_TCLK				1000000000 /*1ns*/
#define TIMER_IRQ				91
#define SLICE_LEN				6
#define SCBAKDATA4				0x324
#define MASK_DDR				0xf00
#define DDRFLUX_PULL_OFFSET			0x0
#define DDRFLUX_EN_OFFSET			0x178
#define DDRFLUX_DRAMTYPE_OFFSET	0x180
#define DDRFLUX_STAID_OOFFSET		0x188

#define TIMER_LOAD		0x20			/* ACVR rw */
#define TIMER_VALUE		0x24			/* ACVR ro */
#define TIMER_CTRL		0x28			/* ACVR rw */
#define TIMER_INTCLR		0x2c			/* ACVR wo */
#define TIMER_RIS		0x30			/*  CVR ro */
#define TIMER_MIS		0x34			/*  CVR ro */
#define TIMER_BGLOAD		0x38			/*  CVR rw */
#define TIMER_CTRL_ONESHOT	(1 << 0)		/*  CVR */
#define TIMER_CTRL_32BIT	(1 << 1)		/*  CVR */
#define TIMER_CTRL_IE		(1 << 5)		/*   VR */
#define TIMER_CTRL_PERIODIC	(1 << 6)		/* ACVR */
#define TIMER_CTRL_ENABLE	(1 << 7)		/* ACVR */
/*lint -e750 +esym(750,*)*/
#define BW_TIMER_DEFAULT_LOAD			0xFFFFFFFF
#define MAX_DATA_OF_32BIT			0xFFFFFFFF

struct ddrflux_data {
	char		slice[SLICE_LEN];
	u64 		ddrc_time;
	u32 		ddr_tclk_ns;
	u32		ddrflux_data[MAX_FLUX_REG_NUM];
};
struct ddrflux_data	*ddrc_datas = NULL;
static void dmss_flux_enable_ctrl(int en);
static void qosbuf_flux_enable_ctrl(int en);
static void dmc_flux_enable_ctrl(int en);
struct dentry *ddrc_flux_dir;
struct dentry *flux_range;
static int stop;
static void hisi_bw_timer_set_time(unsigned int time)
{
	unsigned long ctrl, flags;

	spin_lock_irqsave(&dfdev->ddrc_flux_timer->lock, flags);

	ctrl = readl(dfdev->ddrc_flux_timer->base + TIMER_CTRL);
	/*first disable timer*/
	ctrl &= (~TIMER_CTRL_ENABLE);
	pr_debug("[%s] ctrl=%ld,TIMER_CTRL_ENABLE=%d,%d,=========\n", __func__, ctrl, TIMER_CTRL_ENABLE, __LINE__);
	writel(ctrl, dfdev->ddrc_flux_timer->base + TIMER_CTRL);
	/*set TIME_LOAD register together*/
	writel(time, dfdev->ddrc_flux_timer->base + TIMER_LOAD);
	writel(time, dfdev->ddrc_flux_timer->base + TIMER_BGLOAD);
	pr_debug("[%s] time=%d,%d,=========\n", __func__, time, __LINE__);
	/*then enable timer again*/
	ctrl |= (TIMER_CTRL_ENABLE | TIMER_CTRL_IE);
	writel(ctrl, dfdev->ddrc_flux_timer->base + TIMER_CTRL);

	spin_unlock_irqrestore(&dfdev->ddrc_flux_timer->lock, flags);
}

/*
*func: do timer initializtion
*set timer clk to 4.8MHz
*if mode is periodic and period is not the same as timer value, set bgload value
*set timer control: mode, 32bits, no prescale, interrupt enable, timer enable
*/
static void hisi_bw_timer_init_config(void)
{
	unsigned long flags, ctrl = 0;

	spin_lock_irqsave(&dfdev->ddrc_flux_timer->lock, flags);
	/*1. timer select 4.8M*/
	/*2. clear the interrupt */
	writel(1, dfdev->ddrc_flux_timer->base + TIMER_INTCLR);
	/*3. set timer5 control reg: 32bit, interrupt disable, timer_value,
	 oneshot mode and disable wakeup_timer*/
	ctrl = TIMER_CTRL_32BIT;
	writel(BW_TIMER_DEFAULT_LOAD, dfdev->ddrc_flux_timer->base + TIMER_LOAD);
	ctrl |= TIMER_CTRL_PERIODIC;
	writel(ctrl, dfdev->ddrc_flux_timer->base + TIMER_CTRL);

	spin_unlock_irqrestore(&dfdev->ddrc_flux_timer->lock, flags);
}

static void hisi_bw_timer_clk_disable(void)
{
	clk_disable_unprepare(dfdev->ddrc_flux_timer->clk);
}

static void hisi_bw_timer_disable(void)
{
	unsigned long ctrl, flags;

	spin_lock_irqsave(&dfdev->ddrc_flux_timer->lock, flags);
	ctrl = readl(dfdev->ddrc_flux_timer->base + TIMER_CTRL);
	ctrl &= ~(TIMER_CTRL_ENABLE | TIMER_CTRL_IE);
	writel(ctrl, dfdev->ddrc_flux_timer->base + TIMER_CTRL);
	spin_unlock_irqrestore(&dfdev->ddrc_flux_timer->lock, flags);

	/*hisi_bw_timer_clk_disable();*/
}

#define DDR_FLUX(_addr, _offset, _byte_len, _head) \
{                               \
	.addr = _addr, \
	.offset = _offset,\
	.byte_len    = _byte_len, \
	.head = _head,	\
}

/*lint -e665*/
static struct ddrflux_pull ddrflux_lookups[] = {
	 DDR_FLUX(DMSS , (0x164+0x800*(0)) ,  (1*4), "ASI_QOS_RDOSTD_ST_0,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(1)) ,  (1*4), "ASI_QOS_RDOSTD_ST_1,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(2)) ,  (1*4), "ASI_QOS_RDOSTD_ST_2,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(3)) ,  (1*4), "ASI_QOS_RDOSTD_ST_3,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(4)) ,  (1*4), "ASI_QOS_RDOSTD_ST_4,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(5)) ,  (1*4), "ASI_QOS_RDOSTD_ST_5,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(6)) ,  (1*4), "ASI_QOS_RDOSTD_ST_6,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(7)) ,  (1*4), "ASI_QOS_RDOSTD_ST_7,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(8)) ,  (1*4), "ASI_QOS_RDOSTD_ST_8,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(9)) ,  (1*4), "ASI_QOS_RDOSTD_ST_9,"),
	 DDR_FLUX(DMSS , (0x164+0x800*(10)) ,  (1*4), "ASI_QOS_RDOSTD_ST_10,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(0)) ,  (1*4), "ASI_FLUX_STAT_WR_0,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(1)) ,  (1*4), "ASI_FLUX_STAT_WR_1,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(2)) ,  (1*4), "ASI_FLUX_STAT_WR_2,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(3)) ,  (1*4), "ASI_FLUX_STAT_WR_3,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(4)) ,  (1*4), "ASI_FLUX_STAT_WR_4,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(5)) ,  (1*4), "ASI_FLUX_STAT_WR_5,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(6)) ,  (1*4), "ASI_FLUX_STAT_WR_6,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(7)) ,  (1*4), "ASI_FLUX_STAT_WR_7,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(8)) ,  (1*4), "ASI_FLUX_STAT_WR_8,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(9)) ,  (1*4), "ASI_FLUX_STAT_WR_9,"),
	 DDR_FLUX(DMSS , (0x178+0x800*(10)) , (1*4), "ASI_FLUX_STAT_WR_10,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(0)) ,  (1*4), "ASI_FLUX_STAT_RD_0,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(1)) ,  (1*4), "ASI_FLUX_STAT_RD_1,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(2)) ,  (1*4), "ASI_FLUX_STAT_RD_2,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(3)) ,  (1*4), "ASI_FLUX_STAT_RD_3,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(4)) ,  (1*4), "ASI_FLUX_STAT_RD_4,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(5)) ,  (1*4), "ASI_FLUX_STAT_RD_5,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(6)) ,  (1*4), "ASI_FLUX_STAT_RD_6,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(7)) ,  (1*4), "ASI_FLUX_STAT_RD_7,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(8)) ,  (1*4), "ASI_FLUX_STAT_RD_8,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(9)) ,  (1*4), "ASI_FLUX_STAT_RD_9,"),
	 DDR_FLUX(DMSS , (0x17c+0x800*(10)) , (1*4), "ASI_FLUX_STAT_RD_10,"),
	 DDR_FLUX(QOSB0 , 0x124, (1*4), "QOSB_CMD_SUM_0,"),
	 DDR_FLUX(QOSB0 , 0x180, (1*4), "QOSB_CMD_CNT_0,"),
	 DDR_FLUX(QOSB0 , 0x1e0, (1*4), "QOSB_OSTD_CNT_0,"),
	 DDR_FLUX(QOSB0 , 0x1e4, (1*4), "QOSB_WR_SUM_0,"),
	 DDR_FLUX(QOSB0 , 0x1e8, (1*4), "QOSB_RD_SUM_0,"),
	 DDR_FLUX(QOSB1 , 0x124, (1*4), "QOSB_CMD_SUM_1,"),
	 DDR_FLUX(QOSB1 , 0x180, (1*4), "QOSB_CMD_CNT_1,"),
	 DDR_FLUX(QOSB1 , 0x1e0, (1*4), "QOSB_OSTD_CNT_1,"),
	 DDR_FLUX(QOSB1 , 0x1e4, (1*4), "QOSB_WR_SUM_1,"),
	 DDR_FLUX(QOSB1 , 0x1e8, (1*4), "QOSB_RD_SUM_1,"),
	 DDR_FLUX(DMC00 , 0x380, (1*4), "DDRC_HIS_FLUX_WR_00,"),
	 DDR_FLUX(DMC00 , 0x384, (1*4), "DDRC_HIS_FLUX_RD_00,"),
	 DDR_FLUX(DMC00 , 0x388, (1*4), "DDRC_HIS_FLUX_WCMD_00,"),
	 DDR_FLUX(DMC00 , 0x38C, (1*4), "DDRC_HIS_FLUX_RCMD_00,"),
	 DDR_FLUX(DMC00 , 0x390, (1*4), "DDRC_HIS_FLUXID_WR_00,"),
	 DDR_FLUX(DMC00 , 0x394, (1*4), "DDRC_HIS_FLUXID_RD_00,"),
	 DDR_FLUX(DMC00 , 0x398, (1*4), "DDRC_HIS_FLUXID_WCMD_00,"),
	 DDR_FLUX(DMC00 , 0x39C, (1*4), "DDRC_HIS_FLUXID_RCMD_00,"),
	 DDR_FLUX(DMC00 , 0x3A0, (1*4), "DDRC_HIS_WLATCNT0_00,"),
	 DDR_FLUX(DMC00 , 0x3A4, (1*4), "DDRC_HIS_WLATCNT1_00,"),
	 DDR_FLUX(DMC00 , 0x3A8, (1*4), "DDRC_HIS_RLATCNT0_00,"),
	 DDR_FLUX(DMC00 , 0x3AC, (1*4), "DDRC_HIS_RLATCNT1_00,"),
	 DDR_FLUX(DMC00 , 0x3B0, (1*4), "DDRC_HIS_INHERE_RLAT_CNT_00,"),
	 DDR_FLUX(DMC00 , 0x3B8, (1*4), "DDRC_HIS_CMD_SUM_00,"),
	 DDR_FLUX(DMC00 , 0x3BC, (1*4), "DDRC_HIS_DAT_SUM_00,"),
	 DDR_FLUX(DMC00 , 0x3C0, (1*4), "DDRC_HIS_PRE_CMD_00,"),
	 DDR_FLUX(DMC00 , 0x3C4, (1*4), "DDRC_HIS_ACT_CMD_00,"),
	 DDR_FLUX(DMC00 , 0x3C8, (1*4), "DDRC_HIS_BNK_CHG_00,"),
	 DDR_FLUX(DMC00 , 0x3CC, (1*4), "DDRC_HIS_RNK_CHG_00,"),
	 DDR_FLUX(DMC00 , 0x3D0, (1*4), "DDRC_HIS_RW_CHG_00,"),
	 DDR_FLUX(DMC01 , 0x380, (1*4), "DDRC_HIS_FLUX_WR_01,"),
	 DDR_FLUX(DMC01 , 0x384, (1*4), "DDRC_HIS_FLUX_RD_01,"),
	 DDR_FLUX(DMC01 , 0x388, (1*4), "DDRC_HIS_FLUX_WCMD_01,"),
	 DDR_FLUX(DMC01 , 0x38C, (1*4), "DDRC_HIS_FLUX_RCMD_01,"),
	 DDR_FLUX(DMC01 , 0x390, (1*4), "DDRC_HIS_FLUXID_WR_01,"),
	 DDR_FLUX(DMC01 , 0x394, (1*4), "DDRC_HIS_FLUXID_RD_01,"),
	 DDR_FLUX(DMC01 , 0x398, (1*4), "DDRC_HIS_FLUXID_WCMD_01,"),
	 DDR_FLUX(DMC01 , 0x39C, (1*4), "DDRC_HIS_FLUXID_RCMD_01,"),
	 DDR_FLUX(DMC01 , 0x3A0, (1*4), "DDRC_HIS_WLATCNT0_01,"),
	 DDR_FLUX(DMC01 , 0x3A4, (1*4), "DDRC_HIS_WLATCNT1_01,"),
	 DDR_FLUX(DMC01 , 0x3A8, (1*4), "DDRC_HIS_RLATCNT0_01,"),
	 DDR_FLUX(DMC01 , 0x3AC, (1*4), "DDRC_HIS_RLATCNT1_01,"),
	 DDR_FLUX(DMC01 , 0x3B0, (1*4), "DDRC_HIS_INHERE_RLAT_CNT_01,"),
	 DDR_FLUX(DMC01 , 0x3B8, (1*4), "DDRC_HIS_CMD_SUM_01,"),
	 DDR_FLUX(DMC01 , 0x3BC, (1*4), "DDRC_HIS_DAT_SUM_01,"),
	 DDR_FLUX(DMC01 , 0x3C0, (1*4), "DDRC_HIS_PRE_CMD_01,"),
	 DDR_FLUX(DMC01 , 0x3C4, (1*4), "DDRC_HIS_ACT_CMD_01,"),
	 DDR_FLUX(DMC01 , 0x3C8, (1*4), "DDRC_HIS_BNK_CHG_01,"),
	 DDR_FLUX(DMC01 , 0x3CC, (1*4), "DDRC_HIS_RNK_CHG_01,"),
	 DDR_FLUX(DMC01 , 0x3D0, (1*4), "DDRC_HIS_RW_CHG_01,"),
	 DDR_FLUX(DMC10 , 0x380, (1*4), "DDRC_HIS_FLUX_WR_10,"),
	 DDR_FLUX(DMC10 , 0x384, (1*4), "DDRC_HIS_FLUX_RD_10,"),
	 DDR_FLUX(DMC10 , 0x388, (1*4), "DDRC_HIS_FLUX_WCMD_10,"),
	 DDR_FLUX(DMC10 , 0x38C, (1*4), "DDRC_HIS_FLUX_RCMD_10,"),
	 DDR_FLUX(DMC10 , 0x390, (1*4), "DDRC_HIS_FLUXID_WR_10,"),
	 DDR_FLUX(DMC10 , 0x394, (1*4), "DDRC_HIS_FLUXID_RD_10,"),
	 DDR_FLUX(DMC10 , 0x398, (1*4), "DDRC_HIS_FLUXID_WCMD_10,"),
	 DDR_FLUX(DMC10 , 0x39C, (1*4), "DDRC_HIS_FLUXID_RCMD_10,"),
	 DDR_FLUX(DMC10 , 0x3A0, (1*4), "DDRC_HIS_WLATCNT0_10,"),
	 DDR_FLUX(DMC10 , 0x3A4, (1*4), "DDRC_HIS_WLATCNT1_10,"),
	 DDR_FLUX(DMC10 , 0x3A8, (1*4), "DDRC_HIS_RLATCNT0_10,"),
	 DDR_FLUX(DMC10 , 0x3AC, (1*4), "DDRC_HIS_RLATCNT1_10,"),
	 DDR_FLUX(DMC10 , 0x3B0, (1*4), "DDRC_HIS_INHERE_RLAT_CNT_10,"),
	 DDR_FLUX(DMC10 , 0x3B8, (1*4), "DDRC_HIS_CMD_SUM_10,"),
	 DDR_FLUX(DMC10 , 0x3BC, (1*4), "DDRC_HIS_DAT_SUM_10,"),
	 DDR_FLUX(DMC10 , 0x3C0, (1*4), "DDRC_HIS_PRE_CMD_10,"),
	 DDR_FLUX(DMC10 , 0x3C4, (1*4), "DDRC_HIS_ACT_CMD_10,"),
	 DDR_FLUX(DMC10 , 0x3C8, (1*4), "DDRC_HIS_BNK_CHG_10,"),
	 DDR_FLUX(DMC10 , 0x3CC, (1*4), "DDRC_HIS_RNK_CHG_10,"),
	 DDR_FLUX(DMC10 , 0x3D0, (1*4), "DDRC_HIS_RW_CHG_10,"),
	 DDR_FLUX(DMC11 , 0x380, (1*4), "DDRC_HIS_FLUX_WR_11,"),
	 DDR_FLUX(DMC11 , 0x384, (1*4), "DDRC_HIS_FLUX_RD_11,"),
	 DDR_FLUX(DMC11 , 0x388, (1*4), "DDRC_HIS_FLUX_WCMD_11,"),
	 DDR_FLUX(DMC11 , 0x38C, (1*4), "DDRC_HIS_FLUX_RCMD_11,"),
	 DDR_FLUX(DMC11 , 0x390, (1*4), "DDRC_HIS_FLUXID_WR_11,"),
	 DDR_FLUX(DMC11 , 0x394, (1*4), "DDRC_HIS_FLUXID_RD_11,"),
	 DDR_FLUX(DMC11 , 0x398, (1*4), "DDRC_HIS_FLUXID_WCMD_11,"),
	 DDR_FLUX(DMC11 , 0x39C, (1*4), "DDRC_HIS_FLUXID_RCMD_11,"),
	 DDR_FLUX(DMC11 , 0x3A0, (1*4), "DDRC_HIS_WLATCNT0_11,"),
	 DDR_FLUX(DMC11 , 0x3A4, (1*4), "DDRC_HIS_WLATCNT1_11,"),
	 DDR_FLUX(DMC11 , 0x3A8, (1*4), "DDRC_HIS_RLATCNT0_11,"),
	 DDR_FLUX(DMC11 , 0x3AC, (1*4), "DDRC_HIS_RLATCNT1_11,"),
	 DDR_FLUX(DMC11 , 0x3B0, (1*4), "DDRC_HIS_INHERE_RLAT_CNT_11,"),
	 DDR_FLUX(DMC11 , 0x3B8, (1*4), "DDRC_HIS_CMD_SUM_11,"),
	 DDR_FLUX(DMC11 , 0x3BC, (1*4), "DDRC_HIS_DAT_SUM_11,"),
	 DDR_FLUX(DMC11 , 0x3C0, (1*4), "DDRC_HIS_PRE_CMD_11,"),
	 DDR_FLUX(DMC11 , 0x3C4, (1*4), "DDRC_HIS_ACT_CMD_11,"),
	 DDR_FLUX(DMC11 , 0x3C8, (1*4), "DDRC_HIS_BNK_CHG_11,"),
	 DDR_FLUX(DMC11 , 0x3CC, (1*4), "DDRC_HIS_RNK_CHG_11,"),
	 DDR_FLUX(DMC11 , 0x3D0, (1*4), "DDRC_HIS_RW_CHG_11\n"),
};
/*lint +e665*/

#define DDRFLUX_LIST_LEN      (int)(sizeof(ddrflux_lookups)/sizeof(ddrflux_lookups[0]))
void ddrc_flux_data_pull(void)
{
	int i, j = 0;
	void __iomem 	*base = NULL;

	if (!usr[ddrc_unsec_pass])
		return;
	ddrc_datas[count].ddrc_time = sched_clock();
	strncpy(ddrc_datas[count].slice, dfdev->slice.name, SLICE_LEN);
	ddrc_datas[count].slice[SLICE_LEN-1] = '\0';

	for (i = 0; i < DDRFLUX_LIST_LEN; i++) {
		switch (ddrflux_lookups[i].addr) {
		case DMSS:
			if (usr[dmss_enable])
				base = dfdev->dmss_base;
			break;
		case QOSB0:
			if (usr[qosbuf_enable])
				base = dfdev->qosb_base[0];
			break;
		case QOSB1:
			if (usr[qosbuf_enable])
				base = dfdev->qosb_base[1];
			break;
		case DMC00:
			if ((usr[dmcdata_enable] || usr[dmccmd_enable] || usr[dmclatency_enable])
								& usr[dmc_enable])
				base = dfdev->dmc_base[0];
			break;
		case DMC10:
			if ((usr[dmcdata_enable] || usr[dmccmd_enable] || usr[dmclatency_enable])
								& usr[dmc_enable])
				base = dfdev->dmc_base[1];
			break;
		case DMC01:
			if ((usr[dmcdata_enable] || usr[dmccmd_enable] || usr[dmclatency_enable])
								& usr[dmc_enable]) {
				if (LPDDR4 == dfdev->dram_type) {
					base = dfdev->dmc_base[2];
				} else {
					base = NULL;
				}
			}
			break;
		case DMC11:
			if ((usr[dmcdata_enable] || usr[dmccmd_enable] || usr[dmclatency_enable])
								& usr[dmc_enable]) {
				if (LPDDR4 == dfdev->dram_type) {
					base = dfdev->dmc_base[3];
				} else {
					base = NULL;
				}
			}
			break;
		default:
			pr_err("[%s]ddr mode error!", __func__);
		}
		if (NULL != base) {
			ddrc_datas[count].ddrflux_data[j] = readl(base + ddrflux_lookups[i].offset);
			base = NULL;
			j++;
		} else if (NULL == base) {
			ddrc_datas[count].ddrflux_data[j] = 0;
			j++;
		}
	}
}

static irqreturn_t hisi_bw_timer_interrupt(int irq, void *dev_id)
{
	int freq_index;
	if ((readl(dfdev->ddrc_flux_timer->base + TIMER_RIS)) & 0x1) {
		/* clear the interrupt */
		writel(1, dfdev->ddrc_flux_timer->base + TIMER_INTCLR);
		pr_debug("[%s] cnt =%d--\n", __func__, count);

		freq_index = readl(dfdev->sctrl + SCBAKDATA4);
		freq_index &= MASK_DDR;
		freq_index = freq_index >> 8;
		ddrc_datas[count].ddr_tclk_ns = freq_index;
		ddrc_datas[count].ddrc_time = sched_clock();
		if (!usr[ddrc_unsec_pass]) {
			atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID, dfdev->flux_pull_dma_pa,
					MAX_FLUX_REG_NUM * 4, ACCESS_REGISTER_FN_SUB_ID_DDR_FLUX_R);
			memcpy(ddrc_datas[count].ddrflux_data, (unsigned long *)dfdev->flux_pull_va, sizeof(ddrc_datas[count].ddrflux_data));
			strncpy(ddrc_datas[count].slice, dfdev->slice.name, SLICE_LEN);
			ddrc_datas[count].slice[SLICE_LEN-1] = '\0';
		} else {
			ddrc_flux_data_pull();
		}

		if (count < (usr[sum_time]/usr[interval]) - 1) {
			count++;
			stop = 0;
		} else if (count == (usr[sum_time]/usr[interval] - 1)) {
			pr_debug("[%s] cnt=%d,%d,+++++++++\n", __func__, count, __LINE__);
			hisi_bw_timer_disable();
			stop = 1;
			pr_debug("[%s] cnt=%d,%d,---------\n", __func__, count, __LINE__);
		}
	}

	return IRQ_HANDLED;
}

static int hisi_bw_timer_clk_enable(void)
{
	int ret = 0;
	ret = clk_prepare_enable(dfdev->ddrc_flux_timer->clk);
	if (ret)
		pr_err("clk prepare enable failed !%d\n", __LINE__);
	return ret;
}
/*
*func: used for wakeup on timer for S/R
*decs: set timer2 count value = (seconds*1000+milliseconds)*32.768 ms
*mode is used for user to set timer work in periodic or oneshot mode
*mode: 0 for periodic
*      1 for oneshot
*/
static void hisi_pm_bw_on_timer(unsigned int useconds)
{
	unsigned int set_time;
	unsigned int rate;
	unsigned int max_timing;

	if (!useconds) {
		pr_err("hisi_pm_bw_on_timer: input time error!\n");
		return;
	}
	/*time to be useconds format*/
	rate = clk_get_rate(dfdev->ddrc_flux_timer->clk);
	if (0 == rate) {
		pr_err("hisi_pm_bw_on_timer: clk_get_rate error!\n");
		return;
	}
	set_time = useconds * (rate * 10/1000000)/10;
	pr_debug("[%s]us=%d,rate=%d,settime=%d\n", __func__, useconds, rate, set_time);
	max_timing = (MAX_DATA_OF_32BIT / rate) * 1000000;
	pr_debug("[%s] set_time=%d,%d,=========\n", __func__, set_time, __LINE__);
	if (set_time > max_timing) {
		pr_err("hisi_pm_bw_on_timer: input timing overflow!\n");
		return;
	}
	/*enable clk*/
	if (hisi_bw_timer_clk_enable()) {
		return;
	}
	/*add for the case ICS4.0 system changed the timer clk to 6.5MHz
	here changed back to 4.8MHz.*/
	hisi_bw_timer_init_config();
	hisi_bw_timer_set_time(set_time);
}

int hisi_bw_timer_clk_is_ready(void)
{
	if (NULL == dfdev->ddrc_flux_timer->clk)
		return 1;
	return 0;
}

static int hisi_bw_timer_init(int irq_per_cpu)
{
	int ret = 0;

	if (hisi_bw_timer_clk_is_ready()) {
		pr_err("clk is not ready\n");
		ret = -EINVAL;
		goto err_clk_get;
	}
	ret = clk_set_rate(dfdev->ddrc_flux_timer->clk, 4800000);
	if (ret) {
		pr_err("[%s] set rate falied,%d\n", __func__, __LINE__);
		goto err_set_rate;
	}
	pr_debug("[%s] %d,rate=%ld=========\n", __func__, __LINE__, clk_get_rate(dfdev->ddrc_flux_timer->clk));
	if (hisi_bw_timer_clk_enable())
		goto err_clk_enable;
	/*do timer init configs: disable timer ,mask interrupt,
				clear interrupt and set clk to 32.768KHz*/
	hisi_bw_timer_init_config();
	/*register timer5 interrupt*/
	if (request_irq(dfdev->ddrc_flux_timer->irq, hisi_bw_timer_interrupt,
						IRQF_NO_SUSPEND, MODULE_NAME, NULL)) {
		pr_err("request irq for timer5 error\n");
		goto err_irq;
	}
	pr_debug("[%s] timerirq=%d,irq_per_cpu=%d ,%d\n", __func__, dfdev->ddrc_flux_timer->irq, irq_per_cpu, __LINE__);
	irq_set_affinity(dfdev->ddrc_flux_timer->irq, cpumask_of(irq_per_cpu));
	hisi_bw_timer_clk_disable();

	return ret;
err_irq:
	hisi_bw_timer_clk_disable();
err_clk_enable:
err_set_rate:
err_clk_get:
	return ret;
}

static int hisi_bw_timer_deinit(void)
{
	if (!dfdev->ddrc_flux_timer->clk)
		return -EINVAL;
	/*iounmap(dfdev->ddrc_flux_timer->base);*/
	free_irq(dfdev->ddrc_flux_timer->irq, NULL);

	return 0;
}

void ddrflux_info_cfg(unsigned int *info, unsigned int n)
{
	int i ;

	if (NULL == info)
		return;
	if (0 == usr[interval] || 0 == usr[sum_time]) {
		WARN_ON(1);
		return;
	}
	if (n < 12) {
		pr_err("ddrflux cfg infoe error!");
		return;
	}
	for (i = 0; i < ddrc_flux_max; i++)
		usr[i] = info[i];
}
EXPORT_SYMBOL(ddrflux_info_cfg);

void __ddrflux_init(void)
{
	unsigned long mem_size;
	int ret = 0;
	int i ;

	pr_info("[%s start]%d\n", __func__, __LINE__);
	if (WARN_ON(usr[interval] == 0)) {
		usr[interval] = 10000;
	}

	if (WARN_ON(usr[sum_time] == 0)) {
		usr[sum_time] = 500000;
	}
	if (WARN_ON(usr[interval] > usr[sum_time])) {
		pr_info("current interval > sum_time!\n");
		usr[sum_time] = usr[interval];
	}
	if (usr[ddrc_unsec_pass] == 0) {
		if (WARN_ON(usr[interval] < MIN_STATISTIC_INTERVAL_SEC)) {
			pr_info("under unsec interval can't too small!\n");
			usr[interval] = MIN_STATISTIC_INTERVAL_SEC;
			usr[sum_time] = usr[interval]*10;
		}
	}
	WARN_ON(usr[sum_time] > 20000000);
	mem_size = (usr[sum_time]/usr[interval]+1)*(sizeof(struct ddrflux_data));
	if (WARN_ON(mem_size > MAX_DDRFLUX_PULL_DATA))
		return;
	ddrc_datas = (struct ddrflux_data *)vmalloc(mem_size);
	if (!ddrc_datas) {
		pr_err("[%s] vmalloc size =%ld failed !%d\n", __func__, mem_size, __LINE__);
		ret = -ENOMEM;
		goto no_mem;
	}

	pr_err("[%s] sum=%d,interval=%d\n", __func__, usr[sum_time], usr[interval]);
	/*if ddr is secos */
	if (usr[ddrc_unsec_pass] == 0) {
		pr_err("Welcome enter sec arm-trustframeword!\n");
		/*dram type get*/
		(void)atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID, dfdev->dramtype_dma_pa,
					4, ACCESS_REGISTER_FN_SUB_ID_DDR_DRAM_R);
		dfdev->dram_type = *(u64 *)(dfdev->dramtype_va);
		pr_info("[%s] mask=0x%x ,dramtype=%d,%d\n", __func__, DDRC_DRAM_TYPE_MASK, dfdev->dram_type, __LINE__);
		/*ddrflux enable*/
		if (usr[dmss_enable])
			*((unsigned long *)dfdev->flux_en_va) |= BIT(0);
		if (usr[qosbuf_enable])
			*((unsigned long *)dfdev->flux_en_va) |= BIT(1);
		if (usr[dmc_enable])
			*((unsigned long *)dfdev->flux_en_va) |= BIT(2);
		if (usr[dmccmd_enable])
			*((unsigned long *)dfdev->flux_en_va) |= BIT(3);
		if (usr[dmcdata_enable])
			*((unsigned long *)dfdev->flux_en_va) |= BIT(4);
		if (usr[dmclatency_enable])
			*((unsigned long *)dfdev->flux_en_va) |= BIT(5);
		(void)atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID, dfdev->flux_en_dma_pa,
					2*4, ACCESS_REGISTER_FN_SUB_ID_DDR_FLUX_W);
		/*write sta_id sta_id_mask*/
		*((unsigned long *)dfdev->flux_staid_va) = usr[sta_id];
		(void)atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID, dfdev->flux_staid_pa,
					8*4, ACCESS_REGISTER_FN_SUB_ID_DDR_STDID_W);
		pr_err("[%s] sta_id=0x%x ,mask=%d,%d\n", __func__, usr[sta_id], usr[sta_id_mask], __LINE__);
	/*if ddr is unsecos */
	} else if (usr[ddrc_unsec_pass] == 1) {
		pr_info("Current pass is unsec kernel!\n");
		if (WARN_ON(usr[interval] < MIN_STATISTIC_INTERVAL_UNSEC)) {
			usr[interval] = MIN_STATISTIC_INTERVAL_UNSEC;
		}
		if (usr[dmss_enable]) {
			dmss_flux_enable_ctrl(1);
			if (!dfdev->dmss_base)
			    dfdev->dmss_base = VIRT(SOC_ACPU_DMSS_BASE_ADDR, 8);
			if (!dfdev->dmss_base)
				goto map_err;
		}
		if (usr[qosbuf_enable]) {
			qosbuf_flux_enable_ctrl(1);
			if (!dfdev->qosb_base[0])
			    dfdev->qosb_base[0] = VIRT(SOC_ACPU_DDRC_QOSB_0_BASE_ADDR, 1);
			if (!dfdev->qosb_base[0])
				goto map_err1;
			if (!dfdev->qosb_base[1])
			    dfdev->qosb_base[1] = VIRT(SOC_ACPU_DDRC_QOSB_1_BASE_ADDR, 1);
			if (!dfdev->qosb_base[1])
				goto map_err2;
		}

		dfdev->dram_type = readl(SOC_DDRC_DMC_DDRC_CFG_DDRMODE_ADDR
						(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		dfdev->dram_type &= DDRC_DRAM_TYPE_MASK;
		pr_info("[%s] mask=0x%x ,dramtype=%d,%d\n", __func__, DDRC_DRAM_TYPE_MASK, dfdev->dram_type, __LINE__);
		if (usr[dmc_enable]) {
			if (LPDDR4 == dfdev->dram_type || LPDDR3 == dfdev->dram_type) {
				if (!dfdev->dmc_base[0])
					dfdev->dmc_base[0] = VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1);
				if (!dfdev->dmc_base[0])
					goto map_err3;
				if (!dfdev->dmc_base[1])
					dfdev->dmc_base[1] = VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1);
				if (!dfdev->dmc_base[1])
					goto map_err4;
			}
			if (LPDDR4 == dfdev->dram_type) {
				if (!dfdev->dmc_base[2])
					dfdev->dmc_base[2] = VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1);
				if (!dfdev->dmc_base[2])
					goto map_err5;
				if (!dfdev->dmc_base[3])
					dfdev->dmc_base[3] = VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1);
				if (!dfdev->dmc_base[3])
					goto map_err6;
			}

			/*sta_id sta_id_mask*/
			if (LPDDR4 == dfdev->dram_type) {
				for (i = 0; i < 4; i++) {
					writel(usr[sta_id], SOC_DDRC_DMC_DDRC_CFG_STAID_ADDR(dfdev->dmc_base[i]));
					writel(usr[sta_id_mask], SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_ADDR(dfdev->dmc_base[i]));
				}
			} else if (dfdev->dram_type == LPDDR3) {
				for (i = 0; i < 2; i++) {
					writel(usr[sta_id], SOC_DDRC_DMC_DDRC_CFG_STAID_ADDR(dfdev->dmc_base[i]));
					writel(usr[sta_id_mask], SOC_DDRC_DMC_DDRC_CFG_STAIDMSK_ADDR(dfdev->dmc_base[i]));
				}
			} else {
				pr_err("[%s] unknow ddr type!!! line = %d\n", __func__, __LINE__);
			}
		}
	}

	if (usr[irq_affinity] > 7) {
		pr_err("[%s] input cpucore error!%d\n", __func__, __LINE__);
		usr[irq_affinity] = IRQ_CPU_CORE;
	}
	count = 0;
	hisi_bw_timer_init(usr[irq_affinity]);
	pr_info("[%s sucess]%d\n", __func__, __LINE__);
	return;
map_err6:
    if (dfdev->dmc_base[2]) {
	iounmap(dfdev->dmc_base[2]);
	dfdev->dmc_base[2] = NULL;
    }
map_err5:
    if (dfdev->dmc_base[1]) {
	iounmap(dfdev->dmc_base[1]);
	dfdev->dmc_base[1] = NULL;
    }
map_err4:
	if (dfdev->dmc_base[0]) {
		iounmap(dfdev->dmc_base[0]);
		dfdev->dmc_base[0] = NULL;
    }
map_err3:
    if (dfdev->qosb_base[1]) {
	iounmap(dfdev->qosb_base[1]);
	dfdev->qosb_base[1] = NULL;
    }
map_err2:
    if (dfdev->qosb_base[0]) {
	iounmap(dfdev->qosb_base[0]);
	dfdev->qosb_base[0] = NULL;
    }
map_err1:
    if (dfdev->dmss_base) {
	 iounmap(dfdev->dmss_base);
	dfdev->dmss_base = NULL;
    }
map_err:
    if (ddrc_datas)
	vfree(ddrc_datas);
	ddrc_datas = NULL;
no_mem:
	flag = 1;
	return;
}

static void __ddrflux_exit(void)
{
	if (ddrc_datas != NULL) {
		vfree(ddrc_datas);
		hisi_bw_timer_deinit();
		ddrc_datas = NULL;
	}
	if (usr[ddrc_unsec_pass] == 0) {
		if (usr[dmss_enable])
			*((unsigned long *)dfdev->flux_en_va) &= (~BIT(0));
		if (usr[qosbuf_enable])
			*((unsigned long *)dfdev->flux_en_va) &= (~BIT(1));
		if (usr[dmc_enable])
			*((unsigned long *)dfdev->flux_en_va) &= (~BIT(2));
		if (usr[dmccmd_enable])
			*((unsigned long *)dfdev->flux_en_va) &= (~BIT(3));
		if (usr[dmcdata_enable])
			*((unsigned long *)dfdev->flux_en_va) &= (~BIT(4));
		if (usr[dmclatency_enable])
			*((unsigned long *)dfdev->flux_en_va) &= (~BIT(5));
		(void)atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID, dfdev->flux_en_dma_pa,
					2*4, ACCESS_REGISTER_FN_SUB_ID_DDR_FLUX_W);
		pr_info("[%s]\n", __func__);
	} else {
		if (usr[dmss_enable]) {
			dmss_flux_enable_ctrl(0);
			#if 0
			iounmap(dfdev->dmss_base);
			#endif
		}
		if (usr[qosbuf_enable]) {
			qosbuf_flux_enable_ctrl(0);
			#if 0
			iounmap(dfdev->qosb_base[1]);
			iounmap(dfdev->qosb_base[0]);
			#endif
		}
		if (usr[dmc_enable] && (usr[dmccmd_enable]
						|| usr[dmcdata_enable]
						|| usr[dmclatency_enable])) {
			dmc_flux_enable_ctrl(0);
			#if 0
			if (LPDDR4 == dfdev->dram_type)
				for (i = 0; i < 4; i++)
					iounmap(dfdev->dmc_base[i]);
			if (LPDDR3 == dfdev->dram_type)
				for (i = 0; i < 2; i++)
					iounmap(dfdev->dmc_base[i]);
			#endif
		}
		pr_info("[%s]\n", __func__);
	}
}

void ddrflux_exit(void)
{
	__ddrflux_exit();
}
EXPORT_SYMBOL(ddrflux_exit);

void __ddrflux_start(void)
{
	__ddrflux_init();
	hisi_pm_bw_on_timer(usr[interval]);
}

void ddrflux_start(void)
{
	__ddrflux_start();
}
EXPORT_SYMBOL(ddrflux_start);

void __ddrflux_stop(void)
{
	if (!stop) {
		hisi_bw_timer_disable();
		hisi_bw_timer_deinit();
		pr_info("[%s] sucess!\n", __func__);
	} else {
		pr_info("[%s] ddrflux already take over!\n", __func__);
	}
}

void ddrflux_stop(void)
{
	__ddrflux_stop();
}
EXPORT_SYMBOL(ddrflux_stop);

void __ddrflux_view_point_insert(char *slice_v)
{
	if (NULL == slice_v)
		return;
	strncpy(dfdev->slice.name, slice_v, SLICE_LEN);/*[false alarm]*/
	dfdev->slice.name[SLICE_LEN-1] = '\0';
}

void ddrflux_view_point_insert(char *slice)
{
	if (NULL == slice) {
		pr_err("slice error!\n");
		return;
	}
	WARN_ON(SLICE_LEN <= strlen(slice));/*[false alarm]*/
	__ddrflux_view_point_insert(slice);
}
EXPORT_SYMBOL(ddrflux_view_point_insert);

static void *ddrflux_data_seq_start(struct seq_file *m, loff_t *pos)
{
	return (*pos >= count) ? NULL : pos;
}

static void *ddrflux_data_seq_next(struct seq_file *m, void *v, loff_t *pos)
{
	(*pos)++;
	return (*pos >= count) ? NULL : pos;
}

static void ddrflux_data_seq_stop(struct seq_file *m, void *v)
{
}

int ddr3freq[6] = {
	/* kHz*/
	120000,
	240000,
	360000,
	533000,
	800000,
	933000,
};
int ddr4freq[7] = {
	/* kHz*/
	120000,
	240000,
	360000,
	533000,
	667000,
	960000,
	1333000,
};
static int ddrflux_data_seq_show(struct seq_file *m, void *v)
{
	int i, len;
	u64 sBeginTime;
	unsigned long nsBeginTime;
	struct tm tm_rtc;

	i = *(loff_t *)v;
	if (i == 0) {
		seq_printf(m, "sta_id:%d,sta_id_mask:%d,dram_type:%s,interval:%dus\n",
			usr[sta_id], usr[sta_id_mask], ((dfdev->dram_type == LPDDR3) ? "LPDDR3" : "LPDDR4"), usr[interval]);
		seq_printf(m, "index,time,rtc_time,slice,ddrfreq(khz),");

		for (len = 0; len < DDRFLUX_LIST_LEN; len++)
			seq_printf(m, ddrflux_lookups[len].head);
	}

	if (ddrc_datas != NULL) {
		sBeginTime = ddrc_datas[i].ddrc_time;
		nsBeginTime = do_div(sBeginTime, 1000000000);
		time_to_tm((time_t)sBeginTime, 0, &tm_rtc);
		seq_printf(m, "%d,%05lu.%06lu,", i, (unsigned long)sBeginTime, nsBeginTime/1000);
		seq_printf(m, "[%lu:%.2d:%.2d %.2d:%.2d:%.2d],",
			1900 + tm_rtc.tm_year, tm_rtc.tm_mon + 1, tm_rtc.tm_mday,
			tm_rtc.tm_hour, tm_rtc.tm_min, tm_rtc.tm_sec);
		seq_printf(m, "%s,", ddrc_datas[i].slice);
		if (LPDDR3 == dfdev->dram_type)
			seq_printf(m, "%d,", ddr3freq[ddrc_datas[i].ddr_tclk_ns]);
		if (LPDDR4 == dfdev->dram_type)
			seq_printf(m, "%d,", ddr4freq[ddrc_datas[i].ddr_tclk_ns]);

		for (len = 0; len < MAX_FLUX_REG_NUM - 1; len++)
			seq_printf(m, "0x%08x,", ddrc_datas[i].ddrflux_data[len]);
		seq_printf(m, "0x%08x\n", ddrc_datas[i].ddrflux_data[len - 1]);
	}
	return 0;
}

static ssize_t
ddrflux_stop_store(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	__ddrflux_stop();
	return (ssize_t)cnt;
}

static ssize_t
ddrflux_start_store(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	char init[2] = {};

	if (NULL == ubuf || 0 == cnt) {
		pr_err("buf is null !\n");
		return -EINVAL;
	}
	if (cnt > sizeof(init)) {
		pr_err("input count larger! \n");
		return -ENOMEM;
	}
	/*copy init from user space.*/
	spin_lock(&dfdev->lock);
	if (copy_from_user(init, ubuf, cnt - 1)) {
		spin_unlock(&dfdev->lock);
		return (ssize_t)cnt;
	}
	spin_unlock(&dfdev->lock);
	if (WARN_ON(!strcmp(init, "0"))) {
		return (ssize_t)cnt;
	} else if (!strcmp(init, "1")) {
		if (!flag) {
			hisi_pm_bw_on_timer(usr[interval]);
			pr_info("[%s] sucess!\n", __func__);
		} else {
			pr_info("[%s] ddrflux init exception!\n", __func__);
		}
	} else {
		WARN_ON(1);
		pr_err("ubuf data must be 0 or 1!\n");
	}
	return (ssize_t)cnt;
}

static ssize_t
ddrflux_exit_store(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	__ddrflux_exit();
	return (ssize_t)cnt;
}

static void dmss_flux_enable_ctrl(int en)
{
	int asi_base;
	u32 val, ckg_byp = 0;

	if (!usr[ddrc_unsec_pass])
		return;
	if (en) {
		for (asi_base = 0; asi_base <= MAX_DMSS_ASI_BASE; asi_base++) {
			val = readl(SOC_DMSS_ASI_FLUX_STAT_CTRL_ADDR
					(VIRT(SOC_ACPU_DMSS_BASE_ADDR, 8), asi_base));
			val |= BIT(BIT_FLUX_STAT_RD_EN);
			val |= BIT(BIT_FLUX_STAT_WR_EN);
			writel(val, SOC_DMSS_ASI_FLUX_STAT_CTRL_ADDR
					(VIRT(SOC_ACPU_DMSS_BASE_ADDR, 8), asi_base));
		}
	} else {
		for (asi_base = 0; asi_base <= MAX_DMSS_ASI_BASE; asi_base++) {
			val = readl(SOC_DMSS_ASI_FLUX_STAT_CTRL_ADDR
					(VIRT(SOC_ACPU_DMSS_BASE_ADDR, 8), asi_base));
			val &= ~(BIT(BIT_FLUX_STAT_RD_EN));
			val &= ~(BIT(BIT_FLUX_STAT_WR_EN));
			writel(val, SOC_DMSS_ASI_FLUX_STAT_CTRL_ADDR
					(VIRT(SOC_ACPU_DMSS_BASE_ADDR, 8), asi_base));
			/*ckg_byp_asi SOC_DMSS_ASI_DYN_CKG_ADDR*/
			val = readl(SOC_DMSS_ASI_DYN_CKG_ADDR
					(VIRT(SOC_ACPU_DMSS_BASE_ADDR, 8), asi_base));
			ckg_byp = val;
			val |= BIT(SOC_DMSS_ASI_DYN_CKG_ckg_byp_asi_START);
			writel(val, SOC_DMSS_ASI_DYN_CKG_ADDR
					(VIRT(SOC_ACPU_DMSS_BASE_ADDR, 8), asi_base));
			writel(ckg_byp, SOC_DMSS_ASI_DYN_CKG_ADDR
					(VIRT(SOC_ACPU_DMSS_BASE_ADDR, 8), asi_base));
		}
	}
}

static void qosbuf_flux_enable_ctrl(int en)
{
	u32 val0, val1 = 0;

	if (!usr[ddrc_unsec_pass])
		return;
	if (en) {
		val0 = readl(SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR
					(VIRT(SOC_ACPU_DDRC_QOSB_0_BASE_ADDR, 1)));
		val1 = readl(SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR
					(VIRT(SOC_ACPU_DDRC_QOSB_1_BASE_ADDR, 1)));
		val0 |= BIT(BIT_QOSB_PERF_EN);
		val1 |= BIT(BIT_QOSB_PERF_EN);
		writel(val0, SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR
					(VIRT(SOC_ACPU_DDRC_QOSB_0_BASE_ADDR, 1)));
		writel(val1, SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR
					(VIRT(SOC_ACPU_DDRC_QOSB_1_BASE_ADDR, 1)));
	} else {
		val0 = readl(SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR
					(VIRT(SOC_ACPU_DDRC_QOSB_0_BASE_ADDR, 1)));
		val1 = readl(SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR
					(VIRT(SOC_ACPU_DDRC_QOSB_1_BASE_ADDR, 1)));
		val0 &= ~(BIT(BIT_QOSB_PERF_EN));
		val1 &= ~(BIT(BIT_QOSB_PERF_EN));
		writel(val0, SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR
					(VIRT(SOC_ACPU_DDRC_QOSB_0_BASE_ADDR, 1)));
		writel(val1, SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR
					(VIRT(SOC_ACPU_DDRC_QOSB_1_BASE_ADDR, 1)));
	}
}

static void dmc_flux_enable_ctrl(int en)
{
	u32 val00, val01, val10, val11 = 0;
	if (!usr[ddrc_unsec_pass])
		return;

	if (en) {
		/*DMC_0_0&DMC_1_0, offset 0x254, bit30 to 1*/
		val00 = readl(SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		val10 = readl(SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1)));
		val00 |= BIT(BIT_DMC_EN);
		val10 |= BIT(BIT_DMC_EN);
		writel(val00, SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		writel(val10, SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1)));

		/*DMC_0_0&DMC_1_0, offset 0x260, bit30 to 1*/
		val00 = readl(SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		val10 = readl(SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1)));
		val00 |= BIT(BIT_DMC_EN);
		val10 |= BIT(BIT_DMC_EN);
		writel(val00, SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		writel(val10, SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1)));
		if (LPDDR4 == dfdev->dram_type) {
			/*DMC_0_1&DMC_1_1, offset 0x254, bit30 to 1*/
			val01 = readl(SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1)));
			val11 = readl(SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1)));
			val01 |= BIT(BIT_DMC_EN);
			val11 |= BIT(BIT_DMC_EN);
			writel(val01, SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1)));
			writel(val11, SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1)));
			/*DMC_0_1&DMC_1_1, offset 0x260, bit30 to 1*/
			val01 = readl(SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1)));
			val11 = readl(SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1)));
			val01 |= BIT(BIT_DMC_EN);
			val11 |= BIT(BIT_DMC_EN);
			writel(val01, SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1)));
			writel(val11, SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1)));
		}
	} else {
		/*DMC_0_0&DMC_1_0, offset 0x254, bit30 to 0*/
		val00 = readl(SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		val10 = readl(SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1)));
		val00 &= ~(BIT(BIT_DMC_EN));
		val10 &= ~(BIT(BIT_DMC_EN));
		writel(val00, SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		writel(val10, SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1)));
		/*DMC_0_0&DMC_1_0, offset 0x260, bit30 to 0*/
		val00 = readl(SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		val10 = readl(SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1)));
		val00 &= ~(BIT(BIT_DMC_EN));
		val10 &= ~(BIT(BIT_DMC_EN));
		writel(val00, SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, 1)));
		writel(val10, SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
			(VIRT(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, 1)));
		if (LPDDR4 == dfdev->dram_type) {
			/*DMC_0_1&DMC_1_1, offset 0x254, bit30 to 0*/
			val01 = readl(SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1)));
			val11 = readl(SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1)));
			val01 &= ~(BIT(BIT_DMC_EN));
			val11 &= ~(BIT(BIT_DMC_EN));
			writel(val01, SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1)));
			writel(val11, SOC_DDRC_DMC_DDRC_CFG_STADAT_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1)));
			/*DMC_0_1&DMC_1_1, offset 0x260, bit30 to 0*/
			val01 = readl(SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1)));
			val11 = readl(SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
				(VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1)));
			val01 &= ~(BIT(BIT_DMC_EN));
			val11 &= ~(BIT(BIT_DMC_EN));
			writel(val01, SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
					(VIRT(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, 1)));
			writel(val11, SOC_DDRC_DMC_DDRC_CFG_STACMD_ADDR
					(VIRT(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, 1)));
		}
	}
}

static ssize_t
ddrflux_init_store(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	char init[2] = {0};

	if (NULL == ubuf || 0 == cnt) {
		pr_err("buf is null !\n");
		return -EINVAL;
	}
	if (cnt > sizeof(init)) {
		pr_err("input count larger! \n");
		return -ENOMEM;
	}
	spin_lock(&dfdev->lock);
	/*copy init from user space.*/
	if (copy_from_user(init, ubuf, cnt - 1)) {
		spin_unlock(&dfdev->lock);
		return (ssize_t)cnt;
	}
	spin_unlock(&dfdev->lock);
	if (WARN_ON(!strcmp(init, "0"))) {
		return (ssize_t)cnt;
	} else if (!strcmp(init, "1")) {
		__ddrflux_init();
	} else {
		WARN_ON(1);
		pr_err("ubuf data must be 0 or 1\n");
	}
	return (ssize_t)cnt;
}

static const struct seq_operations ddrflux_data_seq_ops = {
	.start = ddrflux_data_seq_start,
	.next  = ddrflux_data_seq_next,
	.stop  = ddrflux_data_seq_stop,
	.show  = ddrflux_data_seq_show
};

static int ddrflux_data_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &ddrflux_data_seq_ops);
}

static const struct file_operations ddrflux_data_fops = {
	.open	= ddrflux_data_open,
	.read	= seq_read,
	.llseek	= seq_lseek,
	.release = seq_release,
};

static int ddrflux_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

#define MODULE_STORE_DEFINE(func_name)					\
	static const struct file_operations func_name##_fops = {	\
	.open		= ddrflux_open,					\
	.read		= seq_read,					\
	.write		= func_name##_store,				\
	.llseek		= seq_lseek,					\
};
MODULE_STORE_DEFINE(ddrflux_init);
MODULE_STORE_DEFINE(ddrflux_exit);
MODULE_STORE_DEFINE(ddrflux_start);
MODULE_STORE_DEFINE(ddrflux_stop);

static int ddrc_flux_dir_init(void)
{
	ddrc_flux_dir = debugfs_create_dir("ddrflux", NULL);
	if (!ddrc_flux_dir)
		return -ENOMEM;
	flux_range = debugfs_create_dir("enable_range", ddrc_flux_dir);
	if (!flux_range)
		return -ENOMEM;
	#define PRIV_AUTH       (S_IRUSR|S_IWUSR|S_IRGRP)
	debugfs_create_u32("sta_id", PRIV_AUTH, ddrc_flux_dir,
							&usr[sta_id]);
	debugfs_create_u32("sta_id_mask", PRIV_AUTH, ddrc_flux_dir,
							&usr[sta_id_mask]);
	debugfs_create_u32("interval", PRIV_AUTH, ddrc_flux_dir,
							&usr[interval]);
	debugfs_create_u32("sum_time", PRIV_AUTH, ddrc_flux_dir,
							&usr[sum_time]);
	debugfs_create_u32("irq_affinity", PRIV_AUTH, ddrc_flux_dir,
							&usr[irq_affinity]);
	debugfs_create_u32("ddrc_unsec_pass", PRIV_AUTH, ddrc_flux_dir,
							&usr[ddrc_unsec_pass]);
	debugfs_create_u32("dmss_enable", PRIV_AUTH, flux_range,
							&usr[dmss_enable]);
	debugfs_create_u32("qosbuf_enable", PRIV_AUTH, flux_range,
							&usr[qosbuf_enable]);
	debugfs_create_u32("dmc_enable", PRIV_AUTH, flux_range,
							&usr[dmc_enable]);
	debugfs_create_u32("dmccmd_enable", PRIV_AUTH, flux_range,
							&usr[dmccmd_enable]);
	debugfs_create_u32("dmcdata_enable", PRIV_AUTH, flux_range,
							&usr[dmcdata_enable]);
	debugfs_create_u32("dmclatency_enable", PRIV_AUTH, flux_range,
							&usr[dmclatency_enable]);
	debugfs_create_file("ddrflux_init", PRIV_AUTH, ddrc_flux_dir, NULL,
							&ddrflux_init_fops);
	debugfs_create_file("ddrflux_exit", PRIV_AUTH, ddrc_flux_dir, NULL,
							&ddrflux_exit_fops);
	debugfs_create_file("ddrflux_start", PRIV_AUTH, ddrc_flux_dir, NULL,
							&ddrflux_start_fops);
	debugfs_create_file("ddrflux_stop", PRIV_AUTH, ddrc_flux_dir, NULL,
							&ddrflux_stop_fops);
	debugfs_create_file("ddrflux_data", S_IRUGO, ddrc_flux_dir, NULL,
							&ddrflux_data_fops);
	return 0;
}

static int ddrc_flux_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	int ret  = 0;
	u32 data[2] = {0};
	phys_addr_t bl31_smem_base = HISI_SUB_RESERVED_BL31_SHARE_MEM_PHYMEM_BASE;
	int i;

	if (!np) {
		pr_err("%s: %s %d, no dev node\n", MODULE_NAME, __func__, __LINE__);
		ret = -ENODEV;
		goto out;
	}

	pr_err("[%s] [%s]probe !\n", dev_name(&pdev->dev), np->name);
	dfdev = devm_kzalloc(&pdev->dev, sizeof(struct ddrc_flux_device), GFP_KERNEL);
	if (!dfdev) {
		dev_warn(&pdev->dev, "Kzalloc failed\n");
		ret = -ENOMEM;
		goto no_mem;
	}

	if (of_property_read_u32_array(np, "hisi,bl31-share-mem", &data[0], 2)) {
		pr_err("[%s] %s node doesn't have hi3xxx-clkgate property!\n",
			 __func__, np->name);
		goto no_bl;
	}

	bl31_smem_base += data[0];

	dfdev->ddrflux_base = ioremap(bl31_smem_base, data[1]);
	if (!dfdev->ddrflux_base) {
		dev_err(dev, "failed to iomap!\n");
		ret = -ENOMEM;
		goto no_iomap;
	}
	dfdev->katf_data_len = MAX_FLUX_REG_NUM * 4 /*+ MAX_SLICE_LEN*/;
	dfdev->flux_pull_va = dfdev->ddrflux_base + DDRFLUX_PULL_OFFSET;
	dfdev->flux_en_va = dfdev->ddrflux_base + DDRFLUX_EN_OFFSET;
	dfdev->dramtype_va = dfdev->ddrflux_base + DDRFLUX_DRAMTYPE_OFFSET;
	dfdev->flux_staid_va = dfdev->ddrflux_base + DDRFLUX_STAID_OOFFSET;

	dfdev->flux_pull_dma_pa = bl31_smem_base + DDRFLUX_PULL_OFFSET;
	dfdev->flux_en_dma_pa = bl31_smem_base + DDRFLUX_EN_OFFSET;
	dfdev->dramtype_dma_pa = bl31_smem_base + DDRFLUX_DRAMTYPE_OFFSET;
	dfdev->flux_staid_pa = bl31_smem_base + DDRFLUX_STAID_OOFFSET;

	dfdev->dmss_base =  NULL;
	dfdev->qosb_base[0] = NULL;
	dfdev->qosb_base[1] = NULL;
	for (i = 0; i < 4; i++)
		dfdev->dmc_base[i] = NULL;

	dfdev->ddrc_freq_clk = of_clk_get(np, 0);
	if (IS_ERR_OR_NULL(dfdev->ddrc_freq_clk)) {
		dev_warn(&pdev->dev, "Clock not found\n");
		ret = PTR_ERR(dfdev->ddrc_freq_clk);
		goto no_ddrfreq;
	}
	dfdev->ddrc_flux_timer = kzalloc(sizeof(BwTimer), GFP_KERNEL);
	if (!dfdev->ddrc_flux_timer) {
		pr_err("Kzalloc failed %d\n", __LINE__);
		ret = -ENOMEM;
		goto no_timer_mem;
	}
	dfdev->ddrc_flux_timer->clk = of_clk_get(np, 1);
	if (IS_ERR_OR_NULL(dfdev->ddrc_flux_timer->clk)) {
		pr_err("timer clock get failed! %d\n", __LINE__);
		ret = PTR_ERR(dfdev->ddrc_flux_timer->clk);
		goto no_timerclk;
	}
	dfdev->ddrc_flux_timer->base = VIRT(SOC_ACPU_TIMER5_BASE_ADDR, 1);
	if (NULL == dfdev->ddrc_flux_timer->base) {
		pr_err("%s: ioremap failed,%d\n", __func__, __LINE__);
		goto err;
	}
	dfdev->sctrl = VIRT(SOC_ACPU_SCTRL_BASE_ADDR, 1);
	if (NULL == dfdev->sctrl) {
		pr_err("%s: ioremap failed,%d\n", __func__, __LINE__);
		goto err1;
	}
	dfdev->ddrc_flux_timer->irq = TIMER_IRQ;
	dfdev->ddrc_flux_timer->irq_per_cpu =  IRQ_CPU_CORE;
	dfdev->ddrc_flux_timer->pclk = NULL;
	strncpy(dfdev->slice.name, DEFAULT_SLICE_NAME, SLICE_LEN);
	dfdev->dram_type = 0x3;

	spin_lock_init(&dfdev->ddrc_flux_timer->lock);
	spin_lock_init(&dfdev->lock);
	platform_set_drvdata(pdev, dfdev);
	ddrc_flux_dir_init();
	pr_info("[%s] probe sucess!\n", dev_name(&pdev->dev));
	return ret;
err1:
	iounmap(dfdev->ddrc_flux_timer->base);
	dfdev->ddrc_flux_timer->base = NULL;
err:
	clk_put(dfdev->ddrc_flux_timer->clk);
no_timerclk:
	kfree(dfdev->ddrc_flux_timer);
	dfdev->ddrc_flux_timer = NULL;
no_timer_mem:
	clk_put(dfdev->ddrc_freq_clk);
no_ddrfreq:
	iounmap(dfdev->ddrflux_base);
	dfdev->ddrflux_base = NULL;
no_iomap:
no_bl:
	kfree(dfdev);
	dfdev = NULL;
no_mem:
	of_node_put(np);
out:
	return ret;
}

static int ddrc_flux_remove(struct platform_device *pdev)
{
	platform_set_drvdata(pdev, NULL);
	clk_put(dfdev->ddrc_freq_clk);
	clk_put(dfdev->ddrc_flux_timer->clk);
	return 0;
}

#ifdef CONFIG_OF
static struct of_device_id ddrc_flux_of_device_ids[] = {
	{.compatible = "hisilicon,ddrc-flux",},
	{},
};
MODULE_DEVICE_TABLE(of, ddr_devfreq_of_match);
#endif

static struct platform_driver ddrc_flux_driver = {
	.driver		= {
		.name	= "ddrc-flux",
		.owner	= THIS_MODULE,
		.of_match_table = ddrc_flux_of_device_ids,
	},
	.probe		= ddrc_flux_probe,
	.remove	= ddrc_flux_remove,
};
module_platform_driver(ddrc_flux_driver)

/*lint +e438 +e514 +e550 +e715 +e749 +e754 +e774 +e818 +e835 +e838 +e845*/

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ddrc flux statistics driver for hisi");
MODULE_AUTHOR("z00241933 <zhaokai1@hisilicon.com>");
