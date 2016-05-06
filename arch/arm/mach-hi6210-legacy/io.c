/*
 *  linux/arch/arm/mach-k3v2/io.c
 *
 *  Copyright (C) 1999 - 2003 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
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

#include <linux/module.h>
#include <linux/init.h>
#include <asm/mach/map.h>
#include <mach/io.h>
#include <mach/early-debug.h>
#include <mach/ddr_map.h>
#include <mach/fixmap.h>
/*
 * Intercept ioremap() requests for addresses in our fixed mapping regions.
 */
void __iomem *
k3v2_ioremap(unsigned long phys_addr, size_t size, unsigned int mtype)
{
	void __iomem *v = NULL;

	if (phys_addr > 0xF0000000)
		v = (void *) IO_ADDRESS(phys_addr);

	if (NULL == v)
		v = __arm_ioremap(phys_addr, size, mtype);

	/*
	 * If the physical address was not physical memory or statically
	 * mapped, there's nothing we can do to map it safely.
	 */
	BUG_ON(v == NULL);

	return v;
}
EXPORT_SYMBOL(k3v2_ioremap);

void k3v2_iounmap(void __iomem *addr)
{
	unsigned long virt = (unsigned long)addr;

	if (virt >= VMALLOC_START && virt < VMALLOC_END)
		__iounmap(addr);

	else if (virt < VMALLOC_START)
		WARN(1, "arch ioumap addr 0x%lx is not in VMALLOC area!\n",
			(unsigned long) addr);
}
EXPORT_SYMBOL(k3v2_iounmap);
