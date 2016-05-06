#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/i2c.h>
#include <linux/semaphore.h>
#include <linux/device.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/spinlock_types.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <../../../drivers/staging/android/timed_output.h>
#include <linux/hrtimer.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/clk.h>
#include <linux/wakelock.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include "drv2605.h"
#include <linux/mtd/hisi_nve_interface.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

#define GPIO_LEVEL_LOW 0
#define GPIO_LEVEL_HIGH 1
/*
 * DRV2605 built-in effect bank/library
 */
#define EFFECT_LIBRARY LIBRARY_F


/*vibrator calibrate */
#define VIB_CALIDATA_NV_NUM    337
#define VIB_CALIDATA_NV_SIZE    3
#define NV_READ_TAG	   1
#define NV_WRITE_TAG	   0

static char vib_calib[3] = {0};
static int vib_calib_result = 0;
static int vib_init_calibdata = 0;
int hisi_nve_direct_access(struct hisi_nve_info_user *user_info);


/*
 * Rated Voltage:
 * Calculated using the formula r = v * 255 / 5.6
 * where r is what will be written to the register
 * and v is the rated voltage of the actuator

 * Overdrive Clamp Voltage:
 * Calculated using the formula o = oc * 255 / 5.6
 * where o is what will be written to the register
 * and oc is the overdrive clamp voltage of the actuator
 */

#if (EFFECT_LIBRARY == LIBRARY_A)
#define ERM_RATED_VOLTAGE               0x3E
#define ERM_OVERDRIVE_CLAMP_VOLTAGE     0x90

#elif (EFFECT_LIBRARY == LIBRARY_B)
#define ERM_RATED_VOLTAGE               0x90
#define ERM_OVERDRIVE_CLAMP_VOLTAGE     0x90

#elif (EFFECT_LIBRARY == LIBRARY_C)
#define ERM_RATED_VOLTAGE               0x90
#define ERM_OVERDRIVE_CLAMP_VOLTAGE     0x90

#elif (EFFECT_LIBRARY == LIBRARY_D)
#define ERM_RATED_VOLTAGE               0x90
#define ERM_OVERDRIVE_CLAMP_VOLTAGE     0x90

#elif (EFFECT_LIBRARY == LIBRARY_E)
#define ERM_RATED_VOLTAGE               0x90
#define ERM_OVERDRIVE_CLAMP_VOLTAGE     0x90

#else
#define ERM_RATED_VOLTAGE               0x90
#define ERM_OVERDRIVE_CLAMP_VOLTAGE     0x90
#endif

#define LRA_RATED_VOLTAGE               0x34
#define LRA_OVERDRIVE_CLAMP_VOLTAGE     0x76

#define SKIP_LRA_AUTOCAL        1
#define GO_BIT_POLL_INTERVAL    15

#if EFFECT_LIBRARY == LIBRARY_A
#define REAL_TIME_PLAYBACK_STRENGTH 0x38 // ~44% of overdrive voltage (open loop)
#elif EFFECT_LIBRARY == LIBRARY_F
#define REAL_TIME_PLAYBACK_STRENGTH 0x66 // 100% of rated voltage (closed loop)
#else
#define REAL_TIME_PLAYBACK_STRENGTH 0x7F // 100% of overdrive voltage (open loop)
#endif

#define MAX_TIMEOUT 10000 /* 10s */
#define DEFAULT_NAME	("vibrator")

#define YES 1
#define NO  0

#define VB_NAME_LENGTH	(20)

static struct i2c_client* client_temp = NULL;
static struct wake_lock vib_wakelock;

struct drv2605_data {
	int gpio_enable;
	int gpio_pwm;
	int max_timeout_ms;
	volatile int should_stop;
	struct i2c_client *client;
	struct timed_output_dev dev;
	struct hrtimer timer;
	struct mutex lock;
	struct work_struct work;
	struct work_struct work_play_eff;
	unsigned char sequence[8];
	struct class* class;
	struct device* device;
	dev_t version;
	struct cdev cdev;
};

struct drv2605_pdata {
	int gpio_enable;
	int gpio_pwm;
	int max_timeout_ms;
	char lra_rated_voltage;
	char lra_overdriver_voltage;
	char lra_rtp_strength;
	char *name;
};

static struct drv2605_pdata *pdata = NULL;

static char g_effect_bank = EFFECT_LIBRARY;
static int device_id = -1;
static char read_val;
static int vibrator_is_playing = NO;
extern volatile int vibrator_shake;
static char reg_value = 0;
static char reg_add = 0;
static char rtp_strength = 0x7F;
static struct drv2605_data *data = NULL;
static ssize_t haptics_write(struct file* filp, const char* buff, size_t len, loff_t* off);

