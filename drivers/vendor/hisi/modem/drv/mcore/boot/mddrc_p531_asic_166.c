#include <boot/boot.h>
#include <balongv7r2/config.h>
#include <balongv7r2/mddrc.h>

void mddrc_init()
{
	unsigned reg;
	unsigned delay = 100;
    /* ddr init */
	reg = readl(HI_SC_REGBASE_ADDR + HI_CRG_CTRL14_REG);
	reg &= ~0x20000;
	writel(reg, HI_SC_REGBASE_ADDR + HI_CRG_CTRL14_REG);
	
	/* Base Configuration of MDDRC */
	writel(0x1, MDDRC_REGBASE_ADR + 0x10);
	writel(0x01e00210, MDDRC_REGBASE_ADR + 0x1c);
	writel(0x00620000, MDDRC_REGBASE_ADR + 0x14);
	writel(0x10004, MDDRC_REGBASE_ADR + 0x18);
	writel(0x30005300, MDDRC_REGBASE_ADR + 0x20);
#ifndef BALONG_DDR_ACTUAL_SZIE_1GB
	writel(0x122, MDDRC_REGBASE_ADR + 0x2c);
#else
	writel(0x121, MDDRC_REGBASE_ADR + 0x2c);
#endif
	writel(0x50000000, MDDRC_REGBASE_ADR + 0x40);
	writel(0x5498170e, MDDRC_REGBASE_ADR + 0x50);
	writel(0x1837462c, MDDRC_REGBASE_ADR + 0x54);
	writel(0xffd4e033, MDDRC_REGBASE_ADR + 0x5c);
	writel(0x0, MDDRC_REGBASE_ADR + 0xf4);
	writel(0x34514000, MDDRC_REGBASE_ADR + 0x58);
	writel(0x0f000501, MDDRC_REGBASE_ADR + 0xac);
	writel(0x0, MDDRC_REGBASE_ADR + 0x04);
	while(readl(MDDRC_REGBASE_ADR) & 0x4)
	{};
	
	/* Configuration of PUB for DDR PHY ready for initilization */
	writel(0x80000000, MDDRC_REGBASE_ADR + 0x804);
	while(!(readl(MDDRC_REGBASE_ADR+0x818) & 0x1))
	{};
	writel(0x801b8000, MDDRC_REGBASE_ADR + 0x820);
	
	writel(0x408, MDDRC_REGBASE_ADR + 0x888);
	writel(0x3808400, MDDRC_REGBASE_ADR + 0x80c);
	writel(0x44000285, MDDRC_REGBASE_ADR + 0xa80);
	writel(0x44000285, MDDRC_REGBASE_ADR + 0xb00);
	writel(0x44000285, MDDRC_REGBASE_ADR + 0xb80);
	writel(0x44000285, MDDRC_REGBASE_ADR + 0xc00);
	writel(0x44000284, MDDRC_REGBASE_ADR + 0xc80);
	writel(0x44000284, MDDRC_REGBASE_ADR + 0xd00);
	writel(0x44000284, MDDRC_REGBASE_ADR + 0xd80);
	writel(0x44000284, MDDRC_REGBASE_ADR + 0xe00);
	writel(0x44000284, MDDRC_REGBASE_ADR + 0xe80);
	writel(0xaaaa, MDDRC_REGBASE_ADR + 0xa88);
	writel(0x2000, MDDRC_REGBASE_ADR + 0xa8c);
	writel(0xaaaa, MDDRC_REGBASE_ADR + 0xb08);
	writel(0x2000, MDDRC_REGBASE_ADR + 0xb0c);
	writel(0xaaaa, MDDRC_REGBASE_ADR + 0xb88);
	writel(0x2000, MDDRC_REGBASE_ADR + 0xb8c);
	writel(0xaaaa, MDDRC_REGBASE_ADR + 0xc08);
	writel(0x2000, MDDRC_REGBASE_ADR + 0xc0c);
	writel(0x1001586, MDDRC_REGBASE_ADR + 0x8b0);
	writel(0x6864fe, MDDRC_REGBASE_ADR + 0x884);

	/* Configuration of PUB about Timing */	
	writel(0x20010010, MDDRC_REGBASE_ADR + 0x824);
	writel(0x19000900, MDDRC_REGBASE_ADR + 0x828);
	writel(0x321046b, MDDRC_REGBASE_ADR + 0x830);
	writel(0x5380e53, MDDRC_REGBASE_ADR + 0x834);
	writel(0x5d0e8943, MDDRC_REGBASE_ADR + 0x88c);
	writel(0x22816295, MDDRC_REGBASE_ADR + 0x890);
	writel(0x10018c32, MDDRC_REGBASE_ADR + 0x894);
	writel(0x0, MDDRC_REGBASE_ADR + 0x898);
	writel(0x62, MDDRC_REGBASE_ADR + 0x8a0);
	writel(0x4, MDDRC_REGBASE_ADR + 0x8a4);
	writel(0x1, MDDRC_REGBASE_ADR + 0x8a8);
	writel(0x181884, MDDRC_REGBASE_ADR + 0x880);
	writel(0xd, MDDRC_REGBASE_ADR + 0xa44);
	writel(0xd, MDDRC_REGBASE_ADR + 0xa54);
	writel(0xd, MDDRC_REGBASE_ADR + 0xa64);
	writel(0xd, MDDRC_REGBASE_ADR + 0xa74);
	writel(0x58900, MDDRC_REGBASE_ADR + 0xa40);
	writel(0x58902, MDDRC_REGBASE_ADR + 0xa40);
	writel(0xaaaa, MDDRC_REGBASE_ADR + 0xa88);
	writel(0xaaaa, MDDRC_REGBASE_ADR + 0xb08);
	writel(0xaaaa, MDDRC_REGBASE_ADR + 0xb88);
	writel(0xaaaa, MDDRC_REGBASE_ADR + 0xc08);
	writel(0x2000, MDDRC_REGBASE_ADR + 0xa8c);
	writel(0x2000, MDDRC_REGBASE_ADR + 0xb0c);
	writel(0x2000, MDDRC_REGBASE_ADR + 0xb8c);
	writel(0x2000, MDDRC_REGBASE_ADR + 0xc0c);
	
	/* Start initilization */
	writel(0x1e3, MDDRC_REGBASE_ADR + 0x804);
	while(delay)
	{
		delay--;
	}
	while(!(readl(MDDRC_REGBASE_ADR+0x818) & 0x1))
	{};
	writel(0x34514028, MDDRC_REGBASE_ADR + 0x58);
	writel(0x30005700, MDDRC_REGBASE_ADR + 0x20);
	writel(0x1, MDDRC_REGBASE_ADR + 0xf8);
}

