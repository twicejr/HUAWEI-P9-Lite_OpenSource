


#include "product_config.h"
#include "securec.h"
#include "osl_types.h"
#include "osl_bio.h"
#include "osl_module.h"
#include "bsp_version.h"
#include "bsp_memmap.h"
#include "bsp_hardtimer.h"

void k3v5_fpga_init(void)
{
	/* LBUS½âËø */
	writel(0x110, 0xe1fa0024);
    udelay(100000);
}


void board_fpga_init(void)
{
    if(CHIP_V8R5 == bsp_get_version_info()->chip_type &&
       BSP_BOARD_TYPE_SFT == bsp_get_version_info()->board_type)
        k3v5_fpga_init();

    return;
}

