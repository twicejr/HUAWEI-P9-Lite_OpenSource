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

#ifndef __HI_VIC_H__
#define __HI_VIC_H__

/*
 * Project: hi
 * Module : timer
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    vic 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_VIC_INTEN_L_OFFSET                      (0x0) 
#define    HI_VIC_INTEN_H_OFFSET                      (0x4) 
#define    HI_VIC_INTMASK_L_OFFSET                    (0x8) 
#define    HI_VIC_INTMASK_H_OFFSET                    (0xC) 
#define    HI_VIC_INTFORCE_L_OFFSET                   (0x10) 
#define    HI_VIC_INTFORCE_H_OFFSET                   (0x14) 
#define    HI_VIC_RAWSTATUS_L_OFFSET                  (0x18) 
#define    HI_VIC_RAWSTATUS_H_OFFSET                  (0x1C) 
#define    HI_VIC_STATUS_L_OFFSET                     (0x20) 
#define    HI_VIC_STATUS_H_OFFSET                     (0x24) 
#define    HI_VIC_MASKSTATUS_L_OFFSET                 (0x28) 
#define    HI_VIC_MASKSTATUS_H_OFFSET                 (0x2C) 
#define    HI_VIC_FINALSTATUS_L_OFFSET                (0x30) 
#define    HI_VIC_FINALSTATUS_H_OFFSET                (0x34) 
#define    HI_VIC_VECTOR_OFFSET                       (0x38) 
#define    HI_VIC_VECTOR_0_OFFSET                     (0x40) 
#define    HI_VIC_VECTOR_1_OFFSET                     (0x48) 
#define    HI_VIC_VECTOR_2_OFFSET                     (0x50) 
#define    HI_VIC_VECTOR_3_OFFSET                     (0x58) 
#define    HI_VIC_VECTOR_4_OFFSET                     (0x60) 
#define    HI_VIC_VECTOR_5_OFFSET                     (0x68) 
#define    HI_VIC_VECTOR_6_OFFSET                     (0x70) 
#define    HI_VIC_VECTOR_7_OFFSET                     (0x78) 
#define    HI_VIC_VECTOR_8_OFFSET                     (0x80) 
#define    HI_VIC_VECTOR_9_OFFSET                     (0x88) 
#define    HI_VIC_VECTOR_10_OFFSET                    (0x90) 
#define    HI_VIC_VECTOR_11_OFFSET                    (0x98)
#define    HI_VIC_VECTOR_12_OFFSET                    (0xA0)
#define    HI_VIC_VECTOR_13_OFFSET                    (0xA8)
#define    HI_VIC_VECTOR_14_OFFSET                    (0xB0)
#define    HI_VIC_VECTOR_15_OFFSET                    (0xB8)

#endif __HI_VIC_H__

