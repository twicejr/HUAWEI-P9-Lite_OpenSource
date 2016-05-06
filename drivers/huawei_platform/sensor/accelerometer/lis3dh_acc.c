/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
 *
 * File Name          : lis3dh_acc.c
 * Authors            : MSH - Motion Mems BU - Application Team
 *		      : Matteo Dameno (matteo.dameno@st.com)
 *		      : Carmine Iascone (carmine.iascone@st.com)
 *		      : Both authors are willing to be considered the contact
 *		      : and update points for the driver.
 * Version            : V.1.0.8
 * Date               : 2010/Apr/01
 * Description        : LIS3DH accelerometer sensor API
 *
 *******************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THE PRESENT SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES
 * OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, FOR THE SOLE
 * PURPOSE TO SUPPORT YOUR APPLICATION DEVELOPMENT.
 * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * THIS SOFTWARE IS SPECIFICALLY DESIGNED FOR EXCLUSIVE USE WITH ST PARTS.
 *
 ******************************************************************************
 Revision 1.0.0 05/11/09
 First Release;
 Revision 1.0.3 22/01/2010
  Linux K&R Compliant Release;
 Revision 1.0.5 16/08/2010
  modified _get_acceleration_data function;
  modified _update_odr function;
  manages 2 interrupts;
 Revision 1.0.6 15/11/2010
  supports sysfs;
  no more support for ioctl;
 Revision 1.0.7 26/11/2010
  checks for availability of interrupts pins
  correction on FUZZ and FLAT values;
 Revision 1.0.8 2010/Apr/01
  corrects a bug in interrupt pin management in 1.0.7

 ******************************************************************************/

/*==============================================================================
History

Problem NO.         Name        Time         Reason

==============================================================================*/


#include	<linux/err.h>
#include	<linux/errno.h>
#include	<linux/delay.h>
#include	<linux/fs.h>
#include	<linux/i2c.h>
#include	<linux/input.h>
#include	<linux/uaccess.h>
#include	<linux/workqueue.h>
#include	<linux/irq.h>
#include	<linux/gpio.h>
#include	<linux/interrupt.h>
#include	<linux/slab.h>
#include <huawei_platform/sensor/sensor_info.h>
#include    "lis3dh.h"
#include	<linux/sensors.h>
#include <linux/board_sensors.h>
#include	<asm/io.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#include <linux/of.h>
#include <linux/module.h>
#include <linux/moduleparam.h>	
//#define GPIO_BOLCK_NAME "block_gsensor"
#if defined(CONFIG_FB)
#include <linux/notifier.h>
#include <linux/fb.h>

static struct lis3dh_acc_data   fb_lis_acc;
static struct lis3dh_acc_data  *this_gs_data;
#endif
#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#include <linux/mfd/hisi_hi6xxx_pmic.h>
extern struct dsm_client *gsensor_dclient;
static int lis3dh_acc_flag = 0;
#endif
extern bool DT_tset;
extern int Gsensor_data_count;
static int16_t accl_data[3] = {0, 0, 0};
static struct  Gsensor_excep st_excep;

struct  lis3dh_odr_table{
	unsigned int cutoff_ms;
	unsigned int mask;
};
static struct lis3dh_odr_table lis3dh_acc_odr_table[] = {
		{    1, ODR1250 },
		{    3, ODR400  },
		{    5, ODR200  },
		{   10, ODR100  },
		{   20, ODR50   },
		{   40, ODR25   },
		{  100, ODR10   },
		{ 1000, ODR1    },
};
/*sensor class*/
static struct sensors_classdev lis3dh_acc_cdev = {
       .path_name="acc_sensor",
	.name = "3-axis Accelerometer sensor",
	.vendor = "ST_LIS3DH",
	.version = 1,
	.handle = SENSORS_ACCELERATION_HANDLE,
	.type = SENSOR_TYPE_ACCELEROMETER,
	.max_range = "39.02266",
	.resolution = "0.009576807",
	.sensor_power = "0.23",
	.min_delay = 10000,
	.delay_msec = 200,
	.fifo_reserved_event_count = 0,
	.fifo_max_event_count = 0,
	.enabled = 0,
	.sensors_enable = NULL,
	.sensors_poll_delay = NULL,
};

struct lis3dh_acc_data {
	struct i2c_client *client;
	struct lis3dh_acc_platform_data *pdata;

	struct mutex lock;
	struct delayed_work input_work;

	struct input_dev *input_dev;
    struct sensors_classdev cdev;

	int hw_initialized;

	atomic_t enabled;
	int on_before_suspend;

	u8 sensitivity;

	u8 resume_state[RESUME_ENTRIES];

	int irq1;
	struct work_struct irq1_work;
	struct workqueue_struct *irq1_work_queue;
	int irq2;
	struct work_struct irq2_work;
	struct workqueue_struct *irq2_work_queue;

#ifdef DEBUG
	u8 reg_addr;
#endif
#if defined(CONFIG_FB)
	struct notifier_block fb_notify;
#endif
};
static int lis3dh_acc_i2c_read(struct lis3dh_acc_data *acc,
				u8 *buf, int len)
{
	int err;
	int tries = 0;
#if defined (CONFIG_HUAWEI_DSM)
	unsigned char LDO2_status=0;
	unsigned char LDO5_status=0;
#endif
	struct i2c_msg	msgs[] = {
		{
			.addr = acc->client->addr,
			.flags = acc->client->flags & I2C_M_TEN,
			.len = 1,
			.buf = buf,
		},
		{
			.addr = acc->client->addr,
			.flags = (acc->client->flags & I2C_M_TEN) | I2C_M_RD,
			.len = len,
			.buf = buf,
		},
	};

	do {
		err = i2c_transfer(acc->client->adapter, msgs, 2);
		if (err != 2)
			msleep_interruptible(I2C_RETRY_DELAY);
	} while ((err != 2) && (++tries < I2C_RETRIES));

	if (err != 2) {
#if defined (CONFIG_HUAWEI_DSM)
		if(1==lis3dh_acc_flag)
		 {
			if(!dsm_client_ocuppy(gsensor_dclient))
			{
			//gpio_get_value(this_gs_data->pdata->gpio_int1);

		    LDO2_status = hi6xxx_pmic_reg_read(LDO2_PHYS_ADDR);
		    LDO5_status = hi6xxx_pmic_reg_read(LDO5_PHYS_ADDR);
			printk("LDO2_status=%d ### \n",LDO2_status);
	        printk("LDO5_status=%d ### \n",LDO5_status);
		   dsm_client_record(gsensor_dclient,"LDO2_status is 0x%x.\nLDO5_status is 0x%x\nI2C_status:%d.\n",\
			LDO2_status, LDO5_status, err);

		  dsm_client_notify(gsensor_dclient, DSM_GSENSOR_I2C_RW_ERROR_NO);
			}
		 }
#endif
		gs_ERR("[GS]read transfer error\n");
		err = -EIO;
	} else {
		err = 0;
	}

	return err;
}

