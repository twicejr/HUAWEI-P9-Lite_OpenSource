#ifndef _M3_DPM_MODEM_H_
#define _M3_DPM_MODEM_H_

#define RESUME_UNUSED_ADDR   0xFFFFFFFF

typedef struct
{
    u32 base_addr;
	u32 suspend_offset;
	u32 resume_en_offset;
    u32 resume_dis_offset;
    u32 resume_all_offset;
	u32 bitmap;
}T_PM_SYSCTRL_ST;

typedef struct
{
    u32 suspend_dma_start_times;
    u32 suspend_dma_check_times;
    u32 resume_dma_start_times;
    u32 resume_dma_check_times;
}T_DPM_COUNT_ST;

extern s32 modem_suspend(void);
extern void modem_resume(void);
extern void modem_resume_ok(void);

#endif /* end of _M3_DPM_MODEM_H_*/

