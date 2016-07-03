/*
 * Atmel maXTouch Touchscreen driver
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Copyright (C) 2011-2012 Atmel Corporation
 * Copyright (C) 2012 Google, Inc.
 *
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */
#include "atomic_op.h"
#include <linux/firmware.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/kthread.h>

#ifndef ATMEL_CONFIG_H
#define ATMEL_CONFIG_H
#define MAX_KEYS_SUPPORTED_IN_DRIVER 6

#define MISC_PDS_HEAD_LEN 2
#define MISC_PDS_DATA_LEN 11

/* Configuration file */
#define MXT_CFG_MAGIC		"OBP_RAW V1"
#define ATMEL_CHIP_INFO	"atmel-"

/* Registers */
#define MXT_OBJECT_START	0x07
#define MXT_OBJECT_SIZE		6
#define MXT_INFO_CHECKSUM_SIZE	3
//Block size (should more than T5 size(10), less than 255)
#define MXT_MAX_BLOCK_READ	250
#define MXT_MAX_BLOCK_WRITE	128

/* MXT_GEN_MESSAGE_T5 object */
#define MXT_RPTID_NOMSG		0xff

#define MXT_POWER_CFG_RUN		0
#define MXT_POWER_CFG_DEEPSLEEP		1

//#define CONFIG_MXT_DUMMY_CAL_AT_RESUME
//#define CONFIG_MXT_CAL_TRIGGER_T8_WITH_UNKONW_SOURCE
#define CONFIG_MXT_CAL_TRIGGER_CAL_WHEN_CFG_MATCH
//#define CONFIG_MXT_TRACK_TRUNK_DATA
//#define CONFIG_MXT_TRIGGER_PI_PRE_PROCESS_AT_FIRST_POWERUP
//#define CONFIG_MXT_T71_RESET_WATCHDOG
#define CONFIG_MXT_UPDATE_BY_OBJECT


/* Define for T6 command */
#define MXT_COMMAND_RESET	0
#define MXT_COMMAND_BACKUPNV	1
#define MXT_COMMAND_CALIBRATE	2
#define MXT_COMMAND_REPORTALL	3
#define MXT_COMMAND_DIAGNOSTIC	5

/* Define for T6 debug mode command */
#define MXT_T6_DEBUG_PAGEUP	0x1
#define MXT_T6_DEBUG_PAGEDOWN	0x2
#define MXT_T6_DEBUG_DELTA	0x10
#define MXT_T6_DEBUG_REF	0x11
#define MXT_T6_DEBUG_DELTA_PTC	0x14
#define MXT_T6_DEBUG_REF_PTC		0x15
#define MXT_T6_DEBUG_SE	0x33
#define MXT_T6_DEBUG_GESTRUE	0x34
#define MXT_T6_DEBUG_DEVICE_ID		0x80
#define MXT_T6_DEBUG_PID	0x81
#define MXT_T6_DEBUG_TOUCH_THRESH		0xF4
#define MXT_T6_DEBUG_DELTA_SC	0xF7
#define MXT_T6_DEBUG_SIGNAL_SC	0xFE

/* Define for T6 status byte */
#define MXT_T6_STATUS_RESET	(1 << 7)
#define MXT_T6_STATUS_OFL	(1 << 6)
#define MXT_T6_STATUS_SIGERR	(1 << 5)
#define MXT_T6_STATUS_CAL	(1 << 4)
#define MXT_T6_STATUS_CFGERR	(1 << 3)
#define MXT_T6_STATUS_COMSERR	(1 << 2)

#define MXT_T8_CHRGTIME	0
#define MXT_T8_TCHDRIFT	2
#define MXT_T8_DRIFTST	3
#define MXT_T8_TCHAUTOCAL	4
#define MXT_T8_SYNC	5
#define MXT_T8_ATCHCALST	6
#define MXT_T8_ATCHCALSTHR	7
#define MXT_T8_ATCHFRCCALTHR		8
#define MXT_T8_ATCHFRCCALRATIO	9

#define T9_T100_CTRL_ENABLE	(1<<0)
#define T9_T100_CTRL_REPEN	(1<<1)