static int lis3dh_acc_i2c_write(struct lis3dh_acc_data *acc, u8 * buf, int len)
{
	int err;
	int tries = 0;
#if defined (CONFIG_HUAWEI_DSM)
    unsigned char LDO2_status=0;
	unsigned char LDO5_status=0;
#endif
	struct i2c_msg msgs[] = {
		{
			.addr = acc->client->addr,
			.flags = acc->client->flags & I2C_M_TEN,
			.len = len + 1,
			.buf = buf,
		},
	};

	do {
		err = i2c_transfer(acc->client->adapter, msgs, 1);
		if (err != 1)
			msleep_interruptible(I2C_RETRY_DELAY);
	} while ((err != 1) && (++tries < I2C_RETRIES));

	if (err != 1) {
#if defined (CONFIG_HUAWEI_DSM)
		if(1==lis3dh_acc_flag)
		{
			if(!dsm_client_ocuppy(gsensor_dclient))
			{
			    //gpio_get_value(this_gs_data->pdata->gpio_int1);
				//dsm_client_record(gsensor_dclient, "[%s]i2c_status:%d.\n",__func__, err);
			LDO2_status = hi6xxx_pmic_reg_read(LDO2_PHYS_ADDR);
		    LDO5_status = hi6xxx_pmic_reg_read(LDO5_PHYS_ADDR);
			printk("LDO2_status=%d ### \n",LDO2_status);
	        printk("LDO5_status=%d ### \n",LDO5_status);
		   dsm_client_record(gsensor_dclient,"LDO2_status is 0x%x.\nLDO5_status is 0x%x\nI2C_status:%d.\n",\
			LDO2_status, LDO5_status, err);
		   dsm_client_notify(gsensor_dclient, DSM_GSENSOR_I2C_RW_ERROR_NO);
			}
		}
#endif
		gs_ERR("[GS]write transfer error\n");
		err = -EIO;
	} else {
		err = 0;
	}

	return err;
}

static int lis3dh_acc_hw_init(struct lis3dh_acc_data *acc)
{
	int err = -1;
	u8 buf[6] = {0};

	gs_FLOW("[GS]%s: hw init start\n", LIS3DH_ACC_DEV_NAME);

	buf[0] = CFG1;
	err = lis3dh_acc_i2c_read(acc, buf, 1);
	if (err < 0) {
		goto err_resume_state;
	}
	/* set the highest bit of CFG1 register for disable "SA0" pull up mode */
	buf[1] = buf[0]|0x80;
	buf[0] = CFG1;
	err = lis3dh_acc_i2c_write(acc, buf, 1);
	if (err < 0) {
		goto err_resume_state;
	}

	buf[0] = CFG1;
	err = lis3dh_acc_i2c_read(acc, buf, 1);
	if (err < 0) {
		goto err_resume_state;
	}
	/* check CFG1[7] is set to 1*/
	if ((buf[0] & 0x80) != 0x80) {
		gs_ERR("[GS]pull up disable failed 0x%x\n", buf[0]);
		goto err_resume_state;
	}

	buf[0] = CTRL_REG1;
	buf[1] = acc->resume_state[RES_CTRL_REG1];
	err = lis3dh_acc_i2c_write(acc, buf, 1);
	if (err < 0)
		goto err_resume_state;

	buf[0] = TEMP_CFG_REG;
	buf[1] = acc->resume_state[RES_TEMP_CFG_REG];
	err = lis3dh_acc_i2c_write(acc, buf, 1);
	if (err < 0)
		goto err_resume_state;

	buf[0] = FIFO_CTRL_REG;
	buf[1] = acc->resume_state[RES_FIFO_CTRL_REG];
	err = lis3dh_acc_i2c_write(acc, buf, 1);
	if (err < 0)
		goto err_resume_state;

	buf[0] = (I2C_AUTO_INCREMENT | TT_THS);
	buf[1] = acc->resume_state[RES_TT_THS];
	buf[2] = acc->resume_state[RES_TT_LIM];
	buf[3] = acc->resume_state[RES_TT_TLAT];
	buf[4] = acc->resume_state[RES_TT_TW];
	err = lis3dh_acc_i2c_write(acc, buf, 4);
	if (err < 0)
		goto err_resume_state;
	buf[0] = TT_CFG;
	buf[1] = acc->resume_state[RES_TT_CFG];
	err = lis3dh_acc_i2c_write(acc, buf, 1);
	if (err < 0)
		goto err_resume_state;

	buf[0] = (I2C_AUTO_INCREMENT | INT_THS1);
	buf[1] = acc->resume_state[RES_INT_THS1];
	buf[2] = acc->resume_state[RES_INT_DUR1];
	err = lis3dh_acc_i2c_write(acc, buf, 2);
	if (err < 0)
		goto err_resume_state;
	buf[0] = INT_CFG1;
	buf[1] = acc->resume_state[RES_INT_CFG1];
	err = lis3dh_acc_i2c_write(acc, buf, 1);
	if (err < 0)
		goto err_resume_state;

	buf[0] = (I2C_AUTO_INCREMENT | CTRL_REG2);
	buf[1] = acc->resume_state[RES_CTRL_REG2];
	buf[2] = acc->resume_state[RES_CTRL_REG3];
	buf[3] = acc->resume_state[RES_CTRL_REG4];
	buf[4] = acc->resume_state[RES_CTRL_REG5];
	buf[5] = acc->resume_state[RES_CTRL_REG6];
	err = lis3dh_acc_i2c_write(acc, buf, 5);
	if (err < 0)
		goto err_resume_state;

	acc->hw_initialized = 1;

	gs_FLOW("[GS]%s: hw init done\n", LIS3DH_ACC_DEV_NAME);
	return 0;

err_resume_state:
	acc->hw_initialized = 0;
	gs_ERR("[GS]hw init error 0x%x,0x%x: %d\n", buf[0],buf[1], err);	
	return err;
}

static void lis3dh_acc_device_power_off(struct lis3dh_acc_data *acc)
{
	int err;
	u8 buf[2] = { CTRL_REG1, LIS3DH_ACC_PM_OFF };

	err = lis3dh_acc_i2c_write(acc, buf, 1);
	if (err < 0)
        gs_ERR("[GS]soft power off failed: %d\n", err);
	if (acc->pdata->power_off) {
		if (acc->pdata->gpio_int1)
			disable_irq_nosync(acc->irq1);
		if (acc->pdata->gpio_int2)
			disable_irq_nosync(acc->irq2);
		acc->pdata->power_off();
		acc->hw_initialized = 0;
	}
	if (acc->hw_initialized) {
		if (acc->pdata->gpio_int1)
			disable_irq_nosync(acc->irq1);
		if (acc->pdata->gpio_int2)
			disable_irq_nosync(acc->irq2);
		acc->hw_initialized = 0;
	}
}

static int lis3dh_acc_device_power_on(struct lis3dh_acc_data *acc)
{
	int err = -1;

	if (acc->pdata->power_on) {
		err = acc->pdata->power_on();
		if (err < 0) {
			gs_ERR("[GS]lis3dh power_on failed: %d\n", err);
			return err;
		}
		if (acc->pdata->gpio_int1 >= 0)
			enable_irq(acc->irq1);
		if (acc->pdata->gpio_int2 >= 0)
			enable_irq(acc->irq2);
	}

	if (!acc->hw_initialized) {
		err = lis3dh_acc_hw_init(acc);
		if (err < 0) {
			lis3dh_acc_device_power_off(acc);
			return err;
		}
	}

	if (acc->hw_initialized) {
		if (acc->pdata->gpio_int1 >= 0)
			enable_irq(acc->irq1);
		if (acc->pdata->gpio_int2 >= 0)
			enable_irq(acc->irq2);
	}
	return 0;
}

static irqreturn_t lis3dh_acc_isr1(int irq, void *dev)
{
	struct lis3dh_acc_data *acc = dev;

	disable_irq_nosync(irq);
	queue_work(acc->irq1_work_queue, &acc->irq1_work);
    gs_FLOW("[GS]%s: isr1 queued\n", LIS3DH_ACC_DEV_NAME);
	return IRQ_HANDLED;
}

static irqreturn_t lis3dh_acc_isr2(int irq, void *dev)
{
	struct lis3dh_acc_data *acc = dev;

	disable_irq_nosync(irq);
	queue_work(acc->irq2_work_queue, &acc->irq2_work);
    gs_FLOW("[GS]%s: isr2 queued\n", LIS3DH_ACC_DEV_NAME);
	return IRQ_HANDLED;
}

