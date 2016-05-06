/*
 * arch/arm/mach-k3v2/include/mach/board-hi6421-regulator.h
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#include <linux/regulator/machine.h>
#include <linux/mfd/hi6421/hi6421-regulator.h>
static struct regulator_consumer_supply ldo0_consumers[] = {
	REGULATOR_SUPPLY("mlcnand-vcc", "mlc-nand"),
	REGULATOR_SUPPLY("emmc-vcc", "hi_mci.1"),
};
static struct regulator_consumer_supply ldo1_consumers[] = {
	REGULATOR_SUPPLY("clock-26M-vcc", NULL),
};
static struct regulator_consumer_supply ldo2_consumers[] = {
	REGULATOR_SUPPLY("system-vcc", "system"),
	REGULATOR_SUPPLY("btsubsys-vcc", "bt-subsys"),
	REGULATOR_SUPPLY("pll-vcc", "pll-digital"),
};
static struct regulator_consumer_supply ldo3_consumers[] = {
	REGULATOR_SUPPLY("ddr-vcc", "ddr"),
};
static struct regulator_consumer_supply ldo4_consumers[] = {
	REGULATOR_SUPPLY("mipi-vcc", "mipi"),
	REGULATOR_SUPPLY("usb20-vcc", "hisik3-usb-otg"),
	REGULATOR_SUPPLY("pcle-vcc", "pcle"),
	REGULATOR_SUPPLY("sensor-vcc", "sensor"),
};
static struct regulator_consumer_supply ldo5_consumers[] = {
	REGULATOR_SUPPLY("lpddr-vcc", "lpddr"),
	REGULATOR_SUPPLY("slcnand-vcc", "slc-nand"),
	REGULATOR_SUPPLY("bt-vcc", "bt"),
	REGULATOR_SUPPLY("gps-vcc", "gps-rfic"),
	REGULATOR_SUPPLY("ts-vbus", "synaptics-ts"),
	REGULATOR_SUPPLY("es305-vcc", NULL),
	REGULATOR_SUPPLY("lowpower-vcc", NULL),
};
static struct regulator_consumer_supply ldo6_consumers[] = {
	REGULATOR_SUPPLY("io-vcc", "io"),
	REGULATOR_SUPPLY("ts-vdd", "synaptics-ts"),
	REGULATOR_SUPPLY("tsanalog-Platform-vcc", "atmel-ts"),
};
static struct regulator_consumer_supply ldo7_consumers[] = {
	REGULATOR_SUPPLY("sdio-vcc", "hi_mci.0"),
};
static struct regulator_consumer_supply ldo8_consumers[] = {
	REGULATOR_SUPPLY("usbphy-vcc", "hisik3-usb-otg"),
};
static struct regulator_consumer_supply ldo9_consumers[] = {
	REGULATOR_SUPPLY("efuse-vcc", "efuse"),
};
static struct regulator_consumer_supply ldo10_consumers[] = {
	REGULATOR_SUPPLY("btrf-vcc", "btrf"),
	REGULATOR_SUPPLY("pa-vcc", "pa"),
};
static struct regulator_consumer_supply ldo11_consumers[] = {
	REGULATOR_SUPPLY("gpsrf-vcc", "gpsrf"),
	REGULATOR_SUPPLY("sec-cameralog-vcc", "camera"),
};
static struct regulator_consumer_supply ldo12_consumers[] = {
	REGULATOR_SUPPLY("sd-vcc", "hi_mci.0"),
	REGULATOR_SUPPLY("test-vcc", NULL),
};
static struct regulator_consumer_supply ldo13_consumers[] = {
	REGULATOR_SUPPLY("cmmb-vcc", "cmmb"),
	REGULATOR_SUPPLY("tsanalog-Phone-vcc", "atmel-ts"),
};
static struct regulator_consumer_supply ldo14_consumers[] = {
	REGULATOR_SUPPLY("wifiio-vcc", NULL),
	REGULATOR_SUPPLY("bt-io-vcc", NULL),
	REGULATOR_SUPPLY("BT_IO_VDD", NULL),
	REGULATOR_SUPPLY("WIFI_IO_VDD", NULL),
	REGULATOR_SUPPLY("GPS_IO_VDD", NULL),

};
static struct regulator_consumer_supply ldo15_consumers[] = {
	REGULATOR_SUPPLY("wificore-vcc", "wifi-core"),
};
static struct regulator_consumer_supply ldo16_consumers[] = {
	REGULATOR_SUPPLY("lcdio-vcc", "k3_dev_lcd"),
};
static struct regulator_consumer_supply ldo17_consumers[] = {
	REGULATOR_SUPPLY("lcdanalog-vcc", "k3_dev_lcd"),
};
static struct regulator_consumer_supply ldo18_consumers[] = {
	REGULATOR_SUPPLY("camera-vcc", "camera"),
};
static struct regulator_consumer_supply ldo19_consumers[] = {
	REGULATOR_SUPPLY("pri-cameralog-vcc", "camera"),
};
static struct regulator_consumer_supply ldo20_consumers[] = {
	REGULATOR_SUPPLY("cameravcm-vcc", "camera"),
};
static struct regulator_consumer_supply ldo_audio_consumers[] = {
	REGULATOR_SUPPLY("audio-vcc", "hi6421-codec"),
	REGULATOR_SUPPLY("hkadc-vcc", "hkadc"),
};
static struct regulator_consumer_supply buck0_consumers[] = {
	REGULATOR_SUPPLY("a9core0-vcc", "a9core"),
};
static struct regulator_consumer_supply buck1_consumers[] = {
	REGULATOR_SUPPLY("a9core1-vcc", "a9core"),
};
static struct regulator_consumer_supply buck2_consumers[] = {
	REGULATOR_SUPPLY("gpu-vcc", "gpu"),
};
static struct regulator_consumer_supply buck3_consumers[] = {
	REGULATOR_SUPPLY("peripheral-vcc", "peripheral"),
};
static struct regulator_consumer_supply buck4_consumers[] = {
	REGULATOR_SUPPLY("lpddr2-vcc", "lpddr2"),
	REGULATOR_SUPPLY("apio-vcc", "apio"),
};
static struct regulator_consumer_supply buck5_consumers[] = {
	REGULATOR_SUPPLY("ldo-vcc", "ldo"),
};
static struct regulator_consumer_supply usb_chg_pump_consumers[] = {
	REGULATOR_SUPPLY("usb-chg-pump", NULL),
};
static struct regulator_consumer_supply hdmi_chg_pump_consumers[] = {
	REGULATOR_SUPPLY("hdmi-chg-pump", NULL),
};
static struct regulator_init_data k3v2_regulators[] = {
	[HI6421_LDO0] = {
		.constraints = {
			.name = "LDO0",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo0_consumers),
		.consumer_supplies = ldo0_consumers,
	},
	[HI6421_LDO1] = {
		.constraints = {
			.name =  "LDO1",
			.min_uV = 1700000,
			.max_uV = 2000000,
			.input_uV = 1700000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo1_consumers),
		.consumer_supplies = ldo1_consumers,
	},
	[HI6421_LDO2] = {
		.constraints = {
			.name = "LDO2",
			.min_uV = 1050000,
			.max_uV = 1400000,
			.input_uV = 1050000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo2_consumers),
		.consumer_supplies = ldo2_consumers,
	},
	[HI6421_LDO3] = {
		.constraints = {
			.name = "LDO3",
			.min_uV = 1050000,
			.max_uV = 1400000,
			.input_uV = 1050000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo3_consumers),
		.consumer_supplies = ldo3_consumers,
	},
	[HI6421_LDO4] = {
		.constraints = {
			.name = "LDO4",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo4_consumers),
		.consumer_supplies = ldo4_consumers,
	},
	[HI6421_LDO5] = {
		.constraints = {
			.name = "LDO5",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo5_consumers),
		.consumer_supplies = ldo5_consumers,
	},
	[HI6421_LDO6] = {
		.constraints = {
			.name = "LDO6",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo6_consumers),
		.consumer_supplies = ldo6_consumers,
	},
	[HI6421_LDO7] = {
		.constraints = {
			.name = "LDO7",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo7_consumers),
		.consumer_supplies = ldo7_consumers,
	},
	[HI6421_LDO8] = {
		.constraints = {
			.name = "LDO8",
			.min_uV = 1500000,
			.max_uV = 3300000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo8_consumers),
		.consumer_supplies = ldo8_consumers,
	},
	[HI6421_LDO9] = {
		.constraints = {
			.name = "LDO9",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo9_consumers),
		.consumer_supplies = ldo9_consumers,
	},
	[HI6421_LDO10] = {
		.constraints = {
			.name = "LDO10",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo10_consumers),
		.consumer_supplies = ldo10_consumers,
	},
	[HI6421_LDO11] = {
		.constraints = {
			.name = "LDO11",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo11_consumers),
		.consumer_supplies = ldo11_consumers,
	},
	[HI6421_LDO12] = {
		.constraints = {
			.name = "LDO12",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo12_consumers),
		.consumer_supplies = ldo12_consumers,
	},
	[HI6421_LDO13] = {
		.constraints = {
			.name = "LDO13",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo13_consumers),
		.consumer_supplies = ldo13_consumers,
	},
	[HI6421_LDO14] = {
		.constraints = {
			.name = "LDO14",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo14_consumers),
		.consumer_supplies = ldo14_consumers,
	},
	[HI6421_LDO15] = {
		.constraints = {
			.name = "LDO15",
			.min_uV = 1500000,
			.max_uV = 3300000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo15_consumers),
		.consumer_supplies = ldo15_consumers,
	},
	[HI6421_LDO16] = {
		.constraints = {
			.name = "LDO16",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo16_consumers),
		.consumer_supplies = ldo16_consumers,
	},
	[HI6421_LDO17] = {
		.constraints = {
			.name = "LDO17",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo17_consumers),
		.consumer_supplies = ldo17_consumers,
	},
	[HI6421_LDO18] = {
		.constraints = {
			.name = "LDO18",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo18_consumers),
		.consumer_supplies = ldo18_consumers,
	},
	[HI6421_LDO19] = {
		.constraints = {
			.name = "LDO19",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo19_consumers),
		.consumer_supplies = ldo19_consumers,
	},
	[HI6421_LDO20] = {
		.constraints = {
			.name = "LDO20",
			.min_uV = 1500000,
			.max_uV = 3000000,
			.input_uV = 1500000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo20_consumers),
		.consumer_supplies = ldo20_consumers,
	},
	[HI6421_LDOAUDIO] = {
		.constraints = {
			.name = "LDO_AUDIO",
			.min_uV = 2800000,
			.max_uV = 3300000,
			.input_uV = 2800000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(ldo_audio_consumers),
		.consumer_supplies = ldo_audio_consumers,
	},
	[HI6421_BUCK0] = {
		.constraints = {
			.name = "BUCK0",
			.min_uV = 700000,
			.max_uV = 1601700,
			.input_uV = 700000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(buck0_consumers),
		.consumer_supplies = buck0_consumers,
	},
	[HI6421_BUCK1] = {
		.constraints = {
			.name = "BUCK1",
			.min_uV = 700000,
			.max_uV = 1601700,
			.input_uV = 700000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(buck1_consumers),
		.consumer_supplies = buck1_consumers,
	},
	[HI6421_BUCK2] = {
		.constraints = {
			.name = "BUCK2",
			.min_uV = 700000,
			.max_uV = 1601700,
			.input_uV = 700000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(buck2_consumers),
		.consumer_supplies = buck2_consumers,
	},
	[HI6421_BUCK3] = {
		.constraints = {
			.name = "BUCK3",
			.min_uV = 700000,
			.max_uV = 1200000,
			.input_uV = 1150000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(buck3_consumers),
		.consumer_supplies = buck3_consumers,
	},
	[HI6421_BUCK4] = {
		.constraints = {
			.name = "BUCK4",
			.min_uV = 1150000,
			.max_uV = 2000000,
			.input_uV = 1150000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(buck4_consumers),
		.consumer_supplies = buck4_consumers,
	},
	[HI6421_BUCK5] = {
		.constraints = {
			.name = "BUCK5",
			.min_uV = 1150000,
			.max_uV = 1900000,
			.input_uV = 1150000,
			.valid_modes_mask = REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_IDLE,
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
					| REGULATOR_CHANGE_MODE,
			.initial_mode = REGULATOR_MODE_NORMAL,
			.always_on = 1,
		},
		.num_consumer_supplies = ARRAY_SIZE(buck5_consumers),
		.consumer_supplies = buck5_consumers,
	},
	[HI6421_USB_CHG_PUMP] = {
		.constraints = {
			.name = "USB_CHG_PUMP",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(usb_chg_pump_consumers),
		.consumer_supplies = usb_chg_pump_consumers,
	},
	[HI6421_HDMI_CHG_PUMP] = {
		.constraints = {
			.name = "HDMI_CHG_PUMP",
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
			.always_on = 0,
		},
		.num_consumer_supplies = ARRAY_SIZE(hdmi_chg_pump_consumers),
		.consumer_supplies = hdmi_chg_pump_consumers,
	},
};
static struct resource hi6421_regulator_resources[] = {
	{
		.start = REG_BASE_PMUSPI,
		.end = REG_BASE_PMUSPI + REG_PMUSPI_IOSIZE - 1,
		.flags	 = IORESOURCE_MEM,
	},
	{
		.start = IRQ_OCP_RISING,
		.end = IRQ_OCP_RISING,
		.flags	 = IORESOURCE_IRQ,
	},
};
#ifdef _DRV_LLT_
struct platform_device hi6421_regulator_device =
#else
static struct platform_device hi6421_regulator_device =
#endif
{
	.name =  "hi6421-regulator",
	.id = 0,
	.dev = {
		.platform_data	= k3v2_regulators,
	},
	.num_resources = ARRAY_SIZE(hi6421_regulator_resources),
	.resource = hi6421_regulator_resources,
};

