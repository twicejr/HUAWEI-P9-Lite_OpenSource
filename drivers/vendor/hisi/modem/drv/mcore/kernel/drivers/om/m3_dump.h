/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_dump.h
*
*   作    者 :  z67193
*
*   描    述 :  临终遗言功能头文件
*
*   修改记录 :  2012年04月14日  v1.00  z67193  创建
*************************************************************************/
#ifndef	__M3_DUMP_H__
#define __M3_DUMP_H__


#include "bsp_memmap.h"
#include "product_config.h"
#include "osl_types.h"
#include <bsp_modem_log.h>
#include "bsp_dump_mem.h"
#include "bsp_dump.h"

/**************************************************************************
  宏定义
**************************************************************************/
struct hpm_tem_print
{
    unsigned int hpm_hvt_opc;
	unsigned int hpm_uhvt_opc;
	unsigned int hpm_svt_opc;
	signed int	 temperature;
	unsigned char up_volt;
};
/*m3 dump 内存分配*/
#define DUMP_M3_BASE_INFO_ADDR              (DUMP_AREA_LPM3_STATIC_ADDR)
#define DUMP_M3_BASE_INFO_SIZE               0x180
#define DUMP_M3_TASK_SWITCH_ADDR            (DUMP_M3_BASE_INFO_ADDR+DUMP_M3_BASE_INFO_SIZE)
#define DUMP_M3_TASK_SWITCH_SIZE            (0x1000)
#define DUMP_M3_INTLOCK_ADDR                (DUMP_M3_TASK_SWITCH_ADDR+DUMP_M3_TASK_SWITCH_SIZE)
#define DUMP_M3_INTLOCK_SIZE                (0)
#define DUMP_M3_TASK_STACK_ADDR             (DUMP_M3_INTLOCK_ADDR+DUMP_M3_INTLOCK_SIZE)
#define DUMP_M3_TASK_STACK_SIZE             (0x1000)
#define DUMP_M3_INT_STACK_ADDR              (DUMP_M3_TASK_STACK_ADDR+DUMP_M3_TASK_STACK_SIZE)
#define DUMP_M3_INT_STACK_SIZE              (0)
#define DUMP_M3_ALLTASK_ADDR                (DUMP_M3_INT_STACK_ADDR+DUMP_M3_INT_STACK_SIZE)
#define DUMP_M3_ALLTASK_SIZE                (0x800)
#define DUMP_M3_ALLTASK_TCB_ADDR            (DUMP_M3_ALLTASK_ADDR+DUMP_M3_ALLTASK_SIZE)
#define DUMP_M3_ALLTASK_TCB_SIZE            (0x1000)
#define DUMP_M3_PRINT_ADDR                  (DUMP_M3_ALLTASK_TCB_ADDR+DUMP_M3_ALLTASK_TCB_SIZE)
#define DUMP_M3_PRINT_SIZE                  (0x1000)
#define DUMP_M3_LOG_ADDR                    (DUMP_M3_PRINT_ADDR+DUMP_M3_PRINT_SIZE)
#define DUMP_M3_LOG_SIZE                    (0x1000)
#define DUMP_M3_REGS_ADDR                   (DUMP_M3_LOG_ADDR+DUMP_M3_LOG_SIZE)
#define DUMP_M3_REGS_SIZE                   (0x100)
#define DUMP_M3_TCM0_ADDR                   (DUMP_M3_REGS_ADDR+DUMP_M3_REGS_SIZE)
#define DUMP_M3_TCM0_SIZE                   (0)
#define DUMP_M3_TCM1_ADDR                   (DUMP_M3_TCM0_ADDR+DUMP_M3_TCM0_SIZE)
#define DUMP_M3_TCM1_SIZE                   (0)
#define DUMP_M3_BOOST_ADDR                  (DUMP_M3_TCM1_ADDR+DUMP_M3_TCM1_SIZE)
#define DUMP_M3_BOOST_SIZE                  (0x400)
#define DUMP_M3_RSV_ADDR                    (DUMP_M3_BOOST_ADDR+DUMP_M3_BOOST_SIZE)
#define DUMP_M3_RSV_SIZE                    (0)

/*用户空间*/

/**/
#define DUMP_INIT_FLAG                      (0x5B5B0002)
#define DUMP_INIT_FLAG_WAIT                 (0x5C5C5C5C)


