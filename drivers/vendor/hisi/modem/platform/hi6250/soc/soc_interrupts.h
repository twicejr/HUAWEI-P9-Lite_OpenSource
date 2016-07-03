


#ifndef __SOC_INTERRUPTS_H__
#define __SOC_INTERRUPTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#ifdef __KERNEL__
#include <soc_interrupts_app.h>
#elif defined(__FASTBOOT__)
#include <soc_interrupts_app.h>
#elif defined(__VXWORKS__) || defined(__OS_RTOSCK__)
#include <soc_interrupts_mdm.h>
#elif defined(__CMSIS_RTOS)
#include <soc_interrupts_m3.h>
#else
#include <soc_interrupts_comm.h>
#endif

#ifdef __cplusplus
}
#endif

#endif    /* __SOC_INTERRUPTS_H__ */

