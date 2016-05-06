/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include "hisi_fb.h"

static int g_blpwm_on = 0;
#define BLPWM_ON   1
#define BLPWM_OFF 0
#define BLPWM_OUT_PRECISION	(10000)

#define SET_BACKLIGHT_PATH "/sys/devices/platform/huawei_sensor/sbl_setbacklight"

static int  hisifb_write_file(char *filename, char *buf, uint32_t buf_len)
{
	ssize_t write_len = 0;
	struct file *fd = NULL;
	mm_segment_t old_fs;
	loff_t pos = 0;

	BUG_ON(filename == NULL);
	BUG_ON(buf == NULL);

	fd = filp_open(filename, O_CREAT|O_RDWR, 0644);
	if (IS_ERR(fd)) {
		HISI_FB_ERR("filp_open returned:filename %s, error %ld\n",
			filename, PTR_ERR(fd));
		 return -1;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	write_len = vfs_write(fd, (char __user*)buf, buf_len, &pos);

	pos = 0;
	set_fs(old_fs);
	filp_close(fd, NULL);
	return 0;
}


static int send_bcaklight_to_shb( uint32_t bl_level )
{
	int ret = 0;
	char buffer[32];
	int bytes = 0;
	bytes = snprintf(buffer, sizeof(buffer), "T%d\n", bl_level);
	ret = hisifb_write_file(SET_BACKLIGHT_PATH, buffer, bytes);
	return ret;
}

static int send_power_state_to_shb( uint32_t power_state )
{
	int ret = 0;
	char buffer[32];
	int bytes = 0;
	if( power_state == 0) //off
		bytes = snprintf(buffer, sizeof(buffer), "F\n");
	else
		bytes = snprintf(buffer, sizeof(buffer), "O\n");
	ret = hisifb_write_file(SET_BACKLIGHT_PATH, buffer, bytes);
	return ret;
}


int hisi_sh_blpwm_set_backlight(struct hisi_fb_data_type *hisifd, uint32_t bl_level)
{
	int ret = 0;
	struct hisi_panel_info *pinfo = NULL;
	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);
	BUG_ON(pinfo == NULL);

	HISI_FB_DEBUG("BLPWM fb%d, bl_level=%d.\n", hisifd->index, bl_level);
	if( !pinfo->bl_max ) {
		HISI_FB_ERR("BLPWM pinfo->bl_max=%d.\n", pinfo->bl_max);
		return -1;
	}
	bl_level = (bl_level*BLPWM_OUT_PRECISION)/pinfo->bl_max;
	ret = send_bcaklight_to_shb(bl_level);
	return ret;
}


int hisi_sh_blpwm_on(struct platform_device *pdev)
{
	int ret = 0;
	BUG_ON(pdev == NULL);

	if (g_blpwm_on == 1)
		return 0;

	HISI_FB_DEBUG("BLPWM start sensorhub blpwm on \n");
	ret = send_power_state_to_shb(BLPWM_ON);

	g_blpwm_on = 1;

	return ret;
}

int hisi_sh_blpwm_off(struct platform_device *pdev)
{
	int ret = 0;
	BUG_ON(pdev == NULL);

	if (g_blpwm_on == 0)
		return 0;

	HISI_FB_DEBUG("BLPWM start sensorhub blpwm off \n");
	ret = send_power_state_to_shb(BLPWM_OFF);
	g_blpwm_on = 0;

	return ret;
}

