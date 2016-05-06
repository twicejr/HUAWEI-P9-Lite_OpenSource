

/*#define DEBUG*/
/*#define VERBOSE_DEBUG*/



#include "akm09911.h"
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/freezer.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/workqueue.h>
#include <linux/board_sensors.h>
#include <linux/of_gpio.h>
#include <huawei_platform/sensor/sensor_info.h>
#include <linux/sensors.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

#if defined (CONFIG_HUAWEI_DSM)
#include <linux/mfd/hisi_hi6xxx_pmic.h>
#include <dsm/dsm_pub.h>
extern struct dsm_client *compass_dclient;
static int akm09911_flag = 0;
#endif
extern bool DT_tset;
extern int compass_data_count;
extern int Gyro_data_count;
/* IOCTLs for AKM library */
#define ECS_IOCTL_READ				_IOWR(AKMIO, 0x01, char)
#define ECS_IOCTL_WRITE				_IOW(AKMIO, 0x02, char)
#define ECS_IOCTL_RESET				_IO(AKMIO, 0x03)
#define ECS_IOCTL_SET_MODE			_IOW(AKMIO, 0x10, char)
#define ECS_IOCTL_SET_YPR			_IOW(AKMIO, 0x11, int[AKM_YPR_DATA_SIZE])
#define ECS_IOCTL_GET_INFO			_IOR(AKMIO, 0x20, unsigned char[AKM_SENSOR_INFO_SIZE])
#define ECS_IOCTL_GET_CONF			_IOR(AKMIO, 0x21, unsigned char[AKM_SENSOR_CONF_SIZE])
#define ECS_IOCTL_GET_DATA			_IOR(AKMIO, 0x22, unsigned char[AKM_SENSOR_DATA_SIZE])
#define ECS_IOCTL_GET_OPEN_STATUS	_IOR(AKMIO, 0x23, int)
#define ECS_IOCTL_GET_CLOSE_STATUS	_IOR(AKMIO, 0x24, int)
#define ECS_IOCTL_GET_DELAY			_IOR(AKMIO, 0x25, long long int)
#define ECS_IOCTL_GET_LAYOUT		_IOR(AKMIO, 0x26, char)
#define ECS_IOCTL_GET_ACCEL			_IOR(AKMIO, 0x30, short[3])

#define AKM_DEBUG_IF			1
#define AKM_HAS_RESET			1
#define AKM_ACCEL_ITEMS 3
//#define AKM_INPUT_DEVICE_NAME	"input_compass"
#define AKM_DRDY_TIMEOUT_MS		100
#define AKM_BASE_NUM			10

#define AKM_IS_MAG_DATA_ENABLED() (akm->enable_flag & (1 << MAG_DATA_FLAG))

#define AUTO_REPORT             1
#define USE_HRTIMER             1


/* Save last device state for power down */
struct akm_sensor_state {
	bool power_on;
	uint8_t mode;
};
struct akm_compass_data {
	struct i2c_client	*i2c;
	struct input_dev	*input;
	struct device		*class_dev;
	struct class		*compass;
       struct sensors_classdev	cdev;
	struct delayed_work	dwork;
	struct workqueue_struct	*work_queue;
	struct mutex		op_mutex;
	struct mutex		self_test_mutex;

	wait_queue_head_t	drdy_wq;
	wait_queue_head_t	open_wq;

	/* These two buffers are initialized at start up.
	   After that, the value is not changed */
	uint8_t sense_info[AKM_SENSOR_INFO_SIZE];
	uint8_t sense_conf[AKM_SENSOR_CONF_SIZE];

	struct	mutex sensor_mutex;
	uint8_t	sense_data[AKM_SENSOR_DATA_SIZE];
	struct mutex accel_mutex;
	int16_t	accel_data[AKM_ACCEL_ITEMS];

	/* Positive value means the device is working.
	   0 or negative value means the device is not woking,
	   i.e. in power-down mode. */
	int8_t	is_busy;

	struct mutex	val_mutex;
	uint32_t		enable_flag;
	int64_t			delay[AKM_NUM_SENSORS];

#if AKM_DEBUG_IF
	uint8_t			debug_mode;
#endif

	atomic_t	active;

	atomic_t	drdy;
	atomic_t	suspend;

	char layout;
	int	irq;
	int	gpio_rstn;
	int	power_enabled;
	int	auto_report;
	int	use_hrtimer;

	/* The input event last time */
	int	last_x;
	int	last_y;
	int	last_z;

	/* dummy value to avoid sensor event get eaten */
	int	rep_cnt;

	struct regulator	*vdd;
	struct regulator	*vio;
	struct akm_sensor_state state;
	struct hrtimer	poll_timer;
};

static struct sensors_classdev sensors_cdev = {
       .path_name="mag_sensor",
       .name = "3-axis Magnetic field sensor",
	.vendor = "AKM_09911",
	.version = 1,
	.handle = SENSORS_MAGNETIC_FIELD_HANDLE,
	.type = SENSOR_TYPE_MAGNETIC_FIELD,
	.max_range = "1228.8",
	.resolution = "0.6",
	.sensor_power = "0.35",
	.min_delay = 10000,
	.fifo_reserved_event_count = 0,
	.fifo_max_event_count = 0,
	.enabled = 0,
	.delay_msec = 10,
	.sensors_enable = NULL,
	.sensors_poll_delay = NULL,
};


static struct akm_compass_data *s_akm;
static int calibration_value=0;


static int akm_compass_power_set(struct akm_compass_data *data, bool on);
static int akm_self_test_body(struct akm_compass_data *akm);
static ssize_t akm_enable_set(struct akm_compass_data *akm, unsigned int enable);


/***** I2C I/O function ***********************************************/
static int akm_i2c_rxdata(
	struct i2c_client *i2c,
	uint8_t *rxData,
	int length)
{
	int ret;
#if defined (CONFIG_HUAWEI_DSM)
   	unsigned char LDO2_status=0;
	unsigned char LDO5_status=0;
#endif
	struct i2c_msg msgs[] = {
		{
			.addr = i2c->addr,
			.flags = 0,
			.len = 1,
			.buf = rxData,
		},
		{
			.addr = i2c->addr,
			.flags = I2C_M_RD,
			.len = length,
			.buf = rxData,
		},
	};
	uint8_t addr = rxData[0];

	ret = i2c_transfer(i2c->adapter, msgs, ARRAY_SIZE(msgs));
	if (ret < 0) {

		compass_ERR("[COMPASS]%s: transfer failed.", __func__);
#if defined (CONFIG_HUAWEI_DSM)
		    LDO2_status = hi6xxx_pmic_reg_read(LDO2_PHYS_ADDR);
		    LDO5_status = hi6xxx_pmic_reg_read(LDO5_PHYS_ADDR);
            compass_ERR("[COMPASS]%s: LDO2_status=%d\n", __func__,LDO2_PHYS_ADDR);
            compass_ERR("[COMPASS]%s: LDO5_status=%d\n", __func__,LDO5_PHYS_ADDR);

	if(1==akm09911_flag)
	  {
		if(!dsm_client_ocuppy(compass_dclient)){
		dsm_client_record(compass_dclient, "[%s]i2c_status:%d,rst is 0x%x,LDO2_status is 0x%x,LDO5_status is 0x%x.\n",__func__, ret,gpio_get_value(s_akm->gpio_rstn),LDO2_status,LDO5_status);
		dsm_client_notify(compass_dclient, DSM_COMPASS_I2C_RW_ERROR_NO);
		}
	 }
#endif
		return ret;
	} else if (ret != ARRAY_SIZE(msgs)) {
		compass_ERR("[COMPASS]%s: transfer failed(size error).\n",__func__);

#if defined (CONFIG_HUAWEI_DSM)
		LDO2_status = hi6xxx_pmic_reg_read(LDO2_PHYS_ADDR);
		LDO5_status = hi6xxx_pmic_reg_read(LDO5_PHYS_ADDR);
		compass_ERR("[COMPASS]%s: LDO2_status=%d\n", __func__,LDO2_PHYS_ADDR);
		compass_ERR("[COMPASS]%s: LDO5_status=%d\n", __func__,LDO5_PHYS_ADDR);
		//gpio_get_value(s_akm->gpio_rstn);
	if(1==akm09911_flag)
	{ if(!dsm_client_ocuppy(compass_dclient)){
		  dsm_client_record(compass_dclient, "[%s]i2c_status:%d,reset is 0x%x,LDO2_status is 0x%x,LDO5_status is 0x%x.\n",__func__, ret,gpio_get_value(s_akm->gpio_rstn),LDO2_status,LDO5_status);
		 dsm_client_notify(compass_dclient, DSM_COMPASS_I2C_RW_ERROR_NO);
		}
	}
#endif
		return -ENXIO;
	}

	compass_FLOW("[COMPASS]RxData: len=%02x, addr=%02x, data=%02x",length, addr, rxData[0]);

	return 0;
}

static int akm_i2c_txdata(
	struct i2c_client *i2c,
	uint8_t *txData,
	int length)
{
	int ret;
#if defined (CONFIG_HUAWEI_DSM)
    unsigned char LDO2_status=0;
	unsigned char LDO5_status=0;
#endif
	struct i2c_msg msg[] = {
		{
			.addr = i2c->addr,
			.flags = 0,
			.len = length,
			.buf = txData,
		},
	};

	ret = i2c_transfer(i2c->adapter, msg, ARRAY_SIZE(msg));
	if (ret < 0) {
		compass_ERR("[COMPASS]%s: transfer failed.", __func__);
#if defined (CONFIG_HUAWEI_DSM)
		LDO2_status = hi6xxx_pmic_reg_read(LDO2_PHYS_ADDR);
		LDO5_status = hi6xxx_pmic_reg_read(LDO5_PHYS_ADDR);
		compass_ERR("[COMPASS]%s: LDO2_status=%d\n", __func__,LDO2_PHYS_ADDR);
		compass_ERR("[COMPASS]%s: LDO5_status=%d\n", __func__,LDO5_PHYS_ADDR);

	if(1==akm09911_flag)
    {
		if(!dsm_client_ocuppy(compass_dclient)){
		dsm_client_record(compass_dclient, "[%s]i2c_status:%d,reset is 0x%x,LDO2_status is 0x%x,LDO5_status is 0x%x.\n",__func__, ret,gpio_get_value(s_akm->gpio_rstn),LDO2_status,LDO5_status);
		dsm_client_notify(compass_dclient, DSM_COMPASS_I2C_RW_ERROR_NO);
		}
	}
#endif
		return ret;
	} else if (ret != ARRAY_SIZE(msg)) {
		compass_ERR("[COMPASS]%s: transfer failed(size error).",__func__);

#if defined (CONFIG_HUAWEI_DSM)
	if(1==akm09911_flag)
	{
		if(!dsm_client_ocuppy(compass_dclient)){
		LDO2_status = hi6xxx_pmic_reg_read(LDO2_PHYS_ADDR);
		LDO5_status = hi6xxx_pmic_reg_read(LDO5_PHYS_ADDR);
		compass_ERR("[COMPASS]%s: LDO2_status=%d\n", __func__,LDO2_PHYS_ADDR);
		compass_ERR("[COMPASS]%s: LDO5_status=%d\n", __func__,LDO5_PHYS_ADDR);
		//gpio_get_value(s_akm->gpio_rstn);
		dsm_client_record(compass_dclient, "[%s]i2c_status:%d,reset is 0x%x,LDO2_status is 0x%x,LDO5_status is 0x%x.\n",__func__, ret,gpio_get_value(s_akm->gpio_rstn),LDO2_status,LDO5_status);
		dsm_client_notify(compass_dclient, DSM_COMPASS_I2C_RW_ERROR_NO);
		}
	}
#endif
		return -ENXIO;
	}

	compass_FLOW("[COMPASS]TxData: len=%02x, addr=%02x data=%02x",length, txData[0], txData[1]);

	return 0;
}

