/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef _HISI_SENSOR_H_
#define _HISI_SENSOR_H_

#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/pinctrl/consumer.h>
#include <linux/gpio.h>
#include <linux/pinctrl/consumer.h>
#include <media/v4l2-subdev.h>
#include "../hisi_subdev.h"
#include "../hisi_cam_module.h"


#define CAMERA_SENSOR_ARRAY_SIZE	20

#define DEFINE_HISI_SENSOR_MUTEX(id) \
	static struct mutex sensor_mut_##id = __MUTEX_INITIALIZER(sensor_mut_##id)

#define DEFINE_HISI_SENSOR_CTRL(id)	\
	DEFINE_HISI_SENSOR_MUTEX(id);	\
	struct hisi_sensor_ctrl_t hisi_s_ctrl_##id = {	\
		.index = id,	\
		.hisi_sensor_mutex = &sensor_mut_##id,	\
		.sensor_array = sensor_array[id],	\
		.csi_ctrl = &csi_pad,	\
	};


/********************** v4l2 subdev ioctl case id define **********************/
struct sensor_cfg_data;

#define VIDIOC_HISI_SENSOR_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 11, struct sensor_cfg_data)

#define VIDIOC_HISI_CSI_ENABLE \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 12, struct sensor_cfg_data)

#define VIDIOC_HISI_CSI_DISABLE \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 13, struct sensor_cfg_data)



/***************************** cfg type define *******************************/
#define CFG_SENSOR_POWER_UP		0
#define CFG_SENSOR_POWER_DOWN		1
#define CFG_SENSOR_I2C_READ		2
#define CFG_SENSOR_I2C_WRITE		3
#define CFG_SENSOR_I2C_READ_SEQ		4
#define CFG_SENSOR_I2C_WRITE_SEQ	5
#define CFG_SENSOR_GET_SENSOR_NAME	6
#define CFG_SENSOR_GET_CHROMATIX_NAME   7

#define CFG_SENSOR_SET_VTS		21
#define CFG_SENSOR_GET_OTP_AWB	22
#define CFG_SENSOR_GET_OTP_LENC	23
#define CFG_SENSOR_GET_OTP_VCM	24
#define CFG_SENSOR_UPDATE_OTP_AWB	25
#define CFG_SENSOR_UPDATE_OTP_LENC	26
#define CFG_SENSOR_UPDATE_OTP_VCM	27

/********************** sensor base data struct define **********************/
#define SENSOR_INDEX_INVALID		-1
#define LDO_VOLTAGE_1P05V		1050000
#define LDO_VOLTAGE_1P2V		1200000
#define LDO_VOLTAGE_1P5V		1500000
#define LDO_VOLTAGE_1P8V		1800000
#define LDO_VOLTAGE_2P8V		2850000

enum sensor_power_state_t{
	POWER_OFF = 0,
	POWER_ON,
};


enum sensor_iocfg_type_t {
	SENSOR_IO_DISABLE = 0,
	SENSOR_IO_ENABLE,
};

enum sensor_gpiocfg_type_t {
	SENSOR_GPIO_LOW = 0,
	SENSOR_GPIO_HIGH,
};


enum sensor_power_seq_type_t {
	SENSOR_MCLK = 0,
	SENSOR_RST,
	SENSOR_PWDN,
	SENSOR_VCM_PWDN,
	SENSOR_SUSPEND, /* using for suspend the sensor */
	SENSOR_CHECK_LEVEL,
	SENSOR_DVDD,
	SENSOR_DVDD2, /* using for power up second sensor's ldo */
	SENSOR_AVDD,
	SENSOR_AVDD2, /* using for power up second sensor's ldo */
	SENSOR_IOVDD,
	SENSOR_VCM_AVDD,
	SENSOR_VCM_AVDD2,/* using for power up second sensor's ldo */
	SENSOR_I2C,
	SENSOR_CSI,
	SENSOR_IOCFG,
};

struct sensor_power_setting {
	enum sensor_power_seq_type_t seq_type;
	unsigned int seq_val;
	unsigned int config_val;
	void *data;
	unsigned int sensor_index;
	unsigned int delay;  /* delay ms */
};

struct sensor_power_setting_array {
	struct sensor_power_setting *power_setting;
	unsigned int size;
};


/********************** sensor controler struct define **********************/

typedef enum {
	MIPI1,
	MIPI2,
} data_interface_t;

typedef enum {
	CSI_LINES_1 = 0,
	CSI_LINES_2,
	CSI_LINES_3,
	CSI_LINES_4,
	CSI_LINES_5,
	CSI_LINES_6,
	CSI_LINES_7,
	CSI_LINES_8,
	CSI_LINES_INVALID,
} csi_lane_t;

typedef enum {
	CAMERA_SENSOR_PRIMARY = 0,
	CAMERA_SENSOR_SECONDARY,
	CAMERA_SENSOR_MAX
} sensor_index_t;

typedef enum {
	LOW_VALID = 0,
	HIGH_VALID,
} electrical_valid_t;

typedef struct _sensor_power_t {
	electrical_valid_t pd_valid;
	electrical_valid_t reset_valid;
	electrical_valid_t vcmpd_valid;
} sensor_power_t;

typedef enum {
	CSI_INDEX_0 = 0,
	CSI_INDEX_1,
	CSI_INDEX_CNT,
} csi_index_t;



typedef enum {
	I2C_PRIMARY = 0,
	I2C_SECONDARY
} i2c_index_t;

typedef enum {
	I2C_SPEED_100 = 0,
	I2C_SPEED_200 = 1,
	I2C_SPEED_400 = 2,
	I2C_SPEED_MAX = 3,
} i2c_speed_t;

