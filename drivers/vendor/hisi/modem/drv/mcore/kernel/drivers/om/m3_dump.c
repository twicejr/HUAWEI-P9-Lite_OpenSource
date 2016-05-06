
/*lint -save -e537*/
#include "product_config.h"
#include "osl_types.h"
#include "bsp_ipc.h"
#include "bsp_icc.h"
#include "m3_dump.h"
#include "ring_buffer.h"
#include "console.h"
#include "bsp_hardtimer.h"
#include "bsp_softtimer.h"
#include "bsp_wdt.h"
#include "hi_syssc.h"
#include "bsp_memmap.h"
#include "cmsis_os.h"
#include "libc.h"
#include <bsp_onoff.h>
#include <rt_Task.h>
#include "osl_malloc.h"
#include "osl_irq.h"
#include <libfdt.h>
#include "bsp_coresight.h"
#include "bsp_om_version.h"
#include "bsp_sysctrl.h"
#include "drv_nv_def.h"
/*lint -restore*/
#ifdef ENABLE_BUILD_OM
NV_DUMP_STRU         g_dump_cfg = {{0}};
dump_global_info_t  *g_dump_global_info = BSP_NULL;
dump_base_info_t    *g_dump_base_info = BSP_NULL;
dump_task_info_t    *g_dump_task_info = BSP_NULL;
/* r0~r14,pc,xpsr,msp,psp,lr(saving in msp) */
/* 软件主动system_error，只记录r0~r14,pc,xpsr */
u32                 g_dump_regs[20]= {0};
u32                 g_sys_err_flag = true;
struct softtimer_list g_dump_timer ;
dump_sysctrl_reg_t  g_dump_sysctrl_base[OM_SYSCTRL_CNT];
u32                 g_dump_sysctrl_num = 0;


#ifdef CONFIG_CORESIGHT
#define DUMP_AP_UTRACE_SIZE 0x2400
#define DUMP_CP_UTRACE_SIZE 0x2400

/* coresight memory map */
typedef struct coresight_mem_ctrl_ss
{
    unsigned long ap_tmc_virt_addr;
	unsigned long ap_tmc_phy_addr;
	unsigned long ap_tmc_mem_size;
    unsigned long cp_tmc_virt_addr;
	unsigned long cp_tmc_phy_addr;
	unsigned long cp_tmc_mem_size;
}coresight_mem_ctrl_t;
coresight_mem_ctrl_t g_coresight_mem_ctrl;
#endif

/*lint -save -e452*/
typedef void (*funcptr)(int, int);
typedef void (*func_void_t)(void);
extern int task_switch_hook_add (dump_hook switchHook);
extern void int_switch_hook_add(dump_hook pHookFunc);
extern void int_switch_hook_delete(void);
/*lint -restore +e452*/

#ifdef BSP_CONFIG_HI3630
typedef int (*funcptr_int)(int,int);
funcptr_int g_pIntSwitchHook = BSP_NULL;
#endif

#define dump_save_ext_done()\
    do{\
        g_dump_global_info->internal_info.m3_internal.ext_save_flag = DUMP_SAVE_SUCCESS;\
    }while(0)

#define dump_save_m3_done()\
        do{\
            g_dump_global_info->internal_info.m3_internal.save_flag = DUMP_SAVE_SUCCESS;\
        }while(0)

#define DUMP_T_TASK_ERROR(mod_id)      (mod_id & (1<<24))