static void lis3dh_acc_irq1_work_func(struct work_struct *work)
{

	struct lis3dh_acc_data *acc =
	container_of(work, struct lis3dh_acc_data, irq1_work);
	/* TODO  add interrupt service procedure.
		 ie:lis3dh_acc_get_int1_source(acc); */
	gs_FLOW("[GS]%s: IRQ1 triggered\n", LIS3DH_ACC_DEV_NAME);
	enable_irq(acc->irq1);
}

static void lis3dh_acc_irq2_work_func(struct work_struct *work)
{
	struct lis3dh_acc_data *acc =
	container_of(work, struct lis3dh_acc_data, irq2_work);
	/* TODO  add interrupt service procedure.
		 ie:lis3dh_acc_get_tap_source(acc); */
	gs_FLOW("[GS]%s: IRQ2 triggered\n", LIS3DH_ACC_DEV_NAME);
	enable_irq(acc->irq2);
}

static int lis3dh_acc_update_g_range(struct lis3dh_acc_data *acc, u8 new_g_range)
{
	int err = -1;

	u8 sensitivity;
	u8 buf[2];
	u8 updated_val;
	u8 init_val;
	u8 new_val;
	u8 mask = LIS3DH_ACC_FS_MASK | HIGH_RESOLUTION;

	switch (new_g_range) {
	case LIS3DH_ACC_G_2G:

		sensitivity = SENSITIVITY_2G;
		break;
	case LIS3DH_ACC_G_4G:

		sensitivity = SENSITIVITY_4G;
		break;
	case LIS3DH_ACC_G_8G:

		sensitivity = SENSITIVITY_8G;
		break;
	case LIS3DH_ACC_G_16G:

		sensitivity = SENSITIVITY_16G;
		break;
	default:
		gs_ERR("[GS]invalid g range requested: %u\n",new_g_range);
		return -EINVAL;
	}

	if (atomic_read(&acc->enabled)) {
		/* Updates configuration register 4,
		* which contains g range setting */
		buf[0] = CTRL_REG4;
		err = lis3dh_acc_i2c_read(acc, buf, 1);
		if (err < 0)
			goto error;
		init_val = buf[0];
		acc->resume_state[RES_CTRL_REG4] = init_val;
		new_val = new_g_range | HIGH_RESOLUTION;
		updated_val = ((mask & new_val) | ((~mask) & init_val));
		buf[1] = updated_val;
		buf[0] = CTRL_REG4;
		err = lis3dh_acc_i2c_write(acc, buf, 1);
		if (err < 0)
			goto error;
		acc->resume_state[RES_CTRL_REG4] = updated_val;
		acc->sensitivity = sensitivity;
	}

	return err;
error:
	 gs_ERR("[GS]update g range failed 0x%x,0x%x: %d\n",buf[0], buf[1], err);
	return err;
}

static int lis3dh_acc_update_odr(struct lis3dh_acc_data *acc, int poll_interval_ms)
{
	int err = -1;
	int i;
	u8 config[2];

	/* Following, looks for the longest possible odr interval scrolling the
	 * odr_table vector from the end (shortest interval) backward (longest
	 * interval), to support the poll_interval requested by the system.
	 * It must be the longest interval lower then the poll interval.*/
	for (i = ARRAY_SIZE(lis3dh_acc_odr_table) - 1; i >= 0; i--) {
		if (lis3dh_acc_odr_table[i].cutoff_ms <= poll_interval_ms)
			break;
	}

	config[1] = lis3dh_acc_odr_table[i].mask;
	config[1] |= LIS3DH_ACC_ENABLE_ALL_AXES;
	/* If device is currently enabled, we need to write new
	 *  configuration out to it */
	if (atomic_read(&acc->enabled)) {
		config[0] = CTRL_REG1;
		err = lis3dh_acc_i2c_write(acc, config, 1);
		if (err < 0)
			goto error;
		acc->resume_state[RES_CTRL_REG1] = config[1];
	}
	return err;

error:
	gs_ERR("[GS]update odr failed 0x%x,0x%x: %d\n",
			config[0], config[1], err);	
	return err;
}

static int lis3dh_acc_register_write(struct lis3dh_acc_data *acc, u8 *buf,
		u8 reg_address, u8 new_value)
{
	int err = -1;

	/* Sets configuration register at reg_address
	*  NOTE: this is a straight overwrite  */
	buf[0] = reg_address;
	buf[1] = new_value;
	err = lis3dh_acc_i2c_write(acc, buf, 1);
	if (err < 0) {
		gs_ERR("[GS]write register failed 0x%x: %d\n", reg_address, err);
		return err;
	}
	return err;
}

static volatile int lis3dh_debug = 0;

static int lis3dh_acc_get_acceleration_data(struct lis3dh_acc_data *acc,
		int *xyz)
{
	int err = -1;
	/* Data bytes from hardware xL, xH, yL, yH, zL, zH */
	u8 acc_data[6];
	/* x,y,z hardware data */
	s16 hw_d[3] = { 0 };

	acc_data[0] = (I2C_AUTO_INCREMENT | AXISDATA_REG);
	err = lis3dh_acc_i2c_read(acc, acc_data, 6);
	if (err < 0)
		return err;

	hw_d[0] = (((s16) ((acc_data[1] << 8) | acc_data[0])) >> 4);
	hw_d[1] = (((s16) ((acc_data[3] << 8) | acc_data[2])) >> 4);
	hw_d[2] = (((s16) ((acc_data[5] << 8) | acc_data[4])) >> 4);

	hw_d[0] = hw_d[0] * acc->sensitivity;
	hw_d[1] = hw_d[1] * acc->sensitivity;
	hw_d[2] = hw_d[2] * acc->sensitivity;


	xyz[0] = ((acc->pdata->negate_x) ? (-hw_d[acc->pdata->axis_map_x])
		   : (hw_d[acc->pdata->axis_map_x]));
	xyz[1] = ((acc->pdata->negate_y) ? (-hw_d[acc->pdata->axis_map_y])
		   : (hw_d[acc->pdata->axis_map_y]));
	xyz[2] = ((acc->pdata->negate_z) ? (-hw_d[acc->pdata->axis_map_z])
		   : (hw_d[acc->pdata->axis_map_z]));
	if(( abs(xyz[0])+abs(xyz[1])+abs(xyz[2]) )<st_excep.min_three_axis )
	{
		gs_INFO("[GS]%s read [%x %x %x %x %x %x] x=%d mg, y=%d mg, z=%d mg\n", __func__,
            acc_data[0], acc_data[1], acc_data[2], acc_data[3], acc_data[4], acc_data[5],xyz[0], xyz[1], xyz[2]);
	}

    if (lis3dh_debug == 1){
		gs_INFO("[GS]%s read [%x %x %x %x %x %x] x=%d mg, y=%d mg, z=%d mg\n", __func__,
            acc_data[0], acc_data[1], acc_data[2], acc_data[3], acc_data[4], acc_data[5],xyz[0], xyz[1], xyz[2]);
    }

	gs_FLOW("[GS]%s read  x=%d mg, y=%d mg, z=%d mg\n",
			__func__, xyz[0], xyz[1], xyz[2]);

	return err;
}

static void lis3dh_acc_report_values(struct lis3dh_acc_data *acc,
					int *xyz)
{
	accl_data[0] = xyz[0];
	accl_data[1] = xyz[1];
	accl_data[2] = xyz[2];
	input_report_abs(acc->input_dev, ABS_X, xyz[0]);
	input_report_abs(acc->input_dev, ABS_Y, xyz[1]);
	input_report_abs(acc->input_dev, ABS_Z, xyz[2]);
	input_sync(acc->input_dev);
}

