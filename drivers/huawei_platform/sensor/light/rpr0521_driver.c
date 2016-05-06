/* drivers/i2c/chips/rpr521_driver.c - ROHM RPR521 Linux kernel driver
 *
 * Copyright (C) 2012 
 * Written by Andy Mi <andy-mi@rohm.com.cn>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include <linux/debugfs.h>
#include <linux/irq.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/input.h>
#include <linux/wakelock.h>
#include "rpr0521_driver.h"
#include <linux/regulator/consumer.h>
#include <linux/of_gpio.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/board_sensors.h>
#include <huawei_platform/sensor/sensor_info.h>

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#if defined(CONFIG_FB)
#include <linux/notifier.h>
#include <linux/fb.h>
#endif
/*************** Global Data ******************/
/* parameter for als calculation */
#define COEFFICIENT               (4)
#define RPR0521_I2C_RETRY_COUNT		3 	/* Number of times to retry i2c */ 
#define RPR0521_I2C_RETRY_TIMEOUT	1	/* Timeout between retry (miliseconds) */

#define     RPR0521_I2C_BYTE   0
#define     RPR0521_I2C_WORD   1
#define 	RPR_FAR_THRESHOLD(x)		(rpr0521_min_proximity_value<(x)?(x):rpr0521_min_proximity_value)
#define 	RPR_NEAR_THRESHOLD(x)		((RPR_FAR_THRESHOLD(x) + rpr0521_pwindows_value)>0xFFF?0xFFF:(RPR_FAR_THRESHOLD(x) + rpr0521_pwindows_value))
//const unsigned long data0_coefficient[COEFFICIENT] = {192, 141, 127, 117};
//const unsigned long data1_coefficient[COEFFICIENT] = {316, 108,  86,  74};
//const unsigned long judge_coefficient[COEFFICIENT] = { 29,  65,  85, 158}; 
const unsigned long data0_coefficient[COEFFICIENT] = {9290,7711,2079,1810};
const unsigned long data1_coefficient[COEFFICIENT] = {5303,4367,685,580};
const unsigned long judge_coefficient[COEFFICIENT] = {1000,1422,1700,3100}; 
const unsigned int g_luxsection[MAX_SECTION] = {10, 255, 320, 640, 1280, 2600,10000};
static unsigned int luxsection = MAX_SECTION;  //make luxsection= 7 to print the luxvalue on first enable ALS
static unsigned int lastluxvalue = 0;

static int rdtp_fail_times = 0;
static char tp_name[10] = "no_name";
#define  READ_TP_SUCCESS   3

//for lensone tp on CHM
const unsigned long data0_lensone_CHM[COEFFICIENT] = {10843,9754,3779,1810};
const unsigned long data1_lensone_CHM[COEFFICIENT] = {6417,5571,1629,580};
const unsigned long judge_lensone_CHM[COEFFICIENT] = {1000,1520,2300,3100};

//for oflim tp on CHM
const unsigned long data0_oflim_CHM[COEFFICIENT] = {9033,4222,2776,1810};
const unsigned long data1_oflim_CHM[COEFFICIENT] = {6342,2140,1194,580};
const unsigned long judge_oflim_CHM[COEFFICIENT] = {900,1340,2333,3100};
//for truly tp on CHM
const unsigned long data0_truly_CHM[COEFFICIENT] = {7562,3766,2756,1810};
const unsigned long data1_truly_CHM[COEFFICIENT] = {5220,1926,1232,580};
const unsigned long judge_truly_CHM[COEFFICIENT] = {900,1350,2416,3100};

//for junda tp on ALE
const unsigned long data0_junda_ALE[COEFFICIENT] = {8507,5473,3142,1810};
const unsigned long data1_junda_ALE[COEFFICIENT] = {5037,2771,1317,580};
const unsigned long judge_junda_ALE[COEFFICIENT] = {1000,1472,1750,3100};

//for oflim tp on ALE
const unsigned long data0_oflim_ALE[COEFFICIENT] = {8996,6149,2525,1810};
const unsigned long data1_oflim_ALE[COEFFICIENT] = {5647,3420,1098,580};
const unsigned long judge_oflim_ALE[COEFFICIENT] = {1100,1500,1700,3100};

//for truly tp on ALE
const unsigned long data0_truly_ALE[COEFFICIENT] = {7820,5404,2882,1810};
const unsigned long data1_truly_ALE[COEFFICIENT] = {4508,2768,1174,580};
const unsigned long judge_truly_ALE[COEFFICIENT] = {1100,1510,1700,3100};

static int rpr0521_min_proximity_value=3000;
static int rpr0521_pwindows_value =100;
static int rpr0521_pwave_value = 200;
static unsigned int rpr_threshold_value = 0;
static unsigned int apds_type = 0;
static struct wake_lock ps_wlock;
static int loop = 10;
#if defined (CONFIG_HUAWEI_DSM)
#include <linux/mfd/hisi_hi6xxx_pmic.h>
#include <dsm/dsm_pub.h>
extern struct dsm_client *als_ps_dclient;
static int rp0521_als_ps_init_flag=0;
#endif
#define _AUTO_THRESHOLD_CHANGE_

extern bool power_key_ps ;
extern int als_data_count;
extern int ps_data_count;
extern bool DT_tset;
/* mode control table */
#define MODE_CTL_FACTOR (16)
static const struct MCTL_TABLE {
    short ALS;
    short PS;
} mode_table[MODE_CTL_FACTOR] = {
    {  0,   0},   /*  0 */
    {  0,  10},   /*  1 */
    {  0,  40},   /*  2 */
    {  0, 100},   /*  3 */
    {  0, 400},   /*  4 */
    {100,  50},   /*  5 */
    {100, 100},   /*  6 */
    {100, 400},   /*  7 */
    {400,   0},   /*  8 */
    {400, 100},   /*  9 */
    {400,   0},   /* 10 */
    {400, 400},   /* 11 */
    {  50,  50},   /* 12 */
    {  0,   0},   /* 13 */
    {  0,   0},   /* 14 */
    {  0,   0}    /* 15 */
};

/* gain table */
#define GAIN_FACTOR (16)
static const struct GAIN_TABLE {
    /*char DATA0;
    char DATA1;*/
    unsigned char DATA0;
    unsigned char DATA1;
} gain_table[GAIN_FACTOR] = {
    {  1,   1},   /*  0 */
    {  0,   0},   /*  1 */
    {  0,   0},   /*  2 */
    {  0,   0},   /*  3 */
    {  2,   1},   /*  4 */
    {  2,   2},   /*  5 */
    {  0,   0},   /*  6 */
    {  0,   0},   /*  7 */
    {  0,   0},   /*  8 */
    {  0,   0},   /*  9 */
    { 64,  64},   /* 10 */
    {  0,   0},   /* 11 */
    {  0,   0},   /* 12 */
    {  0,   0},   /* 13 */
    {128,  64},   /* 14 */
    {128, 128}    /* 15 */
};
static struct sensors_classdev rohm_als_cdev = {
       .path_name="als_sensor",
	.name = "Light sensor",
	.vendor = "ROHM_RPR521",
	.version = 1,
	.handle = SENSORS_LIGHT_HANDLE,
	.type = SENSOR_TYPE_LIGHT,
	.max_range = "10000",
	.resolution = "0.0125",
	.sensor_power = "0.75",
	.min_delay = 0,
	.delay_msec = 200,
	.fifo_reserved_event_count = 0,
	.fifo_max_event_count = 0,
	.enabled = 0,
	.sensors_enable = NULL,
	.sensors_poll_delay = NULL,
};
static struct sensors_classdev rohm_ps_cdev = {
       .path_name="ps_sensor",
	.name = "Proximity sensor",
	.vendor = "ROHM_RPR521",
	.version = 1,
	.handle = SENSORS_PROXIMITY_HANDLE,
	.type = SENSOR_TYPE_PROXIMITY,
	.max_range = "5",
	.resolution = "5",
	.sensor_power = "0.75",
	.min_delay = 0,
	.delay_msec = 200,
	.fifo_reserved_event_count = 0,
	.fifo_max_event_count = 0,
	.enabled = 0,
	.sensors_enable = NULL,
	.sensors_poll_delay = NULL,
};
static int rpr521_init_client(struct i2c_client *client);


static int Rpr0521_i2c_write(struct i2c_client*client, u8 reg, u16 value,bool flag)
{
	int err,loop;

	struct ALS_PS_DATA *data = i2c_get_clientdata(client);

	loop = RPR0521_I2C_RETRY_COUNT;
	/*we give three times to repeat the i2c operation if i2c errors happen*/
	while(loop) {
		mutex_lock(&data->i2c_update_lock);
		/*0 is i2c_smbus_write_byte_data,1 is i2c_smbus_write_word_data*/
		if(flag == RPR0521_I2C_BYTE)
		{
			//err = i2c_smbus_write_byte_data(client, CMD_BYTE|reg, (u8)value);
			err = i2c_smbus_write_byte_data(client, reg, (u8)value);
		}
		else if(flag == RPR0521_I2C_WORD)
		{
			//err = i2c_smbus_write_word_data(client, CMD_WORD|reg, value);
			err = i2c_smbus_write_word_data(client, reg, value);
		}
		else
		{
			als_ps_INFO("[ALS_PS]%s,line %d:attention: i2c write wrong flag",__func__,__LINE__);
			mutex_unlock(&data->i2c_update_lock);
			return -EINVAL;
		}
		mutex_unlock(&data->i2c_update_lock);
		if(err < 0){
			loop--;
			mdelay(1);
		}
		else
			break;
	}
	/*after three times,we print the register and regulator value*/
	
	if(loop == 0){
		als_ps_INFO("[ALS_PS]%s,line %d:attention: i2c read err = %d,reg=0x%x",__func__,__LINE__,err,reg);
	}
	return err;
}