static void QueueInit(dump_queue_t *Q, u32 elementNum)
{
    Q->maxNum = elementNum;
    Q->front = 0;
    Q->rear = 0;
    Q->num = 0;
    memset((void *)Q->data, 0, (elementNum*sizeof(u32)));
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

__inline__ void dump_interrrupt_enter(void)
{
    g_dump_global_info->internal_info.m3_internal.inInterrupt++;
}

__inline__ void dump_interrrupt_exit(void)
{
    g_dump_global_info->internal_info.m3_internal.inInterrupt--;
}

__inline__ int dump_in_interrrupt(void)
{
    return (int)g_dump_global_info->internal_info.m3_internal.inInterrupt;
}

u32 om_timer_tick_get(void)
{
    u32 omTimerValue;
    /*lint -save -e958*/
	u64 omTick;
    /*lint -restore*/
	omTimerValue = bsp_get_slice_value();
	omTick=((unsigned long long)omTimerValue*100)>>(15);
	return (UINT32)omTick;
}

static void dump_memcpy(u32 * dst, const u32 * src, u32 len)
{
    while(len-- > 0)
    {
        *dst++ = *src++;
    }
}


static s32 dump_config_init(void)
{
    u32 ret;

    ret   = bsp_nvm_read(NVID_DUMP, (u8 *)&g_dump_cfg, sizeof(NV_DUMP_STRU));

    if (BSP_OK != ret)
    {
        /*使用默认值*/
         g_dump_cfg.dump_cfg.uintValue = 0;

        g_dump_cfg.dump_cfg.Bits.dump_switch     = 0x1;
        g_dump_cfg.dump_cfg.Bits.ARMexc          = 0x1;
        g_dump_cfg.dump_cfg.Bits.stackFlow       = 0x1;
        g_dump_cfg.dump_cfg.Bits.taskSwitch      = 0x1;
        g_dump_cfg.dump_cfg.Bits.intSwitch       = 0x1;
        g_dump_cfg.dump_cfg.Bits.intLock         = 0x1;
        g_dump_cfg.dump_cfg.Bits.sysErrReboot    = 0x1;
        g_dump_cfg.dump_cfg.Bits.reset_log       = 0x1;
        g_dump_cfg.dump_cfg.Bits.fetal_err       = 0x1;
    }

    return BSP_OK;
}

static void dump_trace_stop(void)
{
    int_switch_hook_delete();
    task_switch_hook_del();
    g_dump_global_info->internal_info.m3_internal.taskSwitchStart = BSP_FALSE;
    g_dump_global_info->internal_info.m3_internal.IntSwitchStart = BSP_FALSE;

    return;
}

static void dump_save_base_info(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
    if(BSP_MODU_OTHER_CORE == mod_id)
    {
        g_dump_base_info->reboot_task = (u32)(-1);
        g_dump_base_info->reboot_int = (u32)(-1);
    }
    else
    {
        /* 当前处于任务 */
        if (0 == dump_in_interrrupt())
        {
            g_dump_base_info->reboot_task = g_dump_base_info->current_task;
            memset(g_dump_base_info->taskName, 0, sizeof(g_dump_base_info->taskName));
            g_dump_base_info->reboot_int = (u32)(-1);
            g_dump_base_info->reboot_context = DUMP_CTX_TASK;
        }
        /* 当前处于中断 */
        else
        {
            g_dump_base_info->reboot_task = (u32)(-1);
            memset(g_dump_base_info->taskName, 0, sizeof(g_dump_base_info->taskName));
            g_dump_base_info->reboot_int = g_dump_base_info->current_int;
            g_dump_base_info->reboot_context = DUMP_CTX_INT;
        }
    }

    g_dump_base_info->modId = mod_id;
    g_dump_base_info->arg1 = arg1;
    g_dump_base_info->arg2 = arg2;
    g_dump_base_info->arg3 = (u32)data;
    g_dump_base_info->arg3_length = length;

    return;
}


static void dump_save_exc_task(void)
{
    P_TCB ptcb = (P_TCB)g_dump_base_info->current_task;
    u16 len = 1024;

    /* 保存任务栈 */
    len = (len> DUMP_M3_TASK_STACK_SIZE) ? DUMP_M3_TASK_STACK_SIZE : (len);

    memcpy((void * )DUMP_M3_TASK_STACK_ADDR, (const void * )(ptcb->stack ), len);

    return;
}

__inline__ void dump_save_arm_regs(void)
{
    asm volatile(
        "push {r14}\n"
        "ldr r14, =g_dump_regs\n"
        "str r0, [r14,#0x00]\n"
        "str r1, [r14,#0x04]\n"
        "str r2, [r14,#0x08]\n"
        "str r3, [r14,#0x0C]\n"
        "str r4, [r14,#0x10]\n"
        "str r5, [r14,#0x14]\n"
        "str r6, [r14,#0x18]\n"
        "str r7, [r14,#0x1C]\n"
        "str r8, [r14,#0x20]\n"
        "str r9, [r14,#0x24]\n"
        "str r10, [r14,#0x28]\n"
        "str r11, [r14,#0x2C]\n"
        "str r12, [r14,#0x30]\n"
        "str r13, [r14,#0x34]\n"
        "ldr r0, =g_dump_regs\n"
        "pop {r14}\n"
        "str r14, [r0,#0x38]\n"
        "push {r1}\n"
        "mov r1, pc\n"
        "str r1, [r0,#0x3C]\n"
        "mrs r1, xpsr\n"
        "str r1, [r0,#0x40]\n"
        "pop {r1}\n"
    );
}

static void dump_save_mcore_sys_reg(void)
{
    u32 len;
    u32 i;
    u32 * dst_buf;
    u32 reg_addr;

    dst_buf = (u32 *)DUMP_M3_REGS_ADDR;
    len = DUMP_M3_REGS_SIZE/4;

    for(i=0; i<len; i++)
    {
        reg_addr = M3_SYSCTRL_BASE + i*4;
        *dst_buf = readl(reg_addr);
        dst_buf++;
    }
}

static void dump_save_ext(void)
{
    struct list_head* cur = NULL;
    dump_field_hook_t* pfieldhook = NULL;
    dump_area_head_t*  p_head  = (dump_area_head_t*)g_pdump_info->p_cur_area;
    dump_field_map_t*  p_field = (dump_field_map_t*)g_pdump_info->p_cur_area->fields;
    u32 i;
    u32 * f_addr;

    list_for_each(cur, &g_pdump_info->cur_hook_list.hook_list)
    {
        pfieldhook = list_entry(cur, dump_field_hook_t, hook_list);
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
            dump_memcpy(f_addr, (u32 *)(*(f_addr + 1)), (p_field->length)/4);
        }
    }

    dump_save_ext_done();
    return;
}

