/*******************************************************************************
 * Copyright (C) 2014 HiDeep, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *******************************************************************************/

#include "ist520e.h"    // TODO : rename name..

#define IST_RAWDATA_ARRANGE_SWAP "rawdata_arrange_swap"

#define  IST520E_UC  "crimson.bin"

struct ist510e *g_istxxxx_data;
extern struct ts_data g_ts_data;

//0x00: menu key
//0x01: home key
//0x02: back key
#ifdef IST510E_KEYBUTTON
static int tsp_keycodes[] = {KEY_MENU, KEY_HOMEPAGE, KEY_BACK};
#endif

#define CHECK_ENABLE_GESTURE(A)	((u32)(1<<A))
#define HIDEEP_VCI_LDO_VALUE (3300000)
#define HIDEEP_VDDIO_LDO_VALUE (1850000)
static DEFINE_MUTEX(ts_power_gpio_sem);
static int ts_power_gpio_ref = 0;
static u16 pre_status = 0;
//#define HIDEEP_REPEAT_START

static void apple_weight_timeout_func(struct work_struct *work);
static int hideep_holster_switch(struct ts_holster_info *info);
static int hideep_roi_switch(struct ts_roi_info *info);

static int hideep_regulator_get(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;
	struct platform_device *platform_dev = g_istxxxx_data->huawei_ts_dev;

	if (1 == dat->vci_regulator_type) {
		g_istxxxx_data->tp_vci = regulator_get(&platform_dev->dev, HIDEEP_VDD);
		if (IS_ERR(g_istxxxx_data->tp_vci)) {
			TS_LOG_ERR("regulator tp vci not used\n");
			return  -EINVAL;
		}
	}
	if (1 == dat->vddio_regulator_type) {
		g_istxxxx_data->tp_vddio = regulator_get(&platform_dev->dev, HIDEEP_VBUS);
		if (IS_ERR(g_istxxxx_data->tp_vddio)) {
			TS_LOG_ERR("regulator tp vddio not used\n");
			regulator_put(g_istxxxx_data->tp_vci);
			return -EINVAL;
		}
	}
	return 0;
}

static void hideep_regulator_put(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;
	if (1 == dat->vci_regulator_type) {
		if (!IS_ERR(g_istxxxx_data->tp_vci)) {
			regulator_put(g_istxxxx_data->tp_vci);
		}
	}
	if (1 == dat->vddio_regulator_type) {
		if (!IS_ERR(g_istxxxx_data->tp_vddio)) {
			regulator_put(g_istxxxx_data->tp_vddio);
		}
	}
}

static int hideep_vci_enable(void)
{
	int retval;
	int vol_vlaue;

	if (IS_ERR(g_istxxxx_data->tp_vci)){
		TS_LOG_ERR("tp_vci is err\n");
		return  -EINVAL;
	}
	vol_vlaue = HIDEEP_VCI_LDO_VALUE;
	if (!IS_ERR(g_istxxxx_data->tp_vci)){
		TS_LOG_INFO("set voltage is called\n");
		retval = regulator_set_voltage(g_istxxxx_data->tp_vci, vol_vlaue, vol_vlaue);
		if (retval < 0) {
			TS_LOG_ERR("failed to set voltage regulator tp_vci error: %d\n", retval);
			return -EINVAL;
		}
		retval = regulator_enable(g_istxxxx_data->tp_vci);
		if (retval < 0) {
			TS_LOG_ERR("failed to enable regulator tp_vci\n");
			return -EINVAL;
		}
	}
	return 0;
}

static int hideep_vci_disable(void)
{
	int retval;

	if (IS_ERR(g_istxxxx_data->tp_vci)) {
		TS_LOG_ERR("tp_vci is err\n");
		return  -EINVAL;
	}
	retval = regulator_disable(g_istxxxx_data->tp_vci);
	if (retval < 0) {
		TS_LOG_ERR("failed to disable regulator tp_vci\n");
		return -EINVAL;
	}
	return 0;
}

static int hideep_vddio_enable(void)
{
	int retval;
	int vol_vlaue;

	vol_vlaue = HIDEEP_VDDIO_LDO_VALUE;

	if (IS_ERR(g_istxxxx_data->tp_vddio)) {
		TS_LOG_ERR("tp_vddio is err\n");
		return -EINVAL;
	}

	retval = regulator_set_voltage(g_istxxxx_data->tp_vddio, vol_vlaue, vol_vlaue);
	if (retval < 0) {
		TS_LOG_ERR("failed to set voltage regulator tp_vci error: %d\n", retval);
		return -EINVAL;
	}

	retval = regulator_enable(g_istxxxx_data->tp_vddio);
	if (retval < 0) {
		TS_LOG_ERR("failed to enable regulator tp_vddio\n");
		return -EINVAL;
	}
	return 0;
}

static int hideep_vddio_disable(void)
{
	int retval;

	if (IS_ERR(g_istxxxx_data->tp_vddio)) {
		TS_LOG_ERR("tp_vddio is err\n");
		return -EINVAL;
	}
	retval = regulator_disable(g_istxxxx_data->tp_vddio);
	if (retval < 0) {
		TS_LOG_ERR("failed to disable regulator tp_vddio\n");
		return -EINVAL;
	}
	return 0;
}

/* dts */
static int hideep_pinctrl_get_init(void)
{
	int ret = 0;
	struct platform_device *platform_dev = g_istxxxx_data->huawei_ts_dev;

	g_istxxxx_data->pctrl = devm_pinctrl_get(&platform_dev->dev);
	if (IS_ERR(g_istxxxx_data->pctrl)) {
		TS_LOG_ERR("failed to devm pinctrl get\n");
		ret = -EINVAL;
		return ret;
	}
	g_istxxxx_data->pins_default = pinctrl_lookup_state(g_istxxxx_data->pctrl, "default");
	if (IS_ERR(g_istxxxx_data->pins_default)) {
		TS_LOG_ERR("failed to pinctrl lookup state default\n");
		ret = -EINVAL;
		goto err_pinctrl_put;
	}
	g_istxxxx_data->pins_idle = pinctrl_lookup_state(g_istxxxx_data->pctrl, "idle");
	if (IS_ERR(g_istxxxx_data->pins_idle)) {
		TS_LOG_ERR("failed to pinctrl lookup state idle\n");
		ret = -EINVAL;
		goto err_pinctrl_put;
	}
	return 0;
err_pinctrl_put:
	devm_pinctrl_put(g_istxxxx_data->pctrl);
	return ret;
}

static int hideep_pinctrl_select_normal(void)
{
	int retval = NO_ERR;
	retval = pinctrl_select_state(g_istxxxx_data->pctrl, g_istxxxx_data->pins_default);
	if (retval < 0) {
		TS_LOG_ERR("set iomux normal error, %d\n", retval);
	}
	return retval;
}

static int hideep_pinctrl_select_lowpower(void)
{
	int retval = NO_ERR;
	retval = pinctrl_select_state(g_istxxxx_data->pctrl, g_istxxxx_data->pins_idle);
	if (retval < 0) {
		TS_LOG_ERR("set iomux lowpower error, %d\n", retval);
	}
	return retval;
}

static void hideep_power_on_gpio_set(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	gpio_direction_output(dat->reset_gpio, 1);
	hideep_pinctrl_select_normal();
	gpio_direction_input(dat->irq_gpio);
}

void hideep_power_gpio_enable(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	mutex_lock(&ts_power_gpio_sem);
	if (ts_power_gpio_ref == 0) {
		gpio_direction_output(dat->vddio_gpio_ctrl, 1);
	}
	ts_power_gpio_ref++;
	mutex_unlock(&ts_power_gpio_sem);
}
EXPORT_SYMBOL(hideep_power_gpio_enable);

void hideep_power_gpio_disable(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	mutex_lock(&ts_power_gpio_sem);
	if (ts_power_gpio_ref == 1) {
		gpio_direction_output(dat->vddio_gpio_ctrl, 0);
	}
	if(ts_power_gpio_ref > 0) {
		ts_power_gpio_ref--;
	}
	mutex_unlock(&ts_power_gpio_sem);
}
EXPORT_SYMBOL(hideep_power_gpio_disable);

static void hideep_vci_on(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	TS_LOG_INFO("%s +\n", __func__);
	if (dat->vci_regulator_type) {
		if (!IS_ERR(g_istxxxx_data->tp_vci)) {
			TS_LOG_INFO("%s vci enable regulator is called\n", __func__);
			hideep_vci_enable();
		}
	}

	if (dat->vci_gpio_type){
		TS_LOG_INFO("%s vci switch gpio on\n", __func__);
		gpio_direction_output(dat->vci_gpio_ctrl, 1);
	}
	TS_LOG_INFO("%s -\n", __func__);
}

