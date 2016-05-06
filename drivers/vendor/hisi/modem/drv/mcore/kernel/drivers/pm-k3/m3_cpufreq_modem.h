#ifndef _M3_CPUFREQ_MODEM_H_
#define _M3_CPUFREQ_MODEM_H_

#include <bsp_sram.h>
#include <log.h>

#define CPUFREQ_NUM 2
#define CPUFREQ_INVALID_PROFILE   0xFF
#define CPUFREQ_MAX_PROFILE    13
#define CPUFREQ_MIN_PROFILE    0
#define CPUFREQ_MAX_PLL        1

#define M3_CUR_CPUFREQ_PROFILE   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CUR_CPUFREQ_PROFILE)
#define M3_MAX_CPUFREQ_PROFILE   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MAX_CPUFREQ_PROFILE)
#define M3_MIN_CPUFREQ_PROFILE   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MIN_CPUFREQ_PROFILE)

typedef struct {
	u32	pll;
	u32 clkdiv;
}T_CPUFREQ_PROFILE;

typedef struct {
	u32	a9pllcfg0;
	u32 a9pllcfg1;
}T_CPUFREQ_PLL_CONFIG;

typedef enum tagCpufreqCoreType
{
	CPUFREAQ_ACORE = 0,
	CPUFREAQ_CCORE = 1,
	CPUFREAQ_MCORE = 2,
}T_CPUFREQ_CORE_TYPE;

typedef enum tagCpufreqAction
{
	CPUFREAQ_UP = 0,
	CPUFREAQ_UP_TARGET = 1,
	CPUFREAQ_DOWN = 2,
	CPUFREAQ_DOWN_TARGET = 3
}T_CPUFREQ_ACTION;


typedef struct {
	u32	msgtype;
	u32 coretype;
	u32 action;
	u32 profile;
}T_CPUFREQ_MAIL;

typedef struct {
	u32 minprof;
	u32 maxprof;
	u32 curprof;
    u32 ccorelockflag;
}T_CPUFREQ_ST;


#define MODEM_CPUFREQ_PRINT(fmt,...) (printk("[mdm_cpufr]: "fmt, ##__VA_ARGS__))

extern void pm_dfs_bak(u32 profile);
extern void dfs_config_reg(u32 cur, u32 new);
extern void cpufreq_init(void);
extern s32 cpufreq_icc_read_cb(u32 id , u32 len, void* context);
extern u32 cpufreq_get_cur_profile(void);
extern void thread_cpufreq (void const *arg);
extern void cpufreq_suspend(void);
extern void cpufreq_resume(void);
extern void cpufreq_print_debug(void);

#endif /* end of _M3_CPUFREQ_MODEM_H_ */

