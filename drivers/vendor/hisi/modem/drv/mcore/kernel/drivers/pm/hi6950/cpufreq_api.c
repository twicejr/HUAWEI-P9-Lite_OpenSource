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
#include "bsp_ipc.h"
#include "mdrv_ipc.h"
#include "cpufreq_api.h"



/**************************dfs**************************/

extern T_CPUFREQ_ST g_cpufreq;
void dfs_config_reg(u32 cur, u32 new);
TCM_DFS_TRAINING *cpufreq_ddr_train = NULL;
struct dfs_ddr_refresh_ctrl{
	u32 acore_cti_is_debug_stat;
	u32 ccore_cti_is_debug_stat;
	u32 mcore_ddr_option;
	u32 ipc_sem_flag;
};
struct dfs_ddr_refresh_ctrl ddr_refrest_ctrl = {0};

T_CPUFREQ_PROFILE gCpufrqProfile[CPUFREQ_MAX_PROFILE+1] =
{
    {0, 0x00005555, DDR_FREQ_111},//111,111
	{3, 0x40007777, DDR_FREQ_133},//133,133
	{0, 0x40003333, DDR_FREQ_166},//166,166
	{1, 0x00003733, DDR_FREQ_200},//200,200
	{3, 0x00003733, DDR_FREQ_266},//266,266
	{0, 0x40001311, DDR_FREQ_333},//333.333
	{1, 0x40001311, DDR_FREQ_400},//400,400
	//{2, 0x40001311, DDR_FREQ_450},//450.450
	//{3, 0x40001311, DDR_FREQ_533},//533,1066
	{1, 0x40001300, DDR_FREQ_400},//400,800
	//{2, 0x40001300, DDR_FREQ_450},//450.900
	{3, 0x40001300, DDR_FREQ_533}//533,1066
 };

 /* only support 1067M and 667M */
 T_CPUFREQ_PLL_CONFIG gCpufrqPll[CPUFREQ_MAX_PLL + 1] =
 {
	{0x6d5555, 0x2101045},
	{0x555555, 0x2101053},
	{0xc00000, 0x210105d},
	{0x855555, 0x1101037},
 };

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
	curconf.dfs1ctrl1 = readl(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL1);
	curconf.dfs1ctrl2 = readl(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL2);

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
	curclkdiv = readl(CPUFREQ_SC_BASE_ADDR + CPUFREQ_PD_CRG_CLKDIV2);

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

static u32 dfs_get_pro_mode(u32 pro)
{
	u32 curfbus = 0;
	u32 curpll = 0;
	
	curpll = gCpufrqProfile[pro].pll;
	curfbus = (gCpufrqProfile[pro].clkdiv >> 12) & 0xf;
	return ((curpll > 1) && (curfbus < 3)) ? mission_mode : bypass_mode;
}
s32 dfs_get_cur_mode(u32 *cur_ddr)
{
	u32 tmp = 0;
	tmp = dfs_get_profile();
	if(tmp == CPUFREQ_INVALID_PROFILE)
	{
		//M3CPUFREQ_PRINT("cut profile invalid\n");
		tmp = CPUFREQ_MAX_PROFILE;
	}
	*cur_ddr = gCpufrqProfile[tmp].ddrvalue;
	return (s32)dfs_get_pro_mode(tmp);
}

#ifdef BSP_CONFIG_LPDDR2
void dfs_get_ddrc_timing(u32 new, T_CPUFREQ_DDRC_TIMING* ptiming)
{
    u32 ddr_value = gCpufrqProfile[new].ddrvalue;
	ptiming->nxttiming0 = cpufreq_ddr_train->TIMING[ddr_value].timing0;
	ptiming->nxttiming1 = cpufreq_ddr_train->TIMING[ddr_value].timing1;
	ptiming->nxttiming2 = cpufreq_ddr_train->TIMING[ddr_value].timing2;
	ptiming->nxttiming3 = cpufreq_ddr_train->TIMING[ddr_value].timing3;
	ptiming->nxttiming4 = cpufreq_ddr_train->TIMING[ddr_value].timing4;
	ptiming->nxttiming5 = cpufreq_ddr_train->TIMING[ddr_value].timing5;
	ptiming->nxttiming6 = cpufreq_ddr_train->TIMING[ddr_value].timing6;

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING0), 0, 31, ptiming->nxttiming0);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING1), 0, 31, ptiming->nxttiming1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING2), 0, 31, ptiming->nxttiming2);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING3), 0, 31, ptiming->nxttiming3);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING4), 0, 31, ptiming->nxttiming4);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING5), 0, 31, ptiming->nxttiming5);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING6), 0, 31, ptiming->nxttiming6);
}

