/*
 *  apds990x.c - Linux kernel modules for ambient light + proximity sensor
 *
 *  Copyright (C) 2010 Lee Kai Koon <kai-koon.lee@avagotech.com>
 *  Copyright (C) 2010 Avago Technologies
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/input.h>
#include "apds990x.h"
#include <linux/board_sensors.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#include <linux/gpio.h>
#include <asm/io.h>
#include <linux/wakelock.h>
//#include <hsad/config_interface.h>
#include <linux/workqueue.h>
#include <linux/of_gpio.h>
#include <linux/module.h>
#include <linux/moduleparam.h>	
#include <huawei_platform/sensor/sensor_info.h>


#if defined(CONFIG_FB)
#include <linux/notifier.h>
#include <linux/fb.h>
static struct apds990x_data fb_light;
static struct apds990x_data  *this_light_data;
#endif
#if defined (CONFIG_HUAWEI_DSM)
#include <linux/mfd/hisi_hi6xxx_pmic.h>
#include <dsm/dsm_pub.h>
extern struct dsm_client *als_ps_dclient;
static int apds990x_als_ps_init_flag=0;
#endif
static char tp_name[10] = "no_name";
static int rdtp_fail_times = 0;
#define READ_TP_SUCCESS  3
#define APDS990X_I2C_RETRY_COUNT  3
#define APDS990X_I2C_BYTE  0
#define APDS990X_I2C_WORD  1

//#define DEBUG 1

/* Change History
 *
 * 1.0.1	Functions apds990x_show_rev(), apds990x_show_id() and apds990x_show_status()
 *			have missing CMD_BYTE in the i2c_smbus_read_byte_data(). APDS-990x needs
 *			CMD_BYTE for i2c write/read byte transaction.
 *
 *
 * 1.0.2	Include PS switching threshold level when interrupt occurred
 *
 *
 * 1.0.3	Implemented ISR and delay_work, correct PS threshold storing
 *
 * 1.0.4	Added Input Report Event
 */

/*
 * Management functions
 */
#define  MAX_ADC_PROX_VALUE  1023
#define  PS_FIRST_LOW_VALUE  549
#define  PS_FIRST_VALUE      550
#define 	FAR_THRESHOLD(x)		(min_proximity_value<(x)?(x):min_proximity_value)
#define 	NEAR_THRESHOLD(x)		((FAR_THRESHOLD(x) + apds_990x_pwindows_value - 1)>1022?1022:(FAR_THRESHOLD(x) + apds_990x_pwindows_value - 1))
#define  	MAX_FAR_THRESHOLD  (MAX_ADC_PROX_VALUE - apds_990x_pwindows_value-1)//723

#define  DELAY_FOR_DATA_RADY            300

extern int als_data_count;
extern int ps_data_count;
extern bool DT_tset;
static struct wake_lock wlock;
extern bool power_key_ps ;
static int lux_old = 300;
static int IC_old = 0;
static int min_proximity_value;
static int apds_990x_pwindows_value = 300;
static int apds_990x_pwave_value = 250;
static int ps_h, ps_l = 0;
static int ps_pulse_count=5;
static int als_polling_count;
static unsigned int apds_type = 0;
static unsigned int threshold_value = 0;
static unsigned int luxsection = MAX_SECTION;	//make luxsection= 7 to print the luxvalue on first enable ALS
static unsigned int lastluxvalue = 0;

//static int tp_color_for_edge = 0;
//extern unsigned int lcd_product_id;
static int get_reg = 0;
static int apds990x_i2c_write(struct i2c_client*client, u8 reg, u16 value,bool flag);
static int apds990x_i2c_read(struct i2c_client*client, u8 reg,bool flag);
static struct sensors_classdev apds_als_cdev = {
       .path_name="als_sensor",
	.name = "Light sensor",
	.vendor = "TAOS_TMD27723",
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
static struct sensors_classdev apds_ps_cdev = {
       .path_name="ps_sensor",
	.name = "Proximity sensor",
	.vendor = "TAOS_TMD27723",
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
static ssize_t store_get_reg_value(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	get_reg = simple_strtoul(buf, NULL, 10);
	return count;
}

static ssize_t show_get_reg_value(struct device *dev, struct device_attribute *attr, char *buf)
{

	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	int value = 0;

	value = apds990x_i2c_read(data->client,get_reg,APDS990X_I2C_BYTE);
	
	return snprintf(buf, PAGE_SIZE, "%X\n", value);
}
static DEVICE_ATTR(get_reg_value, 0664, show_get_reg_value, store_get_reg_value);

static int apds990x_set_command(struct i2c_client *client, int command)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;
	int clearInt;

	if (command == 0)
		clearInt = CMD_CLR_PS_INT;
	else if (command == 1)
		clearInt = CMD_CLR_ALS_INT;
	else
		clearInt = CMD_CLR_PS_ALS_INT;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte(client, clearInt);
	mutex_unlock(&data->update_lock);

	return ret;
}

static int apds990x_i2c_write(struct i2c_client*client, u8 reg, u16 value,bool flag)
{
	int err=0,count;
	struct apds990x_data *data = i2c_get_clientdata(client);
	
	if(NULL==client)
	{
	  return -EINVAL;
	}

	 count = APDS990X_I2C_RETRY_COUNT;
	/*we give three times to repeat the i2c operation if i2c errors happen*/
	while(count) 
	{
		mutex_lock(&data->single_lock);
		/*0 is i2c_smbus_write_byte_data,1 is i2c_smbus_write_word_data*/
		if(flag == APDS990X_I2C_BYTE)
		{
			err = i2c_smbus_write_byte_data(client, CMD_BYTE|reg, (u8)value);
		}
		else if(flag == APDS990X_I2C_WORD)
		{
			err = i2c_smbus_write_word_data(client, CMD_WORD|reg, value);
		}
		else
		{
			als_ps_INFO("%s,line %d:attention: i2c write wrong flag\n",__func__,__LINE__);
			mutex_unlock(&data->single_lock);
			return -EINVAL;
		}
		mutex_unlock(&data->single_lock);
		if(err < 0)
		{
			count--;
			mdelay(3);
		}
		else
		{
			break;
		}
	}

	/*after three times,we print the register and regulator value*/
	if(count == 0)
	{
		als_ps_INFO("%s,line %d:attention:i2c write err = %d\n",__func__,__LINE__,err);
	}
 
	return err;
}

static int apds990x_i2c_read(struct i2c_client*client, u8 reg,bool flag)
{
	int err=0,count;
	struct apds990x_data *data = i2c_get_clientdata(client);
	if(NULL==client)
	{
	  return -EINVAL;
	}

	count = APDS990X_I2C_RETRY_COUNT;
	/*we give three times to repeat the i2c operation if i2c errors happen*/
	while(count) 
	{
		mutex_lock(&data->single_lock);
		/*0 is i2c_smbus_read_byte_data,1 is i2c_smbus_read_word_data*/
		if(flag == APDS990X_I2C_BYTE)
		{
			err = i2c_smbus_read_byte_data(client, CMD_BYTE|reg);
		}
		else if(flag == APDS990X_I2C_WORD)
		{
			err = i2c_smbus_read_word_data(client, CMD_WORD|reg);
#if defined (CONFIG_HUAWEI_DSM)
			if(err<0)
			{
			 if(apds990x_als_ps_init_flag==1)
			 {
			   if(!dsm_client_ocuppy(als_ps_dclient))
		         {
				  //gpio_get_value(this_light_data->irq);
				  //data->irq = gpio_to_irq(data->apds_gpio);
				 dsm_client_record(als_ps_dclient,"[%s]i2c_status:%d,[irq gpio]num:%d,irq gpio status:%d.\n",__func__,err,data->apds_gpio, gpio_get_value(data->apds_gpio));
                 dsm_client_notify(als_ps_dclient, DSM_ALS_PS_I2C_RW_ERROR_NO);}
			  }
		  }
#endif
		}
		else
		{
			als_ps_INFO("%s,line %d:attention: i2c read wrong flag\n",__func__,__LINE__);
			mutex_unlock(&data->single_lock);
			return -EINVAL;
		}
		mutex_unlock(&data->single_lock);
		if(err < 0)
		{
			count--;
			mdelay(3);
		}
		else
		{
			break;
		}
	}
	/*after three times,we print the register and regulator value*/
	if(count == 0)
	{
		als_ps_INFO("%s,line %d:attention: i2c read err = %d,reg=0x%x\n",__func__,__LINE__,err,reg);
	}

	return err;
}

static int apds990x_regulator_configure(struct apds990x_data *data, struct i2c_client *client)
{
	int rc;

	data->apds990x_vdd = regulator_get(&client->dev, "sensor-vdd");
	if (IS_ERR(data->apds990x_vdd))
	{
		rc = PTR_ERR(data->apds990x_vdd);
		als_ps_ERR("[ALS_PS]Regulator get failed apds990x_vdd rc=%d\n", rc);
		return rc;
	}

	rc = regulator_set_voltage(data->apds990x_vdd, 2800000,
							2800000);
		if (rc) {
			als_ps_ERR("[ALS_PS]regulator set_vtg failed rc=%d\n", rc);
			return rc;
		}
/*
    data->apds990x_io_vdd = regulator_get(&client->dev, "sensor-io");
	if (IS_ERR(data->apds990x_io_vdd)) {
		rc = PTR_ERR(data->apds990x_io_vdd);
		als_ps_ERR("[ALS_PS]Regulator get failed apds990x_io_vdd rc=%d\n", rc);	
		return rc;
	}
*/
	return 0;
}
static int  apds990x_regulator_enable(struct apds990x_data *data)
{
	int rc = 1;

	rc = regulator_enable(data->apds990x_vdd);
	if (rc) {
		als_ps_INFO("[ALS_PS]Regulator apds990x_vdd enable failed rc=%d\n", rc);
		return rc;
		}

/*
	rc = regulator_enable(data->apds990x_io_vdd);
	if (rc) {
		als_ps_INFO("[ALS_PS]Regulator apds990x_io_vdd enable failed rc=%d\n", rc);
		return rc;
	}
*/
	return 0;
}
/*
static int  apds990x_regulator_disable(struct apds990x_data *data)
{
	int rc = 1;
	rc = regulator_disable(data->apds990x_vdd);
	if (rc) {
		als_ps_INFO("[ALS_PS]Regulator apds990x_vdd disable failed rc=%d\n", rc);
		return rc;
		}

	rc = regulator_disable(data->apds990x_io_vdd);
	if (rc) {
		als_ps_INFO("[ALS_PS]Regulator apds990x_io_vdd disable failed rc=%d\n", rc);
		return rc;
	}
	return 0;
}
*/
static int apds990x_set_enable(struct i2c_client *client, int enable)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);	
	ret=apds990x_i2c_write(client, APDS990x_ENABLE_REG, enable,APDS990X_I2C_BYTE);
	mutex_unlock(&data->update_lock);
	data->enable = enable;

	return ret;
}

