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

/*lint --e{537} */
#include <linux/kernel.h>
#include "bsp_sram.h"
#include "mdrv_sysboot.h"
#include "power_com.h"
#include "power_exchange.h"
#include "bsp_nandc.h"
#include "bsp_onoff.h"

#define SRAM_REBOOT_ADDR  (unsigned int)(((SRAM_SMALL_SECTIONS*)(SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_REBOOT_INFO)

/*****************************************************************************
 函 数 名  : clear_misc_message
 功能描述  : clear boot message in normal mode,
           : clear misc when exit recovery mode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
int clear_misc_message(void)
{
	char* str_misc = "misc";
	int rt;

    rt = bsp_nand_erase(str_misc, 0);

    return rt;
}

/*****************************************************************************
 函 数 名  : power_on_wdt_cnt_set
 功能描述  : 清除狗复位计数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
void power_on_wdt_cnt_set( void )
{
    power_info_s * power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    power_info->wdg_rst_cnt = 0;
}

/*****************************************************************************
 函 数 名  : power_on_wdt_cnt_get
 功能描述  : 获取狗复位计数值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
unsigned int power_on_wdt_cnt_get( void )
{
    power_info_s * power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    return power_info->wdg_rst_cnt;
}

/*****************************************************************************
 函 数 名  : power_on_reboot_flag_set
 功能描述  : 设置重启标志
 输入参数  : power_off_reboot_flag 重启原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
void power_on_reboot_flag_set( power_off_reboot_flag enFlag )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    power_info->last_shut_reason = (unsigned int)(enFlag);

    pr_dbg(KERN_DEBUG "#########  power_on_reboot_flag_set = 0x%08X ######## \r\n", (unsigned int)enFlag);
}

/*****************************************************************************
 函 数 名  : power_on_reboot_flag_get
 功能描述  : 获取重启原因
 输入参数  : 无
 输出参数  : 无
 返 回 值  : power_off_reboot_flag 重启原因
 调用函数  :
 被调函数  :
*****************************************************************************/
power_off_reboot_flag power_on_reboot_flag_get( void )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    pr_dbg(KERN_DEBUG "#########  power_on_reboot_flag_get = 0x%08X ######## \r\n", power_info->last_shut_reason );
    return (power_off_reboot_flag)power_info->last_shut_reason;
}

/*****************************************************************************
 函 数 名  : power_on_start_reason_set
 功能描述  : 设置开机原因
 输入参数  : power_on_start_reason 开机原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
void power_on_start_reason_set( power_on_start_reason enReason )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    power_info->power_on_reason = (unsigned int)(enReason);

    pr_dbg(KERN_DEBUG "#########  power_on_start_reason_set = 0x%08X ######## \r\n", enReason );
}

/*****************************************************************************
 函 数 名  : power_on_start_reason_get
 功能描述  : 获取开机原因
 输入参数  : 无
 输出参数  : 无
 返 回 值  : power_on_start_reason 开机原因
 调用函数  :
 被调函数  :
*****************************************************************************/
power_on_start_reason power_on_start_reason_get( void )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    pr_dbg(KERN_DEBUG "#########  power_on_start_reason_get = 0x%08X ######## \r\n", power_info->power_on_reason );
    return (power_on_start_reason)(power_info->power_on_reason);
}

/*****************************************************************************
 函 数 名  : power_on_start_reason_set
 功能描述  : 设置开机原因
 输入参数  : power_on_start_reason 开机原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
void power_reboot_cmd_set( power_reboot_cmd cmd )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    power_info->reboot_cmd = (unsigned int)(cmd);

    pr_dbg(KERN_DEBUG "#########  power_reboot_cmd_set = 0x%08X ######## \r\n", cmd );
}

/*****************************************************************************
 函 数 名  : power_on_c_status_get
 功能描述  : 获取C核状态
 输入参数  : power_on_c_status_get 开机原因
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
c_power_st_e power_on_c_status_get(void)
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    pr_dbg(KERN_DEBUG "#########  power_on_c_status_get = 0x%08X ######## \r\n", power_info->c_power_state );

    return (c_power_st_e)(power_info->c_power_state);

}

/*****************************************************************************
 函 数 名  : print_exchange_addr
 功能描述  : 打印sram区数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
void print_exchange_addr( void )
{
    unsigned int * ulPtr = (unsigned int *)(SRAM_REBOOT_ADDR);

    pr_dbg(KERN_DEBUG "############ (Linux) Addr = 0x%08X \r\n    0x00 = 0x%08X, 0x04 = 0x%08X, 0x08 = 0x%08X, 0x0C = 0x%08X\r\n",
         SRAM_REBOOT_ADDR, *(ulPtr+0), *(ulPtr+1), *(ulPtr+2), *(ulPtr+3));
}

