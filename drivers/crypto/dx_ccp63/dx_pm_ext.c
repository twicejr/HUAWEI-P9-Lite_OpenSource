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
#include "dx_sram_mgr.h"

/*
This function should suspend the HW (if possiable), It should be implemented by 
the driver user. 
The reference code clears the internal SRAM to imitate lose of state. 
*/
void dx_pm_ext_hw_suspend(struct device *dev)
{
	struct dx_drvdata *drvdata =
		(struct dx_drvdata *)dev_get_drvdata(dev);
	unsigned int val;
	void __iomem *cc_base = drvdata->cc_base;
	unsigned int  sram_addr = 0;
#if DX_CC_HAS_ROM 
	sram_addr = READ_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, HOST_SEP_SRAM_THRESHOLD));
#endif

	WRITE_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, SRAM_ADDR), sram_addr);

	for (;sram_addr < DX_CC_SRAM_SIZE ; sram_addr+=4) {
		WRITE_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, SRAM_DATA), 0x0);

		do {
			val = READ_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, SRAM_DATA_READY));
		} while (!(val &0x1));
	}
	WRITE_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, HOST_CC_SW_RST), 1);
	
	/*add to suspend seceng_p6.3*/
	if (regulator_is_enabled(drvdata->ccp_regu)) {
		val = regulator_disable(drvdata->ccp_regu);
		if (val) {
			DX_LOG_ERR("dx_pm_ext_hw_resume: regulator_disable error(%x)\n", val);
			return;
		}
	}
}

/*
This function should resume the HW (if possiable).It should be implemented by 
the driver user. 
*/
void dx_pm_ext_hw_resume(struct device *dev)
{
	/*add to resume seceng_p6.3*/
	int rc;
	struct dx_drvdata *drvdata = (struct dx_drvdata *)dev_get_drvdata(dev);
	if(NULL == drvdata)
	{
		DX_LOG_ERR("dx_pm_ext_hw_resume: dev_get_drvdata error!\n");
		return;
	}

	if (!regulator_is_enabled(drvdata->ccp_regu)) {
		rc = regulator_enable(drvdata->ccp_regu);
		if (rc) {
			DX_LOG_ERR("dx_pm_ext_hw_resume: regulator_enable error(%x)\n", rc);
		}
	}
}

