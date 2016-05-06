/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : libPatch.c
  版 本 号   : 初稿
  作    者   : w00253990
  生成日期   : 2013年11月08日
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :

******************************************************************************/
#ifdef __OS_RTOSCK__

#include "sre_mem.h"
#include "time.h"
#include <sys/time.h>
#include <sre_shell.h>
#include <string.h>
/*lint -e10 -e19 -e410 -e453*/
#define isdigit(c) ('0' <= (c) && (c)  <= '9')

#ifndef __va_list__
typedef char *va_list;
#define __va_list__
#endif
/*lint +e10 +e19 +e410 +e453*/
extern int vsnprintf(char *buf, unsigned int size, const char *fmt, va_list args);

#define  _AUPBND                (sizeof (signed int) - 1)
#define  _ADNBND                (sizeof (signed int) - 1)

#define _bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)           (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define va_end(ap)              (void) 0
#define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))

int sprintf(char * buf, const char *fmt, ...)
{
	va_list args;
	int i;
     /*lint -save -e586 -e64*/
	va_start(args, fmt);/*lint !e64*/
	i=vsnprintf(buf,0x7fffffff, fmt,args);
	va_end(args);
	/*lint -restore*/
	return i;
}


void *malloc(unsigned int size)
{
	return (void *)SRE_MemCacheAlloc(size, MEM_ADDR_ALIGN_004);
     
}

void free (void * ptr)
{
    (void)SRE_MemCacheFree(ptr); 
}
void __assert_func(const char *a, int b, const char *c, const char *d)
{
   return;
}
int _gettimeofday(struct timeval *tv, void *tz)		
{		
	if(!tv)		
	{		
	return -1;		
	}		
	//tv->tv_sec = (long)BSP_GET_RTC_VALUE(); 		
	// tv->tv_usec = (omTimerGet() % 32768) * (1000000 / 32768); 		
	return 0;		
}
#endif //__OS_RTOSCK__
