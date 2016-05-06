/*
 * arch/arm/mach-k3v2/board-tc45msu3.c
 *
 * Copyright (C) 2010 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/stat.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/sysdev.h>
#include <mach/hardware.h>
#include <mach/system.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include <mach/platform.h>
#include <mach/hisi_cortex-a9.h>
#include <mach/early-debug.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/hardware/gic.h>
#include <asm/mach/map.h>
#include <asm/mach/arch.h>
#include <asm/memory.h>
#include <mach/ddr_map.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mux.h>
#include <mach/board.h>
#include <mach/clock.h>
#include <mach/clk_name_interface.h>
#include <mach/clock_info_oem.h>
#include <mach/lm.h>
#include <mach/util.h>
#include <mach/fixmap.h>
#include <general_sram_map.h>
#include <soc_baseaddr_interface.h>
#if defined (CHIP_BB_HI6210)
#include "soc_peri_sctrl_interface.h"
#elif defined (CHIP_BB_HI6620)
#include <soc_sctrl_interface.h>
#endif
#include <soc_ao_sctrl_interface.h>
#include <soc_mddrc_dmc_interface.h> /* config ddr autorefresh in sram_reboot() */
#include <pwrctrl_multi_memcfg.h>    /* config ddr autorefresh in sram_reboot() */
#include <hsad/config_mgr.h>
#include "MemoryMap.h"
#include <mach/boardid.h>

DEFINE_SPINLOCK(io_lock);

static void sram_reboot()
{
    /* clear SCTLR<2>, disable Dcache and MMU*/
    __asm__ __volatile__ (
        "MRC p15,0,r4,c1,c0,0   \n\t"
        "BIC r4, r4, #0x5       \n\t"
        "BIC r4, r4, #(0x1<<12) \n\t"
        "MCR p15,0,r4,c1,c0,0   \n\t"
        "ISB");

    *(volatile int *)SOC_MDDRC_DMC_DDRC_CTRL_SREF_ADDR(SOC_DDRC_DMC0_BASE_ADDR) = 0x1;
    while((*(volatile int *)SOC_MDDRC_DMC_DDRC_CURR_FUNC_ADDR(SOC_DDRC_DMC0_BASE_ADDR)) & 0x1 == 0)
    {
        *(volatile int *)SOC_MDDRC_DMC_DDRC_CURR_FUNC_ADDR(SOC_DDRC_DMC0_BASE_ADDR) == 0x1;
    }
    while (1) {
        *(volatile int *)SOC_AO_SCTRL_SC_SYS_STAT0_ADDR(REG_BASE_SC_ON) = 0x48698284;
    }
}

static void reboot_board(void)
{
    unsigned long reboot_addr = (unsigned long)IO_ADDRESS(PWRCTRL_ACPU_REBOOT);
    printk(KERN_EMERG "rebooting board...\n");

    void (*reboot_entry)(void) = (void *)reboot_addr;
    memcpy((void *)reboot_addr, (const void *)sram_reboot, 512);
    reboot_entry();
}

struct cmdword
{
	unsigned char name[16];
	unsigned long num;
};

static struct cmdword cmd_map[] =
{
    {"coldboot",		0x10},
    {"bootloader",		0x01},
    {"recovery",		0x02},
    {"resetfactory",	0x03},
    {"resetuser",		0x04},
    {"sdupdate",		0x05},
	{"chargereboot",	0x06},
	{"modemupdate",  0x08},
    {"usbupdate",       0x09},
};

static unsigned long find_rebootmap(const char* str)
{
	unsigned long n = 0;

	for (n = 0; n < sizeof(cmd_map)/sizeof(struct cmdword); n++) {
		if(!strcmp(cmd_map[n].name, str)) {
			printk(KERN_INFO "reboot: %s\n", cmd_map[n].name);
		    break;
		}
	}

	return cmd_map[n].num;
}

#define RESET_COLD_FLAG		 "coldboot"
#define RESET_WARM_FLAG		 "warmboot"
#define SRAM_RESET_FLAG_ADDR IO_ADDRESS(MEMORY_AXI_SRESET_FLAG_ADDR)

