#ifndef __MEMORY_DUMP_H
#define __MEMORY_DUMP_H
#include <linux/mm_types.h>

#define MAX_LEN_OF_MEMDUMP_ADDR_STR  (30)
#define TRANSFER_BASE    (16)
#define MEMDUMP_CB_MAGIC 0xDEADBEEFDEADBEEF
#define MAX_EXTRA_MEM 32
#define MAX_DTB_SIZE 0x80000

struct mem_dump_cb
{
    u64 magic;/*mem dump block magic, default value is 0xdeadbeefdeadbeef*/
    struct page *page;/*the virtual base address of the struct page objects. all page objects occupy a contiguous memory region.*/
    u32 page_shift; /*the value is log 2 (the size of a page which is the basic MMU unit).*/
    u32 struct_page_size; /*the size of struct page.*/
    u64 phys_offset; /*the start physical address managed by linux*/
    u64 page_offset; /*the base logical address*/
    /*used to find the pa of a page object through translation table walk. For ARM32 it is 0,
	for ARM64 it is the base va TTBR1 maps*/
    u64 kern_map_offset;
    /*the definition is different from linux. it is used to tell the difference
        between CONFIG_FLATMEM and CONFIG_SPARSEMEM_VMEMMAP*/
    u64 pfn_offset;
    u64 ttbr; /*the base address of the pgd*/
    struct memblock_type *mb_cb; /*the physical address of memory memoryblock_type object.*/
    /*the size of the memory section. if CONFIG_FLATMEM is enabled it is 0,
        if CONFIG_SPARSEMEM_VMEMMAP is enabled it is the size of a memory section*/
    u64 section_size;
    u64 pmd_size; /*used to calculate the page objects for 4KB pages, becacuse they are mapped via the block type pmd entres.*/
    u64 extra_mem_phy_base[MAX_EXTRA_MEM];/*physcal address of the extra mem */
    u64 extra_mem_size[MAX_EXTRA_MEM];/*the size of the  extra mem  */
    u32 mbr_size; /*the size of struct memblock_region, the size of which is depended on kernel configuration. */
};
#endif