#if 0

static int akm_regulator_configure(struct akm09911_platform_data *pdata, struct i2c_client *client)
{
	int rc;

	pdata->akm_vdd = regulator_get(&client->dev, "SENSORS_ANALOG_VDD");
	if (IS_ERR(pdata->akm_vdd)) {
		rc = PTR_ERR(pdata->akm_vdd);
		compass_ERR("[COMPASS]Regulator get failed akm_vdd rc=%d\n", rc);
		return rc;
	}

	rc = regulator_set_voltage(pdata->akm_vdd, 2850000,
							2850000);
		if (rc) {
			compass_ERR("[COMPASS]regulator set_vtg failed rc=%d\n", rc);
			return rc;
		}
	
       pdata->akm_io_vdd = regulator_get(&client->dev, "SENSOR_IO_VDD");
	if (IS_ERR(pdata->akm_io_vdd)) {
		rc = PTR_ERR(pdata->akm_io_vdd);
	compass_ERR("[COMPASS]Regulator get failed apds990x_io_vdd rc=%d\n", rc);
		return rc;
	}

	return 0;
}
static int  akm_regulator_enable(struct akm09911_platform_data *pdata)
{
int rc = 1;
rc = regulator_enable(pdata->akm_vdd);
	if (rc) {
		compass_INFO("[COMPASS]Regulator akm_vdd enable failed rc=%d\n", rc);
		return rc;
		}

	rc = regulator_enable(pdata->akm_io_vdd);
	if (rc) {

		compass_INFO("[COMPASS]Regulator akm_io_vdd enable failed rc=%d\n", rc);
		return rc;
	}

}
static int  akm_regulator_disable(struct akm09911_platform_data *pdata)
{
	int rc = 1;
      rc = regulator_disable(pdata->akm_vdd);
	if (rc) {

		compass_INFO("[COMPASS]Regulator akm_vdd disable failed rc=%d\n", rc);
		return rc;
		}

	rc = regulator_disable(pdata->akm_io_vdd);
	if (rc) {

		compass_INFO("[COMPASS]Regulator akm_io_vdd disable failed rc=%d\n", rc);
		return rc;
	}

}

#endif

/***** akm miscdevice functions *************************************/
static int AKECS_Set_CNTL(
	struct akm_compass_data *akm,
	uint8_t mode)
{
	uint8_t buffer[2];
	int err;

	/***** lock *****/
	mutex_lock(&akm->sensor_mutex);
	/* Busy check */
	if (akm->is_busy > 0) {
		compass_ERR("[COMPASS]%s: device is busy.", __func__);
		err = -EBUSY;
	} else {
		/* Set measure mode */
		buffer[0] = AKM_REG_MODE;
		buffer[1] = mode;
		err = akm_i2c_txdata(akm->i2c, buffer, 2);
		if (err < 0) {
			compass_ERR("[COMPASS]%s: Can not set CNTL.", __func__);
		} else {
			compass_FLOW("[COMPASS]Mode is set to (%d).", mode);
			/* Set flag */
			akm->is_busy = 1;
			atomic_set(&akm->drdy, 0);
			/* wait at least 100us after changing mode */
			udelay(100);
		}
	}

	mutex_unlock(&akm->sensor_mutex);
	/***** unlock *****/

	return err;
}

static int AKECS_Set_PowerDown(
	struct akm_compass_data *akm)
{
	uint8_t buffer[2];
	int err;

	/***** lock *****/
	mutex_lock(&akm->sensor_mutex);
	/* Set powerdown mode */
	buffer[0] = AKM_REG_MODE;
	buffer[1] = AKM_MODE_POWERDOWN;
	err = akm_i2c_txdata(akm->i2c, buffer, 2);
	if (err < 0) {
		compass_ERR("[COMPASS]%s: Can not set to powerdown mode.", __func__);
	} else {
		compass_FLOW("[COMPASS]Powerdown mode is set.");
		/* wait at least 100us after changing mode */
		udelay(100);
	}
	/* Clear status */
	akm->is_busy = 0;
	atomic_set(&akm->drdy, 0);

	mutex_unlock(&akm->sensor_mutex);
	/***** unlock *****/

	return err;
}

static int AKECS_Reset(
	struct akm_compass_data *akm,
	int hard)
{
	int err;
#if AKM_HAS_RESET
	uint8_t buffer[2];

	/***** lock *****/
	mutex_lock(&akm->sensor_mutex);

	if (hard != 0) {
		gpio_set_value(akm->gpio_rstn, 0);
		udelay(5);
		gpio_set_value(akm->gpio_rstn, 1);
		/* No error is returned */
		err = 0;
	} else {
		buffer[0] = AKM_REG_RESET;
		buffer[1] = AKM_RESET_DATA;
		err = akm_i2c_txdata(akm->i2c, buffer, 2);
		if (err < 0) {
			compass_ERR("[COMPASS]%s: Can not set SRST bit.", __func__);
		}
		else
		{
			compass_FLOW("[COMPASS]Soft reset is done.");
		}
	}
	/* Device will be accessible 100 us after */
	udelay(100);
	/* Clear status */
	akm->is_busy = 0;
	atomic_set(&akm->drdy, 0);

	mutex_unlock(&akm->sensor_mutex);
	/***** unlock *****/

#else
	err = AKECS_Set_PowerDown(akm);
#endif

	return err;
}

static int AKECS_SetMode(
	struct akm_compass_data *akm,
	uint8_t mode)
{
	int err;
    compass_INFO("[COMPASS]akm09911 AKECS_SetMode mode = %x\n",mode);

#if AKM_DEBUG_IF
	akm->debug_mode = mode;
#endif

	switch (mode & 0x1F) {
	case AKM_MODE_SNG_MEASURE:
	case AKM_MODE_SELF_TEST:
	case AKM_MODE_FUSE_ACCESS:
	case AKM_MODE_CONTINUOUS_10HZ:
	case AKM_MODE_CONTINUOUS_20HZ:
	case AKM_MODE_CONTINUOUS_50HZ:
	case AKM_MODE_CONTINUOUS_100HZ:
		err = AKECS_Set_CNTL(akm, mode);
		break;
	case AKM_MODE_POWERDOWN:
		err = AKECS_Set_PowerDown(akm);
		break;
	default:
		compass_ERR("[COMPASS]%s: Unknown mode(%d).", __func__, mode);
		return -EINVAL;
	}

	return err;
}
static void AKECS_SetYPR(
	struct akm_compass_data *akm,
	int *rbuf)
{
	uint32_t ready;

	compass_FLOW("[COMPASS]%s: flag =0x%X", __func__, rbuf[0]);
	compass_FLOW("[COMPASS] Acc [LSB]  : %6d,%6d,%6d stat=%d",rbuf[1], rbuf[2], rbuf[3], rbuf[4]);
	compass_FLOW("[COMPASS] Geo [LSB]   : %6d,%6d,%6d stat=%d",
		rbuf[5], rbuf[6], rbuf[7], rbuf[8]);
	compass_FLOW("[COMPASS]  Gyro[LSB]   : %6d,%6d,%6d stat=%d",
		rbuf[9], rbuf[10], rbuf[11], rbuf[12]);
	compass_FLOW("[COMPASS]  Orientation : %6d,%6d,%6d",
		rbuf[13], rbuf[14], rbuf[15]);
	compass_FLOW("[COMPASS]  Gravity     : %6d,%6d,%6d",
		rbuf[16], rbuf[17], rbuf[18]);
	compass_FLOW("[COMPASS]  Linear Acc  : %6d,%6d,%6d",
		rbuf[19], rbuf[20], rbuf[21]);
	compass_FLOW("[COMPASS]  Rotation V  : %6d,%6d,%6d,%6d",
		rbuf[22], rbuf[23], rbuf[24], rbuf[25]);
	/* No events are reported */
	if (!rbuf[0]) {
		compass_FLOW("[COMPASS]Don't waste a time.");
		return;
	}

	mutex_lock(&akm->val_mutex);
	ready = (akm->enable_flag & (uint32_t)rbuf[0]);
	mutex_unlock(&akm->val_mutex);

	/* Report acceleration sensor information */
	if (ready & ACC_DATA_READY) {
		input_report_abs(akm->input, ABS_X, rbuf[1]);
		input_report_abs(akm->input, ABS_Y, rbuf[2]);
		input_report_abs(akm->input, ABS_Z, rbuf[3]);
		input_report_abs(akm->input, ABS_RX, rbuf[4]);
	}
	/* Report magnetic vector information */
	if (ready & MAG_DATA_READY) {
		input_report_abs(akm->input, ABS_RY, rbuf[5]);
		input_report_abs(akm->input, ABS_RZ, rbuf[6]);
		input_report_abs(akm->input, ABS_THROTTLE, rbuf[7]);
		input_report_abs(akm->input, ABS_RUDDER, rbuf[8]);
		if(DT_tset)
		{
			compass_data_count++;
		}
	}
	/* Report fusion sensor information */
	if (ready & FUSION_DATA_READY) {
		/* Gyroscope sensor */
		input_report_abs(akm->input, ABS_WHEEL, rbuf[9]);
		input_report_abs(akm->input, ABS_GAS,   rbuf[10]);
		input_report_abs(akm->input, ABS_BRAKE, rbuf[11]);
		input_report_abs(akm->input, ABS_HAT0X, rbuf[12]);
		/* Orientation */
		input_report_abs(akm->input, ABS_HAT0Y, rbuf[13]);
		input_report_abs(akm->input, ABS_HAT1X, rbuf[14]);
		input_report_abs(akm->input, ABS_HAT1Y, rbuf[15]);
		/* Gravity */
		input_report_abs(akm->input, ABS_HAT2X, rbuf[16]);
		input_report_abs(akm->input, ABS_HAT2Y, rbuf[17]);
		input_report_abs(akm->input, ABS_HAT3X, rbuf[18]);
		/* Linear Acceleration */
		input_report_abs(akm->input, ABS_HAT3Y, rbuf[19]);
		input_report_abs(akm->input, ABS_PRESSURE, rbuf[20]);
		input_report_abs(akm->input, ABS_DISTANCE, rbuf[21]);
		/* Rotation Vector */
		input_report_abs(akm->input, ABS_TILT_X, rbuf[22]);
		input_report_abs(akm->input, ABS_TILT_Y, rbuf[23]);
		input_report_abs(akm->input, ABS_TOOL_WIDTH, rbuf[24]);
		input_report_abs(akm->input, ABS_VOLUME, rbuf[25]);
		if(DT_tset)
		{
			
			Gyro_data_count++;
		}
	}

	input_sync(akm->input);
}
/* This function will block a process until the latest measurement
 * data is available.
 */
