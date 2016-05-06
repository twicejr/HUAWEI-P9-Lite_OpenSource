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

#ifndef __OSL_IO_H
#define __OSL_IO_H

#ifdef __KERNEL__
#include <linux/io.h>

#else /* __KERNEL__ */

#include <osl_types.h>
#include <asm/byteorder.h>
#include <asm/memory.h>
#include <asm-generic/pci_iomap.h>

# define __force	
# define __iomem
# define __chk_io_ptr(x) (void)0

/*
 * ISA I/O bus memory addresses are 1:1 with the physical address.
 */
#define isa_virt_to_bus virt_to_phys
#define isa_page_to_bus page_to_phys
#define isa_bus_to_virt phys_to_virt

/*
 * Generic IO read/write.  These perform native-endian accesses.  Note
 * that some architectures will want to re-define __raw_{read,write}w.
 */
extern void __raw_writesb(void __iomem *addr, const void *data, int bytelen);
extern void __raw_writesw(void __iomem *addr, const void *data, int wordlen);
extern void __raw_writesl(void __iomem *addr, const void *data, int longlen);

extern void __raw_readsb(const void __iomem *addr, void *data, int bytelen);
extern void __raw_readsw(const void __iomem *addr, void *data, int wordlen);
extern void __raw_readsl(const void __iomem *addr, void *data, int longlen);

#define __raw_writeb(v,a)	(__chk_io_ptr(a), *(volatile unsigned char __force  *)(a) = (v))
#define __raw_writew(v,a)	(__chk_io_ptr(a), *(volatile unsigned short __force *)(a) = (v))
#define __raw_writel(v,a)	(__chk_io_ptr(a), *(volatile unsigned int __force   *)(a) = (v))

#define __raw_readb(a)		(__chk_io_ptr(a), *(volatile unsigned char __force  *)(a))
#define __raw_readw(a)		(__chk_io_ptr(a), *(volatile unsigned short __force *)(a))
#define __raw_readl(a)		(__chk_io_ptr(a), *(volatile unsigned int __force   *)(a))


/*
 * A typesafe __io() helper
 */
static inline void __iomem *__typesafe_io(unsigned long addr)
{
	return (void __iomem *)addr;
}

#define IOMEM(x)	((void __force __iomem *)(x))

/* IO barriers */
#ifdef CONFIG_ARM_DMA_MEM_BUFFERABLE
#include <asm/barrier.h>
#define __iormb()		rmb()
#define __iowmb()		wmb()
#else
#define __iormb()		do { } while (0)
#define __iowmb()		do { } while (0)
#endif

/*
 * Now, pick up the machine-defined IO definitions
 */
#define __io(a)		__typesafe_io((a) & IO_SPACE_LIMIT)


/*
 * This is the limit of PC card/PCI/ISA IO space, which is by default
 * 64K if we have PC card, PCI or ISA support.  Otherwise, default to
 * zero to prevent ISA/PCI drivers claiming IO space (and potentially
 * oopsing.)
 *
 * Only set this larger if you really need inb() et.al. to operate over
 * a larger address space.  Note that SOC_COMMON ioremaps each sockets
 * IO space area, and so inb() et.al. must be defined to operate as per
 * readb() et.al. on such platforms.
 */
#define IO_SPACE_LIMIT ((resource_size_t)0)

/*
 *  IO port access primitives
 *  -------------------------
 *
 * The ARM doesn't have special IO access instructions; all IO is memory
 * mapped.  Note that these are defined to perform little endian accesses
 * only.  Their primary purpose is to access PCI and ISA peripherals.
 *
 * Note that for a big endian machine, this implies that the following
 * big endian mode connectivity is in place, as described by numerous
 * ARM documents:
 *
 *    PCI:  D0-D7   D8-D15 D16-D23 D24-D31
 *    ARM: D24-D31 D16-D23  D8-D15  D0-D7
 *
 * The machine specific io.h include defines __io to translate an "IO"
 * address to a memory address.
 *
 * Note that we prevent GCC re-ordering or caching values in expressions
 * by introducing sequence points into the in*() definitions.  Note that
 * __raw_* do not guarantee this behaviour.
 *
 * The {in,out}[bwl] macros are for emulating x86-style PCI/ISA IO space.
 */
#ifdef __io
#define outb(v,p)	({ __iowmb(); __raw_writeb(v,__io(p)); })
#define outw(v,p)	({ __iowmb(); __raw_writew((__force __u16) \
					cpu_to_le16(v),__io(p)); })
#define outl(v,p)	({ __iowmb(); __raw_writel((__force __u32) \
					cpu_to_le32(v),__io(p)); })

#define inb(p)	({ __u8 __v = __raw_readb(__io(p)); __iormb(); __v; })
#define inw(p)	({ __u16 __v = le16_to_cpu((__force __le16) \
			__raw_readw(__io(p))); __iormb(); __v; })
#define inl(p)	({ __u32 __v = le32_to_cpu((__force __le32) \
			__raw_readl(__io(p))); __iormb(); __v; })

#define outsb(p,d,l)		__raw_writesb(__io(p),d,l)
#define outsw(p,d,l)		__raw_writesw(__io(p),d,l)
#define outsl(p,d,l)		__raw_writesl(__io(p),d,l)

#define insb(p,d,l)		__raw_readsb(__io(p),d,l)
#define insw(p,d,l)		__raw_readsw(__io(p),d,l)
#define insl(p,d,l)		__raw_readsl(__io(p),d,l)
#endif

