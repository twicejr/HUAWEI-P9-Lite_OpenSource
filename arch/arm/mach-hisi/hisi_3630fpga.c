/*
 * (Hisilicon's hi3630 board) flattened device tree enabled machine
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/smp.h>
#include <linux/memblock.h>
#include <linux/irqchip.h>
#include <linux/cache.h>
#include <asm/hardware/arm_timer.h>
#include <asm/arch_timer.h>
#include <asm/hardware/timer-sp.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>
#include <asm/smp_plat.h>
#include <asm/smp_twd.h>
#include <asm/proc-fns.h>
#include <asm/sched_clock.h>
#include <asm/cacheflush.h>
#include <linux/of_device.h>
#ifdef CONFIG_MCPM
#include <asm/mcpm.h>
#endif

#ifdef CONFIG_HISI_REBOOT_TYPE
/* be careful:: shoule be the same as defined in fastboot*/
/* there are only 4 bit for reboot_type;
 * U can use the reserved number to add the new command*/
enum {
	REBOOT_BOOTLOADER_CMDNUM = 1,	/*1*/
	REBOOT_RECOVERY_CMDNUM,		/*2*/
	REBOOT_RESETFACTORY_CMDNUM,	/*3*/
	REBOOT_RESETUSER_CMDNUM,	/*4*/
	REBOOT_SDUPDATE_CMDNUM,		/*5*/
	REBOOT_PANIC_CMDNUM,		/*6*/
	REBOOT_RES_0,			/*7*/
	REBOOT_RES_1,			/*8*/
	REBOOT_USBUPDATE_CMDNUM,	/*9*/
	REBOOT_RES_2,			/*10*/
	REBOOT_RES_3,			/*11*/
	REBOOT_RES_4,			/*12*/
	/*be careful: the define of cold reboot is different from k3v2*/
	REBOOT_COLDBOOT_CMDNUM,		/*13*/
	REBOOT_RES_6,			/*14*/
	/*be careful: this is the new one in k3v3*/
	REBOOT_WATCHDOG_CMDNUM,		/*15*/
};

#define PANIC_FLAG					(0x1 << 4)
#define PANIC_FLAG_MASK				(0x3 << 4)

#define REBOOT_COLDBOOT_STR		"coldboot"
#define REBOOT_BOOTLOADER_STR		"bootloader"
#define REBOOT_RECOVERY_STR		"recovery"
#define REBOOT_RESETUSER_STR		"resetuser"
#define REBOOT_RESETFACTORY_STR		"resetfactory"
#define REBOOT_SDUPDATE_STR		"sdupdate"
#define REBOOT_USBUPDATE_STR		"usbupdate"
#define REBOOT_PANIC_STR		"panic"
#endif

#define HISI_RESERVED_MEM_START 0x2D000000
#define HISI_RESERVE_MEM_SIZE (0x40000000 - HISI_RESERVED_MEM_START)

unsigned long hisi_reserved_idle_framebuffer_phymem = 0x2D000000;
unsigned long hisi_reserved_smmu_phymem = 0x2DA00000;
unsigned long hisi_reserved_audio_phymem = 0x2DC00000;
unsigned long hisi_reserved_iom3_phymem = 0x2DE00000;
unsigned long hisi_reserved_secure_os_phymem = 0x2E000000;
unsigned long hisi_reserved_modem_phymem = 0x30000000;
unsigned long hisi_reserved_modem_share_phymem = 0x36400000;
unsigned long hisi_reserved_debug_socp_phymem = 0x36700000;
unsigned long hisi_reserved_hifi3_phymem = 0x37700000;
unsigned long hisi_reserved_graphic_phymem = 0x38000000;
unsigned long hisi_reserved_debug_phymem = 0x3F800000;


EXPORT_SYMBOL(hisi_reserved_idle_framebuffer_phymem);
EXPORT_SYMBOL(hisi_reserved_smmu_phymem);
EXPORT_SYMBOL(hisi_reserved_audio_phymem);
EXPORT_SYMBOL(hisi_reserved_iom3_phymem);
EXPORT_SYMBOL(hisi_reserved_secure_os_phymem);
EXPORT_SYMBOL(hisi_reserved_modem_phymem);
EXPORT_SYMBOL(hisi_reserved_modem_share_phymem);
EXPORT_SYMBOL(hisi_reserved_debug_socp_phymem);
EXPORT_SYMBOL(hisi_reserved_hifi3_phymem);
EXPORT_SYMBOL(hisi_reserved_graphic_phymem);
EXPORT_SYMBOL(hisi_reserved_debug_phymem);

