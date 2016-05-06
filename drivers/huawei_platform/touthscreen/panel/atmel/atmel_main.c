#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <../../huawei_touchscreen_chips.h>
#include <linux/regulator/consumer.h>
#include <linux/hisi/hi6xxx-lcd_type.h>
#include <huawei_platform/log/log_jank.h>
#include "../../huawei_touchscreen_algo.h"
#include "atmel.h"
#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

#if defined (CONFIG_HUAWEI_DSM)
extern bool chip_detfail_dsm;
extern struct dsm_client *tp_dclient;
#endif

static struct mxt_data *mxt_g_data;
static volatile bool mxt_t100_int = true;
extern struct ts_data g_ts_data;
int update_sd_mode = 0;
int featurefile_read_success = 0;
#define T38COVERCUT 58
#define T38COVERSUPWIDL 59
#define T38COVERSUPWIDH 60
#define T38COVERGLASSFL 61
#define T38GLOVESUPWIDL 62
#define T38GLOVESUPWIDH 63

#ifdef ROI
int gMxtT6Cmd58Flag = MXT_T6_CMD58_ON;
#endif

#define T100_PROC_FINGER_NUM
#define AVDD_LDO_VALUE (3300000)
#define VDDIO_LDO_VALUE (1850000)

static void mxt_parse_module_dts(struct ts_device_data *chip_data);
static int atmel_chip_detect(struct device_node *device, struct ts_device_data *chip_data, struct platform_device *ts_dev);
static int atmel_init_chip(void);
static int atmel_parse_dts(struct device_node *device, struct ts_device_data *chip_data);
static int atmel_irq_top_half(struct ts_cmd_node *cmd);
static int atmel_irq_bottom_half(struct ts_cmd_node *in_cmd, struct ts_cmd_node *out_cmd);
static int atmel_fw_update_boot(char *file_name);
static int atmel_fw_update_sd(void);
static int atmel_chip_get_info(struct ts_chip_info_param *info);
static int atmel_before_suspend(void);
static int atmel_suspend(void);
static int atmel_resume(void);
static int atmel_after_resume(void *feature_info);
static void atmel_shutdown(void);
static int atmel_input_config(struct input_dev *input_dev);
static int atmel_get_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd);
static unsigned char* atmel_roi_rawdata(void);
static int atmel_chip_get_capacitance_test_type(struct ts_test_type_info *info);
static int atmel_charger_switch(struct ts_charger_info *info);
static int atmel_chip_glove_switch(struct ts_glove_info *info);
static int atmel_chip_holster_switch(struct ts_holster_info *info);

static int atmel_roi_switch(struct ts_roi_info *info);
static int mxt_set_feature(struct mxt_data *data, int featurecode , int enableflag);
static int mxt_enable_feature(struct mxt_data *data, int featurecode);
static int mxt_disable_feature(struct mxt_data *data, int featurecode);
static int atmel_init_feature_file(bool from_sd);
static int atmel_regs_operate(struct ts_regs_info *info);
static int atmel_debug_switch(u8 loglevel);
static void mxt_disable_all_features();
static int mxt_initialize_info_block(struct mxt_data *data);

static void atmel_special_hardware_test_switch(unsigned int value);
static int atmel_special_hardware_test_result(char *buf);

//WORKAROUND1 finger down workaround
//WORKAROUND2 glove down workaround
//WORKAROUND3 for T72 noise level check feature
//WORKAROUND4 VN-N workaround
//WORKAROUND5 for charger workaround
static struct feature_info mxt_feature_list[] = {{"GLOVE" , MAX_GLOVE_CONF , 0 , MXT_FEATURE_DISABLE , 0},
													{"COVER" , MAX_COVER_CONF , 0 , MXT_FEATURE_DISABLE, 0},
													{"WAKEUP" , MAX_WAKEUP_CONF , 0 , MXT_FEATURE_DISABLE , 0},
													{"GUESTURE" , MAX_GUESTURE_CONF , 0 ,MXT_FEATURE_DISABLE, 0},
													{"KNUCKLE" , MAX_KNUCKLE_CONF , 0 ,MXT_FEATURE_DISABLE, 0},
													{"WORKAROUND1" , MAX_WORKAROUND1_CONF , 0 ,MXT_FEATURE_DISABLE, 0},
													{"WORKAROUND2" , MAX_WORKAROUND2_CONF , 0 ,MXT_FEATURE_DISABLE, 0},
													{"WORKAROUND3" , MAX_WORKAROUND3_CONF , 0 ,MXT_FEATURE_DISABLE, 0},
													{"WORKAROUND4" , MAX_WORKAROUND4_CONF , 0 ,MXT_FEATURE_DISABLE, 0},
													{"WORKAROUND5" , MAX_WORKAROUND5_CONF , 0 ,MXT_FEATURE_DISABLE, 0},
													{"WORKAROUND6" , MAX_WORKAROUND6_CONF , 0 ,MXT_FEATURE_DISABLE, 0}};


struct ts_device_ops ts_atmel_ops = {
	.chip_detect = atmel_chip_detect,
	.chip_init = atmel_init_chip,
	.chip_parse_config = atmel_parse_dts,
	.chip_input_config = atmel_input_config,
	.chip_irq_top_half = atmel_irq_top_half,
	.chip_irq_bottom_half = atmel_irq_bottom_half,
	.chip_fw_update_boot = atmel_fw_update_boot,
	.chip_fw_update_sd = atmel_fw_update_sd,
	.chip_get_info = atmel_chip_get_info,
	.chip_before_suspend = atmel_before_suspend,
	.chip_suspend = atmel_suspend,
	.chip_resume = atmel_resume,
	.chip_after_resume = atmel_after_resume,
	.chip_get_rawdata = atmel_get_rawdata,
	.chip_roi_rawdata = atmel_roi_rawdata,
	.chip_roi_switch = atmel_roi_switch,
	.chip_shutdown = atmel_shutdown,
	.chip_get_capacitance_test_type = atmel_chip_get_capacitance_test_type,
	.chip_glove_switch = atmel_chip_glove_switch,
	.chip_holster_switch = atmel_chip_holster_switch,
	.chip_regs_operate = atmel_regs_operate,
	.chip_debug_switch = atmel_debug_switch,
	.chip_charger_switch = atmel_charger_switch,
	.chip_special_hardware_test_swtich = atmel_special_hardware_test_switch,
	.chip_special_hardware_test_result = atmel_special_hardware_test_result,
};

#if defined (CONFIG_TEE_TUI)
static struct tui_mxt_data_t {
	char device_name[10];
	u8 max_reportid;
	u16 T5_address;
	u8 T5_msg_size;
	u16 T44_address;
	u16 T100_address;
	u8 T100_reportid_min;
	u8 T100_reportid_max;
	u16 addr;
} tui_mxt_data;
#endif
static int __mxt_cache_write(struct ts_device_data *chip_data, u16 addr,
				u16 reg, u16 len, const void *val, u8 *w_cache, u8 *w_cache_pa, unsigned long flag)
{
	struct i2c_msg xfer;
	void *buf = NULL;
	u16 transferred,extend;
	int retry = 3;
	int ret;

	if (test_flag(I2C_ACCESS_NO_REG,&flag)) {
		extend = 0;
		if (test_flag(I2C_ACCESS_NO_CACHE,&flag))
			w_cache = w_cache_pa = (u8 *)val;
	}else {
		extend = 2;
		if (test_flag(I2C_ACCESS_NO_CACHE,&flag)) {
			buf = kmalloc( len + extend, GFP_KERNEL);
			if (!buf)
				return -ENOMEM;
			w_cache = w_cache_pa = buf;
		}

		w_cache[0] = reg & 0xff;
		w_cache[1] = (reg >> 8) & 0xff;
	}

	/* Write register */
	xfer.addr = addr;
	xfer.flags = 0;
	xfer.buf = w_cache_pa;

	transferred = 0;
	while(transferred < len) {
		xfer.len = len - transferred+ extend;
		if (xfer.len> MXT_MAX_BLOCK_WRITE)
			xfer.len = MXT_MAX_BLOCK_WRITE;
	
		if (test_flag(I2C_ACCESS_NO_CACHE,&flag) &&
			test_flag(I2C_ACCESS_NO_REG,&flag))
			xfer.buf = w_cache_pa + transferred;
		else
			memcpy(w_cache + extend, val + transferred, xfer.len - extend);

		if (extend) {
			w_cache[0] = (reg +  transferred) & 0xff;
			w_cache[1] = ((reg + transferred) >> 8) & 0xff;
		}

	retry_write:
		//ret = chip_data->bops->bus_xfer(&xfer, 1) ;
		ret = i2c_transfer(g_ts_data.client->adapter, &xfer, 1);
		if (ret != 1) {
			if (retry) {
				TS_LOG_INFO("%s: i2c transfer(w) retry, reg %d\n", __func__, reg);
				msleep(25);
				retry--;
				goto retry_write;
			} else {
				TS_LOG_ERR("%s: i2c transfer(w) failed (%d) reg %d len %d transferred %d\n",
					__func__, ret, reg, len, transferred);
				if (buf)
					kfree(buf);
			#if defined (CONFIG_HUAWEI_DSM)
				if(!chip_detfail_dsm ) {
					TS_LOG_ERR("chip write init no need dsm \n");
					return -EIO;
				}
				if(!dsm_client_ocuppy(tp_dclient)){
					dsm_client_record(tp_dclient, "irq_gpio:%d\tvalue:%d.\nreset_gpio:%d\t value:%d.\nI2C_status:%d.\n",\
						g_ts_data.chip_data->irq_gpio,\
						gpio_get_value(g_ts_data.chip_data->irq_gpio),\
						g_ts_data.chip_data->reset_gpio,\
						gpio_get_value(g_ts_data.chip_data->reset_gpio),\
						 g_ts_data.dsm_info.constraints_I2C_status);
					dsm_client_notify(tp_dclient, DSM_TP_I2C_RW_ERROR_NO);
				}
			#endif
				return -EIO;
			}
		}

		transferred += xfer.len -extend;

		TS_LOG_DEBUG("[mxt] i2c transfer(w) reg %d len %d current %d transferred %d\n",
			reg, len, xfer.len -extend, transferred);
	}

	if (buf)
		kfree(buf);
	return 0;
}

static int __mxt_cache_read(struct ts_device_data *chip_data, u16 addr, 
				u16 reg, u16 len, void *val, u8 *r_cache, u8 *r_cache_pa, u8 *w_cache, u8 *w_cache_pa, unsigned long flag)
{
	struct i2c_msg *msgs;
	int num;

	struct i2c_msg xfer[2];
	char buf[2];
	u16 transferred;
	int retry = 3;
	int ret;

	TS_LOG_DEBUG("__mxt_cache_read\n");

	if (test_flag(I2C_ACCESS_NO_CACHE,&flag)) {
		w_cache = w_cache_pa = buf;
		r_cache = r_cache_pa = val;
	}

	if (test_flag(I2C_ACCESS_NO_REG,&flag)) {
		msgs = &xfer[1];
		num = 1;
	}else{
		w_cache[0] = reg & 0xff;
		w_cache[1] = (reg >> 8) & 0xff;

		msgs = &xfer[0];
		num = ARRAY_SIZE(xfer);

		/* Write register */
		xfer[0].addr = addr;
		xfer[0].flags = 0;
		xfer[0].len = 2;
		xfer[0].buf = w_cache_pa;
	}

	/* Read data */
	xfer[1].addr = addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].buf = r_cache_pa;

	transferred = 0;
	while(transferred < len) {
		if (!test_flag(I2C_ACCESS_NO_REG | I2C_ACCESS_R_REG_FIXED,&flag)) {
			w_cache[0] = (reg +  transferred) & 0xff;
			w_cache[1] = ((reg + transferred) >> 8) & 0xff;
		}

		if (test_flag(I2C_ACCESS_NO_CACHE,&flag))
			xfer[1].buf = r_cache_pa + transferred;
		xfer[1].len = len - transferred;
		if (xfer[1].len > MXT_MAX_BLOCK_READ)
			xfer[1].len = MXT_MAX_BLOCK_READ;
	retry_read:
		//ret = chip_data->bops->bus_xfer(msgs, num) ;
		ret = i2c_transfer(g_ts_data.client->adapter, msgs, num);
		if (ret != num) {
			if (retry) {
				TS_LOG_DEBUG("%s: i2c transfer(r) retry, reg %d\n", __func__, reg);
				msleep(25);
				retry--;
				goto retry_read;
			} else {
				TS_LOG_ERR("%s: i2c transfer(r) failed (%d) reg %d len %d transferred %d\n", __func__, ret, reg, len, transferred);
			#if defined (CONFIG_HUAWEI_DSM)
				if(!chip_detfail_dsm ) {
					TS_LOG_ERR("chip write init no need dsm \n");
					return -EIO;
				}
				if(!dsm_client_ocuppy(tp_dclient)){
					dsm_client_record(tp_dclient, "irq_gpio:%d\tvalue:%d.\nreset_gpio:%d\t value:%d.\nI2C_status:%d.\n",\
						g_ts_data.chip_data->irq_gpio,\
						gpio_get_value(g_ts_data.chip_data->irq_gpio),\
						g_ts_data.chip_data->reset_gpio,\
						gpio_get_value(g_ts_data.chip_data->reset_gpio),\
						 g_ts_data.dsm_info.constraints_I2C_status);
					dsm_client_notify(tp_dclient, DSM_TP_I2C_RW_ERROR_NO);
				}
			#endif
				return -EIO;
			}
		}
		if (!test_flag(I2C_ACCESS_NO_CACHE,&flag))
			memcpy(val + transferred, r_cache, xfer[1].len);
		transferred += xfer[1].len;

		TS_LOG_DEBUG("[mxt] i2c transfer(r) reg %d len %d current %d transferred %d\n",
			reg, len, xfer[1].len, transferred);
	}
	return 0;
}

static int __mxt_read_reg_ext(struct mxt_data *data, u16 addr, u16 reg, u16 len,
				void *val, unsigned long flag)
{
	u8 *r_cache,*r_cache_pa,*w_cache,*w_cache_pa;
	int ret;

	r_cache_pa = r_cache = NULL;
	w_cache_pa = w_cache = NULL;

	flag |= I2C_ACCESS_NO_CACHE;

	mutex_lock(&data->bus_access_mutex);
	ret = __mxt_cache_read(data->chip_data, addr, reg, len, val, r_cache, r_cache_pa, w_cache, w_cache_pa, flag);
	mutex_unlock(&data->bus_access_mutex);

	return ret;
}

static int __mxt_write_reg_ext(struct mxt_data *data, u16 addr, u16 reg, u16 len,
				const void *val, unsigned long flag)
{
	u8 *w_cache,*w_cache_pa;
	int ret;

	w_cache_pa = w_cache = NULL;

	flag |= I2C_ACCESS_NO_CACHE;

	mutex_lock(&data->bus_access_mutex);
	ret = __mxt_cache_write(data->chip_data, addr, reg, len, val, w_cache, w_cache_pa, flag);
	mutex_unlock(&data->bus_access_mutex);

	return ret;
}

int __mxt_read_reg(struct mxt_data *data, u16 reg, u16 len,
				void *val)
{
	return __mxt_read_reg_ext(data, data->addr, reg, len, val, 0);
}

int __mxt_write_reg(struct mxt_data *data, u16 reg, u16 len,
				const void *val)
{
	return __mxt_write_reg_ext(data, data->addr, reg, len, val, 0);
}

int mxt_write_reg(struct mxt_data *data, u16 reg, u8 val)
{
	return __mxt_write_reg(data, reg, 1, &val);
}

static void mxt_regulator_set(struct mxt_data *data)
{
	int error = 0;

	error = regulator_set_voltage(data->reg_avdd, AVDD_LDO_VALUE, AVDD_LDO_VALUE);
	if (error < 0) {
		TS_LOG_ERR("failed to set voltage regulator tp_vci error: %d\n", error);
		return;
	}

	error = regulator_set_voltage(data->reg_vddio, VDDIO_LDO_VALUE, VDDIO_LDO_VALUE);
	if (error < 0) {
		TS_LOG_ERR("failed to set voltage regulator tp_vddio error: %d\n", error);
		return;
	}

	return;
}

static void mxt_regulator_enable(struct mxt_data *data)
{
	int error = 0;

	if (!data->chip_data->reset_gpio) {
		TS_LOG_ERR("Must have reset GPIO to use regulator support\n");
		return;
	}
	//gpio_direction_output(data->chip_data->reset_gpio, 0);

	regulator_enable(data->reg_vddio);
	mdelay(1);
	regulator_enable(data->reg_avdd);
	mdelay(10);

	error = pinctrl_select_state(data->pctrl, data->pins_default);
	if (error < 0) {
		TS_LOG_ERR("set iomux normal error, %d\n", error);
	}
	gpio_direction_output(data->chip_data->reset_gpio, 1);
	gpio_direction_input(data->chip_data->irq_gpio);
	return;
}

static int mxt_regulator_get(struct mxt_data *data)
{
	int error = 0;

	data->reg_vddio = regulator_get(&data->ts_dev->dev, "atmel-vddio");	//1.8V
	if (IS_ERR(data->reg_vddio)) {
		error = PTR_ERR(data->reg_vddio);
		TS_LOG_ERR("Error %d getting atmel-vdd regulator\n", error);
		goto fail;
	}

	data->reg_avdd = regulator_get(&data->ts_dev->dev, "atmel-avdd");	//3.1V
	if (IS_ERR(data->reg_avdd)) {
		error = PTR_ERR(data->reg_avdd);
		TS_LOG_ERR("Error %d getting atmel-avdd regulator\n", error);
		goto fail;
	}

	return 0;

fail:
	if (data->reg_vddio) {
		regulator_put(data->reg_vddio);
		data->reg_vddio = NULL;
	}
	if (data->reg_avdd) {
		regulator_put(data->reg_avdd);
		data->reg_avdd = NULL;
	}

	return -1;
}

static int mxt_gpio_get(struct mxt_data *data)
{
	int error = 0;

	error = gpio_request(data->chip_data->reset_gpio, "ts_reset_gpio");
	if (error < 0) {
		TS_LOG_ERR("Fail request gpio:%d\n", data->chip_data->reset_gpio);
		return -1;
	}

	error = gpio_request(data->chip_data->irq_gpio, "ts_irq_gpio");
	if (error) {
		TS_LOG_ERR("unable to request gpio:%d\n", data->chip_data->irq_gpio);
		return -1;
	}

	return 0;
}

static int mxt_pinctl_get(struct mxt_data *data)
{
	int error = 0;

	data->pctrl = devm_pinctrl_get(&data->ts_dev->dev);
	if (IS_ERR(data->pctrl)) {
		TS_LOG_ERR("failed to devm pinctrl get\n");
		error = -EINVAL;
		goto err;
	}

	data->pins_default = pinctrl_lookup_state(data->pctrl, "default");
	if (IS_ERR(data->pins_default)) {
		TS_LOG_ERR("failed to pinctrl lookup state default\n");
		error = -EINVAL;
		goto err;
	}

	data->pins_idle = pinctrl_lookup_state(data->pctrl, "idle");
	if (IS_ERR(data->pins_idle)) {
		TS_LOG_ERR("failed to pinctrl lookup state idle\n");
		error = -EINVAL;
		goto err;
	}

	return 0;

err:
	if (data->pctrl) {
		devm_pinctrl_put(data->pctrl);
		data->pctrl = NULL;
	}
	return error;
}

