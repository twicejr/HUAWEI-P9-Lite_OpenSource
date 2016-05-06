

#include <product_config.h>
#include <osl_types.h>
#include <osl_bio.h>
#include <hi_syscrg.h>
#include <soc_memmap.h>
#include <hi_uart.h>
#include <bsp_dfs_training.h>
#include "bsp_ate.h"

#ifndef min
#define min(a,b)        ((a) < (b) ? (a) : (b))
#endif

#define CFG_CLK_CPU_M3_BOOT (120*1000*1000)

TCM_DFS_TRAINING *tcm_dfs = (TCM_DFS_TRAINING * )DFS_DDR_TRAINING_DATA_ADDR;

const unsigned ddr_freq_type[DDR_FREQ_MAX] = {111, 133, 166, 200, 266, 333, 400, 450, 533};
const unsigned a9pll_ctrl1[DDR_FREQ_MAX] = {0x6d5555, 0x855555, 0x6d5555, 0x555555, 0x855555, 0x6d5555, 0x555555, 0xc00000, 0x855555};
const unsigned a9pll_ctrl2[DDR_FREQ_MAX] = {0x2101045, 0x1101037, 0x2101045, 0x2101053, 0x1101037, 0x2101045, 0x2101053, 0x210105d, 0x1101037};
const unsigned busdiv_crgcfg[DDR_FREQ_MAX] = {0x00005555,0x40007777,0x40003333,0x00003733,0x40003311,0x40001300,0x40001300,0x40001300,0x40001300};