static int apds990x_set_atime(struct i2c_client *client, int atime)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_ATIME_REG, atime,APDS990X_I2C_BYTE);
	mutex_unlock(&data->update_lock);
	data->atime = atime;

	return ret;
}

static int apds990x_set_ptime(struct i2c_client *client, int ptime)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_PTIME_REG, ptime,APDS990X_I2C_BYTE);
	mutex_unlock(&data->update_lock);
	data->ptime = ptime;

	return ret;
}

static int apds990x_set_wtime(struct i2c_client *client, int wtime)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_WTIME_REG, wtime,APDS990X_I2C_BYTE);
	mutex_unlock(&data->update_lock);
	data->wtime = wtime;

	return ret;
}

static int apds990x_set_ailt(struct i2c_client *client, int threshold)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_AILTL_REG, threshold,APDS990X_I2C_WORD);
	mutex_unlock(&data->update_lock);
	data->ailt = threshold;

	return ret;
}

static int apds990x_set_aiht(struct i2c_client *client, int threshold)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_AIHTL_REG, threshold,APDS990X_I2C_WORD);
	mutex_unlock(&data->update_lock);
	data->aiht = threshold;

	return ret;
}

static int apds990x_set_pilt(struct i2c_client *client, int threshold)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_PILTL_REG, threshold,APDS990X_I2C_WORD);
	mutex_unlock(&data->update_lock);
	data->pilt = threshold;

	return ret;
}

static int apds990x_set_piht(struct i2c_client *client, int threshold)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_PIHTL_REG, threshold,APDS990X_I2C_WORD);
	mutex_unlock(&data->update_lock);
	data->piht = threshold;

	return ret;
}

static int apds990x_set_pers(struct i2c_client *client, int pers)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_PERS_REG, pers,APDS990X_I2C_BYTE);
	mutex_unlock(&data->update_lock);
	data->pers = pers;

	return ret;
}

static int apds990x_set_config(struct i2c_client *client, int config)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_CONFIG_REG, config,APDS990X_I2C_BYTE);
	mutex_unlock(&data->update_lock);
	data->config = config;

	return ret;
}

static int apds990x_set_ppcount(struct i2c_client *client, int ppcount)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
    ret = apds990x_i2c_write(client,APDS990x_PPCOUNT_REG, ppcount,APDS990X_I2C_BYTE);
	if (ret < 0){
		als_ps_INFO("%s,line %d:i2c error,ppcount = %d\n",__func__,__LINE__,ppcount);
		mutex_unlock(&data->update_lock);
		return ret;
	}
	mutex_unlock(&data->update_lock);
	data->ppcount = ppcount;
	return ret;
}

static int apds990x_set_control(struct i2c_client *client, int control)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = apds990x_i2c_write(client,APDS990x_CONTROL_REG, control,APDS990X_I2C_BYTE);
	if (ret < 0){
		als_ps_INFO("%s,line %d:i2c error,control = %d\n",__func__,__LINE__,control);
		mutex_unlock(&data->update_lock);
		return ret;
	}
	mutex_unlock(&data->update_lock);
	data->control = control;

	/* obtain ALS gain value */
	if ((data->control & 0x03) == 0x00) /* 1X Gain */
		data->als_gain = 1;
	else if ((data->control & 0x03) == 0x01) /* 8X Gain */
		data->als_gain = 8;
	else if ((data->control & 0x03) == 0x02) /* 16X Gain */
		data->als_gain = 16;
	else  /* 120X Gain */
		data->als_gain = 120;

	return ret;
}

