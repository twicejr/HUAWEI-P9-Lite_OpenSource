/*
 *  Hisilicon K3 soc camera ISP driver source file
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
//#include <mach/gpio.h>
#include "mini_k3_isp.h"
#include "mini_k3_isp_io.h"
#include "mini_sensor_common.h"

#define DEBUG_DEBUG 0
#define LOG_TAG "K3_ISPIO"
#include "mini_cam_log.h"
//#include "drv_regulator_user.h"

static mini_ispio_controller *ispio_hw_ctl;
static mini_isp_sensor_reg_controller *isp_sensor_reg_ctl;
static mini_isp_io_data_t isp_io_data = { false, false };
#if defined(CONFIG_MACH_HI6620SFT)
static mini_isp_io_gpio_regulator_t isp_io_gpio_regulator = {
    {CAMERA_ANALOG_VDD, M_CAMERA_ANALOG_VDD},
    {CAMERA_IO_VCC, M_CAMERA_IO_VDD},
    {CAMERA_CORE_VDD, M_CAMERA_CORE_VDD},
    {CAMERA_VCM_VCC, M_CAMERA_VCM_VDD}
};
#endif

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_read_reg;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispio_read_reg(i2c_index_t index, u8 i2c_addr, u16 reg, u16 *val, i2c_length length, i2c_length addr_len)
{
    return isp_sensor_reg_ctl->isp_read_sensor_reg(index, i2c_addr, reg, val, length, addr_len);
}
EXPORT_SYMBOL(mini_k3_ispio_read_reg);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_write_reg;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispio_write_reg(i2c_index_t index, u8 i2c_addr, u16 reg, u16 val, i2c_length length, u8 mask, i2c_length addr_len)
{

    return isp_sensor_reg_ctl->isp_write_sensor_reg(index, i2c_addr, reg, val, length, mask, addr_len);
}
EXPORT_SYMBOL(mini_k3_ispio_write_reg);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_write_seq;
 * Description : write sequeuence to select I2C though isp command set;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispio_write_seq(i2c_index_t index, u8 i2c_addr, const struct _mini_sensor_reg_t *seq,
	u32 size, i2c_length length, u8 mask, i2c_length addr_len)
{
	return isp_sensor_reg_ctl->isp_write_sensor_seq(index, i2c_addr, seq, size, length, mask, addr_len);
}
EXPORT_SYMBOL(mini_k3_ispio_write_seq);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_write_group_seq;
 * Description : write sequeuence to select I2C though isp command set;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispio_write_group_seq(i2c_index_t index, u8 i2c_addr,
			     const struct _mini_sensor_reg_t *reg, u32 size)
{
	return isp_sensor_reg_ctl->isp_write_sensor_group_seq(index, i2c_addr, reg, size);
}
EXPORT_SYMBOL(mini_k3_ispio_write_group_seq);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_write_isp_seq;
 * Description : write sensor related sequeuence to isp;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_k3_ispio_write_isp_seq(const struct mini_isp_reg_t *seq, u32 size)
{
	isp_sensor_reg_ctl->isp_write_isp_seq(seq, size);
}
EXPORT_SYMBOL(mini_k3_ispio_write_isp_seq);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_read_isp_seq;
 * Description : read sensor related sequeuence to isp;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_k3_ispio_read_isp_seq(struct mini_isp_reg_t *seq, u32 size)
{
	isp_sensor_reg_ctl->isp_read_isp_seq(seq, size);
}
EXPORT_SYMBOL(mini_k3_ispio_read_isp_seq);
/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_update_flip;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_k3_ispio_update_flip(u8 flip_changed, u16 width, u16 height, pixel_order changed)
{
	isp_sensor_reg_ctl->isp_update_flip(flip_changed, width, height, changed);
}
EXPORT_SYMBOL(mini_k3_ispio_update_flip);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_power_init;
 * Description : register ldo;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispio_power_init(char *ldo_name, u32 vol_min, u32 vol_max)
{
	return ispio_hw_ctl->power_init(ldo_name, vol_min, vol_max);
}
EXPORT_SYMBOL(mini_k3_ispio_power_init);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_power_deinit;
 * Description : deregister ldo;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_k3_ispio_power_deinit(void)
{
	ispio_hw_ctl->power_deinit();
}
EXPORT_SYMBOL(mini_k3_ispio_power_deinit);


/*
 **************************************************************************
 * FunctionName: mini_k3_socgpio_power_sensor;
 * Description : power for camera sensor;
 * Input       : camera_power_state power_state;
                     unsigned gpio
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_socgpio_power_sensor(int value, unsigned gpio)
{
    int ret = -EINVAL;
#if defined(CONFIG_MACH_HI6620SFT)
    mini_isp_regulator_info_t *regulator_info;

	print_debug("enter %s", __func__);

    if (gpio == CAMERA_ANALOG_VDD) {
        regulator_info = &isp_io_gpio_regulator.camera_analog;
    } else if (gpio == CAMERA_IO_VCC) {
        regulator_info = &isp_io_gpio_regulator.camera_io_vcc;
    } else if (gpio == CAMERA_CORE_VDD) {
        regulator_info = &isp_io_gpio_regulator.camera_core_vdd;
    } else if (gpio == CAMERA_VCM_VCC) {
        regulator_info = &isp_io_gpio_regulator.camera_vcm_vcc;
    } else {
        print_error("%s: invalid request gpio %d for camera sensor", __func__, gpio);
        return -EINVAL;
    }

    ret = gpio_request(regulator_info->gpio, regulator_info->label);
    if (ret < 0) {
        print_error("%s: request camera gpio - %d(%s) failed, result = %d.",
            __func__, regulator_info->gpio, regulator_info->label, ret);
        return -EINVAL;
    }

    ret = gpio_direction_output(regulator_info->gpio, value);
    if (ret < 0) {
        print_error("%s: fail to power_on gpio - %d(%s), result = %d.",
            __func__, regulator_info->gpio, regulator_info->label, ret);
    }

    gpio_free(regulator_info->gpio);
#endif	

	print_debug("leave %s", __func__);

    return ret;
}
EXPORT_SYMBOL(mini_k3_socgpio_power_sensor);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispldo_power_sensor;
 * Description : Power on/off ldo
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispldo_power_sensor(camera_power_state power_state, char *ldo_name)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	/*ldo */
	ret = ispio_hw_ctl->power_sensor(power_state, ldo_name);
	if (ret != 0) {
		print_error("%s: power sensor fail", __func__);
		return ret;
	}

	return ret;
}
EXPORT_SYMBOL(mini_k3_ispldo_power_sensor);

