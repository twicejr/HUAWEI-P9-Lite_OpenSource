/*
 *  arch/arm/mach-k3v2/include/mach/memory.h
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
#ifndef __MACH_K3V2_MEMORY_H
#define __MACH_K3V2_MEMORY_H
#include <mach/ddr_map.h>
/*
 * Physical DRAM offset.
 */

#define PLAT_PHYS_OFFSET	PLAT_MEM_BASE_ADDR

/*
 * Virtual view <-> DMA view memory address translations
 * virt_to_bus: Used to translate the virtual address to an
 *              address suitable to be passed to set_dma_addr
 * bus_to_virt: Used to convert an address for DMA operations
 *              to an address that the kernel can use.
 */
#define __virt_to_bus(x)	((x) - PAGE_OFFSET + PHYS_OFFSET)
#define __bus_to_virt(x)	((x) - PHYS_OFFSET + PAGE_OFFSET)
#define __pfn_to_bus(x)		__pfn_to_phys(x)
#define __bus_to_pfn(x)		__phys_to_pfn(x)

#define MAX_PHYSMEM_BITS        32
#define SECTION_SIZE_BITS       28

#endif
