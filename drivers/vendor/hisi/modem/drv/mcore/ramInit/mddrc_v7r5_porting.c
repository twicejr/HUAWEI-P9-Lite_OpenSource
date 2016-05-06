

#include <hi_syscrg.h>
#include <soc_memmap.h>
#include "product_config.h"
#include <osl_types.h>
#include <osl_bio.h>

#define CFG_CLK_CPU_M3_BOOT (120*1000*1000)
#define V7R5_PORTING        0x6950A100
#define V7R5_ASIC           0x69500100
#define EMU_PALADIN         0x6950E100
#define EMU_ZEBU            0x6950E1A0

void udelay(unsigned int us)
{
	while(us--) {
		unsigned long t = (CFG_CLK_CPU_M3_BOOT/3)/1000000;
		while(t--)
			__asm__ __volatile__("nop");
	}
}

void mddrc_init_emu()
{
	/*A9 CLK switch to peri-pll,ddr:533M*/
	writel(0x8, 0x90000030);/*open peri-pll clk enable*/
	writel(0x8, 0x90000144);/*A9 CLK switch to peri-pll*/
	writel(0x181|readl(0x90000208),0x90000208);/*A9 pll powerdown,bypass*/
	writel(0x855555, 0x90000200);/*a9pll_postdiv=1066m*/
	writel(0x1101037, 0x90000204);
	writel(0x28,0x90000208);/*only enable pll postdivout*/
	while((readl(0x90000208) & 0x80000000) != 0x80000000)/*wait lock*/
	{};
	writel(0x40001300, 0x90000104);/*div cpu:fast:slow=1:2:4*/
	writel(0x1, 0x90000144);/*A9 CLK switch to a9-pll*/
	writel(0x8, 0x90000034);/*close peri-pll clk enable*/

	writel(0xffffffff, 0x90000010);/*enable clk*/
	writel(0x60000|readl(0x90000064),0x90000064);/*ddrphy srst*/
	writel(0x100|readl(0x9000080c),0x9000080c);/*mddrc open clk*/

	/*mddrc init start*/
	writel(0x60000, 0x90000060);/*dis reset mddrc*/
	writel(0x60000, 0x90000064);/*dis reset mddrc*/
	writel(0x03f7f1f1, 0x90000454);/*set ddrphy_pll bypass mode*/

	/* Base Configuration of MDDRC */
	writel(0x20, HI_MDDRC_REGBASE_ADDR + 0x8040);
	writel(0x100122, HI_MDDRC_REGBASE_ADDR + 0x8050);/*rank_num:1, lpddr2*/
	writel(0x132, HI_MDDRC_REGBASE_ADDR + 0x8060);
	writel(0x132, HI_MDDRC_REGBASE_ADDR + 0x8064);
	writel(0x10081000, HI_MDDRC_REGBASE_ADDR + 0x8200);
	
	/*for 533*/
	writel(0x677b6718, HI_MDDRC_REGBASE_ADDR + 0x8100);  
	writel(0x1e821871, HI_MDDRC_REGBASE_ADDR + 0x8104);/*twl:3(wl)+1,trl:6(rl)*/  
	writel(0x95021000, HI_MDDRC_REGBASE_ADDR + 0x8108);  /*cfg taref=0 in init*/
	writel(0xaf50c057, HI_MDDRC_REGBASE_ADDR + 0x810c);
	writel(0x600000, HI_MDDRC_REGBASE_ADDR + 0x8110);
	writel(0x3181908, HI_MDDRC_REGBASE_ADDR + 0x8114);
	writel(0x44, HI_MDDRC_REGBASE_ADDR + 0x8118);
	
	writel(0x1700, HI_MDDRC_REGBASE_ADDR + 0x0100);
	writel(0x71040004, HI_MDDRC_REGBASE_ADDR + 0x0104);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x8000);
	writel(0x2, HI_MDDRC_REGBASE_ADDR + 0x8000);	
	while((readl(HI_MDDRC_REGBASE_ADDR+0x8294) & 0x1) != 0x0)
	{};

	/*mrw start*/
	writel(0x30000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x400003f2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr63:LMR->reset lpddr3*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/	
	while((readl(HI_MDDRC_REGBASE_ADDR+0x800c) & 0x1) != 0x0)
	{};
	writel(0x30000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x400ff0a2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr10 calibration code:0xff;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/	
	while((readl(HI_MDDRC_REGBASE_ADDR+0x800c) & 0x1) != 0x0)
	{};
	writel(0x30000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x40043012, HI_MDDRC_REGBASE_ADDR + 0x8210);/*nWR:6;BL:8;mr1;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
	while((readl(HI_MDDRC_REGBASE_ADDR+0x800c) & 0x1) != 0x0)
	{};
	writel(0x30000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x40004022, HI_MDDRC_REGBASE_ADDR + 0x8210);/*R1:6,W1:3;mr2;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
	while((readl(HI_MDDRC_REGBASE_ADDR+0x800c) & 0x1) != 0x0)
	{};
	/*mrw end*/
	
	writel(0x9502107e, HI_MDDRC_REGBASE_ADDR + 0x8108);/*cfg taref=0x1f after init_done*/		
}


void v7r5_porting_mddrc_init_lpddr2()
{
	writel(0x60000, 0x90000064);/*dis reset ddrphy & mddrc*/
	writel(0x03f7f1f1, 0x90000454);/*set ddrphy_pll bypass mode*/

	/* Base Configuration of MDDRC */
	writel(0x20, HI_MDDRC_REGBASE_ADDR + 0x8040);
	writel(0x000122, HI_MDDRC_REGBASE_ADDR + 0x8050);/*rank_num:1, lpddr2*/
	writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x8060);/*2Gbit/rank;  bank:3bit; row:14bit; col:9bit*/
	writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x8064);/*2Gbit/rank;  bank:3bit; row:14bit; col:9bit*/
	writel(0x10081000, HI_MDDRC_REGBASE_ADDR + 0x8200);
	writel(0x63210b07, HI_MDDRC_REGBASE_ADDR + 0x8100);  
	writel(0x0862181d, HI_MDDRC_REGBASE_ADDR + 0x8104);/*twl:3(wl)+1,trl:6(rl)*/  
	writel(0x43009000, HI_MDDRC_REGBASE_ADDR + 0x8108);  /*cfg taref=0 in init*/
	writel(0xaf444035, HI_MDDRC_REGBASE_ADDR + 0x810c);
	writel(0x600000, HI_MDDRC_REGBASE_ADDR + 0x8110);
	writel(0x1080708, HI_MDDRC_REGBASE_ADDR + 0x8114);
	writel(0x44, HI_MDDRC_REGBASE_ADDR + 0x8118);
	writel(0x1640, HI_MDDRC_REGBASE_ADDR + 0x0100);/*rgn_size:1GB*/
	writel(0x41040004, HI_MDDRC_REGBASE_ADDR + 0x0104);/*bnk_mode:512Byte; addr_aligned:128Byte*/
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x8000);
	writel(0x2, HI_MDDRC_REGBASE_ADDR + 0x8000);	
	while((readl(HI_MDDRC_REGBASE_ADDR+0x8294) & 0x1) != 0x0)
	{};

    /*mrw start*/
	udelay(2); /* 2us */
	writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x400003f2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr63:LMR->reset lpddr3*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
	writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x40043012, HI_MDDRC_REGBASE_ADDR + 0x8210);/*nWR:6;BL:8;mr1;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
	writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x40004022, HI_MDDRC_REGBASE_ADDR + 0x8210);/*R1:6,W1:3;mr2;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
	writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x400ff0a2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr10 calibration code:0xff;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/	
	udelay(10); /* 10us */
	/*mrw end*/
    
	writel(0x4500901f, HI_MDDRC_REGBASE_ADDR + 0x8108);/*cfg taref=0x1f after init_done*/
}


