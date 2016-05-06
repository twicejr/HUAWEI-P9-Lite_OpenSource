/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_allcpu_stack.c
    
    @brief: 读取死机时所有活动 CPU的调用栈
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-06-21
    
    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/utsname.h>
#include <linux/irq.h>
#include <linux/version.h>

#include "../include/srecorder_allcpu_stack.h"
#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_save_log.h"
#include "../include/srecorder_dump_backtrace.h"
#include "../include/srecorder_snprintf.h"


#if defined(CONFIG_DUMP_ALLCPU_STACK)

/*----local macroes------------------------------------------------------------------*/


/*----local prototypes----------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

#ifdef CONFIG_ARM
static void srecorder_show_regs(srecorder_reserved_mem_info_t *pmem_info, struct pt_regs *regs, int all);
#endif
static void srecorder_show_data(srecorder_reserved_mem_info_t *pmem_info, unsigned long addr, int nbytes, const char *name);
#ifdef CONFIG_ARM
static void srecorder_show_extra_register_data(srecorder_reserved_mem_info_t *pmem_info, struct pt_regs *regs, int nbytes);
static void __srecorder_show_regs(srecorder_reserved_mem_info_t *pmem_info, struct pt_regs *regs);
#endif

static int srecorder_trigger_all_cpu_backtrace(srecorder_reserved_mem_info_t *pmem_info);
static void srecorder_arch_trigger_all_cpu_backtrace(srecorder_reserved_mem_info_t *pmem_info);
static void srecorder_smp_send_all_cpu_backtrace(srecorder_reserved_mem_info_t *pmem_info);
static void srecorder_show_stack(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *tsk, unsigned long *sp);


/*----local variables------------------------------------------------------------------*/

static const char *s_processor_modes[] = 
{
    "USER_26", "FIQ_26" , "IRQ_26" , "SVC_26" , "UK4_26" , "UK5_26" , "UK6_26" , "UK7_26" ,
    "UK8_26" , "UK9_26" , "UK10_26", "UK11_26", "UK12_26", "UK13_26", "UK14_26", "UK15_26",
    "USER_32", "FIQ_32" , "IRQ_32" , "SVC_32" , "UK4_32" , "UK5_32" , "UK6_32" , "ABT_32" ,
    "UK8_32" , "UK9_32" , "UK10_32", "UND_32" , "UK12_32", "UK13_32", "UK14_32", "SYS_32"
};

static const char *s_isa_modes[] =
{
    "ARM" , "Thumb" , "Jazelle", "ThumbEE"
};


/*----function definitions--------------------------------------------------------------*/

/**
    @function: static void srecorder_show_data(srecorder_reserved_mem_info_for_log_t *pmem_info, 
                unsigned long addr, int nbytes, const char *name)
    @brief: dump a block of kernel memory from around the given address

    @param: pmem_info SRecorder的保留内存信息
    @param: addr 起始地址
    @param: nbytes 打印的信息长度
    @param: name 寄存器的名称
    
    @return: none

    @note: 
*/
static void srecorder_show_data(srecorder_reserved_mem_info_t *pmem_info, 
    unsigned long addr, int nbytes, const char *name)
{
    int i;
    int j;
    int nlines;
    int bytes_read = 0; 
    u32 *p = NULL;

    /*
   * don't attempt to dump non-kernel addresses or
   * values that are probably just small negative numbers
   */
    if (addr < PAGE_OFFSET || addr > -256UL || NULL == pmem_info)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, "\n%s: %#lx:\n", name, addr);
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    /*
   * round address down to a 32 bit boundary
   * and always dump a multiple of 32 bytes
   */
    p = (u32 *)(addr & ~(sizeof(u32) - 1));
    nbytes += (addr & (sizeof(u32) - 1));
    nlines = (nbytes + 31) / 32; /*按照32bit圆整*/

    for (i = 0; i < nlines; i++) 
    {
        /*
      * just display low 16 bits of address to keep
      * each line of the dump < 80 characters
      */
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, "%04lx ", (unsigned long)p & 0xffff);
        srecorder_renew_meminfo(pmem_info, bytes_read);
        for (j = 0; j < 8; j++) 
        {
            u32 data;
            if (probe_kernel_address(p, data)) 
            {
                bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, "%s", " ********");
            } 
            else 
            {
                bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, " %08x", data);
            }
            srecorder_renew_meminfo(pmem_info, bytes_read);
            ++p;
        }
        
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, "%s", "\n");
        srecorder_renew_meminfo(pmem_info, bytes_read);
    }
}


