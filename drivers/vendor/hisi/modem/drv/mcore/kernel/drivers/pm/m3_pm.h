#ifndef __M3_PM_H__
#define __M3_PM_H__

#include "osl_types.h"
#include "bsp_sram.h"
#include <bsp_shared_ddr.h>
#include <irq.h>

#define PM_SLEEP_VOTE_MASK    \
       ((0x1 << PM_PWR_VOTE_ACORE) | (0x1 << PM_PWR_VOTE_CCORE) | (0x1 << PM_PWR_VOTE_HIFI))

#define PM_SHM_TIMESTAMP_ADDR   (SHM_BASE_ADDR+SHM_OFFSET_TIMESTAMP)

enum debug_wake_type{
	PM_WAKEUP,
	PM_WAKEUP_THEN_SLEEP,
};

typedef enum tagPwrVote
{
	PM_PWR_VOTE_ACORE = 0,
	PM_PWR_VOTE_CCORE = 1,
	PM_PWR_VOTE_HIFI  = 2
}T_PM_PWR_VOTE;

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
	PM_TYEP_HIFI_SLEEP = 8,
	PM_TYEP_HIFI_WAKE = 9,
	PM_TYEP_BUTTOM = 10
}T_PM_TYPE;

typedef struct
{
	T_PM_TYPE      type;
	u32            addr;
}T_PM_MAIL;

typedef struct
{
	u32 u32VoteMap;
	u32 u32VoteMask;
	u32 u32SleepFlag;
	u32 u32AcoreWsrc[4];
	u32 u32CcoreWsrc[4];
	u32 u32McoreWsrc[4];
    u32 u32HiFiWsrc[4];
}T_PM_ST;

typedef struct
{
	u32 u32ClkDiv;
	u32 u32NvicEnable[8];
}T_PM_BAKEUP_ST;

typedef struct
{
	u32 SleepTimes;
	u32 WakeIrq;
}T_PM_CORE_WAKE_ST;

typedef struct
{
	u32 u32NormalWfiTimes;
	u32 u32DeepSleepTimes;
	u32 u32McuTimerIntTimes;
    T_PM_CORE_WAKE_ST Acore;
    T_PM_CORE_WAKE_ST Ccore;
    T_PM_CORE_WAKE_ST HiFi;
    T_PM_CORE_WAKE_ST Mcore;

	u32 u32CcoreSleepTimes;
    u32 u32CcoreWakeIrq;
    u32 u32CcoreWakeSlice;
    u32 u32HiFiSleepTimes;
    u32 u32HiFiWakeIrq;
    u32 u32HiFiWakeSlice;
	u32 u32PwrRegbakFlag;
	u32 u32WakeupDebugFlag;
	u32 u32PrintIrqWsrcFlag;
    u32 u32SleepWithoutWfiFlag;
    /* u32DebugCanSleepTime 
    默认为0 表示非debug模式正常睡眠
    1 表示不睡眠， 大于1表示睡眠(u32DebugCanSleepTime-1)次
    */
    u32 u32DebugCanSleepTime; 
}T_PM_COUNT_ST;

typedef struct
{
	u32 u32DpmSuspendErrTimes;
	u32 u32DpmResumeErrTimes;
	u32 u32AxiBakeupErrTimes;
	u32 u32AxiRestoreErrTimes;
}T_PM_ERROR_ST;


/**************************************************************/
/* sram debug addr */
#define PWR_SRAM_DEBUG_ADDR         (SRAM_BASE_ADDR + SRAM_OFFSET_MCU_RESERVE)
#define PWR_SRAM_DEBUG_SIZE         (SRAM_SIZE_MCU_RESERVE)


#define M3_PM_STAMP_ADDR           (PWR_SRAM_DEBUG_ADDR)

#define strMailAllocFail         "osMailCAlloc failed"

struct m3pm_buck3off
{ /*  5* 4* 4Bytes   */

