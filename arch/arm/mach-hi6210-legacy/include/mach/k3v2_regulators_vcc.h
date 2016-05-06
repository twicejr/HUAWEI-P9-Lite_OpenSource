/*
 * arch/arm/mach-k3v2/k3v2_regulators_vcc.h
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#ifndef __K3V2_REGULATORS_VCC_H_
#define __K3V2_REGULATORS_VCC_H_
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>

/*soft reset enable register of edc1,isp,venc,vdec,bt*/
#define SC_PW_RSTEN0 0x810
#define SC_PW_RSTDIS0  0x814
#define SC_PW_RSTEN1 0x818
#define SC_PW_RSTDIS1 0x81C
#define SC_PW_ISOEN0 0x820
#define SC_PW_ISODIS0 0x824
#define SC_PW_ISOEN1 0x828
#define SC_PW_ISODIS1 0x82C
#define SC_PW_EN0  0x830
#define SC_PW_DIS0 0x834
#define SC_PW_EN1  0x838
#define SC_PW_DIS1 0x83C
#define SCCPUCOREEN 0x250
#define SCCPUCOREDIS 0x254
#define SCCPUCORESTAT 0x258
#define SC_ACPU_CTRL0 0x200
#define SC_PW_STAT0 0x850
#define SC_PW_STAT1 0x854
#define SC_PERIPH_RSTEN1 0x6CC


#define SC_PERIPH_RSTDIS0 0x6C4
#define SC_PERIPH_RSTDIS1 0x6D0
#define SC_PERIPH_RSTDIS2 0x6DC
#define SC_PERIPH_RSTDIS3 0x6E8
#define SC_PERIPH_RSTDIS4 0x6F4
#define SC_PERIPH_RSTDIS5 0x700
#define SC_PERIPH_RSTDIS6 0x70C

#define SC_PERIPH_CLKEN0 0x600
#define SC_PERIPH_CLKEN1 0x60C
#define SC_PERIPH_CLKEN2 0x618
#define SC_PERIPH_CLKEN3 0x624
#define SC_PERIPH_CLKEN4 0x630
#define SC_PERIPH_CLKEN5 0x63C
#define SC_PERIPH_CLKEN6 0x648
#define SC_PERIPH_CLKEN7 0x654
#define SC_PERIPH_CLKEN8 0x660
#define SC_PERIPH_CLKEN9 0x66C
#define SC_PERIPH_CLKEN10 0x678
#define SC_PERIPH_CLKEN11 0x684

#define SC_PW_CLKEN0 0x800
#define SC_PW_CLKEN1 0x808

#define SCCTRLCLKCFG 0xCBC
#define SCCTRLCLKENCDECCFG 0xCC4

#define EN_REG 0xC0
#define DIS_REG 0xC4
#define EN_STAT_REG 0xC8
#define PWR_EN_REG 0xD0
#define PWR_DIS_REG 0xD4
#define PWR_STAT_REG 0xD8
#define PWR_ACK_REG 0xDC
#define SCCPURSTEN_REG 0x410
#define SCCPUCLKOFF_REG 0x404
#define SCCPURSTDIS_REG 0x414
/*soft reset disable register of edc1,isp,venc,vdec,bt*/
#define SCPERRSTDIS1_REG 0x090
/*soft reset enable register of edc1,isp,venc,vdec,bt*/
#define SCPERRSTEN1_REG 0x08c
#define SCPERRSTSTAT1_REG 0x094
#define SCCPURSTSTAT_REG 0x418
#define SCPERCTRL0_WFI_REG 0x200
#define SCCPUCOREEN_REG 0x0F4
#define SCCPUCOREDIS_REG 0x0F8
#define G3D_CLK_EN_REG 0x030
#define G3D_CLK_DISEN_REG 0x034

#define VCC_EDC1 0
#define VCC_ISP 1
#define VCC_VENC 2
#define VCC_VDEC 3
#define VCC_BT 4
#define VCC_CPU2 5
#define VCC_CPU3 6
#define VCC_G3D 7
#define G3D_CORE_RST_BIT 8
#define G3D_INTF_RST_BIT 9
#define LDI1_CLOCK 10
#define PLL2_CLOCK 11
/*edc1's rate, 18750000 64 division of pll2 1200M*/
#define EDC_RST_RATE_FROM_1080M (1080000000 >> 6) /*edc1's rate, 64 division of pll2 1200M*/
#define EDC_RST_RATE_FROM_1400M (1400000000 >> 6) /*edc1's rate, 64 division of pll2 1050M*/
struct vcc_resource {
		void __iomem	*base;
		struct resource	*res;
		struct regulator_dev	*rdev[8];
		unsigned int irq;
};

extern struct regulator_ops vcc_med_ops;
extern struct regulator_ops vcc_cpu23_ops;
extern struct regulator_ops vcc_edc1_ops;
extern struct regulator_ops vcc_g3d_ops;
/*extern struct regulator_ops vcc_ops;*/
extern struct regulator_desc vcc_regulator_desc[];
extern struct platform_device vcc_regulator_device;
#endif
