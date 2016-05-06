
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/smp.h>
#include <linux/notifier.h>
#include <linux/cpu.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <asm/cacheflush.h>
#include <mach/io.h>
#include <mach/platform.h>
#include <soc_baseaddr_interface.h>
#if defined(CHIP_BB_HI6210)
#include "soc_acpu_sctrl_interface.h"
#else
#include <soc_sctrl_interface.h>
#endif
#include <soc_ao_sctrl_interface.h>
#include "drv_ipcm.h"
#include "soc_pmctrl_interface.h"

#include <mach/pwrctrl/pwrctrl_common.h>
#include <asm/cacheflush.h>
#include <mach/pwrctrl/pwrctrl_arm_pmu.h>

#define platform_cpu_id() \
({ \
    unsigned int cpunum; \
    __asm__("mrc p15, 0, %0, c0, c0, 5" \
        : "=r" (cpunum)); \
    cpunum &= 0x0F; \
})

/*acpu ipc sem id */
IPC_SEM_ID_E acpu_ipc_sem_id[ARM_ACPU_CORE_NUM] =
{
    IPC_SEM_SMP_CPU0,
    IPC_SEM_SMP_CPU1,
    IPC_SEM_SMP_CPU2,
    IPC_SEM_SMP_CPU3,
};

unsigned int acpu_load_res[ARM_ACPU_CORE_NUM] =
{0,0,0,0};

unsigned int g_acpu_core_sc_baseaddr[ARM_ACPU_CORE_NUM] = 
{
     SOC_ACPU_SCTRL_ACPU_SC_CPU0_CTRL_ADDR(IO_ADDRESS(SOC_ACPU_SCTRL_BASE_ADDR)),
     SOC_ACPU_SCTRL_ACPU_SC_CPU1_CTRL_ADDR(IO_ADDRESS(SOC_ACPU_SCTRL_BASE_ADDR)),
     SOC_ACPU_SCTRL_ACPU_SC_CPU2_CTRL_ADDR(IO_ADDRESS(SOC_ACPU_SCTRL_BASE_ADDR)),
     SOC_ACPU_SCTRL_ACPU_SC_CPU3_CTRL_ADDR(IO_ADDRESS(SOC_ACPU_SCTRL_BASE_ADDR))
};

typedef struct acpu_core_sc_stru_s
{
    unsigned int acpu_sc_ctrl;
    unsigned int acpu_sc_stat;
    unsigned int acpu_sc_clken;
    unsigned int acpu_sc_clkdis;
    unsigned int acpu_sc_clkstat;
    unsigned int acpu_sc_rsten;
    unsigned int acpu_sc_rstdis;
    unsigned int acpu_sc_rststat;
    unsigned int acpu_sc_mtcmos_en;
    unsigned int acpu_sc_mtcmos_dis;
    unsigned int acpu_sc_mtcmos_stat;
    unsigned int acpu_sc_mtcmos_ack_stat;
     unsigned int acpu_sc_isoen;
    unsigned int acpu_sc_isodis;
    unsigned int acpu_sc_isostat;
}acpu_core_sc_stru;

extern volatile int pen_release;

/*include pwctrl_sleep.h will make us lots of troubles*/
extern void pwrctrl_asm_deep_sleep_entry(void);
extern void l2x0_flush_all(void);

static DECLARE_COMPLETION(cpu_killed);

static inline void cpu_enter_lowpower(void)
{
	unsigned int v;
#if 0
    l2x0_flush_all();
	flush_cache_all();
#endif
	asm volatile(
	"	mcr	p15, 0, %1, c7, c5, 0\n"
	"	mcr	p15, 0, %1, c7, c10, 4\n"
	/*
	 * Turn off coherency
	 */
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, %3\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	"	mrc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	  : "=&r" (v)
	  : "r" (0), "Ir" (CR_C), "Ir" (0x40)
	  : "cc");
}

