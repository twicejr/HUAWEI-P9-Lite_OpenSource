/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_sys_info.c
    
    @brief: 读取死机时当前系统的信息
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-30
    
    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/stddef.h>
#include <linux/swap.h>
#include <linux/slab.h>
#include <linux/utsname.h>
#include <linux/blkdev.h>
#include <linux/jiffies.h>
#include <linux/hugetlb.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/vmalloc.h>
#include <linux/highmem.h>
#include <linux/version.h>
#include <linux/mman.h>

#include <asm/pgtable.h>
#include <asm/uaccess.h>

#include "../include/srecorder_sys_info.h"
#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_save_log.h"
#include "../include/srecorder_snprintf.h"


#if defined(CONFIG_DUMP_SYS_INFO)

/*----local prototypes----------------------------------------------------------------*/

typedef struct __vmalloc_info 
{
    unsigned long used;
    unsigned long largest_chunk;
} vmalloc_info;


/*----local macroes------------------------------------------------------------------*/

#ifdef CONFIG_MMU
#define VMALLOC_TOTAL (VMALLOC_END - VMALLOC_START)
#else
#define VMALLOC_TOTAL 0UL
#define get_vmalloc_info(vmi)            \
do                        \
{                        \
    (vmi)->used = 0;            \
    (vmi)->largest_chunk = 0;        \
} while(0)
#endif

#define VM_LAZY_FREE	0x01
#define VM_LAZY_FREEING	0x02
//#define VM_VM_AREA	0x04


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

#ifdef CONFIG_SWAP
static void srecorder_si_swapinfo(struct sysinfo *val);
#endif

#ifdef CONFIG_MMU
static void srecorder_get_vmalloc_info(vmalloc_info *vmi);
#endif
static long srecorder_nr_blockdev_pages(void);
static void srecorder_si_meminfo(struct sysinfo *val);


/*----function definitions--------------------------------------------------------------*/

#ifdef CONFIG_MMU
static void srecorder_get_vmalloc_info(vmalloc_info *vmi)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
    struct vmap_area *va;
    unsigned long free_area_size;
    unsigned long prev_end;
    struct list_head * phead = (struct list_head *)srecorder_get_vmap_area_list();

    vmi->used = 0;
    vmi->largest_chunk = 0;

    prev_end = VMALLOC_START;

    if (INVALID_KSYM_ADDR == srecorder_get_vmap_area_lock()
        || INVALID_KSYM_ADDR == srecorder_get_vmap_area_list())
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return;
    }
    
    if (!spin_trylock((spinlock_t *)srecorder_get_vmap_area_lock))
    {
        return;
    }

    if (list_empty((struct list_head *)srecorder_get_vmap_area_list()))
    {
        vmi->largest_chunk = VMALLOC_TOTAL;
        goto out;
    }

    list_for_each_entry(va, phead, list)
    {
        unsigned long addr = va->va_start;

        /*
        * Some archs keep another range for modules in vmalloc space
        */
        if (addr < VMALLOC_START)
        {
            continue;
        }
        
        if (addr >= VMALLOC_END)
        {
            break;
        }

        if (va->flags & (VM_LAZY_FREE | VM_LAZY_FREEING))
        {
            continue;
        }

        vmi->used += (va->va_end - va->va_start);

        free_area_size = addr - prev_end;
        if (vmi->largest_chunk < free_area_size)
        {
            vmi->largest_chunk = free_area_size;
        }

        prev_end = va->va_end;
    }

    if (VMALLOC_END - prev_end > vmi->largest_chunk)
    {
        vmi->largest_chunk = VMALLOC_END - prev_end;
    }

out:
    spin_unlock((spinlock_t *)srecorder_get_vmap_area_lock);
