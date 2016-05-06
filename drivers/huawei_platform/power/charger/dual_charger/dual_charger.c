#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <huawei_platform/log/hw_log.h>
#include <huawei_platform/power/huawei_charger.h>
#include <dual_charger.h>
#include <linux/power/hisi/coul/hisi_coul_drv.h>

#define HWLOG_TAG dual_charger
HWLOG_REGIST();

#define IF_OPS(ops, op)  if(ops && ops->op)

struct dual_charger_info *dci = NULL;
struct charge_device_ops *g_main_ops = NULL;
struct charge_device_ops *g_aux_ops = NULL;

extern int bq25892_main_get_ichg_reg(void);
extern int bq25892_aux_get_ichg_reg(void);
extern int bq25892_main_get_ichg_adc(void);
extern int bq25892_aux_get_ichg_adc(void);

/**********************************************************
*  Function:     charge_main_ops_register
*  Discription:  register charger operation, this function
*                should be called by main charger driver
*  Parameters:   ops
*  return value:  0-sucess or others-fail
**********************************************************/
int charge_main_ops_register(struct charge_device_ops *ops)
{
    int ret = 0;

    if(ops != NULL)
    {
        g_main_ops = ops;
    }
    else
    {
        ret = -EPERM;
    }
    return ret;
}
/**********************************************************
*  Function:     charge_aux_ops_register
*  Discription:  register charger operation, this function
*                should be called by aux charger driver
*  Parameters:   ops
*  return value:  0-sucess or others-fail
**********************************************************/
int charge_aux_ops_register(struct charge_device_ops *ops)
{
    int ret = 0;

    if(ops != NULL)
    {
        g_aux_ops = ops;
    }
    else
    {
        ret = -EPERM;
    }
    return ret;
}
/**********************************************************
*  Function:       dual_charger_fcp_chip_init
*  Discription:    dual charger initialization
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_chip_init(void)
{
    int ret = 0;
    IF_OPS(g_main_ops, chip_init)
        ret |= g_main_ops->chip_init();
    IF_OPS(g_aux_ops, chip_init)
        ret |= g_aux_ops->chip_init();
    return ret;
}
/**********************************************************
*  Function:       dual_charger_fcp_chip_init
*  Discription:    dual charger initialization for high voltage adapter
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_fcp_chip_init(void)
{
    int ret = 0;
    IF_OPS(g_main_ops, fcp_chip_init)
        ret |= g_main_ops->fcp_chip_init();
    IF_OPS(g_aux_ops, fcp_chip_init)
        ret |= g_aux_ops->fcp_chip_init();
    return ret;
}
/**********************************************************
*  Function:       dual_charger_device_check
*  Discription:    check chip i2c communication
*  Parameters:   null
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_device_check(void)
{
    int ret1 = CHARGE_IC_BAD;
    int ret2 = CHARGE_IC_BAD;

    IF_OPS(g_main_ops, dev_check)
        ret1 = g_main_ops->dev_check();
    IF_OPS(g_aux_ops, dev_check)
        ret2 = g_aux_ops->dev_check();

    if((CHARGE_IC_GOOD == ret1) && (CHARGE_IC_GOOD == ret2))
    {
        hwlog_info("dual_charger is  good!\n");
        return CHARGE_IC_GOOD;
    }
    else
    {
        hwlog_err("dual_charger is bad!\n");
        return CHARGE_IC_BAD;
    }
}
/**********************************************************
*  Function:       dual_charger_set_input_current_thermal
*  Discription:    record the input current by thermal limit in charging process
*  Parameters:   main--main charger  aux--aux charger
*  return value:  null
**********************************************************/
static void dual_charger_set_input_current_thermal(int main, int aux)
{
    dci->iin_thermal_main = main;
    dci->iin_thermal_aux = aux;
}
/**********************************************************
*  Function:       dual_charger_set_charge_current_thermal
*  Discription:    record the charge current by thermal limit in charging process
*  Parameters:   main--main charger  aux--aux charger
*  return value:  null
**********************************************************/
static void dual_charger_set_charge_current_thermal(int main, int aux)
{
    dci->ichg_thermal_main = main;
    dci->ichg_thermal_aux = aux;
}
/**********************************************************
*  Function:       dual_charger_select_input_current_by_thermal_limit
*  Discription:    select the input current by thermal limit in charging process
*  Parameters:   iin:input current value
*  return value:  null
**********************************************************/
static void dual_charger_select_input_current_by_thermal_limit(int iin)
{
    if((dci->iin_max_each_charger <= dci->iin_thermal_main && dci->iin_max_each_charger <= dci->iin_thermal_aux)
    ||(iin <= dci->iin_thermal_main && iin <= dci->iin_thermal_aux))
    {
        dci->input_current_main = iin/2;
        dci->input_current_aux = iin/2;
    }
    else
    {
        if(dci->iin_thermal_main < dci->iin_thermal_aux)
        {
            dci->input_current_main = dci->iin_thermal_main;
            dci->input_current_aux = iin - dci->iin_thermal_main;
        }
        else
        {
            dci->input_current_main = iin - dci->iin_thermal_aux;
            dci->input_current_aux = dci->iin_thermal_aux;
        }
    }
}
/**********************************************************
*  Function:       dual_charger_select_charge_current_by_thermal_limit
*  Discription:    select the charge current by thermal limit in charging process
*  Parameters:   ichg:charge current value
*  return value:  null
**********************************************************/
static void dual_charger_select_charge_current_by_thermal_limit(int ichg)
{
    if(ichg <= dci->ichg_thermal_main && ichg <= dci->ichg_thermal_aux)
    {
        dci->charge_current_main = ichg/2;
        dci->charge_current_aux = ichg/2;
    }
    else
    {
        if(dci->ichg_thermal_main < dci->ichg_thermal_aux)
        {
            dci->charge_current_main = dci->ichg_thermal_main;
            dci->charge_current_aux = ichg - dci->ichg_thermal_main;
        }
        else
        {
            dci->charge_current_main = ichg - dci->ichg_thermal_aux;
            dci->charge_current_aux = dci->ichg_thermal_aux;
        }
    }
}
/**********************************************************
*  Function:       dual_charger_select_input_current
*  Discription:    select the input current in charging process
*  Parameters:   iin:input current value
*  return value:  null
**********************************************************/
static void dual_charger_select_input_current(int iin)
{
    if(TRUE == dci->charge_done)
    {
        dci->input_current_main = iin;
        dci->input_current_aux = 0;
        return;
    }

    if(dci->ichg < dci->ichg_need_aux_charger)   //don't need aux charger
    {
        dci->input_current_main = iin;
        dci->input_current_aux = 0;
    }
    else
    {
        dual_charger_select_input_current_by_thermal_limit(iin);
    }

    dci->input_current_main = dci->input_current_main < dci->iin_max_each_charger ? dci->input_current_main : dci->iin_max_each_charger;
    dci->input_current_aux = dci->input_current_aux < dci->iin_max_each_charger ? dci->input_current_aux : dci->iin_max_each_charger;
}
/**********************************************************
*  Function:       dual_charger_select_charge_current
*  Discription:    select the charge current in charging process
*  Parameters:   ichg:charge current value
*  return value:  null
**********************************************************/
static void dual_charger_select_charge_current(int ichg)
{
    if(dci->ichg < dci->ichg_need_aux_charger)   //don't need aux charger
    {
        dci->charge_current_main = ichg;
        dci->charge_current_aux = 0;
    }
    else
    {
        dual_charger_select_charge_current_by_thermal_limit(ichg);
    }

    if(TRUE == dci->charge_done)
        dci->charge_current_aux = 0;
}
/**********************************************************
*  Function:       dual_charger_set_input_current
*  Discription:    set the input current in charging process
*  Parameters:   iin:input current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_input_current(int iin)
{
    int ret = 0;
    hwlog_debug("dual charger set input current %d.\n", iin);
    dual_charger_select_input_current(iin);

    IF_OPS(g_main_ops, set_input_current)
        ret |= g_main_ops->set_input_current(dci->input_current_main);
    IF_OPS(g_aux_ops, set_input_current)
        ret |= g_aux_ops->set_input_current(dci->input_current_aux);
    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_charge_current
*  Discription:    set the charge current in charging process
*  Parameters:   ichg:charge current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_charge_current(int ichg)
{
    int ret = 0;

    hwlog_debug("dual charger set charge current %d.\n", ichg);
    dci->ichg = ichg;
    dual_charger_select_charge_current(ichg);

    if(CHARGE_CURRENT_0000_MA == dci->charge_current_main)
        dci->charge_enable_main = FALSE;
    if(CHARGE_CURRENT_0000_MA == dci->charge_current_aux)
        dci->charge_enable_aux = FALSE;

    IF_OPS(g_main_ops, set_charge_current)
        ret |= g_main_ops->set_charge_current(dci->charge_current_main);
    IF_OPS(g_aux_ops, set_charge_current)
        ret |= g_aux_ops->set_charge_current(dci->charge_current_aux);

    return ret;
}
/****************************************************************
*  Function:       dual_charger_get_ichg_reg
*  Discription:    get limited charge current in charging process
*  Parameters:   1:main charger  0:aux charger
*  return value:  limited charge current
*****************************************************************/
static int dual_charger_get_ichg_reg(int flag)
{
    if(MAIN_CHARGER == flag)
    {
        return bq25892_main_get_ichg_reg();
    }
    else if(AUX_CHARGER == flag)
    {
        return bq25892_aux_get_ichg_reg();
    }
    else
    {
        hwlog_err("dual charger get ichg reg: para error.");
        return 0;
    }
}
/****************************************************************
*  Function:       dual_charger_get_ichg_adc
*  Discription:    get charge current from the included ADC in charging process
*  Parameters:   1:main charger  0:aux charger
*  return value:  charge current from the included ADC
*****************************************************************/
static int dual_charger_get_ichg_adc(int flag)
{
    if(MAIN_CHARGER == flag)
    {
        return bq25892_main_get_ichg_adc();
    }
    else if(AUX_CHARGER == flag)
    {
        return bq25892_aux_get_ichg_adc();
    }
    else
    {
        hwlog_err("dual charger get ichg adc: para error.");
        return 0;
    }
}
/**********************************************************
*  Function:       dual_charger_set_terminal_voltage
*  Discription:    set the terminal voltage in charging process
*  Parameters:   value:terminal voltage value
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_terminal_voltage(int value)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_terminal_voltage)
        ret |= g_main_ops->set_terminal_voltage(value);
    IF_OPS(g_aux_ops, set_terminal_voltage)
        ret |= g_aux_ops->set_terminal_voltage(value);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_dpm_voltage
*  Discription:    set the dpm voltage in charging process
*  Parameters:   value:dpm voltage value
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_dpm_voltage(int value)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_dpm_voltage)
        ret |= g_main_ops->set_dpm_voltage(value);
    IF_OPS(g_aux_ops, set_dpm_voltage)
        ret |= g_aux_ops->set_dpm_voltage(value);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_terminal_current
*  Discription:    set the terminal current in charging process
*  Parameters:   value:terminal current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_terminal_current(int value)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_terminal_current)
        ret |= g_main_ops->set_terminal_current(value);
    IF_OPS(g_aux_ops, set_terminal_current)
        ret |= g_aux_ops->set_terminal_current(value);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_charge_enable
*  Discription:    set the charge enable in charging process
*  Parameters:   enable:charge enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_charge_enable(int enable)
{
    int ret = 0;
    dci->charge_enable_main = enable;
    if(dci->ichg >= dci->ichg_need_aux_charger)
        dci->charge_enable_aux = enable;
    else
        dci->charge_enable_aux = FALSE;

    IF_OPS(g_main_ops, set_charge_enable)
        ret |= g_main_ops->set_charge_enable(dci->charge_enable_main & dci->charge_enable_sysfs_main);
    IF_OPS(g_aux_ops, set_charge_enable)
        ret |= g_aux_ops->set_charge_enable(dci->charge_enable_aux & dci->charge_enable_sysfs_aux);
    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_otg_enable
*  Discription:    set the otg mode enable in charging process
*  Parameters:   enable:otg mode  enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_otg_enable(int enable)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_otg_enable)
        ret |= g_main_ops->set_otg_enable(enable);
    IF_OPS(g_aux_ops, set_otg_enable)
        ret |= g_aux_ops->set_otg_enable(FALSE);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_term_enable
*  Discription:    set the terminal enable in charging process
*  Parameters:   enable:terminal enable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_term_enable(int enable)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_term_enable)
        ret |= g_main_ops->set_term_enable(enable);
    IF_OPS(g_aux_ops, set_term_enable)
        ret |= g_aux_ops->set_term_enable(enable);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_get_charge_state
*  Discription:    get the charge states in charging process
*  Parameters:   state:charge states
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_get_charge_state(unsigned int *state)
{
    int ret = 0;
    *state |= CHAGRE_STATE_CHRG_DONE;

    IF_OPS(g_main_ops, get_charge_state)
        ret |= g_main_ops->get_charge_state(state);
    IF_OPS(g_aux_ops, get_charge_state)
        ret |= g_aux_ops->get_charge_state(state);

    if(! (dci->charge_enable_main & dci->charge_enable_sysfs_main) &&
       !(dci->charge_enable_aux & dci->charge_enable_sysfs_aux))
    {
        *state &= ~CHAGRE_STATE_CHRG_DONE;
    }

    if(*state & CHAGRE_STATE_CHRG_DONE)
        dci->charge_done = TRUE;
    else
        dci->charge_done = FALSE;

    return ret;
}
/**********************************************************
*  Function:       dual_charger_reset_watchdog_timer
*  Discription:    reset watchdog timer in charging process
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_reset_watchdog_timer(void)
{
    int ret = 0;

    IF_OPS(g_main_ops, reset_watchdog_timer)
        ret |= g_main_ops->reset_watchdog_timer();
    IF_OPS(g_aux_ops, reset_watchdog_timer)
        ret |= g_aux_ops->reset_watchdog_timer();

    return ret;
}
/**********************************************************
*  Function:       dual_charger_dump_register
*  Discription:    print the register value in charging process
*  Parameters:   reg_value:string for save register value
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_dump_register(char *reg_value)
{
    int ret = 0;

    IF_OPS(g_main_ops, dump_register)
        ret |= g_main_ops->dump_register(reg_value);
    IF_OPS(g_aux_ops, dump_register)
        ret |= g_aux_ops->dump_register(reg_value);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_get_register_head
*  Discription:    print the register head in charging process
*  Parameters:   reg_head:string for save register head
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_get_register_head(char *reg_head)
{
    int ret = 0;

    IF_OPS(g_main_ops, get_register_head)
        ret |= g_main_ops->get_register_head(reg_head);
    IF_OPS(g_aux_ops, get_register_head)
        ret |= g_aux_ops->get_register_head(reg_head);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_watchdog_timer
*  Discription:    set the watchdog timer in charging process
*  Parameters:   value:watchdog timer value
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_watchdog_timer(int value)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_watchdog_timer)
        ret |= g_main_ops->set_watchdog_timer(value);
    IF_OPS(g_aux_ops, set_watchdog_timer)
        ret |= g_aux_ops->set_watchdog_timer(value);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_batfet_disable
*  Discription:    set the batfet disable in charging process
*  Parameters:   disable:batfet disable or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_batfet_disable(int disable)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_batfet_disable)
        ret |= g_main_ops->set_batfet_disable(disable);
    IF_OPS(g_aux_ops, set_batfet_disable)
        ret |= g_aux_ops->set_batfet_disable(disable);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_get_ilim
*  Discription:    get average value for ibus
*  Parameters:     NULL
*  return value:   average value for ibus
**********************************************************/
static int dual_charger_get_ilim(void)
{
    int ret = 0;

    IF_OPS(g_main_ops, get_ibus)
        ret += g_main_ops->get_ibus();
    IF_OPS(g_aux_ops, get_ibus)
        ret += g_aux_ops->get_ibus();

    return ret;
}
/**********************************************************
*  Function:       dual_charger_get_vbus_mv
*  Discription:    get voltage of vbus
*  Parameters:   vbus_mv:voltage of vbus
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_get_vbus_mv(unsigned int *vbus_mv)
{
    int ret = 0;

    IF_OPS(g_main_ops, get_vbus)
        ret = g_main_ops->get_vbus(vbus_mv);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_get_vbat_sys
*  Discription:    get average value for vsys voltage
*  Parameters:   null
*  return value:  vsys voltage
**********************************************************/
static int dual_charger_get_vbat_sys(void)
{
    int ret = 0;

    IF_OPS(g_main_ops, get_vbat_sys)
        ret = g_main_ops->get_vbat_sys();

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_covn_start
*  Discription:    set covn start
*  Parameters:   value: 1(enable) or 0(disable)
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_covn_start(int enable)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_covn_start)
        ret |= g_main_ops->set_covn_start(enable);
    IF_OPS(g_aux_ops, set_covn_start)
        ret |= g_aux_ops->set_covn_start(enable);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_charger_hiz
