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

#include "isp_driver.h"

int hisi_isp_config(struct hisi_isp_ctrl_t *isp_ctrl, void *data)
{
	int rc = 0;

	cam_debug("%s enter.\n", __func__);

	mutex_lock(isp_ctrl->hisi_isp_mutex);

	/*TO DO*/

	mutex_unlock(isp_ctrl->hisi_isp_mutex);
	return rc;
}

struct hisi_isp_fn_t hisi_isp_func_tbl = {
	.isp_config = hisi_isp_config,
};