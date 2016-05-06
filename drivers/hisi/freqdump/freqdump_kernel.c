#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/seq_file.h>
 #include <linux/errno.h>
#include "../../atfdriver/atfdriver.h"

#include <linux/kthread.h>
#include <linux/mutex.h>
#include <linux/delay.h>


#define FREQDUMP_BUFF_SIZE			400
#define LOADMONITOR_BUFF_SIZE			150
#define OK					0
#define FREQDUMP_DATA_PHY_ADDR_BASE		0x34A21000
#define FREQDUMP_DATA_PHY_ADDR_SIZE	  0x400

#define ACCESS_REGISTER_FN_SUB_ID_FREQDUMP_R   (0x55bbcce5)
#define ACCESS_REGISTER_FN_MAIN_ID		(0xc500aa01)

#define MAX_MONITOR_IP_DEVICE 32

static void __iomem *freqdump_virt_addr;
static char freqdump_buf[FREQDUMP_BUFF_SIZE];
static char loadmonitor_buf[LOADMONITOR_BUFF_SIZE];
struct dentry *freqdump_debugfs_root;
struct freqdump_data {
	unsigned int apll[3][2];
	unsigned int a53_l_pllsel;
	unsigned int a53_b_pllsel;
	unsigned int ppll[4][2];
	unsigned int g3dclksel;
	unsigned int g3dclkdiv;
	unsigned int g3dclkdiv_stat;
	unsigned int ddrpllsel;
	unsigned int ddrclkdiv;
	unsigned int peri_usage[3];
	unsigned int dmss_asi_status;
	unsigned int dmc0_curr_sta;
	unsigned int dmc0_ddrc_cfg_wm;
	unsigned int dmc0_flux_wr;
	unsigned int dmc0_flux_rd;
	unsigned int dmc0_ddrc_intsts;
	unsigned int dmc0_tmon_aref;
	unsigned int dmc1_curr_sta;
	unsigned int dmc1_flux_wr;
	unsigned int dmc1_flux_rd;
	unsigned int dmc2_curr_sta;
	unsigned int dmc2_flux_wr;
	unsigned int dmc2_flux_rd;
	unsigned int dmc3_curr_sta;
	unsigned int dmc3_flux_wr;
	unsigned int dmc3_flux_rd;
	unsigned int qosbuf0_cmd;
	unsigned int qosbuf1_cmd;
	unsigned int a53_b_temp;
	unsigned int a53_l_temp;
	unsigned int gpu_temp;
	unsigned int peri_temp;
	unsigned int ddr_temp;
	unsigned int a53_b_buck;
	unsigned int a53_b_vol;
	unsigned int a53_l_buck;
	unsigned int a53_l_vol;
	unsigned int gpu_buck;
	unsigned int gpu_vol;
	unsigned int ddr_vol;
	unsigned int peri_vol;
	unsigned int battery_vol;
	unsigned int battery_current;
	unsigned int socid;
};

struct freqdump_data *freqdump_read_data;

unsigned int loadmonitor_load[32] = {0};

/****** all FREQDUMP service function id start ******/
/* General and test func */
#define FREQDUMP_SVC_CALL_COUNT       0xC7000000
#define FREQDUMP_SVC_UID              0xC7000001
#define FREQDUMP_SVC_VERSION          0xC7000002

#define FREQDUMP_SVC_REG_RD						0xC700EE00
#define FREQDUMP_LOADMONITOR_SVC_REG_RD			0xC700EE01
#define FREQDUMP_LOADMONITOR_SVC_ENABLE			0xC700EE02
#define FREQDUMP_LOADMONITOR_SVC_DISABLE		0xC700EE03
/****** all FREQDUMP service function id end ******/

unsigned int freqdump_atoi(char *str)
{
	int result = 0;
	bool symbol = false;
	if (str == NULL)
		return -2;

	if (((*str > '9') || (*str < '0')) && ((*str == '-') || (*str == '+'))) {
		if ((*str) == '-') {
			symbol = true;
			str++;
		}
	}
	while ((*str) != '\0') {
		if ((*str > '9') || (*str < '0'))
			return -2;
		else
			result = result*10 + ((*str) - '0');
		str++;
	}
	if ((*str) != '\0')
		return -2;
	return symbol ? -result : result;

}

