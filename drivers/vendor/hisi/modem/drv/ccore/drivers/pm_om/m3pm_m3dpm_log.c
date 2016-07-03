

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



