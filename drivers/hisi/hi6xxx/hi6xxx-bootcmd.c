#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/smp.h>
#include <linux/memblock.h>
#include <linux/irqchip.h>


#include <asm/arch_timer.h>
#include <asm/smp_plat.h>
#include <asm/proc-fns.h>
#include <linux/hisi/hw_cmdline_parse.h>

#include <huawei_platform/log/hw_log.h>
#define HWLOG_TAG	cmdline_parse
HWLOG_REGIST();


static unsigned int runmode_factory = RUNMODE_FLAG_NORMAL;

static int __init early_parse_runmode_cmdline(char * p)
{
    if(p)
    {
        if(!strcmp(p,"factory"))
        {
            runmode_factory = RUNMODE_FLAG_FACTORY;
        }

        printk("runmode is %s, runmode_factory = %d\n", p, runmode_factory);
    }

    return 0;
}

early_param("androidboot.swtype", early_parse_runmode_cmdline);

/* the function interface to check factory/normal mode in kernel */
unsigned int runmode_is_factory(void)
{
    return runmode_factory;
}

EXPORT_SYMBOL(runmode_is_factory);


static int logctl_flag = 0;	//default 0, switch logger off
int get_logctl_value(void)
{
    return logctl_flag;
}
EXPORT_SYMBOL(get_logctl_value);

unsigned int enter_recovery_flag;
/**
* parse boot_into_recovery cmdline which is passed from boot_recovery() of boot.c *
* Format : boot_into_recovery_flag=0 or 1             *
*/
static int __init early_parse_enterrecovery_cmdline(char * p)
{
    char enter_recovery[HEX_STRING_MAX + 1];
    char *endptr = NULL;

    memset(enter_recovery, 0, (HEX_STRING_MAX + 1));

    memcpy(enter_recovery, p, HEX_STRING_MAX);
    enter_recovery[HEX_STRING_MAX] = '\0';

    enter_recovery_flag = simple_strtoull(enter_recovery, &endptr, TRANSFER_BASE);

    printk("enter recovery p:%s, enter_recovery_flag :%d\n", p, enter_recovery_flag);

    return 0;
}
early_param("enter_recovery", early_parse_enterrecovery_cmdline);

unsigned int get_boot_into_recovery_flag(void)
{
    return enter_recovery_flag;
}
EXPORT_SYMBOL(get_boot_into_recovery_flag);

static int __init early_parse_logctl_cmdline(char * p)
{
    char logctl[HEX_STRING_MAX + 1];
    char *endptr = NULL;

    if (p == NULL) {
        logctl_flag = 0;	//error parameter, switch logger off
        hwlog_err("%s: setup_logctl parameter error!\n", __func__);
        return 0;
    }

    memset(logctl, 0, (HEX_STRING_MAX + 1));

    memcpy(logctl, p, HEX_STRING_MAX);

    logctl_flag = simple_strtoull(logctl, &endptr, TRANSFER_BASE);

    hwlog_info("%s: p: %s, logctl: %d\n", __func__, p, logctl_flag);

    return 0;
}
early_param("setup_logctl", early_parse_logctl_cmdline);


int trial_version = 0;
static int __init trial_version_setup(char *__unused)
{
	trial_version = 1;

	return 0;
}
int check_acore_only(void)
{
	return trial_version; 
}
early_param("trial_version", trial_version_setup);



static int uart_console_enabled = 1;
static int __init uart_console_config(char *__unused)
{
	uart_console_enabled = 0;

	return 0;
}
early_param("no_uart_console", uart_console_config);

int get_uart0_config(void)
{
	return uart_console_enabled;
}
EXPORT_SYMBOL(get_uart0_config);
