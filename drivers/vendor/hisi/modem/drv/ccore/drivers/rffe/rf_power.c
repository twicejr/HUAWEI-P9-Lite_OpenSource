/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  rf_power.c
*
*   作    者 :  zuofenghua
*
*   描    述 :  用于管理射频器件供电
*
*   修改记录 :  2015年3月23日  v1.00  zuofenghua  创建
*
*************************************************************************/
#include <securec.h>
#include <osl_malloc.h>
#include <osl_sem.h>
#include <osl_thread.h>
#include <of.h>
#include <hi_pmu.h>
#include <mdrv_pmu.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_nvim.h>
#include <bsp_regulator.h>
#include <bsp_pmu.h>
#include <bsp_hardtimer.h>
#include <bsp_version.h>
#include <bsp_dump.h>
#include <bsp_pm_om.h>
#include <rf_balong.h>
#include <rf_power.h>

struct pwr_base_info    rfpwr_info[PWR_CONSUMER_NUM];
struct clk_base_info    rfclk_info[RF_CLK_NUM];
struct rf_pwr_clk_debug *rfdbg_om_info;
ST_PWC_SWITCH_STRU      g_pm_nv_switch;
struct pmu_apt_cfg    g_pmu_apt;

static RFFE_POWER_ID_E balong_get_rffe_powerid(EX_RFFE_POWER_ID_E consumer_id, PWC_COMM_CHANNEL_E chn)
{
    switch(consumer_id)
    {
        case TULPA_VCC:
            return TULPA0_VCC + 2 * chn;

        case TULPA_VBIAS:
            return TULPA0_VBIAS + 2 * chn;

        case RFIC_ANALOG0:
            return RFIC0_ANALOG0 + 4 * chn;

        case RFIC_ANALOG1:
            return RFIC0_ANALOG1 + 4 * chn;

        case FEM:
            return FEM_VCC;

        case GPA_VBIAS:
            return GPA0_VBIAS + 2* chn;

        case GPA_VCC:
            return GPA0_VCC + 2*chn;

        default:
            return PWR_CONSUMER_NUM;
    }
}

#ifdef CONFIG_PMU_APT

/*lint -save -e801*/
void balong_rfpower_pmu_reg_write(u32 addr, u32 value)
{
    writel(value, g_pmu_apt.pmu_base + (addr << 2));
}

void  balong_rfpower_pmu_reg_read(u32 addr, u32 *pValue)
{
    *pValue = readl(g_pmu_apt.pmu_base + (addr << 2));
}

void balong_rfpower_pmu_reg_show(u32 addr)
{
    rf_print_error("addr : 0x%x, value : 0x%x\n", addr, readl(g_pmu_apt.pmu_base + (addr << 2)));
}

