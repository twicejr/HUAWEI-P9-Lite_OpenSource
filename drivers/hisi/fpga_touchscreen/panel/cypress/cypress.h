/*
 * Synaptics DSX touchscreen driver
 *
 * Copyright (C) 2012 Synaptics Incorporated
 *
 * Copyright (C) 2012 Alexandra Chin <alexandra.chin@tw.synaptics.com>
 * Copyright (C) 2012 Scott Lin <scott.lin@tw.synaptics.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#define CY_TOUCH_SETTINGS_MAX 32

#include <linux/version.h>
#include <linux/platform_device.h>

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif
#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 38))
#define KERNEL_ABOVE_2_6_38
#endif

#ifdef KERNEL_ABOVE_2_6_38
#define sstrtoul(...) kstrtoul(__VA_ARGS__)
#else
#define sstrtoul(...) strict_strtoul(__VA_ARGS__)
#endif

#if (LINUX_VERSION_CODE > KERNEL_VERSION(3, 7, 0))
#define KERNEL_ABOVE_3_7
#endif


#define CY_ABS_MIN_X 0
#define CY_ABS_MIN_Y 0
#define CY_ABS_MAX_X 720
#define CY_ABS_MAX_Y 1280
#define CY_ABS_MIN_P 0
#define CY_ABS_MAX_P 255
#define CY_ABS_MIN_W 0
#define CY_ABS_MAX_W 255

#define CY_ABS_MIN_T 0

#define CY_ABS_MAX_T 15

/* Command Sizes and expected Return Sizes */

#define CY_CMD_OP_NULL_CMD_SZ	1
#define CY_CMD_OP_NULL_RET_SZ	0
#define CY_CMD_OP_GET_CRC_CMD_SZ	2
#define CY_CMD_OP_GET_CRC_RET_SZ	3

/*
 * 1: Command
 * 1: Parameter ID
 */
#define CY_CMD_OP_GET_PARA_CMD_SZ	2

/*
 * 1: Parameter ID
 * 1: Size of data type
 * 4: read data
 */
#define CY_CMD_OP_GET_PARA_RET_SZ	6

/*
 * 1: Command
 * 1: Parameter ID
 * 1: Size of data type
 * 4: write data
 */
#define CY_CMD_OP_SET_PARA_CMD_SZ	7

/*
 * 1: Command
 * 1: Parameter ID
 */
#define CY_CMD_OP_SET_PARA_RET_SZ	2

/* Command Sizes and expected Return Sizes */
/*
 * 1: Command
 */
#define CY_CMD_CAT_GET_CFG_ROW_SZ_CMD_SZ 1

/*
 * 2: Row Size
 */
#define CY_CMD_CAT_GET_CFG_ROW_SZ_RET_SZ 2

/*
 * 1: Command
 * 2: Offset
 * 2: Length
 * 1: EBID
 */
#define CY_CMD_CAT_READ_CFG_BLK_CMD_SZ 6

/*
 * 1: Complete bit
 * 1: EBID
 * 2: Read Length
 * 1: Reserved
 * N: EBID Row Size
 * 2: CRC
 */
#define CY_CMD_CAT_READ_CFG_BLK_RET_SZ 7
#define CY_CMD_CAT_READ_CFG_BLK_RET_HDR_SZ 5

/*
 * 1: Command
 */
#define CY_CMD_CAT_EXEC_SCAN_CMD_SZ 1
#define CY_CMD_OP_HAND_DETECT_CMD_SZ 1

/*
 * 1: Status
 */
#define CY_CMD_CAT_EXEC_SCAN_RET_SZ 1
#define CY_CMD_OP_HAND_DETECT_RET_SZ 1

/*
 * 1: Command
 * 2: Read offset
 * 2: Num Element
 * 1: Data ID
 */
#define CY_CMD_CAT_RET_PANEL_DATA_CMD_SZ 6

/*
 * 1: Status
 * 1: Data ID
 * 2: Num Element
 * 1: Data ID
 */
#define CY_CMD_CAT_RET_PANEL_DATA_RET_SZ 5


#define CY_FW_FILE_NAME "cyttsp4_fw.bin"

#define CY_MAX_PRBUF_SIZE           PIPE_BUF
#define CY_PR_TRUNCATED             " truncated..."

#define CY_DEFAULT_CORE_ID          "main_ttsp_core"
#define CY_MAX_NUM_CORE_DEVS        5

