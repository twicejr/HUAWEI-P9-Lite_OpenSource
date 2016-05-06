/*
 * Synopsys DesignWare Multimedia Card Interface driver
 *  (Based on NXP driver for lpc 31xx)
 *
 * Copyright (C) 2009 NXP Semiconductors
 * Copyright (C) 2009, 2010 Imagination Technologies Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _DW_MMC_H_
#define _DW_MMC_H_
#include <linux/mmc/dw_mmc.h>

#define DW_MMC_240A		0x240a

#define SDMMC_CTRL		0x000
#define SDMMC_PWREN		0x004
#define SDMMC_CLKDIV		0x008
#define SDMMC_CLKSRC		0x00c
#define SDMMC_CLKENA		0x010
#define SDMMC_TMOUT		0x014
#define SDMMC_CTYPE		0x018
#define SDMMC_BLKSIZ		0x01c
#define SDMMC_BYTCNT		0x020
#define SDMMC_INTMASK		0x024
#define SDMMC_CMDARG		0x028
#define SDMMC_CMD		0x02c
#define SDMMC_RESP0		0x030
#define SDMMC_RESP1		0x034
#define SDMMC_RESP2		0x038
#define SDMMC_RESP3		0x03c
#define SDMMC_MINTSTS		0x040
#define SDMMC_RINTSTS		0x044
#define SDMMC_STATUS		0x048
#define SDMMC_FIFOTH		0x04c
#define SDMMC_CDETECT		0x050
#define SDMMC_WRTPRT		0x054
#define SDMMC_GPIO		0x058
#define SDMMC_TCBCNT		0x05c
#define SDMMC_TBBCNT		0x060
#define SDMMC_DEBNCE		0x064
#define SDMMC_USRID		0x068
#define SDMMC_VERID		0x06c
#define SDMMC_HCON		0x070
#define SDMMC_UHS_REG		0x074
#define SDMMC_BMOD		0x080
#define SDMMC_PLDMND		0x084
#define SDMMC_DBADDR		0x088
#define SDMMC_IDSTS		0x08c
#define SDMMC_IDINTEN		0x090
#define SDMMC_DSCADDR		0x094
#define SDMMC_BUFADDR		0x098
#define SDMMC_CARDTHRCTL	0x100
#define SDMMC_UHS_REG_EXT	0x108
#define SDMMC_ENABLE_SHIFT	0x110
#define SDMMC_DATA(x)		(x)
#define SDMMC_IDSTS_64DMA		0x90
#define SDMMC_IDINTEN_64DMA	0x94
#define SDMMC_DBADDRL		0x88
#define SDMMC_DBADDRU		0x8c
#define SDMMC_64_BIT_DMA		1
#define SDMMC_32_BIT_DMA		0

/*
 * Data offset is difference according to Version
 * Lower than 2.40a : data register offest is 0x100
 */
#define DATA_OFFSET		0x100
#define DATA_240A_OFFSET	0x200

/* shift bit field */
#define _SBF(f, v)		((v) << (f))

