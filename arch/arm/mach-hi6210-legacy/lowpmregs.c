/*
 *	linux/arch/arm/mach-k3v2/irq.c
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <asm/hardware/gic.h>
#include <mach/io.h>
#include <mach/platform.h>
#include <mach/platform.h>
#include <linux/platform_device.h>
#include <linux/console.h>
#include <mach/early-debug.h>
#include <asm/hardware/arm_timer.h>
#include <mach/boardid.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <hsad/config_interface.h>
#include <linux/ipps.h>
#include <linux/cpufreq-k3v2.h>
#include "board.h"
#include "iomux/iomux.h"

static void __iomem *g_sc_addr;
static void __iomem *g_pctrl_addr;
static void __iomem *g_pmuspi_addr;
static unsigned g_usavedcfg;
#define DEBG_SUSPEND_PMU_SHOW	(1<<2)

#ifdef	CONFIG_LOWPM_DEBUG
static struct ipps_client ipps_client;
#define DEBG_SUSPEND_PRINTK		(1<<0)
#define DEBG_SUSPEND_IO_SHOW	(1<<1)
#define DEBG_SUSPEND_IO_SET		(1<<3)
#define DEBG_SUSPEND_PMU_SET	(1<<4)
#define DEBG_SUSPEND_IO_S_SET	(1<<5)
#define DEBG_SUSPEND_RTC_EN		(1<<6)
#define DEBG_SUSPEND_TIMER_EN	(1<<7)
#define DEBG_SUSPEND_WAKELOCK	(1<<8)
#define DEBG_SUSPEND_AUDIO		(1<<9)

static int g_suspended;
static unsigned g_utimer_inms;
static unsigned g_urtc_ins;

/*****************************************************************
* function: setiolowpower
* description:
*  set all io to low power state.
******************************************************************/
void setiolowpower(void)
{
	if (!(g_usavedcfg & DEBG_SUSPEND_IO_SET))
		return;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);
	iomux_debug_set();
	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}

/*****************************************************************
* function: ioshowstatus
* description:
*  show io status.
******************************************************************/
void ioshowstatus(int check)
{
	if (!(g_usavedcfg & DEBG_SUSPEND_IO_SHOW))
		return;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);
	iomux_debug_show(check);
	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}

#endif

/*****************************************************************
* function:    pmuspi_enable
* description:
*  enable pmu clk.
******************************************************************/
static void pmuspi_enable(void)
{
	/*set clk div*/
	writel(0xFF0003, (g_pctrl_addr + 0x8));

	/*enable clk*/
	writel(1<<1, (g_sc_addr + 0x40));

	/*undo reset*/
	writel(1<<1, (g_sc_addr + 0x9C));
}

/*****************************************************************
* function:    pmuspi_disable
* description:
*  disable pmu clk.
******************************************************************/
static void pmuspi_disable(void)
{
	/*reset*/
	writel(1<<1, (g_sc_addr + 0x98));

	/*disable clk*/
	writel(1<<1, (g_sc_addr + 0x44));
}

#define PMUSPI_REG(x) (g_pmuspi_addr + ((x)<<2))

struct pmuregs {
	unsigned char ucoffset;
	char cval;
	char old_val;
	char cmask;
};

#define PMU_LOW(x, y, z) { .ucoffset = (x), .cval = (y), .cmask = (z), .old_val = 0,}

static struct pmuregs pmuregs_lookups[] = {
	/*close LDO0 */
	PMU_LOW(0x20, 0x00, 0x10),

	/*w 35 0, emmc rst2_n output low.*/
	PMU_LOW(0x35, 0x00, 0x01),

	/*close ldo13*/
	PMU_LOW(0x2D, 0x30, 0x30),

	/*w 25 31  LDO5 ECO mode*/
	/*PMU_LOW(0x25, 0x20, 0x20),*/

	/*w 26 34  LDO6 ECO mode*/
	/*PMU_LOW(0x26, 0x20, 0x20),*/

	/*w 4e 20 close over temperature protect*/
	PMU_LOW(0x4E, 0x00, 0x01),

	/*w 52 00 close backup battery charging*/
	PMU_LOW(0x52, 0x00, 0x01),

	/*w 14 11  BUCK4 Sleep*/
	PMU_LOW(0x14, 0x11, 0x11),

	/*w 16 11  BUCK5 Sleep*/
	PMU_LOW(0x16, 0x11, 0x11),

	/*w 8f 08 sleep*/
	/*PMU_LOW(0x8F, 0x08, 0x07),*/
};


