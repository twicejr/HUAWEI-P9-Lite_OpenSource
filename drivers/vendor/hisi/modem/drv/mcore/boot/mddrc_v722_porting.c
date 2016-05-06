

#include <hi_syscrg.h>
#include <soc_memmap.h>
#include "product_config.h"
#include <osl_types.h>
#include <osl_bio.h>
#include "mddrc_sec_cfg.h"

#define CFG_CLK_CPU_M3_BOOT (120*1000*1000)
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


void mddrc_init_emu()
{

	writel(0x7c0,			0x90000010);/*clock enable*/
	writel(0x60000,		0x90000364);/*reset de-assert*/
	writel(0x1,				0x90040404);/*mddrc_axi0 secure bypass*/
	writel(0x1,				0x90040604);/*mddrc_axi1 secure bypass*/
	writel(0x01e00211,	0x9004001c);/*1 rank; lpddr2; 32bit bl8*/
	writel(0x3f02,			0x90040024);/*cfg do lMR LPDDR2.Reset*/
	writel(0x1,				0x90040028);/*cmd_req*/
	writel(0x00630000,	0x90040014);/*LPDDR2.nWR=5;  LPDDR2.BL=8*/
	writel(0x10004,		0x90040018);/*LPDDR2.RL/WL=6/3 */
	writel(0x30105300,	0x90040020);/*sref_arefnum=3*/
	writel(0x1122,			0x9004002c);/*memmap:R-B-R-C(rank-bank-row-col);  bank:3bit;  row:13bit;  col:10bit*/
	writel(0xa0000000,	0x90040040);/*DDR_MEM BASE_ADDR*/
	writel(0x5498170e,	0x90040050);/*DDRC_TIMING1 (333Mhz)*/
	writel(0x18a7462c,	0x90040054);/*DDRC_TIMING2 (333Mhz)*/
	writel(0x0054e033,	0x9004005c);/*DDRC_TIMING4 (333Mhz)*/
	writel(0x0,				0x900400f4);/*ODT disable*/
	writel(0x0,				0x90040058);/*DDRC_TIMING3 (333Mhz)*/
	writel(0x0f000501,	0x900400ac);/*dt_byte:0xf;  rensel=0x2;  train_mode=1;  train_en=0(gate)*/
	writel(0x0,				0x90040004);/*sr_req=0*/
	while((readl(0x90040000) & 0x4))/*in_sr==0*/
	{};
	writel(0x1,				0x90040008);/*init_req=1*/
	while((readl(0x90040000) & 0x8))/*in_init==0 */
	{};

}

void v722_porting_mddrc_init(void)
{
	writel(0x7c0,      0x90000010);
	writel(0x60000,    0x90000364);
	writel(0x1,        HI_MDDRC_REGBASE_ADDR + 0x404);
	writel(0x1,        HI_MDDRC_REGBASE_ADDR + 0x604);
	writel(0x32308000, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x0f000101, HI_MDDRC_REGBASE_ADDR + 0xac);  
	writel(0x0,        HI_MDDRC_REGBASE_ADDR + 0x04);
	while((readl(HI_MDDRC_REGBASE_ADDR+0x00) & 0x4))
	{};

	/* 1us */
	udelay(1);

	writel(0x01e00210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x3f02,     HI_MDDRC_REGBASE_ADDR + 0x24);
	writel(0x1,        HI_MDDRC_REGBASE_ADDR + 0x28);

	/* 1us */
	udelay(1);

	writel(0x00220000, HI_MDDRC_REGBASE_ADDR + 0x14);
	writel(0x20004,    HI_MDDRC_REGBASE_ADDR + 0x18);
	writel(0x01e00210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x30005300, HI_MDDRC_REGBASE_ADDR + 0x20);
	writel(0x131,      HI_MDDRC_REGBASE_ADDR + 0x2c);
	writel(0x131,      HI_MDDRC_REGBASE_ADDR + 0x30);
	writel(0x131,      HI_MDDRC_REGBASE_ADDR + 0x34);
	writel(0x131,      HI_MDDRC_REGBASE_ADDR + 0x38);
	writel(0xa0000000, HI_MDDRC_REGBASE_ADDR + 0x40);
	writel(0x32330603, HI_MDDRC_REGBASE_ADDR + 0x50);
	writel(0x04324607, HI_MDDRC_REGBASE_ADDR + 0x54);
	writel(0x3230800c, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x00032032, HI_MDDRC_REGBASE_ADDR + 0x5c);
	writel(0x0,        HI_MDDRC_REGBASE_ADDR + 0xf4);
	writel(0x0f000103, HI_MDDRC_REGBASE_ADDR + 0xac);
	writel(0x1,        HI_MDDRC_REGBASE_ADDR + 0x08);
	while((readl(HI_MDDRC_REGBASE_ADDR+0x0) & 0x8))
	{};
	while((readl(HI_MDDRC_REGBASE_ADDR+0xd4) & 0xf))
	{};
	writel(0x30105700, HI_MDDRC_REGBASE_ADDR + 0x20);
}

void mddrc_init()
{

#ifdef BSP_CONFIG_EMU
    mddrc_init_emu();
#else
    v722_porting_mddrc_init();
	mddrc_sec_cfg();
#endif
}
