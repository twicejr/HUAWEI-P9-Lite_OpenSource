#ifndef _HISI_COUL_CORE_H_
#define _HISI_COUL_CORE_H_

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <asm/irq.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/reboot.h>
#include <asm/bug.h>
#include <linux/huawei/hisi_adc.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/mtd/hisi_nve_interface.h>
#include <linux/power/hisi/coul/hisi_coul_drv.h>
#include <linux/power/hisi/hisi_battery_data.h>
#include <linux/power/hisi/hisi_bci_battery.h>
#include <huawei_platform/power/huawei_charger.h>

#define SMARTSTAR_DEBUG
#define RBATT_ADJ 1

#ifndef BIT
#define BIT(x)      (1 << (x))
#endif


#define NOT_UPDATE_FCC  0x1
#define IS_UPDATE_FCC   0


#define DI_LOCK()    do {mutex_lock(&di->soc_mutex);} while (0)
#define DI_UNLOCK()  do {mutex_unlock(&di->soc_mutex);} while (0)


#define ABNORMAL_BATT_TEMPERATURE_LOW   (-40)
#define ABNORMAL_BATT_TEMPERATURE_HIGH  (80)
#define DEFAULT_TEMP             25         /* SFT  UDP */
#define TEMP_TOO_HOT            (60)
#define TEMP_TOO_COLD           (-20)


#define CHARGING_STATE_CHARGE_START         (1)
#define CHARGING_STATE_CHARGE_DONE          (2)
#define CHARGING_STATE_CHARGE_STOP          (3)
#define CHARGING_STATE_CHARGE_RECHARGE      (4)
#define CHARGING_STATE_CHARGE_NOT_CHARGE    (5)
#define CHARGING_STATE_CHARGE_UNKNOW        (0x0)


#define IAVG_SAMPLES 10
#define CHARGING_IAVG_MA 250
#define MIN_CHARGING_CURRENT_OFFSET (-10) 

#define DELTA_FCC_PERCENT 20
#define CALCULATE_SOC_MS    (20*1000)
#define READ_TEMPERATURE_MS (5*1000)
#define TEMPERATURE_INIT_STATUS 1
#define TEMPERATURE_UPDATE_STATUS 0
#define TEMPERATURE_CHANGE_LIMIT 50
#define CALIBRATE_INTERVAL (5*60*1000)    /* 5 min */
#define CHARGED_OCV_UPDATE_INTERVAL (10*60*1000)

#define  DEFAULT_HKADC_BATT_TEMP  10
#define  DEFAULT_HKADC_BATT_ID    6

#ifdef SMARTSTAR_DEBUG
#define DBG_CNT_INC(xxx)     di->xxx++
#else
#define DBG_CNT_INC(xxx)
#endif

#define BATTERY_CC_LOW_LEV      3
#define BATTERY_CC_WARNING_LEV  10
#define BATTERY_SWITCH_ON_VOLTAGE        (3250)
#define BATTERY_VOL_LOW_ERR 2900
#define BATTERY_NORMAL_CUTOFF_VOL 3150


#define LOW_INT_NOT_SET 0
#define LOW_INT_STATE_RUNNING 1
#define LOW_INT_STATE_SLEEP 0
#define LOW_INT_VOL_OFFSET 10     /* mv */
#define BATTERY_VOL_2_PERCENT 3350

#define ZERO_VOLTAGE_PLUS_5 3200
#define ZERO_VOLTAGE_MINUS_10 3300

#define MAX_TEMPS 10

#define INVALID_BATT_ID_VOL  -999
#define IAVG_TIME_2MIN   6 //6*20s

#define SR_ARR_LEN             100
#define SR_MAX_RESUME_TIME     90         // 90 s
#define SR_DELTA_SLEEP_TIME    (4 * 60)   // 4 min
#define SR_DELTA_WAKEUP_TIME   30         // 30 s
#define SR_TOTAL_TIME          (30 * 60)  // 30 min
#define SR_DUTY_RATIO          95
#define SR_DEVICE_WAKEUP       1
#define SR_DEVICE_SLEEP        2