#define CY_TMA1036_TCH_REC_SIZE     6
#define CY_TMA4XX_TCH_REC_SIZE      9
#define CY_MAX_TCH 0x1E

#define GET_HSTMODE(reg)            ((reg & 0x70) >> 4)
#define GET_TOGGLE(reg)             ((reg & 0x80) >> 7)
#define IS_BOOTLOADER(reg)          ((reg) == 0x01)
#define IS_EXCLUSIVE(dev)           ((dev) != NULL)
#define IS_TMO(t)                   ((t) == 0)

#define IS_LITTLEENDIAN(reg)        ((reg & 0x01) == 1)
#define GET_PANELID(reg)        (reg & 0x07)

#define CY_REG_BASE                 0x00
#define CY_NUM_REVCTRL              8
#define CY_NUM_TCHREC               10
#define CY_NUM_DDATA                32
#define CY_NUM_MDATA                64

#define CY_REG_CAT_CMD              2
#define CY_CMD_COMPLETE_MASK        (1 << 6)
#define CY_CMD_MASK                 0x3F

#define CY_TTCONFIG_OFFSET          8

#define CY_NORMAL_ORIGIN 0	/* upper, left corner */
#define CY_INVERT_ORIGIN 1	/* lower, right corner */

/*loader fw*/
#define CY_CMD_I2C_ADDR					0
	/* Timeout in ms. */
#define CY_CMD_LDR_INIT_TIMEOUT				10000
#define CY_CMD_TIMEOUT					500

#define CY_LDR_REQUEST_EXCLUSIVE_TIMEOUT		5000
#define CY_LDR_CALIBRATE_COMMAND_TIMEOUT		5000
#define CY_STATUS_SIZE_BYTE				1
#define CY_STATUS_TYP_DELAY				2
#define CY_CMD_TAIL_LEN					3
#define CY_CMD_BYTE					1
#define CY_STATUS_BYTE					1
#define CY_MAX_STATUS_SIZE				32
#define CY_MIN_STATUS_SIZE				5
#define CY_START_OF_PACKET				0x01
#define CY_END_OF_PACKET				0x17
#define CY_DATA_ROW_SIZE				288
#define CY_DATA_ROW_SIZE_TMA400				128
#define CY_PACKET_DATA_LEN				96
#define CY_MAX_PACKET_LEN				512
#define CY_COMM_BUSY					0xFF
#define CY_CMD_BUSY					0xFE
#define CY_SEPARATOR_OFFSET				0
#define CY_ARRAY_ID_OFFSET				0
#define CY_ROW_NUM_OFFSET				1
#define CY_ROW_SIZE_OFFSET				3
#define CY_ROW_DATA_OFFSET				5
#define CY_FILE_SILICON_ID_OFFSET			0
#define CY_FILE_REV_ID_OFFSET				4
#define CY_CMD_LDR_HOST_SYNC				0xFF /* tma400 */
#define CY_CMD_LDR_EXIT					0x3B
#define CY_CMD_LDR_EXIT_CMD_SIZE			7
#define CY_CMD_LDR_EXIT_STAT_SIZE			7
#define CY_CMD_LDR_ENTER				0x38
#define CY_CMD_LDR_ENTER_CMD_SIZE			7
#define CY_CMD_LDR_ENTER_STAT_SIZE			15
#define CY_CMD_LDR_INIT					0x48
#define CY_CMD_LDR_INIT_CMD_SIZE			15
#define CY_CMD_LDR_INIT_STAT_SIZE			7
#define CY_CMD_LDR_ERASE_ROW				0x34
#define CY_CMD_LDR_ERASE_ROW_CMD_SIZE			10
#define CY_CMD_LDR_ERASE_ROW_STAT_SIZE			7
#define CY_CMD_LDR_SEND_DATA				0x37
#define CY_CMD_LDR_SEND_DATA_CMD_SIZE			4 /* hdr bytes only */
#define CY_CMD_LDR_SEND_DATA_STAT_SIZE			8
#define CY_CMD_LDR_PROG_ROW				0x39
#define CY_CMD_LDR_PROG_ROW_CMD_SIZE			7 /* hdr bytes only */
#define CY_CMD_LDR_PROG_ROW_STAT_SIZE			7
#define CY_CMD_LDR_VERIFY_ROW				0x3A
#define CY_CMD_LDR_VERIFY_ROW_STAT_SIZE			8
#define CY_CMD_LDR_VERIFY_ROW_CMD_SIZE			10
#define CY_CMD_LDR_VERIFY_CHKSUM			0x31
#define CY_CMD_LDR_VERIFY_CHKSUM_CMD_SIZE		7
#define CY_CMD_LDR_VERIFY_CHKSUM_STAT_SIZE		8

