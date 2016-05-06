/*----------------------------------------------------------------------------
 *      balongv7r2 m3 pm
 *----------------------------------------------------------------------------
 *      Name:    pm.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r2 PWR.
 *---------------------------------------------------------------------------*/

#include <cmsis_os.h>
#include <product_config.h>
#include <osl_common.h>
#include <soc_memmap_m3.h>
#include <hi_base.h>
#include <hi_syssc.h>
#include <mdrv_ipc.h>
#include <ipc_balong.h>
#include <wdt_balong.h>
#include <hisi_mem_repair.h>

__ao_func void modem_subsys_init(void)
{
    u32 tmp;

    /* modem subsystem  */
    writel(0x804, 0x40235050);
    writel(0x18000000, 0x40235064);
    writel(0x10000000, 0x40235094);

    tmp = readl(0x40231380);
    tmp &= 0xFFFFFFF7;
    writel(tmp, 0x40231380);

    do
	{
		tmp = readl(0x40231388);
		tmp = (tmp >> 3) & 0x1;
	}while(tmp);

    do
	{
		tmp = readl(0x40231384);
		tmp = (tmp >> 3) & 0x1;
	}while(tmp);

    /* sec */
	/*writel(0x0, HI_SYSCTRL_BASE_ADDR + HI_SEC_CTRL0_OFFSET);*/
	tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_SEC_CTRL0_OFFSET);
	tmp = tmp & ~((u32)0x1 << 9);  /*nsec-read ok*/
	writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_SEC_CTRL0_OFFSET)
}

/* a9 bbe bbp */
__ao_func void mdm_a9pll_init(void)
{
    u32 tmp = 0;

    // a9 pll: 667
    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
    tmp &= 0xFF000000;
    tmp |= 0x00600000;
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
    writel(0x00A04505, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);

    do
	{
		tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG0_OFFSET);
		tmp = (tmp >> 26) & 0x1;
	}while(!tmp);

    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
    tmp |= (0x1<<26);
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_A9PLL_CFG1_OFFSET);
}

__ao_func void mdm_bbepll_init(void)
{
    u32 tmp = 0;

    /* 6 7 8 bbe core :100*/
    tmp = readl(HI_LP_PERI_CRG_REG_ADDR + 0xDC);
    /* first :div [3:0] div=2 */
    tmp &= ~0xF;
    tmp |= 0xF0001;
    writel(tmp, HI_LP_PERI_CRG_REG_ADDR + 0xDC);
    /* bbe sel ccpu pll */
    tmp &= ~0x30;
    tmp |= 0x300010;
    writel(tmp, HI_LP_PERI_CRG_REG_ADDR + 0xDC);
}

__ao_func void mdm_bbppll_init(void)
{
    u32 tmp = 0;

    /* 9 10 11 bbp pll:491*/
    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_BBPPLL_CFG0_OFFSET);
    tmp &= 0xFFFFFFFC;
    tmp |= 0x1;
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_BBPPLL_CFG0_OFFSET);

    do
    {
        tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_BBPPLL_CFG0_OFFSET);
        tmp = (tmp >> 26) & 0x1;
    }while(!tmp);

    tmp = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_BBPPLL_CFG1_OFFSET);
    tmp |= (0x1<<26);
    writel(tmp, HI_SYSCTRL_BASE_ADDR + HI_CRG_BBPPLL_CFG1_OFFSET);
}

void startup_modem(void)
{
    u32 tmp = 0;
    mdm_a9pll_init();
    mdm_bbepll_init();

    mdm_bbppll_init();

    /* 12 a9 bbe ref_clk enable*/
    writel(0x3<<24, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKEN3_OFFSET);

    /* 13 bus div: 0,0,3*/
    writel(0x40040300, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

    /* 14 */
    writel(0x40010300, HI_SYSCTRL_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
}

void modem_start_init(void)
{
    modem_subsys_init();
    hisi_ip_mem_repair(MRB_MODEM);
    startup_modem();
}