/*****************************************************************
* function: pmulowpower
* description:
*  configure pmu low power state.
******************************************************************/
void pmulowpower(int isuspend)
{
	int i = 0;
	int ilen = ARRAY_SIZE(pmuregs_lookups);
	unsigned uregv = 0;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	pmuspi_enable();

	if (1 == isuspend) {
		for (i = 0; i < ilen; i++) {
			uregv = readl(PMUSPI_REG(pmuregs_lookups[i].ucoffset));
			pmuregs_lookups[i].old_val = uregv;
			uregv &= ~pmuregs_lookups[i].cmask;
			uregv |= pmuregs_lookups[i].cval;

#ifdef CONFIG_DEBUG_FS
			if (g_usavedcfg & DEBG_SUSPEND_PMU_SHOW)
				pr_info("[%s] %d %02d reg_%02x=%02x old=%02x.\n", __func__,
				__LINE__, i, pmuregs_lookups[i].ucoffset,
				uregv, pmuregs_lookups[i].old_val);
#endif
			writel(uregv, PMUSPI_REG(pmuregs_lookups[i].ucoffset));
		}

	} else {
		for (i = (ilen - 1); i >= 0; i--) {
			uregv = readl(PMUSPI_REG(pmuregs_lookups[i].ucoffset));
			uregv &= ~pmuregs_lookups[i].cmask;
			uregv |= pmuregs_lookups[i].old_val;
			writel(uregv, PMUSPI_REG(pmuregs_lookups[i].ucoffset));
		}
	}

	if (1 == isuspend)
		pmuspi_disable();

	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}

#ifdef CONFIG_LOWPM_DEBUG

#include <linux/wakelock.h>

static struct wake_lock lowpm_wake_lock;

/****************************************
*function: debuguart_reinit
*description:
*  reinit debug uart.
*****************************************/
void debuguart_reinit(void)
{
	unsigned int usctrl_base = IO_ADDRESS(REG_BASE_SCTRL);
	unsigned int uuart_base  = IO_ADDRESS(REG_EDB_UART);
	unsigned int io_base = IO_ADDRESS(REG_BASE_IOC_OFF);
	unsigned int uregv = 0;

	if (!(g_usavedcfg & DEBG_SUSPEND_PRINTK)) {
		return;
	}

	/* Config necessary IOMG configuration */
	writel(0, (io_base+0xF4));

	/* config necessary IOCG configuration */
	writel(0, (io_base+0xA08));
	writel(0, (io_base+0xA0C));

	/*disable clk*/
	uregv = 0x10000;
	writel(uregv, (usctrl_base + 0x44));

	/*select 26MHz clock*/
	uregv = (1<<23);
	writel(uregv, (usctrl_base + 0x100));

	/*@ enable clk*/
	uregv = 0x10000;
	writel(uregv, (usctrl_base + 0x40));

	/*@;disable recieve and send*/
	uregv = 0x0;
	writel(uregv, (uuart_base + 0x30));

	/*@;enable FIFO*/
	uregv = 0x70;
	writel(uregv, (uuart_base + 0x2c));

	/*@;set baudrate*/
	uregv = 0xE;
	writel(uregv, (uuart_base + 0x24));

	uregv = 0x7;
	writel(uregv, (uuart_base + 0x28));

	/*@;clear buffer*/
	uregv = readl(uuart_base);

	/*@;enable FIFO*/
	uregv = 0x70;
	writel(uregv, (uuart_base + 0x2C));

	/*@;set FIFO depth*/
	uregv = 0x10A;
	writel(uregv, (uuart_base + 0x34));

	uregv = 0x50;
	writel(uregv, (uuart_base + 0x38));

	/*@;enable uart trans*/
	uregv = 0xF01;
	writel(uregv, (uuart_base + 0x30));
}

static struct pmuregs pmuregs_lookups_all[] = {

	/*w c9 FF close adc, all pga*/
	PMU_LOW(0xC9, 0xFF, 0xFF),

	/*w ca FE AVERF 500K,close mix,micbias,pll,ibias*/
	PMU_LOW(0xCA, 0xFE, 0xFF),

	/*w cb FF close DAC,OUTMIX,DAC MIX*/
	PMU_LOW(0xCB, 0xFF, 0xFF),

	/*w cc FF close all output*/
	PMU_LOW(0xCC, 0xFF, 0xFF),

	/*w 20 00 close LDO0*/
	PMU_LOW(0x20, 0x00, 0x10),

	/*w 21 00 close LDO1*/
	PMU_LOW(0x21, 0x00, 0x10),

	/*w 22 31 LDO2 ECO mode*/
	/*PMU_LOW(0x22, 0x20, 0x20),*/

	/*w 23 00 close LDO3*/
	/*PMU_LOW(0x23, 0x00, 0x10),*/

	/*w 24 00 close LDO4*/
	PMU_LOW(0x24, 0x00, 0x10),

	/*w 25 31 LDO5 ECO mode*/
	PMU_LOW(0x25, 0x20, 0x20),

	/*w 26 34 LDO6 ECO mode*/
	PMU_LOW(0x26, 0x20, 0x20),

	/*w 27 3x LDO7 ECO*/
	PMU_LOW(0x27, 0x30, 0x30),

