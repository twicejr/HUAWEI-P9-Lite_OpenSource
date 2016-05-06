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
#include <linux/huawei/rdr.h>

int hisi_nve_direct_access(struct hisi_nve_info_user *user_info);

#define CAP_PROX_CALIDATA_NV_NUM  310
#define CAP_PROX_CALIDATA_NV_SIZE  16
#define SENSOR_CONFIG_DATA_OK 0
#define MAX_MCU_DATA_LENGTH  30
#define ACC_OFFSET_NV_NUM	307
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
bool sensor_info_isensor_version = false;

bool is_invensense_dmp_exist = false;
static char sensor_chip_info[SENSOR_MAX][50];
static int gsensor_offset[3]; //g-sensor校准参数
static RET_TYPE return_calibration = EXEC_FAIL;
static RET_TYPE return_cap_prox_calibration = EXEC_FAIL;
static struct sensor_status sensor_status;
static struct sensor_status sensor_status_backup;
extern int first_start_flag;
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

static struct gyro_platform_data gyro_data={
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
	.poll_interval=10,
	.outbit=0,
	.axis_map_x=0,
	.axis_map_y=1,
	.axis_map_z=2,
};
static struct als_platform_data als_data={
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
};

static struct ps_platform_data ps_data={
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
	.poll_interval = 1000,
};

static struct handpress_platform_data handpress_data={
	.poll_interval = 500,
};

static struct cap_prox_platform_data cap_prox_data={
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


/*check whether there is sensor active, except ps and hw_extern_step_counter
   return 1: still sensor active
   return 0: no sensor active 
*/
int is_sensor_active()
{
	int tag = 0;
	int ret = 0;
	hwlog_info("%s active sensor ", __func__);
	mutex_lock(&mutex_update);
	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		if(unlikely((tag == TAG_PS)||(tag == TAG_STEP_COUNTER))){/*ps and step counter need always on, just skip*/
			continue;
		}
		if(sensor_status.opened[tag] == 1){
			ret = 1;
			hwlog_info(" %s,", obj_tag_str[tag]);
		}
	}
	mutex_unlock(&mutex_update);
	hwlog_info("ret %d\n", ret);
	return ret;
}

/*check whether there is sensor active during ap sleep, except ps and hw_extern_step_counter
   return 1: still sensor active
   return 0: no sensor active 
*/
int is_backup_sensor_active()
{
	int tag = 0;
	int ret = 0;
	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		if(unlikely((tag == TAG_PS)||(tag == TAG_STEP_COUNTER))){/*ps and step counter need always on, just skip*/
			continue;
		}
		if(sensor_status_backup.opened[tag] == 1){
			ret = 1;
			break;
		}
	}

	hwlog_info("%s active sensor %s, ret %d\n", __func__, obj_tag_str[tag], ret);
	return ret;
}

/*check the new para of the sensor is the same with the old para
   1: need update
     open/close:
     delay: new value is bigger less old one
   0: no updata
     open/close:already close/open
     delay: new value is equal/big than old none
*/
int check_sensor_info(int tag, obj_cmd_t cmd, int delay)
{
	int ret = 1;

	if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
		mutex_lock(&mutex_update);
		if ((CMD_CMN_OPEN_REQ == cmd) &&(sensor_status.opened[tag])) {
			ret = 0;
		} else if ((CMD_CMN_CLOSE_REQ == cmd)&&(!sensor_status.opened[tag])) {
			ret = 0;
		} else if ((CMD_CMN_INTERVAL_REQ == cmd)&&(sensor_status.opened[tag])) {
			if ((sensor_status.delay[tag] != 0)&&(sensor_status.delay[tag] <= delay)){
				ret = 0;
			}
		}
		mutex_unlock(&mutex_update);
	}
	hwlog_info("%s %s cmd %d opened %d old delay %d, new delay %d, ret %d\n", __func__, obj_tag_str[tag], cmd,
				sensor_status.opened[tag], sensor_status.delay[tag], delay, ret);
	return ret;
}

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
	user_info.valid_size = 15;
	strncpy(user_info.nv_name, "gsensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}
	first_start_flag=1;
	gsensor_offset[0] = (int8_t)user_info.nv_data[0];
	gsensor_offset[1] = (int8_t)user_info.nv_data[1];
	gsensor_offset[2] = user_info.nv_data[2];
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

	if(temp==NULL)
	{
		hwlog_err("write_gsensor_offset_to_nv fail, invalid para!\n");
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "write_gsensor_offset_to_nv fail, invalid para!\n");
		return -1;
	}
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = ACC_OFFSET_NV_NUM;
	user_info.valid_size = 15;
	strncpy(user_info.nv_name, "gsensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';

	user_info.nv_data[0] = temp[0];
	user_info.nv_data[1] = temp[1];
	user_info.nv_data[2] = temp[2];
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	hwlog_info( "nve_direct_access write temp (%d %d %d )\n",user_info.nv_data[0],user_info.nv_data[1],user_info.nv_data[2]);

	msleep(10);
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = ACC_OFFSET_NV_NUM;
	user_info.valid_size = 15;
	strncpy(user_info.nv_name, "gsensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		hwlog_err("nve direct access read error(%d)\n", ret);
		return -1;
	}
	if(user_info.nv_data[0] != temp[0] || user_info.nv_data[1] != temp[1] || user_info.nv_data[2] != temp[2])
	{
		hwlog_err("nv write fail, (%d %d %d)\n", user_info.nv_data[0],user_info.nv_data[1],user_info.nv_data[2]);
		return -1;
	}
	return ret;
}

int read_mag_calibrate_data_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t pkg_ap;

	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));

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
	if((ret = write_customize_cmd(&pkg_ap, NULL)) != 0) {
		hwlog_err("set mag_sensor data failed, ret = %d!\n", ret);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "set mag_sensor data failed\n");
		return ret;
	} else {
		hwlog_info("send mag_sensor data to mcu success\n");
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

static int write_customize_cmd_noresp(int tag, int cmd, const void *data, int length)
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
    	msleep(10);
	write_customize_cmd_noresp(TAG_MAG, CMD_MAG_SET_CALIBRATE_TO_MCU_REQ, &msensor_calibrate_data, MAG_CALIBRATE_DATA_NV_SIZE);
	msleep(10);
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
				hwlog_info("%s:i2c detect  suc!\n", device_name);
				return 0;
			}
			}
		hwlog_info("%s:i2c detect  fail!\n", device_name);
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

