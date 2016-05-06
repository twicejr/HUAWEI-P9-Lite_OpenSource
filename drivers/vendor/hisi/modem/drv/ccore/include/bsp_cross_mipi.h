/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_tuner.h
*
*   作    者 :  z00227143
*
*   描    述 :
*
*   修改记录 :  2013年2月2日  v1.00  z00227143  创建
*************************************************************************/
#ifndef __BSP_CROSS_MIPI_H__
#define __BSP_CROSS_MIPI_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <RfNvId.h>
#include <product_config.h>

#ifdef CONFIG_CROSS_MIPI

#define NV_GU_RF_CROSS_MIPI_MEM_ID  (en_NV_Item_CROSS_MIPI_MEM_ID)
#define NV_GU_RF_CROSS_MIPI_CTRL_ID (en_NV_Item_CROSS_MIPI_CTRL_ID)

#define NV_GU_RF_CROSS_MIPI_GPIO_CTRL_ID     (en_NV_Item_CROSS_GPIO_MIPI_CTRL_ID)
#define NV_GU_RF_CROSS_MIPI_TUNER0_MEM_ID    (en_NV_Item_CROSS_MIPI_TUNER0_ID)
#define NV_GU_RF_CROSS_MIPI_TUNER1_MEM_ID    (en_NV_Item_CROSS_MIPI_TUNER1_ID)
#define NV_GU_RF_CROSS_MIPI_TUNER2_MEM_ID    (en_NV_Item_CROSS_MIPI_TUNER2_ID)
#define NV_GU_RF_CROSS_GPIO_TUNER_MEM_ID     (en_NV_Item_CROSS_GPIO_TUNER_ID)

void bsp_cross_mipi_init(void);



#else

static inline void bsp_cross_mipi_init(void)
{
    return;
}

#endif

#ifdef __cplusplus
}
#endif

#endif

