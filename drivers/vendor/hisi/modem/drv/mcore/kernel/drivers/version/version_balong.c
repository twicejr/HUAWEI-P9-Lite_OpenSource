
#include "bsp_version.h"

/*****************************************************************************
* 函 数 名  	: bsp_get_version_info
*
* 功能描述  : 为其他模块提供各种版本号信息
*
* 参数说明  : 无
*
*返回值 : version的共享内存数据结构体的地址
*****************************************************************************/
const BSP_VERSION_INFO_S* bsp_get_version_info(void)
{
	return (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
}

