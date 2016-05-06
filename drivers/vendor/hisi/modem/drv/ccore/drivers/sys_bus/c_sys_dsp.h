#ifndef __C_SYS_DSP_H__
#define __C_SYS_DSP_H__
#include <bsp_dsp.h>

struct dsp_press{
    u32 DEMEM_addr;
    u32 press_type;
    u32 dtcm_dest_addr;
};

void sys_dsp_init(struct master* master);

#endif

