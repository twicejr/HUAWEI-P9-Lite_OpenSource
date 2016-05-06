

#include <hi_syscrg.h>
#include <soc_memmap.h>
#include <product_config.h>
#include "bio.h"

void mddrc_init()
{
	unsigned reg;
	unsigned delay = 100;


	writel(0x00020000, 0x90000064);
	writel(0x02000411, 0x90000404);

	writel(0x32308000, HI_MDDRC_REGBASE_ADDR + 0x58);
	writel(0x0f000101, HI_MDDRC_REGBASE_ADDR + 0xac);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0x4);

	while(readl(HI_MDDRC_REGBASE_ADDR) & 0x4)
	{};

	while(delay)
	{
		delay--;
	}

	writel(0x01e00210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x3f02, HI_MDDRC_REGBASE_ADDR + 0x24);
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x28);

	while(delay)
	{
		delay--;
	}

	writel(0x00220000, HI_MDDRC_REGBASE_ADDR + 0x14);
	writel(0x20006, HI_MDDRC_REGBASE_ADDR + 0x18);
	writel(0x01e00210, HI_MDDRC_REGBASE_ADDR + 0x1c);
	writel(0x30005300, HI_MDDRC_REGBASE_ADDR + 0x20);
	writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x2c);
	writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x30);
	writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x34);
	writel(0x131, HI_MDDRC_REGBASE_ADDR + 0x38);
	writel(0x50000000, HI_MDDRC_REGBASE_ADDR + 0x40);
	writel(0x32330403, HI_MDDRC_REGBASE_ADDR + 0x50);
	writel(0x04325807, HI_MDDRC_REGBASE_ADDR + 0x54);
	writel(0x3230800c, HI_MDDRC_REGBASE_ADDR + 0x58);

	writel(0x00032032, HI_MDDRC_REGBASE_ADDR + 0x5c);
	writel(0x0, HI_MDDRC_REGBASE_ADDR + 0xf4);
	writel(0x0f000103, HI_MDDRC_REGBASE_ADDR + 0xac);
	writel(0x1, HI_MDDRC_REGBASE_ADDR + 0x8);

	while(readl(HI_MDDRC_REGBASE_ADDR + 0x0) & 0x8)
	{};

	writel(0x30005700, HI_MDDRC_REGBASE_ADDR + 0x20);

}