	/*w 28 00 close LDO8*/
	PMU_LOW(0x28, 0x00, 0x10),

	/*close ldo13*/
	PMU_LOW(0x2D, 0x00, 0x10),

	/*w 35 0, emmc rst2_n output low.*/
	PMU_LOW(0x35, 0x00, 0x01),

	/*diable ldo3 hardware config.*/
	PMU_LOW(0x4C, 0x08, 0x08),

	/*w 4e 20 close over temperature protect*/
	PMU_LOW(0x4E, 0x00, 0x01),

	/*w 52 00 close backup battery charging*/
	PMU_LOW(0x52, 0x00, 0x01),

	/*w 53 00 disable culon*/
	PMU_LOW(0x53, 0x00, 0x02),

	/*w 0c 00 diable software control BUCK0*/
	PMU_LOW(0x0C, 0x00, 0xFF),

	/*w 0e 00 diable software control BUCK1*/
	PMU_LOW(0x0E, 0x00, 0xFF),

	/*w 10 00  diable software control BUCK2*/
	PMU_LOW(0x10, 0x00, 0xFF),

	/*w 12 00  diable software control BUCK3*/
	PMU_LOW(0x12, 0x00, 0xFF),

	/*w 14 11  BUCK4 Sleep*/
	PMU_LOW(0x14, 0x11, 0x11),

	/*w 16 11  BUCK5 Sleep*/
	PMU_LOW(0x16, 0x11, 0x11),

	/*w 8f 08 sleep*/
	PMU_LOW(0x8F, 0x08, 0x07),
};



/*****************************************************************
* function: pmulowpower
* description:
*  configure pmu low power state.
******************************************************************/
void pmulowpowerall(int isuspend)
{
	int i = 0;
	int ilen = ARRAY_SIZE(pmuregs_lookups_all);
	unsigned uregv = 0;

	if (!(g_usavedcfg & DEBG_SUSPEND_PMU_SET))
		return;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	if (g_suspended == 1)
		pmuspi_enable();

	if (1 == isuspend) {
		for (i = 0; i < ilen; i++) {
			/*audio relative*/
			if (!(DEBG_SUSPEND_AUDIO & g_usavedcfg))
				if ((pmuregs_lookups_all[i].ucoffset == 0xC9)
					|| (pmuregs_lookups_all[i].ucoffset == 0xCA)
					|| (pmuregs_lookups_all[i].ucoffset == 0xCB)
					|| (pmuregs_lookups_all[i].ucoffset == 0xCC))
					continue;

			uregv = readl(PMUSPI_REG(pmuregs_lookups_all[i].ucoffset));
			pmuregs_lookups_all[i].old_val = uregv;
			uregv &= ~pmuregs_lookups_all[i].cmask;
			uregv |= pmuregs_lookups_all[i].cval;
			pr_info("[%s] %d %02d reg_%02x=%02x old=%02x.\n", __func__, __LINE__,
				i, pmuregs_lookups_all[i].ucoffset, uregv, pmuregs_lookups_all[i].old_val);
			writel(uregv, PMUSPI_REG(pmuregs_lookups_all[i].ucoffset));
		}
	} else {
		for (i = (ilen - 1); i >= 0; i--) {

			/*audio relative*/
			if (!(DEBG_SUSPEND_AUDIO & g_usavedcfg))
				if ((pmuregs_lookups_all[i].ucoffset == 0xC9)
					|| (pmuregs_lookups_all[i].ucoffset == 0xCA)
					|| (pmuregs_lookups_all[i].ucoffset == 0xCB)
					|| (pmuregs_lookups_all[i].ucoffset == 0xCC))
					continue;

			uregv = readl(PMUSPI_REG(pmuregs_lookups_all[i].ucoffset));
			uregv &= ~pmuregs_lookups_all[i].cmask;
			uregv |= pmuregs_lookups_all[i].old_val;
			writel(uregv, PMUSPI_REG(pmuregs_lookups_all[i].ucoffset));
		}
	}

	if ((g_suspended == 1) && (1 == isuspend))
		pmuspi_disable();

	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}


/*****************************************************************
* function: pmulowpower_show
* description:
*  show pmu status.
******************************************************************/
void pmulowpower_show(int check)
{
	int i = 7;
	int ilen = ARRAY_SIZE(pmuregs_lookups_all);
	int index = 0;
	unsigned char uregv;

	if (!(g_usavedcfg & DEBG_SUSPEND_PMU_SHOW))
		return;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	if (g_suspended == 1)
		pmuspi_enable();

	for (i = 7; i < 0xFF; i++) {
		uregv = readl(PMUSPI_REG(i));
		printk("PMU 0x%02X=0x%02X", i, uregv);

		if ((check == 1)
			&& (i == pmuregs_lookups_all[index].ucoffset)
			&& (index < ilen)) {
			printk(" (0x%02X)", pmuregs_lookups_all[index].cval);
			index++;
		}

		printk("\n");
	}

	if (g_suspended == 1)
		pmuspi_disable();

	pr_info("[%s] %d leave.\n", __func__, __LINE__);
}