int balong_rfpower_apt_enable(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{
    unsigned int i    = 0;
    unsigned long flag = 0;
    unsigned int max_reg = 0;

    if(chn >=  g_pmu_apt.chn_cnt){
        return RFFE_ERROR;
    }

    max_reg = g_pmu_apt.info[chn].enable_cnt;
    spin_lock_irqsave(&g_pmu_apt.info[chn].lock, flag);
    for(i = 0; i < max_reg; i++)
    {
        balong_rfpower_pmu_reg_write(g_pmu_apt.info[chn].enable_reg[i], g_pmu_apt.info[chn].enable_val[i]);
    }
    spin_unlock_irqrestore(&g_pmu_apt.info[chn].lock, flag);
    return 0;
}

int balong_rfpower_apt_disable(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{
    unsigned int i    = 0;
    int ret = 0;
    unsigned long flag = 0;
    unsigned int   max_reg = 0;
    RFFE_POWER_ID_E pwr_id = 0;

    if(chn >=  g_pmu_apt.chn_cnt){
        return -1;
    }

    max_reg = g_pmu_apt.info[chn].enable_cnt;

    spin_lock_irqsave(&g_pmu_apt.info[chn].lock, flag);

    if(PWC_COMM_MODE_GSM == mode_id)
    {
        pwr_id  =  balong_get_rffe_powerid(GPA_VCC, chn);
        if(!rfpwr_info[pwr_id].valid){
            goto out;
        }
        ret = balong_rfpower_set_voltage(GPA_VCC, 3700, chn);
        if(ret){
            rf_print_error("rf power set pa voltage fail!chn%d, mode id %d", chn, mode_id);
            goto out;
        }
    }
    else{
        ret = balong_rfpower_set_voltage(TULPA_VCC, 3300, chn);
     if(ret){
            rf_print_error("rf power set pa voltage fail!chn%d, mode id %d", chn, mode_id);
            goto out;
        }

    }
    for(i = 0; i < max_reg; i++)
    {
        balong_rfpower_pmu_reg_write(g_pmu_apt.info[chn].disable_reg[i], g_pmu_apt.info[chn].disable_val[i]);
    }

out:
    spin_unlock_irqrestore(&g_pmu_apt.info[chn].lock, flag);
    return ret;

}

int balong_rfpower_get_apt_status(PWC_COMM_CHANNEL_E chn)
{
    u32 reg = 0;

    if(chn >=  g_pmu_apt.chn_cnt){
        return RFFE_ERROR;
    }

    balong_rfpower_pmu_reg_read(g_pmu_apt.info[chn].enable_reg[0], &reg);
    return (int)reg;
}
int balong_rfpower_apt_init(void)
{
    int ret = 0;
    int i = 0;
    struct device_node *dev_node   = NULL;
    struct device_node *child_node = NULL;
    const char         *name       ="hisilicon,rfpower_pmu_apt";

    /*get pmu base addr*/
    g_pmu_apt.pmu_base = bsp_pmic_get_base_addr();
    if(0 == g_pmu_apt.pmu_base )
    {
        rf_print_error("get pmu base addr error!\n");
        return RFFE_ERROR;
    }

    /*get dts info*/
    dev_node = of_find_compatible_node(NULL, NULL, name);
    if(NULL == dev_node)
    {
        rf_print_error("rf power get apt device node not found!\n");
        return RFFE_ERROR;
    }

    ret  = of_property_read_u32_index(dev_node, "chn_cnt", 0, &g_pmu_apt.chn_cnt);
    if(ret)
    {
        rf_print_error("get apt chn cnt fail , ret %d\n", ret);
        return RFFE_ERROR;
    }

    g_pmu_apt.info = malloc(g_pmu_apt.chn_cnt * sizeof(struct pmu_apt_info));
    if(NULL == g_pmu_apt.info)
    {
        rf_print_error("apt info malloc mem fail!\n");
        return RFFE_ERROR;
    }

    for_each_child_of_node(dev_node, child_node){
        ret  = of_property_read_u32_index(child_node, "enable_cnt", 0, &g_pmu_apt.info[i].enable_cnt);
        ret |= of_property_read_u32_index(child_node, "disable_cnt", 0, &g_pmu_apt.info[i].disable_cnt);
        if(ret)
        {
            rf_print_error("get apt config reg cnt error!ret %d\n", ret);
            return RFFE_ERROR;
        }

        g_pmu_apt.info[i].enable_reg = malloc(g_pmu_apt.info[i].enable_cnt * sizeof(unsigned int));
        if(NULL == g_pmu_apt.info[i].enable_reg)
        {
            rf_print_error("malloc apt enable regs fail!\n");
            goto enable_regs_error;
        }

        g_pmu_apt.info[i].enable_val = malloc(g_pmu_apt.info[i].enable_cnt * sizeof(unsigned int));
        if(NULL == g_pmu_apt.info[i].enable_val)
        {
            rf_print_error("malloc apt enable val fail!\n");
            goto enable_val_err;
        }

        g_pmu_apt.info[i].disable_reg = malloc(g_pmu_apt.info[i].disable_cnt * sizeof(unsigned int));
        if(NULL == g_pmu_apt.info[i].disable_reg)
        {
            rf_print_error("malloc apt disable regs fail\n");
            goto disable_regs_err;
        }

        g_pmu_apt.info[i].disable_val = malloc(g_pmu_apt.info[i].disable_cnt * sizeof(unsigned int));
        if(NULL == g_pmu_apt.info[i].disable_val)
        {
            rf_print_error("malloc apt disable value fail\n");
            goto disable_val_err;
        }

        ret  = of_property_read_u32_array(child_node, "enable_reg", g_pmu_apt.info[i].enable_reg, g_pmu_apt.info[i].enable_cnt);
        ret |= of_property_read_u32_array(child_node, "enable_val", g_pmu_apt.info[i].enable_val, g_pmu_apt.info[i].enable_cnt);
        ret |= of_property_read_u32_array(child_node, "disable_reg", g_pmu_apt.info[i].disable_reg, g_pmu_apt.info[i].disable_cnt);
        ret |= of_property_read_u32_array(child_node, "disable_val", g_pmu_apt.info[i].disable_val, g_pmu_apt.info[i].disable_cnt);
        if(ret)
        {
            rf_print_error("get apt dts node info error,ret %d\n", ret);
            goto disable_val_err;
        }

        /*lock init*/
        spin_lock_init(&g_pmu_apt.info[i].lock);
        balong_rfpower_apt_disable( i, PWC_COMM_MODE_LTE);
        i++;
    }
    return 0;

disable_val_err:
    free(g_pmu_apt.info[i].disable_reg);

disable_regs_err:
    free(g_pmu_apt.info[i].enable_val);

enable_val_err:
    free(g_pmu_apt.info[i].enable_reg);

enable_regs_error:
    if(i > 0){
        i = i-1;
        do{
	     free(g_pmu_apt.info[i].disable_val);
            free(g_pmu_apt.info[i].disable_reg);
            free(g_pmu_apt.info[i].enable_val);
            free(g_pmu_apt.info[i].enable_reg);
             i--;
        }while(i >= 0);
    }
    return RFFE_ERROR;
}

#else

int balong_rfpower_apt_enable(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

int balong_rfpower_apt_disable(PWC_COMM_CHANNEL_E chn, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

int balong_rfpower_get_apt_status(PWC_COMM_CHANNEL_E chn)
{
    return 0;
}

int balong_rfpower_apt_init(void)
{
    return 0;
}

#endif

static int balong_rf_regulator_enable(u32 pwr_id)
{
    if(!rfpwr_info[pwr_id].valid ){

        return RFFE_OK;
    }
    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("power id [%d] regulator pointor is null ,\
            please check dts!\n",pwr_id);
        return RFFE_ERROR;
    }
    return regulator_enable(rfpwr_info[pwr_id].regu);
}

static int balong_rf_regulator_disable(u32 pwr_id)
{
    if(!rfpwr_info[pwr_id].valid || rfpwr_info[pwr_id].disable_off){
        return RFFE_OK;
    }
    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("power id [%d] regulator pointor is null ,\
            please check dts!\n",pwr_id);
        return RFFE_ERROR;
    }
    return regulator_disable(rfpwr_info[pwr_id].regu);
}

static int balong_rf_get_module_status(PWC_COMM_MODULE_E module, PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int status = 0;
    switch(module){
        case PWC_COMM_MODULE_PA:
            status = balong_pa_power_status(mode, modem, chn);
            break;
        case PWC_COMM_MODULE_RF:
            status = balong_rfic_power_status(mode, modem, chn);
            break;
        case PWC_COMM_MODULE_FEM:
            status = balong_fem_power_status(mode, modem, chn);
            break;
        default:
            rf_print_error("rf get module status err, module%d", module);
            status=-1;

    }

    return status;
}
/*****************************************************************************
* 函 数    : balong_rf_regulator_get_status
* 功 能    : 获取硬件的真实电源开关状态
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    : z00228752
* 说 明    : 内部接口

*****************************************************************************/
static int balong_rf_regulator_get_status(u32 pwr_id, PWC_COMM_MODULE_E module, PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    if(!rfpwr_info[pwr_id].valid){
        /*如果没有,表示此路电源不需要软件控制,直接返回逻加状态*/
        return balong_rf_get_module_status(module, mode, modem, chn);
    }

    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("power id [%d] regulator pointor is null ,\
            please check dts!\n",pwr_id);
        return 0;
    }
    return regulator_is_enabled(rfpwr_info[pwr_id].regu);

}
/*****************************************************************************
* 函 数    : balong_rf_regulator_disable_local
* 功 能    : 关闭电源内部接口
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    : z00228752
* 说 明    : 内部接口，与balong_rf_regulator_disable的区别是给int\suspend\resume流程调用
                    不需要判断dts中disable选项
*****************************************************************************/
static int balong_rf_regulator_disable_local(u32 pwr_id)
{

    if(!rfpwr_info[pwr_id].valid){
        return RFFE_OK;
    }
    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("power id [%d] regulator pointor is null ,\
            please check dts!\n",pwr_id);
        return RFFE_ERROR;
    }
    return regulator_disable(rfpwr_info[pwr_id].regu);
}