void dfs_get_ddrc_timer(u32 new, T_CPUFREQ_DDRC_TIMER* ptimer)
{
    u32 ddr_value = gCpufrqProfile[new].ddrvalue;
	ptimer->dramtimer0 = cpufreq_ddr_train->TIMING[ddr_value].dramtimer0;
	ptimer->dramtimer1 = cpufreq_ddr_train->TIMING[ddr_value].dramtimer1;
	ptimer->dramtimer2 = cpufreq_ddr_train->TIMING[ddr_value].dramtimer2;
	ptimer->dramtimer3 = cpufreq_ddr_train->TIMING[ddr_value].dramtimer3;
	ptimer->dramtimer4 = cpufreq_ddr_train->TIMING[ddr_value].dramtimer4;
	ptimer->dramtimer5 = cpufreq_ddr_train->TIMING[ddr_value].dramtimer5;
	ptimer->misc       = cpufreq_ddr_train->TIMING[ddr_value].misc;
	ptimer->dmsel      = cpufreq_ddr_train->TIMING[ddr_value].dmsel;
	ptimer->ioctl3     = cpufreq_ddr_train->TIMING[ddr_value].ioctrl3;

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER0), 0, 31, ptimer->dramtimer0);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER1), 0, 31, ptimer->dramtimer1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER2), 0, 31, ptimer->dramtimer2);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER3), 0, 31, ptimer->dramtimer3);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER4), 0, 31, ptimer->dramtimer4);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER5), 0, 31, ptimer->dramtimer5);
}
#elif defined(BSP_CONFIG_LPDDR3)
void dfs_get_ddrc_timing(u32 fbus, u32 pll, T_CPUFREQ_DDRC_TIMING* ptiming)
{
	/* 667M */
	if(0 == pll)
	{
		switch(fbus)
		{
			case 1:/*333*/
				ptiming->nxttiming0 = 0xB54A180F;
				ptiming->nxttiming1 = 0x1272A047;
				ptiming->nxttiming2 = 0x6501204F;
				ptiming->nxttiming3 = 0xAF4A8245;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x12081008;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
#if 0
			case 3:
				ptiming->nxttiming0 = 0xB3290D08;
				ptiming->nxttiming1 = 0x662A017;
				ptiming->nxttiming2 = 0x4500A027;
				ptiming->nxttiming3 = 0xAF454145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080808;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 5:
				ptiming->nxttiming0 = 0xB318C906;
				ptiming->nxttiming1 = 0x462A010;
				ptiming->nxttiming2 = 0x4500901A;
				ptiming->nxttiming3 = 0xAF438145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080608;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 7:
				ptiming->nxttiming0 = 0xB318C805;
				ptiming->nxttiming1 = 0x362A00C;
				ptiming->nxttiming2 = 0x45009013;
				ptiming->nxttiming3 = 0xAF42A145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080608;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
#endif
			default:
				break;
		}
	}
	else if(1 == pll)/* 1066M */
	{
		switch(fbus)
		{
			case 1:/*533*/
				ptiming->nxttiming0 = 0xB77B6718;
				ptiming->nxttiming1 = 0x1D82A071;
				ptiming->nxttiming2 = 0x9501C07E;
				ptiming->nxttiming3 = 0xAF50C255;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x13181908;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
			case 3:/*266*/
				ptiming->nxttiming0 = 0xB441D50D;
				ptiming->nxttiming1 = 0xF72A039;
				ptiming->nxttiming2 = 0x5500F03F;
				ptiming->nxttiming3 = 0xAF486145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x12080D08;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
#if 0
			case 5:
				ptiming->nxttiming0 = 0xB3294E09;
				ptiming->nxttiming1 = 0x762A019;
				ptiming->nxttiming2 = 0x4500A02A;
				ptiming->nxttiming3 = 0xAF45A145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080908;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
#endif
			case 7:
				ptiming->nxttiming0 = 0xB3210B07;
				ptiming->nxttiming1 = 0x862A01D;
				ptiming->nxttiming2 = 0x4500901F;
				ptiming->nxttiming3 = 0xAF444145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080708;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
#if 0
			case 15:
				ptiming->nxttiming0 = 0xB318C704;
				ptiming->nxttiming1 = 0x362A00A;
				ptiming->nxttiming2 = 0x4500900F;
				ptiming->nxttiming3 = 0xAF422145;
				ptiming->nxttiming4 = 0x10B00000;
				ptiming->nxttiming5 = 0x11080608;
				ptiming->nxttiming6 = 0x44;
				ptiming->nxttiming7 = 0x0;
				break;
#endif
			default:
				break;
		}
	}
	else
	{
		printk("dfs_get_ddrc_timing err\n");
	}

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING0), 0, 31, ptiming->nxttiming0);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING1), 0, 31, ptiming->nxttiming1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING2), 0, 31, ptiming->nxttiming2);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING3), 0, 31, ptiming->nxttiming3);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING4), 0, 31, ptiming->nxttiming4);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING5), 0, 31, ptiming->nxttiming5);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING6), 0, 31, ptiming->nxttiming6);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_NXT_TIMING7), 0, 31, ptiming->nxttiming7);
}


