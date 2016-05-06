/*
 * Copyright (C) huawei company
 *
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/delay.h>
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include "protocol.h"
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/types.h>
#include <linux/fs.h>
#include "sensor_info.h"
#include "sensor_sys_info.h"
#include <linux/mtd/hisi_nve_interface.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#include <linux/regulator/consumer.h>
#include <linux/of_device.h>
#include <dsm/dsm_pub.h>

int hisi_nve_direct_access(struct hisi_nve_info_user *user_info);

#define PS_CALIDATA_NV_NUM	334
#define PS_CALIDATA_NV_SIZE  4
#define ALS_CALIDATA_NV_NUM	339
#define ALS_CALIDATA_NV_SIZE  12
#define GYRO_CALIDATA_NV_NUM	341
#define GYRO_CALIDATA_NV_SIZE  24
#define AIRPRESS_CALIDATA_NV_NUM	332
#define AIRPRESS_CALIDATA_NV_SIZE  4
#define CAP_PROX_CALIDATA_NV_NUM  310
#define CAP_PROX_CALIDATA_NV_SIZE  16
#define SENSOR_CONFIG_DATA_OK 0
#define MAX_MCU_DATA_LENGTH  30
#define ACC_OFFSET_NV_NUM	307
#define ACC_OFFSET_NV_SIZE	(16)
#define MAG_CALIBRATE_DATA_NV_NUM 233
#define MAG_CALIBRATE_DATA_NV_SIZE (MAX_MAG_CALIBRATE_DATA_LENGTH)
#define NV_READ_TAG	1
#define NV_WRITE_TAG	0
#define OFFSET_BIG               127
#define OFFSET_SMALL             -128
#define Z_SCALE_BIG              255
#define Z_SCALE_SMALL            175
#define MAX_STR_SIZE	1024
#define MAX_FILE_ID	64
#define DMP_DRIVER_FILE_ID 5
#define DMP_IMG_FILE_ID 6
#define ICM20628_ADDR   0x68
#define REG_BANK_SEL    0x7f
#define INT_PIN_CFG     0x0f
#define PWR_MGMT_1      0x06
#define SENSOR_LIST_NUM 50
#define SENSOR_VBUS "sensor-io"
#define DEBUG_DATA_LENGTH 10
#define HANDPRESS_DEFAULT_STATE				"huawei,default-state"

#define WHITE	0xE1
#define BLACK	0xD2
#define PINK	0xC3
#define RED		0xB4
#define YELLOW	0xA5
#define BLUE	0x96
#define GOLD  0x87
#define GRAY  0x78
#define BROWN  0x69

#define TP_COLOR_BUF_SIZE		20
#define NEXT  11 // decimal base
#define V3  10 // decimal base
#define V3_A  101 // decimal base
#define V4  11 // decimal base
#define VN1  12 // decimal base
#define VN2  13 // decimal base

#define DTS_COMP_LG_ER69006A "hisilicon,mipi_lg_eR69006A"
#define DTS_COMP_JDI_NT35695_CUT3_1 "hisilicon,mipi_jdi_NT35695_cut3_1"
#define DTS_COMP_JDI_NT35695_CUT2_5 "hisilicon,mipi_jdi_NT35695_cut2_5"

#define LG_TPLCD (1)
#define JDI_TPLCD (2)

#define IS_FAIL(flag1, flag2, flag3, flag4, flag5, flag6, flag7, flag8) \
	((flag1 == DET_FAIL) ||(flag2 == DET_FAIL) ||(flag3 == DET_FAIL) \
		||(flag4 == DET_FAIL) ||(flag5 == DET_FAIL) ||(flag6 == DET_FAIL) \
		|| (flag7 == DET_FAIL) || (flag8 == DET_FAIL))

bool sensor_info_isensor_version = false;

static int acc_close_after_calibrate = true;
static int als_close_after_calibrate = true;
static int gyro_close_after_calibrate = true;
static char sensor_chip_info[SENSOR_MAX][50];
static int gsensor_offset[3]; //g-sensor校准参数
static int gyro_sensor_offset[3];
static int ps_sensor_offset = 0;
static uint16_t als_offset[6];
static RET_TYPE return_calibration = EXEC_FAIL;//acc calibrate result
static RET_TYPE ps_calibration_res = EXEC_FAIL;//ps calibrate result
static RET_TYPE als_calibration_res = EXEC_FAIL;//als calibrate result
static RET_TYPE gyro_calibration_res = EXEC_FAIL;//gyro  calibrate result
static RET_TYPE return_cap_prox_calibration = EXEC_FAIL;
struct sensor_status sensor_status;
static struct sensor_status sensor_status_backup;
extern int first_start_flag;
extern int ps_first_start_flag;
extern int txc_ps_flag;
extern int als_first_start_flag;
extern int gyro_first_start_flag;
extern int rohm_rgb_flag;
extern int avago_rgb_flag;
static char buf[MAX_PKT_LENGTH]={0};
pkt_sys_dynload_req_t *dyn_req = (pkt_sys_dynload_req_t *)buf;
static uint16_t sensorlist[SENSOR_LIST_NUM] = {0};
static const char *str_soft_para = "softiron_parameter";
static const char *str_comp = "compass_extend_data";
extern struct dsm_client *shb_dclient;
static uint8_t debug_read_data_buf[DEBUG_DATA_LENGTH] = {0};
extern int get_airpress_data;
extern int get_temperature_data;
extern int iom3_timeout;
extern int g_iom3_state;
extern struct completion iom3_reboot;
static u8 phone_color = 0;
static u8 tplcd_manufacture = 0;
static unsigned char tp_color_buf[TP_COLOR_BUF_SIZE] = {0};
typedef struct _BH1745_ALS_PARA_TABLE{
	uint8_t phone_type;
	uint8_t phone_version;
	uint8_t tp_lcd_manufacture;
	uint8_t tp_color;
	s16 bh745_para[23]; //give to bh1745 rgb sensor use,output lux and cct will use these para
}BH1745_ALS_PARA_TABLE;
BH1745_ALS_PARA_TABLE als_para_diff_tp_color_table[] =
{
	{NEXT,V3,LG_TPLCD,BLACK,{249, 480, 403, 1826, 1472, 249, 451, 1650, 100, -2512, 7591, -2862, 5730, 1022, 1542, 1866, 1934, 5507, 3392, 4859,613, 1154, 4831}},
	{NEXT,V3,LG_TPLCD,WHITE,{197, 154, 73, 538, 541, 197, 434, 1511, 100, -2479, 7196, -2699, 5569, 950, 1531, 1660, 1914, 4726, 6095, 2263,630, 2003, 4953 }},
	{NEXT,V3,LG_TPLCD,GOLD,{192, 544, 412,  1962, 1677, 192, 424, 1510, 100, -2510, 7022, -2715, 5348, 978, 1516, 1718, 1951, 1414, 1782, 646,182, 2132, 4634 }},
	{NEXT,V3,JDI_TPLCD,BLACK,{504, 70, 11, 515, 489, 504, 274, 1144, 100, -2161, 3152, -2780, 3429, 964, 1522, 2481, 2015, 15675, 10524, 14809,1877, 3258, 4744 }},
	{NEXT,V3,JDI_TPLCD,WHITE,{208, 227, 139, 802, 737, 208, 476, 1636, 100, -2531, 7886, -2834, 6160, 991, 1528, 1856, 1897, 3081, 3805, 1363,399, 1298, 4713 }},
	{NEXT,V3,JDI_TPLCD,GOLD,{469, 274, 102, 943, 463, 469, 355, 1428, 100, -2449, 4030, -2501, 4310, 818, 1359, 2023, 2038, 1529, 1934, 700,195, 2313, 4360 }},
	{NEXT,V3_A,LG_TPLCD,GOLD,{221, 5137, 2855, 25042, 24306, 221, 657, 2423, 100, -2491, 9912, -3234, 8383, 1207, 1662, 3065, 1955, 89, 92, 23, 11, 1380, 4819}},
	{NEXT,V3,LG_TPLCD,GRAY,{345, 999, 741, 5871, 4998, 346, 718, 2890, 100, -2516, 10599, -3501, 9174, 1373, 1724, 4096, 1964, 1079, 868, 216,104, 3086, 4670  }},

	{NEXT,V4,LG_TPLCD,BLACK,{346, 998, 740, 5871, 4998, 346, 718, 2890, 100, -2516, 10599, -3501, 9174, 1373, 1724, 4096, 1964, 1079, 868, 216,104, 3086, 4670  }},
	{NEXT,V4,LG_TPLCD,GRAY,{346, 998, 740, 5871, 4998, 346, 718, 2890, 100, -2516, 10599, -3501, 9174, 1373, 1724, 4096, 1964, 1079, 868, 216,104, 3086, 4670  }},
	{NEXT,V4,LG_TPLCD,WHITE,{191, 214, 147, 884, 780, 191, 459, 1633, 100, -2499, 7280, -2905, 5962, 1060, 1556, 2104, 1920, 5144, 6115, 2364,630, 3253, 5223 }},
	{NEXT,V4,LG_TPLCD,GOLD,{174, 806, 488,  3605, 3250, 174, 471, 1811, 100, -2374, 7027, -2835, 5795, 1038, 1624, 2113, 1982, 1235, 1401, 496,144, 3023, 4732 }},
	{NEXT,V4,JDI_TPLCD,BLACK,{334, 873, 660, 4844, 4071, 334, 719, 2815, 100, -2463, 10281, -3452, 9226, 1283, 1720, 3997, 1949, 1233, 1111, 268,135, 3329, 4665  }},
	{NEXT,V4,JDI_TPLCD,GRAY,{334, 873, 660, 4844, 4071, 334, 719, 2815, 100, -2463, 10281, -3452, 9226, 1283, 1720, 3997, 1949, 1233, 1111, 268,135, 3329, 4665 }},
	{NEXT,V4,JDI_TPLCD,WHITE,{199, 216, 128, 921, 871, 199, 482, 1724, 100, -2459, 7487, -2964, 6288, 1062, 1587, 2237, 1918, 4659, 5417, 2005,564, 2997, 5221 }},
	{NEXT,V4,JDI_TPLCD,GOLD,{195, 540, 318,  1966, 1954, 195, 282, 1569, 100, -2425, 6844, -1342, 3208, 944, 1551, 649, 2162, 1529, 1934, 700,195, 2313, 4360 }},

};

typedef struct _APDS9251_ALS_PARA_TABLE{
	uint8_t phone_type;
	uint8_t phone_version;
	uint8_t tp_lcd_manufacture;
	uint8_t tp_color;
	s16 apds251_para[17];//give to apds251 rgb sensor use,output lux and cct will use these par
}APDS9251_ALS_PARA_TABLE;//the apds251_para size must small SENSOR_PLATFORM_EXTEND_DATA_SIZE
APDS9251_ALS_PARA_TABLE apds_als_para_diff_tp_color_table[] =
{
	{NEXT,V4,LG_TPLCD,BLACK,{5917, 2671, 4969, 3860, 3352, 763, 1425, 636, 395, 280, 133, 886, 1124, 287, 34, 3102, 4587}},
	{NEXT,V4,LG_TPLCD,WHITE,{5194, 2464, 942, 897, 812, 845, 1329, 714, 284, 190, 84, 3688, 5435, 1698, 138, 2844, 4855}},
	{NEXT,V4,LG_TPLCD,GOLD,{5160, 2469,  3263, 2996, 2912, 851, 1306, 728, 193, 133, 61, 1142, 1661, 497, 40, 3011, 4719}},
	{NEXT,V4,LG_TPLCD,GRAY,{5917, 2671, 4969, 3860, 3352, 763, 1425, 636, 395, 280, 133, 886, 1124, 287, 34, 3102, 4587}},
	{NEXT,V4,JDI_TPLCD,BLACK,{5917, 2671, 4969, 3860, 3352, 763, 1425, 636, 395, 280, 133, 886, 1124, 287, 34, 3102, 4587}},
	{NEXT,V4,JDI_TPLCD,WHITE,{5194, 2464, 942, 897, 812, 845, 1329, 714, 284, 190, 84, 3688, 5435, 1698, 138, 2844, 4855}},
	{NEXT,V4,JDI_TPLCD,GOLD,{5160, 2469,  3263, 2996, 2912, 851, 1306, 728, 193, 133, 61, 1142, 1661, 497, 40, 3011, 4719}},
	{NEXT,V4,JDI_TPLCD,GRAY,{5917, 2671, 4969, 3860, 3352, 763, 1425, 636, 395, 280, 133, 886, 1124, 287, 34, 3102, 4587}},
};
static struct gyro_platform_data gyro_data={
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval=10,
	.axis_map_x=1,
	.axis_map_y=0,
	.axis_map_z=2,
	.negate_x=1,
	.negate_y=0,
	.negate_z=1,
	.gpio_int1=210,
};
static struct g_sensor_platform_data gsensor_data={
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval=10,
	.axis_map_x=1,
	.axis_map_y=0,
	.axis_map_z=2,
	.negate_x=0,
	.negate_y=1,
	.negate_z=0,
	.gpio_int1=208,
};
static struct compass_platform_data mag_data={
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval=10,
	.outbit=0,
	.axis_map_x=0,
	.axis_map_y=1,
	.axis_map_z=2,
};
static struct als_platform_data als_data={
	.bustype = TAG_I2C,
	.busnum = 0,
	.threshold_value = 1,
	.GA1 = 4166,
	.GA2 = 3000,
	.GA3 = 3750,
	.COE_B = 0,
	.COE_C = 0,
	.COE_D = 0,
	.gpio_int1 = 206,
	.atime = 0xdb,
	.again = 1,
	.poll_interval = 1000,
	.init_time = 150,
	.als_phone_type = 0,
	.als_phone_version =0,
};

static struct ps_platform_data ps_data={
	.bustype = TAG_I2C,
	.busnum = 0,
	.min_proximity_value = 750,
	.pwindows_value = 100,
	.pwave_value = 60,
	.threshold_value = 70,
	.rdata_under_sun = 5500,
	.ps_pulse_count = 5,
	.gpio_int1 = 206,
	.persistent = 0x33,
	.ptime = 0xFF,
	.poll_interval = 250,
	.init_time = 100,
};

static struct airpress_platform_data airpress_data={
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval = 1000,
};

static struct handpress_platform_data handpress_data={
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval = 500,
};

static struct cap_prox_platform_data cap_prox_data={
	.bustype = TAG_I2C,
	.busnum = 0,
	.init_reg_val = {
		0x00010005, 0x00020529, 0x000300cc, 0x00040001, 0x00050F55,
		0x00069905, 0x000700e8, 0x00080200, 0x00090000, 0x000a000C, 0x00798000,
		0x000b9905, 0x000c00e8, 0x000d0200, 0x000e0000, 0x000f000C, 0x007a8000
	},
	.poll_interval = 200,
};

static bool should_be_processed_when_sr(int sensor_tag)
{
	bool ret = true;//can be closed default
	switch (sensor_tag) {
		case TAG_PS:
			ret = false;
			break;
		case TAG_STEP_COUNTER:
			ret = false;
			break;

		default:
			break;
	}

	return ret;
}

static DEFINE_MUTEX(mutex_update);
void update_sensor_info(const pkt_header_t *pkt)//To keep same with mcu, to activate sensor need open first and then setdelay
{
	if (TAG_SENSOR_BEGIN <= pkt->tag && pkt->tag < TAG_SENSOR_END) {
		mutex_lock(&mutex_update);
		if (CMD_CMN_OPEN_REQ == pkt->cmd) {
			sensor_status.opened[pkt->tag] = 1;
		} else if (CMD_CMN_CLOSE_REQ == pkt->cmd) {
			sensor_status.opened[pkt->tag] = 0;
			sensor_status.status[pkt->tag] = 0;
			sensor_status.delay[pkt->tag] = 0;
		} else if (CMD_CMN_INTERVAL_REQ == pkt->cmd) {
			if (sensor_status.opened[pkt->tag]) {
				sensor_status.delay[pkt->tag] = ((const pkt_cmn_interval_req_t *)pkt)->param.period;
				sensor_status.status[pkt->tag] = 1;
			}
		}
		mutex_unlock(&mutex_update);
	}
}
void disable_sensors_when_reboot(void)
{
	int tag = 0;
	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		if (sensor_status.status[tag]) {
			inputhub_sensor_enable(tag, false);
			msleep(50);
			hwlog_info("disable sensor - %d before reboot\n", tag);
		}
	}
}

void disable_sensors_when_suspend(void)
{
	int tag = 0;

	memset(&sensor_status_backup, 0, sizeof(sensor_status_backup));
	memcpy(&sensor_status_backup, &sensor_status, sizeof(sensor_status_backup));
	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		if (sensor_status_backup.status[tag]) {
			if (should_be_processed_when_sr(tag)) {
				inputhub_sensor_enable(tag, false);
			}
		}
	}
}

void enable_sensors_when_resume(void)
{
	int tag = 0;

	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		if (sensor_status_backup.status[tag] && (0 == sensor_status.status[tag])) {
			if (should_be_processed_when_sr(tag)) {
				inputhub_sensor_enable(tag, true);
				inputhub_sensor_setdelay(tag, sensor_status_backup.delay[tag]);
			}
		}
	}
}

void dmd_log_report(int dmd_mark,const char *err_func, const char *err_msg)
{
	if(!dsm_client_ocuppy(shb_dclient)){
		dsm_client_record(shb_dclient, "[%s]%s", err_func, err_msg);
		dsm_client_notify(shb_dclient, dmd_mark);
	}
}

static uint8_t gsensor_calibrate_data[MAX_MAG_CALIBRATE_DATA_LENGTH];
static uint8_t msensor_calibrate_data[MAX_MAG_CALIBRATE_DATA_LENGTH];
static uint8_t ps_sensor_calibrate_data[MAX_MAG_CALIBRATE_DATA_LENGTH];
static uint8_t als_sensor_calibrate_data[MAX_MAG_CALIBRATE_DATA_LENGTH];
static uint8_t gyro_sensor_calibrate_data[MAX_MAG_CALIBRATE_DATA_LENGTH];
/*******************************************************************************************
Function:	read_gsensor_offset_from_nv
Description:   读取NV项中的gsensor 校准数据，并发送给mcu 侧
Data Accessed:  无
Data Updated:   无
Input:         无
Output:         无
Return:         成功或者失败信息: 0->成功, -1->失败
*******************************************************************************************/
int read_gsensor_offset_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;
	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = ACC_OFFSET_NV_NUM;
	user_info.valid_size = ACC_OFFSET_NV_SIZE;
	strncpy(user_info.nv_name, "gsensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}
	first_start_flag=1;
	//copy to gsensor_offset by pass
	memcpy(gsensor_offset, user_info.nv_data, sizeof(gsensor_offset));
	hwlog_info( "nve_direct_access read gsensor_offset (%d %d %d )\n",gsensor_offset[0],gsensor_offset[1],gsensor_offset[2]);

	gsensor_data.offset_x=gsensor_offset[0];
	gsensor_data.offset_y=gsensor_offset[1];
	gsensor_data.offset_z=gsensor_offset[2];
	pkg_ap.tag=TAG_ACCEL;
	pkg_ap.cmd=CMD_ACCEL_OFFSET_REQ;
	pkg_ap.wr_buf=&gsensor_data.offset_x;
	pkg_ap.wr_len=sizeof(int)*3;
	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	memcpy(&gsensor_calibrate_data, pkg_ap.wr_buf, sizeof(gsensor_calibrate_data));
	if(ret)
	{
		hwlog_err("send gsensor offset data to mcu fail,ret=%d\n", ret);
		return -1;
	}
	if(pkg_mcu.errno!=0)
	{
		hwlog_err("set gsensor offset fail,err=%d\n", pkg_mcu.errno);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set gsensor offset fail\n");
	}
	else
	{
		hwlog_info("send gsensor offset data to mcu success\n");
	}
	return 0;
}

