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


#ifndef _MDRV_MISC_H_
#define _MDRV_MISC_H_

#ifdef _cplusplus
extern "C"
{
#endif

#ifdef __KERNEL__
#include <linux/notifier.h>
#endif

#include "mdrv_misc_comm.h"

/*A核SIM卡热插拔，上层taf使用*/
typedef enum
{
    SIM_CARD_OUT = 0,
    SIM_CARD_IN  = 1
} SCI_DETECT_STATE_E;

/*****************************************************************************
 *  函 数 名  : mdrv_misc_scbackup_ext_write
 *  功能描述  : 将锁网锁卡文件备份到Flash中对应的分区
 *  输入参数  :
 *              pRamAddr:    待写入的备份区地址
 *              len:         写入文件长度
 *
 *  输出参数  : 无
 *  返 回 值  :  0           操作成功。
 *               其他        操作失败。
 *
 ******************************************************************************/
int mdrv_misc_scbackup_ext_write(unsigned char *pRamAddr, unsigned int len);
/*****************************************************************************
 *  函 数 名  : mdrv_misc_scbackup_ext_read
 *  功能描述  : 将锁网锁卡从flash中写入到指定内存中
 *  输入参数  :
 *              pRamAddr:    待写入的备份区地址
 *              len:         写入文件长度
 *
 *  输出参数  : 无
 *  返 回 值  :  0           操作成功。
 *               其他        操作失败。
 ******************************************************************************/
int mdrv_misc_scbackup_ext_read(unsigned char *pRamAddr, unsigned int len);

#ifdef _cplusplus
}
#endif
#endif

