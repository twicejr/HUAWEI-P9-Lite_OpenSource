
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/moduleparam.h>
#include <linux/export.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <asm/io.h>
#define DDR_DEBUGFS_PATH 	"lpddr"
#define SCTL_BASE_ADDR    	ioremap(0xF78013A8 , PAGE_ALIGN(SZ_4K))
#define TYPE_LPDDR2         0
#define TYPE_LPDDR3         1

static u32 ddr_type_get(void)
{
	u32 ddr_type = 0;
	u32 sctl_reg_value = 0;

	sctl_reg_value = readw((volatile void *)SCTL_BASE_ADDR);
	printk(KERN_NOTICE "%s sctl_reg_value 0x%x\n", __FUNCTION__, sctl_reg_value);
	
	if(sctl_reg_value & 0x400)
	{
		printk(KERN_NOTICE "%s LPDDR3\n", __FUNCTION__);
		ddr_type = TYPE_LPDDR3;
    }
    else
    {
		printk(KERN_NOTICE "%s LPDDR2\n", __FUNCTION__);
		ddr_type = TYPE_LPDDR2;
    }

	return  ddr_type;
}

static int ddr_info_show(struct seq_file *s, void *data)
{
	const char *str = NULL;
	u32 ddr_type = 0;

	ddr_type = ddr_type_get();
	switch (ddr_type) {
	case TYPE_LPDDR2:
		str = "lpddr2";
		break;
	case TYPE_LPDDR3:
		str = "lpddr3";
		break;
	default:
	    str = "invalid_type";
		break;
	}
	seq_printf(s, "%s\n", str);

	return 0;
}


static int ddr_info_open(struct inode *inode, struct file *file)
{
	return single_open(file, ddr_info_show, inode->i_private);
}

static const struct file_operations ddr_info_fops = {
	.open		= ddr_info_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static void ddr_info_debugfs(void)
{
	struct dentry *root;

	root = debugfs_create_dir(DDR_DEBUGFS_PATH, NULL);
	if (IS_ERR(root))
		/* Don't complain -- debugfs just isn't enabled */
		return;
	if (!root)
		/* Complain -- debugfs is enabled, but it failed to
		 * create the directory. */
		goto err_root;

	if (!debugfs_create_file("lpddr_info", S_IRUSR | S_IRGRP | S_IROTH, root, NULL, &ddr_info_fops))
		goto err_node;

	return;

err_node:
	debugfs_remove_recursive(root);
err_root:
	printk(KERN_ERR "failed to initialize debugfs\n");
}


static int __init ddr_info_init(void)
{
	ddr_info_debugfs();
	return 0;
}

static void __exit ddr_info_exit(void)
{
	;
}


module_init(ddr_info_init);
module_exit(ddr_info_exit);

MODULE_AUTHOR("DRIVER_AUTHOR");
MODULE_DESCRIPTION("DDR INFORMATION");
MODULE_LICENSE("GPL");
