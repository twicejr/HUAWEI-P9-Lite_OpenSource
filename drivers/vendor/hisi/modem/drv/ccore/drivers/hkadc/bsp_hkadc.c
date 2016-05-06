/*lint --e{537} */
#include "securec.h"
#include <stdio.h>
#include <string.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_sem.h>
#include <osl_wait.h>
#include <bsp_om.h>
#include <bsp_icc.h>
#include <bsp_hkadc.h>
#include <bsp_hardtimer.h>

static u16 g_hkadc_voltage;
static osl_sem_id g_hkadc_icc_sem_id;
static osl_sem_id g_hkadc_value_sem_id;
HKADC_DEBUG_INFO hkadc_debug_info;

int bsp_hkadc_convert(enum HKADC_CHANNEL_ID channel, u16* value)
{
    int ret;
    u32 hkadc_channel_id = (u32)channel;
    u32 icc_channel_id = ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_HKADC;

    osl_sem_down(&g_hkadc_icc_sem_id);

    ret = bsp_icc_send(ICC_CPU_MCU, icc_channel_id,
        (u8*)&hkadc_channel_id, sizeof(hkadc_channel_id));
    if (ret != (int)sizeof(hkadc_channel_id))
    {
        osl_sem_up(&g_hkadc_icc_sem_id);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "icc send error, error code: 0x%x\r\n", ret);
        return ret;
    }
    hkadc_debug_info.icc_send_stamp = bsp_get_slice_value();

    /*coverity[lock] */
    osl_sem_down(&g_hkadc_value_sem_id);

    if (0xFFFF == g_hkadc_voltage)
    {
        ret = -1;
    }
    else
    {
        ret = 0;
        *value = g_hkadc_voltage;
    }

    osl_sem_up(&g_hkadc_icc_sem_id);

    return ret;
}
/*lint --e{715 } */
static int bsp_hkadc_icc_callback(u32 icc_channel_id , u32 len, void* context)
{
    int ret;
    u16 voltage = 0;

    ret = bsp_icc_read(icc_channel_id, (u8*)&voltage, len);
    if (ret != (int)sizeof(voltage))
    {
        g_hkadc_voltage = 0xFFFF;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "hkadc icc read error, error code: 0x%x\r\n", ret);
    }
    else
    {
        g_hkadc_voltage = voltage;
    }
    hkadc_debug_info.icc_callback_stamp = bsp_get_slice_value();

    osl_sem_up(&g_hkadc_value_sem_id);

    return 0;
}

void bsp_hkadc_init(void)
{
    int ret = 0;
    u32 icc_channel_id = ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_HKADC;

    osl_sem_init(1, &g_hkadc_icc_sem_id);
    osl_sem_init(0, &g_hkadc_value_sem_id);

    (void)memset_s((void*)&hkadc_debug_info, sizeof(hkadc_debug_info), 0, sizeof(hkadc_debug_info));

    ret |= bsp_icc_event_register(icc_channel_id,
        (read_cb_func)bsp_hkadc_icc_callback, NULL, NULL, NULL);
    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HKADC, "hkadc init error, error code: 0x%x\r\n", ret);
    }
}

