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

#ifndef    _BSP_UDI_DRV_H_
#define    _BSP_UDI_DRV_H_

#include <mdrv_udi.h>
#include <bsp_udi.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define bsp_assert(expr)                                            \
	if (!(expr)) {                                          \
		printk("Assertion failed! %s,%s,%s,line=%d\n",  \
		#expr, __FILE__, __func__, __LINE__);    \
	}

#define UDI_GET_MAIN_DEV_ID(id)	(((id) & 0xff00) >> 8 )
#define UDI_GET_DEV_TYPE(id)		(((id) & 0x00ff))
#define UDI_UNUSED_PARAM(param) //(param=param)

UDI_HANDLE BSP_UDI_ICC_ChnToHandle(unsigned int u32Chn);
UDI_HANDLE BSP_UDI_NCM_DataChnToHandle(unsigned int u32Chn);

int BSP_UDI_SetPrivate(UDI_DEVICE_ID_E devId, void* pPrivate);
int BSP_UDI_GetPrivate(UDI_HANDLE handle);
int BSP_UDI_SetCapability(UDI_DEVICE_ID_E devId, unsigned int u32Capability);
int BSP_UDI_SetInterfaceTable(UDI_DEVICE_ID_E devId, UDI_DRV_INTEFACE_TABLE *pDrvInterface);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BSP_UDI_DRV_H_ */


