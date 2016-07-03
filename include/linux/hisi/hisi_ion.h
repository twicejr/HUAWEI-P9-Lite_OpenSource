/*
 *
 * Copyright (c) 2012, Code Aurora Forum. All rights reserved.
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

#ifndef _LINUX_HISI_ION_H
#define _LINUX_HISI_ION_H

#include <linux/ion.h>
#include <linux/sizes.h>

/**
 * These are the only ids that should be used for Ion heap ids.
 * The ids listed are the order in which allocation will be attempted
 * if specified. Don't swap the order of heap ids unless you know what
 * you are doing!
 * Id's are spaced by purpose to allow new Id's to be inserted in-between (for
 * possible fallbacks)
 */

enum ion_heap_ids {
	INVALID_HEAP_ID = -1,
	ION_SYSTEM_HEAP_ID = 0,
	ION_SYSTEM_CONTIG_HEAP_ID = 1,
	ION_GRALLOC_HEAP_ID = 2,
	ION_DMA_HEAP_ID = 3,
	ION_DMA_POOL_HEAP_ID = 4,
	ION_CPU_DRAW_HEAP_ID = 5,
	ION_CAMERA_HEAP_ID = 6,
	ION_OVERLAY_HEAP_ID = 7,
	ION_VCODEC_HEAP_ID = 8,
	ION_ISP_HEAP_ID = 9,
	ION_FB_HEAP_ID = 10,
	ION_VPU_HEAP_ID = 11,
	ION_JPU_HEAP_ID = 12,
	HISI_ION_HEAP_IOMMU_ID = 13,
	ION_MISC_HEAP_ID = 14,
	ION_DRM_GRALLOC_HEAP_ID=15,
	ION_DRM_VCODEC_HEAP_ID =16,
	ION_TUI_HEAP_ID=17,
	ION_RESERV1_ID=18,
	ION_RESERV2_ID=19,
	ION_RESERV3_ID=20,
	ION_HEAP_ID_RESERVED = 31, /* Bit reserved */
};


/**
 * Macro should be used with ion_heap_ids defined above.
 */
#define ION_HEAP(bit) (1 << (bit))
#define ION_8K_ALIGN(len)  ALIGN(len, SZ_8K)
#define IOMMU_PAGE_SIZE SZ_8K

#define ION_VMALLOC_HEAP_NAME	"vmalloc"
#define ION_KMALLOC_HEAP_NAME	"kmalloc"
#define ION_GRALLOC_HEAP_NAME   "gralloc"


#define ION_SET_CACHED(__cache)		(__cache | ION_FLAG_CACHED)
#define ION_SET_UNCACHED(__cache)	(__cache & ~ION_FLAG_CACHED)

#define ION_IS_CACHED(__flags)	((__flags) & ION_FLAG_CACHED)

//struct used for get phys addr of contig heap
struct ion_phys_data {
	int fd_buffer;
	unsigned int size;
	union {
		unsigned int phys;
		unsigned int phys_l;
	};
	unsigned int phys_h;
};

struct ion_flag_data {
	int shared_fd;
	int flags;
};

#define HISI_ION_NAME_LEN 16

struct ion_heap_info_data{
    char name[HISI_ION_NAME_LEN];
    phys_addr_t heap_phy;
    unsigned int  heap_size;
};
struct ion_kern_va_data {
	int handle_id;
	unsigned int kern_va_h;
	unsigned int kern_va_l;
};
struct ion_issupport_iommu_data{
	int is_support_iommu;
};

struct ion_flush_data {
	int fd;
	void *vaddr;
	unsigned int offset;
	unsigned int length;
};


//user command add for additional use
enum ION_HISI_CUSTOM_CMD {
	ION_HISI_CUSTOM_PHYS,
	ION_HISI_CLEAN_CACHES,
	ION_HISI_INV_CACHES,
	ION_HISI_CLEAN_INV_CACHES,
    ION_HISI_CUSTOM_GET_KERN_VA,
    ION_HISI_CUSTOM_FREE_KERN_VA,
    ION_HISI_CUSTOM_ISSUPPORT_IOMMU,
    ION_HISI_CUSTOM_GET_MEDIA_HEAP_MODE,
    ION_HISI_CUSTOM_SET_FLAG,
};

enum ION_HISI_HEAP_MODE {
    ION_CARVEROUT_MODE=0,
    ION_IOMMU_MODE=1,
};

#define TINY_SYSTEM   0x0        /* tiny version system for chip test*/
#define FULL_SYSTEM   0x1        /* full version system */
/**
 * hisi_ion_client_create() - create iommu mapping for the given handle
 * @heap_mask:	ion heap type mask
 * @name:	the client name
 * @return:     the client handle
 *
 * This function should called by high-level user in kernel. Before users
 * can access a buffer, they should get a client via calling this function.
 */
struct ion_client *
hisi_ion_client_create(const char *name);
int hisi_ion_get_heap_info(unsigned int id,struct ion_heap_info_data* data);
int hisi_ion_get_media_mode(void);
unsigned long long get_system_type(void);
struct ion_device * get_ion_device(void);
#define ION_IOC_HISI_MAGIC 'H'
/**
 *DOC: ION_IOC_FLUSH_ALL_CACHES - flush all the caches pf L1 and L2
 *
 *flush all the caches pf L1 and L2
 */
#define ION_IOC_FLUSH_ALL_CACHES _IOWR(ION_IOC_HISI_MAGIC, 3, \
				struct ion_flush_data)


/*k3 add to calc free memory*/
void hisi_ionsysinfo(struct sysinfo *si);
int ion_handle_get_flags(struct ion_client *client, struct ion_handle *handle,
				unsigned long *flags);
int hisi_ion_memory_info(bool verbose);
#endif
