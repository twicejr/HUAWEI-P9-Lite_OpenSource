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

#include <bsp_dump.h>
#include <icc_core.h>

extern struct icc_control g_icc_ctrl;

void icc_restore_recv_channel_flag(struct icc_channel_fifo * channel_fifo)
{
	/* nothing to do */

	return;
}


s32 icc_channel_has_data(void)
{
	/*lint --e{53, 58, 56 } */
	s32 i = 0;
	u32 read  = 0;
	u32 write = 0;
	struct icc_channel_fifo *fifo = NULL;
	struct icc_channel_packet packet = {0};

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
			icc_print_error("%s[channel-%d] stop suspend flow\n", g_icc_ctrl.channels[i]->name, i);
			if (ICC_CHN_IFC == i || ICC_CHN_MCORE_ACORE == i || ICC_CHN_MCORE_CCORE ==i)
			{
				while(read < write)
				{
					if(fifo_get(fifo, (u8 *)&packet, sizeof(packet), &read) != sizeof(packet))
					{
						break;
					}
					icc_sleep_flag_set();
					if (icc_channel_packet_dump(&packet) != ICC_OK)
					{
						break;
					}
					read = (read + packet.len);
					read = (read >= fifo->size)? (read - fifo->size): (read);
				}
			}
			wake_lock(&g_icc_ctrl.wake_lock);
			osl_sem_up(&g_icc_ctrl.shared_task_sem);
			return ICC_BUSY;
		}
	}

	return ICC_OK;
}

void icc_shared_sem_init(void)
{
    osl_sem_init(ICC_SEM_FULL, &g_icc_ctrl.shared_task_sem);
}

void icc_private_sem_init(osl_sem_id *private_sem)
{
    osl_sem_init(ICC_SEM_FULL, private_sem);
}

int icc_shared_task_init(void)
{
    return osl_task_init("icc_shared", ICC_TASK_SHARED_PRI, ICC_TASK_STK_SIZE ,(void *)icc_task_shared_func, NULL,
		(void*)&g_icc_ctrl.shared_task_id);
}

	
void icc_system_error(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
    system_error(mod_id, arg1, arg2, data, length);
}

int icc_pm_notify(struct notifier_block *nb, unsigned long event, void *dummy)
{
	if (event == PM_SUSPEND_PREPARE)
	{
		return icc_channel_has_data();
	}

	return ICC_OK;
}

static void icc_pm_notify_init(void)
{
	memset(&g_icc_ctrl.pm_notify, 0, sizeof(g_icc_ctrl.pm_notify));
	g_icc_ctrl.pm_notify.notifier_call = icc_pm_notify;
	register_pm_notifier(&g_icc_ctrl.pm_notify);
}

void icc_wake_lock_init(struct wake_lock *lock, int lock_id, const char *name)
{
    wake_lock_init(lock, lock_id, name);
}
void icc_wake_lock(struct wake_lock *lock)
{
    wake_lock(lock);
}
void icc_wake_unlock(struct wake_lock *lock)
{
    wake_unlock(lock);
}

extern s32 bsp_reset_ccpu_status_get(void);

int icc_ccore_is_reseting(u32 cpuid)
{
	if ((0 == bsp_reset_ccpu_status_get()) && (ICC_CPU_MODEM == cpuid))
	{
		return 1;
	}

	return ICC_OK;
}

s32 bsp_icc_channel_reset(DRV_RESET_CB_MOMENT_E stage, int usrdata)
{
		struct icc_channel *channel = NULL;
		u32 i = 0;
		if(MDRV_RESET_RESETTING == stage)
		{
			for (i = ICC_CHN_ACORE_CCORE_MIN; i < ICC_CHN_ACORE_CCORE_MAX; i++)
			{
				channel = g_icc_ctrl.channels[i];
				if(NULL == channel)
				{
					continue;
				}
				channel->fifo_send->read  = 0;
				channel->fifo_send->write = 0;
			}
		}
		return ICC_OK;
}

void bsp_icc_channel_uninit(u32 real_channel_id)
{
	struct icc_channel *channel = NULL;

	channel = g_icc_ctrl.channels[real_channel_id];


	if((!channel->mode.union_stru.task_shared) && (!channel->mode.union_stru.no_task))
	{

		kthread_stop(channel->private_task_id);
		(void)osl_sema_delete(&channel->private_task_sem);
	}

	if(!channel->mode.union_stru.ipc_shared)
	{
        (void)bsp_ipc_int_disable((IPC_INT_LEV_E)channel->ipc_recv_irq_id);
        (void)bsp_ipc_int_disconnect((IPC_INT_LEV_E)channel->ipc_recv_irq_id, (voidfuncptr)icc_ipc_isr, channel->id);
	}

	icc_safe_free(channel->vector);
	(void)memset_s(channel->fifo_send, sizeof(struct icc_channel_fifo) + channel->fifo_send->size,/* [false alarm]:fortify */
		0, sizeof(struct icc_channel_fifo) + channel->fifo_send->size); /*lint !e665 */
	icc_safe_free(channel);

}

void icc_wakeup_flag_set(void)
{
	g_icc_ctrl.wake_up_flag = 1;
}

void icc_sleep_flag_set(void)
{
	g_icc_ctrl.sleep_flag = 1;
}

u32 bsp_icc_channel_status_get(u32 real_channel_id, u32 *channel_stat)
{
	struct icc_channel* channel = g_icc_ctrl.channels[real_channel_id];

	if(NULL == channel)
	{
		*channel_stat = ICC_CHN_CLOSED;
		return *channel_stat;
	}

	*channel_stat = channel->state;
	return *channel_stat;

}

int icc_pm_init(void)
{
	(void)icc_pm_notify_init();
	return ICC_OK;
}

EXPORT_SYMBOL(bsp_icc_channel_status_get);
