/*lint --e{537,713,732,752,607}*/
#ifdef __KERNEL__
#include <linux/platform_device.h>
#include <soc_interrupts_app.h>

#elif defined(__OS_VXWORKS__)||defined(__OS_RTOSCK__)
#include <string.h>
#include <soc_interrupts_mdm.h>
#include <of.h>
//#include <bsp_uart.h>
#endif
#include <osl_module.h>
#include <bsp_memmap.h>
#include <bsp_om.h>
#include <bsp_ipc.h>
#include <bsp_hardtimer.h>
#include <bsp_dpm.h>
#include "ipc_balong.h"
#include <bsp_pm_om.h>
#include "securec.h"
#ifdef CONFIG_IPCM_USE_FPGA_VIC
#include <bsp_vic.h>
unsigned long g_p532_asic_ipcm_virt_addr = 0;
#define  ipc_print_err(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPC, ""fmt"", ##__VA_ARGS__))
#endif


#ifdef __cplusplus
extern "C" {
#endif
void bsp_ipc_debug_show(void);
extern s32 bsp_ipc_test_init(void);

#ifdef __KERNEL__
#define IPC_INT       INT_LVL_IPCM2APP0
#define IPC_SEM       INT_LVL_IPCM2APP1
#elif defined(__OS_VXWORKS__)||defined(__OS_RTOSCK__)
#define IPC_INT       INT_LVL_IPCM2MDM0
#define IPC_SEM       INT_LVL_IPCM2MDM1
#endif

static struct ipc_control		ipc_ctrl;
static struct ipc_debug_s		ipc_debug = {0};
#define IPC_CHECK_PARA(para,max) \
    do {\
        if (para >= max)\
        {\
            bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"[%s]Wrong para , line:%d,para = %d\n",__FUNCTION__, __LINE__,para); \
            return MDRV_ERROR; \
        } \
    } while (0)

