#ifndef __C_SYS_EDMA_H__
#define __C_SYS_EDMA_H__

#include <bsp_sram.h>
#include <bsp_edma.h>
#include <c_sys_bus_pressure.h>

#define edma_ddr_size  (8*1024)
#define EDMA_NONE 0
#define GFP_DMA EDMA_NONE
#define __GFP_WAIT EDMA_NONE

#define SRAM_SYS_EDMA_ADDR            0x80800000//(SRAM_BASE_ADDR + SRAM_OFFSET_GU_MAC_HEADER)
#define SRAM_SYS_EDMA_SIZE            (8*1024)


struct sys_edma {
	enum edma_req_id req;
    channel_isr handler;
    struct edma_cb * edma_cb;
    u32 flag;
    u32 src;
    u32 dst;
    u32 size;
    u32 lli_num;
    u32 channel_id;
    u32 totalsize; /* MB */
    u32 totaltime; /* 32K timestamp */
    u32 start_t;   /* 32K timestamp */
    u32 end_t;     /* 32K timestamp */
};


//void sys_edma_record();


//void sys_edma_start();


//void sys_edma_stop();

void sys_edma_lli_start(struct sys_edma* sys_edma);

void sys_edma_init(struct master* master);

#endif /* __C_SYS_EDMA_H__ */
