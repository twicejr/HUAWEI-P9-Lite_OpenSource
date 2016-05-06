/*--------------------------------------------------------------------------------------------------------------------------
*此文件主要是实现L2CACHE的筛片功能
*说明功能:将MODEM镜像所在的1M空间数据搬到测试空间的低端，比较原始镜像和低端
*         再将低端数据搬移到高端，比较高低端差异
*         将测试空间低端设置为值0x5A5A5A5A,将低端数据搬移到高端，比较高低端差异
*         如果最后的结果仍然是OK的，A9进入死循环，写标志。
*--------------------------------------------------------------------------------------------------------------------------*/
/**
* @file l2cache_screening.c
*
*
* 描述：L2CACHE筛片功能。
*/
#include <string.h>
#include "l2cache_screening.h"

/* 为了保证flush&inc效果，需要先flush L1,再flush&inv L2,最后flush&inv L1*/

void cache_screening_case(void)
{
    unsigned int test_count = 0;

    for(test_count = 1; test_count < 6; test_count++)
    {
        memset_s((void*)(CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),(size_t)MINI_PAGE_SIZE,
                       0xa5a5a5a5,(size_t)MINI_PAGE_SIZE);
        memcpy_s((void*)(CACHE_TEST_END_ADDR - test_count * MINI_PAGE_SIZE),(size_t)MINI_PAGE_SIZE,
               (void*)(CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),
                        (size_t)MINI_PAGE_SIZE);
        if (memcmp((void*)(CACHE_TEST_END_ADDR - test_count * MINI_PAGE_SIZE),
                    (void*)(CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),
                            MINI_PAGE_SIZE))
        {
            while (1)
            {
                ARMA9CTX_REGISTER_WRITE(CACHE_TEST_FLAG_ADDR,test_count);
                CACHE_FLUSH_AND_INV_ALL;
            }
        }
    }
    for(test_count = 6; test_count < 11; test_count++)
    {
        memset_s((void*)(CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),(size_t)MINI_PAGE_SIZE,
                       0x5a5a5a5a,(size_t)MINI_PAGE_SIZE);
        memcpy_s((void*)(CACHE_TEST_END_ADDR - test_count * MINI_PAGE_SIZE),(size_t)MINI_PAGE_SIZE,
               (void*)(CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),
                        (size_t)MINI_PAGE_SIZE);
        if (memcmp((void*)(CACHE_TEST_END_ADDR - test_count * MINI_PAGE_SIZE),
                    (void*)(CACHE_TEST_START_ADDR + MINI_PAGE_SIZE * test_count),
                            MINI_PAGE_SIZE))
        {
            while (1)
            {
                ARMA9CTX_REGISTER_WRITE(CACHE_TEST_FLAG_ADDR,test_count);
                CACHE_FLUSH_AND_INV_ALL;
            }
        }
    }
    while (1)
    {
        ARMA9CTX_REGISTER_WRITE(CACHE_TEST_FLAG_ADDR,0xA5A5A5A5);
        CACHE_FLUSH_AND_INV_ALL;
    }
}