struct ddrc_timing g_ddrc_timing[DDR_FREQ_MAX] = {
#ifdef BSP_CONFIG_LPDDR2
    [DDR_FREQ_111] = {0x6318C906,0x762A019, 0x4300901A,0xAF438035,0x600000,0x1080608,0x44,0x0,
                      0x14C62232,0x6191236, 0x20040C1A,0x80115C70,0x0,0x4,
                      0x20440605,0x106C3,   0xFF0A0000,0x24504A00,0x800C000},
    [DDR_FREQ_133] = {0x63210B07,0x862A01D, 0x4300901F,0xAF444035,0x600000,0x1080708,0x44,0x0,
                      0x18C72232,0x61D1236, 0x20040C1F,0x8014CC86,0x0,0x4,
                      0x20440605,0x106C3,   0xFF0A0000,0x24504A00,0x800C000},
    [DDR_FREQ_166] = {0x63290D08,0xA62A024, 0x4300B027,0xAF454035,0x600000,0x1080808,0x44,0x0,
                      0x1CC82332,0x6241636, 0x20040C26,0x8019F4A7,0x0,0x4,
                      0x20440605,0x106C3,   0xFF0A0000,0x24504A00,0x800C000},
    [DDR_FREQ_200] = {0x6331500A,0xC62A02B, 0x4300D02F,0xAF466035,0x600000,0x2080A08,0x44,0x0,
                      0x20CA3332,0x82B1A36, 0x20040C2D,0x801F44C9,0x0,0x4,
                      0x20440605,0x106C3,   0xFF0A0000,0x24504A00,0x800C000},
    [DDR_FREQ_266] = {0x6441D50D,0xF72A039, 0x5301103F,0xAF486035,0x600000,0x2080D08,0x44,0x0,
                      0x290D4432,0x8392236, 0x20050C3C,0x8029950B,0x0,0x4,
                      0x20440605,0x106C3,   0xFF0A0000,0x24504A00,0x800C000},
    [DDR_FREQ_333] = {0x654A180F,0x1372A047,0x6401504F,0xAF4A8046,0x600000,0x2081008,0x44,0x0,
                      0x354F4542,0x8472A36, 0x2006104B,0x80340D4E,0x0,0x4,
                      0x20440605,0x106C3,   0xFF0A0000,0x24504A00,0x800C000},
    [DDR_FREQ_400] = {0x655A9D12,0x1772A055,0x7401905F,0xAF4CA046,0x600000,0x3081308,0x44,0x0,
                      0x3D525642,0xA553236, 0x20071059,0x803E8591,0x0,0x4,
                      0x20440705,0x106C3,   0xFF0A0000,0x24504A00,0x800C000},
    [DDR_FREQ_450] = {0x666AE114,0x1972A060,0x8501C06A,0xAF4E2057,0x600000,0x3181508,0x44,0x0,
                      0x45946752,0xA603836, 0x20081464,0x804655C3,0x0,0x4,
                      0x20440705,0x106C3,   0xFF0A0000,0x24704A00,0xC000},
    [DDR_FREQ_533] = {0x677B6718,0x1E82A071,0x9502107E,0xAF50C057,0x600000,0x3181908,0x44,0x0,
                      0x51D87852,0xA714236, 0x20091477,0x80534E16,0x0,0x4,
                      0x20440705,0x106C3,   0xFF0A0000,0x24704A00,0xC000},
#elif defined(BSP_CONFIG_LPDDR3)
    [DDR_FREQ_111] = {0xB318C906,0x762A019, 0x4500901A,0xAF438145,0x10B00000,0x11080608,0x44,0x0,
                      0x14C62252,0x619126B, 0x2004101A,0x80115C70,0x3008406,0x4,
                      0x18340605,0x11643,   0xFF0A0000,0x1B504A00,0x800C000},
    [DDR_FREQ_133] = {0xB3210B07,0x862A01D, 0x4500901F,0xAF444145,0x10B00000,0x11080708,0x44,0x0,
                      0x18C72252,0x61D126B, 0x2004101F,0x8014CC86,0x3008407,0x4,
                      0x18340605,0x11643,   0xFF0A0000,0x1B504A00,0x800C000},
    [DDR_FREQ_166] = {0xB3290D08,0xA62A024, 0x4500A027,0xAF454145,0x10B00000,0x11080808,0x44,0x0,
                      0x1CC82352,0x624146B, 0x20041026,0x8019F4A7,0x3008488,0x4,
                      0x18340605,0x11643,   0xFF0A0000,0x1B504A00,0x800C000},
    [DDR_FREQ_200] = {0xB331500A,0xC62A02B, 0x4500B02F,0xAF466145,0x10B00000,0x12080A08,0x44,0x0,
                      0x20CA3352,0x82B166B, 0x2004102D,0x801F44C9,0x3008489,0x4,
                      0x18340605,0x11643,   0xFF0A0000,0x1B504A00,0x800C000},
    [DDR_FREQ_266] = {0xB441D50D,0xF72A039, 0x5500F03F,0xAF486145,0x10B00000,0x12080D08,0x44,0x0,
                      0x290D4452,0x8391E6B, 0x2005103C,0x8029950B,0x300858C,0x4,
                      0x18340605,0x11643,   0xFF0A0000,0x1B504A00,0x800C000},
    [DDR_FREQ_333] = {0xB54A180F,0x1372A047,0x6501204F,0xAF4A8245,0x10B00000,0x12081008,0x44,0x0,
                      0x354F4552,0x847246B, 0x2006104B,0x80340D4E,0x300860F,0x4,
                      0x18340605,0x11643,   0xFF0A0000,0x1B504A00,0x800C000},
    [DDR_FREQ_400] = {0xB55A9D12,0x1772A055,0x7501505F,0xAF4CA245,0x10B00000,0x13081308,0x44,0x0,
                      0x3D525652,0xA552A6B, 0x20071059,0x803E8591,0x3008691,0x4,
                      0x18340705,0x11643,   0xFF0A0000,0x1B504A00,0x800C000},
    [DDR_FREQ_450] = {0xB66AE114,0x1972A060,0x8501806A,0xAF4E2255,0x10B00000,0x13181508,0x44,0x0,
                      0x45946752,0xA60306B, 0x20081464,0x804655C3,0x3008713,0x4,
                      0x18340705,0x11643,   0xFF0A0000,0x1B704A00,0xC000},
    [DDR_FREQ_533] = {0xB77B6718,0x1E82A071,0x9501C07E,0xAF50C255,0x10B00000,0x13181908,0x44,0x0,
                      0x51D87852,0xA71386B, 0x20091477,0x80534E16,0x3008817,0x4,
                      0x18340705,0x11643,   0xFF0A0000,0x1B704A00,0xC000},
#endif
};

void udelay(unsigned int us)
{
#ifndef BSP_CONFIG_EDA
	while(us--) {
		unsigned long t = (CFG_CLK_CPU_M3_BOOT/3)/1000000;
		while(t--)
			__asm__ __volatile__("nop");
	}
#endif
}

