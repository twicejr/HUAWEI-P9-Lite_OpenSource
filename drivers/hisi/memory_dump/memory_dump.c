/*
 *  kernel/drivers/hisi/memory_dump/memory_dump.c
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
 #include <linux/stddef.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/interrupt.h>
#include <linux/pagemap.h>
#include <linux/jiffies.h>
#include <linux/bootmem.h>
#include <linux/memblock.h>
#include <linux/compiler.h>
#include <linux/kernel.h>
#include <linux/kmemcheck.h>
#include <linux/module.h>
#include <linux/suspend.h>
#include <linux/pagevec.h>
#include <linux/blkdev.h>
#include <linux/slab.h>
#include <linux/ratelimit.h>
#include <linux/oom.h>
#include <linux/notifier.h>
#include <linux/topology.h>
#include <linux/sysctl.h>
#include <linux/cpu.h>
#include <linux/cpuset.h>
#include <linux/memory_hotplug.h>
#include <linux/nodemask.h>
#include <linux/vmalloc.h>
#include <linux/vmstat.h>
#include <linux/mempolicy.h>
#include <linux/stop_machine.h>
#include <linux/sort.h>
#include <linux/pfn.h>
#include <linux/backing-dev.h>
#include <linux/fault-inject.h>
#include <linux/page-isolation.h>
#include <linux/page_cgroup.h>
#include <linux/debugobjects.h>
#include <linux/kmemleak.h>
#include <linux/compaction.h>
#include <trace/events/kmem.h>
#include <linux/ftrace_event.h>
#include <linux/memcontrol.h>
#include <linux/prefetch.h>
#include <linux/migrate.h>
#include <linux/page-debug-flags.h>
#include <linux/hugetlb.h>
#include <linux/sched/rt.h>
#ifdef CONFIG_ARCH_HAS_PASR
#include <linux/hisi/pasr.h>
#endif
#include <linux/of_fdt.h>

#include <asm/tlbflush.h>
/*lint -e451*/
#include <asm/div64.h>
/*lint +e451*/
#include "memory_dump.h"

extern int pcpu_base_size;
extern struct memblock memblock;
extern struct mm_struct init_mm;
extern char _text[];
extern char _end[];
extern struct boot_param_header *initial_boot_params;

static u32 g_memdump_reserved_addr=0;
static struct table_extra{
    u64 extra_mem_phy_base;
    u64 extra_mem_size;
}g_tbl_extra_mem[MAX_EXTRA_MEM]={{0,0}};
static int extra_index=0;

static int __init early_parse_memdumpresevred_cmdline(char *p)
{
    char memdump_reserved_addr[MAX_LEN_OF_MEMDUMP_ADDR_STR];
    char *endptr = NULL;

    strncpy(memdump_reserved_addr, p, MAX_LEN_OF_MEMDUMP_ADDR_STR);
    memdump_reserved_addr[MAX_LEN_OF_MEMDUMP_ADDR_STR - 1] = '\0';

    g_memdump_reserved_addr = simple_strtoul(memdump_reserved_addr, &endptr, TRANSFER_BASE);

    pr_err("[early_parse_memdumpresevred_cmdline] p:%s, g_memdump_reserved_addr:0x%lx \n", (const char *)p, (unsigned long)g_memdump_reserved_addr);


    return 0;
}
early_param("memdump_reserved", early_parse_memdumpresevred_cmdline);

int add_extra_table(u64 phys_addr,u64 size)
{
    if((phys_addr == 0) || (size == 0) || (extra_index >= MAX_EXTRA_MEM))
    {
        return -1;
    }
    g_tbl_extra_mem[extra_index].extra_mem_phy_base = phys_addr;
    g_tbl_extra_mem[extra_index].extra_mem_size = size;
    extra_index++;
    return 0;
}