static const unsigned char ERM_autocal_sequence[] = {
    MODE_REG,                       AUTO_CALIBRATION,
    REAL_TIME_PLAYBACK_REG,         REAL_TIME_PLAYBACK_STRENGTH,
    LIBRARY_SELECTION_REG,          EFFECT_LIBRARY,
    WAVEFORM_SEQUENCER_REG,         WAVEFORM_SEQUENCER_DEFAULT,
    WAVEFORM_SEQUENCER_REG2,        WAVEFORM_SEQUENCER_DEFAULT,
    WAVEFORM_SEQUENCER_REG3,        WAVEFORM_SEQUENCER_DEFAULT,
    WAVEFORM_SEQUENCER_REG4,        WAVEFORM_SEQUENCER_DEFAULT,
    WAVEFORM_SEQUENCER_REG5,        WAVEFORM_SEQUENCER_DEFAULT,
    WAVEFORM_SEQUENCER_REG6,        WAVEFORM_SEQUENCER_DEFAULT,
    WAVEFORM_SEQUENCER_REG7,        WAVEFORM_SEQUENCER_DEFAULT,
    WAVEFORM_SEQUENCER_REG8,        WAVEFORM_SEQUENCER_DEFAULT,
    OVERDRIVE_TIME_OFFSET_REG,      0x00,
    SUSTAIN_TIME_OFFSET_POS_REG,    0x00,
    SUSTAIN_TIME_OFFSET_NEG_REG,    0x00,
    BRAKE_TIME_OFFSET_REG,          0x00,
    AUDIO_HAPTICS_CONTROL_REG,      AUDIO_HAPTICS_RECT_20MS | AUDIO_HAPTICS_FILTER_125HZ,
    AUDIO_HAPTICS_MIN_INPUT_REG,    AUDIO_HAPTICS_MIN_INPUT_VOLTAGE,
    AUDIO_HAPTICS_MAX_INPUT_REG,    AUDIO_HAPTICS_MAX_INPUT_VOLTAGE,
    AUDIO_HAPTICS_MIN_OUTPUT_REG,   AUDIO_HAPTICS_MIN_OUTPUT_VOLTAGE,
    AUDIO_HAPTICS_MAX_OUTPUT_REG,   AUDIO_HAPTICS_MAX_OUTPUT_VOLTAGE,
    RATED_VOLTAGE_REG,              ERM_RATED_VOLTAGE,
    OVERDRIVE_CLAMP_VOLTAGE_REG,    ERM_OVERDRIVE_CLAMP_VOLTAGE,
    AUTO_CALI_RESULT_REG,           DEFAULT_ERM_AUTOCAL_COMPENSATION,
    AUTO_CALI_BACK_EMF_RESULT_REG,  DEFAULT_ERM_AUTOCAL_BACKEMF,
    FEEDBACK_CONTROL_REG,           FB_BRAKE_FACTOR_3X | LOOP_RESPONSE_MEDIUM | FEEDBACK_CONTROL_BEMF_ERM_GAIN2,
    Control1_REG,                   STARTUP_BOOST_ENABLED | DEFAULT_DRIVE_TIME,
    Control2_REG,                   BIDIRECT_INPUT | AUTO_RES_GAIN_MEDIUM | BLANKING_TIME_SHORT | IDISS_TIME_SHORT,
    Control3_REG,                   ERM_OpenLoop_Enabled | NG_Thresh_2,
    AUTOCAL_MEM_INTERFACE_REG,      AUTOCAL_TIME_500MS,
    GO_REG,                         GO,
};

static const unsigned char LRA_autocal_sequence[] = {
    MODE_REG,                       AUTO_CALIBRATION,
	FEEDBACK_CONTROL_REG,         	FEEDBACK_CONTROL_MODE_LRA | FB_BRAKE_FACTOR_3X | LOOP_RESPONSE_MEDIUM,
    RATED_VOLTAGE_REG,              LRA_RATED_VOLTAGE,
    OVERDRIVE_CLAMP_VOLTAGE_REG,    LRA_OVERDRIVE_CLAMP_VOLTAGE,

    Control3_REG,                   NG_Thresh_1,
    GO_REG,                         GO,
};

#if SKIP_LRA_AUTOCAL == 1
static const unsigned char LRA_init_sequence[] = {
    MODE_REG,                       MODE_INTERNAL_TRIGGER,
    REAL_TIME_PLAYBACK_REG,         REAL_TIME_PLAYBACK_STRENGTH,
    LIBRARY_SELECTION_REG,          LIBRARY_F,
    GO_REG,                         STOP,
    //OVERDRIVE_TIME_OFFSET_REG,      0x00,
    //SUSTAIN_TIME_OFFSET_POS_REG,    0x00,
    //SUSTAIN_TIME_OFFSET_NEG_REG,    0x00,
    //BRAKE_TIME_OFFSET_REG,          0x00,
    /*RATED_VOLTAGE_REG,              LRA_RATED_VOLTAGE,*/
    /*OVERDRIVE_CLAMP_VOLTAGE_REG,    LRA_OVERDRIVE_CLAMP_VOLTAGE,*/
    //FEEDBACK_CONTROL_REG,           0xB6,	//FEEDBACK_CONTROL_MODE_LRA | FB_BRAKE_FACTOR_4X | LOOP_RESPONSE_MEDIUM | FEEDBACK_CONTROL_BEMF_LRA_GAIN3,
    //Control1_REG,                   STARTUP_BOOST_ENABLED | DEFAULT_DRIVE_TIME,
    //Control2_REG,                   BIDIRECT_INPUT | AUTO_RES_GAIN_MEDIUM | BLANKING_TIME_SHORT | IDISS_TIME_SHORT,
    Control1_REG,                   0x90,
    Control2_REG,                 0xC2,
    Control3_REG,                   0xA0,
    AUTOCAL_MEM_INTERFACE_REG,      0x30,
};
#endif

/******************
* touch haptic lib
*******************/
#define HAPTICS_NUM 8

struct {
    int haptics_type;
    char haptics_value[HAPTICS_NUM];
} haptics_table[] = {
    { 1, {0x01,0,0,0,0,0,0,0}},
    { 2, {0x18,0x06,0x18,0x06,0x18,0,0,0}},
};

static void drv2605_write_reg_val(struct i2c_client *client, const unsigned char *data,
		unsigned int size)
{
	int i = 0;

	if (size % 2 != 0) {
		return;
	}

	while (i < size) {
		i2c_smbus_write_byte_data(client, data[i], data[i + 1]);
		i += 2;
	}
}

static void drv2605_set_go_bit(struct i2c_client *client, char val)
{
	char go[] = {
		GO_REG, val
	};

	drv2605_write_reg_val(client, go, sizeof(go));
}

