/*
 * drivers/mmc/host/k3v3_mmc_raw.c
 *
 * Copyright (C) 2011 Hisilicon, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */
/*lint --e{750}*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/mmc/host.h>
#include <linux/mmc/core.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sd.h>
#include <linux/io.h>
#include <linux/semaphore.h>

#include "k3v3_mmc_raw.h"

/*The macro define in *.h is better*/
/*
 * emmc reg address offset
 */
#define EMMC_REG_OFF_CTRL               (0x0)
#define EMMC_REG_OFF_PWREN              (0x4)
#define EMMC_REG_OFF_CLKDIV             (0x8)
#define EMMC_REG_OFF_CLKSRC             (0xC)
#define EMMC_REG_OFF_CLKENA             (0x10)
#define EMMC_REG_OFF_TMOUT              (0x14)
#define EMMC_REG_OFF_CTYPE              (0x18)
#define EMMC_REG_OFF_BLKSIZ             (0x1C)
#define EMMC_REG_OFF_BYTCNT             (0x20)
#define EMMC_REG_OFF_INTMSK             (0x24)
#define EMMC_REG_OFF_CMDARG             (0x28)
#define EMMC_REG_OFF_CMD                (0x2C)
#define EMMC_REG_OFF_RESP0              (0x30)
#define EMMC_REG_OFF_RESP1              (0x34)
#define EMMC_REG_OFF_RESP2              (0x38)
#define EMMC_REG_OFF_RESP3              (0x3C)
#define EMMC_REG_OFF_MINTSTS            (0x40)
#define EMMC_REG_OFF_RINTSTS            (0x44)
#define EMMC_REG_OFF_STATUS             (0x48)
#define EMMC_REG_OFF_FIFOTH             (0x4C)
#define EMMC_REG_OFF_CDETECT            (0x50)
#define EMMC_REG_OFF_WRTPRT             (0x54)
#define EMMC_REG_OFF_GPIO               (0x58)
#define EMMC_REG_OFF_TCBCNT             (0x5C)
#define EMMC_REG_OFF_TBBCNT             (0x60)
#define EMMC_REG_OFF_DEBNCE             (0x64)
#define EMMC_REG_OFF_USRID              (0x68)
#define EMMC_REG_OFF_VERID              (0x6C)
#define EMMC_REG_OFF_HCON               (0x70)
#define EMMC_REG_OFF_UHS                (0x74)
#define EMMC_REG_OFF_BMOD               (0x80)
#define EMMC_REG_OFF_DBADDR             (0x88)
#define EMMC_REG_OFF_IDSTS              (0x8c)
#define EMMC_REG_OFF_IDINTEN            (0x90)
#define EMMC_REG_OFF_UHS_REG_EXT		(0x108)
#define EMMC_REG_OFF_ENABLE_SHIFT		(0x110)
#define EMMC_REG_OFF_FIFO_START         (0x200)

/* control */
#define BIT_DMA_ENABLE                  (0x1<<5)
#define BIT_INTERNAL_DMA                (0x1<<25)

/* cmd bit */
#define BIT_CMD_RESPONSE_EXPECT         (0x1<<6)
#define BIT_CMD_LONG_RESPONSE           (0x1<<7)
#define BIT_CMD_CHECK_RESPONSE_CRC      (0x1<<8)
#define BIT_CMD_DATA_EXPECTED           (0x1<<9)
#define BIT_CMD_READ                    (0x0<<10)
#define BIT_CMD_WRITE                   (0x1<<10)
#define BIT_CMD_WAIT_PRVDATA_COMPLETE   (0x1<<13)
#define BIT_CMD_STOP_ABORT_CMD          (0x1<<14)
#define BIT_CMD_SEND_INIT               (0x1<<15)
#define BIT_CMD_START_CMD               (0x1<<31)

/* interrupt */
#define BIT_INT_HLE                     (0x1<<12)
#define BIT_INT_DTO                     (0x1<<3)
#define INT_DATA_FIFO_ERROR             (0xA280)

/* emmc status */
#define BIT_INT_DATA_BUSY               (0x1<<9)

/* clock update cmd */
#define CMD_UPDATE_CLK                  0xA0202000
#define CMD_START_BIT                   (0x1<<31)

/* time count */
#define MAX_COUNT_POLL_CMD              (500)
#define MAX_DELAY_POLL_CMD              (0xFF)
#define EMMC_RESET_ALL                  (0x7)

/* cmd defines */
#define CMD0                            0
#define CMD1                            1
#define CMD2                            2
#define CMD3                            3
#define CMD6                            6
#define CMD7                            7
#define CMD8                            8
#define CMD9                            9
#define CMD12                           12
#define CMD13                           13
#define CMD17                           17
#define CMD18                           18
#define CMD24                           24
#define CMD25                           25
#define CMD55                           55

#define EXTCSD_PARTITION_CONFIG         179
#define EXTCSD_BUS_WIDTH                183
#define EXTCSD_HS_TIMING                185

#define EMMC_FIX_RCA                    6

/*
 * ext_csd fields
 */
#define EXT_CSD_REV						192	/* RO */
#define EXT_CSD_SEC_CNT					212	/* RO, 4 bytes */

#undef DEBUG
//#define DEBUG

