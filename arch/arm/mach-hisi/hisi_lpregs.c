/*
 *	linux/arch/arm/mach-k3v2/irq.c
 *
 * Copyright (C) 2013 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#include <linux/init.h>
#include <linux/cpu_pm.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/clockchips.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/arm-cci.h>
#include <linux/irqchip/arm-gic.h>

#define DEBG_SUSPEND_PRINTK		(1<<0)
#define DEBG_SUSPEND_IO_SHOW	(1<<1)
#define DEBG_SUSPEND_PMU_SHOW	(1<<2)
#define DEBG_SUSPEND_IO_SET		(1<<3)
#define DEBG_SUSPEND_PMU_SET	(1<<4)
#define DEBG_SUSPEND_IO_S_SET	(1<<5)
#define DEBG_SUSPEND_RTC_EN		(1<<6)
#define DEBG_SUSPEND_TIMER_EN	(1<<7)
#define DEBG_SUSPEND_WAKELOCK	(1<<8)
#define DEBG_SUSPEND_AUDIO		(1<<9)

#define REG_SCLPM3CLKEN_OFFSET	(0x500)
#define REG_SCLPM3RSTEN_OFFSET	(0x504)
#define REG_SCLPM3RSTDIS_OFFSET	(0x508)
#define BIT_CLK_UART_SHIFT			(1 << 8)
#define BIT_RST_UART_SHIFT			(1 << 9)

extern bool console_suspend_enabled;

static unsigned g_usavedcfg;
static int g_suspended;
static unsigned g_utimer_inms;
static unsigned g_urtc_ins;

extern int get_console_index(void);


#ifdef CONFIG_HISI_SR_DEBUG

#include <linux/wakelock.h>

static struct wake_lock lowpm_wake_lock;

/* struct sysreg_bases to hold the base address of some system registers.*/
struct sysreg_base_addr {
	void __iomem *uart_base;
	void __iomem *pctrl_base;
	void __iomem *sysctrl_base;
	void __iomem *ioc_base;
	void __iomem *crg_base;
};

struct sysreg_base_addr sysreg_base;