static int Rpr0521_i2c_read(struct i2c_client*client, u8 reg,bool flag)
{
	int err,loop;

	struct ALS_PS_DATA *data = i2c_get_clientdata(client);

	loop = RPR0521_I2C_RETRY_COUNT;
	/*we give three times to repeat the i2c operation if i2c errors happen*/
	while(loop) {
		mutex_lock(&data->i2c_update_lock);
		/*0 is i2c_smbus_read_byte_data,1 is i2c_smbus_read_word_data*/
		if(flag == RPR0521_I2C_BYTE)
		{
			//err = i2c_smbus_read_byte_data(client, CMD_BYTE|reg);
			err = i2c_smbus_read_byte_data(client, reg);
		}
		else if(flag == RPR0521_I2C_WORD)
		{
			err = i2c_smbus_read_word_data(client, reg);
#if defined (CONFIG_HUAWEI_DSM)
			if(err<0)
			{
			 if(rp0521_als_ps_init_flag==1)
			 {
			   if(!dsm_client_ocuppy(als_ps_dclient))
		         {
				  //als_ps->irq_gpio = gpio_to_irq(als_ps->rpr0521_gpio);
				 dsm_client_record(als_ps_dclient,"[%s]i2c_status:%d.\n[irq gpio] num:%d, irq gpio status:%d\n",__func__,err,data->rpr0521_gpio, gpio_get_value(data->rpr0521_gpio));
				 dsm_client_notify(als_ps_dclient, DSM_ALS_PS_I2C_RW_ERROR_NO);
			      }
			  }
		  }
#endif
		}
		else
		{
			als_ps_INFO("[ALS_PS]%s,line %d:attention: i2c read wrong flag",__func__,__LINE__);
			mutex_unlock(&data->i2c_update_lock);
			return -EINVAL;
		}
		mutex_unlock(&data->i2c_update_lock);
		if(err < 0){
			loop--;
			mdelay(1);
		}
		else
			break;
	}
	/*after three times,we print the register and regulator value*/
	if(loop == 0){

		als_ps_INFO("[ALS_PS]%s,line %d:attention: i2c read err = %d,reg=0x%x",__func__,__LINE__,err,reg);	
	}

	return err;
}
static int Rpr0521_i2c_read_buf(struct i2c_client*client, u8 reg, u8 length, u8 *buf)
{
	int err,num;
	u8 *values = buf;

	struct ALS_PS_DATA *data = i2c_get_clientdata(client);

	num = RPR0521_I2C_RETRY_COUNT;
	/*we give three times to repeat the i2c operation if i2c errors happen*/
	while(num) {
		mutex_lock(&data->i2c_update_lock);
		
		err = i2c_smbus_read_i2c_block_data(client, reg, length, values);
		
		mutex_unlock(&data->i2c_update_lock);
		if(err !=  length){
			num--;
			mdelay(RPR0521_I2C_RETRY_TIMEOUT);
		}
		else
			break;
	}
	/*after three times,we print the register and regulator value*/
	if(num == 0){
		als_ps_INFO("[ALS_PS]%s,line %d:attention: i2c read err = %d,reg=0x%x",__func__,__LINE__,err,reg);	
	}

	return err;
}
static void rpr0521_change_ps_threshold(struct i2c_client *client)
{
	struct ALS_PS_DATA *data = i2c_get_clientdata(client);

	int pthreshold_h = 0, pthreshold_l = 0;
	int ret;
	unsigned char ps_info[3];
	
	 ret = Rpr0521_i2c_read_buf(client, REG_PERSISTENCE, 3, ps_info);
	 
	 if( ret < 0 )
	 { 
		data->ps_data = 200 ;
		als_ps_ERR("%s, line %d: pdate<0, reset to %d\n", __func__, __LINE__, data->ps_data);
	 }
	 else
	 {
		data->ps_data = (ps_info[2] << 8) | ps_info[1];
	 }

	if (ps_info[0] >> 6 == INFRARED_LOW)
	{
	 	if ((data->ps_data + rpr0521_pwave_value) < rpr0521_min_proximity_value && (data->ps_data >= 0))
        {
            	rpr0521_min_proximity_value = data->ps_data + rpr0521_pwave_value;
	     		Rpr0521_i2c_write(client,REG_PSTH,RPR_NEAR_THRESHOLD(rpr_threshold_value),RPR0521_I2C_WORD);
            	Rpr0521_i2c_write(client, REG_PSTL,RPR_FAR_THRESHOLD(rpr_threshold_value),RPR0521_I2C_WORD);
			
    	}
	}
        pthreshold_h = Rpr0521_i2c_read(client, REG_PSTH,RPR0521_I2C_WORD);
        pthreshold_l = Rpr0521_i2c_read(client, REG_PSTL,RPR0521_I2C_WORD);
		/* far-to-near detected */
	als_ps_INFO("[ALS_PS]ps_data = %d min_proximity_value = %d pthreshold_h = %d pthresold_l= %d\n",data->ps_data,rpr0521_min_proximity_value,pthreshold_h,pthreshold_l);

	if (data->ps_data >= pthreshold_h)/*near*/
        {
            
            Rpr0521_i2c_write(client, REG_PSTL,RPR_FAR_THRESHOLD(rpr_threshold_value),RPR0521_I2C_WORD);
	     Rpr0521_i2c_write(client,REG_PSTH, REG_PSTH_MAX,RPR0521_I2C_WORD);

		 als_ps_INFO("[ALS_PS]apds990x report 0\n");
	     data->ps_direction=1;
            input_report_abs(data->input_dev_ps, ABS_DISTANCE, 0);/* FAR-to-NEAR detection */
            input_sync(data->input_dev_ps);
        }
	
        else if (data->ps_data <=  pthreshold_l)/*far*/
        {
            Rpr0521_i2c_write(client,REG_PSTH,RPR_NEAR_THRESHOLD(rpr_threshold_value),RPR0521_I2C_WORD);
	     if (!loop)
	     {
	         Rpr0521_i2c_write(client, REG_PSTL,0,RPR0521_I2C_WORD);
	     }
	     else
	     {
		   Rpr0521_i2c_write(client, REG_PSTL,RPR_FAR_THRESHOLD(rpr_threshold_value),RPR0521_I2C_WORD);
	     	   loop--;
	     }
	     data->ps_direction=0;

		 als_ps_INFO("[ALS_PS]apds990x report 1\n");
            input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);/* NEAR-to-FAR detection */
	     input_sync(data->input_dev_ps);

        }
        
        else
        {
			als_ps_INFO("[ALS_PS]Wrong status!\n");
           
        }
}

/*************** Functions ******************/
/******************************************************************************
 * NAME       : rpr521_set_enable
 * FUNCTION   : set measurement time according to enable
 * REMARKS    : this function will overwrite the work mode. if it is called improperly, 
 *			   you may shutdown some part unexpectedly. please check als_ps->enable first.
 *			   I assume it is run in normal mode. If you want low noise mode, the code should be modified.
 *****************************************************************************/
static int rpr521_set_enable(struct i2c_client *client, int enable)
{
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	int ret;

	if(enable > 0xFb)
	{
		als_ps_INFO("[ALS_PS]%s: invalid measurement time setting.\n", __func__);
		return -EINVAL;
	}
	else
	{
		ret=Rpr0521_i2c_write(client, REG_MODECONTROL, enable,RPR0521_I2C_BYTE);
		if(ret<0)
		{
			als_ps_INFO("[ALS_PS]%s:i2c error.\n",__func__);
			return ret;
		}

		als_ps->enable = enable;
		als_ps->als_time = mode_table[(enable & 0xF)].ALS;
		als_ps->ps_time = mode_table[(enable & 0xF)].PS;

		return ret;
	}
}

static int rpr521_set_ps_threshold_low(struct i2c_client *client, int threshold)
{
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	int ret;
	unsigned short write_data;

    /* check whether the parameter is valid */
	if(threshold > REG_PSTL_MAX)
	{
		als_ps_INFO("[ALS_PS]%s: exceed maximum possible value.\n", __func__);
		return -EINVAL;
	}
	/*if(threshold > als_ps->ps_th_h)
	{
		als_ps_INFO("[ALS_PS]%s: higher than threshold high.\n", __func__);
		return -EINVAL;
	}*/
	
    /* write register to rpr521 via i2c */
	write_data = CONVERT_TO_BE(threshold);
	mutex_lock(&als_ps->update_lock);
	ret = i2c_smbus_write_i2c_block_data(client, REG_PSTL, sizeof(write_data), (unsigned char *)&write_data);
	mutex_unlock(&als_ps->update_lock);
	if(ret < 0)
	{
		als_ps_INFO("[ALS_PS]%s: write i2c fail.\n", __func__);
		return ret;
	}
	als_ps->ps_th_l = threshold;	//Update the value after successful i2c write to avoid difference. 
		
	return 0;
}

static int rpr521_get_gpio(struct ALS_PS_DATA *data, struct i2c_client *client)
{
	int rc = 0;
	data->rpr0521_gpio = of_get_named_gpio(client->dev.of_node, "proximity_gpio", 0);
	if (!gpio_is_valid(data->rpr0521_gpio)) {

		als_ps_INFO("[ALS_PS]%s: rpr521 irq gpio is not valid\n");
		rc = -EINVAL;
	}
	return rc;
}

static int rpr521_set_ps_threshold_high(struct i2c_client *client, int threshold)
{
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	int ret;
	unsigned short write_data;

    /* check whether the parameter is valid */
	if(threshold > REG_PSTH_MAX)
	{
		als_ps_INFO("[ALS_PS]%s: exceed maximum possible value.\n", __func__);
		return -EINVAL;
	}
	/*if(threshold < als_ps->ps_th_l)
	{
		als_ps_INFO("[ALS_PS]%s: lower than threshold low.\n", __func__);
		return -EINVAL;
	}*
	
    /* write register to rpr521 via i2c */
	write_data = CONVERT_TO_BE(threshold);
	mutex_lock(&als_ps->update_lock);
	ret = i2c_smbus_write_i2c_block_data(client, REG_PSTH, sizeof(write_data), (unsigned char *)&write_data);
	mutex_unlock(&als_ps->update_lock);
	if(ret < 0)
	{
		als_ps_INFO("[ALS_PS]%s: write i2c fail.\n", __func__);
		return ret;
	}
	als_ps->ps_th_h = threshold;	//Update the value after successful i2c write to avoid difference. 
		
	return 0;
}

static int rpr521_calibrate(struct i2c_client *client)
{
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	int average;
//	unsigned int tmp = 0, i;
 	unsigned int i, tmp, ps_th_h, ps_th_l;	

	average = 0;

	//rpr521_set_enable(client, 0x41);	//PS 10ms
	rpr521_set_enable(client, PS_EN|PS_DOUBLE_PULSE|PS10MS);        //PS 10ms


	for(i = 0; i < 20; i ++)
	{
		mdelay(20);
		tmp = i2c_smbus_read_word_data(client, REG_PSDATA);
		if(tmp < 0)
		{
			als_ps_INFO("[ALS_PS]%s: i2c read ps data fail. \n", __func__);
			//goto err_exit;
		}
		average += tmp & 0xFFF;	// 12 bit data
	}
	average /= 20;

//	ps_th_h = average + PS_ALS_SET_PS_TH;
//	ps_th_l = average + PS_ALS_SET_PS_TL;
	ps_th_h = average + THRES_TOLERANCE + THRES_DEFAULT_DIFF;
	ps_th_l = average + THRES_TOLERANCE;

	if(ps_th_h < 0)
	{
		als_ps_INFO("[ALS_PS]%s: high threshold is less than 0.\n", __func__);
		goto err_exit;
	}
	if(ps_th_h > REG_PSTH_MAX)
	{
		als_ps_INFO("[ALS_PS]%s: high threshold is greater than maximum allowed value.\n", __func__);
		goto err_exit;
	}
	if(ps_th_l < 0)
	{
		als_ps_INFO("[ALS_PS]%s: low threshold is less than 0.\n", __func__);
		goto err_exit;
	}
	if(ps_th_l > REG_PSTL_MAX)
	{
		als_ps_INFO("[ALS_PS]%s: low threshold is greater than maximum allowed value.\n", __func__);
		goto err_exit;
	}
#if 1
	if(!(rpr521_set_ps_threshold_high(client, ps_th_h)))
		als_ps->ps_th_h_back = ps_th_h;
	else 
		goto err_exit;
	if(!(rpr521_set_ps_threshold_low(client, ps_th_l)))
		als_ps->ps_th_l_back = ps_th_l;
	else
		goto err_exit;

#endif
	//rpr521_set_enable(client, 0);	//disable ps
        rpr521_set_enable(client, PS_ALS_SET_MODE_CONTROL);
	return 0;		

err_exit:
	//rpr521_set_enable(client, 0);	//disable ps
	rpr521_set_enable(client, PS_ALS_SET_MODE_CONTROL);

	return -1;
	
}