#define MXT_T15_XORIGN		1
#define MXT_T15_YORIGN		2
#define MXT_T15_XSIZE		3
#define MXT_T15_YSIZE		4
#define MXT_T15_TCHHR		7

/* MXT_SPT_COMMSCONFIG_T18 */
#define MXT_COMMS_CTRL		0
#define MXT_COMMS_CMD		1
#define MXT_COMMS_RETRIGEN	  (1 << 6)

/* Define for MXT_GEN_COMMAND_T6 */
#define MXT_BOOT_VALUE		0xa5
#define MXT_RESET_VALUE		0x01
#define MXT_BACKUP_VALUE	0x55

/* Define for MXT_PROCI_TOUCHSUPPRESSION_T42 */
#define MXT_T42_MSG_TCHSUP	(1 << 0)

/* T47 Stylus */
#define MXT_TOUCH_MAJOR_T47_STYLUS	1
#define MXT_TOUCH_MAJOR_T15_VIRTUAL_KEY 2

/* T63 Stylus */
#define MXT_T63_STYLUS_PRESS	(1 << 0)
#define MXT_T63_STYLUS_RELEASE	(1 << 1)
#define MXT_T63_STYLUS_MOVE		(1 << 2)
#define MXT_T63_STYLUS_SUPPRESS	(1 << 3)

#define MXT_T63_STYLUS_DETECT	(1 << 4)
#define MXT_T63_STYLUS_TIP		(1 << 5)
#define MXT_T63_STYLUS_ERASER	(1 << 6)
#define MXT_T63_STYLUS_BARREL	(1 << 7)

#define MXT_T63_STYLUS_PRESSURE_MASK	0x3F

/* Define for NOISE SUPPRESSION T72 */
#define MXT_T72_NOISE_SUPPRESSION_STATECHG	(1 << 3)
#define MXT_T72_NOISE_SUPPRESSION_NOISELVCHG	(1 << 4)
#define MXT_T72_NOISE_SUPPRESSION_STABCTRL         20
#define MXT_T72_NOISE_SUPPRESSION_NOISCTRL         40
#define MXT_T72_NOISE_SUPPRESSION_VNOICTRL         60
#define MXT_T72_NOISE_SUPPRESSION_DUALXMODE         (1<<3)

#define MXT_T72_NOISE_SUPPRESSION_STATUS2STATE_MASK	0x07
#define MXT_T72_NOISE_SUPPRESSION_NO_DEF 0
#define MXT_T72_NOISE_SUPPRESSION_STAB	2
#define MXT_T72_NOISE_SUPPRESSION_NOIS	3
#define MXT_T72_NOISE_SUPPRESSION_VNOIS	4


/* T100 Multiple Touch Touchscreen */
#define MXT_T100_CTRL		0
#define MXT_T100_CFG1		1
#define MXT_T100_SCRAUX		2
#define MXT_T100_TCHAUX		3
#define MXT_T100_XRANGE		13
#define MXT_T100_YRANGE		24

#define MXT_T100_XSIZE		9
#define MXT_T100_YSIZE		20
#define MXT_T100_XORIGIN		8
#define MXT_T100_YORIGIN		19

#define MXT_T100_CFG_SWITCHXY	(1 << 5)

#define MXT_T100_SCRAUX_NUMTCH	(1 << 0)
#define MXT_T100_SCRAUX_TCHAREA	(1 << 1)
#define MXT_T100_SCRAUX_ATCHAREA	(1 << 2)
#define MXT_T100_SCRAUX_INTTCHAREA		(1 << 3)

#define MXT_T100_TCHAUX_VECT			(1 << 0)
#define MXT_T100_TCHAUX_AMPL			(1 << 1)
#define MXT_T100_TCHAUX_AREA			(1 << 2)
#define MXT_T100_TCHAUX_HW			(1 << 3)
#define MXT_T100_TCHAUX_PEAK			(1 << 4)
#define MXT_T100_TCHAUX_AREAHW		(1 << 5)

#define MXT_T100_DETECT				(1 << 7)
#define MXT_T100_TYPE_MASK			0x70
#define MXT_T100_TYPE_FINGER			0x10
#define MXT_T100_TYPE_STYLUS			0x20
#define MXT_T100_TYPE_GLOVE			0x50
#define MXT_T100_TYPE_LARGETOUCH		0x60