void rtc_enable(void)
{
	unsigned uregv = 0;

	void __iomem * urtc_base = (void __iomem *)IO_ADDRESS(REG_BASE_RTC);

	if (!(g_usavedcfg&DEBG_SUSPEND_RTC_EN))
		return;

#if 0
	printk("%s %x\n, %x\n, %x\n, %x\n, %x\n, %x\n, %x\n, %x\n",
		__func__, readl(urtc_base),
		readl(urtc_base+0x4),
		readl(urtc_base+0x8),
		readl(urtc_base+0xc),
		readl(urtc_base+0x10),
		readl(urtc_base+0x14),
		readl(urtc_base+0x18),
		readl(urtc_base+0x1c));
#endif

	/*enable rtc*/
	/*writel(0x1, (urtc_base+0xC));*/

	/*initial LR*/
	/*writel(0x1, (urtc_base+0x8));*/

	/*enable interrupt*/
	writel(0x1, (urtc_base+0x10));

	/*clear intr*/
	writel(0x1, (urtc_base+0x1C));

	/*read current value*/
	uregv = readl(urtc_base);

	/*set cmp value*/
	uregv += g_urtc_ins;
	writel(uregv, (urtc_base+0x4));
}

/**Timer0 wakeup function**/
#define GT_CLK_TIMER1					(1<<3)
#define GT_PCLK_TIMER1					(1<<2)
#define GT_CLK_TIMER0					(1<<1)
#define GT_PCLK_TIMER0					(1<<0)

#define SCCTRL_TIMEREN1OV				(1<<18)
#define SCCTRL_TIMEREN1SEL				(1<<17)
#define SCCTRL_TIMEREN0OV				(1<<16)
#define SCCTRL_TIMEREN0SEL				(1<<15)
#define SCCTRL_TIMEFORCEHIGH			(1<<8)

#define IP_RST_TIMER0					(1<<0)

#define TIMEREN_BIT						(1<<7)
#define TIMERMODE_BIT					(1<<6)
#define TIMEINT_BIT						(1<<5)
#define TIMERSIZE_BIT					(1<<1)


void timer0_0_enable(void)
{
	unsigned uregv = 0;
	void __iomem * usctrl_base = (void __iomem *)IO_ADDRESS(REG_BASE_SCTRL);
	void __iomem * utimer0_base = (void __iomem *)IO_ADDRESS(REG_BASE_TIMER0);

	if (!(g_usavedcfg&DEBG_SUSPEND_TIMER_EN))
		return;

	/*clear timer intr */
	uregv = 1;
	writel(uregv, (utimer0_base+TIMER_INTCLR));

	/*disable timer*/
	uregv = 0;
	writel(uregv, (utimer0_base+TIMER_CTRL));

	/*reset timer0*/
	writel(IP_RST_TIMER0, (usctrl_base + 0x80));

	/*disable pclk_timer0, clk_timer0*/
	uregv = GT_PCLK_TIMER0|GT_CLK_TIMER0;
	writel(uregv, (usctrl_base+0x24));

	uregv  = readl(usctrl_base);
	/*printk("%s, %d, sysctrl=%x\r\n", __func__, __LINE__, uregv);*/

	/*timer0_0 select 32.768KHz.*/
	uregv = readl(usctrl_base);
	uregv &= ~(SCCTRL_TIMEREN0SEL|SCCTRL_TIMEREN0OV);
	uregv |= SCCTRL_TIMEFORCEHIGH;
	writel(uregv, usctrl_base);

	uregv  = readl(usctrl_base);
	/*printk("%s, %d, sysctrl=%x\r\n", __func__, __LINE__, uregv);*/

	/*enable pclk_timer0, clk_timer0*/
	uregv = GT_PCLK_TIMER0|GT_CLK_TIMER0;
	writel(uregv, (usctrl_base+0x20));

	/*undo reset*/
	writel(IP_RST_TIMER0, (usctrl_base + 0x84));

	/*read timer value*/
	uregv = readl((utimer0_base + TIMER_VALUE));
	/*printk("%s, %d, timerv=%d\r\n", __func__, __LINE__, uregv);*/

	/*set load. */
	uregv = 32 * g_utimer_inms;
	writel(uregv, utimer0_base);
	writel(uregv, utimer0_base+TIMER_BGLOAD);

	uregv = readl((utimer0_base + TIMER_VALUE));
	/*printk("%s, %d, timerv=%d\r\n", __func__, __LINE__, uregv);*/

	/*bit 7:timer enable
	*bit 6: timer mode period
	*bit 1:timer size 32bit */
	uregv = TIMEREN_BIT|TIMERMODE_BIT|TIMERSIZE_BIT|TIMEINT_BIT;
	writel(uregv, (utimer0_base+TIMER_CTRL));

	uregv = readl((utimer0_base + TIMER_VALUE));
	/*printk("%s, %d, timerv=%d\r\n", __func__, __LINE__, uregv);*/

}

