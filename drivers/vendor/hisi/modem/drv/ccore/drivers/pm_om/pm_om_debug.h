/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  pm_om_debug.h
*
*   作    者 :  y00184236
*
*   描    述 :  debug相关头文件
*
*   修改记录 :  2014年11月17日  v1.00  y00184236  创建
*************************************************************************/
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
