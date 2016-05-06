#include <cmsis_os.h>
#include <osl_wait.h>
#include <bsp_shared_ddr.h>
#include <osl_common.h>

#include "bsp_om.h"
#include "bsp_icc.h"

#include "bsp_nvim.h"
#include "drv_nv_id.h"
#include "drv_nv_def.h"

#include "bsp_hkadc.h"
#include <bsp_softtimer.h>

#include "mdrv_temp_cfg.h"
#include "bsp_hardtimer.h"
#include "om_balong.h"
#include "drx_interface_cmd_id.h"
#include "bsp_temperature.h"

//#define bsp_trace(log_level, mod_id, fmt,...) printk(fmt, ##__VA_ARGS__)

#define is_valid(old_tem, new_tem) (((old_tem > new_tem) ? (old_tem - new_tem):(new_tem - old_tem)) < TEMPERATURE_MAX_INTERVAL)

/*需要实测，考虑各种场景*/
#define TEMPERATURE_MAX_INTERVAL         5

/*温度调试开关*/
/*#define TEMPERATURE_DEBUG*/

typedef struct
{
    short high;
    short low;
}TEMPERATURE_COUNT;

typedef struct
{
    unsigned short is_first_init;
    unsigned short is_change_timer;

    unsigned short sleep_period;       /*单位为秒*/
    unsigned short tem_update_period;  /*单位为秒*/

    signed short old_tem[MAX_REGION];         /*上一次采集的温度*/
    TEMPERATURE_COUNT gate_count[MAX_REGION]; /*达到温度门限的次数*/
    unsigned short chan_time[HKADC_CHAN_MAX];   /*当前通道已等待时间，相对于每个通道周期而言*/
    DRV_HKADC_DATA_AREA *p_hkadc_area;        /*指向hkadc数据所在内存区域*/

}DRV_TEMPERATURE_PROTECT_DATA;

typedef void (*P_TEMPERATURE_FUN)(void const *args);

__ao_data struct softtimer_list tem_softtimer;

__ao_data DRV_TEMPERATURE_PROTECT_DATA tem_protect_data;

static void tem_update_callback(void);

#ifdef TEMPERATURE_DEBUG

struct hkadc_tem_value tem_table[32] = {{-250,2366},{-200,2316},{-150,2253},{-100,2174},{-50,2078},{0,1967},{50,1840},
{100,1701},{150,1553},{200,1401},{250,1250},{300,1103},{350,965},{400,838},{450,724},{500,622},{550,533},{600,456},
{650,390},{700,333},{750,285},{800,244},{850,209},{900,180},{950,155},{1000,134},{1050,116},{1100,101},{1150,88 },
{1200,77},{1250,68},{1300,61}};

unsigned char phy_tbl[HKADC_LOGIC_CHAN_MAX] ={-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1};

int tem_default_config(void)
{
    unsigned int i = 0;
    unsigned int  ret = 0;
    unsigned int length = 0;

    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;
    DRV_HKADC_DATA_AREA *p_area = p_data->p_hkadc_area;

    p_area->magic_start = TEMPERATURE_MAGIC_DATA;
    p_area->magic_end   = TEMPERATURE_MAGIC_DATA;

    p_data->tem_update_period  = 1;

    p_data->sleep_period = 10;

    p_area->chan_cfg[7].outcfg.out_config = 10;
    p_area->chan_cfg[7].out_peroid = 1;
    p_area->chan_cfg[7].temp_data_len = 32;

    memcpy(p_area->chan_cfg[7].temp_table, tem_table, 32 * (sizeof(struct hkadc_tem_value)));
    memcpy(p_area->phy_tbl, phy_tbl, sizeof(phy_tbl));


}
void k3_hkadc_test(void)
{
    int ret = 0;
    unsigned int i = 0;
    unsigned short voltage = 0;

    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        ret = bsp_hkadc_convert((enum HKADC_CHANNEL_ID)i, &voltage);
        if(0 != ret)
        {
            tem_print_error("adc convert fail,err %d.\n", ret);
            return TEMPERATURE_ERROR;
        }

        tem_print_info("chan %d volt %d", i, voltage);

    }

}