void timer0_0_disable(void)
{
	unsigned uregv = 0;

	void __iomem * utimer0_base = (void __iomem *)IO_ADDRESS(REG_BASE_TIMER0);
	void __iomem * usctrl_base = (void __iomem *)IO_ADDRESS(REG_BASE_SCTRL);

	if (!(g_usavedcfg&DEBG_SUSPEND_TIMER_EN))
		return;

	uregv = readl((utimer0_base + 0x4));
	/*printk("%s, %d, timerv=%d\r\n", __func__, __LINE__, uregv);*/

	/*clear timer intr */
	uregv = 1;
	writel(uregv, (utimer0_base+0xc));

	uregv  = readl(usctrl_base);
	/*printk("%s, %d, sysctrl=%x\r\n", __func__, __LINE__, uregv);*/

	uregv = readl(usctrl_base);
	uregv &= ~(SCCTRL_TIMEREN0OV|SCCTRL_TIMEFORCEHIGH);
	uregv |= SCCTRL_TIMEREN0SEL;
	writel(uregv, usctrl_base);

	uregv  = readl(usctrl_base);
	/*printk("%s, %d, sysctrl=%x\r\n", __func__, __LINE__, uregv);*/

#if 0
	/*disable pclk_timer0, clk_timer0*/
	uregv = GT_PCLK_TIMER0|GT_CLK_TIMER0;
	writel(uregv, (usctrl_base+0x24));
#endif
}

void set_wakelock(int iflag)
{
	if ((1 == iflag) && (0 == wake_lock_active(&lowpm_wake_lock)))
		wake_lock(&lowpm_wake_lock);
	else if ((0 == iflag) && (0 != wake_lock_active(&lowpm_wake_lock)))
		wake_unlock(&lowpm_wake_lock);
}

#ifdef CONFIG_DEBUG_FS

#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

#define MX_BUF_LEN		1024
char g_ctemp[MX_BUF_LEN] = {0};

/*****************************************************************
* function:    dbg_cfg_open
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_cfg_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_cfg_read
* description:
*  show the debug cfg for user.
******************************************************************/
static ssize_t dbg_cfg_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp,
		"0x1<<0 enable suspend console\n"
		"0x1<<1 ENABLE IO STATUS SHOW\n"
		"0x1<<2 ENABLE PMU STATUS SHOW\n"
		"0x1<<3 ENABLE IO SET\n"
		"0x1<<4 ENABLE PMU SET\n"
		"0x1<<5 ENABLE SINGLE IO SET\n"
		"0x1<<6 ENABLE 1s RTC wakeup\n"
		"0x1<<7 ENABLE 500ms TIMER wakeup\n"
		"0x1<<8 ENABLE a wakelock\n"
		"g_usavedcfg=%x\n", g_usavedcfg);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_cfg_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_cfg_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	int index = 0;

	memset(g_ctemp, 0, MX_BUF_LEN);

	if (copy_from_user(g_ctemp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(g_ctemp, "%d", &index))
		g_usavedcfg = index;
	else
		pr_info("ERRR~\n");

	pr_info("%s %d, g_usavedcfg=%x\n", __func__, __LINE__, g_usavedcfg);

	/*suspend print enable*/
	if (DEBG_SUSPEND_PRINTK & g_usavedcfg)
		console_suspend_enabled = 0;
	else
		console_suspend_enabled = 1;

	if (DEBG_SUSPEND_WAKELOCK & g_usavedcfg)
		set_wakelock(1);
	else
		set_wakelock(0);

	*ppos += count;

	return count;
}

const struct file_operations dbg_cfg_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_cfg_open,
	.read	= dbg_cfg_read,
	.write	= dbg_cfg_write,
};

/*****************************************************************
* function:    dbg_timer_open
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_timer_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_timer_read
* description:
*  show the debug cfg for user.
******************************************************************/
static ssize_t dbg_timer_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "ENABLE %dms TIMER wakeup\n", g_utimer_inms);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_timer_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_timer_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	int index = 0;

	memset(g_ctemp, 0, MX_BUF_LEN);

	if (copy_from_user(g_ctemp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(g_ctemp, "%d", &index))
		g_utimer_inms = index;
	else
		pr_info("ERRR~\n");

	pr_info("%s %d, g_utimer_inms=%x\n", __func__, __LINE__, g_utimer_inms);

	*ppos += count;

	return count;
}

const struct file_operations dbg_timer_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_timer_open,
	.read	= dbg_timer_read,
	.write	= dbg_timer_write,
};


