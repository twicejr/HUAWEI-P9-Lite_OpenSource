#ifndef __BSP_DPM_H__
#define __BSP_DPM_H__

#include <osl_types.h>
#include <osl_list.h>
#include <bsp_om.h>
#include <product_config.h>
#define  dpm_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DPM, "[DPM]: <%s> "fmt" ", __FUNCTION__, ##__VA_ARGS__))
/*extern void printksync(const char *fmt, ...);
#define  dpm_print_error(fmt, ...)  printksync("[DPM]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__);
*/

enum DPM_DEBUG_CNT
{
    DPM_FAIL_CNT_S_PREPARE   = 0,
    DPM_FAIL_CNT_S_EARLY     = 1,
    DPM_FAIL_CNT_S_SUSPEND   = 2,
    DPM_FAIL_CNT_S_LATE      = 3,
    DPM_CNT_S_TOTAL     = 4,
    DPM_CNT_R_TOTAL     = 5,
    DPM_CALLBACK_NUM    = 8,
};
/*
suspend级别先后顺序:
	prepare 、suspend_early 、suspend、suspend_late
resume级别先后顺序:
	resume_early 、resume、resume_late 、complete
*/

struct dpm_device
{
	struct list_head   entry;
    char               *device_name;                    /*模块名字*/
	void 			   *platform_data;                  /*回调函数使用的数据可以通过本指针传递,参考linux中struct device中的platform_data*/
	s32    (*prepare)(struct dpm_device *dev);          
	s32    (*suspend_early)( struct dpm_device *dev);         
	s32    (*suspend)( struct dpm_device *dev);         
	s32    (*suspend_late)( struct dpm_device *dev);    
	s32    (*resume_early)( struct dpm_device *dev);   
	s32    (*resume)( struct dpm_device *dev);      
	s32    (*resume_late)( struct dpm_device *dev);    
	s32    (*complete)(struct dpm_device *dev);         
	u32    debug_count[DPM_CALLBACK_NUM];               /*记录dpm各个回调函数失败次数*/
	u32    debug_time[DPM_CALLBACK_NUM][2]; /*打点记录dpm各个回调函数执行前后时间*/
	u32    max_duration[DPM_CALLBACK_NUM];
};

#ifdef CONFIG_CCORE_PM

s32 bsp_device_pm_add(struct dpm_device *dev);


s32 bsp_device_pm_remove(struct dpm_device *dev);

s32 bsp_dpm_suspend(void);


s32 bsp_dpm_suspend_single(char *dev_name);


void bsp_dpm_resume(void);


s32 bsp_dpm_resume_single(char *dev_name);


void bsp_dpm_init(void);
#else
static inline s32 bsp_device_pm_add(struct dpm_device *dev)  {return 0;}
static inline s32 bsp_device_pm_remove(struct dpm_device *dev)  {return 0;}
static inline s32 bsp_dpm_suspend(void)  {return 0;}
static inline s32 bsp_dpm_suspend_single(char *dev_name) {return 0;}
static inline void bsp_dpm_resume(void) {}
static inline s32 bsp_dpm_resume_single(char *dev_name) {return 0;}
static inline void bsp_dpm_init(void) {}
#endif/*CONFIG_CCORE_PM*/

#endif