#define MXT_T100_EVENT_MASK			0x0f
#define MXT_T100_EVENT_NO_EVENT		0
#define MXT_T100_EVENT_MOVE			1
#define MXT_T100_EVENT_DOWN			4
#define MXT_T100_EVENT_UP				5

#define MXT_T100_NUMTOUCH				6
#define MXT_T100_TCHHR					30
#define MXT_T100_TCHHYST				31
#define MXT_T100_INTTHR				32
#define MXT_T100_MRGTHR				35
#define MXT_T100_DXTHRSF				38
#define MXT_T100_MRGHYST				37
#define MXT_T100_INTTHRHYST			53

#define MXT_SCRAUX_STS_DETECT	(1 << 7)
#define MXT_SCRAUX_STS_SUP		(1 << 6)

#define MXT_T70_PROCESS_TIMEOUT 50
#define MXT_T70_PROCESS_RETRY 100

#define MXT_T61_CTRL	0
#define MXT_T61_CMD	1
#define MXT_T61_MODE	2
#define MXT_T61_PERIOD	3

#define MXT_T61_CTRL_EN		(1<<0)
#define MXT_T61_CTRL_RPTEN	(1<<1)

#define MXT_T61_RUNNING		(1<<0)
#define MXT_T61_FORCERPT	(1<<4)
#define MXT_T61_STOP		(1<<5)
#define MXT_T61_START		(1<<6)
#define MXT_T61_ELAPSED		(1<<7)

//  C: T9 THLD / Length: 2
#define MXT_T38_MAGIC_WORD	0x92
#define MXT_T38_OFFICIAL_RESERVED   0
#define MXT_T38_CONFIG_VERSION_0   1
#define MXT_T38_CONFIG_VERSION_1   2
#define MXT_T38_BLOCK_LOW_LIMIT_LEVEL		3
#define MXT_T38_BLOCK_HIGH_LIMIT_LEVEL		4
#define MXT_T38_T9_T100_THLD_NORMAL_STEP1	5
#define MXT_T38_T9_T100_THLD_NOISE		6
#define MXT_T38_MGWD				7

/* Define for MXT_PROCI_GRIPSUPPRESSION_T40 */
#define MXT_GRIP_CTRL			0
#define MXT_GRIP_XLOCRIP		1
#define MXT_GRIP_XHICRIP		2
#define MXT_GRIP_YLOCRIP		3
#define MXT_GRIP_YHICRIP		4
/* T55 reg array */
#define MXT_T55_CTRL			0
#define MXT_T55_TARGETTHR		1
#define MXT_T55_THRADJLIM		2
#define MXT_T55_RESETSTEPTIME		3
#define MXT_T55_FORCECHGDIST		4
#define MXT_T55_FORCECHGTIME		5

#define MXT_T55_CTRL_EN		(1<<0)
/* T65 reg array */
#define MXT_T65_CTRL		0
#define MXT_T65_GRADTHR		1
#define MXT_T65_LPFILTER	10
/* T71 reg array */
#define MXT_T71_RESET_MAGIC_WORD	0x16
#define MXT_T71_RESET_TAG		0

/* T80 reg array */
#define MXT_T80_CTRL		0
#define MXT_T80_COMP_GAIN	1

#define T61_MAX_INSTANCE_NUM 2//here assume support 2 timer

/* MXT_SPT_SELFCAPHOVERCTECONFIG_T102 */
#define MXT_SELF_CHGTIME	13

/* cmd and message */
#define MXT_SELFCAP_CMD	0x1
#define MXT_SELFCMD_TUNE	0x1
#define MXT_SELFCMD_NVM_TUNE	0x2
#define MXT_SELFCMD_RAM_TUNE	0x3
#define MXT_SELFCMD_RAM_FINE	0x4
#define MXT_SELFCMD_STORE	0x5
#define MXT_SELFCMD_BG_TUNE	0x6

/* Command to unlock bootloader */
#define MXT_UNLOCK_CMD_MSB	0xaa
#define MXT_UNLOCK_CMD_LSB	0xdc