/*
 **************************************************************************
 * FunctionName: k3_ispio_power_sensor;
 * Description : Power on/off gpio;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispgpio_power_sensor(mini_camera_sensor *sensor,
			    camera_power_state power_state)
{
	int ret = 0;

	print_debug("enter %s", __func__);

	/*gpio powerdown */
	isp_sensor_reg_ctl->isp_power_sensor(sensor->sensor_index, power_state,
					     sensor->power_conf.pd_valid, sensor->power_conf.vcmpd_valid);

	return ret;
}
EXPORT_SYMBOL(mini_k3_ispgpio_power_sensor);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_ioconfig;
 * Description : io config;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispio_ioconfig(mini_camera_sensor *sensor, camera_power_state power_state)
{

	print_debug("enter %s", __func__);

	return ispio_hw_ctl->ioconfig(power_state, sensor->interface_type);
}
EXPORT_SYMBOL(mini_k3_ispio_ioconfig);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispgpio_reset_sensor;
 * Description : reset sensor through gpio;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispgpio_reset_sensor(sensor_index_t sensor_index, camera_power_state power_state, electrical_valid_t reset_valid)
{
	if (sensor_index >= CAMERA_SENSOR_MAX || reset_valid > HIGH_VALID) {
		print_error("cur_type %d or reset_valid %d error", sensor_index, reset_valid);
		return -EINVAL;
	}

	/*gpio reset */
	isp_sensor_reg_ctl->isp_reset_sensor(sensor_index, power_state, reset_valid);
	return 0;
}
EXPORT_SYMBOL(mini_k3_ispgpio_reset_sensor);

/*
 **************************************************************************
 * FunctionName: mini_k3_isp_io_enable_mclk;
 * Description : enable or disable mclk;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_k3_isp_io_enable_mclk(mclk_state state, sensor_index_t sensor_index)
{
	isp_sensor_reg_ctl->isp_enable_mclk(state, sensor_index);
	return ;
}
EXPORT_SYMBOL(mini_k3_isp_io_enable_mclk);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_init_csi;
 * Description :
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispio_init_csi(csi_index_t mipi_index, csi_lane_t mipi_lane_count, u8 lane_clk)
{
	int ret = 0;

	if (isp_io_data.csi_inited)
		return ret;

	/* enter LP11 state
	   {    SETREG8(ISP_REG_BASE+0x63602, 0x30);
	   SETREG8(ISP_REG_BASE+0x63603, 0x00);
	   SETREG8(ISP_REG_BASE+0x63605, 0x03);
	   SETREG8(ISP_REG_BASE+0x63609, 0x37);
	   } */

	ret = ispio_hw_ctl->init_csi(mipi_index, mipi_lane_count, lane_clk);

	/*exit LP11 state
	 *SETREG8(ISP_REG_BASE+0x63602, 0x30);
	 *SETREG8(ISP_REG_BASE+0x63603, 0x00);
	 *SETREG8(ISP_REG_BASE+0x63605, 0x00);
	 *SETREG8(ISP_REG_BASE+0x63609, 0x37);
	 */
	if (0 == ret)
		isp_io_data.csi_inited = true;

	return ret;
}
EXPORT_SYMBOL(mini_k3_ispio_init_csi);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_deinit_csi;
 * Description :
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_k3_ispio_deinit_csi(csi_index_t mipi_index)
{
	if (isp_io_data.csi_inited == false)
		return;

	ispio_hw_ctl->deinit_csi(mipi_index);
	isp_io_data.csi_inited = false;
}
EXPORT_SYMBOL(mini_k3_ispio_deinit_csi);

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_init;
 * Description : init ispio;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int mini_k3_ispio_init(struct platform_device *pdev)
{
	int ret = 0;
	print_debug("enter %s", __func__);
	if (isp_io_data.inited) {
		print_error("%s ispio not already inited", __func__);
		return -EINVAL;
	}

	isp_sensor_reg_ctl = mini_get_isp_sensor_reg_controller();
	ispio_hw_ctl = mini_get_ispio_controller();
	ret = ispio_hw_ctl->ispio_hw_init(pdev);
	if (ret == 0)
		isp_io_data.inited = true;

	return ret;
}

/*
 **************************************************************************
 * FunctionName: mini_k3_ispio_deinit;
 * Description : deinit ispio;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void mini_k3_ispio_deinit()
{
	print_debug("enter %s", __func__);

	if (isp_io_data.inited) {
		ispio_hw_ctl->ispio_hw_deinit();
		isp_io_data.inited = false;
	}
}

/*********************** END *************************/
