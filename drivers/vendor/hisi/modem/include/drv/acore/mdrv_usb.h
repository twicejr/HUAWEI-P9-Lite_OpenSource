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

#ifndef _MDRV_USB_H_
#define _MDRV_USB_H_

#ifdef _cplusplus
extern "C"
{
#endif

#ifdef __KERNEL__
#include <linux/notifier.h>
#endif

/* IOCTL CMD 定义 */
#define ACM_IOCTL_SET_WRITE_CB      0x7F001000
#define ACM_IOCTL_SET_READ_CB       0x7F001001
#define ACM_IOCTL_SET_EVT_CB        0x7F001002
#define ACM_IOCTL_SET_FREE_CB       0x7F001003

#define ACM_IOCTL_WRITE_ASYNC       0x7F001010
#define ACM_IOCTL_GET_RD_BUFF       0x7F001011
#define ACM_IOCTL_RETURN_BUFF       0x7F001012
#define ACM_IOCTL_RELLOC_READ_BUFF  0x7F001013
#define ACM_IOCTL_SEND_BUFF_CAN_DMA 0x7F001014

#define ACM_IOCTL_IS_IMPORT_DONE    0x7F001020
#define ACM_IOCTL_WRITE_DO_COPY     0x7F001021

#define ACM_MODEM_IOCTL_SET_MSC_READ_CB 0x7F001030
#define ACM_MODEM_IOCTL_MSC_WRITE_CMD   0x7F001031
#define ACM_MODEM_IOCTL_SET_REL_IND_CB  0x7F001032

/* 异步数据收发结构 */
typedef struct tagACM_WR_ASYNC_INFO
{
    char *pVirAddr;
    char *pPhyAddr;
    unsigned int u32Size;
    void* pDrvPriv;
}ACM_WR_ASYNC_INFO;

/* ACM设备事件类型 */
typedef enum tagACM_EVT_E
{
    ACM_EVT_DEV_SUSPEND = 0,        /* 设备不可以进行读写(主要用于事件回调函数的状态) */
    ACM_EVT_DEV_READY = 1,          /* 设备可以进行读写(主要用于事件回调函数的状态) */
    ACM_EVT_DEV_BOTTOM
}ACM_EVT_E;

typedef enum tagACM_IOCTL_FLOW_CONTROL_E
{
    ACM_IOCTL_FLOW_CONTROL_DISABLE = 0,      /* resume receiving data from ACM port */
    ACM_IOCTL_FLOW_CONTROL_ENABLE      /* stop receiving data from ACM port */
}ACM_IOCTL_FLOW_CONTROL_E;

/* 读buffer信息 */
typedef struct tagACM_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}ACM_READ_BUFF_INFO;


typedef void (*ACM_WRITE_DONE_CB_T)(char *pVirAddr, char *pPhyAddr, int size);
typedef void (*ACM_READ_DONE_CB_T)(void);
typedef void (*ACM_EVENT_CB_T)(ACM_EVT_E evt);
typedef void (*ACM_FREE_CB_T)(char* buf);
typedef void (*ACM_MODEM_REL_IND_CB_T)(unsigned int bEnable);

typedef void (*USB_UDI_ENABLE_CB_T)(void);
typedef void (*USB_UDI_DISABLE_CB_T)(void);


/*****************************************************************************
 *  函 数 名  : mdrv_usb_reg_enablecb
 *  功能描述  : 协议栈注册USB使能通知回调函数
 *  输入参数  : pFunc: USB使能回调函数指针
 *
 *  输出参数  : 无
 *  返 回 值  :  0	       操作成功。
 *                           其他	操作失败。
 *
 ******************************************************************************/
unsigned int mdrv_usb_reg_enablecb(USB_UDI_ENABLE_CB_T pFunc);

/*****************************************************************************
 *  函 数 名  : mdrv_usb_reg_disablecb
 *  功能描述  : 协议栈注册USB去使能通知回调函数
 *  输入参数  : pFunc: USB去使能回调函数指针
 *
 *  输出参数  : 无
 *  返 回 值  :  0	       操作成功。
 *                           其他	操作失败。
 *
 ******************************************************************************/
unsigned int mdrv_usb_reg_disablecb(USB_UDI_DISABLE_CB_T pFunc);


#ifdef _cplusplus
}
#endif
#endif

