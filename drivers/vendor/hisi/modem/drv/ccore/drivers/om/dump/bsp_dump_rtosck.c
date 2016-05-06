/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_dump.c
*
*   作    者 :  z67193
*
*   描    述 :  临终遗言功能
*
*   修改记录 :  2012年12月11日  v1.00  z67193  创建
*************************************************************************/
/*lint -save -e537 -e451*/
#include "sre_shell.h"
#include "sre_libc.h"
#include "sre_sem.h"
#include "sre_hook.h"
#include "sre_task.h"
#include "osl_thread.h"
#include "osl_sem.h"
#include "osl_cache.h"
#include "sre_typedef.h"
#include "sre_exc.h"
#include "sre_sys.h"
#include "sre_typedef.h"
#include "product_config.h"
#include "osl_types.h"
#include "drv_comm.h"
#include "bsp_om_api.h"
#include "bsp_dump_drv.h"
#include "bsp_ipc.h"
#include "bsp_memmap.h"
#include "bsp_wdt.h"
#include "bsp_nvim.h"
#include "bsp_onoff.h"
#include "bsp_rfile.h"
#include "bsp_nvim.h"
#include <bsp_uart.h>
#include "bsp_dump.h"
#include "bsp_dump_drv.h"
#include "bsp_dump_def.h"
#include "bsp_version.h"
#include "sre_err.h"
#include "bsp_dsp.h"
#include "bsp_dspload.h"
#include "bsp_om_version.h"
#include "securec.h"
#include "bsp_coresight.h"
#include "of.h"
#include "drv_nv_def.h"
#include "sre_callstack.h"
#include "securec.h"
#include "sre_symbol_api.h"
#include "osl_malloc.h"


/*lint -restore*/
/*lint --e{18 } */
#define DUMP_TASK_NUM_MAX 128
#define ISR_STACK_SIZE    0x2000    /* size of ISR stack, in bytes */


dump_global_info_t  *g_dump_global_info = BSP_NULL;
dump_base_info_t    *g_dump_base_info = BSP_NULL;
dump_task_info_t    *g_dump_task_info = BSP_NULL;
dump_regs_map_t     *g_dump_reg_map = BSP_NULL;
dump_ctrl_s          g_dump_ctrl;
NV_DUMP_STRU         g_dump_cfg = {{0}};
dump_hook           g_dump_trace_read_cb[DUMP_SYSVIEW_BUTT] = {BSP_NULL};
dump_debug_info_t   g_dump_ptr_info = {0};
dump_hook           g_intlock_in_hook = NULL;
dump_hook           g_intlock_out_hook = NULL;

volatile bool g_exc_flag = false;
/* ARM异常保存标志 */
bool g_arm_exc_save_flag = false;
bool g_rtosck_exc = false;
u32  g_dump_product_type = DUMP_PRODUCT_BUTT;
u32 g_pc_fun_list[10] = {0,};


void QueueInit(dump_queue_t *Q, u32 elementNum);
s32  QueueIn(dump_queue_t *Q, u32 element);
s32  QueueOut(dump_queue_t *Q, u32 *element);
s32  QueueReadLast(dump_queue_t *Q, u32 *element);
s32  QueueLoopIn(dump_queue_t *Q, u32 element);
int  QueueNumGet(dump_queue_t *Q);
s32  dump_vsnprintf(char *s, s32 n, const char *fmt, ...);
u32  dump_in_interrrupt(void);
void dump_task_switch_hook(u32 last_pid,u32 next_pid);
BOOL dump_exc_hook(EXC_INFO_S *pstExcInfo) ;
bool dump_check_reboot(void);
void dump_register_hook(void);
void dump_save_global_info(void);
void dump_save_base_info(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length);
void dump_save_log(void);
void dump_save_exc_task(u32 addr);
void dump_save_regs(void);
void dump_save_usr_data(char *data, u32 length);
void dump_save_ext(void);
void dump_wait_for_reboot(void);
void dump_wait_and_reboot(void);
void dump_save_all_task_tcb(s32 tid);
void dump_save_all_task_job(s32 tid);
void dump_save_all_task();
void dump_trace_stop(void);
void dump_system_error_enter(void);
void dump_notify_target(void);
void dump_int_handle(s32 param);
s32  dump_config_init(void);
void dump_map_init(void);
void dump_global_info_init(void);
void dump_base_info_init(void);
void dump_queue_t_init(void);
void dump_wait_save(void);
s32  dump_init_phase1(void);
s32  dump_task_init(void);
void dump_init_done(void);
s32  dump_init(void);
int QueueFrontDel(dump_queue_t *Q, u32 del_num);
extern void regcpy(void* dst, void* src, int size);
void dump_save_dtcm(void);
#ifdef CONFIG_BALONG_MODEM_RESET
extern void FIQ_IntHandle(void);
#endif



#define DUMP_T_TASK_ERROR(mod_id)      (mod_id & (1<<24))
#define DUMP_LINUX_TASK_NUM_MAX         128
#define DUMP_REG_SET_MAX                4096
#define DBG_DEMANGLE_PRINT_LEN 256  /* Num chars of demangled names to print */
#define DUMP_CALL_FUN_LEN 256  /* Num chars of demangled names to print */



#define rtpFromTaskGet(taskId)  (taskTcb(taskId)->rtpId)

void QueueInit(dump_queue_t *Q, u32 elementNum)
{
    Q->maxNum = elementNum;
    Q->front = 0;
    Q->rear = 0;
    Q->num = 0;

    /*lint --e{419 } */
    (void)memset_s((void *)Q->data,(size_t)(elementNum*sizeof(u32)), 0, (size_t)(elementNum*sizeof(u32)));
}

__inline__ s32 QueueIn(dump_queue_t *Q, u32 element)
{
    if (Q->num == Q->maxNum)
    {
        return -1;
    }

    Q->data[Q->rear] = element;
    Q->rear = (Q->rear+1) % Q->maxNum;
    Q->num++;

    return 0;
}

s32 QueueOut(dump_queue_t *Q, u32 *element)
{
    if (0 == Q->num)
    {
        return -1;
    }

    *element = Q->data[Q->front];
    Q->front = (Q->front+1) % Q->maxNum;
    Q->num--;

    return 0;
}

int QueueFrontDel(dump_queue_t *Q, u32 del_num)
{
    if (del_num > Q->num)
    {
        return -1;
    }
    Q->front = (Q->front+del_num) % Q->maxNum;
    Q->num   = Q->num - del_num;

    return 0;
}


s32 QueueReadLast(dump_queue_t *Q, u32 *element)
{
    if (0 == Q->num)
    {
        return -1;
    }

    *element = Q->data[((Q->rear+Q->maxNum)-1) % Q->maxNum];

    return 0;
}


__inline__ s32 QueueLoopIn(dump_queue_t *Q, u32 element)
{
    if (Q->num < Q->maxNum)
    {
        return QueueIn(Q, element);
    }
    else
    {
        Q->data[Q->rear] = element;
        Q->rear = (Q->rear+1) % Q->maxNum;
        Q->front = (Q->front+1) % Q->maxNum;
    }

    return 0;
}

/*lint -save -e586 -e737 -e775*/
s32 dump_vsnprintf(char *s, s32 n, const char *fmt, ...)
{
    /*lint -save -e830*/
    va_list vaList;/*lint !e40 !e522*/
    /*lint -restore +e830*/
    s32 len =0;
    /*lint -save -e530*/
    va_start(vaList, fmt);
    /*lint -restore +e830*/
    len = vsnprintf_s(s, 1024,(u32)n, fmt, vaList); /* [false alarm]:屏蔽Fortify错误 */
    va_end(vaList);
    return len;
}


