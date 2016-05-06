#ifndef __HKADC_BALONG_H__
#define __HKADC_BALONG_H__

#include <hi_hkadc.h>

#define TIME_500US          (500)
#define TIME_1MS            (1000)
#define TICK_32K            (32*1000)
#define HKADC_SSI_TIMEOUT   (0x10000)
#define HKADC_TIMER_NUM     (2)

/* use 2 args to ensure the security of the args */
struct bsp_hkadc_timer_args
{
    u32 icc_channel_id;
    enum HKADC_CHANNEL_ID hkadc_channel_id;
};

#endif /* __HKADC_BALONG_H__ */