#if _FUNCTION_USED_	//masked because they are claimed but not used, which may cause error when compilling if the warning level is high enough. These functions provides some methods.
static int rpr521_set_persist(struct i2c_client *client, int persist)
{
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	int ret;
	
    /* check whether the parameter is valid */
	if(persist > PERSISTENCE_MAX)
	{
		als_ps_INFO("[ALS_PS]%s: exceed maximum possible value.\n", __func__);
		return -EINVAL;
	}
	
    /* write register to rpr521 via i2c */
	mutex_lock(&als_ps->update_lock);
	ret = i2c_smbus_write_byte_data(client, REG_PERSISTENCE, persist);
	mutex_unlock(&als_ps->update_lock);
	if(ret < 0)
	{
		als_ps_INFO("[ALS_PS]%s: write i2c fail.\n", __func__);
		return ret;
	}
	als_ps->persistence = persist;	//Update the value after successful i2c write to avoid difference. 

	return 0;
}

static int rpr521_set_control(struct i2c_client *client, int control)
{
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	int ret;
	unsigned char gain, led_current;
	
	if(control > REG_ALSPSCTL_MAX)
	{
		als_ps_INFO("[ALS_PS]%s: exceed maximum possible value.\n", __func__);
		return -EINVAL;
	}
	
	gain = (control & 0x3C) >> 2;	//gain setting values
	led_current = control & 0x03;		//led current setting value

	if(!((gain == ALSGAIN_X1X1) || (gain == ALSGAIN_X1X2) || (gain == ALSGAIN_X2X2) || (gain == ALSGAIN_X64X64)
		|| (gain == ALSGAIN_X128X64) || (gain == ALSGAIN_X128X128)))
	{
		als_ps_INFO("[ALS_PS]%s: invalid gain setting. \n", __func__);
		return -EINVAL;
	}
	
	mutex_lock(&als_ps->update_lock);
	ret = i2c_smbus_write_byte_data(client, REG_ALSPSCONTROL, control);
	mutex_unlock(&als_ps->update_lock);
	if(ret < 0)
	{
		als_ps_INFO("[ALS_PS]%s: write i2c fail.\n", __func__);
		return ret;
	}
	als_ps->control = control;
	als_ps->gain0 = gain_table[gain].DATA0;
	als_ps->gain1 = gain_table[gain].DATA1;
	als_ps->ledcurrent = led_current;

	return ret;
}
#endif

#if 0
/******************************************************************************
 * NAME       : long_long_divider
 * FUNCTION   : calc divider of unsigned long long int or unsgined long
 * REMARKS    :
 *****************************************************************************/
static void long_long_divider(unsigned long long data, unsigned long base_divier, unsigned long *answer, unsigned long long *overplus)
{
    volatile unsigned long long divier;
    volatile unsigned long      unit_sft;

    if ((long long)data < 0)	// . If data MSB is 1, it may go to endless loop. 
    	{
    	data /= 2;	//0xFFFFFFFFFFFFFFFF / 2 = 0x7FFFFFFFFFFFFFFF
	   base_divier /= 2;
    	}
    divier = base_divier;
    if (data > MASK_LONG) {
        unit_sft = 0;
        while (data > divier) {
            unit_sft++;
            divier = divier << 1;
        }
        while (data > base_divier) {
            if (data > divier) {
                *answer += 1 << unit_sft;
                data    -= divier;
            }
            unit_sft--;
            divier = divier >> 1;
        }
        *overplus = data;
    } else {
        *answer = (unsigned long)(data & MASK_LONG) / base_divier;
        /* calculate over plus and shift 16bit */
        *overplus = (unsigned long long)(data - (*answer * base_divier));
    }
}

#else
/******************************************************************************
 * NAME       : long_long_divider
 * FUNCTION   : calc divider of unsigned long long int or unsgined long
 * REMARKS    :
 *****************************************************************************/
static int long_long_divider(long long data, unsigned long base_divier, unsigned long *answer, unsigned long long *overplus)
{
    volatile long long divier;
    volatile long      unit_sft;

    if ((data < 0) || (base_divier == 0)) {
        *answer   = 0;
        *overplus = 0;
        return (CALC_ERROR);
    }

    divier = base_divier;
    if (data > MASK_LONG) {
        unit_sft = 0;
        while ((data > divier) && (divier > 0)) {
            unit_sft++;
            divier = divier << 1;
        }
        while ((data > base_divier) && (unit_sft > 0)) {
            if (data > divier) {
                *answer += 1 << unit_sft;
                data    -= divier;
            }
            unit_sft--;
            divier = divier >> 1;
        }
        *overplus = data;
    } else {
        *answer = (unsigned long)(data & MASK_LONG) / base_divier;
        /* calculate over plus and shift 16bit */
        *overplus = (unsigned long long)(data - (*answer * base_divier));
    }

    return (0);
}
#endif

/******************************************************************************
 * NAME       : calc_rohm_als_data
 * FUNCTION   : calculate illuminance data for rpr521
 * REMARKS    : final_data is 1000 times, which is defined as CUT_UNIT, of the actual lux value
 *****************************************************************************/
//static int calc_rohm_als_data(unsigned short data0, unsigned short data1, unsigned char gain0, unsigned char gain1, unsigned char time)
static int calc_rohm_als_data(struct i2c_client *client, struct ALS_PS_DATA *als_para)
{
#define DECIMAL_BIT      (15)
#define JUDGE_FIXED_COEF (1000)
#define MAX_OUTRANGE    655350// (11357)
#define MAXRANGE_NMODE   (0xFFFF)
#define MAXSET_CASE      (4)

	int                result;
	int                final_data;
	CALC_DATA          calc_data;
	CALC_ANS           calc_ans;
	unsigned long      calc_judge;
	unsigned char      set_case;
	unsigned long      div_answer;
	unsigned long long div_overplus;
	unsigned long long overplus;
	unsigned long      max_range;

	static unsigned long data0_temp_coefficient[COEFFICIENT] = {0,0,0,0};
	static unsigned long data1_temp_coefficient[COEFFICIENT] = {0,0,0,0};
	static unsigned long judge_temp_coefficient[COEFFICIENT] = {0,0,0,0};

	int err = 0;
	int i = 0;
	char get_tpghost[2] = "1";

	if (0 == apds_type)
	{
		for(i=0; i<4; i++)
		{
			data0_temp_coefficient[i] = data0_coefficient[i];
			data1_temp_coefficient[i] = data1_coefficient[i];
			judge_temp_coefficient[i] = judge_coefficient[i];
		}
	}
	else if (1 == apds_type)			//for CHM
	{
		if ((strcmp (tp_name, "no_name") == 0) || (rdtp_fail_times < READ_TP_SUCCESS))//on first read tp type
		{
			err |= ts_chip_info_store(&client->dev, NULL, get_tpghost, 2);
			err |= ts_chip_info_show(&client->dev, NULL, tp_name);

			if ((err<0) || (strcmp(tp_name, "null")==0))
			{
				rdtp_fail_times++;//if read fail ,then read tp module vendor three times
				als_ps_INFO("detected using tp vendor error. tp_name is %s.err num is %d.\n", tp_name, err);
			}
			else
			{
				rdtp_fail_times = READ_TP_SUCCESS;
				if (!strcmp(tp_name, "truly") || !strcmp(tp_name, "oflim") || !strcmp(tp_name, "lensone"))
				{
					als_ps_INFO("detected using tp vendor is %s.\n", tp_name);
				}
				else
				{
					als_ps_INFO("detected using tp vendor is not proposal.\n");
				}
			}

			if (!strcmp(tp_name,"truly"))	//chose parameter adapt several tp
			{
				for(i=0; i<4; i++)
				{
					data0_temp_coefficient[i] = data0_truly_CHM[i];
					data1_temp_coefficient[i] = data1_truly_CHM[i];
					judge_temp_coefficient[i] = judge_truly_CHM[i];
				}
			}
			else if (!strcmp(tp_name,"oflim"))
			{
				for(i=0; i<4; i++)
				{
					data0_temp_coefficient[i] = data0_oflim_CHM[i];
					data1_temp_coefficient[i] = data1_oflim_CHM[i];
					judge_temp_coefficient[i] = judge_oflim_CHM[i];
				}
			}
			else if (!strcmp(tp_name,"lensone"))
			{
				for(i=0; i<4; i++)
				{
					data0_temp_coefficient[i] = data0_lensone_CHM[i];
					data1_temp_coefficient[i] = data1_lensone_CHM[i];
					judge_temp_coefficient[i] = judge_lensone_CHM[i];
				}
			}
			else
			{
				for(i=0; i<4; i++)   //detected expected tp ,use truly para
				{
					data0_temp_coefficient[i] = data0_truly_CHM[i];
					data1_temp_coefficient[i] = data1_truly_CHM[i];
					judge_temp_coefficient[i] = judge_truly_CHM[i];
				}
			}
		}
	}
	else if (2 == apds_type)   //for ALE
	{
		if ((strcmp (tp_name, "no_name") == 0) || (rdtp_fail_times < READ_TP_SUCCESS))//on first read tp type
		{
			err |= cyttsp5_chip_info_store(&client->dev, NULL, get_tpghost, 2);
			err |= cyttsp5_chip_info_show(&client->dev, NULL, tp_name);

			if ((err<0) || (strcmp(tp_name, "null")==0))
			{
				rdtp_fail_times++;//if read fail ,then read tp module vendor three times
				als_ps_INFO("detected using tp vendor error. tp_name is %s.err num is %d.\n", tp_name, err);
			}
			else
			{
				rdtp_fail_times = READ_TP_SUCCESS;
				if (!strcmp(tp_name, "truly") || !strcmp(tp_name, "oflim") || !strcmp(tp_name, "junda"))
				{
					als_ps_INFO("detected using tp vendor is %s.\n", tp_name);
				}
				else
				{
					als_ps_INFO("detected using tp vendor is not proposal.\n");
				}
			}
			if (!strcmp(tp_name,"truly"))	//chose parameter adapt several tp
			{
				for(i=0; i<4; i++)
				{
					data0_temp_coefficient[i] = data0_truly_ALE[i];
					data1_temp_coefficient[i] = data1_truly_ALE[i];
					judge_temp_coefficient[i] = judge_truly_ALE[i];
				}
			}
			else if (!strcmp(tp_name,"oflim"))
			{
				for(i=0; i<4; i++)
				{
					data0_temp_coefficient[i] = data0_oflim_ALE[i];
					data1_temp_coefficient[i] = data1_oflim_ALE[i];
					judge_temp_coefficient[i] = judge_oflim_ALE[i];
				}
			}
			else if (!strcmp(tp_name,"junda"))
			{
				for(i=0; i<4; i++)
				{
					data0_temp_coefficient[i] = data0_junda_ALE[i];
					data1_temp_coefficient[i] = data1_junda_ALE[i];
					judge_temp_coefficient[i] = judge_junda_ALE[i];
				}
			}
			else
			{
				for(i=0; i<4; i++)   //detected expected tp ,use truly para
				{
					data0_temp_coefficient[i] = data0_truly_ALE[i];
					data1_temp_coefficient[i] = data1_truly_ALE[i];
					judge_temp_coefficient[i] = judge_truly_ALE[i];
				}
			}
		}
	}
	else    //if apds_type is other num ,use default para
	{
		for(i=0; i<4; i++)
		{
			data0_temp_coefficient[i] = data0_coefficient[i];
			data1_temp_coefficient[i] = data1_coefficient[i];
			judge_temp_coefficient[i] = judge_coefficient[i];
		}
	}
	/* set the value of measured als data */
	calc_data.als_data0  = als_para->als_data0_raw;
	calc_data.als_data1  = als_para->als_data1_raw;
	calc_data.gain_data0 = als_para->gain0;

	/* set max range */
	if (calc_data.gain_data0 == 0) 
	{
		/* issue error value when gain is 0 */
		return (CALC_ERROR);
	}
	else
	{
		max_range = MAX_OUTRANGE / calc_data.gain_data0;
	}
	
	/* calculate data */
	if (calc_data.als_data0 == MAXRANGE_NMODE) 
	{
		calc_ans.positive = max_range;
		calc_ans.decimal  = 0;
	} 
	else 
	{
		/* get the value which is measured from power table */
		calc_data.als_time = als_para->als_time;
		if (calc_data.als_time == 0) 
		{
			/* issue error value when time is 0 */
			return (CALC_ERROR);
		}

		calc_judge = calc_data.als_data1 * JUDGE_FIXED_COEF;
		if (calc_judge < (calc_data.als_data0 * judge_temp_coefficient[0]))
		{
			set_case = 0;
		} 
		else if (calc_judge < (calc_data.als_data0 * judge_temp_coefficient[1]))
		{
			set_case = 1;
		} 
		else if (calc_judge < (calc_data.als_data0 * judge_temp_coefficient[2]))
		{
			set_case = 2;
		}
		else if (calc_judge < (calc_data.als_data0 * judge_temp_coefficient[3]))
		{
			 set_case = 3;
		} 
		else
		{
			set_case = MAXSET_CASE;
		}
		calc_ans.positive = 0;
		if (set_case >= MAXSET_CASE) 
		{
			calc_ans.decimal = 0;	//which means that lux output is 0
		}
		else
		{
			calc_data.gain_data1 = als_para->gain1;
			if (calc_data.gain_data1 == 0) 
			{
				/* issue error value when gain is 0 */
				return (CALC_ERROR);
			}
			calc_data.data0      = (unsigned long long )(data0_temp_coefficient[set_case] * calc_data.als_data0) * calc_data.gain_data1;
			calc_data.data1      = (unsigned long long )(data1_temp_coefficient[set_case] * calc_data.als_data1) * calc_data.gain_data0;
			if(calc_data.data0 < calc_data.data1)	//In this case, data will be less than 0. As data is unsigned long long, it will become extremely big.
			{
				return (CALC_ERROR);
			}
			else
			{
				calc_data.data       = (calc_data.data0 - calc_data.data1);
			}
			calc_data.dev_unit   = calc_data.gain_data0 * calc_data.gain_data1 * calc_data.als_time * 10;	//24 bit at max (128 * 128 * 100 * 10)
			if (calc_data.dev_unit == 0) 
			{
				/* issue error value when dev_unit is 0 */
				return (CALC_ERROR);
			}

			/* calculate a positive number */
			div_answer   = 0;
			div_overplus = 0;
#if 0
			long_long_divider(calc_data.data, calc_data.dev_unit, &div_answer, &div_overplus); 
#else
			result = long_long_divider(calc_data.data, calc_data.dev_unit, &div_answer, &div_overplus);
      if (result == CALC_ERROR)
      {
         return (result);
      }
#endif
			calc_ans.positive = div_answer;
			/* calculate a decimal number */
			calc_ans.decimal = 0;
			overplus         = div_overplus;
			if (calc_ans.positive < max_range)
			{
				if (overplus != 0)
				{
					overplus     = overplus << DECIMAL_BIT;
					div_answer   = 0;
					div_overplus = 0;
#if 0
					long_long_divider(overplus, calc_data.dev_unit, &div_answer, &div_overplus);
#else
					result = long_long_divider(overplus, calc_data.dev_unit, &div_answer, &div_overplus);
					if (result == CALC_ERROR)
      		{
         		return (result);
      		}
#endif
					calc_ans.decimal = div_answer;
				}
			}

			else
			{
				calc_ans.positive = max_range;
			}
		}
	}
	
	final_data = calc_ans.positive * CUT_UNIT + ((calc_ans.decimal * CUT_UNIT) >> DECIMAL_BIT);
					
	return (final_data);

#undef DECIMAL_BIT
#undef JUDGE_FIXED_COEF
#undef MAX_OUTRANGE
#undef MAXRANGE_NMODE
#undef MAXSET_CASE
}