int QueueNumGet(dump_queue_t *Q)
{
    return (int)Q->num;
}

u32 dump_in_interrrupt(void)
{
    OS_THREAD_TYPE_E type = SRE_CurThreadType();
    if (SYS_TASK== type || SYS_KERNEL == type)
    {
        return 1;
    }
    else if(SYS_HWI== type || SYS_SWI== type)
    {
        return 0;
    }
    return 2;

}
BOOL bsp_rtosck_exc_hook(EXC_INFO_S *pstExcInfo)
{
    if(g_dump_product_type == DUMP_PHONE && pstExcInfo->uwExcCause == OS_EXCEPT_FIQ)
    {

#ifdef CONFIG_BALONG_MODEM_RESET
        FIQ_IntHandle();
#endif
    }
    else
    {
        return dump_exc_hook(pstExcInfo);
    }
    return 1;

}

void bsp_dump_show_stack(void)
{
    char buf[256] = {'\0',};
    u32 puwMaxNum = 9;
    u32 i = 0;
    char* layers[10] = {"layer0","layer1","layer2","layer3","layer4","layer5","layer6","layer7","layer8","layer9"};
    char* pc_fun_name = NULL;

    SRE_GetCallStack(&puwMaxNum,g_pc_fun_list);

    /* coverity[overrun-buffer-val] */
    dump_vsnprintf(buf, 256, "[dump] ccore call trace is :\n");
    dmesg_write(buf, strlen(buf));
    memset_s(buf, 256, '\0', 256);

    for(i = 0; i < puwMaxNum;i++)
    {
        SRE_SymFindNameByAddr(((char*)g_pc_fun_list[i]), (&pc_fun_name));
        /* coverity[overrun-buffer-val] */
        dump_vsnprintf(buf , 256, "%s : 0x%x %s\n",layers[i],g_pc_fun_list[i],pc_fun_name);
        dmesg_write(buf, strlen(buf));
        memset_s(buf, 256, '\0', 256);
    }
}
void dump_task_switch_hook(u32 last_pid,u32 next_pid)
{
    /* 将要切换的任务ID和时间入队*/
    u32 addr = DUMP_TASK_SWITCH_ADDR;
    u32 tcb_addr = DUMP_TASK_TCB_ADDR;
    u32 old_tcb_pc;
    u32 tsk_addr;
    TSK_CB_S*  new_tcb = NULL;
    TSK_CONTEXT_S  tsk_context;
    unsigned long lock_key;

    if(BSP_FALSE == g_dump_global_info->internal_info.comm_internal.taskSwitchStart)
    {
        return;
    }

    if(TRUE == SRE_TaskIDCheck(next_pid))
    {

        if(SRE_TaskTcbAddrGet( last_pid, (u32*)&tsk_addr) == SRE_OK )
        {

            (void)SRE_TaskTcbAddrGet( next_pid, (u32*)&tsk_addr);
            new_tcb = (TSK_CB_S*)tsk_addr;
            (void)SRE_TaskContextGet(last_pid,&tsk_context);
            old_tcb_pc = tsk_context.uwPC;

            local_irq_save(lock_key);
            (void)QueueLoopIn((dump_queue_t *)tcb_addr, (u32)old_tcb_pc);
            (void)QueueLoopIn((dump_queue_t *)tcb_addr, om_timer_get());

            (void)QueueLoopIn((dump_queue_t *)addr, (u32)new_tcb->uwTaskPID);
            (void)QueueLoopIn((dump_queue_t *)addr, om_timer_get());
            local_irq_restore(lock_key);

            g_dump_base_info->current_task = (u32)new_tcb;

            g_dump_ptr_info.task_swt_ptr = DUMP_TASK_SWITCH_ADDR +0x10 + (((dump_queue_t *)addr)->rear )*4;
        }


    }
    if(BSP_NULL != g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH])
    {
        if( (QueueNumGet((dump_queue_t*)addr)*sizeof(u32)) >= DUMP_TASK_SWT_THRESHOLD_SIZE)
        {
            g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH]();
        }
    }

    return;

}

void dump_int_entry_hook(u32 newVec)
{
    u32 addr = DUMP_TASK_SWITCH_ADDR;
    unsigned long lock_key;

    if(BSP_FALSE == g_dump_global_info->internal_info.comm_internal.taskSwitchStart)
    {
        return;
    }

    local_irq_save(lock_key);
    (void)QueueLoopIn((dump_queue_t *)addr, (((u32)DUMP_INT_IN_FLAG<<16)|newVec));
    (void)QueueLoopIn((dump_queue_t *)addr, om_timer_get());
    local_irq_restore(lock_key);

    g_dump_ptr_info.task_swt_ptr = DUMP_TASK_SWITCH_ADDR +0x10
                                                            + (((dump_queue_t *)addr)->rear )*4;

    if(BSP_NULL != g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH])
    {
        if( (QueueNumGet((dump_queue_t *)addr)*sizeof(u32)) >= DUMP_TASK_SWT_THRESHOLD_SIZE)
        {
            g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH]();
        }
    }

    g_dump_base_info->current_int = newVec;

    return;
}
void dump_int_exit_hook(u32 newVec)
{
    u32 addr = DUMP_TASK_SWITCH_ADDR;
    unsigned long lock_key;

    if(BSP_FALSE == g_dump_global_info->internal_info.comm_internal.taskSwitchStart)
    {
        return;
    }

    local_irq_save(lock_key);
    (void)QueueLoopIn((dump_queue_t *)addr, (((u32)DUMP_INT_EXIT_FLAG<<16)|newVec));
    (void)QueueLoopIn((dump_queue_t *)addr, om_timer_get());
    local_irq_restore(lock_key);

    g_dump_ptr_info.task_swt_ptr = DUMP_TASK_SWITCH_ADDR +0x10
                                                            + (((dump_queue_t *)addr)->rear )*4;

    if(BSP_NULL != g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH])
    {
        if( (QueueNumGet((dump_queue_t *)addr)*sizeof(u32)) >= DUMP_TASK_SWT_THRESHOLD_SIZE)
        {
            g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH]();
        }
    }

    g_dump_base_info->current_int = newVec;

    return;

}


exc_hook g_dump_exc_hook = NULL;
BOOL dump_exc_hook(EXC_INFO_S *pstExcInfo)
{
    dump_trace_stop();
    SRE_ExcInfoPrintf(pstExcInfo);

    if(NULL != g_dump_exc_hook)
    {
        if(g_dump_exc_hook(pstExcInfo) == true)
        {
            return 1;
        }
    }
    
    if(g_arm_exc_save_flag == true || g_exc_flag == true)
    {
        return BSP_OK;
    }
    
    g_rtosck_exc = true;

    g_dump_base_info->vec = (u32)pstExcInfo->stRegInfo.uwPC;
    g_dump_base_info->cpsr = (u32)pstExcInfo->stRegInfo.uwCPSR;
    g_dump_base_info->current_task = (u32)(-1);
    g_pdump_info->p_dump->dump_head.except_reason= DUMP_REASON_ARM;


    /*拷贝寄存器信息*/
    (void)memcpy_s((void * )(g_dump_base_info->regSet), (size_t)(16*sizeof(u32)),(void*)&(pstExcInfo->stRegInfo.uwR0), (size_t)(16*sizeof(u32)));/* [false alarm]:fortify */
    g_dump_base_info->regSet[16] = (u32)pstExcInfo->stRegInfo.uwCPSR;

    /* 寄存器信息保存完毕，防止重复记录 */
    g_arm_exc_save_flag = true;

    /*进行全局复位*/
    /* coverity[sleep] */
    system_error(DRV_ERRNO_DUMP_ARM_EXC, DUMP_REASON_ARM, 0, 0, 0);;

    /* 中断上下文中ARM异常，退出excExcHandle */
    return 1;

}