static int AKECS_GetData(
	struct akm_compass_data *akm,
	uint8_t *rbuf,
	int size)
{
	int err;
	/* Block! */
	err = wait_event_interruptible_timeout(
			akm->drdy_wq,
			atomic_read(&akm->drdy),
			msecs_to_jiffies(AKM_DRDY_TIMEOUT_MS));

	if (err < 0) {
		compass_ERR("[COMPASS]%s: wait_event failed (%d).", __func__, err);
		return err;
	}
	if (!atomic_read(&akm->drdy)) {
		compass_ERR("[COMPASS]%s: DRDY is not set.", __func__);
		return -ENODATA;
	}

	/***** lock *****/
	mutex_lock(&akm->sensor_mutex);

	memcpy(rbuf, akm->sense_data, size);
	atomic_set(&akm->drdy, 0);

	mutex_unlock(&akm->sensor_mutex);
	/***** unlock *****/

	return 0;
}

static int AKECS_GetData_Poll(
	struct akm_compass_data *akm,
	uint8_t *rbuf,
	int size,
	bool is_self_test)
{
	uint8_t buffer[AKM_SENSOR_DATA_SIZE];
	int err;

	/* Read status */
	buffer[0] = AKM_REG_STATUS;
	err = akm_i2c_rxdata(akm->i2c, buffer, 1);
	if (err < 0) {
		compass_ERR("[COMPASS]%s failed.", __func__);
		return err;
	}

	/* Check ST bit */
	if (!(AKM_DRDY_IS_HIGH(buffer[0])))
	{
		{
			return -EAGAIN;
		}
	}


	/* Data is over run is */
	if (AKM_DOR_IS_HIGH(buffer[0])) {
		dev_dbg(&akm->i2c->dev, "Data over run!\n");
      }

	/* Read rest data */
	buffer[1] = AKM_REG_STATUS + 1;
	err = akm_i2c_rxdata(akm->i2c, &(buffer[1]), AKM_SENSOR_DATA_SIZE-1);
	if (err < 0) {
		compass_ERR("[COMPASS]%s failed.", __func__);
		return err;
	}

	memcpy(rbuf, buffer, size);
	atomic_set(&akm->drdy, 0);

	/***** lock *****/
	mutex_lock(&akm->sensor_mutex);
	akm->is_busy = 0;
	mutex_unlock(&akm->sensor_mutex);
	/***** unlock *****/

	return 0;
}

static int AKECS_GetOpenStatus(
	struct akm_compass_data *akm)
{
	return wait_event_interruptible(
			akm->open_wq, (atomic_read(&akm->active) > 0));
}

static int AKECS_GetCloseStatus(
	struct akm_compass_data *akm)
{
	return wait_event_interruptible(
			akm->open_wq, (atomic_read(&akm->active) <= 0));
}

static int AKECS_Open(struct inode *inode, struct file *file)
{
	file->private_data = s_akm;
	return nonseekable_open(inode, file);
}

static int AKECS_Release(struct inode *inode, struct file *file)
{
	return 0;
}

