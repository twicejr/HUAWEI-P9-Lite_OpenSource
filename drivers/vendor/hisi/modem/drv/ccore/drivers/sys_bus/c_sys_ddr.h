#ifndef __C_SYS_DDR_H__
#define __C_SYS_DDR_H__

#include <bsp_sram.h>
#include <c_sys_bus_pressure.h>

#define SRAM_SYS_DDR_ADDR            0x80800000//(SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER)
#define SRAM_SYS_DDR_SIZE            (10*1024)


#define DDR_SIZE	4*1024
/*A9 TEST PARA*/
#define A9_DATA_CACHE_SIZE			(128*1024)
#define AXI_MEM_SIZE_FOR_A9			(1024)
#define DDR_MEM_SIZE_FOR_A9         (1024)
#define DDR_MEM_SIZE_FOR_AP         (1024 * 1024)


typedef struct _sys_mem_str
{
	u32 u32Src;
	u32 u32Dst;
	u32 s32Size;
}bus_mem_str;

void sys_mem_init(struct master* master);

#endif /* __C_SYS_EDMA_H__ */
