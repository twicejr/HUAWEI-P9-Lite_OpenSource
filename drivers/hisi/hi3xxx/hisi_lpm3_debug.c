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

#include <linux/hisi/hisi_mailbox.h>
#include <linux/hisi/hisi_rproc.h>

#define MODULE_NAME	"hisilicon,lowpowerm3"

#define MAX_CMD		6
#define MAX_OBJ		20
#define MAX_TYPE	15

static struct dentry *lpm3_debug_dir = NULL;
static struct notifier_block *nb;
unsigned int display_mailbox_rec;

char *cmd[MAX_CMD] = {
	"on",
	"off",
	"get",
	"set",
	"notify",
	"test",
};

char *obj[MAX_OBJ] = {
	"ap",
	"little",
	"big",
	"gpu",
	"ddr",
	"asp",
	"hifi",
	"iom3",
	"lpm3",
	"modem",
	"sys",
	"hkadc",
	"regulator",
	"clock",
	"temp",
	"coul",
	"psci",
	"telemntn",
	"mca",
	"test",
};

char *type[MAX_TYPE] = {
	"power",
	"clk",
	"core",
	"cluster",
	"sleep",
	"sr",
	"mode",
	"uplimit",
	"dnlimit",
	"freq",
	"T",
	"volt",
	"reset",
	"pwc",
	"test",
};


struct hisi_lpm3_mbox_work {
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


static int hisi_lpm3_debugfs_show(struct seq_file *s, void *data)
{
	pr_debug("%s: %s\n", MODULE_NAME, __FUNCTION__);
	return 0;
}

static int hisi_lpm3_debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, hisi_lpm3_debugfs_show, inode->i_private);
}

int parse_para_to_buf(char *cmd, char *argv[], int max_args)
{
	int para_id;

	para_id  = 0;

	while (*cmd != '\0')
	{
		if (para_id >= max_args)
		    break;
		while (*cmd == ' ')
		    cmd++;

		if ('\0' == *cmd)
		    break;

		argv[para_id] = cmd;
		para_id++;

		while ((*cmd != ' ') && (*cmd != '\0'))
		    cmd++;

		if ('\0' == *cmd)
		    break;

		*cmd = '\0';
		cmd++;

	}

	return para_id;
}

static ssize_t hisi_lpm3_debugfs_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	char *debug_cmd = NULL;
	char *argv[10];
	u32 result = 0;
	u32 argc;
	u32 *msg = NULL;
	s32 i, j, ret = 0;
	int rproc_id = 0;
	rproc_id = HISI_RPROC_LPM3_MBX16;

	debug_cmd = kzalloc(sizeof(char) * count, GFP_KERNEL);
	if (!debug_cmd) {
		pr_err("%s: cannot allocate hisi lpm3 debugfs cmd.\n", MODULE_NAME);
		goto msg_err;
	}

	msg = kzalloc(sizeof(u32) * 8, GFP_KERNEL);
	if (!msg) {
		pr_err("%s: cannot allocate msg space.\n", MODULE_NAME);
		goto msg_err;
	}

	memcpy(debug_cmd, buf, count - 1);

	debug_cmd[count - 1] = '\0';
	pr_info("%s: [cmd: %s[count: %d]]\n", MODULE_NAME, debug_cmd, (int)count);

	argc = parse_para_to_buf(debug_cmd, argv, 10);
	if (argc < 3) {
		pr_err("error, arg too few\n");
		goto msg_err;
	}

	for (i = 0; i < MAX_OBJ; i++) {
		if (!strncmp(obj[i], argv[0], strlen(obj[i]))) {
			msg[0] |= (i << 16);
			break;
		}
	}
	if (i == MAX_OBJ) {
		pr_err("error, no such obj\n");
		goto msg_err;
	}

	for (i = 0; i < MAX_TYPE; i++) {
		if (!strncmp(type[i], argv[1], strlen(type[i]))) {
			msg[0] |= (i + 1);
			break;
		}
	}
	if (i == MAX_TYPE) {
		pr_err("error, no such cmd type\n");
		goto msg_err;
	}

	for (i = 0; i < MAX_CMD; i++) {
		if (!strncmp(cmd[i], argv[2], strlen(cmd[i]))) {
			msg[0] |= (i << 8);
			break;
		}
	}
	if (i == MAX_CMD) {
		pr_err("error, no such cmd\n");
		goto msg_err;
	}

	j = 1;
	for (i = 3; i < argc; i++) {
		ret = kstrtou32(argv[i], 0, &result);
		if (ret != 0) {
			goto msg_err;
		}
		msg[j++] = result;
	}

	for (i = 0; i < 8; i++)
		pr_info("0x%x\n",msg[i]);

	pr_info("%s: %s\n", MODULE_NAME, debug_cmd);

	ret = RPROC_ASYNC_SEND(rproc_id, (mbox_msg_t *)msg, 8);
	if (ret)
		pr_err(" %s , line %d, send error\n", __func__, __LINE__);