noinline int atfd_hisi_service_freqdump_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
	asm volatile (
		__asmeq("%0", "x0")
		__asmeq("%1", "x1")
		__asmeq("%2", "x2")
		__asmeq("%3", "x3")
		"smc	#0\n"
		: "+r" (function_id)
		: "r" (arg0), "r" (arg1), "r" (arg2));

    return (int)function_id;
}


void hisi_sec_freqdump_read(void)
{
	(void)atfd_hisi_service_freqdump_smc(FREQDUMP_SVC_REG_RD, 0, 0, 0);
}

void hisi_sec_loadmonitor_data_read(void)
{
	(void)atfd_hisi_service_freqdump_smc(FREQDUMP_LOADMONITOR_SVC_REG_RD, 0, 0, 0);
}

void hisi_sec_loadmonitor_switch_enable(int delay_value)
{
	(void)atfd_hisi_service_freqdump_smc(FREQDUMP_LOADMONITOR_SVC_ENABLE, delay_value, 0, 0);
}

void hisi_sec_loadmonitor_switch_disable(void)
{
	(void)atfd_hisi_service_freqdump_smc(FREQDUMP_LOADMONITOR_SVC_DISABLE, 0, 0, 0);
}


static int freqdump_node_dump(struct seq_file *s, void *p)
{
	int ret = 0;
	int pos = 0;
	(void)hisi_sec_freqdump_read();
	memcpy_fromio(freqdump_read_data, (void *)freqdump_virt_addr, sizeof(struct freqdump_data));
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->apll[0][0]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->apll[0][1]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->apll[1][0]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->apll[1][1]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->apll[2][0]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->apll[2][1]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->a53_l_pllsel);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->a53_b_pllsel);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ppll[0][0]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ppll[0][1]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ppll[1][0]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ppll[1][1]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ppll[2][0]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ppll[2][1]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ppll[3][0]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ppll[3][1]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->g3dclksel);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->g3dclkdiv);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->g3dclkdiv_stat);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ddrpllsel);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ddrclkdiv);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", (u32)freqdump_read_data->peri_usage[0]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", (u32)freqdump_read_data->peri_usage[1]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", (u32)freqdump_read_data->peri_usage[2]);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmss_asi_status);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc0_curr_sta);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc0_ddrc_cfg_wm);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc0_flux_wr);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc0_flux_rd);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc0_ddrc_intsts);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc0_tmon_aref);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc1_curr_sta);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc1_flux_wr);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc1_flux_rd);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc2_curr_sta);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc2_flux_wr);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc2_flux_rd);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc3_curr_sta);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc3_flux_wr);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->dmc3_flux_rd);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->qosbuf0_cmd);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->qosbuf1_cmd);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->a53_b_temp);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->a53_l_temp);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->gpu_temp);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->peri_temp);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->a53_b_buck);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->a53_b_vol);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->a53_l_buck);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->a53_l_vol);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->gpu_buck);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->gpu_vol);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->ddr_vol);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->peri_vol);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->battery_vol);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u,", freqdump_read_data->battery_current);
	pos += snprintf(freqdump_buf+pos, FREQDUMP_BUFF_SIZE-pos, "%u", freqdump_read_data->socid);
	ret = seq_printf(s, "%s\n", freqdump_buf);
	if (ret < 0) {
		printk(KERN_ERR "freqdump_buf transfer failed!");
		return -ENOENT;
	}
	return OK;

}


static int loadmonitor_node_dump(struct seq_file *s, void *p)
{
	int ret = 0;
	int pos = 0;
	int i;
	(void)hisi_sec_loadmonitor_data_read();
	memcpy_fromio(loadmonitor_load, (void *)(freqdump_virt_addr + sizeof(struct freqdump_data)), sizeof(loadmonitor_load));
	for (i = 0; i < MAX_MONITOR_IP_DEVICE; i++)
		pos += snprintf(loadmonitor_buf+pos, LOADMONITOR_BUFF_SIZE-pos, "%u|", (u32)loadmonitor_load[i]);
	ret = seq_printf(s, "%s\n", loadmonitor_buf);
	if (ret < 0) {
		printk(KERN_ERR "loadmonitor_buf transfer failed!");
		return -ENOENT;
	}
	return OK;
}

static ssize_t loadmonitor_enable_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	char buf[20];
	int delay_time = 0;

	if (copy_from_user(buf, ubuf, cnt - 1)) {
		printk(KERN_ERR "loadmonitor_switch_write can not copy from user\n");
		return -EINVAL;
	}
	buf[cnt - 1] = '\0';
	delay_time = freqdump_atoi(buf);
	if (delay_time < 0) {
		printk(KERN_ERR "%s not support nagative value", __func__);
		return cnt;
	} else
		(void)hisi_sec_loadmonitor_switch_enable(delay_time);
	return cnt;
}