static inline void cpu_leave_lowpower(void)
{
	unsigned int v;

	asm volatile(
	"mrc	p15, 0, %0, c1, c0, 0\n"
	"	orr	%0, %0, %1\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	orr	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	  : "=&r" (v)
	  : "Ir" (CR_C), "Ir" (0x40)
	  : "cc");
}

void  platform_cpu_die(unsigned int cpu)
{
    unsigned int this_cpu = platform_cpu_id();

    if (cpu != this_cpu) {
        printk(KERN_ERR"%s : cpu id %d error , %d expected.\n", __FUNCTION__,
                this_cpu, cpu);
        return;
    }

    complete(&cpu_killed);
#if 0
    l2x0_flush_all();
    dmb();

    flush_cache_all();
#endif
    pwrctrl_asm_deep_sleep_entry();	


	if (pen_release != cpu) {
		for (;;) {
			/*
			 * here's the WFI
			 */
			asm("WFI\n"
			 :
			 :
			 : "memory", "cc");

    		if (pen_release == cpu) {
    			/*
    			 * OK, proper wakeup, we're done
    			 */
    			break;
    		}

    		/*
    		 * getting here, means that we have come out of WFI without
    		 * having been woken up - this shouldn't happen
    		 *
    		 * The trouble is, letting people know about this is not really
    		 * possible, since we are currently running incoherently, and
    		 * therefore cannot safely call printk() or anything else
    		 */
    		printk(KERN_ERR"CPU%d : cpu %d should not be here!.pen_release:%d .\n", this_cpu, cpu,pen_release);
    	}

	}


    return;
}

int platform_cpu_kill(unsigned int cpu)
{
    return wait_for_completion_timeout(&cpu_killed, 5000);
}

int platform_cpu_disable(unsigned int cpu)
{
    return cpu == 0 ? -1 : 0;
}


/*balong v9r1 soc related function, to enable slave power down*/
void platform_cpu_power_down(int cpu)
{
    unsigned int reg, cnt = 0;
#if defined(CHIP_BB_HI6210)/*B020 Modify*/
    unsigned int tmp = 0;
    acpu_core_sc_stru *acpu_core_sc;
	
    spinlock_t lock = SPIN_LOCK_UNLOCKED;
    unsigned long flags;

    if(cpu >= (sizeof(g_acpu_core_sc_baseaddr) / sizeof(g_acpu_core_sc_baseaddr[0])))
    {
    	printk(KERN_ERR"%s : cpu id:%d support max:%d.\n", __FUNCTION__, cpu, (sizeof(g_acpu_core_sc_baseaddr) / sizeof(g_acpu_core_sc_baseaddr[0])));
	return;	
    }
	
    acpu_core_sc = (acpu_core_sc_stru *)g_acpu_core_sc_baseaddr[cpu];
    /*spin_lock_irqsave(&lock, flags);*/	
    /*make sure cpu in wfi status*/
    do {
        reg = readl((unsigned int)&(acpu_core_sc->acpu_sc_stat));
        printk(KERN_ERR"%s : cpu %d stat %d addr:0x%x.\n", __FUNCTION__, cpu, reg, (unsigned int)&(acpu_core_sc->acpu_sc_stat));		
        if (reg & BIT(0x1)) {
            break;
        }

        msleep(1);
        if (cnt++ > 5000) {
            printk(KERN_ERR"%s : cpu %d not in wfi state.\n", __FUNCTION__, cpu);
            return;
        }
    }while(1);
#if 0
    /*configure cpu wfi mask*/
    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    ctrl0->reg.cpu_wfi_mask_cfg |= (1 << cpu);
    writel(reg, SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));

    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    if ((ctrl0->reg.cpu_wfi_mask_cfg & (1 << cpu)) == 0) {
        printk(KERN_ERR"%s : cpu %d fail to set wfi mask.\n", __FUNCTION__, cpu);
    }

    /*
    在启动ACPU从核的下电流程（含时钟复位ISO电源等控制）前，应先按下述配置关闭监控该从核的HPM模块，随后才可以启动ACPU该从核的下电流程。
    步骤 1	配置寄存器ACPUHPMMASKEN，屏蔽监控该从核的HPM模块。
    */
    writel(BIT(cpu), SOC_PMCTRL_ACPUHPMMASKEN_ADDR(IO_ADDRESS(REG_BASE_PMCTRL)));
