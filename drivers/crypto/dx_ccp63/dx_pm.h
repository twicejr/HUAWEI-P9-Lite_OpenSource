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

/* \file dx_power_mgr.h
    */

#ifndef __POWER_MGR_H__
#define __POWER_MGR_H__


#include "dx_config.h"
#include "dx_driver.h"


#define DX_SUSPEND_TIMEOUT 3000


int dx_power_mgr_init(struct dx_drvdata *drvdata);

void dx_power_mgr_fini(struct dx_drvdata *drvdata);

#if defined(CONFIG_PM_RUNTIME)
int dx_power_mgr_runtime_suspend(struct device *dev);

int dx_power_mgr_runtime_resume(struct device *dev);

int dx_power_mgr_runtime_get(struct device *dev);

int dx_power_mgr_runtime_put_suspend(struct device *dev);
#endif

#if defined(CONFIG_PM_SLEEP)
int dx_power_mgr_suspend(struct device *dev);

int dx_power_mgr_resume(struct device *dev);
#endif

#endif /*__POWER_MGR_H__*/