/*****************************************************************
* function:    dbg_timer_open
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_rtc_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_timer_read
* description:
*  show the debug cfg for user.
******************************************************************/
static ssize_t dbg_rtc_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "ENABLE %dms rtc wakeup\n", g_urtc_ins);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_timer_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_rtc_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	int index = 0;

	memset(g_ctemp, 0, MX_BUF_LEN);

	if (copy_from_user(g_ctemp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(g_ctemp, "%d", &index))
		g_urtc_ins = index;
	else
		pr_info("ERRR~\n");

	pr_info("%s %d, g_urtc_ins=%x\n", __func__, __LINE__, g_urtc_ins);

	*ppos += count;

	return count;
}

const struct file_operations dbg_rtc_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_rtc_open,
	.read	= dbg_rtc_read,
	.write	= dbg_rtc_write,
};

/*****************************************************************
* function:    dbg_iomux_open
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_iomux_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_iomux_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_iomux_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	char temp[32] = {0};

	if (*ppos >= 32)
		return 0;

	if (*ppos + count > 32)
		count = 32 - *ppos;

	if (copy_to_user(buffer, temp + *ppos, count))
		return -EFAULT;

	ioshowstatus(1);

	*ppos += count;
	return count;
}

const struct file_operations dbg_iomux_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_iomux_open,
	.read	= dbg_iomux_read,
};


/*****************************************************************
* function:    dbg_pmu_show
* description:
*  show the pmu status.
******************************************************************/
static int dbg_pmu_show(struct seq_file *s, void *unused)
{
	pmulowpower_show(1);

	return 0;
}

/*****************************************************************
* function:    dbg_pmu_open
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_pmu_open(struct inode *inode, struct file *file)
{
	return single_open(file, dbg_pmu_show, &inode->i_private);
}

static const struct file_operations debug_pmu_fops = {
	.open		= dbg_pmu_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

/**********************cpufreq adjust begin*****************************/

#ifdef CONFIG_IPPS_SUPPORT

struct ipps_param gdbgipps_param;
struct ipps_param_stru gdbgipps_param_stru;

/****************cpu begin**********************/

/*****************************************************************
* function:    dbg_cpu_max
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_cpumax_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_iomux_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_cpumax_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "cpumax=%d\n", gdbgipps_param_stru.ipps_param->cpu.max_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_cpumax_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, cpumax=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->cpu.max_freq = index;
		PARAM_MAX_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_cpumax_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_cpumax_open,
	.read	= dbg_cpumax_read,
	.write	= dbg_cpumax_write,
};

/*****************************************************************
* function:    dbg_cpumin
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_cpumin_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_cpumin_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_cpumin_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "cpumin=%d\n", gdbgipps_param_stru.ipps_param->cpu.min_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_cpumin_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_cpumin_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, cpumin=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->cpu.min_freq = index;
		PARAM_MIN_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_cpumin_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_cpumin_open,
	.read	= dbg_cpumin_read,
	.write	= dbg_cpumin_write,
};

/*****************************************************************
* function:    dbg_cpusafe
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_cpusafe_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_cpumin_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_cpusafe_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "cpusafe=%d\n", gdbgipps_param_stru.ipps_param->cpu.safe_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_cpumin_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_cpusafe_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, cpusafe=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->cpu.safe_freq = index;
		PARAM_SAFE_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_CPU, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_cpusafe_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_cpusafe_open,
	.read	= dbg_cpusafe_read,
	.write	= dbg_cpusafe_write,
};
/****************cpu end**********************/

/****************gpu begin**********************/
/*****************************************************************
* function:    dbg_gpumax
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_gpumax_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_iomux_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_gpumax_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "gpumax=%d\n", gdbgipps_param_stru.ipps_param->gpu.max_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_gpumax
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_gpumax_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, gpumax=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->gpu.max_freq = index;
		PARAM_MAX_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_gpumax_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_gpumax_open,
	.read	= dbg_gpumax_read,
	.write	= dbg_gpumax_write,
};

/*****************************************************************
* function:    dbg_gpumin
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_gpumin_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_cpumin_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_gpumin_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "gpumin=%d\n", gdbgipps_param_stru.ipps_param->gpu.min_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_cpumin_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_gpumin_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, gpumin=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->gpu.min_freq = index;
		PARAM_MIN_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_gpumin_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_gpumin_open,
	.read	= dbg_gpumin_read,
	.write	= dbg_gpumin_write,
};

/*****************************************************************
* function:    dbg_gpusafe
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_gpusafe_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_cpumin_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_gpusafe_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "gpusafe=%d\n", gdbgipps_param_stru.ipps_param->gpu.safe_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_cpumin_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_gpusafe_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, gpusafe=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->gpu.safe_freq = index;
		PARAM_SAFE_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_GPU, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_gpusafe_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_gpusafe_open,
	.read	= dbg_gpusafe_read,
	.write	= dbg_gpusafe_write,
};
/****************gpu end************************/