static int mxt_probe_regulators(struct mxt_data *data)
{
	int error;

	TS_LOG_DEBUG("mxt_probe_regulators\n");

	/* According to maXTouch power sequencing specification, RESET line
	 * must be kept low until some time after regulators come up to
	 * voltage */
	error = mxt_regulator_get(data);
	if (error < 0){
		TS_LOG_ERR("%s,failed to get regulator of avdd and vddio\n", __func__);
		return error;
	}

	error = mxt_gpio_get(data);
	if (error < 0){
		TS_LOG_ERR("%s,failed to request gpio for irq and rst\n", __func__);
		return error;
	}

	error = mxt_pinctl_get(data);
	if (error < 0){
		TS_LOG_ERR("%s,failed to set pinctl\n", __func__);
		return error;
	}

	mxt_regulator_set(data);

	mxt_regulator_enable(data);	//regulator enable

	TS_LOG_INFO("Initialised regulators\n");
	return 0;
}

int mxt_probe_info_block(struct mxt_data *data)
{
	u8 val;

	return __mxt_read_reg(data, 0, 1, &val);
}

int mxt_bootloader_read(struct mxt_data *data, u8 *val, unsigned int count)
{
	return __mxt_read_reg_ext(data, data->bootloader_addr, 0, count, val, I2C_ACCESS_NO_REG);
}

int mxt_bootloader_write(struct mxt_data *data, const u8 * const val,
	unsigned int count)
{
	return __mxt_write_reg_ext(data, data->bootloader_addr, 0, count, val, I2C_ACCESS_NO_REG);
}
/*
 *Function for getting bootloader address
 *
 *Bootloader mode is the mode under which FW updating happens.
 *The address for bootloader is different for different mxt devices.
 *
 */
int mxt_lookup_bootloader_address(struct mxt_data *data, bool retry)
{
	u8 appmode = data->addr & 0x7F;
	u8 bootloader;
	u8 family_id = 0;

	if (data->info)
		family_id = data->info->family_id;

	switch (appmode) {
	case 0x4a:
	case 0x4b:
		/* Chips after 1664S use different scheme */
		if (retry || family_id >= 0xa2) {
			bootloader = appmode - 0x24;
			break;
		}
		/* Fall through for normal case */
	case 0x4c:
	case 0x4d:
	case 0x5a:
	case 0x5b:
		bootloader = appmode - 0x26;
		break;
	default:
		TS_LOG_ERR("Appmode i2c address 0x%02x not found\n", appmode);
		return -EINVAL;
	}

	data->bootloader_addr = bootloader;

	TS_LOG_INFO("Appmode i2c address 0x%02x, bootloader 0x%02x\n",appmode,bootloader);

	return 0;
}

/*
 *Function for detecting if the device is under bootloader mode
 *
 *Bootloader mode is the mode under which FW updating happens.
 *
 */
static int mxt_probe_bootloader(struct mxt_data *data, bool retry)
{
	int ret;
	u8 val;
	bool crc_failure;

	ret = mxt_lookup_bootloader_address(data, retry);
	if (ret) {
		TS_LOG_ERR("%s, lookup_bootloader_address fail",__func__);
		return ret;
	}
	ret = mxt_bootloader_read(data, &val, 1);
	if (ret) {
		TS_LOG_ERR("%s,  mxt_bootloader_read failed",__func__);
		return ret;
	}

	/* Check app crc fail mode */
	crc_failure = (val & ~MXT_BOOT_STATUS_MASK) == MXT_APP_CRC_FAIL;

	TS_LOG_ERR("Detected bootloader, status:%02X%s\n",
			val, crc_failure ? ", APP_CRC_FAIL" : "");

	return 0;
}
/*
 *Function for unlocking bootloader mode.
 *
 *Bootloader mode is the mode under which FW updating happens.
 *
 */
int mxt_send_bootloader_cmd(struct mxt_data *data, bool unlock)
{
	int ret;
	u8 buf[2];

	if (unlock) {
		buf[0] = MXT_UNLOCK_CMD_LSB;
		buf[1] = MXT_UNLOCK_CMD_MSB;
	} else {
		buf[0] = 0x01;
		buf[1] = 0x01;
	}

	ret = mxt_bootloader_write(data, buf, 2);
	if (ret){
		TS_LOG_ERR("%s,failed to write under bootloader mode\n", __func__);
		return ret;
	}

	return 0;
}
/*
 *Function for initializing information table.
 *
 *Information table holds the overall constructure of mxt device objects.
 *
 */
static int mxt_pre_initialize(struct mxt_data *data)
{
	int error = NO_ERR;
	bool alt_bootloader_addr = false;
	bool retry = false;

retry_info:
	error = mxt_probe_info_block(data);
	if (error) {
retry_bootloader:
		error = mxt_probe_bootloader(data, alt_bootloader_addr);
		if (error) {
			if (alt_bootloader_addr) {
				/* Chip is not in appmode or bootloader mode */
				TS_LOG_ERR("%s,failed to probe bootloader,alt_bootloader_addr = %d\n",
								__func__, alt_bootloader_addr);
				return error;
			}

			TS_LOG_INFO("%s,Trying alternate bootloader address\n", __func__);
			alt_bootloader_addr = true;
			goto retry_bootloader;
		} else {
			if (retry) {
				TS_LOG_INFO("Could not recover device from "
						"bootloader mode\n");
				/* this is not an error state, we can reflash
				 * from here */
				return 0;
			}

			/* Attempt to exit bootloader into app mode */
			mxt_send_bootloader_cmd(data, false);
			msleep(250);
			retry = true;
			goto retry_info;
		}
	}

	return error;
}

static void mxt_regulator_disable(struct mxt_data *data)
{
	if (!data->chip_data->reset_gpio)
		return;

	gpio_direction_output(data->chip_data->reset_gpio, 0);
	mdelay(2);

	if (data->reg_avdd)
		regulator_disable(data->reg_avdd);
	mdelay(1);
	if (data->reg_vddio)
		regulator_disable(data->reg_vddio);

	return;
}

static void mxt_free_regulators(struct mxt_data *data)
{
	mxt_regulator_disable(data);

	if (data->reg_vddio) {
		regulator_put(data->reg_vddio);
		data->reg_vddio = NULL;
	}
	if (data->reg_avdd) {
		regulator_put(data->reg_avdd);
		data->reg_avdd = NULL;
	}
}
static int atmel_chip_detect(struct device_node *device,
		struct ts_device_data *chip_data, struct platform_device *ts_dev)
{
	struct mxt_data *data;
	int error;

	TS_LOG_INFO("atmel chip detect called\n");

	if (!device || !chip_data || !ts_dev) {
		TS_LOG_ERR("device, chip_data or ts_dev is NULL \n");
		return -ENOMEM;
	}

	data = kzalloc(sizeof(struct mxt_data), GFP_KERNEL);
	if (!data) {
		TS_LOG_ERR("Failed to allocate memory\n");
		return -ENOMEM;
	}

	data->chip_data = chip_data;
	data->ts_dev = ts_dev;
	data->ts_dev->dev.of_node = device;

	data->chip_data->is_in_cell = true;
	//data->chip_data->rs_info.sleep_mode = TS_POWER_OFF_MODE;
	//data->chip_data->rs_info.rs_flag = true;
	//data->chip_data->rs_info.gesture_palm_set_flag = false;

	data->addr = g_ts_data.client->addr;
	TS_LOG_INFO("client addr is 0x%x\n", data->addr);
	chip_data->prv_data = (void *)data;
	init_completion(&data->reset_completion);
	mutex_init(&data->bus_access_mutex);
	mutex_init(&data->access_mutex);
	mutex_init(&data->debug_msg_lock);
	data->use_regulator = true;
	data->in_bootloader = false;
	error = mxt_probe_regulators(data);
	if (error) {
		TS_LOG_ERR("mxt_probe_regulators failed\n");
		goto err_free_object;
	}

	mdelay(100);		//after hw reset, need 88ms.
	error = mxt_pre_initialize(data);
	if (error) {
		TS_LOG_ERR("Failed pre initialize chip\n");
		goto err_free_object;
	}

	mxt_g_data = data;

	error = mxt_mem_access_init(data);
	if (error){
		TS_LOG_ERR("%s,access init failed\n", __func__);
		goto err_free_object;
	}

	return NO_ERR;

err_free_object:
	if (data) {
		mxt_free_regulators(data);
		mutex_destroy(&data->bus_access_mutex);
		mutex_destroy(&data->debug_msg_lock);
		mutex_destroy(&data->access_mutex);
		kfree(data);
		data = NULL;
	}

	return error;
}

void mxt_free_input_device(struct mxt_data *data)
{
	mxt_debug_msg_remove(data);
}

void mxt_free_object_table(struct mxt_data *data)
{
	//mxt_debug_msg_remove(data);
	if (NULL != data->raw_info_block) {
		kfree(data->raw_info_block);
	}
	data->object_table = NULL;
	data->info = NULL;
	data->raw_info_block = NULL;
	if (NULL != data->msg_buf) {
		kfree(data->msg_buf);
	}
	data->msg_buf = NULL;

	mxt_free_input_device(data);

	data->enable_reporting = false;
	data->T5_address = 0;
	data->T5_msg_size = 0;
	data->T6_reportid = 0;
	data->T7_address = 0;
	data->T8_address = 0;
	data->T9_address = 0;
	data->T9_reportid_min = 0;
	data->T9_reportid_max = 0;
	data->T15_address = 0;
	data->T15_reportid_min = 0;
	data->T15_reportid_max = 0;
	data->T18_address = 0;
	data->T19_address = 0;
	data->T19_reportid = 0;
	data->T24_address = 0;
	data->T24_reportid = 0;
	data->T25_address = 0;
	data->T25_reportid = 0;
	data->T37_address = 0;
	data->T38_address = 0;
	data->T40_address = 0;
	data->T42_address = 0;
	data->T42_reportid_min = 0;
	data->T42_reportid_max = 0;
	data->T44_address = 0;
	data->T46_address = 0;
	data->T47_address = 0;
	data->T48_reportid = 0;
	data->T55_address = 0;
	data->T56_address = 0;
	data->T61_address = 0;
	data->T61_reportid_min = 0;
	data->T61_reportid_max = 0;
	data->T61_instances = 0;
	data->T63_reportid_min = 0;
	data->T63_reportid_max = 0;
	data->T65_address = 0;
	data->T68_address = 0;
	data->T71_address = 0;
	data->T72_address = 0;
	data->T72_reportid_min = 0;
	data->T72_reportid_max = 0;
	data->T78_address = 0;
	data->T80_address = 0;
	data->T81_address = 0;
	data->T81_reportid_min= 0;
	data->T81_reportid_max= 0;
	data->T92_address = 0;
	data->T92_reportid = 0;
	data->T93_address = 0;
	data->T93_reportid = 0;
	data->T96_address = 0;
	data->T97_address = 0;
	data->T97_reportid_min = 0;
	data->T97_reportid_max = 0;
	data->T99_address = 0;
	data->T99_reportid = 0;
	data->T100_address = 0;
	data->T100_reportid_min = 0;
	data->T100_reportid_max = 0;
	data->T102_address = 0;
	data->T102_reportid = 0;
	data->T104_address = 0;
	data->T113_address = 0;
	data->T115_address = 0;
	data->T115_reportid = 0;
	data->T125_reportid=0;
	data->max_reportid = 0;
}

static inline int mxt_obj_instances(const struct mxt_object *obj)
{
	return obj->instances_minus_one + 1;
}

static inline int mxt_obj_size(const struct mxt_object *obj)
{
	return obj->size_minus_one + 1;
}

/*
 *Function for reading object instance
 *
 *Object is the function unit of maxTouch devices. One object might have many instances.
 *
 */
static int mxt_read_obj_instance(struct mxt_data *data, u8 type, u8 instance,
		u8 offset, u8 *val)
{
	struct mxt_object *object;
	u16 reg;

	object = mxt_get_object(data, type);
	if (!object) {
		TS_LOG_ERR("%s:object=%ld\n",__func__,PTR_ERR(object));
		goto out;
	}

	if (offset >= mxt_obj_size(object) || instance >= mxt_obj_instances(object)) {
	    TS_LOG_ERR("%s, offset: %d, object size: %d, instance: %d, obj instance: %d\n", __func__, offset, mxt_obj_size(object), instance, mxt_obj_instances(object));
		goto out;
	}

	reg = object->start_address + instance * mxt_obj_size(object) + offset;
	return __mxt_read_reg(data, reg, 1, val);

out:
	return -EINVAL;
}

static int mxt_read_object(struct mxt_data *data, u8 type, u8 offset, u8 *val)
{
	return mxt_read_obj_instance(data, type, 0, offset, val);
}

/*
 *Function for write object instance
 *
 *Object is the function unit of maxTouch devices. One object might have many instances.
 *
 */
static int mxt_write_obj_instance(struct mxt_data *data, u8 type, u8 instance,
		u8 offset, u8 val)
{
	struct mxt_object *object;
	u16 reg;

	object = mxt_get_object(data, type);
	if (!object || offset >= mxt_obj_size(object) ||
	    instance >= mxt_obj_instances(object)) {
		TS_LOG_ERR("offset=%d mxt_obj_size(object)=%d instance=%d mxt_obj_instances(object)=%d\n",
		offset,mxt_obj_size(object),instance,mxt_obj_instances(object));
		return -EINVAL;
	}

	reg = object->start_address + instance * mxt_obj_size(object) + offset;
	return __mxt_write_reg(data, reg, 1, &val);
}

static int mxt_write_object(struct mxt_data *data, u8 type, u8 offset, u8 val)
{
	return mxt_write_obj_instance(data, type, 0, offset, val);
}

#if defined (CONFIG_TEE_TUI)
static void mxt_get_tui_data(struct mxt_data *data)
{
	if (data->chip_data) {
		tui_mxt_data.max_reportid = data->max_reportid;
		tui_mxt_data.T100_address = data->T100_address;
		tui_mxt_data.T100_reportid_max = data->T100_reportid_max;
		tui_mxt_data.T100_reportid_min = data->T100_reportid_min;
		tui_mxt_data.T44_address = data->T44_address;
		tui_mxt_data.T5_address = data->T5_address;
		tui_mxt_data.T5_msg_size = data->T5_msg_size;
		tui_mxt_data.addr = data->addr;
		strncpy(tui_mxt_data.device_name, "atmel", strlen("atmel"));
		tui_mxt_data.device_name[strlen("atmel")+1]='\0';

		data->chip_data->tui_data = &tui_mxt_data;
	}
    TS_LOG_INFO("max_reportid:0x%x,T100_address:0x%x,T100_reportid_max:0x%x,T100_reportid_min:0x%x,T44_address:0x%x,T5_address:0x%x,T5_msg_size:0x%x,addr:0x%x,name:%s\n",
            tui_mxt_data.max_reportid,tui_mxt_data.T100_address,tui_mxt_data.T100_reportid_max,tui_mxt_data.T100_reportid_min,tui_mxt_data.T44_address,tui_mxt_data.T5_address,tui_mxt_data.T5_msg_size,tui_mxt_data.addr,tui_mxt_data.device_name);
}
#endif

/*
 *Function for saving the object information to the mxt-data
 *
 *object information includes the report id ranges and object address.
 *
 */
static int mxt_parse_object_table(struct mxt_data *data, struct mxt_object *object_table)
{
	int i;
	u8 reportid;
	u16 end_address;

	/* Valid Report IDs start counting from 1 */
	reportid = 1;
	data->mem_size = 0;
	for (i = 0; i < data->info->object_num; i++) {
		struct mxt_object *object = object_table + i;
		u8 min_id, max_id;

		le16_to_cpus(&object->start_address);

		if (object->num_report_ids) {
			min_id = reportid;
			reportid += object->num_report_ids *
					mxt_obj_instances(object);
			max_id = reportid - 1;
		} else {
			min_id = 0;
			max_id = 0;
		}

		TS_LOG_DEBUG(
			"T%u Start:%u Size:%u Instances:%u Report IDs:%u-%u\n",
			object->type, object->start_address,
			mxt_obj_size(object), mxt_obj_instances(object),
			min_id, max_id);

		switch (object->type) {
		case MXT_GEN_MESSAGEPROCESSOR_T5:
			if (data->info->family_id == 0x80) {
				/* On mXT224 read and discard unused CRC byte
				 * otherwise DMA reads are misaligned */
				data->T5_msg_size = mxt_obj_size(object);
			} else {
				/* CRC not enabled, so skip last byte */
				data->T5_msg_size = mxt_obj_size(object) - 1;
			}
			data->T5_address = object->start_address;
		case MXT_GEN_COMMANDPROCESSOR_T6:
			data->T6_reportid = min_id;
			data->T6_address = object->start_address;
			break;
		case MXT_GEN_POWERCONFIG_T7:
			data->T7_address = object->start_address;
			break;
		case MXT_GEN_ACQUISITIONCONFIG_T8:
			data->T8_address = object->start_address;
			break;
		case MXT_TOUCH_MULTITOUCHSCREEN_T9:
			/* Only handle messages from first T9 instance */
			data->T9_reportid_min = min_id;
			data->T9_reportid_max = min_id +
						object->num_report_ids - 1;
			data->T9_address = object->start_address;
			data->num_touchids = object->num_report_ids;
			break;
		case MXT_TOUCH_KEYARRAY_T15:
			data->T15_reportid_min = min_id;
			data->T15_reportid_max = max_id;
			data->T15_address = object->start_address;
			break;
		case MXT_SPT_COMCONFIG_T18:
			data->T18_address = object->start_address;
			break;
		case MXT_SPT_GPIOPWM_T19:
			data->T19_address = object->start_address;
			data->T19_reportid = min_id;
			break;			
		case MXT_PROCI_ONETOUCHGESTUREPROCESSOR_T24:
			data->T24_address = object->start_address;
			data->T24_reportid = min_id;
			break;			
		case MXT_SPT_SELFTEST_T25:
			data->T25_address = object->start_address;
			data->T25_reportid = min_id;
			break;
		case MXT_DEBUG_DIAGNOSTIC_T37:
			data->T37_address = object->start_address;
			break;	
		case MXT_SPT_USERDATA_T38:
			data->T38_address = object->start_address;
			break;			
		case MXT_PROCI_GRIPSUPPRESSION_T40:
			data->T40_address = object->start_address;
			break;
		case MXT_PROCI_TOUCHSUPPRESSION_T42:
			data->T42_address = object->start_address;
			data->T42_reportid_min = min_id;
			data->T42_reportid_max = max_id;
			break;
		case MXT_SPARE_T44:
			data->T44_address = object->start_address;
			break;
		case MXT_SPT_CTECONFIG_T46:
			data->T46_address = object->start_address;
			break;
		case MXT_PROCI_STYLUS_T47:
			data->T47_address = object->start_address;
			break;
		case MXT_PROCG_NOISESUPPRESSION_T48:
			data->T48_reportid = min_id;
			break;
		case MXT_ADAPTIVE_T55:
			data->T55_address = object->start_address;
			break;			
		case MXT_PROCI_SHIELDLESS_T56:
			data->T56_address = object->start_address;
			break;
		case MXT_SPT_TIMER_T61:
			/* Only handle messages from first T63 instance */
			data->T61_address = object->start_address;
			data->T61_reportid_min = min_id;
			data->T61_reportid_max = max_id;
			data->T61_instances = mxt_obj_instances(object);
			break;
		case MXT_PROCI_ACTIVESTYLUS_T63:
			/* Only handle messages from first T63 instance */
			data->T63_reportid_min = min_id;
			data->T63_reportid_max = min_id;
			data->num_stylusids = 1;
			break;
		case MXT_PROCI_LENSBENDING_T65:
			data->T65_address = object->start_address;
			break;
		case MXT_SPARE_T68:
			data->T68_address = object->start_address;
			data->T68_reportid_min = min_id;
			data->T68_reportid_max = max_id;
			break;
		case MXT_SPT_DYNAMICCONFIGURATIONCONTROLLER_T70:
			data->T70_address = object->start_address;
			data->T70_reportid_min = min_id;
			data->T70_reportid_max = max_id;
			break;
		case MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71:
			data->T71_address = object->start_address;
			break;
		case MXT_PROCG_NOISESUPPRESSION_T72:
			data->T72_address = object->start_address;
			data->T72_reportid_min = min_id;
			data->T72_reportid_max = max_id;
			break;
		case MXT_PROCI_GLOVEDETECTION_T78:
			data->T78_address = object->start_address;
			break;
		case MXT_PROCI_RETRANSMISSIONCOMPENSATION_T80:
			data->T80_address = object->start_address;
			break;
		case MXT_PROCI_UNLOCKGESTURE_T81:
			data->T81_address = object->start_address;
			data->T81_reportid_min = min_id;
			data->T81_reportid_max = max_id;
			break;
		case MXT_PROCI_GESTURE_T92:
			data->T92_address = object->start_address;
			data->T92_reportid = min_id;
			break;
		case MXT_PROCI_TOUCHSEQUENCELOGGER_T93:
			data->T93_address = object->start_address;
			data->T93_reportid = min_id;
			break;
		case MXT_TOUCH_SPT_PTC_TUNINGPARAMS_T96:
			data->T96_address = object->start_address;
			break;
		case MXT_TOUCH_PTC_KEYS_T97:
			data->T97_reportid_min = min_id;
			data->T97_reportid_max = max_id;
			data->T97_address = object->start_address;
			break;
		case MXT_PROCI_KEYGESTUREPROCESSOR_T99:
			data->T99_address = object->start_address;
			data->T99_reportid = min_id;
			break;
		case MXT_TOUCH_MULTITOUCHSCREEN_T100:
			data->T100_reportid_min = min_id;
			data->T100_reportid_max = max_id;
			data->T100_address = object->start_address;
			/* first two report IDs reserved */
			data->num_touchids = object->num_report_ids - 2;
			break;
		case MXT_SPT_SELFCAPHOVERCTECONFIG_T102:
			data->T102_address = object->start_address;
			data->T102_reportid = min_id;
			break;
		case MXT_PROCI_AUXTOUCHCONFIG_T104:
			data->T104_address = object->start_address;
			break;
		case MXT_SPT_SELFCAPMEASURECONFIG_T113:
			data->T113_address = object->start_address;
			break;
		case MXT_PROCI_SYMBOLGESTURE_T115:
			data->T115_address = object->start_address;
			data->T115_reportid = min_id;
			break;
		case MXT_SPT_SMARTSCAN_T124:
			data->T124_address = object->start_address;
			data->T124_reportid = min_id;
			break;
		case MXT_PROCI_PEAKREGIONDATA_T125:
			data->T125_address = object->start_address;
			data->T125_reportid = min_id;
			break;
		}

		end_address = object->start_address
			+ mxt_obj_size(object) * mxt_obj_instances(object) - 1;

		if (end_address >= data->mem_size)
			data->mem_size = end_address + 1;
	}

	/* Store maximum reportid */
	data->max_reportid = reportid;

	/* If T44 exists, T5 position has to be directly after */
	if (data->T44_address && (data->T5_address != data->T44_address + 1)) {
		TS_LOG_ERR("Invalid T44 position\n");
		return -EINVAL;
	}

	data->msg_buf = kcalloc(data->max_reportid,
				data->T5_msg_size, GFP_KERNEL);
	if (!data->msg_buf) {
		TS_LOG_ERR("Failed to allocate message buffer\n");
		return -ENOMEM;
	}

	return 0;
}