void v7r5_porting_mddrc_init_lpddr3()
{
	writel(0x60000, 0x90000064);/*dis reset ddrphy & mddrc*/
	writel(0x03f7f1f1, 0x90000454);/*set ddrphy_pll bypass mode*/

	/* Base Configuration of MDDRC */
	writel(0x20, HI_MDDRC_REGBASE_ADDR + 0x8040);
	writel(0x000123, HI_MDDRC_REGBASE_ADDR + 0x8050);/*rank_num:1, lpddr3*/
	writel(0x132, HI_MDDRC_REGBASE_ADDR + 0x8060);/*4Gbit/rank;  bank:3bit; row:14bit; col:10bit*/
	writel(0x132, HI_MDDRC_REGBASE_ADDR + 0x8064);/*4Gbit/rank;  bank:3bit; row:14bit; col:10bit*/
	writel(0x10081000, HI_MDDRC_REGBASE_ADDR + 0x8200);
	writel(0xb3210b07, HI_MDDRC_REGBASE_ADDR + 0x8100);  
	writel(0x0862181d, HI_MDDRC_REGBASE_ADDR + 0x8104);/*twl:3(wl)+1,trl:6(rl)*/  
	writel(0x45009000, HI_MDDRC_REGBASE_ADDR + 0x8108);/*cfg taref=0 in init*/
	writel(0xaf444145, HI_MDDRC_REGBASE_ADDR + 0x810c);
	writel(0x10b00000, HI_MDDRC_REGBASE_ADDR + 0x8110);
	writel(0x11080710, HI_MDDRC_REGBASE_ADDR + 0x8114);
	writel(0x44, HI_MDDRC_REGBASE_ADDR + 0x8118);
	writel(0x1640, HI_MDDRC_REGBASE_ADDR + 0x0100);/*rgn_size:1GB*/
	writel(0x41040004, HI_MDDRC_REGBASE_ADDR + 0x0104);/*bnk_mode:512Byte; addr_aligned:128Byte*/
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x8000);
	writel(0x2, HI_MDDRC_REGBASE_ADDR + 0x8000);	
	while((readl(HI_MDDRC_REGBASE_ADDR+0x8294) & 0x1) != 0x0)
	{};

    /*mrw start*/
	udelay(2); /* 2us */
	writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x400003f2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr63:LMR->reset lpddr3*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
	writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x40043012, HI_MDDRC_REGBASE_ADDR + 0x8210);/*nWR:6;BL:8;mr1;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
	writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x40004022, HI_MDDRC_REGBASE_ADDR + 0x8210);/*R1:6,W1:3;mr2;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/
	writel(0x10000, HI_MDDRC_REGBASE_ADDR + 0x8218);/*sfc_rank:rank0*/
	writel(0x400ff0a2, HI_MDDRC_REGBASE_ADDR + 0x8210);/*mr10 calibration code:0xff;LMR*/
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x800c);/*cmd_req=1*/	
	udelay(10); /* 10us */
	/*mrw end*/
    
	writel(0x4500901f, HI_MDDRC_REGBASE_ADDR + 0x8108);/*cfg taref=0x1f after init_done*/
}



