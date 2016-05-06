#include <mdrv_temp_cfg.h>
#include <mdrv_temp_cfg.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_shared_ddr.h>
#include <bsp_memmap.h>
#include <bsp_hkadc.h>
#include <bsp_nvim.h>
#include <bsp_om.h>
#include <bsp_temperature.h>

unsigned int chan_error_num[HKADC_TEMP_BUTT]= {0};

#ifdef CONFIG_TEMPERATURE_PROTECT
int phy_chan_num_get(int logic)
{
    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;
    unsigned char *phy_tbl = p_area->phy_tbl;

    if(logic < 0 || logic >= HKADC_LOGIC_CHAN_MAX || phy_tbl[logic] == (unsigned char)-1)
    {
        return TEMPERATURE_ERROR;
    }

    return phy_tbl[logic];
}

/*
 * 尝试再次获取物理通道
 * 成功 - 返回TEMPERATURE_OK, *phy_chan保存正确的物理通道
 * 失败 - 返回TEMPERATURE_ERROR
 */
s32 try_to_get_phy_chan_again(HKADC_TEMP_PROTECT_E enMode, int *phy_chan, DRV_HKADC_DATA_AREA *p_area)
{
    unsigned int ret = 0;
    int chan = 0;

    if(!p_area || !phy_chan)
    {
        return TEMPERATURE_ERROR;
    }
    
    ++(chan_error_num[enMode]);
    if(chan_error_num[enMode] > ERROR_CHAN_MAX)
    {
        return TEMPERATURE_ERROR;
    }

    if(0 != (ret = bsp_nvm_read(NV_ID_DRV_TEMP_CHAN_MAP, (u8*)(p_area->phy_tbl), sizeof(TEMP_HKADC_PHY_LOGIC_ARRAY))))
    {
        tem_print_error("bsp_nvm_read is error, ret is 0x%x.\n" , ret);
        return TEMPERATURE_ERROR;
    }

    chan = phy_chan_num_get(enMode);
    if(TEMPERATURE_ERROR == chan)
    {
        return TEMPERATURE_ERROR;
    }

    *phy_chan = chan;
    return TEMPERATURE_OK;    
}

/*
 * 从共享内存获取电压和温度。共享内存数据的更新存在延时，默认1秒更新一次
 */
int get_volt_temp_from_shared_ddr(DRV_HKADC_DATA_AREA *p_area, int phy_chan, unsigned short* pusVolt, short* psTemp)
{
    if(!p_area)
    {
        tem_print_error("NULL pointer\n");
        return TEMPERATURE_ERROR;
    }
    
    /*取反校验暂时不判断*/
    if(NULL != pusVolt)
    {
        *pusVolt = p_area->chan_out[phy_chan].volt_l;
    }
    
    if(NULL != psTemp)
    {
        *psTemp = p_area->chan_out[phy_chan].temp_l;
    }

    return TEMPERATURE_OK;    
}

/*
 * 电压转换为温度
 */
int volt2temp(TEM_VOLT_TABLE *table, u32 table_length, u16 voltage, s16 *temperature)
{
    TEM_VOLT_TABLE *table_temp = NULL;

    if ((NULL == table) || (!table_length) || (NULL == temperature))
    {
        tem_print_error("err para,hkadc table NULL\n");
        return TEMPERATURE_ERROR;
    }

    /* handle the extreme value */
    if (voltage >= table->volt)
    {
        *temperature = table->temp;
        return TEMPERATURE_OK;
    }

    table_temp = (TEM_VOLT_TABLE *)(table + table_length - 1);
    if (voltage <= table_temp->volt)
    {
        *temperature = table_temp->temp;
        return TEMPERATURE_OK;
    }

    /* get temperature by voltage */
    while (voltage < table->volt)
    {
        table++;
    }
    
    table_temp = (TEM_VOLT_TABLE *)(table - 1);

    *temperature = (s16)(table_temp->temp + ((((table_temp->volt - voltage) * (table->temp - table_temp->temp)) \
                        + (((table_temp->volt -table->volt) + 1)/2)) / (table_temp->volt -table->volt)));

    return TEMPERATURE_OK;
}

/*
 * 立即获取电压和温度
 */
s32 get_volt_temp_via_icc(DRV_HKADC_DATA_AREA *p_area, int phy_chan, unsigned short* pusVolt, short* psTemp)
{
    s32 ret = 0;
    u16 vol = 0;
    s16 tem = 0;
    
    ret = bsp_hkadc_convert((enum HKADC_CHANNEL_ID)phy_chan, &vol);
    if(ret)
    {
        tem_print_error("bsp_hkadc_convert fail, ret = %d.\n", ret);
        return ret;
    }

    ret = volt2temp(p_area->chan_cfg[phy_chan].temp_table, p_area->chan_cfg[phy_chan].temp_data_len, vol, &tem);
    if(ret)
    {
        tem_print_error("volt2temp fail, ret = %d.\n", ret);
        return TEMPERATURE_ERROR;
    }
    
    if(NULL != pusVolt)
    {
        *pusVolt = vol;
    }
    
    if(NULL != psTemp)
    {
        *psTemp = tem;
    }

    return TEMPERATURE_OK;
}

