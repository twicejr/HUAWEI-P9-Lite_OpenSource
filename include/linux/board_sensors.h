/************************************************************
  Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
  FileName: board_sensors.h
  Author: hantao(00185954)       Version : 0.1      Date:  2011-07-11
  Description:	.h file for sensors
  Version:
  Function List:
  History:
  <author>  <time>   <version >   <desc>
***********************************************************/
/*==============================================================================
History

Problem NO.         Name        Time         Reason

==============================================================================*/

#ifndef	__BOARD_SENSORS_H__
#define	__BOARD_SENSORS_H__

/*Device Id Name*/
#define AKM8975C_I2C_NAME		"akm8975"
#define	LIS3DH_I2C_NAME			"lis3dh_acc"
#define	L3G4200D_I2C_NAME		"l3g4200d_gyr"
#define	TMD2771_I2C_NAME		"tmd2771"
#define APDS990x_I2C_NAME		"apds990x"
#define MMA8452_I2C_NAME		"mma8452"
#define ADXL34X_I2C_NAME		"adxl34x"
#define CM3320_I2C_NAME		"cm3320"
#define HALL_NAME                       "ak8987"
/*Slave Adress*/
#define	AKM8975C_I2C_ADDR		0x0c
#define AKM8963_I2C_ADDR		0x0E
#define AKM09911_I2C_ADDR		0x0D
#define LSM303D_I2C_ADDR		0x1E
#define LSM330_ACC_I2C_ADDR	        0x1E
#define LSM330_GYR_I2C_ADDR	        0x6B
#define	LIS3DH_I2C_ADDR			0x18
#define APDS990x_I2C_ADDR		0x39
#define MMA8452_I2C_ADDR		0x1C
#define L3G4200D_I2C_ADDR		0x6a//0x68//
#define TAOS_DEVICE_ADDR1		0x29
#define TAOS_DEVICE_ADDR2		0x39
#define TAOS_DEVICE_ADDR3		0x49
#define TMD2771_I2C_ADDR		TAOS_DEVICE_ADDR2
#define ADXL34X_I2C_ADDR		0x53
#define CM3320_I2C_ADDR		0x10
#define AD7146_I2C_ADDR             0X2C
/*Input Device Name*/
#ifndef ACCL_INPUT_DEV_NAME
#define	ACCL_INPUT_DEV_NAME		"acc_input"
#endif
#ifndef COMPASS_INPUT_DEV_NAME
#define	COMPASS_INPUT_DEV_NAME	"compass_input"
#endif
#ifndef GYRO_INPUT_DEV_NAME
#define	GYRO_INPUT_DEV_NAME		"gyro_input"
#endif
#ifndef ALS_INPUT_DEV_NAME
#define ALS_INPUT_DEV_NAME	"als_input"
#endif
#ifndef PS_INPUT_DEV_NAME
#define PS_INPUT_DEV_NAME	"ps_input"
#endif
#ifndef HALL_INPUT_DEV_NAME
#define HALL_INPUT_DEV_NAME       "hall_input"
#endif
#ifndef CAP_INPUT_DEV_NAME
#define CAP_INPUT_DEV_NAME	"cs_input"
#endif
#if defined (CONFIG_HUAWEI_DSM)
#define LDO2_PHYS_ADDR	 (0x072)
#define LDO5_PHYS_ADDR	 (0x076)
#endif
enum input_sensor {
	ACC,
	COMPASS,
	ORI,
	GYRO,
	ALS,
	PS,
	HALL,
	CS,
	SENSOR_MAX
};

int set_sensor_event(const char *dev_name, const char *event_num);
int set_sensor_chip_info(enum input_sensor name, const char *chip_info);
int set_gyro_selfTest_result(enum input_sensor name, const char *result);
int set_selftest(int value);
int set_selftest_lm330(int value);

#endif