int mddrc_freq_init(PLL_DIV_CTRL ddr_freq,unsigned int rank_sum)
{
	unsigned n, m, reg;

    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 13, 13, 0x1);
    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 13, 13, 0x0);
    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 15, 15, 0x1);
    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 15, 15, 0x0);
    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 14, 14, 0x1);
    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 14, 14, 0x0);

	if(ddr_freq_type[ddr_freq] <= 400)
		osl_reg_set_bit((void *)(0x90000000 + 0x454), 0, 0, 0x1);/*set ddrphy_pll bypass mode*/
	else
		osl_reg_set_bit((void *)(0x90000000 + 0x454), 0, 0, 0x0);/*set ddrphy_pll mission mode*/

	/*2、手动关闭phy的时钟门控(bypass_mode需要此步骤，mission mode不需要)*/
	if(ddr_freq_type[ddr_freq] <= 400) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF054), 7, 7, 0x1);/*bypass 模式下需要手动打开AC的时钟门控*/

		for(n = 0; n < 4; n++) {
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF248 + 0x80*n), 27, 27, 0x1);/*bypass 模式下需要手动打开DX的时钟门控*/
		}

		/*bypass_mode，phy pll不能锁定；mission_mode，phy pll锁定后，自动关闭时钟门控*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 31, 31, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 14, 14, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 9,  12, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 8,  8, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 0,  3, 0xF);

		/*3、PHY的时钟打开后，需要将PHY的时钟门控交由硬件控制（bypass mode需要此步骤，mission mode不需要）*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE00C), 31, 31, 0x0);/*原因是phyupdate在更新delay_line时，若不关闭phy的时钟，会引入glitch,导致phy内部出错*/
	}

	/*phy & PHY Counter的复位已经不能硬件可控，需要执行软件复位，否则某些寄存器状态未知*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 13, 13, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 13, 13, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 15, 15, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 15, 15, 0x0);

	/*4、关闭phy pll(bypass_mode需要此步骤,mission mode不需要)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE018), 0, 2, 0x7);/*关闭phy的pll,省功耗*/

	/*5-1、只有mission mode需要，PHY PLL参数配置 该寄存器用于调整pll 的sp、it、cpi 的配置值，不同的频点配置值不同，
	手册未说明v7r5需不需要待和台研确认（需要明确v7r5用什么值，实际上v7r5只有一个mission频点，
	故这个寄存器的配置不会引入切频流程）*/
	if(ddr_freq_type[ddr_freq] > 400) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF01C), 26, 27, 0x0);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF01C), 23, 24, 0x2);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF01C), 20, 22, 0x2);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF010), 11, 11, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF020), 0,  5,  0x2);

		for(n = 0; n < 2; n++) {
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF234 + 0x100*n), 10, 11, 0x0);
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF234 + 0x100*n), 7,  8,  0x2);
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF234 + 0x100*n), 4,  6,  0x2);
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF210 + 0x100*n), 0,  5,  0x2);
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF220 + 0x100*n), 10, 10, 0x1);
		}
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE018), 0,  2,  0x0);/*mission模式下要手动解除pll——pwdn*/
	}
	/*5-2、ODT(默认值零，不使能)和驱动力电阻的配置  以及VREF*/
	for(n = 0; n < 2; n++) {
		/*0:240Ω 1:120Ω 2:80Ω 3：60Ω 4:60Ω 5:48Ω 6:40Ω 7:34Ω*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF204 + 0x100*n), 14, 16, 0x7);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF204 + 0x100*n), 11, 13, 0x7);
	}
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF018), 23, 25, 0x7);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF018), 20, 22, 0x7);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF018), 17, 19, 0x7);

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF024), 0,  1, 0x0);

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 22, 23, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 18, 19, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 12, 13, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 6,  7,  0x3);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF028), 0,  1,  0x3);

	for(n = 0; n < 2; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF218 + 0x100*n), 0, 1, 0x0);
	}
	for(n = 0; n < 2; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 24, 25, 0x0);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 18, 19, 0x0);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 12, 13, 0x0);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 6,  7,  0x3);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF21C + 0x100*n), 0,  1,  0x3);
	}

	/*5-3、data_swap/rs_passthrough配置*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE070), 0, 31, g_ddrc_timing[ddr_freq].misc);   /*MISC(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE084), 0, 31, g_ddrc_timing[ddr_freq].dmsel);  /*DMSEL(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xEFF0), 0, 31, g_ddrc_timing[ddr_freq].ioctrl3);/*IOCTL3(PACK)*/

	/*6、配置phy部分寄存器*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE078), 2, 2, 0x1);     /*PHYCTRL0*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE01C), 16, 31, 0x1000);/*PHY_PLL锁定需要的时间(>=20us)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE01C), 0, 7, 0xA0);    /*PHY_PLL复位需要的时间(>=1us)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE020), 0, 0, 0x0);     /*rdqscyc最高127级，在ff corner下，每级dely_line大概11ps,rdqscyc用完才1.4ns左右，因此建议配置为0 （delymeas 校准T/2）*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1D4), 16, 20, 0xC);   /*设定CA和CK之间的T/4相位差*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE010), 12, 31, 0x7000);/*相当于器件手册的参数tINIT3(200us,lpddr2/3相同)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE014), 0, 19, 0x10);   /*相当于器件手册的参数tINIT1(100ns，lpddr2/3相同)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1E4), 0, 7, 0x0);     /*控制器一侧已经保证了cke和ck之间的时序关系，pack里设置这俩个参数反而会导致cke和ck之间的时序关系违例*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE02C), 0, 2, 0x5);     /*配置DRAM类型（5：lpddr2/3）*/

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE030), 0, 31, g_ddrc_timing[ddr_freq].dramtimer0);/*DRAMTIMER0(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE034), 0, 31, g_ddrc_timing[ddr_freq].dramtimer1);/*DRAMTIMER1(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE038), 0, 31, g_ddrc_timing[ddr_freq].dramtimer2);/*DRAMTIMER2(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE03C), 0, 31, g_ddrc_timing[ddr_freq].dramtimer3);/*DRAMTIMER3(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE040), 0, 31, g_ddrc_timing[ddr_freq].dramtimer4);/*DRAMTIMER4(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0BC), 0, 31, g_ddrc_timing[ddr_freq].dramtimer5);/*DRAMTIMER5(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE064), 0, 31, g_ddrc_timing[ddr_freq].modereg01); /*MODEREG01(PACK)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE068), 0, 31, g_ddrc_timing[ddr_freq].modereg23); /*MODEREG23(PACK)*/

	/*7、设置dterrstop*/
	if(ddr_freq_type[ddr_freq] <= 400) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 30, 30, 0x0);/*bypass mode下设0，mission mode设1*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0DC), 29, 29, 0x0);/*bypass mode下设0，mission mode设1*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0E8), 23, 23, 0x1);/*bypass mode下设1，mission mode设0*/
	}
	else {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 30, 30, 0x1);/*bypass mode下设0，mission mode设1*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0DC), 29, 29, 0x1);/*bypass mode下设0，mission mode设1*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0E8), 23, 23, 0x0);/*bypass mode下设1，mission mode设0*/
	}
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 24, 29, 0x30);/*根据张琪检视意见增加(2015-05-08)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0DC), 21, 21, 0x1);/*vince回复，V7R5配置0，1都可以*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0E8), 24, 31, 0x1A);/*Rule: (0x40/Cycle(ns)))；V7R5按400MHz来算，64/2.5 约= 26*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE0E8), 16, 19, 0xF);/*根据张琪检视意见增加(2015-05-08)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE118), 8,  11, 0x5);/*根据张琪检视意见增加(2015-05-08)*/

	/*8、设置phy动态跟踪，设置dfi接口update禁止*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE020), 5, 5, 0x1);/*注意：默认值为1，不对其关闭，用retrain_en总控*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE020), 4, 4, 0x0);/*使能门控窗口展宽后，就不能使用门控窗口的动态跟踪*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE020), 6, 6, 0x1);/*不对其关闭，用retrain_en总控*/

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 16, 31, 0x400);/*注意：默认值为1，不合理（需要台研给一个参考值）*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 14, 14, 0x0);/*rdqsg和GDS retrain功能一直不打开*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 13, 13, 0x0);/*注意：默认值为1，初始化前设置成0，初始化结束后要重新设置*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 0, 12, 0x400);/*注意：设定rsp时间足够大，确保控制器能响应phyupdate请求（暂时设置为默认值）*/

	/*9、使能PHY的门控展宽功能*/
	for(n = 0; n < 4; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF238 + 0x80*n), 28, 29, 0x3);/*门控窗口展宽俩拍*/
	}

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 16, 21, 0x2);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 10, 15, 0x2);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 4,  9,  0x10);/*SDR mode:6'b01000（1/2cycle）；HDR：6'b10000（1cycle）*/

	/*10、启动phy初始化*/
	/*只做delay_meas(bypass_mode需要此步骤，mission mode不需要)*/
	if(ddr_freq_type[ddr_freq] <= 400) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 31, 0x5);/*dlymeans_en*/
		while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 0) != 0x0){};/*确认delay_meas training完成*/
		reg = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE22C), 0, 8);/*rdqsbdl*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF054), 8, 16, min(reg,255));/*rdqsbdl若大于255取255*/
		for(n = 0; n < 4; n++) {
			osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xF250 + 0x80*n), 12, 20, min(reg,255));/*rdqsbdl若大于255取255*/
		}
	}