/* be careful: the strings of reset type  should be the same as defined in fastboot*/
#define RESETMODE_FLAG_ABNORMAL (1)
#define RESETMODE_FLAG_NORMAL	(0)

static unsigned int resetmode_normal = RESETMODE_FLAG_NORMAL;

static int __init early_parse_resetmode_cmdline(char *p)
{
	if (p) {
		if ((!strcmp(p, "press10s,")) || \
			(!strcmp(p, "press1s,")) || \
			(!strcmp(p, "ColdReset,")) || \
			(!strcmp(p, "PoweroffAlarm,"))) {
			resetmode_normal = RESETMODE_FLAG_NORMAL;
			printk("resetmode is %s, resetmode_normal = %d\n", p, resetmode_normal);
		} else if ((!strcmp(p, "PanicReset,")) || (!strcmp(p, "AbnormalReset,"))) {
			resetmode_normal = RESETMODE_FLAG_ABNORMAL;
			printk("resetmode is %s resetmode_normal = %d\n", p, resetmode_normal);
		} else
			printk("Judge resetmode error! \n");
	}
	return 0;
}

early_param("normal_reset_type", early_parse_resetmode_cmdline);
unsigned int resetmode_is_normal(void)
{
	return resetmode_normal;
}

EXPORT_SYMBOL(resetmode_is_normal);


static void __init hisi_timer_init(void)
{
	of_clk_init(NULL);
	clocksource_of_init();
}

static void hisi_reserve(void)
{
	printk("reserved memory start at 0x%x, which size is 0x%x\n",
			HISI_RESERVED_MEM_START, HISI_RESERVE_MEM_SIZE);

	memblock_remove(HISI_RESERVED_MEM_START, HISI_RESERVE_MEM_SIZE);
}

static void __init hisi_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

bool __init hisi_smp_init_ops(void)
{
#ifdef CONFIG_MCPM
	mcpm_smp_set_ops();
	return true;
#endif
	return false;
}

#ifdef CONFIG_HISI_REBOOT_TYPE
struct reboot_cmdword {
	char *name;
	unsigned int num;
};

static struct reboot_cmdword reboot_cmd_map[] = {
	{ REBOOT_COLDBOOT_STR, REBOOT_COLDBOOT_CMDNUM },
	{ REBOOT_BOOTLOADER_STR, REBOOT_BOOTLOADER_CMDNUM },
	{ REBOOT_RECOVERY_STR, REBOOT_RECOVERY_CMDNUM },
	{ REBOOT_RESETFACTORY_STR, REBOOT_RESETFACTORY_CMDNUM },
	{ REBOOT_RESETUSER_STR, REBOOT_RESETUSER_CMDNUM },
	{ REBOOT_SDUPDATE_STR, REBOOT_SDUPDATE_CMDNUM },
	{ REBOOT_USBUPDATE_STR, REBOOT_USBUPDATE_CMDNUM },
	{ REBOOT_PANIC_STR, REBOOT_PANIC_CMDNUM },
};

static unsigned int find_cmd_num(const char *cmd)
{
	unsigned int i;
	unsigned int cmd_id = REBOOT_COLDBOOT_CMDNUM;

	for (i=0; i<sizeof(reboot_cmd_map)/sizeof(reboot_cmd_map[0]); i++) {
		if (!strcmp(reboot_cmd_map[i].name, cmd)) {
			cmd_id = reboot_cmd_map[i].num;
			printk("reboot cmd=%s, cmd_id = %d \n",
				reboot_cmd_map[i].name, reboot_cmd_map[i].num);
			break;
		}
	}
	return cmd_id;
}

#define REG_SYSCTRL_SCLPM3CTRL		0x510
#define PMU_RESET_REG				(0x1C4 << 2)
static void __iomem *pmu_addr = NULL;

static int get_pmu_addr(void)
{
	struct device_node *np;

	if (pmu_addr == NULL) {
		np = of_find_compatible_node(NULL, NULL, "hisilicon,hi6421-pmurtc");
		if (!np) {
			printk(KERN_ERR "get pmu addr error !\n");
			return -1;
		}
		pmu_addr = of_iomap(np, 0);
		if (pmu_addr == NULL) {
			printk(KERN_ERR "get pmu addr error !\n");
			return -1;
		}
	}
	return 0;
}

