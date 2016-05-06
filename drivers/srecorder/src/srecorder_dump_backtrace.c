/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2012. All rights reserved.
    
    @file: srecorder_dump_backtrace.c
    
    @brief: 进行内核堆栈回溯
    
    @version: 1.0 
    
    @author: QiDechun ID: 216641
    
    @date: 2012-07-04
    
    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/ftrace.h>
#include <asm/uaccess.h>
#ifdef CONFIG_ARM
#include <asm/system.h>
#endif
#include <asm/traps.h>

#ifdef CONFIG_ARM_UNWIND
#include <asm/stacktrace.h>
#include <asm/unwind.h>
#include <asm/thread_info.h>
#endif

#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_save_log.h"
#include "../include/srecorder_dump_backtrace.h"
#include "../include/srecorder_snprintf.h"


/*----local macroes------------------------------------------------------------------*/

#ifdef CONFIG_ARM_UNWIND
/* Convert a prel31 symbol to an absolute address */
#define prel31_to_addr(ptr)                \
({                            \
    /* sign-extend to 32 bits */            \
    long offset = (((long)*(ptr)) << 1) >> 1;    \
    (unsigned long)(ptr) + offset;            \
})
#else
#endif


/*----local prototypes----------------------------------------------------------------*/

#ifdef CONFIG_ARM_UNWIND
struct unwind_ctrl_block 
{
    unsigned long vrs[16];        /* virtual register set */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))   
    const unsigned long *insn;        /* pointer to the current instructions word */
#else
    unsigned long *insn;        /* pointer to the current instructions word */
#endif
    int entries;            /* number of entries left to interpret */
    int byte;            /* current byte number in the instructions word */
};

enum regs 
{
#ifdef CONFIG_THUMB2_KERNEL
    FP = 7,
#else
    FP = 11,
#endif
    SP = 13,
    LR = 14,
    PC = 15
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
extern const struct unwind_idx __start_unwind_idx[];
extern const struct unwind_idx __stop_unwind_idx[];
#else
extern struct unwind_idx __start_unwind_idx[];
extern struct unwind_idx __stop_unwind_idx[];
#endif
#endif


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

#ifdef CONFIG_ARM_UNWIND
static void srecorder_unwind_backtrace(srecorder_reserved_mem_info_t *pmem_info, 
    struct pt_regs *regs, struct task_struct *tsk);
#ifdef CONFIG_ARM_UNWIND
static void srecorder_dump_backtrace_entry(srecorder_reserved_mem_info_t *pmem_info, 
    unsigned long where, unsigned long from, unsigned long frame);
#else
void srecorder_dump_backtrace_entry(unsigned long where, unsigned long from, unsigned long frame);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
const static struct unwind_idx *srecorder_search_index(unsigned long addr,
    const struct unwind_idx *start,
    const struct unwind_idx *origin,
    const struct unwind_idx *stop);
static const struct unwind_idx *srecorder_unwind_find_origin(const struct unwind_idx *start, const struct unwind_idx *stop);
#else
static struct unwind_idx *srecorder_search_index(unsigned long addr, struct unwind_idx *first, struct unwind_idx *last);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
static const struct unwind_idx *srecorder_unwind_find_idx(unsigned long addr);
#else
static struct unwind_idx *srecorder_unwind_find_idx(unsigned long addr);
#endif
static int srecorder_unwind_exec_insn(struct unwind_ctrl_block *ctrl);
static unsigned long srecorder_unwind_get_byte(struct unwind_ctrl_block *ctrl);
#endif

static void srecorder_dump_mem(srecorder_reserved_mem_info_t *pmem_info, 
    const char *lvl, const char *str, unsigned long bottom, unsigned long top);


/*----function definitions--------------------------------------------------------------*/

/**
     @function: static void srecorder_dump_mem(srecorder_reserved_mem_info_for_log_t *pmem_info, 
            const char *lvl, const char *str, unsigned long bottom, unsigned long top)
    @brief: Dump out the contents of some memory nicely...
    
    @param: pmem_info SRecorder的保留内存信息
    @param: lvl 日志级别
    @param: str 描述信息
    @param: bottom 内存低地址
    @param: top 内存高地址
    
    @return: none

    @note: 
*/
 static void srecorder_dump_mem(srecorder_reserved_mem_info_t *pmem_info, 
    const char *lvl, const char *str, unsigned long bottom, unsigned long top)
{
    unsigned long first;
    mm_segment_t fs;
    int i = 0;
    int bytes_read = 0;

    if (unlikely(NULL == pmem_info || NULL == lvl || NULL == str))
    {
        return;
    }
    
   /*
   * We need to switch to kernel mode so that we can use __get_user
   * to safely read from kernel space.  Note that we now dump the
   * code first, just in case the backtrace kills us.
   */
    fs = get_fs();
    set_fs(KERNEL_DS);

#ifdef CONFIG_ARM
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%s%s(0x%08lx to 0x%08lx)\n", lvl, str, bottom, top);
#else
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left,
        "%s%s(0x%016lx to 0x%016lx)\n", lvl, str, bottom, top);
#endif
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    for (first = bottom & (~31); first < top; first += 32) /*32bit圆整*/
    {
        unsigned long p;
        char str[sizeof(" 12345678") * 8 + 1]; /*dump的深度为8*/

        memset(str, ' ', sizeof(str));
        str[sizeof(str) - 1] = '\0';

        for (p = first, i = 0; i < 8 && p < top; i++, p += 4) /*8与str中的8一致*/
        {
            if (p >= bottom && p < top) 
            {
#ifdef CONFIG_ARM
                unsigned long val;
                if (__get_user(val, (unsigned long *)p) == 0)
#else
                unsigned int val;
                if (__get_user(val, (unsigned int *)p) == 0)
#endif
                {
                    sprintf(str + i * 9, " %08lx", val); /*9是" 12345678"的长度*/
                }
                else
                {
                    sprintf(str + i * 9, " ?\?\?\?\?\?\?\?"); /*9是" 12345678"的长度*/
                }
            }
        }

        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "%s%04lx:%s\n", lvl, first & 0xffff, str);
        srecorder_renew_meminfo(pmem_info, bytes_read);
    }

    set_fs(fs);
}