s32 bsp_ipc_int_enable (IPC_INT_LEV_E ulLvl)
{
    u32 u32IntMask = 0;
    unsigned long flags=0;
    unsigned int n = ulLvl/INTSRC_NUM;

    IPC_CHECK_PARA(ulLvl,(INTSRC_NUM*IPCM_NUM));
    /*写中断屏蔽寄存器*/
    spin_lock_irqsave(&ipc_ctrl.lock,flags);
    u32IntMask = readl(ipc_ctrl.ipc_base[n] + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
    u32IntMask |= (u32)1 << (ulLvl%INTSRC_NUM);
    writel(u32IntMask,ipc_ctrl.ipc_base[n]+BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
    spin_unlock_irqrestore(&ipc_ctrl.lock,flags);
    return MDRV_OK;
}

s32 bsp_ipc_int_disable(IPC_INT_LEV_E ulLvl)
{
    u32 u32IntMask = 0;
    unsigned long flags=0;
    unsigned int n = ulLvl/INTSRC_NUM;

    IPC_CHECK_PARA(ulLvl,(INTSRC_NUM*IPCM_NUM));
    /*写中断屏蔽寄存器*/
    spin_lock_irqsave(&ipc_ctrl.lock,flags);
    u32IntMask = readl(ipc_ctrl.ipc_base[n] + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
    u32IntMask = u32IntMask & (~((u32)1 << (ulLvl%INTSRC_NUM)));
    writel(u32IntMask, ipc_ctrl.ipc_base[n] + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
    spin_unlock_irqrestore(&ipc_ctrl.lock,flags);
    return MDRV_OK;
}


s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter)
{
	 unsigned long flags=0;
	 IPC_CHECK_PARA(ulLvl,(INTSRC_NUM*IPCM_NUM));
	 spin_lock_irqsave(&ipc_ctrl.lock,flags);
	 ipc_ctrl.ipc_int_table[ulLvl].routine = routine;
	 ipc_ctrl.ipc_int_table[ulLvl].arg = parameter;
	 spin_unlock_irqrestore(&ipc_ctrl.lock,flags);
	 return MDRV_OK;
}


s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter)
{
	unsigned long flags = 0;
	IPC_CHECK_PARA(ulLvl,(INTSRC_NUM*IPCM_NUM));
	spin_lock_irqsave(&ipc_ctrl.lock,flags);
	ipc_ctrl.ipc_int_table[ulLvl].routine = NULL;
	ipc_ctrl.ipc_int_table[ulLvl].arg = 0;
	spin_unlock_irqrestore(&ipc_ctrl.lock,flags);
	return MDRV_OK;
 }

OSL_IRQ_FUNC(static irqreturn_t,ipc_int_handler,irq,arg)
{
	u32 i = 0;
	u32 u32IntStat = 0,begin = 0,end = 0;
	u32 u32Date = 0x1;
	u32 u32BitValue = 0;
	u32 n = (u32)(unsigned long)arg;

	u32IntStat=readl(ipc_ctrl.ipc_base[n] + BSP_IPC_CPU_INT_STAT(ipc_ctrl.core_num));
	/*清中断*/
	writel(u32IntStat,ipc_ctrl.ipc_base[n] + BSP_IPC_CPU_INT_CLR(ipc_ctrl.core_num));
	/* 遍历32个中断 */
	for (i = n*INTSRC_NUM; i < INTSRC_NUM*(n+1) ; i++)
	{
		if(n*INTSRC_NUM!=i)
		{
			u32Date <<= 1;
		}
		u32BitValue = u32IntStat & u32Date;
		/* 如果有中断 ,则调用对应中断处理函数 */
		if (0 != u32BitValue)
		{
			/*调用注册的中断处理函数*/
			if (NULL !=  ipc_ctrl.ipc_int_table[i].routine)
			{
				begin = bsp_get_slice_value();
				ipc_ctrl.last_int_cb_addr = (unsigned long)(ipc_ctrl.ipc_int_table[i].routine);
				ipc_ctrl.ipc_int_table[i].routine(ipc_ctrl.ipc_int_table[i].arg);
				end = bsp_get_slice_value();
				ipc_debug.u32IntTimeDelta[i] = get_timer_slice_delta(begin,end);
			}
			else
			{
				bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"BSP_DRV_IpcIntHandler:No IntConnect,MDRV_ERROR!.int num =%d\n",i);
			}
			ipc_debug.u32IntHandleTimes[i]++;
		}
	}
	return IRQ_HANDLED;
}


s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl)
{
	unsigned long flags = 0;
	unsigned int n = ulLvl/INTSRC_NUM;

	IPC_CHECK_PARA(ulLvl,(INTSRC_NUM*IPCM_NUM));
	IPC_CHECK_PARA(enDstCore,IPC_CORE_BUTTOM);
	/*写原始中断寄存器,产生中断*/
	spin_lock_irqsave(&ipc_ctrl.lock,flags);
#ifdef CONFIG_IPCM_USE_FPGA_VIC
    if (IPC_CORE_MCORE == enDstCore)
	{
	    writel((u32)1 << (ulLvl%INTSRC_NUM), g_p532_asic_ipcm_virt_addr + BSP_IPC_CPU_RAW_INT(enDstCore));
	}
	else
	{
		writel((u32)1 << (ulLvl%INTSRC_NUM),ipc_ctrl.ipc_base[n] + BSP_IPC_CPU_RAW_INT(enDstCore));
	}
#else
	writel((u32)1 << (ulLvl%INTSRC_NUM),ipc_ctrl.ipc_base[n] + BSP_IPC_CPU_RAW_INT(enDstCore));
#endif
	#ifdef CONFIG_P531_DRX_IPC
	switch(ulLvl)
	{
		case IPC_INT_DICC_RELDATA:
		case IPC_ACPU_INT_SRC_CCPU_MSG:
		case IPC_ACPU_INT_SRC_CCPU_NVIM:
		case IPC_INT_DICC_USRDATA:
		case IPC_ACPU_INT_SRC_CCPU_ICC:
		case IPC_ACPU_INT_SRC_ICC_PRIVATE:
		case IPC_ACPU_SRC_CCPU_DUMP:
			writel(1<<IPC_MCU_INT_SRC_CCPU_DRX,ipc_ctrl.ipc_base[n] + BSP_IPC_CPU_RAW_INT(IPC_CORE_MCORE));
			break;
		default:
			break;
	}
	#endif
	spin_unlock_irqrestore(&ipc_ctrl.lock,flags);
	ipc_debug.u32RecvIntCore = enDstCore;
	ipc_debug.u32IntSendTimes[enDstCore][ulLvl]++;
	return MDRV_OK;
}