static int lis3dh_acc_enable(struct lis3dh_acc_data *acc)
{
	int err = 0;

	if (!atomic_cmpxchg(&acc->enabled, 0, 1)) {
		if ((acc->pdata->gpio_int1 >= 0)
			|| (acc->pdata->gpio_int2 >= 0)) {
			/*We don't use interrupt function right now,so this code can't be operate.
			err = blockmux_set(acc->gpio_block, acc->gpio_block_config, NORMAL);
			if (err) {
				gs_ERR("[GS]%s, blockmux_set gpio config err\n",__func__);
				atomic_set(&acc->enabled, 0);
				return err;
			}
			*/
		}

		err = lis3dh_acc_device_power_on(acc);
		if (err < 0) {
			gs_ERR("[GS]%s, lis3dh_acc_device_power_on failed\n",__func__);
			atomic_set(&acc->enabled, 0);
			goto err_power_on;
		}

		schedule_delayed_work(&acc->input_work,
			msecs_to_jiffies(acc->pdata->poll_interval));
	}

	return err;

err_power_on:
	if ((acc->pdata->gpio_int1 >= 0)
		|| (acc->pdata->gpio_int2 >= 0))
	//if (blockmux_set(acc->gpio_block, acc->gpio_block_config, LOWPOWER))
		 gs_ERR("[GS]%s: blockmux_set error.\n", __func__);
	return err;

}

static int lis3dh_acc_disable(struct lis3dh_acc_data *acc)
{

	if (atomic_cmpxchg(&acc->enabled, 1, 0)) {
		cancel_delayed_work_sync(&acc->input_work);
		lis3dh_acc_device_power_off(acc);

		if ((acc->pdata->gpio_int1 >= 0)
			|| (acc->pdata->gpio_int2 >= 0)) {
			//We don't use interrupt function right now,so this code can't be operate.
			//if (blockmux_set(acc->gpio_block, acc->gpio_block_config, LOWPOWER))
				gs_ERR("[GS]%s, blockmux_set gpio config err\n",
					__func__);

		}
	}

	return 0;
}

static ssize_t read_single_reg(struct device *dev, char *buf, u8 reg)
{
	ssize_t ret;
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	int err;

	u8 data = reg;
	err = lis3dh_acc_i2c_read(acc, &data, 1);
	if (err < 0)
		return err;
	ret = sprintf(buf, "0x%02x\n", data);
	return ret;
}

static int write_reg(struct device *dev, const char *buf, u8 reg,
		u8 mask, int resumeIndex)
{
	int err = -1;
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	u8 x[2];
	u8 new_val;
	unsigned long val;

	if (strict_strtoul(buf, 16, &val))
		return -EINVAL;

	new_val = ((u8) val & mask);
	x[0] = reg;
	x[1] = new_val;
	err = lis3dh_acc_register_write(acc, x, reg, new_val);
	if (err < 0)
		return err;
	acc->resume_state[resumeIndex] = new_val;
	return err;
}

static ssize_t attr_get_polling_rate(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	int val;
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	mutex_lock(&acc->lock);
	val = acc->pdata->poll_interval;
	mutex_unlock(&acc->lock);
	return sprintf(buf, "%d\n", val);
}

static ssize_t attr_set_polling_rate(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t size)
{
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	unsigned long interval_ms;

	if (strict_strtoul(buf, 10, &interval_ms))
		return -EINVAL;
	if (!interval_ms) {

		gs_ERR("[GS]%s: interval should larger than zero\n", __func__);
		return -EINVAL;
	}
	gs_INFO("[GS]lis3dh %s: interval_ms=%ld\n", __func__, interval_ms);
	if(DT_tset)
	{
		if(10!=interval_ms)
		{
			return size;
		}
	}
	mutex_lock(&acc->lock);
	if(interval_ms < 10) interval_ms = 10;
	acc->pdata->poll_interval = interval_ms;
	lis3dh_acc_update_odr(acc, interval_ms);
	mutex_unlock(&acc->lock);
	return size;
}

static ssize_t attr_get_range(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	char val;
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	char range = 2;
	mutex_lock(&acc->lock);
	val = acc->pdata->g_range ;
	switch (val) {
	case LIS3DH_ACC_G_2G:
		range = 2;
		break;
	case LIS3DH_ACC_G_4G:
		range = 4;
		break;
	case LIS3DH_ACC_G_8G:
		range = 8;
		break;
	case LIS3DH_ACC_G_16G:
		range = 16;
		break;
	default:
		break;
	}
	mutex_unlock(&acc->lock);
	return sprintf(buf, "%d\n", range);
}

static ssize_t attr_set_range(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t size)
{
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	unsigned long val;
	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;
	mutex_lock(&acc->lock);
	acc->pdata->g_range = val;
	lis3dh_acc_update_g_range(acc, val);
	mutex_unlock(&acc->lock);
	return size;
}

static ssize_t attr_get_enable(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	int val = atomic_read(&acc->enabled);
	return sprintf(buf, "%d\n", val);
}

static ssize_t attr_set_enable(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	unsigned long val;

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	gs_INFO("[GS]%s: val=%ld\n", __func__, val);
	if(DT_tset)
	{
		gs_INFO("[GS][%s] enter DT_TEST val=%ld\n", __func__, val);
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
			return size;
		}
	}
	if (val)
		lis3dh_acc_enable(acc);
	else
		lis3dh_acc_disable(acc);

	return size;
}

static ssize_t attr_set_intconfig1(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return write_reg(dev, buf, INT_CFG1, NO_MASK, RES_INT_CFG1);
}

static ssize_t attr_get_intconfig1(struct device *dev,
		struct device_attribute *attr,	char *buf)
{
	return read_single_reg(dev, buf, INT_CFG1);
}

static ssize_t attr_set_duration1(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return write_reg(dev, buf, INT_DUR1, INT1_DURATION_MASK, RES_INT_DUR1);
}

static ssize_t attr_get_duration1(struct device *dev,
		struct device_attribute *attr,	char *buf)
{
	return read_single_reg(dev, buf, INT_DUR1);
}

static ssize_t attr_set_thresh1(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return write_reg(dev, buf, INT_THS1, INT1_THRESHOLD_MASK, RES_INT_THS1);
}

static ssize_t attr_get_thresh1(struct device *dev,
		struct device_attribute *attr,	char *buf)
{
	return read_single_reg(dev, buf, INT_THS1);
}

static ssize_t attr_get_source1(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return read_single_reg(dev, buf, INT_SRC1);
}

static ssize_t attr_set_source1(struct device *dev,
		struct device_attribute *attr,const char *buf, size_t size)
{
	return size;
}

static ssize_t attr_set_click_cfg(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return write_reg(dev, buf, TT_CFG, TAP_CFG_MASK, RES_TT_CFG);
}

static ssize_t attr_get_click_cfg(struct device *dev,
		struct device_attribute *attr,	char *buf)
{

	return read_single_reg(dev, buf, TT_CFG);
}

static ssize_t attr_get_click_source(struct device *dev,
		struct device_attribute *attr,	char *buf)
{
	return read_single_reg(dev, buf, TT_SRC);
}

static ssize_t attr_set_click_source(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return size;
}

static ssize_t attr_set_click_ths(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return write_reg(dev, buf, TT_THS, TAP_THS_MASK, RES_TT_THS);
}

static ssize_t attr_get_click_ths(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return read_single_reg(dev, buf, TT_THS);
}

static ssize_t attr_set_click_tlim(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return write_reg(dev, buf, TT_LIM, TAP_TLIM_MASK, RES_TT_LIM);
}

static ssize_t attr_get_click_tlim(struct device *dev,
		struct device_attribute *attr,	char *buf)
{
	return read_single_reg(dev, buf, TT_LIM);
}

static ssize_t attr_set_click_tlat(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return write_reg(dev, buf, TT_TLAT, TAP_TLAT_MASK, RES_TT_TLAT);
}

