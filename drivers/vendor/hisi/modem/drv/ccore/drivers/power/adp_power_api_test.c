#include <mdrv_pm.h>
#include <bsp_om.h>
#include <bsp_bbp.h>
#include <bsp_abb.h>
#include <bsp_pa_rf.h>
#include <bbp_balong.h>

#define  adp_power_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_ADP_DPM, "[adp_power]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

static void err_output_diff_module(PWC_COMM_MODULE_E module_id)
{
    switch(module_id)
    {
        case PWC_COMM_MODULE_PA:
        case PWC_COMM_MODULE_RF:
            adp_power_print_error("pa_rf test error,please contact pa_rf rensponsible\n");
            break;
        case PWC_COMM_MODULE_ABB:
            adp_power_print_error("abb test error,please contact abb rensponsible\n");
            break;
        case PWC_COMM_MODULE_BBE16:
            adp_power_print_error("dsp test error,please contact dsp rensponsible\n");
            break;
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            adp_power_print_error("bbp test error,please contact bbp rensponsible\n");
            break;
        default:
            break;
    }
}
/*****************************************************************************
* 函 数 名  : mdrv_pm_pwr_test
*
* 功能描述  : 通信模块控制电源上电接口测试
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
int mdrv_pm_pwrup_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    ret = mdrv_pm_pwrup(mode_id,module_id,modem_id,channel_id);
                    if(ret && (ret != BBP_ERR_PARAM_INVALID))
                        goto err;
                }
            }
        }
    }

    adp_power_print_error("test ok\n");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;
}
int mdrv_pm_pwrdown_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    ret = mdrv_pm_pwrdown(mode_id,module_id,modem_id,channel_id);
                    if(ret && (ret != BBP_ERR_PARAM_INVALID))
                        goto err;
                }
            }
        }
    }

    adp_power_print_error("test ok\n");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;
}
int mdrv_pm_get_pwrstatus_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    ret = mdrv_pm_get_pwrstatus(mode_id,module_id,modem_id,channel_id);
                    if((ret != PWRCTRL_COMM_ON) && (ret != PWRCTRL_COMM_OFF) && (ret != BBP_ERR_PARAM_INVALID))
                        goto err;
                }
            }
        }
    }

    adp_power_print_error("test ok\n");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;
}
int mdrv_pm_pwr_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                   mdrv_pm_pwrup(mode_id,module_id,modem_id,channel_id);
                }
            }
        }
    }

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    ret |= mdrv_pm_get_pwrstatus(mode_id,module_id,modem_id,channel_id);
                    if((ret != PWRCTRL_COMM_ON) && (module_id != PWC_COMM_MODULE_BBE16) &&(module_id != PWC_COMM_MODULE_ABB) && (ret != BBP_ERR_PARAM_INVALID))/*bbe是桩*/
                    {
                        adp_power_print_error("mode_id %d,module_id %d,modem_id %d,channel_id %d should be on!\n",mode_id,module_id,modem_id,channel_id);
                        goto err;
                    }
                }
            }
        }
    }
    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    mdrv_pm_pwrdown(mode_id,module_id,modem_id,channel_id);
                }
            }
        }
    }
    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    ret |= mdrv_pm_get_pwrstatus(mode_id,module_id,modem_id,channel_id);
                    if((ret != PWRCTRL_COMM_OFF) && (module_id != PWC_COMM_MODULE_BBE16) && (module_id != PWC_COMM_MODULE_ABB) && (ret != BBP_ERR_PARAM_INVALID))/*bbe是桩*/
                    {
                        adp_power_print_error("mode_id %d,module_id %d,modem_id %d,channel_id %d should be off!\n",mode_id,module_id,modem_id,channel_id);
                        goto err;
                    }
                }
            }
        }
    }
    adp_power_print_error("test ok\n");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;


}
int mdrv_pm_enable_pllclk_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_1;channel_id++)
                {
                    ret = mdrv_pm_enable_pllclk(mode_id,module_id,modem_id,channel_id);
                    if(ret && (ret != BBP_ERR_PARAM_INVALID))
                        goto err;
                }
            }
        }
    }

    adp_power_print_error("test ok\n");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;
}
int mdrv_pm_disable_pllclk_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_1;channel_id++)
                {
                    ret = mdrv_pm_disable_pllclk(mode_id,module_id,modem_id,channel_id);
                    if(ret && (ret != BBP_ERR_PARAM_INVALID))
                        goto err;
                }
            }
        }
    }

    adp_power_print_error("test ok\n");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;

}
int mdrv_pm_get_pllclk_status_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_1;channel_id++)
                {
                    ret = mdrv_pm_get_pllclk_status(mode_id,module_id,modem_id,channel_id);
                    if((ret != PWRCTRL_COMM_ON) && (ret != PWRCTRL_COMM_OFF) && (ret != BBP_ERR_PARAM_INVALID))
                        goto err;
                }
            }
        }
    }

    adp_power_print_error("test ok\n");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;

}
int mdrv_pm_pllclk_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_1;channel_id++)
                {
                    mdrv_pm_enable_pllclk(mode_id,module_id,modem_id,channel_id);
                }
            }
        }
    }
    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id <= PWC_COMM_MODULE_BBP_DRX;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_1;channel_id++)
                {
                    ret = mdrv_pm_get_pllclk_status(mode_id,module_id,modem_id,channel_id);
                    if((ret != PWRCTRL_COMM_ON) && ((module_id == PWC_COMM_MODULE_BBP_DRX)||(module_id == PWC_COMM_MODULE_ABB)) && (ret != BBP_ERR_PARAM_INVALID))
                    {
                        adp_power_print_error("mode_id %d,module_id %d,modem_id %d,channel_id %d should be on!\n",mode_id,module_id,modem_id,channel_id);
                        goto err;
                    }
                }
            }
        }
    }
    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_1;channel_id++)
                {
                    mdrv_pm_disable_pllclk(mode_id,module_id,modem_id,channel_id);
                }
            }
        }
    }
    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id <= PWC_COMM_MODULE_BBP_DRX;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_1;channel_id++)
                {
                    ret = mdrv_pm_get_pllclk_status(mode_id,module_id,modem_id,channel_id);
                    if((ret != PWRCTRL_COMM_OFF) && ((module_id == PWC_COMM_MODULE_BBP_DRX)||(module_id == PWC_COMM_MODULE_ABB)) && (ret != BBP_ERR_PARAM_INVALID))
                    {
                        adp_power_print_error("mode_id %d,module_id %d,modem_id %d,channel_id %d should be off!\n",mode_id,module_id,modem_id,channel_id);
                        goto err;
                    }
                }
            }
        }
    }
    adp_power_print_error("test ok\n");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;
}

