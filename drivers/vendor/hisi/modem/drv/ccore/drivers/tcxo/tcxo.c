
#include "tcxo_balong.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#ifndef CONFIG_TCXO_BALONG
void bsp_pmu_tcxo1_en_enable(PMU_TCXO_EN bit_value)
{
	return;
}
void bsp_pmu_tcxo1_en_disable(PMU_TCXO_EN bit_value)
{
	return;
}
int mdrv_pm_enable_tcxo(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType)
{
    return 0;
}
int mdrv_pm_disable_tcxo(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType)
{
    return 0;
}

int mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_E enModemId)
{
    return PWRCTRL_COMM_ON;
}
int mdrv_pm_start_tcxo_timer(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_TCXO_FUNCPTR routine,int arg, unsigned int timerValue)
{
    return 0;
}
int tcxo_init_configure()
{
    return 0;
}

int mdrv_pm_get_tcxo_rfclk_status(PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
int mdrv_pm_enable_tcxo_rfclk(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
int mdrv_pm_disable_tcxo_rfclk(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}

void mdrv_misc_tcxo_fre_compensate(unsigned int value)
{
    return ;
}

void tcxo_suspend(void){return;}
void tcxo_resume(void){return;}

#endif

#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif

