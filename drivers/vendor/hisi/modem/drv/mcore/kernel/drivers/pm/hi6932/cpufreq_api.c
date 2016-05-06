/*----------------------------------------------------------------------------
 *      balongv7r5 m3 cpufreq
 *----------------------------------------------------------------------------
 *      Name:    cpufreq_api.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r5 PWR.
 *---------------------------------------------------------------------------*/

#include <ARMCM3.h>
#include "console.h"
#include "printk.h"

#include "osl_types.h"
#include "osl_irq.h"
#include "osl_bio.h"

#include "bsp_shared_ddr.h"
#include "soc_interrupts_m3.h"

#include "m3_pm.h"
#include "bsp_softtimer.h"
#include "drv_edma_enum.h"
#include "edma_balong.h"
#include "dpm_balong.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "bsp_nvim.h"
#include "ios_pd.h"
#include "wdt_balong.h"
#include "m3_cpufreq.h"
#include "bsp_dsp.h"
#include "bsp_hardtimer.h"
#include "bsp_dfs_training.h"
#include "m3_cpufreq.h"
#include "cpufreq_api.h"



/**************************dfs**************************/

extern T_CPUFREQ_ST g_cpufreq;
static void dfs_config_reg(u32 cur, u32 new);
TCM_DFS_TRAINING *cpufreq_ddr_train = NULL;


T_CPUFREQ_PROFILE gCpufrqProfile[CPUFREQ_MAX_PROFILE+1] =
{
	{0, 0x40003333},
	{1, 0x40005555},
	{0, 0x40003311},
	{1, 0x40005511},
	{1, 0x40003311},
	{0, 0x40001300},
	{1, 0x40001311},
	{1, 0x40001300}
 };

/* only support 1067M and 667M */
T_CPUFREQ_PLL_CONFIG gCpufrqPll[CPUFREQ_MAX_PLL + 1] =
{
    {0x555555, 0x4101053},
	{0x6D5555, 0x2101045}
};
T_CPUFREQ_DDRC_CALC gDdrCalc[2];
extern u32 g_set_profile;
void set_pm_dfs_profile(u32 new_profile)
{
    if (new_profile > CPUFREQ_MAX_PROFILE)
    {
        printk("argc err:%d\n", new_profile);
    }
    g_set_profile = new_profile;
}

/* dfs */
void pm_dfs_bak(void)
{
	u32 cur = M3_CUR_CPUFREQ_PROFILE;
	u32 max = g_set_profile;
	u32 min_limit = M3_MIN_CPUFREQ_PROFILE;

	if(max < min_limit)
	{
		max = min_limit;
	}
	if(cur < max)
	{
		dfs_config_reg(cur, max);
		g_cpufreq.curprof = max;
		M3_CUR_CPUFREQ_PROFILE = max;
	}
}

void dfs_set_profile(u32 profile)
{
	dfs_config_reg(g_cpufreq.curprof, profile);
}