static int LuxCalculation(struct i2c_client *client, int cdata, int irdata)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int luxValue = 0;
	char get_tpghost[2] = "1";
	int IAC1 = 0;
	int IAC2 = 0;
	int IAC = 0;
	int GA;
	int COE_B;
	int COE_C;
	int COE_D;
	int DF = 52;
	int err = 0;
	if((data->enable_ps_sensor == 1 && cdata >= 6144) || (cdata >= 37886 && data->enable_ps_sensor == 0))  return 10000;

	COE_B=2117;
	COE_C=76;
	COE_D=78;

	if (2 == apds_type)
	{
		COE_B=1860;
		COE_C=750;
		COE_D=1290;
	}
	IAC1 = (cdata - (COE_B*irdata)/1000);	// re-adjust COE_B to avoid 2 decimal point
	IAC2 = ((COE_C*cdata)/1000 - (COE_D*irdata)/1000); // re-adjust COE_C and COE_D to void 2 decimal point

	if (IAC1 > IAC2)
		IAC = IAC1;
	else IAC = IAC2;

	if(IAC < 0) IAC =IC_old;
	else IC_old = IAC;

	if(0==apds_type)
	{
		GA=6800;
		if(cdata < 2113*irdata/1000)
		{
			GA = GA*95/100;
		}
		else if(cdata >= 2113*irdata/1000  && cdata < 47*irdata/10)
		{
			GA = GA*60/100;
		}
		else
			GA = GA;
		luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else if(1 == apds_type)  //use AVAGO APDS environment sensor
	{
		if((strcmp (tp_name, "no_name") == 0) || (rdtp_fail_times < READ_TP_SUCCESS))//on first read tp type
		{
			err |= ts_chip_info_store(&client->dev, NULL, get_tpghost, 2);
			err |= ts_chip_info_show(&client->dev, NULL, tp_name);

			if ( (err<0) || (!strcmp(tp_name, "null") ))//if read string is null ,then read it again
			{
				rdtp_fail_times++;	//if read fail ,then read tp module vendor three times
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
		}
		if (!strcmp(tp_name, "truly"))  //use truly tp
		{
			GA = 4800;
			if(cdata < 2113*irdata/1000)
			{
				 GA = GA*110/100;
			}
			else if((cdata >= 2113*irdata/1000) && (cdata < 47*irdata/10))
			{
				 GA = GA*65/100;
			}
			else
			{
				 GA = GA ;
			}
		}
		else if (!strcmp(tp_name,"oflim"))  //use oflim tp
		{
			GA = 5350;
			if(cdata < 2150*irdata/1000)
			{
				 GA = GA*110/100;
			}
			else if((cdata >= 2150*irdata/1000) && (cdata < 50*irdata/10))
			{
				 GA = GA*77/100;
			}
			else
			{
				 GA = GA ;
			}
		}
		else if (!strcmp(tp_name,"lensone"))  //use lensone tp
		{
			GA = 5800;
			if(cdata < 2150*irdata/1000)
			{
				 GA = GA*100/100;
			}
			else if((cdata >= 2150*irdata/1000)  && (cdata < 50*irdata/10))
			{
				 GA = GA*86/100;
			}
			else
			{
				 GA = GA ;
			}
		}
		else
		{
			GA=4800;
			if(cdata < 2113*irdata/1000)
			{
				 GA = GA*110/100;
			}
			else if((cdata >= 2113*irdata/1000) && (cdata < 47*irdata/10))
			{
				 GA = GA*65/100;
			}
			else
			{
				 GA = GA ;
			}
		}
		luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else if(2 == apds_type)  //use AVAGO APDS environment sensor
	{
		if((strcmp (tp_name, "no_name") == 0) || (rdtp_fail_times < READ_TP_SUCCESS))//on first read tp type
		{
			err |= cyttsp5_chip_info_store(&client->dev, NULL, get_tpghost, 2);
			err |= cyttsp5_chip_info_show(&client->dev, NULL, tp_name);

			if ((err<0) || (!strcmp(tp_name, "null")))//if read string is null ,then read it again
			{
				rdtp_fail_times++;	//if read fail ,then read tp module vendor three times
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
		}
		if (!strcmp(tp_name,"oflim"))  //use oflim tp
		{
			GA = 5170;
			if(cdata < 2090*irdata/1000)	//A light
			{
				GA = GA*35/100;
			}
			else if((cdata >= 2090*irdata/1000) && (cdata < 49*irdata/10))	//D light
			{
				GA = GA*39/100;
			}
			else							//C light
			{
				GA = GA;
			}
		}
		else if (!strcmp(tp_name, "truly"))  //use truly tp
		{
			GA = 5000;
			if(cdata < 2090*irdata/1000)	//A light
			{
				GA = GA*40/100;
			}
			else if((cdata >= 2090*irdata/1000) && (cdata < 49*irdata/10))	//D light
			{
				GA = GA*40/100;
			}
			else							//C light
			{
				GA = GA;
			}
		}
		else if (!strcmp(tp_name, "junda"))  //use junda tp
		{
			GA = 4500;
			if(cdata < 2150*irdata/1000)	//A light
			{
				GA = GA*40/100;
			}
			else if((cdata >= 2150*irdata/1000) && (cdata < 49*irdata/10))	//D light
			{
				GA = GA*39/100;
			}
			else							//C light
			{
				GA = GA;
			}
		}
		else
		{
			GA=4800;
			if(cdata < 2113*irdata/1000)
			{
				GA = GA*110/100;
			}
			else if((cdata >= 2113*irdata/1000) && (cdata < 47*irdata/10))
			{
				GA = GA*65/100;
			}
			else
			{
				GA = GA ;
			}
		}
		luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else
	{
		GA=3600;
		if(cdata < 215*irdata/100)
			GA = GA*100/150;
		else if(cdata >= 215*irdata/100 && cdata <= 50*irdata/10 )
			GA= GA *100/145;
		else
			GA = GA ;
		luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	return luxValue;
}

static int loop = 10;
static void apds990x_change_ps_threshold(struct i2c_client *client)
{
	struct apds990x_data *data = i2c_get_clientdata(client);

	int pthreshold_h = 0, pthreshold_l = 0;
	data->ps_data =	apds990x_i2c_read(client,APDS990x_PDATAL_REG,APDS990X_I2C_WORD);

        if ((data->ps_data + apds_990x_pwave_value) < min_proximity_value && (data->ps_data >= 0))
        {
            min_proximity_value = data->ps_data + apds_990x_pwave_value;
			apds990x_i2c_write(client,APDS990x_PILTL_REG,FAR_THRESHOLD(threshold_value),APDS990X_I2C_WORD);
		    apds990x_i2c_write(client,APDS990x_PIHTL_REG,NEAR_THRESHOLD(threshold_value),APDS990X_I2C_WORD);
				
        }
    // als_ps_INFO("[ALS_PS]ps_data = %d min_proximity_value = %d pthreshold_h = %d pthresold_l= %d\n",data->psdata,min_proximity_value,pthreshold_h,pthreshold_l);

		 pthreshold_h=apds990x_i2c_read(client,APDS990x_PIHTL_REG,APDS990X_I2C_WORD);
		 pthreshold_l=apds990x_i2c_read(client,APDS990x_PILTL_REG,APDS990X_I2C_WORD);
		 
		/* far-to-near detected */
	     als_ps_INFO("[ALS_PS]ps_data = %d min_proximity_value = %d pthreshold_h = %d pthresold_l= %d\n",data->ps_data,min_proximity_value,pthreshold_h,pthreshold_l);
        if (data->ps_data >= pthreshold_h)/*near*/
        {
            data->ps_detection = 1;

			apds990x_i2c_write(client,APDS990x_PILTL_REG,FAR_THRESHOLD(threshold_value),APDS990X_I2C_WORD);
		    apds990x_i2c_write(client,APDS990x_PIHTL_REG,1023,APDS990X_I2C_WORD);
			
		 als_ps_INFO("[ALS_PS]apds990x report 0\n");
            input_report_abs(data->input_dev_ps, ABS_DISTANCE, 0);/* FAR-to-NEAR detection */
            input_sync(data->input_dev_ps);
        }
        /* if less than the value of  proximity low threshold we set*/
        /* the condition of pdata==pthreshold_l is valid */
        else if (data->ps_data <=  pthreshold_l)/*far*/
        {
            data->ps_detection = 0;
			  apds990x_i2c_write(client,APDS990x_PIHTL_REG,NEAR_THRESHOLD(threshold_value),APDS990X_I2C_WORD);
			
	    if (!loop)
		{
			   apds990x_i2c_write(client,APDS990x_PILTL_REG,0,APDS990X_I2C_WORD);
			   
			   
	    }
		else 
		{
			 apds990x_i2c_write(client,APDS990x_PILTL_REG,FAR_THRESHOLD(threshold_value),APDS990X_I2C_WORD);
			loop--;
	    }

		als_ps_INFO("[ALS_PS]apds990x report 1\n");
        input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);/* NEAR-to-FAR detection */
	    input_sync(data->input_dev_ps);

        }
        /*on 27a platform ,bug info is a lot*/
        else
        {
			als_ps_INFO("[ALS_PS]Wrong status!\n");
			apds990x_i2c_write(client,APDS990x_PILTL_REG, FAR_THRESHOLD(threshold_value),APDS990X_I2C_WORD);
        }
		pthreshold_h = apds990x_i2c_read(client,APDS990x_PIHTL_REG,APDS990X_I2C_WORD);
        pthreshold_l = apds990x_i2c_read(client, APDS990x_PILTL_REG,APDS990X_I2C_WORD);
		
        ps_h = pthreshold_h;
        ps_l = pthreshold_l;


}

static void apds990x_change_als_threshold(struct i2c_client *client)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int cdata, irdata;
	int luxValue = 0;

	cdata = apds990x_i2c_read(client,APDS990x_CDATAL_REG,APDS990X_I2C_WORD);
    irdata= apds990x_i2c_read(client,APDS990x_IRDATAL_REG,APDS990X_I2C_WORD);

	luxValue = LuxCalculation(client, cdata, irdata);
	luxValue = luxValue > 0 ? luxValue : 0;
	luxValue = luxValue < 10000 ? luxValue : 10000;

	/* check PS under sunlight */
	if ((data->ps_detection == 1) &&
			(irdata > 5500)) {
		/*PS was previously in far-to-near condition*/
		/* need to inform input event as there will be no interrupt from the PS */
		/* NEAR-to-FAR detection */
		input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);

		input_sync(data->input_dev_ps);

		apds990x_i2c_write(client,APDS990x_PIHTL_REG, NEAR_THRESHOLD(threshold_value),APDS990X_I2C_WORD);
		
		data->pilt = 0;
		data->piht = data->ps_threshold;

		data->ps_detection = 0;	/* near-to-far detected */

		als_ps_FLOW("[ALS_PS]apds_990x_proximity_handler = FAR\n");
	}


	input_report_abs(data->input_dev_als, ABS_MISC, luxValue); /* report the lux level */
	input_sync(data->input_dev_als);

	data->als_data = cdata;

	data->als_threshold_l = (data->als_data *
		(100 - APDS990x_ALS_THRESHOLD_HSYTERESIS)) / 100;
	data->als_threshold_h = (data->als_data *
		(100 + APDS990x_ALS_THRESHOLD_HSYTERESIS)) / 100;

	if (data->als_threshold_h >= 65535)
		data->als_threshold_h = 65535;

	apds990x_i2c_write(client,APDS990x_AILTL_REG, data->als_threshold_l,APDS990X_I2C_WORD);
	apds990x_i2c_write(client,APDS990x_AIHTL_REG, data->als_threshold_h,APDS990X_I2C_WORD);
		
}

static void apds990x_reschedule_work(struct apds990x_data *data,
					  unsigned long delay)
{
	/* unsigned long flags; */
	/* als_ps_FLOW("[ALS_PS]reschedule_work enter\n");*/
	/* spin_lock_irqsave(&data->update_lock, flags);*/

	/*
	 * If work is already scheduled then subsequent schedules will not
	 * change the scheduled time that's why we have to cancel it first.
	 */
	cancel_delayed_work(&data->dwork);
	queue_delayed_work(data->ps_wq, &data->dwork, delay);

	/* spin_unlock_irqrestore(&data->update_lock, flags); */
}

/* ALS polling routine */
static void apds990x_als_polling_work_handler(struct work_struct *work)
{
	struct apds990x_data *data = container_of(work, struct apds990x_data, als_dwork.work);
	struct i2c_client *client = data->client;
	int cdata, irdata, pdata;
	int luxValue = 0;
	static unsigned long lastprint_time = 0;
	unsigned char i;

	cdata = apds990x_i2c_read(client, APDS990x_CDATAL_REG,APDS990X_I2C_WORD);
	irdata = apds990x_i2c_read(client,APDS990x_IRDATAL_REG,APDS990X_I2C_WORD);
	pdata = apds990x_i2c_read(client, APDS990x_PDATAL_REG,APDS990X_I2C_WORD);
	
	if(irdata < 0 ||cdata < 0 || pdata < 0)
	{
	   als_ps_ERR("[ALS_PS]apds990x: als read i2c read fail!cdata(%d),irdata(%d),pdata(%d)\n", cdata, irdata, pdata);
	}
	luxValue = LuxCalculation(client, cdata, irdata);
	if(luxValue < 0)
	{
	   input_report_abs(data->input_dev_als, ABS_MISC, lux_old); // report the lux level
	   input_sync(data->input_dev_als);
	   als_ps_ERR("[ALS_PS]apds990x:luxvaule = %d!\n", luxValue);
	   return;
	}
	luxValue = luxValue < 10000 ? luxValue : 10000;
	lux_old = luxValue;

	if (time_after_eq(jiffies, lastprint_time + PRINT_LUX_PERIOD * HZ ))   //print the lux value per 30s
	{
		lastprint_time = jiffies;
		als_ps_INFO("[ALS_PS]: the luxval is %d for period.\n", luxValue);
	}
	else					//the luxval over last luxsection luxval, also print to kmsg
	{
		for (i=0; i<MAX_SECTION; i++)
		{
			if (luxValue <= g_luxsection[i])
				break;
		}

		if ((luxsection != i) && (abs(lastluxvalue-luxValue) >= lux_stepbuff))		//the luxval over last luxsection luxval, also print to kmsg
		{
			luxsection = i;
			lastprint_time = jiffies;	//luxsection changed ,so reset the print period counter
			lastluxvalue = luxValue;   //refresh lastluxvalue
			als_ps_INFO("[ALS_PS]: the luxval is %d for luxsection skip to section%d.\n", luxValue, luxsection);
		}
	}

	/* check PS under sunlight */
	if ((data->ps_detection == 1) && (irdata > 5500)) {

		/* PS was previously in far-to-near condition*/
		/* need to inform input event as there will be no interrupt from the PS */

		/* NEAR-to-FAR detection */
		input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
		input_sync(data->input_dev_ps);

		apds990x_i2c_write(client,APDS990x_PIHTL_REG, NEAR_THRESHOLD(threshold_value),APDS990X_I2C_WORD);
		
		data->pilt = 0;
		data->piht = data->ps_threshold;

		data->ps_detection = 0;	/* near-to-far detected */

		als_ps_FLOW("[ALS_PS]apds_990x_proximity_handler = FAR\n");
	}
	if( als_polling_count <5 )
	{
		if(luxValue == 10000)
			luxValue = luxValue - als_polling_count%2;
		else
			luxValue = luxValue + als_polling_count%2;
		als_polling_count++;
	}
	input_report_abs(data->input_dev_als, ABS_MISC, luxValue); /* report the lux level */
	input_sync(data->input_dev_als);
	/* restart timer */
	schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(data->als_poll_delay));
	 if(DT_tset)
	 {
	 	als_data_count++;
	 }
}

/* PS interrupt routine */
static void apds990x_work_handler(struct work_struct *work)
{
	struct apds990x_data *data = container_of(work,
		struct apds990x_data, dwork.work);
	struct i2c_client *client = data->client;
	int	status;
	int cdata,irdata;

	status = apds990x_i2c_read(client, APDS990x_STATUS_REG,APDS990X_I2C_BYTE);
	irdata = apds990x_i2c_read(client, APDS990x_IRDATAL_REG,APDS990X_I2C_WORD);

	/* disable 990x's ADC first */
	apds990x_i2c_write(client, APDS990x_ENABLE_REG,1,APDS990X_I2C_BYTE);

	als_ps_INFO("[ALS_PS]%s, status = %x ,irdata = %d,data->enable = %#x\n", __func__,status,irdata,data->enable);

	if ((status & data->enable & 0x30) == 0x30) {/*not used*/
		/* both PS and ALS are interrupted */
		apds990x_change_als_threshold(client);

		//cdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_CDATAL_REG);
		cdata = apds990x_i2c_read(client, APDS990x_CDATAL_REG,APDS990X_I2C_WORD);
		if (irdata < 5500)
			apds990x_change_ps_threshold(client);
		else {
			if (data->ps_detection == 1) {
				apds990x_change_ps_threshold(client);
			} else {
				
				als_ps_FLOW("[ALS_PS]Triggered by background ambient noise\n");
			}
		}

		apds990x_set_command(client, 2);	/* 2 = CMD_CLR_PS_ALS_INT */
	} else if ((status & data->enable & 0x20) == 0x20) {
		/* only PS is interrupted */

		/* check if this is triggered by background ambient noise */
		cdata = apds990x_i2c_read(client,APDS990x_CDATAL_REG,APDS990X_I2C_WORD);	
		if (irdata < 5500)
			apds990x_change_ps_threshold(client);
		else {
			if (data->ps_detection == 1) {
				apds990x_change_ps_threshold(client);
			} else {
				als_ps_FLOW("[ALS_PS]Triggered by background ambient noise\n");
			}
		}

		apds990x_set_command(client, 0);	/* 0 = CMD_CLR_PS_INT */
	} else if ((status & data->enable & 0x10) == 0x10) {/*not used*/
		/* only ALS is interrupted */
		apds990x_change_als_threshold(client);

		apds990x_set_command(client, 1);	/* 1 = CMD_CLR_ALS_INT */
	}
	if (1 == data->enable_ps_sensor)
	{
		apds990x_i2c_write(client, APDS990x_ENABLE_REG, 0x27, APDS990X_I2C_BYTE);  //enable ps interrupt and enable PS ALS function
	}
	else
	{
		apds990x_i2c_write(client, APDS990x_ENABLE_REG, data->enable, APDS990X_I2C_BYTE);  //write data->enable to enable register
	}

	enable_irq(data->irq);
}

/* assume this is ISR */
static irqreturn_t apds990x_interrupt(int vec, void *info)
{
	struct i2c_client *client = (struct i2c_client *)info;
	struct apds990x_data *data = i2c_get_clientdata(client);
	wake_lock_timeout(&wlock, 2*HZ);
	disable_irq_nosync(data->irq);
	apds990x_reschedule_work(data, 0);

	return IRQ_HANDLED;
}

/*
 * SysFS support
 */

static ssize_t apds990x_show_enable_ps_sensor(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);

	return snprintf(buf, PAGE_SIZE, "%d\n", data->enable_ps_sensor);
}

