/*mmc device declare and register*/
#include <linux/platform_device.h>
#include <linux/io.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include <mach/mmc.h>
#include <mach/gpio.h>

#include "reg_ops.h"
#include <mach/platform.h>
#if defined(CHIP_BB_HI6210)
#else
#include "soc_sctrl_interface.h"
#endif
#include "soc_peri_sctrl_interface.h"
#include <mach/clk_name_interface.h>
#include "drv_regulator_user.h"

#define MMC_RESET_CONTROLLER_TIMEOUT 10
/* mmc0 resource : mmc0 controller & interrupt mmc0 is used for emmc just to keep name to be same with k3*/
static struct resource mmc0_resources[] = {
	[0] = {
		.start          = REG_BASE_MMC0,
		.end            = REG_BASE_MMC0 + REG_MMC0_IOSIZE - 1,
		.flags          = IORESOURCE_MEM,
	},
	[1] = {
		.start          = IRQ_EMMC,
		.end            = IRQ_EMMC,
		.flags          = IORESOURCE_IRQ,
	},
};

static struct resource mmc1_resources[] = {
	[0] = {
		.start          = REG_BASE_MMC1,
		.end            = REG_BASE_MMC1 + REG_MMC1_IOSIZE - 1,
		.flags          = IORESOURCE_MEM,
	},
	[1] = {
		.start          = IRQ_SDMMC,
		.end            = IRQ_SDMMC,
		.flags          = IORESOURCE_IRQ,
	},
};

/* mmc2 resource : mmc2 controller & interrupt mmc2 is used for sdio just to keep name to be same with k3*/
static struct resource mmc2_resources[] = {
	[0] = {
		.start          = REG_BASE_MMC2,
		.end            = REG_BASE_MMC2 + REG_MMC0_IOSIZE - 1,
		.flags          = IORESOURCE_MEM,
	},
	[1] = {
		.start          = IRQ_SDIOMMC,
		.end            = IRQ_SDIOMMC,
		.flags          = IORESOURCE_IRQ,
	},
};

/* mmc1 sd timing config */
static int mmc1_timing_config[2][6] = {
	{
		0x9, 0x9, 0x9, 0x8, -1, 0x8
	},
	{
		0xf, 0xf, 0xf, 0xe, -1, 0xe
	},
};
/* mmc0 timing config */
static int mmc0_timing_config[2][6] = {
	{
		0x8, 0x8, 0x8, 0x8, -1, 0x8
	},
	{
		0x7, 0x7, 0x7, 0x7, -1, 0x7
	},
};

/* mmc2 timing config */
static int mmc2_timing_config[2][6] = {
	{
		0x8, 0x8, 0x8, 0x8, -1, 0x8
	},
	{
		0x7, 0x7, 0x7, 0x7, -1, 0x7
	},
};
/* mmc1 sd tuning init configs */
static int mmc1_init_tuning_config[7][TUNING_INIT_CONFIG_NUM] = {
/*		bus_clk, div, drv_sel, sam_sel, input_clk */
	{
		180000000, 6, 6, 13, 13, 25000000		/* init: 400k */
	},
	{
		180000000, 6, 4, 13, 13, 25000000 		/* 0: SDR12 */
	},
	{
		360000000, 6, 4, 2, 0, 50000000		/* 1: */
	},
	{
		360000000, 6, 4, 2, 0, 50000000		/* 2: SDR25 */
	},
	{
		720000000, 6, 1, 9, 4, 100000000		/* 3: SDR50 */
	},
	{
		-1, -1, -1, -1, -1, -1 			/* 4: SDR104 */
	},
	{
		360000000, 7, 1, 3, 0, 50000000		/* 5: DDR50 */
	},
};

/* mmc0 tuning init configs */
static int mmc0_init_tuning_config[7][TUNING_INIT_CONFIG_NUM] = {
/* bus_clk, div, drv_sel, sam_sel_max, sam_sel_min, input_clk */
    {
        26000000, 1, 1, 3, 3, 13000000          /* init: 400k */
    },
    {
        26000000, 1, 1, 3, 3, 13000000          /* 0: MMC_LEGACY */
    },
    {
        360000000, 6, 3, 3, 1, 50000000     /* 1: MMC_HS*/
    },
    {
        26000000, 1, 1, 3, 3, 13000000          /* 2: SDR25 */
    },
    {
        360000000, 6, 3, 3, 1, 50000000     /* 3: SDR50 */
    },
    {
        -1, -1, -1, -1, -1, -1                  /* 4: SDR104 */
    },
    {
        720000000, 6, 4, 8, 4, 100000000        /* 5: DDR50 */
    },
};

/* mmc2 sdio tuning init configs */
static int mmc2_init_tuning_config[7][TUNING_INIT_CONFIG_NUM] = {
/*		bus_clk, div, drv_sel, sam_sel, input_clk */
	{
		180000000, 6, 6, 13, 13, 25000000		/* init: 400k */
	},
	{
		180000000, 6, 4, 13, 13,25000000 		/* 0: SDR12 */
	},
	{
		360000000, 6, 4, 2, 0, 50000000		/* 1: */
	},
	{
		360000000, 6, 4, 2, 0, 50000000		/* 2: SDR25 */
	},
	{
		720000000, 6, 1, 9, 4, 100000000		/* 3: SDR50 */
	},
	{
		-1, -1, -1, -1, -1, -1			/* 4: SDR104 */
	},
	{
		360000000, 7, 1, 3, 0, 50000000		/* 5: DDR50 */
	},
};