static int send_fileid_to_mcu(void)
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

	ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
	if (ret)
	{
		hwlog_err("send file id to mcu fail,ret=%d\n", ret);
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

static bool check_invensense_exist(void)
{
	int len = 0;
	struct device_node *sensorhub_node = NULL;
	const char *is_invensense_exist = NULL;

	sensorhub_node = of_find_compatible_node(NULL, NULL, "huawei,sensorhub");
	if (!sensorhub_node) {
		hwlog_err("%s, can't find node sensorhub\n", __func__);
		return false;
	}

	is_invensense_exist = of_get_property(sensorhub_node, "invensense_exist", &len);
	if (!is_invensense_exist) {
		hwlog_err("%s, can't find property boardname\n", __func__);
		return false;
	}

	/*just send current to IOM3 in Mogolia*/
	if (strstr(is_invensense_exist, "yes")) {
		hwlog_info("%s, invensense exist\n", __func__);
		return true;
	} else {
		hwlog_info("%s, invensense not exist\n", __func__);
		return false;
	}
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
static int invense_ICM_20628_set_bypass_for_detect(int i2c_bus_id)
{
	int ret = 0;
	uint8_t buf_for_bypass = 0;
	unsigned char reg = 0;
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, REG_BANK_SEL, 1, 1, &reg);
	if (ret < 0) {
		hwlog_err("read bank reg failed!\n");
		return -1;
	}
	reg &= 0xce;
	reg |= (0 << 4);
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, REG_BANK_SEL, 0, 1, &reg);
	if (ret < 0) {
		hwlog_err("select bank reg failed!\n");
		return -1;
	}
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, INT_PIN_CFG, 1, 1, &buf_for_bypass);
	if (ret < 0) {
		hwlog_err("read bypass reg failed!\n");
		return -1;
	}
	buf_for_bypass |= 2;
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, INT_PIN_CFG, 0, 1, &buf_for_bypass);
	if (ret < 0) {
		hwlog_err("set bypass reg failed!\n");
		return -1;
	}
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, PWR_MGMT_1, 1, 1, &reg);
	if (ret < 0) {
		hwlog_err("read sleep reg failed!\n");
		return -1;
	}
	reg &= 0xbf;
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, PWR_MGMT_1, 0, 1, &reg);
	if (ret < 0) {
		hwlog_err("set sleep reg failed!\n");
		return -1;
	}
	return 0;
}
static int invense_ICM_20628_close_bypass_for_detect(int i2c_bus_id)
{
	int ret = 0;
	uint8_t buf_for_bypass = 0;
	unsigned char reg = 0;
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, REG_BANK_SEL, 1, 1, &reg);
	if (ret < 0) {
		hwlog_err("read bank reg failed!\n");
		return -1;
	}
	reg &= 0xce;
	reg |= (0 << 4);
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, REG_BANK_SEL, 0, 1, &reg);
	if (ret < 0) {
		hwlog_err("set bank reg failed!\n");
		return -1;
	}
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, INT_PIN_CFG, 1, 1, &buf_for_bypass);
	if (ret < 0) {
		hwlog_err("read bypass reg failed!\n");
		return -1;
	}
	buf_for_bypass &= 0xfd;
	ret = mcu_i2c_rw(i2c_bus_id, ICM20628_ADDR, INT_PIN_CFG, 0, 1, &buf_for_bypass);
	if (ret < 0) {
		hwlog_err("close bypass reg failed!\n");
		return -1;
	}
	return 0;
}
static int get_adapt_file_id_for_dyn_load(void)
{
	u32 wia[10]={0};
	struct property *prop = NULL;
	unsigned int i = 0;
	unsigned int len = 0;
	struct device_node *sensorhub_node = NULL;
	const char *name = "adapt_file_id";
	sensorhub_node = of_find_compatible_node(NULL, NULL, "huawei,sensorhub");
	if (!sensorhub_node) {
		hwlog_err("%s, can't find node sensorhub\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "can't find node sensorhub\n");
		return -1;
	}
	prop = of_find_property(sensorhub_node, name, NULL);
	if (!prop) {
		hwlog_err("%s! prop is NULL!\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "prop is NULL\n");
		return -EINVAL;
	}
	if (!prop->value) {
		hwlog_err("%s! prop->value is NULL!\n", __func__);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "prop->value is NULL\n");
		return -ENODATA;
	}
	len = prop->length /4;
	if(of_property_read_u32_array(sensorhub_node, name, wia, len))
	{
		hwlog_err("%s:read adapt_file_id from dts fail!\n", name);
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "read adapt_file_id from dts fail\n");
		return -1;
	}
	for (i = 0; i < len; i++) {
		dyn_req->file_list[dyn_req->file_count] = wia[i];
		dyn_req->file_count++;
	}
	return 0;
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
int send_fileid_to_mcu_in_recovery(void)
{
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;
	int ret = 0, i = 0;
     /*TODO: power off/on */

	hwlog_info("file id number = %d\n", dyn_req->file_count);
	for (i = 0; i < dyn_req->file_count; i++) {
		hwlog_info("filedid = %d\n", dyn_req->file_list[i]);
	}
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	dyn_req->end = 1;
	pkg_ap.tag = TAG_SYS;
	pkg_ap.cmd = CMD_SYS_DYNLOAD_REQ;
	pkg_ap.wr_buf = &(dyn_req->end);
	pkg_ap.wr_len = dyn_req->file_count * sizeof(dyn_req->file_list[0])
					+ sizeof(dyn_req->end) + sizeof(dyn_req->file_count);

//>>>ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
	ret = write_customize_cmd_noresp(TAG_SYS, CMD_SYS_DYNLOAD_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
	if (ret)
	{
		hwlog_err("send file id to mcu fail,ret=%d\n", ret);
		return -1;
	}
	if (pkg_mcu.errno != 0)
	{
		hwlog_err("file id set fail\n");
		dmd_log_report(DSM_SHB_ERR_CFG_DATA, __func__, "file id set fail\n");
		return -1;
	}
	hwlog_info("set file id to mcu  success, data len=%d\n", pkg_mcu.data_length);
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

static int init_sensors_cfg_data_from_dts(void)
{
	int ret = 0, i=0;
	int poll_val=0, gpio_irq=0, ga=0, atime=0, again=0, temp=0;
	char *sensor_ty = NULL, *chip_info = NULL;
	struct device_node *dn = NULL;
	int acc_flag=DET_INIT, mag_flag=DET_INIT, gyro_flag=DET_INIT;
	int airpress_flag = DET_INIT, als_flag=DET_INIT, ps_flag=DET_INIT, hand_flag=DET_INIT,cap_prox_flag=DET_INIT;
	int mag_i2c_bus_id = 0;
	char buf[SENSOR_MAX][50] = {0};
	char detect_result[MAX_STR_SIZE] = {0};

	sensor_info_isensor_version = check_sensorhub_isensor_version();
	is_invensense_dmp_exist = check_invensense_exist();
	for_each_node_with_property(dn, "sensor_type")
	{
		ret=of_property_read_string(dn, "sensor_type", (const char **)&sensor_ty);
		if(ret)
		{
			hwlog_err("get sensor type fail ret=%d\n",ret);
			continue;
		}
		if(!strncmp(sensor_ty, "acc", sizeof("acc")))
		{
			if(acc_flag == DET_SUCC) continue;
			if(detect_i2c_device(dn, "acc")) {
				acc_flag = DET_FAIL;
				strncpy(buf[ACC], "acc detect fail", sizeof(buf[ACC]));
				continue;
			}
			acc_flag = DET_SUCC;
			strncpy(buf[ACC], "acc detect succ", sizeof(buf[ACC]));

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			/* detect current device successful, set the flag as present */
			set_hw_dev_flag(DEV_I2C_G_SENSOR);
#endif
			ret=of_property_read_string(dn, "compatible", (const char **)&chip_info);
			if(ret) hwlog_err("%s:read acc poll_interval fail\n",__func__);
			else strncpy(sensor_chip_info[ACC], chip_info, strlen(chip_info));
			hwlog_info("detect acc dev ok.sensor name=%s\n", chip_info);

			gpio_irq = of_get_named_gpio(dn, "gpio_int1", 0);
			if(gpio_irq) gsensor_data.gpio_int1=(uint8_t)gpio_irq;
			ret=of_property_read_u32(dn, "poll_interval", &poll_val);
			if(ret) hwlog_err("%s:read acc poll_interval fail\n",__func__);
			else gsensor_data.poll_interval=(uint16_t)poll_val;

			ret=of_property_read_u32(dn, "axis_map_x", &temp);
			if(ret) hwlog_err("%s:read acc axis_map_x fail\n",__func__);
			else gsensor_data.axis_map_x=(uint8_t)temp;

			ret=of_property_read_u32(dn, "axis_map_y", &temp);
			if(ret) hwlog_err("%s:read acc axis_map_y fail\n",__func__);
			else gsensor_data.axis_map_y=(uint8_t)temp;

			ret=of_property_read_u32(dn, "axis_map_z", &temp);
			if(ret) hwlog_err("%s:read acc axis_map_z fail\n",__func__);
			else gsensor_data.axis_map_z=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_x", &temp);
			if(ret) hwlog_err("%s:read acc negate_x fail\n",__func__);
			else gsensor_data.negate_x=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_y", &temp);
			if(ret) hwlog_err("%s:read acc negate_y fail\n",__func__);
			else gsensor_data.negate_y=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_z", &temp);
			if(ret) hwlog_err("%s:read acc negate_z fail\n",__func__);
			else gsensor_data.negate_z=(uint8_t)temp;

			ret = of_property_read_u32(dn, "file_id", &temp);
			if(ret) hwlog_err("%s:read acc file_id fail\n", __func__);
			else dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
			dyn_req->file_count++;

			ret = of_property_read_u32(dn, "sensor_list_info_id", &temp);
			if(ret) hwlog_err("%s:read acc sensor_list_info_id fail\n", __func__);
			else sensorlist[++sensorlist[0]] = (uint16_t)temp;
		}else if(!strncmp(sensor_ty, "mag", sizeof("mag")))
		{
			ret = of_property_read_u32(dn, "bus_number", &mag_i2c_bus_id);
			if (ret) hwlog_err("%s:read mag mag_i2c_bus_id fail\n",__func__);
			if (true == is_invensense_dmp_exist && DET_SUCC != mag_flag) {//set INVENSENSE 20628 bypass mode to detect mag
			    ret = invense_ICM_20628_set_bypass_for_detect(mag_i2c_bus_id);
			    if (ret < 0) {
			        hwlog_err("set bypass failed\n");
			        continue;
			    }
			}
			if(mag_flag == DET_SUCC) continue;
			if(detect_i2c_device(dn, "mag")){
				if (true == is_invensense_dmp_exist){
					ret = invense_ICM_20628_close_bypass_for_detect(mag_i2c_bus_id);
					if (ret < 0) {
					    hwlog_err("close bypass failed!\n");
					}
				}
				hwlog_err("mag detect failed !\n");
				mag_flag = DET_FAIL;
				strncpy(buf[MAG], "MAG detect fail", sizeof(buf[MAG]));
				continue;
			}

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			/* detect current device successful, set the flag as present */
			set_hw_dev_flag(DEV_I2C_COMPASS);
#endif
			ret=of_property_read_string(dn, "compatible", (const char **)&chip_info);
			if(ret) hwlog_err("%s:read mag poll_interval fail\n",__func__);
			else strncpy(sensor_chip_info[MAG], chip_info, strlen(chip_info));
			hwlog_info("get mag dev from dts.sensor name=%s\n", chip_info);

			ret=of_property_read_u32(dn, "poll_interval", &poll_val);
			if(ret) hwlog_err("%s:read mag poll_interval fail\n",__func__);
			else mag_data.poll_interval=(uint16_t)poll_val;

			ret=of_property_read_u32(dn, "axis_map_x", &temp);
			if(ret) hwlog_err("%s:read mag axis_map_x fail\n",__func__);
			else mag_data.axis_map_x=(uint8_t)temp;

			ret=of_property_read_u32(dn, "axis_map_y", &temp);
			if(ret) hwlog_err("%s:read mag axis_map_y fail\n",__func__);
			else mag_data.axis_map_y=(uint8_t)temp;

			ret=of_property_read_u32(dn, "axis_map_z", &temp);
			if(ret) hwlog_err("%s:read mag axis_map_z fail\n",__func__);
			else mag_data.axis_map_z=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_x", &temp);
			if(ret) hwlog_err("%s:read mag negate_x fail\n",__func__);
			else mag_data.negate_x=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_y", &temp);
			if(ret) hwlog_err("%s:read mag negate_y fail\n",__func__);
			else mag_data.negate_y=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_z", &temp);
			if(ret) hwlog_err("%s:read mag negate_z fail\n",__func__);
			else mag_data.negate_z=(uint8_t)temp;

			ret=of_property_read_u32(dn, "outbit", &temp);
			if(ret) hwlog_err("%s:read mag outbit fail\n",__func__);
			else mag_data.outbit=(uint8_t)temp;

			ret=of_property_read_u32(dn, "reg", &temp);
			if(ret) hwlog_err("%s:read mag reg fail\n",__func__);
			else mag_data.i2c_address=(uint8_t)temp;

			ret = of_property_read_u32(dn, "file_id", &temp);
			if(ret) hwlog_err("%s:read mag file_id fail\n", __func__);
			if (temp > 0) {
				dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
				dyn_req->file_count++;
			} else {
				hwlog_info("%s:mag file_id = 0\n", __func__);
			}
			ret = of_property_read_u32(dn, "sensor_list_info_id", &temp);
			if(ret) hwlog_err("%s:read mag sensor_list_info_id fail\n", __func__);
			else sensorlist[++sensorlist[0]] = (uint16_t)temp;
			gpio_irq=of_get_named_gpio(dn, "gpio_reset", 0);
			if(gpio_irq) mag_data.gpio_rst=(uint8_t)gpio_irq;

			gpio_irq=of_get_named_gpio(dn, "gpio_drdy", 0);
			if(gpio_irq) mag_data.gpio_drdy=(uint8_t)gpio_irq;

			ret = fill_extend_data_in_dts(dn, str_soft_para, mag_data.pdc_data, PDC_SIZE, EXTEND_DATA_TYPE_IN_DTS_BYTE);
			if (ret) {
				hwlog_err("%s:fill_extend_data_in_dts failed!\n", str_soft_para);
			}

			ret = fill_extend_data_in_dts(dn, str_comp, mag_data.compass_extend_data, SENSOR_PLATFORM_EXTEND_DATA_SIZE, EXTEND_DATA_TYPE_IN_DTS_WORD);
			if (ret) {
				hwlog_err("%s:fill_extend_data_in_dts failed!\n", str_comp);
			}

			if (true == is_invensense_dmp_exist) {//finished getting mag dev from dts, then recovery, not bypass
				ret = invense_ICM_20628_close_bypass_for_detect(mag_i2c_bus_id);
				if (ret < 0) {
				    hwlog_err("close bypass failed!\n");
				}
			}
			mag_flag = DET_SUCC;
			strncpy(buf[MAG], "MAG detect succ", sizeof(buf[MAG]));
		}else if(!strncmp(sensor_ty, "gyro", sizeof("gyro")))
		{
			if(gyro_flag == DET_SUCC) continue;
			if(detect_i2c_device(dn, "gyro")){
				gyro_flag = DET_FAIL;
				strncpy(buf[GYRO], "GYRO detect fail", sizeof(buf[GYRO]));
				continue;
			}
			gyro_flag = DET_SUCC;
			strncpy(buf[GYRO], "GYRO detect succ", sizeof(buf[GYRO]));

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			/* detect current device successful, set the flag as present */
			set_hw_dev_flag(DEV_I2C_GYROSCOPE);
#endif
			ret = of_property_read_string(dn, "compatible", (const char **)&chip_info);
			if(ret) hwlog_err("%s:read gyro poll_interval fail\n", __func__);
			else strncpy(sensor_chip_info[GYRO], chip_info, strlen(chip_info));
			hwlog_info("get gyro dev from dts.sensor name=%s\n", chip_info);

			ret=of_property_read_u32(dn, "poll_interval", &poll_val);
			if(ret) hwlog_err("%s:read mag poll_interval fail\n",__func__);
			else gyro_data.poll_interval=(uint16_t)poll_val;

			ret=of_property_read_u32(dn, "axis_map_x", &temp);
			if(ret) hwlog_err("%s:read gyro axis_map_x fail\n",__func__);
			else gyro_data.axis_map_x=(uint8_t)temp;

			ret=of_property_read_u32(dn, "axis_map_y", &temp);
			if(ret) hwlog_err("%s:read gyro axis_map_y fail\n",__func__);
			else gyro_data.axis_map_y=(uint8_t)temp;

			ret=of_property_read_u32(dn, "axis_map_z", &temp);
			if(ret) hwlog_err("%s:read gyro axis_map_z fail\n",__func__);
			else gyro_data.axis_map_z=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_x", &temp);
			if(ret) hwlog_err("%s:read gyro negate_x fail\n",__func__);
			else gyro_data.negate_x=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_y", &temp);
			if(ret) hwlog_err("%s:read gyro negate_y fail\n",__func__);
			else gyro_data.negate_y=(uint8_t)temp;

			ret=of_property_read_u32(dn, "negate_z", &temp);
			if(ret) hwlog_err("%s:read gyro negate_z fail\n",__func__);
			else gyro_data.negate_z=(uint8_t)temp;

			ret = of_property_read_u32(dn, "file_id", &temp);
			if(ret) hwlog_err("%s:read gyro file_id fail\n", __func__);
			else dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
			dyn_req->file_count++;
			ret = of_property_read_u32(dn, "sensor_list_info_id", &temp);
			if(ret) hwlog_err("%s:read gyro sensor_list_info_id fail\n", __func__);
			else sensorlist[++sensorlist[0]] = (uint16_t)temp;

			gpio_irq = of_get_named_gpio(dn, "gpio_int1", 0);
			if(gpio_irq) gyro_data.gpio_int1 = (uint8_t)gpio_irq;
		}
		else if(!strncmp(sensor_ty, "als", sizeof("als")))
		{
			if(als_flag == DET_SUCC) continue;
			if(detect_i2c_device(dn, "als")){
				als_flag = DET_FAIL;
				strncpy(buf[ALS], "ALS detect fail", sizeof(buf[ALS]));
				continue;
			}
			als_flag = DET_SUCC;
			strncpy(buf[ALS], "ALS detect succ", sizeof(buf[ALS]));

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_L_SENSOR);
#endif
			ret = of_property_read_string(dn, "compatible", (const char **)&chip_info);
			if(ret) hwlog_err("%s:read als poll_interval fail\n", __func__);
			else strncpy(sensor_chip_info[ALS], chip_info, strlen(chip_info));
			hwlog_info("get als dev from dts.sensor name=%s\n", chip_info);

			ret=of_property_read_u32(dn, "poll_interval", &poll_val);
			if(ret) hwlog_err("%s:read als poll_interval fail\n",__func__);
			else als_data.poll_interval=(uint16_t)poll_val;

			ret=of_property_read_u32(dn, "init_time", &temp);
			if(ret) hwlog_err("%s:read als init time fail\n",__func__);
			else als_data.init_time=(uint16_t)temp;

			gpio_irq=of_get_named_gpio(dn, "gpio_int1", 0);
			if(gpio_irq) als_data.gpio_int1=(uint8_t)gpio_irq;

			ret=of_property_read_u32(dn, "GA1", &ga);
			if(ret) hwlog_err("%s:read als ga1 fail\n",__func__);
			else als_data.GA1=ga;

			ret=of_property_read_u32(dn, "GA2", &ga);
			if(ret) hwlog_err("%s:read als ga2 fail\n",__func__);
			else als_data.GA2=ga;

			ret=of_property_read_u32(dn, "GA3", &ga);
			if(ret) hwlog_err("%s:read als ga3 fail\n",__func__);
			else als_data.GA3=ga;

			ret=of_property_read_u32(dn, "COE_B", &ga);
			if(ret) hwlog_err("%s:read als COE_B fail\n",__func__);
			else als_data.COE_B=ga;

			ret=of_property_read_u32(dn, "COE_C", &ga);
			if(ret) hwlog_err("%s:read als COE_C fail\n",__func__);
			else als_data.COE_C=ga;

			ret=of_property_read_u32(dn, "COE_D", &ga);
			if(ret) hwlog_err("%s:read als COE_D fail\n",__func__);
			else als_data.COE_D=ga;

			ret=of_property_read_u32(dn, "atime", &atime);
			if(ret) hwlog_err("%s:read als atime fail\n",__func__);
			else als_data.atime=(uint8_t)atime;

			ret=of_property_read_u32(dn, "again", &again);
			if(ret) hwlog_err("%s:read als again fail\n",__func__);
			else als_data.again=(uint8_t)again;

			ret = of_property_read_u32(dn, "file_id", &temp);
			if(ret) hwlog_err("%s:read als file_id fail\n", __func__);
			else dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
			dyn_req->file_count++;
			ret = of_property_read_u32(dn, "sensor_list_info_id", &temp);
			if(ret) hwlog_err("%s:read als sensor_list_info_id fail\n", __func__);
			else sensorlist[++sensorlist[0]] = (uint16_t)temp;
			ret = fill_extend_data_in_dts(dn, "als_extend_data", als_data.als_extend_data, 12, EXTEND_DATA_TYPE_IN_DTS_HALF_WORD);
			if (ret) {
				hwlog_err("als_extend_data:fill_extend_data_in_dts failed!\n");
			}

		}
		else if(!strncmp(sensor_ty, "ps", sizeof("ps")))
		{
			if(ps_flag == DET_SUCC) continue;
			if(detect_i2c_device(dn, "ps")){
				ps_flag = DET_FAIL;
				strncpy(buf[PS], "PS detect fail", sizeof(buf[PS]));
				continue;
			}
			ps_flag = DET_SUCC;
			strncpy(buf[PS], "PS detect succ", sizeof(buf[PS]));

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_L_SENSOR);
#endif
			ret = of_property_read_string(dn, "compatible", (const char **)&chip_info);
			if(ret) hwlog_err("%s:read ps poll_interval fail\n", __func__);
			else strncpy(sensor_chip_info[PS], chip_info, strlen(chip_info));
			hwlog_info("get ps dev from dts.sensor name=%s\n", chip_info);

			ret=of_property_read_u32(dn, "min_proximity_value", &temp);
			if(ret) hwlog_err("%s:read mag min_proximity_value fail\n",__func__);
			else ps_data.min_proximity_value=temp;

			gpio_irq=of_get_named_gpio(dn, "gpio_int1", 0);
			if(gpio_irq) ps_data.gpio_int1=(uint8_t)gpio_irq;

			ret=of_property_read_u32(dn, "pwindows_value", &temp);
			if(ret) hwlog_err("%s:read pwindows_value fail\n",__func__);
			else ps_data.pwindows_value=temp;

			ret=of_property_read_u32(dn, "pwave_value", &temp);
			if(ret) hwlog_err("%s:read pwave_value fail\n",__func__);
			else ps_data.pwave_value=temp;

			ret=of_property_read_u32(dn, "threshold_value", &temp);
			if(ret) hwlog_err("%s:read threshold_value fail\n",__func__);
			else ps_data.threshold_value=temp;

			ret=of_property_read_u32(dn, "rdata_under_sun", &temp);
			if(ret) hwlog_err("%s:read rdata_under_sun fail\n",__func__);
			else ps_data.rdata_under_sun=temp;

			ret=of_property_read_u32(dn, "ps_pulse_count", &temp);
			if(ret) hwlog_err("%s:read ps_pulse_count fail\n",__func__);
			else ps_data.ps_pulse_count=(uint8_t)temp;

			ret=of_property_read_u32(dn, "persistent", &temp);
			if(ret) hwlog_err("%s:read persistent fail\n",__func__);
			else ps_data.persistent=(uint8_t)temp;

			ret=of_property_read_u32(dn, "ptime", &temp);
			if(ret) hwlog_err("%s:read ptime fail\n",__func__);
			else ps_data.ptime=(uint8_t)temp;

			ret=of_property_read_u32(dn, "p_on", &temp);
			if(ret) hwlog_err("%s:read p_on fail\n",__func__);
			else ps_data.p_on=(uint8_t)temp;
			ret=of_property_read_u32(dn, "poll_interval", &temp);
			if(ret) hwlog_err("%s:read poll_interval fail\n",__func__);
			else ps_data.poll_interval=(uint16_t)temp;
			ret=of_property_read_u32(dn, "init_time", &temp);
			if(ret) hwlog_err("%s:read init_time fail\n",__func__);
			else ps_data.init_time=(uint16_t)temp;

			ret = of_property_read_u32(dn, "file_id", &temp);
			if(ret) hwlog_err("%s:read ps file_id fail\n", __func__);
			else dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
			dyn_req->file_count++;

			ret = of_property_read_u32(dn, "sensor_list_info_id", &temp);
			if(ret) hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
			else sensorlist[++sensorlist[0]] = (uint16_t)temp;

		}
		else if(!strncmp(sensor_ty, "airpress", sizeof("airpress")))
		{
			if(airpress_flag == DET_SUCC) continue;
			if(detect_i2c_device(dn, "airpress")){
				airpress_flag = DET_FAIL;
				strncpy(buf[AIRPRESS], "AIRPRESS detect fail", sizeof(buf[AIRPRESS]));
				continue;
			}
			airpress_flag = DET_SUCC;
			strncpy(buf[AIRPRESS], "AIRPRESS detect succ", sizeof(buf[AIRPRESS]));

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_AIRPRESS);
#endif
			ret = of_property_read_string(dn, "compatible", (const char **)&chip_info);
			if(ret) hwlog_err("%s:read airpress compatible fail\n", __func__);
			else strncpy(sensor_chip_info[AIRPRESS], chip_info, strlen(chip_info));
			hwlog_info("get airpress dev from dts.sensor name=%s\n", chip_info);

			ret=of_property_read_u32(dn, "poll_interval", &temp);
			if(ret) hwlog_err("%s:read poll_interval fail\n",__func__);
			else airpress_data.poll_interval=(uint16_t)temp;

			ret = of_property_read_u32(dn, "file_id", &temp);
			if(ret) hwlog_err("%s:read airpress file_id fail\n", __func__);
			else dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
			dyn_req->file_count++;

			ret = of_property_read_u32(dn, "sensor_list_info_id", &temp);
			if(ret) hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
			else sensorlist[++sensorlist[0]] = (uint16_t)temp;

		}
		else if(!strncmp(sensor_ty, "handpress", sizeof("handpress")))
		{
			if(hand_flag == DET_SUCC) continue;
			if(handpress_sensor_detect(dn, &handpress_data)){
				hand_flag = DET_FAIL;
				strncpy(buf[HANDPRESS], "HANDPRESS detect fail", sizeof(buf[HANDPRESS]));
				continue;
			}
			iom3_timeout = 20000;
			hand_flag = DET_SUCC;
			strncpy(buf[HANDPRESS], "HANDPRESS detect succ", sizeof(buf[HANDPRESS]));

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
			set_hw_dev_flag(DEV_I2C_HANDPRESS);
#endif
			ret = of_property_read_string(dn, "compatible", (const char **)&chip_info);
			if(ret) hwlog_err("%s:read handpress compatible fail\n", __func__);
			else strncpy(sensor_chip_info[HANDPRESS], chip_info, strlen(chip_info));
			hwlog_info("get handpress dev from dts.sensor name=%s\n", chip_info);

			ret=of_property_read_u32(dn, "poll_interval", &temp);
			if(ret) hwlog_err("%s:read poll_interval fail\n",__func__);
			else handpress_data.poll_interval=(uint16_t)temp;
			hwlog_info("get handpress dev from dts.sensor name=%d\n", airpress_data.poll_interval);
			
			ret = of_property_read_u32(dn, "file_id", &temp);
			if(ret) hwlog_err("%s:read handpress file_id fail\n", __func__);
			else dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
			dyn_req->file_count++;
			hwlog_info("get handpress dev from dyn_req->file_count=%d\n", dyn_req->file_count);
// + file_ID  FW FILE_ID 0x16
			ret = of_property_read_u32(dn, "file_id_fw", &temp);
			if(ret) hwlog_err("%s:read handpress file_id_fw fail\n", __func__);
			else dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
			dyn_req->file_count++;
			hwlog_info("get handpress dev from dyn_req->file_count=%d\n", dyn_req->file_count);

			ret = of_property_read_u32(dn, "sensor_list_info_id", &temp);
			if(ret) hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
			else sensorlist[++sensorlist[0]] = (uint16_t)temp;
			hwlog_info("get handpress dev from temp=%d; ++sensorlist[0]:%d\n", temp, sensorlist[0]-1);

		}
		else if(!strncmp(sensor_ty, "cap_prox", sizeof("cap_prox")))
		{
			if(cap_prox_flag == DET_SUCC) continue;
			if(detect_i2c_device(dn, "cap_prox")){
				cap_prox_flag = DET_FAIL;
				strncpy(buf[CAP_PROX], "CAP_PROX detect fail", sizeof(buf[CAP_PROX]));
				continue;
			}
			cap_prox_flag = DET_SUCC;
			strncpy(buf[CAP_PROX], "CAP_PROX detect succ", sizeof(buf[CAP_PROX]));

//#ifdef CONFIG_HUAWEI_HW_DEV_DCT
//			set_hw_dev_flag(DEV_I2C_CAP_PROX);
//#endif
			ret = of_property_read_string(dn, "compatible", (const char **)&chip_info);
			if(ret) hwlog_err("%s:read cap_prox poll_interval fail\n", __func__);
			else strncpy(sensor_chip_info[CAP_PROX], chip_info, strlen(chip_info));
			hwlog_info("get cap_prox dev from dts.sensor name=%s\n", chip_info);

			gpio_irq=of_get_named_gpio(dn, "gpio_int", 0);
			if(gpio_irq) cap_prox_data.gpio_int=(uint8_t)gpio_irq;

			ret=of_property_read_u32_array(dn, "init_reg_val", cap_prox_data.init_reg_val, 17);
			if(ret) hwlog_err("%s:read init_reg_val fail\n",__func__);

			ret=of_property_read_u32(dn, "poll_interval", &temp);
			if(ret) hwlog_err("%s:read poll_interval fail\n",__func__);
			else cap_prox_data.poll_interval = (uint16_t)temp;
			hwlog_info("cap_prox_data.poll_interval: %d\n", cap_prox_data.poll_interval);

			ret = of_property_read_u32(dn, "file_id", &temp);
			if(ret) hwlog_err("%s:read cap_prox file_id fail\n", __func__);
			else dyn_req->file_list[dyn_req->file_count] = (uint16_t)temp;
			dyn_req->file_count++;

			ret = of_property_read_u32(dn, "sensor_list_info_id", &temp);
			if(ret) hwlog_err("%s:read cap_prox sensor_list_info_id fail\n", __func__);
			else sensorlist[++sensorlist[0]] = (uint16_t)temp;
		}
	}

	if(acc_flag == DET_FAIL ||mag_flag == DET_FAIL ||gyro_flag == DET_FAIL
		||als_flag == DET_FAIL ||ps_flag == DET_FAIL ||airpress_flag == DET_FAIL
		|| hand_flag == DET_FAIL || cap_prox_flag == DET_FAIL){

		snprintf(detect_result,MAX_STR_SIZE,"%s,%s,%s,%s,%s,%s,%s,%s\n",buf[ACC],buf[MAG],
			buf[GYRO],buf[ALS],buf[PS],buf[AIRPRESS],buf[HANDPRESS],buf[CAP_PROX]);
		hwlog_err("detect_result: %s\n",detect_result);
		dmd_log_report(DSM_SHB_ERR_DYNLOAD, __func__, detect_result);
	}

	ret = get_adapt_file_id_for_dyn_load();
	if (ret < 0) {
		hwlog_err("get_adapt_file_id_for_dyn_load() failed!\n");
    }
	hwlog_info("get file id number = %d\n", dyn_req->file_count);
	ret = get_adapt_sensor_list_id();
	if (ret < 0) {
		hwlog_err("get_adapt_sensor_list_id() failed!\n");
	}
	sensorlist[0] = check_file_list(sensorlist[0], &sensorlist[1]);
	if (sensorlist[0] > 0)
	{
		printk("sensorhub after check, get sensor list id number = %d, list id: ", sensorlist[0]);
		for (i = 0; i < sensorlist[0]; i++) {
			printk("--%d", sensorlist[i+1]);
		}
		printk("\n");
	}
	else
	{
		hwlog_err("%s list num = 0, not send file_id to muc\n", __func__);
		return -EINVAL;
	}

	dyn_req->file_count = check_file_list(dyn_req->file_count, dyn_req->file_list);
	if (dyn_req->file_count)
	{
		printk("sensorhub after check, get dynload file id number = %d, fild id", dyn_req->file_count);
		for (i = 0; i < dyn_req->file_count; i++) {
			printk("--%d", dyn_req->file_list[i]);
		}
		printk("\n");
		return send_fileid_to_mcu();
	}
	else
	{
		hwlog_err("%s file_count = 0, not send file_id to muc\n", __func__);
		return -EINVAL;
	}
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

static int sensor_set_current_info_in_recovery(void)
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
//>>>ret = write_customize_cmd(&pkg_ap,  NULL);
	ret = write_customize_cmd_noresp(TAG_CURRENT, CMD_CURRENT_CFG_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
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

int sensor_set_cfg_data_in_recovery(void)
{
	int ret = 0;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));

	ret = sensor_set_current_info_in_recovery();
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
		//>>>ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		ret = write_customize_cmd_noresp(TAG_ACCEL, CMD_ACCEL_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
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
	//>>>ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		ret = write_customize_cmd_noresp(TAG_GYRO, CMD_GYRO_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
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
	//>>>ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		ret = write_customize_cmd_noresp(TAG_MAG, CMD_MAG_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
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
			}
		}
	}

	//als
	if(strlen(sensor_chip_info[ALS]) != 0)
	{
		pkg_ap.tag=TAG_ALS;
		pkg_ap.cmd=CMD_ALS_PARAMET_REQ;
		pkg_ap.wr_buf=&als_data;
		pkg_ap.wr_len=sizeof(als_data);
	//>>>ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		ret = write_customize_cmd_noresp(TAG_ALS, CMD_ALS_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
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
	//>>>ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		ret = write_customize_cmd_noresp(TAG_PS, CMD_PS_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
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
			}
		}
	}

	//cap_prox
	if(strlen(sensor_chip_info[CAP_PROX]) != 0)
	{
		pkg_ap.tag=TAG_CAP_PROX;
		pkg_ap.cmd=CMD_CAP_PROX_PARAMET_REQ;
		pkg_ap.wr_buf=&cap_prox_data;
		pkg_ap.wr_len=sizeof(cap_prox_data);
	//>>>ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
		ret = write_customize_cmd_noresp(TAG_CAP_PROX, CMD_CAP_PROX_PARAMET_REQ, pkg_ap.wr_buf, pkg_ap.wr_len);
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
			}
		}
	}
	return ret;
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