#ifdef DEBUG
#define DPRINTK(fmt, args...) \
	printk(fmt, ## args)
#else
#define DPRINTK(fmt, args...)
#endif

struct raw_k3v3_mmc_host {
	void *pmuioaddr;
	void *mmcioaddr;
	void *iocioaddr;
	void *scioaddr;
	void *pcioaddr;
	unsigned int clock_base;
	unsigned int f_min;
	unsigned int f_max;
	unsigned int bus_width;
	int type;
};

/* global mmc host */
static struct raw_k3v3_mmc_host emmc_host;
static struct raw_k3v3_mmc_host *kpanic_host;
static void *apanic_ioaddr;
static void *apanic_crgperi_ioaddr;

static void k3v3_mmc_dumpregs(struct raw_k3v3_mmc_host *host)
{
	printk(KERN_ERR ": ============== REGISTER DUMP ==============\n");
	printk(KERN_ERR ": MSHCI_CTRL:	  0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CTRL)));
	printk(KERN_ERR ": MSHCI_PWREN:	 0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_PWREN)));
	printk(KERN_ERR ": MSHCI_CLKDIV:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CLKDIV)));
	printk(KERN_ERR ": MSHCI_CLKSRC:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CLKSRC)));
	printk(KERN_ERR ": MSHCI_CLKENA:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CLKENA)));
	printk(KERN_ERR ": MSHCI_TMOUT:	 0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_TMOUT)));
	printk(KERN_ERR ": MSHCI_CTYPE:	 0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CTYPE)));
	printk(KERN_ERR ": MSHCI_BLKSIZ:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_BLKSIZ)));
	printk(KERN_ERR ": MSHCI_BYTCNT:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_BYTCNT)));
	printk(KERN_ERR ": MSHCI_INTMSK:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_INTMSK)));
	printk(KERN_ERR ": MSHCI_CMDARG:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CMDARG)));
	printk(KERN_ERR ": MSHCI_CMD:	   0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CMD)));
	printk(KERN_ERR ": MSHCI_MINTSTS:   0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_MINTSTS)));
	printk(KERN_ERR ": MSHCI_RINTSTS:   0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS)));
	printk(KERN_ERR ": MSHCI_STATUS:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_STATUS)));
	printk(KERN_ERR ": MSHCI_FIFOTH:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_FIFOTH)));
	printk(KERN_ERR ": MSHCI_CDETECT:   0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CDETECT)));
	printk(KERN_ERR ": MSHCI_WRTPRT:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_WRTPRT)));
	printk(KERN_ERR ": MSHCI_GPIO:	  0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_GPIO)));
	printk(KERN_ERR ": MSHCI_TCBCNT:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_TCBCNT)));
	printk(KERN_ERR ": MSHCI_TBBCNT:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_TBBCNT)));
	printk(KERN_ERR ": MSHCI_DEBNCE:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_DEBNCE)));
	printk(KERN_ERR ": MSHCI_USRID:	 0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_USRID)));
	printk(KERN_ERR ": MSHCI_VERID:	 0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_VERID)));
	printk(KERN_ERR ": MSHCI_HCON:	  0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_HCON)));
	printk(KERN_ERR ": MSHCI_UHS_REG:   0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_UHS)));
	printk(KERN_ERR ": MSHCI_BMOD:	  0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_BMOD)));
	printk(KERN_ERR ": MSHCI_DBADDR:	0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_DBADDR)));
	printk(KERN_ERR ": MSHCI_IDSTS:	 0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_IDSTS)));
	printk(KERN_ERR ": MSHCI_IDINTEN:   0x%08x\n",
		readl((void *)(host->mmcioaddr + EMMC_REG_OFF_IDINTEN)));
	/*
	   printk(KERN_ERR DRIVER_NAME ": MSHCI_FIFODAT:   0x%08x\n",
	   mshci_readl((void *)(host, MSHCI_FIFODAT)));
	 */
	printk(KERN_ERR ": ===========================================\n");
}

#if 0
static int k3v3_set_pmu_rst2n(struct raw_k3v3_mmc_host *host, unsigned int enable)
{
	if (enable) {
		writel(1, (void *)(host->pmuioaddr + PMU_RST_CTRL));
	} else {
		writel(0, (void *)(host->pmuioaddr + PMU_RST_CTRL));
	}
}

/*
 * config ldo0 power
 * 0 for power off and 1 for power on
 */
static int k3v3_sys_set_power(struct raw_k3v3_mmc_host *host, unsigned int enable)
{
	if (enable) {
		writel(BIT_6421_LDO0_EN | BIT_6421_LDO0_V285, (void *)(host->pmuioaddr + REG_OFF_LDO_ADDR));
	} else {
		writel(BIT_6421_LDO0_DIS | BIT_6421_LDO0_ECO, (void *)(host->pmuioaddr + REG_OFF_LDO_ADDR));
	}

	return 0;
}

/*
 * config iomux
 * 0 for gpio and 1 for mmc io
 */
static int k3v3_sys_set_io(struct raw_k3v3_mmc_host *host, unsigned int mode)
{
	if (mode) {

		/* iomg: func2 is emmc mode */
		writel(2, (void *)(host->iocioaddr + 0x02C));
		writel(2, (void *)(host->iocioaddr + 0x030));

		/* iocg: 6mA and pull up */
		writel(2 << 0, (void *)(host->iocioaddr + 0x88C));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x88C));
		writel(2 << 0, (void *)(host->iocioaddr + 0x890));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x890));
		writel(2 << 0, (void *)(host->iocioaddr + 0x894));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x894));
		writel(2 << 0, (void *)(host->iocioaddr + 0x898));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x898));
		writel(2 << 0, (void *)(host->iocioaddr + 0x89c));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x89c));
		writel(2 << 0, (void *)(host->iocioaddr + 0x8A0));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x8A0));
		writel(2 << 0, (void *)(host->iocioaddr + 0x8A4));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x8A4));
		writel(2 << 0, (void *)(host->iocioaddr + 0x8A8));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x8A8));

		writel(2 << 0, (void *)(host->iocioaddr + 0x8AC));
		writel((3 << 4) | (1 << 0), (void *)(host->iocioaddr + 0x8AC));
		writel(2 << 0, (void *)(host->iocioaddr + 0x8B0));
		writel((3 << 4) | (0 << 0), (void *)(host->iocioaddr + 0x8B0));	/* clk without pullup */

	} else {

		/* iomg: func2 is gpio mode */
		writel(1, (void *)(host->iocioaddr + 0x02C));
		writel(1, (void *)(host->iocioaddr + 0x030));

		/* set down out put signal */

		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x88C));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x890));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x894));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x898));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x89c));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x8A0));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x8A4));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x8A8));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x8AC));
		writel((3 << 4) | (2 << 0), (void *)(host->iocioaddr + 0x8B0));	/* clk without pullup */
	}

	return 0;
}
#endif
#if 0
/*
 * config clock
 * 0 for disable and 1 for enable
 */