/******************************************************************************
 * NAME       : calculate_ps_data
 * FUNCTION   : calculate proximity data for rpr521
 * REMARKS    : 12 bit output
 *****************************************************************************/
/*static int calc_rohm_ps_data(unsigned short ps_reg_data)
{
    return (ps_reg_data & 0xFFF);
}*/

static unsigned int rpr521_als_data_to_level(unsigned int als_data)
{
#if 0
#define ALS_LEVEL_NUM 15
	int als_level[ALS_LEVEL_NUM]  = { 0, 50, 100, 150,  200,  250,  300, 350, 400,  450,  550, 650, 750, 900, 1100};
	int als_value[ALS_LEVEL_NUM]  = { 0, 50, 100, 150,  200,  250,  300, 350, 400,  450,  550, 650, 750, 900, 1100};
    	unsigned char idx;

	for(idx = 0; idx < ALS_LEVEL_NUM; idx ++)
	{
		if(als_data < als_value[idx])
		{
			break;
		}
	}
	if(idx >= ALS_LEVEL_NUM)
	{
		als_ps_INFO("[ALS_PS]rpr521 als data to level: exceed range.\n");
		idx = ALS_LEVEL_NUM - 1;
	}
	
	return als_level[idx];
#undef ALS_LEVEL_NUM
#else
	return als_data;
#endif
}

static void rpr521_reschedule_work(struct ALS_PS_DATA *als_ps,
					  unsigned long delay)
{
	unsigned long flags;

	spin_lock_irqsave(&als_ps->update_lock.wait_lock, flags);

	/*
	 * If work is already scheduled then subsequent schedules will not
	 * change the scheduled time that's why we have to cancel it first.
	 */
	cancel_delayed_work(&als_ps->dwork);
	schedule_delayed_work(&als_ps->dwork, delay);

	spin_unlock_irqrestore(&als_ps->update_lock.wait_lock, flags);
}

/* ALS polling routine */
static void rpr521_als_polling_work_handler(struct work_struct *work)
{
	static unsigned long lastprint_time = 0;
	unsigned char i;

	struct ALS_PS_DATA *als_ps = container_of(work, struct ALS_PS_DATA, als_dwork.work);
	struct i2c_client *client=als_ps->client;
	int tmp = 0;
	
	schedule_delayed_work(&als_ps->als_dwork, msecs_to_jiffies(als_ps->als_poll_delay));	// restart timer
	tmp=Rpr0521_i2c_read(client, REG_ALSDATA0,RPR0521_I2C_WORD);
	if(tmp < 0)
	{
		als_ps_INFO("[ALS_PS]%s: i2c read data0 fail. \n", __func__);
		//return tmp;
	}
	als_ps->als_data0_raw = (unsigned short)tmp;
	tmp=Rpr0521_i2c_read(client, REG_ALSDATA1,RPR0521_I2C_WORD);
	if(tmp < 0)
	{
		als_ps_INFO("[ALS_PS]%s: i2c read data1 fail. \n", __func__);
		//return tmp;
	}
	als_ps->als_data1_raw = (unsigned short)tmp;

// Theorically it is not necesssary to do so, but I just want to avoid any potential error.  -- Andy 2012.6.6
	tmp=Rpr0521_i2c_read(client, REG_ALSPSCONTROL,RPR0521_I2C_BYTE);
	if(tmp < 0)
	{
		als_ps_INFO("[ALS_PS]%s: i2c read gain fail. \n", __func__);
		//return tmp;
	}
	tmp = (tmp & 0x3C) >> 2;
	als_ps->gain0 = gain_table[tmp].DATA0;
	als_ps->gain1 = gain_table[tmp].DATA1;	
	tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
	if(tmp < 0)
	{
		als_ps_INFO("[ALS_PS]%s: i2c read time fail. \n", __func__);
		//return tmp;
	}
	tmp = tmp & 0xF;
	als_ps->als_time = mode_table[tmp].ALS;
	als_ps->als_data = calc_rohm_als_data(client, als_ps);
	/*if(als_ps->als_data == 0)
		als_ps->als_data ++;*/
	/*avoid als value > 10000 adn <0*/
	als_ps->als_data  =(als_ps->als_data) > 0 ? (als_ps->als_data) : 0;
	als_ps->als_data = (als_ps->als_data) < 10000 ? (als_ps->als_data) : 10000;
	if (time_after_eq(jiffies, lastprint_time + PRINT_LUX_PERIOD * HZ ))   //print the lux value per 30s
	{
		lastprint_time = jiffies;
		als_ps_INFO("[ALS_PS]: the luxval is %d for period.\n", als_ps->als_data);
	}
	else					//the luxval over last luxsection luxval, also print to kmsg
	{
		for (i=0; i<MAX_SECTION; i++)
		{
			if (als_ps->als_data <= g_luxsection[i])
				break;
		}
		if ((luxsection != i) && (abs(lastluxvalue-als_ps->als_data) >= lux_stepbuff))
		{
			luxsection = i;
			lastprint_time = jiffies;	//luxsection changed ,so reset the print period counter
			lastluxvalue = als_ps->als_data;  //refresh lastluxvalue
			als_ps_INFO("[ALS_PS]: the luxval is %d for luxsection skip to section%d.\n", als_ps->als_data, luxsection);
		}
	}

	als_ps->als_level = rpr521_als_data_to_level(als_ps->als_data);
	if(als_ps->als_data != CALC_ERROR)
	{
		input_report_abs(als_ps->input_dev_als, ABS_MISC, als_ps->als_level); // report als data. maybe necessary to convert to lux level
		input_sync(als_ps->input_dev_als);	
	}
	if(DT_tset)
	{
	 	als_data_count++;
	}
}


/* PS interrupt routine */
static void rpr521_ps_int_work_handler(struct work_struct *work)
{
	struct ALS_PS_DATA *als_ps = container_of((struct delayed_work *)work, struct ALS_PS_DATA, dwork);
	struct i2c_client *client=als_ps->client;
	int tmp;
	int infraded_data=0;
	tmp=Rpr0521_i2c_read(client, REG_INTERRUPT,RPR0521_I2C_BYTE);
	if(tmp < 0)
	{
		als_ps_INFO("[ALS_PS]%s: i2c read interrupt status fail. \n", __func__);
		goto err_exit;
	}

	als_ps_INFO("[ALS_PS]rpr521_ps_int_work_handler tmp=%d.\n",tmp);
	if(tmp & PS_INT_MASK)	//Interrupt is caused by PS
	{

		infraded_data=Rpr0521_i2c_read(client, REG_PERSISTENCE,RPR0521_I2C_BYTE);
		if ((infraded_data>>6) == INFRARED_LOW)
		{
			rpr0521_change_ps_threshold(client);
		}
		else
		{
			if(als_ps->ps_direction)
			{
				als_ps_INFO("[ALS_PS]when ps near background ambient noise\n");
				rpr0521_change_ps_threshold(client);
			}
			else
			{
				als_ps_INFO("[ALS_PS]Triggered by background ambient noise\n");
			}
		}
	}
	else
	{
		als_ps_INFO("[ALS_PS]%s: unknown interrupt source.\n", __func__);
		
	}
	
	if(DT_tset)
	{
	 	ps_data_count++;
	 }


	
err_exit:
	enable_irq(als_ps->irq_gpio);
}

