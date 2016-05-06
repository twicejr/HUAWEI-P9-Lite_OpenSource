#include <osl_common.h>
#define DPM_OK 0
#define DPM_ERROR (-1)
enum dpm_status{
	  PMSG_SUSPEND,
	  PMSG_RESUME,
  };

enum dpm_debug_e{
	DPM_IPF,
	DPM_SOCP,
	DPM_TEM,
	DPM_PMU,
	DPM_PASTAR,
	DPM_BUTTON,
	};
/*****************************************************************************
* 函 数 名     : dpm_suspend
*
* 功能描述  : 回调m3上外设的suspend回调函数
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值     : DPM_OK & DPM_ERROR
*
* 修改记录  : 2013年6月14日   lixiaojie

*****************************************************************************/
 s32 dpm_suspend(void);
/*****************************************************************************
* 函 数 名     : dpm_resume
*
* 功能描述  : 回调m3上外设的resume回调函数
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值     : DPM_OK & DPM_ERROR
*
* 修改记录  : 2013年6月14日   lixiaojie

*****************************************************************************/
 s32 dpm_resume(void);

 s32 dpm_suspend_buck3off(void);
 s32 dpm_resume_buck3off(void);

