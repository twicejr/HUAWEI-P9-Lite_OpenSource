/*************************************************************************
*   版权所有(C) 2014-2016, 深圳华为技术有限公司.
*
*   文 件 名 :  tsensor_balong.c
*
*   作    者 :  l00227192
*
*   描    述 :  tsensor模块驱动
*
*   修改记录 :  2015年11月2日  v1.00  l00227192  创建
*************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

#include <securec.h>
#include <product_config.h>
#include <hi_base.h>
#include <hi_tsensor.h>
#include <hi_crg_ao.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_slice.h>
#include <bsp_efuse.h>
#include <bsp_nvim.h>
#include <bsp_dpm.h>
#include <bsp_icc.h>
#include <bsp_sysctrl.h>
#include <bsp_shared_ddr.h>
#include <bsp_tsensor.h>
#include <bsp_softtimer.h>
#include <bsp_hardtimer.h>
#include "of.h"
#include "tsensor_balong.h"

TSENSOR_INFO g_tsensor_info;
pTFUNCPTR g_func_temp_handler = NULL;
u32 get_delta_slice(void); /* 延时足够,返回0;延时不够,返回还差多少slice */

#ifdef CONFIG_CCORE_PM
void temp_callback_resume(enum temp_type type)
{
    g_tsensor_info.resume_msp_callback_count++;
    g_tsensor_info.resume_msp_callback_stamp = bsp_get_slice_value();
    (*g_func_temp_handler)(type);
}

u32 slice2ms(u32 slice)
{
    u32 time_us = 0;
    time_us = slice * TIMER_32K_US_BOUNDARY;
    return (time_us % 1000 ? (time_us/1000 + 1) : time_us/1000);
}

int tsensor_dpm_resume(struct dpm_device *dev)
{
    enum temp_type type = en_temp_low;
    u32 delta_slice_num = 0, delta_ms = 0;
    
    if(!g_func_temp_handler)
        return TSEN_OK;
    
    /* 延时足够，直接查温度类型，调用钩子函数 */
    delta_slice_num = get_delta_slice();
    if(0 == delta_slice_num){
        type = bsp_tsensor_temptype_get();
        if(en_temp_high == type){
            temp_callback_resume(en_temp_high);
        }else{
            temp_callback_resume(en_temp_low);
        }
        return TSEN_OK;
    }

    /* 延时不够，先上报低温，再起timer查温度 */
    delta_ms = slice2ms(delta_slice_num);
    temp_callback_resume(en_temp_low);
    (void)bsp_softtimer_modify(&g_tsensor_info.softtimer, delta_ms);
    bsp_softtimer_add(&g_tsensor_info.softtimer);
    
    return TSEN_OK;
}

struct dpm_device g_tsensor_dpm_device={
    .device_name = "tsensor_dpm",
    .prepare = NULL,
    .suspend_early = NULL,
    .suspend = NULL,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume = NULL,
    .resume_late = NULL,
    .complete = tsensor_dpm_resume,
};
#endif
    
void temp_callback_int(enum temp_type type)
{
    g_tsensor_info.int_msp_callback_count++;
    g_tsensor_info.int_msp_callback_stamp = bsp_get_slice_value();
    (*g_func_temp_handler)(type);
}

void temp_callback_timer(enum temp_type type)
{
    g_tsensor_info.timer_msp_callback_count++;
    g_tsensor_info.timer_msp_callback_stamp = bsp_get_slice_value();
    (*g_func_temp_handler)(type);
}

/*
 * efuse烧写值(code)与温度(temp)的对应关系
 * bit数为11bits，MSB为符号位（1表示负，0表示正），为0.25℃（每bit），有效数值为[-1023，1023]，温度可烧写范围为[-255.75℃，255.75℃]。
 */
static inline int efuse_code2temperature(int code)
{
    int temp = (code & CODE_DATA_MASK) / 4;
    return (code & CODE_SIGN_MASK) ? -temp : temp;
}

/* 
 * 延时足够,返回0;延时不够,返回还差多少slice 
 */
u32 get_delta_slice(void)
{
    u32 enable_time = readl(TSENSOR_ENABLE_STAMP);
    u32 delta = 0, stamp = bsp_get_slice_value();

    delta = get_timer_slice_delta(enable_time, stamp);
    return (DELAY_SLICE_NEED > delta ? (DELAY_SLICE_NEED - delta) : 0);
}

s32 efuse2reg(s32 data)
{
    s32 tem_tsen = 0;
    tem_tsen = efuse_code2temperature(data);
    return TSEN_TEMP2CODE(tem_tsen);
}