/*****************************************************************************
* 函 数    : balong_rfpower_set_voltage
* 功 能    : 前端器件设置电压
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    : z00228752
* 说 明    : pa的编号根据chn号确定
*****************************************************************************/
int balong_rfpower_set_voltage( EX_RFFE_POWER_ID_E consumer_id, u32 voltage_mv, PWC_COMM_CHANNEL_E chn )
{
    RFFE_POWER_ID_E pwr_id =  balong_get_rffe_powerid(consumer_id, chn);

    if(PWR_CONSUMER_NUM == pwr_id)
    {
        rf_print_error("power id get fail,consumerid is %d,pwr_id is%d\n",consumer_id, pwr_id);
        return RFFE_ERROR;
    }

    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("regulator pointor is null ,consumerid %d,pwr_id is %d\n",consumer_id, pwr_id);
        return RFFE_ERROR;
    }
    return regulator_set_voltage(rfpwr_info[pwr_id].regu, (int)voltage_mv * 1000 , (int)voltage_mv * 1000);
}

/*****************************************************************************
* 函 数    : balong_rfpower_set_voltage
* 功 能    : 前端器件查询电压
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_rfpower_get_voltage( EX_RFFE_POWER_ID_E consumer_id, PWC_COMM_CHANNEL_E chn)
{
    RFFE_POWER_ID_E pwr_id =  balong_get_rffe_powerid(consumer_id, chn);
    if(PWR_CONSUMER_NUM == pwr_id)
    {
        rf_print_error("power id get fail,consumerid is %d,pwr_id is%d, chn%d\n",consumer_id, pwr_id,chn);
        return RFFE_ERROR;
    }

    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("regulator pointor is null ,consumerid %d,pwr_id is %d,chn%d\n",consumer_id, pwr_id,chn);
        return RFFE_ERROR;
    }

    return regulator_get_voltage(rfpwr_info[pwr_id].regu);
}

static void balong_rfpoweron_debuginfo_add(PWR_DBG_E dbg_id, PWC_COMM_CHANNEL_E chn,
                                                  PWC_COMM_MODE_E mode,
                                                  u32 pwr_id, u32 pwr_num,  PWC_COMM_MODEM_E modem, PWC_COMM_MODULE_E module)
{
    u32 i;
    rfdbg_om_info[dbg_id].info[chn].vote    = rfpwr_info[pwr_id].vote;
    rfdbg_om_info[dbg_id].info[chn].on_cnt[mode]++;
    rfdbg_om_info[dbg_id].info[chn].on_stamp[mode] = bsp_get_slice_value();
    for(i = 0; i < pwr_num; i++){
        rfdbg_om_info[dbg_id].info[chn].hw_stat|= (u32)!!balong_rf_regulator_get_status(pwr_id+i,module, mode, modem,chn) << i;
    }

}

static void balong_rfpoweroff_debuginfo_add(PWR_DBG_E dbg_id, PWC_COMM_CHANNEL_E chn,
                                                  PWC_COMM_MODE_E mode,
                                                  u32 pwr_id, u32 pwr_num, PWC_COMM_MODEM_E modem, PWC_COMM_MODULE_E module)
{
    u32 i;
    rfdbg_om_info[dbg_id].info[chn].vote    = rfpwr_info[pwr_id].vote;
    rfdbg_om_info[dbg_id].info[chn].off_cnt[mode]++;
    rfdbg_om_info[dbg_id].info[chn].off_stamp[mode] = bsp_get_slice_value();
    for(i = 0; i < pwr_num; i++){
        rfdbg_om_info[dbg_id].info[chn].hw_stat|= (u32)!!balong_rf_regulator_get_status(pwr_id+i, module, mode, modem,chn) << i;
    }

}

/*****************************************************************************
* 函 数    : balong_pa_power_on
* 功 能    : PA上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_pa_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1  = 0;
    unsigned int  pwr_id2  = 0;
    unsigned int  vote_bit = 0;
    unsigned int  first_on = 0;
    int           ret      = 0;

    /*get pwr id*/
    if(PWC_COMM_MODE_GSM == mode){
        pwr_id1 = GPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = GPA0_VCC   + chn * PA_PWR_NUM;
    }
    else{
        pwr_id1 = TULPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = TULPA0_VCC   + chn * PA_PWR_NUM;
    }
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }

    /*get vote bit*/
    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    first_on = !rfpwr_info[pwr_id1].vote;
    rfpwr_info[pwr_id1].vote |= (u64)1 << vote_bit;
    if(first_on){/*only first power on ,config pmu register*/
        ret  = balong_rf_regulator_enable(pwr_id1);
        ret |= balong_rf_regulator_enable(pwr_id2);
        rfdbg_om_info[PWR_PA].info[chn].true_on_cnt[mode]++;
        rfdbg_om_info[PWR_PA].info[chn].true_on_stamp[mode] = bsp_get_slice_value();
    }

    balong_rfpoweron_debuginfo_add(PWR_PA, chn, mode, pwr_id1, 2, modem, PWC_COMM_MODULE_PA);
    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return ret;
}