int mem_dump_init(void)
{
	int i,j;
	struct mem_dump_cb *cb;
	struct memblock_type *print_mb_cb;

	if(0 == g_memdump_reserved_addr)
	{
		    pr_err("kernel dump cmdline not transfer \n");
		    return 0;
	}
	
	cb = (struct mem_dump_cb *)ioremap_wc((unsigned int)g_memdump_reserved_addr, PAGE_SIZE);
	printk(KERN_ERR"%s begin, 0x%x,0x%llx!\r\n", __FUNCTION__,g_memdump_reserved_addr,(unsigned long long)cb);
	if (NULL == cb){
		printk(KERN_ERR"%s kmalloc fail !\r\n", __FUNCTION__);
		return -1;
	}
	memset((void *)cb,0,sizeof(struct mem_dump_cb ));
	cb->magic = MEMDUMP_CB_MAGIC;
	cb->page_shift = PAGE_SHIFT;
	cb->struct_page_size = sizeof(struct page);
	cb->phys_offset = PHYS_OFFSET;
	cb->page_offset = PAGE_OFFSET;
	cb->extra_mem_phy_base[0] = virt_to_phys(_text);
	cb->extra_mem_size[0] = ALIGN(_end -_text, PAGE_SIZE);
	cb->extra_mem_phy_base[1] = virt_to_phys(pcpu_base_addr); /* per cpu info*/
	cb->extra_mem_size[1] = ALIGN(pcpu_base_size, PAGE_SIZE)*CONFIG_NR_CPUS;
	cb->extra_mem_phy_base[2] = virt_to_phys(initial_boot_params); /* DTB address*/
	cb->extra_mem_size[2] = MAX_DTB_SIZE; /*DTB size 512K*/
	for(i=3,j=0;i<MAX_EXTRA_MEM;i++,j++)
	{
		if(i >= extra_index) break;
		cb->extra_mem_phy_base[i]=g_tbl_extra_mem[j].extra_mem_phy_base;
		cb->extra_mem_size[i]=g_tbl_extra_mem[j].extra_mem_size;
	}

	printk("_text:0x%p _end:0x%p\n", _text, _end);	

#ifdef CONFIG_FLATMEM
	cb->page = mem_map;
	cb->pfn_offset = PHYS_PFN_OFFSET;
	cb->section_size = 0;
#elif defined CONFIG_SPARSEMEM_VMEMMAP
	cb->page = vmemmap;
	cb->pfn_offset = 0;
	cb->pmd_size = PMD_SIZE;
	cb->section_size = 1UL << SECTION_SIZE_BITS;
#else
#error "Configurations other than CONFIG_PLATMEM and CONFIG_SPARSEMEM_VMEMMAP are not supported"
#endif
    #ifdef CONFIG_64BIT
       /*Subtract the base address that TTBR1 maps*/
	cb->kern_map_offset = (UL(0xffffffffffffffff) << VA_BITS);
    #else
	cb->kern_map_offset = 0;
    #endif 

	cb->ttbr = virt_to_phys(init_mm.pgd);
	printk("%s: ttbr:%p\n", __FUNCTION__, (void *)cb->ttbr);

	cb->mb_cb = (struct memblock_type *)virt_to_phys(&memblock.memory);
	print_mb_cb = &memblock.memory;
	cb->mbr_size = sizeof(struct memblock_region);

	printk("cb->page is 0x%llx\n", (unsigned long long)(cb->page));
	printk("cb->page_shift is 0x%x\n", cb->page_shift);
	printk("cb->struct_page_size is 0x%x\n", cb->struct_page_size);
	printk("cb->phys_offset is 0x%llx\n", cb->phys_offset);
	printk("cb->page_offset is 0x%llx\n", cb->page_offset);
	printk("cb->pfn_offset is 0x%llx\n", cb->pfn_offset);
	printk("cb->ttbr is 0x%llx\n", cb->ttbr);
	printk("cb->mb_cb is 0x%llx\n", (unsigned long long)(cb->mb_cb));
	printk("cb->section_size is 0x%llx\n", cb->section_size);
	printk("cb->pmd_size is 0x%llx\n", cb->pmd_size);
	printk("cb->mbr_size is 0x%x\n", cb->mbr_size);
	printk("cb->kern_map_offset is 0x%llx\n", (unsigned long long)(cb->kern_map_offset));

	printk("mem_map is %p\n", mem_map);
	printk("vmemmap is %p\n", vmemmap);
	for (i=0; i< print_mb_cb->cnt; i++) {
		printk("print_mb_cb->regions is 0x%llx\n", (print_mb_cb->regions+i)->base);
		printk("print_mb_cb->regions is 0x%llx\n", (print_mb_cb->regions+i)->size);
	}

	return 0;
}
early_initcall(mem_dump_init);


