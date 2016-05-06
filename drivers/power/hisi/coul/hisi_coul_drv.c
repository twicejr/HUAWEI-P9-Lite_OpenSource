/****************************************************************************
* Filename:	hisi_coul_drv.c
*
* Discription:  this file provide interface to get the battery state such as
*			capacity, voltage, current, temperature.
* Copyright:	(C) 2013 huawei.
*
* revision history:
* 03/25/13 yuanqinshun -v1.0
*****************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/power_supply.h>
#include <linux/power/hisi/coul/hisi_coul_drv.h>
#include <huawei_platform/log/hw_log.h>
#include <hisi_coul_drv_test.h>

#ifdef HWLOG_REGIST
#define HWLOG_TAG hisi_coul_drv
HWLOG_REGIST();
#else
#define hwlog_info(fmt, args...) do { printk(KERN_INFO     "[hisi_coul_drv]" fmt, ## args); } while (0)
#define hwlog_warn(fmt, args...) do { printk(KERN_WARNING "[hisi_coul_drv]" fmt, ## args); } while (0)
#define hwlog_err(fmt, args...)  do { printk(KERN_ERR    "[hisi_coul_drv]" fmt, ## args); } while (0)
#endif

#define HISI_COUL_LOCK()    do {} while (0)
#define HISI_COUL_UNLOCK()  do {} while (0)

static struct hisi_coul_ops *g_hisi_coul_ops;
static enum HISI_COULOMETER_TYPE g_hisi_coul_type = COUL_UNKNOW;
/*lint -e773*/
#define LOCAL_HISI_COUL_OPS() struct hisi_coul_ops *ops = g_hisi_coul_ops
/*lint +e773*/
#define HISI_EXEC_COUL_OP(op) do {if (ops && ops->op) return ops->op(); } while (0)

/****************************************************************************
  Function:     hisi_coulometer_type()
  Description:  get the hisi coulometer type
  Input:        NA
  Output:       NA
  Return:       enum HISI_COULOMETER_TYPE

****************************************************************************/
enum HISI_COULOMETER_TYPE hisi_coulometer_type(void)
{
	return g_hisi_coul_type;
}

/****************************************************************************
  Function:     is_hisi_coul_ready
  Description:  return the coul module state
  Input:        NA
  Output:       NA
  Return:       0:coul module isn't ready
			1:coul module is ready
****************************************************************************/
int is_hisi_coul_ready(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*make sure coul moudule have registered */
	if (g_hisi_coul_ops == NULL)
		return 0;

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(is_coul_ready);

	return 0;
}

/*******************************************************
  Function:        is_hisi_fcc_debounce
  Description:     check whether fcc is debounce
  Input:           NULL
  Output:          NULL
  Return:          0: no  1: is debounce
********************************************************/
int is_hisi_fcc_debounce(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(coul_is_fcc_debounce);
	return 0;

}

/*******************************************************
  Function:        hisi_coul_set_hltherm_flag
  Description:     set the flag for high or low temperature test
  Input:           temp_flag: 1 hltherm test
						0 no test
  Output:          NULL
  Return:          0: set success
				other: set fail
********************************************************/
int hisi_coul_set_hltherm_flag(int temp_flag)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	/*execute the operation of coul module */
	if (ops && ops->set_hltherm_flag)
		return ops->set_hltherm_flag(temp_flag);
	return 0;
}

/*******************************************************
  Function:        hisi_coul_get_hltherm_flag
  Description:     get the flag for high or low temperature test
  Input:           temp_flag: 1 hltherm test
						0 no test
  Output:          NULL
  Return:          1: set hltherm flag
			0: no set
********************************************************/
int hisi_coul_get_hltherm_flag(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(get_hltherm_flag);
	return 0;
}

/****************************************************************************
  Function:     is_hisi_battery_exist
  Description:  check whether battery is exist
  Input:        NA
  Output:       NA
  Return:       0:battery isn't exist
			1:battery is exist
****************************************************************************/
int is_hisi_battery_exist(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	if (NULL != g_hisi_coul_test_info) {
		if (g_hisi_coul_test_info->test_start_flag & 0x0001) {
			hwlog_info("hisi_battery exist status is %d\n", g_hisi_coul_test_info->input_batt_exist);
			return g_hisi_coul_test_info->input_batt_exist;
		}
	}
	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(is_battery_exist);

	return 0;
}

/****************************************************************************
  Function:     is_hisi_battery_reach_threshold
  Description:  check whether remaining capacity of battery reach the low
			power threshold
  Input:        NA
  Output:       NA
  Return:       0: no't reach the threshold
			1: reach the threshold
****************************************************************************/
int is_hisi_battery_reach_threshold(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(is_battery_reach_threshold);

	return 0;
}

/****************************************************************************
  Function:     hisi_battery_brand
  Description:  return the brand of battery
  Input:        NA
  Output:       NA
  Return:       the battery brand in string
			Or < 0 if something fails.
****************************************************************************/
char *hisi_battery_brand(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_brand);

	return "error";
}