#endif
	/*增加关闭HPM的操作*/    
    writel(0x1, (unsigned int)&(acpu_core_sc->acpu_sc_isoen));
    do{
        tmp = readl((unsigned int)&(acpu_core_sc->acpu_sc_isostat)) & 0x1;
     } while (0x1 != tmp);

	/*可以一起复位*/
    writel(0x1F, (unsigned int)&(acpu_core_sc->acpu_sc_rsten));
    do{
        tmp = readl((unsigned int)&(acpu_core_sc->acpu_sc_rststat)) & 0x1F;
     } while (0x1F != tmp);

    writel(0x7, (unsigned int)&(acpu_core_sc->acpu_sc_clkdis));
    do{
        tmp = readl((unsigned int)&(acpu_core_sc->acpu_sc_clkstat)) & 0x7;
     } while (0x0 != tmp);

    writel(0x1, (unsigned int)&(acpu_core_sc->acpu_sc_mtcmos_dis));
#if 0
    do{
        tmp = readl((unsigned int)&(acpu_core_sc->acpu_sc_mtcmos_ack_stat)) & 0x1;
     } while (0x0 != tmp);
#endif
     /*spin_unlock_irqrestore(&lock, flags);	*/
#else
    SOC_SCTRL_SC_ACPU_CTRL0_UNION *ctrl0;


    /*make sure cpu in wfi status*/
    do {
        reg = readl(SOC_SCTRL_SCCPUCORESTAT_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
        if (reg & BIT(SOC_SCTRL_SCCPUCORESTAT_core0standywfi_START + cpu)) {
            break;
        }

        msleep(1);
        if (cnt++ > 5000) {
            printk(KERN_ERR"%s : cpu %d not in wfi state.\n", __FUNCTION__, cpu);
            return;
        }
    }while(1);

    /*configure cpu wfi mask*/
    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    ctrl0->reg.cpu_wfi_mask_cfg |= (1 << cpu);
    writel(reg, SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));

    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    if ((ctrl0->reg.cpu_wfi_mask_cfg & (1 << cpu)) == 0) {
        printk(KERN_ERR"%s : cpu %d fail to set wfi mask.\n", __FUNCTION__, cpu);
    }

    /*
    在启动ACPU从核的下电流程（含时钟复位ISO电源等控制）前，应先按下述配置关闭监控该从核的HPM模块，随后才可以启动ACPU该从核的下电流程。
    步骤 1	配置寄存器ACPUHPMMASKEN，屏蔽监控该从核的HPM模块。
    */
    writel(BIT(cpu), SOC_PMCTRL_ACPUHPMMASKEN_ADDR(IO_ADDRESS(REG_BASE_PMCTRL)));

    /*configure cpu power down*/
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_ISOEN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_RSTEN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_CLKDIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    udelay(5);
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_DIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
#endif
    return;
}

/*balong v9r1 soc related function, to enable slave power on*/
void platform_cpu_power_on(int cpu)
{
#if defined(CHIP_BB_HI6210)/*B020 Modify*/
    unsigned int reg,tmp;
	
    acpu_core_sc_stru *acpu_core_sc;
    spinlock_t lock = SPIN_LOCK_UNLOCKED;
    unsigned long flags;

    if(cpu >= (sizeof(g_acpu_core_sc_baseaddr) / sizeof(g_acpu_core_sc_baseaddr[0])))
    {
    	printk(KERN_ERR"%s : cpu id:%d support max:%d.\n", __FUNCTION__, cpu, (sizeof(g_acpu_core_sc_baseaddr) / sizeof(g_acpu_core_sc_baseaddr[0])));
	return;	
    }	

    acpu_core_sc = (acpu_core_sc_stru *)g_acpu_core_sc_baseaddr[cpu];
    spin_lock_irqsave(&lock, flags);	
#if 0
    SOC_SCTRL_SC_ACPU_CTRL0_UNION *ctrl0;
    SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_UNION *harddis0;


    /*configure cpu wfi mask*/
    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    ctrl0->reg.cpu_wfi_mask_cfg &= ~(1 << cpu);
    writel(reg, SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));

    /*
    在启动ACPU从核的上电流程（含时钟复位ISO电源等控制）前，应先按下述配置打开监控该从核的HPM模块，随后才可以启动ACPU该从核的上电流程。
    步骤 1	配置寄存器ACPUHPMMASKDIS，打开监控该从核的HPM模块。
    */
    writel(BIT(cpu), SOC_PMCTRL_ACPUHPMMASKDIS_ADDR(IO_ADDRESS(REG_BASE_PMCTRL)));
