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

#ifndef __PM_OM_PLATFORM_H__
#define __PM_OM_PLATFORM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <linux/string.h>
#include <linux/semaphore.h>
#include <linux/wakelock.h>
#include <linux/miscdevice.h>
#include <linux/suspend.h>
#include <bsp_dump.h>
#include <bsp_icc.h>
#include <bsp_pm_om.h>

#define PM_OM_DUMP_ID           DUMP_AP_PM_OM
#define PM_OM_DUMP_SIZE         (0x10000)
#define PM_OM_ICC_ACORE_CHN_ID  (ICC_CHANNEL_ID_MAKEUP(ICC_CHN_IFC, IFC_RECV_FUNC_PM_OM))
#define PM_OM_CPUID             (IPC_CORE_ACORE)
#define PM_OM_WAKEUP_INTERVAL   (3000)
#define PM_OM_LOG_THRE_CORE_NUM (4)   /* 有几个核需要配置水线 */
#define PM_OM_LOG_THRE_BUF_SIZE (200) /* 从文件节点读取水线的buffer大小 */

#define memset_s(dest, destMax, val, count) memset(dest, val, count)
#define memcpy_s(dest, destMax, src, count) memcpy(dest, src, count)

struct pm_om_platform
{
	struct pm_om_ctrl   *ctrl;
	struct log_usr_info  log_info;
};

int pm_om_fwrite_trigger(void);
int pm_om_platform_init(void);

#ifdef __cplusplus
}
#endif

#endif  /* __PM_OM_PLATFORM_H__ */