    /* buck3off */
    u32 magic_start; /*init to 0x5A33335A*/
    u32 magic_asc_3off; /*init to 0x46464F33  "3OFF"*/
    u32 buck3off_cnt;
    u32 no_sm_cnt; /* when state machine do not go deepsleep */

    u32 magic_stamp; /*init to 0x5A33335A*/
    u32 in_buck3off_branch;
    u32 after_dpm_suspend_buck3off; /* close pmu */
    u32 after_buck3off_init;
    /*pm_mcu_buck3off_pdown()*/
    u32 after_ios_suspend;
    u32 after_sysreg_suspend;
    u32 after_sram_suspend;
    u32 after_ddr_sref;
    u32 before_sram_retention;

    u32 magic_go_to_sleep;/*init to 0x5A33335A*/

    /*pm_mcu_buck3off_pup()*/
    u32 after_sram_out_retention;
    u32 before_sysreg_resume;
    u32 after_ios_resume;
    u32 after_rf_resetn;
    u32 before_ddr_restore;/*state machine deepsleep*/
    u32 after_ddr_restore;/*state machine deepsleep*/
    u32 no_boot_not_ddr_restore;/*state machine no deepsleep*/
    u32 after_ddr_out_sref;
    u32 before_sram_resume;
    u32 buck3off_pup_end;

    u32 after_dpm_resume_buck3off; /* resume pmu */
}__attribute__ ((aligned (16)));

struct m3pm_buck3on
{ /*  17* 4Bytes = 5 *4*4   */
    /* buck3on */
    u32 magic_start; /*init to 0x5A00005A*/
    u32 magic_asc_3on; /*init to 0x004E4F33  "3ON"*/
    u32 buck3on_cnt;
    u32 no_sm_cnt; /* when state machine do not go deepsleep */

    u32 magic_stamp; /*init to 0x5A00005A*/
    u32 in_buck3on_branch;
    u32 after_gpio_suspend;
    u32 after_sysreg_suspend;
    u32 after_sram_suspend;
    
    u32 after_ddr_sref;
    u32 before_sram_retention;

    u32 magic_go_to_sleep;/*init to 0x5A00005A*/
    
    u32 after_sram_out_retention;
    u32 before_ddr_restore;/*state machine deepsleep*/
    u32 after_ddr_restore;/*state machine deepsleep*/
    u32 no_boot_not_ddr_restore;/*state machine no deepsleep*/

    u32 after_ddr_out_sref;
    u32 before_sysreg_resume;
    u32 after_sysreg_resume;
    u32 after_sram_resume;
    u32 after_gpio_resume;
    u32 buck3on_pup_end;
    
}__attribute__ ((aligned (16)));


struct m3_pm_stamp
{
    u32 magic_asc_m3pm; /*init to: 0x6D70336D  ascii:"m3pm"  */
    /* counts */
    u32 deepsleep_cnt;
    u32 wfi_cnt;
    u32 dpm_fail_cnt;
    u32 ddr_hit_test_out_cnt;
    u32 loop_delay_dummy;
    
    u32 magic_stamp1; /*init to 0x5A5A5A5A*/
    /* in pm_deepsleep()*/
    u32 before_dpm_suspend;
    u32 after_dpm_suspend;
    
    /* in pm_mcu_process() */
    u32 after_dfs_bak;
    /* buck3on /off  pdown-pup */
    u32 before_dpm_resume;
    u32 after_dpm_resume;
    
    /*buck3on/off*/
    struct m3pm_buck3off buck3off;
    struct m3pm_buck3on buck3on;
};