#define outb_p(val,port)	outb((val),(port))
#define outw_p(val,port)	outw((val),(port))
#define outl_p(val,port)	outl((val),(port))
#define inb_p(port)		inb((port))
#define inw_p(port)		inw((port))
#define inl_p(port)		inl((port))

#define outsb_p(port,from,len)	outsb(port,from,len)
#define outsw_p(port,from,len)	outsw(port,from,len)
#define outsl_p(port,from,len)	outsl(port,from,len)
#define insb_p(port,to,len)	insb(port,to,len)
#define insw_p(port,to,len)	insw(port,to,len)
#define insl_p(port,to,len)	insl(port,to,len)

/*
 * String version of IO memory access ops:
 */
extern void _memcpy_fromio(void *, const volatile void __iomem *, size_t);
extern void _memcpy_toio(volatile void __iomem *, const void *, size_t);
extern void _memset_io(volatile void __iomem *, int, size_t);

#define mmiowb()

/*
 *  Memory access primitives
 *  ------------------------
 *
 * These perform PCI memory accesses via an ioremap region.  They don't
 * take an address as such, but a cookie.
 *
 * Again, this are defined to perform little endian accesses.  See the
 * IO port primitives for more information.
 */
#ifndef readl
#define readb_relaxed(c) ({ u8  __r = __raw_readb(c); __r; })
#define readw_relaxed(c) ({ u16 __r = le16_to_cpu((__force __le16) \
					__raw_readw(c)); __r; })
#define readl_relaxed(c) ({ u32 __r = le32_to_cpu((__force __le32) \
					__raw_readl(c)); __r; })

#define writeb_relaxed(v,c)	((void)__raw_writeb(v,c))
#define writew_relaxed(v,c)	((void)__raw_writew((__force u16) \
					cpu_to_le16(v),c))
#define writel_relaxed(v,c)	((void)__raw_writel((__force u32) \
					cpu_to_le32(v),c))

#define readb(c)		({ u8  __v = readb_relaxed(c); __iormb(); __v; })
#define readw(c)		({ u16 __v = readw_relaxed(c); __iormb(); __v; })
#define readl(c)		({ u32 __v = readl_relaxed(c); __iormb(); __v; })

#define writeb(v,c)		({ __iowmb(); writeb_relaxed(v,c); })
#define writew(v,c)		({ __iowmb(); writew_relaxed(v,c); })
#define writel(v,c)		({ __iowmb(); writel_relaxed(v,c); })

#define readsb(p,d,l)		__raw_readsb(p,d,l)
#define readsw(p,d,l)		__raw_readsw(p,d,l)
#define readsl(p,d,l)		__raw_readsl(p,d,l)

#define writesb(p,d,l)		__raw_writesb(p,d,l)
#define writesw(p,d,l)		__raw_writesw(p,d,l)
#define writesl(p,d,l)		__raw_writesl(p,d,l)

#define memset_io(c,v,l)	_memset_io(c,(v),(l))
#define memcpy_fromio(a,c,l)	_memcpy_fromio((a),c,(l))
#define memcpy_toio(c,a,l)	_memcpy_toio(c,(a),(l))

#endif	/* readl */

/*
 * ioremap and friends.
 *
 * ioremap takes a PCI memory address, as specified in
 * Documentation/io-mapping.txt.
 *
 */
#define ioremap(cookie,size)		(cookie)
#define ioremap_nocache(cookie,size) (cookie)
#define iounmap				

/*
 * io{read,write}{8,16,32} macros
 */
#ifndef ioread8
#define ioread8(p)	({ unsigned int __v = __raw_readb(p); __iormb(); __v; })
#define ioread16(p)	({ unsigned int __v = le16_to_cpu((__force __le16)__raw_readw(p)); __iormb(); __v; })
#define ioread32(p)	({ unsigned int __v = le32_to_cpu((__force __le32)__raw_readl(p)); __iormb(); __v; })

#define ioread16be(p)	({ unsigned int __v = be16_to_cpu((__force __be16)__raw_readw(p)); __iormb(); __v; })
#define ioread32be(p)	({ unsigned int __v = be32_to_cpu((__force __be32)__raw_readl(p)); __iormb(); __v; })

#define iowrite8(v,p)	({ __iowmb(); (void)__raw_writeb(v, p); })
#define iowrite16(v,p)	({ __iowmb(); (void)__raw_writew((__force __u16)cpu_to_le16(v), p); })
#define iowrite32(v,p)	({ __iowmb(); (void)__raw_writel((__force __u32)cpu_to_le32(v), p); })

#define iowrite16be(v,p) ({ __iowmb(); (void)__raw_writew((__force __u16)cpu_to_be16(v), p); })
#define iowrite32be(v,p) ({ __iowmb(); (void)__raw_writel((__force __u32)cpu_to_be32(v), p); })

#define ioread8_rep(p,d,c)	__raw_readsb(p,d,c)
#define ioread16_rep(p,d,c)	__raw_readsw(p,d,c)
#define ioread32_rep(p,d,c)	__raw_readsl(p,d,c)

#define iowrite8_rep(p,s,c)	__raw_writesb(p,s,c)
#define iowrite16_rep(p,s,c)	__raw_writesw(p,s,c)
#define iowrite32_rep(p,s,c)	__raw_writesl(p,s,c)

extern void __iomem *ioport_map(unsigned long port, unsigned int nr);
extern void ioport_unmap(void __iomem *addr);
#endif



#endif	/* __KERNEL__ */
#endif	/* __ASM_ARM_IO_H */