static void hideep_vddio_on(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	TS_LOG_INFO("%s +\n", __func__);
	if(1 == dat->vddio_regulator_type) {
		if (!IS_ERR(g_istxxxx_data->tp_vddio)) {
			TS_LOG_INFO("%s vddio enable regulator is called\n", __func__);
			hideep_vddio_enable();
		}
	}

	if (dat->vddio_gpio_type){
		TS_LOG_INFO("%s vddio switch gpio on\n", __func__);
		gpio_direction_output(dat->vddio_gpio_ctrl, 1);
	}
	TS_LOG_INFO("%s -\n", __func__);
}

static void hideep_power_on(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	TS_LOG_INFO("%s +\n", __func__);
	hideep_vci_on();
	mdelay(5);
	hideep_vddio_on();
	mdelay(5);
	hideep_power_on_gpio_set();
	TS_LOG_INFO("%s -\n", __func__);
}

static void hideep_power_off_gpio_set(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	TS_LOG_INFO("suspend RST out L\n");
	gpio_direction_output(dat->reset_gpio, 0);
	hideep_pinctrl_select_lowpower();
}

static void hideep_vddio_off(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	TS_LOG_INFO("%s +\n", __func__);
	if (dat->vddio_gpio_type){
		TS_LOG_INFO("%s vddio switch gpio off\n", __func__);
		gpio_direction_output(dat->vddio_gpio_ctrl, 0);
	}

	if(1 == dat->vddio_regulator_type) {
		if (!IS_ERR(g_istxxxx_data->tp_vddio)) {
			TS_LOG_INFO("%s vddio disable regulator is called\n", __func__);
			hideep_vddio_disable();
		}
	}
	TS_LOG_INFO("%s -\n", __func__);
}

static void hideep_vci_off(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	TS_LOG_INFO("%s +\n", __func__);
	if (dat->vci_gpio_type){
		TS_LOG_INFO("%s vci switch gpio off\n", __func__);
		gpio_direction_output(dat->vci_gpio_ctrl, 0);
	}

	if (dat->vci_regulator_type) {
		if (!IS_ERR(g_istxxxx_data->tp_vci)) {
			TS_LOG_INFO("%s vci disable regulator is called\n", __func__);
			hideep_vci_disable();
		}
	}
	TS_LOG_INFO("%s -\n", __func__);
}

static void hideep_power_off(void)
{
	TS_LOG_INFO("%s +\n", __func__);
	hideep_power_off_gpio_set();
	mdelay(5);
	hideep_vddio_off();
	mdelay(5);
	hideep_vci_off();
	TS_LOG_INFO("%s -\n", __func__);
}

static int hideep_gpio_request(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	int retval = NO_ERR;
	TS_LOG_INFO("hideep_gpio_request\n");

	retval = gpio_request(dat->reset_gpio, "ts_reset_gpio");
	if (retval < 0) {
		TS_LOG_ERR("Fail request gpio:%d\n", dat->reset_gpio);
		goto ts_reset_out;
	}
	retval = gpio_request(dat->irq_gpio, "ts_irq_gpio");
	if (retval) {
		TS_LOG_ERR("unable to request gpio:%d\n", dat->irq_gpio);
		goto ts_irq_out;
	}
	if ((1 == dat->vci_gpio_type) && (1 == dat->vddio_gpio_type)) {
		if (dat->vci_gpio_ctrl == dat->vddio_gpio_ctrl) {
			retval = gpio_request(dat->vci_gpio_ctrl, "ts_vci_gpio");
			if (retval) {
				TS_LOG_ERR("SFT:Ok;  ASIC: Real ERR----unable to request vci_gpio_ctrl firset:%d\n", dat->vci_gpio_ctrl);
				goto ts_vci_out;
			}
		} else {
			retval = gpio_request(dat->vci_gpio_ctrl, "ts_vci_gpio");
			if (retval) {
				TS_LOG_ERR("SFT:Ok;  ASIC: Real ERR----unable to request vci_gpio_ctrl2:%d\n", dat->vci_gpio_ctrl);
				goto ts_vci_out;
			}
			retval = gpio_request(dat->vddio_gpio_ctrl, "ts_vddio_gpio");
			if (retval) {
				TS_LOG_ERR("SFT:Ok;  ASIC: Real ERR----unable to request vddio_gpio_ctrl:%d\n", dat->vddio_gpio_ctrl);
				goto ts_vddio_out;
			}
		}
	} else {
		if (1 == dat->vci_gpio_type) {
			retval = gpio_request(dat->vci_gpio_ctrl, "ts_vci_gpio");
			if (retval) {
				TS_LOG_ERR("SFT:Ok;  ASIC: Real ERR----unable to request vci_gpio_ctrl2:%d\n", dat->vci_gpio_ctrl);
				goto ts_vci_out;
			}
		}
		if (1 == dat->vddio_gpio_type) {
			retval = gpio_request(dat->vddio_gpio_ctrl, "ts_vddio_gpio");
			if (retval) {
				TS_LOG_ERR("SFT:Ok;  ASIC: Real ERR----unable to request vddio_gpio_ctrl:%d\n", dat->vddio_gpio_ctrl);
				goto ts_vddio_out;
			}
		}
	}

	TS_LOG_INFO("reset:%d, irq:%d,\n", dat->reset_gpio, dat->irq_gpio);

	goto ts_reset_out;

ts_vddio_out:
	gpio_free(dat->vci_gpio_ctrl);
ts_vci_out:
	gpio_free(dat->irq_gpio);
ts_irq_out:
	gpio_free(dat->reset_gpio);
ts_reset_out:
	return retval;
}

static void hideep_gpio_free(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	TS_LOG_INFO("hideep_gpio_free\n");
	gpio_free(dat->irq_gpio);
	gpio_free(dat->reset_gpio);
	/*0 is power supplied by gpio, 1 is power supplied by ldo*/
	if (1 == dat->vci_gpio_type) {
		if (dat->vci_gpio_ctrl)
			gpio_free(dat->vci_gpio_ctrl);
	}
	if (1 == dat->vddio_gpio_type) {
		if (dat->vddio_gpio_ctrl)
			gpio_free(dat->vddio_gpio_ctrl);
	}
}

#ifdef HIDEEP_REPEAT_START
int huawei_ts_i2c_read(u8 *reg_addr, u16 reg_len, u8 *buf, u16 len)
{
	int count = 0;
	int ret;
	struct i2c_msg xfer[2];

	TS_LOG_DEBUG("ts_i2c_read enter\n");
	/*register addr*/
	xfer[0].addr = g_ts_data.client->addr;
	xfer[0].flags = 0;
	xfer[0].len = reg_len;
	xfer[0].buf = reg_addr;

	/* Read data */
	xfer[1].addr = g_ts_data.client->addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].len = len;
	xfer[1].buf = buf;

	count = 0;
	do {
		ret = i2c_transfer(g_ts_data.client->adapter, &xfer[0], 1);
		if (ret == 1){
			goto reading_data;
		}
		msleep(I2C_WAIT_TIME);
	} while (++count < I2C_RW_TRIES);

reading_data:
	count = 0;
	do {
		ret = i2c_transfer(g_ts_data.client->adapter, &xfer[1], 1);
		if (ret == 1) {
			return NO_ERR;
		}
do_retry:
		msleep(I2C_WAIT_TIME);
	} while (++count < I2C_RW_TRIES);
	TS_LOG_ERR("ts_i2c_read failed\n");
	return -EIO;
}
#endif

int hideep_i2c_read(struct ist510e *ts, u16 addr, u16 len, u8 *buf)
{
	int ret = -1;


	TS_LOG_DEBUG("hideep_i2c_read:addr = 0x%04x,len = %d\n",addr,len);
	mutex_lock(&ts->i2c_mutex);
#ifdef HIDEEP_REPEAT_START
	ret = huawei_ts_i2c_read((u8*)&addr, 2, buf, len);
#else
	ret = ts->huawei_ts_data->bops->bus_read((u8*)&addr, 2, buf, len);
#endif
	if(ret < 0)
	    goto i2c_err;

	mutex_unlock(&ts->i2c_mutex);
	return  0;

i2c_err:
	mutex_unlock(&ts->i2c_mutex);
	TS_LOG_ERR("i2c read error, ret = %d\n",ret);
	return -1;
}