static void mxt_calc_crc24(u32 *crc, u8 firstbyte, u8 secondbyte)
{
	static const unsigned int crcpoly = 0x80001B;
	u32 result;
	u32 data_word;

	data_word = (secondbyte << 8) | firstbyte;
	result = ((*crc << 1) ^ data_word);

	if (result & 0x1000000)
		result ^= crcpoly;

	*crc = result;
}

u32 mxt_calculate_crc(u8 *base, off_t start_off, off_t end_off)
{
	u32 crc = 0;
	u8 *ptr = base + start_off;
	u8 *last_val = base + end_off - 1;

	if (end_off < start_off)
		return -EINVAL;

	while (ptr < last_val) {
		mxt_calc_crc24(&crc, *ptr, *(ptr + 1));
		ptr += 2;
	}

	/* if len is odd, fill the last byte with 0 */
	if (ptr == last_val)
		mxt_calc_crc24(&crc, *ptr, 0);

	/* Mask to 24-bit */
	crc &= 0x00FFFFFF;

	return crc;
}

static int mxt_read_info_block(struct mxt_data *data)
{
	int error;
	size_t size;
	void *id_buf, *buf;
	uint8_t num_objects;
	u32 calculated_crc;
	u8 *crc_ptr;

	/* If info block already allocated, free it */
	if (data->raw_info_block != NULL)
		mxt_free_object_table(data);

	/* Read 7-byte ID information block starting at address 0 */
	size = sizeof(struct mxt_info);
	id_buf = kzalloc(size, GFP_KERNEL);
	if (!id_buf) {
		TS_LOG_ERR("Failed to allocate memory\n");
		return -ENOMEM;
	}

	error = __mxt_read_reg(data, 0, size, id_buf);
	if (error) {
		TS_LOG_ERR("%s, Failed to get id info\n", __func__);
		kfree(id_buf);
		return error;
	}

	/* Resize buffer to give space for rest of info block */
	num_objects = ((struct mxt_info *)id_buf)->object_num;
	size += (num_objects * sizeof(struct mxt_object))
		+ MXT_INFO_CHECKSUM_SIZE;

	buf = krealloc(id_buf, size, GFP_KERNEL);
	if (!buf) {
		TS_LOG_ERR("Failed to allocate memory\n");
		error = -ENOMEM;
		goto err_free_mem;
	}

	/* Read rest of info block */
	error = __mxt_read_reg(data, MXT_OBJECT_START,
					size - MXT_OBJECT_START,
					buf + MXT_OBJECT_START);
	if (error){
		TS_LOG_ERR("%s, Failed to read object info\n", __func__);
		goto err_free_mem;
	}
	/* Extract & calculate checksum */
	crc_ptr = buf + size - MXT_INFO_CHECKSUM_SIZE;
	data->info_crc = crc_ptr[0] | (crc_ptr[1] << 8) | (crc_ptr[2] << 16);

	calculated_crc = mxt_calculate_crc(buf, 0,
						size - MXT_INFO_CHECKSUM_SIZE);

	/* CRC mismatch can be caused by data corruption due to I2C comms
	 * issue or else device is not using Object Based Protocol */
	if ((data->info_crc == 0) || (data->info_crc != calculated_crc)) {
		TS_LOG_INFO(
			"Info Block CRC error calculated=0x%06X read=0x%06X\n",
			calculated_crc, data->info_crc);

		TS_LOG_DEBUG("info block size %d\n",(int)size);
		print_hex_dump(KERN_ERR, "[mxt] INFO:", DUMP_PREFIX_NONE, 16, 1,
			buf, size, false);

		error = -EIO;
		goto err_free_mem;
	}

	/* Save pointers in device data structure */
	data->raw_info_block = buf;
	data->info = (struct mxt_info *)buf;

	TS_LOG_INFO(
		 "Family: %u Variant: %u Firmware V%u.%u.%02X Objects: %u. matrix_xsize:%u. matrix_ysize:%u\n",
		 data->info->family_id, data->info->variant_id,
		 data->info->version >> 4, data->info->version & 0xf,
		 data->info->build, data->info->object_num,
		 data->info->matrix_xsize, data->info->matrix_ysize);

	/* Parse object table information */
	error = mxt_parse_object_table(data, buf + MXT_OBJECT_START);
	if (error) {
		TS_LOG_ERR("Error %d parsing object table\n", error);
		mxt_free_object_table(data);
		return error;
	}

	TS_LOG_DEBUG(
		 "T5 message size %d\n", data->T5_msg_size);

	data->object_table = (struct mxt_object *)(buf + MXT_OBJECT_START);
	return 0;

err_free_mem:
	kfree(buf);
	return error;
}

static int board_por_reset(struct mxt_data *data)
{
	//write your hw reset here, and return 0
	//if no, returen -EIO

#if defined(CONFIG_HAS_POR)
	mxt_regulator_disable(data);
	mxt_regulator_enable(data);
	return 0;
#endif

	return -EIO;
}

/*
 *Function for sending t6 command
 *
 *t6 is used to control mxt devices in varies ways such as resetting, backup, and calibrate.
 *
 */
int mxt_t6_command(struct mxt_data *data, u16 cmd_offset,
			  u8 value, bool wait)
{
	u16 reg;
	u8 command_register;
	int timeout_counter = 0;
	int ret;

	reg = data->T6_address + cmd_offset;

	ret = mxt_write_reg(data, reg, value);
	if (ret) {
		TS_LOG_ERR("%s: write %u error\n",__func__,reg);
		return ret;
	}
	TS_LOG_INFO("Set T6  to mode %d!\n" , value);

	if (!wait) {
		TS_LOG_INFO("%s:wait = %d\n",__func__,wait);
		return 0;
	}
	do {
		msleep(14);
		ret = __mxt_read_reg(data, reg, 1, &command_register);
		if (ret) {
			TS_LOG_INFO("%s: timeout_counter=%d\n",__func__,timeout_counter);
			return ret;
		}
	} while ((command_register != 0) && (timeout_counter++ <= 50));

	if (timeout_counter > 100) {
		TS_LOG_ERR( "Command failed!\n");
		return -EIO;
	}

	return 0;
}

int mxt_soft_reset(struct mxt_data *data)
{
	TS_LOG_INFO("Resetting chip\n");
	INIT_COMPLETION(data->reset_completion);

	atmel_status_resume();
	mxt_t6_command(data, MXT_COMMAND_REPORTALL, 1, false);
	return 0;
}

/*
 *Function for configuring t7
 *
 *t7 is used to config the mxt power consumption via setting the scan speed under active or inactive mode.
 *
 */
static int mxt_set_t7_power_cfg(struct mxt_data *data, u8 sleep)
{
	int error;
	struct t7_config *new_config;
	struct t7_config deepsleep = { .active = 0, .idle = 0 };

	if (sleep == MXT_POWER_CFG_DEEPSLEEP)
		new_config = &deepsleep;
	else
		new_config = &data->t7_cfg;

	error = __mxt_write_reg(data, data->T7_address,
			sizeof(data->t7_cfg),
			new_config);
	if (error)
		return error;

	TS_LOG_DEBUG("Set T7 ACTV:%d IDLE:%d\n", new_config->active, new_config->idle);

	msleep(10);

	return 0;
}

/*
 *Function for reading out t7 config when booting up.
 *
 *t7 is used to config the mxt power consumption via setting the scan speed under active or inactive mode.
 *
 */
int mxt_init_t7_power_cfg(struct mxt_data *data)
{
	int error;
	bool retry = false;

recheck:
	error = __mxt_read_reg(data, data->T7_address,
				sizeof(data->t7_cfg), &data->t7_cfg);
	if (error)
		return error;

	if (data->t7_cfg.active == 0 || data->t7_cfg.idle == 0) {
		if (!retry) {
			TS_LOG_DEBUG("T7 cfg zero, resetting\n");
			mxt_soft_reset(data);
			retry = true;
			goto recheck;
		} else {
			TS_LOG_DEBUG("T7 cfg zero after reset, overriding\n");
			data->t7_cfg.active = 20;
			data->t7_cfg.idle = 100;
			return mxt_set_t7_power_cfg(data, MXT_POWER_CFG_RUN);
		}
	} else {
		TS_LOG_DEBUG("Initialised power cfg: ACTV %d, IDLE %d\n",
				data->t7_cfg.active, data->t7_cfg.idle);
		return 0;
	}
}

struct mxt_object *mxt_get_object(struct mxt_data *data, u8 type)
{
	struct mxt_object *object;
	int i;

	if (!data->object_table) {
		TS_LOG_ERR("%s:data->object_table=%ld\n",__func__,PTR_ERR(data->object_table));
		goto out;
	}

	for (i = 0; i < data->info->object_num; i++) {
		object = data->object_table + i;
		if (object->type == type)
			return object;
	}

out:
	TS_LOG_ERR( "Invalid object type T%u\n", type);
	return NULL;
}

/*
 *Function for reading out t100 config.
 *
 *t100 is the main touch object which configs the touch performance, including the resolution, touth threshold and so on.
 *
 */
static int mxt_read_t100_config(struct mxt_data *data)
{
	int error;
	struct mxt_object *object;
	u16 range_x, range_y;
	u8 x_size, x_origin, y_size, y_origin;

	object = mxt_get_object(data, MXT_TOUCH_MULTITOUCHSCREEN_T100);
	if (!object) {
		TS_LOG_ERR("get MXT_TOUCH_MULTITOUCHSCREEN_T100 failed\n");
		return -EINVAL;
	}

	error = __mxt_read_reg(data,
					object->start_address + MXT_T100_XRANGE,
					sizeof(range_x), &range_x);
	if (error) {
		TS_LOG_ERR("%s:read MXT_T100_XRANGE failed\n",__func__);
		return error;
	}

	le16_to_cpus(&range_x);

	error = __mxt_read_reg(data,
					object->start_address + MXT_T100_YRANGE,
					sizeof(range_y), &range_y);
	if (error) {
		TS_LOG_ERR("read MXT_T100_YRANGE failed\n");
		return error;
	}

	le16_to_cpus(&range_y);

	error = __mxt_read_reg(data,
				object->start_address,
				sizeof(data->tchcfg), &data->tchcfg);
	if (error) {
		TS_LOG_ERR("read data->tchcfg failed\n");
		return error;
	}

	/* Handle default values */
	if (range_x == 0)
		range_x = 1023;

	/* Handle default values */
	if (range_x == 0)
		range_x = 1023;

	if (range_y == 0)
		range_y = 1023;

	if (test_flag_8bit(MXT_T100_CFG_SWITCHXY, &data->tchcfg[MXT_T100_CFG1])) {
		data->max_x = range_y;
		data->max_y = range_x;
	} else {
		data->max_x = range_x;
		data->max_y = range_y;
	}

/*read x size and y size*/
	error = __mxt_read_reg(data,
					object->start_address + MXT_T100_XSIZE,
					sizeof(x_size), &x_size);
	if (error) {
		TS_LOG_ERR("read MXT_T100_XSIZE failed\n");
		return error;
	}

	le16_to_cpus(&x_size);

	error = __mxt_read_reg(data,
					object->start_address + MXT_T100_YSIZE,
					sizeof(y_size), &y_size);
	if (error) {
		TS_LOG_ERR("read MXT_T100_YSIZE failed\n");
		return error;
	}

	le16_to_cpus(&y_size);

/*read x origin and y origin*/
	error = __mxt_read_reg(data,
					object->start_address + MXT_T100_XORIGIN,
					sizeof(x_origin), &x_origin);
	if (error) {
		TS_LOG_ERR("read MXT_T100_XORIGIN failed\n");
		return error;
	}

	le16_to_cpus(&x_origin);

	error = __mxt_read_reg(data,
					object->start_address + MXT_T100_YORIGIN,
					sizeof(y_origin), &y_origin);
	if (error) {
		TS_LOG_ERR("read MXT_T100_YORIGIN failed\n");
		return error;
	}

	le16_to_cpus(&y_origin);
	data->x_size = x_size;
	data->y_size = y_size;
	data->x_origin = x_origin;
	data->y_origin = y_origin;
	/* allocate aux bytes */
	TS_LOG_INFO(
		 "T100 Touchscreen size X%uY%u, X_size%uY_size%u, X_origin%uY_origin%u\n", data->max_x, data->max_y, data->x_size, data->y_size,
		 data->x_origin, data->y_origin);
	data->chip_data->x_max =  data->max_x + 1;
	data->chip_data->y_max =  data->max_y + 1;
	data->chip_data->x_max_mt =  data->max_x + 1;
	data->chip_data->y_max_mt =  data->max_y + 1;

	return 0;
}

static int mxt_initialize_t100_input_device(struct mxt_data *data)
{
	int error;

	error = mxt_read_t100_config(data);
	if (error)
		TS_LOG_ERR("Failed to initialize T100 resolution\n");

	return 0;
}

int mxt_configure_objects(struct mxt_data *data)
{
	int error;

	error = mxt_debug_msg_init(data);
	if (error) {
		TS_LOG_ERR("Failed to initialize debug msg\n");
		return error;
	}

	error = mxt_init_t7_power_cfg(data);
	if (error) {
		TS_LOG_ERR("Failed to initialize power cfg\n");
		return error;
	}

	if (data->T100_reportid_min) {
		error = mxt_initialize_t100_input_device(data);
		if (error)
			return error;
	} else {
		TS_LOG_ERR("No touch object detected\n");
	}

	data->enable_reporting = true;
	return 0;
}

static int mxt_initialize_info_block(struct mxt_data *data)
{
	int error;
	bool alt_bootloader_addr = false;
	bool retry = false;

retry_info:
	error = mxt_read_info_block(data);
	if (error) {
retry_bootloader:
		error = mxt_probe_bootloader(data, alt_bootloader_addr);
		if (error) {
			if (alt_bootloader_addr) {
				/* Chip is not in appmode or bootloader mode */
				TS_LOG_ERR("%s, Chip is not in appmode or bootloader mode",__func__);
				return error;
			}

			TS_LOG_INFO("%s, Trying alternate bootloader address\n", __func__);
			alt_bootloader_addr = true;
			goto retry_bootloader;
		} else {
			if (retry) {
				TS_LOG_ERR(
						"Could not recover device from "
						"bootloader mode\n");
				/* this is not an error state, we can reflash
				 * from here */
				data->in_bootloader = true;
				return 0;
			}

			/* Attempt to exit bootloader into app mode */
			board_por_reset(data);

			retry = true;
			goto retry_info;
		}
	}

	return error;
}
/*
 *Function for initializing touch device.
 *
 *First, it will initialize the information block, which contains the object information. 
 *Second, it will initialize necessary object for the mxt touch device.
 *
 */
static int mxt_initialize(struct mxt_data *data)
{
	int error;

	error = mxt_initialize_info_block(data);
	if (error) {
		TS_LOG_ERR("%s, mxt_initialize_info_block fail",__func__);
		return error;
	}

	error = mxt_configure_objects(data);
	if (error) {
		TS_LOG_ERR("%s, mxt_configure_objects fail",__func__);
		return error;
	}
#if defined(CONFIG_MXT_FORCE_RESET_AT_POWERUP)
	TS_LOG_ERR("board force a reset after gpio init\n");
	mxt_soft_reset(data);
#endif
#if defined (CONFIG_TEE_TUI)
	mxt_get_tui_data(data);
#endif
	return 0;
}

