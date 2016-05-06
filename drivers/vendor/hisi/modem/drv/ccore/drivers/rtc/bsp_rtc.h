
#ifndef __BSP_RTC_H__
#define __BSP_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <mdrv_rtc.h>

#define RTC_OK          (0)
#define RTC_ERROR       (-1)

#define rtc_log(fmt,...) (SRE_Printf("[rtc]:[func: %s],[line: %d]"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))

#ifdef __cplusplus
}
#endif

#endif /*  __BSP_RTC_H__ */
