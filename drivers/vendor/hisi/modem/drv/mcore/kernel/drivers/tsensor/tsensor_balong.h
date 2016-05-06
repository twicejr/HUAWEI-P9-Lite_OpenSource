#ifndef _TSENSOR_BALONG_H_
#define _TSENSOR_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <osl_spinlock.h>
#include <bsp_om.h>
#include <bsp_shared_ddr.h>

spinlock_t g_tsensor_lock;

#define TSEN_OK 0
#define TSEN_ERR -1

#define TSENSOR_ICC_CHAN                (ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_TSENSOR)
#define TSEN_TEMP1_MASK                 0x3FF

#define TSENSOR_SHM_BASE                ((u32)SHM_BASE_ADDR + SHM_OFFSET_TSENSOR_STAMP)
#define TSENSOR_ENABLE_STAMP            TSENSOR_SHM_BASE
#define TSENSOR_ICC_SEND_STAMP          (TSENSOR_SHM_BASE + 4)

#define tsensor_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_TSENSOR, "<%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define tsensor_print_always(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_TSENSOR, fmt, ##__VA_ARGS__))

#define TSEN_CODE2TEMP(c)               ((c-116)*165/806-40)
#define TSEN_TEMP2CODE(T)               ((T+40)*806/165+116) 

#define DEFAULT_TEMP_LOW_THRESHODE      10      /* µÍÎÂ¸æ¾¯ÃÅÏÞ */
#define DEFAULT_CODE_THRESHODE          TSEN_TEMP2CODE(DEFAULT_TEMP_LOW_THRESHODE)     

#define TSENSOR_DEBUG(a,b)              ((a) = (b))

#ifdef __cplusplus
}
#endif

#endif
