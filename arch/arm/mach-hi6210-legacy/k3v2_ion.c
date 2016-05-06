/*
 * ION Initialization for K3V24.
 *
 * Copyright (C) 2011 Hisilicon
 *
 * Author: zhangniangao@huawei.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/sysdev.h>
#include <linux/interrupt.h>
#include <linux/amba/bus.h>
#include <linux/amba/clcd.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/io.h>
#include <linux/ata_platform.h>
#include <linux/amba/mmci.h>

#include <asm/clkdev.h>
#include <asm/system.h>
#include <mach/hardware.h>
#include <asm/irq.h>
#include <asm/leds.h>
#include <asm/mach-types.h>
#include <asm/hardware/arm_timer.h>

#include <asm/mach/arch.h>
#include <asm/mach/flash.h>
#include <asm/mach/irq.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>

#include <asm/hardware/gic.h>

#include <mach/platform.h>
#include <mach/irqs.h>
#include <mach/early-debug.h>
#include <linux/bootmem.h>

#include <linux/ion.h>
#include <linux/memblock.h>
#include <linux/hisi_ion.h>
#include <mach/hisi_mem.h>


//预留的物理地址
unsigned long hisi_reserved_gpu_phymem;
unsigned long hisi_reserved_fb_phymem;
unsigned long hisi_reserved_codec_phymem;
unsigned long hisi_reserved_dumplog_phymem;
unsigned long hisi_reserved_camera_phymem;
unsigned long hisi_reserved_vpp_phymem;
EXPORT_SYMBOL(hisi_reserved_gpu_phymem);
EXPORT_SYMBOL(hisi_reserved_fb_phymem);
EXPORT_SYMBOL(hisi_reserved_codec_phymem);
EXPORT_SYMBOL(hisi_reserved_dumplog_phymem);
EXPORT_SYMBOL(hisi_reserved_camera_phymem);
EXPORT_SYMBOL(hisi_reserved_vpp_phymem);

#define HISI_LCD_SIZE_NAME 10
struct hisi_reserved_media_memory {
    unsigned char lcd_name[HISI_LCD_SIZE_NAME];
    unsigned long gpu_size;
    unsigned long codec_size;
    unsigned long camera_size;
    unsigned long gralloc_size;
	unsigned long vpp_size;
#if defined(CONFIG_OVERLAY_COMPOSE)
    unsigned long overlay_size;
#endif
	unsigned long fb_size;
};

extern int get_isfullhd();
void memset_for_fhd(void);
void memset_for_hd(void);
unsigned long HISI_FRAME_BUFFER_SIZE;
unsigned long HISI_MEM_FB_SIZE_NEW[2] = {
	PAGE_ALIGN(1280 * (STRIDE_ALIGN(ALIGN_UP((720 * 4), 64))) * 4),	 //14400k
	PAGE_ALIGN(38 * SZ_1M)
};

unsigned long HISI_MEM_GPU_SIZE_NEW[2] = {
	PAGE_ALIGN(SZ_16M),
	PAGE_ALIGN(SZ_16M)
};
unsigned long HISI_PMEM_CAMERA_SIZE_NEW[2] = {
	PAGE_ALIGN(4 * SZ_1K),
	PAGE_ALIGN(4 * SZ_1K)
};
unsigned long HISI_MEM_CODEC_SIZE_NEW[2] = {
	PAGE_ALIGN(52 * SZ_1M),
	PAGE_ALIGN(52 * SZ_1M)
};
unsigned long HISI_PMEM_GRALLOC_SIZE_NEW[2] = {
	PAGE_ALIGN(182 * SZ_1M + 512 * SZ_1K),
	PAGE_ALIGN(196 * SZ_1M)
};

unsigned long PLAT_MEM_RAM_CONSOLE_SIZE_NEW[2] = {
	PAGE_ALIGN(SZ_64K),
	PAGE_ALIGN(SZ_64K)
};

unsigned long HISI_MEM_VPP_SIZE_NEW[2] = {
	PAGE_ALIGN(5 * SZ_1M),
	PAGE_ALIGN(5 * SZ_1M)
};

unsigned long HISI_PMEM_OVERLAY_SIZE_NEW[2] = {
	PAGE_ALIGN(124 * SZ_1M),
	PAGE_ALIGN(188 * SZ_1M)
};

unsigned long PLAT_MEM_RESERVED_SIZE_NEW = 0;


static struct hisi_reserved_media_memory hisi_media_mem_array[] = {
    [0] = {
        .lcd_name = "hvga",
        .gpu_size = HISI_MEM_GPU_SIZE,
        .codec_size = HISI_MEM_CODEC_SIZE,
        .camera_size = HISI_PMEM_CAMERA_SIZE,
        .gralloc_size = HISI_PMEM_GRALLOC_SIZE,
		.vpp_size = HISI_MEM_VPP_SIZE,
    #if defined(CONFIG_OVERLAY_COMPOSE)
        .overlay_size = HISI_PMEM_OVERLAY_SIZE,
    #endif
		.fb_size = HISI_MEM_FB_SIZE,
    },
    [1] = {
        .lcd_name = "vga",
        .gpu_size = HISI_MEM_GPU_SIZE,
        .codec_size = HISI_MEM_CODEC_SIZE,
        .camera_size = HISI_PMEM_CAMERA_SIZE,
        .gralloc_size = HISI_PMEM_GRALLOC_SIZE,
		.vpp_size = HISI_MEM_VPP_SIZE,
    #if defined(CONFIG_OVERLAY_COMPOSE)
        .overlay_size = HISI_PMEM_OVERLAY_SIZE,
    #endif
		.fb_size = HISI_MEM_FB_SIZE,
    },
    [2] = {
        .lcd_name = "dvga",
        .gpu_size = HISI_MEM_GPU_SIZE,
        .codec_size = HISI_MEM_CODEC_SIZE,
        .camera_size = HISI_PMEM_CAMERA_SIZE,
        .gralloc_size = HISI_PMEM_GRALLOC_SIZE,
		.vpp_size = HISI_MEM_VPP_SIZE,
    #if defined(CONFIG_OVERLAY_COMPOSE)
        .overlay_size = HISI_PMEM_OVERLAY_SIZE,
    #endif
		.fb_size = HISI_MEM_FB_SIZE,
    },
    [3] = {
        .lcd_name = "720p",
        .gpu_size = HISI_MEM_GPU_SIZE,
        .codec_size = HISI_MEM_CODEC_SIZE,
        .camera_size = HISI_PMEM_CAMERA_SIZE,
        .gralloc_size = HISI_PMEM_GRALLOC_SIZE,
		.vpp_size = HISI_MEM_VPP_SIZE,
    #if defined(CONFIG_OVERLAY_COMPOSE)
        .overlay_size = HISI_PMEM_OVERLAY_SIZE,
    #endif
		.fb_size = HISI_MEM_FB_SIZE,
    },
    [4] = {
        .lcd_name = "1080p",
        .gpu_size = HISI_MEM_GPU_SIZE,
        .codec_size = HISI_MEM_CODEC_SIZE,
        .camera_size = HISI_PMEM_CAMERA_SIZE,
        .gralloc_size = HISI_PMEM_GRALLOC_SIZE,
		.vpp_size = HISI_MEM_VPP_SIZE,
    #if defined(CONFIG_OVERLAY_COMPOSE)
        .overlay_size = HISI_PMEM_OVERLAY_SIZE,
    #endif
		.fb_size = HISI_MEM_FB_SIZE,
    },
};


static struct hisi_reserved_media_memory hisi_media_mem = {
    .lcd_name = "720p",
    .gpu_size = HISI_MEM_GPU_SIZE,
    .codec_size = HISI_MEM_CODEC_SIZE,
    .camera_size = HISI_PMEM_CAMERA_SIZE,
    .gralloc_size = HISI_PMEM_GRALLOC_SIZE,
	.vpp_size = HISI_MEM_VPP_SIZE,
   #if defined(CONFIG_OVERLAY_COMPOSE)
       .overlay_size = HISI_PMEM_OVERLAY_SIZE,
   #endif
	.fb_size = HISI_MEM_FB_SIZE,
};


/*
pmem allocating 148963328 bytes at (2db00000 physical) for gpu pmem area(142MB)
codec pmem allocating 28311552 bytes at (36910000 physical) for codec pcodec area(27MB)
camera pmem allocating 4096 bytes at (38410000 physical) for camera pic(4K)
camera pmem allocating 58720256 bytes at (38411000 physical) for gralloc pmem area(56MB)
overlay pmem allocating 67108864 bytes at (3bc11000 physical) for overlay pmem area(64MB)
dumplog pmem allocating 2097152 bytes at (3fc11000 physical) for dumplogarea(2MB)
*/

