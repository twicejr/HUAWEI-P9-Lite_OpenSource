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

#ifndef _LOAD_IMAGE_H_
#define _LOAD_IMAGE_H_

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include <bsp_ipc.h>

#ifdef CONFIG_TZDRIVER
#include <teek_client_api.h>
#include <teek_client_id.h>
#else
enum SVC_SECBOOT_IMG_TYPE {
    MODEM,
    HIFI,
    DSP,
    XDSP,
	TAS,
	WAS,
	CAS,
    MODEM_DTB,
    SOC_MAX
};
#endif

#define sec_print_err(fmt, ...)   (printk(KERN_ERR "[sec]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define sec_print_info(fmt, ...)   (printk(KERN_INFO "[sec]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#define SEC_OK      			(0)
#define SEC_ERROR  				(-1)

/* 加载所有modem镜像，初始化和modem单独复位时使用 */
int bsp_load_modem_images(void);

/* 供动态加载协议栈镜像使用 */
int bsp_load_modem_single_image(enum SVC_SECBOOT_IMG_TYPE ecoretype, u32 run_addr, u32 ddr_size);

/*****************************************************************************
 函 数 名  : bsp_load_notify_ccpu_start
 功能描述  : 通知lpm3 C核启动
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回OK,失败返回ERROR
 调用函数  :
 被调函数  :
*****************************************************************************/
static inline int bsp_load_notify_ccpu_start(void)
{
    return bsp_ipc_int_send(IPC_CORE_MCORE, IPC_MCU_INT_SRC_CCPU_START);
}

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif /* _SECURE_IMAGE_H_ */