#ifdef CONFIG_ARM_UNWIND
/**
    @function:static void srecorder_dump_backtrace_entry(srecorder_reserved_mem_info_for_log_t *pmem_info, 
            unsigned long where, unsigned long from, unsigned long frame)
    @brief: 打印调用关系
    
    @param: pmem_info SRecorder的保留内存信息
    @param: where 被调用函数
    @param: from 调用函数
    @param: frame 寄存器lr的值
    
    @return: none

    @note: 
*/
static void srecorder_dump_backtrace_entry(srecorder_reserved_mem_info_t *pmem_info, 
    unsigned long where, unsigned long from, unsigned long frame)
{
    int bytes_read = 0;
    
#ifdef CONFIG_KALLSYMS
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "[<%08lx>] (%pS) from [<%08lx>] (%pS)\n", where, (void *)where, from, (void *)from);
#else
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "Function entered at [<%08lx>] from [<%08lx>]\n", where, from);
#endif
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    if (in_exception_text(where))
    {
        /*32bit==4字节*/
        srecorder_dump_mem(pmem_info, "", "Exception stack", frame + 4, frame + 4 + sizeof(struct pt_regs));
    }
}


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
/*
 * Binary search in the unwind index. The entries are
 * guaranteed to be sorted in ascending order by the linker.
 *
 * start = first entry
 * origin = first entry with positive offset (or stop if there is no such entry)
 * stop - 1 = last entry
 */
const static struct unwind_idx *srecorder_search_index(unsigned long addr,
    const struct unwind_idx *start,
    const struct unwind_idx *origin,
    const struct unwind_idx *stop)
{
    unsigned long addr_prel31;

    if (unlikely(NULL == start || NULL == origin || NULL == stop))
    {
        return NULL;
    }

    /*
    * only search in the section with the matching sign. This way the
    * prel31 numbers can be compared as unsigned longs.
    */
    if (addr < (unsigned long)start)
    {
        /* negative offsets: [start; origin) */
        stop = origin;
    }
    else
    {
        /* positive offsets: [origin; stop) */
        start = origin;
    }
    
    /* prel31 for address relavive to start */
    addr_prel31 = (addr - (unsigned long)start) & 0x7fffffff;

    while (start < stop - 1)
    {
        const struct unwind_idx *mid = start + ((stop - start) >> 1);

        /*
      * As addr_prel31 is relative to start an offset is needed to
      * make it relative to mid.
      */
        if (addr_prel31 - ((unsigned long)mid - (unsigned long)start) < mid->addr_offset)
        {
            stop = mid;
        }
        else
        {
            /* keep addr_prel31 relative to start */
            addr_prel31 -= ((unsigned long)mid - (unsigned long)start);
            start = mid;
        }
    }

    if (likely(start->addr_offset <= addr_prel31))
    {
        return start;
    }
    else
    {
        return NULL;
    }
}
#else
/*
 * Binary search in the unwind index. The entries entries are
 * guaranteed to be sorted in ascending order by the linker.
 */