#endif

/*lint -save -e734 -e958*/
static int bsp_hkadc_get_temp_by_volt(u16 voltage, TEM_VOLT_TABLE *table, u32 table_length, s16 *temperature)
{
    TEM_VOLT_TABLE *table_temp;

    if ((NULL == table) || (!table_length) || (NULL == temperature))
    {
        printk("err para,hkadc table NULL\n");
        return -1;
    }

    /* handle the extreme value */
    if (voltage >= table->volt)
    {
        *temperature = table->temp;
        return 0;
    }

    table_temp = (TEM_VOLT_TABLE *)(table + table_length - 1);
    if (voltage <= table_temp->volt)
    {
        *temperature = table_temp->temp;
        return 0;
    }

    /* get temperature by voltage */
    while (voltage < table->volt)
    {
        table++;
    }
    table_temp = (TEM_VOLT_TABLE *)(table -1);

    *temperature = table_temp->temp + ((((table_temp->volt -
                        voltage) * (table->temp - table_temp->temp)) \
                        + (((table_temp->volt -table->volt) + 1)/2))  \
                        /(table_temp->volt -table->volt));

    return 0;
}
/*lint -restore*/

static int bsp_tem_update(unsigned int chan)
{
    int ret = 0;
    unsigned short voltage = 0;
    short tem = 0;

    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;
    DRV_HKADC_DATA_AREA *p_area = p_data->p_hkadc_area;

    if(TEMPERATURE_MAGIC_DATA != p_area->magic_start || (TEMPERATURE_MAGIC_DATA != p_area->magic_end))
    {
        tem_print_error("tem mem is writed by others.\n");
        return TEMPERATURE_ERROR;
    }

    //tem_print_info("hkadc in ,chan%d volt is %d ret %d timer:%d\n", chan, voltage, ret, bsp_get_elapse_ms());
    ret = bsp_hkadc_convert((enum HKADC_CHANNEL_ID)chan, &voltage);
    //tem_print_info("hkadc out ,chan%d volt is %d ret %d timer:%d\n", chan, voltage, ret, bsp_get_elapse_ms());
    if(0 != ret)
    {
        tem_print_error("adc convert fail,err %d.\n", ret);
        return TEMPERATURE_ERROR;
    }

    p_area->chan_out[chan].volt_l = voltage;
    p_area->chan_out[chan].volt_r = ~voltage;

    if(0 == p_area->chan_cfg[chan].outcfg.bit_out_config.out_vol_temp || (0 == p_area->chan_cfg[chan].temp_data_len))
    {
        return TEMPERATURE_OK;
    }

    ret = bsp_hkadc_get_temp_by_volt(voltage, p_area->chan_cfg[chan].temp_table, p_area->chan_cfg[chan].temp_data_len, &tem);
    if(0 != ret)
    {
        tem_print_error(" hkadc_get_temp is fail.\n");
        return TEMPERATURE_ERROR;
    }

    p_area->chan_out[chan].temp_l = tem;
    p_area->chan_out[chan].temp_r = ~tem;/*lint !e502*/

    //tem_print_error("chan%d volt is %d, tem is %d.\n", chan, p_area->chan_out[chan].volt_l, p_area->chan_out[chan].temp_l);

    return TEMPERATURE_OK;

}