msg_err:
	if (msg != NULL)
		kfree(msg);

	if (debug_cmd != NULL)
		kfree(debug_cmd);

	return count;
}

int volt_freq_cmd_parse(char *debug_cmd, u32 *msg)
{
	char *argv[3];
	u32 argc, i, len, amplifier = 1, result = 0;
	int ret;

	argc = parse_para_to_buf(debug_cmd, argv, 10);
	if (argc != 3) {
		pr_err("error, arg number not right\n");
		return -1;
	}

	for (i = 1; i < 4; i++) {
		if (!strncmp(obj[i], argv[0], strlen(obj[i]))) {
			msg[1] |= ((i - 1) << 20);
			break;
		}
	}
	if (i == 4) {
		pr_err("error, no such cmd\n");
		return -1;
	}

	ret = kstrtou32(argv[1], 0, &result);
	if (ret != 0 || result > 15) {
		pr_err("para out of range\n");
		return -1;
	}
	msg[1] |= result << 16;

	len = strlen(argv[2]);
	for (i = 0; i < len; i++) {
		if (argv[2][i] == '.') {
			if ((i == 3 || i == 4) && (len - i) == 2) {
				argv[2][i] = argv[2][i+1];
				argv[2][i+1] = '\0';
			} else if (i == 1 && len <= 5) {
				if (argv[2][0] == '0') {
					argv[2] += 2;
				} else {
					argv[2][1] = argv[2][0];
					argv[2]++;
				}
				while (len < 5) {
					amplifier *= 10;
					len++;
				}
			}
			break;
		}
	}

	ret = kstrtou32(argv[2], 0, &result);
	result *= amplifier;
	if (ret != 0 || result > 0xFFFF) {
		pr_err("para out of range\n");
		return -1;
	}
	msg[1] |= result;

	return 0;
}

static ssize_t hisi_lpm3_cluster_volt_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	char *debug_cmd = NULL;
	u32 *msg = NULL;
	s32 i, ret = 0;
	int rproc_id = HISI_RPROC_LPM3_MBX16;

	debug_cmd = kzalloc(sizeof(char) * count, GFP_KERNEL);
	if (!debug_cmd) {
		pr_err("%s: cannot allocate hisi lpm3 debugfs cmd.\n", MODULE_NAME);
		goto msg_err;
	}

	msg = kzalloc(sizeof(u32) * 8, GFP_KERNEL);
	if (!msg) {
		pr_err("%s: cannot allocate msg space.\n", MODULE_NAME);
		goto msg_err;
	}

	msg[1] |= (11 << 24);
	msg[0] = 0x0008030F;

	memcpy(debug_cmd, buf, count - 1);

	debug_cmd[count - 1] = '\0';
	pr_info("%s: [cmd: %s[count: %d]]\n", MODULE_NAME, debug_cmd, (int)count);

	ret = volt_freq_cmd_parse(debug_cmd, msg);
	if (ret)
		goto msg_err;

	for (i = 0; i < 8; i++)
		pr_info("0x%x\n",msg[i]);

	pr_info("%s: %s\n", MODULE_NAME, debug_cmd);

	ret = RPROC_ASYNC_SEND(rproc_id, (mbox_msg_t *)msg, 8);
	if(ret)
		pr_err(" %s , line %d, send error\n", __func__, __LINE__);

msg_err:
	if (msg != NULL)
		kfree(msg);

	if (debug_cmd != NULL)
		kfree(debug_cmd);

	return count;
}