static void mxt_parse_module_dts(struct ts_device_data *chip_data)
{
	struct device_node *device = NULL;
	int retval, read_val;
	char *producer = NULL;
	char *description = NULL;

	device = of_find_compatible_node(NULL, NULL, mxt_g_data->module_id);
	if (!device) {
		TS_LOG_INFO("%s, No chip specific dts: %s, need to parse\n", __func__, mxt_g_data->module_id);
		return;
	}

	TS_LOG_INFO("%s, parse specific dts: %s\n", __func__, mxt_g_data->module_id);
	retval = of_property_read_u32(device, "x_max", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific x_max = %d\n", read_val);
		chip_data->x_max = read_val;
	}
	retval = of_property_read_u32(device, "y_max", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific y_max = %d\n", read_val);
		chip_data->y_max = read_val;
	}
	retval = of_property_read_u32(device, "x_max_mt", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific x_max_mt = %d\n", read_val);
		chip_data->x_max_mt = read_val;
	}
	retval = of_property_read_u32(device, "y_max_mt", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific y_max_mt = %d\n", read_val);
		chip_data->y_max_mt = read_val;
	}
	retval = of_property_read_u32(device, "max_minus_min_limit", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific max_minus_min_limit = %d\n", read_val);
		mxt_g_data->max_minus_min_limit = read_val;
	} else {
		mxt_g_data->max_minus_min_limit = chip_data->raw_limit_buf[RAW_DATA_UP];
	}
	retval = of_property_read_u32(device, "t72_noise_level_threshold", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific t72_noise_level_threshold = %d\n", read_val);
		mxt_g_data->t72_noise_level_threshold = read_val;
	} else {
		mxt_g_data->t72_noise_level_threshold = 5;
	}

	retval = of_property_read_string(device, "producer", &producer);
	if (producer != NULL) {
		TS_LOG_INFO("producer = %s\n", producer);
		strncpy(mxt_g_data->module_name, producer, MAX_MODULE_NAME_LEN);
	}
	retval = of_property_read_string(device, "description", &description);
	if (description != NULL) {
		TS_LOG_INFO("description = %s\n", description);
		strncpy(mxt_g_data->description, description, MAX_DESCRIPTION_LEN);
	}

	retval = of_property_read_u32(device, "roi_data_invert", &read_val);
	if (!retval) {
		TS_LOG_INFO("roi_data_invert = %d\n", read_val);
		mxt_g_data->roi_data_invert = (u8)read_val;
	}
	else {
		TS_LOG_INFO("can not get roi_data_invert value\n");
		mxt_g_data->roi_data_invert = 1;
	}

	retval = of_property_read_u32(device, "roi_supported", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific roi_supported = %d\n", read_val);
		g_ts_data.feature_info.roi_info.roi_supported = (u8)read_val;
	}
	else {
		TS_LOG_INFO("can not get roi_supported value\n");
		g_ts_data.feature_info.roi_info.roi_supported = 0;
	}

	retval = of_property_read_u32(device, "support_3d_func", &read_val);
	if (!retval) {
		chip_data->support_3d_func = read_val;
		TS_LOG_INFO("get support_3d_func = %d\n", chip_data->support_3d_func);
	}else {
		chip_data->support_3d_func = 0;
		TS_LOG_INFO("use default support_3d_func value = %d\n", chip_data->support_3d_func);
	}

#if defined(HUAWEI_CHARGER_FB)
	retval = of_property_read_u32(device, "charger_supported", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific charger_supported = %d\n", read_val);
		g_ts_data.feature_info.charger_info.charger_supported = (u8)read_val;
	} else {
		g_ts_data.feature_info.charger_info.charger_supported = 0;
		TS_LOG_INFO("use default charger_supported value = %d\n", g_ts_data.feature_info.charger_info.charger_supported);
	}
#endif
}

static void mxt_init_extra_data(void)
{
	memset(&mxt_g_data->sta_cnt, 0, sizeof(struct status_count));
	memset(&mxt_g_data->t72_noise_level, 0, sizeof(struct t72_noise_level));
	memset(&mxt_g_data->feature_extra_data, 0, sizeof(struct mxt_feature_extra_data));
	memset(&mxt_g_data->t25_msg, 0, sizeof(mxt_g_data->t25_msg));
	mxt_g_data->noise_state = MXT_T72_NOISE_SUPPRESSION_NO_DEF;
	mxt_g_data->mxt_cur_finger_number = 0;
	mxt_g_data->t72_state_change = 0;
}


static int atmel_init_chip(void)
{
	struct mxt_data *data = mxt_g_data;
	int error;

	/*detect the chip*/

	if (!data) {
		TS_LOG_ERR("atmel init chip invalid mxt_g_data\n");
		return -ENODEV;
	}

	error = mxt_initialize(data);
	if (error) {
		TS_LOG_ERR("atmel init chip mxt_initialize() failed\n");
	}

	error = mxt_get_module_name();
	if (error) {
		TS_LOG_ERR("atmel init get lockdown info failed\n");
	}

	mxt_parse_module_dts(data->chip_data);

	mxt_init_extra_data();

	return error;
}

static int atmel_parse_dts(struct device_node *device, struct ts_device_data *chip_data)
{
	int error = 0;
	int array_len = 0;
	int index = 0;
	const char *raw_data_dts = NULL;

	chip_data->irq_gpio = of_get_named_gpio(device, "attn_gpio", 0);
	if (!gpio_is_valid(chip_data->irq_gpio)) {
		TS_LOG_ERR("irq gpio is not valid, value is %d\n", chip_data->irq_gpio);
		error = -EINVAL;
		goto err;
	}
	chip_data->reset_gpio = of_get_named_gpio(device, "reset_gpio", 0);
	if (!gpio_is_valid(chip_data->reset_gpio)) {
		TS_LOG_ERR("reset gpio is not valid\n");
		error = -EINVAL;
		goto err;
	}
	error = of_property_read_u32(device, "irq_config", &chip_data->irq_config);
	if (error) {
		TS_LOG_ERR("get irq config failed\n");
		error = -EINVAL;
		goto err;
	}

	error = of_property_read_u32(device, "algo_id", &chip_data->algo_id);
	if (error) {
		TS_LOG_ERR("get algo id failed\n");
		error = -EINVAL;
		goto err;
	}

	error = of_property_read_u32(device, "x_max", &chip_data->x_max);
	if (error) {
		TS_LOG_INFO("use default x_max config\n");
		chip_data->x_max = 1080;
	}
	error = of_property_read_u32(device, "y_max", &chip_data->y_max);
	if (error) {
		TS_LOG_INFO("use default y_max config\n");
		chip_data->y_max = 1920;
	}
	error = of_property_read_u32(device, "x_max_mt", &chip_data->x_max_mt);
	if (error) {
		TS_LOG_INFO("use default x_max_mt config\n");
		chip_data->x_max_mt = 1080;
	}
	error = of_property_read_u32(device, "y_max_mt", &chip_data->y_max_mt);
	if (error) {
		TS_LOG_ERR("use default y_max_mt config\n");
		chip_data->y_max_mt = 1920;
	}
	error = of_property_read_u32(device, "tp_test_type", &chip_data->tp_test_type);
	if (error) {
		TS_LOG_INFO("get device tp_test_type not exit,use default value\n");
		strncpy(chip_data->tp_test_type,"Normalize_type:judge_different_reslut",TS_CAP_TEST_TYPE_LEN);
		error = 0;
	}

	array_len = of_property_count_strings(device, "raw_data_limit");
	if (array_len > 0 && array_len <= RAWDATA_NUM) {
		for(index = 0; index < array_len; index++){
			error = of_property_read_string_index(device, "raw_data_limit", index, &raw_data_dts);
			if (error) {
				TS_LOG_ERR("read index = %d,raw_data_limit = %s,retval = %d error,\n", index, raw_data_dts, error);
				break;
			}

			chip_data->raw_limit_buf[index] = simple_strtol(raw_data_dts, NULL, 10);
			TS_LOG_INFO("get rawdatabuf[%d] = %d\n", index, chip_data->raw_limit_buf[index]);
		}
	}
	TS_LOG_INFO("reset_gpio = %d, irq_gpio = %d, irq_config = %d, algo_id = %d, x_max = %d, y_max = %d, x_mt = %d,y_mt = %d, support_3d_func = %d\n", \
		chip_data->reset_gpio, chip_data->irq_gpio, chip_data->irq_config, chip_data->algo_id,
		chip_data->x_max, chip_data->y_max, chip_data->x_max_mt, chip_data->y_max_mt, chip_data->support_3d_func);
err:
	return error;
}

static int atmel_input_config(struct input_dev *input_dev)
{
	struct mxt_data *data = mxt_g_data;

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
	//input_set_capability(input_dev, EV_KEY, BTN_TOUCH);

	/* For single touch */
	input_set_abs_params(input_dev, ABS_X, 0, data->chip_data->x_max-1, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, data->chip_data->y_max-1, 0, 0);
	TS_LOG_DEBUG("data->chip_data->x_max-1=%d, data->chip_data->y_max-1=%d\n",
            data->chip_data->x_max-1, data->chip_data->y_max-1);

	input_set_abs_params(input_dev, ABS_PRESSURE, 0, 255, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TRACKING_ID, 0, 15, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
#if 0
	if ((test_flag_8bit(MXT_T100_TCHAUX_AMPL, &data->tchcfg[MXT_T100_TCHAUX])))
		input_set_abs_params(input_dev, ABS_PRESSURE,
					 0, 255, 0, 0);
#endif
#ifdef TYPE_B_PROTOCOL
	/* For multi touch */
	error = input_mt_init_slots(input_dev, data->num_touchids/*, INPUT_MT_DIRECT*/);
	if (error) {
		TS_LOG_ERR("input_mt_init_slots failed, error = %d\n", error);
		return error;
	}
#endif
	//input_set_abs_params(input_dev, ABS_MT_TOOL_TYPE, 0, MT_TOOL_MAX, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_X,
				 0, data->chip_data->x_max_mt-1, 0, 0);

	input_set_abs_params(input_dev, ABS_MT_POSITION_Y,
				 0, data->chip_data->y_max_mt-1, 0, 0);
	TS_LOG_DEBUG("MT: data->chip_data->x_max-1=%d, data->chip_data->y_max-1=%d\n",
            data->chip_data->x_max_mt -1, data->chip_data->y_max_mt -1);
#if 0
	if (test_flag_8bit(MXT_T100_TCHAUX_AREA | MXT_T100_TCHAUX_AREAHW, &data->tchcfg[MXT_T100_TCHAUX]))
		input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR,
					 0, MXT_MAX_AREA, 0, 0);

	if (test_flag_8bit(MXT_T100_TCHAUX_AMPL, &data->tchcfg[MXT_T100_TCHAUX]))
		input_set_abs_params(input_dev, ABS_MT_PRESSURE,
					 0, 255, 0, 0);

	if (test_flag_8bit(MXT_T100_TCHAUX_VECT, &data->tchcfg[MXT_T100_TCHAUX]))
		input_set_abs_params(input_dev, ABS_MT_ORIENTATION,
					 0, 255, 0, 0);
#endif
	return NO_ERR;
}

static int atmel_irq_top_half(struct ts_cmd_node *cmd)
{
	cmd->command = TS_INT_PROCESS;
	TS_LOG_DEBUG("atmel irq top half called\n");
	return NO_ERR;
}

static void mxt_dump_message(struct mxt_data *data, u8 *message)
{
	//print_hex_dump(KERN_DEBUG, "MXT MSG:", DUMP_PREFIX_NONE, 16, 1,
				//message, data->T5_msg_size, false);
}

static void mxt_reset_slots(struct mxt_data *data)
{
}

/*
 *The following functions for processing object messages.
 *
 *Some, not all, object can report messages to the host. An example is t100, which report the touch status.
 *
 */
static void mxt_proc_t6_messages(struct mxt_data *data, u8 *msg)
{
	u8 status = msg[1];
	u32 crc = msg[2] | (msg[3] << 8) | (msg[4] << 16);

	if (crc != data->config_crc) {
		data->config_crc = crc;
		TS_LOG_DEBUG("T6 Config Checksum: 0x%06X\n", crc);
	}

	/* Detect transition out of reset */
	if (data->t6_status & MXT_T6_STATUS_RESET) {
		if (!(status & MXT_T6_STATUS_RESET)) {
		complete(&data->reset_completion);
		}
	}

	/* Output debug if status has changed */
	if (status != data->t6_status) {
		TS_LOG_DEBUG("T6 Status 0x%02X%s%s%s%s%s%s%s\n",
			status,
			(status == 0) ? " OK" : "",
			(status & MXT_T6_STATUS_RESET) ? " RESET" : "",
			(status & MXT_T6_STATUS_OFL) ? " OFL" : "",
			(status & MXT_T6_STATUS_SIGERR) ? " SIGERR" : "",
			(status & MXT_T6_STATUS_CAL) ? " CAL" : "",
			(status & MXT_T6_STATUS_CFGERR) ? " CFGERR" : "",
			(status & MXT_T6_STATUS_COMSERR) ? " COMSERR" : "");

		if (status & MXT_T6_STATUS_CAL)
			mxt_reset_slots(data); //release all points in calibration for safe

	}
	/* Save current status */
	data->t6_status = status;
}

void parse_t100_scr_message(const u8 *message, unsigned long scraux, struct scr_info *in)
{
	u8 aux = 1;

	memset(in, 0, sizeof(struct scr_info));
	in->status = message[aux++];

	if (test_flag(MXT_T100_SCRAUX_NUMTCH, &scraux))
		in->num_tch = message[aux++];

	if (test_flag(MXT_T100_SCRAUX_TCHAREA, &scraux)) {
		in->area_tch = MAKEWORD(message[aux], message[aux + 1]);
		aux += 2;
	}

	if (test_flag(MXT_T100_SCRAUX_ATCHAREA, &scraux)) {
		in->area_atch = MAKEWORD(message[aux], message[aux + 1]);		
		aux += 2;
	}

	if (test_flag(MXT_T100_SCRAUX_INTTCHAREA, &scraux)) {
		in->area_inttch = MAKEWORD(message[aux], message[aux + 1]);
		aux += 2;
	}
}


void parse_t100_ext_message(const u8 *message, const u8 *tchcfg, struct ext_info *in)
{
	u8 aux = 6;
	u8 exp;

	memset(in, 0, sizeof(struct ext_info));
	in->status = message[1];

	if (!(in->status & MXT_T100_DETECT))
		return;

	if (test_flag_8bit(MXT_T100_TCHAUX_VECT, &tchcfg[MXT_T100_TCHAUX]))
		in->vec = message[aux++];

	if (aux < 10) {
		//check amp setting, if amp setting is disabled then set amp to 0xff, in case system do not response touch.
		if (test_flag_8bit(MXT_T100_TCHAUX_AMPL, &tchcfg[MXT_T100_TCHAUX])) {
			in->amp = message[aux++];			
			if (in->amp < 0xff)
				in->amp++;
		}else{
			in->amp = 0xff;
		}
	}

	if (aux < 10) {
		if (test_flag_8bit(MXT_T100_TCHAUX_AREA, &tchcfg[MXT_T100_TCHAUX]))
			in->area = message[aux++];
	}

	if (aux < 9) {
		if (test_flag_8bit(MXT_T100_TCHAUX_HW, &tchcfg[MXT_T100_TCHAUX])) {
				in->height = message[aux++];
				in->width = message[aux++];
			if (test_flag_8bit(MXT_T100_CFG_SWITCHXY, &tchcfg[MXT_T100_CFG1])) 
				swap(in->height,in->width);
		}
	}

	if (aux < 10) {
		if (test_flag_8bit(MXT_T100_TCHAUX_PEAK, &tchcfg[MXT_T100_TCHAUX]))
			in->peak = message[aux++];
	}

	if (aux < 9) {
		if (test_flag_8bit(MXT_T100_TCHAUX_AREAHW, &tchcfg[MXT_T100_TCHAUX])) {
			exp = (message[aux] >> 5) & 0x3;
			in->area = (message[aux] & 0x1f) << exp;
			in->height = (message[aux + 1] & 0xf)  << exp;
			in->width = (message[aux + 1] >> 4)  << exp;
			if (test_flag_8bit(MXT_T100_CFG_SWITCHXY, &tchcfg[MXT_T100_CFG1])) 
				swap(in->height,in->width);			
		}
	}
}

static void mxt_t100_touchdown_message(struct mxt_data *data, u8 status)
{
	struct feature_info* feature_glove = &mxt_feature_list[MAX_GLOVE_CONF];

	if (MXT_FEATURE_ENABLE == feature_glove->on_flag
		&& mxt_g_data->noise_state != MXT_T72_NOISE_SUPPRESSION_VNOIS
		&& mxt_g_data->noise_state != MXT_T72_NOISE_SUPPRESSION_NOIS){
		switch(status & MXT_T100_TYPE_MASK){
			case MXT_T100_TYPE_FINGER:
				mxt_enable_feature(data, MAX_WORKAROUND1_CONF);
				break;
			case MXT_T100_TYPE_GLOVE:
				mxt_enable_feature(data, MAX_WORKAROUND2_CONF);
				break;
			default:
				break;
		}
	}
}
static void mxt_t100_touchup_message(struct mxt_data *data, u8 status)
{
	struct feature_info* feature = &mxt_feature_list[MAX_GLOVE_CONF];

	if (MXT_FEATURE_ENABLE == feature->on_flag
		&& mxt_g_data->noise_state != MXT_T72_NOISE_SUPPRESSION_VNOIS
		&& mxt_g_data->noise_state != MXT_T72_NOISE_SUPPRESSION_NOIS){
		switch(status & MXT_T100_TYPE_MASK){
			case MXT_T100_TYPE_FINGER:
				TS_LOG_DEBUG("mxt_cur_finger_number: %d\n", mxt_g_data->mxt_cur_finger_number);
				if(mxt_g_data->mxt_cur_finger_number==0){
					mxt_disable_feature(data, MAX_WORKAROUND1_CONF);
				}
				break;
			case MXT_T100_TYPE_GLOVE:
				if(mxt_g_data->mxt_cur_finger_number==0){
					mxt_disable_feature(data, MAX_WORKAROUND2_CONF);
				}
				break;
			default:
				break;
		}
	}
}

static bool mxt_touch_suppression(struct mxt_data *data, int x, int y, u8 status)
{
	u8 widHB, widLB;
	int width;
	bool retval = false;
	struct feature_info* feature_glove = &mxt_feature_list[MAX_GLOVE_CONF];
	struct feature_info* feature_cover = &mxt_feature_list[MAX_COVER_CONF];

	if(MXT_FEATURE_ENABLE == feature_glove->on_flag
		&& (status & MXT_T100_TYPE_MASK) == MXT_T100_TYPE_GLOVE){
		widHB = mxt_g_data->feature_extra_data.glove_sup_h;
		widLB = mxt_g_data->feature_extra_data.glove_sup_l;
		width = (widHB << 8) | widLB;
		TS_LOG_DEBUG("touch suppression width for glove is %d\n", width);
		retval = (x < width || x > data->max_x - width);
	}

	if(MXT_FEATURE_ENABLE == feature_cover->on_flag
		&& mxt_g_data->feature_extra_data.cover_glass){
		widHB = mxt_g_data->feature_extra_data.cover_sup_h;
		widLB = mxt_g_data->feature_extra_data.cover_sup_l;
		width = (widHB << 8) | widLB;
		TS_LOG_DEBUG("touch suppression width for cover is %d\n", width);
		retval = retval || (x < width || x > data->max_x - width);
	}

	return retval;
}

