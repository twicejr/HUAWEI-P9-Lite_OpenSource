/*
 * hi6402-gpio driver.
 *
 * Copyright (c) 2014 Hisilicon Technologies CO.Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/irq.h>
#include <linux/hisi/hi64xx/hi_cdc_ctrl.h>
#include <linux/hisi/hi64xx/hi64xx_compat.h>
#include <linux/hisi/hi64xx/hi64xx_utils.h>
#include <linux/hisi/hi64xx/hi64xx_irq.h>


struct hi64xx_compat_data{
	struct hi_cdc_ctrl		*hi_cdc;
	struct hi64xx_irq		*p_irq;
};

static struct hi64xx_compat_data *hi64xx_compat = NULL;

unsigned int hi64xx_compat_reg_read(unsigned int reg_addr)
{
	if(!hi64xx_compat || !hi64xx_compat->hi_cdc){
		pr_err("%s:hi64xx_compat is not ready.\n",__FUNCTION__);
		return 0;
	}
	return hi_cdcctrl_reg_read(hi64xx_compat->hi_cdc, reg_addr);
}
EXPORT_SYMBOL(hi64xx_compat_reg_read);

int hi64xx_compat_reg_write(unsigned int reg_addr, unsigned int value)
{
	if(!hi64xx_compat || !hi64xx_compat->hi_cdc){
		pr_err("%s:hi64xx_compat is not ready.\n",__FUNCTION__);
		return -ENODEV;
	}
	return hi_cdcctrl_reg_write(hi64xx_compat->hi_cdc, reg_addr, value);
}
EXPORT_SYMBOL(hi64xx_compat_reg_write);

int hi64xx_compat_request_irq(int phy_irq_id, irq_handler_t handler, const char *name, void *priv_data)
{
	pr_info("%s:phy_irq_id is %d\n", __FUNCTION__, phy_irq_id);
	if(!hi64xx_compat || !hi64xx_compat->p_irq){
		pr_err("%s:hi64xx_compat is not ready.\n",__FUNCTION__);
		return 0;
	}
	return hi64xx_irq_request_irq(hi64xx_compat->p_irq, phy_irq_id, handler, name, priv_data);
}
EXPORT_SYMBOL(hi64xx_compat_request_irq);

int hi64xx_compat_init(struct hi_cdc_ctrl *hi_cdc, struct hi64xx_irq *irq)
{
	hi64xx_compat = kzalloc(sizeof(struct hi64xx_compat_data), GFP_KERNEL);
	if(NULL == hi64xx_compat){
		pr_err("%s : kzalloc error!\n", __FUNCTION__);
		return -ENOMEM;
	}

	hi64xx_compat->hi_cdc = hi_cdc;
	hi64xx_compat->p_irq = irq;

	pr_info("%s: init ok.\n", __FUNCTION__);

	return 0;
}
EXPORT_SYMBOL(hi64xx_compat_init);

void hi64xx_compat_deinit(void)
{
	if(hi64xx_compat != NULL)
		kfree(hi64xx_compat);
}
EXPORT_SYMBOL(hi64xx_compat_deinit);

MODULE_DESCRIPTION("hisi codec controller");
MODULE_AUTHOR("qupengcheng <qupengcheng@huawei.com>");
MODULE_LICENSE("GPL");