#if 0
#define PWR_SRAM_TIMER0            (PWR_SRAM_DEBUG_ADDR)
#define PWR_SRAM_TIMER1            (PWR_SRAM_DEBUG_ADDR + 0x10)
#define PWR_SRAM_TIMER2            (PWR_SRAM_DEBUG_ADDR + 0x20)
#define PWR_SRAM_TIMER3            (PWR_SRAM_DEBUG_ADDR + 0x30)
#define PWR_SRAM_TIMER4            (PWR_SRAM_DEBUG_ADDR + 0x40)
#define PWR_SRAM_TIMER5            (PWR_SRAM_DEBUG_ADDR + 0x50)
#define PWR_SRAM_TIMER6            (PWR_SRAM_DEBUG_ADDR + 0x60)
#define PWR_SRAM_TIMER7            (PWR_SRAM_DEBUG_ADDR + 0x70)
#define PWR_SRAM_TIMER8            (PWR_SRAM_DEBUG_ADDR + 0x80)
#define PWR_SRAM_TIMER9            (PWR_SRAM_DEBUG_ADDR + 0x90)
#define PWR_SRAM_TIMER10           (PWR_SRAM_DEBUG_ADDR + 0xa0)


#define PWR_SRAM_TIMER21           (PWR_SRAM_DEBUG_ADDR + 0x24)
#define PWR_SRAM_TIMER22           (PWR_SRAM_DEBUG_ADDR + 0x28)

#define PWR_SRAM_TIMER41           (PWR_SRAM_DEBUG_ADDR + 0x44)
#define PWR_SRAM_TIMER42           (PWR_SRAM_DEBUG_ADDR + 0x48)

#define PWR_SRAM_TIMER51           (PWR_SRAM_DEBUG_ADDR + 0x54)
#define PWR_SRAM_TIMER52           (PWR_SRAM_DEBUG_ADDR + 0x58)
#define PWR_SRAM_TIMER53           (PWR_SRAM_DEBUG_ADDR + 0x5c)

#define PWR_SRAM_TIMER61           (PWR_SRAM_DEBUG_ADDR + 0x64)
#define PWR_SRAM_TIMER62           (PWR_SRAM_DEBUG_ADDR + 0x68)
#define PWR_SRAM_TIMER63           (PWR_SRAM_DEBUG_ADDR + 0x6C)

#define PWR_SRAM_TIMER71           (PWR_SRAM_DEBUG_ADDR + 0x74)
#define PWR_SRAM_TIMER72           (PWR_SRAM_DEBUG_ADDR + 0x78)

#define PWR_SRAM_TIMER81           (PWR_SRAM_DEBUG_ADDR + 0x84)

#endif

#define PWR_SRAM_PWRCTRL_REG       (PWR_SRAM_DEBUG_ADDR + 0x100)
#define PWR_SRAM_WAKEUP_NUM_REG    (PWR_SRAM_DEBUG_ADDR + 0x200)
#define PWR_SRAM_WAKEUP_REG        (PWR_SRAM_DEBUG_ADDR + 0x210)

#define PWR_SRAM_CRG_REG           (PWR_SRAM_DEBUG_ADDR + 0x300)


#define DPM_SRAM_DEBUG_ADDR (PWR_SRAM_DEBUG_ADDR+ SRAM_SIZE_MCU_RESERVE)
#define DPM_SRAM_TIMER1           (DPM_SRAM_DEBUG_ADDR - 0x4)
#define DPM_SRAM_TIMER2           (DPM_SRAM_DEBUG_ADDR - 0x8)
#define DPM_SRAM_TIMER3           (DPM_SRAM_DEBUG_ADDR - 0xC)
#define DPM_SRAM_TIMER4           (DPM_SRAM_DEBUG_ADDR - 0x10)
#define DPM_SRAM_TIMER5           (DPM_SRAM_DEBUG_ADDR - 0x14)
#define DPM_SRAM_TIMER6          (DPM_SRAM_DEBUG_ADDR - 0x18)
#define DPM_SRAM_TIMER7          (DPM_SRAM_DEBUG_ADDR - 0x1C)
#define DPM_SRAM_TIMER8           (DPM_SRAM_DEBUG_ADDR - 0x20)
#define DPM_SRAM_TIMER9           (DPM_SRAM_DEBUG_ADDR - 0x24)
#define DPM_SRAM_TIMER10           (DPM_SRAM_DEBUG_ADDR - 0x28)
#define DPM_SRAM_TIMER11           (DPM_SRAM_DEBUG_ADDR - 0x2C)
#define DPM_SRAM_TIMER12          (DPM_SRAM_DEBUG_ADDR - 0x30)
#define DPM_SRAM_TIMER13          (DPM_SRAM_DEBUG_ADDR - 0x34)
#define DPM_SRAM_TIMER14           (DPM_SRAM_DEBUG_ADDR - 0x38)
#define DPM_SRAM_TIMER15           (DPM_SRAM_DEBUG_ADDR - 0x3C)