static void board_arch_reset(char mode, const char *cmd)
{
#warning "to do: record expection information fastboot"
	unsigned long  num  = 0;

	if (cmd == NULL) {
		/* cmd = NULL; case: cold boot */
		num = find_rebootmap(RESET_COLD_FLAG);
		writel(num, SRAM_RESET_FLAG_ADDR);
	} else {
		/* cmd != null; case: warm boot */
		if (!strcmp(cmd, "bootloader") ||
			!strcmp(cmd, "recovery") ||
			!strcmp(cmd, "resetfactory") ||
			!strcmp(cmd, "resetuser") ||
			!strcmp(cmd, "sdupdate") ||
			!strcmp(cmd, "chargereboot") ||
	        !strcmp(cmd, "usbupdate")||
			!strcmp(cmd, "modemupdate")) {

			num = (find_rebootmap(cmd));
			writel(num, SRAM_RESET_FLAG_ADDR);
		} else {
			/* otherwise cold boot */
			printk(KERN_EMERG "reboot: non-supported mode [%s]\n", cmd);
			num = find_rebootmap(RESET_COLD_FLAG);
			writel(num, SRAM_RESET_FLAG_ADDR);
		}
	}

	printk(KERN_EMERG "reboot: mode reg 0x%x\n", readl(SRAM_RESET_FLAG_ADDR));

	reboot_board();
}

 int enter_recovery_flag;
/**
* parse boot_into_recovery cmdline which is passed from boot_recovery() of boot.c *
* Format : boot_into_recovery_flag=0 or 1             *
*/
static int __init early_parse_enterrecovery_cmdline(char * p)
{
    char enter_recovery[HEX_STRING_MAX + 1];
    char *endptr = NULL;

    memset(enter_recovery, 0, HEX_STRING_MAX + 1);

    memcpy(enter_recovery, p, HEX_STRING_MAX);
    enter_recovery[HEX_STRING_MAX] = '\0';

    enter_recovery_flag = simple_strtoull(enter_recovery, &endptr, TRANSFER_BASE);

    printk("enter recovery p:%s, enter_recovery_flag :%d\n", p, enter_recovery_flag);

    return 0;
}
early_param("enter_recovery", early_parse_enterrecovery_cmdline);

unsigned int get_boot_into_recovery_flag(void)
{
    return enter_recovery_flag;
}
EXPORT_SYMBOL(get_boot_into_recovery_flag);
static unsigned int resetmode_normal = RESETMODE_FLAG_NORMAL;