static int k3v3_sys_set_clock(struct raw_k3v3_mmc_host *host, unsigned int enable)
{
	unsigned int reg_val;
	unsigned int dwLoopCount = 0;
	if (enable) {

		/* [3:  0]: 11 - 12 division */
		/* [4]  : 0 - periPLL */
		/* [5]  : 1 - PLL clock sourc */
		/* [8:6]: 0 - 1 division */
		/* [9]  : 1 - PLL clock sourc */
		/* [25  :16]: 0x3FF - mask */
//#define EMMC_SD_CLOCK_VAL ((11 << 0) | (0 << 4) | (1 << 5) | (0 << 6) | (1 << 9) | (0x3FF << 16))
#define SDSEL_VALUE (((1<<4)<<16) | (1<<4))
#define SDDIV_VALUE ((0x1E0F<<16) | (1<<12) | (1<<0) | (1<<9))

		if (DI_CHIP_ID == get_chipid()) {
			/* set sd clock to 100M and emmc clock 100M */
			reg_val = SDSEL_VALUE;
			writel(reg_val, host->scioaddr + 0x108);
			reg_val = SDDIV_VALUE;
			writel(reg_val, host->scioaddr + 0x108);
			host->clock_base = 80 * 1000 * 1000;
		} else {

			/* disable MMC1 clock */
			writel(0x1 << 21, host->scioaddr + 0x54);

			/* choose MMC1_clk 26MHz */
			writel((0x0 << 10) | (0x1 << 26), host->scioaddr + 0x108);

			/* enable MMC1 clock */
			writel(0x1 << 21, host->scioaddr + 0x50);

			// disable MMC1 clk_en
			reg_val = readl(host->pcioaddr + 0x1F8);
			reg_val = reg_val & (~BIT_PCTRL22_MMC1_CLKEN);
			writel(reg_val, host->pcioaddr + 0x1F8);

			// set MMC1 2分频 180度delay
			reg_val = readl(host->pcioaddr + 0x1F8);
			reg_val = (reg_val & 0xFF001FFF) | (0x1 << 13) | (0x1 << 16) | (0x3 << 20);
			writel(reg_val, host->pcioaddr + 0x1F8);

			// enable MMC1 clk_en
			reg_val = readl(host->pcioaddr + 0x1F8);
			reg_val = reg_val | BIT_PCTRL22_MMC1_CLKEN;
			writel(reg_val, host->pcioaddr + 0x1F8);

			host->clock_base = 13 * 1000 * 1000;
		}

		/* reset */
		writel(0x1 << 24, host->pcioaddr + 0x0A4);
		dwLoopCount = 0;
		while (dwLoopCount++ < 10) {
		}

		/* unreset */
		writel(0x1 << 24, host->pcioaddr + 0x0A8);
		dwLoopCount = 0;
		while (dwLoopCount++ < 10) {
		}

	} else {
		/* FIXME */
	}
	return 0;
}
#endif

/*
 * send mmc command
 */