/*******************************************************************************************
Function:	write_gsensor_offset_to_nv
Description:  将temp数据写入NV 项中
Data Accessed:  无
Data Updated:   无
Input:        g-sensor 校准值
Output:         无
Return:         成功或者失败信息: 0->成功, -1->失败
*******************************************************************************************/
int write_gsensor_offset_to_nv(char* temp)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	const int32_t *poffset_data = (const int32_t *)user_info.nv_data;

	if(temp==NULL)
	{
		hwlog_err("write_gsensor_offset_to_nv fail, invalid para!\n");
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "write_gsensor_offset_to_nv fail, invalid para!\n");
		return -1;
	}
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = ACC_OFFSET_NV_NUM;
	user_info.valid_size = ACC_OFFSET_NV_SIZE;
	strncpy(user_info.nv_name, "gsensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';

	//copy to nv by pass
	memcpy(user_info.nv_data, temp, sizeof(user_info.nv_data));
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	hwlog_info( "nve_direct_access write temp (%d %d %d )\n", *poffset_data, *(poffset_data + 1), *(poffset_data + 2));
	return ret;
}

int read_gyro_sensor_offset_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;
	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = GYRO_CALIDATA_NV_NUM;
	user_info.valid_size = GYRO_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "GYRO", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}
	gyro_first_start_flag=1;
	//copy to gsensor_offset by pass
	memcpy(gyro_sensor_offset, user_info.nv_data, sizeof(gyro_sensor_offset));
	hwlog_info( "nve_direct_access read gyro_sensor_offset (%d %d %d )\n",gyro_sensor_offset[0],gyro_sensor_offset[1],gyro_sensor_offset[2]);

	pkg_ap.tag=TAG_GYRO;
	pkg_ap.cmd=CMD_GYRO_OFFSET_REQ;
	pkg_ap.wr_buf=gyro_sensor_offset;    //?????
	pkg_ap.wr_len=sizeof(int)*3;
	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	memcpy(&gyro_sensor_calibrate_data, pkg_ap.wr_buf, sizeof(gyro_sensor_calibrate_data));
	if(ret)
	{
		hwlog_err("send gyro_sensor offset data to mcu fail,ret=%d\n", ret);
		return -1;
	}
	if(pkg_mcu.errno!=0)
	{
		hwlog_err("set gyro_sensor offset fail,err=%d\n", pkg_mcu.errno);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set gyro_sensor offset fail\n");
	}
	else
	{
		hwlog_info("send gyro_sensor offset data to mcu success\n");
	}
	return 0;
}

int write_gyro_sensor_offset_to_nv(char* temp)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	const int32_t *poffset_data = (const int32_t *)user_info.nv_data;

	if(temp==NULL)
	{
		hwlog_err("write_gyro_sensor_offset_to_nv fail, invalid para!\n");
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "write_gyro_sensor_offset_to_nv fail, invalid para!\n");
		return -1;
	}
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = GYRO_CALIDATA_NV_NUM;
	user_info.valid_size = GYRO_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "GYRO", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';

	//copy to nv by pass
	memcpy(user_info.nv_data, temp, sizeof(user_info.nv_data));
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	hwlog_info( "gyro calibrate data (%d %d %d )\n", *poffset_data, *(poffset_data + 1), *(poffset_data + 2));
	return ret;
}

int read_mag_calibrate_data_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t pkg_ap;
	read_info_t  pkg_mcu;
	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	//read from nv
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = MAG_CALIBRATE_DATA_NV_NUM;
	user_info.valid_size = MAG_CALIBRATE_DATA_NV_SIZE;
	strncpy(user_info.nv_name, "msensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0) {
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}

	//send to mcu
	pkg_ap.tag = TAG_MAG;
	pkg_ap.cmd = CMD_MAG_SET_CALIBRATE_TO_MCU_REQ;
	pkg_ap.wr_buf = &user_info.nv_data;
	pkg_ap.wr_len = MAG_CALIBRATE_DATA_NV_SIZE;
	memcpy(&msensor_calibrate_data, pkg_ap.wr_buf, sizeof(msensor_calibrate_data));
	if((ret = write_customize_cmd(&pkg_ap, &pkg_mcu)) != 0) {
		hwlog_err("set mag_sensor data failed, ret = %d!\n", ret);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set mag_sensor data failed\n");
		return -1;
	}

	if(pkg_mcu.errno!=0)
	{
		hwlog_err("set mag offset fail,err=%d\n", pkg_mcu.errno);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set mag offset fail\n");
	}
	else
	{
		hwlog_info("send mag_sensor data %d, %d, %d to mcu success\n", *((uint32_t*)pkg_ap.wr_buf), *((uint32_t*)pkg_ap.wr_buf + 1),*((uint32_t*)pkg_ap.wr_buf + 2) );
	}

	return 0;
}

static int write_magsensor_calibrate_data_to_nv(const char *src)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;

	if(NULL == src) {
		hwlog_err("%s fail, invalid para!\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "invalid para\n");
		return -1;
	}

	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = MAG_CALIBRATE_DATA_NV_NUM;
	user_info.valid_size = MAG_CALIBRATE_DATA_NV_SIZE;
	strncpy(user_info.nv_name, "msensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	memcpy(user_info.nv_data, src, sizeof(user_info.nv_data));
	if ((ret = hisi_nve_direct_access(&user_info)) != 0) {
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -1;
	}

	return ret;
}

static int mag_calibrate_data_from_mcu(const pkt_header_t *head)
{
	return write_magsensor_calibrate_data_to_nv(((const pkt_mag_calibrate_data_req_t *)head)->calibrate_data);
}

int read_airpress_calibrate_data_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t pkg_ap;
	read_info_t  pkg_mcu;
	if(strlen(sensor_chip_info[AIRPRESS]) == 0)
		return 1;

	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = AIRPRESS_CALIDATA_NV_NUM;
	user_info.valid_size = AIRPRESS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "AIRDATA", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0) {
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}
	//send to mcu
	pkg_ap.tag = TAG_PRESSURE;
	pkg_ap.cmd = CMD_AIRPRESS_SET_CALIDATA_REQ;
	pkg_ap.wr_buf = (const void *)&airpress_data;
	pkg_ap.wr_len = sizeof(airpress_data);
	memcpy(&airpress_data.offset, user_info.nv_data, AIRPRESS_CALIDATA_NV_SIZE);
	hwlog_info("***%s***\n",__func__);
	if((ret = write_customize_cmd(&pkg_ap, &pkg_mcu)) != 0) {
		hwlog_err("set airpress_sensor data failed, ret = %d!\n", ret);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set airpress_sensor data failed\n");
		return -1;
	}
	if(pkg_mcu.errno!=0)
	{
		hwlog_err("set airpress_sensor offset fail,err=%d\n", pkg_mcu.errno);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set airpress_sensor offset fail\n");
	}
	else
	{
		hwlog_info("send airpress_sensor data %d to mcu success\n", airpress_data.offset);
	}

	return 0;
}

int read_cap_prox_calibrate_data_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t pkg_ap;

	if(strlen(sensor_chip_info[CAP_PROX]) == 0)
		return -1;

	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));

	//read from nv
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = CAP_PROX_CALIDATA_NV_NUM;
	user_info.valid_size = CAP_PROX_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "Csensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0) {
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}

	//send to mcu
	pkg_ap.tag = TAG_CAP_PROX;
	pkg_ap.cmd = CMD_CAP_PROX_SET_CALIDATA_REQ;
	pkg_ap.wr_buf = (const void *)cap_prox_data.freespace;
	pkg_ap.wr_len = CAP_PROX_CALIDATA_NV_SIZE;
	memcpy(cap_prox_data.freespace, user_info.nv_data, CAP_PROX_CALIDATA_NV_SIZE);
	if((ret = write_customize_cmd(&pkg_ap, NULL)) != 0) {
		hwlog_err("set cap_prox_sensor data failed, ret = %d!\n", ret);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set cap_prox_sensor data failed\n");
		return ret;
	} else {
		hwlog_info("send cap_prox_sensor data to mcu success\n");
	}

	return 0;
}

int read_ps_offset_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;
	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = PS_CALIDATA_NV_NUM;
	user_info.valid_size = PS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "PSENSOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}
	ps_first_start_flag=1;

	ps_sensor_offset = (int)user_info.nv_data[0];

	hwlog_info( "nve_direct_access read ps_offset (%d )\n",ps_sensor_offset);

	pkg_ap.tag=TAG_PS;
	pkg_ap.cmd=CMD_PS_OFFSET_REQ;
	pkg_ap.wr_buf=&ps_sensor_offset;
	pkg_ap.wr_len=sizeof(int);
	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	memcpy(&ps_sensor_calibrate_data, pkg_ap.wr_buf, sizeof(ps_sensor_calibrate_data));
	if(ret)
	{
		hwlog_err("send psensor offset data to mcu fail,ret=%d\n", ret);
		return -1;
	}
	if(pkg_mcu.errno!=0)
	{
		hwlog_err("set psensor offset fail,err=%d\n", pkg_mcu.errno);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set psensor offset fail\n");
	}
	else
	{
		hwlog_info("send psensor offset data to mcu success\n");
	}
	return 0;
}


int write_ps_offset_to_nv(int* temp)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;

	if(temp==NULL)
	{
		hwlog_err("write_ps_offset_to_nv fail, invalid para!\n");
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "write_ps_offset_to_nv fail, invalid para!\n");
		return -1;
	}
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = PS_CALIDATA_NV_NUM;
	user_info.valid_size = PS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "PSENSOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';

	user_info.nv_data[0] = temp[0];
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	hwlog_info( "nve_direct_access write temp (%d)\n",user_info.nv_data[0]);

	msleep(10);
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = PS_CALIDATA_NV_NUM;
	user_info.valid_size = PS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "PSENSOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve direct access read error(%d)\n", ret);
		return -1;
	}
	if(user_info.nv_data[0] != temp[0])
	{
		hwlog_err("nv write fail, (%d)\n", user_info.nv_data[0]);
		return -1;
	}
	return ret;
}

int read_als_offset_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;
	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = ALS_CALIDATA_NV_NUM;
	user_info.valid_size = ALS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "LSENSOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}

	als_first_start_flag=1;
	memcpy(als_offset, user_info.nv_data, sizeof(als_offset));
	hwlog_info( "nve_direct_access read lsensor_offset (%d %d %d %d %d %d)\n",als_offset[0],als_offset[1],als_offset[2],als_offset[3],als_offset[4],als_offset[5]);

	pkg_ap.tag=TAG_ALS;
	pkg_ap.cmd=CMD_ALS_OFFSET_REQ;
	pkg_ap.wr_buf=als_offset;
	pkg_ap.wr_len=ALS_CALIDATA_NV_SIZE;
	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	memcpy(&als_sensor_calibrate_data, pkg_ap.wr_buf, sizeof(als_sensor_calibrate_data));
	if(ret)
	{
		hwlog_err("send als offset data to mcu fail,ret=%d\n", ret);
		return -1;
	}
	if(pkg_mcu.errno!=0)
	{
		hwlog_err("set als offset fail,err=%d\n", pkg_mcu.errno);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set als offset fail\n");
	}
	else
	{
		hwlog_info("send als offset data to mcu success\n");
	}
	return 0;
}


int write_als_offset_to_nv(char* temp)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	const uint16_t *poffset_data = (const uint16_t *)user_info.nv_data;

	if(temp==NULL)
	{
		hwlog_err("write_als_offset_to_nv fail, invalid para!\n");
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "write_als_offset_to_nv fail, invalid para!\n");
		return -1;
	}
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = ALS_CALIDATA_NV_NUM;
	user_info.valid_size = ALS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "LSENSOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';

	//copy to nv by pass
	memcpy(user_info.nv_data, temp, sizeof(user_info.nv_data));
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	hwlog_info( "nve_direct_access als write temp (%d %d %d %d %d %d  )\n", *poffset_data, *(poffset_data + 1), *(poffset_data + 2),*(poffset_data + 3), *(poffset_data + 4),*(poffset_data + 5));
	return ret;
}


void enable_sensors_when_recovery_iom3(void)
{
	int tag;

	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		if (sensor_status.status[tag]) {
			inputhub_sensor_enable_nolock(tag, true);
			inputhub_sensor_setdelay_nolock(tag, sensor_status.delay[tag]);
		}
	}
}

int write_customize_cmd_noresp(int tag, int cmd, const void *data, int length)
{
	uint8_t buf[MAX_PKT_LENGTH] = {0};//

	((pkt_header_t *)buf)->tag = tag;
	((pkt_header_t *)buf)->cmd = cmd;
	((pkt_header_t *)buf)->resp = NO_RESP;
	((pkt_header_t *)buf)->length = length;
	memcpy(buf + sizeof(pkt_header_t), data, ((pkt_header_t *)buf)->length);
	return inputhub_mcu_write_cmd_nolock(&buf, sizeof(pkt_header_t) + ((pkt_header_t *)buf)->length);
}
void reset_calibrate_when_recovery_iom3(void)
{
	write_customize_cmd_noresp(TAG_ACCEL, CMD_ACCEL_OFFSET_REQ, &gsensor_calibrate_data, sizeof(int) * 3);
	//write_customize_cmd_noresp(TAG_MAG, CMD_MAG_SET_CALIBRATE_TO_MCU_REQ, &msensor_calibrate_data, MAG_CALIBRATE_DATA_NV_SIZE);
	if (txc_ps_flag == 1) {
	write_customize_cmd_noresp(TAG_PS, CMD_PS_OFFSET_REQ, &ps_sensor_calibrate_data, sizeof(int));
	}
	if (rohm_rgb_flag == 1 || avago_rgb_flag == 1) {
	write_customize_cmd_noresp(TAG_ALS, CMD_ALS_OFFSET_REQ, &als_sensor_calibrate_data, sizeof(int)* 3);
	}
}

static int detect_i2c_device(struct device_node *dn, char *device_name)
{
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;
	pkt_i2c_read_req_t pkt_i2c_read;
	int i=0, ret=0, i2c_address=0, i2c_bus_num=0, register_add=0, len=0;
	u32 wia[10]={0};
	struct property *prop = NULL;

	memset(&pkt_i2c_read, 0, sizeof(pkt_i2c_read));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if(of_property_read_u32(dn, "bus_number", &i2c_bus_num) || of_property_read_u32(dn, "reg", &i2c_address)
				|| of_property_read_u32(dn, "chip_id_register", &register_add))
	{
		hwlog_err("%s:read i2c bus_number (%d)or bus address(%x) or chip_id_register(%x) from dts fail\n",
			device_name, i2c_bus_num, i2c_address, register_add);
		dmd_log_report(DSM_SHB_ERR_DYNLOAD, __func__, "read i2c bus_number or bus address or chip_id_register from dts fail\n");
		return -1;
	}

	prop = of_find_property(dn, "chip_id_value", NULL);
	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;
	len = prop->length/4;

	if(of_property_read_u32_array(dn, "chip_id_value", wia, len))
	{
		hwlog_err("%s:read chip_id_value (id0=%x) from dts fail len=%d\n", device_name,  wia[0], len);
		dmd_log_report(DSM_SHB_ERR_DYNLOAD, __func__, "read chip_id_value from dts fail\n");
		return -1;
	}

	hwlog_info("%s:read i2c bus_number (%d) slave address(0x%x) chip_id_register(0x%x) chipid value 0x%x 0x%x 0x%x 0x%x\n",
			device_name, i2c_bus_num, i2c_address, register_add, wia[0], wia[1], wia[2], wia[3]);
	pkt_i2c_read.busid = i2c_bus_num;
	pkt_i2c_read.addr = i2c_address;
	pkt_i2c_read.reg = register_add;
	pkt_i2c_read.length = 1;
	pkg_ap.tag = TAG_I2C;
	pkg_ap.cmd = CMD_I2C_READ_REQ;
	pkg_ap.wr_buf = &pkt_i2c_read.busid;
	pkg_ap.wr_len = sizeof(pkt_i2c_read) - sizeof(pkt_i2c_read.hd);
	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	if(ret)
	{
		hwlog_err("%s:detect_i2c_device:send i2c read cmd to mcu fail,ret=%d\n", device_name, ret);
		return -1;
	}
	if(pkg_mcu.errno != 0)
	{
		hwlog_err("%s:detect_i2c_device:i2c read fail\n", device_name);
		return -1;
	}else
	{
		for(i=0;i<len;i++){
			if(pkg_mcu.data[0] == (char)wia[i])
			{
				hwlog_info("%s:i2c detect  suc!chip_value:0x%x\n", device_name,pkg_mcu.data[0]);
				return 0;
			}
		}
		hwlog_info("%s:i2c detect fail,chip_value:0x%x!\n", device_name,pkg_mcu.data[0]);
		return -1;
	}
}

