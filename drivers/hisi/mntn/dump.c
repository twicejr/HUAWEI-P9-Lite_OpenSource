/*
 *  linux/arch/arm/mach-k3v2/dump.c
 *
 * balong memory/register proc-fs  dump implementation
 *
 * Copyright (C) 2012 Hisilicon, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/mm.h>
#include <linux/sizes.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/stat.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/highmem.h>
#include <linux/uaccess.h>
#include <linux/hisi/util.h>
#include <linux/hisi/reset.h>

#define TRANSFER_BASE       (16)
#define STRINGLEN 9
#define MAX_LEN_OF_RSTLOGADDR_STR  30
#define MAX_MEMDUMP_NAME 16

#define memdump_remap(phys_addr, size) memdump_remap_type(phys_addr, size, PAGE_KERNEL)
#define memdump_unmap(vaddr) vunmap(vaddr)

unsigned int g_dump_flag;
unsigned int g_ddr_size = 0x80000000;
char core_flag[STRINGLEN];
struct proc_dir_entry *core_trace, *core_flag_file;
/*dump file information, set to file->private_data*/
struct dump_info {
	void *p;		/*dump region phy/virtual address */
	loff_t size;		/*dump region size */
};
/*保存fastboot传递过来的异常区地址信息*/
static phys_addr_t g_memdump_addr;
static phys_addr_t g_memdump_end;
static unsigned int g_memdump_size;
struct memdump {
	char name[MAX_MEMDUMP_NAME];
	unsigned long base;
	unsigned long size;
};

extern void etb_nve_read(unsigned char *config);
extern unsigned long hisi_get_reserve_mem_size(void);
extern int memblock_free(phys_addr_t base, phys_addr_t size);

static inline void *memdump_remap_type(unsigned long phys_addr, size_t size,
				       pgprot_t pgprot)
{
	int i;
	u8 *vaddr;
	int npages = PAGE_ALIGN((phys_addr & (PAGE_SIZE - 1)) + size) >> PAGE_SHIFT;
	unsigned long offset = phys_addr & (PAGE_SIZE - 1);
	struct page **pages;
	pages = vmalloc(sizeof(struct page *) * npages);
	if (!pages) {
		printk(KERN_ERR "%s: vmalloc return NULL!\n", __func__);
		return NULL;
	}
	pages[0] = phys_to_page(phys_addr);
	for (i = 0; i < npages - 1; i++) {
		pages[i + 1] = pages[i] + 1;
	}
	vaddr = (u8 *) vmap(pages, npages, VM_MAP, pgprot);
	if (vaddr == 0) {
		printk(KERN_ERR "%s: vmap return NULL!\n", __func__);
	} else {
		vaddr += offset;
	}
	vfree(pages);
	return (void *)vaddr;
}

/*read dump file content*/
static ssize_t dump_phy_mem_proc_file_read(struct file *file,
					   char __user *userbuf, size_t bytes,
					   loff_t *off)
{
	struct dump_info *info = (struct dump_info *)file->private_data;
	void __iomem *p;
	ssize_t copy;

	if (!info) {
		printk(KERN_ERR "the proc file don't be created in advance.\n");
		return 0;
	}
	if (*off > info->size) {
		printk(KERN_ERR "read offset error 1\n");
		return 0;
	}

	if (*off == info->size) {
		/*end of file */
		return 0;
	}

	copy = (ssize_t) min(bytes, (size_t) (info->size - *off));

	p = memdump_remap((phys_addr_t) ((char *)info->p + *off), copy);
	if (NULL == p) {
		printk(KERN_ERR"%s ioremap fail\n", __func__);
		return -ENOMEM;
	}

	if (copy_to_user(userbuf, p, copy)) {
		printk(KERN_ERR"%s copy to user error\n", __func__);
		copy = -EFAULT;
		goto copy_err;
	}

	*off += copy;

copy_err:
	p = (void __iomem *)(((unsigned long)p) & (~(PAGE_SIZE - 1)));
	memdump_unmap(p);
	return copy;
}

static int dump_phy_mem_proc_file_open(struct inode *inode, struct file *file)
{
	file->private_data = PDE_DATA(inode);

	return 0;
}

static int dump_phy_mem_proc_file_release(struct inode *inode,
					  struct file *file)
{
	file->private_data = NULL;

	return 0;

}

static const struct file_operations dump_phy_mem_proc_fops = {
	.open = dump_phy_mem_proc_file_open,
	.read = dump_phy_mem_proc_file_read,
	.release = dump_phy_mem_proc_file_release,
};

