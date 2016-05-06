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
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/hisi/hisi_fpga_touchscreen.h>

#define RED_REMOTE
#define X_RES	1080
#define Y_RES	1920

#define GLOVE_SWITCH_ON 1
#define GLOVE_SWITCH_OFF 0
#define FHD_LCD_WIDTH  1080
#define FHD_LCD_HIGHT  1920
#define FHD_LCD_JISUAN  2088

#ifndef _SYNAPTICS_DSX_RMI4_H_
#define _SYNAPTICS_DSX_RMI4_H_

#define SYNAPTICS_DS4 (1 << 0)
#define SYNAPTICS_DS5 (1 << 1)
#define SYNAPTICS_DSX_DRIVER_PRODUCT SYNAPTICS_DS4
#define SYNAPTICS_DSX_DRIVER_VERSION 0x1006
#define SYNAPTICS_BUILD_ID_NO 3
#define SYNAPTICS_IC_NAME_NO 2

#include <linux/version.h>
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

#define REPORT_2D_W
#define REPORT_2D_Z

#define PDT_PROPS (0x00EF)
#define PDT_START (0x00E9)
#define PDT_END (0x000A)
#define PDT_ENTRY_SIZE (0x0006)
#define PAGES_TO_SERVICE (10)
#define PAGE_SELECT_LEN (2)

#define SYNAPTICS_RMI4_F01 (0x01)
#define SYNAPTICS_RMI4_F11 (0x11)
#define SYNAPTICS_RMI4_F12 (0x12)
#define SYNAPTICS_RMI4_F1A (0x1a)
#define SYNAPTICS_RMI4_F34 (0x34)
#define SYNAPTICS_RMI4_F35 (0x35)
#define SYNAPTICS_RMI4_F51 (0x51)
#define SYNAPTICS_RMI4_F54 (0x54)
#define SYNAPTICS_RMI4_F55 (0x55)

#define SYNAPTICS_RMI4_DATE_CODE_SIZE 3
#define SYNAPTICS_RMI4_PRODUCT_INFO_SIZE 2
#define SYNAPTICS_RMI4_PRODUCT_ID_SIZE 10
#define SYNAPTICS_RMI4_PROJECT_ID_SIZE SYNAPTICS_RMI4_PRODUCT_ID_SIZE
#define SYNAPTICS_RMI4_BUILD_ID_SIZE 3
#define SYNAPTICS_RMI4_IC_NAME_SIZE 2
#define SYNAPTICS_RMI4_CAP_DATA_SIZE 1024

#define MAX_NUMBER_OF_FINGERS 10
#define MAX_NUMBER_OF_BUTTONS 4
#define MAX_INTR_REGISTERS 4

#define MASK_16BIT 0xFFFF
#define MASK_8BIT 0xFF
#define MASK_7BIT 0x7F
#define MASK_6BIT 0x3F
#define MASK_5BIT 0x1F
#define MASK_4BIT 0x0F
#define MASK_3BIT 0x07
#define MASK_2BIT 0x03
#define MASK_1BIT 0x01

#define RMI4_END_OF_PDT(id) ((id) == 0x00 || (id) == 0xff)
#define F12_FINGERS_TO_SUPPORT 10
#define cherry_glove_enable_addr 0x0419
#define cherry_guesture_pattern_addr 0x0418
#define cherry_palm_status_addr 0x004a
#define PALM_COVER_SLEEP 2
#define PALM_COVER_SLEEP_S3320 3
#define PALM_COVER_NOSLEEP 0

/**
 * struct synaptics_rmi4_platform_data - contains the rmi4 platform data
 * @irq_number: irq number
 * @irq_type: irq type
 * @x flip: x flip flag
 * @y flip: y flip flag
 * @regulator_en: regulator enable flag
 *
 * This structure gives platform data for rmi4.
 */
struct synaptics_rmi4_platform_data {
	int irq_number;
	int irq_type;
	bool x_flip;
	bool y_flip;
	bool regulator_en;
};

