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
/*lint --e{959}*/
#ifndef	__BSP_DUMP_DRV_H__
#define __BSP_DUMP_DRV_H__

#ifndef __ASSEMBLY__
#include "product_config.h"
#include <mdrv_public.h>
#include "osl_types.h"
#endif/*#ifndef __ASSEMBLY__*/
#if defined(__OS_VXWORKS__)
#include <config.h>
#endif
#include <bsp_memmap.h>
#include "bsp_dump_mem.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/*COMM段内存分配*/
#define DUMP_BASE_INFO_ADDR                 (DUMP_AREA_CP_STATIC_ADDR)
#define DUMP_BASE_INFO_SIZE                 (0x180)
#define DUMP_TASK_SWITCH_ADDR               (DUMP_BASE_INFO_ADDR+DUMP_BASE_INFO_SIZE)
#define DUMP_TASK_SWITCH_SIZE               (0x10000)
#define DUMP_INTLOCK_ADDR                   (DUMP_TASK_SWITCH_ADDR+DUMP_TASK_SWITCH_SIZE)
#define DUMP_INTLOCK_SIZE                   (0x1000)
#define DUMP_TASK_STACK_ADDR                (DUMP_INTLOCK_ADDR+DUMP_INTLOCK_SIZE)
#define DUMP_TASK_STACK_SIZE                (0x2000)
#define DUMP_INT_STACK_ADDR                 (DUMP_TASK_STACK_ADDR+DUMP_TASK_STACK_SIZE)
#if defined(__OS_VXWORKS__)
#define DUMP_INT_STACK_SIZE                 (ISR_STACK_SIZE)
#else
#define DUMP_INT_STACK_SIZE                 (0x2000)
#endif
#define DUMP_ALLTASK_ADDR                   (DUMP_INT_STACK_ADDR+DUMP_INT_STACK_SIZE)
#define DUMP_ALLTASK_SIZE                   (0x800)
#define DUMP_ALLTASK_TCB_ADDR               (DUMP_ALLTASK_ADDR+DUMP_ALLTASK_SIZE)
#define DUMP_ALLTASK_TCB_SIZE               (0x10000)
#define DUMP_PRINT_ADDR                     (DUMP_ALLTASK_TCB_ADDR+DUMP_ALLTASK_TCB_SIZE)
#define DUMP_PRINT_SIZE                     (0x4000)
#define DUMP_DMESG_ADDR                     (DUMP_PRINT_ADDR+DUMP_PRINT_SIZE)
#define DUMP_DMESG_SIZE                     (0x4000)
#define DUMP_REGS_ADDR                      (DUMP_DMESG_ADDR+DUMP_DMESG_SIZE)
#define DUMP_REGS_SIZE                      (0x3000)                                     // 待定
#define DUMP_CPUVIEW_ADDR                   (DUMP_REGS_ADDR+DUMP_REGS_SIZE)
#define DUMP_CPUVIEW_SIZE                   (0)
#define DUMP_USER_DATA_ADDR                 (DUMP_CPUVIEW_ADDR+DUMP_CPUVIEW_SIZE)
#define DUMP_USER_DATA_SIZE                 (0x1000)
#define DUMP_TASK_TCB_ADDR                  (DUMP_USER_DATA_ADDR+DUMP_USER_DATA_SIZE)
#define DUMP_TASK_TCB_SIZE                  (0x1000)
#define DUMP_EXT_OM_RTOSCK_CDA_ADDR         (DUMP_TASK_TCB_ADDR+DUMP_TASK_TCB_SIZE)
#define DUMP_EXT_OM_RTOSCK_CDA_SIZE         (50*1024)

#define DUMP_RSV_ADDR                       (DUMP_EXT_OM_RTOSCK_CDA_ADDR+DUMP_EXT_OM_RTOSCK_CDA_SIZE)
#define DUMP_RSV_SIZE                       (0)

#define DUMP_INIT_FLAG_PHASE1               (0x5B5B0000)
#define DUMP_INIT_FLAG_PHASE2               (0x5B5B0001)
#define DUMP_INIT_FLAG                      (0x5B5B0002)
#define DUMP_INIT_FLAG_WAIT                 (0x5C5C5C5C)