static struct unwind_idx *srecorder_search_index(unsigned long addr, struct unwind_idx *first, struct unwind_idx *last)
{
    if (unlikely(NULL == first || NULL == last))
    {
        return NULL;
    }
    
    if (addr < first->addr) 
    {
        return NULL;
    }
    else if (addr >= last->addr)
    {
        return last;
    }

    while (first < last - 1) 
    {
        struct unwind_idx *mid = first + ((last - first + 1) >> 1);

        if (addr < mid->addr)
        {
            last = mid;
        }
        else
        {
            first = mid;
        }
    }

    return first;
}
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
static const struct unwind_idx *srecorder_unwind_find_origin(
        const struct unwind_idx *start, const struct unwind_idx *stop)
{
    while (start < stop) 
    {
        const struct unwind_idx *mid = start + ((stop - start) >> 1);

        if (mid->addr_offset >= 0x40000000)
        {
            /* negative offset */
            start = mid + 1;
        }
        else
        {
            /* positive offset */
            stop = mid;
        }
    }
    
    return stop;
}
#endif


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
static const struct unwind_idx *srecorder_unwind_find_idx(unsigned long addr)
#else
static struct unwind_idx *srecorder_unwind_find_idx(unsigned long addr)
#endif
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
    const struct unwind_idx *idx = NULL;
#else
    struct unwind_idx *idx = NULL;
#endif

    unsigned long flags;

    if (unlikely(INVALID_KSYM_ADDR == srecorder_get_unwind_lock()))
    {
        return NULL;
    }
    
    if (core_kernel_text(addr))
    {
        /* main unwind table */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
        const struct unwind_idx *srecoder_origin_unwind_idx = (struct unwind_idx *)
            (*(srec_ksym_addr_t *)srecorder_get___origin_unwind_idx());
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
        if (unlikely(NULL == srecoder_origin_unwind_idx))
        {
            srecoder_origin_unwind_idx = srecorder_unwind_find_origin(__start_unwind_idx, __stop_unwind_idx);
        }

        idx = srecorder_search_index(addr, __start_unwind_idx, srecoder_origin_unwind_idx, __stop_unwind_idx);
#else
        idx = srecorder_search_index(addr, __start_unwind_idx, __stop_unwind_idx - 1);
#endif
    }
    else 
    {
        /* module unwind tables */
        struct unwind_table *table;
        struct list_head *unwind_tables = (struct list_head *)srecorder_get_unwind_tables();

        if (unlikely(NULL == unwind_tables))
        {
            return NULL;
        }

        if (spin_trylock_irqsave((spinlock_t *)srecorder_get_unwind_lock(), flags))
        {
            list_for_each_entry(table, unwind_tables, list) 
            {
                if (addr >= table->begin_addr && addr < table->end_addr)
                {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
                    idx = srecorder_search_index(addr, (struct unwind_idx *)table->start, 
                        (struct unwind_idx *)table->origin, (struct unwind_idx *)table->stop);
#else
                    idx = srecorder_search_index(addr, table->start, table->stop - 1);
#endif

                    /* Move-to-front to exploit common traces */
                    list_move(&table->list, unwind_tables);
                    break;
                }
            }
            
            spin_unlock_irqrestore((spinlock_t *)srecorder_get_unwind_lock(), flags);
        }
    }

    return idx;
}


static unsigned long srecorder_unwind_get_byte(struct unwind_ctrl_block *ctrl)
{
    unsigned long ret = 0;

    if (unlikely(NULL == ctrl))
    {
        return 0;
    }
    
    if (ctrl->entries <= 0) 
    {
        return 0;
    }

    ret = (*ctrl->insn >> (ctrl->byte * 8)) & 0xff;

    if (ctrl->byte == 0) 
    {
        ctrl->insn++;
        ctrl->entries--;
        ctrl->byte = 3;
    }
    else
    {
        ctrl->byte--;
    }

    return ret;
}


/*
 * Execute the current unwind instruction.
 */
