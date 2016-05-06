/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include "hisi_sensor.h"
#include "../cci/hisi_cci.h"
#include "sensor_common.h"

#define MAX_RETRY_TIMES	3
#define OV5648_OTP_FEATURE	1

#ifdef OV5648_OTP_FEATURE
#define RG_RATIO_TYPICAL	0x26E
#define BG_RATIO_TYPICAL	0x2E9
#define MAX_GROUP		2
#endif

#define OV5648_EXPOSURE_REG_0			0x3500
#define OV5648_EXPOSURE_REG_1			0x3501
#define OV5648_EXPOSURE_REG_2			0x3502
#define OV5648_GAIN_REG_H				0x350a
#define OV5648_GAIN_REG_L				0x350b

struct sensor_power_setting ov5648_power_setting[] = {
	{
		.seq_type = SENSOR_AVDD,
		.data = (void*)"main-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_IOVDD,
		.data = (void*)"common-iovdd",
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_DVDD,
		.config_val = LDO_VOLTAGE_1P05V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_AVDD2,
		.data = (void*)"slave-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_PWDN,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_RST,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_I2C,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_SUSPEND,
		.config_val = SENSOR_GPIO_HIGH,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
};

int ov5648_write_reg(struct hisi_sensor_ctrl_t *s_ctrl, u16 reg, u8 val, u8 mask)
{
	i2c_t *i2c_info = &s_ctrl->sensor->sensor_info->i2c_config;
	return isp_write_sensor_byte(i2c_info, reg, val, mask);
}

int ov5648_read_reg(struct hisi_sensor_ctrl_t *s_ctrl, u16 reg, u8 *val)
{
	i2c_t *i2c_info = &s_ctrl->sensor->sensor_info->i2c_config;
	return isp_read_sensor_byte(i2c_info, reg, (u16*)val);
}

#ifdef OV5648_OTP_FEATURE
static int ov5648_check_otp_group(struct hisi_sensor_ctrl_t *s_ctrl, int index)
{
	u8 blank, i;
	u32 address;
	u8 flag;

	cam_info("%s enter.\n", __func__);

	for(i = 0; i < 16; i++) {
		ov5648_write_reg(s_ctrl, 0x3d00 + i, 0x00, 0x00);
	}
	ov5648_write_reg(s_ctrl, 0x3d84, 0xc0, 0x00);
	switch(index) {
		case 0:
			blank = 0x05;
			ov5648_write_reg(s_ctrl, 0x3d85, 0x00, 0x00);
			ov5648_write_reg(s_ctrl, 0x3d86, 0x0f, 0x00);
			break;
		case 1:
			blank = 0x00;
			ov5648_write_reg(s_ctrl, 0x3d85, 0x10, 0x00);
			ov5648_write_reg(s_ctrl, 0x3d86, 0x1f, 0x00);
			break;
		default:
			return -1;
	}

	/* set address */
	address = 0x3d00 + blank;
	cam_info("%s address = 0x%x.", __func__, address);

	/* load otp to buffer */
	ov5648_write_reg(s_ctrl, 0x3d81, 0x01, 0x00);
	mdelay(5);

	/* check value */
	ov5648_read_reg(s_ctrl, address, &flag);

	/* disable otp read */
	ov5648_write_reg(s_ctrl, 0x3d81, 0x00, 0x00);

	cam_info("%s temp_value = 0x%x.", __func__, flag);
	flag = flag >> 6;
	if(1 == flag) {
		cam_info("%s group index = %d", __func__, index);
		return 0;
	}
	return -1;
}

static int ov5648_read_otp_wb(struct hisi_sensor_ctrl_t *s_ctrl, int index)
{
	struct hisi_sensor_awb_otp *awb_otp = &s_ctrl->sensor->sensor_otp.awb_otp;
	u8 blank;
	u32 address;

	ov5648_write_reg(s_ctrl, 0x3d84, 0xc0, 0x00);
	switch(index) {
		case 0:
			blank = 0x05;
			ov5648_write_reg(s_ctrl, 0x3d85, 0x00, 0x00);
			ov5648_write_reg(s_ctrl, 0x3d86, 0x0f, 0x00);
			break;
		case 1:
			blank = 0x00;
			ov5648_write_reg(s_ctrl, 0x3d85, 0x10, 0x00);
			ov5648_write_reg(s_ctrl, 0x3d86, 0x1f, 0x00);
			break;
		default:
			return -1;
	}
	/* set address */
	address = 0x3d00 + blank;
	/* select bank */

	/* load otp to buffer */
	ov5648_write_reg(s_ctrl, 0x3d81, 0x01, 0x00);
	mdelay(5);
	/* get value */

	ov5648_read_reg(s_ctrl, address+5, (u8*)&(awb_otp->rg_h));
	ov5648_read_reg(s_ctrl, address+6, (u8*)&(awb_otp->rg_l));
	ov5648_read_reg(s_ctrl, address+7, (u8*)&(awb_otp->bg_h));
	ov5648_read_reg(s_ctrl, address+8, (u8*)&(awb_otp->bg_l));
	ov5648_read_reg(s_ctrl, address+9, (u8*)&(awb_otp->gbgr_h));
	ov5648_read_reg(s_ctrl, address+10, (u8*)&(awb_otp->gbgr_l));

	cam_info("%s rg_h=0x%x, rg_l=0x%x, bg_h=0x%x, bg_l=0x%x, gbgr_h=0x%x, gbgr_l=0x%x.",
		__func__, awb_otp->rg_h, awb_otp->rg_l, awb_otp->bg_h, awb_otp->bg_l,
		awb_otp->gbgr_h, awb_otp->gbgr_l);

	/* disable otp read */
	ov5648_write_reg(s_ctrl, 0x3d81, 0x00, 0x00);
	return 0;
}

static int ov5648_update_wb_gain(struct hisi_sensor_ctrl_t *s_ctrl,
	u16 r_gain, u16 g_gain, u16 b_gain)
{
	cam_info("%s r_gain=0x%x, g_gain=0x%x, b_gain=0x%x.", __func__,
		r_gain, g_gain, b_gain);
	if (r_gain > 0x400) {
		ov5648_write_reg(s_ctrl, 0x5186, r_gain>>8, 0x00);
		ov5648_write_reg(s_ctrl, 0x5187, r_gain & 0x00ff, 0x00);
	}

	if (g_gain > 0x400) {
		ov5648_write_reg(s_ctrl, 0x5188, g_gain>>8, 0x00);
		ov5648_write_reg(s_ctrl, 0x5189, g_gain & 0x00ff, 0x00);
	}

	if (b_gain > 0x400) {
		ov5648_write_reg(s_ctrl, 0x518a, b_gain>>8, 0x00);
		ov5648_write_reg(s_ctrl, 0x518b, b_gain & 0x00ff, 0x00);
	}
	return 0;
}

static int ov5648_read_awb_gain(struct hisi_sensor_ctrl_t *s_ctrl, int index)
{
	struct hisi_sensor_awb_otp *awb_otp = &s_ctrl->sensor->sensor_otp.awb_otp;
	int r_gain, g_gain, b_gain, g_gain_r, g_gain_b;
	int rg,bg;

	ov5648_read_otp_wb(s_ctrl, index);

	rg = (awb_otp->rg_h << 8) + awb_otp->rg_l;
	bg = (awb_otp->bg_h << 8) + awb_otp->bg_l;

	cam_info("%s rg_ratio 0x%x, bg_ratio 0x%x",__func__, rg, bg);

	/* calculate G gain, 0x400 = 1x gain */
	if(bg < BG_RATIO_TYPICAL) {
		if (rg< RG_RATIO_TYPICAL) {
			g_gain = 0x400;
			b_gain = 0x400 * BG_RATIO_TYPICAL / bg;
			r_gain = 0x400 * RG_RATIO_TYPICAL / rg;
		} else {
			r_gain = 0x400;
			g_gain = 0x400 * rg / RG_RATIO_TYPICAL;
			b_gain = g_gain * BG_RATIO_TYPICAL /bg;
		}
	} else {
		if (rg < RG_RATIO_TYPICAL) {
			b_gain = 0x400;
			g_gain = 0x400 * bg / BG_RATIO_TYPICAL;
			r_gain = g_gain * RG_RATIO_TYPICAL / rg;
		} else {
			g_gain_b = 0x400 * bg / BG_RATIO_TYPICAL;
			g_gain_r = 0x400 * rg / RG_RATIO_TYPICAL;

			if(g_gain_b > g_gain_r ) {
				b_gain = 0x400;
				g_gain = g_gain_b;
				r_gain = g_gain * RG_RATIO_TYPICAL /rg;
			} else {
				r_gain = 0x400;
				g_gain = g_gain_r;
				b_gain = g_gain * BG_RATIO_TYPICAL / bg;
			}
		}
	}

	cam_info("%s r_gain=0x%x, g_gain=0x%x, b_gain=0x%x.", __func__,
			r_gain, g_gain, b_gain);

	awb_otp->rgain = r_gain;
	awb_otp->bgain = b_gain;
	awb_otp->ggain = g_gain;
	return 0;
}

static int ov5648_read_otp(struct hisi_sensor_ctrl_t *s_ctrl)
{
	int index;
	int rc = -1;

	cam_info("%s enter.", __func__);

	ov5648_write_reg(s_ctrl, 0x0100, 0x01, 0x00);
	for(index=0; index<MAX_GROUP; index++) {
		if(0 == ov5648_check_otp_group(s_ctrl, index))
			break;
	}

	if(index < MAX_GROUP) {
		rc = ov5648_read_awb_gain(s_ctrl, index);
		if (0 == rc) {
			s_ctrl->sensor->sensor_otp.awb_otp.awb_otp_succeed = 1;
		}
	}
	ov5648_write_reg(s_ctrl, 0x0100, 0x00, 0x00);

	return rc;
}
#endif

int ov5648_match_id(struct hisi_sensor_ctrl_t *s_ctrl)
{
	int ret = 0;
	u16 id_h = 0;
	u16 id_l = 0;
	u16 sensor_id = 0;
	int retry = 0;

	cam_info( "%s, sensor_chipid:0x%x\n",
		__func__, s_ctrl->sensor->sensor_info->sensor_chipid);

	ret = hisi_sensor_power_up(s_ctrl);
	if(ret) {
		cam_err("sensor[%s] power up failed.", s_ctrl->sensor->sensor_info->name);
		ret = -1;
		goto out;
	}

	for (retry=0; retry<MAX_RETRY_TIMES; retry++) {
		/* check sensor id */
		ov5648_read_reg(s_ctrl, 0x300a, (u8*)&id_h);
		ov5648_read_reg(s_ctrl, 0x300b, (u8*)&id_l);

		sensor_id = id_h << 8 | id_l;

		cam_notice( "%s sensor id:  0x%x", __func__, sensor_id);
		if (sensor_id != s_ctrl->sensor->sensor_info->sensor_chipid) {
			cam_notice("%s failed to match sensor(0x%x).", __func__,
					s_ctrl->sensor->sensor_info->sensor_chipid);
			ret =  -1;
		} else {
			cam_notice("%s succeed to match sensor(0x%x).", __func__,
					s_ctrl->sensor->sensor_info->sensor_chipid);
			ret = 0;
			break;
		}
		udelay(100);
	}

	if (0 == ret) {
		#ifdef OV5648_OTP_FEATURE
		ov5648_read_otp(s_ctrl);
		#endif
	}
out:
	hisi_sensor_power_down(s_ctrl);

	return ret;
}

int ov5648_ioctl(struct hisi_sensor_ctrl_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data*)data;
	int   rc = 0;

