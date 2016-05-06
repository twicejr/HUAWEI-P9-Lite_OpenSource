#include <osl_common.h>
#include <osl_bio.h>
#include "hi_base.h"
#include "hi_tsensor.h"

#ifdef TSENSOR_NEW
#include <soc_onchiprom.h>
#include <soc_memmap.h>
#else
#include <hi_syssc.h>
#endif

#ifdef TSENSOR_NEW
#define TEMCODE_TO_TEMPERATURE(c) ((c-125)*165/806-40)
#define CODE_DATA_MASK 0x3FF /* bit0~9 is data */
#define CODE_SIGN_MASK 0x400 /* bit11 is signal */
int g_trim_tem = 0;

/*
 * efuse烧写值(code)与温度(temp)的对应关系
 * bit数为11bits，MSB为符号位（1表示负，0表示正），为0.25℃（每bit），有效数值为[-1023，1023]，温度可烧写范围为[-255.75℃，255.75℃]。
 */
int code2temperature(int code)
{
    int temp = 0;

    temp = (code & CODE_DATA_MASK) / 4;

    return (code & CODE_SIGN_MASK) ? -temp : temp;
}
/* ***********************************
* chip温度获取接口，注意:
* (1)温度采集时间至少为1.5ms
* (2)超过1300(即130℃)，请丢弃
*************************************/
int chip_tem_get(void)
{
    unsigned main_tem = 0;

    unsigned main_code = 0;

    main_code = readl(HI_TSENSOR_BASE_ADDR + HI_TEMP1_OFFSET);

    main_tem = TEMCODE_TO_TEMPERATURE(main_code);

    return main_tem + g_trim_tem;
}

int get_trim_temp(void)
{
    tOcrShareData *p_share_data = (tOcrShareData *)M3_TCM_SHARE_DATA_ADDR;
    unsigned int efuse_val = 0;
    int tem_from_tsensor = 0;
    int tem_base = 0;
    int ret = 0;

    ret = p_share_data->efuse_read(16, &efuse_val, 1);    
    if(ret)
    {
        return ret;
    }

    tem_from_tsensor = code2temperature(efuse_val & (CODE_SIGN_MASK | CODE_DATA_MASK));
    tem_base = code2temperature((efuse_val >> 11) & (CODE_SIGN_MASK | CODE_DATA_MASK));
    
    g_trim_tem = tem_base - tem_from_tsensor;
    
    return 0;
}

int tsensor_init(void)
{
    /* 同一通道采样32次，多次采样采用均值，通道选择local，转换时间为0.512ms*/
    writel(0x60400, HI_TSENSOR_BASE_ADDR + HI_TEMP_CONFIG1_OFFSET); 

    /* 开启去使能后等待 */
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_WAIT_BYPASS1_OFFSET); 

    /* 去使能后等待时间5us */
    writel(0x1F4, HI_TSENSOR_BASE_ADDR + HI_TEMP_WAIT_TIME1_OFFSET); 

    /* 屏蔽中断temp_mskint/temp_rst */
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_INT_MSK1_OFFSET);
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_RST_MSK1_OFFSET);

    /* 开启校准算法，使能tsensor */
    writel(0x1, HI_TSENSOR_BASE_ADDR + HI_TEMP_DET_EN1_OFFSET);

    /* 获取修正温度值 */
    return get_trim_temp();
}



#else
#define TEMCODE_TO_TEMPERATURE(c) (((c)*200-60*255)*10/255)

short trim_array[]={0,8,16,23,31,39,47,55,-8,-16,-23,-31,-39,-47,-55,-62};


int tsensor_init(void)
{

    set_hi_temp_config_sample_num(0x2);    /*同一通道采样的次数*/

    set_hi_temp_config_sample_mode(0x2);    /*多次采样采用均值*/

    set_hi_temp_config_test(0x0);           /*Tsensor通道选择local*/

    //set_hi_temp_config_ct_sel(0x01);        /*转换时间为6.144ms*/
    
    set_hi_temp_config_ct_sel(0x0);        /*转换时间为0.768ms*/
    
    set_hi_temp_dis_time_temp_dis_time(0x6);/*切换Tsensor时间间隔*/
    
    set_hi_temp_en_temp_en(0x1);    /*使能*/
    
    
    return 0;
}

/* ***********************************
* chip温度获取接口，注意:
* (1)温度采集时间至少为1.5ms
* (2)超过1300(即130℃)，请丢弃
*************************************/
int chip_tem_get(void)
{
    int main_tem = 0;
    int trim_tem = 0;
    
    int main_code = 0;
    int trim_code = 0;
	    
    main_code = get_hi_temp_temp();
    trim_code = get_hi_sc_stat86_efuse_tsensor_trim() & ((0x1 << 8) - 1);

    main_tem = TEMCODE_TO_TEMPERATURE(main_code);
    trim_tem = trim_array[trim_code & 0xF];
    
    return (main_tem + trim_tem);

}
#endif