/* assume this is ISR */
static irqreturn_t rpr521_interrupt(int vec, void *info)
{
	struct i2c_client *client=(struct i2c_client *)info;
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	wake_lock_timeout(&ps_wlock, 2*HZ);
	disable_irq_nosync(als_ps->irq_gpio);

	als_ps_INFO("[ALS_PS]%s\n", __func__);
	rpr521_reschedule_work(als_ps, 0);

	return IRQ_HANDLED;
}

/*************** SysFS Support ******************/
static ssize_t rpr521_show_enable_ps_sensor(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	
	return sprintf(buf, "%d\n", als_ps->enable_ps_sensor);
}

static ssize_t rpr521_store_enable_ps_sensor(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	int tmp;
	als_ps_INFO("[ALS_PS]rpr521 enable PS sensor -> %ld \n", val);
	if(DT_tset)
	{
		als_ps_INFO("[ALS_PS][%s] enter DT_TEST val=%ld\n", __func__, val);
		if(2==val)
		{
			val=1;
		}
		else if(3==val)
		{
			val=0;
		}
		else
		{
			return count;
		}
	}
		
	if ((val != 0) && (val != 1)) 
	{
		als_ps_INFO("[ALS_PS]%s:store unvalid value=%ld\n", __func__, val);
		return count;
	}
	
	//mutex_lock(&input_dev->mutex);
	if(val == 1) 
	{
		/* report 1*/
		input_report_abs(als_ps->input_dev_ps, ABS_DISTANCE, 1);
		input_sync(als_ps->input_dev_ps);
		//turn on p sensor
		//wake_lock(&ps_lock);
		loop = 10;
		if (als_ps->enable_ps_sensor == 0) 
		{
			if(als_ps->enable_als_sensor == 0){

				als_ps_INFO("[ALS_PS]%s: ALS and PS power on.\n",__func__);
				tmp = rpr521_init_client(client);
				if (tmp<0) {
					als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init rpr521\n", __func__, __LINE__);
					return tmp;
				}
			}
			else
			{
				tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
				if(tmp<0)
				{
				   als_ps_ERR("[ALS_PS]%s,read REG_MODECONTROL reg error: tmp=%x\n", __func__, tmp);
				   return tmp;
				}

				if (tmp&0x80)		//ALS device power on
				{
					tmp=Rpr0521_i2c_write(client, REG_PSTH, 960,RPR0521_I2C_WORD);
					if (tmp<0) {
						als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init REG_PSTH.\n", __func__, __LINE__);
						return tmp;
					}
					tmp=Rpr0521_i2c_write(client, REG_PSTL, 959,RPR0521_I2C_WORD);
					if (tmp<0) {
						als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init REG_PSTL.\n", __func__, __LINE__);
						return tmp;
					}
				}
				else 			//ALS device power off
				{
					tmp = rpr521_init_client(client);
					if (tmp < 0) {
						als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init rpr521\n", __func__, __LINE__);
						return tmp;
					}
					tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
					if(tmp<0)
					{
					   als_ps_ERR("[ALS_PS]%s,read REG_MODECONTROL reg error: tmp=%x\n", __func__, tmp);
					   return tmp;
					}
					tmp = tmp | 0x80;
					rpr521_set_enable(client, tmp);	//ALS on
				}
			}

			als_ps->enable_ps_sensor = 1;
			
			tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
			if(tmp<0)
			{
			   als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
			   return tmp;
			}
			tmp = tmp | 0x40;
			rpr521_set_enable(client, tmp);	//PS on
			power_key_ps=false;
			schedule_delayed_work(&als_ps->power_work, msecs_to_jiffies(100));
			enable_irq(als_ps->irq_gpio);
		
		}
		else
		{
			als_ps_INFO("[ALS_PS]%s:enable alrady\n", __func__);
		}
	} 
	else 
	{
		if(als_ps->enable_ps_sensor == 1)
		{
			als_ps->enable_ps_sensor = 0;
			cancel_delayed_work(&als_ps->power_work);
			tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
			if(tmp<0)
			{
			  als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
			   return tmp;
			}
			tmp = tmp & (~0x40);
			rpr521_set_enable(client, tmp);	//PS on and ALS off
			disable_irq(als_ps->irq_gpio);
			//wake_unlock(&ps_lock);
		}
	}

	//mutex_unlock(&input_dev->mutex);	
	return count;
}

static ssize_t rpr521_show_enable_als_sensor(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	
	return sprintf(buf, "%d\n", als_ps->enable_als_sensor);
}

static ssize_t rpr521_store_enable_als_sensor(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
 	unsigned long flags;
	int tmp;

	als_ps_INFO("[ALS_PS]rpr521 enable ALS sensor -> %ld\n", val);
	if(DT_tset)
	{
		als_ps_INFO("[ALS_PS][%s] enter DT_TEST val=%ld\n", __func__, val);
		if(2==val)
		{
			val=1;
		}
		else if(3==val)
		{
			val=0;
		}
		else
		{
			return count;
		}
	}

	if ((val != 0) && (val != 1))
	{
		als_ps_INFO("[ALS_PS]%s: enable als sensor=%ld\n", __func__, val);
		return count;
	}
	
	if(val == 1)
	{
		//turn on light  sensor
		if (als_ps->enable_als_sensor==0)
		{
			if(als_ps->enable_ps_sensor == 0){

				als_ps_INFO("[ALS_PS]rpr521_store_enable_als_sensor-grace test before power on/n");
			
				tmp = rpr521_init_client(client);
				if (tmp<0) {
					als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init rpr521\n", __func__, __LINE__);
					return tmp;
				}
			}
			luxsection = MAX_SECTION;			//make luxsection= 7 to print the luxvalue on first enable ALS
			lastluxvalue = g_luxsection[6]+lux_stepbuff;	//make sure after resume, print the luxval
			als_ps->enable_als_sensor = 1;
			tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
			if(tmp<0)
			{
			  als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
			   return tmp;
			}
			tmp = tmp | 0x80;
			rpr521_set_enable(client, tmp);	//ALS on
		}
		
		spin_lock_irqsave(&als_ps->update_lock.wait_lock, flags); 
       	cancel_delayed_work(&als_ps->als_dwork);
		schedule_delayed_work(&als_ps->als_dwork, msecs_to_jiffies(als_ps->als_poll_delay));	// 125ms
		spin_unlock_irqrestore(&als_ps->update_lock.wait_lock, flags);	
	}
	else
	{
		if(als_ps->enable_als_sensor == 1)
		{
			als_ps->enable_als_sensor = 0;

			tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
			if(tmp<0)
			{
			  als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
			   return tmp;
			}
			tmp = tmp & (~0x80);
			rpr521_set_enable(client, tmp);	//PS on and ALS off
		}
		
		spin_lock_irqsave(&als_ps->update_lock.wait_lock, flags); 
		cancel_delayed_work(&als_ps->als_dwork);
		spin_unlock_irqrestore(&als_ps->update_lock.wait_lock, flags);	
	}
	
	return count;
}

static ssize_t rpr521_show_als_poll_delay(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	
	return sprintf(buf, "%d\n", als_ps->als_poll_delay*1000);	// return in micro-second
}

static ssize_t rpr521_store_als_poll_delay(struct device *dev,
					struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	unsigned long flags;
	if(DT_tset)
	{
		if(10000!=val)
		{
			return count;
		}
	}
	if (val < PS_ALS_SET_MIN_DELAY_TIME * 1000)
		val = PS_ALS_SET_MIN_DELAY_TIME * 1000;	
	
	als_ps->als_poll_delay = val /1000;	// convert us => ms
	
	if (als_ps->enable_als_sensor == 1)
	{
	
	/* we need this polling timer routine for sunlight canellation */
	spin_lock_irqsave(&als_ps->update_lock.wait_lock, flags); 
		
	/*
	 * If work is already scheduled then subsequent schedules will not
	 * change the scheduled time that's why we have to cancel it first.
	 */
	cancel_delayed_work(&als_ps->als_dwork);
	schedule_delayed_work(&als_ps->als_dwork, msecs_to_jiffies(als_ps->als_poll_delay));	// 125ms
			
	spin_unlock_irqrestore(&als_ps->update_lock.wait_lock, flags);	
	
	}
	return count;
}

static ssize_t rpr521_show_als_data(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	int tmp;
	int tmp1;
	tmp = i2c_smbus_read_word_data(client, REG_ALSDATA0);
	tmp1 = i2c_smbus_read_word_data(client, REG_ALSDATA1);

	return sprintf(buf, "%d %d\n", tmp, tmp1);
}

static ssize_t rpr521_show_ps_data(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	int tmp = 0;
	tmp = i2c_smbus_read_word_data(client, REG_PSDATA);
	return sprintf(buf, "%d\n", tmp);
}

static ssize_t rpr521_show_ps_thres_high(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	//struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	
	//grace test in 2013.10.09 begin
	int ps_data = 0, ps_high = 0, ps_low = 0;
	ps_data = i2c_smbus_read_word_data(client, REG_PSDATA);
	if(ps_data < 0)
	{
			als_ps_INFO("[ALS_PS]%s: i2c read led current fail. \n", __func__);
			return -1;
	}
	
	ps_high = i2c_smbus_read_word_data(client, REG_PSTH);
	if(ps_high < 0)
	{
			als_ps_INFO("[ALS_PS]%s: i2c read led current fail. \n", __func__);
			return -1;
	}
	
	ps_low = i2c_smbus_read_word_data(client, REG_PSTL);
	if(ps_low < 0)
	{
			als_ps_INFO("[ALS_PS]%s: i2c read led current fail. \n", __func__);
			return -1;
	}
	
	//return sprintf(buf, "%d\n", als_ps->ps_th_h);	
	return sprintf(buf, "%d %d %d\n", ps_data, ps_high, ps_low);
	//grace test in 2013.10.09 end
}

static ssize_t rpr521_store_ps_thres_high(struct device *dev,
					struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	
	if(!(rpr521_set_ps_threshold_high(client, val)))
		als_ps->ps_th_h_back = als_ps->ps_th_h;
	
	return count;
}

static ssize_t rpr521_show_ps_thres_low(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	
	return sprintf(buf, "%d\n", als_ps->ps_th_l);	
}

static ssize_t rpr521_store_ps_thres_low(struct device *dev,
					struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	
	if(!(rpr521_set_ps_threshold_low(client, val)))
		als_ps->ps_th_l_back = als_ps->ps_th_l;
	
	return count;
}

static ssize_t rpr521_show_ps_calib(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	
	return sprintf(buf, "%d\t%d\n", als_ps->ps_th_h, als_ps->ps_th_l);	
}

static ssize_t rpr521_store_ps_calib(struct device *dev,
					struct device_attribute *attr, const char *buf, size_t count)
{
#define SET_LOW_THRES	1
#define SET_HIGH_THRES	2
#define SET_BOTH_THRES	3

	struct i2c_client *client = to_i2c_client(dev);
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
 	unsigned int i, tmp, ps_th_h, ps_th_l;
	int average;	//This should be signed to avoid error.
	