int dram_test()
{
	unsigned reg = 0;
	int ret = 0;
	
	reg = readl(HI_SC_REGBASE_ADDR);
	reg |= 0x1000000;
	writel(reg, HI_SC_REGBASE_ADDR);
	
	reg = readl(HI_SC_REGBASE_ADDR + 0x38);
	reg &= 0xBFFFFFFF;
	writel(reg, HI_SC_REGBASE_ADDR + 0x38);
	
	writel(0x2, HI_SC_REGBASE_ADDR + 0x484);
	
	writel(0x40272, MDDRC_REGBASE_ADR + 0x5008);
	writel(0x50000000, MDDRC_REGBASE_ADR + 0x502c); 
	writel(0xffffffc, MDDRC_REGBASE_ADR + 0x5030);
	//writel(0x1fc, MDDRC_REGBASE_ADR + 0x5030); //∑¬’Ê π”√
	writel(0x0f0f0f0f, MDDRC_REGBASE_ADR + 0x500c);
	writel(0xe1e1e1e1, MDDRC_REGBASE_ADR + 0x5010);
	writel(0x2d2d2d2d, MDDRC_REGBASE_ADR + 0x5014);
	writel(0xc3c3c3c3, MDDRC_REGBASE_ADR + 0x5018);
	writel(0x4b4b4b4b, MDDRC_REGBASE_ADR + 0x501c);
	writel(0xa5a5a5a5, MDDRC_REGBASE_ADR + 0x5020);
	writel(0x69696969, MDDRC_REGBASE_ADR + 0x5024);
	writel(0x87878787, MDDRC_REGBASE_ADR + 0x5028);
	writel(0x1, MDDRC_REGBASE_ADR + 0x5004);
	
	do
	{
		reg = readl(MDDRC_REGBASE_ADR + 0x5000);
		reg &= 0x1;
	}while(reg == 0);
	
	reg = readl(MDDRC_REGBASE_ADR + 0x5000);
	reg &= 0xE;
	if(reg != 0x0)
	{
		cprintf("dram test fail\n");
		while(1);
	}
	else
	{
		ret = 0;
	}
	writel(0x0, HI_SC_REGBASE_ADDR + 0x484);
	
	return ret;
	
}

