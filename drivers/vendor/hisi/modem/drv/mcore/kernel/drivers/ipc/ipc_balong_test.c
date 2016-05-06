/*lint --e{537,718,732,746}*/
#include <bsp_ipc.h>
#include "printk.h"
#include <osl_irq.h>
#include <bsp_om.h>
#include "ipc_balong.h"
#include "cmsis_os.h"
u32 count_num[32] = {0};
void bsp_for_int_handler(u32 n)
{
	count_num[n]++;
	/*printk("count[%d] = %d : ", n,count_num[n]);*/
}

/********************************ST BEGIN****************************************/
s32 ipc_test_case01()
{
	s32 ret = 0;
	ret = bsp_ipc_int_connect(IPC_MCU_INT_SRC_TEST,bsp_for_int_handler,31);
	if(ret!=OK)
		return ERROR;
	ret = bsp_ipc_int_enable(IPC_MCU_INT_SRC_TEST);
	if(ret!=OK)
		return ERROR;
	return OK;
}
s32 ipc_test_case02()
{
	printk("count[31] = %d : ", count_num[31]);
	return OK;
}

s32 ipc_test_m_to_a()
{
	(void)bsp_ipc_int_send(IPC_CORE_ACORE,IPC_ACPU_INT_SRC_MCU_FOR_TEST);
	return OK;
}
s32 ipc_test_m_to_c()
{
	(void)bsp_ipc_int_send(IPC_CORE_CCORE, 31);
	return OK;
}
s32 ipc_test_spinlock()
{
	u32 ret = 0;
	unsigned long flags;
	local_irq_save(flags);
	ret = bsp_ipc_spin_lock(IPC_SEM1_IPC_TEST);/*复用此信号量，测试与a\c核争用*/
	if(ret != OK)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"[%s]:spinlock error\n",__FUNCTION__);
		local_irq_restore(flags);
		return ERROR;
	}
	(void)osDelay(5000);
	ret = bsp_ipc_spin_unlock(IPC_SEM1_IPC_TEST);
	if(ret != OK)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"[%s]:spinunlock error\n",__FUNCTION__);
		local_irq_restore(flags);
		return ERROR;
	}
	local_irq_restore(flags);
	return OK;
}

/********************************ST END****************************************/