static void dump_save_log(void)
{   /*lint -save -e18 */
    struct s_ring_buffer *rb = &g_console.send_buff;
    /*lint -restore +e18 */
    unsigned char * pre_pos;
    unsigned int    pre_size;
    unsigned int    next_size;

    if(rb->in > rb->size)
    {
        next_size = (rb->in)%(rb->size);
        pre_pos   = rb->buffer + next_size;
        pre_size  = rb->size - next_size;
        memcpy((char*)DUMP_M3_PRINT_ADDR, pre_pos, pre_size);
        memcpy((char*)DUMP_M3_PRINT_ADDR+pre_size, rb->buffer, next_size);
    }
    else
    {
        pre_size = rb->in;
        memcpy((char*)DUMP_M3_PRINT_ADDR, rb->buffer, pre_size);
    }
}

static void dump_save_sysctrl(void)
{
    u32 i;
    u32 * field_addr;
    u32 * reg_addr;
    u32 reg_size;

    field_addr = (u32 *)bsp_dump_get_field_addr(DUMP_CP_SYSCTRL);
    if(field_addr == NULL)
    {
        return;
    }

    for(i=0; i<g_dump_sysctrl_num; i++)
    {
        reg_size = g_dump_sysctrl_base[i].reg_size;
        reg_size = (reg_size > 0x1000) ? 0x1000 : reg_size;

        reg_addr = (u32 *)bsp_sysctrl_addr_get((void *)(g_dump_sysctrl_base[i].reg_base));
        /* coverity[dereference] */
        dump_memcpy(field_addr, reg_addr, reg_size >> 2);

        /* 保存头信息: magic_num reg_base reg_size reserved, 16字节 */
        *(field_addr + (reg_size >> 2) - 4) = OM_SYSCTRL_MAGIC;
        *(field_addr + (reg_size >> 2) - 3) = g_dump_sysctrl_base[i].reg_base;
        *(field_addr + (reg_size >> 2) - 2) = g_dump_sysctrl_base[i].reg_size;
        *(field_addr + (reg_size >> 2) - 1) = 0;

        /* 头长度:0x10, 数据区域长度:0x1000 */
        field_addr = field_addr + (reg_size >> 2);
    }
}

static void dump_get_sysctrl_info(void)
{
    struct device_node *node = NULL;
    u32 reg_num;

    node = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl_m3");
	if (!node)
	{
        goto out;
	}

    if(of_property_read_u32_array(node, "reg_sum", &reg_num, 1))
    {
        goto out;
    }

    reg_num = (reg_num > OM_SYSCTRL_CNT) ? OM_SYSCTRL_CNT : reg_num;
    if(of_property_read_u32_array(node, "reg", (u32 *)g_dump_sysctrl_base, reg_num * 2))
    {
        goto out;
    }

    g_dump_sysctrl_num = reg_num;

out:
    return;
}

void dump_int_handle(s32 param)
{
    if (DUMP_INIT_FLAG !=g_dump_global_info->internal_info.m3_internal.init_flag)
    {
        return;
    }

    dump_save_arm_regs();
    dump_save_mcore_sys_reg();

    dump_trace_stop();

     /* 首先保存系统异常基本信息 */
    dump_save_base_info(BSP_MODU_OTHER_CORE, 0, 0, BSP_NULL, 0);

    /*保存异常任务信息*/
    dump_save_exc_task();

    /*保存打印信息*/
    dump_save_log();

    dump_save_ext();

    /*保存系统控制器信息*/
    dump_save_sysctrl();

     /*M3数据保存完成 */
    dump_save_m3_done();

    bsp_softtimer_add(&g_dump_timer);

    return;
}