int hideep_i2c_write(struct ist510e *ts, u16 addr, u16 len, u8 *buf)
{
	int ret = -1;
	int i;

	TS_LOG_DEBUG("hideep_i2c_write:addr = 0x%04x,len = %d\n",addr,len);
	if(g_ts_log_cfg>=1){
		for(i=0;i<len;i++){
			if(i%16==0){
				if(i!=0)
					printk("\n");
				printk("%s:%d:buf[0x%04x]\n",__FUNCTION__,__LINE__,i);
			}
				printk("0x%02x\n",buf[i]);
		}
			printk("\n");
	}
	mutex_lock(&ts->i2c_mutex);
	ts->seg_buff[0] = (addr >> 0) & 0xFF;
	ts->seg_buff[1] = (addr >> 8) & 0xFF;
	memcpy(ts->seg_buff+2, buf, len);
	ret = ts->huawei_ts_data->bops->bus_write(ts->seg_buff, 2+len);
	if(ret < 0){
		TS_LOG_ERR("i2c write address error\n");
		goto i2c_err;
	}
	mutex_unlock(&ts->i2c_mutex);
	return  0;

i2c_err:
	mutex_unlock(&ts->i2c_mutex);
	TS_LOG_ERR("i2c write error, ret = %d\n",ret);    
	return -1;
}

static int hideep_item_switch(u8 rw, u32 addr, u32 len, u8* buffer)
{
	s32 ret = 0;
	struct ist510e *ts   = g_istxxxx_data;

	switch (rw) 
	{
		case TS_ACTION_WRITE:
			ret = hideep_i2c_write(ts, addr, len, buffer);
			break;
		case TS_ACTION_READ :
			ret = hideep_i2c_read (ts, addr, len, buffer);
			break;
		default:
			ret = -EINVAL;
			break;
	}

	return ret ;
}

static s32 hideep_get_event(struct ist510e *ts)
{
	s32 ret;
	u8 i2c_buff[2];
	s32 touch_count = 0;
	uint32_t info_size;
	
	TS_LOG_DEBUG("hideep_get_event enter\n");
#ifdef HIDEEP_READ_I2C_CNT_DATA
	ret = hideep_i2c_read(ts, TOUCH_COUNT_ADDR, TOUCH_MAX_COUNT*sizeof(struct ist510e_touch_evt)+2, (u8*)ts->i2c_buf);
	memcpy((u8*)i2c_buff,(u8*)ts->i2c_buf,2);
#else
	ret = hideep_i2c_read(ts, TOUCH_COUNT_ADDR, 2, (u8*)&i2c_buff);
#endif
	if(ret < 0)
		goto i2c_err;
	ts->input_touch_nr = i2c_buff[0];
	ts->input_key_nr = i2c_buff[1]&0x0f;
	ts->input_event_nr = ((i2c_buff[1]&0xf0)>>4);
	TS_LOG_DEBUG("enter buf[0] = 0x%02x, buf[1] = 0x%02x\n", i2c_buff[0], i2c_buff[1]);
	TS_LOG_DEBUG("touch = %d, key = %d, event = %d \n", ts->input_touch_nr, ts->input_key_nr, ts->input_event_nr);
	if( ts->input_touch_nr >TOUCH_MAX_COUNT || ts->input_key_nr >KEYS_MAX_COUNT){
		TS_LOG_ERR("over size error touch = %d, key = %d\n",ts->input_touch_nr,ts->input_key_nr);
		ts->input_touch_nr = 0;
		ts->input_key_nr = 0;
	}
	touch_count = ts->input_touch_nr + ts->input_key_nr;
	if (ts->input_touch_nr > 0){
		info_size = ts->input_touch_nr *sizeof(struct ist510e_touch_evt);
#ifdef HIDEEP_READ_I2C_CNT_DATA
		memcpy((u8*)ts->input_evt,(u8*)(ts->i2c_buf+2),ts->input_touch_nr *sizeof(struct ist510e_touch_evt));
#else
		ret = hideep_i2c_read(ts, TOUCH_READ_START_ADDR, info_size, (u8*)ts->input_evt);
#endif
		if (ret < 0){
			goto i2c_err;
		}
#ifdef HIDEEP_TRACE_TOUCH_EVENT	//for debug for ghost and missing point
		if(ts->debug_evt){
			ts->debug_index = ts->debug_index>=MAX_DEBUG_COUNT?0:ts->debug_index;
			ts->debug_evt[ts->debug_index].count = ts->input_touch_nr;
			ktime_get_ts(&ts->event_time[ts->debug_index]);
			memcpy(&ts->debug_evt[ts->debug_index].events[0],(u8*)ts->input_evt,info_size);
			ts->debug_index++;
			ts->debug_total++;
			ts->debug_total = ts->debug_total>2000000?2000000:ts->debug_total;
		}
#endif
	}
	if (ts->input_key_nr > 0){
		uint32_t info_size = ts->input_key_nr*sizeof(struct ist510e_touch_key);
		ret = hideep_i2c_read(ts, KEY_READ_START_ADDR, info_size, (u8*)ts->input_key);
		if (ret < 0){
			goto i2c_err;
		}
	}
	return touch_count;
i2c_err:
	TS_LOG_ERR("hideep_get_event i2c err\n");
	return -1;
}

#ifdef ISTCORE_IF_DEVICE
s32 hideep_get_image(struct ist510e *ts)
{
	s32 ret = 0;
	struct ist510e_debug_dev  *debug_dev = &ts->debug_dev;



	TS_LOG_DEBUG("hideep_get_image enter\n");
	ret = hideep_i2c_read(ts, VR_ADDR_IMAGE, debug_dev->im_size, debug_dev->im_buff);
	if(ret < 0)
		goto i2c_err;
	TS_LOG_DEBUG( "load image from sensor(%d)\n", debug_dev->im_size);

	return ret;
i2c_err:
	TS_LOG_ERR("error!\n");
	return ret;
}
#endif

static int hideep_capability(struct input_dev *input_dev, struct ts_device_data *ts_dev_data)
{
	u32 i = 0;

	set_bit(EV_SYN, input_dev->evbit);
	set_bit(EV_KEY, input_dev->evbit);
	set_bit(EV_ABS, input_dev->evbit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOL_FINGER, input_dev->keybit);

	set_bit(TS_DOUBLE_CLICK, input_dev->keybit);
	set_bit(TS_SLIDE_L2R, input_dev->keybit);
	set_bit(TS_SLIDE_R2L, input_dev->keybit);
	set_bit(TS_SLIDE_T2B, input_dev->keybit);
	set_bit(TS_SLIDE_B2T, input_dev->keybit);
	set_bit(TS_CIRCLE_SLIDE, input_dev->keybit);
	set_bit(TS_LETTER_c, input_dev->keybit);
	set_bit(TS_LETTER_e, input_dev->keybit);
	set_bit(TS_LETTER_m, input_dev->keybit);
	set_bit(TS_LETTER_w, input_dev->keybit);
	set_bit(TS_PALM_COVERED, input_dev->keybit);

	set_bit(TS_TOUCHPLUS_KEY0, input_dev->keybit);
	set_bit(TS_TOUCHPLUS_KEY1, input_dev->keybit);
	set_bit(TS_TOUCHPLUS_KEY2, input_dev->keybit);
	set_bit(TS_TOUCHPLUS_KEY3, input_dev->keybit);
	set_bit(TS_TOUCHPLUS_KEY4, input_dev->keybit);

#ifdef INPUT_PROP_DIRECT
	set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
#endif

#ifdef IST510E_KEYBUTTON
	for (i = 0 ; i < ARRAY_SIZE(tsp_keycodes); i++)
		set_bit(tsp_keycodes[i], input_dev->keybit);
#endif
	input_set_abs_params(input_dev, ABS_MT_POSITION_X,  0, ts_dev_data->x_max_mt, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y,  0, ts_dev_data->y_max_mt, 0, 0);
	// z value's range.
	input_set_abs_params(input_dev, ABS_MT_PRESSURE,  0, 65535,0, 0);
	 // w value's range.
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, 255,0, 0);
	input_set_abs_params(input_dev, ABS_MT_TRACKING_ID, 0, TOUCH_MAX_COUNT ,0, 0);
	return 0;
}

static int hideep_get_version(struct ist510e *ts)
{
	s32 ret = 0;
	DWZ_INFO_T  *dmz_info = &ts->dwz_info;

	hideep_reset_ic();
	mdelay(60);
	ret = hideep_i2c_read(ts, VR_VERSION_ADDR, 2, (u8*)&dmz_info->pannel.version);	//ic fw version
	if(ret < 0)
		goto i2c_err;
	TS_LOG_INFO("vr version : %04x\n", dmz_info->pannel.version);
	
	return 0;
i2c_err:
	TS_LOG_ERR("hideep_get_version error\n");
	return ret;
}
/*------------------------------------------------------------------------------
 *
 *-----------------------------------------------------------------------------*/