u32 dfs_get_profile(void)
{
	u32 profile = CPUFREQ_INVALID_PROFILE;
	T_CPUFREQ_PLL_CONFIG curconf;
	u32 invalid = 0xFFFFFFFF;
	u32 curpll = invalid;
	u32 curclkdiv = 0;
	u32 i = 0;

	/* find right pll */
	curconf.dfs1ctrl1 = readl(HI_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL1_OFFSET);
	curconf.dfs1ctrl2 = readl(HI_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL2_OFFSET);

	for(i = 0;i <= CPUFREQ_MAX_PLL;i++)
	{
		if(curconf.dfs1ctrl1 == gCpufrqPll[i].dfs1ctrl1)
		{
			if(curconf.dfs1ctrl2 == gCpufrqPll[i].dfs1ctrl2)
			{
				curpll = i;
				break;
			}
		}
	}
	if(curpll == invalid)
	{
		printk("get pll err\n");
		return CPUFREQ_INVALID_PROFILE;
	}
	/* find right profile */
	curclkdiv = readl(HI_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
    curclkdiv &= 0x4000FFFF;
	for(i = 0;i <= CPUFREQ_MAX_PROFILE;i++)
	{
		if(curpll == gCpufrqProfile[i].pll)
		{
			if(curclkdiv == gCpufrqProfile[i].clkdiv)
			{
				profile = i;
				break;
			}
		}
	}

	return profile;
}

s32 dfs_get_cur_mode(u32 *cur_ddr)
{
	return 0;
}

void dfs_get_ddrc_timing(u32 fbus, u32 pll, T_CPUFREQ_DDRC_TIMING* ptiming)
{
	/* 400M */
	if(0 == pll)
	{
		switch(fbus)
		{
			case 1:
				ptiming->nxttiming0 = 0x52650F09;
				ptiming->nxttiming1 = 0xEA7461A;
				ptiming->nxttiming2 = 0x6250C030;
				ptiming->nxttiming3 = 0xFFCC9022;
				break;

			case 3:
				ptiming->nxttiming0 = 0x52330805;
				ptiming->nxttiming1 = 0x7A7460D;
				ptiming->nxttiming2 = 0x62508018;
				ptiming->nxttiming3 = 0xFFC65022;
				break;
			default:
				break;
		}
	}
	else if(1 == pll)/* 666M */
	{
		switch(fbus)
		{
			case 1:
				ptiming->nxttiming0 = 0x5498170E;
				ptiming->nxttiming1 = 0x18A7462C;
				ptiming->nxttiming2 = 0x64514051;
				ptiming->nxttiming3 = 0xFFD4E033;
				break;

			case 3:
				ptiming->nxttiming0 = 0x52540C07;
				ptiming->nxttiming1 = 0xCA74616;
				ptiming->nxttiming2 = 0x6250A028;
				ptiming->nxttiming3 = 0xFFCA7022;
				break;
			case 5:
				ptiming->nxttiming0 = 0x52330805;
				ptiming->nxttiming1 = 0x8A7460F;
				ptiming->nxttiming2 = 0x6250801B;
				ptiming->nxttiming3 = 0xFFC70022;
				break;
			default:
				break;
		}
	}
	else
	{
		printk("dfs get_timing err\n");
	}

}


void dfs_ddrc_config(u32 fbus, u32 pll)

{
    /* 400M */
    if(0 == pll)
    {
        switch(fbus)
        {
            case 1:
                writel(gDdrCalc[1].ddr_reg_83c, HI_CM3_DDRC_BASE_ADDR + 0x83c);
                writel(gDdrCalc[1].ddr_reg_abc, HI_CM3_DDRC_BASE_ADDR + 0xabc);
                writel(gDdrCalc[1].ddr_reg_b3c, HI_CM3_DDRC_BASE_ADDR + 0xb3c);
                writel(gDdrCalc[1].ddr_reg_bbc, HI_CM3_DDRC_BASE_ADDR + 0xbbc);
                writel(gDdrCalc[1].ddr_reg_c3c, HI_CM3_DDRC_BASE_ADDR + 0xc3c);
                break;
            case 3:
            case 7:
                writel(gDdrCalc[0].ddr_reg_83c, HI_CM3_DDRC_BASE_ADDR + 0x83c);
                writel(gDdrCalc[0].ddr_reg_abc, HI_CM3_DDRC_BASE_ADDR + 0xabc);
                writel(gDdrCalc[0].ddr_reg_b3c, HI_CM3_DDRC_BASE_ADDR + 0xb3c);
                writel(gDdrCalc[0].ddr_reg_bbc, HI_CM3_DDRC_BASE_ADDR + 0xbbc);
                writel(gDdrCalc[0].ddr_reg_c3c, HI_CM3_DDRC_BASE_ADDR + 0xc3c);
                break;
            default:
                break;
        }
    }
    else if(1 == pll)/* 666M */
    {
        switch(fbus)
        {
            case 1:
                writel(gDdrCalc[1].ddr_reg_83c, HI_CM3_DDRC_BASE_ADDR + 0x83c);
                writel(gDdrCalc[1].ddr_reg_abc, HI_CM3_DDRC_BASE_ADDR + 0xabc);
                writel(gDdrCalc[1].ddr_reg_b3c, HI_CM3_DDRC_BASE_ADDR + 0xb3c);
                writel(gDdrCalc[1].ddr_reg_bbc, HI_CM3_DDRC_BASE_ADDR + 0xbbc);
                writel(gDdrCalc[1].ddr_reg_c3c, HI_CM3_DDRC_BASE_ADDR + 0xc3c);
                break;
            case 3:
            case 5:
            case 7:
                writel(gDdrCalc[0].ddr_reg_83c, HI_CM3_DDRC_BASE_ADDR + 0x83c);
                writel(gDdrCalc[0].ddr_reg_abc, HI_CM3_DDRC_BASE_ADDR + 0xabc);
                writel(gDdrCalc[0].ddr_reg_b3c, HI_CM3_DDRC_BASE_ADDR + 0xb3c);
                writel(gDdrCalc[0].ddr_reg_bbc, HI_CM3_DDRC_BASE_ADDR + 0xbbc);
                writel(gDdrCalc[0].ddr_reg_c3c, HI_CM3_DDRC_BASE_ADDR + 0xc3c);
                break;
            default:
                break;
        }
    }
    else
    {
        printk("dfs_ddrc_config err\n");
    }

}

static void dfs_config_reg(u32 cur, u32 new)
{
	u32 tmp = 0;
	u32 curfbus = 0;
	u32 newfbus = 0;
	u32 curpll = 0;
	u32 newpll = 0;
	u32 ddrcnochange = 0;
    volatile u32 times = 0;
    u32 dfs1_ctrl3 = 0;
	T_CPUFREQ_DDRC_TIMING timing = {0};
	cpufreq_dump_pro_timeslice(cur, new);
	/* 1 */
	tmp = readl(HI_CM3_LP_PWRCTRL0);
	tmp |= 0x10000;
	writel(tmp, HI_CM3_LP_PWRCTRL0);

	/* 2 */
	curpll = gCpufrqProfile[cur].pll;
	newpll = gCpufrqProfile[new].pll;
	curfbus = (gCpufrqProfile[cur].clkdiv >> 12) & 0xf;
	newfbus = (gCpufrqProfile[new].clkdiv >> 12) & 0xf;
	if(curpll == newpll)
	{
		if(curfbus == newfbus)
		{
			/* ddrc no change */
			ddrcnochange = 1;
			goto step6;
		}
	}

	/* 3 */
	dfs_get_ddrc_timing(newfbus, newpll, &timing);
	writel(timing.nxttiming0, HI_CM3_DDRC_BASE_ADDR + 0x70);
	writel(timing.nxttiming1, HI_CM3_DDRC_BASE_ADDR + 0x74);
	writel(timing.nxttiming2, HI_CM3_DDRC_BASE_ADDR + 0x78);
	writel(timing.nxttiming3, HI_CM3_DDRC_BASE_ADDR + 0x7c);

	/* 4 */
	writel(0x1, HI_CM3_DDRC_BASE_ADDR + HI_MDDRC_SREFCTRL_OFFSET);
	do{
		tmp = readl(HI_CM3_DDRC_BASE_ADDR);
		tmp &= 0x4;
	}while(!tmp);
    times = 20;
    while(times)
    {
        times--;
    }
    /* 5 */
	dfs_ddrc_config(newfbus, newpll);
	/* 6 */
step6:
	if(curpll == newpll)
	{
        tmp = readl(HI_CM3_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
        tmp &= 0xBFFF0000;
        tmp |= gCpufrqProfile[new].clkdiv;
        writel(tmp, HI_CM3_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
		/* pll no change */
		goto step12;
	}

	/* 7 */
	tmp = readl(HI_CM3_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
	tmp &= 0xBFFF0000;
	tmp |= 0x40001300;
	writel(tmp, HI_CM3_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
	writel(0x8, HI_CM3_CRG_BASE_ADDR + HI_CRG_CLKEN4_OFFSET);
	writel(0x8, HI_CM3_CRG_BASE_ADDR + HI_CRG_CLK_SEL2_OFFSET);
	dfs1_ctrl3 = readl(HI_CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);

	/* 8 */
	writel(0x129, HI_CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);

	/* 9 */
	writel(gCpufrqPll[newpll].dfs1ctrl1, HI_CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL1_OFFSET);
	writel(gCpufrqPll[newpll].dfs1ctrl2, HI_CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL2_OFFSET);
    times = 30;
    while(times)
    {
        times--;
    }
	writel(0x128, HI_CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);

	/* 10 */
	do
	{
		tmp = readl(HI_CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);
		tmp = (tmp >> 31) & 0x1;
	}while(!tmp);

	/* 11 */
	writel(0x1, HI_CM3_CRG_BASE_ADDR + HI_CRG_CLK_SEL2_OFFSET);

	tmp = readl(HI_CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);
	tmp &= ~0x100;
	dfs1_ctrl3 &= 0x100;
	tmp |= dfs1_ctrl3;
	writel(tmp, HI_CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);
    writel(0x8, HI_CM3_CRG_BASE_ADDR + HI_CRG_CLKDIS4_OFFSET);

	/* 12 */
    tmp = readl(HI_CM3_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);
    tmp &= 0xBFFF0000;
    tmp |= gCpufrqProfile[new].clkdiv;
    writel(tmp, HI_CM3_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

	/* 13 */
step12:
	if(ddrcnochange)
	{
		goto step16;
	}
	/* 14 */
	writel(0x40000, HI_CM3_CRG_BASE_ADDR + HI_CRG_SSRSTEN1_OFFSET);
	writel(0x40000, HI_CM3_CRG_BASE_ADDR + HI_CRG_SSRSTDIS1_OFFSET);
	/* 15 */
	writel(0x0, HI_CM3_DDRC_BASE_ADDR + HI_MDDRC_SREFCTRL_OFFSET);
	do{
		tmp = readl(HI_CM3_DDRC_BASE_ADDR);
		tmp &= 0x4;
	}while(tmp);
    times = 20;
    while(times)
    {
        times--;
    }

	/* 16 */
step16:
	tmp = readl(HI_CM3_LP_PWRCTRL0);
	tmp &= ~0x10000;
	writel(tmp, HI_CM3_LP_PWRCTRL0);
}

void dfs_ddrc_calc(void)
{
	SRAM_SMALL_SECTIONS * sram_mem = ((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS));
    gDdrCalc[0].ddr_reg_83c = sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_83c;
	gDdrCalc[1].ddr_reg_83c = sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_83c;

	gDdrCalc[0].ddr_reg_abc = sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_abc;
	gDdrCalc[1].ddr_reg_abc = sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_abc;

	gDdrCalc[0].ddr_reg_b3c = sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_b3c;
	gDdrCalc[1].ddr_reg_b3c = sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_b3c;

	gDdrCalc[0].ddr_reg_bbc = sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_bbc;
	gDdrCalc[1].ddr_reg_bbc = sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_bbc;

	gDdrCalc[0].ddr_reg_c3c = sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_c3c;
	gDdrCalc[1].ddr_reg_c3c = sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_c3c;
}