static int k3v3_mmc_send_cmd(struct raw_k3v3_mmc_host *host, unsigned char cmd_index, unsigned int cmd_arg, unsigned int *resp_buffer)
{
	unsigned int reg_val;
	unsigned int loop;

	/* set up args, no check perform */
	writel(cmd_arg, (void *)(host->mmcioaddr + EMMC_REG_OFF_CMDARG));

	/* clear interrupt */
	writel(0xFFFFFFFF, (void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));

	switch (cmd_index) {
	case CMD0:
		reg_val = BIT_CMD_SEND_INIT;
		break;
	case CMD1:
		reg_val = BIT_CMD_RESPONSE_EXPECT;
		break;
	case CMD2:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_LONG_RESPONSE | BIT_CMD_CHECK_RESPONSE_CRC | BIT_CMD_SEND_INIT;
		break;
	case CMD3:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC | BIT_CMD_SEND_INIT;
		break;
	case CMD8:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC
			| BIT_CMD_DATA_EXPECTED | BIT_CMD_READ | BIT_CMD_WAIT_PRVDATA_COMPLETE;
		break;
	case CMD9:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC | BIT_CMD_LONG_RESPONSE;
		break;
	case CMD12:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC | BIT_CMD_STOP_ABORT_CMD;
		break;
	case CMD17:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC
			| BIT_CMD_DATA_EXPECTED | BIT_CMD_READ | BIT_CMD_WAIT_PRVDATA_COMPLETE;
		break;
	case CMD18:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC
			| BIT_CMD_DATA_EXPECTED | BIT_CMD_READ | BIT_CMD_WAIT_PRVDATA_COMPLETE;
		break;
	case CMD24:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC
			| BIT_CMD_DATA_EXPECTED | BIT_CMD_WRITE | BIT_CMD_WAIT_PRVDATA_COMPLETE;
		break;
	case CMD25:
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC
			| BIT_CMD_DATA_EXPECTED | BIT_CMD_WRITE | BIT_CMD_WAIT_PRVDATA_COMPLETE;
		break;
	default:
		/* default val 0x80000140 */
		reg_val = BIT_CMD_RESPONSE_EXPECT | BIT_CMD_CHECK_RESPONSE_CRC;
		break;
	}

	/* add index */
	reg_val |= cmd_index | BIT_CMD_START_CMD | (1 << 29);

	/* write to register */
	writel(reg_val, (void *)(host->mmcioaddr + EMMC_REG_OFF_CMD));

	/* wait command end */
	for (loop = 0; loop < 1000000; loop++) {

		reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));
		if (reg_val & 0x4) {
			break;
		}
	}

	if (1000 == loop) {
		printk(KERN_ERR "KPANIC_MMC: wait cd timeout\n");
		return -1;
	}

	/* check if normal result */
	/* bit1:RE;bit6:RCRC;bit8:RTO;bit12:HLE;bit15:End bit error. */
	if (reg_val & 0x9040) {
		printk(KERN_ERR "KPANIC_MMC: send cmd error 0x%x(cmd%d)\n", reg_val, cmd_index);
		return -1;
	}

	/* get resp */
	if (resp_buffer) {

		*resp_buffer = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RESP0));
		if (cmd_index == 2 || cmd_index == 9) {
			*(resp_buffer + 1) = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RESP1));
			*(resp_buffer + 2) = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RESP2));
			*(resp_buffer + 3) = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RESP3));
		}
	}

	return 0;
}

/*
 * cofind ext csd
 */
static int k3v3_mmc_update_ext_csd(struct raw_k3v3_mmc_host *host, unsigned int dwAccessIndex, unsigned int dwAccessValue)
{
	unsigned int cmd_reg;
	unsigned int resp = 0;
	unsigned int reg_val;
	unsigned int loop;
	unsigned int timeout;

	cmd_reg = (0x3 << 24) | (dwAccessIndex << 16) | (dwAccessValue << 8) | 0x1;

	k3v3_mmc_send_cmd(host, CMD6, cmd_reg, NULL);

	/* wait busy de-assert */
	for (loop = 0; loop < 100000; loop++) {
		reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_STATUS));
		if (!(reg_val & BIT_INT_DATA_BUSY)) {
			break;
		}
	}

	timeout = 1000;				/* wait 1S */

	do {
		k3v3_mmc_send_cmd(host, CMD13, EMMC_FIX_RCA << 16, &resp);

		if (resp & (1 << 7)) {
			printk(KERN_ERR "KPANIC_MMC: maybe switch eMMC mode error\n");
			return -1;
		} else {
			if (timeout) {
				timeout--;
				udelay(1);
			} else {
				printk(KERN_ERR "KPANIC_MMC: warring -- switch eMMC mode timeout\n");
				break;
			}
		}
	} while ((resp & 0x00001E00) >> 9 == 7);
	return 0;
}

/*
 * update mmc clock
 */
static int k3v3_mmc_update_clock(struct raw_k3v3_mmc_host *host)
{
	unsigned int retry_count;
	unsigned int reg_val;
	volatile unsigned int delay;

	writel(CMD_UPDATE_CLK, (void *)(host->mmcioaddr + EMMC_REG_OFF_CMD));

	/* poll result */
	for (retry_count = 0; retry_count < MAX_COUNT_POLL_CMD; retry_count++) {

		reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CMD));

		if (0 == (reg_val & CMD_START_BIT)) {
			return 0;
		}

		reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));

		if (0 != (reg_val & BIT_INT_HLE)) {
			printk(KERN_ERR "KPANIC_MMC: MMC update clock HLE ERROR\n");
			return -1;
		}

		for (delay = 0; delay < MAX_DELAY_POLL_CMD; delay++) {
			/* just delay for a while */
		}
	}

	printk(KERN_ERR "KPANIC_MMC: MMC update clock time out ERROR\n");
	return -1;
}

/*
 * set mmc clock
 */
