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

#ifndef __SOC_INTERRUPTS_M3_H__
#define __SOC_INTERRUPTS_M3_H__

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************
                  * interrupts level m3 only *
***************************************************************************/
/* todo */
#define  M3_IPCM_INT0_2                 6  /* IPCM给M3的核间通信，对应IPCM中断0[2] */
#define  M3_IPCM_INT1_2                 7  /* IPCM给M3的核间通信，对应IPCM中断1[2] */
#define  M3_IPC_M2C_INT0                8  /* M3 唤醒MODEM */
#define  M3_IPC_M2C_INT1                9  /* M3 唤醒MODEM */

#define  M3_WDT_INT                     21  /* WatchDog模块输出中断 */


#define  M3_UART2_INT                   62  /* 串口2中断 */

#define  M3_SOCP_INT0                   188 /* SOCP Core0中断*/
#define  M3_SOCP_INT1                   189 /* SOCP Core1中断 */
#define M3_TIMER00_INT                20 
#define M3_TIMER01_INT                21 
#define M3_TIMER10_INT                22
#define M3_TIMER11_INT                23
#define M3_TIMER20_INT                24
#define M3_TIMER21_INT                25
#define M3_TIMER30_INT                26
#define M3_TIMER31_INT                27
#define M3_TIMER40_INT                28 
#define M3_TIMER41_INT                29 
#define M3_TIMER50_INT                30
#define M3_TIMER51_INT                31
#define M3_TIMER60_INT                32
#define M3_TIMER61_INT                33
#define M3_TIMER70_INT                34
#define M3_TIMER71_INT                35

#define M3_LTE_ARM_WAKEUP_INT         191
#define M3_TDS_DRX_ARM_WAKEUP_INT     192
#define M3_G1_INT_BBP_TO_CPU_32K      195
#define M3_G2_INT_BBP_TO_CPU_32K      198
#define M3_W_ARM_INT_02               200
#define M3_IPF_INT0                   204
#define M3_IPF_INT1                   205

/* for setting wake_src in acore/ccore */
#define M3_DRX_TIMER_INT M3_TIMER30_INT

#ifdef __cplusplus
}
#endif

#endif /* __SOC_INTERRUPTS_M3_H__ */