enum cypress_ic_ebid {
	CY_TCH_PARM_EBID,
	CY_MDATA_EBID,
	CY_DDATA_EBID,
	CY_EBID_NUM,
};
enum cyttsp4_signal_disparity {
	CY_SIGNAL_DISPARITY_NONE,
	CY_SIGNAL_DISPARITY_SENSITIVITY,
	CY_SIGNAL_DISPARITY_STYLUS,
	CY_SIGNAL_DISPARITY_PROXIMITY,
	CY_SIGNAL_DISPARITY_MAX,
};

enum cyttsp4_holster_mode_switch {
	CY_HOLSTER_OFF_LOW,
	CY_HOLSTER_ON_HIGH,
};


/* touch record system information offset masks and shifts */
#define CY_BYTE_OFS_MASK            0x1F
#define CY_BOFS_MASK                0xE0
#define CY_BOFS_SHIFT               5

/* maximum number of concurrent tracks */
#define CY_NUM_TCH_ID               10

#define CY_ACTIVE_STYLUS_ID         10

/* helpers */
#define GET_NUM_TOUCHES(x)          ((x) & 0x1F)
#define IS_LARGE_AREA(x)            ((x) & 0x20)
#define IS_BAD_PKT(x)               ((x) & 0x20)

/* Timeout in ms. */
#define CY_COMMAND_COMPLETE_TIMEOUT	100
#define CY_WATCHDOG_TIMEOUT		1000

/* drv_debug commands */
#define CY_DBG_SUSPEND                  4
#define CY_DBG_RESUME                   5
#define CY_DBG_SOFT_RESET               97
#define CY_DBG_RESET                    98

enum cypress_cmd_status {
	CY_CMD_STATUS_SUCCESS,
	CY_CMD_STATUS_FAILURE,
};

enum cypress_hst_mode_bits {
	CY_HST_TOGGLE      = (1 << 7),
	CY_HST_MODE_CHANGE = (1 << 3),
	CY_HST_MODE        = (7 << 4),
	CY_HST_OPERATE     = (0 << 4),
	CY_HST_SYSINFO     = (1 << 4),
	CY_HST_CAT         = (2 << 4),
	CY_HST_LOWPOW      = (1 << 2),
	CY_HST_SLEEP       = (1 << 1),
	CY_HST_RESET       = (1 << 0),
};

enum cypress_cmd_bits {
	CY_CMD_COMPLETE    = (1 << 6),
};

enum cypress_cmd_operate {
	CY_CMD_OP_NULL,
	CY_CMD_OP_RESERVED_1,
	CY_CMD_OP_GET_PARA,
	CY_CMD_OP_SET_PARA,
	CY_CMD_OP_RESERVED_2,
	CY_CMD_OP_GET_CRC,
	CY_CMD_OP_RESERVED_3,
	HANDEDNESS_DETECTION,
	HANDEDNESS_DETECTION_INIT,
	CY_CMD_OP_RESERVED_N,
};

#define CY_OP_PARA_SCAN_TYPE			0x4B
#define CY_OP_PARA_FINGER_THRESHOLD		0x53


#define CY_OP_PARA_HOLSTER              0x5A
#define CY_OP_PARA_HOLSTER_SZ           0x01
#define CY_OP_PARA_HOLSTER_COM_ON       0x01
#define CY_OP_PARA_HOLSTER_COM_OFF      0x02



#define CY_OP_PARA_SCAN_TYPE_SZ			1
#define CY_OP_PARA_FINGER_THRESHOLD_SZ		2

#define CY_OP_PARA_FINGER_THRESHOLD_MIN_VAL	1
#define CY_OP_PARA_FINGER_THRESHOLD_MAX_VAL	2000

#define CY_OP_PARA_SCAN_TYPE_NORMAL		0
#define CY_OP_PARA_SCAN_TYPE_GLOVE_MASK	(1<<3)
#define CY_OP_PARA_SCAN_TYPE_STYLUS_MASK	(1<<4)
#define CY_OP_PARA_SCAN_TYPE_HOVER_MASK		(1<<5)
#define CY_OP_PARA_SCAN_TYPE_PROXIMITY_MASK	(1<<6)
#define CY_OP_PARA_SCAN_TYPE_APAMC_MASK		(1<<7)


