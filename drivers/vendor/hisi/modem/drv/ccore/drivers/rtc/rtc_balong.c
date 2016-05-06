

/*lint -save -e534 -e586 -e801 -e830*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <osl_types.h>
#include <of.h>
#include <bsp_rtc.h>
#include <rtc_platform.h>
#include <mdrv_public.h>

#define LEAPS_THRU_END_OF(y)    (((y)/4 - (y)/100) + (y)/400)

/*全局变量结构体定义*/
struct rtc_control
{
    u32 rtc_base_addr;                  /*RTC 寄存器基地址*/
    s32 rtc_days_in_month[12];
    u32 mapped;
};

struct rtc_control g_rtc_ctrl =
{
    0,
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    0
};

static s32 is_leap_year(u32 year)
{
    return (!(year % 4) && (year % 100)) || !(year % 400);
}

/*
 * The number of days in the month.
 */
static s32 rtc_month_days(u32 month, u32  year)
{
    return g_rtc_ctrl.rtc_days_in_month[month] + (s32)(is_leap_year(year) && (month == 1));
}

/*
 * Convert seconds since 01-01-1970 00:00:00 to Gregorian date.
 */
static void rtc_time_to_tm(u32 time, struct rtc_time *tm)
{
    unsigned int month, year;
    int days;

    tm->tm_value = time;
    days = (int)(time / 86400);
    time -= (unsigned int) days * 86400;

    /* day of the week, 1970-01-01 was a Thursday */
    tm->tm_wday = (days + 4) % 7;

    year = (unsigned int)(1970 + days / 365);
    days -= (s32)((year - 1970) * 365
        + LEAPS_THRU_END_OF(year - 1)
        - LEAPS_THRU_END_OF(1970 - 1));
    if (days < 0)
    {
        year -= 1;
        days += 365 + is_leap_year(year);
    }
    tm->tm_year = (int)year;
    tm->tm_yday = days + 1;

    for (month = 0; month < 11; month++)
    {
        int newdays;

        newdays = days - rtc_month_days(month, year);
        if (newdays < 0)
            break;
        days = newdays;
    }
    tm->tm_mon = (int)(month) + 1;
    tm->tm_mday = days + 1;

    tm->tm_hour = (int)(time / 3600);
    time -= (u32)(tm->tm_hour * 3600);
    tm->tm_min = (int)(time / 60);
    tm->tm_sec = (int)((int)time - tm->tm_min * 60);

    tm->tm_isdst = 0;
}

unsigned int mdrv_rtc_get_value(void)
{
    u32 value = 0;
    s32 ret   = 0;

    if (g_rtc_ctrl.mapped == 0)
    {
        struct device_node *np;

        np = of_find_compatible_node(NULL, NULL, CONFIG_RTC_COMPATIBLE);
        if (!np)
        {
            rtc_log("of_find_compatible_node");
            return 0;
        }

        ret = get_rtc_addr(np, 0, "offset", &(g_rtc_ctrl.rtc_base_addr));
        if (ret)
        {
            rtc_log("get_rtc_addr");
            return 0;
        }
        g_rtc_ctrl.mapped = 1;
    }

    value = get_rtc_curr(g_rtc_ctrl.rtc_base_addr);

    return value;
}

int mdrv_rtc_read_time(struct rtc_time *tm)
{
    u32 value = mdrv_rtc_get_value();

    if(NULL == tm)
    {
        rtc_log("the parameter error, tm == NULL!\n");
        return MDRV_ERROR;
    }

    rtc_time_to_tm(value, tm);

    return MDRV_OK;
}

u32 hwclock_r(void)
{
    u32             value = 0;
    struct rtc_time tm    = {0};

    value = mdrv_rtc_read_time(&tm);

    SRE_Printf("[rtc](%.4d-%.2d-%.2d %.2d:%.2d:%.2d)\n",
        tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return value;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*lint -restore*/

