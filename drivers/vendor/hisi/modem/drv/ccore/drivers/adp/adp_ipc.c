/*lint --e{537}*/


#include <mdrv_ipc.h>
#include <bsp_ipc.h>
#include <osl_bio.h>
#include <osl_irq.h>
#include <bsp_memmap.h>
/*lint -save -e18*/
/*lint -save -e532*/


int mdrv_ipc_sem_create (unsigned int u32SignalNum)
{
	return bsp_ipc_sem_create(u32SignalNum);
}

int mdrv_ipc_sem_delete(unsigned int u32SignalNum)
{
	return bsp_ipc_sem_delete(u32SignalNum);
}

int mdrv_ipc_int_enable (IPC_INT_LEV_E ulLvl)
{
	return bsp_ipc_int_enable(ulLvl);
}

int mdrv_ipc_int_disable (IPC_INT_LEV_E ulLvl)
{
	return bsp_ipc_int_disable(ulLvl);
}

int mdrv_ipc_int_connect (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter)
{
	return bsp_ipc_int_connect(ulLvl,(voidfuncptr)routine,parameter);
}

int mdrv_ipc_int_disconnect (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter)
{
	return bsp_ipc_int_disconnect(ulLvl,(voidfuncptr)routine,parameter);
}

int mdrv_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl)
{
	return bsp_ipc_int_send(enDstCore, ulLvl);
}

int mdrv_ipc_sem_take (unsigned int u32SignalNum,int s32timeout)
{
	return bsp_ipc_sem_take(u32SignalNum,s32timeout);
}

int mdrv_ipc_sem_give(unsigned int u32SignalNum)
{
	return bsp_ipc_sem_give(u32SignalNum);
}

void mdrv_ipc_spin_lock(unsigned int u32SignalNum)
{
	(void)bsp_ipc_spin_lock (u32SignalNum);
 	return;
}

int mdrv_ipc_spin_trylock(unsigned int u32SignalNum)
{
	return bsp_ipc_spin_trylock (u32SignalNum);
}

void mdrv_ipc_spin_unlock(unsigned int u32SignalNum)
{
	(void)bsp_ipc_spin_unlock (u32SignalNum);
	return;
}


/*lint -restore +e18*/
/*lint -restore +e532*/

