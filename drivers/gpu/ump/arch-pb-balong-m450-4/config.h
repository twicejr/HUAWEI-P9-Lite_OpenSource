/*
 * Copyright (C) 2010-2012 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation, and any use by you of this program is subject to the terms of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained from Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __ARCH_CONFIG_H__
#define __ARCH_CONFIG_H__

#include <mach/hisi_mem.h>

#if 0
/* 0 USING 1 NOTUSING*/
#define UMP_USING_DED_MEMORY            0

/* UMP using memory size*/
#define UMP_MEMORY_SIZE                 (64*SZ_1M)

#define ARCH_UMP_BACKEND_DEFAULT        UMP_USING_DED_MEMORY

#if (UMP_USING_DED_MEMORY == 0)
#define ARCH_UMP_MEMORY_ADDRESS_DEFAULT PLAT_MEM_CAMERA_ADDR//(PLAT_MEM_GPU_ADDR + HISI_FRAME_BUFFER_SIZE + (160*SZ_1M))
#else
#define ARCH_UMP_MEMORY_ADDRESS_DEFAULT 0
#endif

#define ARCH_UMP_MEMORY_SIZE_DEFAULT    UMP_MEMORY_SIZE
#else /*Test for k3v2*/
#define ARCH_UMP_BACKEND_DEFAULT            1
#define ARCH_UMP_MEMORY_ADDRESS_DEFAULT     0
#define ARCH_UMP_MEMORY_SIZE_DEFAULT        64UL * 1024UL * 1024UL
#endif
#endif /* __ARCH_CONFIG_H__ */
