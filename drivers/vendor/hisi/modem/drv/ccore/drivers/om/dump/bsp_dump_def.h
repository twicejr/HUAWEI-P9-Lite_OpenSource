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

#ifndef	__BSP_DUMP_DEF_H__
#define __BSP_DUMP_DEF_H__

#include "osl_types.h"
#include "product_config.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  宏定义
**************************************************************************/
#define DUMP_SECTION_INVALID                (-1)

#define DUMP_INT_IN_FLAG                    0xAAAA
#define DUMP_INT_EXIT_FLAG                  0xBBBB
#define DUMP_INT_UNLOCK_FLAG                0xCCCC
#define DUMP_SAVE_SUCCESS                   0xA4A4A4A4

#define DUMP_TASK_INFO_SIZE                 0x200
#define DUMP_TASK_INFO_STACK_SIZE           (DUMP_TASK_INFO_SIZE - 32*4)

#define ARM_REGS_NUM                        17

/**************************************************************************
  STRUCT定义
**************************************************************************/
typedef enum _dump_reboot_ctx_e
{
    DUMP_CTX_TASK        = 0x0,
    DUMP_CTX_INT         = 0x1
}dump_reboot_ctx_t;

typedef enum _dump_arm_vec_e
{
    DUMP_ARM_VEC_RESET          = 0x0,
    DUMP_ARM_VEC_UNDEF          = 0x4,
    DUMP_ARM_VEC_SWI            = 0x8,
    DUMP_ARM_VEC_PREFETCH       = 0xc,
    DUMP_ARM_VEC_DATA           = 0x10,
    DUMP_ARM_VEC_IRQ            = 0x18,
    DUMP_ARM_VEC_FIQ            = 0x1c,
    DUMP_ARM_VEC_UNKNOW         = 0xff,
}dump_arm_vec_t;


typedef struct
{
    u32 maxNum;
    u32 front;
    u32 rear;
    u32 num;
    u32 data[1];
} dump_queue_t;

#define D_TASK_RUNNING		    0
#define D_TASK_INTERRUPTIBLE	1
#define D_TASK_UNINTERRUPTIBLE	2
#define D_TASK_STOPPED		    4
#define D_TASK_TRACED		    8
#define D_EXIT_ZOMBIE		    16
#define D_EXIT_DEAD		        32
#define D_TASK_DEAD		        64
#define D_TASK_WAKEKILL		    128
#define D_TASK_WAKING		    256
#define D_TASK_STATE_MAX		512

#define D_WIND_READY            0x00    /* ready to run */
#define D_WIND_SUSPEND          0x01    /* explicitly suspended */
#define D_WIND_PEND             0x02    /* pending on semaphore */
#define D_WIND_DELAY            0x04    /* task delay (or timeout) */
#define D_WIND_DEAD             0x08    /* dead task */
#define D_WIND_STOP             0x10    /* stopped by the debugger */
#define D_WIND_STATE_CHANGE     0x20    /* currently changing state */

typedef enum{
    TASK_SCHED_NORMAL = 0,
    TASK_SCHED_FIFO,
    TASK_SCHED_RR,
    TASK_SCHED_BATCH,
    TASK_SCHED_IDLE
}dump_sched_policy_t;

/*  CPSR R16
  31 30  29  28   27  26    7   6   5   4    3    2    1    0
----------------------------------------------------------------
| N | Z | C | V | Q | RAZ | I | F | T | M4 | M3 | M2 | M1 | M0 |
---------------------------------------------------------------- */

/*  REG
R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13/SP R14/LR R15/PC R16/CPSR
*/

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
    u32 axi_dlock_reg[3];   /*0x8C --- AXI总线挂死寄存器，0x624,0x628,0x658*/
    u32 int_stack_base;     /*0x98 */
    u32 int_stack_end;      /*0x9C */
    u8  version[32];        /*0xA0 */
    u8  compile_time[32];   /*0xB0 */
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
    u32 regs[ARM_REGS_NUM];
    u32 offset;
    u32 rsv[1];
    char dump_stack[DUMP_TASK_INFO_STACK_SIZE];
} dump_task_info_t;


/*         ==============================
          |         reg_addr1            |
          |------------------------------|
          |         reg_size1            |
          |------------------------------|
          |         reg_addr2            |
          |------------------------------|
          |         reg_size2            |
          |------------------------------|
          |         reg_addr3            |
          |------------------------------|
          |         reg_size3            |
          |------------------------------|
          |         resv                 |
          |==============================|
          |   |   reg group1(4K)    |    |
          |   -----------------------    |
          |   |   reg group1(4K)    |    |
          |   -----------------------    |
          |   |   reg group1(4K-16) |    |
           ==============================
*/
//最多支持3组，每组最大4K，具体大小按照头信息指示
typedef struct
{
    u32 reg_addr1;
    u32 reg_size1;
    u32 reg_addr2;
    u32 reg_size2;
    u32 reg_addr3;
    u32 reg_size3;
    u32 resv[2];
} dump_regs_map_t;


typedef struct {
	unsigned magic;
	unsigned log_start;	/* Index into log_buf: next char to be read by syslog() */
	unsigned log_end;	/* Index into log_buf: most-recently-written-char + 1 */
	unsigned logged_chars; /* Number of chars produced since last read+clear operation */
	int      log_buf_len;
	char    *log_buf;
} demsg_buff_t;

typedef struct
{
    unsigned long task_swt_ptr;
    unsigned long int_lock_ptr;
} dump_debug_info_t;


/**************************************************************************
  UNION定义
**************************************************************************/

/**************************************************************************
  OTHERS定义
**************************************************************************/




#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif    /* End #define __BSP_DUMP_H__ */