static int __init early_parse_resetmode_cmdline(char * p)
{
	if (p) {
		if ((!strcmp(p,"press10s,"))||
			(!strcmp(p,"press1s,"))||
			(!strcmp(p,"ColdReset,"))||
			(!strcmp(p,"PoweroffAlarm,"))) {
			resetmode_normal = RESETMODE_FLAG_NORMAL;
			printk("resetmode is %s, resetmode_normal = %d\n", p, resetmode_normal);
		}
		else if ((!strcmp(p,"PanicReset,"))||(!strcmp(p,"AbnormalReset,"))) {
			resetmode_normal = RESETMODE_FLAG_ABNORMAL;
			printk("resetmode is %s resetmode_normal = %d\n", p, resetmode_normal);
		}
		else
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
void (*arch_reset)(char, const char *) = board_arch_reset;

static void __init cache_init(void)
{
#ifdef CONFIG_CACHE_L2X0
	void __iomem *p = (void *)IO_ADDRESS(REG_BASE_L2CC);
	edb_trace(1);

	writel_relaxed(L2X0_DYNAMIC_CLK_GATING_EN|L2X0_STNDBY_MODE_EN,
		p + L2X0_POWER_CTRL);
	writel_relaxed(0x121, p + L2X0_DATA_LATENCY_CTRL);

	/*
	 * 64K * 16 Way = 1024MB
	 */
	/*l2x0_init(p, 0x76070000, 0x8B000fff);*/
	l2x0_init(p, 0x3cc70000, 0xc0000fff);
#endif
}

static void __init init_machine(void)
{
	edb_trace(1);

#warning "add some sys ctrl register operation here, such as enable something .etc"
#if defined(RUN_IN_VPA)
#else
	cache_init();
#endif

#warning "don't replace arm_pm_restart funciton if pm.c is built into boot image "
    arm_pm_restart = board_arch_reset;

#ifndef RUN_IN_EMULATOR
    lm_device_register(&usb_oem_otg);
#endif
    return;
}

static struct k3v2_clk_init_table init_table[] = {
    /* name     parent      rate        enabled */
    {CLK_TIMER0, CLK_REF,   0,      1},
    {CLK_TIMER1, CLK_REF,   0,      1},
    {CLK_TIMER6, CLK_REF,   0,      1},
    {CLK_TIMER7, CLK_REF,   0,      1},
    {CLK_TIMER8, CLK_REF,   0,      1},
    { NULL,	     NULL,	       0,	       0},
};

static void __init init_early(void)
{
    #warning "add some sys ctrl register operation here"
    /*plat_clk_reg();*/

    k3v2_init_clock();

    /*plat_clk_init_from_table(init_table);*/
    k3v2_clk_init_from_table(init_table);
    /*hw_hdmi_clock_init();*/
}

struct iomap_desc
{
    char id[16];
    struct map_desc desc;
};

#define REG_IOMAP(name, mtype) { \
    __stringify(name), \
    { \
        .virtual = (REG_BASE_##name##_VIRT), \
        .pfn = __phys_to_pfn(REG_BASE_##name), \
        .length = REG_##name##_IOSIZE, \
        .type = mtype \
    } \
}

/*virtual address in ascending sort*/
static struct iomap_desc reg_iomap_desc[] __initdata = {
       REG_IOMAP(ACPU_SC, MT_DEVICE), 
	REG_IOMAP(A9PRI, MT_DEVICE),
	REG_IOMAP(L2CC, MT_DEVICE),
	REG_IOMAP(IOC_OFF, MT_DEVICE),
	REG_IOMAP(SC_OFF, MT_DEVICE),
	REG_IOMAP(PMCTRL, MT_DEVICE),
    REG_IOMAP(IPF, MT_DEVICE),
	REG_IOMAP(TIMER0, MT_DEVICE),
	REG_IOMAP(TIMER3, MT_DEVICE),
	REG_IOMAP(TIMER4, MT_DEVICE),
	REG_IOMAP(SC_ON, MT_DEVICE),
	REG_IOMAP(IPC_NS, MT_DEVICE),
	REG_IOMAP(SRAM_ON, MT_MEMORY_ITCM),
	REG_IOMAP(SRAM_OFF, MT_MEMORY_ITCM),
	REG_IOMAP(IOC_ON, MT_DEVICE),
};


#define SHIFT_1K 10
extern void create_mapping(struct map_desc *md);

static int __init init_reg_iomap(void)
{
    struct iomap_desc *desc = reg_iomap_desc;
    int size = ARRAY_SIZE(reg_iomap_desc);
    int i;

    printk("create fix register iomap :\n");

    for (i = 0; i < size; i++){
        create_mapping(&desc->desc);
        desc ++;
    }

	return 0;
}

#define SHIFT_1K 10

static int __init check_reg_iomap(void)
{
    struct iomap_desc *desc = reg_iomap_desc;
    int size = ARRAY_SIZE(reg_iomap_desc);
    unsigned long end = REG_BASE_VIRT;
    int i;

    printk("check fix register iomap :\n");

    for (i = 0; i < size; i++){
        /*print the map*/
        printk("[ %10s ] : phy [ %08x ] vir [ %08x ] type [ %08x ] size [ %5u ]kb\n", desc->id, \
            (unsigned int)(__pfn_to_phys(desc->desc.pfn)), (unsigned int)desc->desc.virtual, \
            desc->desc.type, desc->desc.length>>SHIFT_1K);

        /*check address space*/
        if (desc->desc.virtual < end){
            printk("fix register iomap [ %16s ] [ %08x ] error !\n", desc->id, (unsigned int)desc->desc.virtual);
            return -1;
        }
        end = desc->desc.virtual + desc->desc.length;
        desc ++;
    }

	return 0;
}

static int __init init_check_reg_iomap(void)
{
    int ret = check_reg_iomap();

	if (ret){
		printk(KERN_ERR "#############################\n");
		printk(KERN_ERR "IO Register MAP Check error !\n");
		printk(KERN_ERR "#############################\n");

		panic("io register map check error");
	}

	return ret;
}
late_initcall(init_check_reg_iomap);

#define IPC_IOMAP() { \
	.virtual =   IPC_SHARE_MEM_VIRT_ADDR,	\
	.pfn     =    __phys_to_pfn(IPC_SHARE_MEM_ADDR), \
	.length  =    IPC_SHARE_MEM_SIZE, \
	.type    =    MT_DEVICE\
}

#define MCU_SHARE_IOMAP() { \
	.virtual =   MCU_SHARE_MEM_VIRT_ADDR,	\
	.pfn     =    __phys_to_pfn(MCU_SHARE_MEM_ADDR), \
	.length  =    MCU_SHARE_MEM_SIZE, \
	.type    =    MT_DEVICE\
}

#define EXCP_IOMAP() { \
	.virtual =   GLOBAL_MEM_EXCP_BASE_ADDR_VIRT,	\
	.pfn     =    __phys_to_pfn(GLOBAL_MEM_EXCP_BASE_ADDR), \
	.length  =    GLOBAL_MEM_EXCP_SIZE, \
	.type    =    MT_DEVICE\
}