	switch(val)
	{
		case SET_LOW_THRES:		
		//Take 20 average for noise. use noise + THRES_TOLERANCE as low threshold.
		//If high threshold is lower than the new low threshold + THRES_DIFF, make the high one equal low + THRES_DIFF
		//Please make sure that there is NO object above the sensor, otherwise it may cause the high threshold too high to trigger which make the LCD NEVER shutdown.
		//If the noise is too large, larger than 4065, it will return -1. If so, the mechanical design MUST be redo. It is quite unlikely. 
			average = 0;
			ps_th_h = als_ps->ps_th_h_back;
			ps_th_l = als_ps->ps_th_l_back;
			for(i = 0; i < 20; i ++)
			{
				tmp = i2c_smbus_read_word_data(client, REG_PSDATA);
				if(tmp < 0)
				{
					als_ps_INFO("[ALS_PS]%s: i2c read ps data fail. \n", __func__);
					return -1;
				}
				average += tmp & 0xFFF;	// 12 bit data
			}
			average /= 20;		//This is the average noise
			ps_th_l = average + THRES_TOLERANCE;	
			if(ps_th_l > REG_PSTL_MAX)
			{
				return -1;
			}
			if(ps_th_l < 0)
			{
				return -1;
			}
			if(ps_th_h < ps_th_l + THRES_DIFF)
			{
				ps_th_h = ps_th_l + THRES_DIFF;	//It will not be minus or an error should have occured earlier. 
				if(ps_th_h > REG_PSTH_MAX)
				{
					return -1;
				}
				if(!rpr521_set_ps_threshold_high(client, ps_th_h))
					als_ps->ps_th_h_back = ps_th_h;
				else
					return -1;
			}
			if(!rpr521_set_ps_threshold_low(client, ps_th_l))
				als_ps->ps_th_l_back = ps_th_l;
			else
				return -1;
			break;
		
		case SET_HIGH_THRES:	
		//Take 20 average for signal. use signal -THRES_TOLERANCE as high threshold. 
		//If low threshold is higher than the new high one - THRES_DIFF, make the low one equal high - THRES_DIFF
		//Please make sure that there IS AN object above the sensor, otherwise it will be a disaster. The high threshold will be too low which will cause the panel ALWAYS shutdown
		//Customer can use their own standard to set the test scenario. For example, a 18% grey card @ 2cm, or another example, a 90% white card 4cm, and etc. 
		//If the signal is too weak, less than 30, it will return -1. If so, the mechanical design MUST be redo. It shall not happen very frequently. 
			average = 0;
			ps_th_h = als_ps->ps_th_h_back;
			ps_th_l = als_ps->ps_th_l_back;
			for(i = 0; i < 20; i ++)
			{
				tmp = i2c_smbus_read_word_data(client, REG_PSDATA);
				if(tmp < 0)
				{
					als_ps_INFO("[ALS_PS]%s: i2c read ps data fail. \n", __func__);
					return -1;
				}
				average += tmp & 0xFFF;	// 12 bit data
			}
			average /= 20;		//This is the average signal
			ps_th_h = average - THRES_TOLERANCE;
			if(ps_th_h > REG_PSTH_MAX)
			{
				return -1;
			}
			if(ps_th_h < 0)
			{
				return -1;
			}
			if(ps_th_l > ps_th_h - THRES_DIFF)
			{
				ps_th_l = ps_th_h - THRES_DIFF;	//Given that REG_PSTH_MAX = REG_PSTL+MAX, it will not be greater than REG_PSTL_MAX or an error should have occured earlier.
				if(ps_th_l < 0)
				{
					return -1;
				}
				if(!rpr521_set_ps_threshold_low(client, ps_th_l))
					als_ps->ps_th_l_back = ps_th_l;
				else
					return -1;
			}
			if(!rpr521_set_ps_threshold_high(client, ps_th_h))
				als_ps->ps_th_h_back = ps_th_h;
			else
				return -1;
			break;
		
		case SET_BOTH_THRES:	//Take 20 average for noise. use noise + PS_ALS_SET_PS_TL as low threshold, noise + PS_ALS_SET_PS_TH as high threshold
			rpr521_calibrate(client);
			break;

		default:
			return -EINVAL;	//NOT supported!
	}
			
	return count;

#undef SET_BOTH_THRES
#undef SET_HIGH_THRES
#undef SET_LOW_THRES
}

static ssize_t rpr521_show_type(struct device *dev,
                struct device_attribute *attr, char *buf){
    struct i2c_client *client = to_i2c_client(dev);
    struct ALS_PS_DATA *data = i2c_get_clientdata(client);

    return sprintf(buf, "%d\n", data->type);
}
static DEVICE_ATTR(als_poll_delay,  0660,
				    rpr521_show_als_poll_delay, rpr521_store_als_poll_delay);

static DEVICE_ATTR(enable_als_sensor,  0660 ,
				  rpr521_show_enable_als_sensor, rpr521_store_enable_als_sensor);

static DEVICE_ATTR(enable_ps_sensor,  0660 ,
				   rpr521_show_enable_ps_sensor, rpr521_store_enable_ps_sensor);

static DEVICE_ATTR(ps_thres_high,  0660 ,
				  rpr521_show_ps_thres_high, rpr521_store_ps_thres_high);

static DEVICE_ATTR(ps_thres_low,  0660 ,
				   rpr521_show_ps_thres_low, rpr521_store_ps_thres_low);

static DEVICE_ATTR(ps_calib,  0660 ,
				   rpr521_show_ps_calib, rpr521_store_ps_calib);
static DEVICE_ATTR(als_data, S_IRUGO, rpr521_show_als_data, NULL);
static DEVICE_ATTR(ps_data, S_IRUGO, rpr521_show_ps_data, NULL);
static DEVICE_ATTR(type, S_IRUGO, rpr521_show_type, NULL);//Add for EngineerMode

static struct attribute *rpr521_attributes[] = {
	&dev_attr_enable_ps_sensor.attr,
	&dev_attr_enable_als_sensor.attr,
	&dev_attr_als_poll_delay.attr,
	&dev_attr_ps_thres_high.attr,
	&dev_attr_ps_thres_low.attr,
	&dev_attr_ps_calib.attr,
	&dev_attr_als_data.attr,
	&dev_attr_ps_data.attr,
	&dev_attr_type.attr,
	NULL
};

static const struct attribute_group rpr521_attr_group = {
	.attrs = rpr521_attributes,
};

/*************** Initialze Functions ******************/
static int rpr521_init_client(struct i2c_client *client)
{
    int result;

    /* execute software reset */
   result=Rpr0521_i2c_write(client, REG_SYSTEMCONTROL, 0x40,RPR0521_I2C_BYTE);
   if(result<0)
   {
   	goto exit;
   }

   result=Rpr0521_i2c_write(client, REG_MODECONTROL, PS_ALS_SET_MODE_CONTROL,RPR0521_I2C_BYTE);
   if(result<0)
   {
   	goto exit;
   }
   result=Rpr0521_i2c_write(client, REG_ALSPSCONTROL, PS_ALS_SET_ALSPS_CONTROL,RPR0521_I2C_BYTE);
   if(result<0)
   {
   	goto exit;
   }
   result=Rpr0521_i2c_write(client, REG_PERSISTENCE, PS_ALS_SET_INTR_PERSIST,RPR0521_I2C_BYTE);
   if(result<0)
   {
   	goto exit;
   }
   result=Rpr0521_i2c_write(client, REG_INTERRUPT, PS_ALS_SET_INTR,RPR0521_I2C_BYTE);
   if(result<0)
   {
   	goto exit;
   }

   result=Rpr0521_i2c_write(client, REG_PSTH, 960,RPR0521_I2C_WORD);
   if(result<0)
   {
   	goto exit;
   }
   result=Rpr0521_i2c_write(client, REG_PSTL, 959,RPR0521_I2C_WORD);    
   if(result<0)
   {
   	goto exit;
   }
   als_ps_INFO("[ALS_PS]rpr521_init_client suncess!!!\n");
   return (result);

   exit:
   als_ps_INFO("[ALS_PS]rpr521_init_client fail!!!\n");
   return result;
}

static int rpr_power_on(struct ALS_PS_DATA *data, bool on)
{
	int rc;

	if (!on)
		goto power_off;

	rc = regulator_enable(data->vdd);
	if (rc) {
		als_ps_ERR("[ALS_PS]Regulator vdd enable failed rc=%d\n", rc);
		return rc;
	}
      /*
	rc = regulator_enable(data->vcc_i2c);
	if (rc) {
		als_ps_ERR("[ALS_PS]Regulator vcc_i2c enable failed rc=%d\n", rc);
		regulator_disable(data->vdd);
	}*/

	return rc;

power_off:
	rc = regulator_disable(data->vdd);
	if (rc) {
		als_ps_ERR("[ALS_PS]Regulator vdd disable failed rc=%d\n", rc);
		return rc;
	}
	/*
	rc = regulator_disable(data->vcc_i2c);
	if (rc) {
		als_ps_ERR("[ALS_PS]Regulator vcc_i2c disable failed rc=%d\n", rc);
	}*/

	return rc;
}
static int rpr_power_init(struct ALS_PS_DATA *data, bool on)
{
	int rc;

	
	data->vdd = regulator_get(&data->client->dev, "sensor-vdd");
	if (IS_ERR(data->vdd)) {
		rc = PTR_ERR(data->vdd);
		als_ps_ERR("[ALS_PS]Regulator get failed vdd rc=%d\n", rc);
		return rc;
	}

       rc = regulator_set_voltage(data->vdd, 2800000,
							2800000);
		if (rc) {
			als_ps_ERR("[ALS_PS]regulator set_vtg failed rc=%d\n", rc);
			return rc;
		}
	/*
	data->vcc_i2c = regulator_get(&data->client->dev, "vcc_i2c");
	if (IS_ERR(data->vcc_i2c)) {
		rc = PTR_ERR(data->vcc_i2c);
		als_ps_ERR("[ALS_PS]Regulator get failed vcc_i2c rc=%d\n", rc);
		goto reg_vdd_set_vtg;
	}

	if (regulator_count_voltages(data->vcc_i2c) > 0) {
		rc = regulator_set_voltage(data->vcc_i2c, FT_I2C_VTG_MIN_UV,
					   FT_I2C_VTG_MAX_UV);
		if (rc) {
			als_ps_ERR("[ALS_PS]Regulator set_vtg failed vcc_i2c rc=%d\n", rc);
			goto reg_vcc_i2c_put;
		}
	*/
	return 0;
}