#define RFIC0_RSTN_OFFSET          (0x2c)


#define ACORE_BUCK3_ONOFF_FLAG   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_BUCK3_ACORE_ONOFF_FLAG)
#define CCORE_BUCK3_ONOFF_FLAG   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_BUCK3_CCORE_ONOFF_FLAG)


#ifdef CONFIG_M3PM

extern void pm_config_init(void);
extern void pm_wsrc_init(void);
extern void pm_appa9_nvic_disable(void);
extern void pm_mdma9_nvic_disable(void);
extern void pm_hifi_nvic_disable(void);
extern void print_acore_wsrc(void);
extern void print_ccore_wsrc(void);
extern void pm_acore_sleep(void);
extern void pm_ccore_sleep(void);
extern void pm_hifi_sleep(void);
extern void pm_acore_wake(void);
extern void pm_ccore_wake(void);
extern void pm_hifi_wake(void);
extern void pm_hifi_pll_open(u32 vote);
extern void pm_dsp_pll_open(u32 vote);
extern void pm_mdma9_wsrc_set(u32 lvl);
extern void pm_mdma9_wsrc_unset(u32 lvl);

extern void pm_init(void);
//extern u32 pm_get_deepsleep_status(void);
extern void pm_wake_lock(T_PM_PWR_VOTE vote);
extern void pm_wake_unlock(T_PM_PWR_VOTE vote);
extern u32 pm_is_wake_lock(T_PM_PWR_VOTE vote);
extern irqreturn_t IntHiFiHandler(int irq, void* data); 
extern irqreturn_t IntCcoreHandler(int irq, void* data);
extern irqreturn_t IntAcoreHandler(int irq, void* data);
extern void idle_task(void);

#else

static inline void pm_config_init(void){};
static inline void pm_wsrc_init(void){};
static inline void pm_appa9_nvic_disable(void){}
static inline void pm_mdma9_nvic_disable(void){}
static inline void pm_hifi_nvic_disable(void){}
static inline void print_acore_wsrc(void){}
static inline void print_ccore_wsrc(void){}
static inline void pm_acore_sleep(void){}
static inline void pm_ccore_sleep(void){}
static inline void pm_hifi_sleep(void){}
static inline void pm_acore_wake(void){}
static inline void pm_ccore_wake(void){}
static inline void pm_hifi_wake(void){}
static inline void pm_hifi_pll_open(u32 vote){};
static inline void pm_dsp_pll_open(u32 vote){};
static inline void pm_mdma9_wsrc_set(u32 lvl){};
static inline void pm_mdma9_wsrc_unset(u32 lvl){};

static inline void pm_init(void){};
static inline void pm_wake_lock(T_PM_PWR_VOTE vote){};
static inline void pm_wake_unlock(T_PM_PWR_VOTE vote){};
static inline u32 pm_is_wake_lock(T_PM_PWR_VOTE vote){return 1;};
static inline irqreturn_t IntHiFiHandler(int irq, void* data){return IRQ_HANDLED;}; 
static inline irqreturn_t IntCcoreHandler(int irq, void* data){return IRQ_HANDLED;};
static inline irqreturn_t IntAcoreHandler(int irq, void* data){return IRQ_HANDLED;};
static inline void idle_task(void){}

#endif


#endif
