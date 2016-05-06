#include <product_config.h>
#include <string.h>
#include <osl_common.h>
#include <osl_bio.h>
#include <osl_spinlock.h>
#include <osl_thread.h>
#include <osl_list.h>
#include <of.h>
#include <soc_memmap.h>
#include <bsp_om.h>
#include <bsp_regulator.h>
#include <bsp_pmu.h>
#include <bsp_shared_ddr.h>
#include <pmu_pmic.h>
#include <hi_pmu.h>

extern struct pmic_volt_info g_pmic_voltinfo;
extern struct pmic_xo_info g_pmic_xoinfo;
extern struct dcdc_info g_pmu_exdcdc;
extern struct list_head regulator_list;

//#define pmu_print_dbg(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, fmt,##__VA_ARGS__))
#ifdef __OS_RTOSCK__
#define pmu_print_dbg SRE_Printf
#else
#define pmu_print_dbg(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, fmt,##__VA_ARGS__))
#endif

/*****************************************************************************
* 函 数 : pmic_log_level_set
* 功 能 : pmic 相关打印等级设置
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
void pmic_log_level_set_debug(u32 level)
{
    (void)bsp_mod_level_set(BSP_MODU_PMU, level);
    (void)pmu_print_dbg("bbp log id=%d, set to level=%d)\n",BSP_MODU_PMU,level);
}
/*****************************************************************************
* 函 数 : pmic_log_level_get
* 功 能 : 获取bbp 相关打印等级
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
u32 pmic_log_level_get_debug(void)
{
    u32 log_level = 0;

    log_level = bsp_log_module_cfg_get(BSP_MODU_PMU);
    (void)pmu_print_dbg("bbp log id=%d, level=%d\n",BSP_MODU_PMU,log_level);
    return log_level;
}

void pmic_volt_set_debug(int volt_id, int voltage)
{
    unsigned selector = 0;

    (void)pmic_volt_set_voltage(volt_id, voltage, voltage,&selector);
    (void)pmu_print_dbg("set %d to %d, selector = %d\n", volt_id, voltage, selector);
}

void pmic_addr_debug(void)
{
    int volt_id = 0;
    struct pmic_volt_ctrl *volt_ctrl = NULL;
    struct pmic_volt_reg *volt_reg = NULL;

    (void)pmu_print_dbg("%-10s%-10s%-10s%-10s%-10s%-10s", "id", "name", "en_reg","en_bit","dis_reg","dis_bit");
    (void)pmu_print_dbg("%-10s%-10s%-10s%-10s\n", "state_reg","state_bit","volt_reg", "volt_mask");

    for(volt_id = g_pmic_voltinfo.volt_min; volt_id <= g_pmic_voltinfo.volt_max; volt_id++)
    {
        volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];
        volt_reg = &g_pmic_voltinfo.volt_ctrl[volt_id].volt_reg;
        (void)pmu_print_dbg("%-10d%-10s0x%-8x%-10d0x%-8x%-10d",volt_ctrl->id,volt_ctrl->name,\
            volt_reg->en_reg,volt_reg->en_bit,volt_reg->dis_reg,volt_reg->dis_bit);
        (void)pmu_print_dbg("0x%-8x%-10d0x%-8x0x%-8x\n",volt_reg->state_reg,volt_reg->state_bit,\
            volt_reg->voltage_reg,volt_reg->voltage_mask);
    }
}
void pmic_voltage_table_debug()
{
    struct pmic_volt_ctrl *volt_ctrl = NULL;
    int volt_id = 0;
    u32 selector,voltage = 0;

    for(volt_id = g_pmic_voltinfo.volt_min; volt_id <= g_pmic_voltinfo.volt_max; volt_id++)
    {
        volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];

        (void)pmu_print_dbg("%-10d%-10s num:%d table(uV):",volt_id,volt_ctrl->name,volt_ctrl->voltage_nums);
        for(selector = 0;selector < volt_ctrl->voltage_nums;selector++)
        {
            voltage = pmic_volt_list_voltage(volt_id,selector);
            (void)pmu_print_dbg(" %d",voltage);
        }
        (void)pmu_print_dbg(".\n");
    }
}
void pmic_volt_id_debug(void)
{
    struct pmic_volt_ctrl *volt_ctrl = NULL;
    int volt_id = 0;

    (void)pmu_print_dbg("%-10s%-10s\n","id", "name");
    for(volt_id = g_pmic_voltinfo.volt_min; volt_id <= g_pmic_voltinfo.volt_max; volt_id++)
    {
        volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];
        (void)pmu_print_dbg("%-10d%-10s\n",volt_ctrl->id,volt_ctrl->name);
    }
}

void pmic_volt_state_debug(void)
{
    struct pmic_volt_ctrl *volt_ctrl = NULL;
    int volt_id = 0;
    unsigned int onoff = 0;
    int voltage = 0;

    (void)pmu_print_dbg("%-10s%-10s%-20s%-20s\n","id", "name","is_enabled","voltage(uV)");
    for(volt_id = g_pmic_voltinfo.volt_min; volt_id <= g_pmic_voltinfo.volt_max; volt_id++)
    {
        onoff = !!pmic_volt_is_enabled(volt_id);
        voltage = pmic_volt_get_voltage(volt_id);
        volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];
        (void)pmu_print_dbg("%-10d%-10s%-20d%-20d\n",volt_ctrl->id,volt_ctrl->name,onoff,voltage);
    }
}
void dcdc_state_debug(void)
{
    struct dcdc_ctrl *dcdc_ctrl = NULL;
    unsigned int dc_id = 0;
    unsigned int onoff = 0;

    (void)pmu_print_dbg("%-20s%-20s%-20s%-20s\n","id", "name","gpio","is_enabled");
    for(dc_id = 0; dc_id < g_pmu_exdcdc.dc_num; dc_id++)
    {
        onoff = !!dcdc_volt_is_enabled((int)dc_id);
        dcdc_ctrl = &g_pmu_exdcdc.dc_ctrl[dc_id];
        (void)pmu_print_dbg("%-20d%-20s%-20d%-20d\n",dcdc_ctrl->id,dcdc_ctrl->name,dcdc_ctrl->gpio_id,onoff);
    }
}
void pmic_xo_reg_debug(void)
{
    struct xo_reg_ctrl *xo_ctrl = NULL;
    struct pmic_xorf_ctrl *xorf_ctrl = NULL;
    u32 rf_id = 0;

    (void)pmu_print_dbg("****************c1c2 addr************************\n");
    (void)pmu_print_dbg("%-20s%-20s%-20s%-20s\n","c1_base","c2_base","c2_mask","c2_offset");
    xo_ctrl = &g_pmic_xoinfo.xo_ctrl;
    (void)pmu_print_dbg("0x%-20x0x%-20x0x%-20x0x%-20x\n",xo_ctrl->c1_base,xo_ctrl->c2_base,xo_ctrl->c2_mask,xo_ctrl->c2_offset);

    (void)pmu_print_dbg("****************xorf addr************************\n");
    (void)pmu_print_dbg("%-20s%-20s%-20s%","rf_id","onoff_addr","onoff_bit");
    (void)pmu_print_dbg("%-20s%-20s%-20s%-20s%\n","fre_addr","freq_mask","freq_offset","freq_value");
    for(rf_id = 0; rf_id < g_pmic_xoinfo.xorf_num; rf_id++)
    {
        xorf_ctrl = &g_pmic_xoinfo.xorf_ctrl[rf_id];

        (void)pmu_print_dbg("%-20d0x%-20x%-20d%",xorf_ctrl->rf_id,xorf_ctrl->reg_ctrl.reg_base,xorf_ctrl->reg_ctrl.reg_bit);
        (void)pmu_print_dbg("0x%-20x0x%-20x0x%-20x0x%-20x\n",xorf_ctrl->freq_ctrl.freq_addr,xorf_ctrl->freq_ctrl.freq_mask,\
        xorf_ctrl->freq_ctrl.freq_offset,xorf_ctrl->freq_ctrl.freq_value);
    }
}
void pmic_xo_state_debug(void)
{
    u32 rf_id,rffreq,dcxoId,value = 0;
    struct pmic_xorf_ctrl *xorf_ctrl = NULL;
    int onoff = 0;

    (void)pmu_print_dbg("****************c1c2 info************************\n");
    (void)pmu_print_dbg("%-20s%-20s\n","id(0:c1,1:c2)","compensate_value");
    for(dcxoId = 0; dcxoId < DCXO_COMPENSATE_BUTT; dcxoId++)
    {
        value = pmic_dcxo_compensate_get(dcxoId);
        (void)pmu_print_dbg("%-20d0x%-20x\n",dcxoId,value);
    }

    (void)pmu_print_dbg("****************xorf info************************\n");
    (void)pmu_print_dbg("%-10s%-20s%-20s%-20s\n","id","is_enabled","freq_val_dtsset","freq_val_act");
    for(rf_id = 0; rf_id < g_pmic_xoinfo.xorf_num; rf_id++)
    {
       onoff = !!pmic_rfclk_is_enabled(rf_id);
       rffreq = pmic_rffreq_get(rf_id);

       xorf_ctrl = &g_pmic_xoinfo.xorf_ctrl[rf_id];

       (void)pmu_print_dbg("%-10d%-20d0x%-20x0x%-20x\n",xorf_ctrl->rf_id,onoff,xorf_ctrl->freq_ctrl.freq_value,rffreq);
    }
}
void pmu_regulator_debug(void)
{
    struct regulator *regulator = NULL;
    u32 i = 0;
    struct pmic_volt_ctrl *volt_ctrl = NULL;
    struct dcdc_ctrl *dcdc_ctrl = NULL;
    unsigned int onoff,voltage = 0;

    (void)pmu_print_dbg("%-10s%-15s%-15s%-15s%-15s", "regu_id", "pmic_type", "volt_name","is_enabled","voltage(uV)");
    (void)pmu_print_dbg("%-10s%-20s\n", "gpio_num","consumer");

    /*lint -save -e413 */
    list_for_each_entry(regulator, &regulator_list, list)
    {
        if(strcmp(regulator->regulator_pmic_type, "pmic") == 0)
        {
            volt_ctrl = &g_pmic_voltinfo.volt_ctrl[regulator->id];
            onoff = !!pmic_volt_is_enabled((int)(regulator->id));
            voltage = pmic_volt_get_voltage((int)(regulator->id));

            (void)pmu_print_dbg("%-10d%-15s%-15s%-15d%-15d", regulator->id,regulator->regulator_pmic_type,\
                volt_ctrl->name,onoff,voltage);
            (void)pmu_print_dbg("%-10s","NULL");
        }

        else if(strcmp(regulator->regulator_pmic_type, "dcdc") == 0)
        {
            dcdc_ctrl = &g_pmu_exdcdc.dc_ctrl[regulator->id];
            onoff = dcdc_volt_is_enabled((int)(regulator->id));

            (void)pmu_print_dbg("%-10d%-15s%-15s%-15d%-15s", regulator->id,regulator->regulator_pmic_type,\
                dcdc_ctrl->name,onoff,"ctrlbypdm");
            (void)pmu_print_dbg("%-10d",dcdc_ctrl->gpio_id);
        }

        /*print consumers*/
        for (i = 0; i < regulator->num_consumer_supplies; i++)
        {
            (void)pmu_print_dbg("%s,", regulator->consumer_supplies[i].supply);
        }
        (void)pmu_print_dbg("\n");

    }
    /*lint -restore */
}
void pmic_get_shm_mem_debug(void)
{
    (void)pmu_print_dbg("shm_mem_pmu_npreg_addr:0x%x\n", SHM_MEM_PMU_NPREG_ADDR);
}
void pmu_help(void)
{
    (void)pmu_print_dbg("pmic_volt_enable(volt_id)                               :enable volt\n");
    (void)pmu_print_dbg("pmic_volt_disable(volt_id)                              :disable volt\n");
    (void)pmu_print_dbg("pmic_volt_is_enabled(volt_id)                           :show volt state\n");
    (void)pmu_print_dbg("pmic_volt_get_voltage(volt_id)                          :get volt voltage\n");
    (void)pmu_print_dbg("pmic_volt_set_debug(volt_id,voltage)             :set volt voltage\n");
    (void)pmu_print_dbg("pmic_volt_list_show(volt_id)                            :show volt all voltage\n");
    (void)pmu_print_dbg("pmic_addr_debug          :show addr info\n");
    (void)pmu_print_dbg("pmic_voltage_table_debug :show voltage table\n");
    (void)pmu_print_dbg("pmic_volt_id_debug       :show id name\n");
    (void)pmu_print_dbg("pmic_volt_state_debug    :show onoff voltage info\n");
    (void)pmu_print_dbg("dcdc_state_debug         :show exdcdc state and info\n");
    (void)pmu_print_dbg("pmu_regulator_debug      :show power all relationship\n");
    (void)pmu_print_dbg("pmic_xo_state_debug      :show xo c1c2 and rfclk state\n");
    (void)pmu_print_dbg("pmic_xo_reg_debug        :show xo c1c2 and rfclk reg info\n");
    (void)pmu_print_dbg("pmu_modem_init_debug     :init modem volt\n");
    (void)pmu_print_dbg("pmic_get_shm_mem_debug    :show shm mem addr");
}

