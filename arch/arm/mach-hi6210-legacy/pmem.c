/*
 *  linux/arch/arm/mach-hi3620/pmem.c
 *
 *  Copyright (C) 1999 - 2003 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
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
#include <linux/android_pmem.h>
#include <linux/bootmem.h>
#include <mach/hisi_mem.h>

static struct android_pmem_platform_data android_pmem_camera_pdata = {
	.name = "camera_pmem",
	.type = PMEM_TYPE_K3,
	.cached = 0,
};

static struct platform_device android_pmem_camera_device = {
	.name = "android_pmem",
	.id = 1,
	.dev = { .platform_data = &android_pmem_camera_pdata},
};

static struct android_pmem_platform_data android_pmem_gralloc_pdata = {
	.name = "gralloc_pmem",
	.type = PMEM_TYPE_K3,
	.cached = 0,
};

static struct platform_device android_pmem_gralloc_device = {
	.name = "android_pmem",
	.id = 2,
	.dev = { .platform_data = &android_pmem_gralloc_pdata},
};

static struct platform_device *pmem_devs[] __initdata = {
	&android_pmem_camera_device,
	&android_pmem_gralloc_device,
};

unsigned long hisi_reserved_gpu_phymem;
unsigned long hisi_reserved_codec_phymem;
unsigned long hisi_reserved_dumplog_phymem;
unsigned long hisi_reserved_camera_phymem;
unsigned long hisi_reserved_vpp_phymem;
EXPORT_SYMBOL(hisi_reserved_gpu_phymem);
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
};

static struct hisi_reserved_media_memory hisi_media_mem_array[] = {
	[0] = {
		.lcd_name = "hvga",
		.gpu_size = HISI_MEM_GPU_SIZE,
		.codec_size = HISI_MEM_CODEC_SIZE,
		.camera_size = HISI_PMEM_CAMERA_SIZE,
		.gralloc_size = HISI_PMEM_GRALLOC_SIZE,
	},
	[1] = {
		.lcd_name = "vga",
		.gpu_size = HISI_MEM_GPU_SIZE,
		.codec_size = HISI_MEM_CODEC_SIZE,
		.camera_size = HISI_PMEM_CAMERA_SIZE,
		.gralloc_size = HISI_PMEM_GRALLOC_SIZE,
	},
	[2] = {
		.lcd_name = "dvga",
		.gpu_size = HISI_MEM_GPU_SIZE,
		.codec_size = HISI_MEM_CODEC_SIZE,
		.camera_size = HISI_PMEM_CAMERA_SIZE,
		.gralloc_size = HISI_PMEM_GRALLOC_SIZE,
	},
	[3] = {
		.lcd_name = "720p",
		.gpu_size = HISI_MEM_GPU_SIZE,
		.codec_size = HISI_MEM_CODEC_SIZE,
		.camera_size = HISI_PMEM_CAMERA_SIZE,
		.gralloc_size = HISI_PMEM_GRALLOC_SIZE,
	},
	[4] = {
		.lcd_name = "1080p",
		.gpu_size = HISI_MEM_GPU_SIZE,
		.codec_size = HISI_MEM_CODEC_SIZE,
		.camera_size = HISI_PMEM_CAMERA_SIZE,
		.gralloc_size = HISI_PMEM_GRALLOC_SIZE,
	},
};

static struct hisi_reserved_media_memory hisi_media_mem = {
	.lcd_name = "720p",
	.gpu_size = HISI_MEM_GPU_SIZE,
	.codec_size = HISI_MEM_CODEC_SIZE,
	.camera_size = HISI_PMEM_CAMERA_SIZE,
	.gralloc_size = HISI_PMEM_GRALLOC_SIZE,
};

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
		memcpy(hisi_media_mem.lcd_name, p, strlen(p) + 1);

		printk("lcd %s gpu %luMB codec %luMB camera %luMB gralloc %luMB\n",
				hisi_media_mem.lcd_name, hisi_media_mem.gpu_size / SZ_1M,
				hisi_media_mem.codec_size / SZ_1M, hisi_media_mem.camera_size / SZ_1M,
				hisi_media_mem.gralloc_size / SZ_1M);
	} else {
		printk("lcd %s not found!\n", p);
	}

	return 0;
}
early_param("k3v2_lcd_density", early_k3v2_lcd_density);

void __init k3v2_allocate_memory_regions(void)
{
	/* GPU memory */
	hisi_reserved_gpu_phymem = PLAT_MEM_GPU_ADDR;
	printk("pmem allocating %lu bytes at (%lx physical) for gpu "
		"pmem area\n", HISI_MEM_GPU_SIZE, hisi_reserved_gpu_phymem);

	/* CODEC memory */
	hisi_reserved_codec_phymem = PLAT_MEM_CODEC_ADDR; 
	printk("codec pmem allocating %lu bytes at (%lx physical) for codec "
		"pcodec area\n", HISI_MEM_CODEC_SIZE, PLAT_MEM_CODEC_ADDR);

    hisi_reserved_vpp_phymem = PLAT_MEM_VPP_ADDR;
	printk("pmem allocating %lu bytes at (%lx physical) for vpp "
		"pmem area\n", HISI_PMEM_VPP_SIZE, hisi_reserved_vpp_phymem);


	/* CAMERA memory pmem */
	android_pmem_camera_pdata.start = PLAT_MEM_CAMERA_ADDR;
	android_pmem_camera_pdata.size  = HISI_PMEM_CAMERA_SIZE;
	hisi_reserved_camera_phymem = android_pmem_camera_pdata.start;
	printk("camera pmem allocating %lu bytes at (%lx physical) for camera pic\n",
		HISI_PMEM_CAMERA_SIZE, PLAT_MEM_CAMERA_ADDR);
	
	/* video decoder display && camera preview + Thumbnail */
	android_pmem_gralloc_pdata.start = PLAT_MEM_GRALLOC_ADDR;
	android_pmem_gralloc_pdata.size = HISI_PMEM_GRALLOC_SIZE;
	printk("camera pmem allocating %lu bytes at (%lx physical) for gralloc "
		"pmem area\n", HISI_PMEM_GRALLOC_SIZE, PLAT_MEM_GRALLOC_ADDR);
}

static int __init k3v2_pmem_setup(char *str)
{
	k3v2_allocate_memory_regions();

	return 1;
}
__setup("k3v2_pmem", k3v2_pmem_setup);

static int __init k3v2_pmem_init(void)
{
	platform_add_devices(pmem_devs, ARRAY_SIZE(pmem_devs));

	return 0;
}
arch_initcall(k3v2_pmem_init);
