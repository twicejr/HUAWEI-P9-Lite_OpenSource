/*
 * drivers/power/huawei_charger/charging_core.c
 *
 *huawei charging core driver
 *
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/raid/pq.h>
#include <linux/power/hisi/coul/hisi_coul_drv.h>
#include <charging_core.h>

#define HWLOG_TAG charging_core
HWLOG_REGIST();

struct charge_core_info *g_core_info = NULL;
/**********************************************************
*  Function:       charge_core_tbatt_handler
*  Discription:    update the charge parameters in different battery temperature
*  Parameters:   temp:battery NTC temperature
*                      temp_data[]:the table for describe the temperature property
*                      data:charge parameters
*  return value:  NULL
**********************************************************/
static void charge_core_tbatt_handler(int temp, struct charge_temp_data temp_data[], struct charge_core_data *data)
{
    int i;
    static int last_i = 0;
    static int last_iin = 0;
    static int last_ichg = 0;
    static int last_vterm = 0;
    static int last_temp = 0;
    static int flag_running_first = 1;

    for(i = 0;i < TEMP_PARA_LEVEL;i++)
    {
        if((temp >= temp_data[i].temp_min)&&(temp < temp_data[i].temp_max))
        {
            if((last_temp - temp <= 0)||(temp_data[i].temp_max - temp > temp_data[i].temp_back)
                ||(abs(last_i - i) > 1)||(flag_running_first == 1))
            {
                data->iin = temp_data[i].iin_temp;
                data->ichg = temp_data[i].ichg_temp;
                data->vterm = temp_data[i].vterm_temp;
            }
            else
            {
                data->iin = last_iin;
                data->ichg = last_ichg;
                data->vterm = last_vterm;
            }
            break;
        }
    }
    last_i = i;
    flag_running_first = 0;
    last_temp = temp;
    last_iin = data->iin;
    last_ichg = data->ichg;
    last_vterm = data->vterm;
}
/**********************************************************
*  Function:       charge_core_vbatt_handler
*  Discription:    update the charge parameters in different battery voltage
*  Parameters:   vbat:battery voltage
*                      volt_data[]:the table for describe the voltage property 
*                      data:charge parameters 
*  return value:  NULL
**********************************************************/
static void charge_core_vbatt_handler(int vbat, struct charge_volt_data volt_data[], struct charge_core_data *data)
{
    int i;
    static int last_i = 0;
    static int last_iin = 0;
    static int last_ichg = 0;
    static int last_vbat = 0;
    static int flag_running_first = 1;

    for(i = 0;i < VOLT_PARA_LEVEL;i++)
    {
        if((vbat >= volt_data[i].vbat_min)&&(vbat < volt_data[i].vbat_max))
        {
            if((last_vbat - vbat <= 0)||(volt_data[i].vbat_max - vbat > volt_data[i].volt_back)
                ||(abs(last_i - i) > 1)||(flag_running_first == 1))
            {
                data->iin = data->iin < volt_data[i].iin_volt ? data->iin : volt_data[i].iin_volt;
                data->ichg = data->ichg < volt_data[i].ichg_volt ? data->ichg : volt_data[i].ichg_volt;
            }
            else
            {
                data->iin =  data->iin < last_iin ?  data->iin : last_iin;
                data->ichg =  data->ichg < last_ichg ?  data->ichg : last_ichg;
            }
            break;
        }
    }
    last_i = i;
    flag_running_first = 0;
    last_vbat = vbat;
    last_iin = data->iin;
    last_ichg = data->ichg;
}