static ssize_t attr_get_click_tlat(struct device *dev,
		struct device_attribute *attr,	char *buf)
{
	return read_single_reg(dev, buf, TT_TLAT);
}

static ssize_t attr_set_click_tw(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return write_reg(dev, buf, TT_TLAT, TAP_TW_MASK, RES_TT_TLAT);
}

static ssize_t attr_get_click_tw(struct device *dev,
		struct device_attribute *attr,	char *buf)
{
	return read_single_reg(dev, buf, TT_TLAT);
}

static ssize_t attr_get_accl_data(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);

	mutex_lock(&acc->lock);

	*((int16_t *)&buf[0]) = accl_data[0];
	*((int16_t *)&buf[2]) = accl_data[1];
	*((int16_t *)&buf[4]) = accl_data[2];

	mutex_unlock(&acc->lock);

	return ACCL_DATA_SIZE;
}

static ssize_t attr_set_accl_data(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	return size;
}

#ifdef DEBUG
/* PAY ATTENTION: These DEBUG funtions don't manage resume_state */
static ssize_t attr_reg_set(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	int rc;
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	u8 x[2];
	unsigned long val;

	if (strict_strtoul(buf, 16, &val))
		return -EINVAL;
	mutex_lock(&acc->lock);
	x[0] = acc->reg_addr;
	mutex_unlock(&acc->lock);
	x[1] = val;
	rc = lis3dh_acc_i2c_write(acc, x, 1);
	/*TODO: error need to be managed */
	return size;
}

static ssize_t attr_reg_get(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	ssize_t ret;
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	int rc;
	u8 data;

	mutex_lock(&acc->lock);
	data = acc->reg_addr;
	mutex_unlock(&acc->lock);
	rc = lis3dh_acc_i2c_read(acc, &data, 1);
	/*TODO: error need to be managed */
	ret = sprintf(buf, "0x%02x\n", data);
	return ret;
}

static ssize_t attr_addr_set(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct lis3dh_acc_data *acc = dev_get_drvdata(dev);
	unsigned long val;
	if (strict_strtoul(buf, 16, &val))
		return -EINVAL;
	mutex_lock(&acc->lock);
	acc->reg_addr = val;
	mutex_unlock(&acc->lock);
	return size;
}

static ssize_t attr_addr_get(struct device *dev, struct device_attribute *attr, char *buf)
{
	return 0;
}
#endif

static ssize_t attr_get_accl_info(struct device *dev, struct device_attribute *attr, char *buf)
{
	ssize_t count;
	count = sprintf(buf, "ST LIS3DH");
	return count;
}

static ssize_t attr_set_accl_info(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return size;
}

static ssize_t attr_get_accl_xyz(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "0x%x 0x%x 0x%x\n", accl_data[0], accl_data[1], accl_data[2]);
}

static ssize_t attr_set_accl_xyz(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	return size;
}

static ssize_t attr_set_accl_debug(struct device *dev,
		struct device_attribute *attr,	const char *buf, size_t size)
{
	int val;

	if (kstrtoint(buf, 0, &val))
		return -EINVAL;

    lis3dh_debug = val;

    return size;
}

static ssize_t attr_get_accl_debug(struct device *dev,
		struct device_attribute *attr,	char *buf)
{
	return sprintf(buf, "%d\n", lis3dh_debug);
}

//add some attributes to viod print warning log when boot the phone
static struct device_attribute attributes[] = {

	__ATTR(xyz, 0664, attr_get_accl_xyz, attr_set_accl_xyz),
	__ATTR(debug, 0664, attr_get_accl_debug, attr_set_accl_debug),
	__ATTR(pollrate_ms, 0664, attr_get_polling_rate, attr_set_polling_rate),
	__ATTR(range, 0664, attr_get_range, attr_set_range),
	__ATTR(enable, 0664, attr_get_enable, attr_set_enable),
	__ATTR(int1_config, 0664, attr_get_intconfig1, attr_set_intconfig1),
	__ATTR(int1_duration, 0664, attr_get_duration1, attr_set_duration1),
	__ATTR(int1_threshold, 0664, attr_get_thresh1, attr_set_thresh1),
	__ATTR(int1_source, 0664, attr_get_source1, attr_set_source1),
	__ATTR(click_config, 0664, attr_get_click_cfg, attr_set_click_cfg),
	__ATTR(click_source, 0664, attr_get_click_source, attr_set_click_source),
	__ATTR(click_threshold, 0664, attr_get_click_ths, attr_set_click_ths),
	__ATTR(click_timelimit, 0664, attr_get_click_tlim, attr_set_click_tlim),
	__ATTR(click_timelatency, 0664, attr_get_click_tlat, attr_set_click_tlat),
	__ATTR(click_timewindow, 0664, attr_get_click_tw, attr_set_click_tw),
	__ATTR(accl_data, 0664, attr_get_accl_data, attr_set_accl_data),
	__ATTR(accl_info, 0664, attr_get_accl_info, attr_set_accl_info),
#ifdef DEBUG
	__ATTR(reg_value, 0664, attr_reg_get, attr_reg_set),
	__ATTR(reg_addr, 0664, attr_addr_get, attr_addr_set),
#endif
};

static int create_sysfs_interfaces(struct device *dev)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(attributes); i++)
		if (device_create_file(dev, attributes + i))
			goto error;
	return 0;

error:
	for ( ; i >= 0; i--)
		device_remove_file(dev, attributes + i);

	gs_ERR("[GS]%s:Unable to create interface\n", __func__);
	return -1;
}

static int remove_sysfs_interfaces(struct device *dev)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(attributes); i++)
		device_remove_file(dev, attributes + i);
	return 0;
}

static void lis3dh_acc_input_work_func(struct work_struct *work)
{
	struct lis3dh_acc_data *acc;

	int xyz[3] = { 0 };
	int err;

	acc = container_of((struct delayed_work *)work,
			struct lis3dh_acc_data,	input_work);

	mutex_lock(&acc->lock);

	err = lis3dh_acc_get_acceleration_data(acc, xyz);
	if (err < 0)
		gs_ERR("[GS]get_acceleration_data failed\n");
	else
		lis3dh_acc_report_values(acc, xyz);

	schedule_delayed_work(&acc->input_work, msecs_to_jiffies(
			acc->pdata->poll_interval));

	mutex_unlock(&acc->lock);
	if(DT_tset)
	{
		Gsensor_data_count++;
	}
	

}
#if 0
int lis3dh_acc_input_open(struct input_dev *input)
{
	struct lis3dh_acc_data *acc = input_get_drvdata(input);

	return lis3dh_acc_enable(acc);
}

void lis3dh_acc_input_close(struct input_dev *dev)
{
	struct lis3dh_acc_data *acc = input_get_drvdata(dev);

	lis3dh_acc_disable(acc);
}
#endif
static int lis3dh_acc_validate_pdata(struct lis3dh_acc_data *acc)
{
	acc->pdata->poll_interval = max(acc->pdata->poll_interval,
			acc->pdata->min_interval);

	if (acc->pdata->axis_map_x > 2 ||
		acc->pdata->axis_map_y > 2 ||
		 acc->pdata->axis_map_z > 2) {
		gs_ERR("[GS]invalid axis_map value "
			"x:%u y:%u z%u\n", acc->pdata->axis_map_x,
				acc->pdata->axis_map_y, acc->pdata->axis_map_z);
		return -EINVAL;
	}

	/* Only allow 0 and 1 for negation boolean flag */
	if (acc->pdata->negate_x > 1 || acc->pdata->negate_y > 1
			|| acc->pdata->negate_z > 1) {
			gs_ERR("[GS]invalid negate value "
			"x:%u y:%u z:%u\n", acc->pdata->negate_x,
				acc->pdata->negate_y, acc->pdata->negate_z);	
		return -EINVAL;
	}

	/* Enforce minimum polling interval */
	if (acc->pdata->poll_interval < acc->pdata->min_interval) {
		gs_ERR("[GS]minimum poll interval violated\n");
		return -EINVAL;
	}

	return 0;
}