#ifdef CONFIG_ARM
/**
    @function: static void srecorder_show_extra_register_data(srecorder_reserved_mem_info_for_log_t *pmem_info, 
        struct pt_regs *regs, int nbytes)
    @brief: 打印其他寄存器的信息

    @param: pmem_info SRecorder的保留内存信息
    @param: regs 寄存器
    @param: nbytes 打印的信息长度
    
    @return: none

    @note: 
*/
static void srecorder_show_extra_register_data(srecorder_reserved_mem_info_t *pmem_info, 
    struct pt_regs *regs, int nbytes)
{
    mm_segment_t fs;

    fs = get_fs();
    set_fs(KERNEL_DS);
    srecorder_show_data(pmem_info, regs->ARM_pc - nbytes, nbytes * 2, "PC");
    srecorder_show_data(pmem_info, regs->ARM_lr - nbytes, nbytes * 2, "LR");
    srecorder_show_data(pmem_info, regs->ARM_sp - nbytes, nbytes * 2, "SP");
    srecorder_show_data(pmem_info, regs->ARM_ip - nbytes, nbytes * 2, "IP");
    srecorder_show_data(pmem_info, regs->ARM_fp - nbytes, nbytes * 2, "FP");
    srecorder_show_data(pmem_info, regs->ARM_r0 - nbytes, nbytes * 2, "R0");
    srecorder_show_data(pmem_info, regs->ARM_r1 - nbytes, nbytes * 2, "R1");
    srecorder_show_data(pmem_info, regs->ARM_r2 - nbytes, nbytes * 2, "R2");
    srecorder_show_data(pmem_info, regs->ARM_r3 - nbytes, nbytes * 2, "R3");
    srecorder_show_data(pmem_info, regs->ARM_r4 - nbytes, nbytes * 2, "R4");
    srecorder_show_data(pmem_info, regs->ARM_r5 - nbytes, nbytes * 2, "R5");
    srecorder_show_data(pmem_info, regs->ARM_r6 - nbytes, nbytes * 2, "R6");
    srecorder_show_data(pmem_info, regs->ARM_r7 - nbytes, nbytes * 2, "R7");
    srecorder_show_data(pmem_info, regs->ARM_r8 - nbytes, nbytes * 2, "R8");
    srecorder_show_data(pmem_info, regs->ARM_r9 - nbytes, nbytes * 2, "R9");
    srecorder_show_data(pmem_info, regs->ARM_r10 - nbytes, nbytes * 2, "R10");
    set_fs(fs);
}


/**
    @function: static void __srecorder_show_regs(srecorder_reserved_mem_info_for_log_t *pmem_info, struct pt_regs *regs)
    @brief: 打印寄存器的信息，被函数srecorder_show_regs调用

    @param: pmem_info SRecorder的保留内存信息
    @param: regs 寄存器
    
    @return: none

    @note: 
*/
static void __srecorder_show_regs(srecorder_reserved_mem_info_t *pmem_info, struct pt_regs *regs)
{
    unsigned long flags = 0L;
    char buf[64];
    int bytes_read = 0;
    
    if (NULL == pmem_info || NULL == regs)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }

    flags = regs->ARM_cpsr;
    buf[0] = flags & PSR_N_BIT ? 'N' : 'n';
    buf[1] = flags & PSR_Z_BIT ? 'Z' : 'z';
    buf[2] = flags & PSR_C_BIT ? 'C' : 'c';
    buf[3] = flags & PSR_V_BIT ? 'V' : 'v';
    buf[4] = '\0';
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "CPU: %d    %s  (%s %.*s)\n"
        "PC is at %08lx\n"
        "LR is at %08lx\n"
        "pc : [<%08lx>]    lr : [<%08lx>]    psr: %08lx\n"
        "sp : %08lx  ip : %08lx  fp : %08lx\n"
        "r10: %08lx  r9 : %08lx  r8 : %08lx\n"
        "r7 : %08lx  r6 : %08lx  r5 : %08lx  r4 : %08lx\n"
        "r3 : %08lx  r2 : %08lx  r1 : %08lx  r0 : %08lx\n"
        "Flags: %s  IRQs o%s  FIQs o%s  Mode %s  ISA %s  Segment %s\n",
        raw_smp_processor_id(), 
        print_tainted(),
        init_utsname()->release,
        (int)strcspn(init_utsname()->version, " "),
        init_utsname()->version, 
        instruction_pointer(regs), /*本来是unsigned long型的，怎么要打印成字符串呢?qidechun将其改为打印成%08x*/
        regs->ARM_lr, /*本来是unsigned long型的，怎么要打印成字符串呢?qidechun将其改为打印成%08x*/
        regs->ARM_pc, 
        regs->ARM_lr, 
        regs->ARM_cpsr,
        regs->ARM_sp, 
        regs->ARM_ip, 
        regs->ARM_fp, 
        regs->ARM_r10, 
        regs->ARM_r9,
        regs->ARM_r8, 
        regs->ARM_r7, 
        regs->ARM_r6,
        regs->ARM_r5, 
        regs->ARM_r4, 
        regs->ARM_r3, 
        regs->ARM_r2,
        regs->ARM_r1, 
        regs->ARM_r0, 
        buf, 
        interrupts_enabled(regs) ? "n" : "ff",
        fast_interrupts_enabled(regs) ? "n" : "ff",
        s_processor_modes[processor_mode(regs)],
        s_isa_modes[isa_mode(regs)],
        (get_fs() == get_ds()) ? ("kernel") : ("user"));
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
#ifdef CONFIG_CPU_CP15
    {
        unsigned int ctrl;

        buf[0] = '\0';
#ifdef CONFIG_CPU_CP15_MMU
        {
            unsigned int transbase, dac;
            asm("mrc p15, 0, %0, c2, c0\n\t"
                "mrc p15, 0, %1, c3, c0\n"
                : "=r" (transbase), "=r" (dac));
            SRECORDER_SNPRINTF(buf, sizeof(buf), "  Table: %08x  DAC: %08x", transbase, dac);
        }
#endif
        asm("mrc p15, 0, %0, c1, c0\n" : "=r" (ctrl));
        
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "Control: %08x%s\n", ctrl, buf);
        srecorder_renew_meminfo(pmem_info, bytes_read);
    }
