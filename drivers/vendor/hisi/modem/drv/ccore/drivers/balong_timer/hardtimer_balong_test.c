/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  hardtimer_balong_test.c.c
*
*   作    者 :  lixiaojie l00227190
*
*   描    述 :  本文件主要完成hardtimer驱动测试
*
*   修改记录 :  2013年2月20日  v1.00  l00227190  创建
*************************************************************************/
/*lint --e{64,438,534,537}*/

#include <osl_sem.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>

s32 hardtimer_test_case01(void);
s32 hardtimer_test_case02(void);
s32 hardtimer_test_case03(void);
s32 hardtimer_test_case04(void);
s32 hardtimer_test_case05(void);
s32 hardtimer_test_case06(void);
s32 hardtimer_test_case07(void);

s32 hardtimer_test(void);

int func(int para);

#ifndef OK
#define OK 0
#endif
#ifndef ERROR
#define ERROR  (-1)
#endif
#ifndef SEM_EMPTY
#define SEM_EMPTY 0
#endif
#ifndef SEM_FULL
#define SEM_FULL 1
#endif

osl_sem_id sem;/*lint !e129*//*lint !e19*/
u32 slice_delta[6];

int func(int para)
{
	osl_sem_up(&sem);/*lint !e129*//*lint !e40*/
	slice_delta[1]=bsp_get_slice_value();
	return 0;
}
s32 hardtimer_test_case01(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_CCPU_DSP_DRX_PROT_ID,func,0,32768,(u32)0,(u32)TIMER_UNIT_NONE);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	/*1s定时误差控制在6个slice，大于则认为有错*/
	if((slice_delta[1]-slice_delta[0]>32774)||(slice_delta[1]-slice_delta[0]<32765))
  	{
  		(void)mdrv_timer_stop(TIMER_CCPU_DSP_DRX_PROT_ID);
  		hardtimer_print_error("slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_CCPU_DSP_DRX_PROT_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}
s32 hardtimer_test_case02(void)
{
	s32 ret = 0;
	unsigned int restTime;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_DSP_TIMER2_ID,func,0,10000,(u32)0,(u32)TIMER_UNIT_NONE);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	ret = mdrv_timer_get_rest_time(TIMER_DSP_TIMER2_ID,TIMER_UNIT_NONE,&restTime);
	if(ret!=0)
	{
		(void)mdrv_timer_stop(TIMER_DSP_TIMER2_ID);
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_get_rest_time fail\n");
		return ERROR;
	}
	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"rest time = %d \n",restTime);
	osl_sem_down(&sem);/*lint !e40*/
	if(slice_delta[1]-slice_delta[0]>10006)
  	{
  		(void)mdrv_timer_stop(TIMER_DSP_TIMER2_ID);
  		hardtimer_print_error("slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_DSP_TIMER2_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}

s32 hardtimer_test_case03(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_CCPU_OSA_ID,func,0,1000,(u32)0,(u32)TIMER_UNIT_MS);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	if(slice_delta[1]-slice_delta[0]>32774)
  	{
  		(void)mdrv_timer_stop(TIMER_CCPU_OSA_ID);
  		hardtimer_print_error("slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_CCPU_OSA_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}
s32 hardtimer_test_case04(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_CCPU_DRX1_STABLE_ID,func,0,1000,(u32)0,(u32)TIMER_UNIT_MS);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	if(slice_delta[1]-slice_delta[0]>32774)
  	{
  		(void)mdrv_timer_stop(TIMER_CCPU_DRX1_STABLE_ID);
  		hardtimer_print_error("slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_CCPU_DRX1_STABLE_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}
s32 hardtimer_test_case05(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_DSP_TIMER1_ID,func,0,1000,(u32)0,(u32)TIMER_UNIT_MS);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	if(slice_delta[1]-slice_delta[0]>32774)
  	{
  		(void)mdrv_timer_stop(TIMER_DSP_TIMER1_ID);
  		hardtimer_print_error("slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_DSP_TIMER1_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}
s32 hardtimer_test_case06(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_CCPU_DRX_TIMER_ID,func,0,1000,(u32)0,(u32)TIMER_UNIT_MS);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	if(slice_delta[1]-slice_delta[0]>32774)
  	{
  		(void)mdrv_timer_stop(TIMER_CCPU_DRX_TIMER_ID);
  		hardtimer_print_error("slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_CCPU_DRX_TIMER_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}

s32 hardtimer_test_case07(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_DSP_SWITCH_DELAY_ID,func,0,1000,(u32)0,(u32)TIMER_UNIT_MS);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	if(slice_delta[1]-slice_delta[0]>32774)
  	{
  		(void)mdrv_timer_stop(TIMER_DSP_SWITCH_DELAY_ID);
  		hardtimer_print_error("slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_DSP_SWITCH_DELAY_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}

s32 hardtimer_test(void)
{
   s32 ret;
   ret = hardtimer_test_case01();
   if (OK == ret)
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case01 pass\n");
   else
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case01 fail\n");
   ret = hardtimer_test_case02();
   if (OK == ret)
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case02 pass\n");
   else
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case02 fail\n");
   ret = hardtimer_test_case03();
   if (OK == ret)
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case03 pass\n");
   else
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case03 fail\n");
   ret = hardtimer_test_case04();
   if (OK == ret)
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case04 pass\n");
   else
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case04 fail\n");
   ret = hardtimer_test_case05();
   if (OK == ret)
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case05 pass\n");
   else
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case05 fail\n");
   ret = hardtimer_test_case06();
   if (OK == ret)
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case06 pass\n");
   else
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case06 fail\n");
   ret = hardtimer_test_case07();
   if (OK == ret)
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case07 pass\n");
   else
   	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"hardtimer_test_case07 fail\n");
   return ret;

}
