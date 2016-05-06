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

#ifndef __BSP_SMARTSTAR_H__
#define __BSP_SMARTSTAR_H__
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* 函 数 名  : hi6551_reg_write
* 功能描述  :写smartstar的寄存器
* 输入参数  :addr:寄存器地址，value：写入的值
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
void hi6551_reg_write( u32 addr, u8 value);
/*****************************************************************************
* 函 数 名  : hi6551_reg_read
* 功能描述  :读smartstar的寄存器
* 输入参数  :addr:寄存器地址
* 输出参数  :pValue：读出的值
* 返回值：   无
*
*****************************************************************************/
void hi6551_reg_read( u32 addr, u8 *pValue);
/*****************************************************************************
* 函 数 名  : hi6551_reg_write_mask
* 功能描述  :操作smartstar的寄存器中的某几位
* 输入参数  :addr:寄存器地址，value：写入的值,mask：要操作的bit
* 输出参数  :无
* 返回值：   无
*
*****************************************************************************/
void hi6551_reg_write_mask(u32 addr, u8 value, u8 mask);
/*****************************************************************************
* 函 数 名  : hi6551_reg_read_test
* 功能描述  :读smartstar的寄存器测试接口,输入要读的寄存器地址，返回读出的数据。
* 输入参数  :addr:寄存器地址
* 输出参数  :无
* 返回值：   读出的寄存器值
*
*****************************************************************************/
int  hi6551_reg_read_test(u32 addr);
#ifdef __cplusplus
}
#endif

#endif