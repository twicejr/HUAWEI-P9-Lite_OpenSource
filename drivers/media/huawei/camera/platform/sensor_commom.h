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


#ifndef _SENSOR_COMMOM_H_
#define _SENSOR_COMMOM_H_

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
#include <media/huawei/extisp_cfg.h>
#include "../sensor/hwsensor.h"
#include "../cam_log.h"

#define CAMERA_SENSOR_ARRAY_SIZE    20

#define DEFINE_HISI_SENSOR_MUTEX(id) \
    static struct mutex sensor_mut_##id = __MUTEX_INITIALIZER(sensor_mut_##id)

#define FILE_NAME_LEN    64

/********************** v4l2 subdev ioctl case id define **********************/
struct sensor_cfg_data;

#define VIDIOC_HISI_SENSOR_CFG \
    _IOWR('V', BASE_VIDIOC_PRIVATE + 11, struct sensor_cfg_data)

#define VIDIOC_HISI_CSI_ENABLE \
    _IOWR('V', BASE_VIDIOC_PRIVATE + 12, struct sensor_cfg_data)

#define VIDIOC_HISI_CSI_DISABLE \
    _IOWR('V', BASE_VIDIOC_PRIVATE + 13, struct sensor_cfg_data)



/***************************** cfg type define *******************************/
#define CFG_SENSOR_POWER_UP             0
#define CFG_SENSOR_POWER_DOWN           1
#define CFG_SENSOR_I2C_READ             2
#define CFG_SENSOR_I2C_WRITE            3
#define CFG_SENSOR_I2C_READ_SEQ         4
#define CFG_SENSOR_I2C_WRITE_SEQ        5
#define CFG_SENSOR_GET_SENSOR_NAME      6
#define CFG_SENSOR_GET_CHROMATIX_NAME   7

#define CFG_SENSOR_SET_VTS              21
#define CFG_SENSOR_GET_OTP_AWB          22
#define CFG_SENSOR_GET_OTP_LENC         23
#define CFG_SENSOR_GET_OTP_VCM          24
#define CFG_SENSOR_UPDATE_OTP_AWB       25
#define CFG_SENSOR_UPDATE_OTP_LENC      26
#define CFG_SENSOR_UPDATE_OTP_VCM       27

/********************** sensor base data struct define **********************/
#define SENSOR_INDEX_INVALID        -1
#define LDO_VOLTAGE_1P05V           1050000
#define LDO_VOLTAGE_1P2V            1200000
#define LDO_VOLTAGE_1P5V            1500000
#define LDO_VOLTAGE_1P8V            1800000
#define LDO_VOLTAGE_2P8V            2850000
//add by hefei
#define LDO_VOLTAGE_V2P8V           2800000
#define LDO_VOLTAGE_V2P85V          2850000
#define LDO_VOLTAGE_V2P6V           2600000
#define LDO_VOLTAGE_V1P1V           1100000
#define LDO_VOLTAGE_V1P15V          1150000
#define LDO_VOLTAGE_V0P9V           900000
#define LDO_VOLTAGE_V0P95V          950000

//add by yinxuerui
#define LDO_VOLTAGE_V2P5V       2500000

#define PMIC_1P1V               1100000
#define PMIC_1P15V              1150000
#define PMIC_1P2V               1200000
#define PMIC_1P8V               1800000
#define PMIC_2P8V               2800000
#define PMIC_2P85V              2850000
#define PMIC_3PV                3000000

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
    SENSOR_OIS,
    SENSOR_OIS2,
    SENSOR_IOVDD,
    SENSOR_VCM_AVDD,
    SENSOR_VCM_AVDD2,/* using for power up second sensor's ldo */
    SENSOR_I2C,
    SENSOR_CSI,
    SENSOR_IOCFG,
    SENSOR_RST2,
    SENSOR_PMIC,
    SENSOR_CS,
    SENSOR_LDO_EN,

    SENSOR_AVDD0,
    SENSOR_DVDD0_EN,
    SENSOR_AVDD1,
    SENSOR_DVDD1_EN,
    SENSOR_IOVDD_EN,
    SENSOR_MISPDCDC_EN,
    SENSOR_MISP_VDD,
    SENSOR_MINIISP_VPP,
};

