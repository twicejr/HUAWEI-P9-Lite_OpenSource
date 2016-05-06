/*
 *  arch/arm/mach-k3v2/include/mach/io.h
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
#ifndef __MACH_K3V2_IO_H
#define __MACH_K3V2_IO_H

#include <asm/mach-types.h>
#include <mach/hardware.h>
#include <mach/platform.h>
#include <mach/fixmap.h>

#define IO_SPACE_LIMIT 0xffffffff

#define __io(a)	((void __iomem *) a)
#define __mem_pci(a)	(a)

#define IO_TO_VIRT_BETWEEN(p, name)	(((p) >= (REG_BASE_##name)) && ((p) < ((REG_BASE_##name) + (REG_##name##_IOSIZE))))
#define IO_TO_VIRT_XLATE(p, name)	(((p) - (REG_BASE_##name) + (REG_BASE_##name##_VIRT)))

#define IPC_SHARE_MEM_TO_VIRT_BETWEEN(p)  (((p) >= (IPC_SHARE_MEM_ADDR)) && ((p) < ((IPC_SHARE_MEM_ADDR) + (IPC_SHARE_MEM_SIZE))))
#define IPC_SHARE_MEM_TO_VIRT_XLATE(p)	(((p) - (IPC_SHARE_MEM_ADDR) + (IPC_SHARE_MEM_VIRT_ADDR)))

#define IO_TO_VIRT_PRE(n) ( \
	IO_TO_VIRT_BETWEEN((n), SRAM_OFF) ?	\
		IO_TO_VIRT_XLATE((n), SRAM_OFF) : 	\
	IO_TO_VIRT_BETWEEN((n), SC_OFF) ?	\
		IO_TO_VIRT_XLATE((n), SC_OFF) : 	\
	IO_TO_VIRT_BETWEEN((n), SC_ON) ?	\
		IO_TO_VIRT_XLATE((n), SC_ON) : 	\
	IO_TO_VIRT_BETWEEN((n), TIMER0) ?	\
		IO_TO_VIRT_XLATE((n), TIMER0) : 	\
	IO_TO_VIRT_BETWEEN((n), TIMER3) ?	\
		IO_TO_VIRT_XLATE((n), TIMER3) : 	\
	IO_TO_VIRT_BETWEEN((n), TIMER4) ?	\
		IO_TO_VIRT_XLATE((n), TIMER4) : 	\
	IO_TO_VIRT_BETWEEN((n), IPF) ?	\
		IO_TO_VIRT_XLATE((n), IPF) : 	\
	IO_TO_VIRT_BETWEEN((n), PMCTRL) ?	\
		IO_TO_VIRT_XLATE((n), PMCTRL) : \
	IO_TO_VIRT_BETWEEN((n), A9PRI) ?	\
		IO_TO_VIRT_XLATE((n), A9PRI) : 	\
	IO_TO_VIRT_BETWEEN((n), IOC_OFF) ?	\
		IO_TO_VIRT_XLATE((n), IOC_OFF) : 	\
	IO_TO_VIRT_BETWEEN((n), IOC_ON) ?	\
		IO_TO_VIRT_XLATE((n), IOC_ON) : 	\
	IO_TO_VIRT_BETWEEN((n), MEDIA_SC) ?	\
		IO_TO_VIRT_XLATE((n), MEDIA_SC) : 	\
	IO_TO_VIRT_BETWEEN((n), ACPU_SC) ?	\
		IO_TO_VIRT_XLATE((n), ACPU_SC) : 	\	
	IPC_SHARE_MEM_TO_VIRT_BETWEEN((n))? \
	    IPC_SHARE_MEM_TO_VIRT_XLATE((n)): \
	    0)


#define IO_TO_VIRT(n) IO_TO_VIRT_PRE(n)



#ifndef __ASSEMBLER__

#define __arch_ioremap(p, s, t)	k3v2_ioremap(p, s, t)
#define __arch_iounmap(v)	       k3v2_iounmap(v)

void __iomem *k3v2_ioremap(unsigned long phys, size_t size, unsigned int type);
void k3v2_iounmap(void __iomem *addr);
#endif/*__ASSEMBLER__*/

#endif/*__MACH_K3V2_IO_H*/
