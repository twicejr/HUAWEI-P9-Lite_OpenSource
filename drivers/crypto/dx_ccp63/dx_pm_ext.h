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

/* \file dx_pm_ext.h
    */

#ifndef __PM_EXT_H__
#define __PM_EXT_H__


#include "dx_config.h"
#include "dx_driver.h"

void dx_pm_ext_hw_suspend(struct device *dev);

void dx_pm_ext_hw_resume(struct device *dev);


#endif /*__POWER_MGR_H__*/