void hideep_reset_ic(void)
{
	struct ist510e *ts_drv = g_istxxxx_data;
	struct ts_device_data *dat  = ts_drv->huawei_ts_data;
	TS_LOG_INFO("hideep_reset_ic enter \n");
	gpio_direction_output(dat->reset_gpio, 1);
	mdelay(2);
	gpio_direction_output(dat->reset_gpio, 0);
	mdelay(5);
	gpio_direction_output(dat->reset_gpio, 1);
	TS_LOG_INFO("hideep_reset_ic finish \n");
	return ;
}

static void hideep_dump_config(struct ts_device_data *data)
{
	TS_LOG_INFO("irq_gpio             : %d\n",data->irq_gpio);
	TS_LOG_INFO("irq_config           : %d\n",data->irq_config);
	TS_LOG_INFO("reset_gpio           : %d\n",data->reset_gpio);
	TS_LOG_INFO("algo_id              : %d\n",data->algo_id);
	TS_LOG_INFO("tp_func_flag        : %d\n",data->tp_func_flag);
	TS_LOG_INFO("vci_gpio_ctrl        : %d\n",data->vci_gpio_ctrl);
	TS_LOG_INFO("vddio_gpio_ctrl      : %d\n",data->vddio_gpio_ctrl);    
	TS_LOG_INFO("vci_regulator_type   : %d\n",data->vci_regulator_type);
	TS_LOG_INFO("vddio_regulator_type : %d\n",data->vddio_regulator_type);
	TS_LOG_INFO("x_max                : %d\n",data->x_max);
	TS_LOG_INFO("y_max                : %d\n",data->y_max);
	TS_LOG_INFO("x_max_mt             : %d\n",data->x_max_mt);
	TS_LOG_INFO("y_max_mt             : %d\n",data->y_max_mt);
	TS_LOG_INFO("ic_type              : %d\n",data->ic_type);
	TS_LOG_INFO("support_3d_func : %d\n", data->support_3d_func);
	TS_LOG_INFO("supported_func_indicater : %d\n", data->supported_func_indicater);
	return;
}

static int hideep_parse_config(struct device_node *device, struct ts_device_data *data)
{
	s32 ret = 0;
	int index = 0;
	int array_len;
	const char *raw_data_dts = NULL;
	int read_val=0;

	TS_LOG_INFO("hideep_parse_config enter\n");
	ret  = of_property_read_u32(device, HIDEEP_IRQ_CFG, &data->irq_config);
	ret |= of_property_read_u32(device, HIDEEP_ALGO_ID, &data->algo_id);
	ret |= of_property_read_u32(device, HIDEEP_IC_TYPES,  &data->ic_type);
	ret |= of_property_read_u32(device, HIDEEP_X_MAX_MT,  &data->x_max_mt);
	ret |= of_property_read_u32(device, HIDEEP_Y_MAX_MT, &data->y_max_mt);
	ret |= of_property_read_u32(device, HIDEEP_X_MAX, &data->x_max);
	ret |= of_property_read_u32(device, HIDEEP_Y_MAX,	&data->y_max);
	ret |= of_property_read_u32(device, HIDEEP_TP_FUNC_FLAG, &data->tp_func_flag);
	ret |= of_property_read_u32(device, HIDEEP_VCI_GPIO_TYPE, &data->vci_gpio_type);
	ret |= of_property_read_u32(device, HIDEEP_VCI_REGULATOR_TYPE, &data->vci_regulator_type);
	ret |= of_property_read_u32(device, HIDEEP_VDDIO_GPIO_TYPE, &data->vddio_gpio_type);
	ret |= of_property_read_u32(device, HIDEEP_VDDIO_REGULATOR_TYPE, &data->vddio_regulator_type);

	ret = of_property_read_u32(device, "roi_supported", &read_val);
	if (!ret) {
		TS_LOG_INFO("get chip specific roi_supported = %d\n", read_val);
		g_ts_data.feature_info.roi_info.roi_supported = (u8)read_val;
	}else {
		TS_LOG_INFO("can not get roi_supported value\n");
		g_ts_data.feature_info.roi_info.roi_supported = 0;
	}

	ret = of_property_read_u32(device, "roi_control_addr", &read_val);
	if (!ret) {
		TS_LOG_INFO("get chip specific roi_control_addr = 0x%04x\n", read_val);
		g_ts_data.feature_info.roi_info.roi_control_addr = (u16)read_val;
	}

	ret = of_property_read_u32(device, "roi_control_bit", &read_val);
	if (!ret) {
		TS_LOG_INFO("get chip specific roi_control_bit = %d\n", read_val);
		g_ts_data.feature_info.roi_info.roi_control_bit = (u8)read_val;
	}

	ret = of_property_read_u32(device, "roi_data_addr", &read_val);
	if (!ret) {
		TS_LOG_INFO("get chip specific roi_data_addr = 0x%04x\n", read_val);
		g_ts_data.feature_info.roi_info.roi_data_addr = (u16)read_val;
	}

	ret = of_property_read_u32(device, IST_RAWDATA_ARRANGE_SWAP, &data->rawdata_arrange_swap);
	if (ret) {
		TS_LOG_ERR("get rawdata_arrange_swap failed\n");
		data->rawdata_arrange_swap = 0;
	}

	ret = of_property_read_u32(device, HIDEEP_UNIT_CAP_TEST_INTERFACE, &data->unite_cap_test_interface);
	if (ret) {
		TS_LOG_ERR("get unite_cap_test_interface failed\n");
		ret = 0;
		//goto err;
	}

	ret = of_property_read_u32(device, "support_3d_func", &data->support_3d_func);
	if (ret) {
		data->support_3d_func = 0;
		TS_LOG_ERR("use default support_3d_func value:%d\n", data->support_3d_func);
	}
	
	ret = of_property_read_u32(device, "supported_func_indicater", &data->supported_func_indicater);
	if (ret) {
		data->supported_func_indicater = 0;     
		TS_LOG_ERR("use default supported_func_indicater value:%d\n", data->supported_func_indicater);
	}

	ret = of_property_read_string(device, "tp_test_type", &data->tp_test_type);
	if (ret) {
		TS_LOG_INFO("get device tp_test_type not exit,use default value\n");
		strncpy(data->tp_test_type,"Normalize_type:judge_different_reslut",TS_CAP_TEST_TYPE_LEN);
		ret = 0;
	}

	if (1 == data->unite_cap_test_interface) {
		array_len = of_property_count_strings(device, "raw_data_limit");
		if (array_len <= 0 || array_len > RAWDATA_NUM) {
			TS_LOG_ERR("raw_data_limit length invaild or dts number is larger than:%d\n", array_len);
		}

		for(index = 0; index < array_len; index++){
			ret = of_property_read_string_index(device, "raw_data_limit", index, &raw_data_dts);
			if (ret) {
				TS_LOG_ERR("read index = %d,raw_data_limit = %s,ret = %d error,\n", index, raw_data_dts, ret);
				ret = 0;
			}

			data->raw_limit_buf[index] = simple_strtol(raw_data_dts, NULL, 10);
			TS_LOG_INFO("rawdatabuf[%d] = %d\n", index, data->raw_limit_buf[index]);
		}
	}

	if (ret) {
		goto err;
	}
	if(data->vci_gpio_type == 1) {
		data->vci_gpio_ctrl = of_get_named_gpio(device, HIDEEP_VCI_GPIO_CTRL, 0);
		if (!gpio_is_valid(data->vci_gpio_ctrl)) {
			goto err;
		}
	}
	if(data->vddio_gpio_type == 1) 	{
		data->vddio_gpio_ctrl = of_get_named_gpio(device, HIDEEP_VDDIO_GPIO_CTRL, 0);
		if (!gpio_is_valid(data->vddio_gpio_ctrl)) {
			goto err;
		}
	}
	data->irq_gpio = of_get_named_gpio(device, HIDEEP_IRQ_GPIO, 0);
	if (!gpio_is_valid(data->irq_gpio)) {
		goto err;
	}
	data->reset_gpio = of_get_named_gpio(device, HIDEEP_RST_GPIO, 0);
	if (!gpio_is_valid(data->reset_gpio)) {
		goto err;
	}
	hideep_dump_config(data);
	TS_LOG_INFO(" hideep_parse_config OK.\n");

	return NO_ERR;
err:
	TS_LOG_ERR("hideep_parse_config failed\n");    
	return -EINVAL;;
}

static int hideep_input_config(struct input_dev *input_dev)
{
	struct ist510e *ts_drv =  g_istxxxx_data;

	TS_LOG_INFO("hideep_input_config enter\n");
	ts_drv->input_dev = input_dev;
	hideep_capability(ts_drv->input_dev, ts_drv->huawei_ts_data);

	return NO_ERR;
}

