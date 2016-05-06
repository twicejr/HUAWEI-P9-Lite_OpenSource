#ifndef _HI_MEM_INCLUDE_H_
#define _HI_MEM_INCLUDE_H_

#include <linux/mm.h>
#include <mach/ddr_map.h>

void __init hisi_allocate_memory_regions(void);

extern unsigned long hisi_reserved_codec_phymem;
extern unsigned long hisi_reserved_gpu_phymem;
extern unsigned long hisi_reserved_fb_phymem;
extern unsigned long hisi_reserved_dumplog_phymem;
extern unsigned long hisi_reserved_camera_phymem;
extern unsigned long hisi_reserved_vpp_phymem;
extern unsigned long PLAT_MEM_RESERVED_SIZE_NEW;
extern unsigned long HISI_MEM_FB_SIZE_NEW[];
extern unsigned long HISI_FRAME_BUFFER_SIZE;

#ifndef ALIGN_UP
#define ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#endif
#ifndef ALIGN_DOWN
#define ALIGN_DOWN(x, align)  ((x) & ~((align)-1))
#endif
#ifndef STRIDE_ALIGN
#define STRIDE_ALIGN(stride)	\
	((((stride) / 64) % 2 == 0) ? ((stride) + 64) : (stride))
#endif
#ifdef CONFIG_MACH_HI6620OEM
/* ASIC»ØÆ¬°æ±¾DDRÊÇ2GB */
#define HISI_BASE_MEMORY_SIZE   (SZ_2G)
#else
#define HISI_BASE_MEMORY_SIZE	(SZ_1G)
#endif

#define HISI_MEM_FB_SIZE PLAT_MEM_FRAMEBUFFER_SIZE
#define HISI_MEM_GPU_SIZE	PLAT_MEM_GPU_SIZE
#define HISI_PMEM_CAMERA_SIZE	PLAT_MEM_CAMERA_SIZE
#define HISI_MEM_CODEC_SIZE	PLAT_MEM_CODEC_SIZE
#define HISI_PMEM_GRALLOC_SIZE	PLAT_MEM_GRALLOC_SIZE
#define HISI_MEM_VPP_SIZE   PLAT_MEM_VPP_SIZE
#define HISI_PMEM_OVERLAY_SIZE	PLAT_MEM_OVERLAY_SIZE

/* temp */
#define CAMERA_PREVIEW_BUF_BASE (hisi_reserved_camera_phymem)
#define CAMERA_PREVIEW_BUF_SIZ	(hisi_reserved_media_phymem)

/* alloc from HISI_MEM_GPU_SIZE */
#define HIGPU_BUF_BASE	(hisi_reserved_gpu_phymem)
#define HIGPU_BUF_SIZE	PLAT_MEM_GPU_SIZE

//#define HIGPU_BUF_SIZE	(HISI_MEM_GPU_SIZE - HISI_FRAME_BUFFER_SIZE)

#define HISI_FRAME_BUFFER_BASE    (hisi_reserved_fb_phymem)


unsigned long hisi_get_reserve_mem_size(void);
#endif /* end _HI_MEM_INCLUDE_H_ */