static void mxt_proc_t100_message(struct mxt_data *data, u8 *message)
{
	struct ts_fingers *cache = data->ts_cache;

	int id;
	u8 status;
	int x;
	int y;
	struct ext_info info;
	u16 reg;
	u8 command_register[2];
	int ret;
	/* do not report events if input device not yet registered */

	if (!data->enable_reporting)
		return;

	id = message[0] - data->T100_reportid_min - 2;
	/* ignore SCRSTATUS events */
	if (id < 0) {
		TS_LOG_DEBUG(
			"T100 [%d] SCRSTATUS : 0x%x\n",
			id,
			message[1]);
		return;
	}

	status = message[1];
	x = (message[3] << 8) | message[2];
	y = (message[5] << 8) | message[4];

	if(MXT_FEATURE_ENABLE == mxt_feature_list[MAX_COVER_CONF].on_flag){
		if(mxt_g_data->feature_extra_data.cover_cut){
			x = data->max_x - x;
		}
	}

	parse_t100_ext_message(message, data->tchcfg, &info);
	TS_LOG_DEBUG(
		"[%u] status:%02X x:%u y:%u [amp]:%02X [vec]:%02X [area]:%02X [peak]:%02X [width]:%02X [height]:%02X\n",
		id,
		status,
		x, y,
		info.amp,
		info.vec,
		info.area,
		info.peak,
		info.width,
		info.height);

	memset(&cache->fingers[id], 0, sizeof(cache->fingers[id]));

	if (status & MXT_T100_DETECT) {
		switch(status & MXT_T100_EVENT_MASK){
			case MXT_T100_EVENT_DOWN:
				mxt_t100_touchdown_message(data, status);
				break;
			default:
				break;
		}
	} else {
		/* Touch no longer active, close out slot */
		switch(status & MXT_T100_EVENT_MASK){
			case MXT_T100_EVENT_UP:
				mxt_t100_touchup_message(data, status);
				break;
			default:
				break;
		}
		cache->cur_finger_number = mxt_g_data->mxt_cur_finger_number;
		goto out;
	}

	if(mxt_touch_suppression(data,x,y,status)) goto out;//if touch is within the suppression area

	switch(status & MXT_T100_TYPE_MASK){
		case MXT_T100_TYPE_FINGER:
			cache->fingers[id].status = TP_FINGER;
			TS_LOG_DEBUG("Touch type is finger, status:%02X\n", status & MXT_T100_TYPE_MASK);
			break;
		case MXT_T100_TYPE_STYLUS:
			cache->fingers[id].status = TP_STYLUS;
			TS_LOG_DEBUG("Touch type is stylus, status:%02X\n", status & MXT_T100_TYPE_MASK);
			break;
		case MXT_T100_TYPE_GLOVE:
			cache->fingers[id].status = TP_GLOVE;
			TS_LOG_DEBUG("Touch type is glove, status:%02X\n", status & MXT_T100_TYPE_MASK);
			break;
		default:
			cache->fingers[id].status = 0;
			TS_LOG_DEBUG("Touch type is undefined, status:%02X\n", status & MXT_T100_TYPE_MASK);
			break;
	}
	/* Touch active */
	cache->fingers[id].x = x;
	cache->fingers[id].y = y;

	cache->fingers[id].pressure = info.amp;
	cache->cur_finger_number = mxt_g_data->mxt_cur_finger_number;

	if (test_flag_8bit(MXT_T100_TCHAUX_AREA | MXT_T100_TCHAUX_AREAHW, &data->tchcfg[MXT_T100_TCHAUX])) {
		if (cache->fingers[id].status == TP_STYLUS)
			cache->fingers[id].major = MXT_TOUCH_MAJOR_T47_STYLUS;
		else
			cache->fingers[id].major = info.area;
	}

	if (test_flag_8bit(MXT_T100_TCHAUX_VECT, &data->tchcfg[MXT_T100_TCHAUX]))
		cache->fingers[id].orientation = info.vec;

	TS_LOG_DEBUG(
		"finger[%u] status:%02X, x:%u, y:%u, pressure:%u, cur_finger_number:%u\n",
		id,
		cache->fingers[id].status,
		cache->fingers[id].x,
		cache->fingers[id].y,
		cache->fingers[id].pressure,
		cache->cur_finger_number);

out:
#ifdef ROI
	if( (MXT_T6_CMD58_ON == gMxtT6Cmd58Flag) && ( MXT_FEATURE_ENABLE == mxt_feature_list[MAX_KNUCKLE_CONF].on_flag)){
		reg = data->T37_address;
		ret = __mxt_read_reg(data, reg, sizeof(command_register), &command_register[0]);
		if (ret) {
			TS_LOG_ERR("T37 read offset 0 failed %d!\n",ret);
			return ;
		}
		if((message[1] & MXT_T100_EVENT_MASK)  == MXT_T100_EVENT_DOWN
			&&((u8)command_register[0] != MXT_T6_DEBUG_PEAKREGIONDATA || command_register[1] != 0) ){
			mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC, MXT_T6_DEBUG_PEAKREGIONDATA, 0);
			TS_LOG_DEBUG("T37 has been set to T125 mode!\n");
		}
	}
#endif
}

static void mxt_proc_t25_messages(struct mxt_data *data, u8 *msg)
{
	u8 status = msg[1];

	/* Output debug if status has changed */
	TS_LOG_DEBUG("T25 Status 0x%x Info: %x %x %x %x %x\n",
		status,
		msg[2],
		msg[3],
		msg[4],
		msg[5],
		msg[6]);

	/* Save current status */
	memcpy(&data->t25_msg[0], &msg[1], sizeof(data->t25_msg));
}

static int mxt_proc_gesture_messages(struct mxt_data *data, u8 type, u8 key, u8 *msg)
{
	struct ts_fingers *cache = data->ts_cache;

	u8 num_keys;
	const unsigned int *keymap;
	int idx = -EINVAL;

	if (!data->pdata)
		return 0;

	/* do not report events if input device not yet registered */
	if (!data->pdata->keymap || !data->pdata->num_keys)
		return -ENODEV;

	num_keys =data->pdata->num_keys[key];
	keymap = data->pdata->keymap[key];
	if (idx >= 0 && num_keys) {
		if(idx >= num_keys)
			idx = num_keys - 1;
		if (idx >= 0 && idx < num_keys) {
			cache->gesture_wakeup_value = keymap[idx];
			//cache->gesture_wakeup_command = 2;

			return 0;
		}else{
			TS_LOG_ERR("T%d discard unused key %d\n",
				type,
				idx);
		}
	}

	return -EINVAL;
}

static void mxt_proc_t68_messages(struct mxt_data *data, u8 *msg)
{
	TS_LOG_DEBUG("T68 state = 0x%x\n" , msg[1]);
}


/*
 *Function for processing t70 messages.
 *
 *T70 is an object which dynamicly configs the maxTouch devices.
 *
 */
static void mxt_proc_t70_messages(struct mxt_data *data, u8 *msg)
{
	if( data->T70_reportid_min == msg[0]){
	    if(msg[1] & MAX_HSYN_MASK){
               data->hsyncstatus = MXT_SYNC_LOST;
		TS_LOG_INFO("Hsync lost");
	    } else{
               data->hsyncstatus = MXT_SYNC_OK;
           }
	}
	data->t70_msg_processed = 1;
	TS_LOG_DEBUG("T70 Dynamic Controller ReportID= 0x%x state = 0x%x\n" ,
		msg[0],
		msg[1]);
	TS_LOG_DEBUG("T70 min report id= %d, data->hsyncstatus = %d\n" ,
		data->T70_reportid_min,
		data->hsyncstatus);
}

static void increase_sta_cnt(u32 *pnum)
{
	u32 num = *pnum;
	if(num + 1 < num) {
		memset(&mxt_g_data->sta_cnt, 0, sizeof(struct status_count));
	} else {
		*pnum = num + 1;
	}
}

static void mxt_status_count(u8 *msg)
{
	switch(msg[2]& MXT_T72_NOISE_SUPPRESSION_STATUS2STATE_MASK){
		case MXT_T72_NOISE_SUPPRESSION_STAB:
			increase_sta_cnt(&mxt_g_data->sta_cnt.stable_state);
			break;
		case MXT_T72_NOISE_SUPPRESSION_NOIS:
			increase_sta_cnt(&mxt_g_data->sta_cnt.noise_state);
			break;
		case MXT_T72_NOISE_SUPPRESSION_VNOIS:
			increase_sta_cnt(&mxt_g_data->sta_cnt.vnoise_state);
			break;
		default:
			break;
	}
}

/*detect charger noise message*/
static void mxt_proc_t72_messages(struct mxt_data *data, u8 *msg)
{
	int noise_level;
	struct feature_info* feature = &mxt_feature_list[MAX_GLOVE_CONF];

	TS_LOG_DEBUG("T72 noise state1 = 0x%x state2 = 0x%x\n" ,
		msg[1],
		msg[2]);

	if (msg[1] & MXT_T72_NOISE_SUPPRESSION_STATECHG) {
		mxt_status_count(msg);
		if((mxt_g_data->noise_state == MXT_T72_NOISE_SUPPRESSION_VNOIS)&&
			(msg[2]& MXT_T72_NOISE_SUPPRESSION_STATUS2STATE_MASK) == MXT_T72_NOISE_SUPPRESSION_NOIS){
			TS_LOG_DEBUG("T72 state change from state = %d to state = %d\n", mxt_g_data->noise_state, msg[2] & 0x7);
			if(mxt_g_data->mxt_cur_finger_number == 0){
				mxt_enable_feature(data, MAX_WORKAROUND4_CONF);
				mxt_g_data->t72_state_change = 0;
			}else{
				mxt_g_data->t72_state_change = 1;
			}
		}

		if((msg[2]& MXT_T72_NOISE_SUPPRESSION_STATUS2STATE_MASK) == MXT_T72_NOISE_SUPPRESSION_VNOIS){
			mxt_g_data->t72_state_change = 0;
		}

		if(((msg[2]& MXT_T72_NOISE_SUPPRESSION_STATUS2STATE_MASK) == MXT_T72_NOISE_SUPPRESSION_STAB)
			&& (MXT_FEATURE_ENABLE == feature->on_flag)
			&& (mxt_g_data->mxt_cur_finger_number == 0)){
			mxt_disable_feature(data, MAX_WORKAROUND1_CONF);
			mxt_disable_feature(data, MAX_WORKAROUND2_CONF);
		}
	}
	mxt_g_data->noise_state = msg[2]& MXT_T72_NOISE_SUPPRESSION_STATUS2STATE_MASK;
	TS_LOG_DEBUG("pre state = %d\n" , mxt_g_data->noise_state);

	if(MXT_FEATURE_ENABLE == mxt_feature_list[MAX_WORKAROUND3_CONF].on_flag){
		noise_level = msg[4];
		mxt_g_data->t72_noise_level.total_count++;
		if(noise_level < mxt_g_data->t72_noise_level_threshold){
			mxt_g_data->t72_noise_level.success_count++;
		}
		if(mxt_g_data->t72_noise_level.noise_level_max < noise_level){
			mxt_g_data->t72_noise_level.noise_level_max = noise_level;
		}
		if(mxt_g_data->t72_noise_level.noise_level_min > noise_level){
			mxt_g_data->t72_noise_level.noise_level_min = noise_level;
		}
		TS_LOG_INFO("%s, noise peak/level msg[4] is %d", __func__, noise_level);
	}
}

static void mxt_proc_T81_messages(struct mxt_data *data, u8 *msg)
{
	u8 reportid = msg[0];
 	u8 status = msg[1];

	TS_LOG_DEBUG("T81 Status 0x%x Info: %x %x %x %x\n",
		status,
		msg[2],
		msg[3],
		msg[4],
		msg[5]);

	msg[0] -= data->T81_reportid_min;

	msg[0] = reportid;
}

static void mxt_proc_T92_messages(struct mxt_data *data, u8 *msg)
{
	u8 status = msg[1];

	TS_LOG_DEBUG("T92 %s 0x%x Info: %x %x %x %x %x %x\n",
		(status & 0x80) ? "stroke" : "symbol",
		status,
		msg[2],
		msg[3],
		msg[4],
		msg[5],
		msg[6],
		msg[7]);
}

static void mxt_proc_T93_messages(struct mxt_data *data, u8 *msg)
{
	u8 status = msg[1];

	TS_LOG_DEBUG("T93 Status 0x%x Info: %x\n",
		status,
		msg[1]);
}


static void mxt_proc_t15_messages(struct mxt_data *data, u8 *msg)
{
	struct ts_fingers *cache = data->ts_cache;
	int key;
	bool curr_state, new_state;
	bool sync = false;
	unsigned long keystates = le32_to_cpu(msg[2]);
	u8 num_keys;
	const unsigned int *keymap;

	/* do not report events if input device not yet registered */	
	if (!data->enable_reporting)
		return;

	if (!data->pdata)
		return;

	if (!data->pdata->keymap || !data->pdata->num_keys)
		return;

	num_keys =data->pdata->num_keys[T15_T97_KEY];
	keymap = data->pdata->keymap[T15_T97_KEY];
	for (key = 0; key < num_keys; key++) {
		curr_state = test_bit(key, &data->t15_keystatus);
		new_state = test_bit(key, &keystates);

		if (!curr_state && new_state) {
			TS_LOG_DEBUG("T15 key press: %u\n", key);
			__set_bit(key, &data->t15_keystatus);
			cache->special_button_flag = 1;
			cache->special_button_key = keymap[key];
			sync = true;
		} else if (curr_state && !new_state) {
			TS_LOG_DEBUG("T15 key release: %u\n", key);
			__clear_bit(key, &data->t15_keystatus);
			cache->special_button_flag = 0;
			cache->special_button_key = keymap[key];
			
			sync = true;
		}
	}
}

static void mxt_proc_t97_messages(struct mxt_data *data, u8 *msg)
{
	mxt_proc_t15_messages(data,msg);
}

static void mxt_proc_T99_messages(struct mxt_data *data, u8 *msg)
{
	u8 status = msg[1];

	TS_LOG_DEBUG("T99 Status 0x%x Event: %d Index %d\n",
		status,
		msg[1] & 0xF,
		msg[2]);
}

static void mxt_proc_t102_messages(struct mxt_data *data, u8 *msg)
{
	TS_LOG_DEBUG("msg for t102 = 0x%x 0x%x 0x%x 0x%x\n",
		msg[2], msg[3], msg[4], msg[5]);
}

static void mxt_proc_T115_messages(struct mxt_data *data, u8 *msg)
{
	u8 status = msg[1];

	TS_LOG_DEBUG("T115 Status 0x%x Info: %x\n",
		status,
		msg[1]);
}
/*
 *Read T37 data for Knuckle Gesture
 *
 *t37 is used to store diagnostic data which can be references, delta and so on. Which kind of data is stored is controled by byte 5 of t6.
 *this function fist set t6 byte 5 and then read t37 for the data wanted.
 *
 */
static int mxt_diagnostic_command_roi(struct mxt_data *data, u8 cmd, u8 page, u8 index, u8 num, char * buf, int interval, int interval_c)
{
	u16 reg;
	s8 command_register[2];
	int ret;

	if (buf) {
		//check the mode and page
		ret = __mxt_read_reg(data, data->T37_address, sizeof(command_register), &command_register[0]);
		if (ret) {
			TS_LOG_ERR("T37 read offset 0 failed %d!\n",ret);
			return -EIO;
		}

		if ((u8)command_register[0] != cmd || command_register[1] != page) {
			mxt_t6_command(data, MXT_COMMAND_DIAGNOSTIC, MXT_T6_DEBUG_PEAKREGIONDATA, 0);
			TS_LOG_ERR("%s, T37 not in Peak Data Mode, wait for next round. Expected (%d,%d). Actual (%d,%d). It is OK on booting\n",
							__func__,
							cmd,
							page,
							(u8)command_register[0],
							command_register[1]);
			return -EIO;
		}
		//read data
		ret = __mxt_read_reg(data, data->T37_address + sizeof(command_register) + index, num, buf);
		if (ret) {
			TS_LOG_ERR(
				"Failed to read T37 val at page %d.%d (%d)\n", page, index, ret);
			return -EIO;
		}

		TS_LOG_DEBUG("T37 cmd %d page %d, T37 buf(%03d %03d %03d %03d)\n",
				command_register[0],command_register[1],buf[0], buf[1], buf[2], buf[3]);
	}

	return 0;
}

void mxt_read_roi_data(struct mxt_data *data)
{
#ifdef ROI
	int ret = -EINVAL;
	int retry = 0;
	int i, j;
	u16 temp;
	u16 buf[MXT_ROI_ROW][MXT_ROI_ROW];
	u16 (*target)[MXT_ROI_ROW] = &roi_data[0]+4;

	if(gMxtT6Cmd58Flag != MXT_T6_CMD58_ON){
		return;
	}

	do{
		TS_LOG_DEBUG("%s \n" , __func__);
		ret = mxt_diagnostic_command_roi(data, MXT_T6_DEBUG_PEAKREGIONDATA, 0, 0, MISC_PEAKDATA_LEN_U8, (char *)buf, 10, 5);
		if (ret == 0) {
		    break;
		}
		msleep(10);
	}while(++retry < 5);

	if (ret != 0) {
		TS_LOG_ERR("Read Peak Data failed %d\n",ret);
		memset(roi_data, 0, ROI_DATA_READ_LENGTH);
		return;
	}

	TS_LOG_DEBUG("%s, before inert: %d, %d, %d, %d\n", __func__, buf[0][0], buf[0][MXT_ROI_ROW-1], buf[MXT_ROI_ROW-1][0], buf[MXT_ROI_ROW-1][MXT_ROI_ROW-1]);

	if(mxt_g_data->roi_data_invert){
		for( i = 0 ; i < MXT_ROI_ROW ; i ++){
			for( j = 0 ; j < MXT_ROI_ROW / 2 ; j ++ ){
				temp = buf[i][j];
				buf[i][j] = buf[i][MXT_ROI_ROW - 1 - j];
				buf[i][MXT_ROI_ROW - 1 - j] = temp;
			}
		}
		TS_LOG_DEBUG("%s, roi data invert.\n", __func__);
	}

	TS_LOG_DEBUG("%s, after inert: %d, %d, %d, %d\n", __func__, buf[0][0], buf[0][MXT_ROI_ROW-1], buf[MXT_ROI_ROW-1][0], buf[MXT_ROI_ROW-1][MXT_ROI_ROW-1]);

	for( i = 0 ; i < MXT_ROI_ROW; i ++){
		for (j = 0; j < MXT_ROI_ROW; j++){
			target[i][j] = buf[i][j];
		}
	}
#endif
}


/*
 *Function for processing t125 messages.
 *
 *T125 is used to detect whether the knuckle gesture data is ready in t37. When it is ready, t125 would generate the a message.
 *
 */
static void mxt_proc_T125_messages(struct mxt_data *data, u8 *msg)
{
#ifdef ROI
    mxt_read_roi_data(data);
#endif
}


static void mxt_proc_T124_messages(struct mxt_data *data, u8 *msg)
{
       if(MXT_T124_VSYNC_MASK & msg[1]){
		data->vsyncstatus = MXT_SYNC_OK;
	}else{
		data->vsyncstatus = MXT_SYNC_LOST;
	}

	TS_LOG_DEBUG("%s, msg = 0x%x\n", __func__, msg[1]);
}


static void mxt_proc_t42_messages(struct mxt_data *data, u8 *msg)
{
	u8 status = msg[1];

	if (status & MXT_T42_MSG_TCHSUP)
		TS_LOG_DEBUG("T42 suppress\n");
	else
		TS_LOG_DEBUG("T42 normal\n");
}
static void mxt_proc_t61_messages(struct mxt_data *data, u8 *msg)
{

}
static int mxt_proc_t48_messages(struct mxt_data *data, u8 *msg)
{
	
	u8 status, state;

	status = msg[1];
	state  = msg[4];

	TS_LOG_DEBUG("T48 state %d status %02X %s%s%s%s%s\n",
			state,
			status,
			(status & 0x01) ? "FREQCHG " : "",
			(status & 0x02) ? "APXCHG " : "",
			(status & 0x04) ? "ALGOERR " : "",
			(status & 0x10) ? "STATCHG " : "",
			(status & 0x20) ? "NLVLCHG " : "");

	return 0;
}

