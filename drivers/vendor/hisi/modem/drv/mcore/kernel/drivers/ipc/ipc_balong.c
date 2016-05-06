/*lint --e{537,732}*/
#include "ipc_balong.h"
#include <bsp_memmap.h>
#include <osl_common.h>
#include <libfdt.h>
#include "m3_dump.h"
#ifdef CONFIG_IPCM_USE_FPGA_VIC
unsigned long g_p532_fpga_ipcm_virt_addr = 0;
#endif


#ifdef __cplusplus
extern "C" {
#endif
/*lint --e{452} */
static struct ipc_control    ipc_ctrl;

#ifdef IPC_DEBUG_FEATURE
static struct ipc_debug_s    ipc_debug = {0};
#endif

static u32 ipc_bak_addr[BAK_REG_NUM]={0};
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
	IPC_CHECK_PARA(ulLvl,INTSRC_NUM);
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
	IPC_CHECK_PARA(ulLvl,INTSRC_NUM);
	/*写中断屏蔽寄存器*/
	local_irq_save(flags);
	u32IntMask = readl(ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
	u32IntMask = u32IntMask & (~((u32)1 << ulLvl));
	writel(u32IntMask, ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
	local_irq_restore(flags);
	return OK;
}


s32 bsp_ipc_int_connect(IPC_INT_LEV_E ulLvl, voidfuncptr routine, u32 parameter)
{
	unsigned int flags;
	 IPC_CHECK_PARA(ulLvl,INTSRC_NUM);
	 local_irq_save(flags);
	 ipc_ctrl.ipc_int_table[ulLvl].routine = routine;
	 ipc_ctrl.ipc_int_table[ulLvl].arg = parameter;
	 local_irq_restore(flags);
	 return OK;
}

 
s32 bsp_ipc_int_disconnect(IPC_INT_LEV_E ulLvl,voidfuncptr routine, u32 parameter)
{
	unsigned int flags;
	IPC_CHECK_PARA(ulLvl,INTSRC_NUM);
	local_irq_save(flags);
	ipc_ctrl.ipc_int_table[ulLvl].routine = NULL;
	ipc_ctrl.ipc_int_table[ulLvl].arg = 0;
	local_irq_restore(flags);
	return OK;
 }
#ifdef K3V3_LPM3_HAS_MODEM_FEATURE
void ipc_int_handler(void)
#else
irqreturn_t ipc_int_handler(void)
#endif
{
    u32 i = 0,u32IntStat = 0,u32Date = 0x1,u32BitValue = 0;

    dump_int_enter(get_irq());

    u32IntStat=readl(ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_STAT(ipc_ctrl.core_num));
    /*清中断*/
    writel(u32IntStat,ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_CLR(ipc_ctrl.core_num));
    /* 遍历32个中断 */
    for (i = 0; i < INTSRC_NUM; i++)
    {   
        if (0 != i)              
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
				ipc_ctrl.last_int_cb_addr = (unsigned long)(ipc_ctrl.ipc_int_table[i].routine);
                ipc_ctrl.ipc_int_table[i].routine(ipc_ctrl.ipc_int_table[i].arg);
            }
            else
            {
                printk("cb null int%d\n",i);
            }
	    #ifdef IPC_DEBUG_FEATURE
            ipc_debug.u32IntHandleTimes[i]++;
	    #endif
        }
    }

    dump_int_exit(get_irq());

#ifndef K3V3_LPM3_HAS_MODEM_FEATURE
	return IRQ_HANDLED;
#endif
	
}


