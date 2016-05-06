#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bsp_busstress.h"

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
	    __alloc_next = (unsigned)SRAM_BUSSTRESS_ADDR + (2*1024);
		
		count = 1;
	}
	
    ptr = (void*) __alloc_next;
    __alloc_next = (__alloc_next + sz + 31) & (~31);


    return ptr;
}

int memcpyTestProcess(unsigned int uiSrc,unsigned int uiDst,int iSize)
{

	srand((unsigned int)time((time_t*)0));
	memset((void*)uiSrc,rand(),iSize);
	memset((void*)uiDst,0,iSize);
	memcpy((void*)uiDst,(void*)uiSrc,iSize);
	#if 0/*提高压力不检测数据是否正确*/
	iRet = memcmp((void*)uiSrc,(void*)uiDst,iSize);
	if(0 != iRet)
	{
		printf("memcmp fail,iRet:0x%x\n",iRet);
		return iRet;
	}
    #endif
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
