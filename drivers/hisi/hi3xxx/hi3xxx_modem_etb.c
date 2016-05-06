#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>

#define BVAL(val, n)			(((val) & BIT((n))) >> (n))

#define TOP_ETB_REG_BASE		(0xEC036000)
#define TOP_FUNNEL_REG_BASE		(0xEC031000)


#define REG_UNLOCK				(0xc5acce55)
#define ETB_DATA_SIZE			(0x4000)

#define coresight_writel(val, reg)	__raw_writel(val, reg)
#define coresight_readl( reg)		__raw_readl(reg)

struct hisi_etb_drvdata {
	void __iomem *base;
	struct device *dev;
	struct regulator_bulk_data top_cssys_regu;
	spinlock_t spinlock;
};

static struct hisi_etb_drvdata *g_drvdata;
static char ETB_DATA_BUFFER[ETB_DATA_SIZE] = {0};

static void __iomem *g_top_etb_base;
static void __iomem *g_top_funnel_base;

char *etb_file_path;
#define MAX_ETB_FILE_LEN (128)

static void save_tmc_data(void)
{
	int fd;
	long bytes;
	mm_segment_t old_fs;
	char new_filename[MAX_ETB_FILE_LEN] = {0};

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	memset(new_filename, 0, sizeof(new_filename));
	snprintf(new_filename, sizeof(new_filename), "%setb.bin", etb_file_path);

	fd = sys_creat(new_filename, 0755);
	if (fd < 0) {
		pr_err("<%s()>, create file failed! fd(%d)\n", __func__, fd);
		set_fs(old_fs);
		return;
	}

	bytes = sys_write((unsigned int)fd, ETB_DATA_BUFFER, ETB_DATA_SIZE);
	if ((u32)bytes != ETB_DATA_SIZE) {
		pr_err("<%s()>, write data failed(write length not equal:0x%x)\n", __func__, (int)bytes);
		sys_close(fd);
		set_fs(old_fs);
		return;
	}

	sys_fsync(fd);
	sys_close(fd);
	set_fs(old_fs);
	pr_info("<%s()>, save etb file %s success!\n", __func__, new_filename);

	return;
}

static int debug_coresight_poweron(void)
{
	int ret;

	ret = regulator_bulk_enable(1, &(g_drvdata->top_cssys_regu));
	if (ret) {
		printk("failed to enable regulators %d\n", ret);
		return -1;
	}

	return 0;
}

static int debug_coresight_poweroff(void)
{
	if (regulator_is_enabled(g_drvdata->top_cssys_regu.consumer)) {
		//regulator_bulk_disable(1, &(g_drvdata->top_cssys_regu));
	}

	return 0;
}

void debug_coresight_init(void)
{
	printk("%s: ++\n", __func__);

	g_top_etb_base = ioremap(TOP_ETB_REG_BASE, 0x1000);
	g_top_funnel_base = ioremap(TOP_FUNNEL_REG_BASE, 0x1000);

	printk("%s: --\n", __func__);
	return;
}

void debug_coresight_deinit(void)
{
	printk("%s: ++\n", __func__);

	iounmap(g_top_etb_base);
	iounmap(g_top_funnel_base);

	printk("%s: --\n", __func__);
	return;
}


void debug_coresight_regdump(void)
{
	unsigned long flags;

	spin_lock_irqsave(&g_drvdata->spinlock, flags);
	printk("TOP_ETB: off: 0x%x, val: 0x%x\n", 0x28, coresight_readl(g_top_etb_base + 0x28));
	printk("TOP_ETB: off: 0x%x, val: 0x%x\n", 0x304, coresight_readl(g_top_etb_base + 0x304));
	printk("TOP_ETB: off: 0x%x, val: 0x%x\n", 0x1c, coresight_readl(g_top_etb_base + 0x1c));
	printk("TOP_ETB: off: 0x%x, val: 0x%x\n", 0x20, coresight_readl(g_top_etb_base + 0x20));
	printk("TOP_FUNNEL: off: 0x%x, val: 0x%x\n", 0x0, coresight_readl(g_top_funnel_base + 0x0));
	printk("TOP_FUNNEL: off: 0x%x, val: 0x%x\n", 0x04, coresight_readl(g_top_funnel_base + 0x04));
	spin_unlock_irqrestore(&g_drvdata->spinlock, flags);
}

