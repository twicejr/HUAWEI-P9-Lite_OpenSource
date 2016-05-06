/*
 * arch/arm/mach-k3v2/include/mach/irqs.h
 *
 * Copyright (c) Hisilicon Co. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __MACH_K3V2_IRQS_H
#define __MACH_K3V2_IRQS_H

#include <asm/irq.h>
#include "soc_irqs.h"

/*None SOC IRQ*/
#define IRQ_OCP_RISING                  (NR_SOC_IRQS + 0)
#define IRQ_GPIO_BASE                   (NR_SOC_IRQS + 1)
#define IRQ_GPIO(n)		                (IRQ_GPIO_BASE + n)
/*we have 14 gpio chips, 8 ports per chip*/
#define IRQ_GPIO_NR		                (20 * 8)

/*PMU IRQ NUMBER -S*/
#define IRQ_PMU_NR_BASE                 (IRQ_GPIO(IRQ_GPIO_NR))

#define OTMP_D1R_TYPE                   (IRQ_PMU_NR_BASE + 0)
#define VSYS_2P5_F_TYPE                 (IRQ_PMU_NR_BASE + 1)
#define VSYS_UV_D3R_TYPE                (IRQ_PMU_NR_BASE + 2)
#define VSYS_6P0_D200UR_TYPE            (IRQ_PMU_NR_BASE + 3)
#define POWERON_D4sR_TYPE               (IRQ_PMU_NR_BASE + 4)
#define POWERON_D20F_TYPE               (IRQ_PMU_NR_BASE + 5)
#define POWERON_D20R_TYPE               (IRQ_PMU_NR_BASE + 6)
#define RESERVED_IRQ1_TYPE              (IRQ_PMU_NR_BASE + 7)

#define IRQ_VBUS_COMP_VBAT_FALLING      (IRQ_PMU_NR_BASE + 8)
#define IRQ_VBUS_COMP_VBAT_RISING        (IRQ_PMU_NR_BASE + 9)
#define OCP_SCP_R_TYPE                                (IRQ_PMU_NR_BASE + 10)
#define RESERVED_IRQ2_0_TYPE            (IRQ_PMU_NR_BASE + 11)
#define RESERVED_IRQ2_1_TYPE            (IRQ_PMU_NR_BASE + 12)
#define RESERVED_IRQ2_2_TYPE            (IRQ_PMU_NR_BASE + 13)
#define RESERVED_IRQ2_3_TYPE            (IRQ_PMU_NR_BASE + 14)
#define RESERVED_IRQ2_4_TYPE            (IRQ_PMU_NR_BASE + 15)

#define TCXO_CLK_SEL_R_TYPE                 (IRQ_PMU_NR_BASE + 16)
#define TCXO_CLK_SEL_F_TYPE                 (IRQ_PMU_NR_BASE + 17)
#define DCXO_CLK_SEL_R_TYPE                 (IRQ_PMU_NR_BASE + 18)
#define DCXO_CLK_SEL_F_TYPE                 (IRQ_PMU_NR_BASE + 19)
#define ALARM_ON_TYPE                             (IRQ_PMU_NR_BASE + 20)
#define RESERVED_IRQ3_0_TYPE                 (IRQ_PMU_NR_BASE + 21)
#define RESERVED_IRQ3_1_TYPE            (IRQ_PMU_NR_BASE + 22)
#define RESERVED_IRQ3_2_TYPE            (IRQ_PMU_NR_BASE + 23)

#define CL_INT_I_TYPE                              (IRQ_PMU_NR_BASE + 24)
#define CL_OUT_I_TYPE                             (IRQ_PMU_NR_BASE + 25)
#define CL_IN_I_TYPE                                (IRQ_PMU_NR_BASE + 26)
#define VBAT_INT_I_TYPE                          (IRQ_PMU_NR_BASE + 27)
#define RESERVED_IRQ5_0_TYPE               (IRQ_PMU_NR_BASE + 28)
#define RESERVED_IRQ5_1_TYPE               (IRQ_PMU_NR_BASE + 29)

/*stubs for v9 coul*/
#define CHG_TIMER_I_TYPE                       (IRQ_PMU_NR_BASE + 30)
#define LOAD_TIMER_I_TYPE                     (IRQ_PMU_NR_BASE + 31)

#define IRQ_PMU_NR_END                  (LOAD_TIMER_I_TYPE + 1)

/*PMU IRQ NUMBER -E*/

#define NR_IRQS                         (IRQ_PMU_NR_END)

#define IRQ_G3D_MALI                    (IRQ_G3D)

#endif
