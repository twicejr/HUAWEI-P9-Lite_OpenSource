#include <product_config.h>
#include <osl_bio.h>
#include <osl_spinlock.h>
#include <osl_thread.h>
#include <of.h>
#include <soc_memmap.h>
#include <bsp_gpio.h>
#include <bsp_regulator.h>
#include <pmu_balong.h>
#include <hi_pmu.h>
#include <pmu_pmic.h>
#include <bsp_version.h>

struct dcdc_info g_pmu_exdcdc = 
{
	.dc_num = 0,
	.dc_ctrl = NULL,
};

static inline int dcdc_para_check(int dc_id)
{
    /* 有效性检查 */
    if((dc_id < 0)||(dc_id >= (int)g_pmu_exdcdc.dc_num))
    {
        pmu_print_error("doesn't have dcdc %d!\n",dc_id);
        return BSP_PMU_ERROR;
    }
    return BSP_PMU_OK;
}
int dcdc_volt_enable(int dc_id)
{
    int ret = BSP_PMU_OK;

    /*check para*/
    if(dcdc_para_check(dc_id))
        ret = BSP_PMU_ERROR;
    else
        bsp_gpio_direction_output(g_pmu_exdcdc.dc_ctrl[dc_id].gpio_id,1);

    return ret;
}
int dcdc_volt_disable(int dc_id)
{
    int ret = BSP_PMU_OK;

    /*check para*/
    if(dcdc_para_check(dc_id))
        ret = BSP_PMU_ERROR;
    else
        bsp_gpio_direction_output(g_pmu_exdcdc.dc_ctrl[dc_id].gpio_id,0);

    return ret;
}
int dcdc_volt_is_enabled(int dc_id)
{
    /*check para*/
    if(dcdc_para_check(dc_id))
        return BSP_ERROR;
    else
        return bsp_gpio_get_value(g_pmu_exdcdc.dc_ctrl[dc_id].gpio_id);
}
struct regulator_id_ops dcdc_volt_ops = {
        .is_enabled = dcdc_volt_is_enabled,
        .enable = dcdc_volt_enable,
        .disable = dcdc_volt_disable,
};
void pmu_dcdc_init(void)
{
    int ret = 0;
    u32 i     = 0;

    dcdc_dts_init();
    for(i = 0 ; i < g_pmu_exdcdc.dc_num ; i++){
        bsp_gpio_direction_output(g_pmu_exdcdc.dc_ctrl[i].gpio_id,0);
    }

    ret = regulator_pmic_ops_register(&dcdc_volt_ops, "dcdc");
    if(ret)
    {
        pmu_print_error("register regulator ops failed,err_id %d!",ret);
        return;
    }

    pmu_print_error("init ok!\n");

}