#ifdef BSP_CONFIG_LPDDR2
	if(ddr_freq_type[ddr_freq] <= 400)
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 15, 0x1469);
	else
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 15, 0x176F);
#elif defined(BSP_CONFIG_LPDDR3)
	if(ddr_freq_type[ddr_freq] <= 400)
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 15, 0x1469);
	else
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 15, 0x1FFF);
#endif

	/*11、配置DMC的工作模式及器件参数*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 8, 8, 1); /*1(SDR)/0(HDR)*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 20, 21, rank_sum - 1); /*0：1rank  1：2rank*/
#ifdef BSP_CONFIG_LPDDR2
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 0, 3, 2); /*根据器件类型  2：LPDDR2    3：LPDDR3*/
		for(n = 0; n < 2; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 8, 9, 1); /*根据器件类型 0：4bank   1：8bank*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 4, 6, 3); /*由实际对接的器件决定*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 0, 2, 1); /*由实际对接的器件决定*/
	}
#elif defined(BSP_CONFIG_LPDDR3)
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 0, 3, 3); /*根据器件类型  2：LPDDR2    3：LPDDR3*/

	for(n = 0; n < 2; n++) {
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 8, 9, 1); /*根据器件类型 0：4bank   1：8bank*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 4, 6, 4); /*由实际对接的器件决定*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*n), 0, 2, 2); /*由实际对接的器件决定*/
	}
