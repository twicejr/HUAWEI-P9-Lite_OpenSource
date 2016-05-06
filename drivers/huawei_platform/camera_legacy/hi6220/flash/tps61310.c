/*
 *  Hisilicon K3 soc camera v4l2 driver source file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/mux.h>
#include <linux/kernel.h>
#include <mach/gpio.h>
#include <linux/i2c.h>
//#include "k3_ispv1_io.h"
#include "sensor_common.h"
#include <mach/tps61310.h>
#include <linux/delay.h>
#include <linux/time.h>

#define LOG_TAG "K3_STROBE"

#define DEBUG_DEBUG 0
#include "cam_log.h"

static camera_flashlight tps61310_intf;
struct i2c_client *tps61310_client;

/*
 * record led select status
 * after reset, default LED2 enabled
 * led_select: x x x x x 1 1 1
 *                       | | |_ LED1 enable
 *                       | |___ LED2 enable 
 *                       |_____ LED3 enable
 */
static u8 led_select = 0x02;
static int reset_pin;
static int strobe0_pin;
static int strobe1_pin;

#define K3_FLASH_BLOCK	"block_isp_flash"
static struct iomux_block *gpio_block;
static struct block_config *block_conf;

static int tps61310_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int tps61310_remove(struct i2c_client *client);
static int test_flash(void);
static void set_strobe0(u32 value);
static void set_strobe1(u32 value);
static void dump_reg(void);
static int tps61310_turn_on(work_mode mode, flash_lum_level lum);
static int tps61310_turn_off(void);

static const struct i2c_device_id tps61310_id[] = {
	{K3_FLASH_NAME, 0},
	{}
};

static struct i2c_driver tps61310_driver = {
	.driver = {
		   .name = K3_FLASH_NAME,
		   },
	.probe = tps61310_probe,
	.remove = tps61310_remove,
	.id_table = tps61310_id,
};

/*
 **************************************************************************
 * FunctionName: tps61310_i2c_read;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int tps61310_i2c_read(char *rxData, int length)
{
	int ret = 0;
	struct i2c_msg msgs[] = {
		{
		 .addr = tps61310_client->addr,
		 .flags = I2C_M_RD,
		 .len = length,
		 .buf = rxData,
		 },
	};

	ret = i2c_transfer(tps61310_client->adapter, msgs, 1);
	if (ret < 0)
		print_error("%s: transfer error %d\n", __func__, ret);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: tps61310_i2c_write;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int tps61310_i2c_write(char *txData, int length)
{
	int ret = 0;
	struct i2c_msg msg[] = {
		{
		 .addr = tps61310_client->addr,
		 .flags = 0,
		 .len = length,
		 .buf = txData,
		 },
	};
	ret = i2c_transfer(tps61310_client->adapter, msg, 1);
	if (ret < 0)
		print_error("%s: transfer error %d\n", __func__, ret);

	return ret;
}

/*
 **************************************************************************
 * FunctionName: tps61310_probe;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int tps61310_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter;
	struct tps61310_platform_data *pdata = NULL;
	int ret = 0;
	print_debug("Enter %s", __FUNCTION__);

	adapter = client->adapter;
	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA
				     | I2C_FUNC_SMBUS_WRITE_BYTE)) {
		return -EIO;
	}

	pdata = client->dev.platform_data;
	if (!pdata) {
		print_error("platform data is null");
		return -ENOMEM;
	}

	tps61310_client = client;

	/* get gpio block */
	gpio_block = iomux_get_block(K3_FLASH_BLOCK);
	if (!gpio_block) {
		print_error("%s: failed to get iomux %s\n", __func__, K3_FLASH_BLOCK);
		return -EINVAL;
	}

	/* get gpio config block */
	block_conf = iomux_get_blockconfig(K3_FLASH_BLOCK);
	if (!block_conf) {
		print_error("%s: failed to get iomux isp %s\n", __func__, K3_FLASH_BLOCK);
		return -EINVAL;
	}

	/* set gpio work mode */
	ret = blockmux_set(gpio_block, block_conf, NORMAL);
	if (ret != 0) {
		print_error("%s: failed to set iomux flash to gpio mode.\n", __func__);
		return -EINVAL;
	}

	reset_pin = pdata->reset_pin;
	strobe0_pin = pdata->strobe0;
	strobe1_pin = pdata->strobe1;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: tps61310_remove;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int tps61310_remove(struct i2c_client *client)
{
	print_debug("Enter %s", __FUNCTION__);

	tps61310_client->adapter = NULL;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: tps61310_read_reg8;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int tps61310_read_reg8(u8 reg, u8 *val)
{
	int ret;
	u8 buf[1];
	print_debug("Enter Function:%s", __FUNCTION__);

	buf[0] = reg;
	ret = tps61310_i2c_write(buf, 1);
	if (ret < 0) {
		print_error("tps61310 read reg error(%d), reg=%x", ret, reg);
	}

	ret = tps61310_i2c_read(val, 1);
	if (ret < 0) {
		print_error("tps61310 read reg error(%d), reg=%x", ret, reg);
	}

	return ret;

}

/*
 **************************************************************************
 * FunctionName: tps61310_write_reg8;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int tps61310_write_reg8(u8 reg, u8 val)
{
	u8 buf[2];
	print_debug("Enter Function:%s", __FUNCTION__);

	buf[0] = reg;
	buf[1] = val;
	return tps61310_i2c_write(buf, 2);

}

/*
 **************************************************************************
 * FunctionName: tps61310_cfg_led;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void tps61310_cfg_led(int led, int status)
{
	u8 val;
	print_debug("enter %s", __FUNCTION__);

	tps61310_read_reg8(FLASH_REGISTER5, &val);
	if (status == ENABLE) {
		val = val | (1 << led);
		tps61310_write_reg8(FLASH_REGISTER5, val);
	} else {
		val = val & (~(1 << led));
		tps61310_write_reg8(FLASH_REGISTER5, val);
	}

	led_select = val & 0x07;

	return;
}

/*
 **************************************************************************
 * FunctionName: tps61310_cfg_trig;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void tps61310_cfg_trig(int trigger_mode)
{
	u8 val;
	print_debug("enter %s", __FUNCTION__);

	tps61310_read_reg8(FLASH_REGISTER3, &val);
	if (trigger_mode == TRIG_MODE_LEVEL) {
		val = val & (~FLASH_STT_BIT);
		tps61310_write_reg8(FLASH_REGISTER3, val);
	} else if (trigger_mode == TRIG_MODE_EDGE) {
		val = val | FLASH_STT_BIT;
		tps61310_write_reg8(FLASH_REGISTER3, val);
	} else if (trigger_mode == TRIG_MODE_CMD) {
		/* do nothing */
	}
	return;
}