/**
 * struct rmi_function_descriptor - RMI function base addresses
 * @query_base_addr: The RMI Query base address
 * @command_base_addr: The RMI Command base address
 * @control_base_addr: The RMI Control base address
 * @data_base_addr: The RMI Data base address
 * @interrupt_source_count: The number of irqs this RMI function needs
 * @function_number: The RMI function number
 *
 * This struct is used when iterating the Page Description Table. The addresses
 * are 16-bit values to include the current page address.
 *
 */
struct rmi_function_descriptor {
	u16 query_base_addr;
	u16 command_base_addr;
	u16 control_base_addr;
	u16 data_base_addr;
	u8 interrupt_source_count;
	u8 function_number;
	u8 function_version;
};

/*
 * struct synaptics_rmi4_fn_desc - function descriptor fields in PDT
 * @query_base_addr: base address for query registers
 * @cmd_base_addr: base address for command registers
 * @ctrl_base_addr: base address for control registers
 * @data_base_addr: base address for data registers
 * @intr_src_count: number of interrupt sources
 * @fn_number: function number
 */
struct synaptics_rmi4_fn_desc {
	union {
		struct {
			unsigned char query_base_addr;
			unsigned char cmd_base_addr;
			unsigned char ctrl_base_addr;
			unsigned char data_base_addr;
			unsigned char intr_src_count:3;
			unsigned char reserved_1:2;
			unsigned char fn_version:2;
			unsigned char reserved_2:1;
			unsigned char fn_number;
		} __packed;
		unsigned char data[6];
	};
};

/*
 * synaptics_rmi4_fn_full_addr - full 16-bit base addresses
 * @query_base: 16-bit base address for query registers
 * @cmd_base: 16-bit base address for data registers
 * @ctrl_base: 16-bit base address for command registers
 * @data_base: 16-bit base address for control registers
 */
struct synaptics_rmi4_fn_full_addr {
	unsigned short query_base;
	unsigned short cmd_base;
	unsigned short ctrl_base;
	unsigned short data_base;
};

struct synaptics_rmi4_f12_extra_data {
	unsigned char data1_offset;
	unsigned char data15_offset;
	unsigned char data15_size;
	unsigned char data15_data[(F12_FINGERS_TO_SUPPORT + 7) / 8];
};

/*
 * struct synaptics_rmi4_fn - function handler data structure
 * @fn_number: function number
 * @num_of_data_sources: number of data sources
 * @num_of_data_points: maximum number of fingers supported
 * @size_of_data_register_block: data register block size
 * @data1_offset: offset to data1 register from data base address
 * @intr_reg_num: index to associated interrupt register
 * @intr_mask: interrupt mask
 * @full_addr: full 16-bit base addresses of function registers
 * @link: linked list for function handlers
 * @data_size: size of private data
 * @data: pointer to private data
 */
struct synaptics_rmi4_fn {
	unsigned char fn_number;
	unsigned char num_of_data_sources;
	unsigned char num_of_data_points;
	unsigned char size_of_data_register_block;
	unsigned char data1_offset;
	unsigned char intr_reg_num;
	unsigned char intr_mask;
	struct synaptics_rmi4_fn_full_addr full_addr;
	struct list_head link;
	int data_size;
	void *data;
	void *extra;
};

/*
 * struct synaptics_rmi4_device_info - device information
 * @version_major: rmi protocol major version number
 * @version_minor: rmi protocol minor version number
 * @manufacturer_id: manufacturer id
 * @product_props: product properties information
 * @product_info: product info array
 * @date_code: device manufacture date
 * @tester_id: tester id array
 * @serial_number: device serial number
 * @product_id_string: device product id
 * @support_fn_list: linked list for function handlers
 */
struct synaptics_rmi4_device_info {
	unsigned int version_major;
	unsigned int version_minor;
	unsigned char manufacturer_id;
	unsigned char product_props;
	unsigned char product_info[SYNAPTICS_RMI4_PRODUCT_INFO_SIZE];
	unsigned char date_code[SYNAPTICS_RMI4_DATE_CODE_SIZE];
	unsigned short tester_id;
	unsigned short serial_number;
	unsigned char product_id_string[SYNAPTICS_RMI4_PRODUCT_ID_SIZE + 1];
	unsigned char project_id_string[SYNAPTICS_RMI4_PROJECT_ID_SIZE + 1];
	unsigned char build_id[SYNAPTICS_RMI4_BUILD_ID_SIZE];
	unsigned char ic_name[SYNAPTICS_RMI4_IC_NAME_SIZE];
	unsigned char config_id[4];
	unsigned char synaptics_build_id[SYNAPTICS_BUILD_ID_NO];
	unsigned char synaptics_ic_name[SYNAPTICS_IC_NAME_NO];
	struct list_head support_fn_list;
};