#define CY_NUM_TCH_FIELDS       7
#define CY_NUM_EXT_TCH_FIELDS   3

/* abs settings */
#define CY_IGNORE_VALUE             0xFFFF

enum cypress_tt_mode_bits {
	CY_TT_BL     = (1 << 4),
	CY_TT_INVAL  = (1 << 5),
	CY_TT_CNTR   = (3 << 6),
};

enum cypress_bl_status_bits {
	CY_BL_CS_OK    = (1 << 0),
	CY_BL_WDOG     = (1 << 1),
	CY_BL_RUNNING  = (1 << 4),
	CY_BL_BUSY     = (1 << 7),
};

enum cypress_int_state {
	CY_INT_NONE,
	CY_INT_IGNORE      = (1 << 0),
	CY_INT_MODE_CHANGE = (1 << 1),
	CY_INT_EXEC_CMD    = (1 << 2),
	CY_INT_AWAKE       = (1 << 3),
};

enum cypress_ic_grpnum {
	CY_IC_GRPNUM_RESERVED,
	CY_IC_GRPNUM_CMD_REGS,
	CY_IC_GRPNUM_TCH_REP,
	CY_IC_GRPNUM_DATA_REC,
	CY_IC_GRPNUM_TEST_REC,
	CY_IC_GRPNUM_PCFG_REC,
	CY_IC_GRPNUM_TCH_PARM_VAL,
	CY_IC_GRPNUM_TCH_PARM_SIZE,
	CY_IC_GRPNUM_RESERVED1,
	CY_IC_GRPNUM_RESERVED2,
	CY_IC_GRPNUM_OPCFG_REC,
	CY_IC_GRPNUM_DDATA_REC,
	CY_IC_GRPNUM_MDATA_REC,
	CY_IC_GRPNUM_TEST_REGS,
	CY_IC_GRPNUM_BTN_KEYS,
	CY_IC_GRPNUM_TTHE_REGS,
	CY_IC_GRPNUM_NUM
};

enum ldr_status {
	ERROR_SUCCESS = 0,
	ERROR_COMMAND = 1,
	ERROR_FLASH_ARRAY = 2,
	ERROR_PACKET_DATA = 3,
	ERROR_PACKET_LEN = 4,
	ERROR_PACKET_CHECKSUM = 5,
	ERROR_FLASH_PROTECTION = 6,
	ERROR_FLASH_CHECKSUM = 7,
	ERROR_VERIFY_IMAGE = 8,
	ERROR_UKNOWN1 = 9,
	ERROR_UKNOWN2 = 10,
	ERROR_UKNOWN3 = 11,
	ERROR_UKNOWN4 = 12,
	ERROR_UKNOWN5 = 13,
	ERROR_UKNOWN6 = 14,
	ERROR_INVALID_COMMAND = 15,
	ERROR_INVALID
};

enum cypress_flags {
	CY_FLAG_NONE = 0x00,
	CY_FLAG_HOVER = 0x04,
	CY_FLAG_FLIP = 0x08,
	CY_FLAG_INV_X = 0x10,
	CY_FLAG_INV_Y = 0x20,
	CY_FLAG_VKEYS = 0x40,
	CY_FLAG_REPORT_ON_LO = 0x80,
};

enum cypress_loader_flags {
	CY_FLAG_LOAD_NONE = 0x00,
	CY_FLAG_AUTO_CALIBRATE = 0x01,
};

enum cypress_event_id {
	CY_EV_NO_EVENT,
	CY_EV_TOUCHDOWN,
	CY_EV_MOVE,		/* significant displacement (> act dist) */
	CY_EV_LIFTOFF,		/* record reports last position */
};

enum cypress_object_id {
	CY_OBJ_STANDARD_FINGER,
	CY_OBJ_LARGE_OBJECT,
	CY_OBJ_STYLUS,
	CY_OBJ_RESERVED,			// CHNQ added +
	CY_OBJ_HOVER,
};

#define CY_POST_CODEL_WDG_RST           0x01
#define CY_POST_CODEL_CFG_DATA_CRC_FAIL 0x02
#define CY_POST_CODEL_PANEL_TEST_FAIL   0x04