static int k3v3_mmc_set_clock(struct raw_k3v3_mmc_host *host, unsigned int clock)
{
	unsigned int clock_div;
	volatile unsigned delay_loop = 0xFF;

	if (clock) {
		if (clock <= 400 * 1000) {
			writel(3 | (0xF << 16), (void *)(apanic_crgperi_ioaddr + 0xB4));
			writel(0, (void *)(host->mmcioaddr + EMMC_REG_OFF_GPIO));
			while (delay_loop--) {
			};

			writel(0, (void *)(host->mmcioaddr + EMMC_REG_OFF_UHS_REG_EXT));
			writel(1, (void *)(host->mmcioaddr + EMMC_REG_OFF_ENABLE_SHIFT));
			writel((1 << 16) | (9 << 8) | (1 << 12), (void *)(host->mmcioaddr + EMMC_REG_OFF_GPIO));
			host->clock_base = 36 * 1000 * 1000;
		} else {
			writel(3 | (0xF << 16), (void *)(apanic_crgperi_ioaddr + 0xB4));
			writel(0, (void *)(host->mmcioaddr + EMMC_REG_OFF_GPIO));
			while (delay_loop--) {
			};

			writel((1 << 16), (void *)(host->mmcioaddr + EMMC_REG_OFF_UHS_REG_EXT));
			writel(0, (void *)(host->mmcioaddr + EMMC_REG_OFF_ENABLE_SHIFT));
			writel((1 << 16) | (6 << 8) | (1 << 12), (void *)(host->mmcioaddr + EMMC_REG_OFF_GPIO));
			host->clock_base = 60 * 1000 * 1000;
		}

		clock_div = host->clock_base / (clock * 2);

		writel(clock_div, (void *)(host->mmcioaddr + EMMC_REG_OFF_CLKDIV));
		writel(0, (void *)(host->mmcioaddr + EMMC_REG_OFF_CLKSRC));
		writel(1, (void *)(host->mmcioaddr + EMMC_REG_OFF_CLKENA));
	} else {
		writel(0, (void *)(host->mmcioaddr + EMMC_REG_OFF_CLKDIV));
		writel(0, (void *)(host->mmcioaddr + EMMC_REG_OFF_CLKSRC));
		writel(0, (void *)(host->mmcioaddr + EMMC_REG_OFF_CLKENA));
	}

	return k3v3_mmc_update_clock(host);

}

/*
 * Set clock rate and bus width
 */
static int k3v3_mmc_set_clock_and_width(struct raw_k3v3_mmc_host *host, unsigned int clock, unsigned int bus_width)
{
	int ret = 0;

	switch (bus_width) {
	case 0:
		writel(0x0, (void *)(host->mmcioaddr + EMMC_REG_OFF_CTYPE));
		//ret = k3v3_mmc_update_ext_csd(host, EXTCSD_BUS_WIDTH, 0);
		break;
#if 0
	case 4:
		writel(0x1, EMMC_REG_OFF_CTYPE);
		ret = emmc_update_ext_csd(EXTCSD_BUS_WIDTH, 1);
		/* writel(0x1<<16, EMMC_REG_OFF_UHS); */
		break;
#endif
	case 8:
		writel(0x1 << 16, (void *)(host->mmcioaddr + EMMC_REG_OFF_CTYPE));
		//!!!ddr ->sdr
		ret = k3v3_mmc_update_ext_csd(host, EXTCSD_BUS_WIDTH, (2));
		writel(0x0 << 16, (void *)(host->mmcioaddr + EMMC_REG_OFF_UHS));
		break;

	default:
		printk(KERN_ERR "KPANIC_MMC: default %s:%d\n", __FUNCTION__, __LINE__);
		return -1;
	}

	if (ret) {
		printk(KERN_ERR "KPANIC_MMC:%s:%d\n", __FUNCTION__, __LINE__);
		return ret;
	}
#if 0
	if (CS_CHIP_ID == get_chipid()) {
		reg_val = 0x07E00420;
		writel(reg_val, host->scioaddr + 0x108);

		// disable MMC1 clk_en
		reg_val = readl(host->pcioaddr + 0x1F8);
		reg_val = reg_val & (~BIT_PCTRL22_MMC1_CLKEN);
		writel(reg_val, host->pcioaddr + 0x1F8);

		// set MMC1 2分频 180度delay
		reg_val = readl(host->pcioaddr + 0x1F8);
		reg_val = (reg_val & 0xFF001FFF) | (0x6 << 13) | (0x4 << 16) | (0x6 << 20);
		writel(reg_val, host->pcioaddr + 0x1F8);

		// enable MMC1 clk_en
		reg_val = readl(host->pcioaddr + 0x1F8);
		reg_val = reg_val | BIT_PCTRL22_MMC1_CLKEN;
		writel(reg_val, host->pcioaddr + 0x1F8);

		host->clock_base = 100 * 1000 * 1000;
	}
#endif
	/* Disable clk */
	ret = k3v3_mmc_set_clock(host, 0);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: disable clock failed\n");
		return ret;
	}

	/* set clock and enable clock */
	ret = k3v3_mmc_set_clock(host, clock);
	if (ret) {
		printk("[msl][%s]: set clock %d failed\n", __func__, clock);
		return -1;
	}

	return 0;
}

/*
 * check emmc mode is tran
 */