#define I2C_ACCESS_R_REG_FIXED   (1 << 0)   //don't mov reg address if read len is too long
#define I2C_ACCESS_NO_REG   (1 << 4)  // no reg address, directly access i2c reg
#define I2C_ACCESS_NO_CACHE   (1 << 5)  //no dma cache need

/* Bootloader mode status */
#define MXT_WAITING_BOOTLOAD_CMD	0xc0	/* valid 7 6 bit only */
#define MXT_WAITING_FRAME_DATA	0x80	/* valid 7 6 bit only */
#define MXT_FRAME_CRC_CHECK	0x02
#define MXT_FRAME_CRC_FAIL	0x03
#define MXT_FRAME_CRC_PASS	0x04
#define MXT_APP_CRC_FAIL	0x40	/* valid 7 8 bit only */
#define MXT_BOOT_STATUS_MASK	0x3f
#define MXT_BOOT_EXTENDED_ID	(1 << 5)
#define MXT_BOOT_ID_MASK	0x1f

#define PID_MAGIC_WORD0 64
#define PID_MAGIC_WORD1 0

#define MISC_PDS_HEAD_LEN 2
#define MISC_PDS_DATA_LEN 11

/* Touchscreen absolute values */
#define MXT_MAX_AREA		0xff

/*SYNC detect**/
#define MAX_HSYN_MASK 0x02
#define MXT_T124_VSYNC_MASK   0x02
#define MXT_SYNC_OK     0
#define MXT_SYNC_LOST 1


#ifdef ROI
#define MXT_T6_DEBUG_PEAKREGIONDATA	0x3A
#define MISC_PEAKDATA_LEN_U16 (7*7)
#define MISC_PEAKDATA_LEN_U8 (7*7*2)
static unsigned char roi_data[ROI_DATA_READ_LENGTH] = {0};

#define MXT_T6_CMD58_ON   1
#define MXT_T6_CMD58_OFF 0
#define MXT_ROI_ROW       7
extern int gMxtT6Cmd58Flag;
#endif

#define MXT_FEATURE_DISABLE 0
#define MXT_FEATURE_ENABLE  1
#define MXT_FEATURE_SETERROR 255

#define MAX_GLOVE_CONF 0
#define MAX_COVER_CONF 1
#define MAX_WAKEUP_CONF 2
#define MAX_GUESTURE_CONF 3
#define MAX_KNUCKLE_CONF 4
#define MAX_WORKAROUND1_CONF 5
#define MAX_WORKAROUND2_CONF 6
#define MAX_WORKAROUND3_CONF 7
#define MAX_WORKAROUND4_CONF 8
#define MAX_WORKAROUND5_CONF 9
#define MAX_WORKAROUND6_CONF 10

#define MAX_MODULE_NAME_LEN 32
#define MAX_DESCRIPTION_LEN 32
#define MAX_HARDWARE_TEST_RESULT_LEN 200


#define MAX_REG_DATA_LEN 16
#define FLAG_REG_DATA_IN_EXT_BUF (1<<30)
#define T72_NOISELEVEL_SAMPLECOUNT 10
#define MXT_T72_PROCESS_TIMEOUT 20