void dump_map_init(void)
{
    unsigned long flags = 0;
    u32 base_addr  = 0;
    dump_area_head_t*  p_head  = (dump_area_head_t*)g_pdump_info->p_cur_area;
    dump_field_map_t*  p_field = (dump_field_map_t*)g_pdump_info->p_cur_area->fields;
    dump_load_info_t * dump_load;

    dump_load = (dump_load_info_t *)DUMP_LOAD_INFO_ADDR;
    dump_load->lpm3_tcm0 = HI_M3TCM0_MEM_ADDR;
    dump_load->lpm3_tcm1 = HI_M3TCM1_MEM_ADDR;

    flags = flags;

    /* 初始化AREA HEAD区域 */
    p_head->magic_num = DUMP_LPM3_MAGIC_NUM;
    p_head->name[0] = 'L';
    p_head->name[1] = 'P';
    p_head->name[2] = 'M';
    p_head->name[3] = '3';
    p_head->name[4] = '\0';

    /* 注册DUMP静态区域 */
    spin_lock_irqsave(&g_pdump_info->lock, flags);
    base_addr = (u32)g_pdump_info->p_cur_area;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_BASE_INFO,       "BASE_INFO",   base_addr,DUMP_M3_BASE_INFO_ADDR,     DUMP_M3_BASE_INFO_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_TASK_SWITCH,     "TASK_SWITCH", base_addr,DUMP_M3_TASK_SWITCH_ADDR,   DUMP_M3_TASK_SWITCH_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_INTLOCK,         "INTLOCK",     base_addr,DUMP_M3_INTLOCK_ADDR,       DUMP_M3_INTLOCK_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_TASK_STACK,      "TASK_STACK",  base_addr,DUMP_M3_TASK_STACK_ADDR,    DUMP_M3_TASK_STACK_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_INT_STACK,       "INT_STACK",   base_addr,DUMP_M3_INT_STACK_ADDR,     DUMP_M3_INT_STACK_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_ALLTASK,         "TASK_NAME",   base_addr,DUMP_M3_ALLTASK_ADDR,       DUMP_M3_ALLTASK_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_ALLTASK_TCB,     "ALLTASK_TCB", base_addr,DUMP_M3_ALLTASK_TCB_ADDR,   DUMP_M3_ALLTASK_TCB_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_PRINT,           "PRINT",       base_addr,DUMP_M3_PRINT_ADDR,         DUMP_M3_PRINT_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_LOG,             "LOG",         base_addr,DUMP_M3_LOG_ADDR,           DUMP_M3_LOG_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_REGS,            "REGS",        base_addr,DUMP_M3_REGS_ADDR,          DUMP_M3_REGS_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_TCM0,            "TCM0",        base_addr,DUMP_M3_TCM0_ADDR,          DUMP_M3_TCM0_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_TCM1,            "TCM1",        base_addr,DUMP_M3_TCM1_ADDR,          DUMP_M3_TCM1_SIZE)
    g_pdump_info->cur_field_num++;
    /* 在M3 boot中使用，由dump注册该区域 */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_M3_BOOST,           "BOOST",       base_addr,DUMP_M3_BOOST_ADDR,         DUMP_M3_BOOST_SIZE)
    g_pdump_info->cur_field_num++;
    p_head->field_num = g_pdump_info->cur_field_num;
    spin_unlock_irqrestore(&g_pdump_info->lock, flags);

    g_dump_base_info = (dump_base_info_t *)DUMP_M3_BASE_INFO_ADDR;
    g_dump_task_info = (dump_task_info_t *)DUMP_M3_ALLTASK_TCB_ADDR;

    return;
}

static s32 dump_global_info_init(void)
{
    g_dump_global_info->internal_info.m3_internal.start_flag = DUMP_START_CRASH;
    g_dump_global_info->internal_info.m3_internal.save_flag = BSP_FALSE;
    g_dump_global_info->internal_info.m3_internal.ext_save_flag = BSP_FALSE;
    g_dump_global_info->internal_info.m3_internal.inInterrupt = 0;
    g_dump_global_info->internal_info.m3_internal.taskSwitchStart = BSP_FALSE;
    g_dump_global_info->internal_info.m3_internal.IntSwitchStart = BSP_FALSE;

    return BSP_OK;
}

static s32 dump_base_info_init(void)
{
    int i;

    memset(g_dump_base_info, 0, sizeof(dump_base_info_t));
    g_dump_base_info->vec = 0xff;

    memset((void *)DUMP_M3_ALLTASK_TCB_ADDR, 0, DUMP_M3_ALLTASK_TCB_SIZE);
    for(i=0; i<DUMP_M3_TASK_NUM_MAX; i++)
    {
        g_dump_task_info[i].pid = 0xffffffff;
    }

    return BSP_OK;
}

static void dump_queue_t_init(void)
{
    /* 初始化任务切换队列 */
    QueueInit((dump_queue_t *)(DUMP_M3_TASK_SWITCH_ADDR), (DUMP_M3_TASK_SWITCH_SIZE - 0x10) / 0x4);

    /* 初始化任务名队列 */
    QueueInit((dump_queue_t *)(DUMP_M3_ALLTASK_ADDR), (DUMP_M3_ALLTASK_SIZE - 0x10) / 0x4);

    return;
}