s32 bsp_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl)
{
	unsigned int flags=0;
	IPC_CHECK_PARA(ulLvl,INTSRC_NUM);
	IPC_CHECK_PARA(enDstCore,IPC_CORE_BUTTOM);
	/*写原始中断寄存器,产生中断*/
	local_irq_save(flags);
#ifdef CONFIG_IPCM_USE_FPGA_VIC
    writel((u32)1 << (u32)ulLvl, g_p532_fpga_ipcm_virt_addr + BSP_IPC_CPU_RAW_INT(enDstCore));
#else
	writel((u32)1 << (u32)ulLvl,ipc_ctrl.ipc_base + BSP_IPC_CPU_RAW_INT(enDstCore));
#endif
	local_irq_restore(flags);
	#ifdef IPC_DEBUG_FEATURE
	ipc_debug.u32RecvIntCore = enDstCore;
	ipc_debug.u32IntSendTimes[enDstCore][ulLvl]++;
	#endif
	return OK;
}

 
s32 bsp_ipc_spin_lock(u32 u32SignalNum)
{
    u32 u32HsCtrl = 0;
    IPC_CHECK_PARA(u32SignalNum,IPC_SEM_BUTTOM);
    for(;;)
    {
#ifdef CONFIG_IPCM_USE_FPGA_VIC
        u32HsCtrl = readl(g_p532_fpga_ipcm_virt_addr + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
#else
        u32HsCtrl = readl(ipc_ctrl.ipc_base + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
#endif
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
#ifdef CONFIG_IPCM_USE_FPGA_VIC
	writel(0, g_p532_fpga_ipcm_virt_addr + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
#else
	writel(0,ipc_ctrl.ipc_base + BSP_IPC_HS_CTRL(ipc_ctrl.core_num, u32SignalNum));
#endif
	return OK;
}

void bsp_ipc_init(void)
{
    struct device_node *ptr_device_node = NULL;
	const char *compatible_name = "hisilicon,ipc_balong_m3";
	char *ret_of_iomap = NULL;
	unsigned int irq_no_mcpu_ipc_int = 0;

#ifdef CONFIG_IPCM_USE_FPGA_VIC
	/* 读取基地址并映射 */
	ptr_device_node = of_find_compatible_node(NULL, NULL, "hisilicon,ipc_balong_m3_fpga");
	if (!ptr_device_node)  /* 找不到节点 */
	{
		printk("find node err\n");
		return;
	}

	ret_of_iomap = of_iomap(ptr_device_node, 0); 
	if (!ret_of_iomap)	/* 映射错误 */
	{
		printk("iomap err\n");
		return;
	}
	g_p532_fpga_ipcm_virt_addr = (unsigned long)ret_of_iomap;

#endif

    /* 读取基地址并映射 */
	ptr_device_node = of_find_compatible_node(NULL, NULL, compatible_name);
	if (!ptr_device_node)  /* 找不到节点 */
	{
		printk("find node err\n");
		return;
	}

    ret_of_iomap = of_iomap(ptr_device_node, 0); 
	if (!ret_of_iomap)  /* 映射错误 */
	{
		printk("iomap err\n");
		return;
	}

	ipc_ctrl.core_num = IPC_CORE_MCORE;
	memset((void*)(ipc_ctrl.ipc_int_table),0x0,sizeof(struct ipc_entry) *INTSRC_NUM);
	ipc_ctrl.ipc_base = (u32)ret_of_iomap;   //HI_IPCM_REGBASE_ADDR_VIRT
	ipc_ctrl.ipc_store_reg_table[0] = BSP_IPC_CPU_INT_MASK(0);       
	ipc_ctrl.ipc_store_reg_table[1] = BSP_IPC_CPU_INT_MASK(1);       
	ipc_ctrl.ipc_store_reg_table[2] = BSP_IPC_CPU_INT_MASK(2);       
	ipc_ctrl.ipc_store_reg_table[3] = BSP_IPC_CPU_INT_MASK(3); 
	ipc_ctrl.ipc_store_reg_table[4] = BSP_IPC_CPU_INT_MASK(4);       
	ipc_ctrl.ipc_store_reg_table[5] = BSP_IPC_SEM_INT_MASK(0);       
	ipc_ctrl.ipc_store_reg_table[6] = BSP_IPC_SEM_INT_MASK(1);       
	ipc_ctrl.ipc_store_reg_table[7] = BSP_IPC_SEM_INT_MASK(2);       
	ipc_ctrl.ipc_store_reg_table[8] = BSP_IPC_SEM_INT_MASK(3);     
	ipc_ctrl.ipc_store_reg_table[9] = BSP_IPC_SEM_INT_MASK(4);       
	writel(0x0,ipc_ctrl.ipc_base + BSP_IPC_CPU_INT_MASK(ipc_ctrl.core_num));
	writel(0x0,ipc_ctrl.ipc_base + BSP_IPC_SEM_INT_MASK(ipc_ctrl.core_num));

    /* 获取中断号 */
	irq_no_mcpu_ipc_int = irq_of_parse_and_map(ptr_device_node, 0);

	#ifdef K3V3_LPM3_HAS_MODEM_FEATURE	
	request_irq(irq_no_mcpu_ipc_int, ipc_int_handler, 0, 0, 0);  //MCPU_IPC_INT
	#else
	request_irq(irq_no_mcpu_ipc_int, (irq_handler_t)ipc_int_handler, 0, (const char*)0, (void*)0); //MCPU_IPC_INT
	#endif
	enable_irq(irq_no_mcpu_ipc_int);  //MCPU_IPC_INT
	printk("ipc init ok\n");
	return;    
}
#ifdef IPC_DEBUG_FEATURE
void bsp_ipc_debug_show(void)
{
	u32 i = 0,j = 0;
	printk("curr tx to core%d\n", ipc_debug.u32RecvIntCore);
	for(i = 0;i <IPC_CORE_BUTTOM;i++)
	{
		for(j=0;j<INTSRC_NUM;j++)
		{
			printk("to core %d send %d cnt%d\n",i,j, ipc_debug.u32IntSendTimes[i][j]);
		}
	}
	for(i=0;i<INTSRC_NUM;i++)
	{
	        printk("%d rx cnt%d\n",i, ipc_debug.u32IntHandleTimes[i]);
	}		
}
#endif
void bsp_ipc_suspend(void)
{
    u32 i = 0; 
    for (i = 0; i < BAK_REG_NUM; i++)
    {
        ipc_bak_addr[i] = readl(ipc_ctrl.ipc_store_reg_table[i] + HI_IPCM_REGBASE_ADDR_VIRT);
    }
    return;
}
void bsp_ipc_resume(void)
{
    u32 i = 0;
    for (i = 0; i < BAK_REG_NUM; i++)
    {
        writel(ipc_bak_addr[i],ipc_ctrl.ipc_store_reg_table[i] + HI_IPCM_REGBASE_ADDR_VIRT);
    }
}
/*lint -restore +e568*//*lint -restore +e685*/

#ifdef __cplusplus
}
#endif