static int sensor_set_cfg_data(void)
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
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
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
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
				/* detect current device successful, set the flag as present */
				set_hw_dev_flag(DEV_I2C_G_SENSOR);
#endif
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
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
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
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
				/* detect current device successful, set the flag as present */
				set_hw_dev_flag(DEV_I2C_GYROSCOPE);
#endif
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
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
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
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
				/* detect current device successful, set the flag as present */
				set_hw_dev_flag(DEV_I2C_COMPASS);
#endif
			}
		}
		register_mcu_event_notifier(TAG_MAG, CMD_MAG_SEND_CALIBRATE_TO_AP_REQ, mag_calibrate_data_from_mcu);
	}

	//als
	if(strlen(sensor_chip_info[ALS]) != 0)
	{
		pkg_ap.tag=TAG_ALS;
		pkg_ap.cmd=CMD_ALS_PARAMET_REQ;
		pkg_ap.wr_buf=&als_data;
		pkg_ap.wr_len=sizeof(als_data);
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
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
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
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
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
				/* detect current device successful, set the flag as present */
				set_hw_dev_flag(DEV_I2C_L_SENSOR);
#endif
			}
		}
	}

	//airpress
	if(strlen(sensor_chip_info[AIRPRESS]) != 0)
	{
		pkg_ap.tag=TAG_AIRPRESS;
		pkg_ap.cmd=CMD_AIRPRESS_PARAMET_REQ;
		pkg_ap.wr_buf=&airpress_data;
		pkg_ap.wr_len=sizeof(airpress_data);
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
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
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
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
		ret=write_customize_cmd(&pkg_ap,  &pkg_mcu);
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
	#ifdef CONFIG_HUAWEI_HW_DEV_DCT
				/* detect current device successful, set the flag as present */
				set_hw_dev_flag(DEV_I2C_L_SENSOR);
	#endif
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
		printk( " %d  ", sensorlist[i]);
	printk("\n");
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

SENSOR_SHOE_INFO(HANDPRESS);
static DEVICE_ATTR(handpress_info, S_IRUGO, sensor_show_HANDPRESS_info, NULL);

SENSOR_SHOE_INFO(CAP_PROX);
static DEVICE_ATTR(cap_prox_info, S_IRUGO, sensor_show_CAP_PROX_info, NULL);

unsigned int sensor_read_number[TAG_END] = {0,0,0,0,0};

#define SENSOR_SHOW_VALUE(TAG) \
static ssize_t sensor_show_##TAG##_read_data(struct device *dev, \
				struct device_attribute *attr, char *buf) \
{\
	printk("[sensorhub_test], %s return %d\n", __func__, sensor_read_number[TAG]);\
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

SENSOR_SHOW_VALUE(TAG_AIRPRESS);
static DEVICE_ATTR(airpress_read_data, 0664, sensor_show_TAG_AIRPRESS_read_data, NULL);

SENSOR_SHOW_VALUE(TAG_HANDPRESS);
static DEVICE_ATTR(handpress_read_data, 0664, sensor_show_TAG_HANDPRESS_read_data, NULL);

SENSOR_SHOW_VALUE(TAG_CAP_PROX);
static DEVICE_ATTR(cap_prox_read_data, 0664, sensor_show_TAG_CAP_PROX_read_data, NULL);

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
	char temp_buf[10] = {0};
	int ret=0;
	if(buf == NULL||length <= 0)
	{
		hwlog_err("%s invalid argument.", __func__);
		return_calibration=EXEC_FAIL;
		return -1;
	}
	memcpy(temp_buf, buf, length);
	hwlog_info( "%s:gsensor calibrate ok, %d  %d  %d \n", __func__, temp_buf[0],temp_buf[1],temp_buf[2]);
	ret = write_gsensor_offset_to_nv(temp_buf);
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
	int ret = 0;
	write_info_t	pkg_ap;
	read_info_t	pkg_mcu;

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;
	if(1==val)
	{
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
	}
	return count;
}