/* delete the repeated file id by map table*/
static uint8_t check_file_list(uint8_t file_count, uint16_t *file_list)
{
	uint8_t map[MAX_FILE_ID];
	int i;
	uint8_t count = 0;

	memset(map, 0, sizeof(map));
	if ((file_count == 0) ||(NULL == file_list)) {
		hwlog_err("%s, val invalid\n", __func__);
		dmd_log_report(DSM_SHB_ERR_DYNLOAD, __func__, "val invalid\n");
		return count;
	}

	for (i = 0; i < file_count; i++) {
		if (file_list[i] < sizeof(map))
			map[file_list[i]]++;
	}

	for(i = 0; i < sizeof(map); i++) {
		if (map[i]) {
			file_list[count] = i;
			count ++;
		}
	}

	return count;
}

int send_fileid_to_mcu(void)
{
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;
	int ret = 0;

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	dyn_req->end = 1;
	pkg_ap.tag = TAG_SYS;
	pkg_ap.cmd = CMD_SYS_DYNLOAD_REQ;
	pkg_ap.wr_buf = &(dyn_req->end);
	pkg_ap.wr_len = dyn_req->file_count * sizeof(dyn_req->file_list[0])
					+ sizeof(dyn_req->end) + sizeof(dyn_req->file_count);

	if (g_iom3_state == IOM3_ST_RECOVERY)
		ret = write_customize_cmd_noresp(TAG_SYS, CMD_SYS_DYNLOAD_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
	else
		ret = write_customize_cmd(&pkg_ap, &pkg_mcu);

	if (ret)
	{
		hwlog_err("send file id to mcu fail,ret=%d\n", ret);
                dmd_log_report(DSM_SHB_ERR_DYNLOAD, __func__, "send file id to mcu fail\n");
		return -1;
	}
	if (pkg_mcu.errno != 0)
	{
		hwlog_err("file id set fail\n");
		dmd_log_report(DSM_SHB_ERR_DYNLOAD, __func__, "file id set fail\n");
		return -1;
	}

	return 0;
}

static bool check_sensorhub_isensor_version(void)
{
    int len = 0;
    struct device_node *sensorhub_node = NULL;
    const char *is_isensor = NULL;
    sensorhub_node = of_find_compatible_node(NULL, NULL, "huawei,sensorhub");
    if (!sensorhub_node) {
        hwlog_err("%s, can't find node sensorhub\n", __func__);
        dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "can't find node sensorhub\n");
        return false;
    }
    is_isensor = of_get_property(sensorhub_node, "isensor_version", &len);
    if (!is_isensor) {
        hwlog_err("%s, can't find property isensor_version\n", __func__);
        dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "can't find property isensor_version\n");
        return false;
    }
     if (strstr(is_isensor, "yes")) {
        hwlog_info("%s, sensorhub is isensor interface version\n", __func__);
        return true;
    } else {
        hwlog_info("%s, sensorhub is not isensor interface version\n", __func__);
        return false;
    }
}
static int mcu_i2c_rw(uint8_t bus_num, uint8_t i2c_add, uint8_t register_add, uint8_t rw, int len, uint8_t *buf)
{
	int ret=0;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;
	pkt_i2c_read_req_t pkt_i2c_read;
	pkt_i2c_write_req_t *pkt_i2c_write = kzalloc(sizeof(pkt_i2c_write_req_t)+len,GFP_KERNEL);
	memset(&pkt_i2c_read, 0, sizeof(pkt_i2c_read));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));

	switch (rw) {
		case 1:	//in order to support the users before,add this case branch
			rw = CMD_I2C_READ_REQ;
		case CMD_I2C_READ_REQ:
		case CMD_I2C_READ_ONLY_REQ:
			pkt_i2c_read.busid = bus_num;
			pkt_i2c_read.addr = i2c_add;
			pkt_i2c_read.reg = register_add;
			pkt_i2c_read.length = len;
			pkg_ap.tag = TAG_I2C;
			pkg_ap.cmd = rw;
			pkg_ap.wr_buf = &pkt_i2c_read.busid;
			pkg_ap.wr_len = sizeof(pkt_i2c_read) - sizeof(pkt_i2c_read.hd);
			break;
		case 0:	//in order to support the users before ,add this case branch
			rw = CMD_I2C_WRITE_REQ;
		case CMD_I2C_WRITE_REQ:
		case CMD_I2C_WRITE_ONLY_REQ:
			pkt_i2c_write->busid = bus_num;
			pkt_i2c_write->addr = i2c_add;
			pkt_i2c_write->reg = register_add;
			pkt_i2c_write->length= len;
			memcpy(pkt_i2c_write->data, buf, len);
			pkg_ap.tag = TAG_I2C;
			pkg_ap.cmd = rw;
			pkg_ap.wr_buf = &pkt_i2c_write->busid;
			pkg_ap.wr_len = sizeof(*pkt_i2c_write) - sizeof(pkt_i2c_write->hd) + len;
			break;
		default:
			hwlog_err("rw err:%d\n", rw);
			break;
	}

	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	if(ret) {
		hwlog_err("send i2c cmd to mcu fail, addr=%d, reg=%d,rw=%d\n", i2c_add, register_add, rw);
		kfree(pkt_i2c_write);
		return -1;
	}
	if(pkg_mcu.errno != 0) {
		hwlog_err("mcu_i2c_rw fail, addr=%d, reg=%d,rw=%d\n", i2c_add, register_add, rw);
		dmd_log_report(DSM_SHB_ERR_I2C_DBG, __func__, "mcu_i2c_rw fail\n");
		kfree(pkt_i2c_write);
		return -1;
	} else {
		if (rw == CMD_I2C_READ_REQ || rw ==CMD_I2C_READ_ONLY_REQ) {
			memcpy(buf, pkg_mcu.data, len);
		}
		kfree(pkt_i2c_write);
		return pkg_mcu.data_length;
	}
}
static int get_adapt_sensor_list_id(void)
{
	u32 wia[10]={0};
	struct property *prop = NULL;
	unsigned int i = 0, len = 0;
	struct device_node *sensorhub_node = NULL;
	const char *name = "adapt_sensor_list_id";
	sensorhub_node = of_find_compatible_node(NULL, NULL, "huawei,sensorhub");
	if (!sensorhub_node) {
		hwlog_err("%s, can't find node sensorhub\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "can't find node sensorhub\n");
		return -1;
	}
	prop = of_find_property(sensorhub_node, name, NULL);
	if (!prop) {
		hwlog_err("%s! prop is NULL!\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, " prop is NULL\n");
		return -EINVAL;
	}
	if (!prop->value) {
		hwlog_err("%s! prop->value is NULL!\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "prop->value is NULL\n");
		return -ENODATA;
	}
	len = prop->length / 4;
	if(of_property_read_u32_array(sensorhub_node, name, wia, len))
	{
		hwlog_err("%s:read adapt_sensor_list_id from dts fail!\n", name);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "read adapt_sensor_list_id from dts fail\n");
		return -1;
	}
	for (i = 0; i < len; i++) {
		sensorlist[sensorlist[0]+1] = (uint16_t)wia[i];
		sensorlist[0]++;
	}
	return 0;
}

static int fill_extend_data_in_dts(struct device_node *dn, const char *name, unsigned char *dest, size_t max_size, int flag)
{
	int ret = 0;
	int buf[SENSOR_PLATFORM_EXTEND_DATA_SIZE] = {0};
	struct property *prop = NULL;
	unsigned int len = 0;
	unsigned int i = 0;
	int *pbuf = buf;
	unsigned char *pdest = dest;
	if (!dn || !name || !dest) {
		return -1;
	}
	if (0 == max_size) {
		return -1;
	}
	prop = of_find_property(dn, name, NULL);
	if (!prop) {
		return -EINVAL;
	}
	if (!prop->value) {
		return -ENODATA;
	}
	len = prop->length / 4;//len: word
	if (0 == len || len > max_size) {
		hwlog_err("In %s: len err! len = %d\n", __func__, len);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "len err\n");
		return -1;
	}
	ret = of_property_read_u32_array(dn, name, buf, len);
	if (ret) {
		hwlog_err("In %s: read %s failed!\n", __func__, name);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "read failed\n");
		return -1;
	}
	if (EXTEND_DATA_TYPE_IN_DTS_BYTE == flag) {
		for (i = 0; i < len; i++) {
			*(dest + i) = (uint8_t)buf[i];
		}
	}
	if (EXTEND_DATA_TYPE_IN_DTS_HALF_WORD == flag) {
		for (i = 0; i < len; i++) {
			memcpy(pdest, pbuf, 2);
			pdest += 2;
			pbuf++;
		}
	}
	if (EXTEND_DATA_TYPE_IN_DTS_WORD == flag) {
		memcpy(dest, buf, len * sizeof(int));
	}
	return 0;
}

static int handpress_sensor_detect(struct device_node *dn, struct handpress_platform_data *handpress_data)
{
	int ret = 0;
	int chip_check_result = 0;
	struct device_node  *temp = NULL;
	int num_handpress = 0;
	const char *state = NULL;
	int chips = 0;
	u32 bus_num = 0;
	u32 id = 0, irq=0, points = 0, reg = 0;
	char chip_value[12] = {0xff, 0xff, 0x00};
	char chip_check_cmd_default[8] = {0x01, 0x40, 0x01, 0x00, 0x00, 0xBE, 0xFF, 0x17};
//	char chip_check_value_default[10] = {0x01, 0x00, 0x03, 0x00, 0x02, 0x00, 0xf7, 0x03, 0xff, 0x17};
	char chip_check_cmd[8] = {0x00};
//	char chip_check_value[10] = {0x00};

	ret = of_property_read_u32(dn, "bus_number", &bus_num);
	if (ret) {
		hwlog_err("get bus_num err ret:%d\n", ret);
		goto out;
	}
#if 0
	ret = of_property_read_u32(dn, "chip_id_register", &chip_id_reg);
	if (ret) {
		hwlog_err("get chip_id_reg err ret:%d\n", ret);
		goto out;
	}
#endif
	ret = of_property_read_u8_array(dn, "chip_check_cmd", &chip_check_cmd[0], 8);
	if (ret) {
		hwlog_err("get chip_check_cmd err ret:%d\n", ret);
		memcpy(chip_check_cmd, chip_check_cmd_default, sizeof(chip_check_cmd));
		//goto out;
	}
#if 0
	ret = of_property_read_u8_array(dn, "chip_id_value", chip_check_value, 10);
	if (ret) {
		hwlog_err("get chip_id_value err ret:%d\n", ret);
		memcpy(chip_check_value, chip_check_value_default, sizeof(chip_check_value));
		//goto out;
	}
#endif
	while((temp = of_get_next_child(dn, temp)))
		num_handpress++;

	if (!num_handpress)
		return -ECHILD;

	for_each_child_of_node(dn, temp) {
		ret = of_property_read_string(temp, HANDPRESS_DEFAULT_STATE, &state);
		if (!ret) {
			if (strncmp(state, "on", sizeof("on")) == 0) {
				if (chips >= CYPRESS_CHIPS) {
					hwlog_err("The number of chips overflow\n");
					break;
				}
				ret = of_property_read_u32(temp, "huawei,id", &id);
				if (ret) {
					hwlog_err("huawei,id ret:%d\n", ret);
					break;
				}
				handpress_data->id[chips] = id;

				ret = of_property_read_u32(temp, "huawei,irq", &irq);
				if (ret) {
					hwlog_err("huawei,irq ret:%d\n", ret);
					break;
				}
				handpress_data->irq[chips] = irq;

				ret = of_property_read_u32(temp, "huawei,points", &points);
				if (ret) {
					hwlog_err("huawei, points ret:%d\n", ret);
					break;
				}
				handpress_data->t_pionts[chips] = points;

				ret = of_property_read_u32(temp, "reg", &reg);
				if (ret) {
					hwlog_err("reg ret:%d\n", ret);
					break;
				}
				handpress_data->i2c_address[chips] = reg;
				ret = mcu_i2c_rw(bus_num, reg, 0x00, CMD_I2C_WRITE_ONLY_REQ, sizeof(chip_check_cmd)/sizeof(chip_check_cmd[0]), chip_check_cmd);
				if (ret < 0) {
					hwlog_err("mcu_i2c_rw write ret:%d\n", ret);
					chip_check_result |= 1<<id;
					continue;
				}
				msleep(10);
				ret = mcu_i2c_rw(bus_num, reg, 0x00, CMD_I2C_READ_ONLY_REQ, sizeof(chip_value)/sizeof(chip_value[0]), chip_value);
				if (ret < 0) {
					hwlog_err("mcu_i2c_rw read ret:%d\n", ret);
					chip_check_result |= 1<<id;
					continue;
				}
				if (chip_value[1]) {
					chip_check_result |= 1<<id;
					hwlog_err("handpress detect err! chip[%d]:%x\n", id, chip_value[1]);
					continue;
				}
				chips++;
			}
		}
	}

	if (!chip_check_result)
		ret = 0;
	else
		ret = -1;

	hwlog_info("handpress detect result:%d\n", ret);
out:
	return ret;
}

static void read_chip_info(struct device_node *dn, enum sensor_name sname)
{
	char *chip_info = NULL;
	int ret = 0;

	ret=of_property_read_string(dn, "compatible", (const char **)&chip_info);
	if(ret)
		hwlog_err("%s:read name_id:%d info fail\n",__func__,sname);
	else
		strncpy(sensor_chip_info[sname], chip_info, strlen(chip_info));

	hwlog_info("get chip info from dts success. sensor name=%s\n", sensor_chip_info[sname]);
}

const char *get_sensor_info_by_tag(int tag)
{
	enum sensor_name sname = SENSOR_MAX;

	switch (tag) {
	case TAG_ACCEL:
		sname = ACC;
		break;
	case TAG_MAG:
		sname = MAG;
		break;
	case TAG_GYRO:
		sname = GYRO;
		break;
	case TAG_ALS:
		sname = ALS;
		break;
	case TAG_PS:
		sname = PS;
		break;
	case TAG_PRESSURE:
		sname = AIRPRESS;
		break;
	case TAG_HANDPRESS:
		sname = HANDPRESS;
		break;
	case TAG_CAP_PROX:
		sname = CAP_PROX;
		break;

	default:
		hwlog_err("tag %d has no chip_info\n", tag);
		break;
	}

	return (sname != SENSOR_MAX) ? sensor_chip_info[sname] : "";
}

static void read_acc_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, ACC);

	temp = of_get_named_gpio(dn, "gpio_int1", 0);
	if (temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		gsensor_data.gpio_int1 = (uint8_t)temp;

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read acc poll_interval fail\n",__func__);
	else
		gsensor_data.poll_interval=(uint16_t)temp;

	if (of_property_read_u32(dn, "axis_map_x", &temp))
		hwlog_err("%s:read acc axis_map_x fail\n",__func__);
	else
		gsensor_data.axis_map_x=(uint8_t)temp;

	if (of_property_read_u32(dn, "axis_map_y", &temp))
		hwlog_err("%s:read acc axis_map_y fail\n",__func__);
	else
		gsensor_data.axis_map_y=(uint8_t)temp;

	if (of_property_read_u32(dn, "axis_map_z", &temp))
		hwlog_err("%s:read acc axis_map_z fail\n",__func__);
	else
		gsensor_data.axis_map_z=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_x", &temp))
		hwlog_err("%s:read acc negate_x fail\n",__func__);
	else
		gsensor_data.negate_x=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_y", &temp))
		hwlog_err("%s:read acc negate_y fail\n",__func__);
	else
		gsensor_data.negate_y=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_z", &temp))
		hwlog_err("%s:read acc negate_z fail\n",__func__);
	else
		gsensor_data.negate_z=(uint8_t)temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read acc file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read acc sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t)temp;
}

static void read_mag_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, MAG);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read mag poll_interval fail\n",__func__);
	else
		mag_data.poll_interval=(uint16_t)temp;

	if (of_property_read_u32(dn, "axis_map_x", &temp))
		hwlog_err("%s:read mag axis_map_x fail\n",__func__);
	else
		mag_data.axis_map_x=(uint8_t)temp;

	if (of_property_read_u32(dn, "axis_map_y", &temp))
		hwlog_err("%s:read mag axis_map_y fail\n",__func__);
	else
		mag_data.axis_map_y=(uint8_t)temp;

	if (of_property_read_u32(dn, "axis_map_z", &temp))
		hwlog_err("%s:read mag axis_map_z fail\n",__func__);
	else
		mag_data.axis_map_z=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_x", &temp))
		hwlog_err("%s:read mag negate_x fail\n",__func__);
	else
		mag_data.negate_x=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_y", &temp))
		hwlog_err("%s:read mag negate_y fail\n",__func__);
	else
		mag_data.negate_y=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_z", &temp))
		hwlog_err("%s:read mag negate_z fail\n",__func__);
	else
		mag_data.negate_z=(uint8_t)temp;

	if (of_property_read_u32(dn, "outbit", &temp))
		hwlog_err("%s:read mag outbit fail\n",__func__);
	else
		mag_data.outbit=(uint8_t)temp;

	if (of_property_read_u32(dn, "calibrate_method", &temp))
		hwlog_err("%s:read mag calibrate_method fail\n",__func__);
	else
		mag_data.calibrate_method=(uint8_t)temp;

	if (of_property_read_u32(dn, "reg", &temp))
		hwlog_err("%s:read mag reg fail\n",__func__);
	else
		mag_data.i2c_address=(uint8_t)temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read mag file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read mag sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t)temp;

	temp = of_get_named_gpio(dn, "gpio_reset", 0);
	if(temp < 0)
		hwlog_err("%s:read gpio_rst fail\n", __func__);
	else
		mag_data.gpio_rst = (uint8_t)temp;

}

static void read_gyro_data_from_dts(struct device_node *dn)
{
	int temp=0;

	read_chip_info(dn, GYRO);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read mag poll_interval fail\n",__func__);
	else
		gyro_data.poll_interval=(uint16_t)temp;

	if (of_property_read_u32(dn, "axis_map_x", &temp))
		hwlog_err("%s:read gyro axis_map_x fail\n",__func__);
	else
		gyro_data.axis_map_x=(uint8_t)temp;

	if (of_property_read_u32(dn, "axis_map_y", &temp))
		hwlog_err("%s:read gyro axis_map_y fail\n",__func__);
	else
		gyro_data.axis_map_y=(uint8_t)temp;

	if (of_property_read_u32(dn, "axis_map_z", &temp))
		hwlog_err("%s:read gyro axis_map_z fail\n",__func__);
	else
		gyro_data.axis_map_z=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_x", &temp))
		hwlog_err("%s:read gyro negate_x fail\n",__func__);
	else
		gyro_data.negate_x=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_y", &temp))
		hwlog_err("%s:read gyro negate_y fail\n",__func__);
	else
		gyro_data.negate_y=(uint8_t)temp;

	if (of_property_read_u32(dn, "negate_z", &temp))
		hwlog_err("%s:read gyro negate_z fail\n",__func__);
	else
		gyro_data.negate_z=(uint8_t)temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read gyro file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read gyro sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t)temp;

	temp = of_get_named_gpio(dn, "gpio_int1", 0);
	if(temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		gyro_data.gpio_int1 = (uint8_t)temp;
}