s32 dump_exc_register(exc_hook func)
{
    if(func == NULL)
    {
        dump_fetal("register func is null\n");
        return BSP_ERROR;
    }

    g_dump_exc_hook = func;
    return BSP_OK;
}

/*lint -restore */

bool dump_check_reboot(void)
{
    /* 先检查ACORE */
    if((DUMP_START_EXCH == g_dump_global_info->internal_info.app_internal.start_flag)
        || (DUMP_START_EXCH == g_dump_global_info->internal_info.comm_internal.start_flag)
        ||(DUMP_START_EXCH == g_dump_global_info->internal_info.m3_internal.start_flag))
    {
        /* 异常重启*/
        return (bool)BSP_FALSE;
    }
    else if((DUMP_START_REBOOT == g_dump_global_info->internal_info.app_internal.start_flag)
        || (DUMP_START_REBOOT == g_dump_global_info->internal_info.comm_internal.start_flag))
    {
        return (bool)BSP_TRUE;
    }
    else if((DUMP_START_CRASH == g_dump_global_info->internal_info.app_internal.start_flag)
        || (DUMP_START_CRASH == g_dump_global_info->internal_info.comm_internal.start_flag))
    {
        return (bool)BSP_FALSE;
    }
    else
    {
        dump_fetal("check reboot, use default state!.flag = 0x%x 0x%x\n",
            g_dump_global_info->internal_info.app_internal.start_flag,
            g_dump_global_info->internal_info.comm_internal.start_flag);
        return (bool)BSP_TRUE;
    }
}


void dump_register_hook(void)
{
    u32 ret;
    /*向操作系统注册钩子函数*/
    if(1 == g_dump_cfg.dump_cfg.Bits.taskSwitch)
    {

        ret = SRE_TaskSwitchHookAdd((OS_VOID_FUNC)dump_task_switch_hook);

        if(BSP_OK != ret)
        {
            dump_error("dump_register_hook: reg task hook failed!\n");
        }

    }
    if(1 == g_dump_cfg.dump_cfg.Bits.intSwitch)
    {

        (void)SRE_HwiEntryHookAdd(dump_int_entry_hook);
        (void)SRE_HwiExitHookAdd(dump_int_exit_hook);
    }
    if(1 == g_dump_cfg.dump_cfg.Bits.ARMexc)
    {
        (void)SRE_ExcRegHook(bsp_rtosck_exc_hook);
    }

    /*缺看门狗中断*/

    g_dump_global_info->internal_info.comm_internal.taskSwitchStart = BSP_TRUE;
    g_dump_global_info->internal_info.comm_internal.IntSwitchStart = BSP_TRUE;

    return;
}

__inline__ void dump_save_global_info(void)
{
    //如果是上层复位，标志复位状态
    if(DUMP_REASON_UNDEF == g_pdump_info->p_dump->dump_head.except_reason)
    {
        g_pdump_info->p_dump->dump_head.except_reason = DUMP_REASON_NORMAL;
    }

    g_pdump_info->p_dump->dump_head.except_core= DUMP_CPU_COMM;
    g_pdump_info->p_dump->dump_head.except_time= om_timer_tick_get();
    g_dump_global_info->internal_info.comm_internal.start_flag = DUMP_START_EXCH;

    return;

}

