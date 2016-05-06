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

#ifndef __OSL_BIO_H
#define __OSL_BIO_H
#include <product_config.h>
#ifdef __KERNEL__
#ifndef __ASSEMBLY__
#include <linux/io.h>
#include <asm/barrier.h>
static __inline__  void cache_sync(void)
{
	mb();
}
#endif
#include <bsp_memmap.h>

#elif defined(__OS_VXWORKS__)||defined(__OS_RTOSCK__) && !defined(__ASSEMBLY__)
#define isb() __asm__ __volatile__ ("isb" : : : "memory")
#define dsb() __asm__ __volatile__ ("dsb" : : : "memory")
#define dmb() __asm__ __volatile__ ("dmb" : : : "memory")

#define mb()	do { dsb(); SRE_L2CacheWait(); } while (0)
#define rmb()	dmb()
#define wmb()	mb()

extern void SRE_L2CacheWait(void);
static __inline__ void DWB(void) /* drain write buffer */
{
//    asm volatile ( "mcr p15, 0, r0, c7, c10, 4;");
    asm volatile ( "dsb;" );
}
static __inline__  void cache_sync(void)
{
    dsb();
    SRE_L2CacheWait();
}

static __inline__ void writel_relaxed(unsigned val, unsigned addr)
{
    (*(volatile unsigned *) (addr)) = (val);
}
static inline void writew_relaxed(unsigned val, unsigned addr)
{
    (*(volatile unsigned short *) (addr)) = (val);
}

static __inline__ void writeb_relaxed(unsigned val, unsigned addr)
{
    (*(volatile unsigned char *) (addr)) = (val);
}

static __inline__ void writel(unsigned val, unsigned addr)
{
    mb();
    writel_relaxed(val, addr);
}

static inline void writew(unsigned val, unsigned addr)
{
    mb();
    writew_relaxed(val, addr);
}

static __inline__ void writeb(unsigned val, unsigned addr)
{
    mb();
    writeb_relaxed(val, addr);
}

static __inline__ unsigned readl_relaxed(unsigned addr)
{
    return (*(volatile unsigned *) (addr));
}

static inline unsigned readw_relaxed(unsigned addr)
{
    return (*(volatile unsigned short*) (addr));
}

static __inline__ unsigned readb_relaxed(unsigned addr)
{
    return (*(volatile unsigned char*)(addr));
}

static __inline__ unsigned readl(unsigned addr)
{
    return (*(volatile unsigned *) (addr));
}

static inline unsigned readw(unsigned addr)
{
    return (*(volatile unsigned short*) (addr));
}

static __inline__ unsigned readb(unsigned addr)
{
    return (*(volatile unsigned char*)(addr));
}

#endif/*__KERNEL__*/


#ifdef __OS_VXWORKS__
#ifndef __ASSEMBLY__

/* device: strongly-ordered 寄存器都要使用该接口 */
static __inline__ void *ioremap(unsigned phy_addr, unsigned int len)
{
    return (void *)0;
}

/* device: non-cacheable normal */
static __inline__ void *ioremap_wc(unsigned phy_addr, unsigned int len)
{
    return (void *)0;
}
/* memory: normal */
static __inline__ void *ioremap_memory(unsigned phy_addr, unsigned int len)
{
    return (void *)0;
}

#endif
#endif


#ifdef __CMSIS_RTOS
#define isb() __asm__ __volatile__ ("isb" : : : "memory")
#define dsb() __asm__ __volatile__ ("dsb" : : : "memory")
#define dmb() __asm__ __volatile__ ("dmb" : : : "memory")

#define mb()	dsb()
#define rmb()	dmb()
#define wmb()	mb()

 /* drain write buffer */
static inline void DWB(void)
{
	  //asm volatile ( "dsb;" );
}

static inline void ISB(void) /* drain write buffer */
{
	asm volatile ( "isb;");
}

static inline void WFI(void)
{
	asm volatile ( "wfi;");
}

#ifndef writel
static inline void writel(unsigned val, unsigned addr)
{
    DWB();
    (*(volatile unsigned *) (addr)) = (val);
}
#endif

#ifndef writeb
static inline void writeb(unsigned val, unsigned addr)
{
    DWB();
    (*(volatile unsigned char *) (addr)) = (val);
}
#endif

#ifndef readl
static inline unsigned readl(unsigned addr)
{
    return (*(volatile unsigned *) (addr));
}
#endif

#ifndef readb
static inline unsigned readb(unsigned addr)
{
	return (*(volatile unsigned char*)(addr)); 
}
#endif

static __inline__  void cache_sync(void)
{
	return;
}
#endif/*__CMSIS_RTOS*/


#if defined(__OS_RTOSCK__)

#ifndef __ASSEMBLY__
#include <sre_mmu.h>
#include <product_config.h>
enum MMU_MAP_E
{
	MMU_MAP_CCORE = 0,
	MMU_MAP_CCORE_DTS,
	MMU_MAP_GIC,
	MMU_MAP_UART,
#ifdef CONFIG_BALONG_L2CACHE
	MMU_MAP_L2CACHE,
#endif
	MMU_MAP_MAX
};

#define MMU_STATEMASK_ALL (OS_MMU_STATEMASK_ACCESS|OS_MMU_STATEMASK_ATTRIBUTES|OS_MMU_STATEMASK_SHARE)
#define MMU_STATE_RWX (OS_MMU_STATE_READ|OS_MMU_STATE_WRITE|OS_MMU_STATE_EXE)
#define MMU_STATE_RW (OS_MMU_STATE_READ | OS_MMU_STATE_WRITE)
#define MMU_STATE_ROX (OS_MMU_STATE_READ|OS_MMU_STATE_EXE)
/* device: strongly-ordered 寄存器都要使用该接口 */
void *ioremap(MMU_VA_T phy_addr, unsigned int len);

/* device: non-cacheable normal */
void *ioremap_wc(MMU_VA_T phy_addr, unsigned int len);

/* memory: normal */
void *ioremap_memory(MMU_VA_T phy_addr, unsigned int len);
#endif/*__ASSEMBLY__*/

#endif	/* __OS_RTOSCK__ */

#ifdef __KERNEL__
static __inline__ unsigned osl_reg_get_bit(void *reg, unsigned bit_start, unsigned bit_end)
{
	unsigned tmp;
	tmp = readl(reg);
	return ((tmp >> bit_start)&((1 << (bit_end - bit_start + 1))-1));
}

static __inline__ void osl_reg_set_bit(void *reg, unsigned bit_start, unsigned bit_end, unsigned reg_val)
{
	unsigned tmp;
	tmp = readl(reg);
	tmp &= (~(((1 << (bit_end - bit_start + 1))-1) << bit_start));
	tmp |= (reg_val << bit_start);
	writel(tmp, reg);
}
#elif defined(__CMSIS_RTOS)||defined(__OS_RTOSCK__)
static __inline__ unsigned osl_reg_get_bit(void *reg, unsigned bit_start, unsigned bit_end)
{
	unsigned tmp;
	tmp = readl((unsigned long)reg);
	return ((tmp >> bit_start)&((1 << (bit_end - bit_start + 1))-1));
}

static __inline__ void osl_reg_set_bit(void *reg, unsigned bit_start, unsigned bit_end, unsigned reg_val)
{
	unsigned tmp;
	tmp = readl((unsigned long)reg);
	tmp &= (~(((1 << (bit_end - bit_start + 1))-1) << bit_start));
	tmp |= (reg_val << bit_start);
	writel(tmp, (unsigned long)reg);
}
#endif

#endif	/* __OSL_BIO_H */