static unsigned char drv2605_read_reg(struct i2c_client *client, unsigned char reg)
{
	return i2c_smbus_read_byte_data(client, reg);
}

static void drv2605_poll_go_bit(struct i2c_client *client)
{
	while (drv2605_read_reg(client, GO_REG) == GO) {
		schedule_timeout_interruptible(msecs_to_jiffies(GO_BIT_POLL_INTERVAL));
	}
}

static void drv2605_select_library(struct i2c_client *client, char lib)
{
	char library[] = {
		LIBRARY_SELECTION_REG, lib
	};
	drv2605_write_reg_val(client, library, sizeof(library));
}

static void drv2605_set_rtp_val(struct i2c_client *client, char value)
{
	char rtp_val[] = {
		REAL_TIME_PLAYBACK_REG, value
	};
	drv2605_write_reg_val(client, rtp_val, sizeof(rtp_val));

	dev_info(&client->dev, "Strength: %02X value: \n", value);
}

static void drv2605_set_waveform_sequence(struct i2c_client *client, unsigned char *seq,
		unsigned int size)
{
	unsigned char data[WAVEFORM_SEQUENCER_MAX + 1];

	if (size > WAVEFORM_SEQUENCER_MAX) {
		return;
	}

	memset(data, 0, sizeof(data));
	memcpy(&data[1], seq, size);
	data[0] = WAVEFORM_SEQUENCER_REG;

	i2c_master_send(client, data, sizeof(data));
}

static void drv2605_change_mode(struct i2c_client *client, char mode)
{
	unsigned char tmp[] = {
		MODE_REG, mode
	};

	drv2605_write_reg_val(client, tmp, sizeof(tmp));
}

/*******************************************************************************************
Function:	read_vibrator_calib_value_from_nv
Description:   读取NV项中的vibrator 校准数据
Data Accessed:  无
Data Updated:   无
Input:         无
Output:         无
Return:         成功或者失败信息: 0->成功, -1->失败
*******************************************************************************************/
static int read_vibrator_calib_value_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;

	memset(&user_info, 0, sizeof(user_info));

	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = VIB_CALIDATA_NV_NUM;
	user_info.valid_size = VIB_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "VIBCAL", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		dev_err(&client_temp->dev, "nve_direct_access read error(%d)\n", ret);
		return -1;
	}

	vib_calib[0] = (int8_t)user_info.nv_data[0];
	vib_calib[1] = (int8_t)user_info.nv_data[1];
	vib_calib[2] = (int8_t)user_info.nv_data[2];
	dev_info(&client_temp->dev, "read vib_calib (0x%x  0x%x  0x%x )\n", vib_calib[0],vib_calib[1],vib_calib[2]);

	return 0;
}

