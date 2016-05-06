#include <osl_types.h>
#include <osl_thread.h>
#include "mem_balong.h"
#include "mem_balong_drv.h"
#include <taskLib.h>

#define MEM_TEST_OK         0
#define MEM_TEST_ERROR      1
#define ACORE_MAGIC_NUM           0x50505050


s32 malloc_smem_test_case0(void);
s32 malloc_smem_test_case1(void);
s32 malloc_smem_test_case2(void);
s32 malloc_smem_test_case3(void);
s32 malloc_smem_test_case4(void);
s32 use_smem_test_case0(void);
s32 use_smem_test_case1(void);
s32 use_smem_test_case2(void);
s32 use_smem_test_case3(void);

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


STATIC u32 mem_smalloc_test(u32 size)
{
    void * pret = bsp_smalloc(size, MEM_ICC_DDR_POOL);
    if(pret)
    {
        mem_print_dbg("sucess BSP_Malloc addr:%x   size:%d", pret, size);
        bsp_sfree(pret);
        return MEM_TEST_OK;
    }
    else
    {
        mem_print_error("fail! BSP_Malloc addr:%x   size:%d", pret, size);
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

STATIC s32 use_smem_test(int size)
{
    u32* pret = (u32*)bsp_smalloc(size, MEM_ICC_DDR_POOL);
    u32* praw = pret;
    u32  rawsize = size;
    if(pret)
    {
        mem_print_dbg("sucess BSP_Malloc addr:%x   size:%d", pret, size);
        while(size > 0)
        {
            size -= sizeof(u32);
            *pret = ACORE_MAGIC_NUM;
            pret++;
        }
        osl_task_delay(200);
        size = rawsize;
        pret = praw;
        while(size > 0)
        {
            size -= sizeof(u32);
            if(*pret != ACORE_MAGIC_NUM)
            {
                mem_print_error("fail! Use smalloc fail addr:%x     size:%d", pret, size);
                return MEM_TEST_ERROR;
            }
            pret++;
        }

        bsp_sfree(praw);
        return MEM_TEST_OK;
    }
    else
    {
        mem_print_error("fail! BSP_Malloc addr:%x   size:%d", pret, size);
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