void dump_save_base_info(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{

    TSK_INFO_S  task_info;
    u32 type = dump_in_interrrupt();


    if(BSP_MODU_OTHER_CORE == mod_id)
    {
        g_dump_base_info->reboot_task = (u32)(-1);
        g_dump_base_info->reboot_int = (u32)(-1);
    }
    else
    {
        /* 当前处于任务 */
        if (type == 1)
        {
            //if(!DUMP_T_TASK_ERROR(mod_id))
            if(mod_id == 0x11000025 || mod_id == 0x1100002A)
            {
                g_dump_base_info->reboot_task = arg1;/* [false alarm]:fortify */
            }
            else
            {

                g_dump_base_info->reboot_task = g_dump_base_info->current_task;
            }
            if(NULL != (void*)g_dump_base_info->reboot_task)
            {
                (void)SRE_TaskInfoGet  ( ((TSK_CB_S*)(g_dump_base_info->reboot_task))->uwTaskPID, &task_info );
                (void)memcpy_s(g_dump_base_info->taskName,16, task_info.acName, 16);
            }
            g_dump_base_info->reboot_int = (u32)(-1);
        }
        /* 当前处于中断 */
        else if(type == 0)
        {
            g_dump_base_info->reboot_task = (u32)(-1);
            (void)memset_s(g_dump_base_info->taskName, sizeof(g_dump_base_info->taskName),0, sizeof(g_dump_base_info->taskName));
            g_dump_base_info->reboot_int = g_dump_base_info->current_int;
        }
    }

    /*记录当前状态是任务态还是中断态*/
    if (type == 1)
    {
        g_dump_base_info->reboot_context = DUMP_CTX_TASK;
    }
    else if(type == 0)
    {
        g_dump_base_info->reboot_context = DUMP_CTX_INT;
    }

    g_dump_base_info->modId = mod_id;
    g_dump_base_info->arg1 = arg1;
    g_dump_base_info->arg2 = arg2;
    g_dump_base_info->arg3 = (u32)data;
    g_dump_base_info->arg3_length = length;

    return;
}


void dump_save_log(void)
{
    (void)dmesg_save((char*)DUMP_PRINT_ADDR, DUMP_PRINT_SIZE);
}

/* 中断栈地址 */
extern unsigned int __SP_INIT;
extern unsigned int __SP_END;

void show_int_stack(void)
{
    dump_fetal("SP_INIT: 0x%x, SP_END: 0x%x\n", (u32)&__SP_INIT, (u32)&__SP_END);
}

typedef void(*dump_regs_func)(u32 addr, u32 stack_addr, u32 stack_len);

dump_regs_func g_dump_regs_func;
/*lint -save -e123 -e586 */
void dump_save_arm_regs(u32 addr, u32 stack_addr, u32 stack_len)
{
    u32 int_stack_base;
    u32 int_stack_len;

    /* ARM异常，寄存器信息已经保存 */
    if(g_arm_exc_save_flag != true)
    {
        asm volatile(
            "str r0, [r0,#0x00]\n"
            "str r1, [r0,#0x04]\n"
            "str r2, [r0,#0x08]\n"
            "str r3, [r0,#0x0C]\n"
            "str r4, [r0,#0x10]\n"
            "str r5, [r0,#0x14]\n"
            "str r6, [r0,#0x18]\n"
            "str r7, [r0,#0x1C]\n"
            "str r8, [r0,#0x20]\n"
            "str r9, [r0,#0x24]\n"
            "str r10, [r0,#0x28]\n"
            "str r11, [r0,#0x2C]\n"
            "str r12, [r0,#0x30]\n"
            "str r14, [r0,#0x38]\n"
            "push {r1}\n"
            "str r13, [r0,#0x34]\n"
            "mov r1, pc\n"
            "str r1, [r0,#0x3C]\n"
            "mrs r1, cpsr\n"
            "str r1, [r0,#0x40]\n"
            "pop {r1}\n"
        );
    }
    /* 保存任务栈 */
    (void)memcpy_s((void * )DUMP_TASK_STACK_ADDR, stack_len,(void * )(stack_addr), stack_len);

    /* 保存中断栈 */
    int_stack_len  = (u32)&__SP_END - (u32)&__SP_INIT;
    int_stack_len  = (int_stack_len > DUMP_INT_STACK_SIZE) ? DUMP_INT_STACK_SIZE : int_stack_len;
    int_stack_base = (u32)&__SP_END - int_stack_len;
    g_dump_base_info->int_stack_base = (u32)&__SP_END;
    g_dump_base_info->int_stack_end  = (u32)&__SP_INIT;
    (void)memcpy_s((void * )DUMP_INT_STACK_ADDR, int_stack_len,(void *)int_stack_base, int_stack_len);
}
/*lint -restore*/
void dump_save_exc_task(u32 addr)
{
    u32 cur_pid = 0;
    u32 tcb_addr;
    TSK_CB_S* ptcb = NULL;
    u32 len;
    STACK_INFO_S statck_info;
    u32 stack_addr;

    (void)SRE_TaskSelf(&cur_pid);
    (void)SRE_TaskTcbAddrGet(cur_pid ,(u32*)&tcb_addr);
    ptcb = (TSK_CB_S*)tcb_addr;
    (void)SRE_TaskStackInfoGet  ( cur_pid, &statck_info) ;
    g_dump_base_info->current_task = (u32)ptcb;

    /* 保存任务栈 */
    len = statck_info.uwBottom - statck_info.uwTop;
    len = (len > DUMP_TASK_STACK_SIZE) ? DUMP_TASK_STACK_SIZE : len;

    stack_addr = statck_info.uwBottom - len;
    g_dump_regs_func(addr, stack_addr, len);

    return;
}

/*lint -save -e713 -e732 -e737 -e746 -e115 -e40 -e550 -e420 -e438*/
void dump_save_regs(void)
{
    s32 size;

    if(g_dump_cfg.dump_cfg.Bits.commRegSave1)
    {
        size = (g_dump_cfg.commRegSize1< DUMP_REG_SET_MAX) ? g_dump_cfg.commRegSize1 : DUMP_REG_SET_MAX;
        regcpy((void*)(DUMP_REGS_ADDR + sizeof(dump_regs_map_t)), (void*)g_dump_cfg.commRegAddr1, size);
        g_dump_reg_map->reg_addr1 = g_dump_cfg.commRegAddr1;
        g_dump_reg_map->reg_size1 = size;
    }
    if(g_dump_cfg.dump_cfg.Bits.commRegSave2)
    {
        size = (g_dump_cfg.commRegSize2 < DUMP_REG_SET_MAX) ? g_dump_cfg.commRegSize2 : DUMP_REG_SET_MAX;
        regcpy((void*)(DUMP_REGS_ADDR+ DUMP_REG_SET_MAX), (void*)g_dump_cfg.commRegAddr2, size);
        g_dump_reg_map->reg_addr2 = g_dump_cfg.commRegAddr2;
        g_dump_reg_map->reg_size2 = size;
    }
    if(g_dump_cfg.dump_cfg.Bits.commRegSave3)
    {
        size = (g_dump_cfg.commRegSize3 < (DUMP_REG_SET_MAX-sizeof(dump_regs_map_t)))
            ? g_dump_cfg.commRegSize3
            : (DUMP_REG_SET_MAX-sizeof(dump_regs_map_t));
        regcpy((void*)(DUMP_REGS_ADDR+ DUMP_REG_SET_MAX*2), (void*)g_dump_cfg.commRegAddr3, size);
        g_dump_reg_map->reg_addr3 = g_dump_cfg.commRegAddr3;
        g_dump_reg_map->reg_size3 = size;
    }

    return;
}


void dump_save_usr_data(char *data, u32 length)
{
    s32 len;

    /*保存用户信息*/
    dump_field_map_t* p_field = (dump_field_map_t*)bsp_dump_get_field_map(DUMP_CP_USER_DATA);

    if(p_field == BSP_NULL)
    {
        return;
    }

    if((NULL==data)||(0== length))
    {
        p_field->length = 0;
        return;
    }

    len = (length > DUMP_USER_DATA_SIZE) ? DUMP_USER_DATA_SIZE : length;
    (void)memcpy_s((void *)DUMP_USER_DATA_ADDR, (size_t)len,(const void *)data, (size_t)len); /* [false alarm]:屏蔽Fortify错误 */
    p_field->length = len;
    return;

}

#define dump_save_comm_done()\
    do{\
        g_dump_global_info->internal_info.comm_internal.save_flag = DUMP_SAVE_SUCCESS;\
    }while(0)

#define dump_save_ext_done()\
    do{\
        g_dump_global_info->internal_info.comm_internal.ext_save_flag = DUMP_SAVE_SUCCESS;\
    }while(0)


void dump_save_ext(void)
{
     struct list_head* cur = NULL;
     dump_field_hook_t* pfieldhook = NULL;
     unsigned long flags =0;
     dump_area_head_t*  p_head  = (dump_area_head_t*)g_pdump_info->p_cur_area;
     dump_field_map_t*  p_field = (dump_field_map_t*)g_pdump_info->p_cur_area->fields;
     u32 i;
     u32 * f_addr;
    /*lint -save -e830 -e539*/
    list_for_each(cur, &g_pdump_info->cur_hook_list.hook_list)
    {
        spin_lock_irqsave(&g_pdump_info->lock, flags);
        pfieldhook = list_entry(cur, dump_field_hook_t, hook_list);
        spin_unlock_irqrestore(&g_pdump_info->lock, flags);

        if(pfieldhook->pfunc)
        {
             pfieldhook->pfunc();
        }
     }

     /* 保存自带地址注册区域 */
     for(i=0; i<p_head->field_num; i++, p_field++)
     {
         f_addr = (u32 *)((u8 *)p_head + p_field->offset_addr);
         if(DUMP_FIELD_MAGIC_NUM == *f_addr)
         {
             (void)memcpy_s((u8 *)f_addr, p_field->length,(u8 *)(*(f_addr + 1)), p_field->length);
          }
     }
    /*lint -restore +e830 +e539*/
     dump_save_ext_done();
     return;

}

/*lint -save -e506*/
__inline__ void dump_wait_for_reboot(void)
{
    /* coverity[no_escape] */
    do{
    }while(1);
}
/*lint -restore*/
void dump_wait_and_reboot(void)
{
#define DUMP_WAIT_MAX   500   //2S
    s32 time_start, time_cur;
    int flag = 1;

    time_start = om_timer_tick_get();
    dump_debug("save_file_flag=0x%x\n", g_dump_global_info->internal_info.app_internal.save_file_flag);

    do{
        time_cur = om_timer_tick_get();
        if(DUMP_WAIT_MAX < (time_cur - time_start))
        {
            dump_debug("long time: %d %d %d %d\n", time_start, time_cur);
            break;
        }
    }while(flag);

    /* 配置DDR进入自刷新 */

    /* 重启系统 */
    dump_fetal("system_reboot\n");
    g_dump_global_info->internal_info.app_internal.save_file_flag = DUMP_SAVE_FILE_NEED;
    if((1 == g_dump_cfg.dump_cfg.Bits.sysErrReboot) && (DUMP_MBB == g_dump_product_type))
    {
        bsp_drv_power_reboot_direct();
    }
}

void dump_save_all_task_tcb(s32 tid)
{
    s32 i;
    s32 task_num = 0;
    dump_task_info_t *task_info;
    u32 buffer = (u32)DUMP_ALLTASK_ADDR;
    u32 taskIdList[DUMP_TASK_NUM_MAX] = {0};
    u8 task_name[12] = {0};
    u32 tcb_addr = 0;
    TSK_CB_S *ptcb = NULL;
    TSK_INFO_S tsk_info;
    STACK_INFO_S  statck_info;
    TSK_CONTEXT_S   tsk_context;

    /*获得当前所有任务ID*/
    task_num = DUMP_TASK_NUM_MAX;
    (void)SRE_TaskIDList((u16*)&task_num,taskIdList);
    if (task_num > DUMP_TASK_NUM_MAX)
    {
        task_num = DUMP_TASK_NUM_MAX;
    }
    //(void)SRE_Printf("Enter dump_save_all_task_tcb\n");

    /*根据任务ID获得NAME，并放到指定内存中*/
    for (i = 0; i < task_num; i++)
    {
        (void)SRE_TaskInfoGet  ( taskIdList[i],  &tsk_info);
        (void)strncpy_s((char *)task_name, 12,tsk_info.acName, 11);
        (void)QueueLoopIn((dump_queue_t *)buffer, (u32)taskIdList[i]);
        (void)QueueLoopIn((dump_queue_t *)buffer, *((u32 *)(task_name)));
        (void)QueueLoopIn((dump_queue_t *)buffer, *((u32 *)(task_name+4)));
        (void)QueueLoopIn((dump_queue_t *)buffer, *((u32 *)(task_name+8)));
    }
    for (i = 0; i < (s32)task_num; i++)
    {
        /* 首先保存任务信息*/
        (void)SRE_TaskTcbAddrGet  ( taskIdList[i], &tcb_addr) ;
        ptcb = (TSK_CB_S *)tcb_addr;
        (void)SRE_TaskStackInfoGet  ( taskIdList[i], &statck_info) ;
        (void)SRE_TaskInfoGet  ( taskIdList[i],  &tsk_info);
        (void)SRE_TaskContextGet(taskIdList[i], &tsk_context );


        task_info = &g_dump_task_info[i];
        task_info->pid = ptcb->uwTaskPID;
        task_info->entry = (u32)ptcb->pfnTaskEntry;
        task_info->status = ptcb->usTaskStatus;
        task_info->policy = TASK_SCHED_RR;
        task_info->priority = ptcb->usPriority;
        task_info->stack_base = (u32)statck_info.uwBottom;
        task_info->stack_end = (u32)statck_info.uwTop;
        task_info->stack_high = statck_info.uwPeakUsed;
        task_info->stack_current = statck_info.uwCurrUsed;
        /* coverity[buffer_size_warning] */
        (void)strncpy_s((void*)task_info->name, 16,(void*)tsk_info.acName, 15);
        (void)memcpy_s((void *)(task_info->regs),13*sizeof(u32), (void *)(tsk_context.auwR), 13*sizeof(u32));
        task_info->regs[13] = statck_info.uwSP;
        task_info->regs[14] = tsk_context.uwLR;
        task_info->regs[15] = tsk_context.uwPC;
        task_info->regs[16] = tsk_context.uwCPSR;

        /*暂时不进行异常栈的推导*/
        //dump_task_show_stack(task_info->pid, task_info->dump_stack, DUMP_TASK_INFO_STACK_SIZE);
        if(tid == ptcb->uwTaskPID)
        {
            memcpy_s(task_info->dump_stack, sizeof(g_pc_fun_list), g_pc_fun_list, sizeof(g_pc_fun_list));
        }
    }

    return;
}

void dump_save_all_task_job(s32 tid)
{
    dump_save_all_task_tcb(tid);

    /*保存打印信息*/
    dump_save_log();

    /* 保存DSP DTCM */
    dump_save_dtcm();

    /*COMM数据保存完成 */
    dump_save_comm_done();

    (void)osl_cache_flush(OSL_DATA_CACHE, (void *)DDR_MCORE_ADDR, DDR_MCORE_SIZE);

    /*如果不是rtosck系统异常主动出发系统异常，保存CDA文件 */
    if(g_rtosck_exc == false)
    {
        //dump_save_cda_info();
    }

    return;
}


void dump_save_all_task()
{

    dump_save_all_task_job((s32)g_dump_base_info->reboot_task);
    return; /*clean lint e713*/
}


void dump_trace_stop(void)
{
    bsp_coresight_disable();
    (void)SRE_TaskSwitchHookDelete(dump_task_switch_hook);
    (void)SRE_HwiEntryHookDel(dump_int_entry_hook);
    (void)SRE_HwiExitHookDel(dump_int_exit_hook);
    g_dump_global_info->internal_info.comm_internal.taskSwitchStart = BSP_FALSE;
    g_dump_global_info->internal_info.comm_internal.IntSwitchStart = BSP_FALSE;

    return;
}

void dump_system_error_enter(void)
{
    /* 停止记录任务切换/中断等 */
    dump_trace_stop();

    /* 禁止抢占 */
//    local_irq_save();

    return;
}

void dump_notify_target(void)
{
    (void)bsp_ipc_int_send(IPC_CORE_ACORE, IPC_ACPU_SRC_CCPU_DUMP);
}

void dump_int_handle(s32 param)
{
    char buf[256] = {'\0',};
    param = param; /* [false alarm]:屏蔽Fortify错误 */
    /* 已经发生异常，或者未初始化，不记录 */
    if(g_exc_flag == true || g_dump_global_info == NULL)
    {
        return;
    }
    else
    {
        g_exc_flag = true;
    }
    /* coverity[overrun-buffer-val] */
    dump_vsnprintf(buf,256,"[0x%x][dump]: <%s> acore enter system error \n", om_timer_get(), __FUNCTION__);
    dmesg_write(buf, strlen(buf));

    if(g_dump_global_info->internal_info.comm_internal.init_flag != DUMP_INIT_FLAG)
    {
        return;
    }
    bsp_dump_show_stack();


    /*先停止etb*/
    dump_system_error_enter();
     /*保存异常任务信息*/
    dump_save_exc_task((u32)(&(g_dump_base_info->regSet[0])));




    if(DUMP_INIT_FLAG != g_dump_global_info->internal_info.comm_internal.init_flag)
    {
        if(g_dump_global_info->internal_info.dump_mode == DUMP_MODE_NORMAL)
        {
            /*等待重启*/
            /*lint -save -e522*/
            dump_wait_for_reboot();
            /*lint -restore*/
            
        }
        return;

    }
    /* 首先保存系统异常基本信息 */
    dump_save_base_info(BSP_MODU_OTHER_CORE, 0, 0, BSP_NULL, 0);

    /*保存寄存器信息*/
    dump_save_regs();

    /* 保存扩展区数据 */
    dump_save_ext();

    /*保存所有任务信息*/
    dump_save_all_task_tcb(g_dump_base_info->reboot_task);

    /*保存打印信息*/
    dump_save_log();
    
    if(g_dump_global_info->internal_info.dump_mode == DUMP_MODE_NORMAL)
    {
        /* 保存DSP DTCM */
        dump_save_dtcm();

        /*强制进行BBE16的DTCM的备份，用于dump模块备份*/
        bsp_dsp_store_tcm_force();
    }
    /*COMM数据保存完成 */
    dump_save_comm_done();

    (void)osl_cache_flush(OSL_DATA_CACHE, (void *)DDR_MCORE_ADDR, DDR_MCORE_SIZE);

    if(g_dump_global_info->internal_info.dump_mode == DUMP_MODE_NORMAL)
    {

        /*ap异常等待重启*/
        /*lint -save -e522*/
        dump_wait_for_reboot();
        /*lint -restore +e522*/
    }

    return;
}
/*lint -save -e830 -e539*/

dump_product_type_t dump_get_product_type(void)
{
    struct device_node *node = NULL;
    const char * product_type;

    if(g_dump_product_type != DUMP_PRODUCT_BUTT)
    {
        return g_dump_product_type;
    }
    /* 读取当前产品形态 */
    node = of_find_compatible_node(NULL, NULL, "hisilicon,smntn_type");
    if (!node)
    {
        dump_fetal("dts node mntn type not found!\n");
        return BSP_ERROR;
    }

    if(of_property_read_string(node, "product_type", &product_type))
    {
        dump_fetal("read product_type failed!\n");
        return BSP_ERROR;
    }

    if(0 == strncmp(product_type, "MBB", strlen("MBB")))
    {
        return DUMP_MBB;
    }
    else if(0 == strncmp(product_type, "PHONE", strlen("PHONE")))
    {
        return DUMP_PHONE;
    }
     return DUMP_PRODUCT_BUTT;

}
/*lint -restore +e830 +e539*/

s32 dump_config_init(void)
{
    s32 ret = BSP_ERROR;


    ret = bsp_nvm_read(NVID_DUMP, (u8*)&g_dump_cfg, sizeof(NV_DUMP_STRU));
    if (BSP_OK != ret)
    {
        /*使用默认值*/
        g_dump_cfg.dump_cfg.Bits.dump_switch     = 0x1;
        g_dump_cfg.dump_cfg.Bits.ARMexc          = 0x1;
        g_dump_cfg.dump_cfg.Bits.stackFlow       = 0x1;
        g_dump_cfg.dump_cfg.Bits.taskSwitch      = 0x1;
        g_dump_cfg.dump_cfg.Bits.intSwitch       = 0x1;
        g_dump_cfg.dump_cfg.Bits.intLock         = 0x1;
        g_dump_cfg.dump_cfg.Bits.appRegSave1     = 0x0;
        g_dump_cfg.dump_cfg.Bits.appRegSave2     = 0x0;
        g_dump_cfg.dump_cfg.Bits.appRegSave3     = 0x0;
        g_dump_cfg.dump_cfg.Bits.commRegSave1    = 0x0;
        g_dump_cfg.dump_cfg.Bits.commRegSave2    = 0x0;
        g_dump_cfg.dump_cfg.Bits.commRegSave3    = 0x0;
        g_dump_cfg.dump_cfg.Bits.sysErrReboot    = 0x1;
        g_dump_cfg.dump_cfg.Bits.reset_log       = 0x1;
        g_dump_cfg.dump_cfg.Bits.fetal_err       = 0x1;
        dump_error("[dump]: read NV failed, use the default value!.ret = %d nv id = 0x%x\n", ret, NVID_DUMP);
    }
    g_dump_product_type = dump_get_product_type();

    return BSP_OK;
}

void dump_map_init(void)
{
    unsigned long flags = 0;
    char* str_tmp;
    u32 base_addr  = 0;
    dump_area_head_t*  p_head  = (dump_area_head_t*)g_pdump_info->p_cur_area;
    dump_field_map_t*  p_field = (dump_field_map_t*)g_pdump_info->p_cur_area->fields;
    dump_load_info_t * dump_load;
    u8 * sysctrl_addr;

    dump_load = (dump_load_info_t *)DUMP_LOAD_INFO_ADDR;
    dump_load->mdm_ddr  = DDR_MCORE_ADDR;
    dump_load->mdm_share= DDR_SHARED_MEM_ADDR;
    dump_load->mdm_dump = DDR_MNTN_ADDR;
    dump_load->mdm_sram = HI_SRAM_MEM_ADDR;
    dump_load->mdm_dts  = DDR_MCORE_DTS_ADDR;

    /* 初始化AREA HEAD区域 */
    p_head->magic_num = DUMP_CP_MAGIC_NUM;
    (void)strncpy_s((char*)p_head->name,8, DUMP_CP_AREA_NAME, 7);          /* [false alarm]:屏蔽Fortify错误 */
    /* coverity[secure_coding] */
    str_tmp = (char*)bsp_version_get_firmware();
    if(str_tmp)
    {
        (void)strncpy_s((char*)p_head->version, 16,str_tmp ,15); /* [false alarm]:屏蔽Fortify错误 */
    }

    /* 注册DUMP静态区域 */
    spin_lock_irqsave(&g_pdump_info->lock, flags);
    base_addr = (u32)g_pdump_info->p_cur_area;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_BASE_INFO,       "BASE_INFO",   base_addr,DUMP_BASE_INFO_ADDR, DUMP_BASE_INFO_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_TASK_SWITCH,     "TASK_SWITCH", base_addr,DUMP_TASK_SWITCH_ADDR, DUMP_TASK_SWITCH_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_INTLOCK,         "INTLOCK",     base_addr,DUMP_INTLOCK_ADDR,          DUMP_INTLOCK_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_TASK_STACK,      "TASK_STACK",  base_addr,DUMP_TASK_STACK_ADDR,       DUMP_TASK_STACK_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_INT_STACK,       "INT_STACK",   base_addr,DUMP_INT_STACK_ADDR,        DUMP_INT_STACK_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_ALLTASK,         "TASK_NAME",   base_addr,DUMP_ALLTASK_ADDR,          DUMP_ALLTASK_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_ALLTASK_TCB,     "ALLTASK_TCB", base_addr,DUMP_ALLTASK_TCB_ADDR,      DUMP_ALLTASK_TCB_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_PRINT,           "PRINT",       base_addr,DUMP_PRINT_ADDR,            DUMP_PRINT_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_DMESG,           "DMESG",       base_addr,DUMP_DMESG_ADDR,            DUMP_DMESG_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_REGS,            "REGS",        base_addr,DUMP_REGS_ADDR,             DUMP_REGS_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_CPUVIEW,         "CPUVIEW",     base_addr,DUMP_CPUVIEW_ADDR,          DUMP_CPUVIEW_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_USER_DATA,       "USER_DATA",   base_addr,DUMP_USER_DATA_ADDR,        DUMP_USER_DATA_SIZE)
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_RTOSCK_CDA,      "RTOSCK_CDA",  base_addr,DUMP_EXT_OM_RTOSCK_CDA_ADDR,DUMP_EXT_OM_RTOSCK_CDA_SIZE);
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_CP_TASK_TCB,        "TASK_TCB",    base_addr,DUMP_TASK_TCB_ADDR,         DUMP_TASK_TCB_SIZE);
    g_pdump_info->cur_field_num++;/* [false alarm]:fortify */
    p_head->field_num = g_pdump_info->cur_field_num;
    spin_unlock_irqrestore(&g_pdump_info->lock, flags);

    sysctrl_addr = bsp_dump_register_field(DUMP_CP_SYSCTRL, "SYSCTRL", 0, 0, 0x3000, 0);
    if(sysctrl_addr == NULL)
    {
        dump_fetal("register sysctrl field fail\n");
    }
    else
    {
        (void)memset_s(sysctrl_addr, 0x3000, 0, 0x3000);
    }

    g_dump_global_info = (dump_global_info_t *)DUMP_GLOBAL_INFO_ADDR;
    g_dump_base_info = (dump_base_info_t*)DUMP_BASE_INFO_ADDR;
    g_dump_task_info = (dump_task_info_t*)DUMP_ALLTASK_TCB_ADDR;
    g_dump_reg_map   = (dump_regs_map_t*)DUMP_REGS_ADDR;

    g_dump_reg_map->reg_addr1 = 0;
    g_dump_reg_map->reg_size1 = 0;
    g_dump_reg_map->reg_addr2 = 0;
    g_dump_reg_map->reg_size2 = 0;
    g_dump_reg_map->reg_addr3 = 0;
    g_dump_reg_map->reg_size3 = 0;

    return;
}