/****************ddr begin**********************/
/*****************************************************************
* function:    dbg_ddrmax
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_ddrmax_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_iomux_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_ddrmax_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "ddrmax=%d\n", gdbgipps_param_stru.ipps_param->ddr.max_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_gpumax
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_ddrmax_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, ddrmax=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->ddr.max_freq = index;
		PARAM_MAX_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_ddrmax_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_ddrmax_open,
	.read	= dbg_ddrmax_read,
	.write	= dbg_ddrmax_write,
};

/*****************************************************************
* function:    dbg_ddrmin
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_ddrmin_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_cpumin_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_ddrmin_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "ddrmin=%d\n", gdbgipps_param_stru.ipps_param->ddr.min_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_cpumin_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_ddrmin_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, ddrmin=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->ddr.min_freq = index;
		PARAM_MIN_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_ddrmin_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_ddrmin_open,
	.read	= dbg_ddrmin_read,
	.write	= dbg_ddrmin_write,
};

/*****************************************************************
* function:    dbg_ddrsafe
* description:
*  adapt to the interface.
******************************************************************/
static int dbg_ddrsafe_open(struct inode *inode, struct file *filp)
{
	filp->private_data = inode->i_private;
	return 0;
}

/*****************************************************************
* function:    dbg_cpumin_read
* description:
*  print out he io status on the COM.
******************************************************************/
static ssize_t dbg_ddrsafe_read(struct file *filp, char __user *buffer,
	size_t count, loff_t *ppos)
{
	if (*ppos >= MX_BUF_LEN)
		return 0;

	if (*ppos + count > MX_BUF_LEN)
		count = MX_BUF_LEN - *ppos;

	memset(g_ctemp, 0, MX_BUF_LEN);

	sprintf(g_ctemp, "ddrsafe=%d\n", gdbgipps_param_stru.ipps_param->ddr.safe_freq);

	if (copy_to_user(buffer, g_ctemp + *ppos, count))
		return -EFAULT;

	*ppos += count;
	return count;
}

/*****************************************************************
* function:    dbg_cpumin_write
* description:
*  recieve the configuer of the user.
******************************************************************/
static ssize_t dbg_ddrsafe_write(struct file *filp, const char __user *buffer,
	size_t count, loff_t *ppos)
{
	char tmp[128] = {0};
	int index = 0;

	if (count > 128) {
		pr_info("error! buffer size big than internal buffer\n");
		return -EFAULT;
	}

	if (copy_from_user(tmp, buffer, count)) {
		pr_info("error!\n");
		return -EFAULT;
	}

	if (sscanf(tmp, "%d", &index)) {
		//pr_info("%s, %d, ddrsafe=%d\n", __func__, __LINE__, index);
		gdbgipps_param_stru.ipps_param->ddr.safe_freq = index;
		PARAM_SAFE_TYPE(gdbgipps_param_stru);
		ipps_set_parameter(&ipps_client, IPPS_OBJ_DDR, &gdbgipps_param_stru);
	} else {
		pr_info("ERRR~\n");
	}

	*ppos += count;

	return count;
}

const struct file_operations dbg_ddrsafe_fops = {
	.owner	= THIS_MODULE,
	.open	= dbg_ddrsafe_open,
	.read	= dbg_ddrsafe_read,
	.write	= dbg_ddrsafe_write,
};

/****************ddr end************************/

#endif

/**********************cpufreq adjust end****************************/

