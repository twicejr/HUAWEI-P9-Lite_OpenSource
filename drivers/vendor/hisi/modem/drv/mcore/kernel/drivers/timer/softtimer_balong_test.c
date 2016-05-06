/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  softtimer_balong_test.c.c
*
*   作    者 :  lixiaojie l00227190
*
*   描    述 :  本文件主要完成softtimer驱动测试
*
*   修改记录 :  2013年2月20日  v1.00  l00227190  创建
*************************************************************************/
#include <osl_common.h>
#include <bsp_softtimer.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>
#include "softtimer_balong.h"
extern void printksync(const char *fmt, ...);
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
#define  softtimer_print(fmt, ...)    (printk("[softtimer]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
#else
#define  softtimer_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOFTTIMER, "[softtimer]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
#endif

osSemaphoreId      sem1,sem2,sem3,sem4,sem5,sem6;
osSemaphoreDef(sem1);
osSemaphoreDef(sem2);
osSemaphoreDef(sem3);
osSemaphoreDef(sem4);
osSemaphoreDef(sem5);
osSemaphoreDef(sem6);

struct softtimer_list my_softtimer,my_sec_softtimer,my_thir_softtimer;
struct softtimer_list myown_timer[50];
u32 num[10] = {0};
void for_softtimer_test_1(u32 para)
{
    u32 ret;
	
    ret = bsp_softtimer_free(&my_softtimer);
    if (ret !=OK)
    {
    	softtimer_print("for_softtimer_test_1  free error\n");
	    return;
    }
	osSemaphoreRelease(sem1);
    return;
}
void for_softtimer_test_2(u32 para)
{
    s32 ret = 0;
    num[0]++;
    if (num[0]<10)
    {
       bsp_softtimer_add(&my_softtimer);
    }
    else if (num[0]==10)
     {
         num[0] = 0;
         ret = bsp_softtimer_free(&my_softtimer);
         if (ret !=OK)
		{
	  	softtimer_print("for_softtimer_test_2  free error\n");
		return;
		}
	osSemaphoreRelease(sem2);
   }
   return;
}
void for_softtimer_test_3(u32 para)
{
    s32 ret = 0;
    num[1]++;
    if (num[1]<10)
    {   
   	  ret = bsp_softtimer_modify(&my_softtimer,num[1]*100);
	  if (ret !=OK)
	  {
	 	softtimer_print("for_softtimer_test_3  11modify error\n");
		return;
	  }
	  bsp_softtimer_add(&my_softtimer);
    }
    if (num[1]==10)
    {
    	num[1] = 0;
        ret = bsp_softtimer_free(&my_softtimer);
        if (ret !=OK)
		{
			softtimer_print("for_softtimer_test_3  free error\n");
			return;
        }
		
		osSemaphoreRelease(sem3);
	}	
	return;
}
void for_softtimer_test_4(u32 para)
{
    softtimer_print("para = %d \n",para);
    num[2]++;
    if (num[2]<50)
    {   
	  bsp_softtimer_add(&myown_timer[para]);
    }
    num[2] = 0;
    return;
}
void  for_softtimer_test_5(u32 para)
{
    u32 ret;
    ret = bsp_softtimer_free(&my_sec_softtimer);
    if (ret !=OK)
    {
    	softtimer_print("for_softtimer_test_5  free error\n");
    	return ;
    } 
    
	osSemaphoreRelease(sem5);
    return ;
}
void for_softtimer_test_6(u32 para)
{
    u32 ret;
    ret = bsp_softtimer_free(&my_thir_softtimer);
    if (ret !=OK)
    {
    	softtimer_print("for_softtimer_test_6  free error\n");
	    return ;
    }
	osSemaphoreRelease(sem6);
    return ;
}
void for_softtimer_test_7(u32 para)
{
   printksync("for_softtimer_test_7,para=%d\n",para);
    bsp_softtimer_add(&myown_timer[para]);
    return ;
}
void for_softtimer_test_8(u32 para)
{
    bsp_softtimer_add(&my_softtimer);
   return ;
}
void for_softtimer_test_9(u32 para)
{
    softtimer_print("para = %d \n",para);
    bsp_softtimer_add(&my_sec_softtimer);
    return ;
}


/*测试唤醒源软timer申请和加入链表,在回调函数释放*/
s32 st_softtimer_test_case01(void)
{
	s32 ret = 0;
	my_softtimer.func =for_softtimer_test_1;
	my_softtimer.para = 123;
	my_softtimer.timeout = 1;
	my_softtimer.wake_type=SOFTTIMER_WAKE;
	sem1=osSemaphoreCreate(osSemaphore(sem1),SEM_FULL);
	osSemaphoreWait(sem1, osWaitForever);
	ret = bsp_softtimer_create(&my_softtimer);
	if (ret)
	{
		softtimer_print("create error\n");
		return ERROR;
	}
	bsp_softtimer_add(&my_softtimer);
	osSemaphoreWait(sem1, osWaitForever);
	osSemaphoreDelete(sem1);
	return OK;
}
/*测试唤醒源软timer申请和加入链表,重复执行十次后释放*/
s32 st_softtimer_test_case02(void)
{
	s32 ret = 0;
	my_softtimer.func =for_softtimer_test_2;
	my_softtimer.para = 123;
	my_softtimer.timeout = 1;
	my_softtimer.wake_type=SOFTTIMER_WAKE;
	sem2=osSemaphoreCreate(osSemaphore(sem2),SEM_FULL);
	osSemaphoreWait(sem2, osWaitForever);
	ret = bsp_softtimer_create(&my_softtimer);
	if (ret)
	{
		softtimer_print("create error\n");
		return ERROR;
	}
	bsp_softtimer_add(&my_softtimer);
	osSemaphoreWait(sem2, osWaitForever);
	osSemaphoreDelete(sem2);
	return OK;
}

