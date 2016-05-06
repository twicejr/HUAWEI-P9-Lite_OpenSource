/*lint --e{551} --e{537} */

#include <cmsis_os.h>
#include <product_config.h>
#include <osl_common.h>
#include <hi_hkadc.h>
#include <soc_memmap.h>
#include <bsp_pmu.h>
#include <bsp_om.h>
#include <bsp_icc.h>
#include <bsp_hardtimer.h>
#include <bsp_softtimer.h>
#include <bsp_hkadc.h>
#include "hkadc_balong.h"

#ifdef HKADC_USE_2500mV
#define HKADC_REFER_VCC 2500
#else /* use 1.8v */
#define HKADC_REFER_VCC 1800
#endif

/* 0 for acore, 1 for ccore */
static struct bsp_hkadc_timer_args g_hkadc_timer_args[HKADC_TIMER_NUM];
static struct softtimer_list hkadc_timer_id[HKADC_TIMER_NUM];
static u32 g_last_convert_time = 0;
static u32 g_last_power_on_time = 0;

osMutexDef (hkadc_mutex);
osMutexId hkadc_mutex_id = NULL;

void get_time_stamp(void)
{
    g_last_power_on_time = bsp_get_slice_value();
    g_last_convert_time = bsp_get_slice_value();
}

int hkadc_ssi_transfer(u32 value_20, u32 value_24)
{
    u32 result = 0;
    u32 count = HKADC_SSI_TIMEOUT;

    writel(value_20, HI_HKADCSSI_REGBASE_ADDR + 0x20);
    writel(value_24, HI_HKADCSSI_REGBASE_ADDR + 0x24);

    writel(0x03, HI_HKADCSSI_REGBASE_ADDR + 0x08);/*4ÌõssiÖ¸Áî*/
    writel(HKADC_TWO_INSTRUCTION_DELAY, HI_HKADCSSI_REGBASE_ADDR + 0x30);
    writel(0x00, HI_HKADCSSI_REGBASE_ADDR + 0x34);

    writel(0x01, HI_HKADCSSI_REGBASE_ADDR + 0x00);

    do
    {
        result = readl(HI_HKADCSSI_REGBASE_ADDR + 0x00);
        count--;
    }while(result && count);

    if (!count)
    {
        /* time out, clean the flag */
        writel(0x01, HI_HKADCSSI_REGBASE_ADDR + 0x10);
        return -1;
    }
    else
    {
        return 0;
    }
}

s32 hkadc_convert(enum HKADC_CHANNEL_ID channel_id, u16* value)
{
    s32 ret = 0;
    u32 now, interval, time_max;
	u32 result_48 = 0;
	u32 result_4C = 0;
    osStatus mutex_status;

    if ((NULL == value) || (channel_id > HKADC_CHANNEL_MAX))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "hkadc args error\r\n");
        return -1;
    }

    time_max = TICK_32K / TIME_1MS / 2;
    do{
        now = bsp_get_slice_value();
        interval = get_timer_slice_delta(g_last_power_on_time, now);
    }while (interval < time_max); /* 500us */

    time_max = TICK_32K / TIME_1MS * 1;
    do{
        now = bsp_get_slice_value();
        interval = get_timer_slice_delta(g_last_convert_time, now);
    }while (interval < time_max); /* 1ms */

    g_last_convert_time = bsp_get_slice_value();

    mutex_status = osMutexWait(hkadc_mutex_id, 0);
    if (mutex_status != osOK)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "fail to get hkadc mutex\r\n");
        return -1;
    }

    ret = hkadc_ssi_transfer(0x01010000 | (u32)channel_id, 0x84008300);
    if (!ret)
    {
        result_48 = readl(HI_HKADCSSI_REGBASE_ADDR + 0x48);
        result_4C = readl(HI_HKADCSSI_REGBASE_ADDR + 0x4C);
        result_48 = result_48 << 4;
        result_4C = result_4C >> 4;
        *value = (u16)((result_48 | result_4C) * HKADC_REFER_VCC >> 12);        
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "hkadc convert timeout\r\n");
    }

    /* By pass on */
    ret |= hkadc_ssi_transfer(0x00800080, 0x00800080);

    mutex_status = osMutexRelease(hkadc_mutex_id);
    if (mutex_status != osOK)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "fail to release hkadc mutex\r\n");
        return -1;
    }

    return ret;
}