/*****************************************************************************
* 函 数    : balong_pa_power_off
* 功 能    : PA上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_pa_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u32  pwr_id1   = 0;
    u32  pwr_id2   = 0;
    u32  vote_bit  = 0;
    u64  cur_state = 0;
    int  ret       = 0;

    if(PWC_COMM_MODE_GSM == mode){
        pwr_id1 = GPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = GPA0_VCC   + chn * PA_PWR_NUM;
    }
    else{
        pwr_id1 = TULPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = TULPA0_VCC   + chn * PA_PWR_NUM;
    }
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }


    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_pa_pd){

        return RFFE_OK;
    }
    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    /*当前状态为开，电源才可以关闭,防止重复开*/
    cur_state = rfpwr_info[pwr_id1].vote;
    rfpwr_info[pwr_id1].vote &= ~((u64)1 << vote_bit);

    if((0 == rfpwr_info[pwr_id1].vote) && cur_state){
        ret  = balong_rf_regulator_disable(pwr_id1);
        ret |= balong_rf_regulator_disable(pwr_id2);
        rfdbg_om_info[PWR_PA].info[chn].true_off_cnt[mode]++;
        rfdbg_om_info[PWR_PA].info[chn].true_off_stamp[mode] = bsp_get_slice_value();
    }
    balong_rfpoweroff_debuginfo_add(PWR_PA, chn, mode, pwr_id1, 2, modem, PWC_COMM_MODULE_PA);

    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return ret;

}

/*****************************************************************************
* 函 数    : balong_pa_power_status
* 功 能    : PA供电各模投票状态查询接口
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电，-1为不确定
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_pa_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1 = 0;
    int           status  = 0;

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_pa_pd){
        return 1;
    }
    if(PWC_COMM_MODE_GSM == mode){
        pwr_id1 = GPA0_VBIAS + chn * PA_PWR_NUM;
    }
    else{
        pwr_id1 = TULPA0_VBIAS + chn * PA_PWR_NUM;
    }
    if((PWR_CONSUMER_NUM <= pwr_id1))
    {
        return RFFE_ERROR;
    }

    status = !!rfpwr_info[pwr_id1].vote;

    return status;
}

/*****************************************************************************
* 函 数    : balong_pa_power_status
* 功 能    : PA上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电，-1为不确定
* 作 者    :z00228752
* 说 明    :pa的编号根所chn号确定
*****************************************************************************/
int balong_pa_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1 = 0;
    unsigned int  pwr_id2 = 0;
    int           status  = 0;
    int           status1  = 0;
    int           status2  = 0;

    if(PWC_COMM_MODE_GSM == mode){
        pwr_id1 = GPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = GPA0_VCC   + chn * PA_PWR_NUM;
    }
    else{
        pwr_id1 = TULPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = TULPA0_VCC   + chn * PA_PWR_NUM;
    }
    if((PWR_CONSUMER_NUM <= pwr_id1))
    {
        return RFFE_ERROR;
    }


    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    status1 = balong_rf_regulator_get_status(pwr_id1, PWC_COMM_MODULE_PA, mode, modem, chn);
    status2 = balong_rf_regulator_get_status(pwr_id2, PWC_COMM_MODULE_PA, mode, modem, chn);

    osl_sem_up(&rfpwr_info[pwr_id1].sem);
    if(status1 < 0  || status2 < 0)
    {
        rf_print_error("get pa power hw status fail!ret1= %d, ret2= %d \n", status1, status2);
        return RFFE_ERROR;
    }

    status = ((int)!!status1) & ((int)!!status2);
    /*如果投票需要打开电源，电源状态却为关，则打印error*/
    if(!status  &&  balong_pa_power_status( mode, modem, chn))
    {
        rf_print_info("Mode:%d, Modem:%d, Chn:%d vote pa power on, but it is off!\n", mode, modem, chn);
        rf_print_info("Pa power Vbias status is:%d, Vcc status is :%d\n", status1, status2);
    }

    return status ;
}

/*****************************************************************************
* 函 数    : balong_rfic_power_on
* 功 能    : rfic上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
int balong_rfic_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1  = 0;
    unsigned int  pwr_id2  = 0;
    unsigned int  pwr_id3  = 0;
    unsigned int  pwr_id4  = 0;
    unsigned int  vote_bit = 0;
    unsigned int  first_on = 0;
    int           ret      = 0;

    pwr_id1 = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
    pwr_id2 = RFIC0_ANALOG1 + chn * RF_PWR_NUM;
    pwr_id3 = RFIC0_ANALOG2 + chn * RF_PWR_NUM;
    pwr_id4 = RFIC0_DIGITAL + chn * RF_PWR_NUM;
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }

    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    first_on = !rfpwr_info[pwr_id1].vote;
    rfpwr_info[pwr_id1].vote |= (u64)1 << vote_bit;
    if(first_on){
        ret  = balong_rf_regulator_enable(pwr_id1);
        ret |= balong_rf_regulator_enable(pwr_id2);
        ret |= balong_rf_regulator_enable(pwr_id3);
        ret |= balong_rf_regulator_enable(pwr_id4);
        rfdbg_om_info[PWR_RFIC].info[chn].true_on_cnt[mode]++;
        rfdbg_om_info[PWR_RFIC].info[chn].true_on_stamp[mode] = bsp_get_slice_value();

    }
    balong_rfpoweron_debuginfo_add(PWR_RFIC, chn, mode, pwr_id1, 4,  modem, PWC_COMM_MODULE_RF);

    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return ret;
}

/*****************************************************************************
* 函 数    : balong_rfic_power_off
* 功 能    : rfic下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根据chn号确定
*****************************************************************************/
int balong_rfic_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u32  pwr_id1   = 0;
    u32  pwr_id2   = 0;
    u32  pwr_id3   = 0;
    u32  pwr_id4   = 0;
    u32  vote_bit  = 0;
    u64  cur_state = 0;
    int  ret       = 0;

    pwr_id1 = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
    pwr_id2 = RFIC0_ANALOG1 + chn * RF_PWR_NUM;
    pwr_id3 = RFIC0_ANALOG2 + chn * RF_PWR_NUM;
    pwr_id4 = RFIC0_DIGITAL + chn * RF_PWR_NUM;
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfic_pd){

        return RFFE_OK;
    }

    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    /*当前状态为开，电源才可以关闭,防止重复关闭*/
    cur_state = rfpwr_info[pwr_id1].vote;
    rfpwr_info[pwr_id1].vote &= ~((u64)1 << vote_bit);
    if((0 == rfpwr_info[pwr_id1].vote) && cur_state){
        ret  = balong_rf_regulator_disable(pwr_id1);
        ret |= balong_rf_regulator_disable(pwr_id2);
        ret |= balong_rf_regulator_disable(pwr_id3);
        ret |= balong_rf_regulator_disable(pwr_id4);
        rfdbg_om_info[PWR_RFIC].info[chn].true_off_cnt[mode]++;
        rfdbg_om_info[PWR_RFIC].info[chn].true_off_stamp[mode] = bsp_get_slice_value();

    }
    balong_rfpoweroff_debuginfo_add(PWR_RFIC, chn, mode, pwr_id1, 4,  modem, PWC_COMM_MODULE_RF);
    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return ret;
}

