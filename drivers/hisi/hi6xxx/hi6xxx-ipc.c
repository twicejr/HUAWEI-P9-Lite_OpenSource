/*
  * hi6xxx ipc driver, hi6xxx_ipc.c
  *
  * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
  *
  */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <asm/psci.h>
/*#include "mdrv_ipc.h"*/
#include <linux/hisi/hi6xxx_ipc_enum.h>
#include <linux/hisi/hi6xxx-ipc.h>                   /* For IO_ADDRESS access */
#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */
#include "soc_ipc_interface.h"

#define HISI_MAX_CPUS		(4)
#define HISI_MAX_CLUSTERS	(2)

static unsigned int core_ipc_num[HISI_MAX_CLUSTERS][HISI_MAX_CPUS] = {
    {IPC_MCU_INT_SRC_ACPU0_PD,
     IPC_MCU_INT_SRC_ACPU1_PD,
     IPC_MCU_INT_SRC_ACPU2_PD,
     IPC_MCU_INT_SRC_ACPU3_PD,
     },
     {
     IPC_MCU_INT_SRC_ACPU4_PD,
     IPC_MCU_INT_SRC_ACPU5_PD,
     IPC_MCU_INT_SRC_ACPU6_PD,
     IPC_MCU_INT_SRC_ACPU7_PD,
     }
};

static void __iomem * g_ipc_base_addr = 0;

extern int acpu_core_pd_request_state(void);
int acpu_core_pd_request_state(void)
{
    unsigned int reg = 0;
    unsigned int core_state = 0;
    int i = 0;
    reg = *(volatile int *)g_ipc_base_addr;
    /*core 0-3*/
    for(i = 0; i < 4; i++)
    {
        if(reg & (IPC_MCU_INT_SRC_ACPU0_PD + i))
			core_state |= (1 << i);
    }
    /*core 4-7*/
	for (i = 0; i < 4; i++) {
		if (reg & (IPC_MCU_INT_SRC_ACPU4_PD + i))
			core_state |= (1 << (i+4));
    }
	return core_state;
}
static void hisi_ipc_send(unsigned int ipc_num)
{
    unsigned int reg = 0;

    if(0 == g_ipc_base_addr)
    {
        printk("error ipc base is null!!!\n");
        return;
    }

    reg = BIT(ipc_num);
    *(volatile int *)g_ipc_base_addr = reg;
}

void hisi_ipc_core_suspend(unsigned int core, unsigned int cluster, unsigned int affinity_level)
{
    hisi_ipc_send(core_ipc_num[cluster][core]);
}

void hisi_ipc_pm_suspend(unsigned int core, unsigned int cluster, unsigned int affinity_level)
{
    hisi_ipc_send(IPC_MCU_INT_SRC_ACPU_PD);
}

static int __init hisi_ipc_init(void)
{
	int ret = 0;

    void __iomem *ipc_base = ioremap(SOC_IPC_S_BASE_ADDR, SZ_4K);
    g_ipc_base_addr = SOC_IPC_CPU_RAW_INT_ADDR(ipc_base, 2);

	return ret;
}

early_initcall(hisi_ipc_init);
MODULE_DESCRIPTION("Hisilicon Hi6xxx ipc driver");
MODULE_AUTHOR("wangzhenwei 00176398");
MODULE_LICENSE("GPL");