struct synaptics_rmi4_glove {
	unsigned char glove_switch;
	unsigned char offset;
};

struct synaptics_rmi4_holster {
	unsigned char offset;
};

struct synaptics_rmi4_geswakeup{
	u8 palm_switch;
	unsigned char palm_enable_addr;
	unsigned char f12_2d_data01_palm_status;
	unsigned char f12_2d_data04_gesture;
	unsigned char f12_2d_ctrl20_lpm;
	unsigned char f12_2d_ctrl22_palm;
};

struct synaptics_rmi4_pen{
	unsigned char offset;
};

struct synaptics_rmi4_f01_device_status {
	union {
		struct {
			unsigned char status_code:4;
			unsigned char reserved:2;
			unsigned char flash_prog:1;
			unsigned char unconfigured:1;
		} __packed;
		unsigned char data[1];
	};
};

struct synaptics_rmi4_f12_query_5 {
	union {
		struct {
			unsigned char size_of_query6;
			struct {
				unsigned char ctrl0_is_present:1;
				unsigned char ctrl1_is_present:1;
				unsigned char ctrl2_is_present:1;
				unsigned char ctrl3_is_present:1;
				unsigned char ctrl4_is_present:1;
				unsigned char ctrl5_is_present:1;
				unsigned char ctrl6_is_present:1;
				unsigned char ctrl7_is_present:1;
			} __packed;
			struct {
				unsigned char ctrl8_is_present:1;
				unsigned char ctrl9_is_present:1;
				unsigned char ctrl10_is_present:1;
				unsigned char ctrl11_is_present:1;
				unsigned char ctrl12_is_present:1;
				unsigned char ctrl13_is_present:1;
				unsigned char ctrl14_is_present:1;
				unsigned char ctrl15_is_present:1;
			} __packed;
			struct {
				unsigned char ctrl16_is_present:1;
				unsigned char ctrl17_is_present:1;
				unsigned char ctrl18_is_present:1;
				unsigned char ctrl19_is_present:1;
				unsigned char ctrl20_is_present:1;
				unsigned char ctrl21_is_present:1;
				unsigned char ctrl22_is_present:1;
				unsigned char ctrl23_is_present:1;
			} __packed;
			struct {
				unsigned char ctrl24_is_present:1;
				unsigned char ctrl25_is_present:1;
				unsigned char ctrl26_is_present:1;
				unsigned char ctrl27_is_present:1;
				unsigned char ctrl28_is_present:1;
				unsigned char ctrl29_is_present:1;
				unsigned char ctrl30_is_present:1;
				unsigned char ctrl31_is_present:1;
			} __packed;
		};
		unsigned char data[5];
	};
};

struct synaptics_rmi4_f12_query_8 {
	union {
		struct {
			unsigned char size_of_query9;
			struct {
				unsigned char data0_is_present:1;
				unsigned char data1_is_present:1;
				unsigned char data2_is_present:1;
				unsigned char data3_is_present:1;
				unsigned char data4_is_present:1;
				unsigned char data5_is_present:1;
				unsigned char data6_is_present:1;
				unsigned char data7_is_present:1;
			} __packed;
			struct {
				unsigned char data8_is_present:1;
				unsigned char data9_is_present:1;
				unsigned char data10_is_present:1;
				unsigned char data11_is_present:1;
				unsigned char data12_is_present:1;
				unsigned char data13_is_present:1;
				unsigned char data14_is_present:1;
				unsigned char data15_is_present:1;
			} __packed;
		};
		unsigned char data[3];
	};
};