void dump_global_info_init(void)
{
    g_dump_global_info->internal_info.comm_internal.start_flag = DUMP_START_CRASH;
    g_dump_global_info->internal_info.comm_internal.save_flag = BSP_FALSE;
    g_dump_global_info->internal_info.comm_internal.ext_save_flag = BSP_FALSE;
    g_dump_global_info->internal_info.comm_internal.inInterrupt = 0;
    g_dump_global_info->internal_info.comm_internal.taskSwitchStart = BSP_FALSE;
    g_dump_global_info->internal_info.comm_internal.IntSwitchStart = BSP_FALSE;
}

void dump_base_info_init(void)
{
    int i;

    (void)memset_s(g_dump_base_info, sizeof(dump_base_info_t),0, sizeof(dump_base_info_t));
    g_dump_base_info->vec = DUMP_ARM_VEC_UNKNOW;

    (void)memset_s(g_dump_reg_map, sizeof(dump_regs_map_t),0, sizeof(dump_regs_map_t));

    (void)memset_s((void*)DUMP_ALLTASK_TCB_ADDR, DUMP_ALLTASK_TCB_SIZE,0, DUMP_ALLTASK_TCB_SIZE); /* [false alarm]:屏蔽Fortify错误 */
    for(i=0; i<DUMP_LINUX_TASK_NUM_MAX; i++)
    {
        g_dump_task_info[i].pid = 0xffffffff;
    }
    /*确认RTOSCK的中断栈是多大?*/
    g_dump_base_info->int_stack_base = (u32)-1;
    g_dump_base_info->int_stack_end  = (u32)-1;

    (void)strcpy_s((char*)g_dump_base_info->version,sizeof(g_dump_base_info->version), (char*)bsp_version_get_firmware());
    (void)strcpy_s((char*)g_dump_base_info->compile_time, sizeof(g_dump_base_info->compile_time),(char*)bsp_version_get_build_date_time());
}