#if defined(CONFIG_FB)
static int fb_notifier_callback(struct notifier_block *self,unsigned long event, void *data)
{
	int error = 0;
	int i;
	int tmp=0;
	struct fb_event *fb_event = data;
	struct ALS_PS_DATA *als_ps = container_of((struct notifier_block *)self, struct ALS_PS_DATA, fb_notify);
	struct i2c_client *client=als_ps->client;
	//struct i2c_client *client = this_light_data->client;
	int *blank = fb_event->data;
       for (i = 0 ; i < FB_MAX; i++) {
		if (registered_fb[i] == fb_event->info) {
			if (i == 0) {

				als_ps_INFO("[ALS_PS]ALS light:%d, go on !\n",i);
				break;
			} else {

				als_ps_INFO("[ALS_PS]ALS light:%d, exit !\n",i);
				return error;
			}
		}
	}

	switch(*blank){
	case FB_BLANK_UNBLANK:
		/*resume device*/
		switch(event) {
		case FB_EARLY_EVENT_BLANK:

			als_ps_INFO("[ALS_PS]try to resume\n");
			if ((!als_ps->enable_ps_sensor)&& als_ps->enable_als_sensor) 
			{

				als_ps_INFO("[ALS_PS]enable\n");
				tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
				if(tmp<0)
				{

				   als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
			   		return error;
				}
				tmp = tmp | 0x80;
				rpr521_set_enable(client, tmp);
				cancel_delayed_work(&als_ps->als_dwork);
				schedule_delayed_work(&als_ps->als_dwork, msecs_to_jiffies(als_ps->als_poll_delay));
			}
			break;
		case FB_EVENT_BLANK:
			break;
		default:
			break;
		}
		break;
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
	case FB_BLANK_POWERDOWN:
	default:
		/*suspend device*/
		switch(event) {
		case FB_EARLY_EVENT_BLANK:

			als_ps_INFO("[ALS_PS]try to suspend\n");
			if ((!als_ps->enable_ps_sensor) && als_ps->enable_als_sensor) 
			{

				als_ps_INFO("[ALS_PS]disable\n");
				cancel_delayed_work(&als_ps->als_dwork);
				tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
				if(tmp<0)
				{

				     als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
			   		return error;
				}
				tmp = tmp & (~0x80);
				rpr521_set_enable(client, tmp);
			}
			break;
		case FB_EVENT_BLANK:
			break;
		default:
			break;
		}
		break;
	}
	return error;
}
#endif
static void rpr521_power_screen_handler(struct work_struct *work)
{

	struct ALS_PS_DATA *data = container_of(work,struct ALS_PS_DATA, power_work.work);
	struct i2c_client *client= data->client;
	int i=0;
	int num=0;
	char reg[RPR521_REG_LEN];
	if(true==power_key_ps)
	{	 

		als_ps_INFO("[ALS_PS][%s] : power_key_ps (%d) press\n",__func__, power_key_ps);
	    power_key_ps=false;
	 	input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
        input_sync(data->input_dev_ps);
		for(i = 0; i < RPR521_REG_LEN; i++ )
		{
			reg[i] = Rpr0521_i2c_read(client,(i+0x40),RPR0521_I2C_BYTE);
			if(reg[i] <0)
			{
				als_ps_INFO("[ALS_PS]%s,line %d:read %d reg failed\n",__func__,__LINE__,i);
			}

			als_ps_INFO("[ALS_PS]reg[%x]=%x,",i+0x40,reg[i]);
			num++;
			if(9==num)
			{
				als_ps_INFO("[ALS_PS]\n");
				num=0;
			}
		}

	}
	schedule_delayed_work(&data->power_work, msecs_to_jiffies(500));
}
static int rohm_als_poll_delay_set(struct sensors_classdev *sensors_cdev,unsigned int delay_msec)
{
    struct ALS_PS_DATA *als_ps = container_of(sensors_cdev,struct ALS_PS_DATA, als_cdev);
    unsigned int val = delay_msec;
    unsigned long flags;
     if(als_ps==NULL)
    {
        als_ps_INFO("[ALS_PS]%s: SET DELAY ERRR\n", __func__);
        return -1;
    }

    als_ps_INFO("[ALS_PS][%s] val=%d\n", __func__, val);
    if (val < PS_ALS_SET_MIN_DELAY_TIME )
    {
        val = PS_ALS_SET_MIN_DELAY_TIME;
    }

    als_ps->als_poll_delay = val ;

    if (als_ps->enable_als_sensor == 1)
    {

        /* we need this polling timer routine for sunlight canellation */
        spin_lock_irqsave(&als_ps->update_lock.wait_lock, flags); 
        	
        /*
         * If work is already scheduled then subsequent schedules will not
         * change the scheduled time that's why we have to cancel it first.
         */
        cancel_delayed_work(&als_ps->als_dwork);
        schedule_delayed_work(&als_ps->als_dwork, msecs_to_jiffies(als_ps->als_poll_delay));	// 125ms
        		
        spin_unlock_irqrestore(&als_ps->update_lock.wait_lock, flags);	

    }
    return 0;
}

