#ifndef __MDRV_CCORE_MISC_H__
#define __MDRV_CCORE_MISC_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_misc_comm.h"

/*****************************************************************************
*  函 数 名  : mdrv_misc_tcxo_fre_compensate
*  功能描述  : 为tcxo获取频率补偿
*  输入参数  : value:需要调节的值
*              
*  输出参数  : 无
*  返 回 值  : null
*             
******************************************************************************/      
void mdrv_misc_tcxo_fre_compensate(unsigned int value);

#ifdef __cplusplus
}
#endif
#endif