/*
 **************************************************************************
 * FunctionName: tps61310_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int tps61310_init(void)
{
	int ret;

        /*FIXME:for FPGA no flash*/
#if 0
	ret = gpio_request(reset_pin, NULL);
	if (ret) {
		print_error("failed to request reset pin of flash ic");
		return -EIO;
	}

	ret = gpio_request(strobe0_pin, NULL);
	if (ret) {
		print_error("failed to request strobe0 pin of flash ic");
		return -EIO;
	}

	ret = gpio_request(strobe1_pin, NULL);
	if (ret) {
		print_error("failed to request strobe1 pin of flash ic");
		return -EIO;
	}
#endif

	return 0;
}

/*
 **************************************************************************
 * FunctionName: tps61310_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void tps61310_exit(void)
{
	int ret;
	print_debug("enter %s", __FUNCTION__);

        /*FIXME:for FPGA no flash*/
#if 0
	gpio_direction_output(reset_pin, 0);
	gpio_free(reset_pin);
	gpio_free(strobe0_pin);
	gpio_free(strobe1_pin);

	/* set gpio work mode */
	ret = blockmux_set(gpio_block, block_conf, LOWPOWER);
	if (ret != 0) {
		print_error("%s: failed to set iomux flash to gpio mode.\n", __func__);
		return;
	}
#endif

	return;
}

/*
 **************************************************************************
 * FunctionName: dump_reg;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void dump_reg(void)
{
	u8 val;
	int i;
	print_debug("enter tps61310 %s", __FUNCTION__);

	for (i = 0; i < 8; i++) {
		tps61310_read_reg8(i, &val);
		print_info("read reg 0x%x = 0x%x", i, val);
		msleep(100);
	}
}

/*
 **************************************************************************
 * FunctionName: set_strobe0;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void set_strobe0(u32 value)
{
	if (value == 0)
		gpio_direction_output(strobe0_pin, 0);
	else
		gpio_direction_output(strobe0_pin, 1);

	/* for debug
	 *
	 * value = gpio_get_value(strobe0_pin);
	 * print_debug("===gpio[%d] value:%d", strobe0_pin, value);
	 */

}

/*
 **************************************************************************
 * FunctionName: set_strobe1;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void set_strobe1(u32 value)
{
	if (value == 0)
		gpio_direction_output(strobe1_pin, 0);
	else
		gpio_direction_output(strobe1_pin, 1);

	/* for debug
	 *
	 * value = gpio_get_value(strobe0_pin);
	 * print_debug("===gpio[%d] value:%d", strobe0_pin, value);
	 */
}

/*
 **************************************************************************
 * FunctionName: test_flash;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int test_flash(void)
{
	print_debug("enter %s", __FUNCTION__);

	tps61310_turn_on(TORCH_MODE, 0);
	msleep(4000);
	dump_reg();
	tps61310_turn_off();
	msleep(1000);
	dump_reg();

	tps61310_turn_on(FLASH_MODE, 1);
	msleep(1000);
	dump_reg();
	tps61310_turn_off();
	dump_reg();

	return 0;
}

/*
 **************************************************************************
 * FunctionName: tps61310_reset;
 * Description : software reset;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int tps61310_reset(void)
{
	print_error("enter %s", __FUNCTION__);

        /*FIXME:for FPGA no flash*/