/*测试唤醒源软timer申请和加入链表重复10次，每次都在回调函数修改超时时间*/
s32 st_softtimer_test_case03(void)
{
	s32 ret = 0;
	my_softtimer.func =for_softtimer_test_3;
	my_softtimer.para = 123;
	my_softtimer.timeout = 1;
	my_softtimer.wake_type=SOFTTIMER_WAKE;
	sem3=osSemaphoreCreate(osSemaphore(sem3),SEM_FULL);
	osSemaphoreWait(sem3, osWaitForever);
	ret = bsp_softtimer_create(&my_softtimer);
	if (ret)
	{
		softtimer_print("create error\n");
		return ERROR;
	}
	bsp_softtimer_add(&my_softtimer);
	osSemaphoreWait(sem3, osWaitForever);
	osSemaphoreDelete(sem3);
	return OK;
}

/*测试创建三个唤醒源软timer，按照超时时间大小按顺序执行其超时函数*/
s32 st_softtimer_test_case04(void)
{
	s32 ret = 0;
	my_softtimer.func = for_softtimer_test_1;
	my_softtimer.wake_type=SOFTTIMER_WAKE;
	my_softtimer.para = 1;
	my_softtimer.timeout = 60000;
	sem1=osSemaphoreCreate(osSemaphore(sem1),SEM_FULL);
	sem5=osSemaphoreCreate(osSemaphore(sem5),SEM_FULL);
	sem6=osSemaphoreCreate(osSemaphore(sem6),SEM_FULL);
	osSemaphoreWait(sem1, osWaitForever);
	osSemaphoreWait(sem5, osWaitForever);
	osSemaphoreWait(sem6, osWaitForever);
	ret= bsp_softtimer_create(&my_softtimer);
	if (ret)
	{
		softtimer_print("create error \n");
		return ERROR;
	}
	bsp_softtimer_add(&my_softtimer);
	my_sec_softtimer.func = for_softtimer_test_5;
	my_sec_softtimer.para = 2;
	my_sec_softtimer.timeout = 90000;
	ret= bsp_softtimer_create(&my_sec_softtimer);
	if (ret)
	{
		softtimer_print("create error \n");
		return ERROR;
	}
	bsp_softtimer_add(&my_sec_softtimer);
	my_thir_softtimer.func = for_softtimer_test_6;
	my_thir_softtimer.para = 2;
	my_thir_softtimer.timeout = 120000;
	ret= bsp_softtimer_create(&my_thir_softtimer);
	if (ret)
	{
		softtimer_print("create error \n");
		return ERROR;
	}
	bsp_softtimer_add(&my_thir_softtimer);
	osSemaphoreWait(sem1, osWaitForever);
	osSemaphoreWait(sem5, osWaitForever);
	osSemaphoreWait(sem6, osWaitForever);
	osSemaphoreDelete(sem1);
	osSemaphoreDelete(sem5);
	osSemaphoreDelete(sem6);
	return OK;
}

/*测试唤醒源软timer申请和加入链表，在回调函数外删除软timer
   超时时间较短*/
   #if 0
s32 st_softtimer_test_case05(void)
{
	s32 ret= 0;
	
	sft_info.func = for_softtimer_test_1;
	sft_info.para = 123;
	sft_info.timeout = 1;
	sft_info.wake_type=SOFTTIMER_WAKE;
	sem1=osSemaphoreCreate(osSemaphore(sem1),SEM_FULL);
	osSemaphoreWait(sem1, osWaitForever);
	my_softtimer = bsp_softtimer_create(sft_info);
	 if (NULL ==  my_softtimer)
	 {
		softtimer_print("create error \n");
		return ERROR;
	 }
	 bsp_softtimer_add(my_softtimer);
	 ret = bsp_softtimer_delete(my_softtimer);
	 if (ret ==OK)
	 {
	    ret = bsp_softtimer_free(my_softtimer);
	    if (ret !=OK)
	    {
	    	softtimer_print("softtimer_test_5  free error\n");
			return ret;
	    }
	    
	}
	else if(NOT_ACTIVE == ret)
	{
		osSemaphoreWait(sem1, osWaitForever);
	}
	osSemaphoreDelete(sem1);
	return OK;	
}
/*测试唤醒源软timer申请和加入链表，在回调函数外删除软timer
   超时时间较长*/
