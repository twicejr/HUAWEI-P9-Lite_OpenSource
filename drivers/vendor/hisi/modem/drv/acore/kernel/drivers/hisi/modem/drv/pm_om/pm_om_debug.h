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

#ifndef __PM_OM_DEBUG_H__
#define __PM_OM_DEBUG_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <linux/wakelock.h>
#include <linux/notifier.h>
#include <bsp_pm_om.h>

#define TIME_SLICE_FREQ  (32768)
struct pm_om_stat
{
	u32 wakeup_cnt;    /* 唤醒acore的次数 */
	u32 waket_prev;    /* 唤醒acore的上一次的时间 */
	u32 waket_min;     /* 唤醒acore的最短时间间隔 */
	u32 waket_max;     /* 唤醒acore的最长时间间隔 */
	u32 logt_max;      /* 两次唤醒acore的时间阈值 */
	u32 logt_print_sw; /* 打印开关 */
	u32 wrs_flag;      /* 唤醒源分解时打印开关 */
};

struct pm_om_debug
{
	struct pm_om_stat stat;
	struct pm_om_ctrl *ctrl;
	struct notifier_block pm;
	char   *cdrx_dump_addr;
	char   *cdrx_dump_corepm_addr;
	struct wake_lock wakelock_debug;
};

int pm_om_debug_init(void);
void pm_om_wakeup_stat(void);
u32 pm_om_log_time_rec(u32 time_log_start);
static inline void pm_om_log_time_print(u32 log_sw)
{
	if (log_sw > 0)
	{
		pmom_pr_err("elapse time is %d(slice)\n", log_sw);
	}
}


#ifdef __cplusplus
}
#endif

#endif  /* __PM_OM_DEBUG_H__ */