void dfs_get_ddrc_timer(u32 fbus, u32 pll, T_CPUFREQ_DDRC_TIMER* ptimer)
{
	/* 400M */
	if(0 == pll)
	{
		switch(fbus)
		{
			case 1:
				ptimer->dramtimer0 = 0x354F4552;
				ptimer->dramtimer1 = 0x847246B;
				ptimer->dramtimer2 = 0x2006104B;
				ptimer->dramtimer3 = 0x80340D4E;
				ptimer->dramtimer4 = 0x300860F;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x18340605;
				ptimer->dmsel      = 0x1B504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#if 0
			case 3:
				ptimer->dramtimer0 = 0x1CC82352;
				ptimer->dramtimer1 = 0x624146B;
				ptimer->dramtimer2 = 0x20041026;
				ptimer->dramtimer3 = 0x8019F4A7;
				ptimer->dramtimer4 = 0x3008488;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 5:
				ptimer->dramtimer0 = 0x14C62252;
				ptimer->dramtimer1 = 0x619126B;
				ptimer->dramtimer2 = 0x2004101A;
				ptimer->dramtimer3 = 0x80115C70;
				ptimer->dramtimer4 = 0x3008406;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
			case 7:
				ptimer->dramtimer0 = 0x10C52252;
				ptimer->dramtimer1 = 0x613126B;
				ptimer->dramtimer2 = 0x20041014;
				ptimer->dramtimer3 = 0x800CFC54;
				ptimer->dramtimer4 = 0x3008385;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#endif
			default:
				break;
		}
	}
	else if(1 == pll)/* 666M */
	{
		switch(fbus)
		{
			case 1:
				ptimer->dramtimer0 = 0x51D87852;
				ptimer->dramtimer1 = 0xA71386B;
				ptimer->dramtimer2 = 0x20091477;
				ptimer->dramtimer3 = 0x80534E16;
				ptimer->dramtimer4 = 0x3008817;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x18340705;
				ptimer->dmsel      = 0x1B704A00;
				ptimer->ioctl3     = 0xC000;
				break;
			case 3:
				ptimer->dramtimer0 = 0x290D4452;
				ptimer->dramtimer1 = 0x8391E6B;
				ptimer->dramtimer2 = 0x2005103C;
				ptimer->dramtimer3 = 0x8029950B;
				ptimer->dramtimer4 = 0x300858C;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x18340605;
				ptimer->dmsel      = 0x1B504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#if 0
			case 5:
				ptimer->dramtimer0 = 0x1CC93352;
				ptimer->dramtimer1 = 0x627146B;
				ptimer->dramtimer2 = 0x20041028;
				ptimer->dramtimer3 = 0x801BACB2;
				ptimer->dramtimer4 = 0x3008489;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#endif
			case 7:
				ptimer->dramtimer0 = 0x18C72252;
				ptimer->dramtimer1 = 0x61D126B;
				ptimer->dramtimer2 = 0x2004101F;
				ptimer->dramtimer3 = 0x8014CC86;
				ptimer->dramtimer4 = 0x3008407;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x18340605;
				ptimer->dmsel      = 0x1B504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#if 0
			case 15:
				ptimer->dramtimer0 = 0x10C42252;
				ptimer->dramtimer1 = 0x60F126B;
				ptimer->dramtimer2 = 0x20041010;
				ptimer->dramtimer3 = 0x800A5443;
				ptimer->dramtimer4 = 0x3008384;
				ptimer->dramtimer5 = 0x4;
				ptimer->misc       = 0x20440605;
				ptimer->dmsel      = 0x24504A00;
				ptimer->ioctl3     = 0x800C000;
				break;
#endif
			default:
				break;
		}
	}
	else
	{
		printk("dfs_get_ddrc_timer err\n");
	}

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER0), 0, 31, ptimer->dramtimer0);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER1), 0, 31, ptimer->dramtimer1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER2), 0, 31, ptimer->dramtimer2);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER3), 0, 31, ptimer->dramtimer3);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER4), 0, 31, ptimer->dramtimer4);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DRAMTIMER5), 0, 31, ptimer->dramtimer5);
}
#endif

