#include <mdrv_hkadc_common.h>
#include <mdrv_temp_cfg.h>
#include <hi_hkadc.h>
#include <bsp_om.h>
#include <bsp_hkadc.h>
#include <bsp_shared_ddr.h>
#include <bsp_temperature.h>



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

void tem_volt_null_test(void)
{
    unsigned short volt = 0;
    short temp = 0;

    if(TEMPERATURE_OK != drv_hkadc_get_temp(HKADC_TEMP_TOP,NULL,&temp, HKADC_CONV_DELAY))
    {
        tem_print_error("volt null is fail.\n");
    }
    if(TEMPERATURE_OK != drv_hkadc_get_temp(HKADC_TEMP_TOP,&volt,NULL, HKADC_CONV_DELAY))
    {
        tem_print_error("tem volt null is fail.\n");
    }
}


void tem_volt_get_test(void)
{
    unsigned short volt = 0;
    short temp = 0;

    HKADC_TEMP_PROTECT_E i = HKADC_TEMP_TOP;

    for(i = HKADC_TEMP_TOP; i < HKADC_TEMP_BUTT; i++)
    {
        if(TEMPERATURE_OK == drv_hkadc_get_temp(i, &volt, &temp, HKADC_CONV_DELAY))
        {
            tem_print_info("logic_id = %d, volt = %d, tem = %d.\n", i, volt, temp);
        }

    }
}

/* 温度保护DEBUG函数 */
void tem_phy_logic(void)
{
    int i = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    tem_print_info("-------------TEMPERATURE PHYSICAL LOGFIC TABLE  ------------\n");
    for(i = 0; i < HKADC_LOGIC_CHAN_MAX; i++)
    {
        tem_print_info("logic num = %d ,phy num = %d.\n", i, p_area->phy_tbl[i]);
    }
    tem_print_info("-------------------------------------------------------------\n");

}

void tem_battery_show(void)
{
    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    tem_print_info("-------------BATTERY TEMPERATURE PROTECT CONFIG------------\n");
    tem_print_info("high tem protect:        %s\n", p_area->sys_temp_cfg.enable & 0x1 ? "yes" : "no"); /* bit0：高温保护使能；bit1：低温保护使能 */
    tem_print_info("low tem protect:         %s\n", p_area->sys_temp_cfg.enable & 0x2 ? "yes" : "no");

    tem_print_info("hkadc count is:          %d\n", p_area->sys_temp_cfg.hkadc_id);          /* 高低温保护的hkadc通道ID */
    tem_print_info("high tem gate is:        %d\n", p_area->sys_temp_cfg.high_thres);        /* 高温保护的阀值 */
    tem_print_info("high gate count is:      %d\n", p_area->sys_temp_cfg.high_count);        /* 高温保护次数门限，到达该次数后系统关机 */

    tem_print_info("low tem gate is:         %d\n", p_area->sys_temp_cfg.low_thres);         /* 低温保护的阀值 */
    tem_print_info("low gate count is:       %d\n", p_area->sys_temp_cfg.low_count);         /* 低温保护次数门限，到达该次数后系统关机 */

    tem_print_info("-------------------------------------------------------------\n");

}

void tem_config_show(void)
{
    int i = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    tem_print_info("  channel \t  enable \t period \t table len\n");
    tem_print_info("  ------- \t  ------ \t ------ \t -------\n");
    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        tem_print_info("%6d\t%6d\t       %6d\t       %6d\n", i, p_area->chan_cfg[i].outcfg.out_config, p_area->chan_cfg[i].out_peroid, p_area->chan_cfg[i].temp_data_len);
    }
    tem_print_info("  ------- \t  ------ \t ------ \t -------\n");

    tem_print_info("\n");
}

void tem_table_show(void)
{
    int i = 0;
    int j = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        tem_print_info("channel number is %d\n", i);

        tem_print_info("  volt \t   tem  \n");
        tem_print_info("  ---- \t -------\n");

        for(j = 0;j < p_area->chan_cfg[i].temp_data_len;j++)
        {
            tem_print_info("%6d \t %6d\n", p_area->chan_cfg[i].temp_table[j].volt, p_area->chan_cfg[i].temp_table[j].temp);
        }

        tem_print_info("  ---- \t -------\n");

        tem_print_info("\n");
    }

}



void drv_hkadc_get_temp_debug(HKADC_TEMP_PROTECT_E mode, HKADC_CONV_MODE_E ulMode)
{
    short psTemp = 0;
    unsigned short pusVolt = 0;

    if(TEMPERATURE_OK == drv_hkadc_get_temp(mode, &pusVolt, &psTemp, ulMode))
    {
        tem_print_info("mode = %d volt = %d tem = %d mode = %d.\n", mode, pusVolt, psTemp, ulMode);
    }

}

void tem_output_show(void)
{
    int i = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    tem_print_info(" channel \t   volt  \t   tem  \n");
    tem_print_info(" ------- \t ------- \t -------\n");
    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        tem_print_info("%6d \t %6d \t %6d\n", i, p_area->chan_out[i].volt_l,p_area->chan_out[i].temp_l);
    }
    tem_print_info(" ------- \t ------- \t -------\n");

    tem_print_info("\n");

    tem_print_info(" channel \t reverse volt \t reverse tem\n");
    tem_print_info(" ------- \t ------------ \t -----------\n");
    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        tem_print_info("%6d \t %6d \t %6d \n", i, p_area->chan_out[i].volt_r,p_area->chan_out[i].temp_r);

    }
    tem_print_info(" ------- \t ------------ \t -----------\n");

}