#define TTF_IOMAP() { \
	.virtual =   ECS_TTF_BASE_ADDR_VIRT,	\
	.pfn     =    __phys_to_pfn(ECS_TTF_BASE_ADDR), \
	.length  =    GLOBAL_MEM_GU_RESERVED_SIZE, \
	.type    =    MT_DEVICE\
}

static struct map_desc ddr_map_desc[] __initdata = {
    TTF_IOMAP(),
    IPC_IOMAP(),
    EXCP_IOMAP(),
    MCU_SHARE_IOMAP(),
};

/*
 * Map io address
 */
static void __init map_reg_io(void)
{
    init_reg_iomap();

	iotable_init(ddr_map_desc, ARRAY_SIZE(ddr_map_desc));

	edb_init();

	edb_trace(1);

#ifdef CONFIG_HAVE_ARM_TWD
	#include <asm/smp_twd.h>
	twd_base = IO_ADDRESS(REG_CPU_A9PRVWDOG_BASE);
#endif
	return;
}


static void __init map_io(void)
{
	map_reg_io();

	return;
}

void __iomem *gic_dist_base_addr;
static void __init init_irq(void)
{
	edb_putstr("gic_init_irq\n");

	/* board GIC, primary */
	gic_cpu_base_addr = (void __iomem *)IO_ADDRESS(REG_CPU_A9GIC_BASE);
	WARN_ON(gic_cpu_base_addr == NULL);

	gic_dist_base_addr = (void __iomem *)IO_ADDRESS(REG_CPU_A9GICDIST_BASE);
	WARN_ON(gic_dist_base_addr == NULL);

	/* core tile GIC, primary */
	gic_init(0, IRQ_LOCALTIMER,
		(void __iomem *) gic_dist_base_addr,
		(void __iomem *) gic_cpu_base_addr);
}

static int a9pri_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "gic base phy %x vir %x \n",
			(unsigned int)REG_CPU_A9GIC_BASE,
			(unsigned int) gic_cpu_base_addr);

	seq_printf(m, "gic dist phy %x vir %x \n",
			(unsigned int)REG_CPU_A9GICDIST_BASE,
			(unsigned int) IO_ADDRESS(REG_CPU_A9GICDIST_BASE));

       /*todo : add some timer0 internel status*/

	return 0;
}

static int a9pri_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, a9pri_proc_show, NULL);
}

static const struct file_operations a9pri_proc_fops = {
	.open		= a9pri_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release		= single_release,
};

static int __init  a9pri_proc_init(void)
{
	balong_create_debug_proc_entry("a9private", S_IRUGO, &a9pri_proc_fops, NULL);

	return 0;
}
module_init(a9pri_proc_init);

//qijiwen reserve memory for  Graphic/ Dcode/EnCode etc.
#include <linux/memblock.h>
#include <mach/hisi_mem.h>
static void k3v2_reserve(void)
{
	unsigned long reserved_size;
	phys_addr_t base;

	reserved_size = hisi_get_reserve_mem_size();

	base = HISI_BASE_MEMORY_SIZE - reserved_size;

	printk(KERN_INFO "%s the reserved memor region base:0x%08lx size:0x%08lx\n", __func__, base, reserved_size);

	memblock_remove(base, reserved_size);
}

MACHINE_START(HI6620OEM, "hi6620oem")
	.boot_params		= PLAT_PHYS_OFFSET + 0x00000100,
	.init_irq           = init_irq,
	.init_machine   	= init_machine,
	.map_io          	= map_io,
	.timer             	= &board_timer,
	.init_early 	 	= init_early,
	.reserve	= k3v2_reserve,
MACHINE_END
