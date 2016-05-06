#ifndef __DUAL_CHARGER_H_
#define __DUAL_CHARGER_H_

#define DEFAULT_IIN_MAX_EACH_CHARGER      1100
#define DEFAULT_ICHG_NEED_AUX_CHARGER    1000
#define DEFAULT_ICHG_MAX    3500

enum dual_charger_sysfs_type{
    DUAL_CHARGER_SYSFS_ENABLE_CHARGER_MAIN = 0,
    DUAL_CHARGER_SYSFS_ENABLE_CHARGER_AUX,
};

struct dual_charger_info{
    struct device *dev;

    int iin_thermal_main;
    int iin_thermal_aux;
    int ichg_thermal_main;
    int ichg_thermal_aux;
    int ichg;
    int ichg_max;

    int input_current_main;
    int input_current_aux;
    int charge_current_main;
    int charge_current_aux;

    int charge_enable_main;
    int charge_enable_aux;
    int charge_enable_sysfs_main;
    int charge_enable_sysfs_aux;

    int iin_max_each_charger;
    int ichg_need_aux_charger;

    int charge_done;
};

#ifdef CONFIG_LLT_TEST
struct dual_charger_static_ops {
    void (*select_input_current)(int);
    void (*select_charge_current)(int);
    int (*set_charge_enable)(int);
};
#endif
extern int charge_main_ops_register(struct charge_device_ops *);
extern int charge_aux_ops_register(struct charge_device_ops *);

#endif
