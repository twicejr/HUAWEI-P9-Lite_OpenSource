#ifndef __BSP_TSENSOR_H__
#define __BSP_TSENSOR_H__

#include <product_config.h>
#include <osl_types.h>

enum temp_type{
    en_temp_high,
    en_temp_low,
};
typedef void (*pTFUNCPTR)(enum temp_type);

#ifdef CONFIG_TSENSOR
void bsp_tsensor_init(void); /* for C core and M3 core */

#if defined(__OS_RTOSCK__)  
enum temp_type bsp_tsensor_temptype_get(void); 
s32 bsp_tsensor_callback_regist(pTFUNCPTR p);
#endif

#if defined(__CMSIS_RTOS)   
void bsp_tsensor_enable(void);
void bsp_tsensor_disable(void);
#endif

#else
void bsp_tsensor_init(void){} /* for C core and M3 core */

#if defined(__OS_RTOSCK__)  
enum temp_type bsp_tsensor_temptype_get(void){ return en_temp_low; }
s32 bsp_tsensor_callback_regist(pTFUNCPTR p){ return 0; }
#endif

#if defined(__CMSIS_RTOS)   
void bsp_tsensor_enable(void){}
void bsp_tsensor_disable(void){}
#endif  /* #if defined(__CMSIS_RTOS) */
#endif  /* #ifdef CONFIG_TSENSOR     */
#endif  /* #ifdef __BSP_TSENSOR_H__  */