/*lint -save -e101*/
static void dump_task_switch_hook( P_TCB new_tcb)
{
    /* 将要切换的任务ID和时间入队*/
    u32 addr = DUMP_M3_TASK_SWITCH_ADDR;
    unsigned long flag;

    if(BSP_FALSE == g_dump_global_info->internal_info.m3_internal.taskSwitchStart)
    {
        return;
    }

    local_irq_save(flag);
    QueueLoopIn((dump_queue_t *)addr, (u32)(new_tcb));
    QueueLoopIn((dump_queue_t *)addr, bsp_get_slice_value());
    local_irq_restore(flag);

    g_dump_base_info->current_task = (u32)new_tcb;

    return;
}
/*lint -restore*/

void dump_int_switch_hook(u32 dir, u32 newVec)
{
    u32 addr = DUMP_M3_TASK_SWITCH_ADDR;
    unsigned long flag;

    if(BSP_NULL == g_dump_global_info)
    {
        return;
    }

    if(BSP_TRUE != g_dump_global_info->internal_info.m3_internal.IntSwitchStart)
    {
        return;
    }

    /*lint -save -e648 */
    local_irq_save(flag);
    /* 将触发的中断ID和时间入队*/
    if (0 == dir)/*中断进入*/
    {
        QueueLoopIn((dump_queue_t *)addr, ((DUMP_INT_IN_FLAG<<16)|newVec));
        dump_interrrupt_enter();
    }
    else/*中断退出*/
    {
        QueueLoopIn((dump_queue_t *)addr, ((DUMP_INT_EXIT_FLAG<<16)|newVec));
        dump_interrrupt_exit();
    }
    QueueLoopIn((dump_queue_t *)addr, bsp_get_slice_value());
    local_irq_restore(flag);
    /*lint -restore +e648 */
    g_dump_base_info->current_int = newVec;

    return;
}
/*lint -save -e550*/

static void dump_exc_hook( int error_id,int currentTaskId)
{
    s32 lock_key = 0;

    /*lint -save -e26 -e515 -e718 -e746*/
    local_irq_save(lock_key);
    /*lint -restore*/
    if(lock_key)
    {}

    g_dump_base_info->vec = (u32)error_id;
    g_pdump_info->p_dump->dump_head.except_reason= DUMP_REASON_ARM;

    /*进行全局复位*/
    system_error(DRV_ERRNO_DUMP_ARM_EXC, DUMP_REASON_ARM, 0, 0, 0);

    return;
}
/*lint -restore +e550*/
#ifdef CONFIG_CORESIGHT
/* ETF命名规则: */
/* 1.AP/CP共用一个ETF，ETF名称为tmc-dup(V711/V7R2) */
/* 2.AP/CP有各自的ETF，AP ETF名称为tmc-ap，CP ETF名称为tmc-cp(V7R5) */
static u32 dump_coresight_memmap(void)
{  
    struct device_node * node  = NULL;
    struct device_node ap_node;
    struct device_node cp_node;
	unsigned int reg_data[2] = {0,};

    ap_node.offset = 0;
    cp_node.offset = 0;
    memset(&g_coresight_mem_ctrl, 0, sizeof(coresight_mem_ctrl_t));

    node = of_find_compatible_node(NULL, NULL, "arm,tmc-dup");
    if(node)
    {
        ap_node.offset = node->offset;
        cp_node.offset = node->offset;
    }
    else
    {
        node = of_find_compatible_node(NULL, NULL, "arm,tmc-ap");
        if(node)
        {
            ap_node.offset = node->offset;
        }

        node = of_find_compatible_node(NULL, NULL, "arm,tmc-cp");
        if(node)
        {
            cp_node.offset = node->offset;
        }
    }

    if(ap_node.offset)
    {
        if(of_property_read_u32_array(&ap_node, "reg", reg_data, 2))
        {
            return BSP_ERROR;
        }

        g_coresight_mem_ctrl.ap_tmc_phy_addr  = reg_data[0];
        g_coresight_mem_ctrl.ap_tmc_mem_size  = reg_data[1];
        g_coresight_mem_ctrl.ap_tmc_virt_addr = (unsigned int)of_iomap(&ap_node, 0);
    }

    if(cp_node.offset)
    {
        if(of_property_read_u32_array(&cp_node, "reg", reg_data, 2))
        {
            return BSP_ERROR;
        }

        g_coresight_mem_ctrl.cp_tmc_phy_addr  = reg_data[0];
        g_coresight_mem_ctrl.cp_tmc_mem_size  = reg_data[1];
        g_coresight_mem_ctrl.cp_tmc_virt_addr = (unsigned int)of_iomap(&cp_node, 0);
    }   

	return BSP_OK;
}