#define MMC_RSTDIS_FUNC(chip_id, reg_name) \
static int mmc ## chip_id ## _rstdis(void) \
{\
    unsigned int ret;\
    unsigned int timeout = MMC_RESET_CONTROLLER_TIMEOUT;\
\
    phy_reg_writel(REG_BASE_SC_OFF,\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_ADDR(CALC_REG_OFFSET),\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_ ## reg_name ## _START,\
        SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_ ## reg_name ## _END, 1);\
\
    while (timeout--){\
        ret = phy_reg_readl(REG_BASE_SC_OFF, \
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT0_ADDR(CALC_REG_OFFSET),\
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_ ## reg_name ## _START,\
            SOC_PERI_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_ ## reg_name ## _END);\
\
        if (ret && (!timeout)){\
            printk(KERN_ERR "mmc %d clock rst fail\n", chip_id);\
            return -1;\
        }else if (!ret){\
            return 0;\
        }\
    }\
}

MMC_RSTDIS_FUNC(1, mmc1)
MMC_RSTDIS_FUNC(2, mmc2)

/* emmc platform data */
static struct hisik3_mmc_platform_data emmc_plat_data = {
	.ocr_mask = MMC_VDD_28_29,
#ifdef CONFIG_MACH_HI6210SFT
	.caps = MMC_CAP_8_BIT_DATA | MMC_CAP_CLOCK_GATING,
	.caps2 = MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_PACKED_CMD,
	.quirks = MSHCI_QUIRK_BROKEN_CARD_DETECTION |
		MSHCI_QUIRK_ALWAYS_WRITABLE |
		MSHCI_QUIRK_BROKEN_PRESENT_BIT,
    //MSHCI_QUIRK_TUNING_ENABLE,
#endif

	/* todo */
#ifdef CONFIG_MACH_HI6620OEM
	.caps = MMC_CAP_8_BIT_DATA | MMC_CAP_MMC_HIGHSPEED |MMC_CAP_CLOCK_GATING | MMC_CAP_1_8V_DDR | MMC_CAP_UHS_DDR50 | MMC_CAP_ERASE,
	.caps2 =  MMC_CAP2_HS200_1_8V_SDR | MMC_CAP2_PACKED_CMD,
	.quirks = MSHCI_QUIRK_BROKEN_CARD_DETECTION |
		      MSHCI_QUIRK_ALWAYS_WRITABLE |
		      MSHCI_QUIRK_BROKEN_PRESENT_BIT |
              MSHCI_QUIRK_HI6620_TUNING_FUNC |
              MSHCI_CONTROLLER_NEED_RESET,
              /*MSHCI_QUIRK_TUNING_ENABLE,*/
#endif
	.ext_cd_init = NULL,
	.ext_cd_cleanup = NULL,
	.set_power = NULL,
    .clk_mmc_low = CLK_MMC0LOW,
    .clk_mmc_high = CLK_MMC0HIGH,
	.iomux_name = "block_emmc",
	.reg_name_ldo = EMMC_VDDM_VDD,/*LDO19*/
	.reg_name_lvs = NULL,/*LDO5*/
	.cd_gpio = NULL,
	.reset_gpio = GPIO_2_3,
	.timing_config = &mmc0_timing_config[0][0],
	.init_tuning_config = &mmc0_init_tuning_config[0][0],
	.suspend_timing_config = 0xf,
	.default_signal_voltage = MMC_SIGNAL_VOLTAGE_180,
	.allow_switch_signal_voltage = 0,
};

#ifdef  CONFIG_MACH_HI6210SFT
static int sd_clk_reduce(void)
{
	unsigned long sctrl_addr = (unsigned long)IO_ADDRESS(REG_BASE_SC_OFF);
	writel((0x7)|(0x1<<7), SOC_PERI_SCTRL_SC_CLKCFG8BIT2_ADDR(sctrl_addr));
	return 0;
}
#endif
/*SD卡设备数据*/
static struct hisik3_mmc_platform_data sd_plat_data = {
	.ocr_mask = MMC_VDD_28_29,
	.caps = MMC_CAP_4_BIT_DATA    | MMC_CAP_SD_HIGHSPEED |
		    MMC_CAP_MMC_HIGHSPEED | MMC_CAP_1_8V_DDR | MMC_CAP_UHS_SDR12 |
		    MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50 |
		/*MMC_CAP_UHS_DDR50 |*/ MMC_CAP_DRIVER_TYPE_A | MMC_CAP_CLOCK_GATING,
	.quirks = MSHCI_QUIRK_ALWAYS_WRITABLE |
		MSHCI_QUIRK_EXTERNAL_CARD_DETECTION |
		MSHCI_CONTROLLER_NEED_RESET,
#ifdef  CONFIG_MACH_HI6210SFT
	.cd_gpio = GPIO_10_1,
	.sw_gpio = GPIO_10_0,
	.rstdis_mmc = sd_clk_reduce,
#endif
#ifdef CONFIG_MACH_HI6210OEM
	.cd_gpio = GPIO_0_2,
	.rstdis_mmc = mmc1_rstdis,
#endif
	.ext_cd_init = NULL,
	.ext_cd_cleanup = NULL,
	.set_power = NULL,
    .clk_mmc_low = CLK_MMC1LOW,
    .clk_mmc_high = CLK_MMC1HIGH,
    .iomux_name = "block_sd",/*todo*/
	.reg_name_ldo = SD_CARD_VDD,/*ldo10*/
	.reg_name_lvs = SD_CARD_IO_VDD,/*ldo7*/
	.signal_reg_name = NULL,
	.timing_config = &mmc1_timing_config[0][0],
	.init_tuning_config = &mmc1_init_tuning_config[0][0],
	.suspend_timing_config = 0x9,
	.default_signal_voltage = MMC_SIGNAL_VOLTAGE_330,
	.allow_switch_signal_voltage = 1,
};


static void (*sdio_notify_func)(struct platform_device *,
						   int state);

static int sdio_cd_init(void (*notify_func)(struct platform_device *,
						   int state))
{
	sdio_notify_func = notify_func;
	return 0;
}

static int sdio_cd_cleanup(void (*notify_func)(struct platform_device *,
						      int state))
{
	sdio_notify_func = NULL;
	return 0;
}

static struct hisik3_mmc_platform_data sdio_plat_data = {
	.ocr_mask = MMC_VDD_165_195	| MMC_VDD_27_28 | MMC_VDD_28_29
		| MMC_VDD_29_30 | MMC_VDD_30_31
		| MMC_VDD_31_32 | MMC_VDD_34_35
		| MMC_VDD_35_36,
	.caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ | MMC_CAP_SD_HIGHSPEED | MMC_CAP_NONREMOVABLE
		    | MMC_CAP_CLOCK_GATING,
	.quirks = MSHCI_QUIRK_ALWAYS_WRITABLE |
		MSHCI_QUIRK_WLAN_DETECTION |
		MSHCI_CONTROLLER_NEED_RESET,
	.ext_cd_init = sdio_cd_init,
	.ext_cd_cleanup = sdio_cd_cleanup,
	.set_power = NULL,
	.rstdis_mmc = mmc2_rstdis,
    .clk_mmc_low = CLK_MMC2LOW,
    .clk_mmc_high = CLK_MMC2HIGH,
	.reg_name_ldo = NULL,
	.reg_name_lvs = NULL,
	.signal_reg_name = NULL,
	.timing_config = &mmc2_timing_config[0][0],
	.init_tuning_config = &mmc2_init_tuning_config[0][0],
	.suspend_timing_config = 0x9,
	.default_signal_voltage = MMC_SIGNAL_VOLTAGE_180,
	.allow_switch_signal_voltage = 0,
};


/* emmc device */
static struct platform_device emmc_device = {
	.name           = "hi_mci",
	.id             = 0,
	.num_resources  = ARRAY_SIZE(mmc0_resources),
	.resource       = mmc0_resources,
	.dev = {
		.coherent_dma_mask      = 0xffffffff,
		.platform_data          = &emmc_plat_data,
	},
};

/* sd device */
static struct platform_device sd_device = {
	.name           = "hi_mci",
	.id             = 1,
	.num_resources  = ARRAY_SIZE(mmc1_resources),
	.resource       = mmc1_resources,
	.dev = {
		.coherent_dma_mask      = 0xffffffff,
		.platform_data          = &sd_plat_data,
	},
};

/* sdio device */
static struct platform_device sdio_device = {
	.name           = "hi_mci",
	.id             = 2,
	.num_resources  = ARRAY_SIZE(mmc2_resources),
	.resource       = mmc2_resources,
	.dev = {
		.coherent_dma_mask      = 0xffffffff,
		.platform_data          = &sdio_plat_data,
	},
};


int hi_sdio_detectcard_to_core(int val)
{
        if (sdio_notify_func == NULL)
                return -1;
        sdio_notify_func(&sdio_device, val);
        return 0;
}
EXPORT_SYMBOL(hi_sdio_detectcard_to_core);
void hi_sdio_set_power(int val)
{
        if (sdio_plat_data.set_power == NULL) {
                printk("sdio set power is null\n");
                return;
        }

        sdio_plat_data.set_power(&sdio_device, val);
        return;
}
EXPORT_SYMBOL(hi_sdio_set_power);

/* please add platform device in the struct.*/
static struct platform_device *plat_mmc_dev[] __initdata = {
	&emmc_device,
	//&sd_device,
	//&sdio_device
};

static int __init plat_mmc_dev_init(void)
{
	int ret = 0;

	ret = platform_add_devices(plat_mmc_dev, ARRAY_SIZE(plat_mmc_dev));

	return ret;
};

arch_initcall(plat_mmc_dev_init);

/*emmc test*/
struct platform_device *get_emmc_dev(void)
{
    return &emmc_device;
}

