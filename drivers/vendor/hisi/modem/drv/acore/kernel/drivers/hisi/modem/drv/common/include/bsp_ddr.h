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

#ifndef __BSP_DDR_H__
#define __BSP_DDR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"

#ifdef DDR_MEM_ADDR_FAMA

#define FAMA_DIFF  (DDR_MEM_ADDR_FAMA - DDR_MEM_ADDR)
#define MDDR_FAMA_TO(x)     (FAMA_DIFF+(unsigned long long)(x))
#define MDDR_FAMA_FROM(x)   (unsigned long)((x)-FAMA_DIFF)
#if defined(__KERNEL__) || defined(FASTBOOT_VERSION)
    #define MDDR_FAMA(x)    MDDR_FAMA_TO(x)
#else 
    #define MDDR_FAMA(x)    (x)
#endif
/* ipf,psam,cipher,socp 高32bit配置，传入值x为32bit数 */
/* 寄存器可配7bit，实际高3bit默认为0 128byte交织不动，只需要配置4bit */
#define MDDR_FAMA_CHAN(x)   ((unsigned long)(MDDR_FAMA_TO(x)>>32) & 0x7F)


#else

#define MDDR_FAMA_TO(x)     (x)
#define MDDR_FAMA_FROM(x)   (x)
#define MDDR_FAMA(x)        (x)
#define MDDR_FAMA_CHAN(x)   (0)

#endif


#ifdef __cplusplus
}
#endif

#endif    /* __BSP_DDR_H__ */

