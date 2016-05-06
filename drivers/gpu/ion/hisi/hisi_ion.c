/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
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

#include <linux/export.h>
#include <linux/err.h>
#include <linux/hisi_ion.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/rwsem.h>
#include <asm/cacheflush.h>
#include <linux/uaccess.h>
#include "../ion_priv.h"
#include <linux/memblock.h>

#ifndef CONFIG_ARM64
#include <asm/outercache.h>
#endif
#define MAX_ION_CPU_DRAW_HEAP_SIZE SZ_64M

/*
 * the groble var alse interface
 * for media module use
 */
unsigned long hisi_reserved_gpu_phymem;
unsigned long hisi_reserved_fb_phymem;
unsigned long hisi_reserved_codec_phymem;
unsigned long hisi_reserved_dumplog_phymem;
unsigned long hisi_reserved_camera_phymem;
unsigned long hisi_reserved_vpp_phymem;
unsigned long hisi_reserved_gralloc_phymem;
unsigned long hisi_reserved_overlay_phymem;

EXPORT_SYMBOL(hisi_reserved_gpu_phymem);
EXPORT_SYMBOL(hisi_reserved_fb_phymem);
EXPORT_SYMBOL(hisi_reserved_codec_phymem);
EXPORT_SYMBOL(hisi_reserved_dumplog_phymem);
EXPORT_SYMBOL(hisi_reserved_camera_phymem);
EXPORT_SYMBOL(hisi_reserved_vpp_phymem);
EXPORT_SYMBOL(hisi_reserved_overlay_phymem);
EXPORT_SYMBOL(hisi_reserved_gralloc_phymem);

#define HISI_LCD_SIZE_NAME 16
struct hisi_reserved_media_mem_size {
    unsigned char lcd_name[HISI_LCD_SIZE_NAME];
    unsigned long gpu_size;
    unsigned long codec_size;
    unsigned long camera_size;
    unsigned long gralloc_size;
	unsigned long vpp_size;
    unsigned long overlay_size;
	unsigned long fb_size;
};

/*
 * media reserve mem defualt size
 */
static struct hisi_reserved_media_mem_size hisi_reserve_media_mem_sz = {
    .lcd_name     = "720p",
    .gpu_size     = PAGE_ALIGN(10 * SZ_1M),
    .codec_size   = PAGE_ALIGN(49 * SZ_1M),
    .camera_size  = PAGE_ALIGN(4 * SZ_1K),
    .gralloc_size = PAGE_ALIGN(172 * SZ_1M),
	.vpp_size     = PAGE_ALIGN(5 * SZ_1M),
    .overlay_size = PAGE_ALIGN(124 * SZ_1M),
	.fb_size = PAGE_ALIGN(14400 * SZ_1K),
};

struct ion_device *hisi_ion_device;
static int num_heaps;
static struct ion_heap **heaps;
static struct device *hisi_ion_dev;

struct ion_client *hisi_ion_client_create(const char *name)
{
	return ion_client_create(hisi_ion_device, name);
}

EXPORT_SYMBOL(hisi_ion_client_create);

struct ion_platform_heap hisi_ion_heap[] = {
     [0] = {
        .type = ION_HEAP_TYPE_CARVEOUT,
        .id   = ION_CAMERA_HEAP_ID,
        .name = "camera",
     },
     [1] = {
        .type = ION_HEAP_TYPE_CARVEOUT,
        .id   = ION_GRALLOC_HEAP_ID,
        .name = "gralloc",
        .cached = 1,                                     
     },
     [2] = {
        .type = ION_HEAP_TYPE_CARVEOUT,
        .id = ION_OVERLAY_HEAP_ID,
        .name = "overlay",
		.cached = 1, 
     },
     [3] = {
        .type = ION_HEAP_TYPE_SYSTEM,
        .id = ION_SYSTEM_HEAP_ID,
        .name = "sys_user",                                                                
     },
     [4] = {
        .type = ION_HEAP_TYPE_SYSTEM_CONTIG,
        .id = ION_SYSTEM_CONTIG_HEAP_ID,
        .name = "sys_contig",                                    
     },                                  
};
static struct ion_platform_data hisi_ion_data = {
    .nr = 5,
    .heaps = &hisi_ion_heap[0],
};


