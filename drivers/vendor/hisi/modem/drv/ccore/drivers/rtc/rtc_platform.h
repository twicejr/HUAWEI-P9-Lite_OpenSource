

#ifndef __RTC_PLATFORM_H__
#define __RTC_PLATFORM_H__

typedef enum _rtc_platform_e
{
    MDRV_RTC_PMU,
    MDRV_RTC_SOC,
    MDRV_RTC_MAX
}rtc_platform;

#ifdef CONFIG_RTC_ON_PMU
#define CONFIG_RTC_COMPATIBLE "arm,rtc_pmu"
#define CONFIG_RTC_PLATFORM MDRV_RTC_PMU
#endif

#ifdef CONFIG_RTC_ON_SOC
#define CONFIG_RTC_COMPATIBLE "arm,rtc_soc"
#define CONFIG_RTC_PLATFORM MDRV_RTC_SOC
#endif

#if !defined(CONFIG_RTC_ON_PMU) && !defined(CONFIG_RTC_ON_SOC)
#define CONFIG_RTC_COMPATIBLE "arm,rtc_none"
#define CONFIG_RTC_PLATFORM MDRV_RTC_MAX
#endif

s32 get_rtc_addr(struct device_node *dev_np, s32 index, const char *label, u32 *addr);
u32 get_rtc_curr(const u32 addr);

#endif /* __BSP_PAN_RPC_H__ */