static struct ion_platform_data k3v2_ion_data = {
    .nr = 5,
    .heaps = {
        {
            .type = ION_HEAP_TYPE_CARVEOUT,
            .id = HISI_ION_HEAP_CAMERA_ID,
            .name = "camera",
        },
        {
            .type = ION_HEAP_TYPE_CARVEOUT,
            .id = HISI_ION_HEAP_GRALLOC_ID,
            .name = "gralloc",
            .cached = 1,
        },
        {
            .type = ION_HEAP_TYPE_CARVEOUT,
            .id = HISI_ION_HEAP_OVERLAY_ID,
            .name = "overlay",
			.cached = 1,
        },
        #if 0 //qijiwen
        {
            .type = ION_HEAP_TYPE_K3V2,
            .id = K3V2_ION_HEAP_K3V2_ID,
            .name = "k3v2_system",
        },
        {
            .type = ION_HEAP_TYPE_K3V2_USER,
            .id = K3V2_ION_HEAP_USER_ID,
            .name = "k3v2_user",
        },
        #endif
       {
            .type = ION_HEAP_TYPE_SYSTEM,
            .id = HISI_ION_HEAP_SYS_ID,
            .name = "sys_user",
        },
       {
            .type = ION_HEAP_TYPE_SYSTEM_CONTIG,
            .id = HISI_ION_HEAP_SYS_CONTIG_ID,
            .name = "sys_contig",
        },
    },
};