#endif
	/*增加打开HPM操作*/
    /*power on cpu*/
    writel(0x1, (unsigned int)&(acpu_core_sc->acpu_sc_mtcmos_en));
#if 0
    do{
        tmp = readl((unsigned int)&(acpu_core_sc->acpu_sc_mtcmos_ack_stat)) & 0x1;
     } while (0x1 != tmp);
#endif
    writel(0x7, (unsigned int)&(acpu_core_sc->acpu_sc_clken));
    do{
        tmp = readl((unsigned int)&(acpu_core_sc->acpu_sc_clkstat)) & 0x7;
     } while (0x7 != tmp);
    
    writel(0x1, (unsigned int)&(acpu_core_sc->acpu_sc_isodis));
    do{
        tmp = readl((unsigned int)&(acpu_core_sc->acpu_sc_isostat)) & 0x1;
     } while (0x0 != tmp);

	/*可以合并*/
    writel(0x1F, (unsigned int)&(acpu_core_sc->acpu_sc_rstdis));
    do{
        tmp = readl((unsigned int)&(acpu_core_sc->acpu_sc_rststat)) & 0x1F;
     } while (0x0 != tmp);
     spin_unlock_irqrestore(&lock, flags);		
#else
    unsigned int reg,tmp;
    SOC_SCTRL_SC_ACPU_CTRL0_UNION *ctrl0;
    SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_UNION *harddis0;


    /*configure cpu wfi mask*/
    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    ctrl0->reg.cpu_wfi_mask_cfg &= ~(1 << cpu);
    writel(reg, SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));

    /*
    在启动ACPU从核的上电流程（含时钟复位ISO电源等控制）前，应先按下述配置打开监控该从核的HPM模块，随后才可以启动ACPU该从核的上电流程。
    步骤 1	配置寄存器ACPUHPMMASKDIS，打开监控该从核的HPM模块。
    */
    writel(BIT(cpu), SOC_PMCTRL_ACPUHPMMASKDIS_ADDR(IO_ADDRESS(REG_BASE_PMCTRL)));

    /*power on cpu*/
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_EN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    do{
        tmp = readl(SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)) & BIT(cpu);
     } while (BIT(cpu) != tmp);

    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_CLKEN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_RSTDIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    udelay(10);
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_RSTEN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    udelay(20);
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_ISODIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_RSTDIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
#endif

    return;
}

static int platform_cpu_up_notify (struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;
    unsigned int this_cpu = platform_cpu_id();

    /*printk(KERN_INFO"[CPU %d] %s : cpu %d change to status %ld.\n", this_cpu, __FUNCTION__, cpu, status);*/

    switch(status){
        case CPU_UP_PREPARE:
        case CPU_UP_PREPARE_FROZEN:
            platform_cpu_power_on(cpu);
            break;
        case CPU_ONLINE:
        case CPU_ONLINE_FROZEN:
#if 0            
            /* enalbe arm pmu cpu_load function */
            printk(KERN_INFO"enable cpuload function...\n");
            arm_cpuload_init(acpu_load_res[cpu]);
            arm_cpuload_reset(acpu_load_res[cpu]);
            arm_cpuload_enable(acpu_load_res[cpu]);
            BSP_IPC_SpinUnLock(acpu_ipc_sem_id[cpu]);
			printk(KERN_INFO"up,enable cpuload function end.\n");
 #endif           
            break;
        default:
            /*just pass other event*/
            break;

    }
    return NOTIFY_DONE;
}