static long
AKECS_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	struct akm_compass_data *akm = file->private_data;

	/* NOTE: In this function the size of "char" should be 1-byte. */
	uint8_t i2c_buf[AKM_RWBUF_SIZE];		/* for READ/WRITE */
	uint8_t dat_buf[AKM_SENSOR_DATA_SIZE];/* for GET_DATA */
	int32_t ypr_buf[AKM_YPR_DATA_SIZE];		/* for SET_YPR */
	int64_t delay[AKM_NUM_SENSORS];	/* for GET_DELAY */
	int16_t acc_buf[3];	/* for GET_ACCEL */
	uint8_t mode;			/* for SET_MODE*/
	int status;			/* for OPEN/CLOSE_STATUS */
	int ret = 0;		/* Return value. */

	memset(i2c_buf, 0, AKM_RWBUF_SIZE);

	switch (cmd) {
	case ECS_IOCTL_READ:
	case ECS_IOCTL_WRITE:
		if (argp == NULL) {
			compass_ERR("[COMPASS]invalid argument.");
			return -EINVAL;
		}
		if (copy_from_user(&i2c_buf, argp, sizeof(i2c_buf))) {
			compass_ERR("[COMPASS]copy_from_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_SET_MODE:
		if (argp == NULL) {
			compass_ERR("[COMPASS]invalid argument.");
			return -EINVAL;
		}
		if (copy_from_user(&mode, argp, sizeof(mode))) {
			compass_ERR("[COMPASS]copy_from_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_SET_YPR:
		if (argp == NULL) {
			compass_ERR("[COMPASS]invalid argument.");
			return -EINVAL;
		}
		if (copy_from_user(&ypr_buf, argp, sizeof(ypr_buf))) {
			compass_ERR("[COMPASS]copy_from_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_INFO:
	case ECS_IOCTL_GET_CONF:
	case ECS_IOCTL_GET_DATA:
	case ECS_IOCTL_GET_OPEN_STATUS:
	case ECS_IOCTL_GET_CLOSE_STATUS:
	case ECS_IOCTL_GET_DELAY:
	case ECS_IOCTL_GET_LAYOUT:
	case ECS_IOCTL_GET_ACCEL:
		/* Check buffer pointer for writing a data later. */
		if (argp == NULL) {
			compass_ERR("[COMPASS]invalid argument.");
			return -EINVAL;
		}
		break;
	default:
		break;
	}

	switch (cmd) {
	case ECS_IOCTL_READ:
		compass_FLOW("[COMPASS]IOCTL_READ called.");
		if ((i2c_buf[0] < 1) || (i2c_buf[0] > (AKM_RWBUF_SIZE-1))) {
			compass_ERR("[COMPASS]invalid argument.");
			return -EINVAL;
		}
		ret = akm_i2c_rxdata(akm->i2c, &i2c_buf[1], i2c_buf[0]);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_WRITE:

		compass_FLOW("[COMPASS]IOCTL_WRITE called.");
		if ((i2c_buf[0] < 2) || (i2c_buf[0] > (AKM_RWBUF_SIZE-1))) {
		compass_ERR("[COMPASS]invalid argument.");
			return -EINVAL;
		}
		ret = akm_i2c_txdata(akm->i2c, &i2c_buf[1], i2c_buf[0]);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_RESET:

		compass_FLOW("[COMPASS]IOCTL_RESET called.");
		ret = AKECS_Reset(akm, akm->gpio_rstn);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_SET_MODE:

		compass_FLOW("[COMPASS]IOCTL_SET_MODE called.");
		ret = AKECS_SetMode(akm, mode);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_SET_YPR:

		compass_FLOW("[COMPASS]IOCTL_SET_YPR called.");
		AKECS_SetYPR(akm, ypr_buf);
		break;
	case ECS_IOCTL_GET_DATA:

		compass_FLOW("[COMPASS]IOCTL_GET_DATA called.");
		if (akm->irq)
			ret = AKECS_GetData(akm, dat_buf, AKM_SENSOR_DATA_SIZE);
		else
			ret = AKECS_GetData_Poll(
					akm, dat_buf, AKM_SENSOR_DATA_SIZE, false);

		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_GET_OPEN_STATUS:

		compass_FLOW("[COMPASS]IOCTL_GET_OPEN_STATUS called.");
		ret = AKECS_GetOpenStatus(akm);
		if (ret < 0) {
			compass_ERR("[COMPASS]Get Open returns error (%d).", ret);
			return ret;
		}
		break;
	case ECS_IOCTL_GET_CLOSE_STATUS:

		compass_FLOW("[COMPASS]IOCTL_GET_CLOSE_STATUS called.");
		ret = AKECS_GetCloseStatus(akm);
		if (ret < 0) {
			compass_ERR("[COMPASS]Get Close returns error (%d).", ret);
			return ret;
		}
		break;
	case ECS_IOCTL_GET_DELAY:

		compass_FLOW("[COMPASS]IOCTL_GET_DELAY called.");
		mutex_lock(&akm->val_mutex);
		delay[0] = ((akm->enable_flag & ACC_DATA_READY) ?
				akm->delay[0] : -1);
		delay[1] = ((akm->enable_flag & MAG_DATA_READY) ?
				akm->delay[1] : -1);
		delay[2] = ((akm->enable_flag & FUSION_DATA_READY) ?
				akm->delay[2] : -1);
		mutex_unlock(&akm->val_mutex);
		break;
	case ECS_IOCTL_GET_INFO:
		compass_FLOW("[COMPASS]IOCTL_GET_INFO called.");
		break;
	case ECS_IOCTL_GET_CONF:

		compass_FLOW("[COMPASS]IOCTL_GET_CONF called.");
		break;
	case ECS_IOCTL_GET_LAYOUT:

		compass_FLOW("[COMPASS]IOCTL_GET_LAYOUT called.");
		break;
	case ECS_IOCTL_GET_ACCEL:

		compass_FLOW("[COMPASS]IOCTL_GET_ACCEL called.");
		mutex_lock(&akm->accel_mutex);
		acc_buf[0] = akm->accel_data[0];
		acc_buf[1] = akm->accel_data[1];
		acc_buf[2] = akm->accel_data[2];
		mutex_unlock(&akm->accel_mutex);
		break;
	default:
		return -ENOTTY;
	}

	switch (cmd) {
	case ECS_IOCTL_READ:
		/* +1  is for the first byte */
		if (copy_to_user(argp, &i2c_buf, i2c_buf[0]+1)) {

			compass_ERR("[COMPASS]copy_to_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_INFO:
		if (copy_to_user(argp, &akm->sense_info,
					sizeof(akm->sense_info))) {

			compass_ERR("[COMPASS]copy_to_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_CONF:
		if (copy_to_user(argp, &akm->sense_conf,
					sizeof(akm->sense_conf))) {
			compass_ERR("[COMPASS]copy_to_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_DATA:
		if (copy_to_user(argp, &dat_buf, sizeof(dat_buf))) {

			compass_ERR("[COMPASS]copy_to_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_OPEN_STATUS:
	case ECS_IOCTL_GET_CLOSE_STATUS:
		status = atomic_read(&akm->active);
		if (copy_to_user(argp, &status, sizeof(status))) {
			compass_ERR("[COMPASS]copy_to_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_DELAY:
		if (copy_to_user(argp, &delay, sizeof(delay))) {
			compass_ERR("[COMPASS]copy_to_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_LAYOUT:
		if (copy_to_user(argp, &akm->layout, sizeof(akm->layout))) {
			compass_ERR("[COMPASS]copy_to_user failed.");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_ACCEL:
		if (copy_to_user(argp, &acc_buf, sizeof(acc_buf))) {
			compass_ERR("[COMPASS]copy_to_user failed.");
			return -EFAULT;
		}
		break;
	default:
		break;
	}

	return 0;
}

static const struct file_operations AKECS_fops = {
	.owner = THIS_MODULE,
	.open = AKECS_Open,
	.release = AKECS_Release,
	.unlocked_ioctl = AKECS_ioctl,
};

static struct miscdevice akm_compass_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = AKM_MISCDEV_NAME,
	.fops = &AKECS_fops,
};

/***** akm sysfs functions ******************************************/
static int create_device_attributes(
	struct device *dev,
	struct device_attribute *attrs)
{
	int i;
	int err = 0;
	for (i = 0 ; NULL != attrs[i].attr.name ; ++i) {
		err = device_create_file(dev, &attrs[i]);
		if (err)
			break;
	}

	if (err) {
		for (--i; i >= 0 ; --i)
			device_remove_file(dev, &attrs[i]);
	}

	return err;
}

static void remove_device_attributes(
	struct device *dev,
	struct device_attribute *attrs)
{
	int i;
	for (i = 0 ; NULL != attrs[i].attr.name ; ++i)
		device_remove_file(dev, &attrs[i]);
}

static int create_device_binary_attributes(
	struct kobject *kobj,
	struct bin_attribute *attrs)
{
	int i;
	int err = 0;
	err = 0;

	for (i = 0 ; NULL != attrs[i].attr.name ; ++i) {
		err = sysfs_create_bin_file(kobj, &attrs[i]);
		if (0 != err)
			break;
	}

	if (0 != err) {
		for (--i; i >= 0 ; --i)
			sysfs_remove_bin_file(kobj, &attrs[i]);
	}

	return err;
}

static void remove_device_binary_attributes(
	struct kobject *kobj,
	struct bin_attribute *attrs)
{
	int i;

	for (i = 0 ; NULL != attrs[i].attr.name ; ++i)
		sysfs_remove_bin_file(kobj, &attrs[i]);
}

/*********************************************************************
 *
 * SysFS attribute functions
 *
 * directory : /sys/class/compass/akmXXXX/
 * files :
 *  - enable_acc    [rw] [t] : enable flag for accelerometer
 *  - enable_mag    [rw] [t] : enable flag for magnetometer
 *  - enable_maguc  [rw] [t] : enable flag for uncalibrated magnetometer
 *  - enable_fusion [rw] [t] : enable flag for fusion sensor
 *  - delay_acc     [rw] [t] : delay in nanosecond for accelerometer
 *  - delay_mag     [rw] [t] : delay in nanosecond for magnetometer
 *  - delay_maguc   [rw] [t] : delay in nanosecond for uncalibrated magnetometer
 *  - delay_fusion  [rw] [t] : delay in nanosecond for fusion sensor
 *
 * debug :
 *  - mode       [w]  [t] : E-Compass mode
 *  - bdata      [r]  [t] : buffered raw data
 *  - asa        [r]  [t] : FUSEROM data
 *  - regs       [r]  [t] : read all registers
 *
 * [b] = binary format
 * [t] = text format
 */

/***** sysfs enable *************************************************/
static void akm_compass_sysfs_update_status(
	struct akm_compass_data *akm)
{
	uint32_t en;
	mutex_lock(&akm->val_mutex);
	en = akm->enable_flag;
	mutex_unlock(&akm->val_mutex);
	if (en == 0) {
		if (atomic_cmpxchg(&akm->active, 1, 0) == 1) {
			wake_up(&akm->open_wq);
			compass_FLOW("[COMPASS]Deactivated");
		}
	} else {
		if (atomic_cmpxchg(&akm->active, 0, 1) == 0) {
			wake_up(&akm->open_wq);
			compass_FLOW("[COMPASS]Activated");
		}
	}
	compass_FLOW("[COMPASS]Status updated: enable=0x%X, active=%d",en, atomic_read(&akm->active));
	
}

static inline uint8_t akm_select_frequency(int64_t delay_ns)
{
	if (delay_ns >= 100000000LL)
		return AKM_MODE_CONTINUOUS_10HZ;
	else if (delay_ns >= 50000000LL)
		return AKM_MODE_CONTINUOUS_20HZ;
	else if (delay_ns >= 20000000LL)
		return AKM_MODE_CONTINUOUS_50HZ;
	else
		return AKM_MODE_CONTINUOUS_100HZ;
}

static int akm_class_enable_set(struct sensors_classdev *sensors_cdev,unsigned int enable)
{
    	ssize_t ret = 0;
       unsigned int en=enable;
	//struct akm_compass_data *akm = NULL;// = container_of(sensors_cdev,struct akm_compass_data, cdev);
       compass_INFO("[COMPASS]%s,en=%d.\n",__FUNCTION__,en);
       ret= akm_enable_set(container_of(sensors_cdev,struct akm_compass_data, cdev), en);
       if(ret<0)
       {
             compass_ERR("[COMPASS]%s,Fail to enable.\n",__FUNCTION__);
       }
       return ret;
}
static ssize_t akm_enable_set(struct akm_compass_data *akm, unsigned int enable)
{
	long en = 0;
	uint8_t mode;
       int ret = 0;
       en=enable;
       struct akm_compass_data *akm_default=akm;

       mutex_lock(&akm->op_mutex);
        if (en) {
        ret = akm_compass_power_set(akm_default, true);
        if (ret) {
            compass_ERR("[COMPASS]Fail to power on the device!\n");
            goto exit;
        }
        if (akm->auto_report) {
            mode = akm_select_frequency(akm->delay[MAG_DATA_FLAG]);
            mutex_lock(&akm->self_test_mutex);
            compass_INFO("[COMPASS]%s, line %d, enable set mode called!\n", __FUNCTION__, __LINE__);
            AKECS_SetMode(akm, mode);
            mutex_unlock(&akm->self_test_mutex);
            if (akm->use_hrtimer)
                hrtimer_start(&akm->poll_timer,
                        ns_to_ktime(akm->delay[MAG_DATA_FLAG]),
                        HRTIMER_MODE_REL);
            else
                queue_delayed_work(akm->work_queue, &akm->dwork,
                        (unsigned long)nsecs_to_jiffies64(
                            akm->delay[MAG_DATA_FLAG]));
        }
        compass_INFO("[COMPASS]power on the device!\n");
    } else {
        if (akm->auto_report) {
            if (akm->use_hrtimer) {
                hrtimer_cancel(&akm->poll_timer);
                cancel_work_sync(&akm->dwork.work);
            } else {
                cancel_delayed_work_sync(&akm->dwork);
            }
            mutex_lock(&akm->self_test_mutex);
            compass_INFO("[COMPASS]%s, line %d, disable set mode called!\n", __FUNCTION__, __LINE__);
            AKECS_SetMode(akm, AKM_MODE_POWERDOWN);
            mutex_unlock(&akm->self_test_mutex);
        }
        ret = akm_compass_power_set(akm, false);
        if (ret) {
            compass_ERR("[COMPASS]Fail to power off the device!\n");
            goto exit;
        }
        compass_INFO("[COMPASS]power off the device!\n");
    }

exit:
	mutex_unlock(&akm->op_mutex);
	return ret ;
}
static ssize_t akm_compass_sysfs_enable_show(
	struct akm_compass_data *akm, char *buf, int pos)
{
	int flag;
	mutex_lock(&akm->val_mutex);
	flag = ((akm->enable_flag >> pos) & 1);
	mutex_unlock(&akm->val_mutex);

	return scnprintf(buf, PAGE_SIZE, "%d\n", flag);
}

static ssize_t akm_compass_sysfs_enable_store(
	struct akm_compass_data *akm, char const *buf, size_t count, int pos)
{
	long en = 0;
	if (NULL == buf)
		return -EINVAL;

	if (0 == count)
		return 0;

	if (strict_strtol(buf, AKM_BASE_NUM, &en))
		return -EINVAL;
	if(DT_tset)
	{
		
		if(2==en)
		{
			en=1;
		}
		else if(3==en)
		{
			en=0;
		}
		else
		{
			return count;
		}
	}

	en = en ? 1 : 0;

	mutex_lock(&akm->val_mutex);
	akm->enable_flag &= ~(1<<pos);
	akm->enable_flag |= ((uint32_t)(en))<<pos;
	mutex_unlock(&akm->val_mutex);

	akm_compass_sysfs_update_status(akm);

	return count;
}

/***** Acceleration ***/
static ssize_t akm_enable_acc_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm_compass_sysfs_enable_show(
		dev_get_drvdata(dev), buf, ACC_DATA_FLAG);
}
static ssize_t akm_enable_acc_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm_compass_sysfs_enable_store(
		dev_get_drvdata(dev), buf, count, ACC_DATA_FLAG);
}

/***** Magnetic field ***/
static ssize_t akm_enable_mag_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm_compass_sysfs_enable_show(
		dev_get_drvdata(dev), buf, MAG_DATA_FLAG);
}
static ssize_t akm_enable_mag_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm_compass_sysfs_enable_store(
		dev_get_drvdata(dev), buf, count, MAG_DATA_FLAG);
}

/***** Fusion ***/
static ssize_t akm_enable_fusion_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm_compass_sysfs_enable_show(
		dev_get_drvdata(dev), buf, FUSION_DATA_FLAG);
}
static ssize_t akm_enable_fusion_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm_compass_sysfs_enable_store(
		dev_get_drvdata(dev), buf, count, FUSION_DATA_FLAG);
}
/***** sysfs delay **************************************************/
static int akm_poll_delay_set(struct akm_compass_data *akm)
{
    uint8_t mode;
    int ret;

    mutex_lock(&akm->val_mutex);
    mutex_lock(&akm->self_test_mutex);
    mode = akm_select_frequency(akm->delay[MAG_DATA_FLAG]);
    /*before change compass mode, set to power down mode first*/
    compass_INFO("[COMPASS]%s, line %d, set mode called!\n", __FUNCTION__, __LINE__);
    ret = AKECS_SetMode(akm, AKM_MODE_POWERDOWN);
    if(ret < 0)
    {
        compass_ERR("[COMPASS]Failed to set to power down mode\n");
    }
    ret = AKECS_SetMode(akm, mode);
    if (ret < 0)
    {
        compass_ERR("[COMPASS]Failed to set to mode(%x)\n", mode);
    }
    mutex_unlock(&akm->self_test_mutex);
    mutex_unlock(&akm->val_mutex);

	return ret;
}
static int akm_class_poll_delay_set(struct sensors_classdev *sensors_cdev,unsigned int delay_msec)
{
    int ret = 0;
    struct akm_compass_data *akm = container_of(sensors_cdev,struct akm_compass_data, cdev);
    compass_INFO("[COMPASS]akm_class_poll_delay_set,delay_msec=%d!\n",delay_msec);
    mutex_lock(&akm->val_mutex);
    akm->delay[MAG_DATA_FLAG] = delay_msec*1000000;
    mutex_unlock(&akm->val_mutex);
    ret = akm_poll_delay_set(akm);
    if (ret < 0) 
    {
        compass_ERR("[COMPASS]Fail to set mag poll delay!\n");
    }
    return ret;
}
static ssize_t akm_compass_sysfs_delay_show(
	struct akm_compass_data *akm, char *buf, int pos)
{
	int64_t val;
	mutex_lock(&akm->val_mutex);
	val = akm->delay[pos];
	mutex_unlock(&akm->val_mutex);

	return scnprintf(buf, PAGE_SIZE, "%lld\n", val);
}

static ssize_t akm_compass_sysfs_delay_store(
	struct akm_compass_data *akm, char const *buf, size_t count, int pos)
{
	long long val = 0;
	if (NULL == buf)
		return -EINVAL;

	if (0 == count)
		return 0;

	if (strict_strtoll(buf, AKM_BASE_NUM, &val))
		return -EINVAL;
	if(DT_tset)
	{
		if(10!=val)
		{
			return count;
		}
	}
	mutex_lock(&akm->val_mutex);
	akm->delay[pos] = val;
	mutex_unlock(&akm->val_mutex);

	return count;
}

/***** Accelerometer ***/
static ssize_t akm_delay_acc_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm_compass_sysfs_delay_show(
		dev_get_drvdata(dev), buf, ACC_DATA_FLAG);
}
static ssize_t akm_delay_acc_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm_compass_sysfs_delay_store(
		dev_get_drvdata(dev), buf, count, ACC_DATA_FLAG);
}

/***** Magnetic field ***/
static ssize_t akm_delay_mag_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm_compass_sysfs_delay_show(
		dev_get_drvdata(dev), buf, MAG_DATA_FLAG);
}
static ssize_t akm_delay_mag_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm_compass_sysfs_delay_store(
		dev_get_drvdata(dev), buf, count, MAG_DATA_FLAG);
}

/***** Fusion ***/
static ssize_t akm_delay_fusion_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm_compass_sysfs_delay_show(
		dev_get_drvdata(dev), buf, FUSION_DATA_FLAG);
}
static ssize_t akm_delay_fusion_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm_compass_sysfs_delay_store(
		dev_get_drvdata(dev), buf, count, FUSION_DATA_FLAG);
}
/***** accel (binary) ***/
static ssize_t akm_bin_accel_write(
	struct file *file,
	struct kobject *kobj,
	struct bin_attribute *attr,
		char *buf,
		loff_t pos,
		size_t size)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct akm_compass_data *akm = dev_get_drvdata(dev);
	int16_t *accel_data;
	if (size == 0)
		return 0;

	accel_data = (int16_t *)buf;

	mutex_lock(&akm->accel_mutex);
	akm->accel_data[0] = accel_data[0];
	akm->accel_data[1] = accel_data[1];
	akm->accel_data[2] = accel_data[2];
	mutex_unlock(&akm->accel_mutex);

	compass_FLOW("[COMPASS]accel:%d,%d,%d\n",
			accel_data[0], accel_data[1], accel_data[2]);

	return size;
}
static ssize_t akm_set_cal_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	int err = 0;

	compass_INFO("[COMPASS]akm_set_cal_show,calibration_value=%d\n",calibration_value);
	err = snprintf(buf, PAGE_SIZE, "%d\n", calibration_value);
	return err;
}
static ssize_t akm_set_cal_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	calibration_value =  (int)(buf[0] - '0');

	compass_INFO("[COMPASS]akm_set_cal_store,calibration_value=%d\n",calibration_value);
	return 0;
}
#if AKM_DEBUG_IF
static ssize_t akm_sysfs_mode_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	struct akm_compass_data *akm = dev_get_drvdata(dev);
	long mode = 0;
	if (NULL == buf)
		return -EINVAL;

	if (0 == count)
		return 0;

	if (strict_strtol(buf, AKM_BASE_NUM, &mode))
		return -EINVAL;

	if (AKECS_SetMode(akm, (uint8_t)mode) < 0)
		return -EINVAL;

	return 1;
}

static ssize_t akm_sysfs_mode_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	struct akm_compass_data *akm = dev_get_drvdata(dev);
	uint8_t rbuf;

	mutex_lock(&akm->sensor_mutex);
	rbuf = akm->debug_mode;
	mutex_unlock(&akm->sensor_mutex);

	return scnprintf(buf, PAGE_SIZE, "0x%X\n", rbuf);
}

