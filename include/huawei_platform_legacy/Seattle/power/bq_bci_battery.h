#ifndef _LINUX_BQ_BCI_BATTERY_H
#define _LINUX_BQ_BCI_BATTERY_H


#define BAT_VOL_3200    (3200)
#define BAT_VOL_3500    (3500)
#define BAT_VOL_3550    (3550)
#define BAT_VOL_3600    (3600)
#define BAT_VOL_3700    (3700)
#define BAT_VOL_3800    (3800)
#define BAT_VOL_3850    (3850)
#define BAT_VOL_3900    (3900)
#define BAT_VOL_3950    (3950)
#define BAT_VOL_4000    (4000)
#define BAT_VOL_4200    (4200)
#define BAT_VOL_4250    (4250)
#define BQ_FLAG_SOC1             (1<<2)
#define BQ_FLAG_SOCF             (1<<1)
#define BQ_FLAG_LOCK       (BQ_FLAG_SOC1 | BQ_FLAG_SOCF)

enum charge_status_event{
    VCHRG_POWER_NONE_EVENT = 0,
    VCHRG_NOT_CHARGING_EVENT,
    VCHRG_START_CHARGING_EVENT,
    VCHRG_START_AC_CHARGING_EVENT,
    VCHRG_START_USB_CHARGING_EVENT,
    VCHRG_CHARGE_DONE_EVENT,
    VCHRG_STOP_CHARGING_EVENT,
    VCHRG_POWER_SUPPLY_OVERVOLTAGE,
    VCHRG_POWER_SUPPLY_WEAKSOURCE,
    VCHRG_STATE_WDT_TIMEOUT,
    VCHRG_START_OTG_EVENT,
    BATTERY_LOW_WARNING,
    BATTERY_LOW_SHUTDOWN,
};

#define CURRENT_OFFSET    (10)
#define HIGH_LEVEL_CAPACITY_STAY_THRESH  (1)
#define MID_LEVEL_CAPACITY_STAY_THRESH   (3)
#define LOW_LEVEL_CAPACITY_STAY_THRESH   (6)

#define BATTERY_CAPACITY_FULL     (100)
#define BATTERY_MONITOR_INTERVAL  (10)
#define BATTERY_LOW_CAPACITY      (15)

#define BATTERY_TEMP_LOW_THRESHOLD    (-10)
#define BATTERY_TEMP_HIGH_THRESHOLD    (50)

#define LOW_VOL_IRQ_NUM           (13)
#define LOW_BAT_VOL_MASK_1        (0x3B)
#define LOW_BAT_VOL_MASK_2        (0x39)
#define LOW_BAT_VOL_MASK_3        (0x38)
#define LOW_BAT_VOL_MASK_4        (0x37)
#define LOW_BAT_VOL_MASK_5        (0x3D)

#define ERROR_BATT_NOT_EXIST               (10403)
#define ERROR_BATT_TEMP_LOW                (10404)
#define ERROR_BATT_VOLT_HIGH               (10405)
#define ERROR_BATT_VOLT_LOW                (10406)
#define ERROR_BATT_TERMINATE_TOO_EARLY     (10407)
#define ERROR_BATT_NOT_TERMINATE           (10408)
#define ERROR_BATT_BAD_CURR_SENSOR         (10409)
#define ERROR_VBUS_VOLT_HIGH               (10410)
#define ERROR_WATCHDOG_RESET               (10411)
#define ERROR_CHARGE_CURR_OVERHIGH         (10412)
#define ERROR_DISCHARGE_CURR_OVERHIGH      (10413)
#define ERROR_CHARGE_CURR_ZERO             (10414)
#define ERROR_UFCAPCITY_DEBOUNCE_100       (0x0800)
#define ERROR_FCC_DEBOUNCE                 (0x1000)
#define ERROR_CAPACITY_CHANGE_FAST         (0x2000)
#define ERROR_BATT_TEMP_STAY               (0x4000)
#define ERROR_UFCAPCITY_DEBOUNCE_OTHER     (0x8000)

#define IMPOSSIBLE_IAVG            (9999)
#define RECHG_PROTECT_THRESHOLD    (150)

enum plugin_status {
    /* no charger plugin */
    PLUGIN_DEVICE_NONE,
   /* plugin usb charger */
    PLUGIN_USB_CHARGER,
   /* plugin ac charger */
   PLUGIN_AC_CHARGER,
};

int bq_register_notifier(struct notifier_block *nb,
                unsigned int events);
int bq_unregister_notifier(struct notifier_block *nb,
                unsigned int events);
int bq_bci_show_capacity(void);
struct class *hw_power_get_class(void);
struct dsm_client *get_battery_dclient(void);
#endif
