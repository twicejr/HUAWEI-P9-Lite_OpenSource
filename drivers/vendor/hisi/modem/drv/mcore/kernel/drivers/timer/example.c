
/*本示例创建两个定时器，定时器id1为只执行一次，
 *定时器id2为周期性循环执行*/

#include "cmsis_os.h"
#include "printk.h"
#include <osl_types.h>
int countNum = 0,countNum1=0;
osSemaphoreId      test_sem;    
osSemaphoreDef(test_sem);


/****************************************************
 *        1、定义回调函数参数                            *
 ****************************************************/
u32 args1;                                               /*Timer1 回调参数              */
u32 args2;                                               /*Timer2 回调参数              */


/****************************************************
 *        2、定义回调函数                                       *
 ****************************************************/
void Timer1_callback(void const *args)
{
	countNum1++;
}
void Timer2_callback(void const *args)
{
	countNum++;
	if(countNum==10)
		osSemaphoreRelease(test_sem);
}

/****************************************************
 *        3、定义Timer的属性                                    *
 ****************************************************/

osTimerDef (Timer1,Timer1_callback);
osTimerDef (Timer2,Timer2_callback);
osTimerId Timer1;                                        /*创建两个定时器，一个id1为超时一次，id2为循环执行*/
osTimerId Timer2;

/***********************************************************
 *        4、创建Timer的函数，使用时可根据需要*
 *                在具体功能函数中进行创建                  *
 ************************************************************/                              
int TimerCreate_example(void)
{	
	u32 Timer1Delay = 5000;                           /*Timer1超时时间为5秒   */
	u32 Timer2Delay = 10000;                         /*Timer2超时时间为10秒  */
	osStatus status;
	args1=1;
	Timer1 = osTimerCreate(osTimer(Timer1),osTimerOnce,&args1);
	if(Timer1 )
	{
		status= osTimerStart(Timer1,Timer1Delay);                        
		if(status!=osOK)
		{
			printk("Timer1 start fail,status = 0x%x\n",status);
		}
	}
	else
	{
		printk("Timer1 create fail,status = 0x%x\n",Timer1);
		return -1;
	}
	args2=2;
	Timer2 = osTimerCreate(osTimer(Timer2),osTimerPeriodic,&args2);
	if(Timer2)
	{
		
		status= osTimerStart(Timer2,Timer2Delay);                       
		if(status!=osOK)
		{
			printk("Timer2 start fail,status = 0x%x\n",status);
		}
	}
	else
	{
		printk("Timer2 create fail,status = 0x%x\n",Timer2);
		return -1;
	}
	test_sem=osSemaphoreCreate(osSemaphore(test_sem),1);/*创建信号量，控制定时器2执行次数*/
	osSemaphoreWait(test_sem, osWaitForever);
	osSemaphoreWait(test_sem, osWaitForever);
	status = osTimerStop(Timer2);                                          /*停止定时器,并没有删除，还可以继续start*/
	if(status!=osOK)
	{
		printk("Timer2 stop fail\n");
	}
	/*如果想停止并删除一个timer，可以调用
	   status = osTimerDelete(timerId)
	   if(status!=osOK) {..........}*/
	printk("countNum1=%d, countNum=%d\n",countNum1,countNum);
	status = osTimerDelete(Timer1);
	if(status!=osOK)
	{
		printk("Timer1 delete fail,status = 0x%x\n",status);
	}
	status = osTimerDelete(Timer2);
	if(status!=osOK)
	{
		printk("Timer2 delete fail,status = 0x%x\n",status);
	}
	return 0;
}