#define HISI_COUL_NV_NAME         "HICOUL"
#define HISI_BAT_CALIBRATION_NV_NAME         "BATCALI"
#define HISI_COUL_NV_NUM          316
#define HISI_BAT_CALIBRATION_NV_NUM          317

#define MIN_BEGIN_PERCENT_FOR_LEARNING 60
#define MAX_DELTA_RC_PC 1

/*get ocv by vol*/
#define CURRENT_LIMIT (20*1000)
#define DEFAULT_BATTERY_OHMIC_RESISTANCE 100 /* mohm */

#define FLAG_USE_CLAC_OCV 0xABCD
#define FLAG_USE_PMU_OCV  0xCDEF


#define DEFAULT_V_OFF_A 1014000
#define DEFAULT_V_OFF_B 0
#define DEFAULT_C_OFF_A 1000000
#define DEFAULT_C_OFF_B 0
#define DEFAULT_RPCB 10000 /*uohm*/	

#define CHARGING_CURRENT_OFFSET (-10*1000)


#define BATTERY_PLUG_OUT 1
#define BATTERY_PLUG_IN  0
#define BATTERY_CHECK_TIME_MS (1*1000)

#define PMU_NV_ADDR_CMDLINE_MAX_LEN 30

/*flag:1 success 0:fail*/
#define NV_SAVE_SUCCESS 1
#define NV_SAVE_FAIL 0
#define NV_READ_SUCCESS 1
#define NV_READ_FAIL    0

/*NTC Table length*/
#define T_V_ARRAY_LENGTH 31

#define ABNORMAL_BATT_TEMPERATURE_POWEROFF 670
#define DELTA_TEMP 150
#define LOW_BATT_TEMP_CHECK_THRESHOLD -100

struct ss_coul_nv_info{
    int charge_cycles;
    int v_offset_a;
    int v_offset_b;
    int c_offset_a;
    int c_offset_b;
    int limit_fcc;
    short temp[MAX_TEMPS];
    short real_fcc[MAX_TEMPS];
    /*below get data from fastboot,not need to save*/
    short calc_ocv_reg_v;
    short calc_ocv_reg_c;
    short hkadc_batt_id_voltage;        
};

struct vcdata{
int avg_v; //mv
int avg_c; //ma
int min_c; //ma
int max_c; //ma
};


struct coul_device_ops{
    int   (*calculate_cc_uah)(void);
    void  (*save_cc_uah)(int cc_uah);
    int   (*convert_regval2ua)(short reg_val);    
    int   (*convert_regval2uv)(short reg_val);
    short (*convert_uv2regval)(int uv_val);
    int   (*is_battery_moved)(void);
    void  (*set_battery_moved_magic_num)(int);
    void  (*get_fifo_avg_data)(struct vcdata *vc); 
    int   (*get_fifo_depth)(void);
    int   (*get_delta_rc_ignore_flag)(void);
    int   (*get_nv_read_flag)(void);
    void  (*set_nv_save_flag)(int nv_flag);
    int   (*set_hltherm_flag)(int temp_protect_flag);
    int   (*get_hltherm_flag)(void);
    int   (*get_use_saved_ocv_flag)(void);
    int   (*get_fcc_invalid_up_flag)(void);
    void  (*save_ocv)(int ocv, int invalid_fcc_up_flag);
    short (*get_ocv)(void);
    void  (*clear_ocv)(void);
    void  (*save_ocv_temp)(short ocv_temp);
    short (*get_ocv_temp)(void);
    void  (*clear_ocv_temp)(void);    
    void  (*set_low_low_int_val)(int vol_mv);
    int   (*get_abs_cc)(void);
    unsigned int   (*get_coul_time)(void);
    void  (*clear_coul_time)(void);
    void  (*clear_cc_register)(void);
    void  (*cali_adc)(void);
    int   (*get_battery_voltage_uv)(void);
    int   (*get_battery_current_ua)(void);
    int   (*get_battery_vol_uv_from_fifo)(unsigned int fifo_order);
    int   (*get_battery_cur_ua_from_fifo)(unsigned int fifo_order);
    short (*get_offset_current_mod)(void);
    int   (*get_ate_a)(void);
    int   (*get_ate_b)(void);
    void  (*irq_enable)(void);
    void  (*show_key_reg)(void);
    void  (*enter_eco)(void);
    void  (*exit_eco)(void);
    int   (*calculate_eco_leak_uah)(void);
};

