/*
 *  Hisilicon K3 SOC camera driver source file
 *
 *  Copyright (C) Huawei Technology Co., Ltd.
 *
 * Author:
 * Email:
 * Date:	  2014-11-15
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


#include "hwois.h"

//#define OIS_ID_CODE		0x24
//#define I2V(i) container_of(i, ois_t, intf)

static hw_ois_vtbl_t s_lc8981_vtbl;

static ois_t s_lc8981 =
{
	.intf = { .vtbl = &s_lc8981_vtbl, },
};

int lc8981_get_otp_ois(hw_ois_intf_t *ois_intf, void *data)
{
	/* todo */
	return 0;
}

int lc8981_i2c_read(hw_ois_intf_t *ois_intf, void *data)
{
	/* todo */
	return 0;
}

int lc8981_i2c_write(hw_ois_intf_t *ois_intf, void *data)
{
    /* todo */
	return 0;
}

int lc8981_ioctl(hw_ois_intf_t *ois_intf, void *data)
{
	struct hw_ois_cfg_data *cdata = (struct hw_ois_cfg_data*)data;
	int rc = 0;

	cam_debug("%s enter.\n", __func__);

	switch (cdata->cfgtype) {
	case CFG_OIS_SET_CFG:
		break;
	case CFG_OIS_GET_OTP_AF:
		rc = lc8981_get_otp_ois(ois_intf, data);
		break;
	default:
		rc = -EFAULT;
		cam_err("%s, invalid ois type(%d)! \n", __func__, cdata->cfgtype);
		break;
	}

	return rc;
}

static hw_ois_vtbl_t
s_lc8981_vtbl =
{
	.ois_config = hw_ois_config,
	.ois_i2c_read = lc8981_i2c_read,
	.ois_i2c_write = lc8981_i2c_write,
	.ois_ioctl = lc8981_ioctl,
};

static int32_t lc8981_platform_probe(struct platform_device *pdev)
{
	int rc = 0;
	cam_debug("enter %s",__func__);

	if (pdev->dev.of_node) {
		rc = hw_ois_get_dt_data(pdev, &s_lc8981);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto lc8981_probe_fail;
		}
	} else {
		cam_err("%s lc8981 of_node is NULL.\n", __func__);
		goto lc8981_probe_fail;
	}

	rc = hw_ois_register(pdev, &s_lc8981.intf, s_lc8981.ois_info);
lc8981_probe_fail:
	return rc;
}

static const struct of_device_id hw_lc8981_dt_match[] = {
	{.compatible = "hisi,lc8981"},
	{}
};
MODULE_DEVICE_TABLE(of, hw_lc8981_dt_match);
static struct platform_driver hw_lc8981_platform_driver = {
	.driver = {
		.name = "lc8981",
		.owner = THIS_MODULE,
		.of_match_table = hw_lc8981_dt_match,
	},
};

static int __init hw_lc8981_module_init(void)
{
	int rc = 0;
	cam_debug("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&hw_lc8981_platform_driver,
		lc8981_platform_probe);
	if (rc < 0) {
		cam_notice("%s platform_driver_probe error.\n", __func__);
	}
	return rc;
}

static void __exit hw_lc8981_module_exit(void)
{
	hw_ois_unregister(&s_lc8981.intf);
	platform_driver_unregister(&hw_lc8981_platform_driver);
}

module_init(hw_lc8981_module_init);
module_exit(hw_lc8981_module_exit);
MODULE_DESCRIPTION("LC8981 OIS");
MODULE_LICENSE("GPL v2");
