#ifndef ASMARM_MACH_MMC_H
#define ASMARM_MACH_MMC_H

#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mshci.h>

#define TUNING_INIT_CONFIG_NUM 6

struct hisik3_mmc_platform_data {
	/* available voltages */
	unsigned int ocr_mask;
	/* available capabilities */
	unsigned long caps;
	/* more capabilities */
	unsigned long caps2;
	/* work clock low clk name */
	char *clk_mmc_low;
	/* tuning high clock name */
	char *clk_mmc_high;
	/* deviations from spec. */
	unsigned int quirks;
	/* external detect card gpio */
	unsigned int cd_gpio;
	/* sdcard IO power switch gpio*/
	unsigned int sw_gpio;
	/* emmc reset gpio */
	unsigned int reset_gpio;
	/* iomux name */
	char *iomux_name;
	/* regulator name */
	char *reg_name_ldo;
	/* regulator name */
	char *reg_name_lvs;
	/* signal voltage regulator name */
	char *signal_reg_name;
	int (*ext_cd_init)(void (*notify_func)(struct platform_device *,
		int state));
	int (*ext_cd_cleanup)(void (*notify_func)(struct platform_device *,
		int state));
	int (*set_power)(struct platform_device *, int val);
	int (*rstdis_mmc)(void);
	int *timing_config;
	int *init_tuning_config;
	int suspend_timing_config;
	int allow_switch_signal_voltage;
	int default_signal_voltage;
};

extern void raw_mmc_turn_on(void);
extern void raw_mmc_turn_off(void);

#endif
