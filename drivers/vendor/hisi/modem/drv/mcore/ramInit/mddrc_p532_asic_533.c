

#include <hi_syscrg.h>
#include <soc_memmap.h>
#include "product_config.h"
#include <osl_types.h>
#include <osl_bio.h>

#define CFG_CLK_CPU_M3_BOOT (120*1000*1000)


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
	//reset release
	writel(0x1 << 16, HI_SYSSC_PD_BASE_ADDR + 0x070);
	writel(0x1 << 17, HI_SYSSC_PD_BASE_ADDR + 0x064);
	/* Base Configuration of MDDRC */
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x10);	
	writel(0x01e00211, HI_MDDRC_REGBASE_ADDR + 0x1c);	
	writel(0x3f02, HI_MDDRC_REGBASE_ADDR + 0x24);	
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x28);
	writel(0x00630000, HI_MDDRC_REGBASE_ADDR + 0x14);
	writel(0x00010004, HI_MDDRC_REGBASE_ADDR + 0x18);
	writel(0x30005300, HI_MDDRC_REGBASE_ADDR + 0x20);	
	writel(0x1122, HI_MDDRC_REGBASE_ADDR + 0x2C);	
	writel(0x50000000, HI_MDDRC_REGBASE_ADDR + 0x40);	
	writel(0x5498170E, HI_MDDRC_REGBASE_ADDR + 0x50);
	writel(0x18A7462C, HI_MDDRC_REGBASE_ADDR + 0x54);	
	writel(0x0054E033, HI_MDDRC_REGBASE_ADDR + 0x5C);	
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0xF4);	
	writel(0x34514000, HI_MDDRC_REGBASE_ADDR + 0x58);	
	writel(0x0F000501, HI_MDDRC_REGBASE_ADDR + 0xAC);	
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x4);
	while(readl(HI_MDDRC_REGBASE_ADDR) & 0x4)
	{};	
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x8);	
	while(readl(HI_MDDRC_REGBASE_ADDR) & 0x8)
	{};	
	while(readl(HI_MDDRC_REGBASE_ADDR) & 0x4)
	{};														
}

