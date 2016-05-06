/*
 *  Copyright (C), 2011-2013, Hisilicon Technologies Co., Ltd. 
 *
 * File name     : boosting.c
 * Author        : 
 * Created       : 2013-01-16
 * Last Modified : 
 * Description   :  
 * Modification  : Create file 
 *
 */

#include <hi_syscrg.h>
#include <hi_syssc.h>
#include <soc_memmap.h>
#include "product_config.h"
#include <osl_types.h>
#include <osl_bio.h>
#include <bsp_sram.h>
#include <bsp_pmu.h>
#include <m3_dump.h>

extern void print_info(const char *buffer);

extern int chip_tem_get(void);
extern int bsp_pmu_volt_set(int volt_id,int voltage_mv);

const u16 hpm_hvt_25[17]  = {1110, 1100, 1090, 1090, 1080, 1070, 1070, 1060, 1050, 
	                         1050, 1040, 1040, 1030, 1030, 1030, 1030, 1030};
const u16 hpm_svt_25[17]  = {870,  870,  860,  860,  850,  850,  850,  840, 840, 
	                         830,  830,  830,  830,  820,  820,  820,  820};

const u16 hpm_hvt_50[17]  = {1210, 1200, 1180, 1170, 1160, 1150, 1140, 1130, 1120, 
	                         1120, 1110, 1100, 1090, 1090, 1090, 1080, 1080};
const u16 hpm_svt_50[17]  = {930,  920,  910,  900,  900,  900,  890,  880, 880,
	                         870,  870,  870,  860,  860,  850,  850,  850};

