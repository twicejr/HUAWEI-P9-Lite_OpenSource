/*
 * Remote Processor - Histar ISP remoteproc platform data.
 * include/linux/platform_data/remoteproc-hisi.h
 *
 * Copyright (c) 2013-2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _PLAT_REMOTEPROC_HISI_ISP_H
#define _PLAT_REMOTEPROC_HISI_ISP_H

struct rproc_ops;
struct platform_device;

/*
 * struct omap_rproc_pdata - omap remoteproc's platform data
 * @name: the remoteproc's name
 * @oh_name: omap hwmod device
 * @oh_name_opt: optional, secondary omap hwmod device
 * @firmware: name of firmware file to load
 * @mbox_name: name of omap mailbox device to use with this rproc
 * @ops: start/stop rproc handlers
 * @device_enable: omap-specific handler for enabling a device
 * @device_shutdown: omap-specific handler for shutting down a device
 * @set_bootaddr: omap-specific handler for setting the rproc boot address
 */

struct hisi_rproc_data {
    const char *name;
    const char *firmware;
	const char *bootware;
    const char *mbox_name;
    const struct rproc_ops *ops;
    unsigned int ipc_addr;
    int (*device_enable) (struct platform_device *pdev);
    int (*device_shutdown) (struct platform_device *pdev);
    void(*set_bootaddr)(u32);
};

#endif /* _PLAT_REMOTEPROC_HISI_ISP_H */