	cam_debug("%s enter.\n", __func__);

	switch (cdata->cfgtype) {
	case CFG_SENSOR_SET_VTS:
		cam_info("%s set vts.\n", __func__);
		break;
	case CFG_SENSOR_GET_OTP_AWB:
		//TODO...
		break;
	case CFG_SENSOR_UPDATE_OTP_AWB:
		#ifdef OV5648_OTP_FEATURE
		if (s_ctrl->sensor->sensor_otp.awb_otp.awb_otp_succeed) {
			rc = ov5648_update_wb_gain(s_ctrl,
				s_ctrl->sensor->sensor_otp.awb_otp.rgain,
				s_ctrl->sensor->sensor_otp.awb_otp.ggain,
				s_ctrl->sensor->sensor_otp.awb_otp.bgain);
		} else {
			cam_err("%s awb otp is error.", __func__);
		}
		#endif
		break;
	default:
		rc = -EFAULT;
		break;
	}

	return rc;
}

int ov5648_set_expo(struct hisi_sensor_t *cur_sensor, u32 expo)
{
	int rc = 0;

	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		OV5648_EXPOSURE_REG_0, (expo >> 16) & 0x0f, 0x00);
	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		OV5648_EXPOSURE_REG_1, (expo >> 8) & 0xff, 0x00);
	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		OV5648_EXPOSURE_REG_2, expo & 0xf0, 0x00);
	return rc;
}