#ifdef CONFIG_AMON_FOR_BUS_LOCK
void amon_init_dfs(void)
{
    u32 reg_val;
    
    /*  使用 pmu 寄存器作为标志位， 默认0表示打开 amon监控
        手动修改为1 再复位，则功能关闭 */
    if(readl(0x9001a000+0x40C)==1)
        return;
    
    /* SOC monitor开钟 */
    writel ( 0x18       , 0x90000000 );
    /* 清中断 */
    writel ( 0xFFFFFFFF , 0x96000020 );
    /* 端口配置 */
    writel ( 0x249B1A   , 0x9600001C );
    writel ( 0x40000000 , 0x96000100 );
    writel ( 0x3BF      , 0x960000b0 );
    writel ( 0x90000000 , 0x96000104 );
    writel ( 0x90FFFFFF , 0x96000108 );
    writel ( 0x40000000 , 0x96000200 );
    writel ( 0x3BF      , 0x960000b4 );
    writel ( 0x90000000 , 0x96000204 );
    writel ( 0x90FFFFFF , 0x96000208 );
    writel ( 0x40000000 , 0x96000300 );
    writel ( 0x3BF      , 0x960000b8 );
    writel ( 0x90000000 , 0x96000304 );
    writel ( 0x90FFFFFF , 0x96000308 );
    writel ( 0x40000000 , 0x96000400 );
    writel ( 0x3BF      , 0x960000bC );
    writel ( 0x90000000 , 0x96000404 );
    writel ( 0x90FFFFFF , 0x96000408 );
    writel ( 0x40000000 , 0x96000500 );
    writel ( 0x3BF      , 0x960000C0 );
    writel ( 0x10020000 , 0x96000504 );
    writel ( 0x8FFFFFFF , 0x96000508 );
    writel ( 0x40000000 , 0x96000600 );
    writel ( 0x3BF      , 0x960000C4 );
    writel ( 0x91000000 , 0x96000604 );
    writel ( 0xFFFFFFFF , 0x96000608 );
    writel ( 0x40000000 , 0x96000700 );
    writel ( 0x0        , 0x960000C8 );
    writel ( 0x10020000 , 0x96000704 );
    writel ( 0x8FFFFFFF , 0x96000708 );
    writel ( 0x40000000 , 0x96000800 );
    writel ( 0x0        , 0x960000CC );
    writel ( 0x91000000 , 0x96000804 );
    writel ( 0xFFFFFFFF , 0x96000808 );
    /* reset */
    writel ( 0x2        , 0x96000000 );
    /* wait (0x96000008 bit[4] = 1） */
    do{
        reg_val = readl(0x96000008);
        }while( ((reg_val>>4)&1) != 1 );
    writel ( 0x20000000 , 0x90000060 );
    writel ( 0x20000000 , 0x90000064 );

    /* modem monitor 开钟 */
    writel ( 0x400000   , 0x80200000 );
    /* 清中断 */
    writel ( 0xFFFFFFFF , 0x80458020 );
    /* 端口配置 */
    writel ( 0x1A2D1    , 0x8045801C );
    writel ( 0x40000000 , 0x80458100 );
    writel ( 0x3BF      , 0x804580b0 );
    writel ( 0x90000000 , 0x80458104 );
    writel ( 0x90FFFFFF , 0x80458108 );
    writel ( 0x40000000 , 0x80458200 );
    writel ( 0x3BF      , 0x804580b4 );
    writel ( 0x90000000 , 0x80458204 );
    writel ( 0x90FFFFFF , 0x80458208 );
    writel ( 0x40000000 , 0x80458300 );
    writel ( 0x3BF      , 0x804580b8 );
    writel ( 0x90000000 , 0x80458304 );
    writel ( 0x90FFFFFF , 0x80458308 );
    writel ( 0x40000000 , 0x80458400 );
    writel ( 0x0        , 0x804580bc );
    writel ( 0x90000000 , 0x80458404 );
    writel ( 0x90FFFFFF , 0x80458408 );
    writel ( 0x40000000 , 0x80458500 );
    writel ( 0x0        , 0x804580C0 );
    writel ( 0x90000000 , 0x80458504 );
    writel ( 0x90FFFFFF , 0x80458508 );
    writel ( 0x40000000 , 0x80458600 );
    writel ( 0x0        , 0x804580C4 );
    writel ( 0x90000000 , 0x80458604 );
    writel ( 0x90FFFFFF , 0x80458608 );
    /* reset */
    writel ( 0x2        , 0x80458000 );
    /* wait (0x80458008 bit[4] = 1） */
    do{
        reg_val = readl(0x80458008);
        }while( ((reg_val>>4)&1) != 1 );
    writel ( 0x20000000 , 0x80200020 );
    writel ( 0x20000000 , 0x80200024 );
}
void amon_open(void)
{
    u32 ret = 0;
    /*  使用 pmu 寄存器作为标志位， 默认0表示打开 amon监控
        手动修改为1 再复位，则功能关闭 */
    if(readl(0x9001a000+0x40C)==1)
        return;
    
    /*  soc_amon spy on m3-> [xxx~0x8fffffff]
        open mdm_amon before soc_amon opened */
    ret = readl(0x8020040C);
    ret |= 0x400;
    writel ( ret      , 0x8020040C );
    ret = readl(0x90000800);
    ret |= 0x400;
    writel ( ret      , 0x90000800 );
}
void amon_close(void)
{
    u32 ret = 0;
    /*  使用 pmu 寄存器作为标志位， 默认0表示打开 amon监控
        手动修改为1 再复位，则功能关闭 */
    if(readl(0x9001a000+0x40C)==1)
        return;

    /*  soc_amon spy on m3-> [xxx~0x8fffffff]
        close soc_amon before mdm_amon closed */
    ret = readl(0x90000800);
    ret &= 0xFFFFFBFF;
    writel ( ret        , 0x90000800 );
    ret = readl(0x8020040C);
    ret &= 0xFFFFFBFF;
    writel ( ret        , 0x8020040C );
}
struct amon_int_record
{
    u32 soc_amon_int;
    u32 modem_amon_int;
};
#define AMON_INT_NUM 10
struct amon_int_record amon_int_records[AMON_INT_NUM];
u32 amon_int_index = 0;