#define CY_TEST_CMD_NULL                0

struct touch_framework {
	const uint16_t  *abs;
	uint8_t         size;
	uint8_t         enable_vkeys;
} __packed;

/* test mode NULL command driver codes; D */
enum cypress_null_test_cmd_code {
	CY_NULL_CMD_NULL,
	CY_NULL_CMD_MODE,
	CY_NULL_CMD_STATUS_SIZE,
	CY_NULL_CMD_HANDSHAKE,
	CY_NULL_CMD_LOW_POWER,
};

enum cypress_test_mode {
	CY_TEST_MODE_NORMAL_OP,		/* Send touch data to OS; normal op */
	CY_TEST_MODE_CAT,		/* Configuration and Test */
	CY_TEST_MODE_SYSINFO,		/* System information mode */
	CY_TEST_MODE_CLOSED_UNIT,	/* Send scan data to sysfs */
};

struct cypress_test_mode_params {
	int cur_mode;
	int cur_cmd;
	size_t cur_status_size;
};

enum cypress_tch_abs {	/* for ordering within the extracted touch data array */
	CY_TCH_X,	/* X */
	CY_TCH_Y,	/* Y */
	CY_TCH_P,	/* P (Z) */
	CY_TCH_T,	/* TOUCH ID */
	CY_TCH_E,	/* EVENT ID */
	CY_TCH_O,	/* OBJECT ID */
	CY_TCH_W,	/* SIZE */
	CY_TCH_MAJ,	/* TOUCH_MAJOR */
	CY_TCH_MIN,	/* TOUCH_MINOR */
	CY_TCH_OR,	/* ORIENTATION */
	CY_TCH_NUM_ABS
};

struct cypress_test {
	u8 post_codeh;
	u8 post_codel;
} __packed;

struct cypress_tch_rec_params {
	u8 loc;
	u8 size;
} __packed;

struct cypress_pcfg {
	u8 electrodes_x;
	u8 electrodes_y;
	u8 len_xh;
	u8 len_xl;
	u8 len_yh;
	u8 len_yl;
	u8 res_xh;
	u8 res_xl;
	u8 res_yh;
	u8 res_yl;
	u8 max_zh;
	u8 max_zl;
	u8 panel_info0;
} __packed;

struct cypress_opcfg {
	u8 cmd_ofs;
	u8 rep_ofs;
	u8 rep_szh;
	u8 rep_szl;
	u8 num_btns;
	u8 tt_stat_ofs;
	u8 obj_cfg0;
	u8 max_tchs;
	u8 tch_rec_size;
	struct cypress_tch_rec_params tch_rec_old[CY_NUM_TCH_FIELDS];  //2*7
	u8 btn_rec_size;/* btn record size (in bytes) */
	u8 btn_diff_ofs;/* btn data loc ,diff counts, (Op-Mode byte ofs) */
	u8 btn_diff_size;/* btn size of diff counts (in bits) */
	struct cypress_tch_rec_params tch_rec_new[CY_NUM_EXT_TCH_FIELDS]; //2*3
} __packed;

struct cypress_sysinfo_data {
	u8 hst_mode;
	u8 reserved;
	u8 map_szh;
	u8 map_szl;
	u8 cydata_ofsh;
	u8 cydata_ofsl;
	u8 test_ofsh;
	u8 test_ofsl;
	u8 pcfg_ofsh;
	u8 pcfg_ofsl;
	u8 opcfg_ofsh;
	u8 opcfg_ofsl;
	u8 ddata_ofsh;
	u8 ddata_ofsl;
	u8 mdata_ofsh;
	u8 mdata_ofsl;
} __packed;


struct cypress_touch {
	int abs[CY_TCH_NUM_ABS];
};

struct cypress_tch_abs_params {
	size_t ofs;	/* offset (in bytes) of abs(X, Y, ...) field from the record start, bit4-bit0*/
	size_t size;	/* size of the X abs field(X, Y, ...) (in bits)*/
	size_t max;	/* max value */
	size_t bofs;	/* bit offset */
};