static TEMPERATURE_TYPE high_tem_check(DRV_TEMPERATURE_PROTECT_DATA *p_data, TEMPERATURE_REGION region, short tem, short high_gate)
{
    TEMPERATURE_TYPE type = NORMAL_TEMPERATURE;
    int count = 0;

    if(region <= TSENS_END)
    {
    }
    else if (region >= HKADC_START && (region <= HKADC_END))
    {
        count = p_data->p_hkadc_area->sys_temp_cfg.high_count;
    }
    else
    {
        return NORMAL_TEMPERATURE;
    }

    if(is_valid(p_data->old_tem[region], tem) && (tem >= high_gate))
    {
        ++(p_data->gate_count[region].high);
    }
    else
    {
         p_data->gate_count[region].high = 0;
    }

    if(p_data->gate_count[region].high >= count)
    {
        p_data->gate_count[region].high = 0;
        type = HIGH_TEMPERATURE;
    }
    else
    {
        type = NORMAL_TEMPERATURE;
    }

    return type;

}

static TEMPERATURE_TYPE low_tem_check(DRV_TEMPERATURE_PROTECT_DATA *p_data, TEMPERATURE_REGION region, short tem, short low_gate)
{
    TEMPERATURE_TYPE type = NORMAL_TEMPERATURE;
    int count = 0;

    if(region <= TSENS_END)
    {
        /*count = p_data->p_hkadc_area->tens_cfg[region].low_count;*/
    }
    else if (region >= HKADC_START && (region <= HKADC_END))
    {
        count = p_data->p_hkadc_area->sys_temp_cfg.high_count;
    }
    else
    {
        return NORMAL_TEMPERATURE;
    }

    if(is_valid(p_data->old_tem[region], tem) && (tem <= low_gate))
    {
        ++(p_data->gate_count[region].low);
    }
    else
    {
         p_data->gate_count[region].low = 0;
    }

    if(p_data->gate_count[region].low >= count)
    {
        p_data->gate_count[region].low = 0;
        type = LOW_TEMPERATURE;
    }
    else
    {
        type = NORMAL_TEMPERATURE;
    }

    return type;

}


static int device_tem_protect(int *tem_region, int *tem_status)
{
/*lint --e{734}*/
    unsigned int conf = 0;
    unsigned int type = 0;

    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;
    DRV_HKADC_DATA_AREA *p_area = p_data->p_hkadc_area;

    short tem = p_area->chan_out[p_area->sys_temp_cfg.hkadc_id].temp_l;
    /*int tem_r = p_area->chan_out[HKADC_TEM_CHAN].temp_r;*/

    /*判断温度是否有效*/
    /*if(0 != (tem & tem_r))
    {
        tem_print_error(" mem is writed by others.\n");
        return;
    }*/

    *tem_region = MAX_REGION;
    *tem_status = NORMAL_TEMPERATURE;

    /*电池高温保护*/
    conf = p_area->sys_temp_cfg.enable;
    if(0 == (conf & 0x1))
    {
        return 0;
    }
    type = high_tem_check(p_data, HKADC_BATTERY, tem, p_area->sys_temp_cfg.high_thres);
    if(HIGH_TEMPERATURE == type)
    {
        *tem_region = HKADC_BATTERY;
        *tem_status = HIGH_TEMPERATURE;
        return 0;
    }

    /*电池低温保护*/
    if(0 == (conf & (0x1 << 1)))
    {
        return 0;
    }
    type = low_tem_check(p_data, HKADC_BATTERY, tem, p_area->sys_temp_cfg.low_thres);
    if(LOW_TEMPERATURE == type)
    {
        *tem_region = HKADC_BATTERY;
        *tem_status = LOW_TEMPERATURE;
        return 0;
    }

    /*将当前温度信息保存*/
    p_data->old_tem[HKADC_BATTERY] = tem;

    return NORMAL_TEMPERATURE;
}

