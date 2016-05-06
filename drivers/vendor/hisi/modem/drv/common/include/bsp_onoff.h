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

#ifndef _BSP_ONOFF_H_
#define _BSP_ONOFF_H_

#include <osl_common.h>
#include <osl_sem.h>
#include "bsp_softtimer.h"

#if defined(__KERNEL__) || defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__)
#include "power_com.h"

#include "mdrv_sysboot.h"
void drv_shut_down(DRV_SHUTDOWN_REASON_E enReason);

#define EXCH_ONOFF_LOG_MAX      (0x400*16)
#define pr_dbg printk

typedef struct _tagCtrlMsg
{
    ePowCrtlType             pwr_type;
    DRV_START_MODE_E         mode;
    DRV_SHUTDOWN_REASON_E    reason;
}stCtrlMsg;

typedef struct _tagPowCtrl
{
    unsigned int    is_init;        /* 1:have initialized*/
    osl_sem_id      pwr_sem;
    stCtrlMsg       curr;
}stPowCtrl;


void bsp_reboot_callback_register(void (*hook)(void));

int bsp_on_off_init( void );

void balong_power_off( void );
void balong_power_restart(char mode, const char *cmd);

void bsp_drv_power_reboot( void );

int bsp_start_mode_get(void);

void bsp_drv_power_off(void);

void power_on_c_status_set(c_power_st_e val);
#endif

void bsp_drv_power_reboot_direct(void);

#endif