#endif
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 4, 5, 2); /*DDR数据位宽为32bits*/

#ifdef BSP_CONFIG_LPDDR2
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8200), 16, 20, 0x8); /*配置为wl+4，可降低DMC的功耗:LPDDR2配8，LPDDR3配A*/
#elif defined(BSP_CONFIG_LPDDR3)
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8200), 16, 20, 0xA); /*配置为wl+4，可降低DMC的功耗:LPDDR2配8，LPDDR3配A*/
#endif

	/*12、配置DMC的时序参数*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8100), 0, 31, g_ddrc_timing[ddr_freq].timing0);/*DDRC_CFG_TIMING0*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8104), 0, 31, g_ddrc_timing[ddr_freq].timing1);/*DDRC_CFG_TIMING1*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8108), 0, 31, g_ddrc_timing[ddr_freq].timing2);/*DDRC_CFG_TIMING2*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x810C), 0, 31, g_ddrc_timing[ddr_freq].timing3);/*DDRC_CFG_TIMING3*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8110), 0, 31, g_ddrc_timing[ddr_freq].timing4);/*DDRC_CFG_TIMING4*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8114), 0, 31, g_ddrc_timing[ddr_freq].timing5);/*DDRC_CFG_TIMING5*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8118), 0, 31, g_ddrc_timing[ddr_freq].timing6);/*DDRC_CFG_TIMING6*/