void dump_queue_t_init(void)
{
    /* 初始化任务切换队列 */
    QueueInit((dump_queue_t *)(DUMP_TASK_SWITCH_ADDR), (DUMP_TASK_SWITCH_SIZE - 0x10) / 0x4);
    g_dump_ptr_info.task_swt_ptr = DUMP_TASK_SWITCH_ADDR +0x10;

    /* 初始化中断队列 */
    QueueInit((dump_queue_t *)(DUMP_INTLOCK_ADDR), (DUMP_INTLOCK_SIZE - 0x10) / 0x4);
    g_dump_ptr_info.int_lock_ptr= DUMP_INTLOCK_ADDR +0x10;

    /* 初始化任务名队列 */
    QueueInit((dump_queue_t *)(DUMP_ALLTASK_ADDR), (DUMP_ALLTASK_SIZE - 0x10) / 0x4);

    QueueInit((dump_queue_t *)(DUMP_TASK_TCB_ADDR), (DUMP_TASK_TCB_SIZE - 0x10) / 0x4);

    return;
}

void dump_wait_save(void)
{
    int flag = 1;

    g_dump_global_info = (dump_global_info_t*)DUMP_GLOBAL_INFO_ADDR;

    do{
        if(DUMP_INIT_FLAG_WAIT == g_dump_global_info->internal_info.comm_internal.start_wait_flag)
            break;
        (void)osl_task_delay(1);
    }while(flag);

    g_dump_global_info->internal_info.comm_internal.start_wait_flag = 0;
}