/****************************************************************************
  Function:     hisi_battery_id_voltage
  Description:  return the voltage of battery id
  Input:        NA
  Output:       NA
  Return:       the battery id voltage
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_id_voltage(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_id_voltage);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_voltage
  Description:  return the voltage of battery
  Input:        NA
  Output:       NA
  Return:       the battery Voltage in milivolts
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_voltage(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	if (NULL != g_hisi_coul_test_info) {
		if (g_hisi_coul_test_info->test_start_flag & 0x0004) {
			hwlog_info("the battery voltage is %d\n", g_hisi_coul_test_info->input_batt_volt);
			return g_hisi_coul_test_info->input_batt_volt;
		}
	}
	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_voltage);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_voltage_uv
  Description:  return the voltage of battery
  Input:        NA
  Output:       NA
  Return:       the battery Voltage in microvolts
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_voltage_uv(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_voltage_uv);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_current
  Description:  return the current of battery
  Input:        NA
  Output:       NA
  Return:       the battery average current
			Note that current can be negative signed as well
			Or 0 if something fails.
****************************************************************************/
int hisi_battery_current(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	if (NULL != g_hisi_coul_test_info) {
		if (g_hisi_coul_test_info->test_start_flag & 0x0008) {
			hwlog_info("the input batt cur is %d\n", g_hisi_coul_test_info->input_batt_cur);
			return g_hisi_coul_test_info->input_batt_cur;
		}
	}
	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_current);

	return 0;
}

/****************************************************************************
  Function:     hisi_battery_current_avg
  Description:  return the current_avg of battery
  Input:        NA
  Output:       NA
  Return:       the battery average current
			Note that current can be negative signed as well
			Or 0 if something fails.
****************************************************************************/
int hisi_battery_current_avg(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_current_avg);

	return 0;
}

/****************************************************************************
  Function:     hisi_battery_unfiltered_capacity
  Description:  return the unfilted capacity of battery
  Input:        NA
  Output:       NA
  Return:       the battery Relative State-of-Charge
			The reture value is 0 - 100%
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_unfiltered_capacity(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_unfiltered_capacity);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_capacity
  Description:  return the capacity of battery
  Input:        NA
  Output:       NA
  Return:       the battery Relative State-of-Charge
			The reture value is 0 - 100%
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_capacity(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	if (NULL != g_hisi_coul_test_info) {
		if (g_hisi_coul_test_info->test_start_flag & 0x0010) {
			hwlog_info("input batt cap is %d\n", g_hisi_coul_test_info->input_batt_capacity);
			return g_hisi_coul_test_info->input_batt_capacity;
		}
	}
	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_capacity);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_temperature
  Description:  return the temperature of battery
  Input:        NA
  Output:       NA
  Return:       the battery temperature in Celcius degrees
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_temperature(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	if (NULL != g_hisi_coul_test_info) {
		if (g_hisi_coul_test_info->test_start_flag & 0x0020) {
			hwlog_info("input batt temp is %d\n", g_hisi_coul_test_info->input_batt_temp);
			return g_hisi_coul_test_info->input_batt_temp;
		}
	}
	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_temperature);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_rm
  Description:  return the RemainingCapacity of battery
  Input:        NA
  Output:       NA
  Return:       battery RemainingCapacity,the reture value is mAh
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_rm(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_rm);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_fcc
  Description:  return the FullChargeCapacity of battery
  Input:        NA
  Output:       NA
  Return:       battery FullChargeCapacity,the reture value is mAh
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_fcc(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	if (NULL != g_hisi_coul_test_info) {
		if (g_hisi_coul_test_info->test_start_flag & 0x0040) {
			hwlog_info("input batt fcc is %d\n", g_hisi_coul_test_info->input_batt_fcc);
			return g_hisi_coul_test_info->input_batt_fcc;
		}
	}
	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_fcc);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_fcc_design
  Description:  return the design FullChargeCapacity of battery in mAh
  Input:        NA
  Output:       NA
  Return:       battery FullChargeCapacity,the reture value is mAh
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_fcc_design(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_fcc_design);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_tte
  Description:  return the time to empty in minute
  Input:        NA
  Output:       NA
  Return:       time to empty in minute
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_tte(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_tte);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_ttf
  Description:  return the time to full in minute
  Input:        NA
  Output:       NA
  Return:       time to full in minute
			Or < 0 if something fails.
****************************************************************************/
int hisi_battery_ttf(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_ttf);

	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_health
  Description:  get the health state of battery
  Input:        NA
  Output:       NA
  Return:       0->"Unknown", 1->"Good", 2->"Overheat", 3->"Dead",
			4->"Over voltage", 5->"Unspecified failure", 6->"Cold",
****************************************************************************/
int hisi_battery_health(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_health);

	return 0;
}