static ssize_t akm09911_sysfs_bdata_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	/* AK09911 specific function */
	struct akm_compass_data *akm = dev_get_drvdata(dev);
	uint8_t rbuf[AKM_SENSOR_DATA_SIZE];
	mutex_lock(&akm->sensor_mutex);
	memcpy(&rbuf, akm->sense_data, sizeof(rbuf));
	mutex_unlock(&akm->sensor_mutex);

	return scnprintf(buf, PAGE_SIZE,
		"0x%02X,0x%02X,0x%02X,0x%02X,"
		"0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\n",
		rbuf[0], rbuf[1], rbuf[2], rbuf[3],
		rbuf[4], rbuf[5], rbuf[6], rbuf[7], rbuf[8]);
}

static ssize_t akm09911_sysfs_bdata_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return 0;
}

static ssize_t akm09911_sysfs_asa_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	/* AK09911 specific function */
	struct akm_compass_data *akm = dev_get_drvdata(dev);
	int err;
	uint8_t asa[3];
	err = AKECS_SetMode(akm, AK09911_MODE_FUSE_ACCESS);
	if (err < 0)
		return err;

	asa[0] = AK09911_FUSE_ASAX;
	err = akm_i2c_rxdata(akm->i2c, asa, 3);
	if (err < 0)
		return err;

	err = AKECS_SetMode(akm, AK09911_MODE_POWERDOWN);
	if (err < 0)
		return err;

	return scnprintf(buf, PAGE_SIZE,
			"0x%02X,0x%02X,0x%02X\n", asa[0], asa[1], asa[2]);
}

static ssize_t akm09911_sysfs_asa_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return 0;
}

static ssize_t akm09911_sysfs_regs_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	/* AK09911 specific function */
	/* The total number of registers depends on the device. */
	struct akm_compass_data *akm = dev_get_drvdata(dev);
	int err;
	uint8_t regs[13];
	int sz;
	int n;
	char *cur;
	/* This function does not lock mutex obj */
	regs[0] = AK09911_REG_WIA1;
	err = akm_i2c_rxdata(akm->i2c, regs, 13);
	if (err < 0)
		return err;

	cur = buf;
	sz = snprintf(cur, PAGE_SIZE, "(HEX):");
	cur += sz;
	for (n = 0; n < 13; n++) {
		sz = snprintf(cur, 4, "%02X,", regs[n]);
		cur += sz;
	}

	return (ssize_t)(cur - buf);
}

static ssize_t akm09911_sysfs_regs_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return 0;
}
#endif


static ssize_t attr_get_accl_info(struct device *dev,
                 struct device_attribute *attr, char *buf)
{
	ssize_t count;
	count = snprintf(buf, PAGE_SIZE, "AKM_09911");
	return count;
}

static ssize_t attr_set_accl_info(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return 0;
}
static int akm_class_self_test(struct sensors_classdev *sensors_cdev) 
{
    uint8_t ret = 0;
    struct akm_compass_data *akm = container_of(sensors_cdev,struct akm_compass_data, cdev);
    ret=akm_self_test_body(akm);
    return ret;
}
static ssize_t akm_self_test_show(struct device *dev,
                 struct device_attribute *attr, char *buf)
{
	ssize_t count;
    uint8_t ret = 0;
	struct akm_compass_data *akm = dev_get_drvdata(dev);

    ret = akm_self_test_body(akm);

	count = snprintf(buf, PAGE_SIZE, "%d\n", ret);
	return count;
}

static ssize_t akm_self_test_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return 0;
}

static struct device_attribute akm_compass_attributes[] = {
	__ATTR(enable_acc, 0664, akm_enable_acc_show, akm_enable_acc_store),
	__ATTR(enable_mag, 0664, akm_enable_mag_show, akm_enable_mag_store),
	__ATTR(enable_fusion, 0664, akm_enable_fusion_show,
			akm_enable_fusion_store),
	__ATTR(delay_acc,  0664, akm_delay_acc_show,  akm_delay_acc_store),
	__ATTR(delay_mag,  0664, akm_delay_mag_show,  akm_delay_mag_store),
	__ATTR(delay_fusion, 0664, akm_delay_fusion_show,	akm_delay_fusion_store),
	__ATTR(set_cal,  0664, akm_set_cal_show,  akm_set_cal_store),
	__ATTR(compass_info, 0664, attr_get_accl_info, attr_set_accl_info),

	__ATTR(self_test, 0664, akm_self_test_show, akm_self_test_store),


#if AKM_DEBUG_IF
	__ATTR(mode,  0664, akm_sysfs_mode_show, akm_sysfs_mode_store),
	__ATTR(bdata, 0664, akm09911_sysfs_bdata_show, akm09911_sysfs_bdata_store),
	__ATTR(asa,   0664, akm09911_sysfs_asa_show, akm09911_sysfs_asa_store),
	__ATTR(regs,  0664, akm09911_sysfs_regs_show, akm09911_sysfs_regs_store),
#endif
	__ATTR_NULL,
};
#define __BIN_ATTR(name_, mode_, size_, private_, read_, write_) \
	{ \
		.attr    = { .name = __stringify(name_), .mode = mode_ }, \
		.size    = size_, \
		.private = private_, \
		.read    = read_, \
		.write   = write_, \
	}

#define __BIN_ATTR_NULL \
	{ \
		.attr   = { .name = NULL }, \
	}

static struct bin_attribute akm_compass_bin_attributes[] = {
	__BIN_ATTR(accel, 0220, 6, NULL,
				NULL, akm_bin_accel_write),
	__BIN_ATTR_NULL
};

static char const *const device_link_name = "i2c";
static dev_t const akm_compass_device_dev_t = MKDEV(MISC_MAJOR, 240);

static int create_sysfs_interfaces(struct akm_compass_data *akm)
{
	int err;

	if (NULL == akm)
		return -EINVAL;

	err = 0;

	akm->compass = class_create(THIS_MODULE, AKM_SYSCLS_NAME);
	if (IS_ERR(akm->compass)) {
		err = PTR_ERR(akm->compass);
		goto exit_class_create_failed;
	}

	akm->class_dev = device_create(
						akm->compass,
						NULL,
						akm_compass_device_dev_t,
						akm,
						AKM_SYSDEV_NAME);
	if (IS_ERR(akm->class_dev)) {
		err = PTR_ERR(akm->class_dev);
		goto exit_class_device_create_failed;
	}

	err = sysfs_create_link(
			&akm->class_dev->kobj,
			&akm->i2c->dev.kobj,
			device_link_name);
	if (0 > err)
		goto exit_sysfs_create_link_failed;

	err = create_device_attributes(
			akm->class_dev,
			akm_compass_attributes);
	if(0 > err)
		goto exit_device_binary_attributes_create_failed;
	err = create_device_binary_attributes(
			&akm->class_dev->kobj,
			akm_compass_bin_attributes);
	if (0 > err)
		goto exit_device_binary_attributes_create_failed;

	return err;

exit_device_binary_attributes_create_failed:
	remove_device_attributes(akm->class_dev, akm_compass_attributes);
exit_device_attributes_create_failed:
	sysfs_remove_link(&akm->class_dev->kobj, device_link_name);
exit_sysfs_create_link_failed:
	device_destroy(akm->compass, akm_compass_device_dev_t);
exit_class_device_create_failed:
	akm->class_dev = NULL;
	class_destroy(akm->compass);
exit_class_create_failed:
	akm->compass = NULL;
	return err;
}

static void remove_sysfs_interfaces(struct akm_compass_data *akm)
{
	if (NULL == akm)
		return;

	if (NULL != akm->class_dev) {
		remove_device_binary_attributes(
			&akm->class_dev->kobj,
			akm_compass_bin_attributes);
		remove_device_attributes(
			akm->class_dev,
			akm_compass_attributes);
		sysfs_remove_link(
			&akm->class_dev->kobj,
			device_link_name);
		akm->class_dev = NULL;
	}
	if (NULL != akm->compass) {
		device_destroy(
			akm->compass,
			akm_compass_device_dev_t);
		class_destroy(akm->compass);
		akm->compass = NULL;
	}
}


/***** akm input device functions ***********************************/
static int akm_compass_input_init(
	struct input_dev **input)
{
	int err = 0;
	/* Declare input device */
	*input = input_allocate_device();
	if (!*input)
		return -ENOMEM;

	/* Setup input device */
	
      set_bit(EV_ABS, (*input)->evbit);
	input_set_abs_params(*input, AKM_EVABS_MAG_X,
			-32768, 32767, 0, 0);
	input_set_abs_params(*input, AKM_EVABS_MAG_Y,
			-32768, 32767, 0, 0);
	input_set_abs_params(*input, AKM_EVABS_MAG_Z,
			-32768, 32767, 0, 0);
	/* Report the dummy value */
	input_set_abs_params(*input, ABS_MISC,
			INT_MIN, INT_MAX, 0, 0);