static int hideep_chip_detect(struct device_node *device, struct ts_device_data *ts_data, struct platform_device *ts_dev)
{
	s32 ret = 0;

	TS_LOG_INFO("hideep_chip_detect enter\n");

	g_istxxxx_data = kzalloc(sizeof(struct ist510e), GFP_KERNEL);
	if(g_istxxxx_data == NULL) {
		TS_LOG_ERR("g_istxxxx_data alloc error\n");
		goto err;
	}

	g_istxxxx_data->huawei_ts_data = ts_data;
	g_istxxxx_data->huawei_ts_dev = ts_dev ;
	g_istxxxx_data->huawei_ts_dev->dev.of_node = device;                //for dsti reference
	g_istxxxx_data->client = ts_data->client;
	g_istxxxx_data->dev_state = ISTCORE_PWR_NORMAL;
	g_istxxxx_data->irq = gpio_to_irq(ts_data->irq_gpio);
	g_istxxxx_data->tch_bit = 0;
	g_istxxxx_data->huawei_ts_data->easy_wakeup_info.sleep_mode = TS_POWER_OFF_MODE;
	g_istxxxx_data->huawei_ts_data->easy_wakeup_info.easy_wakeup_gesture = false;
	g_istxxxx_data->huawei_ts_data->easy_wakeup_info.easy_wakeup_flag = false;
	g_istxxxx_data->huawei_ts_data->easy_wakeup_info.palm_cover_flag = false;
	g_istxxxx_data->huawei_ts_data->easy_wakeup_info.palm_cover_control = false;
	g_istxxxx_data->huawei_ts_data->easy_wakeup_info.off_motion_on = false;
	g_istxxxx_data->glove_mode = 0;
	g_istxxxx_data->holster_mode = 0;
	g_istxxxx_data->z_status = false;
	g_istxxxx_data->apple_weight_flag = false;
	g_istxxxx_data->gesture_enable = false;

	mutex_init(&g_istxxxx_data->i2c_mutex);
	mutex_init(&g_istxxxx_data->dev_mutex);

	// prepare hardware for ic detect
	ret = hideep_regulator_get();
	if (ret < 0) {
		TS_LOG_ERR("regulator error\n"); 
		goto err_rgt;
	}
	ret = hideep_gpio_request();
	if (ret < 0) {
		TS_LOG_ERR("gpio get  error\n"); 
		goto err_gpio;
	}
	ret = hideep_pinctrl_get_init();
	if (ret < 0) {
		goto err_pinctrl_get;
	}
	hideep_power_on();
#ifdef CRIMSON	//ic name
	ret = hideep_get_version(g_istxxxx_data);
	if(ret < 0) {
		TS_LOG_ERR("no ic is detected\n");
		goto err_aux;
	}
#endif
	TS_LOG_INFO("detect ok.\n");
	g_istxxxx_data->apple_weight_workqueue = create_singlethread_workqueue("apple_weight_wq");
	INIT_WORK(&g_istxxxx_data->apple_weight_work, apple_weight_timeout_func);
	return NO_ERR;
err_aux:
	hideep_power_off();
err_pinctrl_get:
	hideep_gpio_free();
err_gpio:
	hideep_regulator_put();
err_rgt:
err:    
	if (g_istxxxx_data)
		kfree(g_istxxxx_data);
	return ret;
}

static int hideep_reset(void)
{
	hideep_reset_ic();

	return NO_ERR;
}

static void hideep_shutdown(void)
{
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	TS_LOG_INFO("hideep_shutdown\n");
	hideep_power_off();
	hideep_gpio_free();
	hideep_regulator_put();
	hideep_pinctrl_select_lowpower();
	return;
}

static int hideep_init(void)
{
	struct ist510e *ts_drv =  g_istxxxx_data;
	s32 ic_type  =  ts_drv->huawei_ts_data->ic_type;
	int ret = 0;

	TS_LOG_INFO("hideep_init enter\n");
	switch(ic_type)
	{
		case IST_GREEN:
			break;
		case IST_CRIMSON:
#ifdef ISTCORE_IF_DEVICE	//debug device
			ret = hideep_iface_init(g_istxxxx_data);
			if(ret < 0) {
				TS_LOG_ERR("debug interface device error\n");    
				goto err_deivce;
			}
/*
			ret = hideep_sysfs_init(g_istxxxx_data);
			if (ret != 0)
				goto err_deivce;
			break;
*/
#endif
		case IST_INDIGO :
			break;
		default:
			break;
	}
	return NO_ERR;

#ifdef ISTCORE_IF_DEVICE
err_deivce:
	hideep_iface_uninit(g_istxxxx_data);
	return ret;
#endif
}

static int hideep_irq_top_half(struct ts_cmd_node *cmd)
{
	cmd->command = TS_INT_PROCESS;
	return NO_ERR;
}

