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

#include "hisi_vcm.h"
#include "vcm_driver.h"

#define VCM_ID_CODE		0x5823

int ad5823_ioctl(struct hisi_vcm_ctrl_t *vcm_ctrl, void *data)
{
	struct vcm_cfg_data *cdata = (struct vcm_cfg_data*)data;
	long   rc = 0;

	cam_debug("%s enter.\n", __func__);

	switch (cdata->cfgtype) {
	case CFG_VCM_SET_CFG:
		break;
	default:
		rc = -EFAULT;
		break;
	}

	return rc;
}

int ad5823_i2c_read(struct hisi_vcm_ctrl_t *vcm_ctrl, void *data)
{
	struct vcm_cfg_data *cdata = (struct vcm_cfg_data *)data;
	//struct vcm_i2c_reg reg;
	int   rc = -1;

	cam_info("%s: address=0x%x\n", __func__, cdata->cfg.reg.address);
	//todo ...
	cdata->cfg.reg.value = VCM_ID_CODE;
	return rc;
}

int ad5823_i2c_write(struct hisi_vcm_ctrl_t *vcm_ctrl, void *data)
{
	struct vcm_cfg_data *cdata = (struct vcm_cfg_data *)data;
	int   rc = 0;

	cam_debug("%s enter.\n", __func__);

	cam_debug("%s: address=0x%x, value=0x%x\n", __func__,
		cdata->cfg.reg.address, cdata->cfg.reg.value);

	rc = isp_write_vcm(vcm_ctrl->vcm->vcm_info->slave_address,
			(u16)cdata->cfg.reg.address,
			(u16)cdata->cfg.reg.value,
			vcm_ctrl->vcm->vcm_info->data_type);

	return rc;
}

static struct hisi_vcm_fn_t ad5823_func_tbl = {
	.vcm_config = hisi_vcm_config,
	.vcm_i2c_read = hisi_vcm_i2c_read,
	.vcm_i2c_write = hisi_vcm_i2c_write,
	.vcm_ioctl = ad5823_ioctl,
};

static int32_t ad5823_vcm_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	struct hisi_vcm_t *vcm = NULL;
	cam_debug("%s enter.\n", __func__);
	vcm = (struct hisi_vcm_t*)kmalloc(sizeof(struct hisi_vcm_t),
						GFP_KERNEL);
	if (NULL == vcm) {
		return -ENOMEM;
	}

	vcm->func_tbl = &ad5823_func_tbl;

	if (pdev->dev.of_node) {
		rc = hisi_vcm_get_dt_data(pdev, vcm);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			kfree(vcm);
			vcm = NULL;
			return rc;
		}
	} else {
		cam_err("%s ad5823 of_node is NULL.\n", __func__);
		kfree(vcm);
		vcm = NULL;
		return rc;
	}

	rc = hisi_vcm_add(vcm);
	if (rc < 0) {
		cam_err("%s fail to add vcm into vcm array.\n", __func__);
		kfree(vcm);
		vcm = NULL;
		return rc;
	}
	if (!dev_get_drvdata(&pdev->dev)) {
		dev_set_drvdata(&pdev->dev, (void *)vcm);
	}
	return rc;
}

static const struct of_device_id hisi_ad5823_dt_match[] = {
	{.compatible = "hisi,ad5823"},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_ad5823_dt_match);
static struct platform_driver ad5823_platform_driver = {
	.driver = {
		.name = "ad5823",
		.owner = THIS_MODULE,
		.of_match_table = hisi_ad5823_dt_match,
	},
};

static int32_t ad5823_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	const struct of_device_id *match;
	match = of_match_device(hisi_ad5823_dt_match, &pdev->dev);
	cam_info("%s compatible=%s.\n", __func__, match->compatible);
	rc = ad5823_vcm_probe(pdev);
	return rc;
}

static int __init ad5823_module_init(void)
{
	int rc = 0;
	cam_debug("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&ad5823_platform_driver,
		ad5823_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error.\n", __func__);
	}
	return rc;
}

static void __exit ad5823_module_exit(void)
{
	platform_driver_unregister(&ad5823_platform_driver);
}

MODULE_AUTHOR("HISI");
module_init(ad5823_module_init);
module_exit(ad5823_module_exit);
MODULE_LICENSE("GPL");
