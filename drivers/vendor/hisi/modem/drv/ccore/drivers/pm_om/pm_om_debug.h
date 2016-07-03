
#ifndef __PM_OM_DEBUG_H__
#define __PM_OM_DEBUG_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*lint --e{528}*/
static inline int pm_om_debug_init(void){return 0;}
static inline u32 pm_om_log_time_rec(u32 time_log_start){return 0;}
static inline void pm_om_log_time_print(u32 log_sw){}

#ifdef __cplusplus
}
#endif

#endif  /* __PM_OM_DEBUG_H__ */