/*******************************************************************************************
Function:	write_vibrator_calib_value_to_nv
Description:  将temp数据写入NV 项中
Data Accessed:  无
Data Updated:   无
Input:        vibrator 校准值
Output:         无
Return:         成功或者失败信息: 0->成功, -1->失败
*******************************************************************************************/
static int write_vibrator_calib_value_to_nv(char* temp)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;

	if(temp==NULL)
	{
		dev_err(&client_temp->dev, "write_vibrator_calib_value_to_nv fail, invalid para!\n", ret);
		return -1;
	}
	memset(&user_info, 0, sizeof(user_info));
	user_info.nv_operation = NV_WRITE_TAG;
	user_info.nv_number = VIB_CALIDATA_NV_NUM;
	user_info.valid_size = VIB_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "VIBCAL", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
       dev_info(&client_temp->dev, "nve_direct_access write temp (0x%x  0x%x  0x%x )\n",temp[0],temp[1],temp[2]);
	user_info.nv_data[0] = temp[0];
	user_info.nv_data[1] = temp[1];
	user_info.nv_data[2] = temp[2];
	if ((ret = hisi_nve_direct_access(&user_info))!=0)
	{
		dev_err(&client_temp->dev, "nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	dev_info(&client_temp->dev, "nve_direct_access write nv_data (0x%x  0x%x  0x%x )\n",user_info.nv_data[0],user_info.nv_data[1],user_info.nv_data[2]);

	return ret;
}

/*******************************************************************************************
Function:	save_vibrator_calib_value_to_reg
Description:  将校准值写入芯片寄存器中
Data Accessed:  无
Data Updated:   无
Input:        无
Output:         无
Return:         成功或者失败信息: 0->成功, -1->失败
*******************************************************************************************/
static int save_vibrator_calib_value_to_reg(void)
{
	int ret = 0;
	char acalComp[2]={0}, acalBEMF[2]={0}, BEMFGain[2]={0};

	acalComp[1] = drv2605_read_reg(client_temp, AUTO_CALI_RESULT_REG);
	acalBEMF[1] = drv2605_read_reg(client_temp, AUTO_CALI_BACK_EMF_RESULT_REG);
	BEMFGain[1]= drv2605_read_reg(client_temp, FEEDBACK_CONTROL_REG);
	dev_info(&client_temp->dev, "acalComp:0x%x, acalBEMF:0x%x, BEMFGain:0x%x.\n",
				acalComp[1], acalBEMF[1], BEMFGain[1]);
	BEMFGain[1] = 0x03 & BEMFGain[1];
	dev_info(&client_temp->dev, "BEMFGain:0x%x.\n", BEMFGain[1]);

	if((acalComp[1] == 0x0D) && (acalBEMF[1] == 0x6D) && (BEMFGain[1] == 0x02)){
		ret=read_vibrator_calib_value_from_nv();
		if(ret){
			dev_err(&client_temp->dev, "drv2605 read vibrator calib value from nv:fail.\n");
			return -1;
		}else{
			acalComp[0]=AUTO_CALI_RESULT_REG;
			acalComp[1]=vib_calib[0];
			dev_err(&client_temp->dev, "acalComp: 0x%x, 0x%x .\n",acalComp[0],acalComp[1]);

			acalBEMF[0]=AUTO_CALI_BACK_EMF_RESULT_REG;
			acalBEMF[1]=vib_calib[1];
			dev_err(&client_temp->dev, "acalBEMF: 0x%x, 0x%x .\n",acalBEMF[0],acalBEMF[1]);

			BEMFGain[0] = FEEDBACK_CONTROL_REG;
			BEMFGain[1]=drv2605_read_reg(client_temp, FEEDBACK_CONTROL_REG);
			dev_err(&client_temp->dev, "BEMFGain[1]: 0x%x.\n",BEMFGain[1]);
			BEMFGain[1]=(BEMFGain[1] & 0xFC)|(vib_calib[2] & 0x03);
			dev_err(&client_temp->dev, "BEMFGain[1]: 0x%x.\n",BEMFGain[1]);

			drv2605_write_reg_val(client_temp, acalComp, sizeof(acalComp));
			drv2605_write_reg_val(client_temp, acalBEMF, sizeof(acalBEMF));
			drv2605_write_reg_val(client_temp, BEMFGain, sizeof(BEMFGain));
		}
	}
	return 0;
}

static int vibrator_get_time(struct timed_output_dev *dev)
{
	struct drv2605_data *data;

	data = container_of(dev, struct drv2605_data, dev);

	if (hrtimer_active(&(data->timer))) {
		ktime_t r = hrtimer_get_remaining(&data->timer);
		return ktime_to_ms(r);
	}

	return 0;
}

static void vibrator_off(struct drv2605_data *data)
{
	if (vibrator_is_playing) {
		drv2605_set_rtp_val(data->client, 0);
		msleep(25);
		vibrator_is_playing = NO;
		drv2605_change_mode(data->client, MODE_STANDBY);
		vibrator_shake = 0;
	}

	dev_info(&(data->client->dev), "drv2605 off!");
}

static void vibrator_enable(struct timed_output_dev *dev, int value)
{
	int ret = 0,wake_time = 0;
	struct drv2605_data *data;

	data = container_of(dev, struct drv2605_data, dev);
	dev_info(&(data->client->dev), "drv2605 enable value: %d.\n", value);

	mutex_lock(&data->lock);
	hrtimer_cancel(&data->timer);
	cancel_work_sync(&data->work);

	if (value) {
		drv2605_change_mode(data->client, MODE_DEVICE_READY);
		udelay(1000);
		if(vib_init_calibdata == 0){
			ret = save_vibrator_calib_value_to_reg();
			vib_init_calibdata = 1;
			if(ret){
				dev_err(&(data->client->dev), "save vibrator calib value fail:%d.\n", ret);
				vib_init_calibdata = 0;
			}
		}
		/* Only change the mode if not already in RTP mode; RTP input already set at init */
		if ((drv2605_read_reg(data->client, MODE_REG) & DRV260X_MODE_MASK)
			!= MODE_REAL_TIME_PLAYBACK) {
			vibrator_shake = 1;
			drv2605_set_rtp_val(data->client, rtp_strength);
			drv2605_change_mode(data->client, MODE_REAL_TIME_PLAYBACK);
			vibrator_is_playing = YES;
		}

		if (value > 0) {
			if (value > data->max_timeout_ms) {
				value = data->max_timeout_ms;
			}
			wake_time = value + 50;
			wake_lock_timeout(&vib_wakelock, msecs_to_jiffies(wake_time));
			hrtimer_start(&data->timer, ns_to_ktime((u64)value * NSEC_PER_MSEC),
				HRTIMER_MODE_REL);
		}
	} else {
		vibrator_off(data);
	}

	mutex_unlock(&data->lock);
}

static enum hrtimer_restart vibrator_timer_func(struct hrtimer *timer)
{
	struct drv2605_data *data;

	data = container_of(timer, struct drv2605_data, timer);
	schedule_work(&data->work);
	return HRTIMER_NORESTART;
}

static void vibrator_work(struct work_struct *work)
{
	struct drv2605_data *data;

	data = container_of(work, struct drv2605_data, work);
	vibrator_off(data);
}

static void play_effect(struct work_struct *work)
{
	struct drv2605_data *data;

	data = container_of(work, struct drv2605_data, work_play_eff);
	vibrator_shake = 1;
	drv2605_change_mode(data->client, MODE_DEVICE_READY);
	msleep(1);
	vibrator_is_playing = YES;
	drv2605_set_waveform_sequence(data->client, data->sequence, sizeof(data->sequence));
	drv2605_set_go_bit(data->client, GO);

	while((drv2605_read_reg(data->client, GO_REG) == GO) && (!data->should_stop)) {
		schedule_timeout_interruptible(msecs_to_jiffies(GO_BIT_POLL_INTERVAL));
	}

	if(data->should_stop == YES){
		drv2605_set_go_bit(data, STOP);
	}

	drv2605_change_mode(data->client, MODE_STANDBY);
	vibrator_is_playing = NO;
	vibrator_shake = 0;
}

static int drv2605_parse_dt(struct device *dev, struct drv2605_pdata *pdata)
{
	int rc, temp;
	enum of_gpio_flags flags;

	rc = of_property_read_string(dev->of_node, "ti,label", &pdata->name);
	/* set vibrator as default name */
	if (rc < 0) {
		pdata->name = kmalloc(sizeof(DEFAULT_NAME), GFP_KERNEL);
		strncpy(pdata->name, DEFAULT_NAME, sizeof(DEFAULT_NAME));
	}

	rc = of_property_read_u32(dev->of_node, "ti,max-timeout-ms", &temp);
	/* configure minimum idle timeout */
	if (rc < 0) {
		pdata->max_timeout_ms = MAX_TIMEOUT;
	} else {
		pdata->max_timeout_ms = (int )temp;
	}

	rc = of_property_read_u32(dev->of_node, "lra_rated_voltage", &temp);
	if (rc < 0) {
		pdata->lra_rated_voltage = LRA_RATED_VOLTAGE;
	} else {
		pdata->lra_rated_voltage = (char)temp;
	}

	rc = of_property_read_u32(dev->of_node, "lra_overdriver_voltage", &temp);
	if (rc < 0) {
		pdata->lra_overdriver_voltage = LRA_OVERDRIVE_CLAMP_VOLTAGE;
	} else {
		pdata->lra_overdriver_voltage = (char)temp;
	}

	rc = of_property_read_u32(dev->of_node, "lra_rtp_strength", &temp);
	if (rc < 0) {
		pdata->lra_rtp_strength = REAL_TIME_PLAYBACK_STRENGTH;
	} else {
		pdata->lra_rtp_strength = (char)temp;
	}

	dev_info(dev, "max timedout_ms:%d.\n", pdata->max_timeout_ms);
	pdata->gpio_enable = of_get_named_gpio(dev->of_node, "gpio-enable", 0);

	return 0;
}

static ssize_t vibrator_dbc_test_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned char erm_mode = 0,erm_loop = 0;
	uint64_t value = 0;
	int error = 0;
	char device_ready[2]={0}, erm_select[2] = {0}, erm_openloop[2]={0}, overdriver_val[2] = {0};
	char rtp_out1[2]={0}, rtp_out2[2] = {0}, mode_open[2]={0}, mode_close[2] = {0};


	dev_info(&client_temp->dev, "start vibrator_dbc_test!\n");

	drv2605_change_mode(client_temp, MODE_DEVICE_READY);
	udelay(1000);

	erm_mode = drv2605_read_reg(client_temp, FEEDBACK_CONTROL_REG);
	erm_loop = drv2605_read_reg(client_temp, Control3_REG);
	dev_info(&client_temp->dev, "ERM default erm_mode:%d,erm_loop:%d\n",erm_mode,erm_loop);
	erm_mode = 0x7f&erm_mode;
	erm_loop = 0x20|erm_loop;
	dev_info(&client_temp->dev, "ERM set erm_mode:%d,erm_loop:%d\n",erm_mode,erm_loop);

	device_ready[0] = MODE_REG;
	device_ready[1] = 0x00;

	erm_select[0] = FEEDBACK_CONTROL_REG;
	erm_select[1] = erm_mode;

	erm_openloop[0] = Control3_REG;
	erm_openloop[1] = erm_loop;

	overdriver_val[0] = OVERDRIVE_CLAMP_VOLTAGE_REG;
	overdriver_val[1] = 0xff;

	rtp_out1[0] = REAL_TIME_PLAYBACK_REG;
	rtp_out1[1] = 0x7f;

	rtp_out2[0] = REAL_TIME_PLAYBACK_REG;
	rtp_out2[1] = 0x81;

	mode_open[0] = MODE_REG;
	mode_open[1] = 0x05;

	mode_close[0] = MODE_REG;
	mode_close[1] = 0x00;

	drv2605_write_reg_val(client_temp, erm_select, sizeof(erm_select));
	drv2605_write_reg_val(client_temp, erm_openloop, sizeof(erm_openloop));
	drv2605_write_reg_val(client_temp, overdriver_val, sizeof(overdriver_val));

	if (strict_strtoull(buf, 16, &value)){
		dev_info(&client_temp->dev, "vibrator dbc test read value error\n");
		error = -EINVAL;
		goto out;
	}

	if (value == 1) {
		dev_info(&client_temp->dev, "vibrator dbc test out+\n");
		drv2605_write_reg_val(client_temp, rtp_out1, sizeof(rtp_out1));
		drv2605_write_reg_val(client_temp, mode_open, sizeof(mode_open));
	}else if(value == 0){
		dev_info(&client_temp->dev, "vibrator dbc test close\n");
		drv2605_write_reg_val(client_temp, mode_close, sizeof(mode_close));
		drv2605_change_mode(client_temp, MODE_STANDBY);
	}else if(value == 2){
		dev_info(&client_temp->dev, "vibrator dbc test out-\n");
		drv2605_write_reg_val(client_temp, rtp_out2, sizeof(rtp_out2));
		drv2605_write_reg_val(client_temp, mode_open, sizeof(mode_open));
	}else{
		dev_info(&client_temp->dev, "vibrator dbc test value is invalid:%d\n",value);
	}
	error = count;
out:
	return error;
}