int hisi_ion_get_heap_info(int id,struct ion_heap_info_data* data)
{
     if (!data){
		 printk("=======in [%s]===== data fail======\n",__func__);
		 return -EFAULT;
     }

     switch (id){
    	case ION_GRALLOC_HEAP_ID:
    	{
            data->heap_phy = hisi_reserved_gralloc_phymem;
            data->heap_size = (phys_addr_t)hisi_reserve_media_mem_sz.gralloc_size;
            memcpy((void* )data->name,(void* )hisi_reserve_media_mem_sz.lcd_name,16);

            break;
    	}
    	
    	case ION_CAMERA_HEAP_ID:
    	{
            memcpy((void* )data->name,(void* )hisi_reserve_media_mem_sz.lcd_name,16);
            data->heap_phy = (phys_addr_t)hisi_reserved_camera_phymem;
            data->heap_size = hisi_reserve_media_mem_sz.camera_size;
            break;
    	} 
    	case ION_VCODEC_HEAP_ID:
    	{
            memcpy((void* )data->name,(void* )hisi_reserve_media_mem_sz.lcd_name,16);
            data->heap_phy = (phys_addr_t)hisi_reserved_codec_phymem;
            data->heap_size = hisi_reserve_media_mem_sz.codec_size;
            break;
    	}

    	case ION_OVERLAY_HEAP_ID:
    	{
            memcpy((void* )data->name,(void* )hisi_reserve_media_mem_sz.lcd_name,16);
            data->heap_phy = (phys_addr_t)hisi_reserved_overlay_phymem;
            data->heap_size = hisi_reserve_media_mem_sz.overlay_size;
            break;
    	} 
    	case ION_FB_HEAP_ID:
    	{
            memcpy((void* )data->name,(void* )hisi_reserve_media_mem_sz.lcd_name,16);
            data->heap_phy = (phys_addr_t)hisi_reserved_fb_phymem;
            data->heap_size = hisi_reserve_media_mem_sz.fb_size;
            break;
    	} 
#if  0
    	case ION_VPU_HEAP_ID:
    	{
            data->name = hisi_reserve_media_mem_sz.lcd_name;
            data->heap_phy = hisi_reserved_gralloc_phymem;
            data->heap_size = hisi_reserve_media_mem_sz.gralloc_size;
            break;
    	} 
    	case ION_JPU_HEAP_ID:
    	{
            data->name = hisi_reserve_media_mem_sz.lcd_name;
            data->heap_phy = hisi_reserved_gralloc_phymem;
            data->heap_size = hisi_reserve_media_mem_sz.gralloc_size;
            break;
    	} 
    	case ION_ISP_HEAP_ID:
    	{
            data->name = hisi_reserve_media_mem_sz.lcd_name;
            data->heap_phy = hisi_reserved_gralloc_phymem;
            data->heap_size = hisi_reserve_media_mem_sz.gralloc_size;
            break;
    	} 
#endif
    	default:
    		return -ENOTTY;

     }
     printk("=========lcd name %s id is %d phy %#x size %d==========\n"
            ,data->name,id,(unsigned int)data->heap_phy,(int)data->heap_size);
     return 0;    
}

static int check_vaddr_bounds(unsigned long start, unsigned long end)
{
	struct mm_struct *mm = current->active_mm;
	struct vm_area_struct *vma;
	int ret = 1;

	if(end < start)
		goto out;

	down_read(&mm->mmap_sem);
	vma = find_vma(mm, start);
	if(vma && vma->vm_start < end){
		if(start < vma->vm_start)
			goto out_up;
		if(end > vma->vm_end)
			goto out_up;
		ret = 0;
	}
	out_up:
		up_read(&mm->mmap_sem);
	out:
		return ret;
}