s32 boosting(void)
{
    u32 hpm_hvt_opc,hpm_uhvt_opc,hpm_svt_opc;
    u32 tmp,tmp1;
	u8  i,n = 0;
	s32 temperature = 0;
	s32 curr_temp = 0;
	volatile u32 loop_count = 0;	
	struct hpm_tem_print *hpm_temp_print_ptr = ((struct hpm_tem_print * )DUMP_M3_BOOST_ADDR);

	/*  enable HPM clk  CLKEN2-bit25 */
    writel((0x1 << 25),(HI_SYSSC_BASE_ADDR + HI_CRG_CLKEN2_OFFSET));

	writel(0x000A0A0A,(HI_SYSSC_BASE_ADDR + HI_SC_CTRL17_OFFSET));
	writel(0x00003000,(HI_SYSSC_BASE_ADDR + HI_CRG_SRSTEN1_OFFSET));
	writel(0x00003000,(HI_SYSSC_BASE_ADDR + HI_CRG_SRSTDIS1_OFFSET));
	
    /* 16 enable HPM */
    writel( 0x008A8A8A, (HI_SYSSC_BASE_ADDR+HI_SC_CTRL17_OFFSET));
    /* 17 wait HPM valid  sc_stat3[10]&sc_stat3[22]&sc_stat4[10] -> 1 */
	while(!((readl(HI_SYSSC_BASE_ADDR+HI_SC_STAT3_OFFSET) & 0x400400) == 0x400400))
	{};
	while(!((readl(HI_SYSSC_BASE_ADDR+HI_SC_STAT4_OFFSET) & 0x400) == 0x400))
	{};
    /* 18 get sc_stat3/sc_stat4 hpm0/hpm1/hpm2 opc */
    /* read opc twice, use the value of the second time */
    tmp = readl(HI_SYSSC_BASE_ADDR + HI_SC_STAT3_OFFSET);
    tmp = readl(HI_SYSSC_BASE_ADDR + HI_SC_STAT4_OFFSET);
    
    tmp = readl(HI_SYSSC_BASE_ADDR + HI_SC_STAT3_OFFSET);
    hpm_hvt_opc = (tmp >> 0) & (0x3FF);
    hpm_uhvt_opc = (tmp >> 12) & (0x3FF);
    tmp = readl(HI_SYSSC_BASE_ADDR + HI_SC_STAT4_OFFSET);
    hpm_svt_opc = (tmp >> 0) & (0x3FF);

	hpm_temp_print_ptr->hpm_hvt_opc  = hpm_hvt_opc;
	hpm_temp_print_ptr->hpm_uhvt_opc = hpm_uhvt_opc;
	hpm_temp_print_ptr->hpm_svt_opc  = hpm_svt_opc;
	hpm_temp_print_ptr->up_volt      = 0;
	hpm_temp_print_ptr->temperature  = 0x7fffffff;

    /* 19 disable HPM */
    writel(0x000A0A0A,(HI_SYSSC_BASE_ADDR + HI_SC_CTRL17_OFFSET));
	
    /* 20 disable HPM clk  CLKDIS2-bit25 */
    writel((0x1 << 25),(HI_SYSSC_BASE_ADDR + HI_CRG_CLKDIS2_OFFSET));

    /* 21 / 22 / 23 Ttenseor wait for 1ms(1.5ms) read Ttensor */
    /* only Tsensor 0 is ok, 1&2 unuseable*/
	tsensor_init();

	for(i = 0; i<5 ; i++)
	{
		/* waiting 1.5ms */
		loop_count = 100000; 
		while(loop_count)
		{
			loop_count--;
		}

		curr_temp = chip_tem_get();
		if(curr_temp < 1300 && curr_temp > -300)
		{
			temperature += curr_temp;
			n++;
		}	
		
	}

	/* 5次温度采集均无效，温度无效设置为初始值 */
	if (n == 0)
	{
		return ; /* fail to read temprature*/
	}

	temperature = temperature / (10 * n);

	hpm_temp_print_ptr->temperature = temperature;

	if (hpm_hvt_opc > hpm_svt_opc)
	{
		return ; /* hpm value overflow */
	}
	
    /* 24 boosting according to Tsensor & hpm_opc*/
	n = (temperature % 10) ? (temperature + 50)/10 : (temperature + 40)/10;
	n = (temperature < -40) ? 0 : n;
	n = (temperature > 120) ? 16: n;

#if defined(CONFIG_PMIC_HI6551)
	if(((1000*10*10000/150)/hpm_hvt_opc > hpm_hvt_50[n]) || ((1000*10*10000/150)/hpm_svt_opc > hpm_svt_50[n]))
	{
		/*buck3 volt up 48mV,ldo3 volt up 50mV*/
		hpm_temp_print_ptr->up_volt = 48;
		bsp_pmu_volt_set(PMIC_HI6551_BUCK3,948);
		bsp_pmu_volt_set(PMIC_HI6551_LDO03,950);
	}
	else if(((1000*10*10000/150)/hpm_hvt_opc > hpm_hvt_25[n]) || ((1000*10*10000/150)/hpm_svt_opc > hpm_svt_25[n]))
	{
		/*buck3 volt up 24mV,ldo3 volt up 25mV*/
		hpm_temp_print_ptr->up_volt = 24;
		bsp_pmu_volt_set(PMIC_HI6551_BUCK3,924);
		bsp_pmu_volt_set(PMIC_HI6551_LDO03,925);
	}
#endif
#if defined(CONFIG_PMIC_HI6559)
        if(((1000*10*10000/150)/hpm_hvt_opc > hpm_hvt_50[n]) || ((1000*10*10000/150)/hpm_svt_opc > hpm_svt_50[n]))
        {
            /*buck3 volt up 48mV,ldo3 volt up 50mV*/
            hpm_temp_print_ptr->up_volt = 48;
            bsp_pmu_volt_set(PMIC_HI6559_BUCK3,948);
            bsp_pmu_volt_set(PMIC_HI6559_LDO03,950);
        }
        else if(((1000*10*10000/150)/hpm_hvt_opc > hpm_hvt_25[n]) || ((1000*10*10000/150)/hpm_svt_opc > hpm_svt_25[n]))
        {
            /*buck3 volt up 24mV,ldo3 volt up 25mV*/
            hpm_temp_print_ptr->up_volt = 24;
            bsp_pmu_volt_set(PMIC_HI6559_BUCK3,924);
            bsp_pmu_volt_set(PMIC_HI6559_LDO03,925);
        }
#endif

	return loop_count;
}


static void calc_ddrc_dfs(void)
{
    unsigned tmp = 0;
    SRAM_SMALL_SECTIONS * sram_mem = ((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS));
    
    sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_freq = 166;/**/
    sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_freq = 333;/**/
    
	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0x83c);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_83c = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_83c = tmp>>1;

	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0xabc);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_abc = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_abc = ((tmp & 0xff) >> 1) | (((tmp & 0xff00)>>9)<<8) | (((tmp & 0xff0000)>>17)<<16);

	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0xb3c);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_b3c = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_b3c = ((tmp & 0xff) >> 1) | (((tmp & 0xff00)>>9)<<8) | (((tmp & 0xff0000)>>17)<<16);

	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0xbbc);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_bbc = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_bbc = ((tmp & 0xff) >> 1) | (((tmp & 0xff00)>>9)<<8) | (((tmp & 0xff0000)>>17)<<16);
	
	tmp = readl(HI_MDDRC_REGBASE_ADDR + 0xc3c);
	sram_mem->SRAM_DFS_DDRC_CFG[0].ddr_reg_c3c = tmp;
	sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_c3c = ((tmp & 0xff) >> 1) | (((tmp & 0xff00)>>9)<<8) | (((tmp & 0xff0000)>>17)<<16);

}