/*获取温度信息，并更新到共享内存*/
static void tem_update_callback(void)
{
    unsigned int i = 0;

    DIAG_CMD_DRX_BATTERIES_TEMP_STRU batt_stru = {0};

    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;
    DRV_HKADC_DATA_AREA *p_area = p_data->p_hkadc_area;

    if(TEMPERATURE_MAGIC_DATA != p_area->magic_start || (TEMPERATURE_MAGIC_DATA != p_area->magic_end))
    {
        tem_print_error(" mem is writed by others.\n");
        return;
    }

    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        if(0x2 != p_area->chan_cfg[i].outcfg.bit_out_config.out_prop)/*单次输出考虑*/
        {
            continue;
        }

        if(++(p_data->chan_time[i]) != p_area->chan_cfg[i].out_peroid)
        {
            /*时间未到，直接返回*/
            continue;
        }

        if(i == p_area->sys_temp_cfg.hkadc_id)
        {
            batt_stru.tem = p_area->chan_out[i].temp_l;
        }

        if(0 != bsp_tem_update(i))
        {
            tem_print_error(" bsp_tem_update is fail.\n");
        }

        if(i == p_area->sys_temp_cfg.hkadc_id &&
            (batt_stru.tem != p_area->chan_out[i].temp_l))
        {
            batt_stru.tem = p_area->chan_out[i].temp_l;
            bsp_log_bin_ind(DIAG_CMD_DRX_BATTERIES_TEMP_IND, &(batt_stru),sizeof(DIAG_CMD_DRX_BATTERIES_TEMP_STRU));
            //tem_print_info("battery %d\n", batt_stru.tem);
        }

        p_data->chan_time[i] = 0; /*该通道时间重新初始化为0*/
    }

}


/*初始化原始温度，确保前后温度差不超过5℃*/
static int origin_tem_config(void)
{
    unsigned int i = 0;

    DIAG_CMD_DRX_CHIP_TEMP_STRU chip_stru = {0};
    DIAG_CMD_DRX_BATTERIES_TEMP_STRU batt_stru = {0};

    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;
    DRV_HKADC_DATA_AREA *p_area = p_data->p_hkadc_area;

    for(i = 0;i < HKADC_CHAN_MAX;i++)
    {
        if(0 == (p_area->chan_cfg[i].outcfg.out_config & 0x3))
        {
            continue;
        }

        if(0 != bsp_tem_update(i))
        {
            tem_print_error(" bsp_tem_update is fail.\n");
        }

        if( i == p_area->sys_temp_cfg.hkadc_id)
        {
            batt_stru.tem = p_area->chan_out[i].temp_l;
            bsp_log_bin_ind(DIAG_CMD_DRX_BATTERIES_TEMP_IND, &(batt_stru),sizeof(DIAG_CMD_DRX_BATTERIES_TEMP_STRU));
        }
    }

    p_data->old_tem[HKADC_BATTERY] = p_area->chan_out[p_area->sys_temp_cfg.hkadc_id].temp_l;

    bsp_log_bin_ind(DIAG_CMD_DRX_CHIP_TEMP_IND, &chip_stru,sizeof(DIAG_CMD_DRX_CHIP_TEMP_STRU));

    return TEMPERATURE_OK;
}

