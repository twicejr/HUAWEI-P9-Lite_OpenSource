
#include "vcm_driver.h"

int hisi_vcm_power_up(struct hisi_vcm_ctrl_t *vcm_ctrl)
{
	cam_debug("%s enter.\n", __func__);
	return 0;
}

int hisi_vcm_power_down(struct hisi_vcm_ctrl_t *vcm_ctrl)
{
	cam_debug("%s enter.\n", __func__);
	return 0;
}

int hisi_vcm_i2c_read(struct hisi_vcm_ctrl_t *vcm_ctrl, void *data)
{
	struct vcm_cfg_data *cdata = (struct vcm_cfg_data *)data;
	//struct vcm_i2c_reg reg;
	int   rc = 0;

	cam_info("%s: address=0x%x\n", __func__, cdata->cfg.reg.address);
	cdata->cfg.reg.value = 0x5823;
	return rc;
}

int hisi_vcm_i2c_write(struct hisi_vcm_ctrl_t *vcm_ctrl, void *data)
{
	struct vcm_cfg_data *cdata = (struct vcm_cfg_data *)data;
	int   rc = 0;

	cam_debug("%s enter.\n", __func__);

	cam_info("%s: address=0x%x, value=0x%x\n", __func__,
		cdata->cfg.reg.address, cdata->cfg.reg.value);

	return rc;
}