static ssize_t apds990x_store_enable_ps_sensor(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);

	als_ps_INFO("[ALS_PS][%s] val=%ld\n", __func__, val);
	als_ps_FLOW("[ALS_PS]%s: enable ps senosr ( %ld)\n", __func__, val);
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
	if ((val != 0) && (val != 1)) {
		als_ps_FLOW("[ALS_PS]%s:store unvalid value=%ld\n", __func__, val);
		return count;
	}

	if (data->ps_lock == 0)
	{
		als_ps_FLOW("[ALS_PS]%s:store unvalid value=%ld\n", __func__, val);
		return count;
	}
	if (val == 1) {
		/*turn on p sensor
		first status is FAR */
		input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
		input_sync(data->input_dev_ps);

		/*ps calibrate*/
		loop = 10;

		if (data->enable_ps_sensor == 0) {

			data->enable_ps_sensor = 1;
			cancel_delayed_work(&data->als_dwork);
			apds990x_set_enable(client,0); /* Power Off */
			apds990x_set_atime(client, 0xfa); /* 27.2ms */
			apds990x_set_ptime(client, 0xff); /* 2.72ms */

			apds990x_set_ppcount(client, ps_pulse_count);
			//apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */
			apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

			apds990x_set_pilt(client, PS_FIRST_LOW_VALUE);
			apds990x_set_piht(client, PS_FIRST_VALUE);

			apds990x_set_ailt( client, 0);
			apds990x_set_aiht( client, 0xffff);

			apds990x_set_pers(client, 0x33); /* 3 persistence */
			apds990x_set_enable(client, 0x27);	 /* only enable PS interrupt */

			schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
			power_key_ps=false;
			schedule_delayed_work(&data->power_work, msecs_to_jiffies(100));
			enable_irq(data->irq);
		}
	}
	 else
	 {
		/*turn off p sensor - kk 25 Apr 2011 we can't turn off the entire sensor, the light sensor may be needed by HAL*/
		data->enable_ps_sensor = 0;
		cancel_delayed_work(&data->power_work);
		if (data->enable_als_sensor) {
			cancel_delayed_work(&data->als_dwork);
			// reconfigute light sensor setting
			apds990x_set_enable(client,0); /* Power Off */
			apds990x_set_atime(client, 0xdb);
			apds990x_set_ailt( client, 0);
			apds990x_set_aiht( client, 0xffff);

			/* modify FAE */
			/* apds990x_set_control(client, 0x20);*/ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

			/* 50mA, IR-diode, 1X PGAIN, 16X AGAIN */
			apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */
			apds990x_set_pers(client, 0x33); /* 3 persistence */

			apds990x_set_enable(client, 0x3);	 /* only enable light sensor */

			schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
		}
		else
		{
			apds990x_set_enable(client, 0);


			/*
			 * If work is already scheduled then subsequent schedules will not
			 * change the scheduled time that's why we have to cancel it first.
			 */
			cancel_delayed_work(&data->als_dwork);
		}
		disable_irq(data->irq);
	}


	return count;
}

