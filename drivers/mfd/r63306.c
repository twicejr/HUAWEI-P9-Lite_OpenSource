#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/mfd/core.h>
#include <linux/mfd/r63306.h>

#define RENESAS_ID_VENDOR	0x0122

#define DSI_CMD_LEN		32

enum DATA_TYPE {
	GEN_SHORT_WR_PARAM0 = 0x03,
	GEN_SHORT_WR_PARAM1 = 0x13,
	GEN_SHORT_WR_PARAM2 = 0x23,
	GEN_RD_PARAM0 = 0x04,
	GEN_RD_PARAM1 = 0x14,
	GEN_RD_PARAM2 = 0x24,
	DCS_SHORT_WR_PARAM0 = 0x05,
	DCS_SHORT_WR_PARAM1 = 0x15,
	DCS_RD_PARAM0 = 0x06,
	SET_MAX_PKT = 0x37,
	NULL_PKT = 0x09,
	BLANKING_PKT = 0x19,
	GEN_LONG_WR = 0x29,
	DCS_LONG_WR = 0x39,
	PACKED_PIXEL_16B = 0x0e,
	PACKED_PIXEL_18B = 0x1e,
	LOOSELY_PACKED_PIXEL_18B = 0x2e,
	PACKED_PIXEL_24B = 0x3e,
};

/* 1st byte is DT type, 2nd byte is command, others are parameters. */
static u8 soft_reset[] = {DCS_SHORT_WR_PARAM0, 0x01};
static u8 get_power_mode[] = {DCS_RD_PARAM0, 0x0a};
static u8 get_address_mode[] = {DCS_RD_PARAM0, 0x0b};
static u8 get_display_mode[] = {DCS_RD_PARAM0, 0x0d};
static u8 get_signal_mode[] = {DCS_RD_PARAM0, 0x0e};
static u8 enter_sleep_mode[] = {DCS_SHORT_WR_PARAM0, 0x10};
static u8 exit_sleep_mode[] = {DCS_SHORT_WR_PARAM0, 0x11};
static u8 exit_invert_mode[] = {DCS_SHORT_WR_PARAM0, 0x20};
static u8 enter_invert_mode[] = {DCS_SHORT_WR_PARAM0, 0x21};
static u8 set_display_off[] = {DCS_SHORT_WR_PARAM0, 0x28};
static u8 set_display_on[] = {DCS_SHORT_WR_PARAM0, 0x29};
static u8 set_address_mode[] = {DCS_SHORT_WR_PARAM1, 0x36, 0x0};
static u8 read_dsi_ctrl[] = {GEN_RD_PARAM1, 0xb6};
static u8 write_dsi_ctrl[] = {GEN_LONG_WR, 0xb6};
static u8 read_pfm_pwm_ctrl[] = {GEN_RD_PARAM1, 0xb9};
static u8 write_pfm_pwm_ctrl[] = {GEN_LONG_WR, 0xb9};
static u8 read_backlight[] = {GEN_RD_PARAM1, 0xba};
static u8 read_cabc_ctrl[] = {GEN_RD_PARAM1, 0xbb};
static u8 write_cabc_ctrl[] = {GEN_LONG_WR, 0xbb};
static u8 read_cabc_param[] = {GEN_RD_PARAM1, 0xbe};
static u8 write_cabc_param[] = {GEN_LONG_WR, 0xbe};
static u8 read_device_code[] = {GEN_RD_PARAM1, 0xbf};

static struct mfd_cell pwm_devs[] = {
	{
		.name		= "r63306-pwm",
		.id		= -1,
		.of_compatible = "renesas,r63306-pwm",
	},
};

extern int dsi_set_packet(u8 *cmd, int nr_payload);

int dsi_reset(void)
{
	u8 cmd[DSI_CMD_LEN];

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, soft_reset, sizeof(soft_reset));
	return dsi_set_packet(cmd, 1);
}
EXPORT_SYMBOL(dsi_reset);

int dsi_enter_sleep(void)
{
	u8 cmd[DSI_CMD_LEN];

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, enter_sleep_mode, sizeof(enter_sleep_mode));
	return dsi_set_packet(cmd, 1);
}
EXPORT_SYMBOL(dsi_enter_sleep);