*  Discription:    set the charger hiz close watchdog
*  Parameters:   enable:charger in hiz or not
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_charger_hiz(int enable)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_charger_hiz)
        ret |= g_main_ops->set_charger_hiz(enable);
    IF_OPS(g_aux_ops, set_charger_hiz)
        ret |= g_aux_ops->set_charger_hiz(enable);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_check_input_dpm_state
*  Discription:    check whether VINDPM or IINDPM
*  Parameters:     NULL
*  return value:   TRUE means VINDPM or IINDPM
*                  FALSE means NoT DPM
**********************************************************/
static int dual_charger_check_input_dpm_state(void)
{
    int ret = 0;

    IF_OPS(g_main_ops, check_input_dpm_state)
        ret |= g_main_ops->check_input_dpm_state();
    IF_OPS(g_aux_ops, check_input_dpm_state)
        ret |= g_aux_ops->check_input_dpm_state();

    return ret;
}
/**********************************************************
*  Function:       dual_charger_set_otg_current
*  Discription:    set the otg mdoe current
*  Parameters:     value :current value
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_set_otg_current(int value)
{
    int ret = 0;

    IF_OPS(g_main_ops, set_otg_current)
        ret = g_main_ops->set_otg_current(value);

    return ret;
}
/**********************************************************
*  Function:       dual_charger_stop_charge_config
*  Discription:    config chip after stop charging
*  Parameters:     NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_stop_charge_config(void)
{
    int ret = 0;
    dci->ichg = dci->ichg_max;
    dci->charge_enable_sysfs_main = TRUE;
    dci->charge_enable_sysfs_aux = TRUE;

    IF_OPS(g_main_ops, stop_charge_config)
        ret |= g_main_ops->stop_charge_config();
    IF_OPS(g_aux_ops, stop_charge_config)
        ret |= g_aux_ops->stop_charge_config();

    return ret;
}
struct charge_device_ops dual_charger_ops =
{
    .chip_init = dual_charger_chip_init,
    .fcp_chip_init = dual_charger_fcp_chip_init,
    .dev_check = dual_charger_device_check,
    .set_input_current = dual_charger_set_input_current,
    .set_charge_current = dual_charger_set_charge_current,
    .set_input_current_thermal = dual_charger_set_input_current_thermal,
    .set_charge_current_thermal = dual_charger_set_charge_current_thermal,
    .get_ichg_reg = dual_charger_get_ichg_reg,
    .get_ichg_adc = dual_charger_get_ichg_adc,
    .set_terminal_voltage = dual_charger_set_terminal_voltage,
    .set_dpm_voltage = dual_charger_set_dpm_voltage,
    .set_terminal_current = dual_charger_set_terminal_current,
    .set_charge_enable = dual_charger_set_charge_enable,
    .set_otg_enable = dual_charger_set_otg_enable,
    .set_term_enable = dual_charger_set_term_enable,
    .get_charge_state = dual_charger_get_charge_state,
    .reset_watchdog_timer = dual_charger_reset_watchdog_timer,
    .dump_register = dual_charger_dump_register,
    .get_register_head = dual_charger_get_register_head,
    .set_watchdog_timer = dual_charger_set_watchdog_timer,
    .set_batfet_disable = dual_charger_set_batfet_disable,
    .get_ibus = dual_charger_get_ilim,
    .get_vbus = dual_charger_get_vbus_mv,
    .get_vbat_sys = dual_charger_get_vbat_sys,
    .set_covn_start = dual_charger_set_covn_start,
    .set_charger_hiz = dual_charger_set_charger_hiz,
    .check_input_dpm_state = dual_charger_check_input_dpm_state,
    .set_otg_current = dual_charger_set_otg_current,
    .stop_charge_config = dual_charger_stop_charge_config,
};

#if CONFIG_SYSFS
#define DUAL_CHARGER_SYSFS_FIELD(_name, n, m, store)                \
{                                                   \
    .attr = __ATTR(_name, m, dual_charger_sysfs_show, store),    \
    .name = DUAL_CHARGER_SYSFS_##n,          \
}

#define DUAL_CHARGER_SYSFS_FIELD_RW(_name, n)               \
        DUAL_CHARGER_SYSFS_FIELD(_name, n, S_IWUSR | S_IRUGO,       \
                dual_charger_sysfs_store)

#define DUAL_CHARGER_SYSFS_FIELD_RO(_name, n)               \
        DUAL_CHARGER_SYSFS_FIELD(_name, n, S_IRUGO, NULL)

static ssize_t dual_charger_sysfs_show(struct device *dev,
        struct device_attribute *attr, char *buf);
static ssize_t dual_charger_sysfs_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t count);

struct dual_charger_sysfs_field_info {
    struct device_attribute attr;
    u8 name;
};

static struct dual_charger_sysfs_field_info dual_charger_sysfs_field_tbl[] = {
    DUAL_CHARGER_SYSFS_FIELD_RW(enable_charger_main,    ENABLE_CHARGER_MAIN),
    DUAL_CHARGER_SYSFS_FIELD_RW(enable_charger_aux,    ENABLE_CHARGER_AUX),
};

static struct attribute *dual_charger_sysfs_attrs[ARRAY_SIZE(dual_charger_sysfs_field_tbl) + 1];

static const struct attribute_group dual_charger_sysfs_attr_group = {
    .attrs = dual_charger_sysfs_attrs,
};
static void dual_charger_sysfs_init_attrs(void)
{
    int i, limit = ARRAY_SIZE(dual_charger_sysfs_field_tbl);

    for (i = 0; i < limit; i++)
    {
        dual_charger_sysfs_attrs[i] = &dual_charger_sysfs_field_tbl[i].attr.attr;
    }
    dual_charger_sysfs_attrs[limit] = NULL;
}
static struct dual_charger_sysfs_field_info *dual_charger_sysfs_field_lookup(const char *name)
{
    int i, limit = ARRAY_SIZE(dual_charger_sysfs_field_tbl);

    for (i = 0; i < limit; i++)
    {
        if (!strncmp(name, dual_charger_sysfs_field_tbl[i].attr.attr.name,strlen(name)))
            break;
    }
    if (i >= limit)
        return NULL;

    return &dual_charger_sysfs_field_tbl[i];
}
static ssize_t dual_charger_sysfs_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    struct dual_charger_sysfs_field_info *info = NULL;
    int ret;

    info = dual_charger_sysfs_field_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;

    switch(info->name){
    case DUAL_CHARGER_SYSFS_ENABLE_CHARGER_MAIN:
        return snprintf(buf,PAGE_SIZE, "%d\n", dci->charge_enable_main & dci->charge_enable_sysfs_main);
    case DUAL_CHARGER_SYSFS_ENABLE_CHARGER_AUX:
        return snprintf(buf,PAGE_SIZE, "%d\n", dci->charge_enable_aux & dci->charge_enable_sysfs_aux);
    }
    return 0;
}
static ssize_t dual_charger_sysfs_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t count)
{
    struct dual_charger_sysfs_field_info *info = NULL;
    int ret;
    long val = 0;

    info = dual_charger_sysfs_field_lookup(attr->attr.name);
    if (!info)
        return -EINVAL;

    switch(info->name){
    case DUAL_CHARGER_SYSFS_ENABLE_CHARGER_MAIN:
        if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
            return -EINVAL;
        dci->charge_enable_sysfs_main = val;
        hwlog_info("RUNNINGTEST set charge enable main = %d\n", dci->charge_enable_sysfs_main);

        g_main_ops->set_charge_enable(dci->charge_enable_main & dci->charge_enable_sysfs_main);
        break;
    case DUAL_CHARGER_SYSFS_ENABLE_CHARGER_AUX:
        if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
            return -EINVAL;
        dci->charge_enable_sysfs_aux = val;
        hwlog_info("RUNNINGTEST set charge enable aux = %d\n", dci->charge_enable_sysfs_aux);

        g_aux_ops->set_charge_enable(dci->charge_enable_main & dci->charge_enable_sysfs_main);
        break;
    }

    return count;
}
static int dual_charger_sysfs_create_group(void)
{
    dual_charger_sysfs_init_attrs();
    return sysfs_create_group(&dci->dev->kobj, &dual_charger_sysfs_attr_group);
}
static inline void dual_charger_sysfs_remove_group(void)
{
    sysfs_remove_group(&dci->dev->kobj, &dual_charger_sysfs_attr_group);
}
#else
static int charge_sysfs_create_group(void)
{
    return 0;
}
static inline void charge_sysfs_remove_group(void) {}
#endif
/**********************************************************
*  Function:       dual_charger_parse_dts
*  Discription:    parse the module dts config value
*  Parameters:   null
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_parse_dts(void)
{
    int ret;

    ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,dual_charger"), \
            "iin_max_each_charger", &dci->iin_max_each_charger);
    if (ret)
    {
        hwlog_err("get iin_max_each_charger fail, use default one!\n");
        dci->iin_max_each_charger = DEFAULT_IIN_MAX_EACH_CHARGER;
    }

    ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,dual_charger"),\
            "ichg_need_aux_charger", &dci->ichg_need_aux_charger);
    if (ret)
    {
        hwlog_err("get ichg_need_aux_charger fail, use default one!\n");
        dci->ichg_need_aux_charger = DEFAULT_ICHG_NEED_AUX_CHARGER;
    }

    ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,charging_core"),\
            "ichg_fcp", &dci->ichg_max);
    if (ret)
    {
        hwlog_err("get ichg_max fail, use default one!\n");
        dci->ichg_max = DEFAULT_ICHG_MAX;
    }

    return ret;
}
/**********************************************************
*  Function:       dual_charger_probe
*  Discription:    dual_charger module probe
*  Parameters:   device:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int dual_charger_probe(struct platform_device *pdev)
{
    int ret;
    struct class *power_class = NULL;

    dci = kzalloc(sizeof(*dci), GFP_KERNEL);
    if (NULL == dci)
    {
        hwlog_err("alloc dual_charger_info failed\n");
        ret = -ENOMEM;
        return ret;
    }
    dci->dev = &pdev->dev;

    dual_charger_parse_dts();

    dci->iin_thermal_main = dci->iin_max_each_charger;
    dci->iin_thermal_aux = dci->iin_max_each_charger;
    dci->ichg_thermal_main = dci->ichg_max;
    dci->ichg_thermal_aux = dci->ichg_max;
    dci->ichg = dci->ichg_max;

    dci->charge_enable_main = TRUE;
    dci->charge_enable_aux = TRUE;
    dci->charge_enable_sysfs_main = TRUE;
    dci->charge_enable_sysfs_aux = TRUE;
    dci->charge_done = FALSE;

    ret = charge_ops_register(&dual_charger_ops);
    if(ret)
    {
        hwlog_err("register dual charge ops failed!\n");
        goto dual_charger_fail_0;
    }

    if((NULL == g_main_ops) || (NULL == g_main_ops->chip_init) || (NULL == g_main_ops->dev_check)
        || (NULL == g_main_ops->set_input_current) ||(NULL == g_main_ops->set_charge_current)
        || (NULL == g_main_ops->set_terminal_voltage) || (NULL == g_main_ops->set_dpm_voltage)
        || (NULL == g_main_ops->set_terminal_current) || (NULL == g_main_ops->set_charge_enable)
        || (NULL == g_main_ops->set_otg_enable)  || (NULL == g_main_ops->set_term_enable)
        || (NULL == g_main_ops->get_charge_state) || (NULL == g_main_ops->reset_watchdog_timer)
        || (NULL == g_main_ops->dump_register) || (NULL == g_main_ops->get_register_head)
        || (NULL == g_main_ops->set_watchdog_timer) || (NULL == g_main_ops->set_batfet_disable)
        || (NULL == g_main_ops->get_ibus) || (NULL == g_main_ops->get_vbus) || (NULL == g_main_ops->get_vbat_sys)
        || (NULL == g_main_ops->set_covn_start) || (NULL == g_main_ops->set_charger_hiz)
        || (NULL == g_main_ops->check_input_dpm_state) || (NULL == g_main_ops->set_otg_current)
        || (NULL == g_main_ops->stop_charge_config))
    {
        hwlog_err("main charge ops is NULL!\n");
        ret = -EINVAL;
        goto dual_charger_fail_1;
    }
    if((NULL == g_aux_ops) || (NULL == g_aux_ops->chip_init) || (NULL == g_aux_ops->dev_check)
        || (NULL == g_aux_ops->set_input_current) ||(NULL == g_aux_ops->set_charge_current)
        || (NULL == g_aux_ops->set_terminal_voltage) || (NULL == g_aux_ops->set_dpm_voltage)
        || (NULL == g_aux_ops->set_terminal_current) || (NULL == g_aux_ops->set_charge_enable)
        || (NULL == g_aux_ops->set_otg_enable)  || (NULL == g_aux_ops->set_term_enable)
        || (NULL == g_aux_ops->get_charge_state) || (NULL == g_aux_ops->reset_watchdog_timer)
        || (NULL == g_aux_ops->dump_register) || (NULL == g_aux_ops->get_register_head)
        || (NULL == g_aux_ops->set_watchdog_timer) || (NULL == g_aux_ops->set_batfet_disable)
        || (NULL == g_aux_ops->get_ibus) || (NULL == g_aux_ops->set_covn_start) || (NULL == g_aux_ops->set_charger_hiz)
        || (NULL == g_aux_ops->check_input_dpm_state) || (NULL == g_aux_ops->stop_charge_config))
    {
        hwlog_err("aux charge ops is NULL!\n");
        ret = -EINVAL;
        goto dual_charger_fail_2;
    }
    ret = dual_charger_sysfs_create_group();
    if (ret)
        hwlog_err("can't create dual charger sysfs entries\n");
    power_class = hw_power_get_class();
    if(power_class)
    {
        if(charge_dev == NULL)
            charge_dev = device_create(power_class, NULL, 0, NULL,"charger");
        ret = sysfs_create_link(&charge_dev->kobj, &dci->dev->kobj, "dual_charger");
        if(ret)
        {
            hwlog_err("create link to dual_charger fail.\n");
            goto dual_charger_fail_3;
        }
    }

    hwlog_info("dual charger probe ok!\n");
    return ret;

dual_charger_fail_3:
    dual_charger_sysfs_remove_group();
dual_charger_fail_2:
    g_aux_ops = NULL;
dual_charger_fail_1:
    g_main_ops = NULL;
dual_charger_fail_0:
    kfree(dci);
    dci = NULL;
    return ret;
}
static int dual_charger_remove(struct i2c_client *client)
{
    return 0;
}

#ifdef CONFIG_LLT_TEST
struct dual_charger_static_ops llt_dual_charger_ops = {
    .select_input_current = dual_charger_select_input_current,
    .select_charge_current = dual_charger_select_charge_current,
    .set_charge_enable = dual_charger_set_charge_enable,
};
#endif

static struct of_device_id dual_charger_match_table[] =
{
    {
        .compatible = "huawei,dual_charger",
        .data = NULL,
    },
    {
    },
};
static struct platform_driver dual_charger_driver =
{
    .probe        = dual_charger_probe,
    .remove       = dual_charger_remove,
    .driver       =
    {
        .name           = "huawei,dual_charger",
        .owner          = THIS_MODULE,
        .of_match_table = of_match_ptr(dual_charger_match_table),
    },
};
/**********************************************************
*  Function:       dual_charger_init
*  Discription:    dual_charger initialization
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
int __init dual_charger_init(void)
{
    return (platform_driver_register(&dual_charger_driver));
}
/**********************************************************
*  Function:       dual_charger_exit
*  Discription:    dual_charger exit
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
void __exit dual_charger_exit(void)
{
    platform_driver_unregister(&dual_charger_driver);
}
module_init(dual_charger_init);
module_exit(dual_charger_exit);
MODULE_AUTHOR("HUAWEI");
MODULE_DESCRIPTION("dual_charger module driver");
MODULE_LICENSE("GPL");