/**********************************************************
*  Function:       charge_core_cbatt_handler
*  Discription:    update the charge dpm in different battery capaciy
*  Parameters:   cbat:battery capacity
*                      vdpm_data[]:the table for describe the dpm property
*                      data:charge parameters
*  return value:  NULL
**********************************************************/
static void charge_core_cbatt_handler(int cbat, struct charge_vdpm_data vdpm_data[], struct charge_core_data *data)
{
    int i;
    static int last_i = 0;
    static int last_vdpm = 0;
    static int last_cbat = 0;
    static int flag_running_first = 1;

    for (i = 0; i < VDPM_PARA_LEVEL; i++)
    {
        if ((cbat >= vdpm_data[i].cap_min) && (cbat < vdpm_data[i].cap_max))
        {
            if ((last_cbat - cbat <= 0) || (vdpm_data[i].cap_max - cbat > vdpm_data[i].cap_back)
               || (abs(last_i - i) > 1) || (flag_running_first == 1))
            {
                data->vdpm = vdpm_data[i].vin_dpm;
            }
            else
            {
                data->vdpm = last_vdpm;
            }
            break;
        }
    }

    last_i = i;
    flag_running_first = 0;
    last_cbat = cbat;
    last_vdpm = data->vdpm;

    hwlog_debug("battery capacity is %%%d, vindpm set to %d mV\n", cbat, data->vdpm);
}
/**********************************************************
*  Function:       charge_core_sbatt_by_vbat_ichg_handler
*  Discription:    update the charge parameters in different segment charging
*  Parameters:   vbat:battery voltage
*                      segment_data[]:the table for describe the segment property
*                      data:charge parameters
*  return value:  NULL
**********************************************************/
static void charge_core_sbatt_by_vbat_ichg_handler(int vbat, struct charge_segment_data segment_data[], struct charge_core_data *data)
{
    int i,ichg;
    static int last_i = 0;
    static int last_vterm = 0;
    static int last_ichg = 0;
    static int last_vbat = 0;
    static int flag_running_first = 1;

    ichg =  -hisi_battery_current();

    /* choose index of segment_data */
    for (i = 0; i < data->segment_level; i++)
    {
        if ((vbat >= segment_data[i].vbat_min) && (vbat < segment_data[i].vbat_max) && ichg < segment_data[i].ichg_segment)
        {
            if ((last_i - i <= 0) || (segment_data[i].vbat_max - vbat > segment_data[i].volt_back)
               || (abs(last_i - i) > 1) || (flag_running_first == 1))
            {
                /*do nothing,just get index "i" */
            }
            else
            {
                i = i+1;
            }
            break;
        }
    }

    /* if cannot choose right index ,keep last index  */
    if(i == data->segment_level)
    {
        i=last_i;
    }

    /* set ichg and vterm according to index  only when two consecutive index is the same ,or keep last ichg and vterm */
    if(last_i == i || flag_running_first == 1)
    {
        data->ichg = data->ichg < segment_data[i].ichg_segment ? data->ichg : segment_data[i].ichg_segment;
        data->vterm = data->vterm < segment_data[i].vterm_segment ? data->vterm : segment_data[i].vterm_segment;
    }
    else
    {
        data->ichg = data->ichg < last_ichg ? data->ichg :last_ichg;
        data->vterm = data->vterm < last_vterm ? data->vterm : last_vterm;
    }
    hwlog_info("%s :ichg = %d,vbat =%d , last_i =%d, i =%d,segment_data[i].ichg_segment =%d ,data->ichg =%d ,last_ichg = %d \n",
        __func__,ichg,vbat,last_i,i,segment_data[i].ichg_segment,data->ichg,last_ichg);

    last_i = i;
    flag_running_first = 0;
    last_vbat = vbat;
    last_ichg = data->ichg;
    last_vterm = data->vterm;

}
/**********************************************************
*  Function:       charge_core_sbatt_by_vbat_handler
*  Discription:    update the charge parameters in different segment charging
*  Parameters:   vbat:battery voltage
*                      segment_data[]:the table for describe the segment property
*                      data:charge parameters
*  return value:  NULL
**********************************************************/
static void charge_core_sbatt_by_vbat_handler(int vbat, struct charge_segment_data segment_data[], struct charge_core_data *data)
{
    int i;
    for(i = 0; i < data->segment_level; i++)
    {
        if ((vbat >= segment_data[i].vbat_min) && (vbat < segment_data[i].vbat_max))
        {
            break;
        }
    }
    if(i == data->segment_level)
        i -= 1;

    data->ichg = data->ichg < segment_data[i].ichg_segment ? data->ichg : segment_data[i].ichg_segment;
    data->vterm = data->vterm < segment_data[i].vterm_segment ? data->vterm : segment_data[i].vterm_segment;
}
/**********************************************************
*  Function:       charge_core_sbatt_handler
*  Discription:    update the charge parameters in different segment charging
*  Parameters:   vbat:battery voltage
*                      segment_data[]:the table for describe the segment property
*                      data:charge parameters
*  return value:  NULL
**********************************************************/