void hkadc_timer_callback(u32 args)
{
    struct bsp_hkadc_timer_args *hkadc_agrs = (struct bsp_hkadc_timer_args *)args;
    s32 ret = 0;
    u32 cpuid = 0;
    u16 voltage = 0;

    ret = bsp_hkadc_convert(hkadc_agrs->hkadc_channel_id, &voltage);
    if (ret) 
    {
        voltage = 0xFFFF;
    }

    cpuid = (hkadc_agrs->icc_channel_id >> 16) == ICC_CHN_MCORE_ACORE ? ICC_CPU_APP : ICC_CPU_MODEM;
    ret = bsp_icc_send(cpuid, hkadc_agrs->icc_channel_id, (u8*)&voltage, sizeof(voltage));    
    if (ret != (int)sizeof(voltage))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "icc send error %x\r\n", ret);
    }
}

int hkadc_icc_callback(u32 icc_channel_id , u32 len, void* context)
{
    s32 ret, timer_index;
    u32 hkadc_channel_id = 0;

    ret = bsp_icc_read(icc_channel_id, (u8*)&hkadc_channel_id, len);
    if (ret != (int)sizeof(hkadc_channel_id))
    {
        return -1;
    }

    timer_index = (icc_channel_id >> 16) == ICC_CHN_MCORE_ACORE ? 0 : 1;
    g_hkadc_timer_args[timer_index].icc_channel_id = icc_channel_id;
    g_hkadc_timer_args[timer_index].hkadc_channel_id = (enum HKADC_CHANNEL_ID)hkadc_channel_id;
    bsp_softtimer_add(&hkadc_timer_id[timer_index]);

    return 0;
}

s32 hkadc_timer_register(void)
{
    s32 i = 0;
    s32 ret = 0;

    for(i = 0; i < HKADC_TIMER_NUM; i++)
    {
        hkadc_timer_id[i].func = hkadc_timer_callback;
        hkadc_timer_id[i].wake_type=SOFTTIMER_WAKE;
        hkadc_timer_id[i].timeout = 0;
        hkadc_timer_id[i].para = (u32)&g_hkadc_timer_args[i];
        ret |= bsp_softtimer_create(&hkadc_timer_id[i] );
    }
    
    return ret;
}

s32 hkadc_icc_register(u32 icc_channel_id)
{
    return bsp_icc_event_register(icc_channel_id, (read_cb_func)hkadc_icc_callback, NULL, NULL, NULL);
}

s32 hkadc_mutex_init(void)
{
    hkadc_mutex_id = osMutexCreate(osMutex(hkadc_mutex));
    if(NULL == hkadc_mutex_id)
    {
        return -1;
    }

    return 0;
}

/* 
 * hkadc interface
 */
void bsp_hkadc_init(void)
{
    int ret = 0;
    
    get_time_stamp();

    ret |= hkadc_mutex_init();
    ret |= hkadc_timer_register();
    ret |= hkadc_icc_register(ICC_CHN_MCORE_ACORE << 16 | MCORE_ACORE_FUNC_HKADC);
    ret |= hkadc_icc_register(ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_HKADC);
    
    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "hkadc init failed, ret = %d\r\n", ret);
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "hkadc init ok\r\n");
    }
}

void bsp_hkadc_resume(void)
{
    g_last_power_on_time = bsp_get_slice_value();

    return;
}

int bsp_hkadc_convert(enum HKADC_CHANNEL_ID channel_id, u16* value)
{
    return hkadc_convert(channel_id, value);
}


/*
 * hkadc debug
 */
int hkadc_convert_debug(int channel)
{
    int ret = 0;
    u16 value = 0;

    ret = bsp_hkadc_convert((enum HKADC_CHANNEL_ID)channel, &value);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "channel %d, volt %dmV\n", channel, value);

    return ret;
}