static int platform_cpu_down_notify (struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;
    unsigned int this_cpu = platform_cpu_id();

    /*printk(KERN_INFO"[CPU %d] %s : cpu %d change to status %ld.\n", this_cpu, __FUNCTION__, cpu, status);*/

    switch(status){
        case CPU_DOWN_PREPARE:
        case CPU_DOWN_PREPARE_FROZEN:
            /* Disalbe arm pmu cpu_load function */
            printk(KERN_INFO"disable cpuload function...\n");
            BSP_IPC_SpinLock(acpu_ipc_sem_id[cpu]);
            arm_cpuload_disable(acpu_load_res[cpu]);
            arm_cpuload_reset(acpu_load_res[cpu]);     
	     printk(KERN_INFO"down,disable cpuload function end.\n");
            break;

        case CPU_DEAD:
        case CPU_DEAD_FROZEN:
	     printk(KERN_INFO"platform_cpu_power_down begin...\n");				
            platform_cpu_power_down(cpu);
            printk(KERN_INFO"platform_cpu_power_down end.\n");			
            break;
        case CPU_ONLINE:
        case CPU_ONLINE_FROZEN:
	     printk(KERN_INFO"enable cpuload function...\n");          
            /* enalbe arm pmu cpu_load function */
            arm_cpuload_init(acpu_load_res[cpu]);
            arm_cpuload_reset(acpu_load_res[cpu]);
            arm_cpuload_enable(acpu_load_res[cpu]);
            BSP_IPC_SpinUnLock(acpu_ipc_sem_id[cpu]);          
	     printk(KERN_INFO"up,enable cpuload function end.\n");
            break;
        default:
            /*just pass other event*/
            break;

    }
    return NOTIFY_DONE;
}


static struct notifier_block __refdata platform_cpu_up_notifier = {
    .notifier_call = platform_cpu_up_notify,
    .priority = CPU_PRI_SCHED_ACTIVE,
};

static struct notifier_block __refdata platform_cpu_down_notifier = {
    .notifier_call = platform_cpu_down_notify,
    .priority = CPU_PRI_CPUSET_INACTIVE,
};

static int __init platform_hotplug_init(void)
{
    unsigned int reg = 0;
    unsigned int i;

#if 0
    /*fastboot: 软件模式*/
    for(i=0;i<ARM_ACPU_CORE_NUM;i++)
    {
        platform_cpu_power_on(i);
    }
    /*congigure cpu1/2/3 power control mode, by software*/
    writel(BIT(SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft1_msk_START) \
          |BIT(SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft2_msk_START) \
          |BIT(SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft3_msk_START) \
           , SOC_AO_SCTRL_SC_PW_CTRL_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
#endif

    register_hotcpu_notifier(&platform_cpu_up_notifier);
    register_hotcpu_notifier(&platform_cpu_down_notifier);

    for(i=0;i<ARM_ACPU_CORE_NUM;i++)
    {
        acpu_load_res[i] = (unsigned int)ioremap((ARM_PMU_ACPU0_ADDR + i*ARM_PMU_ACPU_SIZE), ARM_PMU_ACPU_SIZE);
    }

    return 0;
}

static void __exit platform_hotplug_exit(void)
{

    unsigned int i;

    unregister_hotcpu_notifier(&platform_cpu_up_notifier);
    unregister_hotcpu_notifier(&platform_cpu_down_notifier);

    for(i=0;i<ARM_ACPU_CORE_NUM;i++)
    {
        iounmap((void *)acpu_load_res[i]);
    }

    return;
}

module_init(platform_hotplug_init);
module_exit(platform_hotplug_exit);