static long hisi_ion_custom_ioctl(struct ion_client *client, unsigned int cmd,
				            unsigned long arg)
{
	int ret = 0;

	switch (cmd) {
    	case ION_HISI_CUSTOM_PHYS:
    	{
    		struct ion_phys_data data;
    		struct ion_handle *handle;

    		if (copy_from_user(&data, (void __user *)arg,
    				sizeof(data))) {
    			return -EFAULT;
    		}

    		handle = ion_import_dma_buf(client, data.fd_buffer);

    		if (IS_ERR(handle)) {
    			pr_err("%s %d : handle %p phy_h 0x%x phy_l 0x%x size 0x%x fd 0x%x\n", __FUNCTION__,
    				   __LINE__, handle, data.phys_h, data.phys_l,
    				  data.size,(unsigned int)data.fd_buffer);
    			return PTR_ERR(handle);
    		}
    		unsigned long phys = 0;
		unsigned long size = 0;
    		ret = ion_phys(client, handle, &phys, &size);
    		if (ret)
    		{
    			ion_free(client, handle);
    			return ret;
            }
		data.phys_h = (unsigned int)((unsigned long long)phys >> 32);
		data.phys_l = (unsigned int )(phys & 0xffffffff);
		data.size = (unsigned int)size;
    		if (copy_to_user((void __user *)arg, &data, sizeof(data)))
    		{
    			ion_free(client, handle);
    			return -EFAULT;
    		}
    		ion_free(client, handle);

    		break;
    	}
    	    
        case ION_HISI_FLUSH_ALL_CACHES:
        {
            struct ion_flush_data data;
            unsigned long long start, end;
            if(copy_from_user(&data, (void __user*)arg,
                            sizeof(struct ion_flush_data)))
            return -EFAULT;

             unsigned long long vaddr = (unsigned long long)((unsigned long long)(data.vaddr_h) << 32) + (unsigned long long )data.vaddr_l;
             start = vaddr;
             end = vaddr + data.length;

            if(check_vaddr_bounds(start, end)){
                pr_err("%s: virtual address %#llx is out of bounds\n",
                                    __func__, vaddr);
                return -EINVAL;
            }

            /*
             * flush L1 cache 
             */
            flush_cache_all();
            #ifndef CONFIG_ARM64
            /*
             * flush L2 cache
             */
            outer_flush_all();
		#endif
        }
        break;
	case ION_HISI_CUSTOM_GET_KERN_VA:
	{
		struct ion_kern_va_data data;
		unsigned long kern_va = 0;

		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}
		printk("====handle is %#x========\n",(unsigned int)data.handle);

        kern_va = (unsigned long)ion_map_kernel(client, data.handle);
		if (!kern_va)
		{
			return -EFAULT;
        } 
        data.kern_va_h = (unsigned int)((unsigned long long)(kern_va) >> 32);
		data.kern_va_l = (unsigned int)(kern_va & 0xffffffff);
		printk("pkern_va_h is 0x%u pkern_va_l 0x%u\n",data.kern_va_h, data.kern_va_l);
        
		if (copy_to_user((void __user *)arg, &data, sizeof(data))) 
		{
            ion_unmap_kernel(client,data.handle);
			return -EFAULT;
		}
		break;
	}
	case ION_HISI_CUSTOM_FREE_KERN_VA:
	{
		struct ion_kern_va_data data;

		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}
		printk("====handle is %#x========\n",(unsigned int)data.handle);

        ion_unmap_kernel(client, data.handle);
        break;
	}

	case ION_HISI_CUSTOM_ISSUPPORT_IOMMU:
	{
        struct ion_issupport_iommu_data data;

		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}

        data.is_support_iommu = 0;
		printk("====iommu_is_init is %#x========\n",(unsigned int)data.is_support_iommu);
        
		if (copy_to_user((void __user *)arg, &data, sizeof(data))) 
		{
			return -EFAULT;
		}

        break;
	}
        
    	default:
    		return -ENOTTY;
    }

	return ret;
}