static void  mask_int(u32 u32SignalNum)
{
	u32 u32IntMask = 0;
	unsigned long flags=0;
	spin_lock_irqsave(&ipc_ctrl.lock,flags);
	u32IntMask = readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_SEM_INT_MASK(ipc_ctrl.core_num));
	u32IntMask = u32IntMask & (~((u32)1 << u32SignalNum));
	writel(u32IntMask,ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_SEM_INT_MASK(ipc_ctrl.core_num));
	spin_unlock_irqrestore(&ipc_ctrl.lock,flags);
}

 s32 bsp_ipc_sem_create(u32 u32SignalNum)
 {
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
	if(true != ipc_ctrl.sem_exist[u32SignalNum])/*避免同一个信号量在没有删除的情况下创建多次*/
	{
		osl_sem_init(SEM_EMPTY,&(ipc_ctrl.sem_ipc_task[u32SignalNum]));
		ipc_ctrl.sem_exist[u32SignalNum] = true;
		return MDRV_OK;
	}
	else
	{
		return MDRV_OK;
	}

 }

 s32 bsp_ipc_sem_delete(u32 u32SignalNum)
 {
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
	if(false == ipc_ctrl.sem_exist[u32SignalNum] )
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"semphore not exists,may be deleted already.\n");
		return MDRV_ERROR;
	}
	else
	{
		if (osl_sema_delete(&(ipc_ctrl.sem_ipc_task[u32SignalNum])))
		{
			bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"Delete semphore failed.\n");
			return MDRV_ERROR;
		}
		ipc_ctrl.sem_exist[u32SignalNum] = false;
		return MDRV_OK;
	}
 }

 s32 bsp_ipc_sem_take(u32 u32SignalNum,s32 s32timeout)
 {
	u32 u32IntMask = 0,ret = 0;
	/*参数检查*/
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
	 /*将申请的信号量对应的释放中断清零*/
	writel((u32)1<<u32SignalNum, ipc_ctrl.ipc_base[IPCM_NS]+BSP_IPC_SEM_INT_CLR(ipc_ctrl.core_num));
	ret =  readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
	if(0 == ret)
	{
		mask_int(u32SignalNum);
		ipc_debug.u32SemTakeTimes[u32SignalNum]++;
		ipc_debug.u32SemId = u32SignalNum;
		return MDRV_OK;
	}
	else
	{
		if(false == ipc_ctrl.sem_exist[u32SignalNum])
		{
			bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"need call ipc_sem_create to create this sem before call ipc_sem_take!\n");
			return MDRV_ERROR;
		}
		if(0 != s32timeout)
		{
			/*使能信号量释放中断*/
			u32IntMask = readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_SEM_INT_MASK(ipc_ctrl.core_num));
			u32IntMask = u32IntMask | ((u32)1 << u32SignalNum);
			writel(u32IntMask,ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_SEM_INT_MASK(ipc_ctrl.core_num));
			if (MDRV_OK != osl_sem_downtimeout(&(ipc_ctrl.sem_ipc_task[u32SignalNum]), s32timeout))
			{
				mask_int(u32SignalNum);
				bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"semTake timeout!\n");
				ipc_debug.u32SemTakeFailTimes[u32SignalNum]++;
				return MDRV_ERROR;
			}
			else
            {  /*lint !e525*/
				mask_int(u32SignalNum);
				ipc_debug.u32SemTakeTimes[u32SignalNum]++;
				ipc_debug.u32SemId = u32SignalNum;
				return MDRV_OK;
			}
		}
		else
		{
			return MDRV_ERROR;
		}
	}

}