s32 drv_hkadc_get_temp(HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode)
{
    int phy_chan = -1;
    int ret = 0;

    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;

    if(TEMPERATURE_MAGIC_DATA != p_area->magic_start || (TEMPERATURE_MAGIC_DATA != p_area->magic_end))
    {
        tem_print_error("tem mem is writed by others.\n");
        return TEMPERATURE_ERROR;
    }

    phy_chan = phy_chan_num_get(enMode);
    if(TEMPERATURE_ERROR == phy_chan)
    {
        ret = try_to_get_phy_chan_again(enMode, &phy_chan, p_area);        
        if(TEMPERATURE_ERROR == ret)
        {
            return TEMPERATURE_ERROR;
        }
    }

    if(HKADC_CONV_DELAY == ulMode)
    {
        return get_volt_temp_from_shared_ddr(p_area, phy_chan, pusVolt, psTemp);
    }
    else if(HKADC_CONV_NO_DELAY == ulMode)
    {
        return get_volt_temp_via_icc(p_area, phy_chan, pusVolt, psTemp);
    }
    else
    {
        return TEMPERATURE_ERROR;
    }
}

/*****************************************************************************
* 函 数 名  : mdrv_hkadc_get_phy_temp
* 功能描述  : 获取HKADC物理通道usPhyChannel表征的温度、电压
* 输入参数  : usPhyChannel: hkadc的物理通道
*              ulMode: 转换模式
* 输出参数  : *pusVolt: 存储电压值
*              *pstTemp: 存储温度值
* 返 回 值  : 成功返回0，失败返回非0
* 其它说明  : 无
*****************************************************************************/
BSP_S32 mdrv_hkadc_get_phy_temp(unsigned short usPhyChannel, unsigned short *pusVolt, short *pstTemp, HKADC_CONV_MODE_E ulMode)
{
    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;
    
    if(!pusVolt && !pstTemp)
    {
        tem_print_error("error: null pointer found!\r\n");
        return TEMPERATURE_ERROR;
    }

    if(usPhyChannel >= HKADC_CHAN_MAX)
    {
        tem_print_error("error: too big physic channel %d!\r\n", usPhyChannel);
        return TEMPERATURE_ERROR;
    }
    
    if(TEMPERATURE_MAGIC_DATA != p_area->magic_start || (TEMPERATURE_MAGIC_DATA != p_area->magic_end))
    {
        tem_print_error("error: tem mem is writed by others.\n");
        return TEMPERATURE_ERROR;
    }

    if(NULL != pusVolt)
    {
        *pusVolt = p_area->chan_out[usPhyChannel].volt_l;
    }

    if(NULL != pstTemp)
    {
        *pstTemp = p_area->chan_out[usPhyChannel].temp_l;
    }

    return TEMPERATURE_OK;
}

#else

static int phy_chan_num_get(int logic)
{
    return TEMPERATURE_ERROR;
}

s32 drv_hkadc_get_temp(HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode)
{
    if((HKADC_TEMP_PA0 == enMode || (HKADC_TEMP_PA1 == enMode)) && (NULL != psTemp))
    {
        *psTemp = 260;
        return TEMPERATURE_OK;
    }

    if(HKADC_TEMP_XO0 == enMode)
    {
        if(NULL != psTemp)
        {
            *psTemp = 300;
        }
        if(NULL != pusVolt)
        {
            *pusVolt = 796;
        }
        return TEMPERATURE_OK;
    }
    return TEMPERATURE_OK;
}
BSP_S32 mdrv_hkadc_get_phy_temp(unsigned short usPhyChannel, unsigned short *pusVolt, short *pstTemp, HKADC_CONV_MODE_E ulMode)
{
    return TEMPERATURE_OK;
}

#endif

int mdrv_hkadc_get_pa_value (unsigned short *value)
{
    s32 phy_chan = 0;

    if (!value)
        return -1;

    phy_chan = phy_chan_num_get((int)HKADC_TEMP_PA0);
    if(TEMPERATURE_ERROR == phy_chan)
        return -1;

    return bsp_hkadc_convert((enum HKADC_CHANNEL_ID)phy_chan, value);
}

int mdrv_hkadc_get_bat_value (int *ps32Data)
{
    s32 ret;
    s32 phy_chan = 0;
    u16 value    = 0;

    if (!ps32Data)
        return -1;

    phy_chan = phy_chan_num_get((int)HKADC_TEMP_BAT_ET);
    if(TEMPERATURE_ERROR == phy_chan)
        return -1;

    ret = bsp_hkadc_convert((enum HKADC_CHANNEL_ID)phy_chan, &value);
    *ps32Data = value * 2;

    return ret;
}

int mdrv_hkadc_get_bat_volt (int *pslData)
{
    s32 ret;
    s32 phy_chan = 0;
    u16 value    = 0;

    if (!pslData)
        return -1;

    phy_chan = phy_chan_num_get((int)HKADC_TEMP_BAT_ET);
    if(TEMPERATURE_ERROR == phy_chan)
        return -1;

    ret = bsp_hkadc_convert((enum HKADC_CHANNEL_ID)phy_chan, &value);
    *pslData = value;

    return ret;
}


int mdrv_hkadc_get_temp (HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode)
{
    return drv_hkadc_get_temp(enMode, pusVolt, psTemp,ulMode);
}