static int hisi_ion_probe(struct platform_device *pdev)
{
	int i;
	int err;
	struct ion_platform_data *pdata = pdev->dev.platform_data;
        pdata = &hisi_ion_data;
    
	num_heaps = pdata->nr;

	heaps = kzalloc(sizeof(struct ion_heap *) * pdata->nr, GFP_KERNEL);
	if (!heaps)
		return -ENOMEM;

	hisi_ion_device = ion_device_create(&hisi_ion_custom_ioctl);
	if (IS_ERR_OR_NULL(hisi_ion_device)) {
		kfree(heaps);
		return PTR_ERR(hisi_ion_device);
	}

	/* 
	 * create the heaps as specified in the board file
	 */
	for (i = 0; i < num_heaps; i++) {
		struct ion_platform_heap *heap_data = &pdata->heaps[i];

		heaps[i] = ion_heap_create(heap_data);
		if (IS_ERR_OR_NULL(heaps[i])) {
			err = PTR_ERR(heaps[i]);
			goto err;
		}
		ion_device_add_heap(hisi_ion_device, heaps[i]);
		pr_err("%s: adding heap %s of type %d with %lx@%x\n",
                __func__, heap_data->name, heap_data->type,
                heap_data->base, heap_data->size);
	}
	platform_set_drvdata(pdev, hisi_ion_device);

	hisi_ion_dev = &pdev->dev;

	return 0;
err:
	for (i = 0; i < num_heaps; i++) {
		if (heaps[i])
			ion_heap_destroy(heaps[i]);
	}
	kfree(heaps);
	return err;
}

static int hisi_ion_remove(struct platform_device *pdev)
{
	int i;
	struct ion_device *idev = platform_get_drvdata(pdev);

	ion_device_destroy(idev);
	for (i = 0; i < num_heaps; i++){
		ion_heap_destroy(heaps[i]);
	}
	
	kfree(heaps);
	
	return 0;

}

static struct of_device_id hisi_ion_match_table[] = {
	{.compatible = "hisi,k3v2-ion"},
	{.compatible = "hisilicon,hi6xxx-ion"},
	{},
};

static struct platform_driver hisi_ion_driver = {
	.probe = hisi_ion_probe,
	.remove = hisi_ion_remove,
	.driver = {
		.name = "hisi-ion",
		.of_match_table = hisi_ion_match_table,
	},
};

/*
 * the function also call @ mem init
 */
unsigned long hisi_ion_calc_reserve_mem_size(void)
{
    unsigned long reserved = SZ_2M;

    reserved += hisi_reserve_media_mem_sz.gpu_size;
    printk("======gpu_size:[%#x]=========\n",(unsigned int)hisi_reserve_media_mem_sz.gpu_size);

    reserved += hisi_reserve_media_mem_sz.codec_size;
    printk("======codec_size:[%#x]=========\n",(unsigned int)hisi_reserve_media_mem_sz.codec_size);

    reserved += hisi_reserve_media_mem_sz.camera_size;
    printk("======camera_size:[%#x]=========\n",(unsigned int)hisi_reserve_media_mem_sz.camera_size);  

    reserved += hisi_reserve_media_mem_sz.gralloc_size;
    printk("======gralloc_size:[%#x]=========\n",(unsigned int)hisi_reserve_media_mem_sz.gralloc_size);   

	reserved += hisi_reserve_media_mem_sz.vpp_size;
    printk("======vpp_size:[%#x]=========\n",(unsigned int)hisi_reserve_media_mem_sz.vpp_size);   
	
    reserved += hisi_reserve_media_mem_sz.overlay_size;
    printk("======overlay_size:[%#x]=========\n",(unsigned int)hisi_reserve_media_mem_sz.overlay_size);  

	reserved += hisi_reserve_media_mem_sz.fb_size;
    printk("======fb_size:[%#x]=========\n",(unsigned int)hisi_reserve_media_mem_sz.fb_size);
	
    reserved = (reserved & 0xFFF00000) + SZ_1M;

    return reserved;
}
EXPORT_SYMBOL(hisi_ion_calc_reserve_mem_size);



