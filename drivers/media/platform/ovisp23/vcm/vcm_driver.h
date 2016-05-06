
#ifndef _VCM_DRIVER_H_
#define _VCM_DRIVER_H_
#include "hisi_vcm.h"


int hisi_vcm_power_up(struct hisi_vcm_ctrl_t *vcm_ctrl);
int hisi_vcm_power_down(struct hisi_vcm_ctrl_t *vcm_ctrl);
int hisi_vcm_i2c_read(struct hisi_vcm_ctrl_t *vcm_ctrl, void *data);
int hisi_vcm_i2c_write(struct hisi_vcm_ctrl_t *vcm_ctrl, void *data);


#endif /*_VCM_DRIVER_H_*/
