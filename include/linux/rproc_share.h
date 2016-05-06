/*
 * Remote Processor - Histar ISP remoteproc platform data.
 *
 * Copyright (c) 2013-2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#ifndef _INCLUDE_LINUX_RPROC_SHARE_H
#define _INCLUDE_LINUX_RPROC_SHARE_H

enum rdr_enable_mask
{
    RDR_LOG_TRACE       = 0x1,
    RDR_LOG_LAST_WORD   = 0x2,
    RDR_LOG_ALGO        = 0x4,
    RDR_LOG_CVDR        = 0x8,
    RDR_LOG_IRQ         = 0x10,
};

#define A7ISP_LOG_USE_APCTRL        (1 << 31)
#define A7ISP_LOG_TIMESTAMP_FPGAMOD (1 << 30)
#define A7ISP_LOG_FORCE_UART        (1 << 29)
#define A7ISP_LOG_RESERVE_28        (1 << 28)
#define A7ISP_LOG_RESERVE_27        (1 << 27)
#define A7ISP_LOG_RESERVE_26        (1 << 26)
#define A7ISP_LOG_RESERVE_25        (1 << 25)
#define A7ISP_LOG_RESERVE_24        (1 << 24)
#define A7ISP_LOG_RESERVE_23        (1 << 23)
#define A7ISP_LOG_RESERVE_22        (1 << 22)
#define A7ISP_LOG_RESERVE_21        (1 << 21)
#define A7ISP_LOG_RESERVE_20        (1 << 20)
#define A7ISP_LOG_RESERVE_19        (1 << 19)
#define A7ISP_LOG_RESERVE_18        (1 << 18)
#define A7ISP_LOG_RESERVE_17        (1 << 17)
#define A7ISP_LOG_RESERVE_16        (1 << 16)
#define A7ISP_LOG_RESERVE_15        (1 << 15)
#define A7ISP_LOG_RESERVE_14        (1 << 14)
#define A7ISP_LOG_RESERVE_13        (1 << 13)
#define A7ISP_LOG_RESERVE_12        (1 << 12)
#define A7ISP_LOG_RESERVE_11        (1 << 11)
#define A7ISP_LOG_RESERVE_10        (1 << 10)
#define A7ISP_LOG_RESERVE_9         (1 << 9)
#define A7ISP_LOG_RESERVE_8         (1 << 8)
#define A7ISP_LOG_LEVEL_DEBUG_ALGO  (1 << 7)
#define A7ISP_LOG_LEVEL_ERR_ALGO    (1 << 6)
#define A7ISP_LOG_LEVEL_TRACE       (1 << 5)
#define A7ISP_LOG_LEVEL_DUMP        (1 << 4)
#define A7ISP_LOG_LEVEL_DBG         (1 << 3)
#define A7ISP_LOG_LEVEL_INFO        (1 << 2)
#define A7ISP_LOG_LEVEL_WARN        (1 << 1)
#define A7ISP_LOG_LEVEL_ERR         (1 << 0)
#define A7ISP_LOG_LEVEL_MASK        (0xFF)
#define A7ISP_DEFAULT_LOG_LEVEL     (A7ISP_LOG_LEVEL_ERR | A7ISP_LOG_LEVEL_WARN | A7ISP_LOG_LEVEL_INFO)

#define RDR_CHOOSE_TYPE     (RDR_LOG_TRACE | RDR_LOG_LAST_WORD)
#define IRQ_NUM             64

/*
 * struct rproc_shared_para - shared parameters for debug
 * @rdr_enable: the rdr function status
 */
struct isp_plat_cfg {
    unsigned int platform_id;
    unsigned int isp_local_timer;
    unsigned int perf_power;
};

struct bw_boot_status {
    unsigned int entry:1;
    unsigned int invalid_tlb:1;
    unsigned int enable_mmu:1;
    unsigned int reserved:29;
};

struct fw_boot_status {
    unsigned int entry:1;
    unsigned int hard_boot_init:1;
    unsigned int hard_drv_init:1;
    unsigned int app_init:1;
    unsigned int reserved:28;
};

struct rproc_shared_para {
    struct isp_plat_cfg plat_cfg;
    int rdr_enable;
    unsigned int rdr_enable_type;
    unsigned char irq[IRQ_NUM];
    int log_flush_flag;
    unsigned int log_head_size;
    unsigned int log_cache_write;
    struct bw_boot_status bw_stat;
    struct fw_boot_status fw_stat;
    unsigned int logx_switch;
	unsigned int bootware_paddr;
};

extern struct rproc_shared_para *rproc_get_share_para(void);
#endif /* _INCLUDE_LINUX_RPROC_SHARE_H */