s32 dump_init_phase1(void)
{
    s32 ret;/* [false alarm]:fortify */

    /*获取配置*/
    ret = dump_config_init();/* [false alarm]:fortify */
    if(BSP_OK != ret)/* [false alarm]:fortify */
    {
        /* 读取配置失败，异常处理*//* [false alarm]:fortify */
    }

    return BSP_OK;
}

s32 dump_task_init(void)
{
    s32 ret;
    /* 注册中断 */
    ret = bsp_ipc_int_connect(IPC_CCPU_SRC_ACPU_DUMP, (voidfuncptr)dump_int_handle, 0);
    if(BSP_OK != ret)
    {
        dump_error("bsp_ipc_int_connect failed! ret = %d\n", ret);
        return BSP_ERR_DUMP_INIT_FAILED;
    }

    ret = bsp_ipc_int_enable(IPC_CCPU_SRC_ACPU_DUMP);
    if(BSP_OK != ret)
    {
        dump_error("bsp_ipc_int_enable failed! ret = %d\n", ret);
        return BSP_ERR_DUMP_INIT_FAILED;
    }

    return BSP_OK;
}

__inline__ void dump_init_done(void)
{
    g_dump_global_info->internal_info.comm_internal.init_flag = DUMP_INIT_FLAG;
    return;
}

/* dump初始化时，保存系统任务名，防止挂死情况下，任务名得不到保存 */
void bsp_dump_init_task_name(void)
{
    s32 i;
    s32 task_num = 0;
    u32 buffer = (u32)DUMP_ALLTASK_ADDR;
    u32 taskIdList[DUMP_TASK_NUM_MAX] = {0};
    u8 task_name[12] = {0};
    TSK_INFO_S tsk_info;

    /*获得当前所有任务ID*/
    task_num = DUMP_TASK_NUM_MAX;
    (void)SRE_TaskIDList((u16*)&task_num,taskIdList);
    if (task_num > DUMP_TASK_NUM_MAX)
    {
        task_num = DUMP_TASK_NUM_MAX;
    }

    /*根据任务ID获得NAME，并放到指定内存中*/
    for (i = 0; i < task_num; i++)
    {
        (void)SRE_TaskInfoGet  ( taskIdList[i],  &tsk_info);
        (void)strncpy_s((char *)task_name, 12,tsk_info.acName, 11);
        (void)QueueLoopIn((dump_queue_t *)buffer, taskIdList[i]);
        (void)QueueLoopIn((dump_queue_t *)buffer, *((int *)(task_name)));
        (void)QueueLoopIn((dump_queue_t *)buffer, *((int *)(task_name+4)));
        (void)QueueLoopIn((dump_queue_t *)buffer, *((int *)(task_name+8)));
    }
}


s32 dump_init(void)
{
    /* 延迟一分钟后，保存一次系统所有任务名 */
    (void)osl_task_delay(6000);
    bsp_dump_init_task_name();

    return BSP_OK;
}

s32 bsp_dump_init(void)
{
    s32 ret;/* [false alarm]:fortify */

    g_exc_flag = false;
    g_arm_exc_save_flag = false;
    g_rtosck_exc = false;

    /* 初始化任务名队列 */
    QueueInit((dump_queue_t *)(DUMP_ALLTASK_ADDR), (DUMP_ALLTASK_SIZE - 0x10) / 0x4);

#ifdef __OS_VXWORKS__
    dump_trc_arm_exc_init();
#else
#endif
    /*初始化部分结构体*/
    ret  = dump_init_phase1();/* [false alarm]:fortify */
    if(BSP_OK != ret)/* [false alarm]:fortify */
    {
        dump_error("dump_init_phase1 fail 0x%x\n",ret);/* [false alarm]:fortify */
        return BSP_ERROR;/* [false alarm]:fortify */
    }
    

    /*全局信息初始化*/
    dump_global_info_init();

    dump_base_info_init();

    /*系统运行回调函数注册*/
    dump_register_hook();

    g_dump_regs_func = dump_save_arm_regs;
    /*系统运行回调函数注册*/
    dump_init_done();

    /*初始化队列*/
    dump_queue_t_init();

    (void)memset_s((void*)DUMP_PRINT_ADDR,DUMP_PRINT_SIZE, 0, DUMP_PRINT_SIZE); /* [false alarm]:屏蔽Fortify错误 */

    dump_fetal("DUMP INIT SUCCESS!\n");

    return BSP_OK;
}

void bsp_dump_init_phase2(void)
{
    OSL_TASK_ID task_id;
    (void)dump_task_init();
    //(void)taskSpawn("tDumpInit", 100, 0, 0x1000, (FUNCPTR)dump_init, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    (void)osl_task_init("tDumpInit", 30, 0x1000, (OSL_TASK_FUNC)dump_init, 0, &task_id);/*此处调整了优先级*/

    return;
}