static void mxt_proc_t24_messages(struct mxt_data *data, u8 *msg)
{
	u8 status = msg[1];

	TS_LOG_DEBUG("T24 Status 0x%x Info: %x %x %x %x %x %x\n",
		status,
		msg[2],
		msg[3],
		msg[4],
		msg[5],
		msg[6],
		msg[7]);
}

static void mxt_proc_t100_message_number(struct mxt_data *data, u8 *message)
{
	int id;
	u8 status;
	u8 val[1];
	u16 addr;
	int ret;
	struct scr_info info;
	struct ts_feature_info* x_info = &g_ts_data.feature_info;

	/* do not report events if input device not yet registered */

	if (!data->enable_reporting)
		return;

	id = message[0] - data->T100_reportid_min - 2;

	if (id != -2) {
		TS_LOG_DEBUG(
			"T100 [%d] msg : 0x%x\n",
			id,
			message[1]);
		return;
	}

	status = message[1];
	
	parse_t100_scr_message(message, data->tchcfg[MXT_T100_SCRAUX], &info);
	TS_LOG_DEBUG(
		"[scr] status:%02X  [num]:%d [area]:%d %d %d\n",
		status,
		info.num_tch,
		info.area_tch,
		info.area_atch,
		info.area_inttch);

	mxt_g_data->mxt_cur_finger_number = info.num_tch;

	addr = data->T100_address + 1;
	ret = __mxt_read_reg(data,
					addr,
					sizeof(val), val);
	if (ret)
		return;

	if(mxt_g_data->mxt_cur_finger_number == 0 && mxt_g_data->t72_state_change == 1){
		mxt_enable_feature(data, MAX_WORKAROUND4_CONF);
		mxt_g_data->t72_state_change = 0;
	}
	if(mxt_g_data->mxt_cur_finger_number == 0 ){
		if (MXT_FEATURE_ENABLE == x_info->glove_info.glove_switch
		&& mxt_g_data->noise_state == MXT_T72_NOISE_SUPPRESSION_STAB){
			mxt_disable_feature(data, MAX_WORKAROUND1_CONF);
			mxt_disable_feature(data, MAX_WORKAROUND2_CONF);
		}
	}
	return;
}

static int mxt_proc_message(struct mxt_data *data, u8 *message)
{
	u8 report_id = message[0];
	bool dump = data->debug_enabled;

	if (report_id == MXT_RPTID_NOMSG)
		return 0;

	if (report_id == data->T6_reportid) {
		mxt_proc_t6_messages(data, message);
	} else if (report_id >= data->T9_reportid_min
		&& report_id <= data->T9_reportid_max) {
	} else if (report_id >= data->T100_reportid_min
		&& report_id <= data->T100_reportid_max) {
#ifndef T100_PROC_FINGER_NUM
			mxt_proc_t100_message(data, message);
#else
		if (report_id < data->T100_reportid_min + 2)
			mxt_proc_t100_message_number(data, message);
		else
			mxt_proc_t100_message(data, message);
#endif
		mxt_t100_int = true;
	} else if (report_id == data->T19_reportid) {

	} else if (report_id == data->T25_reportid) {
		mxt_proc_t25_messages(data, message);
	} else if (report_id >= data->T63_reportid_min
			&& report_id <= data->T63_reportid_max) {
	} else if (report_id >= data->T42_reportid_min
			&& report_id <= data->T42_reportid_max) {
		mxt_proc_t42_messages(data, message);
	} else if (report_id == data->T48_reportid) {
		mxt_proc_t48_messages(data, message);
	} else if (report_id >= data->T15_reportid_min
			&& report_id <= data->T15_reportid_max) {
		mxt_proc_t15_messages(data, message);
	} else if ( report_id == data->T24_reportid) {
		mxt_proc_t24_messages(data, message);
	} else if (report_id >= data->T68_reportid_min
			&& report_id <= data->T68_reportid_max) {
		mxt_proc_t68_messages(data, message);
	}else if (report_id >= data->T61_reportid_min
			&& report_id <= data->T61_reportid_max) {
		mxt_proc_t61_messages(data, message);
	} else if (report_id >= data->T70_reportid_min
			&& report_id <= data->T70_reportid_max) {
		mxt_proc_t70_messages(data, message);
	}
	else if (report_id >= data->T72_reportid_min
			&& report_id <= data->T72_reportid_max) {
		mxt_proc_t72_messages(data, message);
	} else if (report_id >= data->T81_reportid_min
			&& report_id <= data->T81_reportid_max) {
		mxt_proc_T81_messages(data, message);
	} else if (report_id == data->T92_reportid) {
		mxt_proc_T92_messages(data, message);
	} else if (report_id == data->T93_reportid) {
		mxt_proc_T93_messages(data, message);
	} else if (report_id >= data->T97_reportid_min
			&& report_id <= data->T97_reportid_max) {
		mxt_proc_t97_messages(data, message);
	} else if (report_id == data->T99_reportid) {
		mxt_proc_T99_messages(data, message);
	} else if (report_id == data->T102_reportid) {
		mxt_proc_t102_messages(data, message);
	} else if (report_id == data->T115_reportid) {
		mxt_proc_T115_messages(data, message);
	} else if (report_id == data->T124_reportid) {
		mxt_proc_T124_messages(data, message);
	}else if (report_id == data->T125_reportid) {
		mxt_proc_T125_messages(data, message);
	}
	else {
		dump = true;
	}

	if (dump || report_id > data->max_reportid)
		mxt_dump_message(data, message);

	if (data->debug_v2_enabled && report_id <= data->max_reportid)
		mxt_debug_msg_add(data, message);

	return 1;
}

static int mxt_read_and_process_messages(struct mxt_data *data, u8 count)
{
	int ret;
	int i;
	u8 num_valid = 0;

	/* Safety check for msg_buf */
	if (count > data->max_reportid)
		return -EINVAL;

	/* Process remaining messages if necessary */
	ret = __mxt_read_reg_ext(data, data->addr, data->T5_address,
				data->T5_msg_size * count, data->msg_buf, I2C_ACCESS_R_REG_FIXED);
	if (ret) {
		TS_LOG_ERR("Failed to read %u messages (%d)\n", count, ret);
		return ret;
	}

	for (i = 0;  i < count; i++) {
		ret = mxt_proc_message(data,
			data->msg_buf + data->T5_msg_size * i);

		if (ret == 1)
			num_valid++;
	}

	/* return number of messages read */
	return num_valid;
}

static int mxt_process_messages_t44(struct mxt_data *data)
{
	int ret;
	u8 count, num_left;

	/* Read T44 and T5 together */
	ret = __mxt_read_reg(data, data->T44_address,
		data->T5_msg_size + 1, data->msg_buf);
	if (ret) {
		TS_LOG_ERR("Failed to read T44 and T5 (%d)\n", ret);
		return ret;
	}

	count = data->msg_buf[0];

	if (count == 0) {
		TS_LOG_INFO("Interrupt triggered but zero messages\n");
		return 0;
	} else if (count > data->max_reportid) {
		TS_LOG_ERR("T44 count %d exceeded max report id\n", count);
		count = data->max_reportid;
	}

	/* Process first message, T5 */
	ret = mxt_proc_message(data, data->msg_buf + 1);
	if (ret < 0) {
		TS_LOG_ERR("Unexpected invalid message\n");
		return ret;
	}

	num_left = count - 1;

	/* Process remaining messages if necessary */
	if (num_left) {
		ret = mxt_read_and_process_messages(data, num_left);
		if (ret < 0) {
			TS_LOG_ERR("mxt_read_and_process_messages failed\n");
			goto end;
		}
		else if (ret != num_left)
			TS_LOG_ERR("Unexpected invalid message\n");
	}

end:
	return 0;
}

static int mxt_process_messages(struct mxt_data *data)
{
	int total_handled, num_handled;
	u8 count = data->last_message_count;

	if (count < 1 || count > data->max_reportid)
		count = 1;

	/* include final invalid message */
	total_handled = mxt_read_and_process_messages(data, count + 1);
	if (total_handled < 0)
		return 0;
	/* if there were invalid messages, then we are done */
	else if (total_handled <= count)
		goto update_count;

	/* read two at a time until an invalid message or else we reach
	 * reportid limit */
	do {
		num_handled = mxt_read_and_process_messages(data, 2);
		if (num_handled < 0)
			return 0;

		total_handled += num_handled;

		if (num_handled < 2)
			break;
	} while (total_handled < data->num_touchids);

update_count:
	data->last_message_count = total_handled;

	return 0;
}

static int mxt_interrupt(struct mxt_data *data)
{
	int ret;

	ret = mxt_process_messages_t44(data);

	return ret;
}

int process_messages(struct mxt_data *data, int timeout)
{
	do {
		msleep(2);
		mxt_process_messages_t44(data);
		timeout --;
		if (!timeout) {
			TS_LOG_INFO("process_messages timeout\n");
			return -1;
		}
	}while(data->msg_buf[0]);

	return 0;
}

static int atmel_irq_bottom_half(struct ts_cmd_node *in_cmd, struct ts_cmd_node *out_cmd)
{
	struct mxt_data *data = mxt_g_data;

	int ret = NO_ERR;
	struct ts_fingers *cache = &out_cmd->cmd_param.pub_params.algo_param.info;
	data->ts_cache = cache;
	mxt_t100_int = false;
	ret = mxt_interrupt(data);
	if (ret) {
		TS_LOG_ERR("mxt_interrupt failed\n");
		return -EBUSY;
	}
	if (mxt_t100_int) {
		out_cmd->command = TS_INPUT_ALGO;
		out_cmd->cmd_param.pub_params.algo_param.algo_order = data->chip_data->algo_id;
		TS_LOG_DEBUG("order: %d\n", out_cmd->cmd_param.pub_params.algo_param.algo_order);
	}
	return NO_ERR;
}
static int atmel_print_chip_info(void)
{
	struct mxt_data *data = mxt_g_data;
	struct mxt_object *t38;
	u8 version_byte[8];
	int ret = 0;

	if(!data){
		TS_LOG_ERR("%s return due to null data\n", __func__);
		return -ENODEV;
	}

	t38=mxt_get_object(data, MXT_SPT_USERDATA_T38);
	if( !t38 ) {
		TS_LOG_ERR("%s return due to null t38\n", __func__);
		return -EINVAL;
	}

	ret = __mxt_read_reg(data , t38->start_address , sizeof(version_byte) , version_byte);
	if( ret ) {
		TS_LOG_ERR("%s failed to read t38\n", __func__);
		return ret;
	}
	TS_LOG_INFO("FW%02d.%02x_CFG%02d.%02d_%02d%02d%02d\n",
		version_byte[1], version_byte[2], version_byte[3], version_byte[4], version_byte[5], version_byte[6], version_byte[7]);
	return ret;
}

static int atmel_fw_update_boot(char *file_name)
{
	struct mxt_data *data = mxt_g_data;
	int error = NO_ERR;

	if (!data)
		return -ENODEV;

	TS_LOG_INFO("fw/cfg update starting!\n");
	atmel_print_chip_info();
	mxt_update_fw_file_name(data, &data->fw_name);

	error = mxt_check_firmware_version(data);
	if (error) {
		TS_LOG_INFO("no need to update fw\n");
	} else {
		//lock it for disable outside access
		mutex_lock(&data->access_mutex);
		error = mxt_load_fw(data);
		mutex_unlock(&data->access_mutex);
		if (error) {
			TS_LOG_ERR("The firmware update failed(%d)\n", error);
		#if defined (CONFIG_HUAWEI_DSM)
			if(!dsm_client_ocuppy(tp_dclient)){
				dsm_client_record(tp_dclient, "fw update result: failed.\nupdata_status is %d.\n",\
				g_ts_data.dsm_info.constraints_UPDATE_status);
				dsm_client_notify(tp_dclient, DSM_TP_FWUPDATE_ERROR_NO);
			}
			strncpy(g_ts_data.dsm_info.fw_update_result, "failed", strlen("failed"));
		#endif
		} else {
			error = mxt_initialize_info_block(data);
			if (error){
				TS_LOG_ERR("mxt_initialize_info_block failed(%d)\n", error);
				return error;
			}
			TS_LOG_INFO("The firmware update succeeded\n");
		}
	}
 	error = mxt_update_cfg(data);
	if (error){
		TS_LOG_ERR("mxt_update_cfg failed(%d)\n", error);
		return error;
	}
	if(featurefile_read_success == 0){
		atmel_init_feature_file(false);
	}

	mxt_soft_reset(data);
	TS_LOG_INFO("fw/cfg update ending!\n");
	atmel_print_chip_info();

	if (!strncmp("NULL", data->module_id, strlen("NULL"))) {
		TS_LOG_INFO("again get module name and parse module\n");
		error = mxt_get_module_name();
		if (error) {
			TS_LOG_ERR("atmel init get lockdown info failed\n");
		}

		mxt_parse_module_dts(data->chip_data);
	}
	return error;
}

static int atmel_fw_update_sd(void)
{
	update_sd_mode = 1;
	mxt_disable_all_features();
	atmel_fw_update_boot(NULL);
	update_sd_mode = 0;
	return 0;
}

int mxt_get_module_name(void)
{
    int ret;
	struct mxt_data *data = mxt_g_data;
	struct pds_code *code = NULL;

	code = kzalloc(sizeof(struct pds_code), GFP_KERNEL);
	if (!code) {
		TS_LOG_ERR("malloc failed\n");
		ret = -ENOMEM;
		goto out;
	}

	code->module_name = NULL;
	ret = mxt_pds_get_data(data, code);
	if( ret ) {
		TS_LOG_ERR("%s failed to read pds\n", __func__);
	}

	memcpy(data->module_id, code->id, MISC_PDS_DATA_LEN);
out:
	if (code != NULL) {
		kfree(code);
	}

	return ret;
}

static int atmel_chip_get_info(struct ts_chip_info_param *info)
{
	struct mxt_data *data = mxt_g_data;
	struct mxt_object *t38;
	u8 version_byte[8];
	int ret = 0;

	if(!data){
		TS_LOG_ERR("%s return due to null data\n", __func__);
		return -ENODEV;
	}

	t38=mxt_get_object(data, MXT_SPT_USERDATA_T38);
	if( !t38 ) {
		TS_LOG_ERR("%s return due to null t38\n", __func__);
		return -EINVAL;
	}

	ret = __mxt_read_reg(data , t38->start_address , sizeof(version_byte) , version_byte);
	if( ret ) {
		TS_LOG_ERR("%s failed to read t38\n", __func__);
		return ret;
	}

	mxt_get_module_name();

	//snprintf(info->chip_name, sizeof(info->chip_name), "%s", "Touch");
	snprintf(info->ic_vendor, sizeof(info->ic_vendor), "Atmel-%s",  mxt_g_data->module_id);
	snprintf(info->fw_vendor, sizeof(info->fw_vendor), "FW%02d.%02x_CFG%02d.%02d_%02d%02d%02d",
		version_byte[1], version_byte[2], version_byte[3], version_byte[4], version_byte[5], version_byte[6], version_byte[7]);
	snprintf(info->mod_vendor, sizeof(info->mod_vendor), "%s", mxt_g_data->module_name);
	TS_LOG_INFO("ic_vendor: %s, fw_vendor: %s, mod_vendor: %s\n", info->ic_vendor, info->fw_vendor, info->mod_vendor);

	return ret;
}

static int atmel_before_suspend(void)
{
	TS_LOG_INFO("%s \n", __func__);

	return 0;
}

static int mxt_process_messages_until_invalid(struct mxt_data *data)
{
	int count, read;

	count = data->max_reportid;

	/* Read messages until we force an invalid */
	do {
		read = mxt_read_and_process_messages(data, 1);
		if (read < 1)
			return 0;
	} while (--count);

	TS_LOG_ERR("CHG pin isn't cleared\n");
	return -EBUSY;
}

/*
 *Function for checking t70 messages when the interrupt is disabled.
 *
 *T70 is an object which dynamicly configs the maxTouch devices.
 *
 */
int mxt_get_t70_msg(struct mxt_data *data)
{
	int i;
	mxt_soft_reset(data);
	mxt_t6_command(data, MXT_COMMAND_REPORTALL, 1, false);
	data->t70_msg_processed =0;
	mdelay(100);
	for ( i = 0 ; i < MXT_T70_PROCESS_RETRY ; i ++ ) {
		process_messages(data, MXT_T70_PROCESS_TIMEOUT);
		if (data->t70_msg_processed == 1) {
			break;
		}
	}

	if ( i == MXT_T70_PROCESS_RETRY) {
		TS_LOG_INFO("mxt_get_t70_msg fail\n");
		return 0;
	}
	return 1;
}

static void mxt_start(struct mxt_data *data, bool resume)
{
	if (!data->suspended || data->in_bootloader) {
		TS_LOG_DEBUG("mxt_start exit, suspend:%d, in_bootloader:%d\n", data->suspended, data->in_bootloader);
		return;
	}

	TS_LOG_INFO("mxt_start +\n");

	if (data->use_regulator && !g_tp_power_ctrl) {
		TS_LOG_DEBUG("atmel regulator enable\n");
		mxt_regulator_enable(data);
	} else {
		mxt_process_messages_until_invalid(data);
		mxt_set_t7_power_cfg(data, MXT_POWER_CFG_RUN);
		mxt_soft_reset(data);
		mxt_t6_command(data, MXT_COMMAND_CALIBRATE, 1, false);
	}

	data->enable_reporting = true;
	data->suspended = false;
}

static void mxt_stop(struct mxt_data *data,bool suspend)
{
	int ret = 0;

	if (data->suspended || data->in_bootloader) {
		TS_LOG_DEBUG("mxt_stop exit, suspend:%d, in_bootloader:%d\n", data->suspended, data->in_bootloader);
		return;
	}

	TS_LOG_INFO("mxt_stop, called in suspend\n");

	data->enable_reporting = false;

	if (data->use_regulator && !g_tp_power_ctrl) {
		TS_LOG_DEBUG("atmel regulator disable\n");
		ret = pinctrl_select_state(data->pctrl, data->pins_idle);
		if (ret < 0) {
			TS_LOG_ERR("set iomux normal error, %d\n", ret);
		}
		mxt_regulator_disable(data);
	} else{
		mxt_set_t7_power_cfg(data, MXT_POWER_CFG_DEEPSLEEP);
	}

	if (suspend) {
		if (ret == -EBUSY) {
			TS_LOG_INFO("mxt_stop: set wakeup enable\n");
			//msleep(200);
			mxt_process_messages_until_invalid(data);
		}
	}

	data->suspended = true;
}

static int atmel_suspend(void)
{
	int error = NO_ERR;
	struct mxt_data *data = mxt_g_data;

	TS_LOG_INFO("atmel_suspend +\n");
	switch (data->chip_data->easy_wakeup_info.sleep_mode) {
	case TS_POWER_OFF_MODE:
		/*for in_cell, tp will power off in suspend.*/
		if (data->chip_data->is_in_cell) {
			/*power on and off in lcd*/
			mxt_stop(data, true);
		}
		break;
	/*for gesture wake up mode suspend.*/
	case TS_GESTURE_MODE:
		break;
	default:
		TS_LOG_ERR("no suspend mode\n");
		return -EINVAL;
	}

	TS_LOG_INFO("atmel_suspend -\n");
	return error;
}