static DEVICE_ATTR(acc_calibrate, 0664, attr_acc_calibrate_show, attr_acc_calibrate_write);

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
static DEVICE_ATTR(cap_prox_calibrate, 0664, attr_cap_prox_calibrate_show, attr_cap_prox_calibrate_write);

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
static DEVICE_ATTR(cap_prox_freespace, 0664, attr_cap_prox_freespace_show, attr_cap_prox_freespace_write);

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

SHOW_ENABLE_FUNC(airpress, TAG_AIRPRESS)
STORE_ENABLE_FUNC(airpress, TAG_AIRPRESS, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(airpress_enable, 0664, show_airpress_enable_result, attr_set_airpress_enable);
SHOW_DELAY_FUNC(airpress, TAG_AIRPRESS)
STORE_DELAY_FUNC(airpress, TAG_AIRPRESS, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(airpress_setdelay, 0664, show_airpress_delay_result, attr_set_airpress_delay);

SHOW_ENABLE_FUNC(handpress, TAG_HANDPRESS)
STORE_ENABLE_FUNC(handpress, TAG_HANDPRESS, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(handpress_enable, 0664, show_handpress_enable_result, attr_set_handpress_enable);
SHOW_DELAY_FUNC(handpress, TAG_HANDPRESS)
STORE_DELAY_FUNC(handpress, TAG_HANDPRESS, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(handpress_setdelay, 0664, show_handpress_delay_result, attr_set_handpress_delay);

SHOW_ENABLE_FUNC(cap_prox, TAG_CAP_PROX)
STORE_ENABLE_FUNC(cap_prox, TAG_CAP_PROX, CMD_CMN_OPEN_REQ, CMD_CMN_CLOSE_REQ)
static DEVICE_ATTR(cap_prox_enable, 0664, show_cap_prox_enable_result, attr_set_cap_prox_enable);
SHOW_DELAY_FUNC(cap_prox, TAG_CAP_PROX)
STORE_DELAY_FUNC(cap_prox, TAG_CAP_PROX, CMD_CMN_INTERVAL_REQ)
static DEVICE_ATTR(cap_prox_setdelay, 0664, show_cap_prox_delay_result, attr_set_cap_prox_delay);

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
	hisi_system_error(HISI_RDR_MOD_IOM3_NORMAL, 0, 0, NULL, 0);
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
		inputhub_route_write(ROUTE_SHB_PORT, (char *)&event, 16);
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

	inputhub_route_write(ROUTE_SHB_PORT, (char *)&event, 16);
	return size;
}
static DEVICE_ATTR(dt_stepcounter_stup, 0664, NULL, attr_set_sensor_stepcounter_stup);

static ssize_t show_iom3_sr_status(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, MAX_STR_SIZE, "%s\n", (iom3_sr_status == ST_SLEEP)?"ST_SLEEP":"ST_WAKEUP");
}
static DEVICE_ATTR(iom3_sr_status, 0664, show_iom3_sr_status, NULL);


static ssize_t show_sensor_read_airpress(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, MAX_STR_SIZE, "%d\n", get_airpress_data);
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
	int ret = 0;
	hwlog_info("-------------------------------------\n");
	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		if(unlikely((tag == TAG_PS)||(tag == TAG_STEP_COUNTER))){/*ps and step counter need always on, just skip*/
			continue;
		}
		hwlog_info(" %s\t %s\t %d\n", obj_tag_str[tag], sensor_status.opened[tag]?"open":"close", sensor_status.delay[tag]);
	}
	hwlog_info("-------------------------------------\n");
	return snprintf(buf, MAX_STR_SIZE, "please check log\n", get_temperature_data);
}
static DEVICE_ATTR(dump_sensor_status, 0664, show_dump_sensor_status, NULL);

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
	&dev_attr_gyro_enable.attr,
	&dev_attr_gyro_setdelay.attr,
	&dev_attr_mag_enable.attr,
	&dev_attr_mag_setdelay.attr,
	&dev_attr_als_enable.attr,
	&dev_attr_als_setdelay.attr,
	&dev_attr_ps_enable.attr,
	&dev_attr_ps_setdelay.attr,
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
	&dev_attr_read_airpress.attr,
	&dev_attr_read_temperature.attr,
	&dev_attr_dt_stepcounter_stup.attr,
	&dev_attr_handpress_info.attr,
	&dev_attr_handpress_enable.attr,
	&dev_attr_handpress_setdelay.attr,
	&dev_attr_handpress_read_data.attr,
	&dev_attr_iom3_sr_status.attr,
	&dev_attr_cap_prox_info.attr,
	&dev_attr_cap_prox_read_data.attr,
	&dev_attr_cap_prox_calibrate.attr,
	&dev_attr_cap_prox_freespace.attr,
	&dev_attr_cap_prox_enable.attr,
	&dev_attr_cap_prox_setdelay.attr,
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

extern atomic_t iom3_rec_state;
int mcu_sys_ready_callback(const pkt_header_t *head)
{
	int ret = 0;
	if (ST_MINSYSREADY == ((pkt_sys_statuschange_req_t *)head)->status)
	{
		hwlog_info("sys ready mini!\n");
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

struct platform_driver sensorhub_io_driver = {
         .probe = sensorhub_io_driver_probe,
         .driver = {
                         .name = "Sensorhub_io_driver",
                         .owner = THIS_MODULE,
                         .of_match_table = of_match_ptr(sensorhub_io_supply_ids),
         },
};

static int __init sensor_input_info_init(void)
{
	int ret = 0;
	hwlog_info("[%s] ++", __func__);

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

fs_initcall(sensorhub_io_driver_init);
device_initcall(sensor_input_info_init);
MODULE_DESCRIPTION("sensor input info");
MODULE_AUTHOR("huawei driver group of K3V3");
MODULE_LICENSE("GPL");