typedef enum {
	I2C_8BIT = 0,
	I2C_16BIT
} i2c_length;

typedef struct _i2c_t {
	i2c_index_t index;
	i2c_speed_t speed;
	u32 addr;
	i2c_length addr_bits;
	i2c_length val_bits;
} i2c_t;

typedef enum {
	LDO_DVDD = 0,
	LDO_DVDD2,
	LDO_AVDD,
	LDO_AVDD2, /* using for power up primary sensor and secondary sensor */
	LDO_VCM,
	LDO_VCM2,
	LDO_IOPW,
	LDO_MAX,
} ldo_index_t;

typedef enum {
	RESETB = 0,
	FSIN,
	PWDN,
	VCM,
	SUSPEND,//used to suspend the other sensor when power up
	IO_MAX
} gpio_t;

typedef enum {
	PIN_LEVEL_LOW = 0,
	PIN_LEVEL_HIGH
} pin_level_t;

struct hisi_sensor_info {
	const char *name;   /* sensor name */

	/* interface_type : MIPI or DVP */
	data_interface_t interface_type;
	csi_lane_t csi_lane;
	csi_index_t csi_index;
	u32 csi_mipi_clk;

	sensor_power_t power_conf;
	/* regulator: dvdd, avdd, iopw, vcm*/
	u32 ldo_num;
	struct regulator_bulk_data ldo[LDO_MAX];

	/* i2c  */
	struct pinctrl *pctrl;
	struct pinctrl_state *pinctrl_def;
	struct pinctrl_state *pinctrl_idle;

	sensor_index_t sensor_index;
	i2c_t i2c_config;
	i2c_t otp_i2c_config;

	u32 gpio_num;
	struct gpio gpios[IO_MAX];
	int active_gpios[IO_MAX];
	unsigned int sensor_chipid;
	unsigned int camif_id;
	const char *vcm_name;
	int vcm_enable;
};

struct hisi_sensor_ctrl_t {
	int index;
	struct platform_device *pdev;
	struct mutex *hisi_sensor_mutex;
	struct device *dev;
	struct hisi_sd_subdev hisi_sd;
	struct v4l2_subdev_ops *sensor_v4l2_subdev_ops;
	struct hisi_sensor_t *sensor;
	struct hisi_sensor_t **sensor_array;
	struct hisi_csi_pad *csi_ctrl;
};

struct hisi_sensor_fn_t {
	/* sensor function table */
	int (*sensor_match_id)(struct hisi_sensor_ctrl_t *);
	int (*sensor_config) (struct hisi_sensor_ctrl_t *, void *);
	int (*sensor_power_up) (struct hisi_sensor_ctrl_t *);
	int (*sensor_power_down) (struct hisi_sensor_ctrl_t *);
	int (*sensor_i2c_read) (struct hisi_sensor_ctrl_t *, void *);
	int (*sensor_i2c_write) (struct hisi_sensor_ctrl_t *, void *);
	int (*sensor_i2c_read_seq) (struct hisi_sensor_ctrl_t *, void *);
	int (*sensor_i2c_write_seq) (struct hisi_sensor_ctrl_t *, void *);
	int (*sensor_ioctl) (struct hisi_sensor_ctrl_t *, void *);
	int (*ext_power_ctrl)(int enable);
	int (*sensor_set_expo_gain)(struct hisi_sensor_t *, u32 expo, u16 gain);
	int (*sensor_set_expo)(struct hisi_sensor_t *, u32 expo);
	int (*sensor_set_gain)(struct hisi_sensor_t *, u16 gain);
};

struct hisi_sensor_awb_otp {
	u8 awb_otp_support;
	u8 awb_otp_succeed;
	u32 rg_l;
	u32 rg_h;
	u32 bg_h;
	u32 bg_l;
	u32 gbgr_h;
	u32 gbgr_l;
	u32 rgain;
	u32 bgain;
	u32 ggain;
};

struct hisi_sensor_af_otp {
	u8 af_otp_support;
	u8 af_otp_succeed;
	u32 start_code;
	u32 end_code;
};

struct hisi_sensor_otp {
	struct hisi_sensor_awb_otp awb_otp;
	struct hisi_sensor_af_otp af_otp;
};

struct hisi_sensor_t {
	struct hisi_sensor_fn_t *func_tbl;
	struct hisi_sensor_info *sensor_info;
	struct sensor_power_setting_array power_setting_array;
	struct hisi_sensor_otp sensor_otp;
};


/********************* cfg data define ************************************/

struct sensor_i2c_reg {
	u32 subaddr;
	u32 value;
	u8 mask;
	u16 size;
};

struct sensor_i2c_setting {
	u32 size;
	u32 reserve;
	struct sensor_i2c_reg *setting;
};
/*sensor ioctl arg*/
struct sensor_cfg_data {
	int cfgtype;
	int mode;
	int data;
	/* add for 64bit alignment */
	int reserve;

	union {
	char name[32];
	struct sensor_i2c_reg reg;
	struct sensor_i2c_setting setting;
	struct hisi_sensor_af_otp af_otp;
	} cfg;
};



/***************extern function declare******************/

int hisi_sensor_add(struct hisi_sensor_t *sensor);
int hisi_sensor_del(struct hisi_sensor_t *sensor);
int hisi_sensor_config(struct hisi_sensor_ctrl_t *s_ctrl, void *argp);
int hisi_sensor_get_dt_data(struct platform_device *pdev,
					struct hisi_sensor_t *sensor);

#endif