#endif
    
    srecorder_show_extra_register_data(pmem_info, regs, 128); /*128代表打印信息的长度*/
}


/**
    @function: static void srecorder_show_regs(srecorder_reserved_mem_info_for_log_t *pmem_info, struct pt_regs *regs, int all)
    @brief: 打印寄存器的信息并进行堆栈回溯

    @param: pmem_info SRecorder的保留内存信息
    @param: regs 寄存器
    @param: all 没什么用，为了和X86的函数保持一致
    
    @return: none

    @note: 
*/
static void srecorder_show_regs(srecorder_reserved_mem_info_t *pmem_info, struct pt_regs *regs, int all)
{
    int bytes_read = 0;
    
    if (NULL == pmem_info || NULL == regs)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
    
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "\nPid: %d, comm: %20s\n", task_pid_nr(current), current->comm);
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    __srecorder_show_regs(pmem_info, regs);
    srecorder_dump_backtrace(pmem_info, NULL, NULL);
}
#endif


/**
    @function: static void srecorder_show_stack(srecorder_reserved_mem_info_for_log_t *pmem_info, 
                struct task_struct *tsk, unsigned long *sp)
    @brief: 打印进程的堆栈

    @param: pmem_info SRecorder的保留内存信息
    @param: tsk 待打印堆栈的进程
    @param: sp 堆栈的指针
    
    @return: none

    @note: 
*/
static void srecorder_show_stack(srecorder_reserved_mem_info_t *pmem_info, 
    struct task_struct *tsk, unsigned long *sp)
{
    srecorder_dump_backtrace(pmem_info, NULL, tsk);
    barrier();
}


/**
    @function: static void srecorder_smp_send_all_cpu_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 各个架构的cpu打印调用轨迹的函数，一般是调用该函数的cpu先打印，然后向其他的cpu发送打印调用轨迹的中断
            并等待一段时间，等待其他的cpu打印完调用轨迹后返回

    @param: pmem_info SRecorder的保留内存信息
    
    @return: none

    @note: 
*/
static void srecorder_smp_send_all_cpu_backtrace(srecorder_reserved_mem_info_t *pmem_info)
{
    int bytes_read = 0;
    struct task_struct *g = NULL;
    struct task_struct *p = NULL;
    
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%s", ">>>>> Do backtrace for all threads <<<<<\n");
    srecorder_renew_meminfo(pmem_info, bytes_read);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 2, 0))
    if (read_trylock(&tasklist_lock))
#else
    rcu_read_lock();
#endif
    {
        /* 打印所有进程的调用信息 */
        do_each_thread(g, p) 
        {
            /*
          * reset the NMI-timeout, listing all files on a slow
          * console might take a lot of time:
          */
            const char *stat_nam = TASK_STATE_TO_CHAR_STR;
            unsigned long free = 0;
            unsigned state = p->state ? __ffs(p->state) + 1 : 0;

            /* 只打印D状态、运行态、就绪态的线程调用栈 */
            if ((TASK_RUNNING == p->state) || (TASK_UNINTERRUPTIBLE == (p->state & TASK_UNINTERRUPTIBLE)))
            {
                bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
                    "\ntask:%s %c", p->comm, state < sizeof(stat_nam) - 1 ? stat_nam[state] : '?');
                srecorder_renew_meminfo(pmem_info, bytes_read);
#if BITS_PER_LONG == 32
                if (state == TASK_RUNNING)
                {
                    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
                        "%s", " running ");
                }
                else
                {
                    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
                        " PC:%08lx ", thread_saved_pc(p));
                }
