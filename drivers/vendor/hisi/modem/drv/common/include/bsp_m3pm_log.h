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

#ifndef _BSP_M3PM_M3DPM_LOG_H_
#define _BSP_M3PM_M3DPM_LOG_H_

enum m3_mdm_dpm_log_mode
{
    m3_mdm_dpm_log_begin,
    m3_mdm_dpm_log_temp,
    m3_mdm_dpm_log_ipf,
    m3_mdm_dpm_log_butt
};

enum m3_mdm_pm_log_mode
{
    m3_mdm_pm_log_a9,
    m3_mdm_pm_log_a9_sr,
    m3_mdm_dpm_log_fail
};


#define M3PM_LOG_MODEM_DOWN_OFFSET      0
#define M3PM_LOG_MODEM_DOWN_SIZE        0x8

#define M3PM_LOG_MODEM_UP_OFFSET        (M3PM_LOG_MODEM_DOWN_OFFSET+M3PM_LOG_MODEM_DOWN_SIZE)
#define M3PM_LOG_MODEM_UP_SIZE          (0xC)

#define M3PM_LOG_MODEM_SUSPEND_OFFSET   (M3PM_LOG_MODEM_UP_OFFSET+M3PM_LOG_MODEM_UP_SIZE)
#define M3PM_LOG_MODEM_SUSPEND_SIZE     (0x10)

#define M3PM_LOG_MODEM_RESUME_OFFSET    (M3PM_LOG_MODEM_SUSPEND_OFFSET+M3PM_LOG_MODEM_SUSPEND_SIZE)
#define M3PM_LOG_MODEM_RESUME_SIZE      (0x8)

#define M3PM_LOG_MODEM_RESUME_OK_OFFSET (M3PM_LOG_MODEM_RESUME_OFFSET+M3PM_LOG_MODEM_RESUME_SIZE)
#define M3PM_LOG_MODEM_RESUME_OK_SIZE   (0xC)

#define M3PM_LOG_MODEM_DPM_OFFSET       (M3PM_LOG_MODEM_RESUME_OK_OFFSET+M3PM_LOG_MODEM_RESUME_OK_SIZE)
#define M3PM_LOG_MODEM_DPM_SIZE         (0x4*m3_mdm_dpm_log_butt) 

#define M3PM_LOG_MDM_A9_SIZE            (M3PM_LOG_MODEM_DOWN_SIZE+M3PM_LOG_MODEM_UP_SIZE)
#define M3PM_LOG_MDM_SR_SIZE            (M3PM_LOG_MODEM_SUSPEND_SIZE+M3PM_LOG_MODEM_RESUME_SIZE+M3PM_LOG_MODEM_RESUME_OK_SIZE)
#define M3PM_LOG_MDM_A9_SR_SIZE         (M3PM_LOG_MDM_A9_SIZE+M3PM_LOG_MDM_SR_SIZE)

#define SHM_MEM_M3PM_LOG_ADDR           ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_M3PM_LOG)

#ifdef CONFIG_PM_OM
void m3_mdm_sr_update(void);
void m3_mdm_pm_dpm_log(void);

#else
static inline void m3_mdm_sr_update(void){return;}
static inline void m3_mdm_pm_dpm_log(void){return;}

#endif

#endif

