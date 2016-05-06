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

#include <product_config.h>
#include <bsp_om.h>
#include <mdrv_sysboot.h>
#include <bsp_reset.h>

#ifndef CONFIG_BALONG_MODEM_RESET /* ´ò×®!CONFIG_BALONG_MODEM_RESET */

int mdrv_sysboot_register_reset_notify(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
    return 0;
}

s32 bsp_reset_ccpu_status_get(void)
{
	//bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
	return 1;
}

s32 bsp_reset_cb_func_register(const char *name, pdrv_reset_cbfun func, int user_data, int prior)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
	return 0;
}

void bsp_modem_power_off(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
	return;
}

void bsp_modem_power_on(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
	return;
}

int bsp_cp_reset(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
	return -1;
}

u32 bsp_reset_is_connect_ril(void)
{
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RESET, "[reset]: <%s> is stub\n", __FUNCTION__);
	return 0;
}


#else  /* ÊµÏÖ */

int mdrv_sysboot_register_reset_notify(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
    return bsp_reset_cb_func_register(pname, pcbfun, userdata, priolevel);
}

#endif /* end of CONFIG_BALONG_MODEM_RESET */

#ifndef CONFIG_HISI_HIFI_BB
int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
	return 0;
}
#endif /* end of undef CONFIG_HISI_HIFI_BB */