enum {
	MXT_RESERVED_T0 = 0,
	MXT_RESERVED_T1,
	MXT_DEBUG_DELTAS_T2,
	MXT_DEBUG_REFERENCES_T3,
	MXT_DEBUG_SIGNALS_T4,
	MXT_GEN_MESSAGEPROCESSOR_T5,
	MXT_GEN_COMMANDPROCESSOR_T6,
	MXT_GEN_POWERCONFIG_T7,
	MXT_GEN_ACQUISITIONCONFIG_T8,
	MXT_TOUCH_MULTITOUCHSCREEN_T9,
	MXT_TOUCH_SINGLETOUCHSCREEN_T10,
	MXT_TOUCH_XSLIDER_T11,
	MXT_TOUCH_YSLIDER_T12,
	MXT_TOUCH_XWHEEL_T13,
	MXT_TOUCH_YWHEEL_T14,
	MXT_TOUCH_KEYARRAY_T15,
	MXT_PROCG_SIGNALFILTER_T16,
	MXT_PROCI_LINEARIZATIONTABLE_T17,
	MXT_SPT_COMCONFIG_T18,
	MXT_SPT_GPIOPWM_T19,
	MXT_PROCI_GRIPFACESUPPRESSION_T20,
	MXT_RESERVED_T21,
	MXT_PROCG_NOISESUPPRESSION_T22,
	MXT_TOUCH_PROXIMITY_T23,
	MXT_PROCI_ONETOUCHGESTUREPROCESSOR_T24,
	MXT_SPT_SELFTEST_T25,
	MXT_DEBUG_CTERANGE_T26,
	MXT_PROCI_TWOTOUCHGESTUREPROCESSOR_T27,
	MXT_SPT_CTECONFIG_T28,
	MXT_SPT_GPI_T29,
	MXT_SPT_GATE_T30,
	MXT_TOUCH_KEYSET_T31,
	MXT_TOUCH_XSLIDERSET_T32,
	MXT_RESERVED_T33,
	MXT_GEN_MESSAGEBLOCK_T34,
	MXT_SPT_GENERICDATA_T35,
	MXT_RESERVED_T36,
	MXT_DEBUG_DIAGNOSTIC_T37,
	MXT_SPT_USERDATA_T38,
	MXT_SPARE_T39,
	MXT_PROCI_GRIPSUPPRESSION_T40,
	MXT_SPARE_T41,
	MXT_PROCI_TOUCHSUPPRESSION_T42,
	MXT_SPT_DIGITIZER_T43,
	MXT_SPARE_T44,
	MXT_SPARE_T45,
	MXT_SPT_CTECONFIG_T46,
	MXT_PROCI_STYLUS_T47,
	MXT_PROCG_NOISESUPPRESSION_T48,
	MXT_SPARE_T49,
	MXT_SPARE_T50,
	MXT_SPARE_T51,
	MXT_TOUCH_PROXIMITY_KEY_T52,
	MXT_GEN_DATASOURCE_T53,
	MXT_SPARE_T54,
	MXT_ADAPTIVE_T55,
	MXT_PROCI_SHIELDLESS_T56,
	MXT_PROCI_EXTRATOUCHSCREENDATA_T57,
	MXT_SPARE_T58,
	MXT_SPARE_T59,
	MXT_SPARE_T60,
	MXT_SPT_TIMER_T61,
	MXT_PROCG_NOISESUPPRESSION_T62,
	MXT_PROCI_ACTIVESTYLUS_T63,
	MXT_SPARE_T64,
	MXT_PROCI_LENSBENDING_T65,
	MXT_SPT_GOLDENREFERENCES_T66,
	MXT_SPARE_T67,
	MXT_SPARE_T68,
	MXT_PROCI_PALMGESTUREPROCESSOR_T69,
	MXT_SPT_DYNAMICCONFIGURATIONCONTROLLER_T70,
	MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71,
	MXT_PROCG_NOISESUPPRESSION_T72,
	MXT_PROCI_GLOVEDETECTION_T78 = 78,
	MXT_PROCI_RETRANSMISSIONCOMPENSATION_T80 = 80,
	MXT_PROCI_UNLOCKGESTURE_T81,
	MXT_PROCI_GESTURE_T92 = 92,
	MXT_PROCI_TOUCHSEQUENCELOGGER_T93,
	MXT_TOUCH_SPT_PTC_TUNINGPARAMS_T96 = 96,
	MXT_TOUCH_PTC_KEYS_T97,
	MXT_PROCI_KEYGESTUREPROCESSOR_T99 = 99,
	MXT_TOUCH_MULTITOUCHSCREEN_T100,
	MXT_SPT_TOUCHSCREENHOVER_T101,
	MXT_SPT_SELFCAPHOVERCTECONFIG_T102,
	MXT_PROCI_AUXTOUCHCONFIG_T104 = 104,
	MXT_PROCG_NOISESUPSELFCAP_T108 = 108,
	MXT_SPT_SELFCAPGLOBALCONFIG_T109,
	MXT_SPT_SELFCAPTUNINGPARAMS_T110,
	MXT_SPT_SELFCAPCONFIG_T111,
	MXT_SPT_SELFCAPMEASURECONFIG_T113 = 113,
	MXT_PROCI_SYMBOLGESTURE_T115 = 115,
	MXT_SPT_SYMBOLGESTURECONFIG_T116,
	MXT_SPT_SMARTSCAN_T124 = 124,
	MXT_PROCI_PEAKREGIONDATA_T125 = 125,
	MXT_RESERVED_T255 = 255,
};

