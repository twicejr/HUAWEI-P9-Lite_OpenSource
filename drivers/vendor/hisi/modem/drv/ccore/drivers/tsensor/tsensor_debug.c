#ifdef __cplusplus
extern "C"
{
#endif

#include <bsp_tsensor.h>
#include <bsp_shared_ddr.h>
#include "tsensor_balong.h"

extern TSENSOR_INFO g_tsensor_info;
extern pTFUNCPTR g_func_temp_handler;

s32 tsensor_help(void)
{
    tsensor_print_always("tsensor_debug                 - 查看全局变量信息\n");
    tsensor_print_always("tsensor_get_temp_debug        - 获取芯片温度\n");
    tsensor_print_always("tsensor_get_temp_type_debug   - 获取芯片温度类型\n");
    return TSEN_OK;
}

s32 tsensor_debug(void)
{
    tsensor_print_always("temp_threshold_high = %d\n",              g_tsensor_info.temp_threshold.high_temp);
    tsensor_print_always("temp_threshold_low = %d\n",               g_tsensor_info.temp_threshold.low_temp);
    tsensor_print_always("reg_base_addr = 0x%x\n",                  g_tsensor_info.reg_base_addr);
    tsensor_print_always("init_timestamp = 0x%x\n",                 g_tsensor_info.init_timestamp);
    tsensor_print_always("int_en_timestamp = 0x%x\n",               g_tsensor_info.int_en_timestamp);
    tsensor_print_always("icc_send_stamp = 0x%x\n",                 *((u32*)TSENSOR_ICC_SEND_STAMP));
    tsensor_print_always("int_msp_callback_stamp = 0x%x\n",         g_tsensor_info.int_msp_callback_stamp);
    tsensor_print_always("int_msp_callback_count = 0x%x\n",         g_tsensor_info.int_msp_callback_count);
    tsensor_print_always("resume_msp_callback_stamp = 0x%x\n",      g_tsensor_info.resume_msp_callback_stamp);
    tsensor_print_always("resume_msp_callback_count = 0x%x\n",      g_tsensor_info.resume_msp_callback_count);
    tsensor_print_always("timer_msp_callback_stamp = 0x%x\n",       g_tsensor_info.timer_msp_callback_stamp);
    tsensor_print_always("timer_msp_callback_count = 0x%x\n",       g_tsensor_info.timer_msp_callback_count);
    tsensor_print_always("trim_tem = %d\n",                         g_tsensor_info.trim_tem);
    tsensor_print_always("inited = %d\n",                           g_tsensor_info.inited);
    return TSEN_OK;
}

s32 tsensor_get_temp_type_debug(void)
{
    enum temp_type type = bsp_tsensor_temptype_get();

    if(en_temp_high == type)
        tsensor_print_always("type = en_temp_high\n");
    else
        tsensor_print_always("type = en_temp_low\n");
    
    return TSEN_OK;
}

s32 tsensor_get_temp_debug(void)
{
    s32 temp = 0;
    s32 ret = tsensor_temp_get(&temp);
    if(ret)
    {
        tsensor_print_error("bsp_tsensor_temp_get error, ret = 0x%x\n", ret);
        return TSEN_ERR;
    }

    tsensor_print_always("temperature = %d\n", temp);
    return TSEN_OK;
}

void callback(enum temp_type type)
{
    tsensor_print_always("tsensor callback come in, type = %d...\n", type);
    return;
}

s32 tsensor_func_reg_handle_test(void)
{
    pTFUNCPTR handler_local = g_func_temp_handler;
    
    (void)bsp_tsensor_callback_regist(callback);    
    (*g_func_temp_handler)(en_temp_high);

    g_func_temp_handler = handler_local;
    return TSEN_OK;
}

s32 tsensor_func_regist(void)
{
    (void)bsp_tsensor_callback_regist(callback);
    return TSEN_OK;
}

#ifdef __cplusplus
}
#endif