s32 trim_temp_config(void)
{
    TSEN_EFUSE_INFO efuse_val;
    s32 ret = 0, code_tsen = 0, code_base = 0, code_trim = 0;
    u32 sign = 0;

    ret = bsp_efuse_read(&efuse_val.u32, 16, 1);    
    if(ret){
        tsensor_print_error("error: bsp_efuse_read failed, ret = d%\n", ret);
        return ret;
    }

    code_tsen = efuse2reg(efuse_val.bits.data_tsen);
    code_base = efuse2reg(efuse_val.bits.data_base);
    code_trim = code_base - code_tsen;
    if(code_trim < 0){
        sign = 1;
        code_trim = -code_trim;
    }
    writel(((sign << LOCAL_SEN_ERR_SIGN_OFFSET ) | (u32)code_trim) & CALIB_REG_MASK, g_tsensor_info.reg_base_addr + HI_CALIBRATION11_OFFSET);
    TSENSOR_DEBUG(g_tsensor_info.trim_tem, (efuse_code2temperature(efuse_val.bits.data_base) - efuse_code2temperature(efuse_val.bits.data_tsen)));
    return TSEN_OK;
}

void tsensor_ctrl_init(s32 high, s32 low)
{
    u32 reg_base = g_tsensor_info.reg_base_addr;
    u32 cod_high = TSEN_TEMP2CODE(high), cod_low = TSEN_TEMP2CODE(low);
    
    writel(0x3FFFFC00 | cod_high, reg_base + HI_TEMP_TH1_OFFSET);               /* 高温告警门限 */    
    writel(cod_high - cod_low,    reg_base + HI_TEMP_LAG1_OFFSET);              /* 回滞门限 */
    writel(0x60200, reg_base + HI_TEMP_CONFIG1_OFFSET);                         /* 同一通道采样2次，多次采样采用均值，通道选择local，转换时间为2.048ms*/
    writel(0,       reg_base + HI_TEMP_WAIT_BYPASS1_OFFSET);                    /* 开启去使能后等待 */
    writel(0x1F4,   reg_base + HI_TEMP_WAIT_TIME1_OFFSET);                      /* 去使能后等待时间5us */
    writel(0,       reg_base + HI_TEMP_RST_MSK1_OFFSET);                        /* 屏蔽中断temp_rst */
    writel(1,       reg_base + HI_TEMP_INT_MSK1_OFFSET);                        /* 使能中断temp_intmsk */
    writel(0x3,     reg_base + HI_TEMP_DET_EN1_OFFSET);                         /* 不开启校准算法，使能tsensor */
}

/*
 * reg remap
 */
s32 tsensor_reg_remap()
{
    struct device_node *dev = NULL;
    const char* compatible = "hisilicon,tsensor_balong_mdm";
    u32 addr = 0;

    dev = of_find_compatible_node(NULL, NULL, compatible);
    if(!dev){
        tsensor_print_error("error: tsensor get dts node failed\n");
        return TSEN_ERR;
    }

    addr = (u32)of_iomap(dev, 0);
    if (!addr){
        tsensor_print_error("error: tsensor reg remap failed\n");
        return TSEN_ERR;
    }

    TSENSOR_DEBUG(g_tsensor_info.reg_base_addr, addr);
    return TSEN_OK;
}

/* 
 * chip温度获取接口，注意:
 * (1)温度采集时间至少为2.24ms
 */
s32 tsensor_temp_get(s32 *temp)
{
    u32 main_code = 0, time_stamp = 0, delta = 0;
    u32 enable_time = readl(TSENSOR_ENABLE_STAMP);

    if(!temp){
        tsensor_print_error("error: argu is null\n");
        return TSEN_ERR;
    }

    /* 延时不够，返回低温值 */
    time_stamp = bsp_get_slice_value();
    delta = get_timer_slice_delta(enable_time, time_stamp);
    if(DELAY_SLICE_NEED > delta){
        *temp = g_tsensor_info.temp_threshold.low_temp - 1; 
        return TSEN_OK;
    }
        
    /* 获取温度 */
    main_code = readl(g_tsensor_info.reg_base_addr + HI_TEMP1_OFFSET);
    *temp = (s32)TSEN_CODE2TEMP(main_code);

    return TSEN_OK;    
}

s32 tsensor_icc_handler(u32 channel_id , u32 len, void* context)
{
    DRV_TSENSOR_TEMP_THRESHOLD *threshold = &g_tsensor_info.temp_threshold;
    s32 temperature = 0;
    u32 leng = sizeof(u32);
    u32 length = (u32)bsp_icc_read(TSENSOR_ICC_CHAN, (u8 *)&temperature, leng);
    
    if(length != leng){
        tsensor_print_error("error: bsp_icc_read failed, len = %d\n", length);
        return TSEN_ERR;
    }    

    if(!g_func_temp_handler){
        tsensor_print_error("msp callback func not regist\n");  /* [false alarm]:not dead code */
        goto out;
    }
    
    /* 误差处理。温度值T1转换成码字C，再转换成温度T2后，T2可能比T1小，此处对高温门限做处理，防止把高温报成低温 */
    if((temperature < threshold->high_temp) && (temperature > threshold->low_temp)){
        temp_callback_int(en_temp_high);
        goto out;
    }

    if(temperature >= threshold->high_temp)
        temp_callback_int(en_temp_high);
    else
        temp_callback_int(en_temp_low);

out:
    return TSEN_OK;
}