static void read_als_data_from_dts(struct device_node *dn)
{
	int temp=0;
	int als_phone_type =0;
	int als_phone_version = 0;
	int i = 0,ret = 0;
	char *chip_info = NULL;
	read_chip_info(dn, ALS);
	temp = of_property_read_string(dn, "compatible", (const char **)&chip_info);
	if(temp < 0)
		hwlog_err("%s:read als poll_interval fail\n", __func__);
	else
		strncpy(sensor_chip_info[ALS], chip_info, strlen(chip_info));

	if(!strncmp(chip_info, "huawei,rohm_bh1745", sizeof("huawei,rohm_bh1745"))){
		rohm_rgb_flag = 1;
		hwlog_err("%s:rohm_bh1745 i2c_address suc,%d \n",__func__,temp);
	}

	if(!strncmp(chip_info, "huawei,avago_apds9251", sizeof("huawei,avago_apds9251"))){
		avago_rgb_flag = 1;
		hwlog_err("%s:avago_apds9251 i2c_address suc,%d \n",__func__,temp);
	}

	temp = of_get_named_gpio(dn, "gpio_int1", 0);
	if(temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		als_data.gpio_int1 = (uint8_t)temp;

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read als poll_interval fail\n",__func__);
	else
		als_data.poll_interval=(uint16_t)temp;

	if (of_property_read_u32(dn, "init_time", &temp))
		hwlog_err("%s:read als init time fail\n",__func__);
	else
		als_data.init_time=(uint16_t)temp;

	if (of_property_read_u32(dn, "GA1", &temp))
		hwlog_err("%s:read als ga1 fail\n",__func__);
	else
		als_data.GA1=temp;

	if (of_property_read_u32(dn, "GA2", &temp))
		hwlog_err("%s:read als ga2 fail\n",__func__);
	else
		als_data.GA2=temp;

	if (of_property_read_u32(dn, "GA3", &temp))
		hwlog_err("%s:read als ga3 fail\n",__func__);
	else
		als_data.GA3=temp;

	if(of_property_read_u32(dn, "als_phone_type", &als_phone_type))
		hwlog_err("%s:read als_phone_type fail\n",__func__);
	else
		als_data.als_phone_type=(uint8_t)als_phone_type;

	if(of_property_read_u32(dn, "als_phone_version", &als_phone_version))
		hwlog_err("%s:read als_phone_version fail\n",__func__);
	else
		als_data.als_phone_version=(uint8_t)als_phone_version;

	if (of_property_read_u32(dn, "atime", &temp))
		hwlog_err("%s:read als atime fail\n",__func__);
	else
		als_data.atime=(uint8_t)temp;

	if (of_property_read_u32(dn, "again", &temp))
		hwlog_err("%s:read als again fail\n",__func__);
	else
		als_data.again=(uint8_t)temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read als file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read als sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t)temp;
	if(rohm_rgb_flag == 1){
		if(phone_color != BLACK && phone_color != WHITE && phone_color != GOLD && phone_color != GRAY && phone_color != BROWN){
			//use the defoult als para adjust to the tp black color
			memcpy(als_data.als_extend_data, als_para_diff_tp_color_table[0].bh745_para, sizeof(als_para_diff_tp_color_table[0].bh745_para));
		}
		else{
			for(i=0;i<ARRAY_SIZE(als_para_diff_tp_color_table);i++){
				if((als_para_diff_tp_color_table[i].phone_type== als_data.als_phone_type) && (als_para_diff_tp_color_table[i].phone_version==als_data.als_phone_version)
					&&  (als_para_diff_tp_color_table[i].tp_lcd_manufacture== tplcd_manufacture) && (als_para_diff_tp_color_table[i].tp_color== phone_color)){
					break;
				}
			}

			memcpy(als_data.als_extend_data, als_para_diff_tp_color_table[i].bh745_para, sizeof(als_para_diff_tp_color_table[i].bh745_para));
			hwlog_err("i=%d ,bh1745 phone_color=0x%x  tplcd_manufacture=%d, phone_type=%d,phone_version=%d\n",i,phone_color,tplcd_manufacture,als_data.als_phone_type,als_data.als_phone_version);
		}
	}
	else if(avago_rgb_flag == 1)
	{
		if(phone_color != BLACK && phone_color != WHITE && phone_color != GOLD && phone_color !=GRAY && phone_color != BROWN)
		{
			//use the defoult als para adjust to the tp black color
			memcpy(als_data.als_extend_data, apds_als_para_diff_tp_color_table[0].apds251_para,
			sizeof(apds_als_para_diff_tp_color_table[0].apds251_para)>SENSOR_PLATFORM_EXTEND_DATA_SIZE?SENSOR_PLATFORM_EXTEND_DATA_SIZE:sizeof(apds_als_para_diff_tp_color_table[0].apds251_para));
		}
		else
		{
			for(i=0;i<ARRAY_SIZE(apds_als_para_diff_tp_color_table);i++){
				if((apds_als_para_diff_tp_color_table[i].phone_type== als_data.als_phone_type) && (apds_als_para_diff_tp_color_table[i].phone_version==als_data.als_phone_version)
                && (apds_als_para_diff_tp_color_table[i].tp_color== phone_color)){
					break;
				}
			}
			memcpy(als_data.als_extend_data, apds_als_para_diff_tp_color_table[i].apds251_para,
				sizeof(apds_als_para_diff_tp_color_table[i].apds251_para)>SENSOR_PLATFORM_EXTEND_DATA_SIZE?SENSOR_PLATFORM_EXTEND_DATA_SIZE:sizeof(apds_als_para_diff_tp_color_table[i].apds251_para));
			hwlog_err("i=%d apds9251 phone_color=0x%x phone_type=%d,phone_version=%d\n",i,phone_color,als_data.als_phone_type,als_data.als_phone_version);
		}
	}
	else
	{
		ret = fill_extend_data_in_dts(dn, "als_extend_data", als_data.als_extend_data, 12, EXTEND_DATA_TYPE_IN_DTS_HALF_WORD);
		if (ret){
			hwlog_err("als_extend_data:fill_extend_data_in_dts failed!\n");
		}
	}
}

static void read_ps_data_from_dts(struct device_node *dn)
{
	int temp=0;

	read_chip_info(dn, PS);
    if(!strncmp(sensor_chip_info[PS], "huawei,txc-pa224", sizeof("huawei,txc-pa224"))){
        txc_ps_flag = 1;
        hwlog_err("%s:txc_ps i2c_address suc,%d \n",__func__,temp);
    }

	temp = of_get_named_gpio(dn, "gpio_int1", 0);
	if(temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		ps_data.gpio_int1 = (uint8_t)temp;

	if (of_property_read_u32(dn, "min_proximity_value", &temp))
		hwlog_err("%s:read mag min_proximity_value fail\n",__func__);
	else
		ps_data.min_proximity_value=temp;

	if (of_property_read_u32(dn, "pwindows_value", &temp))
		hwlog_err("%s:read pwindows_value fail\n",__func__);
	else
		ps_data.pwindows_value=temp;

	if (of_property_read_u32(dn, "pwave_value", &temp))
		hwlog_err("%s:read pwave_value fail\n",__func__);
	else
		ps_data.pwave_value=temp;

	if (of_property_read_u32(dn, "threshold_value", &temp))
		hwlog_err("%s:read threshold_value fail\n",__func__);
	else
		ps_data.threshold_value=temp;

	if (of_property_read_u32(dn, "rdata_under_sun", &temp))
		hwlog_err("%s:read rdata_under_sun fail\n",__func__);
	else
		ps_data.rdata_under_sun=temp;

	if (of_property_read_u32(dn, "ps_pulse_count", &temp))
		hwlog_err("%s:read ps_pulse_count fail\n",__func__);
	else
		ps_data.ps_pulse_count=(uint8_t)temp;

	if (of_property_read_u32(dn, "persistent", &temp))
		hwlog_err("%s:read persistent fail\n",__func__);
	else
		ps_data.persistent=(uint8_t)temp;

	if (of_property_read_u32(dn, "ptime", &temp))
		hwlog_err("%s:read ptime fail\n",__func__);
	else
		ps_data.ptime=(uint8_t)temp;

	if (of_property_read_u32(dn, "p_on", &temp))
		hwlog_err("%s:read p_on fail\n",__func__);
	else
		ps_data.p_on=(uint8_t)temp;

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read poll_interval fail\n",__func__);
	else
		ps_data.poll_interval=(uint16_t)temp;

	if (of_property_read_u32(dn, "init_time", &temp))
		hwlog_err("%s:read init_time fail\n",__func__);
	else
		ps_data.init_time=(uint16_t)temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read ps file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t)temp;
}

static void read_airpress_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, AIRPRESS);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read poll_interval fail\n",__func__);
	else
		airpress_data.poll_interval=(uint16_t)temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read airpress file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t)temp;
}

static void read_handpress_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, HANDPRESS);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read poll_interval fail\n",__func__);
	else
		handpress_data.poll_interval=(uint16_t)temp;
	hwlog_info("get handpress dev from dts.sensor name=%d\n", handpress_data.poll_interval);

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read handpress file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;
	hwlog_info("get handpress dev from dyn_req->file_count=%d\n", dyn_req->file_count);

	if (of_property_read_u32(dn, "file_id_fw", &temp))
		hwlog_err("%s:read handpress file_id_fw fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;
	hwlog_info("get handpress dev from dyn_req->file_count=%d\n", dyn_req->file_count);

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t)temp;
	hwlog_info("get handpress dev from temp=%d; ++sensorlist[0]:%d\n", temp, sensorlist[0]-1);
}

static void read_capprox_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, CAP_PROX);

	temp = of_get_named_gpio(dn, "gpio_int", 0);
	if(temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		cap_prox_data.gpio_int = (uint8_t)temp;

	if (of_property_read_u32_array(dn, "init_reg_val", cap_prox_data.init_reg_val, 17))
		hwlog_err("%s:read init_reg_val fail\n",__func__);
	hwlog_info("cap_prox_data.poll_interval: %d\n", cap_prox_data.poll_interval);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read poll_interval fail\n",__func__);
	else
		cap_prox_data.poll_interval = (uint16_t)temp;
	hwlog_info("cap_prox_data.poll_interval: %d\n", cap_prox_data.poll_interval);

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read cap_prox file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read cap_prox sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t)temp;}

static int device_detect(struct device_node *dn, int *flag, enum sensor_name sname, char *sbuf)
{
	char device_name[30];
	const char *s1 = " detect fail!";
	const char *s2 = " detect succ!";
	int ret = 0;

	switch(sname) {
		case ACC:
			strcpy(device_name, "acc");
			break;
		case MAG:
			strcpy(device_name, "mag");
			break;
		case GYRO:
			strcpy(device_name, "gyro");
			break;
		case ALS:
			strcpy(device_name, "als");
			break;
		case PS:
			strcpy(device_name, "ps");
			break;
		case AIRPRESS:
			strcpy(device_name, "airpress");
			break;
		case HANDPRESS:
			strcpy(device_name, "handpress");
			break;
		case CAP_PROX:
			strcpy(device_name, "cap_prox");
			break;
		default:
			hwlog_err("%s incorrect sensor name!\n", __func__);
			return -1;
	}

	if(*flag == DET_SUCC)
		return -1;

	if (HANDPRESS == sname)
		ret = handpress_sensor_detect(dn, &handpress_data);
	else
		ret = detect_i2c_device(dn, device_name);

	if (ret) {
		*flag = DET_FAIL;
		strcat(device_name, s1);
		strcpy(sbuf, device_name);
		return -1;
	}

	*flag = DET_SUCC;
	strcat(device_name, s2);
	strcpy(sbuf, device_name);

	return 0;
}

static int get_adapt_id_and_send(void)
{
	int ret = 0, i=0;

	hwlog_info("get file id number = %d\n", dyn_req->file_count);

	ret = get_adapt_sensor_list_id();
	if (ret < 0) {
		hwlog_err("get_adapt_sensor_list_id() failed!\n");
	}

	sensorlist[0] = check_file_list(sensorlist[0], &sensorlist[1]);
	if (sensorlist[0] > 0) {
		hwlog_info("sensorhub after check, get sensor list id number = %d, list id: ", sensorlist[0]);
		for (i = 0; i < sensorlist[0]; i++) {
			hwlog_info("--%d", sensorlist[i+1]);
		}
		hwlog_info("\n");
	} else {
		hwlog_err("%s list num = 0, not send file_id to muc\n", __func__);
		return -EINVAL;
	}

	dyn_req->file_count = check_file_list(dyn_req->file_count, dyn_req->file_list);
	if (dyn_req->file_count)	{
		hwlog_info("sensorhub after check, get dynload file id number = %d, fild id", dyn_req->file_count);
		for (i = 0; i < dyn_req->file_count; i++) {
			hwlog_info("--%d", dyn_req->file_list[i]);
		}
		hwlog_info("\n");
		return send_fileid_to_mcu();
	} else {
		hwlog_err("%s file_count = 0, not send file_id to mcu\n", __func__);
		return -EINVAL;
	}
}

static int init_sensors_cfg_data_from_dts(void)
{
	int ret = 0;
	char *sensor_ty = NULL;
	struct device_node *dn = NULL;
	int acc_flag=DET_INIT, mag_flag=DET_INIT, gyro_flag=DET_INIT;
	int airpress_flag = DET_INIT, als_flag=DET_INIT, ps_flag=DET_INIT, hand_flag=DET_INIT,cap_prox_flag=DET_INIT;
	int mag_i2c_bus_id = 0;
	char buf[SENSOR_MAX][50] = {{0,},};
	char detect_result[MAX_STR_SIZE] = {0};

	sensor_info_isensor_version = check_sensorhub_isensor_version();
	for_each_node_with_property(dn, "sensor_type")
	{
		ret = of_property_read_string(dn, "sensor_type", (const char **)&sensor_ty);
		if (ret) {
			hwlog_err("get sensor type fail ret=%d\n",ret);
			continue;
		}

		if(!strncmp(sensor_ty, "acc", sizeof("acc"))) {
			if (device_detect(dn, &acc_flag, ACC, buf[ACC]))
				continue;

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			/* detect current device successful, set the flag as present */
			set_hw_dev_flag(DEV_I2C_G_SENSOR);
#endif
			read_acc_data_from_dts(dn);
		}else if(!strncmp(sensor_ty, "mag", sizeof("mag"))) {
			if (of_property_read_u32(dn, "bus_number", &mag_i2c_bus_id))
				hwlog_err("%s:read mag mag_i2c_bus_id fail\n",__func__);

			if (device_detect(dn, &mag_flag, MAG, buf[MAG]))
				continue;

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			/* detect current device successful, set the flag as present */
			set_hw_dev_flag(DEV_I2C_COMPASS);
#endif
			read_mag_data_from_dts(dn);

			ret = fill_extend_data_in_dts(dn, str_soft_para, mag_data.pdc_data, PDC_SIZE, EXTEND_DATA_TYPE_IN_DTS_BYTE);
			if (ret) {
				hwlog_err("%s:fill_extend_data_in_dts failed!\n", str_soft_para);
			}
		}else if(!strncmp(sensor_ty, "gyro", sizeof("gyro"))) {
			if (device_detect(dn, &gyro_flag, GYRO, buf[GYRO]))
				continue;

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			/* detect current device successful, set the flag as present */
			set_hw_dev_flag(DEV_I2C_GYROSCOPE);
#endif
			read_gyro_data_from_dts(dn);
		} else if(!strncmp(sensor_ty, "als", sizeof("als"))) {
			if (device_detect(dn, &als_flag, ALS, buf[ALS]))
				continue;

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_L_SENSOR);
#endif
			read_als_data_from_dts(dn);
		} else if(!strncmp(sensor_ty, "ps", sizeof("ps"))) {
			if (device_detect(dn, &ps_flag, PS, buf[PS]))
				continue;

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_L_SENSOR);
#endif
			read_ps_data_from_dts(dn);
		} else if(!strncmp(sensor_ty, "airpress", sizeof("airpress"))) {
			if (device_detect(dn, &airpress_flag, AIRPRESS, buf[AIRPRESS]))
				continue;

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_AIRPRESS);
#endif
			read_airpress_data_from_dts(dn);
		} else if(!strncmp(sensor_ty, "handpress", sizeof("handpress"))) {
			if (device_detect(dn, &hand_flag, HANDPRESS, buf[HANDPRESS]))
				continue;

			iom3_timeout = 20000;

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_HANDPRESS);
#endif
			read_handpress_data_from_dts(dn);
		} else if(!strncmp(sensor_ty, "cap_prox", sizeof("cap_prox"))) {
			if (device_detect(dn, &cap_prox_flag, CAP_PROX, buf[CAP_PROX]))
				continue;

			read_capprox_data_from_dts(dn);
		}
	}

	if (IS_FAIL(acc_flag, mag_flag, gyro_flag, als_flag, ps_flag, airpress_flag, hand_flag, cap_prox_flag)) {
		snprintf(detect_result,MAX_STR_SIZE,"%s,%s,%s,%s,%s,%s,%s,%s\n",buf[ACC],buf[MAG],
			buf[GYRO],buf[ALS],buf[PS],buf[AIRPRESS],buf[HANDPRESS],buf[CAP_PROX]);
		hwlog_err("detect_result: %s\n",detect_result);
		dmd_log_report(DSM_SHB_ERR_DYNLOAD, __func__, detect_result);
	}

	if (get_adapt_id_and_send())
		return -EINVAL;
	else
		return 0;

}

