#ifndef __MDRV_CCORE_RTC_H__
#define __MDRV_CCORE_RTC_H__
#ifdef __cplusplus
extern "C"
{
#endif

struct rtc_time
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
    unsigned int tm_value;
};

int mdrv_rtc_read_time(struct rtc_time *tm);
unsigned int mdrv_rtc_get_value(void);

#ifdef __cplusplus
}
#endif
#endif
