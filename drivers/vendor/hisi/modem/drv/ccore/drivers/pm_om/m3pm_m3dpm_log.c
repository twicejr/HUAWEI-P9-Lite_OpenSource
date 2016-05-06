/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  m3pm_m3dpm_log.c
*
*   作    者 :  s00219058
*
*   描    述 :  本文件任务：将m3 打点信息以 pm log形式输出
*
*   修改记录 :  2015年1月17日  v1.00  s00219058  创建
**************************************************************************/

#include <bsp_pm_om.h>
#include <bsp_m3pm_log.h>


u32 m3_mdm_last_sr_stamp = 0; 
u32 m3_mdm_last_dpm_stamp = 0; 
void m3_mdm_sr_update(void)
{   
    m3_mdm_last_sr_stamp =  *(u32*)(SHM_MEM_M3PM_LOG_ADDR+M3PM_LOG_MODEM_SUSPEND_OFFSET);
    m3_mdm_last_dpm_stamp =  *(u32*)(SHM_MEM_M3PM_LOG_ADDR+M3PM_LOG_MODEM_DPM_OFFSET);
}
void m3_mdm_pm_dpm_log(void)
{   
    if( m3_mdm_last_sr_stamp == *(u32*)(SHM_MEM_M3PM_LOG_ADDR+M3PM_LOG_MODEM_SUSPEND_OFFSET) )
    {
        bsp_pm_log_type(PM_OM_PMM, m3_mdm_pm_log_a9, M3PM_LOG_MDM_A9_SIZE, \
        (void*)(SHM_MEM_M3PM_LOG_ADDR+M3PM_LOG_MODEM_DOWN_OFFSET));
    }
    else
    {
        bsp_pm_log_type(PM_OM_PMM, m3_mdm_pm_log_a9_sr, M3PM_LOG_MDM_A9_SR_SIZE, \
        (void*)(SHM_MEM_M3PM_LOG_ADDR+M3PM_LOG_MODEM_DOWN_OFFSET));
    }

    if( m3_mdm_last_dpm_stamp == *(u32*)(SHM_MEM_M3PM_LOG_ADDR+M3PM_LOG_MODEM_DPM_OFFSET) )
    {
        return;
    }
    else
    {
        bsp_pm_log_type(PM_OM_PMM, m3_mdm_dpm_log_fail, M3PM_LOG_MODEM_DPM_SIZE, \
            (void*)(SHM_MEM_M3PM_LOG_ADDR+M3PM_LOG_MODEM_DPM_OFFSET));
    }
}