#ifdef BSP_CONFIG_LPDDR3
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x811C), 0, 31, g_ddrc_timing[ddr_freq].timing7);/*DDRC_CFG_TIMING7*/
#endif

	/*13、确认初始化已经结束*/
	while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 0) != 0x0){};

	/*14、确认PHY初始化过程中没有发生错误*/
	if(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE008), 0, 31) != 0x0)
		return -1;

	if(rank_sum == 2) { /*rank数为2时执行以下配置，rank数为1时不需要配置*/
		/*15、设定初始化所在的rank*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 0, 3, 0x1); /*选定rank1*/

		/*16、启动rank1的gt_train*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 5, 6, 0x1);
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 0, 0x1);

		/*17、确认rank1的gt_train完成*/
		while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE004), 0, 0) != 0x0){};

		/*18、确认rank1的gt_training没有发生错误*/
		while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE008), 0, 31) != 0x0){};

		/*19、设定retrain开始的rank为rank0*/
		osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE048), 0, 3, 0x0);/*选定rank0*/
	}

	/*20、保存当前频点的training参数寄存器*/
	if(ddr_freq_type[ddr_freq] <= 400) { /*bypass_mode频点保存*/
		tcm_dfs->TRAINING[ddr_freq].ddr_freq = ddr_freq_type[ddr_freq];
		for(n = 0; n < 4; n++) {
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQSDLY[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE22C + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNGDS[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE23C + 0x80*n), 0, 31);
		}

		for(m = 0; m < 2; m++) {
			for(n = 0; n < 4; n++) {
				tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQSGDLY[m][n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE240 + 0x80*n +0x400*m), 0, 31);
			}
		}
	}
	else { /*mission mode频点保存*/
		tcm_dfs->TRAINING[ddr_freq].ddr_freq = ddr_freq_type[ddr_freq];
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL0 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE140), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL1 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE144), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL2 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE148), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL3 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE14C), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ACADDRBDL4 = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE150), 0, 31);
		tcm_dfs->TRAINING[ddr_freq].ddr_reg_ADDRPHBOUND = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1D4), 0, 31);
		for(n = 0; n < 4; n++) {
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQNBDL0[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE210 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQNBDL1[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE214 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQNBDL2[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE218 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNOEBDL[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE228 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQSDLY[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE22C + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQSDLY[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE230 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWDQDLY[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE234 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNWLSL[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE238 + 0x80*n), 0, 31);
			tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNGDS[n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE23C + 0x80*n), 0, 31);
		}

		for(m = 0; m < 2; m++) {
			for(n = 0; n < 4; n++) {
				tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQNBDL0[m][n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE21C + 0x80*n +0x800*m), 0, 31);
				tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQNBDL1[m][n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE220 + 0x80*n +0x800*m), 0, 31);
				tcm_dfs->TRAINING[ddr_freq].ddr_reg_DXNRDQSGDLY[m][n] = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE240 + 0x80*n +0x400*m), 0, 31);
			}
		}
	}
	return 0;
}

void a9pll_div_ctrl(PLL_DIV_CTRL ddr_freq)
{
	unsigned reg;

	osl_reg_set_bit((void *)(0x90000000 + 0x30), 0, 3, 0x8); /*打开PERIPLL输入参考时钟*/
	osl_reg_set_bit((void *)(0x90000000 + 0x144), 0, 3, 0x8); /*A9输入参考时钟源选择PERI PLL*/
	reg = osl_reg_get_bit((void *)(0x90000000 + 0x208), 8, 8);
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 8, 8, 0x1); /*0：由逻辑自动控制ARM PLL的PD状态；1：由软件控制ARM PLL工作状态，配合pd使用 */
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 0, 0, 0x1); /*配置A9 PLL powdown*/
	osl_reg_set_bit((void *)(0x90000000 + 0x200), 0, 31, a9pll_ctrl1[ddr_freq]); /*配置目标频点*/
	osl_reg_set_bit((void *)(0x90000000 + 0x204), 0, 31, a9pll_ctrl2[ddr_freq]); /*配置目标频点*/
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 0, 0, 0x0); /*解除A9 PLL powdown*/
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 3, 3, 0x1); /*4种相位时钟输出禁止*/
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 5, 5, 0x1); /*vco输出禁止*/
	while(osl_reg_get_bit((void *)(0x90000000 + 0x208), 31, 31) != 0x1){}; /*等待A9 PLL lock*/
	osl_reg_set_bit((void *)(0x90000000 + 0x104), 0, 31, busdiv_crgcfg[ddr_freq]); /*配置目标频点*/
	osl_reg_set_bit((void *)(0x90000000 + 0x144), 0, 3, 0x1); /*A9输入参考时钟源选择A9 PLL*/
	osl_reg_set_bit((void *)(0x90000000 + 0x208), 8, 8, reg); /*恢复切频前读出的pll_ctrl值*/
	osl_reg_set_bit((void *)(0x90000000 + 0x34), 0, 3, 0x8); /*关闭PERIPLL输入参考时钟*/
}