#ifndef __ASSEMBLY__
/**************************************************************************
  STRUCT定义
**************************************************************************/
#define MAX_TRC_ARGS        20
#define MAX_SCAN_DEPTH      2000
#define MAX_TRACE_DEPTH		40

#define OFFSET_MASK         0x00000fff
#define INSTR_MASK          0xfffff000
#define STMDB_SP_MASK       0xffffc000
#define PUSH_SP_MASK        0xfffff000
#define FP_MASK             0x00000800
#define VALUE_MASK          0x000000ff
#define ROTATION_MASK       0x00000f00
#define MULEQ_SP_MASK       0xffff00f0

#define STDDB_SP_INSTR      0xe92d4000
#define PUSH_SP_INSTR       0xe92dd000
#define SUB_SP_SP_IMM_INSTR 0xe24dd000
#define STR_LR_SP_INSTR     0xe52de004
#define SUB_SP_SP_IP_INSTR  0xe04dd00c
#define MOV_IP_IMM_INSTR    0xe3a0c000
#define LDR_IP_PC_IMM_INSTR 0xe59fc000
#define MULEQ_SP_INSTR      0x000d0090

#define BOGUS_SP(sp, low, high)	((!ALIGNED(sp, _STACK_ALIGN_SIZE)) || ((sp) <= (low)) || ((sp) >= (high)))
#define PC_VALIDATE(pc, pCtx)	pCtx->pcValidateRtn((pc), pCtx)

#ifndef FUNC_VOID
typedef void (*func_void_t)(void);
#define FUNC_VOID func_void_t
#endif
//typedef s32 (*FUNCPTR)(void);

struct hpm_tem_print
{
    unsigned int hpm_hvt_opc;
	unsigned int hpm_uhvt_opc;
	unsigned int hpm_svt_opc;
	signed int	 temperature;
	unsigned char up_volt;
};

#if defined(__OS_VXWORKS__)
typedef struct trc_lvl_info
{
    char *	fp;		    /* frame pointer */
    INSTR *	prevPc;		/* call from PC */
    INSTR *	funcAddr;	/* function address */
} TRC_LVL_INFO;

typedef struct
{
    char *  buffer;
    u32 bufferLen;
    FUNCPTR callPrintFunc;
}UserTraceCtx;
#endif

#ifdef __OS_RTOSCK__ 
typedef struct
{
    char *  buffer;
    u32 bufferLen;
    FUNCPTR callPrintFunc;
}UserTraceCtx;
#endif


typedef struct _dump_ctrl_s
{
    u32 current_task_info;           /*0xA0 */
}dump_ctrl_s;

typedef struct
{
    u32 wdtSwitch;
    u32 wdtTimerOut;  /*看门狗超时时间，单位ms*/
    u32 sys_view;

    union
    {
        u32 uintValue;
        struct
        {
            u32 sci_switch     : 1; /* 00: excdump, 01: usbdump, 1x: no dump */
            u32 usb_switch     : 1; /* 2 ARM异常检测开关*/
            u32 pmu_switch     : 1; /* 3 堆栈溢出检测开关*/
            u32 sd_switch      : 1; /* 3 堆栈溢出检测开关*/
            u32 icc_switch     : 1; /* 3 堆栈溢出检测开关*/
            u32 ifc_switch     : 1; /* 4 任务切换记录开关*/
            u32 reserved1      : 26;
        } Bits;
    } mod_cfg;
} OM_NV;

typedef struct
{
    unsigned long tid;
    char          taskname[12];
} task_name_t;

/**************************************************************************
  UNION定义
**************************************************************************/

/**************************************************************************
  OTHERS定义
**************************************************************************/
#define dump_debug(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,   BSP_MODU_DUMP, "[dump]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define dump_warning(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_DUMP, "[dump]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define dump_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,   BSP_MODU_DUMP, "[dump]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define dump_fetal(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL,   BSP_MODU_DUMP, "[dump]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))


/**************************************************************************
  函数声明
**************************************************************************/



#endif/*#ifndef __ASSEMBLY__*/

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif    /* End #define __BSP_DUMP_H__ */





