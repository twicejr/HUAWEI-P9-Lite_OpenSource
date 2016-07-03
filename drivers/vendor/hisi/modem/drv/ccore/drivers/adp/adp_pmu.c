
/*lint --e{537}*/
#include "product_config.h"
#include "mdrv_pmu.h"
#include "bsp_pmu.h"
/*****************************************************************************
*  函 数 名  : mdrv_pmu_dcxo_fre_compensate
*  功能描述  : 为dcxo获取频率补偿
*  输入参数  : value:需要调节的值
*              
*  输出参数  : 无
*  返 回 值  : null
*             
******************************************************************************/   
void mdrv_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value)
{
    bsp_pmu_dcxo_fre_compensate(dcxoId,value);
}