static int lis3dh_acc_input_init(struct lis3dh_acc_data *acc)
{
	int err;

	INIT_DELAYED_WORK(&acc->input_work, lis3dh_acc_input_work_func);
	acc->input_dev = input_allocate_device();
	if (!acc->input_dev) {
		err = -ENOMEM;
		gs_ERR("[GS]input device allocation failed\n");
		goto err0;
	}

	/*acc->input_dev->open = lis3dh_acc_input_open;*/
	/*acc->input_dev->close = lis3dh_acc_input_close;*/
	acc->input_dev->open = NULL;
	acc->input_dev->close = NULL;
	acc->input_dev->name = ACCL_INPUT_DEV_NAME;
	acc->input_dev->id.bustype = BUS_I2C;
	acc->input_dev->dev.parent = &acc->client->dev;

	input_set_drvdata(acc->input_dev, acc);

	set_bit(EV_ABS, acc->input_dev->evbit);
	/*	next is used for interruptA sources data if the case */
	set_bit(ABS_MISC, acc->input_dev->absbit);
	/*	next is used for interruptB sources data if the case */
	set_bit(ABS_WHEEL, acc->input_dev->absbit);

	input_set_abs_params(acc->input_dev, ABS_X, -G_MAX, G_MAX, FUZZ, FLAT);
	input_set_abs_params(acc->input_dev, ABS_Y, -G_MAX, G_MAX, FUZZ, FLAT);
	input_set_abs_params(acc->input_dev, ABS_Z, -G_MAX, G_MAX, FUZZ, FLAT);
	/*	next is used for interruptA sources data if the case */
	input_set_abs_params(acc->input_dev, ABS_MISC, INT_MIN, INT_MAX, 0, 0);
	/*	next is used for interruptB sources data if the case */
	input_set_abs_params(acc->input_dev, ABS_WHEEL, INT_MIN, INT_MAX, 0, 0);


	err = input_register_device(acc->input_dev);
	if (err) {
		gs_ERR("[GS]unable to register input device %s\n",
				acc->input_dev->name);
		goto err1;
	}

	return 0;
err1:
	input_free_device(acc->input_dev);
err0:
	return err;
}

static void lis3dh_acc_input_cleanup(struct lis3dh_acc_data *acc)
{
	input_set_drvdata(acc->input_dev, NULL);
	input_unregister_device(acc->input_dev);
	input_free_device(acc->input_dev);
}


static void acc_resumestate_init(struct lis3dh_acc_data *acc)
{

	memset(acc->resume_state, 0, ARRAY_SIZE(acc->resume_state));

	acc->resume_state[RES_CTRL_REG1] = LIS3DH_ACC_ENABLE_ALL_AXES;
	acc->resume_state[RES_CTRL_REG2] = 0x00;
	acc->resume_state[RES_CTRL_REG3] = 0x00;
	acc->resume_state[RES_CTRL_REG4] = 0x00;
	acc->resume_state[RES_CTRL_REG5] = 0x00;
	acc->resume_state[RES_CTRL_REG6] = 0x00;

	acc->resume_state[RES_TEMP_CFG_REG] = 0x00;
	acc->resume_state[RES_FIFO_CTRL_REG] = 0x00;
	acc->resume_state[RES_INT_CFG1] = 0x00;
	acc->resume_state[RES_INT_THS1] = 0x00;
	acc->resume_state[RES_INT_DUR1] = 0x00;

	acc->resume_state[RES_TT_CFG] = 0x00;
	acc->resume_state[RES_TT_THS] = 0x00;
	acc->resume_state[RES_TT_LIM] = 0x00;
	acc->resume_state[RES_TT_TLAT] = 0x00;
	acc->resume_state[RES_TT_TW] = 0x00;

}

static int lis3dh_config_gpio(struct device *dev, struct lis3dh_acc_data *acc_data)
{

	int ret = 0;

    return ret;
	//this code don't be operated,if remain this code,kernel 3.10 can not complie pass
#if 0
	/* get gpio block*/
	acc_data->gpio_block = iomux_get_block(GPIO_BOLCK_NAME);
	if (IS_ERR(acc_data->gpio_block)) {

		gs_ERR("[GS]%s: failed to get gpio block\n", __func__);
		ret = -EINVAL;
		return ret;
	}

	/* get gpio block config*/
	acc_data->gpio_block_config = iomux_get_blockconfig(GPIO_BOLCK_NAME);
	if (IS_ERR(acc_data->gpio_block_config)) {

		gs_ERR("[GS]%s: failed to get gpio block config\n", __func__);
		ret = -EINVAL;
		goto err_block_config;
	}

	/* config gpio work mode*/
	ret = blockmux_set(acc_data->gpio_block, acc_data->gpio_block_config, LOWPOWER);
	if (ret) {

		gs_ERR([GS] dev, "%s: failed to config gpio\n", __func__);
		ret = -EINVAL;
		goto err_mux_set;
	}

	return ret;

err_mux_set:
	if (acc_data->gpio_block_config)
		acc_data->gpio_block_config = NULL;
err_block_config:
	if (acc_data->gpio_block)
		acc_data->gpio_block = NULL;

	return ret;
#endif
}
static int lis3dh_acc_poll_delay_set(struct sensors_classdev *sensors_cdev,unsigned int delay_msec)
{
    struct lis3dh_acc_data *acc = container_of(sensors_cdev,struct lis3dh_acc_data, cdev);
    int err;
    mutex_lock(&acc->lock);
    if(delay_msec < 10) 
    {
        delay_msec = 10;
    }
    acc->pdata->poll_interval = delay_msec;
    gs_INFO("[GS]%s,acc->pdata->poll_interval  = %d",__func__,acc->pdata->poll_interval );
    err=lis3dh_acc_update_odr(acc, delay_msec);
    mutex_unlock(&acc->lock);
    return err;
}

static int lis3dh_acc_enable_set(struct sensors_classdev *sensors_cdev,unsigned int enable)
{
    struct lis3dh_acc_data *acc = container_of(sensors_cdev,struct lis3dh_acc_data, cdev);
    int err;
    gs_INFO("[GS]%s: enable=%ld\n", __func__, enable);

    if (enable)
    {
        err = lis3dh_acc_enable(acc);
    }
    else
    {
        err = lis3dh_acc_disable(acc);
    }
    return err;
}
#if defined(CONFIG_FB)
static int lis3dh_acc_resume(struct i2c_client *client)
{
	struct lis3dh_acc_data *acc = i2c_get_clientdata(client);

	gs_INFO("[GS][%s] +\n", __func__);
	if (acc->on_before_suspend) {
		if (lis3dh_acc_enable(acc)) {
			gs_ERR("[GS]%s: lis3dh_acc_enable failed\n",
					__func__);
		}
	}
	gs_INFO("[GS][%s] -\n", __func__);
	return 0;
}