void mddrc_init()
{
#ifdef BSP_CONFIG_EMU_PALADIN
		mddrc_init_emu();
#elif defined (BSP_CONFIG_EMU_ZEBU)
		v7r5_porting_mddrc_init_lpddr2();
#else
		v7r5_porting_mddrc_init_lpddr2();
#endif
#if 0
		unsigned reg = 0;
		reg = readl(0x90000f00);
		switch(reg)
		{
			case V7R5_PORTING:
				v7r5_porting_mddrc_init_lpddr2();
				break;
			case V7R5_ASIC:
				break;
			case EMU_PALADIN:
				mddrc_init_emu();
				break;
			case EMU_ZEBU:
				v7r5_porting_mddrc_init_lpddr2();
				break;
			default:
				v7r5_porting_mddrc_init_lpddr2();
				break;	
		}
#endif
}

int dram_test()
{ 
	unsigned reg = 0;
	int ret = 0;
	
	reg = readl(HI_SYSSC_PD_BASE_ADDR);
	reg |= 0x1000000;
	writel(reg, HI_SYSSC_PD_BASE_ADDR);
	
	writel(0x2, HI_SYSSC_PD_BASE_ADDR + 0x840);
	
	writel(0x40272, HI_MDDRC_REGBASE_ADDR + 0x5008);
	writel(0x50000000, HI_MDDRC_REGBASE_ADDR + 0x502c); 
	writel(0x7fffffc, HI_MDDRC_REGBASE_ADDR + 0x5030);
	//writel(0x1fc, MDDRC_REGBASE_ADR + 0x5030); //∑¬’Ê π”√
	writel(0x0f0f0f0f, HI_MDDRC_REGBASE_ADDR + 0x500c);
	writel(0xe1e1e1e1, HI_MDDRC_REGBASE_ADDR + 0x5010);
	writel(0x2d2d2d2d, HI_MDDRC_REGBASE_ADDR + 0x5014);
	writel(0xc3c3c3c3, HI_MDDRC_REGBASE_ADDR + 0x5018);
	writel(0x4b4b4b4b, HI_MDDRC_REGBASE_ADDR + 0x501c);
	writel(0xa5a5a5a5, HI_MDDRC_REGBASE_ADDR + 0x5020);
	writel(0x69696969, HI_MDDRC_REGBASE_ADDR + 0x5024);
	writel(0x87878787, HI_MDDRC_REGBASE_ADDR + 0x5028);
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x5004);
	
	do
	{
		reg = readl(HI_MDDRC_REGBASE_ADDR + 0x5000);
		reg &= 0x1;
	}while(reg == 0);
	
	reg = readl(HI_MDDRC_REGBASE_ADDR + 0x5000);
	reg &= 0xE;
	if(reg != 0x0)
	{
		/* coverity[no_escape] */
		while(1);
	}
	else
	{
		ret = 0;
	}
	writel(0x0, HI_SYSSC_PD_BASE_ADDR + 0x840);
	
	return ret; 
}

