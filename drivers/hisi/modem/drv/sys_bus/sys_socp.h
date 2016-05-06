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

#ifndef __SYS_SOCP_H__
#define __SYS_SOCP_H__


#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <bsp_sram.h>
#include <bsp_socp.h>
#include <sys_bus_pressure.h>
#include <mdrv_socp_common.h>

struct socp_press_case_s{
    u32                             bDstSet;
    u32                             SrcCh;
    u32                             DstCh;
    u32		                        u32BypassEn;
    SOCP_DATA_TYPE_ENUM_UIN32       eDataType;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32  eMode;
    SOCP_CHAN_PRIORITY_ENUM_UIN32   ePriority;
    u32                             u32Reseve1;
    u8*                             u32InputStart;
    u32                             u32InputSize;
    u32                             u32Reseve2;
    u8*                             u32RDStart;
    u32                             u32RDSize;
    u32                             u32Reseve3;
    u32                             u32RDThreshold;
    u32                             u32OutputStart;
    u32                             u32OutputSize;
    u32                             u32Threshold;
    socp_event_cb                   EventCb;
    socp_read_cb                    ReadCb;
    socp_rd_cb                      RdCb;
    u32                             TaskId;
    u32                             u32DataLen;
    u32                             u32DataCnt;
    SOCP_DATA_TYPE_EN_ENUM_UIN32    eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32    eEncDebugEn;
    u32                             u32EncDstThrh;
};


void sys_socp_init(struct master* master);

void sys_socp_stop(struct master* master);
void sys_socp_start(struct master* master);


void sys_socp_report(struct master* master);

void sys_socp_record(struct master* master);



#endif /* __SYS_SOCP_H__ */