static int hideep_irq_bottom_half(struct ts_cmd_node *in_cmd, struct ts_cmd_node *out_cmd)
{
	s32 t_evt;
	s32 ret = 0;
	u32 x,y;
	u8 gesture[25];
	u8 command;
	s32 report_coordinate;
	struct ist510e *ts =  g_istxxxx_data;
#ifdef ISTCORE_IF_DEVICE	//for debug
	struct ist510e_debug_dev  *debug_dev = &ts->debug_dev;
#endif
	struct ts_fingers *info = &out_cmd->cmd_param.pub_params.algo_param.info;
	s32 i;
	s32 id;
	s16 * ps;
	bool  btn_up ;
	bool  btn_dn ;
	bool  btn_mv ;
	struct ist510e_touch_evt *finger;
	u16 temp_status;
	struct ts_easy_wakeup_info *gesture_info;
#ifdef ROI
	char roi_buf[49];
#endif

	out_cmd->cmd_param.pub_params.algo_param.algo_order = 0;//ts->huawei_ts_data->algo_id;
	if(ts->dev_state != ISTCORE_PWR_NORMAL){
		out_cmd->command = TS_INVAILD_CMD;
		goto ret;
	}

#ifdef ISTCORE_IF_DEVICE
	if(debug_dev->im_r_en == 1) {
		mutex_lock  (&ts->dev_mutex);
		out_cmd->command = TS_INVAILD_CMD;
		hideep_get_image(ts);
		ts->debug_dev.i_rdy = 1;                                                  // TODO : need semaphore..
		wake_up_interruptible(&ts->debug_dev.i_packet);
		mutex_unlock(&ts->dev_mutex);
		return NO_ERR;
	}
#endif
	t_evt = hideep_get_event(ts);			//event count
	gesture_info = &g_istxxxx_data->huawei_ts_data->easy_wakeup_info;
	info->cur_finger_number = ts->input_touch_nr;
	TS_LOG_DEBUG("apple_weight_init = %d, input_event_nr = %d",ts->apple_weight_init, ts->input_event_nr);
	if(ts->apple_weight_init && ts->input_event_nr){
		ret = hideep_i2c_read(ts, TOUCH_READ_START_ADDR+TOUCH_MAX_COUNT*sizeof(struct ist510e_touch_evt)+12, 4, (u8*)gesture);
		TS_LOG_DEBUG("gesture[0] = %d",gesture[0]);
		if(HIDEEP_APPLE_WEIGHT_READY==gesture[0]){
			mutex_lock  (&ts->dev_mutex);
			memcpy(&ts->apple_weight_buff,&gesture[2],2);
			ts->apple_weight_flag = true;
			mutex_unlock(&ts->dev_mutex);
			TS_LOG_DEBUG("apple weight buf, weight = %d\n", ts->apple_weight_buff);
		}
	}else
	if(TS_GESTURE_MODE == gesture_info->sleep_mode){
		TS_LOG_DEBUG("ts->input_event_nr = %d\n",ts->input_event_nr);
		info->gesture_wakeup_value = 0;
		if ((true == gesture_info->off_motion_on)&&(ts->input_event_nr ==1)){
			ret = hideep_i2c_read(ts, TOUCH_READ_START_ADDR+TOUCH_MAX_COUNT*sizeof(struct ist510e_touch_evt)+12, 26, (u8*)gesture);
			TS_LOG_DEBUG("gesture = 0x%02x\n",gesture[0]);
			switch(gesture[0]){
			case HIDEEP_GES_DOUBLE_TAP:
				if (CHECK_ENABLE_GESTURE(GESTURE_DOUBLE_CLICK) & gesture_info->easy_wakeup_gesture) {
					TS_LOG_DEBUG("double tap wake up.\n");
					info->gesture_wakeup_value = TS_DOUBLE_CLICK;
				}
				report_coordinate = 2;
				break;
			case HIDEEP_GES_CHAR:
				TS_LOG_DEBUG("character wake up.\n");
				report_coordinate = 6;
				switch(gesture[1]){
					case HIDEEP_CHAR_C:
						if (CHECK_ENABLE_GESTURE(GESTURE_LETTER_c) & gesture_info->easy_wakeup_gesture) {
							info->gesture_wakeup_value = TS_LETTER_c;
						}
						break;
					case HIDEEP_CHAR_E:
						if (CHECK_ENABLE_GESTURE(GESTURE_LETTER_e) & gesture_info->easy_wakeup_gesture) {
							info->gesture_wakeup_value = TS_LETTER_e;
						}
						break;
					case HIDEEP_CHAR_M:
						if (CHECK_ENABLE_GESTURE(GESTURE_LETTER_m) & gesture_info->easy_wakeup_gesture) {
							info->gesture_wakeup_value = TS_LETTER_m;
						}
						break;
					case HIDEEP_CHAR_W:
						if (CHECK_ENABLE_GESTURE(GESTURE_LETTER_w) & gesture_info->easy_wakeup_gesture) {
							info->gesture_wakeup_value = TS_LETTER_w;
						}
						break;
					default:
						TS_LOG_ERR("incorrect character.\n");
						break;
				}
				TS_LOG_DEBUG("character wake up.\n");
				break;
			default:
				TS_LOG_ERR("incorrect ID.\n");
				break;
			}
		}
		TS_LOG_DEBUG("info->gesture_wakeup_value = %d\n",info->gesture_wakeup_value);
		if((true == gesture_info->off_motion_on)&&(info->gesture_wakeup_value!=0)&&(g_istxxxx_data->gesture_enable)){
			wake_lock_timeout(&g_ts_data.ts_wake_lock, 5*HZ);
			gesture_info->off_motion_on = false;
			ps = (s16 *)&gesture[2];
			for(i = 0;i<report_coordinate;i++){	
				x = *ps++;
				y = *ps++;
				gesture_info->easywake_position[i] = (x<<16)|y;
				TS_LOG_DEBUG("x[%d] = %d, y[%d] = %d pos[%d] = 0x%x\n",i,x,i,y,i,gesture_info->easywake_position[i]);
			}
			//out_cmd->cmd_param.pub_params.algo_param.algo_order  = 0;
			ts->input_touch_nr = 0;
			info->cur_finger_number = 0;
			//command = 1;
			//hideep_item_switch(TS_ACTION_WRITE, IST_RESET, 1, &command);
		}else if(true == gesture_info->off_motion_on){
			//incorrect gesture wake up ID. let IC sleep again.
			TS_LOG_DEBUG("re-enter gesture mode \n");
			out_cmd->command = TS_INVAILD_CMD;
			command = 1;
			hideep_item_switch(TS_ACTION_WRITE, VR_LPWU, 1, &command);
			command = 0;
			hideep_i2c_write(ts, IST_ENTER_SANDMAN, 1, &command);
			goto ret;
		}
	}
	for(i = 0; i < TOUCH_MAX_COUNT; i++) {		// memset 0
		info->fingers[i].status = 0;
	}
	finger = ts->input_evt;
	temp_status = 0;
	if((ts->z_flag_calib2)&&(info->cur_finger_number)&&(!ts->z_flag_ready)){
		TS_LOG_DEBUG("z = 0x%x, index = %d\n", finger[0].z, ts->z_index);
		if(ts->z_index>=ts->z_calib_start){
			TS_LOG_DEBUG("reading\n");
			ts->z_data[ts->z_index] = finger[0].z;
			if(ts->z_index >= ts->z_calib_end){
				TS_LOG_DEBUG("ready\n");
				ts->z_flag_ready = true;
			}
		}
		if(!ts->z_flag_ready)
			ts->z_index++;
	}else if(info->cur_finger_number){
		TS_LOG_DEBUG("z_buffer, %d\n",finger[0].z);
		mutex_lock  (&ts->dev_mutex);
		ts->z_buffer = finger[0].z;
		ts->z_status = true;
		mutex_unlock(&ts->dev_mutex);
	}
	if(0 == info->cur_finger_number)
		ts->apple_weight_buff=0;
	for(i = 0; i < info->cur_finger_number; i++){
		id = (finger[i].index >> 0) & 0x0F;
		TS_LOG_DEBUG("%s id = %d, flag = 0x%02x\n",__FUNCTION__,id, finger[i].flag);
		btn_up  = (finger[i].flag  >> EV_RELEASED) & 0x01;
		btn_dn  = (finger[i].flag  >> EV_FIRST_CONTACT) & 0x01;
		btn_mv  = (finger[i].flag  >> EV_DRAG_MOVE) & 0x01;
		if((id>=TOUCH_MAX_COUNT)||(id<0))
			continue;
		if(finger[i].z == 0)
			if(btn_dn | btn_mv)
				finger[i].z = 2;
		if(btn_up){
			TS_LOG_DEBUG("id = %d up.\n",id);
			info->fingers[id].status = TS_FINGER_RELEASE;
			info->fingers[id].x = finger[i].x;
			info->fingers[id].y = finger[i].y;
		}else if(btn_dn | btn_mv){
			TS_LOG_DEBUG("id = %d down.\n",id);
			info->fingers[id].status = TS_FINGER_PRESS;
			info->fingers[id].x = finger[i].x;
			info->fingers[id].y = finger[i].y;
			info->fingers[id].major = finger[i].w;
			info->fingers[id].pressure = finger[i].z;
			temp_status |= 1 << id;
		}
	}
	TS_LOG_DEBUG("temp_status = 0x%x, pre_status = 0x%x, eor = 0x%x, result = 0x%x", temp_status, pre_status, temp_status^pre_status,(temp_status^pre_status)&temp_status);
	if((temp_status!=pre_status) && ((temp_status^pre_status)&temp_status))
	{
		TS_LOG_DEBUG("%s ROI readying\n",__FUNCTION__);
		ret = hideep_i2c_read(g_istxxxx_data, VR_READ_ROI_DATA_ADDR, 49, (u8 *)roi_buf);
		if(!ret){
			ps = (s16*)(&g_istxxxx_data->roi.diff[0]);
			*ps++ = 7;
			*ps++ = 7;
			for(i=0;i<49;i++){
				*ps = (short)(((signed char)roi_buf[i])*8);
				TS_LOG_DEBUG("ps = %d roi buf = %d\n", *ps, roi_buf[i]);
				ps++;
			}
		}
	}
	pre_status = temp_status;
	if(ts->input_key_nr){
		TS_LOG_DEBUG("flag = 0x%02x z = %d\n", ts->input_key[0].flag, ts->input_key[0].z);
		if(ts->input_key[0].flag&0x40)
			info->special_button_flag = 1;
		else
			info->special_button_flag = 0;
        switch(ts->input_key[0].flag&0xf)
        {
		case 1:
			info->special_button_key = TS_TOUCHPLUS_KEY0;/*KEY_F21*/
			break;
		case 2:
			info->special_button_key = TS_TOUCHPLUS_KEY1;/*KEY_F22*/
			break;
		case 3:
			info->special_button_key = TS_TOUCHPLUS_KEY2;/*KEY_F23*/
			break;
		case 4:
			info->special_button_key = TS_TOUCHPLUS_KEY3;/*KEY_F19*/
			break;
		case 5:
			info->special_button_key = TS_TOUCHPLUS_KEY4;/*KEY_F20*/
			break;
		default:
			TS_LOG_ERR("the get_button_number is invald\n");
			break;
        }
	}
	//if(out_cmd->cmd_param.pub_params.algo_param.algo_order)
		out_cmd->command = TS_INPUT_ALGO;
	//else
		//out_cmd->command = TS_REPORT_INPUT;
ret:    
	return NO_ERR;
}
static int hideep_before_suspend(void)
{
	u8 cmd = 0;
	struct ist510e *ts = g_istxxxx_data;
	if(ts->apple_weight_init){
		TS_LOG_DEBUG("still in apple weight mode\n");
		ts->apple_weight_init=0;
		cancel_work_sync(&ts->apple_weight_work);
		cmd=0;
		if(hideep_item_switch(TS_ACTION_WRITE, VR_SINGLE_TOUCH, 1, &cmd)<0){
			hideep_reset_ic();
		}
	}
}

static int hideep_suspend(void)
{
	struct ist510e *ts = g_istxxxx_data;
	u8 cmd = 0;
	u8 gesture = 0;
	struct ts_easy_wakeup_info *gesture_info;

	TS_LOG_INFO("suspend\n");
	gesture_info = &g_istxxxx_data->huawei_ts_data->easy_wakeup_info;
	switch (gesture_info->sleep_mode) {
		case TS_POWER_OFF_MODE:
			if(ts->dev_state == ISTCORE_PWR_SLEEP)
				goto ret;
			ts->dev_state = ISTCORE_PWR_SLEEP;
			hideep_power_off();
			break;
		/*for gesture wake up mode suspend.*/
		case TS_GESTURE_MODE:
			TS_LOG_INFO("enter gesture mode.\n");
			if (false == gesture_info->off_motion_on)
				gesture_info->off_motion_on = true;
			gesture = 1;
			hideep_item_switch(TS_ACTION_WRITE, VR_LPWU, 1, &gesture);
			gesture_info->easy_wakeup_flag = true;
#ifdef CRIMSON
			hideep_i2c_write(ts, IST_ENTER_SANDMAN, 1, &cmd);
#endif  
			break;
		default:
			TS_LOG_ERR("no suspend.\n");
			return -EINVAL;
	}
	TS_LOG_INFO("suspend end.\n");
ret:
	return NO_ERR;
}