struct synaptics_rmi4_f12_ctrl_8 {
	union {
		struct {
			unsigned char max_x_coord_lsb;
			unsigned char max_x_coord_msb;
			unsigned char max_y_coord_lsb;
			unsigned char max_y_coord_msb;
			unsigned char rx_pitch_lsb;
			unsigned char rx_pitch_msb;
			unsigned char tx_pitch_lsb;
			unsigned char tx_pitch_msb;
			unsigned char low_rx_clip;
			unsigned char high_rx_clip;
			unsigned char low_tx_clip;
			unsigned char high_tx_clip;
			unsigned char num_of_rx;
			unsigned char num_of_tx;
		};
		unsigned char data[14];
	};
};

struct synaptics_rmi4_f12_ctrl_23 {
	union {
		struct {
			unsigned char obj_type_enable;
			unsigned char max_reported_objects;
		};
		unsigned char data[2];
	};
};

struct synaptics_rmi4_f12_finger_data {
	unsigned char object_type_and_status;
	unsigned char x_lsb;
	unsigned char x_msb;
	unsigned char y_lsb;
	unsigned char y_msb;
#ifdef REPORT_2D_Z
	unsigned char z;
#endif
#ifdef REPORT_2D_W
	unsigned char wx;
	unsigned char wy;
#endif
};

struct synaptics_rmi4_feature{
	struct synaptics_rmi4_glove glove_feature;
	struct synaptics_rmi4_holster holster_feature;
	struct synaptics_rmi4_geswakeup geswakeup_feature;
	struct synaptics_rmi4_pen pen_feature;
	unsigned short  f12_ctrl_base_addr;
	unsigned short  f12_data_base_addr;
	unsigned short  f12_query_base_addr;
	unsigned short  f11_query_base_addr;
	unsigned short  f11_ctrl_base_addr;
	unsigned short  f11_data_base_addr;
	unsigned short  f11_cmd_base_addr;
	unsigned short  f51_query_base_addr;
	unsigned short  f51_ctrl_base_addr;
	unsigned short  f51_data_base_addr;
	unsigned short  f51_cmd_base_addr;
	unsigned short f01_query_base_addr;
	unsigned short f01_cmd_base_addr;
	unsigned short f01_ctrl_base_addr;
	unsigned short f01_data_base_addr;
};

/*
 * struct synaptics_rmi4_data - rmi4 device instance data
 * @i2c_client: pointer to associated i2c client
 * @input_dev: pointer to associated input device
 * @rmi4_mod_info: device information
 * @current_page: current page in sensor to acess
 * @button_0d_enabled: flag for 0d button support
 * @full_pm_cycle: flag for full power management cycle in early suspend stage
 * @num_of_intr_regs: number of interrupt registers
 * @f01_query_base_addr: query base address for f01
 * @f01_cmd_base_addr: command base address for f01
 * @f01_ctrl_base_addr: control base address for f01
 * @f01_data_base_addr: data base address for f01
 * @irq: attention interrupt
 * @sensor_max_x: sensor maximum x value
 * @sensor_max_y: sensor maximum y value
 * @touch_stopped: flag to stop interrupt thread processing
 * @fingers_on_2d: flag to indicate presence of fingers in 2d area
 * @sensor_sleep: flag to indicate sleep state of sensor
 * @swap_axes: set to TRUE if desired to swap x- and y-axis
 * @flip_x: set to TRUE if desired to flip direction on x-axis
 * @flip_y: set to TRUE if desired to flip direction on y-axis
 * @wait: wait queue for touch data polling in interrupt thread
 * @irq_enable: pointer to irq enable function
 */
