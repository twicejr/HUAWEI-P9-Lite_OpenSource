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

/*lint --e{438,537}*/
#include <bsp_hardtimer.h>
#include <osl_sem.h>
#include <bsp_om.h>

s32 hardtimer_test_case01(void);
s32 hardtimer_test_case02(void);
s32 hardtimer_test_case03(void);
s32 hardtimer_test_case04(void);
s32 hardtimer_test_case05(void);
s32 hardtimer_test_case06(void);
s32 hardtimer_test_case07(void);
s32 hardtimer_test_case08(void);

void hardtimer_test(void);
void print_count(void);

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

struct bsp_hardtimer_control my_timer;
osl_sem_id sem;/*lint !e129*//*lint !e19*/
u32 cnt = 0;
u32 slice_delta[6];

void print_count(void)
{
   bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"cnt = %d\n",cnt);
   return;
}


int func(int para)
{
	osl_sem_up(&sem);/*lint !e129*//*lint !e40*/
	slice_delta[1]=bsp_get_slice_value();
	(void)mdrv_timer_stop(TIMER_ACPU_OSA_ID);
	return 0;
}
/*测试超时时间为1秒，TIMER_UNIT_NONE,能否准确超时*/

s32 hardtimer_test_case01(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_ACPU_OSA_ID,func,0,32768,0,TIMER_UNIT_NONE);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	/*1s定时误差控制在18个slice，大于则认为有错*/
	if((slice_delta[1]-slice_delta[0]>32786)||(slice_delta[1]-slice_delta[0]<32763))
  	{
  		(void)mdrv_timer_stop(TIMER_ACPU_OSA_ID);
  		hardtimer_print_error("error:slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_ACPU_OSA_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_stop fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}
/*测试超时时间为100毫秒，TIMER_UNIT_US,能否准确超时*/
s32 hardtimer_test_case02(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_ACPU_OSA_ID,func,0,100000,0,TIMER_UNIT_US);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	/*linux 响应中断慢,定时误差控制在18个slice，大于则认为有错*/
	if((slice_delta[1]-slice_delta[0]>3294)||(slice_delta[1]-slice_delta[0]<3271))
  	{
  		(void)mdrv_timer_stop(TIMER_ACPU_OSA_ID);
  		hardtimer_print_error("error:slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_ACPU_OSA_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}

/*测试超时时间为1S，TIMER_UNIT_MS,能否准确超时*/
s32 hardtimer_test_case03(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_ACPU_OSA_ID,func,0,1000,0,TIMER_UNIT_MS);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	/*linux 响应中断慢,定时误差控制在18个slice，大于则认为有错*/
	if((slice_delta[1]-slice_delta[0]>32786)||(slice_delta[1]-slice_delta[0]<32763))
  	{
  		(void)mdrv_timer_stop(TIMER_ACPU_OSA_ID);
  		hardtimer_print_error("error:slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_ACPU_OSA_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}
/*测试超时时间为0秒，TIMER_UNIT_NONE,能否准确超时*/

s32 hardtimer_test_case04(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_ACPU_OSA_ID,func,0,0,0,TIMER_UNIT_NONE);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	/*1s定时误差控制在21个slice，大于则认为有错*/
	if(slice_delta[1]-slice_delta[0]>21)
  	{
  		(void)mdrv_timer_stop(TIMER_ACPU_OSA_ID);
  		hardtimer_print_error("error:slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_ACPU_OSA_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}
/*测试超时时间为0秒，TIMER_UNIT_US,能否准确超时*/
s32 hardtimer_test_case05(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_ACPU_OSA_ID,func,0,0,0,TIMER_UNIT_US);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	/*1s定时误差控制在21个slice，大于则认为有错*/
	if(slice_delta[1]-slice_delta[0]>21)
  	{
  		(void)mdrv_timer_stop(TIMER_ACPU_OSA_ID);
  		hardtimer_print_error("error:slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_ACPU_OSA_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}

/*测试超时时间为0S，TIMER_UNIT_MS,能否准确超时*/
s32 hardtimer_test_case06(void)
{
	s32 ret = 0;
	osl_sem_init(SEM_EMPTY,&sem);/*lint !e40*/
	ret = mdrv_timer_start(TIMER_ACPU_OSA_ID,func,0,0,0,TIMER_UNIT_MS);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	/*定时误差控制在21个slice，大于则认为有错*/
	if(slice_delta[1]-slice_delta[0]>21)
  	{
  		(void)mdrv_timer_stop(TIMER_ACPU_OSA_ID);
  		hardtimer_print_error("error:slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_ACPU_OSA_ID);
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
	ret = mdrv_timer_start(TIMER_ACPU_OM_TCXO_ID,func,0,1000,0,TIMER_UNIT_MS);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	slice_delta[0]=bsp_get_slice_value();
	osl_sem_down(&sem);/*lint !e40*/
	/*linux 响应中断慢,定时误差控制在16个slice，大于则认为有错*/
	if((slice_delta[1]-slice_delta[0]>32785)||(slice_delta[1]-slice_delta[0]<32764))
  	{
  		(void)mdrv_timer_stop(TIMER_ACPU_OM_TCXO_ID);
  		hardtimer_print_error("error:slice_delta[1] = %d   slice_delta[0] = %d\n",slice_delta[1] ,slice_delta[0] );
		return ERROR;
  	}
	ret = mdrv_timer_stop(TIMER_ACPU_OM_TCXO_ID);
	if(ret!=0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HARDTIMER,"mdrv_timer_start fail\n");
		return ERROR;
	}
	osl_sema_delete(&sem);/*lint !e40*/
	return OK;
}

void hardtimer_test(void)
{
	s32 ret = 0;
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
	return ;
}