/*******************************************************************************************
Function:	sensor_set_cfg_data
Description: 其他配置信息，例如是否需要根据电池电流大小校准指南针
Data Accessed:  无
Data Updated:   无
Input:        无
Output:         无
Return:         成功或者失败信息: 0->成功, -1->失败
*******************************************************************************************/
static int sensor_set_current_info(void)
{
	int ret = 0;
	u8 need_current = 0;
	write_info_t	pkg_ap;

	memset(&pkg_ap, 0, sizeof(pkg_ap));

	need_current = check_if_need_current();
	if(need_current == 0){
		return 0;
	}

	pkg_ap.tag=TAG_CURRENT;
	pkg_ap.cmd=CMD_CURRENT_CFG_REQ;
	pkg_ap.wr_buf=&need_current;
	pkg_ap.wr_len=sizeof(need_current);

	if (g_iom3_state == IOM3_ST_RECOVERY)
		ret = write_customize_cmd_noresp(TAG_CURRENT, CMD_CURRENT_CFG_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
	else
		ret = write_customize_cmd(&pkg_ap,  NULL);

	if (ret)
	{
		hwlog_err("send current cfg data to mcu fail,ret=%d\n", ret);
		return -1;
	}
	else
	{
		hwlog_info( "set current cfg data to mcu success\n");
	}

	return 0;
}

/*******************************************************************************************
Function:	sensor_set_cfg_data
Description: 将配置参数发至mcu 侧
Data Accessed:  无
Data Updated:   无
Input:        无
Output:         无
Return:         成功或者失败信息: 0->成功, -1->失败
*******************************************************************************************/

int sensor_set_cfg_data(void)
{
	int ret = 0;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));

	ret = sensor_set_current_info();
	if (ret)
	{
		hwlog_err("sensor_set_current_info fail, ret = %d\n", ret);
	}

	//g-sensor
	if(strlen(sensor_chip_info[ACC]) != 0)
	{
		pkg_ap.tag=TAG_ACCEL;
		pkg_ap.cmd=CMD_ACCEL_PARAMET_REQ;
		pkg_ap.wr_buf=&gsensor_data;
		pkg_ap.wr_len=sizeof(gsensor_data);

		if (g_iom3_state == IOM3_ST_RECOVERY)
			ret = write_customize_cmd_noresp(TAG_ACCEL, CMD_ACCEL_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
		else
			ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);

		if(ret)
		{
			hwlog_err("send gsensor cfg data to mcu fail,ret=%d\n", ret);
		}
		else
		{
			if(pkg_mcu.errno!=0)
			{
				hwlog_err("set gsensor cfg fail\n");
				dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set gsensor cfg fail\n");
			}
			else
			{
				hwlog_info( "set gsensor cfg data to mcu success\n");
				if (g_iom3_state != IOM3_ST_RECOVERY) {
			#ifdef CONFIG_HUAWEI_HW_DEV_DCT
					/* detect current device successful, set the flag as present */
					set_hw_dev_flag(DEV_I2C_G_SENSOR);
			#endif
				}
			}
		}
	}

	//gyro
	if(strlen(sensor_chip_info[GYRO]) != 0)
	{
		pkg_ap.tag=TAG_GYRO;
		pkg_ap.cmd=CMD_GYRO_PARAMET_REQ;
		pkg_ap.wr_buf=&gyro_data;
		pkg_ap.wr_len=sizeof(gyro_data);

		if (g_iom3_state == IOM3_ST_RECOVERY)
			ret = write_customize_cmd_noresp(TAG_GYRO, CMD_GYRO_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
		else
			ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);

		if(ret)
		{
			hwlog_err("send gyro cfg data to mcu fail,ret=%d\n", ret);
		}
		else
		{
			if(pkg_mcu.errno!=0)
			{
				hwlog_err("set gyro cfg fail\n");
				dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set gyro cfg fail\n");
			}
			else
			{
				hwlog_info( "set gyro cfg data to mcu success\n");
				if (g_iom3_state != IOM3_ST_RECOVERY) {
			#ifdef CONFIG_HUAWEI_HW_DEV_DCT
					/* detect current device successful, set the flag as present */
					set_hw_dev_flag(DEV_I2C_GYROSCOPE);
			#endif
				}
			}
		}
	}

	//mag
	if(strlen(sensor_chip_info[MAG]) != 0)
	{
		pkg_ap.tag=TAG_MAG;
		pkg_ap.cmd=CMD_MAG_PARAMET_REQ;
		pkg_ap.wr_buf=&mag_data;
		pkg_ap.wr_len=sizeof(mag_data);

		if (g_iom3_state == IOM3_ST_RECOVERY)
			ret = write_customize_cmd_noresp(TAG_MAG, CMD_MAG_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
		else
			ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);

		if(ret)
		{
			hwlog_err("send magg data to mcu fail,ret=%d\n", ret);
		}
		else
		{
			if(pkg_mcu.errno!=0)
			{
				hwlog_err("set mag cfg fail\n");
				dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set mag cfg fail\n");
			}
			else
			{
				hwlog_info( "set mag cfg data to mcu success\n");
				if (g_iom3_state != IOM3_ST_RECOVERY) {
			#ifdef CONFIG_HUAWEI_HW_DEV_DCT
					/* detect current device successful, set the flag as present */
					set_hw_dev_flag(DEV_I2C_COMPASS);
			#endif
				}
			}
		}

		if (g_iom3_state != IOM3_ST_RECOVERY) {
			register_mcu_event_notifier(TAG_MAG, CMD_MAG_SEND_CALIBRATE_TO_AP_REQ, mag_calibrate_data_from_mcu);
		}
	}

	//als
	if(strlen(sensor_chip_info[ALS]) != 0)
	{
		pkg_ap.tag=TAG_ALS;
		pkg_ap.cmd=CMD_ALS_PARAMET_REQ;
		pkg_ap.wr_buf=&als_data;
		pkg_ap.wr_len=sizeof(als_data);

		if (g_iom3_state == IOM3_ST_RECOVERY)
			ret = write_customize_cmd_noresp(TAG_ALS, CMD_ALS_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
		else
			ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);

		if(ret)
		{
			hwlog_err("send als cfg data to mcu fail,ret=%d\n", ret);
		}
		else
		{
			if(pkg_mcu.errno!=0)
			{
				hwlog_err("set als cfg fail\n");
				dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set als cfg fail\n");
			}
			else
			{
				hwlog_info( "set als cfg data to mcu success\n");
			}
		}
	}

	//ps
	if(strlen(sensor_chip_info[PS]) != 0)
	{
		pkg_ap.tag=TAG_PS;
		pkg_ap.cmd=CMD_PS_PARAMET_REQ;
		pkg_ap.wr_buf=&ps_data;
		pkg_ap.wr_len=sizeof(ps_data);

		if (g_iom3_state == IOM3_ST_RECOVERY)
			ret = write_customize_cmd_noresp(TAG_PS, CMD_PS_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
		else
			ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);

		if(ret)
		{
			hwlog_err("send ps cfg data to mcu fail,ret=%d\n", ret);
		}
		else
		{
			if(pkg_mcu.errno!=0)
			{
				hwlog_err("set ps cfg fail\n");
				dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set ps cfg fail\n");
			}
			else
			{
				hwlog_info( "set ps cfg data to mcu success\n");
				if (g_iom3_state != IOM3_ST_RECOVERY) {
			#ifdef CONFIG_HUAWEI_HW_DEV_DCT
					/* detect current device successful, set the flag as present */
					set_hw_dev_flag(DEV_I2C_L_SENSOR);
			#endif
				}
			}
		}
	}

	//airpress
	if(strlen(sensor_chip_info[AIRPRESS]) != 0)
	{
		pkg_ap.tag=TAG_PRESSURE;
		pkg_ap.cmd=CMD_AIRPRESS_PARAMET_REQ;
		pkg_ap.wr_buf=&airpress_data;
		pkg_ap.wr_len=sizeof(airpress_data);

		if (g_iom3_state == IOM3_ST_RECOVERY)
			ret = write_customize_cmd_noresp(TAG_PRESSURE, CMD_AIRPRESS_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
		else
			ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			hwlog_err("send airpress cfg data to mcu fail,ret=%d\n", ret);
		}
		else
		{
			if(pkg_mcu.errno!=0)
			{
				hwlog_err("set airpress cfg fail\n");
				dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set airpress cfg fail\n");
			}
			else
			{
				hwlog_info( "set airpress cfg data to mcu success\n");
			}
		}
	}
	//handpress
	if(strlen(sensor_chip_info[HANDPRESS]) != 0)
	{
		pkg_ap.tag=TAG_HANDPRESS;
		pkg_ap.cmd=CMD_HANDPRESS_PARAMET_REQ;
		pkg_ap.wr_buf=&handpress_data;
		pkg_ap.wr_len=sizeof(handpress_data);

		if (g_iom3_state == IOM3_ST_RECOVERY)
			ret = write_customize_cmd_noresp(TAG_HANDPRESS, CMD_HANDPRESS_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
		else
			ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);

		if(ret)
		{
			hwlog_err("send handpress cfg data to mcu fail,ret=%d\n", ret);
		}
		else
		{
			if(pkg_mcu.errno!=0)
			{
				hwlog_err("set handpress cfg fail:%d\n", pkg_mcu.errno);
				dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set airpress cfg fail\n");
			}
			else
			{
				hwlog_info( "set handpress cfg data to mcu success\n");
			}
		}
	}
	//CAP_PROX
	if(strlen(sensor_chip_info[CAP_PROX]) != 0)
	{
		pkg_ap.tag=TAG_CAP_PROX;
		pkg_ap.cmd=CMD_CAP_PROX_PARAMET_REQ;
		pkg_ap.wr_buf=&cap_prox_data;
		pkg_ap.wr_len=sizeof(cap_prox_data);

		if (g_iom3_state == IOM3_ST_RECOVERY)
			ret = write_customize_cmd_noresp(TAG_CAP_PROX, CMD_CAP_PROX_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
		else
			ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);

		if(ret)
		{
			hwlog_err("send cap_prox cfg data to mcu fail,ret=%d\n", ret);
		}
		else
		{
			if(pkg_mcu.errno!=0)
			{
				hwlog_err("set cap_prox cfg fail\n");
				dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set cap_prox cfg fail\n");
			}
			else
			{
				hwlog_info( "set cap_prox cfg data to mcu success\n");
				if (g_iom3_state != IOM3_ST_RECOVERY) {
			#ifdef CONFIG_HUAWEI_HW_DEV_DCT
					/* detect current device successful, set the flag as present */
					set_hw_dev_flag(DEV_I2C_L_SENSOR);
			#endif
				}
			}
		}
	}
	return ret;
}

static ssize_t show_sensor_list_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int i;
	hwlog_info( "sensor list: ");
	for(i = 0; i <= sensorlist[0]; i++)
		hwlog_info( " %d  ", sensorlist[i]);
	hwlog_info("\n");
	memcpy(buf, sensorlist, ((sensorlist[0]+1)*sizeof(uint16_t)));
	return (sensorlist[0] + 1) * sizeof(uint16_t);
}
static DEVICE_ATTR(sensor_list_info, S_IRUGO,
				   show_sensor_list_info, NULL);

#define SENSOR_SHOE_INFO(TAG)\
static ssize_t sensor_show_##TAG##_info(struct device *dev,\
				struct device_attribute *attr, char *buf)\
{\
	return snprintf(buf, MAX_STR_SIZE, "%s\n", sensor_chip_info[TAG]);\
}

SENSOR_SHOE_INFO(PS);
static DEVICE_ATTR(ps_info, S_IRUGO, sensor_show_PS_info, NULL);

SENSOR_SHOE_INFO(ALS);
static DEVICE_ATTR(als_info, S_IRUGO, sensor_show_ALS_info, NULL);

SENSOR_SHOE_INFO(GYRO);
static DEVICE_ATTR(gyro_info, S_IRUGO, sensor_show_GYRO_info, NULL);

SENSOR_SHOE_INFO(MAG);
static DEVICE_ATTR(mag_info, S_IRUGO, sensor_show_MAG_info, NULL);

SENSOR_SHOE_INFO(ACC);
static DEVICE_ATTR(acc_info, S_IRUGO, sensor_show_ACC_info, NULL);

SENSOR_SHOE_INFO(AIRPRESS);
static DEVICE_ATTR(airpress_info, S_IRUGO, sensor_show_AIRPRESS_info, NULL);

//SENSOR_SHOE_INFO(HANDPRESS);
//static DEVICE_ATTR(handpress_info, S_IRUGO, sensor_show_HANDPRESS_info, NULL);

//SENSOR_SHOE_INFO(CAP_PROX);
//static DEVICE_ATTR(cap_prox_info, S_IRUGO, sensor_show_CAP_PROX_info, NULL);

unsigned int sensor_read_number[TAG_END] = {0,0,0,0,0};

#define SENSOR_SHOW_VALUE(TAG) \
static ssize_t sensor_show_##TAG##_read_data(struct device *dev, \
				struct device_attribute *attr, char *buf) \
{\
	hwlog_info("[sensorhub_test], %s return %d\n", __func__, sensor_read_number[TAG]);\
	return snprintf(buf, MAX_STR_SIZE, "%d\n", sensor_read_number[TAG]);\
}

SENSOR_SHOW_VALUE(TAG_ACCEL);
static DEVICE_ATTR(acc_read_data, 0664, sensor_show_TAG_ACCEL_read_data, NULL);

SENSOR_SHOW_VALUE(TAG_MAG);
static DEVICE_ATTR(mag_read_data, 0664, sensor_show_TAG_MAG_read_data, NULL);

SENSOR_SHOW_VALUE(TAG_GYRO);
static DEVICE_ATTR(gyro_read_data, 0664, sensor_show_TAG_GYRO_read_data, NULL);

SENSOR_SHOW_VALUE(TAG_ALS);
static DEVICE_ATTR(als_read_data, 0664, sensor_show_TAG_ALS_read_data, NULL);

SENSOR_SHOW_VALUE(TAG_PS);
static DEVICE_ATTR(ps_read_data, 0664, sensor_show_TAG_PS_read_data, NULL);

SENSOR_SHOW_VALUE(TAG_PRESSURE);
static DEVICE_ATTR(airpress_read_data, 0664, sensor_show_TAG_PRESSURE_read_data, NULL);

//SENSOR_SHOW_VALUE(TAG_HANDPRESS);
//static DEVICE_ATTR(handpress_read_data, 0664, sensor_show_TAG_HANDPRESS_read_data, NULL);

//SENSOR_SHOW_VALUE(TAG_CAP_PROX);
//static DEVICE_ATTR(cap_prox_read_data, 0664, sensor_show_TAG_CAP_PROX_read_data, NULL);

