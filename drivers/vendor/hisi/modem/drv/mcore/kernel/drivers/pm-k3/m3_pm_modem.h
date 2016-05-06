#ifndef _M3_PM_MODEM_H_
#define _M3_PM_MODEM_H_

#include <bsp_sram.h>
#include <bsp_shared_ddr.h>

#define MAX_NVIC_GROUP_NUM     8

#define PM_SHM_TIMESTAMP_ADDR       (SHM_BASE_ADDR+SHM_OFFSET_TIMESTAMP_ADDR)

#define PWR_SRAM_DEBUG_ADDR         (SRAM_BASE_ADDR + SRAM_OFFSET_MCU_RESERVE)
#define PWR_SRAM_DEBUG_SIZE         (SRAM_SIZE_MCU_RESERVE)

#define PWR_SRAM_TIMER0            (PWR_SRAM_DEBUG_ADDR)
#define PWR_SRAM_TIMER1            (PWR_SRAM_DEBUG_ADDR + 0x10)
#define PWR_SRAM_TIMER2            (PWR_SRAM_DEBUG_ADDR + 0x20)
#define PWR_SRAM_TIMER3            (PWR_SRAM_DEBUG_ADDR + 0x30)

#define PWR_TCM_ADDR                    (TICKMARK_BASE + 0x100)

#define PWR_TCM_MODEM_DOWN_ADDR         PWR_TCM_ADDR
#define PWR_TCM_MODEM_DOWN_SIZE         0x20

#define PWR_TCM_MODEM_SUSPEND_ADDR      (PWR_TCM_MODEM_DOWN_ADDR + PWR_TCM_MODEM_DOWN_SIZE)
#define PWR_TCM_MODEM_SUSPEND_SIZE       0x30

#define PWR_TCM_MODEM_RESUME_ADDR       (PWR_TCM_MODEM_SUSPEND_ADDR + PWR_TCM_MODEM_SUSPEND_SIZE)
#define PWR_TCM_MODEM_RESUME_SIZE        0x40

#define PWR_TCM_MODEM_UP_ADDR           (PWR_TCM_MODEM_RESUME_ADDR + PWR_TCM_MODEM_RESUME_SIZE)
#define PWR_TCM_MODEM_UP_SIZE            0x40

#define PWR_TCM_MODEM_INIT_ADDR         (PWR_TCM_MODEM_UP_ADDR + PWR_TCM_MODEM_UP_SIZE)
#define PWR_TCM_MODEM_INIT_SIZE          0x20

typedef enum tagPmType
{
	PM_TYEP_CCORE_SLEEP = 2,
	PM_TYEP_CCORE_WAKE = 3,
	PM_TYEP_CSET_WSRC = 5,
	PM_TYEP_CUNSET_WSRC = 7,
	PM_TYEP_BUTTOM = 10
}T_PM_TYPE;

typedef struct
{
	T_PM_TYPE      type;
	u32            addr;
}T_PM_MAIL;

typedef struct
{
	u32 u32CcoreSleepTimes;
    u32 u32CcoreWakeTimes;
    u32 u32CcoreDdrDfsErrTimes;
	u32 u32PrintIrqWsrcFlag;
}T_PM_COUNT_ST;

typedef struct
{
	u32 u32CcoreWsrc[MAX_NVIC_GROUP_NUM];
}T_PM_ST;

#define MODEM_PM_PRINT(fmt,...) (printk("[mdm_pm]: "fmt, ##__VA_ARGS__))

extern void pm_modem_init(void);
extern void pm_modem_to_192(void);
extern void pm_modem_to_a9pll(void);
extern void pm_modem_up(void);
extern void pm_modem_down(void);
extern void pm_mdma9_wsrc_set(u32 lvl);
extern void pm_mdma9_wsrc_unset(u32 lvl);
extern s32 pm_wakeup_ccore(void);
extern void pm_debug_clr_timer(void);
extern void pm_set_debug(u32 type, u32 flag);
extern void mdm_udelay (u32 ms, u32 flag);
extern void pm_print_debug(void);


#endif /* end of _M3_PM_MODEM_H_*/
