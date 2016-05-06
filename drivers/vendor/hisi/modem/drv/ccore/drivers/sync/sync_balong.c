/*************************************************************************
*   版权所有(C) 1987-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  BSP_SYNC.c
*
*   作    者     :  lixiaojie
*
*   描    述     :  本文件基于IFC模块实现，用于管理模块主从核同步操作，
					 为上层适配V7R1版本接口。
*
*   修改记录 :  2010年4月2日  v1.00  wangxuesong  创建
				2013年5月6日  v2.00  lixiaojie  修改
*************************************************************************/
#include <osl_spinlock.h>
#include <osl_module.h>
#include <osl_thread.h>
#include <bsp_om.h>
#include <bsp_ipc.h>
#include <bsp_shared_ddr.h>
#include <mdrv_sync.h>
#include <bsp_hardtimer.h>

#define SYNC_LOCK_ADDR           ((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_SYNC)
#define SYNC_STATE_ADDR         (SYNC_LOCK_ADDR + 0x30)
#define SYNC_SLEEP(a) osl_task_delay(a)

struct sync_control
{
	char *g_pSyncLock;
	char *g_pSyncState;
	spinlock_t lock;
};

struct sync_control sync_ctrl;

static unsigned long  SyncSpinLock(void)
{
	unsigned long flag = 0;
	spin_lock_irqsave(&sync_ctrl.lock,flag);
	(void)bsp_ipc_spin_lock(IPC_SEM_SYNC);
	return flag;
}

static void SyncSpinUnlock(unsigned long flag)
{
	(void)bsp_ipc_spin_unlock(IPC_SEM_SYNC);
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
/*lint -save -e574*/

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
int mdrv_sync_lock(SYNC_MODULE_E u32Module, unsigned int *pState, unsigned int u32TimeOut)
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
		(void)SYNC_SLEEP(1);
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
int mdrv_sync_unlock(SYNC_MODULE_E u32Module, unsigned int u32State)
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
int mdrv_sync_wait(SYNC_MODULE_E u32Module, unsigned int u32TimeOut)
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
		(void)SYNC_SLEEP(1);
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
int mdrv_sync_give(SYNC_MODULE_E u32Module)
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

/*lint -restore +e574*/