/*map system registers*/
static int map_sysregs(void)
{
	unsigned int uart_idx = 0;
	struct device_node *np = NULL;

	uart_idx = get_console_index();
	switch (uart_idx) {
	case 0:
		np = of_find_compatible_node(NULL, NULL, "arm,pl011");
		break;
	case 6:
		np = of_find_compatible_node(NULL, NULL,  "hisilicon,lowpm_test");
		break;
	default:
		break;
	}

	if (NULL != np) {
		sysreg_base.uart_base = of_iomap(np, 0);
		if (!sysreg_base.uart_base)
			goto err;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	sysreg_base.sysctrl_base = of_iomap(np, 0);
	if (!sysreg_base.sysctrl_base)
		goto err;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pctrl");
	sysreg_base.pctrl_base = of_iomap(np, 0);
	if (!sysreg_base.pctrl_base)
		goto err;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	sysreg_base.crg_base= of_iomap(np, 0);
	if (!sysreg_base.crg_base)
		goto err;

	np = of_find_compatible_node(NULL, NULL, "pinctrl-single");
	sysreg_base.ioc_base = of_iomap(np, 0);
	if (sysreg_base.ioc_base)
		return 0;

err:
	sysreg_base.uart_base = NULL;
	sysreg_base.sysctrl_base = NULL;
	sysreg_base.pctrl_base = NULL;
	sysreg_base.crg_base = NULL;
	sysreg_base.ioc_base = NULL;
	return -ENODEV;
}


/****************************************
*function: debuguart_reinit
*description:
*  reinit debug uart.
*****************************************/
void debuguart_reinit(void)
{
	unsigned int uart_idx = 0;
	unsigned int uregv = 0;

	if ((console_suspend_enabled == 1) || (sysreg_base.uart_base == NULL))
		return;

	uart_idx = get_console_index();
	if (uart_idx == 6) {
		/* Config necessary IOMG configuration */
		writel(0x1, (sysreg_base.ioc_base + 0xF4));
		/*disable clk*/
		uregv = readl(sysreg_base.sysctrl_base + REG_SCLPM3CLKEN_OFFSET) & (~BIT_CLK_UART_SHIFT);
		writel(uregv, (sysreg_base.sysctrl_base + REG_SCLPM3CLKEN_OFFSET));
		/*enable clk*/
		uregv = readl(sysreg_base.sysctrl_base + REG_SCLPM3CLKEN_OFFSET) | (BIT_CLK_UART_SHIFT);
		writel(uregv, (sysreg_base.sysctrl_base + REG_SCLPM3CLKEN_OFFSET));
		/*reset undo*/
		writel(BIT_RST_UART_SHIFT, (sysreg_base.sysctrl_base + REG_SCLPM3RSTEN_OFFSET));
		writel(BIT_RST_UART_SHIFT, (sysreg_base.sysctrl_base + REG_SCLPM3RSTDIS_OFFSET));
	} else if (uart_idx == 0) {
		/* Config necessary IOMG configuration */
		writel(0x2, (sysreg_base.ioc_base + 0xF0));
		uregv = (1 << (uart_idx + 10));
		writel(uregv, (sysreg_base.crg_base + 0x24));
		/*@ enable clk*/
		writel(uregv, (sysreg_base.crg_base + 0x20));
		/*reset undo*/
		writel(uregv, (sysreg_base.crg_base + 0x78));
		writel(uregv, (sysreg_base.crg_base + 0x7C));
	} else {
		return;
	}

	/*@;disable recieve and send*/
	uregv = 0x0;
	writel(uregv, (sysreg_base.uart_base + 0x30));

	/*@;enable FIFO*/
	uregv = 0x70;
	writel(uregv, (sysreg_base.uart_base + 0x2c));

	/*@;set baudrate*/
	uregv = 0xA;
	writel(uregv, (sysreg_base.uart_base + 0x24));

	uregv = 0x1B;
	writel(uregv, (sysreg_base.uart_base + 0x28));

	/*@;clear buffer*/
	uregv = readl(sysreg_base.uart_base);

	/*@;enable FIFO*/
	uregv = 0x70;
	writel(uregv, (sysreg_base.uart_base + 0x2C));

	/*@;set FIFO depth*/
	uregv = 0x10A;
	writel(uregv, (sysreg_base.uart_base + 0x34));

	uregv = 0x50;
	writel(uregv, (sysreg_base.uart_base + 0x38));

	/*@;enable uart trans*/
	uregv = 0x301;
	writel(uregv, (sysreg_base.uart_base + 0x30));
}

#if 0
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

	if (!(g_usavedcfg&DEBG_SUSPEND_TIMER_EN))
		return;

	uregv = readl((utimer0_base + 0x4));

	/*clear timer intr */
	uregv = 1;
	writel(uregv, (utimer0_base+0xc));

	uregv  = readl(usctrl_base);

	uregv = readl(usctrl_base);
	uregv &= ~(SCCTRL_TIMEREN0OV|SCCTRL_TIMEFORCEHIGH);
	uregv |= SCCTRL_TIMEREN0SEL;
	writel(uregv, usctrl_base);

	uregv  = readl(usctrl_base);
}
#endif

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

	g_suspended = 0;

	/*default timer0 wakeup time 500ms*/
	g_utimer_inms = 200;

	/*default rtc wakeup time in 1s*/
	g_urtc_ins = 1;

	map_sysregs();

	wake_lock_init(&lowpm_wake_lock, WAKE_LOCK_SUSPEND, "lowpm_test");

#ifndef CONFIG_HISI_SR_DEBUG_SLEEP
	set_wakelock(1);
#endif

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

#define MODULE_NAME		"hisilicon,lowpm_test"

static const struct of_device_id lowpm_test_match[] = {
	{ .compatible = MODULE_NAME },
	{},
};

static struct platform_driver lowpm_test_drv = {
	.probe		= lowpm_test_probe,
	.remove		= lowpm_test_remove,
	.suspend	= lowpm_test_suspend,
	.resume		= lowpm_test_resume,
	.driver = {
		.name	= MODULE_NAME,
		.of_match_table = of_match_ptr(lowpm_test_match),
	},
};

static int __init lowpmreg_init(void)
{
	return platform_driver_register(&lowpm_test_drv);
}

static void __exit lowpmreg_exit(void)
{
	platform_driver_unregister(&lowpm_test_drv);
}
#endif /*CONFIG_DEBUG_FS*/

#else

static int __init lowpmreg_init(void)
{
	return 0;
}

static void __exit lowpmreg_exit(void)
{
}

#endif

module_init(lowpmreg_init);
module_exit(lowpmreg_exit);