/* 中断查询时访问 mdm_amon，需要先关闭监控再读 */
void amon_check_int(void)
{
/*查看中断
中断寄存器：0x96000024 bit[15]~ bit[0]
中断寄存器：0x80458024 bit[11]~ bit[0]*/
    u32 soc_check,modem_check;

    /*  使用 pmu 寄存器作为标志位， 默认0表示打开 amon监控
        手动修改为1 再复位，则功能关闭 */
    if(readl(0x9001a000+0x40C)==1)
        return;

    soc_check = readl(0x96000024);
    modem_check = readl(0x80458024);

    if(((soc_check&0xFFFF)||(modem_check&0xFFF))&&(amon_int_index!=10))
    {
        amon_int_records[amon_int_index].soc_amon_int   = soc_check;
        amon_int_records[amon_int_index].modem_amon_int = modem_check;
        amon_int_index++;

        
        /*  使用 pmu 寄存器作为标志位， 默认0:监控到就停 */
        if(readl(0x9001a000 + 0x408)==0)
            __asm__ __volatile__ ("b .");
        
        /* 清中断 */
        writel ( 0xFFFFFFFF , 0x96000020 );
        writel ( 0xFFFFFFFF , 0x80458020 );
    }
}
#else

static inline void amon_open(void){}
static inline void amon_close(void){}
static inline void amon_check_int(void){}

#endif

void dfs_ddrc_config(u32 newpro)
{
	u32 n = 0;
	u32 m = 0;
	s32 ddrvalue = 0;
	ddrvalue = gCpufrqProfile[newpro].ddrvalue;
	if (dfs_get_pro_mode(newpro))
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL0), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL1), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL1);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL2), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL2);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL3), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL3);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL4), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ACADDRBDL4);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ADDRPHBOUND), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_ADDRPHBOUND);
		for (n = 0; n < 4; n++)
		{
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL0 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQNBDL0[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL1 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQNBDL1[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL2 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQNBDL2[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQNBDL0 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQNBDL0[0][n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQNBDL1 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQNBDL1[0][n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNOEBDL	+ n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNOEBDL[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQSDLY  + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQSDLY[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQDLY   + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWDQDLY[n]);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWLSL	 + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNWLSL[n]);
		}
	}
	else
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL0), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL1), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL2), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL3), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ACADDRBDL4), 0, 31, 0);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_ADDRPHBOUND), 0, 31, 0xC0000);
		for (n = 0; n < 4; n++)
		{
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL0 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL1 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQNBDL2 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQNBDL0 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQNBDL1 + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNOEBDL	+ n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQSDLY  + n * 0x80), 0, 31, 0);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWDQDLY   + n * 0x80), 0, 31, 0xC00);
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNWLSL	 + n * 0x80), 0, 31, 0x10000);
		}
	}
	for (n = 0; n < 4; n++)
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQSDLY + n * 0x80), 0, 31, 
								cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSDLY[n]);
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNGDS	 + n * 0x80), 0, 31, 
							cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNGDS[n]);
		for (m = 0; m < 2; m++)
		{
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQSGDLY + n * 0x80 + m * 0x400), 0, 6, 
								(cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSGDLY[m][n] & 0x7F));
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQSGDLY + n * 0x80 + m * 0x400), 9, 14, 
								((cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSGDLY[m][n] & 0x7E00) >> 9));
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DXNRDQSGDLY + n * 0x80 + m * 0x400), 16, 22, 
								((cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSGDLY[m][n] & 0x7F0000) >> 16));
		}
	}
}
void cpufreq_timer_init(void)
{
	u32 ret = 0;
	ret = readl(0x2001E000+0x8);/*ctrl base*/
	writel(ret|0x2,0x2001E000+0x8);/*32 BIT CNT*/
	writel(0xFFFFFFFF,0x2001E000+0X0);/*load init value*/
	ret = readl(0x2001E000+0x8);/*ctrl base*/
	writel(ret|0x82,0x2001E000+0x8);/*32 BIT CNT,start to run*/
}
void cpufreq_udelay(u32 delay_us)
{
	u64 delta = 0;
	u32 begin = 0,end = 0;
	delta = (u64)delay_us*(192/10);
	begin = readl(0x2001E000+0x4);
	do{
		end = readl(0x2001E000+0x4);
	}while(get_timer_slice_delta(end,begin)<(u32)delta);
}