static int hideep_resume(void)
{
	struct ist510e *ts = g_istxxxx_data;
	u8 gesture;
	struct ts_easy_wakeup_info *gesture_info;

	TS_LOG_INFO("hideep_resume\n");
	gesture_info = &g_istxxxx_data->huawei_ts_data->easy_wakeup_info;
	switch (gesture_info->sleep_mode) {
		case TS_POWER_OFF_MODE:
			hideep_power_on();
			msleep(20);
			if(ts->dev_state == ISTCORE_PWR_NORMAL)
				goto ret;
			ts->dev_state = ISTCORE_PWR_NORMAL  ;
#ifdef CRIMSON
			hideep_reset_ic(); 
			msleep(25);
#endif
			break;
		case TS_GESTURE_MODE:
			TS_LOG_INFO("exit gesture mode.\n");
			hideep_reset_ic(); 
			msleep(25);
			gesture = 0;
			hideep_item_switch(TS_ACTION_WRITE, VR_LPWU, 1, &gesture);
			if(gesture_info->off_motion_on)
				gesture_info->off_motion_on = false;
			gesture_info->easy_wakeup_flag = false;
			break;
		default:
			TS_LOG_ERR("no resume.\n");
			return -EINVAL;
	}
	TS_LOG_INFO("resume end.\n");
	//---------------------------------
ret:
	return NO_ERR;
}

static int hideep_after_resume(void *feature_info)
{
	int retval = NO_ERR;
	struct ist510e *ts = g_istxxxx_data;
	struct ts_feature_info *info = (struct ts_feature_info *)feature_info;

	TS_LOG_INFO("hideep_after_resume enter\n");
	//glove mode;
	hideep_item_switch(TS_ACTION_WRITE, VR_GLOVE, 1, &ts->glove_mode);
	//holster mode.
	retval = hideep_holster_switch(&info->holster_info);
	if (retval < 0) {
		TS_LOG_ERR("Failed to set holster switch(%d), err: %d\n",
			info->holster_info.holster_switch, retval);
	}
	hideep_roi_switch(&info->roi_info);
	TS_LOG_INFO("hideep_after_resume exit\n");
	return retval;
}

static int hideep_fw_update_sd(void)
{
	s32 ret = 0;
	struct ist510e *ts = g_istxxxx_data;

	TS_LOG_INFO("enter %s\n", __FUNCTION__);
	ret = hideep_load_ucode(ts, IST520E_UC,0);
	if(ret < 0){
		TS_LOG_ERR("fw update failed\n");    
		goto err;
	}
	TS_LOG_INFO("fw update success\n");

	return NO_ERR;
err:
	return -EINVAL;
}

static int hideep_fw_update_boot(char *file_name)
{
	s32 ret;
	const struct firmware *fw_entry;    
	struct ist510e *ts_drv = g_istxxxx_data;
	struct device *dev = &ts_drv->huawei_ts_dev->dev;

	u16 version;
	size_t file_name_size = strlen(file_name)+strlen("ist510e");
	char firmware_name[PRODUCT_ID_LENGTH + file_name_size +1];
	snprintf(firmware_name, sizeof(firmware_name), "ts/%s%s.bin", file_name, "ist510e");
	firmware_name[PRODUCT_ID_LENGTH + file_name_size] = 0;

	TS_LOG_INFO("hideep_fw_update_boot enter, firmware name is %s\n", firmware_name);
	ret = request_firmware(&fw_entry, firmware_name, dev);
	if(ret != 0){
		TS_LOG_ERR("request_firmware(%s) failed\n", firmware_name);
		goto err;
	}
	release_firmware(fw_entry);
	ret = hideep_i2c_read(ts_drv, VR_VERSION_ADDR, 2, (u8*)&version);
	if(ret < 0){
		TS_LOG_ERR("read i2c fail.\n"); 
		goto err;
	}
	TS_LOG_INFO("vr version : %04x\n", version);
	ret = hideep_load_ucode(ts_drv, firmware_name, version);
	if(ret < 0){
		TS_LOG_ERR("fw update failed\n");    
		goto err;
	}
	TS_LOG_INFO("fw update success\n");
	return NO_ERR;
err:
	return  ret;
}

static int hideep_get_info(struct ts_chip_info_param *info)
{
	struct ist510e *ts   = g_istxxxx_data;
	DWZ_INFO_T     *dmz_info = &ts->dwz_info ;
	struct ts_easy_wakeup_info *gesture_info;

	gesture_info = &g_istxxxx_data->huawei_ts_data->easy_wakeup_info;
	TS_LOG_INFO("hideep_get_info enter, ts->dev_state = %d\n", ts->dev_state);
	if((ISTCORE_PWR_NORMAL != ts->dev_state)&&
		(TS_GESTURE_MODE != gesture_info->sleep_mode)){
		TS_LOG_ERR("hideep_get_rawdata is not in normal mode \n");
		return -1;
	}
	if((TS_GESTURE_MODE == gesture_info->sleep_mode)&&
		(true == gesture_info->off_motion_on)){
		TS_LOG_ERR("hideep_get_rawdata is not in normal mode \n");
		return -1;
	}
	hideep_get_version(g_istxxxx_data);
	hideep_after_resume((void *)&g_ts_data.feature_info);
	snprintf(info->ic_vendor, PAGE_SIZE, "hideep-ist510e");
	snprintf(info->mod_vendor, PAGE_SIZE, "samsung");
	snprintf(info->fw_vendor, PAGE_SIZE,"%04x\n",  dmz_info->pannel.version);

	return NO_ERR;
}