/* Each client has this additional data */
struct mxt_info {
	u8 family_id;
	u8 variant_id;
	u8 version;
	u8 build;
	u8 matrix_xsize;
	u8 matrix_ysize;
	u8 object_num;
};

struct mxt_object {
	u8 type;
	u16 start_address;
	u8 size_minus_one;
	u8 instances_minus_one;
	u8 num_report_ids;
} __packed;

struct mxt_config_info {
	u8 self_chgtime_max;
	u8 self_chgtime_min;
};

/* The platform data for the Atmel maXTouch touchscreen driver */
struct mxt_platform_data {
	unsigned long irqflags;
	const u8 *num_keys;  //len is NUM_KEY_TYPE
	const unsigned int (*keymap)[MAX_KEYS_SUPPORTED_IN_DRIVER];

	unsigned long gpio_reset;
	const char *cfg_name;

	const struct mxt_config_info *config_array;
};

struct mxt_refs_delta_data {
	int Average;
	int MaxNum;
	int MinNum;
	int refs_data_Average;
	int refs_data_MaxNum;
	int refs_data_MinNum;
	int deltas_data_Average;
	int deltas_data_MaxNum;
	int deltas_data_MinNum;
};

struct diagnostic_info {
	u8 cmd;
	s8 page;
	u8 index;
	u8 num;  //data length (byte)
};

struct diagnostic_block{
	struct diagnostic_info diag;
	int step;
	int max_step;
	int curr;
	int ext;

	u8 * buf;
	int interval;
	int count;
};

/* MXT_GEN_POWER_T7 field */
struct t7_config {
	u8 idle;
	u8 active;
} __packed;

struct status_count{
	u32 stable_state;
	u32 noise_state;
	u32 vnoise_state;
	u32 moisture_state;
};
struct t72_noise_level{
	u32 total_count;
	u32 success_count;
	u32 noise_level_sum;
	u32 noise_level_avg;
	u32 noise_level_max;
	u32 noise_level_min;
};

struct mxt_feature_extra_data {
	bool cover_cut;
	bool cover_glass;

	u8 glove_sup_h;
	u8 glove_sup_l;

	u8 cover_sup_h;
	u8 cover_sup_l;
};

struct mxt_data {
	struct mxt_refs_delta_data refs_delta_data;
	struct ts_fingers *ts_cache;

	struct mxt_platform_data *pdata;

	struct mxt_object *object_table;
	struct mxt_info *info;
	void *raw_info_block;
	unsigned int max_x;
	unsigned int max_y;
	u8 x_size;
	u8 y_size;
	u8 x_origin;
	u8 y_origin;
	bool in_bootloader;
	u16 mem_size;

	u8 tchcfg[4];

	struct bin_attribute mem_access_attr;
	bool debug_enabled;
	bool debug_v2_enabled;
	u8 *debug_msg_data;
	u16 debug_msg_count;
	struct bin_attribute debug_msg_attr;
	struct mutex debug_msg_lock;
	u8 max_reportid;
	u32 config_crc;
	u32 info_crc;

	u16 addr;
	u16 bootloader_addr;

	struct mutex bus_access_mutex;

	struct t7_config t7_cfg;
	u8 *msg_buf;
	u8 t6_status;
	u8 last_message_count;
	u8 num_touchids;
	u8 num_stylusids;
	unsigned long t15_keystatus;

	struct regulator *reg_vddio;
	struct regulator *reg_avdd;
	bool use_regulator;

	struct pinctrl *pctrl;
	struct pinctrl_state *pins_default;
	struct pinctrl_state *pins_idle;

	char fw_name[128];
	char cfg_name[128];
	unsigned long alt_chip;