void m3_start_cti(void)
{
	u32 ccore_is_wake = 0;
	u32 acore_is_wake = 0;
	ccore_is_wake = pm_is_wake_lock(PM_PWR_VOTE_CCORE);
	acore_is_wake = pm_is_wake_lock(PM_PWR_VOTE_ACORE);
	//uclock
	cpufreq_cti_unlock(CPUFREQ_CTI_BASE);

	if (acore_is_wake)
	{
	    cpufreq_cti_unlock(CPUFREQ_CTI_BASE_APP);
		cpufreq_cti_unlock(CPUFREQ_DBG_BASE_APP);
		if(0x1 == (readl(CPUFREQ_DBG_BASE_APP + 0x88) & 0x1))
		{
			writel(0x0, CPUFREQ_CTI_BASE_APP + 0xA0);
			writel(0x0, CPUFREQ_CTI_BASE_APP + 0xBC);
			ddr_refrest_ctrl.acore_cti_is_debug_stat = 1;
		}
		else
		{
			writel(0x1, CPUFREQ_CTI_BASE_APP + 0xA0);
			writel(0x2, CPUFREQ_CTI_BASE_APP + 0xBC);
			ddr_refrest_ctrl.acore_cti_is_debug_stat = 0;
		}
	}
	if (ccore_is_wake)
	{
	    cpufreq_cti_unlock(CPUFREQ_CTI_BASE_MDM);
		cpufreq_cti_unlock(CPUFREQ_DBG_BASE_MDM);
		if(0x1 == (readl(CPUFREQ_DBG_BASE_MDM + 0x88) & 0x1))
		{
			writel(0x0, CPUFREQ_CTI_BASE_MDM + 0xA0);
			writel(0x0, CPUFREQ_CTI_BASE_MDM + 0xBC);
			ddr_refrest_ctrl.ccore_cti_is_debug_stat = 1;
		}
		else
		{
			writel(0x1, CPUFREQ_CTI_BASE_MDM + 0xA0);
			writel(0x2, CPUFREQ_CTI_BASE_MDM + 0xBC);
			ddr_refrest_ctrl.ccore_cti_is_debug_stat = 0;
		}
	}
	writel(0x1, CPUFREQ_CTI_BASE + 0x14);
	if (acore_is_wake && (!ddr_refrest_ctrl.acore_cti_is_debug_stat))
	{
		do
		{
			;
		}while(0x0 == (readl(CPUFREQ_DBG_BASE_APP + 0x88) & 0x1));
	}
	if (ccore_is_wake && (!ddr_refrest_ctrl.ccore_cti_is_debug_stat))
	{
		do
		{
			;
		}while(0x0 == (readl(CPUFREQ_DBG_BASE_MDM + 0x88) & 0x1));
	}
	writel(0x1, CPUFREQ_CTI_BASE + 0x18);
	if (ccore_is_wake)
	{
		writel(0x1, CPUFREQ_CTI_BASE_MDM + 0x10);
	}
	if (acore_is_wake)
	{
		writel(0x1, CPUFREQ_CTI_BASE_APP + 0x10);
	}
}
void m3_stop_cti(void)
{
	u32 ccore_is_wake = 0;
	u32 acore_is_wake = 0;
	ccore_is_wake = pm_is_wake_lock(PM_PWR_VOTE_CCORE);
	acore_is_wake = pm_is_wake_lock(PM_PWR_VOTE_ACORE);
	writel(0x2, CPUFREQ_CTI_BASE + 0x14);
	if ((acore_is_wake) && (!ddr_refrest_ctrl.acore_cti_is_debug_stat))
	{
		while(0x1 == (readl(CPUFREQ_DBG_BASE_APP + 0x88) & 0x1))
		{
			;
		}
	}
	if ((ccore_is_wake) && (!ddr_refrest_ctrl.ccore_cti_is_debug_stat))
	{
		while(0x1 == (readl(CPUFREQ_DBG_BASE_MDM + 0x88) & 0x1))
		{
			;
		}
	}
	writel(0x2, CPUFREQ_CTI_BASE + 0x18);
	//lock
	cpufreq_cti_lock(CPUFREQ_CTI_BASE);
	if (ccore_is_wake)
	{
		cpufreq_cti_lock(CPUFREQ_CTI_BASE_MDM);
		cpufreq_cti_lock(CPUFREQ_DBG_BASE_MDM);
	}
	if (acore_is_wake)
	{
		cpufreq_cti_lock(CPUFREQ_CTI_BASE_APP);
		cpufreq_cti_lock(CPUFREQ_DBG_BASE_APP);
	}
}
static void dfs_stamp_init(void)
{
	u32 n = 0;
	for (n = 0; n < DFS_CHIP_FLOW_STAMP_NUM; n++)
	{
		cpufreq_ddr_train->dfs_chip_flow_stamp[n] = 0;
	}
	cpufreq_ddr_train->dfs_chip_flow_stamp[DFS_CHIP_FLOW_STAMP_NUM - 1] = 0xdfdfdfdf;
}
static void dfs_stamp(u32 stamp_num)
{
	if (stamp_num < DFS_CHIP_FLOW_STAMP_NUM)
		cpufreq_ddr_train->dfs_chip_flow_stamp[stamp_num] = stamp_num;
}

