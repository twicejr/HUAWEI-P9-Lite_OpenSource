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

#ifndef __HI_BBP_SYSTIME_H__
#define __HI_BBP_SYSTIME_H__
#include "product_config.h"
/*
 * Project: hi
 * Module : bbp_systime
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    bbp_systime 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#ifdef BSP_CONFIG_K3V3_SFT
#define    HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET                 0x1008 /* DRX绝对定时的低32位 */
#define    HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET                 0x100c /* DRX绝对定时的高32位 */
#else
#define    HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET                 0x534 /* DRX绝对定时的低32位 */
#define    HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET                 0x538 /* DRX绝对定时的高32位 */
#endif

#ifndef __ASSEMBLY__

/********************************************************************************/
/*    bbp_systime 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    fpga_version               : 32; /* [31..0] F1版本号 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_FPGA_VERSION_T;    /* F1版本号 */

typedef union
{
    struct
    {
        unsigned int    abs_timer_l                : 32; /* [31..0] DRX绝对定时的低32位 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABS_TIMER_L_T;    /* DRX绝对定时的低32位 */

typedef union
{
    struct
    {
        unsigned int    abs_timer_h                : 32; /* [31..0] DRX绝对定时的高32位 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABS_TIMER_H_T;    /* DRX绝对定时的高32位 */

typedef union
{
    struct
    {
        unsigned int    drp_data                   : 32; /* [31..0] DRP数据 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_DRP_DATA_T;    /* DRP数据 */

typedef union
{
    struct
    {
        unsigned int    abb_rst                    : 32; /* [31..0] ABB复位控制 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABB_RST_T;    /* ABB复位控制 */


/********************************************************************************/
/*    bbp_systime 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
#if 0
HI_SET_GET(hi_bbp_systime_abs_timer_l_abs_timer_l,abs_timer_l,HI_BBP_SYSTIME_ABS_TIMER_L_T,HI_BBP_SYSTIME_BASE_ADDR, HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)
HI_SET_GET(hi_bbp_systime_abs_timer_h_abs_timer_h,abs_timer_h,HI_BBP_SYSTIME_ABS_TIMER_H_T,HI_BBP_SYSTIME_BASE_ADDR, HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET)
#endif
#endif

#endif // __HI_BBP_SYSTIME_H__