static int atmel_resume(void)
{
	int error = NO_ERR;
	struct mxt_data *data = mxt_g_data;

	TS_LOG_INFO("atmel_resume +\n");
	switch (data->chip_data->easy_wakeup_info.sleep_mode) {
	case TS_POWER_OFF_MODE:
		/*for in_cell, tp should power on in resume.*/
		if (data->chip_data->is_in_cell) {
			mxt_start(data, true);
		}
		break;
	case TS_GESTURE_MODE:
		break;
	default:
		TS_LOG_ERR("no resume mode\n");
		return -EINVAL;
	}

	TS_LOG_INFO("atmel_resume -\n");
	return error;
}

void atmel_status_resume(void)
{
	struct mxt_data *data = mxt_g_data;
	struct ts_feature_info* info = &g_ts_data.feature_info;

	mxt_disable_all_features();
	mxt_t6_command(data, MXT_COMMAND_RESET, MXT_RESET_VALUE, false);
	msleep(105);

	if (MXT_FEATURE_ENABLE == info->glove_info.glove_switch) {
		mxt_enable_feature(data, MAX_GLOVE_CONF);
	}

	if (MXT_FEATURE_ENABLE == info->holster_info.holster_switch) {
		if (MXT_FEATURE_ENABLE == info->glove_info.glove_switch) {
			mxt_disable_feature(data, MAX_GLOVE_CONF);
		}
		mxt_enable_feature(data, MAX_COVER_CONF);
	}

	if (info->roi_info.roi_supported){
		if (MXT_FEATURE_ENABLE == info->roi_info.roi_switch){
			mxt_enable_feature(data, MAX_KNUCKLE_CONF);
		}
	}

#if defined(HUAWEI_CHARGER_FB)
	if (info->charger_info.charger_supported) {
		if (MXT_FEATURE_ENABLE == info->charger_info.charger_switch){
			mxt_enable_feature(data, MAX_WORKAROUND5_CONF);
		}
	}
#endif
}

static int atmel_fw_check_after_resume(void)
{
	int retval = 0;
	struct mxt_data *data = mxt_g_data;
	struct mxt_info *info;

	//read the info block from the chip again
	info = kzalloc(sizeof(struct mxt_info), GFP_KERNEL);
	if (!info) {
		TS_LOG_ERR("Failed to allocate memory\n");
		return -ENOMEM;
	}
	retval = __mxt_read_reg(data, 0, sizeof(struct mxt_info), info);
	if (retval) {
		TS_LOG_ERR("%s, Failed to get fw info\n", __func__);
		kfree(info);
		return retval;
	}
	TS_LOG_INFO( "Current firmware V%u.%u.%02X . Former firmware V%u.%u.%02X\n",
		 info->version >> 4, info->version & 0xf,
		 info->build,
		 data->info->version >> 4, data->info->version & 0xf,
		 data->info->build
		 );

	if(info->version != data->info->version
		||info->build != data->info->build){
		retval = MXT_DRIVER_NEED_UPDATE_MESSAGE;
	}

	kfree(info);
	return retval;
}

static int atmel_after_resume(void *feature_info)
{
	struct mxt_data *data = mxt_g_data;
	int retval = NO_ERR;

	msleep(100);
	retval = atmel_fw_check_after_resume();
	TS_LOG_INFO("%s + atmel_fw_check_after_resume retval=%d\n", __func__, retval);
	if(MXT_DRIVER_NEED_UPDATE_MESSAGE == retval){
		retval = mxt_initialize(data);
		if (retval){
			TS_LOG_ERR("%s, Failed to initialize touch device\n", __func__);
			return retval;
		}
	}
	atmel_status_resume();
	mdelay(10);
	TS_LOG_INFO("%s - status count is: stable: %d, noise: %d, very noise: %d\n", __func__, mxt_g_data->sta_cnt.stable_state, mxt_g_data->sta_cnt.noise_state, mxt_g_data->sta_cnt.vnoise_state);
	return retval;
}

static int mxt_dualX_resume(struct mxt_data *data, u8 *dualX_status)
{
	int retval = NO_ERR;

	retval += mxt_write_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_STABCTRL, dualX_status[0]);
	retval += mxt_write_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_NOISCTRL, dualX_status[1]);
	retval += mxt_write_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_VNOICTRL, dualX_status[2]);

	TS_LOG_DEBUG("T72 recover dualX setting: STABLE: %d, NOISE:  %d, VNOISE:  %d\n",
					dualX_status[0],
					dualX_status[1],
					dualX_status[2]);
	return retval;
}

static int mxt_dualX_disable(struct mxt_data *data, u8 *dualX_status)
{
	int retval = NO_ERR;
	u8 tmp_dualX_status[3] = {0};

	retval += mxt_read_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_STABCTRL, dualX_status);
	retval += mxt_read_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_NOISCTRL, dualX_status+1);
	retval += mxt_read_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_VNOICTRL, dualX_status+2);

	tmp_dualX_status[0] = dualX_status[0]&(~MXT_T72_NOISE_SUPPRESSION_DUALXMODE);
	tmp_dualX_status[1] = dualX_status[1]&(~MXT_T72_NOISE_SUPPRESSION_DUALXMODE);
	tmp_dualX_status[2] = dualX_status[2]&(~MXT_T72_NOISE_SUPPRESSION_DUALXMODE);

	retval += mxt_write_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_STABCTRL, tmp_dualX_status[0]);
	retval += mxt_write_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_NOISCTRL, tmp_dualX_status[1]);
	retval += mxt_write_object(data, MXT_PROCG_NOISESUPPRESSION_T72, MXT_T72_NOISE_SUPPRESSION_VNOICTRL, tmp_dualX_status[2]);

	TS_LOG_DEBUG("T72 original dualX setting is: STABLE: %d, NOISE:  %d, VNOISE:  %d\n",
					dualX_status[0],
					dualX_status[1],
					dualX_status[2]);
	TS_LOG_DEBUG("T72 set dualX setting to: STABLE: %d, NOISE:  %d, VNOISE:  %d\n",
					tmp_dualX_status[0],
					tmp_dualX_status[1],
					tmp_dualX_status[2]);
	return retval;
}

static int atmel_get_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd)
{
	struct mxt_data *data = mxt_g_data;
	int retval = NO_ERR;
	int ret1,ret2,ret3;
	int cmd;
	size_t offset;
	size_t T37_buf_size = 0;
	int refs_data_uplimit = data->chip_data->raw_limit_buf[RAW_DATA_UP];
	int refs_data_lowlimit = data->chip_data->raw_limit_buf[RAW_DATA_LOW];
	int deltas_data_uplimit = data->chip_data->raw_limit_buf[DELT_DATA_UP];
	int deltas_data_lowlimit = data->chip_data->raw_limit_buf[DELT_DATA_LOW];
	int refs_rx2rx_uplimit = data->chip_data->raw_limit_buf[RX_TO_RX_UP];
	int refs_rx2rx_lowlimit = data->chip_data->raw_limit_buf[RX_TO_RX_LOW];
	int refs_tx2tx_uplimit = data->chip_data->raw_limit_buf[TX_TO_TX_UP];
	int refs_tx2tx_lowlimit = data->chip_data->raw_limit_buf[TX_TO_TX_LOW];
	int max_minus_min_limit =  data->max_minus_min_limit;
	char max_min_aver_buf[50] = {0};
	int retry_count1 = 3;
	int retry_count2 = 3;
	u8 dualX_status[3] = {0};

#ifdef ROI
 /**ATTENTION : Should be set to MXT_T6_CMD58_ON in each return branch**/
       gMxtT6Cmd58Flag = MXT_T6_CMD58_OFF;
#endif

#if 0
	retval = mxt_t6_command(data, MXT_COMMAND_RESET, MXT_RESET_VALUE, false);
	if (retval) {
		memcpy(info->result, "0F", strlen("0F"));
		goto out;
	}
	memcpy(info->result, "0P", strlen("0P"));
	mdelay(105);
#endif

	retval = mxt_dualX_disable(data, dualX_status);
	if (retval) {
		TS_LOG_ERR("mxt_dualX_disable error\n");
		memcpy(info->result, "0F", strlen("0F"));
		goto out;
	}
	memcpy(info->result, "0P", strlen("0P"));
	msleep(100);

	retval = mxt_read_t100_config(data);
	if (retval) {
		TS_LOG_ERR("mxt_read_t100_config error\n");
		goto out;
	}

	T37_buf_size = (data->x_size -data->x_origin) * (data->y_size -data->y_origin) * sizeof(int);

	TS_LOG_DEBUG("%s: x = %d , y = %d\n Read ref*********************************\n" , __func__ , (data->info->matrix_xsize) , (data->info->matrix_ysize));
	data->T37_buf_size = T37_buf_size;
	data->T37_buf = kmalloc(data->T37_buf_size, GFP_KERNEL);
	if (!data->T37_buf) {
		TS_LOG_ERR("alloc T37 buf failed\n");
		retval = -ENOMEM;
		goto out;
	}

	info->buff[0] = data->y_size - data->y_origin;//rx
	info->buff[1] = data->x_size - data->x_origin;//tx
	cmd = MXT_T6_DEBUG_REF;

	TS_LOG_DEBUG("\n\n\n%s: x = %d , y = %d\n Read del*********************************\n" , __func__ , (data->info->matrix_xsize) , (data->info->matrix_ysize));

	do {
		retval = mxt_T37_fetch(data, cmd);
		if(!retval) {
			TS_LOG_INFO("mxt_T37_fetch read success\n");
			break;
		}
		mdelay(5);
		TS_LOG_INFO("try remainning %d times\n", retry_count1-1);
	} while(retry_count1 --);
	if (retval) {
		TS_LOG_ERR("mxt_T37_fetch read failed,already try %d times\n",3-retry_count1);
		goto out;
	}

	ret1 = get_refs_or_deltas_data_test(data, refs_data_uplimit, refs_data_lowlimit);
	ret2 = mxt_t25_selftest(data);
	if (ret1&ret2) {
		strncat(info->result, "-1P", strlen("-1P"));
	} else{
		TS_LOG_ERR("raw data test failed\n");
		strncat(info->result, "-1F", strlen("-1F"));
	}
	data->refs_delta_data.refs_data_Average = data->refs_delta_data.Average;
	data->refs_delta_data.refs_data_MaxNum = data->refs_delta_data.MaxNum;
	data->refs_delta_data.refs_data_MinNum = data->refs_delta_data.MinNum;

	memcpy(&info->buff[2], data->T37_buf, data->T37_buf_size);

	ret1 = get_refs_rx2rx_delta_test(data, refs_rx2rx_uplimit, refs_rx2rx_lowlimit);
	ret2 = get_refs_tx2tx_delta_test(data, refs_tx2tx_uplimit, refs_tx2tx_lowlimit);
	ret3 = get_refs_max_minus_min_test(data, max_minus_min_limit);
	if (ret1&ret2&ret3){
		strncat(info->result, "-2P", strlen("-2P"));
	} else {
		TS_LOG_ERR("delta test failed\n");
		strncat(info->result, "-2F", strlen("-2F"));
	}

	retval = mxt_dualX_resume(data, dualX_status);
	if (retval) {
		TS_LOG_ERR("mxt_dualX_resume error\n");
		goto out;
	}
	msleep(150);

	offset = (data->T37_buf_size)/(sizeof(int));
	cmd = MXT_T6_DEBUG_DELTA;
	memset(data->T37_buf, 0, data->T37_buf_size);

	do {
		retval = mxt_T37_fetch(data, cmd);
		if(!retval) {
			TS_LOG_INFO("mxt_T37_fetch read success\n");
			break;
		}
		mdelay(5);
		TS_LOG_INFO("try remainning %d times\n", retry_count2-1);
	} while(retry_count2 --);

	retval = get_refs_or_deltas_data_test(data, deltas_data_uplimit, deltas_data_lowlimit);
	if (retval) {
		strncat(info->result, "-3P", strlen("-3P"));
	} else{
		TS_LOG_ERR("noise test failed\n");
		strncat(info->result, "-3F", strlen("-3F"));
	}
	strncat(info->result, "-4P", strlen("-4P"));
	retval = NO_ERR;
	data->refs_delta_data.deltas_data_Average = data->refs_delta_data.Average;
	data->refs_delta_data.deltas_data_MaxNum = data->refs_delta_data.MaxNum;
	data->refs_delta_data.deltas_data_MinNum = data->refs_delta_data.MinNum;
	mxt_get_t70_msg(data);
	if((MXT_SYNC_OK != data->vsyncstatus) ||(MXT_SYNC_OK != data->hsyncstatus)){
		TS_LOG_ERR("Sync lost, V%d, H%d\n" , data->vsyncstatus , data->hsyncstatus);
		memset(&info->buff[2], -1 , data->T37_buf_size);
	}
	memcpy(&info->buff[2+offset], data->T37_buf, data->T37_buf_size);

	info->used_size = (info->buff[0])*(info->buff[1])*2 + 2;

	get_average_max_min_data(data, max_min_aver_buf);
	strncat(info->result, max_min_aver_buf, strlen(max_min_aver_buf));

	strncat(info->result, ";", strlen(";"));
	if (0 == strlen(info->result) || strstr(info->result, "F")) {
		strncat(info->result, "panel_reason", strlen("panel_reason"));
	}

	strncat(info->result, mxt_g_data->description, strlen(mxt_g_data->description));
	strncat(info->result, "-atmel_touch", strlen("-atmel_touch"));

	if (data->T37_buf) {
		kfree(data->T37_buf);
		data->T37_buf = NULL;
		data->T37_buf_size = 0;
	}

out:
#ifdef ROI
       gMxtT6Cmd58Flag = MXT_T6_CMD58_ON;
#endif
	if (retval) {
		TS_LOG_ERR("all three tests failed\n");
		strncat(info->result, "-1F-2F-3F", strlen("-1F-2F-3F"));
	}
	return retval;
}

static void atmel_shutdown(void)
{
	int error = NO_ERR;
	struct mxt_data *data = mxt_g_data;

	error = pinctrl_select_state(data->pctrl, data->pins_idle);
	if (error < 0) {
		TS_LOG_ERR("set iomux normal error, %d\n", error);
	}

	mxt_regulator_disable(data);
}

static int atmel_chip_get_capacitance_test_type(struct ts_test_type_info *info)
{
	int error = NO_ERR;
	struct mxt_data *data = mxt_g_data;

	if (!info) {
		TS_LOG_ERR("%s:info=%ld\n",__func__,PTR_ERR(info));
		error = -ENOMEM;
		return error;
	}
	switch (info->op_action) {
		case TS_ACTION_READ:
			memcpy(info->tp_test_type, data->chip_data->tp_test_type,TS_CAP_TEST_TYPE_LEN);
			TS_LOG_INFO("read_chip_get_test_type=%s, \n",info->tp_test_type);
			break;
		case TS_ACTION_WRITE:
			break;
		default:
			TS_LOG_ERR("invalid status: %s", info->tp_test_type);
			error = -EINVAL;
			break;
	}
	return error;
}

/*
 *Function for parsing feature file.
 *
 *Feature file is used to store feature configuration for the maxtouch devices.
 *
 */
static int mxt_search_string(char *orignalstring, int len, char c)
{
	int count = 0;
	int i=0;

	for(i =0; i<len;i++){
		if(orignalstring[i]==c)
			count++;
	}
	return count;
}

static void mxt_print_feature_info(char* func_name, struct feature_info* feature)
{
	int i;
	for( i = 0; i < feature->reg_num; i++){
		TS_LOG_DEBUG("%s, objectId: %d, instance: %d, offset: %d, newvalue: %d, oldvalue: %d\n", func_name,
				   feature->reg_value[i].objectId, feature->reg_value[i].instance,
				   feature->reg_value[i].offset, feature->reg_value[i].newvalue, feature->reg_value[i].oldvalue);
	}
}

static void mxt_get_feature_file_name(char *feature_file_name, bool from_sd)
{
	int offset;
	if (!from_sd) {
		offset = snprintf(feature_file_name, PAGE_SIZE, "ts/atmel/");
		offset += snprintf(feature_file_name+offset, PAGE_SIZE-offset, g_ts_data.product_name);
		snprintf(feature_file_name+offset, PAGE_SIZE-offset, "_config_feature.raw");
	} else {
		offset = snprintf(feature_file_name, PAGE_SIZE, "../../../sdcard/update/config_feature.raw");
	}
	TS_LOG_INFO("%s: feature_file_name is %s\n", __func__, feature_file_name);
}

static int mxt_write_file_config_for_feature(struct feature_info* feature)
{
	struct mxt_data *data = mxt_g_data;
	int i;
	int ret = NO_ERR;
	for( i = 0; i < feature->reg_num; i++ ){
		ret = mxt_write_obj_instance( data ,
						   feature->reg_value[i].objectId ,
						   feature->reg_value[i].instance,
						   feature->reg_value[i].offset ,
						   (feature->reg_value[i].newvalue) );
		if (ret){
			TS_LOG_ERR("%s, enable function failed\n", __func__);
			feature->on_flag = MXT_FEATURE_SETERROR;
			goto out;
		}
	}
	mxt_print_feature_info(__func__, feature);

out:
	return ret;
}

static int mxt_write_dev_config_for_feature(struct feature_info* feature)
{
	struct mxt_data* data = mxt_g_data;
	int i;
	int ret = NO_ERR;

	for( i = 0; i < feature->reg_num;  i ++ ){

		ret = mxt_write_obj_instance( data ,
						  feature->reg_value[i].objectId ,
						   feature->reg_value[i].instance,
						   feature->reg_value[i].offset ,
						   (feature->reg_value[i].oldvalue));
		if (ret){
			TS_LOG_ERR("%s, disable function failed\n", __func__);
			feature->on_flag = MXT_FEATURE_SETERROR;
			goto out;
		}
	}
	mxt_print_feature_info(__func__, feature);

out:
	return ret;
}

static int mxt_store_dev_config_for_feature(struct feature_info* feature)
{
	struct mxt_data* data = mxt_g_data;
	int ret = NO_ERR;
	int i;

	for( i = 0  ; i < feature->reg_num;  i++ ){
		ret = mxt_read_obj_instance( data ,
					  feature->reg_value[i].objectId,
					  feature->reg_value[i].instance,
					  feature->reg_value[i].offset,
					  &(feature->reg_value[i].oldvalue) );
		if (ret) {
			TS_LOG_ERR("%s, read tp register error!", __func__);
			goto out;
		}
	}
	mxt_print_feature_info(__func__, feature);

out:
	return ret;
}

static void parse_extra_feature_cover(struct feature_info* feature)
{
	int i;

	for(i = 0; i< feature->reg_num; i++){
		if(feature->reg_value[i].objectId == MXT_SPT_USERDATA_T38
			&&feature->reg_value[i].offset == T38COVERGLASSFL
			&&feature->reg_value[i].newvalue == 1){
			mxt_g_data->feature_extra_data.cover_glass = true;
		}

		if (feature->reg_value[i].objectId == MXT_SPT_USERDATA_T38
			&&feature->reg_value[i].offset == T38COVERCUT
			&&feature->reg_value[i].newvalue != 0) {
			mxt_g_data->feature_extra_data.cover_cut = true;
		}

		if (feature->reg_value[i].objectId == MXT_SPT_USERDATA_T38
			&&feature->reg_value[i].offset == T38COVERSUPWIDL) {
			mxt_g_data->feature_extra_data.cover_sup_l = feature->reg_value[i].newvalue;
		}

		if (feature->reg_value[i].objectId == MXT_SPT_USERDATA_T38
			&&feature->reg_value[i].offset == T38COVERSUPWIDH) {
			mxt_g_data->feature_extra_data.cover_sup_h = feature->reg_value[i].newvalue;
		}
	}

	TS_LOG_INFO("%s: cover_glass is %d, cover_cut, and h, l is %d(%03d,%03d)\n", __func__, mxt_g_data->feature_extra_data.cover_glass, mxt_g_data->feature_extra_data.cover_cut, mxt_g_data->feature_extra_data.cover_sup_h, mxt_g_data->feature_extra_data.cover_sup_l);
}

