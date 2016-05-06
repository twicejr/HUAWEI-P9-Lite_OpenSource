#include <mdrv_pm.h>
#include <bsp_bbp.h>
#include <bsp_abb.h>
#include <bsp_rf_balong.h>
#include <bsp_version.h>
#include <bsp_dsp.h>
#include <bsp_dspload.h>

/*****************************************************************************
* 函 数 名  : mdrv_pm_pwrup
*
* 功能描述  : 通信模块控制电源上电接口
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : 0，执行成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_pwrup (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                   PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            ret = bsp_pa_power_up(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfic_power_up(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_power_up(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_bbe_power_up();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_bbe_power_up_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            ret = bsp_bbp_power_up(enModeId, enModuleId, enModemId);
            break;
		case PWC_COMM_MODULE_FEM:
			ret = bsp_fem_power_up(enModeId, enModemId, enChannel);
			break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* 函 数 名  : mdrv_pm_pwrdown
*
* 功能描述  : 通信模块控制电源下电接口
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : 0，执行成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_pwrdown (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                     PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            ret = bsp_pa_power_down(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfic_power_down(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_power_down(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_bbe_power_down();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_bbe_power_down_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            ret = bsp_bbp_power_down(enModeId, enModuleId, enModemId);
            break;
		case PWC_COMM_MODULE_FEM:
			ret = bsp_fem_power_down(enModeId, enModemId, enChannel);
			break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* 函 数 名  : mdrv_pm_get_pwrstatus
*
* 功能描述  : 通信模块控制电源查询接口
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : PWRCTRL_COMM_ON 外设模块已经上电
*             PWRCTRL_COMM_OFF 外设模块已经下电
*             其他，错误
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_get_pwrstatus (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                           PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = PWRCTRL_COMM_ON;

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            ret = bsp_pa_power_status(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfic_power_status(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_power_status(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_bbe_power_status();
            break;
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            ret = bsp_bbp_power_status(enModeId, enModuleId, enModemId);
            break;
		case PWC_COMM_MODULE_FEM:
			ret = bsp_fem_power_status(enModeId, enModemId, enChannel);
			break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* 函 数 名  : mdrv_pm_enable_pllclk
*
* 功能描述  : DRX PLL使能时钟
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  :  0，执行成功；-1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_enable_pllclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                           PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            //ret =
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfclk_enable(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_pll_enable(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_dsp_dfs_pll_enable();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_dsp_dfs_pll_enable_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            //ret = bsp_bbp_dfs_enable(enModeId, enModuleId, enModemId);
            break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* 函 数 名  : mdrv_pm_disable_pllclk
*
* 功能描述  : DRX PLL关闭时钟
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : 0，执行成功；-1，失败
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_disable_pllclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                            PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            //ret =
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfclk_disable(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_pll_disable(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_dsp_dfs_pll_disable();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_dsp_dfs_pll_disable_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            //ret = bsp_bbp_dfs_disable(enModeId, enModuleId, enModemId);
            break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* 函 数 名  : mdrv_pm_get_pllclk_status
*
* 功能描述  : DRX PLL查询时钟
*
* 输入参数  : PWC_COMM_MODE_E enModeId      协议模式
*             PWC_COMM_MODULE_E enModuleId  操作模块
*             PWC_COMM_MODEM_E enModemId    卡号
*             PWC_COMM_CHANNEL_E enChannel  channel编号
* 输出参数  :
*
* 返 回 值  : PWRCTRL_COMM_ON         时钟打开
*             PWRCTRL_COMM_OFF        时钟关闭
*             -1                      查询失败
*
*
* 其它说明  :
*
*****************************************************************************/
int mdrv_pm_get_pllclk_status (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                               PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = PWRCTRL_COMM_ON;

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            //ret =
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfclk_is_enabled(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_pll_status(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_dsp_dfs_pll_status();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_dsp_dfs_pll_status_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            //ret = bsp_bbp_dfs_status(enModeId, enModuleId, enModemId);
            break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}


