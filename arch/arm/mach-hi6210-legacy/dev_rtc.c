/*rtc device declare and register*/
#include <linux/platform_device.h>
#include <mach/platform.h>

struct resource rtc_res={
	.start  = REG_BASE_RTC,
	.end    = REG_BASE_RTC + SZ_4K - 1,
	.flags  = IORESOURCE_MEM,
};

 static struct platform_device rtc_device = {
	.name =	"rtc-hi6620",
	.dev  =	{
		.init_name = "rtc-hi6620",
	},
	.num_resources	= 1,
	.resource	= &rtc_res,
	.id	= -1,
};

static int __init rtc_dev_init(void)
{
    /* platform devices were addded here. */
	return platform_device_register(&rtc_device);

}

arch_initcall(rtc_dev_init);

