/*
 * record the data to rdr. (RDR: kernel run data recorder.)
 * This file wraps the ring buffer.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _BLACKBOX_PLATFORM_ISP_RDR_HISI_ISP_H
#define _BLACKBOX_PLATFORM_ISP_RDR_HISI_ISP_H

/* sync data */
#define RDR_ISP_MAGIC       0x66668888
#define RDR_ISP_SYNC        0x88886666
#define RDR_SYNC_WORD_OFF   0x4

#define ISP_WDT_IRQ     304
#define MODULE_NAME     "RDR ISP"
#define SYSCTL_ADDR     0xfff0a000
#define SC_WDT_OFFSET   0x33c
#define SC_ISP_WDT_BIT  6
#define PCTRL_ADDR      0xe8a09000
#define PCTRL_ISP_FIQ   0x70
#define WDT_ISP_ADDR    0xe8580000
#define WDT_ENABLE_CTL  0x008
#define WDT_LOCK_CTL    0xc00
#define WDT_LOCK        0x1
#define WDT_UNLOCK      0x1acce551

#define SHOW_SIZE       0x1000
#define TRACE_ON        "trace_on"
#define TRACE_OFF       "trace_off"
#define LAST_WD_ON      "last_wd_on"
#define LAST_WD_OFF     "last_wd_off"
#define ALGO_ON         "algo_on"
#define ALGO_OFF        "algo_off"
#define CVDR_ON         "cvdr_on"
#define CVDR_OFF        "cvdr_off"
#define IRQ_ON          "irq_on"
#define IRQ_OFF         "irq_off"
#define SIRQ_ON         "sirq_on"
#define SIRQ_OFF        "sirq_off"

extern u32 g_isp_rdr_addr;

#endif /* _BLACKBOX_PLATFORM_ISP_RDR_HISI_ISP_H */