static struct platform_device k3v2_ion_device = {
    .name = "ion-k3v2",
    .id = -1,
    .dev = {
        .platform_data = &k3v2_ion_data,
    },
};

static int __init k3v2_register_ion(void)
{
    printk("=====ion device register");
    platform_device_register(&k3v2_ion_device);
    return 0;
}

arch_initcall(k3v2_register_ion);


unsigned long hisi_get_reserve_mem_size(void)
{
    unsigned long reserved = SZ_2M;
	if(!get_isfullhd())
	{
		memset_for_hd();
	}
	else
	{
		memset_for_fhd();
	}
    reserved += hisi_media_mem.gpu_size;
    reserved += hisi_media_mem.codec_size;
    reserved += hisi_media_mem.camera_size;
    reserved += hisi_media_mem.gralloc_size;
	reserved += hisi_media_mem.vpp_size;
#if defined(CONFIG_OVERLAY_COMPOSE)
    reserved += hisi_media_mem.overlay_size;
#endif
	reserved += hisi_media_mem.fb_size;
    //reserved += HISI_PMEM_DUMPLOG_SIZE;
    reserved = (reserved & 0xFFF00000) + SZ_1M;

    return reserved;
}


/* lcd_density=hvga/vga/dvga and so on */
static int __init early_k3v2_lcd_density(char *p)
{
    int mach = 0;
    int i;

    printk("k3v2 lcd density = %s\n", p);
    for (i = 0; i < ARRAY_SIZE(hisi_media_mem_array); i++) {
        if (!strncmp(p, hisi_media_mem_array[i].lcd_name, strlen(p))) {
            mach = 1;
            break;
        }
    }

    if (mach) {
        hisi_media_mem.gpu_size = hisi_media_mem_array[i].gpu_size;
        hisi_media_mem.codec_size = hisi_media_mem_array[i].codec_size;
        hisi_media_mem.camera_size = hisi_media_mem_array[i].camera_size;
        hisi_media_mem.gralloc_size = hisi_media_mem_array[i].gralloc_size;
		hisi_media_mem.vpp_size = hisi_media_mem_array[i].vpp_size;
#if defined(CONFIG_OVERLAY_COMPOSE)
        hisi_media_mem.overlay_size = hisi_media_mem_array[i].overlay_size;
#endif
		hisi_media_mem.fb_size = hisi_media_mem_array[i].fb_size;
        memcpy(hisi_media_mem.lcd_name, p, strlen(p) + 1);

		printk("lcd %s gpu %luMB codec %luMB camera %luMB gralloc %luMB vpp %luMB"
			#if defined(CONFIG_OVERLAY_COMPOSE)
				" overlay %luMB"
			#endif
				" fb %luMB\n",
				hisi_media_mem.lcd_name,
				hisi_media_mem.gpu_size / SZ_1M,
				hisi_media_mem.codec_size / SZ_1M,
				hisi_media_mem.camera_size / SZ_1M,
				hisi_media_mem.gralloc_size / SZ_1M,
				hisi_media_mem.vpp_size / SZ_1M,
			#if defined(CONFIG_OVERLAY_COMPOSE)
				hisi_media_mem.overlay_size / SZ_1M,
			#endif
				hisi_media_mem.fb_size / SZ_1M
		);
    } else {
        printk("lcd %s not found!\n", p);
    }

    return 0;
}
early_param("k3v2_lcd_density", early_k3v2_lcd_density);