/*****************************************************************
* function:    lowpm_test_probe
* description:
*  driver interface.
******************************************************************/
static int lowpm_test_probe(struct platform_device *pdev)
{
	int status = 0;
	struct dentry *pdentry;

	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	g_sc_addr = (void __iomem *) IO_ADDRESS(REG_BASE_SCTRL);
	g_pctrl_addr = (void __iomem *) IO_ADDRESS(REG_BASE_PCTRL);
	g_pmuspi_addr = (void __iomem *) IO_ADDRESS(REG_BASE_PMUSPI);

	g_suspended = 0;

	/*default timer0 wakeup time 500ms*/
	g_utimer_inms = 200;

	/*default rtc wakeup time in 1s*/
	g_urtc_ins = 1;

	wake_lock_init(&lowpm_wake_lock, WAKE_LOCK_SUSPEND, "lowpm_test");

	pdentry = debugfs_create_dir("lowpm_test", NULL);
	if (!pdentry) {
		pr_info("%s %d error can not create debugfs lowpm_test.\n", __func__, __LINE__);
		return -ENOMEM;
	}

	(void) debugfs_create_file("pmu", S_IRUSR, pdentry, NULL, &debug_pmu_fops);

	(void) debugfs_create_file("io", S_IRUSR, pdentry, NULL, &dbg_iomux_fops);

	(void) debugfs_create_file("cfg", S_IRUSR, pdentry, NULL, &dbg_cfg_fops);

	(void) debugfs_create_file("timer", S_IRUSR, pdentry, NULL, &dbg_timer_fops);

	(void) debugfs_create_file("rtc", S_IRUSR, pdentry, NULL, &dbg_rtc_fops);

#ifdef CONFIG_IPPS_SUPPORT
	(void) debugfs_create_file("cpumax", S_IRUSR, pdentry, NULL, &dbg_cpumax_fops);
	(void) debugfs_create_file("cpumin", S_IRUSR, pdentry, NULL, &dbg_cpumin_fops);
	(void) debugfs_create_file("cpusafe", S_IRUSR, pdentry, NULL, &dbg_cpusafe_fops);

	(void) debugfs_create_file("gpumax", S_IRUSR, pdentry, NULL, &dbg_gpumax_fops);
	(void) debugfs_create_file("gpumin", S_IRUSR, pdentry, NULL, &dbg_gpumin_fops);
	(void) debugfs_create_file("gpusafe", S_IRUSR, pdentry, NULL, &dbg_gpusafe_fops);

	(void) debugfs_create_file("ddrmax", S_IRUSR, pdentry, NULL, &dbg_ddrmax_fops);
	(void) debugfs_create_file("ddrmin", S_IRUSR, pdentry, NULL, &dbg_ddrmin_fops);
	(void) debugfs_create_file("ddrsafe", S_IRUSR, pdentry, NULL, &dbg_ddrsafe_fops);
#endif

	pr_info("[%s] %d leave.\n", __func__, __LINE__);

	return status;
}

/*****************************************************************
* function:    lowpm_test_remove
* description:
*  driver interface.
******************************************************************/
static int lowpm_test_remove(struct platform_device *pdev)
{
	return 0;
}

#ifdef CONFIG_PM

static int lowpm_test_suspend(struct platform_device *pdev,
	pm_message_t state)
{
	g_suspended = 1;
	return 0;
}

static int lowpm_test_resume(struct platform_device *pdev)
{
	g_suspended = 0;
	return 0;
}
#else
#define lowpm_test_suspend	NULL
#define lowpm_test_resume	NULL
#endif

#define MODULE_NAME		"lowpm_test"

static struct platform_driver lowpm_test_drv = {
	.probe		= lowpm_test_probe,
	.remove		= __devexit_p(lowpm_test_remove),
	.suspend	= lowpm_test_suspend,
	.resume		= lowpm_test_resume,
	.driver = {
		.name	= MODULE_NAME,
		.owner	= THIS_MODULE,
	},
};

static struct platform_device lowpm_test_device = {
	.id		= 0,
	.name	= MODULE_NAME,
};

#ifdef CONFIG_IPPS_SUPPORT
static void ippsclient_add(struct ipps_device *device)
{
}

static void ippsclient_remove(struct ipps_device *device)
{
}

static struct ipps_client ipps_client = {
	.name   = "lowpmreg",
	.add    = ippsclient_add,
	.remove = ippsclient_remove
};
#endif

static int __init lowpmreg_init(void)
{
	int ret = 0;
	pr_info("[%s] %d enter.\n", __func__, __LINE__);

	ret = platform_driver_register(&lowpm_test_drv);
	if (0 != ret)
		pr_info("%s, %d, err=%x\n", __func__, __LINE__, ret);

	ret = platform_device_register(&lowpm_test_device);
	if (0 != ret)
		pr_info("%s, %d, err=%x\n", __func__, __LINE__, ret);

#ifdef CONFIG_IPPS_SUPPORT
	ret = ipps_register_client(&ipps_client);
#endif
    gdbgipps_param_stru.ipps_param = &gdbgipps_param;
	pr_info("[%s] %d leave.\n", __func__, __LINE__);

	return ret;
}

static void __exit lowpmreg_exit(void)
{
	pr_info("%s %d enter.\n", __func__, __LINE__);

	platform_driver_unregister(&lowpm_test_drv);

	platform_device_unregister(&lowpm_test_device);

#ifdef CONFIG_IPPS_SUPPORT
	ipps_unregister_client(&ipps_client);
#endif

	pr_info("%s %d leave.\n", __func__, __LINE__);
}
#endif /*CONFIG_DEBUG_FS*/

#else

static int __init lowpmreg_init(void)
{
	g_sc_addr		= (void __iomem *) IO_ADDRESS(REG_BASE_SCTRL);
	g_pctrl_addr	= (void __iomem *) IO_ADDRESS(REG_BASE_PCTRL);
	g_pmuspi_addr	= (void __iomem *) IO_ADDRESS(REG_BASE_PMUSPI);
	return 0;
}

static void __exit lowpmreg_exit(void)
{
}

#endif

module_init(lowpmreg_init);
module_exit(lowpmreg_exit);

MODULE_LICENSE("GPL");