/* Control register defines */
#define SDMMC_CTRL_USE_IDMAC		BIT(25)
#define SDMMC_CTRL_CEATA_INT_EN		BIT(11)
#define SDMMC_CTRL_SEND_AS_CCSD		BIT(10)
#define SDMMC_CTRL_SEND_CCSD		BIT(9)
#define SDMMC_CTRL_ABRT_READ_DATA	BIT(8)
#define SDMMC_CTRL_SEND_IRQ_RESP	BIT(7)
#define SDMMC_CTRL_READ_WAIT		BIT(6)
#define SDMMC_CTRL_DMA_ENABLE		BIT(5)
#define SDMMC_CTRL_INT_ENABLE		BIT(4)
#define SDMMC_CTRL_DMA_RESET		BIT(2)
#define SDMMC_CTRL_FIFO_RESET		BIT(1)
#define SDMMC_CTRL_RESET		BIT(0)
/* Clock Enable register defines */
#define SDMMC_CLKEN_LOW_PWR		BIT(16)
#define SDMMC_CLKEN_ENABLE		BIT(0)
/* time-out register defines */
#define SDMMC_TMOUT_DATA(n)		_SBF(8, (n))
#define SDMMC_TMOUT_DATA_MSK		0xFFFFFF00
#define SDMMC_TMOUT_RESP(n)		((n) & 0xFF)
#define SDMMC_TMOUT_RESP_MSK		0xFF
/* card-type register defines */
#define SDMMC_CTYPE_8BIT		BIT(16)
#define SDMMC_CTYPE_4BIT		BIT(0)
#define SDMMC_CTYPE_1BIT		0
/* Interrupt status & mask register defines */
#define SDMMC_INT_SDIO(n)		BIT(16 + (n))
#define SDMMC_INT_EBE			BIT(15)
#define SDMMC_INT_ACD			BIT(14)
#define SDMMC_INT_SBE			BIT(13)
#define SDMMC_INT_HLE			BIT(12)
#define SDMMC_INT_FRUN			BIT(11)
#define SDMMC_INT_HTO			BIT(10)
#define SDMMC_INT_VOLT_SW		BIT(10)
#define SDMMC_INT_DTO			BIT(9)
#define SDMMC_INT_RTO			BIT(8)
#define SDMMC_INT_DCRC			BIT(7)
#define SDMMC_INT_RCRC			BIT(6)
#define SDMMC_INT_RXDR			BIT(5)
#define SDMMC_INT_TXDR			BIT(4)
#define SDMMC_INT_DATA_OVER		BIT(3)
#define SDMMC_INT_CMD_DONE		BIT(2)
#define SDMMC_INT_RESP_ERR		BIT(1)
#define SDMMC_INT_CD			BIT(0)
#define SDMMC_INT_ERROR			0xbfc2
/* Command register defines */
#define SDMMC_CMD_START			BIT(31)
#define SDMMC_CMD_USE_HOLD_REG	BIT(29)
#define SDMMC_VOLT_SWITCH		BIT(28)
#define SDMMC_CMD_CCS_EXP		BIT(23)
#define SDMMC_CMD_CEATA_RD		BIT(22)
#define SDMMC_CMD_UPD_CLK		BIT(21)
#define SDMMC_CMD_INIT			BIT(15)
#define SDMMC_CMD_STOP			BIT(14)
#define SDMMC_CMD_PRV_DAT_WAIT		BIT(13)
#define SDMMC_CMD_SEND_STOP		BIT(12)
#define SDMMC_CMD_STRM_MODE		BIT(11)
#define SDMMC_CMD_DAT_WR		BIT(10)
#define SDMMC_CMD_DAT_EXP		BIT(9)
#define SDMMC_CMD_RESP_CRC		BIT(8)
#define SDMMC_CMD_RESP_LONG		BIT(7)
#define SDMMC_CMD_RESP_EXP		BIT(6)
#define SDMMC_CMD_INDX(n)		((n) & 0x1F)
#define SDMMC_CMD_ONLY_CLK		(SDMMC_CMD_START | SDMMC_CMD_UPD_CLK | \
						SDMMC_CMD_PRV_DAT_WAIT)
/* Status register defines */
#define SDMMC_STATUS_DMA_REQ 	BIT(31)
#define SDMMC_GET_FCNT(x)		(((x)>>17) & 0x1FFF)
#define SDMMC_DATA_BUSY			BIT(9)
/* FIFOTH register defines */
#define SDMMC_SET_FIFOTH(m, r, t)                                              \
	(((m) & 0x7) << 28 | ((r) & 0xFFF) << 16 | ((t) & 0xFFF))
#define SDMMC_SET_RD_THLD(v, x)         (((v) & 0x1FFF) << 16 | (x))
/* Internal DMAC interrupt defines */
#define SDMMC_IDMAC_INT_AI		BIT(9)
#define SDMMC_IDMAC_INT_NI		BIT(8)
#define SDMMC_IDMAC_INT_CES		BIT(5)
#define SDMMC_IDMAC_INT_DU		BIT(4)
#define SDMMC_IDMAC_INT_FBE		BIT(2)
#define SDMMC_IDMAC_INT_RI		BIT(1)
#define SDMMC_IDMAC_INT_TI		BIT(0)
/* Internal DMAC bus mode bits */
#define SDMMC_IDMAC_ENABLE		BIT(7)
#define SDMMC_IDMAC_FB			BIT(1)
#define SDMMC_IDMAC_SWRESET		BIT(0)
/* Version ID register define */
#define SDMMC_GET_VERID(x)		((x) & 0xFFFF)

