/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  icc_rtx.c
*
*   作    者 :  h00277960
*
*   描    述 :  icc rtx相关
*
*   修改记录 :
*      1> 2015年04月20日  v1.00  h00277960  创建
*************************************************************************/
#include <icc_core.h>

extern struct icc_control g_icc_ctrl;

osSemaphoreDef(shared_task_sem);
osSemaphoreDef(private_task_sem);

osThreadDef(icc_task_shared_func, ICC_TASK_SHARED_PRI, 1, ICC_TASK_STK_SIZE);

void icc_restore_recv_channel_flag(struct icc_channel_fifo * channel_fifo)
{
	if (MODEM_ALREADY_INIT_MAGIC == get_modem_init_flag())
	{
		if(ICC_CHN_MAGIC_UNSIGN == channel_fifo->magic)
		{
			channel_fifo->magic = ICC_CHN_MAGIC_SIGN;
		}
	}
	return;
}

s32 icc_channel_has_data(void)
{
	/*lint --e{53, 58, 56 } */
	s32 i = 0;
	u32 read  = 0;
	u32 write = 0;
	struct icc_channel_fifo *fifo = NULL;

	for(i = 0; i < (int)ICC_CHN_ID_MAX; i++)
	{
		
		if(NULL == g_icc_ctrl.channels[i])
		{
			continue;
		}
		fifo = g_icc_ctrl.channels[i]->fifo_recv;
		read  = fifo->read;
		write = fifo->write;
		if(read != write) /* has data to be handled */
		{
			icc_print_error("%s[chan:%d] stop suspend\n", g_icc_ctrl.channels[i]->name, i);
			icc_wake_lock(&g_icc_ctrl.wake_lock);
			osl_sem_up(&g_icc_ctrl.shared_task_sem);
			return ICC_BUSY;
		}
	}

	return ICC_OK;
}


s32 bsp_icc_suspend(void)
{
	return icc_channel_has_data();
}

void icc_shared_sem_init(void)
{
    g_icc_ctrl.shared_task_sem = osl_sem_init(ICC_SEM_FULL, shared_task_sem);
}

/* 与mcore之间的通信暂支持一个私有任务，acore与ccore之间没有限制 */
void icc_private_sem_init(osl_sem_id *sem)
{
    *sem = osl_sem_init(ICC_SEM_FULL, private_task_sem);
}

int icc_shared_task_init(void)
{
	g_icc_ctrl.shared_task_id = osThreadCreate(osThread(icc_task_shared_func), (void*)NULL);
	if(NULL == g_icc_ctrl.shared_task_id)
	{
		return ICC_ERR;
	}

	return ICC_OK;
}