/*****************************************************************************
* 函 数    : balong_rfic_power_status
* 功 能    : rfic供电物理状态查询接口
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
int balong_rfic_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id  = 0;
    int           status  = 0;

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfic_pd){
        return 1;
    }

    pwr_id = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
    if(PWR_CONSUMER_NUM <= pwr_id)
    {
        return RFFE_ERROR;
    }

    status = !!rfpwr_info[pwr_id].vote;

    return status;
}

/*****************************************************************************
* 函 数    : balong_rfic_power_hw_status
* 功 能    : rfic电源开关状态查询
* 输 入    : 无
* 输 出    : 无
* 返 回    : 1为上电,0为下电
* 作 者    :z00228752
* 说 明    :rfic的编号根所chn号确定
*****************************************************************************/
int balong_rfic_power_hw_status( PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1  = 0;
    unsigned int  pwr_id2  = 0;
    unsigned int  pwr_id3  = 0;
    unsigned int  pwr_id4  = 0;
    int           status1  = 0;
    int           status2  = 0;
    int           status3  = 0;
    int           status4  = 0;
    int           status   = 0;

    pwr_id1 = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
    pwr_id2 = RFIC0_ANALOG1 + chn * RF_PWR_NUM;
    pwr_id3 = RFIC0_ANALOG2 + chn * RF_PWR_NUM;
    pwr_id4 = RFIC0_DIGITAL + chn * RF_PWR_NUM;
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    status1 = balong_rf_regulator_get_status(pwr_id1, PWC_COMM_MODULE_RF, mode, modem, chn);
    status2 = balong_rf_regulator_get_status(pwr_id2, PWC_COMM_MODULE_RF, mode, modem, chn);
    status3 = balong_rf_regulator_get_status(pwr_id3, PWC_COMM_MODULE_RF, mode, modem, chn);
    status4 = balong_rf_regulator_get_status(pwr_id4, PWC_COMM_MODULE_RF, mode, modem, chn);

    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    if(status1 < 0 || status2<0 || status3 < 0 || status4 <0)
    {
        rf_print_error("get rfic power status fail,ret1 = %d, ret2 = %d, ret3 = %d, ret4 = %d\n", status1, status2, status3, status4);
        return RFFE_ERROR;
    }
    status = ((int)!!status1) & ((int)!!status2) & ((int)!!status3) & ((int)!!status4);
    /*如果投票需要打开电源，电源状态却为关，则打印error*/
    if(!status  &&  balong_rfic_power_status( mode, modem, chn))
    {
        rf_print_info("Mode:%d, Modem:%d, Chn:%d vote rfic power on, but it is off!\n", mode, modem, chn);
        rf_print_info("rfic power analogo0 status is %d, analogo1 :%d, analogo2:%d, digital power is %d!\n", status1, status2, status3, status4);
    }

    return status;
}

/*****************************************************************************
* 函 数    : balong_fem_power_on
* 功 能    : fem上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为上电成功
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
int balong_fem_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id   = 0;
    unsigned int  vote_bit = 0;
    unsigned int  first_on = 0;
    int           ret      = 0;

    pwr_id = FEM_VCC ;/*fem不区分channel信息*/

    vote_bit = RF_PWR_MODE_NUM*PWC_COMM_MODEM_BUTT*chn + RF_PWR_MODE_NUM*modem +mode;

    osl_sem_down(&rfpwr_info[pwr_id].sem);

    first_on = !rfpwr_info[pwr_id].vote;
    rfpwr_info[pwr_id].vote |= (u64)1 << vote_bit;
    if(first_on){
        ret = balong_rf_regulator_enable(pwr_id);
        rfdbg_om_info[PWR_FEM].info[chn].true_on_cnt[mode]++;
        rfdbg_om_info[PWR_FEM].info[chn].true_on_stamp[mode] = bsp_get_slice_value();

    }
    balong_rfpoweroff_debuginfo_add(PWR_FEM, chn, mode, pwr_id, 1,  modem, PWC_COMM_MODULE_FEM);
    osl_sem_up(&rfpwr_info[pwr_id].sem);

    return ret;
}


/*****************************************************************************
* 函 数    : balong_fem_power_off
* 功 能    : fem下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
int balong_fem_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u32  pwr_id    = 0;
    u32  vote_bit  = 0;
    u64  cur_state = 0;
    int  ret       = 0;

    pwr_id = FEM_VCC;
    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_fem_pd){

        return RFFE_OK;
    }

    vote_bit = RF_PWR_MODE_NUM*PWC_COMM_MODEM_BUTT*chn + RF_PWR_MODE_NUM*modem +mode;

    osl_sem_down(&rfpwr_info[pwr_id].sem);

    /*当前状态为开，电源才可以关闭,防止重复关闭*/
    cur_state = rfpwr_info[pwr_id].vote;

    rfpwr_info[pwr_id].vote &= ~((u64)1 << vote_bit);
    if((0 == rfpwr_info[pwr_id].vote) && cur_state){
        ret = balong_rf_regulator_disable(pwr_id);
        rfdbg_om_info[PWR_FEM].info[chn].true_off_cnt[mode]++;
        rfdbg_om_info[PWR_FEM].info[chn].true_off_stamp[mode] = bsp_get_slice_value();

    }
    balong_rfpoweron_debuginfo_add(PWR_FEM, chn, mode, pwr_id, 1,  modem, PWC_COMM_MODULE_FEM);
    osl_sem_up(&rfpwr_info[pwr_id].sem);

    return ret;
}

/*****************************************************************************
* 函 数    : balong_fem_power_status
* 功 能    : fem下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电，1为上电
* 作 者    :z00228752
* 说 明    :fem 的编号根所modem号确定
*****************************************************************************/
int balong_fem_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id  = 0;
    int           ret     = 0;

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_fem_pd){
        return 1;
    }

    pwr_id = FEM_VCC;

    ret = !!rfpwr_info[pwr_id].vote;

    return ret;
}