static int k3v3_mmc_check_tran_mode(struct raw_k3v3_mmc_host *host)
{
	int ret;
	unsigned int resp = 0;
	unsigned int loop;

	writel(0xFFFF, (void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));

	for (loop = 0; loop < 1000; loop++) {
		ret = k3v3_mmc_send_cmd(host, CMD13, EMMC_FIX_RCA << 16, &resp);
		if (ret) {
			printk(KERN_ERR "KPANIC_MMC: send cmd13 failed, loop:0x%x\n", loop);
		}
		DPRINTK("KPANIC_MMC: resp for cmd13:0x%x", resp);
		if (((resp >> 9) & 0xf) == 4)
			return 0;
	}

	printk(KERN_ERR "KPANIC_MMC: card mode %d\n", ((resp >> 9) & 0xf));
	return -1;
}

#if 1
/*
 * reset emmc ip
 */
static int k3v3_mmc_reset_ip(struct raw_k3v3_mmc_host *host)
{
	volatile u32 reg_val;
	unsigned int loop;

	/* ip: reset all */
	reg_val = EMMC_RESET_ALL;

	writel(reg_val, host->mmcioaddr + EMMC_REG_OFF_CTRL);

	loop = 0;
	do {
		reg_val = readl(host->mmcioaddr + EMMC_REG_OFF_CTRL);
		if (loop <= 0x10000) {
			loop++;
		} else {
			printk(KERN_ERR "KPANIC_MMC: reset ip timeout\n");
			break;
		}
	} while (reg_val != 0);

	/* interrupt mask */
	writel(0x00000000, host->mmcioaddr + EMMC_REG_OFF_INTMSK);
	writel(0xFFFFFFFF, host->mmcioaddr + EMMC_REG_OFF_RINTSTS);
	writel(0xFFFFFFFF, host->mmcioaddr + EMMC_REG_OFF_IDINTEN);
	writel(0xFFFFFFFF, host->mmcioaddr + EMMC_REG_OFF_IDSTS);

#if 0
	/* config io */
	k3v3_sys_set_io(host, 1);

	/* power on */
	k3v3_sys_set_power(host, 1);
	mdelay(50);

	/* set rst2n high */
	k3v3_set_pmu_rst2n(host, 1);

	if (k3v3_mmc_set_clock(host, host->f_min)) {
		printk(KERN_ERR "KPANIC_MMC: k3v3_mmc_set_clock f_min failed\n");
	}
#endif
	/* bit mode: 1 bit */
	writel(0x0, host->mmcioaddr + EMMC_REG_OFF_CTYPE);

	/* non-DDR mode */
	writel(0x0, host->mmcioaddr + EMMC_REG_OFF_UHS);

	/* data time out */
	writel(0xFFFFFFFF, host->mmcioaddr + EMMC_REG_OFF_TMOUT);

	/* debounce time out */
	writel(0xFFFFFFFF, host->mmcioaddr + EMMC_REG_OFF_DEBNCE);

	/* clear bmod */
	writel(0, host->mmcioaddr + EMMC_REG_OFF_BMOD);

	/* fifo config */
	reg_val = (0x3F) << 16 | (0x40);
	writel(reg_val, host->mmcioaddr + EMMC_REG_OFF_FIFOTH);

	DPRINTK(KERN_ERR "KPANIC-MMC: EMMC_REG_OFF_FIFOTH:0x%x\n", reg_val);

	return 0;
}
#endif
/*
 * write function
 */
