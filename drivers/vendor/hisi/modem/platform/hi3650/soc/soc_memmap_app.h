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

#ifndef __SOC_MEMMAP_APP_H__
#define __SOC_MEMMAP_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "soc_memmap_comm.h"

/**********************begin:timer********************/
/*非掉电区*/
#define HI_TIMER_00_REGBASE_ADDR          0xfff00000   //对应k3 timer00
#define HI_TIMER_01_REGBASE_ADDR          0xfff00000   //对应k3 timer01
#define HI_TIMER_02_REGBASE_ADDR          0xfff01000   //对应k3 timer10
#define HI_TIMER_03_REGBASE_ADDR          0xfff01000   //对应k3 timer11
#define HI_TIMER_04_REGBASE_ADDR          0xfff02000   //对应k3 timer20
#define HI_TIMER_05_REGBASE_ADDR          0xfff02000   //对应k3 timer21
#define HI_TIMER_06_REGBASE_ADDR          0xfff03000   //对应k3 timer30
#define HI_TIMER_07_REGBASE_ADDR          0xfff03000   //对应k3 timer31

/*掉电区*/
#define HI_TIMER_08_REGBASE_ADDR          0xe8a00000   //对应k3 timer40
#define HI_TIMER_09_REGBASE_ADDR          0xe8a00000   //对应k3 timer41
#define HI_TIMER_10_REGBASE_ADDR          0xe8a01000   //对应k3 timer50
#define HI_TIMER_11_REGBASE_ADDR          0xe8a01000   //对应k3 timer51
#define HI_TIMER_12_REGBASE_ADDR          0xe8a02000   //对应k3 timer60
#define HI_TIMER_13_REGBASE_ADDR          0xe8a02000   //对应k3 timer61
#define HI_TIMER_14_REGBASE_ADDR          0xe8a03000   //对应k3 timer70
#define HI_TIMER_15_REGBASE_ADDR          0xe8a03000   //对应k3 timer71
#define TIMER_ADDR_SIZE                   0X1000        //单个timer地址大小
/*K3形态以下timer打桩*/
#define HI_TIMER_16_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_17_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_18_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_19_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_20_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_21_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_22_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_23_REGBASE_ADDR          0xFFFFFFFF

/**********************end:timer********************/

#ifdef __cplusplus
}
#endif

#endif    /* __SOC_MEMMAP_APP_H__ */