	/* Set name */
	(*input)->name = COMPASS_INPUT_DEV_NAME;

	/* Register */
	err = input_register_device(*input);
	if (err) {
		input_free_device(*input);
		return err;
	}

	return err;
}
/***** akm functions ************************************************/
static irqreturn_t akm_compass_irq(int irq, void *handle)
{
	struct akm_compass_data *akm = handle;
	uint8_t buffer[AKM_SENSOR_DATA_SIZE];
	int err;
	memset(buffer, 0, sizeof(buffer));

	/***** lock *****/
	mutex_lock(&akm->sensor_mutex);

	/* Read whole data */
	buffer[0] = AKM_REG_STATUS;
	err = akm_i2c_rxdata(akm->i2c, buffer, AKM_SENSOR_DATA_SIZE);
	if (err < 0) {
		compass_ERR("[COMPASS]IRQ I2C error.");
		akm->is_busy = 0;
		mutex_unlock(&akm->sensor_mutex);
		/***** unlock *****/

		return IRQ_HANDLED;
	}
	/* Check ST bit */
	if (!(AKM_DRDY_IS_HIGH(buffer[0])))
		goto work_func_none;

	memcpy(akm->sense_data, buffer, AKM_SENSOR_DATA_SIZE);
	akm->is_busy = 0;

	mutex_unlock(&akm->sensor_mutex);
	/***** unlock *****/

	atomic_set(&akm->drdy, 1);
	wake_up(&akm->drdy_wq);

	compass_FLOW("[COMPASS]IRQ handled.");
	return IRQ_HANDLED;

work_func_none:
	mutex_unlock(&akm->sensor_mutex);
	/***** unlock *****/

	compass_FLOW("[COMPASS]IRQ not handled.");
	return IRQ_NONE;
}

static int akm_compass_suspend(struct device *dev)
{
	struct akm_compass_data *akm = dev_get_drvdata(dev);
	int ret = 0;

	if (AKM_IS_MAG_DATA_ENABLED() && akm->auto_report) {
		if (akm->use_hrtimer)
			hrtimer_cancel(&akm->poll_timer);
		else
			cancel_delayed_work_sync(&akm->dwork);
	}

    compass_FLOW("[COMPASS]%s, line %d, set mode called!\n", __FUNCTION__, __LINE__);
    printk("[COMPASS]%s, line %d, set mode called!\n", __FUNCTION__, __LINE__);
	ret = AKECS_SetMode(akm, AKM_MODE_POWERDOWN);
	if (ret)
		compass_INFO("[COMPASS]Failed to set to POWERDOWN mode.\n");

	akm->state.power_on = akm->power_enabled;
	if (akm->state.power_on)
		akm_compass_power_set(akm, false);

	dev_dbg(&akm->i2c->dev, "suspended\n");

	return ret;
}

static int akm_compass_resume(struct device *dev)
{
	struct akm_compass_data *akm = dev_get_drvdata(dev);
	int ret = 0;
	uint8_t mode;

	if (akm->state.power_on) {
		ret = akm_compass_power_set(akm, true);
		if (ret) {
            compass_ERR("[COMPASS]Sensor power resume fail!\n");
			goto exit;
		}

		if (AKM_IS_MAG_DATA_ENABLED() && akm->auto_report) {
			mode = akm_select_frequency(akm->delay[MAG_DATA_FLAG]);
			ret = AKECS_SetMode(akm, mode);
			if (ret < 0) {
		        compass_ERR("[COMPASS]Failed to set to mode(%d)\n", mode);
				goto exit;
			}
			if (akm->use_hrtimer)
				hrtimer_start(&akm->poll_timer,
					ns_to_ktime(akm->delay[MAG_DATA_FLAG]),
					HRTIMER_MODE_REL);
			else
				queue_delayed_work(akm->work_queue, &akm->dwork,
					(unsigned long)nsecs_to_jiffies64(
						akm->delay[MAG_DATA_FLAG]));
		}
	}

	dev_dbg(&akm->i2c->dev, "resumed\n");

exit:
	return ret;
}
static int akm09911_i2c_check_device(
	struct i2c_client *client)
{
	/* AK09911 specific function */
	struct akm_compass_data *akm = i2c_get_clientdata(client);
	int err;

	akm->sense_info[0] = AK09911_REG_WIA1;
	err = akm_i2c_rxdata(client, akm->sense_info, AKM_SENSOR_INFO_SIZE);
	if (err < 0)
		return err;

	/* Set FUSE access mode */
	err = AKECS_SetMode(akm, AK09911_MODE_FUSE_ACCESS);
	if (err < 0)
		return err;

	akm->sense_conf[0] = AK09911_FUSE_ASAX;
	err = akm_i2c_rxdata(client, akm->sense_conf, AKM_SENSOR_CONF_SIZE);
	if (err < 0)
		return err;

	err = AKECS_SetMode(akm, AK09911_MODE_POWERDOWN);
	if (err < 0)
		return err;

	/* Check read data */
	if ((akm->sense_info[0] != AK09911_WIA1_VALUE) ||
			(akm->sense_info[1] != AK09911_WIA2_VALUE)){

		compass_ERR("[COMPASS]%s: The device is not AKM Compass.", __func__);
		return -ENXIO;
	}
	return err;
}

static int akm_compass_power_set(struct akm_compass_data *data, bool on)
{
	int rc = 0;

	if (!on && data->power_enabled) {
		data->power_enabled = false;
		return rc;
	} else if (on && !data->power_enabled) {

		data->power_enabled = true;
		return rc;
	} else {
		compass_INFO("[COMPASS]Power on=%d. enabled=%d\n", on, data->power_enabled);
		return rc;
	}

}

static int akm_compass_power_init(struct akm_compass_data *data, bool on)
{
    int rc = 0;
    data->vdd = 0;
    data->vio = 0;
    return rc;
}

static int akm_compass_parse_dt(struct device *dev,
				struct akm_compass_data *akm)
{


	struct device_node *np = dev->of_node;
	u32 temp_val;
	int rc;

    rc = of_property_read_u32(np, "compass_layout", &temp_val);
	//rc = of_property_read_u32(np, "akm,layout", &temp_val);
	if (rc && (rc != -EINVAL)) {
		compass_FLOW("[COMPASS]Unable to read akm,layout\n");
		return rc;
	} else {
		akm->layout = temp_val;
	}
    akm->gpio_rstn= of_get_named_gpio(np, "gpio_RSTN", 0);
	//akm->auto_report = of_property_read_bool(np, "akm,auto-report");
	//akm->use_hrtimer = of_property_read_bool(np, "akm,use-hrtimer");

	akm->auto_report = AUTO_REPORT;
	akm->use_hrtimer = USE_HRTIMER;
	
	return 0;
}



static int akm_report_data(struct akm_compass_data *akm)
{
	uint8_t dat_buf[AKM_SENSOR_DATA_SIZE];/* for GET_DATA */
	int ret;
	int mag_x, mag_y, mag_z;
	int tmp;
	int count = 10;
	static unsigned long total_delay_count = 0;
       int getdata_delay = 1;
	do {
		/* The typical time for single measurement is 7.2ms */
		ret = AKECS_GetData_Poll(akm, dat_buf, AKM_SENSOR_DATA_SIZE, false);
		if (ret == -EAGAIN) {
			msleep(getdata_delay);
			total_delay_count++;
			if ((total_delay_count & 0xFFF) == 0xFFF) {
                    compass_INFO("[COMPASS]Waited %d us before polling again, count=%d, total_delay_count=%lu.\n", getdata_delay, count, total_delay_count);
                    total_delay_count=0;
			}
		}
	} while ((ret == -EAGAIN) && (--count));

	if (!count) {
		compass_ERR("[COMPASS]Timeout get valid data.\n");
		return -EIO;
	}

	tmp = (int)((int16_t)(dat_buf[2]<<8)+((int16_t)dat_buf[1]));
	tmp = tmp * akm->sense_conf[0] / 128 + tmp;
	mag_x = tmp;

	tmp = (int)((int16_t)(dat_buf[4]<<8)+((int16_t)dat_buf[3]));
	tmp = tmp * akm->sense_conf[1] / 128 + tmp;
	mag_y = tmp;

	tmp = (int)((int16_t)(dat_buf[6]<<8)+((int16_t)dat_buf[5]));
	tmp = tmp * akm->sense_conf[2] / 128 + tmp;
	mag_z = tmp;

	switch (akm->layout) {
	case 0:
	case 1:
		/* Fall into the default direction */
		break;
	case 2:
		tmp = mag_x;
		mag_x = mag_y;
		mag_y = -tmp;
		break;
	case 3:
		mag_x = -mag_x;
		mag_y = -mag_y;
		break;
	case 4:
		tmp = mag_x;
		mag_x = -mag_y;
		mag_y = tmp;
		break;
	case 5:
		mag_x = -mag_x;
		mag_z = -mag_z;
		break;
	case 6:
		tmp = mag_x;
		mag_x = mag_y;
		mag_y = tmp;
		mag_z = -mag_z;
		break;
	case 7:
		mag_y = -mag_y;
		mag_z = -mag_z;
		break;
	case 8:
		tmp = mag_x;
		mag_x = -mag_y;
		mag_y = -tmp;
		mag_z = -mag_z;
		break;
	}

	if(mag_x == 0 && mag_y == 0 && mag_z == 0)
	{
		compass_ERR("[COMPASS]Invalid data: x,y,z all is 0.\n");
	}

	input_report_abs(akm->input, AKM_EVABS_MAG_X, mag_x);
	input_report_abs(akm->input, AKM_EVABS_MAG_Y, mag_y);
	input_report_abs(akm->input, AKM_EVABS_MAG_Z, mag_z);
	/* avoid eaten by input subsystem framework */
	if ((mag_x == akm->last_x) && (mag_y == akm->last_y) &&
			(mag_z == akm->last_z))
		input_report_abs(akm->input, ABS_MISC, akm->rep_cnt++);

	akm->last_x = mag_x;
	akm->last_y = mag_y;
	akm->last_z = mag_z;

	input_sync(akm->input);
	return 0;
}

