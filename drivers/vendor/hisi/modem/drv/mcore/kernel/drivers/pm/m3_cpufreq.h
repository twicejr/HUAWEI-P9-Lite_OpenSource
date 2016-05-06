#ifndef __M3_CPUFREQ_H__
#define __M3_CPUFREQ_H__
#include <product_config.h>
#include "osl_types.h"
#include <bsp_om.h>

#define CPUFREQ_NUM 2
#define CPUFREQ_INVALID_PROFILE   0xFF

#define M3_CUR_CPUFREQ_PROFILE   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CUR_CPUFREQ_PROFILE)
#define M3_MAX_CPUFREQ_PROFILE   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MAX_CPUFREQ_PROFILE)
#define M3_MIN_CPUFREQ_PROFILE   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MIN_CPUFREQ_PROFILE)
#define M3_CPUFREQ_DOWN_FLAG(a)   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CPUFREQ_DOWN_FLAG[a])
#define M3_CPUFREQ_DOWN_PROFILE(a)   (((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS))->SRAM_CPUFREQ_DOWN_PROFILE[a])

#define CPUFREQ_CTI_BASE        (0x90403000)
#define CPUFREQ_CTI_BASE_MDM    (0x904B8000)
#define CPUFREQ_DBG_BASE_MDM    (0x904B0000)
#define CPUFREQ_CTI_BASE_APP    (0x904F8000)
#define CPUFREQ_DBG_BASE_APP    (0x904F0000)

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
	u32 flag;     /* 1表示有未处理的调频请求，0表示没有 */
	u32 profile;  /* 未处理的目标频率 */
    u32 sleepflag;/* 1表示睡眠，0表示没有睡眠*/
}T_CPUFREQ_TODO;

typedef struct {
	u32 minprof;
	u32 maxprof;
	u32 curprof;
    u32 ccorelockflag;
	u32 debuglockflag;
	u32 coreminlimit[CPUFREQ_NUM];
	T_CPUFREQ_TODO todo[CPUFREQ_NUM];
}T_CPUFREQ_ST;

struct cpufreq_pm_om_log {
	u32 cur_profile;
	u32 cur_timeslice;
	u32 target_profile;
	u32 dst_timeslice;
	u32 max_limit;
	u32 min_limit;
};
struct cpufreq_pm_om_dump {
	u32 profile;
	u64 timeslice;
};
#define M3CPUFREQ_PRINT(fmt,...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_M3_CPUFREQ, "[cpufreq]: "fmt, ##__VA_ARGS__))

extern void cpufreq_init(void);
extern void cpufreq_print_debug(int flag);
extern void cpufreq_ccore_unlock(void);
extern void cpufreq_set_sleepflag(u32 core_type, u32 flag);
extern inline void cpufreq_dump_pro_timeslice(u32 cur, u32 new);
extern void cpufreq_cti_unlock(u32 base_addr);
extern void cpufreq_cti_lock(u32 base_addr);
extern void cpufreq_m3_cti_init(void);
extern void cpufreq_ccore_cti_init(void);
extern void cpufreq_acore_cti_init(void);
extern void cpufreq_cti_init(void);
extern void pm_dfs_bak(void);

#ifdef CONFIG_AMON_FOR_BUS_LOCK
extern void amon_init_dfs(void);
#else
static inline void amon_init_dfs(void){}
#endif

#endif
