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

#ifndef __MDRV_UDI_COMMON_H__
#define __MDRV_UDI_COMMON_H__

#include <mdrv_icc.h>


/*待徐成将icc替换成udi后删除*/
typedef enum tagICC_IOCTL_CMD_E{
    ICC_IOCTL_SET_WRITE_CB  = 0,
    ICC_IOCTL_SET_READ_CB,
    ICC_IOCTL_SET_EVENT_CB,
    ICC_IOCTL_GET_STATE,
    ICC_IOCTL_SET_BUTT
}ICC_IOCTL_CMD_E;

#define ACM_IOCTL_FLOW_CONTROL          0x7F001035

#define UDI_INVALID_HANDLE     (-1)

#define UDI_CAPA_BLOCK_READ    ((unsigned int)(1<<0)) /* 该设备的read接口为阻塞接口 */
#define UDI_CAPA_BLOCK_WRITE   ((unsigned int)(1<<1)) /* 该设备的write接口为阻塞接口 */
#define UDI_CAPA_READ_CB       ((unsigned int)(1<<2)) /* 该设备支持read 回调函数 */
#define UDI_CAPA_WRITE_CB      ((unsigned int)(1<<3)) /* 该设备支持write 回调函数 */
#define UDI_CAPA_BUFFER_LIST   ((unsigned int)(1<<4)) /* 该设备的读写buffer为内存链表结构(默认为普通内存块) */
#define UDI_CAPA_CTRL_OPT      ((unsigned int)(1<<5)) /* 该设备支持控制操作 */

#define MIN_UDI_HANDLE     0x5a0000
#define MAX_UDI_HANDLE     0x5a003f


/* 架构整改,下列宏定义将被删除，禁止新增代码使用下列宏 */
#define DRV_ICC_OPEN(u32ChanId, pChanAttr)  mdrv_icc_open(u32ChanId, pChanAttr)
#define DRV_ICC_READ(u32ChanId,pData,s32Size)  mdrv_icc_read(u32ChanId,pData,s32Size)
#define DRV_ICC_WRITE(u32ChanId,pData,s32Size)  mdrv_icc_write(u32ChanId,pData,s32Size)
/* 架构整改,上面宏定义将被删除，禁止新增代码使用上面宏 */


#endif
