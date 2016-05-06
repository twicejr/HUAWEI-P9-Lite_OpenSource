#ifndef _EARPIECE_PA_H_
#define _EARPIECE_PA_H_

#include <linux/ioctl.h>
#include <linux/notifier.h>


/*----------------------data struct define----------------------*/

#define EAR_PA_OPEN    _IO('A', 0x80)
#define EAR_PA_CLOSE   _IO('A', 0x81)

/*----------------------log define----------------------*/

#define LOG_TAG "earpice_pa"

#define PRINT_INFO  1
#define PRINT_WARN  1
#define PRINT_DEBUG 1
#define PRINT_ERR   1

#if PRINT_INFO
#define logi(fmt, ...) printk("[" LOG_TAG "][I]" fmt "\n", ##__VA_ARGS__)
#else
#define logi(fmt, ...) ((void)0)
#endif

#if PRINT_WARN
#define logw(fmt, ...) printk("[" LOG_TAG "][W]" fmt "\n", ##__VA_ARGS__)
#else
#define logw(fmt, ...) ((void)0)
#endif

#if PRINT_DEBUG
#define logd(fmt, ...) printk("[" LOG_TAG "][D]" fmt "\n", ##__VA_ARGS__)
#else
#define logd(fmt, ...) ((void)0)
#endif

#if PRINT_ERR
#define loge(fmt, ...) printk("[" LOG_TAG "][E]" fmt "\n", ##__VA_ARGS__)
#else
#define loge(fmt, ...) ((void)0)
#endif


#endif //_EARPIECE_PA_H_
