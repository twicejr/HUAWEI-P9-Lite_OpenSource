#ifndef _DWC_OTG_HI6250_
#define _DWC_OTG_HI6250_
#include "hisi_usb_otg_type.h"

/**
 * USB related register in PERICRG
 */
#define PERI_CRG_CLK_EN4			(0x40)
#define PERI_CRG_CLK_DIS4			(0x44)
#define PERI_CRG_CLK_CLKEN4			(0x48)
#define PERI_CRG_CLK_STAT4			(0x4C)
#define BIT_CLK_USB2OTG_REF			(1 << 2)
#define BIT_HCLK_USB2OTG			(1 << 1)
#define BIT_HCLK_USB2OTG_PMU			(1 << 0)

#define PCTRL_PERI_CTRL24				(0x64)

#define PERI_CRG_RSTEN4				(0x90)
#define PERI_CRG_RSTDIS4			(0x94)
#define PERI_CRG_RSTSTAT4			(0x98)
#define BIT_RST_USB2OTG_MUX			(1<<10)
#define BIT_RST_USB2OTG_AHBIF			(1<<11)
#define BIT_RST_USB2OTG_PHY_N			(1<<8)
#define BIT_RST_USB2OTG_ADP			(1<<27)
#define BIT_RST_USB2OTG_32K			(1<<14)
#define BIT_RST_USB2OTG				(1<<9)
#define BIT_RST_USB2OTGPHY			(1<<12)
#define BIT_RST_USB2OTGPHYPOR			(1<<13)

/**
 * USB related registers in PRRICRG
 */
#define REG_PMU_SSI_VERSION		0
#define REG_PMU_SSI_STATUS0		(0x01 << 2)
# define VBAT3P2_2D			(1 << 4)
# define VBUS5P5_D10R			(1 << 3)
# define VBUS4P3_D10			(1 << 2)
# define VBUS_COMP_VBAT_D20		(1 << 1)
#define REG_PMU_SSI_STATUS1		(0x02 << 2)
#define REG_PMU_SSI_IRQ0		(0x120 << 2)
#define REG_PMU_SSI_IRQ1		(0x121 << 2)
# define VBUS_COMP_VBAT_F		(1 << 4)
# define VBUS_COMP_VBAT_R		(1 << 3)
#define REG_PMU_SSI_IRQ_MASK_0		(0x102 << 2)
#define REG_PMU_SSI_IRQ_MASK_1		(0x103 << 2)


/**
 * USB ahbif registers
 */
#define USBPHY_ENTER_SIDDQ			(0x1)
#define USBPHY_QUIT_SIDDQ				(0x0)

#endif
