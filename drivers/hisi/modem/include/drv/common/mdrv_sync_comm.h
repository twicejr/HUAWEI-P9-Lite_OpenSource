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

#ifndef __MDRV_SYNC_COMM_H__
#define __MDRV_SYNC_COMM_H__
#ifdef __cplusplus
extern "C"
{
#endif

/*宏定义*/
#define BSP_ERR_SYNC_BASE                (BSP_S32)(0x80000000 | (BSP_DEF_ERR(BSP_MODU_SYNC, 0)))
#define BSP_ERR_SYNC_TIMEOUT             (BSP_ERR_SYNC_BASE + 0x0)

typedef enum tagSYNC_MODULE_E
{
    SYNC_MODULE_MEM     = 0,
    SYNC_MODULE_NANDC,
    SYNC_MODULE_PMU,
    SYNC_MODULE_SOCP,
    SYNC_MODULE_DMA,
    SYNC_MODULE_IPF,
    SYNC_MODULE_NV,
    SYNC_MODULE_YAFFS,
    SYNC_MODULE_MSP,
    SYNC_MODULE_GPIO,
    SYNC_MODULE_CSHELL,
    SYNC_MODULE_MNTN,
	SYNC_MODULE_MSPNV,
	SYNC_MODULE_ONLINE,
	SYNC_MODULE_CHG,
	SYNC_MODULE_TFUPDATE,
	SYNC_MODULE_RESET,
	SYNC_MODULE_TEST,
    SYNC_MODULE_BUTT,
}SYNC_MODULE_E;



/*****************************************************************************
* 函 数 名  : mdrv_sync_lock
*
* 功能描述  : 锁定并查询模块的初始化状态
*
* 输入参数  : SYNC_MODULE_E u32Module 模块ID
*             unsigned int *pState         模块的初始化状态
*             unsigned int u32TimeOut      超时值，0为永远等待
* 输出参数  :
*
* 返 回 值  : 0，成功；-1，参数错误；其他值，等待超时
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_sync_lock(SYNC_MODULE_E u32Module, unsigned int *pState, unsigned int u32TimeOut);

/*****************************************************************************
* 函 数 名  : mdrv_sync_unlock
*
* 功能描述  : 解锁并更新模块初始化状态
*
* 输入参数  : SYNC_MODULE_E u32Module  模块ID
*             unsigned int u32State         更新模块初始化状态
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_sync_unlock(SYNC_MODULE_E u32Module, unsigned int u32State);

/*****************************************************************************
* 函 数 名  : mdrv_sync_wait
*
* 功能描述  : 从核等待主核操作完成函数
*
* 输入参数  : SYNC_MODULE_E u32Module  模块ID
*             unsigned int u32TimeOut       超时值，0为永远等待
* 输出参数  :
*
* 返 回 值  : 0，成功；-1，参数错误；其他值，等待超时
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_sync_wait(SYNC_MODULE_E u32Module, unsigned int u32TimeOut);

/*****************************************************************************
* 函 数 名  : mdrv_sync_give
*
* 功能描述  : 主核通知从核操作已经完成
*
* 输入参数  : SYNC_MODULE_E u32Module 模块ID
* 输出参数  :
*
* 返 回 值  : 0，成功；其他，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_sync_give(SYNC_MODULE_E u32Module);

#ifdef __cplusplus
}
#endif
#endif