void *cpy_to_tcm(void *_dst, const void *_src, unsigned int len)
{
	unsigned char *dst = _dst;
	const unsigned char *src = _src;
	while(len-- > 0) {
		*dst++ = *src++;
	}
	return _dst;
}
void mddrc_init(void)
{
	unsigned i, ret = 0;

	for(i = 0; i < DDR_FREQ_MAX; i++) {
		cpy_to_tcm((void *)(&tcm_dfs->TIMING[i]),(const void *)(&g_ddrc_timing[i]),sizeof(struct ddrc_timing));
	}
	/*1、MDDRC+PACK+PHY 子系统的外围配置，旨在为DDR子系统提供稳定的、正确的时钟以及合适的系统控制信号：如bypass mode 的配置、复位控制*/
	osl_reg_set_bit((void *)(0x90000000 + 0x10), 0, 31, 0x7c0);  /*打开mddrc/ddrphy相关clk*/

	/*2-22、见mddrc_freq_init函数*/
#ifdef BSP_CONFIG_HIMDDRCV510_533
	a9pll_div_ctrl(DDR_FREQ_533);
	osl_reg_set_bit((void *)(0x90000000 + 0x60), 0, 31, 0x60000);/*手动复位mddrc/ddrphy*/
	osl_reg_set_bit((void *)(0x90000000 + 0x64), 0, 31, 0x60000);/*手动解复位mddrc/ddrphy*/
	ret = mddrc_freq_init(DDR_FREQ_533, 1); /*初始化533M,配置1个rank*/
#elif defined(BSP_CONFIG_HIMDDRCV510_333)
	a9pll_div_ctrl(DDR_FREQ_333);
	osl_reg_set_bit((void *)(0x90000000 + 0x60), 0, 31, 0x60000);/*手动复位mddrc/ddrphy*/
	osl_reg_set_bit((void *)(0x90000000 + 0x64), 0, 31, 0x60000);/*手动解复位mddrc/ddrphy*/
	ret = mddrc_freq_init(DDR_FREQ_333, 1); /*初始化333M,配置1个rank*/
#elif defined(BSP_CONFIG_HIMDDRCV510_133)
	a9pll_div_ctrl(DDR_FREQ_133);
	osl_reg_set_bit((void *)(0x90000000 + 0x60), 0, 31, 0x60000);/*手动复位mddrc/ddrphy*/
	osl_reg_set_bit((void *)(0x90000000 + 0x64), 0, 31, 0x60000);/*手动解复位mddrc/ddrphy*/
	ret = mddrc_freq_init(DDR_FREQ_133, 1); /*初始化133M,配置1个rank*/
#elif defined(BSP_CONFIG_HIMDDRCV510_ALL)
	for(i = 0; i < DDR_FREQ_MAX; i++) {
		a9pll_div_ctrl(i);
		osl_reg_set_bit((void *)(0x90000000 + 0x60), 0, 31, 0x60000);/*手动复位mddrc/ddrphy*/
		osl_reg_set_bit((void *)(0x90000000 + 0x64), 0, 31, 0x60000);/*手动解复位mddrc/ddrphy*/
		ret += mddrc_freq_init(i, 1); /*配置1个rank*/
	}
#endif

	if(ret != 0){
		print_info("mddrc init fail\r\n");
#ifdef ATE_VECTOR
        ate_gpio_on(ATE_GPIO_BAD_CHIP);
#endif
        __asm__ __volatile__("b .");
    }
	else{
		print_info("mddrc init ok\r\n");
#ifdef ATE_VECTOR
        ate_gpio_on(ATE_GPIO_DDR_1);
#endif
    }

	/*23、配置AXI_IF的地址映射模式（V7R5代码配置了俩个region,根据实际的地址映射需求配置该寄存器）*/
#if 0 /*exclusive/防死锁功能暂时不配*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x20),  0, 1, 0x1);/*是否要使能exclusive功能（默认使能），是否要打开读wrap命令拆分（默认禁止0）*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x20),  8, 19, 0x1);/*使能防死锁模式（默认禁止）*/
#endif
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x100), 0, 12, 0x1640);/*结合器件容量及系统应用场景配置,这里设置成一个region,1G容量。回片设置成：0x1640*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 28, 30, 0x4);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 24, 25, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 16, 18, 0x4);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 8,  15, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x104), 0,  5, 0x4);

	/*24、配置AXI_IF/SEC/QOSBUF/DMC的各种可选功能（暂时忽略，根据实际需求配置）*/

	/*25、用宏定义隔开，基本流程调试稳定后再开启*/