s32 bsp_ipc_sem_give(u32 u32SignalNum)
{
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
	ipc_debug.u32SemGiveTimes[u32SignalNum]++;
	/*向信号量请求寄存器写0*/
	writel(0,ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
	return MDRV_OK;
 }
 static s32 ffSLsb(s32 args)
 {
	 s32 num = 0;
	 s32 s32ImpVal = args;
	 if(0 == args)
	 {
	 	return 0;
     }  /*lint !e525*/
	 for(;;)
	 {
		 num++;
		 if (0x1 == (s32ImpVal & 0x1))
		 {
			 break;
		 }
		 s32ImpVal = (s32)((u32)s32ImpVal >> 1);
	 }
	 return num;
 }

 /*****************************************************************************
 * 函 数 名      : ipc_sem_int_handler
 *
 * 功能描述  : 信号量释放中断处理函数
 *
 * 输入参数  : 无
 * 输出参数  : 无
 *
 * 返 回 值      : 无
 *
 * 修改记录  :  2013年1月9日 lixiaojie
 *****************************************************************************/
OSL_IRQ_FUNC(static irqreturn_t,ipc_sem_int_handler,irq,arg)
{
	u32 u32IntStat = 0,u32HsCtrl=0,u32SNum=0, i = 32;
	u32IntStat = readl(ipc_ctrl.ipc_base[IPCM_NS]+BSP_IPC_SEM_INT_STAT(ipc_ctrl.core_num));
	u32SNum = ffSLsb(u32IntStat);
	if( u32SNum != 0)
	{
		do
		{
			 /*如果有信号量释放中断，清除该中断*/
			writel((u32)1<<--u32SNum, ipc_ctrl.ipc_base[IPCM_NS]+BSP_IPC_SEM_INT_CLR(ipc_ctrl.core_num));
			u32HsCtrl = readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SNum));
			if (0 == u32HsCtrl)
			{
				osl_sem_up(&(ipc_ctrl.sem_ipc_task[u32SNum]));
			}
			else
			{
				ipc_debug.u32SemTakeFailTimes[u32SNum]++;
			}
			u32IntStat = readl(ipc_ctrl.ipc_base[IPCM_NS]+BSP_IPC_SEM_INT_STAT(ipc_ctrl.core_num));
			u32SNum = ffSLsb(u32IntStat);
			i--;
		}while((u32SNum != 0) && (i  > 0));
	}
	else
	{
		return  IRQ_NONE;
	}
	return  IRQ_HANDLED;
}

s32 bsp_ipc_spin_lock(u32 u32SignalNum)
{
	u32 u32HsCtrl = 0;
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
	for(;;)
	{
		u32HsCtrl = readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
		if (0 == u32HsCtrl)
		{
			ipc_debug.u32SemTakeTimes[u32SignalNum]++;
			ipc_debug.u32SemId = u32SignalNum;
			break;
		}
	}
	return MDRV_OK;
}