static int srecorder_unwind_exec_insn(struct unwind_ctrl_block *ctrl)
{
    unsigned long insn = srecorder_unwind_get_byte(ctrl);

    if (unlikely(NULL == ctrl))
    {
        return -URC_FAILURE;
    }
    
    if ((insn & 0xc0) == 0x00)
    {
        ctrl->vrs[SP] += ((insn & 0x3f) << 2) + 4;
    }
    else if ((insn & 0xc0) == 0x40)
    {
        ctrl->vrs[SP] -= ((insn & 0x3f) << 2) + 4;
    }
    else if ((insn & 0xf0) == 0x80) 
    {
        unsigned long mask;
        unsigned long *vsp = (unsigned long *)ctrl->vrs[SP];
        int load_sp = 0; 
        int reg = 4;

        insn = (insn << 8) | srecorder_unwind_get_byte(ctrl);
        mask = insn & 0x0fff;
        if (mask == 0) 
        {
            return -URC_FAILURE;
        }

        /* pop R4-R15 according to mask */
        load_sp = mask & (1 << (13 - 4));
        while (mask) 
        {
            if (mask & 1)
            {
                ctrl->vrs[reg] = *vsp++;
            }
            mask >>= 1;
            reg++;
        }
        
        if (!load_sp)
        {
            ctrl->vrs[SP] = (unsigned long)vsp;
        }
    }
    else if ((insn & 0xf0) == 0x90 && (insn & 0x0d) != 0x0d)
    {
        ctrl->vrs[SP] = ctrl->vrs[insn & 0x0f];
    }
    else if ((insn & 0xf0) == 0xa0) 
    {
        unsigned long *vsp = (unsigned long *)ctrl->vrs[SP];
        int reg;

        /* pop R4-R[4+bbb] */
        for (reg = 4; reg <= 4 + (insn & 7); reg++)
        {
            ctrl->vrs[reg] = *vsp++;
        }
        
        if (insn & 0x80)
        {
            ctrl->vrs[14] = *vsp++;
        }
        ctrl->vrs[SP] = (unsigned long)vsp;
    }
    else if (insn == 0xb0)
    {
        if (ctrl->vrs[PC] == 0)
        {
            ctrl->vrs[PC] = ctrl->vrs[LR];
        }
        
        /* no further processing */
        ctrl->entries = 0;
    } 
    else if (insn == 0xb1) 
    {
        unsigned long mask = srecorder_unwind_get_byte(ctrl);
        unsigned long *vsp = (unsigned long *)ctrl->vrs[SP];
        int reg = 0;

        if (mask == 0 || mask & 0xf0) 
        {
            return -URC_FAILURE;
        }

        /* pop R0-R3 according to mask */
        while (mask) 
        {
            if (mask & 1)
            {
                ctrl->vrs[reg] = *vsp++;
            }
            mask >>= 1;
            reg++;
        }
        ctrl->vrs[SP] = (unsigned long)vsp;
    } 
    else if (insn == 0xb2) 
    {
        unsigned long uleb128 = srecorder_unwind_get_byte(ctrl);

        ctrl->vrs[SP] += 0x204 + (uleb128 << 2);
    } 
    else 
    {
        return -URC_FAILURE;
    }

    return URC_OK;
}