#if 0
	gpio_direction_output(reset_pin, 0);
#endif

	return 0;
}

/*
 **************************************************************************
 * FunctionName: tps61310_turn_on;
 * Description : turn on flashlight;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int tps61310_turn_on(work_mode mode, flash_lum_level lum)
{
	u8 val;
	print_debug("enter %s", __FUNCTION__);

        /*FIXME:for FPGA no flash*/

#if 0
	set_strobe0(0);
	set_strobe1(1);

	gpio_direction_output(reset_pin, 1);
	tps61310_read_reg8(0x4, &val);
	val = val | 0x10;
	tps61310_write_reg8(0x4, val);

	/* enable LED1,2,3 */
	tps61310_read_reg8(0x5, &val);
	val = val | 0x7;
	tps61310_write_reg8(0x5, val);

	if (mode == FLASH_MODE) {
		switch (lum) {
		case LUM_LEVEL0:
			val = FLASH_100MA;
			break;

		case LUM_LEVEL1:
			val = FLASH_200MA;
			break;

		case LUM_LEVEL2:
			val = FLASH_300MA;
			break;

		case LUM_LEVEL3:
			val = FLASH_400MA;
			break;

		case LUM_LEVEL4:
			val = FLASH_500MA;
			break;

		case LUM_LEVEL5:
			val = FLASH_600MA;
			break;

		case LUM_LEVEL6:
			val = FLASH_700MA;
			break;

		case LUM_LEVEL7:
			val = FLASH_800MA;
			break;

		default:
			print_error("Unsupport lum_level:%d", lum);
			return -1;
		}

		tps61310_write_reg8(0x1, val | 0x80);
		tps61310_write_reg8(0x2, (val >> 1) | 0x80);

		print_debug("start FLASH_MODE");
		set_strobe1(0);
		set_strobe0(1);
	} else if (mode == TORCH_MODE) {
		if (lum > 3)
			lum = 3;

		val = (lum << 3) + lum * 2;
		tps61310_write_reg8(0x0, val);
		tps61310_read_reg8(0x1, &val);
		val |= 0x80;
		tps61310_write_reg8(0x1, val);
		tps61310_read_reg8(0x2, &val);
		val |= 0x80;
		tps61310_write_reg8(0x2, val);

		print_debug("start TORCH_MODE");
		set_strobe1(1);
		set_strobe0(1);
	}
#endif

	return 0;
}



/*
 **************************************************************************
 * FunctionName: tps61310_turn_off;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int tps61310_turn_off(void)
{
	u8 val;
	u32 value;
	print_debug("enter %s", __FUNCTION__);

        /*FIXME:for FPGA no flash*/
#if 0
	value = gpio_get_value(reset_pin);
	if (value != 0) {
		/* set flash mode ctrl reg */
		tps61310_read_reg8(0x1, &val);
		val = val & 0x3f;
		tps61310_write_reg8(0x1, val);

		tps61310_read_reg8(0x2, &val);
		val = val & 0x3f;
		tps61310_write_reg8(0x2, val);
	}

	set_strobe0(0);
	set_strobe1(1);
	gpio_direction_output(reset_pin, 0);
#endif

	return 0;
}

/*
 **************************************************************************
 * FunctionName: tps61310_set_default;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void tps61310_set_default(void)
{
	print_debug("enter %s", __FUNCTION__);

	tps61310_intf.init		= tps61310_init;
	tps61310_intf.exit		= tps61310_exit;
	tps61310_intf.reset		= tps61310_reset;
	tps61310_intf.turn_on		= tps61310_turn_on;
	tps61310_intf.turn_off		= tps61310_turn_off;
	tps61310_intf.test		= test_flash;
	tps61310_intf.type		= LED_FLASH;
}

/*
 **************************************************************************
 * FunctionName: tps61310_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int __init tps61310_module_init(void)
{
	int ret;
	print_debug("enter %s", __FUNCTION__);
	ret = i2c_add_driver(&tps61310_driver);
	if (0 != ret) {
		print_error("Fail to add flash driver");
		return -1;
	}

	if(tps61310_client == NULL)
	{
		return -1;
	}
	
	tps61310_set_default();
	register_camera_flash(&tps61310_intf);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: tps61310_module_deinit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void __exit tps61310_module_deinit(void)
{
	print_debug("enter %s", __FUNCTION__);
	i2c_del_driver(&tps61310_driver);

	unregister_camera_flash(&tps61310_intf);
	return;
}


module_init(tps61310_module_init);
module_exit(tps61310_module_deinit);
MODULE_AUTHOR("c00168914");
MODULE_DESCRIPTION("tps61310 Flash Driver");
MODULE_LICENSE("GPL");

/********************************** END ***************************************/