#define SHOW_SELFTEST_RESULT(TAG) \
static ssize_t show_##TAG##_selfTest_result(struct device *dev,\
				struct device_attribute *attr, char *buf)\
{\
	return snprintf(buf, MAX_STR_SIZE, "%s\n", sensor_status.TAG##_selfTest_result);\
}\

SHOW_SELFTEST_RESULT(gyro) ;
SHOW_SELFTEST_RESULT(mag) ;
SHOW_SELFTEST_RESULT(accel) ;

#define SET_SENSOR_SELFTEST(TAGUP, TAGLOW)\
static ssize_t attr_set_##TAGLOW##_selftest(struct device *dev, struct device_attribute *attr,\
				const char *buf, size_t size)\
{\
	unsigned long val = 0;\
	int err = -1;\
	write_info_t	pkg_ap;\
	read_info_t	pkg_mcu;\
	memset(&pkg_ap, 0, sizeof(pkg_ap));\
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));\
	if (strict_strtoul(buf, 10, &val))\
		return -EINVAL;\
	if(1==val)\
	{\
		pkg_ap.tag=TAG_##TAGUP;\
		pkg_ap.cmd=CMD_##TAGUP##_SELFTEST_REQ;\
		pkg_ap.wr_buf=NULL;\
		pkg_ap.wr_len=0;\
		err=write_customize_cmd(&pkg_ap,  &pkg_mcu);\
		if(err){\
			hwlog_err("send %s selftest cmd to mcu fail,ret=%d\n", #TAGUP, err);\
			memcpy(sensor_status.TAGLOW##_selfTest_result, "0", 2);\
			return size;\
		}\
		if(pkg_mcu.errno!=0){\
			hwlog_err("%s selftest fail\n", #TAGUP);\
			memcpy(sensor_status.TAGLOW##_selfTest_result, "0", 2);\
			dmd_log_report(DSM_SHB_ERR_IOM3_OTHER, __func__, "-->selftest fail\n");\
		}else{\
			hwlog_info("%s selftest  success, data len=%d\n", #TAGUP, pkg_mcu.data_length);\
			memcpy(sensor_status.TAGLOW##_selfTest_result, "1", 2);\
		}\
	}\
	return size;\
}
SET_SENSOR_SELFTEST(GYRO, gyro);
static DEVICE_ATTR(gyro_selfTest, 0664, show_gyro_selfTest_result, attr_set_gyro_selftest);

SET_SENSOR_SELFTEST(MAG, mag);
static DEVICE_ATTR(mag_selfTest, 0664, show_mag_selfTest_result, attr_set_mag_selftest);

SET_SENSOR_SELFTEST(ACCEL, accel);
static DEVICE_ATTR(acc_selfTest, 0664, show_accel_selfTest_result, attr_set_accel_selftest);

static ssize_t i2c_rw_pi(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	uint64_t val = 0;
	int ret=0;
	uint8_t bus_num = 0, i2c_address = 0, reg_add = 0, len = 0, rw = 0, buf_temp[DEBUG_DATA_LENGTH] = {0};

	if (strict_strtoull(buf, 16, &val))
		return -EINVAL;
	//##(bus_num)##(i2c_addr)##(reg_addr)##(len)
	bus_num = (val>>40)&0xff;
	i2c_address = (val>>32)&0xff;
	reg_add = (val>>24)&0xff;
	len = (val>>16)&0xff;
	if (len > DEBUG_DATA_LENGTH) {
		hwlog_err("len exceed %d\n", len);
		len = DEBUG_DATA_LENGTH;
	}
	rw = (val>>8)&0xff;
	buf_temp[0] = (uint8_t)(val&0xff);

	hwlog_info("In %s! bus_num = %d, i2c_address = %d, reg_add = %d, len = %d, rw = %d, buf_temp[0] = %d\n", __func__, bus_num, i2c_address, reg_add, len, rw, buf_temp[0]);
//static int mcu_i2c_rw(uint8_t bus_num, uint8_t i2c_add, uint8_t register_add, uint8_t rw, int len, uint8_t *buf)
	ret = mcu_i2c_rw(bus_num, i2c_address, reg_add, rw, len, buf_temp);
	if(ret < 0)
		hwlog_err("oper %d(1/32:r 0/31:w) i2c reg fail!\n", rw);
	if(rw) {
		hwlog_err("i2c reg %x value %x %x %x %x\n", reg_add, buf_temp[0], buf_temp[1], buf_temp[2], buf_temp[3]);
		memcpy(debug_read_data_buf, buf_temp, DEBUG_DATA_LENGTH);
	}
	return count;
}

static ssize_t i2c_rw_pi_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned int i = 0;
	unsigned int len = 0;
	char *p = buf;
	if (!buf) {
		return -1;
	}

	for(i = 0; i < DEBUG_DATA_LENGTH; i++) {
		snprintf(p, 5, "0x%x,", debug_read_data_buf[i]);
		if (debug_read_data_buf[i] > 0xf) {
			p += 5;
			len += 5;
		} else {
			p += 4;
			len += 4;
		}
	}

	p = buf;
	*(p + len - 1) = 0;

	p = NULL;
	return len;
}
static DEVICE_ATTR(i2c_rw, 0664, i2c_rw_pi_show, i2c_rw_pi);

static uint8_t i2c_rw16_data_buf[2] = {0};
static ssize_t i2c_rw16_pi(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	uint64_t val = 0;
	int ret=0;
	uint8_t bus_num = 0, i2c_address = 0, reg_add = 0, len = 0, rw = 0, buf_temp[2] = {0};

	if (strict_strtoull(buf, 16, &val))
		return -EINVAL;
	//##(bus_num)##(i2c_addr)##(reg_addr)##(len)
	bus_num = (val>>48)&0xff;
	i2c_address = (val>>40)&0xff;
	reg_add = (val>>32)&0xff;
	len = (val>>24)&0xff;
	if (len > 2) {
		hwlog_err("len exceed %d\n", len);
		len = 2;
	}
	rw = (val>>16)&0xff;
	buf_temp[0] = (uint8_t)(val>>8);
	buf_temp[1] = (uint8_t)(val&0xff);

	hwlog_info("In %s! bus_num=%d, i2c_address=%d, reg_add=%d, len=%d, rw=%d, buf_temp[0]=0x%02x, buf_temp[1]=0x%02x\n",
                __func__, bus_num, i2c_address, reg_add, len, rw, buf_temp[0], buf_temp[1]);
	ret = mcu_i2c_rw(bus_num, i2c_address, reg_add, rw, len, buf_temp);
	if(ret < 0)
		hwlog_err("oper %d(1:r 0:w) i2c reg fail!\n", rw);
	if(rw) {
		hwlog_err("i2c reg %x value %x %x\n", reg_add, buf_temp[0], buf_temp[1]);
		memcpy(i2c_rw16_data_buf, buf_temp, 2);
	}
	return count;
}

static ssize_t i2c_rw16_pi_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	char *p = buf;

	if (!buf) {
		return -1;
	}

	snprintf(p, 8, "0x%02x%02x\n", i2c_rw16_data_buf[0], i2c_rw16_data_buf[1]);
	*(p + 7) = 0;

	p = NULL;
	return 8;
}
static DEVICE_ATTR(i2c_rw16, 0664, i2c_rw16_pi_show, i2c_rw16_pi);

static ssize_t attr_acc_calibrate_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int val = return_calibration;
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}

static int acc_calibrate_save(const void *buf, int length)
{
	const int32_t *poffset_data = (const int32_t *)buf;
	int ret=0;
	if(buf == NULL||length <= 0)
	{
		hwlog_err("%s invalid argument.", __func__);
		return_calibration=EXEC_FAIL;
		return -1;
	}
	hwlog_info( "%s:gsensor calibrate ok, %d  %d  %d \n", __func__, *poffset_data, *(poffset_data + 1), *(poffset_data + 2));
	ret = write_gsensor_offset_to_nv((char *)buf);
	if(ret)
	{
		hwlog_err("nv write fail.\n");
		return_calibration=NV_FAIL;
		return -1;
	}
	return_calibration=SUC;
	return 0;
}

static ssize_t attr_acc_calibrate_write(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val = 0;
    unsigned long delay;
	int ret = 0;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

    if (1 != val) return count;

    if (sensor_status.opened[TAG_ACCEL] == 0) //if acc is not opened, open first
    {
        acc_close_after_calibrate = true;
        hwlog_info("send acc open cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_ACCEL;
		pkg_ap.cmd=CMD_CMN_OPEN_REQ;
		pkg_ap.wr_buf=NULL;
		pkg_ap.wr_len=0;
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			return_calibration=COMMU_FAIL;
			hwlog_err("send acc open cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
    else{
        acc_close_after_calibrate = false;
    }
    //period must <= 100 ms
    if ((sensor_status.delay[TAG_ACCEL] == 0) || (sensor_status.delay[TAG_ACCEL] > 100))
    {
        delay = 100;
        hwlog_info("send acc setdelay cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_ACCEL;
		pkg_ap.cmd=CMD_CMN_INTERVAL_REQ;
		pkg_ap.wr_buf=&delay;
		pkg_ap.wr_len=sizeof(delay);
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			return_calibration=COMMU_FAIL;
			hwlog_err("send acc set delay cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
    //send calibrate command, need set delay first
	pkg_ap.tag=TAG_ACCEL;
	pkg_ap.cmd=CMD_ACCEL_SELFCALI_REQ;
	pkg_ap.wr_buf=NULL;
	pkg_ap.wr_len=0;
	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	if(ret)
	{
		return_calibration=COMMU_FAIL;
		hwlog_err("send acc calibrate cmd to mcu fail,ret=%d\n", ret);
		return count;
	}
	if(pkg_mcu.errno!=0)
	{
		hwlog_err("acc calibrate fail, %d\n", pkg_mcu.errno);
		return_calibration=EXEC_FAIL;
	}
	else
	{
		hwlog_info("acc calibrate  success, data len=%d\n", pkg_mcu.data_length);
		acc_calibrate_save(pkg_mcu.data, pkg_mcu.data_length);
	}

    if(acc_close_after_calibrate == true) {
        acc_close_after_calibrate = false;
        hwlog_info("send acc close cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_ACCEL;
		pkg_ap.cmd=CMD_CMN_CLOSE_REQ;
		pkg_ap.wr_buf=NULL;
		pkg_ap.wr_len=0;
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			return_calibration=COMMU_FAIL;
			hwlog_err("send acc close cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
	return count;
}

static DEVICE_ATTR(acc_calibrate, 0664, attr_acc_calibrate_show, attr_acc_calibrate_write);

static ssize_t attr_gyro_calibrate_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int val = gyro_calibration_res;
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}

static int gyro_calibrate_save(const void *buf, int length)
{
	const int32_t *poffset_data = (const int32_t *)buf;
	int ret=0;
	if(buf == NULL||length <= 0)
	{
		hwlog_err("%s invalid argument.", __func__);
		gyro_calibration_res=EXEC_FAIL;
		return -1;
	}
	hwlog_info( "%s:gyro_sensor calibrate ok, %d  %d  %d \n", __func__, *poffset_data, *(poffset_data + 1), *(poffset_data + 2));
	ret = write_gyro_sensor_offset_to_nv((char *)buf);
	if(ret)
	{
		hwlog_err("nv write fail.\n");
		gyro_calibration_res=NV_FAIL;
		return -1;
	}
	gyro_calibration_res=SUC;
	return 0;
}

static ssize_t attr_gyro_calibrate_write(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
    unsigned long val = 0;
    unsigned long delay;
    int ret = 0;
    write_info_t	pkg_ap;
    read_info_t	pkg_mcu;

    memset(&pkg_ap, 0, sizeof(pkg_ap));
    memset(&pkg_mcu, 0, sizeof(pkg_mcu));
    if (strict_strtoul(buf, 10, &val))
        return -EINVAL;

    if (1 != val)
        return count;

    if (sensor_status.opened[TAG_GYRO] == 0) //if gyro is not opened, open first
    {
        gyro_close_after_calibrate = true;
        hwlog_info("send gyro open cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_GYRO;
		pkg_ap.cmd=CMD_CMN_OPEN_REQ;
		pkg_ap.wr_buf=NULL;
		pkg_ap.wr_len=0;
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			gyro_calibration_res=COMMU_FAIL;
			hwlog_err("send gyro open cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
    else{
        gyro_close_after_calibrate = false;
    }

    if ((sensor_status.delay[TAG_GYRO] == 0) || (sensor_status.delay[TAG_GYRO] > 20))
    {
        delay = 20;
        hwlog_info("send gyro setdelay cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_GYRO;
		pkg_ap.cmd=CMD_CMN_INTERVAL_REQ;
		pkg_ap.wr_buf=&delay;
		pkg_ap.wr_len=sizeof(delay);
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			gyro_calibration_res=COMMU_FAIL;
			hwlog_err("send gyro set delay cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
    //send calibrate command, need set delay first
	pkg_ap.tag=TAG_GYRO;
	pkg_ap.cmd=CMD_GYRO_SELFCALI_REQ;
	pkg_ap.wr_buf=NULL;
	pkg_ap.wr_len=0;
	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	if(ret)
	{
		gyro_calibration_res=COMMU_FAIL;
		hwlog_err("send gyro calibrate cmd to mcu fail,ret=%d\n", ret);
		return count;
	}
	if(pkg_mcu.errno!=0)
	{
		hwlog_err("gyro calibrate fail, %d\n", pkg_mcu.errno);
		gyro_calibration_res=EXEC_FAIL;
	}
	else
	{
		hwlog_info("gyro calibrate  success, data len=%d\n", pkg_mcu.data_length);
		gyro_calibrate_save(pkg_mcu.data, pkg_mcu.data_length);
	}

    if(gyro_close_after_calibrate == true) {
        gyro_close_after_calibrate = false;
        hwlog_info("send gyro close cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_GYRO;
		pkg_ap.cmd=CMD_CMN_CLOSE_REQ;
		pkg_ap.wr_buf=NULL;
		pkg_ap.wr_len=0;
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			gyro_calibration_res=COMMU_FAIL;
			hwlog_err("send gyro close cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
	return count;
}

static DEVICE_ATTR(gyro_calibrate, 0664, attr_gyro_calibrate_show, attr_gyro_calibrate_write);

static ssize_t attr_ps_calibrate_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int val = ps_calibration_res;
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}

static int ps_calibrate_save(const void *buf, int length)
{
	char temp_buf[4] = {0};
	int ret=0;
	if(buf == NULL||length <= 0)
	{
		hwlog_err("%s invalid argument.", __func__);
		ps_calibration_res=EXEC_FAIL;
		return -1;
	}
	memcpy(temp_buf, buf, length);
	hwlog_info( "%s:psensor calibrate ok, %d \n", __func__, temp_buf[0]);
	ret = write_ps_offset_to_nv(temp_buf);
	if(ret)
	{
		hwlog_err("nv write fail.\n");
		ps_calibration_res=NV_FAIL;
		return -1;
	}
	ps_calibration_res=SUC;
	return 0;
}

static ssize_t attr_ps_calibrate_write(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val = 0;
	int ret = 0;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;

	if(txc_ps_flag != 1){
		hwlog_info("ps sensor is not txc_ps_224,no need calibrate\n");
		return count;
	}

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;
	if(1==val)
	{
		pkg_ap.tag=TAG_PS;
		pkg_ap.cmd=CMD_PS_SELFCALI_REQ;
		pkg_ap.wr_buf=NULL;
		pkg_ap.wr_len=0;
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			ps_calibration_res=COMMU_FAIL;
			hwlog_err("send ps calibrate cmd to mcu fail,ret=%d\n", ret);
			return count;
		}
		if(pkg_mcu.errno!=0)
		{
			hwlog_err("ps calibrate fail, %d\n", pkg_mcu.errno);
			ps_calibration_res=EXEC_FAIL;
		}
		else
		{
			hwlog_info("ps calibrate  success, data len=%d\n", pkg_mcu.data_length);
			ps_calibrate_save(pkg_mcu.data, pkg_mcu.data_length);
		}
	}
	return count;
}

static DEVICE_ATTR(ps_calibrate, 0664, attr_ps_calibrate_show, attr_ps_calibrate_write);

static ssize_t attr_als_calibrate_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int val = als_calibration_res;
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}

static int als_calibrate_save(const void *buf, int length)
{
	const uint16_t *poffset_data = (const uint16_t *)buf;
	int ret=0;
	if(buf == NULL||length <= 0)
	{
		hwlog_err("%s invalid argument.", __func__);
		als_calibration_res=EXEC_FAIL;
		return -1;
	}
	hwlog_info( "%s:als calibrate ok, %d  %d  %d %d  %d  %d\n", __func__, *poffset_data, *(poffset_data + 1), *(poffset_data + 2),*(poffset_data + 3), *(poffset_data + 4), *(poffset_data + 5));
	ret = write_als_offset_to_nv((char *)buf);
	if(ret)
	{
		hwlog_err("nv write fail.\n");
		als_calibration_res=NV_FAIL;
		return -1;
	}
	als_calibration_res=SUC;
	return 0;
}

static ssize_t attr_als_calibrate_write(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val = 0;
	int ret = 0;
	unsigned long delay;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;

	if(rohm_rgb_flag != 1 && avago_rgb_flag != 1){
		hwlog_info("als sensor is not rohm_bh1745 or avago apds9251,no need calibrate\n");
		return count;
	}

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	if (1 != val) return count;

    if (sensor_status.opened[TAG_ALS] == 0) //if ALS is not opened, open first
    {
        als_close_after_calibrate = true;
        hwlog_info("send als open cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_ALS;
		pkg_ap.cmd=CMD_CMN_OPEN_REQ;
		pkg_ap.wr_buf=NULL;
		pkg_ap.wr_len=0;
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			als_calibration_res=COMMU_FAIL;
			hwlog_err("send ALS open cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
    else{
        als_close_after_calibrate = false;
    }
    //period must <= 100 ms
    if ((sensor_status.delay[TAG_ALS] == 0) || (sensor_status.delay[TAG_ALS] > 100))
    {
        delay = 100;
        hwlog_info("send als setdelay cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_ALS;
		pkg_ap.cmd=CMD_CMN_INTERVAL_REQ;
		pkg_ap.wr_buf=&delay;
		pkg_ap.wr_len=sizeof(delay);
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			als_calibration_res=COMMU_FAIL;
			hwlog_err("send ALS set delay cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
    //send calibrate command, need set delay first

		pkg_ap.tag=TAG_ALS;
		pkg_ap.cmd=CMD_ALS_SELFCALI_REQ;
		pkg_ap.wr_buf=NULL;
		pkg_ap.wr_len=0;
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			als_calibration_res=COMMU_FAIL;
			hwlog_err("send als calibrate cmd to mcu fail,ret=%d\n", ret);
			return count;
		}
		if(pkg_mcu.errno!=0)
		{
			hwlog_err("als calibrate fail, %d\n", pkg_mcu.errno);
			als_calibration_res=EXEC_FAIL;
		}
		else
		{
			hwlog_info("als calibrate  success, data len=%d\n", pkg_mcu.data_length);
			als_calibrate_save(pkg_mcu.data, pkg_mcu.data_length);
		}

    if(als_close_after_calibrate == true) {
        als_close_after_calibrate = false;
        hwlog_info("send als close cmd(during calibrate) to mcu.\n");
		pkg_ap.tag=TAG_ALS;
		pkg_ap.cmd=CMD_CMN_CLOSE_REQ;
		pkg_ap.wr_buf=NULL;
		pkg_ap.wr_len=0;
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		if(ret)
		{
			als_calibration_res=COMMU_FAIL;
			hwlog_err("send ALS close cmd(during calibrate) to mcu fail,ret=%d\n", ret);
			return count;
		}
    }
	return count;
}

static DEVICE_ATTR(als_calibrate, 0664, attr_als_calibrate_show, attr_als_calibrate_write);

static ssize_t attr_cap_prox_calibrate_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int ret=0;
	u32 *pcaldata = NULL;
	struct hisi_nve_info_user user_info;

	memset(&user_info, 0, sizeof(user_info));
	//read from nv
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = CAP_PROX_CALIDATA_NV_NUM;
	user_info.valid_size = CAP_PROX_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "Csensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0) {
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return snprintf(buf, PAGE_SIZE, "%d\n", return_cap_prox_calibration);
	}

	pcaldata = (u32 *)(user_info.nv_data + 4);
	return snprintf(buf, PAGE_SIZE, "%d:%08x %08x %08x\n", return_cap_prox_calibration,
					pcaldata[0], pcaldata[1], pcaldata[2]);
}

static int cap_prox_calibrate_save(const void *buf, int length)
{
	int ret=0;
	u32 *pcaldata = NULL;
	struct hisi_nve_info_user user_info;

	if (buf == NULL || length != 12) {
		hwlog_err("%s invalid argument.", __func__);
		return_cap_prox_calibration = EXEC_FAIL;
		return -1;
	}
	pcaldata = (u32 *)buf;
	hwlog_err("%s:cap_prox calibrate ok, %08x  %08x  %08x \n", __func__,
				pcaldata[0],pcaldata[1],pcaldata[2]);

	memset(&user_info, 0, sizeof(user_info));
	//read from nv
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = CAP_PROX_CALIDATA_NV_NUM;
	user_info.valid_size = CAP_PROX_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "Csensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0) {
		return_cap_prox_calibration = EXEC_FAIL;
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -2;
	}

	pcaldata = (u32 *)(user_info.nv_data + 4);
	memcpy(pcaldata, buf, length);

	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = CAP_PROX_CALIDATA_NV_NUM;
	user_info.valid_size = CAP_PROX_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "Csensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info)) != 0) {
		return_cap_prox_calibration = EXEC_FAIL;
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -3;
	}

	return_cap_prox_calibration = SUC;
	return 0;
}

static ssize_t attr_cap_prox_calibrate_write(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val = 0;
	int ret = 0;
	write_info_t pkg_ap;
	read_info_t pkg_mcu;

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;
	if (1 == val) {
		pkg_ap.tag = TAG_CAP_PROX;
		pkg_ap.cmd = CMD_CAP_PROX_CALIBRATE_REQ;
		pkg_ap.wr_buf = NULL;
		pkg_ap.wr_len = 0;
		ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
		if (ret) {
			return_cap_prox_calibration = COMMU_FAIL;
			hwlog_err("send cap_prox calibrate cmd to mcu fail,ret=%d\n", ret);
			return count;
		}
		if (pkg_mcu.errno != 0) {
			hwlog_err("cap_prox calibrate fail\n");
			return_cap_prox_calibration = EXEC_FAIL;
		} else {
			hwlog_info("cap_prox calibrate  success, data len=%d\n", pkg_mcu.data_length);
			cap_prox_calibrate_save(pkg_mcu.data, pkg_mcu.data_length);
		}
	}
	return count;
}
//static DEVICE_ATTR(cap_prox_calibrate, 0664, attr_cap_prox_calibrate_show, attr_cap_prox_calibrate_write);

static ssize_t attr_cap_prox_freespace_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	u16 *pfreespace = NULL;

	memset(&user_info, 0, sizeof(user_info));

	//read from nv
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = CAP_PROX_CALIDATA_NV_NUM;
	user_info.valid_size = CAP_PROX_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "Csensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0) {
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}

	pfreespace = (u16 *)user_info.nv_data;
	return snprintf(buf, MAX_STR_SIZE, "%04x%04x\n", pfreespace[0], pfreespace[1]);
}

static ssize_t attr_cap_prox_freespace_write(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	uint32_t val = 0;
	char *pt = NULL;
	int ret = 0;
	struct hisi_nve_info_user user_info;
	u16 *pfreespace = NULL;

	val = simple_strtoul(buf, &pt, 0);

	memset(&user_info, 0, sizeof(user_info));
	//read from nv
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = CAP_PROX_CALIDATA_NV_NUM;
	user_info.valid_size = CAP_PROX_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "Csensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0) {
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}

	pfreespace = (u16 *)user_info.nv_data;
	pfreespace[0] = (u16)((val >> 16) & 0xffff);
	pfreespace[1] = (u16)(val & 0xffff);

	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = CAP_PROX_CALIDATA_NV_NUM;
	user_info.valid_size = CAP_PROX_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "Csensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info)) != 0) {
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -2;
	}

	return count;
}
//static DEVICE_ATTR(cap_prox_freespace, 0664, attr_cap_prox_freespace_show, attr_cap_prox_freespace_write);

/*if val is odd, then last status is sleep, if is even number, then last status is wakeup */
static ssize_t attr_iom3_sr_test_store(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val = 0;
	unsigned long times = 0;

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	times = val;

	if(val > 0){
		for(; val > 0; val--){
			disable_sensors_when_suspend();
			tell_ap_status_to_mcu(ST_SLEEP);
			msleep(2);
			tell_ap_status_to_mcu(ST_WAKEUP);
			enable_sensors_when_resume();
		}

		if (times%2){
			tell_ap_status_to_mcu(ST_SLEEP);
			enable_sensors_when_resume();
		}
	}
	return count;
}

static DEVICE_ATTR(iom3_sr_test, 0664, NULL, attr_iom3_sr_test_store);

//acc enable node
#define SHOW_ENABLE_FUNC(NAME, TAG)\
static ssize_t show_##NAME##_enable_result(struct device *dev,\
				struct device_attribute *attr, char *buf)\
{\
	return snprintf(buf, MAX_STR_SIZE, "%d\n", sensor_status.status[TAG]);\
}

#define STORE_ENABLE_FUNC(NAME, TAG, CMD1, CMD2)\
static ssize_t attr_set_##NAME##_enable(struct device *dev, struct device_attribute *attr,\
				const char *buf, size_t size)\
{\
	unsigned long val = 0;\
	int ret = -1;\
	write_info_t	pkg_ap;\
	read_info_t pkg_mcu;\
	memset(&pkg_ap, 0, sizeof(pkg_ap));\
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));\
	if (strict_strtoul(buf, 10, &val))\
		return -EINVAL;\
	if(1==val)\
	{\
		pkg_ap.tag=TAG;\
		pkg_ap.cmd=CMD1;\
		pkg_ap.wr_buf=NULL;\
		pkg_ap.wr_len=0;\
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);\
		if(ret)\
		{\
			hwlog_err("send %s enable cmd to mcu fail,ret=%d\n", #NAME, ret);\
			return size;\
		} \
		if(pkg_mcu.errno!=0) hwlog_err("set %s enable fail\n", #NAME);\
		else hwlog_info("%s enable success\n", #NAME);\
        if ((TAG == TAG_ACCEL) && (acc_close_after_calibrate == true))\
        {\
            acc_close_after_calibrate = false;\
            hwlog_info("%s received open command during calibrate, will not close after calibrate!\n", #NAME);\
        }\
	}else\
	{\
		pkg_ap.tag=TAG;\
		pkg_ap.cmd=CMD2;\
		pkg_ap.wr_buf=NULL;\
		pkg_ap.wr_len=0;\
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);\
		if(ret)\
		{\
			hwlog_err("send %s disable cmd to mcu fail,ret=%d\n", #NAME, ret);\
			return size;\
		}\
		if(pkg_mcu.errno!=0) hwlog_err("set %s disable fail\n", #NAME);\
		else hwlog_info("%s disable success\n", #NAME);\
	}\
	return size;\
}

#define SHOW_DELAY_FUNC(NAME, TAG) \
static ssize_t show_##NAME##_delay_result(struct device *dev,\
				struct device_attribute *attr, char *buf)\
{\
	return snprintf(buf, MAX_STR_SIZE, "%d\n", sensor_status.delay[TAG]);\
}

#define STORE_DELAY_FUNC(NAME, TAG, CMD)  \
static ssize_t attr_set_##NAME##_delay(struct device *dev, struct device_attribute *attr,\
				const char *buf, size_t size)\
{\
	unsigned long val = 0;\
	int ret = -1;\
	write_info_t	pkg_ap;\
	read_info_t pkg_mcu;\
\
	memset(&pkg_ap, 0, sizeof(pkg_ap));\
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));\
	if (sensor_status.opened[TAG] == 0) {\
		hwlog_err("send tag %d delay must be opend first! \n", TAG);\
		return -EINVAL;\ 
	}\
	if (strict_strtoul(buf, 10, &val))\
		return -EINVAL;\
	if(val>=10&& val<1000)\
	{\
		pkg_ap.tag=TAG;\
		pkg_ap.cmd=CMD;\
		pkg_ap.wr_buf=&val;\
		pkg_ap.wr_len=sizeof(val);\
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);\
		if(ret)\
		{\
			hwlog_err("send %s delay cmd to mcu fail,ret=%d\n", #NAME, ret);\
			return size;\
		}\
		if(pkg_mcu.errno!=0) hwlog_err("set %s delay fail\n", #NAME);\
		else\
		{\
			hwlog_info("set %s delay (%ld)success\n", #NAME, val);\
		}\
	}\
	return size;\
}

SHOW_ENABLE_FUNC(acc, TAG_ACCEL)
STORE_ENABLE_FUNC(acc, TAG_ACCEL, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(acc_enable, 0664, show_acc_enable_result, attr_set_acc_enable);
SHOW_DELAY_FUNC(acc, TAG_ACCEL)
STORE_DELAY_FUNC(acc, TAG_ACCEL, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(acc_setdelay, 0664, show_acc_delay_result, attr_set_acc_delay);

SHOW_ENABLE_FUNC(gyro, TAG_GYRO)
STORE_ENABLE_FUNC(gyro, TAG_GYRO, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(gyro_enable, 0664, show_gyro_enable_result, attr_set_gyro_enable);
SHOW_DELAY_FUNC(gyro, TAG_GYRO)
STORE_DELAY_FUNC(gyro, TAG_GYRO, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(gyro_setdelay, 0664, show_gyro_delay_result, attr_set_gyro_delay);

SHOW_ENABLE_FUNC(mag, TAG_MAG)
STORE_ENABLE_FUNC(mag, TAG_MAG, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(mag_enable, 0664, show_mag_enable_result, attr_set_mag_enable);
SHOW_DELAY_FUNC(mag, TAG_MAG)
STORE_DELAY_FUNC(mag, TAG_MAG, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(mag_setdelay, 0664, show_mag_delay_result, attr_set_mag_delay);

SHOW_ENABLE_FUNC(als, TAG_ALS)
STORE_ENABLE_FUNC(als, TAG_ALS, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(als_enable, 0664, show_als_enable_result, attr_set_als_enable);
SHOW_DELAY_FUNC(als, TAG_ALS)
STORE_DELAY_FUNC(als, TAG_ALS, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(als_setdelay, 0664, show_als_delay_result, attr_set_als_delay);

SHOW_ENABLE_FUNC(sbl, TAG_LABC)
STORE_ENABLE_FUNC(sbl, TAG_LABC, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(sbl_enable, 0664, show_sbl_enable_result, attr_set_sbl_enable);
SHOW_DELAY_FUNC(sbl, TAG_LABC)
STORE_DELAY_FUNC(sbl, TAG_LABC, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(sbl_setdelay, 0664, show_sbl_delay_result, attr_set_sbl_delay);

#define BL_SETTING_LEN 16
static char buffer[BL_SETTING_LEN]={0};
static ssize_t show_sbl_backlight_result(struct device *dev, struct device_attribute *attr, char *buf)
{
	return snprintf(buf, MAX_STR_SIZE, "[LABC] sbl_backlight '%s'\n", buffer);
}

static ssize_t attr_set_sbl_backlight(struct device *dev, struct device_attribute *attr,
    const char *buf, size_t size)
{
	unsigned long val = 0;
	int ret = -1;
	 //char buffer[BL_SETTING_LEN]={0};
	write_info_t pkg_ap;
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	strncpy(buffer, buf, BL_SETTING_LEN-1);
	if(buf[size-1]=='\n' && size<BL_SETTING_LEN) buffer[size-1]=0;
	hwlog_debug("[LABC] set backlight '%s'\n", buffer);
	pkg_ap.tag = TAG_LABC;
	pkg_ap.cmd = CMD_CMN_CONFIG_REQ;
	pkg_ap.wr_buf = buffer;
	pkg_ap.wr_len = BL_SETTING_LEN;
	ret = write_customize_cmd(&pkg_ap,  NULL);

	if(ret) hwlog_err("[LABC] send backlight cmd to mcu fail,ret=%d\n", ret);

	return size;
}

static DEVICE_ATTR(sbl_setbacklight, 0664, show_sbl_backlight_result, attr_set_sbl_backlight);


SHOW_ENABLE_FUNC(ps, TAG_PS)
STORE_ENABLE_FUNC(ps, TAG_PS, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(ps_enable, 0664, show_ps_enable_result, attr_set_ps_enable);
SHOW_DELAY_FUNC(ps, TAG_PS)
STORE_DELAY_FUNC(ps, TAG_PS, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(ps_setdelay, 0664, show_ps_delay_result, attr_set_ps_delay);

SHOW_ENABLE_FUNC(os, TAG_ORIENTATION)
STORE_ENABLE_FUNC(os, TAG_ORIENTATION, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(orientation_enable, 0664, show_os_enable_result, attr_set_os_enable);
SHOW_DELAY_FUNC(os, TAG_ORIENTATION)
STORE_DELAY_FUNC(os, TAG_ORIENTATION, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(orientation_setdelay, 0664, show_os_delay_result, attr_set_os_delay);


SHOW_ENABLE_FUNC(lines, TAG_LINEAR_ACCEL)
STORE_ENABLE_FUNC(lines, TAG_LINEAR_ACCEL, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(lines_enable, 0664, show_lines_enable_result, attr_set_lines_enable);
SHOW_DELAY_FUNC(lines, TAG_LINEAR_ACCEL)
STORE_DELAY_FUNC(lines, TAG_LINEAR_ACCEL, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(lines_setdelay, 0664, show_lines_delay_result, attr_set_lines_delay);


SHOW_ENABLE_FUNC(gras, TAG_GRAVITY)
STORE_ENABLE_FUNC(gras, TAG_GRAVITY, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(gras_enable, 0664, show_gras_enable_result, attr_set_gras_enable);
SHOW_DELAY_FUNC(gras, TAG_GRAVITY)
STORE_DELAY_FUNC(gras, TAG_GRAVITY, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(gras_setdelay, 0664, show_gras_delay_result, attr_set_gras_delay);

SHOW_ENABLE_FUNC(rvs, TAG_ROTATION_VECTORS)
STORE_ENABLE_FUNC(rvs, TAG_ROTATION_VECTORS, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(rvs_enable, 0664, show_rvs_enable_result, attr_set_rvs_enable);
SHOW_DELAY_FUNC(rvs, TAG_ROTATION_VECTORS)
STORE_DELAY_FUNC(rvs, TAG_ROTATION_VECTORS, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(rvs_setdelay, 0664, show_rvs_delay_result, attr_set_rvs_delay);

SHOW_ENABLE_FUNC(airpress, TAG_PRESSURE)
STORE_ENABLE_FUNC(airpress, TAG_PRESSURE, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(airpress_enable, 0664, show_airpress_enable_result, attr_set_airpress_enable);
SHOW_DELAY_FUNC(airpress, TAG_PRESSURE)
STORE_DELAY_FUNC(airpress, TAG_PRESSURE, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(airpress_setdelay, 0664, show_airpress_delay_result, attr_set_airpress_delay);

static ssize_t attr_set_pdr_delay(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	//unsigned long val = 0;
	int val = 0;
	int ret = -1;
    int start_update_flag;
    int precise;
    int interval;
	write_info_t	pkg_ap;
	read_info_t pkg_mcu;
    pdr_ioctl_t pkg_ioctl;

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;
    //val define: xyyzzz x:0 start 1 update yy:precise zzz:interval
    if (val == 0)  val = 1010;
    start_update_flag = (val/100000);
    precise = (val/1000) % 100;
    interval = val % 1000;
	
    hwlog_info("val = %d start_update_flag = %d precise = %d interval= %d\n",val,start_update_flag,precise,interval);
    if (precise == 0) precise = 1;
    if (interval == 0) interval = 240;

    pkg_ap.tag=TAG_PDR;
    pkg_ap.cmd=CMD_CMN_CONFIG_REQ;

	if(val >= 1000)
	{
	    pkg_ioctl.sub_cmd = (start_update_flag == 0 ? CMD_FLP_PDR_START_REQ : CMD_FLP_PDR_UPDATE_REQ);
        pkg_ioctl.start_param.report_interval = interval * 1000;
        pkg_ioctl.start_param.report_precise = precise * 1000;
        pkg_ioctl.start_param.report_count = interval / precise;
        pkg_ioctl.start_param.report_times = 0;
		pkg_ap.wr_buf=&pkg_ioctl;
		pkg_ap.wr_len=sizeof(pkg_ioctl);
	}
    else if (val == 2) //2: stop command
    {
        pkg_ioctl.sub_cmd = CMD_FLP_PDR_STOP_REQ;
        pkg_ioctl.stop_param  = 30000;
		pkg_ap.wr_buf=&pkg_ioctl;
		pkg_ap.wr_len=sizeof(pkg_ioctl);
    }
    hwlog_info(" pkg_ioctl.sub_cmd = %d\n ",pkg_ioctl.sub_cmd);    
	ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
	if(ret)
	{
		hwlog_err("send pdr delay cmd to mcu fail,ret=%d\n", ret);
		return size;
	}
	if(pkg_mcu.errno!=0) hwlog_err("set pdr delay fail\n");
	else
	{
		hwlog_info("set pdr delay (%ld)success\n", val);
	}
	return size;
}

SHOW_ENABLE_FUNC(pdr, TAG_PDR)
STORE_ENABLE_FUNC(pdr, TAG_PDR, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(pdr_enable, 0664, show_pdr_enable_result, attr_set_pdr_enable);
SHOW_DELAY_FUNC(pdr, TAG_PDR)
static DEVICE_ATTR(pdr_setdelay, 0664, show_pdr_delay_result, attr_set_pdr_delay);

//SHOW_ENABLE_FUNC(handpress, TAG_HANDPRESS)
//STORE_ENABLE_FUNC(handpress, TAG_HANDPRESS, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
//static DEVICE_ATTR(handpress_enable, 0664, show_handpress_enable_result, attr_set_handpress_enable);
//SHOW_DELAY_FUNC(handpress, TAG_HANDPRESS)
//STORE_DELAY_FUNC(handpress, TAG_HANDPRESS, CMD_CMN_INTERVAL_REQ)
//static DEVICE_ATTR(handpress_setdelay, 0664, show_handpress_delay_result, attr_set_handpress_delay);

//SHOW_ENABLE_FUNC(cap_prox, TAG_CAP_PROX)
//STORE_ENABLE_FUNC(cap_prox, TAG_CAP_PROX, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
//static DEVICE_ATTR(cap_prox_enable, 0664, show_cap_prox_enable_result, attr_set_cap_prox_enable);
//SHOW_DELAY_FUNC(cap_prox, TAG_CAP_PROX)
//STORE_DELAY_FUNC(cap_prox, TAG_CAP_PROX, CMD_CMN_INTERVAL_REQ)
//static DEVICE_ATTR(cap_prox_setdelay, 0664, show_cap_prox_delay_result, attr_set_cap_prox_delay);

#ifdef CONFIG_IOM3_RECOVERY
static ssize_t start_iom3_recovery(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	hwlog_info("%s +\n", __func__);
	iom3_need_recovery();
	hwlog_info("%s -\n", __func__);
	return size;
}
static DEVICE_ATTR(iom3_recovery, 0664, NULL, start_iom3_recovery);
#endif
/*fordden sensor cmd from HAL*/
int flag_for_sensor_test = 0;
static ssize_t attr_set_sensor_test_mode(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	unsigned long val = 0;
	hwlog_info("%s +\n", __func__);
	if (strict_strtoul(buf, 10, &val)) {
		hwlog_err("In %s! val = %lu\n", __func__, val);
		return -EINVAL;
	}
	if(1 == val)
		flag_for_sensor_test = 1;
	else
		flag_for_sensor_test = 0;
	return size;
}
static DEVICE_ATTR(sensor_test, 0664, NULL, attr_set_sensor_test_mode);

static ssize_t attr_set_rdr_test(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
//	hisi_system_error(HISI_RDR_MOD_IOM3_NORMAL, 0, 0, NULL, 0);
	return size;
}
static DEVICE_ATTR(rdr_test, 0664, NULL, attr_set_rdr_test);

/*buf: motion value, 2byte,
   motion type, 0-11
   second status 0-4
*/
static ssize_t attr_set_dt_motion_stup(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	char dt_motion_value[5] = {};
	int i = 0;
	unsigned long source = 0;

	source = simple_strtoul(buf, NULL, 16);
	hwlog_err("%s buf %s, source %lu\n", __func__, buf, source);

	for (; i < size; i++){
		dt_motion_value[i] = source % ((i+1)*16);
		source = source/16;
	}

	dt_motion_value[4]  = '\0';
       hwlog_err("%s motion %x %x %x %x\n", __func__, dt_motion_value[0], dt_motion_value[1], dt_motion_value[2], dt_motion_value[3]);
	inputhub_route_write(ROUTE_MOTION_PORT, dt_motion_value, 4);

	return size;
}
static DEVICE_ATTR(dt_motion_stup, 0664, NULL, attr_set_dt_motion_stup);

int stop_auto_accel = 0;
static ssize_t attr_set_stop_auto_data(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	stop_auto_accel = simple_strtoul(buf, NULL, 16);
	hwlog_err("%s stop_auto_accel %d\n", __func__, stop_auto_accel);
	return size;
}

static DEVICE_ATTR(dt_stop_auto_data, 0664, NULL, attr_set_stop_auto_data);
static ssize_t attr_set_sensor_motion_stup(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	int i = 0;
	unsigned long source = 0;
	struct sensor_data event;
	source = simple_strtoul(buf, NULL, 16);

	if (source){ /*1: landscape*/
		hwlog_err("%s landscape\n", __func__);
		event.type = TAG_ACCEL;
		event.length = 12;
		event.value[0] = 1000;
		event.value[1] = 0;
		event.value[2] = 0;
	}else{ /*0: portial*/
		hwlog_err("%s portial\n", __func__);
		event.type = TAG_ACCEL;
		event.length = 12;
		event.value[0] = 0;
		event.value[1] = 1000;
		event.value[2] = 0;
	}

	for( i = 0; i < 20 ; i++){
		msleep(100);
		report_sensor_event(TAG_ACCEL, event.value, event.length);
	}
	return size;
}
static DEVICE_ATTR(dt_sensor_stup, 0664, NULL, attr_set_sensor_motion_stup);

static ssize_t attr_set_sensor_stepcounter_stup(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	unsigned long source = 0;
	struct sensor_data event;
	source = simple_strtoul(buf, NULL, 10);

	event.type = TAG_STEP_COUNTER;
	event.length = 12;
	event.value[0] = source;
	event.value[1] = 0;
	event.value[2] = 0;

	report_sensor_event(TAG_STEP_COUNTER, event.value, event.length);
	return size;
}
static DEVICE_ATTR(dt_stepcounter_stup, 0664, NULL, attr_set_sensor_stepcounter_stup);

static ssize_t show_iom3_sr_status(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, MAX_STR_SIZE, "%s\n", (iom3_sr_status == ST_SLEEP)?"ST_SLEEP":"ST_WAKEUP");
}
static DEVICE_ATTR(iom3_sr_status, 0664, show_iom3_sr_status, NULL);

ssize_t show_mag_calibrate_method(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, MAX_STR_SIZE, "%d\n", mag_data.calibrate_method);
}

static int airpress_cali_flag = 0;
ssize_t show_sensor_read_airpress_common(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	airpress_cali_flag = 1;
	return snprintf(buf, MAX_STR_SIZE, "%d\n", get_airpress_data);
}
static ssize_t show_sensor_read_airpress(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return show_sensor_read_airpress_common(dev, attr, buf);
}
static DEVICE_ATTR(read_airpress, 0664, show_sensor_read_airpress, NULL);

static ssize_t show_sensor_read_temperature(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, MAX_STR_SIZE, "%d\n", get_temperature_data);
}
static DEVICE_ATTR(read_temperature, 0664, show_sensor_read_temperature, NULL);

static ssize_t show_dump_sensor_status(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int tag = 0;
	hwlog_info("-------------------------------------\n");
	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		if(unlikely((tag == TAG_PS)||(tag == TAG_STEP_COUNTER))){/*ps and step counter need always on, just skip*/
			continue;
		}
		hwlog_info(" %s\t %s\t %d\n", obj_tag_str[tag], sensor_status.opened[tag]?"open":"close", sensor_status.delay[tag]);
	}
	hwlog_info("-------------------------------------\n");
	return snprintf(buf, MAX_STR_SIZE, "please check log %d\n", get_temperature_data);
}
static DEVICE_ATTR(dump_sensor_status, 0664, show_dump_sensor_status, NULL);

static ssize_t show_airpress_set_calidata(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (strlen(sensor_chip_info[AIRPRESS]) != 0)
		return snprintf(buf, MAX_STR_SIZE, "%d\n", airpress_data.offset);
	else
		return -1;
}
static ssize_t store_airpress_set_calidata(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	long source = 0;
	int ret = 0;
	int i;
	struct hisi_nve_info_user user_info;
	int temp;
	write_info_t pkg_ap;
	read_info_t  pkg_mcu;

	if(strlen(sensor_chip_info[AIRPRESS]) == 0) {
		hwlog_err("AIRPRESS not exits !!\n");
		return -1;
	}
	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (!airpress_cali_flag) {
		hwlog_warn("Takes effect only when the calibration data\n");
		return -1;
	}
	source = simple_strtol(buf, NULL, 10);
	airpress_data.offset += (int)source;

	for(i=0;i<48;i++)
		airpress_data.airpress_extend_data[i] = i;
	//send to mcu
	pkg_ap.tag = TAG_PRESSURE;
	pkg_ap.cmd = CMD_AIRPRESS_SET_CALIDATA_REQ;
	pkg_ap.wr_buf = (const void *)&airpress_data;
	pkg_ap.wr_len = sizeof(airpress_data);
	hwlog_info("***%s***\n",__func__);
	if((ret = write_customize_cmd(&pkg_ap, &pkg_mcu)) != 0) {
		hwlog_err("set airpress_sensor data failed, ret = %d!\n", ret);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set airpress_sensor data failed\n");
		return -1;
	}
	if(pkg_mcu.errno!=0)
	{
		hwlog_err("set airpress_sensor sysfs offset fail,err=%d\n", pkg_mcu.errno);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set airpress_sensor offset fail\n");
	}
	else
	{
		hwlog_info("send airpress_sensor sysfs data :%d to mcu success\n", airpress_data.offset);
	}

	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = AIRPRESS_CALIDATA_NV_NUM;
	user_info.valid_size = AIRPRESS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "AIRDATA", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	memcpy(user_info.nv_data, &airpress_data.offset, sizeof(airpress_data.offset));

	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	msleep(10);
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = AIRPRESS_CALIDATA_NV_NUM;
	user_info.valid_size = AIRPRESS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "AIRDATA", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve direct access read error(%d)\n", ret);
		return -1;
	}
	memcpy(&temp, user_info.nv_data, sizeof(temp));
	if(temp != airpress_data.offset)
	{
		hwlog_err("nv write fail, (%d %d)\n", temp, airpress_data.offset);
		return -1;
	}
	airpress_cali_flag = 0;
	return size;
}
static DEVICE_ATTR(airpress_set_calidata, 0664, show_airpress_set_calidata, store_airpress_set_calidata);

ssize_t sensors_calibrate_show(int tag, struct device *dev,
				struct device_attribute *attr, char *buf)
{
	switch (tag) {
	case TAG_ACCEL:
		return snprintf(buf, PAGE_SIZE, "%d\n", return_calibration != SUC);//flyhorse k: SUC-->"0", OTHERS-->"1"

	case TAG_PS:
		return snprintf(buf, PAGE_SIZE, "%d\n", ps_calibration_res != SUC);//flyhorse k: SUC-->"0", OTHERS-->"1"

	case TAG_PRESSURE:
		return show_airpress_set_calidata(dev, attr, buf);

	default:
		hwlog_err("tag %d calibrate not implement in %s\n", tag, __func__);
		break;
	}

	return 0;
}

ssize_t sensors_calibrate_store(int tag, struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	switch (tag) {
	case TAG_ACCEL:
		return attr_acc_calibrate_write(dev, attr, buf, count);

	case TAG_PS:
		return attr_ps_calibrate_write(dev, attr, buf, count);

	case TAG_PRESSURE:
		return store_airpress_set_calidata(dev, attr, buf, count);

	default:
		hwlog_err("tag %d calibrate not implement in %s\n", tag, __func__);
		break;
	}

	return count;
}


static struct attribute *sensor_attributes[] = {
	&dev_attr_acc_info.attr,
	&dev_attr_mag_info.attr,
	&dev_attr_gyro_info.attr,
	&dev_attr_ps_info.attr,
	&dev_attr_als_info.attr,
	&dev_attr_acc_read_data.attr,
	&dev_attr_mag_read_data.attr,
	&dev_attr_gyro_read_data.attr,
	&dev_attr_ps_read_data.attr,
	&dev_attr_als_read_data.attr,
	&dev_attr_gyro_selfTest.attr,
	&dev_attr_mag_selfTest.attr,
	&dev_attr_acc_selfTest.attr,
	&dev_attr_i2c_rw.attr,
	&dev_attr_i2c_rw16.attr,
	&dev_attr_acc_calibrate.attr,
	&dev_attr_acc_enable.attr,
	&dev_attr_acc_setdelay.attr,
	&dev_attr_gyro_calibrate.attr,
	&dev_attr_gyro_enable.attr,
	&dev_attr_gyro_setdelay.attr,
	&dev_attr_mag_enable.attr,
	&dev_attr_mag_setdelay.attr,
	&dev_attr_als_calibrate.attr,
	&dev_attr_als_enable.attr,
	&dev_attr_als_setdelay.attr,
	&dev_attr_sbl_enable.attr,
	&dev_attr_sbl_setdelay.attr,
	&dev_attr_sbl_setbacklight.attr,
	&dev_attr_ps_calibrate.attr,
	&dev_attr_ps_enable.attr,
	&dev_attr_ps_setdelay.attr,
	&dev_attr_pdr_enable.attr,
	&dev_attr_pdr_setdelay.attr,
	&dev_attr_orientation_enable.attr,
	&dev_attr_orientation_setdelay.attr,
	&dev_attr_lines_enable.attr,
	&dev_attr_lines_setdelay.attr,
	&dev_attr_gras_enable.attr,
	&dev_attr_gras_setdelay.attr,
	&dev_attr_rvs_enable.attr,
	&dev_attr_rvs_setdelay.attr,
	&dev_attr_sensor_list_info.attr,
#ifdef CONFIG_IOM3_RECOVERY
	&dev_attr_iom3_recovery.attr,
#endif
	&dev_attr_sensor_test.attr,
	&dev_attr_iom3_sr_test.attr,
	&dev_attr_dt_motion_stup.attr,
	&dev_attr_dt_sensor_stup.attr,
	&dev_attr_dt_stop_auto_data.attr,
	&dev_attr_airpress_info.attr,
	&dev_attr_airpress_enable.attr,
	&dev_attr_airpress_setdelay.attr,
	&dev_attr_airpress_read_data.attr,
	&dev_attr_airpress_set_calidata.attr,
	&dev_attr_read_airpress.attr,
	&dev_attr_read_temperature.attr,
	&dev_attr_dt_stepcounter_stup.attr,
	//&dev_attr_handpress_info.attr,
	//&dev_attr_handpress_enable.attr,
	//&dev_attr_handpress_setdelay.attr,
	//&dev_attr_handpress_read_data.attr,
	&dev_attr_iom3_sr_status.attr,
	//&dev_attr_cap_prox_info.attr,
	//&dev_attr_cap_prox_read_data.attr,
	//&dev_attr_cap_prox_calibrate.attr,
	//&dev_attr_cap_prox_freespace.attr,
	//&dev_attr_cap_prox_enable.attr,
	//&dev_attr_cap_prox_setdelay.attr,
	&dev_attr_rdr_test.attr,
	&dev_attr_dump_sensor_status.attr,
	NULL
};
static const struct attribute_group sensor_node = {
	.attrs = sensor_attributes,
};

static struct platform_device sensor_input_info = {
	.name = "huawei_sensor",
	.id = -1,
};


int get_lcd_module(void){
	int ret = -1;
	struct device_node *np = NULL;

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_JDI_NT35695_CUT3_1);
	ret = of_device_is_available(np);
	if (np && ret) {
		hwlog_info("%s is present\n", DTS_COMP_JDI_NT35695_CUT3_1);
		return JDI_TPLCD;
	}

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_LG_ER69006A);
	ret = of_device_is_available(np);
	if (np && ret) {
		hwlog_info("%s is present\n", DTS_COMP_LG_ER69006A);
		return LG_TPLCD;
	}

	np = of_find_compatible_node(NULL, NULL, DTS_COMP_JDI_NT35695_CUT2_5);
	ret = of_device_is_available(np);
	if (np && ret) {
		hwlog_info("%s is present\n", DTS_COMP_JDI_NT35695_CUT2_5);
		return JDI_TPLCD;
	}

	hwlog_err("sensor kernel failed to get lcd module\n");
	return ret;
}

extern atomic_t iom3_rec_state;
int mcu_sys_ready_callback(const pkt_header_t *head)
{
	int ret = 0;
	if (ST_MINSYSREADY == ((pkt_sys_statuschange_req_t *)head)->status)
	{
		hwlog_info("sys ready mini!\n");
        tplcd_manufacture = get_lcd_module();
        hwlog_err("sensor kernel get_lcd_module tplcd_manufacture=%d\n", tplcd_manufacture);
		ret = init_sensors_cfg_data_from_dts();
		if(ret) hwlog_err("get sensors cfg data from dts fail,ret=%d, use default config data!\n", ret);
		else hwlog_info( "get sensors cfg data from dts success!\n");
	}else if (ST_MCUREADY == ((pkt_sys_statuschange_req_t *)head)->status)
	{
		hwlog_info("mcu all ready!\n");
		ret = sensor_set_cfg_data();
		if(ret<0) hwlog_err("sensor_chip_detect ret=%d\n", ret);
		unregister_mcu_event_notifier(TAG_SYS, CMD_SYS_STATUSCHANGE_REQ, mcu_sys_ready_callback);
#ifdef CONFIG_IOM3_RECOVERY
		atomic_set(&iom3_rec_state, IOM3_RECOVERY_IDLE);
#endif
	}else{
		hwlog_info("other status\n");
	}
	return 0;
}
int mcu_reboot_callback(const pkt_header_t *head)
{
	if (ST_WAKEUP== ((pkt_sys_statuschange_req_t *)head)->status)
       {   
                hwlog_err("%s\n",__func__);
		complete(&iom3_reboot);
       }
	return 0;
}

static struct of_device_id sensorhub_io_supply_ids[] = {
	{.compatible = "huawei,sensorhub_io" },
	{}
};

MODULE_DEVICE_TABLE(of, sensorhub_io_supply_ids);

static struct regulator *sensorhub_vddio;
static int sensorhub_io_driver_probe(struct platform_device *pdev)
{
	int ret = 0;
	if (!of_match_device(sensorhub_io_supply_ids, &pdev->dev)){
		hwlog_err("[%s,%d]: sensorhub_io_driver_probe match fail !\n", __FUNCTION__, __LINE__);
		return -ENODEV;
	}
	sensorhub_vddio = regulator_get(&pdev->dev, SENSOR_VBUS);
	if(IS_ERR(sensorhub_vddio)){
           hwlog_err("%s: regulator_get fail!\n", __func__);
	    return  -EINVAL;
	}
	ret = regulator_enable(sensorhub_vddio);
	if (ret< 0) {
		hwlog_err("failed to enable regulator sensorhub_vddio\n");
		return -EINVAL;
	}
	hwlog_err("%s: sensorhub_io_driver_probe success!\n", __func__);
	return 0;
}

extern int sensorhub_pm_suspend(struct device *dev);
extern int sensorhub_pm_resume(struct device *dev);

struct dev_pm_ops sensorhub_io_pm_ops = {
     .suspend = sensorhub_pm_suspend,
     .resume = sensorhub_pm_resume,
};

struct platform_driver sensorhub_io_driver = {
         .probe = sensorhub_io_driver_probe,
         .driver = {
                         .name = "Sensorhub_io_driver",
                         .owner = THIS_MODULE,
                         .of_match_table = of_match_ptr(sensorhub_io_supply_ids),
                         .pm = &sensorhub_io_pm_ops,
         },
};

static int __init sensor_input_info_init(void)
{
	int ret = 0;
	hwlog_info("[%s] ++", __func__);

	if(is_sensorhub_disabled())
	     return -1;
	ret = platform_device_register(&sensor_input_info);
	if (ret) {
		hwlog_err("%s: platform_device_register failed, ret:%d.\n",
				__func__, ret);
		goto REGISTER_ERR;
	}

	ret = sysfs_create_group(&sensor_input_info.dev.kobj, &sensor_node);
	if (ret) {
		hwlog_err("sensor_input_info_init sysfs_create_group error ret =%d", ret);
		goto SYSFS_CREATE_CGOUP_ERR;
	}
	hwlog_info("[%s] --", __func__);

	return 0;
SYSFS_CREATE_CGOUP_ERR:
	platform_device_unregister(&sensor_input_info);
REGISTER_ERR:
	return ret;

}
static int sensorhub_io_driver_init(void)
{
	int ret = 0;
	hwlog_info("[%s] ++", __func__);

	ret = platform_driver_register(&sensorhub_io_driver);
	if (ret) {
		hwlog_err("%s: platform_device_register(sensorhub_io_driver) failed, ret:%d.\n",
				__func__, ret);
		return ret;
	}
	hwlog_info("[%s] --", __func__);

	return 0;
}
static int judge_tp_color_correct(u8 color)
{
	return ((color&0x0f)==((~(color>>4))&0x0f)); //if the tp color is correct, after the 4~7 bit inversion shoud be same with 0~3 bit;
}

static int __init light_sensor_read_tp_color_cmdline(char *arg)
{
	int len = 0;
	int tp_color = 0;
	memset(tp_color_buf, 0, sizeof(tp_color_buf));
	if (arg) {
		len = strlen(arg);

		if (len > sizeof(tp_color_buf)) {
			len = sizeof(tp_color_buf);
		}
		memcpy(tp_color_buf, arg, len);
	} else {
		hwlog_info("%s : arg is NULL\n", __func__);
		phone_color = BLACK;  //BLACK is the default tp color
		return 0;
	}

	tp_color = (int)simple_strtol(tp_color_buf, NULL, 10);

	if(judge_tp_color_correct(tp_color))
	{
		phone_color = tp_color;
	}
	else
	{
		hwlog_err("light senso LCD/TP ID error!\n");
		phone_color = BLACK;  //BLACK is the default tp color
	}

	hwlog_err("light sensor read tp color is %s, 0x%x\n", tp_color_buf,phone_color);
	return 0;
}
early_param("TP_COLOR", light_sensor_read_tp_color_cmdline);

fs_initcall(sensorhub_io_driver_init);
device_initcall(sensor_input_info_init);
MODULE_DESCRIPTION("sensor input info");
MODULE_AUTHOR("huawei driver group of K3V3");
MODULE_LICENSE("GPL");