void dfs_config_reg(u32 cur, u32 new)
{
    s32 ret = 0;
	u32 tmp = 0;
	u32 n = 0;
	u32 curfbus = 0;
	u32 newfbus = 0;
	u32 curpll = 0;
	u32 newpll = 0;
	u32 pll_ctrl = 0;
	u32 ddrvalue = 0;
	u32 rdqsbdl = 0;
	u32 ddrcnochange = 0;
	T_CPUFREQ_DDRC_TIMER timer = {0};
	T_CPUFREQ_DDRC_TIMING timing = {0};

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
			goto step17;
		}
	}
	ddr_refrest_ctrl.ipc_sem_flag = 0;
	ret = bsp_ipc_spin_lock(IPC_SEM_DFS_FIX);
	if (OK != ret)
	{
	    ddr_refrest_ctrl.ipc_sem_flag = 1;
	}

	dfs_stamp_init();
	if (0 == ddr_refrest_ctrl.mcore_ddr_option)
	{
		m3_start_cti();
        amon_open();
	}

	dfs_stamp(0);
	/* 2 禁止PHY的动态跟踪功能*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_RETCTRL0), 13, 13, 0);
    /* coverity[check_return] */
	/*3 选择即将写入的影子寄存器*/
	tmp = osl_reg_get_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_REGBANKCTRL), 0, 0);
    /* coverity[unchecked_value] */
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_REGBANKCTRL), 0, 0, ((~tmp) & 0x1));

	/* 4 禁止 PACK  auto  clk  gate*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_LPCTRL), 31, 31, 0);

	/* 5 配置HIPACK的影子寄存器*/
	dfs_get_ddrc_timer(new, &timer);

	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_MISC), 0, 31, timer.misc);
	/*load ddr初始化频点值, fbus大于400M 为mission,其他为bypass*/
	dfs_ddrc_config(new);
	
	/* 6 使能 PACK  auto  clk  gate*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_LPCTRL), 31, 31, 1);

	/* 7 配置DMC的NEXT时序参数寄存器*/
	dfs_get_ddrc_timing(new, &timing);

	/* 8 */
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CFG_SREF), 8, 8, 1);

	/* 9 复位DMC的自刷新状态*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CTRL_SREF), 1, 1, 0);

	/* 10 系统控制（cycreq）DMC进入自刷新*/
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_SC_PERI_CTRL4), 2, 2, 0);

	/* 11 查询系统寄存器，确认DMC是否控制器件进入了自刷新*/
	do{
		tmp = osl_reg_get_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_SC_PERI_STAT30), 1, 1);
	}while(tmp);
	dfs_stamp(1);
	/* coverity[check_return] */
	/* 12 切换PACK工作时所选择的寄存器*/
	tmp = osl_reg_get_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_REGBANKCTRL), 1, 1);
	/* coverity[unchecked_value] */
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_REGBANKCTRL), 1, 1, ((~tmp) & 0x1));

	/* 13 配置PHY更新DLY_LINE*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_MISC), 19, 19, 1);
    cpufreq_udelay(1);
	/* 14 PHY的DLY_LANE交由PACK动态控制*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_MISC), 19, 19, 0);

	/* 15 手动关闭phy的时钟*/
	tmp = osl_reg_get_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYCLKGATED), 0, 31);
	tmp |= 0x80000000;
	tmp &= 0xffffa0f0;
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYCLKGATED), 0, 31, tmp);

	/*配置swap/passthrough相关*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_DMSEL), 0, 31, timer.dmsel);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_IOCTL3), 0, 31, timer.ioctl3);
	/* 当目标频点是在bypass模式下时,需要根据目标频点配置合适的值 fbus大于400M 为mission,其他为bypass*/
	/*配置swap/passthrough相关*/
	if (!(dfs_get_pro_mode(new)))
	{
		ddrvalue = (u32)gCpufrqProfile[new].ddrvalue;
		rdqsbdl = cpufreq_ddr_train->TRAINING[ddrvalue].ddr_reg_DXNRDQSDLY[0] & 0x1FF;
		tmp = (rdqsbdl > 255) ? 255 : rdqsbdl;
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PHY_ACDX_BASE_ADDR + CPUFREQ_ACPHYCTL0), 8, 16, tmp);
		for (n =0; n < 4; n++)
		{
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PHY_ACDX_BASE_ADDR + CPUFREQ_DXNDCC + n * 0x80), 12, 20, tmp);
		}
	}
	/*判断目标频率是否为mission模式*/
	if ((dfs_get_pro_mode(cur)) && (!(dfs_get_pro_mode(new))))
	{
		/*从mission模式切换到bypass模式后，需要禁止PHY内部对bypass时钟的门控 */
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PHY_ACDX_BASE_ADDR + CPUFREQ_ACPHYCTL0), 7, 7, 1);
		for (n = 0; n < 4; n++)
		{
			osl_reg_set_bit((void *)(CPUFREQ_DDRC_PHY_ACDX_BASE_ADDR + CPUFREQ_DXNMISCCTRL2 + n * 0x80), 27, 27, 1);
		}
	}
	/* 从bypass模式切换到mission模式后，可以打开PHY内部对bypass的时钟门控 */
	if ((!(dfs_get_pro_mode(cur))) && (dfs_get_pro_mode(new)))
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PHY_ACDX_BASE_ADDR + CPUFREQ_ACPHYCTL0), 7, 7, 0);
		for (n = 0; n < 4; n++)
		{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PHY_ACDX_BASE_ADDR + CPUFREQ_DXNMISCCTRL2 + n * 0x80), 27, 27, 0);
		}
	}

	/* 16  关掉phy的pll*/
	if ((dfs_get_pro_mode(cur)) && (!(dfs_get_pro_mode(new))))
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PLLCTRL), 0, 2, 0x7);
	}
	dfs_stamp(2);
	/* 17 系统控制完成时钟无毛刺切换，为控制器提供一个新的稳定频率*/
