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

#include <bsp_memmap.h>
#include <osl_bio.h>
#include <bsp_wdt.h>
#include <hi_wdt.h>
BSP_S32 BSP_WDT_Enable(BSP_U8 wdtId)
{
	return bsp_wdt_start();
}

BSP_S32 BSP_WDT_Disable(BSP_U8 wdtId)
{
	return bsp_wdt_stop();
}

int mdrv_wdt_feed(unsigned char wdtId)
{
	return bsp_wdt_keepalive();
}

#ifndef CONFIG_ACORE_WDT

wdt_timeout_cb g_wdt_rebootfunc = WDT_NULL;

s32 hi6930_wdt_init(void)
{
	wdt_pinfo("enter wdt init\n");
	return WDT_OK;
}
s32 bsp_wdt_start(void)
{
    return WDT_OK;
}

s32 bsp_wdt_stop(void)
{
	return WDT_OK;
}

s32 bsp_wdt_keepalive(void)
{
    return WDT_OK;
}

void bsp_wdt_reboot_direct(void)
{
	//hi_syssc_wdt_reboot();
}
void bsp_wdt_reboot(void)
{
	if (g_wdt_rebootfunc)
	{
		g_wdt_rebootfunc(ACORE_WDT_TIMEOUT);
	}
	bsp_wdt_reboot_direct();
}
s32 bsp_wdt_set_timeout(u32 timeout)/*s*/
{
	return WDT_OK;
}
 s32 bsp_wdt_get_timeleft(u32 *timeleft)/*s*/
{
	return WDT_OK;
}
 s32 bsp_wdt_register_hook(void *hook)
{
	return WDT_OK;
}

s32  bsp_wdt_unregister_hook(void)
{
	return WDT_OK;
}

 s32 bsp_wdt_suspend(u32 timeout)
 {
	return WDT_OK;
 }
 void bsp_wdt_resume(void)
 {
 }
 
s32 bsp_wdt_reboot_register_hook(void *hook)
{
    /*参数判断，如果函数指针为空返回错误*/
    if(WDT_NULL == hook)
    {
		 wdt_err("hook is NULL\n");
        return WDT_ERROR;
    }

    /*通过全局变量注册上层MSP处理函数*/
	g_wdt_rebootfunc = hook;
	
	return WDT_OK;
}

s32  bsp_wdt_reboot_unregister_hook(void)
{
	/*卸载上层超时处理函数*/
	g_wdt_rebootfunc = WDT_NULL;
	wdt_pinfo("wdt unregister_hook\n");
	return WDT_OK;
}

#endif

