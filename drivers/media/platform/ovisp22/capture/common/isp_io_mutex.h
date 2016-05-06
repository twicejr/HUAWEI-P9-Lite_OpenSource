/*
 *  arch/arm/mach-k3v2/include/mach/io_mutex.h
 *
 *  Copyright (C) 2011 Hisilicon Co. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __MACH_K3V2_IO_MUTEX_H
#define __MACH_K3V2_IO_MUTEX_H

#include <linux/spinlock.h>

extern spinlock_t io_lock;

#define readl_mutex(addr)  \
({ u32 __v;   \
	unsigned long flags;  \
	spin_lock_irqsave(&io_lock, flags);  \
	__v = readl(addr);  \
	spin_unlock_irqrestore(&io_lock, flags);  \
	__v; })

#define writel_mutex(reg, addr) \
({ 	unsigned long flags;  \
	spin_lock_irqsave(&io_lock, flags);  \
	writel((reg), (addr));  \
	spin_unlock_irqrestore(&io_lock, flags);})

#define ioread8_mutex(p) \
({ u8 __v;   \
	unsigned long flags;  \
	spin_lock_irqsave(&io_lock, flags);  \
	__v = ioread8((p));  \
	spin_unlock_irqrestore(&io_lock, flags); \
	__v; })

#define ioread32_mutex(p) \
({ u32 __v;   \
	unsigned long flags;  \
	spin_lock_irqsave(&io_lock, flags);  \
	__v = ioread32((p));  \
	spin_unlock_irqrestore(&io_lock, flags); \
	__v; })

#define iowrite8_mutex(v,p)  \
({ 	unsigned long flags;  \
	spin_lock_irqsave(&io_lock, flags);  \
	iowrite8((v), (void __iomem *)(p));  \
	spin_unlock_irqrestore(&io_lock, flags);})

#define iowrite16_mutex(v,p)  \
({ 	unsigned long flags;  \
	spin_lock_irqsave(&io_lock, flags);  \
	iowrite16((v), (void __iomem *)(p));  \
	spin_unlock_irqrestore(&io_lock, flags);})

#define iowrite32_mutex(v,p)  \
({ 	unsigned long flags;  \
	spin_lock_irqsave(&io_lock, flags);  \
	iowrite32((v), (void __iomem *)(p));  \
	spin_unlock_irqrestore(&io_lock, flags);})

#define readl_gpu_mutex(addr) \
({ 	u32 __v;\
	unsigned long flags; \
	spin_lock_irqsave(&io_lock, flags);  \
	do { \
		writel(G3D_CPU_LOCK_VALUE, G3D_LOCK); \
	} while ((readl(G3D_LOCK_ST) & G3D_LOCK_MASK) != G3D_CPU_LOCK_VALUE); \
	__v = readl(addr); \
	writel(G3D_CPU_LOCK_VALUE, G3D_UNLOCK); \
	spin_unlock_irqrestore(&io_lock, flags); \
	__v; })

#define writel_asp_mutex(reg, addr) \
({ 	unsigned long flags;  \
	spin_lock_irqsave(&io_lock, flags);  \
	do { \
		writel(G3D_CPU_LOCK_VALUE, G3D_LOCK); \
	} while ((readl(G3D_LOCK_ST) & G3D_LOCK_MASK) != G3D_CPU_LOCK_VALUE); \
	writel((reg), (addr));  \
	writel(G3D_CPU_LOCK_VALUE, G3D_UNLOCK); \
	spin_unlock_irqrestore(&io_lock, flags);})

#define writel_gpu_mutex(reg, addr) writel_asp_mutex(reg, addr)
#endif/*__MACH_K3V2_IO_MUTEX_H*/
