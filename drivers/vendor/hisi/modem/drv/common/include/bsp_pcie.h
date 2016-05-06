/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __BSP_PCIE_H__
#define __BSP_PCIE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <product_config.h>
#include <bsp_sram.h>

#define PCIE_CFG_VALID  (0xA5A55A5A)

/******* work mode **********/
/* ep mode */
#ifndef PCIE_WORK_MODE_EP
#define PCIE_WORK_MODE_EP   (0x0)
#endif

/* legacy ep mode */
#ifndef PCIE_WORK_MODE_LEP
#define PCIE_WORK_MODE_LEP  (0x1)
#endif

/* rc mode */
#ifndef PCIE_WORK_MODE_RC
#define PCIE_WORK_MODE_RC   (0x4)
#endif

/* pcie_ports */
#ifndef PCIE_PORT_MODE_AUTO
#define PCIE_PORT_MODE_AUTO     (0x0)
#endif

#ifndef PCIE_PORT_MODE_NATIVE
#define PCIE_PORT_MODE_NATIVE   (0x1)
#endif

#ifndef PCIE_PORT_MODE_COMPAT
#define PCIE_PORT_MODE_COMPAT   (0x2)
#endif

/* clock mode */
#ifndef PCIE_CLOCK_MODE_OUTER
#define PCIE_CLOCK_MODE_OUTER   (0x0)
#endif

#ifndef PCIE_CLOCK_MODE_INNER
#define PCIE_CLOCK_MODE_INNER   (0x1)
#endif

#ifndef PCIE_CLOCK_MODE_DEFAULT
#define PCIE_CLOCK_MODE_DEFAULT (PCIE_CLOCK_MODE_INNER)
#endif

/* speed mode */
#ifndef PCIE_SPEED_MODE_DEFAULT
#define PCIE_SPEED_MODE_DEFAULT (0x0)
#endif


#ifndef PCIE_ENABLE
#define PCIE_ENABLE (0x1)
#endif
#ifndef PCIE_DISABLE
#define PCIE_DISABLE (0x0)
#endif


struct pcie_cfg
{
    unsigned int valid;
    unsigned int enabled;
    unsigned int work_mode;
    unsigned int port_mode;
    unsigned int clock_mode;
    unsigned int speed_mode;
    unsigned int msi_disable;
    unsigned int aspm_disable;
    unsigned int l1ss_disable;
    unsigned int output_clock_disable;
    unsigned int compliance_test_enable;
};

#define SRAM_PCIE_BALONG_ADDR  (unsigned int)(((SRAM_SMALL_SECTIONS*)(SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_PCIE_INFO)

void pcie_fastboot_init(void);
void pcie_fastboot_console(char *cmd);

#ifdef __cplusplus
}
#endif

#endif