static void charge_core_sbatt_handler(int vbat, struct charge_segment_data segment_data[], struct charge_core_data *data)
{
    /*not fcp do not use segment charging strategy */
    if(FCP_STAGE_SUCESS != fcp_get_stage_status())
    {
        return ;
    }

    switch (data->segment_type) {
    case SEGMENT_TYPE_BY_VBAT_ICHG:
        hwlog_debug("case = SEGMENT_TYPE_BY_VBAT_ICHG. \n");
        charge_core_sbatt_by_vbat_ichg_handler(vbat, segment_data, data);
        break;
    case SEGMENT_TYPE_BY_VBAT:
        hwlog_debug("case = SEGMENT_TYPE_BY_VBAT. \n");
        charge_core_sbatt_by_vbat_handler(vbat, segment_data, data);
        break;
    default:
        break;
    }
}
/**********************************************************
*  Function:       charge_core_protect_inductance_handler
*  Discription:    update the charge parameters in different capacity to protect inductance
*  Parameters:   cbat:battery capacity
*                      inductance_data[]:the table for describe the inductance property
*                      data:charge parameters
*  return value:  NULL
**********************************************************/
static void charge_core_protect_inductance_handler(int cbat, struct charge_inductance_data inductance_data[], struct charge_core_data *data)
{

    int i;
    static int last_i = 0;
    static int last_iin = 0;
    static int last_cbat = 0;
    static int flag_running_first = 1;
     /*not fcp do not use segment charging strategy */
    if(FCP_STAGE_SUCESS != fcp_get_stage_status())
    {
           return ;
    }

    for (i = 0; i < INDUCTANCE_PARA_LEVEL; i++)
    {
        if ((cbat >= inductance_data[i].cap_min) && (cbat < inductance_data[i].cap_max))
        {
            if ((last_i - i <= 0) || (inductance_data[i].cap_max - cbat > inductance_data[i].cap_back)
               || (abs(last_i - i) > 1) || (flag_running_first == 1))
            {
                data->iin = data->iin < inductance_data[i].iin_inductance ? data->iin : inductance_data[i].iin_inductance;
            }
            else
            {
                data->iin = data->iin < last_iin ? data->iin : last_iin;
            }
            break;
        }
    }

    last_i = i;
    flag_running_first = 0;
    last_cbat = cbat;
    last_iin = data->iin;

    hwlog_info("%s : battery capacity is %%%d, last_iin set to %d ma,i = %d \n",__func__, cbat, data->iin,i);
}



/**********************************************************
*  Function:       charge_core_get_params
*  Discription:    update update the charge parameters
*  Parameters:   NULL
*  return value:  charge parameters
**********************************************************/
struct charge_core_data *charge_core_get_params(void)
{
    struct charge_core_info *di = g_core_info;
    int tbatt = hisi_battery_temperature();
    int vbatt = hisi_battery_voltage();
    int cbatt = hisi_battery_capacity();

    charge_core_tbatt_handler(tbatt,di->temp_para,&di->data);
    charge_core_vbatt_handler(vbatt,di->volt_para,&di->data);
    charge_core_cbatt_handler(cbatt,di->vdpm_para,&di->data);
    charge_core_sbatt_handler(vbatt,di->segment_para,&di->data);
    charge_core_protect_inductance_handler(cbatt,di->inductance_para,&di->data);

