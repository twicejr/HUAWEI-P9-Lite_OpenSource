/*lint -save -e537*/
#include <osl_types.h>
#include <osl_bio.h>
#include "product_config.h"
#include "hi_syscrg_interface.h"
#include "bsp_reg_def.h"

#include "bsp_version.h"
#include "hi_gpio.h"
#include "bsp_memmap.h"

#include "hi_pwrctrl.h"
#include "hi_syscrg.h"

#include "ios_list.h"
#include "ios_pd.h"

#include "ios_ao_drv_macro.h"
#include "ios_pd_drv_macro.h"
#include "v7r5_udp_ios_lp_config.h"
/*lint -restore */

#ifdef GPIO_PL061

u32 reg_value[GPIO_MAX_BANK_NUM][10];

/* just for v7r5, maybe different with 722 */
void gpio_clk_enable(void)
{
	/* gpio2 clk enable */
	writel(0x1 << 2, 0x90000010);

	/* gpio3 clk enable */
	writel(0x1 << 30, 0x90000000);

	/* gpio4 to 12 clk enable */
	writel(0x1ff0, 0x90000020);
}

/* just for v7r5, maybe different with 722 */
void gpio_clk_disable(void)
{
	/* gpio2 clk disable */
	writel(0x1 << 2, 0x90000014);

	/* gpio3 clk disable */
	writel(0x1 << 30, 0x90000004);

	/* gpio4 to 12 clk disable */
	writel(0x1ff0, 0x90000024);
}

void gpio_reg_suspend(void)
{
    u32 i = 0;
	u32 base = GPIO_PD_BANK_BASE;

    for(i = 0;i < GPIO_PD_BANK_NUM;i++)
    {
        reg_value[i][0] = readl(base + GPIODIR);
        reg_value[i][1] = readl(base + GPIOIS);
        reg_value[i][2] = readl(base + GPIOIBE);
        reg_value[i][3] = readl(base + GPIOIEV);
        reg_value[i][4] = readl(base + (reg_value[i][0] << 2));

		reg_value[i][5] = readl(base + GPIOIE);
        reg_value[i][6] = readl(base + GPIOIE1);
        reg_value[i][7] = readl(base + GPIOIE2);
        reg_value[i][8] = readl(base + GPIOIE3);
        reg_value[i][9] = readl(base + GPIOIE4);
		base += SZ_4K;
    }

}

void gpio_suspend(void)
{
	gpio_reg_suspend();
	gpio_clk_disable();
}

void gpio_reg_resume(void)
{
    u32 i = 0;
	u32 base = GPIO_PD_BANK_BASE;

	for(i = 0;i < GPIO_PD_BANK_NUM;i++)
	{
		writel(reg_value[i][0], base + GPIODIR);
		writel(reg_value[i][1], base + GPIOIS);
		writel(reg_value[i][2], base + GPIOIBE);
		writel(reg_value[i][3], base + GPIOIEV);
		writel(reg_value[i][4], base + (reg_value[i][0] << 2));

		writel(reg_value[i][5], base + GPIOIE);
		writel(reg_value[i][6], base + GPIOIE1);
		writel(reg_value[i][7], base + GPIOIE2);
		writel(reg_value[i][8], base + GPIOIE3);
		writel(reg_value[i][9], base + GPIOIE4);
		base += SZ_4K;
	}

}

void gpio_resume(void)
{
	gpio_clk_enable();
	gpio_reg_resume();
}

/*just for pd gpio*/
int gpio_direction_input(u32 gpio)
{
	u32 base = 0, tmp = 0;
    u32 bank = gpio / PL061_GPIO_NR;
	u32 pin  = gpio % PL061_GPIO_NR;

	if(bank >= GPIO_MAX_BANK_NUM || bank < GPIO_PD_BANK_START)
	{
		return -1;
	}

	base = GPIO_PD_BANK_BASE + (bank - GPIO_PD_BANK_START) * SZ_4K;

    tmp = readl(base + GPIODIR);
    tmp &= ~(1u << pin);
    writel(tmp, base + GPIODIR);

	return 0;
}

/*just for pd gpio*/
int gpio_direction_output(u32 gpio, u32 value)
{
	u32 base = 0, tmp = 0;
    u32 bank = gpio / PL061_GPIO_NR;
	u32 pin  = gpio % PL061_GPIO_NR;

	if(bank >= GPIO_MAX_BANK_NUM || bank < GPIO_PD_BANK_START || value > 1)
	{
		return -1;
	}

	base = GPIO_PD_BANK_BASE + (bank - GPIO_PD_BANK_START) * SZ_4K;

    tmp  = readl(base + GPIODIR);
    tmp |= 1u << pin;
    writel(tmp, base + GPIODIR);

    writel(value << pin, base + (1u << (pin + 2)));

	return 0;

}


void ios_suspend(void)
{

    gpio_reg_suspend();

	if(HW_VER_V750_UDP == bsp_get_version_info()->board_id_udp_masked)
	{
		V7R5_UDP_IOS_LP_CONFIG;
	}
	gpio_clk_disable();
}


#ifdef CONFIG_IOS_TCM
#define IOS_REG_MAX 768
IOS_REG_DATA ios_reg[IOS_REG_MAX];

void ios_init(void)
{
	u32 i = 0;
	IOS_REG_DATA *tmp = NULL;
    IOS_POOL_CTRL *pctl = (IOS_POOL_CTRL *)SHARED_IOS_ADDR;

	if(pctl->cur - pctl->start > IOS_REG_MAX)
	{
		ios_print_error("reg too much!!\n");
		return;
	}

	memset(ios_reg, 0, sizeof(IOS_REG_DATA)*IOS_REG_MAX);

	tmp = pctl->start;
    while(tmp != pctl->cur)
    {
        ios_reg[i++] = *tmp++;
    }

	ios_print_info("init ok, 0x%x.\n", ios_reg);

}

void ios_reg_resume(void)
{
	u32 i = 0;
    /* coverity[overrun-local] */ /* coverity[cond_at_most] */
    while(0 != ios_reg[i].addr && i < IOS_REG_MAX)
    {
        writel(ios_reg[i].value, ios_reg[i].addr);
		++i;
    }
	//ios_print_info("ios resume %d.\n", i);

}
#else
void ios_init(void)
{
	ios_list_init();
}

#endif

void ios_resume(void)
{
	gpio_clk_enable();
    gpio_reg_resume();

#ifdef CONFIG_IOS_TCM
	ios_reg_resume();
#else
	ios_config_resume();
#endif

}

#else

void ios_init(void)
{
}

void gpio_suspend(void)
{
}

void gpio_resume(void)
{
}

void ios_suspend(void)
{
}

void ios_resume(void)
{
}

#endif

