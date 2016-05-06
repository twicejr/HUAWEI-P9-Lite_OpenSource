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

#ifndef __MDRV_ACORE_IPF_H__
#define __MDRV_ACORE_IPF_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_ipf_comm.h"


typedef int (*BSP_IPF_WakeupDlCb)(void);
typedef int (*BSP_IPF_AdqEmptyDlCb)(IPF_ADQ_EMPTY_E eAdqEmpty);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_config_ulbd
*
* 功能描述  : 配置上行数据
*
* 输入参数  : unsigned int u32Num     需要配置的BD数目
*             IPF_CONFIG_ULPARAM_S* pstUlPara 配置参数结构体数组指针
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_ERROR 配置失败
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_config_ulbd(unsigned int u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_ulbd_num
*
* 功能描述  : 获取上行BDQ中空闲的BD数
*
* 输入参数  :
* 输出参数  :
*
* 返 回 值  : 空闲的BD数目，范围为0~BD_DESC_SIZE
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_ulbd_num(void);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_uldesc_num
*
* 功能描述  : 获取上行可以配置的包数
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  : 不会造成队头堵塞的可上传的包数
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_uldesc_num(void);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_ulrd_num
*
* 功能描述  : 获取上行RD数目
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  : 上行Rd数目
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_ulrd_num (void);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_dlrd
*
* 功能描述  : 获取下行RD
*
* 输入参数  : unsigned int* pu32Num  可以返回的最多的RD数目
*             IPF_RD_DESC_S *pstRd  RD描述符结构体首地址
* 输出参数  :
*
* 返 回 值  : 实际返回的RD数目
*
* 其它说明  :
*
*****************************************************************************/
void mdrv_ipf_get_dlrd (unsigned int  * pu32Num, IPF_RD_DESC_S *pstRd);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_dlrd_num
*
* 功能描述  : 获取下行RD数目
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  : 下行Rd数目
*
* 其它说明  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_dlrd_num (void);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_config_dlad
*
* 功能描述  : 给空闲的AD分配新的内存缓冲区
*
* 输入参数  : IPF_AD_TYPE_E eAdType   AD队列号，0（短包队列）或1（长包对列）
*             unsigned int u32AdNum    需要配置的的AD数目
*             IPF_AD_DESC_S *pstAdDesc 缓存空间对应的数据结构首地址
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_config_dlad(IPF_AD_TYPE_E eAdType, unsigned int u32AdNum, IPF_AD_DESC_S * pstAdDesc);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_dlad_num
*
* 功能描述  : 获取下行（A核）空闲（指向的缓冲区已经被使用）AD数目
*
* 输入参数  : unsigned int* pu32AD0Num  返回空闲的AD0的数目
*             unsigned int* pu32AD1Num  返回空闲的AD1的数目
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS 配置成功
*             IPF_INVALID_PARA 输入参数无效
* 其它说明  :
*
*****************************************************************************/
int mdrv_ipf_get_dlad_num (unsigned int* pu32AD0Num, unsigned int* pu32AD1Num);


/*****************************************************************************
* 函 数 名  : mdrv_ipf_reinit_dlreg
*
* 功能描述  : CCore单独复位恢复时，配置IPF寄存器
*
* 输入参数  : void
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
void mdrv_ipf_reinit_dlreg(void);

/*****************************************************************************
* 函 数 名  : mdrv_ipf_get_used_dlad
*
* 功能描述  : 获取未被使用的下行AD以便ADS释放
*
* 输入参数  : IPF_AD_TYPE_E eAdType  AD类型：0（短包队列）或1（长包对列）
*             unsigned int * pu32AdNum    AD数目
*             IPF_AD_DESC_S * pstAdDesc 需要释放的AD数组首地址
* 输出参数  :
*
* 返 回 值  : IPF_SUCCESS：正常返回
*             IPF_ERROR：失败返回，等待超时IPF通道始终BUSY
*             IPF_INVALID_PARA：入参出错
* 其它说明  : ADS在ccore单独复位流程中需要调用该函数并释放返回的AD，否则会造成内存泄露
*
*****************************************************************************/
int mdrv_ipf_get_used_dlad(IPF_AD_TYPE_E eAdType, unsigned int * pu32AdNum, IPF_AD_DESC_S * pstAdDesc);

#ifdef __cplusplus
}
#endif

#endif