#else
    struct vm_struct *vma;
    unsigned long free_area_size = 0;
    unsigned long prev_end = 0;

    if (unlikely(NULL == vmi))
    {
        return;
    }
    
    vmi->used = 0;
    if (NULL == vmlist) 
    {
        vmi->largest_chunk = VMALLOC_TOTAL;
    }
    else 
    {
        vmi->largest_chunk = 0;

        prev_end = VMALLOC_START;

        if (read_trylock(&vmlist_lock))
        {
            for (vma = vmlist; NULL != vma; vma = vma->next)
            {
                unsigned long addr = (unsigned long)vma->addr;

                /*
            * Some archs keep another range for modules in vmlist
            */
                if (addr < VMALLOC_START)
                {
                    continue;
                }
                
                if (addr >= VMALLOC_END)
                {
                    break;
                }

                vmi->used += vma->size;

                free_area_size = addr - prev_end;
                if (vmi->largest_chunk < free_area_size)
                {
                    vmi->largest_chunk = free_area_size;
                }

                prev_end = vma->size + addr;
            }

            if (VMALLOC_END - prev_end > vmi->largest_chunk)
            {
                vmi->largest_chunk = VMALLOC_END - prev_end;
            }

            read_unlock(&vmlist_lock);
        }
    }
#endif
}
#endif


#ifdef CONFIG_SWAP
static void srecorder_si_swapinfo(struct sysinfo *val)
{
    unsigned int type;
    unsigned long nr_to_be_unused = 0;
    unsigned int nr_swapfiles;
    struct swap_info_struct **swap_info = NULL;

    if (unlikely(NULL == val) 
        || INVALID_KSYM_ADDR == srecorder_get_nr_swapfiles()
        || INVALID_KSYM_ADDR == srecorder_get_swap_info()
        || INVALID_KSYM_ADDR == srecorder_get_swap_lock())
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return;
    }
    
    nr_swapfiles = *(unsigned int *)srecorder_get_nr_swapfiles();
    swap_info = (struct swap_info_struct **)srecorder_get_swap_info();

    if (spin_trylock((spinlock_t *)srecorder_get_swap_lock()))
    {
        for (type = 0; type < nr_swapfiles; type++) 
        {
            struct swap_info_struct *si = swap_info[type];

            if ((si->flags & SWP_USED) && !(si->flags & SWP_WRITEOK))
            {
                nr_to_be_unused += si->inuse_pages;
            }
        }
        
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
        val->freeswap = atomic_long_read(&nr_swap_pages) + nr_to_be_unused;
#else
        val->freeswap = nr_swap_pages + nr_to_be_unused;
#endif
        val->totalswap = total_swap_pages + nr_to_be_unused;
        spin_unlock((spinlock_t *)srecorder_get_swap_lock());
    }
}
#endif


static long srecorder_nr_blockdev_pages(void)
{
    struct block_device *bdev;
    long ret = 0;
    
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
#ifdef CONFIG_BLOCK
#else
    return 0;
#endif
#endif
    
    if (INVALID_KSYM_ADDR == srecorder_get_bdev_lock() 
        || INVALID_KSYM_ADDR == srecorder_get_all_bdevs())
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return 0;
    }
    
    if (spin_trylock((spinlock_t *)srecorder_get_bdev_lock()))
    {
/*lint -e666 */
        list_for_each_entry(bdev, (struct list_head *)srecorder_get_all_bdevs(), bd_list)
/*lint +e666 */
        {
            ret += bdev->bd_inode->i_mapping->nrpages;
        }
        spin_unlock((spinlock_t *)srecorder_get_bdev_lock());
    }

    return ret;
}


static void srecorder_si_meminfo(struct sysinfo *val)
{
    val->totalram = totalram_pages;
    val->sharedram = 0;
    val->freeram = global_page_state(NR_FREE_PAGES);
    val->bufferram = srecorder_nr_blockdev_pages();
    val->totalhigh = totalhigh_pages;
    val->freehigh = nr_free_highpages();
    val->mem_unit = PAGE_SIZE;
}


