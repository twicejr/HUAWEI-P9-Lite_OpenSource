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

#ifndef BSP_IOS_H
#define BSP_IOS_H

#include <bsp_om.h>
#include <bsp_shared_ddr.h>

#define  SHARED_IOS_ADDR ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_IOS)

#define IOS_OK      (0)
#define IOS_ERROR   (-1)
#define IOS_FALSE   (0)
#define IOS_TRUE    (1)

#define ios_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_IOS, "[ios]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define ios_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_IOS, "[ios]: "fmt, ##__VA_ARGS__))

#define VIRT_TO_PHY_ADREE(reg) reg
#define PHY_TO_VIRT_ADREE(reg) reg

/*申请SHARE-MEMORY内存,用来存放fastboot管脚配置的寄存器信息*/
#define IOS_POOL_ADDR	((SHM_BASE_ADDR + SHM_OFFSET_IOS) + sizeof(IOS_POOL_CTRL))
#define IOS_POOL_SIZE   ((SHM_SIZE_IOS - sizeof(IOS_POOL_CTRL)) / sizeof(IOS_REG_DATA) * sizeof(IOS_REG_DATA))

typedef struct
{
    unsigned int           addr;         /*register address*/
    unsigned int           value;        /*register value*/
}IOS_REG_DATA;

typedef struct
{
   IOS_REG_DATA*           start;      /*start address of ios data array*/
   IOS_REG_DATA*           cur;        /*current postion of ios data array*/
   IOS_REG_DATA*           end;        /*last address of ios data array*/
}IOS_POOL_CTRL;


/**************    mcore对外接口**************/
int ios_config_resume(void);

/**************    ccore对外接口**************/
void ios_list_echo(void);
void ios_addr_show(void);
void ios_init(void);

#endif
