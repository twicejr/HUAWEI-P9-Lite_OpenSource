#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/notifier.h>
#include <linux/pm_qos.h>

#include <linux/debugfs.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/of_device.h>
#include <linux/of_address.h>

#include <linux/hisi/hi3xxx_mailbox.h>

#define MODULE_NAME	"hisilicon,lowpowerm3"
#define WDOGCTRL_OFFSET		0x08
#define WDOGLOCK_OFFSET		0xC00
#define SCDEEPSLEEPED_OFFSET	0x300
#define HRST_OFFSET		(0x115 << 2)
#define SCLPM3RSTEN_OFFSET	0x504
#define SCLPM3RSTDIS_OFFSET	0x508
#define SCLPM3CTRL_OFFSET	0x510

#define REG_UNLOCK_KEY		0x1ACCE551

struct hisi_lpm3 {
	void __iomem		*lpram_base;
	void __iomem		*pmu_base;
	void __iomem 		*sysctrl_base;
	int			irq;
	struct platform_device	*pdev;
	struct delayed_work	wd_worker;
	struct clk		*clk;
};

#ifdef CONFIG_HISI_LPM3_DEBUG
#define MAX_CMD		4
#define MAX_OBJ		16
#define MAX_TYPE	13

static struct dentry *lpm3_debug_dir = NULL;
static struct dentry *lpm3_test = NULL;
unsigned int display_mailbox_rec;

char *cmd[MAX_CMD] = {"on", "off", "get", "set"};
char *obj[MAX_OBJ] = {"ap ", "a7 ", "a15 ", "gpu ", "ddr ", "asp ", "hifi ",
		"iom3 ", "lpm3 ", "modem ", "sys ", "hkadc ",
		"regulator ", "clock ", "temp ", "coul"};
char *type[MAX_TYPE] = {"power ", "clk ", "core ", "cluster ", "sleep ",
		"sr ", "mode ", "uplimit ", "dnlimit ","freq ",
		"T ", "volt ", "test "};

static struct notifier_block *nb;
static struct notifier_block *nb_nor;
static struct hisi_mbox *mbox;
static struct hisi_mbox *mbox_nor;

static void hisi_mbox_complete(struct hisi_mbox_task *tx_task);

struct hisi_lpm3_hs3630_mbox_work {
	struct hisi_mbox_task *tx_task;
	struct work_struct work;
	struct hisi_mbox *p;
};

static int hisi_mbox_mbox_notifier(struct notifier_block *nb, unsigned long len, void *msg)
{
	unsigned int *_msg = (unsigned int *)msg;
	unsigned long i;

	if (display_mailbox_rec) {
		pr_info("%s: receive mail\n", MODULE_NAME);
		for (i = 0; i < len; i++)
			pr_info("msg[%d] = 0x%x\n", (int)i, _msg[i]);
	}

	return 0;
}

static void hisi_mbox_complete(struct hisi_mbox_task *tx_task)
{
	struct hisi_lpm3_hs3630_mbox_work *dwork = NULL;
	int i;

	if (display_mailbox_rec) {
		pr_debug("%s: tx complete, tx error[%d], ack msg:\n", MODULE_NAME, tx_task->tx_error);
		for (i = 0; i < tx_task->ack_buffer_len; i++)
			pr_debug("msg[%d] = 0x%x\n", i, tx_task->ack_buffer[i]);
	}

	if (tx_task->tx_buffer)
		kfree((void *)tx_task->tx_buffer);
	tx_task->tx_buffer = NULL;

	dwork = (struct hisi_lpm3_hs3630_mbox_work *)tx_task->context;
	if (dwork)
		dwork->tx_task = NULL;

	hisi_mbox_task_free(&tx_task);
	return;
}

static int hisi_lpm3_debugfs_show(struct seq_file *s, void *data)
{
	pr_debug("%s: %s\n", MODULE_NAME, __FUNCTION__);
	return 0;
}

static int hisi_lpm3_debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, hisi_lpm3_debugfs_show, inode->i_private);
}

