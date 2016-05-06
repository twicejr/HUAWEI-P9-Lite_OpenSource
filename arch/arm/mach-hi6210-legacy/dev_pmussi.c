/*
 * arch/arm/mach-k3v2/dev_pmussi.c
 *
 * Copyright (C) 2012 Hisilicon Co. Ltd.
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/mux.h>
#include <mach/platform.h>
#include <mach/pmussi_drv.h>
#include <mach/clk_name_interface.h>
#include <soc_baseaddr_interface.h>
#include <soc_ao_sctrl_interface.h>


static void pmussi_ctrl_init(void);
static void pmussi_ctrl_exit(void);

static struct pmussi_dev_info pmussi_info = {
    .init = pmussi_ctrl_init,
    .exit = pmussi_ctrl_exit,
    .phy_base_addr = SOC_PMUSSI_BASE_ADDR,
    .clk_name = CLK_PMUSSI,
    .clk = NULL,
    .regulator_name = NULL,
    .regulator = NULL,
};

static void __inline__ pmussi_rstdis(void)
{
    unsigned long sctrl_addr = (unsigned long)IO_ADDRESS(REG_BASE_SC_ON);
#if defined(CHIP_BB_HI6210)/*B020 Modify*/
    *(volatile int *)SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_ADDR(sctrl_addr) = \
    	(1<<SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_27preset_pmussi_n_START);
#else
    *(volatile int *)SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_ADDR(sctrl_addr) = \
    	(1<<SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_1pmussi_START);
#endif
#if defined CONFIG_MACH_HI6210SFT
    *(volatile int *)SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_ADDR(sctrl_addr) = 0x3;/*B020 Modify*/
    	/*(0x00ff0019);*/
#endif
}

static void __inline__ pmussi_rsten(void)
{
    unsigned long sctrl_addr = (unsigned long)IO_ADDRESS(REG_BASE_SC_ON);
#if defined(CHIP_BB_HI6210)/*B020 Modify*/
    *(volatile int *)SOC_AO_SCTRL_SC_PERIPH_RSTEN4_ADDR(sctrl_addr) = \
    	(1<<SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_27preset_pmussi_n_START);
#else
    *(volatile int *)SOC_AO_SCTRL_SC_PERIPH_RSTEN4_ADDR(sctrl_addr) = \
    	(1<<SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_1pmussi_START);
#endif
}



static void  pmussi_ctrl_init(void)
{
    struct pmussi_dev_info *di = (struct pmussi_dev_info*)&pmussi_info;


    if (di->clk)
        clk_enable(di->clk);

    if (di->regulator)
        regulator_enable(di->regulator);

    /*disable reset of pmussi*/
 /*
    pmussi_rstdis();ÒÑÒÆÖÁfastboot
*/
}

static void pmussi_ctrl_exit(void)
{
    struct pmussi_dev_info *di = (struct pmussi_dev_info*)&pmussi_info;

    pmussi_rsten();

    if (di->regulator)
        regulator_disable(di->regulator);

    if (di->clk)
        clk_disable(di->clk);

}

 static struct platform_device pmussi_device = {
	.name =	"pmussi",
	.dev  =	{
		.platform_data = &pmussi_info,
	},
	.id	= -1,
};


static int __init pmussi_dev_init(void)
{
    struct pmussi_dev_info *di = (struct pmussi_dev_info*)&pmussi_info;

    if (di->clk_name) {
        di->clk	= clk_get(NULL,	di->clk_name);
        if (IS_ERR(di->clk)) {
            printk("%s: get clk %s failed!\n",__FUNCTION__,di->clk_name);
            di->clk = NULL;
            goto pmussi_failed;
        }
    }

    if (di->regulator_name) {
        di->regulator = regulator_get(NULL,di->regulator_name);
        if (IS_ERR(di->regulator)) {
            printk("%s: get regulator %s failed!\n",__FUNCTION__,di->regulator_name);
            di->regulator = NULL;
            goto pmussi_failed;
        }
    }

    /* platform devices were addded here. */
    return platform_device_register(&pmussi_device);

pmussi_failed:
    if (di->clk) {
        clk_put(di->clk);
        di->clk = NULL;
    }
    if (di->regulator) {
        regulator_put(di->regulator);
        di->regulator = NULL;
    }
    return -EINVAL;
}

core_initcall(pmussi_dev_init);