s32 bsp_ipc_spin_lock_timeout(u32 u32SignalNum, u32 TimeoutMs)
{
	u32 u32HsCtrl = 0;
	u32 start_time = 0, end_time = 0, elapsed = 0;
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);

	start_time = bsp_get_slice_value();
	elapsed = TimeoutMs * bsp_get_slice_freq() / 1000; /*lint !e647 */

	/* coverity[no_escape] */
	for(;;)
	{
		u32HsCtrl = readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
		if (0 == u32HsCtrl)
		{
			ipc_debug.u32SemTakeTimes[u32SignalNum]++;
			ipc_debug.u32SemId = u32SignalNum;
			break;
		}

		end_time = bsp_get_slice_value();
		if(get_timer_slice_delta(start_time, end_time) > elapsed)
		{
			ipc_debug.u32SemCore = readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_STAT(ipc_ctrl.core_num, u32SignalNum));
			return MDRV_ERROR;
		}
	}
	return MDRV_OK;
}

s32 bsp_ipc_spin_lock_timeout_irqsave(unsigned int u32SignalNum, unsigned int TimeoutMs, unsigned long *flags)
{
	int ret = MDRV_OK;

	local_irq_save(*flags);
	ret = bsp_ipc_spin_lock_timeout(u32SignalNum, TimeoutMs);
	if(ret == MDRV_ERROR) {
		local_irq_restore(*flags);
		return ret;
	}
	return ret;
}

s32 bsp_ipc_spin_trylock(u32 u32SignalNum)
{
	u32 u32HsCtrl = 0;
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
	u32HsCtrl = readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
	if (0 == u32HsCtrl)
	{
		ipc_debug.u32SemTakeTimes[u32SignalNum]++;
		ipc_debug.u32SemId = u32SignalNum;
		return MDRV_OK;
	}
	else
		return MDRV_ERROR;
}

