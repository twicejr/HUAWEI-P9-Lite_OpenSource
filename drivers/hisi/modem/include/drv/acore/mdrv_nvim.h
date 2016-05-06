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

#ifndef __MDRV_ACORE_NVIM_H__
#define __MDRV_ACORE_NVIM_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_nvim_comm.h"

enum NV_FACTORY_CHECK_E
{
    NV_FACTORY_CHECK_M1_GU = 0,     /*GU主卡*/
    NV_FACTORY_CHECK_M1_TL,         /*TL主卡*/
    NV_FACTORY_CHECK_M2_GU,         /*GU副卡*/
    NV_FACTORY_CHECK_BUTT
};

/*****************************************************************************
* 函 数 名  : mdrv_nv_check_factorynv
*
* 功能描述  : 对校准NV进行CRC校验
*
* 输入参数  : u32 mode
*
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Fuxin create
*
*****************************************************************************/
unsigned int mdrv_nv_check_factorynv(unsigned int mode);



/*****************************************************************************
* 函 数 名	: mdrv_nv_get_nvid_num
*
* 功能描述	: 获取NV项数量
*
* 输入参数	:
* 输出参数	: 无
*
* 返 回 值	: OK
*
* 修改记录	: Yangzhi create
*
***************************************************************************/
unsigned int mdrv_nv_get_nvid_num(void);

/*****************************************************************************
* 函 数 名  : mdrv_nv_get_nvid_list
*
* 功能描述  : 获取NV列表
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_get_nvid_list(NV_LIST_INFO_STRU *pstNvIdList);

/*****************************************************************************
* 函 数 名  : mdrv_nv_backup
*
* 功能描述  :  备份NV数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_backup(void);

/*****************************************************************************
* 函 数 名  : mdrv_nv_restore
*
* 功能描述  :  恢复生产NV项
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_restore(void);

/*备份出厂NV项*/
unsigned int mdrv_nv_backup_factorynv(void);

/*恢复出厂NV项*/
unsigned int mdrv_nv_revert_factorynv(void);


#define NV_GetNVIdListNum()		                    mdrv_nv_get_nvid_num()
#define NV_GetNVIdList(list)		                mdrv_nv_get_nvid_list(list)
#define NVM_BackUpFNV()                             mdrv_nv_backup_factorynv()
#define NVM_RevertFNV()                             mdrv_nv_revert_factorynv()
#define NVM_UpgradeBackup(uloption)	                mdrv_nv_backup()
#define NVM_UpgradeRestore()	                    mdrv_nv_restore()




#ifdef __cplusplus
}
#endif
#endif
