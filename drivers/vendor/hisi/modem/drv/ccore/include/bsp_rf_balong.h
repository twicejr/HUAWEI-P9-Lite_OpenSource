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
/*****************************************************************************
* 函 数    : bsp_fem_ioctrl
* 功 能    : 射频管脚配置
* 输 入    : @ctrl_type  接口类型，0为gpio、mipi参照NV配置，1为直接传参配置

               ctrl_type = CFG_RFFE_GROUP_GPIO_MIPI
              @para1 is nvindex    nv  项索引，取值为0-15，此参数参见nv手册18002
              @para2 is mux         管脚复用配置，0为gpio功能，1为线控功能
              @para3 is reserved   保留

                       ctrl_type = CFG_RFFFE_SET_PIN_NO_NV
              @para1 is gpio num    gpio编号
              @para2 is mux         管脚复用配置，0为gpio功能，1为线控功能
              @para3 is value         若para2为gpio功能，则value为输出电平

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 此接口在手机平台使用，MBB不设及，打桩即可
*****************************************************************************/
int bsp_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3);

/*****************************************************************************
* 函 数    : bsp_anten_get_lockstate
* 功 能    : 获取天线有线无线连接状态接口
* 输 入    : @modem_id,modem编号

* 输 出    : @status    有线为1,无线为0

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
int bsp_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status);

/*****************************************************************************
* 函 数    : bsp_anten_set_outer_rfswitch
* 功 能    : NAS专用接口
                    外接Modem的天线选择控制接口
                    当前单板不支持此功能（对应NV项为全0），或者其他异常 返回-1
* 输 入    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 输 出    : 无

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
*****************************************************************************/
int bsp_anten_set_outer_rfswitch(unsigned int status);

/*****************************************************************************
* 函 数    : bsp_anten_get_outer_rfswitch
* 功 能    : NAS专用接口
                    外接Modem的天线选择查询接口
                    当前单板不支持此功能（对应NV项为全0），或者其他异常 返回-1
* 输 入    : 无

* 输 出    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
*****************************************************************************/
int bsp_anten_get_outer_rfswitch(unsigned int *status);

/*****************************************************************************
* 函 数    : bsp_anten_set_mode
* 功 能    : DSP专用接口,GPIO共天线设置
* 输 入    : @mode:天线模式
*                   ANT_LTE     =  0, lte分集天线
*                   ANT_GSM     =  1, GSM副卡天线

* 输 出    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 返 回    : 0:正确，-1:错误
* 作 者    : z00228752
*****************************************************************************/
int bsp_anten_set_mode(GPIO_ANT_MODESET_E mode);

/*****************************************************************************
* 函 数    : bsp_anten_int_install
* 功 能    : 注册oam的天线插拔回调函数
* 输 入    : @modem id
                     @routine 回调函数
                     @ para 参数

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
void bsp_anten_int_install(PWC_COMM_MODEM_E modem_id, void* routine,int para);

#else
/*****************************************************************************
* 函 数    : bsp_fem_ioctrl
* 功 能    : 射频管脚配置
* 输 入    : @ctrl_type  接口类型，0为gpio、mipi参照NV配置，1为直接传参配置

               ctrl_type = CFG_RFFE_GROUP_GPIO_MIPI
              @para1 is nvindex    nv  项索引，取值为0-15，此参数参见nv手册18002
              @para2 is mux         管脚复用配置，0为gpio功能，1为线控功能
              @para3 is reserved   保留

                       ctrl_type = CFG_RFFFE_SET_PIN_NO_NV
              @para1 is gpio num    gpio编号
              @para2 is mux         管脚复用配置，0为gpio功能，1为线控功能
              @para3 is value         若para2为gpio功能，则value为输出电平

* 输 出    : 无
* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 此接口在手机平台使用，MBB不设及，打桩即可
*****************************************************************************/
static inline int bsp_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    return RFFE_OK;
}

/*****************************************************************************
* 函 数    : bsp_anten_get_lockstate
* 功 能    : 获取天线有线无线连接状态接口
* 输 入    : @modem_id,modem编号

* 输 出    : @status    有线为1,无线为0

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
* 说 明    : 内部接口
*****************************************************************************/
static inline int bsp_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status)
{
    *status = 1;
	return RFFE_OK;
}

/*****************************************************************************
* 函 数    : bsp_anten_set_outer_rfswitch
* 功 能    : NAS专用接口
                    外接Modem的天线选择控制接口
                    当前单板不支持此功能（对应NV项为全0），或者其他异常 返回-1
* 输 入    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 输 出    : 无

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
*****************************************************************************/
static inline int bsp_anten_set_outer_rfswitch(unsigned int status)
{
	return RFFE_OK;
}

/*****************************************************************************
* 函 数    : bsp_anten_get_outer_rfswitch
* 功 能    : NAS专用接口
                    外接Modem的天线选择查询接口
                    当前单板不支持此功能（对应NV项为全0），或者其他异常 返回-1
* 输 入    : 无

* 输 出    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 返 回    : 0为成功，-1为失败
* 作 者    : z00228752
*****************************************************************************/
static inline int bsp_anten_get_outer_rfswitch(unsigned int *status)
{
	return RFFE_OK;
}


/*****************************************************************************
* 函 数    : bsp_anten_set_mode
* 功 能    : DSP专用接口,GPIO共天线设置
* 输 入    : @mode:天线模式
*                   ANT_LTE     =  0, lte分集天线
*                   ANT_GSM     =  1, GSM副卡天线

* 输 出    : @status 1:外接Modem天线功能，0：非外接Modem天线功能

* 返 回    : 0:正确，-1:错误
* 作 者    : z00228752
*****************************************************************************/
static inline int bsp_anten_set_mode(GPIO_ANT_MODESET_E mode)
{
	return RFFE_OK;
}

/*****************************************************************************
* 函 数    : bsp_anten_int_install
* 功 能    : 注册oam的天线插拔回调函数
* 输 入    : @modem id
                     @routine 回调函数
                     @ para 参数

* 输 出    : 无
* 返 回    : 非0为成功，-1为失败
* 作 者    :z00228752
* 说 明    :内部接口
*****************************************************************************/
static inline void bsp_anten_int_install(PWC_COMM_MODEM_E modem_id, void* routine,int para)
{
	return ;
}

#endif
#ifdef __cplusplus /* __cplusplus */
}
#endif             /* __cplusplus */

#endif             /*  __RF_POWER_H__ */