#if 1
	/*25-1、使能pd,asref,lp功能*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 20,  31, 0x1);/*dmc连续空闲asref_prd*1024个周期后会进入自刷新(不要影响性能，参考K3)（K3没有实测下配置为1us）*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 16,  19, 0x1);/*ddr_cke在phy内部路径比时钟门控长一个cycle*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 4,  15, 0x20);/*dmc连续空闲pd_prd个周期后进入power_down状态(参考V9R1配置为8？是否会太频繁而影响性能？参考K3)（K3没有实测下配置为23cycle）*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 2,  2, 0x0);  /*进入pd后关闭DDR时钟(pd_en和lp_en是否都会对CK时钟门控？是)（因为V9R1有bug,所以V8R1中也配置为0）*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8028), 0,  0, 0x1);  /*使能pd功能*/
	/*25-2、使能自动刷新优化功能*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x802C), 2,  2, 0x1);  /*1：自动刷新优化  0：自动刷新非优化模式*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x802C), 5,  6, 0x2);  /*配置自动刷新优化的水线为4*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8020), 16, 31, 0x3);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8020), 1,  1, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8020), 0,  0, 0x1);
	/*25-3、使能ZQ校准*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 23, 23, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 22, 22, 0x1);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8050), 16, 16, 0x1);

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1E4), 21, 24, 0x0);/*DDRC_CFG_LP.tlp_wakeup>=t_wakeup_thrd_lv2，关闭时钟和CA*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1E4), 12, 15, 0x7);/*响应时间，必须小于 DDRC_CFG_LP.tlp_resp，否则LP得不到响应（只是DFI协议规定最大7）*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE1E4), 8,  11, 0x6);/*lv3的wakeup time需要足够大，确保pll power_up 之后重新锁定（当前配置下不会用到，改为默认值6）*/

	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x801C), 16, 19, 0xA);/*DDRC_CFG_LP.t_wcke 是为了保证PHY在进入低功耗之前cke能透传到DRAM,从仿真波形来看，
																   在SDR、HDR 模式下，cke重dfi接口到DRAM分别需要四拍和八拍，因此配置A，余量足够！*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x801C), 12, 15, 0xF);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x801C), 8,  11, 0x0);
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x801C), 0,  0,  0x1);/*在pd_en=1，才能使能lp_en*/
	/*25-4、设置dfi接口update使能*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0xE080), 13,  13,  0x1);/*注意：默认值为1，初始化前设置成0，初始化后设置为1*/
#endif

	/*26、配置控制退出自刷新*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8000), 0,  1,  0x0);

	/*27、确认已处于非自刷新态*/
	while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8294), 0, 0) != 0x0){};

	/*28、撤销DMC对AXI的反压*/
	osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8000), 1,  1,  0x1);
    
    /*29、LPDDR2 读mr8自适应修改 row/col 宽度配置信息 (兼容美光由两个 1Gddr拼接的 2Gddr) */
#ifdef BSP_CONFIG_LPDDR2
    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8218), 0, 31, 0x10000); 
    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8210), 0, 31, 0x40000087); 
    osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x800C), 0, 31, 0x00000001);

    while(osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x800C), 0, 0) == 0x1){};

    ret = osl_reg_get_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x84A8), 0, 7);
    if(0x50 == ret)
    {
        for(i = 0; i < 2; i++)
        {
            osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*i), 8, 9, 1); /*根据器件类型 0：4bank   1：8bank*/
            osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*i), 4, 6, 2); /*由实际对接的器件决定*/
            osl_reg_set_bit((void *)(HI_MDDRC_REGBASE_ADDR + 0x8060 + 0x4*i), 0, 2, 2); /*由实际对接的器件决定*/
        }
    }
#endif
}