static ssize_t hisi_lpm3_debugfs_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct hisi_mbox_task *tx_task = NULL;
	char *debug_cmd = NULL;
	u32 result;
	u32 *msg;
	u32 len = 0;
	s32 ret, i, j;

	ret = 0;

	debug_cmd = kzalloc(sizeof(char) * count, GFP_KERNEL);
	if (!debug_cmd) {
		pr_err("%s: cannot allocate hisi lpm3 debugfs cmd.\n", MODULE_NAME);
		goto out;
	}

	msg = kzalloc(sizeof(u32) * 8, GFP_KERNEL);
	if (!msg) {
		pr_err("%s: cannot allocate msg space.\n", MODULE_NAME);
		goto alloc_msg_err;
	}

	memcpy(debug_cmd, buf, count - 1);

	debug_cmd[count - 1] = '\0';
	pr_info("%s: [cmd: %s[count: %d]]\n", MODULE_NAME, debug_cmd, count);

	for (i = 0; i < MAX_OBJ; i++) {
		if (!strncmp(obj[i], debug_cmd + len, strlen(obj[i]))) {
			len += strlen(obj[i]);
			msg[0] |= (i << 16);
			break;
		}
	}
	if (i == MAX_OBJ ) {
		pr_err("error, no such obj\n");
		goto mem_err;
	}

	for (i = 0; i < MAX_TYPE; i++) {
		if (!strncmp(type[i], debug_cmd + len, strlen(type[i]))) {
			len += strlen(type[i]);
			msg[0] |= (i + 1);
			break;
		}
	}
	if (i == MAX_TYPE ) {
		pr_err("error, no such cmd type\n");
		goto mem_err;
	}

	for (i = 0; i < MAX_CMD; i++) {
		if (!strncmp(cmd[i], debug_cmd + len, strlen(cmd[i]))) {
			len += strlen(cmd[i]);
			msg[0] |= (i << 8);
			break;
		}
	}
	if (i == MAX_CMD ) {
		pr_err("error, no such cmd\n");
		goto mem_err;
	}

	len++;
	j = 1;
	while (len < count && j < 8) {
		for (i = len; i < count; i++) {
			if (debug_cmd[i] == ' ') {
				debug_cmd[i] = '\0';
				break;
			}
		}
		ret = kstrtou32(debug_cmd + len, 0, &result);
		if (ret != 0) {
			goto mem_err;
		}
		msg[j++] = result;
		len = i + 1;
	}

	pr_info("0x%x,0x%x\n",msg[0], msg[1]);

	pr_info("%s: %s\n", MODULE_NAME, debug_cmd);

	tx_task = hisi_mbox_task_alloc(mbox,
				HI3630_MAILBOX_RP_LPM3,
				msg,
				8,
				1,
				hisi_mbox_complete,
				NULL);

	hisi_mbox_msg_send_async(mbox, tx_task);
	
mem_err:
	kfree(msg);
alloc_msg_err:
	kfree(debug_cmd);
out:
	return count;
}

static const struct file_operations hisi_lpm3_debugfs_fops =
{
	.open		= hisi_lpm3_debugfs_open,
	.read		= seq_read,
	.write		= hisi_lpm3_debugfs_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};
#endif

static void hisi_lpm3_watchdog_workqueue_handler(struct work_struct *work)
{
	struct hisi_lpm3 *lpm3 = container_of(to_delayed_work(work), struct hisi_lpm3, wd_worker);
	/* record lpm3 */
	writel(2, lpm3->pmu_base + HRST_OFFSET);
}

#ifndef CONFIG_ARM_SP805_WATCHDOG
static irqreturn_t hisi_lpm3_watchdog_irq(int irq, void *args)
{
	unsigned int value;
	struct hisi_lpm3 *lpm3 = (struct hisi_lpm3 *) args;
	struct device *dev = &lpm3->pdev->dev;

	/* generate NMI irq */
	value = readl(lpm3->sysctrl_base + SCLPM3CTRL_OFFSET);
	value |= 0x04;
	writel(value, lpm3->sysctrl_base + SCLPM3CTRL_OFFSET);
	value &= ~0x04;
	writel(value, lpm3->sysctrl_base + SCLPM3CTRL_OFFSET);

	dev_err(dev, "lpm3 watchdog timeout! lpm3 die T_T\n");
	schedule_delayed_work(&lpm3->wd_worker, msecs_to_jiffies(5000));
	return IRQ_HANDLED;
}
#endif

static int hisi_lpm3_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = NULL;
	struct hisi_lpm3 *lpm3 = NULL;
	int ret = 0;
#ifdef CONFIG_HISI_LPM3_DEBUG
	display_mailbox_rec = 0;
