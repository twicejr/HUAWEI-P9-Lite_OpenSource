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

#ifndef __OSL_TYPES_H
#define __OSL_TYPES_H

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#else
#if defined(__CMSIS_RTOS) || defined(__OS_VXWORKS__) ||defined(__OS_RTOSCK__) /* linux中有bool枚举定义 */
#ifndef bool
typedef enum {
	false	= 0,
	true	= 1
}bool;
#endif /* bool */
#endif

#endif /* __cplusplus */

typedef unsigned int        BSP_U32;

#ifdef __KERNEL__
#include <linux/types.h>
#ifndef __ASSEMBLY__
#define UNUSED(a) (a=a)
#endif

#ifndef __inline__
#define __inline__ inline
#endif

#elif defined(_WRS_KERNEL) || defined(__OS_VXWORKS__) ||  defined(__OS_RTOSCK__)

#ifndef __ASSEMBLY__
#ifdef __OS_VXWORKS__
#ifndef inline
#define inline __inline__
#endif
#else

#endif

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;
typedef unsigned short __be16;

typedef signed int s32;
typedef unsigned int u32;
typedef unsigned int __be32;

typedef signed long long s64;
typedef unsigned long long u64;

#ifdef __OS_RTOSCK__
#ifndef uint32_t
typedef unsigned int uint32_t;
#endif

#ifndef size_t
typedef unsigned int size_t;
#endif
#endif

#define S8_C(x)  x
#define U8_C(x)  x ## U
#define S16_C(x) x
#define U16_C(x) x ## U
#define S32_C(x) x
#define U32_C(x) x ## U
#define S64_C(x) x ## LL
#define U64_C(x) x ## ULL
#define UNUSED(a) (a=a)


#else /* __ASSEMBLY__ */

#define S8_C(x)  x
#define U8_C(x)  x
#define S16_C(x) x
#define U16_C(x) x
#define S32_C(x) x
#define U32_C(x) x
#define S64_C(x) x
#define U64_C(x) x

#endif /* __ASSEMBLY__ */

#ifndef __ASSEMBLY__

/* compiler.h */
/*
 * This is used to ensure the compiler did actually allocate the register we
 * asked it for some inline assembly sequences.  Apparently we can't trust
 * the compiler from one version to another so a bit of paranoia won't hurt.
 * This string is meant to be concatenated with the inline asm string and
 * will cause compilation to stop on mismatch.
 * (for details, see gcc PR 15089)
 */
#define __asmeq(x, y)  ".ifnc " x "," y " ; .err ; .endif\n\t"

/* stddef.h */
#undef NULL
#define NULL ((void *)0)

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((u32) &((TYPE *)0)->MEMBER)
#endif

#endif /* __ASSEMBLY__ */

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) 			\
	 ((type *)((char *)(ptr) - offsetof(type,member)))


#ifndef printk
#define printk  printf
#endif

#elif defined(__CMSIS_RTOS) || defined(__FASTBOOT__)

#ifndef __ASSEMBLY__

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((u32) &((TYPE *)0)->MEMBER)
#endif
/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) 			\
	 ((type *)((char *)(ptr) - offsetof(type,member)))
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

/* stddef.h */
#undef NULL
#define NULL ((void *)0)

#define UNUSED(a) (a=a)

#endif

#else

#ifndef __ASSEMBLY__
typedef unsigned int u32;
#endif

#endif /* __KERNEL__ */

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif

