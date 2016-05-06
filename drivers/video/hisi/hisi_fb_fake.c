/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>

#include <linux/slab.h>
#include <linux/mm.h>

#include <linux/fb.h>
#include <asm/uaccess.h>
#include <linux/platform_device.h>


#define HISI_FB_NUM	(3)
#define HISI_FB_XRES	(540)
#define HISI_FB_YRES	(960)

static struct fb_info *hisi_fbi;
int g_debug_enable_lcd_sleep_in = 0;

static int hisi_fb_open(struct fb_info *info, int user)
{
	return 0;
}

static int hisi_fb_release (struct fb_info *info, int user)
{
	return 0;
}

static int hisi_fb_mmap(struct fb_info *info,
	struct vm_area_struct *vma)
{
	unsigned long pfn = __phys_to_pfn(virt_to_phys(info->screen_base));

	return remap_pfn_range(vma, vma->vm_start, pfn + vma->vm_pgoff,
		vma->vm_end - vma->vm_start, vma->vm_page_prot);
}

static int hisi_fb_pan_display(struct fb_var_screeninfo *var,
	struct fb_info *info)
{
	return 0;
}

static struct fb_ops hisi_fb_ops = {
	.owner = THIS_MODULE,
	.fb_open = hisi_fb_open,
	.fb_release = hisi_fb_release,
	.fb_check_var = NULL,
	.fb_set_par = NULL,
	.fb_pan_display = hisi_fb_pan_display,
	.fb_ioctl = NULL,
	.fb_mmap = hisi_fb_mmap,
};

static int hisi_fb_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct fb_info *fbi = NULL;
	struct fb_fix_screeninfo *fix = NULL;
	struct fb_var_screeninfo *var = NULL;
	int bpp = 0;

	BUG_ON(pdev == NULL);

	printk("+.\n");

	fbi = framebuffer_alloc(0, NULL);
	if (!fbi) {
		printk("framebuffer_alloc failed!\n");
		return -ENOMEM;
	}

	hisi_fbi = fbi;

	/*
	 * fb info initialization
	 */
	fix = &fbi->fix;
	var = &fbi->var;

	fix->type_aux = 0;
	fix->visual = FB_VISUAL_TRUECOLOR;
	fix->ywrapstep = 0;
	fix->mmio_start = 0;
	fix->mmio_len = 0;
	fix->accel = FB_ACCEL_NONE;

	var->xoffset = 0;
	var->yoffset = 0;
	var->grayscale = 0;
	var->nonstd = 0;
	var->activate = FB_ACTIVATE_VBL;
	var->height = 0;
	var->width = 0;
	var->accel_flags = 0;
	var->sync = 0;
	var->rotate = 0;

	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->xpanstep = 1;
	fix->ypanstep = 1;

	var->vmode = FB_VMODE_NONINTERLACED;
	var->blue.offset = 0;
	var->green.offset = 8;
	var->red.offset = 16;
	var->transp.offset = 24;
	var->blue.length = 8;
	var->green.length = 8;
	var->red.length = 8;
	var->transp.length = 8;
	var->blue.msb_right = 0;
	var->green.msb_right = 0;
	var->red.msb_right = 0;
	var->transp.msb_right = 0;

	bpp = 2;

	var->xres = HISI_FB_XRES;
	var->yres = HISI_FB_YRES;
	var->xres_virtual = HISI_FB_XRES;
	var->yres_virtual = HISI_FB_YRES * HISI_FB_NUM;
	var->bits_per_pixel = bpp * 8;

	snprintf(fix->id, sizeof(fix->id), "hisifb_fake");
	fix->line_length = var->xres * bpp;
	fix->smem_len = roundup(fix->line_length * var->yres_virtual, PAGE_SIZE);
	fix->smem_start = 0;

	fbi->screen_base  = (void *)__get_free_pages(GFP_ATOMIC | __GFP_ZERO | GFP_USER,
		get_order(fix->smem_len));
	if (!fbi->screen_base) {
		printk("__get_free_pages failed!\n");
		return -ENOMEM;
	}

	fbi->screen_size = fix->smem_len;
	memset(fbi->screen_base, 0x0, fix->smem_len);


	fbi->fbops = &hisi_fb_ops;
	fbi->flags = FBINFO_FLAG_DEFAULT | FBINFO_HWACCEL_YPAN | FBINFO_HWACCEL_XPAN;

	if (register_framebuffer(fbi) < 0) {
		printk("failed to register_framebuffer!\n");
		return -EINVAL;
	}

	printk("-.\n");

	return ret;
}

static int hisi_fb_remove(struct platform_device *pdev)
{
	printk("+.\n");

	/* remove /dev/fb* */
	if (hisi_fbi)
		unregister_framebuffer(hisi_fbi);

	printk("-.\n");

	return 0;
}

static struct platform_device this_device = {
	.name = "hisi_fb_fake",
};

static struct platform_driver this_driver = {
	.probe = hisi_fb_probe,
	.remove = hisi_fb_remove,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "hisi_fb_fake",
		.owner = THIS_MODULE,
	},
};

static int __init hisi_fb_init(void)
{
	int ret = 0;

	ret = platform_device_register(&this_device);
	if (ret) {
		printk("platform_device_register failed, error=%d!\n", ret);
		return ret;
	}

	ret = platform_driver_register(&this_driver);
	if (ret) {
		printk("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

static void __exit hisi_fb_exit(void)
{
	platform_driver_unregister(&this_driver);
	platform_device_unregister(&this_device);
}

module_init(hisi_fb_init);