enum sensor_power_pmic_type_t {
    PMIC_LDO1,
    PMIC_LDO2,
    PMIC_LDO3,
    PMIC_LDO4,
    PMIC_LDO5,
    PMIC_BUCK1,
    PMIC_BUCK2,
    PMIC_MAX,
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
    CAMERA_SENSOR_INVALID = -1,
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
    LDO_MISP,
    LDO_AVDD0,
    LDO_AVDD1,
    LDO_MINI_ISP,
    LDO_MAX,
} ldo_index_t;

typedef enum {
    RESETB = 0,
    FSIN,
    PWDN,
    VCM,
    SUSPEND,//used to suspend the other sensor when power up
    RESETB2, //add by hefei
    LDO_EN,
    OIS,
    OIS2,
    DVDD0_EN,
    DVDD1_EN,
    IOVDD_EN,
    MISPDCDC_EN,
    IO_MAX
} gpio_t;

typedef enum {
    PIN_LEVEL_LOW = 0,
    PIN_LEVEL_HIGH
} pin_level_t;

typedef struct _tag_hwsensor_board_info
{
    const char *name;   /* sensor name */

    /* interface_type : MIPI or DVP */
    data_interface_t interface_type;
    csi_lane_t csi_lane;
    csi_index_t csi_index;
    u32 csi_mipi_clk;

    sensor_power_t power_conf;
    /* regulator: dvdd, avdd, iopw, vcm*/
    int ldo_num;
    struct regulator_bulk_data ldo[LDO_MAX];

    /* i2c  */
    struct pinctrl *pctrl;
    struct pinctrl_state *pinctrl_def;
    struct pinctrl_state *pinctrl_idle;

    sensor_index_t sensor_index;
    i2c_t i2c_config;
    i2c_t otp_i2c_config;

    int gpio_num;
    struct gpio gpios[IO_MAX];
    int active_gpios[IO_MAX];
    unsigned int sensor_chipid;
    unsigned int camif_id;
    const char *vcm_name;
    int vcm_enable;

    unsigned int sensor_type;
    int extisp_type;

    unsigned int mclk;
    unsigned int ldo_diverse;/*this is used to distinguish different dvdd voltage values for main camera sensors*/
    int csi_id[2];
    int i2c_id[2];
    int module_type;
} hwsensor_board_info_t;

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

typedef struct _sensor_t {
    hwsensor_intf_t                            intf;
    hwsensor_board_info_t                     *board_info;
    hwsensor_state_kind_t                     state;
    struct sensor_power_setting_array    power_setting_array;
    struct device *dev;
    struct clk *isp_snclk0;
    struct clk *isp_snclk1;
    struct clk *isp_snclk2;
}sensor_t;


/********************extern function declare**************************/
int hw_sensor_power_up(sensor_t *s_ctrl);
int hw_sensor_power_down(sensor_t *s_ctrl);
int hw_sensor_i2c_read(sensor_t *s_ctrl, void *data);
int hw_sensor_i2c_write(sensor_t *s_ctrl, void *data);
int hw_sensor_i2c_read_seq(sensor_t *s_ctrl, void *data);
int hw_sensor_i2c_write_seq(sensor_t *s_ctrl, void *data);
int hisi_sensor_apply_expo_gain(sensor_t *s_ctrl, void *data);
int hisi_sensor_suspend_eg_task(sensor_t *s_ctrl);
int hw_sensor_get_dt_data(struct platform_device *pdev, sensor_t *sensor);
void hw_camdrv_msleep(unsigned int ms);
int hw_is_fpga_board(void);
int hwsensor_writefile(int index, const char *sensor_name);
int misp_get_module_info(uint8_t index,uint16_t *sensor_id, uint8_t *module_id);
int misp_get_chipid(void);
int misp_load_fw(u8 *out_fw_disp);
void hwcam_mclk_enable(int index, int enable);

#endif
