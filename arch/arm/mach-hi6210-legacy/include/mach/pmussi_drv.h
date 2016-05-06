/*
 * arch/arm/mach-k3v2/include/mach/dev_pmussi.h
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

#ifndef __PMUSSI_DRV_H
#define __PMUSSI_DRV_H

#include <mach/fixmap.h>

#include "soc_baseaddr_interface.h"
#include "soc_ao_sctrl_interface.h"

#define PMU_VERSION_SSI_BUG     (0X24)

#define AOSCTRL_SC_MCU_VOTE1EN0		SOC_AO_SCTRL_SC_MCU_VOTE1EN_ADDR(REG_BASE_SC_ON_VIRT)
#define AOSCTRL_SC_SYS_STAT0		SOC_AO_SCTRL_SC_SYS_STAT0_ADDR(REG_BASE_SC_ON_VIRT)
#define AOSCTRL_SC_MCU_VOTE1DIS0	SOC_AO_SCTRL_SC_MCU_VOTE1DIS_ADDR(REG_BASE_SC_ON_VIRT)
#define AOSCTRL_SC_SYS_CTRL1		SOC_AO_SCTRL_SC_SYS_CTRL1_ADDR(REG_BASE_SC_ON_VIRT)

typedef enum _SSI_VOTE1_E_
{
    VOTE1_MCU_PMU_GET = 0,
    VOTE1_MCU_PMU_SET = 1,
    VOTE1_ACPU_PMU_GET = 8,
    VOTE1_ACPU_PMU_SET = 9,
    VOTE1_CCPU_PMU_GET = 16,
    VOTE1_CCPU_PMU_SET = 17,
    VOTE1_DVFS_DDR    =  24,
    VOTE1_DVFS_ACPU   = 25,
    VOTE1_BUTT
}SSI_VOTE1_E;

struct pmussi_dev_info
{
    void (*init) (void);
    void (*exit) (void);

    unsigned long       phy_base_addr;
    char                *clk_name;
    struct clk          *clk;
    char                *regulator_name;
    struct regulator    *regulator;
};

extern unsigned char pmussi_reg_read (unsigned int reg_addr);
extern void pmussi_reg_write (unsigned int reg_addr, unsigned char regval);
extern int pmussi_recv_data (unsigned int reg_addr, char *buffer, int len);
extern int pmussi_send_data (unsigned int reg_addr, char *buffer, int len);

#endif