	/* Cached parameters from object table */
	u16 T5_address;
	u8 T5_msg_size;
	u8 T6_reportid;
	u16 T6_address;
	u16 T7_address;
	u16 T8_address;
	u16 T9_address;
	u8 T9_reportid_min;
	u8 T9_reportid_max;
	u8 T15_reportid_min;
	u8 T15_reportid_max;
	u16 T15_address;
	u16 T18_address;
	u16 T19_address;
	u8 T19_reportid;
	u8  t19_msg[1];
	u16 T24_address;
	u8 T24_reportid;
	u16 T25_address;
	u8  T25_reportid;
	u8  t25_msg[6];
	u16 T37_address;
	u16 T38_address;
	u16 T40_address;
	u16 T42_address;
	u8 T42_reportid_min;
	u8 T42_reportid_max;
	u16 T44_address;
	u16 T46_address;
	u16 T47_address;
	u8 T48_reportid;
	u16 T55_address;
	u16 T56_address;
	u8 T61_reportid_min;
	u8 T61_reportid_max;
	u16 T61_address;
	u16 T61_instances;
	u8 T63_reportid_min;
	u8 T63_reportid_max;
	u16 T65_address;
	u16 T68_address;
	u8 T68_reportid_min;
	u8 T68_reportid_max;
	u16 T70_address;
	u16 T70_reportid_min;
	u16 T70_reportid_max;
	u16 T71_address;
	u16 T72_address;
	u8 T72_reportid_min;
	u8 T72_reportid_max;
	u16 T78_address;
	u16 T80_address;
	u8 T80_reportid;
	u16 T81_address;
	u8 T81_reportid_min;
	u8 T81_reportid_max;
	u16 T92_address;
	u8 T92_reportid;
	u16 T93_address;
	u8 T93_reportid;
	u8 T97_reportid_min;
	u8 T97_reportid_max;
	u16 T96_address;
	u16 T97_address;
	u16 T99_address;
	u8 T99_reportid;
	u16 T100_address;
	u8 T100_reportid_min;
	u8 T100_reportid_max;
	u16 T102_address;
	u8  T102_reportid;
	u16 T104_address;
	u16 T113_address;
	u16 T115_address;
	u8 T115_reportid;
	u16 T124_address;
	u8 T124_reportid;
	u16 T125_address;
	u8 T125_reportid;
	/* Protect access to the T37 object buffer, used by debugfs */
	struct mutex T37_buf_mutex;
	int *T37_buf;
	size_t T37_buf_size;
	/* for reset handling */
	struct completion reset_completion;

	/* Enable reporting of input events */
	bool enable_reporting;

	/* Indicates whether device is in suspend */
	bool suspended;
	int vsyncstatus;
	int hsyncstatus;
	int t70_msg_processed;
	struct mutex access_mutex;
	u8 roi_data_invert;
	struct ts_device_data *chip_data;
	struct platform_device *ts_dev;
	u8 module_id[MISC_PDS_DATA_LEN];
	u8 module_name[MAX_MODULE_NAME_LEN];
	u8 description[MAX_DESCRIPTION_LEN];

	u8 noise_state;
	int mxt_cur_finger_number;
	int t72_state_change;
	int t72_noise_level_threshold;
	int max_minus_min_limit;
	struct status_count sta_cnt;
	struct t72_noise_level t72_noise_level;
	struct mxt_feature_extra_data feature_extra_data;
};

#define MXT_DRIVER_NEED_UPDATE_MESSAGE 1
struct pds_code{
	u8 head[MISC_PDS_HEAD_LEN];
	u8 id[MISC_PDS_DATA_LEN];
	const char *module_name;
};

struct feature_reg_value
{
	u8 objectId;
	u8 instance;
	u8 offset;
	u8 newvalue;
	u8 oldvalue;
};

struct feature_info
{
	char name[16];
	u8 code;
	u8 reg_num;
	u16 on_flag;
	struct feature_reg_value* reg_value;
};

enum {
	T15_T97_KEY = 0,
	T19_KEY,
	T24_KEY,
	T42_KEY,
	T61_KEY,
	T81_KEY,
	T92_KEY,
	T93_KEY,
	T99_KEY,
	T115_KEY,
	T116_KEY,
	NUM_KEY_TYPE
};