static DEVICE_ATTR(enable_ps_sensor, 0664,
				   apds990x_show_enable_ps_sensor, apds990x_store_enable_ps_sensor);

static ssize_t apds990x_show_enable_als_sensor(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);

	return snprintf(buf, PAGE_SIZE, "%d\n", data->enable_als_sensor);
}

static ssize_t apds990x_store_enable_als_sensor(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);

	als_ps_FLOW("[ALS_PS]%s: enable als sensor ( %ld)\n",__func__, val);
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

	if ((val != 0) && (val != 1)) {
		als_ps_FLOW("[ALS_PS]%s: enable als sensor=%ld\n",__func__, val);
		return count;
	}

	als_ps_INFO("[ALS_PS][%s] val=%ld\n", __func__, val);
	if (val == 1) {
		/* turn on light sensor */
		if (data->enable_als_sensor == 0) {
			als_polling_count = 0;
			luxsection = MAX_SECTION;			//make luxsection= 7 to print the luxvalue on first enable ALS
			lastluxvalue = g_luxsection[6]+lux_stepbuff;	//make sure after resume, print the luxval

			data->enable_als_sensor = 1;
			apds990x_set_enable(client, 0); /* Power Off */

			apds990x_set_ailt(client, 0);
			apds990x_set_aiht(client, 0xffff);
			/* modify 1020 */
			/* apds990x_set_control(client, 0x20); */ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */
			apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */
			apds990x_set_pers(client, 0x33); /* 3 persistence */

			if (data->enable_ps_sensor) {
				apds990x_set_atime(client, 0xfa);
				apds990x_set_ptime(client, 0xff); /* 2.72ms */

			/*	apds990x_set_ppcount(client, 8);*/ /* 8-pulse */
				apds990x_set_ppcount(client, ps_pulse_count);
				/* if prox sensor was activated previously */
				apds990x_set_enable(client, 0x27);
			}
			else {
				apds990x_set_atime(client, 0xdb);
				apds990x_set_enable(client, 0x3);	 /* only enable light sensor */
			}
			/*
			if(E_APDS_TYPE_EDGE_N==apds_type)
			{
				tp_color_for_edge = read_tp_color_from_nv();
				als_ps_INFO("[ALS_PS]als:color=%d\n",tp_color_for_edge);
			}
			*/
			/*
			 * If work is already scheduled then subsequent schedules will not
			 * change the scheduled time that's why we have to cancel it first.
			 */
			cancel_delayed_work(&data->als_dwork);
			schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
		}
	} else {
		/*turn off light sensor
		what if the p sensor is active?*/
		data->enable_als_sensor = 0;
		if (data->enable_ps_sensor) {
			apds990x_set_enable(client, 0); /* Power Off */
			apds990x_set_atime(client, 0xfa);  /* 27.2ms */
			apds990x_set_ptime(client, 0xff); /* 2.72ms */
			/*apds990x_set_ppcount(client, 8);*/ /* 8-pulse */
			apds990x_set_ppcount(client, ps_pulse_count);
			/* modify */
			/* apds990x_set_control(client, 0x20); */ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

			/* 50mA, IR-diode, 1X PGAIN, 16X AGAIN */
			apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */

			//apds990x_set_pilt(client, ps_l);
			//apds990x_set_piht(client, ps_h);

			apds990x_set_ailt(client, 0);
			apds990x_set_aiht(client, 0xffff);

			/* 3 persistence */
			apds990x_set_pers(client, 0x33);

			/* only enable prox sensor with interrupt */
			apds990x_set_enable(client, 0x27);
		}
		else {
			apds990x_set_enable(client, 0);
		}

		/*
		 * If work is already scheduled then subsequent schedules will not
		 * change the scheduled time that's why we have to cancel it first.
		 */
		cancel_delayed_work(&data->als_dwork);
	}

	return count;
}

static DEVICE_ATTR(enable_als_sensor, 0664,
				   apds990x_show_enable_als_sensor, apds990x_store_enable_als_sensor);

static ssize_t apds990x_show_als_poll_delay(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);

	/* return in micro-second */
	return snprintf(buf, PAGE_SIZE, "%d\n", data->als_poll_delay*1000);
}

static ssize_t apds990x_store_als_poll_delay(struct device *dev,
					struct device_attribute *attr, const char *buf, size_t count)
{

	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	int poll_delay = 0;
	/*unsigned long flags;*/

    als_ps_INFO("[ALS_PS][%s] val=%ld\n", __func__, val);
	if(DT_tset)
	{
		if(10000!=val)
		{
			return count;
		}
	}
	if (val < 5000)
		val = 5000;	/* minimum 5ms*/

	data->als_poll_delay = val / 1000;	/* convert us => ms */

	/* the minimum is 2.72ms = 2720 us, maximum is 696.32ms */
	poll_delay = 256 - (val / 2720);
	if (poll_delay < 0)
		data->als_atime = 0;
	else
		data->als_atime = poll_delay;
	return count;

}

static DEVICE_ATTR(als_poll_delay, 0664,
				   apds990x_show_als_poll_delay, apds990x_store_als_poll_delay);

static ssize_t apds990x_show_ps_enable(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);

	return snprintf(buf, PAGE_SIZE, "%d\n", data->ps_lock);
}
static ssize_t apds990x_store_ps_enable(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);

    als_ps_INFO("[ALS_PS][%s] val=%lu\n", __func__, val);
	if (val != 0) {
		if (data->enable_ps_sensor == 0) {
			data->ps_lock = 1;
		} else {/*ps opened */
			
			als_ps_FLOW("[ALS_PS]%s:store ps lock value=%u\n", __func__, data->ps_lock);
		}
	} else {
		apds990x_store_enable_ps_sensor(dev,
				attr, buf, count);
		data->ps_lock = 0;

		min_proximity_value = MAX_FAR_THRESHOLD;//MAX_ADC_PROX_VALUE - apds_990x_pwindows_value;
		input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
		input_sync(data->input_dev_ps);
	}
	return count;
}



static DEVICE_ATTR(ps_enable, 0664,
				   apds990x_show_ps_enable, apds990x_store_ps_enable);

static ssize_t apds990x_show_pdata_value(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	data->ps_data = apds990x_i2c_read(client, APDS990x_PDATAL_REG,APDS990X_I2C_WORD);

	return snprintf(buf, PAGE_SIZE, "%d\n", data->ps_data);
}


static DEVICE_ATTR(pdata_value, 0664,
				   apds990x_show_pdata_value, NULL);

