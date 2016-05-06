

#include <hi_syscrg.h>
#include <soc_memmap.h>
#include <product_config.h>
#include "bio.h"

void mddrc_init()
{
	unsigned reg;
	unsigned delay = 100;
    /* ddr init */
	reg = readl(HI_SYSCTRL_BASE_ADDR + HI_CRG_CTRL14_OFFSET);
	reg &= ~0x20000;
	writel(reg, HI_SYSCTRL_BASE_ADDR + HI_CRG_CTRL14_OFFSET);

	/* Base Configuration of MDDRC */
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x10);
	writel(0x01e70210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x00620000, HI_MDDRC_REGBASE_ADDR + 0x14);
	writel(0x10004, HI_MDDRC_REGBASE_ADDR + 0x18);
	writel(0x30005300, HI_MDDRC_REGBASE_ADDR + 0x20);
#ifndef BALONG_DDR_ACTUAL_SZIE_1GB
	writel(0x122, HI_MDDRC_REGBASE_ADDR + 0x2c);
#else
	writel(0x121, HI_MDDRC_REGBASE_ADDR + 0x2c);
#endif
	writel(0x50000000, HI_MDDRC_REGBASE_ADDR + 0x40);
	writel(0x5498170e, HI_MDDRC_REGBASE_ADDR + 0x50);
	writel(0x1837462c, HI_MDDRC_REGBASE_ADDR + 0x54);
	writel(0xffd4e033, HI_MDDRC_REGBASE_ADDR + 0x5c);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0xf4);
	writel(0x34514000, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x0f000501, HI_MDDRC_REGBASE_ADDR + 0xac);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x04);
	while(readl(HI_MDDRC_REGBASE_ADDR) & 0x4)
	{};

	/* Configuration of PUB for DDR PHY ready for initilization */
	writel(0x80000000, HI_MDDRC_REGBASE_ADDR + 0x804);
	while(!(readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0x1))
	{};
	writel(0x1b8000, HI_MDDRC_REGBASE_ADDR + 0x820);

	writel(0x408, HI_MDDRC_REGBASE_ADDR + 0x888);
	writel(0x3808400, HI_MDDRC_REGBASE_ADDR + 0x80c);
	writel(0x44000285, HI_MDDRC_REGBASE_ADDR + 0xa80);
	writel(0x44000285, HI_MDDRC_REGBASE_ADDR + 0xb00);
	writel(0x44000285, HI_MDDRC_REGBASE_ADDR + 0xb80);
	writel(0x44000285, HI_MDDRC_REGBASE_ADDR + 0xc00);
	writel(0x44000284, HI_MDDRC_REGBASE_ADDR + 0xc80);
	writel(0x44000284, HI_MDDRC_REGBASE_ADDR + 0xd00);
	writel(0x44000284, HI_MDDRC_REGBASE_ADDR + 0xd80);
	writel(0x44000284, HI_MDDRC_REGBASE_ADDR + 0xe00);
	writel(0x44000284, HI_MDDRC_REGBASE_ADDR + 0xe80);
	writel(0xaaaa, HI_MDDRC_REGBASE_ADDR + 0xa88);
	writel(0x2000, HI_MDDRC_REGBASE_ADDR + 0xa8c);
	writel(0xaaaa, HI_MDDRC_REGBASE_ADDR + 0xb08);
	writel(0x2000, HI_MDDRC_REGBASE_ADDR + 0xb0c);
	writel(0xaaaa, HI_MDDRC_REGBASE_ADDR + 0xb88);
	writel(0x2000, HI_MDDRC_REGBASE_ADDR + 0xb8c);
	writel(0xaaaa, HI_MDDRC_REGBASE_ADDR + 0xc08);
	writel(0x2000, HI_MDDRC_REGBASE_ADDR + 0xc0c);
	writel(0x1001586, HI_MDDRC_REGBASE_ADDR + 0x8b0);
	writel(0x6864fe, HI_MDDRC_REGBASE_ADDR + 0x884);

	/* Configuration of PUB about Timing */
	writel(0x20010010, HI_MDDRC_REGBASE_ADDR + 0x824);
	writel(0x19000900, HI_MDDRC_REGBASE_ADDR + 0x828);
	writel(0x321046b, HI_MDDRC_REGBASE_ADDR + 0x830);
	writel(0x5380e53, HI_MDDRC_REGBASE_ADDR + 0x834);
	writel(0x5d0e8943, HI_MDDRC_REGBASE_ADDR + 0x88c);
	writel(0x22816295, HI_MDDRC_REGBASE_ADDR + 0x890);
	writel(0x10018c32, HI_MDDRC_REGBASE_ADDR + 0x894);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x898);
	writel(0x62, HI_MDDRC_REGBASE_ADDR + 0x8a0);
	writel(0x4, HI_MDDRC_REGBASE_ADDR + 0x8a4);
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x8a8);
	writel(0x181884, HI_MDDRC_REGBASE_ADDR + 0x880);
	writel(0xd, HI_MDDRC_REGBASE_ADDR + 0xa44);
	writel(0x58906, HI_MDDRC_REGBASE_ADDR + 0xa40);
	writel(0x58902, HI_MDDRC_REGBASE_ADDR + 0xa40);
	writel(0xaaaa, HI_MDDRC_REGBASE_ADDR + 0xa88);
	writel(0xaaaa, HI_MDDRC_REGBASE_ADDR + 0xb08);
	writel(0xaaaa, HI_MDDRC_REGBASE_ADDR + 0xb88);
	writel(0xaaaa, HI_MDDRC_REGBASE_ADDR + 0xc08);
	writel(0x2000, HI_MDDRC_REGBASE_ADDR + 0xa8c);
	writel(0x2000, HI_MDDRC_REGBASE_ADDR + 0xb0c);
	writel(0x2000, HI_MDDRC_REGBASE_ADDR + 0xb8c);
	writel(0x2000, HI_MDDRC_REGBASE_ADDR + 0xc0c);

	/* Start initilization */
	writel(0x1f3, HI_MDDRC_REGBASE_ADDR + 0x804);
	while(delay)
	{
		delay--;
	}
	while(!(readl(HI_MDDRC_REGBASE_ADDR+0x818) & 0x1))
	{};
	writel(0x34514051, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x30005700, HI_MDDRC_REGBASE_ADDR + 0x20);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0xf8);
	writel(0x10001fc0, HI_MDDRC_REGBASE_ADDR + 0xa48);
	writel(0x58906, HI_MDDRC_REGBASE_ADDR + 0xa40);
}

int dram_test()
{
	unsigned reg = 0;
	int ret = 0;

	reg = readl(HI_SYSCTRL_BASE_ADDR);
	reg |= 0x1000000;
	writel(reg, HI_SYSCTRL_BASE_ADDR);

	reg = readl(HI_SYSCTRL_BASE_ADDR + 0x38);
	reg &= 0xBFFFFFFF;
	writel(reg, HI_SYSCTRL_BASE_ADDR + 0x38);

	writel(0x2, HI_SYSCTRL_BASE_ADDR + 0x484);

	writel(0x40272, HI_MDDRC_REGBASE_ADDR + 0x5008);
	writel(0x50000000, HI_MDDRC_REGBASE_ADDR + 0x502c);
	writel(0xffffffc, HI_MDDRC_REGBASE_ADDR + 0x5030);
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
		while(1);
	}
	else
	{
		ret = 0;
	}
	writel(0x0, HI_SYSCTRL_BASE_ADDR + 0x484);

	return ret;

}