static int k3v3_mmc_write(char *buf, sector_t start_sect, sector_t nr_sects, unsigned int offset, unsigned int len)
{
	struct raw_k3v3_mmc_host *host;
	int ret = 0;
	unsigned int reg_val;
	unsigned int written_len;
	unsigned int total_len;
	unsigned int temp_len;
	unsigned int loop;

	host = &emmc_host;

	if (!len)
		return 0;

	if (offset + len > nr_sects * 512) {
		printk(KERN_ERR "KPANIC-MMC: writing buf too long for " "the partition\n");
		return 0;
	}

	if (offset % 512 != 0) {
		printk(KERN_ERR "KPANIC-MMC: writing offset not aligned to " "sector size\n");
		return 0;
	}

	writel(512, (void *)(host->mmcioaddr + EMMC_REG_OFF_BLKSIZ));
	writel(len, (void *)(host->mmcioaddr + EMMC_REG_OFF_BYTCNT));

	/* clear raw int */
	writel(0xFFFFFFFF, (void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));

	/* FIXME */
	/* how to disable dma */
	writel((readl((void *)(host->mmcioaddr + EMMC_REG_OFF_CTRL)) & (~(BIT_DMA_ENABLE | BIT_INTERNAL_DMA))), (void *)(host->mmcioaddr + EMMC_REG_OFF_CTRL));
	/* we assume emmc is addressed by block */
	ret = k3v3_mmc_send_cmd(host, CMD25, start_sect + (offset / 512), NULL);
	if (ret) {
		printk(KERN_ERR "KPANIC-MMC: send cmd25 failed");
		writel(0xFFFFFFFF, (void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));
		return -1;
	}
	for (loop = 0; loop < 1000; loop++) {

		reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));
		DPRINTK(KERN_ERR "KPANIC_MMC: cmd25 raw intr:0x%x\n", reg_val);
		if (reg_val & 0x4) {
			break;
		}
	}

	/* poll data */
	written_len = 0;
	total_len = len;
	while (written_len < total_len) {
		reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_STATUS));
		reg_val = (reg_val & (0x1FFF << 17)) >> 17;
		temp_len = 512 - reg_val * 4;
		if (temp_len > (total_len - written_len))
			temp_len = (total_len - written_len);
		for (loop = 0; loop < temp_len; loop += 4) {
			writel(*(unsigned int *)(buf + written_len + loop), (void *)(host->mmcioaddr + EMMC_REG_OFF_FIFO_START));
		}
		written_len += temp_len;
	}

	/* poll dto */
	while (((reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS))) & BIT_INT_DTO) == 0) {
		/* got error */
	}

	/* check error */
	reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));

	// 0x809c
	if (reg_val & 0xA280) {
		/* got error */
		printk(KERN_ERR "KPANIC-MMC: send CMD v001 error:0x%x\n", reg_val);
		writel(0xFFFFFFFF, (void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));
		return -1;
	}

	ret = k3v3_mmc_send_cmd(host, CMD12, EMMC_FIX_RCA << 16, NULL);
	if (ret) {
		printk(KERN_ERR "KPANIC-MMC: send CMD12 failed");
		writel(0xFFFFFFFF, (void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));
		return -1;
	}

	/* check error 7,9,13,15, do not check crc error */
	reg_val = readl((void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));
	if (reg_val & 0xA280) {
		/* got error */
		printk(KERN_ERR "KPANIC-MMC: send CMD12 error:0x%x\n", reg_val);
		writel(0xFFFFFFFF, (void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));
		return -1;
	}

	while (1) {
		if (!(readl((void *)(host->mmcioaddr + EMMC_REG_OFF_STATUS)) & BIT_INT_DATA_BUSY)) {
			break;
		}
	}

	writel(0xFFFFFFFF, (void *)(host->mmcioaddr + EMMC_REG_OFF_RINTSTS));

	if (k3v3_mmc_check_tran_mode(host)) {
		printk(KERN_ERR "KPANIC-MMC: check_status failed\n");
		return -1;
	}

	return len;
}

/*
 * init mmc card
 */
static int k3v3_mmc_set_ready(struct raw_k3v3_mmc_host *host)
{
	unsigned int resp_buf[4];
	unsigned int ret;
	unsigned int loop;

	ret = k3v3_mmc_set_clock_and_width(host, host->f_min, 0);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: set_clock_and_width(%d , 0) failed\n", host->f_min);
		return ret;
	}

	/* 1 bit mode */
	// already done above
	//writel(0, host->mmcioaddr + EMMC_REG_OFF_CTYPE);

	/* cmd0 : IDLE */
	ret = k3v3_mmc_send_cmd(host, CMD0, 0, NULL);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: send cmd0 failed\n");
		return ret;
	}

	/* cmd1 : READY */
	for (loop = 0; loop < 1000; loop++) {

		ret = k3v3_mmc_send_cmd(host, CMD1, 0x40ff8000, resp_buf);
		if (ret) {
			printk(KERN_ERR "KPANIC_MMC: send cmd1 failed, loop:0x%x\n", loop);
			return ret;
		}

		/* wait for busy */
		if (resp_buf[0] & 0x80000000)
			break;
		mdelay(1);
	}
	if (1000 == loop) {
		printk(KERN_ERR "KPANIC_MMC: send cmd1 reach max time\n");
		return -1;
	}

	/* cmd2 : IDENT */
	ret = k3v3_mmc_send_cmd(host, CMD2, 0, resp_buf);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: send cmd2 failed\n");
		return ret;
	}

	/* CMD3 : STBY  */
	ret = k3v3_mmc_send_cmd(host, CMD3, EMMC_FIX_RCA << 16, resp_buf);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: send cmd3 failed\n");
		return ret;
	}

	/* CMD9 : get CSD */
	ret = k3v3_mmc_send_cmd(host, CMD9, EMMC_FIX_RCA << 16, resp_buf);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: send cmd9 failed\n");
		return ret;
	}

	/* CMD7 : TRAN */
	ret = k3v3_mmc_send_cmd(host, CMD7, EMMC_FIX_RCA << 16, NULL);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: send cmd7 failed\n");
		return ret;
	}
	/* END : Check */
	ret = k3v3_mmc_check_tran_mode(host);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: check_tran_mode failed\n");
		return ret;
	}
	/* high speed mode */
	ret = k3v3_mmc_update_ext_csd(host, EXTCSD_HS_TIMING, 1);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: EXTCSD_HS_TIMING failed\n");
		return ret;
	}
	//if (DI_CHIP_ID == get_chipid()) {
	//  /* add for k3v3: set delay sel */
	//  writel(0xF0, host->scioaddr+0x064);
	//  writel(0x79, host->scioaddr+0x060);
	//}

	ret = k3v3_mmc_set_clock_and_width(host, host->f_max, host->bus_width);
	if (ret) {
		printk(KERN_ERR "KPANIC_MMC: set_clock_and_width failed\n");
		return ret;
	}
	return 0;
}

/*
 * You never know current state of eMMC card when panic happens
 * So need a clear startup
 */