/**
    @function: int srecorder_unwind_frame(struct stackframe *frame)
    @brief: 进行栈帧检查和追溯
    
    @param: frame 待检查和追溯的栈帧
    
    @return: 0 - successfully, others - failed

    @note: 
*/
int srecorder_unwind_frame(struct stackframe *frame)
{
    unsigned long high;
    unsigned long low;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
    const struct unwind_idx *idx;
#else
    struct unwind_idx *idx;
#endif

    struct unwind_ctrl_block ctrl;
    
    if (unlikely(NULL == frame))
    {
        return -1;
    }
    
    /* only go to a higher address on the stack */
    low = frame->sp;
    high = ALIGN(low, THREAD_SIZE);
    
    if (!kernel_text_address(frame->pc))
    {
        return -URC_FAILURE;
    }

    idx = srecorder_unwind_find_idx(frame->pc);
    if (NULL == idx) 
    {
        return -URC_FAILURE;
    }

    ctrl.vrs[FP] = frame->fp;
    ctrl.vrs[SP] = frame->sp;
    ctrl.vrs[LR] = frame->lr;
    ctrl.vrs[PC] = 0;

    if (idx->insn == 1)
    {
        /* can't unwind */
        return -URC_FAILURE;
    }
    else if ((idx->insn & 0x80000000) == 0)
    {
        /* prel31 to the unwind table */
        ctrl.insn = (unsigned long *)prel31_to_addr(&idx->insn);
    }
    else if ((idx->insn & 0xff000000) == 0x80000000)
    {
        /* only personality routine 0 supported in the index */
        ctrl.insn = &idx->insn;
    }
    else 
    {
        return -URC_FAILURE;
    }

    /* check the personality routine */
    if ((*ctrl.insn & 0xff000000) == 0x80000000) 
    {
        ctrl.byte = 2;
        ctrl.entries = 1;
    } 
    else if ((*ctrl.insn & 0xff000000) == 0x81000000)
    {
        ctrl.byte = 1;
        ctrl.entries = 1 + ((*ctrl.insn & 0x00ff0000) >> 16);
    }
    else 
    {
        return -URC_FAILURE;
    }

    while (ctrl.entries > 0)
    {
        int urc = srecorder_unwind_exec_insn(&ctrl);
        if (urc < 0)
        {
            return urc;
        }
        
        if (ctrl.vrs[SP] < low || ctrl.vrs[SP] >= high)
        {
            return -URC_FAILURE;
        }
    }

    if (ctrl.vrs[PC] == 0)
    {
        ctrl.vrs[PC] = ctrl.vrs[LR];
    }

    /* check for infinite loop */
    if (frame->pc == ctrl.vrs[PC])
    {
        return -URC_FAILURE;
    }

    frame->fp = ctrl.vrs[FP];
    frame->sp = ctrl.vrs[SP];
    frame->lr = ctrl.vrs[LR];
    frame->pc = ctrl.vrs[PC];

    return URC_OK;
}


/**
    @function:static void srecorder_unwind_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info, 
        struct pt_regs *regs, struct task_struct *tsk)
    @brief: dump死机时内核的调用栈信息
    
    @param: pmem_info SRecorder的保留内存信息
    @param: regs cpu的寄存器状态
    @param: tsk 需要被dump调用栈的进程
    
    @return: none

    @note: 
*/
static void srecorder_unwind_backtrace(srecorder_reserved_mem_info_t *pmem_info, 
    struct pt_regs *regs, struct task_struct *tsk)
{
    struct stackframe frame;
    register unsigned long current_sp asm ("sp");

    if (unlikely(NULL == pmem_info))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or kernel symbol addr!\n", __FILE__, __LINE__);
        return;
    }
    
    if (NULL == tsk)
    {
        tsk = current;
    }

    if (NULL != regs) 
    {
        frame.fp = regs->ARM_fp;
        frame.sp = regs->ARM_sp;
        frame.lr = regs->ARM_lr;
        
        /* PC might be corrupted, use LR in that case. */        
        frame.pc = kernel_text_address(regs->ARM_pc) ? regs->ARM_pc : regs->ARM_lr;
    } 
    else if (tsk == current) 
    {
        frame.fp = (unsigned long)__builtin_frame_address(0);
        frame.sp = current_sp;
        frame.lr = (unsigned long)__builtin_return_address(0);
        frame.pc = (unsigned long)srecorder_unwind_backtrace;
    } 
    else 
    {
        /* task blocked in __switch_to */
        frame.fp = thread_saved_fp(tsk);
        frame.sp = thread_saved_sp(tsk);
        
        /*
      * The function calling __switch_to cannot be a leaf function
      * so LR is recovered from the stack.
      */
        frame.lr = 0;
        frame.pc = thread_saved_pc(tsk);
    }

    while (1) 
    {
        int urc;
        unsigned long where = frame.pc;
        
        urc = srecorder_unwind_frame(&frame);
        if (urc < 0)
        {
            break;
        }
        
        srecorder_dump_backtrace_entry(pmem_info, where, frame.pc, frame.sp - 4); /* -4指向寄存器lr */
    }
}
#else
/**
    @function:static void srecorder_dump_backtrace_entry(srecorder_reserved_mem_info_for_log_t *pmem_info, 
            unsigned long where, unsigned long from, unsigned long frame)
    @brief: 打印调用关系
    
    @param: pmem_info SRecorder的保留内存信息
    @param: where 被调用函数
    @param: from 调用函数
    @param: frame 寄存器lr的值
    
    @return: none

    @note: 
*/
void srecorder_dump_backtrace_entry(unsigned long where, unsigned long from, unsigned long frame)
{
	int bytes_read = 0;
	srecorder_reserved_mem_info_t *pmem_info = srecorder_get_reserved_mem_info();

	if (NULL == pmem_info)
	{
		return;
	}
  
#ifdef CONFIG_KALLSYMS
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "[<%08lx>] (%pS) from [<%08lx>] (%pS)\n", where, (void *)where, from, (void *)from);
#else
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "Function entered at [<%08lx>] from [<%08lx>]\n", where, from);
#endif
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    if (in_exception_text(where))
    {
        /*32bit==4字节*/
        srecorder_dump_mem(pmem_info, "", "Exception stack", frame + 4, frame + 4 + sizeof(struct pt_regs));
    }
}
#endif


