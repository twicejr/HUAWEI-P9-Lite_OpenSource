/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  cpufreq_regulator.h
*
*   作    者 :  yangqiang 221789
*
*   描    述 :  cpufreq & regulator 解析头文件
*
*   修改记录 : 2014年12月27日  v1.00  y00221789  创建
*************************************************************************/

#ifndef  __DPM_M3PM_H__
#define  __DPM_M3PM_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>


struct dpm_fail_pm_om_log {
	unsigned int ops_addr;
	unsigned int before_stamp;
	unsigned int after_stamp;
	unsigned int fail_cnt;
};

enum m3_dpm_debug_e{
	DPM_IPF,
	DPM_SOCP,
	DPM_TEM,
	DPM_PMU,
	DPM_PASTAR,
	DPM_BUTTON,
	};
enum m3_mdm_dpm_log_mode
{
    m3_mdm_dpm_log_begin,
    m3_mdm_dpm_log_temp,
    m3_mdm_dpm_log_ipf,
    m3_mdm_dpm_log_butt
};

enum m3_mdm_pm_log_mode
{
    m3_mdm_pm_log_a9,
    m3_mdm_pm_log_a9_sr,
    m3_mdm_dpm_log_fail
};


#define M3PM_LOG_MODEM_DOWN_OFFSET      0
#define M3PM_LOG_MODEM_DOWN_SIZE        0x8

#define M3PM_LOG_MODEM_UP_OFFSET        (M3PM_LOG_MODEM_DOWN_OFFSET+M3PM_LOG_MODEM_DOWN_SIZE)
#define M3PM_LOG_MODEM_UP_SIZE          (0xC)

#define M3PM_LOG_MODEM_SUSPEND_OFFSET   (M3PM_LOG_MODEM_UP_OFFSET+M3PM_LOG_MODEM_UP_SIZE)
#define M3PM_LOG_MODEM_SUSPEND_SIZE     (0x10)

#define M3PM_LOG_MODEM_RESUME_OFFSET    (M3PM_LOG_MODEM_SUSPEND_OFFSET+M3PM_LOG_MODEM_SUSPEND_SIZE)
#define M3PM_LOG_MODEM_RESUME_SIZE      (0x8)

#define M3PM_LOG_MODEM_RESUME_OK_OFFSET (M3PM_LOG_MODEM_RESUME_OFFSET+M3PM_LOG_MODEM_RESUME_SIZE)
#define M3PM_LOG_MODEM_RESUME_OK_SIZE   (0xC)

#define M3PM_LOG_MODEM_DPM_OFFSET       (M3PM_LOG_MODEM_RESUME_OK_OFFSET+M3PM_LOG_MODEM_RESUME_OK_SIZE)
#define M3PM_LOG_MODEM_DPM_SIZE         (0x4*m3_mdm_dpm_log_butt) 

#define M3PM_LOG_MDM_A9_SIZE            (M3PM_LOG_MODEM_DOWN_SIZE+M3PM_LOG_MODEM_UP_SIZE)
#define M3PM_LOG_MDM_SR_SIZE            (M3PM_LOG_MODEM_SUSPEND_SIZE+M3PM_LOG_MODEM_RESUME_SIZE+M3PM_LOG_MODEM_RESUME_OK_SIZE)
#define M3PM_LOG_MDM_A9_SR_SIZE         (M3PM_LOG_MDM_A9_SIZE+M3PM_LOG_MDM_SR_SIZE)


enum pm_log_type_m3pm
{
    ACORE_WAKE = 0x5A5A0000,
    CCORE_WAKE,
    HIFI_WAKE,
    MCORE_WAKE,
};
typedef struct
{
	u32 SleepTimes;
	u32 WakeIrq;
}T_PM_CORE_WAKE_ST;



int dpm_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);
int m3pm_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __DPM_M3PM_H__ */