static void akm_dev_poll(struct work_struct *work)
{
	struct akm_compass_data *akm;
	int ret;
	uint8_t mode;
	akm = container_of((struct delayed_work *)work,
			struct akm_compass_data,  dwork);
	mutex_lock(&akm->self_test_mutex);

	ret = akm_report_data(akm);
	if (ret < 0){
		compass_INFO("[COMPASS]Failed to report data\n");
		/*if error occur, set compass mode to used mode*/
		mode = akm_select_frequency(akm->delay[MAG_DATA_FLAG]);
		/*before change compass mode, set to power down mode first*/
		ret = AKECS_SetMode(akm, AKM_MODE_POWERDOWN);
		if(ret < 0)
		{
		    compass_ERR("[COMPASS]Failed to set to power down mode\n");
		}
		ret = AKECS_SetMode(akm, mode);
		if (ret < 0)
		{
		    compass_ERR("[COMPASS]Failed to set to mode(%x)\n", mode);
		}		
	}

	if (!akm->use_hrtimer)
	queue_delayed_work(akm->work_queue, &akm->dwork,
			(unsigned long)nsecs_to_jiffies64(akm->delay[MAG_DATA_FLAG]));
	mutex_unlock(&akm->self_test_mutex);
}
int
TEST_DATA(const char testno[],
		const char testname[],
		const int testdata,
		const int lolimit,
		const int hilimit,
		int * pf_total)
{
	int pf;                     //Pass;1, Fail;-1

	if ((testno == NULL) && (strncmp(testname, "START", 5) == 0)) {
		// Display header
		compass_ERR("[COMPASS]--------------------------------------------------------------------\n");
		compass_ERR("[COMPASS] Test No. Test Name    Fail    Test Data    [      Low         High]\n");
		compass_ERR("[COMPASS]--------------------------------------------------------------------\n");

		pf = 1;
	} else if ((testno == NULL) && (strncmp(testname, "END", 3) == 0)) {
		// Display result
		compass_ERR("[COMPASS]--------------------------------------------------------------------\n");
		if (*pf_total == 1) {
			compass_ERR("[COMPASS]Factory shipment test was passed.\n\n");
		} else {
			compass_ERR("[COMPASS]Factory shipment test was failed.\n\n");
		}

		pf = 1;
	} else {
		if ((lolimit <= testdata) && (testdata <= hilimit)) {
			//Pass
			pf = 1;
		} else {
			//Fail
			pf = -1;
		}

		//display result
		compass_ERR("[COMPASS] %7s  %-10s      %c    %9d    [%9d    %9d]\n",
				 testno, testname, ((pf == 1) ? ('.') : ('F')), testdata,
				 lolimit, hilimit);
	}

	//Pass/Fail check
	if (*pf_total != 0) {
		if ((*pf_total == 1) && (pf == 1)) {
			*pf_total = 1;            //Pass
		} else {
			*pf_total = -1;           //Fail
		}
	}
	return pf;
}
//static int akm_self_test(struct sensors_classdev *sensors_cdev)
static int akm_self_test_body(struct akm_compass_data *akm)
{
	/*struct akm_compass_data *akm = container_of(sensors_cdev,
			struct akm_compass_data, cdev);*/

	int   pf_total;  //p/f flag for this subtest
	char    i2cData[16];
	int   hdata[3];
	int asax, asay, asaz;
	int count;
	int ret;
	compass_INFO("[COMPASS]%s:%d : akm self test begin \n", __FUNCTION__, __LINE__);
	mutex_lock(&akm->self_test_mutex);

	/* Removed lines. */
	asax = akm->sense_conf[0];
	asay = akm->sense_conf[1];
	asaz = akm->sense_conf[2];

// ***********************************************
	//  Reset Test Result
// ***********************************************
	pf_total = 1;

// ***********************************************
	//  Step1
// ***********************************************

	ret = akm_compass_power_set(akm, true);
	if (ret) {
		compass_ERR("[COMPASS]Sensor power resume fail!\n");
		mutex_unlock(&akm->self_test_mutex);
		return false;
	}

	// Reset device.
	if (AKECS_Reset(akm, 0) < 0) {
		compass_ERR("[COMPASS]Reset failed.\n");
		mutex_unlock(&akm->self_test_mutex);
		return false;
	}

	// TEST
	TEST_DATA(TLIMIT_NO_ASAX_09911, TLIMIT_TN_ASAX_09911, asax, TLIMIT_LO_ASAX_09911, TLIMIT_HI_ASAX_09911, &pf_total);
	TEST_DATA(TLIMIT_NO_ASAY_09911, TLIMIT_TN_ASAY_09911, asay, TLIMIT_LO_ASAY_09911, TLIMIT_HI_ASAY_09911, &pf_total);
	TEST_DATA(TLIMIT_NO_ASAZ_09911, TLIMIT_TN_ASAZ_09911, asaz, TLIMIT_LO_ASAZ_09911, TLIMIT_HI_ASAZ_09911, &pf_total);

    compass_INFO("[COMPASS]%s, line %d, set mode called!\n", __FUNCTION__, __LINE__);
	// Set to PowerDown mode
	if (AKECS_SetMode(akm, AK09911_MODE_POWERDOWN) < 0) {
		compass_ERR("[COMPASS]%s:%d Error.\n", __FUNCTION__, __LINE__);
		mutex_unlock(&akm->self_test_mutex);
		return false;
	}

// ***********************************************
	//  Step2
// ***********************************************
    compass_INFO("[COMPASS]%s, line %d, set mode called!\n", __FUNCTION__, __LINE__);
	// Set to SNG measurement pattern (Set CNTL register)
	if (AKECS_SetMode(akm, AK09911_MODE_SNG_MEASURE) < 0) {
		compass_ERR("[COMPASS]%s:%d Error.\n", __FUNCTION__, __LINE__);
		mutex_unlock(&akm->self_test_mutex);
		return false;
	}

	// Wait for DRDY pin changes to HIGH.
	//usleep(AKM_MEASURE_TIME_US);
	// Get measurement data from AK09911
	// ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + TEMP + ST2
	// = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 + 1 = 9yte
	//if (AKD_GetMagneticData(i2cData) != AKD_SUCCESS) {

	count = 10;

	do {
		/* The typical time for single measurement is 7.2ms */
		ret = AKECS_GetData_Poll(akm, i2cData, AKM_SENSOR_DATA_SIZE, true);
		if (ret == -EAGAIN)
			usleep_range(1000, 10000);
	} while ((ret == -EAGAIN) && (--count));

	if (!count) {
		compass_ERR("[COMPASS]%s:%d :Timeout get valid data.\n",__FUNCTION__,__LINE__);
		mutex_unlock(&akm->self_test_mutex);
		return false;
	}

	//hdata[0] = (int)((((uint)(i2cData[2]))<<8)+(uint)(i2cData[1]));
	//hdata[1] = (int)((((uint)(i2cData[4]))<<8)+(uint)(i2cData[3]));
	//hdata[2] = (int)((((uint)(i2cData[6]))<<8)+(uint)(i2cData[5]));

	hdata[0] = (s16)(i2cData[1] | (i2cData[2] << 8));
	hdata[1] = (s16)(i2cData[3] | (i2cData[4] << 8));
	hdata[2] = (s16)(i2cData[5] | (i2cData[6] << 8));

	// TEST
	i2cData[0] &= 0x7F;
	TEST_DATA(TLIMIT_NO_SNG_ST1_09911,  TLIMIT_TN_SNG_ST1_09911,  (int)i2cData[0], TLIMIT_LO_SNG_ST1_09911,  TLIMIT_HI_SNG_ST1_09911,  &pf_total);

	// TEST
	TEST_DATA(TLIMIT_NO_SNG_HX_09911,   TLIMIT_TN_SNG_HX_09911,   hdata[0],          TLIMIT_LO_SNG_HX_09911,   TLIMIT_HI_SNG_HX_09911,   &pf_total);
	TEST_DATA(TLIMIT_NO_SNG_HY_09911,   TLIMIT_TN_SNG_HY_09911,   hdata[1],          TLIMIT_LO_SNG_HY_09911,   TLIMIT_HI_SNG_HY_09911,   &pf_total);
	TEST_DATA(TLIMIT_NO_SNG_HZ_09911,   TLIMIT_TN_SNG_HZ_09911,   hdata[2],          TLIMIT_LO_SNG_HZ_09911,   TLIMIT_HI_SNG_HZ_09911,   &pf_total);
	TEST_DATA(TLIMIT_NO_SNG_ST2_09911,  TLIMIT_TN_SNG_ST2_09911,  (int)i2cData[8], TLIMIT_LO_SNG_ST2_09911,  TLIMIT_HI_SNG_ST2_09911,  &pf_total);

    compass_INFO("[COMPASS]%s, line %d, set mode called!\n", __FUNCTION__, __LINE__);
	// Set to Self-test mode (Set CNTL register)
	if (AKECS_SetMode(akm, AK09911_MODE_SELF_TEST) < 0) {
		compass_ERR("[COMPASS]%s:%d Error.\n", __FUNCTION__, __LINE__);
		mutex_unlock(&akm->self_test_mutex);
		return false;
	}

	// Wait for DRDY pin changes to HIGH.
	//usleep(AKM_MEASURE_TIME_US);
	// Get measurement data from AK09911
	// ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + TEMP + ST2
	// = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 + 1 = 9byte
	//if (AKD_GetMagneticData(i2cData) != AKD_SUCCESS) {

	count = 10;

	do {
		/* The typical time for single measurement is 7.2ms */
		ret = AKECS_GetData_Poll(akm, i2cData, AKM_SENSOR_DATA_SIZE, true);
		if (ret == -EAGAIN)
			usleep_range(1000, 10000);
	} while ((ret == -EAGAIN) && (--count));

	if (!count) {
		compass_ERR("[COMPASS]%s:%d :Timeout get valid data.\n",__FUNCTION__,__LINE__);
		mutex_unlock(&akm->self_test_mutex);
		return false;
	}

	// TEST
	i2cData[0] &= 0x7F;
	TEST_DATA(TLIMIT_NO_SLF_ST1_09911, TLIMIT_TN_SLF_ST1_09911, (int)i2cData[0], TLIMIT_LO_SLF_ST1_09911, TLIMIT_HI_SLF_ST1_09911, &pf_total);

	//hdata[0] = (int)((((uint)(i2cData[2]))<<8)+(uint)(i2cData[1]));
	//hdata[1] = (int)((((uint)(i2cData[4]))<<8)+(uint)(i2cData[3]));
	//hdata[2] = (int)((((uint)(i2cData[6]))<<8)+(uint)(i2cData[5]));

	hdata[0] = (s16)(i2cData[1] | (i2cData[2] << 8));
	hdata[1] = (s16)(i2cData[3] | (i2cData[4] << 8));
	hdata[2] = (s16)(i2cData[5] | (i2cData[6] << 8));

	// TEST
	TEST_DATA(
			  TLIMIT_NO_SLF_RVHX_09911,
			  TLIMIT_TN_SLF_RVHX_09911,
			  (hdata[0])*(asax/128 + 1),
			  TLIMIT_LO_SLF_RVHX_09911,
			  TLIMIT_HI_SLF_RVHX_09911,
			  &pf_total
			  );

	TEST_DATA(
			  TLIMIT_NO_SLF_RVHY_09911,
			  TLIMIT_TN_SLF_RVHY_09911,
			  (hdata[1])*(asay/128 + 1),
			  TLIMIT_LO_SLF_RVHY_09911,
			  TLIMIT_HI_SLF_RVHY_09911,
			  &pf_total
			  );

	TEST_DATA(
			  TLIMIT_NO_SLF_RVHZ_09911,
			  TLIMIT_TN_SLF_RVHZ_09911,
			  (hdata[2])*(asaz/128 + 1),
			  TLIMIT_LO_SLF_RVHZ_09911,
			  TLIMIT_HI_SLF_RVHZ_09911,
			  &pf_total
			  );

	TEST_DATA(
			TLIMIT_NO_SLF_ST2_09911,
			TLIMIT_TN_SLF_ST2_09911,
			(int)i2cData[8],
			TLIMIT_LO_SLF_ST2_09911,
			TLIMIT_HI_SLF_ST2_09911,
			&pf_total
		 );
	compass_INFO("[COMPASS]%s:%d : pf_total is : %d\n", __FUNCTION__,__LINE__, pf_total);
	if(pf_total <= 0)
	{
		compass_ERR("[COMPASS]%s:%d :self test compass data error, Whether there is a strong magnetic field near?\n",
			__FUNCTION__,__LINE__);
	}

	if (AKM_IS_MAG_DATA_ENABLED() && akm->auto_report) {
		uint8_t mode;
		mode = akm_select_frequency(akm->delay[MAG_DATA_FLAG]);
             compass_INFO("[COMPASS]%s, line %d, set mode called!\n", __FUNCTION__, __LINE__);
		ret = AKECS_SetMode(akm, mode);
		if (ret < 0) {
			compass_ERR("[COMPASS]Failed to restore to mode(%d)\n", mode);
		}
	}else{
		akm_compass_power_set(akm, false);
		compass_ERR("[COMPASS]after compass self test, restore power down mode\n");
	}
	mutex_unlock(&akm->self_test_mutex);
	return (pf_total > 0) ? true : false;
}
static enum hrtimer_restart akm_timer_func(struct hrtimer *timer)
{
	struct akm_compass_data *akm;