void __init hisi_record_media_mem_regions(void)
{
    unsigned long media_reserved_base = SZ_1G;
    unsigned long media_reserved_size;
    unsigned long size;

    media_reserved_size = hisi_ion_calc_reserve_mem_size();

    media_reserved_base -= (media_reserved_size - SZ_1M);

    /* 
     * GPU memory
     */
    size = hisi_reserve_media_mem_sz.gpu_size;
    hisi_reserved_gpu_phymem = media_reserved_base;
    printk("/+++++++++++++++++++++++++++++++++++++++++/\n");
    printk("ion allocating %lu bytes at (%lx physical) for gpu "
        "pmem area\n", size, media_reserved_base);

    media_reserved_base += size;

    /*
     * CODEC memory 
     */
    size = hisi_reserve_media_mem_sz.codec_size;
    hisi_reserved_codec_phymem = media_reserved_base;
    printk("codec ion allocating %lu bytes at (%lx physical) for codec "
           "pcodec area\n", size, media_reserved_base);


	/*
	 * VPP memory 
	 */           
	media_reserved_base += size;
	size = hisi_reserve_media_mem_sz.vpp_size;
	hisi_reserved_vpp_phymem = media_reserved_base;
	printk("vpp ion allocating %lu bytes at (%lx physical) for vpp "
		   "pmem area\n", size, media_reserved_base);

    /*
     * CAMERA memory pmem
     */
    media_reserved_base += size;
    size = hisi_reserve_media_mem_sz.camera_size;
    if (size) {
        hisi_ion_data.heaps[0].base = media_reserved_base;
        hisi_ion_data.heaps[0].size	= size;
        hisi_reserved_camera_phymem = hisi_ion_data.heaps[0].base;
        printk("camera ion allocating %lu bytes at (%lx physical) for camera pic\n",
                size, media_reserved_base);
    }

    /*
     * video decoder display && camera preview + Thumbnail
     */
    media_reserved_base += size;
    size = hisi_reserve_media_mem_sz.gralloc_size;
    if (size) {
        hisi_ion_data.heaps[1].base = media_reserved_base;
        hisi_ion_data.heaps[1].size	= size;
        hisi_reserved_gralloc_phymem =  hisi_ion_data.heaps[1].base;
        printk("camera ion allocating %lu bytes at (%lx physical) for gralloc "
               "pmem area\n", size, media_reserved_base);
    }


    media_reserved_base += size;
    size = hisi_reserve_media_mem_sz.overlay_size;
    if (size) {
        hisi_ion_data.heaps[2].base = media_reserved_base;
        hisi_ion_data.heaps[2].size	= size;
        hisi_reserved_overlay_phymem = hisi_ion_data.heaps[2].base;
        printk("overlay ion allocating %lu bytes at (%lx physical) for overlay "
               "pmem area\n", size, media_reserved_base);
    }

	/*
	 * FB memory
	 */
    media_reserved_base += size;
	size = hisi_reserve_media_mem_sz.fb_size;
	hisi_reserved_fb_phymem = media_reserved_base;
	printk("fb ion allocating %lu bytes at (%lx physical) for fb "
		   "pmem area\n",size,media_reserved_base);
    printk("/+++++++++++++++++++++++++++++++++++++++++/\n");

}

static int __init hisi_ion_setup(char *str)
{
    printk("====in %s === str = %s====\n",__func__,str);
    hisi_record_media_mem_regions();
    return 1;
}
__setup("hisi_ion", hisi_ion_setup);

void hisi_ion_media_mem_reserve(void)
{
	unsigned long reserved_size;
	phys_addr_t base;

	reserved_size = hisi_ion_calc_reserve_mem_size();

	base = SZ_1G - reserved_size;

	printk("%s the reserved memor region base:0x%08lx size:0x%08lx\n", __func__, (unsigned long)base, reserved_size);

	memblock_remove(base, reserved_size);

}
EXPORT_SYMBOL(hisi_ion_media_mem_reserve);


static int __init hisi_ion_init(void)
{
    printk("========in [%s]===========\n",__func__);
	return platform_driver_register(&hisi_ion_driver);
}

static void __exit hisi_ion_exit(void)
{
	platform_driver_unregister(&hisi_ion_driver);
}
subsys_initcall(hisi_ion_init);
module_exit(hisi_ion_exit);