static int k3v3_mmc_probe(struct raw_hd_struct *rhd)
{
	/* need to check the start_sector and nr_sector value are valid */
	struct raw_k3v3_mmc_host *host;
	int ret = 0;

	DPRINTK(KERN_ERR "KPANIC-MMC: probe eMMC chip\n");

	kpanic_host = &emmc_host;	/* detect eMMC, then detect SD case */
	host = &emmc_host;
	memset(host, 0, sizeof(emmc_host));
	if (apanic_ioaddr == 0)
		return -ENOMEM;

	/* no more might_sleep after this point */
	local_irq_disable();

#if 0
	/* init pmu address */
	host->pmuioaddr = IO_ADDRESS_PMU;
	host->mmcioaddr = IO_ADDRESS_EMMC;
	host->iocioaddr = IO_ADDRESS_IOC;
	host->scioaddr = IO_ADDRESS_SC;
	host->pcioaddr = IO_ADDRESS_PC;
	host->f_min = 400 * 1000;	/* 400K */
	if (DI_CHIP_ID == get_chipid())
		host->f_max = 40 * 1000 * 1000;	/* 25M */
	else
		host->f_max = 50 * 1000 * 1000;	/* 25M */
	host->bus_width = 8;		/* 8bit */
	host->type = MMC_TYPE_MMC;	/* mmc */

	/* config io */
	k3v3_sys_set_io(host, 0);

	/* set rst2n low */
	k3v3_set_pmu_rst2n(host, 0);
	mdelay(50);

	/* power off */
	k3v3_sys_set_power(host, 0);
	mdelay(40);

	/* enable clock */
	k3v3_sys_set_clock(host, 1);

	/* reset ip */
	k3v3_mmc_reset_ip(host);

#else
	host->f_min = 400 * 1000;
	host->f_max = 8 * 1000 * 1000;
	host->mmcioaddr = apanic_ioaddr;
	host->bus_width = 8;		/* 8bit */
	host->type = MMC_TYPE_MMC;	/* mmc */
	host->clock_base = 32 * 1000 * 1000;
#endif
	writel((0x1 << 17), (void *)(apanic_crgperi_ioaddr + 0x94));
	writel((0x1 << 16), (void *)(apanic_crgperi_ioaddr + 0x40));
	writel((0x1 << 2 | ((0x1 << 2) << 16)), (void *)(apanic_crgperi_ioaddr + 0xF4));
	k3v3_mmc_reset_ip(host);
	ret = k3v3_mmc_set_ready(host);
	if (ret) {
		k3v3_mmc_dumpregs(host);
	}

	return ret;
}

/*
 * raw_mmc_panic_probe
 */
int raw_mmc_panic_probe(struct raw_hd_struct *rhd, int type)
{

	if (type == MMC_TYPE_MMC)
		return k3v3_mmc_probe(rhd);
#if 0
	else if (type == MMC_TYPE_SD)
		return raw_mmc_probe_usd(rhd);
#endif
	else
		return -1;
}

/*
 * raw_mmc_panic_write
 */
int raw_mmc_panic_write(struct raw_hd_struct *rhd, char *buf, unsigned int offset, unsigned int len)
{
	return k3v3_mmc_write(buf, rhd->start_sect, rhd->nr_sects, offset, len);
}

/*
 * offset and len should be aligned to 512
 */
int raw_mmc_panic_erase(struct raw_hd_struct *rhd, unsigned int offset, unsigned int len)
{
	int ret = -1;

	if (!kpanic_host) {
		printk(KERN_ERR "KPANIC_MMC: no card probed\n");
		return -1;
	}
	if ((offset % 512) || (len % 512)) {
		printk(KERN_ERR "KPANIC_MMC: non-aligned erase\n");
		return -1;
	}
	if ((offset + len) / 512 > rhd->nr_sects) {
		printk(KERN_ERR "KPANIC_MMC: out of range erase\n");
		return -1;
	}
	if (!len)
		return 0;

	if (kpanic_host->type == MMC_TYPE_MMC)
		ret = -1;
#if 0
	else if (kpanic_host->card.type == MMC_TYPE_SD)
		ret = raw_sd_erase(kpanic_host, rhd->start_sect + offset / 512, len / 512);
#endif
	else
		printk(KERN_ERR "KPANIC_MMC: card.type not recognized %d\n", kpanic_host->type);

	if (ret)
		printk(KERN_ERR "KPANIC_MMC: erase mmc/SD failed\n");

	return ret;
}

static int __init raw_mmc_panic_init(void)
{
	apanic_ioaddr = (void *)ioremap_nocache(0xFF1FE000, 0x1000);

	if (apanic_ioaddr == 0) {
		printk(KERN_ERR "remap mmc controler addr failed\n");
		return -1;
	} else {
		printk(KERN_INFO "remap mmc controler addr succeed\n");
	}
	apanic_crgperi_ioaddr = (void *)ioremap_nocache(0xFFF35000, 0x1000);

	if (apanic_crgperi_ioaddr == 0) {
		printk(KERN_ERR "remap crgperi addr failed\n");
		return -1;
	} else {
		printk(KERN_INFO "remap crgperi addr succeed\n");
	}

	return 0;
}

static void __exit raw_mmc_panic_exit(void)
{
	return;
}

arch_initcall(raw_mmc_panic_init);
module_exit(raw_mmc_panic_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yuqing <hw.liuyuqing@hisilicon.com>");
MODULE_DESCRIPTION("kernel run panic record");