void set_panic_resetflag(void)
{
	unsigned int value;
	if (get_pmu_addr())
		return;

	/*panic flag is bit 4 and bit 5,now set the flag(0x1<<4)*/
	value = readl(pmu_addr + PMU_RESET_REG);
	value = (value & ~PANIC_FLAG_MASK) | PANIC_FLAG;
	writel(value, (pmu_addr + PMU_RESET_REG));

}
EXPORT_SYMBOL(set_panic_resetflag);

static int is_panic_reboot(void)
{
	unsigned int value;
	if (get_pmu_addr())
		return 0;

	value = readl(pmu_addr + PMU_RESET_REG);
	if ((value & PANIC_FLAG_MASK) == PANIC_FLAG) {
		return 1;
	}
	return 0;
}

static unsigned int get_reboot_id(const char *cmd)
{
	unsigned int cmd_id;

	/* case: warm boot */
	if (cmd && (!strcmp(cmd, "bootloader") ||
		!strcmp(cmd, "recovery") ||
		!strcmp(cmd, "resetfactory") ||
		!strcmp(cmd, "resetuser") ||
		!strcmp(cmd, "sdupdate"))) {

		cmd_id = (find_cmd_num(cmd));
	} else {
		/* otherwise cold boot */
		if (is_panic_reboot() != 0) {
			cmd_id = find_cmd_num(REBOOT_PANIC_STR);
		} else {
			cmd_id = find_cmd_num(REBOOT_COLDBOOT_STR);
		}
	}

	return cmd_id;
}
#endif

#define REG_SYSCTRL_SCSYSSTAT		0x004
void hisi_restart(char mode, const char *cmd)
{
	struct device_node *np;
	void __iomem *sysctrl_addr;

#ifdef CONFIG_HISI_REBOOT_TYPE
	unsigned int cmd_id;
	unsigned int value;
#endif

	if (cmd) {
		printk(KERN_EMERG "hisi_restart cmd:%s.\n", cmd);
	} else {
		printk(KERN_EMERG "hisi_restart without cmd\n");
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (np) {
		sysctrl_addr = of_iomap(np, 0);
	} else {
		printk(KERN_ERR "get sysctrl addr error !\n");
		return;
	}
#ifdef CONFIG_HISI_REBOOT_TYPE
	if (get_pmu_addr()) {
		goto unmap_sctrl;
	}

	/* write reboot flag */
	cmd_id = get_reboot_id(cmd);
	value = readl(pmu_addr + PMU_RESET_REG);
	value &= (0x1<<7);
	value |= cmd_id;
	writel(cmd_id, (pmu_addr + PMU_RESET_REG));

	/* now reboot */
	if (cmd_id == REBOOT_PANIC_CMDNUM) {
		/*flush cache*/
		flush_cache_all();
		/*
		 *notify lpm3
		 *set bit 2 then clr bit 2
		 */
		printk(KERN_EMERG "notify lpm3 to restart ap, and wait to restart!\n");
		value = readl(sysctrl_addr + REG_SYSCTRL_SCLPM3CTRL);
		value |= (0x1<<2);
		writel(value, (sysctrl_addr + REG_SYSCTRL_SCLPM3CTRL));
		value &= ~(0x1<<2);
		writel(value, (sysctrl_addr + REG_SYSCTRL_SCLPM3CTRL));
		/*wait for restart*/
		while(1);
	} else {
		while(1) {
			writel(0xdeadbeef, (sysctrl_addr + REG_SYSCTRL_SCSYSSTAT));
		}
	}
	return;

unmap_sctrl:
	iounmap(sysctrl_addr);
	return;

#else
	while(1) {
		writel(0xdeadbeef, (sysctrl_addr + REG_SYSCTRL_SCSYSSTAT));
	}
#endif
}

static const char *hisi_compat[] __initdata = {
	"hisilicon,hi3630fpga",
	NULL,
};

DT_MACHINE_START(HS_DT, "hi3630fpga")
	.dt_compat	= hisi_compat,
	.smp_init       = smp_init_ops(hisi_smp_init_ops),
	.map_io		= debug_ll_io_init,
	.init_irq		= irqchip_init,
	.init_time	= hisi_timer_init,
	.init_machine	= hisi_init,
	.restart	= hisi_restart,
	.reserve		= hisi_reserve,
MACHINE_END