/**
    @function: int srecorder_get_sys_info(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 读取死机时当前系统的信息，主要是内存的信息

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_sys_info(srecorder_reserved_mem_info_t *pmem_info)
{
    struct sysinfo si;
    unsigned long committed;
    unsigned long allowed;
    vmalloc_info vmi;
    long cached;
    unsigned long pages[NR_LRU_LISTS];
    int lru;
    int bytes_read = 0;
    psrecorder_info_header_t pinfo_header = NULL;
    char *cpu_name = NULL;
    char *machine_name = NULL;

    if (unlikely(NULL == pmem_info 
        || INVALID_KSYM_ADDR == srecorder_get_cpu_name()
        || INVALID_KSYM_ADDR == srecorder_get_machine_name())
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
#else
#ifdef CONFIG_SWAP
        || INVALID_KSYM_ADDR == srecorder_get_nr_swapfiles()
        || INVALID_KSYM_ADDR == srecorder_get_swap_info()
        || INVALID_KSYM_ADDR == srecorder_get_swap_lock()
#endif
#endif
        || INVALID_KSYM_ADDR == srecorder_get_bdev_lock() 
        || INVALID_KSYM_ADDR == srecorder_get_all_bdevs())
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return -1;
    }

    if (srecorder_log_has_been_dumped(SYS_INFO_BIT1) || pmem_info->dump_modem_crash_log_only)
    {
        SRECORDER_PRINTK("sys info has been dumped successfully!\n");
        return 0;  
    }
    
    if (0 != srecorder_write_info_header(pmem_info, SYS_INFO_BIT1, &pinfo_header))
    {
        SRECORDER_PRINTK("File [%s] line [%d] can not reserve memory for sysinfo!\n", __FILE__, __LINE__);
        return -1;
    }
    
    cpu_name = (char *)(*(srec_ksym_addr_t *)srecorder_get_cpu_name());
    machine_name = (char *)(*(srec_ksym_addr_t *)srecorder_get_machine_name());

    memset(&si, 0, sizeof(struct sysinfo));
    srecorder_si_meminfo(&si);
    
#ifdef CONFIG_SWAP
    srecorder_si_swapinfo(&si);
#else
    si_swapinfo(&si);
#endif

    committed = percpu_counter_read_positive(&vm_committed_as);
    allowed = ((totalram_pages - hugetlb_total_pages()) * sysctl_overcommit_ratio / 100) + total_swap_pages; /*100百分比*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
    cached = global_page_state(NR_FILE_PAGES) - total_swapcache_pages() - si.bufferram;
#else
    cached = global_page_state(NR_FILE_PAGES) - total_swapcache_pages - si.bufferram;
#endif
    if (cached < 0)
    {
        cached = 0;
    }

    memset(&vmi, 0, sizeof(vmalloc_info)); /* 不设置初值居然编译报错，奇怪 */
#ifdef CONFIG_MMU
    srecorder_get_vmalloc_info(&vmi);
#else
    get_vmalloc_info(&vmi);
#endif

    for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
    {
        pages[lru] = global_page_state(NR_LRU_BASE + lru);
    }

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "sysname: %s\nrelease: %s\nversion: %s\n"
        "Processor: %s\nHardware: %s\n"
        "jiffies: %llu\n\n"
        "MemTotal:       %8lu kB\n"
        "MemFree:        %8lu kB\n"
        "Buffers:        %8lu kB\n"
        "Cached:         %8lu kB\n"
        "SwapCached:     %8lu kB\n"
        "Active:         %8lu kB\n"
        "Inactive:       %8lu kB\n"
        "Active(anon):   %8lu kB\n"
        "Inactive(anon): %8lu kB\n"
        "Active(file):   %8lu kB\n"
        "Inactive(file): %8lu kB\n"
        "Unevictable:    %8lu kB\n"
        "Mlocked:        %8lu kB\n"
#ifdef CONFIG_HIGHMEM
        "HighTotal:      %8lu kB\n"
        "HighFree:       %8lu kB\n"
        "LowTotal:       %8lu kB\n"
        "LowFree:        %8lu kB\n"
#endif
#ifndef CONFIG_MMU
        "MmapCopy:       %8lu kB\n"
#endif
        "SwapTotal:      %8lu kB\n"
        "SwapFree:       %8lu kB\n"
        "Dirty:          %8lu kB\n"
        "Writeback:      %8lu kB\n"
        "AnonPages:      %8lu kB\n"
        "Mapped:         %8lu kB\n"
        "Shmem:          %8lu kB\n"
        "Slab:           %8lu kB\n"
        "SReclaimable:   %8lu kB\n"
        "SUnreclaim:     %8lu kB\n"
        "KernelStack:    %8lu kB\n"
        "PageTables:     %8lu kB\n"
#ifdef CONFIG_QUICKLIST
        "Quicklists:     %8lu kB\n"
#endif
        "NFS_Unstable:   %8lu kB\n"
        "Bounce:         %8lu kB\n"
        "WritebackTmp:   %8lu kB\n"
        "CommitLimit:    %8lu kB\n"
        "Committed_AS:   %8lu kB\n"
        "VmallocTotal:   %8lu kB\n"
        "VmallocUsed:    %8lu kB\n"
        "VmallocChunk:   %8lu kB\n"