#define DUMP_INT_IN_FLAG                    0xAAAA
#define DUMP_INT_EXIT_FLAG                  0xBBBB
#define DUMP_INT_UNLOCK_FLAG                0xCCCC
#define DUMP_SAVE_SUCCESS                   0xA4A4A4A4

#define DUMP_TASK_INFO_SIZE                 0x200
#define DUMP_TASK_INFO_STACK_SIZE           (DUMP_TASK_INFO_SIZE - 32*4)

#define DUMP_M3_TASK_NUM_MAX                8

/* M3 sysctrl reg base */
#define M3_SYSCTRL_BASE                     (0xE000ED00)

typedef enum _dump_reboot_ctx_e
{
    DUMP_CTX_TASK        = 0x0,
    DUMP_CTX_INT         = 0x1
}dump_reboot_ctx_t;

typedef enum _dump_vertor_e
{
    STACK_OVERFLOW      = 0x1,
    FIFO_OVERFLOW         = 0x2,
    MAILBOX_OVERFLOW   = 0x3,
    HARD_FAULT= 0xC,
    MEM_MSG         = 0x10,
    BUS_FAULT= 0x14,
    USAGE_FAULT = 0x18,
    END_ERROR
}dump_vertor_e;

typedef struct
{
    u32 reboot_context;     /*0x00  */
    u32 reboot_task;        /*0x04  */
    u8  taskName[16];       /*0x08  */
    u32 reboot_int;         /*0x18  */

    u32 modId;              /*0x1c  */
    u32 arg1;               /*0x20  */
    u32 arg2;               /*0x24  */
    u32 arg3;               /*0x28  */
    u32 arg3_length;        /*0x2c  */

    u32 vec;                /*0x30  */
    u32 cpsr;               /*0x34  */
    u32 regSet[17];         /*0x38  */

    u32 current_task;       /*0x7c */
    u32 current_int;        /*0x80 */

    u32 cpu_usage;          /*0x84 */
    u32 mem_free;           /*0x88 */
    u32 axi_dlock_reg[3];   /*0x94 --- AXI总线挂死寄存器，0x624,0x628,0x658*/
}dump_base_info_t;

// ALL_TASK_TCB
typedef struct
{
    u32 pid;
    u32 entry;
    u32 status;
    u32 policy;
    u32 priority;
    u32 stack_base;
    u32 stack_end;
    u32 stack_high;
    u32 stack_current;
    u8  name[16];
    u32 regs[17];
    u32 offset;
    u32 rsv[1];
    char dump_stack[DUMP_TASK_INFO_STACK_SIZE];
} dump_task_info_t;

typedef struct
{
    u32 maxNum;
    u32 front;
    u32 rear;
    u32 num;
    u32 data[1];
} dump_queue_t;

typedef struct
{
    struct log_mem log_info;
    u32     logged_chars;   /* number of chars in log buffer */
    u32     w_mark;         /* water mark, if logged chars exceed w_mark, ccore send IPC to acore */
    u32     reserved;       /* reserved for 32-byte align */
    u8 *    log_buf;        /* data area */
}log_mem_stru;

typedef struct
{
    u32 reg_base;
    u32 reg_size;
} dump_sysctrl_reg_t;

#define OM_SYSCTRL_MAGIC        (0x5B5C5C5B)
#define OM_SYSCTRL_CNT          (4)
#define M3_LOG_MAGIC            (0x52524554)

#endif
typedef void (*exc_funcptr)(int, int,int,int,int);

void m3_dump_init(void);
void m3_log_init(void);
void m3_log_print(char ch);
void dump_int_switch_hook(u32 dir, u32 newVec);
extern void printk(const char *fmt, ...);
extern void exc_dump_hook_add(exc_funcptr phookfun);
extern int task_switch_hook_del ( void);

#ifdef ENABLE_BUILD_OM
#define dump_int_enter(irq)\
do{\
    dump_int_switch_hook(0, irq);\
}while(0)

#define dump_int_exit(irq)\
do{\
    dump_int_switch_hook(1, irq);\
}while(0)

#else
#define dump_int_enter(irq)\
do{\
}while(0)

#define dump_int_exit(irq)\
do{\
}while(0)

#endif

