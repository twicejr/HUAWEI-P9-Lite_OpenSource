#include "osl_types.h"
#include "osl_wait.h"
//#include "drv_onoff.h"
#include "power_com.h"
#include "bsp_sram.h"
#include "bsp_icc.h"
#include "bsp_onoff.h"
#include <mdrv_sysboot.h>

#include <product_config.h>

#ifndef CONFIG_ONOFF

static stPowCtrl g_pwrctrl;


/*****************************************************************************
 函 数 名  : power_on_c_status_set
 功能描述  : 清空C核状态
 输入参数  : power_on_c_status_set
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
void power_on_c_status_set(c_power_st_e val)
{
    power_info_s *pw_st = (power_info_s *)(SRAM_REBOOT_ADDR);

    pw_st->c_power_state = (u32)val;
}

/*****************************************************************************
 函 数 名  : bsp_start_mode_get
 功能描述  : 用于C核获取开机模式,通过核间调用, 启动的时候不允许获取
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
DRV_START_MODE_E mdrv_sysboot_get_bootmode( void )
{
    return 1;
}

/*****************************************************************************
 函 数 名  : drv_shut_down
 功能描述  : 用于C核进行关机处理,通过核间调用
 输入参数  : 关机原因
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
void mdrv_sysboot_shutdown( DRV_SHUTDOWN_REASON_E enReason )
{
    /* coverity[no_escape] */
    while (1);

    return ;
}

/*****************************************************************************
 函 数 名  : drv_shut_down
 功能描述  : 用于C核进行关机处理,通过核间调用
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
void mdrv_sysboot_poweroff( void )
{
    /* coverity[no_escape] */
    while (1);

    return ;
}

/******************************************************************************
*  Function:  bsp_drv_power_reboot
*  Description: same as drv_power_off, the public API
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : 应用调用重启时调用，at+cfun=6
********************************************************************************/
void bsp_drv_power_reboot( void )
{
    /* coverity[no_escape] */
    while (1);

    return ;
}

/*****************************************************************************
 函 数 名  : bsp_on_off_init
 功能描述  : C核开关机初始化
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
int bsp_on_off_init( void )
{
    g_pwrctrl.is_init = 1;

    return BSP_OK;
}

/******************************************************************************
*  Function:  bsp_drv_power_reboot_direct
*  Description:
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : 直接重启
********************************************************************************/
void bsp_drv_power_reboot_direct( void )
{
    return;
}

#endif

/* 根据GPIO 拨码开关判断是否启动协议栈代码 */
unsigned int mdrv_sysboot_check_startps(void)
{
	return ~DRV_NOT_START_UMTS;
}