int ov5648_set_gain(struct hisi_sensor_t *cur_sensor, u16 gain)
{
	int rc = 0;

	if (gain == 0) {
		return rc;
	}
	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		OV5648_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		OV5648_GAIN_REG_L, gain & 0xff, 0x00);
	return rc;
}

struct hisi_sensor_fn_t ov5648_func_tbl = {
	.sensor_config = hisi_sensor_config,
	.sensor_power_up = hisi_sensor_power_up,
	.sensor_power_down = hisi_sensor_power_down,
	.sensor_i2c_read = hisi_sensor_i2c_read,
	.sensor_i2c_write = hisi_sensor_i2c_write,
	.sensor_i2c_read_seq = hisi_sensor_i2c_read_seq,
	.sensor_i2c_write_seq = hisi_sensor_i2c_write_seq,
	.sensor_ioctl = ov5648_ioctl,
	.sensor_match_id = ov5648_match_id,
	.sensor_set_expo = ov5648_set_expo,
	.sensor_set_gain = ov5648_set_gain,
};

static int32_t ov5648_sensor_probe(struct platform_device *pdev)
{
	int32_t rc = -1;
	struct hisi_sensor_t *sensor = NULL;

	cam_info("%s pdev name %s\n", __func__, pdev->name);

	sensor = (struct hisi_sensor_t*)kzalloc(sizeof(struct hisi_sensor_t),
						GFP_KERNEL);
	if (NULL == sensor) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return -ENOMEM;
	}

	sensor->func_tbl = &ov5648_func_tbl;
	sensor->power_setting_array.power_setting = ov5648_power_setting;
	sensor->power_setting_array.size = ARRAY_SIZE(ov5648_power_setting);

	if (pdev->dev.of_node) {
		rc = hisi_sensor_get_dt_data(pdev, sensor);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			return rc;
		}
	} else {
		cam_err("%s ov5648 of_node is NULL.\n", __func__);
		kfree(sensor);
		sensor = NULL;
		return rc;
	}

	rc = hisi_sensor_add(sensor);
	if (rc < 0) {
		cam_err("%s fail to add sensor into sensor array.\n", __func__);
		kfree(sensor);
		sensor = NULL;
		return rc;
	}
	if (!dev_get_drvdata(&pdev->dev)) {
		dev_set_drvdata(&pdev->dev, (void *)sensor);
	}
	return rc;
}

static const struct of_device_id hisi_ov5648_dt_match[] = {
	{.compatible = "hisi,ov5648_foxconn"},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_ov5648_dt_match);
static struct platform_driver ov5648_platform_driver = {
	.driver = {
		.name = "ov5648",
		.owner = THIS_MODULE,
		.of_match_table = hisi_ov5648_dt_match,
	},
};

static int32_t ov5648_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	const struct of_device_id *match;

	match = of_match_device(hisi_ov5648_dt_match, &pdev->dev);
	cam_notice("%s compatible=%s.\n", __func__, match->compatible);
	rc = ov5648_sensor_probe(pdev);
	return rc;
}

static int __init ov5648_module_init(void)
{
	int rc = 0;
	cam_info("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&ov5648_platform_driver,
		ov5648_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error.\n", __func__);
	}
	return rc;
}

static void __exit ov5648_module_exit(void)
{
	platform_driver_unregister(&ov5648_platform_driver);
}

MODULE_AUTHOR("HISI");
module_init(ov5648_module_init);
module_exit(ov5648_module_exit);
MODULE_LICENSE("GPL");