#ifdef CONFIG_HI3XXX_MODEM_ETB
void top_tmc_enable(void)
{
	unsigned long flags;
	uint32_t read_data;

	printk("%s: ++\n", __func__);
	if (debug_coresight_poweron())
	{
		printk("%s: failed to power on topcssys!\n", __func__);
		return;
	}

	spin_lock_irqsave(&g_drvdata->spinlock, flags);

	/*unlock top_eft and top_funnel*/
	coresight_writel(REG_UNLOCK, g_top_etb_base + 0xFB0);
	coresight_writel(REG_UNLOCK, g_top_funnel_base + 0xFB0);
	mb();

	/*setup for top etb regs*/
	coresight_writel(0x0, g_top_etb_base + 0x28);
	coresight_writel(0x133, g_top_etb_base + 0x304);
	coresight_writel(0x0, g_top_etb_base + 0x1c);
	coresight_writel(0x1, g_top_etb_base + 0x20);

	/*setup for top funnel regs*/
	read_data = coresight_readl(g_top_funnel_base + 0x0);
	read_data &= ~0xF00;
	read_data |= (0x7 << 8);
	read_data |= (0x1 << 3);
	coresight_writel(read_data, g_top_funnel_base + 0x0);
	coresight_writel(0x0, g_top_funnel_base + 0x04);

	mb();

	/*lock top_eft and top_funnel*/
	coresight_writel(0x0, g_top_etb_base + 0xFB0);
	coresight_writel(0x0, g_top_funnel_base + 0xFB0);

	spin_unlock_irqrestore(&g_drvdata->spinlock, flags);
	printk("%s: --\n", __func__);
}
#else
void top_tmc_enable(void){}
#endif

EXPORT_SYMBOL_GPL(top_tmc_enable);


void debug_coresight_disable(void)
{
	int count, i;
	uint32_t ffcr;
	uint32_t read_data;
	unsigned long flags;

	printk("%s: ++\n", __func__);

	memset(ETB_DATA_BUFFER, 0x0, 0x4000);

	spin_lock_irqsave(&g_drvdata->spinlock, flags);

	/*unlock top_eft and top_funnel*/
	coresight_writel(REG_UNLOCK, g_top_etb_base + 0xFB0);
	coresight_writel(REG_UNLOCK, g_top_funnel_base + 0xFB0);
	mb();

	/*disable funnel*/
	read_data = coresight_readl(g_top_funnel_base + 0x0);
	read_data &= ~(0x1 << 3);
	coresight_writel(read_data, g_top_funnel_base + 0x0);

	/*stop and flush etb*/
	ffcr = coresight_readl(g_top_etb_base + 0x304);
	ffcr |= BIT(12);
	coresight_writel(ffcr, g_top_etb_base + 0x304);
	ffcr |= BIT(6);
	coresight_writel(ffcr, g_top_etb_base + 0x304);

	for (count = 5000000; (BVAL(coresight_readl(g_top_etb_base + 0x304), 6) != 0 && count > 0); count--)
		udelay(1);
	if (count == 0)
		printk( "timeout while flushing TMC, TMC_FFCR: %#x\n", coresight_readl(g_top_etb_base + 0x304));

	for (count = 5000000; (BVAL(coresight_readl(g_top_etb_base + 0x0c), 2) != 1 && count > 0); count--)
		udelay(1);
	if (count == 0)
		printk("timeout while waiting for TMC ready, TMC_STS: %#x\n", coresight_readl(g_top_etb_base + 0x0c));

	/*dump etb data*/
	for (i = 0; i < 0x4000;) {
		read_data = coresight_readl(g_top_etb_base + 0x10);
		if (read_data == 0xFFFFFFFF)
			break;
		memcpy(&ETB_DATA_BUFFER[i], &read_data, 4);
		i += 4;
	}

	/*disable etb*/
	coresight_writel(0x0, g_top_etb_base + 0x20);

	mb();
	/*lock top_eft and top_funnel*/
	coresight_writel(0, g_top_etb_base + 0xFB0);
	coresight_writel(0, g_top_funnel_base + 0xFB0);

	spin_unlock_irqrestore(&g_drvdata->spinlock, flags);

	debug_coresight_poweroff();

	/*save etb data to file*/
	save_tmc_data();
	printk("%s: --\n", __func__);
}