static void dump_cs_etb(s32 core)
{
    u32     reg_value;
    u32     i;
    u32  *  data;
    u32     dst_addr   = 0;
    u32     dst_size   = 0;
    u32     tmcRegAddr = 0;   

    if(core ==ACORE_WDT_TIMEOUT)
    {
        tmcRegAddr = g_coresight_mem_ctrl.ap_tmc_virt_addr;
        dst_addr   = (u32)bsp_dump_get_field_addr(DUMP_AP_UTRACE);
        dst_size   = DUMP_AP_UTRACE_SIZE;
    }
    else if(core ==CCORE_WDT_TIMEOUT)
    {   
        tmcRegAddr = g_coresight_mem_ctrl.cp_tmc_virt_addr;
        dst_addr   = (u32)bsp_dump_get_field_addr(DUMP_CP_UTRACE);
        dst_size   = DUMP_CP_UTRACE_SIZE;
    }
    else
    {
        return;
    }

    if((tmcRegAddr==0) || (dst_addr==0))
        return;

    if(*(u32*)dst_addr == 0x89ABCDEF)
        return;

    /* unlock etb, 配置ETF_LOCK_ACCESS */
    writel(0xC5ACCE55, tmcRegAddr + 0xFB0);

    /* stop etb, 配置ETF_FORMAT_FLUSH_CTRL */
    reg_value = readl(tmcRegAddr + 0x304);
    /* FFCR StopOnFl */
    reg_value |= 1 << 12;
    /* FFCR FlushMem */
    reg_value |= 1 << 6;
    writel(reg_value, tmcRegAddr + 0x304);

    /* 等待TMCReady */
    for(i=0; i<2000; i++)
    {
        /* read etb status, 读取ETF_STATUS */
        reg_value = readl(tmcRegAddr + 0xc);
        /* bit2为TMCReady指示位 */
        if(0 != (reg_value & 0x4))
        {
            break;
        }
    }

    /* 超时判断 */
    if(i >= 2000)
    {
        return ;
    }

    /* 导出etb数据 */
    memset((void *)dst_addr, 0x0, dst_size);
    data = (u32 *)(dst_addr + 8);
    for(i=0; i<(1024*8)/4; i++)
    {
        /* read etb, 读取ETF_RAM_RD_DATA */
        reg_value = readl(tmcRegAddr + 0x10);
        *data = reg_value;
        data++;
        if(reg_value == 0xffffffff)
        {
            break;
        }
    }

    /* 0-3字节存放标识码 */
    *((u32 *)dst_addr) = (u32)0x89ABCDEF;
    /* 4-7个字节存放ETB数据长度 */
    *((u32 *)dst_addr + 1) = i*4;

    /* lock etb, 配置ETF_LOCK_ACCESS */
    writel(0x1, tmcRegAddr + 0xFB0);
}
#else
static void dump_cs_etb(s32 core)
{
}

static u32 dump_coresight_memmap(void)
{
    return BSP_OK;
}
#endif

void dump_wdt_hook(s32 core)
{
    g_pdump_info->p_dump->dump_head.except_reason= DUMP_REASON_WDT;

    if(ACORE_WDT_TIMEOUT == core)
    {
        g_pdump_info->p_dump->dump_head.except_core = DUMP_CPU_APP;
        g_dump_global_info->internal_info.app_internal.start_flag = DUMP_START_EXCH;
    }
    else if(CCORE_WDT_TIMEOUT == core)
    {
        g_pdump_info->p_dump->dump_head.except_core = DUMP_CPU_COMM;
        g_dump_global_info->internal_info.comm_internal.start_flag = DUMP_START_EXCH;
    }
    else
    {
        g_pdump_info->p_dump->dump_head.except_core = DUMP_CPU_LPM3;
        g_dump_global_info->internal_info.m3_internal.start_flag = DUMP_START_EXCH;
    }

    /* dump etb */
    if(1 == g_dump_cfg.traceOnstartFlag)
    {
        /* 监控CPU发生挂死 */
        if(((g_pdump_info->p_dump->dump_head.except_core == DUMP_CPU_APP) && ((g_dump_cfg.traceCoreSet & (1<<AP_CORE_SET)) != 0))
            || ((g_pdump_info->p_dump->dump_head.except_core == DUMP_CPU_COMM) && ((g_dump_cfg.traceCoreSet & (1<<CP_CORE_SET)) != 0)))
        {
            dump_cs_etb(core);
        }
    }
    /*进行全局复位*/
    system_error(DRV_ERRNO_DUMP_WDT, DUMP_REASON_WDT, 0, 0, 0);
}