#define CTRL_RESET	(0x1 << 0) /* Reset DWC_mobile_storage controller */
#define FIFO_RESET	(0x1 << 1) /* Reset FIFO */
#define DMA_RESET	(0x1 << 2) /* Reset DMA interface */
#define INT_ENABLE	(0x1 << 4) /* Global interrupt enable/disable bit */
#define DMA_ENABLE	(0x1 << 5) /* DMA transfer mode enable/disable bit */
#define ENABLE_IDMAC	(0x1 << 25)


#define INTMSK_ALL	0xFFFFFFFF
#define INTMSK_CDETECT	(0x1 << 0)
#define INTMSK_RE	(0x1 << 1)
#define INTMSK_CDONE	(0x1 << 2)
#define INTMSK_DTO	(0x1 << 3)
#define INTMSK_TXDR	(0x1 << 4)
#define INTMSK_RXDR	(0x1 << 5)
#define INTMSK_RCRC	(0x1 << 6)
#define INTMSK_DCRC	(0x1 << 7)
#define INTMSK_RTO	(0x1 << 8)
#define INTMSK_DRTO	(0x1 << 9)
#define INTMSK_HTO	(0x1 << 10)
#define INTMSK_VOLT_SWITCH	(0x1 << 10)
#define INTMSK_FRUN	(0x1 << 11)
#define INTMSK_HLE	(0x1 << 12)
#define INTMSK_SBE	(0x1 << 13)
#define INTMSK_ACD	(0x1 << 14)
#define INTMSK_EBE	(0x1 << 15)
#define INTMSK_DMA	(INTMSK_ACD | INTMSK_RXDR | INTMSK_TXDR)

#define INT_SRC_IDMAC	(0x0)
#define INT_SRC_MINT	(0x1)


#define CMD_RESP_EXP_BIT	(0x1 << 6)
#define CMD_RESP_LENGTH_BIT	(0x1 << 7)
#define CMD_CHECK_CRC_BIT	(0x1 << 8)
#define CMD_DATA_EXP_BIT	(0x1 << 9)
#define CMD_RW_BIT		(0x1 << 10)
#define CMD_TRANSMODE_BIT	(0x1 << 11)
#define CMD_WAIT_PRV_DAT_BIT	(0x1 << 13)
#define CMD_STOP_ABORT_CMD	(0x1 << 14)
#define CMD_SEND_INITIALIZATION	(0x1 << 15)
#define CMD_SEND_CLK_ONLY	(0x1 << 21)
#define CMD_VOLT_SWITCH     (0x1 << 28)
#define CMD_USE_HOLD_REG    (0x1 << 29)
#define CMD_STRT_BIT		(0x1 << 31)
#define CMD_ONLY_CLK		(CMD_STRT_BIT | CMD_SEND_CLK_ONLY | \
						CMD_WAIT_PRV_DAT_BIT)

#define CLK_ENABLE	(0x1 << 0)
#define CLK_DISABLE	(0x0 << 0)

#define BOARDTYPE_SFT  (1)

#define STATE_KEEP_PWR		(1)
#define STATE_LEGACY		(0)

#define SD_SLOT_VOL_OPEN 1
#define SD_SLOT_VOL_CLOSE 0

#define SDMMC_ASIC_PLATFORM  (-1)

#define DW_MCI_DATA_ERROR_FLAGS	(SDMMC_INT_DTO | SDMMC_INT_DCRC | \
				 SDMMC_INT_HTO | SDMMC_INT_SBE  | \
				 SDMMC_INT_EBE)
#define DW_MCI_CMD_ERROR_FLAGS	(SDMMC_INT_RTO | SDMMC_INT_RCRC | \
				 SDMMC_INT_RESP_ERR)
#define DW_MCI_ERROR_FLAGS	(DW_MCI_DATA_ERROR_FLAGS | \
				 DW_MCI_CMD_ERROR_FLAGS  | SDMMC_INT_HLE)