/****************************************************************************
  Function:     hisi_battery_capacity_level
  Description:  get the capacity level of battery
  Input:        NA
  Output:       NA
  Return:       capacity level and 0 meaning unknow level
****************************************************************************/
int hisi_battery_capacity_level(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_capacity_level);

	return POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
}

/****************************************************************************
  Function:     hisi_battery_capacity_level
  Description:  get the technology of battery
  Input:        NA
  Output:       NA
  Return:       POWER_SUPPLY_TECHNOLOGY_LIPO
****************************************************************************/
int hisi_battery_technology(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_technology);

	return POWER_SUPPLY_TECHNOLOGY_LIPO;
}

/****************************************************************************
  Function:     hisi_battery_charge_params
  Description:  get the charge params of battery
  Input:        NA
  Output:       NA
  Return:       struct chrg_para_lut *chrg_para or NULL
****************************************************************************/
struct chrg_para_lut *hisi_battery_charge_params(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_charge_params);
	return NULL;
}

/****************************************************************************
  Function:     hisi_battery_vbat_max
  Description:  get the max battery voltage
  Input:         NA
  Output:       NA
  Return:       battery voltage Or < 0 if something fails
****************************************************************************/
int hisi_battery_vbat_max(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_vbat_max);
	return -EPERM;
}

/****************************************************************************
  Function:     hisi_battery_cycle_count
  Description:  get battery charging cycle count
  Input:         NA
  Output:       NA
  Return:       battery cycle count Or < 0 if something fails
****************************************************************************/
int hisi_battery_cycle_count(void)
{
	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();

	/*execute the operation of coul module */
	HISI_EXEC_COUL_OP(battery_cycle_count);
	return -EPERM;
}

/****************************************************************************
  Function:     hisi_power_supply_voltage
  Description:  get the voltage of the power suply, such as USB or AC port
  Input:        NA
  Output:       NA
  Return:       the battery Voltage in milivolts
			Or < 0 if something fails.
****************************************************************************/
int hisi_power_supply_voltage(void)
{
	return 4.2 * 1000;
}

/****************************************************************************
  Function:     hisi_coul_charger_event_rcv()
  Description:  recevie charger event such as charging done/charging start
  Input:        NA
  Output:       NA
  Return:       NA
****************************************************************************/
void hisi_coul_charger_event_rcv(unsigned int event)
{

	extern struct blocking_notifier_head notifier_list;

	/*declare the local variable of struct hisi_coul_ops */
	LOCAL_HISI_COUL_OPS();
	if (NULL != g_hisi_coul_test_info) {
		if (g_hisi_coul_test_info->test_start_flag & 0x0080) {
			hwlog_info("input event is %d\n", g_hisi_coul_test_info->input_event);
			event = g_hisi_coul_test_info->input_event;
		}
	}
	/*execute the operation of coul module */
	if (ops && ops->charger_event_rcv) {
		hwlog_info("charger event = 0x%x\n", (int)event);
		ops->charger_event_rcv(event);
	}

	blocking_notifier_call_chain(&notifier_list, event, NULL);
}

/****************************************************************************
  Function:     hisi_coul_ops_register
  Description:  register the hisi coul ops
  Input:        struct hisi_coul_ops *ops
  Output:       NA
  Return:       0: register successfull
			-EBUSY: register already
****************************************************************************/
int hisi_coul_ops_register(struct hisi_coul_ops *coul_ops, enum HISI_COULOMETER_TYPE coul_type)
{

	HISI_COUL_LOCK();
	if (g_hisi_coul_ops) {
		HISI_COUL_UNLOCK();
		hwlog_err("coul ops have registered already\n");
		return -EBUSY;
	}

	g_hisi_coul_ops = coul_ops;
	g_hisi_coul_type = coul_type;
	HISI_COUL_UNLOCK();

	return 0;
}

/****************************************************************************
  Function:     hisi_coul_ops_unregister
  Description:  UNregister the hisi coul ops
  Input:        struct hisi_coul_ops *ops
  Output:       NA
  Return:       0: unregister successfull
			-EINVAL: unregister failed
****************************************************************************/
int hisi_coul_ops_unregister(struct hisi_coul_ops *coul_ops)
{
	HISI_COUL_LOCK();
	if (g_hisi_coul_ops == coul_ops) {
		g_hisi_coul_ops = NULL;
		g_hisi_coul_type = COUL_UNKNOW;
		HISI_COUL_UNLOCK();
		return 0;
	}
	HISI_COUL_UNLOCK();

	return -EINVAL;
}

int __init hisi_coul_init(void)
{
	hwlog_info("hisi_coul_init\n");
	return 0;
}

module_init(hisi_coul_init);

void __exit hisi_coul_exit(void)
{
	return;
}

module_exit(hisi_coul_exit);

MODULE_AUTHOR("HUAWEI_HISI");
MODULE_DESCRIPTION("hisi coul module driver");
MODULE_LICENSE("GPL");
