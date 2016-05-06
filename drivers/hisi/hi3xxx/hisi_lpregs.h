/*
 * The codes for io debugging, and could checkout unexpected
 * status of all io/clk/pmu before system into SUSPEND.
 *
 * Copyright (C) 2013-2014 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
#ifndef	__HISI_LPREGS_H
#define	__HISI_LPREGS_H

struct pmuregs {
	unsigned int ucoffset;
	unsigned int cval;
	unsigned int old_val;
	unsigned int cmask;
};

#define PERI_EN_CLOSE	(1 << 0)
#define PERI_EN_ECO		(1 << 1)
#define LPM3_DIS		(1 << 2)
#define AP_DIS			(1 << 3)
#define CLK_EN_CLOSE	(1 << 4)
#define NULL_OWNER		(1 << 5)
#define SOFT_ECO		(1 << 6)
struct pmu_idx {
	char *name;
	char *module;
	unsigned int status;
	char *status_name;
};

extern void pm_status_show(struct seq_file *s);
extern void pm_nvic_pending_dump(void);
extern void dbg_io_status_show(void);
extern void dbg_pmu_status_show(void);
extern void dbg_clk_status_show(void);
extern void debuguart_reinit(void);

#endif
