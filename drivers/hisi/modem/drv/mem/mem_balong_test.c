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

#include "mem_balong.h"
#include <osl_types.h>
#include "mem_balong.h"
#include "mem_balong_drv.h"
#include <linux/delay.h>

#define MEM_TEST_OK         0
#define MEM_TEST_ERROR      1
#define ACORE_MAGIC_NUM           'A'

/*u32 mem_malloc_test(u32 size)
{
    void * pret = BSP_Malloc(size, MEM_ICC_DDR_POOL);
    if(pret)
    {
        mem_print_dbg("sucess BSP_Malloc addr:%x   size:%d", pret, size);
        BSP_Free(pret);
        return MEM_TEST_OK;
    }
    else
    {
        mem_print_dbg("fail! BSP_Malloc addr:%x   size:%d", pret, size);
        return MEM_TEST_ERROR;
    }

}

s32 malloc_mem_test_case0()
{
    return mem_malloc_test(12);
}

s32 malloc_mem_test_case1()
{
    return mem_malloc_test(32);
}
s32 alloc_mem_test_case2()
{
    return mem_malloc_test(128*1024);
}
s32 malloc_mem_test_case1()
{
    return mem_malloc_test(1024);
}
s32 malloc_mem_test_case1()
{
    return mem_malloc_test(4094);
}*/


u32 mem_smalloc_test(u32 size)
{
    void * pret = bsp_smalloc(size, MEM_ICC_DDR_POOL);
    if(pret)
    {
        mem_print_dbg("sucess BSP_Malloc addr:%p   size:%d", pret, size);
        bsp_sfree(pret);
        return MEM_TEST_OK;
    }
    else
    {
        mem_print_error("fail! BSP_Malloc addr:%p   size:%d", pret, size);
        return MEM_TEST_ERROR;
    }

}

s32 malloc_smem_test_case0(void)
{
    return mem_smalloc_test(12);
}

s32 malloc_smem_test_case1(void)
{
    return mem_smalloc_test(32);
}
s32 malloc_smem_test_case2(void)
{
    return mem_smalloc_test(128*1024);
}
s32 malloc_smem_test_case3(void)
{
    return mem_smalloc_test(1024);
}
s32 malloc_smem_test_case4(void)
{
    return mem_smalloc_test(4094);
}



s32 use_smem_test(int size)
{
    u32* pret = (u32*)bsp_smalloc(size, MEM_ICC_DDR_POOL);
    u32* praw = pret;
    u32  rawsize = size;
    if(pret)
    {
        mem_print_dbg("sucess BSP_Malloc addr:%p   size:%d", pret, size);
        while(size > 0)
        {
            size -= 4;
            *pret = ACORE_MAGIC_NUM;
            pret++;
        }
        msleep(30);
        size = rawsize;
        pret = praw;
        while(size > 0)
        {
            size -= sizeof(u32);
            if(*pret != ACORE_MAGIC_NUM)
            {
                mem_print_error("fail! Use smalloc fail addr:%p     size:%d", pret, size);
                return MEM_TEST_ERROR;
            }
            pret++;
        }

        bsp_sfree(praw);
        return MEM_TEST_OK;
    }
    else
    {
        mem_print_error("fail! BSP_Malloc addr:%p   size:%d", pret, size);
        return MEM_TEST_ERROR;
    }
}


s32 use_smem_test_case0(void)
{
    return use_smem_test(12);
}
s32 use_smem_test_case1(void)
{
    return use_smem_test(56);
}
s32 use_smem_test_case2(void)
{
    return use_smem_test(64*1024);
}
s32 use_smem_test_case3(void)
{
    return use_smem_test(55);
}