#ifndef CONFIG_ARM_UNWIND
extern void * high_memory;
/*
 * Stack pointers should always be within the kernels view of
 * physical memory.  If it is not there, then we can't dump
 * out any information relating to the stack.
 */
static int verify_stack(unsigned long sp)
{
	if (sp < PAGE_OFFSET ||
	    (sp > (unsigned long)high_memory && high_memory != NULL))
		return -EFAULT;

	return 0;
}
#endif


void srecorder_dump_backtrace_entry64(srecorder_reserved_mem_info_t *pmem_info,
    unsigned long where, unsigned long stack)
{
    int bytes_read = 0;

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr
        + pmem_info->bytes_read, pmem_info->bytes_left,
        "[<%p>] %pS\n", (void *)where, (void *)where);
    srecorder_renew_meminfo(pmem_info, bytes_read);

    if (in_exception_text(where))
    {
        srecorder_dump_mem(pmem_info, "", "Exception stack", stack,
            stack + sizeof(struct pt_regs));
    }
}


/**
    @function: void srecorder_dump_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info, 
        struct pt_regs *regs, struct task_struct *tsk)
    @brief: dump死机时内核的调用栈信息
    
    @param: pmem_info SRecorder的保留内存信息
    @param: regs cpu寄存器的状态
    @param: tsk 需要被dump调用栈的进程
    
    @return: none

    @note: 
*/
void srecorder_dump_backtrace(srecorder_reserved_mem_info_t *pmem_info, 
    struct pt_regs *regs, struct task_struct *tsk)
{
#ifdef CONFIG_ARM
#ifdef CONFIG_ARM_UNWIND
    srecorder_unwind_backtrace(pmem_info, regs, tsk);
#else
    unsigned int fp;
    unsigned int mode;
    int ok = 1;
    int bytes_read = 0;

    if (NULL == pmem_info)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
    
    if (NULL == tsk)
    {
        tsk = current;
    }

    if (NULL != regs) 
    {
        fp = regs->ARM_fp;
        mode = processor_mode(regs);
    } 
    else if (tsk != current) 
    {
        fp = thread_saved_fp(tsk);
        mode = 0x10; /* MODE32_BIT */
    } 
    else 
    {
        asm("mov %0, fp" : "=r" (fp) : : "cc");
        mode = 0x10; /* MODE32_BIT */
    }

    if (0 == fp) 
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, 
            pmem_info->bytes_left, "%s\n", "no frame pointer");
        ok = 0;
    } 
    else if (verify_stack(fp)) 
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, 
            pmem_info->bytes_left, "invalid frame pointer 0x%08x\n", fp);
        ok = 0;
    }
    else if (fp < (unsigned long)end_of_stack(tsk))
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, 
            pmem_info->bytes_left, "%s\n", "frame pointer underflow");
    }
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    if (0 != ok)
    {
        srecorder_c_backtrace(fp, mode);
    }
#endif
#else
    /*  FOR ARM64 */
    struct stackframe frame;
    const register unsigned long current_sp asm ("sp");
    int bytes_read = 0;

    if (NULL == tsk)
    {
        tsk = current;
    }

    if (regs)
    {
        frame.fp = regs->regs[29];
        frame.sp = regs->sp;
        frame.pc = regs->pc;
    }
    else if (tsk == current)
    {
        frame.fp = (unsigned long)__builtin_frame_address(0);
        frame.sp = current_sp;
        frame.pc = (unsigned long)srecorder_dump_backtrace;
    }
    else
    {
        /*
        * task blocked in __switch_to
        */
        frame.fp = thread_saved_fp(tsk);
        frame.sp = thread_saved_sp(tsk);
        frame.pc = thread_saved_pc(tsk);
    }

    while (1)
    {
        unsigned long where = frame.pc;
        int ret;

        ret = unwind_frame(&frame);
        if (ret < 0)
        {
            break;
        }
        srecorder_dump_backtrace_entry64(pmem_info, where, frame.sp);
    }
#endif
}