#ifdef CONFIG_HI3XXX_MODEM_ETB
void top_tmc_disable(char *pdir)
{
	if (MAX_ETB_FILE_LEN < strlen(pdir) + 1) {
		pr_err("ETB: file length is wrong(%d).\n", (int)strlen(pdir));
		return;
	}
	etb_file_path = kmalloc(MAX_ETB_FILE_LEN, GFP_KERNEL);
	if (etb_file_path == NULL) {
		pr_err("etb:kmalloc mem failed\n");
		return;
	}
	strncpy(etb_file_path, pdir, strlen(pdir) + 1);

	debug_coresight_disable();

	kfree(etb_file_path);

	etb_file_path = NULL;
}
#else
void top_tmc_disable(char *pdir){}
#endif

EXPORT_SYMBOL_GPL(top_tmc_disable);

static int hisi_etb_init_map(void)
{
	debug_coresight_init();
	return 0;
}

static int hisi_etb_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct device *dev = &pdev->dev;
	struct hisi_etb_drvdata *drvdata = NULL;

	printk("%s: ++\n", __func__);
	drvdata = devm_kzalloc(dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata) {
		printk("kzalloc error!\n");
		return -ENOMEM;
	}

	drvdata->dev = &pdev->dev;
	platform_set_drvdata(pdev, drvdata);

	drvdata->top_cssys_regu.supply = "top_cssys";
	ret = devm_regulator_bulk_get(dev, 1, &(drvdata->top_cssys_regu));
	if (ret) {
		printk("couldn't get regulators %d\n",ret);
		return -1;
	}

	spin_lock_init(&drvdata->spinlock);

	g_drvdata = drvdata;

	hisi_etb_init_map();

	printk("%s: --\n", __func__);
	return ret;
}

static int  hisi_etb_suspend(struct platform_device *pdev, pm_message_t message)
{
	struct hisi_etb_drvdata *drvdata = platform_get_drvdata(pdev);

	if(NULL == drvdata)
		return -1;
	
	dev_info(drvdata->dev, "+++\n");

	dev_info(drvdata->dev, "---\n");

	return 0;
}

static int  hisi_etb_resume(struct platform_device *pdev)
{
	struct hisi_etb_drvdata *drvdata = platform_get_drvdata(pdev);

	if(NULL == drvdata)
		return -1;

	dev_info(drvdata->dev, "+++\n");

	dev_info(drvdata->dev, "---\n");

	return 0;
}

static int  hisi_etb_remove(struct platform_device *pdev)
{
	debug_coresight_deinit();
	return 0;
}


static struct of_device_id hisi_etb_match[] = {
	{.compatible = "hisilicon,modem-etb"},
	{}
};

static struct platform_driver hisi_etb_driver = {
	.probe          = hisi_etb_probe,
	.remove         = hisi_etb_remove,
	.suspend	= hisi_etb_suspend,
	.resume		= hisi_etb_resume,
	.driver         = {
		.name   = "hisilicon,modem-etb",
		.owner	= THIS_MODULE,
		.of_match_table = hisi_etb_match,
	},
};

int __init hisi_etb_init(void)
{
	return platform_driver_register(&hisi_etb_driver);
}
module_init(hisi_etb_init);

void __exit hisi_etb_exit(void)
{
	platform_driver_unregister(&hisi_etb_driver);
}
module_exit(hisi_etb_exit);

MODULE_DESCRIPTION("Seattle etb feature for modem.");
MODULE_LICENSE("GPL");