int dsi_exit_sleep(void)
{
	u8 cmd[DSI_CMD_LEN];

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, exit_sleep_mode, sizeof(exit_sleep_mode));
	return dsi_set_packet(cmd, 1);
}
EXPORT_SYMBOL(dsi_exit_sleep);

int dsi_get_id(struct r63306_device_id *id)
{
	u8 cmd[DSI_CMD_LEN];
	int ret;

pr_err("#%s, %d\n", __func__, __LINE__);
	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, read_device_code, sizeof(read_device_code));
	ret = dsi_set_packet(cmd, 5);
	if (ret)
		return ret;
	id->vendor = cmd[2] << 8 | cmd[3];
	id->product = cmd[4] << 8 | cmd[5];
	id->revision = cmd[6];
	return 0;
}
EXPORT_SYMBOL(dsi_get_id);

int dsi_get_backlight(int *level)
{
	u8 cmd[DSI_CMD_LEN];
	int ret;

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, read_backlight, sizeof(read_backlight));
	ret = dsi_set_packet(cmd, 2);
	if (ret)
		return ret;
	pr_err("#%s, %d, backlight:0x%x 0x%x\n", __func__, __LINE__, cmd[2], cmd[3]);
	return 0;
}

int dsi_get_cabc(struct r63306_cabc *cabc)
{
	u8 cmd[DSI_CMD_LEN];
	int ret;

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, read_cabc_ctrl, sizeof(read_cabc_ctrl));
	ret = dsi_set_packet(cmd, 1);
	if (ret)
		return ret;
	cabc->cabc_on = (cmd[2] & (1 << 0)) ? 1 : 0;
	cabc->pwm_on = (cmd[2] & (1 << 1)) ? 1 : 0;
	cabc->pfm_on = (cmd[2] & (1 << 2)) ? 1 : 0;
	cabc->ledpwm_pin = (cmd[2] & (1 << 3)) ? 1 : 0;
	cabc->ledpwm_pol = (cmd[2] & (1 << 4)) ? 1 : 0;
	pr_err("#%s, %d, cabc:%d, pwm_on:%d, pfm_on:%d, ledpwm_pin:%d, ledpwm_pol:%d\n",
		__func__, __LINE__, cabc->cabc_on, cabc->pwm_on, cabc->pfm_on, cabc->ledpwm_pin, cabc->ledpwm_pol);
	return 0;
}
EXPORT_SYMBOL(dsi_get_cabc);

int dsi_set_cabc(struct r63306_cabc *cabc)
{
	u8 cmd[DSI_CMD_LEN];

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, write_cabc_ctrl, sizeof(write_cabc_ctrl));
	cmd[2] = (cabc->cabc_on << 0) | (cabc->pwm_on << 1) |
		(cabc->pfm_on << 2) | (cabc->ledpwm_pin << 3) |
		(cabc->ledpwm_pol << 4);
	return dsi_set_packet(cmd, 1 + 1);
}
EXPORT_SYMBOL(dsi_set_cabc);

int dsi_get_cabc_param(struct r63306_cabc_param *cabc)
{
	u8 cmd[DSI_CMD_LEN];
	int ret;

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, read_cabc_param, sizeof(read_cabc_param));
	ret = dsi_set_packet(cmd, 8);
	if (ret < 0)
		return ret;
#if 0
	cabc->backlight = ((cmd[2] & 0xf) << 4) | (cmd[3] & 0xf);
#else
	cabc->backlight = (cmd[2] << 8) | (cmd[3] & 0xf);
#endif
	pr_err("#%s, %d, [2]:0x%x, [3]:0x%x, [4]:0x%x\n",
		__func__, __LINE__, cmd[2], cmd[3], cmd[4]);
	return 0;
}
EXPORT_SYMBOL(dsi_get_cabc_param);

int dsi_set_cabc_param(struct r63306_cabc_param *cabc)
{
	u8 cmd[DSI_CMD_LEN];

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, write_cabc_param, sizeof(write_cabc_param));
/*
#if 0
	cmd[2] = (cabc->backlight >> 4) & 0xf;
	cmd[3] = cabc->backlight & 0xf;
	cmd[4] = 0x02;
	cmd[5] = 0x02;
	cmd[6] = 0x04;
	cmd[7] = 0x04;
	cmd[8] = 0x00;
	cmd[9] = 0x5d;
#else
	cmd[2] = (cabc->backlight & 0xff0) >> 4;
	cmd[3] = cabc->backlight & 0xf;
#endif
*/
	cmd[2] = cabc->backlight;
	cmd[3] = cabc->backlight & 0xf;
	return dsi_set_packet(cmd, 2 + 1);
}