void mddrc_init_winbond_166M()
{
	unsigned reg;
	
	//reset release
	writel(0x1 << 16, HI_SYSSC_PD_BASE_ADDR + 0x070);
	writel(0x1 << 17, HI_SYSSC_PD_BASE_ADDR + 0x064);

	/* Base Configuration of MDDRC */
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x10);
	writel(0x01e00210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x00c20000, HI_MDDRC_REGBASE_ADDR + 0x14);
	writel(0x00010006, HI_MDDRC_REGBASE_ADDR + 0x18);
	writel(0x30007300, HI_MDDRC_REGBASE_ADDR + 0x20);
	writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x2c);  
	writel(0x50000000, HI_MDDRC_REGBASE_ADDR + 0x40);
	writel(0x56ca2318, HI_MDDRC_REGBASE_ADDR + 0x50);  /*ddr 533*/
	writel(0x4ca55846, HI_MDDRC_REGBASE_ADDR + 0x54);
	writel(0xffe15055, HI_MDDRC_REGBASE_ADDR + 0x5c);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0xf4);
	writel(0x8581B000, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x0f000501, HI_MDDRC_REGBASE_ADDR + 0xac);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x04);
	while(readl(HI_MDDRC_REGBASE_ADDR) & 0x4)
	{};
	
	/* Configuration of PUB for DDR PHY ready for initilization */
	writel(0x80000000, HI_MDDRC_REGBASE_ADDR + 0x804);
	while(!((readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0x1) == 0x1))
	{};

	writel(0x001b8000, HI_MDDRC_REGBASE_ADDR + 0x820);
	
	writel(0x408, HI_MDDRC_REGBASE_ADDR + 0x888);
	writel(0x07008780, HI_MDDRC_REGBASE_ADDR + 0x80c);
	writel(0xF0081F, HI_MDDRC_REGBASE_ADDR + 0x810);
	writel(0x44000085, HI_MDDRC_REGBASE_ADDR + 0xa80);
	writel(0x44000085, HI_MDDRC_REGBASE_ADDR + 0xb00);
	writel(0x44000085, HI_MDDRC_REGBASE_ADDR + 0xb80);
	writel(0x44000085, HI_MDDRC_REGBASE_ADDR + 0xc00);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xc80);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xd00);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xd80);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xe00);
	writel(0x44000084, HI_MDDRC_REGBASE_ADDR + 0xe80);
	
	writel(0x11001086, HI_MDDRC_REGBASE_ADDR + 0x8b0);
	writel(0x006c64fe, HI_MDDRC_REGBASE_ADDR + 0x884);

	/*PUB_DX0GTR*/
	writel(0x00055002, HI_MDDRC_REGBASE_ADDR + 0xac8);
	writel(0x00055002, HI_MDDRC_REGBASE_ADDR + 0xb48);
	writel(0x00055002, HI_MDDRC_REGBASE_ADDR + 0xbc8);
	writel(0x00055002, HI_MDDRC_REGBASE_ADDR + 0xc48);

	/* Configuration of PUB about Timing */	
	writel(0x10a00855, HI_MDDRC_REGBASE_ADDR + 0x824);
	writel(0x33f604ae, HI_MDDRC_REGBASE_ADDR + 0x828);
	writel(0x0361a072, HI_MDDRC_REGBASE_ADDR + 0x830);
	writel(0x8541e68, HI_MDDRC_REGBASE_ADDR + 0x834);
	writel(0x29980c55, HI_MDDRC_REGBASE_ADDR + 0x88c);
	writel(0x228232f0, HI_MDDRC_REGBASE_ADDR + 0x890);
	writel(0x10007fff, HI_MDDRC_REGBASE_ADDR + 0x894);
	writel(0x1408d0, HI_MDDRC_REGBASE_ADDR + 0x898);
	writel(0x000000c2, HI_MDDRC_REGBASE_ADDR + 0x8a0);
	writel(0x00000006, HI_MDDRC_REGBASE_ADDR + 0x8a4);
	writel(0x00000001, HI_MDDRC_REGBASE_ADDR + 0x8a8);
	writel(0x00181884, HI_MDDRC_REGBASE_ADDR + 0x880);
	writel(0x000000cc, HI_MDDRC_REGBASE_ADDR + 0xa44);

	writel(0x000000dd, HI_MDDRC_REGBASE_ADDR + 0xa54);/*PUB_ZQ1PR, for DX parts*/

	writel(0x04058906, HI_MDDRC_REGBASE_ADDR + 0xa40);
	/* 1us */
	udelay(1);
    
	writel(0x04058902, HI_MDDRC_REGBASE_ADDR + 0xa40);
	writel(0x0000aaaa, HI_MDDRC_REGBASE_ADDR + 0xa88);
	writel(0x0000aaaa, HI_MDDRC_REGBASE_ADDR + 0xb08);
	writel(0x0000aaaa, HI_MDDRC_REGBASE_ADDR + 0xb88);
	writel(0x0000aaaa, HI_MDDRC_REGBASE_ADDR + 0xc08);
	writel(0x00002000, HI_MDDRC_REGBASE_ADDR + 0xa8c);
	writel(0x00002000, HI_MDDRC_REGBASE_ADDR + 0xb0c);
	writel(0x00002000, HI_MDDRC_REGBASE_ADDR + 0xb8c);
	writel(0x00002000, HI_MDDRC_REGBASE_ADDR + 0xc0c);

	/* Start initilization */
	writel(0x00000173, HI_MDDRC_REGBASE_ADDR + 0x804);

	/* 1us */
	udelay(1);

	while(!((readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0xf) == 0xf))
	{};
	if((readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0x1ff00000) != 0)
		writel(readl(HI_MDDRC_REGBASE_ADDR+0x818),0x90007000);
	
	writel(0x8581b080, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x30107700, HI_MDDRC_REGBASE_ADDR + 0x20);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0xf8);

	reg = readl(HI_MDDRC_REGBASE_ADDR + 0xa48);
	reg &= ~0xFFFC000;
	reg |= 0x3<<30;
	writel(reg, HI_MDDRC_REGBASE_ADDR + 0xa48);

	reg = readl(HI_MDDRC_REGBASE_ADDR + 0xa58);
	reg &= ~0xFFFC000;
	reg |= 0x3<<30;
	writel(reg, HI_MDDRC_REGBASE_ADDR + 0xa58);

	writel(0x0c058906, HI_MDDRC_REGBASE_ADDR + 0xa40);/*power down ZQ w00*/
	writel(0x00002008, HI_MDDRC_REGBASE_ADDR + 0xa8c);
	writel(0x00002008, HI_MDDRC_REGBASE_ADDR + 0xb0c);
	writel(0x00002008, HI_MDDRC_REGBASE_ADDR + 0xb8c);
	writel(0x00002008, HI_MDDRC_REGBASE_ADDR + 0xc0c);

#if 0
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x44);
    writel(0x000008e0, HI_MDDRC_REGBASE_ADDR + 0x24);
    writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x28);
    while(!((readl(HI_MDDRC_REGBASE_ADDR+0x48) & 0x300) == 0x200))
	{};
    writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x44);
#endif

}

void mddrc_init()
{
#ifdef BSP_CONFIG_EMU
	mddrc_init_emu();
#else
	mddrc_init_winbond_166M();
	
	writel(0x01e70210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	/*disable clk*/
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x8e4);
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
	writel(0xffffffc, HI_MDDRC_REGBASE_ADDR + 0x5030);
	//writel(0x1fc, MDDRC_REGBASE_ADR + 0x5030); //·ÂÕæÊ¹ÓÃ
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

