/*
 * hi6210-io.c
 *
 * Copyright (C) 2014 Hisilicon, Inc.
 *
 * Author:
 *		Bintian Wang <bintian.wang@huawei.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/io.h>
#include <asm/page.h>
#include <linux/hisi/hi6xxx-iomap.h>
#include <linux/of.h>
#include <linux/of_fdt.h>

#define MT_DEVICE		0
#define MT_NORMAL_NC    3


struct hisi_va_mem_des
{
	unsigned long va;
	unsigned long pa;
	unsigned long length;
	unsigned int type;
};

static struct hisi_va_mem_des hi6210_va_desc[] = {
	{
		.va = 0,
		.pa = 0,
		.length = REG_ACPU_SC_IOSIZE,
		.type = MT_DEVICE,
	},
	{
        .va = 0,
        .pa = IPC_SHARE_MEM_ADDR,
        .length = IPC_SHARE_MEM_SIZE,
        .type = MT_NORMAL_NC,
    },
    {
        .va = 0,
        .pa = GLOBAL_MEM_GU_RESERVED_ADDR,
        .length = GLOBAL_MEM_GU_RESERVED_SIZE,
        .type = MT_DEVICE,
    },
    {
        .va = 0,
        .pa = GLOBAL_MEM_EXCP_BASE_ADDR,
        .length = GLOBAL_MEM_EXCP_SIZE,
        .type = MT_DEVICE,
    },
    {
        .va = 0,
        .pa = REG_BASE_SRAM_OFF,
        .length = REG_SRAM_OFF_IOSIZE,
        .type = MT_DEVICE,
    },
    {
        .va = 0,
        .pa = REG_BASE_SC_OFF,
        .length = REG_SC_OFF_IOSIZE,
        .type = MT_DEVICE,
    },
    {
        .va = 0,
        .pa = REG_BASE_SC_ON,
        .length = REG_SC_ON_IOSIZE,
        .type = MT_DEVICE,
    },
    {
        .va = 0,
        .pa = REG_BASE_PMCTRL,
        .length = REG_PMCTRL_IOSIZE,
        .type = MT_DEVICE,
    },
    {
        .va = 0,
        .pa = REG_BASE_MEDIA_SC,
        .length = REG_MEDIA_SC_IOSIZE,
        .type = MT_DEVICE,
    },
};

unsigned int g_soc_acpu_base_addr = 0;

static u64 __init dt_socbaseaddr_next_cell(int s, __be32 **cellp)
{
	__be32 *p = *cellp;

	*cellp = p + s;
	return of_read_number(p, s);
}

/*get soc acpu base addr*/
static void get_acpu_pa(void)
{
	unsigned long dt_root;
	__be32 *acpu_socaddr_parse;

	dt_root = of_get_flat_dt_root();
	acpu_socaddr_parse =(__be32 *)(of_get_flat_dt_prop(dt_root, "mntn,acpu-scaddr", NULL));
	if (!acpu_socaddr_parse)
		return;

	g_soc_acpu_base_addr = (unsigned int)(dt_socbaseaddr_next_cell(1,&acpu_socaddr_parse));
	hi6210_va_desc[0].pa = g_soc_acpu_base_addr;
	printk("g_soc_acpu_base_addr:0x%x\n", g_soc_acpu_base_addr);
}

/* map the share space such as multi-core share ddr for special purpose. */
static int  __init hi6210_map_reserved_io(void)
{
    static int flag = 0;
    int i;

    if (flag == 0) {
        flag = 1;
    } else {
        return -1;  /* this function shuld only exectute once */
    }

    get_acpu_pa();

	for(i = 0; i < sizeof(hi6210_va_desc)/sizeof(struct hisi_va_mem_des); i++) {
        switch (hi6210_va_desc[i].type) {
            case MT_NORMAL_NC:
                hi6210_va_desc[i].va = (unsigned long)ioremap_wc(hi6210_va_desc[i].pa,hi6210_va_desc[i].length);
                break;
            case MT_DEVICE:
            default:
                hi6210_va_desc[i].va = (unsigned long)ioremap(hi6210_va_desc[i].pa,hi6210_va_desc[i].length);
        }
    }
    return 0;
}

unsigned long hisi_lookup_va(unsigned long pa)
{
    int i;
    unsigned long va = 0;


	for(i = 0; i < sizeof(hi6210_va_desc)/sizeof(struct hisi_va_mem_des); i++) {
        if ((pa >= hi6210_va_desc[i].pa) && (pa < (hi6210_va_desc[i].pa + hi6210_va_desc[i].length))) {
            va = hi6210_va_desc[i].va + pa - hi6210_va_desc[i].pa;
            break;
        }
    }
    /* due to printk use this function under logbuf lock protect,
       so printk shouldn't be here */

    /* virtual address should not be zero in table */
	if (va == 0) {
		printk(KERN_ERR "look up pa %lx error!\n", pa);
	}
    BUG_ON(va == 0);
    return va;
}

unsigned long hisi_lookup_pa(unsigned long va)
{
    int i;
    unsigned long pa = 0;

	for(i = 0; i < sizeof(hi6210_va_desc)/sizeof(struct hisi_va_mem_des); i++) {
        if ((va >= hi6210_va_desc[i].va) && (va < (hi6210_va_desc[i].va + hi6210_va_desc[i].length))) {
            pa = hi6210_va_desc[i].pa + va - hi6210_va_desc[i].va;
            break;
        }
    }

    /* physical address should not be zero in table*/
	if (pa == 0) {
		printk(KERN_ERR "look up va %lx error!\n", va);
	}
    BUG_ON(pa == 0);
    return pa;
}

/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
static void *memset_align(void *s, int c, unsigned int count)
{
	char *xs = s;

	while (count--)
		*xs++ = c;
	return s;
}

/**
 * memcpy - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * You should not use this function to access IO space, use memcpy_toio()
 * or memcpy_fromio() instead.
 */
static void *memcpy_align(void *dest, const void *src, unsigned int count)
{
	char *tmp = dest;
	const char *s = src;

	while (count--)
		*tmp++ = *s++;
	return dest;
}

/**
 * memcmp - Compare two areas of memory
 * @cs: One area of memory
 * @ct: Another area of memory
 * @count: The size of the area.
 */
static int memcmp_align(const void *cs, const void *ct, unsigned int count)
{
	const unsigned char *su1, *su2;
	int res = 0;

	for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}




/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
void *hisi_io_memset(void *s, int c, unsigned int count)
{
#ifdef CONFIG_ARM64
    return memset_align(s, c, count);
#else
    return memset(s, c, count);
#endif
}

/**
 * memcpy - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * You should not use this function to access IO space, use memcpy_toio()
 * or memcpy_fromio() instead.
 */
void *hisi_io_memcpy(void *dest, const void *src, unsigned int count)
{
#ifdef CONFIG_ARM64
    return memcpy_align(dest, src, count);
#else
    return memcpy(dest, src, count);
#endif
}

/**
 * memcmp - Compare two areas of memory
 * @cs: One area of memory
 * @ct: Another area of memory
 * @count: The size of the area.
 */
int hisi_io_memcmp(const void *cs, const void *ct, unsigned int count)
{
#ifdef CONFIG_ARM64
    return memcmp_align(cs, ct, count);
#else
    return memcmp(cs, ct, count);
#endif
}

early_initcall(hi6210_map_reserved_io);