static ssize_t apds990x_show_cdata_value(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	int cdata=0;
	cdata = apds990x_i2c_read(client,APDS990x_CDATAL_REG,APDS990X_I2C_WORD);
	
	return snprintf(buf, PAGE_SIZE, "%d\n", cdata);
}

static DEVICE_ATTR(cdata_value, 0664,
				   apds990x_show_cdata_value, NULL);


static ssize_t apds990x_show_rdata_value(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	int rdata=0;
	rdata = apds990x_i2c_read(client,APDS990x_IRDATAL_REG,APDS990X_I2C_WORD);
	return snprintf(buf, PAGE_SIZE, "%d\n", rdata);
}

static DEVICE_ATTR(rdata_value, 0664,
				   apds990x_show_rdata_value, NULL);

static struct attribute *apds990x_attributes[] = {
	&dev_attr_enable_ps_sensor.attr,
	&dev_attr_enable_als_sensor.attr,
	&dev_attr_als_poll_delay.attr,
	&dev_attr_ps_enable.attr,
	&dev_attr_pdata_value.attr,
	&dev_attr_cdata_value.attr,
	&dev_attr_rdata_value.attr,
	&dev_attr_get_reg_value.attr,
	NULL
};


static const struct attribute_group apds990x_attr_group = {
	.attrs = apds990x_attributes,
};

/*
 * Initialization function
 */
static int apds990x_init_client(struct i2c_client *client)
{
	int err;
	int id;

	err = apds990x_set_enable(client, 0);

	if (err < 0) {
		als_ps_ERR("[ALS_PS]%s, apds990x_set_enable failed\n",__func__);
		return err;
	}

	id = apds990x_i2c_read(client,APDS990x_ID_REG,APDS990X_I2C_BYTE);
	if (id == 0x20) {

		als_ps_FLOW("[ALS_PS]APDS-9901, or TMD27711\n");
	} else if (id == 0x29) {

		als_ps_FLOW("[ALS_PS]APDS-9900, or TMD27713\n");
	} else if (id == 0x39) {

		als_ps_FLOW("[ALS_PS]TMD27723\n");
	} else if (id == 0x30) {

		als_ps_FLOW("[ALS_PS]TMD27721\n");
	} else {

		als_ps_FLOW("[ALS_PS]Neither APDS-9901 nor APDS-9901\n");
		return -EIO;
	}
	als_ps_INFO("[ALS_PS]Read apds990x chip ok, ID is 0x%x \n", id);
	apds990x_set_atime(client, 0xDB);	/* 100.64ms ALS integration time*/
	apds990x_set_ptime(client, 0xFF);	/* 2.72ms Prox integration time*/
	apds990x_set_wtime(client, 0xFF);	/* 2.72ms Wait time*/

	apds990x_set_ppcount(client, ps_pulse_count);

	apds990x_set_config(client, 0);		/* no long wait */

	apds990x_set_control(client, 0x62);	/* 50mA, IR-diode, 1X PGAIN, 16X AGAIN*/

	ps_l = PS_FIRST_LOW_VALUE;
	ps_h = PS_FIRST_VALUE;
	apds990x_set_pilt(client, ps_l);		// init threshold for proximity
	apds990x_set_piht(client, ps_h);


	/* init threshold for als*/
	apds990x_set_ailt(client, 0);
	apds990x_set_aiht(client, 0xFFFF);

	/* 2 consecutive Interrupt persistence*/
	apds990x_set_pers(client, 0x22);

	/* sensor is in disabled mode but all the configurations are preset*/

	return 0;
}

