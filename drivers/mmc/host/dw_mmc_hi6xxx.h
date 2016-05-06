/*
 *  linux/drivers/mmc/host/dw_mmc_hi6xxx.h -be used only by linux/drivers/mmc/host/dw_mmc_hi6xxx.c
 *
 *  this file clear pclint info 750 maro not reference
 *
 *  Copyright (c) 2013 Hisilicon Limited.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#ifndef _DW_MMC_HI6XXX_H_
#define _DW_MMC_HI6XXX_H_

#define DRIVER_NAME "dwmmc_hs"

#define PERI_CRG_RSTEN4             (0x90)
#define PERI_CRG_RSTDIS4            (0x94)

#define BIT_RST_MMC2                (1<<19)
#define BIT_RST_SD                  (1<<18)
#define BIT_RST_EMMC                (1<<17)

#define GPIO_CLK_ENABLE		        (0x1 << 16)

#define SCPERCTRL5		            (0x214)

#define BIT_SDCARD_IO_SEL18         (0x1 << 2)

#define EMMC_CS_BOARD               (12345678)
#define SD_CS_BOARD                   (10234567)

#define EMMC_TUNING_FAIL            (87654321)
#define EMMC_TUNING_SUCCESS         (0)

#define EMMC_TUNING_POINT_ODD       (1)
#define EMMC_TUNING_POINT_EVEN      (0)

#define EMMC_IS_ODD(value)          ((value%2) ? 1 : 0)

#define UHS_REG_EXT_SAMPLE_PHASE(x)	(((x) & 0x1f) << 16)
#define UHS_REG_EXT_SAMPLE_DLY(x)	(((x) & 0x1f) << 23)
#define SDMMC_UHS_REG_EXT_VALUE(x, y)	(UHS_REG_EXT_SAMPLE_PHASE(x) |	\
					UHS_REG_EXT_SAMPLE_DLY(y))

#define GPIO_CLK_DIV(x)	(((x) & 0xf) << 8)
#define GPIO_USE_SAMPLE_DLY(x)	(((x) & 0x1) << 13)
#define GPIO_DRIVE_SEL(x)	(((x) & 0x1) << 12)
#define SDMMC_GPIO_VALUE(x, y, z)	(GPIO_CLK_DIV(x) |	\
					GPIO_USE_SAMPLE_DLY(y) | GPIO_DRIVE_SEL(z))

#define MMC_UHS_REG_EXT_MACRO   (16)
#define MMC_UHS_REG_EXT_MIN     (21)
#define MMC_UHS_REG_EXT_22BIT   (22)
#define MMC_MAX_TUNING_VALUE    (15)
#define MMC_MAX_TUNING_CS_VALUE (31)
#define INVALID_TUNING_PHASE    (-1)

#define TURNING_SUCCESS_FIRST_POINT   (0x0)

/*SD卡上下电配置需求*/
#define GPIO_8_3    (67)
#define GPIO_8_4    (68)
#define GPIO_8_5    (69)
#define GPIO_8_6    (70)
#define GPIO_8_7    (71)
#define GPIO_9_0    (72)

#endif /* _DW_MMC_HI6XXX_H_ */