#endif
	lpm3 = devm_kzalloc(dev, sizeof(struct hisi_lpm3), GFP_KERNEL);
	if (lpm3 == NULL) {
		dev_err(dev, "cannot get memory\n");
		return -ENOMEM;
	}

	np = of_find_compatible_node(NULL, NULL, MODULE_NAME);
	if (np == NULL) {
		dev_err(dev, "Failed to find device node!\n");
		return -ENODEV;
	}

	lpm3->lpram_base = of_iomap(np, 0);
	if (lpm3->lpram_base == NULL) {
		dev_err(dev, "Failed to get lpram base!\n");
		return -ENXIO;
	}

	lpm3->pmu_base = of_iomap(np, 1);
	if (lpm3->pmu_base == NULL) {
		dev_err(dev, "Failed to get pmu base!\n");
		return -ENXIO;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (np == NULL) {
		dev_err(dev, "Failed to find sysctrl device node!\n");
		return -ENODEV;
	}

	lpm3->sysctrl_base = of_iomap(np, 0);
	if (lpm3->sysctrl_base == NULL) {
		dev_err(dev, "Failed to get sysctrl base!\n");
		return -ENXIO;
	}

	lpm3->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(lpm3->clk)) {
		dev_err(dev, "no dma clk\n");
		return PTR_ERR(lpm3->clk);
        }

	ret = clk_prepare_enable(lpm3->clk);
	if (ret < 0) {
		dev_err(dev, "clk_prepare_enable failed: %d\n", ret);
		return -EINVAL;
	}

	lpm3->irq = platform_get_irq(pdev, 0);
	if (lpm3->irq < 0) {
		dev_err(dev, "cannot find IRQ\n");
		return lpm3->irq;
	}

	INIT_DELAYED_WORK(&lpm3->wd_worker, hisi_lpm3_watchdog_workqueue_handler);
#ifndef CONFIG_ARM_SP805_WATCHDOG
	ret = devm_request_irq(dev, lpm3->irq, hisi_lpm3_watchdog_irq, IRQF_DISABLED, dev_name(dev), lpm3);
	if (ret < 0) {
		dev_err(dev, "cannot claim IRQ\n");
		return ret;
	}
#endif

#ifdef CONFIG_HISI_LPM3_DEBUG
	nb = (struct notifier_block *)devm_kzalloc(dev, sizeof(struct notifier_block), GFP_KERNEL);
	if (!nb) {
		return -ENOMEM;
	}

	nb_nor = (struct notifier_block *)devm_kzalloc(dev, sizeof(struct notifier_block), GFP_KERNEL);
	if (!nb_nor) {
		return -ENOMEM;
	}

	nb->next = NULL;
	nb->notifier_call = hisi_mbox_mbox_notifier;

	nb_nor->next = NULL;
	nb_nor->notifier_call = hisi_mbox_mbox_notifier;

	mbox = hisi_mbox_get(HI3630_MAILBOX_RP_LPM3, nb);
	if (!mbox) {
		return -ENODEV;
	}

	mbox_nor = hisi_mbox_get(HI3630_MAILBOX_RP_UNCERTAIN, nb_nor);
	if (!mbox_nor) {
		hisi_mbox_put(&mbox);
		return -ENODEV;
	}
	lpm3_debug_dir = debugfs_create_dir("hisi_lpm3_debug", NULL);
	if (lpm3_debug_dir)
		lpm3_test = debugfs_create_file("lpm3_test", S_IRUSR, lpm3_debug_dir, NULL, &hisi_lpm3_debugfs_fops);
#endif
	lpm3->pdev = pdev;
	platform_set_drvdata(pdev, lpm3);

	return 0;
}

static int hisi_lpm3_remove(struct platform_device *pdev)
{
	struct hisi_lpm3 *lpm3 = platform_get_drvdata(pdev);

	clk_disable_unprepare(lpm3->clk);
	free_irq(lpm3->irq, NULL);
	kfree(lpm3);
#ifdef CONFIG_HISI_LPM3_DEBUG
	hisi_mbox_put(&mbox);
	hisi_mbox_put(&mbox_nor);
	kfree(nb);
	kfree(nb_nor);
#endif
	return 0;
}

static const struct of_device_id lpm3_match[] = {
	{ .compatible = MODULE_NAME },
	{},
};
MODULE_DEVICE_TABLE(of, lpm3_match);

static struct platform_driver hisi_lpm3_driver = {
	.driver = {
		.name = MODULE_NAME,
		.of_match_table = of_match_ptr(lpm3_match),
	},
	.probe = hisi_lpm3_probe,
	.remove = hisi_lpm3_remove,
};

static int __init hisi_lpm3_init(void)
{
	return platform_driver_register(&hisi_lpm3_driver);
}
module_init(hisi_lpm3_init);

static void __exit hisi_lpm3_exit(void)
{
	platform_driver_unregister(&hisi_lpm3_driver);
}
module_exit(hisi_lpm3_exit);


MODULE_AUTHOR("wangtao.jean@huawei.com>");
MODULE_DESCRIPTION(" LOW POWER M3 DRIVER");
MODULE_LICENSE("GPL");
