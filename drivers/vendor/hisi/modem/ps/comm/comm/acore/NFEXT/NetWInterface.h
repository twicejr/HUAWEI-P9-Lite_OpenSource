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

#ifndef _NETWINTERFACE_H_
#define _NETWINTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (VOS_OS_VER == VOS_WIN32) || defined (__PC_LINT__)
#include "linuxstub.h"
#else
#include <linux/types.h>
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*================================================*/
/* 数值宏定义 */
/*================================================*/
#define NW_INQUIRE_IFCONFIG_ON_MASK      (1)        /*查询Ifconfig掩码*/
#define NW_INQUIRE_ARP_ON_MASK           (1 << 1)   /*查询Arp掩码*/
#define NW_INQUIRE_ROUTE_ON_MASK         (1 << 2)   /*查询Route掩码*/
#define NW_INQUIRE_NETSTATE_ON_MASK      (1 << 3)   /*查询Netstate掩码*/
#define NW_INQUIRE_NAT_ON_MASK           (1 << 4)   /*查询Nat掩码*/

#define NW_INQUIRE_CFG_ALL_MASK          ( NW_INQUIRE_IFCONFIG_ON_MASK \
                                            | NW_INQUIRE_ARP_ON_MASK \
                                            | NW_INQUIRE_ROUTE_ON_MASK \
                                            | NW_INQUIRE_NETSTATE_ON_MASK \
                                            | NW_INQUIRE_NAT_ON_MASK)

#define DEVICE_NAME                      "NetfilterExtDev"     /*字符设备名*/
#define CLASS_NAME                       "NetfilterExtClass"
#define DEV_BUFF_LEN                     (sizeof(NETWORK_INQUIRE_CONFIG_STRU))
#define DEVICE_PATH_LEN                  (100)                 /*设备所在路径的长度*/
#define DEVICE_NUM                       (1)                   /*注册字符设备的数目*/
#define MINOR_NO_START                   (500)                 /*次设备的起始号*/


/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  4 结构定义
*****************************************************************************/
/*********************************************
 结构体名   :NETWORK_INQUIRE_CONFIG_STRU
 协议表格 :
 结构体说明 :network inquire配置信息
*********************************************/
typedef struct
{
    unsigned int ulOnOffMask;                  /* 功能开关掩码 */
    unsigned int ulTimerLen;                   /* 上报周期定时器长度 */
}NETWORK_INQUIRE_CONFIG_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