void tem_timer_callback(void)
{
    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;
    DRV_HKADC_DATA_AREA *p_area = p_data->p_hkadc_area;
    int len = 0;
    int tem_region = MAX_REGION;
    int tem_status = NORMAL_TEMPERATURE;
	unsigned int chan_id = ICC_CHN_MCORE_ACORE << 16 | MCORE_ACORE_FUNC_TEMPERATURE;
	struct tem_msg_stru msg = {0, 0, 0};

    if(TEMPERATURE_MAGIC_DATA != p_area->magic_start || (TEMPERATURE_MAGIC_DATA != p_area->magic_end))
    {
        /* 等待温度保护NV初始化完毕 */
        bsp_softtimer_add(&tem_softtimer);
        return;
    }

    if(1 == p_data->is_first_init)
    {
        /* 备份温度信息，用于检测前后温度异常突变 */
        if(0 != origin_tem_config())
        {
            tem_print_error(" orig_tem_cfg is fail.\n");
    		return ;
        }
        p_data->is_first_init = 0;
    }

    /*电压温度更新到共享内存*/
    tem_update_callback();

    /*温度保护的相关策略*/
    if(0 == device_tem_protect(&tem_region, &tem_status) && (NORMAL_TEMPERATURE != tem_status) && (MAX_REGION != tem_region))
    {
        msg.id     = chan_id;
        msg.region = (unsigned int)tem_region;
        msg.status = (unsigned int)tem_status;

        tem_print_info("tem region%d status %d.\n", tem_region, tem_status);

        len = bsp_icc_send(ICC_CPU_APP, msg.id, (unsigned char*)&msg, sizeof(struct tem_msg_stru));
        if((int)sizeof(struct tem_msg_stru) != len)
        {
            tem_print_error("read len(%x) != expected len(%x).\n", len, sizeof(struct tem_msg_stru));
            return ;
        }

    }

    /* 唤醒时将Timer 0s超时切换为1s */
    if(1 == p_data->is_change_timer)
    {
        if (OK != bsp_softtimer_modify(&tem_softtimer, p_data->tem_update_period * 1000))
        {
            tem_print_error("timer modify error.\n");
            return ;
        }
        p_data->is_change_timer = 0;
    }

    bsp_softtimer_add(&tem_softtimer);
}

int tem_protect_init(void)
{

    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;

    //printk("mcore start time %d.\n", bsp_get_elapse_ms());

    if(MODEM_ALREADY_INIT_MAGIC == get_modem_init_flag())
    {
        return TEMPERATURE_OK;
    }

    memset(p_data, 0, sizeof(DRV_TEMPERATURE_PROTECT_DATA));

    p_data->p_hkadc_area = (DRV_HKADC_DATA_AREA *)(SHM_BASE_ADDR + SHM_OFFSET_TEMPERATURE);

    p_data->tem_update_period = 1;
    p_data->sleep_period      = 10;

	tem_softtimer.func = (softtimer_func)tem_timer_callback;
	tem_softtimer.para = 0;
	tem_softtimer.timeout = p_data->tem_update_period * 1000;
	tem_softtimer.wake_type=SOFTTIMER_WAKE;
	if (bsp_softtimer_create(&tem_softtimer))
	{
		tem_print_error("timer fail\n");
		return TEMPERATURE_ERROR;
	}

    p_data->is_change_timer   = 0;
    p_data->is_first_init     = 1;

    bsp_softtimer_add(&tem_softtimer);

    tem_print_info("tem init ok.\n");

    return TEMPERATURE_OK;

}


s32 tem_protect_suspend(void)
{
    s32 ret = 0;
    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;

    bsp_softtimer_delete(&tem_softtimer);

    ret = bsp_softtimer_modify(&tem_softtimer, p_data->sleep_period * 1000);
    if (ret !=OK)
    {
        tem_print_error("timer modify error\n");
        return TEMPERATURE_ERROR;
    }
    bsp_softtimer_add(&tem_softtimer);

    p_data->is_change_timer = 1;

    return TEMPERATURE_OK;
}

void tem_protect_resume(void)
{
    int i = 0;
    s32 ret = 0;
    DRV_TEMPERATURE_PROTECT_DATA *p_data = &tem_protect_data;

    /*唤醒后，立刻获取各个通道温度*/
    for(i = 0; i < HKADC_CHAN_MAX; i++)
    {
        if(p_data->p_hkadc_area->chan_cfg[i].out_peroid)
        {
            p_data->chan_time[i] = p_data->p_hkadc_area->chan_cfg[i].out_peroid - 1;
        }
    }

    bsp_softtimer_delete(&tem_softtimer);
    ret = bsp_softtimer_modify(&tem_softtimer, 0);
    if (ret != OK)
    {
        tem_print_error("timer modify error\n");
        return ;
    }
    bsp_softtimer_add(&tem_softtimer);

    return ;
}