static int lis3dh_acc_suspend(struct i2c_client *client, pm_message_t mesg)
{
	struct lis3dh_acc_data *acc = i2c_get_clientdata(client);

	gs_INFO("[GS][%s] +\n", __func__);
	acc->on_before_suspend = atomic_read(&acc->enabled);

	lis3dh_acc_disable(acc);
	gs_INFO("[GS][%s] -\n", __func__);
	return 0;
}
static int fb_notifier_callback(struct notifier_block *self,unsigned long event, void *data)  
{
	int error = 0;
	int i;
	struct fb_event *fb_event = data;
	int *blank = fb_event->data;

	for (i = 0 ; i < FB_MAX; i++) {
		if (registered_fb[i] == fb_event->info) {
			if (i == 0) {
				gs_INFO("[GS]%s: lis3dh_acc:%d, go on !\n", __func__,i);
				break;
			} else {
				gs_INFO("[GS]%s: lis3dh_acc:%d, exit !\n", __func__,i);
				return error;
			}
		}
	}

	switch(*blank){
	case FB_BLANK_UNBLANK:
		/*resume device*/
		switch(event) {
		case FB_EARLY_EVENT_BLANK:
			lis3dh_acc_resume(this_gs_data->client);
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
			lis3dh_acc_suspend(this_gs_data->client, PMSG_SUSPEND);
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
static int get_acc_info(struct i2c_client *client,struct lis3dh_acc_platform_data *pdata)
{
	struct device_node *node = client->dev.of_node;
	int rc = 0;
	int error = 0;
	rc = of_property_read_u32(node, "poll_interval", &pdata->poll_interval);
	if (rc) {
		gs_ERR("[GS]poll_interval read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

	rc = of_property_read_u32(node, "min_interval", &pdata->min_interval);
	if (rc) {
		gs_ERR("[GS]min_interval read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

	rc = of_property_read_u32(node, "gpio_int1", &pdata->gpio_int1);
	if (rc) {
		gs_ERR("[GS]gpio_int1 read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}
	pdata->gpio_int1--;//we can't set negative number in dts,so we set 0 in dts and here delete 1

	rc = of_property_read_u32(node, "gpio_int2", &pdata->gpio_int2);
	if (rc) {
		gs_ERR("[GS]gpio_int2 read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}
	pdata->gpio_int2--;//we can't set negative number in dts,so we set 0 in dts and here delete 1

	rc = of_property_read_u32(node, "negate_x", &pdata->negate_x);
	if (rc) {
		gs_ERR("[GS]negate_x read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

	rc = of_property_read_u32(node, "negate_y", &pdata->negate_y);
	if (rc) {

		gs_ERR("[GS]negate_y read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

	rc = of_property_read_u32(node, "negate_z", &pdata->negate_z);
	if (rc) {

		gs_ERR("[GS]negate_z read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

	rc = of_property_read_u32(node, "g_range", &pdata->g_range);
	if (rc) {

		gs_ERR("[GS]g_range read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

	rc = of_property_read_u32(node, "axis_map_x", &pdata->axis_map_x);
	if (rc) {

		gs_ERR("[GS]axis_map_x read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

	rc = of_property_read_u32(node, "axis_map_y", &pdata->axis_map_y);
	if (rc) {

		gs_ERR("[GS]axis_map_y read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

	rc = of_property_read_u32(node, "axis_map_z", &pdata->axis_map_z);
	if (rc) {

		gs_ERR("[GS]axis_map_z read failed:%d\n", rc);
		error = -EINVAL;
		goto out;
	}

out:
	return error;
}

static int lis3dh_acc_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{

	struct lis3dh_acc_data *acc;
	int err = 0;
	u8 chipid = 0;
	u8 i = 0;

	gs_FLOW("[GS]%s: probe start.\n", LIS3DH_ACC_DEV_NAME);
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		gs_ERR("[GS]client not i2c capable\n");
		err = -ENODEV;
		goto exit_check_functionality_failed;
	}


	acc = kzalloc(sizeof(struct lis3dh_acc_data), GFP_KERNEL);
	if (acc == NULL) {
		err = -ENOMEM;
		gs_ERR("[GS]failed to allocate memory for module data: %d\n", err);	
		goto exit_check_functionality_failed;
	}		
	mutex_init(&acc->lock);
	mutex_lock(&acc->lock);
	acc->client = client;

	i2c_set_clientdata(client, acc);
	chipid = WHO_AM_I;
	err = lis3dh_acc_i2c_read(acc, &chipid, 1);
	if (err < 0) {
		gs_ERR("[GS]Error reading WHO_AM_I: is device available/working?\n");
		goto err_mutexunlock;
	}

	if (chipid != WHOAMI_LIS3DH_ACC) {
		gs_ERR("[GS]device unknown. Expected: 0x%x, Replies: 0x%x\n", WHOAMI_LIS3DH_ACC, chipid);
		err = -ENODEV;
		goto err_mutexunlock;
	}

	gs_INFO("[GS]Read lis3dh chip ok, ID is 0x%x\n", chipid);
	err = set_sensor_chip_info(ACC, "ST LIS3DH");
	if (err) {
		gs_ERR("[GS]set_sensor_chip_info error\n");
	}


	err = lis3dh_config_gpio(&client->dev, acc);
	if (err) {
		gs_ERR("[GS]%s: failed to config gpio lowpower mode\n", __func__);
		goto err_mutexunlock;
	}

	acc->pdata = kzalloc(sizeof(*acc->pdata), GFP_KERNEL);
	if (acc->pdata == NULL) {
		err = -ENOMEM;
		gs_ERR("[GS]failed to allocate memory for pdata: %d\n", err);		
		goto err_mutexunlock;
	}

	err =get_acc_info(client,acc->pdata);
	if (err < 0) {

		gs_ERR("[GS]%s: failed to get_acc_info\n", __func__);
		goto err_mutexunlock;
	}

	if (acc->pdata->gpio_int1 >= 0) {
		err = gpio_request(acc->pdata->gpio_int1, "gsensor_gpio1");
		if (err) {

			gs_ERR("[GS]%s: failed to request gpio1 for irq1\n", __func__);
			goto exit_kfree_pdata;
		}

		gpio_direction_input(acc->pdata->gpio_int1);

		acc->irq1 = gpio_to_irq(acc->pdata->gpio_int1);

		gs_FLOW("[GS]%s: %s has set irq1 to irq: %d mapped on gpio:%d\n",
			LIS3DH_ACC_DEV_NAME, __func__, acc->irq1, acc->pdata->gpio_int1);
	}

	if (acc->pdata->gpio_int2 >= 0) {
		err = gpio_request(acc->pdata->gpio_int2, "gsensor_gpio2");
		if (err) {

			gs_ERR("[GS]%s: failed to request gpio2 for irq2\n", __func__);
			goto err_request_int1;
		}
		gpio_direction_input(acc->pdata->gpio_int2);

		acc->irq2 = gpio_to_irq(acc->pdata->gpio_int2);

		gs_FLOW("[GS]%s: %s has set irq2 to irq: %d mapped on gpio:%d\n",
			LIS3DH_ACC_DEV_NAME, __func__, acc->irq2, acc->pdata->gpio_int2);	
	}

	err = lis3dh_acc_validate_pdata(acc);
	if (err < 0) {
		gs_ERR("[GS]failed to validate platform data\n");
		goto err_request_int2;
	}

	if (acc->pdata->init) {
		err = acc->pdata->init();
		if (err < 0) {
			gs_ERR("[GS]init failed: %d\n", err);
			goto err_request_int2;
		}
	}

	/*init the acc resume state register*/
	acc_resumestate_init(acc);

	err = lis3dh_acc_device_power_on(acc);
	if (err < 0) {
		gs_ERR("[GS]power on failed: %d\n", err);
		goto err_pdata_init;
	}

	atomic_set(&acc->enabled, 1);

	err = lis3dh_acc_update_g_range(acc, acc->pdata->g_range);
	if (err < 0) {
		gs_ERR("[GS]update_g_range failed\n");
		goto  err_power_off;
	}

	err = lis3dh_acc_update_odr(acc, acc->pdata->poll_interval);
	if (err < 0) {
		gs_ERR("[GS]update_odr failed\n");
		goto  err_power_off;
	}

	err = lis3dh_acc_input_init(acc);
	if (err < 0) {
		gs_ERR("[GS]input init failed\n");
		goto err_power_off;
	}
       acc->cdev=lis3dh_acc_cdev;
       acc->cdev.sensors_enable=lis3dh_acc_enable_set;
       acc->cdev.sensors_poll_delay=lis3dh_acc_poll_delay_set;
       err = sensors_classdev_register(&client->dev, &acc->cdev);
	if (err) 
      {
	    gs_ERR("[GS]unable to register sensors_classdev: %d\n",err);
	}
#if defined(CONFIG_FB)
		fb_lis_acc.fb_notify.notifier_call = fb_notifier_callback;
		err = fb_register_client(&fb_lis_acc.fb_notify);
		if (err){
			gs_ERR("[GS]unable to register fb_notifier: %d\n",err);
			goto err_power_off;
		 }
#endif

	err = create_sysfs_interfaces(&client->dev);
	if (err < 0) {
		   gs_ERR("[GS]device LIS3DH_ACC_DEV_NAME sysfs register failed\n");
		goto err_input_cleanup;
	}

	lis3dh_acc_device_power_off(acc);

	/* As default, do not report information */
	atomic_set(&acc->enabled, 0);

	if (acc->pdata->gpio_int1 >= 0) {
		INIT_WORK(&acc->irq1_work, lis3dh_acc_irq1_work_func);
		acc->irq1_work_queue =
			create_singlethread_workqueue("lis3dh_acc_wq1");
		if (!acc->irq1_work_queue) {
			err = -ENOMEM;
			gs_ERR("[GS]cannot create work queue1: %d\n", err);		
			goto err_remove_sysfs_int;
		}
		err = request_irq(acc->irq1, lis3dh_acc_isr1,
				IRQF_TRIGGER_RISING, "lis3dh_acc_irq1", acc);
		if (err < 0) {
			gs_ERR("[GS]request irq1 failed: %d\n", err);
			goto err_destoyworkqueue1;
		}
		disable_irq_nosync(acc->irq1);
	}

	if (acc->pdata->gpio_int2 >= 0) {
		INIT_WORK(&acc->irq2_work, lis3dh_acc_irq2_work_func);
		acc->irq2_work_queue =
			create_singlethread_workqueue("lis3dh_acc_wq2");
		if (!acc->irq2_work_queue) {
			err = -ENOMEM;
			gs_ERR("[GS]cannot create work queue2: %d\n", err);	
			goto err_free_irq1;
		}
		err = request_irq(acc->irq2, lis3dh_acc_isr2,
				IRQF_TRIGGER_RISING, "lis3dh_acc_irq2", acc);
		if (err < 0) {
			gs_ERR("[GS]request irq2 failed: %d\n", err);
			goto err_destoyworkqueue2;
		}
		disable_irq_nosync(acc->irq2);
	}
	mutex_unlock(&acc->lock);
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	/* detect current device successful, set the flag as present */
	set_hw_dev_flag(DEV_I2C_G_SENSOR);
#endif
#if defined (CONFIG_HUAWEI_DSM)
      lis3dh_acc_flag=1;
#endif
	gs_FLOW("[GS]%s: probed complete\n", LIS3DH_ACC_DEV_NAME);
	this_gs_data =acc;
	st_excep.base=1024;
	st_excep.min_three_axis=2*1024/5;
	for (i=0; i<3; i++)
	{
		st_excep.last_axis[i] = 0;
		st_excep.current_axis[i] = 0;
	}
	gs_INFO("[GS]lis3dh : Driver Init Success\n");
	return 0;

err_destoyworkqueue2:
	if (acc->pdata->gpio_int2 >= 0)
		destroy_workqueue(acc->irq2_work_queue);
err_free_irq1:
	if (acc->pdata->gpio_int1 >= 0)
		free_irq(acc->irq1, acc);
err_destoyworkqueue1:
	if (acc->pdata->gpio_int1 >= 0)
		destroy_workqueue(acc->irq1_work_queue);
err_remove_sysfs_int:
	remove_sysfs_interfaces(&client->dev);
err_input_cleanup:
	lis3dh_acc_input_cleanup(acc);
err_power_off:
	lis3dh_acc_device_power_off(acc);
err_pdata_init:
	if (acc->pdata->exit)
		acc->pdata->exit();
err_request_int2:
	if (acc->pdata->gpio_int2 >= 0)
		gpio_free(acc->pdata->gpio_int2);
err_request_int1:
	if (acc->pdata->gpio_int1 >= 0)
		gpio_free(acc->pdata->gpio_int1);
exit_kfree_pdata:
	kfree(acc->pdata);
	acc->pdata = NULL;
err_mutexunlock:
	i2c_set_clientdata(client, NULL);
	mutex_unlock(&acc->lock);
	kfree(acc);
	acc = NULL;
exit_check_functionality_failed:
	gs_INFO("[GS]lis3dh : Driver Init failed\n");
	return err;
}

static int lis3dh_acc_remove(struct i2c_client *client)
{
	struct lis3dh_acc_data *acc = i2c_get_clientdata(client);

	if (acc->pdata->gpio_int1 >= 0) {
		free_irq(acc->irq1, acc);
		gpio_free(acc->pdata->gpio_int1);
		destroy_workqueue(acc->irq1_work_queue);
	}

	if (acc->pdata->gpio_int2 >= 0) {
		free_irq(acc->irq2, acc);
		gpio_free(acc->pdata->gpio_int2);
		destroy_workqueue(acc->irq2_work_queue);
	}

	lis3dh_acc_input_cleanup(acc);
	lis3dh_acc_device_power_off(acc);
	remove_sysfs_interfaces(&client->dev);
	if (acc->pdata->exit)
		acc->pdata->exit();
	kfree(acc->pdata);
	acc->pdata = NULL;
#if defined(CONFIG_FB)
	if (fb_unregister_client(&fb_lis_acc.fb_notify))
		gs_ERR("[GS]acc:error occurred while unregistering fb_notifier.\n");
#endif
	kfree(acc);
	acc = NULL;

	i2c_set_clientdata(client, NULL);

	return 0;
}

static void lis3dh_acc_shutdown(struct i2c_client *client)
{
	struct lis3dh_acc_data *acc = i2c_get_clientdata(client);

	 gs_INFO("[GS][%s] +\n", __func__);
	lis3dh_acc_disable(acc);
	if (acc->pdata->exit)
		acc->pdata->exit();
	gs_INFO("[GS][%s],-\n", __func__);

}
static const struct i2c_device_id lis3dh_acc_id[]
		= { { LIS3DH_ACC_DEV_NAME, 0 }, { }, };

MODULE_DEVICE_TABLE(i2c, lis3dh_acc_id);

static const struct of_device_id lis3dh_of_match[] = {
	{.compatible = "huawei,lis3dh_acc",},
	{},
};
MODULE_DEVICE_TABLE(of, lis3dh_of_match);

static struct i2c_driver lis3dh_acc_driver = {
	.driver = {
			.owner = THIS_MODULE,
			.name = LIS3DH_ACC_DEV_NAME,
			.of_match_table = lis3dh_of_match,
		  },
	.probe = lis3dh_acc_probe,
	.remove = lis3dh_acc_remove,
	.shutdown = lis3dh_acc_shutdown,
	.id_table = lis3dh_acc_id,
};

static int __init lis3dh_acc_init(void)
{
	return i2c_add_driver(&lis3dh_acc_driver);
}

static void __exit lis3dh_acc_exit(void)
{
	i2c_del_driver(&lis3dh_acc_driver);
}

module_init(lis3dh_acc_init);
module_exit(lis3dh_acc_exit);

MODULE_DESCRIPTION("lis3dh digital accelerometer sysfs driver");
MODULE_AUTHOR("Matteo Dameno, Carmine Iascone, STMicroelectronics");
MODULE_LICENSE("GPL");

