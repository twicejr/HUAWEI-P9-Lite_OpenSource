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

#ifndef __BSP_ATE_H__
#define __BSP_ATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include <soc_memmap_comm.h>
#include "hi_uart.h"
#ifdef ATE_VECTOR
#include "soc_ate.h"
#endif

#ifdef ATE_VECTOR
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/(sizeof((a)[0])))
#endif

#ifndef __ASSEMBLY__
static inline void print_dec(u32 val)
{
    u32 ret;

    if(val>10){
        ret= val%10;
        val= val/10;
        print_dec(val);
        ret = '0' + ret;
        writel((unsigned int)(ret),HI_UART0_REGBASE_ADDR + UART_REGOFFSET_RBR);
    }else{
        ret = '0' + val;
        writel((unsigned int)(ret),HI_UART0_REGBASE_ADDR + UART_REGOFFSET_RBR);
    }
}

static inline void print_hex(u32 val)
{
    u32 ret;
    u32 loop_cnt = 0;

    for(loop_cnt=0;loop_cnt<8;loop_cnt++){
        ret = (val & 0xf0000000) >> 28;
        val <<= 4;
        ret = (ret >= 10)?('A' + ret - 10):('0' + ret);
        writel((unsigned int)(ret),HI_UART0_REGBASE_ADDR + UART_REGOFFSET_RBR);
    }
}

static inline void print_info_with_hex(const char *buffer, u32 value)
{
    print_info(buffer);
    print_hex(value);
}

static inline void print_info_with_dec(const char *buffer, u32 value)
{
    print_info(buffer);
    print_dec(value);
}

struct ate_vector_wrap{
    int (*func)(void);
    unsigned int is_while;  /* when failed, while(1) or go ahead */
    unsigned int is_bad;    /* when failed, if vote to be bad chip */
    unsigned int pass_gpio;
    unsigned int fail_gpio;
    char case_name[32];
}ate_vector_wrap_s;

extern void ate_gpio_on(unsigned index);
extern int ate_memcopy_init(void);
extern int ate_cache_init(void);
#endif  /*__ASSEMBLY__*/

#endif /*ATE_VECTOR*/

#define return_if(x)\
do{\
    if(x){\
        return -1;\
    }\
}while(0)

#ifdef __cplusplus
}
#endif

#endif