static void dump_register_hook(void)
{
    /*lint -save -e64 */
    /*向操作系统注册钩子函数*/
    if(1 == g_dump_cfg.dump_cfg.Bits.taskSwitch)
    {
        task_switch_hook_add((func_void_t)dump_task_switch_hook); 

    }
    if(1 == g_dump_cfg.dump_cfg.Bits.intSwitch)
    {
        int_switch_hook_add((func_void_t)dump_int_switch_hook);
    }
    if(1 == g_dump_cfg.dump_cfg.Bits.ARMexc)
    {
        exc_dump_hook_add((exc_funcptr)dump_exc_hook);
    }
    /*lint -restore +e64 */
     /*缺看门狗中断*/
    bsp_wdt_register_hook(dump_wdt_hook);

    g_dump_global_info->internal_info.m3_internal.taskSwitchStart = BSP_TRUE;
    g_dump_global_info->internal_info.m3_internal.IntSwitchStart = BSP_TRUE;

    return;
}

void dump_timer_handler(u32 param)
{
    /* 重启系统 */
    g_dump_global_info->internal_info.app_internal.save_file_flag = DUMP_SAVE_FILE_NEED;
    if(1 == g_dump_cfg.dump_cfg.Bits.sysErrReboot)
    {
        bsp_drv_power_reboot_direct();
    }
}

static void dump_create_timer(u32 time_out)
{
    g_dump_timer.func = dump_timer_handler;
    g_dump_timer.para = 0;
    g_dump_timer.timeout = time_out;
    g_dump_timer.wake_type = SOFTTIMER_WAKE;

    if(BSP_OK != bsp_softtimer_create(&g_dump_timer))
    {
        printk("dump timer fail\n");
    }
}

void m3_dump_init(void)
{
    s32 ret;

    /*初始化队列*/
    dump_queue_t_init();

    g_dump_global_info = (dump_global_info_t*)DUMP_GLOBAL_INFO_ADDR;

    g_dump_global_info->internal_info.m3_internal.start_wait_flag = 0;

    /*获取配置*/
    dump_config_init();

    /* 读取coresight配置 */
    dump_coresight_memmap();

    /* 注册中断 */
    ret = bsp_ipc_int_connect(IPC_MCU_INT_SRC_DUMP, (voidfuncptr)dump_int_handle, 0);
    if(BSP_OK != ret)
    {
        return ;
    }

    ret = bsp_ipc_int_enable(IPC_MCU_INT_SRC_DUMP);
    if(BSP_OK != ret)
    {
        return ;
    }

    /*全局信息初始化*/
    dump_global_info_init();

    dump_base_info_init();

    /*系统运行回调函数注册*/
    dump_register_hook();

    /* 清空PRINT缓存 */
    memset((void *)DUMP_M3_PRINT_ADDR, 0, DUMP_M3_PRINT_SIZE);

    dump_get_sysctrl_info();

    dump_create_timer(10000);

    g_dump_global_info->internal_info.m3_internal.init_flag = DUMP_INIT_FLAG;

    return ;
}

log_mem_stru *  g_log_info = NULL;
u32 g_log_enable = false;
#define __LOG_BUF_LEN	        (DUMP_M3_LOG_SIZE)
#define LOG_BUF_MASK            (__LOG_BUF_LEN -1)
#define LOG_BUF(idx)            (g_log_info->log_buf[(idx) & LOG_BUF_MASK])

void m3_log_print(char ch)
{
    if(g_log_enable == false)
    {
        return;
    }

    LOG_BUF(g_log_info->log_info.write) = ch;
    g_log_info->log_info.write++;

    if(g_log_info->log_info.write >= g_log_info->log_info.size)
    {
        g_log_info->log_info.write = 0;
    }
}

void m3_log_init(void)
{
    log_mem_stru * mem = (log_mem_stru *)DUMP_M3_LOG_ADDR;

    mem->log_info.magic = M3_LOG_MAGIC;
    mem->log_info.read  = 0;
    mem->log_info.write = 0;
    mem->logged_chars   = 0;
    mem->log_info.size  = DUMP_M3_LOG_SIZE - sizeof(log_mem_stru);
    mem->log_buf        = (u8 *)DUMP_M3_LOG_ADDR + sizeof(log_mem_stru);
    mem->w_mark         = (mem->log_info.size)/2;
    mem->log_info.app_is_active = 0;

    g_log_info = mem;
    g_log_enable = true;
}

static void dump_save_global_info(void)
{
    //如果是上层复位，标志复位状态
    if(DUMP_REASON_UNDEF == g_pdump_info->p_dump->dump_head.except_reason)
    {
        g_pdump_info->p_dump->dump_head.except_reason = DUMP_REASON_NORMAL;
    }

    if(DUMP_REASON_WDT != g_pdump_info->p_dump->dump_head.except_reason)
    {
        g_pdump_info->p_dump->dump_head.except_core= DUMP_CPU_LPM3;
        g_dump_global_info->internal_info.m3_internal.start_flag = DUMP_START_EXCH;
    }

    g_pdump_info->p_dump->dump_head.except_time= bsp_get_slice_value();

    return;
}