s32 st_softtimer_test_case06(void)
{
	s32 ret= 0;
	
	sft_info.func = for_softtimer_test_1;
	sft_info.para = 123;
	sft_info.timeout = 100;
	sft_info.wake_type=SOFTTIMER_WAKE;
	sem1=osSemaphoreCreate(osSemaphore(sem1),SEM_FULL);
	osSemaphoreWait(sem1, osWaitForever);
	my_softtimer = bsp_softtimer_create(sft_info);
	 if (NULL ==  my_softtimer)
	 {
		softtimer_print("create error \n");
		return ERROR;
	 }
	 bsp_softtimer_add(my_softtimer);
	 ret = bsp_softtimer_delete(my_softtimer);
	 if (ret ==OK)
	 {
	    ret = bsp_softtimer_free(my_softtimer);
	    if (ret !=OK)
	    {
	    		softtimer_print("softtimer_test_6  free error\n");
			return ERROR;
	    }
	    
	}
	else if(NOT_ACTIVE == ret)
	{
		osSemaphoreWait(sem1, osWaitForever);
	}
	osSemaphoreDelete(sem1);
	return OK;
}
/*测试唤醒源软timer申请和加入链表,LOOP模式，执行一段时间后在回调函数外delete*/
s32 st_softtimer_test_case07(void)
{
	s32 ret=0;
	
	sft_info.func = for_softtimer_test_8;
	sft_info.para = 123;
	sft_info.timeout = 1;
	sft_info.wake_type=SOFTTIMER_WAKE;
	my_softtimer = bsp_softtimer_create(sft_info);
	if (NULL == my_softtimer)
	{
		softtimer_print("create error\n");
		return ERROR;
	}
	bsp_softtimer_add(my_softtimer);
	udelay(200);
	ret = bsp_softtimer_delete(my_softtimer);
	if(OK!=ret)
	{
		softtimer_print("bsp_softtimer_delete_sync failed\n");
		return ERROR;
	}
	ret = bsp_softtimer_free(my_softtimer);
	if(OK!=ret)
	{
		softtimer_print("bsp_softtimer_free failed\n");
		return ERROR;
	}
	
	return OK;	
}

void st_softtimer_test_case08(void)
{
	s32 i=0;
	
	sft_info.func = for_softtimer_test_7;
	sft_info.wake_type=SOFTTIMER_WAKE;
	for(i=0;i<4;i++)
	{
		sft_info.para = i;
		sft_info.timeout = 1000+i*1000;
		myown_timer[i] = bsp_softtimer_create(sft_info);
		if (NULL == myown_timer[i])
		{
			softtimer_print("create error i =%d\n",i);
			return ;
		}
		bsp_softtimer_add(myown_timer[i]);
	}	
}

/*在case15或case16运行的情况下运行本测试用例，测试是否可以删除多个定时器*/
s32 st_softtimer_test_case09(void)
{
    int i = 0;
    int ret;
    while(i<31)
    {
		ret = bsp_softtimer_delete(myown_timer[i]);
	 	if(OK!=ret)
	 	{
			softtimer_print("bsp_softtimer_delete_sync failed\n");
			return ERROR;
	 	}
	 	ret = bsp_softtimer_free(myown_timer[i]);
	  	if(OK!=ret)
	 	{
			softtimer_print("bsp_softtimer_free failed\n");
			return ERROR;
	 	}
	 	myown_timer[i]=NULL;
	 	i++;
    }
    return OK;
}
s32 softtimer_test(void)
{
	s32 ret = 0;
	ret = st_softtimer_test_case01();
	if(OK==ret)
		softtimer_print("st_softtimer_test_case01 pass\n");
	else
		softtimer_print("st_softtimer_test_case01 fail\n");
	ret = st_softtimer_test_case02();
	if(OK==ret)
		softtimer_print("st_softtimer_test_case02 pass\n");
	else
		softtimer_print("st_softtimer_test_case02 fail\n");
	ret = st_softtimer_test_case03();
	if(OK==ret)
		softtimer_print("st_softtimer_test_case03 pass\n");
	else
		softtimer_print("st_softtimer_test_case03 fail\n");
	ret = st_softtimer_test_case04();
	if(OK==ret)
		softtimer_print("st_softtimer_test_case04 pass\n");
	else
		softtimer_print("st_softtimer_test_case04 fail\n");
	ret = st_softtimer_test_case05();
	if(OK==ret)
		softtimer_print("st_softtimer_test_case05 pass\n");
	else
		softtimer_print("st_softtimer_test_case05 fail\n");
	ret = st_softtimer_test_case06();
	if(OK==ret)
		softtimer_print("st_softtimer_test_case06 pass\n");
	else
		softtimer_print("st_softtimer_test_case06 fail\n");
	ret = st_softtimer_test_case07();
	if(OK==ret)
		softtimer_print("st_softtimer_test_case07 pass\n");
	else
		softtimer_print("st_softtimer_test_case07 fail\n");
	return OK;
}
#endif