static ssize_t loadmonitor_disable_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
	char buf[20];


	if (copy_from_user(buf, ubuf, cnt - 1)) {
		printk(KERN_ERR "loadmonitor_switch_write can not copy from user\n");
		return -EINVAL;
	}
	buf[cnt - 1] = '\0';
	if (buf[0] == '1')
		(void)hisi_sec_loadmonitor_switch_disable();
	return cnt;
}

static int loadmonitor_debugfs_node_open(struct inode *inode, struct file *file)
{
	return single_open(file, loadmonitor_node_dump, NULL);
}

static int freqdump_debugfs_node_open(struct inode *inode, struct file *file)
{
	return single_open(file, freqdump_node_dump, NULL);
}


static struct file_operations freqdump_fops = {
	.owner		= THIS_MODULE,
	.open      = freqdump_debugfs_node_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release
};

static struct file_operations loadmonitor_dump_fops = {
	.owner		= THIS_MODULE,
	.open      = loadmonitor_debugfs_node_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release
};

static struct file_operations loadmonitor_enable_fops = {
	.owner		= THIS_MODULE,
	.write      = loadmonitor_enable_write,
};

static struct file_operations loadmonitor_disable_fops = {
	.owner		= THIS_MODULE,
	.write      = loadmonitor_disable_write,
};
struct task_struct *k1;
struct task_struct *k2;
static int __init freqdump_debugfs_init(void)
{
	struct dentry *freqdump_flie;
	struct dentry *loadmonitor_file;
	struct dentry *loadmonitor_enable_file;
	struct dentry *loadmonitor_disable_file;

	printk(KERN_ERR "freqdump init!\n");
	memset(freqdump_buf, 0, sizeof(freqdump_buf));
	memset(loadmonitor_buf, 0, sizeof(loadmonitor_buf));
	freqdump_read_data = kzalloc(sizeof(struct freqdump_data), GFP_KERNEL);
	if (!freqdump_read_data) {
		printk(KERN_ERR "freqdump alloc mem failed!\n");
		return -ENOMEM;
	}
	freqdump_virt_addr = ioremap(FREQDUMP_DATA_PHY_ADDR_BASE, FREQDUMP_DATA_PHY_ADDR_SIZE);
	if (NULL == freqdump_virt_addr) {
		printk(KERN_ERR "freqdump ioremap failed!\n");
		kfree(freqdump_read_data);
		return -ENOMEM;
	}
	freqdump_debugfs_root = debugfs_create_dir("freqdump", NULL);
	if (!freqdump_debugfs_root)
		printk(KERN_ERR "freqdump_debugfs_root init failed!\n");
	freqdump_flie = debugfs_create_file("freqdump_data", 0770, freqdump_debugfs_root, NULL, &freqdump_fops);
	if (!freqdump_flie)
		goto Fail;
	loadmonitor_file = debugfs_create_file("loadmonitor_data", 0770, freqdump_debugfs_root, NULL, &loadmonitor_dump_fops);
	if (!loadmonitor_file)
		goto Fail;
	loadmonitor_enable_file = debugfs_create_file("loadmonitor_enable", 0770, freqdump_debugfs_root, NULL, &loadmonitor_enable_fops);
	if (!loadmonitor_enable_file)
		goto Fail;
	loadmonitor_disable_file = debugfs_create_file("loadmonitor_disable", 0770, freqdump_debugfs_root, NULL, &loadmonitor_disable_fops);
	if (!loadmonitor_disable_file)
		goto Fail;
	return OK;
Fail:
	debugfs_remove_recursive(freqdump_debugfs_root);
	kfree(freqdump_read_data);
	iounmap(freqdump_virt_addr);
	printk(KERN_ERR "freqdump init failed!\n");
	return -ENOENT;
}

static void __exit freqdump_debugfs_exit(void)
{
	debugfs_remove_recursive(freqdump_debugfs_root);
	kfree(freqdump_read_data);
	iounmap(freqdump_virt_addr);
	printk(KERN_ERR "freqdump removed!\n");
}

module_init(freqdump_debugfs_init);
module_exit(freqdump_debugfs_exit);