#ifdef CONFIG_MMC_DW_IDMAC
#define IDMAC_INT_CLR           (SDMMC_IDMAC_INT_AI | SDMMC_IDMAC_INT_NI | \
                                 SDMMC_IDMAC_INT_CES | SDMMC_IDMAC_INT_DU | \
                                 SDMMC_IDMAC_INT_FBE | SDMMC_IDMAC_INT_RI | \
                                 SDMMC_IDMAC_INT_TI)
#endif

#define DRIVER_NAME "dwmmc_hs"

#define DW_MCI_EMMC_ID    (0x00)
#define DW_MCI_SD_ID      (0x01)
#define DW_MCI_SDIO_ID    (0x02)

#define PERI_CRG_RSTEN4   (0x90)
#define PERI_CRG_RSTDIS4  (0x94)
#define PERI_CRG_CLKDIV4  (0xb8)
#define PERI_CRG_CLKDIV6  (0xc0)
#define HI3660_FPGA 1
#define PERI_CRG_PERSTAT4 (0x04c)

#define GTCLK_SD_EN (0x20000)

#define BIT_VOLT_OFFSET         (0x314)
#define BIT_VOLT_OFFSET_AUSTIN  (0x214)
#define BIT_VOLT_VALUE_18       (0x4)

#define BIT_RST_EMMC            (1<<20)
#define BIT_RST_SD              (1<<18)
#define BIT_RST_SDIO            (1<<19)

#define BIT_RST_SDIO_CHICAGO    (1<<20)

#define BIT_RST_SD_M      (1<<24)
#define GPIO_CLK_DIV(x) (((x) & 0xf) << 8)
#define GPIO_USE_SAMPLE_DLY(x) (((x) & 0x1) << 13)

#define GPIO_CLK_ENABLE (0x1 << 16)
#define UHS_REG_EXT_SAMPLE_PHASE(x) (((x) & 0x1f) << 16)
#define UHS_REG_EXT_SAMPLE_DLY(x) (((x) & 0x1f) << 26)
#define UHS_REG_EXT_SAMPLE_DRVPHASE(x) (((x) & 0x1f) << 21)
#define SDMMC_UHS_REG_EXT_VALUE(x, y, z)                                          \
		(UHS_REG_EXT_SAMPLE_PHASE(x) | UHS_REG_EXT_SAMPLE_DLY(y) | UHS_REG_EXT_SAMPLE_DRVPHASE(z))
#define SDMMC_GPIO_VALUE(x, y)                                              \
		(GPIO_CLK_DIV(x) | GPIO_USE_SAMPLE_DLY(y))

#define MAX_TUNING_LOOP 200

struct dw_mci_hs_priv_data {
	int				id;
	int				old_timing;
	int				gpio_cd;
	int				gpio_sw;
	int				sw_value;
	int				old_signal_voltage;
	int				old_power_mode;
	unsigned int		priv_bus_hz;
	unsigned int		cd_vol;
       unsigned int sd_slot_ldo10_status;
	int				dw_mmc_bus_clk;
	int				dw_voltage_switch_gpio;
	int				hi3660_sd_ioset_sd_sel;
	int				hi3660_sd_ioset_jtag_sd_sel;
	int				hi3660_fpga_sd_ioset;
	int				cs;
	int				in_resume;
	void __iomem *    ao_sysctrl;
	void __iomem *    peri_sysctrl;
	void __iomem *    ioc_off;
};

