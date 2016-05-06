/*
 * hisi_6402_irq.h  --  Interrupt controller support for Hisilicon HI6402
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef	__HI6402_IRQ_H__
#define	__HI6402_IRQ_H__

#include <linux/clk.h>
#include <linux/irqdomain.h>
#include <linux/mutex.h>
#include <linux/wakelock.h>
#include <linux/regulator/consumer.h>

#define HI6402_MAX_IRQS 32
enum bustype_select {
    BUSTYPE_SELECT_SLIMBUS = 1,
    BUSTYPE_SELECT_SSI,
};

enum hi6402_pll_status {
	HI6402_PLL_PD,
	HI6402_PLL_HIGH_FREQ,
	HI6402_PLL_LOW_FREQ,
	HI6402_PLL_RST,
};

/* hi6402 register operation function struct */
struct hi6402_reg_ops {
    int  (*read_1byte)(void *pdata, unsigned int reg);
    int  (*read_4byte)(void *pdata, unsigned int reg);
    void (*write_1byte)(void *pdata, unsigned int reg, unsigned int val);
    void (*write_4byte)(void *pdata, unsigned int reg, unsigned int val);
};

struct hi6402_irq {
	struct resource		*res;
	struct irq_domain	*domain;
	void __iomem		*reg_base_addr;
	unsigned int		mm_reg;
	struct clk		*pmu_audio_clk;

	struct regulator    *digital_power_supply;

	spinlock_t		lock;
	int			irq;
	int			gpio;
	int			rst;
	unsigned int		irqs[HI6402_MAX_IRQS];
	unsigned int runtime_suspended;
	struct device		*dev;

	struct workqueue_struct	*hi6402_micbias_delay_wq;
	struct delayed_work	hi6402_micbias_delay_work;

	struct mutex		rw_mutex;
	struct mutex		handler_mutex;
	struct mutex		sr_mutex;
	struct mutex		irq_lock;
	struct wake_lock	wake_lock;

	u8			mask0;
	u8			mask1;
	u8			mask2;
	u8			mask3;
	u8			irq0;
	u8			irq1;
	u8			irq2;
	u8			irq3;

	bool			mbhc_micbias_work;
	bool			dapm_micbias_work;
	int			dapm_ibias_work;
	bool			mbhc_ibias_work;

	struct mutex		ibias_mutex;
	struct mutex		pll_mutex;
	struct mutex		hs_micbias_mutex;
	int			ref_pll;
	int			ref_low_pll;
	enum hi6402_pll_status pll_status;
	bool			hifi_misc_probe;
	bool			reset_system_flag;
};

/* Register Access Helpers */
u32 hi6402_irq_read(struct hi6402_irq *irq, unsigned int reg);
void hi6402_irq_write(struct hi6402_irq *irq, unsigned int reg, u32 val);
void hi6402_reg_set_bit(struct hi6402_irq *irq, unsigned int reg, unsigned int offset);
void hi6402_reg_clr_bit(struct hi6402_irq *irq, unsigned int reg, unsigned int offset);
void hi6402_reg_write_bits(struct hi6402_irq *irq, unsigned int reg, unsigned int value, unsigned int mask);
void hi6402_irq_ibias_work_enable(struct hi6402_irq *irq, bool enable);
void hi6402_irq_micbias_work_enable(struct hi6402_irq *irq, bool enable);
void hi6402_irq_micbias_mbhc_enable(struct hi6402_irq *irq, bool enable);
void hi6402_irq_high_freq_pll_enable(struct hi6402_irq *irq, bool enable);
void hi6402_irq_low_freq_pll_enable(struct hi6402_irq *irq, bool enable);
void hi6402_pll_pd(struct hi6402_irq *irq);
void hi6402_irq_set_pll_mode(struct hi6402_irq *irq);
void hi6402_irq_clr_btn_irqs(struct hi6402_irq *irq);
void hi6402_irq_mask_btn_irqs(struct hi6402_irq *irq);
void hi6402_irq_unmask_btn_irqs(struct hi6402_irq *irq);
void hi6402_irq_hs_micbias_enable(struct hi6402_irq *irq, bool enable);
void hi6402_irq_cancel_delay_work(struct hi6402_irq *irq);

#endif		/* __HI6402_IRQ_H__ */
