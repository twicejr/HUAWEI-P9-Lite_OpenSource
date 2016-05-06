#ifndef _HI_MEM_MAP_INCLUDE_H_
#define _HI_MEM_MAP_INCLUDE_H_

#include <linux/types.h>
#include "global_ddr_map.h"

/******************************************************************************************
Linux 物理内存分配

低地址-------> 高地址
|<-- sys memory -->|<- gralloc ->|<- codec ->|<- camera ->|<- gpu ->|

分配原则把给A核的内存减去媒体保留内存，剩余全部给Linux系统使用
*******************************************************************************************/

#define PLAT_MEM_BASE_ADDR 	 	     		(ANDROID_SYS_MEM_ADDR)
#define PLAT_MEM_SIZE						(ANDROID_SYS_MEM_SIZE)
#define PLAT_MEM_OFFSET  			    	((phys_addr_t)ANDROID_SYS_MEM_ADDR + ANDROID_SYS_MEM_SIZE)


#ifndef STRIDE_ALIGN
#define STRIDE_ALIGN(stride)	\
	((((stride) / 64) % 2 == 0) ? ((stride) + 64) : (stride))
#endif
#define HDMI_XRES	(1440)
#define HDMI_YRES	(1050)
#define NUM_HDMI_BUFFERS	(3)
#if defined(BOARD_ASIC)
#define PLAT_MEM_FRAMEBUFFER_SIZE		PAGE_ALIGN(1280 * (STRIDE_ALIGN(ALIGN_UP((720 * 4), 64))) * 4)	 //14400k
#define PLAT_MEM_GPU_SIZE   			PAGE_ALIGN(SZ_16M)
#define PLAT_MEM_GPU_ADDR               (PLAT_MEM_OFFSET - PLAT_MEM_GPU_SIZE)

#define PLAT_MEM_CAMERA_SIZE 			PAGE_ALIGN(4 * SZ_1K)
#define PLAT_MEM_CAMERA_ADDR  			(PLAT_MEM_GPU_ADDR - PLAT_MEM_CAMERA_SIZE)

#define PLAT_MEM_CODEC_SIZE 			PAGE_ALIGN(52 * SZ_1M)
#define PLAT_MEM_CODEC_ADDR  			(PLAT_MEM_CAMERA_ADDR - PLAT_MEM_CODEC_SIZE)

#define PLAT_MEM_GRALLOC_SIZE 			PAGE_ALIGN(182 * SZ_1M + 512 * SZ_1K)
#define PLAT_MEM_GRALLOC_ADDR  			(PLAT_MEM_CODEC_ADDR - PLAT_MEM_GRALLOC_SIZE)

#define PLAT_MEM_RAM_CONSOLE_SIZE		PAGE_ALIGN(SZ_64K)
#define PLAT_MEM_RAM_CONSOLE_ADDR  		(PLAT_MEM_GRALLOC_ADDR - PLAT_MEM_RAM_CONSOLE_SIZE)

#define PLAT_MEM_VPP_SIZE               PAGE_ALIGN(5 * SZ_1M)
#define PLAT_MEM_VPP_ADDR               (PLAT_MEM_RAM_CONSOLE_ADDR - PLAT_MEM_VPP_SIZE)

#define PLAT_MEM_OVERLAY_SIZE           PAGE_ALIGN(124 * SZ_1M)
#define PLAT_MEM_OVERLAY_ADDR           (PLAT_MEM_VPP_ADDR - PLAT_MEM_OVERLAY_SIZE)

                                        /*reserved size = 192 + 16 + 80 + 41 + 78 + 5 + 64K = 412M + 64K*/
#define PLAT_MEM_RESERVED_SIZE          (PLAT_MEM_VPP_SIZE + PLAT_MEM_RAM_CONSOLE_SIZE \
                                        + PLAT_MEM_GRALLOC_SIZE + PLAT_MEM_CODEC_SIZE \
                                        + PLAT_MEM_CAMERA_SIZE  + PLAT_MEM_GPU_SIZE \
                                        + PLAT_MEM_FRAMEBUFFER_SIZE + PLAT_MEM_OVERLAY_SIZE)
#else
#define PLAT_MEM_FRAMEBUFFER_SIZE		PAGE_ALIGN(1280 * (STRIDE_ALIGN(ALIGN_UP((720 * 4), 64))) * 4)	 //14400k
#define PLAT_MEM_GPU_SIZE   			PAGE_ALIGN(128 * SZ_1M + PAGE_ALIGN(HDMI_XRES * HDMI_YRES * 4 *NUM_HDMI_BUFFERS))  //128M + 17720k
#define PLAT_MEM_GPU_ADDR               (PLAT_MEM_OFFSET - PLAT_MEM_GPU_SIZE)

#define PLAT_MEM_CAMERA_SIZE 			PAGE_ALIGN(4 * SZ_1K)
#define PLAT_MEM_CAMERA_ADDR  			(PLAT_MEM_GPU_ADDR - PLAT_MEM_CAMERA_SIZE)

#define PLAT_MEM_CODEC_SIZE 			PAGE_ALIGN(49 * SZ_1M)
#define PLAT_MEM_CODEC_ADDR  			(PLAT_MEM_CAMERA_ADDR - PLAT_MEM_CODEC_SIZE)

#define PLAT_MEM_GRALLOC_SIZE 			PAGE_ALIGN(62 * SZ_1M)
#define PLAT_MEM_GRALLOC_ADDR  			(PLAT_MEM_CODEC_ADDR - PLAT_MEM_GRALLOC_SIZE)

#define PLAT_MEM_RAM_CONSOLE_SIZE		PAGE_ALIGN(SZ_64K)
#define PLAT_MEM_RAM_CONSOLE_ADDR  		(PLAT_MEM_GRALLOC_ADDR - PLAT_MEM_RAM_CONSOLE_SIZE)

#define PLAT_MEM_VPP_SIZE               PAGE_ALIGN(5 * SZ_1M)
#define PLAT_MEM_VPP_ADDR               (PLAT_MEM_RAM_CONSOLE_ADDR - PLAT_MEM_VPP_SIZE)

#define PLAT_MEM_OVERLAY_SIZE           PAGE_ALIGN(72 * SZ_1M)
#define PLAT_MEM_OVERLAY_ADDR           (PLAT_MEM_VPP_ADDR - PLAT_MEM_OVERLAY_SIZE)

                                        /*reserved size = 192 + 16 + 80 + 41 + 78 + 5 + 64K = 412M + 64K*/
#define PLAT_MEM_RESERVED_SIZE          (PLAT_MEM_VPP_SIZE + PLAT_MEM_RAM_CONSOLE_SIZE \
                                        + PLAT_MEM_GRALLOC_SIZE + PLAT_MEM_CODEC_SIZE \
                                        + PLAT_MEM_CAMERA_SIZE  + PLAT_MEM_GPU_SIZE \
                                        + PLAT_MEM_FRAMEBUFFER_SIZE + PLAT_MEM_OVERLAY_SIZE)
#endif



#endif