static ssize_t vibrator_calib_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int status=0;
	unsigned char lra_mode = 0;
	int ret = 0;
	char calib_value[3] = {0}, lra_select[2]={0}, vib_autocalib[2]={0};
	dev_info(&client_temp->dev, "start vibrator auto calibrate!\n");

	drv2605_change_mode(client_temp, MODE_DEVICE_READY);
	udelay(1000);

	lra_mode = drv2605_read_reg(client_temp, FEEDBACK_CONTROL_REG);
	lra_mode = 0x80|lra_mode;

	lra_select[0]=FEEDBACK_CONTROL_REG;
	lra_select[1]=lra_mode;
	vib_autocalib[0]=MODE_REG;
	vib_autocalib[1]=0x07;

	drv2605_write_reg_val(client_temp, lra_select, sizeof(lra_select));
	drv2605_write_reg_val(client_temp, vib_autocalib, sizeof(vib_autocalib));
	drv2605_set_go_bit(client_temp, GO);

	/* Wait until the procedure is done */
	drv2605_poll_go_bit(client_temp);

	/* Read calibration result */
	status = drv2605_read_reg(client_temp, STATUS_REG);
	dev_info(&client_temp->dev,"calibration status =0x%x\n", status);
	status = 0x08 & status;
	if(status != 0){
		vib_calib_result = 0;
		dev_info(&client_temp->dev,"vibrator calibration fail!\n");
		return count;
	}else{
		vib_calib_result = 1;
	}

	/* Read calibration value*/
	calib_value[0] = drv2605_read_reg(client_temp, AUTO_CALI_RESULT_REG);
	calib_value[1] = drv2605_read_reg(client_temp, AUTO_CALI_BACK_EMF_RESULT_REG);
	calib_value[2] = drv2605_read_reg(client_temp, FEEDBACK_CONTROL_REG);
	calib_value[2] = 0x03 & calib_value[2];
	dev_info(&client_temp->dev,"calibration value =0x%x, 0x%x, 0x%x\n", calib_value[0],calib_value[1],calib_value[2]);
	/*write calibration value to nv*/
	ret = write_vibrator_calib_value_to_nv(calib_value);
	if(ret){
		vib_calib_result = 0;
		dev_info(&client_temp->dev,"vibrator calibration result write to nv fail!\n");
	}

	drv2605_change_mode(client_temp,MODE_STANDBY);

	return count;
}

