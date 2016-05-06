

/*lint -save -e534 -e586 -e801*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <osl_types.h>
#include <of.h>
#include <bsp_pmu.h>
#include "rtc_platform.h"

#define PMU_BASE_ADDR (bsp_pmic_get_base_addr())
#define RTC_REG_MASK  (0xff)

static unsigned pmu_read_reg(unsigned addr)
{
    unsigned value = 0;

    value = readl(PMU_BASE_ADDR + (addr << 2));

    return value;
}

static unsigned pmu_rtc_read(unsigned addr)
{
    unsigned val0  = 0;
    unsigned val1  = 0;
    unsigned val2  = 0;
    unsigned val3  = 0;
    unsigned value = 0;

    val0 = pmu_read_reg(addr + 0);
    val1 = pmu_read_reg(addr + 1);
    val2 = pmu_read_reg(addr + 2);
    val3 = pmu_read_reg(addr + 3);

    value = val0 | (val1 << 8) | (val2 << 16) | (val3 << 24);

    return value;
}

s32 get_rtc_addr(struct device_node *dev_np, s32 index, const char *label, u32 *addr)
{
    s32 ret = 0;

    switch(CONFIG_RTC_PLATFORM)
    {
        case MDRV_RTC_PMU:
            ret = of_property_read_u32(dev_np, label, addr);
            break;
        case MDRV_RTC_SOC:
            *addr = (u32)of_iomap(dev_np, index);
            ret = (*addr) ? (0) : (-1); 
            break;
        default:
            ret = -1;
            break;
    }

    return ret;
}

u32 get_rtc_curr(const u32 addr)
{
    u32 value  = 0;

    switch(CONFIG_RTC_PLATFORM)
    {
        case MDRV_RTC_PMU:
            if(!!PMU_BASE_ADDR)
            {
                value = pmu_rtc_read(addr);
            }
            break;
        case MDRV_RTC_SOC:
            value = readl(addr);
            break;
        default:
            break;
    }

    return value;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

/*lint -restore*/

