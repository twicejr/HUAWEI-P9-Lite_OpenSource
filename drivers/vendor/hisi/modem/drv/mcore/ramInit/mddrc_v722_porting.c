

#include <hi_syscrg.h>
#include <soc_memmap.h>
#include "product_config.h"
#include <osl_types.h>
#include <osl_bio.h>

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

void mddrc_init(void)
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
	writel(0x30005700, HI_MDDRC_REGBASE_ADDR + 0x20);
}