static ssize_t vibrator_calib_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int val = vib_calib_result;
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}

static ssize_t vibrator_get_reg_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	uint64_t value = 0;
	char reg_address = 0;
	if (strict_strtoull(buf, 16, &value)){
		dev_info(&client_temp->dev, "vibrator_get_reg_store read value error\n");
		goto out;
	}
	reg_address = (char)value;
	reg_value = drv2605_read_reg(client_temp, reg_address);
	dev_info(&client_temp->dev, "reg_address is 0x%x, reg_value is 0x%x.\n",reg_address,reg_value);

out:
	return count;
}

static ssize_t vibrator_get_reg_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int val = reg_value;
	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}

static ssize_t vibrator_set_reg_address_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	uint64_t value = 0;
	if (strict_strtoull(buf, 16, &value)){
		dev_info(&client_temp->dev, "vibrator_set_reg_address_store read value error\n");
		goto out;
	}
	reg_add = (char)value;
	dev_info(&client_temp->dev, "reg_addr is 0x%x.\n",reg_add);

out:
	return count;
}

static ssize_t vibrator_set_reg_value_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	dev_info(&client_temp->dev, "enter vibrator_set_reg_value_store.\n");
	char val = 0, set_reg[2]={0};
	uint64_t value = 0;

	drv2605_change_mode(client_temp, MODE_DEVICE_READY);
	msleep(1);

	if (strict_strtoull(buf, 16, &value)){
		dev_info(&client_temp->dev, "vibrator_set_reg_value_store read value error\n");
		goto out;
	}

	val = (char)value;
	dev_info(&client_temp->dev, "reg_add is 0x%x, reg_value is 0x%x.\n",reg_add,val);

	set_reg[0] = reg_add;
	set_reg[1] = val;

	drv2605_write_reg_val(client_temp, set_reg, sizeof(set_reg));
	drv2605_change_mode(client_temp, MODE_STANDBY);

out:
	return count;
}

static ssize_t haptic_test_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	char a[2] = {0};
	char haptic_value[100] = {0};
	uint64_t value = 0;
	char type = 0;
	int i = 0, j = 0;
	int  m , n ;
	int time = 0, table_num = 0;
	char rtp_value = 0;

	/*get haptic value */
	for(i = 0, j = 0;i < 100;){
		memcpy(&a[0], &buf[i], 2);
		i = i + 2;
		dev_info(&client_temp->dev, "-----> haptic_test1 is %d %d\n", a[0],a[1]);

		if((a[0] == 57) && (a[1] == 57)){
			haptic_value[j] = 0;
			break;
		}else{
			m = ((a[0] > 57)?(a[0]-97+10):(a[0]-48))*16;
			n =  ((a[1] > 57)?(a[1]-97+10):(a[1]-48));
			haptic_value[j] = m + n;
		}
		dev_info(&client_temp->dev, "-----> haptic_test2 is 0x%x, m = %d, n=%d\n", haptic_value[j],m,n);
		j++;
	}

	/*vibrator work*/
	hrtimer_cancel(&data->timer);
	cancel_work_sync(&data->work);
	vibrator_off(data);
	memcpy(&data->sequence, &haptic_value,8);
	schedule_work(&data->work_play_eff);
	return count;
}

static ssize_t vibrator_set_rtp_value_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	dev_info(&client_temp->dev, "enter vibrator_set_rtp_value_store.\n");
	char val = 0, set_reg[2]={0};
	uint64_t value = 0;

	if (strict_strtoull(buf, 16, &value)){
		dev_info(&client_temp->dev, "vibrator_set_rtp_value_store read value error\n");
		goto out;
	}

	rtp_strength = (char)value;
	dev_info(&client_temp->dev, "rtp_value is 0x%x\n", rtp_strength);

out:
	return count;
}