int dsi_get_pwm(struct r63306_pwm *pwm)
{
	u8 cmd[DSI_CMD_LEN];
	int ret;
	int i;

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, read_pfm_pwm_ctrl, sizeof(read_pfm_pwm_ctrl));
	ret = dsi_set_packet(cmd, 12);
	if (ret)
		return ret;
	pwm->divider = cmd[2];
	pwm->duty_cycle = ((cmd[3] << 8) | cmd[4]) & 0x1ff;
	pwm->pwm_wm = (cmd[3] & 0x10) ? 1 : 0;
#if 1
	pr_err("#%s, %d, divider:%d, duty_cycle:%d, pwm_wm:%d\n",
		__func__, __LINE__, pwm->divider, pwm->duty_cycle, pwm->pwm_wm);
	for (i = 0; i < 12; i++) {
		pr_err("c[%d]:0x%x ", i, cmd[i]);
	}
	pr_err("\n");
#endif
	return 0;
}
EXPORT_SYMBOL(dsi_get_pwm);

int dsi_set_pwm(struct r63306_pwm *pwm)
{
#if 1
	u8 cmd[DSI_CMD_LEN];

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, write_pfm_pwm_ctrl, sizeof(write_pfm_pwm_ctrl));
	cmd[2] = pwm->divider;
	cmd[3] = ((pwm->duty_cycle & 0x100) >> 8) | (pwm->pwm_wm << 4);
	cmd[4] = pwm->duty_cycle & 0xff;
	//cmd[4] = 0x0e;
	return dsi_set_packet(cmd, 12 + 1);
#else
	u8 cmd[DSI_CMD_LEN];
	int ret;

	memset(cmd, 0, DSI_CMD_LEN);
	memcpy(cmd, read_pfm_pwm_ctrl, sizeof(read_pfm_pwm_ctrl));
	ret = dsi_set_packet(cmd, 12);
	if (ret)
		return ret;
	cmd[0] = write_pfm_pwm_ctrl[0];
	cmd[2] = pwm->divider;
	cmd[3] = ((pwm->duty_cycle & 0x100) >> 8) | (pwm->pwm_wm << 4);
	cmd[3] |= (1 << 4);
	cmd[4] = pwm->duty_cycle & 0xff;
	//cmd[4] = 0x0e;
	cmd[5] = 0x73;
	return dsi_set_packet(cmd, 12 + 1);
#endif
}
EXPORT_SYMBOL(dsi_set_pwm);

static int r63306_probe(struct platform_device *pdev)
{
	struct r63306_chip *chip;
	struct r63306_device_id id;
	struct r63306_cabc cabc;
	int ret;

	if (dsi_get_id(&id) < 0 || id.vendor != RENESAS_ID_VENDOR) {
		dev_err(&pdev->dev, "Can't detect Renesas chip\n");
		return -EPROBE_DEFER;
	}

	/* set pwm on */
	ret = dsi_get_cabc(&cabc);
	if (ret < 0)
		return -EPROBE_DEFER;
	//cabc.pwm_on = true;
	ret = dsi_set_cabc(&cabc);
	if (ret < 0)
		return -EPROBE_DEFER;
	chip = kzalloc(sizeof(struct r63306_chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;
	chip->dev = &pdev->dev;

	ret = mfd_add_devices(chip->dev, 0, pwm_devs, ARRAY_SIZE(pwm_devs),
			      NULL, 0, NULL);
	if (ret)
		goto err;
	return 0;
err:
	kfree(chip);
	return ret;
}

static int r63306_remove(struct platform_device *pdev)
{
	return 0;
}

static const struct of_device_id r63306_of_match[] = {
	{ .compatible = "renesas,r63306", },
	{},
};
MODULE_DEVICE_TABLE(of, r63306_of_match);

static struct platform_driver r63306_driver = {
	.probe	= r63306_probe,
	.remove	= r63306_remove,
	.driver	= {
		.name	= "r63306",
		.owner	= THIS_MODULE,
		.of_match_table	= r63306_of_match,
	},
};
module_platform_driver(r63306_driver);
