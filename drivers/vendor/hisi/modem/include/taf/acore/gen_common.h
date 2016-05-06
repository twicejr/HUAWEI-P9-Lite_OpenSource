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


#ifndef __GEN_COMMON_H__
#define __GEN_COMMON_H__


#include "gen_msg.h"
#include <string.h>



#define MSP_CNF_PACKET_SIGN              (0x80000000)
#define MSP_SYS_PACKET_SIGN              (0x40000000)
#define MSP_GE_PACKET_SIGN               (0)


#define MSP_ALIGIN_U32_SIZE(x)  ((x&(~3))+4) /* 构造4个字节对齐*/
#define MSP_IS_ALIGIN_U32(x)    ((x)&3)      /* 判断是否为4字节对齐*/
#define MSP_FIELDOFFSET(s,m)             (VOS_UINT32)&(((s *)0)->m) /* 结构成员偏移*/
#define MSP_CHAR_CR   '\r' /* 0x0D*/
#define MSP_CHAR_LF   '\n' /* 0x0A*/
#define AT_TERMINAL_CHAR  MSP_CHAR_CR


/* 给HSO标识是CNF*/
#define MSP_CNF_PACKET_SIGN              (0x80000000)
#define MSP_SYS_PACKET_SIGN              (0x40000000)
#define MSP_GE_PACKET_SIGN               (0)

/* MSP NV 项定义*/
#define MSP_MAX_HWVER_SIZE     (31)
#define MSP_MAX_IMEI_SIZE      (9)

#define MAKEU16(a, b)       ((VOS_UINT16)(((VOS_UINT8)(a)) | ((VOS_UINT16)((VOS_UINT8)(b))) << 8))
#define MAKEU32(a, b)       ((VOS_UINT32)(((VOS_UINT16)(a)) | ((VOS_UINT32)((VOS_UINT16)(b))) << 16))


#define MSP_MAKE_IDENTIFIER(a,b,c,d)     MAKEU32(MAKEU16(a,b),MAKEU16(c,d))
#define HNV_FILE_SIGNATURE               MSP_MAKE_IDENTIFIER('H','N','V','$')


#define VOLATILE_GETVAR(x,val) (x = val)
#define VOLATILE_VAR(x, val)   (x = val)
#define VOLATILE_VARADD(x)     (x++)


typedef struct
{
    /* 数组第一个元素为长度*/
    /* 数组第二个元素的低4位为奇偶校验位，*/
    /* 其余从前一个元素的高4位到后一个元素的低4位采用BCD码方式依次排列IMEI*/
    VOS_UINT8 aucImei[MSP_MAX_IMEI_SIZE];
    VOS_UINT8 aucRsd[3];
}MSP_NV_IMEI_STRU;



#endif /* __MSP_COMMON_H__*/