enum coul_fault_type{
    COUL_FAULT_NON = 0,
    COUL_FAULT_LOW_VOL,
    COUL_FAULT_CL_INT,
    COUL_FAULT_CL_IN,
    COUL_FAULT_CL_OUT,
    COUL_FAULT_TOTAL,
};
struct coul_cali_nv_info
{
    int v_offset_a;
    int v_offset_b;
    int c_offset_a;
    int c_offset_b;
};

struct smartstar_coul_device
{
    int batt_exist;
    int prev_pc_unusable;
    int batt_ocv; // ocv in uv
    int batt_ocv_temp;
    int batt_ocv_valid_to_refresh_fcc;
    int batt_changed_flag;
    int soc_limit_flag;
    int batt_temp; // temperature in degree*10
    int batt_fcc;
    int batt_limit_fcc;
    int batt_rm;
    int batt_ruc;
    int batt_uuc;
    int batt_delta_rc;
    int batt_pre_delta_rc;
    int rbatt;
    int rbatt_ratio;
    int r_pcb;
    int soc_work_interval;
    int charging_begin_soc;
    int charging_state;
    int charging_stop_time;
    int batt_soc;
    int batt_soc_real;
    int batt_soc_with_uuc;
    int batt_soc_est;
    int product_index;
    unsigned int batt_id_vol;
    unsigned int batt_chargecycles; //chargecycle in percent
    int last_cali_temp; // temperature in degree*10
    int cc_end_value; 
    unsigned int v_cutoff;
    unsigned int v_low_int_value;
    unsigned int 	get_cc_end_time;
    unsigned int   suspend_time; // time when suspend
    int   sr_suspend_time;  // sr time when suspend
    int   sr_resume_time;   // sr time when resume
    int charging_begin_cc;  /*the unit is uah*/
    int suspend_cc; // cc when suspend
    unsigned int last_time;
    int last_cc;
    int last_iavg_ma;
    int last_fifo_iavg_ma;
    int fcc_real_mah;
    struct mutex soc_mutex;
    struct hisi_coul_battery_data *batt_data;
    struct single_row_lut    *adjusted_fcc_temp_lut;
    struct single_row_lut    adjusted_fcc_temp_lut_tbl1;
    struct single_row_lut    adjusted_fcc_temp_lut_tbl2;
    struct delayed_work    calculate_soc_delayed_work;
    struct delayed_work    battery_check_delayed_work;
    struct delayed_work read_temperature_delayed_work;
    struct work_struct      fault_work;
    struct notifier_block   fault_nb;
    struct notifier_block reboot_nb;
    struct hisi_coul_ops  *ops;
    struct ss_coul_nv_info nv_info;
    struct coul_device_ops *coul_dev_ops;
    enum coul_fault_type  coul_fault;    
    struct device *dev;    
    int is_nv_read;
    int is_nv_need_save;

#ifdef SMARTSTAR_DEBUG
    unsigned int dbg_ocv_cng_0; /*ocv change count by wake up*/
    unsigned int dbg_ocv_cng_1; /*ocv change count by full charged*/
    unsigned int dbg_valid_vol; /*vaild voltage from FIFO vol registers*/
    unsigned int dbg_invalid_vol; /*invaild voltage from FIFO vol registers*/
    unsigned int dbg_ocv_fc_failed; /*full charged can't update OCV*/
#endif
};

extern struct device *coul_dev;
extern int v_offset_a;		
extern int v_offset_b;			            
extern int c_offset_a;		
extern int c_offset_b;
extern int coul_core_ops_register(struct coul_device_ops *ops);

#endif