#define CM3_LP_PWRCTRL0      (0xE0044020)
#define CM3_DDRC_BASE_ADDR   (0xE0046000)
#define CM3_CRG_BASE_ADDR     0xE0045000
void dfs_to_max(void)
{
	u32 tmp = 0;
    u32 times = 0;
    SRAM_SMALL_SECTIONS * sram_mem = ((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR+SRAM_OFFSET_SMALL_SECTIONS));

    calc_ddrc_dfs();
    
	/* 1 */
	tmp = readl(CM3_LP_PWRCTRL0);
	tmp |= 0xFF000000;
	writel(tmp, CM3_LP_PWRCTRL0);

	/* 3  config DDRC freq to maximal: 333MHZ*/
	/*dfs_get_ddrc_timing(1, 1, &timing);
				ptiming->nxttiming0 = 0x5498170e;
				ptiming->nxttiming1 = 0x18a7462c;
				ptiming->nxttiming2 = 0x64514051;
				ptiming->nxttiming3 = 0xffd4e033;
	 			*/
	writel(0x5498170e, CM3_DDRC_BASE_ADDR + 0x70);
	writel(0x18a7462c, CM3_DDRC_BASE_ADDR + 0x74);
	writel(0x64514049, CM3_DDRC_BASE_ADDR + 0x78);
	writel(0xffd4e033, CM3_DDRC_BASE_ADDR + 0x7c);

	/* 4 */
	writel(0x1, CM3_DDRC_BASE_ADDR + 0x4);
	do{
		tmp = readl(CM3_DDRC_BASE_ADDR);
		tmp &= 0x4;
	}while(!tmp);
    times = 20;
    while(times)
    {
        times--;
    }

	/* 5 */
	writel(sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_83c, CM3_DDRC_BASE_ADDR + 0x83c);
    writel(sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_abc, CM3_DDRC_BASE_ADDR + 0xabc);
    writel(sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_b3c, CM3_DDRC_BASE_ADDR + 0xb3c);
    writel(sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_bbc, CM3_DDRC_BASE_ADDR + 0xbbc);
    writel(sram_mem->SRAM_DFS_DDRC_CFG[1].ddr_reg_c3c, CM3_DDRC_BASE_ADDR + 0xc3c);

	/* 7 */
	writel(0x40001300, CM3_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);

	tmp = readl(CM3_CRG_BASE_ADDR + HI_CRG_CLK_SEL1_OFFSET);
	tmp &= ~0x300;
	tmp |= 0x200;
	writel(tmp, CM3_CRG_BASE_ADDR + HI_CRG_CLK_SEL1_OFFSET);

	/* 8 */
	writel(0x129, CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);

	/* 9 */
	writel(0x00800000, CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL1_OFFSET); 
	writel(0x0210103e, CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL2_OFFSET); 

    times = 30;
    while(times)
    {
        times--;
    }
	writel(0x128, CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);

	/* 10 */
	do
	{
		tmp = readl(CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);
		tmp = (tmp >> 31) & 0x1;
	}while(!tmp);

	/* 11 */
	tmp = readl(CM3_CRG_BASE_ADDR + HI_CRG_CLK_SEL1_OFFSET);
	tmp &= ~0x300;
	tmp |= 0x100;
	writel(tmp, CM3_CRG_BASE_ADDR + HI_CRG_CLK_SEL1_OFFSET);	
	writel(0x28, CM3_CRG_BASE_ADDR + HI_CRG_DFS1_CTRL3_OFFSET);

	/* 12 */
	writel(0x40001300, CM3_CRG_BASE_ADDR + HI_CRG_CLKDIV2_OFFSET);


	writel(0x1<<16, CM3_CRG_BASE_ADDR + HI_CRG_SRSTEN2_OFFSET);
	writel(0x1<<16, CM3_CRG_BASE_ADDR + HI_CRG_SRSTDIS2_OFFSET);

	/* 14 */
	writel(0x0, CM3_DDRC_BASE_ADDR + 0x4);
	do{
		tmp = readl(CM3_DDRC_BASE_ADDR);
		tmp &= 0x4;
	}while(tmp);
    times = 20;
    while(times)
    {
        times--;
    }

	/* 15 */
	tmp = readl(CM3_LP_PWRCTRL0);
	tmp &= ~0xFF000000;
	writel(tmp, CM3_LP_PWRCTRL0);
}