struct synaptics_rmi4_data {
	struct ts_device_data * synaptics_chip_data;
	struct platform_device *synaptics_dev;
	struct synaptics_rmi4_device_info rmi4_mod_info;
	struct synaptics_rmi4_feature rmi4_feature;
#ifdef RED_REMOTE
	struct input_dev* input_dev;
	bool fw_debug;
#endif
	struct i2c_client	*i2c_client;
	struct regulator *tp_vci;
	struct regulator *tp_vddio;
#ifndef CONFIG_OF
	struct iomux_block *tp_gpio_block;
	struct block_config *tp_gpio_block_config;
#else
	struct pinctrl *pctrl;
	struct pinctrl_state *pins_default;
	struct pinctrl_state *pins_idle;
#endif
	unsigned char current_page;
	unsigned char button_0d_enabled;
	unsigned char full_pm_cycle;
	unsigned char num_of_rx;
	unsigned char num_of_tx;
	unsigned char num_of_fingers;
	unsigned char max_touch_width;
	unsigned char report_enable;
	unsigned char intr_mask[MAX_INTR_REGISTERS];
	unsigned short num_of_intr_regs;
	int sensor_max_x;
	int sensor_max_y;
	int sensor_max_x_mt;
	int sensor_max_y_mt;
	bool touch_stopped;
	bool fingers_on_2d;
	bool sensor_sleep;
	bool swap_axis;
	bool flip_x;
	bool flip_y;
	bool force_update;
	unsigned int reset_delay_ms;
	int (*i2c_read)(struct synaptics_rmi4_data *pdata, unsigned short addr,
			unsigned char *data, unsigned short length);
	int (*i2c_write)(struct synaptics_rmi4_data *pdata, unsigned short addr,
			unsigned char *data, unsigned short length);
	int (*irq_enable)(struct synaptics_rmi4_data *rmi4_data, bool enable);
	int (*reset_device)(struct synaptics_rmi4_data *rmi4_data);
	int (*status_save)(struct synaptics_rmi4_data *rmi4_data);
	int (*status_resume)(struct synaptics_rmi4_data *rmi4_data);
};

enum exp_fn {
	RMI_DEV = 0,
	RMI_F34,
	RMI_F54,
	RMI_FW_UPDATER,
	RMI_LAST,
};
enum synaptics_ic_type{
	SYNAPTICS_S3207 = 0,
	SYNAPTICS_S3350,
	SYNAPTICS_S3320,
	SYNAPTICS_S3718,
};
struct touch_settings {
	unsigned char build_id[SYNAPTICS_RMI4_BUILD_ID_SIZE];
	unsigned char ic_name[SYNAPTICS_RMI4_IC_NAME_SIZE];
	const char *module_name;
	unsigned int ic_type;
};

struct synaptics_rmi4_exp_fn_ptr {
	int (*read)(struct synaptics_rmi4_data *rmi4_data, unsigned short addr,
			unsigned char *data, unsigned short length);
	int (*write)(struct synaptics_rmi4_data *rmi4_data, unsigned short addr,
			unsigned char *data, unsigned short length);
	int (*enable)(struct synaptics_rmi4_data *rmi4_data, bool enable);
};

static inline void batohs(unsigned short *dest, unsigned char *src)
{
	*dest = src[1] * 0x100 + src[0];
}

static inline void hstoba(unsigned char *dest, unsigned short src)
{
	dest[0] = src % 0x100;
	dest[1] = src / 0x100;
}

extern int synaptics_fw_data_init(struct synaptics_rmi4_data *rmi4_data);
extern bool synaptics_check_fw_version(void);
extern int synaptics_get_fw_data_boot(char *file_name,struct touch_settings *synaptics_sett_param_regs);
extern int synaptics_get_fw_data_sd(void);
extern void synaptics_fw_data_release(void);
extern int synaptics_fw_update(void);
extern int synaptics_fw_data_s3718_init(struct synaptics_rmi4_data *rmi4_data);
extern bool synaptics_check_fw_s3718_version(void);
extern int synaptics_get_fw_data_s3718_boot(char *file_name,struct touch_settings *synaptics_sett_param_regs);
extern int synaptics_get_fw_data_s3718_sd(void);
extern void synaptics_fw_data_s3718_release(void);
extern int synaptics_fw_s3718_update(void);
extern int synaptics_rmi4_f54_s3207_init(struct synaptics_rmi4_data *rmi4_data,const char *module_name);
extern int synaptics_rmi4_f54_init(struct synaptics_rmi4_data *rmi4_data,const char *module_name);
#ifdef RED_REMOTE
extern void synaptics_fw_debug_dev_init(struct synaptics_rmi4_data *rmi4_data);
extern void rmidev_sysfs_irq(void *data);
#endif
extern int synaptics_get_cap_data(struct ts_rawdata_info *info);
extern int synaptics_fw_configid(struct synaptics_rmi4_data *rmi4_data, u8 *buf, size_t buf_size);
#endif

