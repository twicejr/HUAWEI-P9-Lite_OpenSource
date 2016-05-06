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

/*lint --e{537,718,746,958,959}*/
#ifdef __KERNEL__
#include <linux/time.h>
#include <linux/delay.h>
#elif defined(__VXWORKS__)
#include <vxWorks.h>
#include <string.h>
#include <taskLib.h>
#include <tickLib.h>
#endif
#include <osl_spinlock.h>
#include <osl_module.h>
#include <bsp_om.h>
#include <bsp_ipc.h>
#include <bsp_shared_ddr.h>
#include <mdrv_sync.h>
#include <bsp_hardtimer.h>

#define SYNC_LOCK_ADDR           (SHM_BASE_ADDR+SHM_OFFSET_SYNC)
#define SYNC_STATE_ADDR         (SYNC_LOCK_ADDR + 0x30)
#ifdef __KERNEL__
#define SYNC_SLEEP(a) msleep(a*10)
#else
#define SYNC_SLEEP(a) taskDelay(a)
#endif
struct sync_control
{
	char *g_pSyncLock;
	char *g_pSyncState;
	spinlock_t lock;
};
	/*lint -save -e34 -e35*/

struct sync_control sync_ctrl;

static unsigned long  SyncSpinLock(void)
{
	unsigned long flag = 0;
	spin_lock_irqsave(&sync_ctrl.lock,flag);
	bsp_ipc_spin_lock(IPC_SEM_SYNC);
	return flag;
}

static void SyncSpinUnlock(unsigned long flag)
{
	bsp_ipc_spin_unlock(IPC_SEM_SYNC);
	spin_unlock_irqrestore(&sync_ctrl.lock,flag);
	return;
}

static void BSP_SYNC_Init(void)
{
    static int sync_init = false;
    if(!sync_init)
    {
        sync_ctrl.g_pSyncLock = (char*)SYNC_LOCK_ADDR;
	    sync_ctrl.g_pSyncState = (char*)SYNC_STATE_ADDR;
		spin_lock_init(&sync_ctrl.lock);
        sync_init = true;
    }
}
/*****************************************************************************
* 函 数 名 : BSP_SYNC_Lock
*
* 功能描述: 锁定并查询模块的初始化状态
*
* 输入参数: u32Module     模块
*                         pState        状态指针
*                         u32TimeOut    超时值，0为永远等待；
*
* 输出参数: 无
*
* 返 回 值   : OK&ERROR
*
* 其它说明: 无
*
*****************************************************************************/
s32 mdrv_sync_lock(SYNC_MODULE_E u32Module, u32 *pState, u32 u32TimeOut)
{
	unsigned long flag;
	u32 tick_end=0;
	u32 tick_begin=0;
	 BSP_SYNC_Init();
	if(!pState || (u32Module >= SYNC_MODULE_BUTT))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_Lock, invalid param,(butt =0x%x, module=0x%x )or *pState is null\n",(u32)SYNC_MODULE_BUTT ,u32Module);
		return BSP_ERROR;
	}
	tick_begin = bsp_get_slice_value();
	tick_end = tick_begin + HI_TIMER_STAMP_CLK*u32TimeOut/100;
	/* 目前只是在usrAppInit中使用，单任务情况下，使用循环查询效率较高
       如果需要支持多任务，需要适当的让出CPU */
	for(;;)
	{
		if(!sync_ctrl.g_pSyncLock[u32Module])
		{
			flag = SyncSpinLock();
			if(!sync_ctrl.g_pSyncLock[u32Module])
			{
				sync_ctrl.g_pSyncLock[u32Module] = 1;
				cache_sync();
				SyncSpinUnlock(flag);
				break;
			}
			else
			{
				SyncSpinUnlock(flag);
			}
		}
		if(u32TimeOut)
		{
			if(bsp_get_slice_value()>tick_end)
			{
				bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_Lock, timeout2, module=0x%x, u32TimeOut=0x%x\n", u32Module, u32TimeOut);
				return BSP_ERR_SYNC_TIMEOUT;
			}
		}
		SYNC_SLEEP(1);
	}
	/*lint -save -e571*/
	*pState = (u32)sync_ctrl.g_pSyncState[u32Module];
	/*lint -restore +e571*/
	return BSP_OK;
}