/* coverity[overrun-buffer-val] */
void system_error (u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
    unsigned long lock_key = 0;
    lock_key = lock_key;/* [false alarm]:fortify */
    char buf[256] = {'\0',};

    /*适配llt测试*/
    if(g_dump_global_info->internal_info.dump_mode == DUMP_MODE_NORMAL)
    {
        local_irq_save(lock_key);

        osl_task_lock();
    }


    /* 已经发生异常，不再记录 */
    if(g_exc_flag == true || g_dump_global_info == NULL)
    {
        return;
    }
    else
    {
        g_exc_flag = true;
    }


    if(g_dump_global_info->internal_info.comm_internal.init_flag != DUMP_INIT_FLAG)
    {
        return;
    }

    dump_system_error_enter();

    /*保存异常任务信息*/
    dump_save_exc_task((u32)(&(g_dump_base_info->regSet[0])));

    /* coverity[overrun-buffer-val] */
    dump_vsnprintf(buf,256,"[0x%x][dump]: <%s> ccore enter system error mod_id = 0x%x, arg1 = 0x%x ,arg2 = 0x%x,data = 0x%p,length = 0x%x!\n", om_timer_get(), __FUNCTION__,mod_id,arg1,arg2,data,length);

    dmesg_write(buf, strlen(buf));
    memset_s(buf, 256, '\0', 256);

    if(g_rtosck_exc == false)
    {
        bsp_dump_show_stack();
    }

    /* 通知comm CPU进行异常处理 */
    dump_notify_target();

    /* 首先保存系统异常基本信息 */
    dump_save_global_info();
    dump_save_base_info(mod_id, arg1, arg2, data, length);

    /*保存寄存器信息*/
    dump_save_regs();

    /*保存上层用户数据*/
    dump_save_usr_data(data, length);

    /* 保存扩展区数据 */
    dump_save_ext();

    dump_save_all_task_tcb(g_dump_base_info->reboot_task);

    /*保存打印信息*/
    dump_save_log();

    /*适配llt测试*/
    if(g_dump_global_info->internal_info.dump_mode == DUMP_MODE_NORMAL)
    {
        /* 保存DSP DTCM */
        dump_save_dtcm();

        /*强制进行BBE16的DTCM的备份，用于dump模块备份*/
        bsp_dsp_store_tcm_force();
    }


    /*COMM数据保存完成 */
    dump_save_comm_done();

    (void)osl_cache_flush(OSL_DATA_CACHE, (void *)DDR_MCORE_ADDR, DDR_MCORE_SIZE);
    /*LLT测试情况下进入死循环*/
    if(g_dump_global_info->internal_info.dump_mode == DUMP_MODE_NORMAL)
    {
        /*lint -save -e522*/
        dump_wait_for_reboot();
        /*lint -restore +e522*/
    }
    return;
}

s32 bsp_dump_register_sysview_hook(dump_sysview_t mod_id, dump_hook func)
{
    if(mod_id >= DUMP_SYSVIEW_BUTT )
    {
        return BSP_ERROR;
    }
    else
    {
        g_dump_trace_read_cb[mod_id] = func;
    }

    return BSP_OK;
}

void bsp_dump_trace_stop(void)
{
    dump_trace_stop();
}

void dump_show_field(void)
{
    dump_area_head_t * head;
    dump_field_map_t * field;
    u32 i;
    u32 used_len = 0;
    u32 field_cnt;

    head = &(g_pdump_info->p_area[DUMP_AREA_AP]->area_head);
    field_cnt = head->field_num;

    dump_fetal("-----------------------------------------\n");
    dump_fetal("AP AREA INFO(BASE ADDR %p):\n", head);

    for(i=0; i<field_cnt; i++)
    {
        field = &(g_pdump_info->p_area[DUMP_AREA_AP]->fields[i]);
        dump_fetal("FILED %-16s: id=0x%-8x offset=0x%-8x size=0x%x\n", field->field_name, field->field_id, field->offset_addr, field->length);
        used_len += field->length;
    }

    dump_fetal("USED: 0x%x, LEFT: 0x%x\n", used_len, DUMP_AREA_AP_SIZE - DUMP_AREA_AP_HEAD_SIZE - DUMP_AREA_AP_MAP_SIZE - used_len);

    head = &(g_pdump_info->p_area[DUMP_AREA_CP]->area_head);
    field_cnt = head->field_num;
    used_len  = 0;

    dump_fetal("-----------------------------------------\n");
    dump_fetal("CP AREA INFO(BASE ADDR %p):\n", head);

    for(i=0; i<field_cnt; i++)
    {
        field = &(g_pdump_info->p_area[DUMP_AREA_CP]->fields[i]);
        dump_fetal("FILED %-16s: id=0x%-8x offset=0x%-8x size=0x%x\n", field->field_name, field->field_id, field->offset_addr, field->length);
        used_len += field->length;
    }

    dump_fetal("USED: 0x%x, LEFT: 0x%x\n", used_len, DUMP_AREA_CP_SIZE - DUMP_AREA_CP_HEAD_SIZE - DUMP_AREA_CP_MAP_SIZE - used_len);

    if(DUMP_MBB == g_dump_product_type)
    {
        head = &(g_pdump_info->p_area[DUMP_AREA_LPM3]->area_head);
        field_cnt = head->field_num;
        used_len  = 0;

        dump_fetal("-----------------------------------------\n");
        dump_fetal("LPM3 AREA INFO(BASE ADDR %p):\n", head);

        for(i=0; i<field_cnt; i++)
        {
            field = &(g_pdump_info->p_area[DUMP_AREA_LPM3]->fields[i]);
            dump_fetal("FILED %-16s: id=0x%-8x offset=0x%-8x size=0x%x\n", field->field_name, field->field_id, field->offset_addr, field->length);
            used_len += field->length;
        }

        dump_fetal("USED: 0x%x, LEFT: 0x%x\n", used_len, DUMP_AREA_LPM3_SIZE - DUMP_AREA_LPM3_HEAD_SIZE - DUMP_AREA_LPM3_MAP_SIZE - used_len);
    }
}

void dump_save_dtcm(void)
{
    (void)bsp_dsp_store_tcm();
}

s32 bsp_dump_mark_voice(u32 flag)
{
    if(flag < DUMP_VOICE_BUTT)
    {
        g_pdump_info->p_dump->dump_head.voice = flag;
    }
    else
    {
        dump_fetal("flag error, flag = 0x%x\n", flag);
        return MDRV_ERROR;
    }
    return MDRV_OK;
}
void dump_set_dump_mod(dump_mode_e mod)
{

    g_dump_global_info->internal_info.dump_mode = mod;
}
void dump_llt_init(void)
{
    u32 ret;

    g_exc_flag = false;

    bsp_coresight_enable();
  
    /*向操作系统注册钩子函数*/
    if(1 == g_dump_cfg.dump_cfg.Bits.taskSwitch)
    {

        ret = SRE_TaskSwitchHookAdd((OS_VOID_FUNC)dump_task_switch_hook);

        if(BSP_OK != ret)
        {
            dump_error("dump_register_hook: reg task hook failed!\n");
        }

    }
    if(1 == g_dump_cfg.dump_cfg.Bits.intSwitch)
    {

        (void)SRE_HwiEntryHookAdd(dump_int_entry_hook);
        (void)SRE_HwiExitHookAdd(dump_int_exit_hook);
    }
    
    g_dump_global_info->internal_info.comm_internal.taskSwitchStart = BSP_TRUE;
    g_dump_global_info->internal_info.comm_internal.IntSwitchStart = BSP_TRUE;

    return;
}
void dump_set_dump_reset_flag(u32 flag)
{
    g_dump_cfg.dump_cfg.Bits.sysErrReboot = flag;
}
/*lint -restore */