static DEVICE_ATTR(vibrator_dbc_test, S_IRUSR|S_IWUSR, NULL, vibrator_dbc_test_store);
static DEVICE_ATTR(vibrator_calib, S_IRUSR|S_IWUSR, vibrator_calib_show, vibrator_calib_store);
static DEVICE_ATTR(vibrator_get_reg, S_IRUSR|S_IWUSR, vibrator_get_reg_show, vibrator_get_reg_store);
static DEVICE_ATTR(vibrator_set_reg_address, S_IRUSR|S_IWUSR, NULL, vibrator_set_reg_address_store);
static DEVICE_ATTR(vibrator_set_reg_value, S_IRUSR|S_IWUSR, NULL, vibrator_set_reg_value_store);
static DEVICE_ATTR(haptic_test, S_IRUSR|S_IWUSR, NULL, haptic_test_store);
static DEVICE_ATTR(vibrator_set_rtp_value, S_IRUSR|S_IWUSR, NULL, vibrator_set_rtp_value_store);

static struct attribute *vb_attributes[] = {
	&dev_attr_vibrator_dbc_test.attr,
	&dev_attr_vibrator_calib.attr,
	&dev_attr_vibrator_get_reg.attr,
	&dev_attr_vibrator_set_reg_address.attr,
	&dev_attr_vibrator_set_reg_value.attr,
	&dev_attr_haptic_test.attr,
	&dev_attr_vibrator_set_rtp_value.attr,
	NULL
};

static const struct attribute_group vb_attr_group = {
	.attrs = vb_attributes,
};

static int haptics_open(struct inode * i_node, struct file * filp)
{
	if(data == NULL){
		return -ENODEV;
	}
	dev_info(&client_temp->dev, "haptics_open");
	filp->private_data = data;
	return 0;
}

static ssize_t haptics_write(struct file* filp, const char* buff, size_t len, loff_t* off)
{
	struct drv2605_data *data = (struct drv2605_data *)filp->private_data;
	int i = 0, type_flag = 0, table_num = 0;
	uint64_t type = 0;

	mutex_lock(&data->lock);
	if(strict_strtoull(buff, 10, &type)){
		dev_info(&(data->client->dev), "[haptics_write] read value error\n");
		goto out;
	}

	for(i=0;i<ARRAY_SIZE(haptics_table);i++){
		if(type == haptics_table[i].haptics_type){
			table_num = i;
			type_flag = 1;
			dev_info(&(data->client->dev), "[haptics write] type:%d,table_num:%d.\n", type,table_num);
			break;
		}
	}
	if(!type_flag){
		dev_info(&(data->client->dev), "[haptics write] undefined type:%d.\n", type);
		goto out;
	}else{
		data->should_stop = YES;
		hrtimer_cancel(&data->timer);
		cancel_work_sync(&data->work);
		vibrator_off(data);
		memcpy(&data->sequence, &haptics_table[table_num].haptics_value,HAPTICS_NUM);
		dev_info(&(data->client->dev), "[haptics write] sequence1-4: 0x%x,0x%x,0x%x,0x%x.\n", data->sequence[0],
						data->sequence[1],data->sequence[2],data->sequence[3]);
		dev_info(&(data->client->dev), "[haptics write] sequence5-8: 0x%x,0x%x,0x%x,0x%x.\n", data->sequence[4],
						data->sequence[5],data->sequence[6],data->sequence[7]);
		data->should_stop = NO;
		schedule_work(&data->work_play_eff);
	}
out:
	mutex_unlock(&data->lock);
	return len;
}

static struct file_operations fops =
{
	.open = haptics_open,
	.write = haptics_write,
};

static int haptics_probe(struct drv2605_data *data)
{
	int ret = -ENOMEM;

	data->version = MKDEV(0,0);
	ret = alloc_chrdev_region(&data->version, 0, 1, CDEVIE_NAME);
	if (ret < 0)
	{
		dev_info(&(data->client->dev), "drv2605: error getting major number %d\n", ret);
		return ret;
	}

	data->class = class_create(THIS_MODULE, CDEVIE_NAME);
	if (!data->class)
	{
		dev_info(&(data->client->dev), "drv2605: error creating class\n");
		goto unregister_cdev_region;
	}

	data->device = device_create(data->class, NULL, data->version, NULL, CDEVIE_NAME);
	if (!data->device)
	{
		dev_info(&(data->client->dev), "drv2605: error creating device 2605\n");
		goto destory_class;
	}

	cdev_init(&data->cdev, &fops);
	data->cdev.owner = THIS_MODULE;
	data->cdev.ops = &fops;
	ret = cdev_add(&data->cdev, data->version, 1);
	if (ret)
	{
		dev_info(&(data->client->dev), "drv2605: fail to add cdev\n");
		goto destory_device;
	}

	INIT_WORK(&data->work_play_eff, play_effect);

	return 0;

destory_device:
	device_destroy(data->class, data->version);
destory_class:
	class_destroy(data->class);
unregister_cdev_region:
	unregister_chrdev_region(data->version, 1);

	return ret;
}

