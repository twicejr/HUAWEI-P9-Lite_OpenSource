

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
	writel(0x1 << 16, 0x90000070);	
	writel(0x1 << 17, 0x90000064);
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

void mddrc_init()
{
	mddrc_init_emu();
}