/*****************************************************************************
* 函 数    : balong_fem_power_hw_status
* 功 能    : fem电源状态查询
* 输 入    : 无
* 输 出    : 无
* 返 回    : 1为上电,0为下电
* 作 者    : z00228752
* 说 明    : fem 的编号根所modem号确定
*****************************************************************************/
int balong_fem_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id   = 0;
    int           status      = 0;

    pwr_id = FEM_VCC ;/*fem不区分channel信息*/

    osl_sem_down(&rfpwr_info[pwr_id].sem);

    status = balong_rf_regulator_get_status(pwr_id, PWC_COMM_MODULE_FEM, mode, modem, chn);

    osl_sem_up(&rfpwr_info[pwr_id].sem);

    /*如果投票需要打开电源，电源状态却为关，则打印error*/
    if(!status  &&  balong_fem_power_status( mode, modem, chn))
    {
        rf_print_info("Mode:%d, Modem:%d, Chn:%d vote fem power on, but it is off! \n", mode, modem, chn);
    }

    return !!status;
}

/*****************************************************************************
* 函 数    : balong_rfclk_enable
* 功 能    : 打开pmu给rfclk提供的时钟
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    : z00228752
* 说 明    : clk的编号根chn号确定
*****************************************************************************/
int balong_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  first_on = 0;
    unsigned int  vote_bit = 0;

    if(chn >= RF_CLK_NUM){
        rf_print_error("chn id is invalid ,chn is %d,max is surport %d\n",chn, RF_CLK_NUM);
        return RFFE_ERROR;
    }

    vote_bit = RF_PWR_MODE_NUM*modem + mode;
    osl_sem_down(&rfclk_info[chn].sem);

    first_on = !rfclk_info[chn].vote;

    rfclk_info[chn].vote |= (u64)1 << vote_bit;

    if(first_on){
        bsp_pmu_rfclk_enable(chn);
        rfdbg_om_info[CLK_RFIC].info[chn].true_on_cnt[mode]++;
        rfdbg_om_info[CLK_RFIC].info[chn].true_on_stamp[mode] = bsp_get_slice_value();

    }

    rfdbg_om_info[CLK_RFIC].info[chn].vote    = rfclk_info[chn].vote;
    rfdbg_om_info[CLK_RFIC].info[chn].on_cnt[mode]++;
    rfdbg_om_info[CLK_RFIC].info[chn].on_stamp[mode] = bsp_get_slice_value();

    osl_sem_up(&rfclk_info[chn].sem);

    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rfclk_disable
* 功 能    : 关闭pmu给rfclk提供的时钟
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    :z00228752
* 说 明    :clk的编号根chn号确定
*****************************************************************************/
int balong_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u64           cur_state = 0;
    unsigned int  vote_bit  = 0;

    if(chn >= RF_CLK_NUM){
        rf_print_error("chn id is invalid ,chn is %d,max is surport %d\n",chn, RF_CLK_NUM);
        return RFFE_ERROR;
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfclk_pd){

        return RFFE_OK;
    }

    vote_bit = RF_PWR_MODE_NUM*modem + mode;
    osl_sem_down(&rfclk_info[chn].sem);

    cur_state = rfclk_info[chn].vote;

    rfclk_info[chn].vote &= ~((u64)1 << vote_bit);

    if(cur_state && (0 == rfclk_info[chn].vote)){
        bsp_pmu_rfclk_disable(chn);
        rfdbg_om_info[CLK_RFIC].info[chn].true_off_cnt[mode]++;
        rfdbg_om_info[CLK_RFIC].info[chn].true_off_stamp[mode] = bsp_get_slice_value();

    }

    rfdbg_om_info[CLK_RFIC].info[chn].vote    = rfclk_info[chn].vote;
    rfdbg_om_info[CLK_RFIC].info[chn].off_cnt[mode]++;
    rfdbg_om_info[CLK_RFIC].info[chn].off_stamp[mode] = bsp_get_slice_value();
    osl_sem_up(&rfclk_info[chn].sem);

    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : balong_rfclk_hw_status
* 功 能    : 查询pmu给rfclk提供的时钟状态,查看逻辑状态
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    :z00228752
* 说 明    :clk的编号根chn号确定
*****************************************************************************/
int balong_rfclk_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int           status  = 0;

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfclk_pd){
        return 1;
    }

    osl_sem_down(&rfclk_info[chn].sem);

    status =  !!rfclk_info[chn].vote;

    osl_sem_up(&rfclk_info[chn].sem);

    return status;

}

/*****************************************************************************
* 函 数    : balong_rfclk_hw_status
* 功 能    : 查询pmu给rfclk提供的时钟状态
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    : z00228752
* 说 明    : clk的编号根chn号确定
*****************************************************************************/
int balong_rfclk_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int status = 0;
    osl_sem_down(&rfclk_info[chn].sem);

    status =  bsp_pmu_rfclk_is_enabled(chn);

    osl_sem_up(&rfclk_info[chn].sem);

    if(status < 0){
        rf_print_error("get rfic clk error!ret = %d\n", status);
        return RFFE_ERROR;
    }

    /*如果投票需要打开时钟，时钟状态却为关，则打印error*/
    if(!status  &&  balong_rfclk_status( mode, modem, chn))
    {
        rf_print_info("Mode:%d, Modem:%d, Chn:%d vote rfclk enable, but it is off!\n", mode, modem, chn);
    }

    return !!status;

}
/*****************************************************************************
* 函 数    : balong_vio_power_off
* 功 能    : 低功耗恢复时，把需要打开的电源上电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
int balong_rf_power_resume(void)
{
    int ret    = RFFE_OK;
    int pwr_id = 0;

    for(pwr_id = 0; pwr_id < PWR_CONSUMER_NUM; pwr_id++ ){
        if(rfpwr_info[pwr_id].init_on && rfpwr_info[pwr_id].dpm_off){
            ret |=balong_rf_regulator_enable(pwr_id);
        }
    }
    return ret;
}
/*****************************************************************************
* 函 数    : balong_vio_power_off
* 功 能    : 低或耗睡眠前，把需要关闭的电源下电
* 输 入    : 无
* 输 出    : 无
* 返 回    : 0为下电成功
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
int balong_rf_power_suspend(void)
{
    int ret    = RFFE_OK;
    int pwr_id = 0;

    for(pwr_id = 0; pwr_id < PWR_CONSUMER_NUM; pwr_id++ ){
        if(rfpwr_info[pwr_id].dpm_off){
            ret |=balong_rf_regulator_disable_local(pwr_id);
        }
    }
    return ret;
}

/*RFIC_VCC_OCP*/
void balong_rffe_ocp_handler(int volt_id)
{
    rf_print_error("RFIC volt ocp,%d!\n",volt_id);
}