void __init k3v2_allocate_memory_regions(void)
{
    unsigned long reserved_base = HISI_BASE_MEMORY_SIZE;
    unsigned long reserved_size;
    unsigned long size;

    edb_trace(1);

    reserved_size = hisi_get_reserve_mem_size();

    reserved_base -= (reserved_size - SZ_1M);

    /* GPU memory */
    size = hisi_media_mem.gpu_size;
    hisi_reserved_gpu_phymem = reserved_base;
    printk("ion allocating %lu bytes at (%lx physical) for gpu "
        "pmem area\n", size, reserved_base);

    reserved_base += size;

    /* CODEC memory */
    size = hisi_media_mem.codec_size;
    /*Revived by y44207 ,V200 64 byte align*/
    hisi_reserved_codec_phymem = reserved_base;
    printk("codec ion allocating %lu bytes at (%lx physical) for codec "
        "pcodec area\n", size, reserved_base);
	reserved_base += size;
	/* VPP memory */
	size = hisi_media_mem.vpp_size;
	hisi_reserved_vpp_phymem = reserved_base;
	printk("vpp ion allocating %lu bytes at (%lx physical) for vpp "
		"pmem area\n", size, reserved_base);

    reserved_base += size;

    /* CAMERA memory pmem */
    size = hisi_media_mem.camera_size;
    if (size) {
        k3v2_ion_data.heaps[0].base = reserved_base;
        k3v2_ion_data.heaps[0].size	= size;
        hisi_reserved_camera_phymem = k3v2_ion_data.heaps[0].base;
        printk("camera ion allocating %lu bytes at (%lx physical) for camera pic\n",
            size, reserved_base);
    }

    reserved_base += size;

    /* video decoder display && camera preview + Thumbnail */
    size = hisi_media_mem.gralloc_size;
    if (size) {
        k3v2_ion_data.heaps[1].base = reserved_base;
        k3v2_ion_data.heaps[1].size	= size;
        printk("camera ion allocating %lu bytes at (%lx physical) for gralloc "
            "pmem area\n", size, reserved_base);
    }

    reserved_base += size;

#if defined(CONFIG_OVERLAY_COMPOSE)
    size = hisi_media_mem.overlay_size;
    if (size) {
        k3v2_ion_data.heaps[2].base = reserved_base;
        k3v2_ion_data.heaps[2].size	= size;
        printk("overlay ion allocating %lu bytes at (%lx physical) for overlay "
            "pmem area\n", size, reserved_base);
    }

    reserved_base += size;
#endif

	/*FB memory*/
	size = hisi_media_mem.fb_size;
	hisi_reserved_fb_phymem = reserved_base;
	printk("fb ion allocating %lu bytes at (%lx physical) for fb "
		"pmem area\n",size,reserved_base);

	reserved_base += size;

    /* dumplog memory */
    //size = HISI_PMEM_DUMPLOG_SIZE;
    /*Revived by y44207 ,V200 64 byte align*/
    //hisi_reserved_dumplog_phymem = reserved_base;
    //printk("dumplog ion allocating %lu bytes at (%lx physical) for dumplog"
    //    "area\n", size, reserved_base);

    //reserved_base += size;

}