static int drv2605_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	char status = 0;
	int rc = 0,ret = 0;
	unsigned char lra_mode = 0, lra_select[2]={0};
	unsigned char lra_rated_voltage[2]={0}, lra_overdriver_voltage[2]={0};

	vib_init_calibdata = 0;
	//struct drv2605_data *data;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "i2c is not supported\n");
		return -EIO;
	}

	client_temp = client;
	if (client->dev.of_node) {
		pdata = devm_kzalloc(&client->dev, sizeof(struct drv2605_pdata), GFP_KERNEL);
		if (!pdata) {
			dev_err(&client->dev, "unable to allocate pdata\n");
			return -ENOMEM;
		}

		/* parse DT */
		rc = drv2605_parse_dt(&client->dev, pdata);
		if (rc) {
			devm_kfree(&client->dev, pdata);
			dev_err(&client->dev, "DT parsing failed\n");
			return -EIO;
		}
	} else {
		return -EINVAL;
	}

	data = devm_kzalloc(&client->dev, sizeof(struct drv2605_data), GFP_KERNEL);
	if (!data) {
		dev_err(&client->dev, "unable to allocate memory\n");
		devm_kfree(&client->dev, pdata);
		return -ENOMEM;
	}

	wake_lock_init(&vib_wakelock, WAKE_LOCK_SUSPEND, "vib_drv2605");
	mutex_init(&data->lock);
	mutex_lock(&data->lock);

	data->gpio_enable = pdata->gpio_enable;
	data->max_timeout_ms = pdata->max_timeout_ms;
	rtp_strength = pdata->lra_rtp_strength;
	dev_info(&client->dev, "rtp_strength:0x%x.\n",rtp_strength);

	i2c_set_clientdata(client, data);

	data->client = client;
	if (gpio_request(data->gpio_enable, "vibrator-en") < 0) {
		dev_err(&client->dev, "drv2605: error requesting enable gpio!\n");
		goto destroy_mutex;
	}

	hrtimer_init(&data->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	data->timer.function = vibrator_timer_func;
	INIT_WORK(&data->work, vibrator_work);
	INIT_WORK(&data->work_play_eff, play_effect);

	data->dev.name = pdata->name;
	data->dev.get_time = vibrator_get_time;
	data->dev.enable = vibrator_enable;

	mutex_unlock(&data->lock);

	rc = timed_output_dev_register(&data->dev);
	if (rc) {
		dev_err(&client->dev, "unable to register with timed_output\n");
		goto unregister_timed_output_dev;
	}

	ret = sysfs_create_group(&data->dev.dev->kobj, &vb_attr_group);
	if (ret) {
		dev_err(&client->dev, "unable create vibrator's sysfs,DBC check IC fail\n");
	}

	/* enable the drv2605 chip */
	gpio_direction_output(data->gpio_enable, GPIO_LEVEL_HIGH);
	udelay(30);

#if	SKIP_LRA_AUTOCAL ==	1
	if (g_effect_bank != LIBRARY_F) {
		drv2605_write_reg_val(data->client, ERM_autocal_sequence, sizeof(ERM_autocal_sequence));
	} else {
		drv2605_write_reg_val(data->client, LRA_init_sequence, sizeof(LRA_init_sequence));
	}
#else
	if (g_effect_bank == LIBRARY_F) {
		drv2605_write_reg_val(data->client, LRA_autocal_sequence,	sizeof(LRA_autocal_sequence));
	} else {
		drv2605_write_reg_val(data->client, ERM_autocal_sequence, sizeof(ERM_autocal_sequence));
	}
#endif

	lra_mode = drv2605_read_reg(data->client, FEEDBACK_CONTROL_REG);
	lra_mode = ((0x03&lra_mode)|0xFC)&0xD3;
       dev_info(&client->dev, "lra_mode:0x%x.\n",lra_mode);
	lra_select[0]=FEEDBACK_CONTROL_REG;
	lra_select[1]=lra_mode;
	drv2605_write_reg_val(data->client, lra_select, sizeof(lra_select));

	lra_rated_voltage[0] = RATED_VOLTAGE_REG;
	lra_rated_voltage[1] = pdata->lra_rated_voltage;
	dev_info(&client->dev, "lra_rated_voltage:0x%x.\n",lra_rated_voltage[1]);
	drv2605_write_reg_val(data->client, lra_rated_voltage, sizeof(lra_rated_voltage));

	lra_overdriver_voltage[0] = OVERDRIVE_CLAMP_VOLTAGE_REG;
	lra_overdriver_voltage[1] = pdata->lra_overdriver_voltage;
	dev_info(&client->dev, "lra_overdriver_voltage:0x%x.\n",lra_overdriver_voltage[1]);
	drv2605_write_reg_val(data->client, lra_overdriver_voltage, sizeof(lra_overdriver_voltage));

	/* Choose default effect library */
	drv2605_select_library(data->client, g_effect_bank);

	drv2605_change_mode(data->client, MODE_STANDBY);
	haptics_probe(data);

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	set_hw_dev_flag(DEV_I2C_VIBRATOR_LRA);
#endif

	dev_info(&client->dev, "drv2605 probe succeeded.\n");

	return 0;

unregister_timed_output_dev:
	timed_output_dev_unregister(&data->dev);
	hrtimer_cancel(&data->timer);
	gpio_free(data->gpio_enable);
destroy_mutex:
	mutex_destroy(&data->lock);
	wake_lock_destroy(&vib_wakelock);
	devm_kfree(&client->dev, data);
	devm_kfree(&client->dev, pdata);

	return rc;
}

static int drv2605_remove(struct i2c_client *client)
{
	struct drv2605_data *data = i2c_get_clientdata(client);

	wake_lock_destroy(&vib_wakelock);
	mutex_destroy(&data->lock);
	sysfs_remove_group(&data->dev.dev->kobj, &vb_attr_group);
	timed_output_dev_unregister(&data->dev);
	hrtimer_cancel(&data->timer);
	cancel_work_sync(&data->work);
	cancel_work_sync(&data->work_play_eff);

	return 0;
}

static const struct i2c_device_id drv2605_id_table[] = {
		{"drv2605", 0},
		{ },
};
MODULE_DEVICE_TABLE(i2c, drv2605_id_table);

static const struct of_device_id drv2605_of_id_table[] = {
		{.compatible = "ti,drv2605"},
		{ },
};

static struct i2c_driver drv2605_i2c_driver = {
		.driver = {
			.name = "drv2605",
			.owner = THIS_MODULE,
			.of_match_table = drv2605_of_id_table,
		},
		.probe = drv2605_probe,
		.remove = drv2605_remove,
		.id_table = drv2605_id_table,
};

module_i2c_driver(drv2605_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huawei Corp.");
MODULE_DESCRIPTION("Driver for "DEVICE_NAME);