    return &di->data;
}
/**********************************************************
*  Function:       charge_core_battery_data
*  Discription:    get the charge raw data from hisi_battery_data module
*  Parameters:   di:charge_core_info
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_core_battery_data(struct charge_core_info *di)
{
    int i;
    struct chrg_para_lut *p_batt_data = NULL;

    p_batt_data = hisi_battery_charge_params();
    if(NULL == p_batt_data)
    {
        hwlog_err("get battery params fail!\n");
        return -EINVAL;
    }

    for(i = 0;i < (p_batt_data->temp_len)/TEMP_PARA_TOTAL;i++)
    {
        di->temp_para[i].temp_min = p_batt_data->temp_data[i][TEMP_PARA_TEMP_MIN];
        di->temp_para[i].temp_max = p_batt_data->temp_data[i][TEMP_PARA_TEMP_MAX];
        di->temp_para[i].iin_temp = p_batt_data->temp_data[i][TEMP_PARA_IIN];
        di->temp_para[i].ichg_temp = p_batt_data->temp_data[i][TEMP_PARA_ICHG];
        di->temp_para[i].vterm_temp = p_batt_data->temp_data[i][TEMP_PARA_VTERM];
        di->temp_para[i].temp_back = p_batt_data->temp_data[i][TEMP_PARA_TEMP_BACK];
        if(di->temp_para[i].iin_temp == -1)
        {
            di->temp_para[i].iin_temp = di->data.iin_max;
        }
        if(di->temp_para[i].ichg_temp == -1)
        {
            di->temp_para[i].ichg_temp = di->data.ichg_max;
        }
        hwlog_debug("temp_min = %d,temp_max = %d,iin_temp = %d,ichg_temp = %d,vterm_temp = %d,temp_back = %d\n",
            di->temp_para[i].temp_min,di->temp_para[i].temp_max,di->temp_para[i].iin_temp,
            di->temp_para[i].ichg_temp,di->temp_para[i].vterm_temp,di->temp_para[i].temp_back);

        if((di->temp_para[i].temp_min < BATTERY_TEMPERATURE_MIN)||(di->temp_para[i].temp_min > BATTERY_TEMPERATURE_MAX)
        ||(di->temp_para[i].temp_max < BATTERY_TEMPERATURE_MIN)||(di->temp_para[i].temp_max > BATTERY_TEMPERATURE_MAX)
        ||(di->temp_para[i].iin_temp < CHARGE_CURRENT_0000_MA)||(di->temp_para[i].iin_temp > CHARGE_CURRENT_4000_MA)
        ||(di->temp_para[i].ichg_temp < CHARGE_CURRENT_0000_MA)||(di->temp_para[i].ichg_temp > CHARGE_CURRENT_4000_MA)
        ||(di->temp_para[i].vterm_temp < BATTERY_VOLTAGE_3200_MV)||(di->temp_para[i].vterm_temp > BATTERY_VOLTAGE_4500_MV)
        ||(di->temp_para[i].temp_back < BATTERY_TEMPERATURE_0_C)||(di->temp_para[i].temp_back > BATTERY_TEMPERATURE_5_C))
        {
            hwlog_err("the temp_para value is out of range!!\n");
            return -EINVAL;
        }
    }
    for(i = 0;i < (p_batt_data->volt_len)/VOLT_PARA_TOTAL;i++)
    {
        di->volt_para[i].vbat_min = p_batt_data->volt_data[i][VOLT_PARA_VOLT_MIN];
        di->volt_para[i].vbat_max = p_batt_data->volt_data[i][VOLT_PARA_VOLT_MAX];
        di->volt_para[i].iin_volt = p_batt_data->volt_data[i][VOLT_PARA_IIN];
        di->volt_para[i].ichg_volt = p_batt_data->volt_data[i][VOLT_PARA_ICHG];
        di->volt_para[i].volt_back = p_batt_data->volt_data[i][VOLT_PARA_VOLT_BACK];
        if(di->volt_para[i].iin_volt == -1)
        {
            di->volt_para[i].iin_volt = di->data.iin_max;
        }
        if(di->volt_para[i].ichg_volt == -1)
        {
            di->volt_para[i].ichg_volt = di->data.ichg_max;
        }
        hwlog_debug("vbat_min = %d,vbat_max = %d,iin_volt = %d,ichg_volt = %d,volt_back = %d\n",
            di->volt_para[i].vbat_min,di->volt_para[i].vbat_max,di->volt_para[i].iin_volt,
            di->volt_para[i].ichg_volt,di->volt_para[i].volt_back);

        if((di->volt_para[i].vbat_min < BATTERY_VOLTAGE_MIN_MV)||(di->volt_para[i].vbat_min > BATTERY_VOLTAGE_MAX_MV)
        ||(di->volt_para[i].vbat_max < BATTERY_VOLTAGE_MIN_MV)||(di->volt_para[i].vbat_max > BATTERY_VOLTAGE_MAX_MV)
        ||(di->volt_para[i].iin_volt < CHARGE_CURRENT_0000_MA)||(di->volt_para[i].iin_volt > CHARGE_CURRENT_4000_MA)
        ||(di->volt_para[i].ichg_volt < CHARGE_CURRENT_0000_MA)||(di->volt_para[i].ichg_volt > CHARGE_CURRENT_4000_MA)
        ||(di->volt_para[i].volt_back < BATTERY_VOLTAGE_0000_MV)||(di->volt_para[i].volt_back > BATTERY_VOLTAGE_0200_MV))
        {
            hwlog_err("the volt_para value is out of range!!\n");
            return -EINVAL;
        }
    }

    /*Initialize segment charging param */

    di->data.segment_level = (p_batt_data->segment_len)/SEGMENT_PARA_TOTAL;
    for(i = 0;i < di->data.segment_level;i++)
    {
        di->segment_para[i].vbat_min = p_batt_data->segment_data[i][SEGMENT_PARA_VOLT_MIN];
        di->segment_para[i].vbat_max = p_batt_data->segment_data[i][SEGMENT_PARA_VOLT_MAX];
        di->segment_para[i].ichg_segment= p_batt_data->segment_data[i][SEGMENT_PARA_ICHG];
        di->segment_para[i].vterm_segment= p_batt_data->segment_data[i][SEGMENT_PARA_VTERM];
        di->segment_para[i].volt_back = p_batt_data->segment_data[i][SEGMENT_PARA_VOLT_BACK];

        hwlog_info("segment param: vbat_min = %d,vbat_max = %d,ichg_segment = %d,vterm_segment = %d,volt_back = %d\n",
            di->segment_para[i].vbat_min,di->segment_para[i].vbat_max,di->segment_para[i].ichg_segment,
            di->segment_para[i].vterm_segment,di->segment_para[i].volt_back);

        if((di->segment_para[i].vbat_min < BATTERY_VOLTAGE_MIN_MV)||(di->segment_para[i].vbat_min > BATTERY_VOLTAGE_MAX_MV)
        ||(di->segment_para[i].vbat_max < BATTERY_VOLTAGE_MIN_MV)||(di->segment_para[i].vbat_max > BATTERY_VOLTAGE_MAX_MV)
        ||(di->segment_para[i].ichg_segment < CHARGE_CURRENT_0000_MA)||(di->segment_para[i].ichg_segment > CHARGE_CURRENT_MAX_MA)
        ||(di->segment_para[i].vterm_segment < BATTERY_VOLTAGE_3200_MV)||(di->segment_para[i].vterm_segment > BATTERY_VOLTAGE_4500_MV)
        ||(di->segment_para[i].volt_back < BATTERY_VOLTAGE_0000_MV)||(di->segment_para[i].volt_back > BATTERY_VOLTAGE_0200_MV))
        {
            hwlog_err("the segment_para value is out of range!!\n");
            return -EINVAL;
        }
    }

    return 0;
}
/**********************************************************
*  Function:       charge_core_parse_dts
*  Discription:    parse the module dts config value
*  Parameters:   np:device_node
*                      di:charge_core_info
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_core_parse_dts(struct device_node* np, struct charge_core_info *di)
{
    int ret = 0;
    int i = 0;
    int array_len = 0;
    int idata = 0;
    const char *chrg_data_string = NULL;

    /*ac charge current*/
    ret = of_property_read_u32(np, "iin_ac", &(di->data.iin_ac));
    if(ret)
    {
        hwlog_err("get iin_ac failed\n");
        return -EINVAL;
    }
    hwlog_debug("iin_ac = %d\n",di->data.iin_ac);
    ret = of_property_read_u32(np, "ichg_ac", &(di->data.ichg_ac));
    if(ret)
    {
        hwlog_err("get ichg_ac failed\n");
        return -EINVAL;
    }
    hwlog_debug("ichg_ac = %d\n",di->data.ichg_ac);

    /*fcp charge current */
    ret = of_property_read_u32(np,"iin_fcp",&(di->data.iin_fcp));
    if(ret)
    {
        hwlog_info("get iin_fcp failed ,use iin_ac's value instead \n");
        di->data.iin_fcp = di->data.iin_ac;
    }
    hwlog_debug("iin_fcp = %d\n",di->data.iin_fcp);
    ret = of_property_read_u32(np,"ichg_fcp",&(di->data.ichg_fcp));
    if(ret)
    {
        hwlog_info("get ichg_fcp failed ,use ichg_ac's value instead \n");
        di->data.ichg_fcp = di->data.ichg_ac;
    }
    hwlog_debug("ichg_fcp = %d\n",di->data.ichg_fcp);

    /*usb charge current*/
    ret = of_property_read_u32(np, "iin_usb", &(di->data.iin_usb));
    if(ret)
    {
        hwlog_err("get iin_usb failed\n");
        return -EINVAL;
    }
    hwlog_debug("iin_usb = %d\n",di->data.iin_usb);
    ret = of_property_read_u32(np, "ichg_usb", &(di->data.ichg_usb));
    if(ret)
    {
        hwlog_err("get ichg_usb failed\n");
        return -EINVAL;
    }
    hwlog_debug("ichg_usb = %d\n",di->data.ichg_usb);
    /*nonstandard charge current*/
    ret = of_property_read_u32(np, "iin_nonstd", &(di->data.iin_nonstd));
    if(ret)
    {
        hwlog_err("get iin_nonstd failed\n");
        return -EINVAL;
    }
    hwlog_debug("iin_nonstd = %d\n",di->data.iin_nonstd);
    ret = of_property_read_u32(np, "ichg_nonstd", &(di->data.ichg_nonstd));
    if(ret)
    {
        hwlog_err("get ichg_nonstd failed\n");
        return -EINVAL;
    }
    hwlog_debug("ichg_nonstd = %d\n",di->data.ichg_nonstd);
    /*Charging Downstream Port*/
    ret = of_property_read_u32(np, "iin_bc_usb", &(di->data.iin_bc_usb));
    if(ret)
    {
        hwlog_err("get iin_bc_usb failed\n");
        return -EINVAL;
    }
    hwlog_debug("iin_bc_usb = %d\n",di->data.iin_bc_usb);
    ret = of_property_read_u32(np, "ichg_bc_usb", &(di->data.ichg_bc_usb));
    if(ret)
    {
        hwlog_err("get ichg_bc_usb failed\n");
        return -EINVAL;
    }
    hwlog_debug("ichg_bc_usb = %d\n",di->data.ichg_bc_usb);
    /*terminal current*/
    ret = of_property_read_u32(np, "iterm", &(di->data.iterm));
    if(ret)
    {
        hwlog_err("get iterm failed\n");
        return -EINVAL;
    }
    hwlog_debug("iterm = %d\n",di->data.iterm);
    /*otg current*/
    ret = of_property_read_u32(np, "otg_curr", &(di->data.otg_curr));
    if(ret)
    {
        hwlog_err("get otg_curr failed\n");
        return -EINVAL;
    }
    hwlog_debug("otg_curr = %d\n",di->data.otg_curr);
    /*segment para type*/
    ret = of_property_read_u32(np, "segment_type", &(di->data.segment_type));
    if(ret)
    {
        hwlog_err("get segment_type failed\n");
        return -EINVAL;
    }
    /*TypeC High mode current*/
    ret = of_property_read_u32(np, "typec_support", &(di->data.typec_support));
    if(ret)
    {
        hwlog_err("get typec support flag!\n");
        return -EINVAL;
    }
    hwlog_info("typec support flag = %d\n",di->data.typec_support);

    ret = of_property_read_u32(np, "iin_typech", &(di->data.iin_typech));
    if(ret)
    {
        hwlog_err("get typec high mode ibus curr failed\n");
        return -EINVAL;
    }
    hwlog_info("typec high mode ibus curr = %d\n",di->data.iin_typech);
    ret = of_property_read_u32(np, "ichg_typech", &(di->data.ichg_typech));
    if(ret)
    {
        hwlog_err("get typec high mode ibat curr failed\n");
        return -EINVAL;
    }
    hwlog_info("typec high mode ibat curr = %d\n",di->data.ichg_typech);
    //vdpm_para
    array_len = of_property_count_strings(np, "vdpm_para");
    if ((array_len <= 0) || (array_len % VDPM_PARA_TOTAL != 0))
    {
        hwlog_err("vdpm_para is invaild,please check vdpm_para number!!\n");
        return -EINVAL;
    }

    if (array_len > VDPM_PARA_LEVEL * VDPM_PARA_TOTAL)
    {
        array_len = VDPM_PARA_LEVEL * VDPM_PARA_TOTAL;
        hwlog_err("vdpm_para is too long,use only front %d paras!!\n", array_len);
        return -EINVAL;
    }

    memset(di->vdpm_para, 0, VDPM_PARA_LEVEL * sizeof(struct charge_vdpm_data)); // data reset to 0

    for (i = 0; i < array_len; i++)
    {
        ret = of_property_read_string_index(np, "vdpm_para", i, &chrg_data_string);
        if (ret)
        {
            hwlog_err("get vdpm_para failed\n");
            return -EINVAL;
        }

        idata = simple_strtol(chrg_data_string, NULL, 10);
        switch (i % VDPM_PARA_TOTAL)
        {
            case VDPM_PARA_CAP_MIN:
                if ((idata < VDPM_CBAT_MIN) || (idata > VDPM_CBAT_MAX))
                {
                    hwlog_err("the vdpm_para cap_min is out of range!!\n");
                    return -EINVAL;
                }
                di->vdpm_para[ i/ (VDPM_PARA_TOTAL)].cap_min = idata;
                break;
            case VDPM_PARA_CAP_MAX:
                if((idata < VDPM_CBAT_MIN) || (idata > VDPM_CBAT_MAX))
                {
                    hwlog_err("the vdpm_para cap_max is out of range!!\n");
                    return -EINVAL;
                }
                di->vdpm_para[i / (VDPM_PARA_TOTAL)].cap_max = idata;
                break;
            case VDPM_PARA_DPM:
                if((idata < VDPM_VOLT_MIN) || (idata > VDPM_VOLT_MAX))
                {
                    hwlog_err("the vdpm_para vin_dpm is out of range!!\n");
                    return -EINVAL;
                }
                di->vdpm_para[i / (VDPM_PARA_TOTAL)].vin_dpm = idata;
                break;
            case VDPM_PARA_CAP_BACK:
                if((idata < 0) || (idata > VDPM_CAP_DETA))
                {
                    hwlog_err("the vdpm_para cap_back is out of range!!\n");
                    return -EINVAL;
                }
                di->vdpm_para[i / (VDPM_PARA_TOTAL)].cap_back = idata;
                break;
            default:
                hwlog_err("get vdpm_para failed\n");
        }
        hwlog_debug("di->vdpm_para[%d][%d] = %d\n", i / (VDPM_PARA_TOTAL),
                   i % (VDPM_PARA_TOTAL), idata);
    }

    /* inductance_para */
    memset(di->inductance_para, 0, INDUCTANCE_PARA_LEVEL * sizeof(struct charge_inductance_data)); // data reset to 0

    array_len = of_property_count_strings(np, "inductance_para");
    if ((array_len <= 0) || (array_len % INDUCTANCE_PARA_TOTAL != 0))
    {
        hwlog_err("inductance_para is invaild,please check inductance_para number!!\n");
        return -EINVAL;
    }
    if (array_len > INDUCTANCE_PARA_LEVEL * INDUCTANCE_PARA_TOTAL)
    {
        array_len = INDUCTANCE_PARA_LEVEL * INDUCTANCE_PARA_TOTAL;
        hwlog_err("inductance_para is too long,use only front %d paras!!\n", array_len);
        return -EINVAL;
    }

    for(i = 0; i < array_len ; i++)
    {
        ret = of_property_read_string_index(np, "inductance_para", i, &chrg_data_string);
        if (ret)
         {
             hwlog_err("get inductance_para failed\n");
             return -EINVAL;
         }

        idata = simple_strtol(chrg_data_string, NULL, 10);
        switch (i % INDUCTANCE_PARA_TOTAL)
        {
            case INDUCTANCE_PARA_CAP_MIN:
                if ((idata < INDUCTANCE_CBAT_MIN) || (idata > INDUCTANCE_CBAT_MAX))
                {
                    hwlog_err("the inductance_para cap_min is out of range!!\n");
                    return -EINVAL;
                }
                di->inductance_para[ i/ (INDUCTANCE_PARA_TOTAL)].cap_min = idata;
                break;
            case INDUCTANCE_PARA_CAP_MAX:
                if ((idata < INDUCTANCE_CBAT_MIN) || (idata > INDUCTANCE_CBAT_MAX))
                {
                    hwlog_err("the inductance_para cap_max is out of range!!\n");
                    return -EINVAL;
                }
                di->inductance_para[i / (INDUCTANCE_PARA_TOTAL)].cap_max = idata;
                break;
            case INDUCTANCE_PARA_IIN:
                if ((idata < INDUCTANCE_IIN_MIN) || (idata > INDUCTANCE_IIN_MAX))
                {
                    hwlog_err("the inductance_para iin is out of range!!\n");
                    return -EINVAL;
                }
                di->inductance_para[i / (INDUCTANCE_PARA_TOTAL)].iin_inductance= idata;
                break;
            case INDUCTANCE_PARA_CAP_BACK:
                if ((idata < 0) || (idata > INDUCTANCE_CAP_DETA))
                {
                    hwlog_err("the inductance_para cap_back is out of range!!\n");
                    return -EINVAL;
                }
                di->inductance_para[i / (INDUCTANCE_PARA_TOTAL)].cap_back = idata;
                break;
            default:
                hwlog_err("get vdpm_para failed\n");
        }
        hwlog_info("di->inductance_para[%d][%d] = %d\n", i / (INDUCTANCE_PARA_TOTAL),
           i % (INDUCTANCE_PARA_TOTAL), idata);
    }

    if(strstr(saved_command_line, "androidboot.swtype=factory") && (!is_hisi_battery_exist()))
    {
        di->data.iin_ac = CHARGE_CURRENT_2000_MA;
        di->data.ichg_ac = CHARGE_CURRENT_1900_MA;
        di->data.iin_bc_usb = CHARGE_CURRENT_2000_MA;
        di->data.ichg_bc_usb = CHARGE_CURRENT_1900_MA;
        hwlog_info("factory version,iin_ac = %d mA,ichg_ac %d mA,iin_bc_usb = %d mA,ichg_bc_usb = %d mA\n",
            di->data.iin_ac,di->data.ichg_ac,di->data.iin_bc_usb,di->data.ichg_bc_usb);
    }
    di->data.iin_max = di->data.iin_ac < di->data.iin_fcp ? di->data.iin_fcp :di->data.iin_ac;
    di->data.ichg_max = di->data.ichg_ac < di->data.ichg_fcp ? di->data.ichg_fcp :di->data.ichg_ac;
    hwlog_info("iin_max = %d mA,ichg_max %d mA\n",di->data.iin_max,di->data.ichg_max);
    return 0;
}
/**********************************************************
*  Function:       charge_core_probe
*  Discription:    charge module probe
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_core_probe(struct platform_device *pdev)
{
    struct charge_core_info *di;
    int ret = 0;
    struct device_node *np = NULL;

    di = kzalloc(sizeof(*di), GFP_KERNEL);
    if (NULL == di)
    {
        hwlog_err("charge_core_info is NULL!\n");
        return -ENOMEM;
    }

    g_core_info = di;
    di->dev = &pdev->dev;
    np = di->dev->of_node;
    platform_set_drvdata(pdev, di);

    ret = charge_core_parse_dts(np,di);
    if(ret < 0)
    {
        hwlog_err("get charge_data from dts fail!\n");
        goto err_batt;
    }

    ret = charge_core_battery_data(di);
    if(ret < 0)
    {
        hwlog_err("get battery charge data fail!\n");
        goto err_batt;
    }

    hwlog_info("charging core probe ok!\n");
    return 0;
err_batt:
    platform_set_drvdata(pdev, NULL);
    kfree(di);
    di = NULL;
    g_core_info = NULL;
    return ret;
}
/**********************************************************
*  Function:       charge_core_remove
*  Discription:    charge module remove
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_core_remove(struct platform_device *pdev)
{
    struct charge_core_info *di = platform_get_drvdata(pdev);

    if (di == NULL) {
        hwlog_err("[%s]di is NULL!\n",__func__);
        return -ENODEV;
    }

    platform_set_drvdata(pdev, NULL);
    kfree(di);
    di = NULL;
    g_core_info = NULL;

    return 0;
}

static struct of_device_id charge_core_match_table[] =
{
    {
        .compatible = "huawei,charging_core",
        .data = NULL,
    },
    {
    },
};
static struct platform_driver charge_core_driver =
{
    .probe        = charge_core_probe,
    .remove       = charge_core_remove,
    .driver       =
    {
        .name           = "huawei,charging_core",
        .owner          = THIS_MODULE,
        .of_match_table = of_match_ptr(charge_core_match_table),
    },
};
/**********************************************************
*  Function:       charge_core_init
*  Discription:    charge module initialization
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
int __init charge_core_init(void)
{
    return (platform_driver_register(&charge_core_driver));
}
/**********************************************************
*  Function:       charge_core_exit
*  Discription:    charge module exit
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
void __exit charge_core_exit(void)
{
    platform_driver_unregister(&charge_core_driver);
}
module_init(charge_core_init);
module_exit(charge_core_exit);
MODULE_AUTHOR("HUAWEI");
MODULE_DESCRIPTION("charging core module driver");
MODULE_LICENSE("GPL");

