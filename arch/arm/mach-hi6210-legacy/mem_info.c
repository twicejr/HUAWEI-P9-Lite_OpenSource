
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/stat.h>
#include <linux/sysdev.h>
#include <linux/uaccess.h>
#include <mach/hardware.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <asm/mach/map.h>
#include <mach/ddr_map.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <mach/util.h>
#include <mach/ddr_map.h>
#include <linux/seq_file.h>




#define MEM_INFO(name, base, string)\
static int name ## _proc_show(struct seq_file *m, void *v)\
{\
	seq_printf(m, "0x%08x\n", base);\
	return 0;\
}\
\
static int name ## _proc_open(struct inode *inode, struct file *file)\
{\
	return single_open(file, name ## _proc_show, NULL);\
}\
\
static const struct file_operations name ## _proc_fops = {\
	.open		= name ## _proc_open,\
	.read		= seq_read,\
	.llseek		= seq_lseek,\
	.release	= single_release,\
};\
\
static int __init name ## _mem_info_proc_init(void)\
{\
	balong_create_debug_proc_entry(string, S_IRUGO, &name ## _proc_fops, NULL);\
\
	return 0;\
}\
\
static void __exit name ## _mem_info_proc_exit(void)\
{\
	balong_remove_debug_proc_entry(string);\
\
	return;\
}\
module_init(name ## _mem_info_proc_init);\
module_exit(name ## _mem_info_proc_exit);


MEM_INFO(gpu_addr, PLAT_MEM_GPU_ADDR, "gpu")
MEM_INFO(camera_addr, PLAT_MEM_CAMERA_ADDR, "camera")
MEM_INFO(codec_addr, PLAT_MEM_CODEC_ADDR, "codec")
MEM_INFO(gralloc_addr, PLAT_MEM_GRALLOC_ADDR, "gralloc")


MODULE_DESCRIPTION("Hisilicon Memory Info Module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");




