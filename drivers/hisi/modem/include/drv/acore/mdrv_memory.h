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


#ifndef __MDRV_ACORE_MEMORY_H__
#define __MDRV_ACORE_MEMORY_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_memory_common.h>

typedef enum tagMEM_MODE_TYPE
{
    MEM_DDR_MODE = 0,
    MEM_IPF_MODE,
    MEM_TTF_MODE,
    MEM_AXI_MODE,
    MEM_MODE_MAX
}MEM_MODE_TYPE_E;

typedef enum tagBSP_DDR_SECT_TYPE_E
{
    BSP_DDR_SECT_TYPE_TTF = 0x0,
    BSP_DDR_SECT_TYPE_ARMDSP,
    BSP_DDR_SECT_TYPE_UPA,
    BSP_DDR_SECT_TYPE_CQI,
    BSP_DDR_SECT_TYPE_APT,
    BSP_DDR_SECT_TYPE_ET,
    BSP_DDR_SECT_TYPE_BBPMASTER,
    BSP_DDR_SECT_TYPE_NV,
    BSP_DDR_SECT_TYPE_DICC,
    BSP_DDR_SECT_TYPE_WAN,
    BSP_DDR_SECT_TYPE_SHARE_MEM,
    BSP_DDR_SECT_TYPE_EXCP,
    BSP_DDR_SECT_TYPE_HIFI,
    BSP_DDR_SECT_TYPE_HARQ,
    BSP_DDR_SECT_TYPE_ZSP_UP,
    BSP_DDR_SECT_TYPE_HUTAF,
    BSP_DDR_SECT_TYPE_BBPSAMPLE,
    BSP_DDR_SECT_TYPE_TDS_LH2,
    BSP_DDR_SECT_TYPE_SOCP,
    BSP_DDR_SECT_TYPE_ECS_TEE,

    BSP_DDR_SECT_TYPE_BUTTOM
}BSP_DDR_SECT_TYPE_E;

typedef enum tagBSP_DDR_SECT_ATTR_E
{
    BSP_DDR_SECT_ATTR_CACHEABLE = 0x0,
    BSP_DDR_SECT_ATTR_NONCACHEABLE,
    BSP_DDR_SECT_ATTR_BUTTOM
}BSP_DDR_SECT_ATTR_E;

typedef enum tagBSP_DDR_SECT_PVADDR_E
{
    BSP_DDR_SECT_PVADDR_EQU = 0x0,
    BSP_DDR_SECT_PVADDR_NOT_EQU,
    BSP_DDR_SECT_PVADDR_BUTTOM
}BSP_DDR_SECT_PVADDR_E;


typedef struct tagBSP_DDR_SECT_QUERY_S
{
    BSP_DDR_SECT_TYPE_E     enSectType;
    BSP_DDR_SECT_ATTR_E     enSectAttr;
    BSP_DDR_SECT_PVADDR_E   enPVAddr;
    unsigned int                 ulSectSize;
}BSP_DDR_SECT_QUERY_S;

typedef struct tagBSP_DDR_SECT_INFO_S
{
    BSP_DDR_SECT_TYPE_E    enSectType;
    BSP_DDR_SECT_ATTR_E    enSectAttr;
    void *                 pSectVirtAddr;
    void *                 pSectPhysAddr;
    unsigned int           ulSectSize;
}BSP_DDR_SECT_INFO_S;

/*****************************************************************************
* 函 数 名  : mdrv_get_fix_ddr_addr
*
* 功能描述  :DDR内存段查询接口。
*
* 输入参数  : pstSectQuery: 需要查询内存段的属性，类型
*             pstSectInfo:  查询到的内存段信息
*
* 输出参数  : 无
* 返 回 值  :  无
****************************************************************************/
int mdrv_get_fix_ddr_addr (BSP_DDR_SECT_QUERY_S *pstSectQuery, BSP_DDR_SECT_INFO_S *pstSectInfo);

/*****************************************************************************
* 函 数 名  : mdrv_virt_to_phy
*
* 功能描述  :虚地址转换成物理地址
*
* 输入参数  : lPAddr: 需要转化为物理地址的虚拟地址的地址值
*             mode:   模块属性
* 输出参数  : 无
* 返 回 值  : 物理地址值
****************************************************************************/
void*  mdrv_virt_to_phy (MEM_MODE_TYPE_E mode, void* lPAddr);

/*****************************************************************************
* 函 数 名  : mdrv_phy_to_virt
*
* 功能描述  :物理地址转换成虚拟地址
*
* 输入参数  : pMem: 需要进行转换的地址
*             mode: 模块属性
*
* 输出参数  : 无
* 返 回 值  : 虚拟地址值
****************************************************************************/
void*  mdrv_phy_to_virt (MEM_MODE_TYPE_E mode, void* pMem);

/*****************************************************************************
* 函 数 名  : mdrv_memcpy
*
* 功能描述  : 数据拷贝接口，底层基于汇编实现的最优化接口，只能用于memory到
*             memory的拷贝
* 约束条件  :
*             只能用于memory 到memory的拷贝，不能用于memory到寄存器的拷贝
*             需要4字节对齐
*             在A核 ARMv8 架构中，需要8字节对齐或者是normal memory 属性，
*             采用ioremap_wc映射的 uncachable 的内存 或者cachable的内存
*
* 输入参数  : dest :  拷贝的目的地址
*             src  :  拷贝的源地址
*             count:  拷贝数据的大小
* 输出参数  : 无
* 返 回 值  :  无
****************************************************************************/
void *mdrv_memcpy(void * dest, const void * src, unsigned long count);

#ifdef __cplusplus
}
#endif
#endif