void balong_rf_power_debug_init(void)
{
    u32 dbg_len = PWR_DBG_NUM * sizeof(struct rf_pwr_clk_debug);

    /*可维可测初始化*/
    rfdbg_om_info = bsp_pm_dump_get(PM_OM_RFFE, dbg_len);
    if(NULL == rfdbg_om_info)
    {
        rf_print_error("pm_dump malloc failed,malloc myself!\n");
        rfdbg_om_info = malloc(dbg_len);
        if(NULL == rfdbg_om_info){
            rf_print_error("pm_dump malloc memory fail!\n");
            return ;
        }
    }
    (void)memset_s(rfdbg_om_info, dbg_len, 0, dbg_len);

}
int balong_rf_power_dts_init(void)
{
    int          ret = 0;
    unsigned int id  = 0;
    struct device_node *dev_node   = NULL;
    struct device_node *child_node = NULL;
    const char         *name       ="hisilicon,rfpower_balong";

    /*get dts info*/
    dev_node = of_find_compatible_node(NULL, NULL, name);
    if(NULL == dev_node)
    {
        rf_print_error("rf power device node not found!\n");
        return RFFE_ERROR;
    }

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node, "pwr_id", 0, &id);
        if(ret)
        {
            rf_print_error("get rf pwr id fail\n");
            return RFFE_ERROR;
        }
        if(id >= PWR_CONSUMER_NUM){
            rf_print_error("rf pwr id err,please check dts!id is %d\n",id);
            break;
        }

        rfpwr_info[id].pwr_id = id;

        ret = of_property_read_u32_index(child_node, "valid", 0, &rfpwr_info[id].valid);

        if(rfpwr_info[id].valid){

            ret = of_property_read_string_index(child_node,"regulator_name",0,&rfpwr_info[id].name);
            if(ret)
            {
                rf_print_error("get rf regulator_name fail\n");
                return RFFE_ERROR;
            }
            ret |= of_property_read_u32_index(child_node, "init_on", 0, &rfpwr_info[id].init_on);

            ret |= of_property_read_u32_index(child_node, "dpm_off", 0, &rfpwr_info[id].dpm_off);

            ret |= of_property_read_u32_index(child_node, "voltage", 0, &rfpwr_info[id].voltage);

            ret |= of_property_read_u32_index(child_node, "disable_off", 0, &rfpwr_info[id].disable_off);
            if(ret)
            {
                rf_print_error("rf power get consumer dts information fail, id is %d!\n",id);
                return RFFE_ERROR;
            }

        }
    }

    return RFFE_OK;
}
/*****************************************************************************
* 函 数    : balong_rf_power_init
* 功 能    : 射频供电初始化
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    :z00228752
* 说 明    :
*****************************************************************************/
int balong_rf_power_init(void)
{
    int          ret = 0;
    unsigned int id  = 0;

    /*get nv info*/
    ret = bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)(&g_pm_nv_switch), sizeof(ST_PWC_SWITCH_STRU));/*lint !e713*/
    if(ret)
    {
        rf_print_error("NV_ID_DRV_NV_PWC_SWITCH:D10B read fail!,ret:%d\n",ret);
    }

    /*get dts info and volt init*/
    ret = balong_rf_power_dts_init();
    if(ret)
    {
        rf_print_error("balong_rf_power_dts_init fail!,ret:%d\n",ret);
        return RFFE_ERROR;
    }

    /*volt init*/
    for(id = 0; id < PWR_CONSUMER_NUM; id++){
        if(rfpwr_info[id].valid){
            rfpwr_info[id].regu = regulator_get(NULL,(char *)rfpwr_info[id].name);

            /*初始化配置电压*/
            if((NULL != rfpwr_info[id].regu ) && rfpwr_info[id].voltage){
                ret = regulator_set_voltage(rfpwr_info[id].regu, (int)rfpwr_info[id].voltage, (int)rfpwr_info[id].voltage);
                if(ret)
                {
                    rf_print_error("rf power set voltage faild! power id is %d\n",id);
                    return RFFE_ERROR;
                }
            }

            /*打开需始化就需要打开的电源*/
            if(rfpwr_info[id].init_on){
                ret = balong_rf_regulator_enable(id);
                if(ret)
                {
                    rf_print_error("rf power enable faild! power id is %d\n",id);
                    return RFFE_ERROR;
                }
            }

            /*注册ocp异常处理*/
            ret |= bsp_pmu_ocp_register((int)rfpwr_info[id].regu->id,balong_rffe_ocp_handler);
            if(0 != ret)
            {
                rf_print_error("pmu ocp register error.\n");
                //return RFFE_ERROR;
            }

        }
        /*初始化信号量*/
        osl_sem_init(RF_PWR_SEM_FULL, &rfpwr_info[id].sem);


    }

    /*rfclk init*/
    for(id = 0; id < RF_CLK_NUM; id++){
        osl_sem_init(RF_PWR_SEM_FULL, &rfclk_info[id].sem);
    }


    /*debug info init*/
    balong_rf_power_debug_init();

    /*TUL pa volt is enable depands on nv */
    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_pa_pd){
        ret |= balong_rf_regulator_enable(TULPA0_VCC);
        ret |= balong_rf_regulator_enable(TULPA1_VCC);
        ret |= balong_rf_regulator_enable(TULPA2_VCC);
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfic_pd){
        ret |= balong_rf_regulator_enable(RFIC0_ANALOG0);
        ret |= balong_rf_regulator_enable(RFIC0_ANALOG1);
        ret |= balong_rf_regulator_enable(RFIC1_ANALOG0);
        ret |= balong_rf_regulator_enable(RFIC1_ANALOG1);
        ret |= balong_rf_regulator_enable(RFIC2_ANALOG0);
        ret |= balong_rf_regulator_enable(RFIC2_ANALOG1);
        udelay(200);
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_fem_pd){
        ret |= balong_rf_regulator_enable(FEM_VCC);
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfclk_pd){
        bsp_pmu_rfclk_enable(0);
        bsp_pmu_rfclk_enable(1);
    }

    /*apt init*/
    ret |= balong_rfpower_apt_init();

    return ret;
}

