/***************************************************************
*  Copyright 2014 (c) Discretix Technologies Ltd.              *
*  This software is protected by copyright, international      *
*  treaties and various patents. Any copy, reproduction or     *
*  otherwise use of this software must be authorized in a      *
*  license agreement and include this Copyright Notice and any *
*  other notices specified in the license agreement.           *
*  Any redistribution in binary form must be authorized in the *
*  license agreement and include this Copyright Notice and     *
*  any other notices specified in the license agreement and/or *
*  in materials provided with the binary distribution.         *
****************************************************************/


#include "dx_config.h"
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <crypto/ctr.h>
#include <linux/pm_runtime.h>
#include "dx_driver.h"
#include "dx_buffer_mgr.h"
#include "dx_request_mgr.h"
#include "hw_queue_defs.h"
#include "dx_sram_mgr.h"
#include "dx_sysfs.h"
#include "dx_ivgen.h"
#include "dx_hash.h"
#include "dx_pm.h"
#include "dx_pm_ext.h"


#if defined(CONFIG_PM_RUNTIME)

int dx_power_mgr_runtime_suspend(struct device *dev)
{
	struct dx_drvdata *drvdata =
		(struct dx_drvdata *)dev_get_drvdata(dev);
	int rc;

	rc = dx_request_mgr_runtime_suspend_queue(drvdata);
	if (rc != 0) {
		DX_LOG_ERR("dx_runtime_suspend_queue (%x)\n", rc);
		return rc;
	}
	fini_cc_regs(drvdata);

	/* Specific HW suspend code */
	dx_pm_ext_hw_suspend(dev);
	return 0;
}

int dx_power_mgr_runtime_resume(struct device *dev)
{
	int rc;
	struct dx_drvdata *drvdata =
		(struct dx_drvdata *)dev_get_drvdata(dev);

	/* Specific HW resume code */
	dx_pm_ext_hw_resume(dev);

	rc = init_cc_regs(drvdata, false);
	if (rc !=0) {
		DX_LOG_ERR("init_cc_regs (%x)\n",rc);
		return rc;
	}

	rc = dx_request_mgr_runtime_resume_queue(drvdata);
	if (rc !=0) {
		DX_LOG_ERR("dx_runtime_resume_queue (%x)\n",rc);
		return rc;
	}

	/* must be after the queue resuming as it uses the HW queue*/
	dx_hash_init_sram_digest_consts(drvdata);
	
	dx_ivgen_init_sram_pool(drvdata);
	return 0;
}

int dx_power_mgr_runtime_get(struct device *dev)
{
	int rc = 0;

	if (dx_request_mgr_is_queue_runtime_suspend(
				(struct dx_drvdata *)dev_get_drvdata(dev))) {
		rc = pm_runtime_get_sync(dev);
	} else {
		pm_runtime_get_noresume(dev);
	}
	return rc;
}

int dx_power_mgr_runtime_put_suspend(struct device *dev)
{
	int rc = 0;

	if (!dx_request_mgr_is_queue_runtime_suspend(
				(struct dx_drvdata *)dev_get_drvdata(dev))) {
		pm_runtime_mark_last_busy(dev);
		rc = pm_runtime_put_autosuspend(dev);
	}
	else {
		/* Something wrong happens*/
		BUG();
	}
	return rc;

}
#endif

#if defined(CONFIG_PM_SLEEP)
int dx_power_mgr_suspend(struct device *dev)
{
	struct dx_drvdata *drvdata =
		(struct dx_drvdata *)dev_get_drvdata(dev);

	DX_LOG_INFO("+\n");

#if defined(CONFIG_PM_RUNTIME)
	if (!dx_request_mgr_is_queue_runtime_suspend(drvdata)) {
#endif
		if (dx_request_mgr_queue_busy(drvdata)) {
			DX_LOG_ERR("queue is busy\n");
			DX_LOG_INFO("-\n");
			return -EBUSY;
		}

		fini_cc_regs(drvdata);

		/* Specific HW suspend code */
		dx_pm_ext_hw_suspend(dev);
#if defined(CONFIG_PM_RUNTIME)
	}
#endif

	DX_LOG_INFO("-\n");
	return 0;
}

int dx_power_mgr_resume(struct device *dev)
{
	struct dx_drvdata *drvdata =
		(struct dx_drvdata *)dev_get_drvdata(dev);
	int rc = 0;

	DX_LOG_INFO("+\n");

#if defined(CONFIG_PM_RUNTIME)
	if (!dx_request_mgr_is_queue_runtime_suspend(drvdata)) {
#endif
		/* Specific HW resume code */
		dx_pm_ext_hw_resume(dev);

		rc = init_cc_regs(drvdata, false);
		if (rc !=0) {
			DX_LOG_ERR("init_cc_regs (%x)\n",rc);
			DX_LOG_INFO("-\n");
			return rc;
		}

		/* must be after the queue resuming as it uses the HW queue*/
		dx_hash_init_sram_digest_consts(drvdata);

		dx_ivgen_init_sram_pool(drvdata);
#if defined(CONFIG_PM_RUNTIME)
	}
#endif

	DX_LOG_INFO("-\n");
	return 0;
}

#endif

int dx_power_mgr_init(struct dx_drvdata *drvdata)
{
	int rc = 0;
#if defined(CONFIG_PM_RUNTIME)
	struct platform_device *plat_dev = drvdata->plat_dev;
	/* must be before the enabling to avoid resdundent suspending */
	pm_runtime_set_autosuspend_delay(&plat_dev->dev,DX_SUSPEND_TIMEOUT);
	pm_runtime_use_autosuspend(&plat_dev->dev);
	/* activate the PM module */
	rc = pm_runtime_set_active(&plat_dev->dev);
	if (rc != 0)
		return rc;
	/* enable the PM module*/
	pm_runtime_enable(&plat_dev->dev);
#endif
	return rc;
}

void dx_power_mgr_fini(struct dx_drvdata *drvdata)
{
#if defined(CONFIG_PM_RUNTIME)
	struct platform_device *plat_dev = drvdata->plat_dev;

	pm_runtime_disable(&plat_dev->dev);
#endif
}
