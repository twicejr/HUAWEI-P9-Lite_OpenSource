/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __HI_BASE_H__
#define __HI_BASE_H__

#include <osl_bio.h>
#include <bsp_memmap.h>

#if defined(__KERNEL__) 
#undef INLINE
#define INLINE inline

#ifndef HI_SET_GET
#define HI_SET_GET(__full_name__,__reg_name,__reg_type, __reg_base, __reg_offset)  \
	static INLINE void set_##__full_name__(unsigned int val)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((volatile void *)((__reg_base##_VIRT) + __reg_offset)); \
		reg_obj.bits.__reg_name = val; \
		writel(reg_obj.u32, (volatile void *)((__reg_base##_VIRT) + __reg_offset)); \
	} \
	static INLINE unsigned int get_##__full_name__(void)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((volatile void *)((__reg_base##_VIRT) + __reg_offset)); \
		return reg_obj.bits.__reg_name; \
	}
#endif
#elif defined(__CMSIS_RTOS) || (defined(__OS_VXWORKS__) && defined(__GNUC__))
#undef INLINE
#define INLINE inline

#define HI_SET_GET(__full_name__,__reg_name,__reg_type, __reg_base, __reg_offset)  \
	static INLINE void set_##__full_name__(unsigned int val)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((__reg_base##_VIRT) + __reg_offset); \
		reg_obj.bits.__reg_name = val; \
		writel(reg_obj.u32, (__reg_base##_VIRT) + __reg_offset); \
	} \
	static INLINE unsigned int get_##__full_name__(void)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((__reg_base##_VIRT) + __reg_offset); \
		return reg_obj.bits.__reg_name; \
	}

#elif defined(__OS_VXWORKS__)
#undef INLINE
#define INLINE __inline__

#define HI_SET_GET(__full_name__,__reg_name,__reg_type, __reg_base, __reg_offset)  \
	static INLINE void set_##__full_name__(unsigned int val)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((__reg_base##_VIRT) + __reg_offset); \
		reg_obj.bits.##__reg_name = val; \
		writel(reg_obj.u32, (__reg_base##_VIRT) + __reg_offset); \
	} \
	static INLINE unsigned int get_##__full_name__(void)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((__reg_base##_VIRT) + __reg_offset); \
		return reg_obj.bits.##__reg_name; \
	}
#elif defined(__OS_RTOSCK__)
#define HI_SET_GET(__full_name__,__reg_name,__reg_type, __reg_base, __reg_offset)  \
	static inline void set_##__full_name__(unsigned int val)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((__reg_base##_VIRT) + __reg_offset); \
		reg_obj.bits.__reg_name = val; \
		writel(reg_obj.u32, (__reg_base##_VIRT) + __reg_offset); \
	} \
	\
	static inline unsigned int get_##__full_name__(void)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((__reg_base##_VIRT) + __reg_offset); \
		return reg_obj.bits.__reg_name; \
	}
#else

#include <boot/boot.h>
#undef INLINE
#define INLINE inline

#define HI_SET_GET(__full_name__,__reg_name,__reg_type, __reg_base, __reg_offset)  \
	static INLINE void set_##__full_name__(unsigned int val)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((__reg_base##_VIRT) + __reg_offset); \
		reg_obj.bits.__reg_name = val; \
		writel(reg_obj.u32, (__reg_base##_VIRT) + __reg_offset); \
	} \
	static INLINE unsigned int get_##__full_name__(void)  \
	{\
		__reg_type  reg_obj; \
		reg_obj.u32 = readl((__reg_base##_VIRT) + __reg_offset); \
		return reg_obj.bits.__reg_name; \
	}

#endif /* __KERNEL__ */

#endif /* __HI_BASE_H__*/

