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

#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <osl_generic.h>
#include <bsp_hardtimer.h>
#include <bsp_pm_om.h>
#include "pm_om_platform.h"
#include "pm_om_debug.h"

struct pm_om_platform g_pmom_platform;

int pm_log_read(struct log_usr_info *usr_info, char *buf, u32 count)
{
	struct ring_buffer rb;
	modem_log_ring_buffer_get(usr_info, &rb);

    if(bsp_ring_buffer_writable_size(&rb) <= 200) /* ÌáÇ°Çå¿Õbuffer */
    {
        usr_info->mem->read = usr_info->mem->write;
	}
	return 0;
}

int pm_om_fwrite_trigger(void)
{
	if (!g_pmom_platform.ctrl || !g_pmom_platform.ctrl->log.init_flag)
	{
		return PM_OM_ERR;
	}

	bsp_modem_log_fwrite_trigger(&(g_pmom_platform.log_info));
	return PM_OM_OK;
}

int pm_om_platform_init(void)
{
	int ret = PM_OM_OK;
	char *dev_name = "pmom";
	struct pm_om_ctrl *ctrl  = pm_om_ctrl_get();

	memset((void *)&g_pmom_platform, 0, sizeof(g_pmom_platform));
	g_pmom_platform.log_info.dev_name  = dev_name;
	g_pmom_platform.log_info.mem       = &(ctrl->log.smem->mem_info);
	g_pmom_platform.log_info.ring_buf  = ctrl->log.rb.buf;
	g_pmom_platform.log_info.read_func = (USR_READ_FUNC)pm_log_read;

	ret = bsp_modem_log_register(&g_pmom_platform.log_info);
	if (ret)
	{
		goto out;
	}
	g_pmom_platform.ctrl = ctrl;
	ctrl->platform = (void *)&g_pmom_platform;

	return PM_OM_OK;
out:
	pmom_pr_err("register modem log error\n");
	return PM_OM_ERR;
}
EXPORT_SYMBOL(pm_om_fwrite_trigger);