s32 bsp_ipc_spin_unlock (u32 u32SignalNum)
{
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
	writel(0,ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
	ipc_debug.u32SemGiveTimes[u32SignalNum]++;
	return MDRV_OK;
}

static s32 ipc_suspend_late(struct dpm_device *dev)
{
	u32 i = 0,ret = 0;
	for(i=0;i<32;i++)
	{
		ret = readl(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_STAT(ipc_ctrl.core_num,i));
		if(ret==0x9)
		{
			//printksync("ipc signum id = %d is occupied\n",i);
			return MDRV_ERROR;
		}
	}
	return MDRV_OK;
}

#ifdef CONFIG_PM_OM
extern void run_icc_pm_debug_callback(void);
extern void icc_wakeup_flag_set(void);
static unsigned int g_ipc_resume_int_stat = 0;
static int get_ipc_int_stat(struct dpm_device *dev)
{
	g_ipc_resume_int_stat = readl((unsigned int)(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_CPU_INT_STAT(ipc_ctrl.core_num)));
	if(g_ipc_resume_int_stat)
	{
		//bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"[C SR]ipc_resume_int_stat = 0x%x\n",ipc_resume_int_stat);
        (void)bsp_pm_log((unsigned int)PM_OM_CIPC, sizeof(g_ipc_resume_int_stat), (void *)&g_ipc_resume_int_stat);
		if(g_ipc_resume_int_stat & (((unsigned int)1) << IPC_CCPU_INT_SRC_ACPU_ICC))
		{
			icc_wakeup_flag_set();
			run_icc_pm_debug_callback();
		}
	}
	return 0;
}
#else
static inline int get_ipc_int_stat(struct dpm_device *dev){return 0;}
#endif


struct dpm_device ipc_dpm =
{
	.device_name = "ipc dpm",
	.suspend_late = ipc_suspend_late,
	.resume_early = get_ipc_int_stat,
};
u32 bsp_get_ipc_base_addr(void)
{
	return ipc_ctrl.ipc_base[IPCM_NS];
}

static void ipc_free_sem_taked(u32 core_id)
{
    u32 i = 0;
    u32 ret = 0;

    for(i = 0; i < 32; i++)
    {
        /*判断资源锁占用，如果占用，则释放*/
        ret = readl((unsigned long)(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_STAT(core_id, i)));
        ret &= 0xf;/*取低4bit*/
        if (ret == ((1 << 3) | core_id))
        {
            writel(0, (unsigned long)(ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_HS_CTRL(core_id, i)));
        }
    }
}

static void bsp_ipc_s_init(void)
{
    s32 ret = 0;
    struct device_node *node = NULL;
    const char *compatible_name = "hisilicon,ipc_balong_mdm_s";
    char *ret_of_iomap = NULL;
    u32  irq_no_ipc_int = 0;

    node = of_find_compatible_node(NULL, NULL, compatible_name);
    if (!node)
        return;

    ret_of_iomap = of_iomap(node, 0); 
    if (!ret_of_iomap) {
        bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ipc_s of_iomap fail\n");
        return;
    }

    (void)memset_s((void*)(ipc_ctrl.ipc_int_table+INTSRC_NUM), sizeof(struct ipc_entry) * INTSRC_NUM, 
                                           0x0, sizeof(struct ipc_entry) * INTSRC_NUM);
    ipc_ctrl.ipc_base[IPCM_S] = (u32)ret_of_iomap;
    writel(0x0,ipc_ctrl.ipc_base[IPCM_S] + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
    writel(0xffffffff,ipc_ctrl.ipc_base[IPCM_S] + BSP_IPC_CPU_INT_CLR(ipc_ctrl.core_num));

    irq_no_ipc_int = irq_of_parse_and_map(node, 0);
    ret = request_irq(irq_no_ipc_int,(irq_handler_t)ipc_int_handler, 0, "ipc_irq",(void*)IPCM_S);
    if (ret) {
        bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ipc_s int handler error,init failed\n");
        return;
    }

    bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ccore ipc_s init success\n");
    return;
}

void bsp_ipc_init(void)
{
	s32 ret = 0,i = 0;
    struct device_node *ptr_device_node = NULL;
	const char *compatible_name = "hisilicon,ipc_balong_mdm";
	char *ret_of_iomap = NULL;
	u32  irq_no_ipc_int = 0;
	u32  irq_no_ipc_sem = 0;
	
	ipc_ctrl.core_num = IPC_CORE_CCORE;
	for(i = 0;i< INTSRC_NUM;i++ )
	{
		ipc_ctrl.sem_exist[i] = false;
	}
	#ifdef CONFIG_CCORE_PM
	ret = bsp_device_pm_add(&ipc_dpm);
	if(ret)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ipc init fail\n");
		return;
	}
	#endif

    /* 读取基地址并映射 */
	ptr_device_node = of_find_compatible_node(NULL, NULL, compatible_name);
	if (!ptr_device_node)  /* 找不到节点 */
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ccore ipc of_find_compatible_node fail\n");
		return;
	}

    ret_of_iomap = of_iomap(ptr_device_node, 0); 
	if (!ret_of_iomap)  /* 映射错误 */
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"of_iomap fail\n");
		return;
	}

#ifdef CONFIG_IPCM_USE_FPGA_VIC
    g_p532_asic_ipcm_virt_addr = (unsigned long)ret_of_iomap;

	/* 读取基地址并映射 */
	ptr_device_node = of_find_compatible_node(NULL, NULL, "hisilicon,ipc_balong_mdm_fpga");
	if (!ptr_device_node)  /* 找不到节点 */
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ccore ipc of_find_compatible_node fail\n");
		return;
	}

	ret_of_iomap = of_iomap(ptr_device_node, 0); 
	if (!ret_of_iomap)	/* 映射错误 */
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"of_iomap fail\n");
		return;
	}

