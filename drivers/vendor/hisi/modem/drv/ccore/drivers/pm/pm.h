/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  pm.h
*
*   作    者 :  y00221789
*
*   描    述 :
*
*   修改记录 :  2013年4月7日  v1.00  s00219058  创建
*   todo:

*************************************************************************/

#ifndef __PM_H__
#define __PM_H__
/*lint -save -e760*/
#ifndef __ASSEMBLY__
#include <bsp_pm.h>
#include "bsp_sram.h"
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#include <bsp_wakelock.h>
#define PM_ERROR    (-1)
#define PM_OK       (0)

#define PM_TEST_WSRC
#define pm_printk(level, fmt, ...)      (bsp_trace(level, BSP_MODU_PM, "[pm]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))

extern void pm_asm_boot_code_begin(void);
extern void pm_asm_cpu_go_sleep(void);
extern void pm_asm_sleep_end(void);
static inline void WFI(void)
{
	asm volatile ( "dsb;" );/*lint !e123*/
    	asm volatile ( "isb;");/*lint !e123*/
	asm volatile ( "wfi;");/*lint !e123*/
	asm volatile ( "nop;");/*lint !e123*/
	asm volatile ( "nop;");/*lint !e123*/
}

/* 动态设置唤醒源 发送  icc */
typedef enum tagPmType
{
	PM_TYEP_ACORE_SLEEP = 0,
	PM_TYEP_ACORE_WAKE = 1,
	PM_TYEP_CCORE_SLEEP = 2,
	PM_TYEP_CCORE_WAKE = 3,
	PM_TYEP_ASET_WSRC = 4,
	PM_TYEP_CSET_WSRC = 5,
	PM_TYEP_AUNSET_WSRC = 6,
	PM_TYEP_CUNSET_WSRC = 7,
	PM_TYEP_BUTTOM = 8
}T_PM_TYPE;
typedef struct
{
	T_PM_TYPE      type;
	u32            addr;
}T_PM_MAIL;

#endif
#define _asm_function_called_from_c(a) \
    .globl a ;\
    .code  32 ;\
    .balign 4 ;\
a:
#define	_asm_variable_(a) \
	.global a ;\
	a: \
	.long 0

#define I_BIT   (1<<7)
#define F_BIT   (1<<6)
/*lint -restore +e760*/

	/* mode bits */
#define MODE_SYSTEM32	0x1F
#define MODE_UNDEF32	0x1B
#define	MODE_ABORT32	0x17
#define MODE_SVC32		0x13
#define MODE_IRQ32      0x12
#define MODE_FIQ32      0x11
#define MODE_USER32		0x10

	/* mode bits */
#define MODE_MASK      MODE_SYSTEM32
//#define PM_MEM_V2P(addr)            SHD_DDR_V2P(addr)
#define PM_STAMP_ADDR       (pm_stamp_addr)
#define PM_STAMP_ADDR_PHY   (pm_stamp_addr_phy)

#define DEBUG_PM_STAMP
#ifdef DEBUG_PM_STAMP
    #define _asm_debug_pm_stamp(macro_addr)\
        LDR    r0, =(macro_addr) ;\
        LDR    r0,[r0];\
        LDR    r1, =(pm_stamp_addr) ;\
        LDR    r1,[r1];\
        LDR    r2, [r1] ;\
        STR    r2, [r0]
    #define _asm_debug_pm_stamp_v2p(macro_addr)\
        LDR    r0, =(macro_addr);\
        LDR    r0,[r0];\
        LDR    r1, =(pm_stamp_addr_phy) ;\
        LDR    r1,[r1];\
        LDR    r2, [r1] ;\
        STR    r2, [r0]
#else
    #define _asm_debug_pm_stamp(macro_addr)
    #define _asm_debug_pm_stamp_v2p(macro_addr)
#endif

//#define DEBUG_PM_PRINT
#ifdef DEBUG_PM_PRINT
    #define _asm_debug_pm_print_virt(char)\
    LDR r0, =pm_hi_uart1_regbase_addr_virt ;\
    LDR r0,[r0];\
    LDR r1, =char ;\
    STR r1, [r0]
    #define _asm_debug_pm_print_phy(char)\
    LDR r0, =pm_hi_uart1_regbase_addr;\
    LDR r0,[r0];\
    LDR r1, =char ;\
    STR r1, [r0]
#else
    #define _asm_debug_pm_print_virt(char)
    #define _asm_debug_pm_print_phy(char)
#endif

/*********  pm start **********/
/* a9热启动地址控制。*/
#define A9_BOOT_ALIGN_64K  0
#define A9_BOOT_ALIGN_32K  1
#define A9_BOOT_ALIGN_16K  2
#define A9_BOOT_ALIGN_8K   3