/* Register access macros */
#define mci_readl(dev, reg)			\
	__raw_readl((dev)->regs + SDMMC_##reg)
#define mci_writel(dev, reg, value)			\
	__raw_writel((value), (dev)->regs + SDMMC_##reg)

/* 16-bit FIFO access macros */
#define mci_readw(dev, reg)			\
	__raw_readw((dev)->regs + SDMMC_##reg)
#define mci_writew(dev, reg, value)			\
	__raw_writew((value), (dev)->regs + SDMMC_##reg)

/* 64-bit FIFO access macros */
#ifdef readq
#define mci_readq(dev, reg)			\
	__raw_readq((dev)->regs + SDMMC_##reg)
#define mci_writeq(dev, reg, value)			\
	__raw_writeq((value), (dev)->regs + SDMMC_##reg)
#else
/*
 * Dummy readq implementation for architectures that don't define it.
 *
 * We would assume that none of these architectures would configure
 * the IP block with a 64bit FIFO width, so this code will never be
 * executed on those machines. Defining these macros here keeps the
 * rest of the code free from ifdefs.
 */
#define mci_readq(dev, reg)			\
	(*(volatile u64 __force *)((dev)->regs + SDMMC_##reg))
#define mci_writeq(dev, reg, value)			\
	(*(volatile u64 __force *)((dev)->regs + SDMMC_##reg) = (value))
#endif

extern int dw_mci_probe(struct dw_mci *host);
extern void dw_mci_remove(struct dw_mci *host);
extern void dw_mci_set_cd(struct dw_mci *host);

#ifdef CONFIG_PM
extern int dw_mci_suspend(struct dw_mci *host);
extern int dw_mci_resume(struct dw_mci *host);
#endif

/**
 * struct dw_mci_slot - MMC slot state
 * @mmc: The mmc_host representing this slot.
 * @host: The MMC controller this slot is using.
 * @quirks: Slot-level quirks (DW_MCI_SLOT_QUIRK_XXX)
 * @wp_gpio: If gpio_is_valid() we'll use this to read write protect.
 * @ctype: Card type for this slot.
 * @mrq: mmc_request currently being processed or waiting to be
 *	processed, or NULL when the slot is idle.
 * @queue_node: List node for placing this node in the @queue list of
 *	&struct dw_mci.
 * @clock: Clock rate configured by set_ios(). Protected by host->lock.
 * @flags: Random state bits associated with the slot.
 * @id: Number of this slot.
 * @last_detect_state: Most recently observed card detect state.
 */
struct dw_mci_slot {
	struct mmc_host		*mmc;
	struct dw_mci		*host;

	int			quirks;
	int			wp_gpio;

	u32			ctype;

	struct mmc_request	*mrq;
	struct list_head	queue_node;

	unsigned int		clock;
	unsigned long		flags;
#define DW_MMC_CARD_PRESENT	0
#define DW_MMC_CARD_NEED_INIT	1
	int			id;
	int			last_detect_state;
	int         sdio_wakelog_switch;
};

struct dw_mci_tuning_data{
    const u8 *blk_pattern;
    unsigned int blksz;
};

/**
 * dw_mci driver data - dw-mshc implementation specific driver data.
 * @caps: mmc subsystem specified capabilities of the controller(s).
 * @init: early implementation specific initialization.
 * @setup_clock: implementation specific clock configuration.
 * @prepare_command: handle CMD register extensions.
 * @set_ios: handle bus specific extensions.
 * @parse_dt: parse implementation specific device tree properties.
 *
 * Provide controller implementation specific extensions. The usage of this
 * data structure is fully optional and usage of each member in this structure
 * is optional as well.
 */
struct dw_mci_drv_data {
	unsigned long	*caps;
	int		(*init)(struct dw_mci *host);
	int		(*setup_clock)(struct dw_mci *host);
	void		(*prepare_command)(struct dw_mci *host, u32 *cmdr);
	void		(*set_ios)(struct dw_mci *host, struct mmc_ios *ios);
	int		(*parse_dt)(struct dw_mci *host);
	int		(*cd_detect_init)(struct dw_mci *host);

	int		(*tuning_find_condition)(struct dw_mci *host, int timing);
	void		(*tuning_set_current_state)(struct dw_mci *host, int ok);
	int		(*tuning_move)(struct dw_mci *host, int timing, int start);
	int		(*slowdown_clk)(struct dw_mci *host, int timing);
	int		(*execute_tuning)(struct dw_mci_slot *slot,u32 opcode,struct dw_mci_tuning_data *tuning_data);
	int		(*start_signal_voltage_switch)(struct mmc_host *mmc,struct mmc_ios *ios);
	void		(*work_fail_reset)(struct dw_mci *host);
};
#endif /* _DW_MMC_H_ */