void tsensor_softtimer_callback(void)
{
    s32 temp = 0;

    (void)tsensor_temp_get(&temp);
    if((temp >= g_tsensor_info.temp_threshold.high_temp) && (g_func_temp_handler)){
        temp_callback_timer(en_temp_high);
    }
    return;
}

s32 tsensor_softtimer_create(void)
{
    struct softtimer_list *softtimer = &g_tsensor_info.softtimer ; 
    softtimer->func = (softtimer_func)tsensor_softtimer_callback;
    softtimer->para = 0;                              
    softtimer->timeout = TIMER_TIME_OUT;                    
    softtimer->wake_type = SOFTTIMER_NOWAKE;
    return bsp_softtimer_create(softtimer);
}

/*
 * init
 */
void bsp_tsensor_init(void)
{
    DRV_TSENSOR_TEMP_THRESHOLD temp_threshold;
    s32 ret = 0;

    memset_s((void *)&g_tsensor_info, sizeof(TSENSOR_INFO), 0, sizeof(TSENSOR_INFO));
    memset_s((void *)&temp_threshold, sizeof(DRV_TSENSOR_TEMP_THRESHOLD), 0, sizeof(DRV_TSENSOR_TEMP_THRESHOLD));
    memset_s((void *)TSENSOR_SHM_BASE, SHM_SIZE_TSENSOR_STAMP, 0, SHM_SIZE_TSENSOR_STAMP);
    
    ret = tsensor_reg_remap();
    if(ret){
        tsensor_print_error("error: get dts info failed, ret = %d\n", ret);
        goto error;
    }
    
    ret = trim_temp_config();
    if(ret){
        tsensor_print_error("error: trim_temp_config fail, ret = %d\n", ret);
        goto error;
    }
    
    ret = (s32)bsp_nvm_read(NV_ID_DRV_TSENSOR_TEMP_THRESHOLD, (u8 *)&temp_threshold, sizeof(DRV_TSENSOR_TEMP_THRESHOLD));
    if(ret){
        tsensor_print_error("error: get nv failed, ret = %d, use default %d %d\n", ret, DEFAULT_TEMP_LOW_THRESHODE, DEFAULT_TEMP_HIGH_THRESHODE);
        temp_threshold.low_temp = DEFAULT_TEMP_LOW_THRESHODE;
        temp_threshold.high_temp = DEFAULT_TEMP_HIGH_THRESHODE;
    }

    ret = tsensor_softtimer_create();
    if(ret){
        tsensor_print_error("error: softtimer create failed, ret = %d\n", ret);
        goto error;
    }
    
#ifdef CONFIG_CCORE_PM
    ret = bsp_device_pm_add(&g_tsensor_dpm_device);
    if(ret){
        tsensor_print_error("error: pm register fail, ret = %d\n", ret);
        goto error;
    }
#endif

    ret = bsp_icc_event_register(TSENSOR_ICC_CHAN, tsensor_icc_handler, NULL, NULL, NULL);
    if(ret){
        tsensor_print_error("error: icc register fail, ret = %d\n", ret);
        goto error;
    }

    tsensor_ctrl_init(temp_threshold.high_temp, temp_threshold.low_temp);

    TSENSOR_DEBUG(g_tsensor_info.init_timestamp, bsp_get_slice_value());
    TSENSOR_DEBUG(g_tsensor_info.temp_threshold.low_temp, temp_threshold.low_temp);
    TSENSOR_DEBUG(g_tsensor_info.temp_threshold.high_temp, temp_threshold.high_temp);
    TSENSOR_DEBUG(g_tsensor_info.inited, 1);                             

    tsensor_print_always("tsensor init ok\n");
    return;
    
error:
    tsensor_print_error("error: tsensor init fail\n");
    return;
}

enum temp_type bsp_tsensor_temptype_get(void)
{
    s32 temp = 0;
    (void)tsensor_temp_get(&temp);

    if(temp >= g_tsensor_info.temp_threshold.high_temp)
        return en_temp_high;
    else
        return en_temp_low;
}

int bsp_tsensor_callback_regist(pTFUNCPTR p)
{
    g_func_temp_handler = p;
    return 0;
}

#ifdef __cplusplus
}
#endif