#else
                if (state == TASK_RUNNING)
                {
                    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
                        "%s", " running task ");
                }
                else
                {
                    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
                        " PC:%016lx ", thread_saved_pc(p));
                }
#endif
                srecorder_renew_meminfo(pmem_info, bytes_read);
                
#ifdef CONFIG_DEBUG_STACK_USAGE
                free = stack_not_used(p);
#endif

                bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
                    "stack:%lu pid:%d father:%d flags:0x%08lx\n", 
                    free, task_pid_nr(p), task_pid_nr(p->real_parent), (unsigned long)task_thread_info(p)->flags);
                srecorder_renew_meminfo(pmem_info, bytes_read);
                
                srecorder_show_stack(pmem_info, p, NULL);
            }
        } while_each_thread(g, p);
        
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 2, 0))
        read_unlock(&tasklist_lock);
#else
        rcu_read_unlock();
#endif
    }
}


/**
    @function: static void srecorder_arch_trigger_all_cpu_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 触发所有的cpu打印自己的调用轨迹，这个与cpu的架构有关系

    @param: pmem_info SRecorder的保留内存信息
    
    @return: none

    @note: 
*/
static void srecorder_arch_trigger_all_cpu_backtrace(srecorder_reserved_mem_info_t *pmem_info)
{
    srecorder_smp_send_all_cpu_backtrace(pmem_info);
}


/**
    @function: static int srecorder_trigger_all_cpu_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 触发所有的cpu打印自己的调用轨迹

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
static int srecorder_trigger_all_cpu_backtrace(srecorder_reserved_mem_info_t *pmem_info)
{
    if (unlikely(NULL == pmem_info))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

    srecorder_arch_trigger_all_cpu_backtrace(pmem_info);
    
    return 0;
}


/**
    @function: int srecorder_get_allcpu_stack(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: 读取死机时所有活动 CPU的调用栈

    @param: pmem_info SRecorder的保留内存信息
    
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_get_allcpu_stack(srecorder_reserved_mem_info_t *pmem_info)
{
    psrecorder_info_header_t pinfo_header = NULL;
    
    if (NULL == pmem_info)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

    if (srecorder_log_has_been_dumped(ALL_CPU_STACK_BIT3) || pmem_info->dump_modem_crash_log_only)
    {
        SRECORDER_PRINTK("all cpu stack have been dumped successfully!\n");
        return -1;   
    }
    
    if (0 != srecorder_write_info_header(pmem_info, ALL_CPU_STACK_BIT3, &pinfo_header))
    {
        return -1;
    }
    
    if (0 > srecorder_trigger_all_cpu_backtrace(pmem_info))
    {
#ifdef CONFIG_ARM
        int bytes_read = 0;
        struct pt_regs *regs = get_irq_regs();    
        
        if (NULL != regs) 
        {
            bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, 
                pmem_info->bytes_left, "CPU%d:\n", smp_processor_id());
            srecorder_renew_meminfo(pmem_info, bytes_read);
            srecorder_show_regs(pmem_info, regs, 1);
        }
#endif
    }

    srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
    
    return 0;
}


/**
    @function:int srecorder_init_allcpu_stack(srecorder_module_init_params_t *pinit_params)
    @brief: 初始化allcpu stack模块

    @param: pinit_params 模块初始化数据
        
    @return: 0 - 成功；-1-失败

    @note: 
*/
int srecorder_init_allcpu_stack(srecorder_module_init_params_t *pinit_params)
{
    srecorder_clear_log_dumped_bit(ALL_CPU_STACK_BIT3);
    
    return 0;
}


/**
    @function: void srecorder_exit_allcpu(void)
    @brief: 模块退出函数，它的主要工作是清除allcpu stack模块中的变量s_reserved_mem_info_for_log_temp，
           因为在等待workqueue完成检查cpu调用栈的超时时间到了以后，我们不再希望其他的线程或者任务往
           SRecorder的保留内存区写内容，因此必须把它设置为NULL。

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_allcpu_stack(void)
{
    srecorder_set_log_dumped_bit(ALL_CPU_STACK_BIT3);
}
#else
int srecorder_get_allcpu_stack(srecorder_reserved_mem_info_t *pmem_info)
{
    return 0;
}


int srecorder_init_allcpu_stack(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


void srecorder_exit_allcpu_stack(void)
{
    return;
}
#endif

