#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <osl_cache.h>
#include <bsp_sram.h>
#include <bsp_busstress.h>

#define SENCE_NUM (4)
#define MODULE_NUM (20)

char* g_testSenceName[SENCE_NUM] = {"S1","S2","S3","S4"};
int   module_test_switch_stat[MODULE_NUM] = {0};
static unsigned __alloc_next = 0;

void *alloc(signed sz)
{
    void *ptr;
	static unsigned int count = 0;

	if(0 == count){
	    __alloc_next = (unsigned int)SRAM_BUSSTRESS_ADDR + (2*1024);
		
		count = 1;
	}
	
    ptr = (void*) __alloc_next;
    __alloc_next = (__alloc_next + sz + 31) & (~31);


    return ptr;
}

int memcpyTestProcess(void* pSrcAddr, void* pDstAddr, int iSize)
{
	int iRet = 0;

	srand((unsigned int)time((time_t*)0));
	memset((void*)pSrcAddr, rand(),iSize);

	/* ddr->ddr 申请的就是不可cache的内存 */ 
	//(void)osl_cache_flush(OSL_DATA_CACHE, (void *)pSrcAddr, iSize); /* 从cache冲出 */

	memset((void*)pDstAddr, 0,     iSize);
	/* ddr->ddr 申请的就是不可cache的内存 */ 
	//(void)osl_cache_flush(OSL_DATA_CACHE, (void *)pDstAddr, iSize); /* 从cache冲出 */
	
	memcpy((void*)pDstAddr, (void*)pSrcAddr, iSize);
	/* ddr->ddr 申请的就是不可cache的内存 */ 
	//(void)osl_cache_invalid(OSL_DATA_CACHE, (void *)pSrcAddr, iSize);
	//(void)osl_cache_invalid(OSL_DATA_CACHE, (void *)pDstAddr, iSize);

	/* 比较3个字节数据:第一个、中间一个、最后一个 */
	iRet = memcmp((void*)pSrcAddr, (void*)pDstAddr, 1);
	if (0 != iRet)
	{
		return iRet;
	}

    /* 中间一个 */
	iRet = memcmp((void*)((unsigned char*)pSrcAddr + iSize / 2), 
		          (void*)((unsigned char*)pDstAddr + iSize / 2),
		          1);
	if (0 != iRet)
	{
		return iRet;
	}

    /* 最后一个 */
	iRet = memcmp((void*)((unsigned char*)pSrcAddr + iSize -1), 
		          (void*)((unsigned char*)pDstAddr + iSize -1),
		          1);
	if (0 != iRet)
	{
		return iRet;
	}

	return 0;
}


int get_test_switch_stat(int module_id)
{
	return module_test_switch_stat[module_id];
}

int set_test_switch_stat(int module_id, int run_or_stop)
{
	module_test_switch_stat[module_id] = run_or_stop;
	return 0;
}