static const char * const cypress_tch_abs_string[] = {
	[CY_TCH_X]	= "X",
	[CY_TCH_Y]	= "Y",
	[CY_TCH_P]	= "P",
	[CY_TCH_T]	= "T",
	[CY_TCH_E]	= "E",
	[CY_TCH_O]	= "O",
	[CY_TCH_W]	= "W",
	[CY_TCH_MAJ]	= "MAJ",
	[CY_TCH_MIN]	= "MIN",
	[CY_TCH_OR]	= "OR",
	[CY_TCH_NUM_ABS] = "INVALID"
};

struct cypress_sysinfo_merged_data {
	size_t chip_type;
	size_t cmd_ofs;		/*offset of the COMMAND register in the Operating Mode register map (in bytes)*/
	size_t rep_ofs;		/*offset of the REP_LEN register in the Operating Mode register map*/
	size_t rep_sz;			/*maximum size (in bytes) of the touch report in the Operating Mode register map*/
	size_t tt_stat_ofs;	/*offset (in bytes) of the TT_STAT register in the Operating Mode register map */
	size_t tch_rec_size;	/*size (in bytes) of each touch record, bit4-bit0*/
	size_t max_tchs;		/*maximum number of touches to be reported to the host*/
	size_t mode_size;		/*mode size in operation register map*/
	size_t data_size;		/*touch recoard data in operation register map*/
	size_t map_sz;		/*system information map size (in bytes)*/
	size_t max_x;		/* x-axis resolution (in pixels)*/
	size_t x_origin;		/* left or right corner */
	size_t max_y;		/* y-axis resolution (in pixels)*/
	size_t y_origin;		/* upper or lower corner */
	size_t max_p;
	size_t cydata_ofs;		/*cydata register addr offset (in bytes)*/
	size_t test_ofs;		/*test register addr offset (in bytes)*/
	size_t pcfg_ofs;		/*pcfg register addr offset (in bytes)*/
	size_t opcfg_ofs;		/*opcfg register addr offset (in bytes)*/
	size_t ddata_ofs;		/*not used yet, customer specified design data (in bytes)*/
	size_t mdata_ofs;		/*not used yet, customer-specified manufacturing test data (in bytes)*/
	struct cypress_tch_abs_params tch_abs[CY_TCH_NUM_ABS];
};
struct cypress_ttconfig {
	u16 version;
	u16 length;
	u16 max_length;
	u16 crc;
};

struct cypress_cydata {		//version information
	u8 ttpidh;					/*MSB of TrueTouch Product ID for each cypress family of controllers*/
	u8 ttpidl;					/*LSB of TrueTouch Product ID for each cypress family of controllers*/
	u8 fw_ver_major;			/*major version of firmware*/
	u8 fw_ver_minor;			/*minor version of firmware*/
	u8 revctrl[CY_NUM_REVCTRL];	/*cypress version control number: 8 registers*/
	u8 blver_major;				/*major version number of the TrueTouch bootloader program*/
	u8 blver_minor;				/*minor version number of the TrueTouch bootloader program*/
	u8 jtag_si_id3;			
	u8 jtag_si_id2;
	u8 jtag_si_id1;
	u8 jtag_si_id0;
	u8 mfgid_sz;					/*size of the Cypress manufacturing ID*/
	u8 *mfg_id;					/*manufacturing ID, length not sure*/
	u8 cyito_idh;
	u8 cyito_idl;
	u8 cyito_verh;
	u8 cyito_verl;
	u8 ttsp_ver_major;
	u8 ttsp_ver_minor;
	u8 device_info;				/*device information bits*/
} __packed;

struct cypress_dev_id {
	u32 silicon_id;
	u8 rev_id;
	u32 bl_ver;
};

struct touch_settings {
	const uint8_t   *data;
	uint32_t         size;
	uint8_t         tag;
} __packed;

struct cypress_hex_image {
	u8 array_id;
	u16 row_num;
	u16 row_size;
	u8 row_data[CY_DATA_ROW_SIZE];
} __packed;

struct cypress_sysinfo_ptr {
	struct cypress_cydata cydata;
	struct cypress_pcfg pcfg;
	struct cypress_opcfg opcfg;
} __packed;

