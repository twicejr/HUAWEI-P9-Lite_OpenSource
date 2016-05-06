
#ifndef __M3_PM_TEST_H__
#define __M3_PM_TEST_H__


#include <soc_memmap.h>

/* c->m send ipc_int  addr & bit  */
#define  PM_C2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)
#define  PM_C2M_IPC_BIT        (0x1<<IPC_MCU_INT_SRC_CCPU_PD)
/* a->m send ipc_int  addr & bit  */
#define  PM_A2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)
#define  PM_A2M_IPC_BIT        (0x1<<IPC_MCU_INT_SRC_ACPU_PD)


/* === 对深睡状态机的唤醒时机做遍历测试 ===
** 睡眠时先设定唤醒timer，然后做loop
** loop值较小时 loop时间短，状态机能进深睡
** loop值较大时 loop时间长，状态机没有足够的时间进深睡
** 通过遍历 loop值，保证对状态机的唤醒时机做遍历测试
**
** 内部测试使用，loop功能默认关闭
** min,max值不同平台有差异，需连仿真器手动调试:使能、调整min max值
*/
struct pm_test_state_machine
{
    u32 enable;     /* 功能是否使用 */
    u32 loop_min;   /* loop值最小值 */
    u32 loop_max;   /* loop值最小值 */
    u32 loop_temp;  /* 当前loop值，初始化为loop_min */
    u32 first_no_sm;/* 记录第一次状态机不进深睡的loop值 */
    u32 tmp_no_sm;  /* loop值为max时，归零。之后记录下一次状态机不进深睡的loop值 */
};



#ifdef CONFIG_M3PM_TEST
extern u32 debug_can_sleep(void);
extern void pm_test_add_timer(void);
extern void pm_test_loop(void);
extern void pm_test_add_timer_and_loop(void);
extern void pm_test_no_sm_record(void);

#else
static inline u32 debug_can_sleep(void){return 1;}
static inline void pm_test_add_timer(void){return;}
static inline void pm_test_loop(void){return;}
static inline void pm_test_no_sm_record(void){return;}

#endif


#endif


        