/*lint -esym(18, system_error) */
/*lint -esym(516, system_error) */
/*lint -esym(532, system_error) */
void system_error (u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
    if(g_sys_err_flag == true)
    {
        dump_save_arm_regs();
        dump_save_mcore_sys_reg();
    }
    printk("system err\n");

    if (DUMP_INIT_FLAG != g_dump_global_info->internal_info.m3_internal.init_flag)
    {
        return;
    }

    dump_trace_stop();

    /* 首先保存系统异常基本信息 */
    dump_save_global_info();
    dump_save_base_info(mod_id, arg1, arg2, data, length);

    /*保存异常任务信息*/
    dump_save_exc_task();

     /* 通知ACPU进行异常处理 */
    bsp_ipc_int_send(IPC_CORE_ACORE, IPC_ACPU_INT_MCU_SRC_DUMP);

    /*保存打印信息*/
    dump_save_log();

    /*保存系统控制器信息*/
    dump_save_sysctrl();

    /* 保存扩展区数据 */
    dump_save_ext();

    /*M3数据保存完成 */
    dump_save_m3_done();

    /* 启动定时器，超时重启 */
    bsp_softtimer_add(&g_dump_timer);

    return;
}

__inline__ void dump_save_arm_exc_regs(void)
{
    asm volatile(
        "ldr    r0, =g_dump_regs\n"
        "str    r4, [r0, #16]\n"
        "str    r5, [r0, #20]\n"
        "str    r6, [r0, #24]\n"
        "str    r7, [r0, #28]\n"
        "str    r8, [r0, #32]\n"
        "str    r9, [r0, #36]\n"
        "str    r10, [r0, #40]\n"
        "str    r11, [r0, #44]\n"
        "mrs    r2, msp\n"
        "mrs    r3, psp\n"
        "/* save lr, lr is in stack */\n"
        "ldr    r1, [r2]\n"
        "str    r1, [r0, #76]\n"
        "/* push lr to msp when in handler, true msp is one word above */\n"
        "add    r2, r2, #4\n"
        "/* make sure which stack is in use */\n"
        "tst    r1, #4\n"
        "/* m3 will push r0~r3,r12,lr,pc,xpsr to stack before go into handler */\n"
        "ittee  eq\n"
        "addeq  r2, r2, #32\n"
        "moveq  r1, r2\n"
        "addne  r3, r3, #32\n"
        "movne  r1, r3\n"
        "/* save r13,msp,psp */\n"
        "str    r1, [r0, #52]\n"
        "str    r2, [r0, #68]\n"
        "str    r3, [r0, #72]\n"
        "sub    r2, r1, #32\n"
        "/* save r0~r3,r12,lr,pc,xpsr */\n"
        "ldr    r1, [r2]\n"
        "str    r1, [r0]\n"
        "ldr    r1, [r2, #4]\n"
        "str    r1, [r0, #4]\n"
        "ldr    r1, [r2, #8]\n"
        "str    r1, [r0, #8]\n"
        "ldr    r1, [r2, #12]\n"
        "str    r1, [r0, #12]\n"
        "ldr    r1, [r2, #16]\n"
        "str    r1, [r0, #48]\n"
        "ldr    r1, [r2, #20]\n"
        "str    r1, [r0, #56]\n"
        "ldr    r1, [r2, #24]\n"
        "str    r1, [r0, #60]\n"
        "ldr    r1, [r2, #28]\n"
        "str    r1, [r0, #64]\n"
    );
}

/*lint -save -e718 -e746*/
void hardfault_dump(void)
{
    dump_save_arm_exc_regs();
    dump_save_mcore_sys_reg();
    g_sys_err_flag = false;
    dump_exc_hook(0xc,(int)rt_tsk_self());
}

void mem_manage_dump(void)
{
	dump_save_arm_exc_regs();
    dump_save_mcore_sys_reg();
    g_sys_err_flag = false;
    dump_exc_hook(0x10,(int)rt_tsk_self());
}

void bus_fault_dump(void)
{
	dump_save_arm_exc_regs();
    dump_save_mcore_sys_reg();
    g_sys_err_flag = false;
    dump_exc_hook(0x14,(int)rt_tsk_self());
}

void usage_fault_dump(void)
{
    dump_save_arm_exc_regs();
    dump_save_mcore_sys_reg();
    g_sys_err_flag = false;
    dump_exc_hook(0x18,(int)rt_tsk_self());
}
/*lint -restore*/
#else
void m3_dump_init(void)
{
    return;
}
void m3_log_init(void)
{
	return;
}
void m3_log_print(char ch)
{
	return;
}
void hardfault_dump(void)
{
    return;
}
void mem_manage_dump(void)
{
    return;
}
void bus_fault_dump(void)
{
    return;
}
void usage_fault_dump(void)
{
    return;
}
void dump_wdt_hook(s32 core)
{
    return;
}

#endif