#ifdef CONFIG_MEMORY_FAILURE
        "HardwareCorrupted: %5lu kB\n"
#endif
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
        "AnonHugePages:  %8lu kB\n"
#endif
        ,
        init_uts_ns.name.sysname, init_uts_ns.name.release, init_uts_ns.name.version, 
        (NULL == cpu_name) ? "unknown" : cpu_name, (NULL == machine_name) ? "unknown" : machine_name, 
        jiffies_64 - INITIAL_JIFFIES, 
        K(si.totalram),
        K(si.freeram),
        K(si.bufferram),
        K(cached),
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
        K(total_swapcache_pages()),
#else
        K(total_swapcache_pages),
#endif
        K(pages[LRU_ACTIVE_ANON] + pages[LRU_ACTIVE_FILE]),
        K(pages[LRU_INACTIVE_ANON] + pages[LRU_INACTIVE_FILE]),
        K(pages[LRU_ACTIVE_ANON]),
        K(pages[LRU_INACTIVE_ANON]),
        K(pages[LRU_ACTIVE_FILE]),
        K(pages[LRU_INACTIVE_FILE]),
        K(pages[LRU_UNEVICTABLE]),
        K(global_page_state(NR_MLOCK)),
#ifdef CONFIG_HIGHMEM
        K(si.totalhigh),
        K(si.freehigh),
        K(si.totalram - si.totalhigh),
        K(si.freeram - si.freehigh),
#endif
#ifndef CONFIG_MMU
        K((unsigned long) atomic_long_read(&mmap_pages_allocated)),
#endif
        K(si.totalswap),
        K(si.freeswap),
        K(global_page_state(NR_FILE_DIRTY)),
        K(global_page_state(NR_WRITEBACK)),
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
        K(global_page_state(NR_ANON_PAGES) + global_page_state(NR_ANON_TRANSPARENT_HUGEPAGES) * HPAGE_PMD_NR),
#else
        K(global_page_state(NR_ANON_PAGES)),
#endif
        K(global_page_state(NR_FILE_MAPPED)),
        K(global_page_state(NR_SHMEM)),
        K(global_page_state(NR_SLAB_RECLAIMABLE) + global_page_state(NR_SLAB_UNRECLAIMABLE)),
        K(global_page_state(NR_SLAB_RECLAIMABLE)),
        K(global_page_state(NR_SLAB_UNRECLAIMABLE)),
        global_page_state(NR_KERNEL_STACK) * THREAD_SIZE / 1024,
        K(global_page_state(NR_PAGETABLE)),
#ifdef CONFIG_QUICKLIST
        K(quicklist_total_size()),
#endif
        K(global_page_state(NR_UNSTABLE_NFS)),
        K(global_page_state(NR_BOUNCE)),
        K(global_page_state(NR_WRITEBACK_TEMP)),
        K(allowed),
        K(committed),
        (unsigned long)VMALLOC_TOTAL >> 10,
        vmi.used >> 10,
        vmi.largest_chunk >> 10
#ifdef CONFIG_MEMORY_FAILURE
        , atomic_long_read(&mce_bad_pages) << (PAGE_SHIFT - 10)
#endif
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
        , K(global_page_state(NR_ANON_TRANSPARENT_HUGEPAGES) * HPAGE_PMD_NR)
#endif
        );

    srecorder_renew_meminfo(pmem_info, bytes_read);
    srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
    
    return 0;
}


/**
    @function: int srecorder_init_sys_info(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化sys info模块

    @param: pinit_params 模块初始化数据
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_sys_info(srecorder_module_init_params_t *pinit_params)
{
    srecorder_clear_log_dumped_bit(SYS_INFO_BIT1);
    
    return 0;
}


/**
    @function: void srecorder_exit_sys_info(void)
    @brief: 退出sys info模块

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_sys_info(void)
{
    srecorder_set_log_dumped_bit(SYS_INFO_BIT1);
}
#else
int srecorder_get_sys_info(srecorder_reserved_mem_info_t *pmem_info)
{
    return 0;
}


int srecorder_init_sys_info(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


void srecorder_exit_sys_info(void)
{
    return;
}
#endif