#if 0
int mdrv_pm_enable_bbpclk_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    ret = mdrv_pm_enable_bbpclk(mode_id,module_id,modem_id,channel_id);
                    if((ret != PWRCTRL_COMM_ON) && (ret != PWRCTRL_COMM_OFF) && (ret != BBP_ERR_PARAM_INVALID))
                        goto err;
                }
            }
        }
    }

    adp_power_print_error("test ok");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;

}
int mdrv_pm_disable_bbpclk_test(void)
{
    int ret = 0;
    PWC_COMM_MODE_E mode_id;
    PWC_COMM_MODULE_E module_id;
    PWC_COMM_MODEM_E modem_id;
    PWC_COMM_CHANNEL_E channel_id;

    for(mode_id = PWC_COMM_MODE_GSM;mode_id < PWC_COMM_MODE_BUTT;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id < PWC_COMM_MODULE_BUTT;module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id < PWC_COMM_MODEM_1;modem_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id < PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    ret = mdrv_pm_disable_bbpclk(mode_id,module_id,modem_id,channel_id);
                    if((ret != PWRCTRL_COMM_ON) && (ret != PWRCTRL_COMM_OFF))
                        goto err;
                }
            }
        }
    }

    adp_power_print_error("test ok");
    goto out;

err:
    err_output_diff_module(module_id);
out:
    return ret;

}

int mdrv_pm_pwr_func_test (void)
{
    int ret = 0;

    ret = bsp_pa_power_test();

    ret |= bsp_rfic_power_test();

    ret |= bsp_abb_power_test();

    ret |= bsp_bbp_power_test();

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
int mdrv_pm_pll_test (PWC_COMM_MODULE_E enModuleId)
{
    int ret = 0;

    ret = abb_ch_pll_test();

    ret |= bsp_bbp_dfs_test();

    return ret;
}
/***************************************************************************
 函 数 名  : mdrv_pm_bbpclk_test()
 功能描述  : bbp相关时钟测试
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BBP_OK         成功
             其他           失败
**************************************************************************/
int mdrv_pm_bbpclk_test (void)
{
	return bsp_bbp_clk_test();
}
#endif