/*****************************************************************************
* 函 数 名      : BSP_SYNC_UnLock
*
* 功能描述  : 解锁并更新模块初始化状态
*
* 输入参数  : u32Module     模块
*                           u32State       更新模块状态
*
* 输出参数  : 无
*
* 返 回 值      : OK&ERROR
*
* 其它说明  : 无
*
*****************************************************************************/
s32 mdrv_sync_unlock(SYNC_MODULE_E u32Module, u32 u32State)
{
	 BSP_SYNC_Init();
	if(u32Module >= SYNC_MODULE_BUTT)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_UnLock, invalid param, module=0x%x\n", u32Module);
		return BSP_ERROR;
	}
	sync_ctrl.g_pSyncState[u32Module] = (char)u32State;
	sync_ctrl.g_pSyncLock[u32Module] = (char)0;
	return BSP_OK;
}
/*****************************************************************************
* 函 数 名     : BSP_SYNC_Wait
*
* 功能描述  : 从核等待主核操作完成函数
*
* 输入参数  : u32Module     模块
*                           u32TimeOut    超时值，0为永远等待；
*
* 输出参数  : 无
*
* 返 回 值      : OK&ERROR
*
* 其它说明  : 无
*
*****************************************************************************/
s32 mdrv_sync_wait(SYNC_MODULE_E u32Module, u32 u32TimeOut)
{
	u32 tick_begin = 0,tick_end = 0;
	 BSP_SYNC_Init();

	if(u32Module >= SYNC_MODULE_BUTT)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_UnLock, invalid param, module=0x%x\n", u32Module);
		return BSP_ERROR;
	}
	tick_begin = bsp_get_slice_value();
	tick_end = tick_begin + HI_TIMER_STAMP_CLK*u32TimeOut/100;
	for(;;)
	{
		if(sync_ctrl.g_pSyncState[u32Module])
		{
			return BSP_OK;
		}
		if(u32TimeOut)
		{
			if(bsp_get_slice_value()>tick_end)
			{
				bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_Wait, timeout, module=0x%x, u32TimeOut=0x%x\n", u32Module, u32TimeOut);
				return BSP_ERR_SYNC_TIMEOUT;
			}
		}
		SYNC_SLEEP(1);
	}
}
/*****************************************************************************
* 函 数 名     : BSP_SYNC_Give
*
* 功能描述  : 主核通知从核主核操作已经完成
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值     : OK&ERROR
*
* 其它说明  : 无
*
*****************************************************************************/
s32 mdrv_sync_give(SYNC_MODULE_E u32Module)
{
	 BSP_SYNC_Init();

	if(u32Module >= SYNC_MODULE_BUTT)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_Give, invalid param, module=0x%x\n", u32Module);
		return BSP_ERROR;
	}
	sync_ctrl.g_pSyncState[u32Module] = 1;
	cache_sync();
	return BSP_OK;
}
int bsp_sync_reset(SYNC_MODULE_E u32Module)
{
	BSP_SYNC_Init();
	if(u32Module >= SYNC_MODULE_BUTT)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"bsp_sync_reset, invalid param, module=0x%x\n", u32Module);
		return BSP_ERROR;
	}
	sync_ctrl.g_pSyncState[u32Module] = 0;
	cache_sync();
	return BSP_OK;
}

/*lint -restore +e34 +e35*/
/*lint -save -e19*/
EXPORT_SYMBOL(mdrv_sync_lock);
EXPORT_SYMBOL(mdrv_sync_unlock);
EXPORT_SYMBOL(mdrv_sync_wait);
EXPORT_SYMBOL(mdrv_sync_give);
EXPORT_SYMBOL(bsp_sync_reset);

/*lint -restore +e19*/


