


#ifndef __SOC_MEMMAP_H__
#define __SOC_MEMMAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#ifdef __KERNEL__
#include <soc_memmap_app.h>
#elif defined(__FASTBOOT__)
#include <soc_memmap_app.h>
#elif defined(__VXWORKS__)
#include <soc_memmap_mdm.h>
#elif defined(__CMSIS_RTOS)
#include <soc_memmap_m3.h>
#else
#include <soc_memmap_comm.h>
#endif

#ifdef __cplusplus
}
#endif

#endif    /* __SOC_MEMMAP_H__ */