void memset_for_hd(void)
{
    int i = 0;

    hisi_media_mem.gpu_size     = HISI_MEM_GPU_SIZE_NEW[0];
    hisi_media_mem.codec_size   = HISI_MEM_CODEC_SIZE_NEW[0];
    hisi_media_mem.camera_size  = HISI_PMEM_CAMERA_SIZE_NEW[0];
    hisi_media_mem.gralloc_size = HISI_PMEM_GRALLOC_SIZE_NEW[0];
    hisi_media_mem.vpp_size     = HISI_MEM_VPP_SIZE_NEW[0];
#if defined(CONFIG_OVERLAY_COMPOSE)
    hisi_media_mem.overlay_size = HISI_PMEM_OVERLAY_SIZE_NEW[0];
#endif
    hisi_media_mem.fb_size      = HISI_MEM_FB_SIZE_NEW[0];

    for(i = 0; i < 5; i++)
    {
        hisi_media_mem_array[i].gpu_size     = HISI_MEM_GPU_SIZE_NEW[0];
        hisi_media_mem_array[i].codec_size   = HISI_MEM_CODEC_SIZE_NEW[0];
        hisi_media_mem_array[i].camera_size  = HISI_PMEM_CAMERA_SIZE_NEW[0];
        hisi_media_mem_array[i].gralloc_size = HISI_PMEM_GRALLOC_SIZE_NEW[0];
        hisi_media_mem_array[i].vpp_size     = HISI_MEM_VPP_SIZE_NEW[0];
#if defined(CONFIG_OVERLAY_COMPOSE)
        hisi_media_mem_array[i].overlay_size = HISI_PMEM_OVERLAY_SIZE_NEW[0];
#endif
       hisi_media_mem_array[i].fb_size      = HISI_MEM_FB_SIZE_NEW[0];
	}

    PLAT_MEM_RESERVED_SIZE_NEW = (HISI_MEM_VPP_SIZE_NEW[0] + PLAT_MEM_RAM_CONSOLE_SIZE_NEW[0] \
        + HISI_PMEM_GRALLOC_SIZE_NEW[0] + HISI_MEM_CODEC_SIZE_NEW[0] \
        + HISI_PMEM_CAMERA_SIZE_NEW[0]  + HISI_MEM_GPU_SIZE_NEW[0] \
        + HISI_MEM_FB_SIZE_NEW[0]       + HISI_PMEM_OVERLAY_SIZE_NEW[0]);
	HISI_FRAME_BUFFER_SIZE = HISI_MEM_FB_SIZE_NEW[0];
}

void memset_for_fhd(void)
{
    int i = 0;
    hisi_media_mem.gpu_size      = HISI_MEM_GPU_SIZE_NEW[1];
    hisi_media_mem.codec_size    = HISI_MEM_CODEC_SIZE_NEW[1];
    hisi_media_mem.camera_size   = HISI_PMEM_CAMERA_SIZE_NEW[1];
    hisi_media_mem.gralloc_size  = HISI_PMEM_GRALLOC_SIZE_NEW[1];
    hisi_media_mem.vpp_size      = HISI_MEM_VPP_SIZE_NEW[1];
#if defined(CONFIG_OVERLAY_COMPOSE)
    hisi_media_mem.overlay_size  = HISI_PMEM_OVERLAY_SIZE_NEW[1];
#endif
    hisi_media_mem.fb_size       = HISI_MEM_FB_SIZE_NEW[1];

    for(i = 0; i < 5; i++)
    {
        hisi_media_mem_array[i].gpu_size     = HISI_MEM_GPU_SIZE_NEW[1];
        hisi_media_mem_array[i].codec_size   = HISI_MEM_CODEC_SIZE_NEW[1];
        hisi_media_mem_array[i].camera_size  = HISI_PMEM_CAMERA_SIZE_NEW[1];
		hisi_media_mem_array[i].gralloc_size = HISI_PMEM_GRALLOC_SIZE_NEW[1];
        hisi_media_mem_array[i].vpp_size     = HISI_MEM_VPP_SIZE_NEW[1];
#if defined(CONFIG_OVERLAY_COMPOSE)
       hisi_media_mem_array[i].overlay_size = HISI_PMEM_OVERLAY_SIZE_NEW[1];
#endif
       hisi_media_mem_array[i].fb_size      = HISI_MEM_FB_SIZE_NEW[1];
    }

    PLAT_MEM_RESERVED_SIZE_NEW = (HISI_MEM_VPP_SIZE_NEW[1] + PLAT_MEM_RAM_CONSOLE_SIZE_NEW[1] \
        + HISI_PMEM_GRALLOC_SIZE_NEW[1] + HISI_MEM_CODEC_SIZE_NEW[1] \
        + HISI_PMEM_CAMERA_SIZE_NEW[1]  + HISI_MEM_GPU_SIZE_NEW[1] \
        + HISI_MEM_FB_SIZE_NEW[1]       + HISI_PMEM_OVERLAY_SIZE_NEW[1]);
	HISI_FRAME_BUFFER_SIZE = HISI_MEM_FB_SIZE_NEW[1];
}

static int __init k3v2_ion_setup(char *str)
{
        k3v2_allocate_memory_regions();

        return 1;
}
__setup("k3v2_ion", k3v2_ion_setup);