	akm = container_of(timer, struct akm_compass_data, poll_timer);

	queue_work(akm->work_queue, &akm->dwork.work);
	hrtimer_forward_now(&akm->poll_timer,
			ns_to_ktime(akm->delay[MAG_DATA_FLAG]));

	return HRTIMER_RESTART;
}
static int akm_compass_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct device_node *node = client->dev.of_node;
	int err = 0;
	int akm9911=0;
	int i;
	compass_INFO("[COMPASS]start probing.");
	err = of_property_read_u32(node, "akm9911", &akm9911);
	if (err) {
		compass_ERR("[COMPASS]akm09911 read failed:%d\n", err);
		return  -ENXIO;
	}

	if(!akm9911)
	{
		compass_INFO("[COMPASS]%s: compass akm09911 device not exits\n", __func__);
		return  -ENXIO;	
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		compass_ERR("[COMPASS]%s: check_functionality failed.", __func__);
		err = -ENODEV;
		goto exit0;
	}

	/* Allocate memory for driver data */
	s_akm = kzalloc(sizeof(struct akm_compass_data), GFP_KERNEL);
	if (!s_akm) {
		compass_ERR("[COMPASS]%s: memory allocation failed.", __func__);
		err = -ENOMEM;
		goto exit1;
	}

	/**** initialize variables in akm_compass_data *****/
	init_waitqueue_head(&s_akm->drdy_wq);
	init_waitqueue_head(&s_akm->open_wq);

	mutex_init(&s_akm->sensor_mutex);
	mutex_init(&s_akm->accel_mutex);
	mutex_init(&s_akm->val_mutex);
	mutex_init(&s_akm->op_mutex);
	mutex_init(&s_akm->self_test_mutex);

	atomic_set(&s_akm->active, 0);
	atomic_set(&s_akm->drdy, 0);

	s_akm->is_busy = 0;
	s_akm->enable_flag = 0;

#if AKM_DEBUG_IF
    s_akm->debug_mode = 0;
#endif
	/* Set to 1G in Android coordination, AKSC format */
	s_akm->accel_data[0] = 0;
	s_akm->accel_data[1] = 0;
	s_akm->accel_data[2] = 720;

	for (i = 0; i < AKM_NUM_SENSORS; i++)
		s_akm->delay[i] = -1;

    err = akm_compass_parse_dt(&client->dev, s_akm);
    if (err) {
		compass_ERR("[COMPASS]Unable to parse platfrom data err=%d\n", err);
        goto exit2;
    }

	if (s_akm->gpio_rstn != 0) {
		compass_INFO("[COMPASS]fyh compass driver reset,gpio=%d,s_akm->gpio_rstn=%d\n",gpio_get_value(s_akm->gpio_rstn),s_akm->gpio_rstn);
		err=gpio_request(s_akm->gpio_rstn,NULL);
		if(err<0)
		{
			compass_INFO("[COMPASS]compass,gpio_request error!!!\n");
		}
		gpio_direction_output(s_akm->gpio_rstn, 1);
		msleep(10);
		gpio_direction_output(s_akm->gpio_rstn, 0);
		msleep(100);
		gpio_direction_output(s_akm->gpio_rstn, 1);
		msleep(10);
		/* No error is returned */
		compass_INFO("[COMPASS]compass driver reset2,gpio=%d\n",gpio_get_value(s_akm->gpio_rstn));
	} 
#if 0
	/***** Set platform information *****/
	pdata = client->dev.platform_data;
	if (pdata) {
		/* Platform data is available. copy its value to local. */
		s_akm->layout = pdata->layout;
		s_akm->gpio_rstn = pdata->gpio_RSTN;
	} else {
		/* Platform data is not available.
		   Layout and information should be set by each application. */
		compass_FLOW("[COMPASS]%s: No platform data.", __func__);
		s_akm->layout = 0;
		s_akm->gpio_rstn = 0;
	}

    /* set regulator*/
	error = akm_regulator_configure(pdata, client);
	if (error) {
		compass_ERR("[COMPASS]Failed to intialize hardware\n");
		compass_INFO("[COMPASS]panben error gyr_regulator_configure\n");
	}
      akm_regulator_enable(pdata);
#endif

	/***** I2C initialization *****/
	s_akm->i2c = client;
	/* set client data */
	i2c_set_clientdata(client, s_akm);
	/* check connection */
	err = akm_compass_power_init(s_akm, 1);
	if (err < 0)
		goto exit2;
	err = akm_compass_power_set(s_akm, 1);
	if (err < 0)
		goto exit3;


	err = akm09911_i2c_check_device(client);
	if (err < 0)
		goto exit4;
	err = set_sensor_chip_info(COMPASS, "AKM AKM09911");
	if (err) {
		compass_ERR("[COMPASS]set_sensor_chip_info error\n");
	}
	/***** input *****/
	err = akm_compass_input_init(&s_akm->input);
	if (err) {
		compass_ERR("[COMPASS]%s: input_dev register failed", __func__);
		goto exit4;
	}
	input_set_drvdata(s_akm->input, s_akm);

	//s_akm->auto_report=1;// read flag from dtsi

	/***** IRQ setup *****/
	s_akm->irq = client->irq;
	compass_FLOW("[COMPASS]%s: IRQ is #%d.",__func__, s_akm->irq);
	
	if (s_akm->irq) {
		err = request_threaded_irq(
				s_akm->irq,
				NULL,
				akm_compass_irq,
				IRQF_TRIGGER_RISING|IRQF_ONESHOT,
				dev_name(&client->dev),
				s_akm);
		if (err < 0) {
			compass_ERR("[COMPASS]%s: request irq failed.", __func__);
			goto exit5;
		}
	} else if (s_akm->auto_report) {
		if (s_akm->use_hrtimer) {
			hrtimer_init(&s_akm->poll_timer, CLOCK_MONOTONIC,
					HRTIMER_MODE_REL);
			s_akm->poll_timer.function = akm_timer_func;
			s_akm->work_queue = alloc_workqueue("akm_poll_work",
				WQ_UNBOUND | WQ_MEM_RECLAIM | WQ_HIGHPRI, 1);
			INIT_WORK(&s_akm->dwork.work, akm_dev_poll);
		} else {
			s_akm->work_queue = alloc_workqueue("akm_poll_work",
				WQ_UNBOUND | WQ_MEM_RECLAIM | WQ_HIGHPRI, 1);
			INIT_DELAYED_WORK(&s_akm->dwork, akm_dev_poll);
		}
	}
	
	s_akm->delay[MAG_DATA_FLAG] = 100 * 1000000;
	/***** misc *****/
	err = misc_register(&akm_compass_dev);
	if (err) {
		compass_ERR("[COMPASS]%s: akm_compass_dev register failed", __func__);
		goto exit6;
	}

	/***** sysfs   debug interface*****/
	err = create_sysfs_interfaces(s_akm);
	if (0 > err) {
		compass_ERR("[COMPASS]%s: create sysfs failed.", __func__);
		goto exit7;
	}
	s_akm->cdev = sensors_cdev;
	s_akm->cdev.sensors_enable = akm_class_enable_set;
	s_akm->cdev.sensors_poll_delay = akm_class_poll_delay_set;
	s_akm->cdev.sensors_self_test = akm_class_self_test;
       err = sensors_classdev_register(&client->dev, &s_akm->cdev);
	if (err) 
      {
	    compass_ERR("[COMPASS]unable to register sensors_classdev: %d\n",err);
           goto exit8;
	}


#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	/* detect current device successful, set the flag as present */
	set_hw_dev_flag(DEV_I2C_COMPASS);
#endif
  #if defined (CONFIG_HUAWEI_DSM)
      akm09911_flag=1;
  #endif
	akm_compass_power_set(s_akm, false);

	compass_INFO("[COMPASS]compass:akm09911 successfully probed.");
	return 0;

exit8:
	remove_sysfs_interfaces(s_akm);
exit7:
	misc_deregister(&akm_compass_dev);
exit6:
	if (s_akm->irq)
		free_irq(s_akm->irq, s_akm);
exit5:
	input_unregister_device(s_akm->input);
exit4:
	akm_compass_power_set(s_akm, 0);

exit3:
	akm_compass_power_init(s_akm, 0);
exit2:
	kfree(s_akm);
exit1:
exit0:
	compass_INFO("[COMPASS]compass:akm09911 probe failed\n");
	return err;
}

static int akm_compass_remove(struct i2c_client *client)
{
	struct akm_compass_data *akm = i2c_get_clientdata(client);

	if (akm->auto_report) {
		if (akm->use_hrtimer) {
			hrtimer_cancel(&akm->poll_timer);
			cancel_work_sync(&akm->dwork.work);
		} else {
			cancel_delayed_work_sync(&akm->dwork);
		}
		destroy_workqueue(akm->work_queue);
	}

	if (akm_compass_power_set(akm, 0))
		compass_ERR("[COMPASS]power set failed.");

	if (akm_compass_power_init(akm, 0))
		compass_ERR("[COMPASS]power deinit failed.");
	remove_sysfs_interfaces(akm);
	if (misc_deregister(&akm_compass_dev) < 0)
		compass_ERR("[COMPASS]misc deregister failed.");
	if (akm->irq)
		free_irq(akm->irq, akm);
	input_unregister_device(akm->input);
	kfree(akm);
	compass_INFO("[COMPASS]successfully removed.");
	return 0;
}

static const struct i2c_device_id akm_compass_id[] = {
	{"akm09911", 0 },
	{ }
};

static const struct dev_pm_ops akm_compass_pm_ops = {
	.suspend	= akm_compass_suspend,
	.resume		= akm_compass_resume,
};

static const struct of_device_id akm09911_of_match[] = {
	{.compatible = "huawei,akm09911",},
	{},
};
MODULE_DEVICE_TABLE(of, akm09911_of_match);

static struct i2c_driver akm_compass_driver = {
	.probe		= akm_compass_probe,
	.remove		= akm_compass_remove,
	.id_table	= akm_compass_id,
	.driver = {
		.name	= "akm09911",
		.owner  = THIS_MODULE,
		.of_match_table = akm09911_of_match,
		.pm		= &akm_compass_pm_ops,
	},
};

static int __init akm_compass_init(void)
{
	compass_INFO("[COMPASS]AKM compass driver: initialize.");
	return i2c_add_driver(&akm_compass_driver);
}

static void __exit akm_compass_exit(void)
{
	compass_INFO("[COMPASS]AKM compass driver: release.");
	i2c_del_driver(&akm_compass_driver);
}

module_init(akm_compass_init);
module_exit(akm_compass_exit);

MODULE_AUTHOR("ben pan<panben@huawei.com>");
MODULE_DESCRIPTION("AKM compass driver");
MODULE_LICENSE("GPL");