static ssize_t hisi_lpm3_cluster_freq_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
	char *debug_cmd = NULL;
	u32 *msg = NULL;
	s32 i, ret = 0;

	int rproc_id = HISI_RPROC_LPM3_MBX16;

	debug_cmd = kzalloc(sizeof(char) * count, GFP_KERNEL);
	if (!debug_cmd) {
		pr_err("%s: cannot allocate hisi lpm3 debugfs cmd.\n", MODULE_NAME);
		goto msg_err;
	}

	msg = kzalloc(sizeof(u32) * 8, GFP_KERNEL);
	if (!msg) {
		pr_err("%s: cannot allocate msg space.\n", MODULE_NAME);
		goto msg_err;
	}

	msg[1] |= (12 << 24);
	msg[0] = 0x0008030F;

	memcpy(debug_cmd, buf, count - 1);

	debug_cmd[count - 1] = '\0';
	pr_info("%s: [cmd: %s[count: %d]]\n", MODULE_NAME, debug_cmd, (int)count);

	ret = volt_freq_cmd_parse(debug_cmd, msg);
	if (ret)
		goto msg_err;

	i = msg[1] & 0xFFFF;
	if (i < 8000)
		msg[1] = (msg[1] & 0xFFFF0000) | (i * 10);

	for (i = 0; i < 8; i++)
		pr_info("0x%x\n",msg[i]);

	pr_info("%s: %s\n", MODULE_NAME, debug_cmd);

	ret = RPROC_ASYNC_SEND(rproc_id, (mbox_msg_t *)msg, 8);
	if(ret)
		pr_err(" %s , line %d, send error\n", __func__, __LINE__);

msg_err:
	if (msg != NULL)
		kfree(msg);

	if (debug_cmd != NULL)
		kfree(debug_cmd);

	return count;
}

#define MAX_OPS		3

static const struct file_operations hisi_lpm3_debugfs_fops[MAX_OPS] =
{
	{
		.open		= hisi_lpm3_debugfs_open,
		.read		= seq_read,
		.write		= hisi_lpm3_debugfs_write,
		.llseek		= seq_lseek,
		.release	= single_release,
	},
	{
		.open		= hisi_lpm3_debugfs_open,
		.read		= seq_read,
		.write		= hisi_lpm3_cluster_volt_write,
		.llseek		= seq_lseek,
		.release	= single_release,
	},
	{
		.open		= hisi_lpm3_debugfs_open,
		.read		= seq_read,
		.write		= hisi_lpm3_cluster_freq_write,
		.llseek		= seq_lseek,
		.release	= single_release,
	},
};

char *fop_str[MAX_OPS] = {
	"lpm3_test",
	"cluster_volt",
	"cluster_freq",
};

static int __init hisi_lpm3_init(void)
{
	int i, ret = 0;
	int rproc_id = 0;
	rproc_id = HISI_RPROC_LPM3_MBX0;
	display_mailbox_rec = 0;

	nb = (struct notifier_block *)kzalloc(sizeof(struct notifier_block), GFP_KERNEL);
	if (!nb) {
		ret = -ENOMEM;
		goto err_alloc_nb;
	}

	nb->next = NULL;
	nb->notifier_call = hisi_mbox_mbox_notifier;

	/* register the rx notify callback */
	ret = RPROC_MONITOR_REGISTER(rproc_id, nb);
	if (ret)
	{
		pr_info("%s:RPROC_MONITOR_REGISTER failed", __func__);
		goto err_alloc_nb_nor;
	}

	lpm3_debug_dir = debugfs_create_dir("hisi_lpm3_debug", NULL);
	if (lpm3_debug_dir) {
		for (i = 0; i < MAX_OPS; i++) {
			if (NULL == debugfs_create_file(fop_str[i], S_IRUSR, lpm3_debug_dir, NULL, &hisi_lpm3_debugfs_fops[i])) {
				debugfs_remove_recursive(lpm3_debug_dir);
				ret = -ENODEV;
				goto err_alloc_nb_nor;
			}
		}
	} else {
		ret = -ENODEV;
		goto err_alloc_nb_nor;
	}

	return 0;

err_alloc_nb_nor:
	kfree(nb);
err_alloc_nb:
	return ret;
}
fs_initcall(hisi_lpm3_init);

static void __exit hisi_lpm3_exit(void)
{
	int rproc_id = 0;
	rproc_id = HISI_RPROC_LPM3_MBX0;

	/*the HISI_RPROC_LPM3 is a shared channel by many IP, but the exit function should never be used  */
	RPROC_PUT(rproc_id);
	debugfs_remove_recursive(lpm3_debug_dir);
	kfree(nb);
}
module_exit(hisi_lpm3_exit);

MODULE_AUTHOR("wangtao.jean@huawei.com>");
MODULE_DESCRIPTION("LOWPOWER M3 DEBUG DRIVER");
MODULE_LICENSE("GPL");
