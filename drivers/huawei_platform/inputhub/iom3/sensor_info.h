/*
 *  drivers/misc/inputhub/inputhub_route.h
 *  Sensor Hub Channel driver
 *
 *  Copyright (C) 2012 Huawei, Inc.
 *  Author: qindiwen <inputhub@huawei.com>
 *
 */
#ifndef	__SENSORS_H__
#define	__SENSORS_H__

#define PDC_SIZE		27
#define SENSOR_PLATFORM_EXTEND_DATA_SIZE    48
#define EXTEND_DATA_TYPE_IN_DTS_BYTE        0
#define EXTEND_DATA_TYPE_IN_DTS_HALF_WORD   1
#define EXTEND_DATA_TYPE_IN_DTS_WORD        2

enum sensor_name {
	ACC,
	MAG,
	GYRO,
	ALS,
	PS,
	AIRPRESS,
	HANDPRESS,
	CAP_PROX,
	SENSOR_MAX
};

typedef enum
{
	SUC=1,
	EXEC_FAIL,
	NV_FAIL,
	COMMU_FAIL
}RET_TYPE;

enum detect_state {
	DET_INIT=0,
	DET_FAIL,
	DET_SUCC
};

struct i2c_data{
	uint8_t bus_num;
	uint8_t i2c_address;
	uint16_t reg_address;
	uint8_t reg_type;
	uint8_t reg_len;
	uint8_t data[MAX_I2C_DATA_LENGTH];
};

struct sensor_status
{
	int status[TAG_SENSOR_END];//record whether sensor is in activate status, already opened and setdelay
	int delay[TAG_SENSOR_END];//record sensor delay time
	int opened[TAG_SENSOR_END];//record whether sensor was opened
	char gyro_selfTest_result[5];
	char mag_selfTest_result[5];
	char accel_selfTest_result[5];
};
struct g_sensor_platform_data{
    uint8_t i2c_address;
    uint8_t axis_map_x;
    uint8_t axis_map_y;
    uint8_t axis_map_z;
    uint8_t negate_x;
    uint8_t negate_y;
    uint8_t negate_z;
    uint8_t gpio_int1;
    uint8_t gpio_int2;
    uint16_t poll_interval;
    int offset_x;
    int offset_y;
    int offset_z;
    uint8_t g_sensor_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};
struct gyro_platform_data{
    uint8_t exist;
    uint8_t i2c_address;
    uint8_t axis_map_x;
    uint8_t axis_map_y;
    uint8_t axis_map_z;
    uint8_t negate_x;
    uint8_t negate_y;
    uint8_t negate_z;
    uint8_t gpio_int1;
    uint8_t gpio_int2;
    uint16_t poll_interval;
    uint8_t gyro_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};
struct compass_platform_data {
	uint8_t i2c_address;
	uint8_t axis_map_x;
	uint8_t axis_map_y;
	uint8_t axis_map_z;
	uint8_t negate_x;
	uint8_t negate_y;
	uint8_t negate_z;
	uint8_t outbit;
	uint8_t gpio_drdy;
	uint8_t gpio_rst;
	uint8_t pdc_data[PDC_SIZE];
	uint16_t poll_interval;
    uint8_t compass_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};
struct als_platform_data{
	uint8_t i2c_address;
	uint8_t gpio_int1;
	uint8_t atime;
	uint8_t again;
	uint16_t poll_interval;
	uint16_t init_time;
	int threshold_value;
	int GA1;
	int GA2;
	int GA3;
	int COE_B;
	int COE_C;
	int COE_D;
    uint8_t als_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};

struct ps_platform_data{
	uint8_t i2c_address;
	uint8_t ps_pulse_count;
	uint8_t gpio_int1;
	uint8_t persistent;
	uint8_t ptime;
	uint8_t p_on;  //need to close oscillator
	uint16_t poll_interval;
	uint16_t init_time;
	int min_proximity_value;
	int pwindows_value;
	int pwave_value;
	int threshold_value;
	int rdata_under_sun;
    uint8_t ps_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};

struct airpress_platform_data{
	uint8_t i2c_address;
	uint16_t poll_interval;
	uint8_t airpress_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};

#define CYPRESS_CHIPS		2
struct handpress_platform_data{
	uint8_t id[CYPRESS_CHIPS];
	uint8_t i2c_address[CYPRESS_CHIPS];
	uint8_t t_pionts[CYPRESS_CHIPS];
	uint16_t poll_interval;
	uint32_t irq[CYPRESS_CHIPS];
	uint8_t handpress_extend_data[SENSOR_PLATFORM_EXTEND_DATA_SIZE];
};

struct cap_prox_platform_data{
	uint8_t i2c_address;
	uint8_t gpio_int;
	uint16_t poll_interval;
	uint32_t init_reg_val[17];      /* init value */
	uint16_t freespace[2];
	uint16_t cal_fact_base[2];
	uint16_t cal_offset[2];
	uint16_t digi_offset[2];
	uint8_t cap_prox_extend_data[8];
};

extern  bool sensor_info_isensor_version;

int is_sensor_active();
int is_backup_sensor_active();

extern int check_sensor_info(int tag, obj_cmd_t cmd, int delay);
extern void update_sensor_info(const pkt_header_t *pkt);
extern void disable_sensors_when_suspend(void);
extern void enable_sensors_when_resume(void);
extern void disable_sensors_when_reboot(void);
extern void enable_sensors_when_recovery_iom3(void);
extern void reset_calibrate_when_recovery_iom3(void);
extern sys_status_t iom3_sr_status;
#endif	/* __SENSORS_H__ */
