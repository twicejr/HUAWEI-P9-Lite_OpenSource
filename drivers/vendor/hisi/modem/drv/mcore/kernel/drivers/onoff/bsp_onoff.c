#include <hi_syssc_interface.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 函 数 名  : power_off_reboot_operation
 功能描述  : pmu rst 系统重启
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
*****************************************************************************/
static void power_off_reboot_operation( void )
{
/* p531 FPGA复位需要同时复位F1/BBP/RF */
#ifdef BSP_CONFIG_P531_FPGA
extern void p531_fpga_reset(void);
	p531_fpga_reset();
#endif

	hi_syssc_pmu_reboot();

    /* coverity[no_escape] */
    while(1);
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
    power_off_reboot_operation();
}

#ifdef __cplusplus
}
#endif