static int apds990x_get_gpio(struct apds990x_data *data, struct i2c_client *client)
{
	int rc = 0;
	data->apds_gpio = of_get_named_gpio(client->dev.of_node, "proximity_gpio", 0);
	if (!gpio_is_valid(data->apds_gpio)) {

		als_ps_FLOW("[ALS_PS]%s: apds990x irq gpio is not valid\n", __func__);
		rc = -EINVAL;
	}
	return rc;
}
#if defined(CONFIG_FB)
static int fb_notifier_callback(struct notifier_block *self,unsigned long event, void *data)
{
	int error = 0;
	int i;
	struct fb_event *fb_event = data;
	struct i2c_client *client = this_light_data->client;
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
			if (!this_light_data->enable_ps_sensor && this_light_data->enable_als_sensor) {

				/*modify als resume and disable ps conflicting*/
				als_ps_INFO("[ALS_PS]enable,this_light_data->enable=%d\n",this_light_data->enable);
				apds990x_i2c_write(client,APDS990x_ENABLE_REG, 0x03,APDS990X_I2C_BYTE);
				cancel_delayed_work(&this_light_data->als_dwork);
				schedule_delayed_work(&this_light_data->als_dwork, msecs_to_jiffies(this_light_data->als_poll_delay));
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
			if (!this_light_data->enable_ps_sensor && this_light_data->enable_als_sensor) {

				als_ps_INFO("[ALS_PS]disable\n");
				cancel_delayed_work(&this_light_data->als_dwork);
				apds990x_i2c_write(client,APDS990x_ENABLE_REG,0,APDS990X_I2C_BYTE);
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
/*
 * I2C init/probing/exit functions
 */
static void apds990x_power_screen_handler(struct work_struct *work)
{
	struct apds990x_data *data = container_of(work,struct apds990x_data, power_work.work);
	int i=0;
	int num=0;
	char reg[APDS990X_REG_LEN];

	if(true==power_key_ps)
	{	 
		als_ps_INFO("[ALS_PS][%s] : power_key_ps (%d) press\n",__func__, power_key_ps);
	    power_key_ps=false;
	    input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
        input_sync(data->input_dev_ps);
		/*dump sensor register*/
		for(i = 0; i < APDS990X_REG_LEN; i++ )
		{
			reg[i] = apds990x_i2c_read(data->client,i,APDS990X_I2C_BYTE);

			if(reg[i] <0)
			{
				als_ps_INFO("[ALS_PS]%s,line %d:read %d reg failed\n",__func__,__LINE__,i);
			}
			als_ps_INFO("[ALS_PS]reg[%x]=%x,",i,reg[i]);
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
static int apds_als_poll_delay_set(struct sensors_classdev *sensors_cdev,unsigned int delay_msec)
{
    struct apds990x_data *data = container_of(sensors_cdev,struct apds990x_data, als_cdev);
    unsigned int val = delay_msec;
    int poll_delay = 0;
	/*unsigned long flags;*/
     if(data==NULL)
    {
        als_ps_INFO("[ALS_PS]%s: SET DELAY ERRR\n", __func__);
        return -1;
    }

    als_ps_INFO("[ALS_PS][%s] val=%d\n", __func__, val);
    if (val < 5)
        val = 5;	/* minimum 5ms*/

    data->als_poll_delay = val;	/* convert us => ms */

    /* the minimum is 2.72ms = 2720 us, maximum is 696.32ms */
    poll_delay = 256 - (val*1000 / 2720);
    if (poll_delay < 0)
        data->als_atime = 0;
    else
        data->als_atime = poll_delay;
    return 0;
}

static int apds_als_enable_set(struct sensors_classdev *sensors_cdev,unsigned int enable)
{
    struct apds990x_data *data = container_of(sensors_cdev,struct apds990x_data, als_cdev);
    struct i2c_client *client = data->client;
    unsigned int val=enable;
    int err;
    als_ps_INFO("[ALS_PS]%s: enable=%d,val=%d\n", __func__,enable,val);
    if ((val != 0) && (val != 1)) 
    {
        als_ps_INFO("[ALS_PS]%s: enable als sensor=%d\n",__func__, val);
        return -1;
    }

    if (val == 1) 
    {
    /* turn on light sensor */
        als_ps_INFO("[ALS_PS]%s: data->enable_als_sensor=%d\n", __func__,data->enable_als_sensor);
        if (data->enable_als_sensor == 0) 
        {
            als_ps_INFO("[ALS_PS]%s: enable_als_sensor=%d\n", __func__, data->enable_als_sensor);
            als_polling_count = 0;
            luxsection = MAX_SECTION;			//make luxsection= 7 to print the luxvalue on first enable ALS
            lastluxvalue = g_luxsection[6]+lux_stepbuff;	//make sure after resume, print the luxval

            data->enable_als_sensor = 1;
            apds990x_set_enable(client, 0); /* Power Off */

            apds990x_set_ailt(client, 0);
            apds990x_set_aiht(client, 0xffff);
            /* modify 1020 */
            /* apds990x_set_control(client, 0x20); */ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */
            apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */
            apds990x_set_pers(client, 0x33); /* 3 persistence */

            if (data->enable_ps_sensor) 
            {
                apds990x_set_atime(client, 0xfa);
                apds990x_set_ptime(client, 0xff); /* 2.72ms */

                /*	apds990x_set_ppcount(client, 8);*/ /* 8-pulse */
                apds990x_set_ppcount(client, ps_pulse_count);
                /* if prox sensor was activated previously */
                apds990x_set_enable(client, 0x27);
            }
            else 
            {
                apds990x_set_atime(client, 0xdb);
                apds990x_set_enable(client, 0x3);	 /* only enable light sensor */
            }
            cancel_delayed_work(&data->als_dwork);
            als_ps_INFO("[ALS_PS]%s: start delay work.\n", __func__);
            schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
        }
    }
    else 
    {
        /*turn off light sensor
        what if the p sensor is active?*/
        data->enable_als_sensor = 0;
        if (data->enable_ps_sensor) 
        {
            apds990x_set_enable(client, 0); /* Power Off */
            apds990x_set_atime(client, 0xfa);  /* 27.2ms */
            apds990x_set_ptime(client, 0xff); /* 2.72ms */
            /*apds990x_set_ppcount(client, 8);*/ /* 8-pulse */
            apds990x_set_ppcount(client, ps_pulse_count);
            /* modify */
            /* apds990x_set_control(client, 0x20); */ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

            /* 50mA, IR-diode, 1X PGAIN, 16X AGAIN */
            apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */

            //apds990x_set_pilt(client, ps_l);
            //apds990x_set_piht(client, ps_h);

            apds990x_set_ailt(client, 0);
            apds990x_set_aiht(client, 0xffff);

            /* 3 persistence */
            apds990x_set_pers(client, 0x33);

            /* only enable prox sensor with interrupt */
            apds990x_set_enable(client, 0x27);
        }
        else 
        {
            apds990x_set_enable(client, 0);
        }

        /*
        * If work is already scheduled then subsequent schedules will not
        * change the scheduled time that's why we have to cancel it first.
        */
        cancel_delayed_work(&data->als_dwork);
    }
    return 0;
}
static int apds_ps_enable_set(struct sensors_classdev *sensors_cdev,unsigned int enable)
{
    struct apds990x_data *data = container_of(sensors_cdev,struct apds990x_data, ps_cdev);
    struct i2c_client *client = data->client;
    unsigned int val=enable;
    int err;
    als_ps_INFO("[ALS_PS]%s: enable=%d,val=%d\n", __func__,enable,val);
    if ((val != 0) && (val != 1)) 
    {
        als_ps_INFO("[ALS_PS]%s: enable als sensor=%d\n",__func__, val);
        return -1;
    }

    if (val == 1) 
    {
        /*turn on p sensor
        first status is FAR */
        input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
        input_sync(data->input_dev_ps);

        /*ps calibrate*/
        loop = 10;

        if (data->enable_ps_sensor == 0) 
        {
            data->enable_ps_sensor = 1;
            cancel_delayed_work(&data->als_dwork);
            apds990x_set_enable(client,0); /* Power Off */
            apds990x_set_atime(client, 0xfa); /* 27.2ms */
            apds990x_set_ptime(client, 0xff); /* 2.72ms */

            apds990x_set_ppcount(client, ps_pulse_count);
            //apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */
            apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

            apds990x_set_pilt(client, PS_FIRST_LOW_VALUE);
            apds990x_set_piht(client, PS_FIRST_VALUE);

            apds990x_set_ailt( client, 0);
            apds990x_set_aiht( client, 0xffff);

            apds990x_set_pers(client, 0x33); /* 3 persistence */
            apds990x_set_enable(client, 0x27);	 /* only enable PS interrupt */

            schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
            power_key_ps=false;
            schedule_delayed_work(&data->power_work, msecs_to_jiffies(100));
            enable_irq(data->irq);
        }
    }
    else
    {
        /*turn off p sensor - kk 25 Apr 2011 we can't turn off the entire sensor, the light sensor may be needed by HAL*/
        data->enable_ps_sensor = 0;
        cancel_delayed_work(&data->power_work);
        if (data->enable_als_sensor) 
        {
            cancel_delayed_work(&data->als_dwork);
            // reconfigute light sensor setting
            apds990x_set_enable(client,0); /* Power Off */
            apds990x_set_atime(client, 0xdb);
            apds990x_set_ailt( client, 0);
            apds990x_set_aiht( client, 0xffff);

            /* modify FAE */
            /* apds990x_set_control(client, 0x20);*/ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

            /* 50mA, IR-diode, 1X PGAIN, 16X AGAIN */
            apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */
            apds990x_set_pers(client, 0x33); /* 3 persistence */

            apds990x_set_enable(client, 0x3);	 /* only enable light sensor */

            schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
        }
        else
        {
            apds990x_set_enable(client, 0);


            /*
            * If work is already scheduled then subsequent schedules will not
            * change the scheduled time that's why we have to cancel it first.
            */
            cancel_delayed_work(&data->als_dwork);
        }
        disable_irq(data->irq);
    }
    return 0;
}
static struct i2c_driver apds990x_driver;
static int apds990x_probe(struct i2c_client *client,
				   const struct i2c_device_id *id)
{
	struct apds990x_data *data;
	struct device_node *node = client->dev.of_node;
	int err = 0;
	int error = 1;
	data = kzalloc(sizeof(struct apds990x_data), GFP_KERNEL);
	if (NULL == data) {
		err = -ENOMEM;
		goto exit;
	}
		 /* set regulator*/

	error = apds990x_regulator_configure(data, client);
	if (error) {
		als_ps_ERR("[ALS_PS]Failed to intialize hardware\n");
		goto exit_kfree;
	}
	apds990x_regulator_enable(data);
       msleep(10);

	err = apds990x_get_gpio(data, client);
	if (err<0) {
		als_ps_ERR("[ALS_PS]Failed to intialize hardware\n");
		goto exit_kfree;
	}
	err = of_property_read_u32(node, "apds_type", &apds_type);
	if (err) {
		als_ps_ERR("[ALS_PS]apds_typel read failed:%d\n", err);
		goto exit_kfree;
	}

	if(0==apds_type)
	{
		apds_990x_pwave_value = 115;
		threshold_value = 120;
		apds_990x_pwindows_value = 170;
		ps_pulse_count=8;
	}
	else if(1 == apds_type)
	{
		apds_990x_pwave_value = 115;
		threshold_value = 120;
		apds_990x_pwindows_value = 170;
		ps_pulse_count=8;
	}
	else if(2 == apds_type)
	{
		apds_990x_pwave_value = 115;
		threshold_value = 120;
		apds_990x_pwindows_value = 170;
		ps_pulse_count=8;
	}
	else
	{
		apds_990x_pwave_value = 250;
		threshold_value = 400;
		apds_990x_pwindows_value = 100;
		ps_pulse_count=3;
	}
	min_proximity_value = MAX_FAR_THRESHOLD;//MAX_ADC_PROX_VALUE - apds_990x_pwindows_value;

	if (!i2c_check_functionality(client->adapter,
		I2C_FUNC_SMBUS_BYTE)) {
        als_ps_INFO("[ALS_PS]-------------i2c check error!--------\n");
		err = -ENODEV;
		goto exit;
	}

	data->client = client;
	i2c_set_clientdata(client, data);

	data->enable = 0;	/* default mode is standard */
	data->ps_lock = 1; /* default ps can be opened*/
	data->ps_threshold = 0;
	data->ps_hysteresis_threshold = 0;
	data->ps_detection = 0;	/* default to no detection */
	data->enable_als_sensor = 0;	/* default to 0 */
	data->enable_ps_sensor = 0;	/* default to 0 */
	/*data->als_poll_delay = 100;*/	/* default to 100ms*/
	data->als_poll_delay = 500;	/* default to 500ms*/
	data->als_atime	= 0xdb;			/* work in conjuction with als_poll_delay*/
	data->irq = gpio_to_irq(data->apds_gpio);

	als_ps_FLOW("[ALS_PS]enable = %x\n", data->enable);

	mutex_init(&data->update_lock);
	mutex_init(&data->single_lock);
	data->ps_wq = create_singlethread_workqueue("ps_wq");
	if (!data->ps_wq) {
		als_ps_ERR("[ALS_PS]failed to create ps workqueue!\n");
		goto exit_kfree;
	}
	INIT_DELAYED_WORK(&data->dwork, apds990x_work_handler);
	INIT_DELAYED_WORK(&data->als_dwork, apds990x_als_polling_work_handler);
	INIT_DELAYED_WORK(&data->power_work,apds990x_power_screen_handler);
	/* Initialize the APDS990x chip */
	err = apds990x_init_client(client);
	if (err)
		goto exit_kfree;

	err = gpio_request(data->apds_gpio, "gpio_3_5");
	if (err) {
		als_ps_ERR("[ALS_PS]%s: failed to request gpio int1 for irq\n",__func__);	
		goto exit_kfree;
	}

	err = gpio_direction_input(data->apds_gpio);
	if (err) {
		als_ps_ERR("[ALS_PS]%s: failed to config gpio direction\n",__func__);	
		goto exit_gpio_request;
	}

	/* Initialize wakelock*/
	wake_lock_init(&wlock, WAKE_LOCK_SUSPEND, "apds990x");

	err = request_irq(data->irq, apds990x_interrupt,
			IRQF_DISABLED | IRQ_TYPE_LEVEL_LOW | IRQF_NO_SUSPEND,
						APDS990x_DRV_NAME, (void *)client);
	if (err) {
		als_ps_ERR("[ALS_PS]%s  allocate APDS990x_IRQ failed.\n",__func__);	
		goto exit_gpio_request;
	}
	disable_irq(data->irq);
    als_ps_FLOW("[ALS_PS]%s interrupt is hooked\n", __func__);

	/* Register to Input Device */
	data->input_dev_als = input_allocate_device();
	if (!data->input_dev_als) {
		err = -ENOMEM;
		als_ps_ERR("[ALS_PS]%s, Failed to allocate input device als\n",__func__);
		goto exit_free_irq;
	}

	data->input_dev_ps = input_allocate_device();
	if (!data->input_dev_ps) {
		err = -ENOMEM;

		als_ps_ERR("[ALS_PS]%s, Failed to allocate input device ps\n",__func__);
		goto exit_free_dev_als;
	}

	data->input_dev_als->name = ALS_INPUT_DEV_NAME;
	data->input_dev_als->id.bustype = BUS_I2C;
	data->input_dev_als->dev.parent = &data->client->dev;
	data->input_dev_ps->name = PS_INPUT_DEV_NAME;
	data->input_dev_ps->id.bustype = BUS_I2C;
	data->input_dev_ps->dev.parent = &data->client->dev;

	set_bit(EV_ABS, data->input_dev_als->evbit);
	set_bit(EV_ABS, data->input_dev_ps->evbit);

	input_set_abs_params(data->input_dev_als, ABS_MISC, 0, 10000, 0, 0);
	input_set_abs_params(data->input_dev_ps, ABS_DISTANCE, 0, 1, 0, 0);

	err = input_register_device(data->input_dev_als);
	if (err) {
		als_ps_ERR("[ALS_PS]%s, Unable to register input device als: %s\n", __func__, data->input_dev_als->name);
		goto exit_free_dev_ps;
	}

	err = input_register_device(data->input_dev_ps);
	if (err) {
		als_ps_ERR("[ALS_PS]%s,Unable to register input device ps: %s\n",__func__, data->input_dev_ps->name);
		goto exit_unregister_dev_als;
	}
       /*register sensor class*/
       data->als_cdev=apds_als_cdev;
       data->als_cdev.sensors_enable=apds_als_enable_set;
       data->als_cdev.sensors_poll_delay=apds_als_poll_delay_set;
       err = sensors_classdev_register(&client->dev, &data->als_cdev);
       if (err) 
       {
            als_ps_ERR("[ALS_PS]unable to register sensors_classdev: %d\n",err);
       }
       data->ps_cdev=apds_ps_cdev;
       data->ps_cdev.sensors_enable=apds_ps_enable_set;
       data->ps_cdev.sensors_poll_delay=NULL;
       err = sensors_classdev_register(&client->dev, &data->ps_cdev);
       if (err) 
       {
            als_ps_ERR("[ALS_PS]unable to register sensors_classdev: %d\n",err);
       }
         
#if defined(CONFIG_FB)
		fb_light.fb_notify.notifier_call = fb_notifier_callback;
		err = fb_register_client(&fb_light.fb_notify);
		if (err){
			als_ps_ERR("[ALS_PS]unable to register fb_notifier: %d\n",err);
			goto exit_unregister_dev_als;
		 }
#endif

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &apds990x_attr_group);
	if (err) {
		als_ps_ERR("[ALS_PS]%s, sysfs_create_group failed\n", __func__);
		goto exit_unregister_dev_ps;
	}

#ifdef CONFIG_HUAWEI_SENSORS_INPUT_INFO
	if(0 == apds_type) {
		err = set_sensor_chip_info(PS, "AVAGO APDS9930 or TAOS TMD27723");
		err = set_sensor_chip_info(ALS, "AVAGO APDS9930 or TAOS TMD27723");
		}
	else {
		err = set_sensor_chip_info(PS, "AVAGO APDS9900 or TAOS TMD27713");
		err = set_sensor_chip_info(ALS, "AVAGO APDS9900 or TAOS TMD27713");
		}

	if (err) {
		als_ps_ERR("[ALS_PS]set_PS_sensor_chip_info error\n");
	    }
#endif

	als_ps_FLOW("[ALS_PS]%s support ver. %s enabled\n",__func__, DRIVER_VERSION);

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
        set_hw_dev_flag(DEV_I2C_L_SENSOR);
#endif
 //     apds990x_regulator_disable(data);
	this_light_data =data;
#if defined (CONFIG_HUAWEI_DSM)
    apds990x_als_ps_init_flag=1;
#endif
	als_ps_INFO("[ALS_PS][%s]: ok\n",__func__);
	return 0;

exit_unregister_dev_ps:
	input_unregister_device(data->input_dev_ps);
exit_unregister_dev_als:
	input_unregister_device(data->input_dev_als);
exit_free_dev_ps:
	input_free_device(data->input_dev_ps);
exit_free_dev_als:
	input_free_device(data->input_dev_als);
exit_free_irq:
	if (data->irq >= 0)
	free_irq(data->irq, client);
exit_gpio_request:
	if (data->irq >= 0)
	gpio_free(data->apds_gpio);
exit_kfree:
        if (data->ps_wq)
		destroy_workqueue(data->ps_wq);
	i2c_set_clientdata(client, NULL);
	kfree(data);
	data = NULL;


exit:
	als_ps_INFO("[ALS_PS][%s]: failed\n",__func__);
	return err;
}

static int apds990x_remove(struct i2c_client *client)
{
	struct apds990x_data *data = i2c_get_clientdata(client);

	input_unregister_device(data->input_dev_als);
	input_unregister_device(data->input_dev_ps);

	input_free_device(data->input_dev_als);
	input_free_device(data->input_dev_ps);

	if (data->irq >= 0) {
		free_irq(data->irq, client);
		gpio_free(data->apds_gpio );
	}

        if (data->ps_wq)
		destroy_workqueue(data->ps_wq);

	sysfs_remove_group(&client->dev.kobj, &apds990x_attr_group);
	/* Power down the device */
	apds990x_set_enable(client, 0);
	i2c_set_clientdata(client, NULL);
#if defined(CONFIG_FB)
	if (fb_unregister_client(&fb_light.fb_notify))
		als_ps_ERR("[ALS_PS]light:error occurred while unregistering fb_notifier.\n");
#endif
	kfree(data);
	data = NULL;

	return 0;
}

static void apds990x_shutdown(struct i2c_client *client)
{
	struct apds990x_data *data = i2c_get_clientdata(client);

    als_ps_INFO("[ALS_PS][%s] +\n", __func__);
	if (data->irq >= 0) {
		free_irq(data->irq, client);
	}

	cancel_delayed_work(&data->dwork);
	cancel_delayed_work(&data->als_dwork);

	/* Power down the device */
	apds990x_set_enable(client, 0);

	wake_lock_destroy(&wlock);

	als_ps_INFO("[ALS_PS][%s] -\n", __func__);
}

static const struct of_device_id apds990x_of_match[] = {
	{.compatible = "huawei,apds990x",},
	{},
};
MODULE_DEVICE_TABLE(of, apds990x_of_match);

static const struct i2c_device_id apds990x_id[] = {
	{APDS990x_DRV_NAME, 0 },
	{ },
};
MODULE_DEVICE_TABLE(i2c, apds990x_id);

static struct i2c_driver apds990x_driver = {
	.driver = {
		.name	= APDS990x_DRV_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = apds990x_of_match,
	},
	.probe	= apds990x_probe,
	//.probe	= NULL,
	.remove	= apds990x_remove,
	//.shutdown = apds990x_shutdown,
	.id_table = apds990x_id,
};

static int __init apds990x_init(void)
{
	return i2c_add_driver(&apds990x_driver);
}

static void __exit apds990x_exit(void)
{
	i2c_del_driver(&apds990x_driver);
}

MODULE_AUTHOR("Lee Kai Koon <kai-koon.lee@avagotech.com>");
MODULE_DESCRIPTION("APDS990x ambient light + proximity sensor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

module_init(apds990x_init);
module_exit(apds990x_exit);