static int rohm_als_enable_set(struct sensors_classdev *sensors_cdev,unsigned int enable)
{
    struct ALS_PS_DATA *als_ps = container_of(sensors_cdev,struct ALS_PS_DATA, als_cdev);
    struct i2c_client *client = als_ps->client;
    unsigned int val=enable;
    unsigned long flags;
    int tmp;
    als_ps_INFO("[ALS_PS]%s: enable=%d,val=%d\n", __func__,enable,val);
    if ((val != 0) && (val != 1)) 
    {
        als_ps_INFO("[ALS_PS]%s: enable als sensor=%d\n",__func__, val);
        return -1;
    }

    if(val == 1)
    {
    	//turn on light  sensor
        if (als_ps->enable_als_sensor==0)
        {
            if(als_ps->enable_ps_sensor == 0)
            {
                als_ps_INFO("[ALS_PS]rpr521_store_enable_als_sensor-grace test before power on/n");
                tmp = rpr521_init_client(client);
                if (tmp<0) 
                {
                    als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init rpr521\n", __func__, __LINE__);
                    return tmp;
                }
            }
            luxsection = MAX_SECTION;			//make luxsection= 7 to print the luxvalue on first enable ALS
            lastluxvalue = g_luxsection[6]+lux_stepbuff;	//make sure after resume, print the luxval
            als_ps->enable_als_sensor = 1;
            tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
            if(tmp<0)
            {
                als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
                return tmp;
            }
            tmp = tmp | 0x80;
            rpr521_set_enable(client, tmp);	//ALS on

        }
        spin_lock_irqsave(&als_ps->update_lock.wait_lock, flags); 
        cancel_delayed_work(&als_ps->als_dwork);
        schedule_delayed_work(&als_ps->als_dwork, msecs_to_jiffies(als_ps->als_poll_delay));	// 125ms
        spin_unlock_irqrestore(&als_ps->update_lock.wait_lock, flags);	
    }
    else
    {
        if(als_ps->enable_als_sensor == 1)
        {
            als_ps->enable_als_sensor = 0;
            tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
            if(tmp<0)
            {
                als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
                return tmp;
            }
            tmp = tmp & (~0x80);
            rpr521_set_enable(client, tmp);	//PS on and ALS off
        }
        spin_lock_irqsave(&als_ps->update_lock.wait_lock, flags); 
        cancel_delayed_work(&als_ps->als_dwork);
        spin_unlock_irqrestore(&als_ps->update_lock.wait_lock, flags);	
    }
    return 0;
}
static int rohm_ps_enable_set(struct sensors_classdev *sensors_cdev,unsigned int enable)
{
    struct ALS_PS_DATA *als_ps = container_of(sensors_cdev,struct ALS_PS_DATA, ps_cdev);
    struct i2c_client *client = als_ps->client;
    unsigned int val=enable;
    int tmp;
    als_ps_INFO("[ALS_PS]%s: enable=%d,val=%d\n", __func__,enable,val);
    if ((val != 0) && (val != 1)) 
    {
        als_ps_INFO("[ALS_PS]%s: enable als sensor=%d\n",__func__, val);
        return -1;
    }

    if(val == 1) 
    {
        /* report 1*/
        input_report_abs(als_ps->input_dev_ps, ABS_DISTANCE, 1);
        input_sync(als_ps->input_dev_ps);
        //turn on p sensor
        loop = 10;
        if (als_ps->enable_ps_sensor == 0) 
        {
            if(als_ps->enable_als_sensor == 0)
            {
                als_ps_INFO("[ALS_PS]%s: ALS and PS power on.\n",__func__);
                tmp = rpr521_init_client(client);
                if (tmp<0) 
                {
                    als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init rpr521\n", __func__, __LINE__);
                    return tmp;
                }
            }
            else
            {
                tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
                if(tmp<0)
                {
                    als_ps_ERR("[ALS_PS]%s,read REG_MODECONTROL reg error: tmp=%x\n", __func__, tmp);
                    return tmp;
                }

                if (tmp&0x80)		//ALS device power on
                {
                    tmp=Rpr0521_i2c_write(client, REG_PSTH, 960,RPR0521_I2C_WORD);
                    if (tmp<0) 
                    {
                        als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init REG_PSTH.\n", __func__, __LINE__);
                        return tmp;
                    }
                    tmp=Rpr0521_i2c_write(client, REG_PSTL, 959,RPR0521_I2C_WORD);
                    if (tmp<0) 
                    {
                        als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init REG_PSTL.\n", __func__, __LINE__);
                        return tmp;
                    }
                }
                else 			//ALS device power off
                {
                    tmp = rpr521_init_client(client);
                    if (tmp < 0) 
                    {
                        als_ps_INFO("[ALS_PS]%s:line:%d,Failed to init rpr521\n", __func__, __LINE__);
                        return tmp;
                    }
                    tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
                    if(tmp<0)
                    {
                        als_ps_ERR("[ALS_PS]%s,read REG_MODECONTROL reg error: tmp=%x\n", __func__, tmp);
                        return tmp;
                    }
                    tmp = tmp | 0x80;
                    rpr521_set_enable(client, tmp);	//ALS on
                }
            }

            als_ps->enable_ps_sensor = 1;

            tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
            if(tmp<0)
            {
                als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
                return tmp;
            }
            tmp = tmp | 0x40;
            rpr521_set_enable(client, tmp);	//PS on
            power_key_ps=false;
            schedule_delayed_work(&als_ps->power_work, msecs_to_jiffies(100));
            enable_irq(als_ps->irq_gpio);

        }
        else
        {
            als_ps_INFO("[ALS_PS]%s:enable alrady\n", __func__);
        }
    } 
    else 
    {
        if(als_ps->enable_ps_sensor == 1)
        {
            als_ps->enable_ps_sensor = 0;
            cancel_delayed_work(&als_ps->power_work);
            tmp=Rpr0521_i2c_read(client, REG_MODECONTROL,RPR0521_I2C_BYTE);
            if(tmp<0)
            {
                als_ps_INFO("[ALS_PS]%s,error: tmp=%x\n", __func__, tmp);
                return tmp;
            }
            tmp = tmp & (~0x40);
            rpr521_set_enable(client, tmp);	//PS on and ALS off
            disable_irq(als_ps->irq_gpio);
        //wake_unlock(&ps_lock);
        }
    }

    return 0;
}
static int rpr521_probe(struct i2c_client *client,
				   const struct i2c_device_id *id)
{
#define ROHM_PSALS_ALSMAX (65535)
#define ROHM_PSALS_PSMAX  (4095)

	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct ALS_PS_DATA *als_ps;
	//unsigned long flags;
	struct device_node *np = client->dev.of_node;
	
	int err = 0;
	int dev_id;

	als_ps_INFO("[ALS_PS]%s started.\n",__func__);

	//wake_lock_init(&ps_lock,WAKE_LOCK_SUSPEND,"ps wakelock");

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE)) {
		err = -EIO;
		goto exit;
	}

	als_ps = kzalloc(sizeof(struct ALS_PS_DATA), GFP_KERNEL);
	if (!als_ps) {
		err = -ENOMEM;
		goto exit;
	}
	als_ps->client = client;
	i2c_set_clientdata(client, als_ps);

	err = rpr_power_init(als_ps, true);
	if (err) {
		als_ps_ERR("[ALS_PS]power init failed");
		goto exit_kfree;
	}
	
	err = rpr_power_on(als_ps, true);
	if (err) {
		als_ps_ERR("[ALS_PS]power on failed");
		goto exit_kfree;
	}

	msleep(3);
	//check whether is rpr521 or apds9930
	mutex_init(&als_ps->update_lock);
	mutex_init(&als_ps->i2c_update_lock);
	dev_id=Rpr0521_i2c_read(client, REG_MANUFACT_ID,RPR0521_I2C_BYTE);
	if(dev_id != 0xE0){
	    kfree(als_ps);
	    return -1;
	}
	als_ps->type = 1;   //not useful

	als_ps_INFO("[ALS_PS]%s: id(0x%x), this is rpr521!\n", __func__, dev_id);

	INIT_DELAYED_WORK(&als_ps->dwork, rpr521_ps_int_work_handler);
	INIT_DELAYED_WORK(&als_ps->als_dwork, rpr521_als_polling_work_handler);
	INIT_DELAYED_WORK(&als_ps->power_work,rpr521_power_screen_handler);
	wake_lock_init(&ps_wlock, WAKE_LOCK_SUSPEND, "rpr0521");


	/* Initialize the RPR400 chip */
	err = rpr521_init_client(client);
	if (err<0)
		goto exit_kfree;

	/* adjust ps parametr acording to different productions*/
	err = of_property_read_u32(np, "apds_type", &apds_type);
	if (err) {

		als_ps_ERR("[ALS_PS]apds_typel read failed:%d\n", err);
		goto exit_kfree;
	}
	if(0==apds_type)		//cherryplus
	{
		rpr0521_pwave_value = 37;
		rpr_threshold_value = 90;
		rpr0521_pwindows_value = 52;
	}
	else if(1 == apds_type)		//CHM
	{
		rpr0521_pwave_value  = 37;
		rpr_threshold_value = 90;
		rpr0521_pwindows_value = 52;
	}
	else if(2 == apds_type)		//ALE
	{
		rpr0521_pwave_value  = 37;
		rpr_threshold_value = 90;
		rpr0521_pwindows_value = 60;
	}
	else
	{
		rpr0521_pwave_value = 115;
		rpr_threshold_value = 120;
		rpr0521_pwindows_value = 170;
	}
	rpr0521_min_proximity_value = 3000;
	
	err =rpr521_get_gpio(als_ps,client);
	if (err<0) {

		als_ps_ERR("[ALS_PS]Failed to intialize hardware\n");
		goto exit_kfree;
	}

	als_ps->irq_gpio = gpio_to_irq(als_ps->rpr0521_gpio);
	als_ps->als_poll_delay = PS_ALS_SET_MIN_DELAY_TIME;	
	als_ps->ps_direction=0;

	/* Register to Input Device */
	als_ps->input_dev_als = input_allocate_device();
	if (!als_ps->input_dev_als) {
		err = -ENOMEM;

		als_ps_INFO("[ALS_PS]%s: Failed to allocate input device als\n", __func__);
		goto exit_free_irq;
	}

	als_ps->input_dev_ps = input_allocate_device();
	if (!als_ps->input_dev_ps) {
		err = -ENOMEM;

		als_ps_INFO("[ALS_PS]%s: Failed to allocate input device ps\n", __func__);
		goto exit_free_dev_als;
	}
	
	input_set_drvdata(als_ps->input_dev_ps, als_ps);
	input_set_drvdata(als_ps->input_dev_als, als_ps);
	
	set_bit(EV_ABS, als_ps->input_dev_als->evbit);
	set_bit(EV_ABS, als_ps->input_dev_ps->evbit);

	input_set_abs_params(als_ps->input_dev_als, ABS_MISC, 0, 10000, 0, 0);
	input_set_abs_params(als_ps->input_dev_ps, ABS_DISTANCE, 0, 1, 0, 0);

	als_ps->input_dev_als->name = ALS_INPUT_DEV_NAME;
	als_ps->input_dev_ps->name = PS_INPUT_DEV_NAME;
	als_ps->input_dev_als->id.bustype = BUS_I2C;
  	als_ps->input_dev_als->dev.parent =&als_ps->client->dev;
  	als_ps->input_dev_ps->id.bustype = BUS_I2C;
  	als_ps->input_dev_ps->dev.parent =&als_ps->client->dev;
 


	err = input_register_device(als_ps->input_dev_als);
	if (err) {
		err = -ENOMEM;

		als_ps_INFO("[ALS_PS]%s: Unable to register input device als: %s\n", __func__, 
		       als_ps->input_dev_als->name);
		goto exit_free_dev_ps;
	}

	err = input_register_device(als_ps->input_dev_ps);
	if (err) {
		err = -ENOMEM;
		als_ps_INFO("[ALS_PS]%s: Unable to register input device ps: %s\n", __func__, 
		       als_ps->input_dev_ps->name);
		goto exit_unregister_dev_als;
	}
       als_ps->als_cdev=rohm_als_cdev;
       als_ps->als_cdev.sensors_enable=rohm_als_enable_set;
       als_ps->als_cdev.sensors_poll_delay=rohm_als_poll_delay_set;
       err = sensors_classdev_register(&client->dev, &als_ps->als_cdev);
       if (err) 
       {
            als_ps_ERR("[ALS_PS]unable to register sensors_classdev: %d\n",err);
       }
       als_ps->ps_cdev=rohm_ps_cdev;
       als_ps->ps_cdev.sensors_enable=rohm_ps_enable_set;
       als_ps->ps_cdev.sensors_poll_delay=NULL;
       err = sensors_classdev_register(&client->dev, &als_ps->ps_cdev);
       if (err) 
       {
            als_ps_ERR("[ALS_PS]unable to register sensors_classdev: %d\n",err);
       }
	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &rpr521_attr_group);
	if (err)
	{
		als_ps_INFO("[ALS_PS]%s sysfs_create_groupX\n", __func__);
		goto exit_unregister_dev_ps;
	}

	/*regster interupt*/
	err = gpio_request(als_ps->rpr0521_gpio, "gpio_3_5");
	if (err) {
		als_ps_ERR("[ALS_PS]%s: failed to request gpio int1 for irq\n",__func__);
		goto exit_unregister_dev_ps;
	}

	err = gpio_direction_input(als_ps->rpr0521_gpio);
	if (err) {

		als_ps_ERR("[ALS_PS]%s: failed to config gpio direction\n",__func__);
		goto exit_free_gpio;
	}

	err = request_irq(als_ps->irq_gpio, rpr521_interrupt,
			IRQF_DISABLED | IRQF_TRIGGER_FALLING | IRQF_NO_SUSPEND,
						RPR521_DRV_NAME, (void *)client);
	if (err) {
		als_ps_ERR("[ALS_PS]%s  allocate rpr521_IRQ failed.\n",__func__);
		goto exit_free_gpio;
	}
	disable_irq(als_ps->irq_gpio);
	/*register FB CALLBACK */
	#if defined(CONFIG_FB)
		
		als_ps->fb_notify.notifier_call = fb_notifier_callback;
		err = fb_register_client(&als_ps->fb_notify);
		if (err){
			als_ps_ERR("[ALS_PS]unable to register fb_notifier: %d\n",err);
			goto exit_free_gpio;
		 }
	#endif
	/* add project meun*/
	err = set_sensor_chip_info(PS, "ROHM rpr0521");
	err = set_sensor_chip_info(ALS, "ROHM rpr0521");

	if (err) {
		als_ps_ERR("[ALS_PS]%s  set chip info error\n",__func__);
	}
	/*add BC TEST FLAG*/
      #ifdef CONFIG_HUAWEI_HW_DEV_DCT
       set_hw_dev_flag(DEV_I2C_L_SENSOR);
      #endif
#if defined (CONFIG_HUAWEI_DSM)
	   rp0521_als_ps_init_flag=1;
#endif
	   als_ps_INFO("[ALS_PS]rpr521_probe sucess \n");
	  
	return 0;

exit_free_gpio:
	gpio_free(als_ps->rpr0521_gpio);
exit_unregister_dev_ps:
	input_unregister_device(als_ps->input_dev_ps);	
exit_unregister_dev_als:

	als_ps_INFO("[ALS_PS]%s exit_unregister_dev_als:\n", __func__);
	input_unregister_device(als_ps->input_dev_als);
exit_free_dev_ps:
	input_free_device(als_ps->input_dev_ps);
exit_free_dev_als:
	input_free_device(als_ps->input_dev_als);
exit_free_irq:
	free_irq(client->irq, client);	
exit_kfree:
	kfree(als_ps);
exit:
	return err;

#undef ROHM_PSALS_ALSMAX
#undef ROHM_PSALS_PSMAX
}

static int rpr521_remove(struct i2c_client *client)
{
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	
	input_unregister_device(als_ps->input_dev_als);
	input_unregister_device(als_ps->input_dev_ps);
	
	input_free_device(als_ps->input_dev_als);
	input_free_device(als_ps->input_dev_ps);

	wake_lock_destroy(&ps_wlock);

	free_irq(als_ps->irq_gpio, client);

	sysfs_remove_group(&client->dev.kobj, &rpr521_attr_group);

	/* Power down the device */
	rpr521_set_enable(client, 0);

	kfree(als_ps);

	return 0;
}
#if 0
static int rpr521_suspend(struct i2c_client *client, pm_message_t mesg)
{
	als_ps_INFO("[ALS_PS]%s\n", __func__);

	disable_irq(client->irq);
	//wake_unlock(&ps_lock);
	//return rpr521_set_enable(client, 0);
	return rpr521_set_enable(client, PS_ALS_SET_MODE_CONTROL);
}

static int rpr521_resume(struct i2c_client *client)
{
#if 0 

	als_ps_INFO("[ALS_PS]%s \n", __func__);
	//wake_lock(&ps_lock);
	enable_irq(client->irq);
	//return rpr521_set_enable(client, BOTH100MS);
	return rpr521_set_enable(client, PS_ALS_SET_MODE_CONTROL|PS_EN);
	
#else
	struct ALS_PS_DATA *als_ps = i2c_get_clientdata(client);
	int tmp = PS_ALS_SET_MODE_CONTROL;
	
	als_ps_INFO("[ALS_PS]%s \n", __func__);
	
	enable_irq(client->irq);
	if(als_ps->enable_als_sensor == 1)
		tmp = tmp | ALS_EN;
	if(als_ps->enable_ps_sensor == 1)	
		tmp = tmp | PS_EN;
	return rpr521_set_enable(client, tmp);

#endif
}
#endif

MODULE_DEVICE_TABLE(i2c, rpr521_id);

static const struct i2c_device_id rpr521_id[] = {
	{ "rpr521", 0 },
	{ }
};

static struct of_device_id rpr_match_table[] = {
                { .compatible = "huawei,rpr521",},
                { },
        };


static struct i2c_driver rpr521_driver = {
	.driver = {
		.name	= RPR521_DRV_NAME,
		.owner	= THIS_MODULE,
		.of_match_table =rpr_match_table,
	},
	.probe	= rpr521_probe,
	.remove	= rpr521_remove,
	.id_table = rpr521_id,
};

static int __init rpr521_init(void)
{
	return i2c_add_driver(&rpr521_driver);
}

static void __exit rpr521_exit(void)
{
	i2c_del_driver(&rpr521_driver);
}

MODULE_AUTHOR("Andy Mi @ ROHM");
MODULE_DESCRIPTION("rpr521 ambient light + proximity sensor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

module_init(rpr521_init);
module_exit(rpr521_exit);