int balong_rfpower_vote_get(PWR_DBG_E consumer, PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u32 pwr_id    = 0;
    u32 vote_bit  = 0;
    u64 vote_lock = 0;

    switch (consumer){
        case PWR_RFIC:
            vote_bit = RF_PWR_MODE_NUM*modem + mode;
            pwr_id   = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
            break;
        case PWR_PA:
            vote_bit = RF_PWR_MODE_NUM*modem + mode;
            if(PWC_COMM_MODE_GSM == mode){
                pwr_id = GPA0_VBIAS + chn * PA_PWR_NUM;
            }
            else{
                pwr_id = TULPA0_VBIAS + chn * PA_PWR_NUM;
            }
            break;
        case PWR_FEM:
            vote_bit = RF_PWR_MODE_NUM*PWC_COMM_MODEM_BUTT*chn + RF_PWR_MODE_NUM*modem +mode;
            pwr_id   = FEM_VCC;
            break;
        default:
            break;
    }

    vote_lock = ((u64)1 << vote_bit) & (rfpwr_info[pwr_id].vote);

    return !!vote_lock;
}

void balong_rfpower_print_mode_info(int mode, char *name)
{
    switch(mode){
        case PWC_COMM_MODE_GSM:
            memcpy_s(name, 32, "GSM",4);
            break;
        case PWC_COMM_MODE_TDS:
            memcpy_s(name, 32, "TDS",4);
            break;
        case PWC_COMM_MODE_LTE:
            memcpy_s(name, 32, "LTE",4);
            break;
        case PWC_COMM_MODE_WCDMA:
            memcpy_s(name, 32, "WCDMA",6);
            break;
        case PWC_COMM_MODE_CDMA_1X:
            memcpy_s(name, 32, "CDMA_1X",8);
            break;
        case PWC_COMM_MODE_CDMA_HRPD:
            memcpy_s(name, 32, "CDMA_HRPD",10);
            break;
        default:
            return ;
    }
    return ;
}

void balong_rfpower_debug_unit(PWR_DBG_E id)
{
    int chn   = 0;
    int mode  = 0;
    u32 vote_low = 0;
    u32 vote_high= 0;
    char consumer[32];

    rf_print_dbg("%-15s%-10s%-16s", \
    "mode", "chn", "vote");
    rf_print_dbg("%-10s%-10s%-10s%-10s%-10s", \
       "hwstat","on_cnt","off_cnt", "on_time", "off_time");
    rf_print_dbg("%-10s%-10s%-10s%-10s\n", \
        "t_on_cnt","t_off_cnt", "t_on_time", "t_off_time");
    for(mode = 0; mode < RF_PWR_MODE_NUM; mode++){
        balong_rfpower_print_mode_info(mode, consumer);
        for(chn = 0; chn < RF_PWR_CHN_NUM; chn++){
            vote_low  = (u32)rfdbg_om_info[id].info[chn].vote;
            vote_high = (u32)(rfdbg_om_info[id].info[chn].vote >> 32);
            rf_print_dbg("%-15s%-10d%8x%-08x",consumer, chn, vote_high, vote_low);
            rf_print_dbg("%-10x%-10x%-10x%-10x%-10x", \

                rfdbg_om_info[id].info[chn].hw_stat ,
                    rfdbg_om_info[id].info[chn].on_cnt[mode],
                    rfdbg_om_info[id].info[chn].off_cnt[mode],
                    rfdbg_om_info[id].info[chn].on_stamp[mode],
                    rfdbg_om_info[id].info[chn].off_stamp[mode]);
                    //rfdbg_om_info[id].info[chn].hw_stat
            rf_print_dbg("%-10x%-10x%-10x%-10x\n", \
                    rfdbg_om_info[id].info[chn].true_on_cnt[mode],
                    rfdbg_om_info[id].info[chn].true_off_cnt[mode],
                    rfdbg_om_info[id].info[chn].true_on_stamp[mode],
                    rfdbg_om_info[id].info[chn].true_off_stamp[mode]);
                osl_task_delay(2);
            }
        }
}

/*****************************************************************************
* 函 数    : balong_rfpower_debug
* 功 能    : 前端器件设置电压
* 输 入    : 无
* 输 出    : 无
* 返 回    :
* 作 者    : z00228752
* 说 明    : 内部接口
                    不需要判断disable接口
*****************************************************************************/
void balong_rfpower_debug_help(void)
{
    rf_print_dbg("PWR_DBG_E id is RFIC--0,FEM--1,PA--2,RFCLK--3\n");
    rf_print_dbg("PWC_COMM_MODE_E is G--0,W----1,L---2,T------3\n");
    rf_print_dbg("check vote and timestamp: balong_rfpower_debug_unit(PWR_DBG_E id)\n");
    rf_print_dbg("open tulpa :balong_pa_power_on(mode, modem, chn)\n");
    rf_print_dbg("open rfic  :balong_rfic_power_on(mode, modem, chn)\n");
    rf_print_dbg("open fem   :balong_fem_power_on(mode, modem, chn)\n");
    rf_print_dbg("open rfclk :balong_rfclk_enable(mode, modem, chn)\n");
    rf_print_dbg("close tulpa:balong_pa_power_off(mode, modem, chn)\n");
    rf_print_dbg("close rfic :balong_rfic_power_off(mode, modem, chn)\n");
    rf_print_dbg("close fem  :balong_fem_power_off(mode, modem, chn)\n");
    rf_print_dbg("close rfclk:balong_rfclk_disable(mode, modem, chn)\n");
    return ;
}

/*lint -restore*/