static void parse_extra_feature_glove(struct feature_info* feature)
{
	int i;

	for(i = 0; i< feature->reg_num; i++){
		if (feature->reg_value[i].objectId == MXT_SPT_USERDATA_T38
			&&feature->reg_value[i].offset == T38GLOVESUPWIDL) {
			mxt_g_data->feature_extra_data.glove_sup_l = feature->reg_value[i].newvalue;
		}

		if (feature->reg_value[i].objectId == MXT_SPT_USERDATA_T38
			&&feature->reg_value[i].offset == T38GLOVESUPWIDH) {
			mxt_g_data->feature_extra_data.glove_sup_h = feature->reg_value[i].newvalue;
		}
	}

	TS_LOG_INFO("%s, glove_sup h, l is (%03d,%03d)\n", __func__, mxt_g_data->feature_extra_data.glove_sup_h, mxt_g_data->feature_extra_data.glove_sup_l);
}


static void parse_extra_feature(void)
{
	parse_extra_feature_glove(&mxt_feature_list[MAX_GLOVE_CONF]);
	parse_extra_feature_cover(&mxt_feature_list[MAX_COVER_CONF]);
}

static int mxt_parse_feature_file(struct firmware *cfg)
{
	int featurecode, feature_list_count;
	char feature_begin[32],  feature_end[32];
	int begin_pos, end_pos,  read_pos, regnum;
	int readobjectId, readinstance, readoffset, readnewvalue;
	int i, ret = NO_ERR;
	struct feature_info* feature;

	feature_list_count = sizeof(mxt_feature_list)/sizeof(struct feature_info);
	for( featurecode = 0 ; featurecode <  feature_list_count; featurecode++){
		feature = &mxt_feature_list[featurecode];

		TS_LOG_DEBUG("%30s", cfg->data);
		//get begin/end strings
		snprintf(feature_begin, sizeof(feature_begin), "[%s BEGIN]", feature->name);
		snprintf(feature_end, sizeof(feature_end), "[%s END]", feature->name);
		TS_LOG_DEBUG("feature_name: %s, feature_begin: %s,  feature_end: %s\n", feature->name, feature_begin, feature_end);

		//find begin/end postions
		begin_pos =strstr((char *)(cfg->data), feature_begin) -  (char *)(cfg->data);
		end_pos = strstr((char *)cfg->data , feature_end) - (char *)(cfg->data);
		if (-1 == begin_pos || -1 == end_pos){
		    TS_LOG_ERR("Failure find %s/%s in file\n", feature_begin, feature_end);
			ret = -EINVAL;
			goto out;
		}

		read_pos = begin_pos + strlen(feature_begin) + 2;
		regnum = mxt_search_string(cfg->data + read_pos, end_pos - read_pos, ';');
		TS_LOG_DEBUG("%s, begin_pos: %d, end_pos: %d, read_pos: %d, regnum: %d, old regnum :%d \n", __func__, begin_pos, end_pos, read_pos, regnum, feature->reg_num);

		if( NULL == feature->reg_value ){
			feature->reg_value = kmalloc(regnum * sizeof(struct feature_reg_value), GFP_KERNEL);
			if (NULL == feature->reg_value) {
				ret = -EINVAL;
				goto out;
			}
			TS_LOG_DEBUG("kmalloc for feature_value_point %d\n", featurecode);
		} else{
		    TS_LOG_DEBUG("feature_value_point %d had been malloced\n", featurecode);
		}
		feature->reg_num = regnum;

		//read feature setting
		for( i = 0; i < regnum; i++ ){
			sscanf(cfg->data + read_pos, "OBJECT=T%d,INSTANCE=%d,OFFSIZE=%d,VALUE=%d;\n", &readobjectId, &readinstance, &readoffset, &readnewvalue);
			feature->reg_value[i].objectId = (u8)readobjectId;
			feature->reg_value[i].instance= (u8)readinstance;
			feature->reg_value[i].offset = (u8)readoffset;
			feature->reg_value[i].newvalue = (u8)readnewvalue;
			//skip a line
			while(cfg->data[++read_pos] != '\n');
			read_pos++;
		}
	}

out:
	return ret;
}

static void mxt_init_mxt_feature_list(void)
{
	int i, num;
	struct feature_info* feature;

	num = sizeof(mxt_feature_list)/sizeof(struct feature_info);
	for( i = 0 ; i <  num; i++){
		feature = &mxt_feature_list[i];
		if( NULL != feature->reg_value ){
			kfree(feature->reg_value);
			feature->reg_value = NULL;
		}
	}
}

static int mxt_read_feature_file(bool from_sd)
{
	struct mxt_data *data = mxt_g_data;
	char feature_file_name[128];
	const struct firmware *cfg = NULL;
	int ret = NO_ERR;

	mxt_get_feature_file_name(feature_file_name, from_sd);
	ret = request_firmware(&cfg, feature_file_name, &data->ts_dev->dev);
	if (ret < 0) {
		TS_LOG_ERR("Failure to request file %s\n", feature_file_name);
		featurefile_read_success = 0;
		return ret;
	}

	mxt_init_mxt_feature_list();

	ret = mxt_parse_feature_file(cfg);
	if(ret){
		TS_LOG_ERR("Failure to mxt_parse_feature_file\n");
		goto release;
	}
	featurefile_read_success = 1;
	TS_LOG_INFO("%s return OK\n", __func__ );
release:
	release_firmware(cfg);
	return ret;
}

static int atmel_init_feature_file(bool from_sd)
{
	int ret;
	ret = mxt_read_feature_file(from_sd);
	if(ret){
		TS_LOG_ERR("%s mxt_read_feature_file fail\n", __func__);
		goto out;
	}
	parse_extra_feature();

out:
	return ret;
}

/*
 *Function for setting up extra features, such as glove, gesture, and kuckle knock.
 *
 *Different features have different configs, so the configs need updating to the mxt device when switching them on/off.
 *The config are stored in a file named XXX_config_feature.raw
 *
 */
static int mxt_set_feature(struct mxt_data *data, int featurecode , int enableflag)
{
	int ret = NO_ERR;
	struct feature_info* feature = &mxt_feature_list[featurecode];

	if(featurefile_read_success == 0){
		ret = atmel_init_feature_file(false);
		if(ret){
			TS_LOG_ERR("%s mxt_read_feature_file fail from sd\n", __func__);
			goto out;
		}
	}

	if(enableflag == MXT_FEATURE_ENABLE){
		if(MXT_FEATURE_DISABLE == feature->on_flag){
			ret = mxt_store_dev_config_for_feature(feature);
			if(ret){
				TS_LOG_ERR("%s mxt_store_dev_config_for_feature fail\n", __func__);
				goto out;
			}
		}
		ret = mxt_write_file_config_for_feature(feature);
		if(ret){
			TS_LOG_ERR("%s mxt_write_file_config_for_feature fail\n", __func__);
			goto out;
		}
	}else{
		if(MXT_FEATURE_ENABLE == feature->on_flag){
			ret = mxt_write_dev_config_for_feature(feature);
			if(ret){
				TS_LOG_ERR("%s mxt_write_dev_config_for_feature fail\n", __func__);
				goto out;
			}
		}
	}

out:
	TS_LOG_INFO("%s set func %s return %s, switch flag: %d, previouse flag: %d\n", __func__ , feature->name, ret?"NG":"OK", enableflag, feature->on_flag);

	if (!ret) {
		feature->on_flag = enableflag;
	}

	return ret;
}

static int mxt_enable_feature(struct mxt_data *data, int featurecode)
{
	return mxt_set_feature(data,featurecode,MXT_FEATURE_ENABLE);
}

static int mxt_disable_feature(struct mxt_data *data, int featurecode)
{
	return mxt_set_feature(data,featurecode,MXT_FEATURE_DISABLE);
}

static void mxt_disable_all_features()
{
	int i;
	int feature_list_count;

	feature_list_count = sizeof(mxt_feature_list)/sizeof(struct feature_info);
	for(i=0; i<feature_list_count; i++){
		if(MXT_FEATURE_ENABLE == mxt_feature_list[i].on_flag){
			mxt_disable_feature(mxt_g_data, i);
		}
	}
}

static void mxt_t72noise_switch(u8 t72noise_switch)
{
	struct mxt_data *data = mxt_g_data;

	switch(t72noise_switch){
		case MXT_FEATURE_ENABLE:
			memset(&mxt_g_data->t72_noise_level, 0, sizeof(struct t72_noise_level));
			mxt_enable_feature(data, MAX_WORKAROUND3_CONF);
			break;
		case MXT_FEATURE_DISABLE:
			mxt_disable_feature(data, MAX_WORKAROUND3_CONF);
			break;
		default:
			break;
	}
	return;
}

static void mxt_charger_switch(u8 charger_switch)
{
	struct mxt_data *data = mxt_g_data;

	switch(charger_switch){
		case MXT_FEATURE_ENABLE:
			mxt_enable_feature(data, MAX_WORKAROUND5_CONF);
			break;
		case MXT_FEATURE_DISABLE:
			mxt_disable_feature(data, MAX_WORKAROUND5_CONF);
			break;
		default:
			break;
	}
	return;
}

static int atmel_charger_switch(struct ts_charger_info *info)
{
	int retval = NO_ERR;

#if defined(HUAWEI_CHARGER_FB)
	if (!info) {
		TS_LOG_ERR("%s: info is Null\n", __func__);
		retval = -ENOMEM;
		return retval;
	}

	switch (info->op_action) {
		case TS_ACTION_WRITE:
			mxt_charger_switch(info->charger_switch);
			break;
		default:
			TS_LOG_INFO("%s, invalid cmd\n", __func__);
			retval = -EINVAL;
			break;
	}
#endif

	return retval;
}
static void mxt_glove_switch(u8 glove_switch)
{
	struct mxt_data *data = mxt_g_data;
	struct ts_feature_info* info = &g_ts_data.feature_info;

	switch(glove_switch){
		case MXT_FEATURE_ENABLE:
			mxt_enable_feature(data, MAX_GLOVE_CONF);
			break;
		case MXT_FEATURE_DISABLE:
			mxt_disable_all_features();
			mxt_t6_command(data, MXT_COMMAND_RESET, MXT_RESET_VALUE, false);
			msleep(105);

			if (info->roi_info.roi_supported){
				if (MXT_FEATURE_ENABLE == info->roi_info.roi_switch){
					mxt_enable_feature(data, MAX_KNUCKLE_CONF);
				}
			}

#if defined(HUAWEI_CHARGER_FB)
			if (info->charger_info.charger_supported) {
				if (MXT_FEATURE_ENABLE == info->charger_info.charger_switch){
					mxt_enable_feature(data, MAX_WORKAROUND5_CONF);
				}
			}
#endif
			break;
		default:
			break;
	}
	mxt_t6_command(data, MXT_COMMAND_CALIBRATE, 1, false);
}

static int atmel_chip_glove_switch(struct ts_glove_info *info)
{
	struct mxt_data *data = mxt_g_data;
	int retval = NO_ERR;

	if (!info) {
		TS_LOG_ERR("%s: info is Null\n" , __func__);
		retval = -ENOMEM;
		return retval;
	}

	TS_LOG_INFO("%s: operation is %d,glove_switch is %d\,status is %dn" , __func__, info->op_action,info->glove_switch,info->status);

	switch (info->op_action) {
		case TS_ACTION_WRITE:
			mxt_glove_switch(info->glove_switch);
			break;
		case TS_ACTION_READ:
			info->glove_switch = mxt_feature_list[MAX_GLOVE_CONF].on_flag;
			break;
		default:
			TS_LOG_INFO("%s invalid action: %d\n", __func__ , info->op_action);
			retval = -EINVAL;
			break;
	}
	return retval;

}

static void mxt_holster_switch(u8 holster_switch)
{
	struct mxt_data *data = mxt_g_data;
	struct ts_feature_info* info = &g_ts_data.feature_info;

	switch(holster_switch){
		case MXT_FEATURE_ENABLE:
			mxt_enable_feature(data, MAX_COVER_CONF);
			break;
		case MXT_FEATURE_DISABLE:
			mxt_disable_all_features();
			mxt_t6_command(data, MXT_COMMAND_RESET, MXT_RESET_VALUE, false);
			msleep(105);

			if (MXT_FEATURE_ENABLE == info->glove_info.glove_switch) {
				mxt_enable_feature(data, MAX_GLOVE_CONF);
			}

			if (info->roi_info.roi_supported){
				if (MXT_FEATURE_ENABLE == info->roi_info.roi_switch){
					mxt_enable_feature(data, MAX_KNUCKLE_CONF);
				}
			}

#if defined(HUAWEI_CHARGER_FB)
			if (info->charger_info.charger_supported) {
				if (MXT_FEATURE_ENABLE == info->charger_info.charger_switch){
					mxt_enable_feature(data, MAX_WORKAROUND5_CONF);
				}
			}
#endif
			break;
		default:
			break;
	}
}

static int atmel_chip_holster_switch(struct ts_holster_info *info)
{
	struct mxt_data *data = mxt_g_data;
	int retval = NO_ERR;

	if (!info) {
		TS_LOG_ERR("%s: info is Null\n" , __func__);
		retval = -ENOMEM;
		return retval;
	}

	TS_LOG_INFO("%s: operation is %d, holster_switch is %d, status is %d\n" , __func__, info->op_action, info->holster_switch, info->status);
	switch (info->op_action) {
		case TS_ACTION_WRITE:
			mxt_holster_switch(info->holster_switch);
			break;
		case TS_ACTION_READ:
			info->holster_switch = mxt_feature_list[MAX_COVER_CONF].on_flag;
			break;
		default:
			TS_LOG_INFO("%s invalid action: %d\n", __func__ , info->op_action);
			retval = -EINVAL;
			break;
	}
	return retval;

}

static unsigned char* atmel_roi_rawdata(void)
{
#ifdef ROI
	return roi_data;
#else
	return NULL;
#endif
}

static int atmel_read_roi_switch(struct ts_roi_info *info)
{
    info->roi_switch = mxt_feature_list[MAX_KNUCKLE_CONF].on_flag;
    return NO_ERR;
}


static int atmel_roi_switch(struct ts_roi_info *info)
{
	struct mxt_data *data = mxt_g_data;
	int retval = NO_ERR;

#ifdef ROI
	if (!info) {
		TS_LOG_ERR("%s: info is Null\n" , __func__);
		retval = -ENOMEM;
		return retval;
	}

	TS_LOG_INFO("%s: operation is %d\n" , __func__, info->op_action);
	switch (info->op_action) {
		case TS_ACTION_WRITE:
			mxt_set_feature(data, MAX_KNUCKLE_CONF, info->roi_switch);
			break;
		case TS_ACTION_READ:
			retval = atmel_read_roi_switch(info);
			break;
		default:
			TS_LOG_DEBUG("invalid roi switch(%d) action: %d\n", info->roi_switch, info->op_action);
			retval = -EINVAL;
			break;
	}
#endif
	return retval;
}

static int atmel_regs_operate(struct ts_regs_info *info)
{
	int retval = NO_ERR;
	unsigned short regs_base_addr = 0;
	u8 value[TS_MAX_REG_VALUE_NUM] = {0};
	u8 value_tmp = 0;
	int i = 0;
	struct mxt_data *data = mxt_g_data;

	if (!info) {
		TS_LOG_ERR("%s: info is Null\n" , __func__);
		retval = -ENOMEM;
		return retval;
	}

	value_tmp = info->values[0];

	TS_LOG_INFO("addr(%d),op_action(%d),bit(%d),num(%d)\n", info->addr, info->op_action, info->bit, info->num);

	for (i = 0; i < info->num; i ++) {
		TS_LOG_INFO("value[%d]=%d\n", i,info->values[i]);
	}
	switch (info->op_action) {
	case TS_ACTION_WRITE:
		for (i = 0; i < info->num; i++) {
			value[i] = info->values[i];
		}

		if ((1 == info->num)&&(8 > info->bit)) {
			retval = __mxt_read_reg(data, info->addr,info->num,value);
			if (retval < 0) {
				TS_LOG_ERR("TS_ACTION_READ error, addr(%d)\n", info->addr);
				retval = -EINVAL;
				goto out;
			}

			if (0 == value_tmp) {
				value[0] &=~(1 << info->bit);
			} else if (1 == value_tmp) {
				value[0] |= (1 << info->bit);
			}
		}

		retval = __mxt_write_reg(data, info->addr,info->num,value);
		if (retval < 0) {
			TS_LOG_ERR("TS_ACTION_WRITE error, addr(%d)\n", info->addr);
			retval = -EINVAL;
			goto out;
		}
		break;
	case TS_ACTION_READ:
		retval = __mxt_read_reg(data, info->addr,info->num,value);
		if (retval < 0) {
			TS_LOG_ERR("TS_ACTION_READ error, addr(%d)\n", info->addr);
			retval = -EINVAL;
			goto out;
		}

		if ((1 == info->num)&&(8 > info->bit)) {
			data->chip_data->reg_values[0] = (value[0] >>  info->bit)&0x01;
		} else {
			for (i = 0; i < info->num; i++) {
				data->chip_data->reg_values[i] = value[i];
			}
		}
		break;
	default:
		TS_LOG_ERR("%s, reg operate default invalid action %d\n", __func__, info->op_action);
		retval = -EINVAL;
		break;
	}
out:
	return retval;
}

static int atmel_debug_switch(u8 loglevel)
{
	int retval = NO_ERR;
	if (loglevel) {
		atmel_init_feature_file(true);
	} else {
		atmel_init_feature_file(false);
	}
	return retval;
}

static void atmel_special_hardware_test_switch(unsigned int value)
{
	struct mxt_data *data = mxt_g_data;

	switch(value){
		case MXT_FEATURE_ENABLE:
			memset(&mxt_g_data->t72_noise_level, 0, sizeof(struct t72_noise_level));
			mxt_g_data->t72_noise_level.noise_level_min = mxt_g_data->t72_noise_level_threshold;
			mxt_enable_feature(data, MAX_WORKAROUND3_CONF);
			break;
		case MXT_FEATURE_DISABLE:
			mxt_disable_feature(data, MAX_WORKAROUND3_CONF);
			break;
		default:
			break;
	}
	return;
}

static int atmel_special_hardware_test_result(char *buf)
{
	int ret = 0;
	int t72_test = 2;
	struct mxt_data *data = mxt_g_data;
	char test_status[][10] = {"pass", "fail", "time_limit"};

	int s_count = mxt_g_data->t72_noise_level.success_count;
	int t_count = mxt_g_data->t72_noise_level.total_count;
	int n_max = mxt_g_data->t72_noise_level.noise_level_max;
	int n_min = mxt_g_data->t72_noise_level.noise_level_min;

	if (t_count >= 5) {
		if (s_count * 2 >= t_count){
			t72_test = 0;
		} else {
			t72_test = 1;
		}
	}

	ret = snprintf(buf, MAX_HARDWARE_TEST_RESULT_LEN, "%s(s/toal %d/%d)(min:%d, max:%d)_t72_test\n", test_status[t72_test], s_count, t_count, n_min, n_max);
	TS_LOG_INFO("%s, resule:%s", __func__, buf);

	return ret;
}