static int hideep_holster_switch(struct ts_holster_info *info)
{
	int ret = NO_ERR;
	struct ist510e *ts = g_istxxxx_data;
	u8 cmd_buf[5]={0};
	int x0 = g_ts_data.feature_info.window_info.top_left_x0;
	int y0 = g_ts_data.feature_info.window_info.top_left_y0;
	int x1 = g_ts_data.feature_info.window_info.bottom_right_x1;
	int y1 = g_ts_data.feature_info.window_info.bottom_right_y1;
	u16 *p16;

	TS_LOG_INFO("switch = %d, Holster window_info is (x0=%d,y0=%d)(x1=%d,y1=%d)\n",\
		info->holster_switch,x0,y0,x1,y1);
	switch(info->op_action){
		case TS_ACTION_WRITE:
			if(!info->holster_switch){
				TS_LOG_INFO("disable holster mode.\n");
				cmd_buf[0] = 0x00;
				ret = hideep_i2c_write(ts, VR_HOLSTER, 1, cmd_buf);
				if(ret < 0){
					TS_LOG_ERR("i2c write error.\n");
					break;
				}
			}else{
				//send the sensitivity;
				cmd_buf[0] = 0x10;
				cmd_buf[1] = info->holster_switch;
				ret = hideep_i2c_write(ts, VR_HOLSTER, 2, cmd_buf);
				if(ret < 0){
					TS_LOG_ERR("i2c write error.\n");
					break;
				}
				//send the top_left x,y;
				cmd_buf[0] = 0x11;
				p16 = &cmd_buf[1];
				*p16++ = x0;
				*p16++ = y0;
				ret = hideep_i2c_write(ts, VR_HOLSTER, 5, cmd_buf);
				if(ret < 0){
					TS_LOG_ERR("i2c write error.\n");
					break;
				}
				//send the right_bottom x,y;
				cmd_buf[0] = 0x12;
				p16 = &cmd_buf[1];
				*p16++ = x1;
				*p16++ = y1;
				ret = hideep_i2c_write(ts, VR_HOLSTER, 5, cmd_buf);
				if(ret < 0){
					TS_LOG_ERR("i2c write error.\n");
					break;
				}
			}
			g_istxxxx_data->holster_mode = info->holster_switch;
			break;
		case TS_ACTION_READ:
			info->holster_switch = g_istxxxx_data->holster_mode;
			break;
		default:
			TS_LOG_ERR("no this action\n");
			break;
	}

	return ret;
}
static void apple_weight_timeout_func(struct work_struct *work)
{
	u8 cmd;
	struct ist510e *ts   = g_istxxxx_data;
	TS_LOG_DEBUG("apple_weight_timeout_func enter\n");
	do
	{
		if(!g_istxxxx_data->apple_weight_init){
			TS_LOG_DEBUG("apple_weight_timeout_func thread finish\n");
			break;
		}
		mdelay(100);
		TS_LOG_DEBUG("apple_weight_timeout_func time out = %d", g_istxxxx_data->apple_weight_timeout);
		g_istxxxx_data->apple_weight_timeout++;
	}while(g_istxxxx_data->apple_weight_timeout<20);
	cmd =0;
	if(hideep_item_switch(TS_ACTION_WRITE, VR_SINGLE_TOUCH, 1, &cmd)<0)
			hideep_reset_ic();
	g_istxxxx_data->apple_weight_init = 0;
	TS_LOG_DEBUG("apple_weight_timeout_func end\n");
	return 0;
}
static int hideep_single_touch_switch(struct ts_single_touch_info *info)
{
	int ret = NO_ERR;
	u8 cmd;
	u8 switch_buf;

	if(TS_ACTION_WRITE == info->op_action){
		TS_LOG_DEBUG("hideep_single_touch_switch single_touch_switch = %d\n", info->single_touch_switch);
		switch(info->single_touch_switch){
		case 0:
			TS_LOG_DEBUG("apple weight STOP\n");
			//cancel_work_sync(&g_istxxxx_data->apple_weight_work);
			g_istxxxx_data->apple_weight_init = 0;
			g_istxxxx_data->apple_weight_timeout = 0;
			hideep_item_switch(info->op_action, VR_SINGLE_TOUCH, 1, &info->single_touch_switch);
			break;
		case 1:
			if(!g_istxxxx_data->apple_weight_init){
				TS_LOG_DEBUG("apple weight INIT\n");
				g_istxxxx_data->apple_weight_init = 1;
				g_istxxxx_data->apple_weight_timeout = 0;
				if(g_istxxxx_data->apple_weight_workqueue)
					queue_work(g_istxxxx_data->apple_weight_workqueue, &g_istxxxx_data->apple_weight_work);
			}else{
				TS_LOG_DEBUG("apple weight INIT2\n");
				g_istxxxx_data->apple_weight_timeout = 0;
			}
			hideep_item_switch(info->op_action, VR_SINGLE_TOUCH, 1, &info->single_touch_switch);
			break;
		case 2:
			TS_LOG_DEBUG("apple weight RESET\n");
			g_istxxxx_data->apple_weight_timeout=0;
			break;
		default:
			TS_LOG_ERR("error 0x0818 msg\n");
			break;
		}
	}else if(TS_ACTION_READ == info->op_action){
		TS_LOG_DEBUG("hideep_single_touch_switch read");
		if(g_istxxxx_data->apple_weight_flag){
			TS_LOG_DEBUG("apple weight read %d\n", g_istxxxx_data->apple_weight_buff);
			g_istxxxx_data->apple_weight_flag = false;
			info->single_touch_switch = g_istxxxx_data->apple_weight_buff;
		}else{
			hideep_i2c_read(g_istxxxx_data, IST_APPLE_WEIGHT_VALUE, 2, (u8*)&info->single_touch_switch);
		}
	}
	return ret;
}

static int hideep_glove_switch(struct ts_glove_info *info)
{
	int ret = NO_ERR;

	TS_LOG_INFO("enter, action = %d, switch = %d\n",info->op_action , info->glove_switch);
	if(info->op_action == TS_ACTION_WRITE){
		g_istxxxx_data->glove_mode = info->glove_switch;
		ret = hideep_item_switch(info->op_action, VR_GLOVE,   1, &info->glove_switch);
	}else if(info->op_action == TS_ACTION_READ){
		info->glove_switch = g_istxxxx_data->glove_mode;
		ret = g_istxxxx_data->glove_mode;
	}

	return ret;
}

static int hideep_palm_switch(struct ts_palm_info *info)
{
	return 0;
}


static int hideep_roi_switch(struct ts_roi_info *info)
{
#ifdef ROI
	int ret = 0;
	u8 roi_switch;
	
	TS_LOG_INFO("%s: action = %d swtich = %d\n",__FUNCTION__, info->op_action, info->roi_switch );
	if (!info) {
		TS_LOG_ERR("%s: info is NULL\n",__FUNCTION__);
		ret = -ENOMEM;
		return ret;
	}
	if(!g_istxxxx_data){
		TS_LOG_ERR("%s: g_istxxxx_data is NULL\n",__FUNCTION__);
		ret = -ENOMEM;
		return ret;
	}
	switch (info->op_action) {
	case TS_ACTION_WRITE:
		TS_LOG_INFO("%s: write swtich = %d\n",__FUNCTION__,info->roi_switch );
		g_istxxxx_data->roi.enable = info->roi_switch > 0 ? 1 : 0;
		ret = hideep_i2c_write(g_istxxxx_data, VR_READ_ROI_EN_ADDR, 1, &g_istxxxx_data->roi.enable);
		break;
	case TS_ACTION_READ:
		TS_LOG_INFO("%s: read enable = %d\n",__FUNCTION__,ret = g_istxxxx_data->roi.enable);
		ret = g_istxxxx_data->roi.enable;
		break;
	default:
		TS_LOG_ERR("invalid roi switch(%d) action: %d\n", info->roi_switch, info->op_action);
		break;
	}
	pre_status = 0;
	return ret;
#else
	return -ENOMEM;
#endif
}

static unsigned char* hideep_roi_rawdata(void)
{
#ifdef ROI
	TS_LOG_DEBUG("%s: enter\n",__FUNCTION__);
	if(!g_istxxxx_data){
		TS_LOG_ERR("%s: ts is NULL\n",__FUNCTION__);
		return NULL;
	}
	return &g_istxxxx_data->roi.diff[0];
#else
	return NULL;
#endif
}

static int hideep_wakeup_gesture_enable_switch(struct ts_wakeup_gesture_enable_info *info)
{
	int retval = NO_ERR;

	TS_LOG_INFO("%s, op_action = %d enter\n",__FUNCTION__, info->op_action);
	if (!info) {
		TS_LOG_ERR("%s: info is Null\n", __func__);
		retval = -ENOMEM;
		goto exit;
	}
	if (info->op_action == TS_ACTION_WRITE){
		g_istxxxx_data->gesture_enable = !!(info->switch_value);
		retval = NO_ERR;
	}else {
		TS_LOG_INFO("invalid deep_sleep switch(%d) action: %d\n", info->switch_value, info->op_action);
		retval = NO_ERR;
	}
exit:
	return retval;
}

static int hideep_get_capacitance_test_type(struct ts_test_type_info *info)
{
	int retval = NO_ERR;
	struct ts_device_data *dat = g_istxxxx_data->huawei_ts_data;

	if (!info) {
		TS_LOG_ERR("hideep_get_capacitance_test_type: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}
	switch (info->op_action) {
		case TS_ACTION_READ:
			memcpy(info->tp_test_type, dat->tp_test_type,TS_CAP_TEST_TYPE_LEN);
			TS_LOG_INFO("read_chip_get_test_type=%s, \n",info->tp_test_type);
			break;
		case TS_ACTION_WRITE:
			break;
		default:
			TS_LOG_ERR("invalid status: %s", info->tp_test_type);
			retval = -EINVAL;
			break;
	}
	return retval;
}

struct ts_device_ops ts_hideep_ops =
{
	.chip_parse_config = hideep_parse_config,
	.chip_input_config  = hideep_input_config,
	.chip_detect = hideep_chip_detect ,
	.chip_init = hideep_init,
	.chip_reset = hideep_reset,
	.chip_hw_reset = hideep_reset,
	.chip_shutdown = hideep_shutdown,

	.chip_irq_top_half = hideep_irq_top_half,
	.chip_irq_bottom_half = hideep_irq_bottom_half,
	.chip_suspend = hideep_suspend,
	.chip_before_suspend = hideep_before_suspend,
	.chip_resume = hideep_resume,
	.chip_after_resume = hideep_after_resume,

	.chip_wakeup_gesture_enable_switch = hideep_wakeup_gesture_enable_switch,
	.chip_fw_update_sd = hideep_fw_update_sd,
	.chip_fw_update_boot = hideep_fw_update_boot,
	.chip_get_info = hideep_get_info,
	.chip_get_rawdata = hideep_get_rawdata,
	.chip_get_capacitance_test_type = hideep_get_capacitance_test_type,

	.chip_holster_switch = hideep_holster_switch,
	.chip_glove_switch = hideep_glove_switch,
	.chip_palm_switch = hideep_palm_switch,
	.chip_roi_switch = hideep_roi_switch,
	//.chip_single_touch_switch = hideep_single_touch_switch,
	.chip_roi_rawdata = hideep_roi_rawdata,
}; 

