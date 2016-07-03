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

#ifndef _MDRV_ERRNO_H_
#define _MDRV_ERRNO_H_

#ifdef _cplusplus
extern "C"
{
#endif

/* 底软调用system_error，module id划分 */
typedef enum _mdrv_errno_e
{
    DRV_ERRNO_DUMP_ARM_EXC      = 0x1000,   /* arm异常 */
    DRV_ERRNO_DUMP_WDT          = 0x1001,   /* watch dog异常 */
    DRV_ERRNO_ICC_RING_BUFFER   = 0x1010,   /* icc循环buffer错误 */
    DRV_ERRNO_PMU_OVER_CUR      = 0x1020,   /* pmu过流 */
    DRV_ERRNO_PMU_OVER_TEMP     = 0x1021,   /* pmu过温 */
    DRV_ERRNO_PMU_UNDEF_VOL     = 0x1022,   /* pmu欠压 */
    DRV_ERRNO_NV_ICC_FIFO_FULL  = 0x1030,   /* nv icc通道满 */
    DRV_ERRNO_AMON_SOC_WR       = 0x1040,   /* amon soc写操作异常 */
    DRV_ERRNO_AMON_SOC_RD       = 0x1041,   /* amon soc读操作异常 */
    DRV_ERRNO_AMON_CPUFAST_WR   = 0x1042,   /* amon fast写操作异常 */
    DRV_ERRNO_AMON_CPUFAST_RD   = 0x1043,   /* amon fast读操作异常 */
    DRV_ERRNO_MBX_WR_FULL       = 0x1050,   /* 下行邮箱满 */
    DRV_ERRNO_MBX_DSP_IPC       = 0x1051,   /* 上行邮箱满，DSP IPC通知ARM */
    DRV_ERRNO_MBX_PS_TIMEOUT    = 0x1052,   /* PS等DSP消息超时 */
    DRV_ERRNO_MBX_UP_WR         = 0x1053,   /* 上行邮箱写指针异常 */
    DRV_ERRNO_MBX_DL_MOD        = 0x1054,   /* 下行邮箱读指针MOD异常 */
    DRV_ERRNO_RESET_SIM_SWITCH  = 0x1060,   /* 切卡引起的modem单独复位 */
    DRV_ERRNO_RESET_RILD        = 0x1061,   /* RILD引起的modem单独复位 */
    DRV_ERRNO_RESET_3RD_MODEM   = 0x1062,   /* 3rd modem引起的发起的单独复位 */
    DRV_ERRNO_RESET_REBOOT_REQ  = 0x1063,   /* modem单独复位为桩时，整机复位 */
    DRV_ERRNO_WATCHPOINT        = 0x1070,   /* watchpoint触发复位 */
    DRV_ERRNO_PDLOCK            = 0x1071,   /* pdlock触发复位*/
    DRV_ERRNO_XMBX_WR_FULL      = 0x1072,   /* CPHY 下行邮箱满 */
    DRV_ERRNO_XMBX_DSP_IPC      = 0x1073,   /* CPHY 上行邮箱满，DSP IPC通知ARM */
    DRV_ERRNO_XMBX_PS_TIMEOUT   = 0x1074,   /* CPHY PS等DSP消息超时 */
    DRV_ERRNO_XMBX_UP_WR        = 0x1075,   /* CPHY 上行邮箱写指针异常 */
    DRV_ERRNO_XMBX_DL_MOD       = 0x1076,   /* CPHY 下行邮箱读指针MOD异常 */
    DRV_ERROR_LCD_VCC           = 0x1077,    /* PMU过流电源关闭，vcc丢失 */
    DRV_ERROR_USER_RESET        = 0x1078,    /* 用户发起的复位*/
    DRV_ERRNO_PAN_RPC           = 0x1080,   /* PAN_RPC 初始化失败复位 */
    DRV_ERRNO_NV_CRC_ERR        = 0x1081,   /* 读取NV文件错误 */
    DRV_ERRNO_IPF_OUT_REG		= 0x1082,	/* ipf 数传越界*/
    DRV_ERRNO_PSAM_OUT_REG		= 0x1083,	/* PSAM 数传越界*/
    DRV_ERRNO_NV_LIST_FULL      = 0x1084,   /* NV 本地写NV list满  */
    DRV_ERRNO_CLK_EXCEPT        = 0x1085,   /* PLL停止异常 & PLL变慢异常*/
	DRV_ERRNO_MODEM_RST_FAIL    = 0x1086,   /*Modem 单独复位中,回调DRV失败*/
    DRV_ERRNO_BBP_IPC_TIMEOUT   = 0x1087,   /* BBP获取核间锁超时 */
    DRV_ERRNO_BBP_DMA_TIMEOUT   = 0x1088,   /* BBP获取核间锁超时 */
    DRV_ERRNO_BUTT              = 0x1FFF
}mdrv_errno_enum;

#ifdef _cplusplus
}
#endif
#endif


