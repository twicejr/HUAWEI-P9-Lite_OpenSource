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

#ifndef __DIAG_MEM_H__
#define __DIAG_MEM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 Macro
*****************************************************************************/


/********************* BBP DS内存配置 **************************
* BBP LOG 0:  64K
* BBP LOG 1:   8K
* BBP LOG 2:   8K
* BBP LOG 3:   8K
* BBP LOG 4:   8K
* BBP LOG 5:   8K
* BBP LOG 6:   8K
* BBP LOG 7:   8K
* BBP DS   :  随机
* TOTAL SIZE: BBPDS + 120K
****************************************************************/
/*BBP 数采要求内存必须为2K对齐的*/
#define BBP_DS_MEM_UNIT_SIZE                        (2*1024)


/* TODO: 先用数字偏移，后期调整 */
#define BBP_MEM_ADDR_BASE                         	(DDR_SOCP_ADDR + (1024*64) + (1024*640) + (1024*32) + (1024*160))

#define BBP_LOG0_MEM_ADDR                        	(BBP_MEM_ADDR_BASE)
#define BBP_LOG0_MEM_SIZE                        	(64*1024)

#define BBP_LOG1_MEM_ADDR                        	(BBP_LOG0_MEM_ADDR + BBP_LOG0_MEM_SIZE)
#define BBP_LOG1_MEM_SIZE                        	(8*1024)

#define BBP_LOG2_MEM_ADDR                        	(BBP_LOG1_MEM_ADDR + BBP_LOG1_MEM_SIZE)
#define BBP_LOG2_MEM_SIZE                        	(8*1024)

#define BBP_LOG3_MEM_ADDR                        	(BBP_LOG2_MEM_ADDR + BBP_LOG2_MEM_SIZE)
#define BBP_LOG3_MEM_SIZE                        	(8*1024)

#define BBP_LOG4_MEM_ADDR                        	(BBP_LOG3_MEM_ADDR + BBP_LOG3_MEM_SIZE)
#define BBP_LOG4_MEM_SIZE                        	(8*1024)

#define BBP_LOG5_MEM_ADDR                        	(BBP_LOG4_MEM_ADDR + BBP_LOG4_MEM_SIZE)
#define BBP_LOG5_MEM_SIZE                        	(8*1024)

#define BBP_LOG6_MEM_ADDR                        	(BBP_LOG5_MEM_ADDR + BBP_LOG5_MEM_SIZE)
#define BBP_LOG6_MEM_SIZE                        	(8*1024)

#define BBP_LOG7_MEM_ADDR                        	(BBP_LOG6_MEM_ADDR + BBP_LOG6_MEM_SIZE)
#define BBP_LOG7_MEM_SIZE                        	(8*1024)

#define BBP_DS_MEM_ADDR                         	(BBP_LOG7_MEM_ADDR + BBP_LOG7_MEM_SIZE)
#define BBP_DS_ORIGIAL_MEM_SIZE                     (DDR_SOCP_ADDR+DDR_SOCP_SIZE -BBP_DS_MEM_ADDR)
#define BBP_DS_MEM_SIZE                             (BBP_DS_ORIGIAL_MEM_SIZE - BBP_DS_ORIGIAL_MEM_SIZE%BBP_DS_MEM_UNIT_SIZE)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of diag_mem.h */