enum cypress_cmd_cat {
	CY_CMD_CAT_NULL,
	CY_CMD_CAT_RESERVED_1,
	CY_CMD_CAT_GET_CFG_ROW_SZ,
	CY_CMD_CAT_READ_CFG_BLK,
	CY_CMD_CAT_WRITE_CFG_BLK,
	CY_CMD_CAT_RESERVED_2,
	CY_CMD_CAT_LOAD_SELF_TEST_DATA,
	CY_CMD_CAT_RUN_SELF_TEST,
	CY_CMD_CAT_GET_SELF_TEST_RESULT,
	CY_CMD_CAT_CALIBRATE_IDACS,
	CY_CMD_CAT_INIT_BASELINES,
	CY_CMD_CAT_EXEC_PANEL_SCAN,
	CY_CMD_CAT_RETRIEVE_PANEL_SCAN,
	CY_CMD_CAT_START_SENSOR_DATA_MODE,
	CY_CMD_CAT_STOP_SENSOR_DATA_MODE,
	CY_CMD_CAT_INT_PIN_MODE,
	CY_CMD_CAT_RETRIEVE_DATA_STRUCTURE,
	CY_CMD_CAT_VERIFY_CFG_BLK_CRC,
	CY_CMD_CAT_RESERVED_N,
};

enum scanDataTypeList {
	CY_MUT_RAW,
	CY_MUT_BASE,
	CY_MUT_DIFF,
	CY_SELF_RAW,
	CY_SELF_BASE,
	CY_SELF_DIFF,
	CY_BAL_RAW,
	CY_BAL_BASE,
	CY_BAL_DIFF,
};
enum check_data_type{
	CY_CHK_MUT_RAW,
	CY_CHK_SELF_RAW,
	CY_CHK_MUT_IDAC,
	CY_CHK_SELF_IDAC,
};
enum FW_UPDATE_STATE{
	FW_UP_INITED = 0,
	FW_UP_ENTER_LDR,
	FW_UP_ENTER_LDR_RESULT,
	FW_UP_LDR_INIT,
	FW_UP_LDR_INT_RESULT,
	FW_UP_ROW_PRO,
	FW_UP_ROW_PRO_RESULT,
	FW_UP_ROW_VERIFY,
	FW_UP_ROW_VERIFY_RESULT,
	FW_UP_ROW_PROG_OR_CHECKSUM,
	FW_UP_CHECKSUM,
	FW_UP_CHECKSUM_RESULT,
	FW_UP_BL_EXIT,
	FW_UP_BL_EXIT_RESULT,
	FW_UP_SUC,
	FW_UP_FAIL = 0XFF,
};

struct heatmap_param {
	bool scan_start;
	enum scanDataTypeList dataType; /* raw, base, diff */
	int numElement;
};

enum cypress_opmode {
	OPMODE_NONE,
	OPMODE_FINGER,
	OPMODE_GLOVE,
};

struct cypress_sysinfo {
	struct cypress_sysinfo_data sysinfo_data;		/*register map from 00h to 0Fh: 16 registers*/
	struct cypress_cydata cydata;				/*register map from CYDATA_OFS to TEST_OFS-1*/
	struct cypress_test test;
	struct cypress_pcfg pcfg;					/*register map from PCFG_OFS to PCFG_OFS+0Ch: 13 registers*/
	struct cypress_opcfg opcfg;					/*register map from OPCFG_OFS to OPCFG_OFS+1Fh: 32 registers*/
	struct cypress_sysinfo_merged_data sysinfo_merged_data;
	struct cypress_ttconfig ttconfig;
	u8 *xy_mode;			/* operational mode and status regs */
	u8 *xy_data;			/* operational touch regs */
};

struct cypress_grpdata {
	uint32_t ic_grpnum;
	uint32_t ic_grpoffset;
	u8 ic_buf[1024];
	u8 return_buf[1024];
	struct heatmap_param heatmap;
};

struct cypress_loader_data {
	u8 status_buf[CY_MAX_STATUS_SIZE];
	struct cypress_dev_id *dev_id;
	struct cypress_hex_image *row_image;
	u8 *row_buf;
	size_t image_rec_size;
	size_t row_buf_size;
};

enum cypress_process_state {
    CY_STATE_INIT = 0,
    CY_STATE_FW_UPDATE = 1,
    CY_STATE_NORMAL = 2,
};

struct cypress_core_data {
	struct ts_device_data *cypress_chip_data;
	struct platform_device *cypress_dev;
	struct input_dev *input;
	struct cypress_loader_data ld;
	struct cypress_grpdata rawdate;
	enum cypress_opmode opmode;
	struct cypress_sysinfo sysinfo;
	bool complete_cmd;
	enum cypress_process_state process_state;
	bool force_fw_update;
	struct regulator *vdd;
	struct regulator *vbus;
};

