#include <linux/types.h>
#include <linux/errno.h>
#include <linux/time.h>

#include <linux/kernel.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/syslog.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <linux/semaphore.h>
#include <linux/completion.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/debugfs.h>
//#include "drv_config.h"
#include "linux/hisi/hi6xxx_ipc_enum.h"
#include "general_sram_map.h"
#include "global_ddr_map.h"
#include <linux/hisi/pm/pwrctrl_multi_dfs.h>
#include <linux/hisi/pm/pwrctrl_multi_def.h>
#include <linux/hisi/pm/hi6xxx-power-common.h>
#include <linux/hisi/pm/hi6xxx-power-dfs.h>
#include <linux/hisi/pm/hi6xxx-power-mca.h>
#include <linux/hisi/hi6xxx-iomap.h>
#include "soc_peri_sctrl_interface.h"

static u8_t *mcushell_buf;
#define  MCUSHELL_BUF_LEN 3072
static int mcushell_node_open(struct inode * inode, struct file * file)
{
	return 0;
}

static int mcushell_node_release(struct inode * inode, struct file * file)
{
	return 0;
}

static ssize_t mcushell_node_read(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
    mcushell_buf[MCUSHELL_BUF_LEN-1] = '\0';
    int len = strlen(mcushell_buf);
    if (copy_to_user(buf, mcushell_buf, len)) {
        printk(KERN_ERR"%s-%s-%d failed\n", __FILE__, __func__, __LINE__);
        memset(mcushell_buf, 0, len);
        return EIO;
    }
    else {
        memset(mcushell_buf, 0, len);
        return len;
    }
}

static ssize_t mcushell_node_write(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos)
{
    union mca_udata_req req;
    union mca_udata_rsp rsp;
    memset(mcushell_buf, 0, MCUSHELL_BUF_LEN);
    count = count > (MCUSHELL_BUF_LEN-1) ? (MCUSHELL_BUF_LEN-1) : count;
    if (copy_from_user(mcushell_buf, buf, count)) {
        printk(KERN_ERR"%s-%s-%d failed\n", __FILE__, __func__, __LINE__);
        return EIO;
    }
#if defined (CONFIG_HISILICON_PLATFORM_POWER_CONTROL)
extern int mca_send(int cmd_id, union mca_udata_req req_data, union mca_udata_rsp* p_rsp_data, int time_out);
    mca_send(MCA_CMD_MCU_SHELL, req, &rsp, 0);
    printk(KERN_ERR"send cmd to mcu (%s)(%s)\n", buf, mcushell_buf);
#endif
    return count;
}

static const struct file_operations mcushell_node_operations = {
	.read		= mcushell_node_read,
    .write      = mcushell_node_write,
	.open		= mcushell_node_open,
	.release	= mcushell_node_release,
};

static int mcushell_debugfs_create(void)
{
    struct dentry *debugfs_root;
    unsigned long base =  (unsigned long)ioremap(SOC_PERI_SCTRL_BASE_ADDR, SZ_4K);
    unsigned int reg_val = readl(base+0xd04);
    printk(KERN_ERR"reg_val : 0x%x\n", reg_val);
    if (((reg_val>>PWC_SWITCH_MCUSHELL) & 0x1) == 0x1)
    {
        debugfs_root = debugfs_create_dir("shell", NULL);
        if (!debugfs_root)
            return (-ENOENT);

        debugfs_create_file("mcushell", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &mcushell_node_operations);
        return 0;
    }
    return 0;

}

static int __init mcushell_node_init(void)
{
    mcushell_buf = ((u8_t *)ioremap(DDR_MCUSHELL_ADDR, MCUSHELL_BUF_LEN));

    mcushell_debugfs_create();
    printk(KERN_ERR"mcushell_node_init success\n");
    return 0;

}

module_init(mcushell_node_init);