enum f54_rawdata_limit {
	RAW_DATA_UP = 0,
	RAW_DATA_LOW = 1,
	DELT_DATA_UP = 2,
	DELT_DATA_LOW = 3,
	RX_TO_RX_UP = 4,
	RX_TO_RX_LOW = 5,
	TX_TO_TX_UP = 6,
	TX_TO_TX_LOW = 7,
};

struct scr_info {
	u8 status;
	u8 num_tch;
	u16 area_tch;
	u16 area_atch;
	u16 area_inttch;
};

enum{
	MSG_SCRAUX_STATUS = 0,
	MSG_SCRAUX_NUMRPTTCH,
	MSG_SCRAUX_TCHAREA0,
	MSG_SCRAUX_TCHAREA1,
	MSG_SCRAUX_ATCHAREA0,
	MSG_SCRAUX_ATCHAREA1,
	MSG_SCRAUX_INTTHRAREA0,
	MSG_SCRAUX_INTTHRAREA1,
	NUM_MSG_SCRAUX
};

struct ext_info {
	u8 status;
	u8 amp;
	u8 vec;
	u8 area;
	u8 peak;
	u8 width;
	u8 height;
};

#define MAKEWORD(a, b)  ((unsigned short)(((unsigned char)(a)) \
	| ((unsigned short)((unsigned char)(b))) << 8))

extern int mxt_debug_msg_init(struct mxt_data *data);
extern int __mxt_read_reg(struct mxt_data *data, u16 reg, u16 len, void *val);
extern int __mxt_write_reg(struct mxt_data *data, u16 reg, u16 len, const void *val);
extern void mxt_debug_msg_remove(struct mxt_data *data);
extern void mxt_debug_msg_add(struct mxt_data *data, u8 *msg);
extern int mxt_check_firmware_version(struct mxt_data *data);
extern int mxt_update_file_name(struct mxt_data *data, char **file_name);
extern void mxt_update_config_file_name(struct mxt_data *data, char *file_name);
extern void mxt_update_fw_file_name(struct mxt_data *data, char *file_name);
extern int mxt_load_fw(struct mxt_data *data);
extern int mxt_t6_command(struct mxt_data *data, u16 cmd_offset, u8 value, bool wait);
extern int mxt_probe_info_block(struct mxt_data *data);
extern int mxt_bootloader_read(struct mxt_data *data, u8 *val, unsigned int count);
extern int mxt_bootloader_write(struct mxt_data *data, const u8 * const val, unsigned int count);
extern int mxt_lookup_bootloader_address(struct mxt_data *data, bool retry);
extern void mxt_free_object_table(struct mxt_data *data);
extern int mxt_send_bootloader_cmd(struct mxt_data *data, bool unlock);
extern int mxt_update_cfg(struct mxt_data *data);
extern void mxt_free_input_device(struct mxt_data *data);
extern int mxt_T37_fetch(struct mxt_data *data, u8 mode);
extern int process_messages(struct mxt_data *data, int timeout);
extern u32 mxt_calculate_crc(u8 *base, off_t start_off, off_t end_off);
extern int mxt_soft_reset(struct mxt_data *data);
extern void atmel_status_resume(void);
extern int mxt_init_t7_power_cfg(struct mxt_data *data);
extern struct mxt_object *mxt_get_object(struct mxt_data *data, u8 type);
extern int mxt_configure_objects(struct mxt_data *data);
extern int mxt_write_reg(struct mxt_data *data, u16 reg, u8 val);
extern int mxt_mem_access_init(struct mxt_data *data);
extern int get_deltas_data_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern int get_refs_data_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern int get_refs_rx2rx_delta_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern int get_refs_tx2tx_delta_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern int get_refs_max_minus_min_test(struct mxt_data *data, int data_limit);
extern void get_average_max_min_data(struct mxt_data *data, char *buf);
extern int mxt_t25_selftest(struct mxt_data *data);
extern int mxt_diagnostic_command(struct mxt_data *data, u8 cmd, u8 page, u8 index, u8 num, char * buf, int interval, int interval_c);
extern int get_refs_or_deltas_data_test(struct mxt_data *data, int data_uplimit, int data_lowlimit);
extern int mxt_pds_get_data(struct mxt_data *data, struct pds_code *code);
#endif