/* boot addr after WFI & powerdown */
#define PM_MEM_CCORE_BASE_ADDR        (pm_mem_ccore_base_addr)
#define PM_ASM_CODE_COPY_OFFSET 0x200  /* data-section in asm*/

#define DSARM0_BASE_ADDR                (PM_MEM_CCORE_BASE_ADDR+0x1000)
#define DSRAM0_DEEPSLEEP_ADDR           (DSARM0_BASE_ADDR + 0x200)

/* in asm save regs(arm,arm-corp,mmu), when powerup restore them */
/*  save r0-r14 */
#define BAK_ARM_REG_ADDR        (DSRAM0_DEEPSLEEP_ADDR + 0x0)  // (14+1) = 0x38
#define BAK_ARM_REG_SIZE        (0x50)
/* store cor_reg */
#define BAK_ARM_CO_REG_ADDR     (BAK_ARM_REG_ADDR + BAK_ARM_REG_SIZE)  //(21+1) = 0x58
#define BAK_ARM_CO_REG_SIZE     (0xD0)
/* store mmu */
#define BAK_MMU_REG_ADDR        (BAK_ARM_CO_REG_ADDR + BAK_ARM_CO_REG_SIZE)  // (12+1) = 0x34
#define BAK_MMU_REG_SIZE        (0x50)

/* cpsr control bits */
#define CTRL_MMU_BIT            (0x01)
#define CTRL_ICACHE_BIT         (1<<12)
#define CTRL_DCACHE_BIT         (1<<2)
#define CTRL_CACHE_BIT          (CTRL_DCACHE_BIT | CTRL_ICACHE_BIT)
#define CTRL_MMU_CACHE          (CTRL_MMU_BIT | CTRL_CACHE_BIT)
#ifndef __ASSEMBLY__


struct pm_om_info{
	u32 dpm_fail_count;
    u32 pm_enter_count;
    u32 pm_enter_asm_count;
    u32 pm_enter_wfi_count;
    u32 pm_out_count;
    u32 suspend_start_time;
    u32 suspend_end_time;
	u32 suspend_max_start_time;
    u32 suspend_max_end_time;
    u32 suspend_max_time;
    u32 resume_start_time;
    u32 resume_end_time;
    u32 resume_max_time;
    u32 dpm_suspend_max;
    u32 dpm_resume_max;
};
#define MAX_PWR_ID_NAME_SIZE 11
#define MAX_PWR_OPS_SIZE 4
typedef struct ST_PWC_SLEEP_OPS_STRU_S
{
	unsigned char    name[MAX_PWR_ID_NAME_SIZE];
	PWC_SLEEP_FUNCPTR     funcSleepIn;
	PWC_SLEEP_FUNCPTR     funcSleepOut;
	u32 latest_suspend_time[2];/*for om record:0:start;1:end*/
	u32 latest_resume_time[2];/*for om recordom:0:start;1:end*/
	u32 max_suspend_time_duration;
	u32 max_resume_time_duration;

} ST_PWC_SLEEP_OPS_STRU;

struct pm_info
{
	struct pm_om_info pm_om;
    u32 stamp_addr;
	T_MODEM_SR_STAMP_STRU *mdm_sr_stamp_base;
    u32 gic_flag;   /* 若不禁GIC 直接从wfi出来，测试整个流程。 */
    u32 sleep_flag; /* 0 - 走dpm cpu不睡眠；奇数 - cpu睡眠; 偶数 - cpu睡眠一次后置为0 ;*/
    u32 deepsleep_nv;
    u32 deepsleep_Tth_nv;
    u32 TLbbp_sleeptimer_Tth_nv;    /* 默认 10ms */
	u32 slice_freq;
	u64 pm_base_tick;
	u64 pm_base_slice;
	u64 tick_adjust_before;
	u64 tick_adjust_after;
	u64 pm_init_tick;
	u64 pm_init_slice;
	u64 pm_wakeup_slice;
	u32 sr_time_limit_flag ;
	u32 bug_reset_modem_flag ;
	u32 print_to_ddr_flag ;
    u32 pm_suspend_threshold ;
    u32 pm_resume_threshold;
    u32 dpm_suspend_threshold ;
    u32 dpm_resume_threshold;
	u32 reserved;
	ST_PWC_SLEEP_OPS_STRU g_stSleepOps[MAX_PWR_OPS_SIZE];
};
struct idle_pm_s{
	u32 slice;
	u32 idle_time_ms;
	u32 bbp_sleeptimer;
};
struct pm_wake_src_s{
	u32 time_slice;
	int task_id;
	unsigned int set_type;
	unsigned int  wake_src;
};

void debug_pm_wake_lock(void);
void debug_pm_wake_unlock(void);
void pm_check_time_limit(void);
extern u32 bsp_get_ipc_base_addr(void);
extern void tcxo_suspend(void);
extern void tcxo_resume(void);


#endif
#endif

