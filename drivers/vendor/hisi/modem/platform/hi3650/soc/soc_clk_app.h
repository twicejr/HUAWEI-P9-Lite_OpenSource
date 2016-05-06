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

#ifndef __SOC_CLK_APP__
#define __SOC_CLK_APP__
#include "soc_clk.h"
/*k3 AP 8个timer的频率*/
#define HI_TIMER0_CLK               (32*1024)
#define HI_TIMER1_CLK               (32*1024)
#define HI_TIMER2_CLK               (32*1024)
#define HI_TIMER3_CLK               (32*1024)
#define HI_TIMER4_CLK               (32*1024)
#define HI_TIMER5_CLK               (32*1024)
#define HI_TIMER6_CLK               (32*1024)
#define HI_TIMER7_CLK               (32*1024)
#define HI_TIMER8_CLK               (32*1024)
#define HI_TIMER9_CLK               (32*1024)
#define HI_TIMER10_CLK               (32*1024)
#define HI_TIMER11_CLK               (32*1024)
#define HI_TIMER12_CLK               (32*1024)
#define HI_TIMER13_CLK               (32*1024)
#define HI_TIMER14_CLK               (32*1024)
#define HI_TIMER15_CLK               (32*1024)
/*保持和v7r2一致，以下为打桩*/
#define HI_TIMER16_CLK               (32*1024)
#define HI_TIMER17_CLK               (32*1024)
#define HI_TIMER18_CLK               (32*1024)
#define HI_TIMER19_CLK               (32*1024)
#define HI_TIMER20_CLK               (32*1024)
#define HI_TIMER21_CLK               (32*1024)
#define HI_TIMER22_CLK               (32*1024)
#define HI_TIMER23_CLK               (32*1024)


#define TIMER_NUM 24 /*物理timer数量*/


#endif/*__SOC_CLK_APP__*/
