#include "ipc_balong.h"
#include <bsp_memmap.h>
#include <osl_common.h>/*lint !e537*/
#include <m3_modem.h>/*lint !e537*/
#include <bsp_om.h>
#include <hwspinlock.h>
//#include <ipc_center.h>
#include <bsp_reset.h>
#ifdef __cplusplus
extern "C" {
#endif
/*lint --e{452,732} */

__ao_data static struct ipc_control    ipc_ctrl;

#ifdef IPC_DEBUG_FEATURE
__ao_data static struct ipc_debug_s    ipc_debug = {0};
#endif
//#define AP_TO_LPM3_IPC_FLAG (OBJ_AP<<24|OBJ_MODEM<<16|CMD_SETTING<<8|TYPE_MODEM)

__ao_data static u32 ipc_bak_addr[BAK_REG_NUM]={0};
__ao_data static u32 ipc_ccore_int_reset_flag=0;
__ao_data static u8  ipc_modem_reset_flag = 0;
#define ipc_bsp_trace(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPC, "[ipc]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
/*lint -save -e568*//*lint -save -e685*/
#define IPC_CHECK_PARA(para,max) \
    do {\
        if ((para >= max))\
        {\
            return ERROR; \
        } \
    } while (0)

s32 bsp_ipc_int_enable (IPC_INT_LEV_E ulLvl)
{
	u32 u32IntMask = 0,flags=0;
	IPC_CHECK_PARA(ulLvl,IPC_INT_BUTTOM);
	/*写中断屏蔽寄存器*/
	local_irq_save(flags);
	u32IntMask = readl(ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
	u32IntMask |= (u32)1 << (u32)ulLvl;
	writel(u32IntMask,ipc_ctrl.ipc_base+BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
	local_irq_restore(flags);
	return OK;
}

s32 bsp_ipc_int_disable(IPC_INT_LEV_E ulLvl)
{
	u32 u32IntMask = 0,flags=0;
	IPC_CHECK_PARA(ulLvl,IPC_INT_BUTTOM);
	/*写中断屏蔽寄存器*/
	local_irq_save(flags);
	u32IntMask = readl(ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
	u32IntMask = u32IntMask & (~((u32)1 << (u32)ulLvl));
	writel(u32IntMask, ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
	local_irq_restore(flags);
	return OK;
}


s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter)
{
	unsigned int flags;
	 IPC_CHECK_PARA(ulLvl,IPC_INT_BUTTOM);
	 local_irq_save(flags);
	 ipc_ctrl.ipc_int_table[ulLvl].routine = routine;
	 ipc_ctrl.ipc_int_table[ulLvl].arg = parameter;
	 local_irq_restore(flags);
	 return OK;
}

 
s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter)
{
	unsigned int flags;
	IPC_CHECK_PARA(ulLvl,IPC_INT_BUTTOM);
	local_irq_save(flags);
	ipc_ctrl.ipc_int_table[ulLvl].routine = NULL;
	ipc_ctrl.ipc_int_table[ulLvl].arg = 0;
	local_irq_restore(flags);
	return OK;
 }

void ipc_int_handler(void)
{
    u32 i = 0,u32IntStat = 0,u32Date = 0x1,u32BitValue = 0;
    u32IntStat=readl(ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_STAT(ipc_ctrl.core_num));
    /*清中断*/
    writel(u32IntStat,ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_CLR(ipc_ctrl.core_num));
    /* 遍历32个中断 */
    for (i = 0; i < INTSRC_NUM; i++)
    {   
        if (0 != i)              
        {      
            u32Date <<= (u32)1;              
        }   
        u32BitValue = u32IntStat & u32Date;		
        /* 如果有中断 ,则调用对应中断处理函数 */
        if (0 != u32BitValue)
        {  
            /*调用注册的中断处理函数*/
            if (NULL !=  ipc_ctrl.ipc_int_table[i].routine)
            {
                ipc_ctrl.ipc_int_table[i].routine(ipc_ctrl.ipc_int_table[i].arg);
            }
            else
            {
                ipc_bsp_trace(" cb num.int no =%d\n",i);
            }
	    #ifdef IPC_DEBUG_FEATURE
            ipc_debug.u32IntHandleTimes[i]++;
	    #endif
        }
    }
}


s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl)
{
	unsigned int flags=0;
	IPC_CHECK_PARA(ulLvl,IPC_INT_BUTTOM);
	IPC_CHECK_PARA(enDstCore,IPC_CORE_BUTTOM);
	if(ipc_modem_reset_flag) /* 核间信息不可以交互 */
	{
		return IPC_ERR_MODEM_RESETING;
	}
	/*写原始中断寄存器,产生中断*/
	local_irq_save(flags);
	writel((u32)1 << (u32)ulLvl,ipc_ctrl.ipc_base + BSP_IPC_CPU_RAW_INT(enDstCore));
	local_irq_restore(flags);
	#ifdef IPC_DEBUG_FEATURE
	ipc_debug.u32RecvIntCore = enDstCore;
	ipc_debug.u32IntSendTimes[enDstCore][ulLvl]++;
	#endif
	return OK;
}

 #if 0
s32 bsp_ipc_spin_lock(u32 u32SignalNum)
{
    u32 u32HsCtrl = 0;
    IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
    if(ipc_modem_reset_flag)
    {
			return OK;
    }
    for(;;)
    {
        u32HsCtrl = readl(ipc_ctrl.ipc_base + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
        if (0 == u32HsCtrl)
        {
            break;
        }
    }
    return OK;
}
s32 bsp_ipc_spin_unlock (u32 u32SignalNum)
{
	IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
	 if(ipc_modem_reset_flag)
	 {
		return OK;
	 }
	writel(0,ipc_ctrl.ipc_base + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
	return OK;
}
#endif
void ipc_modem_reset_cb(DRV_RESET_CALLCBFUN_MOMENT stage, int userdata)
{
    u32 i = 0,ret = 0;
	unsigned long flags=0;
	local_irq_save(flags);
	if (DRV_RESET_CALLCBFUN_RESET_BEFORE == stage)
	{
		for(i=0;i<32;i++)
		{
			do{
				ret = readl(ipc_ctrl.ipc_base + BSP_IPC_HS_STAT(ipc_ctrl.core_num,i));
			}while(ret == 0xa);
			ipc_modem_reset_flag = 1;
		}
	}
	if (DRV_RESET_CALLCBFUN_RESETING == stage)
	{
		ipc_modem_reset_flag = 0;
	}
	local_irq_restore(flags);
	return;
}

/*lint --e{572,778}*/
__ao_func void ccore_ipc_disable(void)
{
	unsigned long flags = 0;
	local_irq_save(flags);
	ipc_ccore_int_reset_flag = readl((const volatile void *)(ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num)));

    writel(0x0,(volatile void *)(ipc_ctrl.ipc_base+BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num)));  
	
	/*把所有C核中断恢复默认值，即屏蔽掉*/
	writel(0x0, ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(IPC_CORE_CCORE));
	local_irq_restore(flags);
}
__ao_func void ccore_ipc_enable(void)
{
	unsigned long flag = 0;
	local_irq_save(flag);
    writel(ipc_ccore_int_reset_flag,(volatile void *)(ipc_ctrl.ipc_base+BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num)));    
	local_irq_restore(flag);
}
void bsp_ipc_init(void)
{
	
	if(MODEM_ALREADY_INIT_MAGIC != get_modem_init_flag())
	{
		ipc_ctrl.core_num = IPC_CORE_MCORE;
		memset((void*)(ipc_ctrl.ipc_int_table),0x0,sizeof(struct ipc_entry) *INTSRC_NUM);
		ipc_ctrl.ipc_base = HI_IPCM_REGBASE_ADDR_VIRT;   
		ipc_ctrl.ipc_store_reg_table[0] = BSP_IPC_CPU_INT_MASK(0);       
		ipc_ctrl.ipc_store_reg_table[1] = BSP_IPC_CPU_INT_MASK(1);       
		ipc_ctrl.ipc_store_reg_table[2] = BSP_IPC_CPU_INT_MASK(3);       
		ipc_ctrl.ipc_store_reg_table[3] = BSP_IPC_CPU_INT_MASK(4); 
		ipc_ctrl.ipc_store_reg_table[4] = BSP_IPC_SEM_INT_MASK(0);       
		ipc_ctrl.ipc_store_reg_table[5] = BSP_IPC_SEM_INT_MASK(1);       
		ipc_ctrl.ipc_store_reg_table[6] = BSP_IPC_SEM_INT_MASK(3);       
		ipc_ctrl.ipc_store_reg_table[7] = BSP_IPC_SEM_INT_MASK(4);   
		ipc_ctrl.ipc_store_reg_table[8] = BSP_IPC_CPU_INT_MASK(2);       
		ipc_ctrl.ipc_store_reg_table[9] = BSP_IPC_SEM_INT_MASK(2);    
		writel(0x0,ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
		writel(0x0,ipc_ctrl.ipc_base + BSP_IPC_SEM_INT_MASK(ipc_ctrl.core_num));
	}
	(void)request_irq(MCPU_IPC_INT, ipc_int_handler, 0, 0, 0);
	enable_irq(MCPU_IPC_INT); 
	ipc_bsp_trace("ipc ok\n");
	return;    
}
#ifdef IPC_DEBUG_FEATURE
void bsp_ipc_debug_show(void)
{
	u32 i = 0,j = 0;
	printk("当前M核发送中断的目的Core ID为          : \t%d\n", ipc_debug.u32RecvIntCore);
	for(i = 0;i <IPC_CORE_BUTTOM;i++)
	{
		for(j=0;j<IPC_INT_BUTTOM;j++)
		{
			printk("往核%d发送中断%d的次数为: \t%d\n",i,j, ipc_debug.u32IntSendTimes[i][j]);
		}
	}
	for(i=0;i<INTSRC_NUM;i++)
	{
	        printk("M核%d号中断接收的次数为         : \t%d\n",i, ipc_debug.u32IntHandleTimes[i]);
	}		
}
#endif

__ao_func static void ipc_suspend(u32 suspend_num)
{
	u32 i = 0;
	for (i = 0; i < suspend_num; i++)
	{
		ipc_bak_addr[i] = readl(ipc_ctrl.ipc_store_reg_table[i] + HI_IPCM_REGBASE_ADDR_VIRT);
	}
}

__ao_func static void ipc_resume(u32 resume_num)
{
	u32 i = 0;
	for (i = 0; i < resume_num; i++)
	{
		writel(ipc_bak_addr[i],ipc_ctrl.ipc_store_reg_table[i] + HI_IPCM_REGBASE_ADDR_VIRT);
	}
}
__ao_func void reset_ipc_status_bakup(void)
{ 
	ipc_suspend(BAK_REG_NUM); 
}
__ao_func void reset_ipc_status_resume(void)
{ 
	ipc_resume(BAK_REG_NUM);
}

/*不保存恢复lpm3上ipc的中断屏蔽状态，低功耗恢复时使用模块重新使能*/
void bsp_ipc_suspend(void)
{  
	if(ipc_modem_reset_flag)
		return  ;
	ipc_suspend(BAK_REG_NUM-2);
}
void bsp_ipc_resume(void)
{
	if(ipc_modem_reset_flag)
		return  ;
	ipc_resume(BAK_REG_NUM-2);
}
/*lint -restore +e568*//*lint -restore +e685*/

#ifdef __cplusplus
}
#endif