step17:	
	if(curpll == newpll)
	{
		osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_PD_CRG_CLKDIV2), 0, 31, gCpufrqProfile[new].clkdiv);
		goto step18;
	}
	/* 打开PERIPLL输入参考时钟*/
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_PD_CRG_CLKEN4), 0, 3, 0x8);

	/* A9输入参考时钟源选择PERI PLL */
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_PD_CRG_CLK_SEL2), 0, 3, 0x8);

	/* 记录下读出的pll_ctrl值，切频完成后再配置回去*/
	pll_ctrl = osl_reg_get_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL3), 8, 8);

	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL3), 8, 8, 0x1);
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL3), 0, 0, 0x1);

	/*gCpufrqPll值需要重新配置*/
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL1), 0, 31, gCpufrqPll[newpll].dfs1ctrl1);
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL2), 0, 31, gCpufrqPll[newpll].dfs1ctrl2);

	tmp = osl_reg_get_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL3), 0, 31);
	tmp &= 0xfffffffe;
	tmp |= 0x28;
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL3), 0, 31, tmp);
	do
	{
		tmp = osl_reg_get_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL3), 31, 31);
	}while(!tmp);
	
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_PD_CRG_CLKDIV2), 0, 31, gCpufrqProfile[new].clkdiv);

	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_PD_CRG_CLK_SEL2), 0, 3, 0x1);

	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_CRG_DFS1_CTRL3), 8, 8, (pll_ctrl & 0x1));

	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_PD_CRG_CLKDIS4), 0, 3, 0x8);
	dfs_stamp(3);
step18:
	if (ddrcnochange)
	{
		return;
	}
	/* 18 系统控制的bypass与mission之间的模式切换*/
	if ((dfs_get_pro_mode(new)) != (dfs_get_pro_mode(cur)))
	{
		tmp = (!(dfs_get_pro_mode(new)))? 1 : 0;
		osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_SC_TOP_CTRL21), 0, 0, tmp);
	}
	
	tmp = (!(dfs_get_pro_mode(new)))? 0 : 1;
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + 0xdc), 29, 29, tmp);
	dfs_stamp(4);
	/* 19 power up  phy  pll*/
	if ((dfs_get_pro_mode(new)))
	{
		osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PLLCTRL), 0, 2, 0);
	}
	/* 20 等待20us左右*/
	if ((dfs_get_pro_mode(new)))
	{
		cpufreq_udelay(20);
		do
		{
			tmp = osl_reg_get_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYPLLCTRL_AC), 31, 31); 
		}while(!tmp);
		do
		{
			tmp = osl_reg_get_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYPLLCTRL_DX), 28, 31); 
		}while(0xf != tmp);
	}
	dfs_stamp(5);
	/* 21 */
	tmp = osl_reg_get_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYCLKGATED), 0, 31);
	tmp |= 0x8000430f;
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYCLKGATED), 0, 31, tmp);

	/* 22 时钟门控交由硬件自动控制*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYCLKGATED), 31, 31, 0);
	
	/* 23 delay_line更新后在重新开始访问之前需要reset PHY里面的计数器*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYINITCTRL), 15, 15, 1);
    cpufreq_udelay(1);
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_PHYINITCTRL), 15, 15, 0);
	dfs_stamp(6);
	/* 24 系统撤销控制DMC进入自刷新的请求*/
	osl_reg_set_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_SC_PERI_CTRL4), 2, 2, 1);

	/* 25 查询系统寄存器，确认DMC已退出自刷新*/
	do{
		tmp = osl_reg_get_bit((void *)(CPUFREQ_SC_BASE_ADDR + CPUFREQ_SC_PERI_STAT30), 1, 1);
	}while(!tmp);

	/* 26 配置DMC解反压*/
	osl_reg_set_bit((void *)(CPUFREQ_DDRC_DMC_BASE_ADDR + CPUFREQ_DDRC_CTRL_SREF), 1, 1, 1);
	
	/* 28 恢复PHY的动态跟踪功能*/
    if(dfs_get_pro_mode(new) == mission_mode){
	    osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_RETCTRL0), 13, 13, 1);
    }else{
	    osl_reg_set_bit((void *)(CPUFREQ_DDRC_PACK_BASE_ADDR + CPUFREQ_RETCTRL0), 13, 13, 0);
    }
	dfs_stamp(7);

	if (0 == ddr_refrest_ctrl.mcore_ddr_option)
	{
	    amon_close();
        amon_check_int();
		m3_stop_cti();
    }
    ret = bsp_ipc_spin_unlock(IPC_SEM_DFS_FIX);
    if (OK != ret)
    {
        ddr_refrest_ctrl.ipc_sem_flag = 2;
    }
    ddr_refrest_ctrl.ipc_sem_flag = 3;
}
void dfs_ddrc_calc(void)
{
	cpufreq_timer_init();
	cpufreq_ddr_train = (TCM_DFS_TRAINING *)DFS_DDR_TRAINING_DATA_ADDR;
}

