#ifndef __RF_BSP_RF_H__
#define __RF_BSP_RF_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif            /* __cplusplus */

#include <product_config.h>
#include <mdrv_pm.h>
#include <mdrv_pmu.h>
#include <mdrv_anten.h>

#define RFFE_ERROR (-1)
#define RFFE_OK    (0)
#define rf_print_error(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PARF, "[DRVRF]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define rf_print_info(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_PARF, "[DRVRF]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define rf_print_dbg(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PARF, fmt,##__VA_ARGS__))

int bsp_pa_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_pa_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
PWC_COMM_STATUS_E bsp_pa_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_rfic_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_rfic_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
PWC_COMM_STATUS_E bsp_rfic_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
PWC_COMM_STATUS_E bsp_fem_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);
int bsp_fem_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);
int bsp_fem_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);
int bsp_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);
int bsp_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);
PWC_COMM_STATUS_E bsp_rfclk_is_enabled(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

int bsp_rffe_init(void);

#ifdef CONFIG_RFFE_ANTEN

int bsp_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3);


int bsp_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status);


int bsp_anten_set_outer_rfswitch(unsigned int status);


int bsp_anten_get_outer_rfswitch(unsigned int *status);


int bsp_anten_set_mode(GPIO_ANT_MODESET_E mode);


void bsp_anten_int_install(PWC_COMM_MODEM_E modem_id, void* routine,int para);

#else

static inline int bsp_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    return RFFE_OK;
}


static inline int bsp_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status)
{
    *status = 1;
	return RFFE_OK;
}


static inline int bsp_anten_set_outer_rfswitch(unsigned int status)
{
	return RFFE_OK;
}


static inline int bsp_anten_get_outer_rfswitch(unsigned int *status)
{
	return RFFE_OK;
}



static inline int bsp_anten_set_mode(GPIO_ANT_MODESET_E mode)
{
	return RFFE_OK;
}


static inline void bsp_anten_int_install(PWC_COMM_MODEM_E modem_id, void* routine,int para)
{
	return ;
}

#endif
#ifdef __cplusplus /* __cplusplus */
}
#endif             /* __cplusplus */

#endif             /*  __RF_POWER_H__ */