/* create memory dump file to dump phy memory */
static void create_dump_phy_mem_proc_file(char *name, unsigned long phy_addr,
					  size_t size)
{
	struct dump_info *info;

	/*as a public interface, we should check the parameter */
	if ((NULL == name) || (0 == phy_addr) || (0 == size)) {
		printk(KERN_ERR
		       "%s %d parameter error : name 0x%p phy_addr 0x%lx ize %lu\r\n",
		       __func__, __LINE__, name, phy_addr, size);
		return;
	}

	info = kmalloc(sizeof(struct dump_info), GFP_KERNEL);
	if (NULL == info) {
		printk(KERN_ERR"%s kmalloc fail !\r\n", __func__);
		return;
	}

	info->p = (void *)(phy_addr);
	info->size = size;

	balong_create_memory_proc_entry(name, S_IRUGO | S_IWUGO,
					&dump_phy_mem_proc_fops, info);

	return;
}

static ssize_t dump_end_proc_read(struct file *file, char __user *userbuf,
				  size_t bytes, loff_t *off)
{
	phys_addr_t addr;
	struct page *page;

	for (addr = g_memdump_addr; addr < (g_memdump_addr + g_memdump_size);
	     addr += PAGE_SIZE) {
		page = pfn_to_page(addr >> PAGE_SHIFT);
		free_reserved_page(page);
#ifdef CONFIG_HIGHMEM
		if (PageHighMem(page))
			totalhigh_pages++;
#endif
	}

	memblock_free(g_memdump_addr, g_memdump_size);

	pr_err("dump_end_proc_read:g_memdump_addr=0x%x, g_memdump_end=0x%x,g_memdump_size=0x%x\n",
		(unsigned int)g_memdump_addr, (unsigned int)g_memdump_end,
		g_memdump_size);
	pr_info("%s:addr%lu\n", __func__, (unsigned long)addr);
	g_memdump_addr = 0;
	g_memdump_end = 0;
	g_memdump_size = 0;
	return 0;
}

static const struct file_operations dump_end_proc_fops = {
	.read = dump_end_proc_read,
};

static int __init early_parse_memdumpaddr_cmdline(char *p)
{
	char memdump_addr[MAX_LEN_OF_RSTLOGADDR_STR];
	char memdump_end[MAX_LEN_OF_RSTLOGADDR_STR];
	char memdump_size[MAX_LEN_OF_RSTLOGADDR_STR];
	char *endptr = NULL;

	memcpy(memdump_addr, p, 10);
	memdump_addr[10] = 0;
	memcpy(memdump_end, p + 11, 10);
	memdump_end[10] = 0;
	memcpy(memdump_size, p + 22, 10);
	memdump_size[10] = 0;

	g_memdump_addr = simple_strtoul(memdump_addr, &endptr, TRANSFER_BASE);
	g_memdump_end = simple_strtoul(memdump_end, &endptr, TRANSFER_BASE);
	g_memdump_size = simple_strtoul(memdump_size, &endptr, TRANSFER_BASE);
	pr_err("[early_parse_memdumpaddr_cmdline] p:%s, g_memdump_addr:0x%lx g_memdump_end:0x%lx,g_memdump_size:0x%x\n",
		(const char *)p, (unsigned long)g_memdump_addr,
		(unsigned long)g_memdump_end, g_memdump_size);

	return 0;
}

early_param("memdump_addr", early_parse_memdumpaddr_cmdline);

static int __init memdump_init(void)
{
	struct memdump *mem_info;
	void __iomem *memdump_head;

	if (!check_himntn(HIMNTN_GOBAL_RESETLOG)) {
		return 0;
	}
	if (g_memdump_addr == 0)
		return 0;

	/* to free the reserve mem of memdump */
	if (NULL == balong_create_memory_proc_entry("dump_end", S_IRUGO,
					    &dump_end_proc_fops, NULL)) {
		return 0;
	}
	memdump_head = memdump_remap(g_memdump_addr, PAGE_SIZE);
	mem_info = (struct memdump *)memdump_head;

	while (mem_info->name[0] != 0) {
		pr_err("%s,name:%s\n", __func__, mem_info->name);
		pr_err("%s:base:0x%lx, size:0x%lx\n", __func__,
		       mem_info->base, mem_info->size);
		create_dump_phy_mem_proc_file(mem_info->name, mem_info->base,
					      (size_t)mem_info->size);
		mem_info++;
	}

	memdump_unmap(memdump_head);

	return 0;
}

arch_initcall(memdump_init);

MODULE_DESCRIPTION("Hisilicon Memory/Register Dump Module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");