#endif
	
	(void)memset_s((void*)(ipc_ctrl.ipc_int_table), sizeof(struct ipc_entry) * INTSRC_NUM, 
		                                   0x0, sizeof(struct ipc_entry) * INTSRC_NUM);
	ipc_ctrl.ipc_base[IPCM_NS] = (u32)ret_of_iomap; //HI_IPCM_REGBASE_ADDR_VIRT
	writel(0x0,ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
	writel(0x0,ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_SEM_INT_MASK(ipc_ctrl.core_num));
	writel(0xffffffff,ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_CPU_INT_CLR(ipc_ctrl.core_num));/*清所有32个中断*/
	writel(0xffffffff,ipc_ctrl.ipc_base[IPCM_NS] + BSP_IPC_SEM_INT_CLR(ipc_ctrl.core_num));/*清所有32个中断*/
	ipc_free_sem_taked((u32)IPC_CORE_CCORE);
	ipc_free_sem_taked((u32)IPC_CORE_LDSP);
	spin_lock_init(&ipc_ctrl.lock);
#ifdef CONFIG_IPCM_USE_FPGA_VIC
	/* 获取中断号 */
	irq_no_ipc_int = irq_of_parse_and_map(ptr_device_node, 0);
	ret = bsp_vic_connect(irq_no_ipc_int, (vicfuncptr)ipc_int_handler, 0);
	ret |= bsp_vic_enable(irq_no_ipc_int);
	if (ret )
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ipc int handler error,init failed\n");
		return;
	}

	/* 获取中断号 */
	irq_no_ipc_sem = irq_of_parse_and_map(ptr_device_node, 1);
	ret = bsp_vic_connect(irq_no_ipc_sem, (vicfuncptr)ipc_sem_int_handler, 0);
	ret |= bsp_vic_enable(irq_no_ipc_sem);
	if (ret )
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ipc sem handler error,init failed\n");
		return;
	}

#else
    /* 获取中断号 */
	irq_no_ipc_int = irq_of_parse_and_map(ptr_device_node, 0);
	ret = request_irq(irq_no_ipc_int,(irq_handler_t) ipc_int_handler, 0, "ipc_irq",(void*)IPCM_NS);  //IPC_INT
	if (ret )
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ipc int handler error,init failed\n");
		return;
	}

    /* 获取中断号 */
	irq_no_ipc_sem = irq_of_parse_and_map(ptr_device_node, 1);
	ret = request_irq(irq_no_ipc_sem, (irq_handler_t) ipc_sem_int_handler, 0, "ipc_sem",(void*) NULL);  //IPC_SEM
	if (ret )
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ipc sem handler error,init failed\n");
		return;
	}
#endif
	
	#ifdef ENABLE_TEST_CODE
	ret = bsp_ipc_test_init();
	if (ret )
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"bsp_ipc_test_init failed\n");
		return;
	}
	#endif
	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"ccore ipc_ns init success\n");
	bsp_ipc_s_init();
	return;
}


void bsp_ipc_debug_show(void)
{
	u32 i = 0;
	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"\ncurrent sem ID       : \t%d\n", ipc_debug.u32SemId);
	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"\ncurrent sem core     : \t%d\n", ipc_debug.u32SemCore);
	bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"current recv int coreid: \t%d\n", ipc_debug.u32RecvIntCore);
	for(i = 0; i < INTSRC_NUM; i++)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"sem%2d take count      : \t%d\n", i,ipc_debug.u32SemTakeTimes[i]);
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"sem%2d give count      : \t%d\n", i,ipc_debug.u32SemGiveTimes[i]);
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"int%2d recv count      : \t%d\n",i, ipc_debug.u32IntHandleTimes[i]);
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"int%2d cost time       : \t%d us\n",i, ipc_debug.u32IntTimeDelta[i]*1000000/HI_TCXO_CLK);
	}
}

void bsp_int_send_info(void)
{
	u32 i = 0,j = 0;
	for(i = 0;i <IPC_CORE_BUTTOM;i++)
	{
		for(j=0;j<IPC_INT_BUTTOM;j++)
		{
			bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_IPC,"int%2d send to core%d count: \t%d\n",j,i, ipc_debug.u32IntSendTimes[i][j]);
		}
	}

}

#ifdef __cplusplus
}
#endif
