#include <product_config.h>
#include <mdrv_anten.h>
#include <mdrv_gpio.h>
#include <drv_nv_def.h>
#include <hi_anten.h>
#include <gpio_balong.h>
#include <bsp_om.h>
#include <bsp_nvim.h>
#include <bsp_version.h>
#include <bsp_rf_balong.h>


/*****************************************************************************
 函 数 名  : drv_anten_lock_status_get
 功能描述  : 获取有线与无线的连接状态
 输入参数  : none
 输出参数  : 0 - 无线连接
             1 - 有线连接
 返 回 值  : 0 - 成功
             其它为失败

*****************************************************************************/
int mdrv_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status)
{
    return bsp_anten_get_lockstate(modem_id,status);
}


/*****************************************************************************
 函 数 名  : drv_anten_int_install
 功能描述  : 中断注册函数，用来获得当前的天线状态
 输入参数  : routine   - 中断处理函数
             para      - 保留字段
 输出参数  : none
 返 回 值  : void

*****************************************************************************/
void mdrv_anten_register_intr_cb(PWC_COMM_MODEM_E modem_id, void* routine, int para)
{
    bsp_anten_int_install(modem_id, routine, para);
}

int mdrv_anten_set_outer_rfswitch(unsigned int status)
{   
    return bsp_anten_set_outer_rfswitch(status);
}

int mdrv_anten_get_outer_rfswitch(unsigned int *status)
{
    return bsp_anten_get_outer_rfswitch(status);
}

int mdrv_anten_set_mode(GPIO_ANT_MODESET_E mode)
{
    return bsp_anten_set_mode(mode);
}


int mdrv_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    return bsp_fem_ioctrl(ctrl_type,para1,para2,para3);
}

